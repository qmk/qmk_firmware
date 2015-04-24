/**
  ******************************************************************************
  * @file    stm32f3xx_hal_adc_ex.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file containing functions prototypes of ADC HAL library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F3xx_ADC_EX_H
#define __STM32F3xx_ADC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"
   
/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx ADC Extended HAL module driver
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADCEx_Exported_Types ADC Extented Exported Types
  * @{
  */
struct __ADC_HandleTypeDef;

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Structure definition of ADC initialization and regular group  
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope entire ADC (affects regular and injected groups): ClockPrescaler, Resolution, DataAlign, 
  *            ScanConvMode, EOCSelection, LowPowerAutoWait.
  *          - Scope regular group: ContinuousConvMode, NbrOfConversion, DiscontinuousConvMode, NbrOfDiscConversion, ExternalTrigConvEdge, ExternalTrigConv, DMAContinuousRequests, Overrun.
  * @note   The setting of these parameters with function HAL_ADC_Init() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled
  *          - For all parameters except 'LowPowerAutoWait' and 'DMAContinuousRequests': ADC enabled without conversion on going on regular group.
  *          - For parameters 'LowPowerAutoWait' and 'DMAContinuousRequests': ADC enabled without conversion on going on regular and injected groups.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting without error reporting (as it can be the expected behaviour in case of intended action to update another parameter (which fullfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t ClockPrescaler;        /*!< Select ADC clock source (synchronous clock derived from AHB clock or asynchronous clock derived from ADC dedicated PLL 72MHz) and clock prescaler.
                                       The clock is common for all the ADCs.
                                       This parameter can be a value of @ref ADCEx_ClockPrescaler
                                       Note: In case of usage of channels on injected group, ADC frequency should be low than AHB clock frequency /4 for resolution 12 or 10 bits, 
                                             AHB clock frequency /3 for resolution 8 bits, AHB clock frequency /2 for resolution 6 bits.
                                       Note: In case of usage of the ADC dedicated PLL clock, this clock must be preliminarily enabled and prescaler set at RCC top level. 
                                       Note: This parameter can be modified only if all ADCs of the common ADC group are disabled (for products with several ADCs) */
  uint32_t Resolution;            /*!< Configures the ADC resolution. 
                                       This parameter can be a value of @ref ADCEx_Resolution */
  uint32_t DataAlign;             /*!< Specifies ADC data alignment to right (for resolution 12 bits: MSB on register bit 11 and LSB on register bit 0) (default setting)
                                       or to left (for resolution 12 bits, if offset disabled: MSB on register bit 15 and LSB on register bit 4, if offset enabled: MSB on register bit 14 and LSB on register bit 3).
                                       See reference manual for alignments with other resolutions.
                                       This parameter can be a value of @ref ADCEx_Data_align */
  uint32_t ScanConvMode;          /*!< Configures the sequencer of regular and injected groups.
                                       This parameter can be associated to parameter 'DiscontinuousConvMode' to have main sequence subdivided in successive parts.
                                       If disabled: Conversion is performed in single mode (one channel converted, the one defined in rank 1).
                                                    Parameters 'NbrOfConversion' and 'InjectedNbrOfConversion' are discarded (equivalent to set to 1).
                                       If enabled:  Conversions are performed in sequence mode (multiple ranks defined by 'NbrOfConversion'/'InjectedNbrOfConversion' and each channel rank).
                                                    Scan direction is upward: from rank1 to rank 'n'.
                                       This parameter can be a value of @ref ADCEx_Scan_mode */
  uint32_t EOCSelection;          /*!< Specifies what EOC (End Of Conversion) flag is used for conversion by polling and interruption: end of conversion of each rank or complete sequence.
                                       This parameter can be a value of @ref ADCEx_EOCSelection. */
  uint32_t LowPowerAutoWait;      /*!< Selects the dynamic low power Auto Delay: new conversion start only when the previous
                                       conversion (for regular group) or previous sequence (for injected group) has been treated by user software.
                                       This feature automatically adapts the speed of ADC to the speed of the system that reads the data. Moreover, this avoids risk of overrun for low frequency applications. 
                                       This parameter can be set to ENABLE or DISABLE.
                                       Note: Do not use with interruption or DMA (HAL_ADC_Start_IT(), HAL_ADC_Start_DMA()) since they have to clear immediately the EOC flag to free the IRQ vector sequencer.
                                             Do use with polling: 1. Start conversion with HAL_ADC_Start(), 2. Later on, when conversion data is needed: use HAL_ADC_PollForConversion() to ensure that conversion is completed
                                             and use HAL_ADC_GetValue() to retrieve conversion result and trig another conversion. */
  uint32_t ContinuousConvMode;    /*!< Specifies whether the conversion is performed in single mode (one conversion) or continuous mode for regular group,
                                       after the selected trigger occurred (software start or external trigger).
                                       This parameter can be set to ENABLE or DISABLE. */
  uint32_t NbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the regular group sequencer.
                                       To use the regular group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 16.
                                       Note: This parameter must be modified when no conversion is on going on regular group (ADC disabled, or ADC enabled without continuous mode or external trigger that could lauch a conversion). */
  uint32_t DiscontinuousConvMode; /*!< Specifies whether the conversions sequence of regular group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                       Discontinuous mode is used only if sequencer is enabled (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                       Discontinuous mode can be enabled only if continuous mode is disabled. If continuous mode is enabled, this parameter setting is discarded.
                                       This parameter can be set to ENABLE or DISABLE. */
  uint32_t NbrOfDiscConversion;   /*!< Specifies the number of discontinuous conversions in which the  main sequence of regular group (parameter NbrOfConversion) will be subdivided.
                                       If parameter 'DiscontinuousConvMode' is disabled, this parameter is discarded.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 8. */
  uint32_t ExternalTrigConv;      /*!< Selects the external event used to trigger the conversion start of regular group.
                                       If set to ADC_SOFTWARE_START, external triggers are disabled.
                                       This parameter can be a value of @ref ADCEx_External_trigger_source_Regular
                                       Caution: For devices with several ADCs, external trigger source is common to ADC common group (for example: ADC1&ADC2, ADC3&ADC4, if available)  */
  uint32_t ExternalTrigConvEdge;  /*!< Selects the external trigger edge of regular group.
                                       If trigger is set to ADC_SOFTWARE_START, this parameter is discarded.
                                       This parameter can be a value of @ref ADCEx_External_trigger_edge_Regular */
  uint32_t DMAContinuousRequests; /*!< Specifies whether the DMA requests are performed in one shot mode (DMA transfer stop when number of conversions is reached)
                                       or in Continuous mode (DMA transfer unlimited, whatever number of conversions).
                                       Note: In continuous mode, DMA must be configured in circular mode. Otherwise an overrun will be triggered when DMA buffer maximum pointer is reached.
                                       This parameter can be set to ENABLE or DISABLE.
                                       Note: This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled without continuous mode or external trigger that could lauch a conversion). */
  uint32_t Overrun;               /*!< Select the behaviour in case of overrun: data overwritten (default) or preserved.
                                       This parameter is for regular group only.
                                       This parameter can be a value of @ref ADCEx_Overrun
                                       Note: Case of overrun set to data preserved and usage with end on conversion interruption (HAL_Start_IT()): ADC IRQ handler has to clear end of conversion flags, this induces the release of the preserved data. If needed, this data can be saved into function HAL_ADC_ConvCpltCallback() (called before end of conversion flags clear).
                                       Note: Error reporting in function of conversion mode:
                                        - Usage with ADC conversion by polling for event or interruption: Error is reported only if overrun is set to data preserved. If overrun is set to data overwritten, user can willingly not read the conversion data each time, this is not considered as an erroneous case.
                                        - Usage with ADC conversion by DMA: Error is reported whatever overrun setting (DMA is expected to process all data from data register, any data missed would be abnormal). */
}ADC_InitTypeDef;

/** 
  * @brief  Structure definition of ADC channel for regular group  
  * @note   The setting of these parameters with function HAL_ADC_ConfigChannel() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled (this is the only possible ADC state to modify parameter 'SingleDiff')
  *          - For all except parameters 'SamplingTime', 'Offset', 'OffsetNumber': ADC enabled without conversion on going on regular group.
  *          - For parameters 'SamplingTime', 'Offset', 'OffsetNumber': ADC enabled without conversion on going on regular and injected groups.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behaviour in case of intended action to update another parameter (which fulfills the ADC state condition) on the fly).
  */
typedef struct 
{
  uint32_t Channel;                /*!< Specifies the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADCEx_channels
                                        Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability. */
  uint32_t Rank;                   /*!< Specifies the rank in the regular group sequencer.
                                        This parameter can be a value of @ref ADCEx_regular_rank
                                        Note: In case of need to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by the new channel setting (or parameter number of conversions can be adjusted) */
  uint32_t SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        Conversion time is the addition of sampling time and processing time (12.5 ADC clock cycles at ADC resolution 12 bits, 10.5 cycles at 10 bits, 8.5 cycles at 8 bits, 6.5 cycles at 6 bits).
                                        This parameter can be a value of @ref ADCEx_sampling_times
                                        Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                 If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                        Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                              sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                              Refer to device datasheet for timings values, parameters TS_vrefint, TS_vbat, TS_temp (values rough order: 2.2us min). */
  uint32_t SingleDiff;             /*!< Selection of single-ended or differential input.
                                        In differential mode: Differential measurement is between the selected channel 'i' (positive input) and channel 'i+1' (negative input).
                                                              Only channel 'i' has to be configured, channel 'i+1' is configured automatically.
                                        This parameter must be a value of @ref ADCEx_SingleDifferential
                                        Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                 If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                        Note: Channels 1 to 14 are available in differential mode. Channels 15, 16, 17, 18 can be used only in single-ended mode.
                                        Note: When configuring a channel 'i' in differential mode, the channel 'i+1' is not usable separately.
                                        Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion).
                                              If ADC is enabled, this parameter setting is bypassed without error reporting (as it can be the expected behaviour in case of another parameter update on the fly) */
  uint32_t OffsetNumber;           /*!< Selects the offset number
                                        This parameter can be a value of @ref ADCEx_OffsetNumber
                                        Caution: Only one channel is allowed per channel. If another channel was on this offset number, the offset will be changed to the new channel */
  uint32_t Offset;                 /*!< Defines the offset to be subtracted from the raw converted data when convert channels.
                                        Offset value must be a positive number.
                                        Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively.
                                        Note: This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled without continuous mode or external trigger that could lauch a conversion). */
}ADC_ChannelConfTypeDef;

/** 
  * @brief  Structure definition of ADC injected group and ADC channel for injected group  
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope channel: InjectedChannel, InjectedRank, InjectedSamplingTime , InjectedSingleDiff, InjectedOffsetNumber, InjectedOffset
  *          - Scope injected group (affects all channels of injected group): InjectedNbrOfConversion, InjectedDiscontinuousConvMode,
  *            AutoInjectedConv, QueueInjectedContext, ExternalTrigInjecConvEdge, ExternalTrigInjecConv.
  * @note   The setting of these parameters with function HAL_ADCEx_InjectedConfigChannel() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled (this is the only possible ADC state to modify parameter 'InjectedSingleDiff')
  *          - For parameters 'InjectedDiscontinuousConvMode', 'QueueInjectedContext': ADC enabled without conversion on going on injected group.
  *          - For parameters 'InjectedSamplingTime', 'InjectedOffset', 'InjectedOffsetNumber', 'AutoInjectedConv': ADC enabled without conversion on going on regular and injected groups.
  *          - For parameters 'InjectedChannel', 'InjectedRank', 'InjectedNbrOfConversion', 'ExternalTrigInjecConv', 'ExternalTrigInjecConvEdge': ADC enabled and while conversion on going on regular and injected groups.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting without error reporting (as it can be the expected behaviour in case of intended action to update another parameter (which fulfills the ADC state condition) on the fly).
  */
typedef struct 
{
  uint32_t InjectedChannel;               /*!< Configure the ADC injected channel
                                               This parameter can be a value of @ref ADCEx_channels
                                               Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability. */
  uint32_t InjectedRank;                  /*!< The rank in the regular group sequencer
                                               This parameter must be a value of @ref ADCEx_injected_rank
                                               Note: In case of need to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by the new channel setting (or parameter number of conversions can be adjusted) */
  uint32_t InjectedSamplingTime;          /*!< Sampling time value to be set for the selected channel.
                                               Unit: ADC clock cycles
                                               Conversion time is the addition of sampling time and processing time (12.5 ADC clock cycles at ADC resolution 12 bits, 10.5 cycles at 10 bits, 8.5 cycles at 8 bits, 6.5 cycles at 6 bits).
                                               This parameter can be a value of @ref ADCEx_sampling_times
                                               Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                        If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                               Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                                     sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                                     Refer to device datasheet for timings values, parameters TS_vrefint, TS_vbat, TS_temp (values rough order: 2.2us min). */
  uint32_t InjectedSingleDiff;            /*!< Selection of single-ended or differential input.
                                               In differential mode: Differential measurement is between the selected channel 'i' (positive input) and channel 'i+1' (negative input).
                                                              Only channel 'i' has to be configured, channel 'i+1' is configured automatically.
                                               This parameter must be a value of @ref ADCEx_SingleDifferential
                                               Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                        If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                               Note: Channels 1 to 14 are available in differential mode. Channels 15, 16, 17, 18 can be used only in single-ended mode.
                                               Note: When configuring a channel 'i' in differential mode, the channel 'i-1' is not usable separately.
                                               Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion).
                                                     If ADC is enabled, this parameter setting is bypassed without error reporting (as it can be the expected behaviour in case of another parameter update on the fly) */
  uint32_t InjectedOffsetNumber;          /*!< Selects the offset number
                                               This parameter can be a value of @ref ADCEx_OffsetNumber
                                               Caution: Only one channel is allowed per offset number. If another channel was on this offset number, the offset will be changed to the new channel. */
  uint32_t InjectedOffset;                /*!< Defines the offset to be subtracted from the raw converted data.
                                               Offset value must be a positive number.
                                               Depending of ADC resolution selected (12, 10, 8 or 6 bits),
                                               this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively. */
  uint32_t InjectedNbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the injected group sequencer.
                                               To use the injected group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                               This parameter must be a number between Min_Data = 1 and Max_Data = 4.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
  uint32_t InjectedDiscontinuousConvMode; /*!< Specifies whether the conversions sequence of injected group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                               Discontinuous mode is used only if sequencer is enabled (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                               Discontinuous mode can be enabled only if continuous mode is disabled. If continuous mode is enabled, this parameter setting is discarded.
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion).
                                               Note: For injected group, number of discontinuous ranks increment is fixed to one-by-one.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
  uint32_t AutoInjectedConv;              /*!< Enables or disables the selected ADC automatic injected group conversion after regular one
                                               This parameter can be set to ENABLE or DISABLE.      
                                               Note: To use Automatic injected conversion, discontinuous mode must be disabled ('DiscontinuousConvMode' and 'InjectedDiscontinuousConvMode' set to DISABLE)
                                               Note: To use Automatic injected conversion, injected group external triggers must be disabled ('ExternalTrigInjecConv' set to ADC_SOFTWARE_START)
                                               Note: In case of DMA used with regular group: if DMA configured in normal mode (single shot) JAUTO will be stopped upon DMA transfer complete.
                                                     To maintain JAUTO always enabled, DMA must be configured in circular mode.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
  uint32_t QueueInjectedContext;          /*!< Specifies whether the context queue feature is enabled.
                                               This parameter can be set to ENABLE or DISABLE.
                                               If context queue is enabled, injected sequencer&channels configurations are queued on up to 2 contexts. If a
                                               new injected context is set when queue is full, error is triggered by interruption and through function 'HAL_ADCEx_InjectedQueueOverflowCallback'.
                                               Caution: This feature request that the sequence is fully configured before injected conversion start.
                                                        Therefore, configure channels with HAL_ADCEx_InjectedConfigChannel() as many times as value of 'InjectedNbrOfConversion' parameter.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set.
                                               Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion). */
  uint32_t ExternalTrigInjecConv;         /*!< Selects the external event used to trigger the conversion start of injected group.
                                               If set to ADC_INJECTED_SOFTWARE_START, external triggers are disabled.
                                               This parameter can be a value of @ref ADCEx_External_trigger_source_Injected
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
  uint32_t ExternalTrigInjecConvEdge;     /*!< Selects the external trigger edge of injected group.
                                               This parameter can be a value of @ref ADCEx_External_trigger_edge_Injected.
                                               If trigger is set to ADC_INJECTED_SOFTWARE_START, this parameter is discarded.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
}ADC_InjectionConfTypeDef;

/** 
  * @brief  Structure definition of ADC analog watchdog
  * @note   The setting of these parameters with function HAL_ADC_AnalogWDGConfig() is conditioned to ADC state.
  *         ADC state can be either: ADC disabled or ADC enabled without conversion on going on regular and injected groups.
  */
typedef struct
{
  uint32_t WatchdogNumber;    /*!< Selects which ADC analog watchdog to apply to the selected channel.
                                   For Analog Watchdog 1: Only 1 channel can be monitored (or overall group of channels by setting parameter 'WatchdogMode')
                                   For Analog Watchdog 2 and 3: Several channels can be monitored (by successive calls of 'HAL_ADC_AnalogWDGConfig()' for each channel)
                                   This parameter can be a value of @ref ADCEx_analog_watchdog_number. */
  uint32_t WatchdogMode;      /*!< For Analog Watchdog 1: Configures the ADC analog watchdog mode: single channel/overall group of channels, regular/injected group.
                                   For Analog Watchdog 2 and 3: There is no configuration for overall group of channels as AWD1. Set value 'ADC_ANALOGWATCHDOG_NONE' to reset channels group programmed with parameter 'Channel', set any other value to not use this parameter.
                                   This parameter can be a value of @ref ADCEx_analog_watchdog_mode. */
  uint32_t Channel;           /*!< Selects which ADC channel to monitor by analog watchdog.
                                   For Analog Watchdog 1: this parameter has an effect only if parameter 'WatchdogMode' is configured on single channel. Only 1 channel can be monitored.
                                   For Analog Watchdog 2 and 3: Several channels can be monitored (successive calls of HAL_ADC_AnalogWDGConfig() must be done, one for each channel.
                                                                Channels group reset can be done by setting WatchdogMode to 'ADC_ANALOGWATCHDOG_NONE').
                                   This parameter can be a value of @ref ADCEx_channels. */
  uint32_t ITMode;            /*!< Specifies whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */
  uint32_t HighThreshold;     /*!< Configures the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively.
                                   Note: Analog watchdog 2 and 3 are limited to a resolution of 8 bits: if ADC resolution is 12 bits 
                                         the 4 LSB are ignored, if ADC resolution is 10 bits the 2 LSB are ignored. */
  uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively.
                                   Note: Analog watchdog 2 and 3 are limited to a resolution of 8 bits: if ADC resolution is 12 bits 
                                         the 4 LSB are ignored, if ADC resolution is 10 bits the 2 LSB are ignored. */
}ADC_AnalogWDGConfTypeDef;

/** 
  * @brief  Structure definition of ADC multimode
  * @note   The setting of these parameters with function HAL_ADCEx_MultiModeConfigChannel() is conditioned to ADCs state (both ADCs of the common group).
  *         State of ADCs of the common group must be: disabled.
  */
typedef struct
{
  uint32_t Mode;              /*!< Configures the ADC to operate in independent or multi mode. 
                                   This parameter can be a value of @ref ADCEx_Common_mode */
  uint32_t DMAAccessMode;     /*!< Configures the DMA mode for multi ADC mode:
                                   selection whether 2 DMA channels (each ADC use its own DMA channel) or 1 DMA channel (one DMA channel for both ADC, DMA of ADC master)
                                   This parameter can be a value of @ref ADCEx_Direct_memory_access_mode_for_multimode
                                   Caution: Limitations with multimode DMA access enabled (1 DMA channel used): In case of dual mode in high speed (more than 5Msps) or high activity of DMA by other peripherals, there is a risk of DMA overrun.
                                            Therefore, it is recommended to disable multimode DMA access: each ADC use its own DMA channel. */
  uint32_t TwoSamplingDelay;  /*!< Configures the Delay between 2 sampling phases.
                                   This parameter can be a value of @ref ADCEx_delay_between_2_sampling_phases
                                   Delay range depends on selected resolution: from 1 to 12 clock cycles for 12 bits, from 1 to 10 clock cycles for 10 bits
                                                                               from 1 to 8 clock cycles for 8 bits, from 1 to 6 clock cycles for 6 bits     */
}ADC_MultiModeTypeDef;
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/** 
  * @brief  Structure definition of ADC and regular group initialization 
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope entire ADC (affects regular and injected groups): DataAlign, ScanConvMode.
  *          - Scope regular group: ContinuousConvMode, NbrOfConversion, DiscontinuousConvMode, NbrOfDiscConversion, ExternalTrigConvEdge, ExternalTrigConv.
  * @note   The setting of these parameters with function HAL_ADC_Init() is conditioned to ADC state.
  *         ADC can be either disabled or enabled without conversion on going on regular group.
  */
typedef struct
{
  uint32_t DataAlign;             /*!< Specifies ADC data alignment to right (MSB on register bit 11 and LSB on register bit 0) (default setting)
                                       or to left (if regular group: MSB on register bit 15 and LSB on register bit 4, if injected group (MSB kept as signed value due to potential negative value after offset application): MSB on register bit 14 and LSB on register bit 3).
                                       This parameter can be a value of @ref ADCEx_Data_align */
  uint32_t ScanConvMode;          /*!< Configures the sequencer of regular and injected groups.
                                       This parameter can be associated to parameter 'DiscontinuousConvMode' to have main sequence subdivided in successive parts.
                                       If disabled: Conversion is performed in single mode (one channel converted, the one defined in rank 1).
                                                    Parameters 'NbrOfConversion' and 'InjectedNbrOfConversion' are discarded (equivalent to set to 1).
                                       If enabled:  Conversions are performed in sequence mode (multiple ranks defined by 'NbrOfConversion'/'InjectedNbrOfConversion' and each channel rank).
                                                    Scan direction is upward: from rank1 to rank 'n'.
                                       This parameter can be a value of @ref ADCEx_Scan_mode
                                       Note: For regular group, this parameter should be enabled in conversion either by polling (HAL_ADC_Start with Discontinuous mode and NbrOfDiscConversion=1)
                                             or by DMA (HAL_ADC_Start_DMA), but not by interruption (HAL_ADC_Start_IT): in scan mode, interruption is triggered only on the
                                             the last conversion of the sequence. All previous conversions would be overwritten by the last one.
                                             Injected group used with scan mode has not this constraint: each rank has its own result register, no data is overwritten. */
  uint32_t ContinuousConvMode;    /*!< Specifies whether the conversion is performed in single mode (one conversion) or continuous mode for regular group,
                                       after the selected trigger occurred (software start or external trigger).
                                       This parameter can be set to ENABLE or DISABLE. */
  uint32_t NbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the regular group sequencer.
                                       To use regular group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 16. */
  uint32_t DiscontinuousConvMode; /*!< Specifies whether the conversions sequence of regular group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                       Discontinuous mode is used only if sequencer is enabled (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                       Discontinuous mode can be enabled only if continuous mode is disabled. If continuous mode is enabled, this parameter setting is discarded.
                                       This parameter can be set to ENABLE or DISABLE. */
  uint32_t NbrOfDiscConversion;   /*!< Specifies the number of discontinuous conversions in which the  main sequence of regular group (parameter NbrOfConversion) will be subdivided.
                                       If parameter 'DiscontinuousConvMode' is disabled, this parameter is discarded.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 8. */
  uint32_t ExternalTrigConv;      /*!< Selects the external event used to trigger the conversion start of regular group.
                                       If set to ADC_SOFTWARE_START, external triggers are disabled.
                                       If set to external trigger source, triggering is on event rising edge.
                                       This parameter can be a value of @ref ADCEx_External_trigger_source_Regular */
}ADC_InitTypeDef;

/** 
  * @brief  Structure definition of ADC channel for regular group   
  * @note   The setting of these parameters with function HAL_ADC_ConfigChannel() is conditioned to ADC state.
  *         ADC can be either disabled or enabled without conversion on going on regular group.
  */ 
typedef struct 
{
  uint32_t Channel;                /*!< Specifies the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADCEx_channels
                                        Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability. */
  uint32_t Rank;                   /*!< Specifies the rank in the regular group sequencer 
                                        This parameter can be a value of @ref ADCEx_regular_rank
                                        Note: In case of need to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by the new channel setting (or parameter number of conversions can be adjusted) */
  uint32_t SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        Conversion time is the addition of sampling time and processing time (12.5 ADC clock cycles at ADC resolution 12 bits).
                                        This parameter can be a value of @ref ADCEx_sampling_times
                                        Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                 If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                        Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                              sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                              Refer to device datasheet for timings values, parameters TS_vrefint, TS_vbat, TS_temp (values rough order: 5us to 17.1us min). */
}ADC_ChannelConfTypeDef;

/** 
  * @brief  ADC Configuration injected Channel structure definition
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope channel: InjectedChannel, InjectedRank, InjectedSamplingTime, InjectedOffset
  *          - Scope injected group (affects all channels of injected group): InjectedNbrOfConversion, InjectedDiscontinuousConvMode,
  *            AutoInjectedConv, ExternalTrigInjecConvEdge, ExternalTrigInjecConv.
  * @note   The setting of these parameters with function HAL_ADCEx_InjectedConfigChannel() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled (this is the only possible ADC state to modify parameter 'ExternalTrigInjecConv')
  *          - For all except parameters 'ExternalTrigInjecConv': ADC enabled without conversion on going on injected group.
  */
typedef struct 
{
  uint32_t InjectedChannel;               /*!< Selection of ADC channel to configure
                                               This parameter can be a value of @ref ADCEx_channels
                                               Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability. */
  uint32_t InjectedRank;                  /*!< Rank in the injected group sequencer
                                               This parameter must be a value of @ref ADCEx_injected_rank
                                               Note: In case of need to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by the new channel setting (or parameter number of conversions can be adjusted) */
  uint32_t InjectedSamplingTime;          /*!< Sampling time value to be set for the selected channel.
                                               Unit: ADC clock cycles
                                               Conversion time is the addition of sampling time and processing time (12.5 ADC clock cycles at ADC resolution 12 bits).
                                               This parameter can be a value of @ref ADCEx_sampling_times
                                               Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                        If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                               Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                                     sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                                     Refer to device datasheet for timings values, parameters TS_vrefint, TS_vbat, TS_temp (values rough order: 5us to 17.1us min). */
  uint32_t InjectedOffset;                /*!< Defines the offset to be subtracted from the raw converted data (for channels set on injected group only).
                                               Offset value must be a positive number.
                                               Depending of ADC resolution selected (12, 10, 8 or 6 bits),
                                               this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively. */
  uint32_t InjectedNbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the injected group sequencer.
                                               To use the injected group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                               This parameter must be a number between Min_Data = 1 and Max_Data = 4.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
  uint32_t InjectedDiscontinuousConvMode; /*!< Specifies whether the conversions sequence of injected group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                               Discontinuous mode is used only if sequencer is enabled (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                               Discontinuous mode can be enabled only if continuous mode is disabled. If continuous mode is enabled, this parameter setting is discarded.
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: For injected group, number of discontinuous ranks increment is fixed to one-by-one.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
  uint32_t AutoInjectedConv;              /*!< Enables or disables the selected ADC automatic injected group conversion after regular one
                                               This parameter can be set to ENABLE or DISABLE.      
                                               Note: To use Automatic injected conversion, discontinuous mode must be disabled ('DiscontinuousConvMode' and 'InjectedDiscontinuousConvMode' set to DISABLE)
                                               Note: To use Automatic injected conversion, injected group external triggers must be disabled ('ExternalTrigInjecConv' set to ADC_SOFTWARE_START)
                                               Note: In case of DMA used with regular group: if DMA configured in normal mode (single shot) JAUTO will be stopped upon DMA transfer complete.
                                                     To maintain JAUTO always enabled, DMA must be configured in circular mode.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
  uint32_t ExternalTrigInjecConv;         /*!< Selects the external event used to trigger the conversion start of injected group.
                                               If set to ADC_INJECTED_SOFTWARE_START, external triggers are disabled.
                                               If set to external trigger source, triggering is on event rising edge.
                                               This parameter can be a value of @ref ADCEx_External_trigger_source_Injected
                                               Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion).
                                                     If ADC is enabled, this parameter setting is bypassed without error reporting (as it can be the expected behaviour in case of another parameter update on the fly)
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
}ADC_InjectionConfTypeDef;

/**
  * @brief  ADC Configuration analog watchdog definition
  * @note   The setting of these parameters with function is conditioned to ADC state.
  *         ADC state can be either disabled or enabled without conversion on going on regular and injected groups.
  */
typedef struct
{
  uint32_t WatchdogMode;      /*!< Configures the ADC analog watchdog mode: single/all channels, regular/injected group.
                                   This parameter can be a value of @ref ADCEx_analog_watchdog_mode. */
  uint32_t Channel;           /*!< Selects which ADC channel to monitor by analog watchdog.
                                   This parameter has an effect only if watchdog mode is configured on single channel (parameter WatchdogMode)
                                   This parameter can be a value of @ref ADCEx_channels. */
  uint32_t ITMode;            /*!< Specifies whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */
  uint32_t HighThreshold;     /*!< Configures the ADC analog watchdog High threshold value.
                                   This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
  uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog High threshold value.
                                   This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
  uint32_t WatchdogNumber;    /*!< Reserved for future use, can be set to 0 */
}ADC_AnalogWDGConfTypeDef;
#endif /* STM32F373xC || STM32F378xx */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Constants ADC Extended Exported Constants
  * @{
  */

/** @defgroup ADCEx_Error_Code ADC Extended Error Code
  * @{
  */
#define HAL_ADC_ERROR_NONE        ((uint32_t)0x00)   /*!< No error                                              */
#define HAL_ADC_ERROR_INTERNAL    ((uint32_t)0x01)   /*!< ADC IP internal error: if problem of clocking,
                                                          enable/disable, erroneous state                       */
#define HAL_ADC_ERROR_OVR         ((uint32_t)0x02)   /*!< Overrun error                                         */
#define HAL_ADC_ERROR_DMA         ((uint32_t)0x04)   /*!< DMA transfer error                                    */
#define HAL_ADC_ERROR_JQOVF       ((uint32_t)0x08)   /*!< Injected context queue overflow error                 */
/**
  * @}
  */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/** @defgroup ADCEx_ClockPrescaler ADC Extended Clock Prescaler
  * @{
  */
#define ADC_CLOCK_ASYNC               ((uint32_t)0x00000000)          /*!< ADC asynchronous clock derived from ADC dedicated PLL */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define ADC_CLOCK_SYNC_PCLK_DIV1      ((uint32_t)ADC12_CCR_CKMODE_0)  /*!< ADC synchronous clock derived from AHB clock without prescaler */
#define ADC_CLOCK_SYNC_PCLK_DIV2      ((uint32_t)ADC12_CCR_CKMODE_1)  /*!< ADC synchronous clock derived from AHB clock divided by a prescaler of 2 */
#define ADC_CLOCK_SYNC_PCLK_DIV4      ((uint32_t)ADC12_CCR_CKMODE)    /*!< ADC synchronous clock derived from AHB clock divided by a prescaler of 4 */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx    */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define ADC_CLOCK_SYNC_PCLK_DIV1      ((uint32_t)ADC1_CCR_CKMODE_0)   /*!< ADC synchronous clock derived from AHB clock without prescaler */
#define ADC_CLOCK_SYNC_PCLK_DIV2      ((uint32_t)ADC1_CCR_CKMODE_1)   /*!< ADC synchronous clock derived from AHB clock divided by a prescaler of 2 */
#define ADC_CLOCK_SYNC_PCLK_DIV4      ((uint32_t)ADC1_CCR_CKMODE)     /*!< ADC synchronous clock derived from AHB clock divided by a prescaler of 4 */
#endif /* STM32F301x8 || STM32F318xx || STM32F302x8 */

#define ADC_CLOCKPRESCALER_PCLK_DIV1   ADC_CLOCK_SYNC_PCLK_DIV1   /* Obsolete naming, kept for compatibility with some other devices */
#define ADC_CLOCKPRESCALER_PCLK_DIV2   ADC_CLOCK_SYNC_PCLK_DIV2   /* Obsolete naming, kept for compatibility with some other devices */
#define ADC_CLOCKPRESCALER_PCLK_DIV4   ADC_CLOCK_SYNC_PCLK_DIV4   /* Obsolete naming, kept for compatibility with some other devices */

#define IS_ADC_CLOCKPRESCALER(ADC_CLOCK) (((ADC_CLOCK) == ADC_CLOCK_ASYNC)          || \
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV1) || \
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV2) || \
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV4)   )
/**
  * @}
  */

/** @defgroup ADCEx_Resolution ADC Extended Resolution
  * @{
  */
#define ADC_RESOLUTION12b      ((uint32_t)0x00000000)          /*!<  ADC 12-bit resolution */
#define ADC_RESOLUTION10b      ((uint32_t)ADC_CFGR_RES_0)      /*!<  ADC 10-bit resolution */
#define ADC_RESOLUTION8b       ((uint32_t)ADC_CFGR_RES_1)      /*!<  ADC 8-bit resolution */
#define ADC_RESOLUTION6b       ((uint32_t)ADC_CFGR_RES)        /*!<  ADC 6-bit resolution */

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION12b) || \
                                       ((RESOLUTION) == ADC_RESOLUTION10b) || \
                                       ((RESOLUTION) == ADC_RESOLUTION8b)  || \
                                       ((RESOLUTION) == ADC_RESOLUTION6b)    )

#define IS_ADC_RESOLUTION_8_6_BITS(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION8b) || \
                                                ((RESOLUTION) == ADC_RESOLUTION6b)   )
/**
  * @}
  */

/** @defgroup ADCEx_Data_align ADC Extended Data Alignment
  * @{
  */
#define ADC_DATAALIGN_RIGHT      ((uint32_t)0x00000000)
#define ADC_DATAALIGN_LEFT       ((uint32_t)ADC_CFGR_ALIGN)

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT)    )
/**
  * @}
  */

/** @defgroup ADCEx_Scan_mode ADC Extended Scan Mode
  * @{
  */
#define ADC_SCAN_DISABLE         ((uint32_t)0x00000000)
#define ADC_SCAN_ENABLE          ((uint32_t)0x00000001)

#define IS_ADC_SCAN_MODE(SCAN_MODE) (((SCAN_MODE) == ADC_SCAN_DISABLE) || \
                                     ((SCAN_MODE) == ADC_SCAN_ENABLE)    )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_edge_Regular ADC Extended External trigger enable and polarity selection for regular channels
  * @{
  */
#define ADC_EXTERNALTRIGCONVEDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGCONVEDGE_RISING         ((uint32_t)ADC_CFGR_EXTEN_0)
#define ADC_EXTERNALTRIGCONVEDGE_FALLING        ((uint32_t)ADC_CFGR_EXTEN_1)
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING  ((uint32_t)ADC_CFGR_EXTEN)

#define IS_ADC_EXTTRIG_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGCONVEDGE_NONE)         || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING)       || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_FALLING)      || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING)  )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_source_Regular ADC Extended External trigger selection for regular group
  * @{
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target (caution: applies to other ADCs sharing the same common group), */
/* sorted by trigger name:                                                    */

/*!< External triggers of regular group for ADC1&ADC2 only */
#define ADC_EXTERNALTRIGCONV_T1_CC1         ADC1_2_EXTERNALTRIG_T1_CC1
#define ADC_EXTERNALTRIGCONV_T1_CC2         ADC1_2_EXTERNALTRIG_T1_CC2
#define ADC_EXTERNALTRIGCONV_T2_CC2         ADC1_2_EXTERNALTRIG_T2_CC2
#define ADC_EXTERNALTRIGCONV_T3_CC4         ADC1_2_EXTERNALTRIG_T3_CC4
#define ADC_EXTERNALTRIGCONV_T4_CC4         ADC1_2_EXTERNALTRIG_T4_CC4
#define ADC_EXTERNALTRIGCONV_T6_TRGO        ADC1_2_EXTERNALTRIG_T6_TRGO
#define ADC_EXTERNALTRIGCONV_EXT_IT11       ADC1_2_EXTERNALTRIG_EXT_IT11

/*!< External triggers of regular group for ADC3&ADC4 only */
#define ADC_EXTERNALTRIGCONV_T2_CC1         ADC3_4_EXTERNALTRIG_T2_CC1
#define ADC_EXTERNALTRIGCONV_T2_CC3         ADC3_4_EXTERNALTRIG_T2_CC3
#define ADC_EXTERNALTRIGCONV_T3_CC1         ADC3_4_EXTERNALTRIG_T3_CC1
#define ADC_EXTERNALTRIGCONV_T4_CC1         ADC3_4_EXTERNALTRIG_T4_CC1
#define ADC_EXTERNALTRIGCONV_T7_TRGO        ADC3_4_EXTERNALTRIG_T7_TRGO
#define ADC_EXTERNALTRIGCONV_T8_CC1         ADC3_4_EXTERNALTRIG_T8_CC1
#define ADC_EXTERNALTRIGCONV_EXT_IT2        ADC3_4_EXTERNALTRIG_EXT_IT2

/*!< External triggers of regular group for ADC1&ADC2, ADC3&ADC4 */
/* Note: Triggers affected to group ADC1_2 by default, redirected to group    */
/*       ADC3_4 by driver when needed.                                        */
#define ADC_EXTERNALTRIGCONV_T1_CC3         ADC1_2_EXTERNALTRIG_T1_CC3
#define ADC_EXTERNALTRIGCONV_T1_TRGO        ADC1_2_EXTERNALTRIG_T1_TRGO
#define ADC_EXTERNALTRIGCONV_T1_TRGO2       ADC1_2_EXTERNALTRIG_T1_TRGO2
#define ADC_EXTERNALTRIGCONV_T2_TRGO        ADC1_2_EXTERNALTRIG_T2_TRGO
#define ADC_EXTERNALTRIGCONV_T3_TRGO        ADC1_2_EXTERNALTRIG_T3_TRGO
#define ADC_EXTERNALTRIGCONV_T4_TRGO        ADC1_2_EXTERNALTRIG_T4_TRGO
#define ADC_EXTERNALTRIGCONV_T8_TRGO        ADC1_2_EXTERNALTRIG_T8_TRGO
#define ADC_EXTERNALTRIGCONV_T8_TRGO2       ADC1_2_EXTERNALTRIG_T8_TRGO2
#define ADC_EXTERNALTRIGCONV_T15_TRGO       ADC1_2_EXTERNALTRIG_T15_TRGO

#define ADC_SOFTWARE_START                  ((uint32_t)0x00000001)

#if defined(STM32F303xE) || defined(STM32F398xx)
/* ADC external triggers specific to device STM303xE: mask to differentiate   */
/* standard triggers from specific timer 20, needed for reallocation of       */
/* triggers common to ADC1&2/ADC3&4 and to avoind mixing with standard        */
/* triggers without remap.                                                    */
#define ADC_EXTERNALTRIGCONV_T20_MASK       0x1000

/*!< List of external triggers specific to device STM303xE: using Timer20     */
/* with ADC trigger input remap.                                              */
/* To remap ADC trigger from other timers/ExtLine to timer20: use macro       */
/* " __HAL_REMAPADCTRIGGER_ENABLE(...) " with parameters described below:     */

/*!< External triggers of regular group for ADC1&ADC2 only, specific to       */
/* device STM303xE: : using Timer20 with ADC trigger input remap              */
#define ADC_EXTERNALTRIGCONV_T20_CC2        ADC_EXTERNALTRIGCONV_T6_TRGO /*!< Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_EXT13) */
#define ADC_EXTERNALTRIGCONV_T20_CC3        ADC_EXTERNALTRIGCONV_T3_CC4  /*!< Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_EXT15) */

/*!< External triggers of regular group for ADC3&ADC4 only, specific to       */
/* device STM303xE: : using Timer20 with ADC trigger input remap              */
/* None */

/*!< External triggers of regular group for ADC1&ADC2, ADC3&ADC4, specific to */
/* device STM303xE: : using Timer20 with ADC trigger input remap              */
/* Note: Triggers affected to group ADC1_2 by default, redirected to group    */
/*       ADC3_4 by driver when needed.                                        */
#define ADC_EXTERNALTRIGCONV_T20_CC1        (ADC_EXTERNALTRIGCONV_T4_CC4 | ADC_EXTERNALTRIGCONV_T20_MASK) /*!< For ADC1&ADC2: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_EXT5) */
                                                                                                          /*!< For ADC3&ADC4: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC34_EXT15) */
#define ADC_EXTERNALTRIGCONV_T20_TRGO       (ADC_EXTERNALTRIGCONV_T1_CC3 | ADC_EXTERNALTRIGCONV_T20_MASK) /*!< For ADC1&ADC2: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_EXT2) */
                                                                                                          /*!< For ADC3&ADC4: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC34_EXT5) */
#define ADC_EXTERNALTRIGCONV_T20_TRGO2      (ADC_EXTERNALTRIGCONV_T2_CC2 | ADC_EXTERNALTRIGCONV_T20_MASK) /*!< For ADC1&ADC2: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_EXT3) */
                                                                                                          /*!< For ADC3&ADC4: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC34_EXT6) */
#endif /* STM32F303xE || STM32F398xx */

#if defined(STM32F303xC) || defined(STM32F358xx)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T6_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11) || \
                                                                                 \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T7_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT2)  || \
                                                                                 \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO2) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO2) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO) || \
                                                                                 \
                                 ((REGTRIG) == ADC_SOFTWARE_START)              )
#endif /* STM32F303xC || STM32F358xx */

#if defined(STM32F303xE) || defined(STM32F398xx)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC4)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T6_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11)  || \
                                                                                  \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC3)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T7_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT2)   || \
                                                                                  \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO2)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO2)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO)  || \
                                                                                  \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T20_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T20_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T20_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T20_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T20_TRGO2) || \
                                                                                  \
                                 ((REGTRIG) == ADC_SOFTWARE_START)               )
#endif /* STM32F303xE || STM32F398xx */

#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F302xE) || \
    defined(STM32F302xC)
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target (caution: applies to other ADCs sharing the same common group), */
/* sorted by trigger name:                                                    */

/*!< External triggers of regular group for ADC1&ADC2 */
#define ADC_EXTERNALTRIGCONV_T1_CC1         ADC1_2_EXTERNALTRIG_T1_CC1
#define ADC_EXTERNALTRIGCONV_T1_CC2         ADC1_2_EXTERNALTRIG_T1_CC2
#define ADC_EXTERNALTRIGCONV_T1_CC3         ADC1_2_EXTERNALTRIG_T1_CC3
#define ADC_EXTERNALTRIGCONV_T1_TRGO        ADC1_2_EXTERNALTRIG_T1_TRGO
#define ADC_EXTERNALTRIGCONV_T1_TRGO2       ADC1_2_EXTERNALTRIG_T1_TRGO2
#define ADC_EXTERNALTRIGCONV_T2_CC2         ADC1_2_EXTERNALTRIG_T2_CC2
#define ADC_EXTERNALTRIGCONV_T2_TRGO        ADC1_2_EXTERNALTRIG_T2_TRGO
#define ADC_EXTERNALTRIGCONV_T3_CC4         ADC1_2_EXTERNALTRIG_T3_CC4
#define ADC_EXTERNALTRIGCONV_T3_TRGO        ADC1_2_EXTERNALTRIG_T3_TRGO
#define ADC_EXTERNALTRIGCONV_T4_CC4         ADC1_2_EXTERNALTRIG_T4_CC4
#define ADC_EXTERNALTRIGCONV_T4_TRGO        ADC1_2_EXTERNALTRIG_T4_TRGO
#define ADC_EXTERNALTRIGCONV_T6_TRGO        ADC1_2_EXTERNALTRIG_T6_TRGO
#define ADC_EXTERNALTRIGCONV_T15_TRGO       ADC1_2_EXTERNALTRIG_T15_TRGO
#define ADC_EXTERNALTRIGCONV_EXT_IT11       ADC1_2_EXTERNALTRIG_EXT_IT11
#define ADC_SOFTWARE_START                  ((uint32_t)0x00000001)

#if defined(STM32F302xE)
/* ADC external triggers specific to device STM302xE: mask to differentiate   */
/* standard triggers from specific timer 20, needed for reallocation of       */
/* triggers common to ADC1&2 and to avoind mixing with standard               */
/* triggers without remap.                                                    */
#define ADC_EXTERNALTRIGCONV_T20_MASK       0x1000

/*!< List of external triggers specific to device STM302xE: using Timer20     */
/* with ADC trigger input remap.                                              */
/* To remap ADC trigger from other timers/ExtLine to timer20: use macro       */
/* " __HAL_REMAPADCTRIGGER_ENABLE(...) " with parameters described below:     */

/*!< External triggers of regular group for ADC1&ADC2 only, specific to       */
/* device STM302xE: : using Timer20 with ADC trigger input remap              */
#define ADC_EXTERNALTRIGCONV_T20_CC2        ADC_EXTERNALTRIGCONV_T6_TRGO /*!< Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_EXT13) */
#define ADC_EXTERNALTRIGCONV_T20_CC3        ADC_EXTERNALTRIGCONV_T3_CC4  /*!< Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_EXT15) */
#endif /* STM32F302xE */

#if defined(STM32F302xE)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO2) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T6_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC4)   || \
                                                                                 \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T20_CC2)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T20_CC3)  || \
                                                                                 \
                                 ((REGTRIG) == ADC_SOFTWARE_START)              )
#endif /* STM32F302xE */

#if defined(STM32F302xC)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO2) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T6_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC4)   || \
                                                                                 \
                                 ((REGTRIG) == ADC_SOFTWARE_START)              )
#endif /* STM32F302xC */

#endif /* STM32F302xE || */
       /* STM32F302xC    */

#if defined(STM32F303x8) || defined(STM32F328xx)
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target (caution: applies to other ADCs sharing the same common group), */
/* sorted by trigger name:                                                    */

/*!< External triggers of regular group for ADC1&ADC2 */
#define ADC_EXTERNALTRIGCONV_T1_CC1         ADC1_2_EXTERNALTRIG_T1_CC1
#define ADC_EXTERNALTRIGCONV_T1_CC2         ADC1_2_EXTERNALTRIG_T1_CC2
#define ADC_EXTERNALTRIGCONV_T1_CC3         ADC1_2_EXTERNALTRIG_T1_CC3
#define ADC_EXTERNALTRIGCONV_T1_TRGO        ADC1_2_EXTERNALTRIG_T1_TRGO
#define ADC_EXTERNALTRIGCONV_T1_TRGO2       ADC1_2_EXTERNALTRIG_T1_TRGO2
#define ADC_EXTERNALTRIGCONV_T2_CC2         ADC1_2_EXTERNALTRIG_T2_CC2
#define ADC_EXTERNALTRIGCONV_T2_TRGO        ADC1_2_EXTERNALTRIG_T2_TRGO
#define ADC_EXTERNALTRIGCONV_T3_CC4         ADC1_2_EXTERNALTRIG_T3_CC4
#define ADC_EXTERNALTRIGCONV_T3_TRGO        ADC1_2_EXTERNALTRIG_T3_TRGO
#define ADC_EXTERNALTRIGCONV_T4_CC4         ADC1_2_EXTERNALTRIG_T4_CC4
#define ADC_EXTERNALTRIGCONV_T4_TRGO        ADC1_2_EXTERNALTRIG_T4_TRGO
#define ADC_EXTERNALTRIGCONV_T8_TRGO        ADC1_2_EXTERNALTRIG_T8_TRGO
#define ADC_EXTERNALTRIGCONV_T8_TRGO2       ADC1_2_EXTERNALTRIG_T8_TRGO2
#define ADC_EXTERNALTRIGCONV_T6_TRGO        ADC1_2_EXTERNALTRIG_T6_TRGO
#define ADC_EXTERNALTRIGCONV_T15_TRGO       ADC1_2_EXTERNALTRIG_T15_TRGO
#define ADC_EXTERNALTRIGCONV_EXT_IT11       ADC1_2_EXTERNALTRIG_EXT_IT11
#define ADC_SOFTWARE_START                  ((uint32_t)0x00000001)

#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO2) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO2) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T6_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC4)   || \
                                                                                 \
                                 ((REGTRIG) == ADC_SOFTWARE_START)              )
#endif /* STM32F303x8 || STM32F328xx */

#if defined(STM32F334x8)
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target (caution: applies to other ADCs sharing the same common group), */
/* sorted by trigger name:                                                    */

/*!< External triggers of regular group for ADC1&ADC2 */
#define ADC_EXTERNALTRIGCONV_T1_CC1         ADC1_2_EXTERNALTRIG_T1_CC1
#define ADC_EXTERNALTRIGCONV_T1_CC2         ADC1_2_EXTERNALTRIG_T1_CC2
#define ADC_EXTERNALTRIGCONV_T1_CC3         ADC1_2_EXTERNALTRIG_T1_CC3
#define ADC_EXTERNALTRIGCONV_T1_TRGO        ADC1_2_EXTERNALTRIG_T1_TRGO
#define ADC_EXTERNALTRIGCONV_T1_TRGO2       ADC1_2_EXTERNALTRIG_T1_TRGO2
#define ADC_EXTERNALTRIGCONV_T2_CC2         ADC1_2_EXTERNALTRIG_T2_CC2
#define ADC_EXTERNALTRIGCONV_T2_TRGO        ADC1_2_EXTERNALTRIG_T2_TRGO
#define ADC_EXTERNALTRIGCONV_T3_CC4         ADC1_2_EXTERNALTRIG_T3_CC4
#define ADC_EXTERNALTRIGCONV_T3_TRGO        ADC1_2_EXTERNALTRIG_T3_TRGO
#define ADC_EXTERNALTRIGCONV_T6_TRGO        ADC1_2_EXTERNALTRIG_T6_TRGO
#define ADC_EXTERNALTRIGCONV_T15_TRGO       ADC1_2_EXTERNALTRIG_T15_TRGO
#define ADC_EXTERNALTRIGCONVHRTIM_TRG1      ADC1_2_EXTERNALTRIG_HRTIM_TRG1
#define ADC_EXTERNALTRIGCONVHRTIM_TRG3      ADC1_2_EXTERNALTRIG_HRTIM_TRG3
#define ADC_EXTERNALTRIGCONV_EXT_IT11       ADC1_2_EXTERNALTRIG_EXT_IT11
#define ADC_SOFTWARE_START                  ((uint32_t)0x00000001)

#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONVHRTIM_TRG1) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONVHRTIM_TRG3) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO2)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T6_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC4)    || \
                                                                                  \
                                 ((REGTRIG) == ADC_SOFTWARE_START)               )
#endif /* STM32F334x8 */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/* List of external triggers with generic trigger name, sorted by trigger     */
/* name:                                                                      */

/* External triggers of regular group for ADC1 */
#define ADC_EXTERNALTRIGCONV_T1_CC1         ADC1_EXTERNALTRIG_T1_CC1
#define ADC_EXTERNALTRIGCONV_T1_CC2         ADC1_EXTERNALTRIG_T1_CC2
#define ADC_EXTERNALTRIGCONV_T1_CC3         ADC1_EXTERNALTRIG_T1_CC3
#define ADC_EXTERNALTRIGCONV_EXT_IT11       ADC1_EXTERNALTRIG_EXT_IT11
#define ADC_EXTERNALTRIGCONV_T1_TRGO        ADC1_EXTERNALTRIG_T1_TRGO
#define ADC_EXTERNALTRIGCONV_T1_TRGO2       ADC1_EXTERNALTRIG_T1_TRGO2
#define ADC_EXTERNALTRIGCONV_T2_TRGO        ADC1_EXTERNALTRIG_T2_TRGO
#define ADC_EXTERNALTRIGCONV_T6_TRGO        ADC1_EXTERNALTRIG_T6_TRGO
#define ADC_EXTERNALTRIGCONV_T15_TRGO       ADC1_EXTERNALTRIG_T15_TRGO
#define ADC_SOFTWARE_START                  ((uint32_t)0x00000001)

#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO2) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T6_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO) || \
                                 ((REGTRIG) == ADC_SOFTWARE_START)              )
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */
/**
  * @}
  */

/** @defgroup ADCEx_Internal_HAL_driver_Ext_trig_src_Regular ADC Extended External trigger selection for regular group (Used Internally)
  * @{
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
/* List of external triggers for common groups ADC1&ADC2 and/or ADC3&ADC4:    */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */

/* External triggers of regular group for ADC1 & ADC2 */
#define ADC1_2_EXTERNALTRIG_T1_CC1           ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIG_T1_CC2           ((uint32_t)ADC_CFGR_EXTSEL_0)
#define ADC1_2_EXTERNALTRIG_T1_CC3           ((uint32_t)ADC_CFGR_EXTSEL_1)
#define ADC1_2_EXTERNALTRIG_T2_CC2           ((uint32_t)(ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T3_TRGO          ((uint32_t)ADC_CFGR_EXTSEL_2)
#define ADC1_2_EXTERNALTRIG_T4_CC4           ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_EXT_IT11         ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T8_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T8_TRGO2         ((uint32_t) ADC_CFGR_EXTSEL_3)
#define ADC1_2_EXTERNALTRIG_T1_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T1_TRGO2         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T2_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T4_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2))
#define ADC1_2_EXTERNALTRIG_T6_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T15_TRGO         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T3_CC4           ((uint32_t)ADC_CFGR_EXTSEL)

/* External triggers of regular group for ADC3 & ADC4 */
#define ADC3_4_EXTERNALTRIG_T3_CC1           ((uint32_t)0x00000000)
#define ADC3_4_EXTERNALTRIG_T2_CC3           ((uint32_t)ADC_CFGR_EXTSEL_0)
#define ADC3_4_EXTERNALTRIG_T1_CC3           ((uint32_t)ADC_CFGR_EXTSEL_1)
#define ADC3_4_EXTERNALTRIG_T8_CC1           ((uint32_t)(ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC3_4_EXTERNALTRIG_T8_TRGO          ((uint32_t)ADC_CFGR_EXTSEL_2)
#define ADC3_4_EXTERNALTRIG_EXT_IT2          ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC3_4_EXTERNALTRIG_T4_CC1           ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC3_4_EXTERNALTRIG_T2_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC3_4_EXTERNALTRIG_T8_TRGO2         ((uint32_t)ADC_CFGR_EXTSEL_3)
#define ADC3_4_EXTERNALTRIG_T1_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0))
#define ADC3_4_EXTERNALTRIG_T1_TRGO2         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1))
#define ADC3_4_EXTERNALTRIG_T3_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC3_4_EXTERNALTRIG_T4_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2))
#define ADC3_4_EXTERNALTRIG_T7_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC3_4_EXTERNALTRIG_T15_TRGO         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC3_4_EXTERNALTRIG_T2_CC1           ((uint32_t)ADC_CFGR_EXTSEL)
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F302xE) || \
    defined(STM32F302xC)
/* List of external triggers of common group ADC1&ADC2:                       */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_2_EXTERNALTRIG_T1_CC1           ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIG_T1_CC2           ((uint32_t)ADC_CFGR_EXTSEL_0)
#define ADC1_2_EXTERNALTRIG_T1_CC3           ((uint32_t)ADC_CFGR_EXTSEL_1)
#define ADC1_2_EXTERNALTRIG_T1_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T1_TRGO2         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T2_CC2           ((uint32_t)(ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T2_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T3_CC4           ((uint32_t)ADC_CFGR_EXTSEL)
#define ADC1_2_EXTERNALTRIG_T3_TRGO          ((uint32_t)ADC_CFGR_EXTSEL_2)
#define ADC1_2_EXTERNALTRIG_T4_CC4           ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T4_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2))
#define ADC1_2_EXTERNALTRIG_T6_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T15_TRGO         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_EXT_IT11         ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#endif /* STM32F302xE || */
       /* STM32F302xC    */

#if defined(STM32F303x8) || defined(STM32F328xx)
/* List of external triggers of common group ADC1&ADC2:                       */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_2_EXTERNALTRIG_T1_CC1           ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIG_T1_CC2           ((uint32_t)ADC_CFGR_EXTSEL_0)
#define ADC1_2_EXTERNALTRIG_T1_CC3           ((uint32_t)ADC_CFGR_EXTSEL_1)
#define ADC1_2_EXTERNALTRIG_T2_CC2           ((uint32_t)(ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T3_TRGO          ((uint32_t)ADC_CFGR_EXTSEL_2)
#define ADC1_2_EXTERNALTRIG_T4_CC4           ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_EXT_IT11         ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T8_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T8_TRGO2         ((uint32_t) ADC_CFGR_EXTSEL_3)
#define ADC1_2_EXTERNALTRIG_T1_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T1_TRGO2         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T2_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T4_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2))
#define ADC1_2_EXTERNALTRIG_T6_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T15_TRGO         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T3_CC4           ((uint32_t)ADC_CFGR_EXTSEL)
#endif /* STM32F303x8 || STM32F328xx */

#if defined(STM32F334x8)
/* List of external triggers of common group ADC1&ADC2:                       */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_2_EXTERNALTRIG_T1_CC1           ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIG_T1_CC2           ((uint32_t)ADC_CFGR_EXTSEL_0)
#define ADC1_2_EXTERNALTRIG_T1_CC3           ((uint32_t)ADC_CFGR_EXTSEL_1)
#define ADC1_2_EXTERNALTRIG_T2_CC2           ((uint32_t)(ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T3_TRGO          ((uint32_t)ADC_CFGR_EXTSEL_2)
#define ADC1_2_EXTERNALTRIG_EXT_IT11         ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_HRTIM_TRG1       ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_HRTIM_TRG3       ((uint32_t) ADC_CFGR_EXTSEL_3)
#define ADC1_2_EXTERNALTRIG_T1_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T1_TRGO2         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T2_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T6_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T15_TRGO         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC1_2_EXTERNALTRIG_T3_CC4           ((uint32_t)ADC_CFGR_EXTSEL)
#endif /* STM32F334x8 */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/* List of external triggers of regular group for ADC1:                       */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_EXTERNALTRIG_T1_CC1           ((uint32_t)0x00000000)
#define ADC1_EXTERNALTRIG_T1_CC2           ((uint32_t)ADC_CFGR_EXTSEL_0)
#define ADC1_EXTERNALTRIG_T1_CC3           ((uint32_t)ADC_CFGR_EXTSEL_1)
#define ADC1_EXTERNALTRIG_EXT_IT11         ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC1_EXTERNALTRIG_T1_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0))
#define ADC1_EXTERNALTRIG_T1_TRGO2         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1))
#define ADC1_EXTERNALTRIG_T2_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC1_EXTERNALTRIG_T6_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC1_EXTERNALTRIG_T15_TRGO         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC_SOFTWARE_START                 ((uint32_t)0x00000001)
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */
/**
  * @}
  */


/** @defgroup ADCEx_EOCSelection ADC Extended End of Regular Sequence/Conversion 
  * @{
  */
#define EOC_SINGLE_CONV         ((uint32_t) ADC_ISR_EOC)
#define EOC_SEQ_CONV            ((uint32_t) ADC_ISR_EOS)
#define EOC_SINGLE_SEQ_CONV     ((uint32_t)(ADC_ISR_EOC | ADC_ISR_EOS))  /*!< reserved for future use */

#define IS_ADC_EOC_SELECTION(EOC_SELECTION) (((EOC_SELECTION) == EOC_SINGLE_CONV)    || \
                                             ((EOC_SELECTION) == EOC_SEQ_CONV)       || \
                                             ((EOC_SELECTION) == EOC_SINGLE_SEQ_CONV)  )
/**
  * @}
  */

/** @defgroup ADCEx_Overrun ADC Extended overrun
  * @{
  */
#define OVR_DATA_OVERWRITTEN            ((uint32_t)0x00000000)   /*!< Default setting, to be used for compatibility with other STM32 devices */
#define OVR_DATA_PRESERVED              ((uint32_t)0x00000001)

#define IS_ADC_OVERRUN(OVR) (((OVR) == OVR_DATA_PRESERVED)  || \
                             ((OVR) == OVR_DATA_OVERWRITTEN)  )
/**
  * @}
  */

/** @defgroup ADCEx_channels ADC Extended Channels
  * @{
  */
/* Note: Depending on devices, some channels may not be available on package  */
/*       pins. Refer to device datasheet for channels availability.           */
#define ADC_CHANNEL_1           ((uint32_t)(ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_2           ((uint32_t)(ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_3           ((uint32_t)(ADC_SQR3_SQ10_1 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_4           ((uint32_t)(ADC_SQR3_SQ10_2))
#define ADC_CHANNEL_5           ((uint32_t)(ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_6           ((uint32_t)(ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_7           ((uint32_t)(ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_1 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_8           ((uint32_t)(ADC_SQR3_SQ10_3))
#define ADC_CHANNEL_9           ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_10          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_11          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_1 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_12          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_2))
#define ADC_CHANNEL_13          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_14          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_15          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_1 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_16          ((uint32_t)(ADC_SQR3_SQ10_4))
#define ADC_CHANNEL_17          ((uint32_t)(ADC_SQR3_SQ10_4 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_18          ((uint32_t)(ADC_SQR3_SQ10_4 | ADC_SQR3_SQ10_1))

/* Note: Vopamp1, TempSensor and Vbat internal channels available on ADC1 only */
#define ADC_CHANNEL_VOPAMP1     ADC_CHANNEL_15
#define ADC_CHANNEL_TEMPSENSOR  ADC_CHANNEL_16
#define ADC_CHANNEL_VBAT        ADC_CHANNEL_17

/* Note: Vopamp2/3/4 internal channels available on ADC2/3/4 respectively     */
#define ADC_CHANNEL_VOPAMP2     ADC_CHANNEL_17
#define ADC_CHANNEL_VOPAMP3     ADC_CHANNEL_17
#define ADC_CHANNEL_VOPAMP4     ADC_CHANNEL_17

/* Note: VrefInt internal channels available on all ADCs, but only            */
/*       one ADC is allowed to be connected to VrefInt at the same time.      */
#define ADC_CHANNEL_VREFINT     ((uint32_t)ADC_CHANNEL_18)

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_1)           || \
                                 ((CHANNEL) == ADC_CHANNEL_2)           || \
                                 ((CHANNEL) == ADC_CHANNEL_3)           || \
                                 ((CHANNEL) == ADC_CHANNEL_4)           || \
                                 ((CHANNEL) == ADC_CHANNEL_5)           || \
                                 ((CHANNEL) == ADC_CHANNEL_6)           || \
                                 ((CHANNEL) == ADC_CHANNEL_7)           || \
                                 ((CHANNEL) == ADC_CHANNEL_8)           || \
                                 ((CHANNEL) == ADC_CHANNEL_9)           || \
                                 ((CHANNEL) == ADC_CHANNEL_10)          || \
                                 ((CHANNEL) == ADC_CHANNEL_11)          || \
                                 ((CHANNEL) == ADC_CHANNEL_12)          || \
                                 ((CHANNEL) == ADC_CHANNEL_13)          || \
                                 ((CHANNEL) == ADC_CHANNEL_14)          || \
                                 ((CHANNEL) == ADC_CHANNEL_15)          || \
                                 ((CHANNEL) == ADC_CHANNEL_TEMPSENSOR)  || \
                                 ((CHANNEL) == ADC_CHANNEL_VBAT)        || \
                                 ((CHANNEL) == ADC_CHANNEL_VREFINT)     || \
                                 ((CHANNEL) == ADC_CHANNEL_VOPAMP1)     || \
                                 ((CHANNEL) == ADC_CHANNEL_VOPAMP2)     || \
                                 ((CHANNEL) == ADC_CHANNEL_VOPAMP3)     || \
                                 ((CHANNEL) == ADC_CHANNEL_VOPAMP4)       )

#define IS_ADC_DIFF_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_1)      || \
                                      ((CHANNEL) == ADC_CHANNEL_2)      || \
                                      ((CHANNEL) == ADC_CHANNEL_3)      || \
                                      ((CHANNEL) == ADC_CHANNEL_4)      || \
                                      ((CHANNEL) == ADC_CHANNEL_5)      || \
                                      ((CHANNEL) == ADC_CHANNEL_6)      || \
                                      ((CHANNEL) == ADC_CHANNEL_7)      || \
                                      ((CHANNEL) == ADC_CHANNEL_8)      || \
                                      ((CHANNEL) == ADC_CHANNEL_9)      || \
                                      ((CHANNEL) == ADC_CHANNEL_10)     || \
                                      ((CHANNEL) == ADC_CHANNEL_11)     || \
                                      ((CHANNEL) == ADC_CHANNEL_12)     || \
                                      ((CHANNEL) == ADC_CHANNEL_13)     || \
                                      ((CHANNEL) == ADC_CHANNEL_14)       )

/**
  * @}
  */

/** @defgroup ADCEx_sampling_times ADC Extended Sampling Times
  * @{
  */
#define ADC_SAMPLETIME_1CYCLE_5       ((uint32_t)0x00000000)                              /*!< Sampling time 1.5 ADC clock cycle */
#define ADC_SAMPLETIME_2CYCLES_5      ((uint32_t)ADC_SMPR2_SMP10_0)                       /*!< Sampling time 2.5 ADC clock cycles */
#define ADC_SAMPLETIME_4CYCLES_5      ((uint32_t)ADC_SMPR2_SMP10_1)                       /*!< Sampling time 4.5 ADC clock cycles */
#define ADC_SAMPLETIME_7CYCLES_5      ((uint32_t)(ADC_SMPR2_SMP10_1 | ADC_SMPR2_SMP10_0)) /*!< Sampling time 7.5 ADC clock cycles */
#define ADC_SAMPLETIME_19CYCLES_5     ((uint32_t)ADC_SMPR2_SMP10_2)                       /*!< Sampling time 19.5 ADC clock cycles */
#define ADC_SAMPLETIME_61CYCLES_5     ((uint32_t)(ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_0)) /*!< Sampling time 61.5 ADC clock cycles */
#define ADC_SAMPLETIME_181CYCLES_5    ((uint32_t)(ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_1)) /*!< Sampling time 181.5 ADC clock cycles */
#define ADC_SAMPLETIME_601CYCLES_5    ((uint32_t)ADC_SMPR2_SMP10)                         /*!< Sampling time 601.5 ADC clock cycles */

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_1CYCLE_5)    || \
                                  ((TIME) == ADC_SAMPLETIME_2CYCLES_5)   || \
                                  ((TIME) == ADC_SAMPLETIME_4CYCLES_5)   || \
                                  ((TIME) == ADC_SAMPLETIME_7CYCLES_5)   || \
                                  ((TIME) == ADC_SAMPLETIME_19CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_61CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_181CYCLES_5) || \
                                  ((TIME) == ADC_SAMPLETIME_601CYCLES_5)   )
/**
  * @}
  */

/** @defgroup ADCEx_SingleDifferential ADC Extended Single-ended/Differential input mode
  * @{
  */
#define ADC_SINGLE_ENDED                ((uint32_t)0x00000000)
#define ADC_DIFFERENTIAL_ENDED          ((uint32_t)0x00000001)

#define IS_ADC_SINGLE_DIFFERENTIAL(SING_DIFF) (((SING_DIFF) == ADC_SINGLE_ENDED)      || \
                                               ((SING_DIFF) == ADC_DIFFERENTIAL_ENDED)  )
/**
  * @}
  */

/** @defgroup ADCEx_OffsetNumber ADC Extended Offset Number
  * @{
  */
#define ADC_OFFSET_NONE               ((uint32_t)0x00)
#define ADC_OFFSET_1                  ((uint32_t)0x01)
#define ADC_OFFSET_2                  ((uint32_t)0x02)
#define ADC_OFFSET_3                  ((uint32_t)0x03)
#define ADC_OFFSET_4                  ((uint32_t)0x04)

#define IS_ADC_OFFSET_NUMBER(OFFSET_NUMBER) (((OFFSET_NUMBER) == ADC_OFFSET_NONE) || \
                                             ((OFFSET_NUMBER) == ADC_OFFSET_1)    || \
                                             ((OFFSET_NUMBER) == ADC_OFFSET_2)    || \
                                             ((OFFSET_NUMBER) == ADC_OFFSET_3)    || \
                                             ((OFFSET_NUMBER) == ADC_OFFSET_4)      )
/**
  * @}
  */

/** @defgroup ADCEx_regular_rank ADC Extended Regular Channel Rank
  * @{
  */
#define ADC_REGULAR_RANK_1    ((uint32_t)0x00000001)
#define ADC_REGULAR_RANK_2    ((uint32_t)0x00000002)
#define ADC_REGULAR_RANK_3    ((uint32_t)0x00000003)
#define ADC_REGULAR_RANK_4    ((uint32_t)0x00000004)
#define ADC_REGULAR_RANK_5    ((uint32_t)0x00000005)
#define ADC_REGULAR_RANK_6    ((uint32_t)0x00000006)
#define ADC_REGULAR_RANK_7    ((uint32_t)0x00000007)
#define ADC_REGULAR_RANK_8    ((uint32_t)0x00000008)
#define ADC_REGULAR_RANK_9    ((uint32_t)0x00000009)
#define ADC_REGULAR_RANK_10   ((uint32_t)0x0000000A)
#define ADC_REGULAR_RANK_11   ((uint32_t)0x0000000B)
#define ADC_REGULAR_RANK_12   ((uint32_t)0x0000000C)
#define ADC_REGULAR_RANK_13   ((uint32_t)0x0000000D)
#define ADC_REGULAR_RANK_14   ((uint32_t)0x0000000E)
#define ADC_REGULAR_RANK_15   ((uint32_t)0x0000000F)
#define ADC_REGULAR_RANK_16   ((uint32_t)0x00000010)

#define IS_ADC_REGULAR_RANK(CHANNEL) (((CHANNEL) == ADC_REGULAR_RANK_1 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_2 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_3 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_4 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_5 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_6 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_7 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_8 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_9 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_10) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_11) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_12) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_13) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_14) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_15) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_16)   )
/**
  * @}
  */

/** @defgroup ADCEx_injected_rank ADC Extended Injected Channel Rank
  * @{
  */
#define ADC_INJECTED_RANK_1    ((uint32_t)0x00000001)
#define ADC_INJECTED_RANK_2    ((uint32_t)0x00000002)
#define ADC_INJECTED_RANK_3    ((uint32_t)0x00000003)
#define ADC_INJECTED_RANK_4    ((uint32_t)0x00000004)

#define IS_ADC_INJECTED_RANK(CHANNEL) (((CHANNEL) == ADC_INJECTED_RANK_1) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_2) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_3) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_4)   )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_edge_Injected External Trigger Edge of Injected Group
  * @{
  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISING         ((uint32_t)ADC_JSQR_JEXTEN_0)
#define ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING        ((uint32_t)ADC_JSQR_JEXTEN_1)
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING  ((uint32_t)ADC_JSQR_JEXTEN)

#define IS_ADC_EXTTRIGINJEC_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_NONE)         || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISING)       || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING)      || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING)  )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_source_Injected External Trigger Source of Injected Group
  * @{
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
/* List of external triggers with generic trigger name, independently of ADC  */
/* target (caution: applies to other ADCs sharing the same common group),     */
/* sorted by trigger name:                                                    */

/* External triggers of injected group for ADC1&ADC2 only */
#define ADC_EXTERNALTRIGINJECCONV_T2_CC1    ADC1_2_EXTERNALTRIGINJEC_T2_CC1
#define ADC_EXTERNALTRIGINJECCONV_T3_CC1    ADC1_2_EXTERNALTRIGINJEC_T3_CC1
#define ADC_EXTERNALTRIGINJECCONV_T3_CC3    ADC1_2_EXTERNALTRIGINJEC_T3_CC3
#define ADC_EXTERNALTRIGINJECCONV_T3_CC4    ADC1_2_EXTERNALTRIGINJEC_T3_CC4
#define ADC_EXTERNALTRIGINJECCONV_T6_TRGO   ADC1_2_EXTERNALTRIGINJEC_T6_TRGO
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15  ADC1_2_EXTERNALTRIGINJEC_EXT_IT15

/* External triggers of injected group for ADC3&ADC4 only */
#define ADC_EXTERNALTRIGINJECCONV_T1_CC3    ADC3_4_EXTERNALTRIGINJEC_T1_CC3
#define ADC_EXTERNALTRIGINJECCONV_T4_CC3    ADC3_4_EXTERNALTRIGINJEC_T4_CC3
#define ADC_EXTERNALTRIGINJECCONV_T4_CC4    ADC3_4_EXTERNALTRIGINJEC_T4_CC4
#define ADC_EXTERNALTRIGINJECCONV_T7_TRGO   ADC3_4_EXTERNALTRIGINJEC_T7_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T8_CC2    ADC3_4_EXTERNALTRIGINJEC_T8_CC2

/* External triggers of injected group for ADC1&ADC2, ADC3&ADC4 */
/* Note: Triggers affected to group ADC1_2 by default, redirected to group    */
/*       ADC3_4 by driver when needed.                                        */
#define ADC_EXTERNALTRIGINJECCONV_T1_CC4    ADC1_2_EXTERNALTRIGINJEC_T1_CC4
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO   ADC1_2_EXTERNALTRIGINJEC_T1_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO2  ADC1_2_EXTERNALTRIGINJEC_T1_TRGO2
#define ADC_EXTERNALTRIGINJECCONV_T2_TRGO   ADC1_2_EXTERNALTRIGINJEC_T2_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T3_TRGO   ADC1_2_EXTERNALTRIGINJEC_T3_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T4_TRGO   ADC1_2_EXTERNALTRIGINJEC_T4_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T8_CC4    ADC1_2_EXTERNALTRIGINJEC_T8_CC4
#define ADC_EXTERNALTRIGINJECCONV_T8_TRGO   ADC1_2_EXTERNALTRIGINJEC_T8_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T8_TRGO2  ADC1_2_EXTERNALTRIGINJEC_T8_TRGO2
#define ADC_EXTERNALTRIGINJECCONV_T15_TRGO  ADC1_2_EXTERNALTRIGINJEC_T15_TRGO

#define ADC_INJECTED_SOFTWARE_START     ((uint32_t)0x00000001)

#if defined(STM32F303xE) || defined(STM32F398xx)
/*!< List of external triggers specific to device STM303xE: using Timer20     */
/* with ADC trigger input remap.                                              */
/* To remap ADC trigger from other timers/ExtLine to timer20: use macro       */
/* " __HAL_REMAPADCTRIGGER_ENABLE(...) " with parameters described below:     */

/*!< External triggers of injected group for ADC1&ADC2 only, specific to      */
/* device STM303xE: : using Timer20 with ADC trigger input remap              */
#define ADC_EXTERNALTRIGINJECCONV_T20_CC4        ADC_EXTERNALTRIGINJECCONV_T3_CC1  /*!< Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_JEXT13) */

/*!< External triggers of injected group for ADC3&ADC4 only, specific to      */
/* device STM303xE: : using Timer20 with ADC trigger input remap              */
#define ADC_EXTERNALTRIGINJECCONV_T20_CC2        ADC_EXTERNALTRIGINJECCONV_T7_TRGO /*!< Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC34_JEXT14) */

/*!< External triggers of regular group for ADC1&ADC2, ADC3&ADC4, specific to */
/* device STM303xE: : using Timer20 with ADC trigger input remap              */
/* Note: Triggers affected to group ADC1_2 by default, redirected to group    */
/*       ADC3_4 by driver when needed.                                        */
#define ADC_EXTERNALTRIGINJECCONV_T20_TRGO       (ADC_EXTERNALTRIGINJECCONV_T2_CC1 | ADC_EXTERNALTRIGCONV_T20_MASK)   /*!< For ADC1&ADC2: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_JEXT3) */
                                                                                                                      /*!< For ADC3&ADC4: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC34_JEXT5) */
#define ADC_EXTERNALTRIGINJECCONV_T20_TRGO2      (ADC_EXTERNALTRIGINJECCONV_EXT_IT15 | ADC_EXTERNALTRIGCONV_T20_MASK) /*!< For ADC1&ADC2: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_JEXT6) */
                                                                                                                      /*!< For ADC3&ADC4: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC34_JEXT11) */
#endif /* STM32F303xE || STM32F398xx */

#if defined(STM32F303xC) || defined(STM32F358xx)
#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC1)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T6_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                                                                           \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC3)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T7_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC2)   || \
                                                                                           \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO2) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC3)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_TRGO2) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T15_TRGO) || \
                                                                                           \
                                      ((INJTRIG) == ADC_INJECTED_SOFTWARE_START)          )
#endif /* STM32F303xC || STM32F358xx */

#if defined(STM32F303xE) || defined(STM32F398xx)
#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC1)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T6_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15)  || \
                                                                                            \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC3)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC4)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T7_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC2)    || \
                                                                                            \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO2)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC3)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC4)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_TRGO2)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T15_TRGO)  || \
                                                                                            \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T20_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T20_CC2)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T20_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T20_TRGO2) || \
                                                                                            \
                                      ((INJTRIG) == ADC_INJECTED_SOFTWARE_START)           )
#endif /* STM32F303xE || STM32F398xx */

#endif /* STM32F303xC || STM32F303xE || STM32F398xx || STM32F358xx */

#if defined(STM32F302xE) || \
    defined(STM32F302xC)
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target (caution: applies to other ADCs sharing the same common group), */
/* sorted by trigger name:                                                    */

/* External triggers of injected group for ADC1&ADC2 */
#define ADC_EXTERNALTRIGINJECCONV_T1_CC4    ADC1_2_EXTERNALTRIGINJEC_T1_CC4
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO   ADC1_2_EXTERNALTRIGINJEC_T1_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO2  ADC1_2_EXTERNALTRIGINJEC_T1_TRGO2
#define ADC_EXTERNALTRIGINJECCONV_T2_CC1    ADC1_2_EXTERNALTRIGINJEC_T2_CC1
#define ADC_EXTERNALTRIGINJECCONV_T2_TRGO   ADC1_2_EXTERNALTRIGINJEC_T2_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T3_CC1    ADC1_2_EXTERNALTRIGINJEC_T3_CC1
#define ADC_EXTERNALTRIGINJECCONV_T3_CC3    ADC1_2_EXTERNALTRIGINJEC_T3_CC3
#define ADC_EXTERNALTRIGINJECCONV_T3_CC4    ADC1_2_EXTERNALTRIGINJEC_T3_CC4
#define ADC_EXTERNALTRIGINJECCONV_T3_TRGO   ADC1_2_EXTERNALTRIGINJEC_T3_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T4_TRGO   ADC1_2_EXTERNALTRIGINJEC_T4_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T6_TRGO   ADC1_2_EXTERNALTRIGINJEC_T6_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T15_TRGO  ADC1_2_EXTERNALTRIGINJEC_T15_TRGO
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15  ADC1_2_EXTERNALTRIGINJEC_EXT_IT15

#define ADC_INJECTED_SOFTWARE_START     ((uint32_t)0x00000001)

#if defined(STM32F302xE)
/*!< List of external triggers specific to device STM302xE: using Timer20     */
/* with ADC trigger input remap.                                              */
/* To remap ADC trigger from other timers/ExtLine to timer20: use macro       */
/* " __HAL_REMAPADCTRIGGER_ENABLE(...) " with parameters described below:     */

/*!< External triggers of injected group for ADC1&ADC2 only, specific to      */
/* device STM302xE: : using Timer20 with ADC trigger input remap              */
#define ADC_EXTERNALTRIGINJECCONV_T20_CC4        ADC_EXTERNALTRIGINJECCONV_T3_CC1  /*!< Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_JEXT13) */
#define ADC_EXTERNALTRIGINJECCONV_T20_TRGO       (ADC_EXTERNALTRIGINJECCONV_T2_CC1 | ADC_EXTERNALTRIGCONV_T20_MASK)   /*!< For ADC1&ADC2: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_JEXT3) */
#define ADC_EXTERNALTRIGINJECCONV_T20_TRGO2      (ADC_EXTERNALTRIGINJECCONV_EXT_IT15 | ADC_EXTERNALTRIGCONV_T20_MASK) /*!< For ADC1&ADC2: Remap trigger using macro __HAL_REMAPADCTRIGGER_ENABLE(HAL_REMAPADCTRIGGER_ADC12_JEXT6) */
#endif /* STM32F302xE */

#if defined(STM32F302xE)
#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO2)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC1)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC3)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T6_TRGO)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T15_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T20_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T20_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T20_TRGO2) || \
                                      ((INJTRIG) == ADC_INJECTED_SOFTWARE_START)             )
#endif /* STM32F302xE */

#if defined(STM32F302xC)
#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO2) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC1)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC3)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T6_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T15_TRGO) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                      ((INJTRIG) == ADC_INJECTED_SOFTWARE_START)          )
#endif /* STM32F302xC */

#endif /* STM32F302xE || */
       /* STM32F302xC    */

#if defined(STM32F303x8) || defined(STM32F328xx)
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target (caution: applies to other ADCs sharing the same common group), */
/* sorted by trigger name:                                                    */

/* External triggers of injected group for ADC1&ADC2 */
#define ADC_EXTERNALTRIGINJECCONV_T1_CC4       ADC1_2_EXTERNALTRIGINJEC_T1_CC4
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO      ADC1_2_EXTERNALTRIGINJEC_T1_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO2     ADC1_2_EXTERNALTRIGINJEC_T1_TRGO2
#define ADC_EXTERNALTRIGINJECCONV_T2_CC1       ADC1_2_EXTERNALTRIGINJEC_T2_CC1
#define ADC_EXTERNALTRIGINJECCONV_T2_TRGO      ADC1_2_EXTERNALTRIGINJEC_T2_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T3_CC1       ADC1_2_EXTERNALTRIGINJEC_T3_CC1
#define ADC_EXTERNALTRIGINJECCONV_T3_CC3       ADC1_2_EXTERNALTRIGINJEC_T3_CC3
#define ADC_EXTERNALTRIGINJECCONV_T3_CC4       ADC1_2_EXTERNALTRIGINJEC_T3_CC4
#define ADC_EXTERNALTRIGINJECCONV_T3_TRGO      ADC1_2_EXTERNALTRIGINJEC_T3_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T4_TRGO      ADC1_2_EXTERNALTRIGINJEC_T4_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T6_TRGO      ADC1_2_EXTERNALTRIGINJEC_T6_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T8_CC4       ADC1_2_EXTERNALTRIGINJEC_T8_CC4
#define ADC_EXTERNALTRIGINJECCONV_T8_TRGO      ADC1_2_EXTERNALTRIGINJEC_T8_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T8_TRGO2     ADC1_2_EXTERNALTRIGINJEC_T8_TRGO2
#define ADC_EXTERNALTRIGINJECCONV_T15_TRGO     ADC1_2_EXTERNALTRIGINJEC_T15_TRGO
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15     ADC1_2_EXTERNALTRIGINJEC_EXT_IT15

#define ADC_INJECTED_SOFTWARE_START     ((uint32_t)0x00000001)

#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO2) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_TRGO2) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC3)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC1)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T6_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T15_TRGO) || \
                                      ((INJTRIG) == ADC_INJECTED_SOFTWARE_START)          )
#endif /* STM32F303x8 || STM32F328xx */

#if defined(STM32F334x8)
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target (caution: applies to other ADCs sharing the same common group), */
/* sorted by trigger name:                                                    */

/* External triggers of injected group for ADC1&ADC2 */
#define ADC_EXTERNALTRIGINJECCONV_T1_CC4       ADC1_2_EXTERNALTRIGINJEC_T1_CC4
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO      ADC1_2_EXTERNALTRIGINJEC_T1_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO2     ADC1_2_EXTERNALTRIGINJEC_T1_TRGO2
#define ADC_EXTERNALTRIGINJECCONV_T2_CC1       ADC1_2_EXTERNALTRIGINJEC_T2_CC1
#define ADC_EXTERNALTRIGINJECCONV_T2_TRGO      ADC1_2_EXTERNALTRIGINJEC_T2_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T3_CC1       ADC1_2_EXTERNALTRIGINJEC_T3_CC1
#define ADC_EXTERNALTRIGINJECCONV_T3_CC3       ADC1_2_EXTERNALTRIGINJEC_T3_CC3
#define ADC_EXTERNALTRIGINJECCONV_T3_CC4       ADC1_2_EXTERNALTRIGINJEC_T3_CC4
#define ADC_EXTERNALTRIGINJECCONV_T3_TRGO      ADC1_2_EXTERNALTRIGINJEC_T3_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T6_TRGO      ADC1_2_EXTERNALTRIGINJEC_T6_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T15_TRGO     ADC1_2_EXTERNALTRIGINJEC_T15_TRGO
#define ADC_EXTERNALTRIGINJECCONV_HRTIM_TRG2   ADC1_2_EXTERNALTRIGINJEC_HRTIM_TRG2
#define ADC_EXTERNALTRIGINJECCONV_HRTIM_TRG4   ADC1_2_EXTERNALTRIGINJEC_HRTIM_TRG4
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15     ADC1_2_EXTERNALTRIGINJEC_EXT_IT15

#define ADC_INJECTED_SOFTWARE_START     ((uint32_t)0x00000001)

#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO2)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_HRTIM_TRG2) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_HRTIM_TRG4) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC3)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_TRGO)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC1)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T6_TRGO)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T15_TRGO)   || \
                                      ((INJTRIG) == ADC_INJECTED_SOFTWARE_START)            )
#endif /* STM32F334x8 */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/* List of external triggers with generic trigger name, sorted by trigger     */
/* name:                                                                      */

/* External triggers of injected group for ADC1 */
#define ADC_EXTERNALTRIGINJECCONV_T1_CC4     ADC1_EXTERNALTRIGINJEC_T1_CC4
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO    ADC1_EXTERNALTRIGINJEC_T1_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO2   ADC1_EXTERNALTRIGINJEC_T1_TRGO2
#define ADC_EXTERNALTRIGINJECCONV_T6_TRGO    ADC1_EXTERNALTRIGINJEC_T6_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T15_TRGO   ADC1_EXTERNALTRIGINJEC_T15_TRGO
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15   ADC1_EXTERNALTRIGINJEC_EXT_IT15

#define ADC_INJECTED_SOFTWARE_START     ((uint32_t)0x00000001)

#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO2) || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T6_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T15_TRGO) || \
                                      ((INJTRIG) == ADC_INJECTED_SOFTWARE_START)          )
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */
/**
  * @}
  */

/** @defgroup ADCEx_Internal_HAL_driver_Ext_trig_src_Injected ADC Extended External Trigger Source of Injected Group (Internal)
  * @{
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
/* List of external triggers sorted of groups ADC1&ADC2 and/or ADC3&ADC4:     */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */

/* External triggers for injected groups of ADC1 & ADC2 */
#define ADC1_2_EXTERNALTRIGINJEC_T1_TRGO    ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIGINJEC_T1_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_0)
#define ADC1_2_EXTERNALTRIGINJEC_T2_TRGO    ((uint32_t)ADC_JSQR_JEXTSEL_1)
#define ADC1_2_EXTERNALTRIGINJEC_T2_CC1     ((uint32_t)(ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_2)
#define ADC1_2_EXTERNALTRIGINJEC_T4_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_EXT_IT15   ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T8_CC4     ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T1_TRGO2   ((uint32_t)ADC_JSQR_JEXTSEL_3)
#define ADC1_2_EXTERNALTRIGINJEC_T8_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T8_TRGO2   ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC3     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC1     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T6_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T15_TRGO   ((uint32_t)ADC_JSQR_JEXTSEL)

/* External triggers for injected groups of ADC3 & ADC4 */
/* Note: External triggers JEXT2 and JEXT5 are the same (TIM4_CC3 event).     */
/*       JEXT2 is the main trigger, JEXT5 could be redirected to another      */
/*       in future devices.                                                   */
/*       However, this channel is implemented with a SW offset of 0x10000 for */
/*       differentiation between similar triggers of common groups ADC1&ADC2, */
/*       ADC3&ADC4 (Differentiation processed into macro                      */
/*       __HAL_ADC_JSQR_JEXTSEL)                                              */
#define ADC3_4_EXTERNALTRIGINJEC_T1_TRGO    ((uint32_t)0x00000000)
#define ADC3_4_EXTERNALTRIGINJEC_T1_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_0)
#define ADC3_4_EXTERNALTRIGINJEC_T4_CC3     ((uint32_t)ADC_JSQR_JEXTSEL_1 | 0x10000)
#define ADC3_4_EXTERNALTRIGINJEC_T8_CC2     ((uint32_t)(ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC3_4_EXTERNALTRIGINJEC_T8_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_2)

#if defined(STM32F303xE) || defined(STM32F398xx)
#define ADC3_4_EXTERNALTRIGINJEC_T20_TRGO   ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#endif /* STM32F303xE || STM32F398xx */

#define ADC3_4_EXTERNALTRIGINJEC_T4_CC4     ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC3_4_EXTERNALTRIGINJEC_T4_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC3_4_EXTERNALTRIGINJEC_T1_TRGO2   ((uint32_t)ADC_JSQR_JEXTSEL_3)
#define ADC3_4_EXTERNALTRIGINJEC_T8_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_0))
#define ADC3_4_EXTERNALTRIGINJEC_T8_TRGO2   ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1))
#define ADC3_4_EXTERNALTRIGINJEC_T1_CC3     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC3_4_EXTERNALTRIGINJEC_T3_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2))
#define ADC3_4_EXTERNALTRIGINJEC_T2_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#define ADC3_4_EXTERNALTRIGINJEC_T7_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC3_4_EXTERNALTRIGINJEC_T15_TRGO   ((uint32_t)ADC_JSQR_JEXTSEL)
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F302xE) || \
    defined(STM32F302xC)
/* List of external triggers of group ADC1&ADC2:                              */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_2_EXTERNALTRIGINJEC_T1_TRGO    ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIGINJEC_T1_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_0)
#define ADC1_2_EXTERNALTRIGINJEC_T2_TRGO    ((uint32_t)ADC_JSQR_JEXTSEL_1)
#define ADC1_2_EXTERNALTRIGINJEC_T2_CC1     ((uint32_t)(ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_2)
#define ADC1_2_EXTERNALTRIGINJEC_T4_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_EXT_IT15   ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T1_TRGO2   ((uint32_t)ADC_JSQR_JEXTSEL_3)
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC3     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC1     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T6_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T15_TRGO   ((uint32_t)ADC_JSQR_JEXTSEL)
#endif /* STM32F302xE || */
       /* STM32F302xC    */
      
#if defined(STM32F303x8) || defined(STM32F328xx)
/* List of external triggers of group ADC1&ADC2:                              */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_2_EXTERNALTRIGINJEC_T1_TRGO    ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIGINJEC_T1_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_0)
#define ADC1_2_EXTERNALTRIGINJEC_T2_TRGO    ((uint32_t)ADC_JSQR_JEXTSEL_1)
#define ADC1_2_EXTERNALTRIGINJEC_T2_CC1     ((uint32_t)(ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_2)
#define ADC1_2_EXTERNALTRIGINJEC_T4_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_EXT_IT15   ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T8_CC4     ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T1_TRGO2   ((uint32_t)ADC_JSQR_JEXTSEL_3)
#define ADC1_2_EXTERNALTRIGINJEC_T8_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T8_TRGO2   ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC3     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC1     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T6_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T15_TRGO   ((uint32_t)ADC_JSQR_JEXTSEL)
#endif /* STM32F303x8 || STM32F328xx */

#if defined(STM32F334x8)
/* List of external triggers of group ADC1&ADC2:                              */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_2_EXTERNALTRIGINJEC_T1_TRGO     ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIGINJEC_T1_CC4      ((uint32_t)ADC_JSQR_JEXTSEL_0)
#define ADC1_2_EXTERNALTRIGINJEC_T2_TRGO     ((uint32_t)ADC_JSQR_JEXTSEL_1)
#define ADC1_2_EXTERNALTRIGINJEC_T2_CC1      ((uint32_t)(ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC4      ((uint32_t)ADC_JSQR_JEXTSEL_2)
#define ADC1_2_EXTERNALTRIGINJEC_EXT_IT15    ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T1_TRGO2    ((uint32_t)ADC_JSQR_JEXTSEL_3)
#define ADC1_2_EXTERNALTRIGINJEC_HRTIM_TRG2  ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_HRTIM_TRG4  ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC3      ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_TRGO     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC1      ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T6_TRGO     ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_2_EXTERNALTRIGINJEC_T15_TRGO    ((uint32_t)ADC_JSQR_JEXTSEL)
#endif /* STM32F334x8 */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/* List of external triggers of injected group for ADC1:                      */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_EXTERNALTRIGINJEC_T1_TRGO    ((uint32_t)0x00000000)
#define ADC1_EXTERNALTRIGINJEC_T1_CC4     ((uint32_t)ADC_JSQR_JEXTSEL_0)
#define ADC1_EXTERNALTRIGINJEC_EXT_IT15   ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_EXTERNALTRIGINJEC_T1_TRGO2   ((uint32_t)ADC_JSQR_JEXTSEL_3)
#define ADC1_EXTERNALTRIGINJEC_T6_TRGO    ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))
#define ADC1_EXTERNALTRIGINJEC_T15_TRGO   ((uint32_t)ADC_JSQR_JEXTSEL)
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */
/**
  * @}
  */

/** @defgroup ADCEx_Common_mode ADC Extended Dual ADC Mode
  * @{
  */
#define ADC_MODE_INDEPENDENT                  ((uint32_t)(0x00000000))
#define ADC_DUALMODE_REGSIMULT_INJECSIMULT    ((uint32_t)(ADC12_CCR_MULTI_0))
#define ADC_DUALMODE_REGSIMULT_ALTERTRIG      ((uint32_t)(ADC12_CCR_MULTI_1))
#define ADC_DUALMODE_INJECSIMULT              ((uint32_t)(ADC12_CCR_MULTI_2 | ADC12_CCR_MULTI_0))
#define ADC_DUALMODE_REGSIMULT                ((uint32_t)(ADC12_CCR_MULTI_2 | ADC12_CCR_MULTI_1))
#define ADC_DUALMODE_INTERL                   ((uint32_t)(ADC12_CCR_MULTI_2 | ADC12_CCR_MULTI_1 | ADC12_CCR_MULTI_0))
#define ADC_DUALMODE_ALTERTRIG                ((uint32_t)(ADC12_CCR_MULTI_3 | ADC12_CCR_MULTI_0))

#define IS_ADC_MODE(MODE) (((MODE) == ADC_MODE_INDEPENDENT)               || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT_INJECSIMULT) || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT_ALTERTRIG)   || \
                           ((MODE) == ADC_DUALMODE_INJECSIMULT)           || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT)             || \
                           ((MODE) == ADC_DUALMODE_INTERL)                || \
                           ((MODE) == ADC_DUALMODE_ALTERTRIG)               )
/**
  * @}
  */


/** @defgroup ADCEx_Direct_memory_access_mode_for_multimode ADC Extended DMA Mode for Dual ADC Mode
  * @{
  */
#define ADC_DMAACCESSMODE_DISABLED      ((uint32_t)0x00000000)         /*!< DMA multimode disabled: each ADC will use its own DMA channel */
#define ADC_DMAACCESSMODE_12_10_BITS    ((uint32_t)ADC12_CCR_MDMA_1)   /*!< DMA multimode enabled (one DMA channel for both ADC, DMA of ADC master) for 12 and 10 bits resolution */
#define ADC_DMAACCESSMODE_8_6_BITS      ((uint32_t)ADC12_CCR_MDMA)     /*!< DMA multimode enabled (one DMA channel for both ADC, DMA of ADC master) for 8 and 6 bits resolution */

#define IS_ADC_DMA_ACCESS_MODE(MODE) (((MODE) == ADC_DMAACCESSMODE_DISABLED)   || \
                                      ((MODE) == ADC_DMAACCESSMODE_12_10_BITS) || \
                                      ((MODE) == ADC_DMAACCESSMODE_8_6_BITS)     )
/**
  * @}
  */

/** @defgroup ADCEx_delay_between_2_sampling_phases ADC Extended Delay Between 2 Sampling Phases
  * @{
  */
#define ADC_TWOSAMPLINGDELAY_1CYCLE     ((uint32_t)(0x00000000))
#define ADC_TWOSAMPLINGDELAY_2CYCLES    ((uint32_t)(ADC12_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_3CYCLES    ((uint32_t)(ADC12_CCR_DELAY_1))
#define ADC_TWOSAMPLINGDELAY_4CYCLES    ((uint32_t)(ADC12_CCR_DELAY_1 | ADC12_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_5CYCLES    ((uint32_t)(ADC12_CCR_DELAY_2))
#define ADC_TWOSAMPLINGDELAY_6CYCLES    ((uint32_t)(ADC12_CCR_DELAY_2 | ADC12_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_7CYCLES    ((uint32_t)(ADC12_CCR_DELAY_2 | ADC12_CCR_DELAY_1))
#define ADC_TWOSAMPLINGDELAY_8CYCLES    ((uint32_t)(ADC12_CCR_DELAY_2 | ADC12_CCR_DELAY_1 | ADC12_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_9CYCLES    ((uint32_t)(ADC12_CCR_DELAY_3))
#define ADC_TWOSAMPLINGDELAY_10CYCLES   ((uint32_t)(ADC12_CCR_DELAY_3 | ADC12_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_11CYCLES   ((uint32_t)(ADC12_CCR_DELAY_3 | ADC12_CCR_DELAY_1))
#define ADC_TWOSAMPLINGDELAY_12CYCLES   ((uint32_t)(ADC12_CCR_DELAY_3 | ADC12_CCR_DELAY_1 | ADC12_CCR_DELAY_0))

#define IS_ADC_SAMPLING_DELAY(DELAY) (((DELAY) == ADC_TWOSAMPLINGDELAY_1CYCLE)   || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_2CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_3CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_4CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_5CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_6CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_7CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_8CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_9CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_10CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_11CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_12CYCLES)   )
/**
  * @}
  */

/** @defgroup ADCEx_analog_watchdog_number ADC Extended Analog Watchdog Selection
  * @{
  */
#define ADC_ANALOGWATCHDOG_1                    ((uint32_t)0x00000001)
#define ADC_ANALOGWATCHDOG_2                    ((uint32_t)0x00000002)
#define ADC_ANALOGWATCHDOG_3                    ((uint32_t)0x00000003)

#define IS_ADC_ANALOG_WATCHDOG_NUMBER(WATCHDOG) (((WATCHDOG) == ADC_ANALOGWATCHDOG_1) || \
                                                 ((WATCHDOG) == ADC_ANALOGWATCHDOG_2) || \
                                                 ((WATCHDOG) == ADC_ANALOGWATCHDOG_3)   )
/**
  * @}
  */

/** @defgroup ADCEx_analog_watchdog_mode ADC Extended Analog Watchdog Mode
  * @{
  */
#define ADC_ANALOGWATCHDOG_NONE                 ((uint32_t) 0x00000000)
#define ADC_ANALOGWATCHDOG_SINGLE_REG           ((uint32_t)(ADC_CFGR_AWD1SGL | ADC_CFGR_AWD1EN))
#define ADC_ANALOGWATCHDOG_SINGLE_INJEC         ((uint32_t)(ADC_CFGR_AWD1SGL | ADC_CFGR_JAWD1EN))
#define ADC_ANALOGWATCHDOG_SINGLE_REGINJEC      ((uint32_t)(ADC_CFGR_AWD1SGL | ADC_CFGR_AWD1EN | ADC_CFGR_JAWD1EN))
#define ADC_ANALOGWATCHDOG_ALL_REG              ((uint32_t) ADC_CFGR_AWD1EN)
#define ADC_ANALOGWATCHDOG_ALL_INJEC            ((uint32_t) ADC_CFGR_JAWD1EN)
#define ADC_ANALOGWATCHDOG_ALL_REGINJEC         ((uint32_t)(ADC_CFGR_AWD1EN | ADC_CFGR_JAWD1EN))

#define IS_ADC_ANALOG_WATCHDOG_MODE(WATCHDOG) (((WATCHDOG) == ADC_ANALOGWATCHDOG_NONE)             || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REG)       || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)     || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)  || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REG)          || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_INJEC)        || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REGINJEC)       )
/**
  * @}
  */

/** @defgroup ADC_conversion_group ADC Conversion Group
  * @{
  */
#define REGULAR_GROUP             ((uint32_t)(ADC_FLAG_EOC | ADC_FLAG_EOS))
#define INJECTED_GROUP            ((uint32_t)(ADC_FLAG_JEOC | ADC_FLAG_JEOS))
#define REGULAR_INJECTED_GROUP    ((uint32_t)(ADC_FLAG_EOC | ADC_FLAG_EOS | ADC_FLAG_JEOC | ADC_FLAG_JEOS))

#define IS_ADC_CONVERSION_GROUP(CONVERSION) (((CONVERSION) == REGULAR_GROUP)        || \
                                            ((CONVERSION) == INJECTED_GROUP)        || \
                                            ((CONVERSION) == REGULAR_INJECTED_GROUP)  )
/**
  * @}
  */

/** @defgroup ADCEx_Event_type ADC Extended Event Type
  * @{
  */
#define AWD1_EVENT           ((uint32_t)ADC_FLAG_AWD1)  /*!< ADC Analog watchdog 1 event (main analog watchdog, present on all STM32 devices) */
#define AWD2_EVENT           ((uint32_t)ADC_FLAG_AWD2)  /*!< ADC Analog watchdog 2 event (additional analog watchdog, present only on STM32F3 devices) */
#define AWD3_EVENT           ((uint32_t)ADC_FLAG_AWD3)  /*!< ADC Analog watchdog 3 event (additional analog watchdog, present only on STM32F3 devices) */
#define OVR_EVENT            ((uint32_t)ADC_FLAG_OVR)   /*!< ADC overrun event */
#define JQOVF_EVENT          ((uint32_t)ADC_FLAG_JQOVF) /*!< ADC Injected Context Queue Overflow event */

#define AWD_EVENT            AWD1_EVENT         /*!< ADC Analog watchdog 1 event: Naming for compatibility with other STM32 devices having only 1 analog watchdog */

#define IS_ADC_EVENT_TYPE(EVENT) (((EVENT) == AWD_EVENT)  || \
                                  ((EVENT) == AWD2_EVENT) || \
                                  ((EVENT) == AWD3_EVENT) || \
                                  ((EVENT) == OVR_EVENT)  || \
                                  ((EVENT) == JQOVF_EVENT)  )
/**
  * @}
  */

/** @defgroup ADCEx_interrupts_definition ADC Extended Interrupts Definition
  * @{
  */
#define ADC_IT_RDY           ADC_IER_RDY        /*!< ADC Ready (ADRDY) interrupt source */
#define ADC_IT_EOSMP         ADC_IER_EOSMP      /*!< ADC End of Sampling interrupt source */
#define ADC_IT_EOC           ADC_IER_EOC        /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_EOS           ADC_IER_EOS        /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IT_OVR           ADC_IER_OVR        /*!< ADC overrun interrupt source */
#define ADC_IT_JEOC          ADC_IER_JEOC       /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IT_JEOS          ADC_IER_JEOS       /*!< ADC End of Injected sequence of Conversions interrupt source */
#define ADC_IT_AWD1          ADC_IER_AWD1       /*!< ADC Analog watchdog 1 interrupt source (main analog watchdog, present on all STM32 devices) */
#define ADC_IT_AWD2          ADC_IER_AWD2       /*!< ADC Analog watchdog 2 interrupt source (additional analog watchdog, present only on STM32F3 devices) */
#define ADC_IT_AWD3          ADC_IER_AWD3       /*!< ADC Analog watchdog 3 interrupt source (additional analog watchdog, present only on STM32F3 devices) */
#define ADC_IT_JQOVF         ADC_IER_JQOVF      /*!< ADC Injected Context Queue Overflow interrupt source */

#define ADC_IT_AWD           ADC_IT_AWD1        /*!< ADC Analog watchdog 1 interrupt source: Naming for compatibility with other STM32 devices having only 1 analog watchdog */

/* Check of single flag */
#define IS_ADC_IT(IT) (((IT) == ADC_IT_RDY)  || ((IT) == ADC_IT_EOSMP) || \
                       ((IT) == ADC_IT_EOC)  || ((IT) == ADC_IT_EOS)   || \
                       ((IT) == ADC_IT_OVR)  || ((IT) == ADC_IT_EOS)   || \
                       ((IT) == ADC_IT_JEOS) || ((IT) == ADC_IT_AWD1)  || \
                       ((IT) == ADC_IT_AWD2) || ((IT) == ADC_IT_AWD3)  || \
                       ((IT) == ADC_IT_JQOVF)                            )
/**
  * @}
  */

/** @defgroup ADCEx_flags_definition ADC Extended Flags Definition
  * @{
  */
#define ADC_FLAG_RDY           ADC_ISR_ADRD     /*!< ADC Ready (ADRDY) flag */
#define ADC_FLAG_EOSMP         ADC_ISR_EOSMP    /*!< ADC End of Sampling flag */
#define ADC_FLAG_EOC           ADC_ISR_EOC      /*!< ADC End of Regular Conversion flag */
#define ADC_FLAG_EOS           ADC_ISR_EOS      /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_FLAG_OVR           ADC_ISR_OVR      /*!< ADC overrun flag */
#define ADC_FLAG_JEOC          ADC_ISR_JEOC     /*!< ADC End of Injected Conversion flag */
#define ADC_FLAG_JEOS          ADC_ISR_JEOS     /*!< ADC End of Injected sequence of Conversions flag */
#define ADC_FLAG_AWD1          ADC_ISR_AWD1     /*!< ADC Analog watchdog 1 flag (main analog watchdog, present on all STM32 devices) */
#define ADC_FLAG_AWD2          ADC_ISR_AWD2     /*!< ADC Analog watchdog 2 flag (additional analog watchdog, present only on STM32F3 devices) */
#define ADC_FLAG_AWD3          ADC_ISR_AWD3     /*!< ADC Analog watchdog 3 flag (additional analog watchdog, present only on STM32F3 devices) */
#define ADC_FLAG_JQOVF         ADC_ISR_JQOVF    /*!< ADC Injected Context Queue Overflow flag */

#define ADC_FLAG_AWD           ADC_FLAG_AWD1    /*!< ADC Analog watchdog 1 flag: Naming for compatibility with other STM32 devices having only 1 analog watchdog */

#define ADC_FLAG_ALL    (ADC_FLAG_RDY | ADC_FLAG_EOSMP | ADC_FLAG_EOC | ADC_FLAG_EOS |  \
                         ADC_FLAG_JEOC | ADC_FLAG_JEOS | ADC_FLAG_OVR | ADC_FLAG_AWD1 | \
                         ADC_FLAG_AWD2 | ADC_FLAG_AWD3 | ADC_FLAG_JQOVF)

/* Combination of all post-conversion flags bits: EOC/EOS, JEOC/JEOS, OVR, AWDx */
#define ADC_FLAG_POSTCONV_ALL (ADC_FLAG_EOC | ADC_FLAG_EOS  | ADC_FLAG_JEOC | ADC_FLAG_JEOS | \
                               ADC_FLAG_OVR | ADC_FLAG_AWD1 | ADC_FLAG_AWD2 | ADC_FLAG_AWD3 | \
                               ADC_FLAG_JQOVF)

/* Check of single flag */
#define IS_ADC_FLAG(FLAG) (((FLAG) == ADC_FLAG_RDY)  || ((FLAG) == ADC_FLAG_EOSMP) || \
                           ((FLAG) == ADC_FLAG_EOC)  || ((FLAG) == ADC_FLAG_EOS)   || \
                           ((FLAG) == ADC_FLAG_OVR)  || ((FLAG) == ADC_FLAG_JEOC)  || \
                           ((FLAG) == ADC_FLAG_JEOS) || ((FLAG) == ADC_FLAG_AWD1)  || \
                           ((FLAG) == ADC_FLAG_AWD2) || ((FLAG) == ADC_FLAG_AWD3)  || \
                           ((FLAG) == ADC_FLAG_JQOVF)                                )
/**
  * @}
  */

/** @defgroup ADC_multimode_bits ADC Multimode Bits
  * @{
  */
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define ADC_CCR_MULTI             ADC12_CCR_MULTI        /*!< Multi ADC mode selection */
#define ADC_CCR_MULTI_0           ADC12_CCR_MULTI_0      /*!< MULTI bit 0 */
#define ADC_CCR_MULTI_1           ADC12_CCR_MULTI_1      /*!< MULTI bit 1 */
#define ADC_CCR_MULTI_2           ADC12_CCR_MULTI_2      /*!< MULTI bit 2 */
#define ADC_CCR_MULTI_3           ADC12_CCR_MULTI_3      /*!< MULTI bit 3 */
#define ADC_CCR_MULTI_4           ADC12_CCR_MULTI_4      /*!< MULTI bit 4 */
#define ADC_CCR_DELAY             ADC12_CCR_DELAY        /*!< Delay between 2 sampling phases */
#define ADC_CCR_DELAY_0           ADC12_CCR_DELAY_0      /*!< DELAY bit 0 */
#define ADC_CCR_DELAY_1           ADC12_CCR_DELAY_1      /*!< DELAY bit 1 */
#define ADC_CCR_DELAY_2           ADC12_CCR_DELAY_2      /*!< DELAY bit 2 */
#define ADC_CCR_DELAY_3           ADC12_CCR_DELAY_3      /*!< DELAY bit 3 */
#define ADC_CCR_DMACFG            ADC12_CCR_DMACFG       /*!< DMA configuration for multi-ADC mode */
#define ADC_CCR_MDMA              ADC12_CCR_MDMA         /*!< DMA mode for multi-ADC mode */
#define ADC_CCR_MDMA_0            ADC12_CCR_MDMA_0       /*!< MDMA bit 0 */
#define ADC_CCR_MDMA_1            ADC12_CCR_MDMA_1       /*!< MDMA bit 1 */
#define ADC_CCR_CKMODE            ADC12_CCR_CKMODE       /*!< ADC clock mode */
#define ADC_CCR_CKMODE_0          ADC12_CCR_CKMODE_0     /*!< CKMODE bit 0 */
#define ADC_CCR_CKMODE_1          ADC12_CCR_CKMODE_1     /*!< CKMODE bit 1 */
#define ADC_CCR_VREFEN            ADC12_CCR_VREFEN       /*!< VREFINT enable */
#define ADC_CCR_TSEN              ADC12_CCR_TSEN         /*!< Temperature sensor enable */
#define ADC_CCR_VBATEN            ADC12_CCR_VBATEN       /*!< VBAT enable */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx    */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define ADC_CCR_MULTI             ADC1_CCR_MULTI        /*!< Multi ADC mode selection */
#define ADC_CCR_MULTI_0           ADC1_CCR_MULTI_0      /*!< MULTI bit 0 */
#define ADC_CCR_MULTI_1           ADC1_CCR_MULTI_1      /*!< MULTI bit 1 */
#define ADC_CCR_MULTI_2           ADC1_CCR_MULTI_2      /*!< MULTI bit 2 */
#define ADC_CCR_MULTI_3           ADC1_CCR_MULTI_3      /*!< MULTI bit 3 */
#define ADC_CCR_MULTI_4           ADC1_CCR_MULTI_4      /*!< MULTI bit 4 */
#define ADC_CCR_DELAY             ADC1_CCR_DELAY        /*!< Delay between 2 sampling phases */
#define ADC_CCR_DELAY_0           ADC1_CCR_DELAY_0      /*!< DELAY bit 0 */
#define ADC_CCR_DELAY_1           ADC1_CCR_DELAY_1      /*!< DELAY bit 1 */
#define ADC_CCR_DELAY_2           ADC1_CCR_DELAY_2      /*!< DELAY bit 2 */
#define ADC_CCR_DELAY_3           ADC1_CCR_DELAY_3      /*!< DELAY bit 3 */
#define ADC_CCR_DMACFG            ADC1_CCR_DMACFG       /*!< DMA configuration for multi-ADC mode */
#define ADC_CCR_MDMA              ADC1_CCR_MDMA         /*!< DMA mode for multi-ADC mode */
#define ADC_CCR_MDMA_0            ADC1_CCR_MDMA_0       /*!< MDMA bit 0 */
#define ADC_CCR_MDMA_1            ADC1_CCR_MDMA_1       /*!< MDMA bit 1 */
#define ADC_CCR_CKMODE            ADC1_CCR_CKMODE       /*!< ADC clock mode */
#define ADC_CCR_CKMODE_0          ADC1_CCR_CKMODE_0     /*!< CKMODE bit 0 */
#define ADC_CCR_CKMODE_1          ADC1_CCR_CKMODE_1     /*!< CKMODE bit 1 */
#define ADC_CCR_VREFEN            ADC1_CCR_VREFEN       /*!< VREFINT enable */
#define ADC_CCR_TSEN              ADC1_CCR_TSEN         /*!< Temperature sensor enable */
#define ADC_CCR_VBATEN            ADC1_CCR_VBATEN       /*!< VBAT enable */
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */


/**
  * @}
  */

/** @defgroup ADCEx_range_verification ADC Extended Range Verification
  * in function of ADC resolution selected (12, 10, 8 or 6 bits)
  * @{
  */
#define IS_ADC_RANGE(RESOLUTION, ADC_VALUE)                                         \
   ((((RESOLUTION) == ADC_RESOLUTION12b) && ((ADC_VALUE) <= ((uint32_t)0x0FFF))) || \
    (((RESOLUTION) == ADC_RESOLUTION10b) && ((ADC_VALUE) <= ((uint32_t)0x03FF))) || \
    (((RESOLUTION) == ADC_RESOLUTION8b)  && ((ADC_VALUE) <= ((uint32_t)0x00FF))) || \
    (((RESOLUTION) == ADC_RESOLUTION6b)  && ((ADC_VALUE) <= ((uint32_t)0x003F)))   )
/**
  * @}
  */

/** @defgroup ADC_injected_nb_conv_verification ADC Injected Conversion Number Verification
  * @{
  */
#define IS_ADC_INJECTED_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)4)))
/**
  * @}
  */

/** @defgroup ADC_regular_nb_conv_verification ADC Regular Conversion Number Verification
  * @{
  */
#define IS_ADC_REGULAR_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)16)))
/**
  * @}
  */

/** @defgroup ADC_regular_discontinuous_mode_number_verification ADC Regular Discontinuous Mode NumberVerification
  * @{
  */
#define IS_ADC_REGULAR_DISCONT_NUMBER(NUMBER) (((NUMBER) >= ((uint32_t)1)) && ((NUMBER) <= ((uint32_t)8)))
/**
  * @}
  */

/** @defgroup ADC_calibration_factor_length_verification ADC Calibration Factor Length Verification
  * @{
  */
/**
  * @brief Calibration factor length verification (7 bits maximum)
  * @param _Calibration_Factor_: Calibration factor value
  * @retval None
  */
#define IS_ADC_CALFACT(_Calibration_Factor_) ((_Calibration_Factor_) <= ((uint32_t)0x7F))
/**
  * @}
  */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */


#if defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup ADCEx_Data_align ADC Extended Data Alignment
  * @{
  */
#define ADC_DATAALIGN_RIGHT      ((uint32_t)0x00000000)
#define ADC_DATAALIGN_LEFT       ((uint32_t)ADC_CR2_ALIGN)

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT)    )
/**
  * @}
  */

/** @defgroup ADCEx_Scan_mode ADC Extended Scan Mode
  * @{
  */
#define ADC_SCAN_DISABLE         ((uint32_t)0x00000000)
#define ADC_SCAN_ENABLE          ((uint32_t)0x00000001)

#define IS_ADC_SCAN_MODE(SCAN_MODE) (((SCAN_MODE) == ADC_SCAN_DISABLE) || \
                                     ((SCAN_MODE) == ADC_SCAN_ENABLE)    )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_edge_Regular ADC Extended External trigger enable for regular channels
  * @{
  */
#define ADC_EXTERNALTRIGCONVEDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGCONVEDGE_RISING         ((uint32_t)ADC_CR2_EXTTRIG)

#define IS_ADC_EXTTRIG_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGCONVEDGE_NONE)  || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING)  )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_source_Regular ADC Extended External trigger selection for regular group
  * @{
  */
/* List of external triggers with generic trigger name, sorted by trigger     */
/* name:                                                                      */

/* External triggers of regular group for ADC1 */
#define ADC_EXTERNALTRIGCONV_T2_CC2      ADC_EXTERNALTRIG_T2_CC2
#define ADC_EXTERNALTRIGCONV_T3_TRGO     ADC_EXTERNALTRIG_T3_TRGO
#define ADC_EXTERNALTRIGCONV_T4_CC2      ADC_EXTERNALTRIG_T4_CC2
#define ADC_EXTERNALTRIGCONV_T19_TRGO    ADC_EXTERNALTRIG_T19_TRGO
#define ADC_EXTERNALTRIGCONV_T19_CC3     ADC_EXTERNALTRIG_T19_CC3
#define ADC_EXTERNALTRIGCONV_T19_CC4     ADC_EXTERNALTRIG_T19_CC4
#define ADC_EXTERNALTRIGCONV_EXT_IT11    ADC_EXTERNALTRIG_EXT_IT11
#define ADC_SOFTWARE_START               ADC_SWSTART

#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T19_TRGO) || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T19_CC3)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T19_CC4)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11) || \
                                 ((REGTRIG) == ADC_SOFTWARE_START)              )
/**
  * @}
  */


/** @defgroup ADCEx_Internal_HAL_driver_Ext_trig_src_Regular ADC Extended External trigger selection for regular group (Used Internally)
  * @{
  */

/* List of external triggers of regular group for ADC1:                       */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */

/* External triggers of regular group for ADC1 */
#define ADC_EXTERNALTRIG_T19_TRGO          ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIG_T19_CC3           ((uint32_t)ADC_CR2_EXTSEL_0)
#define ADC_EXTERNALTRIG_T19_CC4           ((uint32_t)ADC_CR2_EXTSEL_1)
#define ADC_EXTERNALTRIG_T2_CC2            ((uint32_t)(ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIG_T3_TRGO           ((uint32_t)ADC_CR2_EXTSEL_2)
#define ADC_EXTERNALTRIG_T4_CC2            ((uint32_t)(ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIG_EXT_IT11          ((uint32_t)(ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1))
#define ADC_SWSTART                        ((uint32_t)(ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))

/**
  * @}
  */


/** @defgroup ADCEx_channels ADC Extended Channels
  * @{
  */
/* Note: Depending on devices, some channels may not be available on package  */
/*       pins. Refer to device datasheet for channels availability.           */
#define ADC_CHANNEL_0           ((uint32_t)0x00000000)
#define ADC_CHANNEL_1           ((uint32_t)(ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_2           ((uint32_t)(ADC_SQR3_SQ1_1))
#define ADC_CHANNEL_3           ((uint32_t)(ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_4           ((uint32_t)(ADC_SQR3_SQ1_2))
#define ADC_CHANNEL_5           ((uint32_t)(ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_6           ((uint32_t)(ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_1))
#define ADC_CHANNEL_7           ((uint32_t)(ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_8           ((uint32_t)(ADC_SQR3_SQ1_3))
#define ADC_CHANNEL_9           ((uint32_t)(ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_10          ((uint32_t)(ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_1))
#define ADC_CHANNEL_11          ((uint32_t)(ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_12          ((uint32_t)(ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_2))
#define ADC_CHANNEL_13          ((uint32_t)(ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_14          ((uint32_t)(ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_1))
#define ADC_CHANNEL_15          ((uint32_t)(ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_16          ((uint32_t)(ADC_SQR3_SQ1_4))
#define ADC_CHANNEL_17          ((uint32_t)(ADC_SQR3_SQ1_4 | ADC_SQR3_SQ1_0))
#define ADC_CHANNEL_18          ((uint32_t)(ADC_SQR3_SQ1_4 | ADC_SQR3_SQ1_1))

#define ADC_CHANNEL_TEMPSENSOR  ADC_CHANNEL_16
#define ADC_CHANNEL_VREFINT     ADC_CHANNEL_17
#define ADC_CHANNEL_VBAT        ADC_CHANNEL_18

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_0)           || \
                                 ((CHANNEL) == ADC_CHANNEL_1)           || \
                                 ((CHANNEL) == ADC_CHANNEL_2)           || \
                                 ((CHANNEL) == ADC_CHANNEL_3)           || \
                                 ((CHANNEL) == ADC_CHANNEL_4)           || \
                                 ((CHANNEL) == ADC_CHANNEL_5)           || \
                                 ((CHANNEL) == ADC_CHANNEL_6)           || \
                                 ((CHANNEL) == ADC_CHANNEL_7)           || \
                                 ((CHANNEL) == ADC_CHANNEL_8)           || \
                                 ((CHANNEL) == ADC_CHANNEL_9)           || \
                                 ((CHANNEL) == ADC_CHANNEL_10)          || \
                                 ((CHANNEL) == ADC_CHANNEL_11)          || \
                                 ((CHANNEL) == ADC_CHANNEL_12)          || \
                                 ((CHANNEL) == ADC_CHANNEL_13)          || \
                                 ((CHANNEL) == ADC_CHANNEL_14)          || \
                                 ((CHANNEL) == ADC_CHANNEL_15)          || \
                                 ((CHANNEL) == ADC_CHANNEL_TEMPSENSOR)  || \
                                 ((CHANNEL) == ADC_CHANNEL_VREFINT)     || \
                                 ((CHANNEL) == ADC_CHANNEL_VBAT)          )
/**
  * @}
  */

/** @defgroup ADCEx_sampling_times ADC Extended Sampling Times
  * @{
  */
#define ADC_SAMPLETIME_1CYCLE_5       ((uint32_t)0x00000000)                            /*!< Sampling time 1.5 ADC clock cycle */
#define ADC_SAMPLETIME_7CYCLES_5      ((uint32_t) ADC_SMPR2_SMP0_0)                     /*!< Sampling time 7.5 ADC clock cycles */
#define ADC_SAMPLETIME_13CYCLES_5     ((uint32_t) ADC_SMPR2_SMP0_1)                     /*!< Sampling time 13.5 ADC clock cycles */
#define ADC_SAMPLETIME_28CYCLES_5     ((uint32_t)(ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_0)) /*!< Sampling time 28.5 ADC clock cycles */
#define ADC_SAMPLETIME_41CYCLES_5     ((uint32_t) ADC_SMPR2_SMP0_2)                     /*!< Sampling time 41.5 ADC clock cycles */
#define ADC_SAMPLETIME_55CYCLES_5     ((uint32_t)(ADC_SMPR2_SMP0_2 | ADC_SMPR2_SMP0_0)) /*!< Sampling time 55.5 ADC clock cycles */
#define ADC_SAMPLETIME_71CYCLES_5     ((uint32_t)(ADC_SMPR2_SMP0_2 | ADC_SMPR2_SMP0_1)) /*!< Sampling time 71.5 ADC clock cycles */
#define ADC_SAMPLETIME_239CYCLES_5    ((uint32_t) ADC_SMPR2_SMP0)                       /*!< Sampling time 239.5 ADC clock cycles */

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_1CYCLE_5)    || \
                                  ((TIME) == ADC_SAMPLETIME_7CYCLES_5)   || \
                                  ((TIME) == ADC_SAMPLETIME_13CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_28CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_41CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_55CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_71CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_239CYCLES_5)   )
/**
  * @}
  */

/** @defgroup ADCEx_sampling_times_all_channels ADC Extended Sampling Times All Channels
  * @{
  */
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2                                          \
     (ADC_SMPR2_SMP9_2 | ADC_SMPR2_SMP8_2 | ADC_SMPR2_SMP7_2 | ADC_SMPR2_SMP6_2 |     \
      ADC_SMPR2_SMP5_2 | ADC_SMPR2_SMP4_2 | ADC_SMPR2_SMP3_2 | ADC_SMPR2_SMP2_2 |     \
      ADC_SMPR2_SMP1_2 | ADC_SMPR2_SMP0_2)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2                                          \
     (ADC_SMPR1_SMP17_2 | ADC_SMPR1_SMP16_2 | ADC_SMPR1_SMP15_2 | ADC_SMPR1_SMP14_2 | \
      ADC_SMPR1_SMP13_2 | ADC_SMPR1_SMP12_2 | ADC_SMPR1_SMP11_2 | ADC_SMPR1_SMP10_2 )

#define ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT1                                          \
     (ADC_SMPR2_SMP9_1 | ADC_SMPR2_SMP8_1 | ADC_SMPR2_SMP7_1 | ADC_SMPR2_SMP6_1 |     \
      ADC_SMPR2_SMP5_1 | ADC_SMPR2_SMP4_1 | ADC_SMPR2_SMP3_1 | ADC_SMPR2_SMP2_1 |     \
      ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP0_1)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1                                          \
     (ADC_SMPR1_SMP17_1 | ADC_SMPR1_SMP16_1 | ADC_SMPR1_SMP15_1 | ADC_SMPR1_SMP14_1 | \
      ADC_SMPR1_SMP13_1 | ADC_SMPR1_SMP12_1 | ADC_SMPR1_SMP11_1 | ADC_SMPR1_SMP10_1 )

#define ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT0                                          \
     (ADC_SMPR2_SMP9_0 | ADC_SMPR2_SMP8_0 | ADC_SMPR2_SMP7_0 | ADC_SMPR2_SMP6_0 |     \
      ADC_SMPR2_SMP5_0 | ADC_SMPR2_SMP4_0 | ADC_SMPR2_SMP3_0 | ADC_SMPR2_SMP2_0 |     \
      ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP0_0)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0                                          \
     (ADC_SMPR1_SMP17_0 | ADC_SMPR1_SMP16_0 | ADC_SMPR1_SMP15_0 | ADC_SMPR1_SMP14_0 | \
      ADC_SMPR1_SMP13_0 | ADC_SMPR1_SMP12_0 | ADC_SMPR1_SMP11_0 | ADC_SMPR1_SMP10_0 )

#define ADC_SAMPLETIME_1CYCLE5_SMPR2ALLCHANNELS    ((uint32_t)0x00000000)
#define ADC_SAMPLETIME_7CYCLES5_SMPR2ALLCHANNELS   (ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT0)
#define ADC_SAMPLETIME_13CYCLES5_SMPR2ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT1)
#define ADC_SAMPLETIME_28CYCLES5_SMPR2ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT1 | ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT0)
#define ADC_SAMPLETIME_41CYCLES5_SMPR2ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2)
#define ADC_SAMPLETIME_55CYCLES5_SMPR2ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2 | ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT0)
#define ADC_SAMPLETIME_71CYCLES5_SMPR2ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2 | ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT1)
#define ADC_SAMPLETIME_239CYCLES5_SMPR2ALLCHANNELS (ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2 | ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT1 | ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT0)

#define ADC_SAMPLETIME_1CYCLE5_SMPR1ALLCHANNELS    ((uint32_t)0x00000000)
#define ADC_SAMPLETIME_7CYCLES5_SMPR1ALLCHANNELS   (ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0)
#define ADC_SAMPLETIME_13CYCLES5_SMPR1ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1)
#define ADC_SAMPLETIME_28CYCLES5_SMPR1ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1 | ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0)
#define ADC_SAMPLETIME_41CYCLES5_SMPR1ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2)
#define ADC_SAMPLETIME_55CYCLES5_SMPR1ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2 | ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0)
#define ADC_SAMPLETIME_71CYCLES5_SMPR1ALLCHANNELS  (ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2 | ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1)
#define ADC_SAMPLETIME_239CYCLES5_SMPR1ALLCHANNELS (ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2 | ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1 | ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0)

/**
  * @}
  */

/** @defgroup ADCEx_regular_rank ADC Extended Regular Channel Rank
  * @{
  */
#define ADC_REGULAR_RANK_1    ((uint32_t)0x00000001)
#define ADC_REGULAR_RANK_2    ((uint32_t)0x00000002)
#define ADC_REGULAR_RANK_3    ((uint32_t)0x00000003)
#define ADC_REGULAR_RANK_4    ((uint32_t)0x00000004)
#define ADC_REGULAR_RANK_5    ((uint32_t)0x00000005)
#define ADC_REGULAR_RANK_6    ((uint32_t)0x00000006)
#define ADC_REGULAR_RANK_7    ((uint32_t)0x00000007)
#define ADC_REGULAR_RANK_8    ((uint32_t)0x00000008)
#define ADC_REGULAR_RANK_9    ((uint32_t)0x00000009)
#define ADC_REGULAR_RANK_10   ((uint32_t)0x0000000A)
#define ADC_REGULAR_RANK_11   ((uint32_t)0x0000000B)
#define ADC_REGULAR_RANK_12   ((uint32_t)0x0000000C)
#define ADC_REGULAR_RANK_13   ((uint32_t)0x0000000D)
#define ADC_REGULAR_RANK_14   ((uint32_t)0x0000000E)
#define ADC_REGULAR_RANK_15   ((uint32_t)0x0000000F)
#define ADC_REGULAR_RANK_16   ((uint32_t)0x00000010)

#define IS_ADC_REGULAR_RANK(CHANNEL) (((CHANNEL) == ADC_REGULAR_RANK_1 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_2 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_3 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_4 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_5 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_6 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_7 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_8 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_9 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_10) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_11) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_12) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_13) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_14) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_15) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_16)   )
/**
  * @}
  */
       
/** @defgroup ADCEx_injected_rank ADC Extended Injected Channel Rank
  * @{
  */
#define ADC_INJECTED_RANK_1    ((uint32_t)0x00000001)
#define ADC_INJECTED_RANK_2    ((uint32_t)0x00000002)
#define ADC_INJECTED_RANK_3    ((uint32_t)0x00000003)
#define ADC_INJECTED_RANK_4    ((uint32_t)0x00000004)

#define IS_ADC_INJECTED_RANK(CHANNEL) (((CHANNEL) == ADC_INJECTED_RANK_1) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_2) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_3) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_4)   )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_edge_Injected External Trigger Edge of Injected Group
  * @{
  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISING         ((uint32_t)ADC_CR2_JEXTTRIG)

#define IS_ADC_EXTTRIGINJEC_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_NONE)  || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISING)  )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_source_Injected External Trigger Source of Injected Group
  * @{
  */
/* External triggers for injected groups of ADC1 */
#define ADC_EXTERNALTRIGINJECCONV_T2_CC1       ADC_EXTERNALTRIGINJEC_T2_CC1
#define ADC_EXTERNALTRIGINJECCONV_T2_TRGO      ADC_EXTERNALTRIGINJEC_T2_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T3_CC4       ADC_EXTERNALTRIGINJEC_T3_CC4
#define ADC_EXTERNALTRIGINJECCONV_T4_TRGO      ADC_EXTERNALTRIGINJEC_T4_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T19_CC1      ADC_EXTERNALTRIGINJEC_T19_CC1
#define ADC_EXTERNALTRIGINJECCONV_T19_CC2      ADC_EXTERNALTRIGINJEC_T19_CC2
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15     ADC_EXTERNALTRIGINJEC_EXT_IT15
#define ADC_INJECTED_SOFTWARE_START            ADC_JSWSTART

#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)   || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T19_CC1)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T19_CC2)  || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                      ((INJTRIG) == ADC_INJECTED_SOFTWARE_START)          )
/**
  * @}
  */


/** @defgroup ADCEx_Internal_HAL_driver_Ext_trig_src_Injected ADC Extended External Trigger Source of Injected Group (Internal)
  * @{
  */

/* List of external triggers of injected group for ADC1:                      */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC_EXTERNALTRIGINJEC_T19_CC1      ((uint32_t) 0x00000000)
#define ADC_EXTERNALTRIGINJEC_T19_CC2      ((uint32_t) ADC_CR2_JEXTSEL_0)
#define ADC_EXTERNALTRIGINJEC_T2_TRGO      ((uint32_t) ADC_CR2_JEXTSEL_1)
#define ADC_EXTERNALTRIGINJEC_T2_CC1       ((uint32_t)(ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJEC_T3_CC4       ((uint32_t) ADC_CR2_JEXTSEL_2)
#define ADC_EXTERNALTRIGINJEC_T4_TRGO      ((uint32_t)(ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJEC_EXT_IT15     ((uint32_t)(ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1))
#define ADC_JSWSTART                       ((uint32_t)(ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))

/**
  * @}
  */


/** @defgroup ADCEx_analog_watchdog_mode ADC Extended analog watchdog mode
  * @{
  */
#define ADC_ANALOGWATCHDOG_NONE                 ((uint32_t)0x00000000)
#define ADC_ANALOGWATCHDOG_SINGLE_REG           ((uint32_t)(ADC_CR1_AWDSGL | ADC_CR1_AWDEN))
#define ADC_ANALOGWATCHDOG_SINGLE_INJEC         ((uint32_t)(ADC_CR1_AWDSGL | ADC_CR1_JAWDEN))
#define ADC_ANALOGWATCHDOG_SINGLE_REGINJEC      ((uint32_t)(ADC_CR1_AWDSGL | ADC_CR1_AWDEN | ADC_CR1_JAWDEN))
#define ADC_ANALOGWATCHDOG_ALL_REG              ((uint32_t) ADC_CR1_AWDEN)
#define ADC_ANALOGWATCHDOG_ALL_INJEC            ((uint32_t) ADC_CR1_JAWDEN)
#define ADC_ANALOGWATCHDOG_ALL_REGINJEC         ((uint32_t)(ADC_CR1_AWDEN | ADC_CR1_JAWDEN))

#define IS_ADC_ANALOG_WATCHDOG_MODE(WATCHDOG) (((WATCHDOG) == ADC_ANALOGWATCHDOG_NONE)             || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REG)       || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)     || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)  || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REG)          || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_INJEC)        || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REGINJEC)       )
/**
  * @}
  */

/** @defgroup ADC_conversion_group ADC Conversion Group
  * @{
  */
#define REGULAR_GROUP             ((uint32_t)(ADC_FLAG_EOC))
#define INJECTED_GROUP            ((uint32_t)(ADC_FLAG_JEOC))
#define REGULAR_INJECTED_GROUP    ((uint32_t)(ADC_FLAG_EOC | ADC_FLAG_JEOC))

#define IS_ADC_CONVERSION_GROUP(CONVERSION) (((CONVERSION) == REGULAR_GROUP)         || \
                                             ((CONVERSION) == INJECTED_GROUP)        || \
                                             ((CONVERSION) == REGULAR_INJECTED_GROUP)  )
/**
  * @}
  */

/** @defgroup ADCEx_Event_type ADC Extended Event Type
  * @{
  */
#define AWD_EVENT               ((uint32_t)ADC_FLAG_AWD)   /*!< ADC Analog watchdog event */

#define IS_ADC_EVENT_TYPE(EVENT) ((EVENT) == AWD_EVENT)
/**
  * @}
  */

/** @defgroup ADCEx_interrupts_definition ADC Extended Interrupts Definition
  * @{
  */
#define ADC_IT_EOC           ADC_CR1_EOCIE        /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_JEOC          ADC_CR1_JEOCIE       /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IT_AWD           ADC_CR1_AWDIE        /*!< ADC Analog watchdog interrupt source */

/* Check of single flag */
#define IS_ADC_IT(IT) (((IT) == ADC_IT_EOC ) || \
                       ((IT) == ADC_IT_JEOC) || \
                       ((IT) == ADC_IT_AWD )   )
/**
  * @}
  */

/** @defgroup ADCEx_flags_definition ADC Extended Flags Definition
  * @{
  */
#define ADC_FLAG_AWD           ADC_SR_AWD      /*!< ADC Analog watchdog flag */
#define ADC_FLAG_EOC           ADC_SR_EOC      /*!< ADC End of Regular conversion flag */
#define ADC_FLAG_JEOC          ADC_SR_JEOC     /*!< ADC End of Injected conversion flag */
#define ADC_FLAG_JSTRT         ADC_SR_JSTRT    /*!< ADC Injected group start flag */
#define ADC_FLAG_STRT          ADC_SR_STRT     /*!< ADC Regular group start flag */

/* Combination of all post-conversion flags bits: EOC/EOS, JEOC/JEOS, OVR, AWDx */
#define ADC_FLAG_POSTCONV_ALL   (ADC_FLAG_EOC | ADC_FLAG_JEOC | ADC_FLAG_AWD )

/* Check of single flag */
#define IS_ADC_FLAG(FLAG) (((FLAG) == ADC_FLAG_AWD)   || \
                           ((FLAG) == ADC_FLAG_EOC)   || \
                           ((FLAG) == ADC_FLAG_JEOC)  || \
                           ((FLAG) == ADC_FLAG_JSTRT) || \
                           ((FLAG) == ADC_FLAG_STRT)    )
/**
  * @}
  */

/** @defgroup ADCEx_range_verification ADC Extended Range Verification
  * For a unique ADC resolution: 12 bits
  * @{
  */
#define IS_ADC_RANGE(ADC_VALUE) ((ADC_VALUE) <= ((uint32_t)0x0FFF))
/**
  * @}
  */

/** @defgroup ADC_injected_nb_conv_verification ADC Injected Conversion Number Verification
  * @{
  */
#define IS_ADC_INJECTED_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)4)))
/**
  * @}
  */

/** @defgroup ADC_regular_nb_conv_verification ADC Regular Conversion Number Verification
  * @{
  */
#define IS_ADC_REGULAR_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)16)))
/**
  * @}
  */

/** @defgroup ADC_regular_discontinuous_mode_number_verification ADC Regular Discontinuous Mode NumberVerification
  * @{
  */
#define IS_ADC_REGULAR_DISCONT_NUMBER(NUMBER) (((NUMBER) >= ((uint32_t)1)) && ((NUMBER) <= ((uint32_t)8)))
/**
  * @}
  */
#endif /* STM32F373xC || STM32F378xx */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup ADC_Exported_Macro ADC Exported Macros
  * @{
  */
/* Macro for internal HAL driver usage, and possibly can be used into code of */
/* final user.                                                                */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief Verification of ADC state: enabled or disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
#define __HAL_ADC_IS_ENABLED(__HANDLE__)                                                    \
       (( ((((__HANDLE__)->Instance->CR) & (ADC_CR_ADEN | ADC_CR_ADDIS)) == ADC_CR_ADEN) && \
          ((((__HANDLE__)->Instance->ISR) & ADC_FLAG_RDY) == ADC_FLAG_RDY)                  \
        ) ? SET : RESET)

/**
  * @brief Test if conversion trigger of regular group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define __HAL_ADC_IS_SOFTWARE_START_REGULAR(__HANDLE__)                        \
       (((__HANDLE__)->Instance->CFGR & ADC_CFGR_EXTEN) == RESET)

/**
  * @brief Test if conversion trigger of injected group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define __HAL_ADC_IS_SOFTWARE_START_INJECTED(__HANDLE__)                       \
       (((__HANDLE__)->Instance->JSQR & ADC_JSQR_JEXTEN) == RESET)

/**
  * @brief Check if no conversion on going on regular and/or injected groups
  * @param __HANDLE__: ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define __HAL_ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(__HANDLE__)                    \
       (( (((__HANDLE__)->Instance->CR) & (ADC_CR_ADSTART | ADC_CR_JADSTART)) == RESET  \
        ) ? RESET : SET)

/**
  * @brief Check if no conversion on going on regular group
  * @param __HANDLE__: ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define __HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(__HANDLE__)                    \
       (( (((__HANDLE__)->Instance->CR) & ADC_CR_ADSTART) == RESET             \
        ) ? RESET : SET)

/**
  * @brief Check if no conversion on going on injected group
  * @param __HANDLE__: ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define __HAL_ADC_IS_CONVERSION_ONGOING_INJECTED(__HANDLE__)                   \
       (( (((__HANDLE__)->Instance->CR) & ADC_CR_JADSTART) == RESET            \
        ) ? RESET : SET)

/**
  * @brief Returns resolution bits in CFGR1 register: RES[1:0].
  *        Returned value is among parameters to @ref ADCEx_Resolution.
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_GET_RESOLUTION(__HANDLE__) (((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)

/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC interrupt source to check
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                     \
    (( ((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__)      \
     )? SET : RESET                                                            \
    )

/**
  * @brief Enable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->IER) |= (__INTERRUPT__))

/**
  * @brief Disable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->IER) &= ~(__INTERRUPT__))

/**
  * @brief Get the selected ADC's flag status.
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  * @retval None
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->ISR) & (__FLAG__)) == (__FLAG__))

/**
  * @brief Clear the ADC's pending flags
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  * @retval None
  */
/* Note: bit cleared bit by writing 1 (writing 0 has no effect on any bit of register ISR) */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR) = (__FLAG__))

/**
  * @brief Clear ADC error code (set it to error code: "no error")
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
      
#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief Verification of ADC state: enabled or disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
#define __HAL_ADC_IS_ENABLED(__HANDLE__)                                     \
       ((( ((__HANDLE__)->Instance->CR2 & ADC_CR2_ADON) == ADC_CR2_ADON )    \
        ) ? SET : RESET)

/**
  * @brief Test if conversion trigger of regular group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define __HAL_ADC_IS_SOFTWARE_START_REGULAR(__HANDLE__) \
       (((__HANDLE__)->Instance->CR2 & ADC_CR2_EXTSEL) == ADC_SOFTWARE_START)

/**
  * @brief Test if conversion trigger of injected group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define __HAL_ADC_IS_SOFTWARE_START_INJECTED(__HANDLE__) \
       (((__HANDLE__)->Instance->CR2 & ADC_CR2_JEXTSEL) == ADC_INJECTED_SOFTWARE_START)

/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC interrupt source to check
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                     \
    (( ((__HANDLE__)->Instance->CR1 & (__INTERRUPT__)) == (__INTERRUPT__)      \
     )? SET : RESET                                                            \
    )
         
         
/**
  * @brief Enable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CR1) |= (__INTERRUPT__))

/**
  * @brief Disable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CR1) &= ~(__INTERRUPT__))

/**
  * @brief Get the selected ADC's flag status.
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  * @retval None
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

/**
  * @brief Clear the ADC's pending flags
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  * @retval None
  */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR) = ~(__FLAG__))

/**
  * @brief Clear ADC error code (set it to error code: "no error")
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)
      
#endif /* STM32F373xC || STM32F378xx */
/**
  * @}
  */
      

/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/** @defgroup ADCEx_Exported_Macro_internal_HAL_driver ADC Extended Exported Macros (Internal)
  * @{
  */
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

/**
  * @brief Set the ADC's sample time for Channels numbers between 0 and 9.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.  
  * @retval None
  */
#define __HAL_ADC_SMPR1(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * (_CHANNELNB_)))
    
/**
  * @brief Set the ADC's sample time for Channels numbers between 10 and 18.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.  
  * @retval None
  */
#define __HAL_ADC_SMPR2(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * ((_CHANNELNB_) - 10)))

/**
  * @brief Set the selected regular Channel rank for rank between 1 and 4.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __HAL_ADC_SQR1_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (6 * (_RANKNB_)))

/**
  * @brief Set the selected regular Channel rank for rank between 5 and 9.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __HAL_ADC_SQR2_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (6 * ((_RANKNB_) - 5)))

/**
  * @brief Set the selected regular Channel rank for rank between 10 and 14.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __HAL_ADC_SQR3_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (6 * ((_RANKNB_) - 10)))

/**
  * @brief Set the selected regular Channel rank for rank between 15 and 16.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __HAL_ADC_SQR4_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (6 * ((_RANKNB_) - 15)))

/**
  * @brief Set the selected injected Channel rank.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.   
  * @retval None
  */
#define __HAL_ADC_JSQR_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (6 * (_RANKNB_) +2))


/**
  * @brief Set the Analog Watchdog 1 channel.
  * @param _CHANNEL_: channel to be monitored by Analog Watchdog 1.
  * @retval None
  */
#define __HAL_ADC_CFGR_AWD1CH(_CHANNEL_) ((_CHANNEL_) << 26)

/**
  * @brief Configure the channel number into Analog Watchdog 2 or 3.
  * @param _CHANNEL_: ADC Channel
  * @retval None
  */
#define __HAL_ADC_CFGR_AWD23CR(_CHANNEL_) (1U << (_CHANNEL_)) 

/**
  * @brief Enable automatic conversion of injected group
  * @param _INJECT_AUTO_CONVERSION_: Injected automatic conversion.
  * @retval None
  */
#define __HAL_ADC_CFGR_INJECT_AUTO_CONVERSION(_INJECT_AUTO_CONVERSION_) ((_INJECT_AUTO_CONVERSION_) << 25)

/**
  * @brief Enable ADC injected context queue
  * @param _INJECT_CONTEXT_QUEUE_MODE_: Injected context queue mode.
  * @retval None
  */
#define __HAL_ADC_CFGR_INJECT_CONTEXT_QUEUE(_INJECT_CONTEXT_QUEUE_MODE_) ((_INJECT_CONTEXT_QUEUE_MODE_) << 21)

/**
  * @brief Enable ADC discontinuous conversion mode for injected group
  * @param _INJECT_DISCONTINUOUS_MODE_: Injected discontinuous mode.
  * @retval None
  */
#define __HAL_ADC_CFGR_INJECT_DISCCONTINUOUS(_INJECT_DISCONTINUOUS_MODE_) ((_INJECT_DISCONTINUOUS_MODE_) << 20)

/**
  * @brief Enable ADC discontinuous conversion mode for regular group
  * @param _REG_DISCONTINUOUS_MODE_: Regular discontinuous mode.
  * @retval None
  */
#define __HAL_ADC_CFGR_REG_DISCCONTINUOUS(_REG_DISCONTINUOUS_MODE_) ((_REG_DISCONTINUOUS_MODE_) << 16)

/**
  * @brief Configures the number of discontinuous conversions for regular group.
  * @param _NBR_DISCONTINUOUS_CONV_: Number of discontinuous conversions.
  * @retval None
  */
#define __HAL_ADC_CFGR_DISCONTINUOUS_NUM(_NBR_DISCONTINUOUS_CONV_) (((_NBR_DISCONTINUOUS_CONV_) - 1) << 17)

/**
  * @brief Enable the ADC auto delay mode.
  * @param _AUTOWAIT_: Auto delay bit enable or disable.
  * @retval None
  */
#define __HAL_ADC_CFGR_AUTOWAIT(_AUTOWAIT_) ((_AUTOWAIT_) << 14)

/**
  * @brief Enable ADC continuous conversion mode.
  * @param _CONTINUOUS_MODE_: Continuous mode.
  * @retval None
  */
#define __HAL_ADC_CFGR_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << 13)
    
/**
  * @brief Enable ADC overrun mode.
  * @param _OVERRUN_MODE_: Overrun mode.
  * @retval Overrun bit setting to be programmed into CFGR register
  */
/* Note: Bit ADC_CFGR_OVRMOD not used directly in constant                    */
/* "OVR_DATA_OVERWRITTEN" to have this case defined to 0x00, to set it as the */
/* default case to be compliant with other STM32 devices.                     */
#define __HAL_ADC_CFGR_OVERRUN(_OVERRUN_MODE_)                                 \
  ( ( (_OVERRUN_MODE_) != (OVR_DATA_PRESERVED)                                 \
    )? (ADC_CFGR_OVRMOD) : (0x00000000)                                        \
  )

/**
  * @brief Enable the ADC DMA continuous request.
  * @param _DMACONTREQ_MODE_: DMA continuous request mode.
  * @retval None
  */
#define __HAL_ADC_CFGR_DMACONTREQ(_DMACONTREQ_MODE_) ((_DMACONTREQ_MODE_) << 1)

/**
  * @brief For devices with 3 ADCs or more: Defines the external trigger source 
  *        for regular group according to ADC into common group ADC1&ADC2 or 
  *        ADC3&ADC4 (some triggers with same source have different value to
  *        be programmed into ADC EXTSEL bits of CFGR register).
  *        Note: No risk of trigger bits value of common group ADC1&ADC2 
  *        misleading to another trigger at same bits value, because the 3
  *        exceptions below are circular and do not point to any other trigger
  *        with direct treatment.
  *        For devices with 2 ADCs or less: this macro makes no change.
  * @param __HANDLE__: ADC handle
  * @param __EXT_TRIG_CONV__: External trigger selected for regular group.
  * @retval External trigger to be programmed into EXTSEL bits of CFGR register
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)

#if defined(STM32F303xC) || defined(STM32F358xx)
#define __HAL_ADC_CFGR_EXTSEL(__HANDLE__, __EXT_TRIG_CONV__)                   \
 (( ((((__HANDLE__)->Instance) == ADC3) || (((__HANDLE__)->Instance) == ADC4)) \
  )?                                                                           \
   ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T2_TRGO                     \
     )?                                                                        \
      (ADC3_4_EXTERNALTRIG_T2_TRGO)                                            \
      :                                                                        \
      ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T3_TRGO                  \
        )?                                                                     \
         (ADC3_4_EXTERNALTRIG_T3_TRGO)                                         \
         :                                                                     \
         ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T8_TRGO               \
           )?                                                                  \
            (ADC3_4_EXTERNALTRIG_T8_TRGO)                                      \
            :                                                                  \
            (__EXT_TRIG_CONV__)                                                \
         )                                                                     \
      )                                                                        \
   )                                                                           \
   :                                                                           \
   (__EXT_TRIG_CONV__)                                                         \
 )
#endif /* STM32F303xC || STM32F358xx */
   
#if defined(STM32F303xE) || defined(STM32F398xx)
/* Note: Macro including external triggers specific to device STM303xE: using */
/*       Timer20 with ADC trigger input remap.                                */
#define __HAL_ADC_CFGR_EXTSEL(__HANDLE__, __EXT_TRIG_CONV__)                   \
 (( ((((__HANDLE__)->Instance) == ADC3) || (((__HANDLE__)->Instance) == ADC4)) \
  )?                                                                           \
   ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T2_TRGO                     \
     )?                                                                        \
      (ADC3_4_EXTERNALTRIG_T2_TRGO)                                            \
      :                                                                        \
      ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T3_TRGO                  \
        )?                                                                     \
         (ADC3_4_EXTERNALTRIG_T3_TRGO)                                         \
         :                                                                     \
         ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T8_TRGO               \
           )?                                                                  \
            (ADC3_4_EXTERNALTRIG_T8_TRGO)                                      \
            :                                                                  \
            ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T20_CC1            \
              )?                                                               \
               (ADC3_4_EXTERNALTRIG_T2_CC1)                                    \
               :                                                               \
                ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T20_TRGO       \
                  )?                                                           \
                   (ADC3_4_EXTERNALTRIG_EXT_IT2)                               \
                   :                                                           \
                    ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T20_TRGO2  \
                      )?                                                       \
                       (ADC3_4_EXTERNALTRIG_T4_CC1)                            \
                       :                                                       \
                       (__EXT_TRIG_CONV__)                                     \
                  )                                                            \
               )                                                               \
            )                                                                  \
         )                                                                     \
      )                                                                        \
   )                                                                           \
   :                                                                           \
   (__EXT_TRIG_CONV__ & (~ADC_EXTERNALTRIGCONV_T20_MASK))                      \
 )
#endif /* STM32F303xE || STM32F398xx */
#else
#define __HAL_ADC_CFGR_EXTSEL(__HANDLE__, __EXT_TRIG_CONV__)                   \
   (__EXT_TRIG_CONV__)
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

/**
  * @brief For devices with 3 ADCs or more: Defines the external trigger source 
  *        for injected group according to ADC into common group ADC1&ADC2 or 
  *        ADC3&ADC4 (some triggers with same source have different value to
  *        be programmed into ADC JEXTSEL bits of JSQR register).
  *        Note: No risk of trigger bits value of common group ADC1&ADC2 
  *        misleading to another trigger at same bits value, because the 3
  *        exceptions below are circular and do not point to any other trigger
  *        with direct treatment, except trigger
  *        ADC_EXTERNALTRIGINJECCONV_T4_CC3 differentiated with SW offset.
  *        For devices with 2 ADCs or less: this macro makes no change.
  * @param __HANDLE__: ADC handle
  * @param __EXT_TRIG_INJECTCONV__: External trigger selected for injected group
  * @retval External trigger to be programmed into JEXTSEL bits of JSQR register
  */
#if defined(STM32F303xC) || defined(STM32F303xE) || defined(STM32F398xx) || defined(STM32F358xx)
#if defined(STM32F303xC) || defined(STM32F358xx)
#define __HAL_ADC_JSQR_JEXTSEL(__HANDLE__, __EXT_TRIG_INJECTCONV__)            \
 (( ((((__HANDLE__)->Instance) == ADC3) || (((__HANDLE__)->Instance) == ADC4)) \
  )?                                                                           \
   ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO          \
     )?                                                                        \
      (ADC3_4_EXTERNALTRIGINJEC_T2_TRGO)                                       \
      :                                                                        \
      ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO       \
        )?                                                                     \
         (ADC3_4_EXTERNALTRIGINJEC_T4_TRGO)                                    \
         :                                                                     \
         ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T8_CC4     \
           )?                                                                  \
            (ADC3_4_EXTERNALTRIGINJEC_T8_CC4)                                  \
            :                                                                  \
            ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T4_CC3  \
              )?                                                               \
               (ADC3_4_EXTERNALTRIGINJEC_T4_CC3)                               \
               :                                                               \
               (__EXT_TRIG_INJECTCONV__)                                       \
            )                                                                  \
         )                                                                     \
      )                                                                        \
   )                                                                           \
   :                                                                           \
   (__EXT_TRIG_INJECTCONV__)                                                   \
 )
#endif /* STM32F303xC || STM32F358xx */
   
#if defined(STM32F303xE) || defined(STM32F398xx)
/* Note: Macro including external triggers specific to device STM303xE: using */
/*       Timer20 with ADC trigger input remap.                                */
#define __HAL_ADC_JSQR_JEXTSEL(__HANDLE__, __EXT_TRIG_INJECTCONV__)            \
 (( ((((__HANDLE__)->Instance) == ADC3) || (((__HANDLE__)->Instance) == ADC4)) \
  )?                                                                           \
   ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO          \
     )?                                                                        \
      (ADC3_4_EXTERNALTRIGINJEC_T2_TRGO)                                       \
      :                                                                        \
      ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO       \
        )?                                                                     \
         (ADC3_4_EXTERNALTRIGINJEC_T4_TRGO)                                    \
         :                                                                     \
         ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T8_CC4     \
           )?                                                                  \
            (ADC3_4_EXTERNALTRIGINJEC_T8_CC4)                                  \
            :                                                                  \
            ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T4_CC3  \
              )?                                                               \
               (ADC3_4_EXTERNALTRIGINJEC_T4_CC3)                               \
               :                                                               \
                ( ( (__EXT_TRIG_INJECTCONV__)                                  \
                                         == ADC_EXTERNALTRIGINJECCONV_T20_TRGO \
                  )?                                                           \
                   (ADC3_4_EXTERNALTRIGINJEC_T20_TRGO)                         \
                   :                                                           \
                    ( ( (__EXT_TRIG_INJECTCONV__)                              \
                                       == ADC_EXTERNALTRIGINJECCONV_T20_TRGO2  \
                      )?                                                       \
                       (ADC3_4_EXTERNALTRIGINJEC_T1_CC3)                       \
                       :                                                       \
                       (__EXT_TRIG_INJECTCONV__)                               \
                  )                                                            \
               )                                                               \
            )                                                                  \
         )                                                                     \
      )                                                                        \
   )                                                                           \
   :                                                                           \
   (__EXT_TRIG_INJECTCONV__ & (~ADC_EXTERNALTRIGCONV_T20_MASK))                \
 )
#endif /* STM32F303xE || STM32F398xx */
#else
#define __HAL_ADC_JSQR_JEXTSEL(__HANDLE__, __EXT_TRIG_INJECTCONV__)            \
   (__EXT_TRIG_INJECTCONV__)
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

/**
  * @brief Configure the channel number into offset OFRx register
  * @param _CHANNEL_: ADC Channel
  * @retval None
  */
#define __HAL_ADC_OFR_CHANNEL(_CHANNEL_) ((_CHANNEL_) << 26)

/**
  * @brief Configure the channel number into differential mode selection register
  * @param _CHANNEL_: ADC Channel
  * @retval None
  */
#define __HAL_ADC_DIFSEL_CHANNEL(_CHANNEL_) (1U << (_CHANNEL_)) 

/**
  * @brief Calibration factor in differential mode to be set into calibration register
  * @param _Calibration_Factor_: Calibration factor value
  * @retval None
  */
#define __HAL_ADC_CALFACT_DIFF_SET(_Calibration_Factor_) ((_Calibration_Factor_) << 16)

/**
  * @brief Calibration factor in differential mode to be retrieved from calibration register
  * @param _Calibration_Factor_: Calibration factor value
  * @retval None
  */
#define __HAL_ADC_CALFACT_DIFF_GET(_Calibration_Factor_) ((_Calibration_Factor_) >> 16)
     
/**
  * @brief Configure the analog watchdog high threshold into registers TR1, TR2 or TR3.
  * @param _Threshold_: Threshold value
  * @retval None
  */
#define __HAL_ADC_TRX_HIGHTHRESHOLD(_Threshold_) ((_Threshold_) << 16)

/**
  * @brief Enable the ADC DMA continuous request for ADC multimode.
  * @param _DMAContReq_MODE_: DMA continuous request mode.
  * @retval None
  */
#define __HAL_ADC_CCR_MULTI_DMACONTREQ(_DMAContReq_MODE_) ((_DMAContReq_MODE_) << 13)
    

/**
  * @brief Enable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR |= ADC_CR_ADEN)

/**
  * @brief Verification of hardware constraints before ADC can be enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC can be enabled) or RESET (ADC cannot be enabled)
  */
#define __HAL_ADC_ENABLING_CONDITIONS(__HANDLE__)                             \
       (( ( ((__HANDLE__)->Instance->CR) &                                    \
            (ADC_CR_ADCAL | ADC_CR_JADSTP | ADC_CR_ADSTP | ADC_CR_JADSTART |  \
             ADC_CR_ADSTART | ADC_CR_ADDIS | ADC_CR_ADEN                    ) \
           ) == RESET                                                         \
        ) ? SET : RESET)
         
/**
  * @brief Disable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_DISABLE(__HANDLE__)                                          \
  do{                                                                          \
         (__HANDLE__)->Instance->CR |= ADC_CR_ADDIS;                           \
          __HAL_ADC_CLEAR_FLAG((__HANDLE__), (ADC_FLAG_EOSMP | ADC_FLAG_RDY)); \
  } while(0)
    
/**
  * @brief Verification of hardware constraints before ADC can be disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC can be disabled) or RESET (ADC cannot be disabled)
  */
#define __HAL_ADC_DISABLING_CONDITIONS(__HANDLE__)                             \
       (( ( ((__HANDLE__)->Instance->CR) &                                     \
            (ADC_CR_JADSTART | ADC_CR_ADSTART | ADC_CR_ADEN)) == ADC_CR_ADEN   \
        ) ? SET : RESET)
         

/**
  * @brief Shift the offset in function of the selected ADC resolution. 
  *        Offset has to be left-aligned on bit 11, the LSB (right bits) are set to 0
  *        If resolution 12 bits, no shift.
  *        If resolution 10 bits, shift of 2 ranks on the left.
  *        If resolution 8 bits, shift of 4 ranks on the left.
  *        If resolution 6 bits, shift of 6 ranks on the left.
  *        therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2))
  * @param __HANDLE__: ADC handle
  * @param _Offset_: Value to be shifted
  * @retval None
  */
#define __HAL_ADC_OFFSET_SHIFT_RESOLUTION(__HANDLE__, _Offset_) \
        ((_Offset_) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 3)*2))

/**
  * @brief Shift the AWD1 threshold in function of the selected ADC resolution.
  *        Thresholds have to be left-aligned on bit 11, the LSB (right bits) are set to 0.
  *        If resolution 12 bits, no shift.
  *        If resolution 10 bits, shift of 2 ranks on the left.
  *        If resolution 8 bits, shift of 4 ranks on the left.
  *        If resolution 6 bits, shift of 6 ranks on the left.
  *        therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2))
  * @param __HANDLE__: ADC handle
  * @param _Threshold_: Value to be shifted
  * @retval None
  */
#define __HAL_ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, _Threshold_) \
        ((_Threshold_) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 3)*2))

/**
  * @brief Shift the AWD2 and AWD3 threshold in function of the selected ADC resolution.
  *        Thresholds have to be left-aligned on bit 7.
  *        If resolution 12 bits, shift of 4 ranks on the right (the 4 LSB are discarded)
  *        If resolution 10 bits, shift of 2 ranks on the right (the 2 LSB are discarded)
  *        If resolution 8 bits, no shift.
  *        If resolution 6 bits, shift of 2 ranks on the left (the 2 LSB are set to 0)
  * @param __HANDLE__: ADC handle
  * @param _Threshold_: Value to be shifted
  * @retval None
  */
#define __HAL_ADC_AWD23THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, _Threshold_) \
         ( ((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) != (ADC_CFGR_RES_1 | ADC_CFGR_RES_0) ? \
            ((_Threshold_) >> (4- ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 3)*2))) : \
            (_Threshold_) << 2 )
          
/**
  * @brief Defines if the selected ADC is within ADC common register ADC1_2 or ADC3_4
  * if available (ADC2, ADC3, ADC4 availability depends on STM32 product)
  * @param __HANDLE__: ADC handle
  * @retval Common control register ADC1_2 or ADC3_4
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
#define __HAL_ADC_COMMON_REGISTER(__HANDLE__)                                       \
     ( ( ((((__HANDLE__)->Instance) == ADC1) || (((__HANDLE__)->Instance) == ADC2)) \
       )? (ADC1_2_COMMON) : (ADC3_4_COMMON)                                                           \
     )
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F302xE)                                                || \
    defined(STM32F302xC)                                                || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __HAL_ADC_COMMON_REGISTER(__HANDLE__)                                       \
     (ADC1_2_COMMON)
#endif /* STM32F302xE                               || */
       /* STM32F302xC                               || */
       /* STM32F303x8 || STM32F328xx || STM32F334x8    */
       
#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __HAL_ADC_COMMON_REGISTER(__HANDLE__)                                       \
     (ADC1_COMMON)
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */
       
/**
  * @brief Selection of ADC common register CCR bits MULTI[4:0]corresponding to the selected ADC (applicable for devices with several ADCs)
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
#define __HAL_ADC_COMMON_CCR_MULTI(__HANDLE__)                                   \
  ( ( ((((__HANDLE__)->Instance) == ADC1) || (((__HANDLE__)->Instance) == ADC2)) \
    )?                                                                           \
     (ADC1_2_COMMON->CCR & ADC12_CCR_MULTI)                                      \
     :                                                                           \
     (ADC3_4_COMMON->CCR & ADC34_CCR_MULTI)                                      \
  )
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */
    
#if defined(STM32F302xE)                                                || \
    defined(STM32F302xC)                                                || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __HAL_ADC_COMMON_CCR_MULTI(__HANDLE__)                                   \
  (ADC1_2_COMMON->CCR & ADC12_CCR_MULTI)
#endif /* STM32F302xE                               || */
       /* STM32F302xC                               || */
       /* STM32F303x8 || STM32F328xx || STM32F334x8    */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __HAL_ADC_COMMON_CCR_MULTI(__HANDLE__)                                   \
  (RESET)
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

/**
  * @brief Verification of condition for ADC start conversion: ADC must be in non-multimode, or multimode with handle of ADC master (applicable for devices with several ADCs)
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __HAL_ADC_NONMULTIMODE_OR_MULTIMODEMASTER(__HANDLE__)                                   \
  ((__HAL_ADC_COMMON_CCR_MULTI(__HANDLE__) == RESET) || (IS_ADC_MULTIMODE_MASTER_INSTANCE((__HANDLE__)->Instance)))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx    */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __HAL_ADC_NONMULTIMODE_OR_MULTIMODEMASTER(__HANDLE__)                                   \
  (!RESET)
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

/**
  * @brief Set handle of the other ADC sharing the same common register ADC1_2 or ADC3_4
  * if available (ADC2, ADC3, ADC4 availability depends on STM32 product)
  * @param __HANDLE__: ADC handle
  * @param __HANDLE_OTHER_ADC__: other ADC handle
  * @retval None
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
#define __HAL_ADC_COMMON_ADC_OTHER(__HANDLE__, __HANDLE_OTHER_ADC__)           \
  ( ( ((__HANDLE__)->Instance == ADC1)                                         \
    )?                                                                         \
     ((__HANDLE_OTHER_ADC__)->Instance = ADC2)                                 \
     :                                                                         \
     ( ( ((__HANDLE__)->Instance == ADC2)                                      \
       )?                                                                      \
        ((__HANDLE_OTHER_ADC__)->Instance = ADC1)                              \
        :                                                                      \
        ( ( ((__HANDLE__)->Instance == ADC3)                                   \
          )?                                                                   \
           ((__HANDLE_OTHER_ADC__)->Instance = ADC4)                           \
           :                                                                   \
           ( ( ((__HANDLE__)->Instance == ADC4)                                \
             )?                                                                \
              ((__HANDLE_OTHER_ADC__)->Instance = ADC3)                        \
              :                                                                \
              ((__HANDLE_OTHER_ADC__)->Instance = HAL_NULL)                        \
           )                                                                   \
         )                                                                     \
     )                                                                         \
  )
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */
    
#if defined(STM32F302xE)                                                || \
    defined(STM32F302xC)                                                || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __HAL_ADC_COMMON_ADC_OTHER(__HANDLE__, __HANDLE_OTHER_ADC__)           \
  ( ( ((__HANDLE__)->Instance == ADC1)                                         \
    )?                                                                         \
     ((__HANDLE_OTHER_ADC__)->Instance = ADC2)                                 \
     :                                                                         \
     ((__HANDLE_OTHER_ADC__)->Instance = ADC1)                                 \
  )
#endif /* STM32F302xE                               || */
       /* STM32F302xC                               || */
       /* STM32F303x8 || STM32F328xx || STM32F334x8    */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
#define __HAL_ADC_COMMON_ADC_OTHER(__HANDLE__, __HANDLE_OTHER_ADC__)           \
  ((__HANDLE_OTHER_ADC__)->Instance = HAL_NULL)
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

/**
  * @brief Set handle of the ADC slave associated to the ADC master
  * if available (ADC2, ADC3, ADC4 availability depends on STM32 product)
  * @param __HANDLE_MASTER__: ADC master handle
  * @param __HANDLE_SLAVE__: ADC slave handle
  * @retval None
  */
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
#define __HAL_ADC_MULTI_SLAVE(__HANDLE_MASTER__, __HANDLE_SLAVE__)             \
  ( ( ((__HANDLE_MASTER__)->Instance == ADC1)                                  \
    )?                                                                         \
     ((__HANDLE_SLAVE__)->Instance = ADC2)                                     \
     :                                                                         \
     ( ( ((__HANDLE_MASTER__)->Instance == ADC3)                               \
       )?                                                                      \
        ((__HANDLE_SLAVE__)->Instance = ADC4)                                  \
        :                                                                      \
        ((__HANDLE_SLAVE__)->Instance = HAL_NULL)                                  \
     )                                                                         \
  )
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */
    
#if defined(STM32F302xE)                                                || \
    defined(STM32F302xC)                                                || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define __HAL_ADC_MULTI_SLAVE(__HANDLE_MASTER__, __HANDLE_SLAVE__)             \
  ( ( ((__HANDLE_MASTER__)->Instance == ADC1)                                  \
    )?                                                                         \
     ((__HANDLE_SLAVE__)->Instance = ADC2)                                     \
     :                                                                         \
     ( HAL_NULL )                                                                  \
  )
#endif /* STM32F302xE                               || */
       /* STM32F302xC                               || */
       /* STM32F303x8 || STM32F328xx || STM32F334x8    */

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx */


#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief Set ADC number of conversions into regular channel sequence length.
  * @param _NbrOfConversion_: Regular channel sequence length 
  * @retval None
  */
#define __HAL_ADC_SQR1_L(_NbrOfConversion_) (((_NbrOfConversion_) - (uint8_t)1) << 20)

/**
  * @brief Set the ADC's sample time for channel numbers between 10 and 18.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.  
  * @retval None
  */
#define __HAL_ADC_SMPR1(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * ((_CHANNELNB_) - 10)))

/**
  * @brief Set the ADC's sample time for channel numbers between 0 and 9.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.  
  * @retval None
  */
#define __HAL_ADC_SMPR2(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * (_CHANNELNB_)))

/**
  * @brief Set the selected regular channel rank for rank between 1 and 6.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __HAL_ADC_SQR3_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (5 * ((_RANKNB_) - 1)))

/**
  * @brief Set the selected regular channel rank for rank between 7 and 12.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __HAL_ADC_SQR2_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (5 * ((_RANKNB_) - 7)))

/**
  * @brief Set the selected regular channel rank for rank between 13 and 16.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __HAL_ADC_SQR1_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (5 * ((_RANKNB_) - 13)))

/**
  * @brief Set the injected sequence length.
  * @param _JSQR_JL_: Sequence length.
  * @retval None
  */
#define __HAL_ADC_JSQR_JL(_JSQR_JL_)   (((_JSQR_JL_) -1) << 20)

/**
  * @brief Set the selected injected Channel rank (channels sequence starting from 4-JL)
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.
  * @param _JSQR_JL_: Sequence length.
  * @retval None
  */
#define __HAL_ADC_JSQR_RK(_CHANNELNB_, _RANKNB_, _JSQR_JL_)         \
    ((_CHANNELNB_) << (5 * ((4 - ((_JSQR_JL_) - (_RANKNB_))) - 1)))

/**
  * @brief Enable ADC continuous conversion mode.
  * @param _CONTINUOUS_MODE_: Continuous mode.
  * @retval None
  */
#define __HAL_ADC_CR2_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << 1)

/**
  * @brief Configures the number of discontinuous conversions for the regular group channels.
  * @param _NBR_DISCONTINUOUS_CONV_: Number of discontinuous conversions.
  * @retval None
  */
#define __HAL_ADC_CR1_DISCONTINUOUS_NUM(_NBR_DISCONTINUOUS_CONV_) (((_NBR_DISCONTINUOUS_CONV_) - 1) << 13)
   
/**
  * @brief Enable ADC scan mode to convert multiple ranks with sequencer.
  * @param _SCAN_MODE_: Scan conversion mode.
  * @retval None
  */
#define __HAL_ADC_CR1_SCAN(_SCAN_MODE_)                                        \
  ( ( (_SCAN_MODE_) == (ADC_SCAN_ENABLE)                                       \
    )? (ADC_CR1_SCAN) : (0x00000000)                                           \
  )
    
/**
  * @brief Calibration factor in differential mode to be set into calibration register
  * @param _Calibration_Factor_: Calibration factor value
  * @retval None
  */
#define __HAL_ADC_CALFACT_DIFF_SET(_Calibration_Factor_) ((_Calibration_Factor_) << 16)

/**
  * @brief Calibration factor in differential mode to be retrieved from calibration register
  * @param _Calibration_Factor_: Calibration factor value
  * @retval None
  */
#define __HAL_ADC_CALFACT_DIFF_GET(_Calibration_Factor_) ((_Calibration_Factor_) >> 16)
      
      
/**
  * @brief Get the maximum ADC conversion cycles on all channels.
  * Returns the selected sampling time + conversion time (12.5 ADC clock cycles)
  * Approximation of sampling time within 4 ranges, returns the higher value:
  *   below 7.5 cycles {1.5 cycle; 7.5 cycles},
  *   between 13.5 cycles and 28.5 cycles {13.5 cycles; 28.5 cycles}
  *   between 41.5 cycles and 71.5 cycles {41.5 cycles; 55.5 cycles; 71.5cycles}
  *   equal to 239.5 cycles
  * Unit: ADC clock cycles
  * @param __HANDLE__: ADC handle
  * @retval ADC conversion cycles on all channels
  */   
#define __HAL_ADC_CONVCYCLES_MAX_RANGE(__HANDLE__)                                                               \
    (( (((__HANDLE__)->Instance->SMPR2 & ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2) == RESET)  &&                     \
       (((__HANDLE__)->Instance->SMPR1 & ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2) == RESET) ) ?                     \
                                                                                                                 \
          (( (((__HANDLE__)->Instance->SMPR2 & ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT1) == RESET)  &&               \
             (((__HANDLE__)->Instance->SMPR1 & ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1) == RESET) ) ?               \
               ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_7CYCLES5 : ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_28CYCLES5)   \
          :                                                                                                      \
          ((((((__HANDLE__)->Instance->SMPR2 & ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT1) == RESET)  &&               \
             (((__HANDLE__)->Instance->SMPR1 & ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1) == RESET)) ||               \
            ((((__HANDLE__)->Instance->SMPR2 & ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0) == RESET)  &&               \
             (((__HANDLE__)->Instance->SMPR1 & ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0) == RESET))) ?               \
               ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_71CYCLES5 : ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_239CYCLES5) \
     )

/**
  * @brief Get the total ADC clock prescaler (APB2 prescaler x ADC prescaler)
  * from system clock configuration register.
  * Approximation within 3 ranges, returns the higher value:
  *   total prescaler minimum: 2 (ADC presc 2, APB2 presc 0)
  *   total prescaler 32 (ADC presc 0 and APB2 presc all, or
  *                       ADC presc {4, 6, 8} and APB2 presc {0, 2, 4})
  *   total prescaler maximum: 128 (ADC presc {4, 6, 8} and APB2 presc {8, 16})
  * Unit: none (prescaler factor)
  * @param __HANDLE__: ADC handle
  * @retval ADC and APB2 prescaler factor
  */
#define __HAL_ADC_CLOCK_PRECSALER_RANGE(__HANDLE__)                       \
    (( (RCC->CFGR & (RCC_CFGR_ADCPRE_1 | RCC_CFGR_ADCPRE_0)) == RESET) ?  \
        (( (RCC->CFGR & RCC_CFGR_PPRE2_2) == RESET) ? 2 : 32 )            \
        :                                                                 \
        (( (RCC->CFGR & RCC_CFGR_PPRE2_1) == RESET) ? 32 : 128 )          \
      )

/**
  * @brief Get the ADC clock prescaler from system clock configuration register. 
  * @retval None
  */
#define __HAL_ADC_GET_CLOCK_PRESCALER() (((RCC->CFGR & RCC_CFGR_ADCPRE) >> 14) +1)

/**
  * @brief Enable the ADC peripheral (if not already enable to not trig a conversion)
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_ENABLE(__HANDLE__)                                         \
            (__HANDLE__)->Instance->CR2 |= ADC_CR2_ADON
  
/**
  * @brief Disable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_DISABLE(__HANDLE__)                                        \
            (__HANDLE__)->Instance->CR2 &= ~ADC_CR2_ADON
      
#endif /* STM32F373xC || STM32F378xx */
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/  
/** @addtogroup ADCEx_Exported_Functions ADC Extended Exported Functions
  * @{
  */ 
          
/* Initialization/de-initialization functions *********************************/

/** @addtogroup ADCEx_Exported_Functions_Group2 Extended Input and Output operation functions
  * @brief    Extended IO operation functions
  * @{
  */ 
/* I/O operation functions ****************************************************/

/* ADC calibration */
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(struct __ADC_HandleTypeDef* hadc, uint32_t SingleDiff);
uint32_t        HAL_ADCEx_Calibration_GetValue(struct __ADC_HandleTypeDef *hadc, uint32_t SingleDiff);
HAL_StatusTypeDef       HAL_ADCEx_Calibration_SetValue(struct __ADC_HandleTypeDef *hadc, uint32_t SingleDiff, uint32_t CalibrationFactor);
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(struct __ADC_HandleTypeDef* hadc);
#endif /* STM32F373xC || STM32F378xx */

/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(struct __ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(struct __ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(struct __ADC_HandleTypeDef* hadc, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(struct __ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(struct __ADC_HandleTypeDef* hadc);
     
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) 
/* ADC multimode */
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStart_DMA(struct __ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStop_DMA(struct __ADC_HandleTypeDef *hadc); 
uint32_t                HAL_ADCEx_MultiModeGetValue(struct __ADC_HandleTypeDef *hadc);
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADCEx_InjectedGetValue(struct __ADC_HandleTypeDef* hadc, uint32_t InjectedRank);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption) */
void                    HAL_ADCEx_InjectedConvCpltCallback(struct __ADC_HandleTypeDef* hadc);

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
void                    HAL_ADCEx_InjectedQueueOverflowCallback(struct __ADC_HandleTypeDef* hadc);
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
/**
  * @}
  */
     
/** @addtogroup ADCEx_Exported_Functions_Group3 Extended Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  * @{
  */ 
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef       HAL_ADCEx_InjectedConfigChannel(struct __ADC_HandleTypeDef* hadc,ADC_InjectionConfTypeDef* sConfigInjected);

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
HAL_StatusTypeDef       HAL_ADCEx_MultiModeConfigChannel(struct __ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode);
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */ 

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F3xx_ADC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
