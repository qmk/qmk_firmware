/**
  ******************************************************************************
  * @file    stm32f3xx_hal_adc.c
  * @author  MCD Application conversion
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of conversions of regular and injected
  *             groups, using 3 possible modes: polling, interruption or DMA.
  *           + Control functions
  *             ++ Analog Watchdog configuration
  *             ++ Channels configuration on regular group
  *           + State functions
  *             ++ ADC state machine management
  *             ++ Interrupts and flags management
  *         
  @verbatim
  ==============================================================================
                    ##### ADC specific features #####
  ==============================================================================
  [..] 
  (#) 12-bit, 10-bit, 8-bit or 6-bit configurable resolution (available only on 
      STM32F30xxC devices).

  (#) Interrupt generation at the end of regular conversion, end of injected
      conversion, and in case of analog watchdog or overrun events.
  
  (#) Single and continuous conversion modes.
  
  (#) Scan mode for automatic conversion of channel 0 to channel 'n'.
  
  (#) Data alignment with in-built data coherency.
  
  (#) Channel-wise programmable sampling time.
  
  (#) ADC conversion Regular or Injected groups.

  (#) External trigger (timer or EXTI) with configurable polarity for both  
      regular and injected groups.

  (#) DMA request generation for transfer of conversions data of regular group.

  (#) Multimode Dual mode (available on devices with 2 ADCs or more).
  
  (#) Configurable DMA data storage in Multimode Dual mode (available on devices
      with 2 DCs or more).
  
  (#) Configurable delay between conversions in Dual interleaved mode (available 
      on devices with 2 DCs or more).
  
  (#) ADC calibration

  (#) ADC channels selectable single/differential input (available only on
      STM32F30xxC devices)

  (#) ADC Injected sequencer&channels configuration context queue (available 
      only on STM32F30xxC devices)

  (#) ADC offset on injected and regular groups (offset on regular group 
      available only on STM32F30xxC devices)

  (#) ADC supply requirements: 2.4 V to 3.6 V at full speed and down to 1.8 V at 
      slower speed.
  
  (#) ADC input range: from Vref– (connected to Vssa) to Vref+ (connected to 
      Vdda or to an external voltage reference).


                     ##### How to use this driver #####
  ==============================================================================
    [..]

    (#) Enable the ADC interface 
        As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured  
        at RCC top level: clock source and clock prescaler.

        For STM32F30x/STM32F33x devices:
        Two possible clock sources: synchronous clock derived from AHB clock 
        or asynchronous clock derived from ADC dedicated PLL 72MHz.

        For example, in case of device with a single ADC:
            __ADC1_CLK_ENABLE()                            (mandatory)
            __HAL_RCC_ADC1_CONFIG(RCC_ADC1PLLCLK_DIV1);    (optional)  
          
        For example, in case of device with several ADCs:
          if((hadc->Instance == ADC1) || (hadc->Instance == ADC2))             
          {                                                                    
            __ADC12_CLK_ENABLE()                            (mandatory)        
            __HAL_RCC_ADC12_CONFIG(RCC_ADC12PLLCLK_DIV1);   (optional)         
          }                                                                    
          else                                                                 
          {                                                                    
            __ADC34_CLK_ENABLE()                            (mandatory)        
            __HAL_RCC_ADC34_CONFIG(RCC_ADC34PLLCLK_DIV1);   (optional)         
          }                                                                    

        For STM32F37x devices:
        Only one clock source: APB2 clock.
        Example:
          __HAL_RCC_ADC1_CONFIG(RCC_ADC1PCLK2_DIV2);

    (#) ADC pins configuration
         (++) Enable the clock for the ADC GPIOs using the following function:
             __GPIOx_CLK_ENABLE();   
         (++) Configure these ADC pins in analog mode using HAL_GPIO_Init();  
  
     (#) Configure the ADC parameters (conversion resolution, data alignment,  
         continuous mode, ...) using the HAL_ADC_Init() function.

     (#) Activate the ADC peripheral using one of the start functions: 
         HAL_ADC_Start(), HAL_ADC_Start_IT(), HAL_ADC_Start_DMA()
         HAL_ADCEx_InjectedStart(), HAL_ADCEx_InjectedStart_IT() or 
         HAL_ADC_MultiModeStart_DMA().
  
     *** Channels to regular group configuration ***
     ============================================
     [..]    
       (+) To configure the ADC regular group features, use 
           HAL_ADC_Init() and HAL_ADC_ConfigChannel() functions.
       (+) To activate the continuous mode, use the HAL_ADC_Init() function.   
       (+) To read the ADC converted values, use the HAL_ADC_GetValue() function.
            
     *** Multimode ADCs configuration ***
     ======================================================
     [..]
       (+) Multimode feature is available on devices with 2 ADCs or more.
       (+) Refer to "Channels to regular group" description to  
           configure the ADC1 and ADC2 regular groups.        
       (+) Select the Multi mode ADC  features (dual mode
           simultaneous, interleaved, ...) and configure the DMA mode using 
           HAL_ADCEx_MultiModeConfigChannel() functions. 
       (+) Read the ADCs converted values using the HAL_ADCEx_MultiModeGetValue()
           function.
  
     *** DMA for regular configuration ***
     ============================================================= 
     [..]
       (+) To enable the DMA mode for regular group, use the  
           HAL_ADC_Start_DMA() function.
       (+) To enable the generation of DMA requests continuously at the end of 
           the last DMA transfer, use the HAL_ADC_Init() function.
  
     *** Channels to injected group configuration ***
     =============================================    
     [..]
       (+) To configure the ADC Injected channels group features, use 
           HAL_ADCEx_InjectedConfigChannel() functions.
       (+) To activate the continuous mode, use the HAL_ADC_Init() function.
       (+) To read the ADC converted values, use the HAL_ADCEx_InjectedGetValue() 
           function.
  
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

/** @defgroup ADC ADC HAL module driver
  * @brief ADC HAL module driver
  * @{
  */ 

#ifdef HAL_ADC_MODULE_ENABLED
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup ADC_Exported_Functions ADC Exported Functions
  * @{
  */ 

/** @defgroup ADC_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the ADC. 
      (+) De-initialize the ADC. 
         
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the ADC peripheral and regular group according to  
  *         parameters specified in structure "ADC_InitTypeDef".
  * @note   As prerequisite, ADC clock must be configured at RCC top level
  *         depending on both possible clock sources: PLL clock or AHB clock.
  *         See commented example code below that can be copied and uncommented 
  *         into HAL_ADC_MspInit().
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the ADC MSP (HAL_ADC_MspInit()) only when
  *         coming from ADC state reset. Following calls to this function can
  *         be used to reconfigure some parameters of ADC_InitTypeDef  
  *         structure on the fly, without modifying MSP configuration. If ADC  
  *         MSP has to be modified again, HAL_ADC_DeInit() must be called
  *         before HAL_ADC_Init().
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_InitTypeDef".
  * @note   This function configures the ADC within 2 scopes: scope of entire 
  *         ADC and scope of regular group. For parameters details, see comments 
  *         of structure "ADC_InitTypeDef".
  * @note   For devices with several ADCs: parameters related to common ADC 
  *         registers (ADC clock mode) are set only if all ADCs sharing the
  *         same common group are disabled.
  *         If this is not the case, these common parameters setting are  
  *         bypassed without error reporting: it can be the intended behaviour in
  *         case of update of a parameter of ADC_InitTypeDef on the fly,
  *         without  disabling the other ADCs sharing the same common group.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Deinitialize the ADC peripheral registers to their default reset
  *         values, with deinitialization of the ADC MSP.
  * @note   For devices with several ADCs: reset of ADC common registers is done 
  *         only if all ADCs sharing the same common group are disabled.
  *         If this is not the case, reset of these common parameters reset is  
  *         bypassed without error reporting: it can be the intended behaviour in
  *         case of reset of a single ADC while the other ADCs sharing the same 
  *         common group is still running.
  * @note   For devices with several ADCs: Global reset of all ADCs sharing a
  *         common group is possible.
  *         As this function is intended to reset a single ADC, to not impact 
  *         other ADCs, instructions for global reset of multiple ADCs have been
  *         let commented below.
  *         If needed, the example code can be copied and uncommented into
  *         function HAL_ADC_MspDeInit().
  * @param  hadc: ADC handle
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}
    
/**
  * @brief  Initializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MspInit must be implemented in the user file.
   */ 
}

/**
  * @brief  DeInitializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_MspDeInit must be implemented in the user file.
   */ 
}

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group2 Input and Output operation functions
 *  @brief    IO operation functions 
 *
@verbatim   
 ===============================================================================
             ##### IO operation functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Start conversion of regular group.
      (+) Stop conversion of regular group.
      (+) Poll for conversion complete on regular group.
      (+) Poll for conversion event.
      (+) Get result of regular channel conversion.
      (+) Start conversion of regular group and enable interruptions.
      (+) Stop conversion of regular group and disable interruptions.
      (+) Handle ADC interrupt request
      (+) Start conversion of regular group and enable DMA transfer.
      (+) Stop conversion of regular group and disable ADC DMA transfer.
               
@endverbatim
  * @{
  */
/**
  * @brief  Enables ADC, starts conversion of regular group.
  *         Interruptions enabled in this function: None.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function must be called for ADC slave first, then ADC master. 
  *         For ADC slave, ADC is enabled only (conversion is not started).  
  *         For ADC master, ADC is enabled and multimode conversion is started.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function must be called for ADC master first, then ADC slave.
  *         For ADC master, converson is stopped and ADC is disabled. 
  *         For ADC slave, ADC is disabled only (conversion stop of ADC master
  *         has already stopped conversion of ADC slave).
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
__weak HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Wait for regular group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Poll for conversion event.
  * @param  hadc: ADC handle
  * @param  EventType: the ADC event type.
  *          This parameter can be one of the following values:
  *            @arg AWD_EVENT: ADC Analog watchdog 1 event (main analog watchdog, present on all STM32 devices)
  *            @arg AWD2_EVENT: ADC Analog watchdog 2 event (additional analog watchdog, present only on STM32F3 devices)
  *            @arg AWD3_EVENT: ADC Analog watchdog 3 event (additional analog watchdog, present only on STM32F3 devices)
  *            @arg OVR_EVENT: ADC Overrun event
  *            @arg JQOVF_EVENT: ADC Injected context queue overflow event
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Enables ADC, starts conversion of regular group with interruption.
  *         Interruptions enabled in this function: EOC (end of conversion),
  *         overrun (if available).
  *         Each of these interruptions has its dedicated callback function.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function must be called for ADC slave first, then ADC master. 
  *         For ADC slave, ADC is enabled only (conversion is not started).  
  *         For ADC master, ADC is enabled and multimode conversion is started.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable interruption of 
  *         end-of-conversion, disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function must be called for ADC master first, then ADC slave.
  *         For ADC master, conversion is stopped and ADC is disabled. 
  *         For ADC slave, ADC is disabled only (conversion stop of ADC master
  *         has already stopped conversion of ADC slave).
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
__weak HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Enables ADC, starts conversion of regular group and transfers result
  *         through DMA.
  *         Interruptions enabled in this function:
  *         overrun (if available), DMA half transfer, DMA transfer complete. 
  *         Each of these interruptions has its dedicated callback function.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function is for single-ADC mode only. For multimode, use the 
  *         dedicated MultimodeStart function.
  * @param  hadc: ADC handle
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @retval None
  */
__weak HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function is for single-ADC mode only. For multimode, use the 
  *         dedicated MultimodeStop function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
__weak HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Get ADC regular group conversion result.
  * @param  hadc: ADC handle
  * @retval Converted value
  */
__weak uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return ADC converted value */ 
  return hadc->Instance->DR;
}

/**
  * @brief  Handles ADC interrupt request.  
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief  Conversion DMA half-transfer callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvHalfCpltCallback must be implemented in the user file.
  */
}

/**
  * @brief  Analog watchdog callback in non blocking mode. 
  * @note:  In case of several analog watchdog enabled, if needed to know
            which one triggered and on which ADCx, check Analog Watchdog flag
            ADC_FLAG_AWD1/2/3 into HAL_ADC_LevelOutOfWindowCallback() function.
            For example:"if (__HAL_ADC_GET_FLAG(hadc1, ADC_FLAG_AWD1) != RESET)"
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_LevelOoutOfWindowCallback must be implemented in the user file.
  */
}

/**
  * @brief  ADC error callback in non blocking mode
  *        (ADC conversion with interruption or transfer by DMA)
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ErrorCallback must be implemented in the user file.
  */
}

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions 
 *
@verbatim   
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels on regular group
      (+) Configure the analog watchdog
      
@endverbatim
  * @{
  */

/**
  * @brief  Configures the the selected channel to be linked to the regular
  *         group.
  * @note   In case of usage of internal measurement channels:
  *         Vbat/VrefInt/TempSensor.
  *         The recommended sampling time is at least:
  *          - For devices STM32F37x: 17.1us for temperature sensor
  *          - For the other STM32F3 devices: 2.2us for each of channels 
  *            Vbat/VrefInt/TempSensor.
  *         These internal paths can be be disabled using function 
  *         HAL_ADC_DeInit().
  * @note   Possibility to update parameters on the fly:
  *         This function initializes channel into regular group, following  
  *         calls to this function can be used to reconfigure some parameters 
  *         of structure "ADC_ChannelConfTypeDef" on the fly, without reseting 
  *         the ADC.
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_ChannelConfTypeDef".
  * @param  hadc: ADC handle
  * @param  sConfig: Structure of ADC channel for regular group.
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Configures the analog watchdog.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes the selected analog watchdog, following  
  *         calls to this function can be used to reconfigure some parameters 
  *         of structure "ADC_AnalogWDGConfTypeDef" on the fly, without reseting 
  *         the ADC.
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_AnalogWDGConfTypeDef".
  * @param  hadc: ADC handle
  * @param  AnalogWDGConfig: Structure of ADC analog watchdog configuration
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{
  /* Note : This function is defined into this file for library reference. */
  /*        Function content is located into file stm32f3xx_hal_adc_ex.c   */
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group4 Peripheral State functions
 *  @brief   ADC Peripheral State functions 
 *
@verbatim   
 ===============================================================================
            ##### Peripheral state and errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions to get in run-time the status of the  
    peripheral.
      (+) Check the ADC state
      (+) Check the ADC error code
         
@endverbatim
  * @{
  */
  
/**
  * @brief  return the ADC state
  * @param  hadc: ADC handle
  * @retval HAL state
  */
HAL_ADC_StateTypeDef HAL_ADC_GetState(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Return ADC state */
  return hadc->State;
}

/**
  * @brief  Return the ADC error code
  * @param  hadc: ADC handle
  * @retval ADC Error Code
  */
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc)
{
  return hadc->ErrorCode;
}

/**
  * @}
  */
       
/**
  * @}
  */

#endif /* HAL_ADC_MODULE_ENABLED */
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
