/**
  ******************************************************************************
  * @file    stm32f0xx_hal_pwr.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Initialization/de-initialization function
  *           + Peripheral Control function
  *
  @verbatim
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
#include "stm32f0xx_hal.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR HAL module Driver 
  * @brief PWR HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Initialization and de-initialization functions 
  *  @brief    Initialization and de-initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
      After reset, the backup domain (RTC registers, RTC backup data
      registers) is protected against possible unwanted
      write accesses.
      To enable access to the RTC Domain and RTC registers, proceed as follows:
        (+) Enable the Power Controller (PWR) APB1 interface clock using the
            __PWR_CLK_ENABLE() macro.
        (+) Enable access to RTC domain using the HAL_PWR_EnableBkUpAccess() function.

@endverbatim
  * @{
  */

/**
  * @brief Deinitializes the PWR peripheral registers to their default reset values.
  * @retval None
  */
void HAL_PWR_DeInit(void)
{
  __PWR_FORCE_RESET();
  __PWR_RELEASE_RESET();
}

/**
  * @brief Enables access to the backup domain (RTC registers, RTC
  *         backup data registers).
  * @note  If the HSE divided by 32 is used as the RTC clock, the
  *         Backup Domain Access should be kept enabled.
  * @retval None
  */
void HAL_PWR_EnableBkUpAccess(void)
{
  PWR->CR |= (uint32_t)PWR_CR_DBP;
}

/**
  * @brief Disables access to the backup domain (RTC registers, RTC
  *         backup data registers).
  * @note  If the HSE divided by 32 is used as the RTC clock, the
  *         Backup Domain Access should be kept enabled.
  * @retval None
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  PWR->CR &= ~((uint32_t)PWR_CR_DBP);
}

/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2 Peripheral Control functions 
  *  @brief Low Power modes configuration functions
  *
@verbatim

 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================
    
    *** WakeUp pin configuration ***
    ================================
    [..]
      (+) WakeUp pin is used to wakeup the system from Standby mode. This pin is
          forced in input pull down configuration and is active on rising edges.
      (+) There are two WakeUp pins, and up to eight Wakeup pins on STM32F07x & STM32F09x devices.
         (++)WakeUp Pin 1 on PA.00.
         (++)WakeUp Pin 2 on PC.13.
         (++)WakeUp Pin 3 on PE.06.(STM32F07x/STM32F09x)
         (++)WakeUp Pin 4 on PA.02.(STM32F07x/STM32F09x)
         (++)WakeUp Pin 5 on PC.05.(STM32F07x/STM32F09x)
         (++)WakeUp Pin 6 on PB.05.(STM32F07x/STM32F09x)
         (++)WakeUp Pin 7 on PB.15.(STM32F07x/STM32F09x)
         (++)WakeUp Pin 8 on PF.02.(STM32F07x/STM32F09x)

    *** Low Power modes configuration ***
    =====================================
    [..]
      The devices feature 3 low-power modes:
      (+) Sleep mode: Cortex-M0 core stopped, peripherals kept running.
      (+) Stop mode: all clocks are stopped, regulator running, regulator
          in low power mode
      (+) Standby mode: 1.2V domain powered off (mode not available on STM32F0x8 devices).

   *** Sleep mode ***
   ==================
    [..]
      (+) Entry:
          The Sleep mode is entered by using the HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFx)
              functions with
          (++) PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
          (++) PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
     
      (+) Exit:
        (++) Any peripheral interrupt acknowledged by the nested vectored interrupt
              controller (NVIC) can wake up the device from Sleep mode.

   *** Stop mode ***
   =================
    [..]
      In Stop mode, all clocks in the 1.8V domain are stopped, the PLL, the HSI,
      and the HSE RC oscillators are disabled. Internal SRAM and register contents
      are preserved.
      The voltage regulator can be configured either in normal or low-power mode.
      To minimize the consumption.

      (+) Entry:
          The Stop mode is entered using the HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI )
             function with:
          (++) Main regulator ON.
          (++) Low Power regulator ON.
          (++) PWR_STOPENTRY_WFI: enter STOP mode with WFI instruction
          (++) PWR_STOPENTRY_WFE: enter STOP mode with WFE instruction
      (+) Exit:
          (++) Any EXTI Line (Internal or External) configured in Interrupt/Event mode.
          (++) Some specific communication peripherals (CEC, USART, I2C) interrupts, 
               when programmed in wakeup mode (the peripheral must be 
               programmed in wakeup mode and the corresponding interrupt vector 
               must be enabled in the NVIC)

   *** Standby mode ***
   ====================
     [..]
      The Standby mode allows to achieve the lowest power consumption. It is based
      on the Cortex-M0 deep sleep mode, with the voltage regulator disabled.
      The 1.8V domain is consequently powered off. The PLL, the HSI oscillator and
      the HSE oscillator are also switched off. SRAM and register contents are lost
      except for the RTC registers, RTC backup registers and Standby circuitry.
      The voltage regulator is OFF.

      (+) Entry:
          (++) The Standby mode is entered using the HAL_PWR_EnterSTANDBYMode() function.
      (+) Exit:
          (++) WKUP pin rising edge, RTC alarm (Alarm A), RTC wakeup,
               tamper event, time-stamp event, external reset in NRST pin, IWDG reset.

   *** Auto-wakeup (AWU) from low-power mode ***
   =============================================
    [..]
      The MCU can be woken up from low-power mode by an RTC Alarm event, an RTC
      Wakeup event, a tamper event, a time-stamp event, or a comparator event, 
      without depending on an external interrupt (Auto-wakeup mode).

    (+) RTC auto-wakeup (AWU) from the Stop and Standby modes

      (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to
            configure the RTC to generate the RTC alarm using the HAL_RTC_SetAlarm_IT() function.

      (++) To wake up from the Stop mode with an RTC Tamper or time stamp event, it
           is necessary to configure the RTC to detect the tamper or time stamp event using the
           HAL_RTC_SetTimeStamp_IT() or HAL_RTC_SetTamper_IT() functions.

      (++) To wake up from the Stop mode with an RTC WakeUp event, it is necessary to
           configure the RTC to generate the RTC WakeUp event using the HAL_RTC_SetWakeUpTimer_IT() function.

    (+) Comparator auto-wakeup (AWU) from the Stop mode

      (++) To wake up from the Stop mode with a comparator wakeup event, it is necessary to:
           (+++) Configure the EXTI Line associated with the comparator (example EXTI Line 22 for comparator 2) 
                 to be sensitive to to the selected edges (falling, rising or falling 
                 and rising) (Interrupt or Event modes) using the EXTI_Init() function.
           (+++) Configure the comparator to generate the event.      
@endverbatim
  * @{
  */

/**
  * @brief Enables the WakeUp PINx functionality.
  * @param WakeUpPinx: Specifies the Power Wake-Up pin to enable.
  *         This parameter can be value of :
  *           @ref PWREx_WakeUp_Pins
  * @retval None
  */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinx)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinx));
  PWR->CSR |= (PWR_CSR_EWUP1 << (uint8_t)WakeUpPinx);
}

/**
  * @brief Disables the WakeUp PINx functionality.
  * @param WakeUpPinx: Specifies the Power Wake-Up pin to disable.
  *         This parameter can be values of :
  *           @ref PWREx_WakeUp_Pins
  * @retval None
  */
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinx));
  PWR->CSR &= ~(PWR_CSR_EWUP1 << (uint8_t)WakeUpPinx);
}

/**
  * @brief Enters Sleep mode.
  * @note  In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param Regulator: Specifies the regulator state in SLEEP mode.
  *           On STM32F0 devices, this parameter is a dummy value and it is ignored
  *           as regulator can't be modified in this mode. Parameter is kept for platform
  *           compatibility.
  * @param SLEEPEntry: Specifies if SLEEP mode is entered with WFI or WFE instruction.
  *           When WFI entry is used, tick interrupt have to be disabled if not desired as 
  *           the interrupt wake up source.
  *           This parameter can be one of the following values:
  *            @arg PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
  *            @arg PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(Regulator));
  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

  /* Select SLEEP mode entry -------------------------------------------------*/
  if(SLEEPEntry == PWR_SLEEPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }
}

/**
  * @brief Enters STOP mode.
  * @note  In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note  When exiting Stop mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock.
  * @note  When the voltage regulator operates in low power mode, an additional
  *         startup delay is incurred when waking up from Stop mode.
  *         By keeping the internal regulator ON during Stop mode, the consumption
  *         is higher although the startup time is reduced.
  * @param Regulator: Specifies the regulator state in STOP mode.
  *          This parameter can be one of the following values:
  *            @arg PWR_MAINREGULATOR_ON: STOP mode with regulator ON
  *            @arg PWR_LOWPOWERREGULATOR_ON: STOP mode with low power regulator ON
  * @param STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg PWR_STOPENTRY_WFI:Enter STOP mode with WFI instruction
  *            @arg PWR_STOPENTRY_WFE: Enter STOP mode with WFE instruction
  * @retval None
  */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(Regulator));
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Select the regulator state in STOP mode ---------------------------------*/
  tmpreg = PWR->CR;
  
  /* Clear PDDS and LPDS bits */
  tmpreg &= (uint32_t)~(PWR_CR_PDDS | PWR_CR_LPDS);

  /* Set LPDS bit according to Regulator value */
  tmpreg |= Regulator;

  /* Store the new value */
  PWR->CR = tmpreg;

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  /* Select STOP mode entry --------------------------------------------------*/
  if(STOPEntry == PWR_STOPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/**
  * @brief Enters STANDBY mode.
  * @note  In Standby mode, all I/O pins are high impedance except for:
  *          - Reset pad (still available)
  *          - RTC alternate function pins if configured for tamper, time-stamp, RTC
  *            Alarm out, or RTC clock calibration out.
  *          - WKUP pins if enabled.
  *            STM32F0x8 devices, the Stop mode is available, but it is 
  *            aningless to distinguish between voltage regulator in Low power 
  *            mode and voltage regulator in Run mode because the regulator 
  *            not used and the core is supplied directly from an external source.
  *            Consequently, the Standby mode is not available on those devices.
  * @retval None
  */
void HAL_PWR_EnterSTANDBYMode(void)
{
  /* Select STANDBY mode */
  PWR->CR |= (uint32_t)PWR_CR_PDDS;

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
  __force_stores();
#endif
  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @brief Indicates Sleep-On-Exit when returning from Handler mode to Thread mode. 
  * @note Set SLEEPONEXIT bit of SCR register. When this bit is set, the processor 
  *       re-enters SLEEP mode when an interruption handling is over.
  *       Setting this bit is useful when the processor is expected to run only on
  *       interruptions handling.         
  * @retval None
  */
void HAL_PWR_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}


/**
  * @brief Disables Sleep-On-Exit feature when returning from Handler mode to Thread mode. 
  * @note Clears SLEEPONEXIT bit of SCR register. When this bit is set, the processor 
  *       re-enters SLEEP mode when an interruption handling is over.          
  * @retval None
  */
void HAL_PWR_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}



/**
  * @brief Enables CORTEX M4 SEVONPEND bit. 
  * @note Sets SEVONPEND bit of SCR register. When this bit is set, this causes 
  *       WFE to wake up when an interrupt moves from inactive to pended.
  * @retval None
  */
void HAL_PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}


/**
  * @brief Disables CORTEX M4 SEVONPEND bit. 
  * @note Clears SEVONPEND bit of SCR register. When this bit is set, this causes 
  *       WFE to wake up when an interrupt moves from inactive to pended.         
  * @retval None
  */
void HAL_PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_PWR_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
