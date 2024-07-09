/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע��:
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          cpu0_main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.4
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
#define TRAGET_SPEED 2000
#define SPEED_ACCUMULATION 200

//�޷�����
#define CLAMP(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

extern Img_Param prm;      //ͼ������ṹ��

/***********************ȫ�ֱ���******************************/
FusionAhrs ahrs;
FusionOffset offset;
FusionEuler euler;

pid_type_def yaw_angle_pid;
pid_type_def yaw_gyro_pid;
pid_type_def roll_angle_pid;
pid_type_def roll_gyro_pid;
pid_type_def forward_speed_pid;

int watch_count = 0;                //10/100ms����ۼ�
float zero_angle = -0.13f;          //roll������Ƕ�
float yaw_zero_angle = 0.f;         //yaw���Ŀ��Ƕ�(��ʱ����,û�м�yaw��ǶȻ�)
float forward_speed_set = 0;        //ǰ���ٶ�����
int servo_pwm_set = 390;            //���pwm����,390Ϊ��ֵ,����Ϊ��ת���,����Ϊ��ת���
int   turn_over_flag = 1;           //ˤ����־λ   [1]:ˤ���� [0]:��ˤ
float yaw_gyro_set = 0.f;           //yaw����ٶ�����,���ڸ�С��ת��
float prm_error_param = 2.2f;       //����ͷ��ȡ����ƫ��������ת���ϵ��
float prm_forward_param = 1.1f;     //ǰ���ٶȵ�����ϵ��
int   g_mutexFlagBit = 0;
int   g_lastMutexFlagBit = 0;       //˫�˻�������־λ����һ�α�־λ,������Ļ��˫�˵���  [0]:cpu0ռ��  [1]:cpu1ռ��
int   ramp_flag = 0;                //�µ�ʶ���־λ
float watch_param1 = 20.f;
int   elec_action = 0;              //Ԫ�ض������

Menu menu;
Button buttons[NUM_BUTTONS];
Status_car status_car;
LowPassFilter filteredCameraBias;
/***********************ȫ�ֱ���******************************/

// **************************** �������� ****************************
int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������
    //TFT��Ļ��ʼ��
    tft180_set_dir(TFT180_CROSSWISE_180);
    tft180_set_font(TFT180_6X8_FONT);
    tft180_init();
    tft180_show_string(1,1,"WDR MT init...");
    tft180_clear();

    //������ʼ��
    KEY_Init();
    //IMU9963RA��ʼ��
    int imu_res = imu963ra_init();
    if(imu_res == 1){
        tft180_show_string(1,1,"imu error!!!");
    }

    //���PWM��ʹ�����ų�ʼ��
    pwm_init(ATOM0_CH3_P21_5, 1000, 0);
    pwm_init(ATOM0_CH1_P21_3, 1000, 0);
    gpio_init(P21_2,GPO,1,GPO_PUSH_PULL);
    gpio_init(P21_4,GPO,0,GPO_PUSH_PULL);//ǰ������

    //�����������ʼ��
    encoder_dir_init(TIM4_ENCODER,TIM4_ENCODER_CH1_P02_8,TIM4_ENCODER_CH2_P00_9);//ǰ�����������
    encoder_dir_init(TIM2_ENCODER,TIM2_ENCODER_CH1_P33_7,TIM2_ENCODER_CH2_P33_6);//���ҵ��������

    //�����ʼ��
    pwm_init(ATOM0_CH7_P02_7, 50, servo_pwm_set);

    //��������ʼ��
    gpio_init(P33_10,GPO,0,GPO_PUSH_PULL);

    //����pid������ʼ��
    const static fp32 yaw_gyro_pid_s[3] = {MOTOR_YAW_GYRO_PID_KP, MOTOR_YAW_GYRO_PID_KI, MOTOR_YAW_GYRO_PID_KD};
    const static fp32 roll_angle_pid_s[3] = {MOTOR_ROLL_ANGLE_PID_KP, MOTOR_ROLL_ANGLE_PID_KI, MOTOR_ROLL_ANGLE_PID_KD};
    const static fp32 roll_gyro_pid_s[3] = {MOTOR_ROLL_GYRO_PID_KP, MOTOR_ROLL_GYRO_PID_KI, MOTOR_ROLL_GYRO_PID_KD};
    const static fp32 forward_speed_pid_s[3] = {MOTOR_FORWARD_SPEED_PID_KP, MOTOR_FORWARD_SPEED_PID_KI, MOTOR_FORWARD_SPEED_PID_KD};
    PID_init(&yaw_gyro_pid, PID_POSITION, yaw_gyro_pid_s, MOTOR_YAW_GYRO_PID_MAX_OUT, MOTOR_YAW_GYRO_PID_MAX_IOUT);
    PID_init(&roll_angle_pid, PID_POSITION, roll_angle_pid_s, MOTOR_ROLL_ANGLE_PID_MAX_OUT, MOTOR_ROLL_ANGLE_PID_MAX_IOUT);
    PID_init(&roll_gyro_pid, PID_DELTA, roll_gyro_pid_s, MOTOR_ROLL_GYRO_PID_MAX_OUT, MOTOR_ROLL_GYRO_PID_MAX_IOUT);
    PID_init(&forward_speed_pid, PID_POSITION, forward_speed_pid_s, MOTOR_FORWARD_SPEED_PID_MAX_OUT, MOTOR_FORWARD_SPEED_PID_MAX_IOUT);

    //�˵���ʼ��(�˵�page�Ͳ���index�ķ�Χ���Ǵ��㿪ʼ��)
    menu_init(&menu, 3, 15);
    //�˵�������ֵ
    const static fp32 add_reduce_values_1[4] = {0.1, -0.1, 0.01, -0.01};
    const static fp32 add_reduce_values_2[4] = {1, -1, 0.1, -0.1};
    const static fp32 add_reduce_values_3[4] = {5, -5, 1, -1};
    //����ҳ
    modify_param(&menu, 1, 0, &yaw_gyro_pid.Kp, add_reduce_values_1);
    //��һҳ
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
    //�ڶ�ҳ
    modify_param(&menu, 2, 0, &zero_angle, add_reduce_values_1);
    modify_param(&menu, 2, 1, &prm_error_param, add_reduce_values_1);
    modify_param(&menu, 2, 2, &watch_param1, add_reduce_values_3);

    //�����Ǽ��㶨ʱ����ʼ��
    pit_init(CCU60_CH0,1000);//��ʱ1ms
    pit_enable(CCU60_CH0);
    pit_start(CCU60_CH0);

    //pid���㶨ʱ����ʼ��
    pit_init(CCU60_CH1,1000);//��ʱ1ms
    pit_enable(CCU60_CH1);
    pit_start(CCU60_CH1);

    //����ɨ�趨ʱ����ʼ��
    pit_init(CCU61_CH0,10000);//��ʱ10ms
    pit_enable(CCU61_CH0);
    pit_start(CCU61_CH0);

    //���ߴ��ڶ�ʱ����ʼ��
    pit_init(CCU61_CH1,5000);//��ʱ5ms
    pit_enable(CCU61_CH1);
    pit_start(CCU61_CH1);

    //��ʼ��������
    dot_matrix_screen_init();

    //��̬�����ʼ��
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
    //��ͨ�˲����ṹ���ʼ��
    initLowPassFilter(&filteredCameraBias, 10);
    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���

        //����ͷƫ�����ݴ���
        float cameraBias = processLowPassFilter(&filteredCameraBias, prm.error*1.f);

        /******************״̬������*******************/
        switch(status_car)
        {
            case idle:
                //����ֱ��״̬
                forward_speed_set = 0.f;
                yaw_gyro_set = 0.f;
                break;
            case turn:
                //�ٶ�ת��(�Ӽ���)
                if(forward_speed_set > TRAGET_SPEED){
                    //ÿ��100ms����150,1����������
                    if(watch_count >= 10){
                        forward_speed_set += SPEED_ACCUMULATION;
                        watch_count = 0;
                    }
                }else{
                    status_car = run;
                }
                break;
            case run:
                /*****************   ����ƫ��������ǰ���ٶ�   ************************/
                if(fabs(cameraBias) >= 60){
                    prm_forward_param = 0.9;
                }
                else{
                    if(prm_forward_param <= 1.0){
                        prm_forward_param += 0.1;
                    }
                }
                /******************   ����ƫ�����ó�����̬   ************************/
                if(fabs(cameraBias) >= 80){
                    //�����
                    zero_angle = -0.13 + (cameraBias >= 0 ? 5.f:-5.f);
                } else if(fabs(cameraBias) >= 40){
                    //С���
                    zero_angle = -0.13 + (cameraBias >= 0 ? 2.f:-2.f);
                }
                else{
                    //ƫ�������Ϊ�������
                    zero_angle = -0.13;
                }
                /******************   ����ƫ�����ö��ת��   ************************/
                servo_pwm_set = CLAMP((int)(390 + cameraBias/1.75), 250, 530);

                /*****************    ����Ԫ��ִ�й̶�����    ***********************/
                if(prm.round_flag == 1 || prm.round_flag == 2){
                    //��ն�ʱ��,�޸�״̬��
                    watch_count = 0;
                    status_car = action;
                }

                /******************   ǰ���ٶȺ�ת��ƫ������   **********************/
                //ƫ����ٶ�����
                yaw_gyro_set = -(cameraBias * prm_error_param);//��ȡ����ͷƫ��
                //�ٶ�����
                forward_speed_set = (SPEED_ACCUMULATION * 10 * prm_forward_param);
                break;
            case action:
                //��¼��ǰ������ִ��ʱ��
                static int action_time = 0;
                /****************   ����Ԫ��״ִ̬�����ò�ͬ�Ķ���   *******************/
                if(prm.round_flag == 1){
                    //�󻷵�
                    elec_action = 1;
                }else if(prm.round_flag == 2){
                    //�һ���
                    elec_action = 2;
                }

                /****************   ����Ԫ��״̬��ִͬ�в�ͬ�Ķ���   *******************/
                switch(elec_action){
                    case 1:
                        //��ʱ
                        if(watch_count >= 10){
                            watch_count = 0;
                            action_time += 1;
                        }
                        //�󻷵�ִ�й̶�����
                        if(action_time <= 50){
                            //ƫת�Ƕ�����
                            zero_angle = -0.13 + 5.f;
                            //���ת������
                            servo_pwm_set = 390 + 80;
                            //ƫ����ٶ�����
                            yaw_gyro_set = 80.f;//��ȡ����ͷƫ��
                            //�ٶ�����
                            forward_speed_set = 1800;
                        } else {
                            //�������״̬,�˳��󻷵�����
                            action_time = 0;
                            elec_action = 0;
                            status_car = run;
                        }
                        break;
                    case 2:
                        //��ʱ
                        if(watch_count >= 10){
                            watch_count = 0;
                            action_time += 1;
                        }
                        //�һ���ִ�й̶�����
                        if(action_time <= 50){
                            //ƫת�Ƕ�����
                            zero_angle = -0.13 - 5.f;
                            //���ת������
                            servo_pwm_set = 390 - 80;
                            //ƫ����ٶ�����
                            yaw_gyro_set = -80.f;//��ȡ����ͷƫ��
                            //�ٶ�����
                            forward_speed_set = 1800;
                        } else {
                            //�������״̬,�˳��󻷵�����
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

        //��ʾҳ��
        if(g_lastMutexFlagBit != g_mutexFlagBit && g_mutexFlagBit == 0){
            //��Ļ���ĵ����л�,���³�ʼ��,��ֻ��ʼ��һ��
            tft180_clear();
            tft180_set_dir(TFT180_CROSSWISE_180);
            tft180_set_font(TFT180_6X8_FONT);
            tft180_init();
        }
        if(g_mutexFlagBit == 0){
            //��ʾ�˵�
            menu_show(&menu);
        }
        //������һ�εı�־λ
        g_lastMutexFlagBit = g_mutexFlagBit;

        /*************************   �ƹ�����ʾ   *******************************/
//        tld7002_display(5000,"OK ");

        //��ʱ10ms
//        system_delay_ms(100);
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

#pragma section all restore


// **************************** �������� ****************************
