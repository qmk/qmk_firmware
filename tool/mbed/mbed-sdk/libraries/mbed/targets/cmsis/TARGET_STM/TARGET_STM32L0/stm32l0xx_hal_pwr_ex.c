/**
  ******************************************************************************
  * @file    stm32l0xx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Extended Initialization and de-initialization functions
  *           + Extended Peripheral Control functions
  *         
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

#ifdef HAL_PWR_MODULE_ENABLED
/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx 
  * @{
  */

/** @defgroup PWR_Extended_TimeOut_Value PWR Extended Flag Setting Time Out Value
  * @{
  */ 
#define PWR_FLAG_SETTING_DELAY_US   50
/**
  * @}
  */


/** @addtogroup PWREx_Exported_Functions
  * @brief      Low Power modes configuration functions 
  *
@verbatim

 ===============================================================================
                 ##### Peripheral extended features functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
  * @brief  Enables the Fast WakeUp from Ultra Low Power mode.
  * @note This bit works in conjunction with ULP bit. 
  *        Means, when ULP = 1 and FWU = 1 :VREFINT startup time is ignored when 
  *        exiting from low power mode.
  * @retval None
  */
void HAL_PWREx_EnableFastWakeUp(void)
{
  /* Enable the fast wake up */
  SET_BIT(PWR->CR, PWR_CR_FWU);
}

/**
  * @brief  Disables the Fast WakeUp from Ultra Low Power mode.
  * @retval None
  */
void HAL_PWREx_DisableFastWakeUp(void)
{
  /* Disable the fast wake up */
  CLEAR_BIT(PWR->CR, PWR_CR_FWU);
}

/**
  * @brief  Enables the Ultra Low Power mode
  * @retval None
  */
void HAL_PWREx_EnableUltraLowPower(void)
{
  /* Enable the Ultra Low Power mode */
  SET_BIT(PWR->CR, PWR_CR_ULP);
}

/**
  * @brief  Disables the Ultra Low Power mode
  * @retval None
  */
void HAL_PWREx_DisableUltraLowPower(void)
{
  /* Disable the Ultra Low Power mode */
  CLEAR_BIT(PWR->CR, PWR_CR_ULP);
}

/**
  * @brief  Enable the Low Power Run mode.
  * @note   Low power run mode can only be entered when VCORE is in range 2.
  *         In addition, the dynamic voltage scaling must not be used when Low
  *         power run mode is selected. Only Stop and Sleep modes with regulator
  *         configured in Low power mode is allowed when Low power run mode is 
  *         selected.
  * @note   The frequency of the system clock must be decreased to not exceed the
  *         frequency of RCC_MSIRANGE_1.
  * @note   In Low power run mode, all I/O pins keep the same state as in Run mode.
  * @retval None
  */
void HAL_PWREx_EnableLowPowerRunMode(void)
{
  /* Enters the Low Power Run mode */
  SET_BIT(PWR->CR, PWR_CR_LPSDSR);
  SET_BIT(PWR->CR, PWR_CR_LPRUN);
}

/**
  * @brief  Disable the Low Power Run mode.
  * @note  Before HAL_PWREx_DisableLowPowerRunMode() completion, the function checks that 
  *        REGLPF has been properly reset (otherwise, HAL_PWREx_DisableLowPowerRunMode 
  *        returns HAL_TIMEOUT status). The system clock frequency can then be
  *        increased above 2 MHz.   
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void)
{
  uint32_t wait_loop_index = 0;
  
  /* Exit the Low Power Run mode */
  CLEAR_BIT(PWR->CR, PWR_CR_LPRUN);
  CLEAR_BIT(PWR->CR, PWR_CR_LPSDSR);
  
  /* Wait until REGLPF is reset */
  wait_loop_index = (PWR_FLAG_SETTING_DELAY_US * (SystemCoreClock / 1000000));

  while ((wait_loop_index != 0) && (HAL_IS_BIT_SET(PWR->CSR, PWR_CSR_REGLPF)))
  {
    wait_loop_index--;
  }

  if (HAL_IS_BIT_SET(PWR->CSR, PWR_CSR_REGLPF))
  {
    return HAL_TIMEOUT;
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
#endif /* HAL_PWR_MODULE_ENABLED */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

