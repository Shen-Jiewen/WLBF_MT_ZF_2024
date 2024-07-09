/*
 * balance.h
 *
 *  Created on: 2024年3月16日
 *      Author: Rick
 */

#ifndef CODE_CONTROLLER_BALANCE_H_
#define CODE_CONTROLLER_BALANCE_H_
#include "zf_common_headfile.h"

typedef enum {
    idle = 0,       //0:空闲-原地直立
    turn,           //1:速度转换
    run,            //2:正常循迹
    action,         //3.执行固定动作
}Status_car;

// 定义宏MIN和MAX，用于获取最小值和最大值
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// 定义宏LIMIT，用于限制变量x的取值范围在[min, max]之间
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
