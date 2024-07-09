/*
 * user_lib.c
 *
 *  Created on: 2024年6月11日
 *      Author: Rick
 */
#include "user_lib.h"
#include <stdlib.h>

// 初始化低通滤波器
void initLowPassFilter(LowPassFilter *filter, int windowSize) {
    filter->buffer = (float *)malloc(windowSize * sizeof(float));
    filter->windowSize = windowSize;
    filter->index = 0;
    filter->sum = 0.0;

    // 初始化缓冲区
    for (int i = 0; i < windowSize; i++) {
        filter->buffer[i] = 0.0;
    }
}

// 释放低通滤波器资源
void freeLowPassFilter(LowPassFilter *filter) {
    free(filter->buffer);
}

// 低通滤波器处理单个数据点
float processLowPassFilter(LowPassFilter *filter, float input) {
    // 从和中减去最旧的数据点
    filter->sum -= filter->buffer[filter->index];
    // 更新缓冲区和和
    filter->buffer[filter->index] = input;
    filter->sum += input;

    // 更新索引
    filter->index = (filter->index + 1) % filter->windowSize;

    // 返回当前窗口的平均值
    return filter->sum / filter->windowSize;
}
