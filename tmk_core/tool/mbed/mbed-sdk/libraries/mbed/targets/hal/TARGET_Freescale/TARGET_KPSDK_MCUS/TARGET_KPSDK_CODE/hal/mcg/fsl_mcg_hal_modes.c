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

#include "fsl_mcg_hal_modes.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*****************************************************************
 * MCG clock mode transition functions
 *
 *   FEI -> FEE
 *   FEI -> FBI
 *   FEI -> FBE
 *
 *   FEE -> FEI
 *   FEE -> FBI
 *   FEE -> FBE
 *
 *   FBI -> FEI
 *   FBI -> FEE
 *   FBI -> FBE
 *   FBI -> BLPI
 *
 *   BLPI -> FBI
 *
 *   FBE -> FEE
 *   FBE -> FEI
 *   FBE -> FBI
 *   FBE -> PBE
 *   FBE -> BLPE
 *
 *   PBE -> FBE 
 *   PBE -> PEE
 *   PBE -> BLPE
 *
 *   BLPE -> FBE
 *   BLPE -> PBE
 *
 *   PEE -> PBE
 *
 *****************************************************************/
/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_GetMcgMode
 * Description  : internal function will check the mcg registers and determine
 * the current mcg mode
 *
 * Return value : mcgMode or error code mcg_modes_t defined in fsl_mcg_hal_modes.h
 *END***********************************************************************************/
mcg_modes_t CLOCK_HAL_GetMcgMode(uint32_t baseAddr)
{
    /* Check MSG is in FEI mode */
    if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll) &&        /* CLKS mux is FLL output (CLKST=0) */
        (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal)      /* FLL ref is internal ref clk (IREFST=1) */
#if FSL_FEATURE_MCG_HAS_PLL          
        && (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll))          /* PLLS mux is FLL (PLLST=0) */
#else
        )
#endif
    {
        return kMcgModeFEI;                              /* return FEI code */
    }
    /* Check MCG is in PEE mode */
    else if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatPll) &&   /* CLKS mux is PLL output (CLKST=3) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatExternal)  /* FLL ref is external ref clk (IREFST=0) */
#if FSL_FEATURE_MCG_HAS_PLL                    
         && (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel))   /* PLLS mux is PLL or PLLCS (PLLST=1) */
#else
      )
#endif      
    {
        return kMcgModePEE;                              /* return PEE code */
    }
    /* Check MCG is in PBE mode */
    else if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatExternalRef) &&  /* CLKS mux is external ref clk (CLKST=2) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatExternal) && /* FLL ref is external ref clk (IREFST=0) */
#if FSL_FEATURE_MCG_HAS_PLL                    
             (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel) && /* PLLS mux is PLL or PLLCS (PLLST=1) */
#endif               
             (CLOCK_HAL_GetLowPowerMode(baseAddr) == kMcgLowPowerSelNormal))  /* MCG_C2[LP] bit is not set (LP=0) */
    {
        return kMcgModePBE;                              /* return PBE code */
    }
    /* Check MCG is in FBE mode */
    else if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatExternalRef) &&  /* CLKS mux is external ref clk (CLKST=2) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatExternal) && /* FLL ref is external ref clk (IREFST=0) */
#if FSL_FEATURE_MCG_HAS_PLL                 
             (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll) &&   /* PLLS mux is FLL (PLLST=0) */
#endif               
             (CLOCK_HAL_GetLowPowerMode(baseAddr) == kMcgLowPowerSelNormal))  /* MCG_C2[LP] bit is not set (LP=0) */  
    {
        return kMcgModeFBE;                              /* return FBE code */
    }
    /* Check MCG is in BLPE mode */
    else if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatExternalRef) &&  /* CLKS mux is external ref clk (CLKST=2) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatExternal) && /* FLL ref is external ref clk (IREFST=0) */
             (CLOCK_HAL_GetLowPowerMode(baseAddr) == kMcgLowPowerSelLowPower))/* MCG_C2[LP] bit is set (LP=1) */
    {
        return kMcgModeBLPE;                             /* return BLPE code */
    }
    /* Check if in BLPI mode */
    else if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatInternalRef) &&  /* CLKS mux in internal ref clk (CLKST=1) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal) && /* FLL ref is internal ref clk (IREFST=1) */
#if FSL_FEATURE_MCG_HAS_PLL                 
             (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll) &&   /* PLLS mux is FLL (PLLST=0) */
#endif               
             (CLOCK_HAL_GetLowPowerMode(baseAddr) == kMcgLowPowerSelLowPower))/* MCG_C2[LP] bit is set (LP=1) */
    {
        return kMcgModeBLPI;                             /* return BLPI code */
    }
    /* Check if in FBI mode */
    else if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatInternalRef) &&  /* CLKS mux in internal ref clk (CLKST=1) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal) && /* FLL ref is internal ref clk (IREFST=1) */
#if FSL_FEATURE_MCG_HAS_PLL                 
             (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll) &&   /* PLLS mux is FLL (PLLST=0) */
#endif               
             (CLOCK_HAL_GetLowPowerMode(baseAddr) == kMcgLowPowerSelNormal))  /* MCG_C2[LP] bit is not set (LP=0) */
    {  
        return kMcgModeFBI;                              /* return FBI code */
    }
    /* Check MCG is in FEE mode */
    else if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll) &&   /* CLKS mux is FLL output (CLKST=0) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatExternal) /* FLL ref is external ref clk (IREFST=0) */
#if FSL_FEATURE_MCG_HAS_PLL                 
          && (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll))     /* PLLS mux is FLL (PLLST=0) */
#else
      )
#endif      
    {
        return kMcgModeFEE;                              /* return FEE code */
    }
    else
    {
        return kMcgModeError;                            /* error unknown mode */
    }
}   /* CLOCK_HAL_GetMcgMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_GetFllFrequency
 * Description  : internal function to check the fll frequency
 * This function will calculate and check the fll frequency value based on input value.
 *
 * Parameters: fllRef  - fll reference clock in Hz.
 *
 * Return value : fll output frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_GetFllFrequency(uint32_t baseAddr, int32_t fllRef)
{
    int32_t fllFreqHz = 0;
  
    /* Check that only allowed ranges have been selected */
    if (CLOCK_HAL_GetDigitalControlledOscRangeMode(baseAddr) > kMcgDigitalControlledOscRangeSelMid)
    {
        return kMcgErrFllDrstDrsRange; /* return error code if DRS range 2 or 3 selected */
    }
  
    /* if DMX32 set */
    if (CLOCK_HAL_GetDmx32(baseAddr))
    {
        /* determine multiplier based on DRS */
        switch (CLOCK_HAL_GetDigitalControlledOscRangeMode(baseAddr))
        {
        case 0:
            fllFreqHz = (fllRef * kMcgConstant732);
            if (fllFreqHz < kMcgConstant20000000) 
            {
                return kMcgErrFllRange0Min;
            }
            else if (fllFreqHz > kMcgConstant25000000) 
            {
                return kMcgErrFllRange0Max;
            }
            break;
        case 1:
            fllFreqHz = (fllRef * kMcgConstant1464);
            if (fllFreqHz < kMcgConstant40000000) 
            {
                return kMcgErrFllRange1Min;
            }
            else if (fllFreqHz > kMcgConstant50000000) 
            {
                return kMcgErrFllRange1Max;
            }
            break;
        case 2:
            fllFreqHz = (fllRef * kMcgConstant2197);
            if (fllFreqHz < kMcgConstant60000000) 
            {
                return kMcgErrFllRange2Min;
            }
            else if (fllFreqHz > kMcgConstant75000000) 
            {
                return kMcgErrFllRange2Max;
            }
            break;
        case 3:
            fllFreqHz = (fllRef * kMcgConstant2929);
            if (fllFreqHz < kMcgConstant80000000) 
            {
                return kMcgErrFllRange3Min;
            }
            else if (fllFreqHz > kMcgConstant100000000) 
            {
                return kMcgErrFllRange3Max;
            }
            break;
        default:
            break;
        }
    }
    /* if DMX32 = 0 */
    else 
    {
        /* determine multiplier based on DRS */
        switch (CLOCK_HAL_GetDigitalControlledOscRangeMode(baseAddr))
        {
        case 0:
            fllFreqHz = (fllRef * kMcgConstant640);
            if (fllFreqHz < kMcgConstant20000000) 
            {
                return kMcgErrFllRange0Min;
            }
            else if (fllFreqHz > kMcgConstant25000000) 
            {
                return kMcgErrFllRange0Max;
            }
            break;
        case 1:
            fllFreqHz = (fllRef * kMcgConstant1280);
            if (fllFreqHz < kMcgConstant40000000) 
            {
                return kMcgErrFllRange1Min;
            }
            else if (fllFreqHz > kMcgConstant50000000) 
            {
                return kMcgErrFllRange1Max;
            }
            break;
        case 2:
            fllFreqHz = (fllRef * kMcgConstant1920);
            if (fllFreqHz < kMcgConstant60000000) 
            {
                return kMcgErrFllRange2Min;
            }
            else if (fllFreqHz > kMcgConstant75000000) 
            {
                return kMcgErrFllRange2Max;
            }
            break;
        case 3:
            fllFreqHz = (fllRef * kMcgConstant2560);
            if (fllFreqHz < kMcgConstant80000000) 
            {
                return kMcgErrFllRange3Min;
            }
            else if (fllFreqHz > kMcgConstant100000000) 
            {
                return kMcgErrFllRange3Max;
            }
            break;
        default:
            break;
        }
    }    
    return fllFreqHz;
}   /* CLOCK_HAL_GetFllFrequency */


/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFeiToFeeMode
 * Description  : Mode transition FEI to FEE mode
 * This function transitions the MCG from FEI mode to FEE mode. 
 *
 * Parameters: oscselVal  - oscillator selection value 
 *                          (eunm defined in mcg_oscsel_select_t)
 *                          0: kMcgOscselOsc, Selects System Oscillator (OSCCLK)
 *                          1: kMcgOscselRtc, Selects 32 kHz RTC Oscillator 
 *                          2: kMcgOscselIrc, Selects 48 MHz IRC Oscillator (K70)
 *             crystalVal - external clock frequency in Hz
 *                          oscselVal - 0
 *                             erefsVal - 0: osc0 external clock frequency
 *                             erefsVal - 1: osc0 crystal clock frequency
 *                          oscselVal - 1: RTC 32Khz clock source frequency
 *                          oscselVal - 2: IRC 48Mhz clock source frequency
 *             hgoVal     - selects whether low power or high gain mode is selected
 *                          for the crystal oscillator. This value is only valid when
 *                          oscselVal is 0 and erefsVal is 1.
 *                          (enum defined in mcg_high_gain_osc_select_t)
 *                          0: kMcgHgoSelectLow,  Configure for low-power operation 
 *                          1: kMcgHgoSelectHigh, Configure for high-gain operation 
 *             erefsVal   - selects external clock or crystal osc 
 *                          (enum defined in mcg_external_ref_clock_select_t)
 *                          0: kMcgErefClockSelectExt, External reference clock requested 
 *                          1: kMcgErefClockSelectOsc, Oscillator requested 
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFeiToFeeMode(uint32_t baseAddr, mcg_oscsel_select_t oscselVal, uint32_t crystalVal, mcg_high_gain_osc_select_t hgoVal, mcg_external_ref_clock_select_t erefsVal)
{
    uint8_t frDivVal;
    uint32_t mcgOut, fllRefFreq, i;
  
    /* check if in FEI mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFEI)
    {
        return kMcgErrNotInFeiMode;                   /* return error code */
    }

    /* check external frequency is less than the maximum frequency */
    if  (crystalVal > kMcgConstant50000000) 
    {
        return kMcgErrOscEtalRange;       /* - external frequency is bigger than max frequency */
    }
  
    /* check crystal frequency is within spec. if crystal osc is being used */
    if (oscselVal == kMcgOscselOsc)
    {
        if (erefsVal)
        {
            /* return error if one of the available crystal options is not available */
            if ((crystalVal < kMcgConstant30000) ||
                ((crystalVal > kMcgConstant40000) && (crystalVal < kMcgConstant3000000)) ||
                (crystalVal > kMcgConstant32000000)) 
            {
                return kMcgErrOscXtalRange; /* - crystal frequency outside allowed range */
            } 

            /* config the hgo settings */
            CLOCK_HAL_SetHighGainOsc0Mode(baseAddr, hgoVal);
        }

        /* config the erefs0 settings */
        CLOCK_HAL_SetExternalRefSel0Mode(baseAddr, erefsVal);
    }

    /* 
     * the RANGE value is determined by the external frequency. Since the RANGE parameter 
     * affects the FRDIV divide value it still needs to be set correctly even if the 
     * oscillator is not being used
     */
    if (crystalVal <= kMcgConstant40000)
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelLow);
    }
    else if (crystalVal <= kMcgConstant8000000)
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelHigh);
    }
    else
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelVeryHigh);
    }

    /* determine FRDIV based on reference clock frequency */
    /* since the external frequency has already been checked only the maximum frequency for each FRDIV value needs to be compared here. */
    if (crystalVal <= kMcgConstant1250000) 
    {
        frDivVal = kMcgConstant0;
    }
    else if (crystalVal <= kMcgConstant2500000) 
    {
        frDivVal = kMcgConstant1;
    }
    else if (crystalVal <= kMcgConstant5000000) 
    {
        frDivVal = kMcgConstant2;
    }
    else if (crystalVal <= kMcgConstant10000000) 
    {
        frDivVal = kMcgConstant3;
    }
    else if (crystalVal <= kMcgConstant20000000) 
    {
        frDivVal = kMcgConstant4;
    }
    else 
    {
        frDivVal = kMcgConstant5;
    }
   
    /* The FLL ref clk divide value depends on FRDIV and the RANGE value */
    if (CLOCK_HAL_GetRange0Mode(baseAddr) > kMcgFreqRangeSelLow)
    {
        fllRefFreq = ((crystalVal) / (kMcgConstant32 << frDivVal));
    }
    else
    {
        fllRefFreq = ((crystalVal) / (kMcgConstant1 << frDivVal));
    }

    /* Check resulting FLL frequency  */
    /* FLL reference frequency calculated from ext ref freq and FRDIV */
    mcgOut = CLOCK_HAL_GetFllFrequency(baseAddr, fllRefFreq);      
    if (mcgOut < kMcgErrMax) 
    {
        return mcgOut;  /* If error code returned, return the code to calling function */
    }

    /* 
     * Select external oscilator and Reference Divider and clear IREFS to start ext osc
     * If IRCLK is required it must be enabled outside of this driver, existing state will 
     * be maintained CLKS=0, FRDIV=frdivVal, IREFS=0 
     */
    CLOCK_HAL_SetClksFrdivInternalRefSelect(baseAddr, kMcgClkSelOut, frDivVal, kMcgInternalRefClkSrcExternal);

    /* if the external oscillator is used need to wait for OSCINIT to set */
    if ((oscselVal == kMcgOscselOsc) && (erefsVal))
    {
        for (i = 0 ; i < kMcgConstant20000000 ; i++)
        {
            if (CLOCK_HAL_GetOscInit0(baseAddr))
            {
                break; /* jump out early if OSCINIT sets before loop finishes */
            }
        }

        if (!CLOCK_HAL_GetOscInit0(baseAddr))
        {
            /* check bit is really set and return with error if not set */
            return kMcgErrOscSetTimeout; 
        }
    }

    /* Wait for clock status bits to show clock source is FLL */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll)
        {
            break; // jump out early if CLKST shows FLL selected before loop finishes
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatFll) 
    {
        return kMcgErrClkst0; // check FLL is really selected and return with error if not
    }

    /* 
     * Now in FEE  
     * It is recommended that the clock monitor is enabled when using an external clock as the 
     * clock source/reference. 
     * It is enabled here but can be removed if this is not required.
     */
    CLOCK_HAL_SetClkMonitor0Cmd(baseAddr, true);
    
    return mcgOut; /* MCGOUT frequency equals FLL frequency */
} /* CLOCK_HAL_SetFeiToFeeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFeiToFbiMode
 * Description  : Mode transition FEI to FBI mode
 * This function transitions the MCG from FEI mode to FBI mode. 
 *
 * Parameters: ircFreq       - internal reference clock frequency value
 *             ircSelect     - slow or fast clock selection
 *                             0: slow, 1: fast
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFeiToFbiMode(uint32_t baseAddr, uint32_t ircFreq, mcg_internal_ref_clock_select_t ircSelect)
{
    uint8_t fcrDivVal;
    uint16_t i;
  
    /* Check MCG is in FEI mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFEI)
    {
        return kMcgErrNotInFeiMode;                 /* return error code */
    } 


    /* Check that the irc frequency matches the selected IRC  */
    if (!(ircSelect))
    {    
        if ((ircFreq < kMcgConstant31250) || (ircFreq > kMcgConstant39063))
        {
            return kMcgErrIrcSlowRange;
        }
    }
    else
    {
        if ((ircFreq < kMcgConstant3000000) || (ircFreq > kMcgConstant5000000))
        {
            return kMcgErrIrcFastRange;
        } /* Fast IRC freq */
    }

    /* Select the desired IRC */
    CLOCK_HAL_SetInternalRefClkSelMode(baseAddr, ircSelect);
  
    /* Change the CLKS mux to select the IRC as the MCGOUT */
    CLOCK_HAL_SetClkSrcMode(baseAddr, kMcgClkSelInternal);

    /* Set LP bit to enable the FLL */
    CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelNormal);

    /* wait until internal reference switches to requested irc. */
    if (ircSelect == kMcgInternalRefClkSelSlow)
    {
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (!(MCG_S & MCG_S_IRCST_MASK))
            {
                break; /* jump out early if IRCST clears before loop finishes */
            }
        }
        if (MCG_S & MCG_S_IRCST_MASK)
        {
            /* check bit is really clear and return with error if set */
            return kMcgErrIrcstClearTimeout; 
        }
    }
    else
    {
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (MCG_S & MCG_S_IRCST_MASK)
            {
                break; /* jump out early if IRCST sets before loop finishes */
            }
        }
        if (!(MCG_S & MCG_S_IRCST_MASK))
        {
            /* check bit is really set and return with error if not set */
            return kMcgErrIrefstSetTimeout1; 
        }
    }
  
    /* Wait for clock status bits to update */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatInternalRef)
        {
            break; /* jump out early if CLKST shows IRC slected before loop finishes */  
        }
    }
 
    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatInternalRef)
    {
        /* check IRC is really selected and return with error if not */
        return kMcgErrClkst1; 
    }
  
    /* Now in FBI mode */
    if (ircSelect == kMcgInternalRefClkSelFast)
    {
        fcrDivVal = CLOCK_HAL_GetFastClkInternalRefDivider(baseAddr);

        /* MCGOUT frequency equals fast IRC frequency divided by 2 */
        return (ircFreq / fcrDivVal); 
    }
    else
    {
        return ircFreq; /* MCGOUT frequency equals slow IRC frequency */
    }   
}   /* CLOCK_HAL_SetFeiToFbiMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFeiToFbeMode
 * Description  : Mode transition FEI to FBE mode
 * This function transitions the MCG from FEI mode to FBE mode. 
 *
 * Parameters: oscselVal  - oscillator selection value
 *                          0 - OSC 0,  1 - RTC 32k, 2 - IRC 48M
 *             crystalVal - external clock frequency in Hz
 *                          oscselVal - 0
 *                             erefsVal - 0: osc0 external clock frequency
 *                             erefsVal - 1: osc0 crystal clock frequency
 *                          oscselVal - 1: RTC 32Khz clock source frequency
 *                          oscselVal - 2: IRC 48Mhz clock source frequency
 *             hgoVal     - selects whether low power or high gain mode is selected
 *                          for the crystal oscillator. This value is only valid when
 *                          oscselVal is 0 and erefsVal is 1.
 *             erefsVal   - selects external clock (=0) or crystal osc (=1) 
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFeiToFbeMode(uint32_t baseAddr, mcg_oscsel_select_t oscselVal, uint32_t crystalVal, mcg_high_gain_osc_select_t hgoVal, mcg_external_ref_clock_select_t erefsVal)
{
    uint8_t frDivVal;
    int16_t i;
  
    /* check if in FEI mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFEI)
    {
        return kMcgErrNotInFeiMode;                 /* return error code */
    }

    /* check external frequency is less than the maximum frequency */
    if  (crystalVal > kMcgConstant50000000) 
    {
        /* - external frequency is bigger than max frequency */
        return kMcgErrOscEtalRange;       
    }
  
    /* check crystal frequency is within spec. if crystal osc is being used */
    if (oscselVal == kMcgOscselOsc)
    {
        if (erefsVal)
        {
            /* return error if one of the available crystal options is not available */
            if ((crystalVal < kMcgConstant30000) ||
                ((crystalVal > kMcgConstant40000) && (crystalVal < kMcgConstant3000000)) ||
                (crystalVal > kMcgConstant32000000)) 
            {
                /* - crystal frequency outside allowed range */
                return kMcgErrOscXtalRange; 
            } 

            /* config the hgo settings */
            CLOCK_HAL_SetHighGainOsc0Mode(baseAddr, hgoVal);
        }

        /* config the erefs0 settings */
        CLOCK_HAL_SetExternalRefSel0Mode(baseAddr, erefsVal);
    }

    /* 
     * the RANGE value is determined by the external frequency. Since the RANGE parameter           
     * affects the FRDIV divide value it still needs to be set correctly even if the 
     * oscillator is not being used
     */
    if (crystalVal <= kMcgConstant40000)
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelLow);
    }
    else if (crystalVal <= kMcgConstant8000000)
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelHigh);
    }
    else
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelVeryHigh);
    }

    /* determine FRDIV based on reference clock frequency */
    /* since the external frequency has already been checked only the maximum frequency for each FRDIV value needs to be compared here. */
    if (crystalVal <= kMcgConstant1250000) 
    {
        frDivVal = kMcgConstant0;
    }
    else if (crystalVal <= kMcgConstant2500000) 
    {
        frDivVal = kMcgConstant1;
    }
    else if (crystalVal <= kMcgConstant5000000) 
    {
        frDivVal = kMcgConstant2;
    }
    else if (crystalVal <= kMcgConstant10000000) 
    {
        frDivVal = kMcgConstant3;
    }
    else if (crystalVal <= kMcgConstant20000000) 
    {
        frDivVal = kMcgConstant4;
    }
    else 
    {
        frDivVal = kMcgConstant5;
    }
     
    /* Set LP bit to enable the FLL */
    CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelNormal);

    /* 
     * Select external oscilator and Reference Divider and clear IREFS to start ext osc
     * If IRCLK is required it must be enabled outside of this driver, existing state will 
     * be maintained CLKS=0, FRDIV=frdivVal, IREFS=0 
     */
    CLOCK_HAL_SetClksFrdivInternalRefSelect(baseAddr, kMcgClkSelExternal, frDivVal, kMcgInternalRefClkSrcExternal);

    /* if the external oscillator is used need to wait for OSCINIT to set */
    if ((oscselVal == kMcgOscselOsc) && (erefsVal))
    {
        for (i = 0 ; i < kMcgConstant10000 ; i++)
        {
            if (CLOCK_HAL_GetOscInit0(baseAddr))
            {
                break; /* jump out early if OSCINIT sets before loop finishes */
            }
        }

        if (!CLOCK_HAL_GetOscInit0(baseAddr))
        {
            /* check bit is really set and return with error if not set */
            return kMcgErrOscSetTimeout; 
        }
    }

    /* wait for Reference clock Status bit to clear */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (!CLOCK_HAL_GetInternalRefStatMode(baseAddr))
        {
            break; /* jump out early if IREFST clears before loop finishes */
        }
    }

    if (CLOCK_HAL_GetInternalRefStatMode(baseAddr))
    {
        /* check bit is really clear and return with error if not set */
        return kMcgErrIrefstClearTimeOut; 
    }

    /* Wait for clock status bits to show clock source is ext ref clk */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatExternalRef)
        {
            break; /* jump out early if CLKST shows EXT CLK slected before loop finishes */
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatExternalRef)
    {
        return kMcgErrClkst2; /* check EXT CLK is really selected and return with error if not */
    }

    /* 
     * Now in FBE  
     * It is recommended that the clock monitor is enabled when using an external clock as the clock source/reference.
     * It is enabled here but can be removed if this is not required.
     */
    CLOCK_HAL_SetClkMonitor0Cmd(baseAddr, true);
    
    return crystalVal; /* MCGOUT frequency equals external clock frequency */
}   /* CLOCK_HAL_SetFeiToFbeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFeeToFeiMode
 * Description  : Mode transition FEE to FEI mode
 * This function transitions the MCG from FEE mode to FEI mode. 
 *
 * Parameters: ircFreq       - internal reference clock frequency value (slow)
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFeeToFeiMode(uint32_t baseAddr, uint32_t ircFreq)
{
    int16_t i;
    uint32_t mcgOut;

    /* Check MCG is in FEE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFEE)
    {
        return kMcgErrNotInFeeMode;                 /* return error code */
    } 
      
    /* Check IRC frequency is within spec. */
    if ((ircFreq < kMcgConstant31250) || (ircFreq > kMcgConstant39063))
    {
        return kMcgErrIrcSlowRange;
    }

    /* Check resulting FLL frequency */
    mcgOut = CLOCK_HAL_GetFllFrequency(baseAddr, ircFreq); 
    if (mcgOut < kMcgErrMax) 
    {
        /* If error code returned, return the code to calling function */
        return mcgOut;
    } 
  
    /* Ensure clock monitor is disabled before switching to FEI otherwise 
     * a loss of clock will trigger 
     */
    CLOCK_HAL_SetClkMonitor0Cmd(baseAddr, false);

    /* Change FLL reference clock from external to internal by setting IREFS bit */
    CLOCK_HAL_SetInternalRefSelMode(baseAddr, kMcgInternalRefClkSrcSlow);
  
    /* wait for Reference clock to switch to internal reference */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal)
        {
            break; /* jump out early if IREFST sets before loop finishes */
        }
    }

    if (CLOCK_HAL_GetInternalRefStatMode(baseAddr) != kMcgInternalRefStatInternal)
    {
        /* check bit is really set and return with error if not set */
        return kMcgErrIrefstSetTimeout; 
    }
    
    /* Now in FEI mode */
    return mcgOut;  
} /* CLOCK_HAL_SetFeeToFeiMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFeeToFbiMode
 * Description  : Mode transition FEE to FBI mode
 * This function transitions the MCG from FEE mode to FBI mode. 
 *
 * Parameters: ircFreq       - internal reference clock frequency value
 *             ircSelect     - slow or fast clock selection
 *                             0: slow, 1: fast
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFeeToFbiMode(uint32_t baseAddr, uint32_t ircFreq, mcg_internal_ref_clock_select_t ircSelect)
{ 
    uint8_t fcrDivVal;
    int16_t i;
    
    /* Check MCG is in FEE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFEE)
    {
        return kMcgErrNotInFeeMode;                 /* return error code */
    }
  
    /* Check that the irc frequency matches the selected IRC */
    if (!(ircSelect))
    {    
        if ((ircFreq < kMcgConstant31250) || (ircFreq > kMcgConstant39063)) 
        {
            return kMcgErrIrcSlowRange;
        } 
    }
    else
    {
        if ((ircFreq < kMcgConstant3000000) || (ircFreq > kMcgConstant5000000)) 
        {
            return kMcgErrIrcFastRange;
        } /* Fast IRC freq */
    }
    
    /* Select the required IRC */
    CLOCK_HAL_SetInternalRefClkSelMode(baseAddr, ircSelect);
    
    /* Make sure the clock monitor is disabled before switching modes otherwise it will trigger */
    CLOCK_HAL_SetClkMonitor0Cmd(baseAddr, false);

    /* Select the IRC as the CLKS mux selection */
    CLOCK_HAL_SetClksFrdivInternalRefSelect(baseAddr, kMcgClkSelInternal, CLOCK_HAL_GetFllExternalRefDivider(baseAddr), kMcgInternalRefClkSrcSlow); 
 
    /* wait until internal reference switches to requested irc. */
    if (ircSelect == kMcgInternalRefClkSelSlow)
    {
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetInternalRefClkStatMode(baseAddr) == kMcgInternalRefClkStatSlow)
            {
                break; /* jump out early if IRCST clears before loop finishes */
            }
        }
      if (CLOCK_HAL_GetInternalRefClkStatMode(baseAddr) != kMcgInternalRefClkStatSlow)
      {
          /* check bit is really clear and return with error if set */
          return kMcgErrIrcstClearTimeout; 
      }
    }
    else
    {
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetInternalRefClkStatMode(baseAddr) == kMcgInternalRefClkStatFast)
            {
                break; /* jump out early if IRCST sets before loop finishes */
            }
        }
        if (CLOCK_HAL_GetInternalRefClkStatMode(baseAddr) != kMcgInternalRefClkStatFast)
        {
            /* check bit is really set and return with error if not set */
            return kMcgErrIrefstSetTimeout1; 
        }
    }
  
    /* Wait for clock status bits to update */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatInternalRef)
        {
            break; /* jump out early if CLKST shows IRC slected before loop finishes */
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatInternalRef)
    {
        return kMcgErrClkst1; /* check IRC is really selected and return with error if not */
    }
  
    /* wait for Reference clock Status bit to set */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal)
        {
            break; /* jump out early if IREFST sets before loop finishes */
        }
    }

    if (CLOCK_HAL_GetInternalRefStatMode(baseAddr) != kMcgInternalRefStatInternal)
    {
        /* check bit is really set and return with error if not set */
        return kMcgErrIrefstSetTimeout; 
    }
  
    /* Now in FBI mode */
    if (ircSelect == kMcgInternalRefClkSelFast)
    {
        fcrDivVal = CLOCK_HAL_GetFastClkInternalRefDivider(baseAddr);

        return (ircFreq / fcrDivVal); /* MCGOUT frequency equals fast IRC frequency divided by 2 */
    }
    else
    {
        return ircFreq; /* MCGOUT frequency equals slow IRC frequency */
    }
}   /* CLOCK_HAL_SetFeeToFbiMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFeeToFbeMode
 * Description  : Mode transition FEE to FBE mode
 * This function transitions the MCG from FEE mode to FBE mode. 
 *
 * Parameters: crystalVal    - external reference clock frequency value
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFeeToFbeMode(uint32_t baseAddr, uint32_t crystalVal)
{ 
    uint16_t i;
  
    /* Check MCG is in FEE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFEE)
    {
        return kMcgErrNotInFeeMode;                 /* return error code */
    }
  
    /* Set CLKS field to 2 to switch CLKS mux to select ext ref clock */
    CLOCK_HAL_SetClkSrcMode(baseAddr, kMcgClkSelExternal);

    /* Wait for clock status bits to show clock source is ext ref clk */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatExternalRef)
        {
            break; /* jump out early if CLKST shows EXT CLK slected before loop finishes */
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatExternalRef)
    {
        return kMcgErrClkst2; /* check EXT CLK is really selected and return with error if not */
    }
    
    /* Now in FBE mode */
    return crystalVal;
}   /* CLOCK_HAL_SetFeeToFbeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbiToFeiMode
 * Description  : Mode transition FBI to FEI mode
 * This function transitions the MCG from FBI mode to FEI mode. 
 *
 * Parameters: ircFreq       - internal reference clock frequency value (slow)
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbiToFeiMode(uint32_t baseAddr, uint32_t ircFreq)
{
    int16_t i;
    int32_t mcgOut;

    /* check if in FBI mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBI)
    {  
        return kMcgErrNotInFbiMode;                 /* MCG not in correct mode return fail code */
    }

    /* Check IRC frequency is within spec. */
    if ((ircFreq < 31250) || (ircFreq > 39063))
    {
        return kMcgErrIrcSlowRange;
    }

    /* Check resulting FLL frequency */
    mcgOut = CLOCK_HAL_GetFllFrequency(baseAddr, ircFreq); 
    if (mcgOut < kMcgErrMax) 
    {
        /* If error code returned, return the code to calling function */
        return mcgOut;
    } 
  
    /* Change the CLKS mux to select the FLL output as MCGOUT */
    CLOCK_HAL_SetClksFrdivInternalRefSelect(baseAddr, kMcgClkSelOut, CLOCK_HAL_GetFllExternalRefDivider(baseAddr), kMcgInternalRefClkSrcSlow);
  
    /* wait for Reference clock Status bit to clear */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetInternalRefStatMode(baseAddr))
        {
            break; /* jump out early if IREFST clears before loop finishes */
        }
    }

    if (!CLOCK_HAL_GetInternalRefStatMode(baseAddr))
    {
        /* check bit is really set and return with error if not set */
        return kMcgErrIrefstSetTimeout; 
    }
  
    /* Wait for clock status bits to show clock source is ext ref clk */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll)
        {
            break; /* jump out early if CLKST shows FLL slected before loop finishes */
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll)
    {
        return kMcgErrClkst0; /* check FLL is really selected and return with error if not */
    }

    /* Now in FEI mode */
    return mcgOut;  
}   /* CLOCK_HAL_SetFbiToFeiMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbiToFeeMode
 * Description  : Mode transition FBI to FEE mode
 * This function transitions the MCG from FBI mode to FEE mode. 
 *
 * Parameters: oscselVal  - oscillator selection value
 *                          0 - OSC 0,  1 - RTC 32k, 2 - IRC 48M
 *             crystalVal - external clock frequency in Hz
 *                          oscselVal - 0
 *                             erefsVal - 0: osc0 external clock frequency
 *                             erefsVal - 1: osc0 crystal clock frequency
 *                          oscselVal - 1: RTC 32Khz clock source frequency
 *                          oscselVal - 2: IRC 48Mhz clock source frequency
 *             hgoVal     - selects whether low power or high gain mode is selected
 *                          for the crystal oscillator. This value is only valid when
 *                          oscselVal is 0 and erefsVal is 1.
 *             erefsVal   - selects external clock (=0) or crystal osc (=1) 
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbiToFeeMode(uint32_t baseAddr, mcg_oscsel_select_t oscselVal, uint32_t crystalVal, mcg_high_gain_osc_select_t hgoVal, mcg_external_ref_clock_select_t erefsVal)
{
    uint8_t frDivVal;
    uint32_t i;
    uint32_t mcgOut, fllRefFreq;

    /* check if in FBI mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBI)
    {  
        return kMcgErrNotInFbiMode;                 /* MCG not in correct mode return fail code */
    }
  
    /* check external frequency is less than the maximum frequency */
    if  (crystalVal > kMcgConstant50000000) 
    {
        return kMcgErrOscEtalRange;
    }
  
    /* check crystal frequency is within spec. if crystal osc is being used */
    if (oscselVal == kMcgOscselOsc)
    {
        if (erefsVal)
        {
            /* return error if one of the available crystal options is not available */
            if ((crystalVal < kMcgConstant30000) ||
                ((crystalVal > kMcgConstant40000) && (crystalVal < kMcgConstant3000000)) ||
                (crystalVal > kMcgConstant32000000)) 
            {
                return kMcgErrOscXtalRange; /* - crystal frequency outside allowed range */
            } 

            /* config the hgo settings */
            CLOCK_HAL_SetHighGainOsc0Mode(baseAddr, hgoVal);
        }

        /* config the erefs0 settings */
        CLOCK_HAL_SetExternalRefSel0Mode(baseAddr, erefsVal);
    }

    /* 
     * the RANGE value is determined by the external frequency. Since the RANGE parameter 
     * affects the FRDIV divide value it still needs to be set correctly even if the 
     * oscillator is not being used
     */
    if (crystalVal <= kMcgConstant40000)
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelLow);
    }
    else if (crystalVal <= kMcgConstant8000000)
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelHigh);
    }
    else
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelVeryHigh);
    }

    /* determine FRDIV based on reference clock frequency */
    /* since the external frequency has already been checked only the maximum frequency for each FRDIV
     * value needs to be compared here.
     */
    if (crystalVal <= kMcgConstant1250000) 
    {
        frDivVal = kMcgConstant0;
    }
    else if (crystalVal <= kMcgConstant2500000) 
    {
        frDivVal = kMcgConstant1;
    }
    else if (crystalVal <= kMcgConstant5000000) 
    {
        frDivVal = kMcgConstant2;
    }
    else if (crystalVal <= kMcgConstant10000000) 
    {
        frDivVal = kMcgConstant3;
    }
    else if (crystalVal <= kMcgConstant20000000) 
    {
        frDivVal = kMcgConstant4;
    }
    else 
    {
        frDivVal = kMcgConstant5;
    }
   
    /* The FLL ref clk divide value depends on FRDIV and the RANGE value */
    if (CLOCK_HAL_GetRange0Mode(baseAddr) > kMcgFreqRangeSelLow)
    {
        fllRefFreq = ((crystalVal) / (kMcgConstant32 << frDivVal));
    }
    else
    {
        fllRefFreq = ((crystalVal) / (kMcgConstant1 << frDivVal));
    }

    /* Check resulting FLL frequency  */
    /* FLL reference frequency calculated from ext ref freq and FRDIV */
    mcgOut = CLOCK_HAL_GetFllFrequency(baseAddr, fllRefFreq);      
    if (mcgOut < kMcgErrMax) 
    {
        return mcgOut;  /* If error code returned, return the code to calling function */
    }
  
    /* 
     * Select external oscilator and Reference Divider and clear IREFS to start ext osc
     * If IRCLK is required it must be enabled outside of this driver, existing state will 
     * be maintained CLKS=0, FRDIV=frdivVal, IREFS=0
     */
    CLOCK_HAL_SetClksFrdivInternalRefSelect(baseAddr, kMcgClkSelOut, frDivVal, kMcgInternalRefClkSrcExternal);

    /* if the external oscillator is used need to wait for OSCINIT to set */
    if ((oscselVal == kMcgOscselOsc) && (erefsVal))
    {
        for (i = 0 ; i < kMcgConstant20000000 ; i++)
        {
            if (CLOCK_HAL_GetOscInit0(baseAddr))
            {
                break; /* jump out early if OSCINIT sets before loop finishes */
            }
        }

        if (!CLOCK_HAL_GetOscInit0(baseAddr))
        {
            /* check bit is really set and return with error if not set */
            return kMcgErrOscSetTimeout; 
        }
    }

    /* Wait for clock status bits to show clock source is FLL */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll)
        {
            break; // jump out early if CLKST shows FLL selected before loop finishes
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatFll) 
    {
        return kMcgErrClkst0; // check FLL is really selected and return with error if not
    }

    /* 
     * Now in FEE  
     * It is recommended that the clock monitor is enabled when using an external clock as the 
     * clock source/reference. 
     * It is enabled here but can be removed if this is not required.
     */
    CLOCK_HAL_SetClkMonitor0Cmd(baseAddr, true);
    
    return mcgOut; /* MCGOUT frequency equals FLL frequency */
}   /* CLOCK_HAL_SetFbiToFeeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbiToFbeMode
 * Description  : Mode transition FBI to FBE mode
 * This function transitions the MCG from FBI mode to FBE mode. 
 *
 * Parameters: oscselVal  - oscillator selection value
 *                          0 - OSC 0,  1 - RTC 32k, 2 - IRC 48M
 *             crystalVal - external clock frequency in Hz
 *                          oscselVal - 0
 *                             erefsVal - 0: osc0 external clock frequency
 *                             erefsVal - 1: osc0 crystal clock frequency
 *                          oscselVal - 1: RTC 32Khz clock source frequency
 *                          oscselVal - 2: IRC 48Mhz clock source frequency
 *             hgoVal     - selects whether low power or high gain mode is selected
 *                          for the crystal oscillator. This value is only valid when
 *                          oscselVal is 0 and erefsVal is 1.
 *             erefsVal   - selects external clock (=0) or crystal osc (=1) 
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbiToFbeMode(uint32_t baseAddr, mcg_oscsel_select_t oscselVal, uint32_t crystalVal, mcg_high_gain_osc_select_t hgoVal, mcg_external_ref_clock_select_t erefsVal)
{
    uint8_t frDivVal;
    uint16_t i;

    /* check if in FBI mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBI)
    {  
        return kMcgErrNotInFbiMode;                 /* MCG not in correct mode return fail code */
    }
  
    /* check external frequency is less than the maximum frequency */
    if  (crystalVal > kMcgConstant50000000) 
    {
        return kMcgErrOscEtalRange;
    }
 
    /* check crystal frequency is within spec. if crystal osc is being used */
    if (oscselVal == kMcgOscselOsc)
    {
        if (erefsVal)
        {
            /* return error if one of the available crystal options is not available */
            if ((crystalVal < kMcgConstant30000) ||
                ((crystalVal > kMcgConstant40000) && (crystalVal < kMcgConstant3000000)) ||
                (crystalVal > kMcgConstant32000000)) 
            {
                return kMcgErrOscXtalRange; /* - crystal frequency outside allowed range */
            } 

            /* config the hgo settings */
            CLOCK_HAL_SetHighGainOsc0Mode(baseAddr, hgoVal);
        }

        /* config the erefs0 settings */
        CLOCK_HAL_SetExternalRefSel0Mode(baseAddr, erefsVal);
    }

    /* 
     * the RANGE value is determined by the external frequency. Since the RANGE parameter 
     * affects the FRDIV divide value it still needs to be set correctly even if the 
     * oscillator is not being used
     */
    if (crystalVal <= kMcgConstant40000)
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelLow);
    }
    else if (crystalVal <= kMcgConstant8000000)
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelHigh);
    }
    else
    {
        CLOCK_HAL_SetRange0Mode(baseAddr, kMcgFreqRangeSelVeryHigh);
    }

    /* determine FRDIV based on reference clock frequency */
    /* since the external frequency has already been checked only the maximum frequency for each FRDIV
     * value needs to be compared here.
     */
    if (crystalVal <= kMcgConstant1250000) 
    {
        frDivVal = kMcgConstant0;
    }
    else if (crystalVal <= kMcgConstant2500000) 
    {
        frDivVal = kMcgConstant1;
    }
    else if (crystalVal <= kMcgConstant5000000) 
    {
        frDivVal = kMcgConstant2;
    }
    else if (crystalVal <= kMcgConstant10000000) 
    {
        frDivVal = kMcgConstant3;
    }
    else if (crystalVal <= kMcgConstant20000000) 
    {
        frDivVal = kMcgConstant4;
    }
    else 
    {
        frDivVal = kMcgConstant5;
    }

    /* Set LP bit to enable the FLL */
    CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelNormal);

    /*
     * Select external oscilator and Reference Divider and clear IREFS to start ext osc
     * If IRCLK is required it must be enabled outside of this driver, existing state will be maintained
     * CLKS=2, FRDIV=frdiv_val, IREFS=0
     */
    CLOCK_HAL_SetClksFrdivInternalRefSelect(baseAddr, kMcgClkSelExternal, frDivVal, kMcgInternalRefClkSrcExternal);

    /* if the external oscillator is used need to wait for OSCINIT to set */
    if ((oscselVal == kMcgOscselOsc) && (erefsVal))
    {
        for (i = 0 ; i < kMcgConstant10000 ; i++)
        {
            if (CLOCK_HAL_GetOscInit0(baseAddr))
            {
                break; /* jump out early if OSCINIT sets before loop finishes */
            }
        }

        if (!CLOCK_HAL_GetOscInit0(baseAddr))
        {
            /* check bit is really set and return with error if not set */
            return kMcgErrOscSetTimeout; 
        }
    }

    /* wait for Reference clock Status bit to clear */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (!CLOCK_HAL_GetInternalRefStatMode(baseAddr))
        {
            break; /* jump out early if IREFST clears before loop finishes */
        }
    }

    if (CLOCK_HAL_GetInternalRefStatMode(baseAddr))
    {
        /* check bit is really clear and return with error if not set */
        return kMcgErrIrefstClearTimeOut; 
    }

    /* Wait for clock status bits to show clock source is ext ref clk */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatExternalRef)
        {
            break; /* jump out early if CLKST shows EXT CLK slected before loop finishes */
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatExternalRef)
    {
        return kMcgErrClkst2; /* check EXT CLK is really selected and return with error if not */
    }

    /* 
     * Now in FBE  
     * It is recommended that the clock monitor is enabled when using an external clock as the clock source/reference.
     * It is enabled here but can be removed if this is not required.
     */
    CLOCK_HAL_SetClkMonitor0Cmd(baseAddr, true);
    
    return crystalVal; /* MCGOUT frequency equals external clock frequency */
}   /* CLOCK_HAL_SetFbiToFbeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbiToBlpiMode
 * Description  : Mode transition FBI to BLPI mode
 * This function transitions the MCG from FBI mode to BLPI mode.This is
 * achieved by setting the MCG_C2[LP] bit. 
 *
 * Parameters: ircFreq       - internal reference clock frequency value
 *             ircSelect     - slow or fast clock selection
 *                             0: slow, 1: fast
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbiToBlpiMode(uint32_t baseAddr, uint32_t ircFreq, mcg_internal_ref_clock_select_t ircSelect)
{
    uint8_t fcrDivVal;
  
    /* check if in FBI mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBI)
    {  
        return kMcgErrNotInFbiMode;                 /* MCG not in correct mode return fail code */
    }

    /* Set LP bit to disable the FLL and enter BLPI */
    CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelLowPower);
  
    /* Now in BLPI */
    if (ircSelect == kMcgInternalRefClkSelFast)
    {
        fcrDivVal = CLOCK_HAL_GetFastClkInternalRefDivider(baseAddr);
        return (ircFreq / fcrDivVal); /* MCGOUT frequency equals fast IRC frequency divided by 2 */
    }
    else
    {
        return ircFreq; /* MCGOUT frequency equals slow IRC frequency */
    }   
}   /* CLOCK_HAL_SetFbiToBlpiMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetBlpiToFbiMode
 * Description  : Mode transition BLPI to FBI mode
 * This function transitions the MCG from BLPI mode to FBI mode.This is
 * achieved by clearing the MCG_C2[LP] bit. 
 *
 * Parameters: ircFreq       - internal reference clock frequency value
 *             ircSelect     - slow or fast clock selection
 *                             0: slow, 1: fast
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetBlpiToFbiMode(uint32_t baseAddr, uint32_t ircFreq, uint8_t ircSelect)
{
    uint8_t fcrDivVal;

    /* check if in BLPI mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeBLPI)
    {
        return kMcgErrNotInBlpiMode;                /* MCG not in correct mode return fail code */
    }

    /* Clear LP bit to enable the FLL and enter FBI mode */
    CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelNormal);
  
    /* Now in FBI mode */
    if (ircSelect)
    {
        fcrDivVal = CLOCK_HAL_GetFastClkInternalRefDivider(baseAddr);
        return (ircFreq / fcrDivVal); /* MCGOUT frequency equals fast IRC frequency divided by 2 */
    }
    else
    {
        return ircFreq; /* MCGOUT frequency equals slow IRC frequency */
    }
}   /* CLOCK_HAL_SetBlpiToFbiMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbeToFeeMode
 * Description  : Mode transition FBE to FEE mode
 * This function transitions the MCG from FBE mode to FEE mode. 
 *
 * Parameters: crystalVal    - external reference clock frequency value
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbeToFeeMode(uint32_t baseAddr, uint32_t crystalVal)
{
    uint16_t i, fllRefFreq, frDivVal;
    uint32_t mcgOut;

    /* Check MCG is in FBE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBE)
    {
        return kMcgErrNotInFbeMode;                 /* return error code */
    }
  
    /* get curretn frdiv value */
    frDivVal = CLOCK_HAL_GetFllExternalRefDivider(baseAddr);

    /* The FLL ref clk divide value depends on FRDIV and the RANGE value */
    if (CLOCK_HAL_GetRange0Mode(baseAddr) > kMcgFreqRangeSelLow)
    {
        fllRefFreq = ((crystalVal) / (kMcgConstant32 << frDivVal));
    }
    else
    {
        fllRefFreq = ((crystalVal) / (kMcgConstant1 << frDivVal));
    }

    /* Check resulting FLL frequency  */
    /* FLL reference frequency calculated from ext ref freq and FRDIV */
    mcgOut = CLOCK_HAL_GetFllFrequency(baseAddr, fllRefFreq);      
    if (mcgOut < kMcgErrMax) 
    {
        return mcgOut;  /* If error code returned, return the code to calling function */
    }

    /* Clear CLKS field to switch CLKS mux to select FLL output */
    CLOCK_HAL_SetClkSrcMode(baseAddr, kMcgClkSelOut);

    /* Wait for clock status bits to show clock source is FLL */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll)
        {
            break; // jump out early if CLKST shows FLL selected before loop finishes
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatFll) 
    {
        return kMcgErrClkst0; // check FLL is really selected and return with error if not
    }
  
    /* Now in FEE mode */
    return mcgOut;
}   /* CLOCK_HAL_SetFbeToFeeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbeToFeiMode
 * Description  : Mode transition FBE to FEI mode
 * This function transitions the MCG from FBE mode to FEI mode. 
 *
 * Parameters: ircFreq       - internal reference clock frequency value (slow)
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbeToFeiMode(uint32_t baseAddr, uint32_t ircFreq)
{
    uint16_t i;
    uint32_t mcgOut;
  
    /* Check MCG is in FBE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBE)
    {
        return kMcgErrNotInFbeMode;                 /* return error code */
    }

    /* Check IRC frequency is within spec. */
    if ((ircFreq < kMcgConstant31250) || (ircFreq > kMcgConstant39063))
    {
        return kMcgErrIrcSlowRange;
    }
  
    /* Check resulting FLL frequency */
    mcgOut = CLOCK_HAL_GetFllFrequency(baseAddr, ircFreq); 
    if (mcgOut < kMcgErrMax) 
    {
        /* If error code returned, return the code to calling function */
        return mcgOut;
    } 

    /* 
     * Ensure clock monitor is disabled before switching to FEI otherwise 
     * a loss of clock will trigger. This assumes OSC0 is used as the external clock source.
     */
    CLOCK_HAL_SetClkMonitor0Cmd(baseAddr, false);
  
    // Move to FEI by setting CLKS to 0 and enabling the slow IRC as the FLL reference clock
    CLOCK_HAL_SetClksFrdivInternalRefSelect(baseAddr, kMcgClkSelOut, CLOCK_HAL_GetFllExternalRefDivider(baseAddr), kMcgInternalRefClkSrcSlow);
  
    /* wait for Reference clock to switch to internal reference */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal)
        {
            break; /* jump out early if IREFST sets before loop finishes */
        }
    }

    if (CLOCK_HAL_GetInternalRefStatMode(baseAddr) != kMcgInternalRefStatInternal)
    {
        /* check bit is really set and return with error if not set */
        return kMcgErrIrefstSetTimeout; 
    }
  
    /* Wait for clock status bits to show clock source is FLL output */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll)
        {
            /* jump out early if CLKST shows FLL output slected before loop finishes */
            break;
        }
    }

    /* check FLL output is really selected */
    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatFll)
    {
        /* return with error if not */
        return kMcgErrClkst0;
    }

    /* Now in FEI mode */
    return mcgOut;
}   /* CLOCK_HAL_SetFbeToFeiMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbeToFbiMode
 * Description  : Mode transition FBE to FBI mode
 * This function transitions the MCG from FBE mode to FBI mode. 
 *
 * Parameters: ircFreq       - internal reference clock frequency value
 *             ircSelect     - slow or fast clock selection
 *                             0: slow, 1: fast
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbeToFbiMode(uint32_t baseAddr, uint32_t ircFreq, mcg_internal_ref_clock_select_t ircSelect)
{
  uint8_t fcrDivVal;
  uint16_t i;
  
    /* Check MCG is in FBE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBE)
    {
        return kMcgErrNotInFbeMode;                 /* return error code */
    }

    /* Check that the irc frequency matches the selected IRC */
    if (!(ircSelect))
    {    
        if ((ircFreq < kMcgConstant31250) || (ircFreq > kMcgConstant39063)) 
        {
            return kMcgErrIrcSlowRange;
        } 
    }
    else
    {
        if ((ircFreq < kMcgConstant3000000) || (ircFreq > kMcgConstant5000000)) 
        {
            return kMcgErrIrcFastRange;
        } /* Fast IRC freq */
    }
  
    /* Select the required IRC */
    CLOCK_HAL_SetInternalRefClkSelMode(baseAddr, ircSelect);
  
    /* Make sure the clock monitor is disabled before switching modes otherwise it will trigger */
    CLOCK_HAL_SetClkMonitor0Cmd(baseAddr, false);
  
    /* Select the IRC as the CLKS mux selection */
    CLOCK_HAL_SetClksFrdivInternalRefSelect(baseAddr, kMcgClkSelInternal, CLOCK_HAL_GetFllExternalRefDivider(baseAddr), kMcgInternalRefClkSrcSlow); 
  
    /* wait until internal reference switches to requested irc. */
    if (ircSelect == kMcgInternalRefClkSelSlow)
    {
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetInternalRefClkStatMode(baseAddr) == kMcgInternalRefClkStatSlow)
            {
                break; /* jump out early if IRCST clears before loop finishes */
            }
        }
      if (CLOCK_HAL_GetInternalRefClkStatMode(baseAddr) != kMcgInternalRefClkStatSlow)
      {
          /* check bit is really clear and return with error if set */
          return kMcgErrIrcstClearTimeout; 
      }
    }
    else
    {
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetInternalRefClkStatMode(baseAddr) == kMcgInternalRefClkStatFast)
            {
                break; /* jump out early if IRCST sets before loop finishes */
            }
        }
        if (CLOCK_HAL_GetInternalRefClkStatMode(baseAddr) != kMcgInternalRefClkStatFast)
        {
            /* check bit is really set and return with error if not set */
            return kMcgErrIrefstSetTimeout1; 
        }
    }
 
    /* Wait for clock status bits to update */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatInternalRef)
        {
            break; /* jump out early if CLKST shows IRC slected before loop finishes */
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatInternalRef)
    {
        return kMcgErrClkst1; /* check IRC is really selected and return with error if not */
    }
 
    /* wait for Reference clock Status bit to set */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal)
        {
            break; /* jump out early if IREFST sets before loop finishes */
        }
    }

    if (CLOCK_HAL_GetInternalRefStatMode(baseAddr) != kMcgInternalRefStatInternal)
    {
        /* check bit is really set and return with error if not set */
        return kMcgErrIrefstSetTimeout; 
    }
  
    /* Now in FBI mode */
    if (ircSelect == kMcgInternalRefClkSelFast)
    {
        fcrDivVal = CLOCK_HAL_GetFastClkInternalRefDivider(baseAddr);

        return (ircFreq / fcrDivVal); /* MCGOUT frequency equals fast IRC frequency divided by 2 */
    }
    else
    {
        return ircFreq; /* MCGOUT frequency equals slow IRC frequency */
    }
}   /* CLOCK_HAL_SetFbeToFbiMode */

#if FSL_FEATURE_MCG_HAS_PLL  

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbeToPbeMode
 * Description  : Mode transition FBE to PBE mode
 * This function transitions the MCG from FBE mode to PBE mode. 
 * The function requires the desired OSC and PLL be passed in to it for compatibility 
 * with the future support of OSC/PLL selection
 * (This function presently only supports OSC0 as PLL source)
 * Parameters: crystalVal   - external clock frequency in Hz
 *             pllcsSelect  - 0 to select PLL0, non-zero to select PLL1.
 *             prdivVal     - value to divide the external clock source by to create 
 *                            the desired PLL reference clock frequency
 *             vdivVal      - value to multiply the PLL reference clock frequency by
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbeToPbeMode(uint32_t baseAddr, uint32_t crystalVal, mcg_pll_clk_select_t pllcsSelect, 
                           uint8_t prdivVal, uint8_t vdivVal)
{
    uint16_t i;
    uint32_t pllFreq;
  
    /* Check MCG is in FBE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBE)
    {
        return kMcgErrNotInFbeMode;                 /* return error code */
    }

    /* 
     * As the external frequency (osc0) has already been checked when FBE mode was enterred 
     * it is not checked here.
     */

    /* Check PLL divider settings are within spec.*/
    if ((prdivVal < 1) || (prdivVal > FSL_FEATURE_MCG_PLL_PRDIV_MAX))
    {
        return kMcgErrPllPrdidRange;
    }

    if ((vdivVal < FSL_FEATURE_MCG_PLL_VDIV_BASE) || (vdivVal > (FSL_FEATURE_MCG_PLL_VDIV_BASE + 31)))
    {
        return kMcgErrPllVdivRange;
    } 
  
    /* Check PLL reference clock frequency is within spec. */
    if (((crystalVal / prdivVal) < kMcgConstant8000000) || ((crystalVal / prdivVal) > kMcgConstant32000000))
    {
        return kMcgErrPllRefClkRange;
    }
       
    /* Check PLL output frequency is within spec. */
    pllFreq = (crystalVal / prdivVal) * vdivVal;
    if ((pllFreq < kMcgConstant180000000) || (pllFreq > kMcgConstant360000000))
    {
        return kMcgErrPllOutClkRange;
    }

#if FSL_FEATURE_MCG_HAS_PLL1
    /* set pllcsSelect */
    CLOCK_HAL_SetPllcs(pllcsSelect);

    if (pllcsSelect == kMcgPllcsSelectPll0)
#endif
    {
        /* 
         * Configure MCG_C5
         * If the PLL is to run in STOP mode then the PLLSTEN bit needs 
         * to be OR'ed in here or in user code.       
         */

        CLOCK_HAL_SetPllExternalRefDivider0(baseAddr, prdivVal - 1);

        /* 
         * Configure MCG_C6
         * The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk 
         * The clock monitor is not enabled here as it has likely been enabled previously and 
         * so the value of CME is not altered here.
         * The loss of lock interrupt can be enabled by seperate OR'ing in the LOLIE bit in MCG_C6
         */

        CLOCK_HAL_SetVoltCtrlOscDivider0(baseAddr, vdivVal - FSL_FEATURE_MCG_PLL_VDIV_BASE);
        CLOCK_HAL_SetPllSelMode(baseAddr, kMcgPllSelPllClkSel);

        // wait for PLLST status bit to set
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set  */
        if ((CLOCK_HAL_GetPllStatMode(baseAddr) != kMcgPllStatPllClkSel))
        {
            /* return with error if not set */
            return kMcgErrPllstSetTimeout;
        }

        /* Wait for LOCK bit to set */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetLock0Mode(baseAddr) ==  kMcgLockLocked)
            {
                /* jump out early if LOCK sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if ((CLOCK_HAL_GetLock0Mode(baseAddr) !=  kMcgLockLocked))
        {
            /* return with error if not set */
            return kMcgErrPllLockBit;
        }

#if FSL_FEATURE_MCG_USE_PLLREFSEL        
        /* wait for PLLCST status bit to clear */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllcst(baseAddr) == kMcgPllcsSelectPll0)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if (CLOCK_HAL_GetPllcst(baseAddr) != kMcgPllcsSelectPll0)
        {
            /* return with error if not set */
            return kMcgErrPllcst;
        }
#endif        
    }
#if FSL_FEATURE_MCG_HAS_PLL1
    else
    {
        /*
         * Configure MCG_C11
         * If the PLL is to run in STOP mode 
         * then the PLLSTEN bit needs to be OR'ed in here or in user code.       
         */
        CLOCK_HAL_SetPrdiv1(prdivVal - 1);

        /* 
         * Configure MCG_C12
         * The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk 
         * The clock monitor is not enabled here as it has likely been enabled previously
         * and so the value of CME is not altered here.
         * The loss of lock interrupt can be enabled by seperate OR'ing in the LOLIE bit 
         * in MCG_C12
         */

        CLOCK_HAL_SetVdiv1(vdivVal - FSL_FEATURE_MCG_PLL_VDIV_BASE);
        CLOCK_HAL_SetPllSelMode(kMcgPllSelPllClkSel);
  
        // wait for PLLST status bit to set
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set  */
        if ((CLOCK_HAL_GetPllStatMode(baseAddr) != kMcgPllStatPllClkSel))
        {
            /* return with error if not set */
            return kMcgErrPllstSetTimeout;
        }

        /* Wait for LOCK bit to set */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetLock1(baseAddr) ==  kMcgLockLocked)
            {
                /* jump out early if LOCK sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if ((CLOCK_HAL_GetLock1(baseAddr) !=  kMcgLockLocked))
        {
            /* return with error if not set */
            return kMcgErrPllLockBit;
        }
   
        /* wait for PLLCST status bit to clear */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllcst(baseAddr) == kMcgPllcsSelectPll1)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if (CLOCK_HAL_GetPllcst(baseAddr) != kMcgPllcsSelectPll1)
        {
            /* return with error if not set */
            return kMcgErrPllcst;
        }
    }
#endif /* PLL1 is selected */

    /* now in PBE */

    /* MCGOUT frequency equals external clock frequency */
    return crystalVal;
}   /* CLOCK_HAL_SetFbeToPbeMode */
#endif

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetFbeToBlpeMode
 * Description  : Mode transition FBE to BLPE mode
 * This function transitions the MCG from FBE mode to BLPE mode. 
 *
 * Parameters: crystalVal   - external clock frequency in Hz
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetFbeToBlpeMode(uint32_t baseAddr, uint32_t crystalVal)
{
    /* Check MCG is in FBE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeFBE)
    {
        return kMcgErrNotInFbeMode;                 /* return error code */
    }
 
    /* To move from FBE to BLPE the LP bit must be set */
    CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelLowPower);
 
    /* now in FBE mode */

    /* MCGOUT frequency equals external clock frequency */
    return crystalVal;
}   /* CLOCK_HAL_SetFbeToBlpeMode */

#if FSL_FEATURE_MCG_HAS_PLL  

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetPbeToFbeMode
 * Description  : Mode transition PBE to FBE mode
 * This function transitions the MCG from PBE mode to FBE mode. 
 *
 * Parameters: crystalVal   - external clock frequency in Hz
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetPbeToFbeMode(uint32_t baseAddr, uint32_t crystalVal)
{
    int16_t i;
    
    /* Check MCG is in PBE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModePBE)
    {
        return kMcgErrNotInPbeMode;                 /* return error code */
    }

    /* 
     * As we are running from the ext clock, by default the external clock settings are valid 
     * To move to FBE from PBE simply requires the switching of the PLLS mux to disable the PLL  
     */
    
    CLOCK_HAL_SetPllSelMode(baseAddr, kMcgPllSelFll);
  
    /* wait for PLLST status bit to set */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll)
        {
            /* jump out early if PLLST clears before loop finishes */
            break;
        }
    }

    /* check bit is really clear */
    if (CLOCK_HAL_GetPllStatMode(baseAddr) != kMcgPllStatFll)
    {
        /*  return with error if not clear */
        return kMcgErrPllstClearTimeout; 
    }

    /* Now in FBE mode   */

    /* MCGOUT frequency equals external clock frequency  */
    return crystalVal; 
}   /* CLOCK_HAL_SetPbeToFbeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetPbeToPeeMode
 * Description  : Mode transition PBE to PEE mode
 * This function transitions the MCG from PBE mode to PEE mode. 
 *
 * Parameters: crystalVal   - external clock frequency in Hz
 *             pllcsSelect  - PLLCS select setting
 *                            mcg_pll_clk_select_t is defined in fsl_mcg_hal.h
 *                            0: kMcgPllcsSelectPll0  PLL0 output clock is selected 
 *                            1: kMcgPllcsSelectPll1  PLL1 output clock is selected 
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetPbeToPeeMode(uint32_t baseAddr, uint32_t crystalVal, mcg_pll_clk_select_t pllcsSelect)
{
    uint8_t prDiv, vDiv;
    uint16_t i;
    uint32_t mcgOut;

    /* Check MCG is in PBE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModePBE)
    {
        return kMcgErrNotInPbeMode;                 /* return error code */
    }

    /* As the PLL settings have already been checked when PBE mode was enterred they are not checked here */

    /* Check the PLL state before transitioning to PEE mode */

#if FSL_FEATURE_MCG_HAS_PLL1
    /* Check the selected PLL state before transitioning to PEE mode */
    if (pllcsSelect == kMcgPllcsSelectPll1)
    {
        /* Check LOCK bit is set before transitioning MCG to PLL output */
        /* already checked in fbe_pbe but good practice to re-check before switch to use PLL */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetLock1(baseAddr) ==  kMcgLockLocked)
            {
                /* jump out early if LOCK sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if ((CLOCK_HAL_GetLock1(baseAddr) !=  kMcgLockLocked))
        {
            /* return with error if not set */
            return kMcgErrPllLockBit;
        }

        /* Use actual PLL settings to calculate PLL frequency */
        prDiv = (CLOCK_HAL_GetPrdiv1(baseAddr) + 1);
        vDiv = (CLOCK_HAL_GetVdiv1(baseAddr) + FSL_FEATURE_MCG_PLL_VDIV_BASE);
    }
    else
#endif
    {
        /* Check LOCK bit is set before transitioning MCG to PLL output */
        /* already checked in fbe_pbe but good practice to re-check before switch to use PLL */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetLock0Mode(baseAddr) ==  kMcgLockLocked)
            {
                /* jump out early if LOCK sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if ((CLOCK_HAL_GetLock0Mode(baseAddr) !=  kMcgLockLocked))
        {
            /* return with error if not set */
            return kMcgErrPllLockBit;
        }

        /* Use actual PLL settings to calculate PLL frequency */
        prDiv = (CLOCK_HAL_GetPllExternalRefDivider0(baseAddr) + 1);
        vDiv = (CLOCK_HAL_GetVoltCtrlOscDivider0(baseAddr) + FSL_FEATURE_MCG_PLL_VDIV_BASE);
    }

    /* clear CLKS to switch CLKS mux to select PLL as MCG_OUT */
    CLOCK_HAL_SetClkSrcMode(baseAddr, kMcgClkSelOut);

    /* Wait for clock status bits to update */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatPll)
        {
            break; /* jump out early if CLKST = 3 before loop finishes */
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatPll)
    {
        return kMcgErrClkst3; /* check CLKST is set correctly and return with error if not */
    }

    /* Now in PEE */

    /* MCGOUT equals PLL output frequency with any special divider */
    mcgOut = (crystalVal / prDiv) * vDiv;

    return mcgOut;
} /* CLOCK_HAL_SetPbeToPeeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetPbeToBlpeMode
 * Description  : Mode transition PBE to BLPE mode
 * This function transitions the MCG from PBE mode to BLPE mode. 
 *
 * Parameters: crystalVal   - external clock frequency in Hz
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetPbeToBlpeMode(uint32_t baseAddr, uint32_t crystalVal)
{
    /* Check MCG is in PBE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModePBE)
    {
        return kMcgErrNotInPbeMode;                 /* return error code */
    }
  
    /* To enter BLPE mode the LP bit must be set, disabling the PLL */
    CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelLowPower);
  
    /* Now in BLPE mode */
    return crystalVal;  
}   /* CLOCK_HAL_SetPbeToBlpeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetPeeToPbeMode
 * Description  : Mode transition PEE to PBE mode
 * This function transitions the MCG from PEE mode to PBE mode. 
 *
 * Parameters: crystalVal   - external clock frequency in Hz
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetPeeToPbeMode(uint32_t baseAddr, uint32_t crystalVal)
{
    uint16_t i;
  
    /* Check MCG is in PEE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModePEE)
    {
        return kMcgErrNotInPeeMode;                 /* return error code */
    } 
  
    /*
     * As we are running from the PLL by default the PLL and external clock settings are valid 
     * To move to PBE from PEE simply requires the switching of the CLKS mux to select the ext clock  
      */
    /* As CLKS is already 0 the CLKS value can simply be OR'ed into the register  */
    CLOCK_HAL_SetClkSrcMode(baseAddr, kMcgClkSelExternal);
  
    /* Wait for clock status bits to update */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatExternalRef)
        {
            break; /* jump out early if CLKST shows EXT CLK slected before loop finishes */
        }
    }

    if (CLOCK_HAL_GetClkStatMode(baseAddr) != kMcgClkStatExternalRef)
    {
        return kMcgErrClkst2; /* check EXT CLK is really selected and return with error if not */
    }

    /* Now in PBE mode */
    return crystalVal; /* MCGOUT frequency equals external clock frequency */
}   /* CLOCK_HAL_SetPeeToPbeMode */

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetBlpeToPbeMode
 * Description  : Mode transition BLPE to PBE mode
 * This function transitions the MCG from BLPE mode to PBE mode. 
 * The function requires the desired OSC and PLL be passed in to it for compatibility 
 * with the future support of OSC/PLL selection
 * (This function presently only supports OSC0 as PLL source)
 * Parameters: crystalVal   - external clock frequency in Hz
 *             pllcsSelect  - 0 to select PLL0, non-zero to select PLL1.
 *             prdivVal     - value to divide the external clock source by to create 
 *                            the desired PLL reference clock frequency
 *             vdivVal      - value to multiply the PLL reference clock frequency by
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetBlpeToPbeMode(uint32_t baseAddr, uint32_t crystalVal, mcg_pll_clk_select_t pllcsSelect, uint8_t prdivVal, uint8_t vdivVal)
{
    uint16_t i;
    uint32_t pllFreq;

    /* Check MCG is in BLPE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeBLPE)
    {
        return kMcgErrNotInBlpeMode;                                                       /* return error code */
    }
  
    /* 
     * As the external frequency (osc0) has already been checked when FBE mode was enterred 
     * it is not checked here.
     */

    /* Check PLL divider settings are within spec.*/
    if ((prdivVal < 1) || (prdivVal > FSL_FEATURE_MCG_PLL_PRDIV_MAX))
    {
        return kMcgErrPllPrdidRange;
    }

    if ((vdivVal < FSL_FEATURE_MCG_PLL_VDIV_BASE) || (vdivVal > (FSL_FEATURE_MCG_PLL_VDIV_BASE + 31)))
    {
        return kMcgErrPllVdivRange;
    } 
  
    /* Check PLL reference clock frequency is within spec. */
    if (((crystalVal / prdivVal) < kMcgConstant8000000) || ((crystalVal / prdivVal) > kMcgConstant32000000))
    {
        return kMcgErrPllRefClkRange;
    }
       
    /* Check PLL output frequency is within spec. */
    pllFreq = (crystalVal / prdivVal) * vdivVal;
    if ((pllFreq < kMcgConstant180000000) || (pllFreq > kMcgConstant360000000))
    {
        return kMcgErrPllOutClkRange;
    }

#if FSL_FEATURE_MCG_HAS_PLL1
    /* set pllcsSelect */
    CLOCK_HAL_SetPllcs(pllcsSelect);

    if (pllcsSelect == kMcgPllcsSelectPll0)
#endif
    {
        /* 
         * Configure MCG_C5
         * If the PLL is to run in STOP mode then the PLLSTEN bit needs 
         * to be OR'ed in here or in user code.       
         */

        CLOCK_HAL_SetPllExternalRefDivider0(baseAddr, prdivVal - 1);

        /* 
         * Configure MCG_C6
         * The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk 
         * The clock monitor is not enabled here as it has likely been enabled previously and 
         * so the value of CME is not altered here.
         * The loss of lock interrupt can be enabled by seperate OR'ing in the LOLIE bit in MCG_C6
         */

        CLOCK_HAL_SetVoltCtrlOscDivider0(baseAddr, vdivVal - FSL_FEATURE_MCG_PLL_VDIV_BASE);
        CLOCK_HAL_SetPllSelMode(baseAddr, kMcgPllSelPllClkSel);

        /* Set LP bit to enable the PLL */
        CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelNormal);

        // wait for PLLST status bit to set
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set  */
        if ((CLOCK_HAL_GetPllStatMode(baseAddr) != kMcgPllStatPllClkSel))
        {
            /* return with error if not set */
            return kMcgErrPllstSetTimeout;
        }

        /* Wait for LOCK bit to set */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetLock0Mode(baseAddr) ==  kMcgLockLocked)
            {
                /* jump out early if LOCK sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if ((CLOCK_HAL_GetLock0Mode(baseAddr) !=  kMcgLockLocked))
        {
            /* return with error if not set */
            return kMcgErrPllLockBit;
        }
    
#if FSL_FEATURE_MCG_USE_PLLREFSEL
        /* wait for PLLCST status bit to clear */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllcst(baseAddr) == kMcgPllcsSelectPll0)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if (CLOCK_HAL_GetPllcst(baseAddr) != kMcgPllcsSelectPll0)
        {
            /* return with error if not set */
            return kMcgErrPllcst;
        }
#endif        
    }
#if FSL_FEATURE_MCG_HAS_PLL1
    else
    {
        /*
         * Configure MCG_C11
         * If the PLL is to run in STOP mode 
         * then the PLLSTEN bit needs to be OR'ed in here or in user code.       
         */
        CLOCK_HAL_SetPrdiv1(prdivVal - 1);

        /* 
         * Configure MCG_C12
         * The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk 
         * The clock monitor is not enabled here as it has likely been enabled previously
         * and so the value of CME is not altered here.
         * The loss of lock interrupt can be enabled by seperate OR'ing in the LOLIE bit 
         * in MCG_C12
         */

        CLOCK_HAL_SetVdiv1(vdivVal - FSL_FEATURE_MCG_PLL_VDIV_BASE);
        CLOCK_HAL_SetPllSelMode(kMcgPllSelPllClkSel);

        /* Set LP bit to enable the PLL */
        CLOCK_HAL_SetLowPowerMode(kMcgLowPowerSelNormal);

        // wait for PLLST status bit to set
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set  */
        if ((CLOCK_HAL_GetPllStatMode(baseAddr) != kMcgPllStatPllClkSel))
        {
            /* return with error if not set */
            return kMcgErrPllstSetTimeout;
        }

        /* Wait for LOCK bit to set */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetLock1(baseAddr) ==  kMcgLockLocked)
            {
                /* jump out early if LOCK sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if ((CLOCK_HAL_GetLock1(baseAddr) !=  kMcgLockLocked))
        {
            /* return with error if not set */
            return kMcgErrPllLockBit;
        }
   
        /* wait for PLLCST status bit to clear */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllcst(baseAddr) == kMcgPllcsSelectPll1)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if (CLOCK_HAL_GetPllcst(baseAddr) != kMcgPllcsSelectPll1)
        {
            /* return with error if not set */
            return kMcgErrPllcst;
        }
    }
#endif /* PLL1 is selected */

    /* now in PBE */

    /* MCGOUT frequency equals external clock frequency */
    return crystalVal;
}   /* CLOCK_HAL_SetBlpeToPbeMode */
#endif

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_HAL_SetBlpeToFbeMode
 * Description  : Mode transition BLPE to FBE mode
 * This function transitions the MCG from BLPE mode to FBE mode. 
 *
 * Parameters: crystalVal    - external reference clock frequency value
 *
 * Return value : MCGCLKOUT frequency (Hz) or error code
 *END***********************************************************************************/
uint32_t CLOCK_HAL_SetBlpeToFbeMode(uint32_t baseAddr, uint32_t crystalVal)
{
#if FSL_FEATURE_MCG_HAS_PLL 	
    uint16_t i;
#endif	
  
    /* Check MCG is in BLPE mode */
    if (CLOCK_HAL_GetMcgMode(baseAddr) != kMcgModeBLPE)
    {
        return kMcgErrNotInBlpeMode;                /* return error code */
    }
 
    /* To move from BLPE to FBE the PLLS mux be set to select the FLL output*/
    /* and the LP bit must be cleared */
#if FSL_FEATURE_MCG_HAS_PLL      
    CLOCK_HAL_SetPllSelMode(baseAddr, kMcgPllSelFll);
#endif    
    CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelNormal);

#if FSL_FEATURE_MCG_HAS_PLL      
    /* wait for PLLST status bit to set */
    for (i = 0 ; i < kMcgConstant2000 ; i++)
    {
        if (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll)
        {
            /* jump out early if PLLST clears before loop finishes */
            break;
        }
    }

    /* check bit is really clear */
    if (CLOCK_HAL_GetPllStatMode(baseAddr) != kMcgPllStatFll)
    {
        /*  return with error if not clear */
        return kMcgErrPllstClearTimeout; 
    }
#endif
    /* now in FBE mode */

    /* MCGOUT frequency equals external clock frequency      */
    return crystalVal;
}   /* CLOCK_HAL_SetBlpeToFbeMode */
