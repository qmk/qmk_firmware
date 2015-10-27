/**
  ******************************************************************************
  * @file    stm32f1xx_hal_dac_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of DAC HAL Extension module.
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
#ifndef __STM32F1xx_HAL_DAC_EX_H
#define __STM32F1xx_HAL_DAC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)
   
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup DACEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
  
/** @defgroup DACEx_Exported_Constants DACEx Exported Constants
  * @{
  */ 
   
/** @defgroup DACEx_wave_generation DACEx wave generation
  * @{
  */
#define DAC_WAVEGENERATION_NOISE           ((uint32_t)DAC_CR_WAVE1_0)
#define DAC_WAVEGENERATION_TRIANGLE        ((uint32_t)DAC_CR_WAVE1_1)

/**
  * @}
  */

/** @defgroup DACEx_lfsrunmask_triangleamplitude DACEx lfsrunmask triangleamplitude
  * @{
  */
#define DAC_LFSRUNMASK_BIT0                ((uint32_t)0x00000000) /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUNMASK_BITS1_0             ((uint32_t)DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS2_0             ((uint32_t)DAC_CR_MAMP1_1) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS3_0             ((uint32_t)DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0)/*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS4_0             ((uint32_t)DAC_CR_MAMP1_2) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS5_0             ((uint32_t)DAC_CR_MAMP1_2 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS6_0             ((uint32_t)DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS7_0             ((uint32_t)DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS8_0             ((uint32_t)DAC_CR_MAMP1_3) /*!< Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS9_0             ((uint32_t)DAC_CR_MAMP1_3 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS10_0            ((uint32_t)DAC_CR_MAMP1_3 | DAC_CR_MAMP1_1) /*!< Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS11_0            ((uint32_t)DAC_CR_MAMP1_3 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_TRIANGLEAMPLITUDE_1            ((uint32_t)0x00000000) /*!< Select max triangle amplitude of 1 */
#define DAC_TRIANGLEAMPLITUDE_3            ((uint32_t)DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 3 */
#define DAC_TRIANGLEAMPLITUDE_7            ((uint32_t)DAC_CR_MAMP1_1) /*!< Select max triangle amplitude of 7 */
#define DAC_TRIANGLEAMPLITUDE_15           ((uint32_t)DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 15 */
#define DAC_TRIANGLEAMPLITUDE_31           ((uint32_t)DAC_CR_MAMP1_2) /*!< Select max triangle amplitude of 31 */
#define DAC_TRIANGLEAMPLITUDE_63           ((uint32_t)DAC_CR_MAMP1_2 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 63 */
#define DAC_TRIANGLEAMPLITUDE_127          ((uint32_t)DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1) /*!< Select max triangle amplitude of 127 */
#define DAC_TRIANGLEAMPLITUDE_255          ((uint32_t)DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 255 */
#define DAC_TRIANGLEAMPLITUDE_511          ((uint32_t)DAC_CR_MAMP1_3) /*!< Select max triangle amplitude of 511 */
#define DAC_TRIANGLEAMPLITUDE_1023         ((uint32_t)DAC_CR_MAMP1_3 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 1023 */
#define DAC_TRIANGLEAMPLITUDE_2047         ((uint32_t)DAC_CR_MAMP1_3 | DAC_CR_MAMP1_1) /*!< Select max triangle amplitude of 2047 */
#define DAC_TRIANGLEAMPLITUDE_4095         ((uint32_t)DAC_CR_MAMP1_3 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 4095 */

/**
  * @}
  */

/** @defgroup DACEx_wave_generation DACEx wave generation
  * @{
  */
#define DAC_WAVE_NOISE                     ((uint32_t)DAC_CR_WAVE1_0)
#define DAC_WAVE_TRIANGLE                  ((uint32_t)DAC_CR_WAVE1_1)

/**
  * @}
  */
   
/** @defgroup DACEx_trigger_selection DAC trigger selection
  * @{
  */
#define DAC_TRIGGER_NONE                   ((uint32_t)0x00000000) /*!< Conversion is automatic once the DAC1_DHRxxxx register 
                                                                       has been loaded, and not by external trigger */
#define DAC_TRIGGER_T6_TRGO                ((uint32_t)                                                    DAC_CR_TEN1)  /*!< TIM6 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T7_TRGO                ((uint32_t)(                 DAC_CR_TSEL1_1                  | DAC_CR_TEN1)) /*!< TIM7 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T2_TRGO                ((uint32_t)(DAC_CR_TSEL1_2                                   | DAC_CR_TEN1)) /*!< TIM2 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T4_TRGO                ((uint32_t)(DAC_CR_TSEL1_2                  | DAC_CR_TSEL1_0 | DAC_CR_TEN1)) /*!< TIM4 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_EXT_IT9                ((uint32_t)(DAC_CR_TSEL1_2 | DAC_CR_TSEL1_1                  | DAC_CR_TEN1)) /*!< EXTI Line9 event selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_SOFTWARE               ((uint32_t)(DAC_CR_TSEL1                                     | DAC_CR_TEN1)) /*!< Conversion started by software trigger for DAC channel */

#if defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F103xE) || defined (STM32F103xG)
/* For STM32F10x high-density and XL-density devices: TIM8 */
#define DAC_TRIGGER_T8_TRGO                ((uint32_t)                                   DAC_CR_TSEL1_0 | DAC_CR_TEN1)  /*!< TIM8 TRGO selected as external conversion trigger for DAC channel */
#endif /* STM32F101xE || STM32F101xG || STM32F103xE || STM32F103xG */
   
#if defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F105xC) || defined (STM32F107xC)
/* For STM32F10x connectivity line devices and STM32F100x devices: TIM3 */
#define DAC_TRIGGER_T3_TRGO                ((uint32_t)                                   DAC_CR_TSEL1_0 | DAC_CR_TEN1)  /*!< TIM3 TRGO selected as external conversion trigger for DAC channel */
#endif /* STM32F100xB || STM32F100xE || STM32F105xC || STM32F107xC */

/* Availability of trigger from TIM5 and TIM15:                               */
/*  - For STM32F10x value line devices STM32F100xB:                           */
/*    trigger from TIM15 is available, TIM5 not available.                    */
/*  - For STM32F10x value line devices STM32F100xE:                           */
/*    trigger from TIM15 and TIM5 are both available,                         */
/*    selection depends on remap (with TIM5 as default configuration).        */
/*  - Other STM32F1 devices:                                                  */
/*    trigger from TIM5 is available, TIM15 not  available.                   */
#if defined (STM32F100xB)
#define DAC_TRIGGER_T15_TRGO               ((uint32_t)(                 DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0 | DAC_CR_TEN1)) /*!< TIM15 TRGO selected as external conversion trigger for DAC channel */
#else

#define DAC_TRIGGER_T5_TRGO                ((uint32_t)(                 DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0 | DAC_CR_TEN1)) /*!< TIM5 TRGO selected as external conversion trigger for DAC channel */

#if defined (STM32F100xE)
/*!< DAC trigger availability depending on STM32F1 devices:
     For STM32F100x high-density value line devices, the TIM15 TRGO event can be selected 
     as replacement of TIM5 TRGO if the MISC_REMAP bit in the AFIO_MAPR2 register is set.
     Refer to macro "__HAL_AFIO_REMAP_MISC_ENABLE()/__HAL_AFIO_REMAP_MISC_DISABLE()".
     Otherwise, TIM5 TRGO is used and TIM15 TRGO is not used (default case).
     For more details please refer to the AFIO section. */
#define DAC_TRIGGER_T15_TRGO    DAC_TRIGGER_T5_TRGO
#endif /* STM32F100xE */
   
#endif /* STM32F100xB */
/**
  * @}
  */

#if defined (STM32F100xB) || defined (STM32F100xE)
/** @defgroup DAC_flags_definition DAC flags definition
  * @{
  */ 
#define DAC_FLAG_DMAUDR1                   ((uint32_t)DAC_SR_DMAUDR1)
#define DAC_FLAG_DMAUDR2                   ((uint32_t)DAC_SR_DMAUDR2)   

/**
  * @}
  */

/** @defgroup DAC_IT_definition DAC IT definition
  * @{
  */ 
#define DAC_IT_DMAUDR1                   ((uint32_t)DAC_SR_DMAUDR1)
#define DAC_IT_DMAUDR2                   ((uint32_t)DAC_SR_DMAUDR2)   

/**
  * @}
  */
#endif /* STM32F100xB || STM32F100xE */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#if defined (STM32F100xB) || defined (STM32F100xE)
/** @defgroup DACEx_Exported_Macros DACEx Exported Macros
  * @{
  */

/** @brief Enable the DAC interrupt
  * @param  __HANDLE__: specifies the DAC handle
  * @param  __INTERRUPT__: specifies the DAC interrupt.
  *          This parameter can be any combination of the following values:
  *            @arg DAC_IT_DMAUDR1: DAC channel 1 DMA underrun interrupt
  *            @arg DAC_IT_DMAUDR2: DAC channel 2 DMA underrun interrupt
  * @retval None
  */
#define __HAL_DAC_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CR) |= (__INTERRUPT__))

/** @brief Disable the DAC interrupt
  * @param  __HANDLE__: specifies the DAC handle
  * @param  __INTERRUPT__: specifies the DAC interrupt.
  *          This parameter can be any combination of the following values:
  *            @arg DAC_IT_DMAUDR1: DAC channel 1 DMA underrun interrupt
  *            @arg DAC_IT_DMAUDR2: DAC channel 2 DMA underrun interrupt
  * @retval None
  */
#define __HAL_DAC_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CR) &= ~(__INTERRUPT__))

/** @brief  Checks if the specified DAC interrupt source is enabled or disabled.
  * @param __HANDLE__: DAC handle
  * @param __INTERRUPT__: DAC interrupt source to check
  *          This parameter can be any combination of the following values:
  *            @arg DAC_IT_DMAUDR1: DAC channel 1 DMA underrun interrupt
  *            @arg DAC_IT_DMAUDR2: DAC channel 2 DMA underrun interrupt
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_DAC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CR & (__INTERRUPT__)) == (__INTERRUPT__))
    
/** @brief  Get the selected DAC's flag status.
  * @param  __HANDLE__: specifies the DAC handle.
  * @param  __FLAG__: specifies the FLASH flag to get.
  *          This parameter can be any combination of the following values:
  *            @arg DAC_FLAG_DMAUDR1: DAC channel 1 DMA underrun flag
  *            @arg DAC_FLAG_DMAUDR2: DAC channel 2 DMA underrun flag
  * @retval None
  */
#define __HAL_DAC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the DAC's flag.
  * @param  __HANDLE__: specifies the DAC handle.
  * @param  __FLAG__: specifies the DAC flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DAC_FLAG_DMAUDR1: DAC channel 1 DMA underrun flag
  *            @arg DAC_FLAG_DMAUDR2: DAC channel 2 DMA underrun flag
  * @retval None
  */
#define __HAL_DAC_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR) = (__FLAG__))


/**
  * @}
  */
#endif /* STM32F100xB || STM32F100xE */

/* Private macro -------------------------------------------------------------*/

/** @defgroup DACEx_Private_Macros DACEx Private Macros
  * @{
  */
#if defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F103xE) || defined (STM32F103xG)
#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_TRIGGER_NONE)    || \
                                 ((TRIGGER) == DAC_TRIGGER_T6_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T8_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T7_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T5_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T2_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T4_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_EXT_IT9) || \
                                 ((TRIGGER) == DAC_TRIGGER_SOFTWARE))
#endif /* STM32F101xE || STM32F101xG || STM32F103xE || STM32F103xG */
#if defined (STM32F100xE) || defined (STM32F105xC) || defined (STM32F107xC)
#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_TRIGGER_NONE)    || \
                                 ((TRIGGER) == DAC_TRIGGER_T6_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T3_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T7_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T5_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T2_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T4_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_EXT_IT9) || \
                                 ((TRIGGER) == DAC_TRIGGER_SOFTWARE))
#endif /* STM32F100xE || STM32F105xC || STM32F107xC */
#if defined (STM32F100xB)
#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_TRIGGER_NONE)     || \
                                 ((TRIGGER) == DAC_TRIGGER_T6_TRGO)  || \
                                 ((TRIGGER) == DAC_TRIGGER_T3_TRGO)  || \
                                 ((TRIGGER) == DAC_TRIGGER_T7_TRGO)  || \
                                 ((TRIGGER) == DAC_TRIGGER_T15_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T2_TRGO)  || \
                                 ((TRIGGER) == DAC_TRIGGER_T4_TRGO)  || \
                                 ((TRIGGER) == DAC_TRIGGER_EXT_IT9)  || \
                                 ((TRIGGER) == DAC_TRIGGER_SOFTWARE))
#endif /* STM32F100xB */

#define IS_DAC_GENERATE_WAVE(WAVE) (((WAVE) == DAC_WAVEGENERATION_NOISE) || \
                                    ((WAVE) == DAC_WAVEGENERATION_TRIANGLE))

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) (((VALUE) == DAC_LFSRUNMASK_BIT0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS1_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS2_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS3_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS4_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS5_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS6_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS7_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS8_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS9_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS10_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS11_0) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_1) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_3) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_7) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_15) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_31) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_63) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_127) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_255) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_511) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_1023) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_2047) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_4095))

#define IS_DAC_WAVE(WAVE) (((WAVE) == DAC_WAVE_NOISE) || \
                           ((WAVE) == DAC_WAVE_TRIANGLE))

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/  

/** @addtogroup DACEx_Exported_Functions
  * @{
  */

/** @addtogroup DACEx_Exported_Functions_Group1
  * @{
  */
/* Extension features functions ***********************************************/

uint32_t HAL_DACEx_DualGetValue(DAC_HandleTypeDef* hdac);
HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef* hdac, uint32_t Channel, uint32_t Amplitude);
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef* hdac, uint32_t Channel, uint32_t Amplitude);
HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef* hdac, uint32_t Alignment, uint32_t Data1, uint32_t Data2);

void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef* hdac);
void HAL_DACEx_ConvHalfCpltCallbackCh2(DAC_HandleTypeDef* hdac);
void HAL_DACEx_ErrorCallbackCh2(DAC_HandleTypeDef* hdac);

#if defined (STM32F100xB) || defined (STM32F100xE)
void HAL_DAC_IRQHandler(DAC_HandleTypeDef* hdac);
void HAL_DAC_DMAUnderrunCallbackCh1(DAC_HandleTypeDef *hdac);
void HAL_DACEx_DMAUnderrunCallbackCh2(DAC_HandleTypeDef* hdac);
#endif /* STM32F100xB) || defined (STM32F100xE) */

/**
  * @}
  */



    
/**
  * @}
  */

/** @addtogroup DACEx_Private_Functions
  * @{
  */
void DAC_DMAConvCpltCh2(DMA_HandleTypeDef *hdma);
void DAC_DMAHalfConvCpltCh2(DMA_HandleTypeDef *hdma); 
void DAC_DMAErrorCh2(DMA_HandleTypeDef *hdma);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* STM32F100xB || STM32F100xE || STM32F101xE || STM32F101xG || STM32F103xE || STM32F103xG || STM32F105xC || STM32F107xC */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F1xx_HAL_DAC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
