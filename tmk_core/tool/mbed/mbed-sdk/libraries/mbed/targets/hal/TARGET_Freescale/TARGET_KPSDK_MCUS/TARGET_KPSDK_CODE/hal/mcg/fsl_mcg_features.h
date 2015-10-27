/*
** ###################################################################
**     Version:             rev. 1.0, 2014-05-14
**     Build:               b140515
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright: 2014 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2014-05-14)
**         Customer release.
**
** ###################################################################
*/

#if !defined(__FSL_MCG_FEATURES_H__)
#define __FSL_MCG_FEATURES_H__

#if defined(CPU_MK02FN128VFM10) || defined(CPU_MK02FN64VFM10) || defined(CPU_MK02FN128VLF10) || defined(CPU_MK02FN64VLF10) || \
    defined(CPU_MK02FN128VLH10) || defined(CPU_MK02FN64VLH10) || defined(CPU_MKV30F128VFM10) || defined(CPU_MKV30F64VFM10) || \
    defined(CPU_MKV30F128VLF10) || defined(CPU_MKV30F64VLF10) || defined(CPU_MKV30F128VLH10) || defined(CPU_MKV30F64VLH10) || \
    defined(CPU_MKV31F128VLH10) || defined(CPU_MKV31F128VLL10)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (0)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (0)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (0)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (1)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (1)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (0)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (1)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (0)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (0)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (0)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MK20DX128VMP5) || defined(CPU_MK20DN128VMP5) || defined(CPU_MK20DX64VMP5) || defined(CPU_MK20DN64VMP5) || \
    defined(CPU_MK20DX32VMP5) || defined(CPU_MK20DN32VMP5) || defined(CPU_MK20DX128VLH5) || defined(CPU_MK20DN128VLH5) || \
    defined(CPU_MK20DX64VLH5) || defined(CPU_MK20DN64VLH5) || defined(CPU_MK20DX32VLH5) || defined(CPU_MK20DN32VLH5) || \
    defined(CPU_MK20DX128VFM5) || defined(CPU_MK20DN128VFM5) || defined(CPU_MK20DX64VFM5) || defined(CPU_MK20DN64VFM5) || \
    defined(CPU_MK20DX32VFM5) || defined(CPU_MK20DN32VFM5) || defined(CPU_MK20DX128VFT5) || defined(CPU_MK20DN128VFT5) || \
    defined(CPU_MK20DX64VFT5) || defined(CPU_MK20DN64VFT5) || defined(CPU_MK20DX32VFT5) || defined(CPU_MK20DN32VFT5) || \
    defined(CPU_MK20DX128VLF5) || defined(CPU_MK20DN128VLF5) || defined(CPU_MK20DX64VLF5) || defined(CPU_MK20DN64VLF5) || \
    defined(CPU_MK20DX32VLF5) || defined(CPU_MK20DN32VLF5)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (25)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (24)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (0)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (1)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (0)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (0)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (1)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (1)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (1)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (1)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || defined(CPU_MK22FN128VMP10)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (0)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (0)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (1)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (1)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (1)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (0)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (1)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (0)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (0)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (0)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || defined(CPU_MK22FN256VMP12) || \
    defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12) || defined(CPU_MK24FN1M0VDC12) || \
    defined(CPU_MK24FN1M0VLL12) || defined(CPU_MK24FN1M0VLQ12) || defined(CPU_MK24FN256VDC12) || defined(CPU_MK63FN1M0VLQ12) || \
    defined(CPU_MK63FN1M0VMD12) || defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || defined(CPU_MK64FX512VLL12) || \
    defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || defined(CPU_MK64FX512VMD12) || \
    defined(CPU_MK64FN1M0VMD12)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (25)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (24)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (0)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (1)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (1)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (1)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (1)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (1)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (1)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (0)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || defined(CPU_MK65FX1M0VMI18) || \
    defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || defined(CPU_MK66FX1M0VMD18)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (8)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (24)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (0)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (1)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (1)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (1)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (1)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (1)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (1)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (0)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (1)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (1)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || defined(CPU_MK70FX512VMF15) || \
    defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (8)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (16)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (0)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (1)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (1)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (0)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (1)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (0)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (0)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (1)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (1)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (1)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (1)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (1)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MKL03Z32CAF4) || defined(CPU_MKL03Z8VFG4) || defined(CPU_MKL03Z16VFG4) || defined(CPU_MKL03Z32VFG4) || \
    defined(CPU_MKL03Z8VFK4) || defined(CPU_MKL03Z16VFK4) || defined(CPU_MKL03Z32VFK4)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (0)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (1)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (0)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (0)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (0)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (0)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (0)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (0)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (0)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (0)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (0)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (0)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (0)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (0)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (1)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (1)
#elif defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || defined(CPU_MKL05Z32VFK4) || defined(CPU_MKL05Z8VLC4) || \
    defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || \
    defined(CPU_MKL05Z32VFM4) || defined(CPU_MKL05Z16VLF4) || defined(CPU_MKL05Z32VLF4)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (0)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (1)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (0)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (0)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (0)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (0)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (0)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (0)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (1)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (0)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z128VFM4) || defined(CPU_MKL13Z256VFM4) || defined(CPU_MKL13Z64VFT4) || \
    defined(CPU_MKL13Z128VFT4) || defined(CPU_MKL13Z256VFT4) || defined(CPU_MKL13Z64VLH4) || defined(CPU_MKL13Z128VLH4) || \
    defined(CPU_MKL13Z256VLH4) || defined(CPU_MKL13Z64VMP4) || defined(CPU_MKL13Z128VMP4) || defined(CPU_MKL13Z256VMP4) || \
    defined(CPU_MKL23Z64VFM4) || defined(CPU_MKL23Z128VFM4) || defined(CPU_MKL23Z256VFM4) || defined(CPU_MKL23Z64VFT4) || \
    defined(CPU_MKL23Z128VFT4) || defined(CPU_MKL23Z256VFT4) || defined(CPU_MKL23Z64VLH4) || defined(CPU_MKL23Z128VLH4) || \
    defined(CPU_MKL23Z256VLH4) || defined(CPU_MKL23Z64VMP4) || defined(CPU_MKL23Z128VMP4) || defined(CPU_MKL23Z256VMP4) || \
    defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || defined(CPU_MKL33Z128VMP4) || defined(CPU_MKL33Z256VMP4) || \
    defined(CPU_MKL43Z64VLH4) || defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || defined(CPU_MKL43Z64VMP4) || \
    defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (0)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (1)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (0)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (0)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (0)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (0)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (0)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (0)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (1)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (0)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (0)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (0)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (0)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (1)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (1)
#elif defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || defined(CPU_MKL25Z32VFT4) || \
    defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || \
    defined(CPU_MKL25Z128VLH4) || defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (25)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (24)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (1)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (0)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (0)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (0)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (1)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (0)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (1)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (1)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (1)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MKL26Z256VLK4) || defined(CPU_MKL26Z128VLL4) || defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || \
    defined(CPU_MKL26Z256VMC4) || defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (25)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (24)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (1)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (0)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (0)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (1)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (1)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (0)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (1)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (1)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (1)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12) || defined(CPU_MKV31F512VLH12) || defined(CPU_MKV31F512VLL12)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (25)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (24)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (0)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (0)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (1)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (1)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (1)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (1)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (1)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (0)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#elif defined(CPU_MKV40F128VLH15) || defined(CPU_MKV40F128VLL15) || defined(CPU_MKV40F256VLH15) || defined(CPU_MKV40F256VLL15) || \
    defined(CPU_MKV40F64VLH15) || defined(CPU_MKV43F128VLH15) || defined(CPU_MKV43F128VLL15) || defined(CPU_MKV43F64VLH15) || \
    defined(CPU_MKV44F128VLH15) || defined(CPU_MKV44F128VLL15) || defined(CPU_MKV44F64VLH15) || defined(CPU_MKV45F128VLH15) || \
    defined(CPU_MKV45F128VLL15) || defined(CPU_MKV45F256VLH15) || defined(CPU_MKV45F256VLL15) || defined(CPU_MKV46F128VLH15) || \
    defined(CPU_MKV46F128VLL15) || defined(CPU_MKV46F256VLH15) || defined(CPU_MKV46F256VLL15)
    /* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV] increased by one). */
    #define FSL_FEATURE_MCG_PLL_PRDIV_MAX (8)
    /* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
    #define FSL_FEATURE_MCG_PLL_VDIV_BASE (16)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
    #define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (1)
    /* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1] and C8[LOCRE1]). */
    #define FSL_FEATURE_MCG_HAS_RTC_32K (0)
    /* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_PLL1 (0)
    /* @brief Has 48MHz internal oscillator. */
    #define FSL_FEATURE_MCG_HAS_IRC_48M (0)
    /* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
    #define FSL_FEATURE_MCG_HAS_OSC1 (0)
    /* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
    #define FSL_FEATURE_MCG_HAS_FCFTRIM (1)
    /* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
    #define FSL_FEATURE_MCG_HAS_LOLRE (1)
    /* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
    #define FSL_FEATURE_MCG_USE_OSCSEL (0)
    /* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
    #define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
    /* @brief TBD */
    #define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
    /* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL (1)
    /* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
    #define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (0)
    /* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
    #define FSL_FEATURE_MCG_HAS_FLL (1)
    /* @brief Has PLL external to MCG (register C9). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
    /* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
    #define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
    /* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
    /* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
    #define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
    /* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
    #define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
    /* @brief Has external clock monitor (register bit C6[CME]). */
    #define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
    /* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
    #define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
    /* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
    #define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_MCG_FEATURES_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
