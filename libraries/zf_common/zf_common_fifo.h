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
* �ļ�����          zf_common_fifo
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.20
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-08-10        Teternal            first version
* 2023-12-06        Teternal            ���²����߼� �޸������ݶ�ȡʱ�쳣�Ĳ���
********************************************************************************************************************/

#ifndef _zf_common_fifo_h_
#define _zf_common_fifo_h_

#include "zf_common_typedef.h"

typedef enum
{
    FIFO_SUCCESS,                                                               // FIFO �����ɹ�

    FIFO_RESET_UNDO,                                                            // FIFO ���ò���δִ��
    FIFO_CLEAR_UNDO,                                                            // FIFO ��ղ���δִ��
    FIFO_BUFFER_NULL,                                                           // FIFO �û��������쳣
    FIFO_WRITE_UNDO,                                                            // FIFO д�����δִ��
    FIFO_SPACE_NO_ENOUGH,                                                       // FIFO д����� �������ռ䲻��
    FIFO_READ_UNDO,                                                             // FIFO ��ȡ����δִ��
    FIFO_DATA_NO_ENOUGH,                                                        // FIFO ��ȡ���� ���ݳ��Ȳ���
}fifo_state_enum;                                                               // FIFO �������

// �����߼�
// �������ò���   ����ǿ����� FIFO ����ʹ��
// ����д�����   �����������Լ�д�����ʱ����
// ˳���ȡ����   ��������պ����ò���ʱ����
// β����ȡ����   ��������պ������Լ�д�����ʱ����
// ��ȡ��ղ���   ��������պ������Լ���ȡ����ʱ����
// ����Ϊ�˷�ֹ�ж�Ƕ�׵������ݻ���
typedef enum
{
    FIFO_IDLE       = 0x00,                                                     // ����״̬

    FIFO_RESET      = 0x01,                                                     // ����ִ�����û�����
    FIFO_CLEAR      = 0x02,                                                     // ����ִ����ջ�����
    FIFO_WRITE      = 0x04,                                                     // ����ִ��д�뻺����
    FIFO_READ       = 0x08,                                                     // ����ִ�ж�ȡ������
}fifo_execution_enum;                                                           // FIFO ����״̬ ΪǶ��ʹ��Ԥ�� �޷���ȫ���������

typedef enum
{
    FIFO_READ_AND_CLEAN,                                                        // FIFO ������ģʽ ��ȡ������ͷŶ�Ӧ������
    FIFO_READ_ONLY,                                                             // FIFO ������ģʽ ����ȡ
}fifo_operation_enum;

typedef enum
{
    FIFO_DATA_8BIT,                                                             // FIFO ����λ�� 8bit
    FIFO_DATA_16BIT,                                                            // FIFO ����λ�� 16bit
    FIFO_DATA_32BIT,                                                            // FIFO ����λ�� 32bit
}fifo_data_type_enum;

typedef struct
{
    uint8               execution;                                              // ִ�в���
    fifo_data_type_enum type;                                                   // ��������
    void                *buffer;                                                // ����ָ��
    uint32              head;                                                   // ����ͷָ�� ����ָ��յĻ���
    uint32              end;                                                    // ����βָ�� ����ָ��ǿջ��棨����ȫ�ճ��⣩
    uint32              size;                                                   // ����ʣ���С
    uint32              max;                                                    // �����ܴ�С
}fifo_struct;

fifo_state_enum fifo_clear              (fifo_struct *fifo);
uint32          fifo_used               (fifo_struct *fifo);

fifo_state_enum fifo_write_element      (fifo_struct *fifo, uint32 dat);
fifo_state_enum fifo_write_buffer       (fifo_struct *fifo, void *dat, uint32 length);
fifo_state_enum fifo_read_element       (fifo_struct *fifo, void *dat, fifo_operation_enum flag);
fifo_state_enum fifo_read_buffer        (fifo_struct *fifo, void *dat, uint32 *length, fifo_operation_enum flag);
fifo_state_enum fifo_read_tail_buffer   (fifo_struct *fifo, void *dat, uint32 *length, fifo_operation_enum flag);

fifo_state_enum fifo_init               (fifo_struct *fifo, fifo_data_type_enum type, void *buffer_addr, uint32 size);

#endif
