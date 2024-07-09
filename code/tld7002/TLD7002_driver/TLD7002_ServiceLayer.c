/**
 *  @file TLD7002_ServiceLayer.c
 *  @author Infineon
 *  @date 17.06.2022
 *	@brief TLD7002 specific Device Driver implementation from Infineon Technologies AG.
 *	@note  This file includes the implementation for the TLD7002 service layer.
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

/******************************************************************************/
/*	Includes																  */
/******************************************************************************/
#include "TLD7002_ServiceLayer.h"

/******************************************************************************/
/* TLD7002 specific access transmit function implementation	                  */
/******************************************************************************/

/** @brief Transmit sync for all devices (broad cast).
 *
 * Generation of DC_SYNC frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of that frame is to trigger a synchronous sampling event at
 * multiple slaves.This means, the duty cycle data from the shadow register is
 * transferred to the hardware control register synchronized to the start of
 * the next PWM period. An updated output channel completes the actual PWM pulse
 * before changing to the new duty cycle configuration to avoid glitches on the
 * output.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_BRDC_DC_SYNC_FRAME_t* Reference to DC_SYNC frame instance
 */
/* Implements DD-SWA-192 DD-IPVS-29, DD-IPVS-31 */
void TLD7002_TX_BRDC_DC_SYNC_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_BRDC_DC_SYNC_FRAME_t *frm)
{
    /* transmit sync for all devices */
    /* duty cycle sync frame generation */
    TLD7002_brdc_dc_sync_prep(inst, frm);														/*< frame preparation */
    TLD7002_brdc_dc_sync_fin(frm);																/*< Finalize frame before transferring */
    inst->trx_function(frm->write_array, TLD7002_LEN_BRDC_DC_SYNC_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
}


/** @brief Generate a DC-UPDATE frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of DC_UPDATE (8 Bit) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame update duty cycle is to refresh the
 * duty cycle for each channel within one master request.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint16* array of duty cycle value in percentage. Range: [0.00 %: 0 - 100.00%: 10000].
 * 															dc_val[0]: TLD7002 OUT0
 * 															dc_val[1]: TLD7002 OUT1
 * 															...
 * 															dc_val[15]: TLD7002 OUT15
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-193 DD-IPVS-18, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_DC_UPDATE_8BIT_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm, uint8 add, uint16 *dc_val)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_dc_update_8bit_prep(inst, frm, add))
    {
        for(uint8 cnt = 0; cnt < TLD7002_NUM_CH; cnt++)  										/*< go through all channels and set duty cycle */
        {
            TLD7002_setChDc8BitToFrame(frm, cnt, TLD7002_calcChDc8BitValue(*dc_val));			/*< calculate duty cycle value and set to calculated duty cycle to frame */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the duty cycle array is passed." */
            dc_val++;																			/*< jump to next array element */
        }
        TLD7002_dc_update_8bit_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_DC_UPDATE_8BIT_WRITE);					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a DC-UPDATE frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of DC_UPDATE (8 Bit) frame with data
 * length code 0 (DLC0).
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * This frame will have no impact on the TLD7002 configuration, because an
 * UPDATE_DC frame is generated without data. This frame can be used, for
 * example, to simply handle the watchdog, or read out the output status byte
 * and the ACK byte.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-195 DD-IPVS-26, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_DC_UPDATE_8BIT_DLC0_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm, uint8 add)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_dc_update_8bit_dlc0_prep(inst, frm, add))
    {
        TLD7002_dc_update_8bit_dlc0_fin(frm);													/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_DC_UPDATE_8BIT_DLC0_WRITE);			/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a DC-UPDATE frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of DC_UPDATE (14 Bit) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame update duty cycle is to refresh the
 * duty cycle for each channel within one master request.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_14BIT_FRAME_t* Reference to DC_UPDATE_14BIT frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint16* array of duty cycle value in percentage. Range: [0.00 %: 0 - 100.00%: 10000].
 * 															dc_val[0]: TLD7002 OUT0
 * 															dc_val[1]: TLD7002 OUT1
 * 															...
 * 															dc_val[15]: TLD7002 OUT15
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-194 DD-IPVS-22, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_DC_UPDATE_14BIT_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_14BIT_FRAME_t *frm, uint8 add, uint16 *dc_val)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_dc_update_14bit_prep(inst, frm, add))
    {
        for(uint8 cnt = 0; cnt < TLD7002_NUM_CH; cnt++)  										/*< go through all channels and set duty cycle */
        {
            TLD7002_setChDc14BitToFrame(frm, cnt, TLD7002_calcChDc14BitValue(*dc_val));			/*< calculate duty cycle value and set to calculated duty cycle to frame */
            dc_val++;																			/*< jump to next array element */
        }
        TLD7002_dc_update_14bit_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_DC_UPDATE_14BIT_WRITE);				/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a PM_CHANGE frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of PM_CHANGE frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame power mode change is to initiated a
 * transition to the commanded power state.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_PM_CHANGE_FRAME_t* Reference to PM_CHANGE frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] TLD7002_FRAME_POWER_MODE_CHANGE_t mode. 	0x0: TLD7002_FRAME_PM_INIT_MODE
 * 														0x1: TLD7002_FRAME_PM_RES1
 * 														0x2: TLD7002_FRAME_PM_FAIL_SAFE_MODE
 * 														0x3: TLD7002_FRAME_PM_OTP_MODE
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-199 DD-IPVS-33, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_PM_CHANGE_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_PM_CHANGE_FRAME_t *frm, uint8 add, TLD7002_FRAME_POWER_MODE_CHANGE_t mode)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_pm_change_prep(inst, frm, add))
    {
        frm->w_power_mode_change.PM_CHANGE = mode;												/*< set power mode from parameter */
        TLD7002_pm_change_fin(frm);																/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_PM_CHANGE_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a READ_OST frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of READ_OST frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of this frame is to retrieve the output power stage status within
 * one master request.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_OST_FRAME_t* Reference to READ_OST frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-201 DD-IPVS-34, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_READ_OST_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_OST_FRAME_t *frm, uint8 add)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_read_ost_prep(inst, frm, add))
    {
        TLD7002_read_ost_fin(frm);																/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_READ_OST_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a HWCR frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of HWCR frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the hardware control frame is to reset the diagnostic flags.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_HWCR_FRAME_t* Reference to HWCR frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] TLD7002_FRAME_HWCR_RESET_OUT_t reset_overload. reset OUT0 to OUT15 overload indication flags
 * @param[in] TLD7002_FRAME_HWCR_RESET_OUT_t reset_openload. reset OUT0 to OUT15 openload indication flags
 * @param[in] TLD7002_FRAME_HWCR_RESET_OUT_t reset_sls. reset OUT0 to OUT15 single LED short indication flags
 * @param[in] TLD7002_FRAME_HWCR_RESET_STATUS_t reset_status. reset outputput status byte indication flags
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-203 DD-IPVS-35, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_HWCR_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm, uint8 add, TLD7002_FRAME_HWCR_RESET_OUT_t reset_overload, TLD7002_FRAME_HWCR_RESET_OUT_t reset_openload, TLD7002_FRAME_HWCR_RESET_OUT_t reset_sls, TLD7002_FRAME_HWCR_RESET_STATUS_t reset_status)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_hwcr_prep(inst, frm, add))
    {
        frm->w_hardware_control.RESET_OVERLOAD = reset_overload;								/*< set reset of overload from parameter */
        frm->w_hardware_control.RESET_OPENLOAD = reset_openload;								/*< set reset of openload from parameter */
        frm->w_hardware_control.RESET_SLS = reset_sls;											/*< set reset of sls from parameter */
        frm->w_hardware_control.RESET_STATUS = reset_status;									/*< set reset of status from parameter */

        TLD7002_hwcr_fin(frm);																	/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_HWCR_WRITE);							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a HWCR frame for a selected address or broadcast for clearing all HWRC registers.
 *
 * Generation and triggering transmission of a HWCR frame with clearing
 * all HWRC registers.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the hardware control frame is to reset the diagnostic flags.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_HWCR_FRAME_t* Reference to HWCR frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-344 DD-IPVS-48, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_HWCR_ALL_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm, uint8 add)
{
    TLD7002_FRAME_HWCR_RESET_OUT_t reset_overload;
    TLD7002_FRAME_HWCR_RESET_OUT_t reset_openload;
    TLD7002_FRAME_HWCR_RESET_OUT_t reset_sls;
    TLD7002_FRAME_HWCR_RESET_STATUS_t reset_status;

    /* reset overload flags */
    reset_overload.RES_OUT0 = TRUE;
    reset_overload.RES_OUT1 = TRUE;
    reset_overload.RES_OUT2 = TRUE;
    reset_overload.RES_OUT3 = TRUE;
    reset_overload.RES_OUT4 = TRUE;
    reset_overload.RES_OUT5 = TRUE;
    reset_overload.RES_OUT6 = TRUE;
    reset_overload.RES_OUT7 = TRUE;
    reset_overload.RES_OUT8 = TRUE;
    reset_overload.RES_OUT9 = TRUE;
    reset_overload.RES_OUT10 = TRUE;
    reset_overload.RES_OUT11 = TRUE;
    reset_overload.RES_OUT12 = TRUE;
    reset_overload.RES_OUT13 = TRUE;
    reset_overload.RES_OUT14 = TRUE;
    reset_overload.RES_OUT15 = TRUE;

    /* reset open load flags */
    reset_openload.RES_OUT0 = TRUE;
    reset_openload.RES_OUT1 = TRUE;
    reset_openload.RES_OUT2 = TRUE;
    reset_openload.RES_OUT3 = TRUE;
    reset_openload.RES_OUT4 = TRUE;
    reset_openload.RES_OUT5 = TRUE;
    reset_openload.RES_OUT6 = TRUE;
    reset_openload.RES_OUT7 = TRUE;
    reset_openload.RES_OUT8 = TRUE;
    reset_openload.RES_OUT9 = TRUE;
    reset_openload.RES_OUT10 = TRUE;
    reset_openload.RES_OUT11 = TRUE;
    reset_openload.RES_OUT12 = TRUE;
    reset_openload.RES_OUT13 = TRUE;
    reset_openload.RES_OUT14 = TRUE;
    reset_openload.RES_OUT15 = TRUE;

    /* reset sls flags */
    reset_sls.RES_OUT0 = TRUE;
    reset_sls.RES_OUT1 = TRUE;
    reset_sls.RES_OUT2 = TRUE;
    reset_sls.RES_OUT3 = TRUE;
    reset_sls.RES_OUT4 = TRUE;
    reset_sls.RES_OUT5 = TRUE;
    reset_sls.RES_OUT6 = TRUE;
    reset_sls.RES_OUT7 = TRUE;
    reset_sls.RES_OUT8 = TRUE;
    reset_sls.RES_OUT9 = TRUE;
    reset_sls.RES_OUT10 = TRUE;
    reset_sls.RES_OUT11 = TRUE;
    reset_sls.RES_OUT12 = TRUE;
    reset_sls.RES_OUT13 = TRUE;
    reset_sls.RES_OUT14 = TRUE;
    reset_sls.RES_OUT15 = TRUE;

    /* reset status flags */
    reset_status.CUR_WRN = TRUE;
    reset_status.DC_WRN  = TRUE;
    reset_status.OSB_FAULT = TRUE;
    reset_status.GPINn_WRN = TRUE;
    reset_status.OUT_SHRT_WRN = TRUE;
    reset_status.OVLD  = TRUE;
    reset_status.VFWD_WRN = TRUE;
    reset_status.VLED_VS_UV = TRUE;

    return TLD7002_TX_HWCR_FRAME(inst, frm, add, reset_overload, reset_openload, reset_sls, reset_status);			/*< run TLD7002_TX_HWCR_FRAME() function and return if the generating and transmitting of frame was successful */
}


/** @brief Generate a WRITE_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of WRITE_REG (DLC1: 1 word / 2 bytes)
 * frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC1_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 * @param[in] uint16 data. Variable where the word to transmit is stored
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-205 DD-IPVS-36, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_WRITE_REG_DLC1_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC1_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 data)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_write_reg_dlc1_prep(inst, frm, add))
    {
        frm->w_write_reg.StartADDR = regStartAdd;												/*< start address */
        frm->w_write_reg.Data[0] = data;														/*< copy data */
        TLD7002_write_reg_dlc1_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_WRITE_REG_DLC1_WRITE);					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a WRITE_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of WRITE_REG (DLC2: 2 words / 4 bytes)
 * frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC2_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 * @param[in] uint16* data. Reference to the array, where the data to transmit is stored
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-206 DD-IPVS-36, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_WRITE_REG_DLC2_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC2_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_write_reg_dlc2_prep(inst, frm, add))
    {
        frm->w_write_reg.StartADDR = regStartAdd;												/*< start address */
        frm->w_write_reg.Data[0] = *data;														/*< copy data element 0 */
        data++;																					/*< next data element */
        frm->w_write_reg.Data[1] = *data;														/*< copy data element 1 */
        TLD7002_write_reg_dlc2_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_WRITE_REG_DLC2_WRITE);					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a WRITE_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of WRITE_REG (DLC3: 4 words / 8 bytes)
 * frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC3_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 * @param[in] uint16* data. Reference to the array, where the data to transmit is stored
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-207 DD-IPVS-36, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_WRITE_REG_DLC3_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC3_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_write_reg_dlc3_prep(inst, frm, add))
    {
        frm->w_write_reg.StartADDR = regStartAdd;												/*< start address */
        /* copy data from array into message - go through all 16 bit data elements */
        for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC3_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
        {
            frm->w_write_reg.Data[cnt] = *data;													/*< copy data element */
            data++;																				/*< next data element */
        }
        TLD7002_write_reg_dlc3_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_WRITE_REG_DLC3_WRITE);					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a WRITE_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of WRITE_REG (DLC4: 8 words /
 * 16 bytes) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC4_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 * @param[in] uint16* data. Reference to the array, where the data to transmit is stored
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-208 DD-IPVS-36, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_WRITE_REG_DLC4_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC4_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_write_reg_dlc4_prep(inst, frm, add))
    {
        frm->w_write_reg.StartADDR = regStartAdd;												/*< start address */
        /* copy data from array into message - go through all 16 bit data elements */
        for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC4_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
        {
            frm->w_write_reg.Data[cnt] = *data;													/*< copy data element */
            data++;																				/*< next data element */
        }
        TLD7002_write_reg_dlc4_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_WRITE_REG_DLC4_WRITE);					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a WRITE_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of WRITE_REG (DLC5: 12 words /
 * 24 bytes) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC5_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 * @param[in] uint16* data. Reference to the array, where the data to transmit is stored
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-209 DD-IPVS-36, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_WRITE_REG_DLC5_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC5_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_write_reg_dlc5_prep(inst, frm, add))
    {
        frm->w_write_reg.StartADDR = regStartAdd;												/*< start address */
        /* copy data from array into message - go through all 16 bit data elements */
        for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC5_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
        {
            frm->w_write_reg.Data[cnt] = *data;													/*< copy data element */
            data++;																				/*< next data element */
        }
        TLD7002_write_reg_dlc5_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_WRITE_REG_DLC5_WRITE);					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a WRITE_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of WRITE_REG (DLC6: 16 words /
 * 32 bytes) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC6_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 * @param[in] uint16* data. Reference to the array, where the data to transmit is stored
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-210 DD-IPVS-36, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_WRITE_REG_DLC6_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC6_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_write_reg_dlc6_prep(inst, frm, add))
    {
        frm->w_write_reg.StartADDR = regStartAdd;												/*< start address */
        /* copy data from array into message - go through all 16 bit data elements */
        for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC6_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
        {
            frm->w_write_reg.Data[cnt] = *data;													/*< copy data element */
            data++;																				/*< next data element */
        }
        TLD7002_write_reg_dlc6_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_WRITE_REG_DLC6_WRITE);					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a WRITE_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of WRITE_REG (DLC7: 32 words /
 * 64 bytes) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC7_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 * @param[in] uint16* data. Reference to the array, where the data to transmit is stored
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-211 DD-IPVS-36, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_WRITE_REG_DLC7_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC7_FRAME_t *frm, uint8 add, uint8 regStartAdd, uint16 *data)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_write_reg_dlc7_prep(inst, frm, add))
    {
        frm->w_write_reg.StartADDR = regStartAdd;												/*< start address */
        /* copy data from array into message - go through all 16 bit data elements */
        for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC7_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
        {
            frm->w_write_reg.Data[cnt] = *data;													/*< copy data element */
            data++;																				/*< next data element */
        }
        TLD7002_write_reg_dlc7_fin(frm);														/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_WRITE_REG_DLC7_WRITE);					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a REAG_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of REAG_REG (DLC1: 1 word / 2 bytes)
 * frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC1_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-219 DD-IPVS-37, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_READ_REG_DLC1_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC1_FRAME_t *frm, uint8 add, uint8 regStartAdd)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_read_reg_dlc1_prep(inst, frm, add))
    {
        frm->w_read_reg.StartADDR = regStartAdd;												/*< start address */
        TLD7002_read_reg_dlc1_fin(frm);															/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_READ_REG_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a REAG_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of REAG_REG (DLC2: 2words / 4 bytes)
 * frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC2_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-220 DD-IPVS-37, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_READ_REG_DLC2_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC2_FRAME_t *frm, uint8 add, uint8 regStartAdd)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_read_reg_dlc2_prep(inst, frm, add))
    {
        frm->w_read_reg.StartADDR = regStartAdd;												/*< start address */
        TLD7002_read_reg_dlc2_fin(frm);															/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_READ_REG_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a REAG_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of REAG_REG (DLC3: 4 words / 8 bytes)
 * frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC3_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-221 DD-IPVS-37, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_READ_REG_DLC3_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC3_FRAME_t *frm, uint8 add, uint8 regStartAdd)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_read_reg_dlc3_prep(inst, frm, add))
    {
        frm->w_read_reg.StartADDR = regStartAdd;												/*< start address */
        TLD7002_read_reg_dlc3_fin(frm);															/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_READ_REG_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a REAG_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of REAG_REG (DLC4: 8 words / 16 bytes)
 * frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC4_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-222 DD-IPVS-37, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_READ_REG_DLC4_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC4_FRAME_t *frm, uint8 add, uint8 regStartAdd)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_read_reg_dlc4_prep(inst, frm, add))
    {
        frm->w_read_reg.StartADDR = regStartAdd;												/*< start address */
        TLD7002_read_reg_dlc4_fin(frm);															/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_READ_REG_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a REAG_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of REAG_REG (DLC5: 12 words /
 * 24 bytes) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC5_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-223 DD-IPVS-37, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_READ_REG_DLC5_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC5_FRAME_t *frm, uint8 add, uint8 regStartAdd)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_read_reg_dlc5_prep(inst, frm, add))
    {
        frm->w_read_reg.StartADDR = regStartAdd;												/*< start address */
        TLD7002_read_reg_dlc5_fin(frm);															/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_READ_REG_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a REAG_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of REAG_REG (DLC6: 16 words /
 * 32 bytes) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC6_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-224  DD-IPVS-37, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_READ_REG_DLC6_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC6_FRAME_t *frm, uint8 add, uint8 regStartAdd)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_read_reg_dlc6_prep(inst, frm, add))
    {
        frm->w_read_reg.StartADDR = regStartAdd;												/*< start address */
        TLD7002_read_reg_dlc6_fin(frm);															/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_READ_REG_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/** @brief Generate a REAG_REG frame for a selected address or broadcast.
 *
 * Generation and triggering transmission of REAG_REG (DLC7: 32 words /
 * 64 bytes) frame.
 * In this function the frame provided in the frame instance (second parameter)
 * is prepared by generating the header as well as by adding the payload (if
 * applicable) and finalized by generating checksums (if applicable). Afterwards
 * the frame is transmitted via the configured transmit function.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC7_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 slave address [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 * @param[in] uint8 regStartAdd. Registers accessible via HSLI (from register description)
 *
 * @return boolean generation of a frame [TRUE: Generation and transmission of transmit frame was successful; FALSE: Generation and transmission of transmit frame was failed]
 */
/* Implements DD-SWA-225  DD-IPVS-37, DD-IPVS-31, DD-IPVS-32 */
boolean TLD7002_TX_READ_REG_DLC7_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC7_FRAME_t *frm, uint8 add, uint8 regStartAdd)
{
    /* if frame preparation is successful, insert data and transfer frame */
    if(TLD7002_read_reg_dlc7_prep(inst, frm, add))
    {
        frm->w_read_reg.StartADDR = regStartAdd;												/*< start address */
        TLD7002_read_reg_dlc7_fin(frm);															/*< Finalize frame before transferring */
        inst->trx_function(frm->write_array, TLD7002_LEN_READ_REG_WRITE);						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the transmit function is configured." */
        return TRUE;																			/*< generating and transmitting of frame successful */
    }
    return FALSE;																				/*< generating and transmitting of frame not successful */
}


/******************************************************************************/
/* TLD7002 specific access receive function implementation	                  */
/******************************************************************************/

/** @brief Readout DC-UPDATE frame answer.
 *
 * Triggering receive and perform first validation of DC_UPDATE (8 Bit) frame
 * answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * Afterwards, the return value of the function can be evaluated.
 * The purpose of the master request frame update duty cycle is to refresh the
 * duty cycle for each channel within one master request.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-196  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_DC_UPDATE_8BIT_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;												/*< initially an undefined error is set as response */
    /*< message was sent as broadcast message */
    if(frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  			/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer is passed." */
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_DC_UPDATE_8BIT_READ))  						/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_pwm_dc_update.frame_termination),
                                           frm->read_array[TLD7002_POS_DC_UPDATE_8BIT_OST], frm->read_array[TLD7002_POS_DC_UPDATE_8BIT_ACK]);
            ret_resp = TLD7002_dc_update_8bit_val_resp(inst, frm);										/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;											/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout DC-UPDATE frame answer.
 *
 * Triggering receive and perform first validation of DC_UPDATE DLC 0 (8 Bit)
 * frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame update duty cycle is to refresh the
 * duty cycle for each channel within one master request.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-197  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_DC_UPDATE_8BIT_DLC0_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm)
{
    return TLD7002_RX_DC_UPDATE_8BIT_FRAME(inst, frm);													/*< call dc-update 8 bit specific function */
}

/** @brief Readout DC-UPDATE frame answer.
 *
 * Triggering receive and perform first validation of DC_UPDATE (14 Bit) frame
 * answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame update duty cycle is to refresh the
 * duty cycle for each channel within one master request.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_14BIT_FRAME_t* Reference to DC_UPDATE_14BIT frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-198  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_DC_UPDATE_14BIT_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_14BIT_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;												/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_DC_UPDATE_14BIT_READ))  						/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_pwm_dc_update.frame_termination),
                                           frm->read_array[TLD7002_POS_DC_UPDATE_14BIT_OST], frm->read_array[TLD7002_POS_DC_UPDATE_14BIT_ACK]);
            ret_resp = TLD7002_dc_update_14bit_val_resp(inst, frm);										/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;											/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout PM_CHANGE frame answer.
 *
 * Triggering receive and perform first validation of PM_CHANGE frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame power mode change is to initiated a
 * transition to the commanded power state.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_PM_CHANGE_FRAME_t* Reference to PM_CHANGE frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-200  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_PM_CHANGE_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_PM_CHANGE_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;												/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_power_mode_change.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_PM_CHANGE_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_power_mode_change.frame_termination),
                                           frm->read_array[TLD7002_POS_PM_CHANGE_OST], frm->read_array[TLD7002_POS_PM_CHANGE_ACK]);
            ret_resp = TLD7002_pm_change_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;											/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout READ_OST frame answer.
 *
 * Triggering receive and perform first validation of READ_OST frame answer. 
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received 
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of this frame is to retrieve the output power stage status within
 * one master request.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_OST_FRAME_t* Reference to READ_OST frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-202  DD-IPVS-39, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_READ_OST_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_OST_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;												/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_read_output_status.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_READ_OST_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_read_output_status.frame_termination),
                                           frm->read_array[TLD7002_POS_READ_OST_OST], frm->read_array[TLD7002_POS_READ_OST_ACK]);
            /* copy output status bytes from frame */
            frm->r_read_output_status.OSB_OUT0 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT0]);
            frm->r_read_output_status.OSB_OUT1 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT1]);
            frm->r_read_output_status.OSB_OUT2 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT2]);
            frm->r_read_output_status.OSB_OUT3 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT3]);
            frm->r_read_output_status.OSB_OUT4 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT4]);
            frm->r_read_output_status.OSB_OUT5 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT5]);
            frm->r_read_output_status.OSB_OUT6 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT6]);
            frm->r_read_output_status.OSB_OUT7 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT7]);
            frm->r_read_output_status.OSB_OUT8 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT8]);
            frm->r_read_output_status.OSB_OUT9 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT9]);
            frm->r_read_output_status.OSB_OUT10 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT10]);
            frm->r_read_output_status.OSB_OUT11 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT11]);
            frm->r_read_output_status.OSB_OUT12 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT12]);
            frm->r_read_output_status.OSB_OUT13 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT13]);
            frm->r_read_output_status.OSB_OUT14 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT14]);
            frm->r_read_output_status.OSB_OUT15 = TLD7002_ConvOutxByteToStruct(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT15]);
            frm->r_read_output_status.SAFETY_BYTE = frm->read_array[TLD7002_POS_READ_OST_SAFETY_BYTE];
            ret_resp = TLD7002_read_ost_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;											/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout HWCR frame answer. 
 *
 * Triggering receive and perform first validation of HWCR frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received 
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the hardware control frame is to reset the diagnostic flags.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_HWCR_FRAME_t* Reference to HWCR frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-204  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_HWCR_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;												/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_hardware_control.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_HWCR_READ))  									/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_hardware_control.frame_termination),
                                           frm->read_array[TLD7002_POS_HWCR_OST], frm->read_array[TLD7002_POS_HWCR_ACK]);
            ret_resp = TLD7002_hwcr_val_resp(inst, frm);													/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;											/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout WRITE_REG frame answer.
 *
 * Triggering receive and perform first validation of WRITE_REG
 * (DLC1: 1 word / 2 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC1_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-212  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_WRITE_REG_DLC1_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC1_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;												/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_WRITE_REG_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_write_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_WRITE_REG_OST], frm->read_array[TLD7002_POS_WRITE_REG_ACK]);
            ret_resp = TLD7002_write_reg_dlc1_val_resp(inst, frm);										/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;											/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout WRITE_REG frame answer.
 *
 * Triggering receive and perform first validation of WRITE_REG
 * (DLC2: 2 words / 4 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC2_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-213  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_WRITE_REG_DLC2_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC2_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;												/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_WRITE_REG_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_write_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_WRITE_REG_OST], frm->read_array[TLD7002_POS_WRITE_REG_ACK]);
            ret_resp = TLD7002_write_reg_dlc2_val_resp(inst, frm);										/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;											/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout WRITE_REG frame answer.
 *
 * Triggering receive and perform first validation of WRITE_REG
 * (DLC3: 4 words / 8 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC3_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-214  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_WRITE_REG_DLC3_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC3_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;														/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_WRITE_REG_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_write_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_WRITE_REG_OST], frm->read_array[TLD7002_POS_WRITE_REG_ACK]);
            ret_resp = TLD7002_write_reg_dlc3_val_resp(inst, frm);											/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;													/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout WRITE_REG frame answer.
 *
 * Triggering receive and perform first validation of WRITE_REG
 * (DLC4: 8 words / 16 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC4_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-215  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_WRITE_REG_DLC4_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC4_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;														/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_WRITE_REG_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_write_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_WRITE_REG_OST], frm->read_array[TLD7002_POS_WRITE_REG_ACK]);
            ret_resp = TLD7002_write_reg_dlc4_val_resp(inst, frm);											/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;													/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout WRITE_REG frame answer.
 *
 * Triggering receive and perform first validation of WRITE_REG
 * (DLC5: 12 words / 24 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC5_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-216  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_WRITE_REG_DLC5_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC5_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;														/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_WRITE_REG_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_write_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_WRITE_REG_OST], frm->read_array[TLD7002_POS_WRITE_REG_ACK]);
            ret_resp = TLD7002_write_reg_dlc5_val_resp(inst, frm);											/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;													/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout WRITE_REG frame answer.
 *
 * Triggering receive and perform first validation of WRITE_REG
 * (DLC6: 16 words / 32 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC6_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-217  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_WRITE_REG_DLC6_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC6_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;														/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_WRITE_REG_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_write_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_WRITE_REG_OST], frm->read_array[TLD7002_POS_WRITE_REG_ACK]);
            ret_resp = TLD7002_write_reg_dlc6_val_resp(inst, frm);											/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;													/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout WRITE_REG frame answer.
 *
 * Triggering receive and perform first validation of WRITE_REG
 * (DLC7: 32 words / 64 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame write register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC7_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-218  DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_WRITE_REG_DLC7_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC7_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;														/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }

    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_WRITE_REG_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_write_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_WRITE_REG_OST], frm->read_array[TLD7002_POS_WRITE_REG_ACK]);
            ret_resp = TLD7002_write_reg_dlc7_val_resp(inst, frm);											/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;													/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout READ_REG frame answer.
 *
 * Triggering receive and perform first validation of REAG_REG
 * (DLC1: 1 word / 2 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC1_FRAME_t* Reference to READ_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-226  DD-IPVS-40, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_READ_REG_DLC1_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC1_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;															/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_READ_REG_DLC1_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_read_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_READ_REG_DLC1_OST], frm->read_array[TLD7002_POS_READ_REG_DLC1_ACK]);
            /* copy data from frame */
            frm->r_read_reg.Data[0] = frm->read_array[TLD7002_POS_READ_REG_DATA0_LB];
            frm->r_read_reg.Data[0] |= ((uint16)(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]) << 8U);
            frm->r_read_reg.SAFETY_BYTE = frm->read_array[TLD7002_POS_READ_REG_DLC1_SAFETY_BYTE];
            ret_resp = TLD7002_read_reg_dlc1_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;														/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout READ_REG frame answer.
 *
 * Triggering receive and perform first validation of REAG_REG
 * (DLC2: 2 words / 4 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC2_FRAME_t* Reference to READ_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-227  DD-IPVS-40, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_READ_REG_DLC2_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC2_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;															/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_READ_REG_DLC2_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_read_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_READ_REG_DLC2_OST], frm->read_array[TLD7002_POS_READ_REG_DLC2_ACK]);
            /* copy data from frame */
            frm->r_read_reg.Data[0] = frm->read_array[TLD7002_POS_READ_REG_DATA0_LB];
            frm->r_read_reg.Data[0] |= ((uint16)(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]) << 8U);
            frm->r_read_reg.Data[1] = frm->read_array[TLD7002_POS_READ_REG_DATA1_LB];
            frm->r_read_reg.Data[1] |= ((uint16)(frm->read_array[TLD7002_POS_READ_REG_DATA1_HB]) << 8U);
            frm->r_read_reg.SAFETY_BYTE = frm->read_array[TLD7002_POS_READ_REG_DLC2_SAFETY_BYTE];
            ret_resp = TLD7002_read_reg_dlc2_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;														/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout READ_REG frame answer.
 *
 * Triggering receive and perform first validation of REAG_REG
 * (DLC3: 4 words / 8 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC3_FRAME_t* Reference to READ_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-228  DD-IPVS-40, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_READ_REG_DLC3_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC3_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;															/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_READ_REG_DLC3_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_read_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_READ_REG_DLC3_OST], frm->read_array[TLD7002_POS_READ_REG_DLC3_ACK]);
            /* copy data from frame */
            for(uint8 cmd_data_in = 0; cmd_data_in < TLD7002_POS_READ_REG_DLC3_SAFETY_BYTE / 2U; cmd_data_in++)
            {
                frm->r_read_reg.Data[cmd_data_in] = frm->read_array[2 * cmd_data_in + 1];						/*< low byte */
                frm->r_read_reg.Data[cmd_data_in] |= ((uint16)(frm->read_array[2 * cmd_data_in]) << 8U);		/*< high byte */
            }
            frm->r_read_reg.SAFETY_BYTE = frm->read_array[TLD7002_POS_READ_REG_DLC3_SAFETY_BYTE];
            ret_resp = TLD7002_read_reg_dlc3_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;														/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout READ_REG frame answer.
 *
 * Triggering receive and perform first validation of REAG_REG
 * (DLC4: 8 words / 16 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC4_FRAME_t* Reference to READ_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-229  DD-IPVS-40, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_READ_REG_DLC4_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC4_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;															/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_READ_REG_DLC4_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_read_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_READ_REG_DLC4_OST], frm->read_array[TLD7002_POS_READ_REG_DLC4_ACK]);
            /* copy data from frame */
            for(uint8 cmd_data_in = 0; cmd_data_in < TLD7002_POS_READ_REG_DLC4_SAFETY_BYTE / 2U; cmd_data_in++)
            {
                frm->r_read_reg.Data[cmd_data_in] = frm->read_array[2 * cmd_data_in + 1];						/*< low byte */
                frm->r_read_reg.Data[cmd_data_in] |= ((uint16)(frm->read_array[2 * cmd_data_in]) << 8U);		/*< high byte */
            }
            frm->r_read_reg.SAFETY_BYTE = frm->read_array[TLD7002_POS_READ_REG_DLC4_SAFETY_BYTE];
            ret_resp = TLD7002_read_reg_dlc4_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;														/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout READ_REG frame answer.
 *
 * Triggering receive and perform first validation of REAG_REG
 * (DLC5: 12 words / 24 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC5_FRAME_t* Reference to READ_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-230  DD-IPVS-40, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_READ_REG_DLC5_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC5_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;															/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_READ_REG_DLC5_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_read_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_READ_REG_DLC5_OST], frm->read_array[TLD7002_POS_READ_REG_DLC5_ACK]);
            /* copy data from frame */
            for(uint8 cmd_data_in = 0; cmd_data_in < TLD7002_POS_READ_REG_DLC5_SAFETY_BYTE / 2U; cmd_data_in++)
            {
                frm->r_read_reg.Data[cmd_data_in] = frm->read_array[2 * cmd_data_in + 1];						/*< low byte */
                frm->r_read_reg.Data[cmd_data_in] |= ((uint16)(frm->read_array[2 * cmd_data_in]) << 8U);		/*< high byte */
            }
            frm->r_read_reg.SAFETY_BYTE = frm->read_array[TLD7002_POS_READ_REG_DLC5_SAFETY_BYTE];
            ret_resp = TLD7002_read_reg_dlc5_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;														/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout READ_REG frame answer.
 *
 * Triggering receive and perform first validation of REAG_REG
 * (DLC6: 16 words / 32 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC6_FRAME_t* Reference to READ_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-231  DD-IPVS-40, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_READ_REG_DLC6_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC6_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;															/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_READ_REG_DLC6_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_read_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_READ_REG_DLC6_OST], frm->read_array[TLD7002_POS_READ_REG_DLC6_ACK]);
            /* copy data from frame */
            for(uint8 cmd_data_in = 0; cmd_data_in < TLD7002_POS_READ_REG_DLC6_SAFETY_BYTE / 2U; cmd_data_in++)
            {
                frm->r_read_reg.Data[cmd_data_in] = frm->read_array[2 * cmd_data_in + 1];						/*< low byte */
                frm->r_read_reg.Data[cmd_data_in] |= ((uint16)(frm->read_array[2 * cmd_data_in]) << 8U);		/*< high byte */
            }
            frm->r_read_reg.SAFETY_BYTE = frm->read_array[TLD7002_POS_READ_REG_DLC6_SAFETY_BYTE];
            ret_resp = TLD7002_read_reg_dlc6_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;														/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief Readout READ_REG frame answer.
 *
 * Triggering receive and perform first validation of REAG_REG
 * (DLC7: 32 words / 64 bytes) frame answer.
 * This function needs to be called after the corresponding TX function, when
 * the answer from TLD7002 is already in the UART receive buffer.
 * For this function, the same frame instance (second parameter) used for the
 * transmit function must be passed by reference. At first in this function the
 * frame is received via the configured UART receive function.
 * The received data is stored into the frame instance. Here also the received
 * payload is handed (if applicable) and some basic frame validations are done.
 * The purpose of the master request frame read register is to access the
 * devices 16-bit registers.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC7_FRAME_t* Reference to READ_REG frame instance
 *
 * @return uint8 result of response frame validation
 */
/* Implements DD-SWA-232  DD-IPVS-40, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
uint8 TLD7002_RX_READ_REG_DLC7_FRAME(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC7_FRAME_t *frm)
{
    uint8 ret_resp = TLD7002_FRAME_VAL_UNDEFINED_ERROR;															/*< initially an undefined error is set as response */

    /*< message was sent as broadcast message */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        ret_resp = TLD7002_FRAME_VAL_BROADCAST_ERROR;
        inst->rcv_empty_buffer();
    }
    else  		/*< message was not sent as broadcast message -> data is expected*/
    {
        if(inst->rcv_function(frm->read_array, TLD7002_LEN_READ_REG_DLC7_READ))  								/*< copy received data in frame */
        {
            /* copy standard answer from frame */
            TLD7002_CopyTerminationToFrame(&(frm->r_read_reg.frame_termination),
                                           frm->read_array[TLD7002_POS_READ_REG_DLC7_OST], frm->read_array[TLD7002_POS_READ_REG_DLC7_ACK]);
            /* copy data from frame */
            for(uint8 cmd_data_in = 0; cmd_data_in < TLD7002_POS_READ_REG_DLC7_SAFETY_BYTE / 2U; cmd_data_in++)
            {
                frm->r_read_reg.Data[cmd_data_in] = frm->read_array[2 * cmd_data_in + 1];						/*< low byte */
                frm->r_read_reg.Data[cmd_data_in] |= ((uint16)(frm->read_array[2 * cmd_data_in]) << 8U);		/*< high byte */
            }
            frm->r_read_reg.SAFETY_BYTE = frm->read_array[TLD7002_POS_READ_REG_DLC7_SAFETY_BYTE];
            ret_resp = TLD7002_read_reg_dlc7_val_resp(inst, frm);												/*< validate answer frame */
        }
        else
        {
            ret_resp = TLD7002_FRAME_VAL_COPY_FRAME_ERROR;														/*< error at copying received data in frame */
        }
    }
    return ret_resp;
}


/** @brief TLD7002 device driver initialization function.
 *
 * This function needs to be called at first, before using any other function of
 * the Device Driver. Inside this function the init function of the control
 * layer is executed in order to initialize the network instance.
 *
 * @param[in] TLD7002_NetworkInstance_t* pointer to instance of TLD7002 network
 */
/* Implements DD-SWA-233  DD-IPVS-19, DD-IPVS-38, DD-IPVS-41, DD-IPVS-42, DD-IPVS-43, DD-IPVS-44, DD-IPVS-45 */
void TLD7002_InitNetworkInstance(TLD7002_NetworkInstance_t *inst)
{
    TLD7002_init_network(inst);													/* init device driver */
}


/** @brief Run instance specific start sync break function.
 *
 * This functions starts to perform the SYNC_BREAK signal. The timing
 * constraints has to be considered externally.
 * Inside this function the instance specific start sync break function is
 * executed.
 *
 * @param[in] TLD7002_NetworkInstance_t* pointer to instance of TLD7002 network
 */
/* Implements DD-SWA-234 */
void TLD7002_StartSyncBreak(TLD7002_NetworkInstance_t *inst)
{
    inst->startsyncbreak_function();											/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct start sync break function pointer is configured." */
}


/** @brief Run instance specific stop sync break function.
 *
 * This functions stops to perform the SYNC_BREAK signal. The timing constraints
 * has to be considered externally.
 * Inside this function the instance specific stop sync break function is
 * executed.
 *
 * @param[in] TLD7002_NetworkInstance_t* pointer to instance of TLD7002 network
 */
/* Implements DD-SWA-235 */
void TLD7002_StopSyncBreak(TLD7002_NetworkInstance_t *inst)
{
    /* check pointer to network instance */
    inst->stopsyncbreak_function();												/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct stop sync break function pointer is configured." */
}


/** @brief Copy the received termination (standard answer consisting of OST and ACK byte) to a frame.
 *
 * This functions copies the received frame termination bytes
 * via UART consisting of  the OST (output status) byte (second parameter) and
 * ACK byte (third parameter) into a given frame structure (first parameter).
 * This means, the individual fields are extracted and stored to the struct
 * elements representation.
 *
 * @param[in] TLD7002_FRAME_TERMINATION_t* frame_termination. Frame termination received at every frame except the broadcast frame
 * @param[in] uint8 read_ost_byte. Received OST (output status) byte
 * @param[in] uint8 read_ack_byte. Received ACK byte
 */
/* Implements DD-SWA-236 */
void TLD7002_CopyTerminationToFrame(TLD7002_FRAME_TERMINATION_t *frame_termination, uint8 read_ost_byte, uint8 read_ack_byte)
{
    frame_termination->OST.OSB_FAULT = 		((read_ost_byte & TLD7002_OUTPUT_STATUS_BYTE_FAULT_MSK) > 0) ? TRUE : FALSE;
    frame_termination->OST.OVLD = 			((read_ost_byte & TLD7002_OUTPUT_STATUS_BYTE_OVLD_MSK) > 0) ? TRUE : FALSE;
    frame_termination->OST.VFWD_WRN = 		((read_ost_byte & TLD7002_OUTPUT_STATUS_BYTE_VFWD_WRN_MSK) > 0) ? TRUE : FALSE;
    frame_termination->OST.CUR_WRN = 		((read_ost_byte & TLD7002_OUTPUT_STATUS_BYTE_CUR_WRN_MSK) > 0) ? TRUE : FALSE;
    frame_termination->OST.DC_WRN = 		((read_ost_byte & TLD7002_OUTPUT_STATUS_BYTE_DC_WRN_MSK) > 0) ? TRUE : FALSE;
    frame_termination->OST.GPINn_WRN = 		((read_ost_byte & TLD7002_OUTPUT_STATUS_BYTE_GPINn_WRN_MSK) > 0) ? TRUE : FALSE;
    frame_termination->OST.OUT_SHRT_WRN = 	((read_ost_byte & TLD7002_OUTPUT_STATUS_BYTE_OUT_SHRT_WRN_MSK) > 0) ? TRUE : FALSE;
    frame_termination->OST.VLED_VS_UV = 	((read_ost_byte & TLD7002_OUTPUT_STATUS_BYTE_VLED_VS_UV_MSK) > 0) ? TRUE : FALSE;

    frame_termination->ACK.TER = 			((read_ack_byte & TLD7002_ACK_BYTE_TER_MSK) > 0) ? TRUE : FALSE;
    frame_termination->ACK.RC = 			(read_ack_byte & TLD7002_ACK_BYTE_RC_MSK) >> TLD7002_ACK_BYTE_RC_POS;
    frame_termination->ACK.MODE = 			(read_ack_byte & TLD7002_ACK_BYTE_MODE_MSK) >> TLD7002_ACK_BYTE_MODE_POS;
    frame_termination->ACK.CRC = 			(read_ack_byte & TLD7002_ACK_BYTE_CRC_MSK) >> TLD7002_ACK_BYTE_CRC_POS;
    frame_termination->ACK.CRC = 			(read_ack_byte & TLD7002_ACK_BYTE_CRC_MSK) >> TLD7002_ACK_BYTE_CRC_POS;
}


/** @brief Convert a output status byte element of a specific OUTX to uint8 value of a READ_OST frame.
 *
 * This functions converts a output status byte struct element of a specific
 * OUTX (first parameter) to it's uint8 representation. Here the individual
 * fields are extracted from the output status byte element and written to the
 * uint8 representation.
 * The uint8 representation is usually used in the read array of a READ_OST
 * frame.
 * Currently, this function is not called within the device driver, but it
 * can be used for checking a received output status byte element in uint8 representation of a READ_OST frame against a configureable output status byte struct element of a specific OUTX.
 *
 * @param[in] TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t osb_outx. OUTX output status byte element of READ_OST frame as struct
 *
 * @return uint8 OUTX output status byte of READ_OST frame as uint8 representation
 */
/* Implements DD-SWA-237 */
uint8 TLD7002_ConvOutxStructToByte(TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t osb_outx)
{
    uint8 ret_byte = 0;
    ret_byte |= (osb_outx.OUT_STAT == TRUE) ? TLD7002_OUTPUT_STATUS_BYTE_OUT_OUT_STAT_MSK : 0x0;
    ret_byte |= (osb_outx.VFWD_WRN == TRUE) ? TLD7002_OUTPUT_STATUS_BYTE_OUT_VFWD_WRN_MSK : 0x0;
    ret_byte |= (osb_outx.CUR_WRN == TRUE) ? TLD7002_OUTPUT_STATUS_BYTE_OUT_CUR_WRN_MSK : 0x0;
    ret_byte |= (osb_outx.DC_WRN == TRUE) ? TLD7002_OUTPUT_STATUS_BYTE_OUT_DC_WRN_MSK : 0x0;
    ret_byte |= (osb_outx.OUT_SHORT_WRN == TRUE) ? TLD7002_OUTPUT_STATUS_BYTE_OUT_OUT_SHORT_WRN_MSK : 0x0;
    ret_byte |= (osb_outx.OVLD == TRUE) ? TLD7002_OUTPUT_STATUS_BYTE_OUT_OVLD_MSK : 0x0;
    ret_byte |= (osb_outx.SLS == TRUE) ? TLD7002_OUTPUT_STATUS_BYTE_OUT_SLS_MSK : 0x0;
    ret_byte |= (osb_outx.OL == TRUE) ? TLD7002_OUTPUT_STATUS_BYTE_OUT_OL_MSK : 0x0;
    return ret_byte;
}


/** @brief Convert a uint8 value of a specific OUTX from a READ_OST frame to output status byte element.
 *
 * This functions converts a output status byte in uint8 representation of a
 * specific OUTX (first parameter) to a output status byte struct element. Here
 * the individual fields are extracted from the uint8 value and stored to the
 * output status byte element.
 * The uint8 representation is usually used in the read array of a READ_OST
 * frame.
 * This function is called automatically by the receive frame function of the
 * READ_OST frame needs in general not to be called manually.
 * However, it can be used translating manually a received output status byte
 * element in uint8 representation of a READ_OST frame into a output status byte
 * struct element of a specific OUTX.
 *
 * @param[in] uint8 osb_outx. OUTX output status byte of READ_OST frame as uint8 representation
 *
 * @return TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t OUTX output status byte element of READ_OST frame as struct
 */
/* Implements DD-SWA-238 */
TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t TLD7002_ConvOutxByteToStruct(uint8 osb_outx)
{
    TLD7002_FRAME_OUTPUT_STATUS_BYTE_OUT_t ret_element;
    ret_element.OUT_STAT = 		((osb_outx & TLD7002_OUTPUT_STATUS_BYTE_OUT_OUT_STAT_MSK) > 0) ? TRUE : FALSE;
    ret_element.VFWD_WRN = 		((osb_outx & TLD7002_OUTPUT_STATUS_BYTE_OUT_VFWD_WRN_MSK) > 0) ? TRUE : FALSE;
    ret_element.CUR_WRN = 		((osb_outx & TLD7002_OUTPUT_STATUS_BYTE_OUT_CUR_WRN_MSK) > 0) ? TRUE : FALSE;
    ret_element.DC_WRN = 		((osb_outx & TLD7002_OUTPUT_STATUS_BYTE_OUT_DC_WRN_MSK) > 0) ? TRUE : FALSE;
    ret_element.OUT_SHORT_WRN = ((osb_outx & TLD7002_OUTPUT_STATUS_BYTE_OUT_OUT_SHORT_WRN_MSK) > 0) ? TRUE : FALSE;
    ret_element.OVLD = 			((osb_outx & TLD7002_OUTPUT_STATUS_BYTE_OUT_OVLD_MSK) > 0) ? TRUE : FALSE;
    ret_element.SLS = 			((osb_outx & TLD7002_OUTPUT_STATUS_BYTE_OUT_SLS_MSK) > 0) ? TRUE : FALSE;
    ret_element.OL = 			((osb_outx & TLD7002_OUTPUT_STATUS_BYTE_OUT_OL_MSK) > 0) ? TRUE : FALSE;
    return ret_element;
}


/**@}*/