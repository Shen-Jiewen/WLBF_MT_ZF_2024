/*
 * balance.h
 *
 *  Created on: 2024��3��16��
 *      Author: Rick
 */

#ifndef CODE_CONTROLLER_BALANCE_H_
#define CODE_CONTROLLER_BALANCE_H_
#include "zf_common_headfile.h"

typedef enum {
    idle = 0,       //0:����-ԭ��ֱ��
    turn,           //1:�ٶ�ת��
    run,            //2:����ѭ��
    action,         //3.ִ�й̶�����
}Status_car;

// �����MIN��MAX�����ڻ�ȡ��Сֵ�����ֵ
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// �����LIMIT���������Ʊ���x��ȡֵ��Χ��[min, max]֮��
#define LIMIT(x, min, max) (MIN(MAX(x, min), max))

#define MOTOR_YAW_GYRO_PID_KP               0.1f
#define MOTOR_YAW_GYRO_PID_KI               0.0f
#define MOTOR_YAW_GYRO_PID_KD               4.0f
#define MOTOR_YAW_GYRO_PID_MAX_OUT          1000.0f
#define MOTOR_YAW_GYRO_PID_MAX_IOUT         100.0f

#define MOTOR_ROLL_ANGLE_PID_KP             2.0f
#define MOTOR_ROLL_ANGLE_PID_KI             0.0f
#define MOTOR_ROLL_ANGLE_PID_KD             3.0f
#define MOTOR_ROLL_ANGLE_PID_MAX_OUT        3000.0f
#define MOTOR_ROLL_ANGLE_PID_MAX_IOUT       100.0f

#define MOTOR_ROLL_GYRO_PID_KP              8.5f
#define MOTOR_ROLL_GYRO_PID_KI              0.7f
#define MOTOR_ROLL_GYRO_PID_KD              0.0f
#define MOTOR_ROLL_GYRO_PID_MAX_OUT         9000.0f
#define MOTOR_ROLL_GYRO_PID_MAX_IOUT        100.0f

#define MOTOR_FORWARD_SPEED_PID_KP          1.0f
#define MOTOR_FORWARD_SPEED_PID_KI          0.0f
#define MOTOR_FORWARD_SPEED_PID_KD          0.0f
#define MOTOR_FORWARD_SPEED_PID_MAX_OUT     9000.0f
#define MOTOR_FORWARD_SPEED_PID_MAX_IOUT    100.0f

#define DEAD_ZONE                           400

void balance(void);
void set_speed(int pwm1,int pwm2);

#endif /* CODE_CONTROLLER_BALANCE_H_ */
