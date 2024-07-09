/*
 * user_key.c
 *
 *  Created on: 2024��3��19��
 *      Author: Rick
 */

#include "user_key.h"

extern Status_car status_car;
extern Menu menu;

extern int g_mutexFlagBit;

//extern FusionEuler euler;

extern int turn_over_flag;

// ���尴����Ӧ��GPIO��������
const int button_gpio[NUM_BUTTONS] = {
    P20_6, //����1
    P20_7, //����2
    P11_2, //����3
    P11_3, //����4
};

void KEY_Init(void)
{
    //���뿪��
    gpio_init(P33_11,GPI,0,GPI_FLOATING_IN);
    gpio_init(P33_12,GPI,0,GPI_FLOATING_IN);

    //�ĸ���������
    gpio_init(P20_6,GPI,0,GPI_FLOATING_IN);
    gpio_init(P20_7,GPI,0,GPI_FLOATING_IN);
    gpio_init(P11_2,GPI,0,GPI_FLOATING_IN);
    gpio_init(P11_3,GPI,0,GPI_FLOATING_IN);
}

// ģ�⺯������ⰴ���Ƿ���
int is_button_pressed(int gpio_pin) {
    // ģ��ʵ����������谴�����ӵ�GPIO������
    return REVERSE_BIT(gpio_get_level((gpio_pin_enum)gpio_pin));
}

// ��ⰴ��״̬�ĺ���
void key_scan(Button *buttons) {
    // �������������е�ÿ������
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        // ��ȡ��ǰ������Ӧ��GPIO����
        int current_gpio = button_gpio[i];

        // �������������
        if (is_button_pressed(current_gpio)) {
            // �������֮ǰδ������
            if (!buttons[i].pressed) {
                buttons[i].pressed = true;  // ��ǰ���������
                buttons[i].press_count++;   // ���Ӱ��´���
                // ������´����ﵽ������ֵ
                if (buttons[i].press_count >= LONG_PRESS_THRESHOLD) {
                    buttons[i].state = BUTTON_LONG_PRESSED; // ���Ϊ����״̬
                }
            }
        } else { // �������δ������
            // �������֮ǰ������
            if (buttons[i].pressed) {
                buttons[i].pressed = false; // ��ǰ���δ������
                // ������´���δ�ﵽ������ֵ
                if (buttons[i].press_count < LONG_PRESS_THRESHOLD) {
                    buttons[i].state = BUTTON_SHORT_PRESSED; // ���Ϊ�̰�״̬
                }
                buttons[i].press_count = 0; // ���ð��´���
            }else { // �������δ��������֮ǰҲδ������
                // �������״̬���ǿ���״̬����������Ϊ����״̬
                if (buttons[i].state != BUTTON_IDLE) {
                    buttons[i].state = BUTTON_IDLE;
                }
            }
        }
    }
}

void switch_state(Button *buttons){
    //ȷ��
    if(buttons[0].state == BUTTON_SHORT_PRESSED){
        if(menu.current_page == 0 && menu.current_param == 0){
            g_mutexFlagBit = REVERSE_BIT(g_mutexFlagBit);
        }
        else{
            //������־λ��0
            turn_over_flag = 0;
            //��λ������־
            status_car = turn;
        }
    }
    //���ҷ�ҳ
    if(buttons[1].state == BUTTON_SHORT_PRESSED){
        menu.current_param = 0;
        menu.current_page ++;
        if(menu.current_page > menu.total_pages - 1){
            menu.current_page = 0;
        }
    }
    //�����л�����
    if(buttons[2].state == BUTTON_SHORT_PRESSED){
        menu.current_param ++;
        if(menu.current_param > menu.params_per_page - 1){
            menu.current_param = 0;
        }
    }

    //�޸Ĳ���
    if(buttons[3].state == BUTTON_SHORT_PRESSED){
        //���Ӳ���
        if(gpio_get_level(P33_11) == 0){
            *menu.params[menu.current_page][menu.current_param].para +=
                    menu.params[menu.current_page][menu.current_param].add_value_1;
        }
        //��С����
        else if(gpio_get_level(P33_11) == 1){
            *menu.params[menu.current_page][menu.current_param].para +=
                               menu.params[menu.current_page][menu.current_param].reduce_value_1;
        }
    }
}


