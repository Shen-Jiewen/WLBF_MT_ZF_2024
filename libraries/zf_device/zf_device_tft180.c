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
* �ļ�����          zf_device_tft180
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.20
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
* 2023-10-07       pudding            �޸����ݴ��䷽ʽ����������һ������
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                  ------------------------------------
*                  ģ��ܽ�              ��Ƭ���ܽ�
*                  SCL                 �鿴 zf_device_tft180.h �� TFT180_SCL_PIN �궨��
*                  SDA                 �鿴 zf_device_tft180.h �� TFT180_SDA_PIN �궨��
*                  RES                 �鿴 zf_device_tft180.h �� TFT180_RES_PIN �궨��
*                  DC                  �鿴 zf_device_tft180.h �� TFT180_DC_PIN �궨��
*                  CS                  �鿴 zf_device_tft180.h �� TFT180_CS_PIN �궨��
*                  BL                  �鿴 zf_device_tft180.h �� TFT180_BL_PIN �궨��
*                  VCC                 3.3V��Դ
*                  GND                 ��Դ��
*                  ���ֱ���160*128
*                  ------------------------------------
********************************************************************************************************************/

#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"
#include "zf_device_tft180.h"

        uint16                   tft180_width_max    = 160;
		uint16                   tft180_height_max   = 128;
static 	uint16                   tft180_pencolor     = TFT180_DEFAULT_PENCOLOR;          // ������ɫ(����ɫ)
static 	uint16                   tft180_bgcolor      = TFT180_DEFAULT_BGCOLOR;           // ������ɫ

static 	tft180_dir_enum          tft180_display_dir  = TFT180_DEFAULT_DISPLAY_DIR;       // ��ʾ����
static 	tft180_font_size_enum    tft180_display_font = TFT180_DEFAULT_DISPLAY_FONT;      // ��ʾ��������

#if TFT180_USE_SOFT_SPI
static soft_spi_info_struct             tft180_spi;
//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��� SPI д 8bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     tft180_write_8bit_data(dat);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define tft180_write_8bit_data(data)                (soft_spi_write_8bit(&tft180_spi, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��� SPI д 8bit ��������
// ����˵��     *data           ����
// ����˵��     len             ���ݳ���
// ���ز���     void
// ʹ��ʾ��     tft180_write_8bit_data_array(data, len);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define tft180_write_8bit_data_array(data, len)     (soft_spi_write_8bit_array(&tft180_spi, (data), (len)))

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��� SPI д 16bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     tft180_write_16bit_data(x1 + 52);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define tft180_write_16bit_data(data)               (soft_spi_write_16bit(&tft180_spi, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��� SPI д 16bit ��������
// ����˵��     *data           ����
// ����˵��     len             ���ݳ���
// ���ز���     void
// ʹ��ʾ��     tft180_write_16bit_data_array(data, len);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define tft180_write_16bit_data_array(data, len)    (soft_spi_write_16bit_array(&tft180_spi, (data), (len)))
#else
//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 SPI д 8bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     tft180_write_8bit_data(dat);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define tft180_write_8bit_data(data)                (spi_write_8bit(TFT180_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 SPI д 8bit ��������
// ����˵��     *data           ����
// ����˵��     len             ���ݳ���
// ���ز���     void
// ʹ��ʾ��     tft180_write_8bit_data_array(data, len);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define tft180_write_8bit_data_array(data, len)     (spi_write_8bit_array(TFT180_SPI, (data), (len)))

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 SPI д 16bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_16bit_data(x1 + 52);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define tft180_write_16bit_data(data)               (spi_write_16bit(TFT180_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 SPI д 16bit ��������
// ����˵��     *data           ����
// ����˵��     len             ���ݳ���
// ���ز���     void
// ʹ��ʾ��     tft180_write_16bit_data_array(data, len);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define tft180_write_16bit_data_array(data, len)    (spi_write_16bit_array(TFT180_SPI, (data), (len)))
#endif

//-------------------------------------------------------------------------------------------------------------------
// �������     д����
// ����˵��     dat             ����
// ���ز���     void
// ʹ��ʾ��     tft180_write_index(0x2a);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void tft180_write_index (const uint8 dat)
{
    TFT180_DC(0);
    tft180_write_8bit_data(dat);
    TFT180_DC(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ���� �ڲ�����
// ����˵��     x1              ��ʼx������
// ����˵��     y1              ��ʼy������
// ����˵��     x2              ����x������
// ����˵��     y2              ����y������
// ���ز���     void
// ʹ��ʾ��     tft180_set_region(0, 0, tft180_width_max - 1, tft180_height_max - 1);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void tft180_set_region (uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    // ���һ�������ʾ���õĺ��� �Լ�����һ�����ﳬ������Ļ��ʾ��Χ
    zf_assert(x1 < tft180_width_max);
    zf_assert(y1 < tft180_height_max);
    zf_assert(x2 < tft180_width_max);
    zf_assert(y2 < tft180_height_max);

    switch(tft180_display_dir)
    {
        case TFT180_PORTAIT:
        case TFT180_PORTAIT_180:
        {
            tft180_write_index(0x2a);
            tft180_write_8bit_data(0x00);
            tft180_write_8bit_data(x1 + 2);
            tft180_write_8bit_data(0x00);
            tft180_write_8bit_data(x2 + 2);

            tft180_write_index(0x2b);
            tft180_write_8bit_data(0x00);
            tft180_write_8bit_data(y1 + 1);
            tft180_write_8bit_data(0x00);
            tft180_write_8bit_data(y2 + 1);
        }break;
        case TFT180_CROSSWISE:
        case TFT180_CROSSWISE_180:
        {
            tft180_write_index(0x2a);
            tft180_write_8bit_data(0x00);
            tft180_write_8bit_data(x1 + 1);
            tft180_write_8bit_data(0x0);
            tft180_write_8bit_data(x2 + 1);

            tft180_write_index(0x2b);
            tft180_write_8bit_data(0x00);
            tft180_write_8bit_data(y1 + 2);
            tft180_write_8bit_data(0x00);
            tft180_write_8bit_data(y2 + 2);
        }break;
    }
    tft180_write_index(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾDEBUG��Ϣ��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     tft180_debug_init();
// ��ע��Ϣ     �ڲ�ʹ��
//-------------------------------------------------------------------------------------------------------------------
static void tft180_debug_init (void)
{
    debug_output_struct info;
    debug_output_struct_init(&info);

    info.type_index = 1;
    info.display_x_max = tft180_width_max;
    info.display_y_max = tft180_height_max;

    switch(tft180_display_font)
    {
        case TFT180_6X8_FONT:
        {
            info.font_x_size = 6;
            info.font_y_size = 8;
        }break;
        case TFT180_8X16_FONT:
        {
            info.font_x_size = 8;
            info.font_y_size = 16;
        }break;
        case TFT180_16X16_FONT:
        {
            // �ݲ�֧��
        }break;
    }
    info.output_screen = tft180_show_string;
    info.output_screen_clear = tft180_clear;
        
    debug_output_init(&info);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     tft180_clear();
// ��ע��Ϣ     ����Ļ��ճɱ�����ɫ
//-------------------------------------------------------------------------------------------------------------------
void tft180_clear (void)
{
    uint16 color_buffer[tft180_width_max];
    uint16 i = 0, j = 0;

    TFT180_CS(0);
    tft180_set_region(0, 0, tft180_width_max - 1, tft180_height_max - 1);
    for(i = 0; i < tft180_width_max; i ++)
    {
        color_buffer[i] = tft180_bgcolor;
    }
    for (j = 0; j < tft180_height_max; j ++)
    {
        tft180_write_16bit_data_array(color_buffer, tft180_width_max);
    }
    TFT180_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��������
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �ڳ�����ɫ�궨��
// ���ز���     void
// ʹ��ʾ��     tft180_full(RGB565_YELLOW);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft180_full (const uint16 color)
{
    uint16 color_buffer[tft180_width_max];
    uint16 i = 0, j = 0;

    TFT180_CS(0);
    tft180_set_region(0, 0, tft180_width_max - 1, tft180_height_max - 1);
    for(i = 0; i < tft180_width_max; i ++)
    {
        color_buffer[i] = color;
    }
    for (j = 0; j < tft180_height_max; j ++)
    {
        tft180_write_16bit_data_array(color_buffer, tft180_width_max);
    }
    TFT180_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     dir             ��ʾ����  ���� zf_device_ips114.h �� tft180_dir_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     tft180_set_dir(TFT180_CROSSWISE);
// ��ע��Ϣ     �������ֻ���ڳ�ʼ����Ļ֮ǰ���ò���Ч
//-------------------------------------------------------------------------------------------------------------------
void tft180_set_dir (tft180_dir_enum dir)
{
    tft180_display_dir = dir;
    switch(tft180_display_dir)
    {
        case TFT180_PORTAIT:
        case TFT180_PORTAIT_180:
        {
            tft180_width_max = 128;
            tft180_height_max = 160;
        }break;
        case TFT180_CROSSWISE:
        case TFT180_CROSSWISE_180:
        {
            tft180_width_max = 160;
            tft180_height_max = 128;
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     dir             ��ʾ����  ���� zf_device_tft180.h �� tft180_font_size_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     tft180_set_font(TFT180_8x16_FONT);
// ��ע��Ϣ     ���������ʱ�������� ���ú���Ч ������ʾ�����µ������С
//-------------------------------------------------------------------------------------------------------------------
void tft180_set_font (tft180_font_size_enum font)
{
    tft180_display_font = font;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ��ɫ
// ����˵��     pen             ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �ڳ�����ɫ�궨��
// ����˵��     bgcolor         ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �ڳ�����ɫ�궨��
// ���ز���     void
// ʹ��ʾ��     tft180_set_color(RGB565_WHITE, RGB565_BLACK);
// ��ע��Ϣ     ������ɫ�ͱ�����ɫҲ������ʱ�������� ���ú���Ч
//-------------------------------------------------------------------------------------------------------------------
void tft180_set_color (uint16 pen, const uint16 bgcolor)
{
    tft180_pencolor = pen;
    tft180_bgcolor = bgcolor;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ����
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ����ɫ
// ���ز���     void
// ʹ��ʾ��     tft180_draw_point(0, 0, RGB565_RED);            // ���� 0,0 ��һ����ɫ�ĵ�
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft180_draw_point (uint16 x, uint16 y, const uint16 color)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);

    TFT180_CS(0);
    tft180_set_region(x, y, x, y);
    tft180_write_16bit_data(color);
    TFT180_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ����
// ����˵��     x_start         ����x��������
// ����˵��     y_start         ����y��������
// ����˵��     x_end           ����x������յ�
// ����˵��     y_end           ����y������յ�
// ����˵��     dat             ��Ҫ��ʾ����ɫ
// ���ز���     void
// ʹ��ʾ��     tft180_draw_line(0, 0, 10, 10,RGB565_RED);      // ���� 0,0 �� 10,10 ��һ����ɫ����
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft180_draw_line (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x_start < tft180_width_max);
    zf_assert(y_start < tft180_height_max);
    zf_assert(x_end < tft180_width_max);
    zf_assert(y_end < tft180_height_max);

    int16 x_dir = (x_start < x_end ? 1 : -1);
    int16 y_dir = (y_start < y_end ? 1 : -1);
    float temp_rate = 0;
    float temp_b = 0;

    do
    {
        if(x_start != x_end)
        {
            temp_rate = (float)(y_start - y_end) / (float)(x_start - x_end);
            temp_b = (float)y_start - (float)x_start * temp_rate;
        }
        else
        {
            while(y_start != y_end)
            {
                tft180_draw_point(x_start, y_start, color);
                y_start += y_dir;
            }
            tft180_draw_point(x_start, y_start, color);
            break;
        }
        
        if(func_abs(y_start - y_end) > func_abs(x_start - x_end))
        {
            while(y_start != y_end)
            {
                tft180_draw_point(x_start, y_start, color);
                y_start += y_dir;
                x_start = (int16)(((float)y_start - temp_b) / temp_rate);
            }
            tft180_draw_point(x_start, y_start, color);
        }
        else
        {
            while(x_start != x_end)
            {
                tft180_draw_point(x_start, y_start, color);
                x_start += x_dir;
                y_start = (int16)((float)x_start * temp_rate + temp_b);
            }
            tft180_draw_point(x_start, y_start, color);
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ�ַ�
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ�
// ���ز���     void
// ʹ��ʾ��     tft180_show_char(0, 0, 'x');                    // ���� 0,0 дһ���ַ� x
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_char (uint16 x, uint16 y, const char dat)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);

    uint8 i = 0, j = 0;

    TFT180_CS(0);
    switch(tft180_display_font)
    {
        case TFT180_6X8_FONT:
        {
            uint16 display_buffer[6*8];
            tft180_set_region(x, y, x + 5, y + 7);
            for(i = 0; 6 > i; i ++)
            {
                // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
                uint8 temp_top = ascii_font_6x8[dat - 32][i];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        display_buffer[i + j * 6] = (tft180_pencolor);
                    }
                    else
                    {
                        display_buffer[i + j * 6] = (tft180_bgcolor);
                    }
                    temp_top >>= 1;
                }
            }
            tft180_write_16bit_data_array(display_buffer, 6*8);
        }break;
        case TFT180_8X16_FONT:
        {
            uint16 display_buffer[8*16];
            tft180_set_region(x, y, x + 7, y + 15);
            for(i = 0; 8 > i; i ++)
            {
                uint8 temp_top = ascii_font_8x16[dat - 32][i];
                uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        display_buffer[i + j * 8] = (tft180_pencolor);
                    }
                    else
                    {
                        display_buffer[i + j * 8] = (tft180_bgcolor);
                    }
                    temp_top >>= 1;
                }
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_bottom & 0x01)
                    {
                        display_buffer[i + j * 8 + 4 * 16] = (tft180_pencolor);
                    }
                    else
                    {
                        display_buffer[i + j * 8 + 4 * 16] = (tft180_bgcolor);
                    }
                    temp_bottom >>= 1;
                }
            }
            tft180_write_16bit_data_array(display_buffer, 8 * 16);
        }break;
        case TFT180_16X16_FONT:
        {
            // �ݲ�֧��
        }break;
    }
    TFT180_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ�ַ���
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ���
// ���ز���     void
// ʹ��ʾ��     tft180_show_string(0, 0, "seekfree");
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_string (uint16 x, uint16 y, const char dat[])
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    
    uint16 j = 0;
    while('\0' != dat[j])
    {
        switch(tft180_display_font)
        {
            case TFT180_6X8_FONT:   tft180_show_char(x + 6 * j, y, dat[j]); break;
            case TFT180_8X16_FONT:  tft180_show_char(x + 8 * j, y, dat[j]); break;
            case TFT180_16X16_FONT: break;                                      // �ݲ�֧��
        }
        j ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ32λ�з��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� int32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     tft180_show_int(0, 0, x, 3);                    // x ����Ϊ int32 int16 int8 ����
// ��ע��Ϣ     ��������ʾһ�� ��-����
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_int (uint16 x, uint16 y, const int32 dat, uint8 num)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    zf_assert(0 < num);
    zf_assert(10 >= num);

    int32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num + 1);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    tft180_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ32λ�޷��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� uint32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     tft180_show_uint(0, 0, x, 3);                   // x ����Ϊ uint32 uint16 uint8 ����
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_uint (uint16 x, uint16 y, const uint32 dat, uint8 num)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    zf_assert(0 < num);
    zf_assert(10 >= num);

    uint32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];
    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_uint_to_str(data_buffer, dat_temp);
    tft180_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ������(ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� double
// ����˵��     num             ����λ��ʾ����   ���8λ  
// ����˵��     pointnum        С��λ��ʾ����   ���6λ
// ���ز���     void
// ʹ��ʾ��     tft180_show_float(0, 0, x, 2, 3);               // ��ʾ������   ������ʾ2λ   С����ʾ��λ
// ��ע��Ϣ     �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//              ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//              �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//              ��������ʾһ�� ��-����
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_float (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    zf_assert(0 < num);
    zf_assert(8 >= num);
    zf_assert(0 < pointnum);
    zf_assert(6 >= pointnum);

    double dat_temp = dat;
    double offset = 1.0;
    char data_buffer[17];
    memset(data_buffer, 0, 17);
    memset(data_buffer, ' ', num + pointnum + 2);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    for(; 0 < num; num --)
    {
        offset *= 10;
    }
    dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    func_double_to_str(data_buffer, dat_temp, pointnum);
    tft180_show_string(x, y, data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ��ֵͼ�� ����ÿ�˸������һ���ֽ�����
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     *image          ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ��
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ����˵��     dis_width       ͼ����ʾ��� ������Χ [0, tft180_width_max]
// ����˵��     dis_height      ͼ����ʾ�߶� ������Χ [0, tft180_height_max]
// ���ز���     void
// ʹ��ʾ��     tft180_show_binary_image(0, 0, ov7725_image_binary[0], OV7725_W, OV7725_H, OV7725_W / 2, OV7725_H / 2);
// ��ע��Ϣ     ������ʾС����δ��ѹ��ѹ����ֵ��ͼ��
//              �����������������ֱ����ʾ������δѹ���Ķ�ֵ��ͼ��
//              �����������������ֱ����ʾ������δѹ���Ķ�ֵ��ͼ��
//              �����������������ֱ����ʾ������δѹ���Ķ�ֵ��ͼ��
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_binary_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint8 temp = 0;
    uint32 width_index = 0;
    uint16 data_buffer[dis_width];
    const uint8 *image_temp;

    TFT180_CS(0);
    tft180_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // ������ʾ����

    for(j = 0; j < dis_height; j ++)
    {
        image_temp = image + j * height / dis_height * width / 8;               // ֱ�Ӷ� image ������ Hardfault ��ʱ��֪��Ϊʲô
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image_temp + width_index / 8);                             // ��ȡ���ص�
            if(0x80 & (temp << (width_index % 8)))
            {
                data_buffer[i] = (RGB565_WHITE);
            }
            else
            {
                data_buffer[i] = (RGB565_BLACK);
            }
        }
        tft180_write_16bit_data_array(data_buffer, dis_width);
    }
    TFT180_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ 8bit �Ҷ�ͼ�� ����ֵ����ֵ
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     *image          ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ��
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ����˵��     dis_width       ͼ����ʾ��� ������Χ [0, tft180_width_max]
// ����˵��     dis_height      ͼ����ʾ�߶� ������Χ [0, tft180_height_max]
// ����˵��     threshold       ��ֵ����ʾ��ֵ 0-��������ֵ��
// ���ز���     void
// ʹ��ʾ��     tft180_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W / 2, MT9V03X_H / 2, 0);
// ��ע��Ϣ     ������ʾ������ͼ��
//              ���Ҫ��ʾ��ֵ��ͼ�� ֱ���޸����һ������Ϊ��Ҫ�Ķ�ֵ����ֵ����
//              ���Ҫ��ʾ��ֵ��ͼ�� ֱ���޸����һ������Ϊ��Ҫ�Ķ�ֵ����ֵ����
//              ���Ҫ��ʾ��ֵ��ͼ�� ֱ���޸����һ������Ϊ��Ҫ�Ķ�ֵ����ֵ����
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_gray_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint16 color = 0,temp = 0;
    uint16 data_buffer[dis_width];
    const uint8 *image_temp;

    TFT180_CS(0);
    tft180_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // ������ʾ����

    for(j = 0; j < dis_height; j ++)
    {
        image_temp = image + j * height / dis_height * width;                   // ֱ�Ӷ� image ������ Hardfault ��ʱ��֪��Ϊʲô
        for(i = 0; i < dis_width; i ++)
        {
            temp = *(image_temp + i * width / dis_width);               // ��ȡ���ص�
            if(threshold == 0)
            {
                color = (0x001f & ((temp) >> 3)) << 11;
                color = color | (((0x003f) & ((temp) >> 2)) << 5);
                color = color | (0x001f & ((temp) >> 3));
                data_buffer[i] = (color);
            }
            else if(temp < threshold)
            {
                data_buffer[i] = (RGB565_BLACK);
            }
            else
            {
                data_buffer[i] = (RGB565_WHITE);
            }
        }
        tft180_write_16bit_data_array(data_buffer, dis_width);
    }
    TFT180_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ RGB565 ��ɫͼ��
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     *image          ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ��
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ����˵��     dis_width       ͼ����ʾ��� ������Χ [0, tft180_width_max]
// ����˵��     dis_height      ͼ����ʾ�߶� ������Χ [0, tft180_height_max]
// ����˵��     color_mode      ɫ��ģʽ 0-��λ��ǰ 1-��λ��ǰ
// ���ز���     void
// ʹ��ʾ��     tft180_show_rgb565_image(0, 0, scc8660_image[0], SCC8660_W, SCC8660_H, SCC8660_W / 2, SCC8660_H / 2, 1);
// ��ע��Ϣ     ������ʾ��ͫ�� RGB565 ��ͼ��
//              ���Ҫ��ʾ��λ��ǰ������ RGB565 ͼ�� �޸����һ����������
//              ���Ҫ��ʾ��λ��ǰ������ RGB565 ͼ�� �޸����һ����������
//              ���Ҫ��ʾ��λ��ǰ������ RGB565 ͼ�� �޸����һ����������
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_rgb565_image (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint16 data_buffer[dis_width];
    const uint16 *image_temp;

    TFT180_CS(0);
    tft180_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // ������ʾ����

    for(j = 0; j < dis_height; j ++)
    {
        image_temp = image + j * height / dis_height * width;                   // ֱ�Ӷ� image ������ Hardfault ��ʱ��֪��Ϊʲô
        for(i = 0; i < dis_width; i ++)
        {
            data_buffer[i] = *(image_temp + i * width / dis_width); // ��ȡ���ص�
        }
        if(color_mode)
        {
            tft180_write_8bit_data_array((uint8 *)data_buffer, dis_width * 2);
        }
        else
        {
            tft180_write_16bit_data_array(data_buffer, dis_width);
        }
    }
    TFT180_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʾ����
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     *wave           ��������ָ��
// ����˵��     width           ����ʵ�ʿ��
// ����˵��     value_max       ����ʵ�����ֵ
// ����˵��     dis_width       ������ʾ��� ������Χ [0, tft180_width_max]
// ����˵��     dis_value_max   ������ʾ���ֵ ������Χ [0, tft180_height_max]
// ���ز���     void
// ʹ��ʾ��     tft180_show_wave(32, 64, data, 128, 64, 64, 32);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_wave (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    zf_assert(NULL != wave);

    uint32 i = 0, j = 0;
    uint32 width_index = 0, value_max_index = 0;
    uint16 data_buffer[dis_width];

    TFT180_CS(0);
    tft180_set_region(x, y, x + dis_width - 1, y + dis_value_max - 1);          // ������ʾ����
    for(j = 0; j < dis_value_max; j ++)
    {
        for(i = 0; i < dis_width; i ++)
        {
            data_buffer[i] = (tft180_bgcolor); 
        }
        tft180_write_16bit_data_array(data_buffer, dis_width);
    }
    TFT180_CS(1);

    for(i = 0; i < dis_width; i ++)
    {
        width_index = i * width / dis_width;
        value_max_index = *(wave + width_index) * (dis_value_max - 1) / value_max;
        tft180_draw_point((uint16)(i + x), (uint16)((dis_value_max - 1) - value_max_index + y), tft180_pencolor);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ
// ����˵��     x               ����x�������� ������Χ [0, tft180_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, tft180_height_max-1]
// ����˵��     size            ȡģ��ʱ�����õĺ��������С Ҳ����һ������ռ�õĵ��󳤿�Ϊ���ٸ��� ȡģ��ʱ����Ҫ������һ����
// ����˵��     *chinese_buffer ��Ҫ��ʾ�ĺ�������
// ����˵��     number          ��Ҫ��ʾ����λ
// ����˵��     color           ��ʾ��ɫ
// ���ز���     void
// ʹ��ʾ��     tft180_show_chinese(0, 0, 16, chinese_test[0], 4, RGB565_RED);//��ʾfont�ļ������ ʾ��
// ��ע��Ϣ     ʹ��PCtoLCD2002���ȡģ           ���롢����ʽ��˳��   16*16
//-------------------------------------------------------------------------------------------------------------------
void tft180_show_chinese (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < tft180_width_max);
    zf_assert(y < tft180_height_max);
    zf_assert(NULL != chinese_buffer);

    int i = 0, j = 0, k = 0; 
    uint8 temp = 0, temp1 = 0, temp2 = 0;
    const uint8 *p_data = chinese_buffer;
    
    temp2 = size / 8;
    
    TFT180_CS(0);
    tft180_set_region(x, y, number * size - 1 + x, y + size - 1);
    
    for(i = 0; i < size; i ++)
    {
        temp1 = number;
        p_data = chinese_buffer + i * temp2;
        while(temp1 --)
        {
            for(k = 0; k < temp2; k ++)
            {
                for(j = 8; 0 < j; j --)
                {
                    temp = (*p_data >> (j - 1)) & 0x01;
                    if(temp)
                    {
                        tft180_write_16bit_data(color);
                    }
                    else
                    {
                        tft180_write_16bit_data(tft180_bgcolor);
                    }
                }
                p_data ++;
            }
            p_data = p_data - temp2 + temp2 * size;
        }   
    }
    TFT180_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TFT180 ��ʼ��
// ���ز���     void
// ���ز���     void
// ʹ��ʾ��     tft180_init();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void tft180_init (void)
{
#if TFT180_USE_SOFT_SPI
    soft_spi_init(&tft180_spi, 0, TFT180_SOFT_SPI_DELAY, TFT180_SCL_PIN, TFT180_SDA_PIN, SOFT_SPI_PIN_NULL, SOFT_SPI_PIN_NULL);
#else
    spi_init(TFT180_SPI, SPI_MODE0, TFT180_SPI_SPEED, TFT180_SCL_PIN, TFT180_SDA_PIN, TFT180_SDA_PIN_IN, SPI_CS_NULL);
#endif

    gpio_init(TFT180_DC_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(TFT180_RES_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(TFT180_CS_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(TFT180_BL_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    tft180_set_dir(tft180_display_dir);
    tft180_set_color(tft180_pencolor, tft180_bgcolor);

    TFT180_RST(0);
    system_delay_ms(10);

    TFT180_RST(1);
    system_delay_ms(120);
    TFT180_CS(0);

    tft180_write_index(0x11);
    system_delay_ms(120);

    tft180_write_index(0xB1);
    tft180_write_8bit_data(0x01);
    tft180_write_8bit_data(0x2C);
    tft180_write_8bit_data(0x2D);

    tft180_write_index(0xB2);
    tft180_write_8bit_data(0x01);
    tft180_write_8bit_data(0x2C);
    tft180_write_8bit_data(0x2D);

    tft180_write_index(0xB3);
    tft180_write_8bit_data(0x01);
    tft180_write_8bit_data(0x2C);
    tft180_write_8bit_data(0x2D);
    tft180_write_8bit_data(0x01);
    tft180_write_8bit_data(0x2C);
    tft180_write_8bit_data(0x2D);

    tft180_write_index(0xB4);
    tft180_write_8bit_data(0x07);

    tft180_write_index(0xC0);
    tft180_write_8bit_data(0xA2);
    tft180_write_8bit_data(0x02);
    tft180_write_8bit_data(0x84);
    tft180_write_index(0xC1);
    tft180_write_8bit_data(0xC5);

    tft180_write_index(0xC2);
    tft180_write_8bit_data(0x0A);
    tft180_write_8bit_data(0x00);

    tft180_write_index(0xC3);
    tft180_write_8bit_data(0x8A);
    tft180_write_8bit_data(0x2A);
    tft180_write_index(0xC4);
    tft180_write_8bit_data(0x8A);
    tft180_write_8bit_data(0xEE);

    tft180_write_index(0xC5);
    tft180_write_8bit_data(0x0E);

    tft180_write_index(0x36);
    switch(tft180_display_dir)                                                  // y x v
    {
        case TFT180_PORTAIT:        tft180_write_8bit_data(1<<7 | 1<<6 | 0<<5);  break;
        case TFT180_PORTAIT_180:    tft180_write_8bit_data(0<<7 | 0<<6 | 0<<5);  break;
        case TFT180_CROSSWISE:      tft180_write_8bit_data(1<<7 | 0<<6 | 1<<5);  break;
        case TFT180_CROSSWISE_180:  tft180_write_8bit_data(0<<7 | 1<<6 | 1<<5);  break;
    }

    tft180_write_index(0xe0);
    tft180_write_8bit_data(0x0f);
    tft180_write_8bit_data(0x1a);
    tft180_write_8bit_data(0x0f);
    tft180_write_8bit_data(0x18);
    tft180_write_8bit_data(0x2f);
    tft180_write_8bit_data(0x28);
    tft180_write_8bit_data(0x20);
    tft180_write_8bit_data(0x22);
    tft180_write_8bit_data(0x1f);
    tft180_write_8bit_data(0x1b);
    tft180_write_8bit_data(0x23);
    tft180_write_8bit_data(0x37);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x07);
    tft180_write_8bit_data(0x02);
    tft180_write_8bit_data(0x10);

    tft180_write_index(0xe1);
    tft180_write_8bit_data(0x0f);
    tft180_write_8bit_data(0x1b);
    tft180_write_8bit_data(0x0f);
    tft180_write_8bit_data(0x17);
    tft180_write_8bit_data(0x33);
    tft180_write_8bit_data(0x2c);
    tft180_write_8bit_data(0x29);
    tft180_write_8bit_data(0x2e);
    tft180_write_8bit_data(0x30);
    tft180_write_8bit_data(0x30);
    tft180_write_8bit_data(0x39);
    tft180_write_8bit_data(0x3f);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x07);
    tft180_write_8bit_data(0x03);
    tft180_write_8bit_data(0x10);

    tft180_write_index(0x2a);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x00 + 2);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x80 + 2);

    tft180_write_index(0x2b);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x00 + 3);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x80 + 3);

    tft180_write_index(0xF0);
    tft180_write_8bit_data(0x01);
    tft180_write_index(0xF6);
    tft180_write_8bit_data(0x00);

    tft180_write_index(0x3A);
    tft180_write_8bit_data(0x05);
    tft180_write_index(0x29);
    TFT180_CS(1);

    tft180_clear();
    tft180_debug_init();
}
