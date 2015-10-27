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

#include "fsl_osc_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : OSC_HAL_SetExternalRefClkCmd
 * Description   : Enable/disable the external reference clock 
 * This function will enable/disable the external reference clock output 
 * for oscillator - that is the OSCERCLK. This clock will be used by many 
 * peripherals. It should be enabled at early system init stage to ensure the 
 * peripherals could select it and use it.
 * 
 *END**************************************************************************/
void OSC_HAL_SetExternalRefClkCmd(uint32_t baseAddr, bool enable)
{
    BW_OSC_CR_ERCLKEN(baseAddr, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSC_HAL_GetExternalRefClkCmd
 * Description   : Get the external reference clock enable setting for osc
 * This function will get the external reference clock output enable setting 
 * for oscillator - that is the OSCERCLK. This clock will be used by many 
 * peripherals. It should be enabled at early system init stage to ensure the 
 * peripherals could select it and use it.
 * 
 *END**************************************************************************/
bool OSC_HAL_GetExternalRefClkCmd(uint32_t baseAddr)
{
    return (bool)BR_OSC_CR_ERCLKEN(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSC_HAL_SetExternalRefClkInStopModeCmd
 * Description   : Enable/disable the external ref clock in stop mode 
 * This function will enable/disable the external reference clock (OSCERCLK) 
 * when MCU enters Stop mode. 
 * 
 *END**************************************************************************/
void OSC_HAL_SetExternalRefClkInStopModeCmd(uint32_t baseAddr, bool enable)
{
    BW_OSC_CR_EREFSTEN(baseAddr, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSC_HAL_GetExternalRefClkInStopModeCmd
 * Description   : Get the external ref clock enable setting for osc in stop mode 
 * This function will get the external reference clock (OSCERCLK) setting when 
 * MCU enters Stop mode. 
 * 
 *END**************************************************************************/
bool OSC_HAL_GetExternalRefClkInStopModeCmd(uint32_t baseAddr)
{
    return (bool)BR_OSC_CR_EREFSTEN(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSC_HAL_SetCapacitorCmd
 * Description   : Enable/disable the capacitor configuration for oscillator
 * This function will enable/disable the specified capacitors configuration for  
 * oscillator. This should be done in early system level init function call
 * based on system configuration.
 * 
 *END**************************************************************************/
void OSC_HAL_SetCapacitorCmd(uint32_t baseAddr, 
                             osc_capacitor_config_t capacitorConfig,
                             bool enable)
{
    if (capacitorConfig == kOscCapacitor2p)
    {
        BW_OSC_CR_SC2P(baseAddr, enable);
    }
    else if (capacitorConfig == kOscCapacitor4p)
    {
        BW_OSC_CR_SC4P(baseAddr, enable);
    }
    else if (capacitorConfig == kOscCapacitor8p)
    {
        BW_OSC_CR_SC8P(baseAddr, enable);
    }
    else if (capacitorConfig == kOscCapacitor16p)
    {
        BW_OSC_CR_SC16P(baseAddr, enable);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSC_HAL_GetCapacitorCmd
 * Description   : Get the capacitor configuration for specific oscillator
 * This function will get the specified capacitors configuration for the 
 * oscillator.
 * 
 *END**************************************************************************/
bool OSC_HAL_GetCapacitorCmd(uint32_t baseAddr, 
                             osc_capacitor_config_t capacitorConfig)
{
    if (capacitorConfig == kOscCapacitor2p)
    {
        return (bool)BR_OSC_CR_SC2P(baseAddr);
    }
    else if (capacitorConfig == kOscCapacitor4p)
    {
        return (bool)BR_OSC_CR_SC4P(baseAddr);
    }
    else if (capacitorConfig == kOscCapacitor8p)
    {
        return (bool)BR_OSC_CR_SC8P(baseAddr);
    }
    else if (capacitorConfig == kOscCapacitor16p)
    {
        return (bool)BR_OSC_CR_SC16P(baseAddr);
    }

    return 0;
}

#if FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER
/*FUNCTION**********************************************************************
 *
 * Function Name : OSC_HAL_SetExternalRefClkDivCmd
 * Description   : Set the external reference clock divider setting for osc
 * This function will get the external reference clock divider setting 
 * for oscillator - that is the OSCERCLK. This clock will be used by many 
 * peripherals. 
 * 
 *END**************************************************************************/
void OSC_HAL_SetExternalRefClkDivCmd(uint32_t baseAddr, uint32_t divider)
{
    BW_OSC_DIV_ERPS(baseAddr, divider);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSC_HAL_GetExternalRefClkDivCmd
 * Description   : Get the external reference clock divider setting for osc
 * This function will get the external reference clock divider setting 
 * for oscillator - that is the OSCERCLK. This clock will be used by many 
 * peripherals. 
 * 
 *END**************************************************************************/
uint32_t OSC_HAL_GetExternalRefClkDivCmd(uint32_t baseAddr)
{
    return BR_OSC_DIV_ERPS(baseAddr);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

