/**
  ******************************************************************************
  * @file    stm32l1xx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Extended Initialization and de-initialization functions
  *           + Extended Peripheral Control functions
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

/** @defgroup PWREx PWREx
  * @brief    PWR HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWREx_Exported_Functions PWREx Exported Functions
  * @{
  */

/** @defgroup PWREx_Exported_Functions_Group1 Peripheral Extended Features Functions
  * @brief    Low Power modes configuration functions
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
  * @note   This bit works in conjunction with ULP bit. 
  *         Means, when ULP = 1 and FWU = 1 :VREFINT startup time is ignored when 
  *         exiting from low power mode.
  * @retval None
  */
void HAL_PWREx_EnableFastWakeUp(void)
{
  /* Enable the fast wake up */
  *(__IO uint32_t *) CR_FWU_BB = (uint32_t)ENABLE;
}

/**
  * @brief  Disables the Fast WakeUp from Ultra Low Power mode.
  * @retval None
  */
void HAL_PWREx_DisableFastWakeUp(void)
{
  /* Disable the fast wake up */
  *(__IO uint32_t *) CR_FWU_BB = (uint32_t)DISABLE;
}

/**
  * @brief  Enables the Ultra Low Power mode
  * @retval None
  */
void HAL_PWREx_EnableUltraLowPower(void)
{
  /* Enable the Ultra Low Power mode */
  *(__IO uint32_t *) CR_ULP_BB = (uint32_t)ENABLE;
}

/**
  * @brief  Disables the Ultra Low Power mode
  * @retval None
  */
void HAL_PWREx_DisableUltraLowPower(void)
{
  /* Disable the Ultra Low Power mode */
  *(__IO uint32_t *) CR_ULP_BB = (uint32_t)DISABLE;
}

/**
  * @brief  Enters the Low Power Run mode.
  * @note   Low power run mode can only be entered when VCORE is in range 2.
  *         In addition, the dynamic voltage scaling must not be used when Low
  *         power run mode is selected. Only Stop and Sleep modes with regulator
  *         configured in Low power mode is allowed when Low power run mode is 
  *         selected.
  * @note   In Low power run mode, all I/O pins keep the same state as in Run mode.
  * @retval None
  */
void HAL_PWREx_EnableLowPowerRunMode(void)
{
  /* Enters the Low Power Run mode */
  *(__IO uint32_t *) CR_LPSDSR_BB = (uint32_t)ENABLE;
  *(__IO uint32_t *) CR_LPRUN_BB  = (uint32_t)ENABLE;
}

/**
  * @brief  Exits the Low Power Run mode.
  * @retval None
  */
void HAL_PWREx_DisableLowPowerRunMode(void)
{
  /* Exits the Low Power Run mode */
  *(__IO uint32_t *) CR_LPRUN_BB  = (uint32_t)DISABLE;
  *(__IO uint32_t *) CR_LPSDSR_BB = (uint32_t)DISABLE;
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
