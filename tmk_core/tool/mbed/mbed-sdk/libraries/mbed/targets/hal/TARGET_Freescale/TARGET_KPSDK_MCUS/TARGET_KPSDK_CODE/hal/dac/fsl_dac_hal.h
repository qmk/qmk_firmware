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

#ifndef __FSL_DAC_HAL_H__
#define __FSL_DAC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_dac_features.h"

/*!
 * @addtogroup dac_hal
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*!
 * @brief DAC status return codes.
 */
typedef enum _dac_status
{
    kStatus_DAC_Success = 0U, /*!< Success. */
    kStatus_DAC_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_DAC_Failed = 2U /*!< Execution failed. */
} dac_status_t;

/*!
 * @brief Defines the type of selection for DAC module's reference voltage source.
 *
 * See the appropriate SoC Reference Manual for actual connections.
 */
typedef enum _dac_ref_volt_src_mode
{
    kDacRefVoltSrcOfVref1 = 0U, /*!< Select DACREF_1 as the reference voltage. */
    kDacRefVoltSrcOfVref2 = 1U, /*!< Select DACREF_2 as the reference voltage. */
} dac_ref_volt_src_mode_t;

/*!
 * @brief Defines the type of selection for DAC module trigger mode.
 */
typedef enum _dac_trigger_mode
{
    kDacTriggerByHardware = 0U, /*!< Select hardware trigger. */
    kDacTriggerBySoftware = 1U  /*!< Select software trigger. */
} dac_trigger_mode_t;

/*!
 * @brief Defines the type of selection for buffer watermark mode.
 *
 * If the buffer feature for DAC module is enabled, a watermark event will
 * occur when the buffer index hits the watermark.
 */
typedef enum _dac_buff_watermark_mode
{
    kDacBuffWatermarkFromUpperAs1Word = 0U, /*!< Select 1 word away from the upper of buffer. */
    kDacBuffWatermarkFromUpperAs2Word = 1U, /*!< Select 2 word away from the upper of buffer. */
    kDacBuffWatermarkFromUpperAs3Word = 2U, /*!< Select 3 word away from the upper of buffer. */
    kDacBuffWatermarkFromUpperAs4Word = 3U, /*!< Select 4 word away from the upper of buffer. */
} dac_buff_watermark_mode_t;

/*!
 * @brief Defines the type of selection for buffer work mode.
 *
 * There are three kinds of work modes when the DAC buffer is enabled.
 * Normal mode - When the buffer index hits the upper level, it
 *     starts (0) on the next trigger.
 * Swing mode - When the buffer index hits the upper level, it goes backward to
 *    the start and is reduced one-by-one on the next trigger. When the buffer index
 *    hits the start, it goes backward to the upper level and increases one-by-one
 *    on the next trigger.
 * One-Time-Scan mode - The buffer index can only be increased on the next trigger.
 *    When the buffer index hits the upper level, it is not updated by the trigger.
 * FIFO mode
 */
typedef enum _dac_buff_work_mode
{
    kDacBuffWorkAsNormalMode = 0U, /*!< Buffer works as Normal. */
    kDacBuffWorkAsSwingMode = 1U, /*!< Buffer works as swing. */
    kDacBuffWorkAsOneTimeScanMode = 2U, /*!< Buffer works as one time scan.*/
    kDacBuffWorkAsFIFOMode = 3U /*!< Buffer works as FIFO.*/
} dac_buff_work_mode_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Resets all configurable registers to be in the reset state for DAC.
 *
 * This function resets all configurable registers to be in the reset state for DAC.
 * It should be called before configuring the DAC module.
 *
 * @param baseAddr The DAC peripheral base address.
 */
void DAC_HAL_Init(uint32_t baseAddr);

/*!
 * @brief Sets the 12-bit value for the DAC items in the buffer.
 *
 * This function sets the value assembled by the low 8 bits and high 4
 * bits of 12-bit DAC item in the buffer.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param index Buffer index.
 * @param value Setting value.
 */
void DAC_HAL_SetBuffValue(uint32_t baseAddr, uint8_t index, uint16_t value);

/*!
 * @brief Gets the 12-bit value from the DAC item in the buffer.
 *
 * This function gets the value assembled by the low 8 bits and high 4
 * bits of 12-bit DAC item in the buffer.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param index Buffer index.
 * @return Current setting value.
 */
uint16_t DAC_HAL_GetBuffValue(uint32_t baseAddr, uint8_t index);

/*!
 * @brief Clears the flag of the DAC buffer read pointer.
 *
 * This function clears the flag of the DAC buffer read pointer when it hits the
 * bottom position.
 *
 * @param baseAddr The DAC peripheral base address.
 */
static inline void DAC_HAL_ClearBuffIndexUpperFlag(uint32_t baseAddr)
{
    BW_DAC_SR_DACBFRPBF(baseAddr, 0U);
}

/*!
 * @brief Gets the flag of DAC buffer read pointer when it hits the bottom position.
 *
 * This function gets the flag of DAC buffer read pointer when it hits the
 * bottom position.
 *
 * @param baseAddr The DAC peripheral base address.
 * @return Assertion of indicated event.
 */
static inline bool DAC_HAL_GetBuffIndexUpperFlag(uint32_t baseAddr)
{
    return ( 1U == BR_DAC_SR_DACBFRPBF(baseAddr) );
}

/*!
 * @brief Clears the flag of the DAC buffer read pointer when it hits the top position.
 *
 * This function clears the flag of the DAC buffer read pointer when it hits the
 * top position.
 *
 * @param baseAddr The DAC peripheral base address.
 */
static inline void DAC_HAL_ClearBuffIndexStartFlag(uint32_t baseAddr)
{
    BW_DAC_SR_DACBFRPTF(baseAddr, 0U);
}

/*!
 * @brief Gets the flag of the DAC buffer read pointer when it hits the top position.
 *
 * This function gets the flag of the DAC buffer read pointer when it hits the
 * top position.
 *
 * @param baseAddr The DAC peripheral base address.
 * @return Assertion of indicated event.
 */
static inline bool DAC_HAL_GetBuffIndexStartFlag(uint32_t baseAddr)
{
    return ( 1U == BR_DAC_SR_DACBFRPTF(baseAddr) );
}

#if FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION

/*!
 * @brief Gets the flag of the DAC buffer read pointer when it hits the watermark position.
 *
 * This function gets the flag of the DAC buffer read pointer when it hits the
 * watermark position.
 *
 * @param baseAddr The DAC peripheral base address.
 * @return Assertion of indicated event.
 */
static inline bool DAC_HAL_GetBuffIndexWatermarkFlag(uint32_t baseAddr)
{
    return ( 1U == BR_DAC_SR_DACBFWMF(baseAddr) );
}

/*!
 * @brief Clears the flag of the DAC buffer read pointer when it hits the watermark position.
 *
 * This function clears the flag of the DAC buffer read pointer when it hits the
 * watermark position.
 *
 * @param baseAddr The DAC peripheral base address.
 * @return Assertion of indicated event.
 */
static inline void DAC_HAL_ClearBuffIndexWatermarkFlag(uint32_t baseAddr)
{
    BW_DAC_SR_DACBFWMF(baseAddr, 0U);
}
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */

/*!
 * @brief Enables the Programmable Reference Generator.
 *
 * This function enables the Programmable Reference Generator. Then the
 * DAC system is enabled.
 *
 * @param baseAddr The DAC peripheral base address.
 */
static inline void DAC_HAL_Enable(uint32_t baseAddr)
{
    BW_DAC_C0_DACEN(baseAddr, 1U);
}

/*!
 * @brief Disables the Programmable Reference Generator.
 *
 * This function disables the Programmable Reference Generator. Then the
 * DAC system is disabled.
 *
 * @param baseAddr The DAC peripheral base address.
 */
static inline void DAC_HAL_Disable(uint32_t baseAddr)
{
    BW_DAC_C0_DACEN(baseAddr, 0U);
}

/*!
 * @brief Sets the reference voltage source mode for the DAC module.
 *
 * This function sets the reference voltage source mode for the DAC module. 
 *
 * @param baseAddr The DAC peripheral base address.
 * @param mode Selection of enumeration mode. See to "dac_ref_volt_src_mode_t".
 */
static inline void DAC_HAL_SetRefVoltSrcMode(uint32_t baseAddr, dac_ref_volt_src_mode_t mode)
{
    BW_DAC_C0_DACRFS(baseAddr, ((kDacRefVoltSrcOfVref1==mode)?0U:1U) );
}

/*!
 * @brief Sets the trigger mode for the DAC module.
 *
 * This function sets the trigger mode for the DAC module. 
 *
 * @param baseAddr The DAC peripheral base address.
 * @param mode Selection of enumeration mode. See to "dac_trigger_mode_t".
 */
static inline void DAC_HAL_SetTriggerMode(uint32_t baseAddr, dac_trigger_mode_t mode)
{
    BW_DAC_C0_DACTRGSEL(baseAddr, ((kDacTriggerByHardware==mode)?0U:1U) );
}

/*!
 * @brief Triggers the converter with software.
 *
 * This function triggers the converter with software. If the DAC software
 * trigger is selected and buffer enabled, calling this API advances the
 * buffer read pointer once.
 *
 * @param baseAddr The DAC peripheral base address.
 */
static inline void DAC_HAL_SetSoftTriggerCmd(uint32_t baseAddr)
{
    BW_DAC_C0_DACSWTRG(baseAddr, 1U);
}

/*!
 * @brief Switches to enable working in low power mode for the DAC module.
 *
 * This function switches to enable working in low power mode for the DAC module.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param enable Switcher to assert the feature.
 */
static inline void DAC_HAL_SetLowPowerCmd(uint32_t baseAddr, bool enable)
{
    BW_DAC_C0_LPEN(baseAddr, (enable?1U:0U) );
}

#if FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
/*!
 * @brief Switches to enable the interrupt when buffer read pointer hits the watermark position.
 *
 * This function switches to enable the interrupt when the buffer read pointer hits
 * the watermark position.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param enable Switcher to assert the feature.
 */
static inline void DAC_HAL_SetBuffIndexWatermarkIntCmd(uint32_t baseAddr, bool enable)
{
    BW_DAC_C0_DACBWIEN(baseAddr, (enable?1U:0U) );
}
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */

/*!
 * @brief Switches to enable the interrupt when the buffer read pointer hits the top position.
 *
 * This function switches to enable the interrupt when the buffer read pointer hits
 * the top position.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param enable Switcher to assert the feature.
 */
static inline void DAC_HAL_SetBuffIndexStartIntCmd(uint32_t baseAddr, bool enable)
{
    BW_DAC_C0_DACBTIEN(baseAddr, (enable?1U:0U) );
}

/*!
 * @brief Switches to enable the interrupt when the buffer read pointer hits the bottom position.
 *
 * This function switches to enable the interrupt when the buffer read pointer hits
 * the bottom position.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param enable Switcher to assert the feature.
 */
static inline void DAC_HAL_SetBuffIndexUpperIntCmd(uint32_t baseAddr, bool enable)
{
    BW_DAC_C0_DACBBIEN(baseAddr, (enable?1U:0U) );
}

/*!
 * @brief Switches to enable the DMA for DAC.
 *
 * This function switches to enable the DMA for the DAC module. When the DMA is enabled,
 * DMA request is generated by the original interrupts, which are
 * not presented on this module at the same time.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param enable Switcher to assert the feature.
 */
static inline void DAC_HAL_SetDmaCmd(uint32_t baseAddr, bool enable)
{
    BW_DAC_C1_DMAEN(baseAddr, (enable?1U:0U) );
}

#if FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
/*!
 * @brief Sets the watermark mode of the buffer for the DAC module.
 *
 * This function sets the watermark mode of the buffer for the DAC module.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param mode Selection of enumeration mode. See to "dac_buff_watermark_mode_t".
 */
static inline void DAC_HAL_SetBuffWatermarkMode(uint32_t baseAddr, dac_buff_watermark_mode_t mode)
{
    BW_DAC_C1_DACBFWM(baseAddr, (uint8_t)mode);
}
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */

/*!
 * @brief Sets the work mode of the buffer for the DAC module.
 *
 * This function sets the work mode of the buffer for the DAC module.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param mode Selection of enumeration mode. See to "dac_buff_work_mode_t".
 */
static inline void DAC_HAL_SetBuffWorkMode(uint32_t baseAddr, dac_buff_work_mode_t mode)
{
    BW_DAC_C1_DACBFMD(baseAddr, (uint8_t)mode );
}

/*!
 * @brief Switches to enable the buffer for the DAC module.
 *
 * This function switches to enable the buffer for the DAC module.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param enable Switcher to assert the feature.
 */
static inline void DAC_HAL_SetBuffCmd(uint32_t baseAddr, bool enable)
{
    BW_DAC_C1_DACBFEN(baseAddr, (enable?1U:0U) );
}

/*!
 * @brief Gets the buffer index upper limitation for the DAC module.
 *
 * This function gets the upper buffer index upper limitation for the DAC module.
 *
 * @param baseAddr The DAC peripheral base address.
 * @return Value of buffer index upper limitation.
 */
static inline uint8_t DAC_HAL_GetBuffUpperIndex(uint32_t baseAddr)
{
    return BR_DAC_C2_DACBFUP(baseAddr);
}

/*!
 * @brief Sets the buffer index upper limitation for the DAC module.
 *
 * This function sets the upper buffer index upper limitation for the DAC module.
 *
 * @param baseAddr The DAC peripheral base address.
 * @param index Setting value of upper limitation for buffer index.
 */
static inline void DAC_HAL_SetBuffUpperIndex(uint32_t baseAddr, uint8_t index)
{
    assert(index < HW_DAC_DATnL_COUNT);
    BW_DAC_C2_DACBFUP(baseAddr , index);
}

/*!
 * @brief Gets the current buffer index upper limitation for the DAC module.
 *
 * This function gets the current buffer index for the DAC module.
 *
 * @param baseAddr The DAC peripheral base address.
 * @return Value of current buffer index.
 */
static inline uint8_t DAC_HAL_GetBuffCurrentIndex(uint32_t baseAddr)
{
    return BR_DAC_C2_DACBFRP(baseAddr);
}

/*!
 * @brief Sets the buffer index for the DAC module.
 *
 * This function sets the upper buffer index for the DAC module.
 *
 * @param baseAddr the DAC peripheral base address.
 * @param index Setting value for buffer index.
 */
static inline void DAC_HAL_SetBuffCurrentIndex(uint32_t baseAddr, uint8_t index)
{
    assert(index < HW_DAC_DATnL_COUNT);
    BW_DAC_C2_DACBFRP(baseAddr, index);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_DAC_HAL_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

