/*
 * user_lib.c
 *
 *  Created on: 2024��6��11��
 *      Author: Rick
 */
#include "user_lib.h"
#include <stdlib.h>

// ��ʼ����ͨ�˲���
void initLowPassFilter(LowPassFilter *filter, int windowSize) {
    filter->buffer = (float *)malloc(windowSize * sizeof(float));
    filter->windowSize = windowSize;
    filter->index = 0;
    filter->sum = 0.0;

    // ��ʼ��������
    for (int i = 0; i < windowSize; i++) {
        filter->buffer[i] = 0.0;
    }
}

// �ͷŵ�ͨ�˲�����Դ
void freeLowPassFilter(LowPassFilter *filter) {
    free(filter->buffer);
}

// ��ͨ�˲������������ݵ�
float processLowPassFilter(LowPassFilter *filter, float input) {
    // �Ӻ��м�ȥ��ɵ����ݵ�
    filter->sum -= filter->buffer[filter->index];
    // ���»������ͺ�
    filter->buffer[filter->index] = input;
    filter->sum += input;

    // ��������
    filter->index = (filter->index + 1) % filter->windowSize;

    // ���ص�ǰ���ڵ�ƽ��ֵ
    return filter->sum / filter->windowSize;
}
