/*
 * user_key.c
 *
 *  Created on: 2024年3月19日
 *      Author: Rick
 */

#include "user_key.h"

extern Status_car status_car;
extern Menu menu;

extern int g_mutexFlagBit;

//extern FusionEuler euler;

extern int turn_over_flag;

// 定义按键对应的GPIO引脚数组
const int button_gpio[NUM_BUTTONS] = {
    P20_6, //按键1
    P20_7, //按键2
    P11_2, //按键3
    P11_3, //按键4
};

void KEY_Init(void)
{
    //拨码开关
    gpio_init(P33_11,GPI,0,GPI_FLOATING_IN);
    gpio_init(P33_12,GPI,0,GPI_FLOATING_IN);

    //四个独立按键
    gpio_init(P20_6,GPI,0,GPI_FLOATING_IN);
    gpio_init(P20_7,GPI,0,GPI_FLOATING_IN);
    gpio_init(P11_2,GPI,0,GPI_FLOATING_IN);
    gpio_init(P11_3,GPI,0,GPI_FLOATING_IN);
}

// 模拟函数：检测按键是否按下
int is_button_pressed(int gpio_pin) {
    // 模拟实际情况，假设按键连接到GPIO引脚上
    return REVERSE_BIT(gpio_get_level((gpio_pin_enum)gpio_pin));
}

// 检测按键状态的函数
void key_scan(Button *buttons) {
    // 遍历按键数组中的每个按键
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        // 获取当前按键对应的GPIO引脚
        int current_gpio = button_gpio[i];

        // 如果按键被按下
        if (is_button_pressed(current_gpio)) {
            // 如果按键之前未被按下
            if (!buttons[i].pressed) {
                buttons[i].pressed = true;  // 标记按键被按下
                buttons[i].press_count++;   // 增加按下次数
                // 如果按下次数达到长按阈值
                if (buttons[i].press_count >= LONG_PRESS_THRESHOLD) {
                    buttons[i].state = BUTTON_LONG_PRESSED; // 标记为长按状态
                }
            }
        } else { // 如果按键未被按下
            // 如果按键之前被按下
            if (buttons[i].pressed) {
                buttons[i].pressed = false; // 标记按键未被按下
                // 如果按下次数未达到长按阈值
                if (buttons[i].press_count < LONG_PRESS_THRESHOLD) {
                    buttons[i].state = BUTTON_SHORT_PRESSED; // 标记为短按状态
                }
                buttons[i].press_count = 0; // 重置按下次数
            }else { // 如果按键未被按下且之前也未被按下
                // 如果按键状态不是空闲状态，则将其重置为空闲状态
                if (buttons[i].state != BUTTON_IDLE) {
                    buttons[i].state = BUTTON_IDLE;
                }
            }
        }
    }
}

void switch_state(Button *buttons){
    //确定
    if(buttons[0].state == BUTTON_SHORT_PRESSED){
        if(menu.current_page == 0 && menu.current_param == 0){
            g_mutexFlagBit = REVERSE_BIT(g_mutexFlagBit);
        }
        else{
            //翻车标志位置0
            turn_over_flag = 0;
            //置位发车标志
            status_car = turn;
        }
    }
    //向右翻页
    if(buttons[1].state == BUTTON_SHORT_PRESSED){
        menu.current_param = 0;
        menu.current_page ++;
        if(menu.current_page > menu.total_pages - 1){
            menu.current_page = 0;
        }
    }
    //向下切换参数
    if(buttons[2].state == BUTTON_SHORT_PRESSED){
        menu.current_param ++;
        if(menu.current_param > menu.params_per_page - 1){
            menu.current_param = 0;
        }
    }

    //修改参数
    if(buttons[3].state == BUTTON_SHORT_PRESSED){
        //增加参数
        if(gpio_get_level(P33_11) == 0){
            *menu.params[menu.current_page][menu.current_param].para +=
                    menu.params[menu.current_page][menu.current_param].add_value_1;
        }
        //减小参数
        else if(gpio_get_level(P33_11) == 1){
            *menu.params[menu.current_page][menu.current_param].para +=
                               menu.params[menu.current_page][menu.current_param].reduce_value_1;
        }
    }
}


