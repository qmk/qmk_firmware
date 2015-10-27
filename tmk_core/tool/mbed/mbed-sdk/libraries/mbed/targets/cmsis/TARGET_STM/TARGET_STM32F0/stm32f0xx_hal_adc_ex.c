/**
  ******************************************************************************
  * @file    stm32f0xx_hal_adc_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Operation functions
  *             ++ Calibration (ADC automatic self-calibration)
  *         
  @verbatim
  ==============================================================================
                    ##### ADC specific features #####
  ==============================================================================
  [..] 
  (#) 12-bit, 10-bit, 8-bit or 6-bit configurable resolution

  (#) Interrupt generation at the end of regular conversion and in case of 
      analog watchdog or overrun events.
  
  (#) Single and continuous conversion modes.
  
  (#) Scan mode for automatic conversion of channel 0 to channel 'n'.
  
  (#) Data alignment with in-built data coherency.
  
  (#) Programmable sampling time.
  
  (#) ADC conversion group Regular.

  (#) External trigger (timer or EXTI) with configurable polarity.

  (#) DMA request generation for transfer of conversions data of regular group.

  (#) ADC calibration
  
  (#) ADC supply requirements: 2.4 V to 3.6 V at full speed and down to 1.8 V at 
      slower speed.
  
  (#) ADC input range: from Vref minud (connected to Vssa) to Vref plus(connected to 
      Vdda or to an external voltage reference).


                     ##### How to use this driver #####
  ==============================================================================
    [..]

    (#) Enable the ADC interface 
        As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured  
        at RCC top level: clock source and clock prescaler.
        Two possible clock sources: synchronous clock derived from APB clock
        or asynchronous clock derived from ADC dedicated HSI RC oscillator
        14MHz.
        Example:
          __ADC1_CLK_ENABLE();                         (mandatory)
          
          HI14 enable or let under control of ADC:     (optional)

          RCC_OscInitTypeDef   RCC_OscInitStructure;
          RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSI14;
          RCC_OscInitStructure.HSI14CalibrationValue = RCC_HSI14CALIBRATION_DEFAULT;
          RCC_OscInitStructure.HSI14State = RCC_HSI14_ADC_CONTROL;
          RCC_OscInitStructure.PLL...   (optional if used for system clock)
          HAL_RCC_OscConfig(&RCC_OscInitStructure);
          
          Parameter "HSI14State" must be set either:
           - to "...HSI14State = RCC_HSI14_ADC_CONTROL" to let the ADC control 
             the HSI14 oscillator enable/disable (if not used to supply the main 
             system clock): feature used if ADC mode LowPowerAutoPowerOff is 
             enabled.
           - to "...HSI14State = RCC_HSI14_ON" to maintain the HSI14 oscillator
             always enabled: can be used to supply the main system clock.

    (#) ADC pins configuration
         (++) Enable the clock for the ADC GPIOs using the following function:
             __GPIOx_CLK_ENABLE();   
         (++) Configure these ADC pins in analog mode using HAL_GPIO_Init();  
  
     (#) Configure the ADC parameters (conversion resolution, data alignment,  
         continuous mode, ...) using the HAL_ADC_Init() function.

     (#) Activate the ADC peripheral using one of the start functions: 
         HAL_ADC_Start(), HAL_ADC_Start_IT(), HAL_ADC_Start_DMA().
  
     *** Regular channels group configuration ***
     ============================================
     [..]    
       (+) To configure the ADC regular channels group features, use 
           HAL_ADC_Init() and HAL_ADC_ConfigChannel() functions.
       (+) To activate the continuous mode, use the HAL_ADC_Init() function.   
       (+) To read the ADC converted values, use the HAL_ADC_GetValue() function.
              
     *** DMA for Regular channels group features configuration ***
     ============================================================= 
     [..]
       (+) To enable the DMA mode for regular channels group, use the  
           HAL_ADC_Start_DMA() function.
       (+) To enable the generation of DMA requests continuously at the end of 
           the last DMA transfer, use the HAL_ADC_Init() function.
  
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
#include "stm32f0xx_hal.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @defgroup ADCEx ADCEx Extended HAL Module Driver
  * @brief ADC HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ADCEx_Private_Constants ADCEx Private Constants
  * @{
  */ 
 
/* Fixed timeout values for ADC calibration, enable settling time, disable  */
  /* settling time.                                                           */
  /* Values defined to be higher than worst cases: low clock frequency,       */
  /* maximum prescaler.                                                       */
  /* Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock         */
  /* prescaler 4.                                                             */
  /* Unit: ms                                                                 */
  #define ADC_DISABLE_TIMEOUT           2
  #define ADC_CALIBRATION_TIMEOUT       2      
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
      (+) Perform the ADC calibration. 
@endverbatim
  * @{
  */

/**
  * @brief  Perform an ADC automatic self-calibration
  *         Calibration prerequisite: ADC must be disabled (execute this
  *         function before HAL_ADC_Start() or after HAL_ADC_Stop() ).
  * @note   Calibration factor can be read after calibration, using function
  *         HAL_ADC_GetValue() (value on 7 bits: from DR[6;0]).
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  uint32_t tickstart=0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
       
  /* Calibration prerequisite: ADC must be disabled.                          */
  if (__HAL_ADC_IS_ENABLED(hadc) == RESET )
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_READY;
    
    /* Start ADC calibration */
    hadc->Instance->CR |= ADC_CR_ADCAL;

    tickstart = HAL_GetTick();  

    /* Wait for calibration completion */
    while(HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADCAL))
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
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
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
