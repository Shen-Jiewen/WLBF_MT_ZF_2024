/**
 *  @file TLD7002_ControlLayer.h
 *  @author Infineon
 *  @date 17.06.2022
 *	@brief TLD7002 specific Device Driver implementation from Infineon Technologies AG.
 *	@note  This file includes the definitions for the TLD7002 control layer
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

#ifndef TLD7002_CONTROL_LAYER_H_
#define TLD7002_CONTROL_LAYER_H_

/******************************************************************************/
/*	Includes																  */
/******************************************************************************/
#include "TLD7002.h"
#include "TLD7002_Definitions.h"

/******************************************************************************/
/*	Version definition									                      */
/******************************************************************************/
/* Implements DD-SWA-298 */
#define TLD7002_DEVICE_DRIVER_MAJOR_VERSION						  		7
/* Implements DD-SWA-299 */
#define TLD7002_DEVICE_DRIVER_MINOR_VERSION						  		0
/* Implements DD-SWA-300 */
#define TLD7002_DEVICE_DRIVER_VERSION 			STR(TLD7002_DEVICE_DRIVER_MAJOR_VERSION)"."STR(TLD7002_DEVICE_DRIVER_MINOR_VERSION)

/******************************************************************************/
/*	Global CRC lookup table declarations                                      */
/******************************************************************************/
/* CRC3 lookup table for 5 bit value */
/* Implements DD-SWA-316 */
extern const uint8 TLD7002_LOOKUP_CRC3_5BIT[32];

/* CRC3 lookup table for 8 bit value */
/* Implements DD-SWA-317 */
extern const uint8 TLD7002_LOOKUP_CRC3_8BIT[256];

/* CRC3 lookup table used for reflection */
/* Implements DD-SWA-318 */
extern const uint8 TLD7002_MIRROR_MID_CRC3[8];

/* CRC8 lookup table */
/* Implements DD-SWA-319 */
extern const uint8 TLD7002_LOOKUP_CRC8_SAE_J1850[256];

/* DC_UPDATE NON_LIN to LIN lookup table */
/* Implements DD-SWA-320 */
extern const uint8 TLD7002_LOOKUP_LIN_DC_8BIT[256];

/******************************************************************************/
/*	Basic Definitions for TLD7002											  */
/******************************************************************************/
/** number of elements of an array of LED groups */
/* Implements DD-SWA-301 */
#define TLD7002_ARRAY_SIZE(array) (sizeof(array) / sizeof(*array))

/* Implements DD-SWA-302 */
#define TLD7002_NUM_DEVICES					 32U						/**< number of TLD7002 devices */
/* Implements DD-SWA-303 */
#define TLD7002_NUM_CH					 	 16U						/**< number of TLD7002 channels */

/* Implements DD-SWA-304 */
#define TLD7002_LOW_BYTE_16BIT			 0x00FFU						/**< low byte of a 16 bit number */
#define TLD7002_HIGH_BYTE_16BIT			 0xFF00U						/**< high byte of a 16 bit number */
#define TLD7002_HIGH_BYTE_14BIT			 0x3F00U						/**< high byte of a 13 bit number */
#define TLD7002_SHIFT16						 16U						/**< Shift value to extended/decrease with 16 Bit (65536) */


/* Implements DD-SWA-305 */
#define TLD7002_CH_MIN_DC_VAL				  0U						/**< minimum duty cycle for 8 bit and 14 bit duty cycle configuration */
#define TLD7002_CH_MAX_DC_8BIT_VAL			255U						/**< maximum duty cycle for 8 bit duty cycle configuration */
#define TLD7002_CH_MAX_DC_14BIT_VAL		  16383U						/**< maximum duty cycle for 14 bit duty cycle configuration */
#define TLD7002_CH_MIN_DUTY_CYCLE			  0U						/**< minimum channel duty-cycle */
#define TLD7002_CH_MAX_DUTY_CYCLE		  10000U						/**< maximum channel duty-cycle (multiplied with 100 to increase accuracy )*/
#define TLD7002_CH_MAX_CONTROLLED_CURRENT	 75U						/**< maximum controlled current in milliampere */

/* Implements DD-SWA-306 */
#define TLD7002_CRC8_CALC_SEED				0xFFU						/**< CRC-8 (according to CRC-8-AUTOSAR and SAEJ1850) seed */
#define TLD7002_CRC8_CALC_GENERATOR_POLYNOM	0x1DU						/**< CRC-8 (according to CRC-8-AUTOSAR and SAEJ1850) generator polynom value */
#define TLD7002_CRC8_CALC_XOR_VAL			0xFFU						/**< CRC-8 (according to CRC-8-AUTOSAR and SAEJ1850) xor value */
#define TLD7002_CRC3_CALC_SEED				0x05U						/**< CRC-3 seed */
#define TLD7002_CRC3_CALC_GENERATOR_POLYNOM	0x00U						/**< CRC-3 generator polynom value */
#define TLD7002_CRC3_CALC_XOR_VAL			0x00U						/**< CRC-3 xor value */

/** choice between CRC8 Lookup Table and calculation. */
/* Implements ?????? */
#define TLD7002_CRC8_USE_LUT					 1 						/**< use CRC8 lookup table */
#define TLD7002_CRC8_USE_CALC					 2						/**< use CRC8 calculation */

#define TLD7002_CRC8_CONF_ALGORITHM			TLD7002_CRC8_USE_CALC		/**< set configured CRC algorithm */

/** choice between linear and non-linear DC_UPDATE 8 Bit data representation. In TLD7002 DC_UPDATE 8 Bit is a non-linear 8-bit duty cycle configuration */
/* Implements DD-SWA-307 */
#define TLD7002_DC_UPDATE_8_BIT_LINEAR_CONF		 1 						/**< use linear 8 bit data configuration of DC_UPDATE */
#define TLD7002_DC_UPDATE_8_BIT_NON_LINEAR_CONF	 2						/**< use non-linear 8 bit data configuration of DC_UPDATE (standard) */

#define TLD7002_DC_UPDATE_8_BIT_CONF			TLD7002_DC_UPDATE_8_BIT_NON_LINEAR_CONF

/** Definition for the TLD7002 channel numbers */
/* Implements DD-SWA-308 */
#define TLD7002_CH0								 0U						/**< TLD7002 channel 0 */
#define TLD7002_CH1								 1U						/**< TLD7002 channel 1 */
#define TLD7002_CH2								 2U						/**< TLD7002 channel 2 */
#define TLD7002_CH3								 3U						/**< TLD7002 channel 3 */
#define TLD7002_CH4								 4U						/**< TLD7002 channel 4 */
#define TLD7002_CH5								 5U						/**< TLD7002 channel 5 */
#define TLD7002_CH6								 6U						/**< TLD7002 channel 6 */
#define TLD7002_CH7								 7U						/**< TLD7002 channel 7 */
#define TLD7002_CH8								 8U						/**< TLD7002 channel 8 */
#define TLD7002_CH9								 9U						/**< TLD7002 channel 9 */
#define TLD7002_CH10							 10U					/**< TLD7002 channel 10 */
#define TLD7002_CH11							 11U					/**< TLD7002 channel 11 */
#define TLD7002_CH12							 12U					/**< TLD7002 channel 12 */
#define TLD7002_CH13							 13U					/**< TLD7002 channel 13 */
#define TLD7002_CH14							 14U					/**< TLD7002 channel 14 */
#define TLD7002_CH15							 15U					/**< TLD7002 channel 15 */

/** Definition for result of response frame validation */
/* Implements DD-SWA-309 */
#define TLD7002_FRAME_VAL_NO_ERROR 				 0U						/**< No error detected in response frame */
#define TLD7002_FRAME_VAL_UNDEFINED_ERROR 		 1U						/**< An undefined error occurred copying the response in the frame */
#define TLD7002_FRAME_VAL_COPY_FRAME_ERROR 		 2U						/**< An error occurred at copying the response in the frame */
#define TLD7002_FRAME_VAL_BROADCAST_ERROR 		 3U						/**< The answer of an broadcast message cannot be validated */
#define TLD7002_FRAME_VAL_CRC3_ERROR			 4U						/**< CRC3 error detected in response frame */
#define TLD7002_FRAME_VAL_RC_ERROR				 5U						/**< Rolling Counter error detected in response frame */
#define TLD7002_FRAME_VAL_CRC8_ERROR			 6U						/**< CRC8 error detected at data in response frame */

/******************************************************************************/
/*	Function pointer definition												  */
/******************************************************************************/
/** define function pointer for write UART over CAN data to transmit */
/* Implements DD-SWA-310 */
typedef void (*TLD7002_uart_ov_can_trx_t)(uint8 *txbuffer, uint32 len_write);
/** define function pointer for read UART over CAN received data */
/* Implements DD-SWA-311 */
typedef boolean (*TLD7002_uart_ov_can_rcv_t)(uint8 *txbuffer, uint32 len_read);
/** define function pointers for emptying the receive buffer (needs to be implemented, if required) */
/* Implements DD-SWA-312 */
typedef void (*TLD7002_uart_ov_can_empty_rcv_buff_t)(void);
/** define function pointers for sync break generation */
/* Implements DD-SWA-313 */
typedef void (*TLD7002_startsyncbreak_t)(void);
/* Implements DD-SWA-314 */
typedef void (*TLD7002_stopsyncbreak_t)(void);

/******************************************************************************/
/*	Multi-instance support definitions										  */
/******************************************************************************/
/* Implements DD-SWA-315 */
/** TLD7002_NetworkInstance_t
 *
 */
typedef struct
{
    uint8 curr_master_rc;														/*< store the master rolling counter */
    uint8 curr_slave_rc[TLD7002_NUM_DEVICES - 1];									/*< store the slave rolling counters
																				  * TLD7002_curr_slave_rc[0]	(TLD7002_FRAME_SLAVE_ADDRESS_1)				Store slave 1 rolling counter
																				  * TLD7002_curr_slave_rc[1]	(TLD7002_FRAME_SLAVE_ADDRESS_2)				Store slave 2 rolling counter
																				  * ...							...											...
																				  * TLD7002_curr_slave_rc[29] 	(TLD7002_FRAME_SLAVE_ADDRESS_30)			Store slave 30 rolling counter
																				  * TLD7002_curr_slave_rc[30] 	(TLD7002_FRAME_SLAVE_ADDRESS_31)			Store slave 31 rolling counter
																				  */
    TLD7002_uart_ov_can_trx_t trx_function;										/*< store function pointer for writing UART over CAN */
    TLD7002_uart_ov_can_rcv_t rcv_function;										/*< store function pointer for reading UART over CAN */
    TLD7002_uart_ov_can_empty_rcv_buff_t rcv_empty_buffer;						/*< store function pointer for emptying the UART receive buffer */
    TLD7002_startsyncbreak_t startsyncbreak_function;							/*< store function pointers for start sync break generation */
    TLD7002_stopsyncbreak_t stopsyncbreak_function;								/*< store function pointers for stop sync break generation */
} TLD7002_NetworkInstance_t;

/******************************************************************************/
/* Command preparation and validation function declarations                   */
/******************************************************************************/

void TLD7002_brdc_dc_sync_prep(TLD7002_NetworkInstance_t *inst, TLD7002_BRDC_DC_SYNC_FRAME_t *frm);
void TLD7002_brdc_dc_sync_fin(TLD7002_BRDC_DC_SYNC_FRAME_t *frm);
boolean TLD7002_dc_update_8bit_prep(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm, uint8 add);
boolean TLD7002_dc_update_8bit_dlc0_prep(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm, uint8 add);
void TLD7002_dc_update_8bit_fin(TLD7002_DC_UPDATE_8BIT_FRAME_t *frm);
void TLD7002_dc_update_8bit_dlc0_fin(TLD7002_DC_UPDATE_8BIT_FRAME_t *frm);
uint8 TLD7002_dc_update_8bit_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm);
uint8 TLD7002_dc_update_8bit_dlc0_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm);
boolean TLD7002_dc_update_14bit_prep(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_14BIT_FRAME_t *frm, uint8 add);
void TLD7002_dc_update_14bit_fin(TLD7002_DC_UPDATE_14BIT_FRAME_t *frm);
uint8 TLD7002_dc_update_14bit_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_14BIT_FRAME_t *frm);
boolean TLD7002_pm_change_prep(TLD7002_NetworkInstance_t *inst, TLD7002_PM_CHANGE_FRAME_t *frm, uint8 add);
void TLD7002_pm_change_fin(TLD7002_PM_CHANGE_FRAME_t *frm);
uint8 TLD7002_pm_change_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_PM_CHANGE_FRAME_t *frm);
boolean TLD7002_read_ost_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_OST_FRAME_t *frm, uint8 add);
void TLD7002_read_ost_fin(TLD7002_READ_OST_FRAME_t *frm);
uint8 TLD7002_read_ost_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_OST_FRAME_t *frm);
boolean TLD7002_hwcr_prep(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm, uint8 add);
void TLD7002_hwcr_fin(TLD7002_HWCR_FRAME_t *frm);
uint8 TLD7002_hwcr_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm);

boolean TLD7002_write_reg_dlc1_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC1_FRAME_t *frm, uint8 add);
void TLD7002_write_reg_dlc1_fin(TLD7002_WRITE_REG_DLC1_FRAME_t *frm);
uint8 TLD7002_write_reg_dlc1_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC1_FRAME_t *frm);
boolean TLD7002_write_reg_dlc2_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC2_FRAME_t *frm, uint8 add);
void TLD7002_write_reg_dlc2_fin(TLD7002_WRITE_REG_DLC2_FRAME_t *frm);
uint8 TLD7002_write_reg_dlc2_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC2_FRAME_t *frm);
boolean TLD7002_write_reg_dlc3_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC3_FRAME_t *frm, uint8 add);
void TLD7002_write_reg_dlc3_fin(TLD7002_WRITE_REG_DLC3_FRAME_t *frm);
uint8 TLD7002_write_reg_dlc3_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC3_FRAME_t *frm);
boolean TLD7002_write_reg_dlc4_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC4_FRAME_t *frm, uint8 add);
void TLD7002_write_reg_dlc4_fin(TLD7002_WRITE_REG_DLC4_FRAME_t *frm);
uint8 TLD7002_write_reg_dlc4_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC4_FRAME_t *frm);
boolean TLD7002_write_reg_dlc5_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC5_FRAME_t *frm, uint8 add);
void TLD7002_write_reg_dlc5_fin(TLD7002_WRITE_REG_DLC5_FRAME_t *frm);
uint8 TLD7002_write_reg_dlc5_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC5_FRAME_t *frm);
boolean TLD7002_write_reg_dlc6_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC6_FRAME_t *frm, uint8 add);
void TLD7002_write_reg_dlc6_fin(TLD7002_WRITE_REG_DLC6_FRAME_t *frm);
uint8 TLD7002_write_reg_dlc6_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC6_FRAME_t *frm);
boolean TLD7002_write_reg_dlc7_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC7_FRAME_t *frm, uint8 add);
void TLD7002_write_reg_dlc7_fin(TLD7002_WRITE_REG_DLC7_FRAME_t *frm);
uint8 TLD7002_write_reg_dlc7_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC7_FRAME_t *frm);

boolean TLD7002_read_reg_dlc1_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC1_FRAME_t *frm, uint8 add);
void TLD7002_read_reg_dlc1_fin(TLD7002_READ_REG_DLC1_FRAME_t *frm);
uint8 TLD7002_read_reg_dlc1_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC1_FRAME_t *frm);
boolean TLD7002_read_reg_dlc2_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC2_FRAME_t *frm, uint8 add);
void TLD7002_read_reg_dlc2_fin(TLD7002_READ_REG_DLC2_FRAME_t *frm);
uint8 TLD7002_read_reg_dlc2_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC2_FRAME_t *frm);
boolean TLD7002_read_reg_dlc3_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC3_FRAME_t *frm, uint8 add);
void TLD7002_read_reg_dlc3_fin(TLD7002_READ_REG_DLC3_FRAME_t *frm);
uint8 TLD7002_read_reg_dlc3_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC3_FRAME_t *frm);
boolean TLD7002_read_reg_dlc4_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC4_FRAME_t *frm, uint8 add);
void TLD7002_read_reg_dlc4_fin(TLD7002_READ_REG_DLC4_FRAME_t *frm);
uint8 TLD7002_read_reg_dlc4_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC4_FRAME_t *frm);
boolean TLD7002_read_reg_dlc5_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC5_FRAME_t *frm, uint8 add);
void TLD7002_read_reg_dlc5_fin(TLD7002_READ_REG_DLC5_FRAME_t *frm);
uint8 TLD7002_read_reg_dlc5_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC5_FRAME_t *frm);
boolean TLD7002_read_reg_dlc6_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC6_FRAME_t *frm, uint8 add);
void TLD7002_read_reg_dlc6_fin(TLD7002_READ_REG_DLC6_FRAME_t *frm);
uint8 TLD7002_read_reg_dlc6_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC6_FRAME_t *frm);
boolean TLD7002_read_reg_dlc7_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC7_FRAME_t *frm, uint8 add);
void TLD7002_read_reg_dlc7_fin(TLD7002_READ_REG_DLC7_FRAME_t *frm);
uint8 TLD7002_read_reg_dlc7_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC7_FRAME_t *frm);


/******************************************************************************/
/* Auxiliary function declarations                                            */
/******************************************************************************/
void TLD7002_init_network(TLD7002_NetworkInstance_t *inst);
uint8 TLD7002_get_next_rc_val(uint8 mrc);
void TLD7002_calculate_crc3_master_request(TLD7002_FRAME_CRC_ADDRESS_t *byte_req_s_add, TLD7002_FRAME_MRC_DLC_FUN_t *byte_mrc_dlc_fun);
boolean TLD7002_calculate_crc3_slave_response(TLD7002_FRAME_OUTPUT_STATUS_BYTE_t *byte_ost, TLD7002_FRAME_ACK_BYTE_t *byte_ack);
uint8 TLD7002_calculate_crc8_general(uint8 *data_array, uint8 data_len);
uint8 TLD7002_calculate_crc8_leadbyte(uint8 *data_array, uint8 data_len, uint8 lead_byte);
void TLD7002_generate_master_request_header(TLD7002_FRAME_HEADER_t *header, uint8 *w_array);
void TLD7002_setChDc8BitToFrame(TLD7002_DC_UPDATE_8BIT_FRAME_t *updtfram, uint8 ch, uint8 dc_val);
void TLD7002_setChDc14BitToFrame(TLD7002_DC_UPDATE_14BIT_FRAME_t *updtfram, uint8 ch, uint16 dc_val);
uint8 TLD7002_calcChDc8BitValue(uint16 dc_perc);
uint16 TLD7002_calcChDc14BitValue(uint16 dc_perc);

#endif /* TLD7002_CONTROL_LAYER_H_ */
/**@}*/