/**
  ******************************************************************************
  * @file    stm32l0xx_hal_adc_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Start calibration.
  *           + Read the calibration factor.
  *           + Set a calibration factor.
  *          
  @verbatim
  ==============================================================================
                    ##### ADC specific features #####
  ==============================================================================
  [..] 
  (#) Self calibration.


                     ##### How to use this driver #####
  ==============================================================================
    [..]

    (#) Call HAL_ADCEx_Calibration_Start() to start calibration
    
    (#) Read the calibration factor using HAL_ADCEx_Calibration_GetValue()
  
    (#) User can set a his calibration factor using HAL_ADCEx_Calibration_SetValue()
  
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

/** @addtogroup ADCEx 
  * @brief ADC driver modules
  * @{
  */ 

#ifdef HAL_ADC_MODULE_ENABLED
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @addtgroup ADCEx_Group ADC Extended features functions
 *  @brief    ADC Extended features functions 
 *
@verbatim   
 ===============================================================================
            ##### ADC Extended features functions #####
 ===============================================================================  
    [..]
This subsection provides functions allowing to:
      (+) Start calibration.
      (+) Get calibration factor.
      (+) Set calibration factor.

@endverbatim
  * @{
  */


/**
  * @brief  Start an automatic calibration
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @param  SingleDiff: Selection of single-ended or differential input
  *          This parameter can be only of the following values:
  *            @arg ADC_SINGLE_ENDED: Channel in mode input single ended
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc, uint32_t SingleDiff)
{
  uint32_t tickstart = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(SingleDiff));

  /* Process locked */
  __HAL_LOCK(hadc);
   
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
    
    /* Wait for ADC effectively disabled */
    /* Get timeout */
    tickstart = HAL_GetTick();  

    /* Wait for disabling completion */
    while(HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADEN))
    {
      /* Check for the Timeout */
      if(ADC_DISABLE_TIMEOUT != HAL_MAX_DELAY)
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

  /* Start ADC calibration */
  hadc->Instance->CR |= ADC_CR_ADCAL;

  /* Get timeout */
  tickstart = HAL_GetTick(); 

  /* Wait for calibration completion */
  while(HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADCAL))
  {
    /* Check for the Timeout */
    if(ADC_CALIBRATION_TIMEOUT != HAL_MAX_DELAY)
    {
      if((HAL_GetTick() - tickstart ) > ADC_CALIBRATION_TIMEOUT)
      {
        hadc->State= HAL_ADC_STATE_TIMEOUT;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
      }
    }
  }  
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
  
}

/**
  * @brief  Get the calibration factor.
  * @param  hadc: ADC handle.
  * @param  SingleDiff: This parameter can be only:
  *           @arg ADC_SINGLE_ENDED: Channel in mode input single ended.
  * @retval Calibration value.
  */
uint32_t HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef* hadc, uint32_t SingleDiff)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(SingleDiff)); 
  
  /* Return the ADC calibration value */ 
  return ((hadc->Instance->CALFACT) & 0x0000007F);
}

/**
  * @brief  Set the calibration factor to overwrite automatic conversion result.
  *         ADC must be enabled and no conversion is ongoing.
  * @param  hadc: ADC handle
  * @param  SingleDiff: This parameter can be only:
  *           @arg ADC_SINGLE_ENDED: Channel in mode input single ended.
  * @param  CalibrationFactor: Calibration factor (coded on 7 bits maximum)
  * @retval HAL state
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef* hadc, uint32_t SingleDiff, uint32_t CalibrationFactor)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(SingleDiff)); 
  assert_param(IS_ADC_CALFACT(CalibrationFactor)); 
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Verification of hardware constraints before modifying the calibration    */
  /* factors register: ADC must be enabled, no conversion on going.           */
  if ( (ADC_IS_ENABLE(hadc) != RESET)                            &&
       (ADC_IS_CONVERSION_ONGOING(hadc) == RESET)  )
  {
    /* Set the selected ADC calibration value */ 
    hadc->Instance->CALFACT &= ~ADC_CALFACT_CALFACT;
    hadc->Instance->CALFACT |= CalibrationFactor;
  }
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    /* Update ADC state machine to error */
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief Enables the Buffer Vrefint for the ADC.
  * @note This is functional only if the LOCK is not set.
  * @retval None
  */
void HAL_ADCEx_EnableVREFINT(void)
{
    /* Enable the Buffer for the ADC by setting EN_VREFINT bit and the ENBUF_SENSOR_ADC in the CFGR3 register */
    SET_BIT(SYSCFG->CFGR3, (SYSCFG_CFGR3_ENBUF_VREFINT_ADC | SYSCFG_CFGR3_EN_VREFINT)); 
}

/**
  * @brief Disables the Buffer Vrefint for the ADC.
  * @note This is functional only if the LOCK is not set.
  * @retval None
  */
void HAL_ADCEx_DisableVREFINT(void)
{
    /* Disable the Vrefint by resetting EN_VREFINT bit and the ENBUF_SENSOR_ADC in the CFGR3 register */
    CLEAR_BIT(SYSCFG->CFGR3, (SYSCFG_CFGR3_ENBUF_VREFINT_ADC | SYSCFG_CFGR3_EN_VREFINT)); 
}

/**
  * @brief Enables VEREFINT and the Sensor for the ADC.
  * @note This is functional only if the LOCK is not set.
  * @retval None
  */
void HAL_ADCEx_EnableVREFINTTempSensor(void)
{
    /* Enable the Buffer for the ADC by setting EN_VREFINT bit and the ENBUF_SENSOR_ADC in the CFGR3 register */
    SET_BIT(SYSCFG->CFGR3, (SYSCFG_CFGR3_ENBUF_SENSOR_ADC | SYSCFG_CFGR3_EN_VREFINT)); 
}

/**
  * @brief Disables the VEREFINT and Sensor for the ADC.
  * @note This is functional only if the LOCK is not set.
  * @retval None
  */
void HAL_ADCEx_DisableVREFINTTempSensor(void)
{
    /* Disable the Vrefint by resetting EN_VREFINT bit and the ENBUF_SENSOR_ADC in the CFGR3 register */
    CLEAR_BIT(SYSCFG->CFGR3, (SYSCFG_CFGR3_ENBUF_SENSOR_ADC | SYSCFG_CFGR3_EN_VREFINT));
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
