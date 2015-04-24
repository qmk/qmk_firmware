/**
  ******************************************************************************
  * @file    stm32l0xx_hal_adc_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief  This file contains all the functions prototypes for the ADC firmware 
  *          library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_ADC_EX_H
#define __STM32L0xx_ADC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"
  
/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup ADCEx_Exported_Constants
  * @{
  */

 /** @defgroup ADCEx_TimeOut_Values
  * @{
  */ 
#define ADC_CALIBRATION_TIMEOUT       10
/**
  * @}
  */
   
  
/** @defgroup ADCEx_Channel_Mode
  * @{
  */   
#define ADC_SINGLE_ENDED                        (uint32_t)0x00000000   /* dummy value */
#define IS_ADC_SINGLE_DIFFERENTIAL(SING_DIFF)   ((SING_DIFF) == ADC_SINGLE_ENDED)
/**
  * @}
  */
    
/** @defgroup ADCEx_calibration_factor_length_verification
  * @{
  */ 
/**
  * @brief Calibration factor lenght verification (7 bits maximum)
  * @param _Calibration_Factor_: Calibration factor value
  * @retval None
  */
#define IS_ADC_CALFACT(_Calibration_Factor_) ((_Calibration_Factor_) <= ((uint32_t)0x7F))
/**
  * @}
  */ 

#define ADC_FLAG_SENSOR         SYSCFG_CFGR3_SENSOR_ADC_RDYF
#define ADC_FLAG_VREFINT        SYSCFG_VREFINT_ADC_RDYF

/**
  * @}
  */
   
/* Exported functions --------------------------------------------------------*/  
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef   HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc, uint32_t SingleDiff);
uint32_t            HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef* hadc, uint32_t SingleDiff);
HAL_StatusTypeDef   HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef* hadc, uint32_t SingleDiff, uint32_t CalibrationFactor);
void HAL_ADCEx_EnableVREFINT(void);
void HAL_ADCEx_DisableVREFINT(void);
void HAL_ADCEx_EnableVREFINTTempSensor(void);
void HAL_ADCEx_DisableVREFINTTempSensor(void);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__STM32L0xx_ADC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

