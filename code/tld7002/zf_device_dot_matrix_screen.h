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
* 文件名称          zf_device_dot_matrix_screen
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
*                  SR0                 查看zf_device_dot_matrix_screen.h 中 DOT_MATRIX_SCREEN_SR0_PIN宏定义
*                  SR1                 查看zf_device_dot_matrix_screen.h 中 DOT_MATRIX_SCREEN_SR1_PIN宏定义
*                  SR2                 查看zf_device_dot_matrix_screen.h 中 DOT_MATRIX_SCREEN_SR2_PIN宏定义
*                  SR3                 查看zf_device_dot_matrix_screen.h 中 DOT_MATRIX_SCREEN_SR3_PIN宏定义
*                  SR4                 查看zf_device_dot_matrix_screen.h 中 DOT_MATRIX_SCREEN_SR4_PIN宏定义
*                  SR5                 查看zf_device_dot_matrix_screen.h 中 DOT_MATRIX_SCREEN_SR5_PIN宏定义
*                  SR6                 查看zf_device_dot_matrix_screen.h 中 DOT_MATRIX_SCREEN_SR6_PIN宏定义
*                  SYNC                查看zf_device_dot_matrix_screen.h 中 DOT_MATRIX_SCREEN_SYNC_PIN宏定义
*                  GND                 电源地
*                  ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_dot_matrix_screen_h_
#define _zf_device_dot_matrix_screen_h_


#include "zf_common_typedef.h"


#define DOT_MATRIX_SCREEN_SYNC_PIN      (ERU_CH7_REQ11_P20_9)   // 使用P20_9接收同步信号

#define DOT_MATRIX_SCREEN_SR0_PIN       (P20_0)
#define DOT_MATRIX_SCREEN_SR1_PIN       (P20_3)
#define DOT_MATRIX_SCREEN_SR2_PIN       (P00_8)
#define DOT_MATRIX_SCREEN_SR3_PIN       (P33_9)                 // 摩托组可以将引脚定义修改为P33_8
#define DOT_MATRIX_SCREEN_SR4_PIN       (P14_4)
#define DOT_MATRIX_SCREEN_SR5_PIN       (P14_5)
#define DOT_MATRIX_SCREEN_SR6_PIN       (P14_6)

#define DOT_MATRIX_SCREEN_ROW_NUM       (7)

void dot_matrix_screen_scan             (void);
void dot_matrix_screen_show_string      (const char *str);
void dot_matrix_screen_set_brightness   (uint16 brightness);
void dot_matrix_screen_init             (void);


#endif

