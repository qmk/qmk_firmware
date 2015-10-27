/**
  ******************************************************************************
  * @file    stm32f3xx_hal_irda.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   IRDA HAL module driver.
  * 
  *          This file provides firmware functions to manage the following 
  *          functionalities of the IrDA (Infrared Data Association) Peripheral 
  *          (IRDA)
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *
  *           
  @verbatim       
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
    The IRDA HAL driver can be used as follows:
    
    (#) Declare a IRDA_HandleTypeDef handle structure.
    (#) Initialize the IRDA low level resources by implementing the HAL_IRDA_MspInit() API
        in setting the associated USART or UART in IRDA mode:
        (##) Enable the USARTx/UARTx interface clock.
        (##) USARTx/UARTx pins configuration:
            (+) Enable the clock for the USARTx/UARTx GPIOs.
            (+) Configure these USARTx/UARTx pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (HAL_IRDA_Transmit_IT()
             and HAL_IRDA_Receive_IT() APIs):
            (+) Configure the USARTx/UARTx interrupt priority.
            (+) Enable the NVIC IRDA IRQ handle.
            (@) The specific IRDA interrupts (Transmission complete interrupt, 
                RXNE interrupt and Error Interrupts) will be managed using the macros
                __HAL_IRDA_ENABLE_IT() and __HAL_IRDA_DISABLE_IT() inside the transmit and receive process.
        (##) DMA Configuration if you need to use DMA process (HAL_IRDA_Transmit_DMA()
             and HAL_IRDA_Receive_DMA() APIs):
            (+) Declare a DMA handle structure for the Tx/Rx stream.
            (+) Enable the DMAx interface clock.
            (+) Configure the declared DMA handle structure with the required Tx/Rx parameters.                
            (+) Configure the DMA Tx/Rx Stream.
            (+) Associate the initilalized DMA handle to the IRDA DMA Tx/Rx handle.
            (+) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx Stream.

    (#) Program the Baud Rate, Word Length and Parity and Mode(Receiver/Transmitter),
        the normal or low power mode and the clock prescaler in the hirda Init structure.

    (#) Initialize the IRDA registers by calling
        the HAL_IRDA_Init() API.
        
    (@) This API (HAL_IRDA_Init()) configures also the low level Hardware (GPIO, CLOCK, CORTEX...etc)
        by calling the customized HAL_IRDA_MspInit() API.

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

/** @defgroup IRDA IRDA HAL module driver
  * @brief HAL IRDA module driver
  * @{
  */
#ifdef HAL_IRDA_MODULE_ENABLED
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup IRDA_Private_Constants   IRDA Private Constants
  * @{
  */
#define TEACK_REACK_TIMEOUT            1000
#define IRDA_TXDMA_TIMEOUTVALUE        22000
#define IRDA_TIMEOUT_VALUE             22000
#define IRDA_CR1_FIELDS  ((uint32_t)(USART_CR1_M | USART_CR1_PCE \
                                   | USART_CR1_PS | USART_CR1_TE | USART_CR1_RE))
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup IRDA_Private_Functions IRDA Private Functions
  * @{
  */
static void IRDA_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void IRDA_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void IRDA_DMAError(DMA_HandleTypeDef *hdma); 
static HAL_StatusTypeDef IRDA_SetConfig(IRDA_HandleTypeDef *hirda);
static HAL_StatusTypeDef IRDA_CheckIdleState(IRDA_HandleTypeDef *hirda);
static HAL_StatusTypeDef IRDA_WaitOnFlagUntilTimeout(IRDA_HandleTypeDef *hirda, uint32_t Flag, FlagStatus Status, uint32_t Timeout);
static HAL_StatusTypeDef IRDA_Transmit_IT(IRDA_HandleTypeDef *hirda);
static HAL_StatusTypeDef IRDA_EndTransmit_IT(IRDA_HandleTypeDef *hirda);
static HAL_StatusTypeDef IRDA_Receive_IT(IRDA_HandleTypeDef *hirda);
/**
  * @}
  */
/* Exported functions ---------------------------------------------------------*/

/** @defgroup IRDA_Exported_Functions IRDA Exported Functions
  * @{
  */

/** @defgroup IRDA_Exported_Functions_Group1 Initialization and de-initialization functions 
  *  @brief    Initialization and Configuration functions 
  *
@verbatim    
  ==============================================================================
            ##### Initialization and Configuration functions #####
  ==============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the USARTx 
    in asynchronous IRDA mode.
      (+) For the asynchronous mode only these parameters can be configured: 
        (++) Baud Rate
        (++) Word Length 
        (++) Parity: If the parity is enabled, then the MSB bit of the data written
             in the data register is transmitted but is changed by the parity bit.
             Depending on the frame length defined by the M bit (8-bits or 9-bits)
             or by the M1 and M0 bits (7-bit, 8-bit or 9-bit),
             the possible IRDA frame formats are as listed in the following table:
   +---------------------------------------------------------------+     
   |    M bit  |  PCE bit  |            IRDA frame                 |
   |-----------|-----------|---------------------------------------|             
   |     0     |     0     |    | SB | 8-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     0     |     1     |    | SB | 7-bit data | PB | STB |     |
   |-----------|-----------|---------------------------------------|  
   |     1     |     0     |    | SB | 9-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     1     |     1     |    | SB | 8-bit data | PB | STB |     |
   +---------------------------------------------------------------+     
   | M1M0 bits |  PCE bit  |            IRDA frame                 |
   |-----------------------|---------------------------------------|             
   |     10    |     0     |    | SB | 7-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     10    |     1     |    | SB | 6-bit data | PB | STB |     |   
   +---------------------------------------------------------------+                   
          
        (++) Power mode
        (++) Prescaler setting       
        (++) Receiver/transmitter modes

    [..]
    The HAL_IRDA_Init() API follows the USART asynchronous configuration procedures 
    (details for the procedures are available in reference manual).

@endverbatim
  * @{
  */

/**
  * @brief Initializes the IRDA mode according to the specified
  *         parameters in the IRDA_InitTypeDef and creates the associated handle .
  * @param hirda: IRDA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Init(IRDA_HandleTypeDef *hirda)
{
  /* Check the IRDA handle allocation */
  if(hirda == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the USART/UART associated to the IRDA handle */
  assert_param(IS_IRDA_INSTANCE(hirda->Instance));
  
  if(hirda->State == HAL_IRDA_STATE_RESET)
  {   
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_IRDA_MspInit(hirda);
  }
  
  hirda->State = HAL_IRDA_STATE_BUSY;
  
  /* Disable the Peripheral to update the configuration registers */
  __HAL_IRDA_DISABLE(hirda);
  
  /* Set the IRDA Communication parameters */
  if (IRDA_SetConfig(hirda) == HAL_ERROR)
  {
    return HAL_ERROR;
  }  
  
  /* In IRDA mode, the following bits must be kept cleared: 
  - LINEN, STOP and CLKEN bits in the USART_CR2 register,
  - SCEN and HDSEL bits in the USART_CR3 register.*/
  hirda->Instance->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN | USART_CR2_STOP); 
  hirda->Instance->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL); 
   
  /* set the UART/USART in IRDA mode */
  hirda->Instance->CR3 |= USART_CR3_IREN; 
    
  /* Enable the Peripheral */
  __HAL_IRDA_ENABLE(hirda);
  
  /* TEACK and/or REACK to check before moving hirda->State to Ready */
  return (IRDA_CheckIdleState(hirda));
}

/**
  * @brief DeInitializes the IRDA peripheral 
  * @param hirda: IRDA handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_DeInit(IRDA_HandleTypeDef *hirda)
{
  /* Check the IRDA handle allocation */
  if(hirda == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the USART/UART associated to the IRDA handle */
  assert_param(IS_IRDA_INSTANCE(hirda->Instance));

  hirda->State = HAL_IRDA_STATE_BUSY;
  
  /* DeInit the low level hardware */
  HAL_IRDA_MspDeInit(hirda);
  /* Disable the Peripheral */
  __HAL_IRDA_DISABLE(hirda);
  
  hirda->ErrorCode = HAL_IRDA_ERROR_NONE;
  hirda->State = HAL_IRDA_STATE_RESET;
  
  /* Process Unlock */
  __HAL_UNLOCK(hirda);
  
  return HAL_OK;
}

/**
  * @brief IRDA MSP Init
  * @param hirda: IRDA handle
  * @retval None
  */
 __weak void HAL_IRDA_MspInit(IRDA_HandleTypeDef *hirda)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_IRDA_MspInit can be implemented in the user file
   */ 
}

/**
  * @brief IRDA MSP DeInit
  * @param hirda: IRDA handle
  * @retval None
  */
 __weak void HAL_IRDA_MspDeInit(IRDA_HandleTypeDef *hirda)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_IRDA_MspDeInit can be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup IRDA_Exported_Functions_Group2 Input and Output operation functions 
  *  @brief   IRDA Transmit and Receive functions 
  *
@verbatim   
 ===============================================================================
                      ##### I/O operation functions #####
 ===============================================================================  
    This subsection provides a set of functions allowing to manage the IRDA asynchronous
    data transfers.

    (#) There are two modes of transfer:
       (+) Blocking mode: the communication is performed in polling mode. 
            The HAL status of all data processing is returned by the same function 
            after finishing transfer.  
       (+) No-Blocking mode: the communication is performed using Interrupts 
           or DMA, these API's return the HAL status.
           The end of the data processing will be indicated through the 
           dedicated IRDA IRQ when using Interrupt mode or the DMA IRQ when 
           using DMA mode.
           The HAL_IRDA_TxCpltCallback(), HAL_IRDA_RxCpltCallback() user callbacks 
           will be executed respectivelly at the end of the Transmit or Receive process
           The HAL_IRDA_ErrorCallback() user callback will be executed when a communication error is detected

    (#) Blocking mode API's are :
        (+) HAL_IRDA_Transmit()
        (+) HAL_IRDA_Receive() 
        
    (#) Non-Blocking mode API's with Interrupt are :
        (+) HAL_IRDA_Transmit_IT()
        (+) HAL_IRDA_Receive_IT()
        (+) HAL_IRDA_IRQHandler()
        (+) IRDA_Transmit_IT()
        (+) IRDA_Receive_IT()

    (#) Non-Blocking mode functions with DMA are :
        (+) HAL_IRDA_Transmit_DMA()
        (+) HAL_IRDA_Receive_DMA()

    (#) A set of Transfer Complete Callbacks are provided in No_Blocking mode:
        (+) HAL_IRDA_TxCpltCallback()
        (+) HAL_IRDA_RxCpltCallback()
        (+) HAL_IRDA_ErrorCallback()
      
@endverbatim
  * @{
  */

/**
  * @brief Send an amount of data in blocking mode 
  * @param hirda: IRDA handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @param Timeout: Duration of the timeout
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Transmit(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
   uint16_t* tmp;
   
  if ((hirda->State == HAL_IRDA_STATE_READY) || (hirda->State == HAL_IRDA_STATE_BUSY_RX)) 
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
      hirda->TxXferCount--;

        if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_TXE, RESET, Timeout) != HAL_OK)
        { 
          return HAL_TIMEOUT;
        }
      if ((hirda->Init.WordLength == IRDA_WORDLENGTH_9B) && (hirda->Init.Parity == IRDA_PARITY_NONE))
        {
          tmp = (uint16_t*) pData;
          hirda->Instance->TDR = (*tmp & (uint16_t)0x01FF);   
          pData +=2;
        }
        else
        { 
          hirda->Instance->TDR = (*pData++ & (uint8_t)0xFF); 
        }
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
  * @brief Receive an amount of data in blocking mode 
  * @param hirda: IRDA handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be received
  * @param Timeout: Duration of the timeout
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Receive(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{ 
  uint16_t* tmp;
  uint16_t uhMask;
  
  if ((hirda->State == HAL_IRDA_STATE_READY) || (hirda->State == HAL_IRDA_STATE_BUSY_TX))
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

    /* Computation of the mask to apply to the RDR register 
       of the UART associated to the IRDA */
    __HAL_IRDA_MASK_COMPUTATION(hirda);
    uhMask = hirda->Mask;

    /* Check data remaining to be received */
    while(hirda->RxXferCount > 0)
    {
      hirda->RxXferCount--;

      if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_RXNE, RESET, Timeout) != HAL_OK)
      { 
        return HAL_TIMEOUT;
      }         
      if ((hirda->Init.WordLength == IRDA_WORDLENGTH_9B) && (hirda->Init.Parity == IRDA_PARITY_NONE))
      {
        tmp = (uint16_t*) pData ;
        *tmp = (uint16_t)(hirda->Instance->RDR & uhMask);
        pData +=2;
      }
      else
      {
        *pData++ = (uint8_t)(hirda->Instance->RDR & (uint8_t)uhMask); 
      }       
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
  * @brief Send an amount of data in interrupt mode 
  * @param hirda: IRDA handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Transmit_IT(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size)
{
  if ((hirda->State == HAL_IRDA_STATE_READY) || (hirda->State == HAL_IRDA_STATE_BUSY_RX))
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
  * @brief Receive an amount of data in interrupt mode 
  * @param hirda: IRDA handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Receive_IT(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size)
{  
  if ((hirda->State == HAL_IRDA_STATE_READY) || (hirda->State == HAL_IRDA_STATE_BUSY_TX))
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
  
    /* Computation of the mask to apply to the RDR register 
       of the UART associated to the IRDA */
    __HAL_IRDA_MASK_COMPUTATION(hirda); 
  
    hirda->ErrorCode = HAL_IRDA_ERROR_NONE;  
    if(hirda->State == HAL_IRDA_STATE_BUSY_TX) 
    {
      hirda->State = HAL_IRDA_STATE_BUSY_TX_RX;
    }
    else
    {
      hirda->State = HAL_IRDA_STATE_BUSY_RX;
    }
    
    /* Enable the IRDA Parity Error Interrupt */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_PE);
    
    /* Enable the IRDA Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_ERR);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hirda);
    
    /* Enable the IRDA Data Register not empty Interrupt */
    __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_RXNE);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
  * @brief Send an amount of data in DMA mode 
  * @param hirda: IRDA handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Transmit_DMA(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size)
{
  uint32_t *tmp;
  
  if ((hirda->State == HAL_IRDA_STATE_READY) || (hirda->State == HAL_IRDA_STATE_BUSY_RX))
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
    
    /* Set the DMA error callback */
    hirda->hdmatx->XferErrorCallback = IRDA_DMAError;

    /* Enable the IRDA transmit DMA channel */
    tmp = (uint32_t*)&pData;
    HAL_DMA_Start_IT(hirda->hdmatx, *(uint32_t*)tmp, (uint32_t)&hirda->Instance->TDR, Size);
    
    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the IRDA CR3 register */
    hirda->Instance->CR3 |= USART_CR3_DMAT;
    
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
  * @brief Receive an amount of data in DMA mode 
  * @param hirda: IRDA handle
  * @param pData: pointer to data buffer
  * @param Size: amount of data to be received
  * @note   When the IRDA parity is enabled (PCE = 1), the received data contain 
  *         the parity bit (MSB position)  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IRDA_Receive_DMA(IRDA_HandleTypeDef *hirda, uint8_t *pData, uint16_t Size)
{
  uint32_t *tmp;
  
  if ((hirda->State == HAL_IRDA_STATE_READY) || (hirda->State == HAL_IRDA_STATE_BUSY_TX))
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
    
    /* Set the DMA error callback */
    hirda->hdmarx->XferErrorCallback = IRDA_DMAError;

    /* Enable the DMA channel */
    tmp = (uint32_t*)&pData;
    HAL_DMA_Start_IT(hirda->hdmarx, (uint32_t)&hirda->Instance->RDR, *(uint32_t*)tmp, Size);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit 
       in the IRDA CR3 register */
     hirda->Instance->CR3 |= USART_CR3_DMAR;
    
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
  * @brief This function handles IRDA interrupt request.
  * @param hirda: IRDA handle
  * @retval None
  */
void HAL_IRDA_IRQHandler(IRDA_HandleTypeDef *hirda)
{
  /* IRDA parity error interrupt occurred -------------------------------------*/
  if((__HAL_IRDA_GET_IT(hirda, IRDA_IT_PE) != RESET) && (__HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_PE) != RESET))
  { 
    __HAL_IRDA_CLEAR_IT(hirda, IRDA_CLEAR_PEF);

    hirda->ErrorCode |= HAL_IRDA_ERROR_PE;
    /* Set the IRDA state ready to be able to start again the process */
    hirda->State = HAL_IRDA_STATE_READY;
  }
  
  /* IRDA frame error interrupt occured --------------------------------------*/
  if((__HAL_IRDA_GET_IT(hirda, IRDA_IT_FE) != RESET) && (__HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_ERR) != RESET))
  { 
    __HAL_IRDA_CLEAR_IT(hirda, IRDA_CLEAR_FEF);

    hirda->ErrorCode |= HAL_IRDA_ERROR_FE;
    /* Set the IRDA state ready to be able to start again the process */
    hirda->State = HAL_IRDA_STATE_READY;
  }
  
  /* IRDA noise error interrupt occured --------------------------------------*/
  if((__HAL_IRDA_GET_IT(hirda, IRDA_IT_NE) != RESET) && (__HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_ERR) != RESET))
  { 
    __HAL_IRDA_CLEAR_IT(hirda, IRDA_CLEAR_NEF);

    hirda->ErrorCode |= HAL_IRDA_ERROR_NE; 
    /* Set the IRDA state ready to be able to start again the process */
    hirda->State = HAL_IRDA_STATE_READY;
  }
  
  /* IRDA Over-Run interrupt occured -----------------------------------------*/
  if((__HAL_IRDA_GET_IT(hirda, IRDA_IT_ORE) != RESET) && (__HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_ERR) != RESET))
  { 
    __HAL_IRDA_CLEAR_IT(hirda, IRDA_CLEAR_OREF);

    hirda->ErrorCode |= HAL_IRDA_ERROR_ORE; 
    /* Set the IRDA state ready to be able to start again the process */
    hirda->State = HAL_IRDA_STATE_READY;
  }
  
  /* Call IRDA Error Call back function if need be --------------------------*/
  if(hirda->ErrorCode != HAL_IRDA_ERROR_NONE)
  {
    HAL_IRDA_ErrorCallback(hirda);
  } 

  /* IRDA in mode Receiver ---------------------------------------------------*/
  if((__HAL_IRDA_GET_IT(hirda, IRDA_IT_RXNE) != RESET) && (__HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_RXNE) != RESET))
  { 
    IRDA_Receive_IT(hirda);
    /* Clear RXNE interrupt flag */
    __HAL_IRDA_SEND_REQ(hirda, IRDA_RXDATA_FLUSH_REQUEST);
  }
  

  /* IRDA in mode Transmitter ------------------------------------------------*/
 if((__HAL_IRDA_GET_IT(hirda, IRDA_IT_TXE) != RESET) &&(__HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_TXE) != RESET))
  {
    IRDA_Transmit_IT(hirda);
  } 
  
  /* IRDA in mode Transmitter (transmission end) -----------------------------*/
 if((__HAL_IRDA_GET_IT(hirda, IRDA_IT_TC) != RESET) &&(__HAL_IRDA_GET_IT_SOURCE(hirda, IRDA_IT_TC) != RESET))
  {
    IRDA_EndTransmit_IT(hirda);
  }   
  
}
/**
  * @}
  */

/**
  * @}
  */  

/** @addtogroup IRDA_Private_Functions IRDA Private Functions
  * @{
  */

/**
  * @brief DMA IRDA Tx transfer completed callback 
  * @param hdma: DMA handle
  * @retval None
  */
static void IRDA_DMATransmitCplt(DMA_HandleTypeDef *hdma)     
{
  IRDA_HandleTypeDef* hirda = ( IRDA_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  hirda->TxXferCount = 0;
  
  /* Disable the DMA transfer for transmit request by setting the DMAT bit
  in the IRDA CR3 register */
  hirda->Instance->CR3 &= (uint16_t)~((uint16_t)USART_CR3_DMAT);
  
  /* Wait for IRDA TC Flag */
  if(IRDA_WaitOnFlagUntilTimeout(hirda, IRDA_FLAG_TC, RESET, IRDA_TXDMA_TIMEOUTVALUE) != HAL_OK)
  {
    /* Timeout Occured */ 
    HAL_IRDA_ErrorCallback(hirda);
  }
  else
  {
    /* No Timeout */
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

/**
  * @brief DMA IRDA Rx Transfer completed callback 
  * @param hdma: DMA handle
  * @retval None
  */
static void IRDA_DMAReceiveCplt(DMA_HandleTypeDef *hdma)  
{
  IRDA_HandleTypeDef* hirda = ( IRDA_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  hirda->RxXferCount = 0;
  
  /* Disable the DMA transfer for the receiver request by setting the DMAR bit 
     in the IRDA CR3 register */
  hirda->Instance->CR3 &= (uint16_t)~((uint16_t)USART_CR3_DMAR);
  
  if(hirda->State == HAL_IRDA_STATE_BUSY_TX_RX) 
  {
    hirda->State = HAL_IRDA_STATE_BUSY_TX;
  }
  else
  {
    hirda->State = HAL_IRDA_STATE_READY;
  }

  HAL_IRDA_RxCpltCallback(hirda);
}

/**
  * @brief DMA IRDA communication error callback 
  * @param hdma: DMA handle
  * @retval None
  */
static void IRDA_DMAError(DMA_HandleTypeDef *hdma)   
{
  IRDA_HandleTypeDef* hirda = ( IRDA_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  hirda->RxXferCount = 0;
  hirda->TxXferCount = 0;
  hirda->State= HAL_IRDA_STATE_READY;
  hirda->ErrorCode |= HAL_IRDA_ERROR_DMA;
  HAL_IRDA_ErrorCallback(hirda);
}
/**
  * @}
  */

/** @addtogroup IRDA_Exported_Functions IRDA Exported Functions
  * @{
  */
  
/** @addtogroup IRDA_Exported_Functions_Group2 Input and Output operation functions 
  * @{
  */

/**
  * @brief Tx Transfer completed callback
  * @param hirda: irda handle
  * @retval None
  */
 __weak void HAL_IRDA_TxCpltCallback(IRDA_HandleTypeDef *hirda)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_IRDA_TxCpltCallback can be implemented in the user file
   */ 
}

/**
  * @brief Rx Transfer completed callback
  * @param hirda: irda handle
  * @retval None
  */
__weak void HAL_IRDA_RxCpltCallback(IRDA_HandleTypeDef *hirda)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_IRDA_TxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief IRDA error callback
  * @param hirda: IRDA handle
  * @retval None
  */
 __weak void HAL_IRDA_ErrorCallback(IRDA_HandleTypeDef *hirda)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_IRDA_ErrorCallback can be implemented in the user file
   */ 
}

/**
  * @}
  */

/**
  * @}
  */
  
/** @addtogroup IRDA_Private_Functions IRDA Private Functions
  * @{
  */
  
/**
  * @brief Receive an amount of data in non blocking mode. 
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_IRDA_Transmit_IT()      
  * @param hirda: IRDA handle
  * @retval HAL status
  */
static HAL_StatusTypeDef IRDA_Transmit_IT(IRDA_HandleTypeDef *hirda)
{
  uint16_t* tmp;
    
  if((hirda->State == HAL_IRDA_STATE_BUSY_TX) || (hirda->State == HAL_IRDA_STATE_BUSY_TX_RX))
  {
 
    if(hirda->TxXferCount == 0)
    {
      /* Disable the IRDA Transmit Data Register Empty Interrupt */
      __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_TXE);
      
      /* Enable the IRDA Transmit Complete Interrupt */    
      __HAL_IRDA_ENABLE_IT(hirda, IRDA_IT_TC);
      
      return HAL_OK;
    }
    else
    {
      if ((hirda->Init.WordLength == IRDA_WORDLENGTH_9B) && (hirda->Init.Parity == IRDA_PARITY_NONE))
      {
        tmp = (uint16_t*) hirda->pTxBuffPtr;
        hirda->Instance->TDR = (*tmp & (uint16_t)0x01FF);
        hirda->pTxBuffPtr += 2;
      }
      else
      {
        hirda->Instance->TDR = (uint8_t)(*hirda->pTxBuffPtr++ & (uint8_t)0xFF); 
      }
      hirda->TxXferCount--;
  
      return HAL_OK;
    }
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
    
    hirda->State = HAL_IRDA_STATE_READY;
  }
  
  HAL_IRDA_TxCpltCallback(hirda);
  
  return HAL_OK;
}


/**
  * @brief Receive an amount of data in non blocking mode. 
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_IRDA_Receive_IT()      
  * @param hirda: IRDA handle
  * @retval HAL status
  */
static HAL_StatusTypeDef IRDA_Receive_IT(IRDA_HandleTypeDef *hirda)
{
  uint16_t* tmp;
  uint16_t uhMask = hirda->Mask;
  
  if ((hirda->State == HAL_IRDA_STATE_BUSY_RX) || (hirda->State == HAL_IRDA_STATE_BUSY_TX_RX))
  {
    
    if ((hirda->Init.WordLength == IRDA_WORDLENGTH_9B) && (hirda->Init.Parity == IRDA_PARITY_NONE))
        {
        tmp = (uint16_t*) hirda->pRxBuffPtr ;
          *tmp = (uint16_t)(hirda->Instance->RDR & uhMask);
         hirda->pRxBuffPtr  +=2;
        }
        else
        {
          *hirda->pRxBuffPtr++ = (uint8_t)(hirda->Instance->RDR & (uint8_t)uhMask); 
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
  * @}
  */

/** @addtogroup IRDA_Exported_Functions IRDA Exported Functions
  * @{
  */

/** @defgroup IRDA_Exported_Functions_Group3 Peripheral State and Errors functions 
  *  @brief   IRDA control functions 
  *
@verbatim   
 ===============================================================================
                   ##### Peripheral State and Error functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the IRDA.
     (+) HAL_IRDA_GetState() API can be helpful to check in run-time the state of the IRDA peripheral. 
     (+) IRDA_SetConfig() API is used to configure the IRDA communications parameters.
@endverbatim
  * @{
  */

/**
  * @brief return the IRDA state
  * @param hirda: irda handle
  * @retval HAL state
  */
HAL_IRDA_StateTypeDef HAL_IRDA_GetState(IRDA_HandleTypeDef *hirda)
{
  return hirda->State;
}

/**
* @brief  Return the IRDA error code
* @param  hirda : pointer to a IRDA_HandleTypeDef structure that contains
  *              the configuration information for the specified IRDA.
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

/** @addtogroup IRDA_Private_Functions IRDA Private Functions
  * @{
  */
  
/**
  * @brief Configure the IRDA peripheral 
  * @param hirda: irda handle
  * @retval None
  */
static HAL_StatusTypeDef IRDA_SetConfig(IRDA_HandleTypeDef *hirda)
{
  uint32_t tmpreg                     = 0x00000000;
  IRDA_ClockSourceTypeDef clocksource = IRDA_CLOCKSOURCE_UNDEFINED;
  HAL_StatusTypeDef ret               = HAL_OK;  
  
  /* Check the communication parameters */ 
  assert_param(IS_IRDA_BAUDRATE(hirda->Init.BaudRate));  
  assert_param(IS_IRDA_WORD_LENGTH(hirda->Init.WordLength));
  assert_param(IS_IRDA_PARITY(hirda->Init.Parity));
  assert_param(IS_IRDA_TX_RX_MODE(hirda->Init.Mode));
  assert_param(IS_IRDA_PRESCALER(hirda->Init.Prescaler)); 
  assert_param(IS_IRDA_POWERMODE(hirda->Init.PowerMode)); 

  /*-------------------------- USART CR1 Configuration -----------------------*/        
  /* Configure the IRDA Word Length, Parity and transfer Mode: 
     Set the M bits according to hirda->Init.WordLength value 
     Set PCE and PS bits according to hirda->Init.Parity value
     Set TE and RE bits according to hirda->Init.Mode value */
  tmpreg = (uint32_t)hirda->Init.WordLength | hirda->Init.Parity | hirda->Init.Mode ;
  
  MODIFY_REG(hirda->Instance->CR1, IRDA_CR1_FIELDS, tmpreg);
  
  /*-------------------------- USART CR3 Configuration -----------------------*/
  MODIFY_REG(hirda->Instance->CR3, USART_CR3_IRLP, hirda->Init.PowerMode);
    
  /*-------------------------- USART GTPR Configuration ----------------------*/  
  MODIFY_REG(hirda->Instance->GTPR, USART_GTPR_PSC, hirda->Init.Prescaler);
  
  /*-------------------------- USART BRR Configuration -----------------------*/ 
  __HAL_IRDA_GETCLOCKSOURCE(hirda, clocksource);
  switch (clocksource)
  {
    case IRDA_CLOCKSOURCE_PCLK1: 
      hirda->Instance->BRR = (uint16_t)(HAL_RCC_GetPCLK1Freq() / hirda->Init.BaudRate);
      break;
    case IRDA_CLOCKSOURCE_PCLK2: 
      hirda->Instance->BRR = (uint16_t)(HAL_RCC_GetPCLK2Freq() / hirda->Init.BaudRate);
      break;
    case IRDA_CLOCKSOURCE_HSI: 
      hirda->Instance->BRR = (uint16_t)(HSI_VALUE / hirda->Init.BaudRate); 
      break; 
    case IRDA_CLOCKSOURCE_SYSCLK:  
      hirda->Instance->BRR = (uint16_t)(HAL_RCC_GetSysClockFreq() / hirda->Init.BaudRate);
      break;  
    case IRDA_CLOCKSOURCE_LSE:                
      hirda->Instance->BRR = (uint16_t)(LSE_VALUE / hirda->Init.BaudRate); 
      break;      
    case IRDA_CLOCKSOURCE_UNDEFINED:                
    default:                
      ret = HAL_ERROR; 
      break;              
  } 
  
  return ret;  
}

/**
  * @brief Check the IRDA Idle State
  * @param hirda: IRDA handle
  * @retval HAL status
  */
static HAL_StatusTypeDef IRDA_CheckIdleState(IRDA_HandleTypeDef *hirda)
{

  /* Initialize the IRDA ErrorCode */
  hirda->ErrorCode = HAL_IRDA_ERROR_NONE;

  /* Check if the Transmitter is enabled */
  if((hirda->Instance->CR1 & USART_CR1_TE) == USART_CR1_TE)
  {
    /* Wait until TEACK flag is set */
    if(IRDA_WaitOnFlagUntilTimeout(hirda, USART_ISR_TEACK, RESET, TEACK_REACK_TIMEOUT) != HAL_OK)
    { 
      /* Timeout Occured */ 
      return HAL_TIMEOUT;
    }     
  }
  /* Check if the Receiver is enabled */
  if((hirda->Instance->CR1 & USART_CR1_RE) == USART_CR1_RE)
  {
    if(IRDA_WaitOnFlagUntilTimeout(hirda, USART_ISR_REACK, RESET, TEACK_REACK_TIMEOUT) != HAL_OK)
    { 
      /* Timeout Occured */ 
      return HAL_TIMEOUT;
    }       
  }
        
  /* Initialize the IRDA state*/
  hirda->State= HAL_IRDA_STATE_READY;  
  /* Process Unlocked */
  __HAL_UNLOCK(hirda);
  
  return HAL_OK;
}

/**
  * @brief  Handle IRDA Communication Timeout.
  * @param  hirda: IRDA handle
  * @param  Flag: specifies the IRDA flag to check.
  * @param  Status: the flag status (SET or RESET). The function is locked in a while loop as long as the flag remains set to Status.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef IRDA_WaitOnFlagUntilTimeout(IRDA_HandleTypeDef *hirda, uint32_t Flag, FlagStatus Status, uint32_t Timeout)  
{
  uint32_t tickstart = HAL_GetTick();
  
  /* Wait until flag is set */
  if(Status == RESET)
  {    
    while(__HAL_IRDA_GET_FLAG(hirda, Flag) == RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_TXE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_RXNE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_PE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_ERR);
          
          hirda->State= HAL_IRDA_STATE_TIMEOUT;
          
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
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_TXE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_RXNE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_PE);
          __HAL_IRDA_DISABLE_IT(hirda, IRDA_IT_ERR);
  
          hirda->State= HAL_IRDA_STATE_TIMEOUT;
          
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
