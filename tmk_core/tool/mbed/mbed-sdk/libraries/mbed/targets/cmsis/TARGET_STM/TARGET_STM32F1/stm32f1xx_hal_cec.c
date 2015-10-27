/**
  ******************************************************************************
  * @file    stm32f1xx_hal_cec.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   CEC HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the High Definition Multimedia Interface 
  *          Consumer Electronics Control Peripheral (CEC).
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *          
  *  @verbatim    
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]  
    The CEC HAL driver can be used as follows:
    (#) Declare a CEC_HandleTypeDef handle structure.
    (#) Initialize the CEC low level resources by implementing the HAL_CEC_MspInit ()API:
        (##) Enable the CEC interface clock.
        (##) Enable the clock for the CEC GPIOs.
        (##) Configure these CEC pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (HAL_CEC_Transmit_IT()
             and HAL_CEC_Receive_IT() APIs):
        (##) Configure the CEC interrupt priority.
        (##) Enable the NVIC CEC IRQ handle.
        (##) The CEC interrupt is activated/deactivated by the HAL driver

    (#) Program the Bit Timing Error Mode and the Bit Period Error Mode in the hcec Init structure.

    (#) Initialize the CEC registers by calling the HAL_CEC_Init() API.
        
    (#) This API (HAL_CEC_Init()) configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
        by calling the customized HAL_CEC_MspInit() API.

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
#include "stm32f1xx_hal.h"

#ifdef HAL_CEC_MODULE_ENABLED

#if defined(STM32F100xB) || defined(STM32F100xE)

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup CEC CEC
  * @brief HAL CEC module driver
  * @{
  */
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup CEC_Private_Constants CEC Private Constants
  * @{
  */
#define CEC_CFGR_FIELDS (CEC_CFGR_BTEM | CEC_CFGR_BPEM )
#define CEC_FLAG_TRANSMIT_MASK (CEC_FLAG_TSOM|CEC_FLAG_TEOM|CEC_FLAG_TBTRF)
#define CEC_FLAG_RECEIVE_MASK (CEC_FLAG_RSOM|CEC_FLAG_REOM|CEC_FLAG_RBTF)
#define CEC_ESR_ALL_ERROR (CEC_ESR_BTE|CEC_ESR_BPE|CEC_ESR_RBTFE|CEC_ESR_SBE|CEC_ESR_ACKE|CEC_ESR_LINE|CEC_ESR_TBTFE)
#define CEC_RXXFERSIZE_INITIALIZE 0xFFFF /*!< Value used to initialise the RxXferSize of the handle */
/**
 * @}
 */
 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup CEC_Private_Functions CEC Private Functions
  * @{
  */
static HAL_StatusTypeDef CEC_Transmit_IT(CEC_HandleTypeDef *hcec);
static HAL_StatusTypeDef CEC_Receive_IT(CEC_HandleTypeDef *hcec);
/**
 * @}
 */
 
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
        (++) TimingErrorFree
        (++) PeriodErrorFree 
        (++) InitiatorAddress

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
  /* Check the CEC handle allocation */
  if(hcec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */ 
  assert_param(IS_CEC_ALL_INSTANCE(hcec->Instance));
  assert_param(IS_CEC_BIT_TIMING_ERROR_MODE(hcec->Init.TimingErrorFree));
  assert_param(IS_CEC_BIT_PERIOD_ERROR_MODE(hcec->Init.PeriodErrorFree));
  assert_param(IS_CEC_ADDRESS(hcec->Init.InitiatorAddress));

  if(hcec->State == HAL_CEC_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcec-> Lock = HAL_UNLOCKED;
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_CEC_MspInit(hcec);
  }
  
  hcec->State = HAL_CEC_STATE_BUSY;
  
  /* Disable the Peripheral */
  __HAL_CEC_DISABLE(hcec);
  
  /* Write to CEC Control Register */
  MODIFY_REG(hcec->Instance->CFGR, CEC_CFGR_FIELDS, hcec->Init.TimingErrorFree|hcec->Init.PeriodErrorFree);
  
  /* Write to CEC Own Address Register */
  MODIFY_REG(hcec->Instance->OAR, CEC_OAR_OA, hcec->Init.InitiatorAddress);
  
  /* Configure the prescaler to generate the required 50 microseconds time base.*/
  MODIFY_REG(hcec->Instance->PRES, CEC_PRES_PRES, 50*(HAL_RCC_GetPCLK1Freq()/1000000)-1);
  
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
  if(hcec == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_CEC_ALL_INSTANCE(hcec->Instance));

  hcec->State = HAL_CEC_STATE_BUSY;
  
  /* Set peripheral to reset state */
  hcec->Instance->CFGR = 0x0;
  hcec->Instance->OAR = 0x0;
  hcec->Instance->PRES = 0x0;
  hcec->Instance->CFGR = 0x0;
  hcec->Instance->ESR = 0x0;
  hcec->Instance->CSR = 0x0;
  hcec->Instance->TXD = 0x0;
  hcec->Instance->RXD = 0x0;
  
  /* Disable the Peripheral */
  __HAL_CEC_DISABLE(hcec);
  
  /* DeInit the low level hardware */
  HAL_CEC_MspDeInit(hcec);
  
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
                      ##### IO operation functions ##### 
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the CEC data transfers.

    (#) There are two modes of transfer:
       (##) Blocking mode: The communication is performed in polling mode. 
            The HAL status of all data processing is returned by the same function 
            after finishing transfer.  
       (##) No-Blocking mode: The communication is performed using Interrupts. 
           These API's return the HAL status.
           The end of the data processing will be indicated through the 
           dedicated CEC IRQ when using Interrupt mode.
           The HAL_CEC_TxCpltCallback(), HAL_CEC_RxCpltCallback() user callbacks 
           will be executed respectivelly at the end of the Transmit or Receive process.
           The HAL_CEC_ErrorCallback()user callback will be executed when a communication 
           error is detected
    (#) Blocking mode API's are :
        (##) HAL_CEC_Transmit()
        (##) HAL_CEC_Receive() 
    (#) Non-Blocking mode API's with Interrupt are :
        (##) HAL_CEC_Transmit_IT()
        (##) HAL_CEC_Receive_IT()
        (##) HAL_CEC_IRQHandler()
    (#) A set of Transfer Complete Callbacks are provided in No_Blocking mode:
        (##) HAL_CEC_TxCpltCallback()
        (##) HAL_CEC_RxCpltCallback()
        (##) HAL_CEC_ErrorCallback()
      
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
  uint32_t tickstart = 0;

  /* If the IP is ready */
  if((hcec->State == HAL_CEC_STATE_READY) 
     && (__HAL_CEC_GET_TRANSMISSION_START_FLAG(hcec) == RESET)) 
  {
    /* Basic check on pData pointer */
    if(((pData == NULL) && (Size > 0)) || (! IS_CEC_MSGSIZE(Size))) 
    {
      return  HAL_ERROR;
    }

    assert_param(IS_CEC_ADDRESS(DestinationAddress));
    
    /* Process Locked */
    __HAL_LOCK(hcec);
    
    /* Enter the transmit mode */
    hcec->State = HAL_CEC_STATE_BUSY_TX;
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;

    /* Initialize the number of bytes to send,
     * 0 means only one header is sent (ping operation) */
    hcec->TxXferCount = Size;

    /* Send header block */
    temp = (uint8_t)((uint32_t)(hcec->Init.InitiatorAddress) << CEC_INITIATOR_LSB_POS) | DestinationAddress;
    hcec->Instance->TXD = temp;

    /* In case no data to be sent, sender is only pinging the system */
    if (Size != 0)
    {    
      /* Set TX Start of Message (TXSOM) bit */
      hcec->Instance->CSR = CEC_FLAG_TSOM;
    }
    else
    {
      /* Send a ping command */
      hcec->Instance->CSR = CEC_FLAG_TEOM|CEC_FLAG_TSOM;
    }

    /* Polling TBTRF bit with timeout handling*/
    while (hcec->TxXferCount > 0)
    {
      /* Decreasing of the number of remaining data to receive */
      hcec->TxXferCount--;
      
      /* Timeout handling */
      tickstart = HAL_GetTick();
      
      /* Waiting for the next data transmission */
      while(HAL_IS_BIT_CLR(hcec->Instance->CSR, CEC_FLAG_TBTRF))
      {
        /* Timeout handling */
        if(Timeout != HAL_MAX_DELAY)
        {
          if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
          {
            hcec->State = HAL_CEC_STATE_READY; 
            /* Process Unlocked */
            __HAL_UNLOCK(hcec);  
            return HAL_TIMEOUT;
          }
        }        

        /* Check if an error occured */
        if(HAL_IS_BIT_SET(hcec->Instance->CSR, CEC_FLAG_TERR) || HAL_IS_BIT_SET(hcec->Instance->CSR, CEC_FLAG_RERR))
        {
          /* Copy ESR for error handling purposes */
          hcec->ErrorCode = READ_BIT(hcec->Instance->ESR, CEC_ESR_ALL_ERROR);
          
          /* Acknowledgement of the error */
          __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_TERR);
          __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_RERR);
          
          hcec->State = HAL_CEC_STATE_READY;
          __HAL_UNLOCK(hcec);
          return  HAL_ERROR;                                    
        }
      }
      
      /* Write the next data to TX buffer */
      hcec->Instance->TXD = *pData++;
      
      /* If this is the last byte of the ongoing transmission */
      if (hcec->TxXferCount == 0)
      {
        /* Acknowledge byte request and signal end of message */
        MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, CEC_FLAG_TEOM);
      }
      else
      {
        /* Acknowledge byte request by writing 0x00 */
        MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, 0x00);
      }
    }
    
    /* Timeout handling */
    tickstart = HAL_GetTick();
    
    /* Wait for message transmission completion (TBTRF is set) */
    while (HAL_IS_BIT_CLR(hcec->Instance->CSR, CEC_FLAG_TBTRF))
    {
      /* Timeout handling */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          hcec->State = HAL_CEC_STATE_READY;
          __HAL_UNLOCK(hcec);             
          return HAL_TIMEOUT;
        }
      } 

      /* Check of error during transmission of the last byte */
      if(HAL_IS_BIT_SET(hcec->Instance->CSR, CEC_FLAG_TERR) || HAL_IS_BIT_SET(hcec->Instance->CSR, CEC_FLAG_RERR))
      {
        /* Copy ESR for error handling purposes */
        hcec->ErrorCode = READ_BIT(hcec->Instance->ESR, CEC_ESR_ALL_ERROR);
        
        /* Acknowledgement of the error */
        __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_TERR);
        __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_RERR);
        
        hcec->State = HAL_CEC_STATE_READY;
        __HAL_UNLOCK(hcec);
        return  HAL_ERROR;                                    
      }
    }
    
    /* Check of error after the last byte transmission */
    if(HAL_IS_BIT_SET(hcec->Instance->CSR, CEC_FLAG_TERR) || HAL_IS_BIT_SET(hcec->Instance->CSR, CEC_FLAG_RERR))
    {
      /* Copy ESR for error handling purposes */
      hcec->ErrorCode = READ_BIT(hcec->Instance->ESR, CEC_ESR_ALL_ERROR);
      
      /* Acknowledgement of the error */
      __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_TERR);
      __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_RERR);
      
      hcec->State = HAL_CEC_STATE_READY;
      __HAL_UNLOCK(hcec);
      return  HAL_ERROR;
    }
    
    /* Acknowledge successful completion by writing 0x00 */
    MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, 0x00);
    
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
  * @brief Receive data in blocking mode. 
  * @param hcec: CEC handle
  * @param pData: pointer to received data buffer.
  * @param Timeout: Timeout duration.
  * @note  The received data size is not known beforehand, the latter is known
  *        when the reception is complete and is stored in hcec->RxXferSize.  
  *        hcec->RxXferSize is the sum of opcodes + operands (0 to 14 operands max).
  *        If only a header is received, hcec->RxXferSize = 0    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_Receive(CEC_HandleTypeDef *hcec, uint8_t *pData, uint32_t Timeout)
{
  uint32_t temp = 0;
  uint32_t tickstart = 0;   

  if(hcec->State == HAL_CEC_STATE_READY)
  {
    if(pData == NULL) 
    {
      return HAL_ERROR;
    }
    
    /* When a ping is received, RxXferSize is 0*/
    /* When a message is received, RxXferSize contains the number of received bytes */
    hcec->RxXferSize = CEC_RXXFERSIZE_INITIALIZE; 
    
    /* Process Locked */
    __HAL_LOCK(hcec);

    hcec->ErrorCode = HAL_CEC_ERROR_NONE;
    
    /* Continue the reception until the End Of Message is received (CEC_FLAG_REOM) */
    do
    {
      /* Timeout handling */
      tickstart = HAL_GetTick();
      
      /* Wait for next byte to be received */
      while (HAL_IS_BIT_CLR(hcec->Instance->CSR, CEC_FLAG_RBTF))
      {
        /* Timeout handling */
        if(Timeout != HAL_MAX_DELAY)
        {
          if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
          {
            hcec->State = HAL_CEC_STATE_READY;
            __HAL_UNLOCK(hcec);    
            return HAL_TIMEOUT;
          }
        }
        
        /* Check if an error occured during the reception */
        if(HAL_IS_BIT_SET(hcec->Instance->CSR, CEC_FLAG_RERR))
        {
          /* Copy ESR for error handling purposes */
          hcec->ErrorCode = READ_BIT(hcec->Instance->ESR, CEC_ESR_ALL_ERROR);
          
          /* Acknowledgement of the error */
          __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_RERR);
          
          hcec->State = HAL_CEC_STATE_READY;
          __HAL_UNLOCK(hcec);
          return  HAL_ERROR;
        }
      }
      
      /* Keep the value of CSR register as the register is cleared during reception process */
      temp = hcec->Instance->CSR;
      
      /* Read received data */
      *pData++ = hcec->Instance->RXD;
      
      /* Acknowledge received byte by writing 0x00 */
      CLEAR_BIT(hcec->Instance->CSR, CEC_FLAG_RECEIVE_MASK);
      
      /* Increment the number of received data */
      if(hcec->RxXferSize == CEC_RXXFERSIZE_INITIALIZE)
      {
        hcec->RxXferSize = 0;
      }
      else
      {
        hcec->RxXferSize++;
      }
      
    }while (HAL_IS_BIT_CLR(temp, CEC_FLAG_REOM));
    
    hcec->State = HAL_CEC_STATE_READY;
    __HAL_UNLOCK(hcec);  
    
    if(IS_CEC_MSGSIZE(hcec->RxXferSize))
    {
      return HAL_OK;
    }
    else
    {
      return HAL_ERROR;
    }
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
  uint32_t tmp_state = 0;
  
  tmp_state = hcec->State;
  if(((tmp_state == HAL_CEC_STATE_READY) || (tmp_state == HAL_CEC_STATE_BUSY_RX))
     && (__HAL_CEC_GET_TRANSMISSION_START_FLAG(hcec) == RESET)) 
  {
    
    /* Basic check on pData pointer */
    if(((pData == NULL) && (Size > 0)) || (! IS_CEC_MSGSIZE(Size))) 
    {
      return  HAL_ERROR;
    }

    assert_param(IS_CEC_ADDRESS(DestinationAddress));
    
    /* Process Locked */
    __HAL_LOCK(hcec);
    hcec->pTxBuffPtr = pData;
    
    /* Check if a receive process is ongoing or not */
    if(hcec->State == HAL_CEC_STATE_BUSY_RX) 
    {
      hcec->State = HAL_CEC_STATE_BUSY_TX_RX;
      
      /* Interrupt are not enabled here because they are already enabled in the Reception process */
    }
    else
    {
      hcec->State = HAL_CEC_STATE_BUSY_TX;    
      
      /* Enable the CEC interrupt */
      __HAL_CEC_ENABLE_IT(hcec, CEC_IT_IE);
    }    
    
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;
    
    /* initialize the number of bytes to send,
     * 0 means only one header is sent (ping operation) */
    hcec->TxXferCount = Size;

    /* send header block */
    temp = (uint8_t)((uint32_t)(hcec->Init.InitiatorAddress) << CEC_INITIATOR_LSB_POS) | DestinationAddress;
    hcec->Instance->TXD = temp;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcec); 

    /* case no data to be sent, sender is only pinging the system */
    if (Size != 0)
    {    
      /* Set TX Start of Message (TXSOM) bit */
      MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, CEC_FLAG_TSOM);
    }
    else
    {
      /* Send a ping command */
      MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, CEC_FLAG_TEOM|CEC_FLAG_TSOM);
    }
    return HAL_OK;
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
  * @note  The received data size is not known beforehand, the latter is known
  *        when the reception is complete and is stored in hcec->RxXferSize.  
  *        hcec->RxXferSize is the sum of opcodes + operands (0 to 14 operands max).
  *        If only a header is received, hcec->RxXferSize = 0    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CEC_Receive_IT(CEC_HandleTypeDef *hcec, uint8_t *pData)
{
  uint32_t tmp_state = 0;
  tmp_state = hcec->State;
  if((tmp_state == HAL_CEC_STATE_READY) || (tmp_state == HAL_CEC_STATE_BUSY_TX))
  {
    if(pData == NULL) 
    {
      return HAL_ERROR;                                    
    }
    
    /* When a ping is received, RxXferSize is 0 */
    /* When a message is received, RxXferSize contains the number of received bytes */
    hcec->RxXferSize = CEC_RXXFERSIZE_INITIALIZE;
    
    /* Process Locked */
    __HAL_LOCK(hcec);

    hcec->pRxBuffPtr = pData;
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;

    /* Process Unlocked */
    __HAL_UNLOCK(hcec);
    
    /* Check if a transmit process is ongoing or not */
    if(hcec->State == HAL_CEC_STATE_BUSY_TX)
    {
      hcec->State = HAL_CEC_STATE_BUSY_TX_RX;
    }
    else
    {
      hcec->State = HAL_CEC_STATE_BUSY_RX;    
      
      /* Enable CEC interrupt */
      __HAL_CEC_ENABLE_IT(hcec, CEC_IT_IE);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
  * @brief Get size of the received frame.
  * @param hcec: CEC handle
  * @retval Frame size
  */
uint32_t HAL_CEC_GetReceivedFrameSize(CEC_HandleTypeDef *hcec)
{
  return hcec->RxXferSize;
}
  
/**
  * @brief This function handles CEC interrupt requests.
  * @param hcec: CEC handle
  * @retval None
  */
void HAL_CEC_IRQHandler(CEC_HandleTypeDef *hcec)
{
  /* Save error status register for further error handling purposes */
  hcec->ErrorCode = READ_BIT(hcec->Instance->ESR, CEC_ESR_ALL_ERROR);

  /* Transmit error */
  if((__HAL_CEC_GET_FLAG(hcec, CEC_FLAG_TERR) != RESET))
  {
    /* Acknowledgement of the error */
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_TERR);
    
    /* Check if a receive process is ongoing or not */
    if(hcec->State == HAL_CEC_STATE_BUSY_TX_RX) 
    {
      /* Interrupts are not disabled due to reception still ongoing */
      
      hcec->State = HAL_CEC_STATE_BUSY_RX;
    }
    else
    {
      /* Disable the CEC Transmission Interrupts */
      __HAL_CEC_DISABLE_IT(hcec, CEC_IT_IE);
    
      hcec->State = HAL_CEC_STATE_READY;
    }    
  }
  
  /* Receive error */
  if((__HAL_CEC_GET_FLAG(hcec, CEC_FLAG_RERR) != RESET))
  {
    /* Acknowledgement of the error */
    __HAL_CEC_CLEAR_FLAG(hcec, CEC_FLAG_RERR);
    
    /* Check if a transmit process is ongoing or not */
    if(hcec->State == HAL_CEC_STATE_BUSY_TX_RX) 
    {
      /* Interrupts are not disabled due to reception still ongoing */
      
      hcec->State = HAL_CEC_STATE_BUSY_TX;
    }
    else
    {
      /* Disable the CEC Transmission Interrupts */
      __HAL_CEC_DISABLE_IT(hcec, CEC_IT_IE);
      
      hcec->State = HAL_CEC_STATE_READY;
    }
  } 
  
  if ((hcec->ErrorCode & CEC_ESR_ALL_ERROR) != 0)
  {
    HAL_CEC_ErrorCallback(hcec);
  }
  
  /* Transmit byte request or block transfer finished */
  if((__HAL_CEC_GET_FLAG(hcec, CEC_FLAG_TBTRF) != RESET))
  {
    CEC_Transmit_IT(hcec);
  }  

  /* Receive byte or block transfer finished */
  if((__HAL_CEC_GET_FLAG(hcec, CEC_FLAG_RBTF) != RESET))
  {
    CEC_Receive_IT(hcec);
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
            the HAL_CEC_RxCpltCallback can be implemented in the user file
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
     (+) HAL_CEC_GetError() API can be helpful to get the error code of a failed transmission or reception. 
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

/** @addtogroup CEC_Private_Functions
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
  uint32_t tmp_state = 0;
  
  tmp_state = hcec->State;
  /* if the IP is already busy or if there is a previous transmission
     already pending due to arbitration loss */
  if(((tmp_state == HAL_CEC_STATE_BUSY_TX) || (tmp_state == HAL_CEC_STATE_BUSY_TX_RX))
        || (__HAL_CEC_GET_TRANSMISSION_START_FLAG(hcec) != RESET))
  {
    /* if all data have been sent */
    if(hcec->TxXferCount == 0)
    {
      /* Acknowledge successful completion by writing 0x00 */
      MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, 0x00);

      /* Check if a receive process is ongoing or not */
      if(hcec->State == HAL_CEC_STATE_BUSY_TX_RX) 
      {
        /* Interrupts are not disabled due to reception still ongoing */
        
        hcec->State = HAL_CEC_STATE_BUSY_RX;
      }
      else
      {
        /* Disable the CEC Transmission Interrupts */
        __HAL_CEC_DISABLE_IT(hcec, CEC_IT_IE);
      
        hcec->State = HAL_CEC_STATE_READY;
      }
      
      HAL_CEC_TxCpltCallback(hcec);
      
      return HAL_OK;
    }
    else
    {
      /* Reduce the number of bytes to transfer by one */
      hcec->TxXferCount--;
      
      /* Write data to TX buffer*/
      hcec->Instance->TXD = *hcec->pTxBuffPtr++;
      
      /* If this is the last byte of the ongoing transmission */
      if (hcec->TxXferCount == 0)
      {
        /* Acknowledge byte request and signal end of message */
        MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, CEC_FLAG_TEOM);
      }
      else
      {
        /* Acknowledge byte request by writing 0x00 */
        MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_TRANSMIT_MASK, 0x00);
      }  
      
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
  static uint32_t temp;
  uint32_t tmp_state = 0;

  tmp_state = hcec->State; 
  if((tmp_state == HAL_CEC_STATE_BUSY_RX) || (tmp_state == HAL_CEC_STATE_BUSY_TX_RX)) 
  {
    temp = hcec->Instance->CSR;
    
    /* Store received data */
    *hcec->pRxBuffPtr++ = hcec->Instance->RXD;
    
    /* Acknowledge received byte by writing 0x00 */
    MODIFY_REG(hcec->Instance->CSR, CEC_FLAG_RECEIVE_MASK, 0x00);
    
    /* Increment the number of received data */
    if(hcec->RxXferSize == CEC_RXXFERSIZE_INITIALIZE)
    {
      hcec->RxXferSize = 0;
    }
    else
    {
      hcec->RxXferSize++;
    }
    
    /* If the End Of Message is reached */
    if(HAL_IS_BIT_SET(temp, CEC_FLAG_REOM))
    {
      if(hcec->State == HAL_CEC_STATE_BUSY_TX_RX) 
      {
        /* Interrupts are not disabled due to transmission still ongoing */
        
        hcec->State = HAL_CEC_STATE_BUSY_TX;
      }
      else
      {
        /* Disable the CEC Transmission Interrupts */
        __HAL_CEC_DISABLE_IT(hcec, CEC_IT_IE);
        
        hcec->State = HAL_CEC_STATE_READY;
      }

      HAL_CEC_RxCpltCallback(hcec);

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

#endif /* defined(STM32F100xB) || defined(STM32F100xE) */

#endif /* HAL_CEC_MODULE_ENABLED */
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
