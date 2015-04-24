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

#include "fsl_smc_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetMode
 * Description   : Config the power mode
 * This function will configure the power mode control for any run, stop and
 * stop submode if needed. It will also configure the power options for specific
 * power mode. Application should follow the proper procedure to configure and 
 * switch power mode between the different run and stop mode. Refer to reference
 * manual for the proper procedure and supported power mode that can be configured
 * and switch between each other. Refert to smc_power_mode_config_t for required
 * parameters to configure the power mode and the supported options. Other options
 * may need to configure through the hal driver individaully. Refer to hal driver
 * header for details. 
 * 
 *END**************************************************************************/
smc_hal_error_code_t SMC_HAL_SetMode(uint32_t baseAddr, const smc_power_mode_config_t *powerModeConfig)
{
    smc_hal_error_code_t retCode = kSmcHalSuccess;
    uint8_t currentStat;
    volatile unsigned int dummyread;
    smc_stop_mode_t stopMode;
    smc_run_mode_t runMode;
    power_mode_stat_t modeStat;
    power_modes_t powerModeName = powerModeConfig->powerModeName;

    /* verify the power mode name*/
    assert(powerModeName < kPowerModeMax);

#if  FSL_FEATURE_SMC_HAS_LPWUI     
    /* check lpwui option*/
    if (powerModeConfig->lpwuiOption)
    {
       /* check current stat*/
        currentStat = SMC_HAL_GetStat(baseAddr);

        /* if not in VLPR stat, could not set to RUN*/
        if (currentStat == kStatRun)
        {
            SMC_HAL_SetLpwuiMode(baseAddr, powerModeConfig->lpwuiOptionValue);
        }
    }
#endif
    
    /* branch based on power mode name*/
    switch (powerModeName)
    {
    case kPowerModeRun:
    case kPowerModeVlpr:
        if (powerModeName == kPowerModeRun)
        {
            /* mode setting for normal RUN*/
            runMode = kSmcRun;
            modeStat = kStatVlpr;
        }
        else
        {
            /* mode setting for VLPR*/
            runMode = kSmcVlpr;
            modeStat = kStatRun;
        }
        
        /* check current stat*/
        currentStat = SMC_HAL_GetStat(baseAddr);

        /* if not in VLPR stat, could not set to RUN*/
        if (currentStat != modeStat)
        {
            retCode = kSmcHalFailed;
        }
        else
        {
            /* set power mode to normal RUN or VLPR*/
            SMC_HAL_SetRunMode(baseAddr, runMode);
        }
        break;

#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE    
    case kPowerModeHsrun:
        /* mode setting for HSRUN (high speed run) */
        runMode = kSmcHsrun;
        modeStat = kStatRun;

        /* check current stat*/
        currentStat = SMC_HAL_GetStat(baseAddr);

        if (currentStat != modeStat)
        {
            /* if not in the mode, return error*/
            retCode = kSmcHalFailed;
        }
        else
        {
            /* set power mode to normal RUN or VLPR mode first*/
            SMC_HAL_SetRunMode(baseAddr, runMode);
        }

        break;
#endif

    case kPowerModeWait:
    case kPowerModeVlpw:
        if (powerModeName == kPowerModeWait)
        {
            /* mode setting for normal RUN*/
            runMode = kSmcRun;
            modeStat = kStatRun;
        }
        else
        {
            /* mode setting for VLPR*/
            runMode = kSmcVlpr;
            modeStat = kStatVlpr;
        }

        /* check current stat*/
        currentStat = SMC_HAL_GetStat(baseAddr);

        if (currentStat != modeStat)
        {
            /* if not in the mode, return error*/
            retCode = kSmcHalFailed;
        }
        else
        {
            /* set power mode to normal RUN or VLPR mode first*/
            SMC_HAL_SetRunMode(baseAddr, runMode);
        }

        if (retCode == kSmcHalSuccess)
        {
            /* Clear the SLEEPDEEP bit to disable deep sleep mode - enter wait mode*/
            SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            __WFI();
        }        
        break;

    case kPowerModeStop:
    case kPowerModeVlps:
    case kPowerModeLls:
        if (powerModeName == kPowerModeStop)
        {
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE    
            /* check current stat*/
            currentStat = SMC_HAL_GetStat(baseAddr);
            
            if ((currentStat == kStatHsrun) || (SMC_HAL_GetRunMode(baseAddr) == kSmcHsrun))
            {
                retCode = kSmcHalFailed;
                break;
            }
#endif
            stopMode = kSmcStop;
#if FSL_FEATURE_SMC_HAS_PSTOPO
            if (powerModeConfig->pstopOption)
            {
                SMC_HAL_SetPstopMode(baseAddr, powerModeConfig->pstopOptionValue);
            }
#endif
        }
        else if (powerModeName == kPowerModeVlps)
        {
            stopMode = kSmcVlps;
        }
        else
        {
            stopMode = kSmcLls;
        }

        /* set power mode to specified STOP mode*/
        SMC_HAL_SetStopMode(baseAddr, stopMode);

#if FSL_FEATURE_SMC_HAS_LLS_SUBMODE
        if (powerModeName == kPowerModeLls) 
        {
            /* further set the stop sub mode configuration*/
            SMC_HAL_SetStopSubMode(baseAddr, powerModeConfig->stopSubMode);
        }
#endif

        /* wait for write to complete to SMC before stopping core  */
        dummyread = SMC_HAL_GetStat(baseAddr);
        dummyread = dummyread + 1;

        /* Set the SLEEPDEEP bit to enable deep sleep mode (STOP)*/
        SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
        __WFI();

        break;

    case kPowerModeVlls:
        /* set power mode to specified STOP mode*/
        SMC_HAL_SetStopMode(baseAddr, kSmcVlls);

        /* further set the stop sub mode configuration*/
        SMC_HAL_SetStopSubMode(baseAddr, powerModeConfig->stopSubMode);

        /* check if Vlls0 option needs configuration*/
        if (powerModeConfig->stopSubMode == kSmcStopSub0)
        {
#if FSL_FEATURE_SMC_HAS_PORPO              
            if (powerModeConfig->porOption)
            {
                SMC_HAL_SetPorMode(baseAddr, powerModeConfig->porOptionValue);
            }
#endif                
        }

        /* wait for write to complete to SMC before stopping core  */
        dummyread = SMC_HAL_GetStat(baseAddr);
        dummyread = dummyread + 1;

        /* Set the SLEEPDEEP bit to enable deep sleep mode (STOP)*/
        SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
        __WFI();

        break;
    default:
        retCode = kSmcHalNoSuchModeName;
        break;
    }
    
    return retCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetProtection
 * Description   : Config all power mode protection settings
 * This function will configure the power mode protection settings for
 * supported power mode on the specified chip family. The availabe power modes
 * are defined in smc_power_mode_protection_config_t. Application should provide
 * the protect settings for all supported power mode on the chip and aslo this
 * should be done at early system level init stage. Refer to reference manual
 * for details. This register can only write once after power reset. So either
 * use this function or use the individual set function if you only have single
 * option to set.
 * 
 *END**************************************************************************/
void SMC_HAL_SetProtection(uint32_t baseAddr, smc_power_mode_protection_config_t *protectConfig)
{
    /* initialize the setting */
    uint8_t regValue = 0;

    /* check configurations for each mode and combine the seting together */
    if (protectConfig->vlpProt)
    {
        regValue |= BF_SMC_PMPROT_AVLP(1);
    }

    if (protectConfig->llsProt)
    {
        regValue |= BF_SMC_PMPROT_ALLS(1);
    }

    if (protectConfig->vllsProt)
    {
        regValue |= BF_SMC_PMPROT_AVLLS(1);
    }

#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE 
    if (protectConfig->hsrunProt)
    {
        regValue |= BF_SMC_PMPROT_AHSRUN(1);
    }
#endif

    /* write once into pmprot register*/
    HW_SMC_PMPROT_SET(baseAddr, regValue);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetProtectionMode
 * Description   : Config the individual power mode protection setting
 * This function will only configure the power mode protection settings for
 * a specified power mode on the specified chip family. The availabe power modes
 * are defined in smc_power_mode_protection_config_t. Refer to reference manual
 * for details. This register can only write once after power reset.
 * 
 *END**************************************************************************/
void SMC_HAL_SetProtectionMode(uint32_t baseAddr, power_modes_protect_t protect, bool allow)
{
    /* check the setting range */
    assert(protect < kAllowMax);

    /* branch according to mode and write the setting */
    switch (protect)
    {
    case kAllowVlp:
        if (allow) 
        {
            BW_SMC_PMPROT_AVLP(baseAddr, 1);
        }
        else
        {
            BW_SMC_PMPROT_AVLP(baseAddr, 0);
        }
        break;
    case kAllowLls:
        if (allow) 
        {
            BW_SMC_PMPROT_ALLS(baseAddr, 1);
        }
        else
        {
            BW_SMC_PMPROT_ALLS(baseAddr, 0);
        }
        break;
    case kAllowVlls:
        if (allow) 
        {
            BW_SMC_PMPROT_AVLLS(baseAddr, 1);
        }
        else
        {
            BW_SMC_PMPROT_AVLLS(baseAddr, 0);
        }
        break;
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    case kAllowHsrun:
        if (allow) 
        {
            BW_SMC_PMPROT_AHSRUN(baseAddr, 1);
        }
        else
        {
            BW_SMC_PMPROT_AHSRUN(baseAddr, 0);
        }
        break;
#endif
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetProtectionMode
 * Description   : Get the current power mode protection setting
 * This function will get the current power mode protection settings for
 * a specified power mode.
 * 
 *END**************************************************************************/
bool SMC_HAL_GetProtectionMode(uint32_t baseAddr, power_modes_protect_t protect)
{
    bool retValue = false;

    /* check the mode range */
    assert(protect < kAllowMax);

    /* branch according to the mode and read the setting */
    switch (protect)
    {
    case kAllowVlp:
        retValue = BR_SMC_PMPROT_AVLP(baseAddr);
        break;
    case kAllowLls:
        retValue = BR_SMC_PMPROT_ALLS(baseAddr);
        break;
    case kAllowVlls:
        retValue = BR_SMC_PMPROT_AVLLS(baseAddr);
        break;
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    case kAllowHsrun:
        retValue = BR_SMC_PMPROT_AHSRUN(baseAddr);
        break;
#endif
    default:
        break;
    }
    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetRunMode
 * Description   : Config the RUN mode control setting
 * This function will set the run mode settings. For example, normal run mode,
 * very lower power run mode, etc. Refer to smc_run_mode_t for supported run
 * mode on the chip family. Refer to reference manual for details about the 
 * run mode.
 * 
 *END**************************************************************************/
void SMC_HAL_SetRunMode(uint32_t baseAddr, smc_run_mode_t runMode)
{
    BW_SMC_PMCTRL_RUNM(baseAddr, runMode);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetRunMode
 * Description   : Get the current RUN mode config
 * This function will get the run mode settings. Refer to smc_run_mode_t 
 * for supported run mode on the chip family. Refer to reference manual for 
 * details about the run mode.
 * 
 *END**************************************************************************/
smc_run_mode_t SMC_HAL_GetRunMode(uint32_t baseAddr)
{
    return (smc_run_mode_t)BR_SMC_PMCTRL_RUNM(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetStopMode
 * Description   : Config the STOP mode control setting
 * This function will set the stop mode settings. For example, normal stop mode,
 * very lower power stop mode, etc. Refer to smc_stop_mode_t for supported stop
 * mode on the chip family. Refer to reference manual for details about the 
 * stop mode.
 * 
 *END**************************************************************************/
void SMC_HAL_SetStopMode(uint32_t baseAddr, smc_stop_mode_t stopMode)
{
    BW_SMC_PMCTRL_STOPM(baseAddr, stopMode);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetStopMode
 * Description   : Get the current STOP mode control setting
 * This function will get the stop mode settings. For example, normal stop mode,
 * very lower power stop mode, etc. Refer to smc_stop_mode_t for supported stop
 * mode on the chip family. Refer to reference manual for details about the 
 * stop mode.
 * 
 *END**************************************************************************/
smc_stop_mode_t SMC_HAL_GetStopMode(uint32_t baseAddr)
{
    return (smc_stop_mode_t)BR_SMC_PMCTRL_STOPM(baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetStopSubMode
 * Description   : Config the stop sub mode control setting
 * This function will set the stop submode settings. Some of the stop mode will
 * further have submode supported. Refer to smc_stop_submode_t for supported
 * stop submode and Refer to reference manual for details about the submode
 * for specific stop mode.
 * 
 *END**************************************************************************/
void SMC_HAL_SetStopSubMode(uint32_t baseAddr, smc_stop_submode_t stopSubMode)
{
#if FSL_FEATURE_SMC_USE_VLLSCTRL_REG
    BW_SMC_VLLSCTRL_VLLSM(baseAddr, stopSubMode);
#else
#if FSL_FEATURE_SMC_USE_STOPCTRL_VLLSM    
    BW_SMC_STOPCTRL_VLLSM(baseAddr, stopSubMode);
#else
    BW_SMC_STOPCTRL_LLSM(baseAddr, stopSubMode);
#endif    
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetStopSubMode
 * Description   : Get the current stop submode config 
 * This function will get the stop submode settings. Some of the stop mode will
 * further have submode supported. Refer to smc_stop_submode_t for supported
 * stop submode and Refer to reference manual for details about the submode
 * for specific stop mode.
 * 
 *END**************************************************************************/
smc_stop_submode_t SMC_HAL_GetStopSubMode(uint32_t baseAddr)
{
#if FSL_FEATURE_SMC_USE_VLLSCTRL_REG
    return (smc_stop_submode_t)BR_SMC_VLLSCTRL_VLLSM(baseAddr);
#else
#if FSL_FEATURE_SMC_USE_STOPCTRL_VLLSM    
    return (smc_stop_submode_t)BR_SMC_STOPCTRL_VLLSM(baseAddr);
#else
    return (smc_stop_submode_t)BR_SMC_STOPCTRL_LLSM(baseAddr);
#endif
#endif
}

#if FSL_FEATURE_SMC_HAS_PORPO
/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetPorMode
 * Description   : Config the POR (power-on-reset) option
 * This function will set the POR power option setting. It controls whether the
 * POR detect circuit (for brown-out detection) is enabled in certain stop mode.
 * The setting will be either enable or disable the above feature when POR 
 * happened. Refer to reference manual for details.
 * 
 *END**************************************************************************/
void SMC_HAL_SetPorMode(uint32_t baseAddr, smc_por_option_t option)
{
#if FSL_FEATURE_SMC_USE_VLLSCTRL_REG
    BW_SMC_VLLSCTRL_PORPO(baseAddr, option);
#else
    BW_SMC_STOPCTRL_PORPO(baseAddr, option);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetPorMode
 * Description   : Get the config of POR option
 * This function will set the POR power option setting. See config function
 * header for details.
 * 
 *END**************************************************************************/
smc_por_option_t SMC_HAL_GetPorMode(uint32_t baseAddr)
{
#if FSL_FEATURE_SMC_USE_VLLSCTRL_REG
    return (smc_por_option_t)BR_SMC_VLLSCTRL_PORPO(baseAddr);
#else
    return (smc_por_option_t)BR_SMC_STOPCTRL_PORPO(baseAddr);
#endif
}
#endif

#if FSL_FEATURE_SMC_HAS_PSTOPO
/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetPorMode
 * Description   : Config the PSTOPO (Partial Stop Option)
 * This function will set the PSTOPO option. It controls whether a Partial 
 * Stop mode is entered when STOPM=STOP. When entering a Partial Stop mode from
 * RUN mode, the PMC, MCG and flash remain fully powered, allowing the device 
 * to wakeup almost instantaneously at the expense of higher power consumption.
 * In PSTOP2, only system clocks are gated allowing peripherals running on bus
 * clock to remain fully functional. In PSTOP1, both system and bus clocks are
 * gated. Refer to smc_pstop_option_t for supported options. Refer to reference
 * manual for details.
 *
 *END**************************************************************************/
void SMC_HAL_SetPstopMode(uint32_t baseAddr, smc_pstop_option_t option)
{
    BW_SMC_STOPCTRL_PSTOPO(baseAddr, option);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetPorMode
 * Description   : Get the config of PSTOPO option 
 * This function will get the current PSTOPO option setting. Refer to config
 * function for more details.
 *
 *END**************************************************************************/
smc_pstop_option_t SMC_HAL_GetPstopMode(uint32_t baseAddr)
{
    return (smc_pstop_option_t)BR_SMC_STOPCTRL_PSTOPO(baseAddr);
}
#endif

#if FSL_FEATURE_SMC_HAS_LPOPO
/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetPorMode
 * Description   : Config the LPO option setting
 * This function will set the LPO option setting. It controls whether the 1kHZ
 * LPO clock is enabled in certain lower power stop modes. Refer to 
 * smc_lpo_option_t for supported options and refer to reference manual for 
 * details about this option.
 *
 *END**************************************************************************/
void SMC_HAL_SetLpoMode(uint32_t baseAddr, smc_lpo_option_t option)
{
    BW_SMC_STOPCTRL_LPOPO(baseAddr, option);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetPorMode
 * Description   : Get the config of LPO option
 * This function will get the current LPO option setting. Refer to config 
 * function for details.
 *
 *END**************************************************************************/
smc_por_option_t SMC_HAL_GetLpoMode(uint32_t baseAddr)
{
    return (smc_por_option_t)BR_SMC_STOPCTRL_LPOPO(baseAddr);
}
#endif

#if FSL_FEATURE_SMC_HAS_LPWUI
/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetLpwuiMode
 * Description   : Config the LPWUI (Low Power Wake Up on interrup) option
 * This function will set the LPWUI option. It will cause the system to exit
 * to normal RUN mode when any active interrupt occurs while in a certain lower
 * power mode. Refer to smc_lpwui_option_t for supported options and refer to 
 * reference manual for more details about this option.
 * 
 *END**************************************************************************/
void SMC_HAL_SetLpwuiMode(uint32_t baseAddr, smc_lpwui_option_t option)
{
    BW_SMC_PMCTRL_LPWUI(baseAddr, option);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetLpwuiMode
 * Description   : Get the current LPWUI option
 * This function will get the LPWUI option. Refer to config function for more
 * details.
 * 
 *END**************************************************************************/
smc_lpwui_option_t SMC_HAL_GetLpwuiMode(uint32_t baseAddr)
{
    return (smc_lpwui_option_t)BR_SMC_PMCTRL_LPWUI(baseAddr);
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetStat
 * Description   : Get the current power mode stat
 * This function will return the current power mode stat. Once application is 
 * switching the power mode, it should always check the stat to make sure it 
 * runs into the specified mode or not. Also application will need to check 
 * this mode before switching to certain mode. The system will require that
 * only certain mode could switch to other specific mode. Refer to the 
 * reference manual for details. Refer to _power_mode_stat for the meaning
 * of the power stat
 * 
 *END**************************************************************************/
uint8_t SMC_HAL_GetStat(uint32_t baseAddr)
{
    return BR_SMC_PMSTAT_PMSTAT(baseAddr); 
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

