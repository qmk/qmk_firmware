/**
  ******************************************************************************
  * @file    stm32l0xx_hal_smartcard.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   SMARTCARD HAL module driver.
  *
  *          This file provides firmware functions to manage the following 
  *          functionalities of the SmartCard.
  *           + Initialization and de-initialization methods
  *           + IO operation methods
  *           + Peripheral Control methods
  *
  *           
  @verbatim       
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
    The SMARTCARD HAL driver can be used as follow:
    
    (#) Declare a SMARTCARD_HandleTypeDef handle structure.
    (#) Associate a USART to the SMARTCARD handle hsc.
    (#) Initialize the SMARTCARD low level resources by implementing the HAL_SMARTCARD_MspInit ()API:
        (##) Enable the USARTx interface clock.
        (##) USART pins configuration:
            (+) Enable the clock for the USART GPIOs.
            (+) Configure these USART pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (HAL_SMARTCARD_Transmit_IT()
             and HAL_SMARTCARD_Receive_IT() APIs):
            (+) Configure the USARTx interrupt priority.
            (+) Enable the NVIC USART IRQ handle.
            (@) The specific USART interrupts (Transmission complete interrupt, 
                RXNE interrupt and Error Interrupts) will be managed using the macros
                __HAL_SMARTCARD_ENABLE_IT() and __HAL_SMARTCARD_DISABLE_IT() inside the transmit and receive process.
        (##) DMA Configuration if you need to use DMA process (HAL_SMARTCARD_Transmit_DMA()
             and HAL_SMARTCARD_Receive_DMA() APIs):
            (+) Declare a DMA handle structure for the Tx/Rx stream.
            (+) Enable the DMAx interface clock.
            (+) Configure the declared DMA handle structure with the required Tx/Rx parameters.                
            (+) Configure the DMA Tx/Rx Stream.
            (+) Associate the initialized DMA handle to the SMARTCARD DMA Tx/Rx handle.
            (+) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx Stream.

    (#) Program the Baud Rate, Parity, Mode(Receiver/Transmitter), clock enabling/disabling and accordingly,
        the clock parameters (parity, phase, last bit), prescaler value, guard time and NACK on transmission
        error enabling or disabling in the hsc Init structure.
        
    (#) If required, program SMARTCARD advanced features (TX/RX pins swap, TimeOut, auto-retry counter,...)
        in the hsc AdvancedInit structure.

    (#) Initialize the SMARTCARD associated USART registers by calling
        the HAL_SMARTCARD_Init() API.                                 
        
    (@) HAL_SMARTCARD_Init() API also configure also the low level Hardware GPIO, CLOCK, CORTEX...etc) by 
        calling the customized HAL_SMARTCARD_MspInit() API.

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

/** @addtogroup SMARTCARD
  * @brief HAL SMARTCARD module driver
  * @{
  */
#ifdef HAL_SMARTCARD_MODULE_ENABLED
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TEACK_REACK_TIMEOUT               1000
#define HAL_SMARTCARD_TXDMA_TIMEOUTVALUE  22000
#define USART_CR1_FIELDS      ((uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | \
                                          USART_CR1_TE | USART_CR1_RE | USART_CR1_OVER8))
#define USART_CR2_CLK_FIELDS  ((uint32_t)(USART_CR2_CLKEN|USART_CR2_CPOL|USART_CR2_CPHA|USART_CR2_LBCL))   
#define USART_CR2_FIELDS      ((uint32_t)(USART_CR2_RTOEN|USART_CR2_CLK_FIELDS|USART_CR2_STOP))
#define USART_CR3_FIELDS      ((uint32_t)(USART_CR3_ONEBIT|USART_CR3_NACK|USART_CR3_SCARCNT))  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SMARTCARD_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void SMARTCARD_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void SMARTCARD_DMAError(DMA_HandleTypeDef *hdma); 
static void SMARTCARD_SetConfig(SMARTCARD_HandleTypeDef *hsc);
static HAL_StatusTypeDef SMARTCARD_WaitOnFlagUntilTimeout(SMARTCARD_HandleTypeDef *hsc, uint32_t Flag, FlagStatus Status, uint32_t Timeout);
static HAL_StatusTypeDef SMARTCARD_CheckIdleState(SMARTCARD_HandleTypeDef *hsc);
static HAL_StatusTypeDef SMARTCARD_Transmit_IT(SMARTCARD_HandleTypeDef *hsc);
static HAL_StatusTypeDef SMARTCARD_Receive_IT(SMARTCARD_HandleTypeDef *hsc);
static void SMARTCARD_AdvFeatureConfig(SMARTCARD_HandleTypeDef *hsc);
/* Private functions ---------------------------------------------------------*/

/** @addtogroup SMARTCARD_Exported_Functions
  * @{
  */

/** @addtogroup SMARTCARD_Exported_Functions_Group1
  *  @brief    Initialization and Configuration functions 
  *
@verbatim    
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the USARTx 
    associated to the SmartCard.
      (+) These parameters can be configured: 
        (++) Baud Rate
        (++) Parity: parity should be enabled,
             Frame Length is fixed to 8 bits plus parity:
             the USART frame format is given in the following table:
   +---------------------------------------------------------------+
   | M1M0 bits |  PCE bit  |            USART frame                |
   |-----------------------|---------------------------------------|
   |     01    |    1      |    | SB | 8 bit data | PB | STB |     |
   +---------------------------------------------------------------+
        (++) Receiver/transmitter modes
        (++) Synchronous mode (and if enabled, phase, polarity and last bit parameters)
        (++) Prescaler value
        (++) Guard bit time 
        (++) NACK enabling or disabling on transmission error               

      (+) The following advanced features can be configured as well:
        (++) TX and/or RX pin level inversion
        (++) data logical level inversion
        (++) RX and TX pins swap
        (++) RX overrun detection disabling
        (++) DMA disabling on RX error
        (++) MSB first on communication line
        (++) Time out enabling (and if activated, timeout value)
        (++) Block length
        (++) Auto-retry counter       
        
    [..]                                                  
    The HAL_SMARTCARD_Init() API follow respectively the USART (a)synchronous configuration procedures 
    (details for the procedures are available in reference manual).

@endverbatim
  * @{
  */

/**
  * @brief Initializes the SMARTCARD mode according to the specified
  *         parameters in the SMARTCARD_InitTypeDef and creates the associated handle .
  * @param hsc: SMARTCARD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARD_Init(SMARTCARD_HandleTypeDef *hsc)
{
  /* Check the SMARTCARD handle allocation */
  if(hsc == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the USART associated to the SmartCard */
  assert_param(IS_SMARTCARD_INSTANCE(hsc->Instance));
  
  if(hsc->State == HAL_SMARTCARD_STATE_RESET)
  {  
    /* Init the low level hardware : GPIO, CLOCK, CORTEX */
    HAL_SMARTCARD_MspInit(hsc);
  }
  
  hsc->State = HAL_SMARTCARD_STATE_BUSY;
  
  /* Disable the Peripheral */
  __HAL_SMARTCARD_DISABLE(hsc);
  
  /* Set the SMARTCARD Communication parameters */
  SMARTCARD_SetConfig(hsc);
  
  if(hsc->AdvancedInit.AdvFeatureInit != SMARTCARD_ADVFEATURE_NO_INIT)
  {
    SMARTCARD_AdvFeatureConfig(hsc);
  }
  
  /* In SmartCard mode, the following bits must be kept cleared: 
  - LINEN in the USART_CR2 register,
  - HDSEL and IREN  bits in the USART_CR3 register.*/
  hsc->Instance->CR2 &= ~(USART_CR2_LINEN); 
  hsc->Instance->CR3 &= ~(USART_CR3_HDSEL | USART_CR3_IREN); 
  
  /* set the USART in SMARTCARD mode */ 
  hsc->Instance->CR3 |= USART_CR3_SCEN; 
  
  /* Enable the Peripheral */
  __HAL_SMARTCARD_ENABLE(hsc);
  
  /* TEACK and/or REACK to check before moving hsc->State to Ready */
  return (SMARTCARD_CheckIdleState(hsc));
}

/**
  * @brief DeInitializes the SMARTCARD peripheral 
  * @param hsc: SMARTCARD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARD_DeInit(SMARTCARD_HandleTypeDef *hsc)
{
  /* Check the SMARTCARD handle allocation */
  if(hsc == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_SMARTCARD_INSTANCE(hsc->Instance));
  
  hsc->State = HAL_SMARTCARD_STATE_BUSY;
  
  /* DeInit the low level hardware */
  HAL_SMARTCARD_MspDeInit(hsc);
  
  hsc->ErrorCode = HAL_SMARTCARD_ERROR_NONE;
  hsc->State = HAL_SMARTCARD_STATE_RESET;
  
  /* Release Lock */
  __HAL_UNLOCK(hsc);
  
  return HAL_OK;
}

/**
  * @brief SMARTCARD MSP Init
  * @param hsc: SMARTCARD handle
  * @retval None
  */
 __weak void HAL_SMARTCARD_MspInit(SMARTCARD_HandleTypeDef *hsc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SMARTCARD_MspInit could be implenetd in the user file
   */ 
}

/**
  * @brief SMARTCARD MSP DeInit
  * @param hsc: SMARTCARD handle
  * @retval None
  */
 __weak void HAL_SMARTCARD_MspDeInit(SMARTCARD_HandleTypeDef *hsc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SMARTCARD_MspDeInit could be implenetd in the user file
   */ 
}

/**
  * @}
  */

/** @addtogroup SMARTCARD_Exported_Functions_Group2
  *  @brief SMARTCARD Transmit/Receive functions 
  *
@verbatim   
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================  
    This subsection provides a set of functions allowing to manage the SMARTCARD data transfers.

    (#) There are two mode of transfer:
       (+) Blocking mode: The communication is performed in polling mode. 
            The HAL status of all data processing is returned by the same function 
            after finishing transfer.  
       (+) No-Blocking mode: The communication is performed using Interrupts 
           or DMA, These API's return the HAL status.
           The end of the data processing will be indicated through the 
           dedicated SMARTCARD IRQ when using Interrupt mode or the DMA IRQ when 
           using DMA mode.
           The HAL_SMARTCARD_TxCpltCallback(), HAL_SMARTCARD_RxCpltCallback() user callbacks 
           will be executed respectivelly at the end of the transmit or Receive process
           The HAL_SMARTCARD_ErrorCallback()user callback will be executed when a communication error is detected

    (#) Blocking mode API's are :
        (+) HAL_SMARTCARD_Transmit()
        (+) HAL_SMARTCARD_Receive() 
        
    (#) Non-Blocking mode API's with Interrupt are :
        (+) HAL_SMARTCARD_Transmit_IT()
        (+) HAL_SMARTCARD_Receive_IT()
        (+) HAL_SMARTCARD_IRQHandler()
        (+) SMARTCARD_Transmit_IT()
        (+) SMARTCARD_Receive_IT()    

    (#) No-Blocking mode functions with DMA are :
        (+) HAL_SMARTCARD_Transmit_DMA()
        (+) HAL_SMARTCARD_Receive_DMA()

    (#) A set of Transfer Complete Callbacks are provided in No_Blocking mode:
        (+) HAL_SMARTCARD_TxCpltCallback()
        (+) HAL_SMARTCARD_RxCpltCallback()
        (+) HAL_SMARTCARD_ErrorCallback()
      
@endverbatim
  * @{
  */

/**
  * @brief Send an amount of data in blocking mode 
  * @param hsc: SMARTCARD handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @param Timeout : Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARD_Transmit(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  if((hsc->State == HAL_SMARTCARD_STATE_READY) || (hsc->State == HAL_SMARTCARD_STATE_BUSY_RX))
  {
    if((pData == NULL) || (Size == 0)) 
    {
      return  HAL_ERROR;
    }
    
    /* Process Locked */
    __HAL_LOCK(hsc);
    hsc->ErrorCode = HAL_SMARTCARD_ERROR_NONE;    
    /* Check if a non-blocking receive process is ongoing or not */
    if(hsc->State == HAL_SMARTCARD_STATE_BUSY_RX) 
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX_RX;
    }
    else
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX;
    }
    
    hsc->TxXferSize = Size;
    hsc->TxXferCount = Size;
    while(hsc->TxXferCount > 0)
    {
      hsc->TxXferCount--;      
      if(SMARTCARD_WaitOnFlagUntilTimeout(hsc, SMARTCARD_FLAG_TXE, RESET, Timeout) != HAL_OK)  
      { 
        return HAL_TIMEOUT;
      }
      hsc->Instance->TDR = (*pData++ & (uint8_t)0xFF);     
    }
    if(SMARTCARD_WaitOnFlagUntilTimeout(hsc, SMARTCARD_FLAG_TC, RESET, Timeout) != HAL_OK)  
    { 
      return HAL_TIMEOUT;
    }
    /* Check if a non-blocking receive Process is ongoing or not */
    if(hsc->State == HAL_SMARTCARD_STATE_BUSY_TX_RX) 
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_RX;
    }
    else
    {
      hsc->State = HAL_SMARTCARD_STATE_READY;
    }
    
    /* Process Unlocked */
    __HAL_UNLOCK(hsc);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Receive an amount of data in blocking mode 
  * @param hsc: SMARTCARD handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be received
  * @param Timeout : Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARD_Receive(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{ 
  if((hsc->State == HAL_SMARTCARD_STATE_READY) || (hsc->State == HAL_SMARTCARD_STATE_BUSY_TX))
  { 
    if((pData == NULL) || (Size == 0)) 
    {
      return  HAL_ERROR;
    }
    
    /* Process Locked */
    __HAL_LOCK(hsc);
    
    hsc->ErrorCode = HAL_SMARTCARD_ERROR_NONE;
    /* Check if a non-blocking transmit process is ongoing or not */
    if(hsc->State == HAL_SMARTCARD_STATE_BUSY_TX) 
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX_RX;
    }
    else
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_RX;
    }    
    
    hsc->RxXferSize = Size; 
    hsc->RxXferCount = Size;
    /* Check the remain data to be received */
    while(hsc->RxXferCount > 0)
    {
      hsc->RxXferCount--;    
      if(SMARTCARD_WaitOnFlagUntilTimeout(hsc, SMARTCARD_FLAG_RXNE, RESET, Timeout) != HAL_OK)  
      { 
        return HAL_TIMEOUT;
      }          
      *pData++ = (uint8_t)(hsc->Instance->RDR & (uint8_t)0x00FF);              
    }
    
    /* Check if a non-blocking transmit Process is ongoing or not */
    if(hsc->State == HAL_SMARTCARD_STATE_BUSY_TX_RX) 
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX;
    }
    else
    {
      hsc->State = HAL_SMARTCARD_STATE_READY;
    }    
    
    /* Process Unlocked */
    __HAL_UNLOCK(hsc);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Send an amount of data in interrupt mode 
  * @param hsc: SMARTCARD handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARD_Transmit_IT(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size)
{
  if((hsc->State == HAL_SMARTCARD_STATE_READY) || (hsc->State == HAL_SMARTCARD_STATE_BUSY_RX))
  {
    if((pData == NULL) || (Size == 0)) 
    {
      return HAL_ERROR;
    }
    
    /* Process Locked */
    __HAL_LOCK(hsc);
    
    hsc->pTxBuffPtr = pData;
    hsc->TxXferSize = Size;
    hsc->TxXferCount = Size;
    
    hsc->ErrorCode = HAL_SMARTCARD_ERROR_NONE;
    /* Check if a receive process is ongoing or not */
    if(hsc->State == HAL_SMARTCARD_STATE_BUSY_RX) 
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX_RX;
    }
    else
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX;
    }

    /* Enable the SMARTCARD Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_SMARTCARD_ENABLE_IT(hsc, SMARTCARD_IT_ERR);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hsc);    
    
    /* Enable the SMARTCARD Transmit Complete Interrupt */
    __HAL_SMARTCARD_ENABLE_IT(hsc, SMARTCARD_IT_TC);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief Receive an amount of data in interrupt mode 
  * @param hsc: SMARTCARD handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARD_Receive_IT(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size)
{
  if((hsc->State == HAL_SMARTCARD_STATE_READY) || (hsc->State == HAL_SMARTCARD_STATE_BUSY_TX))
  {
    if((pData == NULL) || (Size == 0)) 
    {
      return HAL_ERROR;
    }
    
    /* Process Locked */
  __HAL_LOCK(hsc);
  
    hsc->pRxBuffPtr = pData;
    hsc->RxXferSize = Size;
    hsc->RxXferCount = Size;
    
    hsc->ErrorCode = HAL_SMARTCARD_ERROR_NONE; 
    /* Check if a transmit process is ongoing or not */
    if(hsc->State == HAL_SMARTCARD_STATE_BUSY_TX) 
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX_RX;
    }
    else
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_RX;
    }    
    
    /* Enable the SMARTCARD Parity Error Interrupt */
    __HAL_SMARTCARD_ENABLE_IT(hsc, SMARTCARD_IT_PE);
    
    /* Enable the SMARTCARD Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_SMARTCARD_ENABLE_IT(hsc, SMARTCARD_IT_ERR);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hsc);
    
    /* Enable the SMARTCARD Data Register not empty Interrupt */
    __HAL_SMARTCARD_ENABLE_IT(hsc, SMARTCARD_IT_RXNE);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
  * @brief Send an amount of data in DMA mode 
  * @param hsc: SMARTCARD handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARD_Transmit_DMA(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size)
{
  uint32_t *tmp;
  
  if((hsc->State == HAL_SMARTCARD_STATE_READY) || (hsc->State == HAL_SMARTCARD_STATE_BUSY_RX))
  {
    if((pData == NULL) || (Size == 0)) 
    {
      return HAL_ERROR;
    }
    
    /* Process Locked */
    __HAL_LOCK(hsc);
    
    hsc->pTxBuffPtr = pData;
    hsc->TxXferSize = Size;
    hsc->TxXferCount = Size; 
  
    hsc->ErrorCode = HAL_SMARTCARD_ERROR_NONE;  
    /* Check if a receive process is ongoing or not */
    if(hsc->State == HAL_SMARTCARD_STATE_BUSY_RX) 
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX_RX;
    }
    else
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX;
    }
    
    /* Set the SMARTCARD DMA transfert complete callback */
    hsc->hdmatx->XferCpltCallback = SMARTCARD_DMATransmitCplt;
    
    /* Set the SMARTCARD error callback */
    hsc->hdmatx->XferErrorCallback = SMARTCARD_DMAError;

    /* Enable the SMARTCARD transmit DMA Stream */
    tmp = (uint32_t*)&pData;
    HAL_DMA_Start_IT(hsc->hdmatx, *(uint32_t*)tmp, (uint32_t)&hsc->Instance->TDR, Size);
    
    /* Clear the TC flag in the SR register by writing 0 to it */
    __HAL_SMARTCARD_CLEAR_FLAG(hsc, SMARTCARD_FLAG_TC);

    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the SMARTCARD associated USART CR3 register */
    hsc->Instance->CR3 |= USART_CR3_DMAT;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hsc);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Receive an amount of data in DMA mode 
  * @param hsc: SMARTCARD handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be received
  * @note   The SMARTCARD-associated USART parity is enabled (PCE = 1), 
  *         the received data contain the parity bit (MSB position)   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMARTCARD_Receive_DMA(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size)
{
  uint32_t *tmp;
  
  if((hsc->State == HAL_SMARTCARD_STATE_READY) || (hsc->State == HAL_SMARTCARD_STATE_BUSY_TX))
  {
    if((pData == NULL) || (Size == 0)) 
    {
      return HAL_ERROR;
    }
    
    /* Process Locked */
    __HAL_LOCK(hsc);
    
    hsc->pRxBuffPtr = pData;
    hsc->RxXferSize = Size;
    
    hsc->ErrorCode = HAL_SMARTCARD_ERROR_NONE;
    /* Check if a transmit rocess is ongoing or not */
    if(hsc->State == HAL_SMARTCARD_STATE_BUSY_TX) 
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_TX_RX;
    }
    else
    {
      hsc->State = HAL_SMARTCARD_STATE_BUSY_RX;
    }    
    
    /* Set the SMARTCARD DMA transfert complete callback */
    hsc->hdmarx->XferCpltCallback = SMARTCARD_DMAReceiveCplt;
    
    /* Set the SMARTCARD DMA error callback */
    hsc->hdmarx->XferErrorCallback = SMARTCARD_DMAError;
    
    /* Enable the DMA Stream */
    tmp = (uint32_t*)&pData;
    HAL_DMA_Start_IT(hsc->hdmarx, (uint32_t)&hsc->Instance->RDR, *(uint32_t*)tmp, Size);
    
    /* Enable the DMA transfer for the receiver request by setting the DMAR bit 
    in the SMARTCARD associated USART CR3 register */
    hsc->Instance->CR3 |= USART_CR3_DMAR;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hsc);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}
    
/**
  * @brief SMARTCARD interrupt requests handling.
  * @param hsc: SMARTCARD handle
  * @retval None
  */
void HAL_SMARTCARD_IRQHandler(SMARTCARD_HandleTypeDef *hsc)
{
  /* SMARTCARD parity error interrupt occurred -------------------------------*/
  if((__HAL_SMARTCARD_GET_IT(hsc, SMARTCARD_IT_PE) != RESET) && (__HAL_SMARTCARD_GET_IT_SOURCE(hsc, SMARTCARD_IT_PE) != RESET))
  { 
    __HAL_SMARTCARD_CLEAR_PEFLAG(hsc);
    hsc->ErrorCode |= HAL_SMARTCARD_ERROR_PE;
    /* Set the SMARTCARD state ready to be able to start again the process */
    hsc->State = HAL_SMARTCARD_STATE_READY;
  }
  
  /* SMARTCARD frame error interrupt occured ---------------------------------*/
  if((__HAL_SMARTCARD_GET_IT(hsc, SMARTCARD_IT_FE) != RESET) && (__HAL_SMARTCARD_GET_IT_SOURCE(hsc, SMARTCARD_IT_ERR) != RESET))
  { 
    __HAL_SMARTCARD_CLEAR_FEFLAG(hsc);
    hsc->ErrorCode |= HAL_SMARTCARD_ERROR_FE;
    /* Set the SMARTCARD state ready to be able to start again the process */
    hsc->State = HAL_SMARTCARD_STATE_READY;
  }
  
  /* SMARTCARD noise error interrupt occured ---------------------------------*/
  if((__HAL_SMARTCARD_GET_IT(hsc, SMARTCARD_IT_NE) != RESET) && (__HAL_SMARTCARD_GET_IT_SOURCE(hsc, SMARTCARD_IT_ERR) != RESET))
  { 
    __HAL_SMARTCARD_CLEAR_NEFLAG(hsc);
    hsc->ErrorCode |= HAL_SMARTCARD_ERROR_NE; 
    /* Set the SMARTCARD state ready to be able to start again the process */
    hsc->State = HAL_SMARTCARD_STATE_READY;
  }
  
  /* SMARTCARD Over-Run interrupt occured ------------------------------------*/
  if((__HAL_SMARTCARD_GET_IT(hsc, SMARTCARD_IT_ORE) != RESET) && (__HAL_SMARTCARD_GET_IT_SOURCE(hsc, SMARTCARD_IT_ERR) != RESET))
  { 
    __HAL_SMARTCARD_CLEAR_OREFLAG(hsc);
    hsc->ErrorCode |= HAL_SMARTCARD_ERROR_ORE; 
    /* Set the SMARTCARD state ready to be able to start again the process */
    hsc->State = HAL_SMARTCARD_STATE_READY;
  }
  
  /* SMARTCARD receiver timeout interrupt occured ----------------------------*/
  if((__HAL_SMARTCARD_GET_IT(hsc, SMARTCARD_IT_RTO) != RESET) && (__HAL_SMARTCARD_GET_IT_SOURCE(hsc, SMARTCARD_IT_RTO) != RESET))
  { 
    __HAL_SMARTCARD_CLEAR_IT(hsc, SMARTCARD_CLEAR_RTOF);
    hsc->ErrorCode |= HAL_SMARTCARD_ERROR_RTO; 
    /* Set the SMARTCARD state ready to be able to start again the process */
    hsc->State = HAL_SMARTCARD_STATE_READY;
  }
  
  /* Call SMARTCARD Error Call back function if need be ----------------------*/
  if(hsc->ErrorCode != HAL_SMARTCARD_ERROR_NONE)
  {
    HAL_SMARTCARD_ErrorCallback(hsc);
  } 
  
  /* SMARTCARD in mode Receiver ----------------------------------------------*/
  if((__HAL_SMARTCARD_GET_IT(hsc, SMARTCARD_IT_RXNE) != RESET) && (__HAL_SMARTCARD_GET_IT_SOURCE(hsc, SMARTCARD_IT_RXNE) != RESET))
  { 
    SMARTCARD_Receive_IT(hsc);
    /* Clear RXNE interrupt flag */
    __HAL_SMARTCARD_SEND_REQ(hsc, SMARTCARD_RXDATA_FLUSH_REQUEST);
  }
  
  /* SMARTCARD in mode Receiver, end of block interruption -------------------*/
  if((__HAL_SMARTCARD_GET_IT(hsc, SMARTCARD_IT_EOB) != RESET) && (__HAL_SMARTCARD_GET_IT_SOURCE(hsc, SMARTCARD_IT_EOB) != RESET))
  { 
    hsc->State = HAL_SMARTCARD_STATE_READY;
    HAL_SMARTCARD_RxCpltCallback(hsc);
    /* Clear EOBF interrupt after HAL_SMARTCARD_RxCpltCallback() call for the End of Block information
    * to be available during HAL_SMARTCARD_RxCpltCallback() processing */
    __HAL_SMARTCARD_CLEAR_IT(hsc, SMARTCARD_CLEAR_EOBF);
  }  
  
  /* SMARTCARD in mode Transmitter -------------------------------------------*/
  if((__HAL_SMARTCARD_GET_IT(hsc, SMARTCARD_IT_TC) != RESET) && (__HAL_SMARTCARD_GET_IT_SOURCE(hsc, SMARTCARD_IT_TC) != RESET))
  {
    SMARTCARD_Transmit_IT(hsc);
  } 
} 

/**
  * @brief Tx Transfer completed callbacks
  * @param hsc: SMARTCARD handle
  * @retval None
  */
 __weak void HAL_SMARTCARD_TxCpltCallback(SMARTCARD_HandleTypeDef *hsc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SMARTCARD_TxCpltCallback could be implemented in the user file
   */ 
}

/**
  * @brief Rx Transfer completed callbacks
  * @param hsc: SMARTCARD handle
  * @retval None
  */
__weak void HAL_SMARTCARD_RxCpltCallback(SMARTCARD_HandleTypeDef *hsc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SMARTCARD_TxCpltCallback could be implemented in the user file
   */
}

/**
  * @brief SMARTCARD error callbacks
  * @param hsc: SMARTCARD handle
  * @retval None
  */
 __weak void HAL_SMARTCARD_ErrorCallback(SMARTCARD_HandleTypeDef *hsc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SMARTCARD_ErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */  

/** @addtogroup SMARTCARD_Exported_Functions_Group3
  *  @brief   SMARTCARD State functions 
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the SMARTCARD.
     (+) HAL_SMARTCARD_GetState() API is helpful to check in run-time the state of the SMARTCARD peripheral 
     (+) SMARTCARD_SetConfig() API configures the SMARTCARD peripheral  
     (+) SMARTCARD_CheckIdleState() API ensures that TEACK and/or REACK are set after initialization 

@endverbatim
  * @{
  */


/**
  * @brief return the SMARTCARD state
  * @param hsc: SMARTCARD handle
  * @retval HAL state
  */
HAL_SMARTCARD_StateTypeDef HAL_SMARTCARD_GetState(SMARTCARD_HandleTypeDef *hsc)
{
  return hsc->State;
}

/**
* @brief  Return the SMARTCARD error code
* @param  hsc : pointer to a SMARTCARD_HandleTypeDef structure that contains
  *              the configuration information for the specified SMARTCARD.
* @retval SMARTCARD Error Code
*/
uint32_t HAL_SMARTCARD_GetError(SMARTCARD_HandleTypeDef *hsc)
{
  return hsc->ErrorCode;
}

/**
  * @}
  */
  
/**
  * @brief Send an amount of data in non blocking mode 
  * @param hsc: SMARTCARD handle.
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_SMARTCARD_Transmit_IT()      
  * @retval HAL status
  */
static HAL_StatusTypeDef SMARTCARD_Transmit_IT(SMARTCARD_HandleTypeDef *hsc)
{
  if((hsc->State == HAL_SMARTCARD_STATE_BUSY_TX) || (hsc->State == HAL_SMARTCARD_STATE_BUSY_TX_RX)) 
  {
    if(hsc->TxXferCount == 0)
    {
      /* Disable the SMARTCARD Transmit Complete Interrupt */
      __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_TC);
      
      /* Check if a receive Process is ongoing or not */
      if(hsc->State == HAL_SMARTCARD_STATE_BUSY_TX_RX) 
      {
        hsc->State = HAL_SMARTCARD_STATE_BUSY_RX;
      }
      else
      { 
        /* Disable the SMARTCARD Error Interrupt: (Frame error, noise error, overrun error) */
        __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_ERR);
      
        hsc->State = HAL_SMARTCARD_STATE_READY;
      }
      
      HAL_SMARTCARD_TxCpltCallback(hsc);
      
      return HAL_OK;
    }
    else
    {    
      hsc->Instance->TDR = (*hsc->pTxBuffPtr++ & (uint8_t)0xFF);     
      hsc->TxXferCount--;
  
      return HAL_OK;
    }
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Receive an amount of data in non blocking mode 
  * @param hsc: SMARTCARD handle.
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_SMARTCARD_Receive_IT()      
  * @retval HAL status
  */
static HAL_StatusTypeDef SMARTCARD_Receive_IT(SMARTCARD_HandleTypeDef *hsc)
{
  if((hsc->State == HAL_SMARTCARD_STATE_BUSY_RX) || (hsc->State == HAL_SMARTCARD_STATE_BUSY_TX_RX))
  {
    *hsc->pRxBuffPtr++ = (uint8_t)(hsc->Instance->RDR & (uint8_t)0xFF);  
    
    if(--hsc->RxXferCount == 0)
    {
      while(HAL_IS_BIT_SET(hsc->Instance->ISR, SMARTCARD_FLAG_RXNE))
      {
      }
      __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_RXNE);
      
      /* Check if a transmit Process is ongoing or not */
      if(hsc->State == HAL_SMARTCARD_STATE_BUSY_TX_RX) 
      {
        hsc->State = HAL_SMARTCARD_STATE_BUSY_TX;
      }
      else
      {
        /* Disable the SMARTCARD Parity Error Interrupt */
        __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_PE);
         
        /* Disable the SMARTCARD Error Interrupt: (Frame error, noise error, overrun error) */
        __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_ERR);
        
        hsc->State = HAL_SMARTCARD_STATE_READY;
      }
      
      HAL_SMARTCARD_RxCpltCallback(hsc);
      
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
  * @brief Configure the SMARTCARD associated USART peripheral 
  * @param hsc: SMARTCARD handle
  * @retval None
  */
static void SMARTCARD_SetConfig(SMARTCARD_HandleTypeDef *hsc)
{
  uint32_t tmpreg = 0x00000000;
  uint32_t clocksource = 0x00000000;
  
  /* Check the parameters */ 
  assert_param(IS_SMARTCARD_INSTANCE(hsc->Instance));
  assert_param(IS_SMARTCARD_BAUDRATE(hsc->Init.BaudRate)); 
  assert_param(IS_SMARTCARD_WORD_LENGTH(hsc->Init.WordLength));  
  assert_param(IS_SMARTCARD_STOPBITS(hsc->Init.StopBits));   
  assert_param(IS_SMARTCARD_PARITY(hsc->Init.Parity));
  assert_param(IS_SMARTCARD_MODE(hsc->Init.Mode));
  assert_param(IS_SMARTCARD_POLARITY(hsc->Init.CLKPolarity));
  assert_param(IS_SMARTCARD_PHASE(hsc->Init.CLKPhase));
  assert_param(IS_SMARTCARD_LASTBIT(hsc->Init.CLKLastBit));    
  assert_param(IS_SMARTCARD_ONE_BIT_SAMPLE(hsc->Init.OneBitSampling));
  assert_param(IS_SMARTCARD_NACK(hsc->Init.NACKState));
  assert_param(IS_SMARTCARD_TIMEOUT(hsc->Init.TimeOutEnable));
  assert_param(IS_SMARTCARD_AUTORETRY_COUNT(hsc->Init.AutoRetryCount)); 

  /*-------------------------- USART CR1 Configuration -----------------------*/
  /* In SmartCard mode, M and PCE are forced to 1 (8 bits + parity).
   * Oversampling is forced to 16 (OVER8 = 0).
   * Configure the Parity and Mode: 
   *  set PS bit according to hsc->Init.Parity value
   *  set TE and RE bits according to hsc->Init.Mode value */
  tmpreg = (uint32_t) hsc->Init.Parity | hsc->Init.Mode;
  /* in case of TX-only mode, if NACK is enabled, the USART must be able to monitor 
     the bidirectional line to detect a NACK signal in case of parity error. 
     Therefore, the receiver block must be enabled as well (RE bit must be set). */
  if((hsc->Init.Mode == SMARTCARD_MODE_TX) && (hsc->Init.NACKState == SMARTCARD_NACK_ENABLE))
  {
    tmpreg |= USART_CR1_RE;   
  }
  tmpreg |= (uint32_t) hsc->Init.WordLength;
  MODIFY_REG(hsc->Instance->CR1, USART_CR1_FIELDS, tmpreg);

  /*-------------------------- USART CR2 Configuration -----------------------*/
  /* Stop bits are forced to 1.5 (STOP = 11) */
  tmpreg = hsc->Init.StopBits;
  /* Synchronous mode is activated by default */
  tmpreg |= (uint32_t) USART_CR2_CLKEN | hsc->Init.CLKPolarity; 
  tmpreg |= (uint32_t) hsc->Init.CLKPhase | hsc->Init.CLKLastBit;
  tmpreg |= (uint32_t) hsc->Init.TimeOutEnable;
  MODIFY_REG(hsc->Instance->CR2, USART_CR2_FIELDS, tmpreg); 
    
  /*-------------------------- USART CR3 Configuration -----------------------*/
  /* Configure 
   * - one-bit sampling method versus three samples' majority rule 
   *   according to hsc->Init.OneBitSampling 
   * - NACK transmission in case of parity error according 
   *   to hsc->Init.NACKEnable   
   * - autoretry counter according to hsc->Init.AutoRetryCount     */
  tmpreg =  (uint32_t) hsc->Init.OneBitSampling | hsc->Init.NACKState;
  tmpreg |= (uint32_t) (hsc->Init.AutoRetryCount << SMARTCARD_CR3_SCARCNT_LSB_POS);
  MODIFY_REG(hsc->Instance-> CR3,USART_CR3_FIELDS, tmpreg);
  
  /*-------------------------- USART GTPR Configuration ----------------------*/
  tmpreg = (uint32_t) (hsc->Init.Prescaler | (hsc->Init.GuardTime << SMARTCARD_GTPR_GT_LSB_POS));
  MODIFY_REG(hsc->Instance->GTPR, (uint32_t)(USART_GTPR_GT|USART_GTPR_PSC), tmpreg); 
  
  /*-------------------------- USART RTOR Configuration ----------------------*/ 
  tmpreg =   (uint32_t) (hsc->Init.BlockLength << SMARTCARD_RTOR_BLEN_LSB_POS);
  if(hsc->Init.TimeOutEnable == SMARTCARD_TIMEOUT_ENABLE)
  {
    assert_param(IS_SMARTCARD_TIMEOUT_VALUE(hsc->Init.TimeOutValue));
    tmpreg |=  (uint32_t) hsc->Init.TimeOutValue;
  }
  MODIFY_REG(hsc->Instance->RTOR, (USART_RTOR_RTO|USART_RTOR_BLEN), tmpreg);
  
  /*-------------------------- USART BRR Configuration -----------------------*/
  SMARTCARD_GETCLOCKSOURCE(hsc, clocksource);
  switch (clocksource)
  {
  case SMARTCARD_CLOCKSOURCE_PCLK1: 
    hsc->Instance->BRR = (uint16_t)(HAL_RCC_GetPCLK1Freq() / hsc->Init.BaudRate);
    break;
  case SMARTCARD_CLOCKSOURCE_PCLK2: 
    hsc->Instance->BRR = (uint16_t)(HAL_RCC_GetPCLK2Freq() / hsc->Init.BaudRate);
    break;
  case SMARTCARD_CLOCKSOURCE_HSI: 
    hsc->Instance->BRR = (uint16_t)(HSI_VALUE / hsc->Init.BaudRate); 
    break; 
  case SMARTCARD_CLOCKSOURCE_SYSCLK:  
    hsc->Instance->BRR = (uint16_t)(HAL_RCC_GetSysClockFreq() / hsc->Init.BaudRate);
    break;  
  case SMARTCARD_CLOCKSOURCE_LSE:                
    hsc->Instance->BRR = (uint16_t)(LSE_VALUE / hsc->Init.BaudRate); 
    break;
  default:
    break;
  } 
}

/**
  * @brief Check the SMARTCARD Idle State
  * @param hsc: SMARTCARD handle
  * @retval HAL status
  */
static HAL_StatusTypeDef SMARTCARD_CheckIdleState(SMARTCARD_HandleTypeDef *hsc)
{
  
  /* Initialize the SMARTCARD ErrorCode */
  hsc->ErrorCode = HAL_SMARTCARD_ERROR_NONE;

  /* Check if the Transmitter is enabled */
  if((hsc->Instance->CR1 & USART_CR1_TE) == USART_CR1_TE)
  {
    /* Wait until TEACK flag is set */
    if(SMARTCARD_WaitOnFlagUntilTimeout(hsc, USART_ISR_TEACK, RESET, TEACK_REACK_TIMEOUT) != HAL_OK)  
    { 
      return HAL_TIMEOUT;
    } 
  }
  /* Check if the Receiver is enabled */
  if((hsc->Instance->CR1 & USART_CR1_RE) == USART_CR1_RE)
  {
    /* Wait until REACK flag is set */
    if(SMARTCARD_WaitOnFlagUntilTimeout(hsc, USART_ISR_REACK, RESET, TEACK_REACK_TIMEOUT) != HAL_OK)  
    { 
      return HAL_TIMEOUT;
    }
  }
  
  /* Process Unlocked */
  __HAL_UNLOCK(hsc);
        
  /* Initialize the SMARTCARD state*/
  hsc->State= HAL_SMARTCARD_STATE_READY;
  
  return HAL_OK;
}

/**
  * @brief Configure the SMARTCARD associated USART peripheral advanced feautures 
  * @param hsc: SMARTCARD handle  
  * @retval None
  */
static void SMARTCARD_AdvFeatureConfig(SMARTCARD_HandleTypeDef *hsc)
{  
  /* Check whether the set of advanced features to configure is properly set */ 
  assert_param(IS_SMARTCARD_ADVFEATURE_INIT(hsc->AdvancedInit.AdvFeatureInit));
  
  /* if required, configure TX pin active level inversion */
  if(HAL_IS_BIT_SET(hsc->AdvancedInit.AdvFeatureInit, SMARTCARD_ADVFEATURE_TXINVERT_INIT))
  {
    assert_param(IS_SMARTCARD_ADVFEATURE_TXINV(hsc->AdvancedInit.TxPinLevelInvert));
    MODIFY_REG(hsc->Instance->CR2, USART_CR2_TXINV, hsc->AdvancedInit.TxPinLevelInvert);
  }
  
  /* if required, configure RX pin active level inversion */
  if(HAL_IS_BIT_SET(hsc->AdvancedInit.AdvFeatureInit, SMARTCARD_ADVFEATURE_RXINVERT_INIT))
  {
    assert_param(IS_SMARTCARD_ADVFEATURE_RXINV(hsc->AdvancedInit.RxPinLevelInvert));
    MODIFY_REG(hsc->Instance->CR2, USART_CR2_RXINV, hsc->AdvancedInit.RxPinLevelInvert);
  }
  
  /* if required, configure data inversion */
  if(HAL_IS_BIT_SET(hsc->AdvancedInit.AdvFeatureInit, SMARTCARD_ADVFEATURE_DATAINVERT_INIT))
  {
    assert_param(IS_SMARTCARD_ADVFEATURE_DATAINV(hsc->AdvancedInit.DataInvert));
    MODIFY_REG(hsc->Instance->CR2, USART_CR2_DATAINV, hsc->AdvancedInit.DataInvert);
  }
  
  /* if required, configure RX/TX pins swap */
  if(HAL_IS_BIT_SET(hsc->AdvancedInit.AdvFeatureInit, SMARTCARD_ADVFEATURE_SWAP_INIT))
  {
    assert_param(IS_SMARTCARD_ADVFEATURE_SWAP(hsc->AdvancedInit.Swap));
    MODIFY_REG(hsc->Instance->CR2, USART_CR2_SWAP, hsc->AdvancedInit.Swap);
  }
  
  /* if required, configure RX overrun detection disabling */
  if(HAL_IS_BIT_SET(hsc->AdvancedInit.AdvFeatureInit, SMARTCARD_ADVFEATURE_RXOVERRUNDISABLE_INIT))
  {
    assert_param(IS_SMARTCARD_OVERRUN(hsc->AdvancedInit.OverrunDisable));  
    MODIFY_REG(hsc->Instance->CR3, USART_CR3_OVRDIS, hsc->AdvancedInit.OverrunDisable);
  }
  
  /* if required, configure DMA disabling on reception error */
  if(HAL_IS_BIT_SET(hsc->AdvancedInit.AdvFeatureInit, SMARTCARD_ADVFEATURE_DMADISABLEONERROR_INIT))
  {
    assert_param(IS_SMARTCARD_ADVFEATURE_DMAONRXERROR(hsc->AdvancedInit.DMADisableonRxError));   
    MODIFY_REG(hsc->Instance->CR3, USART_CR3_DDRE, hsc->AdvancedInit.DMADisableonRxError);
  }
  
  /* if required, configure MSB first on communication line */  
  if(HAL_IS_BIT_SET(hsc->AdvancedInit.AdvFeatureInit, SMARTCARD_ADVFEATURE_MSBFIRST_INIT))
  {
    assert_param(IS_SMARTCARD_ADVFEATURE_MSBFIRST(hsc->AdvancedInit.MSBFirst));   
    MODIFY_REG(hsc->Instance->CR2, USART_CR2_MSBFIRST, hsc->AdvancedInit.MSBFirst);
  }
}
  
/**
  * @brief  This function handles SMARTCARD Communication Timeout.
  * @param  hsc: SMARTCARD handle
  * @param  Flag: specifies the SMARTCARD flag to check.
  * @param  Status: The new Flag status (SET or RESET).
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef SMARTCARD_WaitOnFlagUntilTimeout(SMARTCARD_HandleTypeDef *hsc, uint32_t Flag, FlagStatus Status, uint32_t Timeout)  
{
  uint32_t tickstart = 0x00;
  tickstart = HAL_GetTick();

  /* Wait until flag is set */
  if(Status == RESET)
  {    
    while(__HAL_SMARTCARD_GET_FLAG(hsc, Flag) == RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
          __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_TXE);
          __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_RXNE);
          __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_PE);
          __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_ERR);

          hsc->State= HAL_SMARTCARD_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hsc);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {
    while(__HAL_SMARTCARD_GET_FLAG(hsc, Flag) != RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
          __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_TXE);
          __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_RXNE);
          __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_PE);
          __HAL_SMARTCARD_DISABLE_IT(hsc, SMARTCARD_IT_ERR);

          hsc->State= HAL_SMARTCARD_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hsc);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief DMA SMARTCARD transmit process complete callback 
  * @param hdma: DMA handle
  * @retval None
  */
static void SMARTCARD_DMATransmitCplt(DMA_HandleTypeDef *hdma)     
{
  SMARTCARD_HandleTypeDef* hsmartcard = ( SMARTCARD_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  hsmartcard->TxXferCount = 0;

  /* Disable the DMA transfer for transmit request by resetting the DMAT bit
  in the SMARTCARD associated USART CR3 register */
  hsmartcard->Instance->CR3 &= (uint16_t)~((uint16_t)USART_CR3_DMAT);

  /* Enable the SMARTCARD Transmit Complete Interrupt */
  __HAL_SMARTCARD_ENABLE_IT(hsmartcard, SMARTCARD_IT_TC);
}

/**
  * @brief DMA SMARTCARD receive process complete callback 
  * @param hdma: DMA handle
  * @retval None
  */
static void SMARTCARD_DMAReceiveCplt(DMA_HandleTypeDef *hdma)  
{
  SMARTCARD_HandleTypeDef* hsc = ( SMARTCARD_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  hsc->RxXferCount = 0;
  
  /* Disable the DMA transfer for the receiver request by setting the DMAR bit 
     in the SMARTCARD associated USART CR3 register */
  hsc->Instance->CR3 &= (uint16_t)~((uint16_t)USART_CR3_DMAR);
  
  /* Check if a transmit Process is ongoing or not */
  if(hsc->State == HAL_SMARTCARD_STATE_BUSY_TX_RX) 
  {
    hsc->State = HAL_SMARTCARD_STATE_BUSY_TX;
  }
  else
  {
    hsc->State = HAL_SMARTCARD_STATE_READY;
  }
  
  HAL_SMARTCARD_RxCpltCallback(hsc);
}

/**
  * @brief DMA SMARTCARD communication error callback 
  * @param hdma: DMA handle
  * @retval None
  */
static void SMARTCARD_DMAError(DMA_HandleTypeDef *hdma)
{
  SMARTCARD_HandleTypeDef* hsc = ( SMARTCARD_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  hsc->RxXferCount = 0;
  hsc->TxXferCount = 0;
  hsc->State= HAL_SMARTCARD_STATE_READY;
  hsc->ErrorCode |= HAL_SMARTCARD_ERROR_DMA;
  HAL_SMARTCARD_ErrorCallback(hsc);
}
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

