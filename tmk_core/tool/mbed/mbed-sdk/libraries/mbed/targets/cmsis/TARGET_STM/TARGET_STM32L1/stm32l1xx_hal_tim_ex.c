/**
  ******************************************************************************
  * @file    stm32l1xx_hal_tim_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   TIM HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Timer extension peripheral:
  *           + Time Master and Slave synchronization configuration
  *           + Timer remapping capabilities configuration
  @verbatim
  ==============================================================================
                      ##### TIMER Extended features #####
  ==============================================================================
  [..]
    The Timer Extension features include:
    (#) Synchronization circuit to control the timer with external signals and to
        interconnect several timers together.
    (#) Timer remapping capabilities configuration

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

/** @defgroup TIMEx TIMEx
  * @brief TIM HAL module driver
  * @{
  */

#ifdef HAL_TIM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup TIMEx_Exported_Functions TIMEx Exported Functions
  * @{
  */

/** @defgroup TIMEx_Exported_Functions_Group1 Peripheral Control functions
 *  @brief   	Peripheral Control functions
 *
@verbatim
  ==============================================================================
                    ##### Peripheral Control functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Configure the commutation event in case of use of the Hall sensor interface.
      (+) Configure Complementary channels, break features and dead time.
      (+) Configure Master synchronization.
      (+) Configure timer remapping capabilities.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the TIM in master mode.
  * @param  htim: TIM handle.
  * @param  sMasterConfig: pointer to a TIM_MasterConfigTypeDef structure that
  *         contains the selected trigger output (TRGO) and the Master/Slave
  *         mode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef * sMasterConfig)
{
  /* Check the parameters */
  assert_param(IS_TIM_MASTER_INSTANCE(htim->Instance));
  assert_param(IS_TIM_TRGO_SOURCE(sMasterConfig->MasterOutputTrigger));
  assert_param(IS_TIM_MSM_STATE(sMasterConfig->MasterSlaveMode));

  __HAL_LOCK(htim);

  htim->State = HAL_TIM_STATE_BUSY;

  /* Reset the MMS Bits */
  htim->Instance->CR2 &= ~TIM_CR2_MMS;
  /* Select the TRGO source */
  htim->Instance->CR2 |=  sMasterConfig->MasterOutputTrigger;

  /* Reset the MSM Bit */
  htim->Instance->SMCR &= ~TIM_SMCR_MSM;
  /* Set or Reset the MSM Bit */
  htim->Instance->SMCR |= sMasterConfig->MasterSlaveMode;

  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

/**
  * @brief  Configures the TIM2/TIM3/TIM9/TIM10/TIM11 Remapping input capabilities.
  * @param  htim: TIM handle.
  * @param  Remap: specifies the TIM remapping source.
  *         This parameter is a combination of the following values depending on TIM instance.
  *
  *         For TIM2, the parameter can have the following values:
  *            @arg TIM_TIM2_ITR1_TIM10_OC:      TIM2 ITR1 input is connected to TIM10 OC
  *            @arg TIM_TIM2_ITR1_TIM5_TGO:      TIM2 ITR1 input is connected to TIM5 TGO
  *
  *         For TIM3, the parameter can have the following values:
  *            @arg TIM_TIM3_ITR2_TIM11_OC:      TIM3 ITR2 input is connected to TIM11 OC
  *            @arg TIM_TIM3_ITR2_TIM5_TGO:      TIM3 ITR2 input is connected to TIM5 TGO
  *
  *         For TIM9, the parameter is a combination of 2 fields (field1 | field2):
  *                   field1 can have the following values:
  *            @arg TIM_TIM9_ITR1_TIM3_TGO:      TIM9 ITR1 input is connected to TIM3 TGO
  *            @arg TIM_TIM9_ITR1_TS:            TIM9 ITR1 input is connected to touch sensing I/O
  *                   field2 can have the following values:
  *            @arg TIM_TIM9_GPIO:               TIM9 Channel1 is connected to GPIO
  *            @arg TIM_TIM9_LSE:                TIM9 Channel1 is connected to LSE internal clock
  *            @arg TIM_TIM9_GPIO1:              TIM9 Channel1 is connected to GPIO
  *            @arg TIM_TIM9_GPIO2:              TIM9 Channel1 is connected to GPIO
  *
  *         For TIM10, the parameter is a combination of 3 fields (field1 | field2 | field3):
  *                   field1 can have the following values:
  *            @arg TIM_TIM10_TI1RMP:            TIM10 Channel 1 depends on TI1_RMP
  *            @arg TIM_TIM10_RI:                TIM10 Channel 1 is connected to RI
  *                   field2 can have the following values:
  *            @arg TIM_TIM10_ETR_LSE:           TIM10 ETR input is connected to LSE clock
  *            @arg TIM_TIM10_ETR_TIM9_TGO:      TIM10 ETR input is connected to TIM9 TGO
  *                   field3 can have the following values:
  *            @arg TIM_TIM10_GPIO:              TIM10 Channel1 is connected to GPIO
  *            @arg TIM_TIM10_LSI:               TIM10 Channel1 is connected to LSI internal clock
  *            @arg TIM_TIM10_LSE:               TIM10 Channel1 is connected to LSE internal clock
  *            @arg TIM_TIM10_RTC:               TIM10 Channel1 is connected to RTC wakeup interrupt
  *
  *         For TIM11, the parameter is a combination of 3 fields (field1 | field2 | field3):
  *                   field1 can have the following values:
  *            @arg TIM_TIM11_TI1RMP:            TIM11 Channel 1 depends on TI1_RMP
  *            @arg TIM_TIM11_RI:                TIM11 Channel 1 is connected to RI
  *                   field2 can have the following values:
  *            @arg TIM_TIM11_ETR_LSE:           TIM11 ETR input is connected to LSE clock
  *            @arg TIM_TIM11_ETR_TIM9_TGO:      TIM11 ETR input is connected to TIM9 TGO 
  *                   field3 can have the following values:
  *            @arg TIM_TIM11_GPIO:     TIM11 Channel1 is connected to GPIO           
  *            @arg TIM_TIM11_MSI:      TIM11 Channel1 is connected to MSI internal clock
  *            @arg TIM_TIM11_HSE_RTC:  TIM11 Channel1 is connected to HSE_RTC clock
  *            @arg TIM_TIM11_GPIO1:    TIM11 Channel1 is connected to GPIO
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap)
{
  __HAL_LOCK(htim);

  /* Check parameters */
  assert_param(IS_TIM_REMAP_INSTANCE(htim->Instance));
  assert_param(IS_TIM_REMAP(htim->Instance,Remap));

  /* Set the Timer remapping configuration */
  htim->Instance->OR = Remap;

  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup TIMEx_Exported_Functions_Group2 Extension Callbacks functions
 *  @brief   Extension Callbacks functions
 *
@verbatim
  ==============================================================================
                    ##### Extension Callbacks functions #####
  ==============================================================================
  [..]
    This section provides Extension TIM callback functions:
    (+) Timer Commutation callback
    (+) Timer Break callback

@endverbatim
  * @{
  */


/**
  * @}
  */

/** @defgroup TIMEx_Exported_Functions_Group3 Extension Peripheral State functions
 *  @brief   Extension Peripheral State functions
 *
@verbatim
  ==============================================================================
                ##### Extension Peripheral State functions #####
  ==============================================================================
  [..]
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */


/**
  * @}
  */

#endif /* HAL_TIM_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
