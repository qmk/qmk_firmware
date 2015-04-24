/**
  ******************************************************************************
  * @file    stm32f1xx_hal_can_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of CAN HAL Extension module.
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
#ifndef __STM32F1xx_HAL_CAN_EX_H
#define __STM32F1xx_HAL_CAN_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || \
    defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC)

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup CANEx CANEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
      
/** 
  * @brief  CAN filter configuration structure definition
  */
/* CAN filter banks differences over STM32F1 devices:                         */
/* - STM32F1 Connectivity line: 28 filter banks shared between CAN1 and CAN2  */
/* - Other STM32F10x devices:   14 filter banks                               */

typedef struct
{
  uint32_t FilterIdHigh;          /*!< Specifies the filter identification number (MSBs for a 32-bit
                                       configuration, first one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 
                                              
  uint32_t FilterIdLow;           /*!< Specifies the filter identification number (LSBs for a 32-bit
                                       configuration, second one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 

  uint32_t FilterMaskIdHigh;      /*!< Specifies the filter mask number or identification number,
                                       according to the mode (MSBs for a 32-bit configuration,
                                       first one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 

  uint32_t FilterMaskIdLow;       /*!< Specifies the filter mask number or identification number,
                                       according to the mode (LSBs for a 32-bit configuration,
                                       second one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 

  uint32_t FilterFIFOAssignment;  /*!< Specifies the FIFO (0 or 1) which will be assigned to the filter.
                                       This parameter can be a value of @ref CAN_filter_FIFO */
#if defined(STM32F105xC) || defined(STM32F107xC)
  uint32_t FilterNumber;          /*!< Specifies the filter which will be initialized. 
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 27. */
#else
  uint32_t FilterNumber;          /*!< Specifies the filter which will be initialized. 
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 13. */
#endif /* STM32F105xC || STM32F107xC */
  uint32_t FilterMode;            /*!< Specifies the filter mode to be initialized.
                                       This parameter can be a value of @ref CAN_filter_mode */

  uint32_t FilterScale;           /*!< Specifies the filter scale.
                                       This parameter can be a value of @ref CAN_filter_scale */

  uint32_t FilterActivation;      /*!< Enable or disable the filter.
                                       This parameter can be set to ENABLE or DISABLE. */
                                       
  uint32_t BankNumber;            /*!< Select the start slave bank filter
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 28. */ 
  
}CAN_FilterConfTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/** @defgroup CANEx_Private_Macros CAN Extended Private Macros
  * @{
  */
#if defined(STM32F105xC) || defined(STM32F107xC)
#define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 27)
#else
#define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 13)
#endif /* STM32F105xC || STM32F107xC */

/**
  * @}
  */


/**
  * @}
  */ 

/**
  * @}
  */

#endif /* STM32F103x6) || STM32F103xB || STM32F103xE || */
       /* STM32F103xG) || STM32F105xC || STM32F107xC    */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_CAN_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
