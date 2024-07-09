/**
 *  @file TLD7002_ServiceLayer.h
 *  @author Infineon
 *  @date 17.06.2022
 *	@brief TLD7002 specific Device Driver implementation from Infineon Technologies AG.
 *	@note  This file includes the definitions for the TLD7002 service layer
 *
 ***********************************************************************************************************************
 *
 * Copyright (c) 2022, Infineon Technologies AG
 * All rights reserved.
 *
 **********************************************************************************************************************
 */

/**
 * @addtogroup TLD7002_SERVICE_LAYER
 * @{
 */

#ifndef TLD7002_SERVICE_LAYER_H_
#define TLD7002_SERVICE_LAYER_H_

/******************************************************************************/
/*	Includes																  */
/******************************************************************************/
#include "TLD7002_ControlLayer.h"

/******************************************************************************/
/* TLD7002 specific access function declarations 		 					  */
/******************************************************************************/
void TLD7002_TX_BRDC_DC_SYNC_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_BRDC_DC_SYNC_FRAME_t *frm);
boolean TLD7002_TX_DC_UPDATE_8BIT_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm, uint8 add, uint16 *dc_val);
boolean TLD7002_TX_DC_UPDATE_8BIT_DLC0_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm, uint8 add);
boolean TLD7002_TX_DC_UPDATE_14BIT_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_14BIT_FRAME_t *frm, uint8 add, uint16 *dc_val);
boolean TLD7002_TX_PM_CHANGE_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_PM_CHANGE_FRAME_t *frm, uint8 add, TLD7002_FRAME_POWER_MODE_CHANGE_t mode);
boolean TLD7002_TX_READ_OST_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_OST_FRAME_t *frm, uint8 add);
boolean TLD7002_TX_HWCR_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm, uint8 add, TLD7002_FRAME_HWCR_RESET_OUT_t reset_overload, TLD7002_FRAME_HWCR_RESET_OUT_t reset_openload, TLD7002_FRAME_HWCR_RESET_OUT_t reset_sls, TLD7002_FRAME_HWCR_RESET_STATUS_t reset_status);
boolean TLD7002_TX_HWCR_ALL_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm, uint8 add);
boolean TLD7002_TX_WRITE_REG_DLC1_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC1_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 data);
boolean TLD7002_TX_WRITE_REG_DLC2_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC2_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data);
boolean TLD7002_TX_WRITE_REG_DLC3_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC3_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data);
boolean TLD7002_TX_WRITE_REG_DLC4_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC4_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data);
boolean TLD7002_TX_WRITE_REG_DLC5_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC5_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data);
boolean TLD7002_TX_WRITE_REG_DLC6_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC6_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data);
boolean TLD7002_TX_WRITE_REG_DLC7_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC7_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data);
boolean TLD7002_TX_READ_REG_DLC1_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC1_FRAME_t *frm, uint8 add, uint8 regStartAdd);
boolean TLD7002_TX_READ_REG_DLC2_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC2_FRAME_t *frm, uint8 add, uint8 regStartAdd);
boolean TLD7002_TX_READ_REG_DLC3_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC3_FRAME_t *frm, uint8 add, uint8 regStartAdd);
boolean TLD7002_TX_READ_REG_DLC4_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC4_FRAME_t *frm, uint8 add, uint8 regStartAdd);
boolean TLD7002_TX_READ_REG_DLC5_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC5_FRAME_t *frm, uint8 add, uint8 regStartAdd);
boolean TLD7002_TX_READ_REG_DLC6_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC6_FRAME_t *frm, uint8 add, uint8 regStartAdd);
boolean TLD7002_TX_READ_REG_DLC7_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC7_FRAME_t *frm, uint8 add, uint8 regStartAdd);

uint8 TLD7002_RX_DC_UPDATE_8BIT_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm);
uint8 TLD7002_RX_DC_UPDATE_8BIT_DLC0_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm);
uint8 TLD7002_RX_DC_UPDATE_14BIT_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_14BIT_FRAME_t *frm);
uint8 TLD7002_RX_PM_CHANGE_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_PM_CHANGE_FRAME_t *frm);
uint8 TLD7002_RX_READ_OST_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_OST_FRAME_t *frm);
uint8 TLD7002_RX_HWCR_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm);
uint8 TLD7002_RX_WRITE_REG_DLC1_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC1_FRAME_t *frm);
uint8 TLD7002_RX_WRITE_REG_DLC2_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC2_FRAME_t *frm);
uint8 TLD7002_RX_WRITE_REG_DLC3_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC3_FRAME_t *frm);
uint8 TLD7002_RX_WRITE_REG_DLC4_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC4_FRAME_t *frm);
uint8 TLD7002_RX_WRITE_REG_DLC5_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC5_FRAME_t *frm);
uint8 TLD7002_RX_WRITE_REG_DLC6_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC6_FRAME_t *frm);
uint8 TLD7002_RX_WRITE_REG_DLC7_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC7_FRAME_t *frm);
uint8 TLD7002_RX_READ_REG_DLC1_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC1_FRAME_t *frm);
uint8 TLD7002_RX_READ_REG_DLC2_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC2_FRAME_t *frm);
uint8 TLD7002_RX_READ_REG_DLC3_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC3_FRAME_t *frm);
uint8 TLD7002_RX_READ_REG_DLC4_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC4_FRAME_t *frm);
uint8 TLD7002_RX_READ_REG_DLC5_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC5_FRAME_t *frm);
uint8 TLD7002_RX_READ_REG_DLC6_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC6_FRAME_t *frm);
uint8 TLD7002_RX_READ_REG_DLC7_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC7_FRAME_t *frm);

void TLD7002_InitNetworkInstance(TLD7002_NetworkInstance_t *inst);
void TLD7002_StartSyncBreak(TLD7002_NetworkInstance_t *inst);
void TLD7002_StopSyncBreak(TLD7002_NetworkInstance_t *inst);
void TLD7002_CopyTerminationToFrame(TLD7002_FRAME_TERMINATION_t *frame_termination, uint8 read_ost_byte, uint8 read_ack_byte);
uint8 TLD7002_ConvOutxStructToByte(TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t osb_outx);
TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t TLD7002_ConvOutxByteToStruct(uint8 osb_outx);

#endif /* TLD7002_SERVICE_LAYER_H_ */
/**@}*/