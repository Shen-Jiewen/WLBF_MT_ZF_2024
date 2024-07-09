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
* �ļ�����          zf_device_wifi_spi
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.20
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2024-01-18        SeekFree            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   RST                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_RST_PIN �궨��
*                   INT                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_INT_PIN �궨��
*                   CS                  �鿴 zf_device_wifi_spi.h �� WIFI_SPI_CS_PIN �궨��
*                   MISO                �鿴 zf_device_wifi_spi.h �� WIFI_SPI_MISO_PIN �궨��
*                   SCK                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_SCK_PIN �궨��
*                   MOSI                �鿴 zf_device_wifi_spi.h �� WIFI_SPI_MOSI_PIN �궨��
*                   5V                  5V ��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
*********************************************************************************************************************/

#ifndef _zf_device_wifi_spi_h
#define _zf_device_wifi_spi_h

#include "zf_common_typedef.h"

          
#define WIFI_SPI_INDEX              (SPI_3             )        // ����ʹ�õ�SPI��
#define WIFI_SPI_SPEED              (30 * 1000 * 1000  )        // Ӳ�� SPI ����
#define WIFI_SPI_SCK_PIN            (SPI3_SCLK_P22_3   )        // ����SPI_SCK����
#define WIFI_SPI_MOSI_PIN           (SPI3_MOSI_P22_0   )        // ����SPI_MOSI����
#define WIFI_SPI_MISO_PIN           (SPI3_MISO_P22_1   )        // ����SPI_MISO����  IPSû��MISO���ţ�����������Ȼ��Ҫ���壬��spi�ĳ�ʼ��ʱ��Ҫʹ��
#define WIFI_SPI_CS_PIN             (P22_2             )        // ����SPI_CS���� �������CS����
#define WIFI_SPI_INT_PIN            (P15_8             )        // ������������
#define WIFI_SPI_RST_PIN            (P23_1             )        // ���帴λ����


#define WIFI_SPI_RECVIVE_FIFO_SIZE  (1024)                      // ����FIFO��С
#define WIFI_SPI_READ_TRANSFER      (1)                         // �ڵ���wifi_spi_read_buffer �Ƿ��Է���SPIͨѶ�����ģ�����Ƿ���������Ҫ��ȡ 1������SPIͨѶ 0��������SPIͨѶ������ȡFIFO
                                                                // ���Ӧ�ó�����û���κεĵط����÷��ͺ�������WIFI_SPI_READ_TRANSFER��������Ϊ1
                                                                
#define WIFI_SPI_AUTO_CONNECT       (0)                         // �����Ƿ��ʼ��ʱ����TCP����UDP����    0-���Զ�����  1-�Զ�����TCP������  2-�Զ�����UDP

#if     (WIFI_SPI_AUTO_CONNECT > 2)    
#error "WIFI_SPI_AUTO_CONNECT ��ֵֻ��Ϊ [0,1,2]"
#else   
#define WIFI_SPI_TARGET_IP          "192.168.137.1"              // ����Ŀ��� IP
#define WIFI_SPI_TARGET_PORT        "8080"                      // ����Ŀ��Ķ˿�
#define WIFI_SPI_LOCAL_PORT         "6666"                      // �����Ķ˿� 0�����  �����÷�Χ2048-65535  Ĭ�� 6666
#endif


#define WIFI_SPI_RECVIVE_SIZE       (32)                        // ÿ��SPI������յ��ֽ��� �������޸�
#define WIFI_SPI_TRANSFER_SIZE      (4088)                      // ���SPI������յ��ֽ��� �������޸�



typedef enum
{
    // �������͵�����
    WIFI_SPI_INVALID1               = 0x00,                     // ��Ч���ݰ�
    WIFI_SPI_RESET                  = 0x01,                     // ��λ����
    WIFI_SPI_DATA                   = 0x02,                     // ͸�����ݰ�
    WIFI_SPI_UDP_SEND               = 0x03,                     // UDP��������������,Ĭ��SPI�������ݺ�2MSδ�յ������Զ���������
    WIFI_SPI_CLOSE_SOCKET           = 0x04,                     // �Ͽ�����
                
    WIFI_SPI_SET_WIFI_INFORMATION   = 0x10,                     // ����WIFI��Ϣ����
    WIFI_SPI_SET_SOCKET_INFORMATION = 0x11,                     // ����SOCKET��Ϣ����
                    
    WIFI_SPI_GET_VERSION            = 0x20,                     // ��ȡģ��汾
    WIFI_SPI_GET_MAC_ADDR           = 0x21,                     // ��ȡģ��MAC��ַ
    WIFI_SPI_GET_IP_ADDR            = 0x22,                     // ��ȡģ��IP��ַ
                    
    // �ӻ��ش�������
    WIFI_SPI_REPLY_OK               = 0x80,                     // �ӻ�Ӧ�����ȷ����
    WIFI_SPI_REPLY_ERROR            = 0x81,                     // �ӻ�Ӧ��Ĵ�������
                    
    WIFI_SPI_REPLY_DATA_START       = 0x90,                     // �ӻ��ش������ݰ������һ���������Ҫ������ȡ
    WIFI_SPI_REPLY_DATA_END         = 0x91,                     // �ӻ��ش������ݰ��������Ѷ�ȡ���
                    
    WIFI_SPI_REPLY_VERSION          = 0xA0,                     // �ӻ��ظ��̼��汾
    WIFI_SPI_REPLY_MAC_ADDR         = 0xA1,                     // �ӻ��ظ�����MAC��ַ����Ϣ
    WIFI_SPI_REPLY_IP_ADDR          = 0xA2,                     // �ӻ��ظ�����IP��ַ���˿ں�
    WIFI_SPI_INVALID2               = 0xFF                      // ��Ч���ݰ�
}wifi_spi_packets_command_enum;             
                
typedef enum                
{               
    WIFI_SPI_IDLE,                                              // ģ����У����Խ���SPIͨѶ
    WIFI_SPI_BUSY,                                              // ģ����æ�����ɽ���SPIͨѶ
}wifi_spi_state_enum;               
                
                
typedef struct              
{               
    uint8   command;                                            // ������
    uint8   reserve;                                            // ����
    uint16  length;                                             // ����Ч����
}wifi_spi_head_struct;              
                
                
typedef struct              
{               
    wifi_spi_head_struct  head;                                 // ֡ͷ
    uint8 buffer[WIFI_SPI_RECVIVE_SIZE];                        // ������
}wifi_spi_packets_struct;               
                
                
extern char wifi_spi_version[12];                               // �̼��汾         �ַ���
extern char wifi_spi_mac_addr[20];                              // ģ��MAC��ַ      �ַ���
extern char wifi_spi_ip_addr_port[25];                          // IP��ַ��˿ں�   �ַ���

uint8  wifi_spi_wifi_connect        (char *wifi_ssid, char *pass_word);
uint8  wifi_spi_socket_connect      (char *transport_type, char *ip_addr, char *port, char *local_port);
uint8  wifi_spi_socket_disconnect   (void);
uint8  wifi_spi_udp_send_now        (void);
uint32 wifi_spi_send_buffer         (const uint8 *buff, uint32 length);
uint32 wifi_spi_read_buffer         (uint8 *buffer, uint32 length);

uint8  wifi_spi_init                (char *wifi_ssid, char *pass_word);

#endif

