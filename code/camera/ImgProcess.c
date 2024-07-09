/*
 *  ImgProcess.c     图像处理函数
 *
 *  Created on     2021年3月29日   能够扫描边界并得出偏差循迹
 *  version:    4月4日    增加边界斜率计算，能识别直弯道
 *  version:    4月11日   增加拐点搜索，能初步识别十字路
 *  version:    4月13日   增加环岛状态机，能初步跑完环岛
 *  version:    4月20日   增加斑马线扫描，效果不太理想
 *  version:    4月29日   换用灰度摄像头的二值化处理
 *  version:    5月4日    增加三岔路状态机，能初步在三岔路切换行进方向
 *  version:    6月6日    换用灰度图直接处理的方法
 *  version:    6月9日    优化了环岛状态机的冗余
 *  version:    6月20日   增加入库
 *  version:    6月25日   解决全元素，同时拆分了一些函数
 *  version:    7月1日    环岛状态机简化
 *  version:    7月16日   解决了部分误判，优化了三岔路和车库状态机
 *  Author:     刘原岑         QQ:     398817314
 */

#include "ImgProcess.h"

uint8 Data_Package[data_lenth] = {4, 4, 4, 4, 4};

Img_Param prm;      //图像参数结构体

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     画点
// 参数说明     x               坐标x方向的起点 参数范围 [0, width_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, height_max-1]
// 参数说明     dat             需要显示的颜色
// 返回参数     void
// 使用示例     draw_point(0, 0, RGB565_RED);            // 坐标 0,0 画一个红色的点
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void draw_point(uint16 x, uint16 y, const uint16 color){
    //添加自己屏幕的实现函数
    tft180_draw_point((uint16)x / 2, (uint16)y / 2,color);
}

//二值化图像
void binarize_image(uint8_t image[IMG_H][IMG_W], uint8_t threshold) {
    for (int i = 0; i < IMG_H; i++) {
        for (int j = 0; j < IMG_W; j++) {
            if (image[i][j] >= threshold) {
                image[i][j] = 255;
            } else {
                image[i][j] = 0;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      图像参数结构体初始化，只在最开始初始化的内容
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年3月29日
//  Sample usage:               pram_init(&prm);
//-------------------------------------------------------------------------------------------------------------------
void param_init(Img_Param *prm)
{
    prm->error = 0;
    prm->left_slope = 0.0;
    prm->right_slope = 0.0;
    /*初始化状态机标志位*/
    prm->round_flag = 0;
    prm->garage_count = 0;
    prm->zebracrossing_flag = 0;
    prm->garage_flag = 0;
    prm->fork_flag = 0;
    prm->displaly_flag = 0;
    prm->direct_flag = 0;
    prm->debug_mode = 0;
    prm->fork_freq = 1;
    prm->fork_count = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      扫线前重置部分标志位，例如十字路；并且清除所有拐点
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年4月18日
//  Sample usage:               clean_flag(&prm);
//-------------------------------------------------------------------------------------------------------------------
void clean_flag(Img_Param *prm)
{
    prm->left_lose1 = 0;
    prm->left_lose2 = 0;
    prm->left_outliers = 0;
    prm->right_lose1 = 0;
    prm->right_lose2 = 0;
    prm->right_outliers = 0;
    prm->zebracrossing_count = 0;
    /*清除拐点*/
    prm->left_inf1 = 0;
    prm->left_inf2 = 0;
    prm->left_arcinf = 0;
    prm->left_sinf = 0;
    prm->right_inf1 = 0;
    prm->right_inf2 = 0;
    prm->right_arcinf = 0;
    prm->right_sinf = 0;
    /*清除非状态机的路况标志位*/
    prm->cross_flag = 0;
    prm->ramp_flag  = 0;
    prm->flag =  prm->direct_flag << 3;        //重置行进方向
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      求x的绝对值，灰度图处理调用
//  @param      x
//  @return     x的绝对值
//  @creation date       2021年6月6日
//  Sample usage:               grey_abs(x);
//-------------------------------------------------------------------------------------------------------------------
int abs_(int x)
{
    return x > 0 ? x : -x;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      搜索起始行(直接处理灰度图)，可以确保低行无斑马线干扰，同时检测是否出赛道
//  @param      Img     图像数组
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年6月6日
//  Sample usage:               find_startline_grey(Img,&prm);
//-------------------------------------------------------------------------------------------------------------------
void find_startline(uint8 Img[IMG_H][IMG_W], Img_Param *prm)
{
    clean_flag(prm);
    int h = IMG_H - 1, w;     //搜线行列
    int cmp_x, cmp_y, cmp_xy1, cmp_xy2, sum_x, sum_cmp, threshold;
    int mid = IMG_W / 2;
    do
    {
        h--;
        for (w = mid, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w > 0; w--)     //搜索左边界
        {
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //左右差
            if (cmp_x < 10) continue;       //左右差太小则直接跳过
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //上下差
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //左下右上差
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //右下左上差
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //上下左右和
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //差值和
            threshold = (sum_x >> 2) - Border_Threshold;        //阈值
        }
        prm->left_line[h] = w;      //左边界赋值
        for (w = mid, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w < IMG_W - 1; w++)     //搜索左边界
        {
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //左右差
            if (cmp_x < 10) continue;       //左右差太小则直接跳过
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //上下差
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //左下与右上差
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //右下与左上差
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //上下左右和
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //差值和
            threshold = (sum_x >> 2) - Border_Threshold;        //阈值
        }
        prm->right_line[h] = w;     //右边界赋值
    } while ((prm->right_line[h] - prm->left_line[h] < 30 || Img[h][mid] <= prm->black_threshold) && h > IMG_H - 20);        //判断是否为正确的起始行，超过15行则表示出赛道
    prm->road_start = h ;       //起始行赋值
    prm->left_border = prm->left_line[h] + 3;       //标记有效左边界
    prm->right_border = prm->right_line[h] - 3;     //标记有效右边界
    if (Img[prm->road_start][(prm->left_border + prm->right_border) / 2] <= prm->black_threshold)     //停车检测
        prm->stop_flag = 1;
    else prm->stop_flag = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      搜索上边界(直接处理灰度图)，确定最长扫线行
//  @param      Img     图像数组
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年6月7日
//  Sample usage:               find_startline(Img,&prm);
//-------------------------------------------------------------------------------------------------------------------
void find_upborder(uint8 Img[IMG_H][IMG_W], Img_Param *prm)
{
    int h, w ,longest = prm->road_start;
    int cmp_x, cmp_y, cmp_xy1, cmp_xy2, sum_x, sum_cmp, threshold;
    for (w = prm->left_border; w < prm->right_border; w++)      //搜索上边界
    {
        for (h = prm->road_start - 2, sum_cmp = 0, threshold = 1; sum_cmp < threshold && h > 0 &&  Img[h][w] >= prm->black_threshold; h--)
        {
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //上下差
            if (cmp_y < 10) continue;       //上下差太小则直接跳过
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //左右差
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //左下与右上差
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //右下与左上差
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //上下左右和
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //差值和
            threshold = (sum_x >> 2) - Border_Threshold;        //阈值
        }
        prm->up_border[w] = h;        //上边界赋值
    }
        for(w = prm->left_border + 1; w <= prm->right_border - 1; w++)      //搜索最长行
        {
            if (prm->up_border[w] < longest && prm->up_border[w] - prm->up_border[w - 1] < 5 && prm->up_border[w] - prm->up_border[w + 1] < 5)
            {
                longest = prm->up_border[w];
                prm->long_line = w;
            }
        }
}

void find_zebracrossing (Img_Param *prm)
{
    int w;
    for (w = prm->left_border + 5; w + 5 <=prm->right_border; w++)        //搜索斑马线
    {
        if (prm->up_border[w - 1] - prm->up_border[w + 1] > 10)
            prm->zebracrossing_count ++;
    }
    if (prm->zebracrossing_count > 9)
    {
        if (prm->garage_count && (prm->fork_count == prm->fork_freq << 2 || prm->debug_mode))
            prm->zebracrossing_flag = 2;
        else if (prm->fork_count == prm->fork_freq << 1 || prm->debug_mode)
            prm->zebracrossing_flag = 1;
//        prm->displaly_flag = 1;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      搜索边界函数
//  @param      Img     图像数组
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年6月7日
//  Sample usage:               find_border(Img,&prm);
//-------------------------------------------------------------------------------------------------------------------
void find_border(uint8 Img[IMG_H][IMG_W], Img_Param *prm)
{
    int h = prm->road_start - 1, w, mid;
    int cmp_x, cmp_y, cmp_xy1, cmp_xy2, sum_x, sum_cmp, threshold;
    int left_weight = 1, right_weight = 1, total = 1;
    if (prm->round_flag == 3 || prm->round_flag == 5 || prm->garage_flag ==1 || prm->garage_flag ==3 || prm->fork_flag == 1 || prm->fork_flag == 3)        //入左环岛、左三岔、左车库时往内侧搜线
    {
        left_weight = 3;
        right_weight = 1;
        total = 2;
    }
    else if (prm->round_flag == 4 || prm->round_flag == 6 || prm->garage_flag == 2 || prm->garage_flag ==4 || prm->fork_flag == 2 || prm->fork_flag == 4)        //入右环岛、右三岔、右车库时往内侧搜线
    {
        left_weight = 1;
        right_weight = 3;
        total = 2;
    }
    else    //以最长行为中心搜线
    {
        while (h > prm->up_border[prm->long_line] + 3 && Img[h][prm->long_line] >= prm->black_threshold)
        {
            for (w = prm->long_line - 1, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w > 0; w--)     //搜索左边界
            {
                cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //左右差
                if (cmp_x < 10)     continue;       //左右差太小则直接跳过
                cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //上下差
                cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //左下右上差
                cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //右下左上差
                sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //上下左右和
                sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //差值和
                threshold = (sum_x>>2) - Border_Threshold;        //阈值
            }
            if(w < 4 && h >= 64)   prm->left_lose1++;       //低行丢线
            else if(w < 4 && h >= 15) prm->left_lose2++;        //高行丢线
            else if(h < 8 && abs_(w - prm->left_line[h + 1]) > 15)   break;        //异常扫线终止
            if (w < prm->left_line[h + 1])  prm->left_outliers++;
            prm->left_line[h] = w;      //左边界赋值
            for (w = prm->long_line + 1, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w < IMG_W - 1; w++)     //搜索左边界
            {
                cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //左右差
                if (cmp_x < 10)     continue;       //左右差太小则直接跳过
                cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //上下差
                cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //左下与右上差
                cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //右下与左上差
                sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //上下左右和
                sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //差值和
                threshold = (sum_x>>2) - Border_Threshold;        //阈值
            }
            if (w > IMG_W - 5 && h >= 64)   prm->right_lose1++;        //低行丢线
            else if (w > IMG_W - 5 && h >= 15) prm->right_lose2++;     //高行丢线
            else if(h < 5
                    && abs_(prm->right_line[h + 1] - w) > 15)   break;       //异常扫线终止
            if (w > prm->right_line[h + 1])  prm->right_outliers++;
            prm->right_line[h] = w;     //右边界赋值
            h--;
        }
    }
    h++;
    do
    {
        mid = ((left_weight * prm->left_line[h]) + right_weight * prm->right_line[h]) >> total;
        if (h < prm->road_start  - 10)
        {
            cmp_x = abs_(Img[h][mid + 1] - Img[h][mid - 1]) ;        //左右差
            cmp_y = abs_(Img[h + 1][mid] - Img[h - 1][mid]);      //上下差
            cmp_xy1 = abs_(Img[h + 1][mid - 1] - Img[h - 1][mid + 1]);        //左下与右上差
            cmp_xy2 = abs_(Img[h + 1][mid + 1] - Img[h - 1][mid - 1]);        //右下与左上差
            sum_x =  Img[h][mid + 1] + Img[h][mid - 1] + Img[h - 1][mid] + Img[h + 1][mid];     //上下左右和
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //差值和
            threshold = (sum_x >> 2) - Border_Threshold;        //阈值
            if (sum_cmp > threshold || Img[h][mid] < prm->black_threshold)      break;        //停止扫线判断
        }
        h--;
        for (w = mid - 1, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w > 0; w--)     //搜索左边界
        {
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //左右差
            if (cmp_x < 10)     continue;       //左右差太小则直接跳过
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //上下差
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //左下右上差
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //右下左上差
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //上下左右和
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //差值和
            threshold = (sum_x >> 2) - Border_Threshold;        //阈值
        }
        if(w < 4 && h >= 30)   prm->left_lose1++;
        else if(w < 4 && h >= 15) prm->left_lose2++;
        else if(h < 8 && abs_(w - prm->left_line[h + 1]) > 15)   break;        //异常扫线终止
        if (w < prm->left_line[h + 1] - 5)  prm->left_outliers++;
        prm->left_line[h] = w;      //左边界赋值
        for (w = mid + 1, sum_cmp = 0, threshold = 1; sum_cmp < threshold && w < IMG_W - 1; w++)     //搜索左边界
        {
            cmp_x = abs_(Img[h][w + 1] - Img[h][w - 1]) ;        //左右差
            if (cmp_x < 10)     continue;       //左右差太小则直接跳过
            cmp_y = abs_(Img[h + 1][w] - Img[h - 1][w]);      //上下差
            cmp_xy1 = abs_(Img[h + 1][w - 1] - Img[h - 1][w + 1]);        //左下与右上差
            cmp_xy2 = abs_(Img[h + 1][w + 1] - Img[h - 1][w - 1]);        //右下与左上差
            sum_x =  Img[h][w + 1] + Img[h][w - 1] + Img[h - 1][w] + Img[h + 1][w];     //上下左右和
            sum_cmp = cmp_x + cmp_y + cmp_xy1 + cmp_xy2;       //差值和
            threshold = (sum_x >> 2) - Border_Threshold;        //阈值
        }
        if (w > IMG_W - 5 && h >= 30)   prm->right_lose1++;
        else if (w > IMG_W - 5 && h >= 15) prm->right_lose2++;
        else if(h < 5 && abs_(prm->right_line[h + 1] - w) > 15)   break;       //异常扫线终止
        if (w > prm->right_line[h + 1] + 5)  prm->right_outliers++;
        prm->right_line[h] = w;     //右边界赋值
    }   while(h > 0);
    prm -> road_end = h;      //记录结束行
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      分析边界，寻找拐点，确定路况
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年4月11日
//  Sample usage:               analysis_border(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_border(Img_Param *prm)
{
    int i;
    for (i = prm->road_start;  i - 9 > prm->road_end; i--)
    {
        if (prm->left_line[i - 3] - prm->left_line[i - 6] > 12 && prm->left_line[i - 3] < IMG_W * 3 / 4 && i - 3 > prm->road_end + 25)        //如果出现急剧的向外跳变则判断是否为左下拐点
        {
            if (prm->left_line[i - 3] - prm->left_line[i] < 6 && prm->left_line[i] - prm->left_line[i - 3] < 3 && prm->left_line[i - 6] < IMG_W / 5 && prm->right_line[i] - prm->left_line[i] > 30)        //拐点前的边界连续则确认为直角拐点
            {
                prm->left_inf1 = i - 3;
                break;
            }
        }
    }
    for (i = prm->road_start;  i - 9 > prm->road_end; i--)
    {
        if (prm->right_line[i - 6] - prm->right_line[i - 3] > 12 && prm->right_line[i - 3] > IMG_W / 4 && i - 3 >prm->road_end + 25)        //如果出现急剧的向外跳变则判断是否为右下拐点
        {
            if (prm->right_line[i] - prm->right_line[i - 3] < 6 && prm->right_line[i - 3] - prm->right_line[i] < 3 && prm->right_line[i - 6] > IMG_W * 4 / 5 && prm->right_line[i] - prm->left_line[i] > 30)        //拐点前的边界连续则确认为直角拐点
            {
                prm->right_inf1 = i - 3;
                break;
            }
        }
    }
    for (i = (prm->left_inf1 != 0 ? prm->left_inf1 - 10 : prm->road_start);  i - 9 > prm->road_end; i--)
    {
        if (prm->left_line[i - 3] - prm->left_line[i] > 12 && prm->left_line[i - 3] < IMG_W / 2)      //如果出现急剧的向内跳变则判断是否为左上拐点
        {
            if (prm->left_line[i - 3] - prm->left_line[i - 3] < 6 && prm->left_line[i - 3] - prm->left_line[i - 6] < 3 && prm->right_line[i - 6] - prm->left_line[i - 6] > 15)     //拐点后的边界连续则确认为直角拐点
            {
                prm->left_inf2 = i - 3;
                break;
            }
        }
    }
    for (i = (prm->right_inf1 != 0 ? prm->right_inf1 - 10 : prm->road_start);  i - 9> prm->road_end; i--)
    {
        if (prm->right_line[i] - prm->right_line[i - 3] > 12 && prm->right_line[i - 3] > IMG_W / 2)        //如果出现急剧的向内跳变则判断是否为右上拐点
        {
            if (prm->right_line[i - 3] - prm->right_line[i - 6] < 6 && prm->right_line[i - 6] - prm->right_line[i - 3] < 3 && prm->right_line[i - 6] - prm->left_line[i - 6] > 15)     //拐点后的边界连续则确认为直角拐点
            {
                prm->right_inf2 = i - 3;
                break;
            }
        }
    }
    if (!prm->zebracrossing_flag)       //无斑马线的条件下寻找三岔路的小拐点和环岛的圆弧拐点
    {
        if ((prm->left_inf1 > IMG_H / 3 || prm->left_lose1 > 15) && prm->road_end < 10)        //寻找左圆弧拐点判断左环岛
        {
            for (i = (prm->left_inf1 != 0 ? prm->left_inf1 - 10 : prm->road_start - 10);  i - 8 > prm->road_end; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 0 &&
                    prm->left_line[i - 3] > prm->left_line[i - 6] &&
                    prm->left_line[i - 6] > prm->left_line[i - 8] &&
                    prm->left_line[i - 6] > 0 &&
                    prm->left_line[i - 3] > IMG_W / 5 &&
                    prm->left_line[i - 3] < IMG_W * 3 / 4 &&
                    prm->right_line[i - 3] - prm->left_line[i - 3] > 20) {
                        prm->left_arcinf = i - 3;
                        break;
                }
            }
        }
        if ((prm->right_inf1 > IMG_W / 3 || prm->right_lose1 > 15) && prm->road_end < 10)        //寻找右圆弧拐点判断右环岛
        {
            for (i = (prm->right_inf1 != 0 ? prm->right_inf1 - 10 : prm->road_start - 10);  i - 8 > prm->road_end; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 0 &&
                    prm->right_line[i - 6] - prm->right_line[i - 3] > 0 &&
                    prm->right_line[i - 8] - prm->right_line[i - 6] > 0 &&
                    prm->right_line[i - 3] < IMG_W * 4 / 5 &&
                    prm->right_line[i - 3] > IMG_W / 4 &&
                    prm->right_line[i - 3] - prm->left_line[i - 3] > 20)     //如果出现一个突起这判断是否为圆弧拐点
                {
                    prm->right_arcinf = i - 3;
                    break;
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      车库状态机，处理入库
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年6月25日
//  Sample usage:               analysis_garage(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_garage(Img_Param *prm)
{
    int i;
    switch (prm->garage_flag)
    {
        case 1:
            for (i = prm->road_start;  i - 9 > prm->road_end; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i - 6] > 12)        //如果出现急剧的向外跳变则判断是否为左下拐点
                {
                    if (prm->left_line[i - 3] - prm->left_line[i] < 6 && prm->left_line[i] - prm->left_line[i - 3] < 3)        //拐点前的边界连续则确认为直角拐点
                    {
                        prm->left_inf1 = i - 3;
                        break;
                    }
                }
            }
            if (!prm->left_inf1 && prm->left_lose1 > 20)
                prm->garage_flag = 3;
            break;
        case 2:
            for (i = prm->road_start;  i - 9 > prm->road_end; i--)        //寻找右侧的第一个拐点
            {
                if (prm->right_line[i - 6] - prm->right_line[i - 3] > 12)        //如果出现急剧的向外跳变则判断是否为右下拐点
                {
                    if (prm->right_line[i] - prm->right_line[i - 3] < 6 && prm->right_line[i - 3] - prm->right_line[i] < 3)        //拐点前的边界连续则确认为直角拐点
                    {
                        prm->right_inf1 = i - 3;
                        break;
                    }
                }
            }
            if (!prm->right_inf1 && prm->right_lose1 > 20)
                prm->garage_flag = 4;
            break;
        case 3:
            for (i = prm->road_start;  i -  9 > prm->road_end; i--)
            {
                if (prm->right_line[i - 3] - prm->right_line[i - 6] > 10 && prm->right_line[i] - prm->right_line[i - 3] < 6 && prm->right_line[i - 3] - prm->right_line[i] < 3)
                {
                        prm->right_inf2 = i - 6;
                        break;
                }
            }
            if (prm->road_end > 50 && !prm->right_inf2 && prm->left_lose1 + prm->left_lose2 + prm->right_lose1 < 5)
            {
                prm->garage_flag = 5;
                prm->stop_flag = 1;
            }
            break;
        case 4:
              for (i = prm->road_start;  i -  9 > prm->road_end; i--)
              {
                  if (prm->left_line[i - 6] - prm->left_line[i - 3] > 10 && prm->left_line[i - 3] - prm->left_line[i] < 6 && prm->left_line[i] - prm->left_line[i - 3] < 3)
                  {
                          prm->left_inf2 = i - 6;
                          break;
                  }
              }
              if (prm->road_end > 50 && !prm->left_inf2 && prm->left_lose1 + prm->right_lose1 + prm->right_lose2 < 5)
              {
                  prm->garage_flag = 5;
                  prm->stop_flag = 1;
              }
              break;
        case 5:     //停车
            prm->stop_flag = 1;
            break;
        default:    break;
    }
    if (prm->garage_flag == 5)  prm->flag |= 0x04;
    else if (prm->garage_flag > 2)   prm->flag |= 0x03;
    else prm->flag |= 0x02;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      三岔路状态下的拐点寻找
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年6月25日
//  Sample usage:               analysis_fork(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_fork (Img_Param *prm)
{
    int i;
    switch (prm->fork_flag)
    {
        case 1:
            for (i = prm->road_start;  i - 8 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->right_line[i - 2] < prm->right_line[i - 4] && prm->right_line[i - 6] > prm->right_line[i - 4] && prm->right_line[i - 2] > IMG_W / 2)
               {
                   prm->right_inf1 = i - 2;
                   break;
               }
            }
            for (i = prm->road_start;  i - 10 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 10)
                {
                        prm->right_inf2 = i - 3;
                        break;
                }
            }
            if (prm->direct_flag == 1)
            {
                if (!prm->right_inf1 &&  prm->right_inf2 > 35 && prm->right_lose2 < 10)
                {
                    prm->direct_flag = 0;
                    prm->fork_flag = 3;
                }
            }
            else
            {
                if ((!prm->right_inf1 || prm->right_inf1 > 50) && prm->right_lose1 > 15 && prm->right_inf2 > 30 && prm->right_lose2 < 10)
                {
                    prm->direct_flag = 1;
                    prm->fork_flag = 3;
                }
            }
            break;
        case 2:
            for (i = prm->road_start;  i - 8 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->left_line[i - 2] > prm->left_line[i - 4] && prm->left_line[i - 4] > prm->left_line[i - 6] && prm->left_line[i - 2] < IMG_W /2)
               {
                   prm->left_inf1 = i - 2;
                   break;
               }
            }
            for (i = prm->road_start;  i - 10 > prm->road_end  && i > IMG_H / 3; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 10)
                {
                    prm->left_inf2 = i - 3;
                    break;
                }
            }
            if (prm->direct_flag == 1)
            {
                if (!prm->left_inf1 && prm->left_inf2 > 35 && prm->left_lose2 < 10)
                {
                    prm->direct_flag = 0;
                    prm->fork_flag = 4;
                }
            }
            else
            {
                if ((!prm->left_inf1|| prm->left_inf1 > 50) && prm->left_lose1 > 15 && prm->left_inf2 > 30 && prm->left_lose2 < 10)
                {
                    prm->direct_flag = 1;
                    prm->fork_flag = 4;
                }
            }
            break;
        case 3:
            for (i = prm->road_start;  i - 10 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 10)
                {
                        prm->right_inf2 = i - 3;
                        break;
                }
            }
            if(!prm->right_inf2 && prm->right_lose1 < 2)
                prm->fork_flag = 0;
            break;
        case 4:
            for (i = prm->road_start;  i - 10 > prm->road_end && i > IMG_H / 3; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 10)
                {
                    prm->left_inf2 = i - 3;
                    break;
                }
            }
            if (!prm->left_inf2 && prm->left_lose1 < 2)
                prm->fork_flag = 0;
            break;
        default: break;
    }
    prm->flag |= 0x01;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      环岛状态下的拐点寻找，优化后的状态机
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年7月1日
//  Sample usage:               analysis_round(&prm);  由于直接灰度图处理可能会有一些干扰，状态切换时务必加上其他约束条件
//-------------------------------------------------------------------------------------------------------------------
void analysis_round(Img_Param *prm)
{
    int i, temp;
    switch (prm->round_flag)
    {
        /* 环岛状态1（左环岛为例）
         * 拐点搜索：先搜索左下拐点，根据是否有左下拐点决定圆弧拐点的搜索起始行
         * 补线策略：左下拐点与左圆弧拐点相连
         * 状态切换：左下拐点消失则跳转到状态2
         * */
        case 1:     //左环岛1
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)        //寻找左下拐点
            {
                if (prm->left_line[i - 3] - prm->left_line[i - 6] > 12)        //如果出现急剧的向外跳变则判断是否为左下拐点
                {
                    if (prm->left_line[i - 3] - prm->left_line[i] < 6 && prm->left_line[i] - prm->left_line[i - 3] < 3)        //拐点前的边界连续则确认为直角拐点
                    {
                        prm->left_inf1 = i - 3;
                        break;
                    }
                }
            }
            for (i = (prm->left_inf1 == 0 ? prm->road_start - 6 : prm->left_inf1 - 10);  i - 10 > prm->road_end; i--)
            {
                if (prm->left_line[i] <= prm->left_line[i - 3] && prm->left_line[i - 6] < prm->left_line[i - 3] && prm->left_line[i - 3] > 10)     //如果出现一个突起这判断是否为圆弧拐点
                {
                    prm->left_arcinf = i - 3;
                    break;
                }
            }
            if (!prm->left_inf1)
                prm->round_flag = 3;
            break;
        case 2:     //右环岛1
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)          //寻找右下拐点
            {
                if (prm->right_line[i - 6] - prm->right_line[i - 3] > 12)        //如果出现急剧的向外跳变则判断是否为右下拐点
                {
                    if (prm->right_line[i] - prm->right_line[i - 3] < 6 && prm->right_line[i - 3] - prm->right_line[i] < 3)        //拐点前的边界连续则确认为直角拐点
                    {
                        prm->right_inf1 = i - 3;
                        break;
                    }
                }
            }
            for (i = (prm->right_inf1 == 0 ? prm->road_start - 6 : prm->right_inf1 - 10);  i - 10 > prm->road_end; i--)
            {
                if (prm->right_line[i] >= prm->right_line[i - 3] && prm->right_line[i - 6] > prm->right_line[i - 3] && prm->right_line[i - 3] < IMG_W - 11)
                {
                    prm->right_arcinf = i - 3;
                    break;
                }
            }
            if (!prm->right_inf1)
                prm->round_flag = 4;
            break;
        /* 环岛状态2（左环岛为例）
         * 拐点搜索：搜索左圆弧拐点和左上拐点
         * 补线策略：左圆弧拐点往下拉线，拐点对应行的右边界往左侧尽头连接（可调整补线斜率以改善路径）
         * 状态切换：搜索到右上拐点则跳转到状态3
         * */
        case 3:     //左环岛2
            for (i = prm->road_start - 6;  i - 10 > prm->road_end; i--)
            {
                if (prm->left_line[i] <= prm->left_line[i - 3] && prm->left_line[i - 6] < prm->left_line[i - 3] && prm->left_line[i - 3] > 10)
                {
                    prm->left_arcinf = i - 3;
                    break;
                }
            }
            for (i = prm->road_start;  i - 3 > prm->road_end; i--)
            {
                if(prm->right_line[i] - prm->right_line[i - 1] > 15 && prm->right_line[i - 3] < prm->right_line[i - 1])
                {
                    prm->right_inf2 = i - 1;
                    break;
                }
            }
            if (prm->right_inf2 && (!prm->left_arcinf || prm->left_arcinf > 40))
                prm->round_flag = 5;
            break;
        case 4:     //右环岛2
            for (i = prm->road_start - 6;  i - 10 > prm->road_end; i--)
            {
                if (prm->right_line[i] >= prm->right_line[i - 3] && prm->right_line[i - 6] > prm->right_line[i - 3] && prm->right_line[i - 3] < IMG_W - 11)
                {
                    prm->right_arcinf = i - 3;
                    break;
                }
            }
            for (i = prm->road_start;  i - 3 > prm->road_end; i--)
              {
                  if(prm->left_line[i - 1] - prm->left_line[i] > 15 && prm->left_line[i - 3] > prm->left_line[i - 1])
                  {
                      prm->left_inf2 = i - 1;
                      break;
                  }
              }
            if (prm->left_inf2 && (!prm->right_arcinf || prm->right_arcinf > 40))
                prm->round_flag = 6;
            break;
            /* 环岛状态3（左环岛为例）
             * 拐点搜索：搜索右上拐点
             * 补线策略：右上拐点往右下起始位置补线（可根据拐点所在行决定以斜率拉线或固定两点连线）
             * 状态切换：右上拐点消失则跳转到状态4
             * */
        case 5:     //左环岛3
            for (i = prm->road_start;  i - 3 > prm->road_end; i--)
            {
                if(prm->right_line[i] - prm->right_line[i - 1] > 15)
                {
                    prm->right_inf2 = i - 1;
                    break;
                }
            }
            if(!prm->right_inf2 && prm->right_lose1 < 2 && prm->left_lose1 + prm->left_lose2 > 15)
                prm->round_flag = 7;
            break;
        case 6:     //右环岛3
            for (i = prm->road_start;  i - 3 > prm->road_end; i--)
              {
                  if(prm->left_line[i - 1] - prm->left_line[i] > 15)
                  {
                      prm->left_inf2 = i - 1;
                      break;
                  }
              }
            if(!prm->left_inf2 && prm->left_lose1 < 2 && prm->right_lose1 + prm->right_lose2 > 15)
                    prm->round_flag = 8;
            break;
            /* 环岛状态4（左环岛为例）
             * 拐点搜索：搜索右下拐点，同时记录左上方补线行数
             * 补线策略：右下拐点往左上方拉线（可调整补线斜率以改善路径）
             * 状态切换：右下拐点先出现再消失后跳转到状态5
             * */
        case 7:
            for (i = prm->road_start;  i - 9 > prm->road_end; i--)        //寻找右下拐点
            {
                if (prm->right_line[i - 9] - prm->right_line[i - 3] > 12)
                {
                    if (prm->right_line[i - 6] > prm->right_line[i - 3] && prm->right_line[i] > prm->right_line[i - 3])
                    {
                        prm->right_inf1 = i - 3;
                        break;
                    }
                }
            }
            if (prm->right_inf1)        //找到下拐点再确定补线行数
            {
                temp = IMG_W  - 1;
                for (i = prm->right_inf1 - 1;  i > prm->road_end; i--)     //寻找左边线的极值用于补线，这个不是真的拐点
                {
                    if (prm->left_line[i] <= temp)
                    {
                        prm->right_inf2 = i;
                        temp = prm->left_line[i];
                    }
                }
            }
            if (!prm->right_inf1 &&  prm->right_lose1 > 20)
                prm->round_flag = 9;
            break;
        case 8:
            for (i = prm->road_start;  i - 9 > prm->road_end; i--)      //寻找左下拐点
            {
                if (prm->left_line[i - 3] - prm->left_line[i - 9] > 12 )
                {
                    if (prm->left_line[i - 3] > prm->left_line[i - 6] && prm->left_line[i - 3] > prm->left_line[i])
                    {
                        prm->left_inf1 = i - 3;
                        break;
                    }
                }
            }
            if (prm->left_inf1)     //找到下拐点再确定补线行数
            {
                temp = 0;
                for (i = prm->left_inf1 - 1;  i > prm->road_end; i--)     //寻找右边线的极值用于补线
                {
                    if (prm->right_line[i] >= temp)
                    {
                        prm->left_inf2 = i;
                        temp = prm->right_line[i];
                    }
                }
            }
            if (!prm->left_inf1 &&  prm->left_lose1 > 20)
                prm->round_flag = 10;
            break;
            /* 环岛状态5（左环岛为例）
             * 拐点搜索：搜索左上拐点，同时记录左上方补线行数
             * 补线策略：右下方往左上方拉线（可调整补线斜率以改善路径）
             * 状态切换：搜索到左上拐点则跳转到状态6
             * */
        case 9:     //左环岛5
            temp = IMG_W - 1;
            for (i = prm->road_start - 20;  i > prm->road_end; i--)
            {
                if (prm->left_line[i] <= temp)
                {
                    prm->right_inf2 = i;
                    temp = prm->left_line[i];
                }
            }
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 12 && prm->left_line[i - 6] - prm->left_line[i - 3] < 6 && prm->left_line[i - 3] - prm->left_line[i - 6] < 3)
                {
                    prm->left_inf2 = i - 3;
                    break;
                }
            }
            if (prm->left_inf2)
                prm->round_flag = 11;
            break;
        case 10:
            temp = 0;
            for (i = prm->road_start - 15;  i > prm->road_end; i--)     //寻找右边线的极值用于补线
            {
                if (prm->right_line[i] >= temp)
                {
                    prm->left_inf2 = i;
                    temp = prm->right_line[i];
                }
            }
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 12 && prm->right_line[i - 3] - prm->right_line[i - 6] < 6 && prm->right_line[i - 6] - prm->right_line[i - 3] < 3)
                {
                    prm->right_inf2 = i - 3;
                    break;
                }
            }
            if (prm->right_inf2)
               prm->round_flag = 12;
            break;
            /* 环岛状态6（左环岛为例）
             * 拐点搜索：搜索左上拐点
             * 补线策略：左上拐点往左下拉线
             * 状态切换：左上拐点消失则跳转出环岛状态
             * */
        case 11:
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)
            {
                if (prm->left_line[i - 3] - prm->left_line[i] > 12 && prm->left_line[i - 6] - prm->left_line[i - 3] < 6 && prm->left_line[i - 3] - prm->left_line[i - 6] < 3)
                {
                    prm->left_inf2 = i - 3;
                    break;
                }
            }
            if(!prm->left_inf2 && prm->left_lose1 < 4 && prm->left_lose2 < 4)
                prm->round_flag = 0;
            break;
        case 12:
            for (i = prm->road_start;  i - 6 > prm->road_end; i--)
            {
                if (prm->right_line[i] - prm->right_line[i - 3] > 12 && prm->right_line[i - 3] - prm->right_line[i - 6] < 6 && prm->right_line[i - 6] - prm->right_line[i - 3] < 3)
                {
                    prm->right_inf2 = i - 3;
                    break;
                }
            }
            if(!prm->right_inf2 && prm->right_lose1 < 4 && prm->right_lose2 < 4)
                prm->round_flag = 0;
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      根据找到的拐点等情况判断路况
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年4月21日
//  Sample usage:               judge_road(*prm);
//-------------------------------------------------------------------------------------------------------------------
void judge_road(Img_Param *prm)
{
    if (prm->zebracrossing_flag == 1)
    {
        if (prm->left_inf1 && prm->left_inf2)
        {
            prm->right_inf1 = prm->left_inf1;
            prm->right_inf2 = prm->left_inf2;
            prm->garage_count = 1;
        }
        else if (prm->left_inf2)
        {
            prm->right_inf2 = prm->left_inf2;
            prm->garage_count = 1;
        }
        else if (prm->right_inf1 && prm->right_inf2)
        {
            prm->left_inf1 = prm->right_inf1;
            prm->left_inf2 = prm->right_inf2;
            prm->garage_count = 1;
        }
        else if (prm->right_inf2)
        {
            prm->left_inf2 = prm->right_inf2;
            prm->garage_count = 1;
        }
        else if (prm->left_lose1 + prm->right_lose1 < 5)
            prm->zebracrossing_flag = 0;
    }
    if (prm->left_inf1 && prm -> right_inf1 && prm->left_inf2 && prm -> right_inf2)        //正入十字
        prm->cross_flag = 1;
    else if (prm->left_inf1 && prm->left_inf2 && prm -> right_inf2)       //左斜入十字
        prm->cross_flag = 2;
    else if (prm->right_inf1 && prm->right_inf2 && prm->left_inf2)        //右斜入十字
        prm->cross_flag = 3;
    else if (prm->left_inf2 && prm -> right_inf2 && prm->right_line[prm->right_inf2] - prm->left_line[prm->left_inf2] > 30)      //十字中
        prm->cross_flag = 4;
    else if (prm->zebracrossing_flag == 2 && prm->left_inf1)     //左入库
    {
        prm->garage_flag = 1;
        prm->zebracrossing_flag = 0;
    }
    else if (prm->zebracrossing_flag == 2 && prm->right_inf1)       //右入库
    {
        prm->garage_flag = 2;
        prm->zebracrossing_flag = 0;
    }
    else if (prm->left_arcinf && !prm->right_inf1 && !prm->right_inf2 && prm->right_slope > -0.8 && prm->right_outliers < 10
           && prm->right_lose1 + prm->right_lose2 < 5)     //左环岛
    {
        prm->round_flag = 1;
        prm->displaly_flag = 1;
    }

    else if (prm->right_arcinf && !prm->left_inf1 && !prm->left_inf2 && prm->left_slope < 0.8 && prm->left_outliers < 10
            && prm->left_lose1 + prm->left_lose2 < 5)     //右环岛
    {
        prm->round_flag = 2;
        prm->displaly_flag = 1;
    }
}

void correct_misjudgment(Img_Param *prm)
{
    if (prm->round_flag == 1 && prm->right_outliers > 3 && prm->right_lose1 + prm->right_lose2 > 3)
    {
            prm->round_flag = 0;
    }
    else if (prm->round_flag == 2 && prm->left_outliers > 3 && prm->left_lose1 + prm->left_lose2 > 3)
    {
            prm->round_flag = 0;
    }
    else if (prm->round_flag == 3 && prm->left_lose1 + prm->left_lose2 < 3)
    {
            prm->round_flag = 0;
    }
    else if (prm->round_flag == 2 && prm->right_lose1 + prm->right_lose2 < 3)
    {
            prm->round_flag = 0;
    }

}
void patch_left_2point(Img_Param *prm)      //连接左侧两个垂直拐点
{
    float lx = (float)(prm->left_line[prm->left_inf1]  - prm->left_line[prm->left_inf2]) / (prm->left_inf1 - prm->left_inf2);
    for (int i = prm->left_inf1, x = 0; i > prm->left_inf2; i--, x++)
        prm->left_line[i] = prm->left_line[prm->left_inf1] - (lx * x);
}
void patch_right_2point(Img_Param *prm)     //连接右侧两个垂直拐点
{
    float  rx = (float)(prm->right_line[prm->right_inf1]  - prm->right_line[prm->right_inf2]) / (prm->right_inf1 - prm->right_inf2);
    for (int i = prm->right_inf1, x = 0; i > prm->right_inf2; i--, x++)
        prm->right_line[i] = prm->right_line[prm->right_inf1] - (rx * x);
}

void patch_left_slope_down(Img_Param *prm, int mode)      //左垂直拐点往下拉线
{
    float lx = (float)(prm->left_line[prm->left_inf2]  - prm->left_line[prm->left_inf2 - 3]) / 3;
    for (int i = prm->left_inf2, x = 0; i <= prm->road_start; i++, x++)
    {
        int patch = prm->left_line[prm->left_inf2] + (lx * x);
        if (mode)   patch = (patch < prm->left_line[i] ? prm->left_line[i] : patch);
        else patch = (patch < 1 ? 1 : patch);
        prm->left_line[i] = patch;
    }
}
void patch_right_slope_down(Img_Param *prm, int mode)     //右垂直拐点往下拉线
{
    float rx = (float)(prm->right_line[prm->right_inf2]  - prm->right_line[prm->right_inf2 - 3]) / 3;
    for (int i = prm->right_inf2, x = 0; i <= prm->road_start; i++, x++)
    {
        int patch = prm->right_line[prm->right_inf2] + (rx * x);
        if (mode)   patch = (patch > prm->right_line[i] ? prm->right_line[i] : patch);
        else patch = (patch > IMG_W - 2 ? IMG_W - 2 : patch);
        prm->right_line[i] = patch;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      补线函数
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年4月12日
//  Sample usage:               patch_line(&prm);
//-------------------------------------------------------------------------------------------------------------------
void patch_line(Img_Param *prm)
{
    if (prm->garage_flag)       //入库补线
    {
        float lx,rx;
        switch (prm->garage_flag)
        {
            case 1:
                if (prm->left_inf1)
                {
                    lx = (float)(prm->left_line[prm->left_inf1] - prm->left_line[prm->road_end]) *0.75 / (prm->road_end - prm->left_inf1);
                    rx = (float)(prm->right_line[prm->left_inf1] - prm->left_line[prm->road_end]) *0.5 / (prm->road_end - prm->left_inf1);
                    for (int i = prm->left_inf1, x = 0; i > prm->road_end; i--, x++)
                    {
                        prm->left_line[i] = prm->left_line[prm->left_inf1] + (lx * x);
                        prm->right_line[i] = prm->right_line[prm->left_inf1] + (rx * x);
                    }
                }
                break;
            case 2:
                if (prm->right_inf1)
                {
                    lx = (float)(prm->left_line[prm->right_inf1] - prm->right_line[prm->road_end]) * 0.5 / (prm->road_end - prm->right_inf1);
                    rx = (float)(prm->right_line[prm->right_inf1] - prm->right_line[prm->road_end]) * 0.75 / (prm->road_end - prm->right_inf1);
                    for (int i = prm->right_inf1, x = 0; i > prm->road_end; i--, x++)
                    {
                        prm->left_line[i] = prm->left_line[prm->right_inf1] + (lx * x);
                        prm->right_line[i] = prm->right_line[prm->right_inf1] + (rx * x);
                    }
                }
                break;
            case 3:
                if(prm->right_inf2 && prm->right_lose1 > 2)
                    patch_right_slope_down(prm, 1);
                else if (prm->left_lose1 + prm->left_lose2 > 5)
                {
                    rx = (float)(Garage_Patch - prm->left_line[prm->road_end]) *0.5 / (prm->road_end - prm->road_start);
                    for (int i = prm->road_start, x = 0; i > prm->road_end; i--, x++)
                    {
                        prm->left_line[i] = 0;
                        prm->right_line[i] = Garage_Patch + (rx * x);
                    }
                }
                break;
            case 4:
                if (prm->left_inf2 && prm->left_lose1 > 2)
                    patch_left_slope_down(prm, 1);
                else if (prm->right_lose1 + prm->right_lose2 > 5)
                {
                    lx = (float)(IMG_W - 1 -Garage_Patch - prm->right_line[prm->road_end]) *0.5 / (prm->road_end - prm->road_start);
                    for (int i = prm->road_start, x = 0; i > prm->road_end; i--, x++)
                    {
                        prm->right_line[i] = IMG_W - 1;
                        prm->left_line[i] = IMG_W - 1 -Garage_Patch + (lx * x);
                    }
                }
                break;
            default:    break;
        }
    }
    else if (prm->round_flag)       //环岛补线
        {
        static int temp;
            if(prm->round_flag % 2 == 1)        //左环岛补线
            {
                float lx, rx;
                switch(prm->round_flag)
                {
                    case 1:     //左环岛1补线，连接左侧直角拐点和圆弧拐点
                        if (prm->left_inf1)
                        {
                            lx = (float)(prm->left_line[prm->left_inf1]  - prm->left_line[prm->left_arcinf]) / (prm->left_inf1 - prm->left_arcinf);
                            for(int i = prm->left_inf1, x = 0; i > prm->left_arcinf; i--, x++)
                                prm->left_line[i] = prm->left_line[prm->left_inf1] - (lx * x);
                        }
                        else
                        {
                            lx = (float)(prm->right_line[prm->road_start] - First_Patch - prm->left_line[prm->left_arcinf]) / (prm->road_start - prm->left_arcinf);
                            for (int i = prm->road_start, x = 0; i > prm->left_arcinf; i--, x++)
                                prm->left_line[i] = prm->right_line[prm->road_start] - First_Patch - (lx * x);
                        }
                        break;
                    case 3:     //左环岛2补线，将左圆弧拐点往左下补线，对应的右边界行与左上边界连接
                        lx = (float)(prm->right_line[prm->road_start] - First_Patch - prm->left_line[prm->left_arcinf]) / (prm->road_start - prm->left_arcinf);
                        rx = (float)(prm->right_line[prm->left_arcinf] - prm->left_line[prm->road_end]) / (prm->road_end - prm->left_arcinf);
                        for (int i = prm->left_arcinf, x = 0; i > prm->road_end; i--, x++)
                            prm->right_line[i] = prm->right_line[prm->left_arcinf] + (rx * x);
                        for (int i = prm->road_start, x = 0; i > prm->left_arcinf; i--, x++)
                            prm->left_line[i] = prm->right_line[prm->road_start] - First_Patch - (lx * x);
                        break;
                    case 5:     //左环岛3补线，右上拐点往右下补线
                        if(prm->right_inf2 - prm->road_end < 10)
                        {
                            rx = (float)(prm->left_line[prm->road_start] + First_Patch + 15  - prm->right_line[prm->right_inf2]) / (prm->right_inf2 - prm->road_start);
                            for (int i = prm->road_start, x = 0; i > prm->right_inf2; i--, x++)
                                prm->right_line[i] = prm->left_line[prm->road_start] + First_Patch + 15 + (rx * x);
                        }
                        else
                            patch_right_slope_down(prm,1);
                        break;
                               //左环岛4正常循迹不进行补线
                    case 7:     //左环岛5补线，右下拐点往左上补线
                        if (prm->right_inf1)
                        {
                            temp = prm->right_line[prm->right_inf1];
                            rx = (float)(prm->right_line[prm->right_inf1]) / 2 / (prm->right_inf1 - prm->right_inf2);
                            for (int i = prm->right_inf1, x = 0; i > prm->right_inf2; i--, x++)
                                prm->right_line[i] = temp - (rx * x);
                            prm->road_end = prm->right_inf2;     //重新确定结束行
                        }
                        break;
                    case 9:        //左环岛6补线，右下角往左上角连左边界
                        rx = (float)(prm->left_line[prm->right_inf2] - temp) / 2 / (prm->right_inf2 - prm->road_start);
                        for (int i = prm->road_start, x = 0; i > prm->right_inf2; i--, x++)
                            prm->right_line[i] = temp  - (rx * x);
                        prm->road_end = prm->right_inf2;
                        break;
                    case 11:        //左环岛7补线，左上拐点往左下补线
                        patch_left_slope_down(prm, 1);
                        break;
                    default: break;
                }
            }
            else if (prm->round_flag %2 == 0)       //右环岛补线
            {
                float lx, rx;
                switch(prm->round_flag)
                {
                    case 2:     //右环岛1补线，连接右侧直角拐点和圆弧拐点
                        if (prm->right_inf1)
                        {
                            rx = (float)(prm->right_line[prm->right_inf1]  - prm->right_line[prm->right_arcinf]) / (prm->right_inf1 - prm->right_arcinf);
                            for (int i = prm->right_inf1, x = 0; i > prm->right_arcinf; i--, x++)
                                prm->right_line[i] = prm->right_line[prm->right_inf1] - (rx * x);
                        }
                        else
                        {
                            rx = (float)(prm->left_line[prm->road_start] + First_Patch - prm->right_line[prm->right_arcinf]) / (prm->road_start - prm->right_arcinf);
                            for (int i = prm->road_start, x = 0; i > prm->right_arcinf && i > 5; i--, x++)
                                prm->right_line[i] = prm->left_line[prm->road_start] + First_Patch - (rx * x);
                        }
                        break;
                    case 4:       //右环岛2补线，将右圆弧拐点往右下补线，对应的左边界行与右上边界连接
                        lx = (float)(prm->left_line[prm->right_arcinf] - prm->right_line[prm->road_end]) / (prm->road_end - prm->right_arcinf);
                        rx = (float)(prm->left_line[prm->road_start] + First_Patch - prm->right_line[prm->right_arcinf]) / (prm->road_start - prm->right_arcinf);
                        for (int i = prm->right_arcinf, x = 0; i > prm->road_end && i > 5; i--, x++)
                            prm->left_line[i] = prm->left_line[prm->right_arcinf] + (lx * x);
                        for (int i = prm->road_start, x = 0; i > prm->right_arcinf && i > 5; i--, x++)
                            prm->right_line[i] = prm->left_line[prm->road_start] + First_Patch - (rx * x);
                        break;
                    case 6:      //右环岛3补线，左上拐点往左下补线
                        if(prm->left_inf2 - prm->road_end < 10)
                        {
                            lx = (float)(prm->right_line[prm->road_start] - First_Patch - 15 - prm->left_line[prm->left_inf2]) / (prm->left_inf2 - prm->road_start);
                            for (int i = prm->road_start, x = 0; i > prm->left_inf2; i--, x++)
                                prm->left_line[i] = prm->right_line[prm->road_start] - First_Patch - 15 + (lx * x);
                        }
                        else
                            patch_left_slope_down(prm, 1);
                        break;
                    case 8:        //右环岛5补线，左下拐点往右上补线
                        if (prm->left_inf1)
                        {
                            temp = prm->left_line[prm->left_inf1];
                            lx = (float)(prm->left_line[prm->left_inf1]  - IMG_W + 1) / 2 / (prm->left_inf1 - prm->left_inf2);
                            for (int i = prm->left_inf1, x = 0; i > prm->left_inf2; i--, x++)
                                prm->left_line[i] = temp - (lx * x);
                            prm->road_end = prm->left_inf2;
                        }
                        break;
                    case 10:      //右环岛6补线，左下角往右上角连左边界
                        lx = (float)(prm->right_line[prm->left_inf2] - temp) / 2 / (prm->left_inf2 - prm->road_start);
                        for (int i = prm->road_start, x = 0; i > prm->left_inf2; i--, x++)
                            prm->left_line[i] = temp  - (lx * x);
                        prm->road_end = prm->left_inf2;
                        break;
                    case 12:      //右环岛7补线，右上拐点往右下补线
                        patch_right_slope_down(prm, 1);
                        break;
                    default: break;
                }
            }
        }
    else if (prm->cross_flag)       //十字路补线
    {
        switch (prm->cross_flag)
        {
            case 1:     //正入十字补线，四个拐点两两相连
                patch_left_2point(prm);
                patch_right_2point(prm);
                break;
            case 2:     //左斜入十字补线，左侧两个拐点相连，右上拐点往下补线
                patch_left_2point(prm);
                patch_right_slope_down(prm, 1);
                break;
            case 3:     //右斜入十字补线，右侧两个拐点相连，左上拐点往下补线
                patch_left_slope_down(prm, 1);
                patch_right_2point(prm);
                break;
            case 4:     //十字中补线，两个上拐点往下补线
                patch_left_slope_down(prm, 0);
                patch_right_slope_down(prm, 0);
                break;
            default: break;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      分析提取出的边界并计算中线，使用最小二乘法分析左右边界的斜率；
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年4月4日
//  Sample usage:               analysis_border_prossed(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_border_prossed(Img_Param *prm)
{
    float sum_x2 = 0.0, sum_x  = 0.0, suml_y  = 0.0, sumr_y  = 0.0, suml_xy = 0.0, sumr_xy = 0.0, sum_tmp = 0.0;       //最小二乘法参数
    int num = prm->road_start - prm->road_end;     //有效行数
    for (int i = prm->road_start, x = 0; i > prm->road_end; i--, x++)
    {
        prm->mid_line[i] = (prm->left_line[i] + prm->right_line[i]);        //为了保证精度此处未除以二，相当于以IMG_W-1为中点计算偏差
        sum_x2 += x * x;
        sum_x += x;
        suml_y += prm->left_line[i];
        suml_xy += x * prm->left_line[i];
        sumr_y += prm->right_line[i];
        sumr_xy += x * prm->right_line[i];
    }
    if(num > 5)
    {
        sum_tmp = num * sum_x2 - sum_x * sum_x;
        prm->left_slope = (num * suml_xy - sum_x * suml_y) / sum_tmp;       //最小二乘法拟合左边界的斜率
        prm->right_slope = (num * sumr_xy - sum_x * sumr_y) / sum_tmp;       //最小二乘法拟合右边界的斜率
    }
    /*直弯道判断*/
    if ((prm->left_slope > 1.3  && prm-> right_slope > -0.3 && prm->left_outliers < 3 && (prm->road_end > 8 || prm->left_line[prm->road_end - 1] > IMG_W - 6)) ||
            (prm->right_slope < -1.3 && prm-> left_slope < 0.3 && prm->right_outliers < 3 && (prm->road_end > 8 || prm->right_line[prm->road_end - 1] < 5)))        //大弯道
        prm->curve_flag = 3;
    else if (prm->left_slope > 0.95 || prm->right_slope < -0.95 || prm->left_outliers + prm->right_outliers > 13)      //小弯道
        prm->curve_flag = 2;
    else if (prm->road_end > 5)     //短直道
        prm->curve_flag = 1;
    else        //长直道
        prm->curve_flag = 0;
    prm->flag |= prm->curve_flag << 5;      //直弯道标志位封装
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      分析中线，计算偏差
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年4月5日
//  Sample usage:               analysis_midline(&prm);
//-------------------------------------------------------------------------------------------------------------------
void analysis_midline(Img_Param *prm)
{
    int total = 0, count = 0,ramp_count = 0,last_err = prm->mid_line[prm->road_start] - IMG_W + 1, err;
//    const int err_weight03[IMG_H] = {
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 1, 1, 1, 1, 1, 2, 2, 2,
//        2, 2, 2, 3, 3, 3, 3, 4, 5, 6,
//        7, 8, 9, 9, 10, 10, 9, 9, 8, 8,
//        7, 7, 7, 6, 6, 6, 6, 5, 5, 4,
//        4, 3, 3, 3, 2, 2, 2, 2, 2, 2};
    const int err_weight02[IMG_H] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 2, 2, 3, 3, 2, 2, 1, 1,
        3, 3, 5, 5, 7, 7, 5, 5, 3, 3,
        5, 5, 6, 6, 9, 9, 6, 6, 5, 5};
    //完赛识别数组
    const int err_weight03[IMG_H] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 2, 2, 3, 3, 2, 2, 1, 1,
        3, 3, 5, 5, 7, 7, 5, 5, 3, 3,
        5, 5, 6, 6, 9, 9, 6, 6, 5, 5};
    for (int i = prm->road_start, x = 0;  i > prm->road_end; i--, x++)
    {
        int err = prm->mid_line[i] - IMG_W + 1;
        if (prm->curve_flag == 2)
        {
            total += err_weight02[i] * err;      //记录偏差和
            count += err_weight02[i];        //记录权重和
        }
        else
        {
            if (abs_(err - last_err) > 5 && prm->curve_flag == 0) err = last_err;       //滤波
            else last_err = err;
            total += err_weight03[i] * err;      //记录偏差和
            count += err_weight03[i];        //记录权重和
        }
        if (i< IMG_H * 3 / 4 && i > IMG_H / 2)
        {
            if (prm->right_line[i] - prm->left_line[i] < 40)
                ramp_count ++;
        }
    }
    err = total / count;
    if (ramp_count > 2 && !prm->garage_flag && !prm->zebracrossing_flag && abs_(err) < 35)        //坡道
    {
        prm->ramp_flag = 1;
        prm->flag |= 0x80;
    }

    if (abs_(err) < 200)        //限幅
        prm->error = err;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      恶臭函数，让蜂鸣器发出野兽先辈的咆哮
//  @param      prm     图像参数结构体
//  @return     114514
//  @creation date       2021年6月5日

//  Sample usage:               henghengheng_aaaaa_aaaaaaaaaaa(&prm);
//-------------------------------------------------------------------------------------------------------------------
int henghengheng_aaaaa_aaaaaaaaaaa (Img_Param *prm)
{
//    if (prm->stop_flag)
//        beep_control(0);
//    else if (prm->round_flag)
//        beep_control(_f1);
//    else if (prm->fork_flag || prm->garage_flag || prm->zebracrossing_flag)
//        beep_control(_g);
//    else if (prm->ramp_flag)
//        beep_control(_b);
//    else if (prm->curve_flag == 1)
//        beep_control(_a);
//    else if (prm->curve_flag == 2)
//        beep_control(_a1);
//    else if (prm->curve_flag == 3)
//        beep_control(_b);
//    else
//        beep_control(0);
    return 114514;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      参数显示函数
//  @param      prm     图像参数结构体
//  @return     void
//  @creation date       2021年5月13日
//  Sample usage:               display_param(&prm);
//-------------------------------------------------------------------------------------------------------------------
void display_param(Img_Param *prm)
{
//    char str[15];
//    ips114_showint16(0, 4, prm->error);
//    sprintf(str, "ls1:%2d,%2d  ", prm->left_lose1, prm->right_lose1);
//    ips114_showstr(0, 5, str);
//    sprintf(str, "ls2:%2d,%2d  ", prm->left_lose2, prm->right_lose2);
//    ips114_showstr(0, 6, str);
//    sprintf(str, "out:%2d,%2d", prm->left_outliers, prm->right_outliers);
//    ips114_showstr(0, 7, str);
//    if (prm->stop_flag)
//        sprintf(str, "S T O P");
//    else if(prm->round_flag)
//        sprintf(str, "ROUND%d ", (prm->round_flag + 1) >> 1);
//    else if (prm->fork_flag)
//        sprintf(str, "FORKWAY");
//    else if (prm->garage_flag)
//        sprintf(str, "GARAGE2");
//    else if (prm->zebracrossing_flag == 1)
//        sprintf(str, "GARAGE1");
//    else if (prm->ramp_flag)
//        sprintf(str, "RAMPWAY");
//    else if (prm->curve_flag == 3)
//        sprintf(str, "CURVE 2");
//    else if (prm->curve_flag == 2)
//        sprintf(str, "CURVE 1");
//    else if (prm->curve_flag == 1)
//        sprintf(str, "NOMAL 2");
//    else
//        sprintf(str, "NOMAL 1");
//    ips114_showstr(IMG_W, 0, str);
//    sprintf(str, "end%2d", prm->road_end);
//    ips114_showstr(IMG_W, 1, str);
//    ips114_showfloat(IMG_W, 2, prm->left_slope, 1, 3);
//    ips114_showfloat(IMG_W, 3, prm->right_slope, 1, 3);
//    sprintf(str, "zbr%2d", prm->zebracrossing_count);
//    ips114_showstr(IMG_W, 4, str);
//    sprintf(str, "%3d", prm->black_threshold);
//    ips114_showstr(IMG_W, 5, str);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      在屏幕上显示图像
//  @param      *Img     图像入口地址
//  @return     void
//  @creation date       2021年6月6日
//  Sample usage:               display_image(Img[0]);
//-------------------------------------------------------------------------------------------------------------------
void display_grey(uint8 *p, Img_Param *prm)
{
//    uint32 w,h;
//    uint16 color = 0;
//    uint16 temp = 0;
//    tft180_set_region(0,0,IMG_W-1,IMG_H-1);
//    for(h=0; h<IMG_H;h++)
//    {
//        for(w=0;w<IMG_W;w++)
//        {
//            if(h > prm->road_end && h <= prm->road_start)
//            {
//                int mid = (prm->left_line[h] + prm->right_line[h]) >> 1;
//                if (w == prm->left_line[h])
//                    soft_spi_write_16bit(&tft180_spi,RGB565_BLUE);
//                else if (w == prm->right_line[h])
//                    soft_spi_write_16bit(&tft180_spi,RGB565_GREEN);
//                else if (w == mid)
//                    soft_spi_write_16bit(&tft180_spi,RGB565_RED);
//                else
//                {
//                    temp = *(p+h*IMG_W+w);//读取像素点
//                    color=(0x001f&((temp)>>3))<<11;
//                    color=color|(((0x003f)&((temp)>>2))<<5);
//                    color=color|(0x001f&((temp)>>3));
//                    soft_spi_write_16bit(&tft180_spi,color);
//                }
//            }
//            else
//            {
//                temp = *(p+h*IMG_W+w);//读取像素点
//                color=(0x001f&((temp)>>3))<<11;
//                color=color|(((0x003f)&((temp)>>2))<<5);
//                color=color|(0x001f&((temp)>>3));
//                soft_spi_write_16bit(&tft180_spi,color);
//            }
//        }
//    }
}
