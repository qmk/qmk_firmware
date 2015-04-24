/**
  ******************************************************************************
  * @file    stm32f30x_opamp.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the operational amplifiers (OPAMP1,...OPAMP4) peripheral: 
  *           + OPAMP Configuration
  *           + OPAMP calibration
  *
  @verbatim
  
  ==============================================================================
                        ##### OPAMP Peripheral Features #####
  ==============================================================================
                   
  [..]
      The device integrates 4 operational amplifiers OPAMP1, OPAMP2, OPAMP3 and OPAMP4:
              
      (+) The OPAMPs non inverting input can be selected among the list shown by
          table below.
  
      (+) The OPAMPs inverting input can be selected among the list shown by
          table below.
  
      (+) The OPAMPs outputs can be internally connected to the inverting input 
          (follower mode)
      (+) The OPAMPs outputs can be internally connected to resistor feedback
          output (Programmable Gain Amplifier mode)
  
      (+) The OPAMPs outputs can be internally connected to ADC
  
      (+) The OPAMPs can be calibrated to compensate the offset compensation
  
      (+) Timer-controlled Mux for automatic switch of inverting and
          non-inverting input
  
  OPAMPs inverting/non-inverting inputs:
    +--------------------------------------------------------------+     
    |                 |        | OPAMP1 | OPAMP2 | OPAMP3 | OPAMP4 |
    |-----------------|--------|--------|--------|--------|--------|
    |                 | PGA    |  OK    |  OK    |  OK    |  OK    |
    | Inverting Input | Vout   |  OK    |  OK    |  OK    |  OK    |
    |                 | IO1    |  PC5   |  PC5   |  PB10  |  PB10  |
    |                 | IO2    |  PA3   |  PA5   |  PB2   |  PD8   |
    |-----------------|--------|--------|--------|--------|--------|
    |                 | IO1    |  PA7   |  PD14  |  PB13  |  PD11  |
    |  Non Inverting  | IO2    |  PA5   |  PB14  |  PA5   |  PB11  |
    |    Input        | IO3    |  PA3   |  PB0   |  PA1   |  PA4   |
    |                 | IO4    |  PA1   |  PA7   |  PB0   |  PB13  |
    +--------------------------------------------------------------+  
  
                        ##### How to use this driver #####
  ==============================================================================
  [..]
  This driver provides functions to configure and program the OPAMP 
  of all STM32F30x devices.
  
  To use the OPAMP, perform the following steps:
 
  (#) Enable the SYSCFG APB clock to get write access to OPAMP
      register using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  (#) Configure the OPAMP input in analog mode using GPIO_Init()
  
  (#) Configure the OPAMP using OPAMP_Init() function:
      (++) Select the inverting input
      (++) Select the non-inverting inverting input
    
  (#) Enable the OPAMP using OPAMP_Cmd() function
    
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
#include "stm32f30x_opamp.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup OPAMP 
  * @brief OPAMP driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define OPAMP_CSR_DEFAULT_MASK                    ((uint32_t)0xFFFFFF93)
#define OPAMP_CSR_TIMERMUX_MASK                   ((uint32_t)0xFFFFF8FF)
#define OPAMP_CSR_TRIMMING_MASK                   ((uint32_t)0x0000001F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup OPAMP_Private_Functions
  * @{
  */

/** @defgroup OPAMP_Group1 Initialization and Configuration functions
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
  * @brief  Deinitializes OPAMP peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the OPAMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  None
  * @retval None
  */
void OPAMP_DeInit(uint32_t OPAMP_Selection)
{
  /*!< Set OPAMP_CSR register to reset value */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) = ((uint32_t)0x00000000);
}

/**
  * @brief  Initializes the OPAMP peripheral according to the specified parameters
  *         in OPAMP_InitStruct
  * @note   If the selected OPAMP is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  OPAMP_InitStruct: pointer to an OPAMP_InitTypeDef structure that contains 
  *         the configuration information for the specified OPAMP peripheral.
  *           - OPAMP_InvertingInput specifies the inverting input of OPAMP
  *           - OPAMP_NonInvertingInput specifies the non inverting input of OPAMP
  * @retval None
  */
void OPAMP_Init(uint32_t OPAMP_Selection, OPAMP_InitTypeDef* OPAMP_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_OPAMP_INVERTING_INPUT(OPAMP_InitStruct->OPAMP_InvertingInput));
  assert_param(IS_OPAMP_NONINVERTING_INPUT(OPAMP_InitStruct->OPAMP_NonInvertingInput));

  /*!< Get the OPAMPx_CSR register value */
  tmpreg = *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection);

  /*!< Clear the inverting and non inverting bits selection bits */
  tmpreg &= (uint32_t) (OPAMP_CSR_DEFAULT_MASK);

  /*!< Configure OPAMP: inverting and non inverting inputs */
  tmpreg |= (uint32_t)(OPAMP_InitStruct->OPAMP_InvertingInput | OPAMP_InitStruct->OPAMP_NonInvertingInput);

  /*!< Write to OPAMPx_CSR register */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) = tmpreg;
}

/**
  * @brief  Fills each OPAMP_InitStruct member with its default value.
  * @param  OPAMP_InitStruct: pointer to an OPAMP_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void OPAMP_StructInit(OPAMP_InitTypeDef* OPAMP_InitStruct)
{
  OPAMP_InitStruct->OPAMP_NonInvertingInput = OPAMP_NonInvertingInput_IO1;
  OPAMP_InitStruct->OPAMP_InvertingInput = OPAMP_InvertingInput_IO1;
}

/**
  * @brief  Configure the feedback resistor gain.
  * @note   If the selected OPAMP is locked, gain configuration can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  NewState: new state of the OPAMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OPAMP_PGAConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_PGAGain, uint32_t OPAMP_PGAConnect)
{
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_OPAMP_PGAGAIN(OPAMP_PGAGain));
  assert_param(IS_OPAMP_PGACONNECT(OPAMP_PGAConnect));

  /* Reset the configuration bits */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) &= (uint32_t)(~OPAMP_CSR_PGGAIN);

  /* Set the new configuration */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) |= (uint32_t) (OPAMP_PGAGain | OPAMP_PGAConnect);
}

/**
  * @brief  Configure the OPAMP's internal reference.
  * @note   This feature is used when calibration enabled or OPAMP's reference
  *         connected to the non inverting input.
  * @note   If the selected OPAMP is locked, Vref configuration can't be performed.
  *         To unlock the configuration, perform a system reset.  
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  OPAMP_Vref: This parameter can be:
  *           OPAMP_Vref_3VDDA: OPMAP Vref = 3.3% VDDA
  *           OPAMP_Vref_10VDDA: OPMAP Vref = 10% VDDA
  *           OPAMP_Vref_50VDDA: OPMAP Vref = 50% VDDA
  *           OPAMP_Vref_90VDDA: OPMAP Vref = 90% VDDA
  * @retval None
  */
void OPAMP_VrefConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Vref)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_OPAMP_VREF(OPAMP_Vref));

  /*!< Get the OPAMPx_CSR register value */
  tmpreg = *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection);

  /*!< Clear the CALSEL bits */
  tmpreg &= (uint32_t) (~OPAMP_CSR_CALSEL);

  /*!< Configure OPAMP reference */
  tmpreg |= (uint32_t)(OPAMP_Vref);

  /*!< Write to OPAMPx_CSR register */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) = tmpreg;
}

/**
  * @brief  Connnect the internal reference to the OPAMP's non inverting input.
  * @note   If the selected OPAMP is locked, Vref configuration can't be performed.
  *         To unlock the configuration, perform a system reset.  
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  NewState: new state of the OPAMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OPAMP_VrefConnectNonInvertingInput(uint32_t OPAMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Connnect the internal reference to the OPAMP's non inverting input */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) |= (uint32_t) (OPAMP_CSR_FORCEVP);
  }
  else
  {
    /* Disconnnect the internal reference to the OPAMP's non inverting input */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) &= (uint32_t)(~OPAMP_CSR_FORCEVP);
  }
}

/**
  * @brief  Enables or disables connecting the OPAMP's internal reference to ADC.
  * @note   If the selected OPAMP is locked, Vref connection can't be performed.
  *         To unlock the configuration, perform a system reset.  
  * @param  NewState: new state of the Vrefint output.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OPAMP_VrefConnectADCCmd(uint32_t OPAMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable output internal reference */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) |= (uint32_t) (OPAMP_CSR_TSTREF);
  }
  else
  {
    /* Disable output internal reference */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) &= (uint32_t)(~OPAMP_CSR_TSTREF);
  }
}

/**
  * @brief  Configure the OPAMP peripheral (secondary inputs) for timer-controlled
  *          mux mode according to the specified parameters in OPAMP_InitStruct.
  * @note   If the selected OPAMP is locked, timer-controlled mux configuration
  *         can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  OPAMP_InitStruct: pointer to an OPAMP_InitTypeDef structure that contains 
  *         the configuration information for the specified OPAMP peripheral.
  *           - OPAMP_InvertingInput specifies the inverting input of OPAMP
  *           - OPAMP_NonInvertingInput specifies the non inverting input of OPAMP
  * @note   PGA and Vout can't be selected as seconadry inverting input.
  * @retval None
  */
void OPAMP_TimerControlledMuxConfig(uint32_t OPAMP_Selection, OPAMP_InitTypeDef* OPAMP_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_OPAMP_SECONDARY_INVINPUT(OPAMP_InitStruct->OPAMP_InvertingInput));
  assert_param(IS_OPAMP_NONINVERTING_INPUT(OPAMP_InitStruct->OPAMP_NonInvertingInput));

  /*!< Get the OPAMPx_CSR register value */
  tmpreg = *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection);

  /*!< Clear the secondary inverting bit, secondary non inverting bit and TCMEN bits */
  tmpreg &= (uint32_t) (OPAMP_CSR_TIMERMUX_MASK);

  /*!< Configure OPAMP: secondary inverting and non inverting inputs */
  tmpreg |= (uint32_t)((uint32_t)(OPAMP_InitStruct->OPAMP_InvertingInput<<3) | (uint32_t)(OPAMP_InitStruct->OPAMP_NonInvertingInput<<7));

  /*!< Write to OPAMPx_CSR register */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) = tmpreg;
}

/**
  * @brief  Enable or disable the timer-controlled mux mode.
  * @note   If the selected OPAMP is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  NewState: new state of the OPAMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OPAMP_TimerControlledMuxCmd(uint32_t OPAMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the timer-controlled Mux mode */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) |= (uint32_t) (OPAMP_CSR_TCMEN);
  }
  else
  {
    /* Disable the timer-controlled Mux mode */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) &= (uint32_t)(~OPAMP_CSR_TCMEN);
  }
}

/**
  * @brief  Enable or disable the OPAMP peripheral.
  * @note   If the selected OPAMP is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  NewState: new state of the OPAMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OPAMP_Cmd(uint32_t OPAMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected OPAMPx peripheral */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) |= (uint32_t) (OPAMP_CSR_OPAMPxEN);
  }
  else
  {
    /* Disable the selected OPAMPx peripheral */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) &= (uint32_t)(~OPAMP_CSR_OPAMPxEN);
  }
}

/**
  * @brief  Return the output level (high or low) during calibration of the selected OPAMP. 
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  *           - OPAMP output is low when the non-inverting input is at a lower
  *             voltage than the inverting input
  *           - OPAMP output is high when the non-inverting input is at a higher
  *             voltage than the inverting input
  * @note OPAMP ouput level is provided only during calibration phase.
  * @retval Returns the selected OPAMP output level: low or high.
  *       
  */
uint32_t OPAMP_GetOutputLevel(uint32_t OPAMP_Selection)
{
  uint32_t opampout = 0x0;

  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));

  /* Check if selected OPAMP output is high */
  if ((*(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) & (OPAMP_CSR_OUTCAL)) != 0)
  {
    opampout = OPAMP_OutputLevel_High;
  }
  else
  {
    opampout = OPAMP_OutputLevel_Low;
  }

  /* Return the OPAMP output level */
  return (uint32_t)(opampout);
}

/**
  * @brief  Select the trimming mode.
  * @param  OffsetTrimming: the selected offset trimming mode. 
  *   This parameter  can be one of the following values:
  *     @arg OPAMP_Trimming_Factory: factory trimming values are used for offset
  *                                  calibration
  *     @arg OPAMP_Trimming_User: user trimming values are used for offset
  *                               calibration
  * @note When OffsetTrimming_User is selected, use OPAMP_OffsetTrimConfig()
  *       function or OPAMP_OffsetTrimLowPowerConfig() function to adjust 
  *       trimming value.
  * @retval None
  */
void OPAMP_OffsetTrimModeSelect(uint32_t OPAMP_Selection, uint32_t OPAMP_Trimming)
{
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_OPAMP_TRIMMING(OPAMP_Trimming));

  /* Reset USERTRIM bit */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) &= (~(uint32_t) (OPAMP_CSR_USERTRIM));

  /* Select trimming mode */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) |= OPAMP_Trimming;
}

/**
  * @brief  Configure the trimming value of the OPAMP.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  OPAMP_Input: the selected OPAMP input. 
  *   This parameter can be one of the following values:
  *         @arg OPAMP_Input_Inverting: Inverting input is selected to configure the trimming value
  *         @arg OPAMP_Input_NonInverting: Non inverting input is selected to configure the trimming value
  * @param  OPAMP_TrimValue: the trimming value. This parameter can be any value lower
  *         or equal to 0x0000001F. 
  * @retval None
  */
void OPAMP_OffsetTrimConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_OPAMP_INPUT(OPAMP_Input));
  assert_param(IS_OPAMP_TRIMMINGVALUE(OPAMP_TrimValue));

  /*!< Get the OPAMPx_CSR register value */
  tmpreg = *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection);

  /*!< Clear the trimming bits */
  tmpreg &= ((uint32_t)~(OPAMP_CSR_TRIMMING_MASK<<OPAMP_Input));

  /*!< Configure the new trimming value */
  tmpreg |= (uint32_t)(OPAMP_TrimValue<<OPAMP_Input);

  /*!< Write to OPAMPx_CSR register */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) = tmpreg;
}

/**
  * @brief  Start or stop the calibration of selected OPAMP peripheral.
  * @note   If the selected OPAMP is locked, start/stop can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @param  NewState: new state of the OPAMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void OPAMP_StartCalibration(uint32_t OPAMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Start the OPAMPx calibration */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) |= (uint32_t) (OPAMP_CSR_CALON);
  }
  else
  {
    /* Stop the OPAMPx calibration */
    *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) &= (uint32_t)(~OPAMP_CSR_CALON);
  }
}

/**
  * @}
  */

/** @defgroup OPAMP_Group2 OPAMP configuration locking function
 *  @brief   OPAMP1,...OPAMP4 configuration locking function
 *           OPAMP1,...OPAMP4 configuration can be locked each separately.
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
  * @brief  Lock the selected OPAMP configuration.
  * @note   Locking the configuration means that all control bits are read-only.
  *         To unlock the OPAMP configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected OPAMP. 
  *          This parameter can be OPAMP_Selection_OPAMPx where x can be 1 to 4
  *          to select the OPAMP peripheral.
  * @retval None
  */
void OPAMP_LockConfig(uint32_t OPAMP_Selection)
{
  /* Check the parameter */
  assert_param(IS_OPAMP_ALL_PERIPH(OPAMP_Selection));

  /* Set the lock bit corresponding to selected OPAMP */
  *(__IO uint32_t *) (OPAMP_BASE + OPAMP_Selection) |= (uint32_t) (OPAMP_CSR_LOCK);
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
