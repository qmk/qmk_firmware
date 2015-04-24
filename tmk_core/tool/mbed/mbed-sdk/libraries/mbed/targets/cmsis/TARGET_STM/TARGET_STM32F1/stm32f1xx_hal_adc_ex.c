/**
  ******************************************************************************
  * @file    stm32f1xx_hal_adc_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Operation functions
  *             ++ Start, stop, get result of conversions of injected
  *                group, using 2 possible modes: polling, interruption.
  *             ++ Multimode feature (available on devices with 2 ADCs or more)
  *             ++ Calibration (ADC automatic self-calibration)
  *           + Control functions
  *             ++ Channels configuration on injected group
  *          Other functions (generic functions) are available in file 
  *          "stm32f1xx_hal_adc.c".
  *
  @verbatim
  [..] 
  (@) Sections "ADC peripheral features" and "How to use this driver" are
      available in file of generic functions "stm32f1xx_hal_adc.c".
  [..]
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

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup ADCEx ADCEx
  * @brief ADC Extension HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ADCEx_Private_Constants ADCEx Private Constants
  * @{
  */

  /* Delay for ADC calibration:                                               */
  /* Hardware prerequisite before starting a calibration: the ADC must have   */
  /* been in power-on state for at least two ADC clock cycles.                */
  /* Unit: ADC clock cycles                                                   */
  #define ADC_PRECALIBRATION_DELAY_ADCCLOCKCYCLES       ((uint32_t) 2)

  /* Timeout value for ADC calibration                                        */
  /* Value defined to be higher than worst cases: low clocks freq,            */
  /* maximum prescaler.                                                       */
  /* Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock         */
  /* prescaler 4, sampling time 12.5 ADC clock cycles, resolution 12 bits.    */
  /* Unit: ms                                                                 */
  #define ADC_CALIBRATION_TIMEOUT         ((uint32_t) 10)

  /* Delay for temperature sensor stabilization time.                         */
  /* Maximum delay is 10us (refer to device datasheet, parameter tSTART).     */
  /* Unit: us                                                                 */
  #define ADC_TEMPSENSOR_DELAY_US         ((uint32_t) 10)

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

/** @defgroup ADCEx_Exported_Functions_Group1 Extended Extended IO operation functions
 *  @brief    Extended Extended Input and Output operation functions
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

      (+) Start multimode and enable DMA transfer.
      (+) Stop multimode and disable ADC DMA transfer.
      (+) Get result of multimode conversion.

      (+) Perform the ADC self-calibration for single or differential ending.
      (+) Get calibration factors for single or differential ending.
      (+) Set calibration factors for single or differential ending.
      
@endverbatim
  * @{
  */

/**
  * @brief  Perform an ADC automatic self-calibration
  *         Calibration prerequisite: ADC must be disabled (execute this
  *         function before HAL_ADC_Start() or after HAL_ADC_Stop() ).
  *         During calibration process, ADC is enabled. ADC is let enabled at
  *         the completion of this function.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  uint32_t tickstart;
  __IO uint32_t wait_loop_index = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* 1. Calibration prerequisite:                                             */
  /*    - ADC must be disabled for at least two ADC clock cycles in disable   */
  /*      mode before ADC enable                                              */
  /* Stop potential conversion on going, on regular and injected groups       */
  /* Disable ADC peripheral */
  tmp_hal_status = ADC_ConversionStop_Disable(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmp_hal_status != HAL_ERROR)
  {
    /* Hardware prerequisite: delay before starting the calibration.          */
    /*  - Computation of CPU clock cycles corresponding to ADC clock cycles.  */
    /*  - Wait for the expected ADC clock cycles delay */
    wait_loop_index = ((SystemCoreClock
                        / HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_ADC))
                       * ADC_PRECALIBRATION_DELAY_ADCCLOCKCYCLES        );

    while(wait_loop_index != 0)
    {
      wait_loop_index--;
    }
    
    /* 2. Enable the ADC peripheral */
    ADC_Enable(hadc);
    

    /* 3. Resets ADC calibration registers */  
    SET_BIT(hadc->Instance->CR2, ADC_CR2_RSTCAL);
    
    tickstart = HAL_GetTick();  

    /* Wait for calibration reset completion */
    while(HAL_IS_BIT_SET(hadc->Instance->CR2, ADC_CR2_RSTCAL))
    {
      if((HAL_GetTick() - tickstart) > ADC_CALIBRATION_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
    
    
    /* 4. Start ADC calibration */
    SET_BIT(hadc->Instance->CR2, ADC_CR2_CAL);
    
    tickstart = HAL_GetTick();  

    /* Wait for calibration completion */
    while(HAL_IS_BIT_SET(hadc->Instance->CR2, ADC_CR2_CAL))
    {
      if((HAL_GetTick() - tickstart) > ADC_CALIBRATION_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
    
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Enables ADC, starts conversion of injected group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status != HAL_ERROR)
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
    
    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential           */
    /* interruption, to let the process to ADC IRQ Handler.                   */
    __HAL_UNLOCK(hadc);
    
    /* Set ADC error code to none */
    ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);
        
    /* Enable conversion of injected group.                                   */
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* If automatic injected conversion is enabled, conversion will start     */
    /* after next regular group conversion.                                   */
    /* Case of multimode enabled (for devices with several ADCs): if ADC is   */
    /* slave, ADC is enabled only (conversion is not started). If ADC is      */
    /* master, ADC is enabled and conversion is started.                      */
    if (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO))
    {
      if (ADC_IS_SOFTWARE_START_INJECTED(hadc)     &&
          ADC_NONMULTIMODE_OR_MULTIMODEMASTER(hadc)  )
      {
        /* Start ADC conversion on injected group with SW start */
        SET_BIT(hadc->Instance->CR2, (ADC_CR2_JSWSTART | ADC_CR2_JEXTTRIG));
      }
      else
      {
        /* Start ADC conversion on injected group with external trigger */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_JEXTTRIG);
      }
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Stop conversion of injected channels. Disable ADC peripheral if
  *         no regular conversion is on going.
  * @note   If ADC must be disabled and if conversion is on going on 
  *         regular group, function HAL_ADC_Stop must be used to stop both
  *         injected and regular groups, and disable the ADC.
  * @note   In case of auto-injection mode, HAL_ADC_Stop must be used.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
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
    tmp_hal_status = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status != HAL_ERROR)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
      
    tmp_hal_status = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
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
  __IO uint32_t Conversion_Timeout_CPU_cycles = 0;
  uint32_t Conversion_Timeout_CPU_cycles_max = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Get timeout */
  tickstart = HAL_GetTick();  
     
  /* Polling for end of conversion: differentiation if single/sequence        */
  /* conversion.                                                              */
  /* For injected group, flag JEOC is set only at the end of the sequence,    */
  /* not for each conversion within the sequence.                             */
  /*  - If single conversion for injected group (scan mode disabled or        */
  /*    InjectedNbrOfConversion ==1), flag jEOC is used to determine the      */
  /*    conversion completion.                                                */
  /*  - If sequence conversion for injected group (scan mode enabled and      */
  /*    InjectedNbrOfConversion >=2), flag JEOC is set only at the end of the */
  /*    sequence.                                                             */
  /*    To poll for each conversion, the maximum conversion time is computed  */
  /*    from ADC conversion time (selected sampling time + conversion time of */
  /*    12.5 ADC clock cycles) and APB2/ADC clock prescalers (depending on    */
  /*    settings, conversion time range can be from 28 to 32256 CPU cycles).  */
  if ((hadc->Instance->JSQR & ADC_JSQR_JL) == RESET)
  {
    /* Wait until End of Conversion flag is raised */
    while(HAL_IS_BIT_CLR(hadc->Instance->SR, ADC_FLAG_JEOC))
    {
      /* Check if timeout is disabled (set to infinite wait) */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick() - tickstart ) > Timeout))
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
    /* Poll with maximum conversion time */
    /*  - Computation of CPU clock cycles corresponding to ADC clock cycles   */
    /*    and ADC maximum conversion cycles on all channels.                  */
    /*  - Wait for the expected ADC clock cycles delay                        */
    Conversion_Timeout_CPU_cycles_max = ((SystemCoreClock
                                          / HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_ADC))
                                         * ADC_CONVCYCLES_MAX_RANGE(hadc)                 );

    while(Conversion_Timeout_CPU_cycles < Conversion_Timeout_CPU_cycles_max)
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
      Conversion_Timeout_CPU_cycles ++;
    }
  }

  /* Clear injected group conversion flag (and regular conversion flag raised */
  /* simultaneously)                                                          */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JSTRT | ADC_FLAG_JEOC | ADC_FLAG_EOC);
  
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
  *          - JEOC (end of conversion of injected group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status != HAL_ERROR)
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
    
    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential           */
    /* interruption, to let the process to ADC IRQ Handler.                   */
    __HAL_UNLOCK(hadc);
    
    /* Set ADC error code to none */
    ADC_CLEAR_ERRORCODE(hadc);
    
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
    if (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO))
    {
      if (ADC_IS_SOFTWARE_START_INJECTED(hadc)     &&
          ADC_NONMULTIMODE_OR_MULTIMODEMASTER(hadc)  )
      {
        /* Start ADC conversion on injected group with SW start */
        SET_BIT(hadc->Instance->CR2, (ADC_CR2_JSWSTART | ADC_CR2_JEXTTRIG));
      }
      else
      {
        /* Start ADC conversion on injected group with external trigger */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_JEXTTRIG);
      }
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Stop conversion of injected channels, disable interruption of 
  *         end-of-conversion. Disable ADC peripheral if no regular conversion
  *         is on going.
  * @note   If ADC must be disabled and if conversion is on going on 
  *         regular group, function HAL_ADC_Stop must be used to stop both
  *         injected and regular groups, and disable the ADC.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
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
    tmp_hal_status = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status != HAL_ERROR)
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
      
    tmp_hal_status = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
/**
  * @brief  Enables ADC, starts conversion of regular group and transfers result
  *         through DMA.
  *         Multimode must have been previously configured using 
  *         HAL_ADCEx_MultiModeConfigChannel() function.
  *         Interruptions enabled in this function:
  *          - DMA transfer complete
  *          - DMA half transfer
  *         Each of these interruptions has its dedicated callback function.
  * @note:  On STM32F1 devices, ADC slave regular group must be configured 
  *         with conversion trigger ADC_SOFTWARE_START.
  * @note:  ADC slave can be enabled preliminarily using single-mode  
  *         HAL_ADC_Start() function.
  * @param  hadc: ADC handle of ADC master (handle of ADC slave must not be used)
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  ADC_HandleTypeDef tmphadcSlave;

  /* Check the parameters */
  assert_param(IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  
  /* Process locked */
  __HAL_LOCK(hadc);

  /* Set a temporary handle of the ADC slave associated to the ADC master     */
  ADC_MULTI_SLAVE(hadc, &tmphadcSlave);
  
  /* On STM32F1 devices, ADC slave regular group must be configured with      */
  /* conversion trigger ADC_SOFTWARE_START.                                   */
  /* Note: External trigger of ADC slave must be enabled, it is already done  */
  /*       into function "HAL_ADC_Init()".                                    */
  if ((tmphadcSlave.Instance == NULL)                 ||
      (! ADC_IS_SOFTWARE_START_REGULAR(&tmphadcSlave))  )
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    
    return HAL_ERROR;
  }

  /* Enable the ADC peripherals: master and slave (in case if not already     */
  /* enabled previously)                                                      */
  tmp_hal_status = ADC_Enable(hadc);
  if (tmp_hal_status != HAL_ERROR)
  {
    tmp_hal_status = ADC_Enable(&tmphadcSlave);
  }
  
  /* Start conversion all ADCs of multimode are effectively enabled */
  if (tmp_hal_status != HAL_ERROR)
  {
    /* State machine update (ADC master): Check if an injected conversion is  */
    /* ongoing.                                                               */
    if(hadc->State == HAL_ADC_STATE_BUSY_INJ)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    }
      
    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential           */
    /* interruption, to let the process to ADC IRQ Handler.                   */
    __HAL_UNLOCK(hadc);
  
    /* Set ADC error code to none */
    ADC_CLEAR_ERRORCODE(hadc);
    
    
    /* Set the DMA transfer complete callback */
    hadc->DMA_Handle->XferCpltCallback = ADC_DMAConvCplt;
       
    /* Set the DMA half transfer complete callback */
    hadc->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;
    
    /* Set the DMA error callback */
    hadc->DMA_Handle->XferErrorCallback = ADC_DMAError;

    
    /* Manage ADC and DMA start: ADC overrun interruption, DMA start, ADC     */
    /* start (in case of SW start):                                           */
    
    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOC);
    
    /* Enable ADC DMA mode of ADC master */
    SET_BIT(hadc->Instance->CR2, ADC_CR2_DMA);
    
    /* Start the DMA channel */
    HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DR, (uint32_t)pData, Length);
    
    /* Start conversion of regular group if software start has been selected. */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* Note: Alternate trigger for single conversion could be to force an     */
    /*       additional set of bit ADON "hadc->Instance->CR2 |= ADC_CR2_ADON;"*/
    if (ADC_IS_SOFTWARE_START_REGULAR(hadc))
    {
      /* Start ADC conversion on regular group with SW start */
      SET_BIT(hadc->Instance->CR2, (ADC_CR2_SWSTART | ADC_CR2_EXTTRIG));
    }
    else
    {
      /* Start ADC conversion on regular group with external trigger */
      SET_BIT(hadc->Instance->CR2, ADC_CR2_EXTTRIG);
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected channels in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @note   Multimode is kept enabled after this function. To disable multimode 
  *         (set with HAL_ADCEx_MultiModeConfigChannel(), ADC must be 
  *         reinitialized using HAL_ADC_Init() or HAL_ADC_ReInit().
  * @note   In case of DMA configured in circular mode, function 
  *         HAL_ADC_Stop_DMA must be called after this function with handle of
  *         ADC slave, to properly disable the DMA channel.
  * @param  hadc: ADC handle of ADC master (handle of ADC slave must not be used)
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  ADC_HandleTypeDef tmphadcSlave;
  
  /* Check the parameters */
  assert_param(IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
 
  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC master peripheral */
  tmp_hal_status = ADC_ConversionStop_Disable(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmp_hal_status != HAL_ERROR)
  {
    /* Set a temporary handle of the ADC slave associated to the ADC master   */
    ADC_MULTI_SLAVE(hadc, &tmphadcSlave);

    if (tmphadcSlave.Instance == NULL)
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Process unlocked */
      __HAL_UNLOCK(hadc);
      
      return HAL_ERROR;
    }
    else
    {
      /* Disable ADC slave peripheral */
      tmp_hal_status = ADC_ConversionStop_Disable(&tmphadcSlave);
      
      /* Check if ADC is effectively disabled */
      if (tmp_hal_status != HAL_OK)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
    
    /* Disable ADC DMA mode */
    CLEAR_BIT(hadc->Instance->CR2, ADC_CR2_DMA);
    
    /* Reset configuration of ADC DMA continuous request for dual mode */
    CLEAR_BIT(hadc->Instance->CR1, ADC_CR1_DUALMOD);
        
    /* Disable the DMA channel (in case of DMA in circular mode or stop while */
    /* while DMA transfer is on going)                                        */
    tmp_hal_status = HAL_DMA_Abort(hadc->DMA_Handle);
    
    
    /* Check if DMA channel effectively disabled */
    if (tmp_hal_status != HAL_ERROR)
    {
      /* Change ADC state (ADC master) */
      hadc->State = HAL_ADC_STATE_READY;
    }
    else
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;      
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

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
   
  /* Clear injected group conversion flag to have similar behaviour as        */
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

#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
/**
  * @brief  Returns the last ADC Master&Slave regular conversions results data
  *         in the selected multi mode.
  * @param  hadc: ADC handle of ADC master (handle of ADC slave must not be used)
  * @retval The converted data value.
  */
uint32_t HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef* hadc)
{
  uint32_t tmpDR = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance));
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Note: EOC flag is not cleared here by software because automatically     */
  /*       cleared by hardware when reading register DR.                      */
  
  /* On STM32F1 devices, ADC1 data register DR contains ADC2 conversions      */
  /* only if ADC1 DMA mode is enabled.                                        */
  tmpDR = hadc->Instance->DR;

  if (HAL_IS_BIT_CLR(ADC1->CR2, ADC_CR2_DMA))
  {
    tmpDR |= (ADC2->DR << 16);
  }
    
  /* Return ADC converted value */ 
  return tmpDR;
}
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */

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
      (+) Configure multimode

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
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  __IO uint32_t wait_loop_index = 0;
  
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
  /*   parameter "InjectedNbrOfConversion".                                   */
  if (hadc->Init.ScanConvMode == ADC_SCAN_DISABLE)
  {
    if (sConfigInjected->InjectedRank == ADC_INJECTED_RANK_1)
    {
      /* Clear the old SQx bits for all injected ranks */
      MODIFY_REG(hadc->Instance->JSQR                             ,
                 ADC_JSQR_JL   |
                 ADC_JSQR_JSQ4 |
                 ADC_JSQR_JSQ3 |
                 ADC_JSQR_JSQ2 |
                 ADC_JSQR_JSQ1                                    ,
                 ADC_JSQR_RK_JL(sConfigInjected->InjectedChannel,
                                  ADC_INJECTED_RANK_1,
                                  0x01)                            );
    }
    /* If another injected rank than rank1 was intended to be set, and could  */
    /* not due to ScanConvMode disabled, error is reported.                   */
    else
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      tmp_hal_status = HAL_ERROR;
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
      MODIFY_REG(hadc->Instance->JSQR                                         ,
                 
                 ADC_JSQR_JL                                               |
                 ADC_JSQR_RK_JL(ADC_JSQR_JSQ1,                         
                                  sConfigInjected->InjectedRank,         
                                  sConfigInjected->InjectedNbrOfConversion)   ,
                 
                 ADC_JSQR_JL_SHIFT(sConfigInjected->InjectedNbrOfConversion) |
                 ADC_JSQR_RK_JL(sConfigInjected->InjectedChannel,      
                                  sConfigInjected->InjectedRank,         
                                  sConfigInjected->InjectedNbrOfConversion)    );
    }
    else
    {
      /* Clear the old SQx bits for the selected rank */
      MODIFY_REG(hadc->Instance->JSQR                                       ,
                 
                 ADC_JSQR_JL                                               |
                 ADC_JSQR_RK_JL(ADC_JSQR_JSQ1,                         
                                  sConfigInjected->InjectedRank,         
                                  sConfigInjected->InjectedNbrOfConversion) ,
                 
                 0x00000000                                                  );
    }
  } 
    
  /* Configuration of injected group                                          */
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated only when ADC is disabled:                */
  /*  - external trigger to start conversion                                  */
  /* Parameters update not conditioned to ADC state:                          */
  /*  - Automatic injected conversion                                         */
  /*  - Injected discontinuous mode                                           */
  /* Note: In case of ADC already enabled, caution to not launch an unwanted  */
  /*       conversion while modifying register CR2 by writing 1 to bit ADON.  */
  if (ADC_IS_ENABLE(hadc) == RESET)
  {    
    MODIFY_REG(hadc->Instance->CR2                                           ,
               ADC_CR2_JEXTSEL |
               ADC_CR2_ADON                                                  ,
               ADC_CFGR_JEXTSEL(hadc, sConfigInjected->ExternalTrigInjecConv) );
  }
  
  
  /* Configuration of injected group                                          */
  /*  - Automatic injected conversion                                         */
  /*  - Injected discontinuous mode                                           */
  
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
        
        tmp_hal_status = HAL_ERROR;
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
        
        tmp_hal_status = HAL_ERROR;
      }
    }


  /* InjectedChannel sampling time configuration */
  /* For channels 10 to 17 */
  if (sConfigInjected->InjectedChannel >= ADC_CHANNEL_10)
  {
    MODIFY_REG(hadc->Instance->SMPR1                                                             ,
               ADC_SMPR1(ADC_SMPR1_SMP10, sConfigInjected->InjectedChannel)                      ,
               ADC_SMPR1(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel) );
  }
  else /* For channels 0 to 9 */
  {
    MODIFY_REG(hadc->Instance->SMPR2                                                             ,
               ADC_SMPR2(ADC_SMPR2_SMP0, sConfigInjected->InjectedChannel)                       ,
               ADC_SMPR2(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel) );
  }
  
  /* If ADC1 InjectedChannel_16 or InjectedChannel_17 is selected, enable Temperature sensor  */
  /* and VREFINT measurement path.                                            */
  if ((sConfigInjected->InjectedChannel == ADC_CHANNEL_TEMPSENSOR) ||
      (sConfigInjected->InjectedChannel == ADC_CHANNEL_VREFINT)      )
  {
    SET_BIT(hadc->Instance->CR2, ADC_CR2_TSVREFE);
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
    /* For STM32F1 devices with several ADC: Only ADC1 can access internal    */
    /* measurement channels (VrefInt/TempSensor). If these channels are       */
    /* intended to be set on other ADC instances, an error is reported.       */
    if (hadc->Instance == ADC1)
    {
      if (READ_BIT(hadc->Instance->CR2, ADC_CR2_TSVREFE) == RESET)
      {
        SET_BIT(hadc->Instance->CR2, ADC_CR2_TSVREFE);
        
        if ((sConfigInjected->InjectedChannel == ADC_CHANNEL_TEMPSENSOR))
        {
          /* Delay for temperature sensor stabilization time */
          /* Compute number of CPU cycles to wait for */
          wait_loop_index = (ADC_TEMPSENSOR_DELAY_US * (SystemCoreClock / 1000000));
          while(wait_loop_index != 0)
          {
            wait_loop_index--;
          }
        }
      }
    }
    else
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      tmp_hal_status = HAL_ERROR;
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

#if defined (STM32F101xG) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F105xC) || defined (STM32F107xC) || defined (STM32F103xE) || defined (STM32F103xG)
/**
  * @brief  Enable ADC multimode and configure multimode parameters
  * @note   Possibility to update parameters on the fly:
  *         This function initializes multimode parameters, following  
  *         calls to this function can be used to reconfigure some parameters 
  *         of structure "ADC_MultiModeTypeDef" on the fly, without reseting 
  *         the ADCs (both ADCs of the common group).
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_MultiModeTypeDef".
  * @note   To change back configuration from multimode to single mode, ADC must
  *         be reset (using function HAL_ADC_Init() ).
  * @param  hadc: ADC handle
  * @param  multimode: Structure of ADC multimode configuration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef* hadc, ADC_MultiModeTypeDef* multimode)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  ADC_HandleTypeDef tmphadcSlave;
  
  /* Check the parameters */
  assert_param(IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_MODE(multimode->Mode));

  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Set a temporary handle of the ADC slave associated to the ADC master     */
  ADC_MULTI_SLAVE(hadc, &tmphadcSlave);
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on regular group:                                    */
  /*  - ADC master and ADC slave DMA configuration                            */
  /* Parameters that can be updated only when ADC is disabled:                */
  /*  - Multimode mode selection                                              */
  /* To optimize code, all multimode settings can be set when both ADCs of    */
  /* the common group are in state: disabled.                                 */
  if ((ADC_IS_ENABLE(hadc) == RESET)                     &&
      (ADC_IS_ENABLE(&tmphadcSlave) == RESET)            &&
      (IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance))   )
  {
    MODIFY_REG(hadc->Instance->CR1,
               ADC_CR1_DUALMOD    ,
               multimode->Mode     );
  }
  /* If one of the ADC sharing the same common group is enabled, no update    */
  /* could be done on neither of the multimode structure parameters.          */
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    tmp_hal_status = HAL_ERROR;
  }
    
    
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
} 
#endif /* STM32F101xG || defined STM32F103x6 || defined STM32F103xB || defined STM32F105xC || defined STM32F107xC || defined STM32F103xE || defined STM32F103xG */
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
