/**
  ******************************************************************************
  * @file    stm32f3xx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Extended PWR HAL module driver.
  *
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
#include "stm32f3xx_hal.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWR Extended HAL module driver
  * @brief    PWREx HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup PWREx_Private_Constants PWR Extended Private Constants
  * @{
  */
#define PVD_MODE_IT               ((uint32_t)0x00010000)
#define PVD_MODE_EVT              ((uint32_t)0x00020000)
#define PVD_RISING_EDGE           ((uint32_t)0x00000001)
#define PVD_FALLING_EDGE          ((uint32_t)0x00000002)
/**
  * @}
  */
 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @defgroup PWREx_Exported_Functions_Group1 Peripheral Extended Control Functions
  *  @brief   Extended Peripheral Control functions
  *
@verbatim

 ===============================================================================
                 ##### Peripheral Extended control functions #####
 ===============================================================================
    *** PVD configuration (present on all other devices than STM32F3x8 devices) ***
    =========================
    [..]
      (+) The PVD is used to monitor the VDD power supply by comparing it to a
          threshold selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
      (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower
          than the PVD threshold. This event is internally connected to the EXTI
          line16 and can generate an interrupt if enabled. This is done through
          __HAL_PVD_EXTI_ENABLE_IT() macro
      (+) The PVD is stopped in Standby mode.
      (+) Note: PVD is not available on STM32F3x8 Product Line


    *** Voltage regulator ***
    =========================
      (+) The voltage regulator is always enabled after Reset. It works in three different
          modes:
          In Run mode, the regulator supplies full power to the 1.8V domain (core, memories
          and digital peripherals).
          In Stop mode, the regulator supplies low power to the 1.8V domain, preserving
          contents of registers and SRAM.
          In Stop mode, the regulator is powered off. The contents of the registers and SRAM
          are lost except for the Standby circuitry and the Backup Domain.
          Note: In the STM32F3x8xx devices, the voltage regulator is bypassed and the
          microcontroller must be powered from a nominal VDD = 1.8V +/-8% voltage.


      (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower
          than the PVD threshold. This event is internally connected to the EXTI
          line16 and can generate an interrupt if enabled. This is done through
          __HAL_PVD_EXTI_ENABLE_IT() macro
      (+) The PVD is stopped in Standby mode.


    *** SDADC power configuration ***
    ================================
      (+) On STM32F373xC/STM32F378xx devices, there are up to 
          3 SDADC instances that can be enabled/disabled.

@endverbatim
  * @{
  */

#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F303x8) || defined(STM32F334x8) || \
    defined(STM32F301x8) || defined(STM32F302x8) || \
    defined(STM32F373xC)

/**
  * @brief Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param sConfigPVD: pointer to an PWR_PVDTypeDef structure that contains the configuration
  *        information for the PVD.
  * @note Refer to the electrical characteristics of your device datasheet for
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
  * @brief Enables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_EnablePVD(void)
{
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)ENABLE;
}

/**
  * @brief Disables the Power Voltage Detector(PVD).
  * @retval None
  */
void HAL_PWR_DisablePVD(void)
{
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)DISABLE;
}

/**
  * @brief This function handles the PWR PVD interrupt request.
  * @note This API should be called under the PVD_IRQHandler().
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
  * @brief PWR PVD interrupt callback
  * @retval None
  */
__weak void HAL_PWR_PVDCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWR_PVDCallback could be implemented in the user file
   */
}

#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302xC || STM32F303xC || */
       /* STM32F303x8 || STM32F334x8 || */
       /* STM32F301x8 || STM32F302x8 || */
       /* STM32F373xC                   */

#if defined(STM32F373xC) || defined(STM32F378xx)

/**
  * @brief  Enables the SDADC peripheral functionaliy
  * @param  Analogx: specifies the SDADC peripheral instance.
  *   This parameter can be: PWR_SDADC_ANALOG1, PWR_SDADC_ANALOG2 or PWR_SDADC_ANALOG3.
  * @retval None
  */
void HAL_PWREx_EnableSDADCAnalog(uint32_t Analogx)
{
  /* Check the parameters */
  assert_param(IS_PWR_SDADC_ANALOG(Analogx));

  /* Enable PWR clock interface for SDADC use */
  __PWR_CLK_ENABLE();
    
  PWR->CR |= Analogx;
}

/**
  * @brief  Disables the SDADC peripheral functionaliy
  * @param  Analogx: specifies the SDADC peripheral instance.
  *   This parameter can be: PWR_SDADC_ANALOG1, PWR_SDADC_ANALOG2 or PWR_SDADC_ANALOG3.
  * @retval None
  */
void HAL_PWREx_DisableSDADCAnalog(uint32_t Analogx)
{
  /* Check the parameters */
  assert_param(IS_PWR_SDADC_ANALOG(Analogx));
  
  PWR->CR &= ~Analogx;
}

#endif /* STM32F373xC || STM32F378xx */

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
