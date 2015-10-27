/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined(__FSL_SIM_HAL_H__)
#define __FSL_SIM_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_sim_features.h"

/*! @addtogroup sim_hal*/
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum _clock_names {

   /* default clocks*/
   kCoreClock,                         /**/
   kSystemClock,                       /**/
   kPlatformClock,                     /**/
   kBusClock,                          /**/
   kFlexBusClock,                      /**/
   kFlashClock,                        /**/

   /* other internal clocks used by peripherals*/
   /* osc clock*/
   kOsc32kClock,
   kOsc0ErClock,
   kOsc1ErClock,

   /* irc 48Mhz clock */
   kIrc48mClock,

   /* rtc clock*/
   kRtc32kClock,
   kRtc1hzClock,

   /* lpo clcok*/
   kLpoClock,

   /* mcg clocks*/
   kMcgFfClock,
   kMcgFllClock,
   kMcgPll0Clock,
   kMcgPll1Clock,
   kMcgOutClock,
   kMcgIrClock,

   /* constant clocks (provided in other header files?)*/
   kSDHC0_CLKIN,
   kENET_1588_CLKIN,
   kEXTAL_Clock,
   kEXTAL1_Clock,
   kUSB_CLKIN,

   /* reserved value*/
   kReserved,

   kClockNameCount
} clock_names_t;

/*! @brief Clock source and sel names */
typedef enum _clock_source_names {
    kClockNfcSrc,                   /* NFCSRC*/
    kClockEsdhcSrc,                 /* ESDHCSRC K70*/
    kClockSdhcSrc,                  /* SDHCSRC  K64*/
    kClockLcdcSrc,                  /* LCDCSRC*/
    kClockTimeSrc,                  /* TIMESRC*/
    kClockRmiiSrc,                  /* RMIISRC*/
    kClockUsbfSrc,                  /* USBFSRC  K70*/
    kClockUsbSrc,                   /* USBSRC   K64, KL25, KV31, and K22*/
    kClockUsbhSrc,                  /* USBHSRC*/
    kClockUart0Src,                 /* UART0SRC*/
    kClockLpuartSrc,                /* LPUARTSRC K22, KV31 */
    kClockTpmSrc,                   /* TPMSRC*/
    kClockOsc32kSel,                /* OSC32KSEL*/
    kClockUsbfSel,                  /* USBF_CLKSEL*/
    kClockPllfllSel,                /* PLLFLLSEL*/
    kClockNfcSel,                   /* NFC_CLKSEL*/
    kClockLcdcSel,                  /* LCDC_CLKSEL*/
    kClockTraceSel,                 /* TRACE_CLKSEL*/
    kClockClkoutSel,                /* CLKOUTSEL*/
    kClockRtcClkoutSel,             /* RTCCLKOUTSEL */
    kClockSourceMax
} clock_source_names_t;

/*! @brief Clock Divider names*/
typedef enum _clock_divider_names {
    kClockDividerOutdiv1,           /* OUTDIV1*/
    kClockDividerOutdiv2,           /* OUTDIV2*/
    kClockDividerOutdiv3,           /* OUTDIV3*/
    kClockDividerOutdiv4,           /* OUTDIV4*/
    kClockDividerUsbFrac,           /* (USBFRAC + 1) / (USBDIV + 1)*/
    kClockDividerUsbDiv,
    kClockDividerUsbfsFrac,         /* (USBFSFRAC + 1) / (USBFSDIV) + 1)*/
    kClockDividerUsbfsDiv,
    kClockDividerUsbhsFrac,         /* (USBHSFRAC + 1) / (USBHSDIV + 1)*/
    kClockDividerUsbhsDiv,
    kClockDividerLcdcFrac,          /* (LCDCFRAC + 1) / (LCDCDIV + 1)*/
    kClockDividerLcdcDiv,
    kClockDividerNfcFrac,           /* (NFCFRAC + 1) / (NFCDIV + 1)*/
    kClockDividerNfcDiv,
    kClockDividerSpecial1,          /* special divider 1*/
    kClockDividerMax
} clock_divider_names_t;

/*! @brief SIM USB voltage regulator in standby mode setting during stop modes */
typedef enum _sim_usbsstby_stop
{
    kSimUsbsstbyNoRegulator,        /* regulator not in standby during Stop modes */
    kSimUsbsstbyWithRegulator       /* regulator in standby during Stop modes */
} sim_usbsstby_stop_t;

/*! @brief SIM USB voltage regulator in standby mode setting during VLPR and VLPW modes */
typedef enum _sim_usbvstby_stop
{
    kSimUsbvstbyNoRegulator,        /* regulator not in standby during VLPR and VLPW modes */
    kSimUsbvstbyWithRegulator       /* regulator in standby during VLPR and VLPW modes */
} sim_usbvstby_stop_t;

/*! @brief SIM CMT/UART pad drive strength */
typedef enum _sim_cmtuartpad_strengh
{
    kSimCmtuartSinglePad,           /* Single-pad drive strength for CMT IRO or UART0_TXD */
    kSimCmtuartDualPad              /* Dual-pad drive strength for CMT IRO or UART0_TXD */
} sim_cmtuartpad_strengh_t;

/*! @brief SIM PTD7 pad drive strength */
typedef enum _sim_ptd7pad_strengh
{
    kSimPtd7padSinglePad,           /* Single-pad drive strength for PTD7 */
    kSimPtd7padDualPad              /* Dual-pad drive strength for PTD7 */
} sim_ptd7pad_strengh_t;

/*! @brief SIM FlexBus security level */
typedef enum _sim_flexbus_security_level
{
    kSimFbslLevel0,                 /* All off-chip accesses (op code and data) via the FlexBus */
                                    /* and DDR controller are disallowed */
    kSimFbslLevel1,                 /* Undefined */
    kSimFbslLevel2,                 /* Off-chip op code accesses are disallowed. Data accesses */
                                    /* are allowed */
    kSimFbslLevel3                  /* Off-chip op code accesses and data accesses are allowed */
} sim_flexbus_security_level_t;

/*! @brief SIM ADCx pre-trigger select */
typedef enum _sim_pretrgsel
{
    kSimAdcPretrgselA,              /* Pre-trigger A selected for ADCx */
    kSimAdcPretrgselB               /* Pre-trigger B selected for ADCx */
} sim_pretrgsel_t;

/*! @brief SIM ADCx trigger select */
typedef enum _sim_trgsel
{
    kSimAdcTrgselExt,               /* External trigger */
    kSimAdcTrgSelHighSpeedComp0,    /* High speed comparator 0 asynchronous interrupt */
    kSimAdcTrgSelHighSpeedComp1,    /* High speed comparator 1 asynchronous interrupt */
    kSimAdcTrgSelHighSpeedComp2,    /* High speed comparator 2 asynchronous interrupt */
    kSimAdcTrgSelPit0,              /* PIT trigger 0 */
    kSimAdcTrgSelPit1,              /* PIT trigger 1 */
    kSimAdcTrgSelPit2,              /* PIT trigger 2 */
    kSimAdcTrgSelPit3,              /* PIT trigger 3 */
    kSimAdcTrgSelFtm0,              /* FTM0 trigger */
    kSimAdcTrgSelFtm1,              /* FTM1 trigger */
    kSimAdcTrgSelFtm2,              /* FTM2 trigger */
    kSimAdcTrgSelFtm3,              /* FTM3 trigger */
    kSimAdcTrgSelRtcAlarm,          /* RTC alarm */
    kSimAdcTrgSelRtcSec,            /* RTC seconds */
    kSimAdcTrgSelLptimer,           /* Low-power timer trigger */
    kSimAdcTrgSelHigSpeedComp3      /* High speed comparator 3 asynchronous interrupt */
} sim_trgsel_t;

/*! @brief SIM receive data source select */
typedef enum _sim_uart_rxsrc
{
    kSimUartRxsrcPin,               /* UARTx_RX Pin */
    kSimUartRxsrcCmp0,              /* CMP0 */
    kSimUartRxsrcCmp1,              /* CMP1 */
    kSimUartRxsrcReserved           /* Reserved */
} sim_uart_rxsrc_t;

/*! @brief SIM transmit data source select */
typedef enum _sim_uart_txsrc
{
    kSimUartTxsrcPin,               /* UARTx_TX Pin */
    kSimUartTxsrcCmp0,              /* UARTx_TX pin modulated with FTM1 channel 0 output */
    kSimUartTxsrcCmp1,              /* UARTx_TX pin modulated with FTM2 channel 0 output */
    kSimUartTxsrcReserved           /* Reserved */
} sim_uart_txsrc_t;

/*! @brief SIM FlexTimer x trigger y select */
typedef enum _sim_ftm_trg_src
{
    kSimFtmTrgSrc0,                 /* FlexTimer x trigger y select 0 */
    kSimFtmTrgSrc1                  /* FlexTimer x trigger y select 1 */
} sim_ftm_trg_src_t;

/*! @brief SIM FlexTimer external clock select */
typedef enum _sim_ftm_clk_sel
{
    kSimFtmClkSel0,                 /* FTM CLKIN0 pin. */
    kSimFtmClkSel1                  /* FTM CLKIN1 pin. */
} sim_ftm_clk_sel_t;

/*! @brief SIM FlexTimer x channel y input capture source select */
typedef enum _sim_ftm_ch_src
{
    kSimFtmChSrc0,                 /* See RM for details of each selection for each channel */
    kSimFtmChSrc1,                 /* See RM for details of each selection for each channel */
    kSimFtmChSrc2,                 /* See RM for details of each selection for each channel */
    kSimFtmChSrc3                  /* See RM for details of each selection for each channel */
} sim_ftm_ch_src_t;

/*! @brief SIM FlexTimer x Fault y select */
typedef enum _sim_ftm_flt_sel
{
    kSimFtmFltSel0,                 /* FlexTimer x fault y select 0 */
    kSimFtmFltSel1                  /* FlexTimer x fault y select 1 */
} sim_ftm_flt_sel_t;

/*! @brief SIM Timer/PWM external clock select */
typedef enum _sim_tpm_clk_sel
{
    kSimTpmClkSel0,                 /* Timer/PWM TPM_CLKIN0 pin. */
    kSimTpmClkSel1                  /* Timer/PWM TPM_CLKIN1 pin. */
} sim_tpm_clk_sel_t;

/*! @brief SIM Timer/PWM x channel y input capture source select */
typedef enum _sim_tpm_ch_src
{
    kSimTpmChSrc0,                 /* TPMx_CH0 signal */
    kSimTpmChSrc1                  /* CMP0 output */
} sim_tpm_ch_src_t;

/*! @brief SIM HAL API return status*/
typedef enum _sim_hal_status {
    kSimHalSuccess,
    kSimHalFail,
    kSimHalNoSuchModule,
    kSimHalNoSuchClockSrc,
    kSimHalNoSuchDivider
} sim_hal_status_t;

/*! @brief Clock name configuration table structure*/
typedef struct ClockNameConfig {
    bool                            useOtherRefClock;     /*!< if it  uses the other ref clock*/
    clock_names_t                   otherRefClockName;    /*!< other ref clock name*/
    clock_divider_names_t           dividerName;          /*!< clock divider name*/
} clock_name_config_t;

/*! @brief clock name configuration table for specified CPU defined in fsl_clock_module_names_Kxxx.h*/
extern const clock_name_config_t kClockNameConfigTable[];


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name clock-related feature APIs*/
/*@{*/

/*!
 * @brief Sets the clock source setting.
 *
 * This function  sets the settings for a specified clock source. Each clock 
 * source has its own clock selection settings. See the chip reference manual for 
 * clock source detailed settings and the clock_source_names_t 
 * for clock sources.
 *
 * @param baseAddr    Base address for current SIM instance.
 * @param clockSource Clock source name defined in sim_clock_source_names_t
 * @param setting     Setting value
 * @return status     If the clock source doesn't exist, it returns an error.
 */
sim_hal_status_t CLOCK_HAL_SetSource(uint32_t baseAddr, clock_source_names_t clockSource, uint8_t setting);

/*!
 * @brief Gets the clock source setting.
 *
 * This function  gets the settings for a specified clock source. Each clock
 * source has its own clock selection settings. See the reference manual for
 * clock source detailed settings and the clock_source_names_t
 * for clock sources.
 *
 * @param baseAddr    Base address for current SIM instance.
 * @param clockSource Clock source name
 * @param setting     Current setting pointer for the clock source
 * @return status     If the clock source doesn't exist, it returns an error.
 */
sim_hal_status_t CLOCK_HAL_GetSource(uint32_t baseAddr, clock_source_names_t clockSource, 
                                            uint8_t *setting);

/*!
 * @brief Sets the clock divider setting.
 *
 * This function  sets the setting for a specified clock divider. See the
 * reference manual for a supported clock divider and value range and the
 * clock_divider_names_t for dividers.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param clockDivider Clock divider name
 * @param setting      Divider setting
 * @return status      If the clock divider doesn't exist, it  returns an error.
 */
sim_hal_status_t CLOCK_HAL_SetDivider(uint32_t baseAddr, clock_divider_names_t clockDivider, 
                                             uint32_t setting);

/*!
 * @brief Sets the clock out dividers setting.
 *
 * This function  sets the setting for all clock out dividers at the same time.
 * See the reference manual for a supported clock divider and value range and the
 * clock_divider_names_t for clock out dividers.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
void CLOCK_HAL_SetOutDividers(uint32_t baseAddr, uint32_t outdiv1, uint32_t outdiv2,
                                      uint32_t outdiv3, uint32_t outdiv4);

/*!
 * @brief Gets the clock divider setting.
 *
 * This function  gets the setting for a specified clock divider. See the
 * reference manual for a supported clock divider and value range and the 
 * clock_divider_names_t for dividers.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param clockDivider Clock divider name
 * @param setting      Divider value pointer
 * @return status      If the clock divider doesn't exist, it  returns an error.
 */
sim_hal_status_t CLOCK_HAL_GetDivider(uint32_t baseAddr, clock_divider_names_t clockDivider,
                                             uint32_t *setting);

/*@}*/

/*! @name individual field access APIs*/
/*@{*/

#if FSL_FEATURE_SIM_OPT_HAS_RAMSIZE
/*!
 * @brief Gets RAM size.
 *
 * This function gets the RAM size. The field specifies the amount of system RAM
 * available on the device.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return size  RAM size on the device
 */
static inline uint32_t SIM_HAL_GetRamSize(uint32_t baseAddr)
{
    return BR_SIM_SOPT1_RAMSIZE(baseAddr);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_RAMSIZE */

#if FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR
/*!
 * @brief Sets the USB voltage regulator enabled setting.
 *
 * This function  controls whether the USB voltage regulator is enabled. This bit
 * can only be written when the SOPT1CFG[URWE] bit is set. 
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param enable   USB voltage regulator enable setting
 *                  - true: USB voltage regulator is enabled.
 *                  - false: USB voltage regulator is disabled.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorCmd(uint32_t baseAddr, bool enable)
{
    BW_SIM_SOPT1_USBREGEN(baseAddr, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator enabled setting.
 *
 * This function  gets the USB voltage regulator enabled setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorCmd(uint32_t baseAddr)
{
    return BR_SIM_SOPT1_USBREGEN(baseAddr);
}

/*!
 * @brief Sets the USB voltage regulator in a standby mode setting during Stop, VLPS, LLS, and VLLS.
 *
 * This function  controls whether the USB voltage regulator is placed in a standby
 * mode during Stop, VLPS, LLS, and VLLS modes. This bit can only be written when the
 * SOPT1CFG[USSWE] bit is set.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param setting   USB voltage regulator in standby mode setting
 *                  - 0: USB voltage regulator not in standby during Stop, VLPS, LLS and
 *                       VLLS modes.
 *                  - 1: USB voltage regulator in standby during Stop, VLPS, LLS and VLLS
 *                       modes.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringStopMode(uint32_t baseAddr,
                                                                    sim_usbsstby_stop_t setting)
{
    BW_SIM_SOPT1_USBSSTBY(baseAddr, setting);
}

/*!
 * @brief Gets the USB voltage regulator in a standby mode setting.
 *
 * This function  gets the USB voltage regulator in a standby mode setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting  USB voltage regulator in a standby mode setting
 */
static inline sim_usbsstby_stop_t SIM_HAL_GetUsbVoltRegulatorInStdbyDuringStopMode(uint32_t baseAddr)
{
    return (sim_usbsstby_stop_t)BR_SIM_SOPT1_USBSSTBY(baseAddr);
}

/*!
 * @brief Sets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * This function  controls whether the USB voltage regulator is placed in a standby
 * mode during the VLPR and the VLPW modes. This bit can only be written when the
 * SOPT1CFG[UVSWE] bit is set.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param setting   USB voltage regulator in standby mode setting
 *                  - 0: USB voltage regulator not in standby during VLPR and VLPW modes.
 *                  - 1: USB voltage regulator in standby during VLPR and VLPW modes.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringVlprwMode(uint32_t baseAddr,
                                                                     sim_usbvstby_stop_t setting)
{
    BW_SIM_SOPT1_USBVSTBY(baseAddr, setting);
}

/*!
 * @brief Gets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * This function  gets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting  USB voltage regulator in a standby mode during the VLPR or the VLPW
 */
static inline sim_usbvstby_stop_t SIM_HAL_GetUsbVoltRegulatorInStdbyDuringVlprwMode(uint32_t baseAddr)
{
    return (sim_usbvstby_stop_t)BR_SIM_SOPT1_USBVSTBY(baseAddr);
}

/*!
 * @brief Sets the USB voltage regulator stop standby write enable setting.
 *
 * This function  controls whether the USB voltage regulator stop  standby write
 * feature is enabled. Writing one to this bit allows the SOPT1[USBSSTBY] bit to be written. This
 * register bit clears after a write to SOPT1[USBSSTBY].
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param enable  USB voltage regulator stop standby write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringStopCmd(uint32_t baseAddr, bool enable)
{
    BW_SIM_SOPT1CFG_USSWE(baseAddr, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator stop standby write enable setting.
 *
 * This function  gets the USB voltage regulator stop standby write enable setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator stop standby write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorInStdbyDuringStopCmd(uint32_t baseAddr)
{
    return BR_SIM_SOPT1CFG_USSWE(baseAddr);
}

/*!
 * @brief Sets the USB voltage regulator VLP standby write enable setting.
 *
 * This function  controls whether USB voltage regulator VLP standby write
 * feature is enabled. Writing one to this bit allows the SOPT1[USBVSTBY] bit to be written. This
 * register bit clears after a write to SOPT1[USBVSTBY].
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param enable   USB voltage regulator VLP standby write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringVlprwCmd(uint32_t baseAddr, bool enable)
{
    BW_SIM_SOPT1CFG_UVSWE(baseAddr, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator VLP standby write enable setting.
 *
 * This function  gets the USB voltage regulator VLP standby write enable setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator VLP standby write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorInStdbyDuringVlprwCmd(uint32_t baseAddr)
{
    return BR_SIM_SOPT1CFG_UVSWE(baseAddr);
}

/*!
 * @brief Sets the USB voltage regulator enable write enable setting.
 *
 * This function  controls whether the USB voltage regulator write enable
 * feature is enabled. Writing one to this bit allows the SOPT1[USBREGEN] bit to be written.
 * This register bit clears after a write to SOPT1[USBREGEN].
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param enable   USB voltage regulator enable write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorWriteCmd(uint32_t baseAddr, bool enable)
{
    BW_SIM_SOPT1CFG_URWE(baseAddr, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator enable write enable setting.
 *
 * This function  gets the USB voltage regulator enable write enable setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return enabled True if USB voltage regulator enable write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorWriteCmd(uint32_t baseAddr)
{
    return BR_SIM_SOPT1CFG_URWE(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD
/*!
 * @brief Sets the CMT/UART pad drive strength setting.
 *
 * This function  controls the output drive strength of the CMT IRO signal or
 * UART0_TXD signal on PTD7 pin by selecting either one or two pads to drive it.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param setting   CMT/UART pad drive strength setting
 *                  - 0: Single-pad drive strength for CMT IRO or UART0_TXD.
 *                  - 1: Dual-pad drive strength for CMT IRO or UART0_TXD.
 */
static inline void SIM_HAL_SetCmtUartPadDriveStrengthMode(uint32_t baseAddr,
                                                          sim_cmtuartpad_strengh_t setting)
{
    BW_SIM_SOPT2_CMTUARTPAD(baseAddr, setting);
}

/*!
 * @brief Gets the CMT/UART pad drive strength setting.
 *
 * This function  gets the CMT/UART pad drive strength setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting CMT/UART pad drive strength setting
 */
static inline sim_cmtuartpad_strengh_t SIM_HAL_GetCmtUartPadDriveStrengthMode(uint32_t baseAddr)
{
    return (sim_cmtuartpad_strengh_t)BR_SIM_SOPT2_CMTUARTPAD(baseAddr);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD */

#if FSL_FEATURE_SIM_OPT_HAS_PTD7PAD
/*!
 * @brief Sets the PTD7 pad drive strength setting.
 *
 * This function  controls the output drive strength of the PTD7 pin by selecting
 * either one or two pads to drive it.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param setting   PTD7 pad drive strength setting
 *                  - 0: Single-pad drive strength for PTD7.
 *                  - 1: Double pad drive strength for PTD7.
 */
static inline void SIM_HAL_SetPtd7PadDriveStrengthMode(uint32_t baseAddr,
                                                       sim_ptd7pad_strengh_t setting)
{
    BW_SIM_SOPT2_PTD7PAD(baseAddr, setting);
}

/*!
 * @brief Gets the PTD7 pad drive strength setting.
 *
 * This function  gets the PTD7 pad drive strength setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting PTD7 pad drive strength setting
 */
static inline sim_ptd7pad_strengh_t SIM_HAL_GetPtd7PadDriveStrengthMode(uint32_t baseAddr)
{
    return (sim_ptd7pad_strengh_t)BR_SIM_SOPT2_PTD7PAD(baseAddr);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_PTD7PAD */

#if FSL_FEATURE_SIM_OPT_HAS_FBSL
/*!
 * @brief Sets the FlexBus security level setting.
 *
 * This function  sets the FlexBus security level setting. If the security is enabled,
 * this field affects which CPU operations can access the off-chip via the FlexBus
 * and DDR controller interfaces. This field has no effect if the security is not enabled.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param setting   FlexBus security level setting
 *                  - 00: All off-chip accesses (op code and data) via the FlexBus and
 *                        DDR controller are disallowed.
 *                  - 10: Off-chip op code accesses are disallowed. Data accesses are
 *                        allowed.
 *                  - 11: Off-chip op code accesses and data accesses are allowed.
 */
static inline void SIM_HAL_SetFlexbusSecurityLevelMode(uint32_t baseAddr,
                                                       sim_flexbus_security_level_t setting)
{
    BW_SIM_SOPT2_FBSL(baseAddr, setting);
}

/*!
 * @brief Gets the FlexBus security level setting.
 *
 * This function  gets the FlexBus security level setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting FlexBus security level setting
 */
static inline sim_flexbus_security_level_t SIM_HAL_GetFlexbusSecurityLevelMode(uint32_t baseAddr)
{
    return (sim_flexbus_security_level_t)BR_SIM_SOPT2_FBSL(baseAddr);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_FBSL */

#if FSL_FEATURE_SIM_OPT_HAS_PCR
/*!
 * @brief Sets the PCR setting.
 *
 * This function  sets the PCR setting. This is the FlexBus hold cycles before
 * FlexBus can release bus to NFC or to IDLE.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param setting   PCR setting
 */
static inline void SIM_HAL_SetFlexbusHoldCycles(uint32_t baseAddr, uint32_t setting)
{
    BW_SIM_SOPT6_PCR(baseAddr, setting);
}

/*!
 * @brief Gets the PCR setting.
 *
 * This function  gets the PCR setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting PCR setting
 */
static inline uint32_t SIM_HAL_GetFlexbusHoldCycles(uint32_t baseAddr)
{
    return BR_SIM_SOPT6_PCR(baseAddr);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_PCR */

#if FSL_FEATURE_SIM_OPT_HAS_MCC
/*!
 * @brief Sets the MCC setting.
 *
 * This function  sets  the MCC setting. This is the NFC hold cycle in case the
 * FlexBus request during NFC is granted.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param setting   MCC setting
 */
static inline void SIM_HAL_SetNandFlashControllerHoldCycles(uint32_t baseAddr, uint32_t setting)
{
    BW_SIM_SOPT6_MCC(baseAddr, setting);
}

/*!
 * @brief Gets the MCC setting.
 *
 * This function  gets the MCC setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting MCC setting
 */
static inline uint32_t SIM_HAL_GetNandFlashControllerHoldCycles(uint32_t baseAddr)
{
    return BR_SIM_SOPT6_MCC(baseAddr);
}
#endif /* FSL_FEATURE_SIM_OPT_HAS_MCC */

/*!
 * @brief Sets the ADCx alternate trigger enable setting.
 *
 * This function  enables/disables the alternative conversion triggers for ADCx.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param enable Enable alternative conversion triggers for ADCx
 *               - true: Select alternative conversion trigger.
 *               - false: Select PDB trigger.
 */
void SIM_HAL_SetAdcAlternativeTriggerCmd(uint32_t baseAddr, uint8_t instance, bool enable);

/*!
 * @brief Gets the  ADCx alternate trigger enable setting.
 *
 * This function  gets the  ADCx alternate trigger enable setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @return enabled True if  ADCx alternate trigger is enabled
 */
bool SIM_HAL_GetAdcAlternativeTriggerCmd(uint32_t baseAddr, uint8_t instance);

/*!
 * @brief Sets the ADCx pre-trigger select setting.
 *
 * This function  selects the ADCx pre-trigger source when the alternative triggers
 * are enabled through ADCxALTTRGEN.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select pre-trigger select setting for ADCx
 *               - 0: Pre-trigger A selected for ADCx.
 *               - 1: Pre-trigger B selected for ADCx.
 */
void SIM_HAL_SetAdcPreTriggerMode(uint32_t baseAddr, uint8_t instance, sim_pretrgsel_t select);

/*!
 * @brief Gets the ADCx pre-trigger select setting.
 *
 * This function  gets the ADCx pre-trigger select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select ADCx pre-trigger select setting
 */
sim_pretrgsel_t SIM_HAL_GetAdcPreTriggerMode(uint32_t baseAddr, uint8_t instance);

/*!
 * @brief Sets the ADCx trigger select setting.
 *
 * This function  selects the ADCx trigger source when alternative triggers
 * are enabled through ADCxALTTRGEN.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select trigger select setting for ADCx
 *               - 0000: External trigger
 *               - 0001: High speed comparator 0 asynchronous interrupt
 *               - 0010: High speed comparator 1 asynchronous interrupt
 *               - 0011: High speed comparator 2 asynchronous interrupt
 *               - 0100: PIT trigger 0
 *               - 0101: PIT trigger 1
 *               - 0110: PIT trigger 2
 *               - 0111: PIT trigger 3
 *               - 1000: FTM0 trigger
 *               - 1001: FTM1 trigger
 *               - 1010: FTM2 trigger
 *               - 1011: FTM3 trigger
 *               - 1100: RTC alarm
 *               - 1101: RTC seconds
 *               - 1110: Low-power timer trigger
 *               - 1111: High speed comparator 3 asynchronous interrupt
*/
void SIM_HAL_SetAdcTriggerMode(uint32_t baseAddr, uint8_t instance, sim_trgsel_t select);

/*!
 * @brief Gets the ADCx trigger select setting.
 *
 * This function  gets the ADCx trigger select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select ADCx trigger select setting
 */
sim_pretrgsel_t SIM_HAL_GetAdcTriggerMode(uint32_t baseAddr, uint8_t instance);

/*!
 * @brief Sets the UARTx receive data source select setting.
 *
 * This function  selects the source for the UARTx receive data.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the UARTx receive data
 *               - 00: UARTx_RX pin.
 *               - 01: CMP0.
 *               - 10: CMP1.
 *               - 11: Reserved.
 */
void SIM_HAL_SetUartRxSrcMode(uint32_t baseAddr, uint8_t instance, sim_uart_rxsrc_t select);

/*!
 * @brief Gets the UARTx receive data source select setting.
 *
 * This function  gets the UARTx receive data source select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select UARTx receive data source select setting
 */
sim_uart_rxsrc_t SIM_HAL_GetUartRxSrcMode(uint32_t baseAddr, uint8_t instance);

/*!
 * @brief Sets the UARTx transmit data source select setting.
 *
 * This function  selects the source for the UARTx transmit data.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the UARTx transmit data
 *               - 00: UARTx_TX pin.
 *               - 01: UARTx_TX pin modulated with FTM1 channel 0 output.
 *               - 10: UARTx_TX pin modulated with FTM2 channel 0 output.
 *               - 11: Reserved.
 */
void SIM_HAL_SetUartTxSrcMode(uint32_t baseAddr, uint8_t instance, sim_uart_txsrc_t select);

/*!
 * @brief Gets the UARTx transmit data source select setting.
 *
 * This function  gets the UARTx transmit data source select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select UARTx transmit data source select setting
 */
sim_uart_txsrc_t SIM_HAL_GetUartTxSrcMode(uint32_t baseAddr, uint8_t instance);

#if FSL_FEATURE_SIM_OPT_HAS_ODE
/*!
 * @brief Sets the UARTx Open Drain Enable setting.
 *
 * This function  enables/disables the UARTx Open Drain.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param enable Enable/disable UARTx Open Drain
 *               - True: Enable UARTx Open Drain
 *               - False: Disable UARTx Open Drain
 */
void SIM_HAL_SetUartOpenDrainCmd(uint32_t baseAddr, uint8_t instance, bool enable);

/*!
 * @brief Gets the UARTx Open Drain Enable setting.
 *
 * This function  gets the UARTx Open Drain Enable setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @return enabled True if UARTx Open Drain is enabled.
 */
bool SIM_HAL_GetUartOpenDrainCmd(uint32_t baseAddr, uint8_t instance);
#endif

#if FSL_FEATURE_SIM_OPT_HAS_FTM
/*!
 * @brief Sets the FlexTimer x hardware trigger y source select setting.
 *
 * This function  selects  the source of FTMx hardware trigger y.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param trigger      hardware trigger y
 * @param select FlexTimer x hardware trigger y
 *               - 0: Pre-trigger A selected for ADCx.
 *               - 1: Pre-trigger B selected for ADCx.
 */
void SIM_HAL_SetFtmTriggerSrcMode(uint32_t baseAddr,
                                  uint8_t instance,
                                  uint8_t trigger,
                                  sim_ftm_trg_src_t select);

/*!
 * @brief Gets the FlexTimer x hardware trigger y source select setting.
 *
 * This function  gets the FlexTimer x hardware trigger y source select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param trigger      hardware trigger y
 * @return select FlexTimer x hardware trigger y source select setting
 */
sim_ftm_trg_src_t SIM_HAL_GetFtmTriggerSrcMode(uint32_t baseAddr, uint8_t instance, uint8_t trigger);

/*!
 * @brief Sets the FlexTimer x external clock pin select setting.
 *
 * This function  selects the source of FTMx external clock pin select.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select FTMx external clock pin select
 *               - 0: FTMx external clock driven by FTM CLKIN0 pin.
 *               - 1: FTMx external clock driven by FTM CLKIN1 pin.
 */
void SIM_HAL_SetFtmExternalClkPinMode(uint32_t baseAddr, uint8_t instance, sim_ftm_clk_sel_t select);

/*!
 * @brief Gets the FlexTimer x external clock pin select setting.
 *
 * This function  gets the FlexTimer x external clock pin select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select FlexTimer x external clock pin select setting
 */
sim_ftm_clk_sel_t SIM_HAL_GetFtmExternalClkPinMode(uint32_t baseAddr, uint8_t instance);

/*!
 * @brief Sets the FlexTimer x channel y input capture source select setting.
 *
 * This function  selects the FlexTimer x channel y input capture source.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @param select FlexTimer x channel y input capture source
 *               See the reference manual for detailed definition for each channel and selection.
 */
void SIM_HAL_SetFtmChSrcMode(uint32_t baseAddr, uint8_t instance, uint8_t channel, sim_ftm_ch_src_t select);

/*!
 * @brief Gets the FlexTimer x channel y input capture source select setting.
 *
 * This function  gets the FlexTimer x channel y input capture source select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @return select FlexTimer x channel y input capture source select setting
 */
sim_ftm_ch_src_t SIM_HAL_GetFtmChSrcMode(uint32_t baseAddr, uint8_t instance, uint8_t channel);

/*!
 * @brief Sets the FlexTimer x fault y select setting.
 *
 * This function  sets the FlexTimer x fault y select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param fault        fault y
 * @param select FlexTimer x fault y select setting
 *               - 0: FlexTimer x fault y select 0.
 *               - 1: FlexTimer x fault y select 1.
 */
void SIM_HAL_SetFtmFaultSelMode(uint32_t baseAddr, uint8_t instance, uint8_t fault, sim_ftm_flt_sel_t select);

/*!
 * @brief Gets the FlexTimer x fault y select setting.
 *
 * This function  gets the FlexTimer x fault y select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param fault        fault y
 * @return select FlexTimer x fault y select setting
 */
sim_ftm_flt_sel_t SIM_HAL_GetFtmFaultSelMode(uint32_t baseAddr, uint8_t instance, uint8_t fault);
#endif

#if FSL_FEATURE_SIM_OPT_HAS_TPM
/*!
 * @brief Sets the Timer/PWM x external clock pin select setting.
 *
 * This function  selects the source of the Timer/PWM x external clock pin select.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select Timer/PWM x external clock pin select
 *               - 0: Timer/PWM x external clock driven by the TPM_CLKIN0 pin.
 *               - 1: Timer/PWM x external clock driven by the TPM_CLKIN1 pin.
 */
void SIM_HAL_SetTpmExternalClkPinSelMode(uint32_t baseAddr, uint8_t instance, sim_tpm_clk_sel_t select);

/*!
 * @brief Gets the Timer/PWM x external clock pin select setting.
 *
 * This function  gets the Timer/PWM x external clock pin select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select Timer/PWM x external clock pin select setting
 */
sim_tpm_clk_sel_t SIM_HAL_GetTpmExternalClkPinSelMode(uint32_t baseAddr, uint8_t instance);

/*!
 * @brief Sets the Timer/PWM x channel y input capture source select setting.
 *
 * This function  selects the Timer/PWM x channel y input capture source.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      TPM channel y
 * @param select Timer/PWM x channel y input capture source
 *               - 0: TPMx_CH0 signal
 *               - 1: CMP0 output
 */
void SIM_HAL_SetTpmChSrcMode(uint32_t baseAddr, uint8_t instance, uint8_t channel, sim_tpm_ch_src_t select);

/*!
 * @brief Gets the Timer/PWM x channel y input capture source select setting.
 *
 * This function  gets the Timer/PWM x channel y input capture source select setting.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      Tpm channel y
 * @return select Timer/PWM x channel y input capture source select setting
 */
sim_tpm_ch_src_t SIM_HAL_GetTpmChSrcMode(uint32_t baseAddr, uint8_t instance, uint8_t channel);
#endif

#if FSL_FEATURE_SIM_SDID_HAS_FAMILYID
/*!
 * @brief Gets the Kinetis Family ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Family ID in the System Device ID register.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return id Kinetis Family ID
 */
static inline uint32_t SIM_HAL_GetFamilyId(uint32_t baseAddr)
{
    return BR_SIM_SDID_FAMILYID(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_SDID_HAS_SUBFAMID
/*!
 * @brief Gets the Kinetis Sub-Family ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Sub-Family ID in System Device ID register.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return id Kinetis Sub-Family ID
 */
static inline uint32_t SIM_HAL_GetSubFamilyId(uint32_t baseAddr)
{
    return BR_SIM_SDID_SUBFAMID(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_SDID_HAS_SERIESID
/*!
 * @brief Gets the Kinetis SeriesID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Series ID in System Device ID register.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return id Kinetis Series ID
 */
static inline uint32_t SIM_HAL_GetSeriesId(uint32_t baseAddr)
{
    return BR_SIM_SDID_SERIESID(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_SDID_HAS_FAMID
/*!
 * @brief Gets the Kinetis Fam ID in System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Fam ID in System Device ID register.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return id Kinetis Fam ID
 */
static inline uint32_t SIM_HAL_GetFamId(uint32_t baseAddr)
{
    return BR_SIM_SDID_FAMID(baseAddr);
}
#endif

/*!
 * @brief Gets the Kinetis Pincount ID in System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Pincount ID in System Device ID register.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return id Kinetis Pincount ID
 */
static inline uint32_t SIM_HAL_GetPinCntId(uint32_t baseAddr)
{
    return BR_SIM_SDID_PINID(baseAddr);
}

/*!
 * @brief Gets the Kinetis Revision ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Revision ID in System Device ID register.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return id Kinetis Revision ID
 */
static inline uint32_t SIM_HAL_GetRevId(uint32_t baseAddr)
{
    return BR_SIM_SDID_REVID(baseAddr);
}

#if FSL_FEATURE_SIM_SDID_HAS_DIEID
/*!
 * @brief Gets the Kinetis Die ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Die ID in System Device ID register.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return id Kinetis Die ID
 */
static inline uint32_t SIM_HAL_GetDieId(uint32_t baseAddr)
{
    return BR_SIM_SDID_DIEID(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE
/*!
 * @brief Gets the Kinetis SRAM size in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis SRAM Size in System Device ID register.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return id Kinetis SRAM Size
 */
static inline uint32_t SIM_HAL_GetSramSize(uint32_t baseAddr)
{
    return BR_SIM_SDID_SRAMSIZE(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE
/*!
 * @brief Gets the FlexNVM size in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the FlexNVM size in the Flash Configuration Register 1.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return size FlexNVM Size
 */
static inline uint32_t SIM_HAL_GetFlexnvmSize(uint32_t baseAddr)
{
    return BR_SIM_FCFG1_NVMSIZE(baseAddr);
}
#endif

/*!
 * @brief Gets the program flash size in  the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the program flash size in the Flash Configuration Register 1.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return size Program flash Size
 */
static inline uint32_t SIM_HAL_GetProgramFlashSize(uint32_t baseAddr)
{
    return BR_SIM_FCFG1_PFSIZE(baseAddr);
}

#if FSL_FEATURE_SIM_FCFG_HAS_EESIZE
/*!
 * @brief Gets the EEProm size in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the EEProm size in the Flash Configuration Register 1.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return size EEProm Size
 */
static inline uint32_t SIM_HAL_GetEepromSize(uint32_t baseAddr)
{
    return BR_SIM_FCFG1_EESIZE(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_DEPART
/*!
 * @brief Gets the FlexNVM partition in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the FlexNVM partition in the Flash Configuration Register 1
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting FlexNVM partition setting
 */
static inline uint32_t SIM_HAL_GetFlexnvmPartition(uint32_t baseAddr)
{
    return BR_SIM_FCFG1_DEPART(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE
/*!
 * @brief Sets the Flash Doze in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  sets the Flash Doze in the Flash Configuration Register 1.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param setting Flash Doze setting
 */
static inline void SIM_HAL_SetFlashDoze(uint32_t baseAddr, uint32_t setting)
{
    BW_SIM_FCFG1_FLASHDOZE(baseAddr, setting);
}

/*!
 * @brief Gets the Flash Doze in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash Doze in the Flash Configuration Register 1.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting Flash Doze setting
 */
static inline uint32_t SIM_HAL_GetFlashDoze(uint32_t baseAddr)
{
    return BR_SIM_FCFG1_FLASHDOZE(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS
/*!
 * @brief Sets the Flash disable setting in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  sets the Flash disable setting in the Flash Configuration Register 1.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @param disable      Flash disable setting
 */
static inline void SIM_HAL_SetFlashDisableCmd(uint32_t baseAddr, bool disable)
{
    BW_SIM_FCFG1_FLASHDIS(baseAddr, disable);
}

/*!
 * @brief Gets the Flash disable setting in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash disable setting in the Flash Configuration Register 1.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return setting Flash disable setting
 */
static inline bool SIM_HAL_GetFlashDisableCmd(uint32_t baseAddr)
{
    return (bool)BR_SIM_FCFG1_FLASHDIS(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0
/*!
 * @brief Gets the Flash maximum address block 0 in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash maximum block 0 in Flash Configuration Register 2.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return address Flash maximum block 0 address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock0(uint32_t baseAddr)
{
    return BR_SIM_FCFG2_MAXADDR0(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1
/*!
 * @brief Gets the Flash maximum address block 1 in Flash Configuration Register 2.
 *
 * This function  gets the Flash maximum block 1 in Flash Configuration Register 1.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return address Flash maximum block 0 address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock1(uint32_t baseAddr)
{
    return BR_SIM_FCFG2_MAXADDR1(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01
/*!
 * @brief Gets the Flash maximum address block 0 in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function  gets the Flash maximum block 0 in Flash Configuration Register 2.
 *
 * @param baseAddr     Base address for current SIM instance.
 * @return address Flash maximum block 0 address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock01(uint32_t baseAddr)
{
    return BR_SIM_FCFG2_MAXADDR01(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23
/*!
 * @brief Gets the Flash maximum address block 1 in the Flash Configuration Register 2.
 *
 * This function  gets the Flash maximum block 1 in Flash Configuration Register 1.
 *
 * @param baseAddr Base address for current SIM instance.
 * @return address Flash maximum block 0 address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock23(uint32_t baseAddr)
{
    return BR_SIM_FCFG2_MAXADDR23(baseAddr);
}
#endif

#if FSL_FEATURE_SIM_FCFG_HAS_PFLSH
/*!
 * @brief Gets the program flash in the Flash Configuration Register 2.
 *
 * This function  gets the program flash maximum block 0 in Flash Configuration Register 1.
 *
 * @param baseAddr Base address for current SIM instance.
 * @return status program flash status
 */
static inline uint32_t SIM_HAL_GetProgramFlashCmd(uint32_t baseAddr)
{
    return BR_SIM_FCFG2_PFLSH(baseAddr);
}
#endif

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/


/*
 * Include the CPU-specific clock API header files.
 */
#if (defined(CPU_MK02FN128VFM10) || defined(CPU_MK02FN64VFM10) || defined(CPU_MK02FN128VLF10) || \
    defined(CPU_MK02FN64VLF10) || defined(CPU_MK02FN128VLH10) || defined(CPU_MK02FN64VLH10))

    #define K02F12810_SERIES

#elif (defined(CPU_MK20DX128VMP5) || defined(CPU_MK20DN128VMP5) || defined(CPU_MK20DX64VMP5) || \
    defined(CPU_MK20DN64VMP5) || defined(CPU_MK20DX32VMP5) || defined(CPU_MK20DN32VMP5) || \
    defined(CPU_MK20DX128VLH5) || defined(CPU_MK20DN128VLH5) || defined(CPU_MK20DX64VLH5) || \
    defined(CPU_MK20DN64VLH5) || defined(CPU_MK20DX32VLH5) || defined(CPU_MK20DN32VLH5) || \
    defined(CPU_MK20DX128VFM5) || defined(CPU_MK20DN128VFM5) || defined(CPU_MK20DX64VFM5) || \
    defined(CPU_MK20DN64VFM5) || defined(CPU_MK20DX32VFM5) || defined(CPU_MK20DN32VFM5) || \
    defined(CPU_MK20DX128VFT5) || defined(CPU_MK20DN128VFT5) || defined(CPU_MK20DX64VFT5) || \
    defined(CPU_MK20DN64VFT5) || defined(CPU_MK20DX32VFT5) || defined(CPU_MK20DN32VFT5) || \
    defined(CPU_MK20DX128VLF5) || defined(CPU_MK20DN128VLF5) || defined(CPU_MK20DX64VLF5) || \
    defined(CPU_MK20DN64VLF5) || defined(CPU_MK20DX32VLF5) || defined(CPU_MK20DN32VLF5))

    #define K20D5_SERIES


#elif (defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || \
    defined(CPU_MK22FN128VMP10))

    #define K22F12810_SERIES

    /* Clock System Level API header file */
    #include "MK22F12810/fsl_sim_hal_K22F12810.h"

#elif (defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || \
    defined(CPU_MK22FN256VMP12))

    #define K22F25612_SERIES

    /* Clock System Level API header file */
    #include "MK22F25612/fsl_sim_hal_K22F25612.h"



#elif (defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12))

    #define K22F51212_SERIES

    /* Clock System Level API header file */
    #include "MK22F51212/fsl_sim_hal_K22F51212.h"


#elif (defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLQ12))

    #define K24F12_SERIES

   /* Clock System Level API header file */
    #include "MK24F12/fsl_sim_hal_K24F12.h"

#elif (defined(CPU_MK24FN256VDC12))

    #define K24F25612_SERIES


#elif (defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12))

    #define K63F12_SERIES

    /* Clock System Level API header file */
    #include "MK63F12/fsl_sim_hal_K63F12.h"

#elif (defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || defined(CPU_MK64FX512VLL12) || \
    defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VMD12) || defined(CPU_MK64FN1M0VMD12))

    #define K64F12_SERIES

    /* Clock System Level API header file */
    #include "MK64F12/fsl_sim_hal_K64F12.h"

#elif (defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || \
    defined(CPU_MK65FX1M0VMI18))

    #define K65F18_SERIES


#elif (defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || \
    defined(CPU_MK66FX1M0VMD18))

    #define K66F18_SERIES


#elif (defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || \
    defined(CPU_MK70FX512VMF15) || defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || \
    defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))

    #define K70F12_SERIES


#elif (defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || \
    defined(CPU_MK70FX512VMF15) || defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || \
    defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))

    #define K70F15_SERIES


#elif (defined(CPU_MKL02Z32CAF4) || defined(CPU_MKL02Z8VFG4) || defined(CPU_MKL02Z16VFG4) || \
    defined(CPU_MKL02Z32VFG4) || defined(CPU_MKL02Z16VFK4) || defined(CPU_MKL02Z32VFK4) || \
    defined(CPU_MKL02Z16VFM4) || defined(CPU_MKL02Z32VFM4))

    #define KL02Z4_SERIES


#elif (defined(CPU_MKL03Z32CAF4) || defined(CPU_MKL03Z8VFG4) || defined(CPU_MKL03Z16VFG4) || \
    defined(CPU_MKL03Z32VFG4) || defined(CPU_MKL03Z8VFK4) || defined(CPU_MKL03Z16VFK4) || \
    defined(CPU_MKL03Z32VFK4))

    #define KL03Z4_SERIES


#elif (defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || defined(CPU_MKL05Z32VFK4) || \
    defined(CPU_MKL05Z8VLC4) || defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || \
    defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || defined(CPU_MKL05Z32VFM4) || \
    defined(CPU_MKL05Z16VLF4) || defined(CPU_MKL05Z32VLF4))

    #define KL05Z4_SERIES


#elif (defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z128VFM4) || defined(CPU_MKL13Z256VFM4) || \
    defined(CPU_MKL13Z64VFT4) || defined(CPU_MKL13Z128VFT4) || defined(CPU_MKL13Z256VFT4) || \
    defined(CPU_MKL13Z64VLH4) || defined(CPU_MKL13Z128VLH4) || defined(CPU_MKL13Z256VLH4) || \
    defined(CPU_MKL13Z64VMP4) || defined(CPU_MKL13Z128VMP4) || defined(CPU_MKL13Z256VMP4))

    #define KL13Z4_SERIES


#elif (defined(CPU_MKL23Z64VFM4) || defined(CPU_MKL23Z128VFM4) || defined(CPU_MKL23Z256VFM4) || \
    defined(CPU_MKL23Z64VFT4) || defined(CPU_MKL23Z128VFT4) || defined(CPU_MKL23Z256VFT4) || \
    defined(CPU_MKL23Z64VLH4) || defined(CPU_MKL23Z128VLH4) || defined(CPU_MKL23Z256VLH4) || \
    defined(CPU_MKL23Z64VMP4) || defined(CPU_MKL23Z128VMP4) || defined(CPU_MKL23Z256VMP4))

    #define KL23Z4_SERIES


#elif (defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || \
    defined(CPU_MKL25Z32VFT4) || defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || \
    defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || defined(CPU_MKL25Z128VLH4) || \
    defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4))

    #define KL25Z4_SERIES

    /* Clock System Level API header file */
    #include "MKL25Z4/fsl_sim_hal_KL25Z4.h"

#elif (defined(CPU_MKL26Z32VFM4) || defined(CPU_MKL26Z64VFM4) || defined(CPU_MKL26Z128VFM4) || \
    defined(CPU_MKL26Z32VFT4) || defined(CPU_MKL26Z64VFT4) || defined(CPU_MKL26Z128VFT4) || \
    defined(CPU_MKL26Z32VLH4) || defined(CPU_MKL26Z64VLH4) || defined(CPU_MKL26Z128VLH4) || \
    defined(CPU_MKL26Z256VLH4) || defined(CPU_MKL26Z256VLK4) || defined(CPU_MKL26Z128VLL4) || \
    defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || defined(CPU_MKL26Z256VMC4))

    #define KL26Z4_SERIES


#elif (defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || defined(CPU_MKL33Z128VMP4) || \
    defined(CPU_MKL33Z256VMP4))

    #define KL33Z4_SERIES


#elif (defined(CPU_MKL43Z64VLH4) || defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || \
    defined(CPU_MKL43Z64VMP4) || defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4))

    #define KL43Z4_SERIES


#elif (defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4))

    #define KL46Z4_SERIES


#elif (defined(CPU_MKV30F128VFM10) || defined(CPU_MKV30F64VFM10) || defined(CPU_MKV30F128VLF10) || \
    defined(CPU_MKV30F64VLF10) || defined(CPU_MKV30F128VLH10) || defined(CPU_MKV30F64VLH10))

    #define KV30F12810_SERIES


#elif (defined(CPU_MKV31F128VLH10) || defined(CPU_MKV31F128VLL10))

    #define KV31F12810_SERIES

    /* Clock System Level API header file */
    #include "MKV31F12810/fsl_sim_hal_KV31F12810.h"

#elif (defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12))

    #define KV31F25612_SERIES

    /* Clock System Level API header file */
    #include "MKV31F25612/fsl_sim_hal_KV31F25612.h"


#elif (defined(CPU_MKV31F512VLH12) || defined(CPU_MKV31F512VLL12))

    #define KV31F51212_SERIES

    /* Clock System Level API header file */
    #include "MKV31F51212/fsl_sim_hal_KV31F51212.h"

#elif (defined(CPU_MKV40F128VLH15) || defined(CPU_MKV40F128VLL15) || defined(CPU_MKV40F256VLH15) || \
    defined(CPU_MKV40F256VLL15) || defined(CPU_MKV40F64VLH15))

    #define KV40F15_SERIES


#elif (defined(CPU_MKV43F128VLH15) || defined(CPU_MKV43F128VLL15) || defined(CPU_MKV43F64VLH15))

    #define KV43F15_SERIES


#elif (defined(CPU_MKV44F128VLH15) || defined(CPU_MKV44F128VLL15) || defined(CPU_MKV44F64VLH15))

    #define KV44F15_SERIES


#elif (defined(CPU_MKV45F128VLH15) || defined(CPU_MKV45F128VLL15) || defined(CPU_MKV45F256VLH15) || \
    defined(CPU_MKV45F256VLL15))

    #define KV45F15_SERIES


#elif (defined(CPU_MKV46F128VLH15) || defined(CPU_MKV46F128VLL15) || defined(CPU_MKV46F256VLH15) || \
    defined(CPU_MKV46F256VLL15))

    #define KV46F15_SERIES


#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_SIM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

