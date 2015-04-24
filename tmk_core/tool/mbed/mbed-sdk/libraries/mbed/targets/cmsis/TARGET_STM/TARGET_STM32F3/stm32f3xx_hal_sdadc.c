/**
  ******************************************************************************
  * @file    stm32f3xx_hal_sdadc.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Sigma-Delta Analog to Digital Convertor
  *          (SDADC) peripherals:
  *           + Initialization and Configuration
  *           + Regular Channels Configuration
  *           + Injected channels Configuration
  *           + Power saving
  *           + Regular/Injected Channels DMA Configuration
  *           + Interrupts and flags management
  *         
  @verbatim
  ==============================================================================
                    ##### SDADC specific features #####
  ==============================================================================           
  [..] 
  (#) 16-bit sigma delta architecture.
  (#) Self calibration.
  (#) Interrupt generation at the end of calibration, regular/injected conversion  
      and in case of overrun events.
  (#) Single and continuous conversion modes.
  (#) External trigger option with configurable polarity for injected conversion.
  (#) Multi mode (synchronized another SDADC with SDADC1).
  (#) DMA request generation during regular or injected channel conversion.

                     ##### How to use this driver #####
  ==============================================================================
  [..]
    *** Initialization ***
    ======================
    [..]
      (#) As prerequisite, fill in the HAL_SDADC_MspInit() :
        (+) Enable SDADCx clock interface with __SDADCx_CLK_ENABLE().
        (+) Configure SDADCx clock divider with HAL_RCCEx_PeriphCLKConfig.
        (+) Enable power on SDADC with HAL_PWREx_EnableSDADCAnalog().
        (+) Enable the clocks for the SDADC GPIOS with __GPIOx_CLK_ENABLE().
        (+) Configure these SDADC pins in analog mode using HAL_GPIO_Init().
        (+) If interrupt mode is used, enable and configure SDADC global
            interrupt with HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ().
        (+) If DMA mode is used, configure DMA with HAL_DMA_Init and link it
            with SDADC handle using __HAL_LINKDMA.
      (#) Configure the SDADC low power mode, fast conversion mode, slow clock
          mode and SDADC1 reference voltage using the HAL_ADC_Init() function.
          If multiple SDADC are used, please configure first SDADC1 with the
          common reference voltage.
      (#) Prepare channel configurations (input mode, common mode, gain and
          offset) using HAL_SDADC_PrepareChannelConfig and associate channel
          with one configuration using HAL_SDADC_AssociateChannelConfig.

    *** Calibration ***
    ============================================
    [..]
      (#) Start calibration using HAL_SDADC_StartCalibration or
          HAL_SDADC_CalibrationStart_IT.
      (#) In polling mode, use HAL_SDADC_PollForCalibEvent to detect the end of
          calibration.
      (#) In interrupt mode, HAL_SDADC_CalibrationCpltCallback will be called at
          the end of calibration.

    *** Regular channel conversion ***
    ============================================
    [..]    
      (#) Select trigger for regular conversion using
          HAL_SDADC_SelectRegularTrigger.
      (#) Select regular channel and enable/disable continuous mode using
          HAL_SDADC_ConfigChannel.
      (#) Start regular conversion using HAL_SDADC_Start, HAL_SDADC_Start_IT
          or HAL_SDADC_Start_DMA.
      (#) In polling mode, use HAL_SDADC_PollForConversion to detect the end of
          regular conversion.
      (#) In interrupt mode, HAL_SDADC_ConvCpltCallback will be called at the 
          end of regular conversion.
      (#) Get value of regular conversion using HAL_SDADC_GetValue.
      (#) In DMA mode, HAL_SDADC_ConvHalfCpltCallback and 
          HAL_SDADC_ConvCpltCallback will be called respectively at the half 
          tranfer and at the tranfer complete.
      (#) Stop regular conversion using HAL_SDADC_Stop, HAL_SDADC_Stop_IT
          or HAL_SDADC_Stop_DMA.

    *** Injected channels conversion ***
    ============================================
    [..]    
      (#) Enable/disable delay on injected conversion using 
          HAL_SDADC_SelectInjectedDelay.
      (#) If external trigger is used for injected conversion, configure this
          trigger using HAL_SDADC_SelectInjectedExtTrigger.
      (#) Select trigger for injected conversion using
          HAL_SDADC_SelectInjectedTrigger.
      (#) Select injected channels and enable/disable continuous mode using
          HAL_SDADC_InjectedConfigChannel.
      (#) Start injected conversion using HAL_SDADC_InjectedStart,
          HAL_SDADC_InjectedStart_IT or HAL_SDADC_InjectedStart_DMA.
      (#) In polling mode, use HAL_SDADC_PollForInjectedConversion to detect the
          end of injected conversion.
      (#) In interrupt mode, HAL_SDADC_InjectedConvCpltCallback will be called
          at the end of injected conversion.
      (#) Get value of injected conversion and corresponding channel using 
          HAL_SDADC_InjectedGetValue.
      (#) In DMA mode, HAL_SDADC_InjectedConvHalfCpltCallback and 
          HAL_SDADC_InjectedConvCpltCallback will be called respectively at the
          half tranfer and at the tranfer complete.
      (#) Stop injected conversion using HAL_SDADC_InjectedStop, 
          HAL_SDADC_InjectedStop_IT or HAL_SDADC_InjectedStop_DMA.

    *** Multi mode regular channels conversions ***
    ======================================================
    [..]
      (#) Select type of multimode (SDADC1/SDADC2 or SDADC1/SDADC3) using
          HAL_SDADC_MultiModeConfigChannel.
      (#) Select software trigger for SDADC1 and synchronized trigger for
          SDADC2 (or SDADC3) using HAL_SDADC_SelectRegularTrigger.
      (#) Select regular channel for SDADC1 and SDADC2 (or SDADC3) using
          HAL_SDADC_ConfigChannel.
      (#) Start regular conversion for SDADC2 (or SDADC3) with HAL_SDADC_Start.
      (#) Start regular conversion for SDADC1 using HAL_SDADC_Start, 
          HAL_SDADC_Start_IT or HAL_SDADC_MultiModeStart_DMA.
      (#) In polling mode, use HAL_SDADC_PollForConversion to detect the end of
          regular conversion for SDADC1.
      (#) In interrupt mode, HAL_SDADC_ConvCpltCallback will be called at the 
          end of regular conversion for SDADC1.
      (#) Get value of regular conversions using HAL_SDADC_MultiModeGetValue.
      (#) In DMA mode, HAL_SDADC_ConvHalfCpltCallback and 
          HAL_SDADC_ConvCpltCallback will be called respectively at the half 
          tranfer and at the tranfer complete for SDADC1.
      (#) Stop regular conversion using HAL_SDADC_Stop, HAL_SDADC_Stop_IT
          or HAL_SDADC_MultiModeStop_DMA for SDADC1.
      (#) Stop regular conversion using HAL_SDADC_Stop for SDADC2 (or SDADC3).

    *** Multi mode injected channels conversions ***
    ======================================================
    [..]
      (#) Select type of multimode (SDADC1/SDADC2 or SDADC1/SDADC3) using
          HAL_SDADC_InjectedMultiModeConfigChannel.
      (#) Select software or external trigger for SDADC1 and synchronized 
          trigger for SDADC2 (or SDADC3) using HAL_SDADC_SelectInjectedTrigger.
      (#) Select injected channels for SDADC1 and SDADC2 (or SDADC3) using
          HAL_SDADC_InjectedConfigChannel.
      (#) Start injected conversion for SDADC2 (or SDADC3) with 
          HAL_SDADC_InjectedStart.
      (#) Start injected conversion for SDADC1 using HAL_SDADC_InjectedStart,
          HAL_SDADC_InjectedStart_IT or HAL_SDADC_InjectedMultiModeStart_DMA.
      (#) In polling mode, use HAL_SDADC_InjectedPollForConversion to detect 
          the end of injected conversion for SDADC1.
      (#) In interrupt mode, HAL_SDADC_InjectedConvCpltCallback will be called
          at the end of injected conversion for SDADC1.
      (#) Get value of injected conversions using 
          HAL_SDADC_InjectedMultiModeGetValue.
      (#) In DMA mode, HAL_SDADC_InjectedConvHalfCpltCallback and 
          HAL_SDADC_InjectedConvCpltCallback will be called respectively at the
          half tranfer and at the tranfer complete for SDADC1.
      (#) Stop injected conversion using HAL_SDADC_InjectedStop, 
          HAL_SDADC_InjectedStop_IT or HAL_SDADC_InjecteddMultiModeStop_DMA
          for SDADC1.
      (#) Stop injected conversion using HAL_SDADC_InjectedStop for SDADC2
          (or SDADC3).

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

#ifdef HAL_SDADC_MODULE_ENABLED
#if defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup SDADC SDADC HAL module driver
  * @brief SDADC HAL driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup SDADC_Private_Define SDADC Private Define
 * @{
 */
#define SDADC_TIMEOUT          200
#define SDADC_CONFREG_OFFSET   0x00000020
#define SDADC_JDATAR_CH_OFFSET 24
#define SDADC_MSB_MASK         0xFFFF0000
#define SDADC_LSB_MASK         0x0000FFFF
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup SDADC_Private_Functions SDADC Private Functions
  * @{
  */

static HAL_StatusTypeDef SDADC_EnterInitMode(SDADC_HandleTypeDef* hsdadc);
static void              SDADC_ExitInitMode(SDADC_HandleTypeDef* hsdadc);
static uint32_t          SDADC_GetInjChannelsNbr(uint32_t Channels);
static HAL_StatusTypeDef SDADC_RegConvStart(SDADC_HandleTypeDef* hsdadc);
static HAL_StatusTypeDef SDADC_RegConvStop(SDADC_HandleTypeDef* hsdadc);
static HAL_StatusTypeDef SDADC_InjConvStart(SDADC_HandleTypeDef* hsdadc);
static HAL_StatusTypeDef SDADC_InjConvStop(SDADC_HandleTypeDef* hsdadc);
static void              SDADC_DMARegularHalfConvCplt(DMA_HandleTypeDef *hdma);
static void              SDADC_DMARegularConvCplt(DMA_HandleTypeDef *hdma);
static void              SDADC_DMAInjectedHalfConvCplt(DMA_HandleTypeDef *hdma);
static void              SDADC_DMAInjectedConvCplt(DMA_HandleTypeDef *hdma);
static void              SDADC_DMAError(DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup SDADC_Exported_Functions SDADC Exported Functions
  * @{
  */

/** @defgroup SDADC_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and de-initialization functions 
 *
@verbatim    
  ===============================================================================
              ##### Initialization and de-initialization functions #####
  ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the SDADC. 
      (+) De-initialize the SDADC. 
         
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the SDADC according to the specified
  *         parameters in the SDADC_InitTypeDef structure.
  * @note   If multiple SDADC are used, please configure first SDADC1 to set
  *         the common reference voltage.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_SDADC_Init(SDADC_HandleTypeDef* hsdadc)
{
  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_LOWPOWER_MODE(hsdadc->Init.IdleLowPowerMode));
  assert_param(IS_SDADC_FAST_CONV_MODE(hsdadc->Init.FastConversionMode));
  assert_param(IS_SDADC_SLOW_CLOCK_MODE(hsdadc->Init.SlowClockMode));
  assert_param(IS_SDADC_VREF(hsdadc->Init.ReferenceVoltage));
  
  /* Check SDADC handle */
  if(hsdadc == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Initialize SDADC variables with default values */
  hsdadc->RegularContMode     = SDADC_CONTINUOUS_CONV_OFF;
  hsdadc->InjectedContMode    = SDADC_CONTINUOUS_CONV_OFF;
  hsdadc->InjectedChannelsNbr = 1;
  hsdadc->InjConvRemaining    = 1;
  hsdadc->RegularTrigger      = SDADC_SOFTWARE_TRIGGER;
  hsdadc->InjectedTrigger     = SDADC_SOFTWARE_TRIGGER;
  hsdadc->ExtTriggerEdge      = SDADC_EXT_TRIG_RISING_EDGE;
  hsdadc->RegularMultimode    = SDADC_MULTIMODE_SDADC1_SDADC2;
  hsdadc->InjectedMultimode   = SDADC_MULTIMODE_SDADC1_SDADC2;
  hsdadc->ErrorCode           = SDADC_ERROR_NONE;
    
  /* Call MSP init function */
  HAL_SDADC_MspInit(hsdadc);
  
  /* Set idle low power and slow clock modes */
  hsdadc->Instance->CR1 &= ~(SDADC_CR1_SBI|SDADC_CR1_PDI|SDADC_CR1_SLOWCK);
  hsdadc->Instance->CR1 |= (hsdadc->Init.IdleLowPowerMode | \
                            hsdadc->Init.SlowClockMode);

  /* Set fast conversion mode */
  hsdadc->Instance->CR2 &= ~(SDADC_CR2_FAST);
  hsdadc->Instance->CR2 |= hsdadc->Init.FastConversionMode;

  /* Set reference voltage only for SDADC1 */
  if(hsdadc->Instance == SDADC1)
  {
    hsdadc->Instance->CR1 &= ~(SDADC_CR1_REFV);
    hsdadc->Instance->CR1 |= hsdadc->Init.ReferenceVoltage;

    /* Wait at least 2ms before setting ADON */
    HAL_Delay(2);
  }
  
  /* Enable SDADC */
  hsdadc->Instance->CR2 |= SDADC_CR2_ADON;

  /* Wait end of stabilization */
  while((hsdadc->Instance->ISR & SDADC_ISR_STABIP) != 0);
  
  /* Set SDADC to ready state */
  hsdadc->State = HAL_SDADC_STATE_READY;
  
  /* Return HAL status */
  return HAL_OK;
}
  
/**
  * @brief  De-initializes the SDADC.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_SDADC_DeInit(SDADC_HandleTypeDef* hsdadc)
{
  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  
  /* Check SDADC handle */
  if(hsdadc == HAL_NULL)
  {
    return HAL_ERROR;
  }

  /* Disable the SDADC */
  hsdadc->Instance->CR2 &= ~(SDADC_CR2_ADON);

  /* Reset all registers */
  hsdadc->Instance->CR1      = 0x00000000;
  hsdadc->Instance->CR2      = 0x00000000;
  hsdadc->Instance->JCHGR    = 0x00000001;
  hsdadc->Instance->CONF0R   = 0x00000000;
  hsdadc->Instance->CONF1R   = 0x00000000;
  hsdadc->Instance->CONF2R   = 0x00000000;
  hsdadc->Instance->CONFCHR1 = 0x00000000;
  hsdadc->Instance->CONFCHR2 = 0x00000000;

  /* Call MSP deinit function */
  HAL_SDADC_MspDeInit(hsdadc);

  /* Set SDADC in reset state */
  hsdadc->State = HAL_SDADC_STATE_RESET;

  /* Return function status */
  return HAL_OK;
}
    
/**
  * @brief  Initializes the SDADC MSP.
  * @param  hsdadc : SDADC handle
  * @retval None
  */
__weak void HAL_SDADC_MspInit(SDADC_HandleTypeDef* hsdadc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SDADC_MspInit could be implemented in the user file.
   */ 
}

/**
  * @brief  De-initializes the SDADC MSP.
  * @param  hsdadc : SDADC handle
  * @retval None
  */
__weak void HAL_SDADC_MspDeInit(SDADC_HandleTypeDef* hsdadc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SDADC_MspDeInit could be implemented in the user file.
   */ 
}

/**
  * @}
  */

/** @defgroup SDADC_Exported_Functions_Group2 peripheral control functions
 *  @brief    Peripheral control functions
 *
@verbatim   
  ===============================================================================
              ##### Peripheral control functions #####
  ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Program on of the three different configurations for channels.
      (+) Associate channel to one of configurations.
      (+) Select regular and injected channels.
      (+) Enable/disable continuous mode for regular and injected conversions.
      (+) Select regular and injected triggers.
      (+) Select and configure injected external trigger.
      (+) Enable/disable delay addition for injected conversions.
      (+) Configure multimode.

@endverbatim
  * @{
  */

/**
  * @brief  This function allows the user to set parameters for a configuration.
  *         Parameters are input mode, common mode, gain and offset.
  * @note   This function should be called only when SDADC instance is in idle state
  *         (neither calibration nor regular or injected conversion ongoing)
  * @param  hsdadc : SDADC handle.
  * @param  ConfIndex : Index of configuration to modify.
  *         This parameter can be a value of @ref SDADC_ConfIndex.
  * @param  ConfParamStruct : Parameters to apply for this configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_PrepareChannelConfig(SDADC_HandleTypeDef *hsdadc, 
                                                 uint32_t ConfIndex,
                                                 SDADC_ConfParamTypeDef* ConfParamStruct)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t          tmp = 0;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_CONF_INDEX(ConfIndex));
  assert_param(ConfParamStruct != HAL_NULL);
  assert_param(IS_SDADC_INPUT_MODE(ConfParamStruct->InputMode));
  assert_param(IS_SDADC_GAIN(ConfParamStruct->Gain));
  assert_param(IS_SDADC_COMMON_MODE(ConfParamStruct->CommonMode));
  assert_param(IS_SDADC_OFFSET_VALUE(ConfParamStruct->Offset));

  /* Check SDADC state is ready */
  if(hsdadc->State != HAL_SDADC_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_TIMEOUT;
    }
    else
    {
      /* Program configuration register with parameters */
      tmp = (uint32_t)((uint32_t)(hsdadc->Instance) + \
                       SDADC_CONFREG_OFFSET + \
                       (uint32_t)(ConfIndex << 2));
      *(__IO uint32_t *) (tmp) = (uint32_t) (ConfParamStruct->InputMode | \
                                             ConfParamStruct->Gain | \
                                             ConfParamStruct->CommonMode | \
                                             ConfParamStruct->Offset);
      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);
    }
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows the user to associate a channel with one of the
  *         available configurations.
  * @note   This function should be called only when SDADC instance is in idle state
  *         (neither calibration nor regular or injected conversion ongoing)
  * @param  hsdadc : SDADC handle.
  * @param  Channel : Channel to associate with configuration.
  *         This parameter can be a value of @ref SDADC_Channel_Selection.
  * @param  ConfIndex : Index of configuration to associate with channel.
  *         This parameter can be a value of @ref SDADC_ConfIndex.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_AssociateChannelConfig(SDADC_HandleTypeDef *hsdadc,
                                                   uint32_t Channel,
                                                   uint32_t ConfIndex)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t          channelnum = 0;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_REGULAR_CHANNEL(Channel));
  assert_param(IS_SDADC_CONF_INDEX(ConfIndex));

  /* Check SDADC state is ready */
  if(hsdadc->State != HAL_SDADC_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_TIMEOUT;
    }
    else
    {
      /* Program channel configuration register according parameters */
      if(Channel != SDADC_CHANNEL_8)
      {
        /* Get channel number */
        channelnum = (uint32_t)(Channel>>16);

        /* Set the channel configuration */
        hsdadc->Instance->CONFCHR1 &= (uint32_t) ~(SDADC_CONFCHR1_CONFCH0 << (channelnum << 2));
        hsdadc->Instance->CONFCHR1 |= (uint32_t) (ConfIndex << (channelnum << 2));
      }
      else
      {
        hsdadc->Instance->CONFCHR2 = (uint32_t) (ConfIndex);
      }      
      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);
    }
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to select channel for regular conversion and
  *         to enable/disable continuous mode for regular conversion.
  * @param  hsdadc : SDADC handle.
  * @param  Channel : Channel for regular conversion.
  *         This parameter can be a value of @ref SDADC_Channel_Selection.
  * @param  ContinuousMode : Enable/disable continuous mode for regular conversion.
  *         This parameter can be a value of @ref SDADC_ContinuousMode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_ConfigChannel(SDADC_HandleTypeDef *hsdadc,
                                          uint32_t Channel,
                                          uint32_t ContinuousMode)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_REGULAR_CHANNEL(Channel));
  assert_param(IS_SDADC_CONTINUOUS_MODE(ContinuousMode));
  
  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_RESET) && (hsdadc->State != HAL_SDADC_STATE_ERROR))
  {
    /* Set RCH[3:0] and RCONT bits in SDADC_CR2 */
    hsdadc->Instance->CR2 &= (uint32_t) ~(SDADC_CR2_RCH | SDADC_CR2_RCONT);
    if(ContinuousMode == SDADC_CONTINUOUS_CONV_ON)
    {
      hsdadc->Instance->CR2 |= (uint32_t) ((Channel & SDADC_MSB_MASK) | SDADC_CR2_RCONT);    
    }
    else
    {
      hsdadc->Instance->CR2 |= (uint32_t) ((Channel & SDADC_MSB_MASK));    
    }
    /* Store continuous mode information */
    hsdadc->RegularContMode = ContinuousMode;
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to select channels for injected conversion and
  *         to enable/disable continuous mode for injected conversion.
  * @param  hsdadc : SDADC handle.
  * @param  Channel : Channels for injected conversion.
  *         This parameter can be a values combination of @ref SDADC_Channel_Selection.
  * @param  ContinuousMode : Enable/disable continuous mode for injected conversion.
  *         This parameter can be a value of @ref SDADC_ContinuousMode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedConfigChannel(SDADC_HandleTypeDef *hsdadc,
                                                  uint32_t Channel,
                                                  uint32_t ContinuousMode)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_INJECTED_CHANNEL(Channel));
  assert_param(IS_SDADC_CONTINUOUS_MODE(ContinuousMode));
  
  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_RESET) && (hsdadc->State != HAL_SDADC_STATE_ERROR))
  {
    /* Set JCHG[8:0] bits in SDADC_JCHG */
    hsdadc->Instance->JCHGR = (uint32_t) (Channel & SDADC_LSB_MASK);
    /* Set or clear JCONT bit in SDADC_CR2 */
    if(ContinuousMode == SDADC_CONTINUOUS_CONV_ON)
    {
      hsdadc->Instance->CR2 |= SDADC_CR2_JCONT;    
    }
    else
    {
      hsdadc->Instance->CR2 &= ~(SDADC_CR2_JCONT);
    }
    /* Store continuous mode information */
    hsdadc->InjectedContMode = ContinuousMode;
    /* Store number of injected channels */
    hsdadc->InjectedChannelsNbr = SDADC_GetInjChannelsNbr(Channel);
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to select trigger for regular conversions.
  * @note   This function should not be called if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  Trigger : Trigger for regular conversions.
  *         This parameter can be one of the following value :
  *            @arg SDADC_SOFTWARE_TRIGGER : Software trigger.
  *            @arg SDADC_SYNCHRONOUS_TRIGGER : Synchronous with SDADC1 (only for SDADC2 and SDADC3).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_SelectRegularTrigger(SDADC_HandleTypeDef *hsdadc, uint32_t Trigger)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_REGULAR_TRIGGER(Trigger));

  /* Check parameters compatibility */
  if((hsdadc->Instance == SDADC1) && (Trigger == SDADC_SYNCHRONOUS_TRIGGER))
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State == HAL_SDADC_STATE_READY) || \
          (hsdadc->State == HAL_SDADC_STATE_CALIB) || \
          (hsdadc->State == HAL_SDADC_STATE_INJ))
  {
    /* Store regular trigger information */
    hsdadc->RegularTrigger = Trigger;
  }
  else
  {
    status = HAL_ERROR;    
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to select trigger for injected conversions.
  * @note   This function should not be called if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  Trigger : Trigger for injected conversions.
  *         This parameter can be one of the following value :
  *            @arg SDADC_SOFTWARE_TRIGGER : Software trigger.
  *            @arg SDADC_SYNCHRONOUS_TRIGGER : Synchronous with SDADC1 (only for SDADC2 and SDADC3).
  *            @arg SDADC_EXTERNAL_TRIGGER : External trigger.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_SelectInjectedTrigger(SDADC_HandleTypeDef *hsdadc, uint32_t Trigger)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_INJECTED_TRIGGER(Trigger));

  /* Check parameters compatibility */
  if((hsdadc->Instance == SDADC1) && (Trigger == SDADC_SYNCHRONOUS_TRIGGER))
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State == HAL_SDADC_STATE_READY) || \
          (hsdadc->State == HAL_SDADC_STATE_CALIB) || \
          (hsdadc->State == HAL_SDADC_STATE_REG))
  {
    /* Store regular trigger information */
    hsdadc->InjectedTrigger = Trigger;
  }
  else
  {
    status = HAL_ERROR;    
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to select and configure injected external trigger.
  * @note   This function should be called only when SDADC instance is in idle state
  *         (neither calibration nor regular or injected conversion ongoing)
  * @param  hsdadc : SDADC handle.
  * @param  InjectedExtTrigger : External trigger for injected conversions.
  *         This parameter can be a value of @ref SDADC_InjectedExtTrigger.
  * @param  ExtTriggerEdge : Edge of external injected trigger.
  *         This parameter can be a value of @ref SDADC_ExtTriggerEdge.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_SelectInjectedExtTrigger(SDADC_HandleTypeDef *hsdadc,
                                                     uint32_t InjectedExtTrigger,
                                                     uint32_t ExtTriggerEdge)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_EXT_INJEC_TRIG(InjectedExtTrigger));
  assert_param(IS_SDADC_EXT_TRIG_EDGE(ExtTriggerEdge));

  /* Check SDADC state */
  if(hsdadc->State == HAL_SDADC_STATE_READY)
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_TIMEOUT;
    }
    else
    {
      /* Set JEXTSEL[2:0] bits in SDADC_CR2 register */
      hsdadc->Instance->CR2 &= ~(SDADC_CR2_JEXTSEL);
      hsdadc->Instance->CR2 |= InjectedExtTrigger;

      /* Store external trigger edge information */
      hsdadc->ExtTriggerEdge = ExtTriggerEdge;

      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to enable/disable delay addition for injected conversions.
  * @note   This function should be called only when SDADC instance is in idle state
  *         (neither calibration nor regular or injected conversion ongoing)
  * @param  hsdadc : SDADC handle.
  * @param  InjectedDelay : Enable/disable delay for injected conversions.
  *         This parameter can be a value of @ref SDADC_InjectedDelay.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_SelectInjectedDelay(SDADC_HandleTypeDef *hsdadc,
                                                uint32_t InjectedDelay)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_INJECTED_DELAY(InjectedDelay));

  /* Check SDADC state */
  if(hsdadc->State == HAL_SDADC_STATE_READY)
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_TIMEOUT;
    }
    else
    {
      /* Set JDS bit in SDADC_CR2 register */
      hsdadc->Instance->CR2 &= ~(SDADC_CR2_JDS);
      hsdadc->Instance->CR2 |= InjectedDelay;

      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to configure multimode for regular conversions.
  * @note   This function should not be called if regular conversion is ongoing
  *         and should be could only for SDADC1.
  * @param  hsdadc : SDADC handle.
  * @param  MultimodeType : Type of multimode for regular conversions.
  *         This parameter can be a value of @ref SDADC_MultimodeType.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_MultiModeConfigChannel(SDADC_HandleTypeDef* hsdadc,
                                                   uint32_t MultimodeType)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_MULTIMODE_TYPE(MultimodeType));

  /* Check instance is SDADC1 */
  if(hsdadc->Instance != SDADC1)
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State == HAL_SDADC_STATE_READY) || \
          (hsdadc->State == HAL_SDADC_STATE_CALIB) || \
          (hsdadc->State == HAL_SDADC_STATE_INJ))
  {
    /* Store regular trigger information */
    hsdadc->RegularMultimode = MultimodeType;
  }
  else
  {
    status = HAL_ERROR;    
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to configure multimode for injected conversions.
  * @note   This function should not be called if injected conversion is ongoing
  *         and should be could only for SDADC1.
  * @param  hsdadc : SDADC handle.
  * @param  MultimodeType : Type of multimode for injected conversions.
  *         This parameter can be a value of @ref SDADC_MultimodeType.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedMultiModeConfigChannel(SDADC_HandleTypeDef* hsdadc,
                                                           uint32_t MultimodeType)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_MULTIMODE_TYPE(MultimodeType));

  /* Check instance is SDADC1 */
  if(hsdadc->Instance != SDADC1)
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State == HAL_SDADC_STATE_READY) || \
          (hsdadc->State == HAL_SDADC_STATE_CALIB) || \
          (hsdadc->State == HAL_SDADC_STATE_REG))
  {
    /* Store regular trigger information */
    hsdadc->InjectedMultimode = MultimodeType;
  }
  else
  {
    status = HAL_ERROR;    
  }
  /* Return function status */
  return status;
}

/**
  * @}
  */

/** @defgroup SDADC_Exported_Functions_Group3 Input and Output operation functions
 *  @brief    I/O operation Control functions 
 *
@verbatim   
  ===============================================================================
              ##### I/O operation functions #####
  ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Start calibration.
      (+) Poll for the end of calibration.
      (+) Start calibration and enable interrupt.
      (+) Start conversion of regular/injected channel.
      (+) Poll for the end of regular/injected conversion.
      (+) Stop conversion of regular/injected channel.
      (+) Start conversion of regular/injected channel and enable interrupt.
      (+) Stop conversion of regular/injected channel and disable interrupt.
      (+) Start conversion of regular/injected channel and enable DMA transfer.
      (+) Stop conversion of regular/injected channel and disable DMA transfer.
      (+) Start multimode and enable DMA transfer for regular/injected conversion.
      (+) Stop multimode and disable DMA transfer for regular/injected conversion..
      (+) Get result of regular channel conversion.
      (+) Get result of injected channel conversion.
      (+) Get result of multimode conversion.
      (+) Handle SDADC interrupt request.
      (+) Callbacks for calibration and regular/injected conversions.

@endverbatim
  * @{
  */

/**
  * @brief  This function allows to start calibration in polling mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         (neither calibration nor regular or injected conversion ongoing).
  * @param  hsdadc : SDADC handle.
  * @param  CalibrationSequence : Calibration sequence.
  *         This parameter can be a value of @ref SDADC_CalibrationSequence.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_CalibrationStart(SDADC_HandleTypeDef *hsdadc,
                                             uint32_t CalibrationSequence)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_CALIB_SEQUENCE(CalibrationSequence));

  /* Check SDADC state */
  if(hsdadc->State == HAL_SDADC_STATE_READY)
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_TIMEOUT;
    }
    else
    {
      /* Set CALIBCNT[1:0] bits in SDADC_CR2 register */
      hsdadc->Instance->CR2 &= ~(SDADC_CR2_CALIBCNT);
      hsdadc->Instance->CR2 |= CalibrationSequence;

      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);

      /* Set STARTCALIB in SDADC_CR2 */
      hsdadc->Instance->CR2 |= SDADC_CR2_STARTCALIB;

      /* Set SDADC in calibration state */
      hsdadc->State = HAL_SDADC_STATE_CALIB;
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to poll for the end of calibration.
  * @note   This function should be called only if calibration is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  Timeout : Timeout value in milliseconds.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_PollForCalibEvent(SDADC_HandleTypeDef* hsdadc, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if(hsdadc->State != HAL_SDADC_STATE_CALIB)
  {
    /* Return error status */
    return HAL_ERROR;
  }
  else
  {
    /* Get timeout */
    tickstart = HAL_GetTick();  

    /* Wait EOCALF bit in SDADC_ISR register */
    while((hsdadc->Instance->ISR & SDADC_ISR_EOCALF) != SDADC_ISR_EOCALF)
    {
      /* Check the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Return timeout status */
          return HAL_TIMEOUT;
        }
      }
    }
    /* Set CLREOCALF bit in SDADC_CLRISR register */
    hsdadc->Instance->CLRISR |= SDADC_ISR_CLREOCALF;

    /* Set SDADC in ready state */
    hsdadc->State = HAL_SDADC_STATE_READY;

    /* Return function status */
    return HAL_OK;
  }
}

/**
  * @brief  This function allows to start calibration in interrupt mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         (neither calibration nor regular or injected conversion ongoing).
  * @param  hsdadc : SDADC handle.
  * @param  CalibrationSequence : Calibration sequence.
  *         This parameter can be a value of @ref SDADC_CalibrationSequence.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_CalibrationStart_IT(SDADC_HandleTypeDef *hsdadc,
                                                uint32_t CalibrationSequence)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(IS_SDADC_CALIB_SEQUENCE(CalibrationSequence));

  /* Check SDADC state */
  if(hsdadc->State == HAL_SDADC_STATE_READY)
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_TIMEOUT;
    }
    else
    {
      /* Set CALIBCNT[1:0] bits in SDADC_CR2 register */
      hsdadc->Instance->CR2 &= ~(SDADC_CR2_CALIBCNT);
      hsdadc->Instance->CR2 |= CalibrationSequence;

      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);

      /* Set EOCALIE bit in SDADC_CR1 register */
      hsdadc->Instance->CR1 |= SDADC_CR1_EOCALIE;

      /* Set STARTCALIB in SDADC_CR2 */
      hsdadc->Instance->CR2 |= SDADC_CR2_STARTCALIB;

      /* Set SDADC in calibration state */
      hsdadc->State = HAL_SDADC_STATE_CALIB;
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to start regular conversion in polling mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         or if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_Start(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State == HAL_SDADC_STATE_READY) || \
     (hsdadc->State == HAL_SDADC_STATE_INJ))
  {
    /* Start regular conversion */
    status = SDADC_RegConvStart(hsdadc);
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to poll for the end of regular conversion.
  * @note   This function should be called only if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  Timeout : Timeout value in milliseconds.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_PollForConversion(SDADC_HandleTypeDef* hsdadc, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_REG) && \
     (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    return HAL_ERROR;
  }
  else
  {
    /* Get timeout */
    tickstart = HAL_GetTick();  

    /* Wait REOCF bit in SDADC_ISR register */
    while((hsdadc->Instance->ISR & SDADC_ISR_REOCF) != SDADC_ISR_REOCF)
    {
      /* Check the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Return timeout status */
          return HAL_TIMEOUT;
        }
      }
    }
    /* Check if overrun occurs */
    if((hsdadc->Instance->ISR & SDADC_ISR_ROVRF) == SDADC_ISR_ROVRF)
    {
      /* Update error code and call error callback */
      hsdadc->ErrorCode = SDADC_ERROR_REGULAR_OVERRUN;
      HAL_SDADC_ErrorCallback(hsdadc);

      /* Set CLRROVRF bit in SDADC_CLRISR register */
      hsdadc->Instance->CLRISR |= SDADC_ISR_CLRROVRF;
    }
    /* Update SDADC state only if not continuous conversion and SW trigger */
    if((hsdadc->RegularContMode == SDADC_CONTINUOUS_CONV_OFF) && \
       (hsdadc->RegularTrigger == SDADC_SOFTWARE_TRIGGER))
    {
      hsdadc->State = (hsdadc->State == HAL_SDADC_STATE_REG) ? \
                      HAL_SDADC_STATE_READY : HAL_SDADC_STATE_INJ;
    }
    /* Return function status */
    return HAL_OK;
  }
}

/**
  * @brief  This function allows to stop regular conversion in polling mode.
  * @note   This function should be called only if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_Stop(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_REG) && \
     (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    status = HAL_ERROR;
  }
  else
  {
    /* Stop regular conversion */
    status = SDADC_RegConvStop(hsdadc);
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to start regular conversion in interrupt mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         or if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_Start_IT(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State == HAL_SDADC_STATE_READY) || \
     (hsdadc->State == HAL_SDADC_STATE_INJ))
  {
    /* Set REOCIE and ROVRIE bits in SDADC_CR1 register */
    hsdadc->Instance->CR1 |= (uint32_t) (SDADC_CR1_REOCIE | SDADC_CR1_ROVRIE);

    /* Start regular conversion */
    status = SDADC_RegConvStart(hsdadc);
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to stop regular conversion in interrupt mode.
  * @note   This function should be called only if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_Stop_IT(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_REG) && \
     (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    status = HAL_ERROR;
  }
  else
  {
    /* Clear REOCIE and ROVRIE bits in SDADC_CR1 register */
    hsdadc->Instance->CR1 &= (uint32_t) ~(SDADC_CR1_REOCIE | SDADC_CR1_ROVRIE);

    /* Stop regular conversion */
    status = SDADC_RegConvStop(hsdadc);
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to start regular conversion in DMA mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         or if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  pData : The destination buffer address.
  * @param  Length : The length of data to be transferred from SDADC peripheral to memory.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_Start_DMA(SDADC_HandleTypeDef *hsdadc, uint32_t *pData,
                                      uint32_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(pData != HAL_NULL);
  assert_param(Length != 0);

  /* Check that DMA is not enabled for injected conversion */
  if((hsdadc->Instance->CR1 & SDADC_CR1_JDMAEN) == SDADC_CR1_JDMAEN)
  {
    status = HAL_ERROR;
  }
  /* Check parameters compatibility */
  else if((hsdadc->RegularTrigger == SDADC_SOFTWARE_TRIGGER) && \
          (hsdadc->RegularContMode == SDADC_CONTINUOUS_CONV_OFF) && \
          (hsdadc->hdma->Init.Mode == DMA_NORMAL) && \
          (Length != 1))
  {
    status = HAL_ERROR;
  }
  else if((hsdadc->RegularTrigger == SDADC_SOFTWARE_TRIGGER) && \
          (hsdadc->RegularContMode == SDADC_CONTINUOUS_CONV_OFF) && \
          (hsdadc->hdma->Init.Mode == DMA_CIRCULAR))
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State == HAL_SDADC_STATE_READY) || \
          (hsdadc->State == HAL_SDADC_STATE_INJ))
  {
    /* Set callbacks on DMA handler */
    hsdadc->hdma->XferCpltCallback = SDADC_DMARegularConvCplt;
    hsdadc->hdma->XferErrorCallback = SDADC_DMAError;
    if(hsdadc->hdma->Init.Mode == DMA_CIRCULAR)
    {
      hsdadc->hdma->XferHalfCpltCallback = SDADC_DMARegularHalfConvCplt;
    }
    
    /* Set RDMAEN bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 |= SDADC_CR1_RDMAEN;

    /* Start DMA in interrupt mode */
    if(HAL_DMA_Start_IT(hsdadc->hdma, (uint32_t)&hsdadc->Instance->RDATAR, \
                        (uint32_t) pData, Length) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_ERROR;
    }
    else
    {
      /* Start regular conversion */
      status = SDADC_RegConvStart(hsdadc);
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to stop regular conversion in DMA mode.
  * @note   This function should be called only if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_Stop_DMA(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_REG) && \
     (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    status = HAL_ERROR;
  }
  else
  {
    /* Clear RDMAEN bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 &= ~(SDADC_CR1_RDMAEN);

    /* Stop current DMA transfer */
    if(HAL_DMA_Abort(hsdadc->hdma) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_ERROR;
    }
    else
    {
      /* Stop regular conversion */
      status = SDADC_RegConvStop(hsdadc);
    }
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to get regular conversion value.
  * @param  hsdadc : SDADC handle.
  * @retval Regular conversion value
  */
uint32_t HAL_SDADC_GetValue(SDADC_HandleTypeDef *hsdadc)
{
  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Return regular conversion value */
  return hsdadc->Instance->RDATAR;
}

/**
  * @brief  This function allows to start injected conversion in polling mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         or if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedStart(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State == HAL_SDADC_STATE_READY) || \
     (hsdadc->State == HAL_SDADC_STATE_REG))
  {
    /* Start injected conversion */
    status = SDADC_InjConvStart(hsdadc);
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to poll for the end of injected conversion.
  * @note   This function should be called only if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  Timeout : Timeout value in milliseconds.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_PollForInjectedConversion(SDADC_HandleTypeDef* hsdadc,
                                                      uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_INJ) && \
     (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    return HAL_ERROR;
  }
  else
  {
    /* Get timeout */
    tickstart = HAL_GetTick();  

    /* Wait JEOCF bit in SDADC_ISR register */
    while((hsdadc->Instance->ISR & SDADC_ISR_JEOCF) != SDADC_ISR_JEOCF)
    {
      /* Check the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Return timeout status */
          return HAL_TIMEOUT;
        }
      }
    }
    /* Check if overrun occurs */
    if((hsdadc->Instance->ISR & SDADC_ISR_JOVRF) == SDADC_ISR_JOVRF)
    {
      /* Update error code and call error callback */
      hsdadc->ErrorCode = SDADC_ERROR_INJECTED_OVERRUN;
      HAL_SDADC_ErrorCallback(hsdadc);

      /* Set CLRJOVRF bit in SDADC_CLRISR register */
      hsdadc->Instance->CLRISR |= SDADC_ISR_CLRJOVRF;
    }
    /* Update remaining injected conversions */
    hsdadc->InjConvRemaining--;
    if(hsdadc->InjConvRemaining == 0)
    {
      /* end of injected sequence, reset the value */
      hsdadc->InjConvRemaining = hsdadc->InjectedChannelsNbr;
    }

    /* Update SDADC state only if not continuous conversion, SW trigger */
    /* and end of injected sequence */
    if((hsdadc->InjectedContMode == SDADC_CONTINUOUS_CONV_OFF) && \
       (hsdadc->InjectedTrigger == SDADC_SOFTWARE_TRIGGER) && \
       (hsdadc->InjConvRemaining == hsdadc->InjectedChannelsNbr))
    {
      hsdadc->State = (hsdadc->State == HAL_SDADC_STATE_INJ) ? \
                      HAL_SDADC_STATE_READY : HAL_SDADC_STATE_REG;
    }
    /* Return function status */
    return HAL_OK;
  }
}

/**
  * @brief  This function allows to stop injected conversion in polling mode.
  * @note   This function should be called only if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedStop(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_INJ) && \
     (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    status = HAL_ERROR;
  }
  else
  {
    /* Stop injected conversion */
    status = SDADC_InjConvStop(hsdadc);
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to start injected conversion in interrupt mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         or if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedStart_IT(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State == HAL_SDADC_STATE_READY) || \
     (hsdadc->State == HAL_SDADC_STATE_REG))
  {
    /* Set JEOCIE and JOVRIE bits in SDADC_CR1 register */
    hsdadc->Instance->CR1 |= (uint32_t) (SDADC_CR1_JEOCIE | SDADC_CR1_JOVRIE);

    /* Start injected conversion */
    status = SDADC_InjConvStart(hsdadc);
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to stop injected conversion in interrupt mode.
  * @note   This function should be called only if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedStop_IT(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_INJ) && \
     (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    status = HAL_ERROR;
  }
  else
  {
    /* Clear JEOCIE and JOVRIE bits in SDADC_CR1 register */
    hsdadc->Instance->CR1 &= (uint32_t) ~(SDADC_CR1_JEOCIE | SDADC_CR1_JOVRIE);

    /* Stop injected conversion */
    status = SDADC_InjConvStop(hsdadc);
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to start injected conversion in DMA mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         or if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  pData : The destination buffer address.
  * @param  Length : The length of data to be transferred from SDADC peripheral to memory.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedStart_DMA(SDADC_HandleTypeDef *hsdadc, uint32_t *pData,
                                              uint32_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(pData != HAL_NULL);
  assert_param(Length != 0);

  /* Check that DMA is not enabled for regular conversion */
  if((hsdadc->Instance->CR1 & SDADC_CR1_RDMAEN) == SDADC_CR1_RDMAEN)
  {
    status = HAL_ERROR;
  }
  /* Check parameters compatibility */
  else if((hsdadc->InjectedTrigger == SDADC_SOFTWARE_TRIGGER) && \
          (hsdadc->InjectedContMode == SDADC_CONTINUOUS_CONV_OFF) && \
          (hsdadc->hdma->Init.Mode == DMA_NORMAL) && \
          (Length > hsdadc->InjectedChannelsNbr))
  {
    status = HAL_ERROR;
  }
  else if((hsdadc->InjectedTrigger == SDADC_SOFTWARE_TRIGGER) && \
          (hsdadc->InjectedContMode == SDADC_CONTINUOUS_CONV_OFF) && \
          (hsdadc->hdma->Init.Mode == DMA_CIRCULAR))
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State == HAL_SDADC_STATE_READY) || \
          (hsdadc->State == HAL_SDADC_STATE_REG))
  {
    /* Set callbacks on DMA handler */
    hsdadc->hdma->XferCpltCallback = SDADC_DMAInjectedConvCplt;
    hsdadc->hdma->XferErrorCallback = SDADC_DMAError;
    if(hsdadc->hdma->Init.Mode == DMA_CIRCULAR)
    {
      hsdadc->hdma->XferHalfCpltCallback = SDADC_DMAInjectedHalfConvCplt;
    }
    
    /* Set JDMAEN bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 |= SDADC_CR1_JDMAEN;

    /* Start DMA in interrupt mode */
    if(HAL_DMA_Start_IT(hsdadc->hdma, (uint32_t)&hsdadc->Instance->JDATAR, \
                        (uint32_t) pData, Length) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_ERROR;
    }
    else
    {
      /* Start injected conversion */
      status = SDADC_InjConvStart(hsdadc);
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to stop injected conversion in DMA mode.
  * @note   This function should be called only if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedStop_DMA(SDADC_HandleTypeDef *hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check SDADC state */
  if((hsdadc->State != HAL_SDADC_STATE_INJ) && \
     (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    status = HAL_ERROR;
  }
  else
  {
    /* Clear JDMAEN bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 &= ~(SDADC_CR1_JDMAEN);

    /* Stop current DMA transfer */
    if(HAL_DMA_Abort(hsdadc->hdma) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_ERROR;
    }
    else
    {
      /* Stop injected conversion */
      status = SDADC_InjConvStop(hsdadc);
    }
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to get injected conversion value.
  * @param  hsdadc : SDADC handle.
  * @param  Channel : Corresponding channel of injected conversion.
  * @retval Injected conversion value
  */
uint32_t HAL_SDADC_InjectedGetValue(SDADC_HandleTypeDef *hsdadc, uint32_t* Channel)
{
  uint32_t value = 0;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(Channel != HAL_NULL);

  /* Read SDADC_JDATAR register and extract channel and conversion value */
  value = hsdadc->Instance->JDATAR;
  *Channel = ((value & SDADC_JDATAR_JDATACH) >> SDADC_JDATAR_CH_OFFSET);
  value &= SDADC_JDATAR_JDATA;
  
  /* Return injected conversion value */
  return value;
}

/**
  * @brief  This function allows to start multimode regular conversions in DMA mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         or if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  pData : The destination buffer address.
  * @param  Length : The length of data to be transferred from SDADC peripheral to memory.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_MultiModeStart_DMA(SDADC_HandleTypeDef* hsdadc, uint32_t* pData,
                                               uint32_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(pData != HAL_NULL);
  assert_param(Length != 0);

  /* Check instance is SDADC1 */
  if(hsdadc->Instance != SDADC1)
  {
    status = HAL_ERROR;
  }
  /* Check that DMA is not enabled for injected conversion */
  else if((hsdadc->Instance->CR1 & SDADC_CR1_JDMAEN) == SDADC_CR1_JDMAEN)
  {
    status = HAL_ERROR;
  }
  /* Check parameters compatibility */
  else if((hsdadc->RegularTrigger == SDADC_SOFTWARE_TRIGGER) && \
          (hsdadc->RegularContMode == SDADC_CONTINUOUS_CONV_OFF) && \
          (hsdadc->hdma->Init.Mode == DMA_NORMAL) && \
          (Length != 1))
  {
    status = HAL_ERROR;
  }
  else if((hsdadc->RegularTrigger == SDADC_SOFTWARE_TRIGGER) && \
          (hsdadc->RegularContMode == SDADC_CONTINUOUS_CONV_OFF) && \
          (hsdadc->hdma->Init.Mode == DMA_CIRCULAR))
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State == HAL_SDADC_STATE_READY) || \
          (hsdadc->State == HAL_SDADC_STATE_INJ))
  {
    /* Set callbacks on DMA handler */
    hsdadc->hdma->XferCpltCallback = SDADC_DMARegularConvCplt;
    hsdadc->hdma->XferErrorCallback = SDADC_DMAError;
    if(hsdadc->hdma->Init.Mode == DMA_CIRCULAR)
    {
      hsdadc->hdma->XferHalfCpltCallback = SDADC_DMARegularHalfConvCplt;
    }
    /* Set RDMAEN bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 |= SDADC_CR1_RDMAEN;

    /* Start DMA in interrupt mode */
    if(hsdadc->RegularMultimode == SDADC_MULTIMODE_SDADC1_SDADC2)
    {
      status = HAL_DMA_Start_IT(hsdadc->hdma, (uint32_t)&hsdadc->Instance->RDATA12R, \
                                (uint32_t) pData, Length);
    }
    else
    {
      status = HAL_DMA_Start_IT(hsdadc->hdma, (uint32_t)&hsdadc->Instance->RDATA13R, \
                                (uint32_t) pData, Length);
    }
    if(status != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_ERROR;
    }
    else
    {
      /* Start regular conversion */
      status = SDADC_RegConvStart(hsdadc);
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to stop multimode regular conversions in DMA mode.
  * @note   This function should be called only if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_MultiModeStop_DMA(SDADC_HandleTypeDef* hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check instance is SDADC1 */
  if(hsdadc->Instance != SDADC1)
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State != HAL_SDADC_STATE_REG) && \
          (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    status = HAL_ERROR;
  }
  else
  {
    /* Clear RDMAEN bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 &= ~(SDADC_CR1_RDMAEN);

    /* Stop current DMA transfer */
    if(HAL_DMA_Abort(hsdadc->hdma) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_ERROR;
    }
    else
    {
      /* Stop regular conversion */
      status = SDADC_RegConvStop(hsdadc);
    }
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to get multimode regular conversion value.
  * @param  hsdadc : SDADC handle.
  * @retval Multimode regular conversion value
  */
uint32_t HAL_SDADC_MultiModeGetValue(SDADC_HandleTypeDef* hsdadc)
{
  uint32_t value = 0;
  
  /* Check parameters and check instance is SDADC1 */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(hsdadc->Instance == SDADC1);

  /* read multimode regular value */
  value = (hsdadc->RegularMultimode == SDADC_MULTIMODE_SDADC1_SDADC2) ? \
          hsdadc->Instance->RDATA12R : hsdadc->Instance->RDATA13R;

  /* Return multimode regular conversions value */
  return value;
}

/**
  * @brief  This function allows to start multimode injected conversions in DMA mode.
  * @note   This function should be called only when SDADC instance is in idle state
  *         or if regular conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @param  pData : The destination buffer address.
  * @param  Length : The length of data to be transferred from SDADC peripheral to memory.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedMultiModeStart_DMA(SDADC_HandleTypeDef* hsdadc,
                                                       uint32_t* pData, uint32_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(pData != HAL_NULL);
  assert_param(Length != 0);

  /* Check instance is SDADC1 */
  if(hsdadc->Instance != SDADC1)
  {
    status = HAL_ERROR;
  }
  /* Check that DMA is not enabled for regular conversion */
  else if((hsdadc->Instance->CR1 & SDADC_CR1_RDMAEN) == SDADC_CR1_RDMAEN)
  {
    status = HAL_ERROR;
  }
  /* Check parameters compatibility */
  else if((hsdadc->InjectedTrigger == SDADC_SOFTWARE_TRIGGER) && \
          (hsdadc->InjectedContMode == SDADC_CONTINUOUS_CONV_OFF) && \
          (hsdadc->hdma->Init.Mode == DMA_NORMAL) && \
          (Length > (hsdadc->InjectedChannelsNbr << 1)))
  {
    status = HAL_ERROR;
  }
  else if((hsdadc->InjectedTrigger == SDADC_SOFTWARE_TRIGGER) && \
          (hsdadc->InjectedContMode == SDADC_CONTINUOUS_CONV_OFF) && \
          (hsdadc->hdma->Init.Mode == DMA_CIRCULAR))
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State == HAL_SDADC_STATE_READY) || \
          (hsdadc->State == HAL_SDADC_STATE_REG))
  {
    /* Set callbacks on DMA handler */
    hsdadc->hdma->XferCpltCallback = SDADC_DMAInjectedConvCplt;
    hsdadc->hdma->XferErrorCallback = SDADC_DMAError;
    if(hsdadc->hdma->Init.Mode == DMA_CIRCULAR)
    {
      hsdadc->hdma->XferHalfCpltCallback = SDADC_DMAInjectedHalfConvCplt;
    }
    /* Set JDMAEN bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 |= SDADC_CR1_JDMAEN;

    /* Start DMA in interrupt mode */
    if(hsdadc->InjectedMultimode == SDADC_MULTIMODE_SDADC1_SDADC2)
    {
      status = HAL_DMA_Start_IT(hsdadc->hdma, (uint32_t)&hsdadc->Instance->JDATA12R, \
                                (uint32_t) pData, Length);
    }
    else
    {
      status = HAL_DMA_Start_IT(hsdadc->hdma, (uint32_t)&hsdadc->Instance->JDATA13R, \
                                (uint32_t) pData, Length);
    }
    if(status != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_ERROR;
    }
    else
    {
      /* Start injected conversion */
      status = SDADC_InjConvStart(hsdadc);
    }
  }
  else
  {
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to stop multimode injected conversions in DMA mode.
  * @note   This function should be called only if injected conversion is ongoing.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SDADC_InjectedMultiModeStop_DMA(SDADC_HandleTypeDef* hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check parameters */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));

  /* Check instance is SDADC1 */
  if(hsdadc->Instance != SDADC1)
  {
    status = HAL_ERROR;
  }
  /* Check SDADC state */
  else if((hsdadc->State != HAL_SDADC_STATE_INJ) && \
          (hsdadc->State != HAL_SDADC_STATE_REG_INJ))
  {
    /* Return error status */
    status = HAL_ERROR;
  }
  else
  {
    /* Clear JDMAEN bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 &= ~(SDADC_CR1_JDMAEN);

    /* Stop current DMA transfer */
    if(HAL_DMA_Abort(hsdadc->hdma) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_ERROR;
    }
    else
    {
      /* Stop injected conversion */
      status = SDADC_InjConvStop(hsdadc);
    }
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to get multimode injected conversion value.
  * @param  hsdadc : SDADC handle.
  * @retval Multimode injected conversion value
  */
uint32_t HAL_SDADC_InjectedMultiModeGetValue(SDADC_HandleTypeDef* hsdadc)
{
  uint32_t value = 0;
  
  /* Check parameters and check instance is SDADC1 */
  assert_param(IS_SDADC_ALL_INSTANCE(hsdadc->Instance));
  assert_param(hsdadc->Instance == SDADC1);

  /* read multimode injected value */
  value = (hsdadc->InjectedMultimode == SDADC_MULTIMODE_SDADC1_SDADC2) ? \
          hsdadc->Instance->JDATA12R : hsdadc->Instance->JDATA13R;

  /* Return multimode injected conversions value */
  return value;
}

/**
  * @brief  This function handles the SDADC interrupts.
  * @param  hsdadc : SDADC handle.
  * @retval None
  */
void HAL_SDADC_IRQHandler(SDADC_HandleTypeDef* hsdadc)
{
  /* Check if end of regular conversion */
  if(((hsdadc->Instance->ISR & SDADC_ISR_REOCF) == SDADC_ISR_REOCF) && \
          ((hsdadc->Instance->CR1 & SDADC_CR1_REOCIE) == SDADC_CR1_REOCIE))
  {
    /* Call regular conversion complete callback */
    HAL_SDADC_ConvCpltCallback(hsdadc);

    /* End of conversion if mode is not continuous and software trigger */
    if((hsdadc->RegularContMode == SDADC_CONTINUOUS_CONV_OFF) && \
       (hsdadc->RegularTrigger == SDADC_SOFTWARE_TRIGGER))
    {
      /* Clear REOCIE and ROVRIE bits in SDADC_CR1 register */
      hsdadc->Instance->CR1 &= ~(SDADC_CR1_REOCIE | SDADC_CR1_ROVRIE);

      /* Update SDADC state */
      hsdadc->State = (hsdadc->State == HAL_SDADC_STATE_REG) ? \
                      HAL_SDADC_STATE_READY : HAL_SDADC_STATE_INJ;
    }
  }
  /* Check if end of injected conversion */
  else if(((hsdadc->Instance->ISR & SDADC_ISR_JEOCF) == SDADC_ISR_JEOCF) && \
          ((hsdadc->Instance->CR1 & SDADC_CR1_JEOCIE) == SDADC_CR1_JEOCIE))
  {
    /* Call injected conversion complete callback */
    HAL_SDADC_InjectedConvCpltCallback(hsdadc);

    /* Update remaining injected conversions */
    hsdadc->InjConvRemaining--;
    if(hsdadc->InjConvRemaining ==0)
    {
      /* end of injected sequence, reset the value */
      hsdadc->InjConvRemaining = hsdadc->InjectedChannelsNbr;
    }
    /* End of conversion if mode is not continuous, software trigger */
    /* and end of injected sequence */
    if((hsdadc->InjectedContMode == SDADC_CONTINUOUS_CONV_OFF) && \
       (hsdadc->InjectedTrigger == SDADC_SOFTWARE_TRIGGER) && \
       (hsdadc->InjConvRemaining == hsdadc->InjectedChannelsNbr))
    {
      /* Clear JEOCIE and JOVRIE bits in SDADC_CR1 register */
      hsdadc->Instance->CR1 &= ~(SDADC_CR1_JEOCIE | SDADC_CR1_JOVRIE);

      /* Update SDADC state */
      hsdadc->State = (hsdadc->State == HAL_SDADC_STATE_INJ) ? \
                      HAL_SDADC_STATE_READY : HAL_SDADC_STATE_REG;
    }
  }
  /* Check if end of calibration */
  else if(((hsdadc->Instance->ISR & SDADC_ISR_EOCALF) == SDADC_ISR_EOCALF) && \
          ((hsdadc->Instance->CR1 & SDADC_CR1_EOCALIE) == SDADC_CR1_EOCALIE))
  {
    /* Clear EOCALIE bit in SDADC_CR1 register */
    hsdadc->Instance->CR1 &= ~(SDADC_CR1_EOCALIE);

    /* Set CLREOCALF bit in SDADC_CLRISR register */
    hsdadc->Instance->CLRISR |= SDADC_ISR_CLREOCALF;

    /* Call calibration callback */
    HAL_SDADC_CalibrationCpltCallback(hsdadc);

    /* Update SDADC state */
    hsdadc->State = HAL_SDADC_STATE_READY;
  }
  /* Check if overrun occurs during regular conversion */
  else if(((hsdadc->Instance->ISR & SDADC_ISR_ROVRF) == SDADC_ISR_ROVRF) && \
          ((hsdadc->Instance->CR1 & SDADC_CR1_ROVRIE) == SDADC_CR1_ROVRIE))
  {
    /* Set CLRROVRF bit in SDADC_CLRISR register */
    hsdadc->Instance->CLRISR |= SDADC_ISR_CLRROVRF;

    /* Update error code */
    hsdadc->ErrorCode = SDADC_ERROR_REGULAR_OVERRUN;

    /* Call error callback */
    HAL_SDADC_ErrorCallback(hsdadc);
  }
  /* Check if overrun occurs during injected conversion */
  else if(((hsdadc->Instance->ISR & SDADC_ISR_JOVRF) == SDADC_ISR_JOVRF) && \
          ((hsdadc->Instance->CR1 & SDADC_CR1_JOVRIE) == SDADC_CR1_JOVRIE))
  {
    /* Set CLRJOVRF bit in SDADC_CLRISR register */
    hsdadc->Instance->CLRISR |= SDADC_ISR_CLRJOVRF;

    /* Update error code */
    hsdadc->ErrorCode = SDADC_ERROR_INJECTED_OVERRUN;

    /* Call error callback */
    HAL_SDADC_ErrorCallback(hsdadc);
  }
  return;
}

/**
  * @brief  Calibration complete callback. 
  * @param  hsdadc : SDADC handle.
  * @retval None
  */
__weak void HAL_SDADC_CalibrationCpltCallback(SDADC_HandleTypeDef* hsdadc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SDADC_CalibrationCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Half regular conversion complete callback. 
  * @param  hsdadc : SDADC handle.
  * @retval None
  */
__weak void HAL_SDADC_ConvHalfCpltCallback(SDADC_HandleTypeDef* hsdadc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SDADC_ConvHalfCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Regular conversion complete callback. 
  * @note   In interrupt mode, user has to read conversion value in this function
            using HAL_SDADC_GetValue or HAL_SDADC_MultiModeGetValue.
  * @param  hsdadc : SDADC handle.
  * @retval None
  */
__weak void HAL_SDADC_ConvCpltCallback(SDADC_HandleTypeDef* hsdadc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SDADC_ConvCpltCallback could be implemented in the user file.
   */
}

/**
  * @brief  Half injected conversion complete callback. 
  * @param  hsdadc : SDADC handle.
  * @retval None
  */
__weak void HAL_SDADC_InjectedConvHalfCpltCallback(SDADC_HandleTypeDef* hsdadc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SDADC_InjectedConvHalfCpltCallback could be implemented in the user file.
   */
}

/**
  * @brief  Injected conversion complete callback. 
  * @note   In interrupt mode, user has to read conversion value in this function
            using HAL_SDADC_InjectedGetValue or HAL_SDADC_InjectedMultiModeGetValue.
  * @param  hsdadc : SDADC handle.
  * @retval None
  */
__weak void HAL_SDADC_InjectedConvCpltCallback(SDADC_HandleTypeDef* hsdadc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SDADC_InjectedConvCpltCallback could be implemented in the user file.
   */
}

/**
  * @brief  Error callback. 
  * @param  hsdadc : SDADC handle.
  * @retval None
  */
__weak void HAL_SDADC_ErrorCallback(SDADC_HandleTypeDef* hsdadc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SDADC_ErrorCallback could be implemented in the user file.
   */
}

/**
  * @brief  DMA half transfer complete callback for regular conversion. 
  * @param  hdma : DMA handle.
  * @retval None
  */
static void SDADC_DMARegularHalfConvCplt(DMA_HandleTypeDef *hdma)   
{
  /* Get SDADC handle */
  SDADC_HandleTypeDef* hsdadc = (SDADC_HandleTypeDef*) ((DMA_HandleTypeDef*)hdma)->Parent;

  /* Call regular half conversion complete callback */
  HAL_SDADC_ConvHalfCpltCallback(hsdadc);
}

/**
  * @brief  DMA transfer complete callback for regular conversion. 
  * @param  hdma : DMA handle.
  * @retval None
  */
static void SDADC_DMARegularConvCplt(DMA_HandleTypeDef *hdma)   
{
  /* Get SDADC handle */
  SDADC_HandleTypeDef* hsdadc = (SDADC_HandleTypeDef*) ((DMA_HandleTypeDef*)hdma)->Parent;

  /* Call regular conversion complete callback */
  HAL_SDADC_ConvCpltCallback(hsdadc);
}

/**
  * @brief  DMA half transfer complete callback for injected conversion. 
  * @param  hdma : DMA handle.
  * @retval None
  */
static void SDADC_DMAInjectedHalfConvCplt(DMA_HandleTypeDef *hdma)   
{
  /* Get SDADC handle */
  SDADC_HandleTypeDef* hsdadc = (SDADC_HandleTypeDef*) ((DMA_HandleTypeDef*)hdma)->Parent;

  /* Call injected half conversion complete callback */
  HAL_SDADC_InjectedConvHalfCpltCallback(hsdadc);
}

/**
  * @brief  DMA transfer complete callback for injected conversion. 
  * @param  hdma : DMA handle.
  * @retval None
  */
static void SDADC_DMAInjectedConvCplt(DMA_HandleTypeDef *hdma)   
{
  /* Get SDADC handle */
  SDADC_HandleTypeDef* hsdadc = (SDADC_HandleTypeDef*) ((DMA_HandleTypeDef*)hdma)->Parent;

  /* Call injected conversion complete callback */
  HAL_SDADC_InjectedConvCpltCallback(hsdadc);
}

/**
  * @brief  DMA error callback. 
  * @param  hdma : DMA handle.
  * @retval None
  */
static void SDADC_DMAError(DMA_HandleTypeDef *hdma)   
{
  /* Get SDADC handle */
  SDADC_HandleTypeDef* hsdadc = (SDADC_HandleTypeDef*) ((DMA_HandleTypeDef*)hdma)->Parent;

  /* Update error code */
  hsdadc->ErrorCode = SDADC_ERROR_DMA;

  /* Call error callback */
  HAL_SDADC_ErrorCallback(hsdadc);
}

/**
  * @}
  */

/** @defgroup SDADC_Exported_Functions_Group4 Peripheral State functions
 *  @brief   SDADC Peripheral State functions 
 *
@verbatim   
  ===============================================================================
             ##### ADC Peripheral State functions #####
  ===============================================================================  
    [..] This subsection provides functions allowing to
      (+) Get the SDADC state
      (+) Get the SDADC Error
         
@endverbatim
  * @{
  */
  
/**
  * @brief  This function allows to get the current SDADC state.
  * @param  hsdadc : SDADC handle.
  * @retval SDADC state.
  */
HAL_SDADC_StateTypeDef HAL_SDADC_GetState(SDADC_HandleTypeDef* hsdadc)
{
  return hsdadc->State;
}

/**
  * @brief  This function allows to get the current SDADC error code.
  * @param  hsdadc : SDADC handle.
  * @retval SDADC error code.
  */
uint32_t HAL_SDADC_GetError(SDADC_HandleTypeDef* hsdadc)
{
  return hsdadc->ErrorCode;
}
    
/**
  * @}
  */

/**
  * @brief  This function allows to enter in init mode for SDADC instance.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status.
  */
static HAL_StatusTypeDef SDADC_EnterInitMode(SDADC_HandleTypeDef* hsdadc)
{
  uint32_t tickstart = 0;
  
  /* Set INIT bit on SDADC_CR1 register */
  hsdadc->Instance->CR1 |= SDADC_CR1_INIT;

  /* Wait INITRDY bit on SDADC_ISR */
  tickstart = HAL_GetTick();
  while((hsdadc->Instance->ISR & SDADC_ISR_INITRDY) == (uint32_t)RESET)
  {
    if((HAL_GetTick()-tickstart) > SDADC_TIMEOUT)
    {       
      return HAL_TIMEOUT;
    } 
  }
  
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  This function allows to exit from init mode for SDADC instance.
  * @param  hsdadc : SDADC handle.
  * @retval None.
  */
static void SDADC_ExitInitMode(SDADC_HandleTypeDef* hsdadc)
{
  /* Reset INIT bit in SDADC_CR1 register */
  hsdadc->Instance->CR1 &= ~(SDADC_CR1_INIT);
}

/**
  * @brief  This function allows to get the number of injected channels.
  * @param  Channels : bitfield of injected channels.
  * @retval Number of injected channels.
  */
static uint32_t SDADC_GetInjChannelsNbr(uint32_t Channels)
{
  uint32_t nbChannels = 0;
  uint32_t tmp,i;
  
  /* Get the number of channels from bitfield */
  tmp = (uint32_t) (Channels & SDADC_LSB_MASK);
  for(i = 0 ; i < 9 ; i++)
  {
    if(tmp & 1)
    {
      nbChannels++;
    }
    tmp = (uint32_t) (tmp >> 1);
  }
  return nbChannels;
}

/**
  * @brief  This function allows to really start regular conversion.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status.
  */
static HAL_StatusTypeDef SDADC_RegConvStart(SDADC_HandleTypeDef* hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check regular trigger */
  if(hsdadc->RegularTrigger == SDADC_SOFTWARE_TRIGGER)
  {
    /* Set RSWSTART bit in SDADC_CR2 register */
    hsdadc->Instance->CR2 |= SDADC_CR2_RSWSTART;
  }
  else /* synchronuous trigger */
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_TIMEOUT;
    }
    else
    {
      /* Set RSYNC bit in SDADC_CR1 register */
      hsdadc->Instance->CR1 |= SDADC_CR1_RSYNC;

      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);
    }
  }
  /* Update SDADC state only if status is OK */
  if(status == HAL_OK)
  {
    hsdadc->State = (hsdadc->State == HAL_SDADC_STATE_READY) ? \
                    HAL_SDADC_STATE_REG : HAL_SDADC_STATE_REG_INJ;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to really stop regular conversion.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status.
  */
static HAL_StatusTypeDef SDADC_RegConvStop(SDADC_HandleTypeDef* hsdadc)
{
  uint32_t tickstart;

  /* Check continuous mode */
  if(hsdadc->RegularContMode == SDADC_CONTINUOUS_CONV_ON)
  {
    /* Clear REOCF by reading SDADC_RDATAR register */
    hsdadc->Instance->RDATAR;

    /* Clear RCONT bit in SDADC_CR2 register */
    hsdadc->Instance->CR2 &= ~(SDADC_CR2_RCONT);
  }
  /* Wait for the end of regular conversion */
  tickstart = HAL_GetTick();  
  while((hsdadc->Instance->ISR & SDADC_ISR_RCIP) != 0)
  {
    if((HAL_GetTick()-tickstart) > SDADC_TIMEOUT)
    {
      /* Set SDADC in error state and return timeout status */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      return HAL_TIMEOUT;
    }
  }
  /* Check if trigger is synchronuous */
  if(hsdadc->RegularTrigger == SDADC_SYNCHRONOUS_TRIGGER)
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state and return timeout status */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      return HAL_TIMEOUT;
    }
    else
    {
      /* Clear RSYNC bit in SDADC_CR1 register */
      hsdadc->Instance->CR1 &= ~(SDADC_CR1_RSYNC);

      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);
    }
  }
  /* Check if continuous mode */
  if(hsdadc->RegularContMode == SDADC_CONTINUOUS_CONV_ON)
  {
    /* Restore RCONT bit in SDADC_CR2 register */
    hsdadc->Instance->CR2 |= SDADC_CR2_RCONT;
  }
  /* Clear REOCF by reading SDADC_RDATAR register */
  hsdadc->Instance->RDATAR;

  /* Set CLRROVRF bit in SDADC_CLRISR register */
  hsdadc->Instance->CLRISR |= SDADC_ISR_CLRROVRF;

  /* Update SDADC state */
  hsdadc->State = (hsdadc->State == HAL_SDADC_STATE_REG) ? \
                  HAL_SDADC_STATE_READY : HAL_SDADC_STATE_INJ;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  This function allows to really start injected conversion.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status.
  */
static HAL_StatusTypeDef SDADC_InjConvStart(SDADC_HandleTypeDef* hsdadc)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Initialize number of injected conversions remaining */
  hsdadc->InjConvRemaining = hsdadc->InjectedChannelsNbr;

  /* Check injected trigger */
  if(hsdadc->InjectedTrigger == SDADC_SOFTWARE_TRIGGER)
  {
    /* Set JSWSTART bit in SDADC_CR2 register */
    hsdadc->Instance->CR2 |= SDADC_CR2_JSWSTART;
  }
  else /* external or synchronuous trigger */
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      status = HAL_TIMEOUT;
    }
    else
    {
      if(hsdadc->InjectedTrigger == SDADC_SYNCHRONOUS_TRIGGER)
      {
        /* Set JSYNC bit in SDADC_CR1 register */
        hsdadc->Instance->CR1 |= SDADC_CR1_JSYNC;
      }
      else /* external trigger */
      {
        /* Set JEXTEN[1:0] bits in SDADC_CR2 register */
        hsdadc->Instance->CR2 |= hsdadc->ExtTriggerEdge;
      }
      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);
    }
  }
  /* Update SDADC state only if status is OK */
  if(status == HAL_OK)
  {
    hsdadc->State = (hsdadc->State == HAL_SDADC_STATE_READY) ? \
                    HAL_SDADC_STATE_INJ : HAL_SDADC_STATE_REG_INJ;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  This function allows to really stop injected conversion.
  * @param  hsdadc : SDADC handle.
  * @retval HAL status.
  */
static HAL_StatusTypeDef SDADC_InjConvStop(SDADC_HandleTypeDef* hsdadc)
{
  uint32_t tickstart;

  /* Check continuous mode */
  if(hsdadc->InjectedContMode == SDADC_CONTINUOUS_CONV_ON)
  {
    /* Clear JEOCF by reading SDADC_JDATAR register */
    hsdadc->Instance->JDATAR;

    /* Clear JCONT bit in SDADC_CR2 register */
    hsdadc->Instance->CR2 &= ~(SDADC_CR2_JCONT);
  }
  /* Wait for the end of injected conversion */
  tickstart = HAL_GetTick();  
  while((hsdadc->Instance->ISR & SDADC_ISR_JCIP) != 0)
  {
    if((HAL_GetTick()-tickstart) > SDADC_TIMEOUT)
    {
      /* Set SDADC in error state and return timeout status */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      return HAL_TIMEOUT;
    }
  }
  /* Check if trigger is not software */
  if(hsdadc->InjectedTrigger != SDADC_SOFTWARE_TRIGGER)
  {
    /* Enter init mode */
    if(SDADC_EnterInitMode(hsdadc) != HAL_OK)
    {
      /* Set SDADC in error state and return timeout status */
      hsdadc->State = HAL_SDADC_STATE_ERROR;
      return HAL_TIMEOUT;
    }
    else
    {
      /* Check if trigger is synchronuous */
      if(hsdadc->InjectedTrigger == SDADC_SYNCHRONOUS_TRIGGER)
      {
        /* Clear JSYNC bit in SDADC_CR1 register */
        hsdadc->Instance->CR1 &= ~(SDADC_CR1_JSYNC);
      }
      else /* external trigger */
      {
        /* Clear JEXTEN[1:0] bits in SDADC_CR2 register */
        hsdadc->Instance->CR2 &= ~(SDADC_CR2_JEXTEN);
      }
      /* Exit init mode */
      SDADC_ExitInitMode(hsdadc);
    }
  }
  /* Check if continuous mode */
  if(hsdadc->InjectedContMode == SDADC_CONTINUOUS_CONV_ON)
  {
    /* Restore JCONT bit in SDADC_CR2 register */
    hsdadc->Instance->CR2 |= SDADC_CR2_JCONT;
  }
  /* Clear JEOCF by reading SDADC_JDATAR register */
  hsdadc->Instance->JDATAR;

  /* Set CLRJOVRF bit in SDADC_CLRISR register */
  hsdadc->Instance->CLRISR |= SDADC_ISR_CLRJOVRF;

  /* Update SDADC state */
  hsdadc->State = (hsdadc->State == HAL_SDADC_STATE_INJ) ? \
                  HAL_SDADC_STATE_READY : HAL_SDADC_STATE_REG;

  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */ 

#endif /* defined(STM32F373xC) || defined(STM32F378xx) */
#endif /* HAL_SDADC_MODULE_ENABLED */
/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
