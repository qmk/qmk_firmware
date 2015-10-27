/**
  ******************************************************************************
  * @file    stm32f3xx_hal_uart_ex.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Extended UART HAL module driver.
  *
  *          This file provides firmware functions to manage the following extended
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (UART).
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  *           
  @verbatim       
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
    The UART HAL driver can be used as follows:
    
    (#) Declare a UART_HandleTypeDef handle structure.

    (#) For the UART RS485 Driver Enabled mode, initialize the UART registers 
        by calling the HAL_RS485Ex_Init() API.                                  
        

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

/** @defgroup UARTEx UART Extended HAL module driver
  * @brief UART Extended HAL module driver
  * @{
  */
#ifdef HAL_UART_MODULE_ENABLED
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/                                    
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup UARTEx_Exported_Functions UART Extended Exported Functions
  * @{
  */

/** @defgroup UARTEx_Exported_Functions_Group1 Extended Initialization and de-initialization functions
  * @brief    Extended Initialization and Configuration Functions
  *
@verbatim    
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to initialize the USARTx or the UARTy 
    in asynchronous mode.
      (+) For the asynchronous mode only these parameters can be configured: 
        (++) Baud Rate
        (++) Word Length 
        (++) Stop Bit
        (++) Parity: If the parity is enabled, then the MSB bit of the data written
             in the data register is transmitted but is changed by the parity bit.
             Depending on the frame length defined by the M bit (8-bits or 9-bits)
             or by the M1 and M0 bits (7-bit, 8-bit or 9-bit),
             the possible UART frame formats are as listed in the following table:
   +---------------------------------------------------------------+     
   |    M bit  |  PCE bit  |            UART frame                 |
   |-----------|-----------|---------------------------------------|             
   |     0     |     0     |    | SB | 8-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     0     |     1     |    | SB | 7-bit data | PB | STB |     |
   |-----------|-----------|---------------------------------------|  
   |     1     |     0     |    | SB | 9-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     1     |     1     |    | SB | 8-bit data | PB | STB |     |
   +---------------------------------------------------------------+     
   | M1M0 bits |  PCE bit  |            UART frame                 |
   |-----------------------|---------------------------------------|             
   |     10    |     0     |    | SB | 7-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     10    |     1     |    | SB | 6-bit data | PB | STB |     |   
   +---------------------------------------------------------------+            
        (++) Hardware flow control
        (++) Receiver/transmitter modes
        (++) Over Sampling Method
        (++) One-Bit Sampling Method
      (+) For the asynchronous mode, the following advanced features can be configured as well:
        (++) TX and/or RX pin level inversion
        (++) data logical level inversion
        (++) RX and TX pins swap
        (++) RX overrun detection disabling
        (++) DMA disabling on RX error
        (++) MSB first on communication line
        (++) auto Baud rate detection
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
  * @param UART_DEPolarity: select the driver enable polarity
  *        This parameter can be one of the following values:
  *          @arg UART_DE_POLARITY_HIGH: DE signal is active high
  *          @arg UART_DE_POLARITY_LOW: DE signal is active low
  * @param UART_DEAssertionTime: Driver Enable assertion time
  *                         5-bit value defining the time between the activation of the DE (Driver Enable)
  *                         signal and the beginning of the start bit. It is expressed in sample time
  *                         units (1/8 or 1/16 bit time, depending on the oversampling rate)         
  * @param UART_DEDeassertionTime: Driver Enable deassertion time          
  *                         5-bit value defining the time between the end of the last stop bit, in a
  *                         transmitted message, and the de-activation of the DE (Driver Enable) signal.
  *                         It is expressed in sample time units (1/8 or 1/16 bit time, depending on the
  *                         oversampling rate).        
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RS485Ex_Init(UART_HandleTypeDef *huart, uint32_t UART_DEPolarity, uint32_t UART_DEAssertionTime, uint32_t UART_DEDeassertionTime)
{
  uint32_t temp = 0x0;
  
  /* Check the UART handle allocation */
  if(huart == HAL_NULL)
  {
    return HAL_ERROR;
  }
  /* Check the Driver Enable UART instance */
  assert_param(IS_UART_DRIVER_ENABLE_INSTANCE(huart->Instance));
  
  /* Check the Driver Enable polarity */
  assert_param(IS_UART_DE_POLARITY(UART_DEPolarity));
  
  /* Check the Driver Enable assertion time */
  assert_param(IS_UART_ASSERTIONTIME(UART_DEAssertionTime));
  
  /* Check the Driver Enable deassertion time */
  assert_param(IS_UART_DEASSERTIONTIME(UART_DEDeassertionTime));
  
  if(huart->State == HAL_UART_STATE_RESET)
  {   
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_UART_MspInit(huart);
  }
  
  huart->State = HAL_UART_STATE_BUSY;
  
  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);
  
  /* Set the UART Communication parameters */
  if (UART_SetConfig(huart) == HAL_ERROR)
  {
    return HAL_ERROR;
  } 
  
  if (huart->AdvancedInit.AdvFeatureInit != UART_ADVFEATURE_NO_INIT)
  {
    UART_AdvFeatureConfig(huart);
  }
  
  /* Enable the Driver Enable mode by setting the DEM bit in the CR3 register */
  huart->Instance->CR3 |= USART_CR3_DEM;
  
  /* Set the Driver Enable polarity */
  MODIFY_REG(huart->Instance->CR3, USART_CR3_DEP, UART_DEPolarity);
  
  /* Set the Driver Enable assertion and deassertion times */
  temp = (UART_DEAssertionTime << UART_CR1_DEAT_ADDRESS_LSB_POS);
  temp |= (UART_DEDeassertionTime << UART_CR1_DEDT_ADDRESS_LSB_POS);
  MODIFY_REG(huart->Instance->CR1, (USART_CR1_DEDT|USART_CR1_DEAT), temp);
  
  /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart);
  
  /* TEACK and/or REACK to check before moving huart->State to Ready */
  return (UART_CheckIdleState(huart));
}


/**
  * @}
  */

/** @defgroup UARTEx_Exported_Functions_Group2 Extended Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides an extended function allowing to control the UART.
     (+) HAL_MultiProcessorEx_AddressLength_Set() API optionally sets the UART node address
         detection length to more than 4 bits for multiprocessor address mark wake up. 
     (+) HAL_UARTEx_StopModeWakeUpSourceConfig() configures the address for wake-up from
          Stop mode based on address match
     (+) HAL_UARTEx_EnableStopMode() API enables the UART to wake up the MCU from stop mode   
     (+) HAL_UARTEx_DisableStopMode() API disables the above functionality                     
@endverbatim
  * @{
  */



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
  if(huart == HAL_NULL)
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
  /* check the wake-up selection parameter */
  assert_param(IS_UART_WAKEUP_SELECTION(WakeUpSelection.WakeUpEvent));
  
  /* Process Locked */
  __HAL_LOCK(huart);
  
  huart->State = HAL_UART_STATE_BUSY;
  
  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);

  /* Set the wake-up selection scheme */
  MODIFY_REG(huart->Instance->CR3, USART_CR3_WUS, WakeUpSelection.WakeUpEvent);
  
  if (WakeUpSelection.WakeUpEvent == UART_WAKEUP_ON_ADDRESS)
  {
    UART_Wakeup_AddressConfig(huart, WakeUpSelection);
  }
  
  /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart);
  
  /* Wait until REACK flag is set */
  if(UART_WaitOnFlagUntilTimeout(huart, USART_ISR_REACK, RESET, HAL_UART_TIMEOUT_VALUE) != HAL_OK)  
  { 
    return HAL_TIMEOUT;
  }
  else
  {
    /* Initialize the UART State */
    huart->State= HAL_UART_STATE_READY;
    /* Process Unlocked */
    __HAL_UNLOCK(huart);  
    return HAL_OK;
  }
}


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
  * @}
  */

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
