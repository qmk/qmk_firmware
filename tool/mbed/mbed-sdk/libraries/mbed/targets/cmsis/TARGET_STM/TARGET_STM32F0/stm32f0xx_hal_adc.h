/**
  ******************************************************************************
  * @file    stm32f0xx_hal_adc.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file containing functions prototypes of ADC HAL library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_HAL_ADC_H
#define __STM32F0xx_HAL_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"  

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup ADC_Exported_Types ADC Exported Types
  * @{
  */
     
/**
  * @brief  Structure definition of ADC initialization and regular group  
  * @note   The setting of these parameters with function HAL_ADC_Init() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled (this is the only possible ADC state to modify parameter 'ClockPrescaler')
   *         - For all parameters except 'ClockPrescaler': ADC enabled without conversion on going on regular group.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behaviour in case of intended action to update another parameter (which fulfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t ClockPrescaler;        /*!< Select ADC clock source (synchronous clock derived from APB clock or asynchronous clock derived from ADC dedicated HSI RC oscillator 14MHz) and clock prescaler.
                                       This parameter can be a value of @ref ADC_ClockPrescaler
                                       Note: In case of usage of the ADC dedicated HSI RC oscillator, it must be preliminarily enabled at RCC top level. 
                                       Note: This parameter can be modified only if the ADC is disabled */
  uint32_t Resolution;            /*!< Configures the ADC resolution. 
                                       This parameter can be a value of @ref ADC_Resolution */
  uint32_t DataAlign;             /*!< Specifies whether the ADC data  alignment is left or right.  
                                       This parameter can be a value of @ref ADC_Data_align */
  uint32_t ScanConvMode;          /*!< Configures the sequencer of regular group.
                                       This parameter can be associated to parameter 'DiscontinuousConvMode' to have main sequence subdivided in successive parts.
                                       Sequencer is automatically enabled if several channels are set (sequencer cannot be disabled, as it can be the case on other STM32 devices):
                                       If only 1 channel is set: Conversion is performed in single mode.
                                       If several channels are set:  Conversions are performed in sequence mode (ranks defined by each channel number: channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
                                                                     Scan direction can be set to forward (from channel 0 to channel 18) or backward (from channel 18 to channel 0).
                                       This parameter can be a value of @ref ADC_Scan_mode */
  uint32_t EOCSelection;          /*!< Specifies what EOC (End Of Conversion) flag is used for conversion by polling and interruption: end of conversion of each rank or complete sequence.
                                       This parameter can be a value of @ref ADC_EOCSelection. */ 
  uint32_t LowPowerAutoWait;      /*!< Selects the dynamic low power Auto Delay: new conversion start only when the previous
                                       conversion (for regular group) or previous sequence (for injected group) has been treated by user software.
                                       This feature automatically adapts the speed of ADC to the speed of the system that reads the data. Moreover, this avoids risk of overrun for low frequency applications. 
                                       This parameter can be set to ENABLE or DISABLE.
                                       Note: Do not use with interruption or DMA (HAL_ADC_Start_IT(), HAL_ADC_Start_DMA()) since they have to clear immediately the EOC flag to free the IRQ vector sequencer.
                                             Do use with polling: 1. Start conversion with HAL_ADC_Start(), 2. Later on, when conversion data is needed: use HAL_ADC_PollForConversion() to ensure that conversion is completed
                                             and use HAL_ADC_GetValue() to retrieve conversion result and trig another conversion. */
  uint32_t LowPowerAutoPowerOff;  /*!< Selects the auto-off mode: the ADC automatically powers-off after a conversion and automatically wakes-up when a new conversion is triggered (with startup time between trigger and start of sampling).
                                       This feature can be combined with automatic wait mode (parameter 'LowPowerAutoWait').
                                       This parameter can be set to ENABLE or DISABLE.
                                       Note: If enabled, this feature also turns off the ADC dedicated 14 MHz RC oscillator (HSI14) */
  uint32_t ContinuousConvMode;    /*!< Specifies whether the conversion is performed in single mode (one conversion) or continuous mode for regular group,
                                       after the selected trigger occurred (software start or external trigger).
                                       This parameter can be set to ENABLE or DISABLE. */
  uint32_t DiscontinuousConvMode; /*!< Specifies whether the conversions sequence of regular group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                       Discontinuous mode is used only if sequencer is enabled (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                       Discontinuous mode can be enabled only if continuous mode is disabled. If continuous mode is enabled, this parameter setting is discarded.
                                       This parameter can be set to ENABLE or DISABLE
                                       Note: Number of discontinuous ranks increment is fixed to one-by-one. */
  uint32_t ExternalTrigConv;      /*!< Selects the external event used to trigger the conversion start of regular group.
                                       If set to ADC_SOFTWARE_START, external triggers are disabled.
                                       This parameter can be a value of @ref ADC_External_trigger_source_Regular */
  uint32_t ExternalTrigConvEdge;  /*!< Selects the external trigger edge of regular group.
                                       If trigger is set to ADC_SOFTWARE_START, this parameter is discarded.
                                       This parameter can be a value of @ref ADC_External_trigger_edge_Regular */
  uint32_t DMAContinuousRequests; /*!< Specifies whether the DMA requests are performed in one shot mode (DMA transfer stop when number of conversions is reached)
                                       or in Continuous mode (DMA transfer unlimited, whatever number of conversions).
                                       Note: In continuous mode, DMA must be configured in circular mode. Otherwise an overrun will be triggered when DMA buffer maximum pointer is reached.
                                       This parameter can be set to ENABLE or DISABLE. */
  uint32_t Overrun;               /*!< Select the behaviour in case of overrun: data preserved or overwritten 
                                       This parameter has an effect on regular group only, including in DMA mode.
                                       This parameter can be a value of @ref ADC_Overrun */
}ADC_InitTypeDef;

/** 
  * @brief  Structure definition of ADC channel for regular group  
  * @note   The setting of these parameters with function HAL_ADC_ConfigChannel() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled or enabled without conversion on going on regular group.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behaviour in case of intended action to update another parameter (which fulfills the ADC state condition) on the fly).
  */
typedef struct 
{
  uint32_t Channel;                /*!< Specifies the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADC_channels
                                        Note: Depending on devices, some channels may not be available on package pins. Refer to device datasheet for channels availability. */
  uint32_t Rank;                   /*!< Add or remove the channel from ADC regular group sequencer. 
                                        On STM32F0 devices, rank is defined by each channel number (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
                                        Despite the channel rank is fixed, this parameter allow an additional possibility: to remove the selected rank (selected channel) from sequencer.
                                        This parameter can be a value of @ref ADC_rank */
  uint32_t SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        Conversion time is the addition of sampling time and processing time (12.5 ADC clock cycles at ADC resolution 12 bits, 10.5 cycles at 10 bits, 8.5 cycles at 8 bits, 6.5 cycles at 6 bits).
                                        This parameter can be a value of @ref ADC_sampling_times
                                        Caution: this setting impacts the entire regular group. Therefore, call of HAL_ADC_ConfigChannel() to configure a channel can impact the configuration of other channels previously set.
                                        Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                              sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                              Refer to device datasheet for timings values, parameters TS_vrefint, TS_vbat, TS_temp (values rough order: 5us to 17us). */
}ADC_ChannelConfTypeDef;

/** 
  * @brief  Structure definition of ADC analog watchdog
  * @note   The setting of these parameters with function HAL_ADC_AnalogWDGConfig() is conditioned to ADC state.
  *         ADC state can be either: ADC disabled or ADC enabled without conversion on going on regular group.
  */
typedef struct
{
  uint32_t WatchdogMode;      /*!< Configures the ADC analog watchdog mode: single/all/none channels.
                                   This parameter can be a value of @ref ADC_analog_watchdog_mode. */
  uint32_t Channel;           /*!< Selects which ADC channel to monitor by analog watchdog.
                                   This parameter has an effect only if parameter 'WatchdogMode' is configured on single channel. Only 1 channel can be monitored.
                                   This parameter can be a value of @ref ADC_channels. */
  uint32_t ITMode;            /*!< Specifies whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */
  uint32_t HighThreshold;     /*!< Configures the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively. */
  uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively. */
}ADC_AnalogWDGConfTypeDef;

/** 
  * @brief  HAL ADC state machine: ADC States structure definition  
  */ 
typedef enum
{
  HAL_ADC_STATE_RESET                   = 0x00,    /*!< ADC not yet initialized or disabled */
  HAL_ADC_STATE_READY                   = 0x01,    /*!< ADC peripheral ready for use */
  HAL_ADC_STATE_BUSY                    = 0x02,    /*!< An internal process is ongoing */ 
  HAL_ADC_STATE_BUSY_REG                = 0x12,    /*!< Regular conversion is ongoing */
  HAL_ADC_STATE_BUSY_INJ                = 0x22,    /*!< Not used on STM32F0xx devices (kept for compatibility with other devices featuring an injected group) */
  HAL_ADC_STATE_BUSY_INJ_REG            = 0x32,    /*!< Not used on STM32F0xx devices (kept for compatibility with other devices featuring an injected group) */
  HAL_ADC_STATE_TIMEOUT                 = 0x03,    /*!< Timeout state */
  HAL_ADC_STATE_ERROR                   = 0x04,    /*!< ADC state error */
  HAL_ADC_STATE_EOC                     = 0x05,    /*!< Conversion is completed */
  HAL_ADC_STATE_EOC_REG                 = 0x15,    /*!< Regular conversion is completed */
  HAL_ADC_STATE_EOC_INJ                 = 0x25,    /*!< Not used on STM32F0xx devices (kept for compatibility with other devices featuring an injected group) */
  HAL_ADC_STATE_EOC_INJ_REG             = 0x35,    /*!< Not used on STM32F0xx devices (kept for compatibility with other devices featuring an injected group) */
  HAL_ADC_STATE_AWD                     = 0x06,    /*!< ADC state analog watchdog */
  HAL_ADC_STATE_AWD2                    = 0x07,    /*!< Not used on STM32F0xx devices (kept for compatibility with other devices featuring several AWD) */
  HAL_ADC_STATE_AWD3                    = 0x08,    /*!< Not used on STM32F0xx devices (kept for compatibility with other devices featuring several AWD) */ 
}HAL_ADC_StateTypeDef;

/** 
  * @brief  ADC handle Structure definition  
  */ 
typedef struct
{
  ADC_TypeDef                   *Instance;              /*!< Register base address */

  ADC_InitTypeDef               Init;                   /*!< ADC required parameters */

  __IO uint32_t                 NbrOfConversionRank ;   /*!< ADC conversion rank counter */

  DMA_HandleTypeDef             *DMA_Handle;            /*!< Pointer DMA Handler */

  HAL_LockTypeDef               Lock;                   /*!< ADC locking object */

  __IO HAL_ADC_StateTypeDef     State;                  /*!< ADC communication state */

  __IO uint32_t                 ErrorCode;              /*!< ADC Error code */
}ADC_HandleTypeDef;
/**
  * @}
  */



/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_Error_Code ADC Error Code
  * @{
  */ 
#define HAL_ADC_ERROR_NONE        ((uint32_t)0x00)   /*!< No error                                              */
#define HAL_ADC_ERROR_INTERNAL    ((uint32_t)0x01)   /*!< ADC IP internal error: if problem of clocking, 
                                                          enable/disable, erroneous state                       */
#define HAL_ADC_ERROR_OVR         ((uint32_t)0x02)   /*!< Overrun error                                         */
#define HAL_ADC_ERROR_DMA         ((uint32_t)0x04)   /*!< DMA transfer error                                    */

/**
  * @}
  */

/** @defgroup ADC_ClockPrescaler ADC ClockPrescaler
  * @{
  */     
#define ADC_CLOCK_ASYNC               ((uint32_t)0x00000000)          /*!< ADC asynchronous clock derived from ADC dedicated HSI */

#define ADC_CLOCK_SYNC_PCLK_DIV2      ((uint32_t)ADC_CFGR2_CKMODE_0)  /*!< ADC synchronous clock derived from AHB clock divided by a prescaler of 2 */
#define ADC_CLOCK_SYNC_PCLK_DIV4      ((uint32_t)ADC_CFGR2_CKMODE_1)  /*!< ADC synchronous clock derived from AHB clock divided by a prescaler of 4 */

#define ADC_CLOCKPRESCALER_PCLK_DIV2   ADC_CLOCK_SYNC_PCLK_DIV2   /* Obsolete naming, kept for compatibility with some other devices */
#define ADC_CLOCKPRESCALER_PCLK_DIV4   ADC_CLOCK_SYNC_PCLK_DIV4   /* Obsolete naming, kept for compatibility with some other devices */

#define IS_ADC_CLOCKPRESCALER(ADC_CLOCK) (((ADC_CLOCK) == ADC_CLOCK_ASYNC)          || \
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV2) || \
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV4)   )
  
/**
  * @}
  */ 

/** @defgroup ADC_Resolution ADC Resolution
  * @{
  */ 
#define ADC_RESOLUTION12b      ((uint32_t)0x00000000)           /*!<  ADC 12-bit resolution */
#define ADC_RESOLUTION10b      ((uint32_t)ADC_CFGR1_RES_0)      /*!<  ADC 10-bit resolution */
#define ADC_RESOLUTION8b       ((uint32_t)ADC_CFGR1_RES_1)      /*!<  ADC 8-bit resolution */
#define ADC_RESOLUTION6b       ((uint32_t)ADC_CFGR1_RES)        /*!<  ADC 6-bit resolution */

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION12b) || \
                                       ((RESOLUTION) == ADC_RESOLUTION10b) || \
                                       ((RESOLUTION) == ADC_RESOLUTION8b)  || \
                                       ((RESOLUTION) == ADC_RESOLUTION6b)    )
/**
  * @}
  */ 

/** @defgroup ADC_Data_align ADC Data_align
  * @{
  */ 
#define ADC_DATAALIGN_RIGHT      ((uint32_t)0x00000000)
#define ADC_DATAALIGN_LEFT       ((uint32_t)ADC_CFGR1_ALIGN)

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT)    )
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

#define ADC_SCAN_ENABLE         ADC_SCAN_DIRECTION_FORWARD       /* For compatibility with other STM32 devices */

#define IS_ADC_SCAN_MODE(SCAN_MODE) (((SCAN_MODE) == ADC_SCAN_DIRECTION_FORWARD) || \
                                     ((SCAN_MODE) == ADC_SCAN_DIRECTION_BACKWARD)  )
/**
  * @}
  */

/** @defgroup ADC_External_trigger_edge_Regular ADC External trigger edge Regular
  * @{
  */ 
#define ADC_EXTERNALTRIGCONVEDGE_NONE           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIGCONVEDGE_RISING         ((uint32_t)ADC_CFGR1_EXTEN_0)         
#define ADC_EXTERNALTRIGCONVEDGE_FALLING        ((uint32_t)ADC_CFGR1_EXTEN_1)
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING  ((uint32_t)ADC_CFGR1_EXTEN)

#define IS_ADC_EXTTRIG_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGCONVEDGE_NONE)         || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING)       || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_FALLING)      || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING)  )
/**
  * @}
  */ 

/** @defgroup ADC_External_trigger_source_Regular ADC External trigger source Regular
  * @{
  */
/* List of external triggers with generic trigger name, sorted by trigger     */
/* name:                                                                      */

/* External triggers of regular group for ADC1 */
#define ADC_EXTERNALTRIGCONV_T1_TRGO        ADC1_2_EXTERNALTRIG_T1_TRGO
#define ADC_EXTERNALTRIGCONV_T1_CC4         ADC1_2_EXTERNALTRIG_T1_CC4
#define ADC_EXTERNALTRIGCONV_T2_TRGO        ADC1_2_EXTERNALTRIG_T2_TRGO
#define ADC_EXTERNALTRIGCONV_T3_TRGO        ADC1_2_EXTERNALTRIG_T3_TRGO
#define ADC_EXTERNALTRIGCONV_T15_TRGO       ADC1_2_EXTERNALTRIG_T15_TRGO
#define ADC_SOFTWARE_START                  ((uint32_t)0x00000010)

#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC4)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO)  || \
                                 ((REGTRIG) == ADC_EXTERNALTRIGCONV_T15_TRGO) || \
                                 ((REGTRIG) == ADC_SOFTWARE_START)              )
/**
  * @}
  */ 

/** @defgroup ADC_Internal_HAL_driver_Ext_trig_src_Regular ADC Internal HAL driver Ext trig src Regular
  * @{
  */

/* List of external triggers of regular group for ADC1:                       */
/* (used internally by HAL driver. To not use into HAL structure parameters)  */
#define ADC1_2_EXTERNALTRIG_T1_TRGO           ((uint32_t)0x00000000)
#define ADC1_2_EXTERNALTRIG_T1_CC4            ((uint32_t)ADC_CFGR1_EXTSEL_0)
#define ADC1_2_EXTERNALTRIG_T2_TRGO           ((uint32_t)ADC_CFGR1_EXTSEL_1)
#define ADC1_2_EXTERNALTRIG_T3_TRGO           ((uint32_t)(ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_0))
#define ADC1_2_EXTERNALTRIG_T15_TRGO          ((uint32_t)ADC_CFGR1_EXTSEL_2)

/**
  * @}
  */ 

/** @defgroup ADC_EOCSelection ADC EOCSelection
  * @{
  */ 
#define EOC_SINGLE_CONV         ((uint32_t) ADC_ISR_EOC)
#define EOC_SEQ_CONV            ((uint32_t) ADC_ISR_EOS)
#define EOC_SINGLE_SEQ_CONV     ((uint32_t)(ADC_ISR_EOC | ADC_ISR_EOS))  /*!< reserved for future use */

#define IS_ADC_EOC_SELECTION(EOC_SELECTION) (((EOC_SELECTION) == EOC_SINGLE_CONV)    || \
                                             ((EOC_SELECTION) == EOC_SEQ_CONV)       || \
                                             ((EOC_SELECTION) == EOC_SINGLE_SEQ_CONV)  )
/**
  * @}
  */ 

/** @defgroup ADC_Overrun ADC Overrun
  * @{
  */ 
#define OVR_DATA_OVERWRITTEN            ((uint32_t)0x00000000)
#define OVR_DATA_PRESERVED              ((uint32_t)0x00000001)

#define IS_ADC_OVERRUN(OVR) (((OVR) == OVR_DATA_PRESERVED)  || \
                             ((OVR) == OVR_DATA_OVERWRITTEN)  )
/**
  * @}
  */ 

/** @defgroup ADC_channels ADC channels
  * @{
  */
/* Note: Depending on devices, some channels may not be available on package  */
/*       pins. Refer to device datasheet for channels availability.           */
/* Note: Channels are used by bitfields for setting of channel selection      */
/* (register ADC_CHSELR) and used by number for setting of analog watchdog    */
/* channel (bits AWDCH in register ADC_CFGR1).                                */
/* Channels are defined with decimal numbers and converted them to bitfields  */
/* when needed.                                                               */
#define ADC_CHANNEL_0           ((uint32_t) 0x00000000)
#define ADC_CHANNEL_1           ((uint32_t) 0x00000001)
#define ADC_CHANNEL_2           ((uint32_t) 0x00000002)
#define ADC_CHANNEL_3           ((uint32_t) 0x00000003)
#define ADC_CHANNEL_4           ((uint32_t) 0x00000004)
#define ADC_CHANNEL_5           ((uint32_t) 0x00000005)
#define ADC_CHANNEL_6           ((uint32_t) 0x00000006)
#define ADC_CHANNEL_7           ((uint32_t) 0x00000007)
#define ADC_CHANNEL_8           ((uint32_t) 0x00000008)
#define ADC_CHANNEL_9           ((uint32_t) 0x00000009)
#define ADC_CHANNEL_10          ((uint32_t) 0x0000000A)
#define ADC_CHANNEL_11          ((uint32_t) 0x0000000B)
#define ADC_CHANNEL_12          ((uint32_t) 0x0000000C)
#define ADC_CHANNEL_13          ((uint32_t) 0x0000000D)
#define ADC_CHANNEL_14          ((uint32_t) 0x0000000E)
#define ADC_CHANNEL_15          ((uint32_t) 0x0000000F)
#define ADC_CHANNEL_16          ((uint32_t) 0x00000010)
#define ADC_CHANNEL_17          ((uint32_t) 0x00000011)
#define ADC_CHANNEL_18          ((uint32_t) 0x00000012)

#define ADC_CHANNEL_TEMPSENSOR  ADC_CHANNEL_16
#define ADC_CHANNEL_VREFINT     ADC_CHANNEL_17
#define ADC_CHANNEL_VBAT        ADC_CHANNEL_18

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
                                 ((CHANNEL) == ADC_CHANNEL_VBAT)          )
/**
  * @}
  */ 

/** @defgroup ADC_rank ADC rank
  * @{
  */ 
#define ADC_RANK_CHANNEL_NUMBER                 ((uint32_t)0x00001000)  /*!< Enable the rank of the selected channels. Rank is defined by each channel number (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...) */
#define ADC_RANK_NONE                           ((uint32_t)0x00001001)  /*!< Disable the selected rank (selected channel) from sequencer */

#define IS_ADC_RANK(WATCHDOG) (((WATCHDOG) == ADC_RANK_CHANNEL_NUMBER) || \
                               ((WATCHDOG) == ADC_RANK_NONE)             )
/**
  * @}
  */

/** @defgroup ADC_sampling_times ADC sampling times
  * @{
  */ 
#define ADC_SAMPLETIME_1CYCLE_5       ((uint32_t)0x00000000)                        /*!< Sampling time 1.5 ADC clock cycle */
#define ADC_SAMPLETIME_7CYCLES_5      ((uint32_t) ADC_SMPR_SMP_0)                   /*!< Sampling time 7.5 ADC clock cycles */
#define ADC_SAMPLETIME_13CYCLES_5     ((uint32_t) ADC_SMPR_SMP_1)                   /*!< Sampling time 13.5 ADC clock cycles */
#define ADC_SAMPLETIME_28CYCLES_5     ((uint32_t)(ADC_SMPR_SMP_1 | ADC_SMPR_SMP_0)) /*!< Sampling time 28.5 ADC clock cycles */
#define ADC_SAMPLETIME_41CYCLES_5     ((uint32_t) ADC_SMPR_SMP_2)                   /*!< Sampling time 41.5 ADC clock cycles */
#define ADC_SAMPLETIME_55CYCLES_5     ((uint32_t)(ADC_SMPR_SMP_2 | ADC_SMPR_SMP_0)) /*!< Sampling time 55.5 ADC clock cycles */
#define ADC_SAMPLETIME_71CYCLES_5     ((uint32_t)(ADC_SMPR_SMP_2 | ADC_SMPR_SMP_1)) /*!< Sampling time 71.5 ADC clock cycles */
#define ADC_SAMPLETIME_239CYCLES_5    ((uint32_t) ADC_SMPR_SMP)                     /*!< Sampling time 239.5 ADC clock cycles */

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_1CYCLE_5)    || \
                                  ((TIME) == ADC_SAMPLETIME_7CYCLES_5)   || \
                                  ((TIME) == ADC_SAMPLETIME_13CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_28CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_41CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_55CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_71CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_239CYCLES_5)   )
/**
  * @}
  */ 

/** @defgroup ADC_analog_watchdog_mode ADC analog watchdog mode
  * @{
  */ 
#define ADC_ANALOGWATCHDOG_NONE                 ((uint32_t) 0x00000000)
#define ADC_ANALOGWATCHDOG_SINGLE_REG           ((uint32_t)(ADC_CFGR1_AWDSGL | ADC_CFGR1_AWDEN))
#define ADC_ANALOGWATCHDOG_ALL_REG              ((uint32_t) ADC_CFGR1_AWDEN)


#define IS_ADC_ANALOG_WATCHDOG_MODE(WATCHDOG) (((WATCHDOG) == ADC_ANALOGWATCHDOG_NONE)             || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REG)       || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REG)            )
/**
  * @}
  */ 

/** @defgroup ADC_Event_type ADC Event type
  * @{
  */
#define AWD_EVENT              ((uint32_t)ADC_FLAG_AWD)  /*!< ADC Analog watchdog 1 event */
#define OVR_EVENT              ((uint32_t)ADC_FLAG_OVR)  /*!< ADC overrun event */
    
#define IS_ADC_EVENT_TYPE(EVENT) (((EVENT) == AWD_EVENT) || \
                                  ((EVENT) == OVR_EVENT)   )
/**
  * @}
  */

/** @defgroup ADC_interrupts_definition ADC interrupts definition
  * @{
  */
#define ADC_IT_AWD           ADC_IER_AWDIE      /*!< ADC Analog watchdog interrupt source */
#define ADC_IT_OVR           ADC_IER_OVRIE      /*!< ADC overrun interrupt source */
#define ADC_IT_EOS           ADC_IER_EOSEQIE    /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IT_EOC           ADC_IER_EOCIE      /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_EOSMP         ADC_IER_EOSMPIE    /*!< ADC End of Sampling interrupt source */
#define ADC_IT_RDY           ADC_IER_ADRDYIE    /*!< ADC Ready interrupt source */
/**
  * @}
  */ 
    
/** @defgroup ADC_flags_definition ADC flags definition
  * @{
  */
#define ADC_FLAG_AWD           ADC_ISR_AWD      /*!< ADC Analog watchdog flag */
#define ADC_FLAG_OVR           ADC_ISR_OVR      /*!< ADC overrun flag */
#define ADC_FLAG_EOS           ADC_ISR_EOSEQ    /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_FLAG_EOC           ADC_ISR_EOC      /*!< ADC End of Regular Conversion flag */
#define ADC_FLAG_EOSMP         ADC_ISR_EOSMP    /*!< ADC End of Sampling flag */
#define ADC_FLAG_RDY           ADC_ISR_ADRDY    /*!< ADC Ready flag */

#define ADC_FLAG_ALL    (ADC_FLAG_AWD   | ADC_FLAG_OVR | ADC_FLAG_EOS | ADC_FLAG_EOC | \
                         ADC_FLAG_EOSMP | ADC_FLAG_RDY                                )

/* Combination of all post-conversion flags bits: EOC/EOS, OVR, AWD */
#define ADC_FLAG_POSTCONV_ALL    (ADC_FLAG_AWD | ADC_FLAG_OVR | ADC_FLAG_EOS | ADC_FLAG_EOC)
/**
  * @}
  */

/** @defgroup ADC_range_verification ADC range verification
  * in function of ADC resolution selected (12, 10, 8 or 6 bits)
  * @{
  */ 
#define IS_ADC_RANGE(RESOLUTION, ADC_VALUE)                                         \
   ((((RESOLUTION) == ADC_RESOLUTION12b) && ((ADC_VALUE) <= ((uint32_t)0x0FFF))) || \
    (((RESOLUTION) == ADC_RESOLUTION10b) && ((ADC_VALUE) <= ((uint32_t)0x03FF))) || \
    (((RESOLUTION) == ADC_RESOLUTION8b)  && ((ADC_VALUE) <= ((uint32_t)0x00FF))) || \
    (((RESOLUTION) == ADC_RESOLUTION6b)  && ((ADC_VALUE) <= ((uint32_t)0x003F)))   )
/**
  * @}
  */ 

/** @defgroup ADC_regular_rank_verification ADC regular rank verification
  * @{
  */ 
#define IS_ADC_REGULAR_RANK(RANK) (((RANK) >= ((uint32_t)1)) && ((RANK) <= ((uint32_t)16)))
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/* Exported macros -----------------------------------------------------------*/

/** @defgroup ADC_Exported_Macros ADC Exported Macros
  * @{
  */
/** @brief  Reset ADC handle state
  * @param  __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_ADC_STATE_RESET)

/* Macro for internal HAL driver usage, and possibly can be used into code of */
/* final user.                                                                */

/**
  * @brief Verification of ADC state: enabled or disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
/* Note: If low power mode AutoPowerOff is enabled, power-on/off phases are   */
/*       performed automatically by hardware and flag ADC_FLAG_RDY is not     */
/*       set.                                                                 */
#define __HAL_ADC_IS_ENABLED(__HANDLE__)                                                     \
       (( ((((__HANDLE__)->Instance->CR) & (ADC_CR_ADEN | ADC_CR_ADDIS)) == ADC_CR_ADEN)  && \
          (((((__HANDLE__)->Instance->ISR) & ADC_FLAG_RDY) == ADC_FLAG_RDY)          ||      \
           ((((__HANDLE__)->Instance->CFGR1) & ADC_CFGR1_AUTOFF) == ADC_CFGR1_AUTOFF)  )     \
        ) ? SET : RESET)

/**
  * @brief Test if conversion trigger of regular group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define __HAL_ADC_IS_SOFTWARE_START_REGULAR(__HANDLE__)                        \
       (((__HANDLE__)->Instance->CFGR1 & ADC_CFGR1_EXTEN) == RESET)

/**
  * @brief Check if no conversion on going on regular group
  * @param __HANDLE__: ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define __HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(__HANDLE__)                    \
       (( (((__HANDLE__)->Instance->CR) & ADC_CR_ADSTART) == RESET             \
        ) ? RESET : SET)

/**
  * @brief Returns resolution bits in CFGR1 register: RES[1:0].
  *        Returned value is among parameters to @ref ADC_Resolution.
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_GET_RESOLUTION(__HANDLE__) (((__HANDLE__)->Instance->CFGR1) & ADC_CFGR1_RES)

/**
  * @brief Returns ADC sample time bits in SMPR register: SMP[2:0].
  *        Returned value is among parameters to @ref ADC_Resolution.
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_GET_SAMPLINGTIME(__HANDLE__) (((__HANDLE__)->Instance->SMPR) & ADC_SMPR_SMP)
    
/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC interrupt source to check
  * @retval State ofinterruption (SET or RESET)
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                     \
    (( ((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__)      \
     )? SET : RESET                                                            \
    )

/**
  * @brief Enable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->IER) |= (__INTERRUPT__))

/**
  * @brief Disable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->IER) &= ~(__INTERRUPT__))

/**
  * @brief Get the selected ADC's flag status.
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  * @retval None
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->ISR) & (__FLAG__)) == (__FLAG__))

/**
  * @brief Clear the ADC's pending flags
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  * @retval None
  */
/* Note: bit cleared bit by writing 1 (writing 0 has no effect on any bit of register ISR) */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR) = (__FLAG__))

/**
  * @brief Clear ADC error code (set it to error code: "no error")
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)


/**
  * @brief Configure the channel number into channel selection register
  * @param _CHANNEL_: ADC Channel
  * @retval None
  */
/* This function converts ADC channels from numbers (see defgroup ADC_channels) 
   to bitfields, to get the equivalence of CMSIS channels:
        ADC_CHANNEL_0           ((uint32_t) ADC_CHSELR_CHSEL0)
        ADC_CHANNEL_1           ((uint32_t) ADC_CHSELR_CHSEL1)
        ADC_CHANNEL_2           ((uint32_t) ADC_CHSELR_CHSEL2)
        ADC_CHANNEL_3           ((uint32_t) ADC_CHSELR_CHSEL3)
        ADC_CHANNEL_4           ((uint32_t) ADC_CHSELR_CHSEL4)
        ADC_CHANNEL_5           ((uint32_t) ADC_CHSELR_CHSEL5)
        ADC_CHANNEL_6           ((uint32_t) ADC_CHSELR_CHSEL6)
        ADC_CHANNEL_7           ((uint32_t) ADC_CHSELR_CHSEL7)
        ADC_CHANNEL_8           ((uint32_t) ADC_CHSELR_CHSEL8)
        ADC_CHANNEL_9           ((uint32_t) ADC_CHSELR_CHSEL9)
        ADC_CHANNEL_10          ((uint32_t) ADC_CHSELR_CHSEL10)
        ADC_CHANNEL_11          ((uint32_t) ADC_CHSELR_CHSEL11)
        ADC_CHANNEL_12          ((uint32_t) ADC_CHSELR_CHSEL12)
        ADC_CHANNEL_13          ((uint32_t) ADC_CHSELR_CHSEL13)
        ADC_CHANNEL_14          ((uint32_t) ADC_CHSELR_CHSEL14)
        ADC_CHANNEL_15          ((uint32_t) ADC_CHSELR_CHSEL15)
        ADC_CHANNEL_16          ((uint32_t) ADC_CHSELR_CHSEL16)
        ADC_CHANNEL_17          ((uint32_t) ADC_CHSELR_CHSEL17)
        ADC_CHANNEL_18          ((uint32_t) ADC_CHSELR_CHSEL18)
*/
#define __HAL_ADC_CHSELR_CHANNEL(_CHANNEL_) ( 1U << (_CHANNEL_))       
      
/**
  * @}
  */

/** @defgroup ADC_Exported_Macro_internal_HAL_driver ADC Exported Macro internal HAL driver
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/**
  * @brief Set the Analog Watchdog 1 channel.
  * @param _CHANNEL_: channel to be monitored by Analog Watchdog 1.
  * @retval None
  */
#define __HAL_ADC_CFGR_AWDCH(_CHANNEL_) ((_CHANNEL_) << 26)

/**
  * @brief Enable ADC discontinuous conversion mode for regular group
  * @param _REG_DISCONTINUOUS_MODE_: Regular discontinuous mode.
  * @retval None
  */
#define __HAL_ADC_CFGR1_REG_DISCCONTINUOUS(_REG_DISCONTINUOUS_MODE_) ((_REG_DISCONTINUOUS_MODE_) << 16)
  
/**
  * @brief Enable the ADC auto off mode.
  * @param _AUTOOFF_: Auto off bit enable or disable.
  * @retval None
  */
#define __HAL_ADC_CFGR1_AUTOOFF(_AUTOOFF_) ((_AUTOOFF_) << 15)
      
/**
  * @brief Enable the ADC auto delay mode.
  * @param _AUTOWAIT_: Auto delay bit enable or disable.
  * @retval None
  */
#define __HAL_ADC_CFGR1_AUTOWAIT(_AUTOWAIT_) ((_AUTOWAIT_) << 14)

/**
  * @brief Enable ADC continuous conversion mode.
  * @param _CONTINUOUS_MODE_: Continuous mode.
  * @retval None
  */
#define __HAL_ADC_CFGR1_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << 13)
    
/**
  * @brief Enable ADC overrun mode.
  * @param _OVERRUN_MODE_: Overrun mode.
  * @retval Overun bit setting to be programmed into CFGR register
  */
/* Note: Bit ADC_CFGR1_OVRMOD not used directly in constant                   */
/* "OVR_DATA_OVERWRITTEN" to have this case defined to 0x00, to set it as the */
/* default case to be compliant with other STM32 devices.                     */
#define __HAL_ADC_CFGR1_OVERRUN(_OVERRUN_MODE_)                                \
  ( ( (_OVERRUN_MODE_) != (OVR_DATA_PRESERVED)                                 \
    )? (ADC_CFGR1_OVRMOD) : (0x00000000)                                       \
  )

/**
  * @brief Enable ADC scan mode to convert multiple ranks with sequencer.
  * @param _SCAN_MODE_: Scan conversion mode.
  * @retval None
  */
#define __HAL_ADC_CFGR1_SCANDIR(_SCAN_MODE_)                                   \
  ( ( (_SCAN_MODE_) == (ADC_SCAN_DIRECTION_BACKWARD)                           \
    )? (ADC_CFGR1_SCANDIR) : (0x00000000)                                      \
  )
    
/**
  * @brief Enable the ADC DMA continuous request.
  * @param _DMACONTREQ_MODE_: DMA continuous request mode.
  * @retval None
  */
#define __HAL_ADC_CFGR1_DMACONTREQ(_DMACONTREQ_MODE_) ((_DMACONTREQ_MODE_) << 1)

/**
  * @brief Configure the analog watchdog high threshold into register TR.
  * @param _Threshold_: Threshold value
  * @retval None
  */
#define __HAL_ADC_TRX_HIGHTHRESHOLD(_Threshold_) ((_Threshold_) << 16) 

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
#define __HAL_ADC_ENABLING_CONDITIONS(__HANDLE__)                             \
       (( ( ((__HANDLE__)->Instance->CR) &                                    \
            (ADC_CR_ADCAL | ADC_CR_ADSTP |                                    \
             ADC_CR_ADSTART | ADC_CR_ADDIS | ADC_CR_ADEN                    ) \
           ) == RESET                                                         \
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
#define __HAL_ADC_DISABLING_CONDITIONS(__HANDLE__)                             \
       (( ( ((__HANDLE__)->Instance->CR) &                                     \
            (ADC_CR_ADSTART | ADC_CR_ADEN)) == ADC_CR_ADEN   \
        ) ? SET : RESET)
         
/**
  * @brief Shift the AWD threshold in function of the selected ADC resolution.
  *        Thresholds have to be left-aligned on bit 11, the LSB (right bits) are set to 0.
  *        If resolution 12 bits, no shift.
  *        If resolution 10 bits, shift of 2 ranks on the left.
  *        If resolution 8 bits, shift of 4 ranks on the left.
  *        If resolution 6 bits, shift of 6 ranks on the left.
  *        therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2))
  * @param __HANDLE__: ADC handle
  * @param _Threshold_: Value to be shifted
  * @retval None
  */
#define __HAL_ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, _Threshold_) \
        ((_Threshold_) << ((((__HANDLE__)->Instance->CFGR1 & ADC_CFGR1_RES) >> 3)*2))

/**
  * @}
  */   

/* Include ADC HAL Extension module */
#include "stm32f0xx_hal_adc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions
  * @{
  */

/** @addtogroup ADC_Exported_Functions_Group1
  * @{
  */


/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void              HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void              HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);
/**
  * @}
  */

/* IO operation functions  *****************************************************/

/** @addtogroup ADC_Exported_Functions_Group2
  * @{
  */


/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);
HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);

/* Non-blocking mode: DMA */
HAL_StatusTypeDef       HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
/**
  * @}
  */


/* Peripheral Control functions ***********************************************/
/** @addtogroup ADC_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef       HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);
HAL_StatusTypeDef       HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);
/**
  * @}
  */


/* Peripheral State functions *************************************************/
/** @addtogroup ADC_Exported_Functions_Group4
  * @{
  */
HAL_ADC_StateTypeDef    HAL_ADC_GetState(ADC_HandleTypeDef* hadc);
uint32_t                HAL_ADC_GetError(ADC_HandleTypeDef *hadc);
/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */ 

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* __STM32F0xx_HAL_ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

