/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          zf_device_tld7002
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.12
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2024-01-22       Seekfree            first version
********************************************************************************************************************/
/********************************************************************************************************************
* 接线定义：
*                  ------------------------------------
*                  TLD7002驱动模块      单片机管脚
*                  RX                  查看 zf_device_tld7002.h 中 TLD7002_UART_RX 宏定义
*                  HSLIL               查看 zf_device_tld7002.h 中 TLD7002_UART_HLSIL 宏定义
*                  GPIN0               查看 zf_device_tld7002.h 中 TLD7002_GPIN0_PIN 宏定义
*                  VCC                 8-15V电源
*                  GND                 电源地
*                  ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_tld7002_h_
#define _zf_device_tld7002_h_


#include "zf_common_typedef.h"


#define TLD7002_UART_INDEX      (UART_1)            // 串口号
#define TLD7002_UART_BAUD       (2000000)           // 波特率
#define TLD7002_UART_RX         (UART1_TX_P33_12)   // TLD7002驱动模块的RX与单片机的TX连接
#define TLD7002_UART_HLSIL      (UART1_RX_P33_13)   // TLD7002驱动模块的HSLI_L与单片机的RX引脚连接

#define TLD7002_GPIN0_PIN       (P32_4)             // GPIN0引脚定义



extern uint16 tld7002_duty[16];

void    tld7002_set_duty        (uint8 tld7002_id);
void    tld7002_callback        (void);
void    tld7002_init            (void);



#endif
