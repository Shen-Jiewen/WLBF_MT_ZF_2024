/*
 * user_key.h
 *
 *  Created on: 2024年3月19日
 *      Author: Rick
 */

#ifndef CODE_CONTROLLER_USER_KEY_H_
#define CODE_CONTROLLER_USER_KEY_H_

#include "zf_common_headfile.h"

#define REVERSE_BIT(x) ((x) ^ 1)

#define NUM_BUTTONS 9
#define LONG_PRESS_THRESHOLD 100 // 次数为单位

typedef enum {
    BUTTON_IDLE,
    BUTTON_SHORT_PRESSED,
    BUTTON_LONG_PRESSED,
} ButtonState;

typedef struct {
    bool pressed;
    int press_count;
    ButtonState state;
} Button;

void KEY_Init(void);
void key_scan(Button *buttons);
void switch_state(Button *buttons);

#endif /* CODE_CONTROLLER_USER_KEY_H_ */
