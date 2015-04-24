/**
  ******************************************************************************
  * @file    stm32l1xx_hal_adc_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of conversions of regular
  *             group, using 3 possible modes: polling, interruption or DMA.
  *           + Control functions
  *             ++ Analog Watchdog configuration
  *             ++ Channels configuration on regular group
  *           + State functions
  *             ++ ADC state machine management
  *             ++ Interrupts and flags management
  *          Other functions (generic functions) are available in file 
  *          "stm32l1xx_hal_adc.c".
  *
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]

     (#) Activate the ADC peripheral using one of the start functions: 
         HAL_ADCEx_InjectedStart(), HAL_ADCEx_InjectedStart_IT().
    
     *** Channels configuration to injected group ***
     ================================================    
     [..]
       (+) To configure the ADC Injected channels group features, use 
           HAL_ADCEx_InjectedConfigChannel() functions.
       (+) To activate the continuous mode, use the HAL_ADC_Init() function.
       (+) To read the ADC converted values, use the HAL_ADCEx_InjectedGetValue() 
           function.
  
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

/** @defgroup ADCEx ADCEx
  * @brief ADC HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ADCEx_Private_Constants ADCEx Private Constants
  * @{
  */

  /* ADC conversion cycles (unit: ADC clock cycles)                           */
  /* (selected sampling time + conversion time of 12 ADC clock cycles, with   */
  /* resolution 12 bits)                                                      */
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_4CYCLE5   ((uint32_t) 16)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_9CYCLES   ((uint32_t) 21)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_16CYCLES  ((uint32_t) 28)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_24CYCLES  ((uint32_t) 36)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_48CYCLES  ((uint32_t) 60)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_96CYCLES  ((uint32_t)108)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_192CYCLES ((uint32_t)204)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_384CYCLES ((uint32_t)396)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Functions ADCEx Exported Functions
  * @{
  */

/** @defgroup ADCEx_Exported_Functions_Group1 Extended Initialization/de-initialization functions 
 *  @brief    Extended Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start conversion of injected group.
      (+) Stop conversion of injected group.
      (+) Poll for conversion complete on injected group.
      (+) Get result of injected channel conversion.
      (+) Start conversion of injected group and enable interruptions.
      (+) Stop conversion of injected group and disable interruptions.
      
@endverbatim
  * @{
  */

/**
  * @brief  Enables ADC, starts conversion of injected group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Check if a regular conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_REG)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ;
    }
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);
    
    /* Start conversion of injected group if software start has been selected */
    /* and if automatic injected conversion is disabled.                      */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* If automatic injected conversion is enabled, conversion will start     */
    /* after next regular group conversion.                                   */
    if (__HAL_ADC_IS_SOFTWARE_START_INJECTED(hadc)        && 
        HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO)  )
    {
      /* Enable ADC software conversion for injected channels */
      SET_BIT(hadc->Instance->CR2, ADC_CR2_JSWSTART);
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Stop conversion of injected channels. Disable ADC peripheral if
  *         no regular conversion is on going.
  * @note   If ADC must be disabled with this function and if regular conversion
  *         is on going, function HAL_ADC_Stop must be used preliminarily.
  * @note   In case of auto-injection mode, HAL_ADC_Stop must be used.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Stop potential conversion and disable ADC peripheral                     */
  /* Conditioned to:                                                          */
  /* - No conversion on the other group (regular group) is intended to        */
  /*   continue (injected and regular groups stop conversion and ADC disable  */
  /*   are common)                                                            */
  /* - In case of auto-injection mode, HAL_ADC_Stop must be used.             */
    if((hadc->State != HAL_ADC_STATE_BUSY_REG)            &&
       (hadc->State != HAL_ADC_STATE_BUSY_INJ_REG)        &&
       HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO)   )
  {
    /* Stop potential conversion on going, on regular and injected groups */
    /* Disable ADC peripheral */
    tmpHALStatus = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
      
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Wait for injected group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Variables for polling in case of scan mode enabled and polling for each  */
  /* conversion.                                                              */
  /* Note: Variable "conversion_timeout_cpu_cycles" set to offset 28 CPU      */
  /* cycles to compensate number of CPU cycles for processing of variable     */
  /* "conversion_timeout_cpu_cycles_max"                                      */
  uint32_t conversion_timeout_cpu_cycles = 28;
  uint32_t conversion_timeout_cpu_cycles_max = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Get timeout */
  tickstart = HAL_GetTick();  
     
  /* Polling for end of conversion: differentiation if single/sequence        */
  /* conversion.                                                              */
  /* For injected group, flag JEOC is set only at the end of the sequence,    */
  /* not for each conversion within the sequence.                             */
  /* If setting "EOCSelection" is set to poll for each single conversion,     */
  /* management of polling depends on setting of injected group sequencer:    */ 
  /*  - If single conversion for injected group (scan mode disabled or        */
  /*    InjectedNbrOfConversion ==1), flag JEOC is used to determine the      */
  /*    conversion completion.                                                */
  /*  - If sequence conversion for injected group (scan mode enabled and      */
  /*    InjectedNbrOfConversion >=2), flag JEOC is set only at the end of the */
  /*    sequence.                                                             */
  /*    To poll for each conversion, the maximum conversion time is computed  */
  /*    from ADC conversion time (selected sampling time + conversion time of */
  /*    12 ADC clock cycles) and APB2/ADC clock prescalers (depending on      */
  /*    settings, conversion time range can vary from 8 to several thousands  */
  /*    of CPU cycles).                                                       */

  /* Note: On STM32L1, setting "EOCSelection" is related to regular group     */
  /*       only, by hardware. For compatibility with other STM32 devices,     */
  /*       this setting is related also to injected group by software.        */
  if (((hadc->Instance->JSQR & ADC_JSQR_JL) == RESET) ||
      (hadc->Init.EOCSelection != EOC_SINGLE_CONV)      )
  {
    /* Wait until End of Conversion flag is raised */
    while(HAL_IS_BIT_CLR(hadc->Instance->SR, ADC_FLAG_JEOC))
    {
      /* Check if timeout is disabled (set to infinite wait) */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Update ADC state machine to timeout */
          hadc->State = HAL_ADC_STATE_TIMEOUT;
          
          /* Process unlocked */
          __HAL_UNLOCK(hadc);
          
          return HAL_ERROR;
        }
      }
    }
  }
  else
  {
    /* Computation of CPU cycles corresponding to ADC conversion cycles.      */
    /* Retrieve ADC clock prescaler and ADC maximum conversion cycles on all  */
    /* channels.                                                              */
    conversion_timeout_cpu_cycles_max = __ADC_GET_CLOCK_PRESCALER_DECIMAL(hadc);
    conversion_timeout_cpu_cycles_max *= __ADC_CONVCYCLES_MAX_RANGE(hadc);

    /* Poll with maximum conversion time */
    while(conversion_timeout_cpu_cycles < conversion_timeout_cpu_cycles_max)
    {
      /* Check if timeout is disabled (set to infinite wait) */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Update ADC state machine to timeout */
          hadc->State = HAL_ADC_STATE_TIMEOUT;

          /* Process unlocked */
          __HAL_UNLOCK(hadc);
          
          return HAL_ERROR;
        }
      }
      conversion_timeout_cpu_cycles ++;
    }
  }
  
  /* Clear end of conversion flag of injected group if low power feature      */
  /* "Auto Wait" is disabled, to not interfere with this feature until data   */
  /* register is read using function HAL_ADCEx_InjectedGetValue().            */
  if (hadc->Init.LowPowerAutoWait == DISABLE)
  {
    /* Clear injected group conversion flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JSTRT | ADC_FLAG_JEOC);
  }
  
  /* Update state machine on conversion status if not in error state */
  if(hadc->State != HAL_ADC_STATE_ERROR)
  {
    /* Update ADC state machine */
    if(hadc->State != HAL_ADC_STATE_EOC_INJ_REG)
    {

      if(hadc->State == HAL_ADC_STATE_EOC_REG)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
      }
      else
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_INJ;
      }
    }
  }
      
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Enables ADC, starts conversion of injected group with interruption.
  *         Interruptions enabled in this function: JEOC (end of conversion).
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Check if a regular conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_REG)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ;
    }
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);
    
    /* Enable end of conversion interrupt for injected channels */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOC);
    
    /* Start conversion of injected group if software start has been selected */
    /* and if automatic injected conversion is disabled.                      */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* If automatic injected conversion is enabled, conversion will start     */
    /* after next regular group conversion.                                   */
    if (__HAL_ADC_IS_SOFTWARE_START_INJECTED(hadc)        && 
        HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO)  )
    {
      /* Enable ADC software conversion for injected channels */
      SET_BIT(hadc->Instance->CR2, ADC_CR2_JSWSTART);
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Stop conversion of injected channels, disable interruption of 
  *         end-of-conversion. Disable ADC peripheral if no regular conversion
  *         is on going.
  * @note   If ADC must be disabled with this function and if regular conversion
  *         is on going, function HAL_ADC_Stop must be used preliminarily.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Stop potential conversion and disable ADC peripheral                     */
  /* Conditioned to:                                                          */
  /* - No conversion on the other group (regular group) is intended to        */
  /*   continue (injected and regular groups stop conversion and ADC disable  */
  /*   are common)                                                            */
  /* - In case of auto-injection mode, HAL_ADC_Stop must be used.             */ 
    if((hadc->State != HAL_ADC_STATE_BUSY_REG)            &&
       (hadc->State != HAL_ADC_STATE_BUSY_INJ_REG)        &&
       HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO)   )
  {
    /* Stop potential conversion on going, on regular and injected groups */
    /* Disable ADC peripheral */
    tmpHALStatus = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Disable ADC end of conversion interrupt for injected channels */
      __HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOC);
      
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
      
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Get ADC injected group conversion result.
  * @param  hadc: ADC handle
  * @param  InjectedRank: the converted ADC injected rank.
  *          This parameter can be one of the following values:
  *            @arg ADC_INJECTED_RANK_1: Injected Channel1 selected
  *            @arg ADC_INJECTED_RANK_2: Injected Channel2 selected
  *            @arg ADC_INJECTED_RANK_3: Injected Channel3 selected
  *            @arg ADC_INJECTED_RANK_4: Injected Channel4 selected
  * @retval None
  */
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank)
{
  uint32_t tmp_jdr = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_INJECTED_RANK(InjectedRank));
   
  /* Clear injected group conversion flag to have similar behaviour as         */
  /* regular group: reading data register also clears end of conversion flag. */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);
  
  /* Get ADC converted value */ 
  switch(InjectedRank)
  {  
    case ADC_INJECTED_RANK_4: 
      tmp_jdr = hadc->Instance->JDR4;
      break;
    case ADC_INJECTED_RANK_3: 
      tmp_jdr = hadc->Instance->JDR3;
      break;
    case ADC_INJECTED_RANK_2: 
      tmp_jdr = hadc->Instance->JDR2;
      break;
    case ADC_INJECTED_RANK_1:
    default:
      tmp_jdr = hadc->Instance->JDR1;
      break;
  }
  
  /* Return ADC converted value */ 
  return tmp_jdr;
}

/**
  * @brief  Injected conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADCEx_InjectedConvCpltCallback could be implemented in the user file
  */
}

/**
  * @}
  */

/** @defgroup ADCEx_Exported_Functions_Group2 Extended Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim   
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels on injected group
      
@endverbatim
  * @{
  */

/**
  * @brief  Configures the ADC injected group and the selected channel to be
  *         linked to the injected group.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes injected group, following calls to this 
  *         function can be used to reconfigure some parameters of structure
  *         "ADC_InjectionConfTypeDef" on the fly, without reseting the ADC.
  *         The setting of these parameters is conditioned to ADC state: 
  *         this function must be called when ADC is not under conversion.
  * @param  hadc: ADC handle
  * @param  sConfigInjected: Structure of ADC injected group and ADC channel for
  *         injected group.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc, ADC_InjectionConfTypeDef* sConfigInjected)
{   
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CHANNEL(sConfigInjected->InjectedChannel));
  assert_param(IS_ADC_SAMPLE_TIME(sConfigInjected->InjectedSamplingTime));
  assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->AutoInjectedConv));
  assert_param(IS_ADC_EXTTRIGINJEC(sConfigInjected->ExternalTrigInjecConv));
  assert_param(IS_ADC_RANGE(sConfigInjected->InjectedOffset));
  
  if(hadc->Init.ScanConvMode != ADC_SCAN_DISABLE)
  {
    assert_param(IS_ADC_INJECTED_RANK(sConfigInjected->InjectedRank));
    assert_param(IS_ADC_INJECTED_NB_CONV(sConfigInjected->InjectedNbrOfConversion));
    assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->InjectedDiscontinuousConvMode));
  }
  
  if(sConfigInjected->ExternalTrigInjecConvEdge != ADC_INJECTED_SOFTWARE_START)
  {
    assert_param(IS_ADC_EXTTRIGINJEC_EDGE(sConfigInjected->ExternalTrigInjecConvEdge));
  }
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Configuration of injected group sequencer:                               */
  /* - if scan mode is disabled, injected channels sequence length is set to  */
  /*   0x00: 1 channel converted (channel on regular rank 1)                  */
  /*   Parameter "InjectedNbrOfConversion" is discarded.                      */
  /*   Note: Scan mode is present by hardware on this device and, if          */
  /*   disabled, discards automatically nb of conversions. Anyway, nb of      */
  /*   conversions is forced to 0x00 for alignment over all STM32 devices.    */
  /* - if scan mode is enabled, injected channels sequence length is set to   */
  /*   parameter ""InjectedNbrOfConversion".                                  */
  if (hadc->Init.ScanConvMode == ADC_SCAN_DISABLE)
  {
    if (sConfigInjected->InjectedRank == ADC_INJECTED_RANK_1)
    {
      /* Clear the old SQx bits for all injected ranks */
        MODIFY_REG(hadc->Instance->JSQR                           ,
                   ADC_JSQR_JL   |
                   ADC_JSQR_JSQ4 |
                   ADC_JSQR_JSQ3 |
                   ADC_JSQR_JSQ2 |
                   ADC_JSQR_JSQ1                                  ,
                   __ADC_JSQR_RK(sConfigInjected->InjectedChannel,
                                 ADC_INJECTED_RANK_1,
                                 0x01)                             );
    }
    /* If another injected rank than rank1 was intended to be set, and could  */
    /* not due to ScanConvMode disabled, error is reported.                   */
    else
    {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
    }
  }
  else
  {   
    /* Since injected channels rank conv. order depends on total number of   */
    /* injected conversions, selected rank must be below or equal to total   */
    /* number of injected conversions to be updated.                         */
    if (sConfigInjected->InjectedRank <= sConfigInjected->InjectedNbrOfConversion)
    {
      /* Clear the old SQx bits for the selected rank */
      /* Set the SQx bits for the selected rank */
      MODIFY_REG(hadc->Instance->JSQR                                                 ,
                 
                 ADC_JSQR_JL                                            |
                 __ADC_JSQR_RK(ADC_JSQR_JSQ1,                         
                               sConfigInjected->InjectedRank,         
                               sConfigInjected->InjectedNbrOfConversion)              ,
                 
                 __ADC_JSQR_JL(sConfigInjected->InjectedNbrOfConversion) |
                 __ADC_JSQR_RK(sConfigInjected->InjectedChannel,      
                                             sConfigInjected->InjectedRank,         
                                             sConfigInjected->InjectedNbrOfConversion) );
    }
    else
    {
      /* Clear the old SQx bits for the selected rank */
      MODIFY_REG(hadc->Instance->JSQR                                    ,
                 
                 ADC_JSQR_JL                                            |
                 __ADC_JSQR_RK(ADC_JSQR_JSQ1,                         
                               sConfigInjected->InjectedRank,         
                               sConfigInjected->InjectedNbrOfConversion) ,
                 
                 0x00000000                                               );
    }
  } 
    
  /* Enable external trigger if trigger selection is different of software    */
  /* start.                                                                   */
  /* Note: This configuration keeps the hardware feature of parameter         */
  /*       ExternalTrigConvEdge "trigger edge none" equivalent to             */
  /*       software start.                                                    */
  
  if (sConfigInjected->ExternalTrigInjecConv != ADC_INJECTED_SOFTWARE_START)
  {    
    MODIFY_REG(hadc->Instance->CR2                        ,
               ADC_CR2_JEXTEN  |
               ADC_CR2_JEXTSEL                            ,
               sConfigInjected->ExternalTrigInjecConv    |
               sConfigInjected->ExternalTrigInjecConvEdge  );
  }
  else
  {
    MODIFY_REG(hadc->Instance->CR2,
               ADC_CR2_JEXTEN  |
               ADC_CR2_JEXTSEL    ,
               0x00000000          );
  }

  /* Configuration of injected group                                          */
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated only when ADC is disabled:                */
  /*  - Automatic injected conversion                                         */
  /*  - Injected discontinuous mode                                           */
  if ((__HAL_ADC_IS_ENABLED(hadc) == RESET))
  {
    hadc->Instance->CR1 &= ~(ADC_CR1_JAUTO   |
                             ADC_CR1_JDISCEN  );
    
    /* Automatic injected conversion can be enabled if injected group         */
    /* external triggers are disabled.                                        */
    if (sConfigInjected->AutoInjectedConv == ENABLE)
    {
      if (sConfigInjected->ExternalTrigInjecConv == ADC_INJECTED_SOFTWARE_START)
      {
        SET_BIT(hadc->Instance->CR1, ADC_CR1_JAUTO);
      }
      else
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
      }
    }
    
    /* Injected discontinuous can be enabled only if auto-injected mode is    */
    /* disabled.                                                              */  
    if (sConfigInjected->InjectedDiscontinuousConvMode == ENABLE)
    {
      if (sConfigInjected->AutoInjectedConv == DISABLE)
      {
        SET_BIT(hadc->Instance->CR1, ADC_CR1_JDISCEN);
      } 
      else
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
      }
    }
  }

  /* InjectedChannel sampling time configuration */
  /* For InjectedChannels 0 to 9 */
  if (sConfigInjected->InjectedChannel < ADC_CHANNEL_10)
  {
    MODIFY_REG(hadc->Instance->SMPR3,
               __ADC_SMPR3(ADC_SMPR3_SMP0, sConfigInjected->InjectedChannel),
               __ADC_SMPR3(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel) );
  }
  /* For InjectedChannels 10 to 19 */
  else if (sConfigInjected->InjectedChannel < ADC_CHANNEL_20)
  {
    MODIFY_REG(hadc->Instance->SMPR2,
               __ADC_SMPR2(ADC_SMPR2_SMP10, sConfigInjected->InjectedChannel),
               __ADC_SMPR2(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel) );
  }
  /* For InjectedChannels 20 to 26 for devices Cat.1, Cat.2, Cat.3 */
  /* For InjectedChannels 20 to 29 for devices Cat4, Cat.5 */
  else if (sConfigInjected->InjectedChannel <= ADC_SMPR1_CHANNEL_MAX)
  {   
    MODIFY_REG(hadc->Instance->SMPR1,
               __ADC_SMPR1(ADC_SMPR1_SMP20, sConfigInjected->InjectedChannel),
               __ADC_SMPR1(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel) );
  }
  /* For InjectedChannels 30 to 31 for devices Cat4, Cat.5 */
  else
  {
    __ADC_SMPR0_CHANNEL_SET(hadc, sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel);
  }
  
  
  /* Configure the offset: offset enable/disable, InjectedChannel, offset value */
  switch(sConfigInjected->InjectedRank)
  {
    case 1:
      /* Set injected channel 1 offset */     
      MODIFY_REG(hadc->Instance->JOFR1,
                 ADC_JOFR1_JOFFSET1,
                 sConfigInjected->InjectedOffset);
      break;
    case 2:
      /* Set injected channel 2 offset */
      MODIFY_REG(hadc->Instance->JOFR2,
                 ADC_JOFR2_JOFFSET2,
                 sConfigInjected->InjectedOffset);
      break;
    case 3:
      /* Set injected channel 3 offset */
      MODIFY_REG(hadc->Instance->JOFR3,
                 ADC_JOFR3_JOFFSET3,
                 sConfigInjected->InjectedOffset);
      break;
    case 4:
    default:
      MODIFY_REG(hadc->Instance->JOFR4,
                 ADC_JOFR4_JOFFSET4,
                 sConfigInjected->InjectedOffset);
      break;
  }
  
  /* If ADC1 Channel_16 or Channel_17 is selected, enable Temperature sensor  */
  /* and VREFINT measurement path.                                            */
  if ((sConfigInjected->InjectedChannel == ADC_CHANNEL_TEMPSENSOR) ||
      (sConfigInjected->InjectedChannel == ADC_CHANNEL_VREFINT)      )
  {
    SET_BIT(ADC->CCR, ADC_CCR_TSVREFE);
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @}
  */  

/**
  * @}
  */

#endif /* HAL_ADC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
