/**
  ******************************************************************************
  * @file    stm32f30x_dac.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Digital-to-Analog Converter (DAC) peripheral: 
  *           + DAC channels configuration: trigger, output buffer, data format
  *           + DMA management      
  *           + Interrupts and flags management
  *
  @verbatim
    
 ===============================================================================
                      ##### DAC Peripheral features #####
 ===============================================================================
    [..] The device integrates two 12-bit Digital Analog Converters that can 
         be used independently or simultaneously (dual mode):
         (#) DAC1 integrates two DAC channels:
             (++) DAC1 channel 1 with DAC1_OUT1 as output
             (++) DAC1 channel 2 with DAC1_OUT2 as output
             (++) The two channels can be used independently or simultaneously (dual mode)
   
         (#) DAC2 integrates only one channel DAC2 channel 1 with DAC2_OUT1 as output 
         
    [..] Digital to Analog conversion can be non-triggered using DAC_Trigger_None
         and DAC_OUT1/DAC_OUT2 is available once writing to DHRx register using 
         DAC_SetChannel1Data()/DAC_SetChannel2Data.
         
    [..] Digital to Analog conversion can be triggered by:
         (#) External event: EXTI Line 9 (any GPIOx_Pin9) using DAC_Trigger_Ext_IT9.
             The used pin (GPIOx_Pin9) must be configured in input mode.
             
         (#) Timers TRGO: TIM2, TIM8/TIM3, TIM4, TIM6, TIM7, and TIM15 
             (DAC_Trigger_T2_TRGO, DAC_Trigger_T4_TRGO...)
             The timer TRGO event should be selected using TIM_SelectOutputTrigger()
             (++) To trigger DAC conversions by TIM3 instead of TIM8 follow
                 this sequence:
                 (+++) Enable SYSCFG APB clock by calling
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
                 (+++) Select DAC_Trigger_T3_TRGO when calling DAC_Init()
                 (+++) Remap the DAC trigger from TIM8 to TIM3 by calling
                       SYSCFG_TriggerRemapConfig(SYSCFG_TriggerRemap_DACTIM3, ENABLE)
         (#) Software using DAC_Trigger_Software
         
    [..] Each DAC channel integrates an output buffer that can be used to 
         reduce the output impedance, and to drive external loads directly
         without having to add an external operational amplifier.
         To enable, the output buffer use  
         DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
         
    [..] Refer to the device datasheet for more details about output impedance
         value with and without output buffer.
         
    [..] Both DAC channels can be used to generate:
         (+) Noise wave using DAC_WaveGeneration_Noise
         (+) Triangle wave using DAC_WaveGeneration_Triangle
         
    [..] Wave generation can be disabled using DAC_WaveGeneration_None
    
    [..] The DAC data format can be:
         (+) 8-bit right alignment using DAC_Align_8b_R
         (+) 12-bit left alignment using DAC_Align_12b_L
         (+) 12-bit right alignment using DAC_Align_12b_R
         
    [..] The analog output voltage on each DAC channel pin is determined
         by the following equation: 
         (+) DAC_OUTx = VREF+ * DOR / 4095 with DOR is the Data Output Register. 
         VREF+ is the input voltage reference (refer to the device datasheet)
         e.g. To set DAC_OUT1 to 0.7V, use DAC_SetChannel1Data(DAC_Align_12b_R, 868);
         Assuming that VREF+ = 3.3, DAC_OUT1 = (3.3 * 868) / 4095 = 0.7V
         
    [..] A DMA1 request can be generated when an external trigger (but not
         a software trigger) occurs if DMA1 requests are enabled using
         DAC_DMACmd()
         DMA1 requests are mapped as following:
         (+) DAC channel1 is mapped on DMA1 channel3 which must be already 
             configured
         (+) DAC channel2 is mapped on DMA1 channel4 which must be already 
             configured
 
                    ##### How to use this driver #####
 ===============================================================================          
    [..]
         (+) Enable DAC APB1 clock to get write access to DAC registers
             using RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE)

         (+) Configure DACx_OUTy (DAC1_OUT1: PA4, DAC1_OUT2: PA5, DAC2_OUT1: PA6)
             in analog mode.

         (+) Configure the DAC channel using DAC_Init()

         (+) Enable the DAC channel using DAC_Cmd()
 
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
#include "stm32f30x_dac.h"
#include "stm32f30x_rcc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup DAC 
  * @brief DAC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* CR register Mask */
#define CR_CLEAR_MASK              ((uint32_t)0x00000FFE)

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_SET            ((uint32_t)0x00000003)
#define DUAL_SWTRIG_RESET          ((uint32_t)0xFFFFFFFC)

/* DHR registers offsets */
#define DHR12R1_OFFSET             ((uint32_t)0x00000008)
#define DHR12R2_OFFSET             ((uint32_t)0x00000014)
#define DHR12RD_OFFSET             ((uint32_t)0x00000020)

/* DOR register offset */
#define DOR_OFFSET                 ((uint32_t)0x0000002C)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup DAC_Private_Functions
  * @{
  */

/** @defgroup DAC_Group1 DAC channels configuration
 *  @brief   DAC channels configuration: trigger, output buffer, data format 
 *
@verbatim   
 ===============================================================================
    ##### DAC channels configuration: trigger, output buffer, data format #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @retval None
  */
void DAC_DeInit(DAC_TypeDef* DACx)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));

  if (DACx == DAC1)
  {
    /* Enable DAC1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC1, ENABLE);
    /* Release DAC1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC1, DISABLE);
  }
  else
  {
    /* Enable DAC2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC2, ENABLE);
    /* Release DAC2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC2, DISABLE);
  }
}

/**
  * @brief  Initializes the DAC peripheral according to the specified 
  *         parameters in the DAC_InitStruct.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_InitStruct: pointer to a DAC_InitTypeDef structure that
  *         contains the configuration information for the specified DAC channel.
  * @retval None
  */
void DAC_Init(DAC_TypeDef* DACx, uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;

  /* Check the DAC parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
  assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
  assert_param(IS_DAC_BUFFER_SWITCH_STATE(DAC_InitStruct->DAC_Buffer_Switch));

/*---------------------------- DAC CR Configuration --------------------------*/
  /* Get the DAC CR value */
  tmpreg1 = DACx->CR;
  /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
  tmpreg1 &= ~(CR_CLEAR_MASK << DAC_Channel);
  /* Configure for the selected DAC channel: buffer output, trigger, wave generation,
     mask/amplitude for wave generation */
  
  /* Set TSELx and TENx bits according to DAC_Trigger value */
  /* Set WAVEx bits according to DAC_WaveGeneration value */
  /* Set MAMPx bits according to DAC_LFSRUnmask_TriangleAmplitude value */ 
  /* Set BOFFx OUTENx bit according to DAC_Buffer_Switch value */   
  tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
             DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | DAC_InitStruct->DAC_Buffer_Switch);   
                   
  /* Calculate CR register value depending on DAC_Channel */
  tmpreg1 |= tmpreg2 << DAC_Channel;
  /* Write to DAC CR */
  DACx->CR = tmpreg1;
}

/**
  * @brief  Fills each DAC_InitStruct member with its default value.
  * @param  DAC_InitStruct: pointer to a DAC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
/*--------------- Reset DAC init structure parameters values -----------------*/
  /* Initialize the DAC_Trigger member */
  DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
  /* Initialize the DAC_WaveGeneration member */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
  /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  /* Initialize the DAC_Buffer_Switch member */
  DAC_InitStruct->DAC_Buffer_Switch = DAC_BufferSwitch_Enable;
}

/**
  * @brief  Enables or disables the specified DAC channel.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  NewState: new state of the DAC channel. 
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When the DAC channel is enabled the trigger source can no more
  *         be modified.
  * @retval None
  */
void DAC_Cmd(DAC_TypeDef* DACx, uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel */
    DACx->CR |= (DAC_CR_EN1 << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC channel */
    DACx->CR &= (~(DAC_CR_EN1 << DAC_Channel));
  }
}

/**
  * @brief  Enables or disables the selected DAC channel software trigger.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  NewState: new state of the selected DAC channel software trigger.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_SoftwareTriggerCmd(DAC_TypeDef* DACx, uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for the selected DAC channel */
    DACx->SWTRIGR |= (uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4);
  }
  else
  {
    /* Disable software trigger for the selected DAC channel */
    DACx->SWTRIGR &= ~((uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4));
  }
}

/**
  * @brief  Enables or disables simultaneously the two DAC channels software
  *         triggers.
  * @param  DACx: where x can be 1 to select the DAC1 peripheral.
  * @note   Dual trigger is not applicable for DAC2 (DAC2 integrates one channel).
  * @param  NewState: new state of the DAC channels software triggers.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DualSoftwareTriggerCmd(DAC_TypeDef* DACx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_LIST1_PERIPH(DACx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for both DAC channels */
    DACx->SWTRIGR |= DUAL_SWTRIG_SET;
  }
  else
  {
    /* Disable software trigger for both DAC channels */
    DACx->SWTRIGR &= DUAL_SWTRIG_RESET;
  }
}

/**
  * @brief  Enables or disables the selected DAC channel wave generation.
  * @param  DACx: where x can be 1 to select the DAC1 peripheral.
  * @note   Wave generation is not available in DAC2.
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_Wave: Specifies the wave type to enable or disable.
  *          This parameter can be one of the following values:
  *            @arg DAC_Wave_Noise: noise wave generation
  *            @arg DAC_Wave_Triangle: triangle wave generation
  * @param  NewState: new state of the selected DAC channel wave generation.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   
  * @retval None
  */
void DAC_WaveGenerationCmd(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_LIST1_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_WAVE(DAC_Wave)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected wave generation for the selected DAC channel */
    DACx->CR |= DAC_Wave << DAC_Channel;
  }
  else
  {
    /* Disable the selected wave generation for the selected DAC channel */
    DACx->CR &= ~(DAC_Wave << DAC_Channel);
  }
}

/**
  * @brief  Set the specified data holding register value for DAC channel1.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Align: Specifies the data alignment for DAC channel1.
  *          This parameter can be one of the following values:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @param  Data: Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannel1Data(DAC_TypeDef* DACx, uint32_t DAC_Align, uint16_t Data)
{  
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));
  
  tmp = (uint32_t)DACx; 
  tmp += DHR12R1_OFFSET + DAC_Align;

  /* Set the DAC channel1 selected data holding register */
  *(__IO uint32_t *) tmp = Data;
}

/**
  * @brief  Set the specified data holding register value for DAC channel2.
  * @param  DACx: where x can be 1 to select the DAC peripheral.
  * @note   This function is available only for DAC1.
  * @param  DAC_Align: Specifies the data alignment for DAC channel2.
  *          This parameter can be one of the following values:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @param  Data : Data to be loaded in the selected data holding register.
  * @retval None
  */
void DAC_SetChannel2Data(DAC_TypeDef* DACx, uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_LIST1_PERIPH(DACx));
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));
  
  tmp = (uint32_t)DACx;
  tmp += DHR12R2_OFFSET + DAC_Align;

  /* Set the DAC channel2 selected data holding register */
  *(__IO uint32_t *)tmp = Data;
}

/**
  * @brief  Set the specified data holding register value for dual channel DAC.
  * @param  DACx: where x can be 1 to select the DAC peripheral.
  * @note   This function isn't applicable for DAC2.
  * @param  DAC_Align: Specifies the data alignment for dual channel DAC.
  *          This parameter can be one of the following values:
  *            @arg DAC_Align_8b_R: 8bit right data alignment selected
  *            @arg DAC_Align_12b_L: 12bit left data alignment selected
  *            @arg DAC_Align_12b_R: 12bit right data alignment selected
  * @param  Data2: Data for DAC Channel2 to be loaded in the selected data 
  *         holding register.
  * @param  Data1: Data for DAC Channel1 to be loaded in the selected data 
  *         holding register.
  * @note In dual mode, a unique register access is required to write in both
  *       DAC channels at the same time.
  * @retval None
  */
void DAC_SetDualChannelData(DAC_TypeDef* DACx, uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
  uint32_t data = 0, tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_LIST1_PERIPH(DACx));
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data1));
  assert_param(IS_DAC_DATA(Data2));
  
  /* Calculate and set dual DAC data holding register value */
  if (DAC_Align == DAC_Align_8b_R)
  {
    data = ((uint32_t)Data2 << 8) | Data1; 
  }
  else
  {
    data = ((uint32_t)Data2 << 16) | Data1;
  }
  
  tmp = (uint32_t)DACx;
  tmp += DHR12RD_OFFSET + DAC_Align;

  /* Set the dual DAC selected data holding register */
  *(__IO uint32_t *)tmp = data;
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @retval The selected DAC channel data output value.
  */
uint16_t DAC_GetDataOutputValue(DAC_TypeDef* DACx, uint32_t DAC_Channel)
{
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  
  tmp = (uint32_t) DACx;
  tmp += DOR_OFFSET + ((uint32_t)DAC_Channel >> 2);
  
  /* Returns the DAC channel data output register value */
  return (uint16_t) (*(__IO uint32_t*) tmp);
}

/**
  * @}
  */

/** @defgroup DAC_Group2 DMA management functions
 *  @brief   DMA management functions
 *
@verbatim   
 ===============================================================================
                    ##### DMA management functions #####
 =============================================================================== 

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified DAC channel DMA request.
  *         When enabled DMA1 is generated when an external trigger (EXTI Line9,
  *         TIM2, TIM4, TIM6, TIM7 or TIM9  but not a software trigger) occurs
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.
  * @param  DAC_Channel: the selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  NewState: new state of the selected DAC channel DMA request.
  *          This parameter can be: ENABLE or DISABLE.
  * @note The DAC channel1 (channel2) is mapped on DMA1 channel3 (channel4) which 
  *       must be already configured. 
  * @retval None
  */
void DAC_DMACmd(DAC_TypeDef* DACx, uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel DMA request */
    DACx->CR |= (DAC_CR_DMAEN1 << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC channel DMA request */
    DACx->CR &= (~(DAC_CR_DMAEN1 << DAC_Channel));
  }
}

/**
  * @}
  */

/** @defgroup DAC_Group3 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified DAC interrupts.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_IT: specifies the DAC interrupt sources to be enabled or disabled. 
  *          This parameter can be:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @note   The DMA underrun occurs when a second external trigger arrives before
  *         the acknowledgement for the first external trigger is received (first request).
  * @param  NewState: new state of the specified DAC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */ 
void DAC_ITConfig(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState)  
{
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_DAC_IT(DAC_IT)); 

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC interrupts */
    DACx->CR |=  (DAC_IT << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC interrupts */
    DACx->CR &= (~(uint32_t)(DAC_IT << DAC_Channel));
  }
}

/**
  * @brief  Checks whether the specified DAC flag is set or not.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Channel: thee selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_FLAG: specifies the flag to check. 
  *          This parameter can be:
  *            @arg DAC_FLAG_DMAUDR: DMA underrun flag
  * @note   The DMA underrun occurs when a second external trigger arrives before
  *         the acknowledgement for the first external trigger is received (first request).
  * @retval The new state of DAC_FLAG (SET or RESET).
  */
FlagStatus DAC_GetFlagStatus(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  /* Check the status of the specified DAC flag */
  if ((DACx->SR & (DAC_FLAG << DAC_Channel)) != (uint8_t)RESET)
  {
    /* DAC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* DAC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the DAC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the DAC channel's pending flags.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_FLAG: specifies the flag to clear. 
  *          This parameter can be:
  *            @arg DAC_FLAG_DMAUDR: DMA underrun flag                          
  * @retval None
  */
void DAC_ClearFlag(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  /* Clear the selected DAC flags */
  DACx->SR = (DAC_FLAG << DAC_Channel);
}

/**
  * @brief  Checks whether the specified DAC interrupt has occurred or not.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.  
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_IT: specifies the DAC interrupt source to check. 
  *          This parameter can be:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @note   The DMA underrun occurs when a second external trigger arrives before
  *         the acknowledgement for the first external trigger is received (first request).
  * @retval The new state of DAC_IT (SET or RESET).
  */
ITStatus DAC_GetITStatus(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT));

  /* Get the DAC_IT enable bit status */
  enablestatus = (DACx->CR & (DAC_IT << DAC_Channel)) ;
  
  /* Check the status of the specified DAC interrupt */
  if (((DACx->SR & (DAC_IT << DAC_Channel)) != (uint32_t)RESET) && enablestatus)
  {
    /* DAC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* DAC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the DAC_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the DAC channel's interrupt pending bits.
  * @param  DACx: where x can be 1 or 2 to select the DAC peripheral.
  * @param  DAC_Channel: the selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_IT: specifies the DAC interrupt pending bit to clear.
  *          This parameter can be the following values:
  *            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @retval None
  */
void DAC_ClearITPendingBit(DAC_TypeDef* DACx, uint32_t DAC_Channel, uint32_t DAC_IT)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALL_PERIPH(DACx));
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT)); 

  /* Clear the selected DAC interrupt pending bits */
  DACx->SR = (DAC_IT << DAC_Channel);
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

