/**
  ******************************************************************************
  * @file    stm32l1xx_hal_adc.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
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
#ifndef __STM32L1xx_HAL_ADC_H
#define __STM32L1xx_HAL_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"  
/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup ADC_Exported_Types ADC Exported Types
  * @{
  */

/** 
  * @brief  Structure definition of ADC and regular group initialization 
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope entire ADC (affects regular and injected groups): ClockPrescaler, Resolution, ScanConvMode, DataAlign, ScanConvMode, EOCSelection, LowPowerAutoWait, LowPowerAutoPowerOff, ChannelsBank.
  *          - Scope regular group: ContinuousConvMode, NbrOfConversion, DiscontinuousConvMode, NbrOfDiscConversion, ExternalTrigConvEdge, ExternalTrigConv.
  * @note   The setting of these parameters with function HAL_ADC_Init() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled
  *          - For all parameters except 'Resolution', 'ScanConvMode', 'LowPowerAutoWait', 'LowPowerAutoPowerOff', 'DiscontinuousConvMode', 'NbrOfDiscConversion' : ADC enabled without conversion on going on regular group.
  *          - For parameters 'ExternalTrigConv' and 'ExternalTrigConvEdge': ADC enabled, even with conversion on going.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting without error reporting (as it can be the expected behaviour in case of intended action to update another parameter (which fullfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t ClockPrescaler;        /*!< Select ADC clock source (asynchronous clock derived from HSI RC oscillator) and clock prescaler.
                                       This parameter can be a value of @ref ADC_ClockPrescaler
                                       Note: In case of usage of channels on injected group, ADC frequency should be low than AHB clock frequency /4 for resolution 12 or 10 bits, 
                                             AHB clock frequency /3 for resolution 8 bits, AHB clock frequency /2 for resolution 6 bits.
                                       Note: HSI RC oscillator must be preliminarily enabled at RCC top level. */
  uint32_t Resolution;            /*!< Configures the ADC resolution. 
                                       This parameter can be a value of @ref ADC_Resolution */
  uint32_t DataAlign;             /*!< Specifies ADC data alignment to right (MSB on register bit 11 and LSB on register bit 0) (default setting)
                                       or to left (if regular group: MSB on register bit 15 and LSB on register bit 4, if injected group (MSB kept as signed value due to potential negative value after offset application): MSB on register bit 14 and LSB on register bit 3).
                                       This parameter can be a value of @ref ADC_Data_align */
  uint32_t ScanConvMode;          /*!< Configures the sequencer of regular and injected groups.
                                       This parameter can be associated to parameter 'DiscontinuousConvMode' to have main sequence subdivided in successive parts.
                                       If disabled: Conversion is performed in single mode (one channel converted, the one defined in rank 1).
                                                    Parameters 'NbrOfConversion' and 'InjectedNbrOfConversion' are discarded (equivalent to set to 1).
                                       If enabled:  Conversions are performed in sequence mode (multiple ranks defined by 'NbrOfConversion'/'InjectedNbrOfConversion' and each channel rank).
                                                    Scan direction is upward: from rank1 to rank 'n'.
                                       This parameter can be a value of @ref ADC_Scan_mode */
  uint32_t EOCSelection;          /*!< Specifies what EOC (End Of Conversion) flag is used for conversion by polling and interruption: end of conversion of each rank or complete sequence.
                                       This parameter can be a value of @ref ADC_EOCSelection.
                                       Note: For injected group, end of conversion (flag&IT) is raised only at the end of the sequence.
                                             Therefore, if end of conversion is set to end of each conversion, injected group should not be used with interruption (HAL_ADCEx_InjectedStart_IT)
                                             or polling (HAL_ADCEx_InjectedStart and HAL_ADCEx_InjectedPollForConversion). By the way, polling is still possible since driver will use an estimated timing for end of injected conversion.
                                       Note: If overrun feature is intending to be used in ADC mode 'interruption' (function HAL_ADC_Start_IT() ), parameter EOCSelection must be set to each conversion (this is not needed for ADC mode 'transfer by DMA', with function HAL_ADC_Start_DMA()) */
  uint32_t LowPowerAutoWait;      /*!< Selects the dynamic low power Auto Delay: new conversion start only when the previous
                                       conversion (for regular group) or previous sequence (for injected group) has been treated by user software.
                                       This feature automatically adapts the speed of ADC to the speed of the system that reads the data. Moreover, this avoids risk of overrun for low frequency applications. 
                                       This parameter can be a value of @ref ADC_LowPowerAutoWait.
                                       Note: Do not use with interruption or DMA (HAL_ADC_Start_IT(), HAL_ADC_Start_DMA()) since they have to clear immediately the EOC flag to free the IRQ vector sequencer.
                                             Do use with polling: 1. Start conversion with HAL_ADC_Start(), 2. Later on, when conversion data is needed: use HAL_ADC_PollForConversion() to ensure that conversion is completed
                                             and use HAL_ADC_GetValue() to retrieve conversion result and trig another conversion.
                                       Note: ADC clock latency and some timing constraints depending on clock prescaler have to be taken into account: refer to reference manual (register ADC_CR2 bit DELS description). */
  uint32_t LowPowerAutoPowerOff;  /*!< Selects the auto-off mode: the ADC automatically powers-off after a conversion and automatically wakes-up when a new conversion is triggered (with startup time between trigger and start of sampling).
                                       This feature can be combined with automatic wait mode (parameter 'LowPowerAutoWait').
                                       This parameter can be a value of @ref ADC_LowPowerAutoPowerOff. */
  uint32_t ChannelsBank;          /*!< Selects the ADC channels bank.
                                       This parameter can be a value of @ref ADC_ChannelsBank.
                                       Note: Banks availability depends on devices categories.
                                       Note: To change bank selection on the fly, without going through execution of 'HAL_ADC_Init()', macro '__HAL_ADC_CHANNELS_BANK()' can be used directly. */
  uint32_t ContinuousConvMode;    /*!< Specifies whether the conversion is performed in single mode (one conversion) or continuous mode for regular group,
                                       after the selected trigger occurred (software start or external trigger).
                                       This parameter can be set to ENABLE or DISABLE. */
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
  uint32_t NbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the regular group sequencer.
                                       To use regular group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 28. */
#else
  uint32_t NbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the regular group sequencer.
                                       To use regular group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 27. */
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
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
                                       This parameter can be a value of @ref ADC_External_trigger_source_Regular */
  uint32_t ExternalTrigConvEdge;  /*!< Selects the external trigger edge of regular group.
                                       If trigger is set to ADC_SOFTWARE_START, this parameter is discarded.
                                       This parameter can be a value of @ref ADC_External_trigger_edge_Regular */
  uint32_t DMAContinuousRequests; /*!< Specifies whether the DMA requests are performed in one shot mode (DMA transfer stop when number of conversions is reached)
                                       or in Continuous mode (DMA transfer unlimited, whatever number of conversions).
                                       Note: In continuous mode, DMA must be configured in circular mode. Otherwise an overrun will be triggered when DMA buffer maximum pointer is reached.
                                       This parameter can be set to ENABLE or DISABLE.
                                       Note: This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled without continuous mode or external trigger that could lauch a conversion). */
}ADC_InitTypeDef;

/** 
  * @brief  Structure definition of ADC channel for regular group   
  * @note   The setting of these parameters with function HAL_ADC_ConfigChannel() is conditioned to ADC state.
  *         ADC can be either disabled or enabled without conversion on going on regular group.
  */ 
typedef struct 
{
  uint32_t Channel;                /*!< Specifies the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADC_channels
                                        Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability.
                                              Maximum number of channels by device category (without taking in account each device package constraints): 
                                              STM32L1 category 1, 2: 24 channels on external pins + 3 channels on internal measurement paths (VrefInt, Temp sensor, Vcomp): Channel 0 to channel 26.
                                              STM32L1 category 3:    25 channels on external pins + 3 channels on internal measurement paths (VrefInt, Temp sensor, Vcomp): Channel 0 to channel 26, 1 additional channel in bank B. Note: OPAMP1 and OPAMP2 are connected internally but not increasing internal channels number: they are sharing ADC input with external channels ADC_IN3 and ADC_IN8.
                                              STM32L1 category 4, 5: 40 channels on external pins + 3 channels on internal measurement paths (VrefInt, Temp sensor, Vcomp): Channel 0 to channel 31, 11 additional channels in bank B. Note: OPAMP1 and OPAMP2 are connected internally but not increasing internal channels number: they are sharing ADC input with external channels ADC_IN3 and ADC_IN8.
                                        Note: In case of peripherals OPAMPx not used: 3 channels (3, 8, 13) can be configured as direct channels (fast channels). Refer to macro ' __HAL_ADC_CHANNEL_SPEED_FAST() '.
                                        Note: In case of peripheral OPAMP3 and ADC channel OPAMP3 used (OPAMP3 available on STM32L1 devices Cat.4 only): the analog switch COMP1_SW1 must be closed. Refer to macro: ' __HAL_OPAMP_OPAMP3OUT_CONNECT_ADC_COMP1() '. */
  uint32_t Rank;                   /*!< Specifies the rank in the regular group sequencer 
                                        This parameter can be a value of @ref ADC_regular_rank
                                        Note: In case of need to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by the new channel setting (or parameter number of conversions can be adjusted) */
  uint32_t SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        Conversion time is the addition of sampling time and processing time (12 ADC clock cycles at ADC resolution 12 bits, 11 cycles at 10 bits, 9 cycles at 8 bits, 7 cycles at 6 bits).
                                        This parameter can be a value of @ref ADC_sampling_times
                                        Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                 If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                        Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                              sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                              Refer to device datasheet for timings values, parameters TS_vrefint, TS_temp (values rough order: 4us min). */
}ADC_ChannelConfTypeDef;

/**
  * @brief  ADC Configuration analog watchdog definition
  * @note   The setting of these parameters with function is conditioned to ADC state.
  *         ADC state can be either disabled or enabled without conversion on going on regular and injected groups.
  */
typedef struct
{
  uint32_t WatchdogMode;      /*!< Configures the ADC analog watchdog mode: single/all channels, regular/injected group.
                                   This parameter can be a value of @ref ADC_analog_watchdog_mode. */
  uint32_t Channel;           /*!< Selects which ADC channel to monitor by analog watchdog.
                                   This parameter has an effect only if watchdog mode is configured on single channel (parameter WatchdogMode)
                                   This parameter can be a value of @ref ADC_channels. */
  uint32_t ITMode;            /*!< Specifies whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */
  uint32_t HighThreshold;     /*!< Configures the ADC analog watchdog High threshold value.
                                   This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
  uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog High threshold value.
                                   This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
  uint32_t WatchdogNumber;    /*!< Reserved for future use, can be set to 0 */
}ADC_AnalogWDGConfTypeDef;

/** 
  * @brief  HAL ADC state machine: ADC States structure definition  
  */ 
typedef enum
{
  HAL_ADC_STATE_RESET                   = 0x00,    /*!< ADC not yet initialized or disabled */
  HAL_ADC_STATE_READY                   = 0x01,    /*!< ADC peripheral ready for use */
  HAL_ADC_STATE_BUSY                    = 0x02,    /*!< An internal process is ongoing */ 
  HAL_ADC_STATE_BUSY_REG                = 0x12,    /*!< Regular conversion is ongoing */
  HAL_ADC_STATE_BUSY_INJ                = 0x22,    /*!< Injected conversion is ongoing */
  HAL_ADC_STATE_BUSY_INJ_REG            = 0x32,    /*!< Injected and regular conversion are ongoing */
  HAL_ADC_STATE_TIMEOUT                 = 0x03,    /*!< Timeout state */
  HAL_ADC_STATE_ERROR                   = 0x04,    /*!< ADC state error */
  HAL_ADC_STATE_EOC                     = 0x05,    /*!< Conversion is completed */
  HAL_ADC_STATE_EOC_REG                 = 0x15,    /*!< Regular conversion is completed */
  HAL_ADC_STATE_EOC_INJ                 = 0x25,    /*!< Injected conversion is completed */
  HAL_ADC_STATE_EOC_INJ_REG             = 0x35,    /*!< Injected and regular conversion are completed */
  HAL_ADC_STATE_AWD                     = 0x06,    /*!< ADC state analog watchdog */
  HAL_ADC_STATE_AWD2                    = 0x07,    /*!< Not used on STM32L1xx devices (kept for compatibility with other devices featuring several AWD) */
  HAL_ADC_STATE_AWD3                    = 0x08,    /*!< Not used on STM32l1xx devices (kept for compatibility with other devices featuring several AWD) */ 
}HAL_ADC_StateTypeDef;

/** 
  * @brief  ADC handle Structure definition  
  */ 
typedef struct
{
  ADC_TypeDef                   *Instance;              /*!< Register base address */

  ADC_InitTypeDef               Init;                   /*!< ADC required parameters */

  __IO uint32_t                 NbrOfConversionRank ;   /*!< ADC conversion rank counter */

  DMA_HandleTypeDef             *DMA_Handle;            /*!< Pointer DMA Handler */

  HAL_LockTypeDef               Lock;                   /*!< ADC locking object */

  __IO HAL_ADC_StateTypeDef     State;                  /*!< ADC communication state */

  __IO uint32_t                 ErrorCode;              /*!< ADC Error code */
}ADC_HandleTypeDef;
/**
  * @}
  */



/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_Error_Code ADC Error Code
  * @{
  */ 
#define HAL_ADC_ERROR_NONE        ((uint32_t)0x00)   /*!< No error                                              */
#define HAL_ADC_ERROR_INTERNAL    ((uint32_t)0x01)   /*!< ADC IP internal error: if problem of clocking, 
                                                          enable/disable, erroneous state                       */
#define HAL_ADC_ERROR_OVR         ((uint32_t)0x02)   /*!< Overrun error                                         */
#define HAL_ADC_ERROR_DMA         ((uint32_t)0x04)   /*!< DMA transfer error                                    */

/**
  * @}
  */

/** @defgroup ADC_ClockPrescaler ADC ClockPrescaler
  * @{
  */
#define ADC_CLOCK_ASYNC_DIV1          ((uint32_t)0x00000000)          /*!< ADC asynchronous clock derived from ADC dedicated HSI without prescaler */
#define ADC_CLOCK_ASYNC_DIV2          ((uint32_t)ADC_CCR_ADCPRE_0)    /*!< ADC asynchronous clock derived from ADC dedicated HSI divided by a prescaler of 2 */
#define ADC_CLOCK_ASYNC_DIV4          ((uint32_t)ADC_CCR_ADCPRE_1)    /*!< ADC asynchronous clock derived from ADC dedicated HSI divided by a prescaler of 4 */

#define IS_ADC_CLOCKPRESCALER(ADC_CLOCK) (((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV1) || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV2) || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV4)   )
/**
  * @}
  */

/** @defgroup ADC_Resolution ADC Resolution
  * @{
  */
#define ADC_RESOLUTION12b      ((uint32_t)0x00000000)          /*!<  ADC 12-bit resolution */
#define ADC_RESOLUTION10b      ((uint32_t)ADC_CR1_RES_0)       /*!<  ADC 10-bit resolution */
#define ADC_RESOLUTION8b       ((uint32_t)ADC_CR1_RES_1)       /*!<  ADC 8-bit resolution */
#define ADC_RESOLUTION6b       ((uint32_t)ADC_CR1_RES)         /*!<  ADC 6-bit resolution */

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION12b) || \
                                       ((RESOLUTION) == ADC_RESOLUTION10b) || \
                                       ((RESOLUTION) == ADC_RESOLUTION8b)  || \
                                       ((RESOLUTION) == ADC_RESOLUTION6b)    )

#define IS_ADC_RESOLUTION_8_6_BITS(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION8b) || \
                                                ((RESOLUTION) == ADC_RESOLUTION6b)   )
/**
  * @}
  */

/** @defgroup ADC_Data_align ADC Data_align
  * @{
  */
#define ADC_DATAALIGN_RIGHT      ((uint32_t)0x00000000)
#define ADC_DATAALIGN_LEFT       ((uint32_t)ADC_CR2_ALIGN)

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT)    )
/**
  * @}
  */

/** @defgroup ADC_Scan_mode ADC Scan mode
  * @{
  */
#define ADC_SCAN_DISABLE         ((uint32_t)0x00000000)
#define ADC_SCAN_ENABLE          ((uint32_t)0x00000001)

#define IS_ADC_SCAN_MODE(SCAN_MODE) (((SCAN_MODE) == ADC_SCAN_DISABLE) || \
                                     ((SCAN_MODE) == ADC_SCAN_ENABLE)    )
/**
  * @}
  */

/** @defgroup ADC_External_trigger_edge_Regular ADC External trigger edge Regular
  * @{
  */
#define ADC_EXTERNALTRIGCONVEDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGCONVEDGE_RISING         ((uint32_t)ADC_CR2_EXTEN_0)         
#define ADC_EXTERNALTRIGCONVEDGE_FALLING        ((uint32_t)ADC_CR2_EXTEN_1)
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING  ((uint32_t)ADC_CR2_EXTEN)

#define IS_ADC_EXTTRIG_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGCONVEDGE_NONE)         || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING)       || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_FALLING)      || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING)  )
/**
  * @}
  */

/** @defgroup ADC_External_trigger_source_Regular ADC External trigger source Regular
  * @{
  */
/* List of external triggers with generic trigger name, sorted by trigger     */
/* name:                                                                      */

/* External triggers of regular group for ADC1 */
#define ADC_EXTERNALTRIGCONV_T2_CC3      ADC_EXTERNALTRIG_T2_CC3
#define ADC_EXTERNALTRIGCONV_T2_CC2      ADC_EXTERNALTRIG_T2_CC2
#define ADC_EXTERNALTRIGCONV_T2_TRGO     ADC_EXTERNALTRIG_T2_TRGO
#define ADC_EXTERNALTRIGCONV_T3_CC1      ADC_EXTERNALTRIG_T3_CC1
#define ADC_EXTERNALTRIGCONV_T3_CC3      ADC_EXTERNALTRIG_T3_CC3
#define ADC_EXTERNALTRIGCONV_T3_TRGO     ADC_EXTERNALTRIG_T3_TRGO
#define ADC_EXTERNALTRIGCONV_T4_CC4      ADC_EXTERNALTRIG_T4_CC4
#define ADC_EXTERNALTRIGCONV_T4_TRGO     ADC_EXTERNALTRIG_T4_TRGO
#define ADC_EXTERNALTRIGCONV_T6_TRGO     ADC_EXTERNALTRIG_T6_TRGO
#define ADC_EXTERNALTRIGCONV_T9_CC2      ADC_EXTERNALTRIG_T9_CC2
#define ADC_EXTERNALTRIGCONV_T9_TRGO     ADC_EXTERNALTRIG_T9_TRGO
#define ADC_EXTERNALTRIGCONV_EXT_IT11    ADC_EXTERNALTRIG_EXT_IT11

#define ADC_SOFTWARE_START               ((uint32_t)0x00000010)

#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T6_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T9_CC2)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T9_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11) || \
                                 ((REGTRIG) == ADC_SOFTWARE_START)              )
/**
  * @}
  */

/** @defgroup ADC_Internal_HAL_driver_Ext_trig_src_Regular ADC Internal HAL driver Ext trig src Regular
  * @{
  */

/* List of external triggers of regular group for ADC1:                       */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */

/* External triggers of regular group for ADC1 */
#define ADC_EXTERNALTRIG_T9_CC2         ((uint32_t) 0x00000000)
#define ADC_EXTERNALTRIG_T9_TRGO        ((uint32_t)(                                                         ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIG_T2_CC3         ((uint32_t)(                                      ADC_CR2_EXTSEL_1                   ))
#define ADC_EXTERNALTRIG_T2_CC2         ((uint32_t)(                                      ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIG_T3_TRGO        ((uint32_t)(                   ADC_CR2_EXTSEL_2                                      ))
#define ADC_EXTERNALTRIG_T4_CC4         ((uint32_t)(                   ADC_CR2_EXTSEL_2 |                    ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIG_T2_TRGO        ((uint32_t)(                   ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1                   ))
#define ADC_EXTERNALTRIG_T3_CC1         ((uint32_t)(                   ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIG_T3_CC3         ((uint32_t)(ADC_CR2_EXTSEL_3                                                         ))
#define ADC_EXTERNALTRIG_T4_TRGO        ((uint32_t)(ADC_CR2_EXTSEL_3                                       | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIG_T6_TRGO        ((uint32_t)(ADC_CR2_EXTSEL_3                    | ADC_CR2_EXTSEL_1                   ))
#define ADC_EXTERNALTRIG_EXT_IT11       ((uint32_t)(ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))

/**
  * @}
  */

/** @defgroup ADC_EOCSelection ADC EOCSelection
  * @{
  */
#define EOC_SEQ_CONV            ((uint32_t)0x00000000)
#define EOC_SINGLE_CONV         ((uint32_t)ADC_CR2_EOCS)

#define IS_ADC_EOC_SELECTION(EOC_SELECTION) (((EOC_SELECTION) == EOC_SINGLE_CONV)    || \
                                             ((EOC_SELECTION) == EOC_SEQ_CONV)         )
/**
  * @}
  */

/** @defgroup ADC_LowPowerAutoWait ADC LowPowerAutoWait
  * @{
  */
/*!< Note : For compatibility with other STM32 devices with ADC autowait      */
/* feature limited to enable or disable settings:                             */
/* Setting "ADC_AUTOWAIT_UNTIL_DATA_READ" is equivalent to "ENABLE".          */

#define ADC_AUTOWAIT_DISABLE                ((uint32_t)0x00000000)
#define ADC_AUTOWAIT_UNTIL_DATA_READ        ((uint32_t)(                                  ADC_CR2_DELS_0)) /*!< Insert a delay between ADC conversions: infinite delay, until the result of previous conversion is read */
#define ADC_AUTOWAIT_7_APBCLOCKCYCLES       ((uint32_t)(                 ADC_CR2_DELS_1                 )) /*!< Insert a delay between ADC conversions: 7 APB clock cycles */
#define ADC_AUTOWAIT_15_APBCLOCKCYCLES      ((uint32_t)(                 ADC_CR2_DELS_1 | ADC_CR2_DELS_0)) /*!< Insert a delay between ADC conversions: 15 APB clock cycles */
#define ADC_AUTOWAIT_31_APBCLOCKCYCLES      ((uint32_t)(ADC_CR2_DELS_2                                  )) /*!< Insert a delay between ADC conversions: 31 APB clock cycles */
#define ADC_AUTOWAIT_63_APBCLOCKCYCLES      ((uint32_t)(ADC_CR2_DELS_2                  | ADC_CR2_DELS_0)) /*!< Insert a delay between ADC conversions: 63 APB clock cycles */
#define ADC_AUTOWAIT_127_APBCLOCKCYCLES     ((uint32_t)(ADC_CR2_DELS_2 | ADC_CR2_DELS_1                 )) /*!< Insert a delay between ADC conversions: 127 APB clock cycles */
#define ADC_AUTOWAIT_255_APBCLOCKCYCLES     ((uint32_t)(ADC_CR2_DELS_2 | ADC_CR2_DELS_1 | ADC_CR2_DELS_0)) /*!< Insert a delay between ADC conversions: 255 APB clock cycles */

#define IS_ADC_AUTOWAIT(AUTOWAIT) (((AUTOWAIT) == ADC_AUTOWAIT_DISABLE)            || \
                                   ((AUTOWAIT) == ADC_AUTOWAIT_UNTIL_DATA_READ)    || \
                                   ((AUTOWAIT) == ADC_AUTOWAIT_7_APBCLOCKCYCLES)   || \
                                   ((AUTOWAIT) == ADC_AUTOWAIT_15_APBCLOCKCYCLES)  || \
                                   ((AUTOWAIT) == ADC_AUTOWAIT_31_APBCLOCKCYCLES)  || \
                                   ((AUTOWAIT) == ADC_AUTOWAIT_63_APBCLOCKCYCLES)  || \
                                   ((AUTOWAIT) == ADC_AUTOWAIT_127_APBCLOCKCYCLES) || \
                                   ((AUTOWAIT) == ADC_AUTOWAIT_255_APBCLOCKCYCLES)   )
/**
  * @}
  */

/** @defgroup ADC_LowPowerAutoPowerOff ADC LowPowerAutoPowerOff
  * @{
  */
#define ADC_AUTOPOWEROFF_DISABLE            ((uint32_t)0x00000000)
#define ADC_AUTOPOWEROFF_IDLE_PHASE         ((uint32_t)ADC_CR1_PDI)                     /*!< ADC power off when ADC is not converting (idle phase) */
#define ADC_AUTOPOWEROFF_DELAY_PHASE        ((uint32_t)ADC_CR1_PDD)                     /*!< ADC power off when a delay is inserted between conversions (see parameter ADC_LowPowerAutoWait) */
#define ADC_AUTOPOWEROFF_IDLE_DELAY_PHASES  ((uint32_t)(ADC_CR1_PDI | ADC_CR1_PDD))     /*!< ADC power off when ADC is not converting (idle phase) and when a delay is inserted between conversions */

#define IS_ADC_AUTOPOWEROFF(AUTOPOWEROFF) (((AUTOPOWEROFF) == ADC_AUTOPOWEROFF_DISABLE)          || \
                                           ((AUTOPOWEROFF) == ADC_AUTOPOWEROFF_IDLE_PHASE)       || \
                                           ((AUTOPOWEROFF) == ADC_AUTOPOWEROFF_DELAY_PHASE)      || \
                                           ((AUTOPOWEROFF) == ADC_AUTOPOWEROFF_IDLE_DELAY_PHASES)  )
/**
  * @}
  */


/** @defgroup ADC_ChannelsBank ADC ChannelsBank
  * @{
  */
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define ADC_CHANNELS_BANK_A                 ((uint32_t)0x00000000)
#define ADC_CHANNELS_BANK_B                 ((uint32_t)ADC_CR2_CFG)

#define IS_ADC_CHANNELSBANK(BANK) (((BANK) == ADC_CHANNELS_BANK_A) || \
                                   ((BANK) == ADC_CHANNELS_BANK_B)   )
#else
#define ADC_CHANNELS_BANK_A                 ((uint32_t)0x00000000)

#define IS_ADC_CHANNELSBANK(BANK) (((BANK) == ADC_CHANNELS_BANK_A))
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
/**
  * @}
  */

/** @defgroup ADC_channels ADC channels
  * @{
  */
/* Note: Depending on devices, some channels may not be available on package  */
/*       pins. Refer to device datasheet for channels availability.           */
#define ADC_CHANNEL_0           ((uint32_t)0x00000000)                                                                            /* Channel different in bank A and bank B */
#define ADC_CHANNEL_1           ((uint32_t)(                                                                    ADC_SQR5_SQ1_0))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_2           ((uint32_t)(                                                   ADC_SQR5_SQ1_1                 ))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_3           ((uint32_t)(                                                   ADC_SQR5_SQ1_1 | ADC_SQR5_SQ1_0))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_4           ((uint32_t)(                                  ADC_SQR5_SQ1_2                                  ))  /* Direct (fast) channel */
#define ADC_CHANNEL_5           ((uint32_t)(                                  ADC_SQR5_SQ1_2                  | ADC_SQR5_SQ1_0))  /* Direct (fast) channel */
#define ADC_CHANNEL_6           ((uint32_t)(                                  ADC_SQR5_SQ1_2 | ADC_SQR5_SQ1_1                 ))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_7           ((uint32_t)(                                  ADC_SQR5_SQ1_2 | ADC_SQR5_SQ1_1 | ADC_SQR5_SQ1_0))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_8           ((uint32_t)(                 ADC_SQR5_SQ1_3                                                   ))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_9           ((uint32_t)(                 ADC_SQR5_SQ1_3                                   | ADC_SQR5_SQ1_0))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_10          ((uint32_t)(                 ADC_SQR5_SQ1_3                  | ADC_SQR5_SQ1_1                 ))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_11          ((uint32_t)(                 ADC_SQR5_SQ1_3                  | ADC_SQR5_SQ1_1 | ADC_SQR5_SQ1_0))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_12          ((uint32_t)(                 ADC_SQR5_SQ1_3 | ADC_SQR5_SQ1_2                                  ))  /* Channel different in bank A and bank B */
#define ADC_CHANNEL_13          ((uint32_t)(                 ADC_SQR5_SQ1_3 | ADC_SQR5_SQ1_2                  | ADC_SQR5_SQ1_0))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_14          ((uint32_t)(                 ADC_SQR5_SQ1_3 | ADC_SQR5_SQ1_2 | ADC_SQR5_SQ1_1                 ))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_15          ((uint32_t)(                 ADC_SQR5_SQ1_3 | ADC_SQR5_SQ1_2 | ADC_SQR5_SQ1_1 | ADC_SQR5_SQ1_0))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_16          ((uint32_t)(ADC_SQR5_SQ1_4                                                                    ))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_17          ((uint32_t)(ADC_SQR5_SQ1_4                                                    | ADC_SQR5_SQ1_0))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_18          ((uint32_t)(ADC_SQR5_SQ1_4                                   | ADC_SQR5_SQ1_1                 ))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_19          ((uint32_t)(ADC_SQR5_SQ1_4                                   | ADC_SQR5_SQ1_1 | ADC_SQR5_SQ1_0))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_20          ((uint32_t)(ADC_SQR5_SQ1_4                  | ADC_SQR5_SQ1_2                                  ))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_21          ((uint32_t)(ADC_SQR5_SQ1_4                  | ADC_SQR5_SQ1_2                  | ADC_SQR5_SQ1_0))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_22          ((uint32_t)(ADC_SQR5_SQ1_4                  | ADC_SQR5_SQ1_2 | ADC_SQR5_SQ1_1                 ))  /* Direct (fast) channel */
#define ADC_CHANNEL_23          ((uint32_t)(ADC_SQR5_SQ1_4                  | ADC_SQR5_SQ1_2 | ADC_SQR5_SQ1_1 | ADC_SQR5_SQ1_0))  /* Direct (fast) channel */
#define ADC_CHANNEL_24          ((uint32_t)(ADC_SQR5_SQ1_4 | ADC_SQR5_SQ1_3                                                   ))  /* Direct (fast) channel */
#define ADC_CHANNEL_25          ((uint32_t)(ADC_SQR5_SQ1_4 | ADC_SQR5_SQ1_3                                   | ADC_SQR5_SQ1_0))  /* Direct (fast) channel */
#define ADC_CHANNEL_26          ((uint32_t)(ADC_SQR5_SQ1_4 | ADC_SQR5_SQ1_3                  | ADC_SQR5_SQ1_1                 ))  /* Channel common to both bank A and bank B */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define ADC_CHANNEL_27          ((uint32_t)(ADC_SQR5_SQ1_4 | ADC_SQR5_SQ1_3                  | ADC_SQR5_SQ1_1 | ADC_SQR5_SQ1_0))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_28          ((uint32_t)(ADC_SQR5_SQ1_4 | ADC_SQR5_SQ1_3 | ADC_SQR5_SQ1_2                                  ))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_29          ((uint32_t)(ADC_SQR5_SQ1_4 | ADC_SQR5_SQ1_3 | ADC_SQR5_SQ1_2                  | ADC_SQR5_SQ1_0))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_30          ((uint32_t)(ADC_SQR5_SQ1_4 | ADC_SQR5_SQ1_3 | ADC_SQR5_SQ1_2 | ADC_SQR5_SQ1_1                 ))  /* Channel common to both bank A and bank B */
#define ADC_CHANNEL_31          ((uint32_t)(ADC_SQR5_SQ1_4 | ADC_SQR5_SQ1_3 | ADC_SQR5_SQ1_2 | ADC_SQR5_SQ1_1 | ADC_SQR5_SQ1_0))  /* Channel common to both bank A and bank B */
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#define ADC_CHANNEL_TEMPSENSOR  ADC_CHANNEL_16  /* ADC internal channel (no connection on device pin). Channel common to both bank A and bank B. */
#define ADC_CHANNEL_VREFINT     ADC_CHANNEL_17  /* ADC internal channel (no connection on device pin). Channel common to both bank A and bank B. */
#define ADC_CHANNEL_VCOMP       ADC_CHANNEL_26  /* ADC internal channel (no connection on device pin). Channel common to both bank A and bank B. */

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define ADC_CHANNEL_VOPAMP1     ADC_CHANNEL_3   /* Internal connection from OPAMP1 output to ADC switch matrix */
#define ADC_CHANNEL_VOPAMP2     ADC_CHANNEL_8   /* Internal connection from OPAMP2 output to ADC switch matrix */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD)
#define ADC_CHANNEL_VOPAMP3     ADC_CHANNEL_13  /* Internal connection from OPAMP3 output to ADC switch matrix */
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD */
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB) || defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
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
                                 ((CHANNEL) == ADC_CHANNEL_16)          || \
                                 ((CHANNEL) == ADC_CHANNEL_17)          || \
                                 ((CHANNEL) == ADC_CHANNEL_18)          || \
                                 ((CHANNEL) == ADC_CHANNEL_19)          || \
                                 ((CHANNEL) == ADC_CHANNEL_20)          || \
                                 ((CHANNEL) == ADC_CHANNEL_21)          || \
                                 ((CHANNEL) == ADC_CHANNEL_22)          || \
                                 ((CHANNEL) == ADC_CHANNEL_23)          || \
                                 ((CHANNEL) == ADC_CHANNEL_24)          || \
                                 ((CHANNEL) == ADC_CHANNEL_25)          || \
                                 ((CHANNEL) == ADC_CHANNEL_26)            )
#endif /* STM32L100xB || STM32L151xB || STM32L152xB || STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
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
                                 ((CHANNEL) == ADC_CHANNEL_16)          || \
                                 ((CHANNEL) == ADC_CHANNEL_17)          || \
                                 ((CHANNEL) == ADC_CHANNEL_18)          || \
                                 ((CHANNEL) == ADC_CHANNEL_19)          || \
                                 ((CHANNEL) == ADC_CHANNEL_20)          || \
                                 ((CHANNEL) == ADC_CHANNEL_21)          || \
                                 ((CHANNEL) == ADC_CHANNEL_22)          || \
                                 ((CHANNEL) == ADC_CHANNEL_23)          || \
                                 ((CHANNEL) == ADC_CHANNEL_24)          || \
                                 ((CHANNEL) == ADC_CHANNEL_25)          || \
                                 ((CHANNEL) == ADC_CHANNEL_26)          || \
                                 ((CHANNEL) == ADC_CHANNEL_27)          || \
                                 ((CHANNEL) == ADC_CHANNEL_28)          || \
                                 ((CHANNEL) == ADC_CHANNEL_29)          || \
                                 ((CHANNEL) == ADC_CHANNEL_30)          || \
                                 ((CHANNEL) == ADC_CHANNEL_31)            )
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
/**
  * @}
  */

/** @defgroup ADC_sampling_times ADC sampling times
  * @{
  */
#define ADC_SAMPLETIME_4CYCLES      ((uint32_t)0x00000000)                            /*!< Sampling time 4 ADC clock cycles */
#define ADC_SAMPLETIME_9CYCLES      ((uint32_t) ADC_SMPR3_SMP0_0)                     /*!< Sampling time 9 ADC clock cycles */
#define ADC_SAMPLETIME_16CYCLES     ((uint32_t) ADC_SMPR3_SMP0_1)                     /*!< Sampling time 16 ADC clock cycles */
#define ADC_SAMPLETIME_24CYCLES     ((uint32_t)(ADC_SMPR3_SMP0_1 | ADC_SMPR3_SMP0_0)) /*!< Sampling time 24 ADC clock cycles */
#define ADC_SAMPLETIME_48CYCLES     ((uint32_t) ADC_SMPR3_SMP0_2)                     /*!< Sampling time 48 ADC clock cycles */
#define ADC_SAMPLETIME_96CYCLES     ((uint32_t)(ADC_SMPR3_SMP0_2 | ADC_SMPR3_SMP0_0)) /*!< Sampling time 96 ADC clock cycles */
#define ADC_SAMPLETIME_192CYCLES    ((uint32_t)(ADC_SMPR3_SMP0_2 | ADC_SMPR3_SMP0_1)) /*!< Sampling time 192 ADC clock cycles */
#define ADC_SAMPLETIME_384CYCLES    ((uint32_t) ADC_SMPR3_SMP0)                       /*!< Sampling time 384 ADC clock cycles */

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_4CYCLES)   || \
                                  ((TIME) == ADC_SAMPLETIME_9CYCLES)   || \
                                  ((TIME) == ADC_SAMPLETIME_16CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_24CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_48CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_96CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_192CYCLES) || \
                                  ((TIME) == ADC_SAMPLETIME_384CYCLES)   )
/**
  * @}
  */

/** @defgroup ADC_sampling_times_all_channels ADC sampling times all channels
  * @{
  */
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR3BIT2                                          \
     (ADC_SMPR3_SMP9_2 | ADC_SMPR3_SMP8_2 | ADC_SMPR3_SMP7_2 | ADC_SMPR3_SMP6_2 |     \
      ADC_SMPR3_SMP5_2 | ADC_SMPR3_SMP4_2 | ADC_SMPR3_SMP3_2 | ADC_SMPR3_SMP2_2 |     \
      ADC_SMPR3_SMP1_2 | ADC_SMPR3_SMP0_2)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2                                          \
     (ADC_SMPR2_SMP19_2 | ADC_SMPR2_SMP18_2 | ADC_SMPR2_SMP17_2 | ADC_SMPR2_SMP16_2 | \
      ADC_SMPR2_SMP15_2 | ADC_SMPR2_SMP14_2 | ADC_SMPR2_SMP13_2 | ADC_SMPR2_SMP12_2 | \
      ADC_SMPR2_SMP11_2 | ADC_SMPR2_SMP10_2)
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB) || defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2                                          \
     (ADC_SMPR1_SMP26_2 | ADC_SMPR1_SMP25_2 | ADC_SMPR1_SMP24_2 | ADC_SMPR1_SMP23_2 | \
      ADC_SMPR1_SMP22_2 | ADC_SMPR1_SMP21_2 | ADC_SMPR1_SMP20_2)
#endif /* STM32L100xB || STM32L151xB || STM32L152xB || STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2                                          \
     (ADC_SMPR1_SMP29_2 | ADC_SMPR1_SMP28_2 | ADC_SMPR1_SMP27_2 | ADC_SMPR1_SMP26_2 | \
      ADC_SMPR1_SMP25_2 | ADC_SMPR1_SMP24_2 | ADC_SMPR1_SMP23_2 | ADC_SMPR1_SMP22_2 | \
      ADC_SMPR1_SMP21_2 | ADC_SMPR1_SMP20_2)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR0BIT2                                          \
     (ADC_SMPR0_SMP31_2 | ADC_SMPR0_SMP30_2 )
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
       
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR3BIT1                                          \
     (ADC_SMPR3_SMP9_1 | ADC_SMPR3_SMP8_1 | ADC_SMPR3_SMP7_1 | ADC_SMPR3_SMP6_1 |     \
      ADC_SMPR3_SMP5_1 | ADC_SMPR3_SMP4_1 | ADC_SMPR3_SMP3_1 | ADC_SMPR3_SMP2_1 |     \
      ADC_SMPR3_SMP1_1 | ADC_SMPR3_SMP0_1)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT1                                          \
     (ADC_SMPR2_SMP19_1 | ADC_SMPR2_SMP18_1 | ADC_SMPR2_SMP17_1 | ADC_SMPR2_SMP16_1 | \
      ADC_SMPR2_SMP15_1 | ADC_SMPR2_SMP14_1 | ADC_SMPR2_SMP13_1 | ADC_SMPR2_SMP12_1 | \
      ADC_SMPR2_SMP11_1 | ADC_SMPR2_SMP10_1)
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB) || defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1                                          \
     (ADC_SMPR1_SMP26_1 | ADC_SMPR1_SMP25_1 | ADC_SMPR1_SMP24_1 | ADC_SMPR1_SMP23_1 | \
      ADC_SMPR1_SMP22_1 | ADC_SMPR1_SMP21_1 | ADC_SMPR1_SMP20_1)
#endif /* STM32L100xB || STM32L151xB || STM32L152xB || STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT1                                          \
     (ADC_SMPR1_SMP29_1 | ADC_SMPR1_SMP28_1 | ADC_SMPR1_SMP27_1 | ADC_SMPR1_SMP26_1 | \
      ADC_SMPR1_SMP25_1 | ADC_SMPR1_SMP24_1 | ADC_SMPR1_SMP23_1 | ADC_SMPR1_SMP22_1 | \
      ADC_SMPR1_SMP21_1 | ADC_SMPR1_SMP20_1)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR0BIT1                                          \
     (ADC_SMPR0_SMP31_1 | ADC_SMPR0_SMP30_1 )
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
       
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR3BIT0                                          \
     (ADC_SMPR3_SMP9_0 | ADC_SMPR3_SMP8_0 | ADC_SMPR3_SMP7_0 | ADC_SMPR3_SMP6_0 |     \
      ADC_SMPR3_SMP5_0 | ADC_SMPR3_SMP4_0 | ADC_SMPR3_SMP3_0 | ADC_SMPR3_SMP2_0 |     \
      ADC_SMPR3_SMP1_0 | ADC_SMPR3_SMP0_0)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT0                                          \
     (ADC_SMPR2_SMP19_0 | ADC_SMPR2_SMP18_0 | ADC_SMPR2_SMP17_0 | ADC_SMPR2_SMP16_0 | \
      ADC_SMPR2_SMP15_0 | ADC_SMPR2_SMP14_0 | ADC_SMPR2_SMP13_0 | ADC_SMPR2_SMP12_0 | \
      ADC_SMPR2_SMP11_0 | ADC_SMPR2_SMP10_0)
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB) || defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0                                          \
     (ADC_SMPR1_SMP26_0 | ADC_SMPR1_SMP25_0 | ADC_SMPR1_SMP24_0 | ADC_SMPR1_SMP23_0 | \
      ADC_SMPR1_SMP22_0 | ADC_SMPR1_SMP21_0 | ADC_SMPR1_SMP20_0)
#endif /* STM32L100xB || STM32L151xB || STM32L152xB || STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT0                                          \
     (ADC_SMPR1_SMP29_0 | ADC_SMPR1_SMP28_0 | ADC_SMPR1_SMP27_0 | ADC_SMPR1_SMP26_0 | \
      ADC_SMPR1_SMP25_0 | ADC_SMPR1_SMP24_0 | ADC_SMPR1_SMP23_0 | ADC_SMPR1_SMP22_0 | \
      ADC_SMPR1_SMP21_0 | ADC_SMPR1_SMP20_0)
#define ADC_SAMPLETIME_ALLCHANNELS_SMPR0BIT0                                          \
     (ADC_SMPR0_SMP31_0 | ADC_SMPR0_SMP30_0 )
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
/**
  * @}
  */

/** @defgroup ADC_regular_rank ADC regular rank
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
#define ADC_REGULAR_RANK_17   ((uint32_t)0x00000011)
#define ADC_REGULAR_RANK_18   ((uint32_t)0x00000012)
#define ADC_REGULAR_RANK_19   ((uint32_t)0x00000013)
#define ADC_REGULAR_RANK_20   ((uint32_t)0x00000014)
#define ADC_REGULAR_RANK_21   ((uint32_t)0x00000015)
#define ADC_REGULAR_RANK_22   ((uint32_t)0x00000016)
#define ADC_REGULAR_RANK_23   ((uint32_t)0x00000017)
#define ADC_REGULAR_RANK_24   ((uint32_t)0x00000018)
#define ADC_REGULAR_RANK_25   ((uint32_t)0x00000019)
#define ADC_REGULAR_RANK_26   ((uint32_t)0x0000001A)
#define ADC_REGULAR_RANK_27   ((uint32_t)0x0000001B)
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define ADC_REGULAR_RANK_28   ((uint32_t)0x0000001C)
       
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
                                      ((CHANNEL) == ADC_REGULAR_RANK_16) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_17) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_18) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_19) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_20) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_21) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_22) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_23) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_24) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_25) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_26) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_27) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_28)   )
#else

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
                                      ((CHANNEL) == ADC_REGULAR_RANK_16) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_17) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_18) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_19) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_20) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_21) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_22) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_23) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_24) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_25) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_26) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_27)   )
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_mode ADC analog watchdog mode
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

/** @defgroup ADC_conversion_group ADC conversion group
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

/** @defgroup ADC_Event_type ADC Event type
  * @{
  */
#define AWD_EVENT               ((uint32_t)ADC_FLAG_AWD)   /*!< ADC Analog watchdog event */
#define OVR_EVENT               ((uint32_t)ADC_FLAG_OVR)   /*!< ADC overrun event */

#define IS_ADC_EVENT_TYPE(EVENT) (((EVENT) == AWD_EVENT)  || \
                                  ((EVENT) == ADC_FLAG_OVR) )
/**
  * @}
  */

/** @defgroup ADC_interrupts_definition ADC interrupts definition
  * @{
  */
#define ADC_IT_EOC           ADC_CR1_EOCIE        /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_JEOC          ADC_CR1_JEOCIE       /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IT_AWD           ADC_CR1_AWDIE        /*!< ADC Analog watchdog interrupt source */
#define ADC_IT_OVR           ADC_CR1_OVRIE        /*!< ADC overrun interrupt source */
/**
  * @}
  */

/** @defgroup ADC_flags_definition ADC flags definition
  * @{
  */
#define ADC_FLAG_AWD           ADC_SR_AWD      /*!< ADC Analog watchdog flag */
#define ADC_FLAG_EOC           ADC_SR_EOC      /*!< ADC End of Regular conversion flag */
#define ADC_FLAG_JEOC          ADC_SR_JEOC     /*!< ADC End of Injected conversion flag */
#define ADC_FLAG_JSTRT         ADC_SR_JSTRT    /*!< ADC Injected group start flag */
#define ADC_FLAG_STRT          ADC_SR_STRT     /*!< ADC Regular group start flag */
#define ADC_FLAG_OVR           ADC_SR_OVR      /*!< ADC overrun flag */
#define ADC_FLAG_ADONS         ADC_SR_ADONS    /*!< ADC ready status flag */
#define ADC_FLAG_RCNR          ADC_SR_RCNR     /*!< ADC Regular group ready status flag */
#define ADC_FLAG_JCNR          ADC_SR_JCNR     /*!< ADC Regular group ready status flag */

/* Combination of all post-conversion flags bits: EOC/EOS, JEOC/JEOS, OVR, AWDx */
#define ADC_FLAG_POSTCONV_ALL   (ADC_FLAG_EOC | ADC_FLAG_JEOC | ADC_FLAG_AWD | \
                                 ADC_FLAG_OVR)
/**
  * @}
  */

/** @defgroup ADC_range_verification ADC range verification
  * For a unique ADC resolution: 12 bits
  * @{
  */
#define IS_ADC_RANGE(ADC_VALUE) ((ADC_VALUE) <= ((uint32_t)0x0FFF))
/**
  * @}
  */

/** @defgroup ADC_regular_nb_conv_verification ADC regular nb conv verification
  * @{
  */
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define IS_ADC_REGULAR_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)28)))
#else
#define IS_ADC_REGULAR_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)27)))
#endif
/**
  * @}
  */

/** @defgroup ADC_regular_discontinuous_mode_number_verification ADC regular discontinuous mode number verification
  * @{
  */
#define IS_ADC_REGULAR_DISCONT_NUMBER(NUMBER) (((NUMBER) >= ((uint32_t)1)) && ((NUMBER) <= ((uint32_t)8)))
/**
  * @}
  */

/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/

/** @defgroup ADC_Exported_Macros ADC Exported Macros
  * @{
  */
/* Macro for internal HAL driver usage, and possibly can be used into code of */
/* final user.                                                                */

/**
  * @brief Verification of ADC state: enabled or disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
#define __HAL_ADC_IS_ENABLED(__HANDLE__)                                       \
       ((( ((__HANDLE__)->Instance->SR & ADC_SR_ADONS) == ADC_SR_ADONS )       \
        ) ? SET : RESET)

/**
  * @brief Test if conversion trigger of regular group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define __HAL_ADC_IS_SOFTWARE_START_REGULAR(__HANDLE__)                        \
       (((__HANDLE__)->Instance->CR2 & ADC_CR2_EXTEN) == RESET)

/**
  * @brief Test if conversion trigger of injected group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define __HAL_ADC_IS_SOFTWARE_START_INJECTED(__HANDLE__)                       \
       (((__HANDLE__)->Instance->CR2 & ADC_CR2_JEXTEN) == RESET)

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
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)                         \
  (SET_BIT((__HANDLE__)->Instance->CR1, (__INTERRUPT__)))

/**
  * @brief Disable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)                        \
  (CLEAR_BIT((__HANDLE__)->Instance->CR1, (__INTERRUPT__)))

/**
  * @brief Get the selected ADC's flag status.
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  * @retval None
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__)                               \
  ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

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
#define __HAL_ADC_CLEAR_ERRORCODE(__HANDLE__)                                  \
  ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)

/** @brief  Reset ADC handle state
  * @param  __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_ADC_STATE_RESET)
      
/**
  * @}
  */

/* Include ADC HAL Extension module */
#include "stm32l1xx_hal_adc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions
  * @{
  */

/** @addtogroup ADC_Exported_Functions_Group1
  * @{
  */


/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef       HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);
/**
  * @}
  */

/* IO operation functions  *****************************************************/

/** @addtogroup ADC_Exported_Functions_Group2
  * @{
  */


/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);
HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);

/* Non-blocking mode: DMA */
HAL_StatusTypeDef       HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
/**
  * @}
  */


/* Peripheral Control functions ***********************************************/
/** @addtogroup ADC_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef       HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);
HAL_StatusTypeDef       HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);
/**
  * @}
  */


/* Peripheral State functions *************************************************/
/** @addtogroup ADC_Exported_Functions_Group4
  * @{
  */
HAL_ADC_StateTypeDef    HAL_ADC_GetState(ADC_HandleTypeDef* hadc);
uint32_t                HAL_ADC_GetError(ADC_HandleTypeDef *hadc);
/**
  * @}
  */


/**
  * @}
  */


/* Internal HAL driver functions **********************************************/
/** @addtogroup ADC_Private_Functions
  * @{
  */

HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_ConversionStop_Disable(ADC_HandleTypeDef* hadc);
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


#endif /* __STM32L1xx_HAL_ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
