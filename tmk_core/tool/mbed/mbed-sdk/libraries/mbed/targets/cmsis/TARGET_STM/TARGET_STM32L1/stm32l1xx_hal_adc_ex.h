/**
  ******************************************************************************
  * @file    stm32l1xx_hal_adc_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of ADC HAL Extension module.
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
#ifndef __STM32L1xx_HAL_ADC_EX_H
#define __STM32L1xx_HAL_ADC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"  

/** @addtogroup STM32L1xx_HAL_Driver
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
  *          - For all parameters: ADC disabled
  *          - For all except parameters 'InjectedDiscontinuousConvMode' and 'AutoInjectedConv': ADC enabled without conversion on going on injected group.
  *          - For parameters 'ExternalTrigInjecConv' and 'ExternalTrigInjecConvEdge': ADC enabled, even with conversion on going on injected group.
  */
typedef struct 
{
  uint32_t InjectedChannel;               /*!< Selection of ADC channel to configure
                                               This parameter can be a value of @ref ADC_channels
                                               Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability. */
  uint32_t InjectedRank;                  /*!< Rank in the injected group sequencer
                                               This parameter must be a value of @ref ADCEx_injected_rank
                                               Note: In case of need to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by the new channel setting (or parameter number of conversions can be adjusted) */
  uint32_t InjectedSamplingTime;          /*!< Sampling time value to be set for the selected channel.
                                               Unit: ADC clock cycles
                                               Conversion time is the addition of sampling time and processing time (12 ADC clock cycles at ADC resolution 12 bits, 11 cycles at 10 bits, 9 cycles at 8 bits, 7 cycles at 6 bits).
                                               This parameter can be a value of @ref ADC_sampling_times
                                               Caution: This parameter updates the parameter property of the channel, that can be used into regular and/or injected groups.
                                                        If this same channel has been previously configured in the other group (regular/injected), it will be updated to last setting.
                                               Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                                     sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                                     Refer to device datasheet for timings values, parameters TS_vrefint, TS_temp (values rough order: 4us min). */                          
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
  uint32_t ExternalTrigInjecConvEdge;     /*!< Selects the external trigger edge of injected group.
                                               This parameter can be a value of @ref ADCEx_External_trigger_edge_Injected.
                                               If trigger is set to ADC_INJECTED_SOFTWARE_START, this parameter is discarded.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to 
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */
}ADC_InjectionConfTypeDef; 
/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
   
/** @defgroup ADCEx_Exported_Constants ADCEx Exported Constants
  * @{
  */

/** @defgroup ADCEx_injected_rank ADCEx injected rank
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

/** @defgroup ADCEx_External_trigger_edge_Injected ADCEx External trigger edge Injected
  * @{
  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISING         ((uint32_t)ADC_CR2_JEXTEN_0)
#define ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING        ((uint32_t)ADC_CR2_JEXTEN_1)
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING  ((uint32_t)ADC_CR2_JEXTEN)

#define IS_ADC_EXTTRIGINJEC_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_NONE)         || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISING)       || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING)      || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING)  )
/**
  * @}
  */

/** @defgroup ADCEx_External_trigger_source_Injected ADCEx External trigger source Injected
  * @{
  */
/* External triggers for injected groups of ADC1 */
#define ADC_EXTERNALTRIGINJECCONV_T2_CC1      ADC_EXTERNALTRIGINJEC_T2_CC1
#define ADC_EXTERNALTRIGINJECCONV_T2_TRGO     ADC_EXTERNALTRIGINJEC_T2_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T3_CC4      ADC_EXTERNALTRIGINJEC_T3_CC4
#define ADC_EXTERNALTRIGINJECCONV_T4_TRGO     ADC_EXTERNALTRIGINJEC_T4_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T4_CC1      ADC_EXTERNALTRIGINJEC_T4_CC1
#define ADC_EXTERNALTRIGINJECCONV_T4_CC2      ADC_EXTERNALTRIGINJEC_T4_CC2
#define ADC_EXTERNALTRIGINJECCONV_T4_CC3      ADC_EXTERNALTRIGINJEC_T4_CC3
#define ADC_EXTERNALTRIGINJECCONV_T7_TRGO     ADC_EXTERNALTRIGINJEC_T7_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T9_CC1      ADC_EXTERNALTRIGINJEC_T9_CC1
#define ADC_EXTERNALTRIGINJECCONV_T9_TRGO     ADC_EXTERNALTRIGINJEC_T9_TRGO
#define ADC_EXTERNALTRIGINJECCONV_T10_CC1     ADC_EXTERNALTRIGINJEC_T10_CC1
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15    ADC_EXTERNALTRIGINJEC_EXT_IT15

#define ADC_INJECTED_SOFTWARE_START      ((uint32_t)0x00000010)

#define IS_ADC_EXTTRIGINJEC(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC1)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC2)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC3)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T7_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T9_CC1)   || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T9_TRGO)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_T10_CC1)  || \
                                      ((REGTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15) || \
                                      ((REGTRIG) == ADC_SOFTWARE_START)              )
/**
  * @}
  */

/** @defgroup ADCEx_Internal_HAL_driver_Ext_trig_src_Injected ADCEx Internal HAL driver Ext trig src Injected
  * @{
  */

/* List of external triggers of injected group for ADC1:                      */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC_EXTERNALTRIGINJEC_T9_CC1         ((uint32_t) 0x00000000)
#define ADC_EXTERNALTRIGINJEC_T9_TRGO        ((uint32_t)(                                                         ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJEC_T2_TRGO        ((uint32_t)(                                      ADC_CR2_JEXTSEL_1                   ))
#define ADC_EXTERNALTRIGINJEC_T2_CC1         ((uint32_t)(                                      ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJEC_T3_CC4         ((uint32_t)(                   ADC_CR2_JEXTSEL_2                                      ))
#define ADC_EXTERNALTRIGINJEC_T4_TRGO        ((uint32_t)(                   ADC_CR2_JEXTSEL_2 |                    ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJEC_T4_CC1         ((uint32_t)(                   ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1                   ))
#define ADC_EXTERNALTRIGINJEC_T4_CC2         ((uint32_t)(                   ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJEC_T4_CC3         ((uint32_t)(ADC_CR2_JEXTSEL_3                                                         ))
#define ADC_EXTERNALTRIGINJEC_T10_CC1        ((uint32_t)(ADC_CR2_JEXTSEL_3                                       | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJEC_T7_TRGO        ((uint32_t)(ADC_CR2_JEXTSEL_3                    | ADC_CR2_JEXTSEL_1                   ))
#define ADC_EXTERNALTRIGINJEC_EXT_IT15       ((uint32_t)(ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))

/**
  * @}
  */


/** @defgroup ADCEx_injected_nb_conv_verification ADCEx injected nb conv verification
  * @{
  */
#define IS_ADC_INJECTED_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)4)))
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Macros ADCEx Exported Macros
  * @{
  */
/* Macro for internal HAL driver usage, and possibly can be used into code of */
/* final user.                                                                */

/**
  * @brief Selection of channels bank. 
  * Note: Banks availability depends on devices categories.
  * This macro is intended to change bank selection quickly on the fly,   
  * without going through ADC init structure update and execution of function
  * 'HAL_ADC_Init()'.
  * @param __HANDLE__: ADC handle
  * @param __BANK__: Bank selection. This parameter can be a value of @ref ADC_ChannelsBank.
  * @retval None
  */
#define __HAL_ADC_CHANNELS_BANK(__HANDLE__, __BANK__)                          \
  MODIFY_REG((__HANDLE__)->Instance->CR2, ADC_CR2_CFG, (__BANK__))

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
/**
 * @brief Configures the ADC channels speed.
 * Limited to channels 3, 8, 13 and to devices category Cat.3, Cat.4, Cat.5.
 *  - For ADC_CHANNEL_3: Used as ADC direct channel (fast channel) if OPAMP1 is
 *    in power down mode.
 *  - For ADC_CHANNEL_8: Used as ADC direct channel (fast channel) if OPAMP2 is
 *    in power down mode.
 *  - For ADC_CHANNEL_13: Used as ADC re-routed channel if OPAMP3 is in 
 *    power down mode. Otherwise, channel 13 is connected to OPAMP3 output and 
 *    routed through switches COMP1_SW1 and VCOMP to ADC switch matrix.
 *    (Note: OPAMP3 is available on STM32L1 Cat.4 only).
 * @param __CHANNEL__: ADC channel
 * This parameter can be one of the following values:
 * @arg ADC_CHANNEL_3: Channel 3 is selected.
 * @arg ADC_CHANNEL_8: Channel 8 is selected.
 * @arg ADC_CHANNEL_13: Channel 13 is selected.
 * @retval None
 */
#define __HAL_ADC_CHANNEL_SPEED_FAST(__CHANNEL__)                              \
  ( ( ((__CHANNEL__) == ADC_CHANNEL_3)                                         \
    )?                                                                         \
     (SET_BIT(COMP->CSR, COMP_CSR_FCH3))                                       \
     :                                                                         \
     ( ( ((__CHANNEL__) == ADC_CHANNEL_8)                                      \
       )?                                                                      \
        (SET_BIT(COMP->CSR, COMP_CSR_FCH8))                                    \
        :                                                                      \
        ( ( ((__CHANNEL__) == ADC_CHANNEL_13)                                  \
          )?                                                                   \
           (SET_BIT(COMP->CSR, COMP_CSR_RCH13))                                \
           :                                                                   \
           (SET_BIT(COMP->CSR, 0x00000000))                                    \
        )                                                                      \
     )                                                                         \
  )

#define __HAL_ADC_CHANNEL_SPEED_SLOW(__CHANNEL__)                              \
  ( ( ((__CHANNEL__) == ADC_CHANNEL_3)                                         \
    )?                                                                         \
     (CLEAR_BIT(COMP->CSR, COMP_CSR_FCH3))                                     \
     :                                                                         \
     ( ( ((__CHANNEL__) == ADC_CHANNEL_8)                                      \
       )?                                                                      \
        (CLEAR_BIT(COMP->CSR, COMP_CSR_FCH8))                                  \
        :                                                                      \
        ( ( ((__CHANNEL__) == ADC_CHANNEL_13)                                  \
          )?                                                                   \
           (CLEAR_BIT(COMP->CSR, COMP_CSR_RCH13))                              \
           :                                                                   \
           (SET_BIT(COMP->CSR, 0x00000000))                                    \
        )                                                                      \
     )                                                                         \
  )
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
    
/**
  * @}
  */

/* Private macro ------------------------------------------------------------*/

/** @defgroup ADCEx_Private_Macro ADCEx Private Macro
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/**
  * @brief Set ADC number of ranks into regular channel sequence length.
  * @param _NbrOfConversion_: Regular channel sequence length 
  * @retval None
  */
#define __ADC_SQR1_L(_NbrOfConversion_) (((_NbrOfConversion_) - (uint8_t)1) << POSITION_VAL(ADC_SQR1_L))

/**
  * @brief Set ADC ranks available in register SQR1.
  * Register SQR1 bits availability depends on device category.
  * @param _NbrOfConversion_: Regular channel sequence length 
  * @retval None
  */
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define __ADC_SQR1_SQXX   ADC_SQR1_SQ28 | ADC_SQR1_SQ27 | ADC_SQR1_SQ26 | ADC_SQR1_SQ25
#else
#define __ADC_SQR1_SQXX   ADC_SQR1_SQ27 | ADC_SQR1_SQ26 | ADC_SQR1_SQ25
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @brief Set the ADC's sample time for channel numbers between 30 and 31.
  * Register SMPR0 availability depends on device category. If register is not
  * available on the current device, this macro does nothing.
  * @retval None
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.  
  * @retval None
  */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define __ADC_SMPR0(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * ((_CHANNELNB_) - 30)))
#else
#define __ADC_SMPR0(_SAMPLETIME_, _CHANNELNB_) ((uint32_t)0x00000000)
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
    
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
/**
  * @brief Set the ADC's sample time for channel numbers between 20 and 29.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.
  * @retval None
  */
#define __ADC_SMPR1(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * ((_CHANNELNB_) - 20)))
#else
/**
  * @brief Set the ADC's sample time for channel numbers between 20 and 26.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.
  * @retval None
  */
#define __ADC_SMPR1(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * ((_CHANNELNB_) - 20)))
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @brief Defines the highest channel available in register SMPR1. Channels
  * availability depends on device category:
  * Highest channel in register SMPR1 is channel 26 for devices Cat.1, Cat.2, Cat.3
  * Highest channel in register SMPR1 is channel 29 for devices Cat.4, Cat.5
  * @param None
  * @retval None
  */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define ADC_SMPR1_CHANNEL_MAX   ADC_CHANNEL_29
#else
#define ADC_SMPR1_CHANNEL_MAX   ADC_CHANNEL_26
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
   
/**
  * @brief Set the ADC's sample time for channel numbers between 10 and 18.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.  
  * @retval None
  */
#define __ADC_SMPR2(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * ((_CHANNELNB_) - 10)))

/**
  * @brief Set the ADC's sample time for channel numbers between 0 and 9.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.  
  * @retval None
  */
#define __ADC_SMPR3(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * (_CHANNELNB_)))

/**
  * @brief Set the selected regular channel rank for rank between 1 and 6.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __ADC_SQR5_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (5 * ((_RANKNB_) - 1)))

/**
  * @brief Set the selected regular channel rank for rank between 7 and 12.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __ADC_SQR4_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (5 * ((_RANKNB_) - 7)))

/**
  * @brief Set the selected regular channel rank for rank between 13 and 18.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __ADC_SQR3_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (5 * ((_RANKNB_) - 13)))

/**
  * @brief Set the selected regular channel rank for rank between 19 and 24.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __ADC_SQR2_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (5 * ((_RANKNB_) - 19)))
      
/**
  * @brief Set the selected regular channel rank for rank between 25 and 28.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define __ADC_SQR1_RK(_CHANNELNB_, _RANKNB_) ((_CHANNELNB_) << (5 * ((_RANKNB_) - 25)))
      
/**
  * @brief Set the injected sequence length.
  * @param _JSQR_JL_: Sequence length.
  * @retval None
  */
#define __ADC_JSQR_JL(_JSQR_JL_)   (((_JSQR_JL_) -1) << 20)

/**
  * @brief Set the selected injected Channel rank (channels sequence starting from 4-JL)
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.
  * @param _JSQR_JL_: Sequence length.
  * @retval None
  */
#define __ADC_JSQR_RK(_CHANNELNB_, _RANKNB_, _JSQR_JL_)                        \
    ((_CHANNELNB_) << (5 * ((4 - ((_JSQR_JL_) - (_RANKNB_))) - 1)))

      
/**
  * @brief Enable the ADC DMA continuous request.
  * @param _DMACONTREQ_MODE_: DMA continuous request mode.
  * @retval None
  */
#define __ADC_CR2_DMACONTREQ(_DMACONTREQ_MODE_) ((_DMACONTREQ_MODE_) << POSITION_VAL(ADC_CR2_DDS))

/**
  * @brief Enable ADC continuous conversion mode.
  * @param _CONTINUOUS_MODE_: Continuous mode.
  * @retval None
  */
#define __ADC_CR2_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << POSITION_VAL(ADC_CR2_CONT))

/**
  * @brief Define mask of configuration bits of ADC and regular group in
  * register CR2 (bits of ADC enable, conversion start and injected group are 
  * excluded of this mask).
  * @retval None
  */
#if defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define __ADC_CR2_MASK_ADCINIT()                                               \
  (ADC_CR2_EXTEN | ADC_CR2_EXTSEL | ADC_CR2_ALIGN | ADC_CR2_EOCS | ADC_CR2_DDS | ADC_CR2_DELS | ADC_CR2_CFG | ADC_CR2_CONT)
#else
#define __ADC_CR2_MASK_ADCINIT()                                               \
  (ADC_CR2_EXTEN | ADC_CR2_EXTSEL | ADC_CR2_ALIGN | ADC_CR2_EOCS | ADC_CR2_DDS | ADC_CR2_DELS | ADC_CR2_CONT)
#endif

/**
  * @brief Configures the number of discontinuous conversions for the regular group channels.
  * @param _NBR_DISCONTINUOUS_CONV_: Number of discontinuous conversions.
  * @retval None
  */
#define __ADC_CR1_DISCONTINUOUS_NUM(_NBR_DISCONTINUOUS_CONV_) (((_NBR_DISCONTINUOUS_CONV_) - 1) << POSITION_VAL(ADC_CR1_DISCNUM))
   
/**
  * @brief Enable ADC scan mode to convert multiple ranks with sequencer.
  * @param _SCAN_MODE_: Scan conversion mode.
  * @retval None
  */
#define __ADC_CR1_SCAN(_SCAN_MODE_)                                            \
  ( ( (_SCAN_MODE_) == (ADC_SCAN_ENABLE)                                       \
    )? (ADC_CR1_SCAN) : (0x00000000)                                           \
  )

/**
  * @brief Get the maximum ADC conversion cycles on all channels.
  * Returns the selected sampling time + conversion time (12.5 ADC clock cycles)
  * Approximation of sampling time within 2 ranges, returns the higher value:
  *   below 24 cycles {4 cycles; 9 cycles; 16 cycles; 24 cycles}
  *   between 48 cycles and 384 cycles {48 cycles; 96 cycles; 192 cycles; 384 cycles}
  * Unit: ADC clock cycles
  * @param __HANDLE__: ADC handle
  * @retval ADC conversion cycles on all channels
  */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define __ADC_CONVCYCLES_MAX_RANGE(__HANDLE__)                                                          \
    (( (((__HANDLE__)->Instance->SMPR3 & ADC_SAMPLETIME_ALLCHANNELS_SMPR3BIT2) == RESET)  &&            \
       (((__HANDLE__)->Instance->SMPR2 & ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2) == RESET)  &&            \
       (((__HANDLE__)->Instance->SMPR1 & ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2) == RESET)  &&            \
       (((__HANDLE__)->Instance->SMPR0 & ADC_SAMPLETIME_ALLCHANNELS_SMPR0BIT2) == RESET) ) ?            \
                                                                                                        \
        ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_24CYCLES : ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_384CYCLES  \
     )
#else
#define __ADC_CONVCYCLES_MAX_RANGE(__HANDLE__)                                                          \
    (( (((__HANDLE__)->Instance->SMPR3 & ADC_SAMPLETIME_ALLCHANNELS_SMPR3BIT2) == RESET)  &&            \
       (((__HANDLE__)->Instance->SMPR2 & ADC_SAMPLETIME_ALLCHANNELS_SMPR2BIT2) == RESET)  &&            \
       (((__HANDLE__)->Instance->SMPR1 & ADC_SAMPLETIME_ALLCHANNELS_SMPR1BIT2) == RESET) ) ?            \
                                                                                                        \
        ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_24CYCLES : ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_384CYCLES  \
     )
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @brief Get the ADC clock prescaler from ADC common control register
  * and convert it to its decimal number setting (refer to reference manual)
  * @retval None
  */
#define __ADC_GET_CLOCK_PRESCALER_DECIMAL(__HANDLE__)                          \
    ((0x01) << ((ADC->CCR & ADC_CCR_ADCPRE) >> POSITION_VAL(ADC_CCR_ADCPRE)))

/**
  * @brief Clear register SMPR0.
  * Register SMPR0 availability depends on device category. If register is not
  * available on the current device, this macro performs no action.
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define __ADC_SMPR0_CLEAR(__HANDLE__)                                          \
  (CLEAR_BIT((__HANDLE__)->Instance->SMPR0, (ADC_SMPR0_SMP31 | ADC_SMPR0_SMP30)))
#else
#define __ADC_SMPR0_CLEAR(__HANDLE__) __NOP()
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @brief Clear register CR2.
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define __ADC_CR2_CLEAR(__HANDLE__)                                                                \
  (CLEAR_BIT((__HANDLE__)->Instance->CR2, (ADC_CR2_SWSTART  | ADC_CR2_EXTEN  | ADC_CR2_EXTSEL  |   \
                                           ADC_CR2_JSWSTART | ADC_CR2_JEXTEN | ADC_CR2_JEXTSEL |   \
                                           ADC_CR2_ALIGN    | ADC_CR2_EOCS   | ADC_CR2_DDS     |   \
                                           ADC_CR2_DMA      | ADC_CR2_DELS   | ADC_CR2_CFG     |   \
                                           ADC_CR2_CONT     | ADC_CR2_ADON                      )) \
  )
#else
#define __ADC_CR2_CLEAR(__HANDLE__)                                                                \
  (CLEAR_BIT((__HANDLE__)->Instance->CR2, (ADC_CR2_SWSTART  | ADC_CR2_EXTEN  | ADC_CR2_EXTSEL  |   \
                                           ADC_CR2_JSWSTART | ADC_CR2_JEXTEN | ADC_CR2_JEXTSEL |   \
                                           ADC_CR2_ALIGN    | ADC_CR2_EOCS   | ADC_CR2_DDS     |   \
                                           ADC_CR2_DMA      | ADC_CR2_DELS   |                     \
                                           ADC_CR2_CONT     | ADC_CR2_ADON                      )) \
  )
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
      
/**
  * @brief Set the sampling time of selected channel on register SMPR0
  * Register SMPR0 availability depends on device category. If register is not
  * available on the current device, this macro performs no action.
  * @param __HANDLE__: ADC handle
  * @param _SAMPLETIME_: Sample time parameter.
  * @param __CHANNEL__: Channel number.
  * @retval None
  */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define __ADC_SMPR0_CHANNEL_SET(__HANDLE__, _SAMPLETIME_, __CHANNEL__)         \
    MODIFY_REG((__HANDLE__)->Instance->SMPR0,                                  \
               __ADC_SMPR0(ADC_SMPR0_SMP30, (__CHANNEL__)),                    \
               __ADC_SMPR0((_SAMPLETIME_), (__CHANNEL__))  )
#else
#define __ADC_SMPR0_CHANNEL_SET(__HANDLE__, _SAMPLETIME_, __CHANNEL__) __NOP()
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */     

      
/**
  * @brief Enable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __ADC_ENABLE(__HANDLE__)                                               \
            (__HANDLE__)->Instance->CR2 |= ADC_CR2_ADON
  
/**
  * @brief Disable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __ADC_DISABLE(__HANDLE__)                                              \
            (__HANDLE__)->Instance->CR2 &= ~ADC_CR2_ADON

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

/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank);

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

#endif /* __STM32L1xx_HAL_ADC_EX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
