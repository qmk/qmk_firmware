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

#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Table of base addresses for instances. */
const uint32_t g_simBaseAddr[] = SIM_BASE_ADDRS;
const uint32_t g_mcgBaseAddr[] = MCG_BASE_ADDRS;
                                                                 

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetSysClkFreq
 * Description   : Internal function to get the system clock frequency
 * This function will check the clock name configuration table for specific
 * chip family and find out the supported clock name for that chip family
 * then it will call the mcg hal function to get the basic system clock,
 * calculate the clock frequency for specified clock name.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_GetSysClkFreq(clock_names_t clockName,
                                                        uint32_t *frequency)
{
    /* system clock out divider*/
    uint32_t divider;

    const clock_name_config_t *table = &kClockNameConfigTable[clockName];

    /* check if we need to use a reference clock*/
    if (table->useOtherRefClock)
    {
        /* get other specified ref clock*/
        if ( kClockManagerSuccess != CLOCK_SYS_GetFreq(table->otherRefClockName,
                                                                    frequency) )
        {
            return kClockManagerNoSuchClockName;
        }
    }
    else
    {
        /* get default ref clock */
        *frequency = CLOCK_HAL_GetOutClk(g_mcgBaseAddr[0]);
    }

    /* get system clock divider*/
    if ( CLOCK_HAL_GetDivider(g_simBaseAddr[0], table->dividerName, &divider) == kSimHalSuccess)
    {
        /* get the frequency for the specified clock*/
        *frequency = (*frequency) / (divider + 1);
        return kClockManagerSuccess;
    }
    else
    {
        return kClockManagerNoSuchDivider;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetFreq
 * Description   : Internal function to get the frequency by clock name
 * This function will get/calculate the clock frequency based on clock name
 * and current configuration of clock generator.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_GetFreq(clock_names_t clockName,
                                                                   uint32_t *frequency)
{
    clock_manager_error_code_t returnCode = kClockManagerSuccess;

    /* branch according to clock name */
    switch(clockName)
    {
    /* osc clock*/
    case kOsc32kClock:
        *frequency = CPU_XTAL32k_CLK_HZ;    
        break;
    case kOsc0ErClock:
#if FSL_FEATURE_MCG_HAS_OSC1
            /* System oscillator 0 drives MCG clock */
        *frequency = CPU_XTAL0_CLK_HZ;
#else
            /* System oscillator 0 drives MCG clock */
        *frequency = CPU_XTAL_CLK_HZ;
#endif      
        break;

#if FSL_FEATURE_MCG_HAS_OSC1
    case kOsc1ErClock:
        *frequency = CPU_XTAL1_CLK_HZ;           
        break;
#endif          

#if FSL_FEATURE_MCG_HAS_IRC_48M  
    /* irc clock*/
    case kIrc48mClock:
        *frequency = CPU_INT_IRC_CLK_HZ;  
        break;
#endif
        
    /* rtc clock*/
    case kRtc32kClock:
        *frequency = CPU_XTAL32k_CLK_HZ;    
        break;

    case kRtc1hzClock:
        *frequency = CPU_XTAL1hz_CLK_HZ;    // defined in fsl_clock_manager.h for now
        break;

    /* lpo clcok*/
    case kLpoClock:
        *frequency = CPU_LPO_CLK_HZ;       // defined in fsl_clock_manager.h for now
        break;

    /* mcg clocks, calling mcg clock functions */
    case kMcgFfClock:
        *frequency = CLOCK_HAL_GetFllRefClk(g_mcgBaseAddr[0]);
        break;
    case kMcgFllClock:
        *frequency = CLOCK_HAL_GetFllClk(g_mcgBaseAddr[0]);
        break;
#if FSL_FEATURE_MCG_HAS_PLL
    case kMcgPll0Clock:
        *frequency = CLOCK_HAL_GetPll0Clk(g_mcgBaseAddr[0]);
        break;
#endif
    case kMcgOutClock:
        *frequency = CLOCK_HAL_GetOutClk(g_mcgBaseAddr[0]);
        break;
    case kMcgIrClock:
        *frequency = CLOCK_HAL_GetInternalRefClk(g_mcgBaseAddr[0]);
        break;

    case kSDHC0_CLKIN:
        *frequency = SDHC0_CLKIN;            // defined in fsl_clock_manager.h for now
        break;
    case kENET_1588_CLKIN:
        *frequency = ENET_1588_CLKIN;        // defined in fsl_clock_manager.h for now
        break;
    case kEXTAL_Clock:
        *frequency = EXTAL_Clock;            // defined in fsl_clock_manager.h for now
        break;
    case kEXTAL1_Clock:
        *frequency = EXTAL1_Clock;           // defined in fsl_clock_manager.h for now
        break;
    case kUSB_CLKIN:
        *frequency = USB_CLKIN;              // defined in fsl_clock_manager.h for now
        break;

    /* system clocks */
    case kCoreClock:
    case kSystemClock:
    case kPlatformClock:
    case kBusClock:
    case kFlexBusClock:
    case kFlashClock:
        returnCode = CLOCK_SYS_GetSysClkFreq(clockName, frequency);
        break;
        /* reserved value*/
    case kReserved:
    default:
        *frequency = 55555;                     /* for testing use purpose*/
        returnCode = kClockManagerNoSuchClockName;
        break;
    }

    return returnCode;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetSource
 * Description   : Set clock source setting 
 * This function will set the settings for specified clock source. Each clock 
 * source has its clock selection settings. Refer to reference manual for 
 * details of settings for each clock source. Refer to clock_source_names_t 
 * for clock sources.
 * 
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_SetSource(clock_source_names_t clockSource,
                                               uint8_t setting)
{
    clock_manager_error_code_t returnCode = kClockManagerSuccess;

    if (CLOCK_HAL_SetSource(g_simBaseAddr[0], clockSource, setting) != kSimHalSuccess)
    {
        returnCode =  kClockManagerNoSuchClockSource;
    }

    return returnCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetSource
 * Description   : Get clock source setting
 * This function will get the settings for specified clock source. Each clock 
 * source has its clock selection settings. Refer to reference manual for 
 * details of settings for each clock source. Refer to clock_source_names_t
 * for clock sources.
 * 
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_GetSource(clock_source_names_t clockSource,
                                               uint8_t *setting)
{
    clock_manager_error_code_t returnCode = kClockManagerSuccess;

    if (CLOCK_HAL_GetSource(g_simBaseAddr[0], clockSource, setting) != kSimHalSuccess)
    {
        returnCode =  kClockManagerNoSuchClockSource;
    }

    return returnCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetDivider
 * Description   : Set clock divider setting
 * This function will set the setting for specified clock divider. Refer to 
 * reference manual for supported clock divider and value range. Refer to 
 * clock_divider_names_t for dividers.
 * 
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_SetDivider(clock_divider_names_t clockDivider, 
                                                uint32_t setting)
{
    clock_manager_error_code_t returnCode = kClockManagerSuccess;

    if (CLOCK_HAL_SetDivider(g_simBaseAddr[0], clockDivider, setting) != kSimHalSuccess)
    {
        returnCode = kClockManagerNoSuchDivider;
    }

    return returnCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetDivider
 * Description   : Get clock divider setting
 * This function will get the setting for specified clock divider. Refer to 
 * reference manual for supported clock divider and value range. Refer to 
 * clock_divider_names_t for dividers.
 * 
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_GetDivider(clock_divider_names_t clockDivider,
                                                uint32_t *setting)
{
    clock_manager_error_code_t returnCode = kClockManagerSuccess;

    if (CLOCK_HAL_GetDivider(g_simBaseAddr[0], clockDivider, setting) != kSimHalSuccess)
    {
        returnCode = kClockManagerNoSuchDivider;
    }

    return returnCode;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

