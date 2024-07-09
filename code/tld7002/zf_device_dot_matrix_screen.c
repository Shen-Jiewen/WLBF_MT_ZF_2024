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

#include "zf_common_interrupt.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_exti.h"
#include "zf_device_tld7002.h"

#include "zf_device_dot_matrix_screen.h"


const uint32 dot_matrix_screen_row_pin[] = {DOT_MATRIX_SCREEN_SR0_PIN, DOT_MATRIX_SCREEN_SR1_PIN, DOT_MATRIX_SCREEN_SR2_PIN, DOT_MATRIX_SCREEN_SR3_PIN, DOT_MATRIX_SCREEN_SR4_PIN, DOT_MATRIX_SCREEN_SR5_PIN, DOT_MATRIX_SCREEN_SR6_PIN};

int8    dot_matrix_screen_data[3];          // 屏幕显示缓冲区
int8    dot_matrix_screen_data_backup[3];   // 屏幕显示缓冲区备份数组，避免显示到一半，显示内容被更新
uint16  dot_matrix_screen_brightness;       // 屏幕亮度


// 点阵屏幕取模数组
const uint8 tld7002_ascii_font_5x7[][7] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  //    0
    { 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x00},  // !  1
    { 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00},  // "  2
    { 0x14, 0x14, 0x3E, 0x14, 0x3E, 0x14, 0x14},  // #  3
    { 0x08, 0x3C, 0x0A, 0x1C, 0x28, 0x1E, 0x08},  // $  4
    { 0x30, 0x32, 0x04, 0x08, 0x10, 0x26, 0x06},  // %  5
    { 0x0C, 0x12, 0x0A, 0x04, 0x2A, 0x12, 0x2C},  // &  6
    { 0x0C, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00},  // '  7
    { 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10},  // (  8
    { 0x04, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04},  // )  9
    { 0x00, 0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00},  // * 10
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00},  // + 11
    { 0x00, 0x00, 0x00, 0x00, 0x18, 0x10, 0x08},  // , 12
    { 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00},  // - 13
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C},  // . 14
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01},  // / 15
    { 0x1C, 0x22, 0x32, 0x2A, 0x26, 0x22, 0x1C},  // 0 16
    { 0x08, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x1C},  // 1 17
    { 0x1C, 0x22, 0x20, 0x10, 0x08, 0x04, 0x3E},  // 2 18
    { 0x3E, 0x10, 0x08, 0x10, 0x20, 0x22, 0x1C},  // 3 19
    { 0x10, 0x18, 0x14, 0x12, 0x3E, 0x10, 0x10},  // 4 20
    { 0x3E, 0x02, 0x1E, 0x20, 0x20, 0x22, 0x1C},  // 5 21
    { 0x18, 0x04, 0x02, 0x1E, 0x22, 0x22, 0x1C},  // 6 22
    { 0x3E, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04},  // 7 23
    { 0x1C, 0x22, 0x22, 0x1C, 0x22, 0x22, 0x1C},  // 8 24
    { 0x1C, 0x22, 0x22, 0x3C, 0x20, 0x10, 0x0C},  // 9 25
    { 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00},  // : 26
    { 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x08, 0x04},  // ; 27
    { 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10},  // < 28
    { 0x00, 0x00, 0x3E, 0x00, 0x3E, 0x00, 0x00},  // = 29
    { 0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04},  // > 30
    { 0x1C, 0x22, 0x20, 0x10, 0x08, 0x00, 0x08},  // ? 31
    { 0x1C, 0x22, 0x20, 0x2C, 0x3A, 0x22, 0x1C},  // @ 32
    { 0x08, 0x14, 0x22, 0x22, 0x3E, 0x22, 0x22},  // A 33
    { 0x1E, 0x22, 0x22, 0x1E, 0x22, 0x22, 0x1E},  // B 34
    { 0x1C, 0x22, 0x02, 0x02, 0x02, 0x22, 0x1C},  // C 35
    { 0x0E, 0x12, 0x22, 0x22, 0x22, 0x12, 0x0E},  // D 36
    { 0x3E, 0x02, 0x02, 0x1E, 0x02, 0x02, 0x3E},  // E 37
    { 0x3E, 0x02, 0x02, 0x1E, 0x02, 0x02, 0x02},  // F 38
    { 0x1C, 0x22, 0x02, 0x3A, 0x22, 0x22, 0x3C},  // G 39
    { 0x22, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x22},  // H 40
    { 0x1C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C},  // I 41
    { 0x38, 0x10, 0x10, 0x10, 0x10, 0x12, 0x0C},  // J 42
    { 0x22, 0x12, 0x0A, 0x06, 0x0A, 0x12, 0x22},  // K 43
    { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x3E},  // L 44
    { 0x22, 0x36, 0x2A, 0x2A, 0x22, 0x22, 0x22},  // M 45
    { 0x22, 0x22, 0x26, 0x2A, 0x32, 0x22, 0x22},  // N 46
    { 0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C},  // O 47
    { 0x1E, 0x22, 0x22, 0x1E, 0x02, 0x02, 0x02},  // P 48
    { 0x1C, 0x22, 0x22, 0x22, 0x2A, 0x12, 0x2C},  // Q 49
    { 0x1E, 0x22, 0x22, 0x1E, 0x0A, 0x12, 0x22},  // R 50
    { 0x3C, 0x02, 0x02, 0x1C, 0x20, 0x20, 0x1E},  // S 51
    { 0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},  // T 52
    { 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C},  // U 53
    { 0x22, 0x22, 0x22, 0x22, 0x22, 0x14, 0x08},  // V 54
    { 0x22, 0x22, 0x22, 0x2A, 0x2A, 0x2A, 0x14},  // W 55
    { 0x22, 0x22, 0x14, 0x08, 0x14, 0x22, 0x22},  // X 56
    { 0x22, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08},  // Y 57
    { 0x3E, 0x20, 0x10, 0x08, 0x04, 0x02, 0x3E},  // Z 58
    { 0x1C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1C},  // [ 59
    { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20},  // \ 60
    { 0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1C},  // ] 61
    { 0x08, 0x14, 0x22, 0x00, 0x00, 0x00, 0x00},  // ^ 62
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E},  // _ 63
    { 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00},  // ` 64
    { 0x00, 0x00, 0x1C, 0x20, 0x3C, 0x22, 0x3C},  // a 65
    { 0x02, 0x02, 0x1A, 0x26, 0x22, 0x22, 0x1E},  // b 66
    { 0x00, 0x00, 0x1C, 0x02, 0x02, 0x22, 0x1C},  // c 67
    { 0x20, 0x20, 0x2C, 0x32, 0x22, 0x22, 0x3C},  // d 68
    { 0x00, 0x00, 0x1C, 0x22, 0x3E, 0x02, 0x1C},  // e 69
    { 0x18, 0x24, 0x04, 0x0E, 0x04, 0x04, 0x04},  // f 70
    { 0x00, 0x3C, 0x22, 0x22, 0x3C, 0x20, 0x1C},  // g 71
    { 0x02, 0x02, 0x1A, 0x26, 0x22, 0x22, 0x22},  // h 72
    { 0x08, 0x00, 0x0C, 0x08, 0x08, 0x08, 0x1C},  // i 73
    { 0x10, 0x00, 0x18, 0x10, 0x10, 0x12, 0x0C},  // j 74
    { 0x02, 0x02, 0x12, 0x0A, 0x06, 0x0A, 0x12},  // k 75
    { 0x0C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C},  // l 76
    { 0x00, 0x00, 0x16, 0x2A, 0x2A, 0x22, 0x22},  // m 77
    { 0x00, 0x00, 0x1A, 0x26, 0x22, 0x22, 0x22},  // n 78
    { 0x00, 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C},  // o 79
    { 0x00, 0x1E, 0x22, 0x22, 0x1E, 0x02, 0x02},  // p 80
    { 0x00, 0x2C, 0x32, 0x32, 0x2C, 0x20, 0x20},  // q 81
    { 0x00, 0x00, 0x1A, 0x26, 0x02, 0x02, 0x02},  // r 82
    { 0x00, 0x00, 0x1C, 0x02, 0x1C, 0x20, 0x1E},  // s 83
    { 0x04, 0x04, 0x0E, 0x04, 0x04, 0x24, 0x18},  // t 84
    { 0x00, 0x00, 0x22, 0x22, 0x22, 0x32, 0x2C},  // u 85
    { 0x00, 0x00, 0x22, 0x22, 0x22, 0x14, 0x08},  // v 86
    { 0x00, 0x00, 0x22, 0x22, 0x2A, 0x2A, 0x14},  // w 87
    { 0x00, 0x00, 0x22, 0x14, 0x08, 0x14, 0x22},  // x 88
    { 0x00, 0x22, 0x22, 0x22, 0x3C, 0x20, 0x1C},  // y 89
    { 0x00, 0x00, 0x3E, 0x10, 0x08, 0x04, 0x3E},  // z 90
    { 0x0C, 0x04, 0x06, 0x02, 0x06, 0x04, 0x0C},  // { 91
    { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},  // | 92
    { 0x0C, 0x08, 0x18, 0x10, 0x18, 0x08, 0x0C},  // } 93
};

//-------------------------------------------------------------------------------------------------------------------
//  函数简介      点阵屏扫描函数
//  参数说明      void
//  返回参数      void
//  使用示例      此函数需要在exti_ch3_ch7_isr中断的ERU_CH7_REQ16_P15_1分支中调用
//-------------------------------------------------------------------------------------------------------------------
void dot_matrix_screen_scan(void)
{
    uint8 i;
    static uint8 entry_num; // 进入此函数的次数
    uint8 display_row_now;  // 当前正在显示第几行

    display_row_now = entry_num / 2;
    if(0 == (entry_num % 2))
    {
        if(0 == display_row_now)
        {
            // 关闭行信号
            gpio_low(dot_matrix_screen_row_pin[DOT_MATRIX_SCREEN_ROW_NUM - 1]);
        }
        else
        {
            // 关闭行信号
            gpio_low(dot_matrix_screen_row_pin[display_row_now - 1]);
        }

        // 更新占空比
        if(7 > display_row_now)
        {
            // 准备第一个点阵屏的数据
            for(i = 0; 5 > i; i++)
            {
                if((tld7002_ascii_font_5x7[dot_matrix_screen_data_backup[0] - ' '][display_row_now]) & ((uint16)1 << (i + 1))) // (i + 1)中的+1 是为了去掉取模的第一列空白
                {
                    tld7002_duty[i] = dot_matrix_screen_brightness;
                }
                else
                {
                    tld7002_duty[i] = 0;
                }
            }

            // 准备第二个点阵屏的数据
            for(; 10 > i; i++)
            {
                if((tld7002_ascii_font_5x7[dot_matrix_screen_data_backup[1] - ' '][display_row_now]) & ((uint16)1 << (i - 5 + 1)))// (i - 5 + 1)中的+1 是为了去掉取模的第一列空白
                {
                    tld7002_duty[i] = dot_matrix_screen_brightness;
                }
                else
                {
                    tld7002_duty[i] = 0;
                }
            }

            // 准备第三个点阵屏的数据
            for(; 15 > i; i++)
            {
                if((tld7002_ascii_font_5x7[dot_matrix_screen_data_backup[2] - ' '][display_row_now]) & ((uint16)1 << (i - 10 + 1)))// (i - 10 + 1)中的+1 是为了去掉取模的第一列空白
                {
                    tld7002_duty[i] = dot_matrix_screen_brightness;
                }
                else
                {
                    tld7002_duty[i] = 0;
                }
            }
        }
        tld7002_set_duty(1);
    }
    else
    {
        // 奇数 开启行信号
        gpio_high(dot_matrix_screen_row_pin[display_row_now]);

        // 采用偶数行关闭行信号 奇数行打开行信号
        // 这是因为当更新TLD7002的通道占空比后，并不会立即生效，需要等待下一个PWM周期才会生效
        // 因此我们更新占空比之后需要等待下一个周期再打开行信号
    }

    entry_num++;
    if((DOT_MATRIX_SCREEN_ROW_NUM * 2) <= entry_num)
    {
        // 全部显示完成 进入次数清零
        entry_num = 0;
        // 更新备份数组
        memcpy((uint8 *)dot_matrix_screen_data_backup, (uint8 *)dot_matrix_screen_data, sizeof(dot_matrix_screen_data_backup));
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  函数简介      点阵屏字符串显示函数
//  参数说明      *str          需要显示的字符串，最多支持显示3个字符
//  返回参数      void
//  使用示例      dot_matrix_screen_show_string("OK");
//-------------------------------------------------------------------------------------------------------------------
void dot_matrix_screen_show_string(const char *str)
{
    uint8 i;
    for(i = 0; i < 3; i++)
    {
        if(0 == str[i])
        {
            break;
        }
        dot_matrix_screen_data[i] = str[i];
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  函数简介      点阵屏亮度调节
//  参数说明      brightness    设置的屏幕亮度 0-10000
//  返回参数      void
//  使用示例      dot_matrix_screen_show_string("OK");
//-------------------------------------------------------------------------------------------------------------------
void dot_matrix_screen_set_brightness(uint16 brightness)
{
    dot_matrix_screen_brightness = brightness;
}

//-------------------------------------------------------------------------------------------------------------------
//  函数简介      点阵屏初始化
//  参数说明      void
//  返回参数      void
//  使用示例      需要在调用
//-------------------------------------------------------------------------------------------------------------------
void dot_matrix_screen_init(void)
{
    // TLD7002芯片初始化
    tld7002_init();

    exti_init(DOT_MATRIX_SCREEN_SYNC_PIN, EXTI_TRIGGER_FALLING);

    gpio_init(dot_matrix_screen_row_pin[0], GPO, 0, GPO_PUSH_PULL);
    gpio_init(dot_matrix_screen_row_pin[1], GPO, 0, GPO_PUSH_PULL);
    gpio_init(dot_matrix_screen_row_pin[2], GPO, 0, GPO_PUSH_PULL);
    gpio_init(dot_matrix_screen_row_pin[3], GPO, 0, GPO_PUSH_PULL);
    gpio_init(dot_matrix_screen_row_pin[4], GPO, 0, GPO_PUSH_PULL);
    gpio_init(dot_matrix_screen_row_pin[5], GPO, 0, GPO_PUSH_PULL);
    gpio_init(dot_matrix_screen_row_pin[6], GPO, 0, GPO_PUSH_PULL);

    // 打开一个通道 此通道不能关闭，用于捕获同步信号
    tld7002_duty[15] = 5000;
    tld7002_set_duty(1);
    system_delay_ms(10);

    // 设置默认亮度
    dot_matrix_screen_set_brightness(dot_matrix_screen_brightness);
    // 清空显示
    dot_matrix_screen_show_string("   ");
}
