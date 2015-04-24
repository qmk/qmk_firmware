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

#include "fsl_mcg_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetFllRefclk
 * Description   : Internal function to find the fll reference clock
 * This is an internal function to get the fll reference clock. The returned
 * value will be used for other APIs to calculate teh fll and other clock value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetFllRefClk(uint32_t baseAddr)
{
    uint32_t mcgffclk;
    uint8_t  divider;

    if (CLOCK_HAL_GetInternalRefSelMode(baseAddr) == kMcgInternalRefClkSrcExternal)
    {
        /* External reference clock is selected */
#if FSL_FEATURE_MCG_USE_OSCSEL          /* case 1: use oscsel for ffclk      */

        int32_t oscsel = CLOCK_HAL_GetOscselMode(baseAddr);
        if (oscsel == kMcgOscselOsc)
        {
#if FSL_FEATURE_MCG_HAS_OSC1
            /* System oscillator 0 drives MCG clock */
            mcgffclk = CPU_XTAL0_CLK_HZ;
#else
            /* System oscillator 0 drives MCG clock */
            mcgffclk = CPU_XTAL_CLK_HZ;
#endif
        }
        else if (oscsel == kMcgOscselRtc)
        {
            /* RTC 32 kHz oscillator drives MCG clock */
            mcgffclk = CPU_XTAL32k_CLK_HZ;
        }
#if FSL_FEATURE_MCG_HAS_IRC_48M         /* case 1.1: if IRC 48M exists*/
        else if (oscsel == kMcgOscselIrc)
        {
            /* IRC 48Mhz oscillator drives MCG clock */
            mcgffclk = CPU_INT_IRC_CLK_HZ;
        }
#endif
        else
        {
            mcgffclk = 0;
        }

#else                                   /* case 2: use default osc0*/

        /* System oscillator 0 drives MCG clock */
        mcgffclk = CPU_XTAL_CLK_HZ;

#endif

        divider = (uint8_t)(1u << CLOCK_HAL_GetFllExternalRefDivider(baseAddr));

        /* Calculate the divided FLL reference clock*/
        mcgffclk = (mcgffclk / divider);

        if ((CLOCK_HAL_GetRange0Mode(baseAddr) != kMcgFreqRangeSelLow) 
#if FSL_FEATURE_MCG_USE_OSCSEL          /* case 1: use oscsel for ffclk      */
            && (CLOCK_HAL_GetOscselMode(baseAddr) != kMcgOscselRtc))
#else
            )
#endif
        {
            /* If high range is enabled, additional 32 divider is active*/
            mcgffclk = (mcgffclk >> kMcgConstant5);
        }
    }
    else
    {
        /* The slow internal reference clock is selected */
        mcgffclk = CPU_INT_SLOW_CLK_HZ;
    }
    return mcgffclk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetFllclk
 * Description   : Get the current mcg fll clock
 * This function will return the mcgfllclk value in frequency(hz) based on
 * current mcg configurations and settings. Fll should be properly configured
 * in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetFllClk(uint32_t baseAddr)
{
    uint32_t mcgfllclk;
    mcg_dmx32_select_t dmx32;
    mcg_digital_controlled_osc_range_select_t drstDrs;

    mcgfllclk = CLOCK_HAL_GetFllRefClk(baseAddr);

    /* Select correct multiplier to calculate the MCG output clock  */
    dmx32 = CLOCK_HAL_GetDmx32(baseAddr);
    drstDrs = CLOCK_HAL_GetDigitalControlledOscRangeMode(baseAddr);

    switch (drstDrs)
    {
    case kMcgDigitalControlledOscRangeSelLow:         /* Low frequency range */
        switch (dmx32)
        {
        case kMcgDmx32Default:          /* DCO has a default range of 25% */
            mcgfllclk *= kMcgConstant640;
            break;
        case kMcgDmx32Fine:             /* DCO is fine-tuned for max freq 32.768 kHz */
            mcgfllclk *= kMcgConstant732;
            break;
        default:
            break;
        }
        break;
    case kMcgDigitalControlledOscRangeSelMid:         /* Mid frequency range*/
        switch (dmx32)
        {
        case kMcgDmx32Default:          /* DCO has a default range of 25% */
            mcgfllclk *= kMcgConstant1280;
            break;
        case kMcgDmx32Fine:             /* DCO is fine-tuned for max freq 32.768 kHz */
            mcgfllclk *= kMcgConstant1464;
            break;
        default:
            break;
        }
        break;
    case kMcgDigitalControlledOscRangeSelMidHigh:      /* Mid-High frequency range */
        switch (dmx32)
        {
        case kMcgDmx32Default:          /* DCO has a default range of 25% */
            mcgfllclk *= kMcgConstant1920;
            break;
        case kMcgDmx32Fine:             /* DCO is fine-tuned for max freq 32.768 kHz */
            mcgfllclk *= kMcgConstant2197;
            break;
        default:
            break;
        }
        break;
    case kMcgDigitalControlledOscRangeSelHigh:        /* High frequency range */
        switch (dmx32)
        {
        case kMcgDmx32Default:          /* DCO has a default range of 25% */
            mcgfllclk *= kMcgConstant2560;
            break;
        case kMcgDmx32Fine:             /* DCO is fine-tuned for max freq 32.768 kHz */
            mcgfllclk *= kMcgConstant2929;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return mcgfllclk;
}
#if FSL_FEATURE_MCG_HAS_PLL
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetPll0clk
 * Description   : Get the current mcg pll/pll0 clock
 * This function will return the mcgpllclk/mcgpll0 value in frequency(hz) based
 * on current mcg configurations and settings. PLL/PLL0 should be properly
 * configured in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetPll0Clk(uint32_t baseAddr)
{
    uint32_t mcgpll0clk;
    uint8_t  divider;

    /* PLL(0) output is selected*/
#if FSL_FEATURE_MCG_USE_PLLREFSEL /* case 1 use pllrefsel to select pll*/

    if (CLOCK_HAL_GetPllRefSel0Mode(baseAddr) != kMcgPllExternalRefClkSelOsc0)
    {
        /* OSC1 clock source used as an external reference clock */
        mcgpll0clk = CPU_XTAL1_CLK_HZ;
    }
    else
    {
        /* OSC0 clock source used as an external reference clock*/
        mcgpll0clk = CPU_XTAL0_CLK_HZ;
    }
#else
#if FSL_FEATURE_MCG_USE_OSCSEL              /* case 2: use oscsel for pll      */
    mcg_oscsel_select_t oscsel = CLOCK_HAL_GetOscselMode(baseAddr);
    if (oscsel == kMcgOscselOsc)        /* case 2.1: OSC0 */
    {
        /* System oscillator drives MCG clock*/
        mcgpll0clk = CPU_XTAL_CLK_HZ;
    }
    else if (oscsel == kMcgOscselRtc)   /* case 2.2: RTC */
    {
        /* RTC 32 kHz oscillator drives MCG clock*/
        mcgpll0clk = CPU_XTAL32k_CLK_HZ;
    }
#if FSL_FEATURE_MCG_HAS_IRC_48M
    else if (oscsel == kMcgOscselIrc)   /* case 2.3: IRC 48M */
    {
        /* IRC 48Mhz oscillator drives MCG clock*/
        mcgpll0clk = CPU_INT_IRC_CLK_HZ;
    }
    else
    {
        mcgpll0clk = 0;
    }
#endif
#else                                       /* case 3: use default osc0*/
    /* System oscillator drives MCG clock*/
    mcgpll0clk = CPU_XTAL_CLK_HZ;
#endif
#endif

    divider = (kMcgConstant1 + CLOCK_HAL_GetPllExternalRefDivider0(baseAddr));

    /* Calculate the PLL reference clock*/
    mcgpll0clk /= divider;
    divider = (CLOCK_HAL_GetVoltCtrlOscDivider0(baseAddr) + FSL_FEATURE_MCG_PLL_VDIV_BASE);

    /* Calculate the MCG output clock*/
    mcgpll0clk = (mcgpll0clk * divider);

    return mcgpll0clk;
}
#endif

#if FSL_FEATURE_MCG_HAS_PLL1
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetPll1Clk
 * Description   : Get the current mcg pll1 clock
 * This function will return the mcgpll1clk value in frequency(hz) based
 * on current mcg configurations and settings. PLL1 should be properly configured
 * in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetPll1Clk(uint32_t baseAddr)
{
    uint32_t mcgpll1clk;
    uint8_t  divider;

    if (CLOCK_HAL_GetPllRefSel1Mode(baseAddr) != kMcgPllExternalRefClkSelOsc0)
    {
        /* OSC1 clock source used as an external reference clock*/
        mcgpll1clk = CPU_XTAL1_CLK_HZ;
    }
    else
    {
        /* OSC0 clock source used as an external reference clock*/
        mcgpll1clk = CPU_XTAL0_CLK_HZ;
    }

    divider = (kMcgConstant1 + CLOCK_HAL_GetPllExternalRefDivider1(baseAddr));

    /* Calculate the PLL reference clock*/
    mcgpll1clk /= divider;
    divider = (CLOCK_HAL_GetVoltCtrlOscDivider1(baseAddr) + FSL_FEATURE_MCG_PLL_VDIV_BASE);

    /* Calculate the MCG output clock*/
    mcgpll1clk = ((mcgpll1clk * divider) >> kMcgConstant1); /* divided by 2*/
    return mcgpll1clk;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetIrclk
 * Description   : Get the current mcg ir clock
 * This function will return the mcgirclk value in frequency(hz) based
 * on current mcg configurations and settings. It will not check if the
 * mcgirclk is enabled or not, just calculate and return the value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetInternalRefClk(uint32_t baseAddr)
{
    int32_t mcgirclk;
    if (CLOCK_HAL_GetInternalRefClkSelMode(baseAddr) == kMcgInternalRefClkSelSlow)
    {
        /* Slow internal reference clock selected*/
        mcgirclk = CPU_INT_SLOW_CLK_HZ;
    }
    else
    {
        mcgirclk = CPU_INT_FAST_CLK_HZ / (1 << CLOCK_HAL_GetFastClkInternalRefDivider(baseAddr));
    }
    return mcgirclk;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetOutclk
 * Description   : Get the current mcg out clock
 * This function will return the mcgoutclk value in frequency(hz) based on
 * current mcg configurations and settings. The configuration should be
 * properly done in order to get the valid value.
 *
 *END**************************************************************************/
uint32_t CLOCK_HAL_GetOutClk(uint32_t baseAddr)
{
    /* Variable to store output clock frequency of the MCG module*/
    uint32_t mcgoutclk = 0;

    if (CLOCK_HAL_GetClkSrcMode(baseAddr) == kMcgClkSelOut)
    {
#if FSL_FEATURE_MCG_HAS_PLL
        /* Output of FLL or PLL is selected*/
        if (CLOCK_HAL_GetPllSelMode(baseAddr) == kMcgPllSelFll)
        {
            /* FLL is selected*/
            mcgoutclk = CLOCK_HAL_GetFllClk(baseAddr);
        }
        else
        {
            /* PLL is selected*/
#if FSL_FEATURE_MCG_HAS_PLL1
            if (CLOCK_HAL_GetPllClkSelMode(baseAddr) != kMcgPllClkSelPll0)
            {
                /* PLL1 output is selected*/
                mcgoutclk = CLOCK_HAL_GetPll1Clk(baseAddr);
            }
            else
            {
                mcgoutclk = CLOCK_HAL_GetPll0Clk(baseAddr);
            }
#else
            mcgoutclk = CLOCK_HAL_GetPll0Clk(baseAddr);
#endif // FSL_FEATURE_MCG_HAS_PLL1
        }
#else
        mcgoutclk = CLOCK_HAL_GetFllClk(baseAddr);
#endif // FSL_FEATURE_MCG_HAS_PLL
    }
    else if (CLOCK_HAL_GetClkSrcMode(baseAddr) == kMcgClkSelInternal)
    {
        /* Internal reference clock is selected*/
        mcgoutclk = CLOCK_HAL_GetInternalRefClk(baseAddr);
    }
    else if (CLOCK_HAL_GetClkSrcMode(baseAddr) == kMcgClkSelExternal)
    {
        /* External reference clock is selected*/

#if FSL_FEATURE_MCG_USE_OSCSEL              /* case 1: use oscsel for outclock      */

        uint32_t oscsel = CLOCK_HAL_GetOscselMode(baseAddr);
        if (oscsel == kMcgOscselOsc)
        {
#if FSL_FEATURE_MCG_HAS_OSC1
            /* System oscillator drives MCG clock*/
            mcgoutclk = CPU_XTAL0_CLK_HZ;
#else
            /* System oscillator drives MCG clock*/
            mcgoutclk = CPU_XTAL_CLK_HZ;
#endif
        }
        else if (oscsel == kMcgOscselRtc)
        {
            /* RTC 32 kHz oscillator drives MCG clock*/
            mcgoutclk = CPU_XTAL32k_CLK_HZ;
        }
#if FSL_FEATURE_MCG_HAS_IRC_48M             /* case 1.1: IRC 48M exists*/
        else if (oscsel == kMcgOscselIrc)
        {
            /* IRC 48Mhz oscillator drives MCG clock*/
            mcgoutclk = CPU_INT_IRC_CLK_HZ;
        }
        else
        {
            mcgoutclk = 0;
        }
#endif

#else                                       /* case 2: use default osc0*/
        /* System oscillator drives MCG clock*/
        mcgoutclk = CPU_XTAL_CLK_HZ;
#endif
    }
    else
    {
        /* Reserved value*/
        return mcgoutclk;
    }
    return mcgoutclk;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

