/**
  ******************************************************************************
  * @file    stm32l0xx_hal_lptim.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of LPTIM HAL module.
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
#ifndef __STM32L0xx_HAL_LPTIM_H
#define __STM32L0xx_HAL_LPTIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup LPTIM LPTIM (Low power timer)
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
 /** @defgroup TIM_Exported_Types TIM Exported Types
  * @{
  */

/** @defgroup LPTIM_Clock_Configuration LPTIM Clock configuration structure
  * @{
  */
/** 
  * @brief  LPTIM Clock configuration definition  
  */
typedef struct
{
  uint32_t Source;         /*!< Selects the clock source.
                           This parameter can be a value of @ref LPTIM_Clock_Source   */

  uint32_t Prescaler;      /*!< Specifies the counter clock Prescaler.
                           This parameter can be a value of @ref LPTIM_Clock_Prescaler */
  
}LPTIM_ClockConfigTypeDef;
/**
  * @}
  */

/** @defgroup LPTIM_ULPClock_Configuration LPTIM ULP Clock configuration structure
  * @{
  */
/** 
  * @brief  LPTIM ULP Clock configuration definition
  */
typedef struct
{
  uint32_t Polarity;      /*!< Selects the polarity of the active edge for the counter unit
                           if the ULPTIM input is selected.
                           Note: This parameter is used only when Ultra low power clock source is used.
                           Note: If the polarity is configured on 'both edges', an auxiliary clock
                           (one of the Low power oscillator) must be active.
                           This parameter can be a value of @ref LPTIM_Clock_Polarity */ 
  
  uint32_t SampleTime;     /*!< Selects the clock sampling time to configure the clock glitch filter.
                           Note: This parameter is used only when Ultra low power clock source is used.
                           This parameter can be a value of @ref LPTIM_Clock_Sample_Time */  
  
}LPTIM_ULPClockConfigTypeDef;
/**
  * @}
  */

/** @defgroup LPTIM_Trigger_Configuration LPTIM Trigger configuration structure
  * @{
  */
/** 
  * @brief  LPTIM Trigger configuration structure
  */
typedef struct
{
  uint32_t Source;        /*!< Selects the Trigger source.
                          This parameter can be a value of @ref LPTIM_Trigger_Source */
  
  uint32_t ActiveEdge;    /*!< Selects the Trigger active edge.
                          Note: This parameter is used only when an external trigger is used.
                          This parameter can be a value of @ref LPTIM_External_Trigger_Polarity */
  
  uint32_t SampleTime;    /*!< Selects the trigger sampling time to configure the clock glitch filter.
                          Note: This parameter is used only when an external trigger is used.
                          This parameter can be a value of @ref LPTIM_Trigger_Sample_Time  */  
}LPTIM_TriggerConfigTypeDef;
/**
  * @}
  */

/** @defgroup LPTIM_Init_Configuration LPTIM Initialization configuration structure
  * @{
  */
/** 
  * @brief  LPTIM Initialization Structure definition  
  */
typedef struct
{                                                    
  LPTIM_ClockConfigTypeDef     Clock;               /*!< Specifies the clock parameters */
                                                    
  LPTIM_ULPClockConfigTypeDef  UltraLowPowerClock;  /*!< Specifies the Ultra Low Power clock parameters */
                                                    
  LPTIM_TriggerConfigTypeDef   Trigger;             /*!< Specifies the Trigger parameters */
                                                    
  uint32_t                     OutputPolarity;      /*!< Specifies the Output polarity.
                                                    This parameter can be a value of @ref LPTIM_Output_Polarity */
                                                    
  uint32_t                     UpdateMode;          /*!< Specifies whether the update of the autorelaod and the compare
                                                    values is done immediately or after the end of current period.
                                                    This parameter can be a value of @ref LPTIM_Updating_Mode */

  uint32_t                     CounterSource;       /*!< Specifies whether the counter is incremented each internal event
                                                    or each external event.
                                                    This parameter can be a value of @ref LPTIM_Counter_Source */  
  
}LPTIM_InitTypeDef;
/**
  * @}
  */
/** @defgroup LPTIM_State_structure  LPTIM state definition
  * @{
  */
/** 
  * @brief  HAL LPTIM State structure definition  
  */ 
typedef enum __HAL_LPTIM_StateTypeDef
{
  HAL_LPTIM_STATE_RESET            = 0x00,    /*!< Peripheral not yet initialized or disabled  */
  HAL_LPTIM_STATE_READY            = 0x01,    /*!< Peripheral Initialized and ready for use    */
  HAL_LPTIM_STATE_BUSY             = 0x02,    /*!< An internal process is ongoing              */    
  HAL_LPTIM_STATE_TIMEOUT          = 0x03,    /*!< Timeout state                               */  
  HAL_LPTIM_STATE_ERROR            = 0x04     /*!< Internal Process is ongoing                */                                                                             
}HAL_LPTIM_StateTypeDef;
/**
  * @}
  */

/** @defgroup LPTIM_Handle  LPTIM handler
  * @{
  */
/** 
  * @brief  LPTIM handle Structure definition  
  */ 
typedef struct
{
      LPTIM_TypeDef              *Instance;         /*!< Register base address     */
      
      LPTIM_InitTypeDef           Init;             /*!< LPTIM required parameters */
  
      HAL_StatusTypeDef           Status;           /*!< LPTIM peripheral status   */  
  
      HAL_LockTypeDef             Lock;             /*!< LPTIM locking object      */
  
   __IO  HAL_LPTIM_StateTypeDef   State;            /*!< LPTIM peripheral state    */
  
}LPTIM_HandleTypeDef;

/**
  * @}
  */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup LPTIM_Exported_Constants LPTIM Exported constants
  * @{
  */

/* Check autoreload value */
#define IS_LPTIM_AUTORELOAD(__AUTORELOAD__)     ((__AUTORELOAD__) <= 0x0000FFFF)

/* Check compare value */
#define IS_LPTIM_COMPARE(__COMPARE__)          ((__COMPARE__) <= 0x0000FFFF)

/** @defgroup LPTIM_Clock_Source Clock source
  * @{
  */
#define LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC        ((uint32_t)0x00)
#define LPTIM_CLOCKSOURCE_ULPTIM                LPTIM_CFGR_CKSEL
/**                                             
  * @}
  */
#define IS_LPTIM_CLOCK_SOURCE(__SOURCE__)       (((__SOURCE__) == LPTIM_CLOCKSOURCE_ULPTIM) || \
                                                 ((__SOURCE__) == LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC))


/** @defgroup LPTIM_Clock_Prescaler Prescaler
  * @{
  */
#define LPTIM_PRESCALER_DIV1                    ((uint32_t)0x000000)
#define LPTIM_PRESCALER_DIV2                    LPTIM_CFGR_PRESC_0
#define LPTIM_PRESCALER_DIV4                    LPTIM_CFGR_PRESC_1
#define LPTIM_PRESCALER_DIV8                    ((uint32_t)(LPTIM_CFGR_PRESC_0 | LPTIM_CFGR_PRESC_1))
#define LPTIM_PRESCALER_DIV16                   LPTIM_CFGR_PRESC_2
#define LPTIM_PRESCALER_DIV32                   ((uint32_t)(LPTIM_CFGR_PRESC_0 | LPTIM_CFGR_PRESC_2))
#define LPTIM_PRESCALER_DIV64                   ((uint32_t)(LPTIM_CFGR_PRESC_1 | LPTIM_CFGR_PRESC_2))
#define LPTIM_PRESCALER_DIV128                  ((uint32_t)LPTIM_CFGR_PRESC)
/**
  * @}
  */

#define IS_LPTIM_CLOCK_PRESCALER(__PRESCALER__) (((__PRESCALER__) ==  LPTIM_PRESCALER_DIV1  ) || \
                                                 ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV2  ) || \
                                                 ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV4  ) || \
                                                 ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV8  ) || \
                                                 ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV16 ) || \
                                                 ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV32 ) || \
                                                 ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV64 ) || \
                                                 ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV128))

#define IS_LPTIM_CLOCK_PRESCALERDIV1(__PRESCALER__) ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV1)


/** @defgroup LPTIM_Output_Polarity Output polarity
  * @{
  */
#define LPTIM_OUTPUTPOLARITY_HIGH               ((uint32_t)0x00000000)
#define LPTIM_OUTPUTPOLARITY_LOW                (LPTIM_CFGR_WAVPOL)
/**
  * @}
  */
#define IS_LPTIM_OUTPUT_POLARITY(__POLARITY__)  (((__POLARITY__) == LPTIM_OUTPUTPOLARITY_LOW ) || \
                                                 ((__POLARITY__) == LPTIM_OUTPUTPOLARITY_HIGH))

/** @defgroup LPTIM_Clock_Sample_Time Clock sample time
  * @{
  */
#define LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION ((uint32_t)0x00000000)
#define LPTIM_CLOCKSAMPLETIME_2TRANSITIONS     LPTIM_CFGR_CKFLT_0
#define LPTIM_CLOCKSAMPLETIME_4TRANSITIONS     LPTIM_CFGR_CKFLT_1
#define LPTIM_CLOCKSAMPLETIME_8TRANSITIONS     LPTIM_CFGR_CKFLT
/**
  * @}
  */
#define IS_LPTIM_CLOCK_SAMPLE_TIME(__SAMPLETIME__)  (((__SAMPLETIME__) == LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION) || \
                                                     ((__SAMPLETIME__) == LPTIM_CLOCKSAMPLETIME_2TRANSITIONS)     || \
                                                     ((__SAMPLETIME__) == LPTIM_CLOCKSAMPLETIME_4TRANSITIONS)     || \
                                                     ((__SAMPLETIME__) == LPTIM_CLOCKSAMPLETIME_8TRANSITIONS))

/** @defgroup LPTIM_Clock_Polarity Clock polarity
  * @{
  */
#define LPTIM_CLOCKPOLARITY_RISING                   ((uint32_t)0x00000000)
#define LPTIM_CLOCKPOLARITY_FALLING                  LPTIM_CFGR_CKPOL_0
#define LPTIM_CLOCKPOLARITY_RISING_FALLING           LPTIM_CFGR_CKPOL_1
/**
  * @}
  */

#define IS_LPTIM_CLOCK_POLARITY(__POLARITY__)   (((__POLARITY__) == LPTIM_CLOCKPOLARITY_RISING)  || \
                                                 ((__POLARITY__) == LPTIM_CLOCKPOLARITY_FALLING) || \
                                                 ((__POLARITY__) == LPTIM_CLOCKPOLARITY_RISING_FALLING))

/** @defgroup LPTIM_External_Trigger_Polarity Trigger polarity
  * @{
  */
#define LPTIM_ACTIVEEDGE_RISING                LPTIM_CFGR_TRIGEN_0
#define LPTIM_ACTIVEEDGE_FALLING               LPTIM_CFGR_TRIGEN_1
#define LPTIM_ACTIVEEDGE_RISING_FALLING        LPTIM_CFGR_TRIGEN
/**
  * @}
  */
#define IS_LPTIM_EXT_TRG_POLARITY(__POLAR__)   (((__POLAR__) == LPTIM_ACTIVEEDGE_RISING         ) || \
                                                ((__POLAR__) == LPTIM_ACTIVEEDGE_FALLING        ) || \
                                                ((__POLAR__) == LPTIM_ACTIVEEDGE_RISING_FALLING ))

/** @defgroup LPTIM_Trigger_Sample_Time Trigger sample time
  * @{
  */
#define LPTIM_TRIGSAMPLETIME_DIRECTTRANSITION  ((uint32_t)0x00000000)
#define LPTIM_TRIGSAMPLETIME_2TRANSITIONS       LPTIM_CFGR_TRGFLT_0
#define LPTIM_TRIGSAMPLETIME_4TRANSITIONS       LPTIM_CFGR_TRGFLT_1
#define LPTIM_TRIGSAMPLETIME_8TRANSITIONS       LPTIM_CFGR_TRGFLT
/**
  * @}
  */
#define IS_LPTIM_TRIG_SAMPLE_TIME(__SAMPLETIME__) (((__SAMPLETIME__) == LPTIM_TRIGSAMPLETIME_DIRECTTRANSITION  ) || \
                                                   ((__SAMPLETIME__) == LPTIM_TRIGSAMPLETIME_2TRANSITIONS    ) || \
                                                   ((__SAMPLETIME__) == LPTIM_TRIGSAMPLETIME_4TRANSITIONS    ) || \
                                                   ((__SAMPLETIME__) == LPTIM_TRIGSAMPLETIME_8TRANSITIONS    ))


/** @defgroup LPTIM_Updating_Mode Updating mode
  * @{
  */

#define LPTIM_UPDATE_IMMEDIATE                  ((uint32_t)0x00000000)
#define LPTIM_UPDATE_ENDOFPERIOD                LPTIM_CFGR_PRELOAD
/**
  * @}
  */
#define IS_LPTIM_UPDATE_MODE(__MODE__)          (((__MODE__) == LPTIM_UPDATE_IMMEDIATE) || \
                                                 ((__MODE__) == LPTIM_UPDATE_ENDOFPERIOD))



/** @defgroup LPTIM_Counter_Source Counter source
  * @{
  */
#define LPTIM_COUNTERSOURCE_INTERNAL            ((uint32_t)0x00000000)
#define LPTIM_COUNTERSOURCE_EXTERNAL            LPTIM_CFGR_COUNTMODE
/**
  * @}
  */
#define IS_LPTIM_COUNTER_SOURCE(__SOURCE__)     (((__SOURCE__) == LPTIM_COUNTERSOURCE_INTERNAL) || \
                                                 ((__SOURCE__) == LPTIM_COUNTERSOURCE_EXTERNAL))



/* Check for period value */
#define IS_LPTIM_PERIOD(__PERIOD__)               ((__PERIOD__) <= 0x0000FFFF)

/* Check for pulse value */
#define IS_LPTIM_PULSE(__PULSE__)                 ((__PULSE__) <= 0x0000FFFF)

/** @defgroup LPTIM_Flag_Definition Flag definition
  * @{
  */
#define LPTIM_FLAG_DOWN                          LPTIM_ISR_DOWN
#define LPTIM_FLAG_UP                            LPTIM_ISR_UP
#define LPTIM_FLAG_ARROK                         LPTIM_ISR_ARROK
#define LPTIM_FLAG_CMPOK                         LPTIM_ISR_CMPOK
#define LPTIM_FLAG_EXTTRIG                       LPTIM_ISR_EXTTRIG
#define LPTIM_FLAG_ARRM                          LPTIM_ISR_ARRM
#define LPTIM_FLAG_CMPM                          LPTIM_ISR_CMPM
/**
  * @}
  */

/** @defgroup LPTIM_Interrupts_Definition Interrupts definition
  * @{
  */
#define LPTIM_IT_DOWN                            LPTIM_IER_DOWNIE
#define LPTIM_IT_UP                              LPTIM_IER_UPIE
#define LPTIM_IT_ARROK                           LPTIM_IER_ARROKIE
#define LPTIM_IT_CMPOK                           LPTIM_IER_CMPOKIE
#define LPTIM_IT_EXTTRIG                         LPTIM_IER_EXTTRIGIE
#define LPTIM_IT_ARRM                            LPTIM_IER_ARRMIE
#define LPTIM_IT_CMPM                            LPTIM_IER_CMPMIE
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup LPTIM_Exported_Macros LPTIM Exported Macros
  * @{
  */

/** @brief Reset LPTIM handle state
  * @param  __HANDLE__: LPTIM handle
  * @retval None
  */
#define __HAL_LPTIM_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_LPTIM_STATE_RESET)

/**
  * @brief  Enable/Disable the LPTIM peripheral.
  * @param  __HANDLE__: LPTIM handle
  * @retval None
  */
#define __HAL_LPTIM_ENABLE(__HANDLE__)   ((__HANDLE__)->Instance->CR |=  (LPTIM_CR_ENABLE))
#define __HAL_LPTIM_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR &=  ~(LPTIM_CR_ENABLE))

/**
  * @brief  Starts the LPTIM peripheral in Continuous or in single mode.
  * @param  __HANDLE__: DMA handle
  * @retval None
  */
#define __HAL_LPTIM_START_CONTINUOUS(__HANDLE__)  ((__HANDLE__)->Instance->CR |=  LPTIM_CR_CNTSTRT)
#define __HAL_LPTIM_START_SINGLE(__HANDLE__)      ((__HANDLE__)->Instance->CR |=  LPTIM_CR_SNGSTRT)
 
    
/**
  * @brief  Writes the passed parameter in the Autoreload register.
  * @param  __HANDLE__: LPTIM handle
  * @param  __VALUE__ : Autoreload value
  * @retval None
  */
#define __HAL_LPTIM_AUTORELOAD_SET(__HANDLE__ , __VALUE__)  ((__HANDLE__)->Instance->ARR =  (__VALUE__))

/**
  * @brief  Writes the passed parameter in the Compare register.
  * @param  __HANDLE__: LPTIM handle
  * @param  __VALUE__ : Compare value
  * @retval None
  */
#define __HAL_LPTIM_COMPARE_SET(__HANDLE__ , __VALUE__)     ((__HANDLE__)->Instance->CMP =  (__VALUE__))

/**
  * @brief  Checks whether the specified LPTIM flag is set or not.
  * @param  __HANDLE__: LPTIM handle
  * @param  __FLAG__  : LPTIM flag to check
  *            This parameter can be a value of:
  *            @arg LPTIM_FLAG_DOWN    : Counter direction change up Flag.
  *            @arg LPTIM_FLAG_UP      : Counter direction change down to up Flag.
  *            @arg LPTIM_FLAG_ARROK   : Autoreload register update OK Flag.
  *            @arg LPTIM_FLAG_CMPOK   : Compare register update OK Flag.
  *            @arg LPTIM_FLAG_EXTTRIG : External trigger edge event Flag.
  *            @arg LPTIM_FLAG_ARRM    : Autoreload match Flag.
  *            @arg LPTIM_FLAG_CMPM    : Compare match Flag.
  * @retval The state of the specified flag (SET or RESET).
  */
#define __HAL_LPTIM_GET_FLAG(__HANDLE__, __FLAG__)          (((__HANDLE__)->Instance->ISR &(__FLAG__)) == (__FLAG__))

/**
  * @brief  Clears the specified LPTIM flag.
  * @param  __HANDLE__: LPTIM handle.
  * @param  __FLAG__  : LPTIM flag to clear.
  *            This parameter can be a value of:
  *            @arg LPTIM_FLAG_DOWN    : Counter direction change up Flag.
  *            @arg LPTIM_FLAG_UP      : Counter direction change down to up Flag.
  *            @arg LPTIM_FLAG_ARROK   : Autoreload register update OK Flag.
  *            @arg LPTIM_FLAG_CMPOK   : Compare register update OK Flag.
  *            @arg LPTIM_FLAG_EXTTRIG : External trigger edge event Flag.
  *            @arg LPTIM_FLAG_ARRM    : Autoreload match Flag.
  *            @arg LPTIM_FLAG_CMPM    : Compare match Flag.
  * @retval None.
  */
#define __HAL_LPTIM_CLEAR_FLAG(__HANDLE__, __FLAG__)         ((__HANDLE__)->Instance->ICR  = (__FLAG__))

/**
  * @brief  Enable the specified LPTIM interrupt.
  * @param  __HANDLE__    : LPTIM handle.
  * @param  __INTERRUPT__ : LPTIM interrupt to set.
  *            This parameter can be a value of:
  *            @arg LPTIM_IT_DOWN    : Counter direction change up Interrupt.
  *            @arg LPTIM_IT_UP      : Counter direction change down to up Interrupt.
  *            @arg LPTIM_IT_ARROK   : Autoreload register update OK Interrupt.
  *            @arg LPTIM_IT_CMPOK   : Compare register update OK Interrupt.
  *            @arg LPTIM_IT_EXTTRIG : External trigger edge event Interrupt.
  *            @arg LPTIM_IT_ARRM    : Autoreload match Interrupt.
  *            @arg LPTIM_IT_CMPM    : Compare match Interrupt.
  * @retval None.
  */
#define __HAL_LPTIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)         ((__HANDLE__)->Instance->IER  |= (__INTERRUPT__))

 /**
  * @brief  Disable the specified LPTIM interrupt.
  * @param  __HANDLE__    : LPTIM handle.
  * @param  __INTERRUPT__ : LPTIM interrupt to set.
  *            This parameter can be a value of:
  *            @arg LPTIM_IT_DOWN    : Counter direction change up Interrupt.
  *            @arg LPTIM_IT_UP      : Counter direction change down to up Interrupt.
  *            @arg LPTIM_IT_ARROK   : Autoreload register update OK Interrupt.
  *            @arg LPTIM_IT_CMPOK   : Compare register update OK Interrupt.
  *            @arg LPTIM_IT_EXTTRIG : External trigger edge event Interrupt.
  *            @arg LPTIM_IT_ARRM    : Autoreload match Interrupt.
  *            @arg LPTIM_IT_CMPM    : Compare match Interrupt.
  * @retval None.
  */
#define __HAL_LPTIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)         ((__HANDLE__)->Instance->IER  &= (~(__INTERRUPT__)))

  /**
  * @brief  Checks whether the specified LPTIM interrupt is set or not.
  * @param  __HANDLE__    : LPTIM handle.
  * @param  __INTERRUPT__ : LPTIM interrupt to check.
  *            This parameter can be a value of:
  *            @arg LPTIM_IT_DOWN    : Counter direction change up Interrupt.
  *            @arg LPTIM_IT_UP      : Counter direction change down to up Interrupt.
  *            @arg LPTIM_IT_ARROK   : Autoreload register update OK Interrupt.
  *            @arg LPTIM_IT_CMPOK   : Compare register update OK Interrupt.
  *            @arg LPTIM_IT_EXTTRIG : External trigger edge event Interrupt.
  *            @arg LPTIM_IT_ARRM    : Autoreload match Interrupt.
  *            @arg LPTIM_IT_CMPM    : Compare match Interrupt.
  * @retval Interrupt status.
  */
    
#define __HAL_LPTIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @}
  */


/* Include LPTIM HAL Extension module */
#include "stm32l0xx_hal_lptim_ex.h"

/* Exported functions --------------------------------------------------------*/

/** @defgroup LPTIM_Exported_Functions LPTIM Exported Functions
  * @{
  */
/* Initialization/de-initialization functions  ********************************/

/** @defgroup LPTIM_Exported_Functions_Group1 Initialization/de-initialization functions
  * @{
  */
HAL_StatusTypeDef HAL_LPTIM_Init(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_DeInit(LPTIM_HandleTypeDef *hlptim);


/* MSP functions  *************************************************************/

void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef *hlptim);

/**
  * @}
  */

/* Start/Stop operation functions  *********************************************/

/** @defgroup LPTIM_Exported_Functions_Group2 LPTIM Start-Stop operation functions
  * @{
  */

/* ################################# PWM Mode ################################*/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_LPTIM_PWM_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
HAL_StatusTypeDef HAL_LPTIM_PWM_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_LPTIM_PWM_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
HAL_StatusTypeDef HAL_LPTIM_PWM_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* ############################# One Pulse Mode ##############################*/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* ############################## Set once Mode ##############################*/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* ############################### Encoder Mode ##############################*/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_LPTIM_Encoder_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period);
HAL_StatusTypeDef HAL_LPTIM_Encoder_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_LPTIM_Encoder_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period);
HAL_StatusTypeDef HAL_LPTIM_Encoder_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* ############################# Time out  Mode ##############################*/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_LPTIM_TimeOut_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Timeout);
HAL_StatusTypeDef HAL_LPTIM_TimeOut_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_LPTIM_TimeOut_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Timeout);
HAL_StatusTypeDef HAL_LPTIM_TimeOut_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* ############################## Counter Mode ###############################*/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_LPTIM_Counter_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period);
HAL_StatusTypeDef HAL_LPTIM_Counter_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_LPTIM_Counter_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period);
HAL_StatusTypeDef HAL_LPTIM_Counter_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/**
  * @}
  */

/* Reading operation functions ************************************************/

/** @defgroup LPTIM_Exported_Functions_Group3 LPTIM Read operation functions
  * @{
  */
uint32_t HAL_LPTIM_ReadCounter(LPTIM_HandleTypeDef *hlptim);
uint32_t HAL_LPTIM_ReadAutoReload(LPTIM_HandleTypeDef *hlptim);
uint32_t HAL_LPTIM_ReadCompare(LPTIM_HandleTypeDef *hlptim);
/**
  * @}
  */

/* LPTIM IRQ functions  *******************************************************/
/** @defgroup LPTIM_Exported_Functions_Group4 LPTIM IRQ handler
  * @{
  */
void HAL_LPTIM_IRQHandler(LPTIM_HandleTypeDef *hlptim);

/* CallBack functions  ********************************************************/
void HAL_LPTIM_CompareMatchCallback(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_TriggerCallback(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_CompareWriteCallback(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_AutoReloadWriteCallback(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_DirectionUpCallback(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_DirectionDownCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @}
  */
/* Peripheral State functions  ************************************************/
/** @defgroup LPTIM_Exported_Functions_Group5 Peripheral State functions
  * @{
  */

HAL_LPTIM_StateTypeDef HAL_LPTIM_GetState(LPTIM_HandleTypeDef *hlptim);

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

#endif /* __STM32L0xx_HAL_LPTIM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

