/**
 *  @file TLD7002_Definitions.h
 *  @author Infineon
 *  @date 17.06.2022
 *	@brief TLD7002 specific Device Driver implementation from Infineon Technologies AG.
 *	@note  This file includes the implementation for the TLD7002 hardware access layer.
 *		   Hardware version TLD7002-16ES B11
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

#ifndef TLD7002_DEFINITIONS_H_
#define TLD7002_DEFINITIONS_H_
#include "zf_common_typedef.h"
/******************************************************************************/
/*	Definition to get register value with position and mask					  */
/******************************************************************************/
/* Implements DD-SWA-335 */
#define TLD7002_GET_REG_VAL(value, POS, MSK) ((value & MSK) >> POS)									/**< mask bytes and shift to right */

/******************************************************************************/
/*	Definitions for accessing the TLD7002 registers							  */
/******************************************************************************/
/* Implements DD-SWA-336 */

/* LED_DRIVER HSLI configurable register addresses */
#define TLD7002_LD_PWM_DC_CFG0											0x000U						/**< PWM duty-cycle configuration register OUT 0 */
#define TLD7002_LD_PWM_DC_CFG1											0x001U						/**< PWM duty-cycle configuration register OUT 1 */
#define TLD7002_LD_PWM_DC_CFG2											0x002U						/**< PWM duty-cycle configuration register OUT 2 */
#define TLD7002_LD_PWM_DC_CFG3											0x003U						/**< PWM duty-cycle configuration register OUT 3 */
#define TLD7002_LD_PWM_DC_CFG4											0x004U						/**< PWM duty-cycle configuration register OUT 4 */
#define TLD7002_LD_PWM_DC_CFG5											0x005U						/**< PWM duty-cycle configuration register OUT 5 */
#define TLD7002_LD_PWM_DC_CFG6											0x006U						/**< PWM duty-cycle configuration register OUT 6 */
#define TLD7002_LD_PWM_DC_CFG7											0x007U						/**< PWM duty-cycle configuration register OUT 7 */
#define TLD7002_LD_PWM_DC_CFG8											0x008U						/**< PWM duty-cycle configuration register OUT 8 */
#define TLD7002_LD_PWM_DC_CFG9											0x009U						/**< PWM duty-cycle configuration register OUT 9 */
#define TLD7002_LD_PWM_DC_CFG10											0x00AU						/**< PWM duty-cycle configuration register OUT 10 */
#define TLD7002_LD_PWM_DC_CFG11											0x00BU						/**< PWM duty-cycle configuration register OUT 11 */
#define TLD7002_LD_PWM_DC_CFG12											0x00CU						/**< PWM duty-cycle configuration register OUT 12 */
#define TLD7002_LD_PWM_DC_CFG13											0x00DU						/**< PWM duty-cycle configuration register OUT 13 */
#define TLD7002_LD_PWM_DC_CFG14											0x00EU						/**< PWM duty-cycle configuration register OUT 14 */
#define TLD7002_LD_PWM_DC_CFG15											0x00FU						/**< PWM duty-cycle configuration register OUT 15 */
#define TLD7002_LD_PWM_DC_CFG											TLD7002_LD_PWM_DC_CFG0		/**< PWM duty-cycle configuration register */

#define TLD7002_LD_PWM_DAC_CFG0											0x010U						/**< PWM channel current configuration register OUT 0 */
#define TLD7002_LD_PWM_DAC_CFG1											0x011U						/**< PWM channel current configuration register OUT 1 */
#define TLD7002_LD_PWM_DAC_CFG2											0x012U						/**< PWM channel current configuration register OUT 2 */
#define TLD7002_LD_PWM_DAC_CFG3											0x013U						/**< PWM channel current configuration register OUT 3 */
#define TLD7002_LD_PWM_DAC_CFG4											0x014U						/**< PWM channel current configuration register OUT 4 */
#define TLD7002_LD_PWM_DAC_CFG5											0x015U						/**< PWM channel current configuration register OUT 5 */
#define TLD7002_LD_PWM_DAC_CFG6											0x016U						/**< PWM channel current configuration register OUT 6 */
#define TLD7002_LD_PWM_DAC_CFG7											0x017U						/**< PWM channel current configuration register OUT 7 */
#define TLD7002_LD_PWM_DAC_CFG8											0x018U						/**< PWM channel current configuration register OUT 8 */
#define TLD7002_LD_PWM_DAC_CFG9											0x019U						/**< PWM channel current configuration register OUT 9 */
#define TLD7002_LD_PWM_DAC_CFG10										0x01AU						/**< PWM channel current configuration register OUT 10 */
#define TLD7002_LD_PWM_DAC_CFG11										0x01BU						/**< PWM channel current configuration register OUT 11 */
#define TLD7002_LD_PWM_DAC_CFG12										0x01CU						/**< PWM channel current configuration register OUT 12 */
#define TLD7002_LD_PWM_DAC_CFG13										0x01DU						/**< PWM channel current configuration register OUT 13 */
#define TLD7002_LD_PWM_DAC_CFG14										0x01EU						/**< PWM channel current configuration register OUT 14 */
#define TLD7002_LD_PWM_DAC_CFG15										0x01FU						/**< PWM channel current configuration register OUT 15 */
#define TLD7002_LD_PWM_DAC_CFG											TLD7002_LD_PWM_DAC_CFG0		/**< PWM channel current configuration register */

#define TLD7002_DIAG_SLS_CFG											0x020U						/**< SLS threshold configuration register */
#define TLD7002_TH_OVLD_CFG												0x021U						/**< OVLD threshold configuration register */

#define TLD7002_LD_ADC_VFWD0											0x022U						/**< VFWD conversion result register OUT 0 */
#define TLD7002_LD_ADC_VFWD1											0x023U						/**< VFWD conversion result register OUT 1 */
#define TLD7002_LD_ADC_VFWD2											0x024U						/**< VFWD conversion result register OUT 2 */
#define TLD7002_LD_ADC_VFWD3											0x025U						/**< VFWD conversion result register OUT 3 */
#define TLD7002_LD_ADC_VFWD4											0x026U						/**< VFWD conversion result register OUT 4 */
#define TLD7002_LD_ADC_VFWD5											0x027U						/**< VFWD conversion result register OUT 5 */
#define TLD7002_LD_ADC_VFWD6											0x028U						/**< VFWD conversion result register OUT 6 */
#define TLD7002_LD_ADC_VFWD7											0x029U						/**< VFWD conversion result register OUT 7 */
#define TLD7002_LD_ADC_VFWD8											0x02AU						/**< VFWD conversion result register OUT 8 */
#define TLD7002_LD_ADC_VFWD9											0x02BU						/**< VFWD conversion result register OUT 9 */
#define TLD7002_LD_ADC_VFWD10											0x02CU						/**< VFWD conversion result register OUT 10 */
#define TLD7002_LD_ADC_VFWD11											0x02DU						/**< VFWD conversion result register OUT 11 */
#define TLD7002_LD_ADC_VFWD12											0x02EU						/**< VFWD conversion result register OUT 12 */
#define TLD7002_LD_ADC_VFWD13											0x02FU						/**< VFWD conversion result register OUT 13 */
#define TLD7002_LD_ADC_VFWD14											0x030U						/**< VFWD conversion result register OUT 14 */
#define TLD7002_LD_ADC_VFWD15											0x031U						/**< VFWD conversion result register OUT 15 */
#define TLD7002_LD_ADC_VFWD												TLD7002_LD_ADC_VFWD0		/**< VFWD conversion result register */

#define TLD7002_LD_ADC_VLED												0x032U						/**< VLED conversion result register */
#define TLD7002_LD_ADC_VS												0x033U						/**< VS conversion result register */
#define TLD7002_LD_ADC_VOUT_MIN											0x034U						/**< VOUT min data channel register */
#define TLD7002_LD_ADC_VGPIO0											0x035U						/**< VGPIO0 conversion result register */
#define TLD7002_LD_ADC_VGPIO1											0x036U						/**< VGPIO1 conversion result register */
#define TLD7002_TH_OVLD_STATUS											0x037U						/**< Thermal overload status register */
#define TLD7002_DTS_STAT												0x038U						/**< Device temperature status register */
#define TLD7002_FW_RECON_STATUS											0x039U						/**< Reconfirmation status register */

/* PMU HSLI configurable register addresses */
#define TLD7002_PMU_DIAG												0x03AU						/**< Power management unit diagnostic register */

/* HSLI HSLI configurable register addresses */
#define TLD7002_HSLI_TIMING_CFG											0x03BU						/**< HSLI Timing configuration register */

/* OTP_CACHE HSLI configurable register addresses */
#define TLD7002_OTP_EMULATION											0x080U						/**< OTP emulation register */
#define TLD7002_OTP_WRITE												0x081U						/**< OTP write register */
#define TLD7002_OTP_STATUS												0x082U						/**< OTP status register */
#define TLD7002_PWM_DC_GPIN1_0											0x083U						/**< GPIN1 Duty cycle (Higher priority) configuration register OUT 0 / OUT 1 */
#define TLD7002_PWM_DC_GPIN1_1											0x084U						/**< GPIN1 Duty cycle (Higher priority) configuration register OUT 2 / OUT 3 */
#define TLD7002_PWM_DC_GPIN1_2											0x085U						/**< GPIN1 Duty cycle (Higher priority) configuration register OUT 4 / OUT 5 */
#define TLD7002_PWM_DC_GPIN1_3											0x086U						/**< GPIN1 Duty cycle (Higher priority) configuration register OUT 6 / OUT 7 */
#define TLD7002_PWM_DC_GPIN1_4											0x087U						/**< GPIN1 Duty cycle (Higher priority) configuration register OUT 8 / OUT 9 */
#define TLD7002_PWM_DC_GPIN1_5											0x088U						/**< GPIN1 Duty cycle (Higher priority) configuration register OUT 10 / OUT 11 */
#define TLD7002_PWM_DC_GPIN1_6											0x089U						/**< GPIN1 Duty cycle (Higher priority) configuration register OUT 12 / OUT 13 */
#define TLD7002_PWM_DC_GPIN1_7											0x08AU						/**< GPIN1 Duty cycle (Higher priority) configuration register OUT 14 / OUT 15 */
#define TLD7002_PWM_DC_GPIN0_0											0x08BU						/**< GPIN0 Duty cycle (Lower priority) configuration register OUT 0 / OUT 1 */
#define TLD7002_PWM_DC_GPIN0_1											0x08CU						/**< GPIN0 Duty cycle (Lower priority) configuration register OUT 2 / OUT 3 */
#define TLD7002_PWM_DC_GPIN0_2											0x08DU						/**< GPIN0 Duty cycle (Lower priority) configuration register OUT 4 / OUT 5 */
#define TLD7002_PWM_DC_GPIN0_3											0x08EU						/**< GPIN0 Duty cycle (Lower priority) configuration register OUT 6 / OUT 7 */
#define TLD7002_PWM_DC_GPIN0_4											0x08FU						/**< GPIN0 Duty cycle (Lower priority) configuration register OUT 8 / OUT 9 */
#define TLD7002_PWM_DC_GPIN0_5											0x090U						/**< GPIN0 Duty cycle (Lower priority) configuration register OUT 10 / OUT 11 */
#define TLD7002_PWM_DC_GPIN0_6											0x091U						/**< GPIN0 Duty cycle (Lower priority) configuration register OUT 12 / OUT 13 */
#define TLD7002_PWM_DC_GPIN0_7											0x092U						/**< GPIN0 Duty cycle (Lower priority) configuration register OUT 14 / OUT 15 */
#define TLD7002_CH_SAFE_STATE											0x093U						/**< Channel FAIL-SAFE state enable configuration register */
#define TLD7002_CH_ISET_0												0x094U						/**< Channel ISET configuration register OUT 0 / OUT 1 */
#define TLD7002_CH_ISET_1												0x095U						/**< Channel ISET configuration register OUT 2 / OUT 3 */
#define TLD7002_CH_ISET_2												0x096U						/**< Channel ISET configuration register OUT 4 / OUT 5 */
#define TLD7002_CH_ISET_3												0x097U						/**< Channel ISET configuration register OUT 6 / OUT 7 */
#define TLD7002_CH_ISET_4												0x098U						/**< Channel ISET configuration register OUT 8 / OUT 9 */
#define TLD7002_CH_ISET_5												0x099U						/**< Channel ISET configuration register OUT 10 / OUT 11 */
#define TLD7002_CH_ISET_6												0x09AU						/**< Channel ISET configuration register OUT 12 / OUT 13 */
#define TLD7002_CH_ISET_7												0x09BU						/**< Channel ISET configuration register OUT 14 / OUT 15 */
#define TLD7002_PWM_PHASE_EN											0x09CU						/**< PWM phase shift enable register */
#define TLD7002_CUST_CFG0												0x09DU						/**< CUSTOMER Configuration 0 register */
#define TLD7002_CUST_CFG1												0x09EU						/**< CUSTOMER Configuration 1 register */
#define TLD7002_CUST_CFG2												0x09FU						/**< CUSTOMER Configuration 2 register */
#define TLD7002_CUST_CFG3												0x0A0U						/**< CUSTOMER Configuration 3 register */
#define TLD7002_CUST_CFG4												0x0A1U						/**< CUSTOMER Configuration 4 register */
#define TLD7002_CUST_CFG5												0x0A2U						/**< CUSTOMER Configuration 5 register */
#define TLD7002_CUST_CFG6												0x0A3U						/**< CUSTOMER Configuration 6 register */
#define TLD7002_CUST_CFG7												0x0A4U						/**< CUSTOMER Configuration 7 register */
#define TLD7002_SLAVE_ID												0x0A5U						/**< SLAVE identifier register */
#define TLD7002_CUST_SGN												0x0A6U						/**< CUSTOMER signature register */
#define TLD7002_OTP_REG8												0x0A7U						/**< OPT register 8 */
#define TLD7002_OTP_REG9												0x0A8U						/**< OPT register 9 */
#define TLD7002_OTP_REG10												0x0A9U						/**< OPT register 10 */
#define TLD7002_OTP_REG11												0x0AAU						/**< OPT register 11 (general purpose) */
#define TLD7002_OTP_LOG_WORD0											0x0ABU						/**< OTP LOG Word 0 register */
#define TLD7002_OTP_LOG_WORD1											0x0ACU						/**< OTP LOG Word 1 register */
#define TLD7002_OTP_LOG_WORD2											0x0ADU						/**< OTP LOG Word 2 register */
#define TLD7002_OTP_LOG_WORD3											0x0AEU						/**< OTP LOG Word 3 register */


/******************************************************************************/
/*	Definitions for accessing the TLD7002 LED_DRIVER register bits			  */
/******************************************************************************/
/* Implements DD-SWA-337 */

/* LD_PWM_DC_CFG0 to LD_PWM_DC_CFG15 register */
/** TLD7002_LD_PWM_DC_CFGi_t
 *
 */
typedef struct
{
    uint16 PWM_DC;																					/*!< [0..13] Output duty cycle configuration. 0x000: 0 % to 0x3FF: 100 % */
    /*!< [14..15] RESERVED */
} TLD7002_LD_PWM_DC_CFGi_t;

/** TLD7002_LD_PWM_DC_CFGi positions */
#define TLD7002_LD_PWM_DC_CFGi_PWM_DC_POS									  0U					/*!< [0..13] Output duty cycle configuration */
#define TLD7002_LD_PWM_DC_CFGi_RESERVED_POS							 	     14U					/*!< [14..15] RESERVED */

/** TLD7002_LD_PWM_DC_CFGi masks */
#define TLD7002_LD_PWM_DC_CFGi_PWM_DC_MSK								  0x03FFU					/*!< [0..13] Output duty cycle configuration */
#define TLD7002_LD_PWM_DC_CFGi_RESERVED_MSK								  0xC000U					/*!< [14..15] RESERVED */

/* TLD7002_LD_PWM_DAC_CFG0 to TLD7002_LD_PWM_DAC_CFG15 register */
/** TLD7002_LD_PWM_DAC_CFGi_t
 *
 */
typedef struct
{
    uint8 DAC_CONFIG;																				/*!< [0..5] Output current configuration. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [6..7] RESERVED */
    boolean CH_RAMP_EN;																				/*!< [8] Output slew rate configuration. 0: fast slew rate; 1: normal slew rate */
    /*!< [9..15] RESERVED */
} TLD7002_LD_PWM_DAC_CFGi_t;

/** TLD7002_LD_PWM_DAC_CFGi positions */
#define TLD7002_LD_PWM_DAC_CFGi_DAC_CONFIG_POS							      0U					/*!< [0..5] Output current configuration */
#define TLD7002_LD_PWM_DAC_CFGi_RESERVED1_POS							      6U					/*!< [6..7] RESERVED */
#define TLD7002_LD_PWM_DAC_CFGi_CH_RAMP_EN_POS							      8U					/*!< [8] Output slew rate configuration */
#define TLD7002_LD_PWM_DAC_CFGi_RESERVED2_POS							      9U					/*!< [9..15] RESERVED */

/** TLD7002_LD_PWM_DAC_CFGi masks */
#define TLD7002_LD_PWM_DAC_CFGi_DAC_CONFIG_MSK							  0x003FU					/*!< [0..5] Output current configuration */
#define TLD7002_LD_PWM_DAC_CFGi_RESERVED1_MSK							  0x0060U					/*!< [6..7] RESERVED */
#define TLD7002_LD_PWM_DAC_CFGi_CH_RAMP_EN_MSK							  0x0100U					/*!< [8] Output slew rate configuration */
#define TLD7002_LD_PWM_DAC_CFGi_RESERVED2_MSK							  0xFE00U					/*!< [9..15] RESERVED */

/* TLD7002_DIAG_SLS_CFG register */
/** TLD7002_DIAG_SLS_CFG_t
 *
 */
typedef struct
{
    uint8 SLS_TH0;																					/*!< [0..7] SLS threshold for VS related VFWD measurement. 0x00: 0 V to 0xFF: 20.067 V */
    uint8 SLS_TH1;																					/*!< [8..15] SLS threshold for VLED related VFWD measurement . 0x00: 0 V to 0xFF: 20.067 V */
} TLD7002_DIAG_SLS_CFG_t;

/** TLD7002_DIAG_SLS_CFG positions */
#define TLD7002_DIAG_SLS_CFG_SLS_TH0_POS								      0U					/*!< [0..7] SLS threshold for VS related VFWD measurement */
#define TLD7002_DIAG_SLS_CFG_SLS_TH1_POS								      8U					/*!< [8..15] SLS threshold for VLED related VFWD measurement */

/** TLD7002_DIAG_SLS_CFG masks */
#define TLD7002_DIAG_SLS_CFG_SLS_TH0_MSK								  0x00FFU					/*!< [0..7] SLS threshold for VS related VFWD measurement */
#define TLD7002_DIAG_SLS_CFG_SLS_TH1_MSK								  0xFF00U					/*!< [8..15] SLS threshold for VLED related VFWD measurement */

/* TLD7002_TH_OVLD_CFG register */
/** TLD7002_TH_OVLD_CFG_t
 *
 */
typedef struct
{
    boolean TH_OVLD_CFG0;																			/*!< [0] OUT0. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG1;																			/*!< [1] OUT1. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG2;																			/*!< [2] OUT2. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG3;																			/*!< [3] OUT3. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG4;																			/*!< [4] OUT4. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG5;																			/*!< [5] OUT5. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG6;																			/*!< [6] OUT6. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG7;																			/*!< [7] OUT7. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG8;																			/*!< [8] OUT8. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG9;																			/*!< [9] OUT9. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG10;																			/*!< [10] OUT10. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG11;																			/*!< [11] OUT11. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG12;																			/*!< [12] OUT12. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG13;																			/*!< [13] OUT13. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG14;																			/*!< [14] OUT14. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
    boolean TH_OVLD_CFG15;																			/*!< [15] OUT15. 0: the TH_OVLD fault is latched, clear operation is needed to reset the fault and channel restart; 1: the TH_OVLD fault is sampled continuously, automatic reset and restart behavior is selected */
} TLD7002_TH_OVLD_CFG_t;

/** TLD7002_TH_OVLD_CFG positions */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG0_POS								      0U					/*!< [0] OUT0 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG1_POS								      1U					/*!< [1] OUT1 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG2_POS								      2U					/*!< [2] OUT2 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG3_POS								      3U					/*!< [3] OUT3 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG4_POS								      4U					/*!< [4] OUT4 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG5_POS								      5U					/*!< [5] OUT5 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG6_POS								      6U					/*!< [6] OUT6 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG7_POS								      7U					/*!< [7] OUT7 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG8_POS								      8U					/*!< [8] OUT8 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG9_POS								      9U					/*!< [9] OUT9 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG10_POS							     10U					/*!< [10] OUT10 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG11_POS							     11U					/*!< [11] OUT11 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG12_POS							     12U					/*!< [12] OUT12 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG13_POS							     13U					/*!< [13] OUT13 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG14_POS							     14U					/*!< [14] OUT14 */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG15_POS							     15U					/*!< [15] OUT15 */

/** TLD7002_TH_OVLD_CFG masks */
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG0_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG0_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG1_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG1_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG2_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG2_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG3_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG3_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG4_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG4_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG5_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG5_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG6_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG6_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG7_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG7_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG8_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG8_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG9_MSK									(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG9_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG10_MSK								(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG10_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG11_MSK								(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG11_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG12_MSK								(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG12_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG13_MSK								(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG13_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG14_MSK								(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG14_POS)
#define TLD7002_TH_OVLD_CFGTH_OVLD_CFG15_MSK								(1U << TLD7002_TH_OVLD_CFGTH_OVLD_CFG15_POS)

/* TLD7002_LD_ADC_VFWDi register */
/** TLD7002_LD_ADC_VFWDi_t
 *
 */
typedef struct
{
    uint16 VFWD;																					/*!< [0..9] VFWD conversion result. 0x000: 0 V to 0x3FF: 20.067 V */
    /*!< [10..11] RESERVED */
    boolean VAL_F;																					/*!< [12] VFWD valid flag. Indicates a new result. 0: no new result available since last readout; 1: bitfield VFWD has been updated with new results value */
    /*!< [13..15] RESERVED */
} TLD7002_LD_ADC_VFWDi_t;

/** TLD7002_LD_ADC_VFWDi positions */
#define TLD7002_LD_ADC_VFWDi_VFWD_POS									      0U					/*!< [0..9] VFWD conversion result */
#define TLD7002_LD_ADC_VFWDi_RESERVED1_POS							  		 10U					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VFWDi_VAL_F_POS									     12U					/*!< [12] VFWD valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VFWDi_RESERVED2_POS							  		 13U					/*!< [13..15] RESERVED */

/** TLD7002_LD_ADC_VFWDi masks */
#define TLD7002_LD_ADC_VFWDi_VFWD_MSK									  0x03FF					/*!< [0..9] VFWD conversion result */
#define TLD7002_LD_ADC_VFWDi_RESERVED1_MSK						  		  0x0C00					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VFWDi_VAL_F_MSK									  0x1000					/*!< [12] VFWD valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VFWDi_RESERVED2_MSK							  	  0xE000					/*!< [13..15] RESERVED */

/* TLD7002_LD_ADC_VLED register */
/** TLD7002_LD_ADC_VLED_t
 *
 */
typedef struct
{
    uint16 VLED;																					/*!< [0..9] VLED conversion result. 0x000: 0 V to 0x3FF: 20.067 V */
    /*!< [10..11] RESERVED */
    boolean VAL_F;																					/*!< [12] VLED valid flag. Indicates a new result. 0: no new result available since last readout; 1: bitfield VLED has been updated with new results value */
    /*!< [13..15] RESERVED */
} TLD7002_LD_ADC_VLED_t;

/** TLD7002_LD_ADC_VLED positions */
#define TLD7002_LD_ADC_VLED_VLED_POS									      0U					/*!< [0..9] VLED conversion result */
#define TLD7002_LD_ADC_VLED_RESERVED1_POS							  		 10U					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VLED_VAL_F_POS									     12U					/*!< [12] VLED valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VLED_RESERVED2_POS							  		 13U					/*!< [13..15] RESERVED */

/** TLD7002_LD_ADC_VLED masks */
#define TLD7002_LD_ADC_VLED_VLED_MSK									  0x03FF					/*!< [0..9] VLED conversion result */
#define TLD7002_LD_ADC_VLED_RESERVED1_MSK						  		  0x0C00					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VLED_VAL_F_MSK									  0x1000					/*!< [12] VLED valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VLED_RESERVED2_MSK							  	  0xE000					/*!< [13..15] RESERVED */

/* TLD7002_LD_ADC_VS register */
/** TLD7002_LD_ADC_VS_t
 *
 */
typedef struct
{
    uint16 VS;																						/*!< [0..9] VS conversion result. 0x000: 0 V to 0x3FF: 20.067 V */
    /*!< [10..11] RESERVED */
    boolean VAL_F;																					/*!< [12] VS valid flag. Indicates a new result. 0: no new result available since last readout; 1: bitfield VS has been updated with new results value */
    /*!< [13..15] RESERVED */
} TLD7002_LD_ADC_VS_t;

/** TLD7002_LD_ADC_VS positions */
#define TLD7002_LD_ADC_VS_VLED_POS										      0U					/*!< [0..9] VS conversion result */
#define TLD7002_LD_ADC_VS_RESERVED1_POS								  		 10U					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VS_VAL_F_POS										     12U					/*!< [12] VS valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VS_RESERVED2_POS								  		 13U					/*!< [13..15] RESERVED */

/** TLD7002_LD_ADC_VS masks */
#define TLD7002_LD_ADC_VS_VLED_MSK										  0x03FF					/*!< [0..9] VS conversion result */
#define TLD7002_LD_ADC_VS_RESERVED1_MSK							  		  0x0C00					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VS_VAL_F_MSK										  0x1000					/*!< [12] VS valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VS_RESERVED2_MSK								  	  0xE000					/*!< [13..15] RESERVED */

/* TLD7002_LD_ADC_VOUT_MIN register */
/** TLD7002_LD_ADC_VOUT_MIN_t
 *
 */
typedef struct
{
    uint16 VOUT_MIN;																				/*!< [0..9] VOUT_MIN conversion result. 0x000: 0 V to 0x3FF: 20.067 V */
    boolean VAL_F;																					/*!< [10] VOUT_MIN valid flag. Indicates a new result. 0: no new result available since last readout; 1: bitfields VOUT_MIN and VOUT_MIN_CHN has been updated with new results value */
    /*!< [11] RESERVED */
    uint8 VOUT_MIN_CHN;																				/*!< [12..15] VOUT_MIN_CHN contains the channel number of the min(VOUTn) calculation process. 0x0: CH0/OUT0 to 0xF: CH15/OUT15 */
} TLD7002_LD_ADC_VOUT_MIN_t;

/** TLD7002_LD_ADC_VOUT_MIN positions */
#define TLD7002_LD_ADC_VOUT_MIN_VLED_POS								      0U					/*!< [0..9] VOUT_MIN conversion result */
#define TLD7002_LD_ADC_VOUT_MIN_VAL_F_POS								     10U					/*!< [10] VOUT_MIN valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VOUT_MIN_RESERVED_POS						  		 11U					/*!< [11] RESERVED */
#define TLD7002_LD_ADC_VOUT_MIN_VOUT_MIN_CHN_POS					  		 12U					/*!< [12..15] VOUT_MIN_CHN contains the channel number of the min(VOUTn) calculation process. */

/** TLD7002_LD_ADC_VOUT_MIN masks */
#define TLD7002_LD_ADC_VOUT_MIN_VLED_MSK								  0x03FF					/*!< [0..9] VOUT_MIN conversion result */
#define TLD7002_LD_ADC_VOUT_MIN_VAL_F_MSK								  0x0400					/*!< [10] VOUT_MIN valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VOUT_MIN_RESERVED_MSK					  		  0x0800					/*!< [11] RESERVED */
#define TLD7002_LD_ADC_VOUT_MIN_VOUT_MIN_CHN_MSK					  	  0xF000					/*!< [12..15] VOUT_MIN_CHN contains the channel number of the min(VOUTn) calculation process. */

/* TLD7002_LD_ADC_VGPIO0 register */
/** TLD7002_LD_ADC_VGPIO0_t
 *
 */
typedef struct
{
    uint16 VGPIO0_OUT;																				/*!< [0..9] VGPIO0 conversion result. 0x000: 0 V to 0x3FF: 5.5051 V */
    /*!< [10..11] RESERVED */
    boolean VAL_F;																					/*!< [12] VGPIO0 valid flag. Indicates a new result. 0: no new result available since last readout; 1: bitfield VGPIO0 has been updated with new results value */
    /*!< [13..15] RESERVED */
} TLD7002_LD_ADC_VGPIO0_t;

/** TLD7002_LD_ADC_VGPIO0 positions */
#define TLD7002_LD_ADC_VGPIO0_VGPIO0_OUT_POS							      0U					/*!< [0..9] VGPIO0 conversion result */
#define TLD7002_LD_ADC_VGPIO0_RESERVED1_POS							  		 10U					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VGPIO0_VAL_F_POS									     12U					/*!< [12] VGPIO0 valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VGPIO0_RESERVED2_POS							  		 13U					/*!< [13..15] RESERVED */

/** TLD7002_LD_ADC_VGPIO0 masks */
#define TLD7002_LD_ADC_VGPIO0_VGPIO0_OUT_MSK							  0x03FF					/*!< [0..9] VGPIO0 conversion result */
#define TLD7002_LD_ADC_VGPIO0_RESERVED1_MSK						  		  0x0C00					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VGPIO0_VAL_F_MSK									  0x1000					/*!< [12] VGPIO0 valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VGPIO0_RESERVED2_MSK							  	  0xE000					/*!< [13..15] RESERVED */

/* TLD7002_LD_ADC_VGPIO1 register */
/** TLD7002_LD_ADC_VGPIO1_t
 *
 */
typedef struct
{
    uint16 VGPIO1_OUT;																				/*!< [0..9] VGPIO1 conversion result. 0x000: 0 V to 0x3FF: 5.5051 V */
    /*!< [10..11] RESERVED */
    boolean VAL_F;																					/*!< [12] VGPIO1 valid flag. Indicates a new result. 0: no new result available since last readout; 1: bitfield VGPIO1 has been updated with new results value */
    /*!< [13..15] RESERVED */
} TLD7002_LD_ADC_VGPIOP1_t;

/** TLD7002_LD_ADC_VGPIO1 positions */
#define TLD7002_LD_ADC_VGPIO1_VGPIO1_OUT_POS							      0U					/*!< [0..9] VGPIO1 conversion result */
#define TLD7002_LD_ADC_VGPIO1_RESERVED1_POS							  		 10U					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VGPIO1_VAL_F_POS									     12U					/*!< [12] VGPIO1 valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VGPIO1_RESERVED2_POS							  		 13U					/*!< [13..15] RESERVED */

/** TLD7002_LD_ADC_VGPIO1 masks */
#define TLD7002_LD_ADC_VGPIO1_VGPIO1_OUT_MSK							  0x03FF					/*!< [0..9] VGPIO1 conversion result */
#define TLD7002_LD_ADC_VGPIO1_RESERVED1_MSK						  		  0x0C00					/*!< [10..11] RESERVED */
#define TLD7002_LD_ADC_VGPIO1_VAL_F_MSK									  0x1000					/*!< [12] VGPIO1 valid flag. Indicates a new result */
#define TLD7002_LD_ADC_VGPIO1_RESERVED2_MSK							  	  0xE000					/*!< [13..15] RESERVED */

/* TLD7002_TH_OVLD_STATUS register */
/** TLD7002_TH_OVLD_STATUS_t
 *
 */
typedef struct
{
    boolean OVLD0;																					/*!< [0] OUT0. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD1;																					/*!< [1] OUT1. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD2;																					/*!< [2] OUT2. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD3;																					/*!< [3] OUT3. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD4;																					/*!< [4] OUT4. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD5;																					/*!< [5] OUT5. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD6;																					/*!< [6] OUT6. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD7;																					/*!< [7] OUT7. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD8;																					/*!< [8] OUT8. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD9;																					/*!< [9] OUT9. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD10;																					/*!< [10] OUT10. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD11;																					/*!< [11] OUT11. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD12;																					/*!< [12] OUT12. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD13;																					/*!< [13] OUT13. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD14;																					/*!< [14] OUT14. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
    boolean OVLD15;																					/*!< [15] OUT15. 0: no thermal overload event occured since last clear; 1: thermal overload event occured since last clear */
} TLD7002_TH_OVLD_STATUS_t;

/** TLD7002_TH_OVLD_STATUS positions */
#define TLD7002_TH_OVLD_STATUS_OVLD0_POS								      0U					/*!< [0] OUT0 */
#define TLD7002_TH_OVLD_STATUS_OVLD1_POS								      1U					/*!< [1] OUT1 */
#define TLD7002_TH_OVLD_STATUS_OVLD2_POS								      2U					/*!< [2] OUT2 */
#define TLD7002_TH_OVLD_STATUS_OVLD3_POS								      3U					/*!< [3] OUT3 */
#define TLD7002_TH_OVLD_STATUS_OVLD4_POS								      4U					/*!< [4] OUT4 */
#define TLD7002_TH_OVLD_STATUS_OVLD5_POS								      5U					/*!< [5] OUT5 */
#define TLD7002_TH_OVLD_STATUS_OVLD6_POS								      6U					/*!< [6] OUT6 */
#define TLD7002_TH_OVLD_STATUS_OVLD7_POS								      7U					/*!< [7] OUT7 */
#define TLD7002_TH_OVLD_STATUS_OVLD8_POS								      8U					/*!< [8] OUT8 */
#define TLD7002_TH_OVLD_STATUS_OVLD9_POS								      9U					/*!< [9] OUT9 */
#define TLD7002_TH_OVLD_STATUS_OVLD10_POS								     10U					/*!< [10] OUT10 */
#define TLD7002_TH_OVLD_STATUS_OVLD11_POS								     11U					/*!< [11] OUT11 */
#define TLD7002_TH_OVLD_STATUS_OVLD12_POS								     12U					/*!< [12] OUT12 */
#define TLD7002_TH_OVLD_STATUS_OVLD13_POS								     13U					/*!< [13] OUT13 */
#define TLD7002_TH_OVLD_STATUS_OVLD14_POS								     14U					/*!< [14] OUT14 */
#define TLD7002_TH_OVLD_STATUS_OVLD15_POS								     15U					/*!< [15] OUT15 */

/** TLD7002_TH_OVLD_STATUS masks */
#define TLD7002_TH_OVLD_STATUS_OVLD0_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD0_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD1_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD1_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD2_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD2_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD3_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD3_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD4_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD4_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD5_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD5_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD6_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD6_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD7_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD7_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD8_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD8_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD9_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD9_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD10_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD10_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD11_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD11_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD12_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD12_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD13_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD13_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD14_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD14_POS)
#define TLD7002_TH_OVLD_STATUS_OVLD15_MSK									(1 << TLD7002_TH_OVLD_STATUS_OVLD15_POS)

/* TLD7002_DTS_STAT register */
/** TLD7002_DTS_STAT_t
 *
 */
typedef struct
{
    boolean DTS_TEMP_READY;																			/*!< [0] Temperature conversion ready. Indicates a new result. 0: no new result available since last readout; 1: bitfield DTS_TEMP has been updated with new results value */
    boolean DTS_OVERTEMP;																			/*!< [1] DTS Overtemperature. DTS Temperature outside selected range. This is valid only if DTS_STAT.DTS_TEMP_READY = 1. 0: in range; 1: outside range condition detected */
    /*!< [2..3] RESERVED */
    uint16 DTS_TEMP;																				/*!< [4..15] Device temperature. Contains the conversion result of the last valid temperature reading. 0x000 to 0xFFF */
} TLD7002_DTS_STAT_t;

/** TLD7002_DTS_STAT positions */
#define TLD7002_DTS_STAT_DTS_TEMP_READY_POS								      0U					/*!< [0] Temperature conversion ready. Indicates a new result */
#define TLD7002_DTS_STAT_DTS_OVERTEMP_POS								  	  1U					/*!< [1] DTS Overtemperature. */
#define TLD7002_DTS_STAT_RESERVED_POS										  2U					/*!< [2..3] RESERVED */
#define TLD7002_DTS_STAT_DTS_TEMP_POS								  		  4U					/*!< [4..15] Device temperature. */

/** TLD7002_DTS_STAT masks */
#define TLD7002_DTS_STAT_DTS_TEMP_READY_MSK								  0x0001U					/*!< [0] Temperature conversion ready. Indicates a new result */
#define TLD7002_DTS_STAT_DTS_OVERTEMP_MSK						  		  0x0002U					/*!< [1] DTS Overtemperature. */
#define TLD7002_DTS_STAT_RESERVED_MSK									  0x000CU					/*!< [2..3] RESERVED */
#define TLD7002_DTS_STAT_DTS_TEMP_MSK							  		  0xFFF0U					/*!< [4..15] Device temperature. */

/* TLD7002_FW_RECON_STATUS register */
/** TLD7002_FW_RECON_STATUS_t
 *
 */
typedef struct
{
    boolean RECON_FLAG;																				/*!< [1] Reconfirmation flag. 0: No reconfirmation required; 1: Reconfirmation required */
    /*!< [1..15] RESERVED */
} TLD7002_FW_RECON_STATUS_t;

/** TLD7002_FW_RECON positions */
#define TLD7002_FW_RECON_STATUS_RECON_FLAG_POS							      0U					/*!< [0] Reconfirmation flag */
#define TLD7002_FW_RECON_STATUS_RESERVED_POS								  1U					/*!< [1..15] RESERVED */

/** TLD7002_FW_RECON masks */
#define TLD7002_FW_RECON_STATUS_RECON_FLAG_MSK							  0x0001U					/*!< [0] Reconfirmation flag */
#define TLD7002_FW_RECON_STATUS_RESERVED_MSK							  0xFFFEU					/*!< [1..15] RESERVED */


/******************************************************************************/
/*	Definitions for accessing the TLD7002 PMU register bits					  */
/******************************************************************************/
/* Implements DD-SWA-338 */

/* TLD7002_PMU_DIAG register */
/** TLD7002_PMU_DIAG_t
 *
 */
typedef struct
{
    boolean VREG_2V5_UV;																			/*!< [0] 2v5 regulator undervoltage. 0: no undervoltage event occured since last clear; 1: undervoltage event occured since last clear */
    boolean VREG_5V_UV;																				/*!< [1] 5v regulator undervoltage. 0: no undervoltage event occured since last clear; 1: undervoltage event occured since last clear */
    boolean VREG_CAN_UV;																			/*!< [2] CAN regulator undervoltage. 0: no undervoltage event occured since last clear; 1: undervoltage event occured since last clear */
    boolean VREG_CAN_OV;																			/*!< [3] CAN regulator overvoltage. 0: no overvoltage event occured since last clear; 1: overvoltage event occured since last clear */
    boolean VPRG_OTP_OV;																			/*!< [4] OTP regulator overvoltage. 0: no overvoltage event occured since last clear; 1: overvoltage event occured since last clear */
    boolean VPRG_OTP_UV;																			/*!< [5] OTP regulator undervoltage. 0: no undervoltage event occured since last clear; 1: undervoltage event occured since last clear */
    boolean VS_OTP_UV;																				/*!< [6] VS OTP undervoltage. 0: no undervoltage event occured since last clear; 1: undervoltage  event occured since last clear */
    boolean VREG_CAN_OT;																			/*!< [7] CAN regulator overtemperature. 0: no CAN regulator overtemperature event occured since last clear; 1: CAN regulator overtemperature event occured since last clear */
    boolean VREG_CAN_CURR_LIM;																		/*!< [8] 5v CAN current limitation. 0: no CAN current limitation event occured since last clear; 1: CAN current limitation event occured since last clear */
    /*!< [9..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_PMU_DIAG_t;

/** TLD7002_PMU_DIAG positions */
#define TLD7002_PMU_DIAG_VREG_2V5_UV_POS								      0U					/*!< [0] 2v5 regulator undervoltage */
#define TLD7002_PMU_DIAG_VREG_5V_UV_POS								  	      1U					/*!< [1] 5v regulator undervoltage */
#define TLD7002_PMU_DIAG_VREG_CAN_UV_POS								      2U					/*!< [2] CAN regulator undervoltage */
#define TLD7002_PMU_DIAG_VREG_CAN_OV_POS								      3U					/*!< [3] CAN regulator overvoltage */
#define TLD7002_PMU_DIAG_VPRG_OTP_OV_POS								      4U					/*!< [4] OTP regulator overvoltage */
#define TLD7002_PMU_DIAG_VPRG_OTP_UV_POS								      5U					/*!< [5] OTP regulator undervoltage */
#define TLD7002_PMU_DIAG_VS_OTP_UV_POS									      6U					/*!< [6] VS OTP undervoltage */
#define TLD7002_PMU_DIAG_VREG_CAN_OT_POS								      7U					/*!< [7] CAN regulator overtemperature */
#define TLD7002_PMU_DIAG_VREG_CAN_CURR_LIM_POS							      8U					/*!< [8] 5v CAN current limitation */
#define TLD7002_PMU_DIAG_RESERVED_POS										  9U					/*!< [8..15] RESERVED */

/** TLD7002_PMU_DIAG masks */
#define TLD7002_PMU_DIAG_VREG_2V5_UV_MSK									(1U << TLD7002_PMU_DIAG_VREG_2V5_UV_POS)
#define TLD7002_PMU_DIAG_VREG_5V_UV_MSK										(1U << TLD7002_PMU_DIAG_VREG_5V_UV_POS)
#define TLD7002_PMU_DIAG_VREG_CAN_UV_MSK									(1U << TLD7002_PMU_DIAG_VREG_CAN_UV_POS)
#define TLD7002_PMU_DIAG_VREG_CAN_OV_MSK									(1U << TLD7002_PMU_DIAG_VREG_CAN_OV_POS)
#define TLD7002_PMU_DIAG_VPRG_OTP_OV_MSK									(1U << TLD7002_PMU_DIAG_VPRG_OTP_OV_POS)
#define TLD7002_PMU_DIAG_VPRG_OTP_UV_MSK									(1U << TLD7002_PMU_DIAG_VPRG_OTP_UV_POS)
#define TLD7002_PMU_DIAG_VS_OTP_UV_MSK										(1U << TLD7002_PMU_DIAG_VS_OTP_UV_POS)
#define TLD7002_PMU_DIAG_VREG_CAN_OT_MSK									(1U << TLD7002_PMU_DIAG_VREG_CAN_OT_POS)
#define TLD7002_PMU_DIAG_VREG_CAN_CURR_LIM_MSK								(1U << TLD7002_PMU_DIAG_VREG_CAN_CURR_LIM_POS)
#define TLD7002_PMU_DIAG_RESERVED_MSK									  0xFE00U					/*!< [8..15] RESERVED */


/******************************************************************************/
/*	Definitions for accessing the TLD7002 HSLI register bits				  */
/******************************************************************************/
/* Implements DD-SWA-339 */

/* TLD7002_HSLI_TIMING_CFG register */
/** TLD7002_HSLI_TIMING_CFG_t
 *
 */
typedef struct
{
    uint8 BIT_SMPL_ADJ;																				/*!< [0..1] HSLI Bit sampling adjust field. 0b00: (default) 6,7,8; 0b01: 7,8,9; 0b10: 8,9,10; 0b11: 9,10,11 */
    uint8 SYNC_BRK_ADJ;																				/*!< [2..3] HSLI synch break time adjust field. 0b00: 100us; 0b01: 250us; 0b10: 750us; 0b11: (default) 1ms */
    uint8 FRM_DLY_ADJ;																				/*!< [4..6] HSLI frame delay time adjust field. 0b000: 50us; 0b001: 100us; 0b010: 250us; 0b011: 500us; 0b100: (default) 1ms; 0b101: 2.5ms */
    /*!< [7..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_HSLI_TIMING_CFG_t;

/** TLD7002_HSLI_TIMING_CFG positions */
#define TLD7002_HSLI_TIMING_CFG_BIT_SMPL_ADJ_POS						      0U					/*!< [0..1] HSLI Bit sampling adjust field */
#define TLD7002_HSLI_TIMING_CFG_SYNC_BRK_ADJ_POS						      2U					/*!< [2..3] HSLI synch break time adjust field */
#define TLD7002_HSLI_TIMING_CFG_FRM_DLY_ADJ_POS							      3U					/*!< [4..6] HSLI frame delay time adjust field */
#define TLD7002_HSLI_TIMING_CFG_RESERVED_POS							      7U					/*!< [7..15] RESERVED */

/** TLD7002_HSLI_TIMING_CFG masks */
#define TLD7002_HSLI_TIMING_CFG_BIT_SMPL_ADJ_MSK						  0x0003U					/*!< [0..1] HSLI Bit sampling adjust field */
#define TLD7002_HSLI_TIMING_CFG_SYNC_BRK_ADJ_MSK						  0x000CU					/*!< [2..3] HSLI synch break time adjust field */
#define TLD7002_HSLI_TIMING_CFG_FRM_DLY_ADJ_MSK							  0x0070U					/*!< [4..6] HSLI frame delay time adjust field */
#define TLD7002_HSLI_TIMING_CFG_RESERVED_MSK							  0xFF80U					/*!< [7..15] RESERVED */


/******************************************************************************/
/*	Definitions for accessing the TLD7002 OTP_CACHE register bits			  */
/******************************************************************************/
/* Implements DD-SWA-340 */

/* TLD7002_OTP_EMULATION register */
/** TLD7002_OTP_EMULATION_t
 *
 */
typedef struct
{
    uint16 SECRET;																					/*!< [0..15] SECRET. 0x0000 to 0xFFFF */
    /*!< [7..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_OTP_EMULATION_t;

/** TLD7002_OTP_EMULATION positions */
#define TLD7002_OTP_EMULATION_SECRET_POS								      0U					/*!< [0..15] SECRET */

/** TLD7002_OTP_EMULATION masks */
#define TLD7002_OTP_EMULATION_SECRET_MSK								  0xFFFFU					/*!< [0..15] SECRET */

/* TLD7002_OTP_WRITE register */
/** TLD7002_OTP_WRITE_t
 *
 */
typedef struct
{
    uint16 SECRET;																					/*!< [0..15] SECRET. 0x0000 to 0xFFFF */
    /*!< [7..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_OTP_WRITE_t;

/** TLD7002_OTP_WRITE positions */
#define TLD7002_OTP_WRITE_SECRET_POS									      0U					/*!< [0..15] SECRET */

/** TLD7002_OTP_WRITE masks */
#define TLD7002_OTP_WRITE_SECRET_MSK									  0xFFFFU					/*!< [0..15] SECRET */

/* TLD7002_OTP_STATUS register */
/** TLD7002_OTP_STATUS_t
 *
 */
typedef struct
{
    uint8 OTP_STATUS0;																				/*!< [0..1] OTP power mode status. Reports the power mode status during OTP programming. 0b00: BUS-ID emulation mode; 0b01: OTP emulation mode; 0b10: BUS-ID programming mode; 0b11: OTP programming mode */
    boolean OTP_STATUS2;																			/*!< [2] OTP mode status. 0: device is not in OTP mode; 1: device is in OTP mode */
    boolean VS;																						/*!< [3] Reports the supply condition on VS during OTP mode. 0: VS is in range; 1: VS is above overvoltage or below undervoltage threshold */
    boolean VDD_PROG;																				/*!< [4] Reports the supply condition on VDD_PROG during OTP mode. 0: VDD_PROG is in range; 1: VDD_PROG is above overvoltage or below undervoltage threshold */
    boolean VDD_5V;																					/*!< [5] Reports the supply condition on VDD_5V regulator input during OTP mode. 0: VDD_5V is in range; 1: VDD_5V is above overvoltage or below undervoltage threshold */
    boolean VDD_2V5;																				/*!< [6] Reports the supply condition on VDD_2V5 during OTP mode. 0: VDD_2V5 is in range; 1: VDD_2V5 is above overvoltage or below undervoltage threshold */
    boolean DATA_INVALID;																			/*!< [7] Reports validation errors. 0: data valid; 1: data invalid */
    boolean PRG_FAILED;																				/*!< [8] Reports programming status. 0: OK if DATA_INVALID = 0; 0: reserved if DATA_INVALID = 1; 1: programming error occurred before start if DATA_INVALID = 0; 1: programming error occurred during process if DATA_INVALID = 1 */
    boolean VIRGIN;																					/*!< [9] Reports OTP state. 0: no destination address was already programmed; 1: at least one destination address was already programmed. DATA_INVALID = 0 and PRG_FAILED = 1 */
    /*!< [10..15] RESERVED */
} TLD7002_OTP_STATUS_t;

/** TLD7002_OTP_STATUS positions */
#define TLD7002_OTP_STATUS_OTP_STATUS0_POS								      0U					/*!< [0..1] OTP power mode status */
#define TLD7002_OTP_STATUS_OTP_STATUS2_POS								      2U					/*!< [2] OTP mode status */
#define TLD7002_OTP_STATUS_VS_POS										      3U					/*!< [3] Reports the supply condition on VS during OTP mode */
#define TLD7002_OTP_STATUS_VDD_PROG_POS									      4U					/*!< [4] Reports the supply condition on VDD_PROG during OTP mode */
#define TLD7002_OTP_STATUS_VDD_5V_POS									      5U					/*!< [5] Reports the supply condition on VDD_5V regulator input during OTP mode */
#define TLD7002_OTP_STATUS_VDD_2V5_POS									      6U					/*!< [6] Reports the supply condition on VDD_2V5 during OTP mode */
#define TLD7002_OTP_STATUS_DATA_INVALID_POS								      7U					/*!< [7] Reports validation errors */
#define TLD7002_OTP_STATUS_PRG_FAILED_POS								      8U					/*!< [8] Reports programming status */
#define TLD7002_OTP_STATUS_VIRGIN_POS									      9U					/*!< [9] Reports OTP state */
#define TLD7002_OTP_STATUS_RESERVED_POS										 10U					/*!< [10..15] RESERVED */

/** TLD7002_OTP_STATUS masks */
#define TLD7002_OTP_STATUS_OTP_STATUS0									  0x0002U
#define TLD7002_OTP_STATUS_OTP_STATUS2										(1U << TLD7002_OTP_STATUS_OTP_STATUS2_POS)
#define TLD7002_OTP_STATUS_VS_MSK											(1U << TLD7002_OTP_STATUS_VS_POS)
#define TLD7002_OTP_STATUS_VDD_PROG_MSK										(1U << TLD7002_OTP_STATUS_VDD_PROG_POS)
#define TLD7002_OTP_STATUS_VDD_5V_MSK										(1U << TLD7002_OTP_STATUS_VDD_5V_POS)
#define TLD7002_OTP_STATUS_VDD_2V5_MSK										(1U << TLD7002_OTP_STATUS_VDD_2V5_POS)
#define TLD7002_OTP_STATUS_DATA_INVALID_MSK									(1U << TLD7002_OTP_STATUS_DATA_INVALID_POS)
#define TLD7002_OTP_STATUS_PRG_FAILED_MSK									(1U << TLD7002_OTP_STATUS_PRG_FAILED_POS)
#define TLD7002_OTP_STATUS_VIRGIN_MSK										(1U << TLD7002_OTP_STATUS_VIRGIN_POS)
#define TLD7002_OTP_STATUS_RESERVED_MSK									  0xFC00U					/*!< [10..15] RESERVED */

/* TLD7002_PWM_DC_GPIN1_0 register */
/** TLD7002_PWM_DC_GPIN1_0_t
 *
 */
typedef struct
{
    uint8 DC1_OUT0;																					/*!< [0..7] PWM DC for OUT0 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC1_OUT1;																					/*!< [8..15] PWM DC for OUT1 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN1_0_t;

/** TLD7002_PWM_DC_GPIN1_0 positions */
#define TLD7002_PWM_DC_GPIN1_0_DC1_OUT0_POS								      0U					/*!< [0..7] PWM DC for OUT0 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_0_DC1_OUT1_POS								      8U					/*!< [8..15] PWM DC for OUT1 mapped to GPIN1 */

/** TLD7002_PWM_DC_GPIN1_0 masks */
#define TLD7002_PWM_DC_GPIN1_0_DC1_OUT0_MSK								   0x00FFU					/*!< [0..7] PWM DC for OUT0 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_0_DC1_OUT1_MSK								   0xFF00U					/*!< [8..15] PWM DC for OUT1 mapped to GPIN1 */

/* TLD7002_PWM_DC_GPIN1_1 register */
/** TLD7002_PWM_DC_GPIN1_1_t
 *
 */
typedef struct
{
    uint8 DC1_OUT2;																					/*!< [0..7] PWM DC for OUT2 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC1_OUT3;																					/*!< [8..15] PWM DC for OUT3 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN1_1_t;

/** TLD7002_PWM_DC_GPIN1_1 positions */
#define TLD7002_PWM_DC_GPIN1_1_DC1_OUT2_POS								      0U					/*!< [0..7] PWM DC for OUT2 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_1_DC1_OUT3_POS								      8U					/*!< [8..15] PWM DC for OUT3 mapped to GPIN1 */

/** TLD7002_PWM_DC_GPIN1_1 masks */
#define TLD7002_PWM_DC_GPIN1_1_DC1_OUT2_MSK								   0x00FFU					/*!< [0..7] PWM DC for OUT2 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_1_DC1_OUT3_MSK								   0xFF00U					/*!< [8..15] PWM DC for OUT3 mapped to GPIN1 */

/* TLD7002_PWM_DC_GPIN1_2 register */
/** TLD7002_PWM_DC_GPIN1_2_t
 *
 */
typedef struct
{
    uint8 DC1_OUT4;																					/*!< [0..7] PWM DC for OUT4 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC1_OUT5;																					/*!< [8..15] PWM DC for OUT5 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN1_2_t;

/** TLD7002_PWM_DC_GPIN1_2 positions */
#define TLD7002_PWM_DC_GPIN1_2_DC1_OUT4_POS								      0U					/*!< [0..7] PWM DC for OUT4 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_2_DC1_OUT5_POS								      8U					/*!< [8..15] PWM DC for OUT5 mapped to GPIN1 */

/** TLD7002_PWM_DC_GPIN1_2 masks */
#define TLD7002_PWM_DC_GPIN1_2_DC1_OUT4_MSK								   0x00FFU					/*!< [0..7] PWM DC for OUT4 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_2_DC1_OUT5_MSK								   0xFF00U					/*!< [8..15] PWM DC for OUT5 mapped to GPIN1 */

/* TLD7002_PWM_DC_GPIN1_3 register */
/** TLD7002_PWM_DC_GPIN1_3_t
 *
 */
typedef struct
{
    uint8 DC1_OUT6;																					/*!< [0..7] PWM DC for OUT6 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC1_OUT7;																					/*!< [8..15] PWM DC for OUT7 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN1_3_t;

/** TLD7002_PWM_DC_GPIN1_3 positions */
#define TLD7002_PWM_DC_GPIN1_3_DC1_OUT6_POS								      0U					/*!< [0..7] PWM DC for OUT6 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_3_DC1_OUT7_POS								      8U					/*!< [8..15] PWM DC for OUT7 mapped to GPIN1 */

/** TLD7002_PWM_DC_GPIN1_3 masks */
#define TLD7002_PWM_DC_GPIN1_3_DC1_OUT6_MSK								   0x00FFU					/*!< [0..7] PWM DC for OUT6 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_3_DC1_OUT7_MSK								   0xFF00U					/*!< [8..15] PWM DC for OUT7 mapped to GPIN1 */

/* TLD7002_PWM_DC_GPIN1_4 register */
/** TLD7002_PWM_DC_GPIN1_4_t
 *
 */
typedef struct
{
    uint8 DC1_OUT8;																					/*!< [0..7] PWM DC for OUT8 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC1_OUT9;																					/*!< [8..15] PWM DC for OUT9 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN1_4_t;

/** TLD7002_PWM_DC_GPIN1_4 positions */
#define TLD7002_PWM_DC_GPIN1_4_DC1_OUT8_POS								      0U					/*!< [0..7] PWM DC for OUT8 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_4_DC1_OUT9_POS								      8U					/*!< [8..15] PWM DC for OUT9 mapped to GPIN1 */

/** TLD7002_PWM_DC_GPIN1_4 masks */
#define TLD7002_PWM_DC_GPIN1_4_DC1_OUT8_MSK								   0x00FFU					/*!< [0..7] PWM DC for OUT8 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_4_DC1_OUT9_MSK								   0xFF00U					/*!< [8..15] PWM DC for OUT9 mapped to GPIN1 */

/* TLD7002_PWM_DC_GPIN1_5 register */
/** TLD7002_PWM_DC_GPIN1_5_t
 *
 */
typedef struct
{
    uint8 DC1_OUT10;																				/*!< [0..7] PWM DC for OUT10 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC1_OUT11;																				/*!< [8..15] PWM DC for OUT11 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN1_5_t;

/** TLD7002_PWM_DC_GPIN1_5 positions */
#define TLD7002_PWM_DC_GPIN1_5_DC1_OUT10_POS							      0U					/*!< [0..7] PWM DC for OUT10 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_5_DC1_OUT11_POS							      8U					/*!< [8..15] PWM DC for OUT11 mapped to GPIN1 */

/** TLD7002_PWM_DC_GPIN1_5 masks */
#define TLD7002_PWM_DC_GPIN1_5_DC1_OUT10_MSK							   0x00FFU					/*!< [0..7] PWM DC for OUT10 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_5_DC1_OUT11_MSK							   0xFF00U					/*!< [8..15] PWM DC for OUT11 mapped to GPIN1 */

/* TLD7002_PWM_DC_GPIN1_6 register */
/** TLD7002_PWM_DC_GPIN1_6_t
 *
 */
typedef struct
{
    uint8 DC1_OUT12;																				/*!< [0..7] PWM DC for OUT12 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC1_OUT13;																				/*!< [8..15] PWM DC for OUT13 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN1_6_t;

/** TLD7002_PWM_DC_GPIN1_6 positions */
#define TLD7002_PWM_DC_GPIN1_6_DC1_OUT12_POS							      0U					/*!< [0..7] PWM DC for OUT12 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_6_DC1_OUT13_POS							      8U					/*!< [8..15] PWM DC for OUT13 mapped to GPIN1 */

/** TLD7002_PWM_DC_GPIN1_6 masks */
#define TLD7002_PWM_DC_GPIN1_6_DC1_OUT12_MSK							   0x00FFU					/*!< [0..7] PWM DC for OUT12 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_6_DC1_OUT13_MSK							   0xFF00U					/*!< [8..15] PWM DC for OUT13 mapped to GPIN1 */

/* TLD7002_PWM_DC_GPIN1_7 register */
/** TLD7002_PWM_DC_GPIN1_7_t
 *
 */
typedef struct
{
    uint8 DC1_OUT14;																				/*!< [0..7] PWM DC for OUT14 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC1_OUT15;																				/*!< [8..15] PWM DC for OUT15 mapped to GPIN1. Contains the direct control duty cycle via GPIN1 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN1_7_t;

/** TLD7002_PWM_DC_GPIN1_7 positions */
#define TLD7002_PWM_DC_GPIN1_7_DC1_OUT14_POS							      0U					/*!< [0..7] PWM DC for OUT14 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_7_DC1_OUT15_POS							      8U					/*!< [8..15] PWM DC for OUT15 mapped to GPIN1 */

/** TLD7002_PWM_DC_GPIN1_7 masks */
#define TLD7002_PWM_DC_GPIN1_7_DC1_OUT14_MSK							   0x00FFU					/*!< [0..7] PWM DC for OUT14 mapped to GPIN1 */
#define TLD7002_PWM_DC_GPIN1_7_DC1_OUT15_MSK							   0xFF00U					/*!< [8..15] PWM DC for OUT15 mapped to GPIN1 */

/* TLD7002_PWM_DC_GPIN0_0 register */
/** TLD7002_PWM_DC_GPIN0_0_t
 *
 */
typedef struct
{
    uint8 DC0_OUT0;																					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT0. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC0_OUT1;																					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT1. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN0_0_t;

/** TLD7002_PWM_DC_GPIN0_0 positions */
#define TLD7002_PWM_DC_GPIN0_0_DC0_OUT0_POS								      0U					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT0 */
#define TLD7002_PWM_DC_GPIN0_0_DC0_OUT1_POS								      8U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT1 */

/** TLD7002_PWM_DC_GPIN0_0 masks */
#define TLD7002_PWM_DC_GPIN0_0_DC0_OUT0_MSK								   0x00FFU					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT0 */
#define TLD7002_PWM_DC_GPIN0_0_DC0_OUT1_MSK								   0xFF00U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT1 */

/* TLD7002_PWM_DC_GPIN0_1 register */
/** TLD7002_PWM_DC_GPIN0_1_t
 *
 */
typedef struct
{
    uint8 DC0_OUT2;																					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT2. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC0_OUT3;																					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT3. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN0_1_t;

/** TLD7002_PWM_DC_GPIN0_1 positions */
#define TLD7002_PWM_DC_GPIN0_1_DC0_OUT2_POS								      0U					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT2 */
#define TLD7002_PWM_DC_GPIN0_1_DC0_OUT3_POS								      8U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT3 */

/** TLD7002_PWM_DC_GPIN0_1 masks */
#define TLD7002_PWM_DC_GPIN0_1_DC0_OUT2_MSK								   0x00FFU					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT2 */
#define TLD7002_PWM_DC_GPIN0_1_DC0_OUT3_MSK								   0xFF00U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT3 */

/* TLD7002_PWM_DC_GPIN0_2 register */
/** TLD7002_PWM_DC_GPIN0_2_t
 *
 */
typedef struct
{
    uint8 DC0_OUT4;																					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT4. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC0_OUT5;																					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT5. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN0_2_t;

/** TLD7002_PWM_DC_GPIN0_2 positions */
#define TLD7002_PWM_DC_GPIN0_2_DC0_OUT4_POS								      0U					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT4 */
#define TLD7002_PWM_DC_GPIN0_2_DC0_OUT5_POS								      8U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT5 */

/** TLD7002_PWM_DC_GPIN0_2 masks */
#define TLD7002_PWM_DC_GPIN0_2_DC0_OUT4_MSK								   0x00FFU					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT4 */
#define TLD7002_PWM_DC_GPIN0_2_DC0_OUT5_MSK								   0xFF00U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT5 */

/* TLD7002_PWM_DC_GPIN0_3 register */
/** TLD7002_PWM_DC_GPIN0_3_t
 *
 */
typedef struct
{
    uint8 DC0_OUT6;																					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT6. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC0_OUT7;																					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT7. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN0_3_t;

/** TLD7002_PWM_DC_GPIN0_3 positions */
#define TLD7002_PWM_DC_GPIN0_3_DC0_OUT6_POS								      0U					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT6 */
#define TLD7002_PWM_DC_GPIN0_3_DC0_OUT7_POS								      8U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT7 */

/** TLD7002_PWM_DC_GPIN0_3 masks */
#define TLD7002_PWM_DC_GPIN0_3_DC0_OUT6_MSK								   0x00FFU					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT6 */
#define TLD7002_PWM_DC_GPIN0_3_DC0_OUT7_MSK								   0xFF00U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT7 */

/* TLD7002_PWM_DC_GPIN0_4 register */
/** TLD7002_PWM_DC_GPIN0_4_t
 *
 */
typedef struct
{
    uint8 DC0_OUT8;																					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT8. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC0_OUT9;																					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT9. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN0_4_t;

/** TLD7002_PWM_DC_GPIN0_4 positions */
#define TLD7002_PWM_DC_GPIN0_4_DC0_OUT8_POS								      0U					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT8 */
#define TLD7002_PWM_DC_GPIN0_4_DC0_OUT9_POS								      8U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT9 */

/** TLD7002_PWM_DC_GPIN0_4 masks */
#define TLD7002_PWM_DC_GPIN0_4_DC0_OUT8_MSK								   0x00FFU					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT8 */
#define TLD7002_PWM_DC_GPIN0_4_DC0_OUT9_MSK								   0xFF00U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT9 */

/* TLD7002_PWM_DC_GPIN0_5 register */
/** TLD7002_PWM_DC_GPIN0_5_t
 *
 */
typedef struct
{
    uint8 DC0_OUT10;																				/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT10. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC0_OUT11;																				/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT11. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN0_5_t;

/** TLD7002_PWM_DC_GPIN0_5 positions */
#define TLD7002_PWM_DC_GPIN0_5_DC0_OUT10_POS							      0U					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT10 */
#define TLD7002_PWM_DC_GPIN0_5_DC0_OUT11_POS							      8U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT11 */

/** TLD7002_PWM_DC_GPIN0_5 masks */
#define TLD7002_PWM_DC_GPIN0_5_DC0_OUT10_MSK							   0x00FFU					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT10 */
#define TLD7002_PWM_DC_GPIN0_5_DC0_OUT11_MSK							   0xFF00U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT11 */

/* TLD7002_PWM_DC_GPIN0_6 register */
/** TLD7002_PWM_DC_GPIN0_6_t
 *
 */
typedef struct
{
    uint8 DC0_OUT12;																				/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT12. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC0_OUT13;																				/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT13. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN0_6_t;

/** TLD7002_PWM_DC_GPIN0_6 positions */
#define TLD7002_PWM_DC_GPIN0_6_DC0_OUT12_POS							      0U					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT12 */
#define TLD7002_PWM_DC_GPIN0_6_DC0_OUT13_POS							      8U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT13 */

/** TLD7002_PWM_DC_GPIN0_6 masks */
#define TLD7002_PWM_DC_GPIN0_6_DC0_OUT12_MSK							   0x00FFU					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT12 */
#define TLD7002_PWM_DC_GPIN0_6_DC0_OUT13_MSK							   0xFF00U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT13 */

/* TLD7002_PWM_DC_GPIN0_7 register */
/** TLD7002_PWM_DC_GPIN0_7_t
 *
 */
typedef struct
{
    uint8 DC0_OUT14;																				/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT14. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
    uint8 DC0_OUT15;																				/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT15. Contains the fail-safe duty cycle and direct control duty cycle via GPIN0 configuration. 0x00: 0 % to 0xFF: 100 % */
} TLD7002_PWM_DC_GPIN0_7_t;

/** TLD7002_PWM_DC_GPIN0_7 positions */
#define TLD7002_PWM_DC_GPIN0_7_DC0_OUT14_POS							      0U					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT14 */
#define TLD7002_PWM_DC_GPIN0_7_DC0_OUT15_POS							      8U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT15 */

/** TLD7002_PWM_DC_GPIN0_7 masks */
#define TLD7002_PWM_DC_GPIN0_7_DC0_OUT14_MSK							   0x00FFU					/*!< [0..7] Fail-safe PWM DC and GPIN0 DC for OUT14 */
#define TLD7002_PWM_DC_GPIN0_7_DC0_OUT15_MSK							   0xFF00U					/*!< [8..15] Fail-safe PWM DC and GPIN0 DC for OUT15 */

/* TLD7002_TH_CH_SAFE_STATE register */
/** TLD7002_TH_CH_SAFE_STATE_t
 *
 */
typedef struct
{
    boolean SS_EN0;																					/*!< [0] OUT0 Output state in FAIL SAFE MODE. 0: OUT0 is OFF in FAIL SAFE MODE; 1: OUT0 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN1;																					/*!< [1] OUT1 Output state in FAIL SAFE MODE. 0: OUT1 is OFF in FAIL SAFE MODE; 1: OUT1 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN2;																					/*!< [2] OUT2 Output state in FAIL SAFE MODE. 0: OUT2 is OFF in FAIL SAFE MODE; 1: OUT2 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN3;																					/*!< [3] OUT3 Output state in FAIL SAFE MODE. 0: OUT3 is OFF in FAIL SAFE MODE; 1: OUT3 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN4;																					/*!< [4] OUT4 Output state in FAIL SAFE MODE. 0: OUT4 is OFF in FAIL SAFE MODE; 1: OUT4 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN5;																					/*!< [5] OUT5 Output state in FAIL SAFE MODE. 0: OUT5 is OFF in FAIL SAFE MODE; 1: OUT5 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN6;																					/*!< [6] OUT6 Output state in FAIL SAFE MODE. 0: OUT6 is OFF in FAIL SAFE MODE; 1: OUT6 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN7;																					/*!< [7] OUT7 Output state in FAIL SAFE MODE. 0: OUT7 is OFF in FAIL SAFE MODE; 1: OUT7 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN8;																					/*!< [8] OUT8 Output state in FAIL SAFE MODE. 0: OUT8 is OFF in FAIL SAFE MODE; 1: OUT8 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN9;																					/*!< [9] OUT9 Output state in FAIL SAFE MODE. 0: OUT9 is OFF in FAIL SAFE MODE; 1: OUT9 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN10;																				/*!< [10] OUT10 Output state in FAIL SAFE MODE. 0: OUT10 is OFF in FAIL SAFE MODE; 1: OUT10 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN11;																				/*!< [11] OUT11 Output state in FAIL SAFE MODE. 0: OUT11 is OFF in FAIL SAFE MODE; 1: OUT11 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN12;																				/*!< [12] OUT12 Output state in FAIL SAFE MODE. 0: OUT12 is OFF in FAIL SAFE MODE; 1: OUT12 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN13;																				/*!< [13] OUT13 Output state in FAIL SAFE MODE. 0: OUT13 is OFF in FAIL SAFE MODE; 1: OUT13 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN14;																				/*!< [14] OUT14 Output state in FAIL SAFE MODE. 0: OUT14 is OFF in FAIL SAFE MODE; 1: OUT14 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
    boolean SS_EN15;																				/*!< [15] OUT15 Output state in FAIL SAFE MODE. 0: OUT15 is OFF in FAIL SAFE MODE; 1: OUT15 is ON in FAIL SAFE MODE with DC defined in DC0.OUT0<7:0 */
} TLD7002_TH_CH_SAFE_STATE_t;

/** TLD7002_TH_CH_SAFE_STATE positions */
#define TLD7002_CH_SAFE_STATE_SS_EN0_POS								      0U					/*!< [0] OUT0 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN1_POS								      1U					/*!< [1] OUT1 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN2_POS								      2U					/*!< [2] OUT2 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN3_POS								      3U					/*!< [3] OUT3 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN4_POS								      4U					/*!< [4] OUT4 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN5_POS								      5U					/*!< [5] OUT5 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN6_POS								      6U					/*!< [6] OUT6 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN7_POS								      7U					/*!< [7] OUT7 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN8_POS								      8U					/*!< [8] OUT8 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN9_POS								      9U					/*!< [9] OUT9 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN10_POS								     10U					/*!< [10] OUT10 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN11_POS								     11U					/*!< [11] OUT11 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN12_POS								     12U					/*!< [12] OUT12 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN13_POS								     13U					/*!< [13] OUT13 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN14_POS								     14U					/*!< [14] OUT14 Output state in FAIL SAFE MODE */
#define TLD7002_CH_SAFE_STATE_SS_EN15_POS								     15U					/*!< [15] OUT15 Output state in FAIL SAFE MODE */

/** TLD7002_TH_CH_SAFE_STATE masks */
#define TLD7002_CH_SAFE_STATE_SS_EN0_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN0_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN1_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN1_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN2_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN2_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN3_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN3_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN4_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN4_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN5_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN5_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN6_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN6_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN7_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN7_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN8_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN8_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN9_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN9_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN10_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN10_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN11_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN11_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN12_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN12_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN13_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN13_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN14_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN14_POS)
#define TLD7002_CH_SAFE_STATE_SS_EN15_MSK									(1U << TLD7002_CH_SAFE_STATE_SS_EN15_POS)

/* TLD7002_CH_ISET_0 register */
/** TLD7002_CH_ISET_0_t
 *
 */
typedef struct
{
    uint8 ISET_OUT0;																				/*!< [0..5] Current set for OUT0. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    uint8 ISET_OUT1;																				/*!< [6..11] Current set for OUT1. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [12..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_CH_ISET_0_t;

/** TLD7002_CH_ISET_0 positions */
#define TLD7002_CH_ISET_0_ISET_OUT0_POS									      0U					/*!< [0..5] Current set for OUT0 */
#define TLD7002_CH_ISET_0_ISET_OUT1_POS									      6U					/*!< [6..11] Current set for OUT1 */
#define TLD7002_CH_ISET_0_RESERVED_POS										 12U					/*!< [12..15] RESERVED */

/** TLD7002_CH_ISET_0 masks */
#define TLD7002_CH_ISET_0_ISET_OUT0_MSK									   0x003FU					/*!< [0..5] Current set for OUT0 */
#define TLD7002_CH_ISET_0_ISET_OUT1_MSK									   0x0FC0U					/*!< [6..11] Current set for OUT1 */
#define TLD7002_CH_ISET_0_RESERVED_MSK									   0xF000U					/*!< [12..15] RESERVED */

/* TLD7002_CH_ISET_1 register */
/** TLD7002_CH_ISET_1_t
 *
 */
typedef struct
{
    uint8 ISET_OUT2;																				/*!< [0..5] Current set for OUT2. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    uint8 ISET_OUT3;																				/*!< [6..11] Current set for OUT3. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [12..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_CH_ISET_1_t;

/** TLD7002_CH_ISET_1 positions */
#define TLD7002_CH_ISET_1_ISET_OUT2_POS									      0U					/*!< [0..5] Current set for OUT2 */
#define TLD7002_CH_ISET_1_ISET_OUT3_POS									      6U					/*!< [6..11] Current set for OUT3 */
#define TLD7002_CH_ISET_1_RESERVED_POS										 12U					/*!< [12..15] RESERVED */

/** TLD7002_CH_ISET_1 masks */
#define TLD7002_CH_ISET_1_ISET_OUT2_MSK									   0x003FU					/*!< [0..5] Current set for OUT2 */
#define TLD7002_CH_ISET_1_ISET_OUT3_MSK									   0x0FC0U					/*!< [6..11] Current set for OUT3 */
#define TLD7002_CH_ISET_1_RESERVED_MSK									   0xF000U					/*!< [12..15] RESERVED */

/* TLD7002_CH_ISET_2 register */
/** TLD7002_CH_ISET_2_t
 *
 */
typedef struct
{
    uint8 ISET_OUT4;																				/*!< [0..5] Current set for OUT4. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    uint8 ISET_OUT5;																				/*!< [6..11] Current set for OUT5. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [12..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_CH_ISET_2_t;

/** TLD7002_CH_ISET_2 positions */
#define TLD7002_CH_ISET_2_ISET_OUT4_POS									      0U					/*!< [0..5] Current set for OUT4 */
#define TLD7002_CH_ISET_2_ISET_OUT5_POS									      6U					/*!< [6..11] Current set for OUT5 */
#define TLD7002_CH_ISET_2_RESERVED_POS										 12U					/*!< [12..15] RESERVED */


/** TLD7002_CH_ISET_2 masks */
#define TLD7002_CH_ISET_2_ISET_OUT4_MSK									   0x003FU					/*!< [0..5] Current set for OUT4 */
#define TLD7002_CH_ISET_2_ISET_OUT5_MSK									   0x0FC0U					/*!< [6..11] Current set for OUT5 */
#define TLD7002_CH_ISET_2_RESERVED_MSK									   0xF000U					/*!< [12..15] RESERVED */

/* TLD7002_CH_ISET_3 register */
/** TLD7002_CH_ISET_3_t
 *
 */
typedef struct
{
    uint8 ISET_OUT6;																				/*!< [0..5] Current set for OUT6. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    uint8 ISET_OUT7;																				/*!< [6..11] Current set for OUT7. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [12..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_CH_ISET_3_t;

/** TLD7002_CH_ISET_3 positions */
#define TLD7002_CH_ISET_3_ISET_OUT6_POS									      0U					/*!< [0..5] Current set for OUT6 */
#define TLD7002_CH_ISET_3_ISET_OUT7_POS									      6U					/*!< [6..11] Current set for OUT7 */
#define TLD7002_CH_ISET_3_RESERVED_POS										 12U					/*!< [12..15] RESERVED */

/** TLD7002_CH_ISET_3 masks */
#define TLD7002_CH_ISET_3_ISET_OUT6_MSK									   0x003FU					/*!< [0..5] Current set for OUT6 */
#define TLD7002_CH_ISET_3_ISET_OUT7_MSK									   0x0FC0U					/*!< [6..11] Current set for OUT7 */
#define TLD7002_CH_ISET_3_RESERVED_MSK									   0xF000U					/*!< [12..15] RESERVED */

/* TLD7002_CH_ISET_4 register */
/** TLD7002_CH_ISET_4_t
 *
 */
typedef struct
{
    uint8 ISET_OUT8;																				/*!< [0..5] Current set for OUT8. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    uint8 ISET_OUT9;																				/*!< [6..11] Current set for OUT9. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [12..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_CH_ISET_4_t;

/** TLD7002_CH_ISET_4 positions */
#define TLD7002_CH_ISET_4_ISET_OUT8_POS									      0U					/*!< [0..5] Current set for OUT8 */
#define TLD7002_CH_ISET_4_ISET_OUT9_POS									      6U					/*!< [6..11] Current set for OUT9 */
#define TLD7002_CH_ISET_4_RESERVED_POS										 12U					/*!< [12..15] RESERVED */

/** TLD7002_CH_ISET_4 masks */
#define TLD7002_CH_ISET_4_ISET_OUT8_MSK									   0x003FU					/*!< [0..5] Current set for OUT8 */
#define TLD7002_CH_ISET_4_ISET_OUT9_MSK									   0x0FC0U					/*!< [6..11] Current set for OUT9 */
#define TLD7002_CH_ISET_4_RESERVED_MSK									   0xF000U					/*!< [12..15] RESERVED */

/* TLD7002_CH_ISET_5 register */
/** TLD7002_CH_ISET_5_t
 *
 */
typedef struct
{
    uint8 ISET_OUT10;																				/*!< [0..5] Current set for OUT10. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    uint8 ISET_OUT11;																				/*!< [6..11] Current set for OUT11. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [12..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_CH_ISET_5_t;

/** TLD7002_CH_ISET_5 positions */
#define TLD7002_CH_ISET_5_ISET_OUT10_POS								      0U					/*!< [0..5] Current set for OUT10 */
#define TLD7002_CH_ISET_5_ISET_OUT11_POS								      6U					/*!< [6..11] Current set for OUT11 */
#define TLD7002_CH_ISET_5_RESERVED_POS										 12U					/*!< [12..15] RESERVED */

/** TLD7002_CH_ISET_5 masks */
#define TLD7002_CH_ISET_5_ISET_OUT10_MSK								   0x003FU					/*!< [0..5] Current set for OUT10 */
#define TLD7002_CH_ISET_5_ISET_OUT11_MSK								   0x0FC0U					/*!< [6..11] Current set for OUT11 */
#define TLD7002_CH_ISET_5_RESERVED_MSK									   0xF000U					/*!< [12..15] RESERVED */

/* TLD7002_CH_ISET_6 register */
/** TLD7002_CH_ISET_6_t
 *
 */
typedef struct
{
    uint8 ISET_OUT12;																				/*!< [0..5] Current set for OUT12. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    uint8 ISET_OUT13;																				/*!< [6..11] Current set for OUT13. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [12..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_CH_ISET_6_t;

/** TLD7002_CH_ISET_6 positions */
#define TLD7002_CH_ISET_6_ISET_OUT12_POS								      0U					/*!< [0..5] Current set for OUT12 */
#define TLD7002_CH_ISET_6_ISET_OUT13_POS								      6U					/*!< [6..11] Current set for OUT13 */
#define TLD7002_CH_ISET_6_RESERVED_POS										 12U					/*!< [12..15] RESERVED */

/** TLD7002_CH_ISET_6 masks */
#define TLD7002_CH_ISET_6_ISET_OUT12_MSK								   0x003FU					/*!< [0..5] Current set for OUT12 */
#define TLD7002_CH_ISET_6_ISET_OUT13_MSK								   0x0FC0U					/*!< [6..11] Current set for OUT13 */
#define TLD7002_CH_ISET_6_RESERVED_MSK									   0xF000U					/*!< [12..15] RESERVED */

/* TLD7002_CH_ISET_7 register */
/** TLD7002_CH_ISET_7_t
 *
 */
typedef struct
{
    uint8 ISET_OUT14;																				/*!< [0..5] Current set for OUT14. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    uint8 ISET_OUT15;																				/*!< [6..11] Current set for OUT15. 0x00: 5.625 mA to 0x3F: 76.5 mA */
    /*!< [12..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_CH_ISET_7_t;

/** TLD7002_CH_ISET_7 positions */
#define TLD7002_CH_ISET_7_ISET_OUT14_POS								      0U					/*!< [0..5] Current set for OUT14 */
#define TLD7002_CH_ISET_7_ISET_OUT15_POS								      6U					/*!< [6..11] Current set for OUT15 */
#define TLD7002_CH_ISET_7_RESERVED_POS										 12U					/*!< [12..15] RESERVED */

/** TLD7002_CH_ISET_7 masks */
#define TLD7002_CH_ISET_7_ISET_OUT14_MSK								   0x003FU					/*!< [0..5] Current set for OUT14 */
#define TLD7002_CH_ISET_7_ISET_OUT15_MSK								   0x0FC0U					/*!< [6..11] Current set for OUT15 */
#define TLD7002_CH_ISET_7_RESERVED_MSK									   0xF000U					/*!< [12..15] RESERVED */

/* TLD7002_PWM_PHASE_EN register */
/** TLD7002_PWM_PHASE_EN_t
 *
 */
typedef struct
{
    boolean SHIFT_EN0;																				/*!< [0] OUT0 Phase shift Enable. 0: OUT0 has no phase shift compared to OUTn-1; 1: OUT0 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN1;																				/*!< [1] OUT1 Phase shift Enable. 0: OUT1 has no phase shift compared to OUTn-1; 1: OUT1 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN2;																				/*!< [2] OUT2 Phase shift Enable. 0: OUT2 has no phase shift compared to OUTn-1; 1: OUT2 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN3;																				/*!< [3] OUT3 Phase shift Enable. 0: OUT3 has no phase shift compared to OUTn-1; 1: OUT3 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN4;																				/*!< [4] OUT4 Phase shift Enable. 0: OUT4 has no phase shift compared to OUTn-1; 1: OUT4 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN5;																				/*!< [5] OUT5 Phase shift Enable. 0: OUT5 has no phase shift compared to OUTn-1; 1: OUT5 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN6;																				/*!< [6] OUT6 Phase shift Enable. 0: OUT6 has no phase shift compared to OUTn-1; 1: OUT6 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN7;																				/*!< [7] OUT7 Phase shift Enable. 0: OUT7 has no phase shift compared to OUTn-1; 1: OUT7 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN8;																				/*!< [8] OUT8 Phase shift Enable. 0: OUT8 has no phase shift compared to OUTn-1; 1: OUT8 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN9;																				/*!< [9] OUT9 Phase shift Enable. 0: OUT9 has no phase shift compared to OUTn-1; 1: OUT9 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN10;																				/*!< [10] OUT10 Phase shift Enable. 0: OUT10 has no phase shift compared to OUTn-1; 1: OUT10 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN11;																				/*!< [11] OUT11 Phase shift Enable. 0: OUT11 has no phase shift compared to OUTn-1; 1: OUT11 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN12;																				/*!< [12] OUT12 Phase shift Enable. 0: OUT12 has no phase shift compared to OUTn-1; 1: OUT12 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN13;																				/*!< [13] OUT13 Phase shift Enable. 0: OUT13 has no phase shift compared to OUTn-1; 1: OUT13 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN14;																				/*!< [14] OUT14 Phase shift Enable. 0: OUT14 has no phase shift compared to OUTn-1; 1: OUT14 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
    boolean SHIFT_EN15;																				/*!< [15] OUT15 Phase shift Enable. 0: OUT15 has no phase shift compared to OUTn-1; 1: OUT15 has a phase shift compared to OUTn-1. Note: PWM_PHASE_SHIFTEN.OUT0 is always 0, means no phase shift. */
} TLD7002_PWM_PHASE_EN_t;

/** TLD7002_PWM_PHASE_EN positions */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN0_POS								      0U					/*!< [0] OUT0 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN1_POS								      1U					/*!< [1] OUT1 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN2_POS								      2U					/*!< [2] OUT2 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN3_POS								      3U					/*!< [3] OUT3 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN4_POS								      4U					/*!< [4] OUT4 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN5_POS								      5U					/*!< [5] OUT5 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN6_POS								      6U					/*!< [6] OUT6 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN7_POS								      7U					/*!< [7] OUT7 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN8_POS								      8U					/*!< [8] OUT8 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN9_POS								      9U					/*!< [9] OUT9 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN10_POS								     10U					/*!< [10] OUT10 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN11_POS								     11U					/*!< [11] OUT11 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN12_POS								     12U					/*!< [12] OUT12 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN13_POS								     13U					/*!< [13] OUT13 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN14_POS								     14U					/*!< [14] OUT14 Phase shift Enable */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN15_POS								     15U					/*!< [15] OUT15 Phase shift Enable */

/** TLD7002_PWM_PHASE_EN masks */
#define TLD7002_PWM_PHASE_EN_SHIFT_EN0_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN0_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN1_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN1_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN2_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN2_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN3_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN3_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN4_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN4_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN5_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN5_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN6_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN6_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN7_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN7_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN8_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN8_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN9_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN9_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN10_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN10_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN11_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN11_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN12_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN12_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN13_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN13_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN14_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN14_POS)
#define TLD7002_PWM_PHASE_EN_SHIFT_EN15_MSK									(1U << TLD7002_PWM_PHASE_EN_SHIFT_EN15_POS)

/* TLD7002_CUST_CFG0 register */
/** TLD7002_CUST_CFG0
 *
 */
typedef struct
{
    uint8 PWM_FREQ;																					/*!< [0..3] PWM base frequency. 0x0: 100 Hz; 0x1: 200 Hz; 0x2: 240 Hz; 0x3: 300 Hz; 0x4: 360 Hz; 0x5: 400 Hz; 0x6: 540 Hz; 0x7: 600 Hz; 0x8: 660 Hz; 0x9: 720 Hz; 0xA: 780 Hz; 0xB: 900 Hz; 0xC: 1200 Hz; 0xD: 1500 Hz; 0xE: 1800 Hz; 0xF: 2000 Hz; */
    uint8 PWM_PHASE_SHIFT;																			/*!< [4..8] Set the delay between channel n and channel n-1. 0x0: 0 as 14-bit duty cycle reference or 0%; 0x01: equivalent to 32 D as 14-bit duty cycle reference or 0.195%; ... 0x0F: equivalent to 512 D as 14-bit duty cycle reference or 3.125%; ... 0x1F: equivalent to 992 D as 14-bit duty cycle reference or 6.0547% */
    boolean GPIN0_DC_DEC_EN;																		/*!< [9] Duty cycle decoder enable for GPIN0. 0: GPIN0 will be decoded according to the static level at pin; 1: GPIN0 will be decoded according duty cycle level */
    boolean GPIN1_DC_DEC_EN;																		/*!< [10] Duty cycle decoder enable for GPIN0. 0: GPIN1 will be decoded according to the static level at pin; 1: GPIN1 will be decoded according duty cycle level */
    boolean CH_DCDC_OUT0_EN;																		/*!< [11] OUT0 masking for the min(VOUn) measurements. 0: OUT0 is included - not masked - in the min(VOUT) measurement (default); 1: OUT0 is excluded - masked out - from the min(VOUT) measurement */
    boolean GPIN1_INV_EN;																			/*!< [12] GPIN1 inverter enable. 0:  the GPIN1 is not inverted; 1: the GPIN1 is inverted signal */
    boolean GPIN0_Func_OE;																			/*!< [13] Out enable function GPIN0 is used to enable the output stage. 0: GPIN0 is not used as output enable function (default); 1: GPIN0 is the output enable, GPIN0='0' outputs are disabled, GPIN0='1' outputs are enabled */
    boolean GPIN0_HiZ_EN;																			/*!< [14] GPIN configuration for Analog or Digital input. 0: GPIN0 is set as Digital Input and pull down is enabled and ADC will not convert the GPIN0 value; 1: GPIN0 is set as Analog Input and pull down is disable and ADC will convert the GPIN0 voltage value */
    boolean GPIN1_HiZ_EN;																			/*!< [15] GPIN configuration for Analog or Digital input. 0: GPIN1 is set as Digital Input and pull down is enabled and ADC will not convert the GPIN1 value; 1: GPIN1 is set as Analog Input and pull down is disable and ADC will convert the GPIN1 voltage value */
} TLD7002_CUST_CFG0_t;

/** TLD7002_CUST_CFG0 positions */
#define TLD7002_CUST_CFG0_PWM_FREQ_POS									      0U					/*!< [0..3] PWM base frequency. */
#define TLD7002_CUST_CFG0_PWM_PHASE_SHIFT_POS							      4U					/*!< [4..8] Set the delay between channel n and channel n-1.  */
#define TLD7002_CUST_CFG0_GPIN0_DC_DEC_EN_POS							      9U					/*!< [9] Duty cycle decoder enable for GPIN0. */
#define TLD7002_CUST_CFG0_GPIN1_DC_DEC_EN_POS							     10U					/*!< [10] Duty cycle decoder enable for GPIN0. */
#define TLD7002_CUST_CFG0_CH_DCDC_OUT0_EN_POS							     11U					/*!< [11] OUT0 masking for the min(VOUn) measurements. */
#define TLD7002_CUST_CFG0_GPIN1_INV_EN_POS								     12U					/*!< [12] GPIN1 inverter enable. */
#define TLD7002_CUST_CFG0_GPIN0_Func_OE_POS								     13U					/*!< [13] Out enable function GPIN0 is used to enable the output stage. */
#define TLD7002_CUST_CFG0_GPIN0_HiZ_EN_POS								     14U					/*!< [14] GPIN configuration for Analog or Digital input. */
#define TLD7002_CUST_CFG0_GPIN1_HiZ_EN_POS								     15U					/*!< [15] GPIN configuration for Analog or Digital input. */

/** TLD7002_CUST_CFG0 masks */
#define TLD7002_CUST_CFG0_PWM_FREQ_MSK									  0x000FU					/*!< [0..3] PWM base frequency. */
#define TLD7002_CUST_CFG0_PWM_PHASE_SHIFT_MSK							  0x01F0U					/*!< [4..8] Set the delay between channel n and channel n-1. */
#define TLD7002_CUST_CFG0_GPIN0_DC_DEC_EN_MSK							    (1U << TLD7002_CUST_CFG0_GPIN0_DC_DEC_EN_POS)
#define TLD7002_CUST_CFG0_GPIN1_DC_DEC_EN_MSK							    (1U << TLD7002_CUST_CFG0_GPIN1_DC_DEC_EN_POS)
#define TLD7002_CUST_CFG0_CH_DCDC_OUT0_EN_MSK							    (1U << TLD7002_CUST_CFG0_CH_DCDC_OUT0_EN_POS)
#define TLD7002_CUST_CFG0_GPIN1_INV_EN_MSK								    (1U << TLD7002_CUST_CFG0_GPIN1_INV_EN_POS)
#define TLD7002_CUST_CFG0_GPIN0_Func_OE_MSK								    (1U << TLD7002_CUST_CFG0_GPIN0_Func_OE_POS)
#define TLD7002_CUST_CFG0_GPIN0_HiZ_EN_MSK								    (1U << TLD7002_CUST_CFG0_GPIN0_HiZ_EN_POS)
#define TLD7002_CUST_CFG0_GPIN1_HiZ_EN_MSK								    (1U << TLD7002_CUST_CFG0_GPIN1_HiZ_EN_POS)

/* TLD7002_CUST_CFG1 register */
/** TLD7002_CUST_CFG1
 *
 */
typedef struct
{
    uint8 DIAG_VDEN_VS;																				/*!< [0..4] VDEN Threshold for VS. VDEN_threshold from 0.625V up to 20V in 0.625V steps. 0x00: 0.625 V; 0x01: 1.25 V; to 0x1F: 20 V */
    uint8 DIAG_VDEN_VLED;																			/*!< [5..9] VDEN Threshold for VLED. VDEN_threshold from 0.625V up to 20V in 0.625V steps. 0x00: 0.625 V; 0x01: 1.25 V; to 0x1F: 20 V */
    uint8 DIAG_TDELAY;																				/*!< [10..12] Delay time for the start of the ADC conversion. Diagnostic sample delay from 8 us up to 600 us. 0x0: 8 us; 0x1: 16 us; 0x2: 24 us; 0x3: 48 us; 0x4: 96 us; 0x5: 192 us; 0x6: 500 us; 0x7: 600 us */
    uint8 DIAG_OUT15_ERRn_EN;																		/*!< [13..15] ERRN enable on OUT15. ERRN active on OUT15. 0b000: ERRN function disabled on OUT15; 0b111: ERRN function enabled on OUT15 */
} TLD7002_CUST_CFG1_t;

/** TLD7002_CUST_CFG1 positions */
#define TLD7002_CUST_CFG1_DIAG_VDEN_VS_POS								      0U					/*!< [0..4] VDEN Threshold for VS. VDEN_threshold from 0.625V up to 20V in 0.625V steps. */
#define TLD7002_CUST_CFG1_DIAG_VDEN_VLED_POS						  		  5U					/*!< [5..9] VDEN Threshold for VLED. VDEN_threshold from 0.625V up to 20V in 0.625V steps. */
#define TLD7002_CUST_CFG1_DIAG_TDELAY_POS								     10U					/*!< [10..12] Delay time for the start of the ADC conversion. Diagnostic sample delay from 8 us up to 600 us. */
#define TLD7002_CUST_CFG1_DIAG_OUT15_ERRn_EN_POS				 		     13U					/*!< [13..15] ERRN enable on OUT15. ERRN active on OUT15. */

/** TLD7002_CUST_CFG1 masks */
#define TLD7002_CUST_CFG1_DIAG_VDEN_VS_MSK								  0x001FU					/*!< [0..4] VDEN Threshold for VS. VDEN_threshold from 0.625V up to 20V in 0.625V steps. */
#define TLD7002_CUST_CFG1_DIAG_VDEN_VLED_MSK							  0x03E0U					/*!< [5..9] VDEN Threshold for VLED. VDEN_threshold from 0.625V up to 20V in 0.625V steps. */
#define TLD7002_CUST_CFG1_DIAG_TDELAY_MSK								  0x1C00U					/*!< [10..12] Delay time for the start of the ADC conversion. Diagnostic sample delay from 8 us up to 600 us. */
#define TLD7002_CUST_CFG1_DIAG_OUT15_ERRn_EN_MSK						  0xE000U					/*!< [13..15] ERRN enable on OUT15. ERRN active on OUT15. */

/* TLD7002_CUST_CFG2 register */
/** TLD7002_CUST_CFG2
 *
 */
typedef struct
{
    boolean SHORT_WRN_EN_OUT0;																		/*!< [0] OUT0 Map of the 16 channels to the GPIN0. 0: OUT0 short between adjacent channel is disabled (for channel working in parallel); 1: OUT0 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT1;																		/*!< [1] OUT1 Map of the 16 channels to the GPIN0. 0: OUT1 short between adjacent channel is disabled (for channel working in parallel); 1: OUT1 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT2;																		/*!< [2] OUT2 Map of the 16 channels to the GPIN0. 0: OUT2 short between adjacent channel is disabled (for channel working in parallel); 1: OUT2 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT3;																		/*!< [3] OUT3 Map of the 16 channels to the GPIN0. 0: OUT3 short between adjacent channel is disabled (for channel working in parallel); 1: OUT3 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT4;																		/*!< [4] OUT4 Map of the 16 channels to the GPIN0. 0: OUT4 short between adjacent channel is disabled (for channel working in parallel); 1: OUT4 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT5;																		/*!< [5] OUT5 Map of the 16 channels to the GPIN0. 0: OUT5 short between adjacent channel is disabled (for channel working in parallel); 1: OUT5 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT6;																		/*!< [6] OUT6 Map of the 16 channels to the GPIN0. 0: OUT6 short between adjacent channel is disabled (for channel working in parallel); 1: OUT6 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT7;																		/*!< [7] OUT7 Map of the 16 channels to the GPIN0. 0: OUT7 short between adjacent channel is disabled (for channel working in parallel); 1: OUT7 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT8;																		/*!< [8] OUT8 Map of the 16 channels to the GPIN0. 0: OUT8 short between adjacent channel is disabled (for channel working in parallel); 1: OUT8 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT9;																		/*!< [9] OUT9 Map of the 16 channels to the GPIN0. 0: OUT9 short between adjacent channel is disabled (for channel working in parallel); 1: OUT9 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT10;																		/*!< [10] OUT10 Map of the 16 channels to the GPIN0. 0: OUT10 short between adjacent channel is disabled (for channel working in parallel); 1: OUT10 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT11;																		/*!< [11] OUT11 Map of the 16 channels to the GPIN0. 0: OUT11 short between adjacent channel is disabled (for channel working in parallel); 1: OUT11 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT12;																		/*!< [12] OUT12 Map of the 16 channels to the GPIN0. 0: OUT12 short between adjacent channel is disabled (for channel working in parallel); 1: OUT12 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT13;																		/*!< [13] OUT13 Map of the 16 channels to the GPIN0. 0: OUT13 short between adjacent channel is disabled (for channel working in parallel); 1: OUT13 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT14;																		/*!< [14] OUT14 Map of the 16 channels to the GPIN0. 0: OUT14 short between adjacent channel is disabled (for channel working in parallel); 1: OUT14 short between adjacent channel is enabled */
    boolean SHORT_WRN_EN_OUT15;																		/*!< [15] OUT15 Map of the 16 channels to the GPIN0. 0: OUT15 short between adjacent channel is disabled (for channel working in parallel); 1: OUT15 short between adjacent channel is enabled */
} TLD7002_CUST_CFG2_t;

/** TLD7002_CUST_CFG2 positions */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT0_POS							      0U					/*!< [0] OUT0 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT1_POS							      1U					/*!< [1] OUT1 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT2_POS							      2U					/*!< [2] OUT2 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT3_POS							      3U					/*!< [3] OUT3 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT4_POS							      4U					/*!< [4] OUT4 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT5_POS							      5U					/*!< [5] OUT5 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT6_POS							      6U					/*!< [6] OUT6 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT7_POS							      7U					/*!< [7] OUT7 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT8_POS							      8U					/*!< [8] OUT8 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT9_POS							      9U					/*!< [9] OUT9 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT10_POS						     10U					/*!< [10] OUT10 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT11_POS						     11U					/*!< [11] OUT11 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT12_POS						     12U					/*!< [12] OUT12 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT13_POS						     13U					/*!< [13] OUT13 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT14_POS						     14U					/*!< [14] OUT14 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT15_POS						     15U					/*!< [15] OUT15 Map of the 16 channels to the GPIN0. */

/** TLD7002_CUST_CFG2 masks */
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT0_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT0_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT1_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT1_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT2_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT2_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT3_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT3_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT4_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT4_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT5_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT5_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT6_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT6_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT7_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT7_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT8_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT8_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT9_MSK								(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT9_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT10_MSK							(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT10_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT11_MSK							(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT11_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT12_MSK							(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT12_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT13_MSK							(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT13_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT14_MSK							(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT14_POS)
#define TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT15_MSK							(1U << TLD7002_CUST_CFG2_SHORT_WRN_EN_OUT15_POS)

/* TLD7002_CUST_CFG3 register */
/** TLD7002_CUST_CFG3
 *
 */
typedef struct
{
    uint8 SLS_TH0;																					/*!< [0..7] SLS threshold VS related VFWD. SLS threshold for VS related VFWD measurement from 0V to 20.067V in 256 steps. 0x00: 0 V to 0xFF: 20.067 V */
    uint8 SLS_TH1;																					/*!< [8..15] SLS threshold VLED related VFWD. SLS threshold for VLED related VFWD measurement from 0V to 20.067V in 256 steps. 0: OUT9 has no phase 0x00: 0 V to 0xFF: 20.067 V */
} TLD7002_CUST_CFG3_t;

/** TLD7002_CUST_CFG3 positions */
#define TLD7002_CUST_CFG3_SLS_TH0_POS									      0U					/*!< [0..7] SLS threshold VS related VFWD. SLS threshold for VS related VFWD measurement from 0V to 20.067V in 256 steps. */
#define TLD7002_CUST_CFG3_SLS_TH1_POS									      8U					/*!< [8..15] SLS threshold VLED related VFWD. SLS threshold for VLED related VFWD measurement from 0V to 20.067V in 256 steps. */

/** TLD7002_CUST_CFG3 masks */
#define TLD7002_CUST_CFG3_SLS_TH0_MSK									  0x00FFU					/*!< [0..7] SLS threshold VS related VFWD. SLS threshold for VS related VFWD measurement from 0V to 20.067V in 256 steps. */
#define TLD7002_CUST_CFG3_SLS_TH1_MSK									  0xFF00U					/*!< [8..15] SLS threshold VLED related VFWD. SLS threshold for VLED related VFWD measurement from 0V to 20.067V in 256 steps. */

/* TLD7002_CUST_CFG4 register */
/** TLD7002_CUST_CFG4
 *
 */
typedef struct
{
    boolean DIAG_OUT_GROUP_OUT0;																	/*!< [0] OUT0 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT1;																	/*!< [1] OUT1 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT2;																	/*!< [2] OUT2 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT3;																	/*!< [3] OUT3 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT4;																	/*!< [4] OUT4 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT5;																	/*!< [5] OUT5 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT6;																	/*!< [6] OUT6 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT7;																	/*!< [7] OUT7 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT8;																	/*!< [8] OUT8 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT9;																	/*!< [9] OUT9 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT10;																	/*!< [10] OUT10 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT11;																	/*!< [11] OUT11 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT12;																	/*!< [12] OUT12 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT13;																	/*!< [13] OUT13 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT14;																	/*!< [14] OUT14 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
    boolean DIAG_OUT_GROUP_OUT15;																	/*!< [15] OUT15 Diagnostic Group for the anode voltage for LED. 0: VFWDn = VS - VOUTn; 1: VFWDn = VLED - VOUTn (default) */
} TLD7002_CUST_CFG4_t;

/** TLD7002_CUST_CFG4 positions */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT0_POS						      0U					/*!< [0] OUT0 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT1_POS						      1U					/*!< [1] OUT1 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT2_POS						      2U					/*!< [2] OUT2 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT3_POS						      3U					/*!< [3] OUT3 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT4_POS						      4U					/*!< [4] OUT4 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT5_POS						      5U					/*!< [5] OUT5 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT6_POS						      6U					/*!< [6] OUT6 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT7_POS						      7U					/*!< [7] OUT7 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT8_POS						      8U					/*!< [8] OUT8 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT9_POS						      9U					/*!< [9] OUT9 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT10_POS						     10U					/*!< [10] OUT10 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT11_POS						     11U					/*!< [11] OUT11 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT12_POS						     12U					/*!< [12] OUT12 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT13_POS						     13U					/*!< [13] OUT13 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT14_POS						     14U					/*!< [14] OUT14 Diagnostic Group for the anode voltage for LED. */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT15_POS						     15U					/*!< [15] OUT15 Diagnostic Group for the anode voltage for LED. */

/** TLD7002_CUST_CFG4 masks */
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT0_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT0_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT1_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT1_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT2_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT2_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT3_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT3_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT4_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT4_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT5_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT5_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT6_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT6_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT7_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT7_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT8_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT8_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT9_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT9_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT10_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT10_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT11_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT11_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT12_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT12_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT13_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT13_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT14_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT14_POS)
#define TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT15_MSK							(1U << TLD7002_CUST_CFG4_DIAG_OUT_GROUP_OUT15_POS)

/* TLD7002_CUST_CFG5 register */
/** TLD7002_CUST_CFG5
 *
 */
typedef struct
{
    boolean GPIN0_MAP_OUT0;																			/*!< [0] OUT0 Map of the 16 channels to the GPIN0. 0: OUT0 is not mapped to the GPIN0; 1: OUT0 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT1;																			/*!< [1] OUT1 Map of the 16 channels to the GPIN0. 0: OUT1 is not mapped to the GPIN0; 1: OUT1 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT2;																			/*!< [2] OUT2 Map of the 16 channels to the GPIN0. 0: OUT2 is not mapped to the GPIN0; 1: OUT2 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT3;																			/*!< [3] OUT3 Map of the 16 channels to the GPIN0. 0: OUT3 is not mapped to the GPIN0; 1: OUT3 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT4;																			/*!< [4] OUT4 Map of the 16 channels to the GPIN0. 0: OUT4 is not mapped to the GPIN0; 1: OUT4 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT5;																			/*!< [5] OUT5 Map of the 16 channels to the GPIN0. 0: OUT5 is not mapped to the GPIN0; 1: OUT5 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT6;																			/*!< [6] OUT6 Map of the 16 channels to the GPIN0. 0: OUT6 is not mapped to the GPIN0; 1: OUT6 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT7;																			/*!< [7] OUT7 Map of the 16 channels to the GPIN0. 0: OUT7 is not mapped to the GPIN0; 1: OUT7 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT8;																			/*!< [8] OUT8 Map of the 16 channels to the GPIN0. 0: OUT8 is not mapped to the GPIN0; 1: OUT8 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT9;																			/*!< [9] OUT9 Map of the 16 channels to the GPIN0. 0: OUT9 is not mapped to the GPIN0; 1: OUT9 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT10;																		/*!< [10] OUT10 Map of the 16 channels to the GPIN0. 0: OUT10 is not mapped to the GPIN0; 1: OUT10 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT11;																		/*!< [11] OUT11 Map of the 16 channels to the GPIN0. 0: OUT11 is not mapped to the GPIN0; 1: OUT11 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT12;																		/*!< [12] OUT12 Map of the 16 channels to the GPIN0. 0: OUT12 is not mapped to the GPIN0; 1: OUT12 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT13;																		/*!< [13] OUT13 Map of the 16 channels to the GPIN0. 0: OUT13 is not mapped to the GPIN0; 1: OUT13 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT14;																		/*!< [14] OUT14 Map of the 16 channels to the GPIN0. 0: OUT14 is not mapped to the GPIN0; 1: OUT14 is mapped to GPIN0 with DC0_OUTn<7:0> */
    boolean GPIN0_MAP_OUT15;																		/*!< [15] OUT15 Map of the 16 channels to the GPIN0. 0: OUT15 is not mapped to the GPIN0; 1: OUT15 is mapped to GPIN0 with DC0_OUTn<7:0> */
} TLD7002_CUST_CFG5_t;

/** TLD7002_CUST_CFG5 positions */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT0_POS							      0U					/*!< [0] OUT0 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT1_POS							      1U					/*!< [1] OUT1 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT2_POS							      2U					/*!< [2] OUT2 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT3_POS							      3U					/*!< [3] OUT3 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT4_POS							      4U					/*!< [4] OUT4 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT5_POS							      5U					/*!< [5] OUT5 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT6_POS						    	  6U					/*!< [6] OUT6 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT7_POS							      7U					/*!< [7] OUT7 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT8_POS							      8U					/*!< [8] OUT8 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT9_POS							      9U					/*!< [9] OUT9 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT10_POS							     10U					/*!< [10] OUT10 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT11_POS							     11U					/*!< [11] OUT11 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT12_POS							     12U					/*!< [12] OUT12 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT13_POS							     13U					/*!< [13] OUT13 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT14_POS							     14U					/*!< [14] OUT14 Map of the 16 channels to the GPIN0. */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT15_POS							     15U					/*!< [15] OUT15 Map of the 16 channels to the GPIN0. */

/** TLD7002_CUST_CFG5 masks */
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT0_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT0_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT1_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT1_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT2_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT2_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT3_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT3_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT4_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT4_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT5_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT5_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT6_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT6_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT7_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT7_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT8_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT8_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT9_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT9_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT10_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT10_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT11_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT11_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT12_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT12_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT13_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT13_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT14_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT14_POS)
#define TLD7002_CUST_CFG5_GPIN0_MAP_OUT15_MSK								(1U << TLD7002_CUST_CFG5_GPIN0_MAP_OUT15_POS)

/* TLD7002_CUST_CFG6 register */
/** TLD7002_CUST_CFG6
 *
 */
typedef struct
{
    boolean GPIN1_MAP_OUT0;																			/*!< [0] OUT0 Map of the 16 channels to the GPIN1. 0: OUT0 is not mapped to the GPIN1; 1: OUT0 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT1;																			/*!< [1] OUT1 Map of the 16 channels to the GPIN1. 0: OUT1 is not mapped to the GPIN1; 1: OUT1 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT2;																			/*!< [2] OUT2 Map of the 16 channels to the GPIN1. 0: OUT2 is not mapped to the GPIN1; 1: OUT2 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT3;																			/*!< [3] OUT3 Map of the 16 channels to the GPIN1. 0: OUT3 is not mapped to the GPIN1; 1: OUT3 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT4;																			/*!< [4] OUT4 Map of the 16 channels to the GPIN1. 0: OUT4 is not mapped to the GPIN1; 1: OUT4 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT5;																			/*!< [5] OUT5 Map of the 16 channels to the GPIN1. 0: OUT5 is not mapped to the GPIN1; 1: OUT5 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT6;																			/*!< [6] OUT6 Map of the 16 channels to the GPIN1. 0: OUT6 is not mapped to the GPIN1; 1: OUT6 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT7;																			/*!< [7] OUT7 Map of the 16 channels to the GPIN1. 0: OUT7 is not mapped to the GPIN1; 1: OUT7 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT8;																			/*!< [8] OUT8 Map of the 16 channels to the GPIN1. 0: OUT8 is not mapped to the GPIN1; 1: OUT8 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT9;																			/*!< [9] OUT9 Map of the 16 channels to the GPIN1. 0: OUT9 is not mapped to the GPIN1; 1: OUT9 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT10;																		/*!< [10] OUT10 Map of the 16 channels to the GPIN1. 0: OUT10 is not mapped to the GPIN1; 1: OUT10 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT11;																		/*!< [11] OUT11 Map of the 16 channels to the GPIN1. 0: OUT11 is not mapped to the GPIN1; 1: OUT11 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT12;																		/*!< [12] OUT12 Map of the 16 channels to the GPIN1. 0: OUT12 is not mapped to the GPIN1; 1: OUT12 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT13;																		/*!< [13] OUT13 Map of the 16 channels to the GPIN1. 0: OUT13 is not mapped to the GPIN1; 1: OUT13 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT14;																		/*!< [14] OUT14 Map of the 16 channels to the GPIN1. 0: OUT14 is not mapped to the GPIN1; 1: OUT14 is mapped to GPIN1 with DC1_OUTn<7:0> */
    boolean GPIN1_MAP_OUT15;																		/*!< [15] OUT15 Map of the 16 channels to the GPIN1. 0: OUT15 is not mapped to the GPIN1; 1: OUT15 is mapped to GPIN1 with DC1_OUTn<7:0> */
} TLD7002_CUST_CFG6_t;

/** TLD7002_CUST_CFG6 positions */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT0_POS							      0U					/*!< [0] OUT0 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT1_POS							      1U					/*!< [1] OUT1 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT2_POS							      2U					/*!< [2] OUT2 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT3_POS							      3U					/*!< [3] OUT3 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT4_POS							      4U					/*!< [4] OUT4 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT5_POS							      5U					/*!< [5] OUT5 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT6_POS						    	  6U					/*!< [6] OUT6 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT7_POS							      7U					/*!< [7] OUT7 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT8_POS							      8U					/*!< [8] OUT8 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT9_POS							      9U					/*!< [9] OUT9 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT10_POS							     10U					/*!< [10] OUT10 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT11_POS							     11U					/*!< [11] OUT11 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT12_POS							     12U					/*!< [12] OUT12 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT13_POS							     13U					/*!< [13] OUT13 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT14_POS							     14U					/*!< [14] OUT14 Map of the 16 channels to the GPIN1. */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT15_POS							     15U					/*!< [15] OUT15 Map of the 16 channels to the GPIN1. */

/** TLD7002_CUST_CFG6 masks */
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT0_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT0_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT1_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT1_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT2_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT2_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT3_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT3_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT4_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT4_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT5_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT5_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT6_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT6_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT7_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT7_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT8_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT8_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT9_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT9_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT10_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT10_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT11_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT11_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT12_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT12_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT13_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT13_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT14_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT14_POS)
#define TLD7002_CUST_CFG6_GPIN1_MAP_OUT15_MSK								(1U << TLD7002_CUST_CFG6_GPIN1_MAP_OUT15_POS)

/* TLD7002_CUST_CFG7 register */
/** TLD7002_CUST_CFG7
 *
 */
typedef struct
{
    uint8 DIAG_WDT_SET;																				/*!< [0..2] Watchdog timeout. 0x0: 10 ms; 0x1: 20 ms; 0x2: 50 ms; 0x3: 100 ms; 0x4: 200 ms; 0x5: 500 ms; 0x6: 1000 ms; 0x7: 2000 ms */
    uint8 VFWD_VLED_TH;																				/*!< [3..6] Thresholds for the short to VLED - LSB=1.25 V. 0x0: 1.25 V; 0x1: 2.5 V; 0x2: 3.75 V; 0x3: 5 V; 0x4: 6.25 V; 0x5: 7.5 V; 0x6: 8.75 V; 0x7: 10 V; 0x8: 11.25 V; 0x9: 12.5 V; 0xA: 13.75 V; 0xB: 15 V; 0xC: 16.25 V; 0xD: 17.5 V; 0xE: 18.75 V; 0xF: 20 V */
    uint8 VFWD_VS_TH;																				/*!< [7..10] Thresholds for the short to VS - LSB=1.25 V. 0x0: 1.25 V; 0x1: 2.5 V; 0x2: 3.75 V; 0x3: 5 V; 0x4: 6.25 V; 0x5: 7.5 V; 0x6: 8.75 V; 0x7: 10 V; 0x8: 11.25 V; 0x9: 12.5 V; 0xA: 13.75 V; 0xB: 15 V; 0xC: 16.25 V; 0xD: 17.5 V; 0xE: 18.75 V; 0xF: 20 V */
    uint8 DIAG_mgnt_SET;																			/*!< [11] Fault management configuration. 0: no state change (default); 1: change to init mode (power stages are turned off) if VS AND VLED >= VDEN_thresholds */
    boolean DIAG_OUT_SWOFF_DC100;																	/*!< [12] Diagnostic switch OFF for outputs with 100% duty cycle. 0: the output with DC=100% will not have the diagnostic switch OFF.; 1: the output with DC=100% will be switched OFF every 4 period to allow the short detection with its adjacent output. */
    boolean PWR_OFF_LOAD_EN;																		/*!< [13] Power off load global enable function. 0: Power off load global disabled; 1: Power off load global enabled */
    boolean DIAG_SLS_LOCK;																			/*!< [14] Lock of the SLS thresholds. 0: SLS thresholds used by LED driver can be programmed via HSLI.; 1: SLS thresholds used by LED driver is only from OTP. */
    boolean CURR_WRN_REP_DIS;																		/*!< [15] Current Warning ERRN report Disable. 0: Current Warning ERRN report enabled; 1: Current Warning ERRN report disabled */
} TLD7002_CUST_CFG7_t;

/** TLD7002_CUST_CFG7 positions */
#define TLD7002_CUST_CFG7_DIAG_WDT_SET_POS								      0U					/*!< [0..2] Watchdog timeout. */
#define TLD7002_CUST_CFG7_VFWD_VLED_TH_POS								      1U					/*!< [3..6] Thresholds for the short to VLED - LSB=1.25 V. */
#define TLD7002_CUST_CFG7_VFWD_VS_TH_POS							    	  2U					/*!< [7..10] Thresholds for the short to VS - LSB=1.25 V. */

#define TLD7002_CUST_CFG7_DIAG_mgnt_SET_POS								     11U					/*!< [11] Fault management configuration. */
#define TLD7002_CUST_CFG7_DIAG_OUT_SWOFF_DC100_POS						     12U					/*!< [12] Diagnostic switch OFF for outputs with 100% duty cycle. */
#define TLD7002_CUST_CFG7_PWR_OFF_LOAD_EN_POS							     13U					/*!< [13] Power off load global enable function. */
#define TLD7002_CUST_CFG7_DIAG_SLS_LOCK_POS								     14U					/*!< [14] Lock of the SLS thresholds. */
#define TLD7002_CUST_CFG7_CURR_WRN_REP_DIS_POS							     15U					/*!< [15] Current Warning ERRN report Disable. */

/** TLD7002_CUST_CFG7 masks */
#define TLD7002_CUST_CFG7_DIAG_WDT_SET_MSK								  0x0007U					/*!< [0..2] Watchdog timeout. */
#define TLD7002_CUST_CFG7_VFWD_VLED_TH_MSK								  0x0078U					/*!< [3..6] Thresholds for the short to VLED - LSB=1.25 V. */
#define TLD7002_CUST_CFG7_VFWD_VS_TH_MSK							      0x0780U					/*!< [7..10] Thresholds for the short to VS - LSB=1.25 V. */
#define TLD7002_CUST_CFG7_DIAG_mgnt_SET_MSK									(1U << TLD7002_CUST_CFG7_DIAG_mgnt_SET_POS)
#define TLD7002_CUST_CFG7_DIAG_OUT_SWOFF_DC100_MSK							(1U << TLD7002_CUST_CFG7_DIAG_OUT_SWOFF_DC100_POS)
#define TLD7002_CUST_CFG7_PWR_OFF_LOAD_EN_MSK								(1U << TLD7002_CUST_CFG7_PWR_OFF_LOAD_EN_POS)
#define TLD7002_CUST_CFG7_DIAG_SLS_LOCK_MSK									(1U << TLD7002_CUST_CFG7_DIAG_SLS_LOCK_POS)
#define TLD7002_CUST_CFG7_CURR_WRN_REP_DIS_MSK								(1U << TLD7002_CUST_CFG7_CURR_WRN_REP_DIS_POS)

/* TLD7002_SLAVE_ID register */
/** TLD7002_SLAVE_ID_t
 *
 */
typedef struct
{
    uint8 HSLI_ADDR;																				/*!< [0..4] HSLI slave node address. Defines the BUS-ID ranging from 1 to 31. */
    /*!< [5..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_SLAVE_ID_t;

/** TLD7002_SLAVE_ID positions */
#define TLD7002_SLAVE_ID_HSLI_ADDR_POS									      0U					/*!< [0..4] HSLI slave node address. */
#define TLD7002_SLAVE_ID_RESERVED_POS										  5U					/*!< [5..15] RESERVED */

/** TLD7002_SLAVE_ID masks */
#define TLD7002_SLAVE_ID_ISET_OUT12_MSK									  0x001FU					/*!< [0..4] HSLI slave node address. */
#define TLD7002_SLAVE_ID_RESERVED_MSK									  0xFFE0U					/*!< [5..15] RESERVED */

/* TLD7002_CUST_SGN register */
/** TLD7002_CUST_SGN_t
 *
 */
typedef struct
{
    uint16 CUST_CRC;																				/*!< [0..15] CRC to secure the OTP CUST DATA */
} TLD7002_CUST_SGN_t;

/** TLD7002_CUST_SGN positions */
#define TLD7002_CUST_SGN_CUST_CRC_POS									      0U					/*!< [0..15] CRC to secure the OTP CUST DATA */

/** TLD7002_CUST_SGN masks */
#define TLD7002_CUST_SGN_CUST_CRC_MSK									  0xFFFFU					/*!< [0..15] CRC to secure the OTP CUST DATA */

/* TLD7002_OTP_REG8 register */
/** TLD7002_OTP_REG8
 *
 */
typedef struct
{
    boolean CH_TH_DER_EN;																			/*!< [0] Thermal derating Enable. 0: thermal derating is disabled; 1: thermal derating is enabled */
    uint8 CH_TH_DER_TH;																				/*!< [1..3] Thermal derating TJDER configuration. 0x0: 20 �C - TJstart = TJstop - 20 �C; 0x1: 30 �C - TJstart = TJstop - 30 �C; 0x2: 40 �C - TJstart = TJstop - 40 �C; 0x3: 50 �C - TJstart = TJstop - 50 �C; 0x4: 60 �C - TJstart = TJstop - 60 �C */
    uint8 PWR_OFF_LOAD_CH_SET;																		/*!< [4..7] tbd */
    uint8 PWR_OFF_LOAD_TH_CH01_SET;																	/*!< [8..9] tbd */
    uint8 PWR_OFF_LOAD_TH_CH23_SET;																	/*!< [10..11] tbd */
    uint8 PWR_OFF_LOAD_TH_CH89_SET;																	/*!< [12..13] tbd */
    uint8 PWR_OFF_LOAD_TH_CH1011_SET;																/*!< [14..15] tbd */
} TLD7002_OTP_REG8_t;

/** TLD7002_OTP_REG8 positions */
#define TLD7002_OTP_REG8_CH_TH_DER_EN_POS								      0U					/*!< [0] Thermal derating Enable */
#define TLD7002_OTP_REG8_CH_TH_DER_TH_POS								      1U					/*!< [1..3] Thermal derating TJDER configuration */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_CH_SET_POS					   		  4U					/*!< [4..7] tbd */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_TH_CH01_SET_POS					      8U					/*!< [8..9] tbd */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_TH_CH23_SET_POS					     10U					/*!< [10..11] tbd */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_TH_CH89_SET_POS					     12U					/*!< [12..13] tbd */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_TH_CH1011_SET_POS					     14U					/*!< [14..15] tbd */

/** TLD7002_OTP_REG8 masks */
#define TLD7002_OTP_REG8_CH_TH_DER_EN_MSK								  0x0001U					/*!< [0] Thermal derating Enable */
#define TLD7002_OTP_REG8_CH_TH_DER_TH_MSK								  0x000EU					/*!< [1..3] Thermal derating TJDER configuration */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_CH_SET_MSK					   	  0x00F0U					/*!< [4..7] tbd */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_TH_CH01_SET_MSK					  0x0300U					/*!< [8..9] tbd */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_TH_CH23_SET_MSK					  0x0C00U					/*!< [10..11] tbd */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_TH_CH89_SET_MSK					  0x3000U					/*!< [12..13] tbd */
#define TLD7002_OTP_REG8_PWR_OFF_LOAD_TH_CH1011_SET_MSK					  0xC000U					/*!< [14..15] tbd */

/* TLD7002_OTP_REG9 register */
/** TLD7002_OTP_REG9
 *
 */
typedef struct
{
    uint8 HSLI_T_BITSMPL;																			/*!< [0..1] Setup of the sampling time. 0x0: (default) 6,7,8; 0x1: 7,8,9; 0x2: 8,9,10; 0x3: 9,10,11 */
    uint8 HSLI_T_SYNC_BREAK;																		/*!< [2..3] Setup of the sync break time. 0x0: 100 us; 0x1: 250 us; 0x2: 750 us; 0x3: (default) 1 ms  */
    uint8 HSLI_T_FRAME_DLY;																			/*!< [4..6] Setup of the frame delay time. 0x0: 50 us; 0x1: 100 us; 0x2: 250 us; 0x3: 500 us; 0x4: (default) 1 ms; 0x5: 2,5 ms */
    boolean RAMP_EN;																				/*!< [7] Led Driver RAMP enable for each channels. 0: fast slew rate is set for all output channels; can be changed via REG_WRITE; 1: normal slew rate is set for all output channels; can be changed via REG_WRITE */
    /*!< [8..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_OTP_REG9_t;

/** TLD7002_OTP_REG9 positions */
#define TLD7002_OTP_REG9_HSLI_T_BITSMPL_POS								      0U					/*!< [0..1] Setup of the sampling time */
#define TLD7002_OTP_REG9_HSLI_T_SYNC_BREAK_POS							      2U					/*!< [2..3] Setup of the sync break time */
#define TLD7002_OTP_REG9_HSLI_T_FRAME_DLY_POS							      4U					/*!< [4..6] Setup of the frame delay time */
#define TLD7002_OTP_REG9_RAMP_EN_POS									      7U					/*!< [7] Led Driver RAMP enable for each channels */
#define TLD7002_OTP_REG9_RESERVED_POS									      8U					/*!< [8..15] RESERVED */

/** TLD7002_OTP_REG9 masks */
#define TLD7002_OTP_REG9_HSLI_T_BITSMPL_MSK								  0x0003U					/*!< [0..1] Setup of the sampling time */
#define TLD7002_OTP_REG9_HSLI_T_SYNC_BREAK_MSK							  0x000CU					/*!< [2..3] Setup of the sync break time */
#define TLD7002_OTP_REG9_HSLI_T_FRAME_DLY_MSK							  0x0070U					/*!< [4..6] Setup of the frame delay time */
#define TLD7002_OTP_REG9_RAMP_EN_MSK									  0x0080U					/*!< [7] Led Driver RAMP enable for each channels */
#define TLD7002_OTP_REG9_RESERVED_MSK									  0xFF00U					/*!< [8..15] RESERVED */

/* TLD7002_OTP_REG10 register */
/** TLD7002_OTP_REG10
 *
 */
typedef struct
{
    uint8 VGPIN0_TJSTART;																			/*!< [0..4] Low threshold for the Thermal derating. 0x0 to 0x20 */
    uint8 VGPIN0_TJSTOP;																			/*!< [5..9] High threshold for the Thermal derating. 0x0 to 0x20 */
    uint8 CH_TH_DER_GPIN;																			/*!< [10] Thermal de-rating switch between DTS and GPIN0. 0: deactivated ; 1: activated */
    /*!< [11..15] RESERVED. Returns 0 if read; should be written with 0. */
} TLD7002_OTP_REG10_t;

/** TLD7002_OTP_REG10 positions */
#define TLD7002_OTP_REG10_VGPIN0_TJSTART_POS							      0U					/*!< [0..4] Low threshold for the Thermal derating */
#define TLD7002_OTP_REG10_VGPIN0_TJSTOP_POS								      5U					/*!< [5..9] High threshold for the Thermal derating */
#define TLD7002_OTP_REG10_CH_TH_DER_GPIN_POS							     10U					/*!< [10] Thermal de-rating switch between DTS and GPIN0 */
#define TLD7002_OTP_REG10_RESERVED_POS									     11U					/*!< [11..15] RESERVED */

/** TLD7002_OTP_REG10 masks */
#define TLD7002_OTP_REG10_VGPIN0_TJSTART_MSK							  0x001FU					/*!< [0..4] Low threshold for the Thermal derating */
#define TLD7002_OTP_REG10_VGPIN0_TJSTOP_MSK								  0x03E0U					/*!< [5..9] High threshold for the Thermal derating */
#define TLD7002_OTP_REG10_CH_TH_DER_GPIN_MSK							  0x0400U					/*!< [10] Thermal de-rating switch between DTS and GPIN0 */
#define TLD7002_OTP_REG10_RESERVED_MSK									  0xF800U					/*!< [11..15] RESERVED */

/* TLD7002_OTP_REG11 register */
/** TLD7002_OTP_REG11_t
 *
 */
typedef struct
{
    uint16 GP_WORD;																					/*!< [0..15] General Purpose OTP Word */
} TLD7002_OTP_REG11_t;

/** TLD7002_OTP_REG11 positions */
#define TLD7002_OTP_REG11_GP_WORD_POS									      0U					/*!< [0..15] General Purpose OTP Word */

/** TLD7002_OTP_REG11 masks */
#define TLD7002_OTP_REG11_GP_WORD_MSK									  0xFFFFU					/*!< [0..15] General Purpose OTP Word */

/* TLD7002_OTP_LOG_WORD0 register */
/** TLD7002_OTP_LOG_WORD0_t
 *
 */
typedef struct
{
    uint16 LOG_WORD0;																				/*!< [0..15] OTP LOG Word 0 */
} TLD7002_OTP_LOG_WORD0_t;

/** TLD7002_OTP_LOG_WORD0 positions */
#define TLD7002_OTP_LOG_WORD0_LOG_WORD0_POS								      0U					/*!< [0..15] OTP LOG Word 0 */

/** TLD7002_OTP_LOG_WORD0 masks */
#define TLD7002_OTP_LOG_WORD0_LOG_WORD0_MSK								  0xFFFFU					/*!< [0..15] OTP LOG Word 0 */

/* TLD7002_OTP_LOG_WORD1 register */
/** TLD7002_OTP_LOG_WORD1_t
 *
 */
typedef struct
{
    uint16 LOG_WORD1;																				/*!< [0..15] OTP LOG Word 1 */
} TLD7002_OTP_LOG_WORD1_t;

/** TLD7002_OTP_LOG_WORD1 positions */
#define TLD7002_OTP_LOG_WORD1_LOG_WORD1_POS								      0U					/*!< [0..15] OTP LOG Word 1 */

/** TLD7002_OTP_LOG_WORD1 masks */
#define TLD7002_OTP_LOG_WORD1_LOG_WORD1_MSK								  0xFFFFU					/*!< [0..15] OTP LOG Word 1 */

/* TLD7002_OTP_LOG_WORD2 register */
/** TLD7002_OTP_LOG_WORD2_t
 *
 */
typedef struct
{
    uint16 LOG_WORD2;																				/*!< [0..15] OTP LOG Word 2 */
} TLD7002_OTP_LOG_WORD2_t;

/** TLD7002_OTP_LOG_WORD2 positions */
#define TLD7002_OTP_LOG_WORD2_LOG_WORD2_POS								      0U					/*!< [0..15] OTP LOG Word 2 */

/** TLD7002_OTP_LOG_WORD2 masks */
#define TLD7002_OTP_LOG_WORD2_LOG_WORD2_MSK								  0xFFFFU					/*!< [0..15] OTP LOG Word 2 */

/* TLD7002_OTP_LOG_WORD3 register */
/** TLD7002_OTP_LOG_WORD3_t
 *
 */
typedef struct
{
    uint16 LOG_WORD3;																				/*!< [0..15] OTP LOG Word 3 */
} TLD7002_OTP_LOG_WORD3_t;

/** TLD7002_OTP_LOG_WORD3 positions */
#define TLD7002_OTP_LOG_WORD3_LOG_WORD3_POS								      0U					/*!< [0..15] OTP LOG Word 3 */

/** TLD7002_OTP_LOG_WORD3 masks */
#define TLD7002_OTP_LOG_WORD3_LOG_WORD3_MSK								  0xFFFFU					/*!< [0..15] OTP LOG Word 3 */

#endif /* TLD7002_DEFINITIONS_H_ */
/**@}*/