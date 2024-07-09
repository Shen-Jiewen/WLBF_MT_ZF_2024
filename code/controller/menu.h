/*
 * menu.h
 *
 *  Created on: 2024年3月16日
 *      Author: Rick
 */

#ifndef CODE_CONTROLLER_MENU_H_
#define CODE_CONTROLLER_MENU_H_
#include "zf_common_headfile.h"

#define ROW_OFFSET(row)    (row * 8)
#define COLUMN_OFFSET(col) (col * 8)

#define MAX_PAGES 10 // 最大页数
#define MAX_PARAMS 20 // 每页最大参数数量

typedef struct{
    fp32 *para;
    fp32 add_value_1;
    fp32 reduce_value_1;
    fp32 add_value_2;
    fp32 reduce_value_2;
}Para_type_def;

typedef struct {
    int total_pages;    // 总页数
    int params_per_page; // 每页参数数量
    int current_page;   // 当前页数
    int current_param;  // 当前参数位置
    Para_type_def params[MAX_PAGES][MAX_PARAMS]; // 存储参数的二维数组
}Menu;

void menu_init(Menu *menu, int total_pages, int params_per_page);
void modify_param(Menu *menu, int page, int param, fp32 *value,const fp32 add_reduce_values[4]);

void menu_show(Menu *menu);

#endif /* CODE_CONTROLLER_MENU_H_ */
