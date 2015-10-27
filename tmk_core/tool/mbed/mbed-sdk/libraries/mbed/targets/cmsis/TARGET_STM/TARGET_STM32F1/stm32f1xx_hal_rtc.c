/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rtc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   RTC HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Real Time Clock (RTC) peripheral:
  *           + Initialization and de-initialization functions
  *           + RTC Time and Date functions
  *           + RTC Alarm functions
  *           + Peripheral Control functions   
  *           + Peripheral State functions
  *         
  @verbatim
  ==============================================================================
                  ##### How to use this driver #####
  ==================================================================
  [..] 
    (+) Enable the RTC domain access (see description in the section above).
    (+) Configure the RTC Prescaler (Asynchronous prescaler to generate RTC 1Hz time base) 
        using the HAL_RTC_Init() function.
  
  *** Time and Date configuration ***
  ===================================
  [..] 
    (+) To configure the RTC Calendar (Time and Date) use the HAL_RTC_SetTime() 
        and HAL_RTC_SetDate() functions.
    (+) To read the RTC Calendar, use the HAL_RTC_GetTime() and HAL_RTC_GetDate() functions.
  
  *** Alarm configuration ***
  ===========================
  [..]
    (+) To configure the RTC Alarm use the HAL_RTC_SetAlarm() function. 
        You can also configure the RTC Alarm with interrupt mode using the HAL_RTC_SetAlarm_IT() function.
    (+) To read the RTC Alarm, use the HAL_RTC_GetAlarm() function.
  
  *** Tamper configuration ***
  ============================
  [..]
    (+) Enable the RTC Tamper and configure the Tamper Level using the 
        HAL_RTCEx_SetTamper() function. You can configure RTC Tamper with interrupt
        mode using HAL_RTCEx_SetTamper_IT() function.
    (+) The TAMPER1 alternate function can be mapped to PC13

  *** Backup Data Registers configuration ***
  ===========================================
  [..]
    (+) To write to the RTC Backup Data registers, use the HAL_RTCEx_BKUPWrite()
        function.  
    (+) To read the RTC Backup Data registers, use the HAL_RTCEx_BKUPRead()
        function.
     
                  ##### WARNING: Drivers Restrictions  #####
  ==================================================================
  [..] RTC version used on STM32F1 families is version V1. All the features supported by V2
       (other families) will be not supported on F1.
  [..] As on V2, main RTC features are managed by HW. But on F1, date feature is completely 
       managed by SW.
  [..] Then, there are some restrictions compared to other families:
    (+) Only format 24 hours supported in HAL (format 12 hours not supported)
    (+) Date is saved in SRAM. Then, when MCU is in STOP or STANDBY mode, date will be lost.
        User should implement a way to save date before entering in low power mode (an 
        example is provided with firmware package based on backup registers)
    (+) Date is automatically updated each time a HAL_RTC_GetTime or HAL_RTC_GetDate is called.
    (+) Alarm detection is limited to 1 day. It will expire only 1 time (no alarm repetition, need
        to program a new alarm)

              ##### Backup Domain Operating Condition #####
  ==============================================================================
  [..] The real-time clock (RTC) and the RTC backup registers can be powered
       from the VBAT voltage when the main VDD supply is powered off.
       To retain the content of the RTC backup registers and supply the RTC 
       when VDD is turned off, VBAT pin can be connected to an optional 
       standby voltage supplied by a battery or by another source.

  [..] To allow the RTC operating even when the main digital supply (VDD) is turned
       off, the VBAT pin powers the following blocks:
    (+) The RTC
    (+) The LSE oscillator
    (+) PC13 I/O
  
  [..] When the backup domain is supplied by VDD (analog switch connected to VDD),
       the following pins are available:
    (+) PC13 can be used as a Tamper pin
  
  [..] When the backup domain is supplied by VBAT (analog switch connected to VBAT 
       because VDD is not present), the following pins are available:
    (+) PC13 can be used as the Tamper pin 
             
                   ##### Backup Domain Reset #####
  ==================================================================
  [..] The backup domain reset sets all RTC registers and the RCC_BDCR register
       to their reset values. 
  [..] A backup domain reset is generated when one of the following events occurs:
    (#) Software reset, triggered by setting the BDRST bit in the 
        RCC Backup domain control register (RCC_BDCR). 
    (#) VDD or VBAT power on, if both supplies have previously been powered off.  
    (#) Tamper detection event resets all data backup registers.

                   ##### Backup Domain Access #####
  ==================================================================
  [..] After reset, the backup domain (RTC registers, RTC backup data 
       registers and backup SRAM) is protected against possible unwanted write 
       accesses. 
  [..] To enable access to the RTC Domain and RTC registers, proceed as follows:
    (+) Call the function HAL_RCCEx_PeriphCLKConfig in using RCC_PERIPHCLK_RTC for
        PeriphClockSelection and select RTCClockSelection (LSE, LSI or HSE)
    (+) Enable the BKP clock in using __HAL_RCC_BKP_CLK_ENABLE()
  
                  ##### RTC and low power modes #####
  ==================================================================
  [..] The MCU can be woken up from a low power mode by an RTC alternate 
       function.
  [..] The RTC alternate functions are the RTC alarms (Alarm A), 
       and RTC tamper event detection.
       These RTC alternate functions can wake up the system from the Stop and 
       Standby low power modes.
  [..] The system can also wake up from low power modes without depending 
       on an external interrupt (Auto-wakeup mode), by using the RTC alarm.
     
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup RTC RTC
  * @brief RTC HAL module driver
  * @{
  */

#ifdef HAL_RTC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup RTC_Private_Constants RTC Private Constants
  * @{
  */
#define RTC_ALARM_RESETVALUE_REGISTER    (uint16_t)0xFFFF
#define RTC_ALARM_RESETVALUE             (uint32_t)0xFFFFFFFF

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup RTC_Private_Macros RTC Private Macros
  * @{
  */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RTC_Private_Functions RTC Private Functions
  * @{
  */
static uint32_t           RTC_ReadTimeCounter(RTC_HandleTypeDef* hrtc);
static HAL_StatusTypeDef  RTC_WriteTimeCounter(RTC_HandleTypeDef* hrtc, uint32_t TimeCounter);
static uint32_t           RTC_ReadAlarmCounter(RTC_HandleTypeDef* hrtc);
static HAL_StatusTypeDef  RTC_WriteAlarmCounter(RTC_HandleTypeDef* hrtc, uint32_t AlarmCounter);
static HAL_StatusTypeDef  RTC_EnterInitMode(RTC_HandleTypeDef* hrtc);
static HAL_StatusTypeDef  RTC_ExitInitMode(RTC_HandleTypeDef* hrtc);
static uint8_t            RTC_ByteToBcd2(uint8_t Value);
static uint8_t            RTC_Bcd2ToByte(uint8_t Value);
static uint8_t            RTC_IsLeapYear(uint16_t nYear);
static void               RTC_DateUpdate(RTC_HandleTypeDef* hrtc, uint32_t DayElapsed);
static uint8_t            RTC_WeekDayNum(uint32_t nYear, uint8_t nMonth, uint8_t nDay);

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup RTC_Exported_Functions RTC Exported Functions
  * @{
  */
  
/** @defgroup RTC_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
   [..] This section provides functions allowing to initialize and configure the 
         RTC Prescaler (Asynchronous), disable RTC registers Write protection, 
         enter and exit the RTC initialization mode, 
         RTC registers synchronization check and reference clock detection enable.
         (#) The RTC Prescaler should be programmed to generate the RTC 1Hz time base. 
         (#) All RTC registers are Write protected. Writing to the RTC registers
             is enabled by setting the CNF bit in the RTC_CRL register.
         (#) To read the calendar after wakeup from low power modes (Standby or Stop) 
             the software must first wait for the RSF bit (Register Synchronized Flag) 
             in the RTC_CRL register to be set by hardware.
             The HAL_RTC_WaitForSynchro() function implements the above software 
             sequence (RSF clear and RSF check).
 
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the RTC peripheral 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_Init(RTC_HandleTypeDef *hrtc)
{
  uint32_t prescaler = 0;
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_ALL_INSTANCE(hrtc->Instance));
  assert_param(IS_RTC_CALIB_OUTPUT(hrtc->Init.OutPut));
  assert_param(IS_RTC_ASYNCH_PREDIV(hrtc->Init.AsynchPrediv));
    
  if(hrtc->State == HAL_RTC_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hrtc-> Lock = HAL_UNLOCKED;
    
    /* Initialize RTC MSP */
    HAL_RTC_MspInit(hrtc);
  }
  
  /* Set RTC state */  
  hrtc->State = HAL_RTC_STATE_BUSY;  
       
  /* Waiting for synchro */
  if(HAL_RTC_WaitForSynchro(hrtc) != HAL_OK)
  {
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    return HAL_ERROR;
  } 

  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    return HAL_ERROR;
  } 
  else
  { 
    /* Clear Flags Bits */
    CLEAR_BIT(hrtc->Instance->CRL, (RTC_FLAG_OW | RTC_FLAG_ALRAF | RTC_FLAG_SEC));
    
    if(hrtc->Init.OutPut != RTC_OUTPUTSOURCE_NONE)
    {
      /* Disable the selected Tamper pin */
      CLEAR_BIT(BKP->CR, BKP_CR_TPE);
    }
    
    /* Set the signal which will be routed to RTC Tamper pin*/
    MODIFY_REG(BKP->RTCCR, (BKP_RTCCR_CCO | BKP_RTCCR_ASOE | BKP_RTCCR_ASOS), hrtc->Init.OutPut);

    if (hrtc->Init.AsynchPrediv != RTC_AUTO_1_SECOND)
    {
      /* RTC Prescaler provided directly by end-user*/
      prescaler = hrtc->Init.AsynchPrediv;
    }
    else
    {
      /* RTC Prescaler will be automatically calculated to get 1 second timebase */
      /* Get the RTCCLK frequency */
      prescaler = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_RTC);

      /* Check that RTC clock is enabled*/
      if (prescaler == 0)
      {
        /* Should not happen. Frequency is not available*/
        hrtc->State = HAL_RTC_STATE_ERROR;
        return HAL_ERROR;
      }
      else
      {
        /* RTC period = RTCCLK/(RTC_PR + 1) */
        prescaler = prescaler - 1;
      }
    }
    
    /* Configure the RTC_PRLH / RTC_PRLL */
    MODIFY_REG(hrtc->Instance->PRLH, RTC_PRLH_PRL, (prescaler >> 16));
    MODIFY_REG(hrtc->Instance->PRLL, RTC_PRLL_PRL, (prescaler & RTC_PRLL_PRL));
      
    /* Wait for synchro */
    if(RTC_ExitInitMode(hrtc) != HAL_OK)
    {       
      hrtc->State = HAL_RTC_STATE_ERROR;
      
      return HAL_ERROR;
    }
    
    /* Initialize date to 1st of January 2000 */
    hrtc->DateToUpdate.Year = 0x00;
    hrtc->DateToUpdate.Month = RTC_MONTH_JANUARY;
    hrtc->DateToUpdate.Date = 0x01;

    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_READY;
    
    return HAL_OK;
  }
}

/**
  * @brief  DeInitializes the RTC peripheral 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @note   This function does not reset the RTC Backup Data registers.   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_DeInit(RTC_HandleTypeDef *hrtc)
{
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_ALL_INSTANCE(hrtc->Instance));

  /* Set RTC state */
  hrtc->State = HAL_RTC_STATE_BUSY; 
  
  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Release Lock */
    __HAL_UNLOCK(hrtc);

    return HAL_ERROR;
  }  
  else
  {
    CLEAR_REG(hrtc->Instance->CNTL);
    CLEAR_REG(hrtc->Instance->CNTH);
    WRITE_REG(hrtc->Instance->PRLL, 0x00008000);
    CLEAR_REG(hrtc->Instance->PRLH);

    /* Reset All CRH/CRL bits */
    CLEAR_REG(hrtc->Instance->CRH);
    CLEAR_REG(hrtc->Instance->CRL);
    
    if(RTC_ExitInitMode(hrtc) != HAL_OK)
    {       
      hrtc->State = HAL_RTC_STATE_ERROR;
      
      /* Process Unlocked */ 
      __HAL_UNLOCK(hrtc);
      
      return HAL_ERROR;
    }
  }

  /* Wait for synchro*/
  HAL_RTC_WaitForSynchro(hrtc);

  /* Clear RSF flag */
  CLEAR_BIT(hrtc->Instance->CRL, RTC_FLAG_RSF);
    
  /* De-Initialize RTC MSP */
  HAL_RTC_MspDeInit(hrtc);

  hrtc->State = HAL_RTC_STATE_RESET; 
  
  /* Release Lock */
  __HAL_UNLOCK(hrtc);

  return HAL_OK;
}

/**
  * @brief  Initializes the RTC MSP.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.  
  * @retval None
  */
__weak void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTC_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  DeInitializes the RTC MSP.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC. 
  * @retval None
  */
__weak void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTC_MspDeInit could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group2 Time and Date functions
 *  @brief   RTC Time and Date functions
 *
@verbatim   
 ===============================================================================
                 ##### RTC Time and Date functions #####
 ===============================================================================  
 
 [..] This section provides functions allowing to configure Time and Date features

@endverbatim
  * @{
  */

/**
  * @brief  Sets RTC current time.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTime: Pointer to Time structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_FORMAT_BIN: Binary data format 
  *            @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format)
{
  uint32_t counter_time = 0, counter_alarm = 0;
  
  /* Check input parameters */
  if((hrtc == NULL) || (sTime == NULL))
  {
     return HAL_ERROR;
  }
  
 /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  
  /* Process Locked */ 
  __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY;
  
  if(Format == RTC_FORMAT_BIN)
  {
    assert_param(IS_RTC_HOUR24(sTime->Hours));
    assert_param(IS_RTC_MINUTES(sTime->Minutes));
    assert_param(IS_RTC_SECONDS(sTime->Seconds));

    counter_time = (uint32_t)(((uint32_t)sTime->Hours * 3600) + \
                        ((uint32_t)sTime->Minutes * 60) + \
                        ((uint32_t)sTime->Seconds));  
  }
  else
  {
    assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(sTime->Hours)));
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(sTime->Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(sTime->Seconds)));

    counter_time = (((uint32_t)(RTC_Bcd2ToByte(sTime->Hours)) * 3600) + \
              ((uint32_t)(RTC_Bcd2ToByte(sTime->Minutes)) * 60) + \
              ((uint32_t)(RTC_Bcd2ToByte(sTime->Seconds))));   
  }

  /* Write time counter in RTC registers */
  if (RTC_WriteTimeCounter(hrtc, counter_time) != HAL_OK)
  {
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Process Unlocked */ 
    __HAL_UNLOCK(hrtc);
    
    return HAL_ERROR;
  }
  else
  {
    /* Clear Second and overflow flags */
    CLEAR_BIT(hrtc->Instance->CRL, (RTC_FLAG_SEC | RTC_FLAG_OW));
    
    /* Read current Alarm counter in RTC registers */
    counter_alarm = RTC_ReadAlarmCounter(hrtc);

    /* Set again alarm to match with new time if enabled */
    if (counter_alarm != RTC_ALARM_RESETVALUE)
    {
      if(counter_alarm < counter_time)
      {
        /* Add 1 day to alarm counter*/
        counter_alarm += (uint32_t)(24 * 3600);
        
        /* Write new Alarm counter in RTC registers */
        if (RTC_WriteAlarmCounter(hrtc, counter_alarm) != HAL_OK)
        {
          /* Set RTC state */
          hrtc->State = HAL_RTC_STATE_ERROR;
          
          /* Process Unlocked */ 
          __HAL_UNLOCK(hrtc);
          
          return HAL_ERROR;
        }
      }
    }
    
    hrtc->State = HAL_RTC_STATE_READY;
  
   __HAL_UNLOCK(hrtc); 
     
   return HAL_OK;
  }
}

/**
  * @brief  Gets RTC current time.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sTime: Pointer to Time structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_FORMAT_BIN: Binary data format 
  *            @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format)
{
  uint32_t counter_time = 0, counter_alarm = 0, days_elapsed = 0, hours = 0;
  
  /* Check input parameters */
  if((hrtc == NULL) || (sTime == NULL))
  {
     return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));

  /* Check if counter overflow occurred */
  if (__HAL_RTC_OVERFLOW_GET_FLAG(hrtc, RTC_FLAG_OW))
  {
      return HAL_ERROR;
  }

  /* Read the time counter*/
  counter_time = RTC_ReadTimeCounter(hrtc);

  /* Fill the structure fields with the read parameters */
  hours = counter_time / 3600;
  sTime->Minutes  = (uint8_t)((counter_time % 3600) / 60);
  sTime->Seconds  = (uint8_t)((counter_time % 3600) % 60);

  if (hours >= 24)
  {
    /* Get number of days elapsed from last calculation */
    days_elapsed = (hours / 24);

    /* Set Hours in RTC_TimeTypeDef structure*/
    sTime->Hours = (hours % 24);    

    /* Read Alarm counter in RTC registers */
    counter_alarm = RTC_ReadAlarmCounter(hrtc);

    /* Calculate remaining time to reach alarm (only if set and not yet expired)*/
    if ((counter_alarm != RTC_ALARM_RESETVALUE) && (counter_alarm > counter_time))
    {
      counter_alarm -= counter_time;
    }
    else 
    {
      /* In case of counter_alarm < counter_time */
      /* Alarm expiration already occurred but alarm not deactivated */
      counter_alarm = RTC_ALARM_RESETVALUE;
    }

    /* Set updated time in decreasing counter by number of days elapsed */
    counter_time -= (days_elapsed * 24 * 3600);
    
    /* Write time counter in RTC registers */
    if (RTC_WriteTimeCounter(hrtc, counter_time) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Set updated alarm to be set */
    if (counter_alarm != RTC_ALARM_RESETVALUE)
    {
      counter_alarm += counter_time;
      
      /* Write time counter in RTC registers */
      if (RTC_WriteAlarmCounter(hrtc, counter_alarm) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Alarm already occurred. Set it to reset values to avoid unexpected expiration */
      if (RTC_WriteAlarmCounter(hrtc, counter_alarm) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
    
    /* Update date */
    RTC_DateUpdate(hrtc, days_elapsed);
  }
  else 
  {
    sTime->Hours = hours;    
  }

  /* Check the input parameters format */
  if(Format != RTC_FORMAT_BIN)
  {
    /* Convert the time structure parameters to BCD format */
    sTime->Hours    = (uint8_t)RTC_ByteToBcd2(sTime->Hours);
    sTime->Minutes  = (uint8_t)RTC_ByteToBcd2(sTime->Minutes);
    sTime->Seconds  = (uint8_t)RTC_ByteToBcd2(sTime->Seconds);  
  }
  
  return HAL_OK;
}


/**
  * @brief  Sets RTC current date.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sDate: Pointer to date structure
  * @param  Format: specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_FORMAT_BIN: Binary data format 
  *            @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format)
{
  uint32_t counter_time = 0, counter_alarm = 0, hours = 0;
  
  /* Check input parameters */
  if((hrtc == NULL) || (sDate == NULL))
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  
 /* Process Locked */ 
 __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY; 
  
  if(Format == RTC_FORMAT_BIN)
  {   
    assert_param(IS_RTC_YEAR(sDate->Year));
    assert_param(IS_RTC_MONTH(sDate->Month));
    assert_param(IS_RTC_DATE(sDate->Date)); 

    /* Change the current date */
    hrtc->DateToUpdate.Year  = sDate->Year;
    hrtc->DateToUpdate.Month = sDate->Month;
    hrtc->DateToUpdate.Date  = sDate->Date;
  }
  else
  {   
    assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(sDate->Year)));
    assert_param(IS_RTC_MONTH(RTC_Bcd2ToByte(sDate->Month)));
    assert_param(IS_RTC_DATE(RTC_Bcd2ToByte(sDate->Date)));
    
    /* Change the current date */
    hrtc->DateToUpdate.Year  = RTC_Bcd2ToByte(sDate->Year);
    hrtc->DateToUpdate.Month = RTC_Bcd2ToByte(sDate->Month);
    hrtc->DateToUpdate.Date  = RTC_Bcd2ToByte(sDate->Date);
  }

  /* WeekDay set by user can be ignored because automatically calculated */
  hrtc->DateToUpdate.WeekDay = RTC_WeekDayNum(hrtc->DateToUpdate.Year, hrtc->DateToUpdate.Month, hrtc->DateToUpdate.Date);
  sDate->WeekDay = hrtc->DateToUpdate.WeekDay;

  /* Reset time to be aligned on the same day */
  /* Read the time counter*/
  counter_time = RTC_ReadTimeCounter(hrtc);

  /* Fill the structure fields with the read parameters */
  hours = counter_time / 3600;
  if (hours > 24)
  {
    /* Set updated time in decreasing counter by number of days elapsed */
    counter_time -= ((hours / 24) * 24 * 3600);
    /* Write time counter in RTC registers */
    if (RTC_WriteTimeCounter(hrtc, counter_time) != HAL_OK)
    {
      /* Set RTC state */
      hrtc->State = HAL_RTC_STATE_ERROR;
      
      /* Process Unlocked */ 
      __HAL_UNLOCK(hrtc);
      
      return HAL_ERROR;
    }

    /* Read current Alarm counter in RTC registers */
    counter_alarm = RTC_ReadAlarmCounter(hrtc);

    /* Set again alarm to match with new time if enabled */
    if (counter_alarm != RTC_ALARM_RESETVALUE)
    {
      if(counter_alarm < counter_time)
      {
        /* Add 1 day to alarm counter*/
        counter_alarm += (uint32_t)(24 * 3600);
        
        /* Write new Alarm counter in RTC registers */
        if (RTC_WriteAlarmCounter(hrtc, counter_alarm) != HAL_OK)
        {
          /* Set RTC state */
          hrtc->State = HAL_RTC_STATE_ERROR;
          
          /* Process Unlocked */ 
          __HAL_UNLOCK(hrtc);
          
          return HAL_ERROR;
        }
      }
    }
    

  }

  hrtc->State = HAL_RTC_STATE_READY ;
  
  /* Process Unlocked */ 
  __HAL_UNLOCK(hrtc);
  
  return HAL_OK;    
}

/**
  * @brief  Gets RTC current date.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sDate: Pointer to Date structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_FORMAT_BIN:  Binary data format 
  *            @arg RTC_FORMAT_BCD:  BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format)
{
  RTC_TimeTypeDef stime = {0};
  
  /* Check input parameters */
  if((hrtc == NULL) || (sDate == NULL))
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  
  /* Call HAL_RTC_GetTime function to update date if counter higher than 24 hours */
  if (HAL_RTC_GetTime(hrtc, &stime, RTC_FORMAT_BIN) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Fill the structure fields with the read parameters */
  sDate->WeekDay  = hrtc->DateToUpdate.WeekDay;
  sDate->Year     = hrtc->DateToUpdate.Year;
  sDate->Month    = hrtc->DateToUpdate.Month;
  sDate->Date     = hrtc->DateToUpdate.Date;

  /* Check the input parameters format */
  if(Format != RTC_FORMAT_BIN)
  {    
    /* Convert the date structure parameters to BCD format */
    sDate->Year   = (uint8_t)RTC_ByteToBcd2(sDate->Year);
    sDate->Month  = (uint8_t)RTC_ByteToBcd2(sDate->Month);
    sDate->Date   = (uint8_t)RTC_ByteToBcd2(sDate->Date);  
  }
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group3 Alarm functions
 *  @brief   RTC Alarm functions
 *
@verbatim   
 ===============================================================================
                 ##### RTC Alarm functions #####
 ===============================================================================  
 
 [..] This section provides functions allowing to configure Alarm feature

@endverbatim
  * @{
  */

/**
  * @brief  Sets the specified RTC Alarm.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sAlarm: Pointer to Alarm structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg RTC_FORMAT_BIN: Binary data format 
  *             @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format)
{
  uint32_t counter_alarm = 0, counter_time;
  RTC_TimeTypeDef stime = {0};
  
  /* Check input parameters */
  if((hrtc == NULL) || (sAlarm == NULL))
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_RTC_ALARM(sAlarm->Alarm));

  /* Process Locked */ 
  __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY;
  
  /* Call HAL_RTC_GetTime function to update date if counter higher than 24 hours */
  if (HAL_RTC_GetTime(hrtc, &stime, RTC_FORMAT_BIN) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Convert time in seconds */
  counter_time = (uint32_t)(((uint32_t)stime.Hours * 3600) + \
                      ((uint32_t)stime.Minutes * 60) + \
                      ((uint32_t)stime.Seconds));  

  if(Format == RTC_FORMAT_BIN)
  {
    assert_param(IS_RTC_HOUR24(sAlarm->AlarmTime.Hours));
    assert_param(IS_RTC_MINUTES(sAlarm->AlarmTime.Minutes));
    assert_param(IS_RTC_SECONDS(sAlarm->AlarmTime.Seconds));
    
    counter_alarm = (uint32_t)(((uint32_t)sAlarm->AlarmTime.Hours * 3600) + \
                        ((uint32_t)sAlarm->AlarmTime.Minutes * 60) + \
                        ((uint32_t)sAlarm->AlarmTime.Seconds));  
  }
  else
  {
    assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)));
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds)));
    
    counter_alarm = (((uint32_t)(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)) * 3600) + \
              ((uint32_t)(RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes)) * 60) + \
              ((uint32_t)RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds)));   
  }

  /* Check that requested alarm should expire in the same day (otherwise add 1 day) */
  if (counter_alarm < counter_time)
  {
    /* Add 1 day to alarm counter*/
    counter_alarm += (uint32_t)(24 * 3600);
  }

  /* Write Alarm counter in RTC registers */
  if (RTC_WriteAlarmCounter(hrtc, counter_alarm) != HAL_OK)
  {
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Process Unlocked */ 
    __HAL_UNLOCK(hrtc);
    
    return HAL_ERROR;
  }
  else
  {
    hrtc->State = HAL_RTC_STATE_READY;
  
   __HAL_UNLOCK(hrtc); 
     
   return HAL_OK;
  }
}

/**
  * @brief  Sets the specified RTC Alarm with Interrupt 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sAlarm: Pointer to Alarm structure
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg RTC_FORMAT_BIN: Binary data format 
  *             @arg RTC_FORMAT_BCD: BCD data format
  * @note   The HAL_RTC_SetTime() must be called before enabling the Alarm feature.   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_SetAlarm_IT(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format)
{
  uint32_t counter_alarm = 0, counter_time;
  RTC_TimeTypeDef stime = {0};
  
  /* Check input parameters */
  if((hrtc == NULL) || (sAlarm == NULL))
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_RTC_ALARM(sAlarm->Alarm));

  /* Process Locked */ 
  __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY;
  
  /* Call HAL_RTC_GetTime function to update date if counter higher than 24 hours */
  if (HAL_RTC_GetTime(hrtc, &stime, RTC_FORMAT_BIN) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Convert time in seconds */
  counter_time = (uint32_t)(((uint32_t)stime.Hours * 3600) + \
                      ((uint32_t)stime.Minutes * 60) + \
                      ((uint32_t)stime.Seconds));  

  if(Format == RTC_FORMAT_BIN)
  {
    assert_param(IS_RTC_HOUR24(sAlarm->AlarmTime.Hours));
    assert_param(IS_RTC_MINUTES(sAlarm->AlarmTime.Minutes));
    assert_param(IS_RTC_SECONDS(sAlarm->AlarmTime.Seconds));
    
    counter_alarm = (uint32_t)(((uint32_t)sAlarm->AlarmTime.Hours * 3600) + \
      ((uint32_t)sAlarm->AlarmTime.Minutes * 60) + \
        ((uint32_t)sAlarm->AlarmTime.Seconds));  
  }
  else
  {
    assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)));
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds)));
    
    counter_alarm = (((uint32_t)(RTC_Bcd2ToByte(sAlarm->AlarmTime.Hours)) * 3600) + \
      ((uint32_t)(RTC_Bcd2ToByte(sAlarm->AlarmTime.Minutes)) * 60) + \
        ((uint32_t)RTC_Bcd2ToByte(sAlarm->AlarmTime.Seconds)));   
  }
  
  /* Check that requested alarm should expire in the same day (otherwise add 1 day) */
  if (counter_alarm < counter_time)
  {
    /* Add 1 day to alarm counter*/
    counter_alarm += (uint32_t)(24 * 3600);
  }

  /* Write alarm counter in RTC registers */
  if (RTC_WriteAlarmCounter(hrtc, counter_alarm) != HAL_OK)
  {
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Process Unlocked */ 
    __HAL_UNLOCK(hrtc);
    
    return HAL_ERROR;
  }
  else
  {
    /* Clear flag alarm A */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);
    
    /* Configure the Alarm interrupt */
    __HAL_RTC_ALARM_ENABLE_IT(hrtc,RTC_IT_ALRA);
    
    /* RTC Alarm Interrupt Configuration: EXTI configuration */
    __HAL_RTC_ALARM_EXTI_ENABLE_IT();
    
    __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE();

    hrtc->State = HAL_RTC_STATE_READY;
  
   __HAL_UNLOCK(hrtc); 
     
   return HAL_OK;
  }
}

/**
  * @brief  Gets the RTC Alarm value and masks.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  sAlarm: Pointer to Date structure
  * @param  Alarm: Specifies the Alarm.
  *          This parameter can be one of the following values:
  *             @arg RTC_ALARM_A: Alarm
  * @param  Format: Specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *             @arg RTC_FORMAT_BIN: Binary data format 
  *             @arg RTC_FORMAT_BCD: BCD data format
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_GetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Alarm, uint32_t Format)
{
  uint32_t counter_alarm = 0;

  /* Check input parameters */
  if((hrtc == NULL) || (sAlarm == NULL))
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(Format));
  assert_param(IS_RTC_ALARM(Alarm));
  
  /* Read Alarm counter in RTC registers */
  counter_alarm = RTC_ReadAlarmCounter(hrtc);

  /* Fill the structure with the read parameters */
  /* Set hours in a day range (between 0 to 24)*/
  sAlarm->AlarmTime.Hours   = (uint32_t)((counter_alarm / 3600) % 24);
  sAlarm->AlarmTime.Minutes = (uint32_t)((counter_alarm % 3600) / 60);
  sAlarm->AlarmTime.Seconds = (uint32_t)((counter_alarm % 3600) % 60);
  
  if(Format != RTC_FORMAT_BIN)
  {
    sAlarm->AlarmTime.Hours   = RTC_ByteToBcd2(sAlarm->AlarmTime.Hours);
    sAlarm->AlarmTime.Minutes = RTC_ByteToBcd2(sAlarm->AlarmTime.Minutes);
    sAlarm->AlarmTime.Seconds = RTC_ByteToBcd2(sAlarm->AlarmTime.Seconds);
  }  
  
  return HAL_OK;
}

/**
  * @brief  Deactive the specified RTC Alarm 
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Alarm: Specifies the Alarm.
  *          This parameter can be one of the following values:
  *            @arg RTC_ALARM_A:  AlarmA
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_DeactivateAlarm(RTC_HandleTypeDef *hrtc, uint32_t Alarm)
{
  /* Check the parameters */
  assert_param(IS_RTC_ALARM(Alarm));
  
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Process Locked */ 
  __HAL_LOCK(hrtc);
  
  hrtc->State = HAL_RTC_STATE_BUSY;
  
  /* In case of interrupt mode is used, the interrupt source must disabled */ 
  __HAL_RTC_ALARM_DISABLE_IT(hrtc, RTC_IT_ALRA);
  
  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    /* Set RTC state */
    hrtc->State = HAL_RTC_STATE_ERROR;
    
    /* Process Unlocked */ 
    __HAL_UNLOCK(hrtc);
    
    return HAL_ERROR;
  } 
  else
  {
    /* Clear flag alarm A */
    __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);
    
    /* Set to default values ALRH & ALRL registers */
    WRITE_REG(hrtc->Instance->ALRH, RTC_ALARM_RESETVALUE_REGISTER);
    WRITE_REG(hrtc->Instance->ALRL, RTC_ALARM_RESETVALUE_REGISTER);

    /* RTC Alarm Interrupt Configuration: Disable EXTI configuration */
    __HAL_RTC_ALARM_EXTI_DISABLE_IT();
    
    /* Wait for synchro */
    if(RTC_ExitInitMode(hrtc) != HAL_OK)
    {       
      hrtc->State = HAL_RTC_STATE_ERROR;
      
      /* Process Unlocked */ 
      __HAL_UNLOCK(hrtc);
      
      return HAL_ERROR;
    }
  }
  hrtc->State = HAL_RTC_STATE_READY; 
  
  /* Process Unlocked */ 
  __HAL_UNLOCK(hrtc);  
  
  return HAL_OK; 
}

/**
  * @brief  This function handles Alarm interrupt request.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
void HAL_RTC_AlarmIRQHandler(RTC_HandleTypeDef* hrtc)
{  
  if(__HAL_RTC_ALARM_GET_IT_SOURCE(hrtc, RTC_IT_ALRA))
  {
    /* Get the status of the Interrupt */
    if(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAF) != (uint32_t)RESET)
    {
      /* AlarmA callback */ 
      HAL_RTC_AlarmAEventCallback(hrtc);
      
      /* Clear the Alarm interrupt pending bit */
      __HAL_RTC_ALARM_CLEAR_FLAG(hrtc,RTC_FLAG_ALRAF);
    }
  }
  
  /* Clear the EXTI's line Flag for RTC Alarm */
  __HAL_RTC_ALARM_EXTI_CLEAR_FLAG();
  
  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY; 
}

/**
  * @brief  Alarm A callback.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval None
  */
__weak void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RTC_AlarmAEventCallback could be implemented in the user file
   */
}

/**
  * @brief  This function handles AlarmA Polling request.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  Timeout: Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_PollForAlarmAEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout)
{  
  uint32_t tickstart = HAL_GetTick();   
  
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  while(__HAL_RTC_ALARM_GET_FLAG(hrtc, RTC_FLAG_ALRAF) == RESET)
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
  
  /* Clear the Alarm interrupt pending bit */
  __HAL_RTC_ALARM_CLEAR_FLAG(hrtc, RTC_FLAG_ALRAF);
  
  /* Change RTC state */
  hrtc->State = HAL_RTC_STATE_READY; 
  
  return HAL_OK;  
}

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group4 Peripheral State functions 
 *  @brief   Peripheral State functions 
 *
@verbatim   
 ===============================================================================
                     ##### Peripheral State functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Get RTC state

@endverbatim
  * @{
  */
/**
  * @brief  Returns the RTC state.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL state
  */
HAL_RTCStateTypeDef HAL_RTC_GetState(RTC_HandleTypeDef* hrtc)
{
  return hrtc->State;
}

/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group5 Peripheral Control functions 
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
  * @brief  Waits until the RTC registers (RTC_CNT, RTC_ALR and RTC_PRL)
  *   are synchronized with RTC APB clock.
  * @note   This function must be called before any read operation after an APB reset
  *   or an APB clock stop.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RTC_WaitForSynchro(RTC_HandleTypeDef* hrtc)
{
  uint32_t tickstart = 0;
  
  /* Check input parameters */
  if(hrtc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Clear RSF flag */
  CLEAR_BIT(hrtc->Instance->CRL, RTC_FLAG_RSF);
  
  tickstart = HAL_GetTick();
  
  /* Wait the registers to be synchronised */
  while((hrtc->Instance->CRL & RTC_FLAG_RSF) == (uint32_t)RESET)
  {
    if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
    {       
      return HAL_TIMEOUT;
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

/** @addtogroup RTC_Private_Functions
  * @{
  */
  

/**
  * @brief  Read the time counter available in RTC_CNT registers.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval Time counter
  */
static uint32_t RTC_ReadTimeCounter(RTC_HandleTypeDef* hrtc)
{
  uint16_t high1 = 0, high2 = 0, low = 0;
  uint32_t timecounter = 0;

  high1 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
  low   = READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT);
  high2 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);

  if (high1 != high2)
  { /* In this case the counter roll over during reading of CNTL and CNTH registers, 
       read again CNTL register then return the counter value */
    timecounter = (((uint32_t) high2 << 16 ) | READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT));
  }
  else
  { /* No counter roll over during reading of CNTL and CNTH registers, counter 
       value is equal to first value of CNTL and CNTH */
    timecounter = (((uint32_t) high1 << 16 ) | low);
  }

  return timecounter;
}

/**
  * @brief  Write the time counter in RTC_CNT registers.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  TimeCounter: Counter to write in RTC_CNT registers
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_WriteTimeCounter(RTC_HandleTypeDef* hrtc, uint32_t TimeCounter)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    status = HAL_ERROR;
  } 
  else
  {
    /* Set RTC COUNTER MSB word */
    WRITE_REG(hrtc->Instance->CNTH, (TimeCounter >> 16));
    /* Set RTC COUNTER LSB word */
    WRITE_REG(hrtc->Instance->CNTL, (TimeCounter & RTC_CNTL_RTC_CNT));
    
    /* Wait for synchro */
    if(RTC_ExitInitMode(hrtc) != HAL_OK)
    {       
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Read the time counter available in RTC_ALR registers.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval Time counter
  */
static uint32_t RTC_ReadAlarmCounter(RTC_HandleTypeDef* hrtc)
{
  uint16_t high1 = 0, low = 0;

  high1 = READ_REG(hrtc->Instance->ALRH & RTC_CNTH_RTC_CNT);
  low   = READ_REG(hrtc->Instance->ALRL & RTC_CNTL_RTC_CNT);

  return (((uint32_t) high1 << 16 ) | low);
}

/**
  * @brief  Write the time counter in RTC_ALR registers.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  AlarmCounter: Counter to write in RTC_ALR registers
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_WriteAlarmCounter(RTC_HandleTypeDef* hrtc, uint32_t AlarmCounter)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    status = HAL_ERROR;
  } 
  else
  {
    /* Set RTC COUNTER MSB word */
    WRITE_REG(hrtc->Instance->ALRH, (AlarmCounter >> 16));
    /* Set RTC COUNTER LSB word */
    WRITE_REG(hrtc->Instance->ALRL, (AlarmCounter & RTC_ALRL_RTC_ALR));
    
    /* Wait for synchro */
    if(RTC_ExitInitMode(hrtc) != HAL_OK)
    {       
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef* hrtc)
{
  uint32_t tickstart = 0;
  
  tickstart = HAL_GetTick();
  /* Wait till RTC is in INIT state and if Time out is reached exit */
  while((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
  {
    if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
    {       
      return HAL_TIMEOUT;
    } 
  }

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
  
  
  return HAL_OK;  
}

/**
  * @brief  Exit the RTC Initialization mode.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef* hrtc)
{
  uint32_t tickstart = 0;
  
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  
  tickstart = HAL_GetTick();
  /* Wait till RTC is in INIT state and if Time out is reached exit */
  while((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
  {
    if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
    {       
      return HAL_TIMEOUT;
    } 
  }
  
  return HAL_OK;  
}

/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  Value: Byte to be converted
  * @retval Converted byte
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
  uint32_t bcdhigh = 0;
  
  while(Value >= 10)
  {
    bcdhigh++;
    Value -= 10;
  }
  
  return  ((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * @brief  Converts from 2 digit BCD to Binary.
  * @param  Value: BCD value to be converted
  * @retval Converted word
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
  uint32_t tmp = 0;
  tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (Value & (uint8_t)0x0F));
}

/**
  * @brief  Updates date when time is 23:59:59.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  DayElapsed: Number of days elapsed from last date update
  * @retval None
  */
static void RTC_DateUpdate(RTC_HandleTypeDef* hrtc, uint32_t DayElapsed)
{
  uint32_t year = 0, month = 0, day = 0;
  uint32_t loop = 0;

  /* Get the current year*/
  year = hrtc->DateToUpdate.Year;

  /* Get the current month and day */
  month = hrtc->DateToUpdate.Month;
  day = hrtc->DateToUpdate.Date;

  for (loop = 0; loop < DayElapsed; loop++)
  {
    if((month == 1) || (month == 3) || (month == 5) || (month == 7) || \
       (month == 8) || (month == 10) || (month == 12))
    {
      if(day < 31)
      {
        day++;
      }
      /* Date structure member: day = 31 */
      else
      {
        if(month != 12)
        {
          month++;
          day = 1;
        }
        /* Date structure member: day = 31 & month =12 */
        else
        {
          month = 1;
          day = 1;
          year++;
        }
      }
    }
    else if((month == 4) || (month == 6) || (month == 9) || (month == 11))
    {
      if(day < 30)
      {
        day++;
      }
      /* Date structure member: day = 30 */
      else
      {
        month++;
        day = 1;
      }
    }
    else if(month == 2)
    {
      if(day < 28)
      {
        day++;
      }
      else if(day == 28)
      {
        /* Leap year */
        if(RTC_IsLeapYear(year))
        {
          day++;
        }
        else
        {
          month++;
          day = 1;
        }
      }
      else if(day == 29)
      {
        month++;
        day = 1;
      }
    }
  }

  /* Update year */
  hrtc->DateToUpdate.Year = year;

  /* Update day and month */
  hrtc->DateToUpdate.Month = month;
  hrtc->DateToUpdate.Date = day;

  /* Update day of the week */
  hrtc->DateToUpdate.WeekDay = RTC_WeekDayNum(year, month, day);
}

/**
  * @brief  Check whether the passed year is Leap or not.
  * @param  nYear  year to check
  * @retval 1: leap year
  *         0: not leap year
  */
static uint8_t RTC_IsLeapYear(uint16_t nYear)
{
  if((nYear % 4) != 0) 
  {
    return 0;
  }
  
  if((nYear % 100) != 0) 
  {
    return 1;
  }
  
  if((nYear % 400) == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Determines the week number, the day number and the week day number.
  * @param  nYear   year to check
  * @param  nMonth  Month to check
  * @param  nDay    Day to check
  * @note   Day is calculated with hypothesis that year > 2000
  * @retval Value which can take one of the following parameters:
  *         @arg RTC_WEEKDAY_MONDAY
  *         @arg RTC_WEEKDAY_TUESDAY
  *         @arg RTC_WEEKDAY_WEDNESDAY
  *         @arg RTC_WEEKDAY_THURSDAY
  *         @arg RTC_WEEKDAY_FRIDAY
  *         @arg RTC_WEEKDAY_SATURDAY
  *         @arg RTC_WEEKDAY_SUNDAY
  */
static uint8_t RTC_WeekDayNum(uint32_t nYear, uint8_t nMonth, uint8_t nDay)
{
  uint32_t year = 0, weekday = 0;

  year = 2000 + nYear;
  
  if(nMonth < 3)
  {
    /*D = { [(23 x month)/9] + day + 4 + year + [(year-1)/4] - [(year-1)/100] + [(year-1)/400] } mod 7*/
    weekday = (((23 * nMonth)/9) + nDay + 4 + year + ((year-1)/4) - ((year-1)/100) + ((year-1)/400)) % 7;
  }
  else
  {
    /*D = { [(23 x month)/9] + day + 4 + year + [year/4] - [year/100] + [year/400] - 2 } mod 7*/
    weekday = (((23 * nMonth)/9) + nDay + 4 + year + (year/4) - (year/100) + (year/400) - 2 ) % 7; 
  }

  return (uint8_t)weekday;
}

/**
  * @}
  */

#endif /* HAL_RTC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
