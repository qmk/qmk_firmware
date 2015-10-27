/**
  ******************************************************************************
  * @file    stm32l1xx_hal_pwr.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   PWR HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Initialization/de-initialization functions
  *           + Peripheral Control functions 
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
#include "stm32l1xx_hal.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief    PWR HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PVD_MODE_IT               ((uint32_t)0x00010000)
#define PVD_MODE_EVT              ((uint32_t)0x00020000)
#define PVD_RISING_EDGE           ((uint32_t)0x00000001)
#define PVD_FALLING_EDGE          ((uint32_t)0x00000002)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Initialization and de-initialization functions 
  *  @brief   Initialization and de-initialization functions
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
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.
  * @note   Before calling this function, the VOS[1:0] bits should be configured 
  *         to "10" and the system frequency has to be configured accordingly. 
  *         To configure the VOS[1:0] bits, use the PWR_VoltageScalingConfig()
  *         function.      
  * @note   ULP and FWU bits are not reset by this function.    
  * @retval None
  */
void HAL_PWR_DeInit(void)
{
  __PWR_FORCE_RESET();
  __PWR_RELEASE_RESET();
}

/**
  * @brief  Enables access to the backup domain (RTC registers, RTC
  *         backup data registers ).
  * @note   If the HSE divided by 2, 4, 8 or 16 is used as the RTC clock, the
  *         Backup Domain Access should be kept enabled.
  * @retval None
  */
void HAL_PWR_EnableBkUpAccess(void)
{
  /* Enable access to RTC and backup registers */
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)ENABLE;
}

/**
  * @brief  Disables access to the backup domain (RTC registers, RTC
  *         backup data registers).
  * @note   If the HSE divided by 2, 4, 8 or 16 is used as the RTC clock, the
  *         Backup Domain Access should be kept enabled.
  * @retval None
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  /* Disable access to RTC and backup registers */
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)DISABLE;
}

/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2 Peripheral Control functions 
  * @brief    Low Power modes configuration functions
  *
@verbatim

 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================
     
    *** PVD configuration ***
    =========================
    [..]
      (+) The PVD is used to monitor the VDD power supply by comparing it to a
          threshold selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
      (+) The PVD can use an external input analog voltage (PVD_IN) which is compared 
      internally to VREFINT. The PVD_IN (PB7) has to be configured in Analog mode 
      when PWR_PVDLevel_7 is selected (PLS[2:0] = 111).

      (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower
          than the PVD threshold. This event is internally connected to the EXTI
          line16 and can generate an interrupt if enabled. This is done through
          __HAL_PVD_EXTI_ENABLE_IT() macro.
      (+) The PVD is stopped in Standby mode.

    *** WakeUp pin configuration ***
    ================================
    [..]
      (+) WakeUp pin is used to wake up the system from Standby mode. This pin is
          forced in input pull-down configuration and is active on rising edges.
      (+) There are two or three WakeUp pins:
          WakeUp Pin 1 on PA.00.
          WakeUp Pin 2 on PC.13.
          WakeUp Pin 3 on PE.06. : Only on product with GPIOE available 

    [..]
    *** Main and Backup Regulators configuration ***
    ================================================

      (+) The main internal regulator can be configured to have a tradeoff between
          performance and power consumption when the device does not operate at
          the maximum frequency. This is done through __HAL_PWR_VOLTAGESCALING_CONFIG()
          macro which configure VOS bit in PWR_CR register:
        (++) When this bit is set (Regulator voltage output Scale 1 mode selected)
             the System frequency can go up to 32 MHz.
        (++) When this bit is reset (Regulator voltage output Scale 2 mode selected)
             the System frequency can go up to 16 MHz.
        (++) When this bit is reset (Regulator voltage output Scale 3 mode selected)
             the System frequency can go up to 4.2 MHz.
              
        Refer to the datasheets for more details.

    *** Low Power modes configuration ***
    =====================================
     [..]
      The device features 5 low-power modes:
      (+) Low power run mode: regulator in low power mode, limited clock frequency, 
        limited number of peripherals running.
      (+) Sleep mode: Cortex-M3 core stopped, peripherals kept running.
      (+) Low power sleep mode: Cortex-M3 core stopped, limited clock frequency, 
         limited number of peripherals running, regulator in low power mode.
      (+) Stop mode: All clocks are stopped, regulator running, regulator in low power mode.
      (+) Standby mode: VCORE domain powered off
  
   *** Low power run mode ***
   =========================
    [..]
       To further reduce the consumption when the system is in Run mode, the regulator can be
        configured in low power mode. In this mode, the system frequency should not exceed
        MSI frequency range1.
        In Low power run mode, all I/O pins keep the same state as in Run mode.
  
      (+) Entry:
        (++) VCORE in range2
        (++) Decrease the system frequency tonot exceed the frequency of MSI frequency range1.
        (++) The regulator is forced in low power mode using the HAL_PWREx_EnableLowPowerRunMode()
             function.
      (+) Exit:
        (++) The regulator is forced in Main regulator mode using the HAL_PWREx_DisableLowPowerRunMode()
              function.
        (++) Increase the system frequency if needed.
  
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

   *** Low power sleep mode ***
   ============================
    [..]
      (+) Entry:
          The Low power sleep mode is entered by using the HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFx)
              functions with
          (++) PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
          (++) PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
       (+) The Flash memory can be switched off by using the control bits (SLEEP_PD in the FLASH_ACR register. 
             This reduces power consumption but increases the wake-up time.
         
      (+) Exit:
        (++) If the WFI instruction was used to enter Low power sleep mode, any peripheral interrupt
              acknowledged by the nested vectored interrupt controller (NVIC) can wake up the device
              from Low power sleep mode. If the WFE instruction was used to enter Low power sleep mode,
              the MCU exits Sleep mode as soon as an event occurs. 
                
   *** Stop mode ***
   =================
    [..]
      The Stop mode is based on the Cortex-M3 deepsleep mode combined with peripheral
      clock gating. The voltage regulator can be configured either in normal or low-power mode.
      In Stop mode, all clocks in the VCORE domain are stopped, the PLL, the MSI, the HSI and
      the HSE RC oscillators are disabled. Internal SRAM and register contents are preserved.
      To get the lowest consumption in Stop mode, the internal Flash memory also enters low
      power mode. When the Flash memory is in power-down mode, an additional startup delay is
      incurred when waking up from Stop mode.
      To minimize the consumption In Stop mode, VREFINT, the BOR, PVD, and temperature
      sensor can be switched off before entering Stop mode. They can be switched on again by
      software after exiting Stop mode using the ULP bit in the PWR_CR register.
      In Stop mode, all I/O pins keep the same state as in Run mode.

      (+) Entry:
           The Stop mode is entered using the HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI )
             function with:
          (++) Main regulator ON.
          (++) Low Power regulator ON.
          (++) PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
          (++) PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
      (+) Exit:
        (++) By issuing an interrupt or a wakeup event, the MSI RC oscillator is selected as system clock.

   *** Standby mode ***
   ====================
     [..]
      The Standby mode allows to achieve the lowest power consumption. It is based on the
      Cortex-M3 deepsleep mode, with the voltage regulator disabled. The VCORE domain is
      consequently powered off. The PLL, the MSI, the HSI oscillator and the HSE oscillator are
      also switched off. SRAM and register contents are lost except for the RTC registers, RTC
      backup registers and Standby circuitry.
      
      To minimize the consumption In Standby mode, VREFINT, the BOR, PVD, and temperature
       sensor can be switched off before entering the Standby mode. They can be switched 
       on again by software after exiting the Standby mode.
       function.
      
      (+) Entry:
        (++) The Standby mode is entered using the HAL_PWR_EnterSTANDBYMode() function.
      (+) Exit:
        (++) WKUP pin rising edge, RTC alarm (Alarm A and Alarm B), RTC wakeup,
             tamper event, time-stamp event, external reset in NRST pin, IWDG reset.

   *** Auto-wakeup (AWU) from low-power mode ***
   =============================================
    [..]
      The MCU can be woken up from low-power mode by an RTC Alarm event, an RTC 
      Wakeup event, a tamper event, a time-stamp event, or a comparator event, 
      without depending on an external interrupt (Auto-wakeup mode).

    (+) RTC auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to:
             (+++) Configure the EXTI Line 17 to be sensitive to rising edges (Interrupt 
                   or Event modes) and Enable the RTC Alarm Interrupt using the HAL_RTC_SetAlarm_IT()
                   function
             (+++) Configure the RTC to generate the RTC alarm using the HAL_RTC_Init() 
                   and HAL_RTC_SetTime() functions.
        (++) To wake up from the Stop mode with an RTC Tamper or time stamp event, it 
             is necessary to:
             (+++) Configure the EXTI Line 19 to be sensitive to rising edges (Interrupt or Event modes) and
                   Enable the RTC Tamper or time stamp Interrupt using the HAL_RTCEx_SetTamper_IT() 
                   or HAL_RTCEx_SetTimeStamp_IT() functions.
        (++) To wake up from the Stop mode with an RTC WakeUp event, it is necessary to:
             (+++) Configure the EXTI Line 20 to be sensitive to rising edges (Interrupt or Event modes) and
                   Enable the RTC WakeUp Interrupt using the HAL_RTCEx_SetWakeUpTimer_IT() function.
             (+++) Configure the RTC to generate the RTC WakeUp event using the HAL_RTCEx_SetWakeUpTimer() 
                   function.

    (+) RTC auto-wakeup (AWU) from the Standby mode
        (++) To wake up from the Standby mode with an RTC alarm event, it is necessary to:
             (+++) Enable the RTC Alarm Interrupt using the HAL_RTC_SetAlarm_IT() function.
             (+++) Configure the RTC to generate the RTC alarm using the HAL_RTC_Init() 
                   and HAL_RTC_SetTime() functions.
        (++) To wake up from the Standby mode with an RTC Tamper or time stamp event, it 
             is necessary to:
             (+++) Enable the RTC Tamper or time stamp Interrupt and Configure the RTC to 
                   detect the tamper or time stamp event using the HAL_RTCEx_SetTimeStamp_IT()
                   or HAL_RTCEx_SetTamper_IT()functions.
        (++) To wake up from the Standby mode with an RTC WakeUp event, it is necessary to:
             (+++) Enable the RTC WakeUp Interrupt and Configure the RTC to generate the RTC WakeUp event 
                   using the HAL_RTCEx_SetWakeUpTimer_IT() and HAL_RTCEx_SetWakeUpTimer() functions.

    (+) Comparator auto-wakeup (AWU) from the Stop mode
        (++) To wake up from the Stop mode with an comparator 1 or comparator 2 wakeup
             event, it is necessary to:
             (+++) Configure the EXTI Line 21 or EXTI Line 22 for comparator to be sensitive to to the 
                   selected edges (falling, rising or falling and rising) (Interrupt or Event modes) using 
                   the COMP functions.
             (+++) Configure the comparator to generate the event.      
        
            
        
@endverbatim
  * @{
  */

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  sConfigPVD: pointer to an PWR_PVDTypeDef structure that contains the configuration
  *         information for the PVD.
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void HAL_PWR_PVDConfig(PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Set PLS[7:5] bits according to PVDLevel value */
  MODIFY_REG(PWR->CR, PWR_CR_PLS, sConfigPVD->PVDLevel);
  
  /* Clear any previous config. Keep it clear if no event or IT mode is selected */
  __HAL_PWR_PVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_CLEAR_EGDE_TRIGGER();

  /* Configure interrupt mode */
  if((sConfigPVD->Mode & PVD_MODE_IT) == PVD_MODE_IT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_IT();
  }
  
  /* Configure event mode */
  if((sConfigPVD->Mode & PVD_MODE_EVT) == PVD_MODE_EVT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_EVENT();
  }
  
  /* Configure the edge */
  if((sConfigPVD->Mode & PVD_RISING_EDGE) == PVD_RISING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_SET_RISING_EDGE_TRIGGER();
  }
  
  if((sConfigPVD->Mode & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_SET_FALLING_EGDE_TRIGGER();
  }
}

/**
  * @brief  Enables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_EnablePVD(void)
{
  /* Enable the power voltage detector */
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)ENABLE;
}

/**
  * @brief  Disables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_DisablePVD(void)
{
  /* Disable the power voltage detector */
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)DISABLE;
}

/**
  * @brief Enables the WakeUp PINx functionality.
  * @param WakeUpPinx: Specifies the Power Wake-Up pin to enable.
  *        This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN1
  *           @arg PWR_WAKEUP_PIN2
  *           @arg PWR_WAKEUP_PIN3: Only on product with GPIOE available 
  * @retval None
  */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinx)
{
  /* Check the parameter */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinx));
  /* Enable the EWUPx pin */
  *(__IO uint32_t *) CSR_EWUP_BB(WakeUpPinx) = (uint32_t)ENABLE;
}

/**
  * @brief Disables the WakeUp PINx functionality.
  * @param WakeUpPinx: Specifies the Power Wake-Up pin to disable.
  *        This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN1
  *           @arg PWR_WAKEUP_PIN2  
  *           @arg PWR_WAKEUP_PIN3: Only on product with GPIOE available 
  * @retval None
  */
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx)
{
  /* Check the parameter */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinx));
  /* Disable the EWUPx pin */
  *(__IO uint32_t *) CSR_EWUP_BB(WakeUpPinx) = (uint32_t)DISABLE;
}

/**
  * @brief Enters Sleep mode.
  * @note  In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param Regulator: Specifies the regulator state in SLEEP mode.
  *         This parameter can be one of the following values:
  *            @arg PWR_MAINREGULATOR_ON: SLEEP mode with regulator ON
  *            @arg PWR_LOWPOWERREGULATOR_ON: SLEEP mode with low power regulator ON
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

  /* Select the regulator state in Sleep mode: Set PDDS and LPSDSR bit according to PWR_Regulator value */
  MODIFY_REG(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPSDSR), Regulator);

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

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
  * @brief Enters Stop mode. 
  * @note  In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note  When exiting Stop mode by using an interrupt or a wakeup event,
  *        MSI RC oscillator is selected as system clock.
  * @note  When the voltage regulator operates in low power mode, an additional
  *         startup delay is incurred when waking up from Stop mode. 
  *         By keeping the internal regulator ON during Stop mode, the consumption
  *         is higher although the startup time is reduced.    
  * @param Regulator: Specifies the regulator state in Stop mode.
  *          This parameter can be one of the following values:
  *            @arg PWR_MAINREGULATOR_ON: Stop mode with regulator ON
  *            @arg PWR_LOWPOWERREGULATOR_ON: Stop mode with low power regulator ON
  * @param STOPEntry: Specifies if Stop mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg PWR_STOPENTRY_WFI: Enter Stop mode with WFI instruction
  *            @arg PWR_STOPENTRY_WFE: Enter Stop mode with WFE instruction   
  * @retval None
  */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(Regulator));
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Select the regulator state in Stop mode: Set PDDS and LPSDSR bit according to PWR_Regulator value */
  MODIFY_REG(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPSDSR), Regulator);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry --------------------------------------------------*/
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
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief Enters Standby mode.
  * @note  In Standby mode, all I/O pins are high impedance except for:
  *          - Reset pad (still available) 
  *          - RTC_AF1 pin (PC13) if configured for tamper, time-stamp, RTC
  *            Alarm out, or RTC clock calibration out.
  *          - WKUP pin 1 (PA0) if enabled.
  *          - WKUP pin 2 (PC13) if enabled.
  *          - WKUP pin 3 (PE6) if enabled.
  * @retval None
  */
void HAL_PWR_EnterSTANDBYMode(void)
{
  /* Select Standby mode */
  SET_BIT(PWR->CR, PWR_CR_PDDS);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
  __force_stores();
#endif
  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_IRQHandler().
  * @retval None
  */
void HAL_PWR_PVD_IRQHandler(void)
{
  /* Check PWR exti flag */
  if(__HAL_PWR_PVD_EXTI_GET_FLAG() != RESET)
  {
    /* PWR PVD interrupt user callback */
    HAL_PWR_PVDCallback();

    /* Clear PWR Exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_FLAG();
  }
}

/**
  * @brief  PWR PVD interrupt callback
  * @retval None
  */
__weak void HAL_PWR_PVDCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWR_PVDCallback could be implemented in the user file
   */ 
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
