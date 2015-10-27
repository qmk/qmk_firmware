/**
  ******************************************************************************
  * @file    stm32f3xx_hal_usart.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   USART HAL module driver.
  *
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Universal Synchronous/Asynchronous Receiver Transmitter
  *          Peripheral (USART).
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           
  @verbatim       
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
    The USART HAL driver can be used as follows:
    
    (#) Declare a USART_HandleTypeDef handle structure.
    (#) Initialize the USART low level resources by implement the HAL_USART_MspInit ()API:
        (##) Enable the USARTx interface clock.
        (##) USART pins configuration:
            (+) Enable the clock for the USART GPIOs.
            (+) Configure these USART pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (HAL_USART_Transmit_IT(),
              HAL_USART_Receive_IT() and HAL_USART_TransmitReceive_IT() APIs):
            (+) Configure the USARTx interrupt priority.
            (+) Enable the NVIC USART IRQ handle.
            (@) The specific USART interrupts (Transmission complete interrupt, 
                RXNE interrupt and Error Interrupts) will be managed using the macros
                __HAL_USART_ENABLE_IT() and __HAL_USART_DISABLE_IT() inside the transmit and receive process.
        (##) DMA Configuration if you need to use DMA process (HAL_USART_Transmit_DMA()
             HAL_USART_Receive_IT() and HAL_USART_TransmitReceive_IT() APIs):
            (+) Declare a DMA handle structure for the Tx/Rx channel.
            (+) Enable the DMAx interface clock.
            (+) Configure the declared DMA handle structure with the required Tx/Rx parameters.                
            (+) Configure the DMA Tx/Rx channel.
            (+) Associate the initilalized DMA handle to the USART DMA Tx/Rx handle.
            (+) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx channel.

    (#) Program the Baud Rate, Word Length , Stop Bit, Parity, Hardware 
        flow control and Mode(Receiver/Transmitter) in the husart Init structure.

    (#) Initialize the USART registers by calling the HAL_USART_Init() API:
        (+) These API's configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
            by calling the customed HAL_USART_MspInit(&husart) API.
           
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

/** @defgroup USART HAL USART Synchronous module driver
  * @brief HAL USART Synchronous module driver
  * @{
  */
#ifdef HAL_USART_MODULE_ENABLED
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup UASRT_Private_Constants USART Private Constants
  * @{
  */
#define DUMMY_DATA                  ((uint16_t) 0xFFFF)
#define TEACK_REACK_TIMEOUT         ((uint32_t) 1000)
#define USART_TXDMA_TIMEOUTVALUE            22000
#define USART_TIMEOUT_VALUE                 22000
#define USART_CR1_FIELDS  ((uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | \
                                      USART_CR1_TE | USART_CR1_RE))
#define USART_CR2_FIELDS  ((uint32_t)(USART_CR2_CPHA | USART_CR2_CPOL | \
                                      USART_CR2_CLKEN | USART_CR2_LBCL | USART_CR2_STOP))
/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void USART_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void USART_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void USART_DMATxHalfCplt(DMA_HandleTypeDef *hdma);
static void USART_DMARxHalfCplt(DMA_HandleTypeDef *hdma);
static void USART_DMAError(DMA_HandleTypeDef *hdma); 
static HAL_StatusTypeDef USART_WaitOnFlagUntilTimeout(USART_HandleTypeDef *husart, uint32_t Flag, FlagStatus Status, uint32_t Timeout);
static HAL_StatusTypeDef USART_SetConfig(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_CheckIdleState(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_Transmit_IT(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_EndTransmit_IT(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_Receive_IT(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_TransmitReceive_IT(USART_HandleTypeDef *husart);
/* Exported functions --------------------------------------------------------*/


/** @defgroup USART_Exported_Functions USART Exported Functions
  * @{
  */

/** @defgroup USART_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions 
  *
@verbatim   
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to initialize the USART 
    in asynchronous and in synchronous modes.
      (+) For the asynchronous mode only these parameters can be configured: 
        (++) Baud Rate
        (++) Word Length 
        (++) Stop Bit
        (++) Parity: If the parity is enabled, then the MSB bit of the data written
             in the data register is transmitted but is changed by the parity bit.
             Depending on the frame length defined by the M bit (8-bits or 9-bits)
             or by the M1 and M0 bits (7-bit, 8-bit or 9-bit),
             the possible USART frame formats are as listed in the following table:
   +---------------------------------------------------------------+     
   |    M bit  |  PCE bit  |            USART frame                |
   |-----------|-----------|---------------------------------------|             
   |     0     |     0     |    | SB | 8-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     0     |     1     |    | SB | 7-bit data | PB | STB |     |
   |-----------|-----------|---------------------------------------|  
   |     1     |     0     |    | SB | 9-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     1     |     1     |    | SB | 8-bit data | PB | STB |     |
   +---------------------------------------------------------------+     
   | M1M0 bits |  PCE bit  |            USART frame                |
   |-----------------------|---------------------------------------|             
   |     10    |     0     |    | SB | 7-bit data | STB |          |
   |-----------|-----------|---------------------------------------|  
   |     10    |     1     |    | SB | 6-bit data | PB | STB |     |   
   +---------------------------------------------------------------+          
        (++) USART polarity
        (++) USART phase
        (++) USART LastBit
        (++) Receiver/transmitter modes

    [..]
    The HAL_USART_Init() function follows the USART  synchronous configuration 
    procedure (details for the procedure are available in reference manual).

@endverbatim
  * @{
  */

/**
  * @brief Initializes the USART mode according to the specified
  *         parameters in the USART_InitTypeDef and create the associated handle .
  * @param husart: usart handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Init(USART_HandleTypeDef *husart)
{
  /* Check the USART handle allocation */
  if(husart == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_USART_INSTANCE(husart->Instance));
  
  if(husart->State == HAL_USART_STATE_RESET)
  {   
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_USART_MspInit(husart);
  }
  
  husart->State = HAL_USART_STATE_BUSY;
    
  /* Disable the Peripheral */
  __HAL_USART_DISABLE(husart);
  
  /* Set the Usart Communication parameters */
  if (USART_SetConfig(husart) == HAL_ERROR)
  {
    return HAL_ERROR;
  }
  
  /* In Synchronous mode, the following bits must be kept cleared: 
  - LINEN bit in the USART_CR2 register
  - HDSEL, SCEN and IREN bits in the USART_CR3 register.*/
  husart->Instance->CR2 &= ~USART_CR2_LINEN;
  husart->Instance->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
  
  /* Enable the Peripharal */
  __HAL_USART_ENABLE(husart);
  
  /* TEACK and/or REACK to check before moving husart->State to Ready */
  return (USART_CheckIdleState(husart));
}

/**
  * @brief DeInitializes the USART peripheral 
  * @param husart: usart handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_DeInit(USART_HandleTypeDef *husart)
{
   /* Check the USART handle allocation */
  if(husart == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_USART_INSTANCE(husart->Instance));
  
  husart->State = HAL_USART_STATE_BUSY;
  
  husart->Instance->CR1 = 0x0;
  husart->Instance->CR2 = 0x0;
  husart->Instance->CR3 = 0x0;
  
  /* DeInit the low level hardware */
  HAL_USART_MspDeInit(husart);
  
  husart->ErrorCode = HAL_USART_ERROR_NONE;
  husart->State = HAL_USART_STATE_RESET;
  
  /* Process Unlock */
  __HAL_UNLOCK(husart);
  
  return HAL_OK;
}

/**
  * @brief USART MSP Init
  * @param husart: usart handle
  * @retval None
  */
 __weak void HAL_USART_MspInit(USART_HandleTypeDef *husart)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_MspInit can be implemented in the user file
   */ 
}

/**
  * @brief USART MSP DeInit
  * @param husart: usart handle
  * @retval None
  */
 __weak void HAL_USART_MspDeInit(USART_HandleTypeDef *husart)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_MspDeInit can be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup USART_Exported_Functions_Group2 Input and Output operation functions 
  *  @brief   USART Transmit/Receive functions 
  *
@verbatim   
 ===============================================================================
                      ##### I/O operation functions #####
 ===============================================================================  
    This subsection provides a set of functions allowing to manage the USART synchronous
    data transfers.
      
    [..] The USART supports master mode only: it cannot receive or send data related to an input
         clock (SCLK is always an output).

    (#) There are two mode of transfer:
       (+) Blocking mode: The communication is performed in polling mode. 
            The HAL status of all data processing is returned by the same function 
            after finishing transfer.  
       (+) No-Blocking mode: The communication is performed using Interrupts 
           or DMA, These API's return the HAL status.
           The end of the data processing will be indicated through the 
           dedicated USART IRQ when using Interrupt mode or the DMA IRQ when 
           using DMA mode.
           The HAL_USART_TxCpltCallback(), HAL_USART_RxCpltCallback() and HAL_USART_TxRxCpltCallback() user callbacks 
           will be executed respectivelly at the end of the transmit or Receive process
           The HAL_USART_ErrorCallback()user callback will be executed when a communication error is detected

    (#) Blocking mode API's are :
        (+) HAL_USART_Transmit()in simplex mode
        (+) HAL_USART_Receive() in full duplex receive only
        (+) HAL_USART_TransmitReceive() in full duplex mode         
        
    (#) Non-Blocking mode API's with Interrupt are :
        (+) HAL_USART_Transmit_IT()in simplex mode
        (+) HAL_USART_Receive_IT() in full duplex receive only
        (+) HAL_USART_TransmitReceive_IT()in full duplex mode
        (+) HAL_USART_IRQHandler()

    (#) No-Blocking mode functions with DMA are :
        (+) HAL_USART_Transmit_DMA()in simplex mode
        (+) HAL_USART_Receive_DMA() in full duplex receive only
        (+) HAL_USART_TransmitReceive_DMA() in full duplex mode
        (+) HAL_USART_DMAPause()
        (+) HAL_USART_DMAResume()
        (+) HAL_USART_DMAStop()
          
    (#) A set of Transfer Complete Callbacks are provided in No_Blocking mode:
        (+) HAL_USART_TxCpltCallback()
        (+) HAL_USART_RxCpltCallback()
        (+) HAL_USART_TxHalfCpltCallback()
        (+) HAL_USART_RxHalfCpltCallback()
        (+) HAL_USART_ErrorCallback()
        (+) HAL_USART_TxRxCpltCallback()
      
@endverbatim
  * @{
  */

/**
  * @brief Simplex Send an amount of data in blocking mode 
  * @param husart: USART handle
  * @param pTxData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @param Timeout : Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size, uint32_t Timeout)
{
   uint16_t* tmp; 
    
  if(husart->State == HAL_USART_STATE_READY)
  { 
    if((pTxData == HAL_NULL) || (Size == 0)) 
    {
      return  HAL_ERROR;                                    
    }
    
    /* Process Locked */
    __HAL_LOCK(husart);
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX;
    
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;
    
    /* Check the remaining data to be sent */
    while(husart->TxXferCount > 0)
    {
      husart->TxXferCount--;
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TC, RESET, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pTxData;
        husart->Instance->TDR = (*tmp & (uint16_t)0x01FF);
        pTxData += 2;
      } 
      else
      {
        husart->Instance->TDR = (*pTxData++ & (uint8_t)0xFF);
      }
    }
    
    if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TC, RESET, Timeout) != HAL_OK)
    { 
      return HAL_TIMEOUT;
    }
    
    husart->State = HAL_USART_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(husart);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Receive an amount of data in blocking mode 
  *        To receive synchronous data, dummy data are simultaneously transmitted  
  * @param husart: USART handle
  * @param pRxData: pointer to data buffer
  * @param Size: amount of data to be received
  * @param Timeout : Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Receive(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{ 
  uint16_t* tmp;
  uint16_t uhMask;  
  
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pRxData == HAL_NULL) || (Size == 0)) 
    {
      return  HAL_ERROR;                                    
    }
    /* Process Locked */
    __HAL_LOCK(husart);
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;
    
    husart->RxXferSize = Size; 
    husart->RxXferCount = Size;
    
    /* Computation of USART mask to apply to RDR register */
    __HAL_USART_MASK_COMPUTATION(husart);
    uhMask = husart->Mask;
    
    /* as long as data have to be received */
    while(husart->RxXferCount > 0)
    {
      husart->RxXferCount--;
      
      /* Wait until TC flag is set to send dummy byte in order to generate the 
      * clock for the slave to send data.
       * Whatever the frame length (7, 8 or 9-bit long), the same dummy value 
       * can be written for all the cases. */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TC, RESET, Timeout) != HAL_OK)
      {            
        return HAL_TIMEOUT;  
      }
      husart->Instance->TDR = (DUMMY_DATA & (uint16_t)0x0FF);         
        
      /* Wait for RXNE Flag */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_RXNE, RESET, Timeout) != HAL_OK)
      {            
        return HAL_TIMEOUT;
      }
      
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pRxData ;
        *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
        pRxData +=2;        
      } 
      else
      {
        *pRxData++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);  
      }
    }
    
    husart->State = HAL_USART_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(husart);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Full-Duplex Send and Receive an amount of data in blocking mode 
  * @param husart: USART handle
  * @param pTxData: pointer to TX data buffer
  * @param pRxData: pointer to RX data buffer
  * @param Size: amount of data to be sent (same amount to be received)
  * @param Timeout : Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  uint16_t* tmp;
  uint16_t uhMask;  
  
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == HAL_NULL) || (pRxData == HAL_NULL) || (Size == 0)) 
    {
      return  HAL_ERROR;                                    
    }
    /* Process Locked */
    __HAL_LOCK(husart);
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;
    
    husart->RxXferSize = Size;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;
    husart->RxXferCount = Size;

    /* Computation of USART mask to apply to RDR register */
    __HAL_USART_MASK_COMPUTATION(husart);
    uhMask = husart->Mask;

    /* Check the remain data to be sent */
    while(husart->TxXferCount > 0)
    {
      husart->TxXferCount--;
      husart->RxXferCount--;      
      
     /* Wait until TC flag is set to send data */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TC, RESET, Timeout) != HAL_OK)
      {            
        return HAL_TIMEOUT;
      }
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pTxData;
        husart->Instance->TDR = (*tmp & uhMask);
        pTxData += 2;
      }
      else
      {
        husart->Instance->TDR = (*pTxData++ & (uint8_t)uhMask);         
      }   
        
      /* Wait for RXNE Flag */
      if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_RXNE, RESET, Timeout) != HAL_OK)
      {            
          return HAL_TIMEOUT;
      }
      
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) pRxData ;
        *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
        pRxData +=2;        
      } 
      else
      {
        *pRxData++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);  
      }
    }
    
    husart->State = HAL_USART_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(husart);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Send an amount of data in interrupt mode 
  * @param husart: USART handle
  * @param pTxData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size)
{  
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == HAL_NULL) || (Size == 0)) 
    {
      return HAL_ERROR;                                    
    }
    
    /* Process Locked */
    __HAL_LOCK(husart);
    
    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX;
    
    /* The USART Error Interrupts: (Frame error, noise error, overrun error) 
    are not managed by the USART Transmit Process to avoid the overrun interrupt
    when the usart mode is configured for transmit and receive "USART_MODE_TX_RX"
    to benefit for the frame error and noise interrupts the usart mode should be 
    configured only for transmit "USART_MODE_TX" */
    
    /* Process Unlocked */
    __HAL_UNLOCK(husart);
    
    /* Enable the USART Transmit Data Register Empty Interrupt */
    __HAL_USART_ENABLE_IT(husart, USART_IT_TXE);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Receive an amount of data in blocking mode 
  *        To receive synchronous data, dummy data are simultaneously transmitted  
  * @param husart: usart handle
  * @param pRxData: pointer to data buffer
  * @param Size: amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Receive_IT(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size)
{
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pRxData == HAL_NULL) || (Size == 0)) 
    {
      return HAL_ERROR;                                    
    }
    /* Process Locked */
    __HAL_LOCK(husart);
    
    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->RxXferCount = Size;

    __HAL_USART_MASK_COMPUTATION(husart);

    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;
    
    /* Enable the USART Parity Error Interrupt */
    __HAL_USART_ENABLE_IT(husart, USART_IT_PE);
    
    /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_USART_ENABLE_IT(husart, USART_IT_ERR);
    
    /* Enable the USART Data Register not empty Interrupt */
    __HAL_USART_ENABLE_IT(husart, USART_IT_RXNE);
   
    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    
    /* Send dummy byte in order to generate the clock for the Slave to send the next data */
    if(husart->Init.WordLength == USART_WORDLENGTH_9B)
    {
      husart->Instance->TDR = (DUMMY_DATA & (uint16_t)0x01FF); 
    } 
    else
    {
      husart->Instance->TDR = (DUMMY_DATA & (uint16_t)0x00FF);
    }
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
  * @brief Full-Duplex Send and Receive an amount of data in interrupt mode 
  * @param husart: USART handle
  * @param pTxData: pointer to TX data buffer
  * @param pRxData: pointer to RX data buffer
  * @param Size: amount of data to be sent (same amount to be received)   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData,  uint16_t Size)
{

  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == HAL_NULL) || (pRxData == HAL_NULL) || (Size == 0)) 
    {
      return HAL_ERROR;                                    
    }
    /* Process Locked */
    __HAL_LOCK(husart);
    
    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->RxXferCount = Size;
    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;
    
    /* Computation of USART mask to apply to RDR register */
    __HAL_USART_MASK_COMPUTATION(husart);
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX_RX;
    
    /* Enable the USART Data Register not empty Interrupt */
    __HAL_USART_ENABLE_IT(husart, USART_IT_RXNE); 
    
    /* Enable the USART Parity Error Interrupt */
    __HAL_USART_ENABLE_IT(husart, USART_IT_PE);
    
    /* Enable the USART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_USART_ENABLE_IT(husart, USART_IT_ERR);
    
    /* Process Unlocked */
    __HAL_UNLOCK(husart);
    
    /* Enable the USART Transmit Data Register Empty Interrupt */
    __HAL_USART_ENABLE_IT(husart, USART_IT_TXE);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
  
}

/**
  * @brief Send an amount of data in DMA mode 
  * @param husart: USART handle
  * @param pTxData: pointer to data buffer
  * @param Size: amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_Transmit_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size)
{
  uint32_t *tmp;
  
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == HAL_NULL) || (Size == 0)) 
    {
      return HAL_ERROR; 
    }
    /* Process Locked */
    __HAL_LOCK(husart);  
    
    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    husart->TxXferCount = Size;
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX;
    
    /* Set the USART DMA transfer complete callback */
    husart->hdmatx->XferCpltCallback = USART_DMATransmitCplt;
    
    /* Set the USART DMA Half transfer complete callback */
    husart->hdmatx->XferHalfCpltCallback = USART_DMATxHalfCplt;
    
    /* Set the DMA error callback */
    husart->hdmatx->XferErrorCallback = USART_DMAError;

    /* Enable the USART transmit DMA channel */
    tmp = (uint32_t*)&pTxData;
    HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t*)tmp, (uint32_t)&husart->Instance->TDR, Size);
    
    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the USART CR3 register */
    husart->Instance->CR3 |= USART_CR3_DMAT;
    
    /* Process Unlocked */
    __HAL_UNLOCK(husart);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Receive an amount of data in DMA mode 
  * @param husart: USART handle
  * @param pRxData: pointer to data buffer
  * @param Size: amount of data to be received
  * @note   When the USART parity is enabled (PCE = 1), the received data contain 
  *         the parity bit (MSB position)    
  * @retval HAL status
  * @note The USART DMA transmit channel must be configured in order to generate the clock for the slave.
  */
HAL_StatusTypeDef HAL_USART_Receive_DMA(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size)
{
  uint32_t *tmp;
  
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pRxData == HAL_NULL) || (Size == 0)) 
    {
      return HAL_ERROR;                                    
    }
    
    /* Process Locked */
    __HAL_LOCK(husart);
    
    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->pTxBuffPtr = pRxData;
    husart->TxXferSize = Size;
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_RX;
    
    /* Set the USART DMA Rx transfer complete callback */
    husart->hdmarx->XferCpltCallback = USART_DMAReceiveCplt;
    
    /* Set the USART DMA Half transfer complete callback */
    husart->hdmarx->XferHalfCpltCallback = USART_DMARxHalfCplt;    
    
    /* Set the USART DMA Rx transfer error callback */
    husart->hdmarx->XferErrorCallback = USART_DMAError;
    
    /* Enable the USART receive DMA channel */
    tmp = (uint32_t*)&pRxData;
    HAL_DMA_Start_IT(husart->hdmarx, (uint32_t)&husart->Instance->RDR, *(uint32_t*)tmp, Size);
    
    /* Enable the USART transmit DMA channel: the transmit channel is used in order
       to generate in the non-blocking mode the clock to the slave device, 
       this mode isn't a simplex receive mode but a full-duplex receive mode */
    tmp = (uint32_t*)&pRxData;
    HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t*)tmp, (uint32_t)&husart->Instance->TDR, Size);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit 
    in the USART CR3 register */
    husart->Instance->CR3 |= USART_CR3_DMAR;
    
    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the USART CR3 register */
    husart->Instance->CR3 |= USART_CR3_DMAT;
    
    /* Process Unlocked */
    __HAL_UNLOCK(husart);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
  * @brief Full-Duplex Transmit Receive an amount of data in non blocking mode 
  * @param husart: usart handle
  * @param pTxData: pointer to TX data buffer
  * @param pRxData: pointer to RX data buffer
  * @param Size: amount of data to be received/sent
  * @note   When the USART parity is enabled (PCE = 1) the data received contain the parity bit.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_USART_TransmitReceive_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
  uint32_t *tmp;
  
  if(husart->State == HAL_USART_STATE_READY)
  {
    if((pTxData == HAL_NULL) || (pRxData == HAL_NULL) || (Size == 0)) 
    {
      return HAL_ERROR;                                    
    }
    /* Process Locked */
    __HAL_LOCK(husart);
    
    husart->pRxBuffPtr = pRxData;
    husart->RxXferSize = Size;
    husart->pTxBuffPtr = pTxData;
    husart->TxXferSize = Size;
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    husart->State = HAL_USART_STATE_BUSY_TX_RX;
    
    /* Set the USART DMA Rx transfer complete callback */
    husart->hdmarx->XferCpltCallback = USART_DMAReceiveCplt;
    
    /* Set the USART DMA Half transfer complete callback */
    husart->hdmarx->XferHalfCpltCallback = USART_DMARxHalfCplt;

    /* Set the USART DMA Tx transfer complete callback */
    husart->hdmatx->XferCpltCallback = USART_DMATransmitCplt;
    
    /* Set the USART DMA Half transfer complete callback */
    husart->hdmatx->XferHalfCpltCallback = USART_DMATxHalfCplt;

    /* Set the USART DMA Tx transfer error callback */
    husart->hdmatx->XferErrorCallback = USART_DMAError;
    
    /* Set the USART DMA Rx transfer error callback */
    husart->hdmarx->XferErrorCallback = USART_DMAError;
    
    /* Enable the USART receive DMA channel */
    tmp = (uint32_t*)&pRxData;
    HAL_DMA_Start_IT(husart->hdmarx, (uint32_t)&husart->Instance->RDR, *(uint32_t*)tmp, Size);
    
    /* Enable the USART transmit DMA channel */
    tmp = (uint32_t*)&pTxData;
    HAL_DMA_Start_IT(husart->hdmatx, *(uint32_t*)tmp, (uint32_t)&husart->Instance->TDR, Size);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit 
    in the USART CR3 register */
    husart->Instance->CR3 |= USART_CR3_DMAR;
    
    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the USART CR3 register */
    husart->Instance->CR3 |= USART_CR3_DMAT;
    
    /* Process Unlocked */
    __HAL_UNLOCK(husart);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}
    
/**
  * @brief Pauses the DMA Transfer.
  * @param husart: USART handle
  * @retval None
  */
HAL_StatusTypeDef HAL_USART_DMAPause(USART_HandleTypeDef *husart)
{
  /* Process Locked */
  __HAL_LOCK(husart);

  if(husart->State == HAL_USART_STATE_BUSY_TX)
  {
    /* Disable the USART DMA Tx request */
    husart->Instance->CR3 &= (uint32_t)(~USART_CR3_DMAT);
  }
  else if(husart->State == HAL_USART_STATE_BUSY_RX)
  {
    /* Disable the USART DMA Rx request */
    husart->Instance->CR3 &= (uint32_t)(~USART_CR3_DMAR);
  }
  else if(husart->State == HAL_USART_STATE_BUSY_TX_RX)
  {
    /* Disable the USART DMA Tx request */
    husart->Instance->CR3 &= (uint32_t)(~USART_CR3_DMAT);
    /* Disable the USART DMA Rx request */
    husart->Instance->CR3 &= (uint32_t)(~USART_CR3_DMAR);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK; 
}

/**
  * @brief Resumes the DMA Transfer.
  * @param husart: USART handle
  * @retval None
  */
HAL_StatusTypeDef HAL_USART_DMAResume(USART_HandleTypeDef *husart)
{
  /* Process Locked */
  __HAL_LOCK(husart);

  if(husart->State == HAL_USART_STATE_BUSY_TX)
  {
    /* Enable the USART DMA Tx request */
    husart->Instance->CR3 |= USART_CR3_DMAT;
  }
  else if(husart->State == HAL_USART_STATE_BUSY_RX)
  {
    /* Enable the USART DMA Rx request */
    husart->Instance->CR3 |= USART_CR3_DMAR;
  }
  else if(husart->State == HAL_USART_STATE_BUSY_TX_RX)
  {
    /* Enable the USART DMA Rx request  before the DMA Tx request */
    husart->Instance->CR3 |= USART_CR3_DMAR;
    /* Enable the USART DMA Tx request */
    husart->Instance->CR3 |= USART_CR3_DMAT;
  }

  /* If the USART peripheral is still not enabled, enable it */
  if ((husart->Instance->CR1 & USART_CR1_UE) == 0)
  {
    /* Enable USART peripheral */
    __HAL_USART_ENABLE(husart);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}

/**
  * @brief Stops the DMA Transfer.
  * @param husart: USART handle
  * @retval None
  */
HAL_StatusTypeDef HAL_USART_DMAStop(USART_HandleTypeDef *husart)
{
  /* Process Locked */
  __HAL_LOCK(husart);

  /* Disable the USART Tx/Rx DMA requests */
  husart->Instance->CR3 &= ~USART_CR3_DMAT;
  husart->Instance->CR3 &= ~USART_CR3_DMAR;

  /* Abort the USART DMA tx channel */
  if(husart->hdmatx != HAL_NULL)
  {
    HAL_DMA_Abort(husart->hdmatx);
  }
  /* Abort the USART DMA rx channel */
  if(husart->hdmarx != HAL_NULL)
  {
    HAL_DMA_Abort(husart->hdmarx);
  }

  /* Disable USART peripheral */
  __HAL_USART_DISABLE(husart);

  husart->State = HAL_USART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(husart);

  return HAL_OK;
}    
    
/**
  * @brief This function handles USART interrupt request.
  * @param husart: USART handle
  * @retval None
  */
void HAL_USART_IRQHandler(USART_HandleTypeDef *husart)
{
  
  /* USART parity error interrupt occured ------------------------------------*/
  if((__HAL_USART_GET_IT(husart, USART_IT_PE) != RESET) && (__HAL_USART_GET_IT_SOURCE(husart, USART_IT_PE) != RESET))
  { 
    __HAL_USART_CLEAR_IT(husart, USART_IT_PE);
    husart->ErrorCode |= HAL_USART_ERROR_PE;
    /* Set the USART state ready to be able to start again the process */
    husart->State = HAL_USART_STATE_READY;
  }
  
  /* USART frame error interrupt occured -------------------------------------*/
  if((__HAL_USART_GET_IT(husart, USART_IT_FE) != RESET) && (__HAL_USART_GET_IT_SOURCE(husart, USART_IT_ERR) != RESET))
  { 
    __HAL_USART_CLEAR_IT(husart, USART_IT_FE);
    husart->ErrorCode |= HAL_USART_ERROR_FE;
    /* Set the USART state ready to be able to start again the process */
    husart->State = HAL_USART_STATE_READY;
  }
  
  /* USART noise error interrupt occured -------------------------------------*/
  if((__HAL_USART_GET_IT(husart, USART_IT_NE) != RESET) && (__HAL_USART_GET_IT_SOURCE(husart, USART_IT_ERR) != RESET))
  { 
    __HAL_USART_CLEAR_IT(husart, USART_IT_NE);
    husart->ErrorCode |= HAL_USART_ERROR_NE;
    /* Set the USART state ready to be able to start again the process */
    husart->State = HAL_USART_STATE_READY;
  }
  
  /* USART Over-Run interrupt occured ----------------------------------------*/
  if((__HAL_USART_GET_IT(husart, USART_IT_ORE) != RESET) && (__HAL_USART_GET_IT_SOURCE(husart, USART_IT_ERR) != RESET))
  { 
    __HAL_USART_CLEAR_IT(husart, USART_IT_ORE);
    husart->ErrorCode |= HAL_USART_ERROR_ORE;
    /* Set the USART state ready to be able to start again the process */
    husart->State = HAL_USART_STATE_READY;
  }
 
   /* Call USART Error Call back function if need be --------------------------*/
  if(husart->ErrorCode != HAL_USART_ERROR_NONE)
  {
    HAL_USART_ErrorCallback(husart);
  }  
 
  /* USART in mode Receiver --------------------------------------------------*/
  if((__HAL_USART_GET_IT(husart, USART_IT_RXNE) != RESET) && (__HAL_USART_GET_IT_SOURCE(husart, USART_IT_RXNE) != RESET))
  {
    if(husart->State == HAL_USART_STATE_BUSY_RX)
    {
      USART_Receive_IT(husart);
    }
    else
    {
      USART_TransmitReceive_IT(husart);
    }
  }
  
  /* USART in mode Transmitter -----------------------------------------------*/
  if((__HAL_USART_GET_IT(husart, USART_IT_TXE) != RESET) &&(__HAL_USART_GET_IT_SOURCE(husart, USART_IT_TXE) != RESET))
  {    
    if(husart->State == HAL_USART_STATE_BUSY_TX)
    {
      USART_Transmit_IT(husart);
    }
    else
    {
      USART_TransmitReceive_IT(husart);
    }
  }
  
  /* USART in mode Transmitter (transmission end) -----------------------------*/
  if((__HAL_USART_GET_IT(husart, USART_IT_TC) != RESET) &&(__HAL_USART_GET_IT_SOURCE(husart, USART_IT_TC) != RESET))
  {
    USART_EndTransmit_IT(husart);
  } 

}


/**
  * @brief Tx Transfer completed callbacks
  * @param husart: usart handle
  * @retval None
  */
__weak void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_TxCpltCallback can be implemented in the user file
   */ 
}

/**
  * @brief  Tx Half Transfer completed callbacks.
  * @param  husart: USART handle
  * @retval None
  */
 __weak void HAL_USART_TxHalfCpltCallback(USART_HandleTypeDef *husart)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_USART_TxHalfCpltCallback can be implemented in the user file
   */
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  husart: USART handle
  * @retval None
  */
__weak void HAL_USART_RxCpltCallback(USART_HandleTypeDef *husart)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_USART_RxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief Rx Half Transfer completed callbacks
  * @param husart: usart handle
  * @retval None
  */
__weak void HAL_USART_RxHalfCpltCallback(USART_HandleTypeDef *husart)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_RxHalfCpltCallback can be implemented in the user file
   */
}

/**
  * @brief Tx/Rx Transfers completed callback for the non-blocking process
  * @param husart: usart handle
  * @retval None
  */
__weak void HAL_USART_TxRxCpltCallback(USART_HandleTypeDef *husart)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_TxRxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief USART error callbacks
  * @param husart: usart handle
  * @retval None
  */
__weak void HAL_USART_ErrorCallback(USART_HandleTypeDef *husart)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_USART_ErrorCallback can be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup USART_Exported_Functions_Group3 Peripheral Control functions 
  *  @brief   USART control functions 
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the USART.
     (+) HAL_USART_GetState() API can be helpful to check in run-time the state of the USART peripheral. 
     (+) USART_CheckIdleState() APi ensures that TEACK and/or REACK bits are set after initialization
      
@endverbatim
  * @{
  */



/**
  * @brief return the USART state
  * @param husart: USART handle
  * @retval HAL state
  */
HAL_USART_StateTypeDef HAL_USART_GetState(USART_HandleTypeDef *husart)
{
  return husart->State;
}

/**
  * @brief  Return the USART error code
  * @param  husart : pointer to a USART_HandleTypeDef structure that contains
  *              the configuration information for the specified USART.
  * @retval USART Error Code
  */
uint32_t HAL_USART_GetError(USART_HandleTypeDef *husart)
{
  return husart->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */
  
/** @defgroup USART_Private_Functions USART Private Functions
 * @{
 */

/**
  * @brief DMA USART transmit process complete callback 
  * @param hdma : DMA handle
  * @retval None
  */
static void USART_DMATransmitCplt(DMA_HandleTypeDef *hdma)   
{
  USART_HandleTypeDef* husart = ( USART_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  husart->TxXferCount = 0;
  
  if(husart->State == HAL_USART_STATE_BUSY_TX)
  {
    /* Wait for USART TC Flag */
    if(USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TC, RESET, USART_TXDMA_TIMEOUTVALUE) != HAL_OK)
    {
      /* Timeout Occured */ 
      HAL_USART_ErrorCallback(husart);
    }
    else
    {
      /* No Timeout */
      /* Disable the DMA transfer for transmit request by setting the DMAT bit
       in the USART CR3 register */
      husart->Instance->CR3 &= ~(USART_CR3_DMAT);
      husart->State= HAL_USART_STATE_READY;
    }
  }
  /* the usart state is HAL_USART_STATE_BUSY_TX_RX*/
  else
  {
    husart->State= HAL_USART_STATE_BUSY_RX;
    HAL_USART_TxCpltCallback(husart);
  }
}


/**
  * @brief DMA USART transmit process half complete callback 
  * @param hdma : DMA handle
  * @retval None
  */
static void USART_DMATxHalfCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  HAL_USART_TxHalfCpltCallback(husart);
}

/**
  * @brief DMA USART receive process complete callback 
  * @param hdma : DMA handle
  * @retval None
  */
static void USART_DMAReceiveCplt(DMA_HandleTypeDef *hdma)   
{
  USART_HandleTypeDef* husart = ( USART_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  husart->RxXferCount = 0;
  
  /* Disable the DMA RX transfer for the receiver request by resetting the DMAR bit 
     in USART CR3 register */
  husart->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DMAR);
  /* similarly, disable the DMA TX transfer that was started to provide the 
     clock to the slave device */
  husart->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DMAT);

  husart->State= HAL_USART_STATE_READY;
  
  HAL_USART_RxCpltCallback(husart);
}

/**
  * @brief DMA USART receive process half complete callback 
  * @param hdma : DMA handle
  * @retval None
  */
static void USART_DMARxHalfCplt(DMA_HandleTypeDef *hdma)
{
  USART_HandleTypeDef* husart = (USART_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;

  HAL_USART_RxHalfCpltCallback(husart); 
}

/**
  * @brief DMA USART communication error callback 
  * @param hdma : DMA handle
  * @retval None
  */
static void USART_DMAError(DMA_HandleTypeDef *hdma)   
{
  USART_HandleTypeDef* husart = ( USART_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  husart->RxXferCount = 0;
  husart->TxXferCount = 0;
  husart->ErrorCode |= HAL_USART_ERROR_DMA;
  husart->State= HAL_USART_STATE_READY;
  
  HAL_USART_ErrorCallback(husart);
}

/**
  * @brief  This function handles USART Communication Timeout.
  * @param  husart: USART handle
  * @param  Flag: specifies the USART flag to check.
  * @param  Status: The new Flag status (SET or RESET).
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_WaitOnFlagUntilTimeout(USART_HandleTypeDef *husart, uint32_t Flag, FlagStatus Status, uint32_t Timeout)  
{
  uint32_t tickstart = HAL_GetTick();
  
  /* Wait until flag is set */
  if(Status == RESET)
  {    
    while(__HAL_USART_GET_FLAG(husart, Flag) == RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
          __HAL_USART_DISABLE_IT(husart, USART_IT_TXE);
          __HAL_USART_DISABLE_IT(husart, USART_IT_RXNE);
          __HAL_USART_DISABLE_IT(husart, USART_IT_PE);
          __HAL_USART_DISABLE_IT(husart, USART_IT_ERR);
          
          husart->State= HAL_USART_STATE_TIMEOUT;
          
          /* Process Unlocked */
          __HAL_UNLOCK(husart);
          
          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {
    while(__HAL_USART_GET_FLAG(husart, Flag) != RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
          __HAL_USART_DISABLE_IT(husart, USART_IT_TXE);
          __HAL_USART_DISABLE_IT(husart, USART_IT_RXNE);
          __HAL_USART_DISABLE_IT(husart, USART_IT_PE);
          __HAL_USART_DISABLE_IT(husart, USART_IT_ERR);
    
          husart->State= HAL_USART_STATE_TIMEOUT;
          
          /* Process Unlocked */
          __HAL_UNLOCK(husart);
        
          return HAL_TIMEOUT;
        }
      }
    }
  }
  return HAL_OK;      
}

/**
  * @brief Configure the USART peripheral 
  * @param husart: USART handle
  * @retval None
  */
static HAL_StatusTypeDef USART_SetConfig(USART_HandleTypeDef *husart)
{
  uint32_t tmpreg                      = 0x0;
  USART_ClockSourceTypeDef clocksource = USART_CLOCKSOURCE_UNDEFINED;
  HAL_StatusTypeDef ret                = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_USART_POLARITY(husart->Init.CLKPolarity));
  assert_param(IS_USART_PHASE(husart->Init.CLKPhase));
  assert_param(IS_USART_LASTBIT(husart->Init.CLKLastBit));
  assert_param(IS_USART_BAUDRATE(husart->Init.BaudRate));  
  assert_param(IS_USART_WORD_LENGTH(husart->Init.WordLength));
  assert_param(IS_USART_STOPBITS(husart->Init.StopBits));
  assert_param(IS_USART_PARITY(husart->Init.Parity));
  assert_param(IS_USART_MODE(husart->Init.Mode));
 

  /*-------------------------- USART CR1 Configuration -----------------------*/
   /* Clear M, PCE, PS, TE and RE bits and configure       
   *  the USART Word Length, Parity and Mode: 
   *  set the M bits according to husart->Init.WordLength value 
   *  set PCE and PS bits according to husart->Init.Parity value
   *  set TE and RE bits according to husart->Init.Mode value */
  tmpreg = (uint32_t)husart->Init.WordLength | husart->Init.Parity | husart->Init.Mode;
  MODIFY_REG(husart->Instance->CR1, USART_CR1_FIELDS, tmpreg);
  
  /*---------------------------- USART CR2 Configuration ---------------------*/
  /* Clear and configure the USART Clock, CPOL, CPHA, LBCL and STOP bits:
   * set CPOL bit according to husart->Init.CLKPolarity value
   * set CPHA bit according to husart->Init.CLKPhase value
   * set LBCL bit according to husart->Init.CLKLastBit value
   * set STOP[13:12] bits according to husart->Init.StopBits value */
  tmpreg = (uint32_t)(USART_CLOCK_ENABLED); 
  tmpreg |= ((uint32_t)husart->Init.CLKPolarity | (uint32_t)husart->Init.CLKPhase);
  tmpreg |= ((uint32_t)husart->Init.CLKLastBit | (uint32_t)husart->Init.StopBits);
  MODIFY_REG(husart->Instance->CR2, USART_CR2_FIELDS, tmpreg);

  /*-------------------------- USART CR3 Configuration -----------------------*/  
  /* no CR3 register configuration                                            */

  /*-------------------------- USART BRR Configuration -----------------------*/
  __HAL_USART_GETCLOCKSOURCE(husart, clocksource);
  switch (clocksource)
  {
    case USART_CLOCKSOURCE_PCLK1: 
      husart->Instance->BRR = (uint16_t)(HAL_RCC_GetPCLK1Freq() / husart->Init.BaudRate);
      break;
    case USART_CLOCKSOURCE_PCLK2: 
      husart->Instance->BRR = (uint16_t)(HAL_RCC_GetPCLK2Freq() / husart->Init.BaudRate);
      break;
    case USART_CLOCKSOURCE_HSI: 
      husart->Instance->BRR = (uint16_t)(HSI_VALUE / husart->Init.BaudRate); 
      break; 
    case USART_CLOCKSOURCE_SYSCLK:  
      husart->Instance->BRR = (uint16_t)(HAL_RCC_GetSysClockFreq() / husart->Init.BaudRate);
      break;  
    case USART_CLOCKSOURCE_LSE:                
      husart->Instance->BRR = (uint16_t)(LSE_VALUE / husart->Init.BaudRate); 
      break;      
    case USART_CLOCKSOURCE_UNDEFINED:                
    default:                
      ret = HAL_ERROR; 
      break;          
  } 
  
  return ret; 
}



/**
  * @brief Check the USART Idle State
  * @param husart: USART handle
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_CheckIdleState(USART_HandleTypeDef *husart)
{
  /* Initialize the USART ErrorCode */
  husart->ErrorCode = HAL_USART_ERROR_NONE;
  
  /* Check if the Transmitter is enabled */
  if((husart->Instance->CR1 & USART_CR1_TE) == USART_CR1_TE)
  {
    /* Wait until TEACK flag is set */
    if(USART_WaitOnFlagUntilTimeout(husart, USART_ISR_TEACK, RESET, TEACK_REACK_TIMEOUT) != HAL_OK)  
    { 
      /* Timeout Occured */ 
      return HAL_TIMEOUT;
    } 
  }
  /* Check if the Receiver is enabled */
  if((husart->Instance->CR1 & USART_CR1_RE) == USART_CR1_RE)
  {
    /* Wait until REACK flag is set */
    if(USART_WaitOnFlagUntilTimeout(husart, USART_ISR_REACK, RESET, TEACK_REACK_TIMEOUT) != HAL_OK)  
    { 
      /* Timeout Occured */ 
      return HAL_TIMEOUT;
    }
  }
  
  /* Initialize the USART state*/
  husart->State= HAL_USART_STATE_READY;
    
  /* Process Unlocked */
  __HAL_UNLOCK(husart);
  
  return HAL_OK;  
}

/**
  * @brief  Simplex Send an amount of data in non-blocking mode.
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Transmit_IT()      
  * @param  husart: USART handle
  * @retval HAL status
  * @note   The USART errors are not managed to avoid the overrun error.
  */
static HAL_StatusTypeDef USART_Transmit_IT(USART_HandleTypeDef *husart)
{
  uint16_t* tmp;

  if (husart->State == HAL_USART_STATE_BUSY_TX)
  {
    
     if(husart->TxXferCount == 0)
    {
      /* Disable the USART Transmit Complete Interrupt */
      __HAL_USART_DISABLE_IT(husart, USART_IT_TXE);
        
      /* Enable the USART Transmit Complete Interrupt */    
      __HAL_USART_ENABLE_IT(husart, USART_IT_TC);
      
      return HAL_OK;
    }
    else
    {
      if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
      {
        tmp = (uint16_t*) husart->pTxBuffPtr;
        husart->Instance->TDR = (*tmp & (uint16_t)0x01FF);   
        husart->pTxBuffPtr += 2;
      } 
      else
      {
        husart->Instance->TDR = (uint8_t)(*husart->pTxBuffPtr++ & (uint8_t)0xFF);       
      }

      husart->TxXferCount--;
    
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
  * @param  husart: pointer to a USART_HandleTypeDef structure that contains
  *                the configuration information for the specified USART module.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_EndTransmit_IT(USART_HandleTypeDef *husart)
{
  /* Disable the USART Transmit Complete Interrupt */    
  __HAL_USART_DISABLE_IT(husart, USART_IT_TC);
  
  /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
  __HAL_USART_DISABLE_IT(husart, USART_IT_ERR);
    
  husart->State = HAL_USART_STATE_READY;
   
  HAL_USART_TxCpltCallback(husart);
  
  return HAL_OK;
}


/**
  * @brief  Simplex Receive an amount of data in non-blocking mode.
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_Receive_IT()    
  * @param  husart: USART handle
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_Receive_IT(USART_HandleTypeDef *husart)
{
  uint16_t* tmp;
  uint16_t uhMask = husart->Mask;  

  if(husart->State == HAL_USART_STATE_BUSY_RX)
  {
    
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      tmp = (uint16_t*) husart->pRxBuffPtr;
      *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
      husart->pRxBuffPtr += 2;
    } 
    else
    {
      *husart->pRxBuffPtr++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);       
    }
      /* Send dummy byte in order to generate the clock for the Slave to Send the next data */
      husart->Instance->TDR = (DUMMY_DATA & (uint16_t)0x00FF);       
    
    if(--husart->RxXferCount == 0)
    { 
      __HAL_USART_DISABLE_IT(husart, USART_IT_RXNE);      

      /* Disable the USART Parity Error Interrupt */
      __HAL_USART_DISABLE_IT(husart, USART_IT_PE);
        
      /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
      __HAL_USART_DISABLE_IT(husart, USART_IT_ERR);
        
      husart->State = HAL_USART_STATE_READY;
      
      HAL_USART_RxCpltCallback(husart);
      
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
  * @brief  Full-Duplex Send receive an amount of data in full-duplex mode (non-blocking).
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_USART_TransmitReceive_IT()     
  * @param  husart: USART handle
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_TransmitReceive_IT(USART_HandleTypeDef *husart)
{
  uint16_t* tmp;
  uint16_t uhMask = husart->Mask;   

  if(husart->State == HAL_USART_STATE_BUSY_TX_RX)
  {

    if(husart->TxXferCount != 0x00)
    {
      if(__HAL_USART_GET_FLAG(husart, USART_FLAG_TXE) != RESET)
      {
        if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
        {
          tmp = (uint16_t*) husart->pTxBuffPtr;
          husart->Instance->TDR = (uint16_t)(*tmp & uhMask);
          husart->pTxBuffPtr += 2;
        } 
        else
        {
          husart->Instance->TDR = (uint8_t)(*husart->pTxBuffPtr++ & (uint8_t)uhMask);       
        }
        husart->TxXferCount--;
        
        /* Check the latest data transmitted */
        if(husart->TxXferCount == 0)
        {
           __HAL_USART_DISABLE_IT(husart, USART_IT_TXE);
        }
      }
    }
    
    if(husart->RxXferCount != 0x00)
    {
      if(__HAL_USART_GET_FLAG(husart, USART_FLAG_RXNE) != RESET)
      {
        if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
        {
          tmp = (uint16_t*) husart->pRxBuffPtr;
          *tmp = (uint16_t)(husart->Instance->RDR & uhMask);
          husart->pRxBuffPtr += 2;          
        } 
        else
        {
          *husart->pRxBuffPtr++ = (uint8_t)(husart->Instance->RDR & (uint8_t)uhMask);         
        }
        husart->RxXferCount--;
      }
    }
    
    /* Check the latest data received */
    if(husart->RxXferCount == 0)
    {
      __HAL_USART_DISABLE_IT(husart, USART_IT_RXNE);
      
      /* Disable the USART Parity Error Interrupt */
      __HAL_USART_DISABLE_IT(husart, USART_IT_PE);
      
      /* Disable the USART Error Interrupt: (Frame error, noise error, overrun error) */
      __HAL_USART_DISABLE_IT(husart, USART_IT_ERR);
      
      husart->State = HAL_USART_STATE_READY;
      
      HAL_USART_TxRxCpltCallback(husart);
      
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

#endif /* HAL_USART_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
