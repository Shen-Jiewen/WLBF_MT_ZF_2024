/*
 * ImgProcess.h
 *
 *  Created on: 2021��3��29��
 *      Author: ��ԭ�
 */

#ifndef CODE_CAMERA_IMGPROCESS_H_
#define CODE_CAMERA_IMGPROCESS_H_
#include "zf_common_headfile.h"

#define IMG_H MT9V03X_H        // ͼ���
#define IMG_W MT9V03X_W        //ͼ���

#define left_inf1_color 0xFD20 //��ɫ
#define left_inf2_color 0xAEDC //����ɫ
#define right_inf1_color 0x8010 //������ɫ
#define right_inf2_color 0xFEA0 //��ɫ
#define left_arcinf_color 0xC618 //��ɫ
#define right_arcinf_color 0xF7BB //��ɫ

/*��������*/
#define _c 1760
#define _c1 1865
#define _d 1975
#define _d1 2093
#define _e 2217
#define _f 2349
#define _f1 2489
#define _g 2637
#define _g1 2793
#define _a 2960
#define _a1 3135
#define _b 3322
#define Border_Threshold 40

#define First_Patch 96      //���еĲ��߳���
#define Garage_Patch 142

#define data_lenth 5        //���ݰ�����
extern uint8 Data_Package[data_lenth];

/*ͼ������ṹ��*/
typedef struct Param
{
    /*����Ѱ��*/
    int mid_line[IMG_H];      //����
    int left_line[IMG_H];     //��߽���
    int right_line[IMG_H];        //�ұ߽���
    int up_border[IMG_W];       //�ϱ߽���
    int long_line;      //�������
    int left_border;       //��߽�
    int right_border;     //�ұ߽�
    int road_start;       //��Ч��ʼ��
    int road_end;       //��Ч������
    int error;     //ѭ��ƫ��
    int garage_count;      //�����������
    int zebracrossing_count;    //�����߼���
    int fork_count;     //����·����

    /*ֱ���ʶ��*/
    float left_slope;        //��߽�б��
    float right_slope;      //�ұ߽�б��
    int left_lose1;        //��߽���ж�����
    int left_lose2;     //��߽���ж�����
    int left_outliers;      //��߽����������ĵ����
    int right_lose1;     //�ұ߽���ж�����
    int right_lose2;        //�ұ߽���ж�����
    int right_outliers;      //�ұ߽����������ĵ����

    /*�յ�Ѱ��*/
    int left_inf1;      //����ֱ�ǹյ�
    int left_inf2;        //����ֱ�ǹյ�
    int left_arcinf;      //��Բ���յ㣨������
    int left_sinf;      //��С�յ㣨����
    int right_inf1;     //����ֱ�ǹյ�
    int right_inf2;       //����ֱ�ǹյ�
    int right_arcinf;     //�ҷ�Բ���յ㣨������
    int right_sinf;     //�ҷ�С�յ㣨����


    /*��־λ*/
    int flag;     //�ܱ�־λ
    int zebracrossing_flag;     //�����߱�־λ
    int stop_flag;      //ͣ����־λ
    int curve_flag;       //�����־λ
    int ramp_flag;      //�µ���־λ
    int cross_flag;        //ʮ��·��־λ
    int round_flag;      //������־λ
    int fork_flag;        //����·��־λ
    int garage_flag;        //�����־λ
    int direct_flag;     //��ʻ�����־λ��0��ʾ�����ߣ�1��ʾ������
    int displaly_flag;      //��ʾ��־λ��������

    /*���ֲ���*/

    int debug_mode;
    uint32 black_threshold;
    uint32 short_gain;      //��ֱ���ٶ�����
    uint32 long_gain;       //��ֱ���ٶ�����
    uint32 fork_freq;

} Img_Param;


void param_init(Img_Param *prm);     //ͼ������ṹ���ʼ��
void find_startline(uint8 Img[IMG_H][IMG_W], Img_Param *prm); // @suppress("Symbol is not resolved")
void find_upborder(uint8 Img[IMG_H][IMG_W], Img_Param *prm);
void find_zebracrossing (Img_Param *prm);
void find_border(uint8 Img[IMG_H][IMG_W] , Img_Param *prm);        //�����߽� // @suppress("Symbol is not resolved")
void analysis_border(Img_Param *prm);       //�����߽�
void analysis_garage (Img_Param *prm);
void analysis_fork (Img_Param *prm);
void analysis_round (Img_Param *prm);
void judge_road(Img_Param *prm);        //�ж�·��
void correct_misjudgment(Img_Param *prm);     //��������
void patch_line(Img_Param *prm);        //���߲���
void analysis_border_prossed(Img_Param *prm);       //���������ı߽�
void analysis_midline(Img_Param *prm);      //��������
int henghengheng_aaaaa_aaaaaaaaaaa (Img_Param *prm);       //�������
void display_param(Img_Param *prm);     //��ʾ����
void display_grey(uint8 *p, Img_Param *prm);
void draw_point(uint16 x, uint16 y, const uint16 color);
void binarize_image(uint8_t image[IMG_H][IMG_W], uint8_t threshold);

#endif
