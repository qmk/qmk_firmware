/**
  ******************************************************************************
  * @file    stm32f1xx_hal_pwr.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief    PWR HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */
  
/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */ 
#define PVD_MODE_IT               ((uint32_t)0x00010000)
#define PVD_MODE_EVT              ((uint32_t)0x00020000)
#define PVD_RISING_EDGE           ((uint32_t)0x00000001)
#define PVD_FALLING_EDGE          ((uint32_t)0x00000002)
/**
  * @}
  */


/** @defgroup PWR_register_alias_address PWR Register alias address
  * @{
  */ 
/* ------------- PWR registers bit address in the alias region ---------------*/
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)
#define PWR_CR_OFFSET            0x00
#define PWR_CSR_OFFSET           0x04
#define PWR_CR_OFFSET_BB         (PWR_OFFSET + PWR_CR_OFFSET)
#define PWR_CSR_OFFSET_BB        (PWR_OFFSET + PWR_CSR_OFFSET)
/**
  * @}
  */
   
/** @defgroup PWR_CR_register_alias PWR CR Register alias address
  * @{
  */  
/* --- CR Register ---*/
/* Alias word address of LPSDSR bit */
#define LPSDSR_BIT_NUMBER        POSITION_VAL(PWR_CR_LPDS)
#define CR_LPSDSR_BB             ((uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32) + (LPSDSR_BIT_NUMBER * 4)))

/* Alias word address of DBP bit */
#define DBP_BIT_NUMBER            POSITION_VAL(PWR_CR_DBP)
#define CR_DBP_BB                ((uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32) + (DBP_BIT_NUMBER * 4)))

/* Alias word address of PVDE bit */
#define PVDE_BIT_NUMBER           POSITION_VAL(PWR_CR_PVDE)
#define CR_PVDE_BB               ((uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32) + (PVDE_BIT_NUMBER * 4)))

/**
  * @}
  */

/** @defgroup PWR_CSR_register_alias PWR CSR Register alias address
  * @{
  */

/* --- CSR Register ---*/
/* Alias word address of EWUP1 bit */
#define CSR_EWUP_BB(VAL)         ((uint32_t)(PERIPH_BB_BASE + (PWR_CSR_OFFSET_BB * 32) + (POSITION_VAL(VAL) * 4)))
/**
  * @}
  */
  
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup PWR_Private_Functions PWR Private Functions
 * brief   WFE cortex command overloaded for HAL_PWR_EnterSTOPMode usage only (see Workaround section)
 * @{
 */
static void PWR_OverloadWfe(void);

/* Private functions ---------------------------------------------------------*/
__NOINLINE
static void PWR_OverloadWfe(void)
{
  __asm volatile( "wfe" );
  __asm volatile( "nop" );
}

/**
  * @}
  */


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
            __HAL_RCC_PWR_CLK_ENABLE() macro.
        (+) Enable access to RTC domain using the HAL_PWR_EnableBkUpAccess() function.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.  
  * @retval None
  */
void HAL_PWR_DeInit(void)
{
  __HAL_RCC_PWR_FORCE_RESET();
  __HAL_RCC_PWR_RELEASE_RESET();
}

/**
  * @brief  Enables access to the backup domain (RTC registers, RTC
  *         backup data registers ).
  * @note   If the HSE divided by 128 is used as the RTC clock, the
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
  * @note   If the HSE divided by 128 is used as the RTC clock, the
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
      (+) There is one WakeUp pin:
          WakeUp Pin 1 on PA.00.

    [..]

    *** Low Power modes configuration ***
    =====================================
     [..]
      The device features 3 low-power modes:
      (+) Sleep mode: CPU clock off, all peripherals including Cortex-M3 core peripherals like 
                      NVIC, SysTick, etc. are kept running
      (+) Stop mode: All clocks are stopped
      (+) Standby mode: 1.8V domain powered off
  
  
   *** Sleep mode ***
   ==================
    [..]
      (+) Entry:
          The Sleep mode is entered by using the HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFx)
              functions with
          (++) PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
          (++) PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
     
      (+) Exit:
        (++) WFI entry mode, Any peripheral interrupt acknowledged by the nested vectored interrupt
             controller (NVIC) can wake up the device from Sleep mode.
        (++) WFE entry mode, Any wakeup event can wake up the device from Sleep mode.
           (+++) Any peripheral interrupt w/o NVIC configuration & SEVONPEND bit set in the Cortex (HAL_PWR_EnableSEVOnPend)
           (+++) Any EXTI Line (Internal or External) configured in Event mode

   *** Stop mode ***
   =================
    [..]
      The Stop mode is based on the Cortex-M3 deepsleep mode combined with peripheral
      clock gating. The voltage regulator can be configured either in normal or low-power mode.
      In Stop mode, all clocks in the 1.8 V domain are stopped, the PLL, the HSI and the HSE RC 
      oscillators are disabled. SRAM and register contents are preserved.
      In Stop mode, all I/O pins keep the same state as in Run mode.

      (+) Entry:
           The Stop mode is entered using the HAL_PWR_EnterSTOPMode(PWR_REGULATOR_VALUE, PWR_SLEEPENTRY_WFx )
             function with:
          (++) PWR_REGULATOR_VALUE= PWR_MAINREGULATOR_ON: Main regulator ON.
          (++) PWR_REGULATOR_VALUE= PWR_LOWPOWERREGULATOR_ON: Low Power regulator ON.
          (++) PWR_SLEEPENTRY_WFx= PWR_SLEEPENTRY_WFI: enter STOP mode with WFI instruction
          (++) PWR_SLEEPENTRY_WFx= PWR_SLEEPENTRY_WFE: enter STOP mode with WFE instruction
      (+) Exit:
          (++) WFI entry mode, Any EXTI Line (Internal or External) configured in Interrupt mode with NVIC configured
          (++) WFE entry mode, Any EXTI Line (Internal or External) configured in Event mode.

   *** Standby mode ***
   ====================
     [..]
      The Standby mode allows to achieve the lowest power consumption. It is based on the
      Cortex-M3 deepsleep mode, with the voltage regulator disabled. The 1.8 V domain is 
      consequently powered off. The PLL, the HSI oscillator and the HSE oscillator are also 
      switched off. SRAM and register contents are lost except for registers in the Backup domain 
      and Standby circuitry
      
      (+) Entry:
        (++) The Standby mode is entered using the HAL_PWR_EnterSTANDBYMode() function.
      (+) Exit:
        (++) WKUP pin rising edge, RTC alarm event rising edge, external Reset in 
             NRSTpin, IWDG Reset

   *** Auto-wakeup (AWU) from low-power mode ***
       =============================================
       [..]
        
       (+) The MCU can be woken up from low-power mode by an RTC Alarm event, 
           without depending on an external interrupt (Auto-wakeup mode).
   
       (+) RTC auto-wakeup (AWU) from the Stop and Standby modes

           (++) To wake up from the Stop mode with an RTC alarm event, it is necessary to 
                configure the RTC to generate the RTC alarm using the HAL_RTC_SetAlarm_IT() function.

   *** PWR Workarounds linked to Silicon Limitation ***
       ====================================================
       [..]
       Below the list of all silicon limitations known on STM32F1xx prouct.

       (#)Workarounds Implemented inside PWR HAL Driver
          (##)Debugging Stop mode with WFE entry - overloaded the WFE by an internal function    
        
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
void HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Set PLS[7:5] bits according to PVDLevel value */
  MODIFY_REG(PWR->CR, PWR_CR_PLS, sConfigPVD->PVDLevel);
  
  /* Clear any previous config. Keep it clear if no event or IT mode is selected */
  __HAL_PWR_PVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE(); 
  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();

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
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();
  }
  
  if((sConfigPVD->Mode & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();
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
  * @param Regulator: Regulator state as no effect in SLEEP mode -  allows to support portability from legacy software
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
  /* No check on Regulator because parameter not used in SLEEP mode */
  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

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
  *        HSI RC oscillator is selected as system clock.
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

  /* Clear PDDS bit in PWR register to specify entering in STOP mode when CPU enter in Deepsleep */ 
  CLEAR_BIT(PWR->CR,  PWR_CR_PDDS);

  /* Select the voltage regulator mode by setting LPDS bit in PWR register according to Regulator parameter value */
  MODIFY_REG(PWR->CR, PWR_CR_LPDS, Regulator);

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
    PWR_OverloadWfe(); /* WFE redefine locally */
    PWR_OverloadWfe(); /* WFE redefine locally */
  }
  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief Enters Standby mode.
  * @note  In Standby mode, all I/O pins are high impedance except for:
  *          - Reset pad (still available) 
  *          - TAMPER pin if configured for tamper or calibration out.
  *          - WKUP pin (PA0) if enabled.
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
  * @brief Enables CORTEX M3 SEVONPEND bit. 
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
  * @brief Disables CORTEX M3 SEVONPEND bit. 
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
