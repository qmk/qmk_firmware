/**
  ******************************************************************************
  * @file    stm32f3xx_hal_cec.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   CEC HAL module driver.
  * 
  *          This file provides firmware functions to manage the following 
  *          functionalities of the High Definition Multimedia Interface 
  *          Consumer Electronics Control Peripheral (CEC).
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
    The CEC HAL driver can be used as follows:
    
    (#) Declare a CEC_HandleTypeDef handle structure.
    (#) Initialize the CEC low level resources by implementing the HAL_CEC_MspInit ()API:
        (##) Enable the CEC interface clock.
        (##) CEC pins configuration:
            (+) Enable the clock for the CEC GPIOs.
            (+) Configure these CEC pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (HAL_CEC_Transmit_IT()
             and HAL_CEC_Receive_IT() APIs):
            (+) Configure the CEC interrupt priority.
            (+) Enable the NVIC CEC IRQ handle.
            (@) The specific CEC interrupts (Transmission complete interrupt, 
                RXNE interrupt and Error Interrupts) will be managed using the macros
                __HAL_CEC_ENABLE_IT() and __HAL_CEC_DISABLE_IT() inside the transmit 
                and receive process.

    (#) Program the Signal Free Time (SFT) and SFT option, Tolerance, reception stop in
        in case of Bit Rising Error, Error-Bit generation conditions, device logical
        address and Listen mode in the hcec Init structure.

    (#) Initialize the CEC registers by calling the HAL_CEC_Init() API.
        
    (@) This API (HAL_CEC_Init()) configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
        by calling the customed HAL_CEC_MspInit() API.

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

#ifdef HAL_CEC_MODULE_ENABLED

#if defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup CEC CEC HAL module driver
  * @brief HAL CEC module driver
  * @{
  */
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup CEC_Private CEC Private Constants
  * @{
  */
#define CEC_CFGR_FIELDS     (CEC_CFGR_SFT | CEC_CFGR_RXTOL | CEC_CFGR_BRESTP \
                           | CEC_CFGR_BREGEN | CEC_CFGR_LBPEGEN | CEC_CFGR_SFTOPT \
                           | CEC_CFGR_BRDNOGEN | CEC_CFGR_OAR | CEC_CFGR_LSTN)
/**
 * @}
 */ 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static HAL_StatusTypeDef CEC_Transmit_IT(CEC_HandleTypeDef *hcec);
static HAL_StatusTypeDef CEC_Receive_IT(CEC_HandleTypeDef *hcec);
/* Exported functions ---------------------------------------------------------*/

/** @defgroup CEC_Exported_Functions CEC Exported Functions
  * @{
  */

/** @defgroup CEC_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions 
  *
@verbatim                                               
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to initialize the CEC
      (+) The following parameters need to be configured: 
        (++) SignalFreeTime
        (++) Tolerance 
        (++) BRERxStop                 (RX stopped or not upon Bit Rising Error)
        (++) BREErrorBitGen            (Error-Bit generation in case of Bit Rising Error)
        (++) LBPEErrorBitGen           (Error-Bit generation in case of Long Bit Period Error)
        (++) BroadcastMsgNoErrorBitGen (Error-bit generation in case of broadcast message error)
        (++) SignalFreeTimeOption      (SFT Timer start definition)
        (++) OwnAddress                (CEC device address)
        (++) ListenMode

@endverbatim
  * @{
  */

/**
  * @brief Initializes the CEC mode according to the specified
  *         parameters in the CEC_InitTypeDef and creates the associated handle .
  * @param hcec: CEC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_Init(CEC_HandleTypeDef *hcec)
{
  uint32_t tmpreg = 0x0;
  
  /* Check the CEC handle allocation */
  if(hcec == HAL_NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */ 
  assert_param(IS_CEC_ALL_INSTANCE(hcec->Instance));
  assert_param(IS_CEC_SIGNALFREETIME(hcec->Init.SignalFreeTime));
  assert_param(IS_CEC_TOLERANCE(hcec->Init.Tolerance));  
  assert_param(IS_CEC_BRERXSTOP(hcec->Init.BRERxStop));
  assert_param(IS_CEC_BREERRORBITGEN(hcec->Init.BREErrorBitGen));
  assert_param(IS_CEC_LBPEERRORBITGEN(hcec->Init.LBPEErrorBitGen));
  assert_param(IS_CEC_BROADCASTERROR_NO_ERRORBIT_GENERATION(hcec->Init.BroadcastMsgNoErrorBitGen));
  assert_param(IS_CEC_SFTOP(hcec->Init.SignalFreeTimeOption)); 
  assert_param(IS_CEC_OAR_ADDRESS(hcec->Init.OwnAddress)); 
  assert_param(IS_CEC_LISTENING_MODE(hcec->Init.ListenMode));
  assert_param(IS_CEC_ADDRESS(hcec->Init.InitiatorAddress));  

  
  if(hcec->State == HAL_CEC_STATE_RESET)
  {   
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_CEC_MspInit(hcec);
  }
  
  hcec->State = HAL_CEC_STATE_BUSY;
  
  /* Disable the Peripheral */
  __HAL_CEC_DISABLE(hcec);
  
  tmpreg = hcec->Init.SignalFreeTime;
  tmpreg |= hcec->Init.Tolerance;
  tmpreg |= hcec->Init.BRERxStop;
  tmpreg |= hcec->Init.BREErrorBitGen;
  tmpreg |= hcec->Init.LBPEErrorBitGen;
  tmpreg |= hcec->Init.BroadcastMsgNoErrorBitGen;
  tmpreg |= hcec->Init.SignalFreeTimeOption;
  tmpreg |= (hcec->Init.OwnAddress << CEC_CFGR_OAR_LSB_POS);
  tmpreg |= hcec->Init.ListenMode;
  
  /* Write to CEC Control Register */
  MODIFY_REG(hcec->Instance->CFGR, CEC_CFGR_FIELDS, tmpreg);

  /* Enable the Peripheral */
  __HAL_CEC_ENABLE(hcec);
  
  hcec->State = HAL_CEC_STATE_READY;
  
  return HAL_OK;
}



/**
  * @brief DeInitializes the CEC peripheral 
  * @param hcec: CEC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_DeInit(CEC_HandleTypeDef *hcec)
{
  /* Check the CEC handle allocation */
  if(hcec == HAL_NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_CEC_ALL_INSTANCE(hcec->Instance));

  hcec->State = HAL_CEC_STATE_BUSY;
  
  /* DeInit the low level hardware */
  HAL_CEC_MspDeInit(hcec);
  /* Disable the Peripheral */
  __HAL_CEC_DISABLE(hcec);
  
  hcec->ErrorCode = HAL_CEC_ERROR_NONE;
  hcec->State = HAL_CEC_STATE_RESET;
  
  /* Process Unlock */
  __HAL_UNLOCK(hcec);
  
  return HAL_OK;
}

/**
  * @brief CEC MSP Init
  * @param hcec: CEC handle
  * @retval None
  */
 __weak void HAL_CEC_MspInit(CEC_HandleTypeDef *hcec)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_MspInit can be implemented in the user file
   */ 
}

/**
  * @brief CEC MSP DeInit
  * @param hcec: CEC handle
  * @retval None
  */
 __weak void HAL_CEC_MspDeInit(CEC_HandleTypeDef *hcec)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_MspDeInit can be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup CEC_Exported_Functions_Group2 Input and Output operation functions 
  *  @brief CEC Transmit/Receive functions 
  *
@verbatim   
 ===============================================================================
                      ##### I/O operation functions ##### 
 ===============================================================================  
    This subsection provides a set of functions allowing to manage the CEC data transfers.
    
    (#) The CEC handle must contain the initiator (TX side) and the destination (RX side)
        logical addresses (4-bit long addresses, 0xF for broadcast messages destination)
    
    (#) There are two mode of transfer:
       (+) Blocking mode: The communication is performed in polling mode. 
            The HAL status of all data processing is returned by the same function 
            after finishing transfer.  
       (+) No-Blocking mode: The communication is performed using Interrupts. 
           These API's return the HAL status.
           The end of the data processing will be indicated through the 
           dedicated CEC IRQ when using Interrupt mode.
           The HAL_CEC_TxCpltCallback(), HAL_CEC_RxCpltCallback() user callbacks 
           will be executed respectivelly at the end of the transmit or Receive process
           The HAL_CEC_ErrorCallback()user callback will be executed when a communication 
           error is detected

    (#) Blocking mode API's are :
        (+) HAL_CEC_Transmit()
        (+) HAL_CEC_Receive() 
        
    (#) Non-Blocking mode API's with Interrupt are :
        (+) HAL_CEC_Transmit_IT()
        (+) HAL_CEC_Receive_IT()
        (+) HAL_CEC_IRQHandler()

    (#) A set of Transfer Complete Callbacks are provided in No_Blocking mode:
        (+) HAL_CEC_TxCpltCallback()
        (+) HAL_CEC_RxCpltCallback()
        (+) HAL_CEC_ErrorCallback()
      
@endverbatim
  * @{
  */

/**
  * @brief Send data in blocking mode 
  * @param hcec: CEC handle
  * @param DestinationAddress: destination logical address      
  * @param pData: pointer to input byte data buffer
  * @param Size: amount of data to be sent in bytes (without counting the header).
  *              0 means only the header is sent (ping operation).
  *              Maximum TX size is 15 bytes (1 opcode and up to 14 operands).    
  * @param  Timeout: Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_Transmit(CEC_HandleTypeDef *hcec, uint8_t DestinationAddress, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
  uint8_t  temp = 0;  
  uint32_t tempisr = 0;   
  uint32_t tickstart = 0;

  if((hcec->State == HAL_CEC_STATE_READY) && (__HAL_CEC_GET_TRANSMISSION_START_FLAG(hcec) == RESET)) 
  {
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;
    if((pData == HAL_NULL) && (Size > 0)) 
    {
      hcec->State = HAL_CEC_STATE_ERROR;
      return  HAL_ERROR;                                    
    }

    assert_param(IS_CEC_ADDRESS(DestinationAddress)); 
    assert_param(IS_CEC_MSGSIZE(Size));
    
    /* Process Locked */
    __HAL_LOCK(hcec);
    
    hcec->State = HAL_CEC_STATE_BUSY_TX;

    hcec->TxXferCount = Size;
    
    /* case no data to be sent, sender is only pinging the system */
    if (Size == 0)
    {
      /* Set TX End of Message (TXEOM) bit, must be set before writing data to TXDR */
      __HAL_CEC_LAST_BYTE_TX_SET(hcec);
    }
    
    /* send header block */
    temp = (uint8_t)((uint32_t)(hcec->Init.InitiatorAddress) << CEC_INITIATOR_LSB_POS) | DestinationAddress;
    hcec->Instance->TXDR = temp;
    /* Set TX Start of Message  (TXSOM) bit */
    __HAL_CEC_FIRST_BYTE_TX_SET(hcec);
    
    while (hcec->TxXferCount > 0)
    {
      hcec->TxXferCount--;

      tickstart = HAL_GetTick();
      while(HAL_IS_BIT_CLR(hcec->Instance->ISR, CEC_ISR_TXBR))
      {
        if(Timeout != HAL_MAX_DELAY)
        {
          if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
          {
            hcec->State = HAL_CEC_STATE_TIMEOUT; 
            /* Process Unlocked */
            __HAL_UNLOCK(hcec);  
            return HAL_TIMEOUT;
          }
        }        

        /* check whether error occured while waiting for TXBR to be set:
         * has Tx underrun occurred ?
         * has Tx error occurred ?
         * has Tx Missing Acknowledge error occurred ? 
         * has Arbitration Loss error occurred ? */
        tempisr = hcec->Instance->ISR;
        if ((tempisr & (CEC_ISR_TXUDR|CEC_ISR_TXERR|CEC_ISR_TXACKE|CEC_ISR_ARBLST)) != 0)
        {
          /* copy ISR for error handling purposes */
          hcec->ErrorCode = tempisr;
         /* clear all error flags by default */
         __HAL_CEC_CLEAR_FLAG(hcec, (CEC_ISR_TXUDR|CEC_ISR_TXERR|CEC_ISR_TXACKE|CEC_ISR_ARBLST));
         hcec->State = HAL_CEC_STATE_ERROR;
         __HAL_UNLOCK(hcec);
         return  HAL_ERROR;                                    
        }
      } 
      /* TXBR to clear BEFORE writing TXDR register */
      __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_TXBR);
      if (hcec->TxXferCount == 0)
      {
        /* if last byte transmission, set TX End of Message (TXEOM) bit */
        __HAL_CEC_LAST_BYTE_TX_SET(hcec);
      }
      hcec->Instance->TXDR = *pData++;
      
      /* error check after TX byte write up */
      tempisr = hcec->Instance->ISR;
      if ((tempisr & (CEC_ISR_TXUDR|CEC_ISR_TXERR|CEC_ISR_TXACKE|CEC_ISR_ARBLST)) != 0)
      {
        /* copy ISR for error handling purposes */
        hcec->ErrorCode = tempisr;
        /* clear all error flags by default */
        __HAL_CEC_CLEAR_FLAG(hcec, (CEC_ISR_TXUDR|CEC_ISR_TXERR|CEC_ISR_TXACKE|CEC_ISR_ARBLST));
        hcec->State = HAL_CEC_STATE_ERROR;
        __HAL_UNLOCK(hcec);
        return  HAL_ERROR;                                    
      }
    } /* end while (while (hcec->TxXferCount > 0)) */
    
   
    /* if no error up to this point, check that transmission is  
     * complete, that is wait until TXEOM is reset */
    tickstart = HAL_GetTick();

    while (HAL_IS_BIT_SET(hcec->Instance->CR, CEC_CR_TXEOM))
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          hcec->State = HAL_CEC_STATE_ERROR;
          __HAL_UNLOCK(hcec);             
          return HAL_TIMEOUT;
        }
      } 
    }

    /* Final error check once all bytes have been transmitted */
    tempisr = hcec->Instance->ISR;
    if ((tempisr & (CEC_ISR_TXUDR|CEC_ISR_TXERR|CEC_ISR_TXACKE)) != 0)
    {
      /* copy ISR for error handling purposes */
      hcec->ErrorCode = tempisr;
      /* clear all error flags by default */
      __HAL_CEC_CLEAR_FLAG(hcec, (CEC_ISR_TXUDR|CEC_ISR_TXERR|CEC_ISR_TXACKE));
      hcec->State = HAL_CEC_STATE_ERROR;
      __HAL_UNLOCK(hcec);
      return  HAL_ERROR;                                    
    } 

    hcec->State = HAL_CEC_STATE_READY;
    __HAL_UNLOCK(hcec);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}

/**
  * @brief Receive data in blocking mode. Must be invoked when RXBR has been set. 
  * @param hcec: CEC handle
  * @param pData: pointer to received data buffer.
  * @param Timeout: Timeout duration.
  *       Note that the received data size is not known beforehand, the latter is known
  *       when the reception is complete and is stored in hcec->RxXferSize.  
  *       hcec->RxXferSize is the sum of opcodes + operands (0 to 14 operands max).
  *       If only a header is received, hcec->RxXferSize = 0    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_Receive(CEC_HandleTypeDef *hcec, uint8_t *pData, uint32_t Timeout)
{ 
  uint32_t temp;
  uint32_t tickstart = 0;   

  if (hcec->State == HAL_CEC_STATE_READY)
  { 
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;
    if (pData == HAL_NULL) 
    {
      hcec->State = HAL_CEC_STATE_ERROR;
      return  HAL_ERROR;                                    
    }
    
    hcec->RxXferSize = 0;
    /* Process Locked */
    __HAL_LOCK(hcec);
    
    
    /* Rx loop until CEC_ISR_RXEND  is set */
    while (HAL_IS_BIT_CLR(hcec->Instance->ISR, CEC_ISR_RXEND))
    {
      tickstart = HAL_GetTick();
      /* Wait for next byte to be received */
      while (HAL_IS_BIT_CLR(hcec->Instance->ISR, CEC_ISR_RXBR))
      {
      	if(Timeout != HAL_MAX_DELAY)
        {
          if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
          {
            hcec->State = HAL_CEC_STATE_TIMEOUT;
            __HAL_UNLOCK(hcec);    
            return HAL_TIMEOUT;
          }
        }
        /* any error so far ? 
         * has Rx Missing Acknowledge occurred ?
         * has Rx Long Bit Period error occurred ?
         * has Rx Short Bit Period error occurred ? 
         * has Rx Bit Rising error occurred ?             
         * has Rx Overrun error occurred ? */
        temp = (uint32_t) (hcec->Instance->ISR);
        if ((temp & (CEC_ISR_RXACKE|CEC_ISR_LBPE|CEC_ISR_SBPE|CEC_ISR_BRE|CEC_ISR_RXOVR)) != 0)
        {
          /* copy ISR for error handling purposes */
          hcec->ErrorCode = temp;
          /* clear all error flags by default */
          __HAL_CEC_CLEAR_FLAG(hcec, (CEC_ISR_RXACKE|CEC_ISR_LBPE|CEC_ISR_SBPE|CEC_ISR_BRE|CEC_ISR_RXOVR));
          hcec->State = HAL_CEC_STATE_ERROR;
          __HAL_UNLOCK(hcec);
          return  HAL_ERROR;                                    
        }
      } /* while (HAL_IS_BIT_CLR(hcec->Instance->ISR, CEC_ISR_RXBR)) */
  

      /* read received data */
      *pData++ = hcec->Instance->RXDR;
      temp = (uint32_t) (hcec->Instance->ISR);
      /* end of message ? */
      if ((temp &  CEC_ISR_RXEND) != 0)      
      {
         assert_param(IS_CEC_MSGSIZE(hcec->RxXferSize));
         __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_RXEND);
          hcec->State = HAL_CEC_STATE_READY;  
         __HAL_UNLOCK(hcec);  
         return HAL_OK; 
      }
      
      /* clear Rx-Byte Received flag */
      __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_RXBR); 
      /* increment payload byte counter */
       hcec->RxXferSize++;
    } /* while (HAL_IS_BIT_CLR(hcec->Instance->ISR, CEC_ISR_RXEND)) */ 
    
    /* if the instructions below are executed, it means RXEND was set when RXBR was 
     * set for the first time:
     * the code within the "while (HAL_IS_BIT_CLR(hcec->Instance->ISR, CEC_ISR_RXEND))"
     * loop has not been executed and this means a single byte has been sent */
    *pData++ = hcec->Instance->RXDR;
     /* only one header is received: RxXferSize is set to 0 (no operand, no opcode) */ 
     hcec->RxXferSize = 0;
     __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_RXEND);
                             
    hcec->State = HAL_CEC_STATE_READY;  
    __HAL_UNLOCK(hcec);  
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;   
  }
}


/**
  * @brief Send data in interrupt mode 
  * @param hcec: CEC handle 
  * @param DestinationAddress: destination logical address      
  * @param pData: pointer to input byte data buffer
  * @param Size: amount of data to be sent in bytes (without counting the header).
  *              0 means only the header is sent (ping operation).
  *              Maximum TX size is 15 bytes (1 opcode and up to 14 operands).    
  * @retval HAL status
  */  
HAL_StatusTypeDef HAL_CEC_Transmit_IT(CEC_HandleTypeDef *hcec, uint8_t DestinationAddress, uint8_t *pData, uint32_t Size)
{
  uint8_t  temp = 0; 
  /* if the IP isn't already busy and if there is no previous transmission
     already pending due to arbitration lost */
  if (((hcec->State == HAL_CEC_STATE_READY) || (hcec->State == HAL_CEC_STATE_STANDBY_RX)) 
  &&   (__HAL_CEC_GET_TRANSMISSION_START_FLAG(hcec) == RESET)) 
  {    
    if((pData == HAL_NULL) && (Size > 0)) 
    {
      hcec->State = HAL_CEC_STATE_ERROR;
      return  HAL_ERROR;                                    
    }

    assert_param(IS_CEC_ADDRESS(DestinationAddress)); 
    assert_param(IS_CEC_MSGSIZE(Size));
    
    /* Process Locked */
    __HAL_LOCK(hcec);
    hcec->pTxBuffPtr = pData;
    hcec->State = HAL_CEC_STATE_BUSY_TX;
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;
    
    /* Disable Peripheral to write CEC_IER register */
    __HAL_CEC_DISABLE(hcec);
    
    /* Enable the following two CEC Transmission interrupts as
     * well as the following CEC Transmission Errors interrupts: 
     * Tx Byte Request IT 
     * End of Transmission IT
     * Tx Missing Acknowledge IT
     * Tx-Error IT
     * Tx-Buffer Underrun IT 
     * Tx arbitration lost     */
    __HAL_CEC_ENABLE_IT(hcec, CEC_IER_TXBRIE|CEC_IER_TXENDIE|CEC_IER_TX_ALL_ERR);
                                     
    /* Enable the Peripheral */
    __HAL_CEC_ENABLE(hcec);
  
    /* initialize the number of bytes to send,
     * 0 means only one header is sent (ping operation) */
    hcec->TxXferCount = Size;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcec); 
    
    /* in case of no payload (Size = 0), sender is only pinging the system;
     * Set TX End of Message (TXEOM) bit, must be set before writing data to TXDR */
    if (Size == 0)
    {
      __HAL_CEC_LAST_BYTE_TX_SET(hcec);
    }
    
    /* send header block */
    temp = (uint8_t)((uint32_t)(hcec->Init.InitiatorAddress) << CEC_INITIATOR_LSB_POS) | DestinationAddress;
    hcec->Instance->TXDR = temp;
    /* Set TX Start of Message  (TXSOM) bit */
    __HAL_CEC_FIRST_BYTE_TX_SET(hcec);
    
    return HAL_OK;
  }
    /* if the IP is already busy or if there is a previous transmission
     already pending due to arbitration loss */
  else if ((hcec->State == HAL_CEC_STATE_BUSY_TX)
        || (__HAL_CEC_GET_TRANSMISSION_START_FLAG(hcec) != RESET))
  {
    __HAL_LOCK(hcec);
    /* set state to BUSY TX, in case it wasn't set already (case
     * of transmission new attempt after arbitration loss) */
    if (hcec->State != HAL_CEC_STATE_BUSY_TX)
    {
      hcec->State = HAL_CEC_STATE_BUSY_TX;
    }

    /* if all data have been sent */
    if(hcec->TxXferCount == 0)
    {
      /* Disable Peripheral to write CEC_IER register */
      __HAL_CEC_DISABLE(hcec);
      
      /* Disable the CEC Transmission Interrupts */
      __HAL_CEC_DISABLE_IT(hcec, CEC_IER_TXBRIE|CEC_IER_TXENDIE);
      /* Disable the CEC Transmission Error Interrupts */
      __HAL_CEC_DISABLE_IT(hcec, CEC_IER_TX_ALL_ERR);
      
      /* Enable the Peripheral */
      __HAL_CEC_ENABLE(hcec);
    
      __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_TXBR|CEC_ISR_TXEND);
          
      hcec->State = HAL_CEC_STATE_READY;
      /* Call the Process Unlocked before calling the Tx call back API to give the possibility to
      start again the Transmission under the Tx call back API */
      __HAL_UNLOCK(hcec);
      
      HAL_CEC_TxCpltCallback(hcec);
      
      return HAL_OK;
    }
    else
    {
      if (hcec->TxXferCount == 1)
      {
        /* if this is the last byte transmission, set TX End of Message (TXEOM) bit */
        __HAL_CEC_LAST_BYTE_TX_SET(hcec);
      }
      /* clear Tx-Byte request flag */
       __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_TXBR); 
       hcec->Instance->TXDR = *hcec->pTxBuffPtr++;
      hcec->TxXferCount--;
      
      /* Process Unlocked */
      __HAL_UNLOCK(hcec);
  
      return HAL_OK;
    }
  }
  else
  {
    return HAL_BUSY;   
  }
}


/**
  * @brief Receive data in interrupt mode. 
  * @param hcec: CEC handle
  * @param pData: pointer to received data buffer.
  * Note that the received data size is not known beforehand, the latter is known
  * when the reception is complete and is stored in hcec->RxXferSize.  
  * hcec->RxXferSize is the sum of opcodes + operands (0 to 14 operands max).
  * If only a header is received, hcec->RxXferSize = 0    
  * @retval HAL status
  */  
HAL_StatusTypeDef HAL_CEC_Receive_IT(CEC_HandleTypeDef *hcec, uint8_t *pData)
{  
  if(hcec->State == HAL_CEC_STATE_READY)
  {
    if(pData == HAL_NULL) 
    {
      hcec->State = HAL_CEC_STATE_ERROR;
      return HAL_ERROR;                                    
    }
    
    /* Process Locked */
    __HAL_LOCK(hcec);
    hcec->RxXferSize = 0;
    hcec->pRxBuffPtr = pData;
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;
    /* the IP is moving to a ready to receive state */
    hcec->State = HAL_CEC_STATE_STANDBY_RX;

    /* Disable Peripheral to write CEC_IER register */
    __HAL_CEC_DISABLE(hcec);
    
    /* Enable the following CEC Reception Error Interrupts: 
     * Rx overrun
     * Rx bit rising error
     * Rx short bit period error
     * Rx long bit period error
     * Rx missing acknowledge  */
    __HAL_CEC_ENABLE_IT(hcec, CEC_IER_RX_ALL_ERR);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcec);
    
    /* Enable the following two CEC Reception interrupts: 
     * Rx Byte Received IT 
     * End of Reception IT */
    __HAL_CEC_ENABLE_IT(hcec, CEC_IER_RXBRIE|CEC_IER_RXENDIE);
    
    __HAL_CEC_ENABLE(hcec);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}


    
/**
  * @brief This function handles CEC interrupt requests.
  * @param hcec: CEC handle
  * @retval None
  */
void HAL_CEC_IRQHandler(CEC_HandleTypeDef *hcec)
{
  /* save interrupts register for further error or interrupts handling purposes */
  hcec->ErrorCode = hcec->Instance->ISR;
  /* CEC TX missing acknowledge error interrupt occurred -------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_TXACKE) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_TXACKEIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_TXACKE);
    hcec->State = HAL_CEC_STATE_ERROR;
  }
  
  /* CEC transmit error interrupt occured --------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_TXERR) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_TXERRIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_TXERR);
    hcec->State = HAL_CEC_STATE_ERROR;
  }
  
  /* CEC TX underrun error interrupt occured --------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_TXUDR) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_TXUDRIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_TXUDR);
    hcec->State = HAL_CEC_STATE_ERROR;
  }
  
  /* CEC TX arbitration error interrupt occured --------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_ARBLST) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_ARBLSTIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_ARBLST);
    hcec->State = HAL_CEC_STATE_ERROR;
  }
  
  /* CEC RX overrun error interrupt occured --------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_RXOVR) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_RXOVRIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_RXOVR);
    hcec->State = HAL_CEC_STATE_ERROR;
  } 
  
  /* CEC RX bit rising error interrupt occured --------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_BRE) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_BREIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_BRE);
    hcec->State = HAL_CEC_STATE_ERROR;
  }   
  
  /* CEC RX short bit period error interrupt occured --------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_SBPE) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_SBPEIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_SBPE);
    hcec->State = HAL_CEC_STATE_ERROR;
  }   
  
  /* CEC RX long bit period error interrupt occured --------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_LBPE) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_LBPEIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_LBPE);
    hcec->State = HAL_CEC_STATE_ERROR;
  }   
  
  /* CEC RX missing acknowledge error interrupt occured --------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_RXACKE) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_RXACKEIE) != RESET))
  { 
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_RXACKE);
    hcec->State = HAL_CEC_STATE_ERROR;
  }   

  if ((hcec->ErrorCode & CEC_ISR_ALL_ERROR) != 0)
  {
    HAL_CEC_ErrorCallback(hcec);
  }

  /* CEC RX byte received interrupt  ---------------------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_RXBR) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_RXBRIE) != RESET))
  { 
    /* RXBR IT is cleared during HAL_CEC_Transmit_IT processing */
    CEC_Receive_IT(hcec);
  }
  
  /* CEC RX end received interrupt  ---------------------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_RXEND) != RESET) && (__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_RXENDIE) != RESET))
  { 
    /* RXBR IT is cleared during HAL_CEC_Transmit_IT processing */
    CEC_Receive_IT(hcec);
  }
  
  
  /* CEC TX byte request interrupt ------------------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_TXBR) != RESET) &&(__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_TXBRIE) != RESET))
  {
    /* TXBR IT is cleared during HAL_CEC_Transmit_IT processing */
    CEC_Transmit_IT(hcec);
  } 
  
  /* CEC TX end interrupt ------------------------------------------------*/
  if((__HAL_CEC_GET_IT(hcec, CEC_ISR_TXEND) != RESET) &&(__HAL_CEC_GET_IT_SOURCE(hcec, CEC_IER_TXENDIE) != RESET))
  {
   /* TXEND IT is cleared during HAL_CEC_Transmit_IT processing */
    CEC_Transmit_IT(hcec);
  } 
  
}


/**
  * @brief Tx Transfer completed callback
  * @param hcec: CEC handle
  * @retval None
  */
 __weak void HAL_CEC_TxCpltCallback(CEC_HandleTypeDef *hcec)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_TxCpltCallback can be implemented in the user file
   */ 
}

/**
  * @brief Rx Transfer completed callback
  * @param hcec: CEC handle
  * @retval None
  */
__weak void HAL_CEC_RxCpltCallback(CEC_HandleTypeDef *hcec)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_TxCpltCallback can be implemented in the user file
   */
}

/**
  * @brief CEC error callbacks
  * @param hcec: CEC handle
  * @retval None
  */
 __weak void HAL_CEC_ErrorCallback(CEC_HandleTypeDef *hcec)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_CEC_ErrorCallback can be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup CEC_Exported_Functions_Group3 Peripheral Control functions 
  *  @brief   CEC control functions 
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the CEC.
     (+) HAL_CEC_GetState() API can be helpful to check in run-time the state of the CEC peripheral. 
@endverbatim
  * @{
  */





/**
  * @brief return the CEC state
  * @param hcec: CEC handle
  * @retval HAL state
  */
HAL_CEC_StateTypeDef HAL_CEC_GetState(CEC_HandleTypeDef *hcec)
{
  return hcec->State;
}

/**
* @brief  Return the CEC error code
* @param  hcec : pointer to a CEC_HandleTypeDef structure that contains
  *              the configuration information for the specified CEC.
* @retval CEC Error Code
*/
uint32_t HAL_CEC_GetError(CEC_HandleTypeDef *hcec)
{
  return hcec->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CEC_Private_Functions CEC Private Functions
  * @{
  */

 /**
  * @brief Send data in interrupt mode 
  * @param hcec: CEC handle. 
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_CEC_Transmit_IT()   
  * @retval HAL status
  */  
static HAL_StatusTypeDef CEC_Transmit_IT(CEC_HandleTypeDef *hcec)
{
  /* if the IP is already busy or if there is a previous transmission
     already pending due to arbitration loss */
  if ((hcec->State == HAL_CEC_STATE_BUSY_TX)
        || (__HAL_CEC_GET_TRANSMISSION_START_FLAG(hcec) != RESET))
  {

    /* set state to BUSY TX, in case it wasn't set already (case
     * of transmission new attempt after arbitration loss) */
    if (hcec->State != HAL_CEC_STATE_BUSY_TX)
    {
      hcec->State = HAL_CEC_STATE_BUSY_TX;
    }

    /* if all data have been sent */
    if(hcec->TxXferCount == 0)
    {
      /* Disable Peripheral to write CEC_IER register */
      __HAL_CEC_DISABLE(hcec);
      
      /* Disable the CEC Transmission Interrupts */
      __HAL_CEC_DISABLE_IT(hcec, CEC_IER_TXBRIE|CEC_IER_TXENDIE);
      /* Disable the CEC Transmission Error Interrupts */
      __HAL_CEC_DISABLE_IT(hcec, CEC_IER_TX_ALL_ERR);
      
      /* Enable the Peripheral */
      __HAL_CEC_ENABLE(hcec);
    
      __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_TXBR|CEC_ISR_TXEND);
          
      hcec->State = HAL_CEC_STATE_READY;
      
      HAL_CEC_TxCpltCallback(hcec);
      
      return HAL_OK;
    }
    else
    {
      if (hcec->TxXferCount == 1)
      {
        /* if this is the last byte transmission, set TX End of Message (TXEOM) bit */
        __HAL_CEC_LAST_BYTE_TX_SET(hcec);
      }
      /* clear Tx-Byte request flag */
       __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_TXBR); 
       hcec->Instance->TXDR = *hcec->pTxBuffPtr++;
      hcec->TxXferCount--;
  
      return HAL_OK;
    }
  }
  else
  {
    return HAL_BUSY;   
  }
}


/**
  * @brief Receive data in interrupt mode. 
  * @param hcec: CEC handle.
  *         Function called under interruption only, once
  *         interruptions have been enabled by HAL_CEC_Receive_IT()   
  * @retval HAL status
  */  
static HAL_StatusTypeDef CEC_Receive_IT(CEC_HandleTypeDef *hcec)
{
  uint32_t tempisr;
  
  /* Three different conditions are tested to carry out the RX IT processing:
   * - the IP is in reception stand-by (the IP state is HAL_CEC_STATE_STANDBY_RX) and 
   *   the reception of the first byte is starting
   * - a message reception is already on-going (the IP state is HAL_CEC_STATE_BUSY_RX)
   *   and a new byte is being received
   * - a transmission has just been started (the IP state is HAL_CEC_STATE_BUSY_TX)
   *   but has been interrupted by a new message reception or discarded due to 
   *   arbitration loss: the reception of the first or higher priority message 
   *   (the arbitration winner) is starting */
  if ((hcec->State == HAL_CEC_STATE_STANDBY_RX) 
  ||  (hcec->State == HAL_CEC_STATE_BUSY_RX)
  ||  (hcec->State == HAL_CEC_STATE_BUSY_TX)) 
  {
    /* reception is starting */ 
    hcec->State = HAL_CEC_STATE_BUSY_RX;
    tempisr =  (uint32_t) (hcec->Instance->ISR);
    if ((tempisr & CEC_ISR_RXBR) != 0)
    {
      /* read received byte */
      *hcec->pRxBuffPtr++ = hcec->Instance->RXDR;
      /* if last byte has been received */      
      if ((tempisr & CEC_ISR_RXEND) != 0)
      {
        /* clear IT */
        __HAL_CEC_CLEAR_FLAG(hcec,CEC_ISR_RXBR|CEC_ISR_RXEND);
        /* RX interrupts are not disabled at this point.
         * Indeed, to disable the IT, the IP must be disabled first
         * which resets the TXSOM flag. In case of arbitration loss,
         * this leads to a transmission abort.
         * Therefore, RX interruptions disabling if so required,
         * is done in HAL_CEC_RxCpltCallback */
 
        /* IP state is moved to READY.
         * If the IP must remain in standby mode to listen
         * any new message, it is up to HAL_CEC_RxCpltCallback
         * to move it again to HAL_CEC_STATE_STANDBY_RX */  
        hcec->State = HAL_CEC_STATE_READY; 

        HAL_CEC_RxCpltCallback(hcec);
        
        return HAL_OK;
      } 
      __HAL_CEC_CLEAR_FLAG(hcec, CEC_ISR_RXBR);  

      hcec->RxXferSize++;
      
      return HAL_OK;
    }
    else
    {
      return HAL_BUSY; 
    }
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
 * @}
 */ 
 
/**
  * @}
  */

#endif /* defined(STM32F373xC) || defined(STM32F378xx) */

#endif /* HAL_CEC_MODULE_ENABLED */
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
