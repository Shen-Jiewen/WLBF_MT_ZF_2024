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
* �ļ�����          zf_driver_delay
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.20
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
* 2023-11-28       pudding            �޸���ͨ��ʱ�߼�Ϊ�жϴ����������жϹر���ʹ�üĴ���ѭ����ȡ��ʱ
********************************************************************************************************************/

#include "IfxStm.h"
#include "IFXSTM_CFG.h"
#include "SysSe/Bsp/Bsp.h"
#include "zf_common_interrupt.h"
#include "zf_driver_delay.h"


#define IFX_INTPRIO_STM0_SR0  220
#define IFX_INTPRIO_STM1_SR0  221

static vuint8 stm0_isr_flag = 1;
static vuint8 stm1_isr_flag = 1;

IFX_INTERRUPT(stm0_isr, 0, IFX_INTPRIO_STM0_SR0)
{
    interrupt_global_enable(0);                     // �����ж�Ƕ��
    IfxStm_clearCompareFlag(&MODULE_STM0, IfxStm_Comparator_0);
    stm0_isr_flag = 0;
}

IFX_INTERRUPT(stm1_isr, 0, IFX_INTPRIO_STM1_SR0)
{
    interrupt_global_enable(0);                     // �����ж�Ƕ��
    IfxStm_clearCompareFlag(&MODULE_STM1, IfxStm_Comparator_0);
    stm1_isr_flag = 0;
}
//-------------------------------------------------------------------------------------------------------------------
//  �������      system��ʱ����
//  ����˵��      time            ��ʱһ�ֵ�ʱ�䣨��λΪ���룬�����÷�Χ0-20000000��
//  ���ز���      void
//  ʹ��ʾ��      �����û����ã��û���ʹ��h�ļ��еĺ궨�� // 100Mʱ�� ��С��λΪ 10ns
//-------------------------------------------------------------------------------------------------------------------
void system_delay_10ns (uint32 time)
{
    uint32 interrupt_global_state;

    IfxStm_Index stm_index;

    stm_index = (IfxStm_Index)IfxCpu_getCoreId();

    if(areInterruptsEnabled() == 0)
    {
        IfxStm_waitTicks(IfxStm_getAddress(stm_index), time);
    }
    else
    {
        switch(stm_index)
        {
            case IfxStm_Index_0:
            {
                Ifx_STM *stm_sfr = &MODULE_STM0;
                stm0_isr_flag = 1;
                interrupt_global_state = interrupt_global_disable();     // �ر�ȫ���ж�
                stm_sfr->CMP[0].U = stm_sfr->TIM0.U + time;
                interrupt_global_enable(interrupt_global_state);         // ��ȫ���ж�
                while(stm0_isr_flag);
            }break;
            case IfxStm_Index_1:
            {
                Ifx_STM *stm_sfr = &MODULE_STM1;
                stm1_isr_flag = 1;
                interrupt_global_state = interrupt_global_disable();     // �ر�ȫ���ж�
                stm_sfr->CMP[0].U = stm_sfr->TIM0.U + time;
                interrupt_global_enable(interrupt_global_state);         // ��ȫ���ж�
                while(stm1_isr_flag);
            }break;
            case IfxStm_Index_none: break;
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  �������      system ΢�� ��ʱ����
//  ����˵��      time            ��ʱʱ��  ��λ��us
//  ���ز���      void
//  ʹ��ʾ��      system_delay_us(100);  // ��ʱ100΢��
//-------------------------------------------------------------------------------------------------------------------
void system_delay_us (uint32 time)
{
    if(time > 40000000)
    {
        while(time > 40000000)
        {
            system_delay_10ns(4000000000);
            time = time - 40000000;
        }
        system_delay_10ns(time * 100);
    }
    else
    {
        system_delay_10ns(time * 100);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  �������      system ���� ��ʱ����
//  ����˵��      time            ��ʱʱ��  ��λ��ms
//  ���ز���      void
//  ʹ��ʾ��      system_delay_ms(100);  // ��ʱ100����
//-------------------------------------------------------------------------------------------------------------------
void system_delay_ms (uint32 time)
{
    if(time > 40000)
    {
        while(time > 40000)
        {
            system_delay_10ns(4000000000);
            time = time - 40000;
        }
        system_delay_10ns(time * 100000);
    }
    else
    {
        system_delay_10ns(time * 100000);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  �������      system �ӳٳ�ʼ������
//  ���ز���      void
//  ʹ��ʾ��      system_delay_init();
//-------------------------------------------------------------------------------------------------------------------
void system_delay_init(void)
{
    IfxStm_CompareConfig stmConfig;
    boolean interrupt_state = disableInterrupts();

    stmConfig.comparator          = IfxStm_Comparator_0;
    stmConfig.compareOffset       = IfxStm_ComparatorOffset_0;
    stmConfig.compareSize         = IfxStm_ComparatorSize_32Bits;
    stmConfig.comparatorInterrupt = IfxStm_ComparatorInterrupt_ir0;
    stmConfig.ticks               = 1;
    stmConfig.triggerPriority     = IFX_INTPRIO_STM0_SR0;
    stmConfig.typeOfService       = IfxSrc_Tos_cpu0;

    IfxStm_initCompare(&MODULE_STM0, &stmConfig);
    IfxStm_clearCompareFlag(&MODULE_STM0, IfxStm_Comparator_0);

    stmConfig.comparator          = IfxStm_Comparator_0;
    stmConfig.compareOffset       = IfxStm_ComparatorOffset_0;
    stmConfig.compareSize         = IfxStm_ComparatorSize_32Bits;
    stmConfig.comparatorInterrupt = IfxStm_ComparatorInterrupt_ir0;
    stmConfig.ticks               = 1;
    stmConfig.triggerPriority     = IFX_INTPRIO_STM1_SR0;
    stmConfig.typeOfService       = IfxSrc_Tos_cpu1;

    IfxStm_initCompare(&MODULE_STM1, &stmConfig);
    IfxStm_clearCompareFlag(&MODULE_STM1, IfxStm_Comparator_0);

    restoreInterrupts(interrupt_state);
}

