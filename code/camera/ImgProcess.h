/*
 * ImgProcess.h
 *
 *  Created on: 2021年3月29日
 *      Author: 刘原岑
 */

#ifndef CODE_CAMERA_IMGPROCESS_H_
#define CODE_CAMERA_IMGPROCESS_H_
#include "zf_common_headfile.h"

#define IMG_H MT9V03X_H        // 图像高
#define IMG_W MT9V03X_W        //图像宽

#define left_inf1_color 0xFD20 //橙色
#define left_inf2_color 0xAEDC //淡蓝色
#define right_inf1_color 0x8010 //紫罗兰色
#define right_inf2_color 0xFEA0 //金色
#define left_arcinf_color 0xC618 //银色
#define right_arcinf_color 0xF7BB //米色

/*几个音调*/
#define _c 1760
#define _c1 1865
#define _d 1975
#define _d1 2093
#define _e 2217
#define _f 2349
#define _f1 2489
#define _g 2637
#define _g1 2793
#define _a 2960
#define _a1 3135
#define _b 3322
#define Border_Threshold 40

#define First_Patch 96      //底行的补线长度
#define Garage_Patch 142

#define data_lenth 5        //数据包长度
extern uint8 Data_Package[data_lenth];

/*图像参数结构体*/
typedef struct Param
{
    /*基本寻线*/
    int mid_line[IMG_H];      //中线
    int left_line[IMG_H];     //左边界线
    int right_line[IMG_H];        //右边界线
    int up_border[IMG_W];       //上边界线
    int long_line;      //搜线最长行
    int left_border;       //左边界
    int right_border;     //右边界
    int road_start;       //有效起始列
    int road_end;       //有效结束列
    int error;     //循迹偏差
    int garage_count;      //经过车库计数
    int zebracrossing_count;    //斑马线计数
    int fork_count;     //三岔路计数

    /*直弯道识别*/
    float left_slope;        //左边界斜率
    float right_slope;      //右边界斜率
    int left_lose1;        //左边界低行丢线数
    int left_lose2;     //左边界高行丢线数
    int left_outliers;      //左边界向左生长的点个数
    int right_lose1;     //右边界低行丢线数
    int right_lose2;        //右边界高行丢线数
    int right_outliers;      //右边界向右生长的点个数

    /*拐点寻找*/
    int left_inf1;      //左下直角拐点
    int left_inf2;        //左上直角拐点
    int left_arcinf;      //左方圆弧拐点（环岛）
    int left_sinf;      //左方小拐点（三岔）
    int right_inf1;     //右下直角拐点
    int right_inf2;       //右上直角拐点
    int right_arcinf;     //右方圆弧拐点（环岛）
    int right_sinf;     //右方小拐点（三岔）


    /*标志位*/
    int flag;     //总标志位
    int zebracrossing_flag;     //斑马线标志位
    int stop_flag;      //停车标志位
    int curve_flag;       //弯道标志位
    int ramp_flag;      //坡道标志位
    int cross_flag;        //十字路标志位
    int round_flag;      //环岛标志位
    int fork_flag;        //三岔路标志位
    int garage_flag;        //车库标志位
    int direct_flag;     //行驶方向标志位，0表示竖着走，1表示横着走
    int displaly_flag;      //显示标志位，调试用

    /*各种参数*/

    int debug_mode;
    uint32 black_threshold;
    uint32 short_gain;      //短直道速度增益
    uint32 long_gain;       //长直道速度增益
    uint32 fork_freq;

} Img_Param;


void param_init(Img_Param *prm);     //图像参数结构体初始化
void find_startline(uint8 Img[IMG_H][IMG_W], Img_Param *prm); // @suppress("Symbol is not resolved")
void find_upborder(uint8 Img[IMG_H][IMG_W], Img_Param *prm);
void find_zebracrossing (Img_Param *prm);
void find_border(uint8 Img[IMG_H][IMG_W] , Img_Param *prm);        //搜索边界 // @suppress("Symbol is not resolved")
void analysis_border(Img_Param *prm);       //分析边界
void analysis_garage (Img_Param *prm);
void analysis_fork (Img_Param *prm);
void analysis_round (Img_Param *prm);
void judge_road(Img_Param *prm);        //判断路况
void correct_misjudgment(Img_Param *prm);     //修正误判
void patch_line(Img_Param *prm);        //补线操作
void analysis_border_prossed(Img_Param *prm);       //分析处理后的边界
void analysis_midline(Img_Param *prm);      //分析中线
int henghengheng_aaaaa_aaaaaaaaaaa (Img_Param *prm);       //恶臭函数
void display_param(Img_Param *prm);     //显示参数
void display_grey(uint8 *p, Img_Param *prm);
void draw_point(uint16 x, uint16 y, const uint16 color);
void binarize_image(uint8_t image[IMG_H][IMG_W], uint8_t threshold);

#endif
