/**
  ******************************************************************************
  * @file    stm32l1xx_hal_adc.c
  * @author  MCD Application conversion
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of conversions of regular
  *             group, using 3 possible modes: polling, interruption or DMA.
  *           + Control functions
  *             ++ Analog Watchdog configuration
  *             ++ Channels configuration on regular group
  *           + State functions
  *             ++ ADC state machine management
  *             ++ Interrupts and flags management
  *          Other functions (extended functions) are available in file 
  *          "stm32l1xx_hal_adc_ex.c".
  *
  @verbatim
  ==============================================================================
                    ##### ADC specific features #####
  ==============================================================================
  [..] 
  (#) 12-bit, 10-bit, 8-bit or 6-bit configurable resolution

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
  
  (#) ADC calibration

  (#) ADC offset on injected channels
    
  (#) ADC supply requirements: 2.4 V to 3.6 V at full speed and down to 1.8 V at 
      slower speed.
  
  (#) ADC input range: from Vref– (connected to Vssa) to Vref+ (connected to 
      Vdda or to an external voltage reference).


                     ##### How to use this driver #####
  ==============================================================================
    [..]

    (#) Enable the ADC interface 
        As prerequisite, ADC clock must be configured at RCC top level.
        Two clocks settings are mandatory:
         - ADC clock (core clock):
            Example:
            Into HAL_ADC_MspInit() (recommended code location):
              __ADC1_CLK_ENABLE();

         - ADC clock (conversions clock): 
            Only one possible clock source: derived from HSI RC 16MHz oscillator
            (HSI).
            Example:
            Into HAL_ADC_MspInit() or with main setting of RCC:
              RCC_OscInitTypeDef   RCC_OscInitStructure;
              HAL_RCC_GetOscConfig(&RCC_OscInitStructure);
              RCC_OscInitStructure.OscillatorType = (... | RCC_OSCILLATORTYPE_HSI);
              RCC_OscInitStructure.HSIState = RCC_HSI_ON;
              RCC_OscInitStructure.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
              RCC_OscInitStructure.PLL.PLLState = RCC_PLL_NONE;
              RCC_OscInitStructure.PLL.PLLSource = ...
              RCC_OscInitStructure.PLL...
              HAL_RCC_OscConfig(&RCC_OscInitStructure);

            Note: ADC is connected directly to HSI RC 16MHz oscillator.
                  Therefore, RCC PLL setting has no impact on ADC.
                  PLL can be disabled (".PLL.PLLState = RCC_PLL_NONE") or 
                  enabled with HSI16 as clock source
                  (".PLL.PLLSource = RCC_PLLSOURCE_HSI") to be used as device 
                  main clock source SYSCLK.
                  The only mandatory setting is ".HSIState = RCC_HSI_ON"

            Note: ADC clock prescaler is configured at ADC level with
                  parameter "ClockPrescaler" using function HAL_ADC_Init().

    (#) ADC pins configuration
         (++) Enable the clock for the ADC GPIOs using the following function:
             __GPIOx_CLK_ENABLE();   
         (++) Configure these ADC pins in analog mode using HAL_GPIO_Init();  
  
     (#) Configure the ADC parameters (conversion resolution, data alignment,  
         continuous mode, ...) using the HAL_ADC_Init() function.

     (#) Activate the ADC peripheral using one of the start functions: 
         HAL_ADC_Start(), HAL_ADC_Start_IT(), HAL_ADC_Start_DMA().
  
     *** Channels configuration to regular group  ***
     ================================================
     [..]    
       (+) To configure the ADC regular group features, use 
           HAL_ADC_Init() and HAL_ADC_ConfigChannel() functions.
       (+) To read the ADC converted values, use the HAL_ADC_GetValue() function.
              
     *** DMA for regular group configuration ***
     =========================================== 
     [..]
       (+) To enable the DMA mode for regular group, use the  
           HAL_ADC_Start_DMA() function.
       (+) To enable the generation of DMA requests continuously at the end of 
           the last DMA transfer, use the HAL_ADC_Init() function.
  
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
#include "stm32l1xx_hal.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup ADC ADC
  * @brief ADC HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */

  /* Fixed timeout values for ADC calibration, enable settling time.          */
  /* Values defined to be higher than worst cases: low clocks freq,           */
  /* maximum prescaler.                                                       */
  /* Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock         */
  /* prescaler 4, sampling time 7.5 ADC clock cycles, resolution 12 bits.     */
  /* Unit: ms                                                                 */
  #define ADC_ENABLE_TIMEOUT              ((uint32_t) 2)
  #define ADC_DISABLE_TIMEOUT             ((uint32_t) 2)

  /* Delay for ADC stabilization time.                                        */
  /* Maximum delay is 3.5us (refer to device datasheet, parameter tSTAB).     */
  /* Delay in CPU cycles, fixed to worst case: maximum CPU frequency 32MHz to */
  /* have the minimum number of CPU cycles to fulfill this delay.             */
  #define ADC_STAB_DELAY_CPU_CYCLES       ((uint32_t)112)
/**
    * @}
    */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */
static void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_DMAError(DMA_HandleTypeDef *hdma);
/**
    * @}
    */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup ADC_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_Exported_Functions_Group1 Initialization/de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the ADC. 
      (+) De-initialize the ADC
@endverbatim
  * @{
  */

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
  uint32_t tmp_cr1 = 0;
  uint32_t tmp_cr2 = 0;
  
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
  assert_param(IS_ADC_EOC_SELECTION(hadc->Init.EOCSelection));
  assert_param(IS_ADC_AUTOWAIT(hadc->Init.LowPowerAutoWait));
  assert_param(IS_ADC_AUTOPOWEROFF(hadc->Init.LowPowerAutoPowerOff));
  assert_param(IS_ADC_CHANNELSBANK(hadc->Init.ChannelsBank));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_ADC_EXTTRIG(hadc->Init.ExternalTrigConv));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DMAContinuousRequests));
  
  if(hadc->Init.ScanConvMode != ADC_SCAN_DISABLE)
  {
    assert_param(IS_ADC_REGULAR_NB_CONV(hadc->Init.NbrOfConversion));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DiscontinuousConvMode));
    assert_param(IS_ADC_REGULAR_DISCONT_NUMBER(hadc->Init.NbrOfDiscConversion));
  }
      
  if(hadc->Init.ExternalTrigConv != ADC_SOFTWARE_START)
  {
    assert_param(IS_ADC_EXTTRIG_EDGE(hadc->Init.ExternalTrigConvEdge));
  }
  
  
  /* As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured    */
  /* at RCC top level.                                                        */
  /* Refer to header of this file for more details on clock enabling          */
  /* procedure.                                                               */

  /* Actions performed only if ADC is coming from state reset:                */
  /* - Initialization of ADC MSP                                              */
  if (hadc->State == HAL_ADC_STATE_RESET)
  {
    /* Enable SYSCFG clock to control the routing Interface (RI) */
    __SYSCFG_CLK_ENABLE();
  
    /* Init the low level hardware */
    HAL_ADC_MspInit(hadc);
  } 
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Initialize the ADC state */
    hadc->State = HAL_ADC_STATE_BUSY;

    /* Set ADC parameters */
    
    /* Configuration of common ADC clock: clock source HSI with selectable    */
    /* prescaler                                                              */
    MODIFY_REG(ADC->CCR                 ,
               ADC_CCR_ADCPRE           ,
               hadc->Init.ClockPrescaler );

    /* Configuration of ADC:                                                  */
    /*  - external trigger polarity                                           */
    /*  - End of conversion selection                                         */
    /*  - DMA continuous request                                              */
    /*  - Channels bank (Banks availability depends on devices categories)    */
    /*  - continuous conversion mode                                          */
    tmp_cr2 |= (hadc->Init.DataAlign                                   |
                hadc->Init.EOCSelection                                |
                __ADC_CR2_DMACONTREQ(hadc->Init.DMAContinuousRequests) |
                hadc->Init.ChannelsBank                                |
                __ADC_CR2_CONTINUOUS(hadc->Init.ContinuousConvMode)     );

    /* Enable external trigger if trigger selection is different of software  */
    /* start.                                                                 */
    /* Note: This configuration keeps the hardware feature of parameter       */
    /*       ExternalTrigConvEdge "trigger edge none" equivalent to           */
    /*       software start.                                                  */
    if (hadc->Init.ExternalTrigConv != ADC_SOFTWARE_START)
    {
      tmp_cr2 |= ( hadc->Init.ExternalTrigConv    |
                  hadc->Init.ExternalTrigConvEdge );
    }
    
    /* Parameters update conditioned to ADC state:                            */
    /* Parameters that can be updated only when ADC is disabled:              */
    /*  - delay selection (LowPowerAutoWait mode)                             */
    /*  - resolution                                                          */
    /*  - auto power off (LowPowerAutoPowerOff mode)                          */
    /*  - scan mode                                                           */
    /*  - discontinuous mode disable/enable                                   */
    /*  - discontinuous mode number of conversions                            */
    if ((__HAL_ADC_IS_ENABLED(hadc) == RESET))
    {
      tmp_cr2 |= hadc->Init.LowPowerAutoWait;
      
      tmp_cr1 |= (hadc->Init.Resolution                  |
                  hadc->Init.LowPowerAutoPowerOff        |
                  __ADC_CR1_SCAN(hadc->Init.ScanConvMode) );

      /* Enable discontinuous mode only if continuous mode is disabled */
      if ((hadc->Init.DiscontinuousConvMode == ENABLE) &&
          (hadc->Init.ContinuousConvMode == DISABLE)     )
      {    
        /* Enable discontinuous mode of regular group */ 
        /* Set the number of channels to be converted in discontinuous mode */
        tmp_cr1 |= ((ADC_CR1_DISCEN) |
                    __ADC_CR1_DISCONTINUOUS_NUM(hadc->Init.NbrOfDiscConversion));
      }
      
      /* Update ADC configuration register CR1 with previous settings */
        MODIFY_REG(hadc->Instance->CR1,
                   ADC_CR1_RES     |
                   ADC_CR1_PDI     |
                   ADC_CR1_PDD     |
                   ADC_CR1_DISCNUM |
                   ADC_CR1_DISCEN  |
                   ADC_CR1_SCAN       ,
                   tmp_cr1             );
    }
    
    /* Update ADC configuration register CR2 with previous settings */
    MODIFY_REG(hadc->Instance->CR2      ,
               __ADC_CR2_MASK_ADCINIT() ,
               tmp_cr2                   );
    
    /* Configuration of regular group sequencer:                              */
    /* - if scan mode is disabled, regular channels sequence length is set to */
    /*   0x00: 1 channel converted (channel on regular rank 1)                */
    /*   Parameter "NbrOfConversion" is discarded.                            */
    /*   Note: Scan mode is present by hardware on this device and, if        */
    /*   disabled, discards automatically nb of conversions. Anyway, nb of    */
    /*   conversions is forced to 0x00 for alignment over all STM32 devices.  */
    /* - if scan mode is enabled, regular channels sequence length is set to  */
    /*   parameter "NbrOfConversion"                                          */
    if (hadc->Init.ScanConvMode == ADC_SCAN_ENABLE)
    {
      MODIFY_REG(hadc->Instance->SQR1                    ,
                 ADC_SQR1_L                              ,
                 __ADC_SQR1_L(hadc->Init.NbrOfConversion) );
    }
    else
    {
      MODIFY_REG(hadc->Instance->SQR1,
                 ADC_SQR1_L          ,
                 0x00000000           );
    }
    
    /* Check back that ADC registers have effectively been configured to      */
    /* ensure of no potential problem of ADC core IP clocking.                */
    /* Check through register CR2 (excluding execution control bits ADON,     */
    /* JSWSTART, SWSTART and injected trigger bits JEXTEN and JEXTSEL).       */
    if ((READ_REG(hadc->Instance->CR2) & ~(ADC_CR2_ADON |
                                           ADC_CR2_SWSTART | ADC_CR2_JSWSTART |
                                           ADC_CR2_JEXTEN  | ADC_CR2_JEXTSEL   ))
         == tmp_cr2)
    {
      /* Set ADC error code to none */
      __HAL_ADC_CLEAR_ERRORCODE(hadc);
      
      /* Initialize the ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
    else
    {
      /* Update ADC state machine to error */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Set ADC error code to ADC IP internal error */
      hadc->ErrorCode |= HAL_ADC_ERROR_INTERNAL;
      
      tmpHALStatus = HAL_ERROR;
    }
    
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
    CLEAR_BIT(hadc->Instance->CR1, (ADC_CR1_OVRIE   | ADC_CR1_RES     | ADC_CR1_AWDEN  |
                                    ADC_CR1_JAWDEN  | ADC_CR1_PDI     | ADC_CR1_PDD    |
                                    ADC_CR1_DISCNUM | ADC_CR1_JDISCEN | ADC_CR1_DISCEN |
                                    ADC_CR1_JAUTO   | ADC_CR1_AWDSGL  | ADC_CR1_SCAN   |
                                    ADC_CR1_JEOCIE  | ADC_CR1_AWDIE   | ADC_CR1_EOCIE  |
                                    ADC_CR1_AWDCH                                       ));
    
    /* Reset register CR2 */
    __ADC_CR2_CLEAR(hadc);
    
    /* Reset register SMPR0 */
    __ADC_SMPR0_CLEAR(hadc);
    
    /* Reset register SMPR1 */
    CLEAR_BIT(hadc->Instance->SMPR1, (ADC_SMPR1_SMP29 | ADC_SMPR1_SMP28 | ADC_SMPR1_SMP27 | 
                                      ADC_SMPR1_SMP26 | ADC_SMPR1_SMP25 | ADC_SMPR1_SMP24 | 
                                      ADC_SMPR1_SMP23 | ADC_SMPR1_SMP22 | ADC_SMPR1_SMP21 |
                                      ADC_SMPR1_SMP20                                      ));

    /* Reset register SMPR2 */
    CLEAR_BIT(hadc->Instance->SMPR2, (ADC_SMPR2_SMP19 | ADC_SMPR2_SMP18 | ADC_SMPR2_SMP17 | 
                                      ADC_SMPR2_SMP16 | ADC_SMPR2_SMP15 | ADC_SMPR2_SMP14 | 
                                      ADC_SMPR2_SMP13 | ADC_SMPR2_SMP12 | ADC_SMPR2_SMP11 |
                                      ADC_SMPR2_SMP10                                      ));
    
    /* Reset register SMPR3 */
    CLEAR_BIT(hadc->Instance->SMPR3, (ADC_SMPR3_SMP9 | ADC_SMPR3_SMP8 | ADC_SMPR3_SMP7 | 
                                      ADC_SMPR3_SMP6 | ADC_SMPR3_SMP5 | ADC_SMPR3_SMP4 | 
                                      ADC_SMPR3_SMP3 | ADC_SMPR3_SMP2 | ADC_SMPR3_SMP1 |
                                      ADC_SMPR3_SMP0                                    ));
    
    /* Reset register JOFR1 */
    CLEAR_BIT(hadc->Instance->JOFR1, ADC_JOFR1_JOFFSET1);
    /* Reset register JOFR2 */
    CLEAR_BIT(hadc->Instance->JOFR2, ADC_JOFR2_JOFFSET2);
    /* Reset register JOFR3 */
    CLEAR_BIT(hadc->Instance->JOFR3, ADC_JOFR3_JOFFSET3);
    /* Reset register JOFR4 */
    CLEAR_BIT(hadc->Instance->JOFR4, ADC_JOFR4_JOFFSET4);
    
    /* Reset register HTR */
    CLEAR_BIT(hadc->Instance->HTR, ADC_HTR_HT);
    /* Reset register LTR */
    CLEAR_BIT(hadc->Instance->LTR, ADC_LTR_LT);
    
    /* Reset register SQR1 */
    CLEAR_BIT(hadc->Instance->SQR1, (ADC_SQR1_L | __ADC_SQR1_SQXX));
    
    /* Reset register SQR2 */
    CLEAR_BIT(hadc->Instance->SQR2, (ADC_SQR2_SQ24 | ADC_SQR2_SQ23 | ADC_SQR2_SQ22 | 
                                     ADC_SQR2_SQ21 | ADC_SQR2_SQ20 | ADC_SQR2_SQ19  ));
    
    /* Reset register SQR3 */
    CLEAR_BIT(hadc->Instance->SQR3, (ADC_SQR3_SQ18 | ADC_SQR3_SQ17 | ADC_SQR3_SQ16 | 
                                     ADC_SQR3_SQ15 | ADC_SQR3_SQ14 | ADC_SQR3_SQ13  ));
    
    /* Reset register SQR4 */
    CLEAR_BIT(hadc->Instance->SQR4, (ADC_SQR4_SQ12 | ADC_SQR4_SQ11 | ADC_SQR4_SQ10 | 
                                     ADC_SQR4_SQ9  | ADC_SQR4_SQ8  | ADC_SQR4_SQ7   ));
    
    /* Reset register SQR5 */
    CLEAR_BIT(hadc->Instance->SQR5, (ADC_SQR5_SQ6 | ADC_SQR5_SQ5 | ADC_SQR5_SQ4 | 
                                     ADC_SQR5_SQ3 | ADC_SQR5_SQ2 | ADC_SQR5_SQ1  ));
    
    
    /* Reset register JSQR */
    CLEAR_BIT(hadc->Instance->JSQR, (ADC_JSQR_JL |
                                     ADC_JSQR_JSQ4 | ADC_JSQR_JSQ3 | 
                                     ADC_JSQR_JSQ2 | ADC_JSQR_JSQ1  ));
    
    /* Reset register JSQR */
    CLEAR_BIT(hadc->Instance->JSQR, (ADC_JSQR_JL |
                                     ADC_JSQR_JSQ4 | ADC_JSQR_JSQ3 | 
                                     ADC_JSQR_JSQ2 | ADC_JSQR_JSQ1  ));
    
    /* Reset register DR */
    /* bits in access mode read only, no direct reset applicable*/
    
    /* Reset registers JDR1, JDR2, JDR3, JDR4 */
    /* bits in access mode read only, no direct reset applicable*/
    
    /* Reset register CCR */
    CLEAR_BIT(ADC->CCR, ADC_CCR_TSVREFE);   
    
    /* ========== Hard reset ADC peripheral ========== */
    /* Performs a global reset of the entire ADC peripheral: ADC state is     */
    /* forced to a similar state after device power-on.                       */
    /* If needed, copy-paste and uncomment the following reset code into      */
    /* function "void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)":              */
    /*                                                                        */
    /*  __ADC1_FORCE_RESET()                                                  */
    /*  __ADC1_RELEASE_RESET()                                                */
    
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

/** @defgroup ADC_Exported_Functions_Group2 IO operation functions
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
    if (__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc))
    {
      /* Start ADC conversion on regular group */
      SET_BIT(hadc->Instance->CR2, ADC_CR2_SWSTART);
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

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

/**
  * @brief  Wait for regular group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart = 0;
 
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Get timeout */
  tickstart = HAL_GetTick();
     
  /* Wait until End of Conversion flag is raised */
  while(HAL_IS_BIT_CLR(hadc->Instance->SR, ADC_FLAG_EOC))
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        /* Update ADC state machine to timeout */
        hadc->State = HAL_ADC_STATE_TIMEOUT;
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_ERROR;
      }
    }
  }
  
  /* Clear end of conversion flag of regular group if low power feature "Auto */
  /* Wait" is disabled, to not interfere with this feature until data         */
  /* register is read using function HAL_ADC_GetValue().                      */
  if (hadc->Init.LowPowerAutoWait == DISABLE)
  {
    /* Clear regular group conversion flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_STRT | ADC_FLAG_EOC);
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

/**
  * @brief  Poll for conversion event.
  * @param  hadc: ADC handle
  * @param  EventType: the ADC event type.
  *          This parameter can be one of the following values:
  *            @arg AWD_EVENT: ADC Analog watchdog event.
  *            @arg OVR_EVENT: ADC Overrun event
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart = 0; 

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_EVENT_TYPE(EventType));
  
  /* Get timeout */
  tickstart = HAL_GetTick();
      
  /* Check selected event flag */
  while(__HAL_ADC_GET_FLAG(hadc, EventType) == RESET)
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
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
  case AWD_EVENT:
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD;
      
    /* Clear ADC analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD);
    break;
  
  /* Overrun event */
  default: /* Case OVR_EVENT */
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_ERROR;
      
    /* Set ADC error code to overrun */
    hadc->ErrorCode |= HAL_ADC_ERROR_OVR;

    /* Clear ADC Overrun flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_OVR);
    break;
  }
    
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Enables ADC, starts conversion of regular group with interruption.
  *         Interruptions enabled in this function: EOC (end of conversion),
  *         overrun.
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
    __HAL_ADC_ENABLE_IT(hadc, (ADC_IT_EOC | ADC_IT_OVR));
    
    /* Start conversion of regular group if software start has been selected. */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    if (__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc))
    {
      /* Start ADC conversion on regular group */
      SET_BIT(hadc->Instance->CR2, ADC_CR2_SWSTART);
    }   
    
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

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

/**
  * @brief  Enables ADC, starts conversion of regular group and transfers result
  *         through DMA.
  *         Interruptions enabled in this function:
  *         overrun, DMA half transfer, DMA transfer complete. 
  *         Each of these interruptions has its dedicated callback function.
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

    /* Enable ADC overrun interrupt */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_OVR);
    
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
      SET_BIT(hadc->Instance->CR2, ADC_CR2_SWSTART);
    }
  }

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @note:  ADC peripheral disable is forcing interruption of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
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
    /* DMA transfer is on going)                                              */
    tmpHALStatus = HAL_DMA_Abort(hadc->DMA_Handle);
    
    /* Check if DMA channel effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
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
  if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_EOC))
  {
    if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOC) )
    {
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

      /* Disable interruption if no further conversion upcoming regular         */
      /* external trigger or by continuous mode                                 */
      if(__HAL_ADC_IS_SOFTWARE_START_REGULAR(hadc) && 
         (hadc->Init.ContinuousConvMode == DISABLE)  )
      {
        /* Disable ADC end of single conversion interrupt  */
        /* Note: Overrun interrupt was enabled with EOC interrupt in            */
        /* HAL_ADC_Start_IT(), but is not disabled here because can be used by  */
        /* overrun IRQ process below.                                           */
        __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC);
      }

      /* Conversion complete callback */
      HAL_ADC_ConvCpltCallback(hadc);
      
      /* Clear regular group conversion flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_STRT | ADC_FLAG_EOC);
    }
  }

  /* ========== Check End of Conversion flag for injected group ========== */
  if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_JEOC))
  {
    if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOC))
    {
      /* Update state machine on conversion status if not in error state */
      if(hadc->State != HAL_ADC_STATE_ERROR)
      {
        /* Update ADC state machine */
        if(hadc->State != HAL_ADC_STATE_EOC_INJ_REG)
        {

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
      
      /* Clear injected group conversion flag */
      __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_JSTRT | ADC_FLAG_JEOC));
    }
  }
   
  /* ========== Check Analog watchdog flags ========== */
  if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_AWD))
  {
    if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD))
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_AWD;
        
      /* Clear the ADCx's Analog watchdog flag */
      __HAL_ADC_CLEAR_FLAG(hadc,ADC_FLAG_AWD);
      
      /* Level out of window callback */ 
      HAL_ADC_LevelOutOfWindowCallback(hadc);
    }
  }
  
  /* ========== Check Overrun flag ========== */
  if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_OVR))
  {
    if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_OVR))
    {
      /* Change ADC state to error state */
      hadc->State = HAL_ADC_STATE_ERROR;
      
      /* Set ADC error code to overrun */
      hadc->ErrorCode |= HAL_ADC_ERROR_OVR;
      
      /* Error callback */ 
      HAL_ADC_ErrorCallback(hadc);
      
      /* Clear the Overrun flag */
      __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_OVR);
    }
  }
  
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
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_LevelOutOfWindowCallback must be implemented in the user file.
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
    MODIFY_REG(hadc->Instance->SQR5,
               __ADC_SQR5_RK(ADC_SQR5_SQ1, sConfig->Rank),
               __ADC_SQR5_RK(sConfig->Channel, sConfig->Rank) );
  }
  /* For Rank 7 to 12 */
  else if (sConfig->Rank < 13)
  {   
    MODIFY_REG(hadc->Instance->SQR4,
               __ADC_SQR4_RK(ADC_SQR4_SQ7, sConfig->Rank),
               __ADC_SQR4_RK(sConfig->Channel, sConfig->Rank) );
  }
  /* For Rank 13 to 18 */
  else if (sConfig->Rank < 19)
  {
    MODIFY_REG(hadc->Instance->SQR3,
               __ADC_SQR3_RK(ADC_SQR3_SQ13, sConfig->Rank),
               __ADC_SQR3_RK(sConfig->Channel, sConfig->Rank) );
  }
  /* For Rank 19 to 24 */
  else if (sConfig->Rank < 25)
  {
    MODIFY_REG(hadc->Instance->SQR2,
               __ADC_SQR2_RK(ADC_SQR2_SQ19, sConfig->Rank),
               __ADC_SQR2_RK(sConfig->Channel, sConfig->Rank) );
  }
  /* For Rank 25 to 28 */
  else
  {
    MODIFY_REG(hadc->Instance->SQR1,
               __ADC_SQR1_RK(ADC_SQR1_SQ25, sConfig->Rank),
               __ADC_SQR1_RK(sConfig->Channel, sConfig->Rank) );
  }
      
  
  /* Channel sampling time configuration */
  /* For channels 0 to 9 */
  if (sConfig->Channel < ADC_CHANNEL_10)
  {
    MODIFY_REG(hadc->Instance->SMPR3,
               __ADC_SMPR3(ADC_SMPR3_SMP0, sConfig->Channel),
               __ADC_SMPR3(sConfig->SamplingTime, sConfig->Channel) );
  }
  /* For channels 10 to 19 */
  else if (sConfig->Channel < ADC_CHANNEL_20)
  {
    MODIFY_REG(hadc->Instance->SMPR2,
               __ADC_SMPR2(ADC_SMPR2_SMP10, sConfig->Channel),
               __ADC_SMPR2(sConfig->SamplingTime, sConfig->Channel) );
  }
  /* For channels 20 to 26 for devices Cat.1, Cat.2, Cat.3 */
  /* For channels 20 to 29 for devices Cat4, Cat.5 */
  else if (sConfig->Channel <= ADC_SMPR1_CHANNEL_MAX)
  {
    MODIFY_REG(hadc->Instance->SMPR1,
               __ADC_SMPR1(ADC_SMPR1_SMP20, sConfig->Channel),
               __ADC_SMPR1(sConfig->SamplingTime, sConfig->Channel) );
  }
  /* For channels 30 to 31 for devices Cat4, Cat.5 */
  else
  {
    __ADC_SMPR0_CHANNEL_SET(hadc, sConfig->SamplingTime, sConfig->Channel);
  }

  /* If ADC1 Channel_16 or Channel_17 is selected, enable Temperature sensor  */
  /* and VREFINT measurement path.                                            */
  if ((sConfig->Channel == ADC_CHANNEL_TEMPSENSOR) ||
      (sConfig->Channel == ADC_CHANNEL_VREFINT)      )
  {
    SET_BIT(ADC->CCR, ADC_CCR_TSVREFE);
  }
   
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmpHALStatus;
}

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
  assert_param(IS_FUNCTIONAL_STATE(AnalogWDGConfig->ITMode));
  assert_param(IS_ADC_RANGE(AnalogWDGConfig->HighThreshold));
  assert_param(IS_ADC_RANGE(AnalogWDGConfig->LowThreshold));
  
  if((AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REG)     ||
     (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_INJEC)   ||
     (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)  )
  {
    assert_param(IS_ADC_CHANNEL(AnalogWDGConfig->Channel));
  }
  
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


/**
  * @}
  */


/** @defgroup ADC_Exported_Functions_Group4 Peripheral State functions
 *  @brief    Peripheral State functions
 *
@verbatim
 ===============================================================================
            ##### Peripheral State and Errors functions #####
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

/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */

/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  uint32_t wait_loop_index = 0;
  uint32_t tickstart = 0;
  
  /* ADC enable and wait for ADC ready (in case of ADC is disabled or         */
  /* enabling phase not yet completed: flag ADC ready not yet set).           */
  /* Timeout implemented to not be stuck if ADC cannot be enabled (possible   */
  /* causes: ADC clock not running, ...).                                     */
  if (__HAL_ADC_IS_ENABLED(hadc) == RESET)
  {
    /* Enable the Peripheral */
    __ADC_ENABLE(hadc);
    
    /* Delay for ADC stabilization time.                                      */
    /* Delay fixed to worst case: maximum CPU frequency                       */
    while(wait_loop_index < ADC_STAB_DELAY_CPU_CYCLES)
    {
      wait_loop_index++;
    }
    
    /* Get timeout */
    tickstart = HAL_GetTick();    

    /* Wait for ADC effectively enabled */
    while(__HAL_ADC_IS_ENABLED(hadc) == RESET)
    {
      if((HAL_GetTick() - tickstart ) > ADC_ENABLE_TIMEOUT)
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
HAL_StatusTypeDef ADC_ConversionStop_Disable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;
  
  /* Verification if ADC is not already disabled:                             */
  if (__HAL_ADC_IS_ENABLED(hadc) != RESET)
  {
    /* Disable the ADC peripheral */
    __ADC_DISABLE(hadc);
     
    /* Get timeout */
    tickstart = HAL_GetTick();
    
    /* Wait for ADC effectively disabled */    
    while(__HAL_ADC_IS_ENABLED(hadc) != RESET)
    {
      if((HAL_GetTick() - tickstart ) > ADC_DISABLE_TIMEOUT)
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
