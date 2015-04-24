/**
  ******************************************************************************
  * @file    stm32l1xx_hal.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
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
    The HAL contains two APIs' categories: 
         (+) Common HAL APIs
         (+) Services HAL APIs

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

/** @defgroup HAL HAL
  * @brief HAL module driver.
  * @{
  */

#ifdef HAL_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup HAL_Private_Defines HAL Private Defines
  * @{
  */

/**
 * @brief STM32L1xx HAL Driver version number V1.0.0
   */
#define __STM32L1xx_HAL_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32L1xx_HAL_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32L1xx_HAL_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32L1xx_HAL_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32L1xx_HAL_VERSION         ((__STM32L1xx_HAL_VERSION_MAIN << 24)\
                                        |(__STM32L1xx_HAL_VERSION_SUB1 << 16)\
                                        |(__STM32L1xx_HAL_VERSION_SUB2 << 8 )\
                                        |(__STM32L1xx_HAL_VERSION_RC))

#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup HAL_Private_Variables HAL Private Variables
  * @{
  */

static __IO uint32_t uwTick;

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */

/** @defgroup HAL_Exported_Functions_Group1 Initialization and de-initialization Functions 
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
       (++) functions affecting time base configurations are declared as __Weak  
             to make  override possible  in case of other  implementations in user file.
 
@endverbatim
  * @{
  */

/**
  * @brief This function configures the Flash prefetch, 
  *        Configures time base source, NVIC and Low level hardware
  * @note This function is called at the beginning of program after reset and before 
  *       the clock configuration
  * @note The time base configuration is based on MSI clock when exiting from Reset.
  *       Once done, time base tick start incrementing.
  *        In the default implementation,Systick is used as source of time base.
  *        the tick variable is incremented each 1ms in its ISR.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_Init(void)
{
  /* Configure Flash prefetch */
#if (PREFETCH_ENABLE != 0)
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif /* PREFETCH_ENABLE */

  /* Set Interrupt Group Priority */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

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
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DeInit(void)
{
  /* Reset of all peripherals */
  __APB1_FORCE_RESET();
  __APB1_RELEASE_RESET();

  __APB2_FORCE_RESET();
  __APB2_RELEASE_RESET();

  __AHB_FORCE_RESET();
  __AHB_RELEASE_RESET();

  /* De-Init the low level hardware */
  HAL_MspDeInit();
    
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the MSP.
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

/** @defgroup HAL_Exported_Functions_Group2 HAL Control functions 
 *  @brief    HAL Control functions
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
      (+) Enable/Disable Debug module during Sleep mode
      (+) Enable/Disable Debug module during STOP mode
      (+) Enable/Disable Debug module during STANDBY mode
      
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
  * @retval tick value
  */
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function provides accurate delay (in milliseconds) based 
  *        on variable incremented.
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
  * @retval None
  */
__weak void HAL_SuspendTick(void)
{
  /* Disable SysTick Interrupt */
  CLEAR_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the the SysTick interrupt will be enabled and so Tick increment 
  *       is resumed.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void HAL_ResumeTick(void)
{
  /* Enable SysTick Interrupt */
  SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief Returns the HAL revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t HAL_GetHalVersion(void)
{
 return __STM32L1xx_HAL_VERSION;
}

/**
  * @brief Returns the device revision identifier.
  * @retval Device revision identifier
  */
uint32_t HAL_GetREVID(void)
{
  return((DBGMCU->IDCODE) >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @retval Device identifier
  */
uint32_t HAL_GetDEVID(void)
{
   return((DBGMCU->IDCODE) & IDCODE_DEVID_MASK);
}

/**
  * @brief  Enable the Debug Module during SLEEP mode
  * @retval None
  */
void HAL_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode
  * @retval None
  */
void HAL_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @retval None
  */
void HAL_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @retval None
  */
void HAL_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode
  * @retval None
  */
void HAL_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode
  * @retval None
  */
void HAL_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
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
