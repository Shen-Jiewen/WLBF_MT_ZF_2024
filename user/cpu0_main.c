/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明:
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
#define TRAGET_SPEED 2000
#define SPEED_ACCUMULATION 200

//限幅函数
#define CLAMP(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

extern Img_Param prm;      //图像参数结构体

/***********************全局变量******************************/
FusionAhrs ahrs;
FusionOffset offset;
FusionEuler euler;

pid_type_def yaw_angle_pid;
pid_type_def yaw_gyro_pid;
pid_type_def roll_angle_pid;
pid_type_def roll_gyro_pid;
pid_type_def forward_speed_pid;

int watch_count = 0;                //10/100ms间隔累加
float zero_angle = -0.13f;          //roll轴的零点角度
float yaw_zero_angle = 0.f;         //yaw轴的目标角度(暂时废弃,没有加yaw轴角度环)
float forward_speed_set = 0;        //前进速度设置
int servo_pwm_set = 390;            //舵机pwm设置,390为中值,增加为右转打舵,减少为左转打舵
int   turn_over_flag = 1;           //摔倒标志位   [1]:摔倒了 [0]:妹摔
float yaw_gyro_set = 0.f;           //yaw轴角速度设置,用于给小车转弯
float prm_error_param = 2.2f;       //摄像头读取到的偏差作用于转向的系数
float prm_forward_param = 1.1f;     //前进速度的增益系数
int   g_mutexFlagBit = 0;
int   g_lastMutexFlagBit = 0;       //双核互斥锁标志位和上一次标志位,用于屏幕的双核调度  [0]:cpu0占用  [1]:cpu1占用
int   ramp_flag = 0;                //坡道识别标志位
float watch_param1 = 20.f;
int   elec_action = 0;              //元素动作编号

Menu menu;
Button buttons[NUM_BUTTONS];
Status_car status_car;
LowPassFilter filteredCameraBias;
/***********************全局变量******************************/

// **************************** 代码区域 ****************************
int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等
    //TFT屏幕初始化
    tft180_set_dir(TFT180_CROSSWISE_180);
    tft180_set_font(TFT180_6X8_FONT);
    tft180_init();
    tft180_show_string(1,1,"WDR MT init...");
    tft180_clear();

    //按键初始化
    KEY_Init();
    //IMU9963RA初始化
    int imu_res = imu963ra_init();
    if(imu_res == 1){
        tft180_show_string(1,1,"imu error!!!");
    }

    //电机PWM和使能引脚初始化
    pwm_init(ATOM0_CH3_P21_5, 1000, 0);
    pwm_init(ATOM0_CH1_P21_3, 1000, 0);
    gpio_init(P21_2,GPO,1,GPO_PUSH_PULL);
    gpio_init(P21_4,GPO,0,GPO_PUSH_PULL);//前进方向

    //电机编码器初始化
    encoder_dir_init(TIM4_ENCODER,TIM4_ENCODER_CH1_P02_8,TIM4_ENCODER_CH2_P00_9);//前进电机编码器
    encoder_dir_init(TIM2_ENCODER,TIM2_ENCODER_CH1_P33_7,TIM2_ENCODER_CH2_P33_6);//左右电机编码器

    //舵机初始化
    pwm_init(ATOM0_CH7_P02_7, 50, servo_pwm_set);

    //蜂鸣器初始化
    gpio_init(P33_10,GPO,0,GPO_PUSH_PULL);

    //各级pid参数初始化
    const static fp32 yaw_gyro_pid_s[3] = {MOTOR_YAW_GYRO_PID_KP, MOTOR_YAW_GYRO_PID_KI, MOTOR_YAW_GYRO_PID_KD};
    const static fp32 roll_angle_pid_s[3] = {MOTOR_ROLL_ANGLE_PID_KP, MOTOR_ROLL_ANGLE_PID_KI, MOTOR_ROLL_ANGLE_PID_KD};
    const static fp32 roll_gyro_pid_s[3] = {MOTOR_ROLL_GYRO_PID_KP, MOTOR_ROLL_GYRO_PID_KI, MOTOR_ROLL_GYRO_PID_KD};
    const static fp32 forward_speed_pid_s[3] = {MOTOR_FORWARD_SPEED_PID_KP, MOTOR_FORWARD_SPEED_PID_KI, MOTOR_FORWARD_SPEED_PID_KD};
    PID_init(&yaw_gyro_pid, PID_POSITION, yaw_gyro_pid_s, MOTOR_YAW_GYRO_PID_MAX_OUT, MOTOR_YAW_GYRO_PID_MAX_IOUT);
    PID_init(&roll_angle_pid, PID_POSITION, roll_angle_pid_s, MOTOR_ROLL_ANGLE_PID_MAX_OUT, MOTOR_ROLL_ANGLE_PID_MAX_IOUT);
    PID_init(&roll_gyro_pid, PID_DELTA, roll_gyro_pid_s, MOTOR_ROLL_GYRO_PID_MAX_OUT, MOTOR_ROLL_GYRO_PID_MAX_IOUT);
    PID_init(&forward_speed_pid, PID_POSITION, forward_speed_pid_s, MOTOR_FORWARD_SPEED_PID_MAX_OUT, MOTOR_FORWARD_SPEED_PID_MAX_IOUT);

    //菜单初始化(菜单page和参数index的范围都是从零开始的)
    menu_init(&menu, 3, 15);
    //菜单参数赋值
    const static fp32 add_reduce_values_1[4] = {0.1, -0.1, 0.01, -0.01};
    const static fp32 add_reduce_values_2[4] = {1, -1, 0.1, -0.1};
    const static fp32 add_reduce_values_3[4] = {5, -5, 1, -1};
    //第零页
    modify_param(&menu, 1, 0, &yaw_gyro_pid.Kp, add_reduce_values_1);
    //第一页
    modify_param(&menu, 1, 0, &yaw_angle_pid.Kp, add_reduce_values_1);
    modify_param(&menu, 1, 1, &yaw_angle_pid.Ki, add_reduce_values_1);
    modify_param(&menu, 1, 2, &yaw_angle_pid.Kd, add_reduce_values_1);
    modify_param(&menu, 1, 3, &yaw_gyro_pid.Kp, add_reduce_values_1);
    modify_param(&menu, 1, 4, &yaw_gyro_pid.Ki, add_reduce_values_1);
    modify_param(&menu, 1, 5, &yaw_gyro_pid.Kd, add_reduce_values_1);
    modify_param(&menu, 1, 6, &roll_angle_pid.Kp, add_reduce_values_1);
    modify_param(&menu, 1, 7, &roll_angle_pid.Ki, add_reduce_values_1);
    modify_param(&menu, 1, 8, &roll_angle_pid.Kd, add_reduce_values_1);
    modify_param(&menu, 1, 9, &roll_gyro_pid.Kp, add_reduce_values_1);
    modify_param(&menu, 1, 10, &roll_gyro_pid.Ki, add_reduce_values_1);
    modify_param(&menu, 1, 11, &roll_gyro_pid.Kd, add_reduce_values_1);
    modify_param(&menu, 1, 12, &forward_speed_pid.Kp, add_reduce_values_2);
    modify_param(&menu, 1, 13, &forward_speed_pid.Ki, add_reduce_values_1);
    modify_param(&menu, 1, 14, &forward_speed_pid.Kd, add_reduce_values_1);
    //第二页
    modify_param(&menu, 2, 0, &zero_angle, add_reduce_values_1);
    modify_param(&menu, 2, 1, &prm_error_param, add_reduce_values_1);
    modify_param(&menu, 2, 2, &watch_param1, add_reduce_values_3);

    //陀螺仪计算定时器初始化
    pit_init(CCU60_CH0,1000);//定时1ms
    pit_enable(CCU60_CH0);
    pit_start(CCU60_CH0);

    //pid计算定时器初始化
    pit_init(CCU60_CH1,1000);//定时1ms
    pit_enable(CCU60_CH1);
    pit_start(CCU60_CH1);

    //按键扫描定时器初始化
    pit_init(CCU61_CH0,10000);//定时10ms
    pit_enable(CCU61_CH0);
    pit_start(CCU61_CH0);

    //无线串口定时器初始化
    pit_init(CCU61_CH1,5000);//定时5ms
    pit_enable(CCU61_CH1);
    pit_start(CCU61_CH1);

    //初始化点阵屏
    dot_matrix_screen_init();

    //姿态解算初始化
    FusionAhrsInitialise(&ahrs);    // Initialise algorithms
    FusionOffsetInitialise(&offset, 1000);
    // Set AHRS algorithm settings
    const FusionAhrsSettings settings = {
            .convention = FusionConventionNwu,
            .gain = 0.5f,
            .gyroscopeRange = 2000.0f, /* replace this with actual gyroscope range in degrees/s */
            .accelerationRejection = 10.0f,
            .magneticRejection = 10.0f,
            .recoveryTriggerPeriod = 5 *1000
    };
    FusionAhrsSetSettings(&ahrs, &settings);
    //低通滤波器结构体初始化
    initLowPassFilter(&filteredCameraBias, 10);
    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    while (TRUE)
    {
        // 此处编写需要循环执行的代码

        //摄像头偏差数据处理
        float cameraBias = processLowPassFilter(&filteredCameraBias, prm.error*1.f);

        /******************状态机控制*******************/
        switch(status_car)
        {
            case idle:
                //空闲直立状态
                forward_speed_set = 0.f;
                yaw_gyro_set = 0.f;
                break;
            case turn:
                //速度转换(加减速)
                if(forward_speed_set > TRAGET_SPEED){
                    //每隔100ms提速150,1秒进入最高速
                    if(watch_count >= 10){
                        forward_speed_set += SPEED_ACCUMULATION;
                        watch_count = 0;
                    }
                }else{
                    status_car = run;
                }
                break;
            case run:
                /*****************   根据偏差量设置前进速度   ************************/
                if(fabs(cameraBias) >= 60){
                    prm_forward_param = 0.9;
                }
                else{
                    if(prm_forward_param <= 1.0){
                        prm_forward_param += 0.1;
                    }
                }
                /******************   根据偏差设置车身姿态   ************************/
                if(fabs(cameraBias) >= 80){
                    //大弯道
                    zero_angle = -0.13 + (cameraBias >= 0 ? 5.f:-5.f);
                } else if(fabs(cameraBias) >= 40){
                    //小弯道
                    zero_angle = -0.13 + (cameraBias >= 0 ? 2.f:-2.f);
                }
                else{
                    //偏差不大设置为正常零点
                    zero_angle = -0.13;
                }
                /******************   根据偏差设置舵机转角   ************************/
                servo_pwm_set = CLAMP((int)(390 + cameraBias/1.75), 250, 530);

                /*****************    根据元素执行固定操作    ***********************/
                if(prm.round_flag == 1 || prm.round_flag == 2){
                    //清空定时器,修改状态机
                    watch_count = 0;
                    status_car = action;
                }

                /******************   前进速度和转弯偏差设置   **********************/
                //偏差角速度设置
                yaw_gyro_set = -(cameraBias * prm_error_param);//获取摄像头偏差
                //速度设置
                forward_speed_set = (SPEED_ACCUMULATION * 10 * prm_forward_param);
                break;
            case action:
                //记录当前动作的执行时间
                static int action_time = 0;
                /****************   根据元素状态执行设置不同的动作   *******************/
                if(prm.round_flag == 1){
                    //左环岛
                    elec_action = 1;
                }else if(prm.round_flag == 2){
                    //右环岛
                    elec_action = 2;
                }

                /****************   根据元素状态不同执行不同的动作   *******************/
                switch(elec_action){
                    case 1:
                        //计时
                        if(watch_count >= 10){
                            watch_count = 0;
                            action_time += 1;
                        }
                        //左环岛执行固定动作
                        if(action_time <= 50){
                            //偏转角度设置
                            zero_angle = -0.13 + 5.f;
                            //舵机转角设置
                            servo_pwm_set = 390 + 80;
                            //偏差角速度设置
                            yaw_gyro_set = 80.f;//获取摄像头偏差
                            //速度设置
                            forward_speed_set = 1800;
                        } else {
                            //清空所有状态,退出左环岛动作
                            action_time = 0;
                            elec_action = 0;
                            status_car = run;
                        }
                        break;
                    case 2:
                        //计时
                        if(watch_count >= 10){
                            watch_count = 0;
                            action_time += 1;
                        }
                        //右环岛执行固定动作
                        if(action_time <= 50){
                            //偏转角度设置
                            zero_angle = -0.13 - 5.f;
                            //舵机转角设置
                            servo_pwm_set = 390 - 80;
                            //偏差角速度设置
                            yaw_gyro_set = -80.f;//获取摄像头偏差
                            //速度设置
                            forward_speed_set = 1800;
                        } else {
                            //清空所有状态,退出左环岛动作
                            action_time = 0;
                            elec_action = 0;
                            status_car = run;
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

        //显示页面
        if(g_lastMutexFlagBit != g_mutexFlagBit && g_mutexFlagBit == 0){
            //屏幕核心调度切换,重新初始化,且只初始化一次
            tft180_clear();
            tft180_set_dir(TFT180_CROSSWISE_180);
            tft180_set_font(TFT180_6X8_FONT);
            tft180_init();
        }
        if(g_mutexFlagBit == 0){
            //显示菜单
            menu_show(&menu);
        }
        //保存上一次的标志位
        g_lastMutexFlagBit = g_mutexFlagBit;

        /*************************   灯光秀显示   *******************************/
//        tld7002_display(5000,"OK ");

        //延时10ms
//        system_delay_ms(100);
        // 此处编写需要循环执行的代码
    }
}

#pragma section all restore


// **************************** 代码区域 ****************************
