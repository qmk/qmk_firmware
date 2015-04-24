/**
  ******************************************************************************
  * @file    stm32f0xx_hal_dac.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   DAC HAL module driver.
  *         This file provides firmware functions to manage the following 
  *         functionalities of the Digital to Analog Converter (DAC) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions      
  *     
  *
  @verbatim      
  ==============================================================================
                      ##### DAC Peripheral features #####
  ==============================================================================
    [..]        
      *** DAC Channels ***
      ====================  
    [..]  
    STM32F0 devices integrates no, one or two 12-bit Digital Analog Converters.
    STM32F05x devices have one converter (channel1)
    STM32F07x & STM32F09x devices have two converters (i.e. channel1 & channel2)

    When 2 converters are present (i.e. channel1 & channel2)  they 
    can be used independently or simultaneously (dual mode):
      (#) DAC channel1 with DAC_OUT1 (PA4) as output
      (#) DAC channel2 with DAC_OUT2 (PA5) as output
      
      *** DAC Triggers ***
      ====================
    [..]
    Digital to Analog conversion can be non-triggered using DAC_Trigger_None
    and DAC_OUT1/DAC_OUT2 is available once writing to DHRx register. 
    [..] 
    Digital to Analog conversion can be triggered by:
      (#) External event: EXTI Line 9 (any GPIOx_Pin9) using DAC_Trigger_Ext_IT9.
          The used pin (GPIOx_Pin9) must be configured in input mode.
  
      (#) Timers TRGO: TIM2, TIM3, TIM6, and TIM15 
          (DAC_Trigger_T2_TRGO, DAC_Trigger_T3_TRGO...)
  
      (#) Software using DAC_Trigger_Software
  
      *** DAC Buffer mode feature ***
      =============================== 
      [..] 
      Each DAC channel integrates an output buffer that can be used to 
      reduce the output impedance, and to drive external loads directly
      without having to add an external operational amplifier.
      To enable, the output buffer use  
      sConfig.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
      [..]           
      (@) Refer to the device datasheet for more details about output 
          impedance value with and without output buffer.
            
       *** DAC wave generation feature ***
       =================================== 
       [..]     
       Both DAC channels can be used to generate
         (#) Noise wave 
         (#) Triangle wave
            
       *** DAC data format ***
       =======================
       [..]   
       The DAC data format can be:
         (#) 8-bit right alignment using DAC_ALIGN_8B_R
         (#) 12-bit left alignment using DAC_ALIGN_12B_L
         (#) 12-bit right alignment using DAC_ALIGN_12B_R
  
       *** DAC data value to voltage correspondence ***  
       ================================================ 
       [..] 
       The analog output voltage on each DAC channel pin is determined
       by the following equation: 
       DAC_OUTx = VREF+ * DOR / 4095
       with  DOR is the Data Output Register
          VEF+ is the input voltage reference (refer to the device datasheet)
        e.g. To set DAC_OUT1 to 0.7V, use
          Assuming that VREF+ = 3.3V, DAC_OUT1 = (3.3 * 868) / 4095 = 0.7V
  
       *** DMA requests  ***
       =====================
       [..]    
       A DMA1 request can be generated when an external trigger (but not
       a software trigger) occurs if DMA1 requests are enabled using
       HAL_DAC_Start_DMA()
       [..]
       DMA1 requests are mapped as following:
         (#) DAC channel1 : mapped on DMA1 channel3 which must be 
             already configured
         (#) DAC channel2 : mapped on DMA1 channel4 which must be 
             already configured
       
    -@- For Dual mode and specific signal (Triangle and noise) generation please 
        refer to Extension Features Driver description        
        STM32F0 devices with one channel (one converting capability) does not
        support Dual mode and specific signal (Triangle and noise) generation.
      
                      ##### How to use this driver #####
  ==============================================================================
    [..]          
      (+) DAC APB clock must be enabled to get write access to DAC
          registers using HAL_DAC_Init()
      (+) Configure DAC_OUTx (DAC_OUT1: PA4, DAC_OUT2: PA5) in analog mode.
      (+) Configure the DAC channel using HAL_DAC_ConfigChannel() function.
      (+) Enable the DAC channel using HAL_DAC_Start() or HAL_DAC_Start_DMA functions

     *** Polling mode IO operation ***
     =================================
     [..]    
       (+) Start the DAC peripheral using HAL_DAC_Start() 
       (+) To read the DAC last data output value value, use the HAL_DAC_GetValue() function.
       (+) Stop the DAC peripheral using HAL_DAC_Stop()
       
     *** DMA mode IO operation ***    
     ==============================
     [..]    
       (+) Start the DAC peripheral using HAL_DAC_Start_DMA(), at this stage the user specify the length 
           of data to be transfered at each end of conversion 
       (+) At The end of data transfer HAL_DAC_ConvCpltCallbackCh1()or HAL_DAC_ConvCpltCallbackCh2()  
           function is executed and user can add his own code by customization of function pointer 
           HAL_DAC_ConvCpltCallbackCh1 or HAL_DAC_ConvCpltCallbackCh2
       (+) In case of transfer Error, HAL_DAC_ErrorCallbackCh1() function is executed and user can 
            add his own code by customization of function pointer HAL_DAC_ErrorCallbackCh1
       (+) Stop the DAC peripheral using HAL_DAC_Stop_DMA()
                    
     *** DAC HAL driver macros list ***
     ============================================= 
     [..]
       Below the list of most used macros in DAC HAL driver.
       
      (+) __HAL_DAC_ENABLE : Enable the DAC peripheral
      (+) __HAL_DAC_DISABLE : Disable the DAC peripheral
      (+) __HAL_DAC_CLEAR_FLAG: Clear the DAC's pending flags
      (+) __HAL_DAC_GET_FLAG: Get the selected DAC's flag status
      
     [..]
      (@) You can refer to the DAC HAL driver header file for more useful macros  
   
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
#include "stm32f0xx_hal.h"

#ifdef HAL_DAC_MODULE_ENABLED

#if defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined (STM32F098xx)

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @defgroup DAC DAC HAL module driver
  * @brief DAC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/** @defgroup DAC_Exported_Functions DAC Exported Functions
  * @{
  */

/** @defgroup DAC_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
  ==============================================================================
              ##### Initialization and de-initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the DAC. 
      (+) De-initialize the DAC. 
         
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the DAC peripheral according to the specified parameters
  *         in the DAC_InitStruct.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef* hdac)
{ 
  /* Check DAC handle */
  if(hdac == NULL)
  {
     return HAL_ERROR;
  }
  /* Check the parameters */
  assert_param(IS_DAC_ALL_INSTANCE(hdac->Instance));
  
  if(hdac->State == HAL_DAC_STATE_RESET)
  {  
    /* Init the low level hardware */
    HAL_DAC_MspInit(hdac);
  }
  
  /* Initialize the DAC state*/
  hdac->State = HAL_DAC_STATE_BUSY;
  
  /* Set DAC error code to none */
  hdac->ErrorCode = HAL_DAC_ERROR_NONE;
  
  /* Initialize the DAC state*/
  hdac->State = HAL_DAC_STATE_READY;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_DeInit(DAC_HandleTypeDef* hdac)
{
  /* Check DAC handle */
  if(hdac == NULL)
  {
     return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DAC_ALL_INSTANCE(hdac->Instance));

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;

  /* DeInit the low level hardware */
  HAL_DAC_MspDeInit(hdac);

  /* Set DAC error code to none */
  hdac->ErrorCode = HAL_DAC_ERROR_NONE;

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hdac);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the DAC MSP.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{ 
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  DeInitializes the DAC MSP.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.  
  * @retval None
  */
__weak void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_MspDeInit could be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup DAC_Exported_Functions_Group2 IO operation functions
 *  @brief    IO operation functions 
 *
@verbatim   
  ==============================================================================
             ##### IO operation functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) Start conversion and enable DMA transfer.
      (+) Stop conversion and disable DMA transfer.
      (+) Get result of conversion.
                     
@endverbatim
  * @{
  */

/**
  * @brief  Enables DAC and starts conversion of channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f0xx_hal_dac_ex.c   */
  
  /* Return error status as not implemented here */
  return HAL_ERROR;
}

/**
  * @brief  Disables DAC and stop conversion of channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));
  
  /* Disable the Peripheral */
  __HAL_DAC_DISABLE(hdac, Channel);
  
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Enables DAC and starts conversion of channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  * @param  pData: The destination peripheral Buffer address.
  * @param  Length: The length of data to be transferred from memory to DAC peripheral
  * @param  Alignment: Specifies the data alignment for DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
  *            @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
  *            @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel, uint32_t* pData, uint32_t Length, uint32_t Alignment)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f0xx_hal_dac_ex.c   */
  
  /* Return error status as not implemented here */
  return HAL_ERROR;
}

/**
  * @brief  Disables DAC and stop conversion of channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
   HAL_StatusTypeDef status = HAL_OK;
    
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));
  
  /* Disable the selected DAC channel DMA request */
    hdac->Instance->CR &= ~(DAC_CR_DMAEN1 << Channel);
    
  /* Disable the Peripharal */
  __HAL_DAC_DISABLE(hdac, Channel);
  
  /* Disable the DMA Channel */
  /* Channel1 is used */
  if (Channel == DAC_CHANNEL_1)
  {
    status = HAL_DMA_Abort(hdac->DMA_Handle1);   
  }
  else /* Channel2 is used for */
  {
    status = HAL_DMA_Abort(hdac->DMA_Handle2);   
  }

  /* Check if DMA Channel effectively disabled */
  if (status != HAL_OK)
  {
  /* Update DAC state machine to error */
  hdac->State = HAL_DAC_STATE_ERROR; 
  }
  else
  {
  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Conversion complete callback in non blocking mode for Channel1 
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_ConvCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Conversion half DMA transfer callback in non blocking mode for Channel1 
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef* hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_ConvHalfCpltCallbackCh1 could be implemented in the user file
   */
}

/**
  * @brief  Error DAC callback for Channel1.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_ErrorCallback could be implemented in the user file
   */
}

/**
  * @brief  DMA underrun DAC callback for channel1.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_DMAUnderrunCallbackCh1(DAC_HandleTypeDef *hdac)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DAC_DMAUnderrunCallbackCh1 could be implemented in the user file
   */
}

/**
  * @}
  */
  
/** @defgroup DAC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief   	Peripheral Control functions 
 *
@verbatim   
  ==============================================================================
             ##### Peripheral Control functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels. 
      (+) Set the specified data holding register value for DAC channel.
      
@endverbatim
  * @{
  */

/**
  * @brief  Configures the selected DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  sConfig: DAC configuration structure.
  * @param  Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef* hdac, DAC_ChannelConfTypeDef* sConfig, uint32_t Channel)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f0xx_hal_dac_ex.c   */
  
  /* Return error status as not implemented here */
  return HAL_ERROR;
}

/**
  * @brief  Set the specified data holding register value for DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected  
  * @param  Alignment: Specifies the data alignment.
  *          This parameter can be one of the following values:
  *            @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
  *            @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
  *            @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
  * @param  Data: Data to be loaded in the selected data holding register.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef* hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data)
{  
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));
  assert_param(IS_DAC_ALIGN(Alignment));
  assert_param(IS_DAC_DATA(Data));
  
  tmp = (uint32_t)hdac->Instance; 
  if(Channel == DAC_CHANNEL_1)
  {
    tmp += __HAL_DHR12R1_ALIGNEMENT(Alignment);
  }
  else
  {
    tmp += __HAL_DHR12R2_ALIGNEMENT(Alignment);
  }

  /* Set the DAC channel1 selected data holding register */
  *(__IO uint32_t *) tmp = Data;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel: The selected DAC channel. 
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  * @retval The selected DAC channel data output value.
  */
__weak uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f0xx_hal_dac_ex.c   */
  
  /* Return error status as not implemented here */
  return HAL_ERROR;
}

/**
  * @}
  */

/** @defgroup DAC_Exported_Functions_Group4 Peripheral State and Errors functions
 *  @brief   Peripheral State and Errors functions 
 *
@verbatim   
  ==============================================================================
            ##### Peripheral State and Errors functions #####
  ==============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Check the DAC state.
      (+) Check the DAC Errors.
        
@endverbatim
  * @{
  */

/**
  * @brief  return the DAC state
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval HAL state
  */
HAL_DAC_StateTypeDef HAL_DAC_GetState(DAC_HandleTypeDef* hdac)
{
  /* Return DAC state */
  return hdac->State;
}


/**
  * @brief  Return the DAC error code
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval DAC Error Code
  */
uint32_t HAL_DAC_GetError(DAC_HandleTypeDef *hdac)
{
  return hdac->ErrorCode;
}

/**
  * @brief  Handles DAC interrupt request  
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
__weak void HAL_DAC_IRQHandler(DAC_HandleTypeDef* hdac)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f0xx_hal_dac_ex.c   */
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

#endif /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#endif /* HAL_DAC_MODULE_ENABLED */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
