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
#if !defined(__FSL_ENET_FEATURES_H__)
#define __FSL_ENET_FEATURES_H__


#if defined(CPU_MK63FN1M0VMD12) || defined(CPU_MK63FN1M0VMD12WS)
  #define FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY             (1)
	#define FSL_FEATURE_ENET_SUPPORT_PTP                     (0)
	#define FSL_FEATURE_ENET_INTERRUPT_COUNT                 (4)
	#define FSL_FEATURE_ENET_PTP_TIMER_CHANNEL_INTERRUPT     (0)
#elif  defined(CPU_MK64FN1M0VMD12) || defined(CPU_MK64FX512VMD12)
  #define FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY             (0)
	#define FSL_FEATURE_ENET_SUPPORT_PTP                     (0)
	#define FSL_FEATURE_ENET_INTERRUPT_COUNT                 (4)
	#define FSL_FEATURE_ENET_PTP_TIMER_CHANNEL_INTERRUPT     (0)
#elif defined(CPU_MK70FN1M0VMJ12)
  #define FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY             (1)
	#define FSL_FEATURE_ENET_SUPPORT_PTP                     (0)
	#define FSL_FEATURE_ENET_INTERRUPT_COUNT                 (4)
#else
    #define MBED_NO_ENET
#endif


#endif /* __FSL_ENET_FEATURES_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/
