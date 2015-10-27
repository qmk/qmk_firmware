/**
  ******************************************************************************
  * @file    stm32f3xx_hal_adc_ex.c
  * @author  MCD Application Team
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
  *             ++ Multimode feature (available on devices with 2 ADCs or more)
  *             ++ Calibration (ADC automatic self-calibration)
  *           + Control functions
  *             ++ Configure channels on regular group
  *             ++ Configure channels on injected group
  *             ++ Configure the analog watchdog
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
         - synchronous clock is configured using macro __ADCx_CLK_ENABLE()
         - asynchronous clock is configured using macro __HAL_RCC_ADCx_CONFIG()
           or function HAL_RCCEx_PeriphCLKConfig().
        
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

/** @defgroup ADCEx ADC Extended HAL module driver
  * @brief ADC Extended HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ADCEx_Private_Constants ADC Extended Private Constants
  * @{
  */
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
  /* Fixed timeout values for ADC calibration, enable settling time, disable  */
  /* settling time.                                                           */
  /* Values defined to be higher than worst cases: low clock frequency,       */
  /* maximum prescalers.                                                      */
  /* Ex of profile low frequency : Clock source at 0.5 MHz, ADC clock         */
  /* prescaler 256 (devices STM32F30xx), sampling time 7.5 ADC clock cycles,  */
  /* resolution 12 bits.                                                      */
  /* Unit: ms                                                                 */
  #define ADC_CALIBRATION_TIMEOUT         ((uint32_t) 10)
  #define ADC_ENABLE_TIMEOUT              ((uint32_t)  2)
  #define ADC_DISABLE_TIMEOUT             ((uint32_t)  2)
  #define ADC_STOP_CONVERSION_TIMEOUT     ((uint32_t) 11)

  /* Timeout to wait for current conversion on going to be completed.         */
  /* Timeout fixed to worst case, for 1 channel.                              */
  /*   - maximum sampling time (601.5 adc_clk)                                */
  /*   - ADC resolution (Tsar 12 bits= 12.5 adc_clk)                          */
  /*   - ADC clock (from PLL with prescaler 256 (devices STM32F30xx))         */
  /* Unit: cycles of CPU clock.                                               */
  #define ADC_CONVERSION_TIME_MAX_CPU_CYCLES ((uint32_t) 156928)
    
  /* Delay for ADC stabilization time (ADC voltage regulator start-up time)   */
  /* Maximum delay is 10us (refer to device datasheet, param. TADCVREG_STUP). */
  /* Delay in CPU cycles, fixed to worst case: maximum CPU frequency 72MHz to */
  /* have the minimum number of CPU cycles to fulfill this delay.             */
  #define ADC_STAB_DELAY_CPU_CYCLES       ((uint32_t)720)
    
  /* Delay for temperature sensor stabilization time.                         */
  /* Maximum delay is 10us (refer device datasheet, parameter tSTART).        */
  /* Delay in CPU cycles, fixed to worst case: maximum CPU frequency 72MHz to */
  /* have the minimum number of CPU cycles to fulfill this delay.             */
  #define ADC_TEMPSENSOR_DELAY_CPU_CYCLES    ((uint32_t)720)
    
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
  /* Fixed timeout values for ADC calibration, enable settling time.          */
  /* Values defined to be higher than worst cases: low clocks freq,           */
  /* maximum prescalers.                                                      */
  /* ex: On STM32F303C, clock source PLL=1MHz, presc. RCC_ADC12PLLCLK_DIV256  */
  /* Unit: ms                                                                 */
  #define ADC_CALIBRATION_TIMEOUT         ((uint32_t) 10)
  #define ADC_ENABLE_TIMEOUT              ((uint32_t) 10)

  /* Delay for ADC stabilization time.                                        */
  /* Maximum delay is 1us (refer to device datasheet, parameter tSTAB).       */
  /* Delay in CPU cycles, fixed to worst case: maximum CPU frequency 48MHz to */
  /* have the minimum number of CPU cycles to fulfill this delay.             */
  #define ADC_STAB_DELAY_CPU_CYCLES       ((uint32_t)72)

  /* Maximum number of CPU cycles corresponding to 1 ADC cycle                */
  /* Value fixed to worst case: clock prescalers slowing down ADC clock to    */
  /* minimum frequency                                                        */
  /*   - AHB prescaler: 16                                                    */
  /*   - ADC prescaler: 8                                                     */
  /* Unit: cycles of CPU clock.                                               */
  #define ADC_CYCLE_WORST_CASE_CPU_CYCLES ((uint32_t) 128)

  /* ADC conversion cycles (unit: ADC clock cycles)                           */
  /* (selected sampling time + conversion time of 12.5 ADC clock cycles, with */
  /* resolution 12 bits)                                                      */
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_1CYCLE5    ((uint32_t) 14)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_7CYCLES5   ((uint32_t) 20)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_13CYCLES5  ((uint32_t) 26)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_28CYCLES5  ((uint32_t) 41)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_41CYCLES5  ((uint32_t) 54)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_55CYCLES5  ((uint32_t) 68)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_71CYCLES5  ((uint32_t) 84)
  #define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_239CYCLES5 ((uint32_t)252)
#endif /* STM32F373xC || STM32F378xx */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
static HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc);
static HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc, uint32_t ConversionGroup);
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
static HAL_StatusTypeDef ADC_ConversionStop_Disable(ADC_HandleTypeDef* hadc);
#endif /* STM32F373xC || STM32F378xx */

static void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_DMAError(DMA_HandleTypeDef *hdma);

/* Exported functions --------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Functions ADC Extended Exported Functions
  * @{
  */ 

/** @defgroup ADCEx_Exported_Functions_Group1 Extended Initialization and de-initialization functions
  * @brief    Extended Initialization and Configuration functions
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

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Initializes the ADC peripheral and regular group according to  
  *         parameters specified in structure "ADC_InitTypeDef".
  * @note   As prerequisite, ADC clock must be configured at RCC top level
  *         depending on both possible clock sources: AHB clock or PLL clock.
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
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  ADC_Common_TypeDef *tmpADC_Common;
  ADC_HandleTypeDef tmphadcSharingSameCommonRegister;
  uint32_t tmpCFGR = 0;
  uint32_t WaitLoopIndex = 0;
  
  /* Check ADC handle */
  if(hadc == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CLOCKPRESCALER(hadc->Init.ClockPrescaler));
  assert_param(IS_ADC_RESOLUTION(hadc->Init.Resolution));
  assert_param(IS_ADC_DATA_ALIGN(hadc->Init.DataAlign)); 
  assert_param(IS_ADC_SCAN_MODE(hadc->Init.ScanConvMode));
  assert_param(IS_ADC_REGULAR_NB_CONV(hadc->Init.NbrOfConversion));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DiscontinuousConvMode));
  assert_param(IS_ADC_REGULAR_DISCONT_NUMBER(hadc->Init.NbrOfDiscConversion));
  assert_param(IS_ADC_EXTTRIG_EDGE(hadc->Init.ExternalTrigConvEdge));
  assert_param(IS_ADC_EXTTRIG(hadc->Init.ExternalTrigConv));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DMAContinuousRequests));
  assert_param(IS_ADC_EOC_SELECTION(hadc->Init.EOCSelection));
  assert_param(IS_ADC_OVERRUN(hadc->Init.Overrun));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.LowPowerAutoWait));
   
  
  /* As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured    */
  /* at RCC top level depending on both possible clock sources:               */
  /* PLL clock or AHB clock.                                                  */
  /* For example:                                                             */
  /* if((hadc->Instance == ADC1) || (hadc->Instance == ADC2))                 */
  /* {                                                                        */
  /*   __ADC12_CLK_ENABLE();                                                  */
  /*   __HAL_RCC_ADC12_CONFIG(RCC_ADC12PLLCLK_DIV1);                          */
  /* }                                                                        */
  /* else                                                                     */
  /* {                                                                        */
  /*   __ADC34_CLK_ENABLE();                                                  */
  /*   __HAL_RCC_ADC34_CONFIG(RCC_ADC34PLLCLK_DIV1);                          */
  /* }                                                                        */
  
  
  /* Actions performed only if ADC is coming from state reset:                */
  /* - Initialization of ADC MSP                                              */
  /* - ADC voltage regulator enable                                           */
  if (hadc->State == HAL_ADC_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_ADC_MspInit(hadc);
    
    /* Enable voltage regulator (if disabled at this step) */
    if (HAL_IS_BIT_CLR(hadc->Instance->CR, ADC_CR_ADVREGEN_0))
    {
      /* Note: The software must wait for the startup time of the ADC voltage */
      /*       regulator before launching a calibration or enabling the ADC.  */
      /*       This temporization must be implemented by software and is      */ 
      /*       equal to 10 us in the worst case process/temperature/power     */
      /*       supply.                                                        */
      
      /* Disable the ADC (if not already disabled) */
      tmpHALStatus = ADC_Disable(hadc);
      
      /* Check if ADC is effectively disabled */
      if (tmpHALStatus != HAL_ERROR)
      {
        /* Initialize the ADC state */
        hadc->State = HAL_ADC_STATE_BUSY;
        
        /* Set the intermediate state before moving the ADC voltage regulator */
        /* to state enable.                                                   */
        hadc->Instance->CR &= ~(ADC_CR_ADVREGEN);
        /* Set ADVREGEN bits to 0x01 */
        hadc->Instance->CR |= ADC_CR_ADVREGEN_0;
        
        /* Delay for ADC stabilization time.                                  */
        /* Delay fixed to worst case: maximum CPU frequency                   */
        while(WaitLoopIndex < ADC_STAB_DELAY_CPU_CYCLES)
        {
          WaitLoopIndex++;
        }
      }
    }
  }

  /* Verification that ADC voltage regulator is correctly enabled, whatever   */
  /* ADC coming from state reset or not (if any potential problem of          */
  /* clocking, voltage regulator would not be enabled).                       */
  if ((hadc->Instance->CR & ADC_CR_ADVREGEN) != ADC_CR_ADVREGEN_0)
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    /* Set ADC error code to ADC IP internal error */
    hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
    
    tmpHALStatus = HAL_ERROR;
  }

  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  /* and if there is no conversion on going on regular group (ADC can be      */ 
  /* enabled anyway, in case of call of this function to update a parameter   */
  /* on the fly).                                                             */
  if ((hadc->State != HAL_ADC_STATE_ERROR)                    &&
      (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)  )
  {
    /* Initialize the ADC state */
    hadc->State = HAL_ADC_STATE_BUSY;
    
    /* Configuration of common ADC parameters                                 */
    
    /* Pointer to the common control register to which is belonging hadc      */
    /* (Depending on STM32F3 product, there may be up to 4 ADC and 2 common   */
    /* control registers)                                                     */
    tmpADC_Common = __HAL_ADC_COMMON_REGISTER(hadc);
    
    /* Set handle of the other ADC sharing the same common register           */
    __HAL_ADC_COMMON_ADC_OTHER(hadc, &tmphadcSharingSameCommonRegister);
    

    /* Parameters update conditioned to ADC state:                            */
    /* Parameters that can be updated only when ADC is disabled:              */
    /*  - Multimode clock configuration                                       */
    if ((__HAL_ADC_IS_ENABLED(hadc) == RESET)                                  &&
        ( (tmphadcSharingSameCommonRegister.Instance == HAL_NULL) ||
          (__HAL_ADC_IS_ENABLED(&tmphadcSharingSameCommonRegister) == RESET) ))
    {
      /* Reset configuration of ADC common register CCR:                      */
      /*   - ADC clock mode: CKMODE                                           */
      /* Some parameters of this register are not reset, since they are set   */
      /* by other functions and must be kept in case of usage of this         */
      /* function on the fly (update of a parameter of ADC_InitTypeDef        */
      /* without needing to reconfigure all other ADC groups/channels         */
      /* parameters):                                                         */
      /*   - multimode related parameters: MDMA, DMACFG, DELAY, MULTI (set    */
      /*     into HAL_ADCEx_MultiModeConfigChannel() )                        */
      /*   - internal measurement paths: Vbat, temperature sensor, Vref       */
      /*     (set into HAL_ADC_ConfigChannel() or                             */
      /*     HAL_ADCEx_InjectedConfigChannel() )                              */
      tmpADC_Common->CCR &= ~(ADC_CCR_CKMODE);
      
      /* Configuration of common ADC clock: clock source PLL or AHB with      */
      /* selectable prescaler                                                 */
      tmpADC_Common->CCR |= hadc->Init.ClockPrescaler;
    }
      
    /* Configuration of ADC:                                                  */
    /*  - resolution                                                          */
    /*  - data alignment                                                      */
    /*  - external trigger to start conversion                                */
    /*  - external trigger polarity                                           */
    /*  - continuous conversion mode                                          */
    /*  - overrun                                                             */
    /*  - discontinuous mode                                                  */
    hadc->Instance->CFGR &= ~( ADC_CFGR_DISCNUM |
                               ADC_CFGR_DISCEN  |
                               ADC_CFGR_CONT    |
                               ADC_CFGR_OVRMOD  |
                               ADC_CFGR_EXTSEL  |
                               ADC_CFGR_EXTEN   |
                               ADC_CFGR_ALIGN   |
                               ADC_CFGR_RES      );

    tmpCFGR |= ( __HAL_ADC_CFGR_CONTINUOUS(hadc->Init.ContinuousConvMode) |
                 __HAL_ADC_CFGR_OVERRUN(hadc->Init.Overrun)               |
                 hadc->Init.DataAlign                                     |
                 hadc->Init.Resolution                                     );
    
    /* Enable discontinuous mode only if continuous mode is disabled */
    if ((hadc->Init.DiscontinuousConvMode == ENABLE) &&
        (hadc->Init.ContinuousConvMode == DISABLE)     )
    {
      /* Enable the selected ADC regular discontinuous mode */
      /* Set the number of channels to be converted in discontinuous mode */   
      tmpCFGR |= ( ADC_CFGR_DISCEN |
                   __HAL_ADC_CFGR_DISCONTINUOUS_NUM(hadc->Init.NbrOfDiscConversion) );
    }
      
    /* Enable external trigger if trigger selection is different of software  */
    /* start.                                                                 */
    /* Note: This configuration keeps the hardware feature of parameter       */
    /*       ExternalTrigConvEdge "trigger edge none" equivalent to           */
    /*       software start.                                                  */
    if (hadc->Init.ExternalTrigConv != ADC_SOFTWARE_START)
    {
      tmpCFGR |= ( __HAL_ADC_CFGR_EXTSEL(hadc, hadc->Init.ExternalTrigConv) |
                   hadc->Init.ExternalTrigConvEdge                           );
    }

    /* Parameters update conditioned to ADC state:                            */
    /* Parameters that can be updated when ADC is disabled or enabled without */
    /* conversion on going on regular and injected groups:                    */
    /*  - DMA continuous request                                              */
    /*  - LowPowerAutoWait feature                                            */
    if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(hadc) == RESET)
    {
      hadc->Instance->CFGR &= ~( ADC_CFGR_AUTDLY |
                                 ADC_CFGR_DMACFG  );
      
      tmpCFGR |= ( __HAL_ADC_CFGR_AUTOWAIT(hadc->Init.LowPowerAutoWait)       |
                   __HAL_ADC_CFGR_DMACONTREQ(hadc->Init.DMAContinuousRequests) );
    }
    
    /* Update ADC configuration register with previous settings */
    hadc->Instance->CFGR |= tmpCFGR;
    
    
    /* Configuration of regular group sequencer:                              */
    /* - if scan mode is disabled, regular channels sequence length is set to */
    /*   0x00: 1 channel converted (channel on regular rank 1)                */
    /*   Parameter "NbrOfConversion" is discarded.                            */
    /*   Note: Scan mode is not present by hardware on this device, but       */
    /*   emulated by software for alignment over all STM32 devices.           */
    /* - if scan mode is enabled, regular channels sequence length is set to  */
    /*   parameter "NbrOfConversion"                                          */
    hadc->Instance->SQR1 &= ~(ADC_SQR1_L);
    if (hadc->Init.ScanConvMode == ADC_SCAN_ENABLE)
    {
      /* Set number of ranks in regular group sequencer */
      hadc->Instance->SQR1 |=  (hadc->Init.NbrOfConversion - (uint8_t)1);
    } 
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Initialize the ADC state */
    hadc->State = HAL_ADC_STATE_READY;
  
  }
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
        
    tmpHALStatus = HAL_ERROR;
  }
  
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Initializes the ADC peripheral and regular group according to  
  *         parameters specified in structure "ADC_InitTypeDef".
  * @note   As prerequisite, ADC clock must be configured at RCC top level
  *         (clock source APB2).
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
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check ADC handle */
  if(hadc == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_DATA_ALIGN(hadc->Init.DataAlign));
  assert_param(IS_ADC_SCAN_MODE(hadc->Init.ScanConvMode));
  assert_param(IS_ADC_REGULAR_NB_CONV(hadc->Init.NbrOfConversion));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DiscontinuousConvMode));
  assert_param(IS_ADC_REGULAR_DISCONT_NUMBER(hadc->Init.NbrOfDiscConversion));
  assert_param(IS_ADC_EXTTRIG(hadc->Init.ExternalTrigConv));       
      
  /* As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured    */
  /* at RCC top level.                                                        */
  /* For example:                                                             */
  /*   __ADC1_CLK_ENABLE();                                                   */

  
  /* Actions performed only if ADC is coming from state reset:                */
  /* - Initialization of ADC MSP                                              */
  if (hadc->State == HAL_ADC_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_ADC_MspInit(hadc);
  }
  
  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC peripheral */
  /* Note: In case of ADC already enabled, precaution to not launch an        */
  /*       unwanted conversion while modifying register CR2 by writing 1 to   */
  /*       bit ADON.                                                          */
  tmpHALStatus = ADC_ConversionStop_Disable(hadc);
  
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Initialize the ADC state */
    hadc->State = HAL_ADC_STATE_BUSY;

    /* Set ADC parameters */
    
    /* Configuration of ADC:                                                  */
    /*  - data alignment                                                      */
    /*  - external trigger to start conversion                                */
    /*  - external trigger polarity (always set to 1, because needed for all  */
    /*    triggers: external trigger of SW start)                             */
    /*  - continuous conversion mode                                          */
    hadc->Instance->CR2 &= ~( ADC_CR2_ALIGN   |
                              ADC_CR2_EXTSEL  |
                              ADC_CR2_EXTTRIG |
                              ADC_CR2_CONT     );
    
    hadc->Instance->CR2 |= ( hadc->Init.DataAlign                                   |
                             hadc->Init.ExternalTrigConv                            |
                             ADC_CR2_EXTTRIG                                        |
                             __HAL_ADC_CR2_CONTINUOUS(hadc->Init.ContinuousConvMode) );
        
    /* Configuration of ADC:                                                  */
    /*  - scan mode                                                           */
    /*  - discontinuous mode disable/enable                                   */
    /*  - discontinuous mode number of conversions                            */
    hadc->Instance->CR1 &= ~( ADC_CR1_SCAN    |
                              ADC_CR1_DISCEN  |
                              ADC_CR1_DISCNUM  );
    
    hadc->Instance->CR1 |= ( __HAL_ADC_CR1_SCAN(hadc->Init.ScanConvMode) );

    /* Enable discontinuous mode only if continuous mode is disabled */
    if ((hadc->Init.DiscontinuousConvMode == ENABLE) &&
        (hadc->Init.ContinuousConvMode == DISABLE)     )
    {    
      /* Enable the selected ADC regular discontinuous mode */
      hadc->Instance->CR1 |= (ADC_CR1_DISCEN);
      
      /* Set the number of channels to be converted in discontinuous mode */
      hadc->Instance->CR1 |= __HAL_ADC_CR1_DISCONTINUOUS_NUM(hadc->Init.NbrOfDiscConversion);
    }

    /* Configuration of regular group sequencer:                              */
    /* - if scan mode is disabled, regular channels sequence length is set to */
    /*   0x00: 1 channel converted (channel on regular rank 1)                */
    /*   Parameter "NbrOfConversion" is discarded.                            */
    /*   Note: Scan mode is present by hardware on this device and, if        */
    /*   disabled, discards automatically nb of conversions. Anyway, nb of    */
    /*   conversions is forced to 0x00 for alignment over all STM32 devices.  */
    /* - if scan mode is enabled, regular channels sequence length is set to  */
    /*   parameter "NbrOfConversion"                                          */
    hadc->Instance->SQR1 &= ~(ADC_SQR1_L);
    if (hadc->Init.ScanConvMode == ADC_SCAN_ENABLE)
    {
      /* Set number of ranks in regular group sequencer */
      hadc->Instance->SQR1 |=  __HAL_ADC_SQR1_L(hadc->Init.NbrOfConversion);
    }
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Initialize the ADC state */
    hadc->State = HAL_ADC_STATE_READY;
  }
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
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
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  ADC_Common_TypeDef *tmpADC_Common;
  ADC_HandleTypeDef tmphadcSharingSameCommonRegister;
  
  /* Check ADC handle */
  if(hadc == HAL_NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Change ADC state */
  hadc->State = HAL_ADC_STATE_BUSY;
  
  /* Stop potential conversion on going, on regular and injected groups */
  tmpHALStatus = ADC_ConversionStop(hadc, REGULAR_INJECTED_GROUP);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Flush register JSQR: queue sequencer reset when injected queue         */
    /* sequencer is enabled and ADC disabled                                  */
    /* Enable injected queue sequencer after injected conversion stop         */
    hadc->Instance->CFGR |= ADC_CFGR_JQM;
    
    /* Disable the ADC peripheral */
    tmpHALStatus = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
    else
    {      
      tmpHALStatus = HAL_ERROR;
    }
  }
  
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (tmpHALStatus != HAL_ERROR)
  {
  
    /* ========== Reset ADC registers ========== */
    /* Reset register IER */
    __HAL_ADC_DISABLE_IT(hadc, (ADC_IT_AWD3  | ADC_IT_AWD2 | ADC_IT_AWD1 |
                                ADC_IT_JQOVF | ADC_IT_OVR  |
                                ADC_IT_JEOS  | ADC_IT_JEOC |
                                ADC_IT_EOS   | ADC_IT_EOC  |
                                ADC_IT_EOSMP | ADC_IT_RDY                 ) );
        
    /* Reset register ISR */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_AWD3  | ADC_FLAG_AWD2 | ADC_FLAG_AWD1 |
                                ADC_FLAG_JQOVF | ADC_FLAG_OVR  |
                                ADC_FLAG_JEOS  | ADC_FLAG_JEOC |
                                ADC_FLAG_EOS   | ADC_FLAG_EOC  |
                                ADC_FLAG_EOSMP | ADC_FLAG_RDY                   ) );
    
    /* Reset register CR */
    /* Bits ADC_CR_JADSTP, ADC_CR_ADSTP, ADC_CR_JADSTART, ADC_CR_ADSTART are  */
    /* in access mode "read-set": no direct reset applicable.                 */
    /* Reset Calibration mode to default setting (single ended):              */
    /* Disable voltage regulator:                                             */
    /* Note: Voltage regulator disable is conditioned to ADC state disabled:  */
    /*       already done above.                                              */
    /* Note: Voltage regulator disable is intended for power saving.          */
    /* Sequence to disable voltage regulator:                                 */
    /* 1. Set the intermediate state before moving the ADC voltage regulator  */
    /*    to disable state.                                                   */
    hadc->Instance->CR &= ~(ADC_CR_ADVREGEN | ADC_CR_ADCALDIF);
    /* 2. Set ADVREGEN bits to 0x10 */
    hadc->Instance->CR |= ADC_CR_ADVREGEN_1;
        
    /* Reset register CFGR */
    hadc->Instance->CFGR &= ~(ADC_CFGR_AWD1CH  | ADC_CFGR_JAUTO   | ADC_CFGR_JAWD1EN |   
                              ADC_CFGR_AWD1EN  | ADC_CFGR_AWD1SGL | ADC_CFGR_JQM     |     
                              ADC_CFGR_JDISCEN | ADC_CFGR_DISCNUM | ADC_CFGR_DISCEN  | 
                              ADC_CFGR_AUTDLY  | ADC_CFGR_CONT    | ADC_CFGR_OVRMOD  |     
                              ADC_CFGR_EXTEN   | ADC_CFGR_EXTSEL  | ADC_CFGR_ALIGN   |     
                              ADC_CFGR_RES     | ADC_CFGR_DMACFG  | ADC_CFGR_DMAEN    );
    
    /* Reset register SMPR1 */
    hadc->Instance->SMPR1 &= ~(ADC_SMPR1_SMP9 | ADC_SMPR1_SMP8 | ADC_SMPR1_SMP7 | 
                               ADC_SMPR1_SMP6 | ADC_SMPR1_SMP5 | ADC_SMPR1_SMP4 | 
                               ADC_SMPR1_SMP3 | ADC_SMPR1_SMP2 | ADC_SMPR1_SMP1  );
    
    /* Reset register SMPR2 */
    hadc->Instance->SMPR2 &= ~(ADC_SMPR2_SMP18 | ADC_SMPR2_SMP17 | ADC_SMPR2_SMP16 | 
                               ADC_SMPR2_SMP15 | ADC_SMPR2_SMP14 | ADC_SMPR2_SMP13 | 
                               ADC_SMPR2_SMP12 | ADC_SMPR2_SMP11 | ADC_SMPR2_SMP10  );
    
    /* Reset register TR1 */
    hadc->Instance->TR1 &= ~(ADC_TR1_HT1 | ADC_TR1_LT1);
    
    /* Reset register TR2 */
    hadc->Instance->TR2 &= ~(ADC_TR2_HT2 | ADC_TR2_LT2);
    
    /* Reset register TR3 */
    hadc->Instance->TR3 &= ~(ADC_TR3_HT3 | ADC_TR3_LT3);
    
    /* Reset register SQR1 */
    hadc->Instance->SQR1 &= ~(ADC_SQR1_SQ4 | ADC_SQR1_SQ3 | ADC_SQR1_SQ2 | 
                              ADC_SQR1_SQ1 | ADC_SQR1_L);
    
    /* Reset register SQR2 */
    hadc->Instance->SQR2 &= ~(ADC_SQR2_SQ9 | ADC_SQR2_SQ8 | ADC_SQR2_SQ7 | 
                              ADC_SQR2_SQ6 | ADC_SQR2_SQ5);
    
    /* Reset register SQR3 */
    hadc->Instance->SQR3 &= ~(ADC_SQR3_SQ14 | ADC_SQR3_SQ13 | ADC_SQR3_SQ12 | 
                              ADC_SQR3_SQ11 | ADC_SQR3_SQ10);
    
    /* Reset register SQR4 */
    hadc->Instance->SQR4 &= ~(ADC_SQR4_SQ16 | ADC_SQR4_SQ15);
    
    /* Reset register DR */
    /* bits in access mode read only, no direct reset applicable*/
      
    /* Reset register OFR1 */
    hadc->Instance->OFR1 &= ~(ADC_OFR1_OFFSET1_EN | ADC_OFR1_OFFSET1_CH | ADC_OFR1_OFFSET1);
    /* Reset register OFR2 */
    hadc->Instance->OFR2 &= ~(ADC_OFR2_OFFSET2_EN | ADC_OFR2_OFFSET2_CH | ADC_OFR2_OFFSET2);
    /* Reset register OFR3 */
    hadc->Instance->OFR3 &= ~(ADC_OFR3_OFFSET3_EN | ADC_OFR3_OFFSET3_CH | ADC_OFR3_OFFSET3);
    /* Reset register OFR4 */
    hadc->Instance->OFR4 &= ~(ADC_OFR4_OFFSET4_EN | ADC_OFR4_OFFSET4_CH | ADC_OFR4_OFFSET4);
    
    /* Reset registers JDR1, JDR2, JDR3, JDR4 */
    /* bits in access mode read only, no direct reset applicable*/
    
    /* Reset register AWD2CR */
    hadc->Instance->AWD2CR &= ~(ADC_AWD2CR_AWD2CH);
    
    /* Reset register AWD3CR */
    hadc->Instance->AWD3CR &= ~(ADC_AWD3CR_AWD3CH);
    
    /* Reset register DIFSEL */
    hadc->Instance->DIFSEL &= ~(ADC_DIFSEL_DIFSEL);
    
    /* Reset register CALFACT */
    hadc->Instance->CALFACT &= ~(ADC_CALFACT_CALFACT_D | ADC_CALFACT_CALFACT_S);

    
    
    
    
    
    /* ========== Reset common ADC registers ========== */
    
    /* Pointer to the common control register to which is belonging hadc      */
    /* (Depending on STM32F3 product, there may be up to 4 ADC and 2 common   */
    /* control registers)                                                     */
    tmpADC_Common = __HAL_ADC_COMMON_REGISTER(hadc);
    
    /* Set handle of the other ADC sharing the same common register           */
    __HAL_ADC_COMMON_ADC_OTHER(hadc, &tmphadcSharingSameCommonRegister);
    
    /* Software is allowed to change common parameters only when all ADCs of  */
    /* the common group are disabled.                                         */
    if ((__HAL_ADC_IS_ENABLED(hadc) == RESET)                                  &&
        ( (tmphadcSharingSameCommonRegister.Instance == HAL_NULL) ||
          (__HAL_ADC_IS_ENABLED(&tmphadcSharingSameCommonRegister) == RESET) ))
    {
      /* Reset configuration of ADC common register CCR:
        - clock mode: CKMODE
        - multimode related parameters: MDMA, DMACFG, DELAY, MULTI (set into
          HAL_ADCEx_MultiModeConfigChannel() )
        - internal measurement paths: Vbat, temperature sensor, Vref (set into
          HAL_ADC_ConfigChannel() or HAL_ADCEx_InjectedConfigChannel() )
      */
      tmpADC_Common->CCR &= ~( ADC_CCR_CKMODE |
                               ADC_CCR_VBATEN |
                               ADC_CCR_TSEN   |
                               ADC_CCR_VREFEN |
                               ADC_CCR_DMACFG |
                               ADC_CCR_DMACFG |
                               ADC_CCR_DELAY  |
                               ADC_CCR_MULTI   );
      
      /* Other ADC common registers (CSR, CDR) are in access mode read only,
         no direct reset applicable */
    }
    
    
    /* ========== Hard reset of ADC peripheral ========== */
    /* Performs a global reset of the entire ADC peripheral: ADC state is     */
    /* forced to a similar state after device power-on.                       */
    /* Caution:                                                               */
    /* These settings impact both ADC of common group: ADC1&ADC2, ADC3&ADC4   */
    /* if available (ADC2, ADC3, ADC4 availability depends on STM32 product)  */
    /* As this function is intended to reset a single ADC, instructions for   */
    /* global reset of multiple ADC have been let commented below.            */
    /*                                                                        */
    /* If global reset of common ADC is corresponding to the current          */
    /* application, copy-paste and uncomment the following reset code into    */
    /* function "void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)":            */
    /*                                                                        */
    /* ADC clock reset */
    /* if((hadc->Instance == ADC1) || (hadc->Instance == ADC2))               */
    /* {                                                                      */          
    /*   __ADC12_FORCE_RESET();                                               */    
    /*   __ADC12_RELEASE_RESET();                                             */    
    /* }                                                                      */    
    /* else                                                                   */    
    /* {                                                                      */    
    /*   __ADC34_FORCE_RESET();                                               */    
    /*   __ADC34_RELEASE_RESET();                                             */    
    /* }                                                                      */    
    /*                                                                        */
    /* ADC clock disable of both possible clock sources: AHB clock and        */
    /* PLL clock.                                                             */
    /* if((hadc->Instance == ADC1) || (hadc->Instance == ADC2))               */ 
    /* {                                                                      */ 
    /*   __HAL_RCC_ADC12_CONFIG(RCC_ADC12PLLCLK_OFF);                         */
    /*   __ADC12_CLK_DISABLE();                                               */
    /* }                                                                      */ 
    /* else                                                                   */
    /* {                                                                      */ 
    /*   __HAL_RCC_ADC34_CONFIG(RCC_ADC12PLLCLK_OFF);                         */
    /*   __ADC34_CLK_DISABLE();                                               */
    /* }                                                                      */ 
    
    /* DeInit the low level hardware */
    HAL_ADC_MspDeInit(hadc);
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_RESET; 
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Deinitialize the ADC peripheral registers to its default reset values.
  * @note   To not impact other ADCs, reset of common ADC registers have been
  *         left commented below.
  *         If needed, the example code can be copied and uncommented into
  *         function HAL_ADC_MspDeInit().
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{ 
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check ADC handle */
  if(hadc == HAL_NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Change ADC state */
  hadc->State = HAL_ADC_STATE_BUSY;
  
  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC peripheral */
  tmpHALStatus = ADC_ConversionStop_Disable(hadc);
  
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* ========== Reset ADC registers ========== */
    /* Reset register SR */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_AWD | ADC_FLAG_JEOC | ADC_FLAG_EOC |
                                ADC_FLAG_JSTRT | ADC_FLAG_STRT));
                         
    /* Reset register CR1 */
    hadc->Instance->CR1 &= ~(ADC_CR1_AWDEN | ADC_CR1_JAWDEN | ADC_CR1_DISCNUM | 
                             ADC_CR1_JDISCEN | ADC_CR1_DISCEN | ADC_CR1_JAUTO | 
                             ADC_CR1_AWDSGL | ADC_CR1_SCAN | ADC_CR1_JEOCIE |   
                             ADC_CR1_AWDIE | ADC_CR1_EOCIE | ADC_CR1_AWDCH);
    
    /* Reset register CR2 */
    hadc->Instance->CR2 &= ~(ADC_CR2_TSVREFE | ADC_CR2_SWSTART | ADC_CR2_JSWSTART | 
                             ADC_CR2_EXTTRIG | ADC_CR2_EXTSEL | ADC_CR2_JEXTTRIG |  
                             ADC_CR2_JEXTSEL | ADC_CR2_ALIGN | ADC_CR2_DMA |        
                             ADC_CR2_RSTCAL | ADC_CR2_CAL | ADC_CR2_CONT |          
                             ADC_CR2_ADON );
    
    /* Reset register SMPR1 */
    hadc->Instance->SMPR1 &= ~(ADC_SMPR1_SMP17 | ADC_SMPR1_SMP16 | ADC_SMPR1_SMP15 | 
                               ADC_SMPR1_SMP14 | ADC_SMPR1_SMP13 | ADC_SMPR1_SMP12 | 
                               ADC_SMPR1_SMP11 |ADC_SMPR1_SMP10);
    
    /* Reset register SMPR2 */
    hadc->Instance->SMPR2 &= ~(ADC_SMPR2_SMP9 | ADC_SMPR2_SMP8 | ADC_SMPR2_SMP7 | 
                               ADC_SMPR2_SMP6 | ADC_SMPR2_SMP5 | ADC_SMPR2_SMP4 | 
                               ADC_SMPR2_SMP3 | ADC_SMPR2_SMP2 | ADC_SMPR2_SMP1 | 
                               ADC_SMPR2_SMP0);
    
    /* Reset register JOFR1 */
    hadc->Instance->JOFR1 &= ~(ADC_JOFR1_JOFFSET1);
    /* Reset register JOFR2 */
    hadc->Instance->JOFR2 &= ~(ADC_JOFR2_JOFFSET2);
    /* Reset register JOFR3 */
    hadc->Instance->JOFR3 &= ~(ADC_JOFR3_JOFFSET3);
    /* Reset register JOFR4 */
    hadc->Instance->JOFR4 &= ~(ADC_JOFR4_JOFFSET4);
    
    /* Reset register HTR */
    hadc->Instance->HTR &= ~(ADC_HTR_HT);
    /* Reset register LTR */
    hadc->Instance->LTR &= ~(ADC_LTR_LT);
    
    /* Reset register SQR1 */
    hadc->Instance->SQR1 &= ~(ADC_SQR1_L    |
                              ADC_SQR1_SQ16 | ADC_SQR1_SQ15 | 
                              ADC_SQR1_SQ14 | ADC_SQR1_SQ13  );
    
    /* Reset register SQR1 */
    hadc->Instance->SQR1 &= ~(ADC_SQR1_L    |
                              ADC_SQR1_SQ16 | ADC_SQR1_SQ15 | 
                              ADC_SQR1_SQ14 | ADC_SQR1_SQ13  );
    
    /* Reset register SQR2 */
    hadc->Instance->SQR2 &= ~(ADC_SQR2_SQ12 | ADC_SQR2_SQ11 | ADC_SQR2_SQ10 | 
                              ADC_SQR2_SQ9  | ADC_SQR2_SQ8  | ADC_SQR2_SQ7   );
    
    /* Reset register SQR3 */
    hadc->Instance->SQR3 &= ~(ADC_SQR3_SQ6 | ADC_SQR3_SQ5 | ADC_SQR3_SQ4 | 
                              ADC_SQR3_SQ3 | ADC_SQR3_SQ2 | ADC_SQR3_SQ1  );
    
    /* Reset register JSQR */
    hadc->Instance->JSQR &= ~(ADC_JSQR_JL |
                              ADC_JSQR_JSQ4 | ADC_JSQR_JSQ3 | 
                              ADC_JSQR_JSQ2 | ADC_JSQR_JSQ1  );
    
    /* Reset register JSQR */
    hadc->Instance->JSQR &= ~(ADC_JSQR_JL |
                              ADC_JSQR_JSQ4 | ADC_JSQR_JSQ3 | 
                              ADC_JSQR_JSQ2 | ADC_JSQR_JSQ1  );
    
    /* Reset register DR */
    /* bits in access mode read only, no direct reset applicable*/
    
    /* Reset registers JDR1, JDR2, JDR3, JDR4 */
    /* bits in access mode read only, no direct reset applicable*/
    
    /* Reset VBAT measurement path, in case of enabled before by selecting    */
    /* channel ADC_CHANNEL_VBAT. */
    SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_VBAT);
    
    
    /* ========== Hard reset ADC peripheral ========== */
    /* Performs a global reset of the entire ADC peripheral: ADC state is     */
    /* forced to a similar state after device power-on.                       */
    /* If needed, copy-paste and uncomment the following reset code into      */
    /* function "void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)":              */
    /*                                                                        */
    /*  __ADC1_FORCE_RESET();                                                 */
    /*  __ADC1_RELEASE_RESET();                                               */
    
    /* DeInit the low level hardware */
    HAL_ADC_MspDeInit(hadc);
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_RESET; 
  
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

/**
  * @}
  */

/** @defgroup ADCEx_Exported_Functions_Group2 Extended Input and Output operation functions
  * @brief    Extended IO operation functions
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

      (+) Start conversion of injected group.
      (+) Stop conversion of injected group.
      (+) Poll for conversion complete on injected group.
      (+) Get result of injected channel conversion.
      (+) Start conversion of injected group and enable interruptions.
      (+) Stop conversion of injected group and disable interruptions.

      (+) Start multimode and enable DMA transfer.
      (+) Stop multimode and disable ADC DMA transfer.
      (+) Get result of multimode conversion.

      (+) Perform the ADC self-calibration for single or differential ending.
      (+) Get calibration factors for single or differential ending.
      (+) Set calibration factors for single or differential ending.

@endverbatim
  * @{
  */
  
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Enables ADC, starts conversion of regular group.
  *         Interruptions enabled in this function: None.
  * @note:  Case of multimode enabled (for devices with several ADCs): if ADC
  *         is slave, ADC is enabled only (conversion is not started). If ADC  
  *         is master, ADC is enabled and multimode conversion is started.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
   
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* State machine update: Check if an injected conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_INJ)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    }

    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS | ADC_FLAG_OVR));
    
    /* Enable conversion of regular group.                                    */
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* Case of multimode enabled (for devices with several ADCs): if ADC is   */
    /* slave, ADC is enabled only (conversion is not started). If ADC is      */
    /* master, ADC is enabled and conversion is started.                      */
    if (__HAL_ADC_NONMULTIMODE_OR_MULTIMODEMASTER(hadc)   )
    {
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Enables ADC, starts conversion of regular group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
   
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* State machine update: Check if an injected conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_INJ)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    }

    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
  
    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOC);
    
    /* Start conversion of regular group if software start has been selected. */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* Note: Alternate trigger for single conversion could be to force an     */
    /*       additional set of bit ADON "hadc->Instance->CR2 |= ADC_CR2_ADON;"*/
    if (__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc))
    {
      /* Start ADC conversion on regular group */
      hadc->Instance->CR2 |= ADC_CR2_SWSTART;
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{ 
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion on going, on regular and injected groups */
  tmpHALStatus = ADC_ConversionStop(hadc, REGULAR_INJECTED_GROUP);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* 2. Disable the ADC peripheral */
    tmpHALStatus = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Stop ADC conversion of regular group (and injected channels in 
  *         case of auto_injection mode), disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
     
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC peripheral */
  tmpHALStatus = ADC_ConversionStop_Disable(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_READY;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Wait for regular group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t tmp_Flag_EOC;
 
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

/* If end of conversion selected to end of sequence */
  if (hadc->Init.EOCSelection == EOC_SEQ_CONV)
  {
    tmp_Flag_EOC = ADC_FLAG_EOS;
  }
  /* If end of conversion selected to end of each conversion */
  else /* EOC_SINGLE_CONV */
  {
    tmp_Flag_EOC = (ADC_FLAG_EOC | ADC_FLAG_EOS);
  }
    
  /* Get timeout */
  tickstart = HAL_GetTick();  
     
  /* Wait until End of Conversion flag is raised */
  while(HAL_IS_BIT_CLR(hadc->Instance->ISR, tmp_Flag_EOC))
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
      {
        /* Update ADC state machine to timeout */
        hadc->State = HAL_ADC_STATE_TIMEOUT;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
  }
  
  /* Clear end of conversion flag of regular group if low power feature       */
  /* "LowPowerAutoWait " is disabled, to not interfere with this feature      */
  /* until data register is read using function HAL_ADC_GetValue().           */
  if (hadc->Init.LowPowerAutoWait == DISABLE)
  {
    /* Clear regular group conversion flag */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS));
  }
  
  /* Update state machine on conversion status if not in error state */
  if(hadc->State != HAL_ADC_STATE_ERROR)
  {
    /* Update ADC state machine */
    if(hadc->State != HAL_ADC_STATE_EOC_INJ_REG)
    {
      /* Check if a conversion is ready on injected group */
      if(hadc->State == HAL_ADC_STATE_EOC_INJ)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
      }
      else
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_REG;
      }
    }
  }
  
  /* Return ADC state */
  return HAL_OK;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Wait for regular group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Variables for polling in case of scan mode enabled */
  uint32_t Conversion_Timeout_CPU_cycles_max =0;
  uint32_t Conversion_Timeout_CPU_cycles =0;
 
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Get timeout */
  tickstart = HAL_GetTick();  
     
  /* Polling for end of conversion: differentiation if single/sequence        */
  /* conversion.                                                              */
  /*  - If single conversion for regular group (Scan mode disabled or enabled */
  /*    with NbrOfConversion =1), flag EOC is used to determine the           */
  /*    conversion completion.                                                */
  /*  - If sequence conversion for regular group, flag EOC is set only a the  */
  /*    end of the sequence. To poll for each conversion, the maximum         */
  /*    conversion time is calculated from ADC conversion time (selected      */
  /*    sampling time + conversion time of 12.5 ADC clock cycles) and         */
  /*    APB2/ADC clock prescalers (depending on settings, conversion time     */
  /*    range can be from 28 to 32256 CPU cycles).                            */
  if ((HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_SCAN)) &&
      ((hadc->Instance->SQR1 & ADC_SQR1_L) == RESET)        )
  {
    /* Wait until End of Conversion flag is raised */
    while(HAL_IS_BIT_CLR(hadc->Instance->SR, ADC_FLAG_EOC))
    {
      /* Check if timeout is disabled (set to infinite wait) */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Update ADC state machine to timeout */
          hadc->State = HAL_ADC_STATE_TIMEOUT;
          
          /* Process unlocked */
          __HAL_UNLOCK(hadc);
          
          return HAL_ERROR;
        }
      }
    }
  }
  else
  {
    /* Computation of CPU cycles corresponding to ADC conversion cycles       */
    /* Retrieve ADC clock prescaler and ADC maximum conversion cycles on all  */
    /* channels.                                                              */
    Conversion_Timeout_CPU_cycles_max = __HAL_ADC_CLOCK_PRECSALER_RANGE() ;
    Conversion_Timeout_CPU_cycles_max *= __HAL_ADC_CONVCYCLES_MAX_RANGE(hadc);

    /* Maximum conversion cycles taking in account offset of 34 CPU cycles:   */
    /* number of CPU cycles for processing of conversion cycles estimation.   */
    Conversion_Timeout_CPU_cycles = 34;
    
    /* Poll with maximum conversion time */
    while(Conversion_Timeout_CPU_cycles < Conversion_Timeout_CPU_cycles_max)
    {
      /* Check if timeout is disabled (set to infinite wait) */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Update ADC state machine to timeout */
          hadc->State = HAL_ADC_STATE_TIMEOUT;
          
          /* Process unlocked */
          __HAL_UNLOCK(hadc);
          
          return HAL_ERROR;
        }
      }
      Conversion_Timeout_CPU_cycles ++;
    }
  }
  
  /* Clear regular group conversion flag */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_STRT | ADC_FLAG_EOC);
  
  /* Update state machine on conversion status if not in error state */
  if(hadc->State != HAL_ADC_STATE_ERROR)
  {
    /* Update ADC state machine */
    if(hadc->State != HAL_ADC_STATE_EOC_INJ_REG)
    {
      /* Check if a conversion is ready on injected group */
      if(hadc->State == HAL_ADC_STATE_EOC_INJ)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
      }
      else
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_REG;
      }
    }
  }
  
  /* Return ADC state */
  return HAL_OK;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
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
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart; 

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_EVENT_TYPE(EventType));
  
  tickstart = HAL_GetTick();   
      
  /* Check selected event flag */
  while(__HAL_ADC_GET_FLAG(hadc, EventType) == RESET)
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
      {
        /* Update ADC state machine to timeout */
        hadc->State = HAL_ADC_STATE_TIMEOUT;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
  }

  
  switch(EventType)
  {
  /* Analog watchdog (level out of window) event */
  /* Note: In case of several analog watchdog enabled, if needed to know      */
  /* which one triggered and on which ADCx, test ADC state of Analog Watchdog */
  /* flags HAL_ADC_STATE_AWD/2/3 function.                                    */
  /* For example: "if (HAL_ADC_GetState(hadc1) == HAL_ADC_STATE_AWD) "        */
  /*              "if (HAL_ADC_GetState(hadc1) == HAL_ADC_STATE_AWD2)"        */
  /*              "if (HAL_ADC_GetState(hadc1) == HAL_ADC_STATE_AWD3)"        */
  /* Check analog watchdog 1 flag */
  case AWD_EVENT:
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD;
      
    /* Clear ADC analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD1);
    break;
  
  /* Check analog watchdog 2 flag */
  case AWD2_EVENT:
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD2;
      
    /* Clear ADC analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD2);
    break;
  
  /* Check analog watchdog 3 flag */
  case AWD3_EVENT:
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD3;
      
    /* Clear ADC analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD3);
    break;
  
  /* Injected context queue overflow event */
  case JQOVF_EVENT:
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_ERROR;
      
    /* Set ADC error code to Injected context queue overflow */
    hadc->ErrorCode |= HAL_ADC_ERROR_JQOVF;
    
    /* Clear ADC Injected context queue overflow flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JQOVF);
    break;
     
  /* Overrun event */
  default: /* Case OVR_EVENT */
    /* If overrun is set to overwrite previous data, overrun event is not     */
    /* considered as an error.                                                */
    /* (cf ref manual "Managing conversions without using the DMA and without */
    /* overrun ")                                                             */
    if (hadc->Init.Overrun == OVR_DATA_PRESERVED)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_ERROR;
        
      /* Set ADC error code to overrun */
      hadc->ErrorCode |= HAL_ADC_ERROR_OVR;
    }
    
    /* Clear ADC Overrun flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_OVR);
    break;
  }
  
  /* Return ADC state */
  return HAL_OK;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Poll for conversion event.
  * @param  hadc: ADC handle
  * @param  EventType: the ADC event type.
  *          This parameter can be one of the following values:
  *            @arg AWD_EVENT: ADC Analog watchdog event.
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart; 

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_EVENT_TYPE(EventType));
  
  tickstart = HAL_GetTick();   
      
  /* Check selected event flag */
  while(__HAL_ADC_GET_FLAG(hadc, EventType) == RESET)
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
      {
        /* Update ADC state machine to timeout */
        hadc->State = HAL_ADC_STATE_TIMEOUT;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
  }
  
  /* Analog watchdog (level out of window) event */
  /* Change ADC state */
  hadc->State = HAL_ADC_STATE_AWD;
    
  /* Clear ADC analog watchdog flag */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD);
  
  /* Return ADC state */
  return HAL_OK;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
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
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
    
  /* Process locked */
  __HAL_LOCK(hadc);
   
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* State machine update: Check if an injected conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_INJ)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    } 
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS | ADC_FLAG_OVR));
    
    /* Enable ADC end of conversion interrupt */
    /* Enable ADC overrun interrupt */  
    switch(hadc->Init.EOCSelection)
    {
      case EOC_SEQ_CONV: 
        __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC);
        __HAL_ADC_ENABLE_IT(hadc, (ADC_IT_EOS | ADC_IT_OVR));
        break;
      /* case EOC_SINGLE_CONV */
      default:
        __HAL_ADC_ENABLE_IT(hadc, (ADC_IT_EOC | ADC_IT_EOS | ADC_IT_OVR));
        break;
    }
    
    /* Enable conversion of regular group.                                    */
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* Case of multimode enabled (for devices with several ADCs): if ADC is   */
    /* slave, ADC is enabled only (conversion is not started). If ADC is      */
    /* master, ADC is enabled and conversion is started.                      */
    if (__HAL_ADC_NONMULTIMODE_OR_MULTIMODEMASTER(hadc)   )
    {
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Enables ADC, starts conversion of regular group with interruption.
  *         Interruptions enabled in this function: EOC (end of conversion),
  *         overrun (if available).
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* State machine update: Check if an injected conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_INJ)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    }

    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOC);
    
    /* Enable end of conversion interrupt for regular group */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_EOC);
    
    /* Start conversion of regular group if software start has been selected. */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    if (__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc))
    {
      /* Start ADC conversion on regular group */
      hadc->Instance->CR2 |= ADC_CR2_SWSTART;
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable interruption of 
  *         end-of-conversion, disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion on going, on regular and injected groups */
  tmpHALStatus = ADC_ConversionStop(hadc, REGULAR_INJECTED_GROUP);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Disable ADC end of conversion interrupt for regular group */
    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc, (ADC_IT_EOC | ADC_IT_EOS | ADC_IT_OVR));
    
    /* 2. Disable the ADC peripheral */
    tmpHALStatus = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable interrution of 
  *         end-of-conversion, disable ADC peripheral.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
     
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC peripheral */
  tmpHALStatus = ADC_ConversionStop_Disable(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Disable ADC end of conversion interrupt for regular group */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC);
    
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_READY;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
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
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
    
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Verification if multimode is disabled (for devices with several ADC)     */
  /* If multimode is enabled, dedicated function multimode conversion         */
  /* start DMA must be used.                                                  */
  if(__HAL_ADC_COMMON_CCR_MULTI(hadc) == RESET)
  {
    
    /* Enable the ADC peripheral */
    tmpHALStatus = ADC_Enable(hadc);
    
    /* Start conversion if ADC is effectively enabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* State machine update: Check if an injected conversion is ongoing */
      if(hadc->State == HAL_ADC_STATE_BUSY_INJ)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
      }
      else
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_BUSY_REG;
      }
      
      /* Set ADC error code to none */
      __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
      
      /* Set the DMA transfer complete callback */
      hadc->DMA_Handle->XferCpltCallback = ADC_DMAConvCplt;

      /* Set the DMA half transfer complete callback */
      hadc->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;
      
      /* Set the DMA error callback */
      hadc->DMA_Handle->XferErrorCallback = ADC_DMAError;

            
      /* Manage ADC and DMA start: ADC overrun interruption, DMA start, ADC   */
      /* start (in case of SW start):                                         */
      
      /* Clear regular group conversion flag and overrun flag */
      /* (To ensure of no unknown state from potential previous ADC           */
      /* operations)                                                          */
      __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS | ADC_FLAG_OVR));
      
      /* Enable ADC overrun interrupt */
      __HAL_ADC_ENABLE_IT(hadc, ADC_IT_OVR);
      
      /* Enable ADC DMA mode */
      hadc->Instance->CFGR |= ADC_CFGR_DMAEN;
      
      /* Start the DMA channel */
      HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DR, (uint32_t)pData, Length);
               
      /* Enable conversion of regular group.                                  */
      /* If software start has been selected, conversion starts immediately.  */
      /* If external trigger has been selected, conversion will start at next */
      /* trigger event.                                                       */
      hadc->Instance->CR |= ADC_CR_ADSTART;
      
    }
  }
  else
  {
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Enables ADC, starts conversion of regular group and transfers result
  *         through DMA.
  *         Interruptions enabled in this function:
  *         overrun (if available), DMA half transfer, DMA transfer complete. 
  *         Each of these interruptions has its dedicated callback function.
  * @note   For devices with several ADCs: This function is for single-ADC mode 
  *         only. For multimode, use the dedicated MultimodeStart function.
  * @param  hadc: ADC handle
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* State machine update: Check if an injected conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_INJ)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    }
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    

    /* Set the DMA transfer complete callback */
    hadc->DMA_Handle->XferCpltCallback = ADC_DMAConvCplt;
       
    /* Set the DMA half transfer complete callback */
    hadc->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;
    
    /* Set the DMA error callback */
    hadc->DMA_Handle->XferErrorCallback = ADC_DMAError;

    
    /* Manage ADC and DMA start: ADC overrun interruption, DMA start, ADC     */
    /* start (in case of SW start):                                           */
    
    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOC);
    
    /* Enable ADC DMA mode */
    hadc->Instance->CR2 |= ADC_CR2_DMA;
    
    /* Start the DMA channel */
    HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DR, (uint32_t)pData, Length);

    /* Start conversion of regular group if software start has been selected. */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* Note: Alternate trigger for single conversion could be to force an     */
    /*       additional set of bit ADON "hadc->Instance->CR2 |= ADC_CR2_ADON;"*/
    if (__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc))
    {
      /* Start ADC conversion on regular group */
      hadc->Instance->CR2 |= ADC_CR2_SWSTART;
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Stop ADC conversion of regular group (and injected channels in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  *         Each of these interruptions has its dedicated callback function.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function is for single-ADC mode only. For multimode, use the 
  *         dedicated MultimodeStop function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc)
{  
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion on going, on regular and injected groups */
  tmpHALStatus = ADC_ConversionStop(hadc, REGULAR_INJECTED_GROUP);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus == HAL_OK)
  {
    /* Disable ADC DMA (ADC DMA configuration ADC_CFGR_DMACFG is kept) */
    hadc->Instance->CFGR &= ~ADC_CFGR_DMAEN;
    
    /* Disable the DMA channel (in case of DMA in circular mode or stop while */
    /* while DMA transfer is on going)                                        */
    tmpHALStatus = HAL_DMA_Abort(hadc->DMA_Handle);   
    
    /* Check if DMA channel effectively disabled */
    if (tmpHALStatus != HAL_OK)
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;      
    }
    
    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IT_OVR);
    
    /* 2. Disable the ADC peripheral */
    /* Update "tmpHALStatus" only if DMA channel disabling passed, to keep in */
    /* memory a potential failing status.                                     */
    if (tmpHALStatus == HAL_OK)
    {
      tmpHALStatus = ADC_Disable(hadc);
    }
    else
    {
      ADC_Disable(hadc);
    }

    /* Check if ADC is effectively disabled */
    if (tmpHALStatus == HAL_OK)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
    
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @note   For devices with several ADCs: This function is for single-ADC mode 
  *         only. For multimode, use the dedicated MultimodeStop function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
     
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC peripheral */
  tmpHALStatus = ADC_ConversionStop_Disable(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Disable ADC DMA mode */
    hadc->Instance->CR2 &= ~ADC_CR2_DMA;

    /* Disable the DMA channel (in case of DMA in circular mode or stop while */
    /* while DMA transfer is on going)                                        */
    tmpHALStatus = HAL_DMA_Abort(hadc->DMA_Handle);
    
    /* Check if DMA channel effectively disabled */
    if (tmpHALStatus == HAL_OK)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
    else
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;      
    }
  }
    
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
    
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Get ADC regular group conversion result.
  * @param  hadc: ADC handle
  * @retval Converted value
  */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Note: EOC flag is automatically cleared by hardware when reading         */
  /*       register DR. Additionally, clear flag EOS by software.             */
  
  /* Clear regular group conversion flag */
  __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS) );
  
  /* Return ADC converted value */ 
  return hadc->Instance->DR;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Get ADC regular group conversion result.
  * @param  hadc: ADC handle
  * @retval Converted value
  */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Note: EOC flag is not cleared here by software because automatically     */
  /*       cleared by hardware when reading register DR.                      */
  
  /* Return ADC converted value */ 
  return hadc->Instance->DR;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Handles ADC interrupt request.  
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_ADC_EOC_SELECTION(hadc->Init.EOCSelection));
  
  /* ========== Check End of Conversion flag for regular group ========== */
  if( (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOC) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_EOC)) || 
      (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOS) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_EOS))   )
  {
    /* Update state machine on conversion status if not in error state */
    if(hadc->State != HAL_ADC_STATE_ERROR)
    {
      /* Check if an injected conversion is ready */
      if(hadc->State == HAL_ADC_STATE_EOC_INJ)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
      }
      else
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_REG;
      }
    }
    
    /* Disable interruption if no further conversion upcoming by regular      */
    /* external trigger or by continuous mode,                                */
    /* and if scan sequence if completed.                                     */
    if(__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc) && 
       (hadc->Init.ContinuousConvMode == DISABLE)  )
    {
      /* If End of Sequence is reached, disable interrupts */
      if( __HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOS) )
      {
        /* Allowed to modify bits ADC_IT_EOC/ADC_IT_EOS only if bit           */
        /* ADSTART==0 (no conversion on going)                                */
        if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)
        {
          /* Disable ADC end of sequence conversion interrupt */
          /* Note: Overrun interrupt was enabled with EOC interrupt in        */
          /* HAL_Start_IT(), but is not disabled here because can be used     */
          /* by overrun IRQ process below.                                    */
          __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC | ADC_IT_EOS);
        }
        else
        {
          /* Change ADC state to error state */
          hadc->State = HAL_ADC_STATE_ERROR;
          
          /* Set ADC error code to ADC IP internal error */
          hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
        }
      }
    }
    
    /* Conversion complete callback */
    /* Note: into callback, to determine if conversion has been triggered     */
    /*       from EOC or EOS, possibility to use:                             */
    /*        " if( __HAL_ADC_GET_FLAG(&hadc, ADC_FLAG_EOS)) "                */
      HAL_ADC_ConvCpltCallback(hadc);

    
    /* Clear regular group conversion flag */
    /* Note: in case of overrun set to OVR_DATA_PRESERVED, end of conversion  */
    /*       flags clear induces the release of the preserved data.           */
    /*       Therefore, if the preserved data value is needed, it must be     */
    /*       read preliminarily into HAL_ADC_ConvCpltCallback().              */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS) );
  }
  
  
  /* ========== Check End of Conversion flag for injected group ========== */
  if( (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOC) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_JEOC)) ||   
      (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOS) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_JEOS))   )
  {
    /* Update state machine on conversion status if not in error state */
    if(hadc->State != HAL_ADC_STATE_ERROR)
    {
      /* Check if a regular conversion is ready */
      if(hadc->State == HAL_ADC_STATE_EOC_REG)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_INJ_REG;
      }
      else
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_INJ;
      }
    }
    
    /* Disable interruption if no further conversion upcoming by injected     */
    /* external trigger or by automatic injected conversion with regular      */
    /* group having no further conversion upcoming (same conditions as        */
    /* regular group interruption disabling above),                           */
    /* and if injected scan sequence is completed.                            */
    if(__HAL_ADC_IS_SOFTWARE_START_INJECTED(hadc)               || 
       (HAL_IS_BIT_CLR(hadc->Instance->CFGR, ADC_CFGR_JAUTO) &&    
       (__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc) &&               
        (hadc->Init.ContinuousConvMode == DISABLE)  )          )  )
    {
      /* If End of Sequence is reached, disable interrupts */
      if( __HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOS))
      {
        /* Allowed to modify bits ADC_IT_JEOC/ADC_IT_JEOS only if bit         */
        /* JADSTART==0 (no conversion on going)                               */
        if (__HAL_ADC_IS_CONVERSION_ONGOING_INJECTED(hadc) == RESET)
        {
          /* Disable ADC end of sequence conversion interrupt  */
          __HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOC | ADC_IT_JEOS);
        }
        else
        {
          /* Change ADC state to error state */
          hadc->State = HAL_ADC_STATE_ERROR;
          
          /* Set ADC error code to ADC IP internal error */
          hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
        }
      }
    }
    
    /* Conversion complete callback */
    /* Note: into callback, to determine if conversion has been triggered     */
    /*       from JEOC or JEOS, possibility to use:                           */
    /*        " if( __HAL_ADC_GET_FLAG(&hadc, ADC_FLAG_JEOS)) "               */
    HAL_ADCEx_InjectedConvCpltCallback(hadc);
    
    /* Clear injected group conversion flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC | ADC_FLAG_JEOS);
  }
  
   
  /* ========== Check Analog watchdog flags ========== */
  if( (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD1) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_AWD1)) || 
      (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD2) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_AWD2)) || 
      (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD3) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_AWD3))   )
  {
    
    if (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD1) != RESET)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_AWD;

      /* Clear ADC Analog watchdog flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD1);
    }
    else if (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD2) != RESET)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_AWD2;

      /* Clear ADC Analog watchdog flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD2);
    }
    else if (__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD3) != RESET)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_AWD3;

      /* Clear ADC Analog watchdog flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD3);
    }
    else
    {
      /* Change ADC state to error state */
      hadc->State = HAL_ADC_STATE_ERROR;
    }
    
    /* Level out of window callback */ 
    /* Note: In case of several analog watchdog enabled, if needed to know    */
    /* which one triggered and on which ADCx, either:                         */
    /* Test Analog Watchdog flags ADC_FLAG_AWD1/2/3 into function             */
    /* HAL_ADC_LevelOutOfWindowCallback().                                    */
    /* For example: "if (__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_AWD1) != RESET)" */
    /*              "if (__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_AWD2) != RESET)" */
    /*              "if (__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_AWD3) != RESET)" */
    /* Test ADC state of Analog Watchdog flags HAL_ADC_STATE_AWD/2/3 into     */
    /* HAL_ADC_LevelOutOfWindowCallback().                                    */
    /* For example: "if (HAL_ADC_GetState(&hadc1) == HAL_ADC_STATE_AWD) "     */
    /*              "if (HAL_ADC_GetState(&hadc1) == HAL_ADC_STATE_AWD2)"     */
    /*              "if (HAL_ADC_GetState(&hadc1) == HAL_ADC_STATE_AWD3)"     */
    HAL_ADC_LevelOutOfWindowCallback(hadc);
  }
  
  
  /* ========== Check Overrun flag ========== */
  if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_OVR) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_OVR))
  {
    /* If overrun is set to overwrite previous data (default setting),        */
    /* overrun event is not considered as an error.                           */
    /* (cf ref manual "Managing conversions without using the DMA and without */
    /* overrun ")                                                             */
    /* Exception for usage with DMA overrun event always considered as an     */
    /* error.                                                                 */
    if ((hadc->Init.Overrun == OVR_DATA_PRESERVED)          ||
        HAL_IS_BIT_SET(hadc->Instance->CFGR, ADC_CFGR_DMAEN)  )
    {
      /* Change ADC state to error state */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Set ADC error code to overrun */
      hadc->ErrorCode |= HAL_ADC_ERROR_OVR;
      
      /* Error callback */ 
      HAL_ADC_ErrorCallback(hadc);
    }

    /* Clear the Overrun flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_OVR);

  }
  
  
  /* ========== Check Injected context queue overflow flag ========== */
  if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JQOVF) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_JQOVF))
  {
    /* Change ADC state to overrun state */
    hadc->State = HAL_ADC_STATE_ERROR;
        
    /* Set ADC error code to Injected context queue overflow */
    hadc->ErrorCode |= HAL_ADC_ERROR_JQOVF;
    
    /* Clear the Injected context queue overflow flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JQOVF);
    
    /* Error callback */ 
    HAL_ADCEx_InjectedQueueOverflowCallback(hadc);
  }
  
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Handles ADC interrupt request  
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_ADC_REGULAR_NB_CONV(hadc->Init.NbrOfConversion));
  
  
  /* ========== Check End of Conversion flag for regular group ========== */
  if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOC) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_EOC))
  {
    /* Check if an injected conversion is ready */
    if(hadc->State == HAL_ADC_STATE_EOC_INJ)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_EOC_REG;
    }
    
    /* Disable interruption if no further conversion upcoming regular         */
    /* external trigger or by continuous mode                                 */
    if(__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc) && 
       (hadc->Init.ContinuousConvMode == DISABLE)  )
    {
      /* Disable ADC end of single conversion interrupt  */
      __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC);
    }

    /* Conversion complete callback */
    HAL_ADC_ConvCpltCallback(hadc);
    
    /* Clear regular group conversion flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_STRT | ADC_FLAG_EOC);
  }
  

  /* ========== Check End of Conversion flag for injected group ========== */
  if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOC) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_JEOC))
  {
    /* Check if a regular conversion is ready */
    if(hadc->State == HAL_ADC_STATE_EOC_REG)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_EOC_INJ;
    }

    /* Disable interruption if no further conversion upcoming injected        */
    /* external trigger or by automatic injected conversion with regular      */
    /* group having no further conversion upcoming (same conditions as        */
    /* regular group interruption disabling above).                           */
    if(__HAL_ADC_IS_SOFTWARE_START_INJECTED(hadc)              || 
       (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO) &&     
       (__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc) &&              
        (hadc->Init.ContinuousConvMode == DISABLE)  )         )  )
    {
      /* Disable ADC end of single conversion interrupt  */
      __HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOC);
    }

    /* Conversion complete callback */ 
    HAL_ADCEx_InjectedConvCpltCallback(hadc);
    
    /* Clear injected group conversion flag (and regular conversion flag raised simultaneously) */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_JSTRT | ADC_FLAG_JEOC | ADC_FLAG_EOC));
  }
  
   
  /* ========== Check Analog watchdog flags ========== */
  if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_AWD))
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD;
      
    /* Clear the ADCx's Analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc,ADC_FLAG_AWD);
    
    /* Level out of window callback */ 
    HAL_ADC_LevelOutOfWindowCallback(hadc);
  }
  
}
#endif /* STM32F373xC || STM32F378xx */


#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Perform an ADC automatic self-calibration
  *         Calibration prerequisite: ADC must be disabled (execute this
  *         function before HAL_ADC_Start() or after HAL_ADC_Stop() ).
  * @param  hadc: ADC handle
  * @param  SingleDiff: Selection of single-ended or differential input
  *          This parameter can be one of the following values:
  *            @arg ADC_SINGLE_ENDED: Channel in mode input single ended
  *            @arg ADC_DIFFERENTIAL_ENDED: Channel in mode input differential ended
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc, uint32_t SingleDiff)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  uint32_t tickstart;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(SingleDiff));

  /* Process locked */
  __HAL_LOCK(hadc);
   
  /* Calibration prerequisite: ADC must be disabled.                          */
   
  /* Disable the ADC (if not already disabled) */
  tmpHALStatus = ADC_Disable(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_READY;
    
    /* Select calibration mode single ended or differential ended */
    hadc->Instance->CR &= (~ADC_CR_ADCALDIF);
    if (SingleDiff == ADC_DIFFERENTIAL_ENDED)
    {
      hadc->Instance->CR |= ADC_CR_ADCALDIF;
    }

    /* Start ADC calibration */
    hadc->Instance->CR |= ADC_CR_ADCAL;

    tickstart = HAL_GetTick();  

    /* Wait for calibration completion */
    while(HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADCAL))
    {
      if((HAL_GetTick()-tickstart) > ADC_CALIBRATION_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
  }
  else
  {
    /* Update ADC state machine to error */
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Perform an ADC automatic self-calibration
  *         Calibration prerequisite: ADC must be disabled (execute this
  *         function before HAL_ADC_Start() or after HAL_ADC_Stop() ).
  *         During calibration process, ADC is enabled. ADC is let enabled at
  *         the completion of this function.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  uint32_t WaitLoopIndex = 0;
  uint32_t tickstart;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* 1. Calibration prerequisite:                                             */
  /*    - ADC must be disabled for at least two ADC clock cycles in disable   */
  /*      mode before ADC enable                                              */
  /* Stop potential conversion on going, on regular and injected groups       */
  /* Disable ADC peripheral */
  tmpHALStatus = ADC_ConversionStop_Disable(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmpHALStatus != HAL_ERROR)
  {

    /* Wait two ADC clock cycles */
    while(WaitLoopIndex < ADC_CYCLE_WORST_CASE_CPU_CYCLES *2)
    {
      WaitLoopIndex++;
    }
    
    /* 2. Enable the ADC peripheral */
    ADC_Enable(hadc);
    

    /* 3. Resets ADC calibration registers */  
    hadc->Instance->CR2 |= ADC_CR2_RSTCAL;
    
    tickstart = HAL_GetTick();  

    /* Wait for calibration reset completion */
    while(HAL_IS_BIT_SET(hadc->Instance->CR2, ADC_CR2_RSTCAL))
    {
      if((HAL_GetTick()-tickstart) > ADC_CALIBRATION_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
    
    
    /* 4. Start ADC calibration */
    hadc->Instance->CR2 |= ADC_CR2_CAL;

    tickstart = HAL_GetTick();  

    /* Wait for calibration completion */
    while(HAL_IS_BIT_SET(hadc->Instance->CR2, ADC_CR2_CAL))
    {
      if((HAL_GetTick()-tickstart) > ADC_CALIBRATION_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
    
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Get the calibration factor from automatic conversion result
  * @param  hadc: ADC handle
  * @param  SingleDiff: Selection of single-ended or differential input
  *          This parameter can be one of the following values:
  *            @arg ADC_SINGLE_ENDED: Channel in mode input single ended
  *            @arg ADC_DIFFERENTIAL_ENDED: Channel in mode input differential ended
  * @retval Converted value
  */
uint32_t HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef* hadc, uint32_t SingleDiff)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(SingleDiff)); 
  
  /* Return the selected ADC calibration value */ 
  if (SingleDiff == ADC_DIFFERENTIAL_ENDED)
  {
    return __HAL_ADC_CALFACT_DIFF_GET(hadc->Instance->CALFACT);
  }
  else
  {
    return ((hadc->Instance->CALFACT) & 0x0000007F);
  }
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Set the calibration factor to overwrite automatic conversion result. ADC must be enabled and no conversion on going.
  * @param  hadc: ADC handle
  * @param  SingleDiff: Selection of single-ended or differential input
  *          This parameter can be one of the following values:
  *            @arg ADC_SINGLE_ENDED: Channel in mode input single ended
  *            @arg ADC_DIFFERENTIAL_ENDED: Channel in mode input differential ended
  * @param  CalibrationFactor: Calibration factor (coded on 7 bits maximum)
  * @retval HAL state
  */
HAL_StatusTypeDef HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef* hadc, uint32_t SingleDiff, uint32_t CalibrationFactor)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(SingleDiff)); 
  assert_param(IS_ADC_CALFACT(CalibrationFactor)); 
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Verification of hardware constraints before modifying the calibration    */
  /* factors register: ADC must be enabled, no conversion on going.           */
  if ( (__HAL_ADC_IS_ENABLED(hadc) != RESET)                            &&
       (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(hadc) == RESET)  )
  {
    /* Set the selected ADC calibration value */ 
    if (SingleDiff == ADC_DIFFERENTIAL_ENDED)
    {
      hadc->Instance->CALFACT &= ~ADC_CALFACT_CALFACT_D;
      hadc->Instance->CALFACT |= __HAL_ADC_CALFACT_DIFF_SET(CalibrationFactor);
    }
    else
    {
      hadc->Instance->CALFACT &= ~ADC_CALFACT_CALFACT_S;
      hadc->Instance->CALFACT |= CalibrationFactor;
    }
  }
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    /* Update ADC state machine to error */
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Enables ADC, starts conversion of injected group.
  *         Interruptions enabled in this function: None.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function must be called for ADC slave first, then ADC master. 
  *         For ADC slave, ADC is enabled only (conversion is not started).  
  *         For ADC master, ADC is enabled and multimode conversion is started.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Check if a regular conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_REG)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ;
    }
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_JEOC | ADC_FLAG_JEOS));
    
    /* Enable conversion of injected group, if automatic injected conversion  */
    /* is disabled.                                                           */
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* Case of multimode enabled (for devices with several ADCs): if ADC is   */
    /* slave, ADC is enabled only (conversion is not started). If ADC is      */
    /* master, ADC is enabled and conversion is started.                      */
    if ( 
        HAL_IS_BIT_CLR(hadc->Instance->CFGR, ADC_CFGR_JAUTO)  && 
        __HAL_ADC_NONMULTIMODE_OR_MULTIMODEMASTER(hadc)         )
    {
      hadc->Instance->CR |= ADC_CR_JADSTART;
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Enables ADC, starts conversion of injected group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Check if a regular conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_REG)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ;
    }
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);
    
    /* Start conversion of injected group if software start has been selected */
    /* and if automatic injected conversion is disabled.                      */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* If automatic injected conversion is enabled, conversion will start     */
    /* after next regular group conversion.                                   */
    if (__HAL_ADC_IS_SOFTWARE_START_INJECTED(hadc)        && 
        HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO)  )
    {
      /* Enable ADC software conversion for injected channels */
      hadc->Instance->CR2 |= ADC_CR2_JSWSTART;
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Stop conversion of injected channels. Disable ADC peripheral if
  *         no regular conversion is on going.
  * @note   If ADC must be disabled with this function and if regular conversion
  *         is on going, function HAL_ADC_Stop must be used preliminarily.
  * @note   In case of auto-injection mode, HAL_ADC_Stop must be used.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function must be called for ADC master first, then ADC slave.
  *         For ADC master, conversion is stopped and ADC is disabled. 
  *         For ADC slave, ADC is disabled only (conversion stop of ADC master
  *         has already stopped conversion of ADC slave).
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc)
{  
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion on going on injected group only. */
  tmpHALStatus = ADC_ConversionStop(hadc, INJECTED_GROUP);
  
  /* Disable ADC peripheral if injected conversions are effectively stopped   */
  /* and if no conversion on the other group (regular group) is intended to   */
  /* continue.                                                                */
  if (tmpHALStatus != HAL_ERROR)
  {
    if((__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET) &&
       (hadc->State != HAL_ADC_STATE_BUSY_REG)                  &&
       (hadc->State != HAL_ADC_STATE_BUSY_INJ_REG)                )
    {
      /* 2. Disable the ADC peripheral */
      tmpHALStatus = ADC_Disable(hadc);
      
      /* Check if ADC is effectively disabled */
      if (tmpHALStatus != HAL_ERROR)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_READY;
      }
    }
    /* Conversion on injected group is stopped, but ADC not disabled since    */
    /* conversion on regular group is still running.                          */
    else
    {
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Stop conversion of injected channels. Disable ADC peripheral if
  *         no regular conversion is on going.
  * @note   If ADC must be disabled with this function and if regular conversion
  *         is on going, function HAL_ADC_Stop must be used preliminarily.
  * @note   In case of auto-injection mode, HAL_ADC_Stop must be used.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Stop potential conversion and disable ADC peripheral                     */
  /* Conditioned to:                                                          */
  /* - No conversion on the other group (regular group) is intended to        */
  /*   continue (injected and regular groups stop conversion and ADC disable  */
  /*   are common)                                                            */
  /* - In case of auto-injection mode, HAL_ADC_Stop must be used.             */
    if((hadc->State != HAL_ADC_STATE_BUSY_REG)            &&
       (hadc->State != HAL_ADC_STATE_BUSY_INJ_REG)        &&
       HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO)   )
  {
    /* Stop potential conversion on going, on regular and injected groups */
    /* Disable ADC peripheral */
    tmpHALStatus = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
      
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Wait for injected group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t tmp_Flag_EOC;
 
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* If end of conversion selected to end of sequence */
  if (hadc->Init.EOCSelection == EOC_SEQ_CONV)
  {
    tmp_Flag_EOC = ADC_FLAG_JEOS;
  }
  /* If end of conversion selected to end of each conversion */
  else /* EOC_SINGLE_CONV */
  {
    tmp_Flag_EOC = (ADC_FLAG_JEOC | ADC_FLAG_JEOS);
  }

  /* Get timeout */
  tickstart = HAL_GetTick();  
     
  /* Wait until End of Conversion flag is raised */
  while(HAL_IS_BIT_CLR(hadc->Instance->ISR, tmp_Flag_EOC))
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
      {
        /* Update ADC state machine to timeout */
        hadc->State = HAL_ADC_STATE_TIMEOUT;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
  }
  
  /* Clear end of conversion flag of injected group if low power feature      */
  /* "Auto Wait" is disabled, to not interfere with this feature until data   */
  /* register is read using function HAL_ADC_GetValue().                      */
  if (hadc->Init.LowPowerAutoWait == DISABLE)
  {
    /* Clear injected group conversion flag */
    __HAL_ADC_CLEAR_FLAG(hadc,(ADC_FLAG_JEOC | ADC_FLAG_JEOS));
  }
  

  /* Update ADC state machine */
  if(hadc->State != HAL_ADC_STATE_EOC_INJ_REG)
  {
    /* Check if a conversion is ready on regular group */
    if(hadc->State == HAL_ADC_STATE_EOC_REG)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_EOC_INJ;
    }
  }
    
  /* Return ADC state */
  return HAL_OK;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Wait for injected group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Variables for polling in case of scan mode enabled */
  uint32_t Conversion_Timeout_CPU_cycles_max =0;
  uint32_t Conversion_Timeout_CPU_cycles =0;
 
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Get timeout */
  tickstart = HAL_GetTick();  
     
  /* Polling for end of conversion: differentiation if single/sequence        */
  /* conversion.                                                              */
  /* For injected group, flag JEOC is set only at the end of the sequence,    */
  /* not for each conversion within the sequence.                             */
  /*  - If single conversion for injected group (scan mode disabled or        */
  /*    InjectedNbrOfConversion ==1), flag jEOC is used to determine the      */
  /*    conversion completion.                                                */
  /*  - If sequence conversion for injected group (scan mode enabled and      */
  /*    InjectedNbrOfConversion >=2), flag JEOC is set only at the end of the */
  /*    sequence.                                                             */
  /*    To poll for each conversion, the maximum conversion time is computed  */
  /*    from ADC conversion time (selected sampling time + conversion time of */
  /*    12.5 ADC clock cycles) and APB2/ADC clock prescalers (depending on    */
  /*    settings, conversion time range can be from 28 to 32256 CPU cycles).  */
  if ((hadc->Instance->JSQR & ADC_JSQR_JL) == RESET)
  {
    /* Wait until End of Conversion flag is raised */
    while(HAL_IS_BIT_CLR(hadc->Instance->SR, ADC_FLAG_JEOC))
    {
      /* Check if timeout is disabled (set to infinite wait) */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Update ADC state machine to timeout */
          hadc->State = HAL_ADC_STATE_TIMEOUT;
          
          /* Process unlocked */
          __HAL_UNLOCK(hadc);
          
          return HAL_ERROR;
        }
      }
    }
  }
  else
  {
    /* Calculation of CPU cycles corresponding to ADC conversion cycles.      */
    /* Retrieve ADC clock prescaler and ADC maximum conversion cycles on all  */
    /* channels.                                                              */
    Conversion_Timeout_CPU_cycles_max = __HAL_ADC_CLOCK_PRECSALER_RANGE() ;
    Conversion_Timeout_CPU_cycles_max *= __HAL_ADC_CONVCYCLES_MAX_RANGE(hadc);

    /* Maximum conversion cycles taking in account offset of 34 CPU cycles:   */
    /* number of CPU cycles for processing of conversion cycles estimation.   */
    Conversion_Timeout_CPU_cycles = 34;
    
    /* Poll with maximum conversion time */
    while(Conversion_Timeout_CPU_cycles < Conversion_Timeout_CPU_cycles_max)
    {
      /* Check if timeout is disabled (set to infinite wait) */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Update ADC state machine to timeout */
          hadc->State = HAL_ADC_STATE_TIMEOUT;
          
          /* Process unlocked */
          __HAL_UNLOCK(hadc);
          
          return HAL_ERROR;
        }
      }
      Conversion_Timeout_CPU_cycles ++;
    }
  }
  
      
  /* Clear injected group conversion flag (and regular conversion flag raised simultaneously) */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JSTRT | ADC_FLAG_JEOC | ADC_FLAG_EOC);
  
  /* Check if a regular conversion is ready */
  if(hadc->State == HAL_ADC_STATE_EOC_REG)
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
  }
  else
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_EOC_INJ;
  }
  
  /* Return ADC state */
  return HAL_OK;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Enables ADC, starts conversion of injected group with interruption.
  *         Interruptions enabled in this function: JEOC (end of conversion).
  *         Each of these interruptions has its dedicated callback function.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function must be called for ADC slave first, then ADC master. 
  *         For ADC slave, ADC is enabled only (conversion is not started).  
  *         For ADC master, ADC is enabled and multimode conversion is started.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Check if a regular conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_REG)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ;
    }
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
  
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_JEOC | ADC_FLAG_JEOS));
    
    /* Enable ADC Injected context queue overflow interrupt if this feature   */
    /* is enabled.                                                            */
    if ((hadc->Instance->CFGR & ADC_CFGR_JQM) != RESET)
    {
      __HAL_ADC_ENABLE_IT(hadc, ADC_FLAG_JQOVF);
    }
    
    /* Enable ADC end of conversion interrupt */
    switch(hadc->Init.EOCSelection)
    {
      case EOC_SEQ_CONV: 
        __HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOC);
        __HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOS);
        break;
      /* case EOC_SINGLE_CONV */
      default:
        __HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOC | ADC_IT_JEOS);
        break;
    }
    
    /* Enable conversion of injected group, if automatic injected conversion  */
    /* is disabled.                                                           */
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* Case of multimode enabled (for devices with several ADCs): if ADC is   */
    /* slave, ADC is enabled only (conversion is not started). If ADC is      */
    /* master, ADC is enabled and conversion is started.                      */
    if ( 
        HAL_IS_BIT_CLR(hadc->Instance->CFGR, ADC_CFGR_JAUTO)  && 
        __HAL_ADC_NONMULTIMODE_OR_MULTIMODEMASTER(hadc)         )
    {
      hadc->Instance->CR |= ADC_CR_JADSTART;
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Enables ADC, starts conversion of injected group with interruption.
  *         Interruptions enabled in this function: JEOC (end of conversion),
  *         overrun (if available).
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmpHALStatus = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Check if a regular conversion is ongoing */
    if(hadc->State == HAL_ADC_STATE_BUSY_REG)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;  
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ;
    }
    
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);
    
    /* Enable end of conversion interrupt for injected channels */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOC);

    /* Start conversion of injected group if software start has been selected */
    /* and if automatic injected conversion is disabled.                      */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* If automatic injected conversion is enabled, conversion will start     */
    /* after next regular group conversion.                                   */
    if (__HAL_ADC_IS_SOFTWARE_START_INJECTED(hadc)        && 
        HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO)  )
    {
      /* Enable ADC software conversion for injected channels */
      hadc->Instance->CR2 |= ADC_CR2_JSWSTART;
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Stop conversion of injected channels, disable interruption of 
  *         end-of-conversion. Disable ADC peripheral if no regular conversion
  *         is on going.
  * @note   If ADC must be disabled with this function and if regular conversion
  *         is on going, function HAL_ADC_Stop must be used preliminarily.
  * @note:  Case of multimode enabled (for devices with several ADCs): This 
  *         function must be called for ADC master first, then ADC slave.
  *         For ADC master, conversion is stopped and ADC is disabled. 
  *         For ADC slave, ADC is disabled only (conversion stop of ADC master
  *         has already stopped conversion of ADC slave).
  * @note   In case of auto-injection mode, HAL_ADC_Stop must be used.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc)
{ 
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* 1. Stop potential conversion on going on injected group only. */
  tmpHALStatus = ADC_ConversionStop(hadc, INJECTED_GROUP);
  
  /* Disable ADC peripheral if injected conversions are effectively stopped   */
  /* and if no conversion on the other group (regular group) is intended to   */
  /* continue.                                                                */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Disable ADC end of conversion interrupt for injected channels */
    __HAL_ADC_DISABLE_IT(hadc, (ADC_IT_JEOC | ADC_IT_JEOS));
    
    if((__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET) &&
       (hadc->State != HAL_ADC_STATE_BUSY_REG)                  &&
       (hadc->State != HAL_ADC_STATE_BUSY_INJ_REG)                )
    {
      /* 2. Disable the ADC peripheral */
      tmpHALStatus = ADC_Disable(hadc);
      
      /* Check if ADC is effectively disabled */
      if (tmpHALStatus != HAL_ERROR)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_READY;
      }
    }
    /* Conversion on injected group is stopped, but ADC not disabled since    */
    /* conversion on regular group is still running.                          */
    else
    {
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Stop conversion of injected channels, disable interruption of 
  *         end-of-conversion. Disable ADC peripheral if no regular conversion
  *         is on going.
  * @note   If ADC must be disabled with this function and if regular conversion
  *         is on going, function HAL_ADC_Stop must be used preliminarily.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Stop potential conversion and disable ADC peripheral                     */
  /* Conditioned to:                                                          */
  /* - No conversion on the other group (regular group) is intended to        */
  /*   continue (injected and regular groups stop conversion and ADC disable  */
  /*   are common)                                                            */
  /* - In case of auto-injection mode, HAL_ADC_Stop must be used.             */ 
    if((hadc->State != HAL_ADC_STATE_BUSY_REG)            &&
       (hadc->State != HAL_ADC_STATE_BUSY_INJ_REG)        &&
       HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO)   )
  {
    /* Stop potential conversion on going, on regular and injected groups */
    /* Disable ADC peripheral */
    tmpHALStatus = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Disable ADC end of conversion interrupt for injected channels */
      __HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOC);
      
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
      
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
/**
  * @brief  Enables ADC, starts conversion of regular group and transfers result
  *         through DMA.
  *         Multimode must have been previously configured using 
  *         HAL_ADCEx_MultiModeConfigChannel() function.
  *         Interruptions enabled in this function:
  *         overrun, DMA half transfer, DMA transfer complete. 
  *         Each of these interruptions has its dedicated callback function.
  * @note:  ADC slave can be enabled preliminarily using single-mode  
  *         HAL_ADC_Start() function.
  * @param  hadc: ADC handle of ADC master (handle of ADC slave must not be used)
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  ADC_HandleTypeDef tmphadcSlave;
  ADC_Common_TypeDef *tmpADC_Common;

  /* Check the parameters */
  assert_param(IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_ADC_EXTTRIG_EDGE(hadc->Init.ExternalTrigConvEdge));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DMAContinuousRequests));
  
  /* Process locked */
  __HAL_LOCK(hadc);

  /* Set a temporary handle of the ADC slave associated to the ADC master     */
  /* (Depending on STM32F3 product, there may be up to 2 ADC slaves)          */
  __HAL_ADC_MULTI_SLAVE(hadc, &tmphadcSlave);
  
  if (tmphadcSlave.Instance == HAL_NULL)
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    
    return HAL_ERROR;
  }
    
  
  /* Enable the ADC peripherals: master and slave (in case if not already     */
  /* enabled previously)                                                      */
  tmpHALStatus = ADC_Enable(hadc);
  if (tmpHALStatus != HAL_ERROR)
  {
    tmpHALStatus = ADC_Enable(&tmphadcSlave);
  }
  
  /* Start conversion all ADCs of multimode are effectively enabled */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* State machine update (ADC master): Check if an injected conversion is  */
    /* ongoing.                                                               */
    if(hadc->State == HAL_ADC_STATE_BUSY_INJ)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_INJ_REG;
    }
    else
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
    }
      
    /* Set ADC error code to none */
    __HAL_ADC_CLEAR_ERRORCODE(hadc);
    
    
    /* Set the DMA transfer complete callback */
    hadc->DMA_Handle->XferCpltCallback = ADC_DMAConvCplt;
       
    /* Set the DMA half transfer complete callback */
    hadc->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;
    
    /* Set the DMA error callback */
    hadc->DMA_Handle->XferErrorCallback = ADC_DMAError ;
    
    /* Pointer to the common control register to which is belonging hadc      */
    /* (Depending on STM32F3 product, there may be up to 4 ADC and 2 common   */
    /* control registers)                                                     */
    tmpADC_Common = __HAL_ADC_COMMON_REGISTER(hadc);
    
    
    /* Manage ADC and DMA start: ADC overrun interruption, DMA start, ADC     */
    /* start (in case of SW start):                                           */

    /* Clear regular group conversion flag and overrun flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS | ADC_FLAG_OVR));
    
    /* Enable ADC overrun interrupt */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_OVR);

    /* Start the DMA channel */
    HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&tmpADC_Common->CDR, (uint32_t)pData, Length);
        
    /* Enable conversion of regular group.                                    */
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    hadc->Instance->CR |= ADC_CR_ADSTART;

  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected channels in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @note   Multimode is kept enabled after this function. To disable multimode 
  *         (set with HAL_ADCEx_MultiModeConfigChannel(), ADC must be 
  *         reinitialized using HAL_ADC_Init() or HAL_ADC_ReInit().
  * @note   In case of DMA configured in circular mode, function 
  *         HAL_ADC_Stop_DMA must be called after this function with handle of
  *         ADC slave, to properly disable the DMA channel.
  * @param  hadc: ADC handle of ADC master (handle of ADC slave must not be used)
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  uint32_t tickstart;
  ADC_HandleTypeDef tmphadcSlave;
  ADC_Common_TypeDef *tmpADC_Common;
  
  /* Check the parameters */
  assert_param(IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
 
  /* 1. Stop potential multimode conversion on going, on regular and injected groups */
  tmpHALStatus = ADC_ConversionStop(hadc, REGULAR_INJECTED_GROUP);

  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Set a temporary handle of the ADC slave associated to the ADC master   */
    /* (Depending on STM32F3 product, there may be up to 2 ADC slaves)        */
    __HAL_ADC_MULTI_SLAVE(hadc, &tmphadcSlave);
    
    if (tmphadcSlave.Instance == HAL_NULL)
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Process unlocked */
      __HAL_UNLOCK(hadc);
      
      return HAL_ERROR;
    }
    
    /* Procedure to disable the ADC peripheral: wait for conversions          */
    /* effectively stopped (ADC master and ADC slave), then disable ADC       */
    
    /* 1. Wait until ADSTP=0 for ADC master and ADC slave*/
    tickstart = HAL_GetTick();  

    while(__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc)          || 
          __HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(&tmphadcSlave)   )
    {
      if((HAL_GetTick()-tickstart) > ADC_STOP_CONVERSION_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
    
    
    /* Pointer to the common control register to which is belonging hadc      */
    /* (Depending on STM32F3 product, there may be up to 4 ADC and 2 common   */
    /* control registers)                                                     */
    tmpADC_Common = __HAL_ADC_COMMON_REGISTER(hadc);
    
    /* Reset configuration of ADC DMA continuous request for dual mode */
    tmpADC_Common->CCR &= ~ADC_CCR_DMACFG;
    
    /* Disable the DMA channel (in case of DMA in circular mode or stop while  */
    /* while DMA transfer is on going)                                        */
    /* Note: DMA channel of ADC slave should stopped after this function with  */
    /*       function HAL_ADC_Stop_DMA.                                       */
    tmpHALStatus = HAL_DMA_Abort(hadc->DMA_Handle);
    
    /* Check if DMA channel effectively disabled */
    if (tmpHALStatus != HAL_OK)
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;      
    }
    
    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IT_OVR);
    
    
    
    /* 2. Disable the ADC peripherals: master and slave */
    /* Update "tmpHALStatus" only if DMA channel disabling passed, to keep in  */
    /* memory a potential failing status.                                     */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Check if ADC are effectively disabled */
      if ((ADC_Disable(hadc) != HAL_ERROR)         &&
          (ADC_Disable(&tmphadcSlave) != HAL_ERROR)   )
      {
        tmpHALStatus = HAL_OK;
        
        /* Change ADC state (ADC master) */
        hadc->State = HAL_ADC_STATE_READY;
      }
    }
    else
    {
      ADC_Disable(hadc);
      ADC_Disable(&tmphadcSlave);
    }
    
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Returns the last ADC Master&Slave regular conversions results data
  *         in the selected multi mode.
  * @param  hadc: ADC handle of ADC master (handle of ADC slave must not be used)
  * @retval The converted data value.
  */
uint32_t HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef* hadc)
{
  ADC_Common_TypeDef *tmpADC_Common;
  
  /* Check the parameters */
  assert_param(IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance));
  
  /* Pointer to the common control register to which is belonging hadc        */
  /* (Depending on STM32F3 product, there may be up to 4 ADC and 2 common     */
  /* control registers)                                                       */
  tmpADC_Common = __HAL_ADC_COMMON_REGISTER(hadc);
  
  /* Return the multi mode conversion value */
  return tmpADC_Common->CDR;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx    */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Get ADC injected group conversion result.
  * @param  hadc: ADC handle
  * @param  InjectedRank: the converted ADC injected rank.
  *          This parameter can be one of the following values:
  *            @arg ADC_INJECTED_RANK_1: Injected Channel1 selected
  *            @arg ADC_INJECTED_RANK_2: Injected Channel2 selected
  *            @arg ADC_INJECTED_RANK_3: Injected Channel3 selected
  *            @arg ADC_INJECTED_RANK_4: Injected Channel4 selected
  * @retval None
  */
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank)
{
  uint32_t tmp_jdr = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_INJECTED_RANK(InjectedRank));
  
  /* Clear injected group conversion flag to have similar behaviour as        */
  /* regular group: reading data register also clears end of conversion flag, */
  /* and in case of usage of ADC feature "LowPowerAutoWait".                  */
  __HAL_ADC_CLEAR_FLAG(hadc,(ADC_FLAG_JEOC | ADC_FLAG_JEOS));
  
  /* Get ADC converted value */ 
  switch(InjectedRank)
  {  
    case ADC_INJECTED_RANK_4: 
      tmp_jdr = hadc->Instance->JDR4;
      break;
    case ADC_INJECTED_RANK_3: 
      tmp_jdr = hadc->Instance->JDR3;
      break;
    case ADC_INJECTED_RANK_2: 
      tmp_jdr = hadc->Instance->JDR2;
      break;
    case ADC_INJECTED_RANK_1:
    default:
      tmp_jdr = hadc->Instance->JDR1;
      break;
  }
  
  /* Return ADC converted value */ 
  return tmp_jdr;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Get ADC injected group conversion result.
  * @param  hadc: ADC handle
  * @param  InjectedRank: the converted ADC injected rank.
  *          This parameter can be one of the following values:
  *            @arg ADC_INJECTED_RANK_1: Injected Channel1 selected
  *            @arg ADC_INJECTED_RANK_2: Injected Channel2 selected
  *            @arg ADC_INJECTED_RANK_3: Injected Channel3 selected
  *            @arg ADC_INJECTED_RANK_4: Injected Channel4 selected
  * @retval None
  */
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank)
{
  uint32_t tmp_jdr = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_INJECTED_RANK(InjectedRank));
  
  /* Clear injected group conversion flag to have similar behaviour as         */
  /* regular group: reading data register also clears end of conversion flag. */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);
  
  /* Get ADC converted value */ 
  switch(InjectedRank)
  {  
    case ADC_INJECTED_RANK_4: 
      tmp_jdr = hadc->Instance->JDR4;
      break;
    case ADC_INJECTED_RANK_3: 
      tmp_jdr = hadc->Instance->JDR3;
      break;
    case ADC_INJECTED_RANK_2: 
      tmp_jdr = hadc->Instance->JDR2;
      break;
    case ADC_INJECTED_RANK_1:
    default:
      tmp_jdr = hadc->Instance->JDR1;
      break;
  }
  
  /* Return ADC converted value */ 
  return tmp_jdr;
}
#endif /* STM32F373xC || STM32F378xx */

/**
  * @brief  Injected conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADCEx_InjectedConvCpltCallback could be implemented in the user file
  */
}

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Injected context queue overflow flag callback. 
  * @note:  This callback is called if injected context queue is enabled
            (parameter "QueueInjectedContext" in injected channel configuration)
            and if a new injected context is set when queue is full (maximum 2
            contexts).
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADCEx_InjectedQueueOverflowCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADCEx_InjectedQueueOverflowCallback must be implemented 
            in the user file.
  */
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

/**
  * @}
  */

/** @defgroup ADCEx_Exported_Functions_Group3 Extended Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim   
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels on regular group
      (+) Configure channels on injected group
      (+) Configure multimode
      (+) Configure the analog watchdog
      
@endverbatim
  * @{
  */


#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
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
  * @param  sConfig: Structure ADC channel for regular group.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  ADC_Common_TypeDef *tmpADC_Common;
  ADC_HandleTypeDef tmphadcSharingSameCommonRegister;
  uint32_t tmpOffsetShifted;
  uint32_t WaitLoopIndex = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_REGULAR_RANK(sConfig->Rank));
  assert_param(IS_ADC_SAMPLE_TIME(sConfig->SamplingTime));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(sConfig->SingleDiff));
  assert_param(IS_ADC_OFFSET_NUMBER(sConfig->OffsetNumber));
  assert_param(IS_ADC_RANGE(__HAL_ADC_GET_RESOLUTION(hadc), sConfig->Offset));
  
  
  /* Verification of channel number: Channels 1 to 14 are available in        */  
  /* differential mode. Channels 15, 16, 17, 18 can be used only in           */
  /* single-ended mode.                                                       */
  if (sConfig->SingleDiff != ADC_DIFFERENTIAL_ENDED)
  {
    assert_param(IS_ADC_CHANNEL(sConfig->Channel));
  }
  else
  {
    assert_param(IS_ADC_DIFF_CHANNEL(sConfig->Channel));
  }
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on regular group:                                    */
  /*  - Channel number                                                        */
  /*  - Channel rank                                                          */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)
  {
    /* Regular sequence configuration */
    /* For Rank 1 to 4 */
    if (sConfig->Rank < 5)
    {
      /* Clear the old SQx bits for the selected rank */
      hadc->Instance->SQR1 &= ~__HAL_ADC_SQR1_RK(ADC_SQR2_SQ5, sConfig->Rank);
      
      /* Set the SQx bits for the selected rank */
      hadc->Instance->SQR1 |= __HAL_ADC_SQR1_RK(sConfig->Channel, sConfig->Rank);
    }
    /* For Rank 5 to 9 */
    else if (sConfig->Rank < 10)
    {
      /* Clear the old SQx bits for the selected rank */
      hadc->Instance->SQR2 &= ~__HAL_ADC_SQR2_RK(ADC_SQR2_SQ5, sConfig->Rank);
      
      /* Set the SQx bits for the selected rank */
      hadc->Instance->SQR2 |= __HAL_ADC_SQR2_RK(sConfig->Channel, sConfig->Rank);
    }
    /* For Rank 10 to 14 */
    else if (sConfig->Rank < 15)
    {
      /* Clear the old SQx bits for the selected rank */
      hadc->Instance->SQR3 &= ~__HAL_ADC_SQR3_RK(ADC_SQR3_SQ10, sConfig->Rank);
      
      /* Set the SQx bits for the selected rank */
      hadc->Instance->SQR3 |= __HAL_ADC_SQR3_RK(sConfig->Channel, sConfig->Rank);
    }
    /* For Rank 15 to 16 */
    else
    {   
      /* Clear the old SQx bits for the selected rank */
      hadc->Instance->SQR4 &= ~__HAL_ADC_SQR4_RK(ADC_SQR4_SQ15, sConfig->Rank);
      
      /* Set the SQx bits for the selected rank */
      hadc->Instance->SQR4 |= __HAL_ADC_SQR4_RK(sConfig->Channel, sConfig->Rank);
    }
    
    
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on regular group:                                    */
  /*  - Channel sampling time                                                 */
  /*  - Channel offset                                                        */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(hadc) == RESET)
  {
    /* Channel sampling time configuration */
    /* For channels 10 to 18 */
    if (sConfig->Channel > ADC_CHANNEL_10)
    {
      /* Clear the old sample time */
      hadc->Instance->SMPR2 &= ~__HAL_ADC_SMPR2(ADC_SMPR1_SMP0, sConfig->Channel);
      
      /* Set the new sample time */
      hadc->Instance->SMPR2 |= __HAL_ADC_SMPR2(sConfig->SamplingTime, sConfig->Channel);
    }
    else /* For channels 0 to 9 */
    {
      /* Clear the old sample time */
      hadc->Instance->SMPR1 &= ~__HAL_ADC_SMPR1(ADC_SMPR2_SMP10, sConfig->Channel);
      
      /* Set the new sample time */
      hadc->Instance->SMPR1 |= __HAL_ADC_SMPR1(sConfig->SamplingTime, sConfig->Channel);
    }
    

    /* Configure the offset: offset enable/disable, channel, offset value */

    /* Shift the offset in function of the selected ADC resolution. */
    /* Offset has to be left-aligned on bit 11, the LSB (right bits) are set to 0 */
    tmpOffsetShifted = __HAL_ADC_OFFSET_SHIFT_RESOLUTION(hadc, sConfig->Offset);
    
    switch (sConfig->OffsetNumber)
    {
    case ADC_OFFSET_1:
      /* Configure offset register 1:                                         */
      /* - Enable offset                                                      */
      /* - Set channel number                                                 */
      /* - Set offset value                                                   */
      hadc->Instance->OFR1 &= ~( ADC_OFR1_OFFSET1_CH |
                                 ADC_OFR1_OFFSET1     );
      hadc->Instance->OFR1 |= ( ADC_OFR1_OFFSET1_EN                     |
                                __HAL_ADC_OFR_CHANNEL(sConfig->Channel) |
                                tmpOffsetShifted                         );
      break;
    
    case ADC_OFFSET_2:
      /* Configure offset register 2:                                         */
      /* - Enable offset                                                      */
      /* - Set channel number                                                 */
      /* - Set offset value                                                   */
      hadc->Instance->OFR2 &= ~( ADC_OFR2_OFFSET2_CH |
                                 ADC_OFR2_OFFSET2     );
      hadc->Instance->OFR2 |= ( ADC_OFR2_OFFSET2_EN                     |
                                __HAL_ADC_OFR_CHANNEL(sConfig->Channel) |
                                tmpOffsetShifted                         );
      break;
        
    case ADC_OFFSET_3:
      /* Configure offset register 3:                                         */
      /* - Enable offset                                                      */
      /* - Set channel number                                                 */
      /* - Set offset value                                                   */
      hadc->Instance->OFR3 &= ~( ADC_OFR3_OFFSET3_CH |
                                 ADC_OFR3_OFFSET3     );
      hadc->Instance->OFR3 |= ( ADC_OFR3_OFFSET3_EN                     |
                                __HAL_ADC_OFR_CHANNEL(sConfig->Channel) |
                                tmpOffsetShifted                         );
      break;
    
    case ADC_OFFSET_4:
      /* Configure offset register 1:                                         */
      /* - Enable offset                                                      */
      /* - Set channel number                                                 */
      /* - Set offset value                                                   */
      hadc->Instance->OFR4 &= ~( ADC_OFR4_OFFSET4_CH |
                                 ADC_OFR4_OFFSET4     );
      hadc->Instance->OFR4 |= ( ADC_OFR4_OFFSET4_EN                     |
                                __HAL_ADC_OFR_CHANNEL(sConfig->Channel) |
                                tmpOffsetShifted                         );
      break;
    
    /* Case ADC_OFFSET_NONE */
    default :
    /* Scan OFR1, OFR2, OFR3, OFR4 to check if the selected channel is enabled. If this is the case, offset OFRx is disabled. */
      if (((hadc->Instance->OFR1) & ADC_OFR1_OFFSET1_CH) == __HAL_ADC_OFR_CHANNEL(sConfig->Channel))
      {
        /* Disable offset OFR1*/
        hadc->Instance->OFR1 &= ~ADC_OFR1_OFFSET1_EN; 
      }
      if (((hadc->Instance->OFR2) & ADC_OFR2_OFFSET2_CH) == __HAL_ADC_OFR_CHANNEL(sConfig->Channel))
      {
        /* Disable offset OFR2*/
        hadc->Instance->OFR2 &= ~ADC_OFR2_OFFSET2_EN; 
      }
      if (((hadc->Instance->OFR3) & ADC_OFR3_OFFSET3_CH) == __HAL_ADC_OFR_CHANNEL(sConfig->Channel))
      {
        /* Disable offset OFR3*/
        hadc->Instance->OFR3 &= ~ADC_OFR3_OFFSET3_EN;
      }
      if (((hadc->Instance->OFR4) & ADC_OFR4_OFFSET4_CH) == __HAL_ADC_OFR_CHANNEL(sConfig->Channel))
      {
        /* Disable offset OFR4*/
        hadc->Instance->OFR4 &= ~ADC_OFR4_OFFSET4_EN;
      }
      break;
    }

  }
 

  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated only when ADC is disabled:                */
  /*  - Single or differential mode                                           */
  /*  - Internal measurement channels: Vbat/VrefInt/TempSensor                */
  if (__HAL_ADC_IS_ENABLED(hadc) == RESET)
  {
    /* Configuration of differential mode */
    if (sConfig->SingleDiff != ADC_DIFFERENTIAL_ENDED)
    {
      /* Disable differential mode (default mode: single-ended) */
      hadc->Instance->DIFSEL &= ~(__HAL_ADC_DIFSEL_CHANNEL(sConfig->Channel));
    }
    else
    {
      /* Enable differential mode */
      hadc->Instance->DIFSEL |= __HAL_ADC_DIFSEL_CHANNEL(sConfig->Channel);
      
      /* Sampling time configuration of channel ADC_IN+1 (negative input) */
      /* For channels 10 to 18 */
      if (sConfig->Channel > ADC_CHANNEL_10)
      {
        /* Clear the old sample time */
        hadc->Instance->SMPR2 &= ~__HAL_ADC_SMPR2(ADC_SMPR1_SMP0, (sConfig->Channel +1));
        
        /* Set the new sample time */
        hadc->Instance->SMPR2 |= __HAL_ADC_SMPR2(sConfig->SamplingTime, (sConfig->Channel +1));
      }
      else /* For channels 0 to 9 */
      {
        /* Clear the old sample time */
        hadc->Instance->SMPR1 &= ~__HAL_ADC_SMPR1(ADC_SMPR2_SMP10, (sConfig->Channel +1));
        
        /* Set the new sample time */
        hadc->Instance->SMPR1 |= __HAL_ADC_SMPR1(sConfig->SamplingTime, (sConfig->Channel +1));
      }
    }
  
    
  /* Management of internal measurement channels: Vbat/VrefInt/TempSensor     */
    /* internal measurement paths enable: If internal channel selected,       */
    /* enable dedicated internal buffers and path.                            */
    /* Note: these internal measurement paths can be disabled using           */
    /* HAL_ADC_DeInit().                                                      */
       
    /* Configuration of common ADC parameters                                 */
    /* Pointer to the common control register to which is belonging hadc      */
    /* (Depending on STM32F3 product, there may be up to 4 ADC and 2 common   */
    /* control registers)                                                     */
    tmpADC_Common = __HAL_ADC_COMMON_REGISTER(hadc);
  
    /* If the requested internal measurement path has already been enabled,   */
    /* bypass the configuration processing.                                   */
    if (( (sConfig->Channel == ADC_CHANNEL_TEMPSENSOR) &&
          (HAL_IS_BIT_CLR(tmpADC_Common->CCR, ADC_CCR_TSEN))            ) ||
        ( (sConfig->Channel == ADC_CHANNEL_VBAT)       &&
          (HAL_IS_BIT_CLR(tmpADC_Common->CCR, ADC_CCR_VBATEN))          ) ||
        ( (sConfig->Channel == ADC_CHANNEL_VREFINT)    &&
          (HAL_IS_BIT_CLR(tmpADC_Common->CCR, ADC_CCR_VREFEN)))
       )
    {
      /* Configuration of common ADC parameters (continuation)                */
      /* Set handle of the other ADC sharing the same common register         */
      __HAL_ADC_COMMON_ADC_OTHER(hadc, &tmphadcSharingSameCommonRegister);
      
      /* Software is allowed to change common parameters only when all ADCs   */
      /* of the common group are disabled.                                    */
      if ((__HAL_ADC_IS_ENABLED(hadc) == RESET)                                  &&
          ( (tmphadcSharingSameCommonRegister.Instance == HAL_NULL) ||
            (__HAL_ADC_IS_ENABLED(&tmphadcSharingSameCommonRegister) == RESET) ))
      {
        /* If Channel_16 is selected, enable Temp. sensor measurement path    */
        /* Note: Temp. sensor internal channels available on ADC1 only        */
        if ((sConfig->Channel == ADC_CHANNEL_TEMPSENSOR) && (hadc->Instance == ADC1))
        {
          tmpADC_Common->CCR |= ADC_CCR_TSEN;
          
          /* Delay for temperature sensor stabilization time */
          while(WaitLoopIndex < ADC_TEMPSENSOR_DELAY_CPU_CYCLES)
          {
            WaitLoopIndex++;
          }
        }
        /* If Channel_17 is selected, enable VBAT measurement path            */
        /* Note: VBAT internal channels available on ADC1 only                */
        else if ((sConfig->Channel == ADC_CHANNEL_VBAT) && (hadc->Instance == ADC1))
        {
          tmpADC_Common->CCR |= ADC_CCR_VBATEN;
        }
        /* If Channel_18 is selected, enable VREFINT measurement path         */
        /* Note: VrefInt internal channels available on all ADCs, but only    */
        /*       one ADC is allowed to be connected to VrefInt at the same    */
        /*       time.                                                        */
        else if (sConfig->Channel == ADC_CHANNEL_VREFINT)
        {
          tmpADC_Common->CCR |= ADC_CCR_VREFEN;
        }
      }
      /* If the requested internal measurement path has already been          */
      /* enabled and other ADC of the common group are enabled, internal      */
      /* measurement paths cannot be enabled.                                 */
      else  
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
      }
    }
    
  }
    
  }
  /* If a conversion is on going on regular group, no update on regular       */
  /* channel could be done on neither of the channel configuration structure  */
  /* parameters.                                                              */
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    tmpHALStatus = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
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
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{ 
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CHANNEL(sConfig->Channel));
  assert_param(IS_ADC_REGULAR_RANK(sConfig->Rank));
  assert_param(IS_ADC_SAMPLE_TIME(sConfig->SamplingTime));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
   
  /* Regular sequence configuration */
  /* For Rank 1 to 6 */
  if (sConfig->Rank < 7)
  {
    /* Clear the old SQx bits for the selected rank */
    hadc->Instance->SQR3 &= ~__HAL_ADC_SQR3_RK(ADC_SQR3_SQ1, sConfig->Rank);
    
    /* Set the SQx bits for the selected rank */
    hadc->Instance->SQR3 |= __HAL_ADC_SQR3_RK(sConfig->Channel, sConfig->Rank);
  }
  /* For Rank 7 to 12 */
  else if (sConfig->Rank < 13)
  {
    /* Clear the old SQx bits for the selected rank */
    hadc->Instance->SQR2 &= ~__HAL_ADC_SQR2_RK(ADC_SQR2_SQ7, sConfig->Rank);
    
    /* Set the SQx bits for the selected rank */
    hadc->Instance->SQR2 |= __HAL_ADC_SQR2_RK(sConfig->Channel, sConfig->Rank);
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Clear the old SQx bits for the selected rank */
    hadc->Instance->SQR1 &= ~__HAL_ADC_SQR1_RK(ADC_SQR1_SQ13, sConfig->Rank);
    
    /* Set the SQx bits for the selected rank */
    hadc->Instance->SQR1 |= __HAL_ADC_SQR1_RK(sConfig->Channel, sConfig->Rank);
  }
      
  /* Channel sampling time configuration */
  /* For channels 10 to 18 */
  if (sConfig->Channel > ADC_CHANNEL_10)
  {
    /* Clear the old sample time */
    hadc->Instance->SMPR1 &= ~__HAL_ADC_SMPR1(ADC_SMPR1_SMP10, sConfig->Channel);
    
    /* Set the new sample time */
    hadc->Instance->SMPR1 |= __HAL_ADC_SMPR1(sConfig->SamplingTime, sConfig->Channel);
  }
  else   /* For channels 0 to 9 */
  {
    /* Clear the old sample time */
    hadc->Instance->SMPR2 &= ~__HAL_ADC_SMPR2(ADC_SMPR2_SMP0, sConfig->Channel);
    
    /* Set the new sample time */
    hadc->Instance->SMPR2 |= __HAL_ADC_SMPR2(sConfig->SamplingTime, sConfig->Channel);
  }

  /* if ADC1 Channel_16 or Channel_17 is selected, enable Temperature sensor / VREFINT measurement path */
  if ((sConfig->Channel == ADC_CHANNEL_TEMPSENSOR) || (sConfig->Channel == ADC_CHANNEL_VREFINT))
  {
    hadc->Instance->CR2 |= ADC_CR2_TSVREFE;
  }
  
  /* if ADC1 Channel_17 is selected, enable VBAT measurement path */
  else if (sConfig->Channel == ADC_CHANNEL_VBAT)
  {
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_VBAT;
  }

   
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Configures the ADC injected group and the selected channel to be
  *         linked to the injected group.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes injected group, following calls to this 
  *         function can be used to reconfigure some parameters of structure
  *         "ADC_InjectionConfTypeDef" on the fly, without reseting the ADC.
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_InjectionConfTypeDef".
  * @note   In case of usage of internal measurement channels:
  *         Vbat/VrefInt/TempSensor.
  *         The recommended sampling time is at least:
  *          - For devices STM32F37x: 17.1us for temperature sensor
  *          - For the other STM32F3 devices: 2.2us for each of channels 
  *            Vbat/VrefInt/TempSensor.
  *         These internal paths can be be disabled using function 
  *         HAL_ADC_DeInit().
  * @note   To reset injected sequencer, function HAL_ADCEx_InjectedStop() can
  *         be used.
  * @note   Caution: For Injected Context Queue use: a context must be fully 
  * defined before start of injected conversion: all channels configured 
  * consecutively for the same ADC instance. Therefore, Number of calls of 
  * HAL_ADCEx_InjectedConfigChannel() must correspond to value of parameter 
  * InjectedNbrOfConversion for each context.
  *  - Example 1: If 1 context intended to be used (or not use of this feature: 
  *    QueueInjectedContext=DISABLE) and usage of the 3 first injected ranks 
  *    (InjectedNbrOfConversion=3), HAL_ADCEx_InjectedConfigChannel() must be  
  *    called once for each channel (3 times) before launching a conversion.   
  *    This function must not be called to configure the 4th injected channel:   
  *    it would start a new context into context queue.
  *  - Example 2: If 2 contexts intended to be used and usage of the 3 first 
  *    injected ranks (InjectedNbrOfConversion=3),  
  *    HAL_ADCEx_InjectedConfigChannel() must be called once for each channel and  
  *    for each context (3 channels x 2 contexts = 6 calls). Conversion can  
  *    start once the 1st context is set. The 2nd context can be set on the fly.
  * @param  hadc: ADC handle
  * @param  sConfigInjected: Structure of ADC injected group and ADC channel for
  *         injected group.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc, ADC_InjectionConfTypeDef* sConfigInjected)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  ADC_Common_TypeDef *tmpADC_Common;
  ADC_HandleTypeDef tmphadcSharingSameCommonRegister;
  uint32_t tmpOffsetShifted;
  uint32_t WaitLoopIndex = 0;
  
  /* Injected context queue feature: temporary JSQR variables defined in      */
  /* static to be passed over calls of this function                          */
  static uint32_t tmp_JSQR_ContextQueueBeingBuilt_ADCInstance = 0;
  static uint32_t tmp_JSQR_ContextQueueBeingBuilt_Channel_Count = 0;
  static uint32_t tmp_JSQR_ContextQueueBeingBuilt;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_INJECTED_RANK(sConfigInjected->InjectedRank));
  assert_param(IS_ADC_SAMPLE_TIME(sConfigInjected->InjectedSamplingTime));
  assert_param(IS_ADC_SINGLE_DIFFERENTIAL(sConfigInjected->InjectedSingleDiff));
  assert_param(IS_ADC_INJECTED_NB_CONV(sConfigInjected->InjectedNbrOfConversion));
  assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->InjectedDiscontinuousConvMode));
  assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->AutoInjectedConv));
  assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->QueueInjectedContext));
  assert_param(IS_ADC_EXTTRIGINJEC_EDGE(sConfigInjected->ExternalTrigInjecConvEdge));
  assert_param(IS_ADC_EXTTRIGINJEC(sConfigInjected->ExternalTrigInjecConv));
  assert_param(IS_ADC_OFFSET_NUMBER(sConfigInjected->InjectedOffsetNumber));
  assert_param(IS_ADC_RANGE(__HAL_ADC_GET_RESOLUTION(hadc), sConfigInjected->InjectedOffset));
  
  /* Verification of channel number: Channels 1 to 14 are available in        */  
  /* differential mode. Channels 15, 16, 17, 18 can be used only in           */
  /* single-ended mode.                                                       */
  if (sConfigInjected->InjectedSingleDiff != ADC_DIFFERENTIAL_ENDED)
  {
    assert_param(IS_ADC_CHANNEL(sConfigInjected->InjectedChannel));
  }
  else
  {
    assert_param(IS_ADC_DIFF_CHANNEL(sConfigInjected->InjectedChannel));
  }
    
  /* Process locked */
  __HAL_LOCK(hadc);


  /* Configuration of Injected group sequencer.                               */
  /* Hardware constraint: Must fully define injected context register JSQR    */
  /* before make it entering into injected sequencer queue.                   */
  /*                                                                          */
  /* - if scan mode is disabled:                                              */
  /*    * Injected channels sequence length is set to 0x00: 1 channel         */
  /*      converted (channel on injected rank 1)                              */
  /*      Parameter "InjectedNbrOfConversion" is discarded.                   */
  /*    * Injected context register JSQR setting is simple: register is fully */
  /*      defined on one call of this function (for injected rank 1) and can  */
  /*      be entered into queue directly.                                     */
  /* - if scan mode is enabled:                                               */
  /*    * Injected channels sequence length is set to parameter               */
  /*      "InjectedNbrOfConversion".                                          */
  /*    * Injected context register JSQR setting more complex: register is    */
  /*      fully defined over successive calls of this function, for each      */
  /*      injected channel rank. It is entered into queue only when all       */
  /*      injected ranks have been set.                                       */
  /*   Note: Scan mode is not present by hardware on this device, but used    */
  /*   by software for alignment over all STM32 devices.                      */
  
  if ((hadc->Init.ScanConvMode == ADC_SCAN_DISABLE)  ||
      (sConfigInjected->InjectedNbrOfConversion == 1)  )
  {
    /* Configuration of context register JSQR:                                */
    /*  - number of ranks in injected group sequencer: fixed to 1st rank      */
    /*    (scan mode disabled, only rank 1 used)                              */
    /*  - external trigger to start conversion                                */
    /*  - external trigger polarity                                           */
    /*  - channel set to rank 1 (scan mode disabled, only rank 1 used)        */
    
    if (sConfigInjected->InjectedRank == ADC_INJECTED_RANK_1)
    {
      tmp_JSQR_ContextQueueBeingBuilt = 0;
      
      /* Enable external trigger if trigger selection is different of         */
      /* software start.                                                      */
      /* Note: This configuration keeps the hardware feature of parameter     */
      /*       ExternalTrigInjecConvEdge "trigger edge none" equivalent to    */
      /*       software start.                                                */
      if (sConfigInjected->ExternalTrigInjecConv != ADC_INJECTED_SOFTWARE_START)
      {
        tmp_JSQR_ContextQueueBeingBuilt |= ( __HAL_ADC_JSQR_RK(sConfigInjected->InjectedChannel, ADC_INJECTED_RANK_1) |
                                             __HAL_ADC_JSQR_JEXTSEL(hadc, sConfigInjected->ExternalTrigInjecConv)     |
                                             sConfigInjected->ExternalTrigInjecConvEdge                                );
      }
      else
      {
        tmp_JSQR_ContextQueueBeingBuilt |= ( __HAL_ADC_JSQR_RK(sConfigInjected->InjectedChannel, ADC_INJECTED_RANK_1) );
      }
      
      hadc->Instance->JSQR = tmp_JSQR_ContextQueueBeingBuilt;
    
    }
    /* If another injected rank than rank1 was intended to be set, and could  */
    /* not due to ScanConvMode disabled, error is reported.                   */
    else
    {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
    }
    
  }
  else
  {    
    /* Case of scan mode enabled, several channels to set into injected group */
    /* sequencer.                                                             */
    /* Procedure to define injected context register JSQR over successive     */
    /* calls of this function, for each injected channel rank:                */
    
    /* 1. Start new context and set parameters related to all injected        */
    /*    channels: injected sequence length and trigger                      */
    if (tmp_JSQR_ContextQueueBeingBuilt_Channel_Count == 0)
    {
      /* Memorize ADC instance on the context being built */
      tmp_JSQR_ContextQueueBeingBuilt_ADCInstance = (uint32_t)hadc->Instance;
      /* Initialize number of channels that will be configured on the context */
      /*  being built                                                         */
      tmp_JSQR_ContextQueueBeingBuilt_Channel_Count = sConfigInjected->InjectedNbrOfConversion;
      /* Initialize value that will be set into register JSQR */
      tmp_JSQR_ContextQueueBeingBuilt = (uint32_t)0x00000000;
      
      /* Configuration of context register JSQR:                              */
      /*  - number of ranks in injected group sequencer                       */
      /*  - external trigger to start conversion                              */
      /*  - external trigger polarity                                         */
      tmp_JSQR_ContextQueueBeingBuilt = 0;
        
      /* Enable external trigger if trigger selection is different of         */
      /* software start.                                                      */
      /* Note: This configuration keeps the hardware feature of parameter     */
      /*       ExternalTrigInjecConvEdge "trigger edge none" equivalent to    */
      /*       software start.                                                */
      if (sConfigInjected->ExternalTrigInjecConv != ADC_INJECTED_SOFTWARE_START)
      {
        tmp_JSQR_ContextQueueBeingBuilt |= ((sConfigInjected->InjectedNbrOfConversion - (uint32_t)1)              |
                                             __HAL_ADC_JSQR_JEXTSEL(hadc, sConfigInjected->ExternalTrigInjecConv) |
                                             sConfigInjected->ExternalTrigInjecConvEdge                            );
      }
      else
      {
        tmp_JSQR_ContextQueueBeingBuilt |= ((sConfigInjected->InjectedNbrOfConversion - (uint32_t)1) );
      }
      
    }

    /* Verification that context being built is still targeting the same ADC */
    /* instance. If ADC instance mixing during context being built, ADC state */
    /* changed to error */
    if ((uint32_t)hadc->Instance == tmp_JSQR_ContextQueueBeingBuilt_ADCInstance)
    {
      /* 2. Continue setting of context under definition with parameter       */
      /*    related to each channel: channel rank sequence                    */ 
      /* Clear the old JSQx bits for the selected rank */
      tmp_JSQR_ContextQueueBeingBuilt &= ~__HAL_ADC_JSQR_RK(ADC_SQR3_SQ10, sConfigInjected->InjectedRank);
      
      /* Set the JSQx bits for the selected rank */
      tmp_JSQR_ContextQueueBeingBuilt |= __HAL_ADC_JSQR_RK(sConfigInjected->InjectedChannel, sConfigInjected->InjectedRank);

      /* Decrease channel count after setting into temporary JSQR variable */
      tmp_JSQR_ContextQueueBeingBuilt_Channel_Count --;
      
      /* 3. End of context setting: If last channel set, then write context   */
      /*    into register JSQR and make it enter into queue                   */
      if (tmp_JSQR_ContextQueueBeingBuilt_Channel_Count == 0)
      {
        hadc->Instance->JSQR = tmp_JSQR_ContextQueueBeingBuilt;
        
        /* Reset context channels count for next context configuration */
        tmp_JSQR_ContextQueueBeingBuilt_Channel_Count =0;
      }
    }
    else
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Process unlocked */
      __HAL_UNLOCK(hadc);
      
      return HAL_ERROR;
    }
  }

  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on injected group:                                   */
  /*  - Injected context queue: Queue disable (active context is kept) or     */
  /*    enable (context decremented, up to 2 contexts queued)                 */
  /*  - Injected discontinuous mode: can be enabled only if auto-injected     */
  /*    mode is disabled.                                                     */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_INJECTED(hadc) == RESET)
  {
    hadc->Instance->CFGR &= ~(ADC_CFGR_JQM    |
                              ADC_CFGR_JDISCEN );
     
    /* If auto-injected mode is disabled: no constraint                       */
    if (sConfigInjected->AutoInjectedConv == DISABLE)
    {
      hadc->Instance->CFGR |= (__HAL_ADC_CFGR_INJECT_CONTEXT_QUEUE(sConfigInjected->QueueInjectedContext)          | 
                               __HAL_ADC_CFGR_INJECT_DISCCONTINUOUS(sConfigInjected->InjectedDiscontinuousConvMode) );
    }
    /* If auto-injected mode is enabled: Injected discontinuous setting is   */
    /* discarded.                                                             */
    else
    {
      hadc->Instance->CFGR |= __HAL_ADC_CFGR_INJECT_CONTEXT_QUEUE(sConfigInjected->QueueInjectedContext);
      
      /* If injected discontinuous mode was intended to be set and could not  */
      /* due to auto-injected enabled, error is reported.                     */
      if (sConfigInjected->InjectedDiscontinuousConvMode == ENABLE)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
      }
    }

  }
  
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on regular and injected groups:                      */
  /*  - Automatic injected conversion: can be enabled if injected group       */
  /*    external triggers are disabled.                                       */
  /*  - Channel sampling time                                                 */
  /*  - Channel offset                                                        */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(hadc) == RESET)
  {
    /* Configure Automatic injected conversion */
    hadc->Instance->CFGR &= ~(ADC_CFGR_JAUTO);
    
    /* If injected group external triggers are disabled (set to injected      */
    /* software start): no constraint                                         */
    if (sConfigInjected->ExternalTrigInjecConv == ADC_INJECTED_SOFTWARE_START)
    {
      hadc->Instance->CFGR |= __HAL_ADC_CFGR_INJECT_AUTO_CONVERSION(sConfigInjected->AutoInjectedConv);
    }
    /* If Automatic injected conversion was intended to be set and could not  */
    /* due to injected group external triggers enabled, error is reported.    */
    else
    {
      if (sConfigInjected->AutoInjectedConv == ENABLE)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
      }
    }
      

    /* Sampling time configuration of the selected channel */
    /* if ADC_Channel_10 ... ADC_Channel_18 is selected */
    if (sConfigInjected->InjectedChannel > ADC_CHANNEL_10)
    {
      /* Clear the old sample time */
      hadc->Instance->SMPR2 &= ~__HAL_ADC_SMPR2(ADC_SMPR1_SMP0, sConfigInjected->InjectedChannel);
      
      /* Set the new sample time */
      hadc->Instance->SMPR2 |= __HAL_ADC_SMPR2(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel);
    }
    else /* ADC_Channel include in ADC_Channel_[0..9] */
    {
      /* Clear the old sample time */
      hadc->Instance->SMPR1 &= ~__HAL_ADC_SMPR1(ADC_SMPR2_SMP10, sConfigInjected->InjectedChannel);
      
      /* Set the new sample time */
      hadc->Instance->SMPR1 |= __HAL_ADC_SMPR1(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel);
    }
        
    /* Configure the offset: offset enable/disable, channel, offset value */

    /* Shift the offset in function of the selected ADC resolution. */
    /* Offset has to be left-aligned on bit 11, the LSB (right bits) are set to 0 */
    tmpOffsetShifted = __HAL_ADC_OFFSET_SHIFT_RESOLUTION(hadc, sConfigInjected->InjectedOffset);
    
    switch (sConfigInjected->InjectedOffsetNumber)
    {
    case ADC_OFFSET_1:
      /* Configure offset register 1:                                         */
      /* - Enable offset                                                      */
      /* - Set channel number                                                 */
      /* - Set offset value                                                   */
      hadc->Instance->OFR1 &= ~( ADC_OFR1_OFFSET1_CH |
                                 ADC_OFR1_OFFSET1     );
      hadc->Instance->OFR1 |= ( ADC_OFR1_OFFSET1_EN                     |
                                __HAL_ADC_OFR_CHANNEL(sConfigInjected->InjectedChannel) |
                                tmpOffsetShifted                         );
      break;
    
    case ADC_OFFSET_2:
      /* Configure offset register 2:                                         */
      /* - Enable offset                                                      */
      /* - Set channel number                                                 */
      /* - Set offset value                                                   */
      hadc->Instance->OFR2 &= ~( ADC_OFR2_OFFSET2_CH |
                                 ADC_OFR2_OFFSET2     );
      hadc->Instance->OFR2 |= ( ADC_OFR2_OFFSET2_EN                     |
                                __HAL_ADC_OFR_CHANNEL(sConfigInjected->InjectedChannel) |
                                tmpOffsetShifted                         );
      break;
        
    case ADC_OFFSET_3:
      /* Configure offset register 3:                                         */
      /* - Enable offset                                                      */
      /* - Set channel number                                                 */
      /* - Set offset value                                                   */
      hadc->Instance->OFR3 &= ~( ADC_OFR3_OFFSET3_CH |
                                 ADC_OFR3_OFFSET3     );
      hadc->Instance->OFR3 |= ( ADC_OFR3_OFFSET3_EN                     |
                                __HAL_ADC_OFR_CHANNEL(sConfigInjected->InjectedChannel) |
                                tmpOffsetShifted                         );
      break;
    
    case ADC_OFFSET_4:
      /* Configure offset register 1:                                         */
      /* - Enable offset                                                      */
      /* - Set channel number                                                 */
      /* - Set offset value                                                   */
      hadc->Instance->OFR4 &= ~( ADC_OFR4_OFFSET4_CH |
                                 ADC_OFR4_OFFSET4     );
      hadc->Instance->OFR4 |= ( ADC_OFR4_OFFSET4_EN                     |
                                __HAL_ADC_OFR_CHANNEL(sConfigInjected->InjectedChannel) |
                                tmpOffsetShifted                         );
      break;
    
    /* Case ADC_OFFSET_NONE */
    default :
    /* Scan OFR1, OFR2, OFR3, OFR4 to check if the selected channel is enabled. If this is the case, offset OFRx is disabled. */
      if (((hadc->Instance->OFR1) & ADC_OFR1_OFFSET1_CH) == __HAL_ADC_OFR_CHANNEL(sConfigInjected->InjectedChannel))
      {
        /* Disable offset OFR1*/
        hadc->Instance->OFR1 &= ~ADC_OFR1_OFFSET1_EN; 
      }
      if (((hadc->Instance->OFR2) & ADC_OFR2_OFFSET2_CH) == __HAL_ADC_OFR_CHANNEL(sConfigInjected->InjectedChannel))
      {
        /* Disable offset OFR2*/
        hadc->Instance->OFR2 &= ~ADC_OFR2_OFFSET2_EN; 
      }
      if (((hadc->Instance->OFR3) & ADC_OFR3_OFFSET3_CH) == __HAL_ADC_OFR_CHANNEL(sConfigInjected->InjectedChannel))
      {
        /* Disable offset OFR3*/
        hadc->Instance->OFR3 &= ~ADC_OFR3_OFFSET3_EN;
      }
      if (((hadc->Instance->OFR4) & ADC_OFR4_OFFSET4_CH) == __HAL_ADC_OFR_CHANNEL(sConfigInjected->InjectedChannel))
      {
        /* Disable offset OFR4*/
        hadc->Instance->OFR4 &= ~ADC_OFR4_OFFSET4_EN;
      }
      break;
    }

  }
  
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated only when ADC is disabled:                */
  /*  - Single or differential mode                                           */
  /*  - Internal measurement channels: Vbat/VrefInt/TempSensor                */
  if (__HAL_ADC_IS_ENABLED(hadc) == RESET)
  {
    /* Configuration of differential mode */
    if (sConfigInjected->InjectedSingleDiff != ADC_DIFFERENTIAL_ENDED)
    {
      /* Disable differential mode (default mode: single-ended) */
      hadc->Instance->DIFSEL &= ~(__HAL_ADC_DIFSEL_CHANNEL(sConfigInjected->InjectedChannel));
    }
    else
    {
      /* Enable differential mode */
      hadc->Instance->DIFSEL |= __HAL_ADC_DIFSEL_CHANNEL(sConfigInjected->InjectedChannel);
      
      /* Sampling time configuration of channel ADC_IN+1 (negative input) */
      /* For channels 10 to 18 */
      if (sConfigInjected->InjectedChannel > ADC_CHANNEL_10)
      {
        /* Clear the old sample time */
        hadc->Instance->SMPR2 &= ~__HAL_ADC_SMPR2(ADC_SMPR1_SMP0, (sConfigInjected->InjectedChannel +1));
        
        /* Set the new sample time */
        hadc->Instance->SMPR2 |= __HAL_ADC_SMPR2(sConfigInjected->InjectedSamplingTime, (sConfigInjected->InjectedChannel +1));
      }
      else /* For channels 0 to 9 */
      {
        /* Clear the old sample time */
        hadc->Instance->SMPR1 &= ~__HAL_ADC_SMPR1(ADC_SMPR2_SMP10, (sConfigInjected->InjectedChannel +1));
        
        /* Set the new sample time */
        hadc->Instance->SMPR1 |= __HAL_ADC_SMPR1(sConfigInjected->InjectedSamplingTime, (sConfigInjected->InjectedChannel +1));
      }
    }
    

  /* Management of internal measurement channels: Vbat/VrefInt/TempSensor     */
    /* internal measurement paths enable: If internal channel selected,       */
    /* enable dedicated internal buffers and path.                            */
    /* Note: these internal measurement paths can be disabled using           */
    /* HAL_ADC_deInit().                                                      */
       
    /* Configuration of common ADC parameters                                 */
    /* Pointer to the common control register to which is belonging hadc      */
    /* (Depending on STM32F3 product, there may be up to 4 ADC and 2 common   */
    /* control registers)                                                     */
    tmpADC_Common = __HAL_ADC_COMMON_REGISTER(hadc);
  
    /* If the requested internal measurement path has already been enabled,   */
    /* bypass the configuration processing.                                   */
    if (( (sConfigInjected->InjectedChannel == ADC_CHANNEL_TEMPSENSOR) &&
          (HAL_IS_BIT_CLR(tmpADC_Common->CCR, ADC_CCR_TSEN))            ) ||
        ( (sConfigInjected->InjectedChannel == ADC_CHANNEL_VBAT)       &&
          (HAL_IS_BIT_CLR(tmpADC_Common->CCR, ADC_CCR_VBATEN))          ) ||
        ( (sConfigInjected->InjectedChannel == ADC_CHANNEL_VREFINT)    &&
          (HAL_IS_BIT_CLR(tmpADC_Common->CCR, ADC_CCR_VREFEN)))
       )
    {
      /* Configuration of common ADC parameters (continuation)                */
      /* Set handle of the other ADC sharing the same common register         */
      __HAL_ADC_COMMON_ADC_OTHER(hadc, &tmphadcSharingSameCommonRegister);
      
      /* Software is allowed to change common parameters only when all ADCs   */
      /* of the common group are disabled.                                    */
      if ((__HAL_ADC_IS_ENABLED(hadc) == RESET)                                  &&
          ( (tmphadcSharingSameCommonRegister.Instance == HAL_NULL) ||
            (__HAL_ADC_IS_ENABLED(&tmphadcSharingSameCommonRegister) == RESET) ))
      {
        /* If Channel_16 is selected, enable Temp. sensor measurement path    */
        /* Note: Temp. sensor internal channels available on ADC1 only        */
        if ((sConfigInjected->InjectedChannel == ADC_CHANNEL_TEMPSENSOR) && (hadc->Instance == ADC1))
        {
          tmpADC_Common->CCR |= ADC_CCR_TSEN;
          
          /* Delay for temperature sensor stabilization time */
          while(WaitLoopIndex < ADC_TEMPSENSOR_DELAY_CPU_CYCLES)
          {
            WaitLoopIndex++;
          }
        }
        /* If Channel_17 is selected, enable VBAT measurement path            */
        /* Note: VBAT internal channels available on ADC1 only                */
        else if ((sConfigInjected->InjectedChannel == ADC_CHANNEL_VBAT) && (hadc->Instance == ADC1))
        {
          tmpADC_Common->CCR |= ADC_CCR_VBATEN;
        }
        /* If Channel_18 is selected, enable VREFINT measurement path         */
        /* Note: VrefInt internal channels available on all ADCs, but only    */
        /*       one ADC is allowed to be connected to VrefInt at the same    */
        /*       time.                                                        */
        else if (sConfigInjected->InjectedChannel == ADC_CHANNEL_VREFINT)
        {
          tmpADC_Common->CCR |= ADC_CCR_VREFEN;
        }
      }
      /* If the requested internal measurement path has already been enabled  */
      /* and other ADC of the common group are enabled, internal              */
      /* measurement paths cannot be enabled.                                 */
      else  
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
      }
    }
    
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Configures the ADC injected group and the selected channel to be
  *         linked to the injected group.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes injected group, following calls to this 
  *         function can be used to reconfigure some parameters of structure
  *         "ADC_InjectionConfTypeDef" on the fly, without reseting the ADC.
  *         The setting of these parameters is conditioned to ADC state: 
  *         this function must be called when ADC is not under conversion.
  * @note   In case of usage of internal measurement channels:
  *         Vbat/VrefInt/TempSensor.
  *         The recommended sampling time is at least:
  *          - For devices STM32F37x: 17.1us for temperature sensor
  *          - For the other STM32F3 devices: 2.2us for each of channels 
  *            Vbat/VrefInt/TempSensor.
  *         These internal paths can be be disabled using function 
  *         HAL_ADC_DeInit().
  * @param  hadc: ADC handle
  * @param  sConfigInjected: Structure of ADC injected group and ADC channel for
  *         injected group.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc, ADC_InjectionConfTypeDef* sConfigInjected)
{   
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CHANNEL(sConfigInjected->InjectedChannel));
  assert_param(IS_ADC_INJECTED_RANK(sConfigInjected->InjectedRank));
  assert_param(IS_ADC_SAMPLE_TIME(sConfigInjected->InjectedSamplingTime));
  assert_param(IS_ADC_INJECTED_NB_CONV(sConfigInjected->InjectedNbrOfConversion));
  assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->InjectedDiscontinuousConvMode));
  assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->AutoInjectedConv));
  assert_param(IS_ADC_EXTTRIGINJEC(sConfigInjected->ExternalTrigInjecConv));
  assert_param(IS_ADC_RANGE(sConfigInjected->InjectedOffset));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  
  /* Configuration of injected group sequencer:                               */
  /* - if scan mode is disabled, injected channels sequence length is set to  */
  /*   0x00: 1 channel converted (channel on regular rank 1)                  */
  /*   Parameter "InjectedNbrOfConversion" is discarded.                      */
  /*   Note: Scan mode is present by hardware on this device and, if          */
  /*   disabled, discards automatically nb of conversions. Anyway, nb of      */
  /*   conversions is forced to 0x00 for alignment over all STM32 devices.    */
  /* - if scan mode is enabled, injected channels sequence length is set to   */
  /*   parameter ""InjectedNbrOfConversion".                                  */
  if (hadc->Init.ScanConvMode == ADC_SCAN_DISABLE)
  {
    if (sConfigInjected->InjectedRank == ADC_INJECTED_RANK_1)
    {
      /* Clear the old SQx bits for all injected ranks */
      hadc->Instance->JSQR &= ~ (ADC_JSQR_JL   |
                                 ADC_JSQR_JSQ4 |
                                 ADC_JSQR_JSQ3 |
                                 ADC_JSQR_JSQ2 |
                                 ADC_JSQR_JSQ1  );

      /* Set the SQx bits for the selected rank */
      hadc->Instance->JSQR |= __HAL_ADC_JSQR_RK(sConfigInjected->InjectedChannel,
                                                ADC_INJECTED_RANK_1,
                                                0x01);
    }
    /* If another injected rank than rank1 was intended to be set, and could  */
    /* not due to ScanConvMode disabled, error is reported.                   */
    else
    {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
    }
  }
  else
  {
    /* Clear the old SQx bits for the selected rank */
    hadc->Instance->JSQR &= ~ (ADC_JSQR_JL                                                |
                               __HAL_ADC_JSQR_RK(ADC_JSQR_JSQ1,                         
                                                 sConfigInjected->InjectedRank,         
                                                 sConfigInjected->InjectedNbrOfConversion) );
    
    /* Since injected channels rank conv. order depends on total number of   */
    /* injected conversions, selected rank must be below or equal to total   */
    /* number of injected conversions to be updated.                         */
    if (sConfigInjected->InjectedRank <= sConfigInjected->InjectedNbrOfConversion)
    {
      /* Set the SQx bits for the selected rank */
      hadc->Instance->JSQR |= (__HAL_ADC_JSQR_JL(sConfigInjected->InjectedNbrOfConversion) |
                               __HAL_ADC_JSQR_RK(sConfigInjected->InjectedChannel,      
                                                 sConfigInjected->InjectedRank,         
                                                 sConfigInjected->InjectedNbrOfConversion)  );
    }
  }
   
  
  /* Configuration of injected group: external trigger                        */
  /*  - external trigger to start conversion                                  */
  /*  - external trigger polarity                                             */
  /*    If Automatic injected conversion disabled: always set to 1,           */
  /*    because needed for all triggers: external trigger of SW start)        */
  /* Hardware constraint: ADC must be disabled                                */
  /* Note: In case of ADC already enabled, caution to not launch an unwanted  */
  /*       conversion while modifying register CR2 by writing 1 to bit ADON   */
  /* These settings are modified only if required parameters are different as */
  /* current setting                                                          */
  if ((__HAL_ADC_IS_ENABLED(hadc) == RESET)                                              && 
      ((hadc->Instance->CR2 & ADC_CR2_JEXTSEL) != sConfigInjected->ExternalTrigInjecConv)  )
  {
    hadc->Instance->CR2 &= ~( ADC_CR2_JEXTSEL  |
                              ADC_CR2_JEXTTRIG |
                              ADC_CR2_ADON      );
    
    /* If automatic injected conversion is intended to be enabled and         */
    /* conditions are fulfilled (injected group external triggers are         */
    /* disabled), then keep injected external trigger JEXTTRIG cleared        */
    if (!((sConfigInjected->AutoInjectedConv == ENABLE) &&
          (sConfigInjected->ExternalTrigInjecConv == ADC_INJECTED_SOFTWARE_START)))
    {
      hadc->Instance->CR2 |= ( sConfigInjected->ExternalTrigInjecConv |
                               ADC_CR2_JEXTTRIG                        );
    }
    else
    {
      hadc->Instance->CR2 |= ( sConfigInjected->ExternalTrigInjecConv );
    }
  }
  
  
  /* Configuration of injected group                                          */
  /*  - Automatic injected conversion                                         */
  /*  - Injected discontinuous mode                                           */
  hadc->Instance->CR1 &= ~(ADC_CR1_JAUTO   |
                           ADC_CR1_JDISCEN  );
    
    /* Automatic injected conversion can be enabled if injected group         */
    /* external triggers are disabled.                                        */
    if (sConfigInjected->AutoInjectedConv == ENABLE)
    {
      if (sConfigInjected->ExternalTrigInjecConv == ADC_INJECTED_SOFTWARE_START)
      {
        hadc->Instance->CR1 |= ADC_CR1_JAUTO;
      }
      else
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
      } 
    }
    
    /* Injected discontinuous can be enabled only if auto-injected mode is    */
    /* disabled.                                                              */  
    if (sConfigInjected->InjectedDiscontinuousConvMode == ENABLE)
    {
      if (sConfigInjected->AutoInjectedConv == DISABLE)
      {
        hadc->Instance->CR1 |= ADC_CR1_JDISCEN;
      } 
      else
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        tmpHALStatus = HAL_ERROR;
      }
    }

  
  /* Channel sampling time configuration */
  /* For channels 10 to 18 */
  if (sConfigInjected->InjectedChannel > ADC_CHANNEL_10)
  {
    /* Clear the old sample time */
    hadc->Instance->SMPR1 &= ~__HAL_ADC_SMPR1(ADC_SMPR1_SMP10, sConfigInjected->InjectedChannel);
    
    /* Set the new sample time */
    hadc->Instance->SMPR1 |= __HAL_ADC_SMPR1(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel);
  }
  else   /* For channels 0 to 9 */
  {
    /* Clear the old sample time */
    hadc->Instance->SMPR2 &= ~__HAL_ADC_SMPR2(ADC_SMPR2_SMP0, sConfigInjected->InjectedChannel);
    
    /* Set the new sample time */
    hadc->Instance->SMPR2 |= __HAL_ADC_SMPR2(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel);
  }
    
  /* Configure the offset: offset enable/disable, InjectedChannel, offset value */
  switch(sConfigInjected->InjectedRank)
  {
    case 1:
      /* Set injected channel 1 offset */
      hadc->Instance->JOFR1 &= ~(ADC_JOFR1_JOFFSET1);
      hadc->Instance->JOFR1 |= sConfigInjected->InjectedOffset;
      break;
    case 2:
      /* Set injected channel 2 offset */
      hadc->Instance->JOFR2 &= ~(ADC_JOFR2_JOFFSET2);
      hadc->Instance->JOFR2 |= sConfigInjected->InjectedOffset;
      break;
    case 3:
      /* Set injected channel 3 offset */
      hadc->Instance->JOFR3 &= ~(ADC_JOFR3_JOFFSET3);
      hadc->Instance->JOFR3 |= sConfigInjected->InjectedOffset;
      break;
    default:
      /* Set injected channel 4 offset */
      hadc->Instance->JOFR4 &= ~(ADC_JOFR4_JOFFSET4);
      hadc->Instance->JOFR4 |= sConfigInjected->InjectedOffset;
      break;
  }
  
  /* if ADC1 Channel_16 or Channel_17 is selected, enable Temperature sensor / VREFINT measurement path */
  if ((sConfigInjected->InjectedChannel == ADC_CHANNEL_TEMPSENSOR) || (sConfigInjected->InjectedChannel == ADC_CHANNEL_VREFINT))
  {
    hadc->Instance->CR2 |= ADC_CR2_TSVREFE;
  }
  /* if ADC1 Channel_17 is selected, enable VBAT measurement path */
  else if (sConfigInjected->InjectedChannel == ADC_CHANNEL_VBAT)
  {
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_VBAT;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
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
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  uint32_t tmpAWDHighThresholdShifted;
  uint32_t tmpAWDLowThresholdShifted;
  
  uint32_t tmpADCFlagAWD2orAWD3;
  uint32_t tmpADCITAWD2orAWD3;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_ANALOG_WATCHDOG_NUMBER(AnalogWDGConfig->WatchdogNumber));
  assert_param(IS_ADC_ANALOG_WATCHDOG_MODE(AnalogWDGConfig->WatchdogMode));
  assert_param(IS_ADC_CHANNEL(AnalogWDGConfig->Channel));
  assert_param(IS_FUNCTIONAL_STATE(AnalogWDGConfig->ITMode));

  /* Verify if threshold is within the selected ADC resolution */
  assert_param(IS_ADC_RANGE(__HAL_ADC_GET_RESOLUTION(hadc), AnalogWDGConfig->HighThreshold));
  assert_param(IS_ADC_RANGE(__HAL_ADC_GET_RESOLUTION(hadc), AnalogWDGConfig->LowThreshold));

  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on regular and injected groups:                      */
  /*  - Analog watchdog channels                                              */
  /*  - Analog watchdog thresholds                                            */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(hadc) == RESET)
  {
  
    /* Analog watchdogs configuration */
    if(AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_1)
    {
      /* Configuration of analog watchdog:                                    */
      /*  - Set the analog watchdog enable mode: regular and/or injected      */
      /*    groups, one or overall group of channels.                         */
      /*  - Set the Analog watchdog channel (is not used if watchdog          */
      /*    mode "all channels": ADC_CFGR_AWD1SGL=0).                         */
      hadc->Instance->CFGR &= ~( ADC_CFGR_AWD1SGL |
                                 ADC_CFGR_JAWD1EN |
                                 ADC_CFGR_AWD1EN  |
                                 ADC_CFGR_AWD1CH   );
      
      hadc->Instance->CFGR |= ( AnalogWDGConfig->WatchdogMode                  |
                                __HAL_ADC_CFGR_AWD1CH(AnalogWDGConfig->Channel) );

      /* Shift the offset in function of the selected ADC resolution:         */
      /* Thresholds have to be left-aligned on bit 11, the LSB (right bits)   */
      /* are set to 0                                                         */ 
      tmpAWDHighThresholdShifted = __HAL_ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(hadc, AnalogWDGConfig->HighThreshold);
      tmpAWDLowThresholdShifted  = __HAL_ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(hadc, AnalogWDGConfig->LowThreshold);
      
      /* Set the high and low thresholds */
      hadc->Instance->TR1 &= ~(ADC_TR1_HT1 | ADC_TR1_LT1);
      hadc->Instance->TR1 |=  ( __HAL_ADC_TRX_HIGHTHRESHOLD (tmpAWDHighThresholdShifted) |
                                tmpAWDLowThresholdShifted                                 );
      
      /* Clear the ADC Analog watchdog flag (in case of let enabled by        */
      /* previous ADC operations) to be ready to use for HAL_ADC_IRQHandler() */
      /* or HAL_ADC_PollForEvent().                                           */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_IT_AWD1);
      
      /* Configure ADC Analog watchdog interrupt */
      if(AnalogWDGConfig->ITMode == ENABLE)
      {
        /* Enable the ADC Analog watchdog interrupt */
        __HAL_ADC_ENABLE_IT(hadc, ADC_IT_AWD1);
      }
      else
      {
        /* Disable the ADC Analog watchdog interrupt */
        __HAL_ADC_DISABLE_IT(hadc, ADC_IT_AWD1);
      }
      
    }
    /* Case of ADC_ANALOGWATCHDOG_2 and ADC_ANALOGWATCHDOG_3 */
    else
    {
    /* Shift the threshold in function of the selected ADC resolution */
    /* have to be left-aligned on bit 7, the LSB (right bits) are set to 0    */
      tmpAWDHighThresholdShifted = __HAL_ADC_AWD23THRESHOLD_SHIFT_RESOLUTION(hadc, AnalogWDGConfig->HighThreshold);
      tmpAWDLowThresholdShifted  = __HAL_ADC_AWD23THRESHOLD_SHIFT_RESOLUTION(hadc, AnalogWDGConfig->LowThreshold);

      if (AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_2)
      {
        /* Set the Analog watchdog channel or group of channels. This also    */
        /* enables the watchdog.                                              */
        /* Note: Conditionnal register reset, because several channels can be */
        /*       set by successive calls of this function.                    */
        if (AnalogWDGConfig->WatchdogMode != ADC_ANALOGWATCHDOG_NONE) 
        {
          hadc->Instance->AWD2CR |= __HAL_ADC_CFGR_AWD23CR(AnalogWDGConfig->Channel);
        }
        else
        {
          hadc->Instance->AWD2CR &= ~ADC_AWD2CR_AWD2CH;
        }
        
        /* Set the high and low thresholds */
        hadc->Instance->TR2 &= ~(ADC_TR2_HT2 | ADC_TR2_LT2);
        hadc->Instance->TR2 |=  ( __HAL_ADC_TRX_HIGHTHRESHOLD (tmpAWDHighThresholdShifted) |
                                  tmpAWDLowThresholdShifted                                 );
        
        /* Set temporary variable to flag and IT of AWD2 or AWD3 for further  */
        /* settings.                                                          */
        tmpADCFlagAWD2orAWD3 = ADC_FLAG_AWD2;
        tmpADCITAWD2orAWD3 = ADC_IT_AWD2;
      }
      /* (AnalogWDGConfig->WatchdogNumber == ADC_ANALOGWATCHDOG_3) */
      else
      {
        /* Set the Analog watchdog channel or group of channels. This also    */
        /* enables the watchdog.                                              */
        /* Note: Conditionnal register reset, because several channels can be */
        /*       set by successive calls of this function.                    */
        if (AnalogWDGConfig->WatchdogMode != ADC_ANALOGWATCHDOG_NONE) 
        {
          hadc->Instance->AWD3CR |= __HAL_ADC_CFGR_AWD23CR(AnalogWDGConfig->Channel);
        }
        else
        {
          hadc->Instance->AWD3CR &= ~ADC_AWD3CR_AWD3CH;
        }
        
        /* Set the high and low thresholds */
        hadc->Instance->TR3 &= ~(ADC_TR3_HT3 | ADC_TR3_LT3);
        hadc->Instance->TR3 |=  ( __HAL_ADC_TRX_HIGHTHRESHOLD (tmpAWDHighThresholdShifted) |
                                  tmpAWDLowThresholdShifted                                 );
        
        /* Set temporary variable to flag and IT of AWD2 or AWD3 for further  */
        /* settings.                                                          */
        tmpADCFlagAWD2orAWD3 = ADC_FLAG_AWD3;
        tmpADCITAWD2orAWD3 = ADC_IT_AWD3;
      }

      /* Clear the ADC Analog watchdog flag (in case of let enabled by        */
      /* previous ADC operations) to be ready to use for HAL_ADC_IRQHandler() */
      /* or HAL_ADC_PollForEvent().                                           */
      __HAL_ADC_CLEAR_FLAG(hadc, tmpADCFlagAWD2orAWD3);

      /* Configure ADC Analog watchdog interrupt */
      if(AnalogWDGConfig->ITMode == ENABLE)
      {
        __HAL_ADC_ENABLE_IT(hadc, tmpADCITAWD2orAWD3);
      }
      else
      {
        __HAL_ADC_DISABLE_IT(hadc, tmpADCITAWD2orAWD3);
      }
    }
  
  }
  /* If a conversion is on going on regular or injected groups, no update     */
  /* could be done on neither of the AWD configuration structure parameters.  */
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    tmpHALStatus = HAL_ERROR;
  }
  
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Configures the analog watchdog.
  * @param  hadc: ADC handle
  * @param  AnalogWDGConfig: Structure of ADC analog watchdog configuration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_ANALOG_WATCHDOG_MODE(AnalogWDGConfig->WatchdogMode));
  assert_param(IS_ADC_CHANNEL(AnalogWDGConfig->Channel));
  assert_param(IS_FUNCTIONAL_STATE(AnalogWDGConfig->ITMode));
  assert_param(IS_ADC_RANGE(AnalogWDGConfig->HighThreshold));
  assert_param(IS_ADC_RANGE(AnalogWDGConfig->LowThreshold));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Analog watchdog configuration */

  /* Configure ADC Analog watchdog interrupt */
  if(AnalogWDGConfig->ITMode == ENABLE)
  {
    /* Enable the ADC Analog watchdog interrupt */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_AWD);
  }
  else
  {
    /* Disable the ADC Analog watchdog interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IT_AWD);
  }
  
  /* Configuration of analog watchdog:                                        */
  /*  - Set the analog watchdog enable mode: regular and/or injected groups,  */
  /*    one or all channels.                                                  */
  /*  - Set the Analog watchdog channel (is not used if watchdog              */
  /*    mode "all channels": ADC_CFGR_AWD1SGL=0).                             */
  hadc->Instance->CR1 &= ~( ADC_CR1_AWDSGL |
                            ADC_CR1_JAWDEN |
                            ADC_CR1_AWDEN  |
                            ADC_CR1_AWDCH   );
  
  hadc->Instance->CR1 |= ( AnalogWDGConfig->WatchdogMode |
                           AnalogWDGConfig->Channel       );
      
  /* Set the high threshold */
  hadc->Instance->HTR = AnalogWDGConfig->HighThreshold;
  
  /* Set the low threshold */
  hadc->Instance->LTR = AnalogWDGConfig->LowThreshold;

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}
#endif /* STM32F373xC || STM32F378xx */


#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
/**
  * @brief  Enable ADC multimode and configure multimode parameters
  * @note   Possibility to update parameters on the fly:
  *         This function initializes multimode parameters, following  
  *         calls to this function can be used to reconfigure some parameters 
  *         of structure "ADC_MultiModeTypeDef" on the fly, without reseting 
  *         the ADCs (both ADCs of the common group).
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_MultiModeTypeDef".
  * @note   To change back configuration from multimode to single mode, ADC must
  *         be reset (using function HAL_ADC_Init() ).
  * @param  hadc: ADC handle
  * @param  multimode : Structure of ADC multimode configuration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef* hadc, ADC_MultiModeTypeDef* multimode)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  ADC_Common_TypeDef *tmpADC_Common;
  ADC_HandleTypeDef tmphadcSharingSameCommonRegister;
  
  /* Check the parameters */
  assert_param(IS_ADC_MULTIMODE_MASTER_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_MODE(multimode->Mode));
  assert_param(IS_ADC_DMA_ACCESS_MODE(multimode->DMAAccessMode));
  assert_param(IS_ADC_SAMPLING_DELAY(multimode->TwoSamplingDelay));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  
  /* Set handle of the other ADC sharing the same common register             */
  __HAL_ADC_COMMON_ADC_OTHER(hadc, &tmphadcSharingSameCommonRegister);
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on regular group:                                    */
  /*  - Multimode DMA configuration                                           */
  /*  - Multimode DMA mode                                                    */
  /* Parameters that can be updated only when ADC is disabled:                */
  /*  - Multimode mode selection                                              */
  /*  - Multimode delay                                                       */
  /* To optimize code, all multimode settings can be set when both ADCs of    */
  /* the common group are in state: disabled.                                 */
  if ((__HAL_ADC_IS_ENABLED(hadc) == RESET)                             &&
      (__HAL_ADC_IS_ENABLED(&tmphadcSharingSameCommonRegister) == RESET)  )
  {
    
    /* Pointer to the common control register to which is belonging hadc      */
    /* (Depending on STM32F3 product, there may have up to 4 ADC and 2 common */
    /* control registers)                                                     */
    tmpADC_Common = __HAL_ADC_COMMON_REGISTER(hadc);
    
    /* Configuration of ADC common group ADC1&ADC2, ADC3&ADC4 if available    */
    /* (ADC2, ADC3, ADC4 availability depends on STM32 product)               */
    /*  - set the selected multimode                                          */
    /*  - DMA access mode                                                     */
    /*  - Set delay between two sampling phases                               */
    /*    Note: Delay range depends on selected resolution:                   */
    /*      from 1 to 12 clock cycles for 12 bits                             */
    /*      from 1 to 10 clock cycles for 10 bits,                            */
    /*      from 1 to 8 clock cycles for 8 bits                               */
    /*      from 1 to 6 clock cycles for 6 bits                               */
    /*    If a higher delay is selected, it will be clamped to maximum delay  */
    /*    range                                                               */
    tmpADC_Common->CCR &= ~( ADC_CCR_MULTI |
                             ADC_CCR_MDMA  |
                             ADC_CCR_DELAY | 
                             ADC_CCR_DMACFG );
    
    tmpADC_Common->CCR |= ( multimode->Mode                                                 |
                            multimode->DMAAccessMode                                        |
                            multimode->TwoSamplingDelay                                     |
                            __HAL_ADC_CCR_MULTI_DMACONTREQ(hadc->Init.DMAContinuousRequests) );
  }
  /* If one of the ADC sharing the same common group is enabled, no update    */
  /* could be done on neither of the multimode structure parameters.          */
  else
  {
    /* Update ADC state machine to error */
    hadc->State = HAL_ADC_STATE_ERROR;
    
    tmpHALStatus = HAL_ERROR;
  }
    
    
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
} 
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F328xx || STM32F334x8    */

/**
  * @}
  */

/**
  * @}
  */
  
/** @defgroup ADCEx_Private_Functions ADC Extended Private Functions
  * @{
  */
/**
  * @brief  DMA transfer complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma)
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
 
  /* Update state machine on conversion status if not in error state */
  if(hadc->State != HAL_ADC_STATE_ERROR)
  {
    /* Update ADC state machine */
    if(hadc->State != HAL_ADC_STATE_EOC_INJ_REG)
    {
      /* Check if a conversion is ready on injected group */
      if(hadc->State == HAL_ADC_STATE_EOC_INJ)
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_INJ_REG;  
      }
      else
      {
        /* Change ADC state */
        hadc->State = HAL_ADC_STATE_EOC_REG;
      }
    }
  }
  
  /* Conversion complete callback */
  HAL_ADC_ConvCpltCallback(hadc); 
}

/**
  * @brief  DMA half transfer complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma)   
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  /* Half conversion callback */
  HAL_ADC_ConvHalfCpltCallback(hadc); 
}

/**
  * @brief  DMA error callback 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void ADC_DMAError(DMA_HandleTypeDef *hdma)   
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef* hadc = ( ADC_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  /* Change ADC state */
  hadc->State = HAL_ADC_STATE_ERROR;
  
  /* Set ADC error code to DMA error */
  hadc->ErrorCode |= HAL_ADC_ERROR_DMA;
  
  /* Error callback */
  HAL_ADC_ErrorCallback(hadc); 
}

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;
  
  /* ADC enable and wait for ADC ready (in case of ADC is disabled or         */
  /* enabling phase not yet completed: flag ADC ready not yet set).           */
  /* Timeout implemented to not be stuck if ADC cannot be enabled (possible   */
  /* causes: ADC clock not running, ...).                                     */
  if (__HAL_ADC_IS_ENABLED(hadc) == RESET)
  {
    /* Check if conditions to enable the ADC are fulfilled */
    if (__HAL_ADC_ENABLING_CONDITIONS(hadc) == RESET)
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Set ADC error code to ADC IP internal error */
      hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
      
      return HAL_ERROR;
    }
    
    /* Enable the ADC peripheral */
    __HAL_ADC_ENABLE(hadc);
    
    /* Wait for ADC effectively enabled */
    tickstart = HAL_GetTick();  
    
    while(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_RDY) == RESET)
    {
      if((HAL_GetTick()-tickstart) > ADC_ENABLE_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Set ADC error code to ADC IP internal error */
        hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
      
        return HAL_ERROR;
      }
    }
  }
   
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Disable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;
  
  /* Verification if ADC is not already disabled:                             */
  /* Note: forbidden to disable ADC (set bit ADC_CR_ADDIS) if ADC is already  */
  /* disabled.                                                                */
  if (__HAL_ADC_IS_ENABLED(hadc) != RESET )
  {
    /* Check if conditions to disable the ADC are fulfilled */
    if (__HAL_ADC_DISABLING_CONDITIONS(hadc) != RESET)
    {
      /* Disable the ADC peripheral */
      __HAL_ADC_DISABLE(hadc);
    }
    else
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Set ADC error code to ADC IP internal error */
      hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
      
      return HAL_ERROR;
    }
     
    /* Wait for ADC effectively disabled */
    tickstart = HAL_GetTick();
    
    while(HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADEN))
    {
      if((HAL_GetTick()-tickstart) > ADC_DISABLE_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Set ADC error code to ADC IP internal error */
        hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
        
        return HAL_ERROR;
      }
    }
  }
  
  /* Return HAL status */
  return HAL_OK;
}


/**
  * @brief  Stop ADC conversion.
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped to disable the ADC.
  * @param  hadc: ADC handle
  * @param  ConversionGroup: ADC group regular and/or injected.
  *          This parameter can be one of the following values:
  *            @arg REGULAR_GROUP: ADC regular conversion type.
  *            @arg INJECTED_GROUP: ADC injected conversion type.
  *            @arg REGULAR_INJECTED_GROUP: ADC regular and injected conversion type.
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc, uint32_t ConversionGroup)
{
  uint32_t tmp_ADC_CR_ADSTART_JADSTART = 0;
  uint32_t tickstart = 0;
  uint32_t Conversion_Timeout_CPU_cycles = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CONVERSION_GROUP(ConversionGroup));
    
  /* Verification if ADC is not already stopped (on regular and injected      */
  /* groups) to bypass this function if not needed.                           */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(hadc))
  {
    /* Particular case of continuous auto-injection mode combined with        */
    /* auto-delay mode.                                                       */
    /* In auto-injection mode, regular group stop ADC_CR_ADSTP is used (not   */
    /* injected group stop ADC_CR_JADSTP).                                    */
    /* Procedure to be followed: Wait until JEOS=1, clear JEOS, set ADSTP=1   */
    /* (see reference manual).                                                */
    if ((HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CFGR_JAUTO)) 
         && (hadc->Init.ContinuousConvMode==ENABLE) 
         && (hadc->Init.LowPowerAutoWait==ENABLE))
    {
      /* Use stop of regular group */
      ConversionGroup = REGULAR_GROUP;
      
      /* Wait until JEOS=1 (maximum Timeout: 4 injected conversions) */
      while(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOS) == RESET)
      {
        if (Conversion_Timeout_CPU_cycles >= (ADC_CONVERSION_TIME_MAX_CPU_CYCLES *4))
        {
          /* Update ADC state machine to error */
          hadc->State = HAL_ADC_STATE_ERROR;
          
          /* Set ADC error code to ADC IP internal error */
          hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
          
          return HAL_ERROR;
        }
        Conversion_Timeout_CPU_cycles ++;
      }

      /* Clear JEOS */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOS);
    }
    
    /* Stop potential conversion on going on regular group */
    if (ConversionGroup != INJECTED_GROUP)
    {
      /* Software is allowed to set ADSTP only when ADSTART=1 and ADDIS=0 */
      if (HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADSTART) && 
          HAL_IS_BIT_CLR(hadc->Instance->CR, ADC_CR_ADDIS)     )
      {
        /* Stop conversions on regular group */
        hadc->Instance->CR |= ADC_CR_ADSTP;
      }
    }

    /* Stop potential conversion on going on injected group */
    if (ConversionGroup != REGULAR_GROUP)
    {
      /* Software is allowed to set JADSTP only when JADSTART=1 and ADDIS=0 */
      if (HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_JADSTART) && 
          HAL_IS_BIT_CLR(hadc->Instance->CR, ADC_CR_ADDIS)      )
      {
        /* Stop conversions on injected group */
        hadc->Instance->CR |= ADC_CR_JADSTP;
      }
    }

    /* Selection of start and stop bits in function of regular or injected group */
    switch(ConversionGroup)
    {
    case REGULAR_INJECTED_GROUP:
        tmp_ADC_CR_ADSTART_JADSTART = (ADC_CR_ADSTART | ADC_CR_JADSTART);
        break;
    case INJECTED_GROUP:
        tmp_ADC_CR_ADSTART_JADSTART = ADC_CR_JADSTART;
        break;
    /* Case REGULAR_GROUP */
    default:
        tmp_ADC_CR_ADSTART_JADSTART = ADC_CR_ADSTART;
        break;
    }
    
    /* Wait for conversion effectively stopped */
    tickstart = HAL_GetTick();
      
    while((hadc->Instance->CR & tmp_ADC_CR_ADSTART_JADSTART) != RESET)
    {
      if((HAL_GetTick()-tickstart) > ADC_STOP_CONVERSION_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Set ADC error code to ADC IP internal error */
        hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
        
        return HAL_ERROR;
      }
    }
    
  }
   
  /* Return HAL status */
  return HAL_OK;
}
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  uint32_t WaitLoopIndex = 0;
  uint32_t tickstart = 0;
  
  /* ADC enable and wait for ADC ready (in case of ADC is disabled or         */
  /* enabling phase not yet completed: flag ADC ready not yet set).           */
  /* Timeout implemented to not be stuck if ADC cannot be enabled (possible   */
  /* causes: ADC clock not running, ...).                                     */
  if (__HAL_ADC_IS_ENABLED(hadc) == RESET)
  {
    /* Enable the Peripheral */
    __HAL_ADC_ENABLE(hadc);
    
    /* Delay for ADC stabilization time.                                      */
    /* Delay fixed to worst case: maximum CPU frequency                       */
    while(WaitLoopIndex < ADC_STAB_DELAY_CPU_CYCLES)
    {
      WaitLoopIndex++;
    }
    
    /* Get timeout */
    tickstart = HAL_GetTick();
    
    /* Wait for ADC effectively enabled */
    while(HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_ADON))
    {
      if((HAL_GetTick()-tickstart) > ADC_ENABLE_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
      
        /* Set ADC error code to ADC IP internal error */
        hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
      
        return HAL_ERROR;
      }
    }
  }
   
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Stop ADC conversion and disable the selected ADC
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped to disable the ADC.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_ConversionStop_Disable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;
  
  /* Verification if ADC is not already disabled:                             */
  if (__HAL_ADC_IS_ENABLED(hadc) != RESET)
  {
    /* Disable the ADC peripheral */
    __HAL_ADC_DISABLE(hadc);
     
    /* Get timeout */
    tickstart = HAL_GetTick();
    
    /* Wait for ADC effectively disabled */
    while(__HAL_ADC_IS_ENABLED(hadc) != RESET)
    {
      if((HAL_GetTick()-tickstart) > ADC_ENABLE_TIMEOUT)
      {
        /* Update ADC state machine to error */
        hadc->State = HAL_ADC_STATE_ERROR;
        
        /* Set ADC error code to ADC IP internal error */
        hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
        
        return HAL_ERROR;
      }
    }
  }
  
  /* Return HAL status */
  return HAL_OK;
}
#endif /* STM32F373xC || STM32F378xx */  
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
