/*
 * beep.c
 *
 *  Created on: 2024��7��8��
 *      Author: Rick
 */

#include "beep.h"

void beep_on(void){
    //����������
    gpio_set_level(P33_10,1);
}

void beep_off(void){
    //�رշ�����
    gpio_set_level(P33_10,0);
}

