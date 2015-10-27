/**
  ******************************************************************************
  * @file    stm32f30x_adc.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *           + Initialization and Configuration
  *           + Analog Watchdog configuration
  *           + Temperature Sensor, Vbat & Vrefint (Internal Reference Voltage) management 
  *           + Regular Channels Configuration
  *           + Regular Channels DMA Configuration
  *           + Injected channels Configuration
  *           + Interrupts and flags management
  *           + Dual mode configuration  
  *         
  @verbatim
  ==============================================================================
                             ##### How to use this driver #####
  ==============================================================================
    [..]
    (#) select the ADC clock using the function RCC_ADCCLKConfig()
    (#) Enable the ADC interface clock using RCC_AHBPeriphClockCmd();
    (#) ADC pins configuration
        (++) Enable the clock for the ADC GPIOs using the following function:
             RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);
        (++) Configure these ADC pins in analog mode using GPIO_Init();
    (#) Configure the ADC conversion resolution, data alignment, external
        trigger and edge, sequencer lenght and Enable/Disable the continuous mode
        using the ADC_Init() function.
    (#) Activate the ADC peripheral using ADC_Cmd() function.

    *** ADC channels group configuration ***
    ========================================    
    [..] 
    (+) To configure the ADC channels features, use ADC_Init(), ADC_InjectedInit()
        and/or ADC_RegularChannelConfig() functions.
    (+) To activate the continuous mode, use the ADC_ContinuousModeCmd()
        function.
    (+) To activate the Discontinuous mode, use the ADC_DiscModeCmd() functions. 
    (+) To activate the overrun mode, use the ADC_OverrunModeCmd() functions.
    (+) To activate the calibration mode, use the ADC_StartCalibration() functions.
    (+) To read the ADC converted values, use the ADC_GetConversionValue()
        function.

    *** DMA for ADC channels features configuration ***
    ===================================================     
    [..] 
    (+) To enable the DMA mode for ADC channels group, use the ADC_DMACmd() function.
    (+) To configure the DMA transfer request, use ADC_DMAConfig() function.

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
#include "stm32f30x_adc.h"
#include "stm32f30x_rcc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC 
  * @brief ADC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* CFGR register Mask */
#define CFGR_CLEAR_Mask             ((uint32_t)0xFDFFC007)

/* JSQR register Mask */
#define JSQR_CLEAR_Mask             ((uint32_t)0x00000000)

/* ADC ADON mask */
#define CCR_CLEAR_MASK              ((uint32_t)0xFFFC10E0)

/* ADC JDRx registers offset */
#define JDR_Offset                  ((uint8_t)0x80)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ADC_Private_Functions
  * @{
  */

/** @defgroup ADC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
                 ##### Initialization and Configuration functions  #####
 ===============================================================================  
  [..] 
  This section provides functions allowing to:
   (#) Initialize and configure the ADC injected and/or regular channels and dual mode.
   (#) Management of the calibration process
   (#) ADC Power-on Power-off
   (#) Single ended or differential mode 
   (#) Enabling the queue of context and the auto delay mode
   (#) The number of ADC conversions that will be done using the sequencer for regular 
       channel group
   (#) Enable or disable the ADC peripheral
   
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the ADCx peripheral registers to their default reset values.
  * @param  ADCx: where x can be 1, 2,3 or 4 to select the ADC peripheral.
  * @retval None
  */
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));


  if((ADCx == ADC1) || (ADCx == ADC2))
  {
    /* Enable ADC1/ADC2 reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ADC12, ENABLE);
    /* Release ADC1/ADC2 from reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ADC12, DISABLE);
  }
  else if((ADCx == ADC3) || (ADCx == ADC4))
  {
    /* Enable ADC3/ADC4 reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ADC34, ENABLE);
    /* Release ADC3/ADC4 from reset state */
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ADC34, DISABLE);
  }
}
/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  uint32_t tmpreg1 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CONVMODE(ADC_InitStruct->ADC_ContinuousConvMode));
  assert_param(IS_ADC_RESOLUTION(ADC_InitStruct->ADC_Resolution));
  assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrigConvEvent)); 
  assert_param(IS_EXTERNALTRIG_EDGE(ADC_InitStruct->ADC_ExternalTrigEventEdge));  
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign)); 
  assert_param(IS_ADC_OVRUNMODE(ADC_InitStruct->ADC_OverrunMode));
  assert_param(IS_ADC_AUTOINJECMODE(ADC_InitStruct->ADC_AutoInjMode));
  assert_param(IS_ADC_REGULAR_LENGTH(ADC_InitStruct->ADC_NbrOfRegChannel));

  /*---------------------------- ADCx CFGR Configuration -----------------*/
  /* Get the ADCx CFGR value */
  tmpreg1 = ADCx->CFGR;
  /* Clear SCAN bit */
  tmpreg1 &= CFGR_CLEAR_Mask; 
  /* Configure ADCx: scan conversion mode */
  /* Set SCAN bit according to ADC_ScanConvMode value */
  tmpreg1 |= (uint32_t)ADC_InitStruct->ADC_ContinuousConvMode | 
  ADC_InitStruct->ADC_Resolution|                 
  ADC_InitStruct->ADC_ExternalTrigConvEvent|         
  ADC_InitStruct->ADC_ExternalTrigEventEdge|     
  ADC_InitStruct->ADC_DataAlign|                 
  ADC_InitStruct->ADC_OverrunMode|        
  ADC_InitStruct->ADC_AutoInjMode;
  
  /* Write to ADCx CFGR */
  ADCx->CFGR = tmpreg1;
  
  /*---------------------------- ADCx SQR1 Configuration -----------------*/
  /* Get the ADCx SQR1 value */
  tmpreg1 = ADCx->SQR1;
  /* Clear L bits */
  tmpreg1 &= ~(uint32_t)(ADC_SQR1_L);
  /* Configure ADCx: regular channel sequence length */
  /* Set L bits according to ADC_NbrOfRegChannel value */
  tmpreg1 |= (uint32_t) (ADC_InitStruct->ADC_NbrOfRegChannel - 1);
  /* Write to ADCx SQR1 */
  ADCx->SQR1 = tmpreg1; 
   
}  

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @param  ADC_InitStruct : pointer to an ADC_InitTypeDef structure which will be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;
  ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;                 
  ADC_InitStruct->ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;         
  ADC_InitStruct->ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;                 
  ADC_InitStruct->ADC_OverrunMode = DISABLE;   
  ADC_InitStruct->ADC_AutoInjMode = DISABLE;  
  ADC_InitStruct->ADC_NbrOfRegChannel = 1; 
}

/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_InjectInitStruct: pointer to an ADC_InjecInitTypeDef structure that contains
  *         the configuration information for the specified ADC injected channel.
  * @retval None
  */
void ADC_InjectedInit(ADC_TypeDef* ADCx, ADC_InjectedInitTypeDef* ADC_InjectedInitStruct)
{
  uint32_t tmpreg1 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_InjectedInitStruct->ADC_ExternalTrigInjecConvEvent)); 
  assert_param(IS_EXTERNALTRIGINJ_EDGE(ADC_InjectedInitStruct->ADC_ExternalTrigInjecEventEdge));   
  assert_param(IS_ADC_INJECTED_LENGTH(ADC_InjectedInitStruct->ADC_NbrOfInjecChannel));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedInitStruct->ADC_InjecSequence1));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedInitStruct->ADC_InjecSequence2));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedInitStruct->ADC_InjecSequence3));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedInitStruct->ADC_InjecSequence4));
  
  /*---------------------------- ADCx JSQR Configuration -----------------*/
  /* Get the ADCx JSQR value */
  tmpreg1 = ADCx->JSQR;
  /* Clear L bits */
  tmpreg1 &= JSQR_CLEAR_Mask;
  /* Configure ADCx: Injected channel sequence length, external trigger, 
     external trigger edge and sequences
  */
  tmpreg1 = (uint32_t) ((ADC_InjectedInitStruct->ADC_NbrOfInjecChannel - (uint8_t)1) |
                         ADC_InjectedInitStruct->ADC_ExternalTrigInjecConvEvent |         
                         ADC_InjectedInitStruct->ADC_ExternalTrigInjecEventEdge |
                         (uint32_t)((ADC_InjectedInitStruct->ADC_InjecSequence1) << 8) |
                         (uint32_t)((ADC_InjectedInitStruct->ADC_InjecSequence2) << 14) |
                         (uint32_t)((ADC_InjectedInitStruct->ADC_InjecSequence3) << 20) |
                         (uint32_t)((ADC_InjectedInitStruct->ADC_InjecSequence4) << 26));
  /* Write to ADCx SQR1 */
  ADCx->JSQR = tmpreg1;  
}

/**
  * @brief  Fills each ADC_InjectedInitStruct member with its default value.
  * @param  ADC_InjectedInitStruct : pointer to an ADC_InjectedInitTypeDef structure which will be initialized.
  * @retval None
  */
void ADC_InjectedStructInit(ADC_InjectedInitTypeDef* ADC_InjectedInitStruct)
{
  ADC_InjectedInitStruct->ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_0;    
  ADC_InjectedInitStruct->ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_None;     
  ADC_InjectedInitStruct->ADC_NbrOfInjecChannel = 1;                                                             
  ADC_InjectedInitStruct->ADC_InjecSequence1 = ADC_InjectedChannel_1; 
  ADC_InjectedInitStruct->ADC_InjecSequence2 = ADC_InjectedChannel_1;
  ADC_InjectedInitStruct->ADC_InjecSequence3 = ADC_InjectedChannel_1;
  ADC_InjectedInitStruct->ADC_InjecSequence4 = ADC_InjectedChannel_1; 
}
    
/**
  * @brief  Initializes the ADCs peripherals according to the specified parameters 
  *         in the ADC_CommonInitStruct.
  * @param  ADCx: where x can be 1 or 4 to select the ADC peripheral.
  * @param  ADC_CommonInitStruct: pointer to an ADC_CommonInitTypeDef structure 
  *         that contains the configuration information for  All ADCs peripherals.
  * @retval None
  */
void ADC_CommonInit(ADC_TypeDef* ADCx, ADC_CommonInitTypeDef* ADC_CommonInitStruct)
{
  uint32_t tmpreg1 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_MODE(ADC_CommonInitStruct->ADC_Mode));
  assert_param(IS_ADC_CLOCKMODE(ADC_CommonInitStruct->ADC_Clock));
  assert_param(IS_ADC_DMA_MODE(ADC_CommonInitStruct->ADC_DMAMode));
  assert_param(IS_ADC_DMA_ACCESS_MODE(ADC_CommonInitStruct->ADC_DMAAccessMode));
  assert_param(IS_ADC_TWOSAMPLING_DELAY(ADC_CommonInitStruct->ADC_TwoSamplingDelay));

  if((ADCx == ADC1) || (ADCx == ADC2))
  {
    /* Get the ADC CCR value */
    tmpreg1 = ADC1_2->CCR;
  
    /* Clear MULTI, DELAY, DMA and ADCPRE bits */
    tmpreg1 &= CCR_CLEAR_MASK;
  }
  else
  {
    /* Get the ADC CCR value */
    tmpreg1 = ADC3_4->CCR;
  
    /* Clear MULTI, DELAY, DMA and ADCPRE bits */
    tmpreg1 &= CCR_CLEAR_MASK;
  }
  /*---------------------------- ADC CCR Configuration -----------------*/  
  /* Configure ADCx: Multi mode, Delay between two sampling time, ADC clock, DMA mode
     and DMA access mode for dual mode */
  /* Set MULTI bits according to ADC_Mode value */
  /* Set CKMODE bits according to ADC_Clock value */
  /* Set MDMA bits according to ADC_DMAAccessMode value */
  /* Set DMACFG bits according to ADC_DMAMode value */
  /* Set DELAY bits according to ADC_TwoSamplingDelay value */    
  tmpreg1 |= (uint32_t)(ADC_CommonInitStruct->ADC_Mode | 
                        ADC_CommonInitStruct->ADC_Clock | 
                        ADC_CommonInitStruct->ADC_DMAAccessMode | 
                        (uint32_t)(ADC_CommonInitStruct->ADC_DMAMode << 12) |
                        (uint32_t)((uint32_t)ADC_CommonInitStruct->ADC_TwoSamplingDelay << 8));

  if((ADCx == ADC1) || (ADCx == ADC2))
  {                        
    /* Write to ADC CCR */
    ADC1_2->CCR = tmpreg1;
  }
  else
  {
    /* Write to ADC CCR */
    ADC3_4->CCR = tmpreg1;
  }
}

/**
  * @brief  Fills each ADC_CommonInitStruct member with its default value.
  * @param  ADC_CommonInitStruct: pointer to an ADC_CommonInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct)
{
  /* Initialize the ADC_Mode member */
  ADC_CommonInitStruct->ADC_Mode = ADC_Mode_Independent;

  /* initialize the ADC_Clock member */
  ADC_CommonInitStruct->ADC_Clock = ADC_Clock_AsynClkMode;

  /* Initialize the ADC_DMAAccessMode member */
  ADC_CommonInitStruct->ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;

  /* Initialize the ADC_DMAMode member */
  ADC_CommonInitStruct->ADC_DMAMode = ADC_DMAMode_OneShot;

  /* Initialize the ADC_TwoSamplingDelay member */
  ADC_CommonInitStruct->ADC_TwoSamplingDelay = 0;

}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the ADCx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ADEN bit */
    ADCx->CR |= ADC_CR_ADEN;
  }
  else
  {
    /* Disable the selected ADC peripheral: Set the ADDIS bit */
    ADCx->CR |= ADC_CR_ADDIS;
  }
}

/**
  * @brief  Starts the selected ADC calibration process.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval None
  */
void ADC_StartCalibration(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Set the ADCAL bit */
  ADCx->CR |= ADC_CR_ADCAL;
}

/**
  * @brief  Returns the ADCx calibration value.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval None
  */
uint32_t ADC_GetCalibrationValue(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Return the selected ADC calibration value */
  return (uint32_t)ADCx->CALFACT;
}

/**
  * @brief  Sets the ADCx calibration register.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval None
  */
void ADC_SetCalibrationValue(ADC_TypeDef* ADCx, uint32_t ADC_Calibration)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Set the ADC calibration register value */
  ADCx->CALFACT = ADC_Calibration;
}

/**
  * @brief  Select the ADC calibration mode.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_CalibrationMode: the ADC calibration mode.
  *         This parameter can be one of the following values: 
  *          @arg ADC_CalibrationMode_Single: to select the calibration for single channel
  *          @arg ADC_CalibrationMode_Differential: to select the calibration for differential channel         
  * @retval None
  */
void ADC_SelectCalibrationMode(ADC_TypeDef* ADCx, uint32_t ADC_CalibrationMode)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CALIBRATION_MODE(ADC_CalibrationMode));
  /* Set or Reset the ADCALDIF bit */
  ADCx->CR &= (~ADC_CR_ADCALDIF);
  ADCx->CR |= ADC_CalibrationMode;

}

/**
  * @brief  Gets the selected ADC calibration status.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval The new state of ADC calibration (SET or RESET).
  */
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Check the status of CAL bit */
  if ((ADCx->CR & ADC_CR_ADCAL) != (uint32_t)RESET)
  {
    /* CAL bit is set: calibration on going */
    bitstatus = SET;
  }
  else
  {
    /* CAL bit is reset: end of calibration */
    bitstatus = RESET;
  }
  /* Return the CAL bit status */
  return  bitstatus;
}

/**
  * @brief  ADC Disable Command.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval None
  */
void ADC_DisableCmd(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Set the ADDIS bit */
  ADCx->CR |= ADC_CR_ADDIS;
}


/**
  * @brief  Gets the selected ADC disable command Status.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval The new state of ADC ADC disable command (SET or RESET).
  */
FlagStatus ADC_GetDisableCmdStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of ADDIS bit */
  if ((ADCx->CR & ADC_CR_ADDIS) != (uint32_t)RESET)
  {
    /* ADDIS bit is set */
    bitstatus = SET;
  }
  else
  {
    /* ADDIS bit is reset */
    bitstatus = RESET;
  }
  /* Return the ADDIS bit status */
  return  bitstatus;
}

/**
  * @brief  Enables or disables the specified ADC Voltage Regulator.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the ADCx Voltage Regulator.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VoltageRegulatorCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* set the intermediate state before moving the ADC voltage regulator 
  from enable state to disable state or from disable state to enable state */
  ADCx->CR &= ~(ADC_CR_ADVREGEN);
  
  if (NewState != DISABLE)
  {
    /* Set the ADVREGEN bit 0 */
    ADCx->CR |= ADC_CR_ADVREGEN_0;
  }
  else
  {
    /* Set the ADVREGEN bit 1 */
    ADCx->CR |=ADC_CR_ADVREGEN_1;
  }
}

/**
  * @brief  Selectes the differential mode for a specific channel
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure for the analog watchdog. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  * @note : Channel 15, 16 and 17 are fixed to single-ended inputs mode.
  * @retval None
  */
void ADC_SelectDifferentialMode(ADC_TypeDef* ADCx, uint8_t ADC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx)); 
  assert_param(IS_ADC_DIFFCHANNEL(ADC_Channel)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the DIFSEL bit */
   ADCx->DIFSEL |= (uint32_t)(1 << ADC_Channel );
  }
  else
  {
    /* Reset the DIFSEL bit */
   ADCx->DIFSEL &= ~(uint32_t)(1 << ADC_Channel);
  }
}

/**
  * @brief  Selects the Queue Of Context Mode for injected channels.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the Queue Of Context Mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SelectQueueOfContextMode(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the JQM bit */
    ADCx->CFGR |= (uint32_t)(ADC_CFGR_JQM );
  }
  else
  {
    /* Reset the JQM bit */
    ADCx->CFGR &= ~(uint32_t)(ADC_CFGR_JQM);
  }
}

/**
  * @brief  Selects the ADC Delayed Conversion Mode.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the ADC Delayed Conversion Mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AutoDelayCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the AUTDLY bit */
    ADCx->CFGR |= (uint32_t)(ADC_CFGR_AUTDLY );
  }
  else
  {
    /* Reset the AUTDLY bit */
    ADCx->CFGR &= ~(uint32_t)(ADC_CFGR_AUTDLY);
  }
}

/**
  * @}
  */

/** @defgroup ADC_Group2 Analog Watchdog configuration functions
 *  @brief   Analog Watchdog configuration functions 
 *
@verbatim   
 ===============================================================================
                    ##### Analog Watchdog configuration functions #####
 ===============================================================================  

  [..] This section provides functions allowing to configure the 3 Analog Watchdogs 
       (AWDG1, AWDG2 and AWDG3) in the ADC.
  
  [..] A typical configuration Analog Watchdog is done following these steps :
   (#) The ADC guarded channel(s) is (are) selected using the functions: 
      (++) ADC_AnalogWatchdog1SingleChannelConfig().
      (++) ADC_AnalogWatchdog2SingleChannelConfig().
      (++) ADC_AnalogWatchdog3SingleChannelConfig().

   (#) The Analog watchdog lower and higher threshold are configured using the functions: 
      (++) ADC_AnalogWatchdog1ThresholdsConfig().
      (++) ADC_AnalogWatchdog2ThresholdsConfig().
      (++) ADC_AnalogWatchdog3ThresholdsConfig().

   (#) The Analog watchdog is enabled and configured to enable the check, on one
      or more channels, using the function:
      (++) ADC_AnalogWatchdogCmd().

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the analog watchdog on single/all regular
  *         or injected channels
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_AnalogWatchdog: the ADC analog watchdog configuration.
  *   This parameter can be one of the following values:
  *     @arg ADC_AnalogWatchdog_SingleRegEnable: Analog watchdog on a single regular channel
  *     @arg ADC_AnalogWatchdog_SingleInjecEnable: Analog watchdog on a single injected channel
  *     @arg ADC_AnalogWatchdog_SingleRegOrInjecEnable: Analog watchdog on a single regular or injected channel
  *     @arg ADC_AnalogWatchdog_AllRegEnable: Analog watchdog on  all regular channel
  *     @arg ADC_AnalogWatchdog_AllInjecEnable: Analog watchdog on  all injected channel
  *     @arg ADC_AnalogWatchdog_AllRegAllInjecEnable: Analog watchdog on all regular and injected channels
  *     @arg ADC_AnalogWatchdog_None: No channel guarded by the analog watchdog
  * @retval None	  
  */
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_ANALOG_WATCHDOG(ADC_AnalogWatchdog));
  /* Get the old register value */
  tmpreg = ADCx->CFGR;
  /* Clear AWDEN, AWDENJ and AWDSGL bits */
  tmpreg &= ~(uint32_t)(ADC_CFGR_AWD1SGL|ADC_CFGR_AWD1EN|ADC_CFGR_JAWD1EN);
  /* Set the analog watchdog enable mode */
  tmpreg |= ADC_AnalogWatchdog;
  /* Store the new register value */
  ADCx->CFGR = tmpreg;
}

/**
  * @brief  Configures the high and low thresholds of the analog watchdog1.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *   This parameter must be a 12bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWatchdog1ThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,
                                         uint16_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));
  /* Set the ADCx high threshold */
  ADCx->TR1 &= ~(uint32_t)ADC_TR1_HT1;
  ADCx->TR1 |= (uint32_t)((uint32_t)HighThreshold << 16);

  /* Set the ADCx low threshold */
  ADCx->TR1 &= ~(uint32_t)ADC_TR1_LT1;
  ADCx->TR1 |= LowThreshold;
}

/**
  * @brief  Configures the high and low thresholds of the analog watchdog2.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *   This parameter must be a 8bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *   This parameter must be a 8bit value.
  * @retval None
  */
void ADC_AnalogWatchdog2ThresholdsConfig(ADC_TypeDef* ADCx, uint8_t HighThreshold,
                                         uint8_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  /* Set the ADCx high threshold */
  ADCx->TR2 &= ~(uint32_t)ADC_TR2_HT2;
  ADCx->TR2 |= (uint32_t)((uint32_t)HighThreshold << 16);

  /* Set the ADCx low threshold */
  ADCx->TR2 &= ~(uint32_t)ADC_TR2_LT2;
  ADCx->TR2 |= LowThreshold;
}

/**
  * @brief  Configures the high and low thresholds of the analog watchdog3.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *   This parameter must be a 8bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *   This parameter must be a 8bit value.
  * @retval None
  */
void ADC_AnalogWatchdog3ThresholdsConfig(ADC_TypeDef* ADCx, uint8_t HighThreshold,
                                         uint8_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Set the ADCx high threshold */
  ADCx->TR3 &= ~(uint32_t)ADC_TR3_HT3;
  ADCx->TR3 |= (uint32_t)((uint32_t)HighThreshold << 16);

  /* Set the ADCx low threshold */
  ADCx->TR3 &= ~(uint32_t)ADC_TR3_LT3;
  ADCx->TR3 |= LowThreshold;
}

/**
  * @brief  Configures the analog watchdog 2 guarded single channel
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure for the analog watchdog. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  *     @arg ADC_Channel_18: ADC Channel18 selected
  * @retval None
  */
void ADC_AnalogWatchdog1SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  /* Get the old register value */
  tmpreg = ADCx->CFGR;
  /* Clear the Analog watchdog channel select bits */
  tmpreg &= ~(uint32_t)ADC_CFGR_AWD1CH;
  /* Set the Analog watchdog channel */
  tmpreg |= (uint32_t)((uint32_t)ADC_Channel << 26);
  /* Store the new register value */
  ADCx->CFGR = tmpreg;
}

/**
  * @brief  Configures the analog watchdog 2 guarded single channel
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure for the analog watchdog. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  *     @arg ADC_Channel_18: ADC Channel18 selected
  * @retval None
  */
void ADC_AnalogWatchdog2SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  /* Get the old register value */
  tmpreg = ADCx->AWD2CR;
  /* Clear the Analog watchdog channel select bits */
  tmpreg &= ~(uint32_t)ADC_AWD2CR_AWD2CH;
  /* Set the Analog watchdog channel */
  tmpreg |= (uint32_t)1 << (ADC_Channel);
  /* Store the new register value */
  ADCx->AWD2CR |= tmpreg;
}

/**
  * @brief  Configures the analog watchdog 3 guarded single channel
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure for the analog watchdog. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  *     @arg ADC_Channel_18: ADC Channel18 selected
  * @retval None
  */
void ADC_AnalogWatchdog3SingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  /* Get the old register value */
  tmpreg = ADCx->AWD3CR;
  /* Clear the Analog watchdog channel select bits */
  tmpreg &= ~(uint32_t)ADC_AWD3CR_AWD3CH;
  /* Set the Analog watchdog channel */
  tmpreg |= (uint32_t)1 << (ADC_Channel);
  /* Store the new register value */
  ADCx->AWD3CR |= tmpreg;
}

/**
  * @}
  */

/** @defgroup ADC_Group3 Temperature Sensor - Vrefint (Internal Reference Voltage) and VBAT management functions
 *  @brief   Vbat, Temperature Sensor & Vrefint (Internal Reference Voltage) management function 
 *
@verbatim   
 ====================================================================================================
  ##### Temperature Sensor - Vrefint (Internal Reference Voltage) and VBAT management functions #####
 ====================================================================================================  

  [..] This section provides a function allowing to enable/ disable the internal 
  connections between the ADC and the Vbat/2, Temperature Sensor and the Vrefint source.

  [..] A typical configuration to get the Temperature sensor and Vrefint channels 
  voltages is done following these steps :
   (#) Enable the internal connection of Vbat/2, Temperature sensor and Vrefint sources 
       with the ADC channels using:
      (++) ADC_TempSensorCmd()  
      (++) ADC_VrefintCmd() 
      (++) ADC_VbatCmd()  

   (#) select the ADC_Channel_TempSensor and/or ADC_Channel_Vrefint and/or ADC_Channel_Vbat using 
      (++) ADC_RegularChannelConfig() or  
      (++) ADC_InjectedInit() functions 

   (#) Get the voltage values, using:
      (++) ADC_GetConversionValue() or  
      (++) ADC_GetInjectedConversionValue().
 
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the temperature sensor channel.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  NewState: new state of the temperature sensor.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TempSensorCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
   {
     /* Enable the temperature sensor channel*/
     ADC1_2->CCR |= ADC12_CCR_TSEN;
   }
  else
   {
     /* Disable the temperature sensor channel*/
     ADC1_2->CCR &= ~(uint32_t)ADC12_CCR_TSEN;
   }
}

/**
  * @brief  Enables or disables the Vrefint channel.
  * @param  ADCx: where x can be 1 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the Vrefint.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VrefintCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if((ADCx == ADC1) || (ADCx == ADC2))
  {
    if (NewState != DISABLE)
    {
      /* Enable the Vrefint channel*/
      ADC1_2->CCR |= ADC12_CCR_VREFEN;
    }
    else
    {
      /* Disable the Vrefint channel*/
      ADC1_2->CCR &= ~(uint32_t)ADC12_CCR_VREFEN;
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Enable the Vrefint channel*/
      ADC3_4->CCR |= ADC34_CCR_VREFEN;
    }
    else
    {
      /* Disable the Vrefint channel*/
      ADC3_4->CCR &= ~(uint32_t)ADC34_CCR_VREFEN;
    }
  }
}

/**
  * @brief  Enables or disables the Vbat channel.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  NewState: new state of the Vbat.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VbatCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
   {
     /* Enable the Vbat channel*/
     ADC1_2->CCR |= ADC12_CCR_VBATEN;
   }
  else
   {
     /* Disable the Vbat channel*/
     ADC1_2->CCR &= ~(uint32_t)ADC12_CCR_VBATEN;
   }
}

/**
  * @}
  */

/** @defgroup ADC_Group4 Regular Channels Configuration functions
 *  @brief   Regular Channels Configuration functions 
 *
@verbatim   
 ===============================================================================
                  ##### Channels Configuration functions #####
 ===============================================================================  

  [..] This section provides functions allowing to manage the ADC regular channels.
   
  [..] To configure a regular sequence of channels use:
   (#) ADC_RegularChannelConfig()
       this fuction allows:
       (++) Configure the rank in the regular group sequencer for each channel
       (++) Configure the sampling time for each channel

   (#) ADC_RegularChannelSequencerLengthConfig() to set the length of the regular sequencer

   [..] The regular trigger is configured using the following functions:
   (#) ADC_SelectExternalTrigger()
   (#) ADC_ExternalTriggerPolarityConfig()

   [..] The start and the stop conversion are controlled by:
   (#) ADC_StartConversion()
   (#) ADC_StopConversion()
    
   [..] 
   (@)Please Note that the following features for regular channels are configurated
     using the ADC_Init() function : 
          (++) continuous mode activation
          (++) Resolution  
          (++) Data Alignement 
          (++) Overrun Mode.
     
  [..] Get the conversion data: This subsection provides an important function in 
     the ADC peripheral since it returns the converted data of the current 
     regular channel. When the Conversion value is read, the EOC Flag is 
     automatically cleared.

  [..] To configure the  discontinous mode, the following functions should be used:
   (#) ADC_DiscModeChannelCountConfig() to configure the number of discontinuous channel to be converted.
   (#) ADC_DiscModeCmd() to enable the discontinuous mode.

  [..] To configure and enable/disable the Channel offset use the functions:
     (++) ADC_SetChannelOffset1()
     (++) ADC_SetChannelOffset2()
     (++) ADC_SetChannelOffset3()
     (++) ADC_SetChannelOffset4()
     (++) ADC_ChannelOffset1Cmd()
     (++) ADC_ChannelOffset2Cmd()
     (++) ADC_ChannelOffset3Cmd()
     (++) ADC_ChannelOffset4Cmd()
  
@endverbatim
  * @{
  */

/**
  * @brief  Configures for the selected ADC regular channel its corresponding
  *         rank in the sequencer and its sample time.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  *     @arg ADC_Channel_18: ADC Channel18 selected
  * @param  Rank: The rank in the regular group sequencer. This parameter must be between 1 to 16.
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel. 
  *   This parameter can be one of the following values:
  *     @arg ADC_SampleTime_1Cycles5: Sample time equal to 1.5 cycles
  *     @arg ADC_SampleTime_2Cycles5: Sample time equal to 2.5 cycles
  *     @arg ADC_SampleTime_4Cycles5: Sample time equal to 4.5 cycles
  *     @arg ADC_SampleTime_7Cycles5: Sample time equal to 7.5 cycles	
  *     @arg ADC_SampleTime_19Cycles5: Sample time equal to 19.5 cycles	
  *     @arg ADC_SampleTime_61Cycles5: Sample time equal to 61.5 cycles	
  *     @arg ADC_SampleTime_181Cycles5: Sample time equal to 181.5 cycles	
  *     @arg ADC_SampleTime_601Cycles5: Sample time equal to 601.5 cycles	
  * @retval None
  */
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

  /* Regular sequence configuration */
  /* For Rank 1 to 4 */
  if (Rank < 5)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR1;
    /* Calculate the mask to clear */
    tmpreg2 = 0x1F << (6 * (Rank ));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)(ADC_Channel) << (6 * (Rank));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR1 = tmpreg1;
  }
  /* For Rank 5 to 9 */
  else if (Rank < 10)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR2;
    /* Calculate the mask to clear */
    tmpreg2 = ADC_SQR2_SQ5 << (6 * (Rank - 5));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)(ADC_Channel) << (6 * (Rank - 5));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR2 = tmpreg1;
  }
  /* For Rank 10 to 14 */
  else if (Rank < 15)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR3;
    /* Calculate the mask to clear */
    tmpreg2 = ADC_SQR3_SQ10 << (6 * (Rank - 10));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)(ADC_Channel) << (6 * (Rank - 10));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR3 = tmpreg1;
  }
  else 
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR4;
    /* Calculate the mask to clear */
    tmpreg2 = ADC_SQR3_SQ15 << (6 * (Rank - 15));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)(ADC_Channel) << (6 * (Rank - 15));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR4 = tmpreg1;
  }

  /* Channel sampling configuration */
  /* if ADC_Channel_10 ... ADC_Channel_18 is selected */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR2;
    /* Calculate the mask to clear */
    tmpreg2 = ADC_SMPR2_SMP10 << (3 * (ADC_Channel - 10));
    /* Clear the old channel sample time */
	ADCx->SMPR2 &= ~tmpreg2;
    /* Calculate the mask to set */
	ADCx->SMPR2 |= (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));

  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR1;
    /* Calculate the mask to clear */
    tmpreg2 = ADC_SMPR1_SMP1 << (3 * (ADC_Channel - 1));
    /* Clear the old channel sample time */
	ADCx->SMPR1 &= ~tmpreg2;
    /* Calculate the mask to set */
	ADCx->SMPR1 |= (uint32_t)ADC_SampleTime << (3 * (ADC_Channel));
  }
}

/**
  * @brief  Sets the ADC regular channel sequence lenght.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  SequenceLength: The Regular sequence length. This parameter must be between 1 to 16.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_RegularChannelSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t SequencerLength)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Configure the ADC sequence lenght */  
  ADCx->SQR1 &= ~(uint32_t)ADC_SQR1_L;
  ADCx->SQR1 |= (uint32_t)(SequencerLength - 1);   
}

/**
  * @brief  External Trigger Enable and Polarity Selection for regular channels.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_ExternalTrigConvEvent: ADC external Trigger source.
  *   This parameter can be one of the following values:
  *     @arg ADC_ExternalTrigger_Event0: External trigger event 0 
  *     @arg ADC_ExternalTrigger_Event1: External trigger event 1
  *     @arg ADC_ExternalTrigger_Event2: External trigger event 2
  *     @arg ADC_ExternalTrigger_Event3: External trigger event 3
  *     @arg ADC_ExternalTrigger_Event4: External trigger event 4 
  *     @arg ADC_ExternalTrigger_Event5: External trigger event 5
  *     @arg ADC_ExternalTrigger_Event6: External trigger event 6
  *     @arg ADC_ExternalTrigger_Event7: External trigger event 7
  *     @arg ADC_ExternalTrigger_Event8: External trigger event 8 
  *     @arg ADC_ExternalTrigger_Event9: External trigger event 9
  *     @arg ADC_ExternalTrigger_Event10: External trigger event 10
  *     @arg ADC_ExternalTrigger_Event11: External trigger event 11
  *     @arg ADC_ExternalTrigger_Event12: External trigger event 12 
  *     @arg ADC_ExternalTrigger_Event13: External trigger event 13
  *     @arg ADC_ExternalTrigger_Event14: External trigger event 14
  *     @arg ADC_ExternalTrigger_Event15: External trigger event 15	  
  * @param  ADC_ExternalTrigEventEdge: ADC external Trigger Polarity.
  *   This parameter can be one of the following values:
  *     @arg ADC_ExternalTrigEventEdge_OFF: Hardware trigger detection disabled 
  *                                          (conversions can be launched by software)
  *     @arg ADC_ExternalTrigEventEdge_RisingEdge: Hardware trigger detection on the rising edge
  *     @arg ADC_ExternalTrigEventEdge_FallingEdge: Hardware trigger detection on the falling edge
  *     @arg ADC_ExternalTrigEventEdge_BothEdge: Hardware trigger detection on both the rising and falling edges	
  * @retval None
  */
void ADC_ExternalTriggerConfig(ADC_TypeDef* ADCx, uint16_t ADC_ExternalTrigConvEvent, uint16_t ADC_ExternalTrigEventEdge)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_EXT_TRIG(ADC_ExternalTrigConvEvent));
  assert_param(IS_EXTERNALTRIG_EDGE(ADC_ExternalTrigEventEdge));

  /* Disable the selected ADC conversion on external event */
  ADCx->CFGR &= ~(ADC_CFGR_EXTEN | ADC_CFGR_EXTSEL);
  ADCx->CFGR |= (uint32_t)(ADC_ExternalTrigEventEdge | ADC_ExternalTrigConvEvent);
}

/**
  * @brief  Enables or disables the selected ADC start conversion .
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval None
  */
void ADC_StartConversion(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Set the ADSTART bit */
  ADCx->CR |= ADC_CR_ADSTART;
}

/**
  * @brief  Gets the selected ADC start conversion Status.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval The new state of ADC start conversion (SET or RESET).
  */
FlagStatus ADC_GetStartConversionStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Check the status of ADSTART bit */
  if ((ADCx->CR & ADC_CR_ADSTART) != (uint32_t)RESET)
  {
    /* ADSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* ADSTART bit is reset */
    bitstatus = RESET;
  }
  /* Return the ADSTART bit status */
  return  bitstatus;
}

/**
  * @brief  Stops the selected ADC ongoing conversion.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval None
  */
void ADC_StopConversion(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Set the ADSTP bit */
   ADCx->CR |= ADC_CR_ADSTP;
}


/**
  * @brief  Configures the discontinuous mode for the selected ADC regular
  *         group channel.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  Number: specifies the discontinuous mode regular channel
  *         count value. This number must be between 1 and 8.
  * @retval None
  */
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_REGULAR_DISC_NUMBER(Number));
  /* Get the old register value */
  tmpreg1 = ADCx->CFGR;
  /* Clear the old discontinuous mode channel count */
  tmpreg1 &= ~(uint32_t)(ADC_CFGR_DISCNUM);
  /* Set the discontinuous mode channel count */
  tmpreg2 = Number - 1;
  tmpreg1 |= tmpreg2 << 17;
  /* Store the new register value */
  ADCx->CFGR = tmpreg1;
}

/**
  * @brief  Enables or disables the discontinuous mode on regular group
  *         channel for the specified ADC
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC discontinuous mode
  *         on regular group channel.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC regular discontinuous mode */
    ADCx->CFGR |= ADC_CFGR_DISCEN;
  }
  else
  {
    /* Disable the selected ADC regular discontinuous mode */
    ADCx->CFGR &= ~(uint32_t)(ADC_CFGR_DISCEN);
  }
}

/**
  * @brief  Returns the last ADCx conversion result data for regular channel.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Return the selected ADC conversion value */
  return (uint16_t) ADCx->DR;
}

/**
  * @brief  Returns the last ADC1, ADC2, ADC3 and ADC4 regular conversions results 
  *         data in the selected dual mode.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.  
  * @retval The Data conversion value.
  * @note   In dual mode, the value returned by this function is as following
  *           Data[15:0] : these bits contain the regular data of the Master ADC.
  *           Data[31:16]: these bits contain the regular data of the Slave ADC.           
  */
uint32_t ADC_GetDualModeConversionValue(ADC_TypeDef* ADCx)
{
  uint32_t tmpreg1 = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  if((ADCx == ADC1) || (ADCx== ADC2))
  {
    /* Get the dual mode conversion value */
    tmpreg1 = ADC1_2->CDR;
  }
  else
  {	
    /* Get the dual mode conversion value */
    tmpreg1 = ADC3_4->CDR;
  }
  /* Return the dual mode conversion value */
  return (uint32_t) tmpreg1;
}

/**
  * @brief  Set the ADC channels conversion value offset1
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  *     @arg ADC_Channel_18: ADC Channel18 selected
  * @param  Offset: the offset value for the selected ADC Channel
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_SetChannelOffset1(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_OFFSET(Offset));
    
  /* Select the Channel */
  ADCx->OFR1 &= ~ (uint32_t) ADC_OFR1_OFFSET1_CH;
  ADCx->OFR1 |=	(uint32_t)((uint32_t)ADC_Channel << 26);

  /* Set the data offset */
  ADCx->OFR1 &= ~ (uint32_t) ADC_OFR1_OFFSET1;
  ADCx->OFR1 |= (uint32_t)Offset;
}

/**
  * @brief  Set the ADC channels conversion value offset2
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  *     @arg ADC_Channel_18: ADC Channel18 selected
  * @param  Offset: the offset value for the selected ADC Channel
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_SetChannelOffset2(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_OFFSET(Offset));
    
  /* Select the Channel */
  ADCx->OFR2 &= ~ (uint32_t) ADC_OFR2_OFFSET2_CH;
  ADCx->OFR2 |=	(uint32_t)((uint32_t)ADC_Channel << 26);

  /* Set the data offset */
  ADCx->OFR2 &= ~ (uint32_t) ADC_OFR2_OFFSET2;
  ADCx->OFR2 |= (uint32_t)Offset;
}

/**
  * @brief  Set the ADC channels conversion value offset3
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  *     @arg ADC_Channel_18: ADC Channel18 selected
  * @param  Offset: the offset value for the selected ADC Channel
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_SetChannelOffset3(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_OFFSET(Offset));
    
  /* Select the Channel */
  ADCx->OFR3 &= ~ (uint32_t) ADC_OFR3_OFFSET3_CH;
  ADCx->OFR3 |=	(uint32_t)((uint32_t)ADC_Channel << 26);

  /* Set the data offset */
  ADCx->OFR3 &= ~ (uint32_t) ADC_OFR3_OFFSET3;
  ADCx->OFR3 |= (uint32_t)Offset;
}

/**
  * @brief  Set the ADC channels conversion value offset4
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *   This parameter can be one of the following values:
  *     @arg ADC_Channel_1: ADC Channel1 selected
  *     @arg ADC_Channel_2: ADC Channel2 selected
  *     @arg ADC_Channel_3: ADC Channel3 selected
  *     @arg ADC_Channel_4: ADC Channel4 selected
  *     @arg ADC_Channel_5: ADC Channel5 selected
  *     @arg ADC_Channel_6: ADC Channel6 selected
  *     @arg ADC_Channel_7: ADC Channel7 selected
  *     @arg ADC_Channel_8: ADC Channel8 selected
  *     @arg ADC_Channel_9: ADC Channel9 selected
  *     @arg ADC_Channel_10: ADC Channel10 selected
  *     @arg ADC_Channel_11: ADC Channel11 selected
  *     @arg ADC_Channel_12: ADC Channel12 selected
  *     @arg ADC_Channel_13: ADC Channel13 selected
  *     @arg ADC_Channel_14: ADC Channel14 selected
  *     @arg ADC_Channel_15: ADC Channel15 selected
  *     @arg ADC_Channel_16: ADC Channel16 selected
  *     @arg ADC_Channel_17: ADC Channel17 selected
  *     @arg ADC_Channel_18: ADC Channel18 selected
  * @param  Offset: the offset value for the selected ADC Channel
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_SetChannelOffset4(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint16_t Offset)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_OFFSET(Offset));
    
  /* Select the Channel */
  ADCx->OFR4 &= ~ (uint32_t) ADC_OFR4_OFFSET4_CH;
  ADCx->OFR4 |=	(uint32_t)((uint32_t)ADC_Channel << 26);

  /* Set the data offset */
  ADCx->OFR4 &= ~ (uint32_t) ADC_OFR4_OFFSET4;
  ADCx->OFR4 |= (uint32_t)Offset;
}

/**
  * @brief  Enables or disables the Offset1.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the ADCx offset1.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ChannelOffset1Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the OFFSET1_EN bit */
    ADCx->OFR1 |= ADC_OFR1_OFFSET1_EN;
  }
  else
  {
    /* Reset the OFFSET1_EN bit */
    ADCx->OFR1 &= ~(ADC_OFR1_OFFSET1_EN);
  }
}

/**
  * @brief  Enables or disables the Offset2.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the ADCx offset2.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ChannelOffset2Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the OFFSET1_EN bit */
    ADCx->OFR2 |= ADC_OFR2_OFFSET2_EN;
  }
  else
  {
    /* Reset the OFFSET1_EN bit */
    ADCx->OFR2 &= ~(ADC_OFR2_OFFSET2_EN);
  }
}

/**
  * @brief  Enables or disables the Offset3.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the ADCx offset3.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ChannelOffset3Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the OFFSET1_EN bit */
    ADCx->OFR3 |= ADC_OFR3_OFFSET3_EN;
  }
  else
  {
    /* Reset the OFFSET1_EN bit */
    ADCx->OFR3 &= ~(ADC_OFR3_OFFSET3_EN);
  }
}

/**
  * @brief  Enables or disables the Offset4.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the ADCx offset4.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ChannelOffset4Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the OFFSET1_EN bit */
    ADCx->OFR4 |= ADC_OFR4_OFFSET4_EN;
  }
  else
  {
    /* Reset the OFFSET1_EN bit */
    ADCx->OFR4 &= ~(ADC_OFR4_OFFSET4_EN);
  }
}

/**
  * @}
  */

/** @defgroup ADC_Group5 Regular Channels DMA Configuration functions
 *  @brief   Regular Channels DMA Configuration functions 
 *
@verbatim   
 ===============================================================================
                   ##### Regular Channels DMA Configuration functions #####
 ===============================================================================  

  [..] This section provides functions allowing to configure the DMA for ADC regular 
  channels. Since converted regular channel values are stored into a unique data register, 
  it is useful to use DMA for conversion of more than one regular channel. This 
  avoids the loss of the data already stored in the ADC Data register. 
  
  (#) ADC_DMACmd() function is used to enable the ADC DMA mode, after each
      conversion of a regular channel, a DMA request is generated.
  (#) ADC_DMAConfig() function is used to select between the one shot DMA mode 
      or the circular DMA mode

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified ADC DMA request.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC DMA transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_DMA_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC DMA request */
    ADCx->CFGR |= ADC_CFGR_DMAEN;
  }
  else
  {
    /* Disable the selected ADC DMA request */
    ADCx->CFGR &= ~(uint32_t)ADC_CFGR_DMAEN;
  }
}

/**
  * @brief  Configure ADC DMA mode.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_DMAMode: select the ADC DMA mode.
  *   This parameter can be one of the following values:
  *     @arg ADC_DMAMode_OneShot: ADC DMA Oneshot mode
  *     @arg ADC_DMAMode_Circular: ADC DMA circular mode
  * @retval None
  */
void ADC_DMAConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMAMode)
{
  /* Check the parameters */
  assert_param(IS_ADC_DMA_PERIPH(ADCx));
  assert_param(IS_ADC_DMA_MODE(ADC_DMAMode));

  /* Set or reset the DMACFG bit */
   ADCx->CFGR &= ~(uint32_t)ADC_CFGR_DMACFG;
   ADCx->CFGR |= ADC_DMAMode;
}

/**
  * @}
  */

/** @defgroup ADC_Group6 Injected channels Configuration functions
 *  @brief   Injected channels Configuration functions 
 *
@verbatim   
 ===============================================================================
                     ##### Injected channels Configuration functions #####
 ===============================================================================  

  [..] This section provide functions allowing to manage the ADC Injected channels,
  it is composed of : 
    
   (#) Configuration functions for Injected channels sample time
   (#) Functions to start and stop the injected conversion
   (#) unction to select the discontinuous mode    
   (#) Function to get the Specified Injected channel conversion data: This subsection 
      provides an important function in the ADC peripheral since it returns the 
      converted data of the specific injected channel.

@endverbatim
  * @{
  */ 

/**
  * @brief  Configures for the selected ADC injected channel its corresponding
  *         sample time.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *   This parameter can be one of the following values:
  *     @arg ADC_InjectedChannel_1: ADC Channel1 selected
  *     @arg ADC_InjectedChannel_2: ADC Channel2 selected
  *     @arg ADC_InjectedChannel_3: ADC Channel3 selected
  *     @arg ADC_InjectedChannel_4: ADC Channel4 selected
  *     @arg ADC_InjectedChannel_5: ADC Channel5 selected
  *     @arg ADC_InjectedChannel_6: ADC Channel6 selected
  *     @arg ADC_InjectedChannel_7: ADC Channel7 selected
  *     @arg ADC_InjectedChannel_8: ADC Channel8 selected
  *     @arg ADC_InjectedChannel_9: ADC Channel9 selected
  *     @arg ADC_InjectedChannel_10: ADC Channel10 selected
  *     @arg ADC_InjectedChannel_11: ADC Channel11 selected
  *     @arg ADC_InjectedChannel_12: ADC Channel12 selected
  *     @arg ADC_InjectedChannel_13: ADC Channel13 selected
  *     @arg ADC_InjectedChannel_14: ADC Channel14 selected
  *     @arg ADC_InjectedChannel_15: ADC Channel15 selected
  *     @arg ADC_InjectedChannel_16: ADC Channel16 selected
  *     @arg ADC_InjectedChannel_17: ADC Channel17 selected
  *     @arg ADC_InjectedChannel_18: ADC Channel18 selected
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel. 
  *   This parameter can be one of the following values:
  *     @arg ADC_SampleTime_1Cycles5: Sample time equal to 1.5 cycles
  *     @arg ADC_SampleTime_2Cycles5: Sample time equal to 2.5 cycles
  *     @arg ADC_SampleTime_4Cycles5: Sample time equal to 4.5 cycles
  *     @arg ADC_SampleTime_7Cycles5: Sample time equal to 7.5 cycles	
  *     @arg ADC_SampleTime_19Cycles5: Sample time equal to 19.5 cycles	
  *     @arg ADC_SampleTime_61Cycles5: Sample time equal to 61.5 cycles	
  *     @arg ADC_SampleTime_181Cycles5: Sample time equal to 181.5 cycles	
  *     @arg ADC_SampleTime_601Cycles5: Sample time equal to 601.5 cycles	
  * @retval None
  */
void ADC_InjectedChannelSampleTimeConfig(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

  /* Channel sampling configuration */
  /* if ADC_InjectedChannel_10 ... ADC_InjectedChannel_18 is selected */
  if (ADC_InjectedChannel > ADC_InjectedChannel_9)
  {
    /* Calculate the mask to clear */
    tmpreg1 = ADC_SMPR2_SMP10 << (3 * (ADC_InjectedChannel - 10));
    /* Clear the old channel sample time */
	ADCx->SMPR2 &= ~tmpreg1;
    /* Calculate the mask to set */
	ADCx->SMPR2 |= (uint32_t)ADC_SampleTime << (3 * (ADC_InjectedChannel - 10));

  }
  else /* ADC_InjectedChannel include in ADC_InjectedChannel_[0..9] */
  {
    /* Calculate the mask to clear */
    tmpreg1 = ADC_SMPR1_SMP1 << (3 * (ADC_InjectedChannel - 1));
    /* Clear the old channel sample time */
	ADCx->SMPR1 &= ~tmpreg1;
    /* Calculate the mask to set */
	ADCx->SMPR1 |= (uint32_t)ADC_SampleTime << (3 * (ADC_InjectedChannel));
  }  
}

/**
  * @brief  Enables or disables the selected ADC start of the injected 
  *         channels conversion.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC software start injected conversion.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_StartInjectedConversion(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Enable the selected ADC conversion for injected group on external event and start the selected
     ADC injected conversion */
  ADCx->CR |= ADC_CR_JADSTART;
}

/**
  * @brief  Stops the selected ADC ongoing injected conversion.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval None
  */
void ADC_StopInjectedConversion(ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Set the JADSTP bit */
   ADCx->CR |= ADC_CR_JADSTP;
}

/**
  * @brief  Gets the selected ADC Software start injected conversion Status.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @retval The new state of ADC start injected conversion (SET or RESET).
  */
FlagStatus ADC_GetStartInjectedConversionStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Check the status of JADSTART bit */
  if ((ADCx->CR & ADC_CR_JADSTART) != (uint32_t)RESET)
  {
    /* JADSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* JADSTART bit is reset */
    bitstatus = RESET;
  }
  /* Return the JADSTART bit status */
  return  bitstatus;
}

/**
  * @brief  Enables or disables the selected ADC automatic injected group
  *         conversion after regular one.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC auto injected conversion
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC automatic injected group conversion */
    ADCx->CFGR |= ADC_CFGR_JAUTO;
  }
  else
  {
    /* Disable the selected ADC automatic injected group conversion */
    ADCx->CFGR &= ~ADC_CFGR_JAUTO;
  }
}

/**
  * @brief  Enables or disables the discontinuous mode for injected group
  *         channel for the specified ADC
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  NewState: new state of the selected ADC discontinuous mode
  *         on injected group channel.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC injected discontinuous mode */
    ADCx->CFGR |= ADC_CFGR_JDISCEN;
  }
  else
  {
    /* Disable the selected ADC injected discontinuous mode */
    ADCx->CFGR &= ~ADC_CFGR_JDISCEN;
  }
}

/**
  * @brief  Returns the ADC injected channel conversion result
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_InjectedSequence: the converted ADC injected sequence.
  *   This parameter can be one of the following values:
  *     @arg ADC_InjectedSequence_1: Injected Sequence1 selected
  *     @arg ADC_InjectedSequence_2: Injected Sequence2 selected
  *     @arg ADC_InjectedSequence_3: Injected Sequence3 selected
  *     @arg ADC_InjectedSequence_4: Injected Sequence4 selected
  * @retval The Data conversion value.
  */
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedSequence)
{
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_SEQUENCE(ADC_InjectedSequence));

  tmp = (uint32_t)ADCx;
  tmp += ((ADC_InjectedSequence - 1 )<< 2) + JDR_Offset;
  
  /* Returns the selected injected channel conversion data value */
  return (uint16_t) (*(__IO uint32_t*)  tmp);   
}

/**
  * @}
  */

/** @defgroup ADC_Group7 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
                   ##### Interrupts and flags management functions #####
 ===============================================================================  

  [..] This section provides functions allowing to configure the ADC Interrupts, get 
        the status and clear flags and Interrupts pending bits.
  
  [..] The ADC provide 11 Interrupts sources and 11 Flags which can be divided into 3 groups:
  
  (#) Flags and Interrupts for ADC regular channels
  (##)Flags
      (+) ADC_FLAG_RDY: ADC Ready flag
      (+) ADC_FLAG_EOSMP: ADC End of Sampling flag
      (+) ADC_FLAG_EOC: ADC End of Regular Conversion flag.
      (+) ADC_FLAG_EOS: ADC End of Regular sequence of Conversions flag
      (+) ADC_FLAG_OVR: ADC overrun flag
     
  (##) Interrupts
      (+) ADC_IT_RDY: ADC Ready interrupt source 
      (+) ADC_IT_EOSMP: ADC End of Sampling interrupt source
      (+) ADC_IT_EOC: ADC End of Regular Conversion interrupt source
      (+) ADC_IT_EOS: ADC End of Regular sequence of Conversions interrupt
      (+) ADC_IT_OVR: ADC overrun interrupt source
  
  
  (#) Flags and Interrupts for ADC regular channels
  (##)Flags
      (+) ADC_FLAG_JEOC: ADC Ready flag
      (+) ADC_FLAG_JEOS: ADC End of Sampling flag
      (+) ADC_FLAG_JQOVF: ADC End of Regular Conversion flag.
     
  (##) Interrupts
      (+) ADC_IT_JEOC: ADC End of Injected Conversion interrupt source 
      (+) ADC_IT_JEOS: ADC End of Injected sequence of Conversions interrupt source
      (+) ADC_IT_JQOVF: ADC Injected Context Queue Overflow interrupt source   

  (#) General Flags and Interrupts for the ADC
  (##)Flags 
     (+)  ADC_FLAG_AWD1: ADC Analog watchdog 1 flag
     (+) ADC_FLAG_AWD2: ADC Analog watchdog 2 flag
     (+) ADC_FLAG_AWD3: ADC Analog watchdog 3 flag
    
  (##)Flags 
     (+)  ADC_IT_AWD1: ADC Analog watchdog 1 interrupt source
     (+) ADC_IT_AWD2: ADC Analog watchdog 2 interrupt source
     (+) ADC_IT_AWD3: ADC Analog watchdog 3 interrupt source
     
  (#) Flags  for ADC dual mode
  (##)Flags for Master
     (+) ADC_FLAG_MSTRDY: ADC master Ready (ADRDY) flag 
     (+) ADC_FLAG_MSTEOSMP: ADC master End of Sampling flag 
     (+) ADC_FLAG_MSTEOC: ADC master End of Regular Conversion flag 
     (+) ADC_FLAG_MSTEOS: ADC master End of Regular sequence of Conversions flag 
     (+) ADC_FLAG_MSTOVR: ADC master overrun flag 
     (+) ADC_FLAG_MSTJEOC: ADC master End of Injected Conversion flag 
     (+) ADC_FLAG_MSTJEOS: ADC master End of Injected sequence of Conversions flag 
     (+) ADC_FLAG_MSTAWD1: ADC master Analog watchdog 1 flag 
     (+) ADC_FLAG_MSTAWD2: ADC master Analog watchdog 2 flag 
     (+) ADC_FLAG_MSTAWD3: ADC master Analog watchdog 3 flag 
     (+) ADC_FLAG_MSTJQOVF: ADC master Injected Context Queue Overflow flag       
     
  (##) Flags for Slave
     (+) ADC_FLAG_SLVRDY: ADC slave Ready (ADRDY) flag 
     (+) ADC_FLAG_SLVEOSMP: ADC slave End of Sampling flag 
     (+) ADC_FLAG_SLVEOC: ADC slave End of Regular Conversion flag 
     (+) ADC_FLAG_SLVEOS: ADC slave End of Regular sequence of Conversions flag 
     (+) ADC_FLAG_SLVOVR: ADC slave overrun flag 
     (+) ADC_FLAG_SLVJEOC: ADC slave End of Injected Conversion flag 
     (+) ADC_FLAG_SLVJEOS: ADC slave End of Injected sequence of Conversions flag 
     (+) ADC_FLAG_SLVAWD1: ADC slave Analog watchdog 1 flag 
     (+) ADC_FLAG_SLVAWD2: ADC slave Analog watchdog 2 flag 
     (+) ADC_FLAG_SLVAWD3: ADC slave Analog watchdog 3 flag 
     (+) ADC_FLAG_SLVJQOVF: ADC slave Injected Context Queue Overflow flag 
     
  The user should identify which mode will be used in his application to manage   
  the ADC controller events: Polling mode or Interrupt mode.
  
  In the Polling Mode it is advised to use the following functions:
      - ADC_GetFlagStatus() : to check if flags events occur. 
      - ADC_ClearFlag()     : to clear the flags events.
      
  In the Interrupt Mode it is advised to use the following functions:
     - ADC_ITConfig()       : to enable or disable the interrupt source.
     - ADC_GetITStatus()    : to check if Interrupt occurs.
     - ADC_ClearITPendingBit() : to clear the Interrupt pending Bit 
                                (corresponding Flag). 
@endverbatim
  * @{
  */ 

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled. 
  *   This parameter can be any combination of the following values:
  *     @arg ADC_IT_RDY: ADC Ready (ADRDY) interrupt source 
  *     @arg ADC_IT_EOSMP: ADC End of Sampling interrupt source 
  *     @arg ADC_IT_EOC: ADC End of Regular Conversion interrupt source 
  *     @arg ADC_IT_EOS: ADC End of Regular sequence of Conversions interrupt source 
  *     @arg ADC_IT_OVR: ADC overrun interrupt source 
  *     @arg ADC_IT_JEOC: ADC End of Injected Conversion interrupt source 
  *     @arg ADC_IT_JEOS: ADC End of Injected sequence of Conversions interrupt source 
  *     @arg ADC_IT_AWD1: ADC Analog watchdog 1 interrupt source 
  *     @arg ADC_IT_AWD2: ADC Analog watchdog 2 interrupt source 
  *     @arg ADC_IT_AWD3: ADC Analog watchdog 3 interrupt source 
  *     @arg ADC_IT_JQOVF: ADC Injected Context Queue Overflow interrupt source 
  * @param  NewState: new state of the specified ADC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_IT(ADC_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->IER |= ADC_IT;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->IER &= (~(uint32_t)ADC_IT);
  }
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to check. 
  *   This parameter can be one of the following values:
  *     @arg ADC_FLAG_RDY: ADC Ready (ADRDY) flag 
  *     @arg ADC_FLAG_EOSMP: ADC End of Sampling flag 
  *     @arg ADC_FLAG_EOC: ADC End of Regular Conversion flag 
  *     @arg ADC_FLAG_EOS: ADC End of Regular sequence of Conversions flag 
  *     @arg ADC_FLAG_OVR: ADC overrun flag 
  *     @arg ADC_FLAG_JEOC: ADC End of Injected Conversion flag 
  *     @arg ADC_FLAG_JEOS: ADC End of Injected sequence of Conversions flag 
  *     @arg ADC_FLAG_AWD1: ADC Analog watchdog 1 flag 
  *     @arg ADC_FLAG_AWD2: ADC Analog watchdog 2 flag 
  *     @arg ADC_FLAG_AWD3: ADC Analog watchdog 3 flag 
  *     @arg ADC_FLAG_JQOVF: ADC Injected Context Queue Overflow flag 
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADCx->ISR & ADC_FLAG) != (uint32_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the ADCx's pending flags.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_FLAG: specifies the flag to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg ADC_FLAG_RDY: ADC Ready (ADRDY) flag 
  *     @arg ADC_FLAG_EOSMP: ADC End of Sampling flag 
  *     @arg ADC_FLAG_EOC: ADC End of Regular Conversion flag 
  *     @arg ADC_FLAG_EOS: ADC End of Regular sequence of Conversions flag 
  *     @arg ADC_FLAG_OVR: ADC overrun flag 
  *     @arg ADC_FLAG_JEOC: ADC End of Injected Conversion flag 
  *     @arg ADC_FLAG_JEOS: ADC End of Injected sequence of Conversions flag 
  *     @arg ADC_FLAG_AWD1: ADC Analog watchdog 1 flag 
  *     @arg ADC_FLAG_AWD2: ADC Analog watchdog 2 flag 
  *     @arg ADC_FLAG_AWD3: ADC Analog watchdog 3 flag 
  *     @arg ADC_FLAG_JQOVF: ADC Injected Context Queue Overflow flag 
  * @retval None
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));
  /* Clear the selected ADC flags */
  ADCx->ISR = (uint32_t)ADC_FLAG;
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_FLAG: specifies the master or slave flag to check. 
  *   This parameter can be one of the following values:
  *     @arg ADC_FLAG_MSTRDY: ADC master Ready (ADRDY) flag 
  *     @arg ADC_FLAG_MSTEOSMP: ADC master End of Sampling flag 
  *     @arg ADC_FLAG_MSTEOC: ADC master End of Regular Conversion flag 
  *     @arg ADC_FLAG_MSTEOS: ADC master End of Regular sequence of Conversions flag 
  *     @arg ADC_FLAG_MSTOVR: ADC master overrun flag 
  *     @arg ADC_FLAG_MSTJEOC: ADC master End of Injected Conversion flag 
  *     @arg ADC_FLAG_MSTJEOS: ADC master End of Injected sequence of Conversions flag 
  *     @arg ADC_FLAG_MSTAWD1: ADC master Analog watchdog 1 flag 
  *     @arg ADC_FLAG_MSTAWD2: ADC master Analog watchdog 2 flag 
  *     @arg ADC_FLAG_MSTAWD3: ADC master Analog watchdog 3 flag 
  *     @arg ADC_FLAG_MSTJQOVF: ADC master Injected Context Queue Overflow flag 
  *     @arg ADC_FLAG_SLVRDY: ADC slave Ready (ADRDY) flag 
  *     @arg ADC_FLAG_SLVEOSMP: ADC slave End of Sampling flag 
  *     @arg ADC_FLAG_SLVEOC: ADC slave End of Regular Conversion flag 
  *     @arg ADC_FLAG_SLVEOS: ADC slave End of Regular sequence of Conversions flag 
  *     @arg ADC_FLAG_SLVOVR: ADC slave overrun flag 
  *     @arg ADC_FLAG_SLVJEOC: ADC slave End of Injected Conversion flag 
  *     @arg ADC_FLAG_SLVJEOS: ADC slave End of Injected sequence of Conversions flag 
  *     @arg ADC_FLAG_SLVAWD1: ADC slave Analog watchdog 1 flag 
  *     @arg ADC_FLAG_SLVAWD2: ADC slave Analog watchdog 2 flag 
  *     @arg ADC_FLAG_SLVAWD3: ADC slave Analog watchdog 3 flag 
  *     @arg ADC_FLAG_SLVJQOVF: ADC slave Injected Context Queue Overflow flag 
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetCommonFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  uint32_t tmpreg1 = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_COMMONFLAG(ADC_FLAG));

  if((ADCx == ADC1) || (ADCx == ADC2))
  {
    tmpreg1 = ADC1_2->CSR;
  }
  else
  {
    tmpreg1 = ADC3_4->CSR;
  }  
  /* Check the status of the specified ADC flag */
  if ((tmpreg1 & ADC_FLAG) != (uint32_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the ADCx's pending flags.
  * @param  ADCx: where x can be 1, 2, 3 or 4 to select the ADC peripheral.
  * @param  ADC_FLAG: specifies the master or slave flag to clear. 
  *   This parameter can be one of the following values:
  *     @arg ADC_FLAG_MSTRDY: ADC master Ready (ADRDY) flag 
  *     @arg ADC_FLAG_MSTEOSMP: ADC master End of Sampling flag 
  *     @arg ADC_FLAG_MSTEOC: ADC master End of Regular Conversion flag 
  *     @arg ADC_FLAG_MSTEOS: ADC master End of Regular sequence of Conversions flag 
  *     @arg ADC_FLAG_MSTOVR: ADC master overrun flag 
  *     @arg ADC_FLAG_MSTJEOC: ADC master End of Injected Conversion flag 
  *     @arg ADC_FLAG_MSTJEOS: ADC master End of Injected sequence of Conversions flag 
  *     @arg ADC_FLAG_MSTAWD1: ADC master Analog watchdog 1 flag 
  *     @arg ADC_FLAG_MSTAWD2: ADC master Analog watchdog 2 flag 
  *     @arg ADC_FLAG_MSTAWD3: ADC master Analog watchdog 3 flag 
  *     @arg ADC_FLAG_MSTJQOVF: ADC master Injected Context Queue Overflow flag 
  *     @arg ADC_FLAG_SLVRDY: ADC slave Ready (ADRDY) flag 
  *     @arg ADC_FLAG_SLVEOSMP: ADC slave End of Sampling flag 
  *     @arg ADC_FLAG_SLVEOC: ADC slave End of Regular Conversion flag 
  *     @arg ADC_FLAG_SLVEOS: ADC slave End of Regular sequence of Conversions flag 
  *     @arg ADC_FLAG_SLVOVR: ADC slave overrun flag 
  *     @arg ADC_FLAG_SLVJEOC: ADC slave End of Injected Conversion flag 
  *     @arg ADC_FLAG_SLVJEOS: ADC slave End of Injected sequence of Conversions flag 
  *     @arg ADC_FLAG_SLVAWD1: ADC slave Analog watchdog 1 flag 
  *     @arg ADC_FLAG_SLVAWD2: ADC slave Analog watchdog 2 flag 
  *     @arg ADC_FLAG_SLVAWD3: ADC slave Analog watchdog 3 flag 
  *     @arg ADC_FLAG_SLVJQOVF: ADC slave Injected Context Queue Overflow flag 
  * @retval None
  */
void ADC_ClearCommonFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_COMMONFLAG(ADC_FLAG));

  if((ADCx == ADC1) || (ADCx == ADC2))
  {
    /* Clear the selected ADC flags */
    ADC1_2->CSR |= (uint32_t)ADC_FLAG;
  }
  else
  {
    /* Clear the selected ADC flags */
    ADC3_4->CSR |= (uint32_t)ADC_FLAG;
  }  
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt source to check. 
  *   This parameter can be one of the following values:
  *     @arg ADC_IT_RDY: ADC Ready (ADRDY) interrupt source 
  *     @arg ADC_IT_EOSMP: ADC End of Sampling interrupt source 
  *     @arg ADC_IT_EOC: ADC End of Regular Conversion interrupt source 
  *     @arg ADC_IT_EOS: ADC End of Regular sequence of Conversions interrupt source 
  *     @arg ADC_IT_OVR: ADC overrun interrupt source 
  *     @arg ADC_IT_JEOC: ADC End of Injected Conversion interrupt source 
  *     @arg ADC_IT_JEOS: ADC End of Injected sequence of Conversions interrupt source 
  *     @arg ADC_IT_AWD1: ADC Analog watchdog 1 interrupt source 
  *     @arg ADC_IT_AWD2: ADC Analog watchdog 2 interrupt source 
  *     @arg ADC_IT_AWD3: ADC Analog watchdog 3 interrupt source 
  *     @arg ADC_IT_JQOVF: ADC Injected Context Queue Overflow interrupt source 
  * @retval The new state of ADC_IT (SET or RESET).
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
  ITStatus bitstatus = RESET;  
  uint16_t itstatus = 0x0, itenable = 0x0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_IT(ADC_IT));
   
  itstatus = ADCx->ISR & ADC_IT;
  
  itenable = ADCx->IER & ADC_IT;
  if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the ADCx's interrupt pending bits.
  * @param  ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_IT_RDY: ADC Ready (ADRDY) interrupt source 
  *     @arg ADC_IT_EOSMP: ADC End of Sampling interrupt source 
  *     @arg ADC_IT_EOC: ADC End of Regular Conversion interrupt source 
  *     @arg ADC_IT_EOS: ADC End of Regular sequence of Conversions interrupt source 
  *     @arg ADC_IT_OVR: ADC overrun interrupt source 
  *     @arg ADC_IT_JEOC: ADC End of Injected Conversion interrupt source 
  *     @arg ADC_IT_JEOS: ADC End of Injected sequence of Conversions interrupt source 
  *     @arg ADC_IT_AWD1: ADC Analog watchdog 1 interrupt source 
  *     @arg ADC_IT_AWD2: ADC Analog watchdog 2 interrupt source 
  *     @arg ADC_IT_AWD3: ADC Analog watchdog 3 interrupt source 
  *     @arg ADC_IT_JQOVF: ADC Injected Context Queue Overflow interrupt source
  * @retval None
  */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_IT(ADC_IT));
  /* Clear the selected ADC interrupt pending bit */
  ADCx->ISR = (uint32_t)ADC_IT;
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
