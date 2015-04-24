/**
  ******************************************************************************
  * @file    stm32l1xx_hal_tim_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of TIM HAL Extension module.
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
#ifndef __STM32L1xx_HAL_TIM_EX_H
#define __STM32L1xx_HAL_TIM_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup TIMEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup TIMEx_Exported_Types TIMEx Exported Types
  * @{
  */

/** 
  * @brief  TIM Master configuration Structure definition  
  */ 
typedef struct {
  uint32_t  MasterOutputTrigger;   /*!< Trigger output (TRGO) selection 
                                      This parameter can be a value of @ref TIM_Master_Mode_Selection */ 
  uint32_t  MasterSlaveMode;       /*!< Master/slave mode selection 
                                      This parameter can be a value of @ref TIM_Master_Slave_Mode */
}TIM_MasterConfigTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Constants TIMEx_Exported_Constants
  * @{
  */
    
/** @defgroup TIMEx_Remap TIMEx_Remap
  * @{
  */

#if defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define TIM_TIM2_ITR1_TIM10_OC        (0x00000000)       /* !< TIM2 ITR1 input is connected to TIM10 OC */
#define TIM_TIM2_ITR1_TIM5_TGO        TIM2_OR_ITR1_RMP   /* !< TIM2 ITR1 input is connected to TIM5 TGO */
#endif /* defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) */

#if defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define TIM_TIM3_ITR2_TIM11_OC        (0x00000000)       /* !< TIM3 ITR2 input is connected to TIM11 OC */
#define TIM_TIM3_ITR2_TIM5_TGO        TIM2_OR_ITR1_RMP   /* !< TIM3 ITR2 input is connected to TIM5 TGO */
#endif /* defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) */

#if defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define TIM_TIM9_ITR1_TIM3_TGO        (0x00000000)       /* !< TIM9 ITR1 input is connected to TIM3 TGO */
#define TIM_TIM9_ITR1_TS              TIM9_OR_ITR1_RMP   /* !< TIM9 ITR1 input is connected to touch sensing I/O */
#endif /* defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) */
#define TIM_TIM9_GPIO                 (0x00000000)       /* !< TIM9 Channel1 is connected to GPIO */
#define TIM_TIM9_LSE                  TIM_OR_TI1RMP_0    /* !< TIM9 Channel1 is connected to LSE internal clock */
#define TIM_TIM9_GPIO1                TIM_OR_TI1RMP_1    /* !< TIM9 Channel1 is connected to GPIO */
#define TIM_TIM9_GPIO2                TIM_OR_TI1RMP      /* !< TIM9 Channel1 is connected to GPIO */


#if defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define TIM_TIM10_TI1RMP              (0x00000000)       /* !< TIM10 Channel 1 depends on TI1_RMP */
#define TIM_TIM10_RI                  TIM_OR_TI1_RMP_RI  /* !< TIM10 Channel 1 is connected to RI */
#define TIM_TIM10_ETR_LSE             (0x00000000)       /* !< TIM10 ETR input is connected to LSE clock */
#define TIM_TIM10_ETR_TIM9_TGO        TIM_OR_ETR_RMP     /* !< TIM10 ETR input is connected to TIM9 TGO */
#endif /* defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) */
#define TIM_TIM10_GPIO                (0x00000000) /* !< TIM10 Channel1 is connected to GPIO */
#define TIM_TIM10_LSI                 TIM_OR_TI1RMP_0    /* !< TIM10 Channel1 is connected to LSI internal clock */
#define TIM_TIM10_LSE                 TIM_OR_TI1RMP_1    /* !< TIM10 Channel1 is connected to LSE internal clock */
#define TIM_TIM10_RTC                 TIM_OR_TI1RMP      /* !< TIM10 Channel1 is connected to RTC wakeup interrupt */

#if defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define TIM_TIM11_TI1RMP              (0x00000000)       /* !< TIM11 Channel 1 depends on TI1_RMP */
#define TIM_TIM11_RI                  TIM_OR_TI1_RMP_RI  /* !< TIM11 Channel 1 is connected to RI */
#define TIM_TIM11_ETR_LSE             (0x00000000)       /* !< TIM11 ETR input is connected to LSE clock */
#define TIM_TIM11_ETR_TIM9_TGO        TIM_OR_ETR_RMP     /* !< TIM11 ETR input is connected to TIM9 TGO */
#endif /* defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) */
#define TIM_TIM11_GPIO                (0x00000000)       /* !< TIM11 Channel1 is connected to GPIO */
#define TIM_TIM11_MSI                 TIM_OR_TI1RMP_0    /* !< TIM11 Channel1 is connected to MSI internal clock */
#define TIM_TIM11_HSE_RTC             TIM_OR_TI1RMP_1    /* !< TIM11 Channel1 is connected to HSE_RTC clock */
#define TIM_TIM11_GPIO1               TIM_OR_TI1RMP      /* !< TIM11 Channel1 is connected to GPIO */


#if defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)               \
        ( (((INSTANCE) == TIM2)  && (((TIM_REMAP) == TIM_TIM2_ITR1_TIM10_OC) || ((TIM_REMAP) == TIM_TIM2_ITR1_TIM5_TGO)))  || \
          (((INSTANCE) == TIM3)  && (((TIM_REMAP) == TIM_TIM3_ITR2_TIM11_OC) || ((TIM_REMAP) == TIM_TIM3_ITR2_TIM5_TGO)))  || \
          (((INSTANCE) == TIM9)  && ((TIM_REMAP) <= (TIM_TIM9_ITR1_TS | TIM_TIM9_GPIO2)))                                  || \
          (((INSTANCE) == TIM10) && ((TIM_REMAP) <= (TIM_TIM10_RI | TIM_TIM10_ETR_TIM9_TGO | TIM_TIM10_RTC)))              || \
          (((INSTANCE) == TIM11) && ((TIM_REMAP) <= (TIM_TIM11_RI | TIM_TIM11_ETR_TIM9_TGO | TIM_TIM11_GPIO1)))               \
        )
#else /* defined (STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) */
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)               \
        ( (((INSTANCE) == TIM9)  && (((TIM_REMAP) == TIM_TIM9_GPIO) || ((TIM_REMAP) == TIM_TIM9_LSE) || ((TIM_REMAP) == TIM_TIM9_GPIO1) || ((TIM_REMAP) == TIM_TIM9_GPIO2)))       || \
          (((INSTANCE) == TIM10) && (((TIM_REMAP) == TIM_TIM10_GPIO) || ((TIM_REMAP) == TIM_TIM10_LSI) || ((TIM_REMAP) == TIM_TIM10_LSE) || ((TIM_REMAP) == TIM_TIM10_RTC)))       || \
          (((INSTANCE) == TIM11) && (((TIM_REMAP) == TIM_TIM11_GPIO) || ((TIM_REMAP) == TIM_TIM11_MSI) || ((TIM_REMAP) == TIM_TIM11_HSE_RTC) || ((TIM_REMAP) == TIM_TIM11_GPIO1)))    \
        )
#endif 


/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup TIMEx_Exported_Functions
  * @{
  */ 

/** @addtogroup TIMEx_Exported_Functions_Group1
  * @{
  */
/* Extension Control functions  ************************************************/
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef * sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);
/**
  * @}
  */
  
/** @addtogroup TIMEx_Exported_Functions_Group2
  * @{
  */

/**
  * @}
  */

/* Extension Callback *********************************************************/

/** @addtogroup TIMEx_Exported_Functions_Group3
  * @{
  */

/**
  * @}
  */
/* Extension Peripheral State functions  **************************************/
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


#endif /* __STM32L1xx_HAL_TIM_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
