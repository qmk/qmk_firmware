/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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
#if !defined(__FSL_MCG_HAL_MODES_H__)
#define __FSL_MCG_HAL_MODES_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_mcg_features.h"
#include "fsl_mcg_hal.h"

//! @addtogroup mcg_hal
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/*! @brief MCG mode definitions */
typedef enum _mcg_modes {
    kMcgModeFEI,                    /* FEI - FLL Engaged Internal    */
    kMcgModeFEE,                    /* FEE - FLL Engaged External    */
    kMcgModeFBI,                    /* FBI - FLL Bypassed Internal   */
    kMcgModeFBE,                    /* FBE - FLL Bypassed External   */
    kMcgModePEE,                    /* PEE - PLL Engaged External    */
    kMcgModePBE,                    /* PBE - PLL Bypassed Enternal   */
    kMcgModeBLPI,                   /* BLPI - Bypassed Low Power Internal    */
    kMcgModeBLPE,                   /* BLPE - Bypassed Low Power External    */
    kMcgModeSTOP,                   /* STOP - Stop   */
    kMcgModeError                   /* Unknown mode */
} mcg_modes_t;

/*! @brief MCG mode transition API error code definitions */
typedef enum McgModeErrorCode {

    /* MCG mode error codes */

    kMcgErrNotInFeiMode =  0x01,    /* - Not in FEI mode */
    kMcgErrNotInFeeMode =  0x02,    /* - Not in FEE mode */
    kMcgErrNotInFbiMode =  0x03,    /* - Not in FBI mode */
    kMcgErrNotInFbeMode =  0x04,    /* - Not in FBE mode */
    kMcgErrNotInBlpiMode = 0x05,    /* - Not in BLPI mode */
    kMcgErrNotInBlpeMode = 0x06,    /* - Not in BLPE mode */
    kMcgErrNotInPbeMode =  0x07,    /* - Not in PBE mode */
    kMcgErrNotInPeeMode =  0x08,    /* - Not in PEE mode */

    /* CLock MUX switching error codes */

    kMcgErrIrefstClearTimeOut =  0x11,    /* - IREFST did not clear within allowed time, FLL 
                                         reference did not switch over from internal to 
                                         external clock */
    kMcgErrIrefstSetTimeout =   0x12,    /* - IREFST did not set within allowed time, the FLL 
                                         reference did not switch over from external to 
                                         internal clock(NEED TO CHECK IN MOVES TO FBI MODE) */
    kMcgErrIrcstClearTimeout =    0x13,    /* - IRCST did not clear within allowed time, 
                                         slow IRC is not selected */
    kMcgErrIrefstSetTimeout1 =   0x14,    /* - IREFST did not set within allowed time, 
                                         fast IRC is not selected */
    kMcgErrPllstClearTimeout =   0x15,    /* - PLLST did not clear, PLLST did not switch to 
                                         FLL output, FLL is not running */
    kMcgErrPllstSetTimeout =     0x16,    /* - PLLST did not set, PLLST did not switch to PLL 
                                         ouptut, PLL is not running */
    kMcgErrPllcst =              0x17,    /* - PLLCST did not switch to the correct state, 
                                         the correct PLL is not selected as PLLS clock source */
    kMcgErrClkst0 =              0x18,    /* - CLKST != 0, MCG did not switch to FLL output */ 
    kMcgErrClkst1 =              0x19,    /* - CLKST != 1, MCG did not switch to internal reference
                                         clock source */
    kMcgErrClkst2 =              0x1A,    /* - CLKST != 2, MCG did not switch to external clock */
    kMcgErrClkst3 =              0x1B,    /* - CLKST != 3, MCG did not switch to PLL */

    /* Oscillator error codes */

    kMcgErrOscEtalRange =        0x21,    /* - external frequency is bigger than max frequency */
    kMcgErrOscXtalRange =        0x22,    /* - crystal frequency outside allowed range */
    kMcgErrOscSetTimeout =       0x23,    /* - OSCINIT/OSCINIT2 did not set within allowed time */

    /* IRC and FLL error codes */

    kMcgErrIrcSlowRange =        0x31,    /* - slow IRC is outside allowed range */
    kMcgErrIrcFastRange =        0x32,    /* - fast IRC is outside allowed range */
    kMcgErrFllRange0Min =        0x33,    /* - FLL frequency is below minimum value for range 0 */
    kMcgErrFllRange0Max =        0x34,    /* - FLL frequency is above maximum value for range 0 */
    kMcgErrFllRange1Min =        0x35,    /* - FLL frequency is below minimum value for range 1 */
    kMcgErrFllRange1Max =        0x36,    /* - FLL frequency is above maximum value for range 1 */
    kMcgErrFllRange2Min =        0x37,    /* - FLL frequency is below minimum value for range 2 */
    kMcgErrFllRange2Max =        0x38,    /* - FLL frequency is above maximum value for range 2 */
    kMcgErrFllRange3Min =        0x39,    /* - FLL frequency is below minimum value for range 3 */
    kMcgErrFllRange3Max =        0x3A,    /* - FLL frequency is above maximum value for range 3 */
    kMcgErrFllDrstDrsRange  =    0x3B,    /* - DRS is out of range */
    
    kMcgErrFllFreqency  =        0x3C,

    /* PLL error codes */

    kMcgErrPllPrdidRange =       0x41,    /* - PRDIV outside allowed range */
    kMcgErrPllVdivRange =        0x42,    /* - VDIV outside allowed range */
    kMcgErrPllRefClkRange =      0x43,    /* - PLL reference clock frequency, out of allowed range */
    kMcgErrPllLockBit =          0x44,    /* - LOCK or LOCK2 bit did not set */
    kMcgErrPllOutClkRange =      0x45,    /* - PLL output frequency is outside allowed range (NEED 
                                             TO ADD THIS CHECK TO fbe_pbe and blpe_pbe) only in 
                                             fei-pee at this time */
    kMcgErrMax = 0x1000
} mcg_mode_error_code_t;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/*!
 * @brief Gets the current MCG mode.
 *
 * This is an internal function that checks the MCG registers and determine
 * the current MCG mode
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @return      mcgMode     Current MCG mode or error code mcg_modes_t
 */
mcg_modes_t CLOCK_HAL_GetMcgMode(uint32_t baseAddr);

/*!
 * @brief Checks the FLL frequency integrity.
 *
 * This function calculates and checks the FLL frequency value based on input value.
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       fllRef  - FLL reference clock in Hz.
 *
 * @return      value       FLL output frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_GetFllFrequency(uint32_t baseAddr, int32_t fllRef);

/*!
 * @brief  Mode transition FEI to FEE mode
 *
 * This function transitions the MCG from FEI mode to FEE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       oscselVal   - oscillator selection value
 *                            0 - OSC 0,  1 - RTC 32k, 2 - IRC 48M
 * @param       crystalVal  - external clock frequency in Hz
 *                            oscselVal - 0
 *                             erefsVal - 0: osc0 external clock frequency
 *                             erefsVal - 1: osc0 crystal clock frequency
 *                            oscselVal - 1: RTC 32Khz clock source frequency
 *                            oscselVal - 2: IRC 48Mhz clock source frequency
 * @param       hgoVal      - selects whether low power or high gain mode is selected
 *                            for the crystal oscillator. This value is only valid when
 *                            oscselVal is 0 and erefsVal is 1.
 * @param       erefsVal    - selects external clock (=0) or crystal OSC (=1) 
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFeiToFeeMode(uint32_t baseAddr, mcg_oscsel_select_t oscselVal,
                                   uint32_t crystalVal, mcg_high_gain_osc_select_t hgoVal,
                                   mcg_external_ref_clock_select_t erefsVal);

/*!
 * @brief Mode transition FEI to FBI mode
 *
 * This function transitions the MCG from FEI mode to FBI mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       ircFreq     - internal reference clock frequency value
 * @param       ircSelect   - slow or fast clock selection
 *                             0: slow, 1: fast
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFeiToFbiMode(uint32_t baseAddr, uint32_t ircFreq,
                                   mcg_internal_ref_clock_select_t ircSelect);

/*!
 * @brief Mode transition FEI to FBE mode
 *
 * This function transitions the MCG from FEI mode to FBE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       oscselVal   - oscillator selection value
 *                            0 - OSC 0,  1 - RTC 32k, 2 - IRC 48M
 * @param       crystalVal  - external clock frequency in Hz
 *                            oscselVal - 0
 *                             erefsVal - 0: osc0 external clock frequency
 *                             erefsVal - 1: osc0 crystal clock frequency
 *                            oscselVal - 1: RTC 32Khz clock source frequency
 *                            oscselVal - 2: IRC 48Mhz clock source frequency
 * @param       hgoVal      - selects whether low power or high gain mode is selected
 *                            for the crystal oscillator. This value is only valid when
 *                            oscselVal is 0 and erefsVal is 1.
 * @param       erefsVal    - selects external clock (=0) or crystal OSC (=1) 
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFeiToFbeMode(uint32_t baseAddr, mcg_oscsel_select_t oscselVal,
                                   uint32_t crystalVal, mcg_high_gain_osc_select_t hgoVal,
                                   mcg_external_ref_clock_select_t erefsVal);

/*!
 * @brief Mode transition FEE to FEI mode
 *
 * This function transitions the MCG from FEE mode to FEI mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       ircFreq     - internal reference clock frequency value (slow)
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFeeToFeiMode(uint32_t baseAddr, uint32_t ircFreq);

/*!
 * @brief Mode transition FEE to FBI mode
 *
 * This function transitions the MCG from FEE mode to FBI mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       ircFreq     - internal reference clock frequency value
 * @param       ircSelect   - slow or fast clock selection
 *                             0: slow, 1: fast
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFeeToFbiMode(uint32_t baseAddr, uint32_t ircFreq,
                                   mcg_internal_ref_clock_select_t ircSelect);

/*!
 * @brief Mode transition FEE to FBE mode
 *
 * This function transitions the MCG from FEE mode to FBE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external reference clock frequency value
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFeeToFbeMode(uint32_t baseAddr, uint32_t crystalVal);

/*!
 * @brief Mode transition FBI to FEI mode
 *
 * This function transitions the MCG from FBI mode to FEI mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       ircFreq     - internal reference clock frequency value (slow)
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFbiToFeiMode(uint32_t baseAddr, uint32_t ircFreq);

/*!
 * @brief Mode transition FBI to FEE mode
 *
 * This function transitions the MCG from FBI mode to FEE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       oscselVal   - oscillator selection value
 *                            0 - OSC 0,  1 - RTC 32k, 2 - IRC 48M
 * @param       crystalVal  - external clock frequency in Hz
 *                            oscselVal - 0
 *                             erefsVal - 0: osc0 external clock frequency
 *                             erefsVal - 1: osc0 crystal clock frequency
 *                            oscselVal - 1: RTC 32Khz clock source frequency
 *                            oscselVal - 2: IRC 48Mhz clock source frequency
 * @param       hgoVal      - selects whether low power or high gain mode is selected
 *                            for the crystal oscillator. This value is only valid when
 *                            oscselVal is 0 and erefsVal is 1.
 * @param       erefsVal    - selects external clock (=0) or crystal OSC (=1) 
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFbiToFeeMode(uint32_t baseAddr, mcg_oscsel_select_t oscselVal,
                                   uint32_t crystalVal, mcg_high_gain_osc_select_t hgoVal,
                                   mcg_external_ref_clock_select_t erefsVal); 

/*!
 * @brief Mode transition FBI to FBE mode
 *
 * This function transitions the MCG from FBI mode to FBE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       oscselVal   - oscillator selection value
 *                            0 - OSC 0,  1 - RTC 32k, 2 - IRC 48M
 * @param       crystalVal  - external clock frequency in Hz
 *                            oscselVal - 0
 *                             erefsVal - 0: osc0 external clock frequency
 *                             erefsVal - 1: osc0 crystal clock frequency
 *                            oscselVal - 1: RTC 32Khz clock source frequency
 *                            oscselVal - 2: IRC 48Mhz clock source frequency
 * @param       hgoVal      - selects whether low power or high gain mode is selected
 *                            for the crystal oscillator. This value is only valid when
 *                            oscselVal is 0 and erefsVal is 1.
 * @param       erefsVal    - selects external clock (=0) or crystal OSC (=1) 
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFbiToFbeMode(uint32_t baseAddr, mcg_oscsel_select_t oscselVal, 
                                   uint32_t crystalVal, mcg_high_gain_osc_select_t hgoVal,
                                   mcg_external_ref_clock_select_t erefsVal);

/*!
 * @brief Mode transition FBI to BLPI mode
 *
 * This function transitions the MCG from FBI mode to BLPI mode.This is
 * achieved by setting the MCG_C2[LP] bit. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       ircFreq     - internal reference clock frequency value
 * @param       ircSelect   - slow or fast clock selection
 *                             0: slow, 1: fast
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFbiToBlpiMode(uint32_t baseAddr, uint32_t ircFreq,
                                    mcg_internal_ref_clock_select_t ircSelect);

/*!
 * @brief Mode transition BLPI to FBI mode
 *
 * This function transitions the MCG from BLPI mode to FBI mode.This is
 * achieved by clearing the MCG_C2[LP] bit. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       ircFreq     - internal reference clock frequency value
 * @param       ircSelect   - slow or fast clock selection
 *                             0: slow, 1: fast
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetBlpiToFbiMode(uint32_t baseAddr, uint32_t ircFreq, uint8_t ircSelect);

/*!
 * @brief Mode transition FBE to FEE mode
 *
 * This function transitions the MCG from FBE mode to FEE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external reference clock frequency value
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFbeToFeeMode(uint32_t baseAddr, uint32_t crystalVal);

/*!
 * @brief Mode transition FBE to FEI mode
 *
 * This function transitions the MCG from FBE mode to FEI mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       ircFreq     - internal reference clock frequency value (slow)
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbeToFeiMode(uint32_t baseAddr, uint32_t ircFreq);

/*!
 * @brief Mode transition FBE to FBI mode
 *
 * This function transitions the MCG from FBE mode to FBI mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       ircFreq     - internal reference clock frequency value
 * @param       ircSelect   - slow or fast clock selection
 *                             0: slow, 1: fast
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbeToFbiMode(uint32_t baseAddr, uint32_t ircFreq,
                                   mcg_internal_ref_clock_select_t ircSelect);

/*!
 * @brief Mode transition FBE to PBE mode
 *
 * This function transitions the MCG from FBE mode to PBE mode. 
 * The function requires the desired OSC and PLL be passed in to it for compatibility 
 * with the future support of OSC/PLL selection
 * (This function presently only supports OSC0 as PLL source)
 * 
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external clock frequency in Hz
 * @param       pllcsSelect - 0 to select PLL0, non-zero to select PLL1.
 * @param       prdivVal    - value to divide the external clock source by to create 
 *                           the desired PLL reference clock frequency
 * @param       vdivVal     - value to multiply the PLL reference clock frequency by
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFbeToPbeMode(uint32_t baseAddr, uint32_t crystalVal,
                                   mcg_pll_clk_select_t pllcsSelect, 
                                   uint8_t prdivVal, uint8_t vdivVal);

/*!
 * @brief Mode transition FBE to BLPE mode
 *
 * This function transitions the MCG from FBE mode to BLPE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal   - external clock frequency in Hz
 *
 * @return      value        MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetFbeToBlpeMode(uint32_t baseAddr, uint32_t crystalVal);

/*!
 * @brief Mode transition PBE to FBE mode
 *
 * This function transitions the MCG from PBE mode to FBE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external clock frequency in Hz
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetPbeToFbeMode(uint32_t baseAddr, uint32_t crystalVal);

/*!
 * @brief Mode transition PBE to PEE mode
 *
 * This function transitions the MCG from PBE mode to PEE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external clock frequency in Hz
 * @param       pllcsSelect - PLLCS select setting
 *                            mcg_pll_clk_select_t is defined in fsl_mcg_hal.h
 *                            0: kMcgPllcsSelectPll0  PLL0 output clock is selected 
 *                            1: kMcgPllcsSelectPll1  PLL1 output clock is selected 
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetPbeToPeeMode(uint32_t baseAddr, uint32_t crystalVal,
                                   mcg_pll_clk_select_t pllcsSelect);

/*!
 * @brief Mode transition PBE to BLPE mode
 *
 * This function transitions the MCG from PBE mode to BLPE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external clock frequency in Hz
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetPbeToBlpeMode(uint32_t baseAddr, uint32_t crystalVal);

/*!
 * @brief Mode transition PEE to PBE mode
 *
 * This function transitions the MCG from PEE mode to PBE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external clock frequency in Hz
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetPeeToPbeMode(uint32_t baseAddr, uint32_t crystalVal);

/*!
 * @brief Mode transition BLPE to PBE mode
 *
 * This function transitions the MCG from BLPE mode to PBE mode. 
 * The function requires the desired OSC and PLL be passed in to it for compatibility 
 * with the future support of OSC/PLL selection
 * (This function presently only supports OSC0 as PLL source)
 * 
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external clock frequency in Hz
 * @param       pllcsSelect - 0 to select PLL0, non-zero to select PLL1.
 * @param       prdivVal    - value to divide the external clock source by to create 
 *                            the desired PLL reference clock frequency
 * @param       vdivVal     - value to multiply the PLL reference clock frequency by
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetBlpeToPbeMode(uint32_t baseAddr, uint32_t crystalVal,
                                    mcg_pll_clk_select_t pllcsSelect, 
                                    uint8_t prdivVal, uint8_t vdivVal);

/*!
 * @brief Mode transition BLPE to FBE mode
 *
 * This function transitions the MCG from BLPE mode to FBE mode. 
 *
 * @param       baseAddr  Base address for current MCG instance.
 * @param       crystalVal  - external reference clock frequency value
 *
 * @return      value       MCGCLKOUT frequency (Hz) or error code
 */
uint32_t CLOCK_HAL_SetBlpeToFbeMode(uint32_t baseAddr, uint32_t crystalVal);

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

#endif // __FSL_MCG_HAL_MODES_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
