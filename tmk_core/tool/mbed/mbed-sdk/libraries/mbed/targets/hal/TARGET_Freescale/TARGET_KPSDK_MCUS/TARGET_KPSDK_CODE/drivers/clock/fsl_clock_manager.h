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

#if !defined(__FSL_CLOCK_MANAGER_H__)
#define __FSL_CLOCK_MANAGER_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_mcg_hal.h"
#include "fsl_sim_hal.h"

/*! @addtogroup clock_manager*/
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* system clocks definition (should be moved to other proper place) */
#define CPU_XTAL1hz_CLK_HZ          1
#define CPU_LPO_CLK_HZ           1000

/* external clock definition (should be moved to other proper place) */

#define SDHC0_CLKIN                 0   /* kSimSDHC0_CLKIN */ 
#define ENET_1588_CLKIN             0   /* kSimENET_1588_CLKIN */
#define EXTAL_Clock                 0   /* kSimEXTAL_Clock */
#define EXTAL1_Clock                0   /* kSimEXTAL1_Clock */
#define USB_CLKIN                   0   /* kSimUSB_CLKIN */

/* Table of base addresses for instances. */
extern const uint32_t g_simBaseAddr[];
extern const uint32_t g_mcgBaseAddr[];

/*!
 * @brief Error code definition for the clock manager APIs
 */
typedef enum _clock_manager_error_code {
    kClockManagerSuccess,                           /*!< success */
    kClockManagerNoSuchClockName,                   /*!< cannot find the clock name */
    kClockManagerNoSuchClockModule,                 /*!< cannot find the clock module name */
    kClockManagerNoSuchClockSource,                 /*!< cannot find the clock source name */
    kClockManagerNoSuchDivider,                     /*!< cannot find the divider name */
    kClockManagerUnknown                            /*!< unknown error*/
} clock_manager_error_code_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Clock Frequencies*/
/*@{*/

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_names_t.
 * The MCG must be properly configured before using this function. See
 * the reference manual for supported clock names for different chip families.
 * The returned value is in Hertz. If it cannot find the clock name
 * or the name is not supported for a specific chip family, it returns an
 * error.
 *
 * @param clockName Clock names defined in clock_names_t
 * @param frequency Returned clock frequency value in Hertz
 * @return status   Error code defined in clock_manager_error_code_t
 */
clock_manager_error_code_t CLOCK_SYS_GetFreq(clock_names_t clockName,
                                                        uint32_t *frequency);

/*!
 * @brief Sets the clock source setting.
 *
 * This function sets the settings for a specified clock source. Each clock 
 * source has its own clock selection settings. See the chip reference manual for 
 * clock source detailed settings and the sim_clock_source_names_t 
 * for clock sources.
 *
 * @param clockSource Clock source name defined in sim_clock_source_names_t
 * @param setting     Setting value
 * @return status     If the clock source doesn't exist, it returns an error.
 */
clock_manager_error_code_t CLOCK_SYS_SetSource(clock_source_names_t clockSource, 
                                               uint8_t setting);

/*!
 * @brief Gets the clock source setting.
 *
 * This function gets the settings for a specified clock source. Each clock
 * source has its own clock selection settings. See the reference manual for
 * clock source detailed settings and the sim_clock_source_names_t
 * for clock sources.
 *
 * @param clockSource Clock source name
 * @param setting     Current setting for the clock source
 * @return status     If the clock source doesn't exist, it returns an error.
 */
clock_manager_error_code_t CLOCK_SYS_GetSource(clock_source_names_t clockSource, 
                                               uint8_t *setting);

/*!
 * @brief Sets the clock divider setting.
 *
 * This function sets the setting for a specified clock divider. See the
 * reference manual for a supported clock divider and value range and the
 * sim_clock_divider_names_t for dividers.
 *
 * @param clockDivider Clock divider name
 * @param divider      Divider setting
 * @return status      If the clock divider doesn't exist, it  returns an error.
 */
clock_manager_error_code_t CLOCK_SYS_SetDivider(clock_divider_names_t clockDivider, 
                                                uint32_t setting);

/*!
 * @brief Gets the clock divider setting.
 *
 * This function gets the setting for a specified clock divider. See the
 * reference manual for a supported clock divider and value range and the 
 * clock_divider_names_t for dividers.
 *
 * @param clockDivider Clock divider name
 * @param divider      Divider value pointer
 * @return status      If the clock divider doesn't exist, it returns an error.
 */
clock_manager_error_code_t CLOCK_SYS_GetDivider(clock_divider_names_t clockDivider,
                                                uint32_t *setting);

/*!
 * @brief Sets the clock out dividers setting.
 *
 * This function sets the setting for all clock out dividers at the same time.
 * See the reference manual for a supported clock divider and value range and the
 * clock_divider_names_t for clock out dividers.
 *
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
static inline void CLOCK_SYS_SetOutDividers(uint32_t outdiv1, uint32_t outdiv2,
                                            uint32_t outdiv3, uint32_t outdiv4)
{
    CLOCK_HAL_SetOutDividers(g_simBaseAddr[0], outdiv1, outdiv2, outdiv3, outdiv4);
}

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

/*
 * Include the cpu specific clock API header files.
 */
#if (defined(CPU_MK02FN128VFM10) || defined(CPU_MK02FN64VFM10) || defined(CPU_MK02FN128VLF10) || \
    defined(CPU_MK02FN64VLF10) || defined(CPU_MK02FN128VLH10) || defined(CPU_MK02FN64VLH10))

    #define K02F12810_SERIES

#elif (defined(CPU_MK20DX128VMP5) || defined(CPU_MK20DN128VMP5) || defined(CPU_MK20DX64VMP5) || \
    defined(CPU_MK20DN64VMP5) || defined(CPU_MK20DX32VMP5) || defined(CPU_MK20DN32VMP5) || \
    defined(CPU_MK20DX128VLH5) || defined(CPU_MK20DN128VLH5) || defined(CPU_MK20DX64VLH5) || \
    defined(CPU_MK20DN64VLH5) || defined(CPU_MK20DX32VLH5) || defined(CPU_MK20DN32VLH5) || \
    defined(CPU_MK20DX128VFM5) || defined(CPU_MK20DN128VFM5) || defined(CPU_MK20DX64VFM5) || \
    defined(CPU_MK20DN64VFM5) || defined(CPU_MK20DX32VFM5) || defined(CPU_MK20DN32VFM5) || \
    defined(CPU_MK20DX128VFT5) || defined(CPU_MK20DN128VFT5) || defined(CPU_MK20DX64VFT5) || \
    defined(CPU_MK20DN64VFT5) || defined(CPU_MK20DX32VFT5) || defined(CPU_MK20DN32VFT5) || \
    defined(CPU_MK20DX128VLF5) || defined(CPU_MK20DN128VLF5) || defined(CPU_MK20DX64VLF5) || \
    defined(CPU_MK20DN64VLF5) || defined(CPU_MK20DX32VLF5) || defined(CPU_MK20DN32VLF5))

    #define K20D5_SERIES


#elif (defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || \
    defined(CPU_MK22FN128VMP10))

    #define K22F12810_SERIES

    /* Clock System Level API header file */
    #include "MK22F12810/fsl_clock_K22F12810.h"

#elif (defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || \
    defined(CPU_MK22FN256VMP12))

    #define K22F25612_SERIES

    /* Clock System Level API header file */
    #include "MK22F25612/fsl_clock_K22F25612.h"



#elif (defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12))

    #define K22F51212_SERIES

    /* Clock System Level API header file */
    #include "MK22F51212/fsl_clock_K22F51212.h"


#elif (defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLQ12))

    #define K24F12_SERIES

    /* Clock System Level API header file */
    #include "MK24F12/fsl_clock_K24F12.h"

#elif (defined(CPU_MK24FN256VDC12))

    #define K24F25612_SERIES


#elif (defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12))

    #define K63F12_SERIES

    /* Clock System Level API header file */
    #include "MK63F12/fsl_clock_K63F12.h"

#elif (defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || defined(CPU_MK64FX512VLL12) || \
    defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VMD12) || defined(CPU_MK64FN1M0VMD12))

    #define K64F12_SERIES

    /* Clock System Level API header file */
    #include "MK64F12/fsl_clock_K64F12.h"

#elif (defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || \
    defined(CPU_MK65FX1M0VMI18))

    #define K65F18_SERIES


#elif (defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || \
    defined(CPU_MK66FX1M0VMD18))

    #define K66F18_SERIES


#elif (defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || \
    defined(CPU_MK70FX512VMF15) || defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || \
    defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))

    #define K70F12_SERIES


#elif (defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || \
    defined(CPU_MK70FX512VMF15) || defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || \
    defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))

    #define K70F15_SERIES


#elif (defined(CPU_MKL02Z32CAF4) || defined(CPU_MKL02Z8VFG4) || defined(CPU_MKL02Z16VFG4) || \
    defined(CPU_MKL02Z32VFG4) || defined(CPU_MKL02Z16VFK4) || defined(CPU_MKL02Z32VFK4) || \
    defined(CPU_MKL02Z16VFM4) || defined(CPU_MKL02Z32VFM4))

    #define KL02Z4_SERIES


#elif (defined(CPU_MKL03Z32CAF4) || defined(CPU_MKL03Z8VFG4) || defined(CPU_MKL03Z16VFG4) || \
    defined(CPU_MKL03Z32VFG4) || defined(CPU_MKL03Z8VFK4) || defined(CPU_MKL03Z16VFK4) || \
    defined(CPU_MKL03Z32VFK4))

    #define KL03Z4_SERIES


#elif (defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || defined(CPU_MKL05Z32VFK4) || \
    defined(CPU_MKL05Z8VLC4) || defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || \
    defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || defined(CPU_MKL05Z32VFM4) || \
    defined(CPU_MKL05Z16VLF4) || defined(CPU_MKL05Z32VLF4))

    #define KL05Z4_SERIES


#elif (defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z128VFM4) || defined(CPU_MKL13Z256VFM4) || \
    defined(CPU_MKL13Z64VFT4) || defined(CPU_MKL13Z128VFT4) || defined(CPU_MKL13Z256VFT4) || \
    defined(CPU_MKL13Z64VLH4) || defined(CPU_MKL13Z128VLH4) || defined(CPU_MKL13Z256VLH4) || \
    defined(CPU_MKL13Z64VMP4) || defined(CPU_MKL13Z128VMP4) || defined(CPU_MKL13Z256VMP4))

    #define KL13Z4_SERIES


#elif (defined(CPU_MKL23Z64VFM4) || defined(CPU_MKL23Z128VFM4) || defined(CPU_MKL23Z256VFM4) || \
    defined(CPU_MKL23Z64VFT4) || defined(CPU_MKL23Z128VFT4) || defined(CPU_MKL23Z256VFT4) || \
    defined(CPU_MKL23Z64VLH4) || defined(CPU_MKL23Z128VLH4) || defined(CPU_MKL23Z256VLH4) || \
    defined(CPU_MKL23Z64VMP4) || defined(CPU_MKL23Z128VMP4) || defined(CPU_MKL23Z256VMP4))

    #define KL23Z4_SERIES


#elif (defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || \
    defined(CPU_MKL25Z32VFT4) || defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || \
    defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || defined(CPU_MKL25Z128VLH4) || \
    defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4))

    #define KL25Z4_SERIES

    /* Clock System Level API header file */
    #include "MKL25Z4/fsl_clock_KL25Z4.h"

#elif (defined(CPU_MKL26Z32VFM4) || defined(CPU_MKL26Z64VFM4) || defined(CPU_MKL26Z128VFM4) || \
    defined(CPU_MKL26Z32VFT4) || defined(CPU_MKL26Z64VFT4) || defined(CPU_MKL26Z128VFT4) || \
    defined(CPU_MKL26Z32VLH4) || defined(CPU_MKL26Z64VLH4) || defined(CPU_MKL26Z128VLH4) || \
    defined(CPU_MKL26Z256VLH4) || defined(CPU_MKL26Z256VLK4) || defined(CPU_MKL26Z128VLL4) || \
    defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || defined(CPU_MKL26Z256VMC4))

    #define KL26Z4_SERIES


#elif (defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || defined(CPU_MKL33Z128VMP4) || \
    defined(CPU_MKL33Z256VMP4))

    #define KL33Z4_SERIES


#elif (defined(CPU_MKL43Z64VLH4) || defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || \
    defined(CPU_MKL43Z64VMP4) || defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4))

    #define KL43Z4_SERIES


#elif (defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4))

    #define KL46Z4_SERIES


#elif (defined(CPU_MKV30F128VFM10) || defined(CPU_MKV30F64VFM10) || defined(CPU_MKV30F128VLF10) || \
    defined(CPU_MKV30F64VLF10) || defined(CPU_MKV30F128VLH10) || defined(CPU_MKV30F64VLH10))

    #define KV30F12810_SERIES


#elif (defined(CPU_MKV31F128VLH10) || defined(CPU_MKV31F128VLL10))

    #define KV31F12810_SERIES

    /* Clock System Level API header file */
    #include "MKV31F12810/fsl_clock_KV31F12810.h"

#elif (defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12))

    #define KV31F25612_SERIES

    /* Clock System Level API header file */
    #include "MKV31F25612/fsl_clock_KV31F25612.h"


#elif (defined(CPU_MKV31F512VLH12) || defined(CPU_MKV31F512VLL12))

    #define KV31F51212_SERIES

    /* Clock System Level API header file */
    #include "MKV31F51212/fsl_clock_KV31F51212.h"

#elif (defined(CPU_MKV40F128VLH15) || defined(CPU_MKV40F128VLL15) || defined(CPU_MKV40F256VLH15) || \
    defined(CPU_MKV40F256VLL15) || defined(CPU_MKV40F64VLH15))

    #define KV40F15_SERIES


#elif (defined(CPU_MKV43F128VLH15) || defined(CPU_MKV43F128VLL15) || defined(CPU_MKV43F64VLH15))

    #define KV43F15_SERIES


#elif (defined(CPU_MKV44F128VLH15) || defined(CPU_MKV44F128VLL15) || defined(CPU_MKV44F64VLH15))

    #define KV44F15_SERIES


#elif (defined(CPU_MKV45F128VLH15) || defined(CPU_MKV45F128VLL15) || defined(CPU_MKV45F256VLH15) || \
    defined(CPU_MKV45F256VLL15))

    #define KV45F15_SERIES


#elif (defined(CPU_MKV46F128VLH15) || defined(CPU_MKV46F128VLL15) || defined(CPU_MKV46F256VLH15) || \
    defined(CPU_MKV46F256VLL15))

    #define KV46F15_SERIES

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_CLOCK_MANAGER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

