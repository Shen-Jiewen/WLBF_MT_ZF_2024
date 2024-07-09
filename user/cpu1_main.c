/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          cpu1_main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.4
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#pragma section all "cpu1_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU1��RAM��

// **************************** �������� ****************************

// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������

#define SHOW_RANGE 2
#define POINT_VALID(x, y) (((x) >= 0) && ((x) < MT9V03X_W) && ((y) >= 0) && ((y) < MT9V03X_H))

extern Img_Param prm;      //ͼ������ṹ��

extern int g_mutexFlagBit;
extern int g_lastMutexFlagBit;       //˫�˻�������־λ����һ�α�־λ,������Ļ��˫�˵���  [0]:cpu0ռ��  [1]:cpu1ռ��

void core1_main(void)
{
    disable_Watchdog();                     // �رտ��Ź�
    interrupt_global_enable(0);             // ��ȫ���ж�
    // �˴���д�û����� ���������ʼ�������
    /**********ϵͳ��ʼ��***********/
    //����ͷ��ʼ��
    mt9v03x_init();

    //ͼ�����ʼ��
    param_init(&prm);
    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();                 // �ȴ����к��ĳ�ʼ�����
    while (TRUE)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        // ���ͼ������ɱ�־Ϊ�棬�����ͼ����
        if(mt9v03x_finish_flag)
        {
            //��ֵ��ͼ��
//            binarize_image(mt9v03x_image,200);
            // �ҵ�ͼ�����ʼ��
            find_startline(mt9v03x_image, &prm);
            // ����ҵ�ֹͣ�߱�־Ϊ��
            if (prm.stop_flag)
            {
                mt9v03x_finish_flag = 0; // ���ͼ������ɱ�־
                prm.flag |= 0x04; // ���ò�����־
                prm.road_start = 0; // ·����ʼλ������Ϊ0
                prm.road_end = 0; // ·�Ľ���λ������Ϊ0
                prm.round_flag = 0; // Բ�α�־����Ϊ0
            }
            else{
                // ���δ�ҵ������ߺͳ����־
                if (!prm.zebracrossing_flag && !prm.garage_flag)
                    find_zebracrossing(&prm); // Ѱ�Ұ�����
                // �ҵ�ͼ����ϱ߽�
                find_upborder(mt9v03x_image, &prm);
                // �ҵ�ͼ��ı߽�
                find_border(mt9v03x_image, &prm);
                mt9v03x_finish_flag = 0; // ���ͼ������ɱ�־
                // ��������־Ϊ�棬���������
                if (prm.garage_flag)
                    analysis_garage(&prm);
                // ���������־Ϊ�棬���������
                else if (prm.round_flag)
                    analysis_round(&prm);
                // ���򣬷����߽粢�жϵ�·
                else{
                    analysis_border(&prm);
                    judge_road(&prm);
                }
                patch_line(&prm); // ���߲���
                analysis_border_prossed(&prm); // ���������ı߽�
                analysis_midline(&prm); // ��������
            }

            //��ʾ����
            //�л���Ļ��ʾ����
            if(g_lastMutexFlagBit != g_mutexFlagBit && g_mutexFlagBit == 1){
                //��Ļ���ĵ����л�,���³�ʼ��,��ֻ��ʼ��һ��
                tft180_clear();
                tft180_set_dir(TFT180_CROSSWISE);
                tft180_set_font(TFT180_6X8_FONT);
                tft180_init();
            }
            if(g_mutexFlagBit == 1){
                //��ʾ����
                tft180_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W/SHOW_RANGE, MT9V03X_H/SHOW_RANGE, 0);
                //��ʾѲ�ߵ����ұ߽������
                for (int i = MT9V03X_H - 2; i > 0; i -= SHOW_RANGE) {
                    unsigned short int x_left = prm.left_line[i] / SHOW_RANGE;
                    unsigned short int x_right = prm.right_line[i] / SHOW_RANGE;
                    unsigned short int x_mid = prm.mid_line[i] / (SHOW_RANGE * 2);
                    unsigned short int y = i / SHOW_RANGE;

                    //�������ߺͱ���
                    if (POINT_VALID(x_left, y)) {
                        tft180_draw_point((uint16)x_left, (uint16)y, RGB565_GREEN);
                    }
                    if (POINT_VALID(x_right, y)) {
                        tft180_draw_point((uint16)x_right, (uint16)y, RGB565_RED);
                    }
                    if (POINT_VALID(x_mid, y)) {
                        tft180_draw_point((uint16)x_mid, (uint16)y, RGB565_BLUE);
                    }
                }

                //��ʾ�յ���Ϣ
                if(prm.left_inf2 != 0){
                    tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(9), 1, 1);
                } else {
                    tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(9), 0, 1);
                }

                if(prm.left_arcinf != 0){
                    tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(10), 1, 1);
                } else {
                    tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(10), 0, 1);
                }

                if(prm.left_inf1 != 0){
                    tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(11), 1, 1);
                } else {
                    tft180_show_int(ROW_OFFSET(0), COLUMN_OFFSET(11), 0, 1);
                }

                if(prm.right_inf2 != 0){
                    tft180_show_int(ROW_OFFSET(3), COLUMN_OFFSET(9), 1, 1);
                } else {
                    tft180_show_int(ROW_OFFSET(3), COLUMN_OFFSET(9), 0, 1);
                }

                if(prm.right_arcinf != 0){
                    tft180_show_int(ROW_OFFSET(3), COLUMN_OFFSET(10), 1, 1);
                } else {
                    tft180_show_int(ROW_OFFSET(3), COLUMN_OFFSET(10), 0, 1);
                }

                if(prm.right_inf1 != 0){
                    tft180_show_int(ROW_OFFSET(3), COLUMN_OFFSET(11), 1, 1);
                } else {
                    tft180_show_int(ROW_OFFSET(3), COLUMN_OFFSET(11), 0, 1);
                }

                // ������
                tft180_show_int(ROW_OFFSET(5), COLUMN_OFFSET(9), prm.left_lose2, 2);
                tft180_show_int(ROW_OFFSET(5), COLUMN_OFFSET(11), prm.left_lose1, 2);
                // �Ҷ�����
                tft180_show_int(ROW_OFFSET(10), COLUMN_OFFSET(9), prm.right_lose2, 2);
                tft180_show_int(ROW_OFFSET(10), COLUMN_OFFSET(11), prm.right_lose1, 2);
                // ����������
                tft180_show_int(ROW_OFFSET(5), COLUMN_OFFSET(12), prm.left_outliers, 2);
                // ����������
                tft180_show_int(ROW_OFFSET(10), COLUMN_OFFSET(12), prm.right_outliers, 2);

                //�������
                tft180_draw_line(0,prm.long_line/2,MT9V03X_W / SHOW_RANGE,prm.long_line/2,RGB565_RED);
                // ������ʼ��
                tft180_draw_line(0, prm.road_start/2, MT9V03X_W / SHOW_RANGE, prm.road_start/2, RGB565_GREEN);
                // ����������
                tft180_draw_line(0, prm.road_end/2, MT9V03X_W / SHOW_RANGE, prm.road_end/2, RGB565_YELLOW);

                //��ʾ����ƫ��ֵ
                tft180_show_string(ROW_OFFSET(13), COLUMN_OFFSET(0),"error:");
                tft180_show_int(ROW_OFFSET(13), COLUMN_OFFSET(1), prm.error, 5);
                tft180_show_string(ROW_OFFSET(13), COLUMN_OFFSET(2),"slope:");
                tft180_show_float(ROW_OFFSET(13), COLUMN_OFFSET(3), prm.left_slope , 2, 2);

                //��ʾ����Ԫ��״̬
                tft180_show_int(ROW_OFFSET(2), COLUMN_OFFSET(8), prm.round_flag, 2);

                //��ʾ��ǰԪ�ص�ʶ��״̬
//                if(prm.curve_flag == 0){
//                    //��ֱ��[����+����ת��]
//                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "A ");
//                }
//                else if(prm.curve_flag == 1){
//                    //��ֱ��[����+����ת��]
//                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "B ");
//                }
//                else if(prm.curve_flag == 2){
//                    //С���[�����ٶ�+����ת��]
//                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "C ");
//                }
//                else if(prm.curve_flag == 3){
//                    //�����[�����ٶ�+����ת��]
//                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "D ");
//                }
                if(prm.round_flag > 0 && prm.round_flag < 11){
                    //����[�����ٶ�+����ת��]
                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "E");
                    //�������ͳ���������������
//                    if(prm.round_flag == 1 || prm.round_flag == ){
//
//                    }
                }
                else if(prm.cross_flag > 0 && prm.cross_flag < 5){
                    //ʮ��·��[�����ٶ�+����ת��]
                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "F ");
                }
                else{
                    //Ĭ�����[�����ٶ�+����ת��]
                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "G ");
                }

            }
        }
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}
#pragma section all restore
// **************************** �������� ****************************
