/*
 * menu.h
 *
 *  Created on: 2024��3��16��
 *      Author: Rick
 */

#ifndef CODE_CONTROLLER_MENU_H_
#define CODE_CONTROLLER_MENU_H_
#include "zf_common_headfile.h"

#define ROW_OFFSET(row)    (row * 8)
#define COLUMN_OFFSET(col) (col * 8)

#define MAX_PAGES 10 // ���ҳ��
#define MAX_PARAMS 20 // ÿҳ����������

typedef struct{
    fp32 *para;
    fp32 add_value_1;
    fp32 reduce_value_1;
    fp32 add_value_2;
    fp32 reduce_value_2;
}Para_type_def;

typedef struct {
    int total_pages;    // ��ҳ��
    int params_per_page; // ÿҳ��������
    int current_page;   // ��ǰҳ��
    int current_param;  // ��ǰ����λ��
    Para_type_def params[MAX_PAGES][MAX_PARAMS]; // �洢�����Ķ�ά����
}Menu;

void menu_init(Menu *menu, int total_pages, int params_per_page);
void modify_param(Menu *menu, int page, int param, fp32 *value,const fp32 add_reduce_values[4]);

void menu_show(Menu *menu);

#endif /* CODE_CONTROLLER_MENU_H_ */
