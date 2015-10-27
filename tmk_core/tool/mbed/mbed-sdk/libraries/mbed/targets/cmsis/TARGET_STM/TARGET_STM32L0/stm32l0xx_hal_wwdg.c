/**
  ******************************************************************************
  * @file    stm32l0xx_hal_wwdg.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   WWDG HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Window Watchdog (WWDG) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State functions        
  @verbatim
  ==============================================================================
                      ##### WWDG specific features #####
  ==============================================================================
  [..] 
    Once enabled the WWDG generates a system reset on expiry of a programmed
       time period, unless the program refreshes the counter (downcounter)
       before reaching 0x3F value (i.e. a reset is generated when the counter
       value rolls over from 0x40 to 0x3F).

        (+) An MCU reset is also generated if the counter value is refreshed
            before the counter has reached the refresh window value. This
            implies that the counter must be refreshed in a limited window.
        (+) Once enabled the WWDG cannot be disabled except by a system reset.
        (+) WWDGRST flag in RCC_CSR register can be used to inform when a WWDG
            reset occurs.               
        (+) The WWDG counter input clock is derived from the APB clock divided
            by a programmable prescaler.
        (+) WWDG counter clock = PCLK1 / Prescaler
            WWDG timeout = (WWDG counter clock) * (counter value) 
        (+) Min-max timeout value @32 MHz(PCLK1): ~128.0 us / ~65.54 ms


                     ##### How to use this driver #####
  ==============================================================================
  [..]
    (+) Enable WWDG APB1 clock using __HAL_RCC_WWDG_CLK_ENABLE().
    (+) Set the WWDG prescaler, refresh window and counter value
        using HAL_WWDG_Init() function.
    (+) Start the WWDG using HAL_WWDG_Start() function.
        When the WWDG is enabled the counter value should be configured to
        a value greater than 0x40 to prevent generating an immediate reset.
    (+) Optionally you can enable the Early Wakeup Interrupt (EWI) which is
        generated when the counter reaches 0x40, and then start the WWDG using
        HAL_WWDG_Start_IT().
        Once enabled, EWI interrupt cannot be disabled except by a system reset.
    (+) Then the application program must refresh the WWDG counter at regular
        intervals during normal operation to prevent an MCU reset, using
        HAL_WWDG_Refresh() function. This operation must occur only when
        the counter is lower than the refresh window value already programmed.
        
     *** WWDG HAL driver macros list ***
     ==================================
     [..]
       Below the list of most used macros in WWDG HAL driver.
       
      (+) __HAL_WWDG_ENABLE: Enable the WWDG peripheral 
      (+) __HAL_WWDG_GET_FLAG: Get the selected WWDG's flag status
      (+) __HAL_WWDG_CLEAR_FLAG: Clear the WWDG's pending flags 
      (+) __HAL_WWDG_ENABLE_IT:  Enables the WWDG early wakeup interrupt  

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

/** @addtogroup WWDG
  * @brief WWDG HAL module driver.
  * @{
  */

#ifdef HAL_WWDG_MODULE_ENABLED

/** @addtogroup WWDG_Exported_Functions WWDG Exported Functions
  * @{
  */

/** @addtogroup WWDG_Exported_Functions_Group1
 *  @brief    Initialization and Configuration functions.
 *
@verbatim
  ==============================================================================
          ##### Initialization and de-initialization functions #####
  ==============================================================================
  [..]  
    This section provides functions allowing to:
      (+) Initialize the WWDG according to the specified parameters
          in the WWDG_InitTypeDef and create the associated handle
      (+) DeInitialize the WWDG peripheral
      (+) Initialize the WWDG MSP
      (+) DeInitialize the WWDG MSP

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the WWDG according to the specified
  *         parameters in the WWDG_InitTypeDef and creates the associated handle.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_WWDG_Init(WWDG_HandleTypeDef *hwwdg)
{

  /* Check the WWDG handle allocation */
  if(hwwdg == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_WWDG_ALL_INSTANCE(hwwdg->Instance));
  assert_param(IS_WWDG_PRESCALER(hwwdg->Init.Prescaler));
  assert_param(IS_WWDG_WINDOW(hwwdg->Init.Window));
  assert_param(IS_WWDG_COUNTER(hwwdg->Init.Counter));
  
  if(hwwdg->State == HAL_WWDG_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_WWDG_MspInit(hwwdg);
  }

  /* Take lock  and change peripheral state */
   __HAL_LOCK(hwwdg);
  hwwdg->State = HAL_WWDG_STATE_BUSY;

   /* Set WWDG Prescaler and Window  and Counter*/
  MODIFY_REG(hwwdg->Instance->CFR, (WWDG_CFR_WDGTB | WWDG_CFR_W), (hwwdg->Init.Prescaler | hwwdg->Init.Window));
  MODIFY_REG(hwwdg->Instance->CR, WWDG_CR_T, hwwdg->Init.Counter);

  /* Change peripheral state and release lock*/
  hwwdg->State = HAL_WWDG_STATE_READY;
  __HAL_UNLOCK(hwwdg);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  DeInitializes the WWDG peripheral.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_WWDG_DeInit(WWDG_HandleTypeDef *hwwdg)
{
  /* Check the parameters */
  assert_param(IS_WWDG_ALL_INSTANCE(hwwdg->Instance));

  /* Take lock and change peripheral state */
   __HAL_LOCK(hwwdg);
  hwwdg->State = HAL_WWDG_STATE_BUSY;

  /* DeInit the low level hardware */
  HAL_WWDG_MspDeInit(hwwdg);

  /* Reset WWDG Control, configuration and status  register */
  MODIFY_REG(hwwdg->Instance->CR, (WWDG_CR_T | WWDG_CR_WDGA),0x0000007F);
  MODIFY_REG(hwwdg->Instance->CFR, (WWDG_CFR_WDGTB | WWDG_CFR_W | WWDG_CFR_EWI),0x0000007F);
  MODIFY_REG(hwwdg->Instance->SR,WWDG_SR_EWIF,0x0);

  /* Change peripheral state and release lock*/
  hwwdg->State = HAL_WWDG_STATE_RESET;
  __HAL_UNLOCK(hwwdg);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the WWDG MSP.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval None
  */
__weak void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_WWDG_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes the WWDG MSP.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval None
  */
__weak void HAL_WWDG_MspDeInit(WWDG_HandleTypeDef *hwwdg)
{
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_WWDG_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @addtogroup WWDG_Exported_Functions_Group2
 *  @brief    IO operation functions 
 *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================  
  [..]  
    This section provides functions allowing to:
      (+) Start the WWDG.
      (+) Refresh the WWDG.
      (+) Handle WWDG interrupt request.

@endverbatim
  * @{
  */

/**
  * @brief  Starts the WWDG.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_WWDG_Start(WWDG_HandleTypeDef *hwwdg)
{
  /* Take lock and change peripheral state */
  __HAL_LOCK(hwwdg); 
  hwwdg->State = HAL_WWDG_STATE_BUSY;

  /* Enable the peripheral */
  __HAL_WWDG_ENABLE(hwwdg);

  /* Change peripheral state and release lock*/
  hwwdg->State = HAL_WWDG_STATE_READY;
  __HAL_UNLOCK(hwwdg);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Starts the WWDG with interrupt enabled.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_WWDG_Start_IT(WWDG_HandleTypeDef *hwwdg)
{
  /* Take lock and change peripheral state */
  __HAL_LOCK(hwwdg);
  hwwdg->State = HAL_WWDG_STATE_BUSY;

  /* Enable the Early Wakeup Interrupt */
  __HAL_WWDG_ENABLE_IT(hwwdg,WWDG_IT_EWI);

  /* Enable the peripheral */
  __HAL_WWDG_ENABLE(hwwdg);

  /* Change peripheral state and release lock*/
  hwwdg->State = HAL_WWDG_STATE_READY;
  __HAL_UNLOCK(hwwdg);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Refreshes the WWDG.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @param  Counter: value of counter to put in WWDG counter
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_WWDG_Refresh(WWDG_HandleTypeDef *hwwdg, uint32_t Counter)
{

  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));

  /* Write to WWDG CR the WWDG Counter value to refresh with */
  MODIFY_REG(hwwdg->Instance->CR, (uint32_t)WWDG_CR_T, Counter);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Handles WWDG interrupt request.
  * @note   The Early Wakeup Interrupt (EWI) can be used if specific safety operations
  *         or data logging must be performed before the actual reset is generated.
  *         The EWI interrupt is enabled using __HAL_WWDG_ENABLE_IT() macro.
  *         When the downcounter reaches the value 0x40, and EWI interrupt is
  *         generated and the corresponding Interrupt Service Routine (ISR) can
  *         be used to trigger specific actions (such as communications or data
  *         logging), before resetting the device.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval None
  */
void HAL_WWDG_IRQHandler(WWDG_HandleTypeDef *hwwdg)
{
  /* Check if Early Wakeup Interrupt is enable */
  if(__HAL_WWDG_GET_IT_SOURCE(hwwdg, WWDG_IT_EWI) != RESET)
  {
    /* Check if WWDG Early Wakeup Interrupt occurred */
    if(__HAL_WWDG_GET_FLAG(hwwdg, WWDG_FLAG_EWIF) != RESET)
    {
      /* Early Wakeup callback */
      HAL_WWDG_WakeupCallback(hwwdg);

      /* Clear the WWDG Data Ready flag */
      __HAL_WWDG_CLEAR_IT(hwwdg, WWDG_FLAG_EWIF);
    }
  }
}

/**
  * @brief  Early Wakeup WWDG callback.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval None
  */
__weak void HAL_WWDG_WakeupCallback(WWDG_HandleTypeDef* hwwdg)
{
}

/**
  * @}
  */

/** @addtogroup WWDG_Exported_Functions_Group3
 *  @brief    Peripheral State functions.
 *
@verbatim
  ==============================================================================
                      ##### Peripheral State functions #####
  ==============================================================================  
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the WWDG state.
  * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
  *              the configuration information for the specified WWDG module.
  * @retval HAL state
  */
HAL_WWDG_StateTypeDef HAL_WWDG_GetState(WWDG_HandleTypeDef *hwwdg)
{
  return hwwdg->State;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_WWDG_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

