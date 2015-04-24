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
 
#ifndef __FSL_ADC_HAL_H__
#define __FSL_ADC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_adc_features.h"

/*!
 * @addtogroup adc_hal
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*!
 * @brief ADC status return codes.
 */
typedef enum _adc_status 
{
    kStatus_ADC_Success         = 0U, /*!< Success. */
    kStatus_ADC_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_ADC_Failed          = 2U  /*!< Execution failed. */
} adc_status_t;

#if FSL_FEATURE_ADC_HAS_MUX_SELECT

/*!
 * @brief Defines the type of the enumerating channel multiplexer mode for each channel.
 * 
 * For some ADC channels, there are two selections for the channel multiplexer. For
 * example, ADC0_SE4a and ADC0_SE4b are the different channels but share the same
 * channel number.
 */
typedef enum _adc_chn_mux_mode
{
    kAdcChnMuxOfA = 0U, /*!< For channel with channel mux a. */
    kAdcChnMuxOfB = 1U, /*!< For channel with channel mux b. */
    kAdcChnMuxOfDefault = kAdcChnMuxOfA /*!< For channel without any channel mux identifier. */
} adc_chn_mux_mode_t;
#endif /* FSL_FEATURE_ADC_HAS_MUX_SELECT */

/*!
 * @brief Defines the type of the enumerating divider for the converter.
 */
typedef enum _adc_clk_divider_mode
{
    kAdcClkDividerInputOf1 = 0U, /*!< For divider 1 from the input clock to ADC. */
    kAdcClkDividerInputOf2 = 1U, /*!< For divider 2 from the input clock to ADC. */
    kAdcClkDividerInputOf4 = 2U, /*!< For divider 4 from the input clock to ADC. */
    kAdcClkDividerInputOf8 = 3U  /*!< For divider 8 from the input clock to ADC. */
} adc_clk_divider_mode_t;

/*!
 *@brief Defines the type of the enumerating resolution for the converter.
 */
typedef enum _adc_resolution_mode
{
    kAdcResolutionBitOf8or9 = 0U,
        /*!< 8-bit for single end sample, or 9-bit for differential sample. */
    kAdcResolutionBitOfSingleEndAs8 = kAdcResolutionBitOf8or9, /*!< 8-bit for single end sample. */
    kAdcResolutionBitOfDiffModeAs9 = kAdcResolutionBitOf8or9, /*!< 9-bit for differential sample. */
    
    kAdcResolutionBitOf12or13 = 1U,
        /*!< 12-bit for single end sample, or 13-bit for differential sample. */
    kAdcResolutionBitOfSingleEndAs12 = kAdcResolutionBitOf12or13, /*!< 12-bit for single end sample. */
    kAdcResolutionBitOfDiffModeAs13 = kAdcResolutionBitOf12or13, /*!< 13-bit for differential sample. */
    
    kAdcResolutionBitOf10or11 = 2U,
        /*!< 10-bit for single end sample, or 11-bit for differential sample. */
    kAdcResolutionBitOfSingleEndAs10 = kAdcResolutionBitOf10or11, /*!< 10-bit for single end sample. */
    kAdcResolutionBitOfDiffModeAs11 = kAdcResolutionBitOf10or11 /*!< 11-bit for differential sample. */
#if (FSL_FEATURE_ADC_MAX_RESOLUTION>=16)
    , kAdcResolutionBitOf16 = 3U,
        /*!< 16-bit for both single end sample and differential sample. */
    kAdcResolutionBitOfSingleEndAs16 = kAdcResolutionBitOf16, /*!< 16-bit for single end sample. */
    kAdcResolutionBitOfDiffModeAs16 = kAdcResolutionBitOf16 /*!< 16-bit for differential sample. */

#endif /* FSL_FEATURE_ADC_MAX_RESOLUTION */
} adc_resolution_mode_t;

/*!
 * @brief Defines the type of the enumerating source of the input clock.
 */
typedef enum _adc_clk_src_mode
{
    kAdcClkSrcOfBusClk = 0U, /*!< For input as bus clock. */
    kAdcClkSrcOfBusOrAltClk2 = 1U, /*!< For input as bus clock /2 or AltClk2. */
    kAdcClkSrcOfAltClk = 2U, /*!< For input as alternate clock (ALTCLK). */
    kAdcClkSrcOfAsynClk = 3U /*!< For input as asynchronous clock (ADACK). */
} adc_clk_src_mode_t;

/*
 * @brief Defines the type of the enumerating long sample cycles.
 */
typedef enum _adc_long_sample_cycle_mode
{
    kAdcLongSampleCycleOf24 = 0U, /*!< 20 extra ADCK cycles, 24 ADCK cycles total. */
    kAdcLongSampleCycleOf16 = 1U, /*!< 12 extra ADCK cycles, 16 ADCK cycles total. */
    kAdcLongSampleCycleOf10 = 2U, /*!< 6 extra ADCK cycles, 10 ADCK cycles total. */
    kAdcLongSampleCycleOf4 = 3U /*!< 2 extra ADCK cycles, 6 ADCK cycles total. */
} adc_long_sample_cycle_mode_t;

/*
 * @brief Defines the type of the enumerating reference voltage source.
 */
typedef enum _adc_ref_volt_src_mode
{
    kAdcRefVoltSrcOfVref = 0U, /*!< For external pins pair of VrefH and VrefL. */
    kAdcRefVoltSrcOfValt = 1U /*!< For alternate reference pair of ValtH and ValtL.*/
} adc_ref_volt_src_mode_t;

#if FSL_FEATURE_ADC_HAS_HW_AVERAGE

/*
 * @brief Defines the type of the enumerating hardware average mode.
 */
typedef enum _adc_hw_average_count_mode
{
    kAdcHwAverageCountOf4 = 0U, /*!< For hardware average with 4 samples. */
    kAdcHwAverageCountOf8 = 1U, /*!< For hardware average with 8 samples. */
    kAdcHwAverageCountOf16 = 2U, /*!< For hardware average with 16 samples. */
    kAdcHwAverageCountOf32 = 3U /*!< For hardware average with 32 samples. */
} adc_hw_average_count_mode_t;

#endif /* FSL_FEATURE_ADC_HAS_HW_AVERAGE */

/*!
 * @brief Defines the type of the enumerating asserted range in the hardware compare. 
 *
 * When the internal CMP is enabled, the COCO flag, which represents the complement
 * of the conversion, is not asserted if the sample value is not in the indicated
 * range. Eventually, the data of conversion result  is not kept in the result
 * data register. The two values, cmpValue1 and cmpValue2, mark
 * the thresholds  with the comparator feature.
 * kAdcHwCmpRangeModeOf1:
 *      Both greater than and in range switchers  are disabled.
 *      The available range is "< cmpValue1".
 * kAdcHwCmpRangeModeOf2:
 *      Greater than switcher  is enabled while the in range switcher is disabled.
 *      The available range is " > cmpValue1".
 * kAdcHwCmpRangeModeOf3:
 *      Greater than switcher  is disabled while in range switcher is enabled.
 *      The available range is "< cmpValue1" or "> cmpValue2" when
 *      cmpValue1 <= cmpValue2, or "< cmpValue1" and "> cmpValue2" when
 *      cmpValue1 >= cmpValue2.
 * kAdcHwCmpRangeModeOf4:
 *      Both greater than and in range switchers are enabled.
 *      The available range is "> cmpValue1" and "< cmpValue2" when
 *      cmpValue1 <= cmpValue2, or "> cmpValue1" or "< cmpValue2" when
 *      cmpValue1 < cmpValue2.
 */
typedef enum _adc_hw_cmp_range_mode
{
    kAdcHwCmpRangeModeOf1 = 0U, /*!< For selection mode 1. */
    kAdcHwCmpRangeModeOf2 = 1U, /*!< For selection mode 2. */
    kAdcHwCmpRangeModeOf3 = 2U, /*!< For selection mode 3. */
    kAdcHwCmpRangeModeOf4 = 3U  /*!< For selection mode 4. */
} adc_hw_cmp_range_mode_t;

#if FSL_FEATURE_ADC_HAS_PGA

/*!
 * @brief Defines the type of enumerating PGA's Gain mode.
 */
typedef enum _adc_pga_gain_mode
{
    kAdcPgaGainValueOf1 = 0U, /*!< For amplifier gain of 1.*/
    kAdcPgaGainValueOf2 = 1U, /*!< For amplifier gain of 2.*/
    kAdcPgaGainValueOf4 = 2U, /*!< For amplifier gain of 4.*/
    kAdcPgaGainValueOf8 = 3U, /*!< For amplifier gain of 8.*/
    kAdcPgaGainValueOf16 = 4U, /*!< For amplifier gain of 16.*/
    kAdcPgaGainValueOf32 = 5U, /*!< For amplifier gain of 32.*/
    kAdcPgaGainValueOf64 = 6U  /*!< For amplifier gain of 64.*/
} adc_pga_gain_mode_t;

#endif /* FSL_FEATURE_ADC_HAS_PGA */

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/


/*!
 * @brief Resets all registers into a known state for the ADC module.
 *
 * This function resets all registers into a known state for the ADC
 * module. This known state is the reset value indicated by the Reference
 * manual. It is strongly recommended to call this API before any other operation
 * when initializing the ADC module.
 *
 * @param baseAddr Register base address for the module.
 */
void ADC_HAL_Init(uint32_t baseAddr);

/*!
 * @brief Configures the conversion channel for the ADC module.
 *
 * This function configures the channel for the ADC module. At any point, 
 * only one of the configuration groups takes effect. The other channel mux of
 * the first group (group A, 0) is only for the hardware trigger. Both software and
 * hardware trigger can be used to the first group. When in software trigger
 * mode, once the available channel is set, the conversion begins to execute.
 *
 * @param baseAddr Register base address for the module.
 * @param chnGroup Channel configuration group ID.
 * @param intEnable Switcher to enable interrupt when conversion is completed.
 * @param diffEnable Switcher to enable differential channel mode.
 * @param chnNum ADC channel for next conversion.
 */
static inline void ADC_HAL_ConfigChn(uint32_t baseAddr, uint32_t chnGroup,
    bool intEnable, bool diffEnable, uint8_t chnNum)
{
    assert(chnGroup < FSL_FEATURE_ADC_CONVERSION_CONTROL_COUNT);

#if FSL_FEATURE_ADC_HAS_DIFF_MODE  
    HW_ADC_SC1n_WR(baseAddr, chnGroup, \
        (   (intEnable ? BM_ADC_SC1n_AIEN : 0U) \
          | ( (diffEnable)? BM_ADC_SC1n_DIFF : 0U) \
          | BF_ADC_SC1n_ADCH(chnNum) \
        ) );
#else
    HW_ADC_SC1n_WR(baseAddr, chnGroup, \
        (   (intEnable ? BM_ADC_SC1n_AIEN : 0U) \
          | BF_ADC_SC1n_ADCH(chnNum) \
        ) );

#endif /* FSL_FEATURE_ADC_HAS_DIFF_MODE */

}

#if FSL_FEATURE_ADC_HAS_DIFF_MODE

/*!
 * @brief Checks whether the channel differential mode is enabled.
 *
 * This function checks whether the channel differential mode for
 *  is enabled.
 *
 * @param baseAddr Register base address for the module.
 * @param chnGroup Channel configuration group ID.
 * @return Assertion of enabling differential mode.
 */
static inline bool ADC_HAL_GetChnDiffCmd(uint32_t baseAddr, uint32_t chnGroup)
{
    assert(chnGroup < FSL_FEATURE_ADC_CONVERSION_CONTROL_COUNT);
    return (1U == BR_ADC_SC1n_DIFF(baseAddr, chnGroup));
}
#endif /* FSL_FEATURE_ADC_HAS_DIFF_MODE */

/*!
 * @brief Checks whether the channel conversion  is completed.
 *
 * This function checks whether the channel conversion for the ADC
 * module is completed.
 *
 * @param baseAddr Register base address for the module.
 * @param chnGroup Channel configuration group ID.
 * @return Assertion of completed conversion mode.
 */
static inline bool ADC_HAL_GetChnConvCompletedCmd(uint32_t baseAddr, uint32_t chnGroup)
{
    assert(chnGroup < FSL_FEATURE_ADC_CONVERSION_CONTROL_COUNT);
    return (1U == BR_ADC_SC1n_COCO(baseAddr, chnGroup) );
}

/*!
 * @brief Switches to enable the low power mode for ADC module.
 *
 * This function switches to enable the low power mode for ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetLowPowerCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_CFG1_ADLPC(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Selects the clock divider mode for the ADC module.
 *
 * This function selects the clock divider mode for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of mode enumeration. See to "adc_clk_divider_mode_t".
 */
static inline void ADC_HAL_SetClkDividerMode(uint32_t baseAddr, adc_clk_divider_mode_t mode)
{
    BW_ADC_CFG1_ADIV(baseAddr, (uint32_t)mode );
}

/*!
 * @brief Switches to enable the long sample mode for the ADC module.
 *
 * This function switches to enable the long sample mode for the ADC module.
 * This function adjusts the sample period to allow the higher impedance inputs to
 * be accurately sampled or to maximize the conversion speed for the lower impedance
 * inputs. Longer sample times can also be used to lower overall power
 * consumption if the continuous conversions are enabled and the high conversion rates
 * are not required. If the long sample mode is enabled, more configuration
 * is set by calling the "ADC_HAL_SetLongSampleCycleMode()" function.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetLongSampleCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_CFG1_ADLSMP(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Selects the conversion resolution mode for ADC module.
 *
 * This function selects the conversion resolution mode for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of mode enumeration. See to "adc_resolution_mode_t".
 */
static inline void ADC_HAL_SetResolutionMode(uint32_t baseAddr, adc_resolution_mode_t mode)
{
    BW_ADC_CFG1_MODE(baseAddr, (uint32_t)mode );
}

/*!
 * @brief Gets the conversion resolution mode for ADC module.
 *
 * This function gets the conversion resolution mode for the ADC module.
 * It is specially used when processing the conversion result of RAW format.
 *
 * @param baseAddr Register base address for the module.
 * @return Current conversion resolution mode.
 */
static inline adc_resolution_mode_t ADC_HAL_GetResolutionMode(uint32_t baseAddr)
{
    return (adc_resolution_mode_t)( BR_ADC_CFG1_MODE(baseAddr) );
}

/*!
 * @brief Selects the input clock source for the ADC module.
 *
 * This function selects the input clock source for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of mode enumeration. See to "adc_clk_src_mode_t".
 */
static inline void ADC_HAL_SetClkSrcMode(uint32_t baseAddr, adc_clk_src_mode_t mode)
{
    BW_ADC_CFG1_ADICLK(baseAddr, (uint32_t)mode );
}

#if FSL_FEATURE_ADC_HAS_MUX_SELECT

/*!
 * @brief Selects the channel mux mode for the ADC module.
 *
 * This function selects the channel mux mode for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of mode enumeration. See to "adc_chn_mux_mode_t".
 */
static inline void ADC_HAL_SetChnMuxMode(uint32_t baseAddr, adc_chn_mux_mode_t mode)
{
    BW_ADC_CFG2_MUXSEL(baseAddr, ((kAdcChnMuxOfA == mode) ? 0U : 1U) );
}

/*!
 * @brief Gets the current channel mux mode for the ADC module.
 *
 * This function selects the channel mux mode for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @return Selection of mode enumeration. See to "adc_chn_mux_mode_t".
 */
static inline adc_chn_mux_mode_t ADC_HAL_GetChnMuxMode(uint32_t baseAddr)
{
    return (adc_chn_mux_mode_t)(BR_ADC_CFG2_MUXSEL(baseAddr) );
}

#endif /* FSL_FEATURE_ADC_HAS_MUX_SELECT */

/*!
 * @brief Switches to enable the asynchronous clock for the ADC module.
 *
 * This function switches to enable the asynchronous clock for the ADC module. 
 * It enables the ADC's asynchronous clock source and the clock source
 * output regardless of the conversion and the input clock select status of the
 * ADC. Asserting this function allows the clock to be used even while the ADC
 * is idle or operating from a different clock source. Also, latency of
 * initiating a single or first-continuous conversion with the asynchronous
 * clock selected is reduced since the ADC internal clock has been already
 * operational.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetAsyncClkCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_CFG2_ADACKEN(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Switches to enable the high speed mode for the ADC module.
 *
 * This function switches to enable the high speed mode for the ADC module. 
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetHighSpeedCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_CFG2_ADHSC(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Selects the long sample cycle mode for the ADC module.
 *
 * This function selects the long sample cycle mode for the ADC module.
 * This function should be called along with "ADC_HAL_SetLongSampleCmd()".
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of long sample cycle mode. See the "adc_long_sample_cycle_mode_t".
 */
static inline void ADC_HAL_SetLongSampleCycleMode(uint32_t baseAddr,
    adc_long_sample_cycle_mode_t mode)
{
    BW_ADC_CFG2_ADLSTS(baseAddr, (uint32_t)mode );
}

/*!
 * @brief Gets the raw result data of channel conversion for the ADC module.
 *
 * This function gets the result data of conversion for the ADC module.
 * The return value is raw data  that is not processed. The unavailable bits would be
 * filled with "0" in single-ended mode and sign bit in differential mode. 
 *
 * @param baseAddr Register base address for the module.
 * @param chnGroup Channel configuration group ID.
 * @return Conversion value of RAW.
 */
static inline uint16_t ADC_HAL_GetChnConvValueRAW(uint32_t baseAddr,
    uint32_t chnGroup )
{
    assert(chnGroup < FSL_FEATURE_ADC_CONVERSION_CONTROL_COUNT);
    return (uint16_t)(BR_ADC_Rn_D(baseAddr, chnGroup) );
}

/*!
 * @brief Sets the compare value of the lower limitation for the ADC module.
 *
 * This function sets the compare value of the lower limitation for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param value Setting value.
 */
static inline void ADC_HAL_SetHwCmpValue1(uint32_t baseAddr, uint16_t value)
{
    BW_ADC_CV1_CV(baseAddr,value);
}

/*!
 * @brief Sets the compare value of the higher limitation for the ADC module.
 *
 * This function sets the compare value of the higher limitation for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param value Setting value.
 */
static inline void ADC_HAL_SetHwCmpValue2(uint32_t baseAddr, uint16_t value)
{
    BW_ADC_CV2_CV(baseAddr,value);
}

/*!
 * @brief Checks whether the converter is active for the ADC module.
 *
 * This function checks  whether the converter is active for the ADC
 * module. If it is dis-asserted when the conversion is completed, one of the
 * completed flag is asserted for the indicated group mux. See the
 * "ADC_HAL_GetChnConvCompletedCmd()".
 *
 * @param baseAddr Register base address for the module.
 * @return Assertion of that the converter is active.
 */
static inline bool ADC_HAL_GetConvActiveCmd(uint32_t baseAddr)
{
    return (1U == BR_ADC_SC2_ADACT(baseAddr) );
}

/*!
 * @brief Switches to enable the hardware trigger mode for the ADC module.
 *
 * This function switches to enable the hardware trigger mode for the ADC
 * module.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetHwTriggerCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_SC2_ADTRG(baseAddr,(enable ? 1U : 0U) );
}

/*!
 * @brief Switches to enable the hardware comparator for the ADC module.
 *
 * This function switches to enable the hardware comparator for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetHwCmpCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_SC2_ACFE(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Switches to enable the setting that is greater than the hardware comparator.
 *
 * This function switches to enable the setting that is greater than the
 * hardware comparator.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetHwCmpGreaterCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_SC2_ACFGT(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Switches to enable the setting of the range for hardware comparator.
 *
 * This function switches to enable the setting of range for the hardware
 * comparator.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetHwCmpRangeCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_SC2_ACREN(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Configures the asserted range of the hardware comparator for the ADC module.
 *
 * This function configures the asserted range of the hardware comparator for the
 * ADC module. 
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of range mode, see to "adc_hw_cmp_range_mode_t".
 */
void ADC_HAL_SetHwCmpMode(uint32_t baseAddr, adc_hw_cmp_range_mode_t mode);

#if FSL_FEATURE_ADC_HAS_DMA

/*!
 * @brief Switches to enable the DMA for the ADC module.
 *
 * This function switches to enable the DMA for the ADC module. When enabled, the
 * DMA request is asserted during the ADC conversion complete event, which is noted
 * by the assertion of any of the ADC channel completed flags.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetDmaCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_SC2_DMAEN(baseAddr, (enable ? 1U : 0U) );
}

#endif /* FSL_FEATURE_ADC_HAS_DMA */

/*!
 * @brief Selects the reference voltage source for the ADC module.
 *
 * This function selects the reference voltage source for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of asserted the feature.
 */
static inline void ADC_HAL_SetRefVoltSrcMode(uint32_t baseAddr, adc_ref_volt_src_mode_t mode)
{
    BW_ADC_SC2_REFSEL(baseAddr, (uint32_t)mode );
}

#if FSL_FEATURE_ADC_HAS_CALIBRATION

/*!
 * @brief Switches to enable the hardware calibration for the ADC module.
 *
 * This function launches the hardware calibration for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetAutoCalibrationCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_SC3_CAL(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Gets the hardware calibration status for the ADC module.
 *
 * This function gets the status whether the hardware calibration is active
 * for the ADC module. The return value holds on as asserted during the hardware
 * calibration. Then, it is cleared and dis-asserted after the
 * calibration.
 *
 * @param baseAddr Register base address for the module.
 */
static inline bool ADC_HAL_GetAutoCalibrationActiveCmd(uint32_t baseAddr)
{
    return (1U == BR_ADC_SC3_CAL(baseAddr) );
}

/*!
 * @brief Gets the hardware calibration status  for the ADC module.
 *
 * This function gets the status whether the hardware calibration has failed
 * for the ADC module. The return value  is asserted if there is anything wrong
 * with the hardware calibration.
 *
 * @param baseAddr Register base address for the module.
 */
static inline bool ADC_HAL_GetAutoCalibrationFailedCmd(uint32_t baseAddr)
{
    return (1U == BR_ADC_SC3_CALF(baseAddr) );
}

/*!
 * @brief Gets and calculates the plus side calibration parameter from the auto calibration.
 *
 * This function  gets the values of CLP0 - CLP4 and CLPS internally,
 * accumulates them, and returns the value that can be used to be set in the PG
 * register directly. Note that this API should be called after the process of
 * auto calibration is complete.
 *
 * @param baseAddr Register base address for the module.
 * @return value that can be set into PG directly.
 */
uint16_t ADC_HAL_GetAutoPlusSideGainValue(uint32_t baseAddr);

/*!
 * @brief Sets the plus side gain calibration value  for the ADC module.
 *
 * This function  sets the plus side gain calibration value  for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param value Setting value for plus side gain.
 */
static inline void ADC_HAL_SetPlusSideGainValue(uint32_t baseAddr, uint16_t value)
{
    BW_ADC_PG_PG(baseAddr, value);
}

#if FSL_FEATURE_ADC_HAS_DIFF_MODE

/*!
 * @brief Gets and calculates the minus side calibration parameter from the auto calibration.
 *
 * This function gets the values of CLM0 - CLM4 and CLMS internally,
 * accumulates them, and returns the value that can be used to be set in the MG
 * register directly. Note that this API should be called after the process of
 * auto calibration is complete.
 *
 * @param baseAddr Register base address for the module.
 * @return value that can be set into MG directly.
 */
uint16_t ADC_HAL_GetAutoMinusSideGainValue(uint32_t baseAddr);

/*!
 * @brief Sets the minus side gain calibration  value for the ADC module.
 *
 * This function sets the minus side gain calibration value for the ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param value Setting value for minus side gain.
 */
static inline void ADC_HAL_SetMinusSideGainValue(uint32_t baseAddr, uint16_t value)
{
    BW_ADC_MG_MG(baseAddr, value);
}

#endif /* FSL_FEATURE_ADC_HAS_DIFF_MODE */

#endif /* FSL_FEATURE_ADC_HAS_CALIBRATION */

#if FSL_FEATURE_ADC_HAS_OFFSET_CORRECTION

/*!
 * @brief Gets the offset correction value for the ADC module.
 *
 * This function gets the offset correction value for the ADC module. 
 * When auto calibration is executed, the OFS register holds the new value
 * generated by the calibration. It can be left as default or modified
 * according to the use case.
 *
 * @param baseAddr Register base address for the module.
 * @return current value for OFS.
 */
static inline uint16_t ADC_HAL_GetOffsetValue(uint32_t baseAddr)
{
    return (uint16_t)(BR_ADC_OFS_OFS(baseAddr) );
}

/*!
 * @brief Sets the offset correction value for the ADC module.
 *
 * This function sets the offset correction value for the ADC module. The ADC
 * offset correction register (OFS) contains the user-selected or calibration-generated
 * offset error correction value. The value in the offset correction
 * registers (OFS) is subtracted from the conversion and the result is
 * transferred into the result registers (Rn). If the result is above the
 * maximum or below the minimum result value, it is forced to the appropriate
 * limit for the current mode of operation. 
 *
 * @param baseAddr Register base address for the module.
 * @param value Setting value for OFS.
 */
static inline void ADC_HAL_SetOffsetValue(uint32_t baseAddr, uint16_t value)
{
    BW_ADC_OFS_OFS(baseAddr, value);
}

#endif /* FSL_FEATURE_ADC_HAS_OFFSET_CORRECTION */

/*!
 * @brief Switches to enable the continuous conversion mode for the ADC module.
 *
 * This function switches to enable the continuous conversion mode for the ADC
 * module. Once enabled, continuous conversions, or sets of conversions if the
 * hardware average function, is enabled after initiating a conversion.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetContinuousConvCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_SC3_ADCO(baseAddr, (enable ? 1U : 0U) );
}

#if FSL_FEATURE_ADC_HAS_HW_AVERAGE

/*!
 * @brief Switches to enable the hardware average for the ADC module.
 *
 * This function switches to enable the hardware average for the ADC module.
 * Once enabled, the conversion does not stop before the average
 * count has been reached.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted the feature.
 */
static inline void ADC_HAL_SetHwAverageCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_SC3_AVGE(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Selects the hardware average mode for the ADC module.
 *
 * This function switches to select the hardware average mode for the ADC
 * module.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of hardware average count mode, see to "adc_hw_average_count_mode_t".
 */
static inline void ADC_HAL_SetHwAverageMode(uint32_t baseAddr, adc_hw_average_count_mode_t mode)
{
    BW_ADC_SC3_AVGS(baseAddr, (uint32_t)mode );
}

#endif /* FSL_FEATURE_ADC_HAS_HW_AVERAGE */

#if FSL_FEATURE_ADC_HAS_PGA

/*!
 * @brief Switches to enable the Programmable Gain Amplifier for ADC module.
 *
 * This function enables the PGA for the ADC module. The Programmable Gain
 * Amplifier (PGA) is designed to increase the dynamic range by amplifying the
 * low-amplitude signals before they are fed to the 16 bit SAR ADC. 
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted feature.
 */
static inline void ADC_HAL_SetPgaCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_PGA_PGAEN(baseAddr, (enable ? 1U : 0U) );
}

/*!
 * @brief Switches to enable the PGA chopping mode for the ADC module.
 *
 * This function switches to enable the PGA chopping mode for the ADC module.
 * The PGA employs chopping to remove/reduce offset and 1/f noise and offers an
 * offset measurement configuration that aids the offset calibration. 
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted feature.
 */
static inline void ADC_HAL_SetPgaChoppingCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_PGA_PGACHPb(baseAddr, (enable ? 0U : 1U) );
}

/*!
 * @brief Switches to enable the PGA working in low power mode for the ADC module.
 *
 * This function switches to enable the PGA working in low power mode for
 * ADC module.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted feature.
 */
static inline void ADC_HAL_SetPgaLowPowerCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_PGA_PGALPb(baseAddr, (enable ? 0U : 1U) );
}

/*!
 * @brief Selects the amplifier mode for the PGA.
 *
 * This function selects the amplifier mode for the PGA.
 *
 * @param baseAddr Register base address for the module.
 * @param mode Selection of asserted feature. See to "adc_pga_gain_mode_t".
 */
static inline void ADC_HAL_SetPgaGainMode(uint32_t baseAddr, adc_pga_gain_mode_t mode)
{
    BW_ADC_PGA_PGAG(baseAddr, (uint32_t)mode );
}

/*!
 * @brief Switches to enable the offset measurement mode for the ADC module.
 *
 * This function switches to enable the offset measurement mode for the ADC
 * module. When asserted, the PGA disconnects  from the external inputs and
 * auto-configures into offset measurement mode. With this function asserted,
 * run the ADC in recommended settings and enable maximum hardware averaging
 * to get the PGA offset number. The output is the (PGA offset * (64+1))
 * for a given setting.
 *
 * @param baseAddr Register base address for the module.
 * @param enable Switcher to asserted feature.
 */
static inline void ADC_HAL_SetPgaOffsetMeasurementCmd(uint32_t baseAddr, bool enable)
{
    BW_ADC_PGA_PGAOFSM(baseAddr, (enable ? 1U : 0U) );
}

#endif /* FSL_FEATURE_ADC_HAS_PGA */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_ADC_HAL_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

