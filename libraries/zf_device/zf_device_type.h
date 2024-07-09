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
* �ļ�����          zf_device_type
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.20
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
* 2023-04-28       pudding            ��������ע��˵��
* 2023-05-26       pudding            ����SPI WIFI �жϻص�ָ��
********************************************************************************************************************/

#ifndef _zf_device_type_h_
#define _zf_device_type_h_

#include "zf_common_debug.h"

//==============================================���� ���� �����ṹ��==================================================
typedef enum
{
    NO_CAMERE = 0,                                                              // ������ͷ
    CAMERA_BIN_IIC,                                                             // С��� IIC �汾
    CAMERA_BIN_UART,                                                            // С��� UART �汾
    CAMERA_GRAYSCALE,                                                           // �����
    CAMERA_COLOR,                                                               // ��ͫ
}camera_type_enum;

typedef enum
{
    NO_WIRELESS = 0,                                                            // ���豸
    WIRELESS_UART,                                                              // ���ߴ���
    BLUETOOTH_CH9141,                                                           // ���� CH9141
    WIFI_UART,                                                                  // ���� WiFi
    RECEIVER_UART,                                                              // ǹʽң����
}wireless_type_enum;

typedef enum
{
    NO_TOF = 0,                                                                 // ���豸
    TOF_DL1A,                                                                   // DL1A
    TOF_DL1B,                                                                   // DL1B
}tof_type_enum;
//==============================================���� ���� �����ṹ��==================================================


//===========================================���� �ص�����ָ�뼰���� ����==============================================
typedef void (*callback_function)(void);

extern wireless_type_enum wireless_type;
extern callback_function wireless_module_uart_handler;                          // ���ߴ��ڽ����жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת

extern camera_type_enum camera_type;
extern callback_function camera_dma_handler;                                    // ����ͨѶ�жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת
extern callback_function camera_vsync_handler;                                  // ����ͨѶ�жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת
extern callback_function camera_uart_handler;                                   // ����ͨѶ�жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת
extern callback_function wireless_module_spi_handler;                           // WIFI SPI GPIO�жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת

extern tof_type_enum     tof_type;                                              // ToF ģ�� ����
extern callback_function tof_module_exti_handler;                               // ToF ģ�� INT �����ж�
//===========================================���� �ص�����ָ�뼰���� ����==============================================


//=============================================���� �жϻص� ��������================================================
void   set_camera_type          (camera_type_enum type_set, callback_function vsync_callback, callback_function dma_callback, callback_function uart_callback);
void   set_wireless_type        (wireless_type_enum type_set, callback_function wireless_callback);
void   set_tof_type             (tof_type_enum type_set, callback_function exti_callback);
//=============================================���� �жϻص� ��������================================================

#endif
