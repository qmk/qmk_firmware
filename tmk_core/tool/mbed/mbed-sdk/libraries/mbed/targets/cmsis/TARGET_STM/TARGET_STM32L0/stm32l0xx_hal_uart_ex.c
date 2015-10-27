/**
  ******************************************************************************
  * @file    stm32l0xx_hal_uart_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Extended UART HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Inter Integrated Circuit (UART) peripheral:
  *           + Extended Control methods
  *         
  @verbatim
  ==============================================================================
               ##### UART peripheral extended features  #####
  ==============================================================================
           
  [..] Comparing to other previous devices, the UART interface for STM32L0XX
       devices contains the following additional features
       
       (+) Possibility to disable or enable Analog Noise Filter
       (+) Use of a configured Digital Noise Filter
       (+) Disable or enable wakeup from Stop mode
   
                     ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to configure Noise Filter
  
  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup UARTEx
  * @brief UARTEx module driver
  * @{
  */

#ifdef HAL_UART_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define UART_REACK_TIMEOUT       ((uint32_t) 1000)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void UART_Wakeup_AddressConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection);
/* Private functions ---------------------------------------------------------*/

/** @addtogroup UARTEx_Exported_Functions
  * @{
  */

/** @addtogroup UARTEx_Exported_Functions_Group1
  * @brief    Extended Initialization and Configuration Functions

  *
@verbatim    
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]
    The HAL_RS485Ex_Init() API follows respectively the UART RS485 mode 
    configuration procedures (details for the procedures are available in reference manual).

@endverbatim
  * @{
  */

/**
  * @brief Initializes the RS485 Driver enable feature according to the specified
  *         parameters in the UART_InitTypeDef and creates the associated handle .
  * @param huart: uart handle
  * @param Polarity: select the driver enable polarity
  *        This parameter can be one of the following values:
  *          @arg UART_DE_POLARITY_HIGH: DE signal is active high
  *          @arg UART_DE_POLARITY_LOW: DE signal is active low
  * @param AssertionTime: Driver Enable assertion time
  *                         5-bit value defining the time between the activation of the DE (Driver Enable)
  *                         signal and the beginning of the start bit. It is expressed in sample time
  *                         units (1/8 or 1/16 bit time, depending on the oversampling rate)         
  * @param DeassertionTime: Driver Enable deassertion time          
  *                         5-bit value defining the time between the end of the last stop bit, in a
  *                         transmitted message, and the de-activation of the DE (Driver Enable) signal.
  *                         It is expressed in sample time units (1/8 or 1/16 bit time, depending on the
  *                         oversampling rate).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RS485Ex_Init(UART_HandleTypeDef *huart, uint32_t Polarity, uint32_t AssertionTime, uint32_t DeassertionTime)
{
  uint32_t temp = 0x0;
  
  /* Check the UART handle allocation */
  if(huart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the Driver Enable polarity */
  assert_param(IS_UART_DE_POLARITY(Polarity));
  
  /* Check the Driver Enable assertion time */
  assert_param(IS_UART_ASSERTIONTIME(AssertionTime));
  
  /* Check the Driver Enable deassertion time */
  assert_param(IS_UART_DEASSERTIONTIME(DeassertionTime));
  
  if(huart->State == HAL_UART_STATE_RESET)
  {   
    /* Init the low level hardware : GPIO, CLOCK, CORTEX */
    HAL_UART_MspInit(huart);
  }

  huart->State = HAL_UART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);
  
  /* Set the UART Communication parameters */
  UART_SetConfig(huart);
  
  if(huart->AdvancedInit.AdvFeatureInit != UART_ADVFEATURE_NO_INIT)
  {
    UART_AdvFeatureConfig(huart);
  }
  
  /* Enable the Driver Enable mode by setting the DEM bit in the CR3 register */
  huart->Instance->CR3 |= USART_CR3_DEM;
  
  /* Set the Driver Enable polarity */
  MODIFY_REG(huart->Instance->CR3, USART_CR3_DEP, Polarity);
  
  /* Set the Driver Enable assertion and deassertion times */
  temp = (AssertionTime << UART_CR1_DEAT_ADDRESS_LSB_POS);
  temp |= (DeassertionTime << UART_CR1_DEDT_ADDRESS_LSB_POS);
  MODIFY_REG(huart->Instance->CR1, (USART_CR1_DEDT|USART_CR1_DEAT), temp);
  
  /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart);
  
  /* TEACK and/or REACK to check before moving huart->State to Ready */
  return (UART_CheckIdleState(huart));
}


/**
  * @}
  */
  
/** @addtogroup UARTEx_Exported_Functions_Group2
 *  @brief   management functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control funtions #####
 ===============================================================================  
    [..] This section provides functions allowing to:
     (+) UART_AdvFeatureConfig() API optionally configures the UART advanced features 
     (+) HAL_MultiProcessorEx_AddressLength_Set() API optionally sets the UART node address
         detection length to more than 4 bits for multiprocessor address mark wake up.
     (+) HAL_UARTEx_EnableStopMode() API enables the UART to wake up the MCU from stop mode   
     (+) HAL_UARTEx_DisableStopMode() API disables the above functionality
     (+) HAL_UARTEx_EnableClockStopMode() API enables the UART HSI clock during stop mode   
     (+) HAL_UARTEx_DisableClockStopMode() API disables the above functionality   
     (+) UART_Wakeup_AddressConfig() API configures the wake-up from stop mode parameters

@endverbatim
  * @{
  */
  
/**
  * @brief Enable UART Stop Mode
  * The UART is able to wake up the MCU from Stop mode as long as UART clock is HSI or LSE
  * @param huart: uart handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UARTEx_EnableStopMode(UART_HandleTypeDef *huart)
{
  /* Process Locked */
  __HAL_LOCK(huart);
  
  huart->State = HAL_UART_STATE_BUSY;
  
  /* Set the USART UESM bit */
  huart->Instance->CR1 |= USART_CR1_UESM;
  
  huart->State = HAL_UART_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(huart);
  
  return HAL_OK; 
}

/**
  * @brief Enable UART Clock in Stop Mode
  * The UART keeps the Clock ON during Stop mode
  * @param huart: uart handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UARTEx_EnableClockStopMode(UART_HandleTypeDef *huart)
{
  /* Process Locked */
  __HAL_LOCK(huart);
  
  huart->State = HAL_UART_STATE_BUSY;
  
  /* Set the USART UESM bit */
  huart->Instance->CR3 |= USART_CR3_UCESM;
  
  huart->State = HAL_UART_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(huart);
  
  return HAL_OK; 
}

/**
  * @brief Disable UART Stop Mode 
  * @param huart: uart handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UARTEx_DisableStopMode(UART_HandleTypeDef *huart)
{
  /* Process Locked */
  __HAL_LOCK(huart);

  huart->State = HAL_UART_STATE_BUSY; 

  /* Clear USART UESM bit */
  huart->Instance->CR1 &= ~(USART_CR1_UESM);
  
  huart->State = HAL_UART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(huart);

  return HAL_OK;
}

/**
  * @brief Disable UART Clock in Stop Mode 
  * @param huart: uart handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UARTEx_DisableClockStopMode(UART_HandleTypeDef *huart)
{
  /* Process Locked */
  __HAL_LOCK(huart);

  huart->State = HAL_UART_STATE_BUSY;

  /* Clear USART UESM bit */
  huart->Instance->CR3 &= ~(USART_CR3_UCESM);

  huart->State = HAL_UART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(huart);

  return HAL_OK;
}

/**
  * @brief Set Wakeup from Stop mode interrupt flag selection
  * @param huart: uart handle, 
  * @param WakeUpSelection: address match, Start Bit detection or RXNE bit status.
  * This parameter can be one of the following values:
  *      @arg UART_WAKEUP_ON_ADDRESS
  *      @arg UART_WAKEUP_ON_STARTBIT
  *      @arg UART_WAKEUP_ON_READDATA_NONEMPTY
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UARTEx_StopModeWakeUpSourceConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection)
{

  /* check the wake-up from stop mode UART instance */
  assert_param(IS_UART_WAKEUP_FROMSTOP_INSTANCE(huart->Instance));
  /* Check the wake-up selection parameter */
  assert_param(IS_UART_WAKEUP_SELECTION(WakeUpSelection.WakeUpEvent));

  /* Process Locked */
  __HAL_LOCK(huart);

  huart->State = HAL_UART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);

  /* Set the wake-up selection scheme */
  MODIFY_REG(huart->Instance->CR3, USART_CR3_WUS, WakeUpSelection.WakeUpEvent);

  if(WakeUpSelection.WakeUpEvent == UART_WAKEUP_ON_ADDRESS)
  {
    UART_Wakeup_AddressConfig(huart, WakeUpSelection);
  }

  /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart);

  /* Wait until REACK flag is set before moving huart->State to Ready */
  if(UART_WaitOnFlagUntilTimeout(huart, USART_ISR_REACK, RESET, UART_REACK_TIMEOUT) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  /* Process Unlocked */
  __HAL_UNLOCK(huart);

  /* Initialize the UART state*/
  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->State= HAL_UART_STATE_READY;

  return HAL_OK;
}
/**
  * @brief By default in multiprocessor mode, when the wake up method is set 
  *        to address mark, the UART handles only 4-bit long addresses detection. 
  *        This API allows to enable longer addresses detection (6-, 7- or 8-bit
  *        long):
  *        - 6-bit address detection in 7-bit data mode
  *        - 7-bit address detection in 8-bit data mode
  *        - 8-bit address detection in 9-bit data mode
  * @param huart: UART handle
  * @param AddressLength: this parameter can be one of the following values:
  *          @arg UART_ADDRESS_DETECT_4B: 4-bit long address
  *          @arg UART_ADDRESS_DETECT_7B: 6-, 7- or 8-bit long address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MultiProcessorEx_AddressLength_Set(UART_HandleTypeDef *huart, uint32_t AddressLength)
{
  /* Check the UART handle allocation */
  if(huart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address length parameter */
  assert_param(IS_UART_ADDRESSLENGTH_DETECT(AddressLength));
  
  huart->State = HAL_UART_STATE_BUSY;
  
  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);
  
  /* Set the address length */
  MODIFY_REG(huart->Instance->CR2, USART_CR2_ADDM7, AddressLength);
  
  /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart); 
  
  /* TEACK and/or REACK to check before moving huart->State to Ready */
  return (UART_CheckIdleState(huart));
}

/**
  * @}
  */  

/**
  * @brief Initializes the UART wake-up from stop mode parameters when triggered by address detection.
  * @param huart: uart handle
  * @param WakeUpSelection: UART wake up from stop mode parameters
  * @retval HAL status
  */                        
static void UART_Wakeup_AddressConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection)
{
  assert_param(IS_UART_ADDRESSLENGTH_DETECT(WakeUpSelection.AddressLength));
  if(WakeUpSelection.AddressLength == UART_ADDRESS_DETECT_4B)
  {
    assert_param(IS_UART_4B_ADDRESS(WakeUpSelection.Address));
  }
  else
  {
    assert_param(IS_UART_7B_ADDRESS(WakeUpSelection.Address));
  }

  /* Set the USART address length */
  MODIFY_REG(huart->Instance->CR2, USART_CR2_ADDM7, WakeUpSelection.AddressLength);

  /* Set the USART address node */
  MODIFY_REG(huart->Instance->CR2, USART_CR2_ADD, ((uint32_t)WakeUpSelection.Address << UART_CR2_ADDRESS_LSB_POS));
}

/**
  * @brief UART wakeup from Stop mode callback
  * @param huart: uart handle
  * @retval None
  */
 __weak void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_WakeupCallback can be implemented in the user file
   */
}

/**
  * @}
  */

#endif /* HAL_UART_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

