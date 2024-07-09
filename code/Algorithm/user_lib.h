/*
 * user_lib.h
 *
 *  Created on: 2024年6月11日
 *      Author: Rick
 */

#ifndef CODE_ALGORITHM_USER_LIB_H_
#define CODE_ALGORITHM_USER_LIB_H_

// 低通滤波器状态结构体
typedef struct {
    float *buffer;     // 滤波器的缓冲区
    int windowSize;    // 窗口大小
    int index;         // 当前索引
    float sum;         // 当前窗口的和
} LowPassFilter;

// 初始化低通滤波器
void initLowPassFilter(LowPassFilter *filter, int windowSize);

// 释放低通滤波器资源
void freeLowPassFilter(LowPassFilter *filter);

// 低通滤波器处理单个数据点
float processLowPassFilter(LowPassFilter *filter, float input);

#endif /* CODE_ALGORITHM_USER_LIB_H_ */
