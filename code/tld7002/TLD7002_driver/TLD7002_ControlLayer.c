/**
 *  @file TLD7002_ControlLayer.c
 *  @author Infineon
 *  @date 17.06.2022
 *	@brief TLD7002 specific device driver implementation from Infineon Technologies AG.
 *	@note  This file includes the implementation for the TLD7002 control layer.
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

/******************************************************************************/
/*	Includes																  */
/******************************************************************************/
#include "TLD7002_ControlLayer.h"

/******************************************************************************/
/*	Global lookup table definitions                		                      */
/******************************************************************************/
/* CRC3 lookup table for 5 bit value */
const uint8 TLD7002_LOOKUP_CRC3_5BIT[32] =
{
    0, 1, 5, 4, 7, 6, 2, 3, 6, 7, 3, 2, 1, 0, 4, 5,
    3, 2, 6, 7, 4, 5, 1, 0, 5, 4, 0, 1, 2, 3, 7, 6
};

/* CRC3 lookup table for 8 bit value */
const uint8 TLD7002_LOOKUP_CRC3_8BIT[256] =
{
    0, 3, 4, 7, 2, 1, 6, 5, 1, 2, 5, 6, 3, 0, 7, 4,
    5, 6, 1, 2, 7, 4, 3, 0, 4, 7, 0, 3, 6, 5, 2, 1,
    7, 4, 3, 0, 5, 6, 1, 2, 6, 5, 2, 1, 4, 7, 0, 3,
    2, 1, 6, 5, 0, 3, 4, 7, 3, 0, 7, 4, 1, 2, 5, 6,
    6, 5, 2, 1, 4, 7, 0, 3, 7, 4, 3, 0, 5, 6, 1, 2,
    3, 0, 7, 4, 1, 2, 5, 6, 2, 1, 6, 5, 0, 3, 4, 7,
    1, 2, 5, 6, 3, 0, 7, 4, 0, 3, 4, 7, 2, 1, 6, 5,
    4, 7, 0, 3, 6, 5, 2, 1, 5, 6, 1, 2, 7, 4, 3, 0,
    3, 0, 7, 4, 1, 2, 5, 6, 2, 1, 6, 5, 0, 3, 4, 7,
    6, 5, 2, 1, 4, 7, 0, 3, 7, 4, 3, 0, 5, 6, 1, 2,
    4, 7, 0, 3, 6, 5, 2, 1, 5, 6, 1, 2, 7, 4, 3, 0,
    1, 2, 5, 6, 3, 0, 7, 4, 0, 3, 4, 7, 2, 1, 6, 5,
    5, 6, 1, 2, 7, 4, 3, 0, 4, 7, 0, 3, 6, 5, 2, 1,
    0, 3, 4, 7, 2, 1, 6, 5, 1, 2, 5, 6, 3, 0, 7, 4,
    2, 1, 6, 5, 0, 3, 4, 7, 3, 0, 7, 4, 1, 2, 5, 6,
    7, 4, 3, 0, 5, 6, 1, 2, 6, 5, 2, 1, 4, 7, 0, 3
};

/* CRC3 lookup table used for reflection */
const uint8 TLD7002_MIRROR_MID_CRC3[8] =
{
    0, 4, 2, 6, 1, 5, 3, 7
};

/* CRC8 lookup table */
const uint8 TLD7002_LOOKUP_CRC8_SAE_J1850[256] =
{
    0x00, 0x1D, 0x3A, 0x27, 0x74, 0x69, 0x4E, 0x53,
    0xE8, 0xF5, 0xD2, 0xCF, 0x9C, 0x81, 0xA6, 0xBB,
    0xCD, 0xD0, 0xF7, 0xEA, 0xB9, 0xA4, 0x83, 0x9E,
    0x25, 0x38, 0x1F, 0x02, 0x51, 0x4C, 0x6B, 0x76,
    0x87, 0x9A, 0xBD, 0xA0, 0xF3, 0xEE, 0xC9, 0xD4,
    0x6F, 0x72, 0x55, 0x48, 0x1B, 0x06, 0x21, 0x3C,
    0x4A, 0x57, 0x70, 0x6D, 0x3E, 0x23, 0x04, 0x19,
    0xA2, 0xBF, 0x98, 0x85, 0xD6, 0xCB, 0xEC, 0xF1,
    0x13, 0x0E, 0x29, 0x34, 0x67, 0x7A, 0x5D, 0x40,
    0xFB, 0xE6, 0xC1, 0xDC, 0x8F, 0x92, 0xB5, 0xA8,
    0xDE, 0xC3, 0xE4, 0xF9, 0xAA, 0xB7, 0x90, 0x8D,
    0x36, 0x2B, 0x0C, 0x11, 0x42, 0x5F, 0x78, 0x65,
    0x94, 0x89, 0xAE, 0xB3, 0xE0, 0xFD, 0xDA, 0xC7,
    0x7C, 0x61, 0x46, 0x5B, 0x08, 0x15, 0x32, 0x2F,
    0x59, 0x44, 0x63, 0x7E, 0x2D, 0x30, 0x17, 0x0A,
    0xB1, 0xAC, 0x8B, 0x96, 0xC5, 0xD8, 0xFF, 0xE2,
    0x26, 0x3B, 0x1C, 0x01, 0x52, 0x4F, 0x68, 0x75,
    0xCE, 0xD3, 0xF4, 0xE9, 0xBA, 0xA7, 0x80, 0x9D,
    0xEB, 0xF6, 0xD1, 0xCC, 0x9F, 0x82, 0xA5, 0xB8,
    0x03, 0x1E, 0x39, 0x24, 0x77, 0x6A, 0x4D, 0x50,
    0xA1, 0xBC, 0x9B, 0x86, 0xD5, 0xC8, 0xEF, 0xF2,
    0x49, 0x54, 0x73, 0x6E, 0x3D, 0x20, 0x07, 0x1A,
    0x6C, 0x71, 0x56, 0x4B, 0x18, 0x05, 0x22, 0x3F,
    0x84, 0x99, 0xBE, 0xA3, 0xF0, 0xED, 0xCA, 0xD7,
    0x35, 0x28, 0x0F, 0x12, 0x41, 0x5C, 0x7B, 0x66,
    0xDD, 0xC0, 0xE7, 0xFA, 0xA9, 0xB4, 0x93, 0x8E,
    0xF8, 0xE5, 0xC2, 0xDF, 0x8C, 0x91, 0xB6, 0xAB,
    0x10, 0x0D, 0x2A, 0x37, 0x64, 0x79, 0x5E, 0x43,
    0xB2, 0xAF, 0x88, 0x95, 0xC6, 0xDB, 0xFC, 0xE1,
    0x5A, 0x47, 0x60, 0x7D, 0x2E, 0x33, 0x14, 0x09,
    0x7F, 0x62, 0x45, 0x58, 0x0B, 0x16, 0x31, 0x2C,
    0x97, 0x8A, 0xAD, 0xB0, 0xE3, 0xFE, 0xD9, 0xC4
};

/* DC_UPDATE NON_LIN to LIN lookup table */
const uint8 TLD7002_LOOKUP_LIN_DC_8BIT[256] =
{
    0,   7,  13,  20,  26,  32,  38,  43,  48,  53,  57,  61,  64,  67,  70,  72,
    75,  77,  79,  80,  82,  84,  85,  87,  88,  90,  91,  93,  94,  96,  97,  98,
    100, 101, 102, 103, 104, 106, 107, 108, 109, 111, 112, 113, 114, 116, 117, 118,
    119, 120, 121, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
    136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 145, 146, 147, 148, 149, 150,
    150, 151, 152, 153, 154, 154, 155, 156, 157, 157, 158, 159, 160, 161, 161, 162,
    163, 164, 164, 165, 166, 167, 167, 168, 169, 170, 170, 171, 172, 173, 173, 174,
    175, 176, 176, 177, 178, 179, 179, 180, 181, 182, 182, 183, 184, 185, 185, 186,
    187, 187, 188, 189, 189, 190, 191, 191, 192, 193, 193, 194, 194, 195, 196, 196,
    197, 198, 198, 199, 199, 200, 200, 201, 202, 202, 203, 203, 204, 204, 205, 206,
    206, 207, 207, 208, 208, 209, 209, 210, 211, 211, 212, 212, 213, 213, 214, 215,
    215, 216, 216, 217, 218, 218, 219, 219, 220, 221, 221, 222, 222, 223, 223, 224,
    225, 225, 226, 226, 227, 227, 228, 229, 229, 230, 230, 231, 231, 232, 232, 233,
    233, 234, 234, 235, 235, 235, 236, 236, 237, 237, 238, 238, 239, 239, 239, 240,
    240, 241, 241, 242, 242, 242, 243, 243, 244, 244, 245, 246, 246, 247, 247, 248,
    248, 249, 249, 250, 250, 251, 251, 252, 252, 252, 253, 253, 254, 254, 255, 255
};
/* The 8 bit duty cycle configuration follows the function: 100 * (DC_8bit/255)^(1/gamma))
 * where ...
 * 		DC_8bit is 0 ... 255
 * 		gamma is 0.4545
 *
 * In order to reach a linear behaviour even for the 8 bit duty cycle configuration, a
 * lookup table is required. This lookup table is calculated by a polinomical fit function
 * of 10th degree smoothed by an piecewise cubic interpolation based on support points at
 * 0 %, 5 %, 10 %, ... 95 %, 100 % duty cycle on OUTx of TLD7002.
 */

/******************************************************************************/
/* Command preparation and validation function implementation                 */
/******************************************************************************/

/** @brief Prepare a DC_SYNC frame.
 *
 * Preparing of a DC_SYNC frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS, the
 * FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_BRDC_DC_SYNC_FRAME_t* Reference to DC_SYNC frame instance
 */
/* Implements DD-SWA-239 */
void TLD7002_brdc_dc_sync_prep(TLD7002_NetworkInstance_t *inst, TLD7002_BRDC_DC_SYNC_FRAME_t *frm)
{
    frm->w_brdc_dc_sync.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
    frm->w_brdc_dc_sync.frame_header.CRC_REQ_S_ADD.ADDRESS = TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST;
    frm->w_brdc_dc_sync.frame_header.CRC_REQ_S_ADD.CRC = 0;									/*< CRC initially 0 */
    frm->w_brdc_dc_sync.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_BRDC_DC_SYNC;
    frm->w_brdc_dc_sync.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_0;
    frm->w_brdc_dc_sync.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
    inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);					/*< calculate next Slave Rolling Counter */
}


/** @brief Finalize a TLD7002 BRDC_DC_SYNC data frame
 *
 * Finalize a PM_CHANGE frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_BRDC_DC_SYNC_FRAME_t* Reference to DC_SYNC frame instance
 */
/* Implements DD-SWA-240 */
void TLD7002_brdc_dc_sync_fin(TLD7002_BRDC_DC_SYNC_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_brdc_dc_sync.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_brdc_dc_sync.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_brdc_dc_sync.frame_header),
                                           &(frm->write_array[TLD7002_POS_BRDC_DC_SYNC_SYNC]));
}


/** @brief Prepare a TLD7002 DC_UPDATE (8 Bit) data frame
 *
 * Preparing of a DC_UPDATE (8 Bit) frame.
 * This functions prepares a frame by generating the content of the frame
 * header. Therefore at first the it is checked, if the slave address is valid
 * for that frame. Afterwards the header is generated by setting the SYNC byte,
 * the ADDRESS, the FUN field, the DLC field and the MRC as well as resetting
 * the CRC3 field. Additionally the slave and master rolling counters in the
 * instance are updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 * @param[in] uint8 address of slave where the frame has to be send [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-241 */
boolean TLD7002_dc_update_8bit_prep(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_pwm_dc_update.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.CRC = 0;							/*< CRC initially 0 */
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_DC_UPDATE;
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_4;
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;			/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Prepare a DC-UPDATE (8 Bit) frame with data length code 0 (DLC0).
 *
 * Preparing of a DC_UPDATE (8 Bit) frame with data length code 0 (DLC0).
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-242 */
boolean TLD7002_dc_update_8bit_dlc0_prep(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_pwm_dc_update.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.CRC = 0;							/*< CRC initially 0 */
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_DC_UPDATE;
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_0;
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;			/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a DC-UPDATE (8 Bit) frame.
 *
 * Finalize a DC_UPDATE (8 Bit) frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 */
/* Implements DD-SWA-243 */
void TLD7002_dc_update_8bit_fin(TLD7002_DC_UPDATE_8BIT_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_pwm_dc_update.frame_header),
                                           &(frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_SYNC]));

    /* copy duty cycles - if not already done at TLD7002_setChDc8BitToFrame() */
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT0] = frm->w_pwm_dc_update.DutyCycleOUT0;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT1] = frm->w_pwm_dc_update.DutyCycleOUT1;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT2] = frm->w_pwm_dc_update.DutyCycleOUT2;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT3] = frm->w_pwm_dc_update.DutyCycleOUT3;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT4] = frm->w_pwm_dc_update.DutyCycleOUT4;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT5] = frm->w_pwm_dc_update.DutyCycleOUT5;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT6] = frm->w_pwm_dc_update.DutyCycleOUT6;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT7] = frm->w_pwm_dc_update.DutyCycleOUT7;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT8] = frm->w_pwm_dc_update.DutyCycleOUT8;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT9] = frm->w_pwm_dc_update.DutyCycleOUT9;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT10] = frm->w_pwm_dc_update.DutyCycleOUT10;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT11] = frm->w_pwm_dc_update.DutyCycleOUT11;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT12] = frm->w_pwm_dc_update.DutyCycleOUT12;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT13] = frm->w_pwm_dc_update.DutyCycleOUT13;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT14] = frm->w_pwm_dc_update.DutyCycleOUT14;
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT15] = frm->w_pwm_dc_update.DutyCycleOUT15;

    /* Calculate CRC8 for SAFETY_BYTE from POS_DC_UPDATE_8BIT_DCOUT0 to POS_DC_UPDATE_8BIT_DCOUT15 */
    frm->w_pwm_dc_update.SAFETY_BYTE = TLD7002_calculate_crc8_general(
                                           &(frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT0]), TLD7002_POS_DC_UPDATE_8BIT_SAFETY_BYTE -
                                           TLD7002_POS_DC_UPDATE_8BIT_DCOUT0);                                                                                                                                                                                                     /*<
                                                                                                                                                                                                                                                 * CRC
                                                                                                                                                                                                                                                 * will
                                                                                                                                                                                                                                                 * be
                                                                                                                                                                                                                                                 * written
                                                                                                                                                                                                                                                 * in
                                                                                                                                                                                                                                                 * SAFETY_BYTE
                                                                                                                                                                                                                                                 * */
    frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_SAFETY_BYTE] = frm->w_pwm_dc_update.SAFETY_BYTE;
}


/** @brief Finalize a DC-UPDATE (8 Bit) frame with data length code 0 (DLC0).
 *
 * Finalize a DC_UPDATE (8 Bit) frame with data length code 0 (DLC0).
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 */
/* Implements DD-SWA-244 */
void TLD7002_dc_update_8bit_dlc0_fin(TLD7002_DC_UPDATE_8BIT_FRAME_t *frm)
{
    /* calculate for DLC0 message only CRC3 */
    TLD7002_calculate_crc3_master_request(&(frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_pwm_dc_update.frame_header),
                                           &(frm->write_array[TLD7002_POS_DC_UPDATE_8BIT_SYNC]));
}


/** @brief Validate a DC-UPDATE (8 Bit) frame answer.
 *
 * Validate a DC-UPDATE  (8 Bit) frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-245 */
uint8 TLD7002_dc_update_8bit_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_pwm_dc_update.frame_termination.OST), &(frm->r_pwm_dc_update.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_pwm_dc_update.frame_termination.ACK;									/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Validate a DC-UPDATE (8 Bit) with data length code 0 (DLC0) frame answer.
 *
 * Validate a DC-UPDATE  (8 Bit) with data length code 0 (DLC0) frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* Reference to DC_UPDATE_8BIT frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-246 */
uint8 TLD7002_dc_update_8bit_dlc0_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_8BIT_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  		/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    return TLD7002_dc_update_8bit_val_resp(inst, frm);											/* call same function as for standard DC_UPDATE frame */
}


/** @brief Prepare a DC-UPDATE (14 Bit) frame.
 *
 * Preparing of a DC_UPDATE (14 Bit) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame. Afterwards the header is generated by setting the SYNC byte, the
 * ADDRESS, the FUN field, the DLC field and the MRC as well as resetting the
 * CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * C and MRC as well as resetting the CRC3.
 * Additionally it is checked, if the slave address is valid for that frame.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_14BIT_FRAME_t* Reference to DC_UPDATE_14BIT frame instance
 * @param[in] uint8 address of slave where the frame has to be send [TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-247 */
boolean TLD7002_dc_update_14bit_prep(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_14BIT_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_pwm_dc_update.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.CRC = 0;							/*< CRC initially 0 */
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_DC_UPDATE;
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_6;
        frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;			/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a DC-UPDATE (14 Bit) frame.
 *
 * Finalize a DC_UPDATE (14 Bit) frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_DC_UPDATE_14BIT_FRAME_t* Reference to DC_UPDATE_14BIT frame instance
 */
/* Implements DD-SWA-248 */
void TLD7002_dc_update_14bit_fin(TLD7002_DC_UPDATE_14BIT_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_pwm_dc_update.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_pwm_dc_update.frame_header),
                                           &(frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_SYNC]));

    /* copy duty cycles - if not already done at TLD7002_setChDc14BitToFrame() */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT0_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT0 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT0_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT0 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT1_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT1 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT1_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT1 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT2_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT2 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT2_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT2 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT3_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT3 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT3_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT3 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT4_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT4 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT4_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT4 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT5_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT5 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT5_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT5 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT6_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT6 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT6_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT6 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT7_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT7 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT7_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT7 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT8_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT8 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT8_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT8 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT9_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT9 & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT9_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT9 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT10_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT10 & TLD7002_LOW_BYTE_16BIT);			/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT10_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT10 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT11_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT11 & TLD7002_LOW_BYTE_16BIT);			/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT11_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT11 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT12_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT12 & TLD7002_LOW_BYTE_16BIT);			/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT12_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT12 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT13_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT13 & TLD7002_LOW_BYTE_16BIT);			/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT13_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT13 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT14_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT14 & TLD7002_LOW_BYTE_16BIT);			/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT14_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT14 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT15_LB] = (uint8)(frm->w_pwm_dc_update.DutyCycleOUT15 & TLD7002_LOW_BYTE_16BIT);			/*< copy data element LSB */
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT15_HB] = (uint8)((frm->w_pwm_dc_update.DutyCycleOUT15 & TLD7002_HIGH_BYTE_14BIT) >> 8U);	/*< copy data element MSB */

    /* Calculate CRC8 for SAFETY_BYTE from POS_DC_UPDATE_14BIT_DCOUT0_HB to POS_DC_UPDATE_14BIT_DCOUT15_LB */
    frm->w_pwm_dc_update.SAFETY_BYTE                         = TLD7002_calculate_crc8_general(
                &(frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT0_HB]), TLD7002_POS_DC_UPDATE_14BIT_SAFETY_BYTE -
                TLD7002_POS_DC_UPDATE_14BIT_DCOUT0_HB);
    frm->write_array[TLD7002_POS_DC_UPDATE_14BIT_SAFETY_BYTE] = frm->w_pwm_dc_update.SAFETY_BYTE;
}


/** @brief Validate a DC-UPDATE (14 Bit) frame answer.
 *
 * Validate a DC-UPDATE  (14 Bit) frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_DC_UPDATE_14BIT_FRAME_t* Reference to DC_UPDATE_14BIT frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-249 */
uint8 TLD7002_dc_update_14bit_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_DC_UPDATE_14BIT_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_pwm_dc_update.frame_termination.OST), &(frm->r_pwm_dc_update.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_pwm_dc_update.frame_termination.ACK;											/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_pwm_dc_update.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a PM_CHANGE frame.
 *
 * Preparing of a PM_CHANGE frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_PM_CHANGE_FRAME_t* Reference to PM_CHANGE frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-341 */
boolean TLD7002_pm_change_prep(TLD7002_NetworkInstance_t *inst, TLD7002_PM_CHANGE_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_power_mode_change.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;				/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_power_mode_change.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_power_mode_change.frame_header.CRC_REQ_S_ADD.CRC = 0;						/*< CRC initially 0 */
        frm->w_power_mode_change.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_PM_CHANGE;
        frm->w_power_mode_change.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_1;
        frm->w_power_mode_change.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;		/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a PM_CHANGE frame.
 *
 * Finalize a PM_CHANGE frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_PM_CHANGE_FRAME_t* Reference to PM_CHANGE frame instance
 */
/* Implements DD-SWA-343 */
void TLD7002_pm_change_fin(TLD7002_PM_CHANGE_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_power_mode_change.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_power_mode_change.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_power_mode_change.frame_header),
                                           &(frm->write_array[TLD7002_POS_PM_CHANGE_SYNC]));

    /* set power mode and reserved byte */
    frm->write_array[TLD7002_POS_PM_CHANGE_POWER_MODE] = (uint8)(frm->w_power_mode_change.PM_CHANGE);
    frm->write_array[TLD7002_POS_PM_CHANGE_RES] = TLD7002_FRAME_RES_BYTE;

    /* Calculate CRC8 for SAFETY_BYTE from POS_PM_CHANGE_POWER_MODE to POS_PM_CHANGE_RES (0x00) */
    frm->w_power_mode_change.SAFETY_BYTE = TLD7002_calculate_crc8_general(
            &(frm->write_array[TLD7002_POS_PM_CHANGE_POWER_MODE]), TLD7002_POS_PM_CHANGE_SAFETY_BYTE -
            TLD7002_POS_PM_CHANGE_POWER_MODE);
    frm->write_array[TLD7002_POS_PM_CHANGE_SAFETY_BYTE] = frm->w_power_mode_change.SAFETY_BYTE;
}


/** @brief Validate a PM_CHANGE frame answer.
 *
 * Validate a PM_CHANGE frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_PM_CHANGE_FRAME_t* Reference to PM_CHANGE frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-342 */
uint8 TLD7002_pm_change_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_PM_CHANGE_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_power_mode_change.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_power_mode_change.frame_termination.OST), &(frm->r_power_mode_change.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_power_mode_change.frame_termination.ACK;								/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_power_mode_change.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a READ_OST frame.
 *
 * Preparing of a READ_OST frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_OST_FRAME_t* Reference to READ_OST frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_1 ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-250 */
boolean TLD7002_read_ost_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_OST_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_read_output_status.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;				/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_read_output_status.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_read_output_status.frame_header.CRC_REQ_S_ADD.CRC = 0;						/*< CRC initially 0 */
        frm->w_read_output_status.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_READ_OST;
        frm->w_read_output_status.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_4;
        frm->w_read_output_status.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;		/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a READ_OST frame.
 *
 * Finalize a READ_OST frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_READ_OST_FRAME_t* Reference to READ_OST frame instance
 */
/* Implements DD-SWA-251 */
void TLD7002_read_ost_fin(TLD7002_READ_OST_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_read_output_status.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_read_output_status.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_read_output_status.frame_header),
                                           &(frm->write_array[TLD7002_POS_READ_OST_SYNC]));
}


/** @brief Validate a READ_OST frame answer.
 *
 * Validate a READ_OST frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_OST_FRAME_t* Reference to READ_OST frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error; TLD7002_FRAME_VAL_CRC8_ERROR: CRC8 error in DATA; ]
 */
/* Implements DD-SWA-252 */
uint8 TLD7002_read_ost_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_OST_FRAME_t *frm)
{
    uint8 crc8_data_val = 0;
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_read_output_status.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* from POS_READ_OST_OSB_OUT0 to POS_READ_OST_OSB_OUT15 */
    crc8_data_val = TLD7002_calculate_crc8_general(&(frm->read_array[TLD7002_POS_READ_OST_OSB_OUT0]),
                    TLD7002_POS_READ_OST_SAFETY_BYTE - TLD7002_POS_READ_OST_OSB_OUT0);

    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_read_output_status.frame_termination.OST), &(frm->r_read_output_status.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_read_output_status.frame_termination.ACK;								/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_read_output_status.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* check for CRC8 error of data */
    if(crc8_data_val != frm->r_read_output_status.SAFETY_BYTE)
    {
        return TLD7002_FRAME_VAL_CRC8_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a HWCR frame
 *
 * Preparing of a HWCR frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_HWCR_FRAME_t* Reference to HWCR frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-253 */
boolean TLD7002_hwcr_prep(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_hardware_control.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;					/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_hardware_control.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_hardware_control.frame_header.CRC_REQ_S_ADD.CRC = 0;							/*< CRC initially 0 */
        frm->w_hardware_control.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_HWCR;
        frm->w_hardware_control.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_3;
        frm->w_hardware_control.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;		/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a HWCR frame.
 *
 * Finalize a HWCR frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] HWCR_FRAME_t* Reference to HWCR frame instance
 */
/* Implements DD-SWA-254 */
void TLD7002_hwcr_fin(TLD7002_HWCR_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_hardware_control.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_hardware_control.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_hardware_control.frame_header),
                                           &(frm->write_array[TLD7002_POS_HWCR_SYNC]));

    /* set reset and reserved bytes */
    frm->write_array[TLD7002_POS_HWCR_RESET_OL_HB] = 0;
    frm->write_array[TLD7002_POS_HWCR_RESET_OL_LB] = 0;
    frm->write_array[TLD7002_POS_HWCR_RESET_OP_HB] = 0;
    frm->write_array[TLD7002_POS_HWCR_RESET_OP_LB] = 0;
    frm->write_array[TLD7002_POS_HWCR_RESET_SLS_HB] = 0;
    frm->write_array[TLD7002_POS_HWCR_RESET_SLS_LB] = 0;
    frm->write_array[TLD7002_POS_HWCR_RESET_STATUS] = 0;
    frm->write_array[TLD7002_POS_HWCR_RESET_OL_HB] |=
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT15) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT15_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT15_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT14) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT14_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT14_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT13) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT13_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT13_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT12) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT12_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT12_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT11) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT11_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT11_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT10) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT10_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT10_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT9) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT9_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT9_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT8) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT8_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT8_POS - 8U)));
    frm->write_array[TLD7002_POS_HWCR_RESET_OL_LB] |=
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT7) << TLD7002_HWCR_RESET_OUT_BYTE_OUT7_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT7_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT6) << TLD7002_HWCR_RESET_OUT_BYTE_OUT6_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT6_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT5) << TLD7002_HWCR_RESET_OUT_BYTE_OUT5_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT5_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT4) << TLD7002_HWCR_RESET_OUT_BYTE_OUT4_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT4_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT3) << TLD7002_HWCR_RESET_OUT_BYTE_OUT3_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT3_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT2) << TLD7002_HWCR_RESET_OUT_BYTE_OUT2_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT2_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT1) << TLD7002_HWCR_RESET_OUT_BYTE_OUT1_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT1_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OVERLOAD.RES_OUT0) << TLD7002_HWCR_RESET_OUT_BYTE_OUT0_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT0_MSK);
    frm->write_array[TLD7002_POS_HWCR_RESET_OP_HB] |=
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT15) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT15_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT15_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT14) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT14_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT14_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT13) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT13_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT13_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT12) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT12_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT12_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT11) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT11_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT11_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT10) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT10_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT10_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT9) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT9_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT9_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT8) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT8_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT8_POS - 8U)));
    frm->write_array[TLD7002_POS_HWCR_RESET_OP_LB] |=
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT7) << TLD7002_HWCR_RESET_OUT_BYTE_OUT7_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT7_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT6) << TLD7002_HWCR_RESET_OUT_BYTE_OUT6_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT6_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT5) << TLD7002_HWCR_RESET_OUT_BYTE_OUT5_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT5_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT4) << TLD7002_HWCR_RESET_OUT_BYTE_OUT4_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT4_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT3) << TLD7002_HWCR_RESET_OUT_BYTE_OUT3_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT3_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT2) << TLD7002_HWCR_RESET_OUT_BYTE_OUT2_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT2_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT1) << TLD7002_HWCR_RESET_OUT_BYTE_OUT1_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT1_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_OPENLOAD.RES_OUT0) << TLD7002_HWCR_RESET_OUT_BYTE_OUT0_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT0_MSK);
    frm->write_array[TLD7002_POS_HWCR_RESET_SLS_HB] |=
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT15) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT15_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT15_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT14) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT14_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT14_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT13) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT13_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT13_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT12) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT12_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT12_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT11) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT11_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT11_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT10) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT10_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT10_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT9) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT9_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT9_POS - 8U))) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT8) << (TLD7002_HWCR_RESET_OUT_BYTE_OUT8_POS - 8U)) & (1U << (TLD7002_HWCR_RESET_OUT_BYTE_OUT8_POS - 8U)));
    frm->write_array[TLD7002_POS_HWCR_RESET_SLS_LB] |=
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT7) << TLD7002_HWCR_RESET_OUT_BYTE_OUT7_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT7_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT6) << TLD7002_HWCR_RESET_OUT_BYTE_OUT6_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT6_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT5) << TLD7002_HWCR_RESET_OUT_BYTE_OUT5_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT5_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT4) << TLD7002_HWCR_RESET_OUT_BYTE_OUT4_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT4_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT3) << TLD7002_HWCR_RESET_OUT_BYTE_OUT3_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT3_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT2) << TLD7002_HWCR_RESET_OUT_BYTE_OUT2_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT2_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT1) << TLD7002_HWCR_RESET_OUT_BYTE_OUT1_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT1_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_SLS.RES_OUT0) << TLD7002_HWCR_RESET_OUT_BYTE_OUT0_POS) & TLD7002_HWCR_RESET_OUT_BYTE_OUT0_MSK);
    frm->write_array[TLD7002_POS_HWCR_RESERVED] = TLD7002_FRAME_RES_BYTE;
    frm->write_array[TLD7002_POS_HWCR_RESET_STATUS] |=
        (((uint8)(frm->w_hardware_control.RESET_STATUS.VLED_VS_UV) 		<< TLD7002_HWCR_RESET_STATUS_VLED_VS_UV_POS) 	& TLD7002_HWCR_RESET_STATUS_VLED_VS_UV_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_STATUS.OUT_SHRT_WRN)	<< TLD7002_HWCR_RESET_STATUS_OUT_SHRT_WRN_POS) 	& TLD7002_HWCR_RESET_STATUS_OUT_SHRT_WRN_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_STATUS.GPINn_WRN)		<< TLD7002_HWCR_RESET_STATUS_GPINn_WRN_POS) 	& TLD7002_HWCR_RESET_STATUS_GPINn_WRN_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_STATUS.DC_WRN) 			<< TLD7002_HWCR_RESET_STATUS_DC_WRN_POS)		& TLD7002_HWCR_RESET_STATUS_DC_WRN_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_STATUS.CUR_WRN) 		<< TLD7002_HWCR_RESET_STATUS_CUR_WRN_POS) 		& TLD7002_HWCR_RESET_STATUS_CUR_WRN_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_STATUS.VFWD_WRN) 		<< TLD7002_HWCR_RESET_STATUS_VFWD_WRN_POS) 		& TLD7002_HWCR_RESET_STATUS_VFWD_WRN_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_STATUS.OVLD) 			<< TLD7002_HWCR_RESET_STATUS_OVLD_POS) 			& TLD7002_HWCR_RESET_STATUS_OVLD_MSK) |
        (((uint8)(frm->w_hardware_control.RESET_STATUS.OSB_FAULT) 		<< TLD7002_HWCR_RESET_STATUS_FAULT_POS) 		& TLD7002_HWCR_RESET_STATUS_FAULT_MSK);

    /* Calculate CRC8 for SAFETY_BYTE from POS_HWCR_RESET_OL_1 to POS_HWCR_RESET_STATUS */
    frm->w_hardware_control.SAFETY_BYTE            = TLD7002_calculate_crc8_general(
                &(frm->write_array[TLD7002_POS_HWCR_RESET_OL_HB]), TLD7002_POS_HWCR_SAFETY_BYTE - TLD7002_POS_HWCR_RESET_OL_HB);
    frm->write_array[TLD7002_POS_HWCR_SAFETY_BYTE] = frm->w_hardware_control.SAFETY_BYTE;
}


/** @brief Validate a HWCR frame answer.
 *
 * Validate a HWCR frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_HWCR_FRAME_t* Reference to HWCR frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-255 */
uint8 TLD7002_hwcr_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_HWCR_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_hardware_control.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_hardware_control.frame_termination.OST), &(frm->r_hardware_control.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_hardware_control.frame_termination.ACK;								/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_hardware_control.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a WRITE_REG_DLC1 frame.
 *
 * Preparing of a WRITE_REG (DLC1: 1 word / 2 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC1_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-256 */
boolean TLD7002_write_reg_dlc1_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC1_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_write_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;								/*< CRC initially 0 */
        frm->w_write_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_WRITE_REG;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_1;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a WRITE_REG_DLC1 frame.
 *
 * Finalize a WRITE_REG_DLC1 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_WRITE_REG_DLC1_FRAME_t* Reference to WRITE_REG frame instance
 */
/* Implements DD-SWA-257 */
void TLD7002_write_reg_dlc1_fin(TLD7002_WRITE_REG_DLC1_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_write_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_write_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_write_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_WRITE_REG_SYNC]));

    /* set address */
    frm->write_array[TLD7002_POS_WRITE_REG_START_ADD] = frm->w_write_reg.StartADDR;

    /* copy data bytes */
    frm->write_array[TLD7002_POS_WRITE_REG_DATA0_HB] = (uint8)((frm->w_write_reg.Data[0] & TLD7002_HIGH_BYTE_16BIT) >> 8U);
    frm->write_array[TLD7002_POS_WRITE_REG_DATA0_LB] = (uint8)(frm->w_write_reg.Data[0] & TLD7002_LOW_BYTE_16BIT);

    /* Calculate CRC8 for SAFETY_BYTE from POS_WRITE_REG_DATA0_HB to POS_WRITE_REG_DLC1_SAFETY_BYTE-1 */
    frm->w_write_reg.SAFETY_BYTE = TLD7002_calculate_crc8_general(
                                       &(frm->write_array[TLD7002_POS_WRITE_REG_START_ADD]), TLD7002_POS_WRITE_REG_DLC1_SAFETY_BYTE -
                                       TLD7002_POS_WRITE_REG_START_ADD);
    frm->write_array[TLD7002_POS_WRITE_REG_DLC1_SAFETY_BYTE] = frm->w_write_reg.SAFETY_BYTE;
}

/** @brief Validate a WRITE_REG_DLC1 frame.
 *
 * Validate a WRITE_REG_DLC1 frame response.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC1_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-258 */
uint8 TLD7002_write_reg_dlc1_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC1_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_write_reg.frame_termination.OST), &(frm->r_write_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_write_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a WRITE_REG_DLC2 frame.
 *
 * Preparing of a WRITE_REG (DLC2: 2 words / 4 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC2_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-259 */
boolean TLD7002_write_reg_dlc2_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC2_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_write_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;								/*< CRC initially 0 */
        frm->w_write_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_WRITE_REG;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_2;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}

/** @brief Finalize a WRITE_REG_DLC2 frame.
 *
 * Finalize a WRITE_REG_DLC2 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_WRITE_REG_DLC2_FRAME_t* Reference to WRITE_REG frame instance
 */
/* Implements DD-SWA-260 */
void TLD7002_write_reg_dlc2_fin(TLD7002_WRITE_REG_DLC2_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_write_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_write_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_write_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_WRITE_REG_SYNC]));

    /* set address */
    frm->write_array[TLD7002_POS_WRITE_REG_START_ADD] = frm->w_write_reg.StartADDR;

    /* copy data bytes */
    frm->write_array[TLD7002_POS_WRITE_REG_DATA0_HB] = (uint8)((frm->w_write_reg.Data[0] & TLD7002_HIGH_BYTE_16BIT) >> 8U);
    frm->write_array[TLD7002_POS_WRITE_REG_DATA0_LB] = (uint8)(frm->w_write_reg.Data[0] & TLD7002_LOW_BYTE_16BIT);
    frm->write_array[TLD7002_POS_WRITE_REG_DATA1_HB] = (uint8)((frm->w_write_reg.Data[1] & TLD7002_HIGH_BYTE_16BIT) >> 8U);
    frm->write_array[TLD7002_POS_WRITE_REG_DATA1_LB] = (uint8)(frm->w_write_reg.Data[1] & TLD7002_LOW_BYTE_16BIT);

    /* Calculate CRC8 for SAFETY_BYTE from POS_WRITE_REG_DATA0_HB to POS_WRITE_REG_DLC2_SAFETY_BYTE-1 */
    frm->w_write_reg.SAFETY_BYTE = TLD7002_calculate_crc8_general(
                                       &(frm->write_array[TLD7002_POS_WRITE_REG_START_ADD]), TLD7002_POS_WRITE_REG_DLC2_SAFETY_BYTE -
                                       TLD7002_POS_WRITE_REG_START_ADD);
    frm->write_array[TLD7002_POS_WRITE_REG_DLC2_SAFETY_BYTE] = frm->w_write_reg.SAFETY_BYTE;
}


/** @brief Validate a WRITE_REG_DLC2 frame.
 *
 * Validate a WRITE_REG_DLC2 frame response.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC2_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-261 */
uint8 TLD7002_write_reg_dlc2_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC2_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_write_reg.frame_termination.OST), &(frm->r_write_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_write_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a WRITE_REG_DLC3 frame.
 *
 * Preparing of a WRITE_REG (DLC3: 4 words / 8 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC3_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-262 */
boolean TLD7002_write_reg_dlc3_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC3_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_write_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;								/*< CRC initially 0 */
        frm->w_write_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_WRITE_REG;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_3;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a WRITE_REG_DLC3 frame.
 *
 * Finalize a WRITE_REG_DLC3 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_WRITE_REG_DLC3_FRAME_t* Reference to WRITE_REG frame instance
 */
/* Implements DD-SWA-263 */
void TLD7002_write_reg_dlc3_fin(TLD7002_WRITE_REG_DLC3_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_write_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_write_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_write_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_WRITE_REG_SYNC]));

    /* set address */
    frm->write_array[TLD7002_POS_WRITE_REG_START_ADD] = frm->w_write_reg.StartADDR;

    /* copy data bytes */
    for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC3_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
    {
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_HB + cnt * 2] = (uint8)((frm->w_write_reg.Data[cnt] & TLD7002_HIGH_BYTE_16BIT) >> 8U);
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_LB + cnt * 2] = (uint8)(frm->w_write_reg.Data[cnt] & TLD7002_LOW_BYTE_16BIT);
    }

    /* Calculate CRC8 for SAFETY_BYTE from POS_WRITE_REG_DATA0_HB to POS_WRITE_REG_DLC3_SAFETY_BYTE-1 */
    frm->w_write_reg.SAFETY_BYTE = TLD7002_calculate_crc8_general(
                                       &(frm->write_array[TLD7002_POS_WRITE_REG_START_ADD]), TLD7002_POS_WRITE_REG_DLC3_SAFETY_BYTE -
                                       TLD7002_POS_WRITE_REG_START_ADD);
    frm->write_array[TLD7002_POS_WRITE_REG_DLC3_SAFETY_BYTE] = frm->w_write_reg.SAFETY_BYTE;
}


/** @brief Validate a WRITE_REG_DLC3 frame.
 *
 * Validate a WRITE_REG_DLC3 frame response.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC3_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-264 */
uint8 TLD7002_write_reg_dlc3_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC3_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_write_reg.frame_termination.OST), &(frm->r_write_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_write_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a WRITE_REG_DLC4 frame.
 *
 * Preparing of a WRITE_REG (DLC4: 8 words / 16 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC4_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-265 */
boolean TLD7002_write_reg_dlc4_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC4_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_write_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;								/*< CRC initially 0 */
        frm->w_write_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_WRITE_REG;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_4;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a WRITE_REG_DLC4 frame.
 *
 * Finalize a WRITE_REG_DLC4 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_WRITE_REG_DLC4_FRAME_t* Reference to WRITE_REG frame instance
 */
/* Implements DD-SWA-266 */
void TLD7002_write_reg_dlc4_fin(TLD7002_WRITE_REG_DLC4_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_write_reg.frame_header.CRC_REQ_S_ADD), &(frm->w_write_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_write_reg.frame_header), &(frm->write_array[TLD7002_POS_WRITE_REG_SYNC]));

    /* set address */
    frm->write_array[TLD7002_POS_WRITE_REG_START_ADD] = frm->w_write_reg.StartADDR;

    /* copy data bytes */
    for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC4_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
    {
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_HB + cnt * 2] = (uint8)((frm->w_write_reg.Data[cnt] & TLD7002_HIGH_BYTE_16BIT) >> 8U);
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_LB + cnt * 2] = (uint8)(frm->w_write_reg.Data[cnt] & TLD7002_LOW_BYTE_16BIT);
    }

    /* Calculate CRC8 for SAFETY_BYTE from POS_WRITE_REG_DATA0_HB to POS_WRITE_REG_DLC4_SAFETY_BYTE-1 */
    frm->w_write_reg.SAFETY_BYTE = TLD7002_calculate_crc8_general(&(frm->write_array[TLD7002_POS_WRITE_REG_START_ADD]), TLD7002_POS_WRITE_REG_DLC4_SAFETY_BYTE - TLD7002_POS_WRITE_REG_START_ADD);
    frm->write_array[TLD7002_POS_WRITE_REG_DLC4_SAFETY_BYTE] = frm->w_write_reg.SAFETY_BYTE;
}

/** @brief Validate a WRITE_REG_DLC4 frame.
 *
 * Validate a WRITE_REG_DLC4 frame response.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC4_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-267 */
uint8 TLD7002_write_reg_dlc4_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC4_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_write_reg.frame_termination.OST), &(frm->r_write_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_write_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a WRITE_REG_DLC5 frame.
 *
 * Preparing of a WRITE_REG (DLC5: 12 words / 24 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC5_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-268 */
boolean TLD7002_write_reg_dlc5_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC5_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_write_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;								/*< CRC initially 0 */
        frm->w_write_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_WRITE_REG;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_5;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a WRITE_REG_DLC5 frame.
 *
 * Finalize a WRITE_REG_DLC5 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_WRITE_REG_DLC5_FRAME_t* Reference to WRITE_REG frame instance
 */
/* Implements DD-SWA-269 */
void TLD7002_write_reg_dlc5_fin(TLD7002_WRITE_REG_DLC5_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_write_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_write_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_write_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_WRITE_REG_SYNC]));

    /* set address */
    frm->write_array[TLD7002_POS_WRITE_REG_START_ADD] = frm->w_write_reg.StartADDR;

    /* copy data bytes */
    for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC5_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
    {
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_HB + cnt * 2U] = (uint8)((frm->w_write_reg.Data[cnt] & TLD7002_HIGH_BYTE_16BIT) >> 8U);
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_LB + cnt * 2U] = (uint8)(frm->w_write_reg.Data[cnt] & TLD7002_LOW_BYTE_16BIT);
    }

    /* Calculate CRC8 for SAFETY_BYTE from POS_WRITE_REG_DATA0_HB to POS_WRITE_REG_DLC5_SAFETY_BYTE-1 */
    frm->w_write_reg.SAFETY_BYTE = TLD7002_calculate_crc8_general(
                                       &(frm->write_array[TLD7002_POS_WRITE_REG_START_ADD]), TLD7002_POS_WRITE_REG_DLC5_SAFETY_BYTE -
                                       TLD7002_POS_WRITE_REG_START_ADD);
    frm->write_array[TLD7002_POS_WRITE_REG_DLC5_SAFETY_BYTE] = frm->w_write_reg.SAFETY_BYTE;
}


/** @brief Validate a WRITE_REG_DLC5 frame.
 *
 * Validate a WRITE_REG_DLC5 frame response.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC5_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-270 */
uint8 TLD7002_write_reg_dlc5_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC5_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_write_reg.frame_termination.OST), &(frm->r_write_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_write_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a WRITE_REG_DLC6 frame.
 *
 * Preparing of a WRITE_REG (DLC6: 16 words / 32 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC6_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-271 */
boolean TLD7002_write_reg_dlc6_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC6_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_write_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;								/*< CRC initially 0 */
        frm->w_write_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_WRITE_REG;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_6;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a WRITE_REG_DLC6 frame.
 *
 * Finalize a WRITE_REG_DLC6 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_WRITE_REG_DLC6_FRAME_t* Reference to WRITE_REG frame instance
 */
/* Implements DD-SWA-272 */
void TLD7002_write_reg_dlc6_fin(TLD7002_WRITE_REG_DLC6_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_write_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_write_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_write_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_WRITE_REG_SYNC]));

    /* set address */
    frm->write_array[TLD7002_POS_WRITE_REG_START_ADD] = frm->w_write_reg.StartADDR;

    /* copy data bytes */
    for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC6_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
    {
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_HB + cnt * 2] = (uint8)((frm->w_write_reg.Data[cnt] & TLD7002_HIGH_BYTE_16BIT) >> 8U);
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_LB + cnt * 2] = (uint8)(frm->w_write_reg.Data[cnt] & TLD7002_LOW_BYTE_16BIT);
    }

    /* Calculate CRC8 for SAFETY_BYTE from POS_WRITE_REG_DATA0_HB to POS_WRITE_REG_DLC6_SAFETY_BYTE-1 */
    frm->w_write_reg.SAFETY_BYTE = TLD7002_calculate_crc8_general(
                                       &(frm->write_array[TLD7002_POS_WRITE_REG_START_ADD]), TLD7002_POS_WRITE_REG_DLC6_SAFETY_BYTE -
                                       TLD7002_POS_WRITE_REG_START_ADD);
    frm->write_array[TLD7002_POS_WRITE_REG_DLC6_SAFETY_BYTE] = frm->w_write_reg.SAFETY_BYTE;
}


/** @brief Validate a WRITE_REG_DLC6 frame.
 *
 * Validate a WRITE_REG_DLC6 frame response.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC6_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-273 */
uint8 TLD7002_write_reg_dlc6_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC6_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_write_reg.frame_termination.OST), &(frm->r_write_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_write_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a WRITE_REG_DLC7 frame.
 *
 * Preparing of a WRITE_REG (DLC7: 32 words / 64 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC7_FRAME_t* Reference to WRITE_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-274 */
boolean TLD7002_write_reg_dlc7_prep(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC7_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_write_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;						/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_write_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;								/*< CRC initially 0 */
        frm->w_write_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_WRITE_REG;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_7;
        frm->w_write_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a WRITE_REG_DLC7 frame.
 *
 * Finalize a WRITE_REG_DLC7 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_WRITE_REG_DLC7_FRAME_t* Reference to WRITE_REG frame instance
 */
/* Implements DD-SWA-275 */
void TLD7002_write_reg_dlc7_fin(TLD7002_WRITE_REG_DLC7_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_write_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_write_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_write_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_WRITE_REG_SYNC]));

    /* set address */
    frm->write_array[TLD7002_POS_WRITE_REG_START_ADD] = frm->w_write_reg.StartADDR;

    /* copy data bytes */
    for(uint16 cnt = 0; cnt < (TLD7002_LEN_WRITE_REG_DLC7_WRITE - TLD7002_LEN_WRITE_REG_OVHD) / 2; cnt++)
    {
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_HB + cnt * 2] = (uint8)((frm->w_write_reg.Data[cnt] & TLD7002_HIGH_BYTE_16BIT) >> 8U);
        frm->write_array[TLD7002_POS_WRITE_REG_DATA0_LB + cnt * 2] = (uint8)(frm->w_write_reg.Data[cnt] & TLD7002_LOW_BYTE_16BIT);
    }

    /* Calculate CRC8 for SAFETY_BYTE from POS_WRITE_REG_DATA0_HB to POS_WRITE_REG_DLC7_SAFETY_BYTE-1 */
    frm->w_write_reg.SAFETY_BYTE = TLD7002_calculate_crc8_general(
                                       &(frm->write_array[TLD7002_POS_WRITE_REG_START_ADD]), TLD7002_POS_WRITE_REG_DLC7_SAFETY_BYTE -
                                       TLD7002_POS_WRITE_REG_START_ADD);
    frm->write_array[TLD7002_POS_WRITE_REG_DLC7_SAFETY_BYTE] = frm->w_write_reg.SAFETY_BYTE;
}


/** @brief Validate a WRITE_REG_DLC7 frame.
 *
 * Validate a WRITE_REG_DLC6 frame response.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_WRITE_REG_DLC7_FRAME_t* Reference to WRITE_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE ; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error]
 */
/* Implements DD-SWA-276 */
uint8 TLD7002_write_reg_dlc7_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_WRITE_REG_DLC7_FRAME_t *frm)
{
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_write_reg.frame_termination.OST), &(frm->r_write_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_write_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_write_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a READ_REG_DLC1 frame.
 *
 * Preparing of a READ_REG (DLC1: 1 word / 2 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC1_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-277 */
boolean TLD7002_read_reg_dlc1_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC1_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_read_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;									/*< CRC initially 0 */
        frm->w_read_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_READ_REG;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_1;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a READ_REG_DLC1 frame.
 *
 * Finalize a READ_REG_DLC1 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_READ_REG_DLC1_FRAME_t* Reference to READ_REG frame instance
 */
/* Implements DD-SWA-278 */
void TLD7002_read_reg_dlc1_fin(TLD7002_READ_REG_DLC1_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_read_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_read_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_read_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_READ_REG_SYNC]));

    /* set start address to frame */
    frm->write_array[TLD7002_POS_READ_REG_START_ADD] = frm->w_read_reg.StartADDR;
}


/** @brief Validate a READ_REG_DLC1 frame.
 *
 * Validate a READ_REG_DLC1 frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC1_FRAME_t* Reference to READ_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error; TLD7002_FRAME_VAL_CRC8_ERROR: CRC8 error in DATA; ]
 */
/* Implements DD-SWA-279 */
uint8 TLD7002_read_reg_dlc1_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC1_FRAME_t *frm)
{
    uint8 crc8_data_val = 0;
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* leading slave address + data from POS_READ_REG_DATA0_HB to POS_READ_REG_DLC1_SAFETY_BYTE-1 */
    crc8_data_val = TLD7002_calculate_crc8_leadbyte(&(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]),
                    TLD7002_POS_READ_REG_DLC1_SAFETY_BYTE - TLD7002_POS_READ_REG_DATA0_HB,
                    frm->write_array[TLD7002_POS_READ_REG_START_ADD]);

    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_read_reg.frame_termination.OST), &(frm->r_read_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_read_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* check for CRC8 error of data */
    if(crc8_data_val != frm->r_read_reg.SAFETY_BYTE)
    {
        return TLD7002_FRAME_VAL_CRC8_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a READ_REG_DLC2 frame.
 *
 * Preparing of a READ_REG (DLC2: 2 words / 4 bytes)  frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC2_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-280 */
boolean TLD7002_read_reg_dlc2_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC2_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_read_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;									/*< CRC initially 0 */
        frm->w_read_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_READ_REG;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_2;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a READ_REG_DLC2 frame.
 *
 * Finalize a READ_REG_DLC2 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_READ_REG_DLC2_FRAME_t* Reference to READ_REG frame instance
 */
/* Implements DD-SWA-281 */
void TLD7002_read_reg_dlc2_fin(TLD7002_READ_REG_DLC2_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_read_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_read_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_read_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_READ_REG_SYNC]));

    /* set start address to frame */
    frm->write_array[TLD7002_POS_READ_REG_START_ADD] = frm->w_read_reg.StartADDR;
}


/** @brief Validate a READ_REG_DLC2 frame.
 *
 * Validate a READ_REG_DLC2 frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC2_FRAME_t* Reference to READ_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error; TLD7002_FRAME_VAL_CRC8_ERROR: CRC8 error in DATA; ]
 */
/* Implements DD-SWA-282 */
uint8 TLD7002_read_reg_dlc2_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC2_FRAME_t *frm)
{
    uint8 crc8_data_val = 0;
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* leading slave address + data from POS_READ_REG_DATA0_HB to POS_READ_REG_DLC2_SAFETY_BYTE-1 */
    crc8_data_val = TLD7002_calculate_crc8_leadbyte(&(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]),
                    TLD7002_POS_READ_REG_DLC2_SAFETY_BYTE - TLD7002_POS_READ_REG_DATA0_HB,
                    frm->write_array[TLD7002_POS_READ_REG_START_ADD]);

    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_read_reg.frame_termination.OST), &(frm->r_read_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_read_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* check for CRC8 error of data */
    if(crc8_data_val != frm->r_read_reg.SAFETY_BYTE)
    {
        return TLD7002_FRAME_VAL_CRC8_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a READ_REG_DLC3 frame.
 *
 * Preparing of a READ_REG (DLC3: 4 words / 8 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC3_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-283 */
boolean TLD7002_read_reg_dlc3_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC3_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_read_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;									/*< CRC initially 0 */
        frm->w_read_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_READ_REG;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_3;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a READ_REG_DLC3 frame.
 *
 * Finalize a READ_REG_DLC3 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_READ_REG_DLC3_FRAME_t* Reference to READ_REG frame instance
 */
/* Implements DD-SWA-284 */
void TLD7002_read_reg_dlc3_fin(TLD7002_READ_REG_DLC3_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_read_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_read_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_read_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_READ_REG_SYNC]));

    /* set start address to frame */
    frm->write_array[TLD7002_POS_READ_REG_START_ADD] = frm->w_read_reg.StartADDR;
}

/** @brief Validate a READ_REG_DLC3 frame.
 *
 * Validate a READ_REG_DLC3 frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC3_FRAME_t* Reference to READ_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error; TLD7002_FRAME_VAL_CRC8_ERROR: CRC8 error in DATA; ]
 */
/* Implements DD-SWA-285 */
uint8 TLD7002_read_reg_dlc3_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC3_FRAME_t *frm)
{
    uint8 crc8_data_val = 0;
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* leading slave address + data from POS_READ_REG_DATA0_HB to POS_READ_REG_DLC3_SAFETY_BYTE-1 */
    crc8_data_val = TLD7002_calculate_crc8_leadbyte(&(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]),
                    TLD7002_POS_READ_REG_DLC3_SAFETY_BYTE - TLD7002_POS_READ_REG_DATA0_HB,
                    frm->write_array[TLD7002_POS_READ_REG_START_ADD]);

    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_read_reg.frame_termination.OST), &(frm->r_read_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_read_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* check for CRC8 error of data */
    if(crc8_data_val != frm->r_read_reg.SAFETY_BYTE)
    {
        return TLD7002_FRAME_VAL_CRC8_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a READ_REG_DLC4 frame.
 *
 * Preparing of a READ_REG (DLC4: 8 words / 16 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC4_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-286 */
boolean TLD7002_read_reg_dlc4_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC4_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_read_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;									/*< CRC initially 0 */
        frm->w_read_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_READ_REG;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_4;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a READ_REG_DLC4 frame.
 *
 * Finalize a READ_REG_DLC4 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_READ_REG_DLC4_FRAME_t* Reference to READ_REG frame instance
 */
/* Implements DD-SWA-287 */
void TLD7002_read_reg_dlc4_fin(TLD7002_READ_REG_DLC4_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_read_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_read_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_read_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_READ_REG_SYNC]));

    /* set start address to frame */
    frm->write_array[TLD7002_POS_READ_REG_START_ADD] = frm->w_read_reg.StartADDR;
}


/** @brief Validate a READ_REG_DLC4 frame.
 *
 * Validate a READ_REG_DLC4 frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC4_FRAME_t* Reference to READ_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error; TLD7002_FRAME_VAL_CRC8_ERROR: CRC8 error in DATA; ]
 */
/* Implements DD-SWA-288 */
uint8 TLD7002_read_reg_dlc4_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC4_FRAME_t *frm)
{
    uint8 crc8_data_val = 0;
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* leading slave address + data from POS_READ_REG_DATA0_HB to POS_READ_REG_DLC4_SAFETY_BYTE-1 */
    crc8_data_val = TLD7002_calculate_crc8_leadbyte(&(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]),
                    TLD7002_POS_READ_REG_DLC4_SAFETY_BYTE - TLD7002_POS_READ_REG_DATA0_HB,
                    frm->write_array[TLD7002_POS_READ_REG_START_ADD]);

    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_read_reg.frame_termination.OST), &(frm->r_read_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_read_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* check for CRC8 error of data */
    if(crc8_data_val != frm->r_read_reg.SAFETY_BYTE)
    {
        return TLD7002_FRAME_VAL_CRC8_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a READ_REG_DLC5 frame.
 *
 * Preparing of a READ_REG (DLC5: 12 words / 24 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC5_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-289 */
boolean TLD7002_read_reg_dlc5_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC5_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_read_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;									/*< CRC initially 0 */
        frm->w_read_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_READ_REG;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_5;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a READ_REG_DLC5 frame.
 *
 * Finalize a READ_REG_DLC5 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_READ_REG_DLC5_FRAME_t* Reference to READ_REG frame instance
 */
/* Implements DD-SWA-290 */
void TLD7002_read_reg_dlc5_fin(TLD7002_READ_REG_DLC5_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_read_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_read_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_read_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_READ_REG_SYNC]));

    /* set start address to frame */
    frm->write_array[TLD7002_POS_READ_REG_START_ADD] = frm->w_read_reg.StartADDR;
}

/** @brief Validate a READ_REG_DLC5 frame.
 *
 * Validate a READ_REG_DLC5 frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC1_FRAME_t* Reference to READ_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error; TLD7002_FRAME_VAL_CRC8_ERROR: CRC8 error in DATA; ]
 */
/* Implements DD-SWA-291 */
uint8 TLD7002_read_reg_dlc5_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC5_FRAME_t *frm)
{
    uint8 crc8_data_val = 0;
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* leading slave address + data from POS_READ_REG_DATA0_HB to POS_READ_REG_DLC5_SAFETY_BYTE-1 */
    crc8_data_val = TLD7002_calculate_crc8_leadbyte(&(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]),
                    TLD7002_POS_READ_REG_DLC5_SAFETY_BYTE - TLD7002_POS_READ_REG_DATA0_HB,
                    frm->write_array[TLD7002_POS_READ_REG_START_ADD]);

    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_read_reg.frame_termination.OST), &(frm->r_read_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_read_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* check for CRC8 error of data */
    if(crc8_data_val != frm->r_read_reg.SAFETY_BYTE)
    {
        return TLD7002_FRAME_VAL_CRC8_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a READ_REG_DLC6 frame.
 *
 * Preparing of a READ_REG (DLC6: 16 words / 32 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC6_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-292 */
boolean TLD7002_read_reg_dlc6_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC6_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_read_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;									/*< CRC initially 0 */
        frm->w_read_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_READ_REG;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_6;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a READ_REG_DLC6 frame.
 *
 * Finalize a READ_REG_DLC6 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_READ_REG_DLC6_FRAME_t* Reference to READ_REG frame instance
 */
/* Implements DD-SWA-293 */
void TLD7002_read_reg_dlc6_fin(TLD7002_READ_REG_DLC6_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_read_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_read_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_read_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_READ_REG_SYNC]));

    /* set start address to frame */
    frm->write_array[TLD7002_POS_READ_REG_START_ADD] = frm->w_read_reg.StartADDR;
}


/** @brief Validate a READ_REG_DLC6 frame.
 *
 * Validate a READ_REG_DLC6 frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC6_FRAME_t* Reference to READ_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error; TLD7002_FRAME_VAL_CRC8_ERROR: CRC8 error in DATA; ]
 */
/* Implements DD-SWA-294 */
uint8 TLD7002_read_reg_dlc6_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC6_FRAME_t *frm)
{
    uint8 crc8_data_val = 0;
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* leading slave address + data from POS_READ_REG_DATA0_HB to POS_READ_REG_DLC6_SAFETY_BYTE-1 */
    crc8_data_val = TLD7002_calculate_crc8_leadbyte(&(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]),
                    TLD7002_POS_READ_REG_DLC6_SAFETY_BYTE - TLD7002_POS_READ_REG_DATA0_HB,
                    frm->write_array[TLD7002_POS_READ_REG_START_ADD]);

    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_read_reg.frame_termination.OST), &(frm->r_read_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_read_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* check for CRC8 error of data */
    if(crc8_data_val != frm->r_read_reg.SAFETY_BYTE)
    {
        return TLD7002_FRAME_VAL_CRC8_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/** @brief Prepare a READ_REG_DLC7 frame.
 *
 * Preparing of a READ_REG (DLC7: 32 words / 64 bytes) frame.
 * This functions prepares a frame by generating the content of the frame header.
 * Therefore at first the it is checked, if the slave address is valid for that
 * frame.
 * Afterwards the header is generated by setting the SYNC byte, the ADDRESS,
 * the FUN field, the DLC field and the MRC as well as resetting the CRC3 field.
 * Additionally the slave and master rolling counters in the instance are
 * updated.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC7_FRAME_t* Reference to READ_REG frame instance
 * @param[in] uint8 address of slave where the frame has to be send [FRAME_SLAVE_ADDRESS_BROADCAST ... FRAME_SLAVE_ADDRESS_31]
 *
 * @return preparation of a frame [TRUE: preparation of a frame successful; FALSE: preparation of a frame not successful]
 */
/* Implements DD-SWA-295 */
boolean TLD7002_read_reg_dlc7_prep(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC7_FRAME_t *frm, uint8 add)
{
    boolean ret_val = FALSE;																/*< initially return value FALSE */
    if(add <= TLD7002_FRAME_SLAVE_ADDRESS_31)  												/*< valid addresses: TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST ... TLD7002_FRAME_SLAVE_ADDRESS_31 */
    {
        ret_val = TRUE;																		/*< address is valid */
        frm->w_read_reg.frame_header.SYNC = TLD7002_FRAME_SYNC_MSG;							/* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS = add;
        frm->w_read_reg.frame_header.CRC_REQ_S_ADD.CRC = 0;									/*< CRC initially 0 */
        frm->w_read_reg.frame_header.MRC_DLC_FUN.FUN = TLD7002_FRAME_FUN_READ_REG;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.DLC = TLD7002_FRAME_DLC_7;
        frm->w_read_reg.frame_header.MRC_DLC_FUN.MRC = inst->curr_master_rc;				/*< set MRC */ /* polyspace MISRA-C3:D4.14 [Justified:Low] "The validity of this pointer cannot be checked because the memory layout is not known. The user of the API has to ensure that the correct pointer to the high level API is passed." */
        frm->timeout = FALSE;																/*< reset timeout */
        frm->slave_rc = 0U;																	/*< reset slave rolling counter for frame */
        inst->curr_master_rc = TLD7002_get_next_rc_val(inst->curr_master_rc);				/*< calculate next Slave Rolling Counter */
        if(add != TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)  									/*< only for messages which are not broadcast messages (would lead to two times increasing MRC) */
        {
            frm->slave_rc = inst->curr_slave_rc[add - 1];										/*< set expected slave rolling counter */
            inst->curr_slave_rc[add - 1] = TLD7002_get_next_rc_val(inst->curr_slave_rc[add - 1]);	/*< calculate expected Rolling Counter for answer */
        }
    }
    return ret_val;
}


/** @brief Finalize a READ_REG_DLC7 frame.
 *
 * Finalize a READ_REG_DLC7 frame.
 * This functions finalizes a frame by copying data in the frame write_array
 * (if not already done) as well as calculating the CRC3 for the MRC_DLC_FUN
 * byte and calculating the CRC8 in order to store it in the SAFETY_BYTE (if
 * applicable) and write this to the write_array too.
 *
 * @param[in] TLD7002_READ_REG_DLC7_FRAME_t* Reference to READ_REG frame instance
 */
/* Implements DD-SWA-296 */
void TLD7002_read_reg_dlc7_fin(TLD7002_READ_REG_DLC7_FRAME_t *frm)
{
    TLD7002_calculate_crc3_master_request(&(frm->w_read_reg.frame_header.CRC_REQ_S_ADD),
                                          &(frm->w_read_reg.frame_header.MRC_DLC_FUN));

    /* generate write array content for frame transmission */
    TLD7002_generate_master_request_header(&(frm->w_read_reg.frame_header),
                                           &(frm->write_array[TLD7002_POS_READ_REG_SYNC]));

    /* set start address to frame */
    frm->write_array[TLD7002_POS_READ_REG_START_ADD] = frm->w_read_reg.StartADDR;
}

/** @brief Validate a READ_REG_DLC7 frame.
 *
 * Validate a READ_REG_DLC7 frame answer.
 * This functions validates the the slave response. In this basic frame
 * validation Rolling Counter, CRC or data handling Errors can be recognized.
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param[in] TLD7002_READ_REG_DLC7_FRAME_t* Reference to READ_REG frame instance
 *
 * @return detected error in validation [TLD7002_FRAME_VAL_NO_ERROR: no error detected; TLD7002_FRAME_VAL_CRC3_ERROR: CRC3 error in ACK_BYTE; TLD7002_FRAME_VAL_RC_ERROR: rolling counter error; TLD7002_FRAME_VAL_CRC8_ERROR: CRC8 error in DATA; ]
 */
/* Implements DD-SWA-297 */
uint8 TLD7002_read_reg_dlc7_val_resp(TLD7002_NetworkInstance_t *inst, TLD7002_READ_REG_DLC7_FRAME_t *frm)
{
    uint8 crc8_data_val = 0;
    /* a broadcast message cannot be validated -> abort function and return TLD7002_FRAME_VAL_BROADCAST_ERROR */
    if(frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS == TLD7002_FRAME_SLAVE_ADDRESS_BROADCAST)
    {
        return TLD7002_FRAME_VAL_BROADCAST_ERROR;
    }
    /* leading slave address + data from POS_READ_REG_DATA0_HB to POS_READ_REG_DLC7_SAFETY_BYTE-1 */
    crc8_data_val = TLD7002_calculate_crc8_leadbyte(&(frm->read_array[TLD7002_POS_READ_REG_DATA0_HB]),
                    TLD7002_POS_READ_REG_DLC7_SAFETY_BYTE - TLD7002_POS_READ_REG_DATA0_HB,
                    frm->write_array[TLD7002_POS_READ_REG_START_ADD]);

    /* check for CRC3 error */
    if(FALSE == TLD7002_calculate_crc3_slave_response(&(frm->r_read_reg.frame_termination.OST), &(frm->r_read_reg.frame_termination.ACK)))
    {
        return TLD7002_FRAME_VAL_CRC3_ERROR;
    }
    /* check for Rolling Counter Error */
    TLD7002_FRAME_ACK_BYTE_t temp_ack;
    temp_ack = frm->r_read_reg.frame_termination.ACK;										/*< store ACK byte temporary */
    if(temp_ack.RC != frm->slave_rc)  														/*< check if received rolling counter equals the expected rolling counter */
    {
        /* correct automatically device rolling counter alignment to the received one */
        inst->curr_slave_rc[frm->w_read_reg.frame_header.CRC_REQ_S_ADD.ADDRESS - 1] = TLD7002_get_next_rc_val(temp_ack.RC);
        frm->slave_rc = temp_ack.RC;
        return TLD7002_FRAME_VAL_RC_ERROR;
    }
    /* check for CRC8 error of data */
    if(crc8_data_val != frm->r_read_reg.SAFETY_BYTE)
    {
        return TLD7002_FRAME_VAL_CRC8_ERROR;
    }
    /* no error detected */
    return TLD7002_FRAME_VAL_NO_ERROR;
}


/******************************************************************************/
/* Auxiliary function implementation	 									  */
/******************************************************************************/

/** @brief TLD7002 Device Driver initialization function
 *
 * This functions performs the required initialization tasks for the TLD7002
 * Device Driver network and has to be executed only one time.
 * Tasks:
 *   - reset master rolling counter
 *   - reset slave rolling counters
 *
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 */
/* Implements DD-SWA-321 */
void TLD7002_init_network(TLD7002_NetworkInstance_t *inst)
{
    /* reset master rolling counter to initial values */
    inst->curr_master_rc = TLD7002_FRAME_RC_2BIT_0;

    /* reset slave rolling counters to initial values */
    for(uint8 index = 0; index < TLD7002_NUM_DEVICES - 1; index++)
    {
        inst->curr_slave_rc[index] = TLD7002_FRAME_RC_2BIT_0;
    }
}


/** @brief Generate next Rolling Counter value
 *
 * This functions returns the next Rolling Counter, a 2 bit counter value, which the master needs to increment in
 *  every data transmission starting from 0x00 default (start) value.
 *
 * @param[in] uint8 mrc. current MRC value [FRAME_RC_2BIT_START_VALUE, FRAME_RC_2BIT_0 ... FRAME_RC_2BIT_3]
 *
 * @return uint8 next RC value
 */
/* Implements DD-SWA-322 */
uint8 TLD7002_get_next_rc_val(uint8 mrc)
{
    uint8 nextMrc = TLD7002_FRAME_RC_2BIT_START_VALUE;		/*< initialize return value */

    switch(mrc)  											/*< switch current RC value */
    {
        case TLD7002_FRAME_RC_2BIT_0:						/*< TLD7002_FRAME_RC_2BIT_0 (TLD7002_FRAME_RC_2BIT_START_VALUE) -> TLD7002_FRAME_RC_2BIT_1 */
            nextMrc = TLD7002_FRAME_RC_2BIT_1;
            break;
        case TLD7002_FRAME_RC_2BIT_1:						/*< TLD7002_FRAME_RC_2BIT_1 -> TLD7002_FRAME_RC_2BIT_2 */
            nextMrc = TLD7002_FRAME_RC_2BIT_2;
            break;
        case TLD7002_FRAME_RC_2BIT_2:						/*< TLD7002_FRAME_RC_2BIT_2 -> TLD7002_FRAME_RC_2BIT_3 */
            nextMrc = TLD7002_FRAME_RC_2BIT_3;
            break;
        case TLD7002_FRAME_RC_2BIT_3:						/*< TLD7002_FRAME_RC_2BIT_3 -> TLD7002_FRAME_RC_2BIT_0 */
            nextMrc = TLD7002_FRAME_RC_2BIT_0;
            break;
        default:											/* do nothing */
            break;
    }
    return nextMrc;
}


/** @brief Calculate CRC3 of the master request
 *
 * This functions calculates the CRC3 of master request over the Address, MRC, DLC and FUN.
 *
 * @param[in] TLD7002_FRAME_CRC_ADDRESS_t* pointer to CRC_REQ_S_ADD byte of frame
 * @param[in] TLD7002_FRAME_MRC_DLC_FUN_t* pointer to MRC_DLC_FUN byte of frame
 *
 */
/* Implements DD-SWA-323 */
void TLD7002_calculate_crc3_master_request(TLD7002_FRAME_CRC_ADDRESS_t *byte_req_s_add, TLD7002_FRAME_MRC_DLC_FUN_t *byte_mrc_dlc_fun)
{
    uint8 crc = TLD7002_CRC3_CALC_SEED;
    uint8 crc_address_byte = 	((byte_req_s_add->ADDRESS << TLD7002_CRC_ADDRESS_ADDRESS_POS) & TLD7002_CRC_ADDRESS_ADDRESS_MSK);
    uint8 mrc_dlc_fun_byte = 0;
    mrc_dlc_fun_byte |= 		((byte_mrc_dlc_fun->MRC << TLD7002_MRC_DLC_FUN_MRC_POS) & TLD7002_MRC_DLC_FUN_MRC_MSK) |
                                ((byte_mrc_dlc_fun->DLC << TLD7002_MRC_DLC_FUN_DLC_POS) & TLD7002_MRC_DLC_FUN_DLC_MSK) |
                                ((byte_mrc_dlc_fun->FUN << TLD7002_MRC_DLC_FUN_FUN_POS) & TLD7002_MRC_DLC_FUN_FUN_MSK);
    crc = TLD7002_LOOKUP_CRC3_5BIT[crc ^ (crc_address_byte & 0x1FU)];				/*< CRC of lower 5 bits */
    crc = TLD7002_MIRROR_MID_CRC3[crc];												/*< get reflected CRC3 value */
    crc = TLD7002_LOOKUP_CRC3_8BIT[crc ^ mrc_dlc_fun_byte];							/*< get reflected CRC3 value */
    byte_req_s_add->CRC = crc;
}


/** @brief Check CRC3 of the slave response
 *
 * This functions calculates the CRC3 of slave response over the output status byte, MODE, RC and TER.
 *
 * @param[in] TLD7002_FRAME_OUTPUT_STATUS_BYTE_t* pointer to OST of frame
 * @param[in] TLD7002_FRAME_ACK_BYTE_t* pointer to ACK byte of frame
 *
 * @return boolean [TRUE: crc value is correct; FALSE: crc value is not correct]
 *
 */
/* Implements DD-SWA-324 */
boolean TLD7002_calculate_crc3_slave_response(TLD7002_FRAME_OUTPUT_STATUS_BYTE_t *byte_ost, TLD7002_FRAME_ACK_BYTE_t *byte_ack)
{
    boolean crc_correct = FALSE;													/*< initially CRC is not correct */
    uint8 crc = TLD7002_CRC3_CALC_SEED;
    uint8 ost_byte = 0;
    uint8 ack_byte = 0;

    ost_byte |=		((uint8)(byte_ost->OSB_FAULT) 		<< TLD7002_OUTPUT_STATUS_BYTE_FAULT_POS) |
                    ((uint8)(byte_ost->OVLD) 			<< TLD7002_OUTPUT_STATUS_BYTE_OVLD_POS) |
                    ((uint8)(byte_ost->VFWD_WRN) 		<< TLD7002_OUTPUT_STATUS_BYTE_VFWD_WRN_POS) |
                    ((uint8)(byte_ost->CUR_WRN) 		<< TLD7002_OUTPUT_STATUS_BYTE_CUR_WRN_POS) |
                    ((uint8)(byte_ost->DC_WRN) 			<< TLD7002_OUTPUT_STATUS_BYTE_DC_WRN_POS) |
                    ((uint8)(byte_ost->GPINn_WRN) 		<< TLD7002_OUTPUT_STATUS_BYTE_GPINn_WRN_POS) |
                    ((uint8)(byte_ost->OUT_SHRT_WRN)	<< TLD7002_OUTPUT_STATUS_BYTE_OUT_SHRT_WRN_POS) |
                    ((uint8)(byte_ost->VLED_VS_UV) 		<< TLD7002_OUTPUT_STATUS_BYTE_VLED_VS_UV_POS);

    ack_byte |= 	((uint8)(byte_ack->TER)  			<< TLD7002_ACK_BYTE_TER_POS) |
                    ((uint8)(byte_ack->RC)   			<< TLD7002_ACK_BYTE_RC_POS) |
                    ((uint8)(byte_ack->MODE) 			<< TLD7002_ACK_BYTE_MODE_POS);

    crc = TLD7002_LOOKUP_CRC3_8BIT[crc ^ ost_byte];
    crc = TLD7002_MIRROR_MID_CRC3[crc];												/*< get reflected CRC3 value */
    crc = TLD7002_LOOKUP_CRC3_5BIT[crc ^ (ack_byte & 0x1FU)];						/*< CRC of lower 5 bits */
    crc_correct = crc == byte_ack->CRC ? TRUE : FALSE;								/* Check if CRC is correct */
    return crc_correct;
}


/** @brief Calculate CRC8 in general
 *
 * This functions calculates the CRC8 based on the 8-SAE J1850 algorithm.
 * Here the possibility of using a lookup table or calculation variant is provided.
 *
 * @param[in] uint8* pointer to data_array
 * @param[in] uint8 length of data array [0 ... 255]
 *
 * @return uint8 calculated CRC8 [0 ... 255]
 */
/* Implements DD-SWA-325 */
uint8 TLD7002_calculate_crc8_general(uint8 *data_array, uint8 data_len)
{
    uint8 crc = TLD7002_CRC8_CALC_SEED;												/* CRC initial value */
    uint8 index = 0;
#if (TLD7002_CRC8_CONF_ALGORITHM == TLD7002_CRC8_USE_LUT)
    /* CRC-8-SAE J1850 algorithm */
    /* all elements of the data array */
    for (index = 0; index < data_len; index++)
    {
        /* use data bytes */
        crc = TLD7002_LOOKUP_CRC8_SAE_J1850[crc ^ data_array[index]];
    }
#elif (TLD7002_CRC8_CONF_ALGORITHM == TLD7002_CRC8_USE_CALC)
    uint8 bit = 0U;
    /* CRC-8-SAE J1850 algorithm */
    /* all elements of the data array */
    for (index = 0; index < data_len; index++)
    {
        /* use data bytes */
        crc ^= data_array[index];

        for(bit = 0; bit < 8; bit++)
        {
            if ((crc & 0x80U) != 0U)
            {
                crc <<= 1U;
                crc ^= TLD7002_CRC8_CALC_GENERATOR_POLYNOM;
            }
            else
            {
                crc <<= 1U;
            }
        }
    }
#endif
    crc = crc ^ TLD7002_CRC8_CALC_XOR_VAL;											/* write CRC into SAFETY_BYTE */
    return crc;
}


/** @brief Calculate CRC8 with leading byte
 *
 * This functions calculates the CRC8 based on the 8-SAE J1850 algorithm adding
 * an additional byte (leading byte) at the beginning.
 * This means the CRC is calculated for: lead_byte; data_array[0];
 * data_array[1]; data_array[2]; data_array[3]; ... data_array[255]
 * Here the possibility of using a lookup table or calculation variant is provided.
 *
 * @param[in] uint8* pointer to data_array
 * @param[in] uint8 length of data array [0 ... 255]
 * @param[in] uint8 leading byte [0 ... 255]
 *
 * @return uint8 calculated CRC8 [0 ... 255]
 */
/* Implements DD-SWA-326 */
uint8 TLD7002_calculate_crc8_leadbyte(uint8 *data_array, uint8 data_len, uint8 lead_byte)
{
    uint8 crc = TLD7002_CRC8_CALC_SEED;												/* CRC initial value */
    uint8 index = 0U;
#if (TLD7002_CRC8_CONF_ALGORITHM == TLD7002_CRC8_USE_LUT)
    /* CRC-8-SAE J1850 algorithm for first element (lead_byte) */
    crc = TLD7002_LOOKUP_CRC8_SAE_J1850[crc ^ lead_byte];

    /* CRC-8-SAE J1850 algorithm */
    /* all elements of the data array */
    for (index = 0; index < data_len; index++)
    {
        /* use data bytes */
        crc = TLD7002_LOOKUP_CRC8_SAE_J1850[crc ^ data_array[index]];
    }

#elif (TLD7002_CRC8_CONF_ALGORITHM == TLD7002_CRC8_USE_CALC)
    uint8 bit = 0U;
    /* CRC-8-SAE J1850 algorithm for first element (lead_byte) */
    crc ^= lead_byte;

    for(bit = 0; bit < 8; bit++)
    {
        if ((crc & 0x80U) != 0U)
        {
            crc <<= 1U;
            crc ^= TLD7002_CRC8_CALC_GENERATOR_POLYNOM;
        }
        else
        {
            crc <<= 1U;
        }
    }

    /* CRC-8-SAE J1850 algorithm for data array */
    /* all elements of the data array */
    for (index = 0; index < data_len; index++)
    {
        /* use data bytes */
        crc ^= data_array[index];

        for(bit = 0; bit < 8; bit++)
        {
            if ((crc & 0x80U) != 0U)
            {
                crc <<= 1U;
                crc ^= TLD7002_CRC8_CALC_GENERATOR_POLYNOM;
            }
            else
            {
                crc <<= 1U;
            }
        }
    }
#endif
    crc = crc ^ TLD7002_CRC8_CALC_XOR_VAL;				/* write CRC into SAFETY_BYTE */
    return crc;
}


/** @brief Generate the write array header frame content of the master request
 *
 * This functions generates the master request  header (Sync, Address, MRC, DLC,
 * FUN and CRC3) out of the frame header.
 *
 * @param[in] TLD7002_FRAME_HEADER_t* pointer frame header of frame
 * @param[in] uint8* pointer to write_array of frame
 */
/* Implements DD-SWA-327 */
void TLD7002_generate_master_request_header(TLD7002_FRAME_HEADER_t *header, uint8 *w_array)
{
    /* set element [0] */
    *w_array = header->SYNC;

    /* set element [1] */
    *(w_array + 1) = 0;
    *(w_array + 1) |= 	((header->CRC_REQ_S_ADD.CRC << TLD7002_CRC_ADDRESS_CRC_POS) & TLD7002_CRC_ADDRESS_CRC_MSK) |
                        ((header->CRC_REQ_S_ADD.ADDRESS << TLD7002_CRC_ADDRESS_ADDRESS_POS) &
                         TLD7002_CRC_ADDRESS_ADDRESS_MSK);

    /* set element [2] */
    *(w_array + 2) = 0;
    *(w_array + 2) |=	((header->MRC_DLC_FUN.MRC << TLD7002_MRC_DLC_FUN_MRC_POS) & TLD7002_MRC_DLC_FUN_MRC_MSK) |
                        ((header->MRC_DLC_FUN.DLC << TLD7002_MRC_DLC_FUN_DLC_POS) & TLD7002_MRC_DLC_FUN_DLC_MSK) |
                        ((header->MRC_DLC_FUN.FUN << TLD7002_MRC_DLC_FUN_FUN_POS) & TLD7002_MRC_DLC_FUN_FUN_MSK);
}


/** @brief This functions configures the duty cycle value in the parameter to a given frame.
 *
 * This functions configures the duty cycle value in the parameter to a given
 * frame. It additionally provides the possibility to use Linear/Logarithmic
 * Lookup table (gamma correction)
 *
 * @param[in] TLD7002_DC_UPDATE_8BIT_FRAME_t* pointer to frame where the duty cycle should be stored
 * @param[in] uint8 channel where the duty cycle should be configured [TLD7002_CH0 ... TLD7002_CH15]
 * @param[in] uint8 duty cycle value [CH_MIN_DC_VAL ... CH_MAX_DC_8BIT_VAL]
 */
/* Implements DD-SWA-328 */
void TLD7002_setChDc8BitToFrame(TLD7002_DC_UPDATE_8BIT_FRAME_t *updtfram, uint8 ch, uint8 dc_val)
{

#if (TLD7002_DC_UPDATE_8_BIT_CONF == TLD7002_DC_UPDATE_8_BIT_LINEAR_CONF)
    dc_val = TLD7002_LOOKUP_LIN_DC_8BIT[dc_val];		/*< get logarithmic intensity value */
#endif

    switch(ch) 											/*< decide between channels and set duty cycle to frame and write_array */
    {
        case TLD7002_CH0:
            updtfram->w_pwm_dc_update.DutyCycleOUT0 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT0] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH1:
            updtfram->w_pwm_dc_update.DutyCycleOUT1 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT1] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH2:
            updtfram->w_pwm_dc_update.DutyCycleOUT2 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT2] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH3:
            updtfram->w_pwm_dc_update.DutyCycleOUT3 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT3] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH4:
            updtfram->w_pwm_dc_update.DutyCycleOUT4 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT4] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH5:
            updtfram->w_pwm_dc_update.DutyCycleOUT5 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT5] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH6:
            updtfram->w_pwm_dc_update.DutyCycleOUT6 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT6] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH7:
            updtfram->w_pwm_dc_update.DutyCycleOUT7 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT7] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH8:
            updtfram->w_pwm_dc_update.DutyCycleOUT8 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT8] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH9:
            updtfram->w_pwm_dc_update.DutyCycleOUT9 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT9] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH10:
            updtfram->w_pwm_dc_update.DutyCycleOUT10 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT10] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH11:
            updtfram->w_pwm_dc_update.DutyCycleOUT11 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT11] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH12:
            updtfram->w_pwm_dc_update.DutyCycleOUT12 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT12] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH13:
            updtfram->w_pwm_dc_update.DutyCycleOUT13 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT13] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH14:
            updtfram->w_pwm_dc_update.DutyCycleOUT14 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT14] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        case TLD7002_CH15:
            updtfram->w_pwm_dc_update.DutyCycleOUT15 = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            updtfram->write_array[TLD7002_POS_DC_UPDATE_8BIT_DCOUT15] = dc_val & TLD7002_CH_MAX_DC_8BIT_VAL;
            break;
        default:											/* do nothing */
            break;
    };
}


/** @brief Set a duty cycle Value of the dc_update (14 Bit) frame
 *
 * This functions configures the duty cycle value in the parameter to a given frame.
 *
 * @param[in] TLD7002_DC_UPDATE_14BIT_FRAME_t* pointer to frame where the duty cycle should be stored
 * @param[in] uint8 channel where the duty cycle should be configured [TLD7002_CH0 ... TLD7002_CH15]
 * @param[in] uint16 duty cycle value [CH_MIN_DC_VAL ... CH_MAX_DC_14BIT_VAL]
 */
/* Implements DD-SWA-329 */
void TLD7002_setChDc14BitToFrame(TLD7002_DC_UPDATE_14BIT_FRAME_t *updtfram, uint8 ch, uint16 dc_val)
{
    switch(ch) 											/*<decide between channels and set duty cycle to frame and write_array */
    {
        case TLD7002_CH0:
            updtfram->w_pwm_dc_update.DutyCycleOUT0 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT0_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT0_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH1:
            updtfram->w_pwm_dc_update.DutyCycleOUT1 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT1_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT1_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH2:
            updtfram->w_pwm_dc_update.DutyCycleOUT2 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT2_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT2_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH3:
            updtfram->w_pwm_dc_update.DutyCycleOUT3 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT3_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT3_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH4:
            updtfram->w_pwm_dc_update.DutyCycleOUT4 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT4_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT4_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH5:
            updtfram->w_pwm_dc_update.DutyCycleOUT5 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT5_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT5_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH6:
            updtfram->w_pwm_dc_update.DutyCycleOUT6 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT6_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT6_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH7:
            updtfram->w_pwm_dc_update.DutyCycleOUT7 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT7_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT7_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH8:
            updtfram->w_pwm_dc_update.DutyCycleOUT8 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT8_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT8_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH9:
            updtfram->w_pwm_dc_update.DutyCycleOUT9 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT9_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT9_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH10:
            updtfram->w_pwm_dc_update.DutyCycleOUT10 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT10_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT10_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH11:
            updtfram->w_pwm_dc_update.DutyCycleOUT11 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT11_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT11_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH12:
            updtfram->w_pwm_dc_update.DutyCycleOUT12 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT12_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT12_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH13:
            updtfram->w_pwm_dc_update.DutyCycleOUT13 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT13_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT13_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH14:
            updtfram->w_pwm_dc_update.DutyCycleOUT14 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT14_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT14_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        case TLD7002_CH15:
            updtfram->w_pwm_dc_update.DutyCycleOUT15 = (dc_val & TLD7002_DC_UPDATE_14BITDCVAL_DUTY_CYCLE_MSK);						/*< copy data element */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT15_LB] = (uint8)(dc_val & TLD7002_LOW_BYTE_16BIT);				/*< copy data element LSB */
            updtfram->write_array[TLD7002_POS_DC_UPDATE_14BIT_DCOUT15_HB] = (uint8)((dc_val & TLD7002_HIGH_BYTE_14BIT) >> 8U);		/*< copy data element MSB */
            break;
        default:											/* do nothing */
            break;
    };
}


/** @brief Calculate 8 Bit duty cycle value.
 *
 * Calculate 8 Bit duty cycle value from given duty cycle in percent.
 *
 * @param[in] uint16 duty cycle [0.00 %: 0 - 100.00%: 10000]
 *
 * @return uint8 duty cycle 8 bit value
 */
/* Implements DD-SWA-330 */
uint8 TLD7002_calcChDc8BitValue(uint16 dc_perc)
{
    uint8 ret_val = 0;								/*< variable to store the value to be returned */
    uint32 dc_val = 0;								/*< variable to store calculated DC value */
    if(dc_perc == TLD7002_CH_MIN_DUTY_CYCLE)   		/*< for 0 percent duty cycle -> set to minimum value (avoid errors in rounding) */
    {
        ret_val = TLD7002_CH_MIN_DC_VAL;
    }
    else if(dc_perc == TLD7002_CH_MAX_DUTY_CYCLE)   /*< for 100 percent duty cycle -> set to minimum value (avoid errors in rounding) */
    {
        ret_val = TLD7002_CH_MAX_DC_8BIT_VAL;
    }
    else  										 	/*< for all other values the duty cycle is calculated */
    {
        dc_val = (uint32)TLD7002_CH_MAX_DC_8BIT_VAL << TLD7002_SHIFT16;		/*< extend the data-width for 100 % duty cycle */
        dc_val /= TLD7002_CH_MAX_DUTY_CYCLE;		/*< divide by the maximum value for the duty cycle to get the extended value for 1 % duty cycle */
        dc_val *= dc_perc;							/*< multiply with the duty cycle value from the parameter */
        dc_val = dc_val >> TLD7002_SHIFT16;			/*< shrink data with to get final data word */
        ret_val = (uint8)(dc_val & TLD7002_CH_MAX_DC_8BIT_VAL);				/*< set the calculated DC value to return value */
    }
    return ret_val;
}


/** @brief Calculate 14 Bit duty cycle value.
 *
 * Calculate 14 Bit duty cycle value from given duty cycle in percent.
 *
 * @param[in] uint16 duty cycle [0.00 %: 0 - 100.00%: 10000]
 *
 * @return uint16 duty cycle 14 bit value
 */
/* Implements DD-SWA-331 */
uint16 TLD7002_calcChDc14BitValue(uint16 dc_perc)
{
    uint16 ret_val = 0;								/*< variable to store the value to be returned */
    uint32 dc_val = 0;								/*< variable to store calculated DC value */
    if(dc_perc == TLD7002_CH_MIN_DUTY_CYCLE)   		/*< for 0 percent duty cycle -> set to minimum value (avoid errors in rounding) */
    {
        ret_val = TLD7002_CH_MIN_DC_VAL;
    }
    else if(dc_perc == TLD7002_CH_MAX_DUTY_CYCLE)   /*< for 100 percent duty cycle -> set to minimum value (avoid errors in rounding) */
    {
        ret_val = TLD7002_CH_MAX_DC_14BIT_VAL;
    }
    else  										 	/*< for all other values the duty cycle is calculated */
    {
        dc_val = (uint32)TLD7002_CH_MAX_DC_14BIT_VAL << TLD7002_SHIFT16;	/*< extend the data-width for 100 % duty cycle */
        dc_val /= TLD7002_CH_MAX_DUTY_CYCLE;		/*< divide by the maximum value for the duty cycle to get the extended value for 1 % duty cycle */
        dc_val *= dc_perc;							/*< multiply with the duty cycle value from the parameter */
        dc_val = dc_val >> TLD7002_SHIFT16;			/*< shrink data with to get final data word */
        ret_val = (uint16)(dc_val & TLD7002_CH_MAX_DC_14BIT_VAL);				/*< set the calculated DC value to return value */
    }
    return ret_val;
}


/**@}*/