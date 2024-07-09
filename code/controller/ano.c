#include "ano.h"
#include "zf_driver_uart.h"

//ʹ������4.3��λ��Э��
/////////////////////////////////////////////////////////////////////////////////////
//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )     /*!< uint32_t ���ݲ�� byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )     /*!< uint32_t ���ݲ�� byte1  */
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )     /*!< uint32_t ���ݲ�� byte2  */
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )     /*!< uint32_t ���ݲ�� byte3  */

/**  �������ݻ��� */
unsigned char data_to_send[50];

/*!
  * @brief    Send_Data������Э�������з������ݹ���ʹ�õ��ķ��ͺ���
  *
  * @param    dataToSend   :   Ҫ���͵������׵�ַ
  * @param    length       :   Ҫ���͵����ݳ���
  *
  * @return   ��
  *
  * @note     ��ֲʱ���û�Ӧ��������Ӧ�õ����������ʹ�õ�ͨ�ŷ�ʽ��ʵ�ִ˺���
  *
  * @see      �ڲ�����
  *
  * @date     2019/5/28 ���ڶ�
  */
void ANO_DT_Send_Data(unsigned char *dataToSend , unsigned short length)
{
//	HAL_UART_Transmit(&huart6, dataToSend, length, 1000);
    uart_write_buffer(UART_0,dataToSend,length);
}



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
void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 )
{
    unsigned char  _cnt = 0;
    unsigned char sumcheck = 0, addcheck = 0;
	data_to_send[_cnt++] = 0xAB;        //����Э��֡ͷ  0xAB
	data_to_send[_cnt++] = 0x00;	    //Դ��ַ
	data_to_send[_cnt++] = 0xFF;		//Ŀ���ַ
	data_to_send[_cnt++] = 0xF1;        //ʹ���û�Э��֡0xF1
	data_to_send[_cnt++] = 0x10;      
	data_to_send[_cnt++] = 0x00;        //8��int16_t ���� 16���ֽ�

	data_to_send[_cnt++]=BYTE0(data1);
	data_to_send[_cnt++]=BYTE1(data1);

	data_to_send[_cnt++]=BYTE0(data2);
	data_to_send[_cnt++]=BYTE1(data2);

	data_to_send[_cnt++]=BYTE0(data3);
	data_to_send[_cnt++]=BYTE1(data3);

	data_to_send[_cnt++]=BYTE0(data4);
	data_to_send[_cnt++]=BYTE1(data4);

	data_to_send[_cnt++]=BYTE0(data5);
	data_to_send[_cnt++]=BYTE1(data5);

	data_to_send[_cnt++]=BYTE0(data6);
	data_to_send[_cnt++]=BYTE1(data6);

	data_to_send[_cnt++]=BYTE0(data7);
	data_to_send[_cnt++]=BYTE1(data7);

	data_to_send[_cnt++]=BYTE0(data8);
	data_to_send[_cnt++]=BYTE1(data8);

	uint16_t flen = data_to_send[4] + data_to_send[5] * 256;
	for(uint16_t i=0; i < (flen+6); i++)
	{
		sumcheck += data_to_send[i]; //��֡ͷ��ʼ����ÿһ�ֽڽ�����ͣ�ֱ�� DATA ������
		addcheck += sumcheck; //ÿһ�ֽڵ���Ͳ���������һ�� sumcheck ���ۼ�
	}

    data_to_send[_cnt++]=sumcheck;
    data_to_send[_cnt++]=addcheck;

	ANO_DT_Send_Data(data_to_send, _cnt);
}
void ANO_DT_send_float(float data1, float data2, float data3, float data4)
{
    unsigned char  _cnt = 0;
    unsigned char sumcheck = 0, addcheck = 0;
	data_to_send[_cnt++] = 0xAB;      //����Э��֡ͷ  0xAB
    data_to_send[_cnt++] = 0x00;      //Դ��ַ
    data_to_send[_cnt++] = 0xFF;      //Ŀ���ַ
	data_to_send[_cnt++] = 0xF1;      //ʹ���û�Э��֡0xF1
    data_to_send[_cnt++] = 0x10;
    data_to_send[_cnt++] = 0x00;      //4��float ���� 16���ֽ�

	data_to_send[_cnt++]=BYTE0(data1);
	data_to_send[_cnt++]=BYTE1(data1);
	data_to_send[_cnt++]=BYTE2(data1);
	data_to_send[_cnt++]=BYTE3(data1);

	data_to_send[_cnt++]=BYTE0(data2);
	data_to_send[_cnt++]=BYTE1(data2);
	data_to_send[_cnt++]=BYTE2(data2);
	data_to_send[_cnt++]=BYTE3(data2);

	data_to_send[_cnt++]=BYTE0(data3);
	data_to_send[_cnt++]=BYTE1(data3);
	data_to_send[_cnt++]=BYTE2(data3);
	data_to_send[_cnt++]=BYTE3(data3);

	data_to_send[_cnt++]=BYTE0(data4);
	data_to_send[_cnt++]=BYTE1(data4);
	data_to_send[_cnt++]=BYTE2(data4);
	data_to_send[_cnt++]=BYTE3(data4);

    uint16_t flen = data_to_send[4] + data_to_send[5] * 256;
    for(uint16_t i=0; i < (flen+6); i++)
    {
        sumcheck += data_to_send[i]; //��֡ͷ��ʼ����ÿһ�ֽڽ�����ͣ�ֱ�� DATA ������
        addcheck += sumcheck; //ÿһ�ֽڵ���Ͳ���������һ�� sumcheck ���ۼ�
    }

    data_to_send[_cnt++]=sumcheck;
    data_to_send[_cnt++]=addcheck;

    ANO_DT_Send_Data(data_to_send, _cnt);
}

void Vofa_SendData(float data0, float data1, float data2, float data3, float data4, float data5, uint8_t len)
{
    static uint8_t tmp_dat[64];
    uint8_t cnt=len*sizeof(float);
    float data[6]={data0, data1, data2, data3, data4, data5};
    uint8_t i=0;

    for(i=0; i<cnt; i++)
    {
        tmp_dat[i] = *(((uint8_t*)data)+i);
    }
    tmp_dat[i++] = 0x00;
    tmp_dat[i++] = 0x00;
    tmp_dat[i++] = 0x80;
    tmp_dat[i++] = 0x7f;

    ANO_DT_Send_Data(tmp_dat, i);
}

