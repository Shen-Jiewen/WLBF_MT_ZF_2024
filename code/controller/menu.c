/*
 * menu.c
 *
 *  Created on: 2024年3月16日
 *      Author: Rick
 */
#include "menu.h"

//extern pid_type_def yaw_angle_pid;
extern pid_type_def yaw_gyro_pid;
extern pid_type_def roll_angle_pid;
extern pid_type_def roll_gyro_pid;
extern pid_type_def forward_speed_pid;

extern FusionEuler euler;
extern int watch_count;
extern float forward_speed;
extern float side_speed;

//extern fp32 INS_angle[3];      //euler angle, unit rad.欧拉角 单位 rad

// 初始化菜单
void menu_init(Menu *menu, int total_pages, int params_per_page) {
    menu->total_pages = total_pages;
    menu->params_per_page = params_per_page;
    menu->current_page = 0;
    menu->current_param = 0;

    // 为参数数组分配内存
    for (int i = 0; i < total_pages; ++i) {
        for (int j = 0; j < params_per_page; ++j) {
            menu->params[i][j].para = malloc(sizeof(float));
            *(menu->params[i][j].para) = 0.0f; // 将参数初始化为0
            menu->params[i][j].add_value_1 = 0.0f;
            menu->params[i][j].reduce_value_1 = 0.0f;
            menu->params[i][j].add_value_2 = 0.0f;
            menu->params[i][j].reduce_value_2 = 0.0f;
        }
    }
}

// 修改参数值
void modify_param(Menu *menu, int page, int param, fp32 *value,const fp32 add_reduce_values[4]) {
    if (page >= 0 && page < menu->total_pages && param >= 0 && param < menu->params_per_page) {
        menu->params[page][param].para = value;
        menu->params[page][param].add_value_1 = add_reduce_values[0];
        menu->params[page][param].reduce_value_1 = add_reduce_values[1];
        menu->params[page][param].add_value_2 = add_reduce_values[2];
        menu->params[page][param].reduce_value_2 = add_reduce_values[3];
    }
}

void menu_show(Menu *menu){
    static int last_page = 0;
    if(last_page != menu->current_page){
        tft180_clear();
    }
    last_page = menu->current_page;
    switch(menu->current_page){
        case 0:
//            //显示五向按键的数据
//            tft180_show_int(ROW_OFFSET(1), COLUMN_OFFSET(0), gpio_get_level(P13_1), 1);//上按键
//            tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(1), gpio_get_level(P13_0), 1);//左按键
//            tft180_show_int(ROW_OFFSET(1), COLUMN_OFFSET(1), gpio_get_level(P13_2), 1);//中按键
//            tft180_show_int(ROW_OFFSET(2), COLUMN_OFFSET(1), gpio_get_level(P13_3), 1);//右按键
//            tft180_show_int(ROW_OFFSET(1), COLUMN_OFFSET(2), gpio_get_level(P11_2), 1);//下按键
//
//            //显示四个独立按键的数据
//            tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(4), gpio_get_level(P11_9), 1);//按键1
//            tft180_show_int(ROW_OFFSET(1), COLUMN_OFFSET(4), gpio_get_level(P11_10), 1);//按键2
//            tft180_show_int(ROW_OFFSET(2), COLUMN_OFFSET(4), gpio_get_level(P11_11), 1);//按键3
//            tft180_show_int(ROW_OFFSET(3), COLUMN_OFFSET(4), gpio_get_level(P11_12), 1);//按键4

            //显示左右编码器数据
            tft180_show_float(ROW_OFFSET(0), COLUMN_OFFSET(5), forward_speed, 4, 1);//前进轮编码器
            tft180_show_float(ROW_OFFSET(0), COLUMN_OFFSET(6), side_speed, 4, 1);//左右轮编码器

            //显示手动编码器
//            tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(7), encoder_get_count(TIM6_ENCODER), 6);//手动编码器计数

            //显示姿态角度
            tft180_show_float(ROW_OFFSET(6), COLUMN_OFFSET(4), euler.angle.pitch, 3, 3);
            tft180_show_float(ROW_OFFSET(6), COLUMN_OFFSET(5), euler.angle.yaw, 3, 3);
            tft180_show_float(ROW_OFFSET(6), COLUMN_OFFSET(6), euler.angle.roll, 3, 3);

            //显示定时器计数
            tft180_show_float(ROW_OFFSET(6), COLUMN_OFFSET(7), watch_count * 1.0, 2, 3);
            break;
        case 1:
            // yaw_angle_pid
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(0), "yaw_angle:");
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(1), "kp:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(1), *menu->params[1][0].para, 1, 4);//yaw_angle_pid_kp
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(2), "ki:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(2), *menu->params[1][1].para, 1, 4);//yaw_angle_pid_ki
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(3), "kd:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(3), *menu->params[1][2].para, 1, 4);//yaw_angle_pid_kd

            // yaw_gyro_pid
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(4), "yaw_gyro:");
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(5), "kp:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(5), *menu->params[1][3].para, 1, 4);//yaw_gyro_pid_kp
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(6), "ki:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(6), *menu->params[1][4].para, 1, 4);//yaw_gyro_pid_ki
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(7), "kd:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(7), *menu->params[1][5].para, 1, 4);//yaw_gyro_pid_kd

            // roll_angle_pid
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "roll_ang:");
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(9), "kp:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(9), *menu->params[1][6].para, 1, 3);//roll_angle_pid_kp
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(10), "ki:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(10), *menu->params[1][7].para, 1, 3);//roll_angle_pid_kp
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(11), "kd:");
            tft180_show_float(ROW_OFFSET(1) + 23, COLUMN_OFFSET(11), *menu->params[1][8].para, 1, 3);//roll_angle_pid_kp

            // roll_gyro_pid
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(0), "roll_gyro:");
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(1), "kp:");
            tft180_show_float(ROW_OFFSET(10) + 23, COLUMN_OFFSET(1), *menu->params[1][9].para, 3, 2);//roll_gyro_pid_kp
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(2), "ki:");
            tft180_show_float(ROW_OFFSET(10) + 23, COLUMN_OFFSET(2), *menu->params[1][10].para, 3, 2);//roll_gyro_pid_kp
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(3), "kd:");
            tft180_show_float(ROW_OFFSET(10) + 23, COLUMN_OFFSET(3), *menu->params[1][11].para, 3, 2);//roll_gyro_pid_kp

            // forward_speed_pid
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(4), "fw_speed:");
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(5), "kp:");
            tft180_show_float(ROW_OFFSET(10) + 23, COLUMN_OFFSET(5), *menu->params[1][12].para, 2, 3);//forward_speed_pid_kp
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(6), "ki:");
            tft180_show_float(ROW_OFFSET(10) + 23, COLUMN_OFFSET(6), *menu->params[1][13].para, 2, 3);//forward_speed_pid_kp
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(7), "kd:");
            tft180_show_float(ROW_OFFSET(10) + 23, COLUMN_OFFSET(7), *menu->params[1][14].para, 2, 3);//forward_speed_pid_kp

            // 显示参数位置
            tft180_show_string(ROW_OFFSET(10), COLUMN_OFFSET(12), "index:");
            tft180_show_int(ROW_OFFSET(16), COLUMN_OFFSET(12), menu->current_param, 2); // 当前参数位置
            break;
        case 2:
            // 显示 PID 输出
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(0), "pid_out:");
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(1), "yg:");
            tft180_show_int(ROW_OFFSET(1) + 23, COLUMN_OFFSET(1), yaw_gyro_pid.out, 5);
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(2), "ra:");
            tft180_show_int(ROW_OFFSET(1) + 23, COLUMN_OFFSET(2), roll_angle_pid.out, 5);
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(3), "rg:");
            tft180_show_int(ROW_OFFSET(1) + 23, COLUMN_OFFSET(3), roll_gyro_pid.out, 5);
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(4), "fs:");
            tft180_show_int(ROW_OFFSET(1) + 23, COLUMN_OFFSET(4), forward_speed_pid.out, 5);

            // 显示零角度和当前参数位置
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(5), "roll_zero_angle:");
            tft180_show_float(ROW_OFFSET(0), COLUMN_OFFSET(6), *menu->params[2][0].para, 2, 3);
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(7), "yaw_gyro_set:");
            tft180_show_float(ROW_OFFSET(0), COLUMN_OFFSET(8), *menu->params[2][1].para, 2, 3);
            tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(9), "watch_param1:");
            tft180_show_float(ROW_OFFSET(0), COLUMN_OFFSET(10), *menu->params[2][2].para, 3, 2);
            tft180_show_string(ROW_OFFSET(8), COLUMN_OFFSET(15), "index:");
            tft180_show_int(ROW_OFFSET(14), COLUMN_OFFSET(15), menu->current_param, 2); // 当前参数位置
            break;
        default:
            //页数报错就清屏
            tft180_clear();
            break;
    }
}
