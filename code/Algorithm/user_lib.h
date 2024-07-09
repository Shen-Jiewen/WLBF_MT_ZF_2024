/*
 * user_lib.h
 *
 *  Created on: 2024��6��11��
 *      Author: Rick
 */

#ifndef CODE_ALGORITHM_USER_LIB_H_
#define CODE_ALGORITHM_USER_LIB_H_

// ��ͨ�˲���״̬�ṹ��
typedef struct {
    float *buffer;     // �˲����Ļ�����
    int windowSize;    // ���ڴ�С
    int index;         // ��ǰ����
    float sum;         // ��ǰ���ڵĺ�
} LowPassFilter;

// ��ʼ����ͨ�˲���
void initLowPassFilter(LowPassFilter *filter, int windowSize);

// �ͷŵ�ͨ�˲�����Դ
void freeLowPassFilter(LowPassFilter *filter);

// ��ͨ�˲������������ݵ�
float processLowPassFilter(LowPassFilter *filter, float input);

#endif /* CODE_ALGORITHM_USER_LIB_H_ */
