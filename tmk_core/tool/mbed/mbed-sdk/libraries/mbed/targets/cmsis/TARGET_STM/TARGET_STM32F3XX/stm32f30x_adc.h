/**
  ******************************************************************************
  * @file    stm32f30x_adc.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file contains all the functions prototypes for the ADC firmware 
  *          library.
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
#ifndef __STM32F30x_ADC_H
#define __STM32F30x_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  ADC Init structure definition  
  */
typedef struct
{

  uint32_t ADC_ContinuousConvMode;        /*!< Specifies whether the conversion is performed in
                                               Continuous or Single mode.
                                               This parameter can be set to ENABLE or DISABLE. */
  uint32_t ADC_Resolution;                /*!< Configures the ADC resolution.
                                               This parameter can be a value of @ref ADC_resolution */ 
  uint32_t ADC_ExternalTrigConvEvent;      /*!< Defines the external trigger used to start the analog
                                               to digital conversion of regular channels. This parameter
                                               can be a value of @ref ADC_external_trigger_sources_for_regular_channels_conversion */
  uint32_t ADC_ExternalTrigEventEdge;      /*!< Select the external trigger edge and enable the trigger of a regular group.                                               
                                               This parameter can be a value of 
                                               @ref ADC_external_trigger_edge_for_regular_channels_conversion */
  uint32_t ADC_DataAlign;                 /*!< Specifies whether the ADC data alignment is left or right.
                                               This parameter can be a value of @ref ADC_data_align */
  uint32_t ADC_OverrunMode;               /*!< Specifies the way data overrun are managed.
                                               This parameter can be set to ENABLE or DISABLE. */
  uint32_t ADC_AutoInjMode;               /*!< Enable/disable automatic injected group conversion after
                                               regular group conversion.
                                               This parameter can be set to ENABLE or DISABLE. */
  uint8_t ADC_NbrOfRegChannel;            /*!< Specifies the number of ADC channels that will be converted
                                               using the sequencer for regular channel group.
                                               This parameter must range from 1 to 16. */
}ADC_InitTypeDef;

/**
  * @}
  */
/** 
  * @brief  ADC Init structure definition  
  */
typedef struct
{

   uint32_t ADC_ExternalTrigInjecConvEvent;     /*!< Defines the external trigger used to start the analog
                                                     to digital conversion of injected channels. This parameter
                                                     can be a value of @ref ADC_external_trigger_sources_for_Injected_channels_conversion */
  uint32_t ADC_ExternalTrigInjecEventEdge;     /*!< Select the external trigger edge and enable the trigger of an injected group. 
                                                    This parameter can be a value of 
                                                    @ref ADC_external_trigger_edge_for_Injected_channels_conversion */
  uint8_t ADC_NbrOfInjecChannel;               /*!< Specifies the number of ADC channels that will be converted
                                                    using the sequencer for injected channel group.
                                                    This parameter must range from 1 to 4. */ 
  uint32_t ADC_InjecSequence1; 
  uint32_t ADC_InjecSequence2;
  uint32_t ADC_InjecSequence3;
  uint32_t ADC_InjecSequence4;                                            
}ADC_InjectedInitTypeDef;

/**
  * @}
  */
typedef struct 
{
  uint32_t ADC_Mode;                      /*!< Configures the ADC to operate in 
                                               independent or multi mode. 
                                               This parameter can be a value of @ref ADC_mode */                                              
  uint32_t ADC_Clock;                    /*!< Select the clock of the ADC. The clock is common for both master 
                                              and slave ADCs.
                                              This parameter can be a value of @ref ADC_Clock */
  uint32_t ADC_DMAAccessMode;             /*!< Configures the Direct memory access mode for multi ADC mode.                                               
                                               This parameter can be a value of 
                                               @ref ADC_Direct_memory_access_mode_for_multi_mode */
  uint32_t ADC_DMAMode;                  /*!< Configures the DMA mode for ADC.                                             
                                              This parameter can be a value of @ref ADC_DMA_Mode_definition */
  uint8_t ADC_TwoSamplingDelay;          /*!< Configures the Delay between 2 sampling phases.
                                               This parameter can be a value between  0x0 and 0xF  */
  
}ADC_CommonInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */ 

#define IS_ADC_ALL_PERIPH(PERIPH) (((PERIPH) == ADC1) || \
                                   ((PERIPH) == ADC2) || \
                                   ((PERIPH) == ADC3) || \
                                   ((PERIPH) == ADC4))

#define IS_ADC_DMA_PERIPH(PERIPH) (((PERIPH) == ADC1) || \
                                   ((PERIPH) == ADC2) || \
                                   ((PERIPH) == ADC3) || \
                                   ((PERIPH) == ADC4))

/** @defgroup ADC_ContinuousConvMode 
  * @{
  */
#define ADC_ContinuousConvMode_Enable	 ((uint32_t)0x00002000)  /*!<  ADC continuous conversion mode enable */
#define ADC_ContinuousConvMode_Disable	 ((uint32_t)0x00000000)  /*!<  ADC continuous conversion mode disable */
#define IS_ADC_CONVMODE(MODE) (((MODE) == ADC_ContinuousConvMode_Enable) || \
                               ((MODE) == ADC_ContinuousConvMode_Disable))
/**
  * @}
  */
/** @defgroup ADC_OverunMode 
  * @{
  */
#define ADC_OverrunMode_Enable	 ((uint32_t)0x00001000)  /*!<  ADC Overrun Mode enable */
#define ADC_OverrunMode_Disable	 ((uint32_t)0x00000000)  /*!<  ADC Overrun Mode disable */
#define IS_ADC_OVRUNMODE(MODE) (((MODE) == ADC_OverrunMode_Enable) || \
                                ((MODE) == ADC_OverrunMode_Disable))
/**
  * @}
  */
/** @defgroup ADC_AutoInjecMode 
  * @{
  */
#define ADC_AutoInjec_Enable	 ((uint32_t)0x02000000)  /*!<  ADC Auto injected Mode enable */
#define ADC_AutoInjec_Disable	 ((uint32_t)0x00000000)  /*!<  ADC Auto injected Mode disable */
#define IS_ADC_AUTOINJECMODE(MODE) (((MODE) == ADC_AutoInjec_Enable) || \
                                    ((MODE) == ADC_AutoInjec_Disable))
/**
  * @}
  */
/** @defgroup ADC_resolution 
  * @{
  */ 
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)  /*!<  ADC 12-bit resolution */
#define ADC_Resolution_10b                         ((uint32_t)0x00000008)  /*!<  ADC 10-bit resolution */
#define ADC_Resolution_8b                          ((uint32_t)0x00000010)  /*!<  ADC 8-bit resolution */
#define ADC_Resolution_6b                          ((uint32_t)0x00000018)  /*!<  ADC 6-bit resolution */
#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) || \
                                       ((RESOLUTION) == ADC_Resolution_10b) || \
                                       ((RESOLUTION) == ADC_Resolution_8b) || \
                                       ((RESOLUTION) == ADC_Resolution_6b))
                                      
/**
  * @}
  */ 
  
  
/** @defgroup ADC_external_trigger_edge_for_regular_channels_conversion 
  * @{
  */
#define ADC_ExternalTrigEventEdge_None            ((uint16_t)0x0000)     /*!<  ADC No external trigger for regular conversion */
#define ADC_ExternalTrigEventEdge_RisingEdge      ((uint16_t)0x0400)     /*!<  ADC external trigger rising edge for regular conversion */
#define ADC_ExternalTrigEventEdge_FallingEdge     ((uint16_t)0x0800)     /*!<  ADC ADC external trigger falling edge for regular conversion */
#define ADC_ExternalTrigEventEdge_BothEdge        ((uint16_t)0x0C00)     /*!<  ADC ADC external trigger both edges for regular conversion */

#define IS_EXTERNALTRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigEventEdge_None) || \
                                    ((EDGE) == ADC_ExternalTrigEventEdge_RisingEdge) || \
                                    ((EDGE) == ADC_ExternalTrigEventEdge_FallingEdge) || \
                                    ((EDGE) == ADC_ExternalTrigEventEdge_BothEdge))
  
/**
  * @}
  */
   
/** @defgroup ADC_external_trigger_edge_for_Injected_channels_conversion 
  * @{
  */     
#define ADC_ExternalTrigInjecEventEdge_None		     ((uint16_t)0x0000)    /*!<  ADC No external trigger for regular conversion */
#define ADC_ExternalTrigInjecEventEdge_RisingEdge	 ((uint16_t)0x0040)    /*!<  ADC external trigger rising edge for injected conversion */
#define ADC_ExternalTrigInjecEventEdge_FallingEdge	 ((uint16_t)0x0080)  /*!<  ADC external trigger falling edge for injected conversion */
#define ADC_ExternalTrigInjecEventEdge_BothEdge	     ((uint16_t)0x00C0)  /*!<  ADC external trigger both edges for injected conversion */

#define IS_EXTERNALTRIGINJ_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigInjecEventEdge_None) || \
                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_RisingEdge) || \
                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_FallingEdge) || \
                                       ((EDGE) == ADC_ExternalTrigInjecEventEdge_BothEdge))
  
/** @defgroup ADC_external_trigger_sources_for_regular_channels_conversion 
  * @{
  */
#define ADC_ExternalTrigConvEvent_0              ((uint16_t)0x0000)   /*!<  ADC external trigger event 0 */
#define ADC_ExternalTrigConvEvent_1              ((uint16_t)0x0040)   /*!<  ADC external trigger event 1 */
#define ADC_ExternalTrigConvEvent_2              ((uint16_t)0x0080)   /*!<  ADC external trigger event 2 */
#define ADC_ExternalTrigConvEvent_3              ((uint16_t)0x00C0)   /*!<  ADC external trigger event 3 */
#define ADC_ExternalTrigConvEvent_4              ((uint16_t)0x0100)   /*!<  ADC external trigger event 4 */
#define ADC_ExternalTrigConvEvent_5              ((uint16_t)0x0140)   /*!<  ADC external trigger event 5 */
#define ADC_ExternalTrigConvEvent_6              ((uint16_t)0x0180)   /*!<  ADC external trigger event 6 */
#define ADC_ExternalTrigConvEvent_7              ((uint16_t)0x01C0)   /*!<  ADC external trigger event 7 */
#define ADC_ExternalTrigConvEvent_8              ((uint16_t)0x0200)   /*!<  ADC external trigger event 8 */
#define ADC_ExternalTrigConvEvent_9              ((uint16_t)0x0240)   /*!<  ADC external trigger event 9 */
#define ADC_ExternalTrigConvEvent_10             ((uint16_t)0x0280)   /*!<  ADC external trigger event 10 */
#define ADC_ExternalTrigConvEvent_11             ((uint16_t)0x02C0)   /*!<  ADC external trigger event 11 */
#define ADC_ExternalTrigConvEvent_12             ((uint16_t)0x0300)   /*!<  ADC external trigger event 12 */
#define ADC_ExternalTrigConvEvent_13             ((uint16_t)0x0340)   /*!<  ADC external trigger event 13 */
#define ADC_ExternalTrigConvEvent_14             ((uint16_t)0x0380)   /*!<  ADC external trigger event 14 */
#define ADC_ExternalTrigConvEvent_15             ((uint16_t)0x03C0)   /*!<  ADC external trigger event 15 */

#define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_ExternalTrigConvEvent_0) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_5) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_6) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_7) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_8) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_9) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_10) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_11) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_12) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_13) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_14) || \
                                  ((REGTRIG) == ADC_ExternalTrigConvEvent_15))

/**
  * @}
  */

/** @defgroup ADC_external_trigger_sources_for_Injected_channels_conversion 
  * @{
  */
        
#define ADC_ExternalTrigInjecConvEvent_0              ((uint16_t)0x0000)  /*!<  ADC external trigger for injected conversion event 0 */
#define ADC_ExternalTrigInjecConvEvent_1              ((uint16_t)0x0004)  /*!<  ADC external trigger for injected conversion event 1 */
#define ADC_ExternalTrigInjecConvEvent_2              ((uint16_t)0x0008)  /*!<  ADC external trigger for injected conversion event 2 */
#define ADC_ExternalTrigInjecConvEvent_3              ((uint16_t)0x000C)  /*!<  ADC external trigger for injected conversion event 3 */
#define ADC_ExternalTrigInjecConvEvent_4              ((uint16_t)0x0010)  /*!<  ADC external trigger for injected conversion event 4 */
#define ADC_ExternalTrigInjecConvEvent_5              ((uint16_t)0x0014)  /*!<  ADC external trigger for injected conversion event 5 */
#define ADC_ExternalTrigInjecConvEvent_6              ((uint16_t)0x0018)  /*!<  ADC external trigger for injected conversion event 6 */
#define ADC_ExternalTrigInjecConvEvent_7              ((uint16_t)0x001C)  /*!<  ADC external trigger for injected conversion event 7 */
#define ADC_ExternalTrigInjecConvEvent_8              ((uint16_t)0x0020)  /*!<  ADC external trigger for injected conversion event 8 */
#define ADC_ExternalTrigInjecConvEvent_9              ((uint16_t)0x0024)  /*!<  ADC external trigger for injected conversion event 9 */
#define ADC_ExternalTrigInjecConvEvent_10             ((uint16_t)0x0028)  /*!<  ADC external trigger for injected conversion event 10 */
#define ADC_ExternalTrigInjecConvEvent_11             ((uint16_t)0x002C)  /*!<  ADC external trigger for injected conversion event 11 */
#define ADC_ExternalTrigInjecConvEvent_12             ((uint16_t)0x0030)  /*!<  ADC external trigger for injected conversion event 12 */
#define ADC_ExternalTrigInjecConvEvent_13             ((uint16_t)0x0034)  /*!<  ADC external trigger for injected conversion event 13 */
#define ADC_ExternalTrigInjecConvEvent_14             ((uint16_t)0x0038)  /*!<  ADC external trigger for injected conversion event 14 */
#define ADC_ExternalTrigInjecConvEvent_15             ((uint16_t)0x003C)  /*!<  ADC external trigger for injected conversion event 15 */

#define IS_ADC_EXT_INJEC_TRIG(INJTRIG) (((INJTRIG) == ADC_ExternalTrigInjecConvEvent_0) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_1) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_2) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_3) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_5) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_6) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_7) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_8) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_9) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_10) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_11) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_12) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_13) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_14) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConvEvent_15))
/**
  * @}
  */
/** @defgroup ADC_data_align 
  * @{
  */

#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)  /*!<  ADC Data alignment right */
#define ADC_DataAlign_Left                         ((uint32_t)0x00000020)  /*!<  ADC Data alignment left */
#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */

/** @defgroup ADC_channels 
  * @{
  */

#define ADC_Channel_1                               ((uint8_t)0x01)    /*!<  ADC Channel 1 */
#define ADC_Channel_2                               ((uint8_t)0x02)    /*!<  ADC Channel 2 */
#define ADC_Channel_3                               ((uint8_t)0x03)    /*!<  ADC Channel 3 */
#define ADC_Channel_4                               ((uint8_t)0x04)    /*!<  ADC Channel 4 */
#define ADC_Channel_5                               ((uint8_t)0x05)    /*!<  ADC Channel 5 */
#define ADC_Channel_6                               ((uint8_t)0x06)    /*!<  ADC Channel 6 */
#define ADC_Channel_7                               ((uint8_t)0x07)    /*!<  ADC Channel 7 */
#define ADC_Channel_8                               ((uint8_t)0x08)    /*!<  ADC Channel 8 */
#define ADC_Channel_9                               ((uint8_t)0x09)    /*!<  ADC Channel 9 */
#define ADC_Channel_10                              ((uint8_t)0x0A)    /*!<  ADC Channel 10 */
#define ADC_Channel_11                              ((uint8_t)0x0B)    /*!<  ADC Channel 11 */
#define ADC_Channel_12                              ((uint8_t)0x0C)    /*!<  ADC Channel 12 */
#define ADC_Channel_13                              ((uint8_t)0x0D)    /*!<  ADC Channel 13 */
#define ADC_Channel_14                              ((uint8_t)0x0E)    /*!<  ADC Channel 14 */
#define ADC_Channel_15                              ((uint8_t)0x0F)    /*!<  ADC Channel 15 */
#define ADC_Channel_16                              ((uint8_t)0x10)    /*!<  ADC Channel 16 */
#define ADC_Channel_17                              ((uint8_t)0x11)    /*!<  ADC Channel 17 */
#define ADC_Channel_18                              ((uint8_t)0x12)    /*!<  ADC Channel 18 */

#define ADC_Channel_TempSensor                      ((uint8_t)ADC_Channel_16)
#define ADC_Channel_Vrefint                         ((uint8_t)ADC_Channel_18)
#define ADC_Channel_Vbat                            ((uint8_t)ADC_Channel_17)

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_1)  || \
                                 ((CHANNEL) == ADC_Channel_2)  || \
                                 ((CHANNEL) == ADC_Channel_3)  || \
                                 ((CHANNEL) == ADC_Channel_4)  || \
                                 ((CHANNEL) == ADC_Channel_5)  || \
                                 ((CHANNEL) == ADC_Channel_6)  || \
                                 ((CHANNEL) == ADC_Channel_7)  || \
                                 ((CHANNEL) == ADC_Channel_8)  || \
                                 ((CHANNEL) == ADC_Channel_9)  || \
                                 ((CHANNEL) == ADC_Channel_10) || \
                                 ((CHANNEL) == ADC_Channel_11) || \
                                 ((CHANNEL) == ADC_Channel_12) || \
                                 ((CHANNEL) == ADC_Channel_13) || \
                                 ((CHANNEL) == ADC_Channel_14) || \
                                 ((CHANNEL) == ADC_Channel_15) || \
                                 ((CHANNEL) == ADC_Channel_16) || \
                                 ((CHANNEL) == ADC_Channel_17) || \
                                 ((CHANNEL) == ADC_Channel_18))
#define IS_ADC_DIFFCHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_1)  || \
                                     ((CHANNEL) == ADC_Channel_2)  || \
                                     ((CHANNEL) == ADC_Channel_3)  || \
                                     ((CHANNEL) == ADC_Channel_4)  || \
                                     ((CHANNEL) == ADC_Channel_5)  || \
                                     ((CHANNEL) == ADC_Channel_6)  || \
                                     ((CHANNEL) == ADC_Channel_7)  || \
                                     ((CHANNEL) == ADC_Channel_8)  || \
                                     ((CHANNEL) == ADC_Channel_9)  || \
                                     ((CHANNEL) == ADC_Channel_10) || \
                                     ((CHANNEL) == ADC_Channel_11) || \
                                     ((CHANNEL) == ADC_Channel_12) || \
                                     ((CHANNEL) == ADC_Channel_13) || \
                                     ((CHANNEL) == ADC_Channel_14))
/**
  * @}
  */

/** @defgroup ADC_mode 
  * @{
  */    
#define ADC_Mode_Independent                  ((uint32_t)0x00000000) /*!<  ADC independent mode */
#define ADC_Mode_CombRegSimulInjSimul         ((uint32_t)0x00000001) /*!<  ADC multi ADC mode: Combined Regular simultaneous injected simultaneous mode */
#define ADC_Mode_CombRegSimulAltTrig          ((uint32_t)0x00000002) /*!<  ADC multi ADC mode: Combined Regular simultaneous Alternate trigger mode */
#define ADC_Mode_InjSimul                     ((uint32_t)0x00000005) /*!<  ADC multi ADC mode: Injected simultaneous mode */
#define ADC_Mode_RegSimul                     ((uint32_t)0x00000006) /*!<  ADC multi ADC mode: Regular simultaneous mode */
#define ADC_Mode_Interleave                   ((uint32_t)0x00000007) /*!<  ADC multi ADC mode: Interleave mode */
#define ADC_Mode_AltTrig                      ((uint32_t)0x00000009) /*!<  ADC multi ADC mode: Alternate Trigger mode */

#define IS_ADC_MODE(MODE) (((MODE) == ADC_Mode_Independent) || \
                           ((MODE) == ADC_Mode_CombRegSimulInjSimul) || \
                           ((MODE) == ADC_Mode_CombRegSimulAltTrig) || \
                           ((MODE) == ADC_Mode_InjSimul) || \
                           ((MODE) == ADC_Mode_RegSimul) || \
                           ((MODE) == ADC_Mode_Interleave) || \
                           ((MODE) == ADC_Mode_AltTrig))
                                     
/**
  * @}
  */

/** @defgroup ADC_Clock 
  * @{
  */ 
#define ADC_Clock_AsynClkMode                  ((uint32_t)0x00000000)   /*!< ADC Asynchronous clock mode */
#define ADC_Clock_SynClkModeDiv1               ((uint32_t)0x00010000)   /*!< Synchronous clock mode divided by 1 */
#define ADC_Clock_SynClkModeDiv2               ((uint32_t)0x00020000)   /*!<  Synchronous clock mode divided by 2 */
#define ADC_Clock_SynClkModeDiv4               ((uint32_t)0x00030000)   /*!<  Synchronous clock mode divided by 4 */
#define IS_ADC_CLOCKMODE(CLOCK) (((CLOCK) == ADC_Clock_AsynClkMode) ||\
				((CLOCK) == ADC_Clock_SynClkModeDiv1) ||\
				((CLOCK) == ADC_Clock_SynClkModeDiv2)||\
				((CLOCK) == ADC_Clock_SynClkModeDiv4))
/**
  * @}
  */
/** @defgroup ADC_Direct_memory_access_mode_for_multi_mode 
  * @{
  */ 
#define ADC_DMAAccessMode_Disabled      ((uint32_t)0x00000000)     /*!<  DMA mode disabled */
#define ADC_DMAAccessMode_1             ((uint32_t)0x00008000)     /*!<  DMA mode enabled for 12 and 10-bit resolution (6 bit) */
#define ADC_DMAAccessMode_2             ((uint32_t)0x0000C000)     /*!<  DMA mode enabled for 8 and 6-bit resolution (8bit) */
#define IS_ADC_DMA_ACCESS_MODE(MODE) (((MODE) == ADC_DMAAccessMode_Disabled) || \
                                      ((MODE) == ADC_DMAAccessMode_1) || \
                                      ((MODE) == ADC_DMAAccessMode_2))
                                     
/**
  * @}
  */
/** @defgroup ADC_sampling_time 
  * @{
  */

#define ADC_SampleTime_1Cycles5                    ((uint8_t)0x00)   /*!<  ADC sampling time 1.5 cycle */
#define ADC_SampleTime_2Cycles5                    ((uint8_t)0x01)   /*!<  ADC sampling time 2.5 cycles */
#define ADC_SampleTime_4Cycles5                    ((uint8_t)0x02)   /*!<  ADC sampling time 4.5 cycles */
#define ADC_SampleTime_7Cycles5                    ((uint8_t)0x03)   /*!<  ADC sampling time 7.5 cycles */
#define ADC_SampleTime_19Cycles5                   ((uint8_t)0x04)   /*!<  ADC sampling time 19.5 cycles */
#define ADC_SampleTime_61Cycles5                   ((uint8_t)0x05)   /*!<  ADC sampling time 61.5 cycles */
#define ADC_SampleTime_181Cycles5                  ((uint8_t)0x06)   /*!<  ADC sampling time 181.5 cycles */
#define ADC_SampleTime_601Cycles5                  ((uint8_t)0x07)   /*!<  ADC sampling time 601.5 cycles */
#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SampleTime_1Cycles5) || \
                                  ((TIME) == ADC_SampleTime_2Cycles5) || \
                                  ((TIME) == ADC_SampleTime_4Cycles5) || \
                                  ((TIME) == ADC_SampleTime_7Cycles5) || \
                                  ((TIME) == ADC_SampleTime_19Cycles5) || \
                                  ((TIME) == ADC_SampleTime_61Cycles5) || \
                                  ((TIME) == ADC_SampleTime_181Cycles5) || \
                                  ((TIME) == ADC_SampleTime_601Cycles5))
/**
  * @}
  */

/** @defgroup ADC_injected_Channel_selection 
  * @{
  */

#define ADC_InjectedChannel_1                       ADC_Channel_1        /*!<  ADC Injected channel 1 */
#define ADC_InjectedChannel_2                       ADC_Channel_2        /*!<  ADC Injected channel 2 */
#define ADC_InjectedChannel_3                       ADC_Channel_3        /*!<  ADC Injected channel 3 */
#define ADC_InjectedChannel_4                       ADC_Channel_4        /*!<  ADC Injected channel 4 */
#define ADC_InjectedChannel_5                       ADC_Channel_5        /*!<  ADC Injected channel 5 */
#define ADC_InjectedChannel_6                       ADC_Channel_6        /*!<  ADC Injected channel 6 */
#define ADC_InjectedChannel_7                       ADC_Channel_7        /*!<  ADC Injected channel 7 */
#define ADC_InjectedChannel_8                       ADC_Channel_8        /*!<  ADC Injected channel 8 */
#define ADC_InjectedChannel_9                       ADC_Channel_9        /*!<  ADC Injected channel 9 */
#define ADC_InjectedChannel_10                      ADC_Channel_10       /*!<  ADC Injected channel 10 */
#define ADC_InjectedChannel_11                      ADC_Channel_11       /*!<  ADC Injected channel 11 */
#define ADC_InjectedChannel_12                      ADC_Channel_12       /*!<  ADC Injected channel 12 */
#define ADC_InjectedChannel_13                      ADC_Channel_13       /*!<  ADC Injected channel 13 */
#define ADC_InjectedChannel_14                      ADC_Channel_14       /*!<  ADC Injected channel 14 */
#define ADC_InjectedChannel_15                      ADC_Channel_15       /*!<  ADC Injected channel 15 */
#define ADC_InjectedChannel_16                      ADC_Channel_16       /*!<  ADC Injected channel 16 */
#define ADC_InjectedChannel_17                      ADC_Channel_17       /*!<  ADC Injected channel 17 */
#define ADC_InjectedChannel_18                      ADC_Channel_18       /*!<  ADC Injected channel 18 */

#define IS_ADC_INJECTED_CHANNEL(CHANNEL) (((CHANNEL) == ADC_InjectedChannel_1) || \
                                          ((CHANNEL) == ADC_InjectedChannel_2) || \
                                          ((CHANNEL) == ADC_InjectedChannel_3) || \
                                          ((CHANNEL) == ADC_InjectedChannel_4) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_5) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_6) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_7) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_8) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_9) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_10) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_11) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_12) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_13) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_14) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_15) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_16) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_17) ||\
                                          ((CHANNEL) == ADC_InjectedChannel_18))
/**
  * @}
  */

/** @defgroup ADC_injected_Sequence_selection 
  * @{
  */

#define ADC_InjectedSequence_1                       ADC_Channel_1        /*!<  ADC Injected sequence 1 */
#define ADC_InjectedSequence_2                       ADC_Channel_2        /*!<  ADC Injected sequence 2 */
#define ADC_InjectedSequence_3                       ADC_Channel_3        /*!<  ADC Injected sequence 3 */
#define ADC_InjectedSequence_4                       ADC_Channel_4        /*!<  ADC Injected sequence 4 */
#define IS_ADC_INJECTED_SEQUENCE(SEQUENCE) (((SEQUENCE) == ADC_InjectedSequence_1) || \
                                            ((SEQUENCE) == ADC_InjectedSequence_2) || \
                                            ((SEQUENCE) == ADC_InjectedSequence_3) || \
                                            ((SEQUENCE) == ADC_InjectedSequence_4))
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_selection 
  * @{
  */

#define ADC_AnalogWatchdog_SingleRegEnable         ((uint32_t)0x00C00000)    /*!<  ADC Analog watchdog single regular mode */
#define ADC_AnalogWatchdog_SingleInjecEnable       ((uint32_t)0x01400000)    /*!<  ADC Analog watchdog single injected mode */
#define ADC_AnalogWatchdog_SingleRegOrInjecEnable  ((uint32_t)0x01C00000)    /*!<  ADC Analog watchdog single regular or injected mode */
#define ADC_AnalogWatchdog_AllRegEnable            ((uint32_t)0x00800000)    /*!<  ADC Analog watchdog all regular mode */
#define ADC_AnalogWatchdog_AllInjecEnable          ((uint32_t)0x01000000)    /*!<  ADC Analog watchdog all injected mode */
#define ADC_AnalogWatchdog_AllRegAllInjecEnable    ((uint32_t)0x01800000)    /*!<  ADC Analog watchdog all regular and all injected mode */
#define ADC_AnalogWatchdog_None                    ((uint32_t)0x00000000)    /*!<  ADC Analog watchdog off */

#define IS_ADC_ANALOG_WATCHDOG(WATCHDOG) (((WATCHDOG) == ADC_AnalogWatchdog_SingleRegEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleRegOrInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegAllInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_None))
/**
  * @}
  */

/** @defgroup ADC_Calibration_Mode_definition 
  * @{
  */
#define ADC_CalibrationMode_Single         ((uint32_t)0x00000000)   /*!<  ADC Calibration for single ended channel */
#define ADC_CalibrationMode_Differential   ((uint32_t)0x40000000)   /*!<  ADC Calibration for differential channel */

#define IS_ADC_CALIBRATION_MODE(MODE) (((MODE) == ADC_CalibrationMode_Single) ||((MODE) == ADC_CalibrationMode_Differential))

/**
  * @}
  */

/** @defgroup ADC_DMA_Mode_definition 
  * @{
  */
#define ADC_DMAMode_OneShot	   ((uint32_t)0x00000000)   /*!<  ADC DMA Oneshot mode */
#define ADC_DMAMode_Circular   ((uint32_t)0x00000002)   /*!<  ADC DMA circular mode */

#define IS_ADC_DMA_MODE(MODE) (((MODE) == ADC_DMAMode_OneShot) || ((MODE) == ADC_DMAMode_Circular))
/**
  * @}
  */

/** @defgroup ADC_interrupts_definition 
  * @{
  */

#define ADC_IT_RDY           ((uint16_t)0x0001)  /*!< ADC Ready (ADRDY) interrupt source */
#define ADC_IT_EOSMP         ((uint16_t)0x0002)  /*!< ADC End of Sampling interrupt source */
#define ADC_IT_EOC           ((uint16_t)0x0004)  /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_EOS           ((uint16_t)0x0008)  /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IT_OVR           ((uint16_t)0x0010)  /*!< ADC overrun interrupt source */
#define ADC_IT_JEOC          ((uint16_t)0x0020)  /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IT_JEOS          ((uint16_t)0x0040)  /*!< ADC End of Injected sequence of Conversions interrupt source */
#define ADC_IT_AWD1          ((uint16_t)0x0080)  /*!< ADC Analog watchdog 1 interrupt source */
#define ADC_IT_AWD2          ((uint16_t)0x0100)  /*!< ADC Analog watchdog 2 interrupt source */
#define ADC_IT_AWD3          ((uint16_t)0x0200)  /*!< ADC Analog watchdog 3 interrupt source */
#define ADC_IT_JQOVF         ((uint16_t)0x0400)  /*!< ADC Injected Context Queue Overflow interrupt source */


#define IS_ADC_IT(IT) ((((IT) & (uint16_t)0xF800) == 0x0000) && ((IT) != 0x0000))

#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_RDY) || ((IT) == ADC_IT_EOSMP) || \
                           ((IT) == ADC_IT_EOC) || ((IT) == ADC_IT_EOS) || \
                           ((IT) == ADC_IT_OVR) || ((IT) == ADC_IT_EOS) || \
                           ((IT) == ADC_IT_JEOS) || ((IT) == ADC_IT_AWD1) || \
                           ((IT) == ADC_IT_AWD2) || ((IT) == ADC_IT_AWD3) || \
                           ((IT) == ADC_IT_JQOVF))
/**
  * @}
  */

/** @defgroup ADC_flags_definition 
  * @{
  */
  
#define ADC_FLAG_RDY           ((uint16_t)0x0001)  /*!< ADC Ready (ADRDY) flag */
#define ADC_FLAG_EOSMP         ((uint16_t)0x0002)  /*!< ADC End of Sampling flag */
#define ADC_FLAG_EOC           ((uint16_t)0x0004)  /*!< ADC End of Regular Conversion flag */
#define ADC_FLAG_EOS           ((uint16_t)0x0008)  /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_FLAG_OVR           ((uint16_t)0x0010)  /*!< ADC overrun flag */
#define ADC_FLAG_JEOC          ((uint16_t)0x0020)  /*!< ADC End of Injected Conversion flag */
#define ADC_FLAG_JEOS          ((uint16_t)0x0040)  /*!< ADC End of Injected sequence of Conversions flag */
#define ADC_FLAG_AWD1          ((uint16_t)0x0080)  /*!< ADC Analog watchdog 1 flag */
#define ADC_FLAG_AWD2          ((uint16_t)0x0100)  /*!< ADC Analog watchdog 2 flag */
#define ADC_FLAG_AWD3          ((uint16_t)0x0200)  /*!< ADC Analog watchdog 3 flag */
#define ADC_FLAG_JQOVF         ((uint16_t)0x0400)  /*!< ADC Injected Context Queue Overflow flag */

#define IS_ADC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xF800) == 0x0000) && ((FLAG) != 0x0000))
#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_RDY) || ((FLAG) == ADC_FLAG_EOSMP) || \
                               ((FLAG) == ADC_FLAG_EOC) || ((FLAG) == ADC_FLAG_EOS) || \
                               ((FLAG) == ADC_FLAG_OVR) || ((FLAG) == ADC_FLAG_JEOC) || \
                               ((FLAG) == ADC_FLAG_JEOS) || ((FLAG) == ADC_FLAG_AWD1) || \
                               ((FLAG) == ADC_FLAG_AWD2) || ((FLAG) == ADC_FLAG_AWD3) || \
                               ((FLAG) == ADC_FLAG_JQOVF))
/**
  * @}
  */

/** @defgroup ADC_Common_flags_definition 
  * @{
  */
  
#define ADC_FLAG_MSTRDY           ((uint32_t)0x00000001)  /*!< ADC Master Ready (ADRDY) flag */
#define ADC_FLAG_MSTEOSMP         ((uint32_t)0x00000002)  /*!< ADC Master End of Sampling flag */
#define ADC_FLAG_MSTEOC           ((uint32_t)0x00000004)  /*!< ADC Master End of Regular Conversion flag */
#define ADC_FLAG_MSTEOS           ((uint32_t)0x00000008)  /*!< ADC Master End of Regular sequence of Conversions flag */
#define ADC_FLAG_MSTOVR           ((uint32_t)0x00000010)  /*!< ADC Master overrun flag */
#define ADC_FLAG_MSTJEOC          ((uint32_t)0x00000020)  /*!< ADC Master End of Injected Conversion flag */
#define ADC_FLAG_MSTJEOS          ((uint32_t)0x00000040)  /*!< ADC Master End of Injected sequence of Conversions flag */
#define ADC_FLAG_MSTAWD1          ((uint32_t)0x00000080)  /*!< ADC Master Analog watchdog 1 flag */
#define ADC_FLAG_MSTAWD2          ((uint32_t)0x00000100)  /*!< ADC Master Analog watchdog 2 flag */
#define ADC_FLAG_MSTAWD3          ((uint32_t)0x00000200)  /*!< ADC Master Analog watchdog 3 flag */
#define ADC_FLAG_MSTJQOVF         ((uint32_t)0x00000400)  /*!< ADC Master Injected Context Queue Overflow flag */

#define ADC_FLAG_SLVRDY           ((uint32_t)0x00010000)  /*!< ADC Slave Ready (ADRDY) flag */
#define ADC_FLAG_SLVEOSMP         ((uint32_t)0x00020000)  /*!< ADC Slave End of Sampling flag */
#define ADC_FLAG_SLVEOC           ((uint32_t)0x00040000)  /*!< ADC Slave End of Regular Conversion flag */
#define ADC_FLAG_SLVEOS           ((uint32_t)0x00080000)  /*!< ADC Slave End of Regular sequence of Conversions flag */
#define ADC_FLAG_SLVOVR           ((uint32_t)0x00100000)  /*!< ADC Slave overrun flag */
#define ADC_FLAG_SLVJEOC          ((uint32_t)0x00200000)  /*!< ADC Slave End of Injected Conversion flag */
#define ADC_FLAG_SLVJEOS          ((uint32_t)0x00400000)  /*!< ADC Slave End of Injected sequence of Conversions flag */
#define ADC_FLAG_SLVAWD1          ((uint32_t)0x00800000)  /*!< ADC Slave Analog watchdog 1 flag */
#define ADC_FLAG_SLVAWD2          ((uint32_t)0x01000000)  /*!< ADC Slave Analog watchdog 2 flag */
#define ADC_FLAG_SLVAWD3          ((uint32_t)0x02000000)  /*!< ADC Slave Analog watchdog 3 flag */
#define ADC_FLAG_SLVJQOVF         ((uint32_t)0x04000000)  /*!< ADC Slave Injected Context Queue Overflow flag */

#define IS_ADC_CLEAR_COMMONFLAG(FLAG) ((((FLAG) & (uint32_t)0xF800F800) == 0x0000) && ((FLAG) != 0x00000000))
#define IS_ADC_GET_COMMONFLAG(FLAG) (((FLAG) == ADC_FLAG_MSTRDY) || ((FLAG) == ADC_FLAG_MSTEOSMP) || \
                                     ((FLAG) == ADC_FLAG_MSTEOC) || ((FLAG) == ADC_FLAG_MSTEOS) || \
                                     ((FLAG) == ADC_FLAG_MSTOVR) || ((FLAG) == ADC_FLAG_MSTEOS) || \
                                     ((FLAG) == ADC_FLAG_MSTJEOS) || ((FLAG) == ADC_FLAG_MSTAWD1) || \
                                     ((FLAG) == ADC_FLAG_MSTAWD2) || ((FLAG) == ADC_FLAG_MSTAWD3) || \
                                     ((FLAG) == ADC_FLAG_MSTJQOVF) || \
                                     ((FLAG) == ADC_FLAG_SLVRDY) || ((FLAG) == ADC_FLAG_SLVEOSMP) || \
                                     ((FLAG) == ADC_FLAG_SLVEOC) || ((FLAG) == ADC_FLAG_SLVEOS) || \
                                     ((FLAG) == ADC_FLAG_SLVOVR) || ((FLAG) == ADC_FLAG_SLVEOS) || \
                                     ((FLAG) == ADC_FLAG_SLVJEOS) || ((FLAG) == ADC_FLAG_SLVAWD1) || \
                                     ((FLAG) == ADC_FLAG_SLVAWD2) || ((FLAG) == ADC_FLAG_SLVAWD3) || \
                                     ((FLAG) == ADC_FLAG_SLVJQOVF))
/**
  * @}
  */

/** @defgroup ADC_thresholds 
  * @{
  */

#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)  

/**
  * @}
  */

/** @defgroup ADC_injected_offset 
  * @{
  */

#define IS_ADC_OFFSET(OFFSET) ((OFFSET) <= 0xFFF)   

/**
  * @}
  */

/** @defgroup ADC_injected_length 
  * @{
  */

#define IS_ADC_INJECTED_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))

/**
  * @}
  */


/** @defgroup ADC_regular_length 
  * @{
  */

#define IS_ADC_REGULAR_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10)) 
/**
  * @}
  */

/** @defgroup ADC_regular_discontinuous_mode_number 
  * @{
  */

#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER) (((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))  

/**
  * @}
  */

/** @defgroup ADC_two_sampling_delay_number 
  * @{
  */
#define IS_ADC_TWOSAMPLING_DELAY(DELAY)	(((DELAY) <= 0xF))

/**
  * @}
  */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/*  Function used to set the ADC configuration to the default reset state *****/
void ADC_DeInit(ADC_TypeDef* ADCx);	

/* Initialization and Configuration functions *********************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);	
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct); 
void ADC_InjectedInit(ADC_TypeDef* ADCx, ADC_InjectedInitTypeDef* ADC_InjectedInitStruct); 
void ADC_InjectedStructInit(ADC_InjectedInitTypeDef* ADC_InjectedInitStruct);
void ADC_CommonInit(ADC_TypeDef* ADCx, ADC_CommonInitTypeDef* ADC_CommonInitStruct);    
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct);

void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_StartCalibration(ADC_TypeDef* ADCx); 
uint32_t ADC_GetCalibrationValue(ADC_TypeDef* ADCx);
void ADC_SetCalibrationValue(ADC_TypeDef* ADCx, uint32_t ADC_Calibration);
void ADC_SelectCalibrationMode(ADC_TypeDef* ADCx, uint32_t ADC_CalibrationMode); 
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_DisableCmd(ADC_TypeDef* ADCx); 
FlagStatus ADC_GetDisableCmdStatus(ADC_TypeDef* ADCx); 
void ADC_VoltageRegulatorCmd(ADC_TypeDef* ADCx, FunctionalState NewState);  
void ADC_SelectDifferentialMode(ADC_TypeDef* ADCx, uint8_t ADC_Channel, FunctionalState NewState);
void ADC_SelectQueueOfContextMode(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_AutoDelayCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 

/* Analog Watchdog configuration functions ************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog); 
void ADC_AnalogWatchdog1ThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);	
void ADC_AnalogWatchdog2ThresholdsConfig(ADC_TypeDef* ADCx, uint8_t HighThreshold, uint8_t LowThreshold);	
void ADC_AnalogWatchdog3ThresholdsConfig(ADC_TypeDef* ADCx, uint8_t HighThreshold, uint8_t LowThreshold);	
void ADC_AnalogWatchdog1SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel); 
void ADC_AnalogWatchdog2SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);   
void ADC_AnalogWatchdog3SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel); 

/* Temperature Sensor, Vrefint and Vbat management function */
void ADC_TempSensorCmd(ADC_TypeDef* ADCx, FunctionalState NewState);  
void ADC_VrefintCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_VbatCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 

/* Channels Configuration functions ***********************************/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_RegularChannelSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t SequencerLength); 
void ADC_ExternalTriggerConfig(ADC_TypeDef* ADCx, uint16_t ADC_ExternalTrigConvEvent, uint16_t ADC_ExternalTrigEventEdge); 
 
void ADC_StartConversion(ADC_TypeDef* ADCx);
FlagStatus ADC_GetStartConversionStatus(ADC_TypeDef* ADCx);
void ADC_StopConversion(ADC_TypeDef* ADCx);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number);	
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);
uint32_t ADC_GetDualModeConversionValue(ADC_TypeDef* ADCx);

void ADC_SetChannelOffset1(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset);  
void ADC_SetChannelOffset2(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset);  
void ADC_SetChannelOffset3(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset);  
void ADC_SetChannelOffset4(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset);  

void ADC_ChannelOffset1Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);  
void ADC_ChannelOffset2Cmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_ChannelOffset3Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);  
void ADC_ChannelOffset4Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);  

/* Regular Channels DMA Configuration functions *******************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_DMAConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMAMode);  

/* Injected channels Configuration functions **********************************/
void ADC_InjectedChannelSampleTimeConfig(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint8_t ADC_SampleTime);
void ADC_StartInjectedConversion(ADC_TypeDef* ADCx); 
FlagStatus ADC_GetStartInjectedConversionStatus(ADC_TypeDef* ADCx); 
void ADC_StopInjectedConversion(ADC_TypeDef* ADCx); 
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState); 
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel);  

/* ADC Dual Modes Configuration functions *************************************/
FlagStatus ADC_GetCommonFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearCommonFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG); 

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState); 
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG); 
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT);  
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT);  

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_ADC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
