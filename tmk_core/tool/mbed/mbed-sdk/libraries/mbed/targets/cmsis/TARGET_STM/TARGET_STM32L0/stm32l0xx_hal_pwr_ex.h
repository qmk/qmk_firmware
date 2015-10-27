/**
  ******************************************************************************
  * @file    stm32l0xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of PWR HAL Extension module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_HAL_PWR_EX_H
#define __STM32L0xx_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWR extented module
  * @{
  */

/** @defgroup PWREx_Exported_Macros PWRex exported macros
 * @{
 */

/** @brief  Macros to enable the Deep-sleep mode with Flash memory kept off.
  * @note   When entering low power mode (stop or standby only), if DS_EE_KOFF and RUN_PD of
  *         FLASH_ACR register are both set , the Flash memory will not be woken up 
  *         when exiting from deep-sleep mode.
  */
#define __HAL_PWR_FLASHWAKEUP_ENABLE()      CLEAR_BIT(PWR->CR, PWR_CR_DSEEKOFF)

/** @brief  Macros to disable the Deep-sleep mode with Flash memory kept off.
  * @note   When entering low power mode (stop or standby only), if DS_EE_KOFF and RUN_PD of
  *         FLASH_ACR register are both set , the Flash memory will not be woken up 
  *         when exiting from deep-sleep mode.
  */
#define __HAL_PWR_FLASHWAKEUP_DISABLE()     SET_BIT(PWR->CR, PWR_CR_DSEEKOFF)
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions PWRex exported functions
 * @{
 */
void HAL_PWREx_EnableFastWakeUp(void);
void HAL_PWREx_DisableFastWakeUp(void);
void HAL_PWREx_EnableUltraLowPower(void);
void HAL_PWREx_DisableUltraLowPower(void);
void HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

