/**
  ******************************************************************************
  * @file    stm32l1xx_hal_irda.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   IRDA HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the IrDA SIR ENDEC block (IrDA):
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
    The IRDA HAL driver can be used as follows:

    (#) Declare a IRDA_HandleTypeDef handle structure.
    (#) Initialize the IRDA low level resources by implementing the HAL_IRDA_MspInit() API:
        (##) Enable the USARTx interface clock.
        (##) IRDA pins configuration:
            (+++) Enable the clock for the IRDA GPIOs.
            (+++) Configure these IRDA pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (HAL_IRDA_Transmit_IT()
             and HAL_IRDA_Receive_IT() APIs):
            (+++) Configure the USARTx interrupt priority.
            (+++) Enable the NVIC USART IRQ handle.
        (##) DMA Configuration if you need to use DMA process (HAL_IRDA_Transmit_DMA()
             and HAL_IRDA_Receive_DMA() APIs):
            (+++) Declare a DMA handle structure for the Tx/Rx channel.
            (+++) Enable the DMAx interface clock.
            (+++) Configure the declared DMA handle structure with the required Tx/Rx parameters.
            (+++) Configure the DMA Tx/Rx channel.
            (+++) Associate the initilalized DMA handle to the IRDA DMA Tx/Rx handle.
            (+++) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx channel.

    (#) Program the Baud Rate, Word Length, Parity, IrDA Mode, Prescaler 
        and Mode(Receiver/Transmitter) in the hirda Init structure.

    (#) Initialize the IRDA registers by calling the HAL_IRDA_Init() API:
        (++) This API configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
             by calling the customed HAL_IRDA_MspInit() API.

        -@@- The specific IRDA interrupts (Transmission complete interrupt, 
             RXNE interrupt and Error Interrupts) will be managed using the macros
             __HAL_IRDA_ENABLE_IT() and __HAL_IRDA_DISABLE_IT() inside the transmit and receive process.
          
    (#) Three operation modes are available within this driver :
 
     *** Polling mode IO operation ***
     =================================
     [..]    
       (+) Send an amount of data in blocking mode using HAL_IRDA_Transmit() 
       (+) Receive an amount of data in blocking mode using HAL_IRDA_Receive()
       
     *** Interrupt mode IO operation ***    
     ===================================
     [..]    
       (+) Send an amount of data in non blocking mode using HAL_IRDA_Transmit_IT() 
       (+) At transmission end of transfer HAL_IRDA_TxCpltCallback is executed and user can 
            add his own code by customization of function pointer HAL_IRDA_TxCpltCallback
       (+) Receive an amount of data in non blocking mode using HAL_IRDA_Receive_IT() 
       (+) At reception end of transfer HAL_IRDA_RxCpltCallback is executed and user can 
            add his own code by customization of function pointer HAL_IRDA_RxCpltCallback                                      
       (+) In case of transfer Error, HAL_IRDA_ErrorCallback() function is executed and user can 
            add his own code by customization of function pointer HAL_IRDA_ErrorCallback

     *** DMA mode IO operation ***    
     ==============================
     [..] 
       (+) Send an amount of data in non blocking mode (DMA) using HAL_IRDA_Transmit_DMA() 
       (+) At transmission end of transfer HAL_IRDA_TxCpltCallback is executed and user can 
            add his own code by customization of function pointer HAL_IRDA_TxCpltCallback
       (+) Receive an amount of data in non blocking mode (DMA) using HAL_IRDA_Receive_DMA() 
       (+) At reception end of transfer HAL_IRDA_RxCpltCallback is executed and user can 
            add his own code by customization of function pointer HAL_IRDA_RxCpltCallback                                      
       (+) In case of transfer Error, HAL_IRDA_ErrorCallback() function is executed and user can 
            add his own code by customization of function pointer HAL_IRDA_ErrorCallback

     *** IRDA HAL driver macros list ***
     ====================================
     [..]
       Below the list of most used macros in IRDA HAL driver.
       
       (+) __HAL_IRDA_ENABLE: Enable the IRDA peripheral 
       (+) __HAL_IRDA_DISABLE: Disable the IRDA peripheral     
       (+) __HAL_IRDA_GET_FLAG : Check whether the specified IRDA flag is set or not
       (+) __HAL_IRDA_CLEAR_FLAG : Clear the specified IRDA pending flag
       (+) __HAL_IRDA_ENABLE_IT: Enable the specified IRDA interrupt
       (+) __HAL_IRDA_DISABLE_IT: Disable the specified IRDA interrupt
      
     [..] 
       (@) You can refer to the IRDA HAL driver header file for more useful macros

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
#include "stm32l1xx_hal.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup IRDA IRDA
  * @brief HAL IRDA module driver
  * @{
  */

#ifdef HAL_IRDA_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup IRDA_Private_Constants   IRDA Private Constants
  * @{
  */
#define IRDA_TIMEOUT_VALUE  22000
#define IRDA_DR_MASK_U16_7DATABITS  (uint16_t)0x007F
#define IRDA_DR_MASK_U16_8DATABITS  (uint16_t)0x00FF
#define IRDA_DR_MASK_U16_9DATABITS  (uint16_t)0x01FF

#define IRDA_DR_MASK_U8_7DATABITS  (uint8_t)0x7F
#define IRDA_DR_MASK_U8_8DATABITS  (uint8_t)0xFF


/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup IRDA_Private_Functions   IRDA Private Functions
  * @{
  */
static HAL_StatusTypeDef IRDA_Transmit_IT(IRDA_HandleTypeDef *hirda);
static HAL_StatusTypeDef IRDA_EndTransmit_IT(IRDA_HandleTypeDef *hirda);
static HAL_StatusTypeDef IRDA_Receive_IT(IRDA_HandleTypeDef *hirda);
static void IRDA_SetConfig (IRDA_HandleTypeDef *hirda);
static void IRDA_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void IRDA_DMATransmitHalfCplt(DMA_HandleTypeDef *hdma);
static void IRDA_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void IRDA_DMAReceiveHalfCplt(DMA_HandleTypeDef *hdma);
static void IRDA_DMAError(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef IRDA_WaitOnFlagUntilTimeout(IRDA_HandleTypeDef *hirda, uint32_t Flag, FlagStatus Status, uint32_t Timeout);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup IRDA_Exported_Functions IRDA Exported Functions
  * @{
  */

/** @defgroup IRDA_Exported_Functions_Group1 IrDA Initialization and de-initialization functions 
  *  @brief    Initialization and Configuration functions 
  *
@verbatim
  ==============================================================================
              ##### Initialization and Configuration functions #####
  ==============================================================================
  [..]
  This subsection provides a set of functions allowing to initialize the USARTx or the UARTy 
  in IrDA mode.
  (+) For the asynchronous mode only these parameters can be configured: 
      (++) Baud Rate
      (++) Word Length 
      (++) Parity: If the parity is enabled, then the MSB bit of the data written
           in the data register is transmitted but is changed by the parity bit.
           Depending on the frame length defined by the M bit (8-bits or 9-bits),
           the possible IRDA frame formats are as listed in the following table:
   +-------------------------------------------------------------+
   |   M bit |  PCE bit  |            IRDA frame                |
   |---------------------|---------------------------------------|
   |    0    |    0      |    | SB | 8 bit data | STB |          |
   |---------|-----------|---------------------------------------|
   |    0    |    1      |    | SB | 7 bit data | PB | STB |     |
   |---------|-----------|---------------------------------------|
   |    1    |    0      |    | SB | 9 bit data | STB |          |
   |---------|-----------|---------------------------------------|
   |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
   +-------------------------------------------------------------+
      (++) Prescaler: A pulse of width less than two and greater than one PSC period(s) may or may
           not be rejected. The receiver set up time should be managed by software. The IrDA physical layer
           specification specifies a minimum of 10 ms delay between transmission and 
           reception (IrDA is a half duplex protocol).
      (++) Mode: Receiver/transmitter modes
      (++) IrDAMode: the IrDA can operate in the Normal mode or in the Low power mode.

  [..]
    The HAL_IRDA_Init() function follows IRDA configuration procedures (details for the procedures
    are available in reference manual (RM0038)).

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the IRDA mode according to the specified
  *         parameters in the IRDA_InitTypeDef and create the associated handle.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Init(IRDA_HandleTypeDef *hirda)
{
  /* Check the IRDA handle allocation */
  if(hirda == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the IRDA instance parameters */
  assert_param(IS_IRDA_INSTANCE(hirda->Instance));
  /* Check the IRDA mode parameter in the IRDA handle */
  assert_param(IS_IRDA_POWERMODE(hirda->Init.IrDAMode)); 
  
  if(hirda->State == HAL_IRDA_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_IRDA_MspInit(hirda);
  }
  
  hirda->State = HAL_IRDA_STATE_BUSY;
  
  /* Disable the IRDA peripheral */
  __HAL_IRDA_DISABLE(hirda);
  
  /* Set the IRDA communication parameters */
  IRDA_SetConfig(hirda);
  
  /* In IrDA mode, the following bits must be kept cleared: 
     - LINEN, STOP and CLKEN bits in the USART_CR2 register,
     - SCEN and HDSEL bits in the USART_CR3 register.*/
  CLEAR_BIT(hirda->Instance->CR2, (USART_CR2_LINEN | USART_CR2_STOP | USART_CR2_CLKEN));
  CLEAR_BIT(hirda->Instance->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL));
  
  /* Enable the IRDA peripheral */
  __HAL_IRDA_ENABLE(hirda);
  
  /* Set the prescaler */
  MODIFY_REG(hirda->Instance->GTPR, USART_GTPR_PSC, hirda->Init.Prescaler);
  
  /* Configure the IrDA mode */
  MODIFY_REG(hirda->Instance->CR3, USART_CR3_IRLP, hirda->Init.IrDAMode);
  
  /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
  SET_BIT(hirda->Instance->CR3, USART_CR3_IREN);
  
  /* Initialize the IRDA state*/
  hirda->ErrorCode = HAL_IRDA_ERROR_NONE;
  hirda->State= HAL_IRDA_STATE_READY;
  
  return HAL_OK;
}

/**
  * @brief  DeInitializes the IRDA peripheral
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_DeInit(IRDA_HandleTypeDef *hirda)
{
  /* Check the IRDA handle allocation */
  if(hirda == HAL_NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_IRDA_INSTANCE(hirda->Instance));

  hirda->State = HAL_IRDA_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_IRDA_DISABLE(hirda);

  /* DeInit the low level hardware */
  HAL_IRDA_MspDeInit(hirda);

  hirda->ErrorCode = HAL_IRDA_ERROR_NONE;
  hirda->State = HAL_IRDA_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hirda);

  return HAL_OK;
}

/**
  * @brief  IRDA MSP Init.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval None
  */
 __weak void HAL_IRDA_MspInit(IRDA_HandleTypeDef *hirda)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_IRDA_MspInit can be implemented in the user file
   */ 
}

/**
  * @brief  IRDA MSP DeInit.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval None
  */
 __weak void HAL_IRDA_MspDeInit(IRDA_HandleTypeDef *hirda)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_IRDA_MspDeInit can be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup IRDA_Exported_Functions_Group2 IO operation functions 
  *  @brief   IRDA Transmit and Receive functions 
  *
@verbatim
  ==============================================================================
                         ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the IRDA data transfers.

  [..]
    IrDA is a half duplex communication protocol. If the Transmitter is busy, any data
    on the IrDA receive line will be ignored by the IrDA decoder and if the Receiver 
    is busy, data on the TX from the USART to IrDA will not be encoded by IrDA.
    While receiving data, transmission should be avoided as the data to be transmitted
    could be corrupted.

    (#) There are two modes of transfer:
        (++) Blocking mode: The communication is performed in polling mode. 
             The HAL status of all data processing is returned by the same function 
             after finishing transfer.  
        (++) No-Blocking mode: The communication is performed using Interrupts 
             or DMA, These API's return the HAL status.
             The end of the data processing will be indicated through the 
             dedicated IRDA IRQ when using Interrupt mode or the DMA IRQ when 
             using DMA mode.
             The HAL_IRDA_TxCpltCallback(), HAL_IRDA_RxCpltCallback() user callbacks 
             will be executed respectivelly at the end of the transmit or Receive process
             The HAL_IRDA_ErrorCallback() user callback will be executed when a communication 
             error is detected

    (#) Blocking mode APIs are :
        (++) HAL_IRDA_Transmit()
        (++) HAL_IRDA_Receive()
        
    (#) Non Blocking mode APIs with Interrupt are :
        (++) HAL_IRDA_Transmit_IT()
        (++) HAL_IRDA_Receive_IT()
        (++) HAL_IRDA_IRQHandler()

    (#) Non Blocking mode functions with DMA are :
        (++) HAL_IRDA_Transmit_DMA()
        (++) HAL_IRDA_Receive_DMA()
        (++) HAL_IRDA_DMAPause()
        (++) HAL_IRDA_DMAResume()
        (++) HAL_IRDA_DMAStop()

    (#) A set of Transfer Complete Callbacks are provided in non Blocking mode:
        (++) HAL_IRDA_TxHalfCpltCallback()
        (++) HAL_IRDA_TxCpltCallback()
        (++) HAL_IRDA_RxHalfCpltCallback()
        (++) HAL_IRDA_RxCpltCallback()
        (++) HAL_IRDA_ErrorCallback()

@endverbatim
  * @{
  */

/**
  * @brief  Sends an amount of data in blocking mode.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @param  Timeout: Specify timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Transmit(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint16_t* tmp = 0;
  uint32_t  tmp1 = 0;

  tmp1 = hirda->State;
  if((tmp1 == HAL_IRDA_STATE_READY) || (tmp1 == HAL_IRDA_STATE_BUSY_RX))
  {
    if((pData == HAL_NULL) || (Size == 0)) 
    {
      return  HAL_ERROR;
    }
    
    /* Process Locked */
    __HAL_LOCK(hirda);
    
    hirda->ErrorCode = HAL_IRDA_ERROR_NONE;
    if(hirda->State == HAL_IRDA_STATE_BUSY_RX) 
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX_RX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX;
    }

    hirda->TxXferSize = Size;
    hirda->TxXferCount = Size;
    while(hirda->TxXferCount > 0)
    {
      if(hirda->Init.WordLength == IRDA_WORDLENGTH_9B)
      {
        if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_TXE, RESET, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
        tmp = (uint16_t*) pData;
        WRITE_REG(hirda->Instance->DR,(*tmp & IRDA_DR_MASK_U16_9DATABITS));
        if(hirda->Init.Parity == IRDA_PARITY_NONE)
        {
          pData +=2;
        }
        else
        {
          pData +=1;
        }
      }
      else
      {
        if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_TXE, RESET, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
        WRITE_REG(hirda->Instance->DR, (*pData++ & IRDA_DR_MASK_U8_8DATABITS));
      }
      hirda->TxXferCount--;
    }

    if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_TC, RESET, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    if(hirda->State == HAL_IRDA_STATE_BUSY_TX_RX) 
    {
      hirda->State = HAL_IRDA_STATE_BUSY_RX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_READY;
    }

    /* Process Unlocked */
    __HAL_UNLOCK(hirda);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Receive an amount of data in blocking mode. 
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @param  Timeout: Specify timeout value    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Receive(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint16_t* tmp = 0;
  uint32_t  tmp1 = 0;
  
  tmp1 = hirda->State;
  if((tmp1 == HAL_IRDA_STATE_READY) || (tmp1 == HAL_IRDA_STATE_BUSY_TX))
  {
    if((pData == HAL_NULL) || (Size == 0)) 
    {
      return  HAL_ERROR;
    }
    
    /* Process Locked */
    __HAL_LOCK(hirda);
    
    hirda->ErrorCode = HAL_IRDA_ERROR_NONE;
    if(hirda->State == HAL_IRDA_STATE_BUSY_TX) 
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX_RX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_BUSY_RX;
    }
    hirda->RxXferSize = Size;
    hirda->RxXferCount = Size;
    /* Check the remain data to be received */
    while(hirda->RxXferCount > 0)
    {
      if(hirda->Init.WordLength == IRDA_WORDLENGTH_9B)
      {
        if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_RXNE, RESET, Timeout) != HAL_OK)
        { 
          return HAL_TIMEOUT;
        }
        tmp = (uint16_t*) pData ;
        if(hirda->Init.Parity == IRDA_PARITY_NONE)
        {
          *tmp = (uint16_t)(hirda->Instance->DR & IRDA_DR_MASK_U16_9DATABITS);
          pData +=2;
        }
        else
        {
          *tmp = (uint16_t)(hirda->Instance->DR & IRDA_DR_MASK_U16_8DATABITS);
          pData +=1;
        }
      } 
      else
      {
        if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_RXNE, RESET, Timeout) != HAL_OK)
        { 
          return HAL_TIMEOUT;
        }
        if(hirda->Init.Parity == IRDA_PARITY_NONE)
        {
          *pData++ = (uint8_t)(hirda->Instance->DR & IRDA_DR_MASK_U8_8DATABITS);
        }
        else
        {
          *pData++ = (uint8_t)(hirda->Instance->DR & IRDA_DR_MASK_U8_7DATABITS);
        }
      }
      hirda->RxXferCount--;
    }
    if(hirda->State == HAL_IRDA_STATE_BUSY_TX_RX) 
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_READY;
    }
    
    /* Process Unlocked */
    __HAL_UNLOCK(hirda);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief  Sends an amount of data in non-blocking mode. 
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Transmit_IT(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size)
{
  uint32_t tmp = 0;
  
  tmp = hirda->State;
  if((tmp == HAL_IRDA_STATE_READY) || (tmp == HAL_IRDA_STATE_BUSY_RX))
  {
    if((pData == HAL_NULL) || (Size == 0))
    {
      return HAL_ERROR;
    }
    /* Process Locked */
    __HAL_LOCK(hirda);
    
    hirda->pTxBuffPtr = pData;
    hirda->TxXferSize = Size;
    hirda->TxXferCount = Size;

    hirda->ErrorCode = HAL_IRDA_ERROR_NONE;
    if(hirda->State == HAL_IRDA_STATE_BUSY_RX) 
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX_RX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX;
    }

    /* Enable the IRDA Parity Error Interrupt */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_PE);

    /* Enable the IRDA Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_ERR);

    /* Process Unlocked */
    __HAL_UNLOCK(hirda);

    /* Enable the IRDA Transmit Data Register Empty Interrupt */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_TXE);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Receives an amount of data in non-blocking mode. 
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Receive_IT(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size)
{
  uint32_t tmp = 0;
  
  tmp = hirda->State;
  if((tmp == HAL_IRDA_STATE_READY) || (tmp == HAL_IRDA_STATE_BUSY_TX))
  {
    if((pData == HAL_NULL) || (Size == 0))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(hirda);

    hirda->pRxBuffPtr = pData;
    hirda->RxXferSize = Size;
    hirda->RxXferCount = Size;

    hirda->ErrorCode = HAL_IRDA_ERROR_NONE;
    if(hirda->State == HAL_IRDA_STATE_BUSY_TX)
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX_RX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_BUSY_RX;
    }

    /* Enable the IRDA Data Register not empty Interrupt */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_RXNE); 

    /* Enable the IRDA Parity Error Interrupt */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_PE);

    /* Enable the IRDA Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_ERR);

    /* Process Unlocked */
    __HAL_UNLOCK(hirda);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Sends an amount of data in non-blocking mode. 
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Transmit_DMA(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size)
{
  uint32_t *tmp = 0;
  uint32_t  tmp1 = 0;

  tmp1 = hirda->State;
  if((tmp1 == HAL_IRDA_STATE_READY) || (tmp1 == HAL_IRDA_STATE_BUSY_RX))
  {
    if((pData == HAL_NULL) || (Size == 0)) 
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(hirda);

    hirda->pTxBuffPtr = pData;
    hirda->TxXferSize = Size;
    hirda->TxXferCount = Size;
    hirda->ErrorCode = HAL_IRDA_ERROR_NONE;

    if(hirda->State == HAL_IRDA_STATE_BUSY_RX)
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX_RX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX;
    }

    /* Set the IRDA DMA transfer complete callback */
    hirda->hdmatx->XferCpltCallback = IRDA_DMATransmitCplt;

    /* Set the IRDA DMA half transfert complete callback */
    hirda->hdmatx->XferHalfCpltCallback = IRDA_DMATransmitHalfCplt;

    /* Set the DMA error callback */
    hirda->hdmatx->XferErrorCallback = IRDA_DMAError;

    /* Enable the IRDA transmit DMA channel */
    tmp = (uint32_t*)&pData;
    HAL_DMA_Start_IT(hirda->hdmatx, *(uint32_t*)tmp, (uint32_t)&hirda->Instance->DR, Size);

    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the USART CR3 register */
    SET_BIT(hirda->Instance->CR3, USART_CR3_DMAT);

    /* Process Unlocked */
    __HAL_UNLOCK(hirda);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Receive an amount of data in non-blocking mode. 
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @param  pData: Pointer to data buffer
  * @param  Size: Amount of data to be received
  * @note   When the IRDA parity is enabled (PCE = 1) the data received contain the parity bit.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Receive_DMA(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size)
{
  uint32_t *tmp = 0;
  uint32_t tmp1 = 0;

  tmp1 = hirda->State;
  if((tmp1 == HAL_IRDA_STATE_READY) || (tmp1 == HAL_IRDA_STATE_BUSY_TX))
  {
    if((pData == HAL_NULL) || (Size == 0))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(hirda);

    hirda->pRxBuffPtr = pData;
    hirda->RxXferSize = Size;
    hirda->ErrorCode = HAL_IRDA_ERROR_NONE;
    if(hirda->State == HAL_IRDA_STATE_BUSY_TX)
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX_RX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_BUSY_RX;
    }

    /* Set the IRDA DMA transfer complete callback */
    hirda->hdmarx->XferCpltCallback = IRDA_DMAReceiveCplt;

    /* Set the IRDA DMA half transfert complete callback */
    hirda->hdmarx->XferHalfCpltCallback = IRDA_DMAReceiveHalfCplt;

    /* Set the DMA error callback */
    hirda->hdmarx->XferErrorCallback = IRDA_DMAError;

    /* Enable the DMA channel */
    tmp = (uint32_t*)&pData;
    HAL_DMA_Start_IT(hirda->hdmarx, (uint32_t)&hirda->Instance->DR, *(uint32_t*)tmp, Size);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit 
       in the USART CR3 register */
    SET_BIT(hirda->Instance->CR3, USART_CR3_DMAR);

    /* Process Unlocked */
    __HAL_UNLOCK(hirda);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Pauses the DMA Transfer.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_DMAPause(IRDA_HandleTypeDef *hirda)
{
  /* Process Locked */
  __HAL_LOCK(hirda);
  
  if(hirda->State == HAL_IRDA_STATE_BUSY_TX)
  {
    /* Disable the UART DMA Tx request */
    CLEAR_BIT(hirda->Instance->CR3, USART_CR3_DMAT);
  }
  else if(hirda->State == HAL_IRDA_STATE_BUSY_RX)
  {
    /* Disable the UART DMA Rx request */
    CLEAR_BIT(hirda->Instance->CR3, USART_CR3_DMAR);
  }
  else if (hirda->State == HAL_IRDA_STATE_BUSY_TX_RX)
  {
    /* Disable the UART DMA Tx & Rx requests */
    CLEAR_BIT(hirda->Instance->CR3, USART_CR3_DMAT);
    CLEAR_BIT(hirda->Instance->CR3, USART_CR3_DMAR);
  }
  else
  {
    /* Process Unlocked */
    __HAL_UNLOCK(hirda);
  
    return HAL_ERROR; 
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hirda);
  
  return HAL_OK; 
}

/**
  * @brief Resumes the DMA Transfer.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_DMAResume(IRDA_HandleTypeDef *hirda)
{
  /* Process Locked */
  __HAL_LOCK(hirda);
  
  if(hirda->State == HAL_IRDA_STATE_BUSY_TX)
  {
    /* Enable the UART DMA Tx request */
    SET_BIT(hirda->Instance->CR3, USART_CR3_DMAT);
  }
  else if(hirda->State == HAL_IRDA_STATE_BUSY_RX)
  {
    /* Clear the Overrun flag before resumming the Rx transfer*/
    __HAL_IRDA_CLEAR_OREFLAG(hirda);
    /* Enable the UART DMA Rx request */
    SET_BIT(hirda->Instance->CR3, USART_CR3_DMAR);
  }
  else if(hirda->State == HAL_IRDA_STATE_BUSY_TX_RX)
  {
    /* Clear the Overrun flag before resumming the Rx transfer*/
    __HAL_IRDA_CLEAR_OREFLAG(hirda);
    /* Enable the UART DMA Tx & Rx request */
    SET_BIT(hirda->Instance->CR3, USART_CR3_DMAT);
    SET_BIT(hirda->Instance->CR3, USART_CR3_DMAR);
  }
  else
  {
    /* Process Unlocked */
    __HAL_UNLOCK(hirda);
  
    return HAL_ERROR; 
  }
  
  /* Process Unlocked */
  __HAL_UNLOCK(hirda);
  
  return HAL_OK;
}

/**
  * @brief Stops the DMA Transfer.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_DMAStop(IRDA_HandleTypeDef *hirda)
{
  /* The Lock is not implemented on this API to allow the user application
     to call the HAL UART API under callbacks HAL_UART_TxCpltCallback() / HAL_UART_RxCpltCallback():
     when calling HAL_DMA_Abort() API the DMA TX/RX Transfer complete interrupt is generated
     and the correspond call back is executed HAL_UART_TxCpltCallback() / HAL_UART_RxCpltCallback()
     */

  /* Disable the UART Tx/Rx DMA requests */
  CLEAR_BIT(hirda->Instance->CR3, USART_CR3_DMAT);
  CLEAR_BIT(hirda->Instance->CR3, USART_CR3_DMAR);
  
  /* Abort the UART DMA tx channel */
  if(hirda->hdmatx != HAL_NULL)
  {
    HAL_DMA_Abort(hirda->hdmatx);
  }
  /* Abort the UART DMA rx channel */
  if(hirda->hdmarx != HAL_NULL)
  {
    HAL_DMA_Abort(hirda->hdmarx);
  }
  
  hirda->State = HAL_IRDA_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  This function handles IRDA interrupt request.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval None
  */
void HAL_IRDA_IRQHandler(IRDA_HandleTypeDef *hirda)
{
  uint32_t  tmp1 = 0, tmp2 = 0;
  
  tmp1 = __HAL_IRDA_GET_FLAG(hirda, IRDA_FLAG_PE);
  tmp2 = __HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_PE);
  /* IRDA parity error interrupt occurred -----------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    __HAL_IRDA_CLEAR_PEFLAG(hirda);
    hirda->ErrorCode |= HAL_IRDA_ERROR_PE;
  }

  tmp1 = __HAL_IRDA_GET_FLAG(hirda, IRDA_FLAG_FE);
  tmp2 = __HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_ERR);
  /* IRDA frame error interrupt occurred ------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    __HAL_IRDA_CLEAR_FEFLAG(hirda);
    hirda->ErrorCode |= HAL_IRDA_ERROR_FE;
  }

  tmp1 = __HAL_IRDA_GET_FLAG(hirda, IRDA_FLAG_NE);
  tmp2 = __HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_ERR);
  /* IRDA noise error interrupt occurred ------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    __HAL_IRDA_CLEAR_NEFLAG(hirda);
    hirda->ErrorCode |= HAL_IRDA_ERROR_NE;
  }

  tmp1 = __HAL_IRDA_GET_FLAG(hirda, IRDA_FLAG_ORE);
  tmp2 = __HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_ERR);
  /* IRDA Over-Run interrupt occurred ---------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    __HAL_IRDA_CLEAR_OREFLAG(hirda);
    hirda->ErrorCode |= HAL_IRDA_ERROR_ORE;
  }

  /* Call the Error call Back in case of Errors */
  if(hirda->ErrorCode != HAL_IRDA_ERROR_NONE)
  {
    /* Disable PE and ERR interrupt */
    __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_ERR);
    __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_PE);
    __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_TXE);
    
    /* Set the IRDA state ready to be able to start again the process */
    hirda->State = HAL_IRDA_STATE_READY;
    HAL_IRDA_ErrorCallback(hirda);
  }

  tmp1 = __HAL_IRDA_GET_FLAG(hirda, IRDA_FLAG_RXNE);
  tmp2 = __HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_RXNE);
  /* IRDA in mode Receiver --------------------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    IRDA_Receive_IT(hirda);
  }

  tmp1 = __HAL_IRDA_GET_FLAG(hirda, IRDA_FLAG_TXE);
  tmp2 = __HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_TXE);
  /* IRDA in mode Transmitter -----------------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    IRDA_Transmit_IT(hirda);
  }

  tmp1 = __HAL_IRDA_GET_FLAG(hirda, IRDA_FLAG_TC);
  tmp2 = __HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_TC);
  /* IRDA in mode Transmitter (transmission end) -----------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    IRDA_EndTransmit_IT(hirda);
  }   
  
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval None
  */
 __weak void HAL_IRDA_TxCpltCallback(IRDA_HandleTypeDef *hirda)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_IRDA_TxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  Tx Half Transfer completed callbacks.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified USART module.
  * @retval None
  */
 __weak void HAL_IRDA_TxHalfCpltCallback(IRDA_HandleTypeDef *hirda)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_IRDA_TxHalfCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval None
  */
__weak void HAL_IRDA_RxCpltCallback(IRDA_HandleTypeDef *hirda)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_IRDA_RxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  Rx Half Transfer complete callbacks.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval None
  */
__weak void HAL_IRDA_RxHalfCpltCallback(IRDA_HandleTypeDef *hirda)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_IRDA_RxHalfCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  IRDA error callbacks.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval None
  */
 __weak void HAL_IRDA_ErrorCallback(IRDA_HandleTypeDef *hirda)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_IRDA_ErrorCallback can be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup IRDA_Exported_Functions_Group3 Peripheral State and Errors functions 
  *  @brief   IRDA State and Errors functions 
  *
@verbatim   
  ==============================================================================
                  ##### Peripheral State and Errors functions #####
  ==============================================================================  
  [..]
    This subsection provides a set of functions allowing to return the State of IrDA 
    communication process and also return Peripheral Errors occurred during communication process
     (+) HAL_IRDA_GetState() API can be helpful to check in run-time the state 
         of the IRDA peripheral.
     (+) HAL_IRDA_GetError() check in run-time errors that could be occurred during 
         communication.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the IRDA state.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval HAL state
  */
HAL_IRDA_StateTypeDef HAL_IRDA_GetState(IRDA_HandleTypeDef *hirda)
{
  return hirda->State;
}

/**
  * @brief  Return the IRDA error code
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval IRDA Error Code
  */
uint32_t HAL_IRDA_GetError(IRDA_HandleTypeDef *hirda)
{
  return hirda->ErrorCode;
}

/**
  * @}
  */
  
/**
  * @}
  */

/** @defgroup IRDA_Private_Functions   IRDA Private Functions
  *  @brief   IRDA Private functions 
  * @{
  */
/**
  * @brief  DMA IRDA transmit process complete callback. 
  * @param  hdma: Pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void IRDA_DMATransmitCplt(DMA_HandleTypeDef *hdma)
{
  IRDA_HandleTypeDef* hirda = ( IRDA_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  /* DMA Normal mode */
  if((hdma->Instance->CCR & DMA_CCR_CIRC) == 0)
  {
    hirda->TxXferCount = 0;

    /* Disable the DMA transfer for transmit request by setting the DMAT bit
       in the IRDA CR3 register */
    CLEAR_BIT(hirda->Instance->CR3, USART_CR3_DMAT);

    /* Wait for IRDA TC Flag */
    if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_TC, RESET, IRDA_TIMEOUT_VALUE) != HAL_OK)
    {
      /* Timeout occurred */ 
      hirda->State = HAL_IRDA_STATE_TIMEOUT;
      HAL_IRDA_ErrorCallback(hirda);
    }
    else
    {
      /* No Timeout */
      /* Check if a receive process is ongoing or not */
      if(hirda->State == HAL_IRDA_STATE_BUSY_TX_RX)
      {
        hirda->State = HAL_IRDA_STATE_BUSY_RX;
      }
      else
      {
        hirda->State = HAL_IRDA_STATE_READY;
      }
      HAL_IRDA_TxCpltCallback(hirda);
    }
  }
  /* DMA Circular mode */
  else
  {
    HAL_IRDA_TxCpltCallback(hirda);
  }
}

/**
  * @brief DMA IRDA receive process half complete callback 
  * @param  hdma: Pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void IRDA_DMATransmitHalfCplt(DMA_HandleTypeDef *hdma)
{
  IRDA_HandleTypeDef* hirda = ( IRDA_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  HAL_IRDA_TxHalfCpltCallback(hirda); 
}

/**
  * @brief  DMA IRDA receive process complete callback. 
  * @param  hdma: Pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void IRDA_DMAReceiveCplt(DMA_HandleTypeDef *hdma)   
{
  IRDA_HandleTypeDef* hirda = ( IRDA_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  /* DMA Normal mode */
  if((hdma->Instance->CCR & DMA_CCR_CIRC) == 0)
  {
    hirda->RxXferCount = 0;

    /* Disable the DMA transfer for the receiver request by setting the DMAR bit 
       in the IRDA CR3 register */
    CLEAR_BIT(hirda->Instance->CR3, USART_CR3_DMAR);

    if(hirda->State == HAL_IRDA_STATE_BUSY_TX_RX) 
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_READY;
    }
  }

  HAL_IRDA_RxCpltCallback(hirda);
}

/**
  * @brief DMA IRDA receive process half complete callback 
  * @param  hdma: Pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void IRDA_DMAReceiveHalfCplt(DMA_HandleTypeDef *hdma)
{
  IRDA_HandleTypeDef* hirda = ( IRDA_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  HAL_IRDA_RxHalfCpltCallback(hirda); 
}

/**
  * @brief  DMA IRDA communication error callback. 
  * @param  hdma: Pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void IRDA_DMAError(DMA_HandleTypeDef *hdma)   
{
  IRDA_HandleTypeDef* hirda = ( IRDA_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  hirda->RxXferCount = 0;
  hirda->TxXferCount = 0;
  hirda->ErrorCode |= HAL_IRDA_ERROR_DMA; 
  hirda->State= HAL_IRDA_STATE_READY;
  
  HAL_IRDA_ErrorCallback(hirda);
}

/**
  * @brief  This function handles IRDA Communication Timeout.
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @param  Flag: specifies the IRDA flag to check.
  * @param  Status: The new Flag status (SET or RESET).
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef IRDA_WaitOnFlagUntilTimeout(IRDA_HandleTypeDef *hirda, uint32_t Flag, FlagStatus Status, uint32_t Timeout)
{
  uint32_t tickstart = 0;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until flag is set */
  if(Status == RESET)
  {
    while(__HAL_IRDA_GET_FLAG(hirda, Flag) == RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_TXE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_RXNE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_PE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_ERR);

          hirda->State= HAL_IRDA_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hirda);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {
    while(__HAL_IRDA_GET_FLAG(hirda, Flag) != RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_TXE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_RXNE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_PE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_ERR);

          hirda->State= HAL_IRDA_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hirda);
        
          return HAL_TIMEOUT;
        }
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief  Send an amount of data in non-blocking mode. 
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_IRDA_Transmit_IT()      
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval HAL status
  */
static HAL_StatusTypeDef IRDA_Transmit_IT(IRDA_HandleTypeDef *hirda)
{
  uint16_t* tmp = 0;
  uint32_t  tmp1 = 0;

  tmp1 = hirda->State;
  if((tmp1 == HAL_IRDA_STATE_BUSY_TX) || (tmp1 == HAL_IRDA_STATE_BUSY_TX_RX))
  {
    if(hirda->Init.WordLength == IRDA_WORDLENGTH_9B)
    {
      tmp = (uint16_t*) hirda->pTxBuffPtr;
      WRITE_REG(hirda->Instance->DR, (uint16_t)(*tmp & IRDA_DR_MASK_U16_9DATABITS));
      if(hirda->Init.Parity == IRDA_PARITY_NONE)
      {
        hirda->pTxBuffPtr += 2;
      }
      else
      {
        hirda->pTxBuffPtr += 1;
      }
    } 
    else
    {
      WRITE_REG(hirda->Instance->DR, (uint8_t)(*hirda->pTxBuffPtr++ & IRDA_DR_MASK_U8_8DATABITS));
    }
    
    if(--hirda->TxXferCount == 0)
    {
      /* Disable the IRDA Transmit Data Register Empty Interrupt */
      __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_TXE);
     
      /* Enable the IRDA Transmit Complete Interrupt */    
      __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_TC);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Wraps up transmission in non blocking mode.
  * @param  hirda: pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval HAL status
  */
static HAL_StatusTypeDef IRDA_EndTransmit_IT(IRDA_HandleTypeDef *hirda)
{
  /* Disable the IRDA Transmit Complete Interrupt */    
  __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_TC);
  
  /* Check if a receive process is ongoing or not */
  if(hirda->State == HAL_IRDA_STATE_BUSY_TX_RX) 
  {
    hirda->State = HAL_IRDA_STATE_BUSY_RX;
  }
  else
  {
    /* Disable the IRDA Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_ERR);

    /* Disable the IRDA Parity Error Interrupt */
    __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_PE);

    hirda->State = HAL_IRDA_STATE_READY;
  }
  
  HAL_IRDA_TxCpltCallback(hirda);
  
  return HAL_OK;
}


/**
  * @brief  Receive an amount of data in non-blocking mode. 
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval HAL status
  */
static HAL_StatusTypeDef IRDA_Receive_IT(IRDA_HandleTypeDef *hirda)
{
  uint16_t* tmp = 0;
  uint32_t tmp1 = 0;

  tmp1 = hirda->State;  
  if((tmp1 == HAL_IRDA_STATE_BUSY_RX) || (tmp1 == HAL_IRDA_STATE_BUSY_TX_RX))
  {
    if(hirda->Init.WordLength == IRDA_WORDLENGTH_9B)
    {
      tmp = (uint16_t*) hirda->pRxBuffPtr;
      if(hirda->Init.Parity == IRDA_PARITY_NONE)
      {
        *tmp = (uint16_t)(hirda->Instance->DR & IRDA_DR_MASK_U16_9DATABITS);
        hirda->pRxBuffPtr += 2;
      }
      else
      {
        *tmp = (uint16_t)(hirda->Instance->DR & IRDA_DR_MASK_U16_8DATABITS);
        hirda->pRxBuffPtr += 1;
      }
    } 
    else
    {
      if(hirda->Init.Parity == IRDA_PARITY_NONE)
      {
        *hirda->pRxBuffPtr++ = (uint8_t)(hirda->Instance->DR & IRDA_DR_MASK_U8_8DATABITS);
      }
      else
      {
        *hirda->pRxBuffPtr++ = (uint8_t)(hirda->Instance->DR & IRDA_DR_MASK_U8_7DATABITS);
      }
    }

    if(--hirda->RxXferCount == 0)
    {

      __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_RXNE);
      
      if(hirda->State == HAL_IRDA_STATE_BUSY_TX_RX) 
      {
        hirda->State = HAL_IRDA_STATE_BUSY_TX;
      }
      else
      {
        /* Disable the IRDA Parity Error Interrupt */
        __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_PE);

        /* Disable the IRDA Error Interrupt: (Frame error, noise error, overrun error) */
        __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_ERR);

        hirda->State = HAL_IRDA_STATE_READY;
      }
      HAL_IRDA_RxCpltCallback(hirda);

      return HAL_OK;
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
  * @brief  Configures the IRDA peripheral. 
  * @param  hirda: Pointer to a IRDA_HandleTypeDef structure that contains
  *                the configuration information for the specified IRDA module.
  * @retval None
  */
static void IRDA_SetConfig(IRDA_HandleTypeDef *hirda)
{
  /* Check the parameters */
  assert_param(IS_IRDA_INSTANCE(hirda->Instance));
  assert_param(IS_IRDA_BAUDRATE(hirda->Init.BaudRate));  
  assert_param(IS_IRDA_WORD_LENGTH(hirda->Init.WordLength));
  assert_param(IS_IRDA_PARITY(hirda->Init.Parity));
  assert_param(IS_IRDA_MODE(hirda->Init.Mode));
  
  /*-------------------------- IRDA CR2 Configuration ------------------------*/
  /* Clear STOP[13:12] bits */
  CLEAR_BIT(hirda->Instance->CR2, USART_CR2_STOP);
  
  /*-------------------------- USART CR1 Configuration -----------------------*/
  /* Configure the USART Word Length, Parity and mode: 
     Set the M bits according to hirda->Init.WordLength value 
     Set PCE and PS bits according to hirda->Init.Parity value
     Set TE and RE bits according to hirda->Init.Mode value */
  MODIFY_REG(hirda->Instance->CR1,
             ((uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | USART_CR1_TE | USART_CR1_RE)),
             (uint32_t)hirda->Init.WordLength | hirda->Init.Parity | hirda->Init.Mode);
  
  /*-------------------------- USART CR3 Configuration -----------------------*/  
  /* Clear CTSE and RTSE bits */
  CLEAR_BIT(hirda->Instance->CR3, (USART_CR3_RTSE | USART_CR3_CTSE));
  
  /*-------------------------- USART BRR Configuration -----------------------*/
  if(hirda->Instance == USART1)
  {
    hirda->Instance->BRR = IRDA_BRR(HAL_RCC_GetPCLK2Freq(), hirda->Init.BaudRate);
  }
  else
  {
    hirda->Instance->BRR = IRDA_BRR(HAL_RCC_GetPCLK1Freq(), hirda->Init.BaudRate);
  }
}
/**
  * @}
  */

#endif /* HAL_IRDA_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
