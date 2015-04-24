/**
  ******************************************************************************
  * @file    stm32f1xx_hal_adc_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of ADC HAL extension module.
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
#ifndef __STM32F1xx_HAL_ADC_EX_H
#define __STM32F1xx_HAL_ADC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"  

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup ADCEx_Exported_Types ADCEx Exported Types
  * @{
  */

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
                                               This parameter can be a value of @ref ADC_channels
                                               Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability.
                                               Note: On STM32F1 devices with several ADC: Only ADC1 can access internal measurement channels (VrefInt/TempSensor) 
                                               Note: On STM32F10xx8 and STM32F10xxB devices: A low-amplitude voltage glitch may be generated (on ADC input 0) on the PA0 pin, when the ADC is converting with injection trigger.
                                                     It is advised to distribute the analog channels so that Channel 0 is configured as an injected channel.
                                                     Refer to errata sheet of these devices for more details. */
  uint32_t InjectedRank;                  /*!< Rank in the injected group sequencer
                                               This parameter must be a value of @ref ADCEx_injected_rank
                                               Note: In case of need to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by the new channel setting (or parameter number of conversions can be adjusted) */
  uint32_t InjectedSamplingTime;          /*!< Sampling time value to be set for the selected channel.
                                               Unit: ADC clock cycles
                                               Conversion time is the addition of sampling time and processing time (12.5 ADC clock cycles at ADC resolution 12 bits).
                                               This parameter can be a value of @ref ADC_sampling_times
                                               Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                        If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                               Note: In case of usage of internal measurement channels (VrefInt/TempSensor),
                                                     sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                                     Refer to device datasheet for timings values, parameters TS_vrefint, TS_temp (values rough order: 5us to 17.1us min). */
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

#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
/** 
  * @brief  Structure definition of ADC multimode
  * @note   The setting of these parameters with function HAL_ADCEx_MultiModeConfigChannel() is conditioned to ADCs state (both ADCs of the common group).
  *         State of ADCs of the common group must be: disabled.
  */
typedef struct
{
  uint32_t Mode;              /*!< Configures the ADC to operate in independent or multi mode. 
                                   This parameter can be a value of @ref ADCEx_Common_mode
                                   Note: In dual mode, a change of channel configuration generates a restart that can produce a loss of synchronization. It is recommended to disable dual mode before any configuration change.
                                   Note: In case of simultaneous mode used: Exactly the same sampling time should be configured for the 2 channels that will be sampled simultaneously by ACD1 and ADC2.
                                   Note: In case of interleaved mode used: To avoid overlap between conversions, maximum sampling time allowed is 7 ADC clock cycles for fast interleaved mode and 14 ADC clock cycles for slow interleaved mode.
                                   Note: Some multimode parameters are fixed on STM32F1 and can be configured on other STM32 devices with several ADC (multimode configuration structure can have additional parameters).
                                         The equivalences are:
                                           - Parameter 'DMAAccessMode': On STM32F1, this parameter is fixed to 1 DMA channel (one DMA channel for both ADC, DMA of ADC master). On other STM32 devices with several ADC, this is equivalent to parameter 'ADC_DMAACCESSMODE_12_10_BITS'.
                                           - Parameter 'TwoSamplingDelay': On STM32F1, this parameter is fixed to 7 or 14 ADC clock cycles depending on fast or slow interleaved mode selected. On other STM32 devices with several ADC, this is equivalent to parameter 'ADC_TWOSAMPLINGDELAY_7CYCLES' (for fast interleaved mode). */

  
}ADC_MultiModeTypeDef;                                                          
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
   
/** @defgroup ADCEx_Exported_Constants ADCEx Exported Constants
  * @{
  */

/** @defgroup ADCEx_injected_rank ADCEx rank into injected group
  * @{
  */
#define ADC_INJECTED_RANK_1    ((uint32_t)0x00000001)
#define ADC_INJECTED_RANK_2    ((uint32_t)0x00000002)
#define ADC_INJECTED_RANK_3    ((uint32_t)0x00000003)
#define ADC_INJECTED_RANK_4    ((uint32_t)0x00000004)
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_edge_Injected ADCEx external trigger enable for injected group
  * @{
  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISING         ((uint32_t)ADC_CR2_JEXTTRIG)
/**
  * @}
  */
    
/** @defgroup ADC_External_trigger_source_Regular ADC External trigger selection for regular group
  * @{
  */
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target, sorted by trigger name:                                        */

/*!< External triggers of regular group for ADC1&ADC2 only */
#define ADC_EXTERNALTRIGCONV_T1_CC1         ADC1_2_EXTERNALTRIG_T1_CC1
#define ADC_EXTERNALTRIGCONV_T1_CC2         ADC1_2_EXTERNALTRIG_T1_CC2
#define ADC_EXTERNALTRIGCONV_T2_CC2         ADC1_2_EXTERNALTRIG_T2_CC2
#define ADC_EXTERNALTRIGCONV_T3_TRGO        ADC1_2_EXTERNALTRIG_T3_TRGO
#define ADC_EXTERNALTRIGCONV_T4_CC4         ADC1_2_EXTERNALTRIG_T4_CC4
#define ADC_EXTERNALTRIGCONV_EXT_IT11       ADC1_2_EXTERNALTRIG_EXT_IT11

#if defined (STM32F103xE) || defined (STM32F103xG)
/*!< External triggers of regular group for ADC3 only */
#define ADC_EXTERNALTRIGCONV_T2_CC3         ADC3_EXTERNALTRIG_T2_CC3
#define ADC_EXTERNALTRIGCONV_T3_CC1         ADC3_EXTERNALTRIG_T3_CC1
#define ADC_EXTERNALTRIGCONV_T5_CC1         ADC3_EXTERNALTRIG_T5_CC1
#define ADC_EXTERNALTRIGCONV_T5_CC3         ADC3_EXTERNALTRIG_T5_CC3
#define ADC_EXTERNALTRIGCONV_T8_CC1         ADC3_EXTERNALTRIG_T8_CC1
#endif /* STM32F103xE || defined STM32F103xG */

/*!< External triggers of regular group for all ADC instances */
#define ADC_EXTERNALTRIGCONV_T1_CC3         ADC1_2_3_EXTERNALTRIG_T1_CC3

#if defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)
/*!< Note: TIM8_TRGO is available on ADC1 and ADC2 only in high-density and   */
/*         XL-density devices.                                                */
/*         To use it on ADC or ADC2, a rempap of trigger must be done from    */
/*         EXTI line 11 to TIM8_TRGO with macro:                              */
/*           __HAL_AFIO_REMAP_ADC1_ETRGREG_ENABLE()                           */
/*           __HAL_AFIO_REMAP_ADC2_ETRGREG_ENABLE()                           */

/* Note for internal constant value management: If TIM8_TRGO is available,    */
/* its definition is set to value for ADC1&ADC2 by default and changed to     */
/* value for ADC3 by HAL ADC driver if ADC3 is selected.                      */
#define ADC_EXTERNALTRIGCONV_T8_TRGO        ADC1_2_EXTERNALTRIG_T8_TRGO
#endif /* STM32F101xE || STM32F101xG || STM32F103xE || STM32F103xG || STM32F105xC || STM32F107xC */

#define ADC_SOFTWARE_START                  ADC1_2_3_SWSTART
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_source_Injected ADCEx External trigger selection for injected group
  * @{
  */
/*!< List of external triggers with generic trigger name, independently of    */
/* ADC target, sorted by trigger name:                                        */

/*!< External triggers of injected group for ADC1&ADC2 only */
#define ADC_EXTERNALTRIGINJECCONV_T2_TRGO        ADC1_2_EXTERNALTRIGINJEC_T2_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T2_CC1         ADC1_2_EXTERNALTRIGINJEC_T2_CC1
#define ADC_EXTERNALTRIGINJECCONV_T3_CC4         ADC1_2_EXTERNALTRIGINJEC_T3_CC4
#define ADC_EXTERNALTRIGINJECCONV_T4_TRGO        ADC1_2_EXTERNALTRIGINJEC_T4_TRGO 
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15       ADC1_2_EXTERNALTRIGINJEC_EXT_IT15

#if defined (STM32F103xE) || defined (STM32F103xG)
/*!< External triggers of injected group for ADC3 only */
#define ADC_EXTERNALTRIGINJECCONV_T4_CC3         ADC3_EXTERNALTRIGINJEC_T4_CC3
#define ADC_EXTERNALTRIGINJECCONV_T8_CC2         ADC3_EXTERNALTRIGINJEC_T8_CC2
#define ADC_EXTERNALTRIGINJECCONV_T5_TRGO        ADC3_EXTERNALTRIGINJEC_T5_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T5_CC4         ADC3_EXTERNALTRIGINJEC_T5_CC4
#endif /* STM32F103xE || defined STM32F103xG */

/*!< External triggers of injected group for all ADC instances */
#define ADC_EXTERNALTRIGINJECCONV_T1_CC4         ADC1_2_3_EXTERNALTRIGINJEC_T1_CC4
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO        ADC1_2_3_EXTERNALTRIGINJEC_T1_TRGO

#if defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)
/*!< Note: TIM8_CC4 is available on ADC1 and ADC2 only in high-density and    */
/*         XL-density devices.                                                */
/*         To use it on ADC or ADC2, a rempap of trigger must be done from    */
/*         EXTI line 11 to TIM8_TRGO with macro:                              */
/*           __HAL_AFIO_REMAP_ADC1_ETRGINJ_ENABLE()                           */
/*           __HAL_AFIO_REMAP_ADC2_ETRGINJ_ENABLE()                           */

/* Note for internal constant value management: If TIM8_CC4 is available,     */
/* its definition is set to value for ADC1&ADC2 by default and changed to     */
/* value for ADC3 by HAL ADC driver if ADC3 is selected.                      */
#define ADC_EXTERNALTRIGINJECCONV_T8_CC4         ADC1_2_EXTERNALTRIGINJEC_T8_CC4
#endif /* STM32F101xE || STM32F101xG || STM32F103xE || STM32F103xG || STM32F105xC || STM32F107xC */

#define ADC_INJECTED_SOFTWARE_START              ADC1_2_3_JSWSTART
/**
  * @}
  */

#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
/** @defgroup ADCEx_Common_mode ADC Extended Dual ADC Mode
  * @{
  */
#define ADC_MODE_INDEPENDENT                  ((uint32_t)(0x00000000)) /*!< ADC dual mode disabled (ADC independent mode) */
#define ADC_DUALMODE_REGSIMULT_INJECSIMULT    ((uint32_t)(                                                            ADC_CR1_DUALMOD_0)) /*!< ADC dual mode enabled: Combined regular simultaneous + injected simultaneous mode */
#define ADC_DUALMODE_REGSIMULT_ALTERTRIG      ((uint32_t)(                                        ADC_CR1_DUALMOD_1                    )) /*!< ADC dual mode enabled: Combined regular simultaneous + alternate trigger mode */
#define ADC_DUALMODE_INJECSIMULT_INTERLFAST   ((uint32_t)(                                        ADC_CR1_DUALMOD_1 | ADC_CR1_DUALMOD_0)) /*!< ADC dual mode enabled: Combined injected simultaneous + fast interleaved mode (delay between ADC sampling phases: 7 ADC clock cycles (equivalent to parameter "TwoSamplingDelay" set to "ADC_TWOSAMPLINGDELAY_7CYCLES" on other STM32 devices)) */
#define ADC_DUALMODE_INJECSIMULT_INTERLSLOW   ((uint32_t)(                    ADC_CR1_DUALMOD_2                                        )) /*!< ADC dual mode enabled: Combined injected simultaneous + slow Interleaved mode (delay between ADC sampling phases: 14 ADC clock cycles (equivalent to parameter "TwoSamplingDelay" set to "ADC_TWOSAMPLINGDELAY_7CYCLES" on other STM32 devices)) */
#define ADC_DUALMODE_INJECSIMULT              ((uint32_t)(                    ADC_CR1_DUALMOD_2 |                     ADC_CR1_DUALMOD_0)) /*!< ADC dual mode enabled: Injected simultaneous mode only */
#define ADC_DUALMODE_REGSIMULT                ((uint32_t)(                    ADC_CR1_DUALMOD_2 | ADC_CR1_DUALMOD_1                    )) /*!< ADC dual mode enabled: Regular simultaneous mode only */
#define ADC_DUALMODE_INTERLFAST               ((uint32_t)(                    ADC_CR1_DUALMOD_2 | ADC_CR1_DUALMOD_1 | ADC_CR1_DUALMOD_0)) /*!< ADC dual mode enabled: Fast interleaved mode only (delay between ADC sampling phases: 7 ADC clock cycles (equivalent to parameter "TwoSamplingDelay" set to "ADC_TWOSAMPLINGDELAY_7CYCLES" on other STM32 devices)) */
#define ADC_DUALMODE_INTERLSLOW               ((uint32_t)(ADC_CR1_DUALMOD_3                                                            )) /*!< ADC dual mode enabled: Slow interleaved mode only (delay between ADC sampling phases: 14 ADC clock cycles (equivalent to parameter "TwoSamplingDelay" set to "ADC_TWOSAMPLINGDELAY_7CYCLES" on other STM32 devices)) */
#define ADC_DUALMODE_ALTERTRIG                ((uint32_t)(ADC_CR1_DUALMOD_3 |                                         ADC_CR1_DUALMOD_0)) /*!< ADC dual mode enabled: Alternate trigger mode only */
/**
  * @}
  */
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/

/** @addtogroup ADCEx_Private_Constants ADCEx Private Constants
  * @{
  */

/** @defgroup ADCEx_Internal_HAL_driver_Ext_trig_src_Regular ADC Extended Internal HAL driver trigger selection for regular group
  * @{
  */
/* List of external triggers of regular group for ADC1, ADC2, ADC3 (if ADC    */
/* instance is availble on the selected device).                              */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */

/* External triggers of regular group for ADC1&ADC2 (if ADCx available) */
#define ADC1_2_EXTERNALTRIG_T1_CC1           ((uint32_t) 0x00000000)
#define ADC1_2_EXTERNALTRIG_T1_CC2           ((uint32_t)(                                      ADC_CR2_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T2_CC2           ((uint32_t)(                   ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T3_TRGO          ((uint32_t)(ADC_CR2_EXTSEL_2                                      ))
#define ADC1_2_EXTERNALTRIG_T4_CC4           ((uint32_t)(ADC_CR2_EXTSEL_2 |                    ADC_CR2_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_EXT_IT11         ((uint32_t)(ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1                   ))
#if defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F103xE) || defined (STM32F103xG)
/* Note: TIM8_TRGO is available on ADC1 and ADC2 only in high-density and     */
/* XL-density devices.                                                        */
#define ADC1_2_EXTERNALTRIG_T8_TRGO          ADC1_2_EXTERNALTRIG_EXT_IT11
#endif

#if defined (STM32F103xE) || defined (STM32F103xG)
/* External triggers of regular group for ADC3 */
#define ADC3_EXTERNALTRIG_T3_CC1             ADC1_2_EXTERNALTRIG_T1_CC1
#define ADC3_EXTERNALTRIG_T2_CC3             ADC1_2_EXTERNALTRIG_T1_CC2
#define ADC3_EXTERNALTRIG_T8_CC1             ADC1_2_EXTERNALTRIG_T2_CC2
#define ADC3_EXTERNALTRIG_T8_TRGO            ADC1_2_EXTERNALTRIG_T3_TRGO
#define ADC3_EXTERNALTRIG_T5_CC1             ADC1_2_EXTERNALTRIG_T4_CC4
#define ADC3_EXTERNALTRIG_T5_CC3             ADC1_2_EXTERNALTRIG_EXT_IT11
#endif

/* External triggers of regular group for ADC1&ADC2&ADC3 (if ADCx available) */
#define ADC1_2_3_EXTERNALTRIG_T1_CC3         ((uint32_t)(                   ADC_CR2_EXTSEL_1                   ))
#define ADC1_2_3_SWSTART                     ((uint32_t)(ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))
/**
  * @}
  */

/** @defgroup ADCEx_Internal_HAL_driver_Ext_trig_src_Injected ADC Extended Internal HAL driver trigger selection for injected group
  * @{
  */
/* List of external triggers of injected group for ADC1, ADC2, ADC3 (if ADC    */
/* instance is availble on the selected device).                              */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */

/* External triggers of injected group for ADC1&ADC2 (if ADCx available) */
#define ADC1_2_EXTERNALTRIGINJEC_T2_TRGO          ((uint32_t)(                    ADC_CR2_JEXTSEL_1                    ))
#define ADC1_2_EXTERNALTRIGINJEC_T2_CC1           ((uint32_t)(                    ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_T3_CC4           ((uint32_t)(ADC_CR2_JEXTSEL_2                                        ))
#define ADC1_2_EXTERNALTRIGINJEC_T4_TRGO          ((uint32_t)(ADC_CR2_JEXTSEL_2 |                     ADC_CR2_JEXTSEL_0))
#define ADC1_2_EXTERNALTRIGINJEC_EXT_IT15         ((uint32_t)(ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1                    ))
#if defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F103xE) || defined (STM32F103xG)
/* Note: TIM8_CC4 is available on ADC1 and ADC2 only in high-density and      */
/* XL-density devices.                                                        */
#define ADC1_2_EXTERNALTRIGINJEC_T8_CC4           ADC1_2_EXTERNALTRIGINJEC_EXT_IT15
#endif

#if defined (STM32F103xE) || defined (STM32F103xG)
/* External triggers of injected group for ADC3 */
#define ADC3_EXTERNALTRIGINJEC_T4_CC3             ADC1_2_EXTERNALTRIGINJEC_T2_TRGO
#define ADC3_EXTERNALTRIGINJEC_T8_CC2             ADC1_2_EXTERNALTRIGINJEC_T2_CC1
#define ADC3_EXTERNALTRIGINJEC_T8_CC4             ADC1_2_EXTERNALTRIGINJEC_T3_CC4
#define ADC3_EXTERNALTRIGINJEC_T5_TRGO            ADC1_2_EXTERNALTRIGINJEC_T4_TRGO
#define ADC3_EXTERNALTRIGINJEC_T5_CC4             ADC1_2_EXTERNALTRIGINJEC_EXT_IT15
#endif /* STM32F103xE || defined STM32F103xG */

/* External triggers of injected group for ADC1&ADC2&ADC3 (if ADCx available) */
#define ADC1_2_3_EXTERNALTRIGINJEC_T1_TRGO        ((uint32_t) 0x00000000)
#define ADC1_2_3_EXTERNALTRIGINJEC_T1_CC4         ((uint32_t)(                                        ADC_CR2_JEXTSEL_0))
#define ADC1_2_3_JSWSTART                         ((uint32_t)(ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/** @defgroup ADCEx_Private_Macro ADCEx Private Macro
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

    
/**
  * @brief For devices with 3 ADCs: Defines the external trigger source 
  *        for regular group according to ADC into common group ADC1&ADC2 or 
  *        ADC3 (some triggers with same source have different value to
  *        be programmed into ADC EXTSEL bits of CR2 register).
  *        For devices with 2 ADCs or less: this macro makes no change.
  * @param __HANDLE__: ADC handle
  * @param __EXT_TRIG_CONV__: External trigger selected for regular group.
  * @retval External trigger to be programmed into EXTSEL bits of CR2 register
  */
#if defined (STM32F103xE) || defined (STM32F103xG)
#define ADC_CFGR_EXTSEL(__HANDLE__, __EXT_TRIG_CONV__)                         \
 (( (((__HANDLE__)->Instance) == ADC3)                                         \
  )?                                                                           \
   ( ( (__EXT_TRIG_CONV__) == ADC_EXTERNALTRIGCONV_T8_TRGO                     \
     )?                                                                        \
      (ADC3_EXTERNALTRIG_T8_TRGO)                                              \
      :                                                                        \
      (__EXT_TRIG_CONV__)                                                      \
   )                                                                           \
   :                                                                           \
   (__EXT_TRIG_CONV__)                                                         \
 )
#else
#define ADC_CFGR_EXTSEL(__HANDLE__, __EXT_TRIG_CONV__)                         \
  (__EXT_TRIG_CONV__)
#endif /* STM32F103xE || STM32F103xG */

/**
  * @brief For devices with 3 ADCs: Defines the external trigger source 
  *        for injected group according to ADC into common group ADC1&ADC2 or 
  *        ADC3 (some triggers with same source have different value to
  *        be programmed into ADC JEXTSEL bits of CR2 register).
  *        For devices with 2 ADCs or less: this macro makes no change.
  * @param __HANDLE__: ADC handle
  * @param __EXT_TRIG_INJECTCONV__: External trigger selected for injected group.
  * @retval External trigger to be programmed into JEXTSEL bits of CR2 register
  */
#if defined (STM32F103xE) || defined (STM32F103xG)
#define ADC_CFGR_JEXTSEL(__HANDLE__, __EXT_TRIG_INJECTCONV__)                  \
 (( (((__HANDLE__)->Instance) == ADC3)                                         \
  )?                                                                           \
   ( ( (__EXT_TRIG_INJECTCONV__) == ADC_EXTERNALTRIGINJECCONV_T8_CC4           \
     )?                                                                        \
      (ADC3_EXTERNALTRIGINJEC_T8_CC4)                                          \
      :                                                                        \
      (__EXT_TRIG_INJECTCONV__)                                                \
   )                                                                           \
   :                                                                           \
   (__EXT_TRIG_INJECTCONV__)                                                   \
 )
#else
#define ADC_CFGR_JEXTSEL(__HANDLE__, __EXT_TRIG_INJECTCONV__)                  \
   (__EXT_TRIG_INJECTCONV__)
#endif /* STM32F103xE || STM32F103xG */


/**
  * @brief Verification if multimode is enabled for the selected ADC (multimode ADC master or ADC slave) (applicable for devices with several ADCs)
  * @param __HANDLE__: ADC handle
  * @retval Multimode state: RESET if multimode is disabled, other value if multimode is enabled
  */
#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
#define ADC_MULTIMODE_IS_ENABLE(__HANDLE__)                                    \
 (( (((__HANDLE__)->Instance) == ADC1) || (((__HANDLE__)->Instance) == ADC2)   \
  )?                                                                           \
   (ADC1->CR1 & ADC_CR1_DUALMOD)                                               \
   :                                                                           \
   (RESET)                                                                     \
 )
#else
#define ADC_MULTIMODE_IS_ENABLE(__HANDLE__)                                    \
  (RESET)
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

/**
  * @brief Verification of condition for ADC start conversion: ADC must be in non-multimode, or multimode with handle of ADC master (applicable for devices with several ADCs)
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
#define ADC_NONMULTIMODE_OR_MULTIMODEMASTER(__HANDLE__)                        \
 (( (((__HANDLE__)->Instance) == ADC2)                                         \
  )?                                                                           \
   ((ADC1->CR1 & ADC_CR1_DUALMOD) == RESET)                                    \
   :                                                                           \
   (!RESET)                                                                    \
 )
#else
#define ADC_NONMULTIMODE_OR_MULTIMODEMASTER(__HANDLE__)                        \
  (!RESET)
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
/**
  * @brief Set handle of the other ADC sharing the common multimode settings
  * @param __HANDLE__: ADC handle
  * @param __HANDLE_OTHER_ADC__: other ADC handle
  * @retval None
  */
#define ADC_COMMON_ADC_OTHER(__HANDLE__, __HANDLE_OTHER_ADC__)                 \
  ((__HANDLE_OTHER_ADC__)->Instance = ADC2)

/**
  * @brief Set handle of the ADC slave associated to the ADC master
  * On STM32F1 devices, ADC slave is always ADC2 (this can be different
  * on other STM32 devices)
  * @param __HANDLE_MASTER__: ADC master handle
  * @param __HANDLE_SLAVE__: ADC slave handle
  * @retval None
  */
#define ADC_MULTI_SLAVE(__HANDLE_MASTER__, __HANDLE_SLAVE__)                   \
  ((__HANDLE_SLAVE__)->Instance = ADC2)
       
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

#define IS_ADC_INJECTED_RANK(CHANNEL) (((CHANNEL) == ADC_INJECTED_RANK_1) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_2) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_3) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_4)   )

#define IS_ADC_EXTTRIGINJEC_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_NONE)  || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISING)  )

/** @defgroup ADCEx_injected_nb_conv_verification ADCEx injected nb conv verification
  * @{
  */
#define IS_ADC_INJECTED_NB_CONV(LENGTH)                                        \
  (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)4)))
/**
  * @}
  */

#if defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F101x6) || defined (STM32F101xB) || defined (STM32F102x6) || defined (STM32F102xB) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11)  || \
                                                                                  \
                                 ((REGTRIG) == ADC_SOFTWARE_START)               )
#endif
#if defined (STM32F101xE) || defined (STM32F101xG)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO)   || \
                                                                                  \
                                 ((REGTRIG) == ADC_SOFTWARE_START)               )
#endif
#if defined (STM32F103xE) || defined (STM32F103xG)
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_EXT_IT11)  || \
                                                                                  \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC3)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T5_CC1)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T5_CC3)    || \
                                                                                  \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO)   || \
                                 ((REGTRIG) == ADC_SOFTWARE_START)               )
#endif

#if defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F101x6) || defined (STM32F101xB) || defined (STM32F102x6) || defined (STM32F102xB) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC)
#define IS_ADC_EXTTRIGINJEC(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                                                                           \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)  || \
                                                                                           \
                                      ((REGTRIG) == ADC_INJECTED_SOFTWARE_START)          )
#endif
#if defined (STM32F101xE) || defined (STM32F101xG)
#define IS_ADC_EXTTRIGINJEC(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                                                                           \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC4)   || \
                                                                                           \
                                      ((REGTRIG) == ADC_INJECTED_SOFTWARE_START)          )
#endif
#if defined (STM32F103xE) || defined (STM32F103xG)
#define IS_ADC_EXTTRIGINJEC(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T5_CC4)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                                                                           \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC3)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC2)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T5_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T5_CC4)   || \
                                                                                           \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC4)   || \
                                                                                           \
                                      ((REGTRIG) == ADC_INJECTED_SOFTWARE_START)          )
#endif

#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
#define IS_ADC_MODE(MODE) (((MODE) == ADC_MODE_INDEPENDENT)                || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT_INJECSIMULT)  || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT_ALTERTRIG)    || \
                           ((MODE) == ADC_DUALMODE_INJECSIMULT_INTERLFAST) || \
                           ((MODE) == ADC_DUALMODE_INJECSIMULT_INTERLSLOW) || \
                           ((MODE) == ADC_DUALMODE_INJECSIMULT)            || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT)              || \
                           ((MODE) == ADC_DUALMODE_INTERLFAST)             || \
                           ((MODE) == ADC_DUALMODE_INTERLSLOW)             || \
                           ((MODE) == ADC_DUALMODE_ALTERTRIG)                )
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

/**
  * @}
  */      
   
    

    
    
   
/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADCEx_Exported_Functions
  * @{
  */

/* IO operation functions  *****************************************************/
/** @addtogroup ADCEx_Exported_Functions_Group1
  * @{
  */

/* ADC calibration */
HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc);

/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc);

#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
/* ADC multimode */
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef *hadc); 
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank);
#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
uint32_t                HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef *hadc);
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption) */
void                    HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc);
/**
  * @}
  */


/* Peripheral Control functions ***********************************************/
/** @addtogroup ADCEx_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef       HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc,ADC_InjectionConfTypeDef* sConfigInjected);
#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
HAL_StatusTypeDef       HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode);
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */
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

#endif /* __STM32F1xx_HAL_ADC_EX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
