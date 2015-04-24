/**
  ******************************************************************************
  * @file    stm32f3xx_hal_pcd_ex.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file of PCD HAL Extended module.
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
#ifndef __STM32F3xx_HAL_PCD_EX_H
#define __STM32F3xx_HAL_PCD_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F302x8)                         || \
    defined(STM32F373xC)

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup PCDEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/                                              
/** @defgroup PCDEx_Exported_Macros PCD Extended Exported Macros
  * @{
  */
/**
  * @brief  Gets address in an endpoint register.
  * @param  USBx: USB peripheral instance register address.
  * @param  bEpNum: Endpoint Number.
  * @retval None
  */
   
#if defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F373xC)
      
#define PCD_EP_TX_ADDRESS(USBx, bEpNum) ((uint32_t *)((USBx->BTABLE+bEpNum*8)*2+     ((uint32_t)USBx + 0x400)))
#define PCD_EP_TX_CNT(USBx, bEpNum) ((uint32_t *)((USBx->BTABLE+bEpNum*8+2)*2+  ((uint32_t)USBx + 0x400)))
#define PCD_EP_RX_ADDRESS(USBx, bEpNum) ((uint32_t *)((USBx->BTABLE+bEpNum*8+4)*2+  ((uint32_t)USBx + 0x400)))
#define PCD_EP_RX_CNT(USBx, bEpNum) ((uint32_t *)((USBx->BTABLE+bEpNum*8+6)*2+  ((uint32_t)USBx + 0x400)))
      
#define PCD_SET_EP_RX_CNT(USBx, bEpNum,wCount) {\
    uint32_t *pdwReg = PCD_EP_RX_CNT(USBx, bEpNum); \
    PCD_SET_EP_CNT_RX_REG(pdwReg, wCount);\
  }    

#endif /* STM32F302xC || STM32F303xC || */
       /* STM32F373xC                   */
   
      
#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302x8)
           
#define PCD_EP_TX_ADDRESS(USBx, bEpNum) ((uint16_t *)((USBx->BTABLE+bEpNum*8)+     ((uint32_t)USBx + 0x400)))
#define PCD_EP_TX_CNT(USBx, bEpNum) ((uint16_t *)((USBx->BTABLE+bEpNum*8+2)+  ((uint32_t)USBx + 0x400)))
#define PCD_EP_RX_ADDRESS(USBx, bEpNum) ((uint16_t *)((USBx->BTABLE+bEpNum*8+4)+  ((uint32_t)USBx + 0x400)))
#define PCD_EP_RX_CNT(USBx, bEpNum) ((uint16_t *)((USBx->BTABLE+bEpNum*8+6)+  ((uint32_t)USBx + 0x400)))

#define PCD_SET_EP_RX_CNT(USBx, bEpNum,wCount) {\
    uint16_t *pdwReg = PCD_EP_RX_CNT(USBx, bEpNum); \
    PCD_SET_EP_CNT_RX_REG(pdwReg, wCount);\
  }

#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302x8                   */
/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PCDEx_Exported_Functions PCD Extended Exported Functions
  * @{
  */
/** @addtogroup PCDEx_Exported_Functions_Group1 Extended Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions
  * @{
  */
HAL_StatusTypeDef HAL_PCDEx_PMAConfig(PCD_HandleTypeDef *hpcd, 
                                     uint16_t ep_addr,
                                     uint16_t ep_kind,
                                     uint32_t pmaadress);

 __weak void HAL_PCDEx_SetConnectionState(PCD_HandleTypeDef *hpcd, uint8_t state);

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

#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302xC || STM32F303xC || */
       /* STM32F302x8                || */
       /* STM32F373xC                   */

#ifdef __cplusplus
}
#endif


#endif /* __STM32F3xx_HAL_PCD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
