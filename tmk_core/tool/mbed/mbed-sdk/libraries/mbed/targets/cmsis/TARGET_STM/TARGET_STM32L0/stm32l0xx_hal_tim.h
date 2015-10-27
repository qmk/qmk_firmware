/**
  ******************************************************************************
  * @file    stm32l0xx_hal_tim.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of TIM HAL module.
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
#ifndef __STM32L0xx_HAL_TIM_H
#define __STM32L0xx_HAL_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup TIM TIM (Timer)
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

 /** @defgroup TIM_Exported_Types TIM Exported Types
  * @{
  */

/** @defgroup TIM_Base_Configuration TIM base configuration structure
  * @{
  */
/** 
  * @brief  TIM Time base Configuration Structure definition  
  */
typedef struct
{
  uint32_t Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

  uint32_t CounterMode;       /*!< Specifies the counter mode.
                                   This parameter can be a value of @ref TIM_Counter_Mode */

  uint32_t Period;            /*!< Specifies the period value to be loaded into the active
                                   Auto-Reload Register at the next update event.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.  */ 

  uint32_t ClockDivision;     /*!< Specifies the clock division.
                                   This parameter can be a value of @ref TIM_ClockDivision */
} TIM_Base_InitTypeDef;
/**
  * @}
  */

/** @defgroup TIM_Output_Configuration TIM output compare configuration structure
  * @{
  */

/**
  * @brief  TIM Output Compare Configuration Structure definition  
  */

typedef struct
{                                 
  uint32_t OCMode;        /*!< Specifies the TIM mode.
                               This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint32_t Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                               This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */                          

  uint32_t OCPolarity;    /*!< Specifies the output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_Polarity */
  
  uint32_t OCFastMode;   /*!< Specifies the Fast mode state.
                               This parameter can be a value of @ref TIM_Output_Fast_State
                               @note This parameter is valid only in PWM1 and PWM2 mode. */

} TIM_OC_InitTypeDef;  
/**
  * @}
  */

/** @defgroup TIM_OnePulse_Configuration TIM One Pulse configuration structure
  * @{
  */
/** 
  * @brief  TIM One Pulse Mode Configuration Structure definition  
  */
typedef struct
{                               
  uint32_t OCMode;        /*!< Specifies the TIM mode.
                               This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint32_t Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                               This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */                          

  uint32_t OCPolarity;    /*!< Specifies the output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_Polarity */


  uint32_t ICPolarity;    /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t ICSelection;   /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t ICFilter;      /*!< Specifies the input capture filter.
                              This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */  
} TIM_OnePulse_InitTypeDef;  
/**
  * @}
  */

/** @defgroup TIM_Input_Capture TIM input capture configuration structure
  * @{
  */
/** 
  * @brief  TIM Input Capture Configuration Structure definition  
  */

typedef struct
{                                  
  uint32_t  ICPolarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t ICSelection;  /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                              This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t ICFilter;     /*!< Specifies the input capture filter.
                              This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_IC_InitTypeDef;
/**
  * @}
  */

/** @defgroup TIM_Encoder TIM encoder configuration structure
  * @{
  */
/** 
  * @brief  TIM Encoder Configuration Structure definition  
  */

typedef struct
{
  uint32_t EncoderMode;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Encoder_Mode */
                                  
  uint32_t IC1Polarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t IC1Selection;  /*!< Specifies the input.
                               This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t IC1Prescaler;  /*!< Specifies the Input Capture Prescaler.
                               This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t IC1Filter;     /*!< Specifies the input capture filter.
                               This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
                                  
  uint32_t IC2Polarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t IC2Selection;  /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t IC2Prescaler;  /*!< Specifies the Input Capture Prescaler.
                               This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t IC2Filter;     /*!< Specifies the input capture filter.
                               This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */                                 
} TIM_Encoder_InitTypeDef;
/**
  * @}
  */

/** @defgroup TIM_Clock_Configuration TIM clock configuration structure
  * @{
  */
/** 
  * @brief  Clock Configuration Handle Structure definition  
  */ 
typedef struct
{
  uint32_t ClockSource;     /*!< TIM clock sources. 
                                 This parameter can be a value of @ref TIM_Clock_Source */ 
  uint32_t ClockPolarity;   /*!< TIM clock polarity. 
                                 This parameter can be a value of @ref TIM_Clock_Polarity */
  uint32_t ClockPrescaler;  /*!< TIM clock prescaler. 
                                 This parameter can be a value of @ref TIM_Clock_Prescaler */
  uint32_t ClockFilter;    /*!< TIM clock filter. 
                                This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
}TIM_ClockConfigTypeDef;
/**
  * @}
  */

/** @defgroup TIM_Clear_Input_Configuration TIM clear input configuration structure
  * @{
  */
/** 
  * @brief  Clear Input Configuration Handle Structure definition  
  */ 
typedef struct
{ 
  uint32_t ClearInputState;      /*!< TIM clear Input state. 
                                      This parameter can be ENABLE or DISABLE */  
  uint32_t ClearInputSource;     /*!< TIM clear Input sources. 
                                      This parameter can be a value of @ref TIM_ClearInput_Source */ 
  uint32_t ClearInputPolarity;   /*!< TIM Clear Input polarity. 
                                      This parameter can be a value of @ref TIM_ClearInput_Polarity */
  uint32_t ClearInputPrescaler;  /*!< TIM Clear Input prescaler. 
                                      This parameter can be a value of @ref TIM_ClearInput_Prescaler */
  uint32_t ClearInputFilter;    /*!< TIM Clear Input filter. 
                                     This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
}TIM_ClearInputConfigTypeDef;
/**
  * @}
  */

/** @defgroup TIM_Slave_Configuratio TIM slave configuration structure
  * @{
  */
/** 
  * @brief  TIM Slave configuration Structure definition  
  */ 
typedef struct {
  uint32_t  SlaveMode;         /*!< Slave mode selection. 
                                  This parameter can be a value of @ref TIM_Slave_Mode */ 
  uint32_t  InputTrigger;      /*!< Input Trigger source. 
                                  This parameter can be a value of @ref TIM_Trigger_Selection */
  uint32_t  TriggerPolarity;   /*!< Input Trigger polarity. 
                                  This parameter can be a value of @ref TIM_Trigger_Polarity */
  uint32_t  TriggerPrescaler;  /*!< Input trigger prescaler. 
                                  This parameter can be a value of @ref TIM_Trigger_Prescaler */
  uint32_t  TriggerFilter;     /*!< Input trigger filter. 
                                  This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */

}TIM_SlaveConfigTypeDef;
/**
  * @}
  */

/** @defgroup TIM_State_Definition  TIM state definition
  * @{
  */
/** 
  * @brief  HAL State structures definition  
  */ 
typedef enum
{
  HAL_TIM_STATE_RESET             = 0x00,    /*!< Peripheral not yet initialized or disabled  */
  HAL_TIM_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use    */
  HAL_TIM_STATE_BUSY              = 0x02,    /*!< An internal process is ongoing              */    
  HAL_TIM_STATE_TIMEOUT           = 0x03,    /*!< Timeout state                               */  
  HAL_TIM_STATE_ERROR             = 0x04     /*!< Reception process is ongoing                */                                                                             
}HAL_TIM_StateTypeDef;
/**
  * @}
  */

/** @defgroup TIM_Active_Channel  TIM active channel definition
  * @{
  */
/** 
  * @brief  HAL Active channel structures definition  
  */ 
typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01,    /*!< The active channel is 1     */
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02,    /*!< The active channel is 2     */
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04,    /*!< The active channel is 3     */   
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08,    /*!< The active channel is 4     */
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00     /*!< All active channels cleared */    
}HAL_TIM_ActiveChannel;
/**
  * @}
  */

/** @defgroup TIM_Handle  TIM handler
  * @{
  */
/** 
  * @brief  TIM Time Base Handle Structure definition  
  */ 
typedef struct
{
  TIM_TypeDef              *Instance;     /*!< Register base address             */ 
  TIM_Base_InitTypeDef     Init;          /*!< TIM Time Base required parameters */
  HAL_TIM_ActiveChannel    Channel;       /*!< Active channel                    */ 
  DMA_HandleTypeDef        *hdma[7];      /*!< DMA Handlers array
                                             This array is accessed by a @ref DMA_Handle_index */
  HAL_LockTypeDef          Lock;          /*!< Locking object                    */
__IO HAL_TIM_StateTypeDef  State;         /*!< TIM operation state               */  
}TIM_HandleTypeDef;
/**
  * @}
  */

/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup TIM_Exported_Constants TIM Exported Constants
  * @{
  */


#define IS_TIM_PERIOD(__PERIOD__)      ((__PERIOD__) <= 0xFFFF)

#define IS_TIM_PRESCALER(__PRESCALER__)      ((__PRESCALER__) <= 0xFFFF)


/** @defgroup TIM_Input_Channel_Polarity Input channel polarity
  * @{
  */
#define  TIM_INPUTCHANNELPOLARITY_RISING      ((uint32_t)0x00000000)            /*!< Polarity for TIx source */
#define  TIM_INPUTCHANNELPOLARITY_FALLING     (TIM_CCER_CC1P)                   /*!< Polarity for TIx source */
#define  TIM_INPUTCHANNELPOLARITY_BOTHEDGE    (TIM_CCER_CC1P | TIM_CCER_CC1NP)  /*!< Polarity for TIx source */
/**
  * @}
  */

/** @defgroup TIM_ETR_Polarity ETR polarity
  * @{
  */
#define TIM_ETRPOLARITY_INVERTED              (TIM_SMCR_ETP)                    /*!< Polarity for ETR source */ 
#define TIM_ETRPOLARITY_NONINVERTED           ((uint32_t)0x0000)                /*!< Polarity for ETR source */ 
/**
  * @}
  */

/** @defgroup TIM_ETR_Prescaler ETR prescaler
  * @{
  */                
#define TIM_ETRPRESCALER_DIV1                 ((uint32_t)0x0000)                /*!< No prescaler is used */
#define TIM_ETRPRESCALER_DIV2                 (TIM_SMCR_ETPS_0)                 /*!< ETR input source is divided by 2 */
#define TIM_ETRPRESCALER_DIV4                 (TIM_SMCR_ETPS_1)                 /*!< ETR input source is divided by 4 */
#define TIM_ETRPRESCALER_DIV8                 (TIM_SMCR_ETPS)                   /*!< ETR input source is divided by 8 */
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode Counter mode
  * @{
  */
#define TIM_COUNTERMODE_UP                 ((uint32_t)0x0000)
#define TIM_COUNTERMODE_DOWN               TIM_CR1_DIR
#define TIM_COUNTERMODE_CENTERALIGNED1     TIM_CR1_CMS_0
#define TIM_COUNTERMODE_CENTERALIGNED2     TIM_CR1_CMS_1
#define TIM_COUNTERMODE_CENTERALIGNED3     TIM_CR1_CMS
/**
  * @}
  */
#define IS_TIM_COUNTER_MODE(__MODE__) (((__MODE__) == TIM_COUNTERMODE_UP)              || \
                                       ((__MODE__) == TIM_COUNTERMODE_DOWN)            || \
                                       ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED1)  || \
                                       ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED2)  || \
                                       ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED3))



  
/** @defgroup TIM_ClockDivision Clock division
  * @{
  */
#define TIM_CLOCKDIVISION_DIV1                       ((uint32_t)0x0000)
#define TIM_CLOCKDIVISION_DIV2                       (TIM_CR1_CKD_0)
#define TIM_CLOCKDIVISION_DIV4                       (TIM_CR1_CKD_1)
/**
  * @}
  */
#define IS_TIM_CLOCKDIVISION_DIV(__DIV__) (((__DIV__) == TIM_CLOCKDIVISION_DIV1) || \
                                           ((__DIV__) == TIM_CLOCKDIVISION_DIV2) || \
                                           ((__DIV__) == TIM_CLOCKDIVISION_DIV4))


/** @defgroup TIM_Output_Compare_and_PWM_modes Output compare and PWM modes
  * @{
  */
#define TIM_OCMODE_TIMING                   ((uint32_t)0x0000)
#define TIM_OCMODE_ACTIVE                   (TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_INACTIVE                 (TIM_CCMR1_OC1M_1)
#define TIM_OCMODE_TOGGLE                   (TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1)
#define TIM_OCMODE_PWM1                     (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2)
#define TIM_OCMODE_PWM2                     (TIM_CCMR1_OC1M)
#define TIM_OCMODE_FORCED_ACTIVE            (TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_2)
#define TIM_OCMODE_FORCED_INACTIVE          (TIM_CCMR1_OC1M_2)
/**
  * @}
  */

#define IS_TIM_PWM_MODE(__MODE__) (((__MODE__) == TIM_OCMODE_PWM1) || \
                                   ((__MODE__) == TIM_OCMODE_PWM2))
                              
#define IS_TIM_OC_MODE(__MODE__) (((__MODE__) == TIM_OCMODE_TIMING)           || \
                                  ((__MODE__) == TIM_OCMODE_ACTIVE)           || \
                                  ((__MODE__) == TIM_OCMODE_INACTIVE)         || \
                                  ((__MODE__) == TIM_OCMODE_TOGGLE)           || \
                                  ((__MODE__) == TIM_OCMODE_FORCED_ACTIVE)    || \
                                  ((__MODE__) == TIM_OCMODE_FORCED_INACTIVE))


/** @defgroup TIM_Output_Compare_State Output compare state
  * @{
  */
#define TIM_OUTPUTSTATE_DISABLE            ((uint32_t)0x0000)
#define TIM_OUTPUTSTATE_ENABLE             (TIM_CCER_CC1E)
/**
  * @}
  */

/** @defgroup TIM_Output_Fast_State Output fast state
  * @{
  */
#define TIM_OCFAST_DISABLE                ((uint32_t)0x0000)
#define TIM_OCFAST_ENABLE                 (TIM_CCMR1_OC1FE)
/**
  * @}
  */ 
#define IS_TIM_FAST_STATE(__STATE__) (((__STATE__) == TIM_OCFAST_DISABLE) || \
                                      ((__STATE__) == TIM_OCFAST_ENABLE))

/** @defgroup TIM_Output_Compare_N_State Output compare N state
  * @{
  */
#define TIM_OUTPUTNSTATE_DISABLE            ((uint32_t)0x0000)
#define TIM_OUTPUTNSTATE_ENABLE             (TIM_CCER_CC1NE)
/**
  * @}
  */
  
/** @defgroup TIM_Output_Compare_Polarity Output compare polarity
  * @{
  */
#define TIM_OCPOLARITY_HIGH                ((uint32_t)0x0000)
#define TIM_OCPOLARITY_LOW                 (TIM_CCER_CC1P)
/**
  * @}
  */
#define IS_TIM_OC_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_OCPOLARITY_HIGH) || \
                                          ((__POLARITY__) == TIM_OCPOLARITY_LOW))

/** @defgroup TIM_Channel TIM channels
  * @{
  */
#define TIM_CHANNEL_1                      ((uint32_t)0x0000)
#define TIM_CHANNEL_2                      ((uint32_t)0x0004)
#define TIM_CHANNEL_3                      ((uint32_t)0x0008)
#define TIM_CHANNEL_4                      ((uint32_t)0x000C)
#define TIM_CHANNEL_ALL                    ((uint32_t)0x0018)
/**
  * @}
  */

#define IS_TIM_CHANNELS(__CHANNEL__) (((__CHANNEL__) == TIM_CHANNEL_1) || \
                                      ((__CHANNEL__) == TIM_CHANNEL_2) || \
                                      ((__CHANNEL__) == TIM_CHANNEL_3) || \
                                      ((__CHANNEL__) == TIM_CHANNEL_4) || \
                                      ((__CHANNEL__) == TIM_CHANNEL_ALL))

#define IS_TIM_OPM_CHANNELS(__CHANNEL__) (((__CHANNEL__) == TIM_CHANNEL_1) || \
                                          ((__CHANNEL__) == TIM_CHANNEL_2))


/** @defgroup TIM_Input_Capture_Polarity Input capture polarity
  * @{
  */
#define  TIM_ICPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING
#define  TIM_ICPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING
#define  TIM_ICPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE
/**
  * @}
  */
#define IS_TIM_IC_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_ICPOLARITY_RISING)   || \
                                          ((__POLARITY__) == TIM_ICPOLARITY_FALLING)  || \
                                          ((__POLARITY__) == TIM_ICPOLARITY_BOTHEDGE))


/** @defgroup TIM_Input_Capture_Selection Input capture selection
  * @{
  */
#define TIM_ICSELECTION_DIRECTTI           (TIM_CCMR1_CC1S_0)   /*!< TIM Input 1, 2, 3 or 4 is selected to be 
                                                                     connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSELECTION_INDIRECTTI         (TIM_CCMR1_CC1S_1)   /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                     connected to IC2, IC1, IC4 or IC3, respectively */
#define TIM_ICSELECTION_TRC                (TIM_CCMR1_CC1S)     /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC */

#define IS_TIM_IC_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_ICSELECTION_DIRECTTI) || \
                                            ((__SELECTION__) == TIM_ICSELECTION_INDIRECTTI) || \
                                            ((__SELECTION__) == TIM_ICSELECTION_TRC))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Prescaler Input capture prescaler
  * @{
  */
#define TIM_ICPSC_DIV1                     ((uint32_t)0x0000)       /*!< Capture performed each time an edge is detected on the capture input */
#define TIM_ICPSC_DIV2                     (TIM_CCMR1_IC1PSC_0)     /*!< Capture performed once every 2 events */
#define TIM_ICPSC_DIV4                     (TIM_CCMR1_IC1PSC_1)     /*!< Capture performed once every 4 events */
#define TIM_ICPSC_DIV8                     (TIM_CCMR1_IC1PSC)       /*!< Capture performed once every 8 events */
/**
  * @}
  */
#define IS_TIM_IC_PRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_ICPSC_DIV1) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV2) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV4) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV8))

/** @defgroup TIM_One_Pulse_Mode One pulse mode
  * @{
  */
#define TIM_OPMODE_SINGLE                  (TIM_CR1_OPM)
#define TIM_OPMODE_REPETITIVE              ((uint32_t)0x0000)
/**
  * @}
  */ 
#define IS_TIM_OPM_MODE(__MODE__) (((__MODE__) == TIM_OPMODE_SINGLE) || \
                                   ((__MODE__) == TIM_OPMODE_REPETITIVE))

/** @defgroup TIM_Encoder_Mode Encoder_Mode
  * @{
  */ 
#define TIM_ENCODERMODE_TI1                (TIM_SMCR_SMS_0)
#define TIM_ENCODERMODE_TI2                (TIM_SMCR_SMS_1)
#define TIM_ENCODERMODE_TI12               (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)
/**
  * @}
  */
#define IS_TIM_ENCODER_MODE(__MODE__) (((__MODE__) == TIM_ENCODERMODE_TI1) || \
                                       ((__MODE__) == TIM_ENCODERMODE_TI2) || \
                                       ((__MODE__) == TIM_ENCODERMODE_TI12))

/** @defgroup TIM_Interrupt_definition Interrupt definition
  * @{
  */ 
#define TIM_IT_UPDATE           (TIM_DIER_UIE)
#define TIM_IT_CC1              (TIM_DIER_CC1IE)
#define TIM_IT_CC2              (TIM_DIER_CC2IE)
#define TIM_IT_CC3              (TIM_DIER_CC3IE)
#define TIM_IT_CC4              (TIM_DIER_CC4IE)
#define TIM_IT_TRIGGER          (TIM_DIER_TIE)
/**
  * @}
  */
#define IS_TIM_IT(__IT__) ((((__IT__) & 0xFFFFFFA0) == 0x00000000) && ((__IT__) != 0x00000000))

#define IS_TIM_GET_IT(__IT__) (((__IT__) == TIM_IT_UPDATE)  || \
                               ((__IT__) == TIM_IT_CC1)     || \
                               ((__IT__) == TIM_IT_CC2)     || \
                               ((__IT__) == TIM_IT_CC3)     || \
                               ((__IT__) == TIM_IT_CC4)     || \
                               ((__IT__) == TIM_IT_TRIGGER))


/** @defgroup TIM_DMA_sources DMA sources
  * @{
  */
#define TIM_DMA_UPDATE                     (TIM_DIER_UDE)
#define TIM_DMA_CC1                        (TIM_DIER_CC1DE)
#define TIM_DMA_CC2                        (TIM_DIER_CC2DE)
#define TIM_DMA_CC3                        (TIM_DIER_CC3DE)
#define TIM_DMA_CC4                        (TIM_DIER_CC4DE)
#define TIM_DMA_TRIGGER                    (TIM_DIER_TDE)
/**
  * @}
  */
#define IS_TIM_DMA_SOURCE(__SOURCE__) ((((__SOURCE__) & 0xFFFFA0FF) == 0x00000000) && ((__SOURCE__) != 0x00000000))


    
/** @defgroup TIM_Event_Source Event sources
  * @{
  */
#define TIM_EVENTSOURCE_UPDATE            TIM_EGR_UG  
#define TIM_EVENTSOURCE_CC1                 TIM_EGR_CC1G
#define TIM_EVENTSOURCE_CC2                 TIM_EGR_CC2G
#define TIM_EVENTSOURCE_CC3               TIM_EGR_CC3G
#define TIM_EVENTSOURCE_CC4                 TIM_EGR_CC4G
#define TIM_EVENTSOURCE_TRIGGER               TIM_EGR_TG    
/**
  * @}
  */
#define IS_TIM_EVENT_SOURCE(__SOURCE__) ((((__SOURCE__) & 0xFFFFFFA0) == 0x00000000) && ((__SOURCE__) != 0x00000000))
  

/** @defgroup TIM_Flag_definition Flag definition
  * @{
  */                                
#define TIM_FLAG_UPDATE                    (TIM_SR_UIF)
#define TIM_FLAG_CC1                       (TIM_SR_CC1IF)
#define TIM_FLAG_CC2                       (TIM_SR_CC2IF)
#define TIM_FLAG_CC3                       (TIM_SR_CC3IF)
#define TIM_FLAG_CC4                       (TIM_SR_CC4IF)
#define TIM_FLAG_TRIGGER                   (TIM_SR_TIF)
#define TIM_FLAG_CC1OF                     (TIM_SR_CC1OF)
#define TIM_FLAG_CC2OF                     (TIM_SR_CC2OF)
#define TIM_FLAG_CC3OF                     (TIM_SR_CC3OF)
#define TIM_FLAG_CC4OF                     (TIM_SR_CC4OF)
/**
  * @}
  */
#define IS_TIM_FLAG(__FLAG__) (((__FLAG__) == TIM_FLAG_UPDATE) || \
                               ((__FLAG__) == TIM_FLAG_CC1)     || \
                               ((__FLAG__) == TIM_FLAG_CC2)     || \
                               ((__FLAG__) == TIM_FLAG_CC3)     || \
                               ((__FLAG__) == TIM_FLAG_CC4)     || \
                               ((__FLAG__) == TIM_FLAG_TRIGGER) || \
                               ((__FLAG__) == TIM_FLAG_CC1OF)   || \
                               ((__FLAG__) == TIM_FLAG_CC2OF)   || \
                               ((__FLAG__) == TIM_FLAG_CC3OF)   || \
                               ((__FLAG__) == TIM_FLAG_CC4OF))


/** @defgroup TIM_Clock_Source Clock source
  * @{
  */ 
#define  TIM_CLOCKSOURCE_ETRMODE2    (TIM_SMCR_ETPS_1)
#define  TIM_CLOCKSOURCE_INTERNAL    (TIM_SMCR_ETPS_0)
#define  TIM_CLOCKSOURCE_ITR0        ((uint32_t)0x0000)
#define  TIM_CLOCKSOURCE_ITR1        (TIM_SMCR_TS_0)
#define  TIM_CLOCKSOURCE_ITR2        (TIM_SMCR_TS_1)
#define  TIM_CLOCKSOURCE_ITR3        (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)
#define  TIM_CLOCKSOURCE_TI1ED       (TIM_SMCR_TS_2)
#define  TIM_CLOCKSOURCE_TI1         (TIM_SMCR_TS_0 | TIM_SMCR_TS_2)
#define  TIM_CLOCKSOURCE_TI2         (TIM_SMCR_TS_1 | TIM_SMCR_TS_2)
#define  TIM_CLOCKSOURCE_ETRMODE1    (TIM_SMCR_TS)
/**
  * @}
  */

#define IS_TIM_CLOCKSOURCE(__CLOCK__) (((__CLOCK__) == TIM_CLOCKSOURCE_INTERNAL) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ETRMODE2) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR0)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR1)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR2)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR3)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI1ED)    || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI1)      || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI2)      || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ETRMODE1))


/** @defgroup TIM_Clock_Polarity Clock polarity
  * @{
  */
#define TIM_CLOCKPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED          /*!< Polarity for ETRx clock sources */ 
#define TIM_CLOCKPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED       /*!< Polarity for ETRx clock sources */ 
#define TIM_CLOCKPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING   /*!< Polarity for TIx clock sources */ 
#define TIM_CLOCKPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING   /*!< Polarity for TIx clock sources */ 
#define TIM_CLOCKPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE  /*!< Polarity for TIx clock sources */ 
/**
  * @}
  */
#define IS_TIM_CLOCKPOLARITY(__POLARITY__) (((__POLARITY__) == TIM_CLOCKPOLARITY_INVERTED)    || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_NONINVERTED) || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_RISING)      || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_FALLING)     || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_BOTHEDGE))

/** @defgroup TIM_Clock_Prescaler Clock prescaler
  * @{
  */                
#define TIM_CLOCKPRESCALER_DIV1                 TIM_ETRPRESCALER_DIV1     /*!< No prescaler is used */
#define TIM_CLOCKPRESCALER_DIV2                 TIM_ETRPRESCALER_DIV2     /*!< Prescaler for External ETR Clock: Capture performed once every 2 events. */
#define TIM_CLOCKPRESCALER_DIV4                 TIM_ETRPRESCALER_DIV4     /*!< Prescaler for External ETR Clock: Capture performed once every 4 events. */
#define TIM_CLOCKPRESCALER_DIV8                 TIM_ETRPRESCALER_DIV8     /*!< Prescaler for External ETR Clock: Capture performed once every 8 events. */
/**
  * @}
  */
#define IS_TIM_CLOCKPRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV1) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV2) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV4) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV8))

  
/* Check clock filter */
#define IS_TIM_CLOCKFILTER(__ICFILTER__)      ((__ICFILTER__) <= 0xF)

/** @defgroup TIM_ClearInput_Source Clear input source
  * @{
  */
#define TIM_CLEARINPUTSOURCE_ETR           ((uint32_t)0x0001) 
#define TIM_CLEARINPUTSOURCE_NONE          ((uint32_t)0x0000)
/**
  * @}
  */

#define IS_TIM_CLEARINPUT_SOURCE(__SOURCE__)  (((__SOURCE__) == TIM_CLEARINPUTSOURCE_NONE) || \
                                               ((__SOURCE__) == TIM_CLEARINPUTSOURCE_ETR))


/** @defgroup TIM_ClearInput_Polarity Clear input polarity
  * @{
  */
#define TIM_CLEARINPUTPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED                    /*!< Polarity for ETRx pin */ 
#define TIM_CLEARINPUTPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED                 /*!< Polarity for ETRx pin */ 
/**
  * @}
  */ 
#define IS_TIM_CLEARINPUT_POLARITY(__POLARITY__)   (((__POLARITY__) == TIM_CLEARINPUTPOLARITY_INVERTED) || \
                                                    ((__POLARITY__) == TIM_CLEARINPUTPOLARITY_NONINVERTED))


/** @defgroup TIM_ClearInput_Prescaler Clear input prescaler
  * @{
  */
#define TIM_CLEARINPUTPRESCALER_DIV1                    TIM_ETRPRESCALER_DIV1      /*!< No prescaler is used */
#define TIM_CLEARINPUTPRESCALER_DIV2                    TIM_ETRPRESCALER_DIV2      /*!< Prescaler for External ETR pin: Capture performed once every 2 events. */
#define TIM_CLEARINPUTPRESCALER_DIV4                    TIM_ETRPRESCALER_DIV4      /*!< Prescaler for External ETR pin: Capture performed once every 4 events. */
#define TIM_CLEARINPUTPRESCALER_DIV8                    TIM_ETRPRESCALER_DIV8        /*!< Prescaler for External ETR pin: Capture performed once every 8 events. */
/**
  * @}
  */
#define IS_TIM_CLEARINPUT_PRESCALER(__PRESCALER__)   (((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV1) || \
                                                      ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV2) || \
                                                      ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV4) || \
                                                      ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV8))

  
/* Check IC filter */
#define IS_TIM_CLEARINPUT_FILTER(ICFILTER) ((ICFILTER) <= 0xF) 

  
/** @defgroup TIM_Master_Mode_Selection TIM Master Mode Selection
  * @{
  */  
#define  TIM_TRGO_RESET            ((uint32_t)0x0000)
#define  TIM_TRGO_ENABLE           (TIM_CR2_MMS_0)
#define  TIM_TRGO_UPDATE           (TIM_CR2_MMS_1)
#define  TIM_TRGO_OC1              ((TIM_CR2_MMS_1 | TIM_CR2_MMS_0))
#define  TIM_TRGO_OC1REF           (TIM_CR2_MMS_2)
#define  TIM_TRGO_OC2REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_0))
#define  TIM_TRGO_OC3REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_1))
#define  TIM_TRGO_OC4REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0))
/**
  * @}
  */
#define IS_TIM_TRGO_SOURCE(__SOURCE__) (((__SOURCE__) == TIM_TRGO_RESET) || \
                                        ((__SOURCE__) == TIM_TRGO_ENABLE) || \
                                        ((__SOURCE__) == TIM_TRGO_UPDATE) || \
                                        ((__SOURCE__) == TIM_TRGO_OC1) || \
                                        ((__SOURCE__) == TIM_TRGO_OC1REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC2REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC3REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC4REF))
      
   

/** @defgroup TIM_Slave_Mode Slave mode
  * @{
  */
#define TIM_SLAVEMODE_DISABLE              ((uint32_t)0x0000)
#define TIM_SLAVEMODE_RESET                ((uint32_t)0x0004)
#define TIM_SLAVEMODE_GATED                ((uint32_t)0x0005)
#define TIM_SLAVEMODE_TRIGGER              ((uint32_t)0x0006)
#define TIM_SLAVEMODE_EXTERNAL1            ((uint32_t)0x0007)
/**
  * @}
  */
#define IS_TIM_SLAVE_MODE(__MODE__) (((__MODE__) == TIM_SLAVEMODE_DISABLE) || \
                                     ((__MODE__) == TIM_SLAVEMODE_GATED) || \
                                     ((__MODE__) == TIM_SLAVEMODE_RESET) || \
                                     ((__MODE__) == TIM_SLAVEMODE_TRIGGER) || \
                                     ((__MODE__) == TIM_SLAVEMODE_EXTERNAL1))

/** @defgroup TIM_Master_Slave_Mode Master slave mode
  * @{
  */

#define TIM_MASTERSLAVEMODE_ENABLE          ((uint32_t)0x0080)
#define TIM_MASTERSLAVEMODE_DISABLE         ((uint32_t)0x0000)
/**
  * @}
  */
#define IS_TIM_MSM_STATE(__STATE__) (((__STATE__) == TIM_MASTERSLAVEMODE_ENABLE) || \
                                     ((__STATE__) == TIM_MASTERSLAVEMODE_DISABLE))

/** @defgroup TIM_Trigger_Selection Trigger selection
  * @{
  */
#define TIM_TS_ITR0                        ((uint32_t)0x0000)
#define TIM_TS_ITR1                        ((uint32_t)0x0010)
#define TIM_TS_ITR2                        ((uint32_t)0x0020)
#define TIM_TS_ITR3                        ((uint32_t)0x0030)
#define TIM_TS_TI1F_ED                     ((uint32_t)0x0040)
#define TIM_TS_TI1FP1                      ((uint32_t)0x0050)
#define TIM_TS_TI2FP2                      ((uint32_t)0x0060)
#define TIM_TS_ETRF                        ((uint32_t)0x0070)
#define TIM_TS_NONE                        ((uint32_t)0xFFFF)
/**
  * @}
  */
#define IS_TIM_TRIGGER_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_TS_ITR0) || \
                                                 ((__SELECTION__) == TIM_TS_ITR1) || \
                                                 ((__SELECTION__) == TIM_TS_ITR2) || \
                                                 ((__SELECTION__) == TIM_TS_ITR3) || \
                                                 ((__SELECTION__) == TIM_TS_TI1F_ED) || \
                                                 ((__SELECTION__) == TIM_TS_TI1FP1) || \
                                                 ((__SELECTION__) == TIM_TS_TI2FP2) || \
                                                 ((__SELECTION__) == TIM_TS_ETRF))
#define IS_TIM_INTERNAL_TRIGGEREVENT_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_TS_ITR0) || \
                                                               ((__SELECTION__) == TIM_TS_ITR1) || \
                                                               ((__SELECTION__) == TIM_TS_ITR2) || \
                                                               ((__SELECTION__) == TIM_TS_ITR3) || \
                                                               ((__SELECTION__) == TIM_TS_NONE))


/** @defgroup TIM_Trigger_Polarity Trigger polarity
  * @{
  */
#define TIM_TRIGGERPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED      /*!< Polarity for ETRx trigger sources */ 
#define TIM_TRIGGERPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED   /*!< Polarity for ETRx trigger sources */ 
#define TIM_TRIGGERPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING        /*!< Polarity for TIxFPx or TI1_ED trigger sources */ 
#define TIM_TRIGGERPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING       /*!< Polarity for TIxFPx or TI1_ED trigger sources */ 
#define TIM_TRIGGERPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE      /*!< Polarity for TIxFPx or TI1_ED trigger sources */ 
/**
  * @}
  */
#define IS_TIM_TRIGGERPOLARITY(__POLARITY__) (((__POLARITY__) == TIM_TRIGGERPOLARITY_INVERTED   ) || \
                                              ((__POLARITY__) == TIM_TRIGGERPOLARITY_NONINVERTED) || \
                                              ((__POLARITY__) == TIM_TRIGGERPOLARITY_RISING     ) || \
                                              ((__POLARITY__) == TIM_TRIGGERPOLARITY_FALLING    ) || \
                                              ((__POLARITY__) == TIM_TRIGGERPOLARITY_BOTHEDGE   ))


/** @defgroup TIM_Trigger_Prescaler Trigger prescaler
  * @{
  */                
#define TIM_TRIGGERPRESCALER_DIV1             TIM_ETRPRESCALER_DIV1     /*!< No prescaler is used */
#define TIM_TRIGGERPRESCALER_DIV2             TIM_ETRPRESCALER_DIV2     /*!< Prescaler for External ETR Trigger: Capture performed once every 2 events. */
#define TIM_TRIGGERPRESCALER_DIV4             TIM_ETRPRESCALER_DIV4     /*!< Prescaler for External ETR Trigger: Capture performed once every 4 events. */
#define TIM_TRIGGERPRESCALER_DIV8             TIM_ETRPRESCALER_DIV8     /*!< Prescaler for External ETR Trigger: Capture performed once every 8 events. */
/**
  * @}
  */
#define IS_TIM_TRIGGERPRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV1) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV2) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV4) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV8))


/* Check trigger filter */
#define IS_TIM_TRIGGERFILTER(__ICFILTER__)     ((__ICFILTER__) <= 0xF)


 /** @defgroup TIM_TI1_Selection TI1 selection
  * @{
  */
#define TIM_TI1SELECTION_CH1                ((uint32_t)0x0000)
#define TIM_TI1SELECTION_XORCOMBINATION     (TIM_CR2_TI1S)
/**
  * @}
  */
#define IS_TIM_TI1SELECTION(__TI1SELECTION__) (((__TI1SELECTION__) == TIM_TI1SELECTION_CH1) || \
                                               ((__TI1SELECTION__) == TIM_TI1SELECTION_XORCOMBINATION))

  
/** @defgroup TIM_DMA_Base_address DMA base address
  * @{
  */
#define TIM_DMABASE_CR1                    (0x00000000)
#define TIM_DMABASE_CR2                    (0x00000001)
#define TIM_DMABASE_SMCR                   (0x00000002)
#define TIM_DMABASE_DIER                   (0x00000003)
#define TIM_DMABASE_SR                     (0x00000004)
#define TIM_DMABASE_EGR                    (0x00000005)
#define TIM_DMABASE_CCMR1                  (0x00000006)
#define TIM_DMABASE_CCMR2                  (0x00000007)
#define TIM_DMABASE_CCER                   (0x00000008)
#define TIM_DMABASE_CNT                    (0x00000009)
#define TIM_DMABASE_PSC                    (0x0000000A)
#define TIM_DMABASE_ARR                    (0x0000000B)
#define TIM_DMABASE_CCR1                   (0x0000000D)
#define TIM_DMABASE_CCR2                   (0x0000000E)
#define TIM_DMABASE_CCR3                   (0x0000000F)
#define TIM_DMABASE_CCR4                   (0x00000010)
#define TIM_DMABASE_DCR                    (0x00000012)
#define TIM_DMABASE_OR                     (0x00000013)
/**
  * @}
  */
#define IS_TIM_DMA_BASE(__BASE__) (((__BASE__) == TIM_DMABASE_CR1) || \
                                   ((__BASE__) == TIM_DMABASE_CR2) || \
                                   ((__BASE__) == TIM_DMABASE_SMCR) || \
                                   ((__BASE__) == TIM_DMABASE_DIER) || \
                                   ((__BASE__) == TIM_DMABASE_SR) || \
                                   ((__BASE__) == TIM_DMABASE_EGR) || \
                                   ((__BASE__) == TIM_DMABASE_CCMR1) || \
                                   ((__BASE__) == TIM_DMABASE_CCMR2  ) || \
                                   ((__BASE__) == TIM_DMABASE_CCER) || \
                                   ((__BASE__) == TIM_DMABASE_CNT) || \
                                   ((__BASE__) == TIM_DMABASE_PSC) || \
                                   ((__BASE__) == TIM_DMABASE_ARR) || \
                                   ((__BASE__) == TIM_DMABASE_CCR1) || \
                                   ((__BASE__) == TIM_DMABASE_CCR2) || \
                                   ((__BASE__) == TIM_DMABASE_CCR3) || \
                                   ((__BASE__) == TIM_DMABASE_CCR4) || \
                                   ((__BASE__) == TIM_DMABASE_DCR) || \
                                   ((__BASE__) == TIM_DMABASE_OR))


/** @defgroup TIM_DMA_Burst_Length DMA burst length
  * @{
  */
#define TIM_DMABURSTLENGTH_1TRANSFER             (0x00000000)
#define TIM_DMABURSTLENGTH_2TRANSFERS          (0x00000100)
#define TIM_DMABURSTLENGTH_3TRANSFERS          (0x00000200)
#define TIM_DMABURSTLENGTH_4TRANSFERS          (0x00000300)
#define TIM_DMABURSTLENGTH_5TRANSFERS          (0x00000400)
#define TIM_DMABURSTLENGTH_6TRANSFERS          (0x00000500)
#define TIM_DMABURSTLENGTH_7TRANSFERS          (0x00000600)
#define TIM_DMABURSTLENGTH_8TRANSFERS          (0x00000700)
#define TIM_DMABURSTLENGTH_9TRANSFERS            (0x00000800)
#define TIM_DMABURSTLENGTH_10TRANSFERS         (0x00000900)
#define TIM_DMABURSTLENGTH_11TRANSFERS           (0x00000A00)
#define TIM_DMABURSTLENGTH_12TRANSFERS         (0x00000B00)
#define TIM_DMABURSTLENGTH_13TRANSFERS         (0x00000C00)
#define TIM_DMABURSTLENGTH_14TRANSFERS         (0x00000D00)
#define TIM_DMABURSTLENGTH_15TRANSFERS         (0x00000E00)
#define TIM_DMABURSTLENGTH_16TRANSFERS         (0x00000F00)
#define TIM_DMABURSTLENGTH_17TRANSFERS         (0x00001000)
#define TIM_DMABURSTLENGTH_18TRANSFERS           (0x00001100)
/**
  * @}
  */
#define IS_TIM_DMA_LENGTH(__LENGTH__) (((__LENGTH__) == TIM_DMABURSTLENGTH_1TRANSFER  ) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_2TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_3TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_4TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_5TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_6TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_7TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_8TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_9TRANSFERS  ) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_10TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_11TRANSFERS  ) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_12TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_13TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_14TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_15TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_16TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_17TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_18TRANSFERS  ))


/* Check IC filter */
#define IS_TIM_IC_FILTER(__ICFILTER__) ((__ICFILTER__) <= 0xF)

/** @defgroup DMA_Handle_index DMA handle index
  * @{
  */
#define TIM_DMA_ID_UPDATE                ((uint16_t) 0x0)       /*!< Index of the DMA handle used for Update DMA requests */
#define TIM_DMA_ID_CC1                   ((uint16_t) 0x1)       /*!< Index of the DMA handle used for Capture/Compare 1 DMA requests */
#define TIM_DMA_ID_CC2                   ((uint16_t) 0x2)       /*!< Index of the DMA handle used for Capture/Compare 2 DMA requests */
#define TIM_DMA_ID_CC3                   ((uint16_t) 0x3)       /*!< Index of the DMA handle used for Capture/Compare 3 DMA requests */
#define TIM_DMA_ID_CC4                   ((uint16_t) 0x4)       /*!< Index of the DMA handle used for Capture/Compare 4 DMA requests */
#define TIM_DMA_ID_TRIGGER               ((uint16_t) 0x5)       /*!< Index of the DMA handle used for Trigger DMA requests */
/**
  * @}
  */ 

/** @defgroup Channel_CC_State Channel state
  * @{
  */
#define TIM_CCx_ENABLE                   ((uint32_t)0x0001)
#define TIM_CCx_DISABLE                  ((uint32_t)0x0000)
/**
  * @}
  */ 

/**
  * @}
  */   
  
/* Exported macro ------------------------------------------------------------*/
/** @defgroup TIM_Exported_Macro TIM Exported Macro
  * @{
  */

/** @brief Reset UART handle state
  * @param  __HANDLE__ : TIM handle
  * @retval None
  */
#define __HAL_TIM_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_TIM_STATE_RESET)

/**
  * @brief  Enable the TIM peripheral.
  * @param  __HANDLE__ : TIM handle
  * @retval None
 */
#define __HAL_TIM_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR1|=(TIM_CR1_CEN))

/* The counter of a timer instance is disabled only if all the CCx channels have
   been disabled */
#define TIM_CCER_CCxE_MASK ((uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E))

/**
  * @brief  Disable the TIM peripheral.
  * @param  __HANDLE__ : TIM handle
  * @retval None
  */
#define __HAL_TIM_DISABLE(__HANDLE__) \
                        do { \
                          if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0) \
                          { \
                            (__HANDLE__)->Instance->CR1 &= ~(TIM_CR1_CEN); \
                          } \
                        } while(0) 

#define __HAL_TIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->DIER |= (__INTERRUPT__))
#define __HAL_TIM_ENABLE_DMA(__HANDLE__, __DMA__)         ((__HANDLE__)->Instance->DIER |= (__DMA__))
#define __HAL_TIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->DIER &= ~(__INTERRUPT__))
#define __HAL_TIM_DISABLE_DMA(__HANDLE__, __DMA__)        ((__HANDLE__)->Instance->DIER &= ~(__DMA__))
#define __HAL_TIM_GET_FLAG(__HANDLE__, __FLAG__)          (((__HANDLE__)->Instance->SR &(__FLAG__)) == (__FLAG__))
#define __HAL_TIM_CLEAR_FLAG(__HANDLE__, __FLAG__)        ((__HANDLE__)->Instance->SR = ~(__FLAG__))

#define __HAL_TIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->DIER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)
#define __HAL_TIM_CLEAR_IT(__HANDLE__, __INTERRUPT__)     ((__HANDLE__)->Instance->SR = ~(__INTERRUPT__))

#define __HAL_TIM_IS_TIM_COUNTING_DOWN(__HANDLE__)            (((__HANDLE__)->Instance->CR1 &(TIM_CR1_DIR)) == (TIM_CR1_DIR))
#define __HAL_TIM_SET_PRESCALER(__HANDLE__, __PRESC__)        ((__HANDLE__)->Instance->PSC = (__PRESC__))

#define TIM_SET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__, __ICPSC__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= (__ICPSC__)) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= ((__ICPSC__) << 8)) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= (__ICPSC__)) :\
 ((__HANDLE__)->Instance->CCMR2 |= ((__ICPSC__) << 8)))

#define TIM_RESET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= (uint16_t)~TIM_CCMR1_IC1PSC) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= (uint16_t)~TIM_CCMR1_IC2PSC) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= (uint16_t)~TIM_CCMR2_IC3PSC) :\
 ((__HANDLE__)->Instance->CCMR2 &= (uint16_t)~TIM_CCMR2_IC4PSC))
                          
#define TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER |= (__POLARITY__)) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 4)) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 8)) :\
 ((__HANDLE__)->Instance->CCER |= (((__POLARITY__) << 12) & TIM_CCER_CC4P)))

#define TIM_RESET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER &= (uint16_t)~(TIM_CCER_CC1P | TIM_CCER_CC1NP)) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER &= (uint16_t)~(TIM_CCER_CC2P | TIM_CCER_CC2NP)) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER &= (uint16_t)~(TIM_CCER_CC3P | TIM_CCER_CC3NP)) :\
 ((__HANDLE__)->Instance->CCER &= (uint16_t)~TIM_CCER_CC4P))

/**
  * @brief  Sets the TIM Capture Compare Register value on runtime without
  *         calling another time ConfigChannel function.
  * @param  __HANDLE__ : TIM handle.
  * @param  __CHANNEL__ : TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @param  __COMPARE__: specifies the Capture Compare register new value.
  * @retval None
  */
#define __HAL_TIM_SET_COMPARE(__HANDLE__, __CHANNEL__, __COMPARE__) \
(*(__IO uint32_t *)(&((__HANDLE__)->Instance->CCR1) + ((__CHANNEL__) >> 2)) = (__COMPARE__))

/**
  * @brief  Gets the TIM Capture Compare Register value on runtime
  * @param  __HANDLE__ : TIM handle.
  * @param  __CHANNEL__ : TIM Channel associated with the capture compare register
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: get capture/compare 1 register value
  *            @arg TIM_CHANNEL_2: get capture/compare 2 register value
  *            @arg TIM_CHANNEL_3: get capture/compare 3 register value
  *            @arg TIM_CHANNEL_4: get capture/compare 4 register value
  * @retval None
  */
#define __HAL_TIM_GET_COMPARE(__HANDLE__, __CHANNEL__) \
  (*(__IO uint32_t *)(&((__HANDLE__)->Instance->CCR1) + ((__CHANNEL__) >> 2)))

/**
  * @brief  Sets the TIM Counter Register value on runtime.
  * @param  __HANDLE__ : TIM handle.
  * @param  __COUNTER__: specifies the Counter register new value.
  * @retval None
  */
#define __HAL_TIM_SET_COUNTER(__HANDLE__, __COUNTER__)  ((__HANDLE__)->Instance->CNT = (__COUNTER__))

/**
  * @brief  Gets the TIM Counter Register value on runtime.
  * @param  __HANDLE__ : TIM handle.
  * @retval None
  */
#define __HAL_TIM_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->CNT)

/**
  * @brief  Sets the TIM Autoreload Register value on runtime without calling 
  *         another time any Init function.
  * @param  __HANDLE__ : TIM handle.
  * @param  __AUTORELOAD__: specifies the Counter register new value.
  * @retval None
  */
#define __HAL_TIM_SET_AUTORELOAD(__HANDLE__, __AUTORELOAD__) \
                        do{                                                    \
                              (__HANDLE__)->Instance->ARR = (__AUTORELOAD__);  \
                              (__HANDLE__)->Init.Period = (__AUTORELOAD__);    \
                          } while(0)
/**
  * @brief  Gets the TIM Autoreload Register value on runtime
  * @param  __HANDLE__ : TIM handle.
  * @retval None
  */
#define __HAL_TIM_GET_AUTORELOAD(__HANDLE__) ((__HANDLE__)->Instance->ARR)

/**
  * @brief  Sets the TIM Clock Division value on runtime without calling 
  *         another time any Init function. 
  * @param  __HANDLE__ : TIM handle.
  * @param  __CKD__: specifies the clock division value.
  *          This parameter can be one of the following value:
  *            @arg TIM_CLOCKDIVISION_DIV1
  *            @arg TIM_CLOCKDIVISION_DIV2
  *            @arg TIM_CLOCKDIVISION_DIV4
  * @retval None
  */
#define __HAL_TIM_SET_CLOCKDIVISION(__HANDLE__, __CKD__) \
                        do{                                                    \
                              (__HANDLE__)->Instance->CR1 &= (uint16_t)(~TIM_CR1_CKD);  \
                              (__HANDLE__)->Instance->CR1 |= (__CKD__);                   \
                              (__HANDLE__)->Init.ClockDivision = (__CKD__);             \
                          } while(0)
/**
  * @brief  Gets the TIM Clock Division value on runtime
  * @param  __HANDLE__ : TIM handle.
  * @retval None
  */
#define __HAL_TIM_GET_CLOCKDIVISION(__HANDLE__) ((__HANDLE__)->Instance->CR1 & TIM_CR1_CKD)

/**
  * @brief  Sets the TIM Input Capture prescaler on runtime without calling 
  *         another time HAL_TIM_IC_ConfigChannel() function.
  * @param  __HANDLE__ : TIM handle.
  * @param  __CHANNEL__ : TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @param  __ICPSC__: specifies the Input Capture4 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
#define __HAL_TIM_SET_ICPRESCALER(__HANDLE__, __CHANNEL__, __ICPSC__) \
                        do{                                                    \
                              TIM_RESET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__));  \
                              TIM_SET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__), (__ICPSC__)); \
                          } while(0)

/**
  * @brief  Gets the TIM Input Capture prescaler on runtime
  * @param  __HANDLE__ : TIM handle.
  * @param  __CHANNEL__ : TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: get input capture 1 prescaler value
  *            @arg TIM_CHANNEL_2: get input capture 2 prescaler value
  *            @arg TIM_CHANNEL_3: get input capture 3 prescaler value
  *            @arg TIM_CHANNEL_4: get input capture 4 prescaler value
  * @retval None
  */
#define __HAL_TIM_GET_ICPRESCALER(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 & TIM_CCMR1_IC1PSC) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? (((__HANDLE__)->Instance->CCMR1 & TIM_CCMR1_IC2PSC) >> 8) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC3PSC) :\
   (((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC4PSC)) >> 8)
   

/**
  * @brief  Set the Update Request Source (URS) bit of the TIMx_CR1 register
  * @param  __HANDLE__: TIM handle.
  * @note  When the URS bit of the TIMx_CR1 register is set, only counter
  *        overflow/underflow generates an update interrupt or DMA request (if
  *        enabled)
  * @retval None
  */
#define __HAL_TIM_URS_ENABLE(__HANDLE__) \
    ((__HANDLE__)->Instance->CR1|= (TIM_CR1_URS))

/**
  * @brief  Reset the Update Request Source (URS) bit of the TIMx_CR1 register
  * @param  __HANDLE__: TIM handle.
  * @note  When the URS bit of the TIMx_CR1 register is reset, any of the
  *        following events generate an update interrupt or DMA request (if
  *        enabled):
  *          – Counter overflow/underflow
  *          – Setting the UG bit
  *          – Update generation through the slave mode controller
  * @retval None
  */
#define __HAL_TIM_URS_DISABLE(__HANDLE__) \
      ((__HANDLE__)->Instance->CR1&=~(TIM_CR1_URS))

/**
  * @brief  Sets the TIM Capture x input polarity on runtime.
  * @param  __HANDLE__: TIM handle.
  * @param  __CHANNEL__: TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @param  __POLARITY__: Polarity for TIx source
  *            @arg TIM_INPUTCHANNELPOLARITY_RISING: Rising Edge
  *            @arg TIM_INPUTCHANNELPOLARITY_FALLING: Falling Edge
  *            @arg TIM_INPUTCHANNELPOLARITY_BOTHEDGE: Rising and Falling Edge
  * @note  The polarity TIM_INPUTCHANNELPOLARITY_BOTHEDGE is not authorized  for TIM Channel 4.
  * @retval None
  */
#define __HAL_TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__)                          \
                       do{                                                                            \
                           TIM_RESET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__));               \
                           TIM_SET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__), (__POLARITY__)); \
                         }while(0)

/**
  * @}
  */   
     
/* Include TIM HAL Extension module */
#include "stm32l0xx_hal_tim_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @defgroup TIM_Exported_Functions TIM Exported Functions
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/* Time Base functions ********************************************************/

/** @defgroup TIM_Exported_Functions_Group1 Timer Base functions
 *  @brief    Time Base functions
 *  @{
 */
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef *htim);

/**
  * @}
  */


/* Timer Output Compare functions **********************************************/

/** @defgroup TIM_Exported_Functions_Group2 Timer Output Compare functions
 *  @brief    Timer Output Compare functions
 *  @{
 */

HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_OC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_OC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */


/* Timer PWM functions *********************************************************/

/** @defgroup TIM_Exported_Functions_Group3 Timer PWM functions
 *   @brief    Timer PWM functions
 *   @{
 */
HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/* Timer Input Capture functions ***********************************************/

/** @defgroup TIM_Exported_Functions_Group4 Timer Input Capture functions
 *  @brief    Timer Input Capture functions
 *  @{
 */
HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_IC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_IC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/* Timer One Pulse functions ***************************************************/

/** @defgroup TIM_Exported_Functions_Group5 Timer One Pulse functions
 *  @brief    Timer One Pulse functions
 *  @{
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

/**
  * @}
  */

/* Timer Encoder functions *****************************************************/

/** @defgroup TIM_Exported_Functions_Group6 Timer Encoder functions
 *  @brief       Timer Encoder functions
 *  @{
 */
HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim,  TIM_Encoder_InitTypeDef* sConfig);
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_Encoder_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData1, uint32_t *pData2, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
  * @}
  */

/* Interrupt Handler functions  **********************************************/

/** @defgroup TIM_Exported_Functions_Group7 Timer IRQ handler management
 *  @brief      Interrupt Handler functions
 *  @{
 */
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);
/**
  * @}
  */

/* Control functions  *********************************************************/

/** @defgroup TIM_Exported_Functions_Group8 Peripheral Control functions
 *  @brief      Control functions
 *  @{
 */
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef* sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef* sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_IC_InitTypeDef* sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef* sConfig, uint32_t OutputChannel,  uint32_t InputChannel);
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim, TIM_ClearInputConfigTypeDef * sClearInputConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef * sClockSourceConfig);    
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchronization(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef * sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchronization_IT(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef * sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress, uint32_t BurstRequestSrc, \
                                              uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress, uint32_t BurstRequestSrc, \
                                              uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);
uint32_t HAL_TIM_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
  * @}
  */

/* Callback in non blocking modes (Interrupt and DMA) *************************/

/** @defgroup TIM_Exported_Functions_Group9 Timer Callbacks functions
 *  @brief      Callback functions
 *  @{
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);
/**
  * @}
  */


/* Peripheral State functions  **************************************************/

/** @defgroup TIM_Exported_Functions_Group10 Peripheral State functions
 *  @brief      Peripheral State functions
 *  @{
 */
HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(TIM_HandleTypeDef *htim);
void TIM_DMADelayPulseCplt(DMA_HandleTypeDef *hdma);
void TIM_DMAError(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureCplt(DMA_HandleTypeDef *hdma);

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

#endif /* __STM32L0xx_HAL_TIM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

