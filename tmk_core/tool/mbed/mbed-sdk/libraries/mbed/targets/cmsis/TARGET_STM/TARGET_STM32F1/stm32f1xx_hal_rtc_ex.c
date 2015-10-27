/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rtc_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Extended RTC HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Real Time Clock (RTC) Extension peripheral:
  *           + RTC Tamper functions 
  *           + Extension Control functions
  *           + Extension RTC features functions    
  *         
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */
  
#ifdef HAL_RTC_MODULE_ENABLED

/** @defgroup RTCEx RTCEx
  * @brief RTC Extended HAL module driver
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup RTCEx_Private_Macros RTCEx Private Macros
  * @{
  */
/**
  * @}
  */
  
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RTCEx_Exported_Functions RTCEx Exported Functions
  * @{
  */
  
/** @defgroup RTCEx_Exported_Functions_Group1 RTC Tamper functions
  * @brief    RTC Tamper functions
  *
@verbatim   
 ===============================================================================
                 ##### RTC Tamper functions #####
 ===============================================================================  
 
 [..] This section provides functions allowing to configure Tamper feature

@endverbatim
  * @{
  */

/**
  * @brief  Sets Tamper
  * @note   By calling this API we disable the tamper interrupt for all tampers. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTamper: Pointer to Tamper Structure.
  * @note   Tamper can be enabled only if ASOE and CCO bit are reset
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef* sTamper)
{
  /* Check input parameters */
  if((hrtc == NULL) || (sTamper == NULL))
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(sTamper->Tamper));
  assert_param(IS_RTC_TAMPER_TRIGGER(sTamper->Trigger));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;
  
  if (HAL_IS_BIT_SET(BKP->RTCCR,(BKP_RTCCR_CCO | BKP_RTCCR_ASOE)))
  {
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hrtc);
    
    return HAL_ERROR;
  }

  MODIFY_REG(BKP->CR, (BKP_CR_TPE | BKP_CR_TPAL), (sTamper->Tamper | (sTamper->Trigger)));

  hrtc->State = HAL_RTC_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Sets Tamper with interrupt.
  * @note   By calling this API we force the tamper interrupt for all tampers.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTamper: Pointer to RTC Tamper.
  * @note   Tamper can be enabled only if ASOE and CCO bit are reset
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef* sTamper)
{
  /* Check input parameters */
  if((hrtc == NULL) || (sTamper == NULL))
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(sTamper->Tamper)); 
  assert_param(IS_RTC_TAMPER_TRIGGER(sTamper->Trigger));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  if (HAL_IS_BIT_SET(BKP->RTCCR,(BKP_RTCCR_CCO | BKP_RTCCR_ASOE)))
  {
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hrtc);
    
    return HAL_ERROR;
  }

  MODIFY_REG(BKP->CR, (BKP_CR_TPE | BKP_CR_TPAL), (sTamper->Tamper | (sTamper->Trigger)));

  /* Configure the Tamper Interrupt in the BKP->CSR */
  __HAL_RTC_TAMPER_ENABLE_IT(hrtc, RTC_IT_TAMP1);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates Tamper.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Tamper: Selected tamper pin.
  *          This parameter can be a value of @ref RTCEx_Tamper_Pins_Definitions
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(RTC_HandleTypeDef *hrtc, uint32_t Tamper)
{
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  assert_param(IS_RTC_TAMPER(Tamper));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the selected Tamper pin */
  CLEAR_BIT(BKP->CR, BKP_CR_TPE);
  
  /* Disable the Tamper Interrupt in the BKP->CSR */
  /* Configure the Tamper Interrupt in the BKP->CSR */
  __HAL_RTC_TAMPER_DISABLE_IT(hrtc, RTC_IT_TAMP1);
  
  /* Clear the Tamper interrupt pending bit */
  __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc, RTC_FLAG_TAMP1F);
  SET_BIT(BKP->CSR, BKP_CSR_CTE);
  
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  This function handles Tamper interrupt request.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTCEx_TamperIRQHandler(RTC_HandleTypeDef *hrtc)
{  
  /* Get the status of the Interrupt */
  if(__HAL_RTC_TAMPER_GET_IT_SOURCE(hrtc, RTC_IT_TAMP1))
  {
    /* Get the TAMPER Interrupt enable bit and pending bit */
    if(__HAL_RTC_TAMPER_GET_FLAG(hrtc, RTC_FLAG_TAMP1F) != (uint32_t)RESET)
    {
      /* Tamper callback */ 
      HAL_RTCEx_Tamper1EventCallback(hrtc);
  
      /* Clear the Tamper interrupt pending bit */
      __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc,RTC_FLAG_TAMP1F);
    }
  }

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}

/**
  * @brief  Tamper 1 callback. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTCEx_Tamper1EventCallback could be implemented in the user file
   */
}

/**
  * @brief  This function handles Tamper1 Polling.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTamper1Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{  
  uint32_t tickstart = HAL_GetTick();

  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Get the status of the Interrupt */
  while(__HAL_RTC_TAMPER_GET_FLAG(hrtc,RTC_FLAG_TAMP1F)== RESET)
  {
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear the Tamper Flag */
  __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc,RTC_FLAG_TAMP1F);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @}
  */
  
/** @defgroup RTCEx_Exported_Functions_Group2 RTC Second functions
  * @brief    RTC Second functions
  *
@verbatim   
 ===============================================================================
                 ##### RTC Second functions #####
 ===============================================================================  
 
 [..] This section provides functions implementing second interupt handlers

@endverbatim
  * @{
  */

/**
  * @brief  Sets Interrupt for second
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetSecond_IT(RTC_HandleTypeDef *hrtc)
{
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Enable Second interuption */
  __HAL_RTC_SECOND_ENABLE_IT(hrtc, RTC_IT_SEC);
  
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates Second.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateSecond(RTC_HandleTypeDef *hrtc)
{
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Deactivate Second interuption*/ 
  __HAL_RTC_SECOND_DISABLE_IT(hrtc, RTC_IT_SEC);
  
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  This function handles second interrupt request.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTCEx_RTCIRQHandler(RTC_HandleTypeDef* hrtc)
{
  if(__HAL_RTC_SECOND_GET_IT_SOURCE(hrtc, RTC_IT_SEC))
  {
    /* Get the status of the Interrupt */
    if(__HAL_RTC_SECOND_GET_FLAG(hrtc, RTC_FLAG_SEC))
    {
      /* Check if Overrun occurred */
      if (__HAL_RTC_SECOND_GET_FLAG(hrtc, RTC_FLAG_OW))
      {
        /* Second error callback */ 
        HAL_RTCEx_RTCEventErrorCallback(hrtc);
        
        /* Clear flag Second */
        __HAL_RTC_OVERFLOW_CLEAR_FLAG(hrtc, RTC_FLAG_OW);
        
        /* Change RTC state */
        hrtc->State = HAL_RTC_STATE_ERROR; 
      }
      else 
      {
        /* Second callback */ 
        HAL_RTCEx_RTCEventCallback(hrtc);
        
        /* Change RTC state */
        hrtc->State = HAL_RTC_STATE_READY; 
      }
      
      /* Clear flag Second */
      __HAL_RTC_SECOND_CLEAR_FLAG(hrtc, RTC_FLAG_SEC);
    }
  }
}

/**
  * @brief  Second event callback.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTCEx_RTCEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Second event error callback.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_RTCEventErrorCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTCEx_RTCEventErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */
  
/** @defgroup RTCEx_Exported_Functions_Group3 Extended Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim   
 ===============================================================================
              ##### Extension Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Writes a data in a specified RTC Backup data register
      (+) Read a data in a specified RTC Backup data register
      (+) Sets the Smooth calibration parameters.

@endverbatim
  * @{
  */

/**
  * @brief  Writes a data in a specified RTC Backup data register.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC. 
  * @param  BackupRegister: RTC Backup data Register number.
  *          This parameter can be: RTC_BKP_DRx where x can be from 1 to 10 (or 42) to 
  *                                 specify the register (depending devices).
  * @param  Data: Data to be written in the specified RTC Backup data register.                     
  * @retval None
  */
void HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_RTC_BKP(BackupRegister));
  
  tmp = (uint32_t)BKP_BASE; 
  tmp += (BackupRegister * 4);

  *(__IO uint32_t *) tmp = (Data & BKP_DR1_D);
}

/**
  * @brief  Reads data from the specified RTC Backup data Register.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC. 
  * @param  BackupRegister: RTC Backup data Register number.
  *          This parameter can be: RTC_BKP_DRx where x can be from 1 to 10 (or 42) to 
  *                                 specify the register (depending devices).
  * @retval Read value
  */
uint32_t HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister)
{
  uint32_t backupregister = 0;
  uint32_t pvalue = 0;

  /* Check the parameters */
  assert_param(IS_RTC_BKP(BackupRegister));

  backupregister = (uint32_t)BKP_BASE; 
  backupregister += (BackupRegister * 4);
  
  pvalue = (*(__IO uint32_t *)(backupregister)) & BKP_DR1_D;

  /* Read the specified register */
  return pvalue;
}


/**
  * @brief  Sets the Smooth calibration parameters.
  * @param  hrtc: RTC handle  
  * @param  SmoothCalibPeriod: Not used (only present for compatibility with another families)
  * @param  SmoothCalibPlusPulses: Not used (only present for compatibility with another families)
  * @param  SmouthCalibMinusPulsesValue: specifies the RTC Clock Calibration value.
  *          This parameter must be a number between 0 and 0x7F.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef* hrtc, uint32_t SmoothCalibPeriod, uint32_t SmoothCalibPlusPulses, uint32_t SmouthCalibMinusPulsesValue)
{
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_SMOOTH_CALIB_MINUS(SmouthCalibMinusPulsesValue));
  
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Sets RTC Clock Calibration value.*/
  MODIFY_REG(BKP->RTCCR, BKP_RTCCR_CAL, SmouthCalibMinusPulsesValue);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */

#endif /* HAL_RTC_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

