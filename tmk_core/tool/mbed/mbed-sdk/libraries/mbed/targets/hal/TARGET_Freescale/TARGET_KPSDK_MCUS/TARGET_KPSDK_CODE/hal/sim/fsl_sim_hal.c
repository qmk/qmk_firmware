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

#include "fsl_sim_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_SetSource
 * Description   : Set clock source setting 
 * This function will set the settings for specified clock source. Each clock 
 * source has its clock selection settings. Refer to reference manual for 
 * details of settings for each clock source. Refer to clock_source_names_t 
 * for clock sources.
 * 
 *END**************************************************************************/
sim_hal_status_t CLOCK_HAL_SetSource(uint32_t baseAddr,
                                     clock_source_names_t clockSource,
                                     uint8_t setting)
{
    sim_hal_status_t status = kSimHalSuccess;
    assert(clockSource < kClockSourceMax);

    switch (clockSource)
    {
#if FSL_FEATURE_SIM_OPT_HAS_NFCSRC
    case kClockNfcSrc:                   /* NFCSRC*/
        BW_SIM_SOPT2_NFCSRC(baseAddr, setting);
        break;
    case kClockNfcSel:                   /* NFC_CLKSEL*/
        BW_SIM_SOPT2_NFC_CLKSEL(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC
    case kClockEsdhcSrc:                 /* ESDHCSRC*/
        BW_SIM_SOPT2_ESDHCSRC(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_SDHCSRC
    case kClockSdhcSrc:                  /* SDHCSRC*/
        BW_SIM_SOPT2_SDHCSRC(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_LCDCSRC
    case kClockLcdcSrc:                  /* LCDCSRC*/
        BW_SIM_SOPT2_LCDCSRC(baseAddr, setting);
        break;
    case kClockLcdcSel:                  /* LCDC_CLKSEL*/
        BW_SIM_SOPT2_LCDC_CLKSEL(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_TIMESRC
    case kClockTimeSrc:                  /* TIMESRC*/
        BW_SIM_SOPT2_TIMESRC(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_RMIISRC
    case kClockRmiiSrc:                  /* RMIISRC*/
        BW_SIM_SOPT2_RMIISRC(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_USBSRC
    case kClockUsbSrc:                    /* USBSRC*/
        BW_SIM_SOPT2_USBSRC(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_USBFSRC
    case kClockUsbfSrc:                   /* USBFSRC*/
        BW_SIM_SOPT2_USBFSRC(baseAddr, setting);
        break;
    case kClockUsbfSel:                  /* USBF_CLKSEL*/
        BW_SIM_SOPT2_USBF_CLKSEL(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_USBHSRC
    case kClockUsbhSrc:                  /* USBHSRC*/
        BW_SIM_SOPT2_USBHSRC(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_UART0SRC
    case kClockUart0Src:                 /* UART0SRC*/
        BW_SIM_SOPT2_UART0SRC(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_TPMSRC
    case kClockTpmSrc:                   /* TPMSRC*/
        BW_SIM_SOPT2_TPMSRC(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC
    case kClockLpuartSrc:                /* LPUARTSRC*/
        BW_SIM_SOPT2_LPUARTSRC(baseAddr, setting);
        break;
#endif

    case kClockOsc32kSel:                /* OSC32KSEL*/
        BW_SIM_SOPT1_OSC32KSEL(baseAddr, setting);
        break;

    case kClockPllfllSel:                /* PLLFLLSEL*/
        BW_SIM_SOPT2_PLLFLLSEL(baseAddr, setting);
        break;

#if FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL
    case kClockTraceSel:                 /* TRACE_CLKSEL*/
        BW_SIM_SOPT2_TRACECLKSEL(baseAddr, setting);
        break;
#endif

    case kClockClkoutSel:                /* CLKOUTSEL*/
        BW_SIM_SOPT2_CLKOUTSEL(baseAddr, setting);
        break;

#if FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION
    case kClockRtcClkoutSel:                /* RTCCLKOUTSEL*/
        BW_SIM_SOPT2_RTCCLKOUTSEL(baseAddr, setting);
        break;
#endif
        
    default:
        status = kSimHalNoSuchClockSrc;
        break;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetSource
 * Description   : Get clock source setting
 * This function will get the settings for specified clock source. Each clock 
 * source has its clock selection settings. Refer to reference manual for 
 * details of settings for each clock source. Refer to clock_source_names_t
 * for clock sources.
 * 
 *END**************************************************************************/
sim_hal_status_t CLOCK_HAL_GetSource(uint32_t baseAddr,
                                     clock_source_names_t clockSource,
                                     uint8_t *setting)
{
    sim_hal_status_t status = kSimHalSuccess;
    assert(clockSource < kClockSourceMax);

    switch (clockSource)
    {
#if FSL_FEATURE_SIM_OPT_HAS_NFCSRC
    case kClockNfcSrc:                   /* NFCSRC*/
        *setting = BR_SIM_SOPT2_NFCSRC(baseAddr);
        break;
    case kClockNfcSel:                   /* NFC_CLKSEL*/
        *setting = BR_SIM_SOPT2_NFC_CLKSEL(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC
    case kClockEsdhcSrc:                 /* ESDHCSRC*/
        *setting = BR_SIM_SOPT2_ESDHCSRC(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_SDHCSRC
    case kClockSdhcSrc:                  /* SDHCSRC*/
        *setting = BR_SIM_SOPT2_SDHCSRC(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_LCDCSRC
    case kClockLcdcSrc:                  /* LCDCSRC*/
        *setting = BR_SIM_SOPT2_LCDCSRC(baseAddr);
        break;
    case kClockLcdcSel:                  /* LCDC_CLKSEL*/
        *setting = BR_SIM_SOPT2_LCDC_CLKSEL(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_TIMESRC
    case kClockTimeSrc:                  /* TIMESRC*/
        *setting = BR_SIM_SOPT2_TIMESRC(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_RMIISRC
    case kClockRmiiSrc:                  /* RMIISRC*/
        *setting = BR_SIM_SOPT2_RMIISRC(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_USBSRC
    case kClockUsbSrc:                    /* USBSRC*/
        *setting = BR_SIM_SOPT2_USBSRC(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_USBFSRC
    case kClockUsbfSrc:                   /* USBFSRC*/
        *setting = BR_SIM_SOPT2_USBFSRC(baseAddr);
        break;
    case kClockUsbfSel:                  /* USBF_CLKSEL*/
        *setting = BR_SIM_SOPT2_USBF_CLKSEL(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_USBHSRC
    case kClockUsbhSrc:                  /* USBHSRC*/
        *setting = BR_SIM_SOPT2_USBHSRC(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_UART0SRC
    case kClockUart0Src:                 /* UART0SRC*/
        *setting = BR_SIM_SOPT2_UART0SRC(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_TPMSRC
    case kClockTpmSrc:                   /* TPMSRC*/
        *setting = BR_SIM_SOPT2_TPMSRC(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC
    case kClockLpuartSrc:                /* LPUARTSRC*/
        *setting = BR_SIM_SOPT2_LPUARTSRC(baseAddr);
        break;
#endif

    case kClockOsc32kSel:                /* OSC32KSEL*/
        *setting = BR_SIM_SOPT1_OSC32KSEL(baseAddr);
        break;

    case kClockPllfllSel:                /* PLLFLLSEL*/
        *setting = BR_SIM_SOPT2_PLLFLLSEL(baseAddr);
        break;

#if FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL
    case kClockTraceSel:                 /* TRACE_CLKSEL*/
        *setting = BR_SIM_SOPT2_TRACECLKSEL(baseAddr);
        break;
#endif

    case kClockClkoutSel:                /* CLKOUTSEL */
        *setting = BR_SIM_SOPT2_CLKOUTSEL(baseAddr);
        break;

#if FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION
    case kClockRtcClkoutSel:                /* RTCCLKOUTSEL */
        *setting = BR_SIM_SOPT2_RTCCLKOUTSEL(baseAddr);
        break;
#endif
        
    default:
        status = kSimHalNoSuchClockSrc;
        break;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_SetDivider
 * Description   : Set clock divider setting
 * This function will set the setting for specified clock divider. Refer to 
 * reference manual for supported clock divider and value range. Refer to 
 * clock_divider_names_t for dividers.
 * 
 *END**************************************************************************/
sim_hal_status_t CLOCK_HAL_SetDivider(uint32_t baseAddr,
                                      clock_divider_names_t clockDivider, 
                                      uint32_t setting)
{
    sim_hal_status_t status = kSimHalSuccess;
    assert(clockDivider < kClockDividerMax);

    switch (clockDivider)
    {
    case kClockDividerOutdiv1:           /* OUTDIV1*/
        BW_SIM_CLKDIV1_OUTDIV1(baseAddr, setting);
        break;

#if FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2
    case kClockDividerOutdiv2:           /* OUTDIV2*/
        BW_SIM_CLKDIV1_OUTDIV2(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3
    case kClockDividerOutdiv3:           /* OUTDIV3*/
        BW_SIM_CLKDIV1_OUTDIV3(baseAddr, setting);
        break;
#endif

    case kClockDividerOutdiv4:           /* OUTDIV4*/
        BW_SIM_CLKDIV1_OUTDIV4(baseAddr, setting);
        break;

#if FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV
    case kClockDividerUsbFrac:           /* USBFRAC*/
        BW_SIM_CLKDIV2_USBFRAC(baseAddr, setting);
        break;
    case kClockDividerUsbDiv:            /* USBDIV*/
        BW_SIM_CLKDIV2_USBDIV(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV
    case kClockDividerUsbfsFrac:         /* USBFSFRAC*/
        BW_SIM_CLKDIV2_USBFSFRAC(baseAddr, setting);
        break;
    case kClockDividerUsbfsDiv:          /* USBFSDIV*/
        BW_SIM_CLKDIV2_USBFSDIV(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV
    case kClockDividerUsbhsFrac:         /* USBHSFRAC*/
        BW_SIM_CLKDIV2_USBHSFRAC(baseAddr, setting);
        break;
    case kClockDividerUsbhsDiv:          /* USBHSDIV*/
        BW_SIM_CLKDIV2_USBHSDIV(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_LCDCSRC
    case kClockDividerLcdcFrac:          /* LCDCFRAC*/
        BW_SIM_CLKDIV3_LCDCFRAC(baseAddr, setting);
        break;
    case kClockDividerLcdcDiv:           /* LCDCDIV*/
        BW_SIM_CLKDIV3_LCDCDIV(baseAddr, setting);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_NFCSRC
    case kClockDividerNfcFrac:           /* NFCFRAC*/
        BW_SIM_CLKDIV4_NFCFRAC(baseAddr, setting);
        break;
    case kClockDividerNfcDiv:            /* NFCDIV*/
        BW_SIM_CLKDIV4_NFCDIV(baseAddr, setting);
        break;
#endif

    case kClockDividerSpecial1:          /* special divider 1   */
        break;

    default:
        status = kSimHalNoSuchDivider;
        break;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_SetOutDividers
 * Description   : Set all clock out dividers setting at the same time
 * This function will set the setting for all clock out dividers. Refer to 
 * reference manual for supported clock divider and value range. Refer to 
 * clock_divider_names_t for dividers.
 * 
 *END**************************************************************************/
void CLOCK_HAL_SetOutDividers(uint32_t baseAddr, uint32_t outdiv1, uint32_t outdiv2, 
                                 uint32_t outdiv3, uint32_t outdiv4)
{
    uint32_t clkdiv1 = 0;
    
    clkdiv1 |= BF_SIM_CLKDIV1_OUTDIV1(outdiv1);
#if FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2
    clkdiv1 |= BF_SIM_CLKDIV1_OUTDIV2(outdiv2);
#endif
#if FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3
    clkdiv1 |= BF_SIM_CLKDIV1_OUTDIV3(outdiv3);
#endif
    clkdiv1 |= BF_SIM_CLKDIV1_OUTDIV4(outdiv4);
    
    HW_SIM_CLKDIV1_WR(baseAddr, clkdiv1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_HAL_GetDivider
 * Description   : Get clock divider setting
 * This function will get the setting for specified clock divider. Refer to 
 * reference manual for supported clock divider and value range. Refer to 
 * clock_divider_names_t for dividers.
 * 
 *END**************************************************************************/
sim_hal_status_t CLOCK_HAL_GetDivider(uint32_t baseAddr,
                                      clock_divider_names_t clockDivider,
                                      uint32_t *setting)
{
    sim_hal_status_t status = kSimHalSuccess;
    assert(clockDivider < kClockDividerMax);

    *setting = 0;

    switch (clockDivider)
    {
    case kClockDividerOutdiv1:           /* OUTDIV1*/
        *setting = BR_SIM_CLKDIV1_OUTDIV1(baseAddr);
        break;

#if FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2
    case kClockDividerOutdiv2:           /* OUTDIV2*/
        *setting = BR_SIM_CLKDIV1_OUTDIV2(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3
    case kClockDividerOutdiv3:           /* OUTDIV3*/
        *setting = BR_SIM_CLKDIV1_OUTDIV3(baseAddr);
        break;
#endif

    case kClockDividerOutdiv4:           /* OUTDIV4*/
        *setting = BR_SIM_CLKDIV1_OUTDIV4(baseAddr);
        break;

#if FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV
    case kClockDividerUsbFrac:           /* USBFRAC*/
        *setting = BR_SIM_CLKDIV2_USBFRAC(baseAddr);
        break;
    case kClockDividerUsbDiv:            /* USBDIV*/
        *setting = BR_SIM_CLKDIV2_USBDIV(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV
    case kClockDividerUsbfsFrac:         /* USBFSFRAC*/
        *setting = BR_SIM_CLKDIV2_USBFSFRAC(baseAddr);
        break;
    case kClockDividerUsbfsDiv:          /* USBFSDIV*/
        *setting = BR_SIM_CLKDIV2_USBFSDIV(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV
    case kClockDividerUsbhsFrac:         /* USBHSFRAC*/
        *setting = BR_SIM_CLKDIV2_USBHSFRAC(baseAddr);
        break;
    case kClockDividerUsbhsDiv:          /* USBHSDIV*/
        *setting = BR_SIM_CLKDIV2_USBHSDIV(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_LCDCSRC
    case kClockDividerLcdcFrac:          /* LCDCFRAC*/
        *setting = BR_SIM_CLKDIV3_LCDCFRAC(baseAddr);
        break;
    case kClockDividerLcdcDiv:           /* LCDCDIV*/
        *setting = BR_SIM_CLKDIV3_LCDCDIV(baseAddr);
        break;
#endif

#if FSL_FEATURE_SIM_OPT_HAS_NFCSRC
    case kClockDividerNfcFrac:           /* NFCFRAC*/
        *setting = BR_SIM_CLKDIV4_NFCFRAC(baseAddr);
        break;
    case kClockDividerNfcDiv:            /* NFCDIV*/
        *setting = BR_SIM_CLKDIV4_NFCDIV(baseAddr);
        break;
#endif

    case kClockDividerSpecial1:          /* special divider 1    */
        *setting = 1;                   
        break;

    default:
        status = kSimHalNoSuchDivider;
        break;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetAdcAlternativeTriggerCmd
 * Description   : Set ADCx alternate trigger enable setting
 * This function will enable/disable alternative conversion triggers for ADCx. 
 * 
 *END**************************************************************************/
void SIM_HAL_SetAdcAlternativeTriggerCmd(uint32_t baseAddr, uint8_t instance, bool enable)
{
    assert(instance < HW_ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        BW_SIM_SOPT7_ADC0ALTTRGEN(baseAddr, enable ? 1 : 0);
        break;
#if (HW_ADC_INSTANCE_COUNT > 1)
    case 1:
        BW_SIM_SOPT7_ADC1ALTTRGEN(baseAddr, enable ? 1 : 0);
        break;
#if (HW_ADC_INSTANCE_COUNT > 2)
    case 2:
        BW_SIM_SOPT7_ADC2ALTTRGEN(baseAddr, enable ? 1 : 0);
        break;
    case 3:
        BW_SIM_SOPT7_ADC3ALTTRGEN(baseAddr, enable ? 1 : 0);
        break;
#endif
#endif
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcAlternativeTriggerCmd
 * Description   : Get ADCx alternate trigger enable settingg
 * This function will get ADCx alternate trigger enable setting. 
 * 
 *END**************************************************************************/
bool SIM_HAL_GetAdcAlternativeTriggerCmd(uint32_t baseAddr, uint8_t instance)
{
    bool retValue = false;

    assert(instance < HW_ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = BR_SIM_SOPT7_ADC0ALTTRGEN(baseAddr);
        break;
#if (HW_ADC_INSTANCE_COUNT > 1)
    case 1:
        retValue = BR_SIM_SOPT7_ADC1ALTTRGEN(baseAddr);
        break;
#if (HW_ADC_INSTANCE_COUNT > 2)
    case 2:
        retValue = BR_SIM_SOPT7_ADC2ALTTRGEN(baseAddr);
        break;
    case 3:
        retValue = BR_SIM_SOPT7_ADC3ALTTRGEN(baseAddr);
        break;
#endif
#endif
    default:
        retValue = false;
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetAdcPreTriggerMode
 * Description   : Set ADCx pre-trigger select setting
 * This function will select the ADCx pre-trigger source when alternative
 * triggers are enabled through ADCxALTTRGEN
 * 
 *END**************************************************************************/
void SIM_HAL_SetAdcPreTriggerMode(uint32_t baseAddr, uint8_t instance, sim_pretrgsel_t select)
{
    assert(instance < HW_ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        BW_SIM_SOPT7_ADC0PRETRGSEL(baseAddr, select);
        break;
#if (HW_ADC_INSTANCE_COUNT > 1)
    case 1:
        BW_SIM_SOPT7_ADC1PRETRGSEL(baseAddr, select);
        break;
#if (HW_ADC_INSTANCE_COUNT > 2)
    case 2:
        BW_SIM_SOPT7_ADC2PRETRGSEL(baseAddr, select);
        break;
    case 3:
        BW_SIM_SOPT7_ADC3PRETRGSEL(baseAddr, select);
        break;
#endif
#endif
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcPreTriggerMode
 * Description   : Get ADCx pre-trigger select setting
 * This function will get ADCx pre-trigger select setting.
 * 
 *END**************************************************************************/
sim_pretrgsel_t SIM_HAL_GetAdcPreTriggerMode(uint32_t baseAddr, uint8_t instance)
{
    sim_pretrgsel_t retValue = (sim_pretrgsel_t)0;

    assert(instance < HW_ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_pretrgsel_t)BR_SIM_SOPT7_ADC0PRETRGSEL(baseAddr);
        break;
#if (HW_ADC_INSTANCE_COUNT > 1)
    case 1:
        retValue = (sim_pretrgsel_t)BR_SIM_SOPT7_ADC1PRETRGSEL(baseAddr);
        break;
#if (HW_ADC_INSTANCE_COUNT > 2)
    case 2:
        retValue = (sim_pretrgsel_t)BR_SIM_SOPT7_ADC2PRETRGSEL(baseAddr);
        break;
    case 3:
        retValue = (sim_pretrgsel_t)BR_SIM_SOPT7_ADC3PRETRGSEL(baseAddr);
        break;
#endif
#endif
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetAdcTriggerMode
 * Description   : Set ADCx trigger select setting
 * This function will select the ADCx trigger source when alternative triggers
 * are enabled through ADCxALTTRGEN
 * 
 *END**************************************************************************/
void SIM_HAL_SetAdcTriggerMode(uint32_t baseAddr, uint8_t instance, sim_trgsel_t select)
{
    assert(instance < HW_ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        BW_SIM_SOPT7_ADC0TRGSEL(baseAddr, select);
        break;
#if (HW_ADC_INSTANCE_COUNT > 1)
    case 1:
        BW_SIM_SOPT7_ADC1TRGSEL(baseAddr, select);
        break;
#if (HW_ADC_INSTANCE_COUNT > 2)
    case 2:
        BW_SIM_SOPT7_ADC2TRGSEL(baseAddr, select);
        break;
    case 3:
        BW_SIM_SOPT7_ADC3TRGSEL(baseAddr, select);
        break;
#endif
#endif
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcTriggerMode
 * Description   : Get ADCx trigger select setting 
 * This function will get ADCx trigger select setting.
 * 
 *END**************************************************************************/
sim_pretrgsel_t SIM_HAL_GetAdcTriggerMode(uint32_t baseAddr, uint8_t instance)
{
    sim_pretrgsel_t retValue =(sim_pretrgsel_t)0;

    assert(instance < HW_ADC_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_pretrgsel_t)BR_SIM_SOPT7_ADC0TRGSEL(baseAddr);
        break;
#if (HW_ADC_INSTANCE_COUNT > 1)
    case 1:
        retValue = (sim_pretrgsel_t)BR_SIM_SOPT7_ADC1TRGSEL(baseAddr);
        break;
#if (HW_ADC_INSTANCE_COUNT > 2)
    case 2:
        retValue = (sim_pretrgsel_t)BR_SIM_SOPT7_ADC2TRGSEL(baseAddr);
        break;
    case 3:
        retValue = (sim_pretrgsel_t)BR_SIM_SOPT7_ADC3TRGSEL(baseAddr);
        break;
#endif
#endif
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetUartRxSrcMode
 * Description   : Set UARTx receive data source select setting 
 * This function will select the source for the UART1 receive data.
 * 
 *END**************************************************************************/
void SIM_HAL_SetUartRxSrcMode(uint32_t baseAddr, uint8_t instance, sim_uart_rxsrc_t select)
{
    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        BW_SIM_SOPT5_UART0RXSRC(baseAddr, select);
        break;
    case 1:
        BW_SIM_SOPT5_UART1RXSRC(baseAddr, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetAdcPreTriggerMode
 * Description   : Get UARTx receive data source select setting 
 * This function will get UARTx receive data source select setting.
 * 
 *END**************************************************************************/
sim_uart_rxsrc_t SIM_HAL_GetUartRxSrcMode(uint32_t baseAddr, uint8_t instance)
{
    sim_uart_rxsrc_t retValue = (sim_uart_rxsrc_t)0;

    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_uart_rxsrc_t)BR_SIM_SOPT5_UART0RXSRC(baseAddr);
        break;
    case 1:
        retValue = (sim_uart_rxsrc_t)BR_SIM_SOPT5_UART1RXSRC(baseAddr);
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetUartTxSrcMode
 * Description   : Set UARTx transmit data source select setting 
 * This function will select the source for the UARTx transmit data.
 * 
 *END**************************************************************************/
void SIM_HAL_SetUartTxSrcMode(uint32_t baseAddr, uint8_t instance, sim_uart_txsrc_t select)
{
    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        BW_SIM_SOPT5_UART0TXSRC(baseAddr, select);
        break;
    case 1:
        BW_SIM_SOPT5_UART1TXSRC(baseAddr, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUartTxSrcMode
 * Description   : Get UARTx transmit data source select setting 
 * This function will get UARTx transmit data source select setting.
 * 
 *END**************************************************************************/
sim_uart_txsrc_t SIM_HAL_GetUartTxSrcMode(uint32_t baseAddr, uint8_t instance)
{
    sim_uart_txsrc_t retValue =(sim_uart_txsrc_t)0;

    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_uart_txsrc_t)BR_SIM_SOPT5_UART0TXSRC(baseAddr);
        break;
    case 1:
        retValue = (sim_uart_txsrc_t)BR_SIM_SOPT5_UART1TXSRC(baseAddr);
        break;
    default:
        break;
    }

    return retValue;
}

#if FSL_FEATURE_SIM_OPT_HAS_ODE
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetUartOpenDrainCmd
 * Description   : Set UARTx Open Drain Enable setting 
 * This function will enable/disable the UARTx Open Drain.
 * 
 *END**************************************************************************/
void SIM_HAL_SetUartOpenDrainCmd(uint32_t baseAddr, uint8_t instance, bool enable)
{
    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        BW_SIM_SOPT5_UART0ODE(baseAddr, enable ? 1 : 0);
        break;
    case 1:
        BW_SIM_SOPT5_UART1ODE(baseAddr, enable ? 1 : 0);
        break;
    case 2:
        BW_SIM_SOPT5_UART2ODE(baseAddr, enable ? 1 : 0);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetUartOpenDrainCmd
 * Description   : Get UARTx Open Drain Enable setting 
 * This function will get UARTx Open Drain Enable setting.
 * 
 *END**************************************************************************/
bool SIM_HAL_GetUartOpenDrainCmd(uint32_t baseAddr, uint8_t instance)
{
    bool retValue = false;

    assert(instance < FSL_FEATURE_SIM_OPT_UART_COUNT);

    switch (instance)
    {
    case 0:
        retValue = BR_SIM_SOPT5_UART0ODE(baseAddr);
        break;
    case 1:
        retValue = BR_SIM_SOPT5_UART1ODE(baseAddr);
        break;
    case 2:
        retValue = BR_SIM_SOPT5_UART2ODE(baseAddr);
        break;
    default:
        break;
    }

    return retValue;
}
#endif

#if FSL_FEATURE_SIM_OPT_HAS_FTM
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetFtmTriggerSrcMode
 * Description   : Set FlexTimer x hardware trigger y source select setting 
 * This function will select the source of FTMx hardware trigger y.
 * 
 *END**************************************************************************/
void SIM_HAL_SetFtmTriggerSrcMode(uint32_t baseAddr,
                                  uint8_t  instance,
                                  uint8_t  trigger,
                                  sim_ftm_trg_src_t select)
{
    assert (instance < HW_FTM_INSTANCE_COUNT);
    assert (trigger < FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT);

    switch (instance)
    {
#if FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER
    case 0:
        switch (trigger)
        {
        case 0:
            BW_SIM_SOPT4_FTM0TRG0SRC(baseAddr, select);
            break;
        case 1:
            BW_SIM_SOPT4_FTM0TRG1SRC(baseAddr, select);
            break;
        default:
            break;
        }
        break;
#endif
#if FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER
    case 3:
        switch (trigger)
        {
        case 0:
            BW_SIM_SOPT4_FTM3TRG0SRC(baseAddr, select);
            break;
        case 1:
            BW_SIM_SOPT4_FTM3TRG1SRC(baseAddr, select);
            break;
        default:
            break;
        }
        break;
#endif
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmTriggerSrcMode
 * Description   : Get FlexTimer x hardware trigger y source select setting
 * This function will get FlexTimer x hardware trigger y source select setting.
 * 
 *END**************************************************************************/
sim_ftm_trg_src_t SIM_HAL_GetFtmTriggerSrcMode(uint32_t baseAddr, uint8_t instance, uint8_t trigger)
{
    sim_ftm_trg_src_t retValue = (sim_ftm_trg_src_t)0;

    assert (instance < HW_FTM_INSTANCE_COUNT);
    assert (trigger < FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT);

    switch (instance)
    {
#if FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER
    case 0:
        switch (trigger)
        {
        case 0:
            retValue = (sim_ftm_trg_src_t)BR_SIM_SOPT4_FTM0TRG0SRC(baseAddr);
            break;
        case 1:
            retValue = (sim_ftm_trg_src_t)BR_SIM_SOPT4_FTM0TRG1SRC(baseAddr);
            break;
        default:
            break;
        }
        break;
#endif
#if FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER
    case 3:
        switch (trigger)
        {
        case 0:
            retValue = (sim_ftm_trg_src_t)BR_SIM_SOPT4_FTM3TRG0SRC(baseAddr);
            break;
        case 1:
            retValue = (sim_ftm_trg_src_t)BR_SIM_SOPT4_FTM3TRG1SRC(baseAddr);
            break;
        default:
            break;
        }
        break;
#endif
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetFtmExternalClkPinMode
 * Description   : Set FlexTimer x external clock pin select setting 
 * This function will select the source of FTMx external clock pin select
 * 
 *END**************************************************************************/
void SIM_HAL_SetFtmExternalClkPinMode(uint32_t baseAddr, uint8_t instance, sim_ftm_clk_sel_t select)
{
    assert (instance < HW_FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        BW_SIM_SOPT4_FTM0CLKSEL(baseAddr, select);
        break;
    case 1:
        BW_SIM_SOPT4_FTM1CLKSEL(baseAddr, select);
        break;
    case 2:
        BW_SIM_SOPT4_FTM2CLKSEL(baseAddr, select);
        break;
#if (HW_FTM_INSTANCE_COUNT > 3)
    case 3:
        BW_SIM_SOPT4_FTM3CLKSEL(baseAddr, select);
        break;
#endif
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmExternalClkPinMode
 * Description   : Get FlexTimer x external clock pin select setting
 * This function will get FlexTimer x external clock pin select setting.
 * 
 *END**************************************************************************/
sim_ftm_clk_sel_t SIM_HAL_GetFtmExternalClkPinMode(uint32_t baseAddr, uint8_t instance)
{
    sim_ftm_clk_sel_t retValue = (sim_ftm_clk_sel_t)0;

    assert (instance < HW_FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_ftm_clk_sel_t)BR_SIM_SOPT4_FTM0CLKSEL(baseAddr);
        break;
    case 1:
        retValue = (sim_ftm_clk_sel_t)BR_SIM_SOPT4_FTM1CLKSEL(baseAddr);
        break;
    case 2:
        retValue = (sim_ftm_clk_sel_t)BR_SIM_SOPT4_FTM2CLKSEL(baseAddr);
        break;
#if (HW_FTM_INSTANCE_COUNT > 3)
    case 3:
        retValue = (sim_ftm_clk_sel_t)BR_SIM_SOPT4_FTM3CLKSEL(baseAddr);
        break;
#endif
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetFtmChSrcMode
 * Description   : FlexTimer x channel y input capture source select setting 
 * This function will select FlexTimer x channel y input capture source
 * 
 *END**************************************************************************/
void SIM_HAL_SetFtmChSrcMode(uint32_t baseAddr,
                             uint8_t  instance,
                             uint8_t  channel,
                             sim_ftm_ch_src_t select)
{
    assert (instance < HW_FTM_INSTANCE_COUNT);

    switch (instance)
    {
#if FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS
    case 1:
        switch (channel)
        {
        case 0:
            BW_SIM_SOPT4_FTM1CH0SRC(baseAddr, select);
            break;
        default:
            break;
        }
        break;
#endif
#if FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS
    case 2:
        switch (channel)
        {
        case 0:
            BW_SIM_SOPT4_FTM2CH0SRC(baseAddr, select);
            break;
#if FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1
        case 1:
            BW_SIM_SOPT4_FTM2CH1SRC(baseAddr, select);
            break;
#endif
        default:
            break;
        }
        break;
#endif
#if FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS
    case 3:
        switch (channel)
        {
        case 0:
            BW_SIM_SOPT4_FTM3CH0SRC(baseAddr, select);
            break;
        default:
            break;
        }
        break;
#endif
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmChSrcMode
 * Description   : Get FlexTimer x channel y input capture source select setting
 * This function will get FlexTimer x channel y input capture source select 
 * setting.
 * 
 *END**************************************************************************/
sim_ftm_ch_src_t SIM_HAL_GetFtmChSrcMode(uint32_t baseAddr, uint8_t instance, uint8_t channel)
{
    sim_ftm_ch_src_t retValue = (sim_ftm_ch_src_t)0;

    assert (instance < HW_FTM_INSTANCE_COUNT);

    switch (instance)
    {
#if FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS
    case 1:
        switch (channel)
        {
        case 0:
            retValue = (sim_ftm_ch_src_t)BR_SIM_SOPT4_FTM1CH0SRC(baseAddr);
            break;
        default:
            break;
        }
        break;
#endif
#if FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS
    case 2:
        switch (channel)
        {
        case 0:
            retValue = (sim_ftm_ch_src_t)BR_SIM_SOPT4_FTM2CH0SRC(baseAddr);
            break;
#if FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1
        case 1:
            retValue = (sim_ftm_ch_src_t)BR_SIM_SOPT4_FTM2CH1SRC(baseAddr);
            break;
#endif
        default:
            break;
        }
        break;
#endif
#if FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS
    case 3:
        switch (channel)
        {
        case 0:
            retValue = (sim_ftm_ch_src_t)BR_SIM_SOPT4_FTM3CH0SRC(baseAddr);
            break;
        default:
            break;
        }
        break;
#endif
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetFtmFaultSelMode
 * Description   : Set FlexTimer x fault y select setting 
 * This function will set the FlexTimer x fault y select setting.
 * 
 *END**************************************************************************/
void SIM_HAL_SetFtmFaultSelMode(uint32_t baseAddr,
                                uint8_t  instance,
                                uint8_t  fault,
                                sim_ftm_flt_sel_t select)
{
    assert (instance < HW_FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        switch (fault)
        {
        case 0:
            BW_SIM_SOPT4_FTM0FLT0(baseAddr, select);
            break;
        case 1:
            BW_SIM_SOPT4_FTM0FLT1(baseAddr, select);
            break;
#if (FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT > 2)
        case 2:
            BW_SIM_SOPT4_FTM0FLT2(baseAddr, select);
            break;
#if (FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT > 3)
        case 3:
            BW_SIM_SOPT4_FTM0FLT3(baseAddr, select);
            break;
#endif
#endif
        default:
            break;
        }
        break;
    case 1:
        BW_SIM_SOPT4_FTM1FLT0(baseAddr, select);
        break;
    case 2:
        BW_SIM_SOPT4_FTM2FLT0(baseAddr, select);
        break;
#if (HW_FTM_INSTANCE_COUNT > 3)        
    case 3:
        BW_SIM_SOPT4_FTM3FLT0(baseAddr, select);
        break;
#endif
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetFtmFaultSelMode
 * Description   : Get FlexTimer x fault y select setting
 * This function will get FlexTimer x fault y select setting.
 * 
 *END**************************************************************************/
sim_ftm_flt_sel_t SIM_HAL_GetFtmFaultSelMode(uint32_t baseAddr, uint8_t instance, uint8_t fault)
{
    sim_ftm_flt_sel_t retValue = (sim_ftm_flt_sel_t)0;

    assert (instance < HW_FTM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        switch (fault)
        {
        case 0:
            retValue = (sim_ftm_flt_sel_t)BR_SIM_SOPT4_FTM0FLT0(baseAddr);
            break;
        case 1:
            retValue = (sim_ftm_flt_sel_t)BR_SIM_SOPT4_FTM0FLT1(baseAddr);
            break;
#if (FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT > 2)
        case 2:
            retValue = (sim_ftm_flt_sel_t)BR_SIM_SOPT4_FTM0FLT2(baseAddr);
            break;
#if (FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT > 3)
        case 3:
            retValue = (sim_ftm_flt_sel_t)BR_SIM_SOPT4_FTM0FLT3(baseAddr);
            break;
#endif
#endif
        default:
            break;
        }
        break;
    case 1:
        retValue = (sim_ftm_flt_sel_t)BR_SIM_SOPT4_FTM1FLT0(baseAddr);
        break;
    case 2:
        retValue = (sim_ftm_flt_sel_t)BR_SIM_SOPT4_FTM2FLT0(baseAddr);
        break;
#if (HW_FTM_INSTANCE_COUNT > 3)        
    case 3:
        retValue = (sim_ftm_flt_sel_t)BR_SIM_SOPT4_FTM3FLT0(baseAddr);
        break;
#endif
    default:
        break;
    }

    return retValue;
}
#endif

#if FSL_FEATURE_SIM_OPT_HAS_TPM
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetTpmExternalClkPinSelMode
 * Description   : Set Timer/PWM x external clock pin select setting 
 * This function will select the source of Timer/PWM x external clock pin select
 * 
 *END**************************************************************************/
void SIM_HAL_SetTpmExternalClkPinSelMode(uint32_t baseAddr,
                                         uint8_t instance,
                                         sim_tpm_clk_sel_t select)
{
    assert (instance < HW_TPM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        BW_SIM_SOPT4_TPM0CLKSEL(baseAddr, select);
        break;
    case 1:
        BW_SIM_SOPT4_TPM1CLKSEL(baseAddr, select);
        break;
    case 2:
        BW_SIM_SOPT4_TPM2CLKSEL(baseAddr, select);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetTpmExternalClkPinSelMode
 * Description   : Get Timer/PWM x external clock pin select setting
 * This function will get Timer/PWM x external clock pin select setting.
 * 
 *END**************************************************************************/
sim_tpm_clk_sel_t SIM_HAL_GetTpmExternalClkPinSelMode(uint32_t baseAddr, uint8_t instance)
{
    sim_tpm_clk_sel_t retValue = (sim_tpm_clk_sel_t)0;

    assert (instance < HW_TPM_INSTANCE_COUNT);

    switch (instance)
    {
    case 0:
        retValue = (sim_tpm_clk_sel_t)BR_SIM_SOPT4_TPM0CLKSEL(baseAddr);
        break;
    case 1:
        retValue = (sim_tpm_clk_sel_t)BR_SIM_SOPT4_TPM1CLKSEL(baseAddr);
        break;
    case 2:
        retValue = (sim_tpm_clk_sel_t)BR_SIM_SOPT4_TPM2CLKSEL(baseAddr);
        break;
    default:
        break;
    }

    return retValue;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_SetTpmChSrcMode
 * Description   : Timer/PWM x channel y input capture source select setting 
 * This function will select Timer/PWM x channel y input capture source
 * 
 *END**************************************************************************/
void SIM_HAL_SetTpmChSrcMode(uint32_t baseAddr,
                             uint8_t instance,
                             uint8_t channel,
                             sim_tpm_ch_src_t select)
{
    assert (instance < HW_TPM_INSTANCE_COUNT);

    switch (instance)
    {
    case 1:
        switch (channel)
        {
        case 0:
            BW_SIM_SOPT4_TPM1CH0SRC(baseAddr, select);
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (channel)
        {
        case 0:
            BW_SIM_SOPT4_TPM2CH0SRC(baseAddr, select);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_HAL_GetTpmChSrcMode
 * Description   : Get Timer/PWM x channel y input capture source select setting
 * This function will get Timer/PWM x channel y input capture source select 
 * setting.
 * 
 *END**************************************************************************/
sim_tpm_ch_src_t SIM_HAL_GetTpmChSrcMode(uint32_t baseAddr,
                                         uint8_t instance,
                                         uint8_t channel)
{
    sim_tpm_ch_src_t retValue = (sim_tpm_ch_src_t)0;

    assert (instance < HW_TPM_INSTANCE_COUNT);

    switch (instance)
    {
    case 1:
        switch (channel)
        {
        case 0:
            retValue = (sim_tpm_ch_src_t)BR_SIM_SOPT4_TPM1CH0SRC(baseAddr);
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (channel)
        {
        case 0:
            retValue = (sim_tpm_ch_src_t)BR_SIM_SOPT4_TPM2CH0SRC(baseAddr);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return retValue;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

