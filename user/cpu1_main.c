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
* 文件名称          cpu1_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#pragma section all "cpu1_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中

// **************************** 代码区域 ****************************

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

#define SHOW_RANGE 2
#define POINT_VALID(x, y) (((x) >= 0) && ((x) < MT9V03X_W) && ((y) >= 0) && ((y) < MT9V03X_H))

extern Img_Param prm;      //图像参数结构体

extern int g_mutexFlagBit;
extern int g_lastMutexFlagBit;       //双核互斥锁标志位和上一次标志位,用于屏幕的双核调度  [0]:cpu0占用  [1]:cpu1占用

void core1_main(void)
{
    disable_Watchdog();                     // 关闭看门狗
    interrupt_global_enable(0);             // 打开全局中断
    // 此处编写用户代码 例如外设初始化代码等
    /**********系统初始化***********/
    //摄像头初始化
    mt9v03x_init();

    //图像处理初始化
    param_init(&prm);
    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();                 // 等待所有核心初始化完毕
    while (TRUE)
    {
        // 此处编写需要循环执行的代码
        // 如果图像处理完成标志为真，则进行图像处理
        if(mt9v03x_finish_flag)
        {
            //二值化图像
//            binarize_image(mt9v03x_image,200);
            // 找到图像的起始行
            find_startline(mt9v03x_image, &prm);
            // 如果找到停止线标志为真
            if (prm.stop_flag)
            {
                mt9v03x_finish_flag = 0; // 清除图像处理完成标志
                prm.flag |= 0x04; // 设置参数标志
                prm.road_start = 0; // 路的起始位置设置为0
                prm.road_end = 0; // 路的结束位置设置为0
                prm.round_flag = 0; // 圆形标志设置为0
            }
            else{
                // 如果未找到斑马线和车库标志
                if (!prm.zebracrossing_flag && !prm.garage_flag)
                    find_zebracrossing(&prm); // 寻找斑马线
                // 找到图像的上边界
                find_upborder(mt9v03x_image, &prm);
                // 找到图像的边界
                find_border(mt9v03x_image, &prm);
                mt9v03x_finish_flag = 0; // 清除图像处理完成标志
                // 如果车库标志为真，则分析车库
                if (prm.garage_flag)
                    analysis_garage(&prm);
                // 如果环岛标志为真，则分析环岛
                else if (prm.round_flag)
                    analysis_round(&prm);
                // 否则，分析边界并判断道路
                else{
                    analysis_border(&prm);
                    judge_road(&prm);
                }
                patch_line(&prm); // 补线操作
                analysis_border_prossed(&prm); // 分析处理后的边界
                analysis_midline(&prm); // 分析中线
            }

            //显示画面
            //切换屏幕显示类型
            if(g_lastMutexFlagBit != g_mutexFlagBit && g_mutexFlagBit == 1){
                //屏幕核心调度切换,重新初始化,且只初始化一次
                tft180_clear();
                tft180_set_dir(TFT180_CROSSWISE);
                tft180_set_font(TFT180_6X8_FONT);
                tft180_init();
            }
            if(g_mutexFlagBit == 1){
                //显示画面
                tft180_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W/SHOW_RANGE, MT9V03X_H/SHOW_RANGE, 0);
                //显示巡线的左右边界和中线
                for (int i = MT9V03X_H - 2; i > 0; i -= SHOW_RANGE) {
                    unsigned short int x_left = prm.left_line[i] / SHOW_RANGE;
                    unsigned short int x_right = prm.right_line[i] / SHOW_RANGE;
                    unsigned short int x_mid = prm.mid_line[i] / (SHOW_RANGE * 2);
                    unsigned short int y = i / SHOW_RANGE;

                    //绘制中线和边线
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

                //显示拐点信息
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

                // 左丢线数
                tft180_show_int(ROW_OFFSET(5), COLUMN_OFFSET(9), prm.left_lose2, 2);
                tft180_show_int(ROW_OFFSET(5), COLUMN_OFFSET(11), prm.left_lose1, 2);
                // 右丢线数
                tft180_show_int(ROW_OFFSET(10), COLUMN_OFFSET(9), prm.right_lose2, 2);
                tft180_show_int(ROW_OFFSET(10), COLUMN_OFFSET(11), prm.right_lose1, 2);
                // 向左增长数
                tft180_show_int(ROW_OFFSET(5), COLUMN_OFFSET(12), prm.left_outliers, 2);
                // 向右增长数
                tft180_show_int(ROW_OFFSET(10), COLUMN_OFFSET(12), prm.right_outliers, 2);

                //画出最长行
                tft180_draw_line(0,prm.long_line/2,MT9V03X_W / SHOW_RANGE,prm.long_line/2,RGB565_RED);
                // 画出开始行
                tft180_draw_line(0, prm.road_start/2, MT9V03X_W / SHOW_RANGE, prm.road_start/2, RGB565_GREEN);
                // 画出结束行
                tft180_draw_line(0, prm.road_end/2, MT9V03X_W / SHOW_RANGE, prm.road_end/2, RGB565_YELLOW);

                //显示赛道偏差值
                tft180_show_string(ROW_OFFSET(13), COLUMN_OFFSET(0),"error:");
                tft180_show_int(ROW_OFFSET(13), COLUMN_OFFSET(1), prm.error, 5);
                tft180_show_string(ROW_OFFSET(13), COLUMN_OFFSET(2),"slope:");
                tft180_show_float(ROW_OFFSET(13), COLUMN_OFFSET(3), prm.left_slope , 2, 2);

                //显示环岛元素状态
                tft180_show_int(ROW_OFFSET(2), COLUMN_OFFSET(8), prm.round_flag, 2);

                //显示当前元素的识别状态
//                if(prm.curve_flag == 0){
//                    //长直道[提速+削弱转弯]
//                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "A ");
//                }
//                else if(prm.curve_flag == 1){
//                    //短直道[提速+削弱转弯]
//                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "B ");
//                }
//                else if(prm.curve_flag == 2){
//                    //小弯道[正常速度+增大转弯]
//                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "C ");
//                }
//                else if(prm.curve_flag == 3){
//                    //大弯道[正常速度+增大转弯]
//                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "D ");
//                }
                if(prm.round_flag > 0 && prm.round_flag < 11){
                    //环岛[正常速度+增大转弯]
                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "E");
                    //进环岛和出环岛蜂鸣器响鸣
//                    if(prm.round_flag == 1 || prm.round_flag == ){
//
//                    }
                }
                else if(prm.cross_flag > 0 && prm.cross_flag < 5){
                    //十字路口[正常速度+增大转弯]
                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "F ");
                }
                else{
                    //默认情况[正常速度+正常转弯]
                    tft180_show_string(ROW_OFFSET(0), COLUMN_OFFSET(8), "G ");
                }

            }
        }
        // 此处编写需要循环执行的代码
    }
}
#pragma section all restore
// **************************** 代码区域 ****************************
