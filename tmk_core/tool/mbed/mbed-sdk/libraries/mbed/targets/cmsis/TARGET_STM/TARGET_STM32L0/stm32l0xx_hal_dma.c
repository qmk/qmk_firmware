/**
  ******************************************************************************
  * @file    stm32l0xx_hal_dma.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   DMA HAL module driver.
  *    
  *         This file provides firmware functions to manage the following 
  *         functionalities of the Direct Memory Access (DMA) peripheral:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral State functions
  *  
  *           
  @verbatim     
  ==============================================================================      
                        ##### How to use this driver #####
  ============================================================================== 
  [..]
   (#) Enable and configure the peripheral to be connected to the DMA Channel
       (except for internal SRAM / FLASH memories: no initialization is 
       necessary). 
          
   (#) For a given Channel, program the required configuration through the following parameters:   
       Channel request, Transfer Direction, Source and Destination data formats, 
       Circular, Normal or peripheral flow control mode, Channel Priority level, 
       Source and Destination Increment mode using HAL_DMA_Init() function.
   
     *** Polling mode IO operation ***
     =================================   
    [..] 
          (+) Use HAL_DMA_Start() to start DMA transfer after the configuration of Source 
              address and destination address and the Length of data to be transferred
          (+) Use HAL_DMA_PollForTransfer() to poll for the end of current transfer, in this  
              case a fixed Timeout can be configured by User depending from his application.
               
     *** Interrupt mode IO operation ***    
     =================================== 
    [..]     
          (+) Configure the DMA interrupt priority using HAL_NVIC_SetPriority()
          (+) Enable the DMA IRQ handler using HAL_NVIC_EnableIRQ() 
          (+) Use HAL_DMA_Start_IT() to start DMA transfer after the configuration of  
              Source address and destination address and the Length of data to be transferred. In this 
              case the DMA interrupt is configured 
          (+) Use HAL_DMA_IRQHandler() called under DMA_IRQHandler() Interrupt subroutine
          (+) At the end of data transfer HAL_DMA_IRQHandler() function is executed and user can 
              add his own function by customization of function pointer XferCpltCallback and 
              XferErrorCallback (i.e a member of DMA handle structure). 
                
   (#) Use HAL_DMA_GetState() function to return the DMA state and HAL_DMA_GetError() in case of error 
       detection.
         
   (#) Use HAL_DMA_Abort() function to abort the current transfer              
                   
   -@-   In Memory-to-Memory transfer mode, Circular mode is not allowed.          
  
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

/** @addtogroup DMA DMA
  * @brief DMA HAL module driver
  * @{
  */

#ifdef HAL_DMA_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/  
/** @defgroup DMA_Private_Types DMA Private Types
  *
  * @{
  */
#define HAL_TIMEOUT_DMA_ABORT    ((uint32_t)1000)  /* 1s  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/  
/** @defgroup DMA_Private_Functions DMA Private Functions
  * @{
  */
static void DMA_SetConfig(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions DMA Exported Functions
  * @{
  */

/** @addtogroup DMA_Exported_Functions_Group1 
 *  @brief   Initialization/de-initialization functions 
 *
@verbatim   
 ===============================================================================
             ##### Initialization and de-initialization functions  #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the DMA
      (+) De-Initialize the DMA 

@endverbatim
  * @{
  */
  
/**
  * @brief  Initializes the DMA according to the specified
  *         parameters in the DMA_InitTypeDef and create the associated handle.
  * @param  hdma: Pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Channel.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma)
{ 
  uint32_t tmp = 0;
  
  /* Check the DMA peripheral state */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(hdma->Instance));
  assert_param(IS_DMA_ALL_REQUEST(hdma->Init.Request));
  assert_param(IS_DMA_DIRECTION(hdma->Init.Direction));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(hdma->Init.PeriphInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(hdma->Init.MemInc));
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(hdma->Init.PeriphDataAlignment));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(hdma->Init.MemDataAlignment));
  assert_param(IS_DMA_MODE(hdma->Init.Mode));
  assert_param(IS_DMA_PRIORITY(hdma->Init.Priority));
  
  /* Change DMA peripheral state */
  hdma->State = HAL_DMA_STATE_BUSY;

  /* Get the CR register value */
  tmp = hdma->Instance->CCR;
  
  /* Clear PL, MSIZE, PSIZE, MINC, PINC, CIRC, DIR bits */
  tmp &= ((uint32_t)~(DMA_CCR_PL    | DMA_CCR_MSIZE  | DMA_CCR_PSIZE  | \
                      DMA_CCR_MINC  | DMA_CCR_PINC   | DMA_CCR_CIRC   | \
                      DMA_CCR_DIR));
  
  /* Prepare the DMA Channel configuration */
  tmp |=  hdma->Init.Direction        |
          hdma->Init.PeriphInc           | hdma->Init.MemInc           |
          hdma->Init.PeriphDataAlignment | hdma->Init.MemDataAlignment |
          hdma->Init.Mode                | hdma->Init.Priority;

  /* Write to DMA Channel CR register */
  hdma->Instance->CCR = tmp;  
  
  /* Write to DMA channel selection register */
  if (hdma->Instance == DMA1_Channel1)
  {
    /*Reset request selection for DMA1 Channel1*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C1S;
    
    /* Configure request selection for DMA1 Channel1 */
    DMA1_CSELR->CSELR |= hdma->Init.Request;
  }
  else if (hdma->Instance == DMA1_Channel2)
  {
    /*Reset request selection for DMA1 Channel2*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C2S;
    
    /* Configure request selection for DMA1 Channel2 */
    DMA1_CSELR->CSELR |= (uint32_t)(hdma->Init.Request << 4);
  }
  else if (hdma->Instance == DMA1_Channel3)
  {
    /*Reset request selection for DMA1 Channel3*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C3S;
    
    /* Configure request selection for DMA1 Channel3 */
    DMA1_CSELR->CSELR |= (uint32_t) (hdma->Init.Request << 8);
  }
  else if (hdma->Instance == DMA1_Channel4)
  {
    /*Reset request selection for DMA1 Channel4*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C4S;
    
    /* Configure request selection for DMA1 Channel4 */
    DMA1_CSELR->CSELR |= (uint32_t) (hdma->Init.Request << 12);
  }
  else if (hdma->Instance == DMA1_Channel5)
  {
    /*Reset request selection for DMA1 Channel5*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C5S;
    
    /* Configure request selection for DMA1 Channel5 */
    DMA1_CSELR->CSELR |= (uint32_t) (hdma->Init.Request << 16);
  }
  else if (hdma->Instance == DMA1_Channel6)
  {
    /*Reset request selection for DMA1 Channel6*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C6S;
    
    /* Configure request selection for DMA1 Channel6 */
    DMA1_CSELR->CSELR |= (uint32_t) (hdma->Init.Request << 20);
  }
  else if (hdma->Instance == DMA1_Channel7)
  {
    /*Reset request selection for DMA1 Channel7*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C7S;
    
    /* Configure request selection for DMA1 Channel7 */
    DMA1_CSELR->CSELR |= (uint32_t) (hdma->Init.Request << 24);
  }
   
  /* Initialize the DMA state*/
  hdma->State  = HAL_DMA_STATE_READY;
  
  return HAL_OK;
}  
  
/**
  * @brief  DeInitializes the DMA peripheral 
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Channel.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma)
{
  /* Check the DMA peripheral state */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the DMA peripheral state */
  if(hdma->State == HAL_DMA_STATE_BUSY)
  {
    return HAL_ERROR;
  }

  /* Disable the selected DMA Channelx */
  __HAL_DMA_DISABLE(hdma);
  
  /* Reset DMA Channel control register */
  hdma->Instance->CCR  = 0;
  
  /* Reset DMA Channel Number of Data to Transfer register */
  hdma->Instance->CNDTR = 0;
  
  /* Reset DMA Channel peripheral address register */
  hdma->Instance->CPAR  = 0;
  
  /* Reset DMA Channel memory address register */
  hdma->Instance->CMAR = 0;

  /* Clear all flags */
  __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_GI_FLAG_INDEX(hdma));
  __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma));
  __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TE_FLAG_INDEX(hdma));
  __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_HT_FLAG_INDEX(hdma));
  
  /* Reset DMA channel selection register */
  if (hdma->Instance == DMA1_Channel1)
  {
    /*Reset DMA request*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C1S;
  }
  else if (hdma->Instance == DMA1_Channel2)
  {
    /*Reset DMA request*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C2S;
  }
  else if (hdma->Instance == DMA1_Channel3)
  {
    /*Reset DMA request*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C3S;
  }
  else if (hdma->Instance == DMA1_Channel4)
  {
    /*Reset DMA request*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C4S;
  }
  else if (hdma->Instance == DMA1_Channel5)
  {
    /*Reset DMA request*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C5S;
  }
  else if (hdma->Instance == DMA1_Channel6)
  {
    /*Reset DMA request*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C6S;
  }
  else if (hdma->Instance == DMA1_Channel7)
  {
    /*Reset DMA request*/
    DMA1_CSELR->CSELR &= ~DMA_CSELR_C7S;
  }
  
  /* Initialise the error code */
  hdma->ErrorCode = HAL_DMA_ERROR_NONE;

  /* Initialize the DMA state */
  hdma->State = HAL_DMA_STATE_RESET;
  
  /* Release Lock */
  __HAL_UNLOCK(hdma);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group2  
 *  @brief   I/O operation functions  
 *
@verbatim   
 ===============================================================================
                      #####  IO operation functions  #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure the source, destination address and data length and Start DMA transfer
      (+) Configure the source, destination address and data length and 
          Start DMA transfer with interrupt
      (+) Abort DMA transfer
      (+) Poll for transfer complete
      (+) Handle DMA interrupt request  

@endverbatim
  * @{
  */

/**
  * @brief  Starts the DMA Transfer.
  * @param  hdma      : pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Channel.  
  * @param  SrcAddress: The source memory Buffer address
  * @param  DstAddress: The destination memory Buffer address
  * @param  DataLength: The length of data to be transferred from source to destination
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{ 
  /* Process locked */
  __HAL_LOCK(hdma);  

  /* Change DMA peripheral state */  
  hdma->State = HAL_DMA_STATE_BUSY;  

   /* Check the parameters */
  assert_param(IS_DMA_BUFFER_SIZE(DataLength));
  
  /* Disable the peripheral */
  __HAL_DMA_DISABLE(hdma);  
  
  /* Configure the source, destination address and the data length */
  DMA_SetConfig(hdma, SrcAddress, DstAddress, DataLength);

  /* Enable the Peripheral */
  __HAL_DMA_ENABLE(hdma);  

  return HAL_OK; 
} 

/**
  * @brief  Start the DMA Transfer with interrupt enabled.
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Channel.  
  * @param  SrcAddress: The source memory Buffer address
  * @param  DstAddress: The destination memory Buffer address
  * @param  DataLength: The length of data to be transferred from source to destination
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
  /* Process locked */
  __HAL_LOCK(hdma);

  /* Change DMA peripheral state */  
  hdma->State = HAL_DMA_STATE_BUSY;  

   /* Check the parameters */
  assert_param(IS_DMA_BUFFER_SIZE(DataLength));
  
  /* Disable the peripheral */
  __HAL_DMA_DISABLE(hdma);
  
  /* Configure the source, destination address and the data length */  
  DMA_SetConfig(hdma, SrcAddress, DstAddress, DataLength);
  
  /* Enable the transfer complete interrupt */
  __HAL_DMA_ENABLE_IT(hdma, DMA_IT_TC);

  /* Enable the Half transfer complete interrupt */
  __HAL_DMA_ENABLE_IT(hdma, DMA_IT_HT);  

  /* Enable the transfer Error interrupt */
  __HAL_DMA_ENABLE_IT(hdma, DMA_IT_TE);
  
   /* Enable the Peripheral */
  __HAL_DMA_ENABLE(hdma);   
  
  return HAL_OK;    
} 

/**
  * @brief  Aborts the DMA Transfer.
  * @param  hdma  : pointer to a DMA_HandleTypeDef structure that contains
  *                 the configuration information for the specified DMA Channel.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma)
{
  uint32_t tickstart = 0;
  
  /* Disable the channel */
  __HAL_DMA_DISABLE(hdma);
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  /* Check if the DMA Channel is effectively disabled */
  while((hdma->Instance->CCR & DMA_CCR_EN) != 0) 
  {
    /* Check for the Timeout */
    if( (HAL_GetTick()  - tickstart ) > HAL_TIMEOUT_DMA_ABORT)
    {
      /* Update error code */
      hdma->ErrorCode |= HAL_DMA_ERROR_TIMEOUT;
      
      /* Process Unlocked */
      __HAL_UNLOCK(hdma);
      
      /* Change the DMA state */
      hdma->State = HAL_DMA_STATE_TIMEOUT;
      
      return HAL_TIMEOUT;
    }
  }
  /* Process Unlocked */
  __HAL_UNLOCK(hdma);
  
  /* Change the DMA state*/
  hdma->State = HAL_DMA_STATE_READY; 
  
  return HAL_OK; 
}

/**
  * @brief  Polling for transfer complete.
  * @param  hdma:    pointer to a DMA_HandleTypeDef structure that contains
  *                  the configuration information for the specified DMA Channel.
  * @param  CompleteLevel: Specifies the DMA level complete.  
  * @param  Timeout:       Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, uint32_t CompleteLevel, uint32_t Timeout)
{
  uint32_t temp;
  uint32_t tickstart = 0;
  
  /* Get the level transfer complete flag */
  if(CompleteLevel == HAL_DMA_FULL_TRANSFER)
  {
    /* Transfer Complete flag */
    temp = __HAL_DMA_GET_TC_FLAG_INDEX(hdma);
  }
  else
  {
    /* Half Transfer Complete flag */
    temp = __HAL_DMA_GET_HT_FLAG_INDEX(hdma);
  }

  /* Get timeout */
  tickstart = HAL_GetTick();

  while(__HAL_DMA_GET_FLAG(hdma, temp) == RESET)
  {
    if((__HAL_DMA_GET_FLAG(hdma, __HAL_DMA_GET_TE_FLAG_INDEX(hdma)) != RESET))
    {      
      /* Clear the transfer error flags */
      __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TE_FLAG_INDEX(hdma));
      
      /* Update error code */
      SET_BIT(hdma->ErrorCode, HAL_DMA_ERROR_TE);
      
      /* Change the DMA state */
      hdma->State= HAL_DMA_STATE_ERROR;       
      
      /* Process Unlocked */
      __HAL_UNLOCK(hdma);
      
      return HAL_ERROR;      
    }      
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Update error code */
        SET_BIT(hdma->ErrorCode, HAL_DMA_ERROR_TIMEOUT);
        
        /* Change the DMA state */
        hdma->State= HAL_DMA_STATE_TIMEOUT;
        
        /* Process Unlocked */
        __HAL_UNLOCK(hdma);
      
        return HAL_TIMEOUT;
      }
    }
  }

  if(CompleteLevel == HAL_DMA_FULL_TRANSFER)
  {
    /* Clear the transfer complete flag */
    __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma));

    /* The selected Channelx EN bit is cleared (DMA is disabled and 
    all transfers are complete) */
    hdma->State = HAL_DMA_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hdma);  
  }
  else
  { 
    /* Clear the half transfer complete flag */
    __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_HT_FLAG_INDEX(hdma));

    /* The selected Channelx EN bit is cleared (DMA is disabled and 
    all transfers are complete) */
    hdma->State = HAL_DMA_STATE_READY_HALF;
    
    /* Process unlocked */
    __HAL_UNLOCK(hdma); 
  }
  
  return HAL_OK;
}
/**
  * @brief  Handles DMA interrupt request.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Channel.  
  * @retval None
  */
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma)
{        
  /* Transfer Error Interrupt management ***************************************/
  if(__HAL_DMA_GET_FLAG(hdma, __HAL_DMA_GET_TE_FLAG_INDEX(hdma)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TE) != RESET)
    {
      /* Disable the transfer error interrupt */
      __HAL_DMA_DISABLE_IT(hdma, DMA_IT_TE);
    
      /* Clear the transfer error flag */
      __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TE_FLAG_INDEX(hdma));
    
      /* Update error code */
      hdma->ErrorCode |= HAL_DMA_ERROR_TE;

      /* Change the DMA state */
      hdma->State = HAL_DMA_STATE_ERROR;    
    
      /* Process Unlocked */
      __HAL_UNLOCK(hdma); 
    
      if (hdma->XferErrorCallback != NULL)
      {
        /* Transfer error callback */
        hdma->XferErrorCallback(hdma);
      }
    }
  }

  /* Half Transfer Complete Interrupt management ******************************/
  if(__HAL_DMA_GET_FLAG(hdma, __HAL_DMA_GET_HT_FLAG_INDEX(hdma)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_HT) != RESET)
    { 
      /* Disable the half transfer interrupt if the DMA mode is not CIRCULAR */
      if((hdma->Instance->CCR & DMA_CCR_CIRC) == 0)
      {
        /* Disable the half transfer interrupt */
        __HAL_DMA_DISABLE_IT(hdma, DMA_IT_HT);
      }
      /* Clear the half transfer complete flag */
      __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_HT_FLAG_INDEX(hdma));

      /* Change DMA peripheral state */
      hdma->State = HAL_DMA_STATE_READY_HALF;

      if(hdma->XferHalfCpltCallback != NULL)
      {
        /* Half transfer callback */
        hdma->XferHalfCpltCallback(hdma);
      }
    }
  }
  
  /* Transfer Complete Interrupt management ***********************************/
  if(__HAL_DMA_GET_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
    {
      if((hdma->Instance->CCR & DMA_CCR_CIRC) == 0)
      {
        /* Disable the transfer complete interrupt */
        __HAL_DMA_DISABLE_IT(hdma, DMA_IT_TC);
      }
      /* Clear the transfer complete flag */
      __HAL_DMA_CLEAR_FLAG(hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma));
    
      /* Update error code */
      hdma->ErrorCode |= HAL_DMA_ERROR_NONE;

      /* Change the DMA state */
      hdma->State = HAL_DMA_STATE_READY;    
    
      /* Process Unlocked */
      __HAL_UNLOCK(hdma);
    
      if(hdma->XferCpltCallback != NULL)
      {       
        /* Transfer complete callback */
        hdma->XferCpltCallback(hdma);
      }
    }
  }
}  

/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group3 
 *  @brief    Peripheral State functions 
 *
@verbatim   
 ===============================================================================
                        ##### Peripheral State functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Check the DMA state
      (+) Get error code

@endverbatim
  * @{
  */  

/**
  * @brief  Returns the DMA state.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Channel.  
  * @retval HAL state
  */
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma)
{
  return hdma->State;
}

/**
  * @brief  Return the DMA error code
  * @param  hdma : pointer to a DMA_HandleTypeDef structure that contains
  *              the configuration information for the specified DMA Channel.
  * @retval DMA Error Code
  */
uint32_t HAL_DMA_GetError(DMA_HandleTypeDef *hdma)
{
  return hdma->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/  
/** @addtogroup DMA_Private_Functions DMA Private Functions
  * @{
  */
  
  /*
  * @brief  Sets the DMA Transfer parameter.
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Channel.  
  * @param  SrcAddress: The source memory Buffer address
  * @param  DstAddress: The destination memory Buffer address
  * @param  DataLength: The length of data to be transferred from source to destination
  * @retval HAL status
  */
static void DMA_SetConfig(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{  
  /* Configure DMA Channel data length */
  hdma->Instance->CNDTR = DataLength;
  
  /* Peripheral to Memory */
  if((hdma->Init.Direction) == DMA_MEMORY_TO_PERIPH)
  {   
    /* Configure DMA Channel destination address */
    hdma->Instance->CPAR = DstAddress;
    
    /* Configure DMA Channel source address */
    hdma->Instance->CMAR = SrcAddress;
  }
  /* Memory to Peripheral */
  else
  {
    /* Configure DMA Channel source address */
    hdma->Instance->CPAR = SrcAddress;
    
    /* Configure DMA Channel destination address */
    hdma->Instance->CMAR = DstAddress;
  }
}
/**
  * @}
  */

#endif /* HAL_DMA_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

