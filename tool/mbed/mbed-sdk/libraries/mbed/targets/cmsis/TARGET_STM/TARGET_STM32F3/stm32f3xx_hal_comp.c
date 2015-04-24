/**
  ******************************************************************************
  * @file    stm32f3xx_hal_comp.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   COMP HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the COMP peripheral:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions 
  *           + Peripheral State functions
  *         
  @verbatim
================================================================================
          ##### COMP Peripheral features #####
================================================================================
           
  [..]       
      The STM32F3xx device family integrates up to 7 analog comparators COMP1, COMP2...COMP7:
      (#) The non inverting input and inverting input can be set to GPIO pins
          as shown in table1. COMP Inputs below for STM32F303xB/STM32F303xC as example.
          For other STM32F3xx devices please refer to the COMP peripheral section in corresponding 
          Reference Manual.
  
      (#) The COMP output is available using HAL_COMP_GetOutputLevel()
          and can be set on GPIO pins. Refer to table 2. COMP Outputs below for STM32F303xB/STM32F303xC as example.
          For other STM32F3xx devices please refer to the COMP peripheral section in corresponding 
          Reference Manual.
  
      (#) The COMP output can be redirected to embedded timers (TIM1, TIM2, TIM3...)
          Refer to table 3. COMP Outputs redirection to embedded timers below for STM32F303xB/STM32F303xC as example.
          For other STM32F3xx devices please refer to the COMP peripheral section in corresponding 
          Reference Manual.
  
      (#) The comparators COMP1 and COMP2, COMP3 and COMP4, COMP5 and COMP6 can be combined in window
          mode and only COMP1, COMP3 and COMP5 non inverting input can be used as non-inverting input.
  
      (#) The seven comparators have interrupt capability with wake-up
          from Sleep and Stop modes (through the EXTI controller):
          (++) COMP1 is internally connected to EXTI Line 21
          (++) COMP2 is internally connected to EXTI Line 22
          (++) COMP3 is internally connected to EXTI Line 29
          (++) COMP4 is internally connected to EXTI Line 30
          (++) COMP5 is internally connected to EXTI Line 31
          (++) COMP6 is internally connected to EXTI Line 32
          (++) COMP7 is internally connected to EXTI Line 33
          From the corresponding IRQ handler, the right interrupt source can be retrieved with the 
          macro __HAL_COMP_EXTI_GET_FLAG(). Possible values are:
          (++) COMP_EXTI_LINE_COMP1_EVENT
          (++) COMP_EXTI_LINE_COMP2_EVENT
          (++) COMP_EXTI_LINE_COMP3_EVENT
          (++) COMP_EXTI_LINE_COMP4_EVENT
          (++) COMP_EXTI_LINE_COMP5_EVENT
          (++) COMP_EXTI_LINE_COMP6_EVENT
          (++) COMP_EXTI_LINE_COMP7_EVENT

[..] Table 1. COMP Inputs for the STM32F303xB/STM32F303xC/STM32F303xE devices
 +------------------------------------------------------------------------------------------+     
 |                 |                | COMP1 | COMP2 | COMP3 | COMP4 | COMP5 | COMP6 | COMP7 |
 |-----------------|----------------|---------------|---------------------------------------|
 |                 | 1/4 VREFINT    |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | 1/2 VREFINT    |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | 3/4 VREFINT    |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 | Inverting Input | VREFINT        |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | DAC1 OUT (PA4) |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | DAC2 OUT (PA5) |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | IO1            |  PA0  |  PA2  |  PD15 |  PE8  |  PD13 |  PD10 |  PC0  |
 |                 | IO2            |  ---  |  ---  |  PB12 |  PB2  |  PB10 |  PB15 |  ---  |
 |-----------------|----------------|-------|-------|-------|-------|-------|-------|-------|
 |  Non Inverting  | IO1            |  PA1  |  PA7  |  PB14 |  PB0  |  PD12 |  PD11 |  PA0  |
 |    Input        | IO2            |  ---  |  PA3  |  PD14 |  PE7  |  PB13 |  PB11 |  PC1  |
 +------------------------------------------------------------------------------------------+  
  
 [..] Table 2. COMP Outputs for the STM32F303xB/STM32F303xC/STM32F303xE devices
 +-------------------------------------------------------+     
 | COMP1 | COMP2 | COMP3 | COMP4 | COMP5 | COMP6 | COMP7 |
 |-------|-------|-------|-------|-------|-------|-------|
 |  PA0  |  PA2  |  PB1  |  PC8  |  PC7  |  PA10 |  PC2  |
 |  PF4  |  PA7  |  ---  |  PA8  |  PA9  |  PC6  |  ---  |
 |  PA6  |  PA12 |  ---  |  ---  |  ---  |  ---  |  ---  |
 |  PA11 |  PB9  |  ---  |  ---  |  ---  |  ---  |  ---  |
 |  PB8  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
 +-------------------------------------------------------+

 [..] Table 3. COMP Outputs redirection to embedded timers for the STM32F303xB/STM32F303xC devices
 +----------------------------------------------------------------------------------------------------------------------+     
 |     COMP1      |     COMP2      |     COMP3      |     COMP4      |     COMP5      |     COMP6      |     COMP7      |
 |----------------|----------------|----------------|----------------|----------------|----------------|----------------|
 |  TIM1 BKIN     |  TIM1 BKIN     |  TIM1 BKIN     |  TIM1 BKIN     |  TIM1 BKIN     |  TIM1 BKIN     |  TIM1 BKIN     |
 |                |                |                |                |                |                |                |
 |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |
 |                |                |                |                |                |                |                |
 |  TIM8 BKIN     |  TIM8 BKIN     |  TIM8 BKIN     |  TIM8 BKIN     |  TIM8 BKIN     |  TIM8 BKIN     |  TIM8 BKIN     |
 |                |                |                |                |                |                |                |
 |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |
 |                |                |                |                |                |                |                |
 |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |
 |     +          |     +          |     +          |     +          |     +          |     +          |     +          |
 |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |
 |                |                |                |                |                |                |                |
 |  TIM1 OCREFCLR |  TIM1 OCREFCLR |  TIM1 OCREFCLR |  TIM8 OCREFCLR |  TIM8 OCREFCLR |  TIM8 OCREFCLR |  TIM1 OCREFCLR |  
 |                |                |                |                |                |                |                |
 |  TIM1 IC1      |  TIM1 IC1      |  TIM2 OCREFCLR |  TIM3 IC3      |  TIM2 IC1      |  TIM2 IC2      |  TIM8 OCREFCLR |
 |                |                |                |                |                |                |                |
 |  TIM2 IC4      |  TIM2 IC4      |  TIM3 IC2      |  TIM3 OCREFCLR |  TIM3 OCREFCLR |  TIM2 OCREFCLR |  TIM2 IC3      |
 |                |                |                |                |                |                |                |
 |  TIM2 OCREFCLR |  TIM2 OCREFCLR |  TIM4 IC1      |  TIM4 IC2      |  TIM4 IC3      |  TIM16 OCREFCLR|  TIM1 IC2      |
 |                |                |                |                |                |                |                |
 |  TIM3 IC1      |  TIM3 IC1      |  TIM15 IC1     |  TIM15 OCREFCLR|  TIM16 BKIN    |  TIM16 IC1     |  TIM17 OCREFCLR|          
 |                |                |                |                |                |                |                |
 |  TIM3 OCREFCLR |  TIM3 OCREFCLR |  TIM15 BKIN    |  TIM15 IC2     |  TIM17 IC1     |  TIM4 IC4      |  TIM17 BKIN    |
 +----------------------------------------------------------------------------------------------------------------------+

 [..] Table 4. COMP Outputs redirection to embedded timers for the STM32F303xE devices
 +----------------------------------------------------------------------------------------------------------------------+
 |     COMP1      |     COMP2      |     COMP3      |     COMP4      |     COMP5      |     COMP6      |     COMP7      |
 |----------------|----------------|----------------|----------------|----------------|----------------|----------------|
 |  TIM1 BKIN     |  TIM1 BKIN     |  TIM1 BKIN     |  TIM1 BKIN (1) |  TIM1 BKIN     |  TIM1 BKIN     |  TIM1 BKIN (1) |
 |                |                |                |                |                |                |                |
 |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |
 |                |                |                |                |                |                |                |
 |  TIM8 BKIN     |  TIM8 BKIN     |  TIM8 BKIN     |  TIM8 BKIN (1) |  TIM8 BKIN     |  TIM8 BKIN     |  TIM8 BKIN (1) |
 |                |                |                |                |                |                |                |
 |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |
 |                |                |                |                |                |                |                |
 |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |
 |     +          |     +          |     +          |     +          |     +          |     +          |     +          |
 |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |  TIM8BKIN2     |
 |                |                |                |                |                |                |                |
 |  TIM1 OCREFCLR |  TIM1 OCREFCLR |  TIM1 OCREFCLR |  TIM8 OCREFCLR |  TIM8 OCREFCLR |  TIM8 OCREFCLR |  TIM1 OCREFCLR |  
 |                |                |                |                |                |                |                |
 |  TIM1 IC1      |  TIM1 IC1      |  TIM2 OCREFCLR |  TIM3 IC3      |  TIM2 IC1      |  TIM2 IC2      |  TIM8 OCREFCLR |
 |                |                |                |                |                |                |                |
 |  TIM2 IC4      |  TIM2 IC4      |  TIM3 IC2      |  TIM3 OCREFCLR |  TIM3 OCREFCLR |  TIM2 OCREFCLR |  TIM2 IC3      |
 |                |                |                |                |                |                |                |
 |  TIM2 OCREFCLR |  TIM2 OCREFCLR |  TIM4 IC1      |  TIM4 IC2      |  TIM4 IC3      |  TIM16 OCREFCLR|  TIM1 IC2      |
 |                |                |                |                |                |                |                |
 |  TIM3 IC1      |  TIM3 IC1      |  TIM15 IC1     |  TIM15 OCREFCLR|  TIM16 BKIN    |  TIM16 IC1     |  TIM17 OCREFCLR|          
 |                |                |                |                |                |                |                |
 |  TIM3 OCREFCLR |  TIM3 OCREFCLR |  TIM15 BKIN    |  TIM15 IC2     |  TIM17 IC1     |  TIM4 IC4      |  TIM17 BKIN    |
 |                |                |                |                |                |                |                |
 |  TIM20 BKIN    |  TIM20 BKIN    |  TIM20 BKIN    |  TIM20 BKIN (1)|  TIM20 BKIN    |  TIM20 BKIN    |  TIM20 BKIN (1)|
 |                |                |                |                |                |                |                |
 |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |
 |                |                |                |                |                |                |                |
 |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |  TIM1 BKIN2    |
 |     +          |     +          |     +          |     +          |     +          |     +          |     +          |
 |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |  TIM8 BKIN2    |
 |     +          |     +          |     +          |     +          |     +          |     +          |     +          |
 |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |  TIM20 BKIN2   |
 |                |                |                |                |                |                |                |
 +----------------------------------------------------------------------------------------------------------------------+
 (1):This connection consists of connecting both GPIO and COMP output to TIM1/8/20 BRK input through an OR gate, instead
     of connecting the GPIO to the TIM1/8/20 BRK input and the COMP output to the TIM1/8/20 BRK_ACTH input. The aim is to 
     add a digital filter (3  bits) on the COMP output.

 [..] Table 5. COMP Outputs blanking sources for the STM32F303xB/STM32F303xC/STM32F303xE devices
 +----------------------------------------------------------------------------------------------------------------------+
 |     COMP1      |     COMP2      |     COMP3      |     COMP4      |     COMP5      |     COMP6      |     COMP7      |
 |----------------|----------------|----------------|----------------|----------------|----------------|----------------|
 |  TIM1 OC5      |  TIM1 OC5      |  TIM1 OC5      |  TIM3 OC4      |  --------      |  TIM8 OC5      |  TIM1 OC5      |
 |                |                |                |                |                |                |                |
 |  TIM2 OC3      |  TIM2 OC3      |  --------      |  TIM8 OC5      |  TIM3 OC3      |  TIM2 OC4      |  TIM8 OC5      |
 |                |                |                |                |                |                |                |
 |  TIM3 OC3      |  TIM3 OC3      |  TIM2 OC4      |  TIM15 OC1     |  TIM8 OC5      |  TIM15 OC2     |  TIM15 OC2     |
 |                |                |                |                |                |                |                |
 +----------------------------------------------------------------------------------------------------------------------+
   
            ##### How to use this driver #####
================================================================================
  [..]
      This driver provides functions to configure and program the Comparators of all STM32F3xx devices.

      To use the comparator, perform the following steps:
  
      (#) Fill in the HAL_COMP_MspInit() to
      (++) Configure the comparator input in analog mode using HAL_GPIO_Init()
      (++) Configure the comparator output in alternate function mode using HAL_GPIO_Init() to map the comparator 
           output to the GPIO pin
      (++) If required enable the COMP interrupt by configuring and enabling EXTI line in Interrupt mode and 
           selecting the desired sensitivity level using HAL_GPIO_Init() function. After that enable the comparator
           interrupt vector using HAL_NVIC_EnableIRQ() function.
  
      (#) Configure the comparator using HAL_COMP_Init() function:
      (++) Select the inverting input
      (++) Select the non-inverting input
      (++) Select the output polarity  
      (++) Select the output redirection
      (++) Select the hysteresis level
      (++) Select the power mode
      (++) Select the event/interrupt mode
  
      (#) Enable the comparator using HAL_COMP_Start() function or HAL_COMP_Start_IT() function for interrupt mode
    
      (#) Read the comparator output level with HAL_COMP_GetOutputLevel()
    
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
#include "stm32f3xx_hal.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @defgroup COMP COMP HAL module driver
  * @brief COMP HAL module driver
  * @{
  */

#ifdef HAL_COMP_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup COMP_Exported_Functions COMP Exported Functions
  * @{
  */

/** @defgroup COMP_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization/de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions to initialize and de-initialize comparators 

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the COMP according to the specified
  *         parameters in the COMP_InitTypeDef and create the associated handle.
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  hcomp: COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the COMP handle allocation and lock status */
  if((hcomp == HAL_NULL) || ((hcomp->State & COMP_STATE_BIT_LOCK) != RESET))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));
    assert_param(IS_COMP_INVERTINGINPUT(hcomp->Init.InvertingInput));
    assert_param(IS_COMP_NONINVERTINGINPUT(hcomp->Init.NonInvertingInput));
    assert_param(IS_COMP_NONINVERTINGINPUT_INSTANCE(hcomp->Instance, hcomp->Init.NonInvertingInput));
    assert_param(IS_COMP_OUTPUT(hcomp->Init.Output));
    assert_param(IS_COMP_OUTPUTPOL(hcomp->Init.OutputPol));
    assert_param(IS_COMP_HYSTERESIS(hcomp->Init.Hysteresis));  
    assert_param(IS_COMP_MODE(hcomp->Init.Mode));
    assert_param(IS_COMP_BLANKINGSRCE(hcomp->Init.BlankingSrce)); 
    assert_param(IS_COMP_BLANKINGSRCE_INSTANCE(hcomp->Instance, hcomp->Init.BlankingSrce)); 
    
    if(hcomp->Init.WindowMode != COMP_WINDOWMODE_DISABLED)
    {
      assert_param(IS_COMP_WINDOWMODE_INSTANCE(hcomp->Instance));
    }
  
    if(hcomp->State == HAL_COMP_STATE_RESET)
    {
      /* Init SYSCFG and the low level hardware to access comparators */
      __SYSCFG_CLK_ENABLE();

      HAL_COMP_MspInit(hcomp);
    }
  
    /* Set COMP parameters */
    /*     Set COMPxINSEL bits according to hcomp->Init.InvertingInput value        */
    /*     Set COMPxNONINSEL bits according to hcomp->Init.NonInvertingInput value  */
    /*     Set COMPxBLANKING bits according to hcomp->Init.BlankingSrce value       */
    /*     Set COMPxOUTSEL bits according to hcomp->Init.Output value               */
    /*     Set COMPxPOL bit according to hcomp->Init.OutputPol value                */
    /*     Set COMPxHYST bits according to hcomp->Init.Hysteresis value             */
    /*     Set COMPxMODE bits according to hcomp->Init.Mode value                   */
    COMP_INIT(hcomp);

    /* Initialize the COMP state*/
    if(hcomp->State == HAL_COMP_STATE_RESET)
    {
      hcomp->State = HAL_COMP_STATE_READY;
    }
  }
  
  return status;
}

/**
  * @brief  DeInitializes the COMP peripheral 
  * @note   Deinitialization can't be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  hcomp: COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef *hcomp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if((hcomp == HAL_NULL) || ((hcomp->State & COMP_STATE_BIT_LOCK) != RESET))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    /* Set COMP_CSR register to reset value */
    COMP_DEINIT(hcomp);

    /* DeInit the low level hardware: SYSCFG, GPIO, CLOCK and NVIC */
    HAL_COMP_MspDeInit(hcomp);

    hcomp->State = HAL_COMP_STATE_RESET;
  }
  
  return status;
}

/**
  * @brief  Initializes the COMP MSP.
  * @param  hcomp: COMP handle
  * @retval None
  */
__weak void HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_COMP_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes COMP MSP.
  * @param  hcomp: COMP handle
  * @retval None
  */
__weak void HAL_COMP_MspDeInit(COMP_HandleTypeDef *hcomp)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_COMP_MspDeInit could be implenetd in the user file
   */
}

/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group2 Input and Output operation functions 
 *  @brief   Data transfers functions 
 *
@verbatim   
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the COMP data 
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the comparator 
  * @param  hcomp: COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the COMP handle allocation and lock status */
  if((hcomp == HAL_NULL) || ((hcomp->State & COMP_STATE_BIT_LOCK) != RESET))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    if(hcomp->State == HAL_COMP_STATE_READY)
    {
      /* Enable the selected comparator */
      COMP_START(hcomp);

      hcomp->State = HAL_COMP_STATE_BUSY;      
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Stop the comparator 
  * @param  hcomp: COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the COMP handle allocation and lock status */
  if((hcomp == HAL_NULL) || ((hcomp->State & COMP_STATE_BIT_LOCK) != RESET))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    if(hcomp->State == HAL_COMP_STATE_BUSY)
    {
      /* Disable the selected comparator */
      COMP_STOP(hcomp);

      hcomp->State = HAL_COMP_STATE_READY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  
  return status;
}

/**
  * @brief  Enables the interrupt and starts the comparator
  * @param  hcomp: COMP handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_COMP_Start_IT(COMP_HandleTypeDef *hcomp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t extiline = 0;
  
  /* Check the parameter */
  assert_param(IS_COMP_TRIGGERMODE(hcomp->Init.TriggerMode));

  status = HAL_COMP_Start(hcomp);
  if(status == HAL_OK)
  {
    /* Check the Exti Line output configuration */
    extiline = __HAL_COMP_GET_EXTI_LINE(hcomp->Instance);
    /* Configure the rising edge */
    if((hcomp->Init.TriggerMode & COMP_TRIGGERMODE_IT_RISING) != RESET)
    {
      __HAL_COMP_EXTI_RISING_IT_ENABLE(extiline);
    }
    else
    {
      __HAL_COMP_EXTI_RISING_IT_DISABLE(extiline);
    }
    /* Configure the falling edge */
    if((hcomp->Init.TriggerMode & COMP_TRIGGERMODE_IT_FALLING) != RESET)
    {
      __HAL_COMP_EXTI_FALLING_IT_ENABLE(extiline);
    }
    else
    {
      __HAL_COMP_EXTI_FALLING_IT_DISABLE(extiline);
    }
    /* Enable Exti interrupt mode */
    __HAL_COMP_EXTI_ENABLE_IT(extiline);
    /* Clear COMP Exti pending bit */
    __HAL_COMP_EXTI_CLEAR_FLAG(extiline);    
  }

  return status;
}

/**
  * @brief  Disable the interrupt and Stop the comparator 
  * @param  hcomp: COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Stop_IT(COMP_HandleTypeDef *hcomp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Disable the Exti Line interrupt mode */
  __HAL_COMP_EXTI_DISABLE_IT(__HAL_COMP_GET_EXTI_LINE(hcomp->Instance));
  
  status = HAL_COMP_Stop(hcomp);
  
  return status;
}

/**
  * @brief  Comparator IRQ Handler 
  * @param  hcomp: COMP handle
  * @retval HAL status
  */
void HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp)
{
  uint32_t extiline = __HAL_COMP_GET_EXTI_LINE(hcomp->Instance);
  
  /* Check COMP Exti flag */
  if(__HAL_COMP_EXTI_GET_FLAG(extiline) != RESET)
  {
    /* Clear COMP Exti pending bit */
    __HAL_COMP_EXTI_CLEAR_FLAG(extiline);

    /* COMP trigger user callback */
    HAL_COMP_TriggerCallback(hcomp);    
  }  
}

/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group3 Peripheral Control functions 
 *  @brief   management functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the COMP data 
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected comparator configuration. 
  * @param  hcomp: COMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef *hcomp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the COMP handle allocation and lock status */
  if((hcomp == HAL_NULL) || ((hcomp->State & COMP_STATE_BIT_LOCK) != RESET))
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

    /* Set lock flag */
    hcomp->State |= COMP_STATE_BIT_LOCK;

    /* Set the lock bit corresponding to selected comparator */
    COMP_LOCK(hcomp);
  }
  
  return status; 
}

/**
  * @brief  Return the output level (high or low) of the selected comparator. 
  *         The output level depends on the selected polarity.
  *         If the polarity is not inverted:
  *           - Comparator output is low when the non-inverting input is at a lower
  *             voltage than the inverting input
  *           - Comparator output is high when the non-inverting input is at a higher
  *             voltage than the inverting input
  *         If the polarity is inverted:
  *           - Comparator output is high when the non-inverting input is at a lower
  *             voltage than the inverting input
  *           - Comparator output is low when the non-inverting input is at a higher
  *             voltage than the inverting input
  * @param  hcomp: COMP handle
  * @retval Returns the selected comparator output level: COMP_OUTPUTLEVEL_LOW or COMP_OUTPUTLEVEL_HIGH.
  *       
  */
uint32_t HAL_COMP_GetOutputLevel(COMP_HandleTypeDef *hcomp)
{
  uint32_t level=0;
  
  /* Check the parameter */
  assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));
  
  level = READ_BIT(hcomp->Instance->CSR, COMP_CSR_COMPxOUT);

  if(level != 0)
  {
    return(COMP_OUTPUTLEVEL_HIGH);
  }
  return(COMP_OUTPUTLEVEL_LOW);
}

/**
  * @brief  Comparator callback.
  * @param  hcomp: COMP handle
  * @retval None
  */
__weak void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_COMP_TriggerCallback should be implemented in the user file
   */
}


/**
  * @}
  */

/** @defgroup COMP_Exported_Functions_Group4 Peripheral State functions 
 *  @brief   Peripheral State functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================  
    [..]
    This subsection permit to get in run-time the status of the peripheral 
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the COMP state
  * @param  hcomp : COMP handle
  * @retval HAL state
  */
HAL_COMP_StateTypeDef HAL_COMP_GetState(COMP_HandleTypeDef *hcomp)
{
  /* Check the COMP handle allocation */
  if(hcomp == HAL_NULL)
  {
    return HAL_COMP_STATE_RESET;
  }

  /* Check the parameter */
  assert_param(IS_COMP_ALL_INSTANCE(hcomp->Instance));

  return hcomp->State;
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
