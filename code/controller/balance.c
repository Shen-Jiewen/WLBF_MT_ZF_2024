/*
 * balance.c
 *
 *  Created on: 2024年3月16日
 *      Author: Rick
 */
#include "balance.h"

extern pid_type_def yaw_angle_pid;
extern pid_type_def yaw_gyro_pid;
extern pid_type_def roll_angle_pid;
extern pid_type_def roll_gyro_pid;
extern pid_type_def forward_speed_pid;
extern Status_car status_car;

extern float zero_angle;
//extern float yaw_zero_angle;
extern float forward_speed_set;
extern int   turn_over_flag;
extern float yaw_gyro_set;
extern int servo_pwm_set;

extern FusionEuler euler;

float yaw_angle = 0.f;
float yaw_gyro = 0.f;
float roll_angle = 0.f;
float roll_gyro = 0.f;
float forward_speed = 0.f;
float side_speed = 0.f;

void balance(void){
    //电机侧向电机角度和角速度状态输入
    yaw_angle = euler.angle.yaw;
    yaw_gyro = -imu963ra_gyro_transition(imu963ra_gyro_z);
    roll_angle = euler.angle.pitch;
    roll_gyro = -imu963ra_gyro_transition(imu963ra_gyro_y);
    //电机前向电机速度输入
    forward_speed = -encoder_get_count(TIM4_ENCODER);
    encoder_clear_count(TIM4_ENCODER);
    forward_speed = 0;
    //电机侧向电机编码器输入
    side_speed = encoder_get_count(TIM2_ENCODER);
    encoder_clear_count(TIM2_ENCODER);

    //计算pid
    //平衡方向pid计算
    PID_calc(&yaw_gyro_pid, yaw_gyro, yaw_gyro_set);
    PID_calc(&roll_angle_pid, roll_angle + yaw_gyro_pid.out, zero_angle);   //roll轴角度环
    PID_calc(&roll_gyro_pid, roll_gyro - roll_angle_pid.out, 0);            //roll轴角速度环
    //行进方向pid计算
    PID_calc(&forward_speed_pid, forward_speed, forward_speed_set);

    //前进和左右电机电机赋值
    //摔倒检测
    if(euler.angle.pitch <= 40 && euler.angle.pitch >= -40 && turn_over_flag == 0){
        set_speed(forward_speed_pid.out,roll_gyro_pid.out);
    }else{
        set_speed(0,0);
        //重置标志位
        status_car = idle;
        turn_over_flag = 1;
        //清空PID参数
        PID_clear(&yaw_angle_pid);
        PID_clear(&yaw_gyro_pid);
        PID_clear(&roll_angle_pid);
        PID_clear(&roll_gyro_pid);
    }

    //舵机控制
    pwm_set_duty(ATOM0_CH7_P02_7,servo_pwm_set);
}

//pwm1为前进的速度,pwm2为左右的速度
//pwm1为正向前,为负向后,pwm2--[正 - 向右] [负 - 向左]
void set_speed(int pwm1,int pwm2){
    static int pwm3,pwm4;

    //左右控制的死区
    if(pwm2 > 0){
        pwm2 += DEAD_ZONE;
    }else if(pwm2 < 0){
        pwm2 -= DEAD_ZONE;
    }

    //pwm差分解算
    pwm3 = pwm1 + pwm2;
    pwm4 = pwm1 - pwm2;

    //限幅函数
    pwm3 = LIMIT(pwm3,-10000,10000);
    pwm4 = LIMIT(pwm4,-10000,10000);

    if(pwm3 >= 0){
        gpio_init(P21_2,GPO,1,GPO_PUSH_PULL);
        pwm_set_duty(ATOM0_CH1_P21_3,pwm3);
    }else{
        gpio_init(P21_2,GPO,0,GPO_PUSH_PULL);
        pwm_set_duty(ATOM0_CH1_P21_3,-pwm3);
    }

    if(pwm4 >= 0){
        gpio_init(P21_4,GPO,0,GPO_PUSH_PULL);
        pwm_set_duty(ATOM0_CH3_P21_5,pwm4);
    }else{
        gpio_init(P21_4,GPO,1,GPO_PUSH_PULL);
        pwm_set_duty(ATOM0_CH3_P21_5,-pwm4);
    }
}


