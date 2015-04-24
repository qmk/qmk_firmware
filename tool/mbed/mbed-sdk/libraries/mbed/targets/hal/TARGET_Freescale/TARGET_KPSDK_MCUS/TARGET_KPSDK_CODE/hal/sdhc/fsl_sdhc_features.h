/*
** ###################################################################
**     Version:             rev. 1.0, 2014-05-14
**     Build:               b140519
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

#if !defined(__FSL_SDHC_FEATURES_H__)
#define __FSL_SDHC_FEATURES_H__

#if defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLL12) || defined(CPU_MK24FN1M0VLQ12) || defined(CPU_MK63FN1M0VLQ12) || \
    defined(CPU_MK63FN1M0VMD12) || defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || defined(CPU_MK64FX512VLL12) || \
    defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || defined(CPU_MK64FX512VMD12) || \
    defined(CPU_MK64FN1M0VMD12)
    /* @brief Has external DMA support (register bit VENDOR[EXTDMAEN]). */
    #define FSL_FEATURE_SDHC_HAS_EXTERNAL_DMA_SUPPORT (1)
    /* @brief Has support of 3.0V voltage (register bit HTCAPBLT[VS30]). */
    #define FSL_FEATURE_SDHC_HAS_V300_SUPPORT (0)
    /* @brief Has support of 1.8V voltage (register bit HTCAPBLT[VS18]). */
    #define FSL_FEATURE_SDHC_HAS_V180_SUPPORT (0)
#elif defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || defined(CPU_MK65FX1M0VMI18) || \
    defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || defined(CPU_MK66FX1M0VMD18)
    /* @brief Has external DMA support (register bit VENDOR[EXTDMAEN]). */
    #define FSL_FEATURE_SDHC_HAS_EXTERNAL_DMA_SUPPORT (0)
    /* @brief Has support of 3.0V voltage (register bit HTCAPBLT[VS30]). */
    #define FSL_FEATURE_SDHC_HAS_V300_SUPPORT (0)
    /* @brief Has support of 1.8V voltage (register bit HTCAPBLT[VS18]). */
    #define FSL_FEATURE_SDHC_HAS_V180_SUPPORT (0)
#elif defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || defined(CPU_MK70FX512VMF15) || \
    defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15)
    /* @brief Has external DMA support (register bit VENDOR[EXTDMAEN]). */
    #define FSL_FEATURE_SDHC_HAS_EXTERNAL_DMA_SUPPORT (1)
    /* @brief Has support of 3.0V voltage (register bit HTCAPBLT[VS30]). */
    #define FSL_FEATURE_SDHC_HAS_V300_SUPPORT (1)
    /* @brief Has support of 1.8V voltage (register bit HTCAPBLT[VS18]). */
    #define FSL_FEATURE_SDHC_HAS_V180_SUPPORT (1)
#else
    #define MBED_NO_SDHC
#endif

#endif /* __FSL_SDHC_FEATURES_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
