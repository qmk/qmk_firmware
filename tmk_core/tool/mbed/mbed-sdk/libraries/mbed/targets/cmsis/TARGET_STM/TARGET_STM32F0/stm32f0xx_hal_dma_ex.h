/**
  ******************************************************************************
  * @file    stm32f0xx_hal_dma_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file of DMA HAL Extension module.
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
#ifndef __STM32F0xx_HAL_DMA_EX_H
#define __STM32F0xx_HAL_DMA_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup DMAEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
#if defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
/** @defgroup DMAEx_Exported_Constants DMAEx Exported Constants
  * @{
  */ 
#define DMA1_CHANNEL1_RMP                                     0x00000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA1_CHANNEL2_RMP                                     0x10000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA1_CHANNEL3_RMP                                     0x20000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA1_CHANNEL4_RMP                                     0x30000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA1_CHANNEL5_RMP                                     0x40000000 /*!< Internal define for remaping on STM32F09x/30xC */
#if !defined(STM32F030xC)
#define DMA1_CHANNEL6_RMP                                     0x50000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA1_CHANNEL7_RMP                                     0x60000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA2_CHANNEL1_RMP                                     0x00000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA2_CHANNEL2_RMP                                     0x10000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA2_CHANNEL3_RMP                                     0x20000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA2_CHANNEL4_RMP                                     0x30000000 /*!< Internal define for remaping on STM32F09x/30xC */
#define DMA2_CHANNEL5_RMP                                     0x40000000 /*!< Internal define for remaping on STM32F09x/30xC */
#endif /* !defined(STM32F030xC) */

/****************** DMA1 remap bit field definition********************/
/* DMA1 - Channel 1 */
#define HAL_DMA1_CH1_DEFAULT      (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_DEFAULT)       /*!< Default remap position for DMA1 */   
#define HAL_DMA1_CH1_ADC          (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_ADC)       /*!< Remap ADC on DMA1 Channel 1*/   
#define HAL_DMA1_CH1_TIM17_CH1    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 1 */
#define HAL_DMA1_CH1_TIM17_UP     (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 1 */ 
#define HAL_DMA1_CH1_USART1_RX    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 1 */ 
#define HAL_DMA1_CH1_USART2_RX    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 1 */ 
#define HAL_DMA1_CH1_USART3_RX    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 1 */ 
#define HAL_DMA1_CH1_USART4_RX    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 1 */ 
#define HAL_DMA1_CH1_USART5_RX    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 1 */ 
#define HAL_DMA1_CH1_USART6_RX    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 1 */ 
#if !defined(STM32F030xC)
#define HAL_DMA1_CH1_USART7_RX    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 1 */ 
#define HAL_DMA1_CH1_USART8_RX    (uint32_t) (DMA1_CHANNEL1_RMP | DMA1_CSELR_CH1_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 1 */ 
#endif /* !defined(STM32F030xC) */

/* DMA1 - Channel 2 */
#define HAL_DMA1_CH2_DEFAULT      (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_DEFAULT)       /*!< Default remap position for DMA1 */   
#define HAL_DMA1_CH2_ADC          (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_ADC)       /*!< Remap ADC on DMA1 channel 2 */  
#define HAL_DMA1_CH2_I2C1_TX      (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_I2C1_TX)   /*!< Remap I2C1 Tx on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_SPI1_RX      (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_SPI1_RX)   /*!< Remap SPI1 Rx on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_TIM1_CH1     (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_TIM1_CH1)  /*!< Remap TIM1 channel 1 on DMA1 channel 2 */
#define HAL_DMA1_CH2_TIM17_CH1    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 2 */
#define HAL_DMA1_CH2_TIM17_UP     (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_USART1_TX    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_USART2_TX    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_USART3_TX    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_USART4_TX    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_USART5_TX    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_USART6_TX    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 2 */ 
#if !defined(STM32F030xC)
#define HAL_DMA1_CH2_USART7_TX    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 2 */ 
#define HAL_DMA1_CH2_USART8_TX    (uint32_t) (DMA1_CHANNEL2_RMP | DMA1_CSELR_CH2_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 2 */ 
#endif /* !defined(STM32F030xC) */

/* DMA1 - Channel 3 */
#define HAL_DMA1_CH3_DEFAULT      (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_DEFAULT)       /*!< Default remap position for DMA1 */   
#define HAL_DMA1_CH3_TIM6_UP      (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_TIM6_UP)   /*!< Remap TIM6 up on DMA1 channel 3 */ 
#if !defined(STM32F030xC)
#define HAL_DMA1_CH3_DAC_CH1      (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_DAC_CH1)   /*!< Remap DAC Channel 1on DMA1 channel 3 */ 
#endif /* !defined(STM32F030xC) */
#define HAL_DMA1_CH3_I2C1_RX      (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_I2C1_RX)   /*!< Remap I2C1 Rx on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_SPI1_TX      (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_SPI1_TX)   /*!< Remap SPI1 Tx on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_TIM1_CH2     (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_TIM1_CH2)  /*!< Remap TIM1 channel 2 on DMA1 channel 3 */
#if !defined(STM32F030xC)
#define HAL_DMA1_CH3_TIM2_CH2     (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_TIM2_CH2)  /*!< Remap TIM2 channel 2 on DMA1 channel 3 */
#endif /* !defined(STM32F030xC) */
#define HAL_DMA1_CH3_TIM16_CH1    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 3 */
#define HAL_DMA1_CH3_TIM16_UP     (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_USART1_RX    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_USART2_RX    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_USART3_RX    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_USART4_RX    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_USART5_RX    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_USART6_RX    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 3 */ 
#if !defined(STM32F030xC)
#define HAL_DMA1_CH3_USART7_RX    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 3 */ 
#define HAL_DMA1_CH3_USART8_RX    (uint32_t) (DMA1_CHANNEL3_RMP | DMA1_CSELR_CH3_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 3 */ 
#endif /* !defined(STM32F030xC) */

/* DMA1 - Channel 4 */
#define HAL_DMA1_CH4_DEFAULT      (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_DEFAULT)       /*!< Default remap position for DMA1 */   
#define HAL_DMA1_CH4_TIM7_UP      (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_TIM7_UP)   /*!< Remap TIM7 up on DMA1 channel 4 */ 
#if !defined(STM32F030xC)
#define HAL_DMA1_CH4_DAC_CH2      (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_DAC_CH2)   /*!< Remap DAC Channel 2 on DMA1 channel 4 */
#endif /* !defined(STM32F030xC) */
#define HAL_DMA1_CH4_I2C2_TX      (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_I2C2_TX)   /*!< Remap I2C2 Tx on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_SPI2_RX      (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_SPI2_RX)   /*!< Remap SPI2 Rx on DMA1 channel 4 */ 
#if !defined(STM32F030xC)
#define HAL_DMA1_CH4_TIM2_CH4     (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_TIM2_CH4)  /*!< Remap TIM2 channel 4 on DMA1 channel 4 */
#endif /* !defined(STM32F030xC) */
#define HAL_DMA1_CH4_TIM3_CH1     (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_TIM3_CH1)  /*!< Remap TIM3 channel 1 on DMA1 channel 4 */
#define HAL_DMA1_CH4_TIM3_TRIG    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_TIM3_TRIG) /*!< Remap TIM3 Trig on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_TIM16_CH1    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 4 */
#define HAL_DMA1_CH4_TIM16_UP     (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_USART1_TX    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_USART2_TX    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_USART3_TX    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_USART4_TX    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_USART5_TX    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_USART6_TX    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 4 */ 
#if !defined(STM32F030xC)
#define HAL_DMA1_CH4_USART7_TX    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 4 */ 
#define HAL_DMA1_CH4_USART8_TX    (uint32_t) (DMA1_CHANNEL4_RMP | DMA1_CSELR_CH4_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 4 */ 
#endif /* !defined(STM32F030xC) */

/* DMA1 - Channel 5 */
#define HAL_DMA1_CH5_DEFAULT      (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_DEFAULT)       /*!< Default remap position for DMA1 */   
#define HAL_DMA1_CH5_I2C2_RX      (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_I2C2_RX)   /*!< Remap I2C2 Rx on DMA1 channel 5 */ 
#define HAL_DMA1_CH5_SPI2_TX      (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_SPI2_TX)   /*!< Remap SPI1 Tx on DMA1 channel 5 */ 
#define HAL_DMA1_CH5_TIM1_CH3     (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_TIM1_CH3)  /*!< Remap TIM1 channel 3 on DMA1 channel 5 */
#define HAL_DMA1_CH5_USART1_RX    (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 5 */ 
#define HAL_DMA1_CH5_USART2_RX    (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 5 */ 
#define HAL_DMA1_CH5_USART3_RX    (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 5 */ 
#define HAL_DMA1_CH5_USART4_RX    (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 5 */ 
#define HAL_DMA1_CH5_USART5_RX    (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 5 */ 
#define HAL_DMA1_CH5_USART6_RX    (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 5 */ 
#if !defined(STM32F030xC)
#define HAL_DMA1_CH5_USART7_RX    (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 5 */ 
#define HAL_DMA1_CH5_USART8_RX    (uint32_t) (DMA1_CHANNEL5_RMP | DMA1_CSELR_CH5_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 5 */ 
#endif /* !defined(STM32F030xC) */

#if !defined(STM32F030xC)
/* DMA1 - Channel 6 */
#define HAL_DMA1_CH6_DEFAULT      (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_DEFAULT)       /*!< Default remap position for DMA1 */   
#define HAL_DMA1_CH6_I2C1_TX      (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_I2C1_TX)   /*!< Remap I2C1 Tx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_SPI2_RX      (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_SPI2_RX)   /*!< Remap SPI2 Rx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_TIM1_CH1     (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_TIM1_CH1)  /*!< Remap TIM1 channel 1 on DMA1 channel 6 */
#define HAL_DMA1_CH6_TIM1_CH2     (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_TIM1_CH2)  /*!< Remap TIM1 channel 2 on DMA1 channel 6 */
#define HAL_DMA1_CH6_TIM1_CH3     (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_TIM1_CH3)  /*!< Remap TIM1 channel 3 on DMA1 channel 6 */
#define HAL_DMA1_CH6_TIM3_CH1     (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_TIM3_CH1)  /*!< Remap TIM3 channel 1 on DMA1 channel 6 */
#define HAL_DMA1_CH6_TIM3_TRIG    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_TIM3_TRIG) /*!< Remap TIM3 Trig on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_TIM16_CH1    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_TIM16_CH1) /*!< Remap TIM16 channel 1 on DMA1 channel 6 */
#define HAL_DMA1_CH6_TIM16_UP     (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_TIM16_UP)  /*!< Remap TIM16 up on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_USART1_RX    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_USART1_RX) /*!< Remap USART1 Rx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_USART2_RX    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_USART2_RX) /*!< Remap USART2 Rx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_USART3_RX    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_USART3_RX) /*!< Remap USART3 Rx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_USART4_RX    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_USART4_RX) /*!< Remap USART4 Rx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_USART5_RX    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_USART5_RX) /*!< Remap USART5 Rx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_USART6_RX    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_USART6_RX) /*!< Remap USART6 Rx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_USART7_RX    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_USART7_RX) /*!< Remap USART7 Rx on DMA1 channel 6 */ 
#define HAL_DMA1_CH6_USART8_RX    (uint32_t) (DMA1_CHANNEL6_RMP | DMA1_CSELR_CH6_USART8_RX) /*!< Remap USART8 Rx on DMA1 channel 6 */ 
/* DMA1 - Channel 7 */
#define HAL_DMA1_CH7_DEFAULT      (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_DEFAULT)       /*!< Default remap position for DMA1 */   
#define HAL_DMA1_CH7_I2C1_RX      (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_I2C1_RX)   /*!< Remap I2C1 Rx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_SPI2_TX      (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_SPI2_TX)   /*!< Remap SPI2 Tx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_TIM2_CH2     (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_TIM2_CH2)  /*!< Remap TIM2 channel 2 on DMA1 channel 7 */
#define HAL_DMA1_CH7_TIM2_CH4     (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_TIM2_CH4)  /*!< Remap TIM2 channel 4 on DMA1 channel 7 */
#define HAL_DMA1_CH7_TIM17_CH1    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_TIM17_CH1) /*!< Remap TIM17 channel 1 on DMA1 channel 7 */
#define HAL_DMA1_CH7_TIM17_UP     (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_TIM17_UP)  /*!< Remap TIM17 up on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_USART1_TX    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_USART1_TX) /*!< Remap USART1 Tx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_USART2_TX    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_USART2_TX) /*!< Remap USART2 Tx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_USART3_TX    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_USART3_TX) /*!< Remap USART3 Tx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_USART4_TX    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_USART4_TX) /*!< Remap USART4 Tx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_USART5_TX    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_USART5_TX) /*!< Remap USART5 Tx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_USART6_TX    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_USART6_TX) /*!< Remap USART6 Tx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_USART7_TX    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_USART7_TX) /*!< Remap USART7 Tx on DMA1 channel 7 */ 
#define HAL_DMA1_CH7_USART8_TX    (uint32_t) (DMA1_CHANNEL7_RMP | DMA1_CSELR_CH7_USART8_TX) /*!< Remap USART8 Tx on DMA1 channel 7 */

/****************** DMA2 remap bit field definition********************/
/* DMA2 - Channel 1 */
#define HAL_DMA2_CH1_DEFAULT      (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_DEFAULT)       /*!< Default remap position for DMA2 */   
#define HAL_DMA2_CH1_I2C2_TX      (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_I2C2_TX)   /*!< Remap I2C2 TX on DMA2 channel 1 */ 
#define HAL_DMA2_CH1_USART1_TX    (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 1 */ 
#define HAL_DMA2_CH1_USART2_TX    (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 1 */ 
#define HAL_DMA2_CH1_USART3_TX    (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 1 */ 
#define HAL_DMA2_CH1_USART4_TX    (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 1 */ 
#define HAL_DMA2_CH1_USART5_TX    (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 1 */ 
#define HAL_DMA2_CH1_USART6_TX    (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 1 */ 
#define HAL_DMA2_CH1_USART7_TX    (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 1 */ 
#define HAL_DMA2_CH1_USART8_TX    (uint32_t) (DMA2_CHANNEL1_RMP | DMA2_CSELR_CH1_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 1 */ 
/* DMA2 - Channel 2 */
#define HAL_DMA2_CH2_DEFAULT      (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_DEFAULT)       /*!< Default remap position for DMA2 */   
#define HAL_DMA2_CH2_I2C2_RX      (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_I2C2_RX)   /*!< Remap I2C2 Rx on DMA2 channel 2 */ 
#define HAL_DMA2_CH2_USART1_RX    (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_USART1_RX) /*!< Remap USART1 Rx on DMA2 channel 2 */ 
#define HAL_DMA2_CH2_USART2_RX    (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_USART2_RX) /*!< Remap USART2 Rx on DMA2 channel 2 */ 
#define HAL_DMA2_CH2_USART3_RX    (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_USART3_RX) /*!< Remap USART3 Rx on DMA2 channel 2 */ 
#define HAL_DMA2_CH2_USART4_RX    (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_USART4_RX) /*!< Remap USART4 Rx on DMA2 channel 2 */ 
#define HAL_DMA2_CH2_USART5_RX    (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_USART5_RX) /*!< Remap USART5 Rx on DMA2 channel 2 */ 
#define HAL_DMA2_CH2_USART6_RX    (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_USART6_RX) /*!< Remap USART6 Rx on DMA2 channel 2 */ 
#define HAL_DMA2_CH2_USART7_RX    (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_USART7_RX) /*!< Remap USART7 Rx on DMA2 channel 2 */ 
#define HAL_DMA2_CH2_USART8_RX    (uint32_t) (DMA2_CHANNEL2_RMP | DMA2_CSELR_CH2_USART8_RX) /*!< Remap USART8 Rx on DMA2 channel 2 */ 
/* DMA2 - Channel 3 */
#define HAL_DMA2_CH3_DEFAULT      (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_DEFAULT)       /*!< Default remap position for DMA2 */   
#define HAL_DMA2_CH3_TIM6_UP      (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_TIM6_UP)   /*!< Remap TIM6 up on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_DAC_CH1      (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_DAC_CH1)   /*!< Remap DAC channel 1 on DMA2 channel 3 */
#define HAL_DMA2_CH3_SPI1_RX      (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_SPI1_RX)   /*!< Remap SPI1 Rx on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_USART1_RX    (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_USART1_RX) /*!< Remap USART1 Rx on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_USART2_RX    (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_USART2_RX) /*!< Remap USART2 Rx on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_USART3_RX    (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_USART3_RX) /*!< Remap USART3 Rx on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_USART4_RX    (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_USART4_RX) /*!< Remap USART4 Rx on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_USART5_RX    (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_USART5_RX) /*!< Remap USART5 Rx on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_USART6_RX    (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_USART6_RX) /*!< Remap USART6 Rx on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_USART7_RX    (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_USART7_RX) /*!< Remap USART7 Rx on DMA2 channel 3 */ 
#define HAL_DMA2_CH3_USART8_RX    (uint32_t) (DMA2_CHANNEL3_RMP | DMA2_CSELR_CH3_USART8_RX) /*!< Remap USART8 Rx on DMA2 channel 3 */ 
/* DMA2 - Channel 4 */
#define HAL_DMA2_CH4_DEFAULT      (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_DEFAULT)       /*!< Default remap position for DMA2 */   
#define HAL_DMA2_CH4_TIM7_UP      (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_TIM7_UP)   /*!< Remap TIM7 up on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_DAC_CH2      (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_DAC_CH2)   /*!< Remap DAC channel 2 on DMA2 channel 4 */
#define HAL_DMA2_CH4_SPI1_TX      (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_SPI1_TX)   /*!< Remap SPI1 Tx on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_USART1_TX    (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_USART2_TX    (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_USART3_TX    (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_USART4_TX    (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_USART5_TX    (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_USART6_TX    (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_USART7_TX    (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 4 */ 
#define HAL_DMA2_CH4_USART8_TX    (uint32_t) (DMA2_CHANNEL4_RMP | DMA2_CSELR_CH4_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 4 */ 
/* DMA2 - Channel 5 */
#define HAL_DMA2_CH5_DEFAULT      (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_DEFAULT)       /*!< Default remap position for DMA2 */   
#define HAL_DMA2_CH5_ADC          (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_ADC)       /*!< Remap ADC on DMA2 channel 5 */  
#define HAL_DMA2_CH5_USART1_TX    (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_USART1_TX) /*!< Remap USART1 Tx on DMA2 channel 5 */ 
#define HAL_DMA2_CH5_USART2_TX    (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_USART2_TX) /*!< Remap USART2 Tx on DMA2 channel 5 */ 
#define HAL_DMA2_CH5_USART3_TX    (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_USART3_TX) /*!< Remap USART3 Tx on DMA2 channel 5 */ 
#define HAL_DMA2_CH5_USART4_TX    (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_USART4_TX) /*!< Remap USART4 Tx on DMA2 channel 5 */ 
#define HAL_DMA2_CH5_USART5_TX    (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_USART5_TX) /*!< Remap USART5 Tx on DMA2 channel 5 */ 
#define HAL_DMA2_CH5_USART6_TX    (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_USART6_TX) /*!< Remap USART6 Tx on DMA2 channel 5 */ 
#define HAL_DMA2_CH5_USART7_TX    (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_USART7_TX) /*!< Remap USART7 Tx on DMA2 channel 5 */ 
#define HAL_DMA2_CH5_USART8_TX    (uint32_t) (DMA2_CHANNEL5_RMP | DMA2_CSELR_CH5_USART8_TX) /*!< Remap USART8 Tx on DMA2 channel 5 */ 
#endif /* !defined(STM32F030xC) */

#if defined(STM32F091xC) || defined(STM32F098xx) 
#define IS_HAL_DMA1_REMAP(REQUEST)  (((REQUEST) == HAL_DMA1_CH1_DEFAULT)  ||\
                                    ((REQUEST) == HAL_DMA1_CH1_ADC)       ||\
                                    ((REQUEST) == HAL_DMA1_CH1_TIM17_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_TIM17_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART6_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART7_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART8_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH2_ADC)       ||\
                                    ((REQUEST) == HAL_DMA1_CH2_I2C1_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH2_SPI1_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH2_TIM1_CH1)  ||\
                                    ((REQUEST) == HAL_DMA1_CH2_I2C1_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH2_TIM17_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_TIM17_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART1_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART2_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART3_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART4_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART5_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART6_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART7_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART8_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM6_UP)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_DAC_CH1)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_I2C1_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_SPI1_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM1_CH2)  ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM2_CH2)  ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM16_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM16_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART6_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART7_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART8_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM7_UP)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_DAC_CH2)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_I2C2_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_SPI2_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM2_CH4)  ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM3_CH1)  ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM3_TRIG) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM16_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM16_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART1_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART2_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART3_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART4_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART5_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART6_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART7_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART8_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH5_I2C2_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH5_SPI2_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH5_TIM1_CH3)  ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART6_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART7_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART8_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH6_I2C1_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH6_SPI2_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH6_TIM1_CH1)  ||\
                                    ((REQUEST) == HAL_DMA1_CH6_TIM1_CH2)  ||\
                                    ((REQUEST) == HAL_DMA1_CH6_TIM1_CH3)  ||\
                                    ((REQUEST) == HAL_DMA1_CH6_TIM3_CH1)  ||\
                                    ((REQUEST) == HAL_DMA1_CH6_TIM3_TRIG) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_TIM16_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_TIM16_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH6_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_USART6_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_USART7_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH6_USART8_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH7_I2C1_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH7_SPI2_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH7_TIM2_CH2)  ||\
                                    ((REQUEST) == HAL_DMA1_CH7_TIM2_CH4)  ||\
                                    ((REQUEST) == HAL_DMA1_CH7_TIM17_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_TIM17_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH7_USART1_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_USART2_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_USART3_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_USART4_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_USART5_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_USART6_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_USART7_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH7_USART8_TX))

#define IS_HAL_DMA2_REMAP(REQUEST)  (((REQUEST) == HAL_DMA2_CH1_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA2_CH1_I2C2_TX)   ||\
                                    ((REQUEST) == HAL_DMA2_CH1_USART1_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH1_USART2_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH1_USART3_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH1_USART4_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH1_USART5_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH1_USART6_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH1_USART7_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH1_USART8_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH2_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA2_CH2_I2C2_RX)   ||\
                                    ((REQUEST) == HAL_DMA2_CH2_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH2_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH2_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH2_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH2_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH2_USART6_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH2_USART7_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH2_USART8_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH3_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA2_CH3_TIM6_UP)   ||\
                                    ((REQUEST) == HAL_DMA2_CH3_DAC_CH1)   ||\
                                    ((REQUEST) == HAL_DMA2_CH3_SPI1_RX)   ||\
                                    ((REQUEST) == HAL_DMA2_CH3_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH3_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH3_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH3_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH3_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH3_USART6_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH3_USART7_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH3_USART8_RX) ||\
                                    ((REQUEST) == HAL_DMA2_CH4_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA2_CH4_TIM7_UP)   ||\
                                    ((REQUEST) == HAL_DMA2_CH4_DAC_CH2)   ||\
                                    ((REQUEST) == HAL_DMA2_CH4_SPI1_TX)   ||\
                                    ((REQUEST) == HAL_DMA2_CH4_USART1_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH4_USART2_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH4_USART3_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH4_USART4_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH4_USART5_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH4_USART6_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH4_USART7_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH4_USART8_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH5_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA2_CH5_ADC)       ||\
                                    ((REQUEST) == HAL_DMA2_CH5_USART1_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH5_USART2_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH5_USART3_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH5_USART4_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH5_USART5_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH5_USART6_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH5_USART7_TX) ||\
                                    ((REQUEST) == HAL_DMA2_CH5_USART8_TX ))
#endif /* STM32F091xC || STM32F098xx */

#if defined(STM32F030xC)
#define IS_HAL_DMA1_REMAP(REQUEST)  (((REQUEST) == HAL_DMA1_CH1_DEFAULT)  ||\
                                    ((REQUEST) == HAL_DMA1_CH1_ADC)       ||\
                                    ((REQUEST) == HAL_DMA1_CH1_TIM17_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_TIM17_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH1_USART6_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH2_ADC)       ||\
                                    ((REQUEST) == HAL_DMA1_CH2_I2C1_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH2_SPI1_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH2_TIM1_CH1)  ||\
                                    ((REQUEST) == HAL_DMA1_CH2_I2C1_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH2_TIM17_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_TIM17_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART1_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART2_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART3_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART4_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART5_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH2_USART6_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM6_UP)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_I2C1_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_SPI1_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM1_CH2)  ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM16_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_TIM16_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH3_USART6_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM7_UP)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_I2C2_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_SPI2_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM3_CH1)  ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM3_TRIG) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM16_CH1) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_TIM16_UP)  ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART1_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART2_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART3_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART4_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART5_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH4_USART6_TX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_DEFAULT)   ||\
                                    ((REQUEST) == HAL_DMA1_CH5_I2C2_RX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH5_SPI2_TX)   ||\
                                    ((REQUEST) == HAL_DMA1_CH5_TIM1_CH3)  ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART1_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART2_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART3_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART4_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART5_RX) ||\
                                    ((REQUEST) == HAL_DMA1_CH5_USART6_RX))
#endif /* STM32F030xC */

/**
  * @}
  */ 
#endif /* STM32F091xC  || STM32F098xx || STM32F030xC */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup DMAEx_Exported_Macros DMAEx Exported Macros
  * @{
  */
/* Interrupt & Flag management */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx)
/**
  * @brief  Returns the current DMA Channel transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer complete flag index.
  */      
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TC5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TC6 :\
   DMA_FLAG_TC7)

/**
  * @brief  Returns the current DMA Channel half transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified half transfer complete flag index.
  */      
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_HT5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_HT6 :\
   DMA_FLAG_HT7)

/**
  * @brief  Returns the current DMA Channel transfer error flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer error flag index.
  */
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TE5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TE6 :\
   DMA_FLAG_TE7)

/**
  * @brief  Get the DMA Channel pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *         Where x can be 1_7 to select the DMA Channel flag.   
  * @retval The state of FLAG (SET or RESET).
  */

#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)   (DMA1->ISR & (__FLAG__))

/**
  * @brief  Clears the DMA Channel pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *         Where x can be 1_7 to select the DMA Channel flag.   
  * @retval None
  */
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) (DMA1->IFCR = (__FLAG__))

#elif defined(STM32F091xC) || defined(STM32F098xx)
/**
  * @brief  Returns the current DMA Channel transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer complete flag index.
  */      
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TC5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TC6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel7))? DMA_FLAG_TC7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_TC4 :\
   DMA_FLAG_TC5)

/**
  * @brief  Returns the current DMA Channel half transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified half transfer complete flag index.
  */      
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_HT5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_HT6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel7))? DMA_FLAG_HT7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_HT4 :\
   DMA_FLAG_HT5)

/**
  * @brief  Returns the current DMA Channel transfer error flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer error flag index.
  */
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel5))? DMA_FLAG_TE5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel6))? DMA_FLAG_TE6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel7))? DMA_FLAG_TE7 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Channel4))? DMA_FLAG_TE4 :\
   DMA_FLAG_TE5)

/**
  * @brief  Get the DMA Channel pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *         Where x can be 0_4, 1_5, 2_6 or 3_7 to select the DMA Channel flag.   
  * @retval The state of FLAG (SET or RESET).
  */

#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)\
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Channel7)? (DMA2->ISR & (__FLAG__)) :\
  (DMA1->ISR & (__FLAG__)))

/**
  * @brief  Clears the DMA Channel pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *         Where x can be 0_4, 1_5, 2_6 or 3_7 to select the DMA Channel flag.   
  * @retval None
  */
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) \
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Channel7)? (DMA2->IFCR = (__FLAG__)) :\
  (DMA1->IFCR = (__FLAG__)))

#else /* STM32F030x8_STM32F030xC_STM32F031x6_STM32F038xx_STM32F051x8_STM32F058xx_STM32F070x6_STM32F070xB Product devices */
/**
  * @brief  Returns the current DMA Channel transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer complete flag index.
  */      
#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TC1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TC2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TC3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TC4 :\
   DMA_FLAG_TC5)

/**
  * @brief  Returns the current DMA Channel half transfer complete flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified half transfer complete flag index.
  */      
#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_HT1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_HT2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_HT3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_HT4 :\
   DMA_FLAG_HT5)

/**
  * @brief  Returns the current DMA Channel transfer error flag.
  * @param  __HANDLE__: DMA handle
  * @retval The specified transfer error flag index.
  */
#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel1))? DMA_FLAG_TE1 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel2))? DMA_FLAG_TE2 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel3))? DMA_FLAG_TE3 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Channel4))? DMA_FLAG_TE4 :\
   DMA_FLAG_TE5)

/**
  * @brief  Get the DMA Channel pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *         Where x can be 1_5 to select the DMA Channel flag.   
  * @retval The state of FLAG (SET or RESET).
  */

#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)   (DMA1->ISR & (__FLAG__))

/**
  * @brief  Clears the DMA Channel pending flags.
  * @param  __HANDLE__: DMA handle
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TCx:  Transfer complete flag
  *            @arg DMA_FLAG_HTx:  Half transfer complete flag
  *            @arg DMA_FLAG_TEx:  Transfer error flag
  *         Where x can be 1_5 to select the DMA Channel flag.   
  * @retval None
  */
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) (DMA1->IFCR = (__FLAG__))

#endif


#if defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
#define __HAL_DMA1_REMAP(__REQUEST__)                                                              \
         do { assert_param(IS_HAL_DMA1_REMAP(__REQUEST__));                                             \
              DMA1->CSELR &= ~((uint32_t)0x0F << (uint32_t)(((__REQUEST__) >> 28) * 4)); \
              DMA1->CSELR |= (uint32_t)((__REQUEST__) & 0x0FFFFFFF);                                     \
  }while(0)

#if defined(STM32F091xC) || defined(STM32F098xx)
#define __HAL_DMA2_REMAP(__REQUEST__)                                                              \
         do { assert_param(IS_HAL_DMA2_REMAP(__REQUEST__));                                             \
              DMA2->CSELR &= ~((uint32_t)0x0F << (uint32_t)(((__REQUEST__) >> 28) * 4)); \
              DMA2->CSELR |= (uint32_t)((__REQUEST__) & 0x0FFFFFFF);                                     \
         }while(0)
#endif /* STM32F091xC || STM32F098xx */

#endif /* STM32F091xC || STM32F098xx || STM32F030xC */

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

#endif /* __STM32F0xx_HAL_DMA_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
