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
* 2023-05-26       pudding            ����SPI WIFI �жϻص�ָ��
* 2024-01-16       pudding            �Ƴ�SPI WIFI �жϻص�ָ�� SPI WIFI������ʹ���ⲿ
********************************************************************************************************************/

#include "zf_device_type.h"

static void type_default_callback(void);

camera_type_enum    camera_type                     = NO_CAMERE;                    // ����ͷ���ͱ���
callback_function   camera_uart_handler             = type_default_callback;        // ����ͨѶ�жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת
callback_function   camera_vsync_handler            = type_default_callback;        // ���жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת
callback_function   camera_dma_handler              = type_default_callback;        // DMA����жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת

wireless_type_enum  wireless_type                   = NO_WIRELESS;
callback_function   wireless_module_uart_handler    = type_default_callback;        // ���ߴ��ڽ����жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת

tof_type_enum       tof_type                        = NO_TOF;
callback_function   tof_module_exti_handler         = type_default_callback;        // ToF ģ�� INT �����ж�

//-------------------------------------------------------------------------------------------------------------------
// �������     Ĭ�ϻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��
// ��ע��Ϣ     ������������� ��ֹ��û�г�ʼ���豸��ʱ���ܷ�
//-------------------------------------------------------------------------------------------------------------------
static void type_default_callback (void)
{

}
//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͷ����
// ����˵��     type_set        ѡ��������ͷ����
// ����˵��     vsync_callback  �豸�ĳ��жϻص�����
// ����˵��     dma_callback    �豸�� DMA ����жϻص�����
// ����˵��     uart_callback   �豸�Ĵ��ڻص�����
// ���ز���     void
// ʹ��ʾ��     set_camera_type(CAMERA_GRAYSCALE);
// ��ע��Ϣ     һ���ɸ�����ͷ��ʼ���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void  set_camera_type (camera_type_enum type_set, callback_function vsync_callback, callback_function dma_callback, callback_function uart_callback)
{
    camera_type = type_set;
    camera_uart_handler = ((uart_callback == NULL) ? (type_default_callback) : (uart_callback));
    camera_vsync_handler = ((vsync_callback == NULL) ? (type_default_callback) : (vsync_callback));
    camera_dma_handler = ((dma_callback == NULL) ? (type_default_callback) : (dma_callback));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ģ������
// ����˵��     type_set        ѡ��������ģ������
// ����˵��     uart_callback   �豸�Ĵ��ڻص�����
// ���ز���     void
// ʹ��ʾ��     set_wireless_type(WIRELESS_UART, uart_callback);
// ��ע��Ϣ     һ���ɸ�����ͷ��ʼ���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void set_wireless_type (wireless_type_enum type_set, callback_function wireless_callback)
{
    wireless_type = type_set;
    wireless_module_uart_handler = ((wireless_callback == NULL) ? (type_default_callback) : (wireless_callback));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ToF ģ������
// ����˵��     type_set        ѡ���� ToF ģ������
// ����˵��     exti_callback   �豸���ⲿ�жϻص�����
// ���ز���     void
// ʹ��ʾ��     set_tof_type(TOF_DL1A, dl1a_int_handler);
// ��ע��Ϣ     һ���ɸ�����ͷ��ʼ���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void set_tof_type (tof_type_enum type_set, callback_function exti_callback)
{
    tof_type = type_set;
    tof_module_exti_handler = ((exti_callback == NULL) ? (type_default_callback) : (exti_callback));
}

