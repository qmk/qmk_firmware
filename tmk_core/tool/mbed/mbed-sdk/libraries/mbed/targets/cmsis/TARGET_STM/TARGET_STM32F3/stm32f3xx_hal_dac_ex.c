/**
  ******************************************************************************
  * @file    stm32f3xx_hal_dac_ex.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Extended DAC HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (DAC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  @verbatim   

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

#ifdef HAL_DAC_MODULE_ENABLED

/** @defgroup DACEx DAC Extended HAL module driver
  * @brief DAC HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup DACEx_Private_Functions DAC Extended Private Functions
  * @{
  */
static void DAC_DMAConvCpltCh1(DMA_HandleTypeDef *hdma);
static void DAC_DMAErrorCh1(DMA_HandleTypeDef *hdma);
static void DAC_DMAHalfConvCpltCh1(DMA_HandleTypeDef *hdma); 

#if defined(STM32F303xE) || defined(STM32F398xx)                         || \
    defined(STM32F303xC) || defined(STM32F358xx)                         || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F373xC) || defined(STM32F378xx) 
/* DAC channel 2 is available on top of DAC channel 1 */
static void DAC_DMAConvCpltCh2(DMA_HandleTypeDef *hdma);
static void DAC_DMAErrorCh2(DMA_HandleTypeDef *hdma);
static void DAC_DMAHalfConvCpltCh2(DMA_HandleTypeDef *hdma); 
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup DAC DAC HAL module driver
  * @brief DAC HAL module driver
  * @{
  */ 

/* Exported functions ---------------------------------------------------------*/
/** @addtogroup DAC_Exported_Functions DAC Exported Functions
  * @{
  */

/** @addtogroup DAC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief   	Peripheral Control functions 
 *
@verbatim   
  ==============================================================================
             ##### Peripheral Control functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Set the specified data holding register value for DAC channel.
      
@endverbatim
  * @{
  */

/**
  * @brief  Set the specified data holding register value for DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel. 
  * @param  alignment: Specifies the data alignment for DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
  *            @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
  *            @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
  * @param  data: Data to be loaded in the selected data holding register.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef* hdac, uint32_t channel, uint32_t alignment, uint32_t data)
{  
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(channel));
  assert_param(IS_DAC_ALIGN(alignment));
  assert_param(IS_DAC_DATA(data));
   
  tmp = (uint32_t) (hdac->Instance);

/* DAC 1 has 1 or 2 channels - no DAC2 */
/* DAC 1 has 2 channels 1 & 2 - DAC 2 has one channel 1 */

  if(channel == DAC_CHANNEL_1)
  {
    tmp += __HAL_DHR12R1_ALIGNEMENT(alignment);
  }
#if defined(STM32F303xE) || defined(STM32F398xx)                         || \
    defined(STM32F303xC) || defined(STM32F358xx)                         || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
  else /* channel = DAC_CHANNEL_2  */
  {
    tmp += __HAL_DHR12R2_ALIGNEMENT(alignment);
  }
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

  /* Set the DAC channel1 selected data holding register */
  *(__IO uint32_t *) tmp = data;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup DAC_Exported_Functions_Group2 Input and Output operation functions
 *  @brief    IO operation functions 
 *
@verbatim   
  ==============================================================================
             ##### IO operation functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) Start conversion and enable DMA transfer.
      (+) Stop conversion and disable DMA transfer.
      (+) Get result of conversion.
                     
@endverbatim
  * @{
  */

/* DAC 1 has 2 channels 1 & 2 - DAC 2 has one channel 1 */
#if  defined(STM32F303xE) || defined(STM32F398xx)                         || \
     defined(STM32F303xC) || defined(STM32F358xx)                         || \
     defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
     defined(STM32F373xC) || defined(STM32F378xx)
/* DAC 1 has 2 channels 1 & 2 */

/**
  * @brief  Enables DAC and starts conversion of channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 or DAC2 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef* hdac, uint32_t channel)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL_INSTANCE(hdac->Instance, channel));
  
  /* Process locked */
  __HAL_LOCK(hdac);
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;
  
  /* Enable the Peripharal */
  __HAL_DAC_ENABLE(hdac, channel);
  
  if(channel == DAC_CHANNEL_1)
  {
    /* Check if software trigger enabled */
    if(((hdac->Instance->CR & DAC_CR_TEN1) ==  DAC_CR_TEN1) && ((hdac->Instance->CR & DAC_CR_TSEL1) ==  DAC_CR_TSEL1))
    {
      /* Enable the selected DAC software conversion */
      hdac->Instance->SWTRIGR |= (uint32_t)DAC_SWTRIGR_SWTRIG1;
    }
  }
  else
  {
    /* Check if software trigger enabled */
    if(((hdac->Instance->CR & DAC_CR_TEN2) == DAC_CR_TEN2) && ((hdac->Instance->CR & DAC_CR_TSEL2) == DAC_CR_TSEL2))
    {
      /* Enable the selected DAC software conversion*/
      hdac->Instance->SWTRIGR |= (uint32_t)DAC_SWTRIGR_SWTRIG2;
    }
  }
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hdac);
    
  /* Return function status */
  return HAL_OK;
}
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || \
    defined(STM32F302xC) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/* DAC 1 has 1 channels 1 */

/**
  * @brief  Enables DAC and starts conversion of channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef* hdac, uint32_t channel)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL_INSTANCE(hdac->Instance, channel));
  
  /* Process locked */
  __HAL_LOCK(hdac);
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;
  
  /* Enable the Peripharal */
  __HAL_DAC_ENABLE(hdac, channel);
  
  /* Check if software trigger enabled */
  if(((hdac->Instance->CR & DAC_CR_TEN1) ==  DAC_CR_TEN1) && ((hdac->Instance->CR & DAC_CR_TSEL1) ==  DAC_CR_TSEL1))
  {
    /* Enable the selected DAC software conversion */
    hdac->Instance->SWTRIGR |= (uint32_t)DAC_SWTRIGR_SWTRIG1;
  }
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hdac);
    
  /* Return function status */
  return HAL_OK;
}
#endif /* STM32F302xE                               || */
       /* STM32F302xC                               || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

/* DAC 1 has 2 channels 1 & 2 - DAC 2 has one channel 1 */
#if defined(STM32F303xE) || defined(STM32F398xx)                         || \
    defined(STM32F303xC) || defined(STM32F358xx)                         || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
    
/* DAC 1 has 2 channels 1 & 2 */

/**
  * @brief  Enables DAC and starts conversion of channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected
  * @param  pData: The destination peripheral Buffer address.
  * @param  Length: The length of data to be transferred from memory to DAC peripheral
  * @param  alignment: Specifies the data alignment for DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef* hdac, uint32_t channel, uint32_t* pData, uint32_t Length, uint32_t alignment)
{
  uint32_t tmpreg = 0;
    
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL_INSTANCE(hdac->Instance, channel));
  assert_param(IS_DAC_ALIGN(alignment));
  
  /* Process locked */
  __HAL_LOCK(hdac);
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;

  if(channel == DAC_CHANNEL_1)
  {
    /* Set the DMA transfer complete callback for channel1 */
    hdac->DMA_Handle1->XferCpltCallback = DAC_DMAConvCpltCh1;
    
    /* Set the DMA half transfer complete callback for channel1 */
    hdac->DMA_Handle1->XferHalfCpltCallback = DAC_DMAHalfConvCpltCh1;
      
    /* Set the DMA error callback for channel1 */
    hdac->DMA_Handle1->XferErrorCallback = DAC_DMAErrorCh1;
  }
  else
  {
    /* Set the DMA transfer complete callback for channel2 */
    hdac->DMA_Handle2->XferCpltCallback = DAC_DMAConvCpltCh2;
    
    /* Set the DMA half transfer complete callback for channel2 */
    hdac->DMA_Handle2->XferHalfCpltCallback = DAC_DMAHalfConvCpltCh2;
       
    /* Set the DMA error callback for channel2 */
    hdac->DMA_Handle2->XferErrorCallback = DAC_DMAErrorCh2;
  }
  
 if(channel == DAC_CHANNEL_1)
  {
    /* Enable the selected DAC channel1 DMA request */
    hdac->Instance->CR |= DAC_CR_DMAEN1;
    
    /* Case of use of channel 1 */
    switch(alignment)
    {
      case DAC_ALIGN_12B_R:
        /* Get DHR12R1 address */
        tmpreg = (uint32_t)&hdac->Instance->DHR12R1;
        break;
      case DAC_ALIGN_12B_L:
        /* Get DHR12L1 address */
        tmpreg = (uint32_t)&hdac->Instance->DHR12L1;
        break;
      case DAC_ALIGN_8B_R:
        /* Get DHR8R1 address */
        tmpreg = (uint32_t)&hdac->Instance->DHR8R1;
        break;
      default:
        break;
    }
  }
  else
  {
    /* Enable the selected DAC channel2 DMA request */
    hdac->Instance->CR |= DAC_CR_DMAEN2;
    
    /* Case of use of channel 2 */
    switch(alignment)
    {
      case DAC_ALIGN_12B_R:
        /* Get DHR12R2 address */
        tmpreg = (uint32_t)&hdac->Instance->DHR12R2;
        break;
      case DAC_ALIGN_12B_L:
        /* Get DHR12L2 address */
        tmpreg = (uint32_t)&hdac->Instance->DHR12L2;
        break;
      case DAC_ALIGN_8B_R:
        /* Get DHR8R2 address */
        tmpreg = (uint32_t)&hdac->Instance->DHR8R2;
        break;
      default:
        break;
    }
  }
  
  /* Enable the DMA Channel */
  if(channel == DAC_CHANNEL_1)
  {
    /* Enable the DAC DMA underrun interrupt */
    __HAL_DAC_ENABLE_IT(hdac, DAC_IT_DMAUDR1);

    /* Enable the DMA Channel */
    HAL_DMA_Start_IT(hdac->DMA_Handle1, (uint32_t)pData, tmpreg, Length);
  } 
  else
  {
    /* Enable the DAC DMA underrun interrupt */
    __HAL_DAC_ENABLE_IT(hdac, DAC_IT_DMAUDR2);

    /* Enable the DMA Channel */
    HAL_DMA_Start_IT(hdac->DMA_Handle2, (uint32_t)pData, tmpreg, Length);
  }
 
  /* Enable the Peripheral */
  __HAL_DAC_ENABLE(hdac, channel);
  
  /* Process Unlocked */
  __HAL_UNLOCK(hdac);
  
  /* Return function status */
  return HAL_OK;
}
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || \
    defined(STM32F302xC) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/* DAC 1 has 1 channels 1 */

/**
  * @brief  Enables DAC and starts conversion of channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  * @param  pData: The destination peripheral Buffer address.
  * @param  Length: The length of data to be transferred from memory to DAC peripheral
  * @param  alignment: Specifies the data alignment for DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef* hdac, uint32_t channel, uint32_t* pData, uint32_t Length, uint32_t alignment)
{
  uint32_t tmpreg = 0;
    
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL_INSTANCE(hdac->Instance, channel));
  assert_param(IS_DAC_ALIGN(alignment));
  
  /* Process locked */
  __HAL_LOCK(hdac);
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;
    
  /* Set the DMA transfer complete callback for channel1 */
  hdac->DMA_Handle1->XferCpltCallback = DAC_DMAConvCpltCh1;
  
  /* Set the DMA half transfer complete callback for channel1 */
  hdac->DMA_Handle1->XferHalfCpltCallback = DAC_DMAHalfConvCpltCh1;
    
  /* Set the DMA error callback for channel1 */
  hdac->DMA_Handle1->XferErrorCallback = DAC_DMAErrorCh1;

  /* Enable the selected DAC channel1 DMA request */
  hdac->Instance->CR |= DAC_CR_DMAEN1;
    
  /* Case of use of channel 1 */
  switch(alignment)
  {
    case DAC_ALIGN_12B_R:
      /* Get DHR12R1 address */
      tmpreg = (uint32_t)&hdac->Instance->DHR12R1;
      break;
    case DAC_ALIGN_12B_L:
      /* Get DHR12L1 address */
      tmpreg = (uint32_t)&hdac->Instance->DHR12L1;
      break;
    case DAC_ALIGN_8B_R:
      /* Get DHR8R1 address */
      tmpreg = (uint32_t)&hdac->Instance->DHR8R1;
      break;
    default:
      break;
  }
  
  /* Enable the DMA Channel */
  /* Enable the DAC DMA underrun interrupt */
  __HAL_DAC_ENABLE_IT(hdac, DAC_IT_DMAUDR1);

  /* Enable the DMA Channel */
  HAL_DMA_Start_IT(hdac->DMA_Handle1, (uint32_t)pData, tmpreg, Length);
 
  /* Enable the Peripheral */
  __HAL_DAC_ENABLE(hdac, channel);
  
  /* Process Unlocked */
  __HAL_UNLOCK(hdac);
  
  /* Return function status */
  return HAL_OK;
}
#endif /* STM32F302xE                               || */
       /* STM32F302xC                               || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

/* DAC 1 has 2 channels 1 & 2 - DAC 2 has one channel 1 */
#if  defined(STM32F303xE) || defined(STM32F398xx)                         || \
     defined(STM32F303xC) || defined(STM32F358xx)                         || \
     defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
     defined(STM32F373xC) || defined(STM32F378xx)
     
/* DAC 1 has 2 channels 1 & 2 */

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 or DAC2 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected
  * @retval The selected DAC channel data output value.
  */


/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected
  * @retval The selected DAC channel data output value.
  */
uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef* hdac, uint32_t channel)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL_INSTANCE(hdac->Instance, channel));
  
  /* Returns the DAC channel data output register value */
  if(channel == DAC_CHANNEL_1) 
  {
    return hdac->Instance->DOR1;
  }
  else /* channel = DAC_CHANNEL_2  */
  {
    return hdac->Instance->DOR2;
  }
}

#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || \
    defined(STM32F302xC) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/* DAC 1 has 1 channel (channel 1)  */
/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  * @retval The selected DAC channel data output value.
  */
uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef* hdac, uint32_t channel)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL_INSTANCE(hdac->Instance, channel));
  
  /* Returns the DAC channel data output register value */
  return hdac->Instance->DOR1;
}
#endif /* STM32F302xE                               || */
       /* STM32F302xC                               || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F302xE) || \
    defined(STM32F302xC) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/* DAC channel 2 is NOT available. Only DAC channel 1 is available */

/**
  * @brief  Handles DAC interrupt request  
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */

void HAL_DAC_IRQHandler(struct __DAC_HandleTypeDef* hdac)
{
  /* Check Overrun flag */
  if(__HAL_DAC_GET_FLAG(hdac, DAC_FLAG_DMAUDR1))
  {
    /* Change DAC state to error state */
    hdac->State = HAL_DAC_STATE_ERROR;
    
    /* Set DAC error code to chanel1 DMA underrun error */
    hdac->ErrorCode |= HAL_DAC_ERROR_DMAUNDERRUNCH1;
    
    /* Clear the underrun flag */
    __HAL_DAC_CLEAR_FLAG(hdac,DAC_FLAG_DMAUDR1);
    
    /* Disable the selected DAC channel1 DMA request */
    hdac->Instance->CR &= ~DAC_CR_DMAEN1;
    
    /* Error callback */ 
    HAL_DAC_DMAUnderrunCallbackCh1(hdac);
  }
}
#endif /* STM32F302xE                               || */
       /* STM32F302xC                               || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if  defined(STM32F303xE) || defined(STM32F398xx)                         || \
     defined(STM32F303xC) || defined(STM32F358xx)                         || \
     defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
     defined(STM32F373xC) || defined(STM32F378xx)
/* DAC channel 2 is available on top of DAC channel 1 */

/**
  * @brief  Handles DAC interrupt request  
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
void HAL_DAC_IRQHandler(struct __DAC_HandleTypeDef* hdac)
{
  /* Check Overrun flag */
  if(__HAL_DAC_GET_FLAG(hdac, DAC_FLAG_DMAUDR1))
  {
    /* Change DAC state to error state */
    hdac->State = HAL_DAC_STATE_ERROR;
    
    /* Set DAC error code to chanel1 DMA underrun error */
    hdac->ErrorCode |= HAL_DAC_ERROR_DMAUNDERRUNCH1;
    
    /* Clear the underrun flag */
    __HAL_DAC_CLEAR_FLAG(hdac,DAC_FLAG_DMAUDR1);
    
    /* Disable the selected DAC channel1 DMA request */
    hdac->Instance->CR &= ~DAC_CR_DMAEN1;
    
    /* Error callback */ 
    HAL_DAC_DMAUnderrunCallbackCh1(hdac);
  }
  else
  {
    if (__HAL_DAC_GET_FLAG(hdac, DAC_FLAG_DMAUDR2))
    {
      /* Change DAC state to error state */
      hdac->State = HAL_DAC_STATE_ERROR;
    
      /* Set DAC error code to channel2 DMA underrun error */
      hdac->ErrorCode |= HAL_DAC_ERROR_DMAUNDERRUNCH2;
    
      /* Clear the underrun flag */
      __HAL_DAC_CLEAR_FLAG(hdac,DAC_FLAG_DMAUDR2);
    
      /* Disable the selected DAC channel1 DMA request */
      hdac->Instance->CR &= ~DAC_CR_DMAEN2;
    
      /* Error callback */ 
      HAL_DACEx_DMAUnderrunCallbackCh2(hdac);
    }
  }
}
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup DACEx
  * @brief DACEx Extended HAL module driver
  * @{
  */
/* Exported functions ---------------------------------------------------------*/

/** @addtogroup DACEx_Exported_Functions DAC Extended Exported Functions
  * @{
  */

#if  defined(STM32F303xE) || defined(STM32F398xx)                         || \
     defined(STM32F303xC) || defined(STM32F358xx)                         || \
     defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
     defined(STM32F373xC) || defined(STM32F378xx)
/* DAC channel 2 is present in DAC 1 */
/**
  * @brief  Set the specified data holding register value for dual DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  alignment: Specifies the data alignment for dual channel DAC.
  *          This parameter can be one of the following values:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @param  data2: Data for DAC Channel2 to be loaded in the selected data holding register.
  * @param  data1: Data for DAC Channel1 to be loaded in the selected data  holding register.
  * @note   In dual mode, a unique register access is required to write in both
  *          DAC channels at the same time.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef* hdac, uint32_t alignment, uint32_t data1, uint32_t data2)
{
  uint32_t data = 0, tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(alignment));
  assert_param(IS_DAC_DATA(data1));
  assert_param(IS_DAC_DATA(data2));

  /* Calculate and set dual DAC data holding register value */
  if (alignment == DAC_ALIGN_8B_R)
  {
    data = ((uint32_t)data2 << 8) | data1;
  }
  else
  {
    data = ((uint32_t)data2 << 16) | data1;
  }

    tmp = (uint32_t) (hdac->Instance);
    tmp += __HAL_DHR12RD_ALIGNEMENT(alignment);

  /* Set the dual DAC selected data holding register */
  *(__IO uint32_t *)tmp = data;

  /* Return function status */
  return HAL_OK;
}
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval The selected DAC channel data output value.
  */
uint32_t HAL_DACEx_DualGetValue(DAC_HandleTypeDef* hdac)
{
  uint32_t tmp = 0;

  tmp |= hdac->Instance->DOR1;

#if  defined(STM32F303xE) || defined(STM32F398xx)                         || \
     defined(STM32F303xC) || defined(STM32F358xx)                         || \
     defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
     defined(STM32F373xC) || defined(STM32F378xx)
/* DAC channel 2 is present in DAC 1 */
  tmp |= hdac->Instance->DOR2 << 16;
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

  /* Returns the DAC channel data output register value */
  return tmp;
}

/**
  * @brief  Enables or disables the selected DAC channel wave generation.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected
  * @param  Amplitude: Select max triangle amplitude.
  *          This parameter can be one of the following values:
  *            @arg DAC_TRIANGLEAMPLITUDE_1: Select max triangle amplitude of 1
  *            @arg DAC_TRIANGLEAMPLITUDE_3: Select max triangle amplitude of 3
  *            @arg DAC_TRIANGLEAMPLITUDE_7: Select max triangle amplitude of 7
  *            @arg DAC_TRIANGLEAMPLITUDE_15: Select max triangle amplitude of 15
  *            @arg DAC_TRIANGLEAMPLITUDE_31: Select max triangle amplitude of 31
  *            @arg DAC_TRIANGLEAMPLITUDE_63: Select max triangle amplitude of 63
  *            @arg DAC_TRIANGLEAMPLITUDE_127: Select max triangle amplitude of 127
  *            @arg DAC_TRIANGLEAMPLITUDE_255: Select max triangle amplitude of 255
  *            @arg DAC_TRIANGLEAMPLITUDE_511: Select max triangle amplitude of 511
  *            @arg DAC_TRIANGLEAMPLITUDE_1023: Select max triangle amplitude of 1023
  *            @arg DAC_TRIANGLEAMPLITUDE_2047: Select max triangle amplitude of 2047
  *            @arg DAC_TRIANGLEAMPLITUDE_4095: Select max triangle amplitude of 4095
  * @note   Wave generation is not available in DAC2.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef* hdac, uint32_t channel, uint32_t Amplitude)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(channel));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));

  /* Process locked */
  __HAL_LOCK(hdac);

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;

  /* Enable the selected wave generation for the selected DAC channel */
  hdac->Instance->CR |= (DAC_WAVE_TRIANGLE | Amplitude) << channel;

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdac);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Enables or disables the selected DAC channel wave generation.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  channel: The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC1 Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC1 Channel2 selected
  * @param  Amplitude: Unmask DAC channel LFSR for noise wave generation.
  *          This parameter can be one of the following values:
  *            @arg DAC_LFSRUNMASK_BIT0: Unmask DAC channel LFSR bit0 for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS1_0: Unmask DAC channel LFSR bit[1:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS2_0: Unmask DAC channel LFSR bit[2:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS3_0: Unmask DAC channel LFSR bit[3:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS4_0: Unmask DAC channel LFSR bit[4:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS5_0: Unmask DAC channel LFSR bit[5:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS6_0: Unmask DAC channel LFSR bit[6:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS7_0: Unmask DAC channel LFSR bit[7:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS8_0: Unmask DAC channel LFSR bit[8:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS9_0: Unmask DAC channel LFSR bit[9:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS10_0: Unmask DAC channel LFSR bit[10:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS11_0: Unmask DAC channel LFSR bit[11:0] for noise wave generation
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef* hdac, uint32_t channel, uint32_t Amplitude)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(channel));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));

  /* Process locked */
  __HAL_LOCK(hdac);

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;

  /* Enable the selected wave generation for the selected DAC channel */
  hdac->Instance->CR |= (DAC_WAVE_NOISE | Amplitude) << channel;

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdac);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Conversion complete callback in non blocking mode for Channel2
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef* hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DACEx_ConvCpltCallbackCh2 could be implemented in the user file
   */
}

/**
  * @brief  Conversion half DMA transfer callback in non blocking mode for Channel2
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DACEx_ConvHalfCpltCallbackCh2(DAC_HandleTypeDef* hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DACEx_ConvHalfCpltCallbackCh2 could be implemented in the user file
   */
}

/**
  * @brief  Error DAC callback for Channel2.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DACEx_ErrorCallbackCh2(DAC_HandleTypeDef *hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DACEx_ErrorCallbackCh2 could be implemented in the user file
   */
}

/**
  * @brief  DMA underrun DAC callback for channel2.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DACEx_DMAUnderrunCallbackCh2(DAC_HandleTypeDef *hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DACEx_DMAUnderrunCallbackCh2 could be implemented in the user file
   */
}

/**
  * @brief  DMA conversion complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void DAC_DMAConvCpltCh1(DMA_HandleTypeDef *hdma)   
{
  DAC_HandleTypeDef* hdac = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  HAL_DAC_ConvCpltCallbackCh1(hdac); 
  
  hdac->State= HAL_DAC_STATE_READY;
}

/**
  * @brief  DMA half transfer complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void DAC_DMAHalfConvCpltCh1(DMA_HandleTypeDef *hdma)   
{
    DAC_HandleTypeDef* hdac = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
    /* Conversion complete callback */
    HAL_DAC_ConvHalfCpltCallbackCh1(hdac); 
}

/**
  * @brief  DMA error callback 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void DAC_DMAErrorCh1(DMA_HandleTypeDef *hdma)   
{
  DAC_HandleTypeDef* hdac = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
    
  /* Set DAC error code to DMA error */
  hdac->ErrorCode |= HAL_DAC_ERROR_DMA;
    
  HAL_DAC_ErrorCallbackCh1(hdac); 
    
  hdac->State= HAL_DAC_STATE_READY;
}

#if  defined(STM32F303xE) || defined(STM32F398xx)                         || \
     defined(STM32F303xC) || defined(STM32F358xx)                         || \
     defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
     defined(STM32F373xC) || defined(STM32F378xx)
/* DAC channel 2 is available on top of DAC channel 1 */

/**
  * @brief  DMA conversion complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void DAC_DMAConvCpltCh2(DMA_HandleTypeDef *hdma)   
{
  DAC_HandleTypeDef* hdac = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  HAL_DACEx_ConvCpltCallbackCh2(hdac);
  
  hdac->State= HAL_DAC_STATE_READY;
}

/**
  * @brief  DMA half transfer complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void DAC_DMAHalfConvCpltCh2(DMA_HandleTypeDef *hdma)   
{
    DAC_HandleTypeDef* hdac = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
    /* Conversion complete callback */
    HAL_DACEx_ConvHalfCpltCallbackCh2(hdac);
}

/**
  * @brief  DMA error callback 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void DAC_DMAErrorCh2(DMA_HandleTypeDef *hdma)   
{
  DAC_HandleTypeDef* hdac = ( DAC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
    
  /* Set DAC error code to DMA error */
  hdac->ErrorCode |= HAL_DAC_ERROR_DMA;
    
  HAL_DACEx_ErrorCallbackCh2(hdac);
    
  hdac->State= HAL_DAC_STATE_READY;
}
#endif /* STM32F303xE || STM32F398xx                || */
       /* STM32F303xC || STM32F358xx                || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F373xC || STM32F378xx                   */

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_DAC_MODULE_ENABLED */
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
