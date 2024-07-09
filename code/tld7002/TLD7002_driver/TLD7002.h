/**
 *  @file TLD7002.h
 *  @author Infineon
 *  @date 17.06.2022
 *	@brief TLD7002 specific Device Driver implementation from Infineon Technologies AG.
 *	@note  This file includes the implementation for the TLD7002 hardware access layer.
 *
 ***********************************************************************************************************************
 *
 * Copyright (c) 2022, Infineon Technologies AG
 * All rights reserved.
 *
 **********************************************************************************************************************
 */

/**
 * @addtogroup TLD7002_CONTROL_LAYER
 * @{
 */

#ifndef TLD7002_H_
#define TLD7002_H_

/******************************************************************************/
/*	Includes																  */
/******************************************************************************/
/** Definition for external type definition include file */
#define TLD7002_INCLUDE_EXT_TYPEDEF							1			/**< external types.h shall be included */

#if(TLD7002_INCLUDE_EXT_TYPEDEF)
#include "Platform_Types.h"
#endif

/******************************************************************************/
/*	UART over CAN frame and field content definitions 					 	  */
/******************************************************************************/
/* Implements DD-SWA-332 */

/** Definition for frame SYNC byte */
#define TLD7002_FRAME_SYNC_MSG								  0x55U		/**< sync message */

/** Definition for frame RES_BYTE */
#define TLD7002_FRAME_RES_BYTE								  0x00U		/**< reserved byte */

/** Definition for frame slave addresses */
#define TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST				   0x0U		/**< broadcast message */
#define TLD7002_FRAME_SLAVE_ADDRESS_1						   0x1U		/**< slave address  1 */
#define TLD7002_FRAME_SLAVE_ADDRESS_2						   0x2U		/**< slave address  2 */
#define TLD7002_FRAME_SLAVE_ADDRESS_3						   0x3U		/**< slave address  3 */
#define TLD7002_FRAME_SLAVE_ADDRESS_4						   0x4U		/**< slave address  4 */
#define TLD7002_FRAME_SLAVE_ADDRESS_5						   0x5U		/**< slave address  5 */
#define TLD7002_FRAME_SLAVE_ADDRESS_6						   0x6U		/**< slave address  6 */
#define TLD7002_FRAME_SLAVE_ADDRESS_7						   0x7U		/**< slave address  7 */
#define TLD7002_FRAME_SLAVE_ADDRESS_8						   0x8U		/**< slave address  8 */
#define TLD7002_FRAME_SLAVE_ADDRESS_9						   0x9U		/**< slave address  9 */
#define TLD7002_FRAME_SLAVE_ADDRESS_10						   0xAU		/**< slave address 10 */
#define TLD7002_FRAME_SLAVE_ADDRESS_11						   0xBU		/**< slave address 11 */
#define TLD7002_FRAME_SLAVE_ADDRESS_12						   0xCU		/**< slave address 12 */
#define TLD7002_FRAME_SLAVE_ADDRESS_13						   0xDU		/**< slave address 13 */
#define TLD7002_FRAME_SLAVE_ADDRESS_14						   0xEU		/**< slave address 14 */
#define TLD7002_FRAME_SLAVE_ADDRESS_15						   0xFU		/**< slave address 15 */
#define TLD7002_FRAME_SLAVE_ADDRESS_16						  0x10U		/**< slave address 16 */
#define TLD7002_FRAME_SLAVE_ADDRESS_17						  0x11U		/**< slave address 17 */
#define TLD7002_FRAME_SLAVE_ADDRESS_18						  0x12U		/**< slave address 18 */
#define TLD7002_FRAME_SLAVE_ADDRESS_19						  0x13U		/**< slave address 19 */
#define TLD7002_FRAME_SLAVE_ADDRESS_20						  0x14U		/**< slave address 20 */
#define TLD7002_FRAME_SLAVE_ADDRESS_21						  0x15U		/**< slave address 21 */
#define TLD7002_FRAME_SLAVE_ADDRESS_22						  0x16U		/**< slave address 22 */
#define TLD7002_FRAME_SLAVE_ADDRESS_23						  0x17U		/**< slave address 23 */
#define TLD7002_FRAME_SLAVE_ADDRESS_24						  0x18U		/**< slave address 24 */
#define TLD7002_FRAME_SLAVE_ADDRESS_25						  0x19U		/**< slave address 25 */
#define TLD7002_FRAME_SLAVE_ADDRESS_26						  0x1AU		/**< slave address 26 */
#define TLD7002_FRAME_SLAVE_ADDRESS_27						  0x1BU		/**< slave address 27 */
#define TLD7002_FRAME_SLAVE_ADDRESS_28						  0x1CU		/**< slave address 28 */
#define TLD7002_FRAME_SLAVE_ADDRESS_29						  0x1DU		/**< slave address 29 */
#define TLD7002_FRAME_SLAVE_ADDRESS_30						  0x1EU		/**< slave address 30 */
#define TLD7002_FRAME_SLAVE_ADDRESS_31						  0x1FU		/**< slave address 31 */

/** Definition for frame SLAVE_ADDRESS_CRC */
#define TLD7002_FRAME_SLAVE_ADDRESS_NO_CRC					  0x00U		/**< no slave address CRC */

/** TLD7002_FRAME_CRC_ADDRESS_t
 *
 */
typedef struct
{
    uint8 ADDRESS;														/*!< [0..4] Address */
    uint8 CRC;															/*!< [5..7] CRC */
} TLD7002_FRAME_CRC_ADDRESS_t;

/** FRAME_CRC_ADDRESS masks */
#define TLD7002_CRC_ADDRESS_ADDRESS_MSK						  0x1FU		/*!< [0..4] Address */
#define TLD7002_CRC_ADDRESS_CRC_MSK							  0xE0U		/*!< [5..7] CRC */

/** FRAME_CRC_ADDRESS positions */
#define TLD7002_CRC_ADDRESS_ADDRESS_POS						    0U		/*!< [0..4] Address */
#define TLD7002_CRC_ADDRESS_CRC_POS							    5U		/*!< [5..7] CRC */

/** Definition for frame FUN to represent the desired function request */
#define TLD7002_FRAME_FUN_BRDC_DC_SYNC						   0x0U		/**< Broadcast duty cycle synchronization */
#define TLD7002_FRAME_FUN_DC_UPDATE							   0x1U		/**< Duty cycle shadow register update */
#define TLD7002_FRAME_FUN_READ_OST							   0x2U		/**< Request diagnostics */
#define TLD7002_FRAME_FUN_HWCR								   0x3U		/**< Hardware control frame */
#define TLD7002_FRAME_FUN_WRITE_REG							   0x4U		/**< Write register */
#define TLD7002_FRAME_FUN_READ_REG							   0x5U		/**< Read register */
#define TLD7002_FRAME_FUN_PM_CHANGE							   0x6U		/**< Power mode change */
#define TLD7002_FRAME_FUN_RESERVED							   0x7U		/**< Reserved */

/** Definition for frame DLC to represent the Data Length Code, 3 Bit. Represented in words - multiple of 2 bytes */
#define TLD7002_FRAME_DLC_0									   0x0U		/**< 0 words, 0 bytes */
#define TLD7002_FRAME_DLC_1									   0x1U		/**< 1 word, 2 bytes */
#define TLD7002_FRAME_DLC_2									   0x2U		/**< 2 words, 4 bytes */
#define TLD7002_FRAME_DLC_3									   0x3U		/**< 4 words, 8 bytes */
#define TLD7002_FRAME_DLC_4									   0x4U		/**< 8 words, 16 bytes */
#define TLD7002_FRAME_DLC_5									   0x5U		/**< 12 words, 24 bytes */
#define TLD7002_FRAME_DLC_6									   0x6U		/**< 16 words, 32 bytes */
#define TLD7002_FRAME_DLC_7									   0x7U		/**< 32 words, 64 bytes */

/** Definition for frame RC_2BIT.
 *  The rolling counter is a 2 bit counter value, has to be incremented in every
 *  data transmission. 0x00 default (start) value
 */
#define TLD7002_FRAME_RC_2BIT_START_VALUE					   0x0U		/**< default (start) value */
#define TLD7002_FRAME_RC_2BIT_0								   0x0U
#define TLD7002_FRAME_RC_2BIT_1								   0x1U
#define TLD7002_FRAME_RC_2BIT_2								   0x2U
#define TLD7002_FRAME_RC_2BIT_3								   0x3U

/** TLD7002_FRAME_MRC_DLC_FUN_t
 *
 */
typedef struct
{
    uint8 FUN;															/*!< [0..2] Function */
    uint8 DLC;															/*!< [3..5] Data Length Code */
    uint8 MRC;                                                          /*!< [6..7] Rolling Counter,  master needs to
                                                                         * increment in every data transmission*/
} TLD7002_FRAME_MRC_DLC_FUN_t;

/** FRAME_MRC_DLC_FUN masks */
#define TLD7002_MRC_DLC_FUN_FUN_MSK							  0x07U		/*!< [0..2] Function */
#define TLD7002_MRC_DLC_FUN_DLC_MSK							  0x38U		/*!< [3..5] Data Length Code */
#define TLD7002_MRC_DLC_FUN_MRC_MSK 0xC0U                               /*!< [6..7] Rolling Counter,  master needs to
                                                                         * increment in every data transmission*/
/** FRAME_MRC_DLC_FUN positions */
#define TLD7002_MRC_DLC_FUN_FUN_POS							    0U		/*!< [0..2] Function */
#define TLD7002_MRC_DLC_FUN_DLC_POS							    3U		/*!< [3..5] Data Length Code */
#define TLD7002_MRC_DLC_FUN_MRC_POS 6U                                  /*!< [6..7] Rolling Counter,  master needs to
                                                                         * increment in every data transmission*/
/** TLD7002_FRAME_OUTPUT_STATUS_BYTE_t
 *
 */
typedef struct
{
    boolean OSB_FAULT;                                                  /*!< [0] Internal fault flag. 0: no internal
                                                                         * fault detected; 1: internal fault condition
                                                                         * detected */
    boolean OVLD;                                                       /*!< [1] Over load flag. 0: no overload
                                                                         * condition detected on OUT0 to OUT15; 1: there
                                                                         * was at least one overload condition detected
                                                                         * */
    boolean VFWD_WRN;                                                   /*!< [2] Forward voltage warning flag. 0: no
                                                                         * forward voltage warning for OUT0 to OUT15
                                                                         * detected; 1: there was at least one forward
                                                                         * voltage warning condition */
    boolean CUR_WRN;                                                    /*!< [3] Output current warning flag. 0: no
                                                                         * output current warning for OUT0 to OUT15
                                                                         * detected; 1: there was at least one output
                                                                         * current warning condition */
    boolean DC_WRN;                                                     /*!< [4] Duty cycle warning flag. 0: no duty
                                                                         * cycle warning for OUT0 to OUT15 detected; 1:
                                                                         * there was at least one duty cycle warning
                                                                         * condition */
    boolean GPINn_WRN;                                                  /*!< [5] GPINn warning flag. 0: GPIN0 and GPIN1
                                                                         * are not in a fault condition; 1: there was at
                                                                         * least one GPINn fault condition or GPINn
                                                                         * adjacent short condition */
    boolean OUT_SHRT_WRN;                                               /*!< [6] short between adjacent output warning.
                                                                         * 0: no short between adjacent output warning
                                                                         * detected; 1: there was at least one short
                                                                         * between an adjacent output warning detected
                                                                         * */
    boolean VLED_VS_UV;                                                 /*!< [7] VLED/VS under voltage flag. 0: if
                                                                         * (V_LED AND V_S) is above V_DEN_threshold ; 1:
                                                                         * there was at least one under voltage
                                                                         * condition event detected */
} TLD7002_FRAME_OUTPUT_STATUS_BYTE_t;


/** FRAME_OUTPUT_STATUS_BYTE masks */
#define TLD7002_OUTPUT_STATUS_BYTE_FAULT_MSK        (1U << 0U)          /*!< [0] Internal fault flag. 0: no internal
                                                                         * fault detected; 1: internal fault condition
                                                                         * detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OVLD_MSK         (1U << 1U)          /*!< [1] Over load flag. 0: no overload
                                                                         * condition detected on OUT0 to OUT15; 1: there
                                                                         * was at least one overload condition detected
                                                                         * */
#define TLD7002_OUTPUT_STATUS_BYTE_VFWD_WRN_MSK     (1U << 2U)          /*!< [2] Forward voltage warning flag. 0: no
                                                                         * forward voltage warning for OUT0 to OUT15
                                                                         * detected; 1: there was at least one forward
                                                                         * voltage warning condition */
#define TLD7002_OUTPUT_STATUS_BYTE_CUR_WRN_MSK      (1U << 3U)          /*!< [3] Output current warning flag. 0: no
                                                                         * output current warning for OUT0 to OUT15
                                                                         * detected; 1: there was at least one output
                                                                         * current warning condition */
#define TLD7002_OUTPUT_STATUS_BYTE_DC_WRN_MSK       (1U << 4U)          /*!< [4] Duty cycle warning flag. 0: no duty
                                                                         * cycle warning for OUT0 to OUT15 detected; 1:
                                                                         * there was at least one duty cycle warning
                                                                         * condition */
#define TLD7002_OUTPUT_STATUS_BYTE_GPINn_WRN_MSK    (1U << 5U)          /*!< [5] GPINn warning flag. 0: GPIN0 and GPIN1
                                                                         * are not in a fault condition; 1: there was at
                                                                         * least one GPINn fault condition or GPINn
                                                                         * adjacent short condition */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_SHRT_WRN_MSK (1U << 6U)          /*!< [6] short between adjacent output warning.
                                                                         * 0: no short between adjacent output warning
                                                                         * detected; 1: there was at least one short
                                                                         * between an adjacent output warning detected
                                                                         * */
#define TLD7002_OUTPUT_STATUS_BYTE_VLED_VS_UV_MSK   (1U << 7U)          /*!< [7] VLED/VS under voltage flag. 0: if
                                                                         * (V_LED AND V_S) is above V_DEN_threshold ; 1:
                                                                         * there was at least one under voltage
                                                                         * condition event detected */

/** FRAME_OUTPUT_STATUS_BYTE positions */
#define TLD7002_OUTPUT_STATUS_BYTE_FAULT_POS        0U                  /*!< [0] Internal fault flag. 0: no internal
                                                                         * fault detected; 1: internal fault condition
                                                                         * detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OVLD_POS         1U                  /*!< [1] Over load flag. 0: no overload
                                                                         * condition detected on OUT0 to OUT15; 1: there
                                                                         * was at least one overload condition detected
                                                                         * */
#define TLD7002_OUTPUT_STATUS_BYTE_VFWD_WRN_POS     2U                  /*!< [2] Forward voltage warning flag. 0: no
                                                                         * forward voltage warning for OUT0 to OUT15
                                                                         * detected; 1: there was at least one forward
                                                                         * voltage warning condition */
#define TLD7002_OUTPUT_STATUS_BYTE_CUR_WRN_POS      3U                  /*!< [3] Output current warning flag. 0: no
                                                                         * output current warning for OUT0 to OUT15
                                                                         * detected; 1: there was at least one output
                                                                         * current warning condition */
#define TLD7002_OUTPUT_STATUS_BYTE_DC_WRN_POS       4U                  /*!< [4] Duty cycle warning flag. 0: no duty
                                                                         * cycle warning for OUT0 to OUT15 detected; 1:
                                                                         * there was at least one duty cycle warning
                                                                         * condition */
#define TLD7002_OUTPUT_STATUS_BYTE_GPINn_WRN_POS    5U                  /*!< [5] GPINn warning flag. 0: GPIN0 and GPIN1
                                                                         * are not in a fault condition; 1: there was at
                                                                         * least one GPINn fault condition or GPINn
                                                                         * adjacent short condition */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_SHRT_WRN_POS 6U                  /*!< [6] short between adjacent output warning.
                                                                         * 0: no short between adjacent output warning
                                                                         * detected; 1: there was at least one short
                                                                         * between an adjacent output warning detected
                                                                         * */
#define TLD7002_OUTPUT_STATUS_BYTE_VLED_VS_UV_POS   7U                  /*!< [7] VLED/VS under voltage flag. 0: if
                                                                         * (V_LED AND V_S) is above V_DEN_threshold ; 1:
                                                                         * there was at least one under voltage
                                                                         * condition event detected */

/** FRAME_DC_UPDATE_14BITDCVAL masks */
#define TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK 0x3FFFU             /*!< [0..14] Duty Cycle */
#define TLD7002_DC_UPDATE_14BITDCVAL_RESERVED_MSK   0xC000U             /*!< [15..16] RESERVED */

/** FRAME_DC_UPDATE_14BITDCVAL positions */
#define TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_POS 0U                  /*!< [0..14] Duty Cycle */
#define TLD7002_DC_UPDATE_14BITDCVAL_RESERVED_POS   15U                 /*!< [15..16] RESERVED */

/** TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t
 *
 */
typedef struct
{
    boolean OUT_STAT;                                                   /*!< [0] Output state flag. 0: power output
                                                                         * channel is in OFF state; 1: power output
                                                                         * channel is in ON state */
    boolean VFWD_WRN;                                                   /*!< [1] Forward voltage warning flag. 0: no
                                                                         * forward voltage warning detected; 1: there
                                                                         * was at least one forward voltage warning
                                                                         * condition detected */
    boolean CUR_WRN;                                                    /*!< [2] Output current warning flag. 0: no
                                                                         * output current warning detected; 1: there was
                                                                         * at least one output current warning condition
                                                                         * detected */
    boolean DC_WRN;                                                     /*!< [3] Duty cycle warning flag. 0: no duty
                                                                         * cycle warning detected; 1: there was at least
                                                                         * one duty cycle warning condition detected */
    boolean OUT_SHORT_WRN;                                              /*!< [4] Short between adjacent output warning
                                                                         * flag. 0: no short between adjacent output
                                                                         * warning detected; 1: there was at least one
                                                                         * short between an adjacent output warning
                                                                         * detected */
    boolean OVLD;                                                       /*!< [5] OVLD flag. 0: no OVLD condition
                                                                         * detected; 1: there was at least one OVLD
                                                                         * condition since the last read out */
    boolean SLS;                                                        /*!< [6] Single LED Short (SLS) flag. 0: no SLS
                                                                         * condition detected; 1: there was at least one
                                                                         * single LED short detected */
    boolean OL;                                                         /*!< [7] Open load flag. 0: no open load
                                                                         * condition detected; 1: there was at least one
                                                                         * open load condition detected */
} TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t;

/** FRAME_OUTPUT_STATUS_BYTE_OUT masks */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_OUT_STAT_MSK      (1U << 0U)     /*!< [0] Output state flag. 0: power output
                                                                         * channel is in OFF state; 1: power output
                                                                         * channel is in ON state */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_VFWD_WRN_MSK      (1U << 1U)     /*!< [1] Forward voltage warning flag. 0: no
                                                                         * forward voltage warning detected; 1: there
                                                                         * was at least one forward voltage warning
                                                                         * condition detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_CUR_WRN_MSK       (1U << 2U)     /*!< [2] Output current warning flag. 0: no
                                                                         * output current warning detected; 1: there was
                                                                         * at least one output current warning condition
                                                                         * detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_DC_WRN_MSK        (1U << 3U)     /*!< [3] Duty cycle warning flag. 0: no duty
                                                                         * cycle warning detected; 1: there was at least
                                                                         * one duty cycle warning condition detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_OUT_SHORT_WRN_MSK (1U << 4U)     /*!< [4] Short between adjacent output warning
                                                                         * flag. 0: no short between adjacent output
                                                                         * warning detected; 1: there was at least one
                                                                         * short between an adjacent output warning
                                                                         * detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_OVLD_MSK          (1U << 5U)     /*!< [5] OVLD flag. 0: no OVLD condition
                                                                         * detected; 1: there was at least one OVLD
                                                                         * condition since the last read out */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_SLS_MSK           (1U << 6U)     /*!< [6] Single LED Short (SLS) flag. 0: no SLS
                                                                         * condition detected; 1: there was at least one
                                                                         * single LED short detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_OL_MSK            (1U << 7U)     /*!< [7] Open load flag. 0: no open load
                                                                         * condition detected; 1: there was at least one
                                                                         * open load condition detected */

/** FRAME_OUTPUT_STATUS_BYTE_OUT positions */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_OUT_STAT_POS      0U             /*!< [0] Output state flag. 0: power output
                                                                         * channel is in OFF state; 1: power output
                                                                         * channel is in ON state */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_VFWD_WRN_POS      1U             /*!< [1] Forward voltage warning flag. 0: no
                                                                         * forward voltage warning detected; 1: there
                                                                         * was at least one forward voltage warning
                                                                         * condition detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_CUR_WRN_POS       2U             /*!< [2] Output current warning flag. 0: no
                                                                         * output current warning detected; 1: there was
                                                                         * at least one output current warning condition
                                                                         * detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_DC_WRN_POS        3U             /*!< [3] Duty cycle warning flag. 0: no duty
                                                                         * cycle warning detected; 1: there was at least
                                                                         * one duty cycle warning condition detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_OUT_SHORT_WRN_POS 4U             /*!< [4] Short between adjacent output warning
                                                                         * flag. 0: no short between adjacent output
                                                                         * warning detected; 1: there was at least one
                                                                         * short between an adjacent output warning
                                                                         * detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_OVLD_POS          5U             /*!< [5] OVLD flag. 0: no OVLD condition
                                                                         * detected; 1: there was at least one OVLD
                                                                         * condition since the last read out */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_SLS_POS           6U             /*!< [6] Single LED Short (SLS) flag. 0: no SLS
                                                                         * condition detected; 1: there was at least one
                                                                         * single LED short detected */
#define TLD7002_OUTPUT_STATUS_BYTE_OUT_OL_POS            7U             /*!< [7] Open load flag. 0: no open load
                                                                         * condition detected; 1: there was at least one
                                                                         * open load condition detected */

/** TLD7002_FRAME_HWCR_RESET_OUT_t
 *
 */
typedef struct
{
    boolean RES_OUT0;													/*!< [0] RESET OUT0 */
    boolean RES_OUT1;													/*!< [1] RESET OUT1 */
    boolean RES_OUT2;													/*!< [2] RESET OUT2 */
    boolean RES_OUT3;													/*!< [3] RESET OUT3 */
    boolean RES_OUT4;													/*!< [4] RESET OUT4 */
    boolean RES_OUT5;													/*!< [5] RESET OUT5 */
    boolean RES_OUT6;													/*!< [6] RESET OUT6 */
    boolean RES_OUT7;													/*!< [7] RESET OUT7 */
    boolean RES_OUT8;													/*!< [8] RESET OUT8 */
    boolean RES_OUT9;													/*!< [9] RESET OUT9 */
    boolean RES_OUT10;													/*!< [10] RESET OUT10 */
    boolean RES_OUT11;													/*!< [11] RESET OUT11 */
    boolean RES_OUT12;													/*!< [12] RESET OUT12 */
    boolean RES_OUT13;													/*!< [13] RESET OUT13 */
    boolean RES_OUT14;													/*!< [14] RESET OUT14 */
    boolean RES_OUT15;													/*!< [15] RESET OUT15 */
} TLD7002_FRAME_HWCR_RESET_OUT_t;

/** FRAME_HWCR_RESET_OUT masks */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT0_MSK				(1U << 0U)	/*!< [0] RESET OUT0 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT1_MSK				(1U << 1U)	/*!< [1] RESET OUT1 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT2_MSK				(1U << 2U)	/*!< [2] RESET OUT2 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT3_MSK				(1U << 3U)	/*!< [3] RESET OUT3 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT4_MSK				(1U << 4U)	/*!< [4] RESET OUT4 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT5_MSK				(1U << 5U)	/*!< [5] RESET OUT5 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT6_MSK				(1U << 6U)	/*!< [6] RESET OUT6 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT7_MSK				(1U << 7U)	/*!< [7] RESET OUT7 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT8_MSK				(1U << 8U)	/*!< [8] RESET OUT8 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT9_MSK				(1U << 9U)	/*!< [9] RESET OUT9 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT10_MSK				(1U << 10U)	/*!< [10] RESET OUT10 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT11_MSK				(1U << 11U)	/*!< [11] RESET OUT11 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT12_MSK				(1U << 12U)	/*!< [12] RESET OUT12 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT13_MSK				(1U << 13U)	/*!< [13] RESET OUT13 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT14_MSK				(1U << 14U)	/*!< [14] RESET OUT14 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT15_MSK				(1U << 15U)	/*!< [15] RESET OUT15 */

/** FRAME_HWCR_RESET_OUT positions */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT0_POS				    0U		/*!< [0] RESET OUT0 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT1_POS				    1U		/*!< [1] RESET OUT1 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT2_POS				    2U		/*!< [2] RESET OUT2 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT3_POS				    3U		/*!< [3] RESET OUT3 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT4_POS				    4U		/*!< [4] RESET OUT4 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT5_POS				    5U		/*!< [5] RESET OUT5 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT6_POS				    6U		/*!< [6] RESET OUT6 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT7_POS				    7U		/*!< [7] RESET OUT7 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT8_POS				    8U		/*!< [8] RESET OUT8 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT9_POS				    9U		/*!< [9] RESET OUT9 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT10_POS				   10U		/*!< [10] RESET OUT10 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT11_POS				   11U		/*!< [11] RESET OUT11 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT12_POS				   12U		/*!< [12] RESET OUT12 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT13_POS				   13U		/*!< [13] RESET OUT13 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT14_POS				   14U		/*!< [14] RESET OUT14 */
#define TLD7002_HWCR_RESET_OUT_BYTE_OUT15_POS				   15U		/*!< [15] RESET OUT15 */

/** TLD7002_FRAME_HWCR_RESET_STATUS_t
 *  equals FRAME_OUTPUT_STATUS_BYTE_t
 *
 */
typedef TLD7002_FRAME_OUTPUT_STATUS_BYTE_t TLD7002_FRAME_HWCR_RESET_STATUS_t;

/** FRAME_HWCR_RESET_STATUS masks equals FRAME_OUTPUT_STATUS_BYTE */
#define TLD7002_HWCR_RESET_STATUS_FAULT_MSK					TLD7002_OUTPUT_STATUS_BYTE_FAULT_MSK		/*!< Bit 0 */
#define TLD7002_HWCR_RESET_STATUS_OVLD_MSK					TLD7002_OUTPUT_STATUS_BYTE_OVLD_MSK			/*!< Bit 1 */
#define TLD7002_HWCR_RESET_STATUS_VFWD_WRN_MSK				TLD7002_OUTPUT_STATUS_BYTE_VFWD_WRN_MSK		/*!< Bit 2 */
#define TLD7002_HWCR_RESET_STATUS_CUR_WRN_MSK				TLD7002_OUTPUT_STATUS_BYTE_CUR_WRN_MSK		/*!< Bit 3 */
#define TLD7002_HWCR_RESET_STATUS_DC_WRN_MSK				TLD7002_OUTPUT_STATUS_BYTE_DC_WRN_MSK		/*!< Bit 4 */
#define TLD7002_HWCR_RESET_STATUS_GPINn_WRN_MSK				TLD7002_OUTPUT_STATUS_BYTE_GPINn_WRN_MSK	/*!< Bit 5 */
#define TLD7002_HWCR_RESET_STATUS_OUT_SHRT_WRN_MSK			TLD7002_OUTPUT_STATUS_BYTE_OUT_SHRT_WRN_MSK	/*!< Bit 6 */
#define TLD7002_HWCR_RESET_STATUS_VLED_VS_UV_MSK			TLD7002_OUTPUT_STATUS_BYTE_VLED_VS_UV_MSK	/*!< Bit 7 */

/** FRAME_HWCR_RESET_STATUS positions equals FRAME_OUTPUT_STATUS_BYTE */
#define TLD7002_HWCR_RESET_STATUS_FAULT_POS					TLD7002_OUTPUT_STATUS_BYTE_FAULT_POS		/*!< Bit 0 */
#define TLD7002_HWCR_RESET_STATUS_OVLD_POS					TLD7002_OUTPUT_STATUS_BYTE_OVLD_POS			/*!< Bit 1 */
#define TLD7002_HWCR_RESET_STATUS_VFWD_WRN_POS				TLD7002_OUTPUT_STATUS_BYTE_VFWD_WRN_POS		/*!< Bit 2 */
#define TLD7002_HWCR_RESET_STATUS_CUR_WRN_POS				TLD7002_OUTPUT_STATUS_BYTE_CUR_WRN_POS		/*!< Bit 3 */
#define TLD7002_HWCR_RESET_STATUS_DC_WRN_POS				TLD7002_OUTPUT_STATUS_BYTE_DC_WRN_POS		/*!< Bit 4 */
#define TLD7002_HWCR_RESET_STATUS_GPINn_WRN_POS				TLD7002_OUTPUT_STATUS_BYTE_GPINn_WRN_POS	/*!< Bit 5 */
#define TLD7002_HWCR_RESET_STATUS_OUT_SHRT_WRN_POS			TLD7002_OUTPUT_STATUS_BYTE_OUT_SHRT_WRN_POS	/*!< Bit 6 */
#define TLD7002_HWCR_RESET_STATUS_VLED_VS_UV_POS			TLD7002_OUTPUT_STATUS_BYTE_VLED_VS_UV_POS	/*!< Bit 7 */

/** Definition for frame POWER_MODE. Master power mode change byte comprises the commanded power mode state. */
#define TLD7002_FRAME_PM_INIT_MODE							   0x0U		/**< enter init mode */
#define TLD7002_FRAME_PM_RES1								   0x1U		/**< reserved */
#define TLD7002_FRAME_PM_FAIL_SAFE_MODE						   0x2U		/**< enter fail safe mode */
#define TLD7002_FRAME_PM_OTP_MODE							   0x3U		/**< enter OTP mode */

/** TLD7002_FRAME_POWER_MODE_CHANGE_t
 *
 */
typedef uint8 TLD7002_FRAME_POWER_MODE_CHANGE_t;

/** FRAME_POWER_MODE_CHANGE masks */
#define TLD7002_POWER_MODE_CHANGE_POWER_MODE_MSK			  0x07U		/*!< [0..2] Power mode  */
#define TLD7002_POWER_MODE_CHANGE_RESERVED_MSK				  0xF8U		/*!< [3..7] Reserved */


/** FRAME_POWER_MODE_CHANGE positions */
#define TLD7002_POWER_MODE_CHANGE_POWER_MODE_POS			    0U		/*!< [0..2] Power mode  */
#define TLD7002_POWER_MODE_CHANGE_RESERVED_POS				    3U		/*!< [3..7] Reserved */

/** Definition for frame ACK_BYTE_MODE. Rolling Counter, 2 bit counter value. */
#define TLD7002_FRAME_ACK_BYTE_MODE_0						   0x0U		/**< init mode */
#define TLD7002_FRAME_ACK_BYTE_MODE_1						   0x1U		/**< active mode */
#define TLD7002_FRAME_ACK_BYTE_MODE_2						   0x2U		/**< fail-safe mode */
#define TLD7002_FRAME_ACK_BYTE_MODE_3						   0x3U		/**< programming or emulation mode */

/** Definition for frame ACK_BYTE_CRC. */
#define TLD7002_FRAME_ACK_BYTE_NO_CRC						   0x0U		/**< no ack byte CRC */

/** TLD7002_FRAME_ACK_BYTE_t
 *
 */
typedef struct
{
    boolean TER;														/*!< [0] Transmission Error. 0 current frame has been successfully received; 1: the received frame resulted in a CRC8 error */
    uint8 RC;															/*!< [1..2] rolling counter, incremented at every slave response */
    uint8 MODE;															/*!< [3..4] mode */
    uint8 CRC;															/*!< [5..7] CRC3 */
} TLD7002_FRAME_ACK_BYTE_t;

/** FRAME_ACK_BYTE masks */
#define TLD7002_ACK_BYTE_TER_MSK  0x01U                                 /*!< [0] Transmission Error. 0 current frame has
                                                                         * been successfully received; 1: the received
                                                                         * frame resulted in a CRC8 error */
#define TLD7002_ACK_BYTE_RC_MSK   0x06U                                 /*!< [1..2] rolling counter, incremented at
                                                                         * every slave response */
#define TLD7002_ACK_BYTE_MODE_MSK 0x18U                                 /*!< [3..4] mode */
#define TLD7002_ACK_BYTE_CRC_MSK  0xE0U                                 /*!< [5..7] CRC3 */

/** FRAME_ACK_BYTE positions */
#define TLD7002_ACK_BYTE_TER_POS  0U                                    /*!< [0] Transmission Error. 0 current frame has
                                                                         * been successfully received; 1: the received
                                                                         * frame resulted in a CRC8 error */
#define TLD7002_ACK_BYTE_RC_POS   1U                                    /*!< [1..2] rolling counter, incremented at
                                                                         * every slave response */
#define TLD7002_ACK_BYTE_MODE_POS 3U                                    /*!< [3..4] mode */
#define TLD7002_ACK_BYTE_CRC_POS  5U                                    /*!< [5..7] CRC3 */

/******************************************************************************/
/*	UART over CAN frame basic frame component definitions 					  */
/******************************************************************************/
/* Implements DD-SWA-333 */

/** TLD7002_FRAME_HEADER_t
 */
typedef struct
{
    uint8 SYNC;														/*!< sync message */
    TLD7002_FRAME_CRC_ADDRESS_t CRC_REQ_S_ADD;						/*!< CRC and slave address */
    TLD7002_FRAME_MRC_DLC_FUN_t MRC_DLC_FUN;						/*!< MRC, DLC and FUN */
} TLD7002_FRAME_HEADER_t;

/** TLD7002_FRAME_TERMINATION_t
 */
typedef struct
{
    TLD7002_FRAME_OUTPUT_STATUS_BYTE_t OST;							/*!< Output status byte */
    TLD7002_FRAME_ACK_BYTE_t ACK;									/*!< Acknowledge byte */
} TLD7002_FRAME_TERMINATION_t;

/******************************************************************************/
/*	UART over CAN frame type definitions 									  */
/******************************************************************************/
/* Implements DD-SWA-334 */

/* DC_SYNC - Broadcast duty cycle */
#define TLD7002_POS_BRDC_DC_SYNC_SYNC						   0U
#define TLD7002_POS_BRDC_DC_SYNC_CRC_REQ_S_ADD				   1U
#define TLD7002_POS_BRDC_DC_SYNC_DLC_FUN					   2U

#define TLD7002_LEN_BRDC_DC_SYNC_WRITE		 				   3U

/** TLD7002_BRDC_DC_SYNC_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
    } w_brdc_dc_sync;
    uint8 write_array[TLD7002_LEN_BRDC_DC_SYNC_WRITE];					/*!< write frame */
} TLD7002_BRDC_DC_SYNC_FRAME_t;

/* DC_UPDATE_8BIT - Update duty cycle and output status */
#define TLD7002_POS_DC_UPDATE_8BIT_SYNC						   0U
#define TLD7002_POS_DC_UPDATE_8BIT_CRC_REQ_S_ADD			   1U
#define TLD7002_POS_DC_UPDATE_8BIT_MRC_DLC_FUN				   2U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT0					   3U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT1					   4U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT2					   5U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT3					   6U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT4					   7U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT5					   8U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT6					   9U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT7					  10U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT8					  11U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT9					  12U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT10					  13U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT11					  14U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT12					  15U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT13					  16U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT14					  17U
#define TLD7002_POS_DC_UPDATE_8BIT_DCOUT15					  18U
#define TLD7002_POS_DC_UPDATE_8BIT_SAFETY_BYTE				  19U
#define TLD7002_POS_DC_UPDATE_8BIT_OST						   0U
#define TLD7002_POS_DC_UPDATE_8BIT_ACK						   1U

#define TLD7002_LEN_DC_UPDATE_8BIT_WRITE					  20U
#define TLD7002_LEN_DC_UPDATE_8BIT_DLC0_WRITE				   3U
#define TLD7002_LEN_DC_UPDATE_8BIT_READ						   2U
#define TLD7002_LEN_DC_UPDATE_8BIT_DLC0_READ				   2U

/** TLD7002_DC_UPDATE_8BIT_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;                            /*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 DutyCycleOUT0;											/*!< 8 Bit duty cycle representation for OUT0 */
        uint8 DutyCycleOUT1;											/*!< 8 Bit duty cycle representation for OUT1 */
        uint8 DutyCycleOUT2;											/*!< 8 Bit duty cycle representation for OUT2 */
        uint8 DutyCycleOUT3;											/*!< 8 Bit duty cycle representation for OUT3 */
        uint8 DutyCycleOUT4;											/*!< 8 Bit duty cycle representation for OUT4 */
        uint8 DutyCycleOUT5;											/*!< 8 Bit duty cycle representation for OUT5 */
        uint8 DutyCycleOUT6;											/*!< 8 Bit duty cycle representation for OUT6 */
        uint8 DutyCycleOUT7;											/*!< 8 Bit duty cycle representation for OUT7 */
        uint8 DutyCycleOUT8;											/*!< 8 Bit duty cycle representation for OUT8 */
        uint8 DutyCycleOUT9;											/*!< 8 Bit duty cycle representation for OUT9 */
        uint8 DutyCycleOUT10;											/*!< 8 Bit duty cycle representation for OUT10 */
        uint8 DutyCycleOUT11;											/*!< 8 Bit duty cycle representation for OUT11 */
        uint8 DutyCycleOUT12;											/*!< 8 Bit duty cycle representation for OUT12 */
        uint8 DutyCycleOUT13;											/*!< 8 Bit duty cycle representation for OUT13 */
        uint8 DutyCycleOUT14;											/*!< 8 Bit duty cycle representation for OUT14 */
        uint8 DutyCycleOUT15;											/*!< 8 Bit duty cycle representation for OUT15 */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_pwm_dc_update;
    uint8 write_array[TLD7002_LEN_DC_UPDATE_8BIT_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_pwm_dc_update;
    uint8 read_array[TLD7002_LEN_DC_UPDATE_8BIT_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_DC_UPDATE_8BIT_FRAME_t;

/* DC_UPDATE_14BIT - Update duty cycle and output status */
#define TLD7002_POS_DC_UPDATE_14BIT_SYNC					   0U
#define TLD7002_POS_DC_UPDATE_14BIT_CRC_REQ_S_ADD			   1U
#define TLD7002_POS_DC_UPDATE_14BIT_MRC_DLC_FUN				   2U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT0_HB				   3U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT0_LB				   4U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT1_HB				   5U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT1_LB				   6U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT2_HB				   7U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT2_LB				   8U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT3_HB				   9U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT3_LB				  10U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT4_HB				  11U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT4_LB				  12U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT5_HB				  13U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT5_LB				  14U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT6_HB				  15U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT6_LB				  16U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT7_HB				  17U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT7_LB				  18U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT8_HB				  19U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT8_LB				  20U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT9_HB				  21U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT9_LB				  22U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT10_HB				  23U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT10_LB				  24U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT11_HB				  25U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT11_LB				  26U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT12_HB				  27U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT12_LB				  28U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT13_HB				  29U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT13_LB				  30U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT14_HB				  31U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT14_LB				  32U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT15_HB				  33U
#define TLD7002_POS_DC_UPDATE_14BIT_DCOUT15_LB				  34U
#define TLD7002_POS_DC_UPDATE_14BIT_SAFETY_BYTE				  35U
#define TLD7002_POS_DC_UPDATE_14BIT_OST						   0U
#define TLD7002_POS_DC_UPDATE_14BIT_ACK						   1U

#define TLD7002_LEN_DC_UPDATE_14BIT_WRITE					  36U
#define TLD7002_LEN_DC_UPDATE_14BIT_READ					   2U

/** TLD7002_DC_UPDATE_14BIT_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;                            /*!< frame header containing SYNC, CRC3, slave
                                                                         * address, MRC, DLC and FUN */
        uint16 DutyCycleOUT0;                           				/*!< 14 Bit duty cycle representation for OUT0
                                                                         * */
        uint16 DutyCycleOUT1;                           				/*!< 14 Bit duty cycle representation for OUT1
                                                                         * */
        uint16 DutyCycleOUT2;                           				/*!< 14 Bit duty cycle representation for OUT2
                                                                         * */
        uint16 DutyCycleOUT3;                           				/*!< 14 Bit duty cycle representation for OUT3
                                                                         * */
        uint16 DutyCycleOUT4;                           				/*!< 14 Bit duty cycle representation for OUT4
                                                                         * */
        uint16 DutyCycleOUT5;                           				/*!< 14 Bit duty cycle representation for OUT5
                                                                         * */
        uint16 DutyCycleOUT6;             					            /*!< 14 Bit duty cycle representation for OUT6
                                                                         * */
        uint16 DutyCycleOUT7;                           				/*!< 14 Bit duty cycle representation for OUT7
                                                                         * */
        uint16 DutyCycleOUT8;                           				/*!< 14 Bit duty cycle representation for OUT8
                                                                         * */
        uint16 DutyCycleOUT9;                           				/*!< 14 Bit duty cycle representation for OUT9
                                                                         * */
        uint16 DutyCycleOUT10;                          				/*!< 14 Bit duty cycle representation for OUT10
                                                                         * */
        uint16 DutyCycleOUT11;                          				/*!< 14 Bit duty cycle representation for OUT11
                                                                         * */
        uint16 DutyCycleOUT12;                          				/*!< 14 Bit duty cycle representation for OUT12
                                                                         * */
        uint16 DutyCycleOUT13;                          				/*!< 14 Bit duty cycle representation for OUT13
                                                                         * */
        uint16 DutyCycleOUT14;                          				/*!< 14 Bit duty cycle representation for OUT14
                                                                         * */
        uint16 DutyCycleOUT15;                          				/*!< 14 Bit duty cycle representation for OUT15
                                                                         * */
        uint8 SAFETY_BYTE;                            					/*!< CRC */
    } w_pwm_dc_update;
    uint8 write_array[TLD7002_LEN_DC_UPDATE_14BIT_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_pwm_dc_update;
    uint8 read_array[TLD7002_LEN_DC_UPDATE_14BIT_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_DC_UPDATE_14BIT_FRAME_t;

/* PM_CHANGE - Power mode change */
#define TLD7002_POS_PM_CHANGE_SYNC							   0U
#define TLD7002_POS_PM_CHANGE_CRC_REQ_S_ADD					   1U
#define TLD7002_POS_PM_CHANGE_MRC_DLC_FUN					   2U
#define TLD7002_POS_PM_CHANGE_POWER_MODE					   3U
#define TLD7002_POS_PM_CHANGE_RES							   4U
#define TLD7002_POS_PM_CHANGE_SAFETY_BYTE					   5U
#define TLD7002_POS_PM_CHANGE_OST							   0U
#define TLD7002_POS_PM_CHANGE_ACK							   1U

#define TLD7002_LEN_PM_CHANGE_WRITE							   6U
#define TLD7002_LEN_PM_CHANGE_READ							   2U

/** TLD7002_PM_CHANGE_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        TLD7002_FRAME_POWER_MODE_CHANGE_t PM_CHANGE;					/*!< Power Mode */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_power_mode_change;
    uint8 write_array[TLD7002_LEN_PM_CHANGE_WRITE];						/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_power_mode_change;
    uint8 read_array[TLD7002_LEN_PM_CHANGE_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_PM_CHANGE_FRAME_t;

/* READ_OST - Read all output status */
#define TLD7002_POS_READ_OST_SYNC							   0U
#define TLD7002_POS_READ_OST_CRC_REQ_S_ADD					   1U
#define TLD7002_POS_READ_OST_MRC_DLC_FUN					   2U
#define TLD7002_POS_READ_OST_OSB_OUT0						   0U
#define TLD7002_POS_READ_OST_OSB_OUT1						   1U
#define TLD7002_POS_READ_OST_OSB_OUT2						   2U
#define TLD7002_POS_READ_OST_OSB_OUT3						   3U
#define TLD7002_POS_READ_OST_OSB_OUT4						   4U
#define TLD7002_POS_READ_OST_OSB_OUT5						   5U
#define TLD7002_POS_READ_OST_OSB_OUT6						   6U
#define TLD7002_POS_READ_OST_OSB_OUT7						   7U
#define TLD7002_POS_READ_OST_OSB_OUT8						   8U
#define TLD7002_POS_READ_OST_OSB_OUT9						   9U
#define TLD7002_POS_READ_OST_OSB_OUT10						  10U
#define TLD7002_POS_READ_OST_OSB_OUT11						  11U
#define TLD7002_POS_READ_OST_OSB_OUT12						  12U
#define TLD7002_POS_READ_OST_OSB_OUT13						  13U
#define TLD7002_POS_READ_OST_OSB_OUT14						  14U
#define TLD7002_POS_READ_OST_OSB_OUT15						  15U
#define TLD7002_POS_READ_OST_SAFETY_BYTE					  16U
#define TLD7002_POS_READ_OST_OST							  17U
#define TLD7002_POS_READ_OST_ACK							  18U

#define TLD7002_LEN_READ_OST_WRITE							   3U
#define TLD7002_LEN_READ_OST_READ							  19U

/** TLD7002_READ_OST_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
    } w_read_output_status;
    uint8 write_array[TLD7002_LEN_READ_OST_WRITE];						/*!< write frame */
    struct
    {
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT0;				/*!< Output Status Byte for OUT0 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT1;				/*!< Output Status Byte for OUT1 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT2;				/*!< Output Status Byte for OUT2 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT3;				/*!< Output Status Byte for OUT3 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT4;				/*!< Output Status Byte for OUT4 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT5;				/*!< Output Status Byte for OUT5 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT6;				/*!< Output Status Byte for OUT6 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT7;				/*!< Output Status Byte for OUT7 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT8;				/*!< Output Status Byte for OUT8 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT9;				/*!< Output Status Byte for OUT9 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT10;				/*!< Output Status Byte for OUT10 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT11;				/*!< Output Status Byte for OUT11 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT12;				/*!< Output Status Byte for OUT12 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT13;				/*!< Output Status Byte for OUT13 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT14;				/*!< Output Status Byte for OUT14 */
        TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OSB_OUT15;				/*!< Output Status Byte for OUT15 */
        uint8 SAFETY_BYTE;												/*!< CRC */
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_read_output_status;
    uint8 read_array[TLD7002_LEN_READ_OST_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_READ_OST_FRAME_t;

/* HWCR - Hardware control */
#define TLD7002_POS_HWCR_SYNC								   0U
#define TLD7002_POS_HWCR_CRC_REQ_S_ADD						   1U
#define TLD7002_POS_HWCR_MRC_DLC_FUN						   2U
#define TLD7002_POS_HWCR_RESET_OL_HB						   3U
#define TLD7002_POS_HWCR_RESET_OL_LB						   4U
#define TLD7002_POS_HWCR_RESET_OP_HB						   5U
#define TLD7002_POS_HWCR_RESET_OP_LB						   6U
#define TLD7002_POS_HWCR_RESET_SLS_HB						   7U
#define TLD7002_POS_HWCR_RESET_SLS_LB						   8U
#define TLD7002_POS_HWCR_RESERVED							   9U
#define TLD7002_POS_HWCR_RESET_STATUS						  10U
#define TLD7002_POS_HWCR_SAFETY_BYTE						  11U
#define TLD7002_POS_HWCR_OST								   0U
#define TLD7002_POS_HWCR_ACK								   1U

#define TLD7002_LEN_HWCR_WRITE								  12U
#define TLD7002_LEN_HWCR_READ								   2U


/** TLD7002_HWCR_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        TLD7002_FRAME_HWCR_RESET_OUT_t RESET_OVERLOAD;					/*!< Reset Overload for outputs */
        TLD7002_FRAME_HWCR_RESET_OUT_t RESET_OPENLOAD;					/*!< Reset Openload for outputs */
        TLD7002_FRAME_HWCR_RESET_OUT_t RESET_SLS;						/*!< Reset SLS for outputs */
        TLD7002_FRAME_HWCR_RESET_STATUS_t RESET_STATUS;					/*!< Reset status byte */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_hardware_control;
    uint8 write_array[TLD7002_LEN_HWCR_WRITE];							/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_hardware_control;
    uint8 read_array[TLD7002_LEN_HWCR_READ];							/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_HWCR_FRAME_t;

/* WRITE_REG - Write register content */
#define TLD7002_POS_WRITE_REG_SYNC							   0U
#define TLD7002_POS_WRITE_REG_CRC_REQ_S_ADD					   1U
#define TLD7002_POS_WRITE_REG_MRC_DLC_FUN					   2U
#define TLD7002_POS_WRITE_REG_START_ADD						   3U
#define TLD7002_POS_WRITE_REG_DATA0_HB						   4U
#define TLD7002_POS_WRITE_REG_DATA0_LB						   5U
#define TLD7002_POS_WRITE_REG_DATA1_HB						   6U
#define TLD7002_POS_WRITE_REG_DATA1_LB						   7U
#define TLD7002_POS_WRITE_REG_DATA2_HB						   8U
#define TLD7002_POS_WRITE_REG_DATA2_LB						   9U
#define TLD7002_POS_WRITE_REG_DATA3_HB						  10U
#define TLD7002_POS_WRITE_REG_DATA3_LB						  11U
#define TLD7002_POS_WRITE_REG_DATA4_HB						  12U
#define TLD7002_POS_WRITE_REG_DATA4_LB						  13U
#define TLD7002_POS_WRITE_REG_DATA5_HB						  14U
#define TLD7002_POS_WRITE_REG_DATA5_LB						  15U
#define TLD7002_POS_WRITE_REG_DATA6_HB						  16U
#define TLD7002_POS_WRITE_REG_DATA6_LB						  17U
#define TLD7002_POS_WRITE_REG_DATA7_HB						  18U
#define TLD7002_POS_WRITE_REG_DATA7_LB						  19U
#define TLD7002_POS_WRITE_REG_DATA8_HB						  20U
#define TLD7002_POS_WRITE_REG_DATA8_LB						  21U
#define TLD7002_POS_WRITE_REG_DATA9_HB						  22U
#define TLD7002_POS_WRITE_REG_DATA9_LB						  23U
#define TLD7002_POS_WRITE_REG_DATA10_HB						  24U
#define TLD7002_POS_WRITE_REG_DATA10_LB						  25U
#define TLD7002_POS_WRITE_REG_DATA11_HB						  26U
#define TLD7002_POS_WRITE_REG_DATA11_LB						  27U
#define TLD7002_POS_WRITE_REG_DATA12_HB						  28U
#define TLD7002_POS_WRITE_REG_DATA12_LB						  29U
#define TLD7002_POS_WRITE_REG_DATA13_HB						  30U
#define TLD7002_POS_WRITE_REG_DATA13_LB						  31U
#define TLD7002_POS_WRITE_REG_DATA14_HB						  32U
#define TLD7002_POS_WRITE_REG_DATA14_LB						  33U
#define TLD7002_POS_WRITE_REG_DATA15_HB						  34U
#define TLD7002_POS_WRITE_REG_DATA15_LB						  35U
#define TLD7002_POS_WRITE_REG_DATA16_HB						  36U
#define TLD7002_POS_WRITE_REG_DATA16_LB						  37U
#define TLD7002_POS_WRITE_REG_DATA17_HB						  38U
#define TLD7002_POS_WRITE_REG_DATA17_LB						  39U
#define TLD7002_POS_WRITE_REG_DATA18_HB						  40U
#define TLD7002_POS_WRITE_REG_DATA18_LB						  41U
#define TLD7002_POS_WRITE_REG_DATA19_HB						  42U
#define TLD7002_POS_WRITE_REG_DATA19_LB						  43U
#define TLD7002_POS_WRITE_REG_DATA20_HB						  44U
#define TLD7002_POS_WRITE_REG_DATA20_LB						  45U
#define TLD7002_POS_WRITE_REG_DATA21_HB						  46U
#define TLD7002_POS_WRITE_REG_DATA21_LB						  47U
#define TLD7002_POS_WRITE_REG_DATA22_HB						  48U
#define TLD7002_POS_WRITE_REG_DATA22_LB						  49U
#define TLD7002_POS_WRITE_REG_DATA23_HB						  50U
#define TLD7002_POS_WRITE_REG_DATA23_LB						  51U
#define TLD7002_POS_WRITE_REG_DATA24_HB						  52U
#define TLD7002_POS_WRITE_REG_DATA24_LB						  53U
#define TLD7002_POS_WRITE_REG_DATA25_HB						  54U
#define TLD7002_POS_WRITE_REG_DATA25_LB						  55U
#define TLD7002_POS_WRITE_REG_DATA26_HB						  56U
#define TLD7002_POS_WRITE_REG_DATA26_LB						  57U
#define TLD7002_POS_WRITE_REG_DATA27_HB						  58U
#define TLD7002_POS_WRITE_REG_DATA27_LB						  59U
#define TLD7002_POS_WRITE_REG_DATA28_HB						  60U
#define TLD7002_POS_WRITE_REG_DATA28_LB						  61U
#define TLD7002_POS_WRITE_REG_DATA29_HB						  62U
#define TLD7002_POS_WRITE_REG_DATA29_LB						  63U
#define TLD7002_POS_WRITE_REG_DATA30_HB						  64U
#define TLD7002_POS_WRITE_REG_DATA30_LB						  65U
#define TLD7002_POS_WRITE_REG_DATA31_HB						  66U
#define TLD7002_POS_WRITE_REG_DATA31_LB						  67U
#define TLD7002_POS_WRITE_REG_DLC1_SAFETY_BYTE				   6U
#define TLD7002_POS_WRITE_REG_DLC2_SAFETY_BYTE				   8U
#define TLD7002_POS_WRITE_REG_DLC3_SAFETY_BYTE				  12U
#define TLD7002_POS_WRITE_REG_DLC4_SAFETY_BYTE				  20U
#define TLD7002_POS_WRITE_REG_DLC5_SAFETY_BYTE				  28U
#define TLD7002_POS_WRITE_REG_DLC6_SAFETY_BYTE				  36U
#define TLD7002_POS_WRITE_REG_DLC7_SAFETY_BYTE				  68U
#define TLD7002_POS_WRITE_REG_OST							   0U
#define TLD7002_POS_WRITE_REG_ACK							   1U

#define TLD7002_LEN_WRITE_REG_OVHD							   5U		/*!< SYNC/CRC_REQ_S_ADD/MRC_DLC_FUN/StartADDR/SAFETY_BYTE overhead at WRITE_REG frame */
#define TLD7002_LEN_WRITE_REG_DLC1_WRITE					   7U
#define TLD7002_LEN_WRITE_REG_DLC2_WRITE					   9U
#define TLD7002_LEN_WRITE_REG_DLC3_WRITE					  13U
#define TLD7002_LEN_WRITE_REG_DLC4_WRITE					  21U
#define TLD7002_LEN_WRITE_REG_DLC5_WRITE					  29U
#define TLD7002_LEN_WRITE_REG_DLC6_WRITE					  37U
#define TLD7002_LEN_WRITE_REG_DLC7_WRITE					  69U
#define TLD7002_LEN_WRITE_REG_READ							   2U

/** TLD7002_WRITE_REG_DLC1_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
        uint16 Data[(TLD7002_LEN_WRITE_REG_DLC1_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_write_reg;
    uint8 write_array[TLD7002_LEN_WRITE_REG_DLC1_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_write_reg;
    uint8 read_array[TLD7002_LEN_WRITE_REG_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_WRITE_REG_DLC1_FRAME_t;

/** TLD7002_WRITE_REG_DLC2_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
        uint16 Data[(TLD7002_LEN_WRITE_REG_DLC2_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_write_reg;
    uint8 write_array[TLD7002_LEN_WRITE_REG_DLC2_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_write_reg;
    uint8 read_array[TLD7002_LEN_WRITE_REG_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_WRITE_REG_DLC2_FRAME_t;


/** TLD7002_WRITE_REG_DLC3_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
        uint16 Data[(TLD7002_LEN_WRITE_REG_DLC3_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_write_reg;
    uint8 write_array[TLD7002_LEN_WRITE_REG_DLC3_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_write_reg;
    uint8 read_array[TLD7002_LEN_WRITE_REG_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_WRITE_REG_DLC3_FRAME_t;


/** TLD7002_WRITE_REG_DLC4_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
        uint16 Data[(TLD7002_LEN_WRITE_REG_DLC4_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_write_reg;
    uint8 write_array[TLD7002_LEN_WRITE_REG_DLC4_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_write_reg;
    uint8 read_array[TLD7002_LEN_WRITE_REG_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_WRITE_REG_DLC4_FRAME_t;


/** TLD7002_WRITE_REG_DLC5_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
        uint16 Data[(TLD7002_LEN_WRITE_REG_DLC5_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_write_reg;
    uint8 write_array[TLD7002_LEN_WRITE_REG_DLC5_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_write_reg;
    uint8 read_array[TLD7002_LEN_WRITE_REG_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_WRITE_REG_DLC5_FRAME_t;


/** TLD7002_WRITE_REG_DLC6_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
        uint16 Data[(TLD7002_LEN_WRITE_REG_DLC6_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_write_reg;
    uint8 write_array[TLD7002_LEN_WRITE_REG_DLC6_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_write_reg;
    uint8 read_array[TLD7002_LEN_WRITE_REG_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_WRITE_REG_DLC6_FRAME_t;


/** TLD7002_WRITE_REG_DLC7_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
        uint16 Data[(TLD7002_LEN_WRITE_REG_DLC7_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
    } w_write_reg;
    uint8 write_array[TLD7002_LEN_WRITE_REG_DLC7_WRITE];				/*!< write frame */
    struct
    {
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_write_reg;
    uint8 read_array[TLD7002_LEN_WRITE_REG_READ];						/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_WRITE_REG_DLC7_FRAME_t;

/* READ_REG - Read register content */
#define TLD7002_POS_READ_REG_SYNC							   0U
#define TLD7002_POS_READ_REG_CRC_REQ_S_ADD					   1U
#define TLD7002_POS_READ_REG_MRC_DLC_FUN					   2U
#define TLD7002_POS_READ_REG_START_ADD						   3U
#define TLD7002_POS_READ_REG_DATA0_HB						   0U
#define TLD7002_POS_READ_REG_DATA0_LB						   1U
#define TLD7002_POS_READ_REG_DATA1_HB						   2U
#define TLD7002_POS_READ_REG_DATA1_LB						   3U
#define TLD7002_POS_READ_REG_DATA2_HB						   4U
#define TLD7002_POS_READ_REG_DATA2_LB						   5U
#define TLD7002_POS_READ_REG_DATA3_HB						   6U
#define TLD7002_POS_READ_REG_DATA3_LB						   7U
#define TLD7002_POS_READ_REG_DATA4_HB						   8U
#define TLD7002_POS_READ_REG_DATA4_LB						   9U
#define TLD7002_POS_READ_REG_DATA5_HB						  10U
#define TLD7002_POS_READ_REG_DATA5_LB						  11U
#define TLD7002_POS_READ_REG_DATA6_HB						  12U
#define TLD7002_POS_READ_REG_DATA6_LB						  13U
#define TLD7002_POS_READ_REG_DATA7_HB						  14U
#define TLD7002_POS_READ_REG_DATA7_LB						  15U
#define TLD7002_POS_READ_REG_DATA8_HB						  16U
#define TLD7002_POS_READ_REG_DATA8_LB						  17U
#define TLD7002_POS_READ_REG_DATA9_HB						  18U
#define TLD7002_POS_READ_REG_DATA9_LB						  19U
#define TLD7002_POS_READ_REG_DATA10_HB						  20U
#define TLD7002_POS_READ_REG_DATA10_LB						  21U
#define TLD7002_POS_READ_REG_DATA11_HB						  22U
#define TLD7002_POS_READ_REG_DATA11_LB						  23U
#define TLD7002_POS_READ_REG_DATA12_HB						  24U
#define TLD7002_POS_READ_REG_DATA12_LB						  25U
#define TLD7002_POS_READ_REG_DATA13_HB						  26U
#define TLD7002_POS_READ_REG_DATA13_LB						  27U
#define TLD7002_POS_READ_REG_DATA14_HB						  28U
#define TLD7002_POS_READ_REG_DATA14_LB						  29U
#define TLD7002_POS_READ_REG_DATA15_HB						  30U
#define TLD7002_POS_READ_REG_DATA15_LB						  31U
#define TLD7002_POS_READ_REG_DATA16_HB						  32U
#define TLD7002_POS_READ_REG_DATA16_LB						  33U
#define TLD7002_POS_READ_REG_DATA17_HB						  34U
#define TLD7002_POS_READ_REG_DATA17_LB						  35U
#define TLD7002_POS_READ_REG_DATA18_HB						  36U
#define TLD7002_POS_READ_REG_DATA18_LB						  37U
#define TLD7002_POS_READ_REG_DATA19_HB						  38U
#define TLD7002_POS_READ_REG_DATA19_LB						  39U
#define TLD7002_POS_READ_REG_DATA20_HB						  40U
#define TLD7002_POS_READ_REG_DATA20_LB						  41U
#define TLD7002_POS_READ_REG_DATA21_HB						  42U
#define TLD7002_POS_READ_REG_DATA21_LB						  43U
#define TLD7002_POS_READ_REG_DATA22_HB						  44U
#define TLD7002_POS_READ_REG_DATA22_LB						  45U
#define TLD7002_POS_READ_REG_DATA23_HB						  46U
#define TLD7002_POS_READ_REG_DATA23_LB						  47U
#define TLD7002_POS_READ_REG_DATA24_HB						  48U
#define TLD7002_POS_READ_REG_DATA24_LB						  49U
#define TLD7002_POS_READ_REG_DATA25_HB						  50U
#define TLD7002_POS_READ_REG_DATA25_LB						  51U
#define TLD7002_POS_READ_REG_DATA26_HB						  52U
#define TLD7002_POS_READ_REG_DATA26_LB						  53U
#define TLD7002_POS_READ_REG_DATA27_HB						  54U
#define TLD7002_POS_READ_REG_DATA27_LB						  55U
#define TLD7002_POS_READ_REG_DATA28_HB						  56U
#define TLD7002_POS_READ_REG_DATA28_LB						  57U
#define TLD7002_POS_READ_REG_DATA29_HB						  58U
#define TLD7002_POS_READ_REG_DATA29_LB						  59U
#define TLD7002_POS_READ_REG_DATA30_HB						  60U
#define TLD7002_POS_READ_REG_DATA30_LB						  61U
#define TLD7002_POS_READ_REG_DATA31_HB						  62U
#define TLD7002_POS_READ_REG_DATA31_LB						  63U
#define TLD7002_POS_READ_REG_DLC1_SAFETY_BYTE				   2U
#define TLD7002_POS_READ_REG_DLC1_OST						   3U
#define TLD7002_POS_READ_REG_DLC1_ACK						   4U
#define TLD7002_POS_READ_REG_DLC2_SAFETY_BYTE				   4U
#define TLD7002_POS_READ_REG_DLC2_OST						   5U
#define TLD7002_POS_READ_REG_DLC2_ACK						   6U
#define TLD7002_POS_READ_REG_DLC3_SAFETY_BYTE				   8U
#define TLD7002_POS_READ_REG_DLC3_OST						   9U
#define TLD7002_POS_READ_REG_DLC3_ACK						  10U
#define TLD7002_POS_READ_REG_DLC4_SAFETY_BYTE				  16U
#define TLD7002_POS_READ_REG_DLC4_OST						  17U
#define TLD7002_POS_READ_REG_DLC4_ACK						  18U
#define TLD7002_POS_READ_REG_DLC5_SAFETY_BYTE				  24U
#define TLD7002_POS_READ_REG_DLC5_OST						  25U
#define TLD7002_POS_READ_REG_DLC5_ACK						  26U
#define TLD7002_POS_READ_REG_DLC6_SAFETY_BYTE				  32U
#define TLD7002_POS_READ_REG_DLC6_OST						  33U
#define TLD7002_POS_READ_REG_DLC6_ACK						  34U
#define TLD7002_POS_READ_REG_DLC7_SAFETY_BYTE				  64U
#define TLD7002_POS_READ_REG_DLC7_OST						  65U
#define TLD7002_POS_READ_REG_DLC7_ACK						  66U

#define TLD7002_LEN_READ_REG_OVHD							   3U		/*!< SAFETY_BYTE/OST/ACK overhead at READ_REG frame */
#define TLD7002_LEN_READ_REG_WRITE							   4U
#define TLD7002_LEN_READ_REG_DLC1_READ						   5U
#define TLD7002_LEN_READ_REG_DLC2_READ						   7U
#define TLD7002_LEN_READ_REG_DLC3_READ						  11U
#define TLD7002_LEN_READ_REG_DLC4_READ						  19U
#define TLD7002_LEN_READ_REG_DLC5_READ						  27U
#define TLD7002_LEN_READ_REG_DLC6_READ						  35U
#define TLD7002_LEN_READ_REG_DLC7_READ						  67U

/** TLD7002_READ_REG_DLC1_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
    } w_read_reg;
    uint8 write_array[TLD7002_LEN_READ_REG_WRITE];						/*!< write frame */
    struct
    {
        uint16 Data[(TLD7002_LEN_READ_REG_DLC1_READ - TLD7002_LEN_READ_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_read_reg;
    uint8 read_array[TLD7002_LEN_READ_REG_DLC1_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_READ_REG_DLC1_FRAME_t;


/** TLD7002_READ_REG_DLC2_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
    } w_read_reg;
    uint8 write_array[TLD7002_LEN_READ_REG_WRITE];						/*!< write frame */
    struct
    {
        uint16 Data[(TLD7002_LEN_READ_REG_DLC2_READ - TLD7002_LEN_READ_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_read_reg;
    uint8 read_array[TLD7002_LEN_READ_REG_DLC2_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_READ_REG_DLC2_FRAME_t;

/** TLD7002_READ_REG_DLC3_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
    } w_read_reg;
    uint8 write_array[TLD7002_LEN_READ_REG_WRITE];						/*!< write frame */
    struct
    {
        uint16 Data[(TLD7002_LEN_READ_REG_DLC3_READ - TLD7002_LEN_READ_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_read_reg;
    uint8 read_array[TLD7002_LEN_READ_REG_DLC3_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_READ_REG_DLC3_FRAME_t;


/** TLD7002_READ_REG_DLC4_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
    } w_read_reg;
    uint8 write_array[TLD7002_LEN_READ_REG_WRITE];						/*!< write frame */
    struct
    {
        uint16 Data[(TLD7002_LEN_READ_REG_DLC4_READ - TLD7002_LEN_READ_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_read_reg;
    uint8 read_array[TLD7002_LEN_READ_REG_DLC4_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_READ_REG_DLC4_FRAME_t;

/** TLD7002_READ_REG_DLC5_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
    } w_read_reg;
    uint8 write_array[TLD7002_LEN_READ_REG_WRITE];						/*!< write frame */
    struct
    {
        uint16 Data[(TLD7002_LEN_READ_REG_DLC5_READ - TLD7002_LEN_READ_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_read_reg;
    uint8 read_array[TLD7002_LEN_READ_REG_DLC5_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_READ_REG_DLC5_FRAME_t;


/** TLD7002_READ_REG_DLC6_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
    } w_read_reg;
    uint8 write_array[TLD7002_LEN_READ_REG_WRITE];						/*!< write frame */
    struct
    {
        uint16 Data[(TLD7002_LEN_READ_REG_DLC6_READ - TLD7002_LEN_READ_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_read_reg;
    uint8 read_array[TLD7002_LEN_READ_REG_DLC6_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_READ_REG_DLC6_FRAME_t;


/** TLD7002_READ_REG_DLC7_FRAME_t
 */
typedef struct
{
    struct
    {
        TLD7002_FRAME_HEADER_t frame_header;							/*!< frame header containing SYNC, CRC3, slave address, MRC, DLC and FUN */
        uint8 StartADDR;												/*!< Start Address byte */
    } w_read_reg;
    uint8 write_array[TLD7002_LEN_READ_REG_WRITE];						/*!< write frame */
    struct
    {
        uint16 Data[(TLD7002_LEN_READ_REG_DLC7_READ - TLD7002_LEN_READ_REG_OVHD) / 2];	/*!< Data */
        uint8 SAFETY_BYTE;												/*!< CRC */
        TLD7002_FRAME_TERMINATION_t frame_termination;					/*!< Output status byte and Acknowledge byte */
    } r_read_reg;
    uint8 read_array[TLD7002_LEN_READ_REG_DLC7_READ];					/*!< read frame */
    boolean timeout;													/*!< receive answer timeout */
    uint8 slave_rc;														/*!< slave rolling counter */
} TLD7002_READ_REG_DLC7_FRAME_t;

/* SYNC_BREAK - Sync break reset
 * Implementation of SYNC_BREAK has to be done externally
 */

#endif /* TLD7002_H_ */
/**@}*/