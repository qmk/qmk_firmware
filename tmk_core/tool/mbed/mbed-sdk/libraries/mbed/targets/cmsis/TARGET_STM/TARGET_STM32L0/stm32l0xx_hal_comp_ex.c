/**
  ******************************************************************************
  * @file    stm32l0xx_hal_comp_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Extended COMP HAL module driver.
  * @brief   This file provides firmware functions to manage the VREFINT
  *          which can act as input to the comparator.
  @verbatim 
  ==============================================================================
               ##### COMP peripheral Extended features  #####
  ==============================================================================

  [..] Comparing to other previous devices, the COMP interface for STM32L0XX
       devices contains the following additional features

       (+) Possibility to enable or disable the VREFINT which is used as input
           to the comparator.


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

/** @addtogroup COMPEx
  * @brief Extended COMP HAL module driver
  * @{
  */

#ifdef HAL_COMP_MODULE_ENABLED


/** @addtogroup COMPEx_Exported_Functions
  * @{
  */

/** @addtogroup COMPEx_Exported_Functions_Group1
  * @brief  Extended functions to manage VREFINT for the comparator
  *
  * @{
  */

/**
  * @brief  Enables the Buffer Vrefint for the COMP.
  * @note   This is functional only if the LOCK bit is not set

  * @retval None
  */
void HAL_COMPEx_EnableVREFINT(void)
{
    /* Enable the Buffer for the COMP by setting EN_VREFINT bit and the ENBUFLP_VREFINT_COMP in the CFGR3 register */

    SYSCFG->CFGR3 |= (SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP | SYSCFG_CFGR3_EN_VREFINT);
}

/**
  * @brief  Disables the Buffer Vrefint for the COMP.
  * @note   This is functional only if the LOCK bit is not set
  * @retval None
  */
void HAL_COMPEx_DisableVREFINT(void)
{
    /* Disable the Vrefint by resetting ENBUFLP_BGAP_COMP bit and the EN_VREFINT bit in the CFGR3 register */

    SYSCFG->CFGR3 &= (uint32_t)~((uint32_t)(SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP | SYSCFG_CFGR3_EN_VREFINT));
}

/**
  * @}
  */

/**
  * @}
  */


#endif /* HAL_COMP_MODULE_ENABLED */
/**
  * @}
  */ 

/**
  * @}
  */ 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
