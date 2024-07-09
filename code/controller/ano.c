#include "ano.h"
#include "zf_driver_uart.h"

//使用匿名4.3上位机协议
/////////////////////////////////////////////////////////////////////////////////////
//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )     /*!< uint32_t 数据拆分 byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )     /*!< uint32_t 数据拆分 byte1  */
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )     /*!< uint32_t 数据拆分 byte2  */
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )     /*!< uint32_t 数据拆分 byte3  */

/**  发送数据缓存 */
unsigned char data_to_send[50];

/*!
  * @brief    Send_Data函数是协议中所有发送数据功能使用到的发送函数
  *
  * @param    dataToSend   :   要发送的数据首地址
  * @param    length       :   要发送的数据长度
  *
  * @return   无
  *
  * @note     移植时，用户应根据自身应用的情况，根据使用的通信方式，实现此函数
  *
  * @see      内部调用
  *
  * @date     2019/5/28 星期二
  */
void ANO_DT_Send_Data(unsigned char *dataToSend , unsigned short length)
{
//	HAL_UART_Transmit(&huart6, dataToSend, length, 1000);
    uart_write_buffer(UART_0,dataToSend,length);
}



/*!
  * @brief    向上位机发送发送8个int16_t数据
  *
  * @param    data1 - data8  ： 发送给上位机显示波形
  *
  * @return   无
  *
  * @note     无
  *
  * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
  *
  * @date     2019/5/28 星期二
  */
void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 )
{
    unsigned char  _cnt = 0;
    unsigned char sumcheck = 0, addcheck = 0;
	data_to_send[_cnt++] = 0xAB;        //匿名协议帧头  0xAB
	data_to_send[_cnt++] = 0x00;	    //源地址
	data_to_send[_cnt++] = 0xFF;		//目标地址
	data_to_send[_cnt++] = 0xF1;        //使用用户协议帧0xF1
	data_to_send[_cnt++] = 0x10;      
	data_to_send[_cnt++] = 0x00;        //8个int16_t 长度 16个字节

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
		sumcheck += data_to_send[i]; //从帧头开始，对每一字节进行求和，直到 DATA 区结束
		addcheck += sumcheck; //每一字节的求和操作，进行一次 sumcheck 的累加
	}

    data_to_send[_cnt++]=sumcheck;
    data_to_send[_cnt++]=addcheck;

	ANO_DT_Send_Data(data_to_send, _cnt);
}
void ANO_DT_send_float(float data1, float data2, float data3, float data4)
{
    unsigned char  _cnt = 0;
    unsigned char sumcheck = 0, addcheck = 0;
	data_to_send[_cnt++] = 0xAB;      //匿名协议帧头  0xAB
    data_to_send[_cnt++] = 0x00;      //源地址
    data_to_send[_cnt++] = 0xFF;      //目标地址
	data_to_send[_cnt++] = 0xF1;      //使用用户协议帧0xF1
    data_to_send[_cnt++] = 0x10;
    data_to_send[_cnt++] = 0x00;      //4个float 长度 16个字节

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
        sumcheck += data_to_send[i]; //从帧头开始，对每一字节进行求和，直到 DATA 区结束
        addcheck += sumcheck; //每一字节的求和操作，进行一次 sumcheck 的累加
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

