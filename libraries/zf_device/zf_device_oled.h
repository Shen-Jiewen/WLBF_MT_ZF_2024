/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_device_oled
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.20
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
* 2023-04-28       pudding            ��������ע��˵��
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                  ------------------------------------
*                  ģ��ܽ�             ��Ƭ���ܽ�
*                  D0                 �鿴 zf_device_oled.h �� OLED_D0_PIN �궨��
*                  D1                 �鿴 zf_device_oled.h �� OLED_D1_PIN �궨��
*                  RES                �鿴 zf_device_oled.h �� OLED_RES_PIN �궨��
*                  DC                 �鿴 zf_device_oled.h �� OLED_DC_PIN �궨��
*                  CS                 �鿴 zf_device_oled.h �� OLED_CS_PIN �궨��
*                  VCC                3.3V��Դ
*                  GND                ��Դ��
*                  ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_oled_h_
#define _zf_device_oled_h_

#include "zf_common_typedef.h"

//===================================================���� OLED ��������=================================================
#define OLED_USE_SOFT_SPI               (0 )                                    // Ĭ��ʹ��Ӳ�� SPI ��ʽ���� ����ʹ��Ӳ�� SPI ��ʽ����
#if OLED_USE_SOFT_SPI                                                           // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� SPI ����====================================================
#define OLED_SOFT_SPI_DELAY             (0 )                                    // ��� SPI ��ʱ����ʱ���� ��ֵԽС SPI ͨ������Խ��
#define OLED_D0_PIN                     (P15_3)                                 // ��� SPI SCK ����
#define OLED_D1_PIN                     (P15_5)                                 // ��� SPI MOSI ����
//====================================================��� SPI ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
#define OLED_SPI_SPEED                  (30*1000*1000)                          // Ӳ�� SPI ����
#define OLED_SPI                        (SPI_2)                                 // Ӳ�� SPI ��
#define OLED_D0_PIN                     (SPI2_SCLK_P15_3 )                      // Ӳ�� SPI SCK ����
#define OLED_D1_PIN                     (SPI2_MOSI_P15_5)                       // Ӳ�� SPI MOSI ����
#define OLED_D1_PIN_IN                  (SPI2_MISO_P15_4)                       // Ӳ�� SPI MISO ����  OLEDû��MISO���ţ�����������Ȼ��Ҫ���壬��spi�ĳ�ʼ��ʱ��Ҫʹ��
//====================================================Ӳ�� SPI ����====================================================
#endif


#define OLED_RES_PIN                    (P15_1)                                 // Һ����λ���Ŷ���
#define OLED_DC_PIN                     (P15_0 )                                // Һ������λ���Ŷ���
#define OLED_CS_PIN                     (P15_2 )                                // CS Ƭѡ����
#define OLED_BRIGHTNESS                 (0x7f)                                  // ����OLED���� Խ��Խ�� ��Χ0-0XFF
#define OLED_DEFAULT_DISPLAY_DIR        ( OLED_PORTAIT )                        // Ĭ�ϵ���ʾ����
#define OLED_DEFAULT_DISPLAY_FONT       (OLED_6X8_FONT )                        // Ĭ�ϵ�����ģʽ
#define OLED_X_MAX                      (128)                                   // ��ĻX���������ֵ
#define OLED_Y_MAX                      (64 )                                   // ��ĻY���������ֵ

#define OLED_RES(x)                     ((x) ? (gpio_high(OLED_RES_PIN)) : (gpio_low(OLED_RES_PIN)))
#define OLED_DC(x)                      ((x) ? (gpio_high(OLED_DC_PIN))  : (gpio_low(OLED_DC_PIN)))
#define OLED_CS(x)                      ((x) ? (gpio_high(OLED_CS_PIN))  : (gpio_low(OLED_CS_PIN)))
//===================================================���� OLED ��������=================================================


//===================================================���� OLED �����ṹ��=================================================
typedef enum
{
    OLED_PORTAIT                        = 0,                                    // ����ģʽ
    OLED_PORTAIT_180                    = 1,                                    // ����ģʽ  ��ת180
}oled_dir_enum;

typedef enum
{
    OLED_6X8_FONT                       = 0,                                    // 6x8      ����
    OLED_8X16_FONT                      = 1,                                    // 8x16     ����
    OLED_16X16_FONT                     = 2,                                    // 16x16    ���� Ŀǰ��֧��
}oled_font_size_enum;
//===================================================���� OLED ��������=================================================


//===================================================���� OLED ��������=================================================
void    oled_clear                      (void);                                                             // OLED ��������
void    oled_full                       (const uint8 color);                                                // OLED ��Ļ��亯��
void    oled_set_dir                    (oled_dir_enum dir);                                                // OLED ������ʾ����
void    oled_set_font                   (oled_font_size_enum font);                                         // OLED ������ʾ����
void    oled_draw_point                 (uint16 x, uint16 y, const uint8 color);                            // OLED ���㺯��

void    oled_show_string                (uint16 x, uint16 y, const char ch[]);                              // OLED ��ʾ�ַ���
void    oled_show_int                   (uint16 x, uint16 y, const int32 dat, uint8 num);                   // OLED ��ʾ32λ�з��� (ȥ������������Ч��0)
void    oled_show_uint                  (uint16 x, uint16 y, const uint32 dat, uint8 num);                  // OLED ��ʾ32λ�޷��� (ȥ������������Ч��0)
void    oled_show_float                 (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    oled_show_binary_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);                     // OLED ��ʾ��ֵͼ�� ����ÿ�˸������һ���ֽ�����
void    oled_show_gray_image            (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);    // OLED ��ʾ 8bit �Ҷ�ͼ�� ����ֵ����ֵ

void    oled_show_wave                  (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);              // OLED ��ʾ����
void    oled_show_chinese               (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number);                                                    // OLED ������ʾ
void    oled_init                       (void);                                                             // OLED ��ʼ������
//===================================================���� OLED ��������=================================================


//===================================================���� OLED ��չ����=================================================
//-------------------------------------------------------------------------------------------------------------------
// �������     OLED 128*64 ��ʾС���ͼ��
// ����˵��     p               ͼ������
// ���ز���     void
// ʹ��ʾ��     oled_displayimage7725(ov7725_image_binary[0]);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define oled_displayimage7725(p)        (oled_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, 128, 64))

//-------------------------------------------------------------------------------------------------------------------
// �������     OLED 128*64 ��ʾ�����ͼ�� ����ֵ��
// ����˵��     p               ͼ������
// ����˵��     x               ��ֵ����ʾ��ֵ
// ���ز���     void
// ʹ��ʾ��     oled_displayimage03x(mt9v03x_image[0], 127);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define oled_displayimage03x(p,x)       (oled_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, 128, 64, (x)))
//===================================================���� OLED ��չ����=================================================


#endif
