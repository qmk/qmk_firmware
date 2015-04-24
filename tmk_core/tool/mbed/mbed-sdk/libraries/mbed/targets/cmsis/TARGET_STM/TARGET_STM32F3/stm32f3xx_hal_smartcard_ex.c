/**
  ******************************************************************************
  * @file    stm32f3xx_hal_smartcard_ex.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   SMARTCARD HAL module driver.
  *
  *          This file provides extended firmware functions to manage the following 
  *          functionalities of the SmartCard.
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  *           
  @verbatim       
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
    The Extended SMARTCARD HAL driver can be used as follows:
  
        
    (#) After having configured the SMARTCARD basic features with HAL_SMARTCARD_Init(), 
        then if required, program SMARTCARD advanced features (TX/RX pins swap, TimeOut, 
        auto-retry counter,...) in the hsmartcard AdvancedInit structure.



  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @defgroup SMARTCARDEx SMARTCARD Extended HAL module driver
  * @brief SMARTCARD Extended HAL module driver
  * @{
  */
#ifdef HAL_SMARTCARD_MODULE_ENABLED
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions ---------------------------------------------------------*/

/** @defgroup SMARTCARDEx_Exported_Functions SMARTCARD Extended Exported Functions
  * @{
  */

/** @defgroup SMARTCARDEx_Exported_Functions_Group1 Extended Peripheral Control functions
  * @brief    Extended control functions
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to initialize the SMARTCARD.
     (+) HAL_SMARTCARDEx_BlockLength_Config() API allows to configure the Block Length on the fly 
     (+) HAL_SMARTCARDEx_TimeOut_Config() API allows to configure the receiver timeout value on the fly  
     (+) HAL_SMARTCARDEx_EnableReceiverTimeOut() API enables the receiver timeout feature
     (+) HAL_SMARTCARDEx_DisableReceiverTimeOut() API disables the receiver timeout feature                      
               
@endverbatim
  * @{
  */





/**
  * @brief Update on the fly the SMARTCARD block length in RTOR register
  * @param hsmartcard: SMARTCARD handle
  * @param BlockLength: SMARTCARD block length (8-bit long at most)  
  * @retval None
  */
void HAL_SMARTCARDEx_BlockLength_Config(SMARTCARD_HandleTypeDef *hsmartcard, uint8_t BlockLength)
{
  MODIFY_REG(hsmartcard->Instance->RTOR, USART_RTOR_BLEN, ((uint32_t)BlockLength << SMARTCARD_RTOR_BLEN_LSB_POS));
}

/**
  * @brief Update on the fly the receiver timeout value in RTOR register
  * @param hsmartcard: SMARTCARD handle
  * @param TimeOutValue: receiver timeout value in number of baud blocks. The timeout
  *                     value must be less or equal to 0x0FFFFFFFF. 
  * @retval None
  */
void HAL_SMARTCARDEx_TimeOut_Config(SMARTCARD_HandleTypeDef *hsmartcard, uint32_t TimeOutValue)
{
  assert_param(IS_SMARTCARD_TIMEOUT_VALUE(hsmartcard->Init.TimeOutValue));
  MODIFY_REG(hsmartcard->Instance->RTOR, USART_RTOR_RTO, TimeOutValue); 
}

/**
  * @brief Enable the SMARTCARD receiver timeout feature
  * @param hsmartcard: SMARTCARD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARDEx_EnableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsmartcard)
{
 
  /* Process Locked */
  __HAL_LOCK(hsmartcard);
  
  hsmartcard->State = HAL_SMARTCARD_STATE_BUSY;
  
  /* Set the USART RTOEN bit */
  hsmartcard->Instance->CR2 |= USART_CR2_RTOEN;
  
  hsmartcard->State = HAL_SMARTCARD_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hsmartcard);
  
  return HAL_OK;   
}

/**
  * @brief Disable the SMARTCARD receiver timeout feature
  * @param hsmartcard: SMARTCARD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARDEx_DisableReceiverTimeOut(SMARTCARD_HandleTypeDef *hsmartcard)
{
 
  /* Process Locked */
  __HAL_LOCK(hsmartcard);
  
  hsmartcard->State = HAL_SMARTCARD_STATE_BUSY;
  
  /* Clear the USART RTOEN bit */
  hsmartcard->Instance->CR2 &= ~(USART_CR2_RTOEN);
  
  hsmartcard->State = HAL_SMARTCARD_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hsmartcard);
  
  return HAL_OK;   
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_SMARTCARD_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
