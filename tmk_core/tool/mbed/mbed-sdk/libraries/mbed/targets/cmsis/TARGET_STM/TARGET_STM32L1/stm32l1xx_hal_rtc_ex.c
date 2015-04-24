/**
  ******************************************************************************
  * @file    stm32l1xx_hal_rtc_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Extended RTC HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Real Time Clock (RTC) Extension peripheral:
  *           + RTC Time Stamp functions
  *           + RTC Tamper functions 
  *           + RTC Wake-up functions
  *           + Extension Control functions
  *           + Extension RTC features functions    
  *         
  @verbatim
  ==============================================================================
                  ##### How to use this driver #####
  ==============================================================================
  [..] 
    (+) Enable the RTC domain access.
    (+) Configure the RTC Prescaler (Asynchronous and Synchronous) and RTC hour 
        format using the HAL_RTC_Init() function.
  
  *** RTC Wakeup configuration ***
  ================================
  [..] 
    (+) To configure the RTC Wakeup Clock source and Counter use the HAL_RTCEx_SetWakeUpTimer()
        function. You can also configure the RTC Wakeup timer with interrupt mode 
        using the HAL_RTCEx_SetWakeUpTimer_IT() function.
    (+) To read the RTC WakeUp Counter register, use the HAL_RTCEx_GetWakeUpTimer()
        function.
  
  *** TimeStamp configuration ***
  ===============================
  [..]
    (+) Configure the RTC_AFx trigger and enable the RTC TimeStamp using the 
        HAL_RTCEx_SetTimeStamp() function. You can also configure the RTC TimeStamp with
        interrupt mode using the HAL_RTCEx_SetTimeStamp_IT() function.
    (+) To read the RTC TimeStamp Time and Date register, use the HAL_RTCEx_GetTimeStamp()
        function.
    (+) The TIMESTAMP alternate function can be mapped to RTC_AF1 (PC13).
  
  *** Tamper configuration ***
  ============================
  [..]
    (+) Enable the RTC Tamper and configure the Tamper filter count, trigger Edge 
        or Level according to the Tamper filter (if equal to 0 Edge else Level) 
        value, sampling frequency, precharge or discharge and Pull-UP using the 
        HAL_RTCEx_SetTamper() function. You can configure RTC Tamper with interrupt
        mode using HAL_RTCEx_SetTamper_IT() function.
    (+) The TAMPER1 alternate function can be mapped to RTC_AF1 (PC13).

  *** Backup Data Registers configuration ***
  ===========================================
  [..]
    (+) To write to the RTC Backup Data registers, use the HAL_RTCEx_BKUPWrite()
        function.  
    (+) To read the RTC Backup Data registers, use the HAL_RTCEx_BKUPRead()
        function.
     
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
#include "stm32l1xx_hal.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */
  
/** @addtogroup RTC
  * @{
  */
  
#ifdef HAL_RTC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @addtogroup RTC_Exported_Functions
  * @{
  */


/** @addtogroup RTC_Exported_Functions_Group1
  * @{
  */
  
/**
  * @brief  DeInitializes the RTC peripheral 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @note   This function does not reset the RTC Backup Data registers.   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_DeInit(RTC_HandleTypeDef *hrtc)
{
  uint32_t tickstart = 0;

  /* Check the parameters */
  assert_param(IS_RTC_ALL_INSTANCE(hrtc->Instance));

  /* Set RTC state */
  hrtc->State = HAL_RTC_STATE_BUSY; 
  
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
  
  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc); 
    
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    return HAL_ERROR;
  }  
  else
  {
    /* Reset TR, DR and CR registers */
    hrtc->Instance->TR = (uint32_t)0x00000000;
    hrtc->Instance->DR = (uint32_t)0x00002101;
    /* Reset All CR bits except CR[2:0] */
    hrtc->Instance->CR &= (uint32_t)0x00000007;
    
    tickstart = HAL_GetTick();
    
    /* Wait till WUTWF flag is set and if Time out is reached exit */
    while(((hrtc->Instance->ISR) & RTC_ISR_WUTWF) == (uint32_t)RESET)
    {
      if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      { 
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc); 
        
        /* Set RTC state */
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        
        return HAL_TIMEOUT;
      } 
    }
    
    /* Reset all RTC CR register bits */
    hrtc->Instance->CR &= (uint32_t)0x00000000;
    hrtc->Instance->WUTR = (uint32_t)0x0000FFFF;
    hrtc->Instance->PRER = (uint32_t)0x007F00FF;
    hrtc->Instance->CALIBR = (uint32_t)0x00000000;
    hrtc->Instance->ALRMAR = (uint32_t)0x00000000;
    hrtc->Instance->ALRMBR = (uint32_t)0x00000000;
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
    hrtc->Instance->SHIFTR = (uint32_t)0x00000000;
    hrtc->Instance->CALR = (uint32_t)0x00000000;
    hrtc->Instance->ALRMASSR = (uint32_t)0x00000000;
    hrtc->Instance->ALRMBSSR = (uint32_t)0x00000000;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
    /* Reset ISR register and exit initialization mode */
    hrtc->Instance->ISR = (uint32_t)0x00000000;
    
    /* Reset Tamper and alternate functions configuration register */
    hrtc->Instance->TAFCR = 0x00000000;
    
    /* Wait for synchro */
    if(HAL_RTC_WaitForSynchro(hrtc) != HAL_OK)
    {
      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);  
      
      hrtc->State = HAL_RTC_STATE_ERROR;
      
      return HAL_ERROR;
    }  
  }
  
  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  
  /* De-Initialize RTC MSP */
  HAL_RTC_MspDeInit(hrtc);
  
  hrtc->State = HAL_RTC_STATE_RESET; 
  
  /* Release Lock */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTC_Exported_Functions_Group2
  * @{
  */
  
/**
  * @brief  Gets RTC current time.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTime: Pointer to Time structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg FORMAT_BIN: Binary data format 
  *            @arg FORMAT_BCD: BCD data format
  * @note   Call HAL_RTC_GetDate() after HAL_RTC_GetTime() to unlock the values 
  *         in the higher-order calendar shadow registers.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
  /* Get subseconds values from the correspondent registers*/
  sTime->SubSeconds = (uint32_t)((hrtc->Instance->SSR) & RTC_SSR_SS);
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Get the TR register */
  tmpreg = (uint32_t)(hrtc->Instance->TR & RTC_TR_RESERVED_MASK); 
  
  /* Fill the structure fields with the read parameters */
  sTime->Hours = (uint8_t)((tmpreg & (RTC_TR_HT | RTC_TR_HU)) >> 16);
  sTime->Minutes = (uint8_t)((tmpreg & (RTC_TR_MNT | RTC_TR_MNU)) >>8);
  sTime->Seconds = (uint8_t)(tmpreg & (RTC_TR_ST | RTC_TR_SU));
  sTime->TimeFormat = (uint8_t)((tmpreg & (RTC_TR_PM)) >> 16); 
  
  /* Check the input parameters format */
  if(Format == FORMAT_BIN)
  {
    /* Convert the time structure parameters to Binary format */
    sTime->Hours = (uint8_t)RTC_Bcd2ToByte(sTime->Hours);
    sTime->Minutes = (uint8_t)RTC_Bcd2ToByte(sTime->Minutes);
    sTime->Seconds = (uint8_t)RTC_Bcd2ToByte(sTime->Seconds);  
  }
  
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RTC_Exported_Functions_Group3
  * @{
  */

/**
  * @brief  Sets the specified RTC Alarm.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sAlarm: Pointer to Alarm structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg FORMAT_BIN: Binary data format 
  *             @arg FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format)
{
  uint32_t tickstart = 0;
  uint32_t tmpreg = 0;
  
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
  uint32_t subsecondtmpreg = 0;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_ALARM(sAlarm->Alarm));
  assert_param(IS_ALARM_MASK(sAlarm->AlarmMask));
  assert_param(IS_RTC_ALARM_DATE_WEEKDAY_SEL(sAlarm->AlarmDateWeekDaySel));
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
  assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(sAlarm->AlarmTime.SubSeconds));
  assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(sAlarm->AlarmSubSecondMask));
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Process Locked */ 
  __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY;
  
  if(Format == FORMAT_BIN)
  {
    if((hrtc->Instance->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      assert_param(IS_RTC_HOUR12(sAlarm->AlarmTime.Hours));
      assert_param(IS_RTC_HOURFORMAT12(sAlarm->AlarmTime.TimeFormat));
    } 
    else
    {
      sAlarm->AlarmTime.TimeFormat = 0x00;
      assert_param(IS_RTC_HOUR24(sAlarm->AlarmTime.Hours));
    }
    assert_param(IS_RTC_MINUTES(sAlarm->AlarmTime.Minutes));
    assert_param(IS_RTC_SECONDS(sAlarm->AlarmTime.Seconds));
    
    if(sAlarm->AlarmDateWeekDaySel == RTC_ALARMDATEWEEKDAYSEL_DATE)
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(sAlarm->AlarmDateWeekDay));
    }
    else
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(sAlarm->AlarmDateWeekDay));
    }
    
    tmpreg = (((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Hours) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Minutes) << 8) | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Seconds)) | \
              ((uint32_t)(sAlarm->AlarmTime.TimeFormat) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmDateWeekDay) << 24) | \
              ((uint32_t)sAlarm->AlarmDateWeekDaySel) | \
              ((uint32_t)sAlarm->AlarmMask)); 
  }
  else
  {
    if((hrtc->Instance->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      tmpreg = RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours);
      assert_param(IS_RTC_HOUR12(tmpreg));
      assert_param(IS_RTC_HOURFORMAT12(sAlarm->AlarmTime.TimeFormat));
    } 
    else
    {
      sAlarm->AlarmTime.TimeFormat = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)));
    }
    
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds)));
    
    if(sAlarm->AlarmDateWeekDaySel == RTC_ALARMDATEWEEKDAYSEL_DATE)
    {
      tmpreg = RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay);
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(tmpreg));    
    }
    else
    {
      tmpreg = RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay);
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(tmpreg));      
    }  
    
    tmpreg = (((uint32_t)(sAlarm->AlarmTime.Hours) << 16) | \
              ((uint32_t)(sAlarm->AlarmTime.Minutes) << 8) | \
              ((uint32_t) sAlarm->AlarmTime.Seconds) | \
              ((uint32_t)(sAlarm->AlarmTime.TimeFormat) << 16) | \
              ((uint32_t)(sAlarm->AlarmDateWeekDay) << 24) | \
              ((uint32_t)sAlarm->AlarmDateWeekDaySel) | \
              ((uint32_t)sAlarm->AlarmMask));   
  }
  
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
  /* Configure the Alarm A or Alarm B Sub Second registers */
  subsecondtmpreg = (uint32_t)((uint32_t)(sAlarm->AlarmTime.SubSeconds) | (uint32_t)(sAlarm->AlarmSubSecondMask));
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the Alarm register */
  if(sAlarm->Alarm == RTC_ALARM_A)
  {
    /* Disable the Alarm A interrupt */
    __HAL_RTC_ALARMA_DISABLE(hrtc);
    
    /* In case of interrupt mode is used, the interrupt source must disabled */ 
    __HAL_RTC_ALARM_DISABLE_IT(hrtc, RTC_IT_ALRA);
         
    tickstart = HAL_GetTick();
    /* Wait till RTC ALRAWF flag is set and if Time out is reached exit */
    while(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAWF) == RESET)
    {
      if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
        
        hrtc->State = HAL_RTC_STATE_TIMEOUT; 
        
        /* Process Unlocked */ 
        __HAL_UNLOCK(hrtc);
        
        return HAL_TIMEOUT;
      }   
    }
    
    hrtc->Instance->ALRMAR = (uint32_t)tmpreg;
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
    /* Configure the Alarm A Sub Second register */
    hrtc->Instance->ALRMASSR = subsecondtmpreg;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
    /* Configure the Alarm state: Enable Alarm */
    __HAL_RTC_ALARMA_ENABLE(hrtc);
  }
  else
  {
    /* Disable the Alarm B interrupt */
    __HAL_RTC_ALARMB_DISABLE(hrtc);
    
    /* In case of interrupt mode is used, the interrupt source must disabled */ 
    __HAL_RTC_ALARM_DISABLE_IT(hrtc, RTC_IT_ALRB);
       
    tickstart = HAL_GetTick();
    /* Wait till RTC ALRBWF flag is set and if Time out is reached exit */
    while(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRBWF) == RESET)
    {
      if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
        
        hrtc->State = HAL_RTC_STATE_TIMEOUT; 
        
        /* Process Unlocked */ 
        __HAL_UNLOCK(hrtc);
        
        return HAL_TIMEOUT;
      }  
    }    
    
    hrtc->Instance->ALRMBR = (uint32_t)tmpreg;
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
    /* Configure the Alarm B Sub Second register */
    hrtc->Instance->ALRMBSSR = subsecondtmpreg;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
    /* Configure the Alarm state: Enable Alarm */
    __HAL_RTC_ALARMB_ENABLE(hrtc); 
  }
  
  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);   
  
  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY; 
  
  /* Process Unlocked */ 
  __HAL_UNLOCK(hrtc);
  
  return HAL_OK;
}

/**
  * @brief  Sets the specified RTC Alarm with Interrupt 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sAlarm: Pointer to Alarm structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg FORMAT_BIN: Binary data format 
  *             @arg FORMAT_BCD: BCD data format
  * @note   The Alarm register can only be written when the corresponding Alarm
  *         is disabled (Use the HAL_RTC_DeactivateAlarm()).   
  * @note   The HAL_RTC_SetTime() must be called before enabling the Alarm feature.   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetAlarm_IT(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format)
{
  uint32_t tickstart = 0;
  uint32_t tmpreg = 0;
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  uint32_t subsecondtmpreg = 0;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_ALARM(sAlarm->Alarm));
  assert_param(IS_ALARM_MASK(sAlarm->AlarmMask));
  assert_param(IS_RTC_ALARM_DATE_WEEKDAY_SEL(sAlarm->AlarmDateWeekDaySel));
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
  assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(sAlarm->AlarmTime.SubSeconds));
  assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(sAlarm->AlarmSubSecondMask));
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Process Locked */ 
  __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY;
  
  if(Format == FORMAT_BIN)
  {
    if((hrtc->Instance->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      assert_param(IS_RTC_HOUR12(sAlarm->AlarmTime.Hours));
      assert_param(IS_RTC_HOURFORMAT12(sAlarm->AlarmTime.TimeFormat));
    } 
    else
    {
      sAlarm->AlarmTime.TimeFormat = 0x00;
      assert_param(IS_RTC_HOUR24(sAlarm->AlarmTime.Hours));
    }
    assert_param(IS_RTC_MINUTES(sAlarm->AlarmTime.Minutes));
    assert_param(IS_RTC_SECONDS(sAlarm->AlarmTime.Seconds));
    
    if(sAlarm->AlarmDateWeekDaySel == RTC_ALARMDATEWEEKDAYSEL_DATE)
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(sAlarm->AlarmDateWeekDay));
    }
    else
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(sAlarm->AlarmDateWeekDay));
    }
    tmpreg = (((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Hours) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Minutes) << 8) | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmTime.Seconds)) | \
              ((uint32_t)(sAlarm->AlarmTime.TimeFormat) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(sAlarm->AlarmDateWeekDay) << 24) | \
              ((uint32_t)sAlarm->AlarmDateWeekDaySel) | \
              ((uint32_t)sAlarm->AlarmMask)); 
  }
  else
  {
    if((hrtc->Instance->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      tmpreg = RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours);
      assert_param(IS_RTC_HOUR12(tmpreg));
      assert_param(IS_RTC_HOURFORMAT12(sAlarm->AlarmTime.TimeFormat));
    } 
    else
    {
      sAlarm->AlarmTime.TimeFormat = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)));
    }
    
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds)));
    
    if(sAlarm->AlarmDateWeekDaySel == RTC_ALARMDATEWEEKDAYSEL_DATE)
    {
      tmpreg = RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay);
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(tmpreg));    
    }
    else
    {
      tmpreg = RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay);
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(tmpreg));      
    }
    tmpreg = (((uint32_t)(sAlarm->AlarmTime.Hours) << 16) | \
              ((uint32_t)(sAlarm->AlarmTime.Minutes) << 8) | \
              ((uint32_t) sAlarm->AlarmTime.Seconds) | \
              ((uint32_t)(sAlarm->AlarmTime.TimeFormat) << 16) | \
              ((uint32_t)(sAlarm->AlarmDateWeekDay) << 24) | \
              ((uint32_t)sAlarm->AlarmDateWeekDaySel) | \
              ((uint32_t)sAlarm->AlarmMask));     
  }
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
  /* Configure the Alarm A or Alarm B Sub Second registers */
  subsecondtmpreg = (uint32_t)((uint32_t)(sAlarm->AlarmTime.SubSeconds) | (uint32_t)(sAlarm->AlarmSubSecondMask));
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
  
  /* Configure the Alarm register */
  if(sAlarm->Alarm == RTC_ALARM_A)
  {
    /* Disable the Alarm A interrupt */
    __HAL_RTC_ALARMA_DISABLE(hrtc);

    /* Clear flag alarm A */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);

    tickstart = HAL_GetTick();
    /* Wait till RTC ALRAWF flag is set and if Time out is reached exit */
    while(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAWF) == RESET)
    {
      if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
        
        hrtc->State = HAL_RTC_STATE_TIMEOUT; 
        
        /* Process Unlocked */ 
        __HAL_UNLOCK(hrtc);
        
        return HAL_TIMEOUT;
      }  
    }
    
    hrtc->Instance->ALRMAR = (uint32_t)tmpreg;
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
    /* Configure the Alarm A Sub Second register */
    hrtc->Instance->ALRMASSR = subsecondtmpreg;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
    /* Configure the Alarm state: Enable Alarm */
    __HAL_RTC_ALARMA_ENABLE(hrtc);
    /* Configure the Alarm interrupt */
    __HAL_RTC_ALARM_ENABLE_IT(hrtc,RTC_IT_ALRA);
  }
  else
  {
    /* Disable the Alarm B interrupt */
    __HAL_RTC_ALARMB_DISABLE(hrtc);

    /* Clear flag alarm B */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRBF);

    tickstart = HAL_GetTick();
    /* Wait till RTC ALRBWF flag is set and if Time out is reached exit */
    while(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRBWF) == RESET)
    {
      if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
        
        hrtc->State = HAL_RTC_STATE_TIMEOUT; 
        
        /* Process Unlocked */ 
        __HAL_UNLOCK(hrtc);
        
        return HAL_TIMEOUT;
      }  
    }

    hrtc->Instance->ALRMBR = (uint32_t)tmpreg;
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
    /* Configure the Alarm B Sub Second register */
    hrtc->Instance->ALRMBSSR = subsecondtmpreg;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
    /* Configure the Alarm state: Enable Alarm */
    __HAL_RTC_ALARMB_ENABLE(hrtc);
    /* Configure the Alarm interrupt */
    __HAL_RTC_ALARM_ENABLE_IT(hrtc, RTC_IT_ALRB);
  }

  /* RTC Alarm Interrupt Configuration: EXTI configuration */
  __HAL_RTC_ENABLE_IT(RTC_EXTI_LINE_ALARM_EVENT);
  
  EXTI->RTSR |= RTC_EXTI_LINE_ALARM_EVENT;
  
  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);  
  
  hrtc->State = HAL_RTC_STATE_READY; 
  
  /* Process Unlocked */ 
  __HAL_UNLOCK(hrtc);  
  
  return HAL_OK;
}

/**
  * @brief  Gets the RTC Alarm value and masks.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sAlarm: Pointer to Date structure
  * @param  Alarm: Specifies the Alarm.
  *          This parameter can be one of the following values:
  *             @arg RTC_ALARM_A: AlarmA
  *             @arg RTC_ALARM_B: AlarmB  
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg FORMAT_BIN: Binary data format 
  *             @arg FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Alarm, uint32_t Format)
{
  uint32_t tmpreg = 0;
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  uint32_t subsecondtmpreg = 0;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_ALARM(Alarm));
  
  if(Alarm == RTC_ALARM_A)
  {
    /* AlarmA */
    sAlarm->Alarm = RTC_ALARM_A;
    
    tmpreg = (uint32_t)(hrtc->Instance->ALRMAR);
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
    subsecondtmpreg = (uint32_t)((hrtc->Instance->ALRMASSR) & RTC_ALRMASSR_SS);
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */    
  }
  else
  {
    sAlarm->Alarm = RTC_ALARM_B;
    
    tmpreg = (uint32_t)(hrtc->Instance->ALRMBR);
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
    subsecondtmpreg = (uint32_t)((hrtc->Instance->ALRMBSSR) & RTC_ALRMBSSR_SS);
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */    
  }
    
  /* Fill the structure with the read parameters */
  sAlarm->AlarmTime.Hours = (uint32_t)((tmpreg & (RTC_ALRMAR_HT | RTC_ALRMAR_HU)) >> 16);
  sAlarm->AlarmTime.Minutes = (uint32_t)((tmpreg & (RTC_ALRMAR_MNT | RTC_ALRMAR_MNU)) >> 8);
  sAlarm->AlarmTime.Seconds = (uint32_t)(tmpreg & (RTC_ALRMAR_ST | RTC_ALRMAR_SU));
  sAlarm->AlarmTime.TimeFormat = (uint32_t)((tmpreg & RTC_ALRMAR_PM) >> 16);
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  sAlarm->AlarmTime.SubSeconds = (uint32_t) subsecondtmpreg;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */  
  sAlarm->AlarmDateWeekDay = (uint32_t)((tmpreg & (RTC_ALRMAR_DT | RTC_ALRMAR_DU)) >> 24);
  sAlarm->AlarmDateWeekDaySel = (uint32_t)(tmpreg & RTC_ALRMAR_WDSEL);
  sAlarm->AlarmMask = (uint32_t)(tmpreg & RTC_ALARMMASK_ALL);
    
  if(Format == FORMAT_BIN)
  {
    sAlarm->AlarmTime.Hours = RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours);
    sAlarm->AlarmTime.Minutes = RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes);
    sAlarm->AlarmTime.Seconds = RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds);
    sAlarm->AlarmDateWeekDay = RTC_Bcd2ToByte(sAlarm->AlarmDateWeekDay);
  }  
    
  return HAL_OK;
}

/**
  * @}
  */


/** @defgroup RTC_Exported_Functions_Group6 Peripheral Control functions 
 *  @brief   Peripheral Control functions 
 *
@verbatim   
 ===============================================================================
                     ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Wait for RTC Time and Date Synchronization

@endverbatim
  * @{
  */

/**
  * @brief  Waits until the RTC Time and Date registers (RTC_TR and RTC_DR) are 
  *         synchronized with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the 
  *         __HAL_RTC_WRITEPROTECTION_DISABLE() before calling this function.
  * @note   To read the calendar through the shadow registers after Calendar 
  *         initialization, calendar update or after wakeup from low power modes 
  *         the software must first clear the RSF flag. 
  *         The software must then wait until it is set again before reading 
  *         the calendar, which means that the calendar registers have been 
  *         correctly copied into the RTC_TR and RTC_DR shadow registers.   
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_WaitForSynchro(RTC_HandleTypeDef* hrtc)
{
  uint32_t tickstart = 0;
  
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  /* If RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
  if((hrtc->Instance->CR & RTC_CR_BYPSHAD) == RESET)
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  {
    /* Clear RSF flag */
    hrtc->Instance->ISR &= (uint32_t)RTC_RSF_MASK;
    
  tickstart = HAL_GetTick();

    /* Wait the registers to be synchronised */
    while((hrtc->Instance->ISR & RTC_ISR_RSF) == (uint32_t)RESET)
    {
    if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      {       
        return HAL_TIMEOUT;
      } 
    }
  }

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
    
/** @defgroup RTCEx RTCEx
  * @brief RTC Extended HAL module driver
  * @{
  */
  
/** @defgroup RTCEx_Exported_Functions RTCEx Exported Functions
  * @{
  */
  
/** @defgroup RTCEx_Exported_Functions_Group4 RTC TimeStamp and Tamper functions
  * @brief    RTC TimeStamp and Tamper functions
  *
@verbatim   
 ===============================================================================
                 ##### RTC TimeStamp and Tamper functions #####
 ===============================================================================  
 
 [..] This section provides functions allowing to configure TimeStamp feature

@endverbatim
  * @{
  */

/**
  * @brief  Sets TimeStamp.
  * @note   This API must be called before enabling the TimeStamp feature. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  TimeStampEdge: Specifies the pin edge on which the TimeStamp is 
  *         activated.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPEDGE_RISING: the Time stamp event occurs on the  
  *                                        rising edge of the related pin.
  *             @arg RTC_TIMESTAMPEDGE_FALLING: the Time stamp event occurs on the 
  *                                         falling edge of the related pin.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_TIMESTAMP_EDGE(TimeStampEdge));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(hrtc->Instance->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

  tmpreg|= TimeStampEdge;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the Time Stamp TSEDGE and Enable bits */
  hrtc->Instance->CR = (uint32_t)tmpreg;

  __HAL_RTC_TIMESTAMP_ENABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Sets TimeStamp with Interrupt. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @note   This API must be called before enabling the TimeStamp feature.
  * @param  TimeStampEdge: Specifies the pin edge on which the TimeStamp is 
  *         activated.
  *          This parameter can be one of the following values:
  *             @arg RTC_TIMESTAMPEDGE_RISING: the Time stamp event occurs on the  
  *                                        rising edge of the related pin.
  *             @arg RTC_TIMESTAMPEDGE_FALLING: the Time stamp event occurs on the 
  *                                         falling edge of the related pin.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp_IT(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_TIMESTAMP_EDGE(TimeStampEdge));

  /* Process Locked */ 
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(hrtc->Instance->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

  tmpreg |= TimeStampEdge;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Configure the Time Stamp TSEDGE and Enable bits */
  hrtc->Instance->CR = (uint32_t)tmpreg;

  __HAL_RTC_TIMESTAMP_ENABLE(hrtc);

  /* Enable IT timestamp */
  __HAL_RTC_TIMESTAMP_ENABLE_IT(hrtc,RTC_IT_TS);

  /* RTC timestamp Interrupt Configuration: EXTI configuration */
  __HAL_RTC_ENABLE_IT(RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT);

  EXTI->RTSR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT;

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates TimeStamp. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateTimeStamp(RTC_HandleTypeDef *hrtc)
{
  uint32_t tmpreg = 0;

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* In case of interrupt mode is used, the interrupt source must disabled */
  __HAL_RTC_TIMESTAMP_DISABLE_IT(hrtc, RTC_IT_TS);

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(hrtc->Instance->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

  /* Configure the Time Stamp TSEDGE and Enable bits */
  hrtc->Instance->CR = (uint32_t)tmpreg;

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Gets the RTC TimeStamp value.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTimeStamp: Pointer to Time structure
  * @param  sTimeStampDate: Pointer to Date structure  
  * @param  Format: specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             FORMAT_BIN: Binary data format 
  *             FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_GetTimeStamp(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef* sTimeStamp, RTC_DateTypeDef* sTimeStampDate, uint32_t Format)
{
  uint32_t tmptime = 0, tmpdate = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));

  /* Get the TimeStamp time and date registers values */
  tmptime = (uint32_t)(hrtc->Instance->TSTR & RTC_TR_RESERVED_MASK);
  tmpdate = (uint32_t)(hrtc->Instance->TSDR & RTC_DR_RESERVED_MASK);

  /* Fill the Time structure fields with the read parameters */
  sTimeStamp->Hours = (uint8_t)((tmptime & (RTC_TR_HT | RTC_TR_HU)) >> 16);
  sTimeStamp->Minutes = (uint8_t)((tmptime & (RTC_TR_MNT | RTC_TR_MNU)) >> 8);
  sTimeStamp->Seconds = (uint8_t)(tmptime & (RTC_TR_ST | RTC_TR_SU));
  sTimeStamp->TimeFormat = (uint8_t)((tmptime & (RTC_TR_PM)) >> 16);
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  sTimeStamp->SubSeconds = (uint32_t)((hrtc->Instance->TSSSR) & RTC_TSSSR_SS);
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

  /* Fill the Date structure fields with the read parameters */
  sTimeStampDate->Year = 0;
  sTimeStampDate->Month = (uint8_t)((tmpdate & (RTC_DR_MT | RTC_DR_MU)) >> 8);
  sTimeStampDate->Date = (uint8_t)(tmpdate & (RTC_DR_DT | RTC_DR_DU));
  sTimeStampDate->WeekDay = (uint8_t)((tmpdate & (RTC_DR_WDU)) >> 13);

  /* Check the input parameters format */
  if(Format == FORMAT_BIN)
  {
    /* Convert the TimeStamp structure parameters to Binary format */
    sTimeStamp->Hours = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Hours);
    sTimeStamp->Minutes = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Minutes);
    sTimeStamp->Seconds = (uint8_t)RTC_Bcd2ToByte(sTimeStamp->Seconds);

    /* Convert the DateTimeStamp structure parameters to Binary format */
    sTimeStampDate->Month = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->Month);
    sTimeStampDate->Date = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->Date);
    sTimeStampDate->WeekDay = (uint8_t)RTC_Bcd2ToByte(sTimeStampDate->WeekDay);
  }

  /* Clear the TIMESTAMP Flag */
  __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSF);

  return HAL_OK;
}

/**
  * @brief  Sets Tamper
  * @note   By calling this API we disable the tamper interrupt for all tampers. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTamper: Pointer to Tamper Structure.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef* sTamper)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_TAMPER(sTamper->Tamper));
  assert_param(IS_TAMPER_TRIGGER(sTamper->Trigger));
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  assert_param(IS_TAMPER_FILTER(sTamper->Filter));
  assert_param(IS_TAMPER_SAMPLING_FREQ(sTamper->SamplingFrequency));
  assert_param(IS_TAMPER_PRECHARGE_DURATION(sTamper->PrechargeDuration));
  assert_param(IS_TAMPER_PULLUP_STATE(sTamper->TamperPullUp));
  assert_param(IS_TAMPER_TIMESTAMPONTAMPER_DETECTION(sTamper->TimeStampOnTamperDetection));
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  if((sTamper->Trigger == RTC_TAMPERTRIGGER_RISINGEDGE))
  {
    /* Configure the RTC_TAFCR register */
    sTamper->Trigger = RTC_TAMPERTRIGGER_RISINGEDGE;
  }
  else
  {
    sTamper->Trigger = (uint32_t)(sTamper->Tamper << 1);
  }

  tmpreg = ((uint32_t)sTamper->Tamper | (uint32_t)sTamper->Trigger | (uint32_t)sTamper->Filter |\
            (uint32_t)sTamper->SamplingFrequency | (uint32_t)sTamper->PrechargeDuration |\
            (uint32_t)sTamper->TamperPullUp | sTamper->TimeStampOnTamperDetection);

  hrtc->Instance->TAFCR &= (uint32_t)~((uint32_t)sTamper->Tamper | (uint32_t)(sTamper->Tamper << 1) | (uint32_t)RTC_TAFCR_TAMPTS |\
                                       (uint32_t)RTC_TAFCR_TAMPFREQ | (uint32_t)RTC_TAFCR_TAMPFLT | (uint32_t)RTC_TAFCR_TAMPPRCH |\
                                       (uint32_t)RTC_TAFCR_TAMPPUDIS | (uint32_t)RTC_TAFCR_TAMPIE);
#else
  tmpreg = ((uint32_t)sTamper->Tamper | (uint32_t)(sTamper->Trigger));

  hrtc->Instance->TAFCR &= (uint32_t)~((uint32_t)RTC_TAFCR_TAMP1E | (uint32_t)RTC_TAFCR_TAMP1TRG);

#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  hrtc->Instance->TAFCR |= tmpreg;
  
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
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef* sTamper)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_TAMPER(sTamper->Tamper)); 
  assert_param(IS_TAMPER_TRIGGER(sTamper->Trigger));
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  assert_param(IS_TAMPER_FILTER(sTamper->Filter));
  assert_param(IS_TAMPER_SAMPLING_FREQ(sTamper->SamplingFrequency));
  assert_param(IS_TAMPER_PRECHARGE_DURATION(sTamper->PrechargeDuration));
  assert_param(IS_TAMPER_PULLUP_STATE(sTamper->TamperPullUp));
  assert_param(IS_TAMPER_TIMESTAMPONTAMPER_DETECTION(sTamper->TimeStampOnTamperDetection));
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  /* Configure the tamper trigger */
  if((sTamper->Trigger == RTC_TAMPERTRIGGER_RISINGEDGE))
  {
    sTamper->Trigger = RTC_TAMPERTRIGGER_RISINGEDGE;
  }
  else
  {
    sTamper->Trigger = (uint32_t) (sTamper->Tamper<<1);
  }

  tmpreg = ((uint32_t)sTamper->Tamper | (uint32_t)sTamper->Trigger | (uint32_t)sTamper->Filter |\
            (uint32_t)sTamper->SamplingFrequency | (uint32_t)sTamper->PrechargeDuration |\
            (uint32_t)sTamper->TamperPullUp | sTamper->TimeStampOnTamperDetection);

  hrtc->Instance->TAFCR &= (uint32_t)~((uint32_t)sTamper->Tamper | (uint32_t)(sTamper->Tamper << 1) | (uint32_t)RTC_TAFCR_TAMPTS |\
                                       (uint32_t)RTC_TAFCR_TAMPFREQ | (uint32_t)RTC_TAFCR_TAMPFLT | (uint32_t)RTC_TAFCR_TAMPPRCH |\
                                       (uint32_t)RTC_TAFCR_TAMPPUDIS);
#else
  tmpreg = ((uint32_t)sTamper->Tamper | (uint32_t)sTamper->Trigger);

  hrtc->Instance->TAFCR &= (uint32_t)~((uint32_t)RTC_TAFCR_TAMP1E | (uint32_t)RTC_TAFCR_TAMP1TRG | (uint32_t)RTC_TAFCR_TAMPIE);
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  hrtc->Instance->TAFCR |= tmpreg;

  /* Configure the Tamper Interrupt in the RTC_TAFCR */
  hrtc->Instance->TAFCR |= (uint32_t)RTC_TAFCR_TAMPIE;

  /* RTC Tamper Interrupt Configuration: EXTI configuration */
  __HAL_RTC_ENABLE_IT(RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT);

  EXTI->RTSR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT;

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
  assert_param(IS_TAMPER(Tamper));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the selected Tamper pin */
  hrtc->Instance->TAFCR &= (uint32_t)~Tamper;

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  This function handles TimeStamp interrupt request.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTCEx_TamperTimeStampIRQHandler(RTC_HandleTypeDef *hrtc)
{  
  if(__HAL_RTC_TIMESTAMP_GET_IT(hrtc, RTC_IT_TS))
  {
    /* Get the status of the Interrupt */
    if((uint32_t)(hrtc->Instance->CR & RTC_IT_TS) != (uint32_t)RESET)
    {
      /* TIMESTAMP callback */ 
      HAL_RTCEx_TimeStampEventCallback(hrtc);
  
      /* Clear the TIMESTAMP interrupt pending bit */
      __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc,RTC_FLAG_TSF);
    }
  }

  /* Get the status of the Interrupt */
  if(__HAL_RTC_TAMPER_GET_IT(hrtc,RTC_IT_TAMP1))
  {
    /* Get the TAMPER Interrupt enable bit and pending bit */
    if(((hrtc->Instance->TAFCR & (RTC_TAFCR_TAMPIE))) != (uint32_t)RESET)
    {
      /* Tamper callback */ 
      HAL_RTCEx_Tamper1EventCallback(hrtc);
  
      /* Clear the Tamper interrupt pending bit */
      __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc,RTC_FLAG_TAMP1F);
    }
  }

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  /* Get the status of the Interrupt */
  if(__HAL_RTC_TAMPER_GET_IT(hrtc, RTC_IT_TAMP2))
  {
    /* Get the TAMPER Interrupt enable bit and pending bit */
    if(((hrtc->Instance->TAFCR & RTC_TAFCR_TAMPIE)) != (uint32_t)RESET)
    {
      /* Tamper callback */ 
      HAL_RTCEx_Tamper2EventCallback(hrtc);
  
      /* Clear the Tamper interrupt pending bit */
      __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc, RTC_FLAG_TAMP2F);
    }
  }

  /* Get the status of the Interrupt */
  if(__HAL_RTC_TAMPER_GET_IT(hrtc, RTC_IT_TAMP3))
  {
    /* Get the TAMPER Interrupt enable bit and pending bit */
    if(((hrtc->Instance->TAFCR & RTC_TAFCR_TAMPIE)) != (uint32_t)RESET)
    {
      /* Tamper callback */
      HAL_RTCEx_Tamper3EventCallback(hrtc);

      /* Clear the Tamper interrupt pending bit */
      __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc, RTC_FLAG_TAMP3F);
    }
  }
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

  /* Clear the EXTI s Flag for RTC TimeStamp and Tamper */
  __HAL_RTC_CLEAR_FLAG(RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}

/**
  * @brief  TimeStamp callback. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTCEx_TimeStampEventCallback could be implemented in the user file
  */
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

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
/**
  * @brief  Tamper 2 callback. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTCEx_Tamper2EventCallback could be implemented in the user file
   */
}

/**
  * @brief  Tamper 3 callback. 
  * @param  hrtc: RTC handle
  * @retval None
  */
__weak void HAL_RTCEx_Tamper3EventCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTCEx_Tamper3EventCallback could be implemented in the user file
   */
}
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @brief  This function handles TimeStamp polling request.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTimeStampEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while(__HAL_RTC_TIMESTAMP_GET_FLAG(hrtc, RTC_FLAG_TSF) == RESET)
  {
    if(__HAL_RTC_TIMESTAMP_GET_FLAG(hrtc, RTC_FLAG_TSOVF) != RESET)
    {
      /* Clear the TIMESTAMP OverRun Flag */
      __HAL_RTC_TIMESTAMP_CLEAR_FLAG(hrtc, RTC_FLAG_TSOVF);

      /* Change TIMESTAMP state */
      hrtc->State = HAL_RTC_STATE_ERROR;

      return HAL_ERROR;
    }

    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        hrtc->State = HAL_RTC_STATE_TIMEOUT;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
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

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
/**
  * @brief  This function handles Tamper2 Polling.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTamper2Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{  
  uint32_t tickstart = HAL_GetTick();

  /* Get the status of the Interrupt */
  while(__HAL_RTC_TAMPER_GET_FLAG(hrtc,RTC_FLAG_TAMP2F) == RESET)
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
  __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc,RTC_FLAG_TAMP2F);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  This function handles Tamper3 Polling.
  * @param  hrtc: RTC handle
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForTamper3Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{  
  uint32_t tickstart = HAL_GetTick();

  /* Get the status of the Interrupt */
  while(__HAL_RTC_TAMPER_GET_FLAG(hrtc,RTC_FLAG_TAMP3F) == RESET)
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
  __HAL_RTC_TAMPER_CLEAR_FLAG(hrtc,RTC_FLAG_TAMP3F);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @}
  */
  
/** @defgroup RTCEx_Exported_Functions_Group5 RTC Wake-up functions
  * @brief    RTC Wake-up functions
  *
@verbatim   
 ===============================================================================
                        ##### RTC Wake-up functions #####
 ===============================================================================  
 
 [..] This section provides functions allowing to configure Wake-up feature

@endverbatim
  * @{
  */

/**
  * @brief  Sets wake up timer. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  WakeUpCounter: Wake up counter
  * @param  WakeUpClock: Wake up clock  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock)
{
  uint32_t tickstart = 0;

  /* Check the parameters */
  assert_param(IS_WAKEUP_CLOCK(WakeUpClock));
  assert_param(IS_WAKEUP_COUNTER(WakeUpCounter));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  __HAL_RTC_WAKEUPTIMER_DISABLE(hrtc);
     
  tickstart = HAL_GetTick();

  /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
  while(__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTWF) == RESET)
  {
    if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
    {
      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

      hrtc->State = HAL_RTC_STATE_TIMEOUT;

      /* Process Unlocked */
      __HAL_UNLOCK(hrtc);

      return HAL_TIMEOUT;
    }
  }

  /* Clear the Wakeup Timer clock source bits in CR register */
  hrtc->Instance->CR &= (uint32_t)~RTC_CR_WUCKSEL;

  /* Configure the clock source */
  hrtc->Instance->CR |= (uint32_t)WakeUpClock;

  /* Configure the Wakeup Timer counter */
  hrtc->Instance->WUTR = (uint32_t)WakeUpCounter;

   /* Enable the Wakeup Timer */
  __HAL_RTC_WAKEUPTIMER_ENABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Sets wake up timer with interrupt
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  WakeUpCounter: Wake up counter
  * @param  WakeUpClock: Wake up clock  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock)
{
  uint32_t tickstart = 0;

  /* Check the parameters */
  assert_param(IS_WAKEUP_CLOCK(WakeUpClock));
  assert_param(IS_WAKEUP_COUNTER(WakeUpCounter));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  __HAL_RTC_WAKEUPTIMER_DISABLE(hrtc);

  tickstart = HAL_GetTick();

  /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
  while(__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTWF) == RESET)
  {
    if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
    {
      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

      hrtc->State = HAL_RTC_STATE_TIMEOUT;

      /* Process Unlocked */
      __HAL_UNLOCK(hrtc);

      return HAL_TIMEOUT;
    }
  }

  /* Configure the Wakeup Timer counter */
  hrtc->Instance->WUTR = (uint32_t)WakeUpCounter;

  /* Clear the Wakeup Timer clock source bits in CR register */
  hrtc->Instance->CR &= (uint32_t)~RTC_CR_WUCKSEL;

  /* Configure the clock source */
  hrtc->Instance->CR |= (uint32_t)WakeUpClock;

  /* RTC WakeUpTimer Interrupt Configuration: EXTI configuration */
  __HAL_RTC_ENABLE_IT(RTC_EXTI_LINE_WAKEUPTIMER_EVENT);

  EXTI->RTSR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT;

  /* Configure the Interrupt in the RTC_CR register */
  __HAL_RTC_WAKEUPTIMER_ENABLE_IT(hrtc,RTC_IT_WUT);

  /* Enable the Wakeup Timer */
  __HAL_RTC_WAKEUPTIMER_ENABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates wake up timer counter.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC. 
  * @retval HAL status
  */
uint32_t HAL_RTCEx_DeactivateWakeUpTimer(RTC_HandleTypeDef *hrtc)
{
  uint32_t tickstart = 0;

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Disable the Wakeup Timer */
  __HAL_RTC_WAKEUPTIMER_DISABLE(hrtc);

  /* In case of interrupt mode is used, the interrupt source must disabled */
  __HAL_RTC_WAKEUPTIMER_DISABLE_IT(hrtc,RTC_IT_WUT);

  tickstart = HAL_GetTick();
  /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
  while(__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTWF) == RESET)
  {
    if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
    {
      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

      hrtc->State = HAL_RTC_STATE_TIMEOUT;

      /* Process Unlocked */
      __HAL_UNLOCK(hrtc);

      return HAL_TIMEOUT;
    }
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Gets wake up timer counter.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC. 
  * @retval Counter value
  */
uint32_t HAL_RTCEx_GetWakeUpTimer(RTC_HandleTypeDef *hrtc)
{
  /* Get the counter value */
  return ((uint32_t)(hrtc->Instance->WUTR & RTC_WUTR_WUT));
}

/**
  * @brief  This function handles Wake Up Timer interrupt request.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTCEx_WakeUpTimerIRQHandler(RTC_HandleTypeDef *hrtc)
{
  if(__HAL_RTC_WAKEUPTIMER_GET_IT(hrtc, RTC_IT_WUT))
  {
    /* Get the status of the Interrupt */
    if((uint32_t)(hrtc->Instance->CR & RTC_IT_WUT) != (uint32_t)RESET)
    {
      /* WAKEUPTIMER callback */
      HAL_RTCEx_WakeUpTimerEventCallback(hrtc);

      /* Clear the WAKEUPTIMER interrupt pending bit */
      __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(hrtc, RTC_FLAG_WUTF);
    }
  }

  /* Clear the EXTI s line Flag for RTC WakeUpTimer */
  __HAL_RTC_CLEAR_FLAG(RTC_EXTI_LINE_WAKEUPTIMER_EVENT);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;
}

/**
  * @brief  Wake Up Timer callback.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTCEx_WakeUpTimerEventCallback could be implemented in the user file
   */
}

/**
  * @brief  This function handles Wake Up Timer Polling.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForWakeUpTimerEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();

  while(__HAL_RTC_WAKEUPTIMER_GET_FLAG(hrtc, RTC_FLAG_WUTF) == RESET)
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

  /* Clear the WAKEUPTIMER Flag */
  __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(hrtc, RTC_FLAG_WUTF);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group7 Extended Peripheral Control functions
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
      (+) Sets the Coarse calibration parameters.
      (+) Deactivates the Coarse calibration parameters
      (+) Sets the Smooth calibration parameters.
      (+) Configures the Synchronization Shift Control Settings.
      (+) Configures the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
      (+) Deactivates the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
      (+) Enables the RTC reference clock detection.
      (+) Disable the RTC reference clock detection.
      (+) Enables the Bypass Shadow feature.
      (+) Disables the Bypass Shadow feature.

@endverbatim
  * @{
  */

/**
  * @brief  Writes a data in a specified RTC Backup data register.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC. 
  * @param  BackupRegister: RTC Backup data Register number.
  *          This parameter can be: RTC_BKP_DRx where x can be from 0 to 19 to 
  *                                 specify the register.
  * @param  Data: Data to be written in the specified RTC Backup data register.                     
  * @retval None
  */
void HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_RTC_BKP(BackupRegister));
  
  tmp = (uint32_t)&(hrtc->Instance->BKP0R);
  tmp += (BackupRegister * 4);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * @brief  Reads data from the specified RTC Backup data Register.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC. 
  * @param  BackupRegister: RTC Backup data Register number.
  *          This parameter can be: RTC_BKP_DRx where x can be from 0 to 19 to 
  *                                 specify the register.                   
  * @retval Read value
  */
uint32_t HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_RTC_BKP(BackupRegister));

  tmp = (uint32_t)&(hrtc->Instance->BKP0R);
  tmp += (BackupRegister * 4);

  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}

/**
  * @brief  Sets the Coarse calibration parameters.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.  
  * @param  CalibSign: Specifies the sign of the coarse calibration value.
  *          This parameter can be  one of the following values :
  *             @arg RTC_CALIBSIGN_POSITIVE: The value sign is positive 
  *             @arg RTC_CALIBSIGN_NEGATIVE: The value sign is negative
  * @param  Value: value of coarse calibration expressed in ppm (coded on 5 bits).
  *    
  * @note   This Calibration value should be between 0 and 63 when using negative
  *         sign with a 2-ppm step.
  *           
  * @note   This Calibration value should be between 0 and 126 when using positive
  *         sign with a 4-ppm step.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetCoarseCalib(RTC_HandleTypeDef* hrtc, uint32_t CalibSign, uint32_t Value)
{
  /* Check the parameters */
  assert_param(IS_RTC_CALIB_SIGN(CalibSign));
  assert_param(IS_RTC_CALIB_VALUE(Value)); 
  
  /* Process Locked */ 
  __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc); 
    
    /* Set RTC state*/
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Process Unlocked */ 
    __HAL_UNLOCK(hrtc);
    
    return HAL_ERROR;
  } 
  else
  { 
    /* Enable the Coarse Calibration */
    __HAL_RTC_COARSE_CALIB_ENABLE(hrtc);
    
    /* Set the coarse calibration value */
    hrtc->Instance->CALIBR = (uint32_t)(CalibSign|Value);
    
    /* Exit Initialization mode */
    hrtc->Instance->ISR &= (uint32_t)~RTC_ISR_INIT; 
  } 

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  
  /* Change state */
  hrtc->State = HAL_RTC_STATE_READY; 
  
  /* Process Unlocked */ 
  __HAL_UNLOCK(hrtc);
  
  return HAL_OK;
}

/**
  * @brief  Deactivates the Coarse calibration parameters.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateCoarseCalib(RTC_HandleTypeDef* hrtc)
{ 
  /* Process Locked */ 
  __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY;
  
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc); 
    
    /* Set RTC state*/
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Process Unlocked */ 
    __HAL_UNLOCK(hrtc);
    
    return HAL_ERROR;
  } 
  else
  { 
    /* Enable the Coarse Calibration */
    __HAL_RTC_COARSE_CALIB_DISABLE(hrtc);
    
    /* Exit Initialization mode */
    hrtc->Instance->ISR &= (uint32_t)~RTC_ISR_INIT; 
  } 

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  
  /* Change state */
  hrtc->State = HAL_RTC_STATE_READY; 
  
  /* Process Unlocked */ 
  __HAL_UNLOCK(hrtc);
  
  return HAL_OK;
}

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
/**
  * @brief  Sets the Smooth calibration parameters.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.  
  * @param  SmoothCalibPeriod: Select the Smooth Calibration Period.
  *          This parameter can be can be one of the following values :
  *             @arg RTC_SMOOTHCALIB_PERIOD_32SEC: The smooth calibration periode is 32s.
  *             @arg RTC_SMOOTHCALIB_PERIOD_16SEC: The smooth calibration periode is 16s.
  *             @arg RTC_SMOOTHCALIB_PERIOD_8SEC: The smooth calibartion periode is 8s.
  * @param  SmoothCalibPlusPulses: Select to Set or reset the CALP bit.
  *          This parameter can be one of the following values:
  *             @arg RTC_SMOOTHCALIB_PLUSPULSES_SET: Add one RTCCLK puls every 2*11 pulses.
  *             @arg RTC_SMOOTHCALIB_PLUSPULSES_RESET: No RTCCLK pulses are added.
  * @param  SmouthCalibMinusPulsesValue: Select the value of CALM[8:0] bits.
  *          This parameter can be one any value from 0 to 0x000001FF.
  * @note   To deactivate the smooth calibration, the field SmoothCalibPlusPulses 
  *         must be equal to SMOOTHCALIB_PLUSPULSES_RESET and the field 
  *         SmouthCalibMinusPulsesValue must be equal to 0.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef* hrtc, uint32_t SmoothCalibPeriod, uint32_t SmoothCalibPlusPulses, uint32_t SmouthCalibMinusPulsesValue)
{
  uint32_t tickstart = 0;

  /* Check the parameters */
  assert_param(IS_RTC_SMOOTH_CALIB_PERIOD(SmoothCalibPeriod));
  assert_param(IS_RTC_SMOOTH_CALIB_PLUS(SmoothCalibPlusPulses));
  assert_param(IS_RTC_SMOOTH_CALIB_MINUS(SmouthCalibMinusPulsesValue));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* check if a calibration is pending*/
  if((hrtc->Instance->ISR & RTC_ISR_RECALPF) != RESET)
  {
    tickstart = HAL_GetTick();

    /* check if a calibration is pending*/
    while((hrtc->Instance->ISR & RTC_ISR_RECALPF) != RESET)
    {
      if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        /* Change RTC state */
        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }
  }

  /* Configure the Smooth calibration settings */
  hrtc->Instance->CALR = (uint32_t)((uint32_t)SmoothCalibPeriod | (uint32_t)SmoothCalibPlusPulses | (uint32_t)SmouthCalibMinusPulsesValue);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Configures the Synchronization Shift Control Settings.
  * @note   When REFCKON is set, firmware must not write to Shift control register. 
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.    
  * @param  ShiftAdd1S: Select to add or not 1 second to the time calendar.
  *          This parameter can be one of the following values :
  *             @arg RTC_SHIFTADD1S_SET: Add one second to the clock calendar. 
  *             @arg RTC_SHIFTADD1S_RESET: No effect.
  * @param  ShiftSubFS: Select the number of Second Fractions to substitute.
  *          This parameter can be one any value from 0 to 0x7FFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetSynchroShift(RTC_HandleTypeDef* hrtc, uint32_t ShiftAdd1S, uint32_t ShiftSubFS)
{
  uint32_t tickstart = 0;

  /* Check the parameters */
  assert_param(IS_RTC_SHIFT_ADD1S(ShiftAdd1S));
  assert_param(IS_RTC_SHIFT_SUBFS(ShiftSubFS));

  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

    tickstart = HAL_GetTick();

    /* Wait until the shift is completed*/
    while((hrtc->Instance->ISR & RTC_ISR_SHPF) != RESET)
    {
      if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_TIMEOUT;
      }
    }

    /* Check if the reference clock detection is disabled */
    if((hrtc->Instance->CR & RTC_CR_REFCKON) == RESET)
    {
      /* Configure the Shift settings */
      hrtc->Instance->SHIFTR = (uint32_t)(uint32_t)(ShiftSubFS) | (uint32_t)(ShiftAdd1S);

      /* Wait for synchro */
      if(HAL_RTC_WaitForSynchro(hrtc) != HAL_OK)
      {
        /* Enable the write protection for RTC registers */
        __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

        hrtc->State = HAL_RTC_STATE_ERROR;

        /* Process Unlocked */
        __HAL_UNLOCK(hrtc);

        return HAL_ERROR;
      }
    }
    else
    {
      /* Enable the write protection for RTC registers */
      __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

      /* Change RTC state */
      hrtc->State = HAL_RTC_STATE_ERROR;

      /* Process Unlocked */
      __HAL_UNLOCK(hrtc);

      return HAL_ERROR;
    }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */


#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
/**
  * @brief  Configures the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.    
  * @param  CalibOutput : Select the Calibration output Selection .
  *          This parameter can be one of the following values:
  *             @arg RTC_CALIBOUTPUT_512HZ: A signal has a regular waveform at 512Hz. 
  *             @arg RTC_CALIBOUTPUT_1HZ: A signal has a regular waveform at 1Hz.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetCalibrationOutPut(RTC_HandleTypeDef* hrtc, uint32_t CalibOutput)
#else
/**
  * @brief  Configure the Calibration Pinout (RTC_CALIB).
  * @param  hrtc : RTC handle    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetCalibrationOutPut(RTC_HandleTypeDef* hrtc)
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
{
#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  /* Check the parameters */
  assert_param(IS_RTC_CALIB_OUTPUT(CalibOutput));
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)   
  /* Clear flags before config */
  hrtc->Instance->CR &= (uint32_t)~RTC_CR_COSEL;

  /* Configure the RTC_CR register */
  hrtc->Instance->CR |= (uint32_t)CalibOutput;
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
  __HAL_RTC_CALIBRATION_OUTPUT_ENABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Deactivates the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateCalibrationOutPut(RTC_HandleTypeDef* hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  __HAL_RTC_CALIBRATION_OUTPUT_DISABLE(hrtc);

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Enables the RTC reference clock detection.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_SetRefClock(RTC_HandleTypeDef* hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

    /* Set RTC state*/
    hrtc->State = HAL_RTC_STATE_ERROR;

    /* Process Unlocked */
    __HAL_UNLOCK(hrtc);

    return HAL_ERROR;
  }
  else
  {
    __HAL_RTC_CLOCKREF_DETECTION_ENABLE(hrtc);

    /* Exit Initialization mode */
    hrtc->Instance->ISR &= (uint32_t)~RTC_ISR_INIT;
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

   /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Disable the RTC reference clock detection.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DeactivateRefClock(RTC_HandleTypeDef* hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

    /* Set RTC state*/
    hrtc->State = HAL_RTC_STATE_ERROR;

    /* Process Unlocked */
    __HAL_UNLOCK(hrtc);

    return HAL_ERROR;
  }
  else
  {
    __HAL_RTC_CLOCKREF_DETECTION_DISABLE(hrtc);

    /* Exit Initialization mode */
    hrtc->Instance->ISR &= (uint32_t)~RTC_ISR_INIT;
  }

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) 
/**
  * @brief  Enables the Bypass Shadow feature.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.  
  * @note   When the Bypass Shadow is enabled the calendar value are taken 
  *         directly from the Calendar counter.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_EnableBypassShadow(RTC_HandleTypeDef* hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Set the BYPSHAD bit */
  hrtc->Instance->CR |= (uint8_t)RTC_CR_BYPSHAD;

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Disables the Bypass Shadow feature.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.  
  * @note   When the Bypass Shadow is enabled the calendar value are taken
  *         directly from the Calendar counter.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_DisableBypassShadow(RTC_HandleTypeDef* hrtc)
{
  /* Process Locked */
  __HAL_LOCK(hrtc);

  hrtc->State = HAL_RTC_STATE_BUSY;

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

  /* Reset the BYPSHAD bit */
  hrtc->Instance->CR &= (uint8_t)~RTC_CR_BYPSHAD;

  /* Enable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group8 Extended features functions
  * @brief    Extended features functions
  *
@verbatim   
 ===============================================================================
                 ##### Extended features functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) RTC Alram B callback
      (+) RTC Poll for Alarm B request
               
@endverbatim
  * @{
  */

/**
  * @brief  Alarm B callback.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTCEx_AlarmBEventCallback could be implemented in the user file
   */
}

/**
  * @brief  This function handles AlarmB Polling request.
  * @param  hrtc: pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTCEx_PollForAlarmBEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{  
  uint32_t tickstart = HAL_GetTick();
  
  while(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRBF) == RESET)
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
  
  /* Clear the Alarm Flag */
  __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRBF);
  
  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY; 
  
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
