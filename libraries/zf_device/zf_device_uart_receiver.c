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
* �ļ�����          zf_device_uart_receiver
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.20
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-11-04       JKS                first version
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   TXD               �鿴 zf_device_uart_receiver.h �� UART_RECEVIER_RX_PIN �궨��
*                   GND               ��Դ��
*                   5V                5V��Դ
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_device_type.h"
#include "zf_driver_uart.h"
#include "zf_driver_timer.h"
#include "zf_device_uart_receiver.h"

uart_receiver_struct    uart_receiver ;             // ���ڽ��ջ�ͨ��������״̬

uint8   uart_receiver_data[REV_DATA_LEN]  = {0};    // ������ԭʼ����

//-------------------------------------------------------------------------------------------------------------------
//  �������     ��ȡ���ε���uart_receiver_interval_time����ʱ����
//  ����˵��     void
//  ���ز���     uint32            ���شӿ�ʼ�����ڵ�ʱ��(��λ1us)
//  ʹ��ʾ��     uint32 time = uart_receiver_interval_time();
//  ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint32 uart_receiver_interval_time (void)
{
    static uint32 time_last = 0;
    uint32 time, interval_time;
    uint32 stm_clk;

    stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)(IfxCpu_getCoreId())));

    time = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)(IfxCpu_getCoreId())));
    interval_time = time - time_last;
    time_last = time;
    interval_time = (uint32)((uint64)interval_time * 1000000 / stm_clk);

    return interval_time;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     SBUS���ݽ���
// ����˵��     *remote_data    ����ң�������ݵĵ�ַ
// ����˵��     *bufer          ԭʼ����
// ���ز���     void
// ʹ��ʾ��
// ��ע��Ϣ     ��sbus���ݽ������н���
//-------------------------------------------------------------------------------------------------------------------
static void uart_receiver_analysis (uart_receiver_struct *remote_data,uint8 * buffer)
{
    uint8 num = 0;
    remote_data->channel[num++] = (buffer[1] |buffer[ 2] << 8 ) & 0x07FF;
    remote_data->channel[num++] = (buffer[2] >> 3 | buffer[3] << 5 ) & 0x07FF;
    remote_data->channel[num++] = (buffer[3] >> 6 | buffer[4] << 2 | buffer[5] << 10 ) & 0x07FF;
    remote_data->channel[num++] = (buffer[5] >> 1 | buffer[6] << 7 ) & 0x07FF;
    remote_data->channel[num++] = (buffer[6] >> 4 | buffer[7] << 4 ) & 0x07FF;
    remote_data->channel[num++] = (buffer[7] >> 7 | buffer[8] << 1 | buffer[9] << 9 ) & 0x07FF;
    remote_data->state = (SBUS_NORMAL_STATE == buffer[23]) ? 1 : 0;
    uart_receiver.finsh_flag  = 1;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڽ��ջ�ģ�� �����жϻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     uart_receiver_callback();
// ��ע��Ϣ     �ú����� ISR �ļ� �����жϳ���ͨ��uart_receiver_uart_handler����ָ�뱻����
//-------------------------------------------------------------------------------------------------------------------
void uart_receiver_callback(void)
{
    static vuint8 length = 0;

    if (uart_receiver_interval_time() > 3000)
    {
        length = 0;
    }
    uart_receiver_data[length++] = uart_read_byte(UART_RECEVIER_UART_INDEX);
    if  ( (REV_DATA_LEN  == length)                                                                    // ���֡����֡ͷ��֡β����Э��
        && (FRAME_STAR   == uart_receiver_data[0])
        && (FRAME_END    == uart_receiver_data[24]))
    {
        uart_receiver_analysis(&uart_receiver, uart_receiver_data);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڽ��ջ���ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     uart_receiver_init();
//-------------------------------------------------------------------------------------------------------------------
void uart_receiver_init(void)
{
    uart_sbus_init(UART_RECEVIER_UART_INDEX, SBUS_UART_BAUDRATE, UART_RECEVIER_TX_PIN, UART_RECEVIER_RX_PIN);

    // ���ô����жϻص�����
    set_wireless_type(RECEIVER_UART, uart_receiver_callback);
}
