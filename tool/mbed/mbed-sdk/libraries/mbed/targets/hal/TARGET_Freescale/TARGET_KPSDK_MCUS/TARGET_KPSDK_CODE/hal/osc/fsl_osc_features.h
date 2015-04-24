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

#if !defined(__FSL_OSC_FEATURES_H__)
#define __FSL_OSC_FEATURES_H__

#if defined(CPU_MK02FN128VFM10) || defined(CPU_MK02FN64VFM10) || defined(CPU_MK02FN128VLF10) || defined(CPU_MK02FN64VLF10) || \
    defined(CPU_MK02FN128VLH10) || defined(CPU_MK02FN64VLH10) || defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || \
    defined(CPU_MK22FN128VLL10) || defined(CPU_MK22FN128VMP10) || defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || \
    defined(CPU_MK22FN256VLL12) || defined(CPU_MK22FN256VMP12) || defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || \
    defined(CPU_MK22FN512VLL12) || defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || \
    defined(CPU_MK65FX1M0VMI18) || defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || \
    defined(CPU_MK66FX1M0VMD18) || defined(CPU_MKV30F128VFM10) || defined(CPU_MKV30F64VFM10) || defined(CPU_MKV30F128VLF10) || \
    defined(CPU_MKV30F64VLF10) || defined(CPU_MKV30F128VLH10) || defined(CPU_MKV30F64VLH10) || defined(CPU_MKV31F128VLH10) || \
    defined(CPU_MKV31F128VLL10) || defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12) || defined(CPU_MKV31F512VLH12) || \
    defined(CPU_MKV31F512VLL12)
    /* @brief Has OSC1 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC1 (0)
    /* @brief Has OSC0 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC0 (0)
    /* @brief Has OSC external oscillator (without index). */
    #define FSL_FEATURE_OSC_HAS_OSC (1)
    /* @brief Number of OSC external oscillators. */
    #define FSL_FEATURE_OSC_OSC_COUNT (1)
    /* @brief Has external reference clock divider (register bit field DIV[ERPS]). */
    #define FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER (1)
#elif defined(CPU_MK20DX128VMP5) || defined(CPU_MK20DN128VMP5) || defined(CPU_MK20DX64VMP5) || defined(CPU_MK20DN64VMP5) || \
    defined(CPU_MK20DX32VMP5) || defined(CPU_MK20DN32VMP5) || defined(CPU_MK20DX128VLH5) || defined(CPU_MK20DN128VLH5) || \
    defined(CPU_MK20DX64VLH5) || defined(CPU_MK20DN64VLH5) || defined(CPU_MK20DX32VLH5) || defined(CPU_MK20DN32VLH5) || \
    defined(CPU_MK20DX128VFM5) || defined(CPU_MK20DN128VFM5) || defined(CPU_MK20DX64VFM5) || defined(CPU_MK20DN64VFM5) || \
    defined(CPU_MK20DX32VFM5) || defined(CPU_MK20DN32VFM5) || defined(CPU_MK20DX128VFT5) || defined(CPU_MK20DN128VFT5) || \
    defined(CPU_MK20DX64VFT5) || defined(CPU_MK20DN64VFT5) || defined(CPU_MK20DX32VFT5) || defined(CPU_MK20DN32VFT5) || \
    defined(CPU_MK20DX128VLF5) || defined(CPU_MK20DN128VLF5) || defined(CPU_MK20DX64VLF5) || defined(CPU_MK20DN64VLF5) || \
    defined(CPU_MK20DX32VLF5) || defined(CPU_MK20DN32VLF5) || defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || \
    defined(CPU_MKL05Z32VFK4) || defined(CPU_MKL05Z8VLC4) || defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || \
    defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || defined(CPU_MKL05Z32VFM4) || defined(CPU_MKL05Z16VLF4) || \
    defined(CPU_MKL05Z32VLF4) || defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z128VFM4) || defined(CPU_MKL13Z256VFM4) || \
    defined(CPU_MKL13Z64VFT4) || defined(CPU_MKL13Z128VFT4) || defined(CPU_MKL13Z256VFT4) || defined(CPU_MKL13Z64VLH4) || \
    defined(CPU_MKL13Z128VLH4) || defined(CPU_MKL13Z256VLH4) || defined(CPU_MKL13Z64VMP4) || defined(CPU_MKL13Z128VMP4) || \
    defined(CPU_MKL13Z256VMP4) || defined(CPU_MKL23Z64VFM4) || defined(CPU_MKL23Z128VFM4) || defined(CPU_MKL23Z256VFM4) || \
    defined(CPU_MKL23Z64VFT4) || defined(CPU_MKL23Z128VFT4) || defined(CPU_MKL23Z256VFT4) || defined(CPU_MKL23Z64VLH4) || \
    defined(CPU_MKL23Z128VLH4) || defined(CPU_MKL23Z256VLH4) || defined(CPU_MKL23Z64VMP4) || defined(CPU_MKL23Z128VMP4) || \
    defined(CPU_MKL23Z256VMP4) || defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || \
    defined(CPU_MKL25Z32VFT4) || defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || defined(CPU_MKL25Z32VLH4) || \
    defined(CPU_MKL25Z64VLH4) || defined(CPU_MKL25Z128VLH4) || defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || \
    defined(CPU_MKL25Z128VLK4) || defined(CPU_MKL26Z256VLK4) || defined(CPU_MKL26Z128VLL4) || defined(CPU_MKL26Z256VLL4) || \
    defined(CPU_MKL26Z128VMC4) || defined(CPU_MKL26Z256VMC4) || defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || \
    defined(CPU_MKL33Z128VMP4) || defined(CPU_MKL33Z256VMP4) || defined(CPU_MKL43Z64VLH4) || defined(CPU_MKL43Z128VLH4) || \
    defined(CPU_MKL43Z256VLH4) || defined(CPU_MKL43Z64VMP4) || defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4) || \
    defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || defined(CPU_MKL46Z256VLL4) || \
    defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4)
    /* @brief Has OSC1 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC1 (0)
    /* @brief Has OSC0 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC0 (1)
    /* @brief Has OSC external oscillator (without index). */
    #define FSL_FEATURE_OSC_HAS_OSC (0)
    /* @brief Number of OSC external oscillators. */
    #define FSL_FEATURE_OSC_OSC_COUNT (1)
    /* @brief Has external reference clock divider (register bit field DIV[ERPS]). */
    #define FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER (0)
#elif defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLL12) || defined(CPU_MK24FN1M0VLQ12) || defined(CPU_MK24FN256VDC12) || \
    defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12) || defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || \
    defined(CPU_MK64FX512VLL12) || defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VMD12) || defined(CPU_MK64FN1M0VMD12)
    /* @brief Has OSC1 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC1 (0)
    /* @brief Has OSC0 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC0 (0)
    /* @brief Has OSC external oscillator (without index). */
    #define FSL_FEATURE_OSC_HAS_OSC (1)
    /* @brief Number of OSC external oscillators. */
    #define FSL_FEATURE_OSC_OSC_COUNT (1)
    /* @brief Has external reference clock divider (register bit field DIV[ERPS]). */
    #define FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER (0)
#elif defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || defined(CPU_MK70FX512VMF15) || \
    defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15)
    /* @brief Has OSC1 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC1 (1)
    /* @brief Has OSC0 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC0 (1)
    /* @brief Has OSC external oscillator (without index). */
    #define FSL_FEATURE_OSC_HAS_OSC (0)
    /* @brief Number of OSC external oscillators. */
    #define FSL_FEATURE_OSC_OSC_COUNT (2)
    /* @brief Has external reference clock divider (register bit field DIV[ERPS]). */
    #define FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER (0)
#elif defined(CPU_MKL03Z32CAF4) || defined(CPU_MKL03Z8VFG4) || defined(CPU_MKL03Z16VFG4) || defined(CPU_MKL03Z32VFG4) || \
    defined(CPU_MKL03Z8VFK4) || defined(CPU_MKL03Z16VFK4) || defined(CPU_MKL03Z32VFK4)
    /* @brief Has OSC1 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC1 (0)
    /* @brief Has OSC0 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC0 (0)
    /* @brief Has OSC external oscillator (without index). */
    #define FSL_FEATURE_OSC_HAS_OSC (0)
    /* @brief Number of OSC external oscillators. */
    #define FSL_FEATURE_OSC_OSC_COUNT (0)
    /* @brief Has external reference clock divider (register bit field DIV[ERPS]). */
    #define FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER (0)
#elif defined(CPU_MKV40F128VLH15) || defined(CPU_MKV40F128VLL15) || defined(CPU_MKV40F256VLH15) || defined(CPU_MKV40F256VLL15) || \
    defined(CPU_MKV40F64VLH15) || defined(CPU_MKV43F128VLH15) || defined(CPU_MKV43F128VLL15) || defined(CPU_MKV43F64VLH15) || \
    defined(CPU_MKV44F128VLH15) || defined(CPU_MKV44F128VLL15) || defined(CPU_MKV44F64VLH15) || defined(CPU_MKV45F128VLH15) || \
    defined(CPU_MKV45F128VLL15) || defined(CPU_MKV45F256VLH15) || defined(CPU_MKV45F256VLL15) || defined(CPU_MKV46F128VLH15) || \
    defined(CPU_MKV46F128VLL15) || defined(CPU_MKV46F256VLH15) || defined(CPU_MKV46F256VLL15)
    /* @brief Has OSC1 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC1 (0)
    /* @brief Has OSC0 external oscillator. */
    #define FSL_FEATURE_OSC_HAS_OSC0 (0)
    /* @brief Has OSC external oscillator (without index). */
    #define FSL_FEATURE_OSC_HAS_OSC (0)
    /* @brief Number of OSC external oscillators. */
    #define FSL_FEATURE_OSC_OSC_COUNT (0)
    /* @brief Has external reference clock divider (register bit field DIV[ERPS]). */
    #define FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER (1)
#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_OSC_FEATURES_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
