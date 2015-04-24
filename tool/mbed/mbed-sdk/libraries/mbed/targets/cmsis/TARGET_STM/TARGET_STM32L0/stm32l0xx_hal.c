/**
  ******************************************************************************
  * @file    stm32l0xx_hal.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   HAL module driver.
  *          This is the common part of the HAL initialization
  *
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The common HAL driver contains a set of generic and common APIs that can be
    used by the PPP peripheral drivers and the user to start using the HAL. 
    [..]
    The HAL contains two APIs categories: 
         (+) Common HAL APIs
         (+) Services HAL APIs

  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addgroup HAL 
  * @brief HAL module driver.
  * @{
  */
#ifdef HAL_MODULE_ENABLED


/** @addtogroup HAL_Exported_Constants
  *
  * @{
  */

/** @defgroup HAL_Version HAL Version
  * @{
  */
#define SYSCFG_BOOT_MAINFLASH          ((uint32_t)0x00000000)
#define SYSCFG_BOOT_SYSTEMFLASH        ((uint32_t)SYSCFG_CFGR1_MEM_MODE_0)
#define SYSCFG_BOOT_SRAM               ((uint32_t)SYSCFG_CFGR1_BOOT_MODE)     


#define HAL_TIMEOUT_DMA_ABORT    ((uint32_t)1000)  /* 1s  */

/**
 * @brief STM32L0xx HAL Driver version number V1.2.0
   */
#define __STM32L0xx_HAL_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32L0xx_HAL_VERSION_SUB1   (0x02) /*!< [23:16] sub1 version */
#define __STM32L0xx_HAL_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32L0xx_HAL_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32L0xx_HAL_VERSION         ((__STM32L0xx_HAL_VERSION_MAIN << 24)\
                                        |(__STM32L0xx_HAL_VERSION_SUB1 << 16)\
                                        |(__STM32L0xx_HAL_VERSION_SUB2 << 8 )\
                                        |(__STM32L0xx_HAL_VERSION_RC))

#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)

/**
  * @}
  */ 
  
/**
  * @}
  */
/** @defgroup HAL_Private_Data
  * @{
  */ 
static __IO uint32_t uwTick;

/**
  * @}
  */ 

/** @addtogroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1 Initialization and de-initialization Functions 
 *  @brief    Initialization and de-initialization functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
   [..]  This section provides functions allowing to:
      (+) Initializes the Flash interface, the NVIC allocation and initial clock 
          configuration. It initializes the source of time base also when timeout 
          is needed and the backup domain when enabled.
      (+) de-Initializes common part of the HAL.
      (+) Configure The time base source to have 1ms time base with a dedicated 
          Tick interrupt priority. 
        (++) Systick timer is used by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
        (++) Time base configuration function (HAL_InitTick ()) is called automatically 
             at the beginning of the program after reset by HAL_Init() or at any time 
             when clock is configured, by HAL_RCC_ClockConfig(). 
        (++) Source of time base is configured  to generate interrupts at regular 
             time intervals. Care must be taken if HAL_Delay() is called from a 
             peripheral ISR process, the Tick interrupt line must have higher priority 
            (numerically lower) than the peripheral interrupt. Otherwise the caller 
            ISR process will be blocked. 
       (++) functions affecting time base configurations are declared as __weak  
             to make  override possible  in case of other  implementations in user file.
 
@endverbatim
  * @{
  */

/**
  * @brief This function configures the Flash prefetch, Flash preread and Buffer cache,
  *        Configures time base source, NVIC and Low level hardware
  * @note This function is called at the beginning of program after reset and before 
  *       the clock configuration
  * @note The time base configuration is based on MSI clock when exiting from Reset.
  *       Once done, time base tick start incrementing.
  *        In the default implementation,Systick is used as source of time base.
  *        the tick variable is incremented each 1ms in its ISR.
  * @param None
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_Init(void)
{
  /* Configure Buffer cache, Flash prefetch,  Flash preread */ 
#if (BUFFER_CACHE_DISABLE != 0)
  __HAL_FLASH_BUFFER_CACHE_DISABLE();
#endif /* BUFFER_CACHE_DISABLE */

#if (PREREAD_ENABLE != 0)
  __HAL_FLASH_PREREAD_BUFFER_ENABLE();
#endif /* PREREAD_ENABLE */

#if (PREFETCH_ENABLE != 0)
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif /* PREFETCH_ENABLE */

  /* Use systick as time base source and configure 1ms tick (default clock after Reset is MSI) */

  HAL_InitTick(TICK_INT_PRIORITY);

  /* Init the low level hardware */
  HAL_MspInit();

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief This function de-Initializes common part of the HAL and stops the source
  *        of time base.
  * @note This function is optional.
  * @param None
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DeInit(void)
{
  /* Reset of all peripherals */
  __HAL_RCC_APB1_FORCE_RESET();
  __HAL_RCC_APB1_RELEASE_RESET();

  __HAL_RCC_APB2_FORCE_RESET();
  __HAL_RCC_APB2_RELEASE_RESET();

  __HAL_RCC_AHB_FORCE_RESET();
  __HAL_RCC_AHB_RELEASE_RESET();

  __HAL_RCC_IOP_FORCE_RESET();
  __HAL_RCC_IOP_RELEASE_RESET();

  /* De-Init the low level hardware */
  HAL_MspDeInit();
    
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the MSP.
  * @param  None
  * @retval None
  */
__weak void HAL_MspInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes the MSP.
  * @param  None  
  * @retval None
  */
__weak void HAL_MspDeInit(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_MspDeInit could be implemented in the user file
   */
}


/**
  * @brief This function configures the source of the time base. 
  *        The time source is configured  to have 1ms time base with a dedicated 
  *        Tick interrupt priority.
  * @note This function is called  automatically at the beginning of program after
  *       reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig(). 
  * @note In the default implementation, SysTick timer is the source of time base. 
  *       It is used to generate interrupts at regular time intervals. 
  *       Care must be taken if HAL_Delay() is called from a peripheral ISR process, 
  *       The the SysTick interrupt must have higher priority (numerically lower) 
  *       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *       The function is declared as __Weak  to be overwritten  in case of other
  *       implementation  in user file.
  * @param TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  /*Configure the SysTick to have interrupt in 1ms time basis*/
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  /*Configure the SysTick IRQ priority */
  HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority ,0);

   /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2 
 *  @brief    Peripheral Control functions
 *
@verbatim
 ===============================================================================
                      ##### HAL Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Provide a tick value in millisecond
      (+) Provide a blocking delay in millisecond
      (+) Suspend the time base source interrupt
      (+) Resume the time base source interrupt
      (+) Get the HAL API driver version
      (+) Get the device identifier
      (+) Get the device revision identifier
      (+) Configures low power mode behavior when the MCU is in Debug mode
      (+) Manages the VEREFINT feature (activation, lock, output selection)
      
@endverbatim
  * @{
  */

/**
  * @brief This function is called to increment  a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in Systick ISR.
 * @note This function is declared as __weak to be overwritten in case of other 
  *      implementations in user file.
  * @param None
  * @retval None
  */
__weak void HAL_IncTick(void)
{
  uwTick++;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note This function is declared as __weak to be overwritten in case of other 
  *       implementations in user file.
  * @param None
  * @retval tick value
  */
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function provides accurate delay (in ms) based on a variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note ThiS function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay: specifies the delay time length, in milliseconds.
  * @retval None
  */
__weak void HAL_Delay(__IO uint32_t Delay)
{
  uint32_t tickstart = 0;
  tickstart = HAL_GetTick();
  while((HAL_GetTick() - tickstart) < Delay)
  {
  }
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the the SysTick interrupt will be disabled and so Tick increment 
  *       is suspended.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param None
  * @retval None
  */
__weak void HAL_SuspendTick(void)
{
  /* Disable SysTick Interrupt */
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the the SysTick interrupt will be enabled and so Tick increment 
  *       is resumed.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param None
  * @retval None
  */
__weak void HAL_ResumeTick(void)
{
  /* Enable SysTick Interrupt */
  SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief Returns the HAL revision
  * @param None
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t HAL_GetHalVersion(void)
{
  return __STM32L0xx_HAL_VERSION;
}

/**
  * @brief Returns the device revision identifier.
  * @param None
  * @retval Device revision identifier
  */
uint32_t HAL_GetREVID(void)
{
  return((DBGMCU->IDCODE) >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @param  None
  * @retval Device identifier
  */
uint32_t HAL_GetDEVID(void)
{
   return((DBGMCU->IDCODE) & IDCODE_DEVID_MASK);
}

/**
  * @brief  Enable the Debug Module during SLEEP mode
  * @param  None
  * @retval None
  */
void HAL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode
  * @param  None
  * @retval None
  */
void HAL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @param  None
  * @retval None
  */
void HAL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @param  None
  * @retval None
  */
void HAL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode
  * @param  None
  * @retval None
  */
void HAL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode
  * @param  None
  * @retval None
  */
void HAL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Enable low power mode behavior when the MCU is in Debug mode.
  * @param Periph: specifies the low power mode.
  *   This parameter can be any combination of the following values:
  *     @arg DBGMCU_SLEEP: Keep debugger connection during SLEEP mode
  *     @arg DBGMCU_STOP: Keep debugger connection during STOP mode
  *     @arg DBGMCU_STANDBY: Keep debugger connection during STANDBY mode
  * @retval None
  */
void HAL_DBGMCU_DBG_EnableLowPowerConfig(uint32_t Periph)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_PERIPH(Periph));
  
  DBGMCU->CR |= Periph;

}
/**
  * @brief  Disable low power mode behavior when the MCU is in Debug mode.
  * @param Periph: specifies the low power mode.
  *   This parameter can be any combination of the following values:
  *     @arg DBGMCU_SLEEP: Keep debugger connection during SLEEP mode
  *     @arg DBGMCU_STOP: Keep debugger connection during STOP mode
  *     @arg DBGMCU_STANDBY: Keep debugger connection during STANDBY mode
  * @retval None
  */
void HAL_DBGMCU_DBG_DisableLowPowerConfig(uint32_t Periph)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_PERIPH(Periph));
  {
    DBGMCU->CR &= ~Periph;
  }
}

/**
  * @brief  Returns the boot mode as configured by user.
  * @param  None.
  * @retval The boot mode as configured by user. The returned value can be one 
  *         of the following values:
  *              - 0x00000000: Boot is configured in Main Flash memory
  *              - 0x00000100: Boot is configured in System Flash memory
  *              - 0x00000300: Boot is configured in Embedded SRAM memory
  */
uint32_t  HAL_SYSCFG_GetBootMode(void)
{
  return (SYSCFG->CFGR1 & SYSCFG_CFGR1_BOOT_MODE);
}

/**
  * @brief Enables the VREFINT.
  * @param None
  * @retval None
  */
void HAL_SYSCFG_EnableVREFINT(void)
{
    /* Enable the VREFINT by setting EN_VREFINT bit in the CFGR3 register */
    SET_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_EN_VREFINT);
}

/**
  * @brief Disables the VREFINT.
  * @param None.
  * @retval None
  */
void HAL_SYSCFG_DisableVREFINT(void)
{
    /* Disable the VREFINT by setting EN_VREFINT bit in the CFGR3 register */
    CLEAR_BIT(SYSCFG->CFGR3,SYSCFG_CFGR3_EN_VREFINT); 
}
/**
  * @brief Selects the output of internal reference voltage (VREFINT).
  *        The VREFINT output can be routed to(PB0) or
  *        (PB1) or both.
  * @note   Kept for backward compatibility
  *         We recommend to use the MACRO 
  *         __HAL_SYSCFG_VREFINT_OUTPUT_SELECT(__VREFINT_OUTPUT__)
  *         rather than this function
  * @param SYSCFG_Vrefint_OUTPUT: new state of the Vrefint output.
  *        This parameter can be one of the following values:
  *     @arg SYSCFG_VREFINT_OUT_NONE
  *     @arg SYSCFG_VREFINT_OUT_PB0
  *     @arg SYSCFG_VREFINT_OUT_PB1
  *     @arg SYSCFG_VREFINT_OUT_PB0_PB1
  * @retval None
  */
void HAL_SYSCFG_VREFINT_OutputSelect(uint32_t SYSCFG_Vrefint_OUTPUT)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_VREFINT_OUT_SELECT(SYSCFG_Vrefint_OUTPUT));

  /* Set the output Vrefint pin */
  SYSCFG->CFGR3 &= ~(SYSCFG_CFGR3_VREF_OUT);
  SYSCFG->CFGR3 |= (uint32_t)(SYSCFG_Vrefint_OUTPUT);
}

/**
  * @brief  Lock the SYSCFG VREF register values
  * @retval None
  */
void HAL_SYSCFG_Enable_Lock_VREFINT(void)
{
    /* Enable the LOCK by setting REF_LOCK bit in the CFGR3 register */
    SET_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_REF_LOCK);
}

/**
  * @brief  Unlock the overall SYSCFG VREF register values
  * @retval None
  */
void HAL_SYSCFG_Disable_Lock_VREFINT(void)
{
    /* Disable the LOCK by setting REF_LOCK bit in the CFGR3 register */
    CLEAR_BIT(SYSCFG->CFGR3, SYSCFG_CFGR3_REF_LOCK);
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

