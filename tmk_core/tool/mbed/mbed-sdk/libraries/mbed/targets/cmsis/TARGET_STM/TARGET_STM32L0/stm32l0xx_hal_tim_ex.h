/**
  ******************************************************************************
  * @file    stm32l0xx_hal_tim_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of TIM HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32L0xx_HAL_TIM_EX_H
#define __STM32L0xx_HAL_TIM_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup TIMEx TIMEx (Timer extended)
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  TIM Master configuration Structure definition  
  */ 
typedef struct {
  uint32_t  MasterOutputTrigger;   /*!< Trigger output (TRGO) selection 
                                      This parameter can be a value of @ref TIM_Master_Mode_Selection */
  uint32_t  MasterSlaveMode;       /*!< Master/slave mode selection 
                                      This parameter can be a value of @ref TIM_Master_Slave_Mode */
}TIM_MasterConfigTypeDef;



/* Exported constants --------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Constants TIMEx Exported Constants
  * @{
  */

/** @defgroup TIMEx_Trigger_Selection Trigger selection
  * @{
  */  
#define  TIM_TRGO_RESET            ((uint32_t)0x0000)
#define  TIM_TRGO_ENABLE           (TIM_CR2_MMS_0)
#define  TIM_TRGO_UPDATE           (TIM_CR2_MMS_1)
#define  TIM_TRGO_OC1              ((TIM_CR2_MMS_1 | TIM_CR2_MMS_0))
#define  TIM_TRGO_OC1REF           (TIM_CR2_MMS_2)
#define  TIM_TRGO_OC2REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_0))
#define  TIM_TRGO_OC3REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_1))
#define  TIM_TRGO_OC4REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0))

#define IS_TIM_TRGO_SOURCE(__SOURCE__) (((__SOURCE__) == TIM_TRGO_RESET)  || \
                                        ((__SOURCE__) == TIM_TRGO_ENABLE) || \
                                        ((__SOURCE__) == TIM_TRGO_UPDATE) || \
                                        ((__SOURCE__) == TIM_TRGO_OC1)    || \
                                        ((__SOURCE__) == TIM_TRGO_OC1REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC2REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC3REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC4REF))
   
/**
  * @}
  */ 

/** @defgroup TIMEx_Remap Remaping
  * @{
  */

#define TIM2_ETR_GPIO                     ((uint32_t)0x0)
#define TIM2_ETR_HSI48                    TIM2_OR_ETR_RMP_2
#define TIM2_ETR_LSE                      (TIM2_OR_ETR_RMP_2 | TIM2_OR_ETR_RMP_0)
#define TIM2_ETR_COMP2_OUT                (TIM2_OR_ETR_RMP_2 | TIM2_OR_ETR_RMP_1)
#define TIM2_ETR_COMP1_OUT                TIM2_OR_ETR_RMP
#define TIM2_TI4_GPIO                     ((uint32_t)0x0)
#define TIM2_TI4_COMP2                    TIM2_OR_TI4_RMP_0
#define TIM2_TI4_COMP1                    TIM2_OR_TI4_RMP_1

#define TIM21_ETR_GPIO                    ((uint32_t)0x0)
#define TIM21_ETR_COMP2_OUT               TIM21_OR_ETR_RMP_0
#define TIM21_ETR_COMP1_OUT               TIM21_OR_ETR_RMP_1
#define TIM21_ETR_LSE                     TIM21_OR_ETR_RMP
#define TIM21_TI1_GPIO                    ((uint32_t)0x0)
#define TIM21_TI1_MCO                     TIM21_OR_TI1_RMP
#define TIM21_TI1_RTC_WKUT_IT             TIM21_OR_TI1_RMP_0
#define TIM21_TI1_HSE_RTC                 TIM21_OR_TI1_RMP_1
#define TIM21_TI1_MSI                     (TIM21_OR_TI1_RMP_0 | TIM21_OR_TI1_RMP_1)
#define TIM21_TI1_LSE                     TIM21_OR_TI1_RMP_2
#define TIM21_TI1_LSI                     (TIM21_OR_TI1_RMP_2 | TIM21_OR_TI1_RMP_0)
#define TIM21_TI1_COMP1_OUT               (TIM21_OR_TI1_RMP_2 | TIM21_OR_TI1_RMP_1)
#define TIM21_TI2_GPIO                    ((uint32_t)0x0)
#define TIM21_TI2_COMP2_OUT               TIM21_OR_TI2_RMP

#define TIM22_ETR_LSE                     ((uint32_t)0x0)
#define TIM22_ETR_COMP2_OUT               TIM22_OR_ETR_RMP_0
#define TIM22_ETR_COMP1_OUT               TIM22_OR_ETR_RMP_1
#define TIM22_ETR_GPIO                    TIM22_OR_ETR_RMP
#define TIM22_TI1_GPIO1                   ((uint32_t)0x0)
#define TIM22_TI1_COMP2_OUT               TIM22_OR_TI1_RMP_0
#define TIM22_TI1_COMP1_OUT               TIM22_OR_TI1_RMP_1
#define TIM22_TI1_GPIO2                   TIM22_OR_TI1_RMP

#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) \
    || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)

#define TIM3_TI4_GPIO_DEF                 ((uint32_t)0x0)
#define TIM3_TI4_GPIOC9_AF2               TIM3_OR_TI4_RMP
#define TIM3_TI2_GPIO_DEF                 ((uint32_t)0x0)
#define TIM3_TI2_GPIOB5_AF4               TIM3_OR_TI2_RMP
#define TIM3_TI1_USB_SOF                  ((uint32_t)0x0)
#define TIM3_TI1_GPIO                     TIM3_OR_TI1_RMP
#define TIM3_ETR_GPIO                     ((uint32_t)0x0)
#define TIM3_ETR_HSI                      TIM3_OR_ETR_RMP_1

#endif /*defined (STM32L07Xxx) or defined (STM32L08Xxx) */



#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) \
    || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)


#define IS_TIM_REMAP(__INSTANCE__, __TIM_REMAP__)               \
        (((__INSTANCE__ == TIM2)   &&  ((__TIM_REMAP__) <=  (TIM2_OR_TI4_RMP  | TIM2_OR_ETR_RMP))) || \
         ((__INSTANCE__ == TIM22)  &&  ((__TIM_REMAP__) <=  (TIM22_OR_TI1_RMP | TIM22_OR_ETR_RMP))) || \
         ((__INSTANCE__ == TIM21)  &&  ((__TIM_REMAP__) <=  (TIM21_OR_ETR_RMP | TIM21_OR_TI1_RMP | TIM21_OR_TI2_RMP))) || \
         ((__INSTANCE__ == TIM3)   &&  ((__TIM_REMAP__) <=  (TIM3_OR_ETR_RMP  | TIM3_OR_TI1_RMP  | TIM3_OR_TI2_RMP | TIM3_OR_TI4_RMP))))

#define IS_CHANNEL_AVAILABLE(__INSTANCE__, __CHANNEL__)     \
        (((__INSTANCE__ == TIM2)   &&  (((__CHANNEL__) == TIM_CHANNEL_1)    ||   \
                                        ((__CHANNEL__) == TIM_CHANNEL_2)   ||   \
                                        ((__CHANNEL__) == TIM_CHANNEL_3)   ||   \
                                        ((__CHANNEL__) == TIM_CHANNEL_4))) ||   \
          ((__INSTANCE__ == TIM3) &&   (((__CHANNEL__) == TIM_CHANNEL_1)    ||   \
                                        ((__CHANNEL__) == TIM_CHANNEL_2)   ||   \
                                        ((__CHANNEL__) == TIM_CHANNEL_3)   ||   \
                                        ((__CHANNEL__) == TIM_CHANNEL_4))) ||   \
          ((__INSTANCE__ == TIM21) &&  (((__CHANNEL__) == TIM_CHANNEL_1)    ||   \
                                        ((__CHANNEL__) == TIM_CHANNEL_2))) ||   \
          ((__INSTANCE__ == TIM22) &&  (((__CHANNEL__) == TIM_CHANNEL_1)    ||   \
                                        ((__CHANNEL__) == TIM_CHANNEL_2))))

#else

#define IS_TIM_REMAP(__INSTANCE__, __TIM_REMAP__)               \
        (((__INSTANCE__ == TIM2)   &&  ((__TIM_REMAP__) <=  (TIM2_OR_TI4_RMP  | TIM2_OR_ETR_RMP))) || \
         ((__INSTANCE__ == TIM22)  &&  ((__TIM_REMAP__) <=  (TIM22_OR_TI1_RMP | TIM22_OR_ETR_RMP))) || \
         ((__INSTANCE__ == TIM21)  &&  ((__TIM_REMAP__) <=  (TIM21_OR_ETR_RMP | TIM21_OR_TI1_RMP | TIM21_OR_TI2_RMP))))

#define IS_CHANNEL_AVAILABLE(__INSTANCE__, __CHANNEL__)     \
        (((__INSTANCE__ == TIM2)   &&   (((__CHANNEL__) == TIM_CHANNEL_1)   || \
                                         ((__CHANNEL__) == TIM_CHANNEL_2)   || \
                                         ((__CHANNEL__) == TIM_CHANNEL_3)   || \
                                         ((__CHANNEL__) == TIM_CHANNEL_4))) || \
          ((__INSTANCE__ == TIM21)  &&  (((__CHANNEL__) == TIM_CHANNEL_1)   || \
                                         ((__CHANNEL__) == TIM_CHANNEL_2))) || \
          ((__INSTANCE__ == TIM22)  &&  (((__CHANNEL__) == TIM_CHANNEL_1)   || \
                                         ((__CHANNEL__) == TIM_CHANNEL_2))))

#endif /*defined (STM32L07Xxx) or defined (STM32L08Xxx) */


/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Control functions  ***********************************************************/

/** @defgroup TIMEx_Exported_Functions TIMEx Exported Functions
 *  @{
 */

/** @defgroup TIMEx_Exported_Functions_Group1 TIMEx Peripheral Control functions
 *  @{
 */

HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef * sMasterConfig);

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

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_TIM_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

