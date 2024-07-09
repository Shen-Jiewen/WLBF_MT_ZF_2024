/**
 *  @file TLD7002FuncLayer.h
 *  @author Infineon
 *  @date 03.08.2022
 *	@brief Functional layer, which provide simplified access to the TLD7002-16 device drivers
 *   It combines several calls to the TLD7002-16 device Drivers in order to perform  complex functionalities like:
 *   OTP emulation/write , NTC readings , VLED & VS reading, Diagnostic reading and so on
 *   without the needs for the user to understand the TLD7002-16 registers bitfields.
 *
 ***********************************************************************************************************************
 *
 * Copyright (c) 2022, Infineon Technologies AG
 * All rights reserved.
 *
 **********************************************************************************************************************
 */

#ifndef TLD7002FUNC_LAYER_H_
#define TLD7002FUNC_LAYER_H_

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "TLD7002.h"
#include "TLD7002_ServiceLayer.h"

/*******************************************************************************
**                         Global Macro Declarations                          **
*******************************************************************************/
#define BROADCAST_ADDRESS	    0   /* Broadcast message address */
#define INTERFR_DELAY           50 /* [us]interframe delay. It has been set to 55us in the TLD7002-16 OTP. Distance
                                      between 2 HSLI transmissions on the TLD7002-16, see datasheet*/
#define INTERFR_DELAY_OTP_WRITE 100 /* interframe delay set during OTP write and emulation*/

#define tINIT2ACTIVE            250   /* [us]Time neededd from the TLD7002 to "wake up" from INIT mode */
#define tFAILSAFE2INIT          5000  /* [us]Time needed from the TLD7002 from fail safe to INIT mode 250us + 2(1/fPWM)@400Hz*/
#define PWM_PERIOD_uS           1120  /* [us]Output LED PWM period, default is 300Hz =>3.3ms, setup is 899Hz =>1.1ms*/
#define EMULATION_PASSW         0x3BD2/* Password needed in orderto emulate the TLD7002-16 OTP. See TLD7002-16 OTP app note */
#define OTP_WRITE_PASSW         0xA47B/* Password needed in orderto emulate the TLD7002-16 OTP. See TLD7002-16 OTP app note */

/*******************************************************************************
**                                   Enums                                    **
*******************************************************************************/
/* Enum of possible error on a TLD7002-16, combined for: output errors, communication, undervoltages, operating mode */
enum TLDerr
{
    NO_ERR        = 0x0000,
    COMM_ERROR    = 0x0001, /* communication error */
    MODE_ERROR    = 0x0002, /* device not active or not in emulation mode */
    UV_ERROR      = 0x0004, /* undervoltage at VS or VLED  */
    OUT_DC_ERROR  = 0x0008, /* TLD7002-16 DC_WRN bit is set, output duty differs from the set one. See TLD7002 datasheet*/
    OUT_CUR_ERROR = 0x0010, /* TLD7002-16 CUR_WRN bit is set, output current lower than requested. See TLD7002 datasheet*/
    OUT_OVLD_ERROR = 0x0020, /* TLD7002-16 OVLD bit is set, thermal overload present in one or more ch. See TLD7002 datash*/
    OUT_VFWD_ERROR = 0x0040, /* TLD7002-16 VFWD_WRN bit is set in one or more channels, this means that the LED forward
                             voltage is lower than expected ,see TLD7002-16 datasheet */
    INT_FAULT_ERR = 0x0080, /* device not active or not in emulation mode */
    ADC_ERROR     = 0x0100  /* ADC read not valid */
};

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
void TLD7002initDrivers(TLD7002_NetworkInstance_t *HSLInetwork);
enum TLDerr TLD7002initDevice(TLD7002_NetworkInstance_t *HSLInetwork, uint8 add);
boolean OTPwrite(uint16 *otp_cfg, TLD7002_NetworkInstance_t *HSLInetwork, uint8 address, uint16 newInterfrDelay  );
boolean OTPemuComplete(uint16 *otp_cfg, TLD7002_NetworkInstance_t *HSLInetwork, uint8 add_after_emu, uint16 newInterfrDelay  );
enum TLDerr TLD7002readExtNTC(float *tempNTC, TLD7002_NetworkInstance_t *HSLInetwork, uint8 add);
enum TLDerr TLD7002readDTS(uint16 *VLEDmV, TLD7002_NetworkInstance_t *HSLInetwork, uint8 add);
enum TLDerr TLD7002readVLED(uint16 *VLEDmV, TLD7002_NetworkInstance_t *HSLInetwork, uint8 add);
enum TLDerr TLD7002setDutyReadDiag(uint16 *dutyArray, TLD7002_NetworkInstance_t *HSLInetwork, uint8 add );
void TLD7002broadcastDCsync(TLD7002_NetworkInstance_t *HSLInetwork );
void TLD7002HWCRall(TLD7002_NetworkInstance_t *HSLInetwork, uint8 add);

/**************** Device Driver Wrappers TX,RX combined ***********/
uint8 TLD7002_TRX_READ_REG_DLC1(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add, uint8 startAdd);
uint8 TLD7002_TRX_DC_UPDATE_14BIT(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add, uint16 *dc_val);
uint8 TLD7002_TRX_DC_UPDATE_8BIT(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add, uint16 *dc_val);
uint8 TLD7002_TRX_DC_UPDATE_DLC0(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add);
uint8 TLD7002_TRX_HWCR_ALL (TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add);
uint8 TLD7002_TRX_PM_CHANGE(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add, TLD7002_FRAME_POWER_MODE_CHANGE_t mode);
uint8 TLD7002_TRX_WRITE_REG_DLC7(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add, uint8 startAdd, uint16 *data);
uint8 TLD7002_TRX_WRITE_REG_DLC4(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add, uint8 startAdd, uint16 *data);
uint8 TLD7002_TRX_WRITE_REG_DLC1(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add, uint8 startAdd, uint16 data);
uint8 TLD7002_TRX_READ_REG_DLC4(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add, uint8 startAdd);
uint8 TLD7002_TRX_READ_OST(TLD7002_NetworkInstance_t *mcldNet, char *buffTxRx, uint8 add) ;

/*******************************************************************************
**                        local Function Declarations                        **
*******************************************************************************/
enum TLDerr TLD7002decodeStdAnswer (TLD7002_FRAME_TERMINATION_t frame_termination);

#endif /* TLD7002FUNC_LAYER_H_ */
