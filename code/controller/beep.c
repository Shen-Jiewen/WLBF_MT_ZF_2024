/*
 * beep.c
 *
 *  Created on: 2024年7月8日
 *      Author: Rick
 */

#include "beep.h"

void beep_on(void){
    //开启蜂鸣器
    gpio_set_level(P33_10,1);
}

void beep_off(void){
    //关闭蜂鸣器
    gpio_set_level(P33_10,0);
}

