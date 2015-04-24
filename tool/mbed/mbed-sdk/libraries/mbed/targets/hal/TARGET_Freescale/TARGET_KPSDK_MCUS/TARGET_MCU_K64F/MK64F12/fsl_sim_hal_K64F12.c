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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "fsl_sim_hal_K64F12.h"
#include "fsl_sim_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief CLOCK name config table for K64*/
const clock_name_config_t kClockNameConfigTable [] =  {
    {false, kSystemClock,     kClockDividerOutdiv1},
    {false, kSystemClock,     kClockDividerOutdiv1},
    {false, kSystemClock,     kClockDividerOutdiv1},
    {false, kSystemClock,     kClockDividerOutdiv2},
    {false, kSystemClock,     kClockDividerOutdiv3},
    {false, kSystemClock,     kClockDividerOutdiv4}
};

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableDmaClock
 * Description   : Enable the clock for DMA module
 * This function enables the clock for DMA moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableDmaClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC7_DMA(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableDmaClock
 * Description   : Disable the clock for DMA module
 * This function disables the clock for DMA moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableDmaClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC7_DMA(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetDmaGateCmd
 * Description   : Get the the clock gate state for DMA module
 * This function will get the clock gate state for DMA moudle
 *
 *END**************************************************************************/
bool SIM_HAL_GetDmaGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC7_DMA(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableDmamuxClock
 * Description   : Enable the clock for DMAMUX module
 * This function enables the clock for DMAMUX moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableDmamuxClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_DMAMUX(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableDmamuxClock
 * Description   : Disable the clock for DMAMUX module
 * This function disables the clock for DMAMUX moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableDmamuxClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_DMAMUX(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetDmamuxGateCmd
 * Description   : Get the the clock gate state for DMAMUX module
 * This function will get the clock gate state for DMAMUX moudle
 *
 *END**************************************************************************/
bool SIM_HAL_GetDmamuxGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_DMAMUX(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnablePortClock
 * Description   : Enable the clock for PORT module
 * This function enables the clock for PORT moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnablePortClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC5_PORTA(baseAddr, 1);
        break;
    case 1:
        BW_SIM_SCGC5_PORTB(baseAddr, 1);
        break;
    case 2:
        BW_SIM_SCGC5_PORTC(baseAddr, 1);
        break;
    case 3:
        BW_SIM_SCGC5_PORTD(baseAddr, 1);
        break;
    case 4:
        BW_SIM_SCGC5_PORTE(baseAddr, 1);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisablePortClock
 * Description   : Disable the clock for PORT module
 * This function disables the clock for PORT moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisablePortClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC5_PORTA(baseAddr, 0);
        break;
    case 1:
        BW_SIM_SCGC5_PORTB(baseAddr, 0);
        break;
    case 2:
        BW_SIM_SCGC5_PORTC(baseAddr, 0);
        break;
    case 3:
        BW_SIM_SCGC5_PORTD(baseAddr, 0);
        break;
    case 4:
        BW_SIM_SCGC5_PORTE(baseAddr, 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetPortGateCmd
 * Description   : Get the the clock gate state for PORT module
 * This function will get the clock gate state for PORT moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetPortGateCmd(uint32_t baseAddr, uint32_t instance)
{
    bool retValue = false;

    switch (instance)
    {
    case 0:
        retValue =  BR_SIM_SCGC5_PORTA(baseAddr);
        break;
    case 1:
        retValue =  BR_SIM_SCGC5_PORTB(baseAddr);
        break;
    case 2:
        retValue =  BR_SIM_SCGC5_PORTC(baseAddr);
        break;
    case 3:
        retValue =  BR_SIM_SCGC5_PORTD(baseAddr);
        break;
    case 4:
        retValue =  BR_SIM_SCGC5_PORTE(baseAddr);
        break;
    default:
        retValue =  false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableMpuClock
 * Description   : Enable the clock for MPU module
 * This function enables the clock for MPU moudle.
 *
 *END**************************************************************************/
void SIM_HAL_EnableMpuClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC7_MPU(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableMpuClock
 * Description   : Disable the clock for MPU module.
 * This function disables the clock for MPU moudle.
 *
 *END**************************************************************************/
void SIM_HAL_DisableMpuClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC7_MPU(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetMpuGateCmd
 * Description   : Get the the clock gate state for MPU module
 * This function will get the clock gate state for MPU moudl.
 *
 *END**************************************************************************/
bool SIM_HAL_GetMpuGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC7_MPU(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableEwmClock
 * Description   : Enable the clock for EWM module
 * This function enables the clock for EWM moudle.
 *
 *END**************************************************************************/
void SIM_HAL_EnableEwmClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_EWM(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableEwmClock
 * Description   : Disable the clock for EWM modul
 * This function disables the clock for EWM moudle.
 *
 *END**************************************************************************/
void SIM_HAL_DisableEwmClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_EWM(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetEwmGateCmd
 * Description   : Get the the clock gate state for EWM module
 * This function will get the clock gate state for EWM moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetEwmGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC4_EWM(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableFlexbusClock
 * Description   : Enable the clock for FLEXBUS module
 * This function enables the clock for FLEXBUS moudle.
 *
 *END**************************************************************************/
void SIM_HAL_EnableFlexbusClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC7_FLEXBUS(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableFlexbusClock
 * Description   : Disable the clock for FLEXBUS module
 * This function disables the clock for FLEXBUS moudle.
 *
 *END**************************************************************************/
void SIM_HAL_DisableFlexbusClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC7_FLEXBUS(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFlexbusGateCmd
 * Description   : Get the the clock gate state for FLEXBUS module
 * This function will get the clock gate state for FLEXBUS moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetFlexbusGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC7_FLEXBUS(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableFtfClock
 * Description   : Enable the clock for FTF module
 * This function enables the clock for FTF moudle.
 *
 *END**************************************************************************/
void SIM_HAL_EnableFtfClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_FTF(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableFtfClock
 * Description   : Disable the clock for FTF module
 * This function disables the clock for FTF moudle.
 *
 *END**************************************************************************/
void SIM_HAL_DisableFtfClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_FTF(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtfGateCmd
 * Description   : Get the the clock gate state for FTF module
 * This function will get the clock gate state for FTF moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetFtfGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_FTF(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableCrcClock
 * Description   : Enable the clock for CRC module
 * This function enables the clock for CRC moudle.
 *
 *END**************************************************************************/
void SIM_HAL_EnableCrcClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_CRC(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableCrcClock
 * Description   : Disable the clock for CRC module
 * This function disables the clock for CRC moudle.
 *
 *END**************************************************************************/
void SIM_HAL_DisableCrcClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_CRC(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetCrcGateCmd
 * Description   : Get the the clock gate state for CRC module
 * This function will get the clock gate state for CRC moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetCrcGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_CRC(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableRngaClock
 * Description   : Enable the clock for RNGA module
 * This function enables the clock for RNGA moudle.
 *
 *END**************************************************************************/
void SIM_HAL_EnableRngaClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_RNGA(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableRngaClock
 * Description   : Disable the clock for RNGA module
 * This function disables the clock for RNGA moudle.
 *
 *END**************************************************************************/
void SIM_HAL_DisableRngaClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_RNGA(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetRngaGateCmd
 * Description   : Get the the clock gate state for RNGA module
 * This function will get the clock gate state for RNGA moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetRngaGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_RNGA(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableAdcClock
 * Description   : Enable the clock for ADC module
 * This function enables the clock for ADC moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableAdcClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC6_ADC0(baseAddr, 1);
        break;
    case 1:
        BW_SIM_SCGC3_ADC1(baseAddr, 1);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableAdcClock
 * Description   : Disable the clock for ADC module
 * This function disables the clock for ADC moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableAdcClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC6_ADC0(baseAddr, 0);
        break;
    case 1:
        BW_SIM_SCGC3_ADC1(baseAddr, 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcGateCmd
 * Description   : Get the the clock gate state for ADC module
 * This function will get the clock gate state for ADC moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetAdcGateCmd(uint32_t baseAddr, uint32_t instance)
{
    bool retValue = false;

    switch (instance)
    {
    case 0:
        retValue =  BR_SIM_SCGC6_ADC0(baseAddr);
        break;
    case 1:
        retValue =  BR_SIM_SCGC3_ADC1(baseAddr);
        break;
    default:
        retValue =  false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableCmpClock
 * Description   : Enable the clock for CMP module
 * This function enables the clock for CMP moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableCmpClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_CMP(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableCmpClock
 * Description   : Disable the clock for CMP module
 * This function disables the clock for CMP moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableCmpClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_CMP(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetCmpGateCmd
 * Description   : Get the the clock gate state for CMP module
 * This function will get the clock gate state for CMP moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetCmpGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC4_CMP(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableDacClock
 * Description   : Enable the clock for DAC module
 * This function enables the clock for DAC moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableDacClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC2_DAC0(baseAddr, 1);
        break;
    case 1:
        BW_SIM_SCGC2_DAC1(baseAddr, 1);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableDacClock
 * Description   : Disable the clock for DAC module
 * This function disables the clock for DAC moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableDacClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC2_DAC0(baseAddr, 0);
        break;
    case 1:
        BW_SIM_SCGC2_DAC1(baseAddr, 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetDacGateCmd
 * Description   : Get the the clock gate state for DAC module
 * This function will get the clock gate state for DAC moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetDacGateCmd(uint32_t baseAddr, uint32_t instance)
{
    bool retValue = false;

    switch (instance)
    {
    case 0:
        retValue =  BR_SIM_SCGC2_DAC0(baseAddr);
        break;
    case 1:
        retValue =  BR_SIM_SCGC2_DAC1(baseAddr);
        break;
    default:
        retValue =  false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableVrefClock
 * Description   : Enable the clock for VREF module
 * This function enables the clock for VREF moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableVrefClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_VREF(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableVrefClock
 * Description   : Disable the clock for VREF module
 * This function disables the clock for VREF moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableVrefClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_VREF(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetVrefGateCmd
 * Description   : Get the the clock gate state for VREF module
 * This function will get the clock gate state for VREF moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetVrefGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC4_VREF(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableSaiClock
 * Description   : Enable the clock for SAI module
 * This function enables the clock for SAI moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableSaiClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_I2S(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableSaiClock
 * Description   : Disable the clock for SAI module
 * This function disables the clock for SAI moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableSaiClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_I2S(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetSaiGateCmd
 * Description   : Get the the clock gate state for SAI module
 * This function will get the clock gate state for SAI moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetSaiGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_I2S(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnablePdbClock
 * Description   : Enable the clock for PDB module
 * This function enables the clock for PDB moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnablePdbClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_PDB(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisablePdbClock
 * Description   : Disable the clock for PDB module
 * This function disables the clock for PDB moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisablePdbClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_PDB(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetPdbGateCmd
 * Description   : Get the the clock gate state for PDB module
 * This function will get the clock gate state for PDB moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetPdbGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_PDB(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableFtmClock
 * Description   : Enable the clock for FTM module
 * This function enables the clock for FTM moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableFtmClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC6_FTM0(baseAddr, 1);
        break;
    case 1:
        BW_SIM_SCGC6_FTM1(baseAddr, 1);
        break;
    case 2:
        BW_SIM_SCGC6_FTM2(baseAddr, 1);
        break;
    case 3:
        BW_SIM_SCGC3_FTM3(baseAddr, 1);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableFtmClock
 * Description   : Disable the clock for FTM module
 * This function disables the clock for FTM moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableFtmClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC6_FTM0(baseAddr, 0);
        break;
    case 1:
        BW_SIM_SCGC6_FTM1(baseAddr, 0);
        break;
    case 2:
        BW_SIM_SCGC6_FTM2(baseAddr, 0);
        break;
    case 3:
        BW_SIM_SCGC3_FTM3(baseAddr, 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmGateCmd
 * Description   : Get the the clock gate state for FTM module
 * This function will get the clock gate state for FTM moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetFtmGateCmd(uint32_t baseAddr, uint32_t instance)
{
    bool retValue = false;

    switch (instance)
    {
    case 0:
        retValue =  BR_SIM_SCGC6_FTM0(baseAddr);
        break;
    case 1:
        retValue =  BR_SIM_SCGC6_FTM1(baseAddr);
        break;
    case 2:
        retValue =  BR_SIM_SCGC6_FTM2(baseAddr);
        break;
    case 3:
        retValue =  BR_SIM_SCGC3_FTM3(baseAddr);
        break;
    default:
        retValue =  false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnablePitClock
 * Description   : Enable the clock for PIT module
 * This function enables the clock for PIT moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnablePitClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_PIT(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisablePitClock
 * Description   : Disable the clock for PIT module
 * This function disables the clock for PIT moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisablePitClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_PIT(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetPitGateCmd
 * Description   : Get the the clock gate state for PIT module
 * This function will get the clock gate state for PIT moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetPitGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_PIT(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableLptimerClock
 * Description   : Enable the clock for LPTIMER module
 * This function enables the clock for LPTIMER moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableLptimerClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC5_LPTMR(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableLptimerClock
 * Description   : Disable the clock for LPTIMER module
 * This function disables the clock for LPTIMER moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableLptimerClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC5_LPTMR(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetLptimerGateCmd
 * Description   : Get the the clock gate state for LPTIMER module
 * This function will get the clock gate state for LPTIMER moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetLptimerGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC5_LPTMR(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableCmtClock
 * Description   : Enable the clock for CMT module
 * This function enables the clock for CMT moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableCmtClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_CMT(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableCmtClock
 * Description   : Disable the clock for CMT module
 * This function disables the clock for CMT moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableCmtClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_CMT(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetCmtGateCmd
 * Description   : Get the the clock gate state for CMT module
 * This function will get the clock gate state for CMT moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetCmtGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC4_CMT(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableRtcClock
 * Description   : Enable the clock for RTC module
 * This function enables the clock for RTC moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableRtcClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_RTC(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableRtcClock
 * Description   : Disable the clock for RTC module
 * This function disables the clock for RTC moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableRtcClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_RTC(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetRtcGateCmd
 * Description   : Get the the clock gate state for RTC module
 * This function will get the clock gate state for RTC moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetRtcGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_RTC(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableEnetClock
 * Description   : Enable the clock for ENET module
 * This function enables the clock for ENET moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableEnetClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC2_ENET(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableEnetClock
 * Description   : Disable the clock for ENET module
 * This function disables the clock for ENET moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableEnetClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC2_ENET(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetEnetGateCmd
 * Description   : Get the the clock gate state for ENET module
 * This function will get the clock gate state for ENET moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetEnetGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC2_ENET(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableUsbClock
 * Description   : Enable the clock for USBFS module
 * This function enables the clock for USBFS moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableUsbClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_USBOTG(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableUsbClock
 * Description   : Disable the clock for USBFS module
 * This function disables the clock for USBFS moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableUsbClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC4_USBOTG(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUsbGateCmd
 * Description   : Get the the clock gate state for USB module
 * This function will get the clock gate state for USB moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetUsbGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC4_USBOTG(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableUsbdcdClock
 * Description   : Enable the clock for USBDCD module
 * This function enables the clock for USBDCD moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableUsbdcdClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_USBDCD(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableUsbdcdClock
 * Description   : Disable the clock for USBDCD module
 * This function disables the clock for USBDCD moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableUsbdcdClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_USBDCD(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUsbdcdGateCmd
 * Description   : Get the the clock gate state for USBDCD module
 * This function will get the clock gate state for USBDCD moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetUsbdcdGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_USBDCD(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableFlexcanClock
 * Description   : Enable the clock for FLEXCAN module
 * This function enables the clock for FLEXCAN moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableFlexcanClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_FLEXCAN0(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableFlexcanClock
 * Description   : Disable the clock for FLEXCAN module
 * This function disables the clock for FLEXCAN moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableFlexcanClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC6_FLEXCAN0(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFlexcanGateCmd
 * Description   : Get the the clock gate state for FLEXCAN module
 * This function will get the clock gate state for FLEXCAN moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetFlexcanGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC6_FLEXCAN0(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableSpiClock
 * Description   : Enable the clock for SPI module
 * This function enables the clock for SPI moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableSpiClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC6_SPI0(baseAddr, 1);
        break;
    case 1:
        BW_SIM_SCGC6_SPI1(baseAddr, 1);
        break;
    case 2:
        BW_SIM_SCGC3_SPI2(baseAddr, 1);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableSpiClock
 * Description   : Disable the clock for SPI module
 * This function disables the clock for SPI moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableSpiClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC6_SPI0(baseAddr, 0);
        break;
    case 1:
        BW_SIM_SCGC6_SPI1(baseAddr, 0);
        break;
    case 2:
        BW_SIM_SCGC3_SPI2(baseAddr, 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetSpiGateCmd
 * Description   : Get the the clock gate state for SPI module
 * This function will get the clock gate state for SPI moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetSpiGateCmd(uint32_t baseAddr, uint32_t instance)
{
    bool retValue = false;

    switch (instance)
    {
    case 0:
        retValue =  BR_SIM_SCGC6_SPI0(baseAddr);
        break;
    case 1:
        retValue =  BR_SIM_SCGC6_SPI1(baseAddr);
        break;
    case 2:
        retValue =  BR_SIM_SCGC3_SPI2(baseAddr);
        break;
    default:
        retValue =  false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableI2cClock
 * Description   : Enable the clock for I2C module
 * This function enables the clock for I2C moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableI2cClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC4_I2C0(baseAddr, 1);
        break;
    case 1:
        BW_SIM_SCGC4_I2C1(baseAddr, 1);
        break;
    case 2:
        BW_SIM_SCGC1_I2C2(baseAddr, 1);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableI2cClock
 * Description   : Disable the clock for I2C module
 * This function disables the clock for I2C moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableI2cClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC4_I2C0(baseAddr, 0);
        break;
    case 1:
        BW_SIM_SCGC4_I2C1(baseAddr, 0);
        break;
    case 2:
        BW_SIM_SCGC1_I2C2(baseAddr, 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetI2cGateCmd
 * Description   : Get the the clock gate state for I2C module
 * This function will get the clock gate state for I2C moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetI2cGateCmd(uint32_t baseAddr, uint32_t instance)
{
    bool retValue = false;

    switch (instance)
    {
    case 0:
        retValue =  BR_SIM_SCGC4_I2C0(baseAddr);
        break;
    case 1:
        retValue =  BR_SIM_SCGC4_I2C1(baseAddr);
        break;
    case 2:
        retValue =  BR_SIM_SCGC1_I2C2(baseAddr);
        break;
    default:
        retValue =  false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableUartClock
 * Description   : Enable the clock for UART module
 * This function enables the clock for UART moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableUartClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC4_UART0(baseAddr, 1);
        break;
    case 1:
        BW_SIM_SCGC4_UART1(baseAddr, 1);
        break;
    case 2:
        BW_SIM_SCGC4_UART2(baseAddr, 1);
        break;
    case 3:
        BW_SIM_SCGC4_UART3(baseAddr, 1);
        break;
    case 4:
        BW_SIM_SCGC1_UART4(baseAddr, 1);
        break;
    case 5:
        BW_SIM_SCGC1_UART5(baseAddr, 1);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableUartClock
 * Description   : Disable the clock for UART module
 * This function disables the clock for UART moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableUartClock(uint32_t baseAddr, uint32_t instance)
{
    switch (instance)
    {
    case 0:
        BW_SIM_SCGC4_UART0(baseAddr, 0);
        break;
    case 1:
        BW_SIM_SCGC4_UART1(baseAddr, 0);
        break;
    case 2:
        BW_SIM_SCGC4_UART2(baseAddr, 0);
        break;
    case 3:
        BW_SIM_SCGC4_UART3(baseAddr, 0);
        break;
    case 4:
        BW_SIM_SCGC1_UART4(baseAddr, 0);
        break;
    case 5:
        BW_SIM_SCGC1_UART5(baseAddr, 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUartGateCmd
 * Description   : Get the the clock gate state for UART module
 * This function will get the clock gate state for UART moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetUartGateCmd(uint32_t baseAddr, uint32_t instance)
{
    bool retValue = false;

    switch (instance)
    {
    case 0:
        retValue =  BR_SIM_SCGC4_UART0(baseAddr);
        break;
    case 1:
        retValue =  BR_SIM_SCGC4_UART1(baseAddr);
        break;
    case 2:
        retValue =  BR_SIM_SCGC4_UART2(baseAddr);
        break;
    case 3:
        retValue =  BR_SIM_SCGC4_UART3(baseAddr);
        break;
    case 4:
        retValue =  BR_SIM_SCGC1_UART4(baseAddr);
        break;
    case 5:
        retValue =  BR_SIM_SCGC1_UART5(baseAddr);
        break;
    default:
        retValue =  false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_EnableSdhcClock
 * Description   : Enable the clock for SDHC module
 * This function enables the clock for SDHC moudle
 *
 *END**************************************************************************/
void SIM_HAL_EnableSdhcClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC3_SDHC(baseAddr, 1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_DisableSdhcClock
 * Description   : Disable the clock for SDHC module
 * This function disables the clock for SDHC moudle
 *
 *END**************************************************************************/
void SIM_HAL_DisableSdhcClock(uint32_t baseAddr, uint32_t instance)
{
    BW_SIM_SCGC3_SDHC(baseAddr, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetSdhcGateCmd
 * Description   : Get the the clock gate state for SDHC module
 * This function will get the clock gate state for SDHC moudle.
 *
 *END**************************************************************************/
bool SIM_HAL_GetSdhcGateCmd(uint32_t baseAddr, uint32_t instance)
{
    return BR_SIM_SCGC3_SDHC(baseAddr);
}
/*******************************************************************************
 * EOF
 ******************************************************************************/

