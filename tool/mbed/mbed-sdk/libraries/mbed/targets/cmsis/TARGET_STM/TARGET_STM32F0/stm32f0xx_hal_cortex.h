/**
  ******************************************************************************
  * @file    stm32f0xx_hal_cortex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file of CORTEX HAL module.
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
#ifndef __STM32F0xx_HAL_CORTEX_H
#define __STM32F0xx_HAL_CORTEX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup CORTEX CORTEX HAL module driver
  * @{
  */ 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Constants CORTEX Exported Constants
  * @{
  */
  
/** @defgroup CORTEX_Priority CORTEX Priority
  * @{
  */
#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x4)
/**
  * @}
  */
  
/** @defgroup CORTEX_SysTick_clock_source CORTEX SysTick clock source
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8    ((uint32_t)0x00000000)
#define SYSTICK_CLKSOURCE_HCLK         ((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || \
                                      ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))
/**
  * @}
  */

/**
  * @}
  */
  
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Macro CORTEX Exported Macro
  * @{
  */

/** @brief Configures the SysTick clock source.
  * @param __CLKSRC__: specifies the SysTick clock source.
  *   This parameter can be one of the following values:
  *     @arg SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
  *     @arg SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
  * @retval None
  */
#define __HAL_CORTEX_SYSTICKCLK_CONFIG(__CLKSRC__)                             \
                            do {                                               \
                                 if ((__CLKSRC__) == SYSTICK_CLKSOURCE_HCLK)   \
                                  {                                            \
                                    SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;   \
                                  }                                            \
                                 else                                          \
                                    SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;  \
                                } while(0)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CORTEX_Exported_Functions CORTEX Exported Functions
  * @{
  */
/** @addtogroup CORTEX_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions
 * @{
 */
/* Initialization and de-initialization functions *******************************/
void HAL_NVIC_SetPriority(IRQn_Type IRQn,uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
/**
  * @}
  */

/** @addtogroup CORTEX_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief   Cortex control functions
 * @{
 */
 
/* Peripheral Control functions *************************************************/
uint32_t HAL_NVIC_GetPriority(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);
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

#endif /* __STM32F0xx_HAL_CORTEX_H */
 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

