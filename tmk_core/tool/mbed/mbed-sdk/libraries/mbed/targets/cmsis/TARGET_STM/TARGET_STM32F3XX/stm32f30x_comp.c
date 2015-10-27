/**
  ******************************************************************************
  * @file    stm32f30x_comp.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the 7 analog comparators (COMP1, COMP2...COMP7) peripheral: 
  *           + Comparators configuration
  *           + Window mode control
  *
  @verbatim
   
  ==============================================================================
                        ##### COMP Peripheral features #####
  ==============================================================================
  [..]       
      The device integrates 7 analog comparators COMP1, COMP2...COMP7:
      (#) The non inverting input and inverting input can be set to GPIO pins
          as shown in table1. COMP Inputs below.
  
      (#) The COMP output is internally is available using COMP_GetOutputLevel()
          and can be set on GPIO pins. Refer to table 2. COMP Outputs below.
  
      (#) The COMP output can be redirected to embedded timers (TIM1, TIM2, TIM3...)
          Refer to table 3. COMP Outputs redirection to embedded timers below.
  
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

 [..] Table 1. COMP Inputs
 +------------------------------------------------------------------------------------------+     
 |                 |                | COMP1 | COMP2 | COMP3 | COMP4 | COMP5 | COMP6 | COMP7 |
 |-----------------|----------------|---------------|---------------------------------------|
 |                 | 1/4 VREFINT    |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | 1/2 VREFINT    |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | 3/4 VREFINT    |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 | Inverting Input | VREFINT        |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | DAC1 OUT1(PA4) |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | DAC1 OUT2(PA5) |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |  OK   |
 |                 | IO1            |  PA0  |  PA2  |  PD15 |  PE8  |  PD13 |  PD10 |  PC0  |
 |                 | IO2            |  ---  |  ---  |  PB12 |  PB2  |  PB10 |  PB15 |  ---  |
 |                 | DAC2 OUT1(PA6) |  ---  |  OK   |  ---  |  OK   |  ---  |  OK   |  ---  |
 |-----------------|----------------|-------|-------|-------|-------|-------|-------|-------|
 |  Non Inverting  | IO1            |  PA1  |  PA7  |  PB14 |  PB0  |  PD12 |  PD11 |  PA0  |
 |    Input        | IO2            |  ---  |  PA3  |  PD14 |  PE7  |  PB13 |  PB11 |  PC1  |
 +------------------------------------------------------------------------------------------+  

 [..] Table 2. COMP Outputs
 +-------------------------------------------------------+     
 | COMP1 | COMP2 | COMP3 | COMP4 | COMP5 | COMP6 | COMP7 |
 |-------|-------|-------|-------|-------|-------|-------|
 |  PA0  |  PA2  |  PB1  |  PC8  |  PC7  |  PA10 |  PC2  |
 |  PF4  |  PA7  |  ---  |  PA8  |  PA9  |  PC6  |  ---  |
 |  PA6  |  PA12 |  ---  |  ---  |  ---  |  ---  |  ---  |
 |  PA11 |  PB9  |  ---  |  ---  |  ---  |  ---  |  ---  |
 |  PB8  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
 +-------------------------------------------------------+

 [..] Table 3. COMP Outputs redirection to embedded timers
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

 [..] Table 4. COMP Outputs blanking sources
 +----------------------------------------------------------------------------------------------------------------------+
 |     COMP1      |     COMP2      |     COMP3      |     COMP4      |     COMP5      |     COMP6      |     COMP7      |
 |----------------|----------------|----------------|----------------|----------------|----------------|----------------|
 |  TIM1 OC5      |  TIM1 OC5      |  TIM1 OC5      |  TIM3 OC4      |  TIM3 OC3      |  TIM2 OC4      |  TIM1 OC5      |
 |                |                |                |                |                |                |                |
 |  TIM2 OC3      |  TIM2 OC3      |  --------      |  TIM8 OC5      |  TIM8 OC5      |  TIM8 OC5      |  TIM8 OC5      |
 |                |                |                |                |                |                |                |
 |  TIM3 OC3      |  TIM3 OC3      |  TIM2 OC4      |  TIM15 OC1     |  TIM8 BKIN     |  TIM15 OC2     |  TIM15 OC2     |
 |                |                |                |                |                |                |                |
 +----------------------------------------------------------------------------------------------------------------------+

  
                         ##### How to use this driver #####
  ==============================================================================
  [..]
  This driver provides functions to configure and program the Comparators 
  of all STM32F30x devices.
  
  To use the comparator, perform the following steps:
  
  (#) Enable the SYSCFG APB clock to get write access to comparator
      register using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  (#) Configure the comparator input in analog mode using GPIO_Init()
  
  (#) Configure the comparator output in alternate function mode
      using GPIO_Init() and use GPIO_PinAFConfig() function to map the
      comparator output to the GPIO pin
  
  (#) Configure the comparator using COMP_Init() function:
      (++) Select the inverting input
      (++) Select the non-inverting input
      (++) Select the output polarity  
      (++) Select the output redirection
      (++) Select the hysteresis level
      (++) Select the power mode
  
  (#) Enable the comparator using COMP_Cmd() function
  
  (#) If required enable the COMP interrupt by configuring and enabling
      EXTI line in Interrupt mode and selecting the desired sensitivity
      level using EXTI_Init() function. After that enable the comparator
      interrupt vector using NVIC_Init() function.

  @endverbatim
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
#include "stm32f30x_comp.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup COMP 
  * @brief COMP driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* CSR register Mask */
#define COMP_CSR_CLEAR_MASK              ((uint32_t)0x00000003)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup COMP_Private_Functions
  * @{
  */

/** @defgroup COMP_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */
   
/**
  * @brief  Deinitializes COMP peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be COMP_Selection_COMPx where x can be 1 to 7
  *          to select the COMP peripheral.
  * @param  None
  * @retval None
  */
void COMP_DeInit(uint32_t COMP_Selection)
{
  /*!< Set COMP_CSR register to reset value */
  *(__IO uint32_t *) (COMP_BASE + COMP_Selection) = ((uint32_t)0x00000000);
}

/**
  * @brief  Initializes the COMP peripheral according to the specified parameters
  *         in COMP_InitStruct
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @note   By default, PA1 is selected as COMP1 non inverting input.
  *         To use PA4 as COMP1 non inverting input call COMP_SwitchCmd() after COMP_Init()
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be COMP_Selection_COMPx where x can be 1 to 7
  *          to select the COMP peripheral.
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure that contains 
  *         the configuration information for the specified COMP peripheral.
  *           - COMP_InvertingInput specifies the inverting input of COMP
  *           - COMP_NonInvertingInput specifies the non inverting input of COMP
  *           - COMP_Output connect COMP output to selected timer
  *             input (Input capture / Output Compare Reference Clear / Break Input)
  *           - COMP_BlankingSrce specifies the blanking source of COMP
  *           - COMP_OutputPol select output polarity
  *           - COMP_Hysteresis configures COMP hysteresis value
  *           - COMP_Mode configures COMP power mode
  * @retval None
  */
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_COMP_INVERTING_INPUT(COMP_InitStruct->COMP_InvertingInput));
  assert_param(IS_COMP_NONINVERTING_INPUT(COMP_InitStruct->COMP_NonInvertingInput));
  assert_param(IS_COMP_OUTPUT(COMP_InitStruct->COMP_Output));
  assert_param(IS_COMP_BLANKING_SOURCE(COMP_InitStruct->COMP_BlankingSrce));
  assert_param(IS_COMP_OUTPUT_POL(COMP_InitStruct->COMP_OutputPol));
  assert_param(IS_COMP_HYSTERESIS(COMP_InitStruct->COMP_Hysteresis));
  assert_param(IS_COMP_MODE(COMP_InitStruct->COMP_Mode));

  /*!< Get the COMPx_CSR register value */
  tmpreg = *(__IO uint32_t *) (COMP_BASE + COMP_Selection);

  /*!< Clear the COMP1SW1, COMPxINSEL, COMPxOUTSEL, COMPxPOL, COMPxHYST and COMPxMODE bits */
  tmpreg &= (uint32_t) (COMP_CSR_CLEAR_MASK);

  /*!< Configure COMP: inverting input, output redirection, hysteresis value and power mode */
  /*!< Set COMPxINSEL bits according to COMP_InitStruct->COMP_InvertingInput value */
  /*!< Set COMPxNONINSEL bits according to COMP_InitStruct->COMP_NonInvertingInput value */
  /*!< Set COMPxBLANKING bits according to COMP_InitStruct->COMP_BlankingSrce value */
  /*!< Set COMPxOUTSEL bits according to COMP_InitStruct->COMP_Output value */
  /*!< Set COMPxPOL bit according to COMP_InitStruct->COMP_OutputPol value */
  /*!< Set COMPxHYST bits according to COMP_InitStruct->COMP_Hysteresis value */
  /*!< Set COMPxMODE bits according to COMP_InitStruct->COMP_Mode value */
  tmpreg |= (uint32_t)(COMP_InitStruct->COMP_InvertingInput | COMP_InitStruct->COMP_NonInvertingInput |
                        COMP_InitStruct->COMP_Output | COMP_InitStruct->COMP_OutputPol | COMP_InitStruct->COMP_BlankingSrce |
                        COMP_InitStruct->COMP_Hysteresis | COMP_InitStruct->COMP_Mode);

  /*!< Write to COMPx_CSR register */
  *(__IO uint32_t *) (COMP_BASE + COMP_Selection) = tmpreg;
}

/**
  * @brief  Fills each COMP_InitStruct member with its default value.
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct)
{
  COMP_InitStruct->COMP_InvertingInput = COMP_InvertingInput_1_4VREFINT;
  COMP_InitStruct->COMP_NonInvertingInput = COMP_NonInvertingInput_IO1;
  COMP_InitStruct->COMP_Output = COMP_Output_None;
  COMP_InitStruct->COMP_BlankingSrce = COMP_BlankingSrce_None;
  COMP_InitStruct->COMP_OutputPol = COMP_OutputPol_NonInverted;
  COMP_InitStruct->COMP_Hysteresis = COMP_Hysteresis_No;
  COMP_InitStruct->COMP_Mode = COMP_Mode_UltraLowPower;
}

/**
  * @brief  Enable or disable the COMP peripheral.
  * @note   If the selected comparator is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be COMP_Selection_COMPx where x can be 1 to 7
  *          to select the COMP peripheral.
  * @param  NewState: new state of the COMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  *         When enabled, the comparator compares the non inverting input with 
  *                       the inverting input and the comparison result is available
  *                       on comparator output.
  *         When disabled, the comparator doesn't perform comparison and the 
  *                        output level is low.
  * @retval None
  */
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected COMPx peripheral */
    *(__IO uint32_t *) (COMP_BASE + COMP_Selection) |= (uint32_t) (COMP_CSR_COMPxEN);
  }
  else
  {
    /* Disable the selected COMP peripheral  */
    *(__IO uint32_t *) (COMP_BASE + COMP_Selection) &= (uint32_t)(~COMP_CSR_COMPxEN);
  }
}

/**
  * @brief  Close or Open the SW1 switch.
  * @note   If the COMP1 is locked, Close/Open the SW1 switch can't be performed.
  *         To unlock the configuration, perform a system reset.  
  * @note   This switch is solely intended to redirect signals onto high
  *         impedance input, such as COMP1 non-inverting input (highly resistive switch)
  * @param  NewState: New state of the analog switch.
  *   This parameter can be 
  *     ENABLE so the SW1 is closed; PA1 is connected to PA4
  *     or DISABLE so the SW1 switch is open; PA1 is disconnected from PA4
  * @retval None
  */
void COMP_SwitchCmd(uint32_t COMP_Selection, FunctionalState NewState)
{
  /* Check the parameter */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Close SW1 switch */
    *(__IO uint32_t *) (COMP_BASE + COMP_Selection) |= (uint32_t) (COMP_CSR_COMP1SW1);
  }
  else
  {
    /* Open SW1 switch */
    *(__IO uint32_t *) (COMP_BASE + COMP_Selection) &= (uint32_t)(~COMP_CSR_COMP1SW1);
  }
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
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be COMP_Selection_COMPx where x can be 1 to 7
  *          to select the COMP peripheral.
  * @retval Returns the selected comparator output level: low or high.
  *       
  */
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection)
{
  uint32_t compout = 0x0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Check if selected comparator output is high */
  if ((*(__IO uint32_t *) (COMP_BASE + COMP_Selection) & (COMP_CSR_COMPxOUT)) != 0)
  {
    compout = COMP_OutputLevel_High;
  }
  else
  {
    compout = COMP_OutputLevel_Low;
  }

  /* Return the comparator output level */
  return (uint32_t)(compout);
}

/**
  * @}
  */

/** @defgroup COMP_Group2 Window mode control function
 *  @brief   Window mode control function 
 *
@verbatim   
 ===============================================================================
                    ##### Window mode control function #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the window mode.
  *         Window mode for comparators makes use of two comparators:
  *         COMP1 and COM2, COMP3 and COMP4, COMP5 and COMP6.
  *         In window mode, COMPx and COMPx-1 (where x can be 2, 4 or 6)
  *         non inverting inputs are connected together and only COMPx-1 non
  *         inverting input can be used.
  *         e.g When window mode enabled for COMP4, COMP3 non inverting input (PB14 or PD14)
  *             is to be used.
  * @note   If the COMPx is locked, ENABLE/DISABLE the window mode can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be COMP_Selection_COMPx where x can be 2, 4 or 6
  *          to select the COMP peripheral.
  * param   NewState: new state of the window mode.
  *   This parameter can be ENABLE or DISABLE.
  *        When enbaled, COMPx and COMPx-1 non inverting inputs are connected together.
  *        When disabled, COMPx and COMPx-1 non inverting inputs are disconnected.
  * @retval None
  */
void COMP_WindowCmd(uint32_t COMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_COMP_WINDOW(COMP_Selection));
  
  if (NewState != DISABLE)
  {
    /* Enable the window mode */
    *(__IO uint32_t *) (COMP_BASE + COMP_Selection) |= (uint32_t) COMP_CSR_COMPxWNDWEN;
  }
  else
  {
    /* Disable the window mode */
    *(__IO uint32_t *) (COMP_BASE + COMP_Selection) &= (uint32_t)(~COMP_CSR_COMPxWNDWEN);
  }
}

/**
  * @}
  */

/** @defgroup COMP_Group3 COMP configuration locking function
 *  @brief   COMP1, COMP2,...COMP7 configuration locking function
 *           COMP1, COMP2,...COMP7 configuration can be locked each separately.
 *           Unlocking is performed by system reset.
 *
@verbatim   
 ===============================================================================
                   ##### Configuration Lock function #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected comparator (COMP1/COMP2) configuration.
  * @note   Locking the configuration means that all control bits are read-only.
  *         To unlock the comparator configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be COMP_Selection_COMPx where x can be 1 to 7
  *          to select the COMP peripheral.
  * @retval None
  */
void COMP_LockConfig(uint32_t COMP_Selection)
{
  /* Check the parameter */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Set the lock bit corresponding to selected comparator */
  *(__IO uint32_t *) (COMP_BASE + COMP_Selection) |= (uint32_t) (COMP_CSR_COMPxLOCK);
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
