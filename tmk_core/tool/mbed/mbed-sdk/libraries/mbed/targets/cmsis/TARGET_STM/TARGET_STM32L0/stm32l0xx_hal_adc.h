/**
  ******************************************************************************
  * @file    stm32l0xx_hal_adc.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   This file contains all the functions prototypes for the ADC firmware 
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
#ifndef __STM32L0xx_ADC_H
#define __STM32L0xx_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"
   
/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/   
/** 
  * @brief  HAL State structures definition  
  */ 
typedef enum
{
  HAL_ADC_STATE_RESET                   = 0x00,    /*!< ADC not yet initialized or disabled */
  HAL_ADC_STATE_READY                   = 0x01,    /*!< ADC peripheral ready for use */
  HAL_ADC_STATE_BUSY                    = 0x02,    /*!< An internal process is ongoing */ 
  HAL_ADC_STATE_BUSY_REG                = 0x12,    /*!< Regular conversion is ongoing */
  HAL_ADC_STATE_TIMEOUT                 = 0x03,    /*!< Timeout state */
  HAL_ADC_STATE_ERROR                   = 0x04,    /*!< ADC state error */
  HAL_ADC_STATE_EOC                     = 0x05,    /*!< Conversion is completed */
  HAL_ADC_STATE_AWD                     = 0x06,    /*!< ADC state analog watchdog */
}HAL_ADC_StateTypeDef;


/** 
  * @brief  ADC Oversampler structure definition  
  */
typedef struct
{
  uint32_t Ratio;                         /*!< Configures the oversampling ratio.
                                               This parameter can be a value of @ref ADC_Oversampling_Ratio */
  uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler.
                                               This parameter can be a value of @ref ADC_Right_Bit_Shift */
  uint32_t TriggeredMode;                 /*!< Selects the regular triggered oversampling mode
                                               This parameter can be a value of @ref ADC_Triggered_Oversampling_Mode */
                                        
}ADC_OversamplingTypeDef;

/**
  * @brief  ADC Init structure definition  
  * @note   The setting of these parameters with function HAL_ADC_Init() is conditioned by the ADC state.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behaviour in case of intended action to update antother parameter (which fullfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t OversamplingMode;             /*!< Specifies whether the oversampling feature is enabled or disabled
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  ADC_OversamplingTypeDef  Oversample;   /*!< Specifies the Oversampling parameters
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t ClockPrescaler;               /*!< Selects the ADC clock frequency.
                                              This parameter can be a value of @ref ADC_ClockPrescaler
                                              Note: This parameter can be modified only if ADC is disabled. */
  uint32_t Resolution;                   /*!< Configures the ADC resolution mode. 
                                              This parameter can be a value of @ref ADC_Resolution
                                              Note: This parameter can be modified only if ADC is disabled. */
  uint32_t SamplingTime;                 /*!< The sample time value to be set for all channels.
                                              This parameter can be a value of @ref ADC_sampling_times
                                              Note: This parameter can be modified only if there is no conversion ongoing. */
  uint32_t ScanConvMode;                  /*!< The scan sequence direction.
                                              This parameter can be a value of @ref ADC_Scan_mode
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t DataAlign;                    /*!< Specifies whether the ADC data  alignment is left or right.  
                                              This parameter can be a value of @ref ADC_data_align
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t ContinuousConvMode;           /*!< Specifies whether the conversion is performed in Continuous or Single mode.
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t DiscontinuousConvMode;        /*!< Specifies whether the conversion is performed
                                              in Complete-sequence/Discontinuous-sequence.
                                              Discontinuous mode can be enabled only if continuous mode is disabled.
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t ExternalTrigConvEdge;         /*!< Select the external trigger edge and enable the trigger. 
                                              This parameter can be a value of @ref ADC_Regular_External_Trigger_Source_Edge
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t ExternalTrigConv;             /*!< Select the external event used to trigger the start of conversion.
                                              This parameter can be a value of @ref ADC_External_trigger_Source
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t DMAContinuousRequests;        /*!< Specifies whether the DMA requests are performed in one shot mode (DMA transfer stop when number of conversions is reached)
                                              or in Continuous mode (DMA transfer unlimited, whatever number of conversions).
                                              Note: In continuous mode, DMA must be configured in circular mode. Otherwise an overrun will be triggered when DMA buffer max pointer is reached.
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t EOCSelection;                 /*!< Specifies what EOC (End Of Conversion) flag is used for conversion polling and interruption:  
                                              end of single channel conversion or end of channels conversions sequence.
                                              This parameter can be a value of @ref ADC_EOCSelection */ 
  uint32_t Overrun;                      /*!< Select the behaviour in case of overrun: data preserved or overwritten 
                                              This parameter has an effect on regular channels only, including in DMA mode.
                                              This parameter can be a value of @ref ADC_Overrun
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t LowPowerAutoWait;             /*!< Specifies the usage of dynamic low power Auto Delay: new conversion start only
                                              when the previous conversion (for regular channel) is completed.
                                              This avoids risk of overrun for low frequency application. 
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t LowPowerFrequencyMode;        /*!< When selecting an analog ADC clock frequency lower than 2.8MHz,
                                              it is mandatory to first enable the Low Frequency Mode.
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
  uint32_t LowPowerAutoPowerOff;         /*!< When setting the AutoOff feature, the ADC is always powered off when not converting and automatically
                                              wakes-up when a conversion is started (by software or hardware trigger).
                                              This parameter can be set to ENABLE or DISABLE.
                                              Note: This parameter can be modified only if there is no conversion is ongoing. */
}ADC_InitTypeDef;

/** 
  * @brief  ADC handle Structure definition  
  */ 
typedef struct __ADC_HandleTypeDef
{
  ADC_TypeDef                   *Instance;              /*!< Register base address */

  ADC_InitTypeDef               Init;                   /*!< ADC required parameters */

  DMA_HandleTypeDef             *DMA_Handle;            /*!< Pointer DMA Handler */

  HAL_LockTypeDef               Lock;                   /*!< ADC locking object */

  __IO HAL_ADC_StateTypeDef     State;                  /*!< ADC communication state */

  __IO uint32_t                 ErrorCode;              /*!< ADC Error code */
}ADC_HandleTypeDef;

/** 
  * @brief  ADC Configuration regular Channel structure definition  
  */ 
typedef struct 
{
  uint32_t Channel;                /*!< the ADC channel to configure 
                                        This parameter can be a value of @ref ADC_channels */ 
}ADC_ChannelConfTypeDef;


/** 
  * @brief   ADC Configuration analog watchdog definition  
  */ 
typedef struct
{
  uint32_t WatchdogMode;      /*!< Configures the ADC analog watchdog mode: single/all channels.
                                   This parameter can be a value of @ref ADC_analog_watchdog_mode */
  uint32_t Channel;           /*!< Selects which ADC channel to monitor by analog watchdog.
                                   This parameter has an effect only if watchdog mode is configured on single channel (parameter WatchdogMode)
                                   This parameter can be a value of @ref ADC_channels */
  uint32_t ITMode;            /*!< Specifies whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */
  uint32_t HighThreshold;     /*!< Configures the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits),
                                   this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively. */
  uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits),
                                   this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively. */
}ADC_AnalogWDGConfTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */

/** @defgroup ADC_Error_Code 
  * @{
  */ 
#define HAL_ADC_ERROR_NONE        ((uint32_t)0x00)   /*!< No error           */
#define HAL_ADC_ERROR_INTERNAL    ((uint32_t)0x01)   /*!< ADC IP internal error: if problem of clocking, 
                                                          enable/disable, erroneous state */
#define HAL_ADC_ERROR_OVR         ((uint32_t)0x02)   /*!< OVR error          */
#define HAL_ADC_ERROR_DMA         ((uint32_t)0x03)   /*!< DMA transfer error */
/**
  * @}
  */  

/** @defgroup ADC_TimeOut_Values
  * @{
  */ 

  /* Fixed timeout values for ADC calibration, enable settling time, disable  */
  /* settling time.                                                           */
  /* Values defined to be higher than worst cases: low clocks freq,           */
  /* maximum prescalers.                                                      */
  /* Unit: ms                                                                 */      
#define ADC_ENABLE_TIMEOUT            10
#define ADC_DISABLE_TIMEOUT           10
#define ADC_STOP_CONVERSION_TIMEOUT   10

  /* Delay of 10us fixed to worst case: maximum CPU frequency 180MHz to have  */
  /* the minimum number of CPU cycles to fulfill this delay                   */
  #define ADC_DELAY_10US_MIN_CPU_CYCLES         1800 
/**
  * @}
  */

/** @defgroup ADC_ClockPrescaler
  * @{
  */     
#define ADC_CLOCK_ASYNC_DIV1              ((uint32_t)0x00000000)                                /*!< ADC Asynchronous clock mode divided by 1 */
#define ADC_CLOCK_ASYNC_DIV2              (ADC_CCR_PRESC_0)                                     /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV4              (ADC_CCR_PRESC_1)                                     /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV6              (ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0)                   /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV8              (ADC_CCR_PRESC_2)                                     /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV10             (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_0)                   /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV12             (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1)                   /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV16             (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0) /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV32             (ADC_CCR_PRESC_3)                                     /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV64             (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_0)                   /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV128            (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1)                   /*!< ADC Asynchronous clock mode divided by 2 */
#define ADC_CLOCK_ASYNC_DIV256            (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0) /*!< ADC Asynchronous clock mode divided by 2 */

#define ADC_CLOCK_SYNC_PCLK_DIV1         ((uint32_t)ADC_CFGR2_CKMODE_0)  /*!< Synchronous clock mode divided by 1 
                                                                               This configuration must be enabled only if PCLK has a 50%
                                                                               duty clock cycle (APB prescaler configured inside the RCC must be bypassed and the system clock
                                                                               must by 50% duty cycle)*/
#define ADC_CLOCK_SYNC_PCLK_DIV2          ((uint32_t)ADC_CFGR2_CKMODE_1)  /*!< Synchronous clock mode divided by 2 */
#define ADC_CLOCK_SYNC_PCLK_DIV4          ((uint32_t)ADC_CFGR2_CKMODE)    /*!< Synchronous clock mode divided by 4 */

#define IS_ADC_CLOCKPRESCALER(ADC_CLOCK) (((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV1) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV1) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV2) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV4) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV1  ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV2  ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV4  ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV6  ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV8  ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV10 ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV12 ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV16 ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV32 ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV64 ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV128 ) ||\
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV256))
/**                                                       
  * @}
  */ 

/** @defgroup ADC_Resolution
  * @{
  */ 
#define ADC_RESOLUTION_12B      ((uint32_t)0x00000000)          /*!<  ADC 12-bit resolution */
#define ADC_RESOLUTION_10B      ((uint32_t)ADC_CFGR1_RES_0)      /*!<  ADC 10-bit resolution */
#define ADC_RESOLUTION_8B       ((uint32_t)ADC_CFGR1_RES_1)      /*!<  ADC 8-bit resolution */
#define ADC_RESOLUTION_6B       ((uint32_t)ADC_CFGR1_RES)        /*!<  ADC 6-bit resolution */

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION_12B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_10B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_8B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_6B))

#define IS_ADC_RESOLUTION_8_6_BITS(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION_8B) || \
                                                ((RESOLUTION) == ADC_RESOLUTION_6B))
/**
  * @}
  */ 

/** @defgroup ADC_data_align
  * @{
  */ 
#define ADC_DATAALIGN_RIGHT      ((uint32_t)0x00000000)
#define ADC_DATAALIGN_LEFT       ((uint32_t)ADC_CFGR1_ALIGN)

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT))
/**
  * @}
  */ 

/** @defgroup ADC_Regular_External_Trigger_Source_Edge ADC External Trigger Source Edge for Regular Group
  * @{
  */ 
#define ADC_EXTERNALTRIGCONVEDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGCONVEDGE_RISING         ((uint32_t)ADC_CFGR1_EXTEN_0)         
#define ADC_EXTERNALTRIGCONVEDGE_FALLING        ((uint32_t)ADC_CFGR1_EXTEN_1)
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING  ((uint32_t)ADC_CFGR1_EXTEN)

#define IS_ADC_EXTTRIG_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGCONVEDGE_NONE) || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING) || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_FALLING) || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING))
/**
  * @}
  */ 

/** @defgroup ADC_External_trigger_Source
  * @{
  */
#define ADC_EXTERNALTRIGCONV_T6_TRGO               ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGCONV_T21_CC2               ADC_CFGR1_EXTSEL_0
#define ADC_EXTERNALTRIGCONV_T2_TRGO               ADC_CFGR1_EXTSEL_1
#define ADC_EXTERNALTRIGCONV_T2_CC4                ((uint32_t)0x000000C0)
#define ADC_EXTERNALTRIGCONV_T22_TRGO              ADC_CFGR1_EXTSEL_2
#define ADC_EXTERNALTRIGCONV_EXT_IT11              ADC_CFGR1_EXTSEL

#define IS_ADC_EXTERNAL_TRIG_CONV(CONV) (((CONV) == ADC_EXTERNALTRIGCONV_T6_TRGO  )  || \
                                         ((CONV) == ADC_EXTERNALTRIGCONV_T21_CC2  )  || \
                                         ((CONV) == ADC_EXTERNALTRIGCONV_T2_TRGO  )  || \
                                         ((CONV) == ADC_EXTERNALTRIGCONV_T2_CC4   )  || \
                                         ((CONV) == ADC_EXTERNALTRIGCONV_T22_TRGO )  || \
                                         ((CONV) == ADC_EXTERNALTRIGCONV_EXT_IT11 ))

/**
  * @}
  */ 

/** @defgroup ADC_EOCSelection
  * @{
  */ 
#define ADC_EOC_SINGLE_CONV         ((uint32_t) ADC_ISR_EOC)
#define ADC_EOC_SEQ_CONV            ((uint32_t) ADC_ISR_EOS)
#define ADC_EOC_SINGLE_SEQ_CONV    ((uint32_t)(ADC_ISR_EOC | ADC_ISR_EOS))  /*!< reserved for future use */

#define IS_ADC_EOC_SELECTION(EOC_SELECTION) (((EOC_SELECTION) == ADC_EOC_SINGLE_CONV)   || \
                                             ((EOC_SELECTION) == ADC_EOC_SEQ_CONV)      || \
                                             ((EOC_SELECTION) == ADC_EOC_SINGLE_SEQ_CONV))
/**
  * @}
  */ 

/** @defgroup ADC_Overrun
  * @{
  */ 
#define ADC_OVR_DATA_PRESERVED              ((uint32_t)0x00000000)
#define ADC_OVR_DATA_OVERWRITTEN            ((uint32_t)ADC_CFGR1_OVRMOD)

#define IS_ADC_OVERRUN(OVR) (((OVR) == ADC_OVR_DATA_PRESERVED) || \
                             ((OVR) == ADC_OVR_DATA_OVERWRITTEN))
/**
  * @}
  */ 

/** @defgroup ADC_channels
  * @{
  */
#define ADC_CHANNEL_0           ((uint32_t)(ADC_CHSELR_CHSEL0))
#define ADC_CHANNEL_1           ((uint32_t)(ADC_CHSELR_CHSEL1) | ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_2           ((uint32_t)(ADC_CHSELR_CHSEL2) | ADC_CFGR1_AWDCH_1)
#define ADC_CHANNEL_3           ((uint32_t)(ADC_CHSELR_CHSEL3)| ADC_CFGR1_AWDCH_1 | ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_4           ((uint32_t)(ADC_CHSELR_CHSEL4)| ADC_CFGR1_AWDCH_2)
#define ADC_CHANNEL_5           ((uint32_t)(ADC_CHSELR_CHSEL5)| ADC_CFGR1_AWDCH_2| ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_6           ((uint32_t)(ADC_CHSELR_CHSEL6)| ADC_CFGR1_AWDCH_2| ADC_CFGR1_AWDCH_1)
#define ADC_CHANNEL_7           ((uint32_t)(ADC_CHSELR_CHSEL7)| ADC_CFGR1_AWDCH_2| ADC_CFGR1_AWDCH_1 | ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_8           ((uint32_t)(ADC_CHSELR_CHSEL8)| ADC_CFGR1_AWDCH_3)
#define ADC_CHANNEL_9           ((uint32_t)(ADC_CHSELR_CHSEL9)| ADC_CFGR1_AWDCH_3| ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_10          ((uint32_t)(ADC_CHSELR_CHSEL10)| ADC_CFGR1_AWDCH_3| ADC_CFGR1_AWDCH_1)
#define ADC_CHANNEL_11          ((uint32_t)(ADC_CHSELR_CHSEL11)| ADC_CFGR1_AWDCH_3| ADC_CFGR1_AWDCH_1| ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_12          ((uint32_t)(ADC_CHSELR_CHSEL12)| ADC_CFGR1_AWDCH_3| ADC_CFGR1_AWDCH_2)
#define ADC_CHANNEL_13          ((uint32_t)(ADC_CHSELR_CHSEL13)| ADC_CFGR1_AWDCH_3| ADC_CFGR1_AWDCH_2| ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_14          ((uint32_t)(ADC_CHSELR_CHSEL14)| ADC_CFGR1_AWDCH_3| ADC_CFGR1_AWDCH_2| ADC_CFGR1_AWDCH_1)
#define ADC_CHANNEL_15          ((uint32_t)(ADC_CHSELR_CHSEL15)| ADC_CFGR1_AWDCH_3| ADC_CFGR1_AWDCH_2| ADC_CFGR1_AWDCH_1| ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_16          ((uint32_t)(ADC_CHSELR_CHSEL16)| ADC_CFGR1_AWDCH_4)
#define ADC_CHANNEL_17          ((uint32_t)(ADC_CHSELR_CHSEL17)| ADC_CFGR1_AWDCH_4| ADC_CFGR1_AWDCH_0)
#define ADC_CHANNEL_18          ((uint32_t)(ADC_CHSELR_CHSEL18)| ADC_CFGR1_AWDCH_4| ADC_CFGR1_AWDCH_1)

/* Internal channels */
#define ADC_CHANNEL_VLCD         ADC_CHANNEL_16    
#define ADC_CHANNEL_VREFINT      ADC_CHANNEL_17
#define ADC_CHANNEL_TEMPSENSOR   ADC_CHANNEL_18    

    
#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_0)           || \
                                 ((CHANNEL) == ADC_CHANNEL_1)           || \
                                 ((CHANNEL) == ADC_CHANNEL_2)           || \
                                 ((CHANNEL) == ADC_CHANNEL_3)           || \
                                 ((CHANNEL) == ADC_CHANNEL_4)           || \
                                 ((CHANNEL) == ADC_CHANNEL_5)           || \
                                 ((CHANNEL) == ADC_CHANNEL_6)           || \
                                 ((CHANNEL) == ADC_CHANNEL_7)           || \
                                 ((CHANNEL) == ADC_CHANNEL_8)           || \
                                 ((CHANNEL) == ADC_CHANNEL_9)           || \
                                 ((CHANNEL) == ADC_CHANNEL_10)          || \
                                 ((CHANNEL) == ADC_CHANNEL_11)          || \
                                 ((CHANNEL) == ADC_CHANNEL_12)          || \
                                 ((CHANNEL) == ADC_CHANNEL_13)          || \
                                 ((CHANNEL) == ADC_CHANNEL_14)          || \
                                 ((CHANNEL) == ADC_CHANNEL_15)          || \
                                 ((CHANNEL) == ADC_CHANNEL_TEMPSENSOR)  || \
                                 ((CHANNEL) == ADC_CHANNEL_VREFINT)     || \
                                 ((CHANNEL) == ADC_CHANNEL_VLCD))

/**
  * @}
  */

/** @defgroup ADC_Channel_AWD_Masks
  * @{
  */
#define ADC_CHANNEL_MASK        ((uint32_t)0x0007FFFF)
#define ADC_CHANNEL_AWD_MASK    ((uint32_t)0x7C000000)
/**
  * @}
  */


/** @defgroup ADC_sampling_times
  * @{
  */
    
#define ADC_SAMPLETIME_1CYCLE_5       ((uint32_t)0x00000000)                          /*!<  ADC sampling time 1.5 cycle */
#define ADC_SAMPLETIME_7CYCLES_5      ((uint32_t)ADC_SMPR_SMPR_0)                     /*!<  ADC sampling time 7.5 CYCLES */
#define ADC_SAMPLETIME_13CYCLES_5     ((uint32_t)ADC_SMPR_SMPR_1)                     /*!<  ADC sampling time 13.5 CYCLES */
#define ADC_SAMPLETIME_28CYCLES_5     ((uint32_t)(ADC_SMPR_SMPR_1 | ADC_SMPR_SMPR_0)) /*!<  ADC sampling time 28.5 CYCLES */
#define ADC_SAMPLETIME_41CYCLES_5     ((uint32_t)ADC_SMPR_SMPR_2)                     /*!<  ADC sampling time 41.5 CYCLES */
#define ADC_SAMPLETIME_55CYCLES_5     ((uint32_t)(ADC_SMPR_SMPR_2 | ADC_SMPR_SMPR_0)) /*!<  ADC sampling time 55.5 CYCLES */
#define ADC_SAMPLETIME_71CYCLES_5     ((uint32_t)(ADC_SMPR_SMPR_2 | ADC_SMPR_SMPR_1)) /*!<  ADC sampling time 71.5 CYCLES */
#define ADC_SAMPLETIME_239CYCLES_5    ((uint32_t)ADC_SMPR_SMPR)                       /*!<  ADC sampling time 239.5 CYCLES */

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_1CYCLE_5   ) || \
                                  ((TIME) == ADC_SAMPLETIME_7CYCLES_5  ) || \
                                  ((TIME) == ADC_SAMPLETIME_13CYCLES_5 ) || \
                                  ((TIME) == ADC_SAMPLETIME_28CYCLES_5 ) || \
                                  ((TIME) == ADC_SAMPLETIME_41CYCLES_5 ) || \
                                  ((TIME) == ADC_SAMPLETIME_55CYCLES_5 ) || \
                                  ((TIME) == ADC_SAMPLETIME_71CYCLES_5 ) || \
                                  ((TIME) == ADC_SAMPLETIME_239CYCLES_5))
/**
  * @}
  */


/** @defgroup ADC_Scan_mode ADC Scan mode
  * @{
  */
/* Note: Scan mode values must be compatible with other STM32 devices having  */
/*       a configurable sequencer.                                            */
/*       Scan direction setting values are defined by taking in account       */
/*       already defined values for other STM32 devices:                      */
/*         ADC_SCAN_DISABLE         ((uint32_t)0x00000000)                    */
/*         ADC_SCAN_ENABLE          ((uint32_t)0x00000001)                    */
/*       Scan direction forward is considered as default setting equivalent   */
/*       to scan enable.                                                      */
/*       Scan direction backward is considered as additional setting.         */
/*       In case of migration from another STM32 device, the user will be     */
/*       warned of change of setting choices with assert check.               */
#define ADC_SCAN_DIRECTION_FORWARD        ((uint32_t)0x00000001)        /*!< Scan direction forward: from channel 0 to channel 18 */
#define ADC_SCAN_DIRECTION_BACKWARD       ((uint32_t)0x00000002)        /*!< Scan direction backward: from channel 18 to channel 0 */

#define ADC_SCAN_ENABLE         ADC_SCAN_DIRECTION_FORWARD             /* For compatibility with other STM32 devices */

#define IS_ADC_SCAN_MODE(SCAN_MODE) (((SCAN_MODE) == ADC_SCAN_DIRECTION_FORWARD) || \
                                     ((SCAN_MODE) == ADC_SCAN_DIRECTION_BACKWARD))

/**
  * @}
  */

/** @defgroup ADC_Oversampling_Ratio
  * @{
  */

#define ADC_OVERSAMPLING_RATIO_2                    ((uint32_t)0x00000000)  /*!<  ADC Oversampling ratio 2x */
#define ADC_OVERSAMPLING_RATIO_4                    ((uint32_t)0x00000004)  /*!<  ADC Oversampling ratio 4x */
#define ADC_OVERSAMPLING_RATIO_8                    ((uint32_t)0x00000008)  /*!<  ADC Oversampling ratio 8x */
#define ADC_OVERSAMPLING_RATIO_16                   ((uint32_t)0x0000000C)  /*!<  ADC Oversampling ratio 16x */
#define ADC_OVERSAMPLING_RATIO_32                   ((uint32_t)0x00000010)  /*!<  ADC Oversampling ratio 32x */
#define ADC_OVERSAMPLING_RATIO_64                   ((uint32_t)0x00000014)  /*!<  ADC Oversampling ratio 64x */
#define ADC_OVERSAMPLING_RATIO_128                  ((uint32_t)0x00000018)  /*!<  ADC Oversampling ratio 128x */
#define ADC_OVERSAMPLING_RATIO_256                  ((uint32_t)0x0000001C)  /*!<  ADC Oversampling ratio 256x */
#define IS_ADC_OVERSAMPLING_RATIO(RATIO)          (((RATIO) == ADC_OVERSAMPLING_RATIO_2   ) || \
                                                   ((RATIO) == ADC_OVERSAMPLING_RATIO_4   ) || \
                                                   ((RATIO) == ADC_OVERSAMPLING_RATIO_8   ) || \
                                                   ((RATIO) == ADC_OVERSAMPLING_RATIO_16  ) || \
                                                   ((RATIO) == ADC_OVERSAMPLING_RATIO_32  ) || \
                                                   ((RATIO) == ADC_OVERSAMPLING_RATIO_64  ) || \
                                                   ((RATIO) == ADC_OVERSAMPLING_RATIO_128 ) || \
                                                   ((RATIO) == ADC_OVERSAMPLING_RATIO_256 ))
/**
  * @}
  */

/** @defgroup ADC_Right_Bit_Shift
  * @{
  */
#define ADC_RIGHTBITSHIFT_NONE                       ((uint32_t)0x00000000)  /*!<  ADC No bit shift for oversampling */
#define ADC_RIGHTBITSHIFT_1                          ((uint32_t)0x00000020)  /*!<  ADC 1 bit shift for oversampling */
#define ADC_RIGHTBITSHIFT_2                          ((uint32_t)0x00000040)  /*!<  ADC 2 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_3                          ((uint32_t)0x00000060)  /*!<  ADC 3 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_4                          ((uint32_t)0x00000080)  /*!<  ADC 4 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_5                          ((uint32_t)0x000000A0)  /*!<  ADC 5 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_6                          ((uint32_t)0x000000C0)  /*!<  ADC 6 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_7                          ((uint32_t)0x000000E0)  /*!<  ADC 7 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_8                          ((uint32_t)0x00000100)  /*!<  ADC 8 bits shift for oversampling */
#define IS_ADC_RIGHT_BIT_SHIFT(SHIFT)               (((SHIFT) == ADC_RIGHTBITSHIFT_NONE) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_1   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_2   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_3   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_4   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_5   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_6   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_7   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_8   ))
/**
  * @}
  */

/** @defgroup ADC_Triggered_Oversampling_Mode
  * @{
  */
#define ADC_TRIGGEREDMODE_SINGLE_TRIGGER            ((uint32_t)0x00000000)  /*!<  ADC No bit shift for oversampling */
#define ADC_TRIGGEREDMODE_MULTI_TRIGGER             ((uint32_t)0x00000200)  /*!<  ADC No bit shift for oversampling */
#define IS_ADC_TRIGGERED_OVERSAMPLING_MODE(MODE)     (((MODE) == ADC_TRIGGEREDMODE_SINGLE_TRIGGER) || \
                                                      ((MODE) == ADC_TRIGGEREDMODE_MULTI_TRIGGER) )
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_mode
  * @{
  */ 
#define ADC_ANALOGWATCHDOG_NONE                     ((uint32_t) 0x00000000)
#define ADC_ANALOGWATCHDOG_SINGLE_REG               ((uint32_t)(ADC_CFGR1_AWDSGL | ADC_CFGR1_AWDEN))
#define ADC_ANALOGWATCHDOG_ALL_REG                  ((uint32_t) ADC_CFGR1_AWDEN)
                                                  
                                                  
#define IS_ADC_ANALOG_WATCHDOG_MODE(WATCHDOG)     (((WATCHDOG) == ADC_ANALOGWATCHDOG_NONE      )   || \
                                                   ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REG)   || \
                                                   ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REG   ))
/**
  * @}
  */

/** @defgroup ADC_conversion_type
  * @{
  */ 
#define ADC_REGULAR_GROUP                         ((uint32_t)(ADC_FLAG_EOC | ADC_FLAG_EOS))                                              
#define IS_ADC_CONVERSION_GROUP(CONVERSION)   ((CONVERSION) == ADC_REGULAR_GROUP)
/**
  * @}
  */

/** @defgroup ADC_Event_type
  * @{
  */ 
#define ADC_AWD_EVENT              ((uint32_t)ADC_FLAG_AWD)
#define ADC_OVR_EVENT              ((uint32_t)ADC_FLAG_OVR)
    
#define IS_ADC_EVENT_TYPE(EVENT) (((EVENT) == ADC_AWD_EVENT) || \
                                  ((EVENT) == ADC_OVR_EVENT))
/**
  * @}
  */
  
/** @defgroup ADC_interrupts_definition
  * @{
  */
#define ADC_IT_RDY           ADC_IER_ADRDYIE     /*!< ADC Ready (ADRDY) interrupt source */
#define ADC_IT_EOSMP         ADC_IER_EOSMPIE     /*!< ADC End of Sampling interrupt source */
#define ADC_IT_EOC           ADC_IER_EOCIE       /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_EOS           ADC_IER_EOSEQIE     /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IT_OVR           ADC_IER_OVRIE       /*!< ADC overrun interrupt source */
#define ADC_IT_AWD           ADC_IER_AWDIE       /*!< ADC Analog watchdog 1 interrupt source */
#define ADC_IT_EOCAL         ADC_IER_EOCALIE     /*!< ADC End of Calibration interrupt source */

/* Check of single flag */
#define IS_ADC_IT(IT) (((IT) == ADC_IT_AWD)   || ((IT) == ADC_IT_RDY) || \
                       ((IT) == ADC_IT_EOSMP) || ((IT) == ADC_IT_EOC) || \
                       ((IT) == ADC_IT_EOS)   || ((IT) == ADC_IT_OVR))
/**
  * @}
  */ 

  

/** @defgroup ADC_flags_definition
  * @{
  */
#define ADC_FLAG_RDY           ADC_ISR_ADRDY    /*!< ADC Ready (ADRDY) flag */
#define ADC_FLAG_EOSMP         ADC_ISR_EOSMP    /*!< ADC End of Sampling flag */
#define ADC_FLAG_EOC           ADC_ISR_EOC      /*!< ADC End of Regular Conversion flag */
#define ADC_FLAG_EOS           ADC_ISR_EOSEQ    /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_FLAG_OVR           ADC_ISR_OVR      /*!< ADC overrun flag */
#define ADC_FLAG_AWD           ADC_ISR_AWD      /*!< ADC Analog watchdog flag */
#define ADC_FLAG_EOCAL         ADC_ISR_EOCAL    /*!< ADC Enf Of Calibration flag */


#define ADC_FLAG_ALL    (ADC_FLAG_RDY | ADC_FLAG_EOSMP | ADC_FLAG_EOC | ADC_FLAG_EOS |  \
                         ADC_FLAG_OVR | ADC_FLAG_AWD   | ADC_FLAG_EOCAL)

/* Check of single flag */
#define IS_ADC_FLAG(FLAG) (((FLAG) == ADC_FLAG_RDY)  || ((FLAG) == ADC_FLAG_EOSMP) || \
                           ((FLAG) == ADC_FLAG_EOC)  || ((FLAG) == ADC_FLAG_EOS)   || \
                           ((FLAG) == ADC_FLAG_OVR)  || ((FLAG) == ADC_FLAG_AWD)   || \
                           ((FLAG) == ADC_FLAG_EOCAL))
/**
  * @}
  */


/** @defgroup ADC_range_verification
  * in function of ADC resolution selected (12, 10, 8 or 6 bits)
  * @{
  */ 
#define IS_ADC_RANGE(RESOLUTION, ADC_VALUE)                                     \
   ((((RESOLUTION) == ADC_RESOLUTION_12B) && ((ADC_VALUE) <= ((uint32_t)0x0FFF))) || \
    (((RESOLUTION) == ADC_RESOLUTION_10B) && ((ADC_VALUE) <= ((uint32_t)0x03FF))) || \
    (((RESOLUTION) == ADC_RESOLUTION_8B)  && ((ADC_VALUE) <= ((uint32_t)0x00FF))) || \
    (((RESOLUTION) == ADC_RESOLUTION_6B)  && ((ADC_VALUE) <= ((uint32_t)0x003F))))
/**
  * @}
  */ 

/** @defgroup ADC_regular_nb_conv_verification
  * @{
  */ 
#define IS_ADC_REGULAR_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)16)))
/**
  * @}
  */

/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
     
/** @defgroup ADC_Exported_Macro
  * @{
  */
/** @brief Reset ADC handle state
  * @param  __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_ADC_STATE_RESET)

/**
  * @brief Enable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR |= ADC_CR_ADEN)

/**
  * @brief Verification of hardware constraints before ADC can be enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC can be enabled) or RESET (ADC cannot be enabled)
  */
#define ADC_ENABLING_CONDITIONS(__HANDLE__)           \
       (( ( ((__HANDLE__)->Instance->CR) &                  \
            (ADC_CR_ADCAL | ADC_CR_ADSTP | ADC_CR_ADSTART | \
             ADC_CR_ADDIS | ADC_CR_ADEN )                   \
           ) == RESET                                       \
        ) ? SET : RESET)

/**
  * @brief Disable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_DISABLE(__HANDLE__)                                          \
  do{                                                                          \
         (__HANDLE__)->Instance->CR |= ADC_CR_ADDIS;                           \
          __HAL_ADC_CLEAR_FLAG((__HANDLE__), (ADC_FLAG_EOSMP | ADC_FLAG_RDY)); \
  } while(0)
    
/**
  * @brief Verification of hardware constraints before ADC can be disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC can be disabled) or RESET (ADC cannot be disabled)
  */
#define ADC_DISABLING_CONDITIONS(__HANDLE__)                             \
       (( ( ((__HANDLE__)->Instance->CR) &                                     \
            (ADC_CR_ADSTART | ADC_CR_ADEN)) == ADC_CR_ADEN   \
        ) ? SET : RESET)
         
/**
  * @brief Verification of ADC state: enabled or disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
#define ADC_IS_ENABLE(__HANDLE__)                                                    \
       (( ((((__HANDLE__)->Instance->CR) & (ADC_CR_ADEN | ADC_CR_ADDIS)) == ADC_CR_ADEN) && \
          ((((__HANDLE__)->Instance->ISR) & ADC_FLAG_RDY) == ADC_FLAG_RDY)                  \
        ) ? SET : RESET)
         
/**
  * @brief Returns resolution bits in CFGR register: RES[1:0]. Return value among parameter to @ref ADC_Resolution.
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define ADC_GET_RESOLUTION(__HANDLE__) (((__HANDLE__)->Instance->CFGR1) & ADC_CFGR1_RES)

/**
  * @brief Check if no conversion is ongoing on regular groups
  * @param __HANDLE__: ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define ADC_IS_CONVERSION_ONGOING(__HANDLE__) \
       (( (((__HANDLE__)->Instance->CR) & (ADC_CR_ADSTART)) == RESET ) ? RESET : SET)
 
/**
  * @brief Enable ADC continuous conversion mode.
  * @param _CONTINUOUS_MODE_: Continuous mode.
  * @retval None
  */
#define ADC_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << 13)

/**
  * @brief Enable ADC scan mode to convert multiple ranks with sequencer.
  * @param _SCAN_MODE_: Scan conversion mode.
  * @retval None
  */
#define ADC_SCANDIR(_SCAN_MODE_)                                   \
  ( ( (_SCAN_MODE_) == (ADC_SCAN_DIRECTION_BACKWARD)                           \
    )? (ADC_CFGR1_SCANDIR) : (0x00000000)                                      \
  )

/**
  * @brief Configures the number of discontinuous conversions for the regular group channels.
  * @param _NBR_DISCONTINUOUS_CONV_: Number of discontinuous conversions.
  * @retval None
  */
#define __HAL_ADC_CFGR1_DISCONTINUOUS_NUM(_NBR_DISCONTINUOUS_CONV_) (((_NBR_DISCONTINUOUS_CONV_) - 1) << 17)

/**
  * @brief Enable the ADC DMA continuous request.
  * @param _DMAContReq_MODE_: DMA continuous request mode.
  * @retval None
  */
#define ADC_DMACONTREQ(_DMAContReq_MODE_) ((_DMAContReq_MODE_) << 1)

/**
  * @brief Enable the ADC Auto Delay.
  * @param _AutoDelay_: Auto delay bit enable or disable.
  * @retval None
  */
#define __HAL_ADC_CFGR1_AutoDelay(_AutoDelay_) ((_AutoDelay_) << 14)

/**
  * @brief Enable the ADC LowPowerAutoPowerOff.
  * @param _AUTOFF_: AutoOff bit enable or disable.
  * @retval None
  */
#define __HAL_ADC_CFGR1_AUTOFF(_AUTOFF_) ((_AUTOFF_) << 15)
          
/**
  * @brief Configure the analog watchdog high threshold into registers TR1, TR2 or TR3.
  * @param _Threshold_: Threshold value
  * @retval None
  */
#define ADC_TRX_HIGHTHRESHOLD(_Threshold_) ((_Threshold_) << 16)

          /**
  * @brief Enable the ADC Low Frequency mode.
  * @param _LOW_FREQUENCY_MODE_: Low Frequency mode.
  * @retval None
  */
#define __HAL_ADC_CCR_LOWFREQUENCY(_LOW_FREQUENCY_MODE_) ((_LOW_FREQUENCY_MODE_) << 25)
    
/**
  * @brief Shift the offset in function of the selected ADC resolution. 
  *        Offset has to be left-aligned on bit 11, the LSB (right bits) are set to 0
  *        If resolution 12 bits, no shift.
  *        If resolution 10 bits, shift of 2 ranks on the right.
  *        If resolution 8 bits, shift of 4 ranks on the right.
  *        If resolution 6 bits, shift of 6 ranks on the right.
  *        therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2))
  * @param __HANDLE__: ADC handle.
  * @param _Offset_: Value to be shifted
  * @retval None
  */
#define ADC_OFFSET_SHIFT_RESOLUTION(__HANDLE__, _Offset_) \
        ((_Offset_) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR1_RES) >> 3)*2))

/**
  * @brief Shift the AWD1 threshold in function of the selected ADC resolution.
  *        Thresholds have to be left-aligned on bit 11, the LSB (right bits) are set to 0
  *        If resolution 12 bits, no shift.
  *        If resolution 10 bits, shift of 2 ranks on the right.
  *        If resolution 8 bits, shift of 4 ranks on the right.
  *        If resolution 6 bits, shift of 6 ranks on the right.
  *        therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2))
  * @param __HANDLE__: ADC handle.
  * @param _Threshold_: Value to be shifted
  * @retval None
  */
#define ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, _Threshold_) \
        ((_Threshold_) << ((((__HANDLE__)->Instance->CFGR1 & ADC_CFGR1_RES) >> 3)*2))
       
/**
  * @brief Shift the value on the left, less significant are set to 0. 
  * @param _Value_: Value to be shifted
  * @param _Shift_: Number of shift to be done
  * @retval None
  */
#define __HAL_ADC_Value_Shift_left(_Value_, _Shift_) ((_Value_) << (_Shift_))


/**
  * @brief Enable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle.
  * @param __INTERRUPT__: ADC Interrupt.
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->IER) |= (__INTERRUPT__))

/**
  * @brief Disable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle.
  * @param __INTERRUPT__: ADC interrupt.
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->IER) &= ~(__INTERRUPT__))

/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__: specifies the ADC Handle.
  * @param __INTERRUPT__: specifies the ADC interrupt source to check.
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @brief Clear the ADC's pending flags
  * @param __HANDLE__: ADC handle.
  * @param __FLAG__: ADC flag.
  * @retval None
  */
/* Note: bit cleared bit by writing 1 */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR) = (__FLAG__))

/**
  * @brief Get the selected ADC's flag status.
  * @param __HANDLE__: ADC handle.
  * @param __FLAG__: ADC flag.
  * @retval None
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->ISR) & (__FLAG__)) == (__FLAG__))

    
   
/**
  * @brief Configuration of ADC clock & prescaler: clock source PCLK or Asynchronous with selectable prescaler
  * @param __HANDLE__: ADC handle
  * @retval None
  */

#define __HAL_ADC_CLOCK_PRESCALER(__HANDLE__)                                       \
  do{                                                                               \
      if ((((__HANDLE__)->Init.ClockPrescaler) == ADC_CLOCK_SYNC_PCLK_DIV1) ||  \
          (((__HANDLE__)->Init.ClockPrescaler) == ADC_CLOCK_SYNC_PCLK_DIV2) ||  \
          (((__HANDLE__)->Init.ClockPrescaler) == ADC_CLOCK_SYNC_PCLK_DIV4))    \
      {                                                                             \
        (__HANDLE__)->Instance->CFGR2 &= ~(ADC_CFGR2_CKMODE);                       \
        (__HANDLE__)->Instance->CFGR2 |=  (__HANDLE__)->Init.ClockPrescaler;        \
      }                                                                             \
      else                                                                          \
      {                                                                             \
        /* CKMOD bits must be reset */                                              \
        (__HANDLE__)->Instance->CFGR2 &= ~(ADC_CFGR2_CKMODE);                       \
        ADC->CCR &= ~(ADC_CCR_PRESC);                                               \
        ADC->CCR |=  (__HANDLE__)->Init.ClockPrescaler;                             \
      }                                                                             \
  } while(0)

 /**
  * @}
  */
         
/* Include ADC HAL Extension module */
#include "stm32l0xx_hal_adc_ex.h"
    
/* Exported functions --------------------------------------------------------*/  
/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef    HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef    HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void                 HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void                 HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);

/* IO operation functions  *****************************************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef    HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef    HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef    HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);                 
HAL_StatusTypeDef    HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout);
                     
/* Non-blocking mode: Interruption */
HAL_StatusTypeDef    HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef    HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);
                     
/* Non-blocking mode: DMA */
HAL_StatusTypeDef    HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);
HAL_StatusTypeDef    HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);
                     
/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t             HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);
                     
/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
void                 HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void                 HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
void                 HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc);
void                 HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);

/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef    HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);
HAL_StatusTypeDef    HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);

/* Peripheral State functions *************************************************/
HAL_ADC_StateTypeDef HAL_ADC_GetState(ADC_HandleTypeDef* hadc);
uint32_t             HAL_ADC_GetError(ADC_HandleTypeDef *hadc);


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
