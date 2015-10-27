/**
  ******************************************************************************
  * @file    stm32l0xx_hal_tim_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   TIM HAL module driver.
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Timer (TIM) peripheral:
  *           + Time Hall Sensor Interface Initialization
  *           + Time Hall Sensor Interface Start
  *           + Time Master and Slave synchronization configuration
  @verbatim 
================================================================================
          ##### TIM specific features integration #####
================================================================================
           
    [..] The Timer features include: 
         (#) 16-bit up, down, up/down auto-reload counter.
         (#) 16-bit programmable prescaler allowing dividing (also on the fly) the counter clock
             frequency either by any factor between 1 and 65536.
         (#) Up to 4 independent channels for:
           Input Capture
           Output Compare
           PWM generation (Edge and Center-aligned Mode)
           One-pulse mode output
         (#) Synchronization circuit to control the timer with external signals and to interconnect
            several timers together.
         (#) Supports incremental (quadrature) encoder and hall-sensor circuitry for positioning
           purposes               
   
            ##### How to use this driver #####
================================================================================
    [..]
     (#) Enable the TIM interface clock using 
         __HAL_RCC_TIMx_CLK_ENABLE(); 
       
     (#) TIM pins configuration
          (++) Enable the clock for the TIM GPIOs using the following function:
              __HAL_RCC_GPIOx_CLK_ENABLE();   
          (++) Configure these TIM pins in Alternate function mode using HAL_GPIO_Init();  

     (#) The external Clock can be configured, if needed (the default clock is the internal clock from the APBx), 
         using the following function:
         HAL_TIM_ConfigClockSource, the clock configuration should be done before any start function.
  
     (#) Configure the TIM in the desired operating mode using one of the 
         configuration function of this driver:
          (++) HAL_TIMEx_MasterConfigSynchronization() to configure the peripheral in master mode.

     (#) Remap the Timer I/O using HAL_TIMEx_RemapConfig() API.

  
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

/** @addtogroup TIMEx
  * @brief TIMEx HAL module driver
  * @{
  */

#ifdef HAL_TIM_MODULE_ENABLED


/** @addtogroup TIMEx_Exported_Functions
  * @{
  */


/** @addtogroup TIMEx_Exported_Functions_Group1
 *  @brief    Peripheral Control functions
 *
@verbatim   
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure Master and the Slave synchronization.
      
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
  
  /* Change the handler state */
  htim->State = HAL_TIM_STATE_BUSY;

  /* Reset the MMS Bits */
  htim->Instance->CR2 &= ~TIM_CR2_MMS;
  /* Select the TRGO source */
  htim->Instance->CR2 |= sMasterConfig->MasterOutputTrigger;

  /* Reset the MSM Bit */
  htim->Instance->SMCR &= ~TIM_SMCR_MSM;
  /* Set or Reset the MSM Bit */
  htim->Instance->SMCR |= sMasterConfig->MasterSlaveMode;

  htim->State = HAL_TIM_STATE_READY;
  
  __HAL_UNLOCK(htim);
  
  return HAL_OK;
}  


#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) \
    || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)

/**
  * @brief  Configures the remapping of the TIM2, TIM3, TIM21 and TIM22 inputs.
  *         The channel inputs (T1..T4) and the Trigger input (ETR) of the
  *         timers can be remaped thanks to this function. When an input is
  *         mapped, on a GPIO, refer yourself to the GPIO alternate functions
  *         for more details.
  * @note   It is not possible to connect TIM2 and TIM21 on
  *         GPIOB5_AF4 at the same time.
  *         When selecting TIM3_TI2_GPIOB5_AF4, Channel2 of TIM3 will be
  *         connected to GPIOB5_AF4 and Channel2 of TIM22 will be connected to
  *         some other GPIOs. (refer to alternate functions for more details)
  *         When selecting TIM3_TI2_GPIO_DEF, Channel2 of Timer 3 will be
  *         connected an GPIO (other than GPIOB5_AF4) and Channel2 of TIM22
  *         will be connected to GPIOB5_AF4.
  *
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  *               the configuration information for TIM module.
  * @param  Remap: specifies the TIM input remapping source.
  *                This parameter is a combination of the following values
  *                depending on TIM instance:
  *
  *         For TIM2, the parameter can have the following values:
  *           @arg TIM2_ETR_GPIO:      TIM2  ETR connected to GPIO (default):
  *                                    GPIOA(0)_AF5 or GPIOA(5)_AF2 or
  *                                    GPIOA(15)_AF2 or GPIOE(9)_AF2
  *           @arg TIM2_ETR_HSI48:     TIM2  ETR connected to HSI48
  *           @arg TIM2_ETR_LSE:       TIM2  ETR connected to LSE
  *           @arg TIM2_ETR_COMP2_OUT: TIM2  ETR connected to COMP2 output
  *           @arg TIM2_ETR_COMP1_OUT: TIM2  ETR connected to COMP1 output
  *           @arg TIM2_TI4_GPIO :     TIM2  TI4 connected to GPIO1(default):
  *                                    GPIOA(3)_AF2 or GPIOB(11)_AF2 or
  *                                    GPIOE(12)_AF0
  *           @arg TIM2_TI4_COMP1:     TIM2  TI4 connected to COMP1
  *           @arg TIM2_TI4_COMP2:     TIM2  TI4 connected to COMP2
  *
  *         For TIM3, the parameter can have the following values:
  *           @arg TIM3_ETR_GPIO:      TIM3  ETR connected to GPIO (default):
  *                                    GPIOE(2)_AF2 or GPIOD(2)_AF2 or
  *                                    GPIOE(2)AF2
  *           @arg TIM3_ETR_HSI:       TIM3 ETR connected to HSI
  *           @arg TIM3_TI1_USB_SOF:   TIM3 TI1 connected to USB_SOF (default)
  *           @arg TIM3_TI1_GPIO:      TIM3 TI1 connected to GPIO :
  *                                    GPIOE(3)_AF2 or GPIOA(6)_AF2 or
  *                                    GPIOC(6)_AF2 or GPIOB(4)_AF2
  *           @arg TIM3_TI2_GPIOB5_AF4:TIM3 TI3 connected to GPIOB(5)_AF4
  *                                    (refer to note)
  *           @arg TIM3_TI2_GPIO_DEF:  TIM3 TI3 connected to GPIO (default):
  *                                    GPIO_A(7)_AF2 or GPIO_B(5)_AF4 or
  *                                    GPIOC(7)_AF2 or GPIOE(7)_AF2
  *           @arg TIM3_TI4_GPIO_DEF:  TIM3 TI4 connected to GPIO:
  *                                    GPIO_B(1)_AF2 or GPIO_E(6)_AF2
  *           @arg TIM3_TI4_GPIOC9_AF2:TIM3 TI4 connected to GPIOC(9)_AF2
  *
  *         For TIM21, the parameter can have the following values:
  *           @arg TIM21_ETR_GPIO:     TIM21 ETR connected to GPIO(default) :
  *                                    APB2_PC(9)_AF0 or APB2_PA(1)_AF5
  *           @arg TIM21_ETR_COMP2_OUT:TIM21 ETR connected to COMP2 output
  *           @arg TIM21_ETR_COMP1_OUT:TIM21 ETR connected to COMP1 output
  *           @arg TIM21_ETR_LSE:      TIM21 ETR connected to LSE
  *           @arg TIM21_TI1_MCO:      TIM21 TI1 connected to MCO
  *           @arg TIM21_TI1_RTC_WKUT_IT: TIM21 TI1 connected to RTC WAKEUP interrupt
  *           @arg TIM21_TI1_HSE_RTC:  TIM21 TI1 connected to HSE_RTC
  *           @arg TIM21_TI1_MSI:      TIM21 TI1 connected to MSI clock
  *           @arg TIM21_TI1_LSE:      TIM21 TI1 connected to LSE
  *           @arg TIM21_TI1_LSI:      TIM21 TI1 connected to LSI
  *           @arg TIM21_TI1_COMP1_OUT:TIM21 TI1 connected to COMP1_OUT
  *           @arg TIM21_TI1_GPIO:     TIM21 TI1 connected to GPIO(default):
  *                                    GPIOA(2)_AF0 or GPIOB(13)_AF6 or
  *                                    GPIOE(5)_AF0 or GPIOD(0)_AF0
  *           @arg TIM21_TI2_GPIO:     TIM21 TI2 connected to GPIO(default):
  *                                    GPIOA(3)_AF0 or GPIOB(14)_AF6 or
  *                                    GPIOE(6)_AF0 or GPIOD(7)_AF1
  *           @arg TIM21_TI2_COMP2_OUT:TIM21 TI2 connected to COMP2 output
  *
  *         For TIM22, the parameter can have the following values:
  *           @arg TIM22_ETR_LSE:      TIM22 ETR connected to LSE
  *           @arg TIM22_ETR_COMP2_OUT:TIM22 ETR connected to COMP2 output
  *           @arg TIM22_ETR_COMP1_OUT:TIM22 ETR connected to COMP1 output
  *           @arg TIM22_ETR_GPIO:     TIM22 ETR connected to GPIO(default):
  *                                    GPIOC(8)_AF0 or GPIOA(4)_AF5
  *           @arg TIM22_TI1_GPIO1:    TIM22 TI1 connected to GPIO(default):
  *                                    GPIOC(6)_AF0 or GPIOA(6)_AF5 or
  *                                    GPIOB(4)_AF4 or GPIOE(0)_AF3
  *           @arg TIM22_TI1_COMP2_OUT:TIM22 TI1 connected to COMP2 output
  *           @arg TIM22_TI1_COMP1_OUT:TIM22 TI1 connected to COMP1 output
  *           @arg TIM22_TI1_GPIO2:    TIM22 TI1 connected to GPIO:
  *                                    GPIOC(6)_AF0 or GPIOA(6)_AF5 or
  *                                    GPIOB(4)_AF4 or GPIOE(3)_AF0
  *
  * @retval HAL status
  */
#else
/**
  * @brief  Configures the remapping of the TIM2, TIM21 and TIM22 inputs.
  *         The channel inputs (T1..T4) and the Trigger input (ETR) of the
  *         timers can be remaped thanks to this function. When an input is
  *         mapped, on a GPIO, refer yourself to the GPIO alternate functions
  *         for more details.
  *
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  *               the configuration information for TIM module.
  * @param  Remap: specifies the TIM input remapping source.
  *                This parameter is a combination of the following values
  *                depending on TIM instance:
  *
  *         For TIM2, the parameter can have the following values:
  *           @arg TIM2_ETR_GPIO:      TIM2  ETR connected to GPIO (default):
  *                                    GPIOA(0)_AF5 or GPIOA(5)_AF2 or
  *                                    GPIOA(15)_AF2 or GPIOE(9)_AF2
  *           @arg TIM2_ETR_HSI48:     TIM2  ETR connected to HSI48
  *           @arg TIM2_ETR_LSE:       TIM2  ETR connected to LSE
  *           @arg TIM2_ETR_COMP2_OUT: TIM2  ETR connected to COMP2 output
  *           @arg TIM2_ETR_COMP1_OUT: TIM2  ETR connected to COMP1 output
  *           @arg TIM2_TI4_GPIO:      TIM2  TI4 connected to GPIO1(default):
  *                                    GPIOA(3)_AF2 or GPIOB(11)_AF2 or
  *                                    GPIOE(12)_AF0
  *           @arg TIM2_TI4_COMP1:     TIM2  TI4 connected to COMP1
  *           @arg TIM2_TI4_COMP2:     TIM2  TI4 connected to COMP2
  *           @arg TIM2_TI4_GPIO2:     TIM2  TI4 connected to GPIO2 :
  *                                    GPIOA(3)_AF2 or GPIOB(11)_AF2 or
  *                                    GPIOE(12)_AF0
  *
  *         For TIM21, the parameter can have the following values:
  *           @arg TIM21_ETR_GPIO:     TIM21 ETR connected to GPIO(default) :
  *                                    APB2_PC(9)_AF0 or APB2_PA(1)_AF5
  *           @arg TIM21_ETR_COMP2_OUT:TIM21 ETR connected to COMP2 output
  *           @arg TIM21_ETR_COMP1_OUT:TIM21 ETR connected to COMP1 output
  *           @arg TIM21_ETR_LSE:      TIM21 ETR connected to LSE
  *           @arg TIM21_TI1_MCO:      TIM21 TI1 connected to MCO
  *           @arg TIM21_TI1_RTC_WKUT_IT: TIM21 TI1 connected to RTC WAKEUP interrupt
  *           @arg TIM21_TI1_HSE_RTC:  TIM21 TI1 connected to HSE_RTC
  *           @arg TIM21_TI1_MSI:      TIM21 TI1 connected to MSI clock
  *           @arg TIM21_TI1_LSE:      TIM21 TI1 connected to LSE
  *           @arg TIM21_TI1_LSI:      TIM21 TI1 connected to LSI
  *           @arg TIM21_TI1_COMP1_OUT:TIM21 TI1 connected to COMP1_OUT
  *           @arg TIM21_TI1_GPIO:     TIM21 TI1 connected to GPIO(default):
  *                                    GPIOA(2)_AF0 or GPIOB(13)_AF6 or
  *                                    GPIOE(5)_AF0 or GPIOD(0)_AF0
  *           @arg TIM21_TI2_GPIO:     TIM21 TI2 connected to GPIO(default):
  *                                    GPIOA(3)_AF0 or GPIOB(14)_AF6 or
  *                                    GPIOE(6)_AF0 or GPIOD(7)_AF1
  *           @arg TIM21_TI2_COMP2_OUT:TIM21 TI2 connected to COMP2 output
  *
  *         For TIM22, the parameter can have the following values:
  *           @arg TIM22_ETR_LSE:      TIM22 ETR connected to LSE
  *           @arg TIM22_ETR_COMP2_OUT:TIM22 ETR connected to COMP2 output
  *           @arg TIM22_ETR_COMP1_OUT:TIM22 ETR connected to COMP1 output
  *           @arg TIM22_ETR_GPIO:     TIM22 ETR connected to GPIO(default):
  *                                    GPIOC(8)_AF0 or GPIOA(4)_AF5
  *           @arg TIM22_TI1_GPIO1:    TIM22 TI1 connected to GPIO(default):
  *                                    GPIOC(6)_AF0 or GPIOA(6)_AF5 or
  *                                    GPIOB(4)_AF4 or GPIOE(0)_AF3
  *           @arg TIM22_TI1_COMP2_OUT:TIM22 TI1 connected to COMP2 output
  *           @arg TIM22_TI1_COMP1_OUT:TIM22 TI1 connected to COMP1 output
  *           @arg TIM22_TI1_GPIO2:    TIM22 TI1 connected to GPIO:
  *                                    GPIOC(6)_AF0 or GPIOA(6)_AF5 or
  *                                    GPIOB(4)_AF4 or GPIOE(3)_AF0
  *
  * @retval HAL status
  */

#endif /* STM32L07xxx or STM32L08xxx */

HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap)
{

   __HAL_LOCK(htim);

  /* Check parameters */
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
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
