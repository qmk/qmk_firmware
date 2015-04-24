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

#include "fsl_llwu_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetExternalInputPinMode
 * Description   : Set external input pin source mode
 * This function will set the external input pin source mode that will be used
 * as wake up source.
 * 
 *END**************************************************************************/
void LLWU_HAL_SetExternalInputPinMode(uint32_t baseAddr,
                                      llwu_external_pin_modes_t pinMode,
                                      uint32_t pinNumber)
{
    /* check pin number */
    assert(pinNumber < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);

    switch (pinNumber)
    {
    case 0:
        BW_LLWU_PE1_WUPE0(baseAddr, pinMode);
        break;
    case 1:
        BW_LLWU_PE1_WUPE1(baseAddr, pinMode);
        break;
    case 2:
        BW_LLWU_PE1_WUPE2(baseAddr, pinMode);
        break;
    case 3:
        BW_LLWU_PE1_WUPE3(baseAddr, pinMode);
        break;
    case 4:
        BW_LLWU_PE2_WUPE4(baseAddr, pinMode);
        break;
    case 5:
        BW_LLWU_PE2_WUPE5(baseAddr, pinMode);
        break;
    case 6:
        BW_LLWU_PE2_WUPE6(baseAddr, pinMode);
        break;
    case 7:
        BW_LLWU_PE2_WUPE7(baseAddr, pinMode);
        break;
    case 8:
        BW_LLWU_PE3_WUPE8(baseAddr, pinMode);
        break;
    case 9:
        BW_LLWU_PE3_WUPE9(baseAddr, pinMode);
        break;
    case 10:
        BW_LLWU_PE3_WUPE10(baseAddr, pinMode);
        break;
    case 11:
        BW_LLWU_PE3_WUPE11(baseAddr, pinMode);
        break;
    case 12:
        BW_LLWU_PE4_WUPE12(baseAddr, pinMode);
        break;
    case 13:
        BW_LLWU_PE4_WUPE13(baseAddr, pinMode);
        break;
    case 14:
        BW_LLWU_PE4_WUPE14(baseAddr, pinMode);
        break;
    case 15:
        BW_LLWU_PE4_WUPE15(baseAddr, pinMode);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetExternalInputPinMode
 * Description   : Get external input pin source mode
 * This function will get the external input pin source mode that will be used
 * as wake up source.
 * 
 *END**************************************************************************/
llwu_external_pin_modes_t LLWU_HAL_GetExternalInputPinMode(uint32_t baseAddr,
                                                           uint32_t pinNumber)
{
    llwu_external_pin_modes_t retValue = (llwu_external_pin_modes_t)0;

    /* check pin number */
    assert(pinNumber < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);

    switch (pinNumber)
    {
    case 0:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE1_WUPE0(baseAddr);
        break;
    case 1:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE1_WUPE1(baseAddr);
        break;
    case 2:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE1_WUPE2(baseAddr);
        break;
    case 3:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE1_WUPE3(baseAddr);
        break;
    case 4:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE2_WUPE4(baseAddr);
        break;
    case 5:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE2_WUPE5(baseAddr);
        break;
    case 6:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE2_WUPE6(baseAddr);
        break;
    case 7:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE2_WUPE7(baseAddr);
        break;
    case 8:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE3_WUPE8(baseAddr);
        break;
    case 9:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE3_WUPE9(baseAddr);
        break;
    case 10:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE3_WUPE10(baseAddr);
        break;
    case 11:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE3_WUPE11(baseAddr);
        break;
    case 12:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE4_WUPE12(baseAddr);
        break;
    case 13:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE4_WUPE13(baseAddr);
        break;
    case 14:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE4_WUPE14(baseAddr);
        break;
    case 15:
        retValue = (llwu_external_pin_modes_t)BR_LLWU_PE4_WUPE15(baseAddr);
        break;
    default:
        retValue = (llwu_external_pin_modes_t)0;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetInternalModuleCmd
 * Description   : Enable/disable internal module source
 * This function will enable/disable the internal module source mode that will 
 * be used as wake up source. 
 * 
 *END**************************************************************************/
void LLWU_HAL_SetInternalModuleCmd(uint32_t baseAddr, uint32_t moduleNumber, bool enable)
{
    /* check module number */
    assert(moduleNumber < FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE);

    switch (moduleNumber)
    {
    case 0:
        BW_LLWU_ME_WUME0(baseAddr, enable);
        break;
    case 1:
        BW_LLWU_ME_WUME1(baseAddr, enable);
        break;
    case 2:
        BW_LLWU_ME_WUME2(baseAddr, enable);
        break;
    case 3:
        BW_LLWU_ME_WUME3(baseAddr, enable);
        break;
    case 4:
        BW_LLWU_ME_WUME4(baseAddr, enable);
        break;
    case 5:
        BW_LLWU_ME_WUME5(baseAddr, enable);
        break;
    case 6:
        BW_LLWU_ME_WUME6(baseAddr, enable);
        break;
    case 7:
        BW_LLWU_ME_WUME7(baseAddr, enable);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetInternalModuleCmd
 * Description   : Get internal module source enable setting
 * This function will enable/disable the internal module source mode that will 
 * be used as wake up source. 
 * 
 *END**************************************************************************/
bool LLWU_HAL_GetInternalModuleCmd(uint32_t baseAddr, uint32_t moduleNumber)
{
    bool retValue = false;

    /* check module number */
    assert(moduleNumber < FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE);

    switch (moduleNumber)
    {
    case 0:
        retValue = (bool)BR_LLWU_ME_WUME0(baseAddr);
        break;
    case 1:
        retValue = (bool)BR_LLWU_ME_WUME1(baseAddr);
        break;
    case 2:
        retValue = (bool)BR_LLWU_ME_WUME2(baseAddr);
        break;
    case 3:
        retValue = (bool)BR_LLWU_ME_WUME3(baseAddr);
        break;
    case 4:
        retValue = (bool)BR_LLWU_ME_WUME4(baseAddr);
        break;
    case 5:
        retValue = (bool)BR_LLWU_ME_WUME5(baseAddr);
        break;
    case 6:
        retValue = (bool)BR_LLWU_ME_WUME6(baseAddr);
        break;
    case 7:
        retValue = (bool)BR_LLWU_ME_WUME7(baseAddr);
        break;
    default:
        retValue = false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetExternalPinWakeupFlag
 * Description   : Get external wakeup source flag
 * This function will get the external wakeup source flag for specific pin. 
 * 
 *END**************************************************************************/
bool LLWU_HAL_GetExternalPinWakeupFlag(uint32_t baseAddr, uint32_t pinNumber)
{
    bool retValue = false;

    /* check pin number */
    assert(pinNumber < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);

    switch (pinNumber)
    {
    case 0:
        retValue = (bool)BR_LLWU_F1_WUF0(baseAddr);
        break;
    case 1:
        retValue = (bool)BR_LLWU_F1_WUF1(baseAddr);
        break;
    case 2:
        retValue = (bool)BR_LLWU_F1_WUF2(baseAddr);
        break;
    case 3:
        retValue = (bool)BR_LLWU_F1_WUF3(baseAddr);
        break;
    case 4:
        retValue = (bool)BR_LLWU_F1_WUF4(baseAddr);
        break;
    case 5:
        retValue = (bool)BR_LLWU_F1_WUF5(baseAddr);
        break;
    case 6:
        retValue = (bool)BR_LLWU_F1_WUF6(baseAddr);
        break;
    case 7:
        retValue = (bool)BR_LLWU_F1_WUF7(baseAddr);
        break;
    case 8:
        retValue = (bool)BR_LLWU_F2_WUF8(baseAddr);
        break;
    case 9:
        retValue = (bool)BR_LLWU_F2_WUF9(baseAddr);
        break;
    case 10:
        retValue = (bool)BR_LLWU_F2_WUF10(baseAddr);
        break;
    case 11:
        retValue = (bool)BR_LLWU_F2_WUF11(baseAddr);
        break;
    case 12:
        retValue = (bool)BR_LLWU_F2_WUF12(baseAddr);
        break;
    case 13:
        retValue = (bool)BR_LLWU_F2_WUF13(baseAddr);
        break;
    case 14:
        retValue = (bool)BR_LLWU_F2_WUF14(baseAddr);
        break;
    case 15:
        retValue = (bool)BR_LLWU_F2_WUF15(baseAddr);
        break;
    default:
        retValue = false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_ClearExternalPinWakeupFlag
 * Description   : Clear external wakeup source flag
 * This function will clear the external wakeup source flag for specific pin.
 * 
 *END**************************************************************************/
void LLWU_HAL_ClearExternalPinWakeupFlag(uint32_t baseAddr, uint32_t pinNumber)
{
    /* check pin number */
    assert(pinNumber < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);

    switch (pinNumber)
    {
    case 0:
        BW_LLWU_F1_WUF0(baseAddr, 1);
        break;
    case 1:
        BW_LLWU_F1_WUF1(baseAddr, 1);
        break;
    case 2:
        BW_LLWU_F1_WUF2(baseAddr, 1);
        break;
    case 3:
        BW_LLWU_F1_WUF3(baseAddr, 1);
        break;
    case 4:
        BW_LLWU_F1_WUF4(baseAddr, 1);
        break;
    case 5:
        BW_LLWU_F1_WUF5(baseAddr, 1);
        break;
    case 6:
        BW_LLWU_F1_WUF6(baseAddr, 1);
        break;
    case 7:
        BW_LLWU_F1_WUF7(baseAddr, 1);
        break;
    case 8:
        BW_LLWU_F2_WUF8(baseAddr, 1);
        break;
    case 9:
        BW_LLWU_F2_WUF9(baseAddr, 1);
        break;
    case 10:
        BW_LLWU_F2_WUF10(baseAddr, 1);
        break;
    case 11:
        BW_LLWU_F2_WUF11(baseAddr, 1);
        break;
    case 12:
        BW_LLWU_F2_WUF12(baseAddr, 1);
        break;
    case 13:
        BW_LLWU_F2_WUF13(baseAddr, 1);
        break;
    case 14:
        BW_LLWU_F2_WUF14(baseAddr, 1);
        break;
    case 15:
        BW_LLWU_F2_WUF15(baseAddr, 1);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetInternalModuleWakeupFlag
 * Description   : Get internal module wakeup source flag
 * This function will get the internal module wakeup source flag for specific 
 * module
 * 
 *END**************************************************************************/
bool LLWU_HAL_GetInternalModuleWakeupFlag(uint32_t baseAddr, uint32_t moduleNumber)
{
    bool retValue = false;

    /* check module number */
    assert(moduleNumber < FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE);

    switch (moduleNumber)
    {
    case 0:
        retValue = (bool)BR_LLWU_F3_MWUF0(baseAddr);
        break;
    case 1:
        retValue = (bool)BR_LLWU_F3_MWUF1(baseAddr);
        break;
    case 2:
        retValue = (bool)BR_LLWU_F3_MWUF2(baseAddr);
        break;
    case 3:
        retValue = (bool)BR_LLWU_F3_MWUF3(baseAddr);
        break;
    case 4:
        retValue = (bool)BR_LLWU_F3_MWUF4(baseAddr);
        break;
    case 5:
        retValue = (bool)BR_LLWU_F3_MWUF5(baseAddr);
        break;
    case 6:
        retValue = (bool)BR_LLWU_F3_MWUF6(baseAddr);
        break;
    case 7:
        retValue = (bool)BR_LLWU_F3_MWUF7(baseAddr);
        break;
    default:
        retValue = false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetPinFilterMode
 * Description   : Set pin filter configuration
 * This function will set the pin filter configuration.
 * 
 *END**************************************************************************/
void LLWU_HAL_SetPinFilterMode(uint32_t baseAddr,
                               uint32_t filterNumber, 
                               llwu_external_pin_filter_mode_t pinFilterMode)
{
    /* check filter and pin number */
    assert(filterNumber < FSL_FEATURE_LLWU_HAS_PIN_FILTER);
    assert(pinFilterMode.pinNumber < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);

    /* branch to filter number */
    switch(filterNumber)
    {
    case 0:
        BW_LLWU_FILT1_FILTSEL(baseAddr, pinFilterMode.pinNumber);
        BW_LLWU_FILT1_FILTE(baseAddr, pinFilterMode.filterMode);
        break;
    case 1:
        BW_LLWU_FILT2_FILTSEL(baseAddr, pinFilterMode.pinNumber);
        BW_LLWU_FILT2_FILTE(baseAddr, pinFilterMode.filterMode);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetPinFilterMode
 * Description   : Get pin filter configuration.
 * This function will get the pin filter configuration.
 * 
 *END**************************************************************************/
void LLWU_HAL_GetPinFilterMode(uint32_t baseAddr,
                               uint32_t filterNumber, 
                               llwu_external_pin_filter_mode_t *pinFilterMode)
{
    /* check filter and pin number */
    assert(filterNumber < FSL_FEATURE_LLWU_HAS_PIN_FILTER);
    assert(pinFilterMode->pinNumber < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);

    /* branch to filter number */
    switch(filterNumber)
    {
    case 0:
        pinFilterMode->pinNumber = BR_LLWU_FILT1_FILTSEL(baseAddr);
        pinFilterMode->filterMode = (llwu_filter_modes_t)BR_LLWU_FILT1_FILTE(baseAddr);
        break;
    case 1:
        pinFilterMode->pinNumber = BR_LLWU_FILT2_FILTSEL(baseAddr);
        pinFilterMode->filterMode = (llwu_filter_modes_t)BR_LLWU_FILT2_FILTE(baseAddr);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetFilterDetectFlag
 * Description   : Get filter detect flag
 * This function will get the filter detect flag.
 * 
 *END**************************************************************************/
bool LLWU_HAL_GetFilterDetectFlag(uint32_t baseAddr, uint32_t filterNumber)
{
    bool retValue = false;

    /* check filter and pin number */
    assert(filterNumber < FSL_FEATURE_LLWU_HAS_PIN_FILTER);

    /* branch to filter number */
    switch(filterNumber)
    {
    case 0:
        retValue = (bool)BR_LLWU_FILT1_FILTF(baseAddr);
        break;
    case 1:
        retValue = (bool)BR_LLWU_FILT2_FILTF(baseAddr);
        break;
    default:
        retValue = false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_ClearFilterDetectFlag
 * Description   : Clear filter detect flag
 * This function will clear the filter detect flag.
 * 
 *END**************************************************************************/
void LLWU_HAL_ClearFilterDetectFlag(uint32_t baseAddr, uint32_t filterNumber)
{
    /* check filter and pin number */
    assert(filterNumber < FSL_FEATURE_LLWU_HAS_PIN_FILTER);

    /* branch to filter number */
    switch(filterNumber)
    {
    case 0:
        BW_LLWU_FILT1_FILTF(baseAddr, 1);
        break;
    case 1:
        BW_LLWU_FILT2_FILTF(baseAddr, 1);
        break;
    default:
        break;
    }
}

#if FSL_FEATURE_LLWU_HAS_RESET_ENABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_SetResetEnableMode
 * Description   : Set reset enable mode
 * This function will set the reset enable mode.
 * 
 *END**************************************************************************/
void LLWU_HAL_SetResetEnableMode(uint32_t baseAddr, llwu_reset_enable_mode_t resetEnableMode)
{
    BW_LLWU_RST_RSTFILT(baseAddr, resetEnableMode.digitalFilterMode);
    BW_LLWU_RST_LLRSTE(baseAddr, resetEnableMode.lowLeakageMode);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LLWU_HAL_GetResetEnableMode
 * Description   : Get reset enable mode
 * This function will get the reset enable mode.
 * 
 *END**************************************************************************/
void LLWU_HAL_GetResetEnableMode(uint32_t baseAddr, llwu_reset_enable_mode_t *resetEnableMode)
{
    resetEnableMode->digitalFilterMode = (bool)BR_LLWU_RST_RSTFILT(baseAddr);
    resetEnableMode->lowLeakageMode = (bool)BR_LLWU_RST_LLRSTE(baseAddr);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

