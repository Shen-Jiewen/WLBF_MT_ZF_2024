/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ���������
* �����Ը���������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù�������֤��������
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
* ����Դ��ʹ�� GPL3.0 ��Դ����֤Э�� ������������Ϊ���İ汾
* ��������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ����֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_common_typedef
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.20
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding             first version
********************************************************************************************************************/

#ifndef _zf_common_typedef_h_
#define _zf_common_typedef_h_

#include "math.h"
#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"
#include "string.h"
#include "stdlib.h"
#include "ifx_types.h"
#include "PLATFORM_TYPES.H"
//=================================================== ���Ͷ��� ===================================================

//#define COMPATIBLE_WITH_OLDER_VERSIONS                                          // ���ݾɰ濪Դ��ӿ�
#define USE_ZF_TYPEDEF      (1)                                                 // �Ƿ��������Ͷ�������
#if USE_ZF_TYPEDEF
// ������������
// ����ʹ�� stdint.h ������������� �����ͻ ������Բü�
typedef signed char         int8;                                               // �з���  8 bits
typedef signed short int    int16;                                              // �з��� 16 bits
typedef signed int          int32;                                              // �з��� 32 bits
typedef signed long long    int64;                                              // �з��� 64 bits

typedef volatile uint8      vuint8;                                             // �ױ������� �޷���  8 bits
typedef volatile uint16     vuint16;                                            // �ױ������� �޷��� 16 bits
typedef volatile uint32     vuint32;                                            // �ױ������� �޷��� 32 bits
typedef volatile uint64     vuint64;                                            // �ױ������� �޷��� 64 bits

typedef volatile int8       vint8;                                              // �ױ������� �з���  8 bits
typedef volatile int16      vint16;                                             // �ױ������� �з��� 16 bits
typedef volatile int32      vint32;                                             // �ױ������� �з��� 32 bits
typedef volatile int64      vint64;                                             // �ױ������� �з��� 64 bits

//typedef volatile float      fp32;
typedef float fp32;
#endif

#define ZF_ENABLE       (1)
#define ZF_DISABLE      (0)

#define ZF_TRUE         (1)
#define ZF_FALSE        (0)

#define ZF_WEAK         __attribute__((weak))
//=================================================== ���Ͷ��� ===================================================

#endif