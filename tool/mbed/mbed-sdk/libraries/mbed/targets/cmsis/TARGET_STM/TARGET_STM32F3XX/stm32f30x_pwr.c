/**
  ******************************************************************************
  * @file    stm32f30x_pwr.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Power Controller (PWR) peripheral:           
  *           + Backup Domain Access
  *           + PVD configuration
  *           + WakeUp pins configuration
  *           + Low Power modes configuration
  *           + Flags management
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
#include "stm32f30x_pwr.h"
#include "stm32f30x_rcc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR 
  * @brief PWR driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* --------- PWR registers bit address in the alias region ---------- */
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* --- CR Register ---*/

/* Alias word address of DBP bit */
#define CR_OFFSET                (PWR_OFFSET + 0x00)
#define DBP_BitNumber            0x08
#define CR_DBP_BB                (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber           0x04
#define CR_PVDE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* ------------------ PWR registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_DS_MASK               ((uint32_t)0xFFFFFFFC)
#define CR_PLS_MASK              ((uint32_t)0xFFFFFF1F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions
  * @{
  */

/** @defgroup PWR_Group1 Backup Domain Access function 
 *  @brief   Backup Domain Access function
 *
@verbatim
  ==============================================================================
                   ##### Backup Domain Access function #####
  ==============================================================================

    [..] After reset, the Backup Domain Registers (RCC BDCR Register, RTC registers
         and RTC backup registers) are protected against possible stray write accesses.
    [..] To enable access to Backup domain use the PWR_BackupAccessCmd(ENABLE) function.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void PWR_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
  * @brief  Enables or disables access to the RTC and backup registers.
  * @note   If the HSE divided by 32 is used as the RTC clock, the 
  *         Backup Domain Access should be kept enabled.
  * @param  NewState: new state of the access to the RTC and backup registers.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)NewState;
}

/**
  * @}
  */

/** @defgroup PWR_Group2 PVD configuration functions
 *  @brief   PVD configuration functions 
 *
@verbatim   
 ===============================================================================
                    ##### PVD configuration functions #####
  ==============================================================================
  [..]
  (+) The PVD is used to monitor the VDD power supply by comparing it to a threshold
      selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
  (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower than the 
      PVD threshold. This event is internally connected to the EXTI line16
      and can generate an interrupt if enabled through the EXTI registers.
  (+) The PVD is stopped in Standby mode.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDLevel: specifies the PVD detection level
  *         This parameter can be one of the following values:
  *             @arg PWR_PVDLevel_0: PVD detection level set to 2.18V
  *             @arg PWR_PVDLevel_1: PVD detection level set to 2.28V
  *             @arg PWR_PVDLevel_2: PVD detection level set to 2.38V
  *             @arg PWR_PVDLevel_3: PVD detection level set to 2.48V
  *             @arg PWR_PVDLevel_4: PVD detection level set to 2.58V
  *             @arg PWR_PVDLevel_5: PVD detection level set to 2.68V
  *             @arg PWR_PVDLevel_6: PVD detection level set to 2.78V
  *             @arg PWR_PVDLevel_7: PVD detection level set to 2.88V
  * @retval None
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
  
  tmpreg = PWR->CR;
  
  /* Clear PLS[7:5] bits */
  tmpreg &= CR_PLS_MASK;
  
  /* Set PLS[7:5] bits according to PWR_PVDLevel value */
  tmpreg |= PWR_PVDLevel;
  
  /* Store the new value */
  PWR->CR = tmpreg;
}

/**
  * @brief  Enables or disables the Power Voltage Detector(PVD).
  * @param  NewState: new state of the PVD.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PVDCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)NewState;
}

/**
  * @}
  */

/** @defgroup PWR_Group3 WakeUp pins configuration functions
 *  @brief   WakeUp pins configuration functions 
 *
@verbatim   
 ===============================================================================
              ##### WakeUp pins configuration functions #####
 ===============================================================================  
    [..]
    (+) WakeUp pins are used to wakeup the system from Standby mode. These pins are 
        forced in input pull down configuration and are active on rising edges.
    (+) There are three WakeUp pins: WakeUp Pin 1 on PA.00, WakeUp Pin 2 on PC.13 and
        WakeUp Pin 3 on PE.06.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the WakeUp Pin functionality.
  * @param  PWR_WakeUpPin: specifies the WakeUpPin.
  *         This parameter can be: PWR_WakeUpPin_1, PWR_WakeUpPin_2 or PWR_WakeUpPin_3.
  * @param  NewState: new state of the WakeUp Pin functionality.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState)
{  
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(PWR_WakeUpPin));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the EWUPx pin */
    PWR->CSR |= PWR_WakeUpPin;
  }
  else
  {
    /* Disable the EWUPx pin */
    PWR->CSR &= ~PWR_WakeUpPin;
  }
}

/**
  * @}
  */


/** @defgroup PWR_Group4 Low Power modes configuration functions
 *  @brief   Low Power modes configuration functions 
 *
@verbatim   
 ===============================================================================
              ##### Low Power modes configuration functions #####
  ==============================================================================

    [..] The devices feature three low-power modes:
    (+) Sleep mode: Cortex-M4 core stopped, peripherals kept running.
    (+) Stop mode: all clocks are stopped, regulator running, regulator in low power mode
    (+) Standby mode: VCORE domain powered off

  *** Sleep mode *** 
  ==================
  [..] 
    (+) Entry:
        (++) The Sleep mode is entered by executing the WFE() or WFI() instructions.
    (+) Exit:
        (++) Any peripheral interrupt acknowledged by the nested vectored interrupt 
             controller (NVIC) can wake up the device from Sleep mode.

  *** Stop mode *** 
  =================
  [..] In Stop mode, all clocks in the VCORE domain are stopped, the PLL, the HSI,
       and the HSE RC oscillators are disabled. Internal SRAM and register 
       contents are preserved.
       The voltage regulator can be configured either in normal or low-power mode.

    (+) Entry:
        (++) The Stop mode is entered using the PWR_EnterSTOPMode(PWR_Regulator_LowPower,) 
             function with regulator in LowPower or with Regulator ON.
    (+) Exit:
        (++) Any EXTI Line (Internal or External) configured in Interrupt/Event mode
             or any internal IPs (I2C or UASRT) wakeup event.

  *** Standby mode *** 
  ====================
  [..] The Standby mode allows to achieve the lowest power consumption. It is based 
       on the Cortex-M4 deepsleep mode, with the voltage regulator disabled. 
       The VCORE domain is consequently powered off. The PLL, the HSI, and the HSE 
       oscillator are also switched off. SRAM and register 
       contents are lost except for the Backup domain (RTC registers, RTC backup 
       registers and Standby circuitry).
   
  [..] The voltage regulator is OFF.

    (+) Entry:
        (++) The Standby mode is entered using the PWR_EnterSTANDBYMode() function.
    (+) Exit:
        (++) WKUP pin rising edge, RTC alarm (Alarm A and Alarm B), RTC wakeup,
             tamper event, time-stamp event, external reset in NRST pin, IWDG reset.

  *** Auto-wakeup (AWU) from low-power mode *** 
  =============================================
  [..] The MCU can be woken up from low-power mode by an RTC Alarm event, a tamper 
       event, a time-stamp event, or a comparator event, without depending on an 
       external interrupt (Auto-wakeup mode).

    (+) RTC auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to:
             (+++) Configure the EXTI Line 17 to be sensitive to rising edges (Interrupt 
                   or Event modes) using the EXTI_Init() function.
             (+++) Enable the RTC Alarm Interrupt using the RTC_ITConfig() function
             (+++) Configure the RTC to generate the RTC alarm using the RTC_SetAlarm() 
                   and RTC_AlarmCmd() functions.
        (++) To wake up from the Stop mode with an RTC Tamper or time stamp event, it 
             is necessary to:
             (+++) Configure the EXTI Line 19 to be sensitive to rising edges (Interrupt 
                   or Event modes) using the EXTI_Init() function.
             (+++) Enable the RTC Tamper or time stamp Interrupt using the RTC_ITConfig() 
                   function.
             (+++) Configure the RTC to detect the tamper or time stamp event using the
                   RTC_TimeStampConfig(), RTC_TamperTriggerConfig() and RTC_TamperCmd()
                   functions.

    (+) RTC auto-wakeup (AWU) from the Standby mode
        (++) To wake up from the Standby mode with an RTC alarm event, it is necessary to:
             (+++) Enable the RTC Alarm Interrupt using the RTC_ITConfig() function.
             (+++) Configure the RTC to generate the RTC alarm using the RTC_SetAlarm() 
                   and RTC_AlarmCmd() functions.
        (++) To wake up from the Standby mode with an RTC Tamper or time stamp event, it 
             is necessary to:
             (+++) Enable the RTC Tamper or time stamp Interrupt using the RTC_ITConfig() 
                   function.
             (+++) Configure the RTC to detect the tamper or time stamp event using the
                   RTC_TimeStampConfig(), RTC_TamperTriggerConfig() and RTC_TamperCmd()
                   functions.

    (+) Comparator auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with a comparator wakeup event, it is necessary to:
             (+++) Configure the correspondant comparator EXTI Line to be sensitive to 
                   the selected edges (falling, rising or falling and rising) 
                   (Interrupt or Event modes) using the EXTI_Init() function.
             (+++) Configure the comparator to generate the event.

@endverbatim
  * @{
  */

/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.                 
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *             @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *             @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));
  
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  
  /* Select SLEEP mode entry -------------------------------------------------*/
  if(PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
  {   
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE();
  }
}

/**
  * @brief  Enters STOP mode.
  * @note   In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note   When exiting Stop mode by issuing an interrupt or a wakeup event, 
  *         the HSI RC oscillator is selected as system clock.
  * @note   When the voltage regulator operates in low power mode, an additional 
  *         startup delay is incurred when waking up from Stop mode. 
  *         By keeping the internal regulator ON during Stop mode, the consumption 
  *         is higher although the startup time is reduced.
  * @param  PWR_Regulator: specifies the regulator state in STOP mode.
  *         This parameter can be one of the following values:
  *             @arg PWR_Regulator_ON: STOP mode with regulator ON
  *             @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
  * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *             @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
  *             @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(PWR_Regulator));
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
  
  /* Select the regulator state in STOP mode ---------------------------------*/
  tmpreg = PWR->CR;
  /* Clear PDDS and LPDSR bits */
  tmpreg &= CR_DS_MASK;
  
  /* Set LPDSR bit according to PWR_Regulator value */
  tmpreg |= PWR_Regulator;
  
  /* Store the new value */
  PWR->CR = tmpreg;
  
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  
  /* Select STOP mode entry --------------------------------------------------*/
  if(PWR_STOPEntry == PWR_STOPEntry_WFI)
  {   
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE();
  }
  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);  
}

/**
  * @brief  Enters STANDBY mode.
  * @note   In Standby mode, all I/O pins are high impedance except for:
  * @note     Reset pad (still available) 
  * @note     RTC_AF1 pin (PC13) if configured for Wakeup pin 2 (WKUP2), tamper, 
  *           time-stamp, RTC Alarm out, or RTC clock calibration out.
  * @note     WKUP pin 1 (PA0) and WKUP pin 3 (PE6), if enabled.       
  * @param  None
  * @retval None
  */
void PWR_EnterSTANDBYMode(void)
{
  /* Clear Wakeup flag */
  PWR->CR |= PWR_CR_CWUF;
  
  /* Select STANDBY mode */
  PWR->CR |= PWR_CR_PDDS;
  
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  
/* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM   )
  __force_stores();
#endif
  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @}
  */

/** @defgroup PWR_Group5 Flags management functions
 *  @brief   Flags management functions 
 *
@verbatim   
 ===============================================================================
                    ##### Flags management functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified PWR flag is set or not.
  * @param  PWR_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg PWR_FLAG_WU: Wake Up flag. This flag indicates that a wakeup event 
  *       was received from the WKUP pin or from the RTC alarm (Alarm A or Alarm B), 
  *       RTC Tamper event, RTC TimeStamp event or RTC Wakeup.
  *     @arg PWR_FLAG_SB: StandBy flag. This flag indicates that the system was
  *                       resumed from StandBy mode.    
  *     @arg PWR_FLAG_PVDO: PVD Output. This flag is valid only if PVD is enabled 
  *       by the PWR_PVDCmd() function.
  *     @arg PWR_FLAG_VREFINTRDY: Internal Voltage Reference Ready flag. This 
  *       flag indicates the state of the internal voltage reference, VREFINT.
  * @retval The new state of PWR_FLAG (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_PWR_GET_FLAG(PWR_FLAG));
  
  if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clears the PWR's pending flags.
  * @param  PWR_FLAG: specifies the flag to clear.
  *   This parameter can be one of the following values:
  *     @arg PWR_FLAG_WU: Wake Up flag
  *     @arg PWR_FLAG_SB: StandBy flag
  * @retval None
  */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
  /* Check the parameters */
  assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));
         
  PWR->CR |=  PWR_FLAG << 2;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
