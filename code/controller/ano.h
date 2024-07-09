#ifndef SRC_APPSW_TRICORE_USER_ANO_DT_H_
#define SRC_APPSW_TRICORE_USER_ANO_DT_H_

#include "zf_common_headfile.h"

/*!
  * @brief    ����λ�����ͷ���8��int16_t����
  *
  * @param    data1 - data8  �� ���͸���λ����ʾ����
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
  *
  * @date     2019/5/28 ���ڶ�
  */
void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 );
void ANO_DT_send_float(float data1, float data2, float data3, float data4);
void Vofa_SendData(float data0, float data1, float data2, float data3, float data4, float data5, uint8_t len);

#endif /* SRC_APPSW_TRICORE_USER_ANO_DT_H_ */


