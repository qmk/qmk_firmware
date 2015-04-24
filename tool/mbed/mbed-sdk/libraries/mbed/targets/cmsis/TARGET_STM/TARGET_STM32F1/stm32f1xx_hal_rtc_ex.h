/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rtc_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of RTC HAL Extension module.
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
#ifndef __STM32F1xx_HAL_RTC_EX_H
#define __STM32F1xx_HAL_RTC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup RTCEx
  * @{
  */ 

/** @addtogroup RTCEx_Private_Macros
  * @{
  */
  
/** @defgroup RTCEx_Alias_For_Legacy Alias define maintained for legacy
  * @{
  */ 
#define HAL_RTCEx_TamperTimeStampIRQHandler HAL_RTCEx_TamperIRQHandler

/**
  * @}
  */
  
/** @defgroup RTCEx_IS_RTC_Definitions Private macros to check input parameters
  * @{
  */ 
#define IS_RTC_TAMPER(__TAMPER__) ((__TAMPER__) == RTC_TAMPER_1)

#define IS_RTC_TAMPER_TRIGGER(__TRIGGER__)  (((__TRIGGER__) == RTC_TAMPERTRIGGER_LOWLEVEL) || \
                                         ((__TRIGGER__) == RTC_TAMPERTRIGGER_HIGHLEVEL)) 

#if RTC_BKP_NUMBER > 10
#define IS_RTC_BKP(BKP)                   (((BKP) <= (uint32_t) RTC_BKP_DR10) || (((BKP) >= (uint32_t) RTC_BKP_DR11) && ((BKP) <= (uint32_t) RTC_BKP_DR42)))
#else
#define IS_RTC_BKP(BKP)                   ((BKP) <= (uint32_t) RTC_BKP_NUMBER)
#endif
#define IS_RTC_SMOOTH_CALIB_MINUS(__VALUE__) ((__VALUE__) <= 0x0000007F)

/**
  * @}
  */

/**
  * @}
  */
  
/* Exported types ------------------------------------------------------------*/ 
/** @defgroup RTCEx_Exported_Types RTCEx Exported Types
  * @{
  */
/** 
  * @brief  RTC Tamper structure definition  
  */
typedef struct 
{
  uint32_t Tamper;                      /*!< Specifies the Tamper Pin.
                                             This parameter can be a value of @ref  RTCEx_Tamper_Pins_Definitions */
  
  uint32_t Trigger;                     /*!< Specifies the Tamper Trigger.
                                             This parameter can be a value of @ref  RTCEx_Tamper_Trigger_Definitions */

}RTC_TamperTypeDef;

/**
  * @}
  */ 
  
/* Exported constants --------------------------------------------------------*/
/** @defgroup RTCEx_Exported_Constants RTCEx Exported Constants
  * @{
  */ 
  
/** @defgroup RTCEx_Tamper_Pins_Definitions Tamper Pins Definitions
  * @{
  */
#define RTC_TAMPER_1                        BKP_CR_TPE            /*!< Select tamper to be enabled (mainly for legacy purposes) */

/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Trigger_Definitions Tamper Trigger Definitions 
  * @{
  */ 
#define RTC_TAMPERTRIGGER_LOWLEVEL          BKP_CR_TPAL           /*!< A high level on the TAMPER pin resets all data backup registers (if TPE bit is set) */
#define RTC_TAMPERTRIGGER_HIGHLEVEL        ((uint32_t)0x00000000) /*!< A low level on the TAMPER pin resets all data backup registers (if TPE bit is set) */

/**
  * @}
  */  

/** @defgroup RTCEx_Backup_Registers_Definitions Backup Registers Definitions 
  * @{
  */
#if RTC_BKP_NUMBER > 0
#define RTC_BKP_DR1                       ((uint32_t)0x00000001)
#define RTC_BKP_DR2                       ((uint32_t)0x00000002)
#define RTC_BKP_DR3                       ((uint32_t)0x00000003)
#define RTC_BKP_DR4                       ((uint32_t)0x00000004)
#define RTC_BKP_DR5                       ((uint32_t)0x00000005)
#define RTC_BKP_DR6                       ((uint32_t)0x00000006)
#define RTC_BKP_DR7                       ((uint32_t)0x00000007)
#define RTC_BKP_DR8                       ((uint32_t)0x00000008)
#define RTC_BKP_DR9                       ((uint32_t)0x00000009)
#define RTC_BKP_DR10                      ((uint32_t)0x0000000A)
#endif /* RTC_BKP_NUMBER > 0 */
   
#if RTC_BKP_NUMBER > 10
#define RTC_BKP_DR11                      ((uint32_t)0x00000010)
#define RTC_BKP_DR12                      ((uint32_t)0x00000011)
#define RTC_BKP_DR13                      ((uint32_t)0x00000012)
#define RTC_BKP_DR14                      ((uint32_t)0x00000013)
#define RTC_BKP_DR15                      ((uint32_t)0x00000014)
#define RTC_BKP_DR16                      ((uint32_t)0x00000015)
#define RTC_BKP_DR17                      ((uint32_t)0x00000016)
#define RTC_BKP_DR18                      ((uint32_t)0x00000017)
#define RTC_BKP_DR19                      ((uint32_t)0x00000018)
#define RTC_BKP_DR20                      ((uint32_t)0x00000019)
#define RTC_BKP_DR21                      ((uint32_t)0x0000001A)
#define RTC_BKP_DR22                      ((uint32_t)0x0000001B)
#define RTC_BKP_DR23                      ((uint32_t)0x0000001C)
#define RTC_BKP_DR24                      ((uint32_t)0x0000001D)
#define RTC_BKP_DR25                      ((uint32_t)0x0000001E)
#define RTC_BKP_DR26                      ((uint32_t)0x0000001F)
#define RTC_BKP_DR27                      ((uint32_t)0x00000020)
#define RTC_BKP_DR28                      ((uint32_t)0x00000021)
#define RTC_BKP_DR29                      ((uint32_t)0x00000022)
#define RTC_BKP_DR30                      ((uint32_t)0x00000023)
#define RTC_BKP_DR31                      ((uint32_t)0x00000024)
#define RTC_BKP_DR32                      ((uint32_t)0x00000025)
#define RTC_BKP_DR33                      ((uint32_t)0x00000026)
#define RTC_BKP_DR34                      ((uint32_t)0x00000027)
#define RTC_BKP_DR35                      ((uint32_t)0x00000028)
#define RTC_BKP_DR36                      ((uint32_t)0x00000029)
#define RTC_BKP_DR37                      ((uint32_t)0x0000002A)
#define RTC_BKP_DR38                      ((uint32_t)0x0000002B)
#define RTC_BKP_DR39                      ((uint32_t)0x0000002C)
#define RTC_BKP_DR40                      ((uint32_t)0x0000002D)
#define RTC_BKP_DR41                      ((uint32_t)0x0000002E)
#define RTC_BKP_DR42                      ((uint32_t)0x0000002F)
#endif /* RTC_BKP_NUMBER > 10 */

/**
  * @}
  */ 

/**
  * @}
  */
  
/* Exported macro ------------------------------------------------------------*/
/** @defgroup RTCEx_Exported_Macros RTCEx Exported Macros
  * @{
  */
  
/**
  * @brief  Enable the RTC Tamper interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Tamper interrupt sources to be enabled
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_TAMP1: Tamper A interrupt
  * @retval None
  */   
#define __HAL_RTC_TAMPER_ENABLE_IT(__HANDLE__, __INTERRUPT__) SET_BIT(BKP->CSR, (__INTERRUPT__))

/**
  * @brief  Disable the RTC Tamper interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Tamper interrupt sources to be disabled. 
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_TAMP1: Tamper A interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_DISABLE_IT(__HANDLE__, __INTERRUPT__)  CLEAR_BIT(BKP->CSR, (__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Tamper interrupt has been enabled or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Tamper interrupt sources to be checked.
  *         This parameter can be:
  *            @arg  RTC_IT_TAMP1
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)    ((((BKP->CSR) & ((__INTERRUPT__))) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC Tamper's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Tamper Flag sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_FLAG_TAMP1F      
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_FLAG(__HANDLE__, __FLAG__)       ((((BKP->CSR) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC Tamper's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Tamper interrupt sources to be checked.
  *         This parameter can be:
  *            @arg  RTC_IT_TAMP1
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT(__HANDLE__, __INTERRUPT__)       ((((BKP->CSR) & (BKP_CSR_TEF)) != RESET)? SET : RESET)

/**
  * @brief  Clear the RTC Tamper's pending flags.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Tamper Flag sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_FLAG_TAMP1F  
  * @retval None
  */
#define __HAL_RTC_TAMPER_CLEAR_FLAG(__HANDLE__, __FLAG__)     SET_BIT(BKP->CSR, BKP_CSR_CTE | BKP_CSR_CTI)

/**
  * @brief  Enable the RTC Second interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Second interrupt sources to be enabled
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_SEC: Second A interrupt
  * @retval None
  */   
#define __HAL_RTC_SECOND_ENABLE_IT(__HANDLE__, __INTERRUPT__)  SET_BIT((__HANDLE__)->Instance->CRH, (__INTERRUPT__))

/**
  * @brief  Disable the RTC Second interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Second interrupt sources to be disabled. 
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_SEC: Second A interrupt
  * @retval None
  */
#define __HAL_RTC_SECOND_DISABLE_IT(__HANDLE__, __INTERRUPT__) CLEAR_BIT((__HANDLE__)->Instance->CRH, (__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Second interrupt has occurred or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Second interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_SEC: Second A interrupt
  * @retval None
  */
#define __HAL_RTC_SECOND_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)      ((((((__HANDLE__)->Instance->CRH)& ((__INTERRUPT__)))) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC Second's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Second Flag sources to be enabled or disabled.
  *          This parameter can be:
  *            @arg RTC_FLAG_SEC
  * @retval None
  */
#define __HAL_RTC_SECOND_GET_FLAG(__HANDLE__, __FLAG__)        (((((__HANDLE__)->Instance->CRL) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Clear the RTC Second's pending flags.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Second Flag sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_FLAG_SEC
  * @retval None
  */
#define __HAL_RTC_SECOND_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((__HANDLE__)->Instance->CRL) = ~(__FLAG__)

/**
  * @brief  Enable the RTC Overflow interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Overflow interrupt sources to be enabled
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_OW: Overflow A interrupt
  * @retval None
  */   
#define __HAL_RTC_OVERFLOW_ENABLE_IT(__HANDLE__, __INTERRUPT__)  SET_BIT((__HANDLE__)->Instance->CRH, (__INTERRUPT__))

/**
  * @brief  Disable the RTC Overflow interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Overflow interrupt sources to be disabled. 
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_OW: Overflow A interrupt
  * @retval None
  */
#define __HAL_RTC_OVERFLOW_DISABLE_IT(__HANDLE__, __INTERRUPT__) CLEAR_BIT((__HANDLE__)->Instance->CRH, (__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Overflow interrupt has occurred or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Overflow interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_OW: Overflow A interrupt
  * @retval None
  */
#define __HAL_RTC_OVERFLOW_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)    ((((((__HANDLE__)->Instance->CRH)& ((__INTERRUPT__))) ) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC Overflow's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Overflow Flag sources to be enabled or disabled.
  *          This parameter can be:
  *            @arg RTC_FLAG_OW
  * @retval None
  */
#define __HAL_RTC_OVERFLOW_GET_FLAG(__HANDLE__, __FLAG__)        (((((__HANDLE__)->Instance->CRL) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Clear the RTC Overflow's pending flags.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Overflow Flag sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_FLAG_OW
  * @retval None
  */
#define __HAL_RTC_OVERFLOW_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((__HANDLE__)->Instance->CRL) = ~(__FLAG__)

/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RTCEx_Exported_Functions
  * @{
  */
  
/* RTC Tamper functions *****************************************/
/** @addtogroup RTCEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef* sTamper);
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef* sTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(RTC_HandleTypeDef *hrtc, uint32_t Tamper);
void              HAL_RTCEx_TamperIRQHandler(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTamper1Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout);

/**
  * @}
  */
  
/* RTC Second functions *****************************************/
/** @addtogroup RTCEx_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_RTCEx_SetSecond_IT(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateSecond(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_RTCIRQHandler(RTC_HandleTypeDef* hrtc);
void              HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_RTCEventErrorCallback(RTC_HandleTypeDef *hrtc);

/**
  * @}
  */
  
/* Extension Control functions ************************************************/
/** @addtogroup RTCEx_Exported_Functions_Group3
  * @{
  */
void              HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data);
uint32_t          HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister);

HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef* hrtc, uint32_t SmoothCalibPeriod, uint32_t SmoothCalibPlusPulses, uint32_t SmouthCalibMinusPulsesValue);
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

#endif /* __STM32F1xx_HAL_RTC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
