/**
  ******************************************************************************
  * @file    stm32f0xx_hal_pcd_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file of PCD HAL Extension module.
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
#ifndef __STM32L0xx_HAL_PCD_EX_H
#define __STM32L0xx_HAL_PCD_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F072xB) || defined(STM32F078xx)|| defined(STM32F070xB)|| defined(STM32F070x6)

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"  
   
/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup PCDEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Internal macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup PCDEx_Exported_Functions
  * @{
  */
  
/** @addtogroup PCDEx_Exported_Functions_Group2
  * @{
  */
   
HAL_StatusTypeDef HAL_PCDEx_PMAConfig(PCD_HandleTypeDef *hpcd, 
                                     uint16_t ep_addr,
                                     uint16_t ep_kind,
                                     uint32_t pmaadress);
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

#endif /* STM32F042x6 || STM32F072xB || STM32F078xx || STM32F070xB || STM32F070x6*/

#ifdef __cplusplus
}
#endif


#endif /* __STM32F0xx_HAL_PCD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

