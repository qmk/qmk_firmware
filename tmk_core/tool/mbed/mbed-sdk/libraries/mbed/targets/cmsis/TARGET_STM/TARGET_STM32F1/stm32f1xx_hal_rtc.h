/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rtc.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of RTC HAL module.
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
#ifndef __STM32F1xx_HAL_RTC_H
#define __STM32F1xx_HAL_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */ 

/** @addtogroup RTC_Private_Macros
  * @{
  */

#define IS_RTC_ASYNCH_PREDIV(PREDIV)  (((PREDIV) <= (uint32_t)0xFFFFF) || ((PREDIV) == RTC_AUTO_1_SECOND))
#define IS_RTC_HOUR24(HOUR)           ((HOUR) <= (uint32_t)23)
#define IS_RTC_MINUTES(MINUTES)       ((MINUTES) <= (uint32_t)59)
#define IS_RTC_SECONDS(SECONDS)       ((SECONDS) <= (uint32_t)59)
#define IS_RTC_FORMAT(FORMAT)         (((FORMAT) == RTC_FORMAT_BIN) || ((FORMAT) == RTC_FORMAT_BCD))
#define IS_RTC_YEAR(YEAR)             ((YEAR) <= (uint32_t)99)
#define IS_RTC_MONTH(MONTH)           (((MONTH) >= (uint32_t)1) && ((MONTH) <= (uint32_t)12))
#define IS_RTC_DATE(DATE)             (((DATE) >= (uint32_t)1) && ((DATE) <= (uint32_t)31))
#define IS_RTC_ALARM(ALARM)           ((ALARM) == RTC_ALARM_A)
#define IS_RTC_CALIB_OUTPUT(__OUTPUT__) (((__OUTPUT__) == RTC_OUTPUTSOURCE_NONE) || \
                                         ((__OUTPUT__) == RTC_OUTPUTSOURCE_CALIBCLOCK) || \
                                         ((__OUTPUT__) == RTC_OUTPUTSOURCE_ALARM) || \
                                         ((__OUTPUT__) == RTC_OUTPUTSOURCE_SECOND)) 


/**
  * @}
  */

/** @addtogroup RTC_Private_Constants
  * @{
  */
/** @defgroup RTC_Timeout_Value Default Timeout Value
  * @{
  */ 
#define RTC_TIMEOUT_VALUE           1000
/**
  * @}
  */  
  
/** @defgroup RTC_EXTI_Line_Event RTC EXTI Line event
  * @{
  */ 
#define RTC_EXTI_LINE_ALARM_EVENT   ((uint32_t)0x00020000)  /*!< External interrupt line 17 Connected to the RTC Alarm event */
/**
  * @}
  */


/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup RTC_Exported_Types RTC Exported Types
  * @{
  */
/** 
  * @brief  RTC Time structure definition  
  */
typedef struct
{
  uint8_t Hours;            /*!< Specifies the RTC Time Hour.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 23 */

  uint8_t Minutes;          /*!< Specifies the RTC Time Minutes.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
  
  uint8_t Seconds;          /*!< Specifies the RTC Time Seconds.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
  
}RTC_TimeTypeDef; 

/** 
  * @brief  RTC Alarm structure definition  
  */
typedef struct
{
  RTC_TimeTypeDef AlarmTime;     /*!< Specifies the RTC Alarm Time members */
    
  uint32_t Alarm;                /*!< Specifies the alarm ID (only 1 alarm ID for STM32F1).
                                      This parameter can be a value of @ref RTC_Alarms_Definitions */
}RTC_AlarmTypeDef;
  
/** 
  * @brief  HAL State structures definition  
  */ 
typedef enum
{
  HAL_RTC_STATE_RESET             = 0x00,  /*!< RTC not yet initialized or disabled */
  HAL_RTC_STATE_READY             = 0x01,  /*!< RTC initialized and ready for use   */
  HAL_RTC_STATE_BUSY              = 0x02,  /*!< RTC process is ongoing              */     
  HAL_RTC_STATE_TIMEOUT           = 0x03,  /*!< RTC timeout state                   */  
  HAL_RTC_STATE_ERROR             = 0x04   /*!< RTC error state                     */      
                                                                        
}HAL_RTCStateTypeDef;

/** 
  * @brief  RTC Configuration Structure definition  
  */
typedef struct
{
  uint32_t AsynchPrediv;    /*!< Specifies the RTC Asynchronous Predivider value.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFFFFF  or RTC_AUTO_1_SECOND 
                                 If RTC_AUTO_1_SECOND is selected, AsynchPrediv will be set automatically to get 1sec timebase */
                               
  uint32_t OutPut;          /*!< Specifies which signal will be routed to the RTC Tamper pin.
                                 This parameter can be a value of @ref RTC_output_source_to_output_on_the_Tamper_pin */      
  
}RTC_InitTypeDef;
  
/** 
  * @brief  RTC Date structure definition  
  */
typedef struct
{
  uint8_t WeekDay;  /*!< Specifies the RTC Date WeekDay (not necessary for HAL_RTC_SetDate).
                         This parameter can be a value of @ref RTC_WeekDay_Definitions */
  
  uint8_t Month;    /*!< Specifies the RTC Date Month (in BCD format).
                         This parameter can be a value of @ref RTC_Month_Date_Definitions */

  uint8_t Date;     /*!< Specifies the RTC Date.
                         This parameter must be a number between Min_Data = 1 and Max_Data = 31 */
  
  uint8_t Year;     /*!< Specifies the RTC Date Year.
                         This parameter must be a number between Min_Data = 0 and Max_Data = 99 */
                        
}RTC_DateTypeDef;

/** 
  * @brief  Time Handle Structure definition  
  */ 
typedef struct
{
  RTC_TypeDef                 *Instance;  /*!< Register base address    */

  RTC_InitTypeDef             Init;       /*!< RTC required parameters  */ 

  RTC_DateTypeDef             DateToUpdate;       /*!< Current date set by user and updated automatically  */ 

  HAL_LockTypeDef             Lock;       /*!< RTC locking object       */

  __IO HAL_RTCStateTypeDef    State;      /*!< Time communication state */

}RTC_HandleTypeDef;

/**
  * @}
  */ 

/* Exported constants --------------------------------------------------------*/
/** @defgroup RTC_Exported_Constants RTC Exported Constants
  * @{
  */ 
  
/** @defgroup RTC_Automatic_Prediv_1_Second Automatic calculation of prediv for 1sec timebase
  * @{
  */ 
#define RTC_AUTO_1_SECOND                      ((uint32_t)0xFFFFFFFF)

/**
  * @}
  */

/** @defgroup RTC_Input_parameter_format_definitions Input Parameter Format
  * @{
  */ 
#define RTC_FORMAT_BIN                      ((uint32_t)0x000000000)
#define RTC_FORMAT_BCD                      ((uint32_t)0x000000001)

/**
  * @}
  */

/** @defgroup RTC_Month_Date_Definitions Month Definitions
  * @{
  */ 

/* Coded in BCD format */
#define RTC_MONTH_JANUARY              ((uint8_t)0x01)
#define RTC_MONTH_FEBRUARY             ((uint8_t)0x02)
#define RTC_MONTH_MARCH                ((uint8_t)0x03)
#define RTC_MONTH_APRIL                ((uint8_t)0x04)
#define RTC_MONTH_MAY                  ((uint8_t)0x05)
#define RTC_MONTH_JUNE                 ((uint8_t)0x06)
#define RTC_MONTH_JULY                 ((uint8_t)0x07)
#define RTC_MONTH_AUGUST               ((uint8_t)0x08)
#define RTC_MONTH_SEPTEMBER            ((uint8_t)0x09)
#define RTC_MONTH_OCTOBER              ((uint8_t)0x10)
#define RTC_MONTH_NOVEMBER             ((uint8_t)0x11)
#define RTC_MONTH_DECEMBER             ((uint8_t)0x12)

/**
  * @}
  */ 

/** @defgroup RTC_WeekDay_Definitions WeekDay Definitions 
  * @{
  */ 
#define RTC_WEEKDAY_MONDAY             ((uint8_t)0x01)
#define RTC_WEEKDAY_TUESDAY            ((uint8_t)0x02)
#define RTC_WEEKDAY_WEDNESDAY          ((uint8_t)0x03)
#define RTC_WEEKDAY_THURSDAY           ((uint8_t)0x04)
#define RTC_WEEKDAY_FRIDAY             ((uint8_t)0x05)
#define RTC_WEEKDAY_SATURDAY           ((uint8_t)0x06)
#define RTC_WEEKDAY_SUNDAY             ((uint8_t)0x00)

/**
  * @}
  */ 

/** @defgroup RTC_Alarms_Definitions Alarms Definitions 
  * @{
  */ 
#define RTC_ALARM_A          0                  /*!< Specify alarm ID (mainly for legacy purposes) */

/**
  * @}
  */ 


/** @defgroup RTC_output_source_to_output_on_the_Tamper_pin Output source to output on the Tamper pin
  * @{
  */

#define RTC_OUTPUTSOURCE_NONE               ((uint32_t)0x00000000)            /*!< No output on the TAMPER pin  */
#define RTC_OUTPUTSOURCE_CALIBCLOCK         BKP_RTCCR_CCO                     /*!< RTC clock with a frequency divided by 64 on the TAMPER pin  */
#define RTC_OUTPUTSOURCE_ALARM              BKP_RTCCR_ASOE                    /*!< Alarm pulse signal on the TAMPER pin  */
#define RTC_OUTPUTSOURCE_SECOND             (BKP_RTCCR_ASOS | BKP_RTCCR_ASOE) /*!< Second pulse signal on the TAMPER pin  */

/**
  * @}
  */

/** @defgroup RTC_Interrupts_Definitions Interrupts Definitions 
  * @{
  */ 
#define RTC_IT_OW            RTC_CRH_OWIE       /*!< Overflow interrupt */
#define RTC_IT_ALRA          RTC_CRH_ALRIE      /*!< Alarm interrupt */
#define RTC_IT_SEC           RTC_CRH_SECIE      /*!< Second interrupt */
#define RTC_IT_TAMP1         BKP_CSR_TPIE       /*!< TAMPER Pin interrupt enable */  
/**
  * @}
  */

/** @defgroup RTC_Flags_Definitions Flags Definitions 
  * @{
  */ 
#define RTC_FLAG_RTOFF       RTC_CRL_RTOFF      /*!< RTC Operation OFF flag */
#define RTC_FLAG_RSF         RTC_CRL_RSF        /*!< Registers Synchronized flag */
#define RTC_FLAG_OW          RTC_CRL_OWF        /*!< Overflow flag */
#define RTC_FLAG_ALRAF       RTC_CRL_ALRF       /*!< Alarm flag */
#define RTC_FLAG_SEC         RTC_CRL_SECF       /*!< Second flag */
#define RTC_FLAG_TAMP1F      BKP_CSR_TEF        /*!< Tamper Interrupt Flag */

/**
  * @}
  */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RTC_Exported_macros RTC Exported Macros
  * @{
  */
  
/** @brief  Reset RTC handle state
  * @param  __HANDLE__: RTC handle.
  * @retval None
  */
#define __HAL_RTC_RESET_HANDLE_STATE(__HANDLE__)              ((__HANDLE__)->State = HAL_RTC_STATE_RESET)
 
/**
  * @brief  Disable the write protection for RTC registers.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WRITEPROTECTION_DISABLE(__HANDLE__)         SET_BIT((__HANDLE__)->Instance->CRL, RTC_CRL_CNF)

/**
  * @brief  Enable the write protection for RTC registers.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WRITEPROTECTION_ENABLE(__HANDLE__)          CLEAR_BIT((__HANDLE__)->Instance->CRL, RTC_CRL_CNF)
 
/**
  * @brief  Enable the RTC Alarm interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Alarm interrupt sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_ALRA: Alarm A interrupt
  * @retval None
  */   
#define __HAL_RTC_ALARM_ENABLE_IT(__HANDLE__, __INTERRUPT__)  SET_BIT((__HANDLE__)->Instance->CRH, (__INTERRUPT__))

/**
  * @brief  Disable the RTC Alarm interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Alarm interrupt sources to be enabled or disabled. 
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_ALRA: Alarm A interrupt
  * @retval None
  */
#define __HAL_RTC_ALARM_DISABLE_IT(__HANDLE__, __INTERRUPT__) CLEAR_BIT((__HANDLE__)->Instance->CRH, (__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Alarm interrupt has been enabled or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Alarm interrupt sources to be checked
  *         This parameter can be:
  *            @arg RTC_IT_ALRA: Alarm A interrupt
  * @retval None
  */
#define __HAL_RTC_ALARM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)     ((((((__HANDLE__)->Instance->CRH)& ((__INTERRUPT__)))) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC Alarm's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Alarm Flag sources to be enabled or disabled.
  *          This parameter can be:
  *            @arg RTC_FLAG_ALRAF
  * @retval None
  */
#define __HAL_RTC_ALARM_GET_FLAG(__HANDLE__, __FLAG__)        (((((__HANDLE__)->Instance->CRL) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Check whether the specified RTC Alarm interrupt has occurred or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Alarm interrupt sources to check.
  *         This parameter can be:
  *            @arg RTC_IT_ALRA: Alarm A interrupt
  * @retval None
  */
#define __HAL_RTC_ALARM_GET_IT(__HANDLE__, __INTERRUPT__)        (((((__HANDLE__)->Instance->CRL) & (__INTERRUPT__)) != RESET)? SET : RESET)

/**
  * @brief  Clear the RTC Alarm's pending flags.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Alarm Flag sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_FLAG_ALRAF
  * @retval None
  */
#define __HAL_RTC_ALARM_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((__HANDLE__)->Instance->CRL) = ~(__FLAG__)

/**
  * @brief Enable interrupt on ALARM Exti Line 17.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_IT()                  SET_BIT(EXTI->IMR, RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief Disable interrupt on ALARM Exti Line 17. 
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_IT()                 CLEAR_BIT(EXTI->IMR, RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief Enable event on ALARM Exti Line 17.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_EVENT()               SET_BIT(EXTI->EMR, RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief Disable event on ALARM Exti Line 17.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_EVENT()              CLEAR_BIT(EXTI->EMR, RTC_EXTI_LINE_ALARM_EVENT)


/**
  * @brief  ALARM EXTI line configuration: set falling edge trigger.  
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_FALLING_EDGE()        SET_BIT(EXTI->FTSR, RTC_EXTI_LINE_ALARM_EVENT)


/**
  * @brief Disable the ALARM Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_FALLING_EDGE()       CLEAR_BIT(EXTI->FTSR, RTC_EXTI_LINE_ALARM_EVENT)


/**
  * @brief  ALARM EXTI line configuration: set rising edge trigger.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE()         SET_BIT(EXTI->RTSR, RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief Disable the ALARM Extended Interrupt Rising Trigger.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_RISING_EDGE()        CLEAR_BIT(EXTI->RTSR, RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief  ALARM EXTI line configuration: set rising & falling edge trigger.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_RISING_FALLING_EDGE() __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE();__HAL_RTC_ALARM_EXTI_ENABLE_FALLING_EDGE();

/**
  * @brief Disable the ALARM Extended Interrupt Rising & Falling Trigger.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_RISING_FALLING_EDGE() __HAL_RTC_ALARM_EXTI_DISABLE_RISING_EDGE();__HAL_RTC_ALARM_EXTI_DISABLE_FALLING_EDGE()();

/**
  * @brief Check whether the specified ALARM EXTI interrupt flag is set or not.
  * @retval EXTI ALARM Line Status.
  */
#define __HAL_RTC_ALARM_EXTI_GET_FLAG()                   (EXTI->PR & (RTC_EXTI_LINE_ALARM_EVENT))

/**
  * @brief Clear the ALARM EXTI flag.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_CLEAR_FLAG()                 (EXTI->PR = (RTC_EXTI_LINE_ALARM_EVENT))

/**
  * @brief Generate a Software interrupt on selected EXTI line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_GENERATE_SWIT()              SET_BIT(EXTI->SWIER, RTC_EXTI_LINE_ALARM_EVENT)
/**
  * @}
  */

/* Include RTC HAL Extension module */
#include "stm32f1xx_hal_rtc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RTC_Exported_Functions
  * @{
  */


/* Initialization and de-initialization functions  ****************************/
/** @addtogroup RTC_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_RTC_Init(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_DeInit(RTC_HandleTypeDef *hrtc);
void              HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc);
void              HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */
  
/* RTC Time and Date functions ************************************************/
/** @addtogroup RTC_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_RTC_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_GetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format);
/**
  * @}
  */

/* RTC Alarm functions ********************************************************/
/** @addtogroup RTC_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_RTC_SetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_SetAlarm_IT(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_DeactivateAlarm(RTC_HandleTypeDef *hrtc, uint32_t Alarm);
HAL_StatusTypeDef HAL_RTC_GetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Alarm, uint32_t Format);
void              HAL_RTC_AlarmIRQHandler(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_PollForAlarmAEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
void              HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */

/* Peripheral State functions *************************************************/
/** @addtogroup RTC_Exported_Functions_Group4
  * @{
  */
HAL_RTCStateTypeDef HAL_RTC_GetState(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */

/* Peripheral Control functions ***********************************************/
/** @addtogroup RTC_Exported_Functions_Group5
  * @{
  */
HAL_StatusTypeDef   HAL_RTC_WaitForSynchro(RTC_HandleTypeDef* hrtc);
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

#endif /* __STM32F1xx_HAL_RTC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
