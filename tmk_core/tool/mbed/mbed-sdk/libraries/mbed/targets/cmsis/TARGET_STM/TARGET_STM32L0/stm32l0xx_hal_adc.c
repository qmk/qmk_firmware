/**
  ******************************************************************************
  * @file    stm32l0xx_hal_adc.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of conversions of regular 
  *             groups, using 3 possible modes : polling, interruption or DMA.
  *             ++ Calibration feature
  *           + Control functions
  *             ++ Analog Watchdog configuration
  *             ++ Regular Channels Configuration
  *           + State functions
  *             ++ ADC state machine management
  *             ++ Interrupts and flags management
  *         
  @verbatim
  ==============================================================================
                    ##### ADC specific features #####
  ==============================================================================
  [..] 
  (#) 12-bit, 10-bit, 8-bit or 6-bit configurable resolution.

  (#) A built-in hardware oversampler allows to improve analog performances
      while off-loading the related computational burden from the CPU.

  (#) Interrupt generation at the end of conversion and in case of analog
      watchdog or overrun events.
  
  (#) Single and continuous conversion modes.
  
  (#) Scan or discontinuous mode conversion of channel 0 to channel 18.

  (#) Configurable scan direction (Upward from channel 0 to 18 or Backward from
      channel 18 to channel 0)
  
  (#) Data alignment with in-built data coherency.
  
  (#) Channel-wise programmable sampling time.

  (#) External trigger option with configurable polarity.

  (#) DMA request generation during regular channel conversion.
  
  (#) ADC supply requirements: 2.4 V to 3.6 V at full speed and down to 1.8 V at 
      slower speed.
  
  (#) ADC input range: VREF- =VIN =VREF+.

  (#) ADC self-calibration.

  (#) ADC is automatically powered off (AutoOff mode) except during the active
      conversion phase. This dramatically reduces the power consumption of the
      ADC.

  (#) Wait mode to prevent ADC overrun in applications with low frequency.


                     ##### How to use this driver #####
  ==============================================================================
    [..]

    (#) Enable the ADC interface 
        As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured  
        at RCC top level.

        Depending on both possible clock sources: PCLK clock or ADC asynchronous
        clock. 
          __HAL_RCC_ADC1_CLK_ENABLE();                                                            


    (#) ADC pins configuration
         (++) Enable the clock for the ADC GPIOs using the following function:
             __HAL_RCC_GPIOx_CLK_ENABLE();   
         (++) Configure these ADC pins in analog mode using HAL_GPIO_Init();  
  
     (#) Configure the ADC parameters (conversion resolution, oversampler, 
         data alignment, continuous mode,...) using the HAL_ADC_Init() function.

     (#) Activate the ADC peripheral using one of the start functions: 
         HAL_ADC_Start(), HAL_ADC_Start_IT() or HAL_ADC_Start_DMA()
  
     *** Channels configuration ***
     ===============================
     [..]    
       (+) To configure the ADC channels group, use HAL_ADC_ConfigChannel() function.   
       (+) To read the ADC converted values, use the HAL_ADC_GetValue() function.
            
     *** DMA feature configuration ***
     =================================
     [..]
       (+) To enable the DMA mode, use the HAL_ADC_Start_DMA() function.
       (+) To enable the generation of DMA requests continuously at the end of 
           the last DMA transfer, set .Init.DMAContinuousRequests to ENABLE and
           call HAL_ADC_Init() function.

  
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

/** @addtogroup ADC 
  * @brief ADC driver modules
  * @{
  */ 

#ifdef HAL_ADC_MODULE_ENABLED
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Delay for ADC stabilization time.                                          */
/* Maximum delay is 1us (refer to device datasheet, parameter tSTART). */
/* Unit: us */
#define ADC_STAB_DELAY_US       ((uint32_t) 1)

/* Delay for temperature sensor stabilization time. */
/* Maximum delay is 10us (refer to device datasheet, parameter tSTART). */
/* Unit: us */
#define ADC_TEMPSENSOR_DELAY_US ((uint32_t) 10) 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
static void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_DMAError(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc, uint32_t ConversionGroup);
static HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc);
static void ADC_DelayMicroSecond(uint32_t microSecond);

/* Private functions ---------------------------------------------------------*/

/** @defgroup ADC_Private_Functions
  * @{
  */ 

/** @defgroup ADC_Group1 Initialization/de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the ADC. 
      (+) De-initialize the ADC. 
         
@endverbatim
  * @{
  */


/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters 
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC 
  *         (ClockPrescaler, Resolution, Data Alignment and number of conversion), however,
  *         the rest of the configuration parameters are specific to the regular
  *         channels group (scan mode activation, continuous mode activation,
  *         External trigger source and edge, DMA continuous request after the  
  *         last transfer and End of conversion selection).
  *         
  *         As prerequisite, into HAL_ADC_MspInit(), ADC clock must be 
  *         configured at RCC top level.
  *         See commented example code below that can be copied 
  *         and uncommented into HAL_ADC_MspInit().
  *         
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0x00;
  
  /* Check ADC handle */
  if(hadc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CLOCKPRESCALER(hadc->Init.ClockPrescaler));
  assert_param(IS_ADC_RESOLUTION(hadc->Init.Resolution));
  assert_param(IS_ADC_SAMPLE_TIME(hadc->Init.SamplingTime));
  assert_param(IS_ADC_SCAN_MODE(hadc->Init.ScanConvMode));  
  assert_param(IS_ADC_DATA_ALIGN(hadc->Init.DataAlign)); 
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));	    
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DiscontinuousConvMode));
  assert_param(IS_ADC_EXTTRIG_EDGE(hadc->Init.ExternalTrigConvEdge));
  assert_param(IS_ADC_EXTERNAL_TRIG_CONV(hadc->Init.ExternalTrigConv));   
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DMAContinuousRequests));	    
  assert_param(IS_ADC_EOC_SELECTION(hadc->Init.EOCSelection));
  assert_param(IS_ADC_OVERRUN(hadc->Init.Overrun));	    
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.LowPowerAutoWait));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.LowPowerFrequencyMode));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.LowPowerAutoPowerOff));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.OversamplingMode));

  if(hadc->State == HAL_ADC_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_ADC_MspInit(hadc);
  }
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  /* and if there is no conversion on going  (ADC can be enabled anyway,      */ 
  /* in case of call of this function to update a parameter                   */
  /* on the fly).                                                             */
  if ((hadc->State == HAL_ADC_STATE_ERROR) ||
      (ADC_IS_CONVERSION_ONGOING(hadc) != RESET)  )
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    return HAL_ERROR;
  }

  /* Initialize the ADC state */
  hadc->State = HAL_ADC_STATE_BUSY;
  
  /* Configuration of ADC clock: clock source PCLK or asynchronous with 
  selectable prescaler */
  __HAL_ADC_CLOCK_PRESCALER(hadc);
  
  /* Set the Low Frequency mode */
  ADC->CCR &= (uint32_t)~ADC_CCR_LFMEN;
  ADC->CCR |=__HAL_ADC_CCR_LOWFREQUENCY(hadc->Init.LowPowerFrequencyMode);  
   
  /* Enable voltage regulator (if disabled at this step) */
  if (HAL_IS_BIT_CLR(hadc->Instance->CR, ADC_CR_ADVREGEN))
  {
    /* Disable the ADC (if not already disabled) */
    if (ADC_IS_ENABLE(hadc) != RESET )
    {
      /* Check if conditions to disable the ADC are fulfilled */
      if (ADC_DISABLING_CONDITIONS(hadc) != RESET)
      {
        __HAL_ADC_DISABLE(hadc);    
      }
      else  
      {
        hadc->State= HAL_ADC_STATE_ERROR;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }   
      
      /* Get timeout */
      tickstart = HAL_GetTick();

      /* Wait for disabling completion */
      while(HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADEN))
      {
        /* Check for the Timeout */
        if(ADC_ENABLE_TIMEOUT != HAL_MAX_DELAY)
        {          
          if((HAL_GetTick() - tickstart ) > ADC_DISABLE_TIMEOUT)
          {
            hadc->State= HAL_ADC_STATE_TIMEOUT;
            
            /* Process unlocked */
            __HAL_UNLOCK(hadc);
            
            return HAL_TIMEOUT;
          }
        }
      }
      
    }
  
    /* Set ADVREGEN bit */
    hadc->Instance->CR |= ADC_CR_ADVREGEN;
  }
  
  /* Configuration of ADC:                                                    */
  /*  - Resolution                                                            */
  /*  - Data alignment                                                        */
  /*  - Scan direction                                                         */
  /*  - External trigger to start conversion                                  */
  /*  - External trigger polarity                                             */
  /*  - Continuous conversion mode                                            */
  /*  - DMA continuous request                                                */
  /*  - Overrun                                                               */
  /*  - AutoDelay feature                                                     */
  /*  - Discontinuous mode                                                    */
  hadc->Instance->CFGR1 &= ~( ADC_CFGR1_RES   |
                             ADC_CFGR1_ALIGN  |
                             ADC_CFGR1_SCANDIR  |
                             ADC_CFGR1_EXTSEL |
                             ADC_CFGR1_EXTEN  |
                             ADC_CFGR1_CONT   |
                             ADC_CFGR1_DMACFG |
                             ADC_CFGR1_OVRMOD |
                             ADC_CFGR1_AUTDLY |
                             ADC_CFGR1_AUTOFF |
                             ADC_CFGR1_DISCEN);
  
  hadc->Instance->CFGR1 |= ( hadc->Init.Resolution                                       |
                            hadc->Init.DataAlign                                         |
                            ADC_SCANDIR(hadc->Init.ScanConvMode)             |
                            hadc->Init.ExternalTrigConvEdge                              |
                            ADC_CONTINUOUS(hadc->Init.ContinuousConvMode)    | 
                            ADC_DMACONTREQ(hadc->Init.DMAContinuousRequests) |
                            hadc->Init.Overrun                                           |
                            __HAL_ADC_CFGR1_AutoDelay(hadc->Init.LowPowerAutoWait)       |
                            __HAL_ADC_CFGR1_AUTOFF(hadc->Init.LowPowerAutoPowerOff));
  
  /* Configure the external trigger only if Conversion edge is not "NONE" */
  if (hadc->Init.ExternalTrigConvEdge != ADC_EXTERNALTRIGCONVEDGE_NONE)
  {
    hadc->Instance->CFGR1 |= hadc->Init.ExternalTrigConv;
  }
  
  /* Enable discontinuous mode only if continuous mode is disabled */
  if ((hadc->Init.DiscontinuousConvMode == ENABLE) && (hadc->Init.ContinuousConvMode == DISABLE))
  {  
    /* Enable the selected ADC discontinuous mode */   
    hadc->Instance->CFGR1 |= ( ADC_CFGR1_DISCEN);
  }
  
  if (hadc->Init.OversamplingMode == ENABLE)
  {
    assert_param(IS_ADC_OVERSAMPLING_RATIO(hadc->Init.Oversample.Ratio));
    assert_param(IS_ADC_RIGHT_BIT_SHIFT(hadc->Init.Oversample.RightBitShift));
    assert_param(IS_ADC_TRIGGERED_OVERSAMPLING_MODE(hadc->Init.Oversample.TriggeredMode));

    /* Configuration of Oversampler:                                          */
    /*  - Oversampling Ratio                                                  */
    /*  - Right bit shift                                                     */
    /*  - Triggered mode                                                      */
    
    hadc->Instance->CFGR2 &= ~( ADC_CFGR2_OVSR |
                                ADC_CFGR2_OVSS |
                                ADC_CFGR2_TOVS );
    
    hadc->Instance->CFGR2 |= ( hadc->Init.Oversample.Ratio         |
                               hadc->Init.Oversample.RightBitShift             |
                               hadc->Init.Oversample.TriggeredMode );
    
    /* Enable OverSampling mode */
     hadc->Instance->CFGR2 |= ADC_CFGR2_OVSE;
  }
  else
  {
    /* Disable OverSampling mode */
     hadc->Instance->CFGR2 &= ~ADC_CFGR2_OVSE;
  }    
  
  /* Clear the old sampling time */
  hadc->Instance->SMPR &= (uint32_t)(~ADC_SMPR_SMPR);
  
  /* Set the new sample time */
  hadc->Instance->SMPR |= hadc->Init.SamplingTime;
  
  
  /* Set ADC error code to none */
  hadc->ErrorCode = HAL_ADC_ERROR_NONE;
  
  /* Initialize the ADC state */
  hadc->State = HAL_ADC_STATE_READY;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Deinitialize the ADC peripheral registers to its default reset values.
  * @note   To not impact other ADCs, reset of common ADC registers have been
  *         left commented below.
  *         If needed, the example code can be copied and uncommented into
  *         function HAL_ADC_MspDeInit().
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;
  
  /* Check ADC handle */
  if(hadc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Change ADC state */
  hadc->State = HAL_ADC_STATE_BUSY;
  
  /* Stop potential conversion ongoing */
  if (HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADSTART) && HAL_IS_BIT_CLR(hadc->Instance->CR, ADC_CR_ADDIS))
  {
    /* Stop regular conversion */
    hadc->Instance->CR |= ADC_CR_ADSTP;
  }
  
  /* Disable ADC: Solution to recover from an unknown ADC state (for example, */
  /* in case of forbidden action on register bits)                            */
  /* Procedure to disable the ADC peripheral: wait for conversions            */
  /* effectively stopped, then disable ADC                                    */
  /* 1. Wait until ADSTART = 0 */
  
  /* Get timeout */
  tickstart = HAL_GetTick();  
  
  while(HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADSTART))
  {
    /* Check for the Timeout */
    if(ADC_STOP_CONVERSION_TIMEOUT != HAL_MAX_DELAY)
    {
      if((HAL_GetTick() - tickstart ) > ADC_STOP_CONVERSION_TIMEOUT)
      {
        hadc->State= HAL_ADC_STATE_TIMEOUT;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* 2. Disable the ADC peripheral */
  __HAL_ADC_DISABLE(hadc);
  
    
  /* Reset ADC registers****************/
  /* Reset register IER */
  __HAL_ADC_DISABLE_IT(hadc, (ADC_IT_AWD | ADC_IT_OVR | ADC_IT_EOCAL | ADC_IT_EOS |  \
                              ADC_IT_EOC | ADC_IT_RDY | ADC_IT_EOSMP ));
      
  /* Reset register ISR */
  __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_AWD | ADC_FLAG_EOCAL | ADC_FLAG_OVR | ADC_FLAG_EOS |  \
                              ADC_FLAG_EOC | ADC_FLAG_EOSMP | ADC_FLAG_RDY));
  
  /* Reset register CR */
  /* Disable voltage regulator */
  /* Note: Regulator disable useful for power saving */
  /* Reset ADVREGEN bit */
  hadc->Instance->CR &= ~ADC_CR_ADVREGEN;
  
  /* Bits ADC_CR_ADSTP, ADC_CR_ADSTART are in access mode "read-set": no direct reset applicable */
  /* No action */
  
  /* Reset register CFGR1 */
  hadc->Instance->CFGR1 &= ~(ADC_CFGR1_AWDCH  | ADC_CFGR1_AWDEN  | ADC_CFGR1_AWDSGL | \
                             ADC_CFGR1_DISCEN | ADC_CFGR1_AUTOFF | ADC_CFGR1_AUTDLY | \
                             ADC_CFGR1_CONT   | ADC_CFGR1_OVRMOD | ADC_CFGR1_EXTEN  | \
                             ADC_CFGR1_EXTSEL | ADC_CFGR1_ALIGN  | ADC_CFGR1_RES    | \
                             ADC_CFGR1_SCANDIR| ADC_CFGR1_DMACFG | ADC_CFGR1_DMAEN);

  /* Reset register CFGR2 */
  hadc->Instance->CFGR2 &= ~(ADC_CFGR2_TOVS  | ADC_CFGR2_OVSS  | ADC_CFGR2_OVSR | \
                             ADC_CFGR2_OVSE  | ADC_CFGR2_CKMODE );
  
  /* Reset register SMPR */
  hadc->Instance->SMPR &= ~(ADC_SMPR_SMPR);
  
  /* Reset register TR */
  hadc->Instance->TR &= ~(ADC_TR_LT | ADC_TR_HT);
  
  /* Reset register CALFACT */
  hadc->Instance->CALFACT &= ~(ADC_CALFACT_CALFACT);
  
  /* Reset register DR */
  /* bits in access mode read only, no direct reset applicable*/

  /* Reset register CALFACT */
  hadc->Instance->CALFACT &= ~(ADC_CALFACT_CALFACT);

    
  /* DeInit the low level hardware */
  HAL_ADC_MspDeInit(hadc);
  
  /* Set ADC error code to none */
  hadc->ErrorCode = HAL_ADC_ERROR_NONE;
  
  /* Change ADC state */
  hadc->State = HAL_ADC_STATE_RESET; 
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the ADC MSP.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.  
  * @retval None
  */
__weak void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADC_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  DeInitializes the ADC MSP.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.  
  * @retval None
  */
__weak void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADC_MspDeInit could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup ADC_Group2 I/O operation functions
 *  @brief    I/O operation functions 
 *
@verbatim   
 ===============================================================================
             ##### IO operation functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) poll for conversion complete.
      (+) poll for conversion event.
      (+) Start conversion and enable interrupt.
      (+) Stop conversion and disable interrupt.
      (+) handle ADC interrupt request.
      (+) Start conversion of regular channel and enable DMA transfer.
      (+) Stop conversion of regular channel and disable DMA transfer.
      (+) Get result of regular channel conversion.
      (+) Handle ADC interrupt request.

@endverbatim
  * @{
  */


/**
  * @brief  Enables ADC and starts conversion of the regular channels.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Perform ADC enable and conversion start if no conversion is on going */
  if (ADC_IS_CONVERSION_ONGOING(hadc) == RESET)
  {
    /* Process locked */
    __HAL_LOCK(hadc);
    
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_BUSY_REG;
    
    /* Set ADC error code to none */
    hadc->ErrorCode = HAL_ADC_ERROR_NONE;
  
    /* Enable the ADC peripheral */
    /* If low power mode AutoPowerOff is enabled, power-on/off phases are       */
    /* performed automatically by hardware.                                     */
    if (hadc->Init.LowPowerAutoPowerOff != ENABLE)
    {
      tmpHALStatus = ADC_Enable(hadc);
    }
    
    /* Start conversion if ADC is effectively enabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* ADC start conversion command */
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
        
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  else
  {
    tmpHALStatus = HAL_BUSY;
  }
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Stop ADC conversion of regular channels, disable ADC peripheral.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion ongoing (regular conversion) */
  tmpHALStatus = ADC_ConversionStop(hadc, ADC_REGULAR_GROUP);
  
  /* 2. Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Disable the ADC peripheral */
    tmpHALStatus = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if ((hadc->State != HAL_ADC_STATE_ERROR) && (tmpHALStatus != HAL_ERROR))
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {   
    return HAL_ERROR;
  }  
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Wait for regular group conversion to be completed.
  * @note   ADC conversion flags EOS (end of sequence) and EOC (end of
  *         conversion) are cleared by this function, with an exception:
  *         if low power feature "LowPowerAutoWait" is enabled, flags are 
  *         not cleared to not interfere with this feature until data register
  *         is read using function HAL_ADC_GetValue().
  * @note   This function cannot be used in a particular setup: ADC configured 
  *         in DMA mode and polling for end of each conversion (ADC init
  *         parameter "EOCSelection" set to ADC_EOC_SINGLE_CONV).
  *         In this case, DMA resets the flag EOC and polling cannot be
  *         performed on each conversion. Nevertheless, polling can still 
  *         be performed on the complete sequence.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart = 0;
  uint32_t tmp_Flag_EOC;
 
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* If end of conversion selected to end of sequence */
  if (hadc->Init.EOCSelection == ADC_EOC_SEQ_CONV)
  {
    tmp_Flag_EOC = ADC_FLAG_EOS;
  }
  /* If end of conversion selected to end of each conversion */
  else /* ADC_EOC_SINGLE_CONV */
  {
    /* Verification that ADC configuration is compliant with polling for      */
    /* each conversion:                                                       */
    /* Particular case is ADC configured in DMA mode and ADC sequencer with   */
    /* several ranks and polling for end of each conversion.                  */
    /* For code simplicity sake, this particular case is generalized to       */
    /* ADC configured in DMA mode and and polling for end of each conversion. */
    if (HAL_IS_BIT_SET(hadc->Instance->CFGR1, ADC_CFGR1_DMAEN))
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Process unlocked */
      __HAL_UNLOCK(hadc);
      
      return HAL_ERROR;
    }
    else
    {
      tmp_Flag_EOC = (ADC_FLAG_EOC | ADC_FLAG_EOS);
    }
  }
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  /* Wait until End of Conversion flag is raised */
  while(HAL_IS_BIT_CLR(hadc->Instance->ISR, tmp_Flag_EOC))
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
      {
        /* Update ADC state machine to timeout */
        hadc->State = HAL_ADC_STATE_TIMEOUT;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* Clear end of conversion flag of regular group if low power feature       */
  /* "LowPowerAutoWait " is disabled, to not interfere with this feature      */
  /* until data register is read using function HAL_ADC_GetValue().           */
  if (hadc->Init.LowPowerAutoWait == DISABLE)
  {
    /* Clear regular group conversion flag */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS));
  }
  
  /* Update state machine on conversion status if not in error state */
  if(hadc->State != HAL_ADC_STATE_ERROR)
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_EOC;
  }
  
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Poll for conversion event.
  * @param  hadc: ADC handle.
  * @param  EventType: the ADC event type.
  *          This parameter can be one of the following values:
  *            @arg ADC_AWD_EVENT: ADC Analog watchdog event.
  *            @arg ADC_OVR_EVENT: ADC Overrun event.
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart = 0; 
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_EVENT_TYPE(EventType));
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  /* Check selected event flag */
  while(!(__HAL_ADC_GET_FLAG(hadc,EventType)))
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
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  switch(EventType)
  {
    /* Check analog watchdog flag */
  case ADC_AWD_EVENT:
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD;
    
    /* Clear ADC analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD);
    break;
    
    /* Case ADC_OVR_EVENT */
  default:
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    /* Clear ADC Overrun flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_OVR);
    break;
  }
  
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Enables the interrupt and starts ADC conversion of regular channels.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
    
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Perform ADC enable and conversion start if no conversion is on going */
  if (ADC_IS_CONVERSION_ONGOING(hadc) == RESET)
  {
    /* Process locked */
    __HAL_LOCK(hadc);
    
    /* State machine update: Change ADC state */
    hadc->State = HAL_ADC_STATE_BUSY_REG;
    
    /* Set ADC error code to none */
    hadc->ErrorCode = HAL_ADC_ERROR_NONE;
    
    /* Enable the ADC peripheral */
    /* If low power mode AutoPowerOff is enabled, power-on/off phases are       */
    /* performed automatically by hardware.                                     */
    if (hadc->Init.LowPowerAutoPowerOff != ENABLE)
    {
      tmpHALStatus = ADC_Enable(hadc);
    }
    
    /* Start conversion if ADC is effectively enabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Enable ADC overrun interrupt */
      __HAL_ADC_ENABLE_IT(hadc, ADC_IT_OVR);
      
      /* Enable ADC end of conversion interrupt */
      switch(hadc->Init.EOCSelection)
      {
        case ADC_EOC_SEQ_CONV: 
          __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC);
          __HAL_ADC_ENABLE_IT(hadc, ADC_IT_EOS);
          break;
        /* case ADC_EOC_SINGLE_CONV */
        default:
          __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOS);
          __HAL_ADC_ENABLE_IT(hadc, ADC_IT_EOC);
          break;
      }
      
      /* ADC start conversion command */
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
    
    else
    {
      tmpHALStatus = HAL_ERROR;
    }
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  else
  {
    tmpHALStatus = HAL_BUSY;
  }

  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Stop ADC conversion of regular channels, disable interruptions
  *         EOC/EOS/OVR, disable ADC peripheral.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
    
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion ongoing (regular conversion) */
  tmpHALStatus = ADC_ConversionStop(hadc, ADC_REGULAR_GROUP);
  
  /* 2. Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Disable ADC interrupts */
    __HAL_ADC_DISABLE_IT(hadc, (ADC_IT_EOC | ADC_IT_EOS | ADC_IT_OVR));
    
    /* Disable the ADC peripheral */
    tmpHALStatus = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if ((hadc->State != HAL_ADC_STATE_ERROR) && (tmpHALStatus != HAL_ERROR))
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {   
    return HAL_ERROR;
  }
  
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Handles ADC interrupt request  
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_EOC_SELECTION(hadc->Init.EOCSelection));
  
  
  /* Check End of Conversion flag for regular channels */
  if( (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOC) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_EOC)) || \
      (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOS) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_EOS)) )
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_EOC;

    
    /* Disable interruption if no further conversion upcoming by continuous mode or external trigger */
    if((hadc->Init.ContinuousConvMode == DISABLE) && \
       (hadc->Init.ExternalTrigConvEdge == ADC_EXTERNALTRIGCONVEDGE_NONE)
       )
    {
      /* Allowed to modify bits ADC_IT_EOC/ADC_IT_EOS only if bit ADSTART==0 (no conversion on going) */
      if (HAL_IS_BIT_CLR(hadc->Instance->CR, ADC_CR_ADSTART))
      {
        /* Cases of interruption after each conversion or after each sequence */
        /* If interruption after each sequence */
        if (hadc->Init.EOCSelection == ADC_EOC_SEQ_CONV)
        {
          /* Allowed to modify bits ADC_IT_EOC/ADC_IT_EOS/ADC_IT_OVR only if bit*/
          /* ADSTART==0 (no conversion on going)                                */
          if (ADC_IS_CONVERSION_ONGOING(hadc) == RESET)
          {
            /* If End of Sequence is reached, disable interrupts */
            if( __HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOS) )
            {
              /* DISABLE ADC end of sequence conversion interrupt  */
              /* DISABLE ADC overrun interrupt */
              __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC | ADC_IT_EOS | ADC_IT_OVR);
            }
          }
          else
          {
            /* Change ADC state to error state */
            hadc->State = HAL_ADC_STATE_ERROR;
            /* Set ADC error code to ADC IP internal error */
            hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
          }
        }
        /* If interruption after each conversion */
        else
        {
          /* DISABLE ADC end of single conversion interrupt */
          /* DISABLE ADC overrun interrupt */
          __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC | ADC_IT_OVR);
        }
      }
      else
      {
        /* Change ADC state to error state */
        hadc->State = HAL_ADC_STATE_ERROR;
      }       
    }    

    /* Conversion complete callback */
    /* Note: into callback, to determine if callback has been triggered from EOC or EOS, */
    /*       it is possible to use: if( __HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOS))         */
    HAL_ADC_ConvCpltCallback(hadc);
    
    /* Clear regular channels conversion flag */
    if (hadc->Init.LowPowerAutoWait != ENABLE)
    {
      __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS) );
    }
  }
  
   
  /* Check Analog watchdog flags */
  if( (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_AWD)))
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD;
    
    /* Level out of window callback */
    HAL_ADC_LevelOutOfWindowCallback(hadc);
    
    /* Clear ADC Analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD);    
  }  
  
  /* Check Overrun flag */
  if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_OVR) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_OVR))
  {
    /* Change ADC state to overrun state */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    /* Set ADC error code to overrun */
    hadc->ErrorCode |= HAL_ADC_ERROR_OVR;
    
    /* Clear the Overrun flag */
    __HAL_ADC_CLEAR_FLAG(hadc,ADC_FLAG_OVR);
    
    /* Error callback */ 
    HAL_ADC_ErrorCallback(hadc);
  }
}

/**
  * @brief  Enables ADC DMA request after last transfer (Single-ADC mode) and enables ADC peripheral  
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Perform ADC enable and conversion start if no conversion is on going */
  if (ADC_IS_CONVERSION_ONGOING(hadc) == RESET)
  {
    /* Process locked */
    __HAL_LOCK(hadc);
    
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_BUSY_REG;
    
    /* Set ADC error code to none */
    hadc->ErrorCode = HAL_ADC_ERROR_NONE;
  
    /* Enable the ADC peripheral */
    /* If low power mode AutoPowerOff is enabled, power-on/off phases are       */
    /* performed automatically by hardware.                                     */
    if (hadc->Init.LowPowerAutoPowerOff != ENABLE)
    {
      tmpHALStatus = ADC_Enable(hadc);
    }
    
    /* Start conversion if ADC is effectively enabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Enable ADC DMA mode */
      hadc->Instance->CFGR1 |= ADC_CFGR1_DMAEN;
      
      /* Set the DMA transfer complete callback */
      hadc->DMA_Handle->XferCpltCallback = ADC_DMAConvCplt;
  
      /* Set the DMA half transfer complete callback */
      hadc->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;
      
      /* Set the DMA error callback */
      hadc->DMA_Handle->XferErrorCallback = ADC_DMAError;
      
      /* Manage ADC and DMA start: ADC overrun interruption, DMA start,
         ADC start (in case of SW start) */
      
      /* Enable ADC overrun interrupt */
      __HAL_ADC_ENABLE_IT(hadc, ADC_IT_OVR);
      
      /* Enable the DMA Stream */
      HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DR, (uint32_t)pData, Length);
       
      /* ADC start conversion command */
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
        
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  else
  {
    tmpHALStatus = HAL_BUSY;
  }
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Disable ADC DMA (Single-ADC mode), disable ADC peripheral
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion ongoing (regular conversion) */
  tmpHALStatus = ADC_ConversionStop(hadc, ADC_REGULAR_GROUP);
  
  /* 2. Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Disable ADC DMA (ADC DMA configuration ADC_CFGR_DMACFG is kept) */
    hadc->Instance->CFGR1 &= ~ADC_CFGR1_DMAEN;
    
    /* Disable the DMA Stream */
    if (HAL_DMA_Abort(hadc->DMA_Handle) != HAL_OK)
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Process unlocked */
      __HAL_UNLOCK(hadc);
      
      return HAL_ERROR;
    }
    
    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IT_OVR);
    
    /* Disable the ADC peripheral */
    tmpHALStatus = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if ((hadc->State != HAL_ADC_STATE_ERROR) && (tmpHALStatus != HAL_ERROR))
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {   
    return HAL_ERROR;
  }  
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Gets the converted value from data register of regular channel.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval Converted value
  */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
{       
  /* Return the selected ADC converted value */ 
  return hadc->Instance->DR;
}

/**
  * @brief  Regular conversion complete callback in non blocking mode 
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADC_ConvCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Regular conversion half DMA transfer callback in non blocking mode 
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
__weak void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADC_ConvHalfCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Analog watchdog callback in non blocking mode 
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
__weak void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADC_LevelOoutOfWindowCallback could be implemented in the user file
   */
}

/**
  * @brief  Error ADC callback.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
__weak void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADC_ErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup ADC_Group3 Peripheral Control functions
 *  @brief   	Peripheral Control functions 
 *
@verbatim   
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels.
      (+) Configure the analog watch dog.
      
@endverbatim
  * @{
  */


/**
  * @brief  Configures the selected ADC regular channel: sampling time,
  *         offset,.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @param  sConfig: ADC regular channel configuration structure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CHANNEL(sConfig->Channel));
  
  /* Process locked */
  __HAL_LOCK(hadc);    
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going :                                                    */
  /*  - Channel number                                                        */
  /*  - Management of internal measurement channels: Vbat/VrefInt/TempSensor  */
  if (ADC_IS_CONVERSION_ONGOING(hadc) != RESET)
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    return HAL_ERROR;
  }
  
  /* Enable selected channels */
  hadc->Instance->CHSELR |= (uint32_t)(sConfig->Channel & ADC_CHANNEL_MASK);
  
  /* Management of internal measurement channels: Vlcd/VrefInt/TempSensor     */
  /* internal measurement paths enable: If internal channel selected, enable  */
  /* dedicated internal buffers and path.                                     */
  
  /* If Temperature sensor channel is selected, then enable the internal      */
  /* buffers and path  */
  if (((sConfig->Channel & ADC_CHANNEL_MASK) & ADC_CHANNEL_TEMPSENSOR ) == (ADC_CHANNEL_TEMPSENSOR & ADC_CHANNEL_MASK))
  {
    ADC->CCR |= ADC_CCR_TSEN;   
    
    /* Delay for temperature sensor stabilization time */
    ADC_DelayMicroSecond(ADC_TEMPSENSOR_DELAY_US);
  }
  
  /* If VRefInt channel is selected, then enable the internal buffers and path   */
  if (((sConfig->Channel & ADC_CHANNEL_MASK) & ADC_CHANNEL_VREFINT) == (ADC_CHANNEL_VREFINT & ADC_CHANNEL_MASK))
  {
    ADC->CCR |= ADC_CCR_VREFEN;   
  }
  
  /* If Vlcd channel is selected, then enable the internal buffers and path   */
  if (((sConfig->Channel & ADC_CHANNEL_MASK) & ADC_CHANNEL_VLCD) == (ADC_CHANNEL_VLCD & ADC_CHANNEL_MASK))
  {
    ADC->CCR |= ADC_CCR_VLCDEN;   
  }
 
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Configures the analog watchdog.
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @param  AnalogWDGConfig : pointer to an ADC_AnalogWDGConfTypeDef structure 
  *         that contains the configuration information of ADC analog watchdog.
  * @retval HAL status	  
  */
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{
  uint32_t tmpAWDHighThresholdShifted;
  uint32_t tmpAWDLowThresholdShifted;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_ANALOG_WATCHDOG_MODE(AnalogWDGConfig->WatchdogMode));
  assert_param(IS_ADC_CHANNEL(AnalogWDGConfig->Channel));
  assert_param(IS_FUNCTIONAL_STATE(AnalogWDGConfig->ITMode));
  
  assert_param(IS_ADC_RANGE(ADC_GET_RESOLUTION(hadc), AnalogWDGConfig->HighThreshold));
  assert_param(IS_ADC_RANGE(ADC_GET_RESOLUTION(hadc), AnalogWDGConfig->LowThreshold));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going :                                                    */
  /*  - Analog watchdog channels                                              */
  /*  - Analog watchdog thresholds                                            */
  if (ADC_IS_CONVERSION_ONGOING(hadc) != RESET)
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    return HAL_ERROR;
  }

  /* Configure ADC Analog watchdog interrupt */
  if(AnalogWDGConfig->ITMode == ENABLE)
  {
    /* Enable the ADC Analog watchdog interrupt */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_AWD);
  }
  else
  {
    /* Disable the ADC Analog watchdog interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IT_AWD);
  }
    
  /* Configuration of analog watchdog:                                        */
  /*  - Set the analog watchdog mode                                          */
  /*  - Set the Analog watchdog channel (is not used if watchdog              */
  /*    mode "all channels": ADC_CFGR1_AWD1SGL=0)                             */
  hadc->Instance->CFGR1 &= ~( ADC_CFGR1_AWDSGL |
                             ADC_CFGR1_AWDEN  |
                             ADC_CFGR1_AWDCH);
  
  hadc->Instance->CFGR1 |= ( AnalogWDGConfig->WatchdogMode |
                            (AnalogWDGConfig->Channel & ADC_CHANNEL_AWD_MASK));
  
  
  /* Shift the offset in function of the selected ADC resolution: Thresholds  */
  /* have to be left-aligned on bit 11, the LSB (right bits) are set to 0     */
  tmpAWDHighThresholdShifted = ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(hadc, AnalogWDGConfig->HighThreshold);
  tmpAWDLowThresholdShifted  = ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(hadc, AnalogWDGConfig->LowThreshold);
  
  /* Clear High & Low high thresholds */
  hadc->Instance->TR &= (uint32_t) ~ (ADC_TR_HT | ADC_TR_LT);
  
  /* Set the high threshold */
  hadc->Instance->TR = ADC_TRX_HIGHTHRESHOLD (tmpAWDHighThresholdShifted);
  /* Set the low threshold */
  hadc->Instance->TR |= tmpAWDLowThresholdShifted;  
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup ADC_Group4 ADC Peripheral State functions
 *  @brief   ADC Peripheral State functions 
 *
@verbatim   
 ===============================================================================
            ##### ADC Peripheral State functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Check the ADC state.
      (+) handle ADC interrupt request.
         
@endverbatim
  * @{
  */

/**
  * @brief  return the ADC state
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval HAL state
  */
HAL_ADC_StateTypeDef HAL_ADC_GetState(ADC_HandleTypeDef* hadc)
{
  /* Return ADC state */
  return hadc->State;
}

/**
  * @brief  Return the ADC error code
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval ADC Error Code
  */
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc)
{
  return hadc->ErrorCode;
}


/**
  * @}
  */

/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @note If low power mode AutoPowerOff is enabled, power-on/off phases are
  * performed automatically by hardware.
  * In this mode, this function is useless and must not be called because 
  * flag ADC_FLAG_RDY is not usable.
  * Therefore, this function must be called under condition of
  * "if (hadc->Init.LowPowerAutoPowerOff != ENABLE)". 
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;

  /* ADC enable and wait for ADC ready (in case of ADC is disabled or         */
  /* enabling phase not yet completed: flag ADC ready not yet set).           */
  /* Timeout implemented to not be stuck if ADC cannot be enabled (possible   */
  /* causes: ADC clock not running, ...).                                     */
  if (ADC_IS_ENABLE(hadc) == RESET)
  {
    /* Check if conditions to enable the ADC are fulfilled */
    if (ADC_ENABLING_CONDITIONS(hadc) == RESET)
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Set ADC error code to ADC IP internal error */
      hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
      
      return HAL_ERROR;
    }
    
    /* Enable the ADC peripheral */
    __HAL_ADC_ENABLE(hadc);
    
    /* Delay for ADC stabilization time. */
    ADC_DelayMicroSecond(ADC_STAB_DELAY_US);

    /* Wait for ADC effectively enabled */
    /* Get timeout */
    tickstart = HAL_GetTick();  
    
    /* Skip polling for RDY ADRDY when AutoOFF is enabled  */
    if (hadc->Init.LowPowerAutoPowerOff != ENABLE)
    {      
      while(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_RDY) == RESET)
      {
        /* Check for the Timeout */
        if(ADC_ENABLE_TIMEOUT != HAL_MAX_DELAY)
        {
          if((HAL_GetTick() - tickstart ) > ADC_ENABLE_TIMEOUT)
          {
            /* Update ADC state machine to error */
            hadc->State = HAL_ADC_STATE_ERROR;
            
            /* Set ADC error code to ADC IP internal error */
            hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
            
            return HAL_ERROR;
          }
        }
      }
    }
  }
   
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Disable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped to disable the ADC.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;
  
  /* Verification if ADC is not already disabled:                             */
  /* forbidden to disable ADC (set bit ADC_CR_ADDIS) if ADC is already        */
  /* disabled.                                                                */
  if (ADC_IS_ENABLE(hadc) != RESET )
  {
    /* Check if conditions to disable the ADC are fulfilled */
    if (ADC_DISABLING_CONDITIONS(hadc) != RESET)
    {
      /* Disable the ADC peripheral */
      __HAL_ADC_DISABLE(hadc);
    }
    else
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Set ADC error code to ADC internal error */
      hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
      
      return HAL_ERROR;
    }
     
    /* Wait for ADC effectively disabled */
    /* Get timeout */
    tickstart = HAL_GetTick();
    
    while(HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADEN))
    {
      /* Check for the Timeout */
      if(ADC_ENABLE_TIMEOUT != HAL_MAX_DELAY)
      {
        if((HAL_GetTick() - tickstart ) > ADC_DISABLE_TIMEOUT)
        {
          /* Update ADC state machine to error */
          hadc->State = HAL_ADC_STATE_ERROR;
          
          /* Set ADC error code to ADC internal error */
          hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
          
          return HAL_ERROR;
        }
      }
    }
  }
  
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Stop ADC conversion.
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped to disable the ADC.
  * @param  hadc: ADC handle
  * @param  ConversionGroup: Only ADC group regular.
  *          This parameter can be one of the following values:
  *            @arg ADC_REGULAR_GROUP: ADC regular conversion type.
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc, uint32_t ConversionGroup)
{
  uint32_t tickstart = 0 ;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CONVERSION_GROUP(ConversionGroup));
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going :                                                    */
  if (ADC_IS_CONVERSION_ONGOING(hadc) != RESET)
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    /* Process unlocked */
    return HAL_ERROR;
  }  
  
  /* Verification: if ADC is not already stopped, bypass this function */
  if (HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADSTART))
  {    
    /* Stop potential conversion on regular group */
    if (ConversionGroup == ADC_REGULAR_GROUP)
    {
      /* Software is allowed to set ADSTP only when ADSTART=1 and ADDIS=0 */
      if (HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADSTART) && \
          HAL_IS_BIT_CLR(hadc->Instance->CR, ADC_CR_ADDIS)                  )
      {
        /* Stop conversions on regular group */
        hadc->Instance->CR |= ADC_CR_ADSTP;
      }
    }
    
    /* Wait for conversion effectively stopped */
    /* Get timeout */
    tickstart = HAL_GetTick();
      
    while((hadc->Instance->CR & ADC_CR_ADSTART) != RESET)
    {
      /* Check for the Timeout */
      if(ADC_STOP_CONVERSION_TIMEOUT != HAL_MAX_DELAY)
      {
        if((HAL_GetTick() - tickstart ) > ADC_STOP_CONVERSION_TIMEOUT)
        {
          /* Update ADC state machine to error */
          hadc->State = HAL_ADC_STATE_ERROR;
          
          /* Set ADC error code to ADC IP internal error */
          hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
          
          return HAL_ERROR;
        }
      }
    }    
  }
   
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  DMA transfer complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma)   
{
    ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_EOC;
    
    HAL_ADC_ConvCpltCallback(hadc); 
}

/**
  * @brief  DMA half transfer complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma)   
{
    ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
    
    /* Conversion complete callback */
    HAL_ADC_ConvHalfCpltCallback(hadc); 
}

/**
  * @brief  DMA error callback 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void ADC_DMAError(DMA_HandleTypeDef *hdma)   
{
    ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
    hadc->State= HAL_ADC_STATE_ERROR;
    /* Set ADC error code to DMA error */
    hadc->ErrorCode |= HAL_ADC_ERROR_DMA;
    HAL_ADC_ErrorCallback(hadc); 
}

/**
  * @brief  Delay micro seconds 
  * @param  microSecond : delay
  * @retval None
  */
static void ADC_DelayMicroSecond(uint32_t microSecond)
{
  /* Compute number of CPU cycles to wait for */
  __IO uint32_t waitLoopIndex = (microSecond * (SystemCoreClock / 1000000));

  while(waitLoopIndex != 0)
  {
    waitLoopIndex--;
  } 
}

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
