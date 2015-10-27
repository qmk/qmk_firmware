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
#if !defined(__FSL_LLWU_HAL_H__)
#define __FSL_LLWU_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_llwu_features.h"

/*! @addtogroup llwu_hal*/
/*! @{*/

/*! @file fsl_llwu_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief External input pin control modes */
typedef enum _llwu_external_pin_modes {
    kLlwuExternalPinDisabled,          /* pin disabled as wakeup input */
    kLlwuExternalPinRisingEdge,        /* pin enabled with rising edge detection */
    kLlwuExternalPinFallingEdge,       /* pin enabled with falling edge detection */
    kLlwuExternalPinChangeDetect       /* pin enabled with any change detection */
} llwu_external_pin_modes_t;

/*! @brief Digital filter control modes */
typedef enum _llwu_filter_modes {
    kLlwuFilterDisabled,            /* filter disabled  */
    kLlwuFilterPosEdgeDetect,       /* filter positive edge detection */
    kLlwuFilterNegEdgeDetect,       /* filter negative edge detection */
    kLlwuFilterAnyEdgeDetect        /* filter any edge detection */
} llwu_filter_modes_t;

/*! @brief External input pin filter control structure */
typedef struct _llwu_external_pin_filter_mode {
    llwu_filter_modes_t         filterMode;         /* filter mode */
    uint32_t                    pinNumber;          /* pin number */
} llwu_external_pin_filter_mode_t;

/*! @brief Reset enable control structure */
typedef struct _llwu_reset_enable_mode {
    bool                        lowLeakageMode;     /* reset for Low-leakage mode */
    bool                        digitalFilterMode;  /* reset for digital filter mode */
} llwu_reset_enable_mode_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Sets the external input pin source mode.
 *
 * This function sets the external input pin source mode that is used
 * as a wake up source. 
 *
 * @param baseAddr      Register base address of LLWU
 * @param pinMode       pin configuration mode defined in llwu_external_pin_modes_t
 * @param pinNumber     pin number specified
 */
void LLWU_HAL_SetExternalInputPinMode(uint32_t baseAddr,
                                      llwu_external_pin_modes_t pinMode,
                                      uint32_t pinNumber);

/*!
 * @brief Gets the external input pin source mode.
 *
 * This function gets the external input pin source mode that is used
 * as wake up source. 
 *
 * @param baseAddr      Register base address of LLWU
 * @param pinNumber     pin number specified
 * @return pinMode      pin mode defined in llwu_external_pin_modes_t
 */
llwu_external_pin_modes_t LLWU_HAL_GetExternalInputPinMode(uint32_t baseAddr,
                                                           uint32_t pinNumber);

/*!
 * @brief Enables/disables the internal module source.
 *
 * This function enables/disables the internal module source mode that is used
 * as a wake up source. 
 *
 * @param baseAddr      Register base address of LLWU
 * @param moduleNumber  module number specified
 * @param enable        enable or disable setting
 */
void LLWU_HAL_SetInternalModuleCmd(uint32_t baseAddr, uint32_t moduleNumber, bool enable);

/*!
 * @brief Gets the internal module source enable setting.
 *
 * This function gets the internal module source enable setting that is used
 * as a wake up source. 
 *
 * @param baseAddr      Register base address of LLWU
 * @param moduleNumber     module number specified
 * @return enable        enable or disable setting
 */
bool LLWU_HAL_GetInternalModuleCmd(uint32_t baseAddr, uint32_t moduleNumber);

/*!
 * @brief Gets the external wakeup source flag.
 *
 * This function gets the external wakeup source flag for a specific pin.
 *
 * @param baseAddr      Register base address of LLWU
 * @param pinNumber     pin number specified
 * @return flag         true if wakeup source flag set
 */
bool LLWU_HAL_GetExternalPinWakeupFlag(uint32_t baseAddr, uint32_t pinNumber);

/*!
 * @brief Clears the external wakeup source flag.
 *
 * This function clears the external wakeup source flag for a specific pin.
 *
 * @param baseAddr      Register base address of LLWU
 * @param pinNumber     pin number specified
 */
void LLWU_HAL_ClearExternalPinWakeupFlag(uint32_t baseAddr, uint32_t pinNumber);

/*!
 * @brief Gets the internal module wakeup source flag.
 *
 * This function gets the internal module wakeup source flag for a specific module.
 *
 * @param baseAddr      Register base address of LLWU
 * @param moduleNumber  module number specified
 * @return flag         true if wakeup flag set
 */
bool LLWU_HAL_GetInternalModuleWakeupFlag(uint32_t baseAddr, uint32_t moduleNumber);

/*!
 * @brief Sets the pin filter configuration.
 *
 * This function sets the pin filter configuration.
 *
 * @param baseAddr      Register base address of LLWU
 * @param filterNumber  filter number specified
 * @param pinFilterMode filter mode configuration
 */
void LLWU_HAL_SetPinFilterMode(uint32_t baseAddr, uint32_t filterNumber, 
                               llwu_external_pin_filter_mode_t pinFilterMode);
/*!
 * @brief Gets the pin filter configuration.
 *
 * This function gets the pin filter configuration.
 *
 * @param baseAddr      Register base address of LLWU
 * @param filterNumber  filter number specified
 * @param pinFilterMode filter mode configuration
 */
void LLWU_HAL_GetPinFilterMode(uint32_t baseAddr, uint32_t filterNumber, 
                               llwu_external_pin_filter_mode_t *pinFilterMode);

/*!
 * @brief Gets the filter detect flag.
 *
 * This function will get the filter detect flag.
 *
 * @param baseAddr      Register base address of LLWU
 * @param filterNumber  filter number specified
 * @return flag         true if the filter was a wakeup source
 */
bool LLWU_HAL_GetFilterDetectFlag(uint32_t baseAddr, uint32_t filterNumber);

/*!
 * @brief Clears the filter detect flag.
 *
 * This function will clear the filter detect flag.
 *
 * @param baseAddr      Register base address of LLWU
 * @param filterNumber  filter number specified
 */
void LLWU_HAL_ClearFilterDetectFlag(uint32_t baseAddr, uint32_t filterNumber);

#if FSL_FEATURE_LLWU_HAS_RESET_ENABLE
/*!
 * @brief Sets the reset enable mode.
 *
 * This function will set the reset enable mode.
 *
 * @param baseAddr      Register base address of LLWU
 * @param resetEnableMode  reset enable mode defined in llwu_reset_enable_mode_t
 */
void LLWU_HAL_SetResetEnableMode(uint32_t baseAddr, llwu_reset_enable_mode_t resetEnableMode);

/*!
 * @brief Gets the reset enable mode.
 *
 * This function gets the reset enable mode.
 *
 * @param baseAddr      Register base address of LLWU
 * @param resetEnableMode  reset enable mode defined in llwu_reset_enable_mode_t
 */
void LLWU_HAL_GetResetEnableMode(uint32_t baseAddr, llwu_reset_enable_mode_t *resetEnableMode);
#endif

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Low-Leakage Wakeup Unit Control APIs*/
/*@{*/


/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_LLWU_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

