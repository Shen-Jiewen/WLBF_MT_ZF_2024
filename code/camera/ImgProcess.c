/*
 *  ImgProcess.c     ͼ������
 *
 *  Created on     2021��3��29��   �ܹ�ɨ��߽粢�ó�ƫ��ѭ��
 *  version:    4��4��    ���ӱ߽�б�ʼ��㣬��ʶ��ֱ���
 *  version:    4��11��   ���ӹյ��������ܳ���ʶ��ʮ��·
 *  version:    4��13��   ���ӻ���״̬�����ܳ������껷��
 *  version:    4��20��   ���Ӱ�����ɨ�裬Ч����̫����
 *  version:    4��29��   ���ûҶ�����ͷ�Ķ�ֵ������
 *  version:    5��4��    ��������·״̬�����ܳ���������·�л��н�����
 *  version:    6��6��    ���ûҶ�ͼֱ�Ӵ���ķ���
 *  version:    6��9��    �Ż��˻���״̬��������
 *  version:    6��20��   �������
 *  version:    6��25��   ���ȫԪ�أ�ͬʱ�����һЩ����
 *  version:    7��1��    ����״̬����
 *  version:    7��16��   ����˲������У��Ż�������·�ͳ���״̬��
 *  Author:     ��ԭ�         QQ:     398817314
 */

#include "ImgProcess.h"

uint8 Data_Package[data_lenth] = {4, 4, 4, 4, 4};

Img_Param prm;      //ͼ������ṹ��

//-------------------------------------------------------------------------------------------------------------------
// �������     ����
// ����˵��     x               ����x�������� ������Χ [0, width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, height_max-1]
// ����˵��     dat             ��Ҫ��ʾ����ɫ
// ���ز���     void
// ʹ��ʾ��     draw_point(0, 0, RGB565_RED);            // ���� 0,0 ��һ����ɫ�ĵ�
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void draw_point(uint16 x, uint16 y, const uint16 color){
    //����Լ���Ļ��ʵ�ֺ���
    tft180_draw_point((uint16)x / 2, (uint16)y / 2,color);
}

//��ֵ��ͼ��
void binarize_image(uint8_t image[IMG_H][IMG_W], uint8_t threshold) {
    for (int i = 0; i < IMG_H; i++) {
        for (int j = 0; j < IMG_W; j++) {
            if (image[i][j] >= threshold) {
                image[i][j] = 255;
            } else {
                image[i][j] = 0;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ͼ������ṹ���ʼ����ֻ���ʼ��ʼ��������
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��3��29��
//  Sample usage:               pram_init(&prm);
//-------------------------------------------------------------------------------------------------------------------
void param_init(Img_Param *prm)
{
    prm->error = 0;
    prm->left_slope = 0.0;
    prm->right_slope = 0.0;
    /*��ʼ��״̬����־λ*/
    prm->round_flag = 0;
    prm->garage_count = 0;
    prm->zebracrossing_flag = 0;
    prm->garage_flag = 0;
    prm->fork_flag = 0;
    prm->displaly_flag = 0;
    prm->direct_flag = 0;
    prm->debug_mode = 0;
    prm->fork_freq = 1;
    prm->fork_count = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ɨ��ǰ���ò��ֱ�־λ������ʮ��·������������йյ�
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��4��18��
//  Sample usage:               clean_flag(&prm);
//-------------------------------------------------------------------------------------------------------------------
void clean_flag(Img_Param *prm)
{
    prm->left_lose1 = 0;
    prm->left_lose2 = 0;
    prm->left_outliers = 0;
    prm->right_lose1 = 0;
    prm->right_lose2 = 0;
    prm->right_outliers = 0;
    prm->zebracrossing_count = 0;
    /*����յ�*/
    prm->left_inf1 = 0;
    prm->left_inf2 = 0;
    prm->left_arcinf = 0;
    prm->left_sinf = 0;
    prm->right_inf1 = 0;
    prm->right_inf2 = 0;
    prm->right_arcinf = 0;
    prm->right_sinf = 0;
    /*�����״̬����·����־λ*/
    prm->cross_flag = 0;
    prm->ramp_flag  = 0;
    prm->flag =  prm->direct_flag << 3;        //�����н�����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��x�ľ���ֵ���Ҷ�ͼ�������
//  @param      x
//  @return     x�ľ���ֵ
//  @creation date       2021��6��6��
//  Sample usage:               grey_abs(x);
//-------------------------------------------------------------------------------------------------------------------
int abs_(int x)
{
    return x > 0 ? x : -x;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ʼ��(ֱ�Ӵ���Ҷ�ͼ)������ȷ�������ް����߸��ţ�ͬʱ����Ƿ������
//  @param      Img     ͼ������
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��6��6��
//  Sample usage:               find_startline_grey(Img,&prm);
//-------------------------------------------------------------------------------------------------------------------
void find_startline(uint8 Img[IMG_H][IMG_W], Img_Param *prm)
{
    clean_flag(prm);
    int h = IMG_H - 1, w;     //��������
    int cmp_x, cmp_y, cmp_xy1, cmp_xy2, sum_x, sum_cmp, threshold;
    int mid = IMG_W / 2;
    do
    {
        h--;
        for (w = mid, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w > 0; w--)     //������߽�
        {
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //���Ҳ�
            if (cmp_x < 10) continue;       //���Ҳ�̫С��ֱ������
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //���²�
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //�������ϲ�
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //�������ϲ�
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //�������Һ�
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //��ֵ��
            threshold = (sum_x >> 2) - Border_Threshold;        //��ֵ
        }
        prm->left_line[h] = w;      //��߽縳ֵ
        for (w = mid, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w < IMG_W - 1; w++)     //������߽�
        {
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //���Ҳ�
            if (cmp_x < 10) continue;       //���Ҳ�̫С��ֱ������
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //���²�
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //���������ϲ�
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //���������ϲ�
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //�������Һ�
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //��ֵ��
            threshold = (sum_x >> 2) - Border_Threshold;        //��ֵ
        }
        prm->right_line[h] = w;     //�ұ߽縳ֵ
    } while ((prm->right_line[h] - prm->left_line[h] < 30 || Img[h][mid] <= prm->black_threshold) && h > IMG_H - 20);        //�ж��Ƿ�Ϊ��ȷ����ʼ�У�����15�����ʾ������
    prm->road_start = h ;       //��ʼ�и�ֵ
    prm->left_border = prm->left_line[h] + 3;       //�����Ч��߽�
    prm->right_border = prm->right_line[h] - 3;     //�����Ч�ұ߽�
    if (Img[prm->road_start][(prm->left_border + prm->right_border) / 2] <= prm->black_threshold)     //ͣ�����
        prm->stop_flag = 1;
    else prm->stop_flag = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ϱ߽�(ֱ�Ӵ���Ҷ�ͼ)��ȷ���ɨ����
//  @param      Img     ͼ������
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��6��7��
//  Sample usage:               find_startline(Img,&prm);
//-------------------------------------------------------------------------------------------------------------------
void find_upborder(uint8 Img[IMG_H][IMG_W], Img_Param *prm)
{
    int h, w ,longest = prm->road_start;
    int cmp_x, cmp_y, cmp_xy1, cmp_xy2, sum_x, sum_cmp, threshold;
    for (w = prm->left_border; w < prm->right_border; w++)      //�����ϱ߽�
    {
        for (h = prm->road_start - 2, sum_cmp = 0, threshold = 1; sum_cmp < threshold && h > 0 &&  Img[h][w] >= prm->black_threshold; h--)
        {
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //���²�
            if (cmp_y < 10) continue;       //���²�̫С��ֱ������
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //���Ҳ�
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //���������ϲ�
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //���������ϲ�
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //�������Һ�
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //��ֵ��
            threshold = (sum_x >> 2) - Border_Threshold;        //��ֵ
        }
        prm->up_border[w] = h;        //�ϱ߽縳ֵ
    }
        for(w = prm->left_border + 1; w <= prm->right_border - 1; w++)      //�������
        {
            if (prm->up_border[w] < longest && prm->up_border[w] - prm->up_border[w - 1] < 5 && prm->up_border[w] - prm->up_border[w + 1] < 5)
            {
                longest = prm->up_border[w];
                prm->long_line = w;
            }
        }
}

void find_zebracrossing (Img_Param *prm)
{
    int w;
    for (w = prm->left_border + 5; w + 5 <=prm->right_border; w++)        //����������
    {
        if (prm->up_border[w - 1] - prm->up_border[w + 1] > 10)
            prm->zebracrossing_count ++;
    }
    if (prm->zebracrossing_count > 9)
    {
        if (prm->garage_count && (prm->fork_count == prm->fork_freq << 2 || prm->debug_mode))
            prm->zebracrossing_flag = 2;
        else if (prm->fork_count == prm->fork_freq << 1 || prm->debug_mode)
            prm->zebracrossing_flag = 1;
//        prm->displaly_flag = 1;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����߽纯��
//  @param      Img     ͼ������
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��6��7��
//  Sample usage:               find_border(Img,&prm);
//-------------------------------------------------------------------------------------------------------------------
void find_border(uint8 Img[IMG_H][IMG_W], Img_Param *prm)
{
    int h = prm->road_start - 1, w, mid;
    int cmp_x, cmp_y, cmp_xy1, cmp_xy2, sum_x, sum_cmp, threshold;
    int left_weight = 1, right_weight = 1, total = 1;
    if (prm->round_flag == 3 || prm->round_flag == 5 || prm->garage_flag ==1 || prm->garage_flag ==3 || prm->fork_flag == 1 || prm->fork_flag == 3)        //���󻷵����������󳵿�ʱ���ڲ�����
    {
        left_weight = 3;
        right_weight = 1;
        total = 2;
    }
    else if (prm->round_flag == 4 || prm->round_flag == 6 || prm->garage_flag == 2 || prm->garage_flag ==4 || prm->fork_flag == 2 || prm->fork_flag == 4)        //���һ������������ҳ���ʱ���ڲ�����
    {
        left_weight = 1;
        right_weight = 3;
        total = 2;
    }
    else    //�����Ϊ��������
    {
        while (h > prm->up_border[prm->long_line] + 3 && Img[h][prm->long_line] >= prm->black_threshold)
        {
            for (w = prm->long_line - 1, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w > 0; w--)     //������߽�
            {
                cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //���Ҳ�
                if (cmp_x < 10)     continue;       //���Ҳ�̫С��ֱ������
                cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //���²�
                cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //�������ϲ�
                cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //�������ϲ�
                sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //�������Һ�
                sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //��ֵ��
                threshold = (sum_x>>2) - Border_Threshold;        //��ֵ
            }
            if(w < 4 && h >= 64)   prm->left_lose1++;       //���ж���
            else if(w < 4 && h >= 15) prm->left_lose2++;        //���ж���
            else if(h < 8 && abs_(w - prm->left_line[h + 1]) > 15)   break;        //�쳣ɨ����ֹ
            if (w < prm->left_line[h + 1])  prm->left_outliers++;
            prm->left_line[h] = w;      //��߽縳ֵ
            for (w = prm->long_line + 1, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w < IMG_W - 1; w++)     //������߽�
            {
                cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //���Ҳ�
                if (cmp_x < 10)     continue;       //���Ҳ�̫С��ֱ������
                cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //���²�
                cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //���������ϲ�
                cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //���������ϲ�
                sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //�������Һ�
                sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //��ֵ��
                threshold = (sum_x>>2) - Border_Threshold;        //��ֵ
            }
            if (w > IMG_W - 5 && h >= 64)   prm->right_lose1++;        //���ж���
            else if (w > IMG_W - 5 && h >= 15) prm->right_lose2++;     //���ж���
            else if(h < 5
                    && abs_(prm->right_line[h + 1] - w) > 15)   break;       //�쳣ɨ����ֹ
            if (w > prm->right_line[h + 1])  prm->right_outliers++;
            prm->right_line[h] = w;     //�ұ߽縳ֵ
            h--;
        }
    }
    h++;
    do
    {
        mid = ((left_weight * prm->left_line[h]) + right_weight * prm->right_line[h]) >> total;
        if (h < prm->road_start  - 10)
        {
            cmp_x = abs_(Img[h][mid + 1] - Img[h][mid - 1]) ;        //���Ҳ�
            cmp_y = abs_(Img[h + 1][mid] - Img[h - 1][mid]);      //���²�
            cmp_xy1 = abs_(Img[h + 1][mid - 1] - Img[h - 1][mid + 1]);        //���������ϲ�
            cmp_xy2 = abs_(Img[h + 1][mid + 1] - Img[h - 1][mid - 1]);        //���������ϲ�
            sum_x =  Img[h][mid + 1] + Img[h][mid - 1] + Img[h - 1][mid] + Img[h + 1][mid];     //�������Һ�
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //��ֵ��
            threshold = (sum_x >> 2) - Border_Threshold;        //��ֵ
            if (sum_cmp > threshold || Img[h][mid] < prm->black_threshold)      break;        //ֹͣɨ���ж�
        }
        h--;
        for (w = mid - 1, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w > 0; w--)     //������߽�
        {
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //���Ҳ�
            if (cmp_x < 10)     continue;       //���Ҳ�̫С��ֱ������
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //���²�
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //�������ϲ�
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //�������ϲ�
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //�������Һ�
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //��ֵ��
            threshold = (sum_x >> 2) - Border_Threshold;        //��ֵ
        }
        if(w < 4 && h >= 30)   prm->left_lose1++;
        else if(w < 4 && h >= 15) prm->left_lose2++;
        else if(h < 8 && abs_(w - prm->left_line[h + 1]) > 15)   break;        //�쳣ɨ����ֹ
        if (w < prm->left_line[h + 1] - 5)  prm->left_outliers++;
        prm->left_line[h] = w;      //��߽縳ֵ
        for (w = mid + 1, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w < IMG_W - 1; w++)     //������߽�
        {
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //���Ҳ�
            if (cmp_x < 10)     continue;       //���Ҳ�̫С��ֱ������
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //���²�
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //���������ϲ�
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //���������ϲ�
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //�������Һ�
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //��ֵ��
            threshold = (sum_x >> 2) - Border_Threshold;        //��ֵ
        }
        if (w > IMG_W - 5 && h >= 30)   prm->right_lose1++;
        else if (w > IMG_W - 5 && h >= 15) prm->right_lose2++;
        else if(h < 5 && abs_(prm->right_line[h + 1] - w) > 15)   break;       //�쳣ɨ����ֹ
        if (w > prm->right_line[h + 1] + 5)  prm->right_outliers++;
        prm->right_line[h] = w;     //�ұ߽縳ֵ
    }   while(h > 0);
    prm -> road_end = h;      //��¼������
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����߽磬Ѱ�ҹյ㣬ȷ��·��
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��4��11��
//  Sample usage:               analysis_border(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_border(Img_Param *prm)
{
    int i;
    for (i = prm->road_start;  i - 9 > prm->road_end; i--)
    {
        if (prm->left_line[i - 3] - prm->left_line[i - 6] > 12 && prm->left_line[i - 3] < IMG_W * 3 / 4 && i - 3 > prm->road_end + 25)        //������ּ���������������ж��Ƿ�Ϊ���¹յ�
        {
            if (prm->left_line[i - 3] - prm->left_line[i] < 6 && prm->left_line[i] - prm->left_line[i - 3] < 3 && prm->left_line[i - 6] < IMG_W / 5 && prm->right_line[i] - prm->left_line[i] > 30)        //�յ�ǰ�ı߽�������ȷ��Ϊֱ�ǹյ�
            {
                prm->left_inf1 = i - 3;
                break;
            }
        }
    }
    for (i = prm->road_start;  i - 9 > prm->road_end; i--)
    {
        if (prm->right_line[i - 6] - prm->right_line[i - 3] > 12 && prm->right_line[i - 3] > IMG_W / 4 && i - 3 >prm->road_end + 25)        //������ּ���������������ж��Ƿ�Ϊ���¹յ�
        {
            if (prm->right_line[i] - prm->right_line[i - 3] < 6 && prm->right_line[i - 3] - prm->right_line[i] < 3 && prm->right_line[i - 6] > IMG_W * 4 / 5 && prm->right_line[i] - prm->left_line[i] > 30)        //�յ�ǰ�ı߽�������ȷ��Ϊֱ�ǹյ�
            {
                prm->right_inf1 = i - 3;
                break;
            }
        }
    }
    for (i = (prm->left_inf1 != 0 ? prm->left_inf1 - 10 : prm->road_start);  i - 9 > prm->road_end; i--)
    {
        if (prm->left_line[i - 3] - prm->left_line[i] > 12 && prm->left_line[i - 3] < IMG_W / 2)      //������ּ���������������ж��Ƿ�Ϊ���Ϲյ�
        {
            if (prm->left_line[i - 3] - prm->left_line[i - 3] < 6 && prm->left_line[i - 3] - prm->left_line[i - 6] < 3 && prm->right_line[i - 6] - prm->left_line[i - 6] > 15)     //�յ��ı߽�������ȷ��Ϊֱ�ǹյ�
            {
                prm->left_inf2 = i - 3;
                break;
            }
        }
    }
    for (i = (prm->right_inf1 != 0 ? prm->right_inf1 - 10 : prm->road_start);  i - 9> prm->road_end; i--)
    {
        if (prm->right_line[i] - prm->right_line[i - 3] > 12 && prm->right_line[i - 3] > IMG_W / 2)        //������ּ���������������ж��Ƿ�Ϊ���Ϲյ�
        {
            if (prm->right_line[i - 3] - prm->right_line[i - 6] < 6 && prm->right_line[i - 6] - prm->right_line[i - 3] < 3 && prm->right_line[i - 6] - prm->left_line[i - 6] > 15)     //�յ��ı߽�������ȷ��Ϊֱ�ǹյ�
            {
                prm->right_inf2 = i - 3;
                break;
            }
        }
    }
    if (!prm->zebracrossing_flag)       //�ް����ߵ�������Ѱ������·��С�յ�ͻ�����Բ���յ�
    {
        if ((prm->left_inf1 > IMG_H / 3 || prm->left_lose1 > 15) && prm->road_end < 10)        //Ѱ����Բ���յ��ж��󻷵�
        {
            for (i = (prm->left_inf1 != 0 ? prm->left_inf1 - 10 : prm->road_start - 10);  i - 8 > prm->road_end; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 0 &&
                    prm->left_line[i - 3] > prm->left_line[i - 6] &&
                    prm->left_line[i - 6] > prm->left_line[i - 8] &&
                    prm->left_line[i - 6] > 0 &&
                    prm->left_line[i - 3] > IMG_W / 5 &&
                    prm->left_line[i - 3] < IMG_W * 3 / 4 &&
                    prm->right_line[i - 3] - prm->left_line[i - 3] > 20) {
                        prm->left_arcinf = i - 3;
                        break;
                }
            }
        }
        if ((prm->right_inf1 > IMG_W / 3 || prm->right_lose1 > 15) && prm->road_end < 10)        //Ѱ����Բ���յ��ж��һ���
        {
            for (i = (prm->right_inf1 != 0 ? prm->right_inf1 - 10 : prm->road_start - 10);  i - 8 > prm->road_end; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 0 &&
                    prm->right_line[i - 6] - prm->right_line[i - 3] > 0 &&
                    prm->right_line[i - 8] - prm->right_line[i - 6] > 0 &&
                    prm->right_line[i - 3] < IMG_W * 4 / 5 &&
                    prm->right_line[i - 3] > IMG_W / 4 &&
                    prm->right_line[i - 3] - prm->left_line[i - 3] > 20)     //�������һ��ͻ�����ж��Ƿ�ΪԲ���յ�
                {
                    prm->right_arcinf = i - 3;
                    break;
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����״̬�����������
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��6��25��
//  Sample usage:               analysis_garage(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_garage(Img_Param *prm)
{
    int i;
    switch (prm->garage_flag)
    {
        case 1:
            for (i = prm->road_start;  i - 9 > prm->road_end; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i - 6] > 12)        //������ּ���������������ж��Ƿ�Ϊ���¹յ�
                {
                    if (prm->left_line[i - 3] - prm->left_line[i] < 6 && prm->left_line[i] - prm->left_line[i - 3] < 3)        //�յ�ǰ�ı߽�������ȷ��Ϊֱ�ǹյ�
                    {
                        prm->left_inf1 = i - 3;
                        break;
                    }
                }
            }
            if (!prm->left_inf1 && prm->left_lose1 > 20)
                prm->garage_flag = 3;
            break;
        case 2:
            for (i = prm->road_start;  i - 9 > prm->road_end; i--)        //Ѱ���Ҳ�ĵ�һ���յ�
            {
                if (prm->right_line[i - 6] - prm->right_line[i - 3] > 12)        //������ּ���������������ж��Ƿ�Ϊ���¹յ�
                {
                    if (prm->right_line[i] - prm->right_line[i - 3] < 6 && prm->right_line[i - 3] - prm->right_line[i] < 3)        //�յ�ǰ�ı߽�������ȷ��Ϊֱ�ǹյ�
                    {
                        prm->right_inf1 = i - 3;
                        break;
                    }
                }
            }
            if (!prm->right_inf1 && prm->right_lose1 > 20)
                prm->garage_flag = 4;
            break;
        case 3:
            for (i = prm->road_start;  i -  9 > prm->road_end; i--)
            {
                if (prm->right_line[i - 3] - prm->right_line[i - 6] > 10 && prm->right_line[i] - prm->right_line[i - 3] < 6 && prm->right_line[i - 3] - prm->right_line[i] < 3)
                {
                        prm->right_inf2 = i - 6;
                        break;
                }
            }
            if (prm->road_end > 50 && !prm->right_inf2 && prm->left_lose1 + prm->left_lose2 + prm->right_lose1 < 5)
            {
                prm->garage_flag = 5;
                prm->stop_flag = 1;
            }
            break;
        case 4:
              for (i = prm->road_start;  i -  9 > prm->road_end; i--)
              {
                  if (prm->left_line[i - 6] - prm->left_line[i - 3] > 10 && prm->left_line[i - 3] - prm->left_line[i] < 6 && prm->left_line[i] - prm->left_line[i - 3] < 3)
                  {
                          prm->left_inf2 = i - 6;
                          break;
                  }
              }
              if (prm->road_end > 50 && !prm->left_inf2 && prm->left_lose1 + prm->right_lose1 + prm->right_lose2 < 5)
              {
                  prm->garage_flag = 5;
                  prm->stop_flag = 1;
              }
              break;
        case 5:     //ͣ��
            prm->stop_flag = 1;
            break;
        default:    break;
    }
    if (prm->garage_flag == 5)  prm->flag |= 0x04;
    else if (prm->garage_flag > 2)   prm->flag |= 0x03;
    else prm->flag |= 0x02;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����·״̬�µĹյ�Ѱ��
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��6��25��
//  Sample usage:               analysis_fork(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_fork (Img_Param *prm)
{
    int i;
    switch (prm->fork_flag)
    {
        case 1:
            for (i = prm->road_start;  i - 8 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->right_line[i - 2] < prm->right_line[i - 4] && prm->right_line[i - 6] > prm->right_line[i - 4] && prm->right_line[i - 2] > IMG_W / 2)
               {
                   prm->right_inf1 = i - 2;
                   break;
               }
            }
            for (i = prm->road_start;  i - 10 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 10)
                {
                        prm->right_inf2 = i - 3;
                        break;
                }
            }
            if (prm->direct_flag == 1)
            {
                if (!prm->right_inf1 &&  prm->right_inf2 > 35 && prm->right_lose2 < 10)
                {
                    prm->direct_flag = 0;
                    prm->fork_flag = 3;
                }
            }
            else
            {
                if ((!prm->right_inf1 || prm->right_inf1 > 50) && prm->right_lose1 > 15 && prm->right_inf2 > 30 && prm->right_lose2 < 10)
                {
                    prm->direct_flag = 1;
                    prm->fork_flag = 3;
                }
            }
            break;
        case 2:
            for (i = prm->road_start;  i - 8 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->left_line[i - 2] > prm->left_line[i - 4] && prm->left_line[i - 4] > prm->left_line[i - 6] && prm->left_line[i - 2] < IMG_W /2)
               {
                   prm->left_inf1 = i - 2;
                   break;
               }
            }
            for (i = prm->road_start;  i - 10 > prm->road_end  && i > IMG_H / 3; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 10)
                {
                    prm->left_inf2 = i - 3;
                    break;
                }
            }
            if (prm->direct_flag == 1)
            {
                if (!prm->left_inf1 && prm->left_inf2 > 35 && prm->left_lose2 < 10)
                {
                    prm->direct_flag = 0;
                    prm->fork_flag = 4;
                }
            }
            else
            {
                if ((!prm->left_inf1|| prm->left_inf1 > 50) && prm->left_lose1 > 15 && prm->left_inf2 > 30 && prm->left_lose2 < 10)
                {
                    prm->direct_flag = 1;
                    prm->fork_flag = 4;
                }
            }
            break;
        case 3:
            for (i = prm->road_start;  i - 10 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 10)
                {
                        prm->right_inf2 = i - 3;
                        break;
                }
            }
            if(!prm->right_inf2 && prm->right_lose1 < 2)
                prm->fork_flag = 0;
            break;
        case 4:
            for (i = prm->road_start;  i - 10 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 10)
                {
                    prm->left_inf2 = i - 3;
                    break;
                }
            }
            if (!prm->left_inf2 && prm->left_lose1 < 2)
                prm->fork_flag = 0;
            break;
        default: break;
    }
    prm->flag |= 0x01;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����״̬�µĹյ�Ѱ�ң��Ż����״̬��
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��7��1��
//  Sample usage:               analysis_round(&prm);  ����ֱ�ӻҶ�ͼ������ܻ���һЩ���ţ�״̬�л�ʱ��ؼ�������Լ������
//-------------------------------------------------------------------------------------------------------------------
void analysis_round(Img_Param *prm)
{
    int i, temp;
    switch (prm->round_flag)
    {
        /* ����״̬1���󻷵�Ϊ����
         * �յ����������������¹յ㣬�����Ƿ������¹յ����Բ���յ��������ʼ��
         * ���߲��ԣ����¹յ�����Բ���յ�����
         * ״̬�л������¹յ���ʧ����ת��״̬2
         * */
        case 1:     //�󻷵�1
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)        //Ѱ�����¹յ�
            {
                if (prm->left_line[i - 3] - prm->left_line[i - 6] > 12)        //������ּ���������������ж��Ƿ�Ϊ���¹յ�
                {
                    if (prm->left_line[i - 3] - prm->left_line[i] < 6 && prm->left_line[i] - prm->left_line[i - 3] < 3)        //�յ�ǰ�ı߽�������ȷ��Ϊֱ�ǹյ�
                    {
                        prm->left_inf1 = i - 3;
                        break;
                    }
                }
            }
            for (i = (prm->left_inf1 == 0 ? prm->road_start - 6 : prm->left_inf1 - 10);  i - 10 > prm->road_end; i--)
            {
                if (prm->left_line[i] <= prm->left_line[i - 3] && prm->left_line[i - 6] < prm->left_line[i - 3] && prm->left_line[i - 3] > 10)     //�������һ��ͻ�����ж��Ƿ�ΪԲ���յ�
                {
                    prm->left_arcinf = i - 3;
                    break;
                }
            }
            if (!prm->left_inf1)
                prm->round_flag = 3;
            break;
        case 2:     //�һ���1
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)          //Ѱ�����¹յ�
            {
                if (prm->right_line[i - 6] - prm->right_line[i - 3] > 12)        //������ּ���������������ж��Ƿ�Ϊ���¹յ�
                {
                    if (prm->right_line[i] - prm->right_line[i - 3] < 6 && prm->right_line[i - 3] - prm->right_line[i] < 3)        //�յ�ǰ�ı߽�������ȷ��Ϊֱ�ǹյ�
                    {
                        prm->right_inf1 = i - 3;
                        break;
                    }
                }
            }
            for (i = (prm->right_inf1 == 0 ? prm->road_start - 6 : prm->right_inf1 - 10);  i - 10 > prm->road_end; i--)
            {
                if (prm->right_line[i] >= prm->right_line[i - 3] && prm->right_line[i - 6] > prm->right_line[i - 3] && prm->right_line[i - 3] < IMG_W - 11)
                {
                    prm->right_arcinf = i - 3;
                    break;
                }
            }
            if (!prm->right_inf1)
                prm->round_flag = 4;
            break;
        /* ����״̬2���󻷵�Ϊ����
         * �յ�������������Բ���յ�����Ϲյ�
         * ���߲��ԣ���Բ���յ��������ߣ��յ��Ӧ�е��ұ߽�����ྡͷ���ӣ��ɵ�������б���Ը���·����
         * ״̬�л������������Ϲյ�����ת��״̬3
         * */
        case 3:     //�󻷵�2
            for (i = prm->road_start - 6;  i - 10 > prm->road_end; i--)
            {
                if (prm->left_line[i] <= prm->left_line[i - 3] && prm->left_line[i - 6] < prm->left_line[i - 3] && prm->left_line[i - 3] > 10)
                {
                    prm->left_arcinf = i - 3;
                    break;
                }
            }
            for (i = prm->road_start;  i - 3 > prm->road_end; i--)
            {
                if(prm->right_line[i] - prm->right_line[i - 1] > 15 && prm->right_line[i - 3] < prm->right_line[i - 1])
                {
                    prm->right_inf2 = i - 1;
                    break;
                }
            }
            if (prm->right_inf2 && (!prm->left_arcinf || prm->left_arcinf > 40))
                prm->round_flag = 5;
            break;
        case 4:     //�һ���2
            for (i = prm->road_start - 6;  i - 10 > prm->road_end; i--)
            {
                if (prm->right_line[i] >= prm->right_line[i - 3] && prm->right_line[i - 6] > prm->right_line[i - 3] && prm->right_line[i - 3] < IMG_W - 11)
                {
                    prm->right_arcinf = i - 3;
                    break;
                }
            }
            for (i = prm->road_start;  i - 3 > prm->road_end; i--)
              {
                  if(prm->left_line[i - 1] - prm->left_line[i] > 15 && prm->left_line[i - 3] > prm->left_line[i - 1])
                  {
                      prm->left_inf2 = i - 1;
                      break;
                  }
              }
            if (prm->left_inf2 && (!prm->right_arcinf || prm->right_arcinf > 40))
                prm->round_flag = 6;
            break;
            /* ����״̬3���󻷵�Ϊ����
             * �յ��������������Ϲյ�
             * ���߲��ԣ����Ϲյ���������ʼλ�ò��ߣ��ɸ��ݹյ������о�����б�����߻�̶��������ߣ�
             * ״̬�л������Ϲյ���ʧ����ת��״̬4
             * */
        case 5:     //�󻷵�3
            for (i = prm->road_start;  i - 3 > prm->road_end; i--)
            {
                if(prm->right_line[i] - prm->right_line[i - 1] > 15)
                {
                    prm->right_inf2 = i - 1;
                    break;
                }
            }
            if(!prm->right_inf2 && prm->right_lose1 < 2 && prm->left_lose1 + prm->left_lose2 > 15)
                prm->round_flag = 7;
            break;
        case 6:     //�һ���3
            for (i = prm->road_start;  i - 3 > prm->road_end; i--)
              {
                  if(prm->left_line[i - 1] - prm->left_line[i] > 15)
                  {
                      prm->left_inf2 = i - 1;
                      break;
                  }
              }
            if(!prm->left_inf2 && prm->left_lose1 < 2 && prm->right_lose1 + prm->right_lose2 > 15)
                    prm->round_flag = 8;
            break;
            /* ����״̬4���󻷵�Ϊ����
             * �յ��������������¹յ㣬ͬʱ��¼���Ϸ���������
             * ���߲��ԣ����¹յ������Ϸ����ߣ��ɵ�������б���Ը���·����
             * ״̬�л������¹յ��ȳ�������ʧ����ת��״̬5
             * */
        case 7:
            for (i = prm->road_start;  i - 9 > prm->road_end; i--)        //Ѱ�����¹յ�
            {
                if (prm->right_line[i - 9] - prm->right_line[i - 3] > 12)
                {
                    if (prm->right_line[i - 6] > prm->right_line[i - 3] && prm->right_line[i] > prm->right_line[i - 3])
                    {
                        prm->right_inf1 = i - 3;
                        break;
                    }
                }
            }
            if (prm->right_inf1)        //�ҵ��¹յ���ȷ����������
            {
                temp = IMG_W  - 1;
                for (i = prm->right_inf1 - 1;  i > prm->road_end; i--)     //Ѱ������ߵļ�ֵ���ڲ��ߣ����������Ĺյ�
                {
                    if (prm->left_line[i] <= temp)
                    {
                        prm->right_inf2 = i;
                        temp = prm->left_line[i];
                    }
                }
            }
            if (!prm->right_inf1 &&  prm->right_lose1 > 20)
                prm->round_flag = 9;
            break;
        case 8:
            for (i = prm->road_start;  i - 9 > prm->road_end; i--)      //Ѱ�����¹յ�
            {
                if (prm->left_line[i - 3] - prm->left_line[i - 9] > 12 )
                {
                    if (prm->left_line[i - 3] > prm->left_line[i - 6] && prm->left_line[i - 3] > prm->left_line[i])
                    {
                        prm->left_inf1 = i - 3;
                        break;
                    }
                }
            }
            if (prm->left_inf1)     //�ҵ��¹յ���ȷ����������
            {
                temp = 0;
                for (i = prm->left_inf1 - 1;  i > prm->road_end; i--)     //Ѱ���ұ��ߵļ�ֵ���ڲ���
                {
                    if (prm->right_line[i] >= temp)
                    {
                        prm->left_inf2 = i;
                        temp = prm->right_line[i];
                    }
                }
            }
            if (!prm->left_inf1 &&  prm->left_lose1 > 20)
                prm->round_flag = 10;
            break;
            /* ����״̬5���󻷵�Ϊ����
             * �յ��������������Ϲյ㣬ͬʱ��¼���Ϸ���������
             * ���߲��ԣ����·������Ϸ����ߣ��ɵ�������б���Ը���·����
             * ״̬�л������������Ϲյ�����ת��״̬6
             * */
        case 9:     //�󻷵�5
            temp = IMG_W - 1;
            for (i = prm->road_start - 20;  i > prm->road_end; i--)
            {
                if (prm->left_line[i] <= temp)
                {
                    prm->right_inf2 = i;
                    temp = prm->left_line[i];
                }
            }
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 12 && prm->left_line[i - 6] - prm->left_line[i - 3] < 6 && prm->left_line[i - 3] - prm->left_line[i - 6] < 3)
                {
                    prm->left_inf2 = i - 3;
                    break;
                }
            }
            if (prm->left_inf2)
                prm->round_flag = 11;
            break;
        case 10:
            temp = 0;
            for (i = prm->road_start - 15;  i > prm->road_end; i--)     //Ѱ���ұ��ߵļ�ֵ���ڲ���
            {
                if (prm->right_line[i] >= temp)
                {
                    prm->left_inf2 = i;
                    temp = prm->right_line[i];
                }
            }
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 12 && prm->right_line[i - 3] - prm->right_line[i - 6] < 6 && prm->right_line[i - 6] - prm->right_line[i - 3] < 3)
                {
                    prm->right_inf2 = i - 3;
                    break;
                }
            }
            if (prm->right_inf2)
               prm->round_flag = 12;
            break;
            /* ����״̬6���󻷵�Ϊ����
             * �յ��������������Ϲյ�
             * ���߲��ԣ����Ϲյ�����������
             * ״̬�л������Ϲյ���ʧ����ת������״̬
             * */
        case 11:
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 12 && prm->left_line[i - 6] - prm->left_line[i - 3] < 6 && prm->left_line[i - 3] - prm->left_line[i - 6] < 3)
                {
                    prm->left_inf2 = i - 3;
                    break;
                }
            }
            if(!prm->left_inf2 && prm->left_lose1 < 4 && prm->left_lose2 < 4)
                prm->round_flag = 0;
            break;
        case 12:
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 12 && prm->right_line[i - 3] - prm->right_line[i - 6] < 6 && prm->right_line[i - 6] - prm->right_line[i - 3] < 3)
                {
                    prm->right_inf2 = i - 3;
                    break;
                }
            }
            if(!prm->right_inf2 && prm->right_lose1 < 4 && prm->right_lose2 < 4)
                prm->round_flag = 0;
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ҵ��Ĺյ������ж�·��
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��4��21��
//  Sample usage:               judge_road(*prm);
//-------------------------------------------------------------------------------------------------------------------
void judge_road(Img_Param *prm)
{
    if (prm->zebracrossing_flag == 1)
    {
        if (prm->left_inf1 && prm->left_inf2)
        {
            prm->right_inf1 = prm->left_inf1;
            prm->right_inf2 = prm->left_inf2;
            prm->garage_count = 1;
        }
        else if (prm->left_inf2)
        {
            prm->right_inf2 = prm->left_inf2;
            prm->garage_count = 1;
        }
        else if (prm->right_inf1 && prm->right_inf2)
        {
            prm->left_inf1 = prm->right_inf1;
            prm->left_inf2 = prm->right_inf2;
            prm->garage_count = 1;
        }
        else if (prm->right_inf2)
        {
            prm->left_inf2 = prm->right_inf2;
            prm->garage_count = 1;
        }
        else if (prm->left_lose1 + prm->right_lose1 < 5)
            prm->zebracrossing_flag = 0;
    }
    if (prm->left_inf1 && prm -> right_inf1 && prm->left_inf2 && prm -> right_inf2)        //����ʮ��
        prm->cross_flag = 1;
    else if (prm->left_inf1 && prm->left_inf2 && prm -> right_inf2)       //��б��ʮ��
        prm->cross_flag = 2;
    else if (prm->right_inf1 && prm->right_inf2 && prm->left_inf2)        //��б��ʮ��
        prm->cross_flag = 3;
    else if (prm->left_inf2 && prm -> right_inf2 && prm->right_line[prm->right_inf2] - prm->left_line[prm->left_inf2] > 30)      //ʮ����
        prm->cross_flag = 4;
    else if (prm->zebracrossing_flag == 2 && prm->left_inf1)     //�����
    {
        prm->garage_flag = 1;
        prm->zebracrossing_flag = 0;
    }
    else if (prm->zebracrossing_flag == 2 && prm->right_inf1)       //�����
    {
        prm->garage_flag = 2;
        prm->zebracrossing_flag = 0;
    }
    else if (prm->left_arcinf && !prm->right_inf1 && !prm->right_inf2 && prm->right_slope > -0.8 && prm->right_outliers < 10
           && prm->right_lose1 + prm->right_lose2 < 5)     //�󻷵�
    {
        prm->round_flag = 1;
        prm->displaly_flag = 1;
    }

    else if (prm->right_arcinf && !prm->left_inf1 && !prm->left_inf2 && prm->left_slope < 0.8 && prm->left_outliers < 10
            && prm->left_lose1 + prm->left_lose2 < 5)     //�һ���
    {
        prm->round_flag = 2;
        prm->displaly_flag = 1;
    }
}

void correct_misjudgment(Img_Param *prm)
{
    if (prm->round_flag == 1 && prm->right_outliers > 3 && prm->right_lose1 + prm->right_lose2 > 3)
    {
            prm->round_flag = 0;
    }
    else if (prm->round_flag == 2 && prm->left_outliers > 3 && prm->left_lose1 + prm->left_lose2 > 3)
    {
            prm->round_flag = 0;
    }
    else if (prm->round_flag == 3 && prm->left_lose1 + prm->left_lose2 < 3)
    {
            prm->round_flag = 0;
    }
    else if (prm->round_flag == 2 && prm->right_lose1 + prm->right_lose2 < 3)
    {
            prm->round_flag = 0;
    }

}
void patch_left_2point(Img_Param *prm)      //�������������ֱ�յ�
{
    float lx = (float)(prm->left_line[prm->left_inf1]  - prm->left_line[prm->left_inf2]) / (prm->left_inf1 - prm->left_inf2);
    for (int i = prm->left_inf1, x = 0; i > prm->left_inf2; i--, x++)
        prm->left_line[i] = prm->left_line[prm->left_inf1] - (lx * x);
}
void patch_right_2point(Img_Param *prm)     //�����Ҳ�������ֱ�յ�
{
    float  rx = (float)(prm->right_line[prm->right_inf1]  - prm->right_line[prm->right_inf2]) / (prm->right_inf1 - prm->right_inf2);
    for (int i = prm->right_inf1, x = 0; i > prm->right_inf2; i--, x++)
        prm->right_line[i] = prm->right_line[prm->right_inf1] - (rx * x);
}

void patch_left_slope_down(Img_Param *prm, int mode)      //��ֱ�յ���������
{
    float lx = (float)(prm->left_line[prm->left_inf2]  - prm->left_line[prm->left_inf2 - 3]) / 3;
    for (int i = prm->left_inf2, x = 0; i <= prm->road_start; i++, x++)
    {
        int patch = prm->left_line[prm->left_inf2] + (lx * x);
        if (mode)   patch = (patch < prm->left_line[i] ? prm->left_line[i] : patch);
        else patch = (patch < 1 ? 1 : patch);
        prm->left_line[i] = patch;
    }
}
void patch_right_slope_down(Img_Param *prm, int mode)     //�Ҵ�ֱ�յ���������
{
    float rx = (float)(prm->right_line[prm->right_inf2]  - prm->right_line[prm->right_inf2 - 3]) / 3;
    for (int i = prm->right_inf2, x = 0; i <= prm->road_start; i++, x++)
    {
        int patch = prm->right_line[prm->right_inf2] + (rx * x);
        if (mode)   patch = (patch > prm->right_line[i] ? prm->right_line[i] : patch);
        else patch = (patch > IMG_W - 2 ? IMG_W - 2 : patch);
        prm->right_line[i] = patch;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ߺ���
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��4��12��
//  Sample usage:               patch_line(&prm);
//-------------------------------------------------------------------------------------------------------------------
void patch_line(Img_Param *prm)
{
    if (prm->garage_flag)       //��ⲹ��
    {
        float lx,rx;
        switch (prm->garage_flag)
        {
            case 1:
                if (prm->left_inf1)
                {
                    lx = (float)(prm->left_line[prm->left_inf1] - prm->left_line[prm->road_end]) *0.75 / (prm->road_end - prm->left_inf1);
                    rx = (float)(prm->right_line[prm->left_inf1] - prm->left_line[prm->road_end]) *0.5 / (prm->road_end - prm->left_inf1);
                    for (int i = prm->left_inf1, x = 0; i > prm->road_end; i--, x++)
                    {
                        prm->left_line[i] = prm->left_line[prm->left_inf1] + (lx * x);
                        prm->right_line[i] = prm->right_line[prm->left_inf1] + (rx * x);
                    }
                }
                break;
            case 2:
                if (prm->right_inf1)
                {
                    lx = (float)(prm->left_line[prm->right_inf1] - prm->right_line[prm->road_end]) * 0.5 / (prm->road_end - prm->right_inf1);
                    rx = (float)(prm->right_line[prm->right_inf1] - prm->right_line[prm->road_end]) * 0.75 / (prm->road_end - prm->right_inf1);
                    for (int i = prm->right_inf1, x = 0; i > prm->road_end; i--, x++)
                    {
                        prm->left_line[i] = prm->left_line[prm->right_inf1] + (lx * x);
                        prm->right_line[i] = prm->right_line[prm->right_inf1] + (rx * x);
                    }
                }
                break;
            case 3:
                if(prm->right_inf2 && prm->right_lose1 > 2)
                    patch_right_slope_down(prm, 1);
                else if (prm->left_lose1 + prm->left_lose2 > 5)
                {
                    rx = (float)(Garage_Patch - prm->left_line[prm->road_end]) *0.5 / (prm->road_end - prm->road_start);
                    for (int i = prm->road_start, x = 0; i > prm->road_end; i--, x++)
                    {
                        prm->left_line[i] = 0;
                        prm->right_line[i] = Garage_Patch + (rx * x);
                    }
                }
                break;
            case 4:
                if (prm->left_inf2 && prm->left_lose1 > 2)
                    patch_left_slope_down(prm, 1);
                else if (prm->right_lose1 + prm->right_lose2 > 5)
                {
                    lx = (float)(IMG_W - 1 -Garage_Patch - prm->right_line[prm->road_end]) *0.5 / (prm->road_end - prm->road_start);
                    for (int i = prm->road_start, x = 0; i > prm->road_end; i--, x++)
                    {
                        prm->right_line[i] = IMG_W - 1;
                        prm->left_line[i] = IMG_W - 1 -Garage_Patch + (lx * x);
                    }
                }
                break;
            default:    break;
        }
    }
    else if (prm->round_flag)       //��������
        {
        static int temp;
            if(prm->round_flag % 2 == 1)        //�󻷵�����
            {
                float lx, rx;
                switch(prm->round_flag)
                {
                    case 1:     //�󻷵�1���ߣ��������ֱ�ǹյ��Բ���յ�
                        if (prm->left_inf1)
                        {
                            lx = (float)(prm->left_line[prm->left_inf1]  - prm->left_line[prm->left_arcinf]) / (prm->left_inf1 - prm->left_arcinf);
                            for(int i = prm->left_inf1, x = 0; i > prm->left_arcinf; i--, x++)
                                prm->left_line[i] = prm->left_line[prm->left_inf1] - (lx * x);
                        }
                        else
                        {
                            lx = (float)(prm->right_line[prm->road_start] - First_Patch - prm->left_line[prm->left_arcinf]) / (prm->road_start - prm->left_arcinf);
                            for (int i = prm->road_start, x = 0; i > prm->left_arcinf; i--, x++)
                                prm->left_line[i] = prm->right_line[prm->road_start] - First_Patch - (lx * x);
                        }
                        break;
                    case 3:     //�󻷵�2���ߣ�����Բ���յ������²��ߣ���Ӧ���ұ߽��������ϱ߽�����
                        lx = (float)(prm->right_line[prm->road_start] - First_Patch - prm->left_line[prm->left_arcinf]) / (prm->road_start - prm->left_arcinf);
                        rx = (float)(prm->right_line[prm->left_arcinf] - prm->left_line[prm->road_end]) / (prm->road_end - prm->left_arcinf);
                        for (int i = prm->left_arcinf, x = 0; i > prm->road_end; i--, x++)
                            prm->right_line[i] = prm->right_line[prm->left_arcinf] + (rx * x);
                        for (int i = prm->road_start, x = 0; i > prm->left_arcinf; i--, x++)
                            prm->left_line[i] = prm->right_line[prm->road_start] - First_Patch - (lx * x);
                        break;
                    case 5:     //�󻷵�3���ߣ����Ϲյ������²���
                        if(prm->right_inf2 - prm->road_end < 10)
                        {
                            rx = (float)(prm->left_line[prm->road_start] + First_Patch + 15  - prm->right_line[prm->right_inf2]) / (prm->right_inf2 - prm->road_start);
                            for (int i = prm->road_start, x = 0; i > prm->right_inf2; i--, x++)
                                prm->right_line[i] = prm->left_line[prm->road_start] + First_Patch + 15 + (rx * x);
                        }
                        else
                            patch_right_slope_down(prm,1);
                        break;
                               //�󻷵�4����ѭ�������в���
                    case 7:     //�󻷵�5���ߣ����¹յ������ϲ���
                        if (prm->right_inf1)
                        {
                            temp = prm->right_line[prm->right_inf1];
                            rx = (float)(prm->right_line[prm->right_inf1]) / 2 / (prm->right_inf1 - prm->right_inf2);
                            for (int i = prm->right_inf1, x = 0; i > prm->right_inf2; i--, x++)
                                prm->right_line[i] = temp - (rx * x);
                            prm->road_end = prm->right_inf2;     //����ȷ��������
                        }
                        break;
                    case 9:        //�󻷵�6���ߣ����½������Ͻ�����߽�
                        rx = (float)(prm->left_line[prm->right_inf2] - temp) / 2 / (prm->right_inf2 - prm->road_start);
                        for (int i = prm->road_start, x = 0; i > prm->right_inf2; i--, x++)
                            prm->right_line[i] = temp  - (rx * x);
                        prm->road_end = prm->right_inf2;
                        break;
                    case 11:        //�󻷵�7���ߣ����Ϲյ������²���
                        patch_left_slope_down(prm, 1);
                        break;
                    default: break;
                }
            }
            else if (prm->round_flag %2 == 0)       //�һ�������
            {
                float lx, rx;
                switch(prm->round_flag)
                {
                    case 2:     //�һ���1���ߣ������Ҳ�ֱ�ǹյ��Բ���յ�
                        if (prm->right_inf1)
                        {
                            rx = (float)(prm->right_line[prm->right_inf1]  - prm->right_line[prm->right_arcinf]) / (prm->right_inf1 - prm->right_arcinf);
                            for (int i = prm->right_inf1, x = 0; i > prm->right_arcinf; i--, x++)
                                prm->right_line[i] = prm->right_line[prm->right_inf1] - (rx * x);
                        }
                        else
                        {
                            rx = (float)(prm->left_line[prm->road_start] + First_Patch - prm->right_line[prm->right_arcinf]) / (prm->road_start - prm->right_arcinf);
                            for (int i = prm->road_start, x = 0; i > prm->right_arcinf && i > 5; i--, x++)
                                prm->right_line[i] = prm->left_line[prm->road_start] + First_Patch - (rx * x);
                        }
                        break;
                    case 4:       //�һ���2���ߣ�����Բ���յ������²��ߣ���Ӧ����߽��������ϱ߽�����
                        lx = (float)(prm->left_line[prm->right_arcinf] - prm->right_line[prm->road_end]) / (prm->road_end - prm->right_arcinf);
                        rx = (float)(prm->left_line[prm->road_start] + First_Patch - prm->right_line[prm->right_arcinf]) / (prm->road_start - prm->right_arcinf);
                        for (int i = prm->right_arcinf, x = 0; i > prm->road_end && i > 5; i--, x++)
                            prm->left_line[i] = prm->left_line[prm->right_arcinf] + (lx * x);
                        for (int i = prm->road_start, x = 0; i > prm->right_arcinf && i > 5; i--, x++)
                            prm->right_line[i] = prm->left_line[prm->road_start] + First_Patch - (rx * x);
                        break;
                    case 6:      //�һ���3���ߣ����Ϲյ������²���
                        if(prm->left_inf2 - prm->road_end < 10)
                        {
                            lx = (float)(prm->right_line[prm->road_start] - First_Patch - 15 - prm->left_line[prm->left_inf2]) / (prm->left_inf2 - prm->road_start);
                            for (int i = prm->road_start, x = 0; i > prm->left_inf2; i--, x++)
                                prm->left_line[i] = prm->right_line[prm->road_start] - First_Patch - 15 + (lx * x);
                        }
                        else
                            patch_left_slope_down(prm, 1);
                        break;
                    case 8:        //�һ���5���ߣ����¹յ������ϲ���
                        if (prm->left_inf1)
                        {
                            temp = prm->left_line[prm->left_inf1];
                            lx = (float)(prm->left_line[prm->left_inf1]  - IMG_W + 1) / 2 / (prm->left_inf1 - prm->left_inf2);
                            for (int i = prm->left_inf1, x = 0; i > prm->left_inf2; i--, x++)
                                prm->left_line[i] = temp - (lx * x);
                            prm->road_end = prm->left_inf2;
                        }
                        break;
                    case 10:      //�һ���6���ߣ����½������Ͻ�����߽�
                        lx = (float)(prm->right_line[prm->left_inf2] - temp) / 2 / (prm->left_inf2 - prm->road_start);
                        for (int i = prm->road_start, x = 0; i > prm->left_inf2; i--, x++)
                            prm->left_line[i] = temp  - (lx * x);
                        prm->road_end = prm->left_inf2;
                        break;
                    case 12:      //�һ���7���ߣ����Ϲյ������²���
                        patch_right_slope_down(prm, 1);
                        break;
                    default: break;
                }
            }
        }
    else if (prm->cross_flag)       //ʮ��·����
    {
        switch (prm->cross_flag)
        {
            case 1:     //����ʮ�ֲ��ߣ��ĸ��յ���������
                patch_left_2point(prm);
                patch_right_2point(prm);
                break;
            case 2:     //��б��ʮ�ֲ��ߣ���������յ����������Ϲյ����²���
                patch_left_2point(prm);
                patch_right_slope_down(prm, 1);
                break;
            case 3:     //��б��ʮ�ֲ��ߣ��Ҳ������յ����������Ϲյ����²���
                patch_left_slope_down(prm, 1);
                patch_right_2point(prm);
                break;
            case 4:     //ʮ���в��ߣ������Ϲյ����²���
                patch_left_slope_down(prm, 0);
                patch_right_slope_down(prm, 0);
                break;
            default: break;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ȡ���ı߽粢�������ߣ�ʹ����С���˷��������ұ߽��б�ʣ�
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��4��4��
//  Sample usage:               analysis_border_prossed(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_border_prossed(Img_Param *prm)
{
    float sum_x2 = 0.0, sum_x  = 0.0, suml_y  = 0.0, sumr_y  = 0.0, suml_xy = 0.0, sumr_xy = 0.0, sum_tmp = 0.0;       //��С���˷�����
    int num = prm->road_start - prm->road_end;     //��Ч����
    for (int i = prm->road_start, x = 0; i > prm->road_end; i--, x++)
    {
        prm->mid_line[i] = (prm->left_line[i] + prm->right_line[i]);        //Ϊ�˱�֤���ȴ˴�δ���Զ����൱����IMG_W-1Ϊ�е����ƫ��
        sum_x2 += x * x;
        sum_x += x;
        suml_y += prm->left_line[i];
        suml_xy += x * prm->left_line[i];
        sumr_y += prm->right_line[i];
        sumr_xy += x * prm->right_line[i];
    }
    if(num > 5)
    {
        sum_tmp = num * sum_x2 - sum_x * sum_x;
        prm->left_slope = (num * suml_xy - sum_x * suml_y) / sum_tmp;       //��С���˷������߽��б��
        prm->right_slope = (num * sumr_xy - sum_x * sumr_y) / sum_tmp;       //��С���˷�����ұ߽��б��
    }
    /*ֱ����ж�*/
    if ((prm->left_slope > 1.3  && prm-> right_slope > -0.3 && prm->left_outliers < 3 && (prm->road_end > 8 || prm->left_line[prm->road_end - 1] > IMG_W - 6)) ||
            (prm->right_slope < -1.3 && prm-> left_slope < 0.3 && prm->right_outliers < 3 && (prm->road_end > 8 || prm->right_line[prm->road_end - 1] < 5)))        //�����
        prm->curve_flag = 3;
    else if (prm->left_slope > 0.95 || prm->right_slope < -0.95 || prm->left_outliers + prm->right_outliers > 13)      //С���
        prm->curve_flag = 2;
    else if (prm->road_end > 5)     //��ֱ��
        prm->curve_flag = 1;
    else        //��ֱ��
        prm->curve_flag = 0;
    prm->flag |= prm->curve_flag << 5;      //ֱ�����־λ��װ
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ߣ�����ƫ��
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��4��5��
//  Sample usage:               analysis_midline(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_midline(Img_Param *prm)
{
    int total = 0, count = 0,ramp_count = 0,last_err = prm->mid_line[prm->road_start] - IMG_W + 1, err;
//    const int err_weight03[IMG_H] = {
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 1, 1, 1, 1, 1, 2, 2, 2,
//        2, 2, 2, 3, 3, 3, 3, 4, 5, 6,
//        7, 8, 9, 9, 10, 10, 9, 9, 8, 8,
//        7, 7, 7, 6, 6, 6, 6, 5, 5, 4,
//        4, 3, 3, 3, 2, 2, 2, 2, 2, 2};
    const int err_weight02[IMG_H] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 2, 2, 3, 3, 2, 2, 1, 1,
        3, 3, 5, 5, 7, 7, 5, 5, 3, 3,
        5, 5, 6, 6, 9, 9, 6, 6, 5, 5};
    //����ʶ������
    const int err_weight03[IMG_H] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 2, 2, 3, 3, 2, 2, 1, 1,
        3, 3, 5, 5, 7, 7, 5, 5, 3, 3,
        5, 5, 6, 6, 9, 9, 6, 6, 5, 5};
    for (int i = prm->road_start, x = 0;  i > prm->road_end; i--, x++)
    {
        int err = prm->mid_line[i] - IMG_W + 1;
        if (prm->curve_flag == 2)
        {
            total += err_weight02[i] * err;      //��¼ƫ���
            count += err_weight02[i];        //��¼Ȩ�غ�
        }
        else
        {
            if (abs_(err - last_err) > 5 && prm->curve_flag == 0) err = last_err;       //�˲�
            else last_err = err;
            total += err_weight03[i] * err;      //��¼ƫ���
            count += err_weight03[i];        //��¼Ȩ�غ�
        }
        if (i< IMG_H * 3 / 4 && i > IMG_H / 2)
        {
            if (prm->right_line[i] - prm->left_line[i] < 40)
                ramp_count ++;
        }
    }
    err = total / count;
    if (ramp_count > 2 && !prm->garage_flag && !prm->zebracrossing_flag && abs_(err) < 35)        //�µ�
    {
        prm->ramp_flag = 1;
        prm->flag |= 0x80;
    }

    if (abs_(err) < 200)        //�޷�
        prm->error = err;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����������÷���������Ұ���ȱ�������
//  @param      prm     ͼ������ṹ��
//  @return     114514
//  @creation date       2021��6��5��

//  Sample usage:               henghengheng_aaaaa_aaaaaaaaaaa(&prm);
//-------------------------------------------------------------------------------------------------------------------
int henghengheng_aaaaa_aaaaaaaaaaa (Img_Param *prm)
{
//    if (prm->stop_flag)
//        beep_control(0);
//    else if (prm->round_flag)
//        beep_control(_f1);
//    else if (prm->fork_flag || prm->garage_flag || prm->zebracrossing_flag)
//        beep_control(_g);
//    else if (prm->ramp_flag)
//        beep_control(_b);
//    else if (prm->curve_flag == 1)
//        beep_control(_a);
//    else if (prm->curve_flag == 2)
//        beep_control(_a1);
//    else if (prm->curve_flag == 3)
//        beep_control(_b);
//    else
//        beep_control(0);
    return 114514;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ʾ����
//  @param      prm     ͼ������ṹ��
//  @return     void
//  @creation date       2021��5��13��
//  Sample usage:               display_param(&prm);
//-------------------------------------------------------------------------------------------------------------------
void display_param(Img_Param *prm)
{
//    char str[15];
//    ips114_showint16(0, 4, prm->error);
//    sprintf(str, "ls1:%2d,%2d  ", prm->left_lose1, prm->right_lose1);
//    ips114_showstr(0, 5, str);
//    sprintf(str, "ls2:%2d,%2d  ", prm->left_lose2, prm->right_lose2);
//    ips114_showstr(0, 6, str);
//    sprintf(str, "out:%2d,%2d", prm->left_outliers, prm->right_outliers);
//    ips114_showstr(0, 7, str);
//    if (prm->stop_flag)
//        sprintf(str, "S T O P");
//    else if(prm->round_flag)
//        sprintf(str, "ROUND%d ", (prm->round_flag + 1) >> 1);
//    else if (prm->fork_flag)
//        sprintf(str, "FORKWAY");
//    else if (prm->garage_flag)
//        sprintf(str, "GARAGE2");
//    else if (prm->zebracrossing_flag == 1)
//        sprintf(str, "GARAGE1");
//    else if (prm->ramp_flag)
//        sprintf(str, "RAMPWAY");
//    else if (prm->curve_flag == 3)
//        sprintf(str, "CURVE 2");
//    else if (prm->curve_flag == 2)
//        sprintf(str, "CURVE 1");
//    else if (prm->curve_flag == 1)
//        sprintf(str, "NOMAL 2");
//    else
//        sprintf(str, "NOMAL 1");
//    ips114_showstr(IMG_W, 0, str);
//    sprintf(str, "end%2d", prm->road_end);
//    ips114_showstr(IMG_W, 1, str);
//    ips114_showfloat(IMG_W, 2, prm->left_slope, 1, 3);
//    ips114_showfloat(IMG_W, 3, prm->right_slope, 1, 3);
//    sprintf(str, "zbr%2d", prm->zebracrossing_count);
//    ips114_showstr(IMG_W, 4, str);
//    sprintf(str, "%3d", prm->black_threshold);
//    ips114_showstr(IMG_W, 5, str);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����Ļ����ʾͼ��
//  @param      *Img     ͼ����ڵ�ַ
//  @return     void
//  @creation date       2021��6��6��
//  Sample usage:               display_image(Img[0]);
//-------------------------------------------------------------------------------------------------------------------
void display_grey(uint8 *p, Img_Param *prm)
{
//    uint32 w,h;
//    uint16 color = 0;
//    uint16 temp = 0;
//    tft180_set_region(0,0,IMG_W-1,IMG_H-1);
//    for(h=0; h<IMG_H;h++)
//    {
//        for(w=0;w<IMG_W;w++)
//        {
//            if(h > prm->road_end && h <= prm->road_start)
//            {
//                int mid = (prm->left_line[h] + prm->right_line[h]) >> 1;
//                if (w == prm->left_line[h])
//                    soft_spi_write_16bit(&tft180_spi,RGB565_BLUE);
//                else if (w == prm->right_line[h])
//                    soft_spi_write_16bit(&tft180_spi,RGB565_GREEN);
//                else if (w == mid)
//                    soft_spi_write_16bit(&tft180_spi,RGB565_RED);
//                else
//                {
//                    temp = *(p+h*IMG_W+w);//��ȡ���ص�
//                    color=(0x001f&((temp)>>3))<<11;
//                    color=color|(((0x003f)&((temp)>>2))<<5);
//                    color=color|(0x001f&((temp)>>3));
//                    soft_spi_write_16bit(&tft180_spi,color);
//                }
//            }
//            else
//            {
//                temp = *(p+h*IMG_W+w);//��ȡ���ص�
//                color=(0x001f&((temp)>>3))<<11;
//                color=color|(((0x003f)&((temp)>>2))<<5);
//                color=color|(0x001f&((temp)>>3));
//                soft_spi_write_16bit(&tft180_spi,color);
//            }
//        }
//    }
}
