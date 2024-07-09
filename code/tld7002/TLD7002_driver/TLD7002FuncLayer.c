/**
 *  @file TLD7002FuncLayer.cpp
 *  @author Infineon
 *  @date 03.08.2022
 *	@brief Functional layer, which provide simplified access to the TLD7002-16 device drivers
 *   It combines several calls to the TLD7002-16 device Drivers in order to perform  complex functionalities like:
 *   OTP emulation/write , NTC readings , VLED & VS reading, Diagnostic reading and so on
 *   without the needs for the user to understand the TLD7002-16 registers bitfields.
 *
 **********************************************************************************************************************
 *
 * Copyright (c) 2022, Infineon Technologies AG
 * All rights reserved.
 *
 **********************************************************************************************************************
*/

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "TLD7002FuncLayer.h"
#include "zf_driver_delay.h"

/*******************************************************************************
**                         Global Variable Definitions                        **
*******************************************************************************/
/* gBuffTxRx : buffer used from the Device driver to store HSLI tx/rx frames, TLD7002_READ_OST_FRAME_t is the Longest
 * HSLI frame this buffer is used instead of multiple specific frame structures requested by the device drivers, (one per
 * frame type) due to the low memory avaible on Arduino UNO. TLD7002_READ_OST_FRAME_t is the biggest frame + 5 bytes
   of padding */
char gBuffTxRx [sizeof (TLD7002_READ_OST_FRAME_t) +5];

#define max(a, b)               ((a)>(b)?a:b)

#define TLD7002_HSLI_SPEED_BPS  (1000000)  /* acceptable down to 20kbps, even if datasheet states 200kbps, when setting very low speed
                                          interframe delay has to be extended (or all bit = 1 will be read as an interframe delay)*/
#define TLD7002_BYTE_TIME_uS    (((8 + 2) * 1000000) / TLD7002_HSLI_SPEED_BPS)

extern void    tld7002_send_buffer             (uint8 *buffer, uint32 length);
extern boolean tld7002_read_buffer             (uint8 *buffer, uint32 length);
extern void    tld7002_clean_buffer            (void);
extern void    tld7002_gpin0_set_level         (uint8 state);

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

/* @brief: TLD7002initDrivers initialize TLD7002-16 Device Drivers (but not the TLD7002-16 device itself)
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 */
void TLD7002initDrivers(TLD7002_NetworkInstance_t *HSLInetwork)
{
    /* initialize serial pin and speed that will be used for TLD7002-16 control */
    HSLInetwork->trx_function = tld7002_send_buffer;
    HSLInetwork->rcv_function = tld7002_read_buffer;
    HSLInetwork->rcv_empty_buffer = tld7002_clean_buffer;
    /* initialize Device Drivers ( not initializing the device TLD7002-16 itself, but only the Device Drivers) by providing
      HW specific function pointers  */
    TLD7002_InitNetworkInstance(HSLInetwork);
}

/**
 * @brief TLD7002initDevice functions initialize the TLD7002-16ES device and set it to Active mode (ready to turn ON the
 * outputs) it clears also eventual error flags
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @return: error on the initialization
 */
enum TLDerr TLD7002initDevice(TLD7002_NetworkInstance_t *HSLInetwork, uint8 add )
{
    uint8       trxRes;      // stores HSLI transmission result
    enum TLDerr err = NO_ERR;

    /* send PM change to INIT twice, to syncronize Device driver master rolling counter and TLD7002 rolling counter
     * this restore the device to INIT and send DC to 0, ready for next command*/
    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, add, TLD7002_FRAME_PM_INIT_MODE);
    system_delay_us(INTERFR_DELAY);
    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, add, TLD7002_FRAME_PM_INIT_MODE);/*send cmd twice to sync MRC*/
    system_delay_us(tFAILSAFE2INIT); /* wait > FAILSAFE2INIT, so if the device it was in fail safe, it can move to init*/

    TLD7002_TRX_HWCR_ALL (HSLInetwork, gBuffTxRx,  add);    /* clear all TLD7002 error flags */
    system_delay_us(INTERFR_DELAY);

    // ÅäÖÃ²ÎÊý
    TLD7002_TRX_DC_UPDATE_DLC0(HSLInetwork, gBuffTxRx, add);/* send a DC_UPDATE to move the TLD7002 to active
                                                                        mode & to set all DC to 0 */
    system_delay_us(tINIT2ACTIVE);                                   /* wait for the device to move to ACTIVE */

    trxRes = TLD7002_TRX_DC_UPDATE_DLC0(HSLInetwork, gBuffTxRx, add); /* send a DC_UPDATE with DLC 0 just to,
                                                                          read back the OUTPUT STATUS BYTE diagnostic */
    system_delay_us(INTERFR_DELAY);

    if ( trxRes == TLD7002_FRAME_VAL_NO_ERROR)
    {
        err = TLD7002decodeStdAnswer( ((TLD7002_DC_UPDATE_8BIT_FRAME_t *)gBuffTxRx)->r_pwm_dc_update.frame_termination );
        //    if (err==NO_ERR){
        //      Serial.println("TLD7002-16 device init OK");
        //    }
        //    else{
        //      Serial.println("TLD7002-16 device init ERR");
        //    }
    }
    else
    {
        err = COMM_ERROR; /* communication error  */
        //Serial.print("TLD init Frame Err. Res="); Serial.println(trxRes);
    }
    return err;
}

/*
 * @brief OTP_Write: OTP write PROCEDURE, it permanently write the OTP on the TLD7002-16, and then checks if the OTP is
 * written correctly. The sequence of STEPS and all the delay between steps are as specified in the
 * Infineon-TLD7002-16ES_OTP_programming_procedure-AN-v01_10-EN application note
 * NOTE: OTP can be written only once in a TLD7002-16 device, if OTP write fails, the device is permanently ruined
 * NOTE: test OTP_hex_cfg with emulation in advance
 * NOTE: apply VS_REV in the following range 16V < VS < 20V
 * @global gBuffTxRx - buffer used from the Device driver to store HSLI tx/rx frames
 * @param otp_cfg - TLD7002-16 OTP configuration array, 40 bytes
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param address - address of the TLD7002-16 after OTP write, this has to match to the one set in the otp_cgf array
 * @param newInterfrDelay - TLD7002-16 interframe delay set on the otp_cfg array, this has to match to the one set in the
 *                       otp_cgf array
  */
boolean OTPwrite( uint16 *otp_cfg, TLD7002_NetworkInstance_t *HSLInetwork, uint8 address, uint16 newInterfrDelay  )
{
    uint8 res = TLD7002_FRAME_VAL_NO_ERROR;
    boolean  ret = TRUE;
    boolean  readBackMatch = TRUE;

    //Serial.println("OTP write start");
    tld7002_gpin0_set_level (0); /* ensure GPIN0 is 0 */

    /*  Step1: ensure the device is in INIT mode to enter into OTP mode, before the OTP mode request */
    TLD7002_TX_PM_CHANGE_FRAME(HSLInetwork, (TLD7002_PM_CHANGE_FRAME_t *)gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_INIT_MODE);
    system_delay_us(1005); /* delay counted starting from the last bit transmitted */  //TODO [ALL] magic number

    /* Step2: send command twice to syncronize LLD library master rolling counter and TLD7002 rolling counter */
    TLD7002_TX_PM_CHANGE_FRAME(HSLInetwork, (TLD7002_PM_CHANGE_FRAME_t *)gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_INIT_MODE);
    system_delay_us(1005);

    /* Step3: set interframe delay to 100us(INTERFR_DELAY_OTP_WRITE) by  writing the volatile register TLD7002_HSLI_TIMING_CFG(ADD 0x3B) with 000C */
    TLD7002_TX_WRITE_REG_DLC1_FRAME(HSLInetwork, (TLD7002_WRITE_REG_DLC1_FRAME_t *)gBuffTxRx, BROADCAST_ADDRESS, 0x3B, 0x001C);
    system_delay_us(INTERFR_DELAY_OTP_WRITE); /* delay counted starting from the last bit transmitted */

    /* Step4: set the TLD7002-16 in OTP mode */
    TLD7002_TX_PM_CHANGE_FRAME(HSLInetwork, (TLD7002_PM_CHANGE_FRAME_t *)gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_OTP_MODE);
    system_delay_us(1005); /* delay counted starting from the last bit transmitted */

    /* Step5: set GPIN0 1 to enable programming */  //TODO [ALL] OK? DONE removed old comment
    tld7002_gpin0_set_level (1); /*Set_GPIN0_to_high_value();*/
    system_delay_us(50);

    /* Step6: write OTP Programming passw at address 0x81 */
    TLD7002_TX_WRITE_REG_DLC1_FRAME(HSLInetwork, (TLD7002_WRITE_REG_DLC1_FRAME_t *)gBuffTxRx, BROADCAST_ADDRESS, 0x81, OTP_WRITE_PASSW);
    system_delay_us(INTERFR_DELAY_OTP_WRITE); /* delay counted starting from the last bit transmitted */

    /* Step7: write first 32 words */
    TLD7002_TX_WRITE_REG_DLC7_FRAME(HSLInetwork, (TLD7002_WRITE_REG_DLC7_FRAME_t *)gBuffTxRx, BROADCAST_ADDRESS, 0x83, otp_cfg);
    system_delay_ms(18); /* wait 17,5ms, OTP write is slow, delay counted starting from the last bit transmitted */

    /* Step8: Write last 8 words */
    TLD7002_TX_WRITE_REG_DLC4_FRAME(HSLInetwork, (TLD7002_WRITE_REG_DLC4_FRAME_t *)gBuffTxRx, BROADCAST_ADDRESS, 0xA3, &otp_cfg[32]);
    system_delay_ms(5); /* wait 5ms, OTP write is slow */

    /* Step9: The GPIN0 voltage of the device under programming can be set to low after programming*/
    tld7002_gpin0_set_level (0); /* Set GPIN0 to low_value() according to OTP app note procedure; */
    system_delay_us(INTERFR_DELAY_OTP_WRITE);

    /* Step 10: The device is moved to INIT mode.If the OTP writing procedure ends successfully then the device is
       configured by the new OTP array.*/
    TLD7002_TX_PM_CHANGE_FRAME(HSLInetwork, (TLD7002_PM_CHANGE_FRAME_t *)gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_INIT_MODE);

    system_delay_us(max(newInterfrDelay, 205)); /* delay counted starting from the last bit transmitted, delay shall be:delay > 200us or bigger than the just configured interframe delay */

    /* Step 11: Send HWCR frame to delete the FAULT produced at startup by the unwritten device*/
    TLD7002_TRX_HWCR_ALL (HSLInetwork, gBuffTxRx,  address); /* First TRX command with device address!= broadcast, result
                                         is probably bad becasue roll counter is not sync with Device drivers library */
    system_delay_us(newInterfrDelay); /* wait > new programmed interframe delay */

    /* Step 12  read OTP_STATUS register */
    res = TLD7002_TRX_READ_REG_DLC1(HSLInetwork, gBuffTxRx, address, TLD7002_OTP_STATUS);
    system_delay_us(newInterfrDelay);       /* wait > new programmed interframe delay */
    if ( res == TLD7002_FRAME_VAL_NO_ERROR )  /* if received frame is valid, check the status byte */
    {
        if(  ((TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx)->r_read_reg.Data[0] == 0x03) /* OTP_STATUS as expected for correct OTP write */
        {
            //Serial.println("OTP wr:OTP_STATUS OK = 0x03");
        }
        else
        {
            //Serial.print("OTP wr: err OTP_STATUS=0x");
            //Serial.println(((TLD7002_READ_REG_DLC1_FRAME_t*)gBuffTxRx)->r_read_reg.Data[0],HEX);
            ret = FALSE;
        }
    }
    else
    {
        //Serial.print("OTP wr: Err frame1 res=");
        //Serial.println(res);
        ret = FALSE;
    }

    /* Step13: set the TLD7002-16 in OTP mode */
    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, address, TLD7002_FRAME_PM_OTP_MODE);
    if ( res != TLD7002_FRAME_VAL_NO_ERROR )   /* received frame is valied */
    {
        //Serial.print("OTP wr: Err frame2 res=");
        //Serial.println(res);
        ret = FALSE;
    }
    system_delay_us(newInterfrDelay); /* the interframe shall be counted starting from the last bit transmitted from the
                                          //TLD7002-16 (slave response) */
    /* STEP14 and Step 15: read back the entire OTP, simplified with CMD read 5 times 8 word from the OTP */
    for (int n = 0; n < 5; n++)
    {
        res = TLD7002_TRX_READ_REG_DLC4(HSLInetwork, gBuffTxRx, address, 0x83 + n * 8);
        system_delay_us (newInterfrDelay); /* wait interframe delay after TLD7002-16 answer */

        if ( res == TLD7002_FRAME_VAL_NO_ERROR )
        {
            for (int i = 0; i < 8 ; i++ ) /* lenght of DLC6 is 16 wrd(TLD7002_LEN_WRITE_REG_DLC6_WRITE-TLD7002_LEN_WRITE_REG_OVHD)/2 */
            {
                if ( ((TLD7002_READ_REG_DLC4_FRAME_t *)gBuffTxRx)->r_read_reg.Data[i] != otp_cfg[i + n * 8] ) /* compare readed OTP */
                {
                    /* values with the ones written OTP cfg */
                    //Serial.println("OTP wr: Err read Back Mismatch");
                    ret = FALSE;
                    readBackMatch = FALSE;
                    break;
                }
            }
        }
        else
        {
            //Serial.print("OTP wr: Err readBack frame err res=");
            //Serial.println(res);
            ret = FALSE;
            readBackMatch = FALSE;
            break;
        }
    }
    if (readBackMatch == TRUE)
        //Serial.println("OTP wr: OTP readBack OK");

        /* STEP 16 check output status fault BIT */
        system_delay_us(2 * PWM_PERIOD_uS); /* wait for 2 PWM periods from the last HWCR command, CRC is checked 1 per PWM
                              //period, this is the worst case time needed to highlight CRC errors on the OUTPUT STATUS */
    res = TLD7002_TRX_READ_REG_DLC1(HSLInetwork, gBuffTxRx, address, TLD7002_OTP_STATUS); /* dummy read, just to have the
                                                                                        OUTPUT STATUS byte reply back */
    if ( res == TLD7002_FRAME_VAL_NO_ERROR)
    {
        if ( ((TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx)->r_read_reg.frame_termination.OST.OSB_FAULT == 0)
        {
            /* check if the
                                                                                            OUTPUT STATUS byte FAULT bit is 0 */
            //Serial.println("OTP wr: OK FAULT=0 ");
        }
        else
        {
            //Serial.println("OTP wr: Err-OSB_FAULT=1");
            ret = FALSE;
        }
    }
    else
    {
        //Serial.println("OTP wr: Err-frame2");
        ret = FALSE;
    }

    //  if ( ret == TRUE)
    //    Serial.println( "OTP WRITE SUCCESS");
    //  else
    //    Serial.println( "OTP WRITE ERROR");

    return ret;
}

/**
 * OTP EMULATION PROCEDURE:
 * @brief OTPemuComplete - TLD7002-16 OTP emulation PROCEDURE, it emulates the OTP on the TLD7002-16, and then checks if
 * the OTP is emulated correctly. The sequence and all the delay between steps are as specified in the
 * Infineon-TLD7002-16ES_OTP_programming_procedure-AN-v01_10-EN application note
 * NOTE: TLD7002-16 emulation is only possible if GPIN0 was not already configured as analog pin in  aprevious OTP
 * emulation or programming
 * @param otp_cfg - TLD7002-16 OTP configuration array, 40 bytes
 * @param gBuffTxRx - buffer used from the Device driver to store HSLI tx/rx frames
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param add_after_emu - device address after emulation (has to match the address passed on the OTP configuration file,
          which is emulated)
 * @param newInterfrDelay - TLD7002 interframe delay set on the otp_cfg array, this has to match to the one set in the
          otp_cgf array
 */
boolean OTPemuComplete(uint16 *otp_cfg, TLD7002_NetworkInstance_t *HSLInetwork, uint8 add_after_emu, uint16 newInterfrDelay  )
{
    uint8 res;
    boolean  ret = TRUE;

    //pinMode(PIN_GPIN0, OUTPUT);
    tld7002_gpin0_set_level (0); /* bring GPIN0 is 0 */
    system_delay_us(1005);

    /*  Step1: ensure the device is in INIT mode to enter into OTP mode, before the OTP mode request */
    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_INIT_MODE);
    system_delay_us(1005); /* delay counted starting from the last bit transmitted */

    /* case Step2: Sent twice the INIT mode request to sync MRC and RC of the Device Driver and TLD7002-16 device */
    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_INIT_MODE);
    system_delay_us(7000); /* If the device/devices under programming never reaches/reach the failsafe state the delay*/
    /* can be reduced to 1005us, delay counted starting from the last bit transmitted          */

    /* Step3: set interframe delay to 50us by  writing the volatile register TLD7002_HSLI_TIMING_CFG(ADD 0x3B) with 000C*/
    TLD7002_TRX_WRITE_REG_DLC1(HSLInetwork, gBuffTxRx, BROADCAST_ADDRESS, 0x3B, 0x001C);
    system_delay_us(INTERFR_DELAY_OTP_WRITE); /* delay counted starting from the last bit transmitted */

    /* Step4: set the TLD7002-16 in OTP mode */
    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_OTP_MODE);
    system_delay_us(1005); /* delay counted starting from the last bit transmitted */

    /* Step5: set GPIN0 1 to enable programming */
    tld7002_gpin0_set_level (1);
    system_delay_us(INTERFR_DELAY_OTP_WRITE);

    /* Step6 : write OTP mode emulation password OTP emu*/
    TLD7002_TRX_WRITE_REG_DLC1(HSLInetwork, gBuffTxRx, (uint8)BROADCAST_ADDRESS, TLD7002_OTP_EMULATION, EMULATION_PASSW);
    system_delay_us(INTERFR_DELAY_OTP_WRITE); //interframe delay

    /* Step7: write the first 32 words of the OTP */
    TLD7002_TRX_WRITE_REG_DLC7(HSLInetwork, gBuffTxRx, BROADCAST_ADDRESS, 0x83, otp_cfg);
    system_delay_us(INTERFR_DELAY_OTP_WRITE); //delay counted starting from the last bit transmitted*/

    /* Step8: write the last 8 words of the OTP (the first 32 words has been wrtten with previous DLC7 frame) */
    TLD7002_TRX_WRITE_REG_DLC4(HSLInetwork, gBuffTxRx, BROADCAST_ADDRESS, 0xA3, otp_cfg + 32);
    system_delay_us(INTERFR_DELAY_OTP_WRITE);  /* wait for interframe delay */

    /* Step9: The GPIN0 voltage of the device under programming can be set to low after programming*/
    tld7002_gpin0_set_level (0); /*  Set GPIN0 to a logic low */
    system_delay_us(INTERFR_DELAY_OTP_WRITE);

    /* Step 10: The device is moved to INIT mode.If the OTP writing procedure ends successfully then the device is
     * configured by the new OTP array.*/
    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_INIT_MODE);
    system_delay_us(max(205, newInterfrDelay)); /*delay counted starting from the last bit transmitted,if the new
                                                //intraframe delay is lower than 200us. The delay shall be:delay > 200us*/

    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, BROADCAST_ADDRESS, TLD7002_FRAME_PM_INIT_MODE);
    system_delay_us(max(205, newInterfrDelay)); /*delay counted starting from the last bit transmitted,if the new
                                                    //intraframe delay is lower than 200us. The delay shall be:delay > 200us*/

    TLD7002_TRX_READ_REG_DLC1(HSLInetwork, gBuffTxRx, add_after_emu, 0x82);

    /* dummy frame with new address after emulation, to syncronize library slave roll. counter, not in the OTP app note */
    TLD7002_TRX_PM_CHANGE(HSLInetwork, gBuffTxRx, add_after_emu, TLD7002_FRAME_PM_INIT_MODE);
    system_delay_us(newInterfrDelay);

    /* Step11 and STEP 12 combined: Read back and compare the entire OTP array */
    for (int n = 0; n < 5; n++) /* entire CFC configurationis 40 words, read 5 times 8 word from the OTP (arduino has 62 bytes*/
    {
        /* limited serial buffer, can not read the enire DLC7 frame) */
        res = TLD7002_TRX_READ_REG_DLC4(HSLInetwork, gBuffTxRx, add_after_emu, 0x83 + n * 8);
        system_delay_us (newInterfrDelay);/*wait interfframe delay after TLD7002-16 answer*/

        if ( res == TLD7002_FRAME_VAL_NO_ERROR )
        {
            for (int i = 0; i < 8 ; i++ ) /*lenght of DLC6 is 16wrd(TLD7002_LEN_WRITE_REG_DLC6_WRITE-TLD7002_LEN_WRITE_REG_OVHD)/2*/
            {
                if ( ((TLD7002_READ_REG_DLC4_FRAME_t *)gBuffTxRx)->r_read_reg.Data[i] != otp_cfg[i + n * 8] )
                {
                    //Serial.println("OTP read Back Mismatch");
                    ret = FALSE;
                    break; /* breaks for loop ( performing OTP reading), if mismatches are present during readback*/

                }
            }
        }
        else
        {
            //Serial.print("readBackERR res=");
            //Serial.println(res);
            ret = FALSE;
            break; /* breaks for loop ( performing OTP reading), if frame errors are present during readback*/
        }
    }

    //  if ( ret == TRUE)
    //    Serial.println( "OTP EMU SUCCESS");
    //  else
    //    Serial.println( "OTP EMU ERROR");

    return ret;/* return TRUE if OTP write was successfully performed */
}


/**
 * @brief TLD7002HWCRall: reads TLD7002-16 external temperature on NTC connected to GPIO1
 * this is valid for a 10k NTC part number: Mitsubishy TD11-3H103F 0603 10K 3370K TD11-3H103F 0603 10K Ohm 3370K
 * NTC is placed as low side resistor divider with Upper resistor 10k to the 5V supply (see TLD7002-16SHIELD schematic)
 * @return: error on the conversion or in the device operating mode
 */
void TLD7002HWCRall(TLD7002_NetworkInstance_t *HSLInetwork, uint8 address )
{
    TLD7002_TRX_HWCR_ALL (HSLInetwork, gBuffTxRx, address ); /* clear all TLD7002 error flags */
}

/**
 * @brief TLD7002readExtNTC: reads TLD7002-16 external temperature on NTC connected to GPIO1
 * this is valid for a 10k NTC part number: Mitsubishy TD11-3H103F 0603 10K 3370K TD11-3H103F 0603 10K Ohm 3370K
 * NTC is placed as low side resistor divider with Upper resistor 10k to the 5V supply (see TLD7002-16SHIELD schematic)
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instances
 * @return: error on the conversion or in the device operating mode
 */
enum TLDerr TLD7002readExtNTC(float *tempNTC, TLD7002_NetworkInstance_t *HSLInetwork, uint8 address)
{
    uint16        ADCvalue;
    volatile uint32 GPIN_mV;
    volatile float  GPIN_v;
    uint8           res = TLD7002_FRAME_VAL_NO_ERROR;/*used to store transmission HSLI replies*/
    enum TLDerr     ret = NO_ERR;

    /* read GPIO1 voltage, becasue the NTC is applied to GPI=1 with a voltage divider  */
    res = TLD7002_TRX_READ_REG_DLC1(HSLInetwork, gBuffTxRx, address, TLD7002_LD_ADC_VGPIO1); /* send read register
                                                                                       request to read VS ADC voltage */
    if ( res == TLD7002_FRAME_VAL_NO_ERROR)
    {
        if ( ((TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx)->r_read_reg.Data[0] & TLD7002_LD_ADC_VGPIO1_VAL_F_MSK )
        {
            /* check the
                                                                                                        VALID (ready )bitfield */
            ADCvalue = ((TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx)->r_read_reg.Data[0] & TLD7002_LD_ADC_VGPIO1_VGPIO1_OUT_MSK;
            GPIN_mV = ((uint32)ADCvalue * 5496) / 1023; /* calculate ADC value in mV.  GPINx has 5496mV full scale 1023 value */
            GPIN_v = (float)GPIN_mV / 1000;
            *tempNTC = (1.8928 * GPIN_v * GPIN_v * GPIN_v * GPIN_v) - (23.013 * GPIN_v * GPIN_v * GPIN_v) +
                       (95.833 * GPIN_v * GPIN_v) - 181.98 * (GPIN_v) + 169.94 ; /* fourth order aproximation formula for temp calc
                                                        = 1.8928x4 - 23.013x3 + 95.833x2 - 181.98x + 169.94 */
        }
        else
        {
            ret = ADC_ERROR; /* ADC not valid or device in INIT  mode */
        }
    }
    else  /* Serial.print("Frame Error Res=");Serial.println(res);*/
    {
        ret = COMM_ERROR;
    }
    return ret;
}

/**
 * @brief TLD7002readDTS: reads TLD7002-16 internal temp (DTS Die Temp Sensor)
 * and print it in the serial monitor in Â°C. It reads also if the TLD7002-16 thermal derating is active
 * @return: error on the conversion or in the device operating mode
 */
enum TLDerr TLD7002readDTS( uint16 *DTS_temp, TLD7002_NetworkInstance_t *HSLInetwork, uint8 address)
{
    uint16 DTS_value;
    uint8  res = TLD7002_FRAME_VAL_NO_ERROR;/* used to store transmission HSLI replies */
    uint16 ret = NO_ERR;

    res = TLD7002_TRX_READ_REG_DLC1(HSLInetwork, gBuffTxRx, address, TLD7002_DTS_STAT); /* send read register request */
    /* to read Die Temp Sensor(internal Temp) */
    if ( res == TLD7002_FRAME_VAL_NO_ERROR)
    {
        if ( ((TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx)->r_read_reg.Data[0] & TLD7002_DTS_STAT_DTS_TEMP_READY_MSK )
        {
            /* check
                                                                                                   the VALID (ready )bitfield */
            DTS_value = (((TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx)->r_read_reg.Data[0] & TLD7002_DTS_STAT_DTS_TEMP_MSK)
                        >> TLD7002_DTS_STAT_DTS_TEMP_POS;
            *DTS_temp = (uint16)(((uint32)DTS_value * 1000) / 1139 ) - 273;
            /*DER_active = (((TLD7002_READ_REG_DLC1_FRAME_t*)gBuffTxRx)->r_read_reg.Data[0] & TLD7002_DTS_STAT_DTS_OVERTEMP_MSK)
                                                                                        >>TLD7002_DTS_STAT_DTS_OVERTEMP_POS;*/
        }
        else  /* ADC not valid or device in INIT mode */
        {
            ret |= ADC_ERROR;
        }
    }
    else /* Frame Error */
    {
        ret |= COMM_ERROR;
    }
    return (enum TLDerr)ret;
}

/**
 * @brief TLD7002readVLED: reads TLD7002-16 VLED voltage in mV and print it's value on the serial monitor
 * @return: error on the conversion or in the device operating mode
 */
enum TLDerr TLD7002readVLED(uint16 *VLEDmV, TLD7002_NetworkInstance_t *HSLInetwork, uint8 add)
{
    uint16    ADCvalue;
    uint32      ADCmV;
    uint8       res = TLD7002_FRAME_VAL_NO_ERROR;//used to store transmission HSLI replies
    uint16      ret = NO_ERR;

    // *** READ VLED
    res = TLD7002_TRX_READ_REG_DLC1(HSLInetwork, gBuffTxRx, add, TLD7002_LD_ADC_VLED); /* send read register
                                                                                       request to read VS ADC voltage */
    if ( res == TLD7002_FRAME_VAL_NO_ERROR)
    {
        if ( ((TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx)->r_read_reg.Data[0] & TLD7002_LD_ADC_VLED_VAL_F_MSK )
        {
            /* check the
                                                                                                               VALID bitfield */
            ADCvalue = ((TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx)->r_read_reg.Data[0] & TLD7002_LD_ADC_VS_VLED_MSK;
            ADCmV = ((uint32)ADCvalue * 20067) / 1023; // VS ADC to mV  conversion formula
            *VLEDmV = (uint16)ADCmV ;
        }
        else  /*ADC not valid or device in INIT mode */
        {
            ret |= ADC_ERROR;
        }
    }
    else /* Frame Error */
    {
        ret = COMM_ERROR;
    }
    return (enum TLDerr)ret;
}


/**
 * @brief TLD7002decodeStdAnswer: Interprets the standard diagnostic answer (output status byte(OST) and (ACK) byte) of
 * the TLD7002 and check the device operating mode. The function combines several TLD7002 possible err into few groups
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @return : error if the device it is not in ACTIVE or EMULATION mode, or if errors are present at the TLD7002-16 outs
 */
enum TLDerr TLD7002decodeStdAnswer (TLD7002_FRAME_TERMINATION_t frame_termination)
{
    uint16 err = NO_ERR;

    if  ( frame_termination.ACK.MODE == TLD7002_FRAME_ACK_BYTE_MODE_1    /* check if the device is in ACTIVE Mode or */
            || frame_termination.ACK.MODE == TLD7002_FRAME_ACK_BYTE_MODE_3 ) /* EMULATION mode (not acceptable to be in INIT)*/
    {
        if (frame_termination.OST.VLED_VS_UV)
        {
            err |= UV_ERROR;
        }
        if (frame_termination.OST.DC_WRN)
        {
            err |= OUT_DC_ERROR;
        }
        if (frame_termination.OST.CUR_WRN)
        {
            err |= OUT_CUR_ERROR;
        }
        if (frame_termination.OST.OVLD)
        {
            err |= OUT_OVLD_ERROR;
        }
        if (frame_termination.OST.VFWD_WRN)
        {
            err |= OUT_VFWD_ERROR;
        }
        if (frame_termination.OST.OSB_FAULT)
        {
            err |= INT_FAULT_ERR;
        }
    }
    else  /*  device not in active, it not makes sense to interpret the outputs diagnostic bytes */
    {
        err |= MODE_ERROR;
    }
    return (enum TLDerr)err;
}

/**
 * @brief TLD7002setDutyReadDiag: Update the TLD7002-16 shadow registers (LD_PWM_DC_CFGi )by using the DC_UPDATE HSLI
 * command and reads TLD7002 standard diagnostic (returned at each HSLI command). The written duty cycle is not immediately
 * visible ,it is just stored in the TLD7002-16 LD_PWM_DC_CFGi register, a DC_SYNC (TLD7002broadcastDCsync)command is needed
 * to utput the shadow register duty cycle at the LEDs. In case more TLD7002-16 devices are connected to the HSLI bus multiple
 * TLD7002setDutyReadDiag has to be sent at each device address then a single TLD7002broadcastDCsync is sent to update all the outputs simultaneously
 * @param dutyArray: array of 16 duty cycles that will be sent to the TLD7002-16 shadow registers
 * @param[in] TLD7002_NetworkInstance_t* Reference to TLD7002 network instance
 * @param add: address of the TLD7002-16 that has to be controlled
 * @return: eventual TLD7002-16 errors combined ( TLD7002-16 diag err, TLD7002 wrong operating mode,  HSLI communication)
 */
enum TLDerr TLD7002setDutyReadDiag( uint16 *dutyArray, TLD7002_NetworkInstance_t *HSLInetwork, uint8 add )
{
    uint16 err = NO_ERR;
    uint8  trxRes;      // stores HSLI transmission result

    trxRes = TLD7002_TRX_DC_UPDATE_8BIT(HSLInetwork, gBuffTxRx, add, dutyArray); /* Provides new duty cycle
                                                                                            array to shadow registers */

    if ( trxRes == TLD7002_FRAME_VAL_NO_ERROR)
    {
        err = TLD7002decodeStdAnswer( ((TLD7002_DC_UPDATE_14BIT_FRAME_t *)gBuffTxRx)->r_pwm_dc_update.frame_termination);
    }
    else  /* TLD Frame Err */
    {
        err = COMM_ERROR; /* communication error , remain in TLD7002_INIT state */
    }
    return (enum TLDerr)err;
}

/**
 * @brief TLD7002broadcastDCsync: activate duty cycles which were stored in the shadow registers by the TLD7002setDutyReadDiag
 * command. It sends a DC_SYNC_FRAME on the HSLI bus. Since the DC_SYNC it is a broadcast command, there will be no reply on it
 * from the TLD7002-16 (because if multiple TLD7002-16 are connected to the bus, they would all reply)
 *
 */
void TLD7002broadcastDCsync(TLD7002_NetworkInstance_t *HSLInetwork)
{
    TLD7002_TX_BRDC_DC_SYNC_FRAME(HSLInetwork, (TLD7002_BRDC_DC_SYNC_FRAME_t *)gBuffTxRx ); /* send DC sync to bring  */
    /* duty cycles stored in the shadow register at the output */
    return;
}

/**
 *  *****************************   Wrappers TX,RX combined *****************************************************
 * Wrapper functions which combines TX of the TLD7002 frame and RX of the TLD7002 acknowledge answer the wrappers funct
 * are casting one single gBuffTxRx[] in to each possible frame type needed by the device driver TX or RX function
 * NOTE:
 * This arduino Sketch adopts soft serial for UART TX, therefore TX is a blocking function,
 * the TRX functions are delay-waiting for the TLD7002 answer, before calling the RX device driver function
 * but in case of HW UART implementation (very common for other uC), where TX is not blocking code execurion while
 * tranmitting on the UART, the delay has to count also for transmitted bytes. E.G. on the TLD7002_TRX_DC_UPDATE_8BIT =>
 * system_delay_us(TLD7002_LEN_DC_UPDATE_8BIT_READ + TLD7002_LEN_DC_UPDATE_8BIT_WRITE )*TLD7002_BYTE_TIME_uS
 */

uint8 TLD7002_TRX_DC_UPDATE_8BIT(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add, uint16 *dc_val)
{
    TLD7002_TX_DC_UPDATE_8BIT_FRAME(mcldNet, (TLD7002_DC_UPDATE_8BIT_FRAME_t *)gBuffTxRx, add, dc_val); /* update shadow reg
                                                          with new duty cycles (output still not change until DC_SYNC) */
    system_delay_us(TLD7002_LEN_DC_UPDATE_8BIT_READ * TLD7002_BYTE_TIME_uS); /* wait for TLD7002 reply */
    return TLD7002_RX_DC_UPDATE_8BIT_FRAME(mcldNet, (TLD7002_DC_UPDATE_8BIT_FRAME_t *)gBuffTxRx); /* receive TLD7002 answer */
}

uint8 TLD7002_TRX_DC_UPDATE_14BIT(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add, uint16 *dc_val)
{
    TLD7002_TX_DC_UPDATE_14BIT_FRAME(mcldNet, (TLD7002_DC_UPDATE_14BIT_FRAME_t *)gBuffTxRx, add, dc_val);/* send a DC_UPDATE
                                      to move to active mode,  providing also new duty cycle array to shadow registers */
    system_delay_us(TLD7002_LEN_DC_UPDATE_14BIT_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available*/
    return TLD7002_RX_DC_UPDATE_14BIT_FRAME(mcldNet, (TLD7002_DC_UPDATE_14BIT_FRAME_t *)gBuffTxRx); /* receive TLD7002 answer */
}

uint8 TLD7002_TRX_READ_REG_DLC1(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add, uint8 startAdd)
{
    TLD7002_TX_READ_REG_DLC1_FRAME(mcldNet, (TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx, add, startAdd); /*TX a read DLC1 frame*/
    system_delay_us(TLD7002_LEN_READ_REG_DLC1_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available */
    return TLD7002_RX_READ_REG_DLC1_FRAME(mcldNet, (TLD7002_READ_REG_DLC1_FRAME_t *)gBuffTxRx); /*RX a read DLC1 frame*/
}

uint8 TLD7002_TRX_READ_REG_DLC4(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add, uint8 startAdd)
{
    TLD7002_TX_READ_REG_DLC4_FRAME(mcldNet, (TLD7002_READ_REG_DLC4_FRAME_t *)gBuffTxRx, add, startAdd); /*TX a read DLC4 frame*/
    system_delay_us( TLD7002_LEN_READ_REG_DLC4_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available */
    return TLD7002_RX_READ_REG_DLC4_FRAME(mcldNet, (TLD7002_READ_REG_DLC4_FRAME_t *)gBuffTxRx); /*RX a read DLC4 frame*/
}

uint8 TLD7002_TRX_DC_UPDATE_DLC0(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add)
{
    TLD7002_TX_DC_UPDATE_8BIT_DLC0_FRAME(mcldNet, (TLD7002_DC_UPDATE_8BIT_FRAME_t *)gBuffTxRx, add);/* send a DC_UPDATE DLC0
                                                                                               to move to active mode*/
    system_delay_us( TLD7002_LEN_DC_UPDATE_8BIT_DLC0_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available */
    return TLD7002_RX_DC_UPDATE_8BIT_DLC0_FRAME(mcldNet, (TLD7002_DC_UPDATE_8BIT_FRAME_t *)gBuffTxRx);
}

uint8 TLD7002_TRX_HWCR_ALL (TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add)
{
    TLD7002_TX_HWCR_ALL_FRAME(mcldNet, (TLD7002_HWCR_FRAME_t *)gBuffTxRx, add);
    system_delay_us( TLD7002_LEN_HWCR_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available*/
    return TLD7002_RX_HWCR_FRAME(mcldNet, (TLD7002_HWCR_FRAME_t *)gBuffTxRx);
}

uint8 TLD7002_TRX_PM_CHANGE(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add, TLD7002_FRAME_POWER_MODE_CHANGE_t mode)
{
    TLD7002_TX_PM_CHANGE_FRAME(mcldNet, (TLD7002_PM_CHANGE_FRAME_t *)gBuffTxRx, add, mode);
    system_delay_us( TLD7002_LEN_PM_CHANGE_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available */
    return TLD7002_RX_PM_CHANGE_FRAME(mcldNet, (TLD7002_PM_CHANGE_FRAME_t *) gBuffTxRx);
}

uint8 TLD7002_TRX_WRITE_REG_DLC7(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add, uint8 startAdd, uint16 *data)
{
    TLD7002_TX_WRITE_REG_DLC7_FRAME(mcldNet, (TLD7002_WRITE_REG_DLC7_FRAME_t *)gBuffTxRx, add, startAdd, data);
    system_delay_us( TLD7002_LEN_WRITE_REG_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available*/
    return TLD7002_RX_WRITE_REG_DLC7_FRAME(mcldNet, (TLD7002_WRITE_REG_DLC7_FRAME_t *)gBuffTxRx);
}

uint8 TLD7002_TRX_WRITE_REG_DLC4(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add, uint8 startAdd, uint16 *data)
{
    TLD7002_TX_WRITE_REG_DLC4_FRAME(mcldNet, (TLD7002_WRITE_REG_DLC4_FRAME_t *)gBuffTxRx, add, startAdd, data);
    system_delay_us( TLD7002_LEN_WRITE_REG_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available*/
    return TLD7002_RX_WRITE_REG_DLC4_FRAME(mcldNet, (TLD7002_WRITE_REG_DLC4_FRAME_t *)gBuffTxRx);
}

uint8 TLD7002_TRX_WRITE_REG_DLC1(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add, uint8 startAdd, uint16 data)
{
    TLD7002_TX_WRITE_REG_DLC1_FRAME(mcldNet, (TLD7002_WRITE_REG_DLC1_FRAME_t *)gBuffTxRx, add, startAdd, data);
    system_delay_us( TLD7002_LEN_WRITE_REG_READ * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available*/
    return TLD7002_RX_WRITE_REG_DLC1_FRAME(mcldNet, (TLD7002_WRITE_REG_DLC1_FRAME_t *)gBuffTxRx);
}

uint8 TLD7002_TRX_READ_OST(TLD7002_NetworkInstance_t *mcldNet, char *gBuffTxRx, uint8 add)
{
    TLD7002_TX_READ_OST_FRAME(mcldNet, (TLD7002_READ_OST_FRAME_t *)gBuffTxRx,  add);
    system_delay_us( TLD7002_LEN_READ_OST_WRITE * TLD7002_BYTE_TIME_uS ); /* wait > data from TLD7002-16 to be available*/
    return TLD7002_RX_READ_OST_FRAME(mcldNet, (TLD7002_READ_OST_FRAME_t *)gBuffTxRx);
}
