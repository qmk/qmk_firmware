/**
  ******************************************************************************
  * @file    stm32f0xx_hal_adc.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization and de-initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of conversions of regular group,
  *             using 3 possible modes: polling, interruption or DMA.
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
  (#) 12-bit, 10-bit, 8-bit or 6-bit configurable resolution

  (#) Interrupt generation at the end of regular conversion and in case of 
      analog watchdog or overrun events.
  
  (#) Single and continuous conversion modes.
  
  (#) Scan mode for automatic conversion of channel 0 to channel 'n'.
  
  (#) Data alignment with in-built data coherency.
  
  (#) Programmable sampling time.
  
  (#) ADC conversion group Regular.

  (#) External trigger (timer or EXTI) with configurable polarity.

  (#) DMA request generation for transfer of conversions data of regular group.

  (#) ADC calibration
  
  (#) ADC supply requirements: 2.4 V to 3.6 V at full speed and down to 1.8 V at 
      slower speed.
  
  (#) ADC input range: from Vref minus (connected to Vssa) to Vref plus (connected to 
      Vdda or to an external voltage reference).


                     ##### How to use this driver #####
  ==============================================================================
    [..]

    (#) Enable the ADC interface 
        (++) As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured  
        at RCC top level: clock source and clock prescaler.
        (++)Two possible clock sources: synchronous clock derived from APB clock
        or asynchronous clock derived from ADC dedicated HSI RC oscillator
        14MHz.
        (++)Example:
          __ADC1_CLK_ENABLE();                         (mandatory)
          
          HI14 enable or let under control of ADC:     (optional)

          RCC_OscInitTypeDef   RCC_OscInitStructure;
          RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSI14;
          RCC_OscInitStructure.HSI14CalibrationValue = RCC_HSI14CALIBRATION_DEFAULT;
          RCC_OscInitStructure.HSI14State = RCC_HSI14_ADC_CONTROL;
          RCC_OscInitStructure.PLL...   (optional if used for system clock)
          HAL_RCC_OscConfig(&RCC_OscInitStructure);
          
          Parameter "HSI14State" must be set either:
           - to "...HSI14State = RCC_HSI14_ADC_CONTROL" to let the ADC control 
             the HSI14 oscillator enable/disable (if not used to supply the main 
             system clock): feature used if ADC mode LowPowerAutoPowerOff is 
             enabled.
           - to "...HSI14State = RCC_HSI14_ON" to maintain the HSI14 oscillator
             always enabled: can be used to supply the main system clock.

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
       (+) To activate the continuous mode, use the HAL_ADC_Init() function.   
       (+) To read the ADC converted values, use the HAL_ADC_GetValue() function.
              
     *** DMA for regular configuration ***
     ============================================================= 
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
#include "stm32f0xx_hal.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @defgroup ADC ADC HAL module driver
  * @brief ADC HAL module driver
  * @{
  */

#ifdef HAL_ADC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */

  /* Fixed timeout values for ADC calibration, enable settling time, disable  */
  /* settling time.                                                           */
  /* Values defined to be higher than worst cases: low clock frequency,       */
  /* maximum prescaler.                                                       */
  /* Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock         */
  /* prescaler 4, sampling time 7.5 ADC clock cycles, resolution 12 bits.     */
  /* Unit: ms                                                                 */
  #define ADC_ENABLE_TIMEOUT             ((uint32_t) 2)
  #define ADC_DISABLE_TIMEOUT            ((uint32_t) 2)
  #define ADC_STOP_CONVERSION_TIMEOUT    ((uint32_t) 2)

  /* Delay for temperature sensor stabilization time.                         */
  /* Maximum delay is 10us (refer to device datasheet, parameter tSTART).     */
  /* Delay in CPU cycles, fixed to worst case: maximum CPU frequency 48MHz to */
  /* have the minimum number of CPU cycles to fulfill this delay.             */
  #define ADC_TEMPSENSOR_DELAY_CPU_CYCLES ((uint32_t) 480)

  /* Delay for ADC stabilization time.                                        */
  /* Maximum delay is 1us (refer to device datasheet, parameter tSTAB).       */
  /* Delay in CPU cycles, fixed to worst case: maximum CPU frequency 48MHz to */
  /* have the minimum number of CPU cycles to fulfill this delay.             */
  #define ADC_STAB_DELAY_CPU_CYCLES       ((uint32_t)48)
/**
    * @}
    */
  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
static HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc);
static HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc);
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
  *         depending on both possible clock sources: APB clock of HSI clock.
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
  uint32_t tmpCFGR1 = 0;

  /* Check ADC handle */
  if(hadc == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CLOCKPRESCALER(hadc->Init.ClockPrescaler));
  assert_param(IS_ADC_RESOLUTION(hadc->Init.Resolution));
  assert_param(IS_ADC_DATA_ALIGN(hadc->Init.DataAlign)); 
  assert_param(IS_ADC_SCAN_MODE(hadc->Init.ScanConvMode));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DiscontinuousConvMode));
  assert_param(IS_ADC_EXTTRIG_EDGE(hadc->Init.ExternalTrigConvEdge));   
  assert_param(IS_ADC_EXTTRIG(hadc->Init.ExternalTrigConv));   
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DMAContinuousRequests));
  assert_param(IS_ADC_EOC_SELECTION(hadc->Init.EOCSelection));
  assert_param(IS_ADC_OVERRUN(hadc->Init.Overrun));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.LowPowerAutoWait));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.LowPowerAutoPowerOff));
  
  /* As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured    */
  /* at RCC top level depending on both possible clock sources:               */
  /* APB clock or HSI clock.                                                  */
  /* Refer to header of this file for more details on clock enabling procedure*/
  
  /* Actions performed only if ADC is coming from state reset:                */
  /* - Initialization of ADC MSP                                              */
  /* - ADC voltage regulator enable                                           */
  if (hadc->State == HAL_ADC_STATE_RESET)
  {
    /* Init the low level hardware */
    HAL_ADC_MspInit(hadc);
    
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
    
    /* Parameters update conditioned to ADC state:                            */
    /* Parameters that can be updated only when ADC is disabled:              */
    /*  - ADC clock mode                                                      */
    /*  - ADC clock prescaler                                                 */
    if (__HAL_ADC_IS_ENABLED(hadc) == RESET)
    {
      /* Some parameters of this register are not reset, since they are set   */
      /* by other functions and must be kept in case of usage of this         */
      /* function on the fly (update of a parameter of ADC_InitTypeDef        */
      /* without needing to reconfigure all other ADC groups/channels         */
      /* parameters):                                                         */
      /*   - internal measurement paths: Vbat, temperature sensor, Vref       */
      /*     (set into HAL_ADC_ConfigChannel() )                              */
     
      /* Reset configuration of ADC configuration register CFGR2:             */
      /*   - ADC clock mode: CKMODE                                           */
      hadc->Instance->CFGR2 &= ~(ADC_CFGR2_CKMODE);
      
      /* Configuration of ADC clock mode: clock source AHB or HSI with        */
      /* selectable prescaler                                                 */
      hadc->Instance->CFGR2 |= hadc->Init.ClockPrescaler;
    }
      
    /* Configuration of ADC:                                                  */
    /*  - discontinuous mode                                                  */
    /*  - LowPowerAutoWait mode                                               */
    /*  - LowPowerAutoPowerOff mode                                           */
    /*  - continuous conversion mode                                          */
    /*  - overrun                                                             */
    /*  - external trigger to start conversion                                */
    /*  - external trigger polarity                                           */
    /*  - data alignment                                                      */
    /*  - resolution                                                          */
    /*  - scan direction                                                      */
    /*  - DMA continuous request                                              */
    hadc->Instance->CFGR1 &= ~( ADC_CFGR1_DISCEN  |
                                ADC_CFGR1_AUTOFF  |
                                ADC_CFGR1_AUTDLY  |
                                ADC_CFGR1_CONT    |
                                ADC_CFGR1_OVRMOD  |
                                ADC_CFGR1_EXTSEL  |
                                ADC_CFGR1_EXTEN   |
                                ADC_CFGR1_ALIGN   |
                                ADC_CFGR1_RES     |
                                ADC_CFGR1_SCANDIR |
                                ADC_CFGR1_DMACFG   );

    tmpCFGR1 |= (__HAL_ADC_CFGR1_AUTOWAIT(hadc->Init.LowPowerAutoWait)       |
                 __HAL_ADC_CFGR1_AUTOOFF(hadc->Init.LowPowerAutoPowerOff)    |
                 __HAL_ADC_CFGR1_CONTINUOUS(hadc->Init.ContinuousConvMode)   |
                 __HAL_ADC_CFGR1_OVERRUN(hadc->Init.Overrun)                 |
                 hadc->Init.DataAlign                                        |
                 hadc->Init.Resolution                                       |
                 __HAL_ADC_CFGR1_SCANDIR(hadc->Init.ScanConvMode)            |
                 __HAL_ADC_CFGR1_DMACONTREQ(hadc->Init.DMAContinuousRequests) );
    
    /* Enable discontinuous mode only if continuous mode is disabled */
    if ((hadc->Init.DiscontinuousConvMode == ENABLE) &&
        (hadc->Init.ContinuousConvMode == DISABLE)     )
    {
      /* Enable discontinuous mode of regular group */ 
      tmpCFGR1 |= ADC_CFGR1_DISCEN;
    }
      
    /* Enable external trigger if trigger selection is different of software  */
    /* start.                                                                 */
    /* @Note: This configuration keeps the hardware feature of parameter       */
    /*       ExternalTrigConvEdge "trigger edge none" equivalent to           */
    /*       software start.                                                  */
    if (hadc->Init.ExternalTrigConv != ADC_SOFTWARE_START)
    {
      tmpCFGR1 |= ( hadc->Init.ExternalTrigConv    |
                    hadc->Init.ExternalTrigConvEdge );
    }
    
    /* Update ADC configuration register with previous settings */
    hadc->Instance->CFGR1 |= tmpCFGR1;
    
    /* Check back that ADC registers have effectively been configured to      */
    /* ensure of no potential problem of ADC core IP clocking.                */
    /* Check through register CFGR1 (excluding analog watchdog configuration: */
    /* set into separate dedicated function).                                 */
    if ((hadc->Instance->CFGR1 & ~(ADC_CFGR1_AWDCH | ADC_CFGR1_AWDEN | ADC_CFGR1_AWDSGL))
         == tmpCFGR1)
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
  * @brief  Deinitialize the ADC peripheral registers to their default reset
  *         values, with deinitialization of the ADC MSP.
  * @note   For devices with several ADCs: reset of ADC common registers is done 
  *         only if all ADCs sharing the same common group are disabled.
  *         If this is not the case, reset of these common parameters reset is  
  *         bypassed without error reporting: it can be the intended behaviour in
  *         case of reset of a single ADC while the other ADCs sharing the same 
  *         common group is still running.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check ADC handle */
  if(hadc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Change ADC state */
  hadc->State = HAL_ADC_STATE_BUSY;
  
  /* Stop potential conversion on going, on regular group */
  tmpHALStatus = ADC_ConversionStop(hadc);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {   
    /* Disable the ADC peripheral */
    tmpHALStatus = ADC_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_READY;
    }
  }
  
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (tmpHALStatus != HAL_ERROR)
  {
  
    /* ========== Reset ADC registers ========== */
    /* Reset register IER */
    __HAL_ADC_DISABLE_IT(hadc, (ADC_IT_AWD   | ADC_IT_OVR  |
                                ADC_IT_EOS   | ADC_IT_EOC  |
                                ADC_IT_EOSMP | ADC_IT_RDY   ) );
        
    /* Reset register ISR */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_AWD   | ADC_FLAG_OVR  |
                                ADC_FLAG_EOS   | ADC_FLAG_EOC  |
                                ADC_FLAG_EOSMP | ADC_FLAG_RDY   ) );
      
    /* Reset register CR */
    /* Bits ADC_CR_ADCAL, ADC_CR_ADSTP, ADC_CR_ADSTART are in access mode     */
    /* "read-set": no direct reset applicable.                                */

    /* Reset register CFGR1 */
    hadc->Instance->CFGR1 &= ~(ADC_CFGR1_AWDCH   | ADC_CFGR1_AWDEN  | ADC_CFGR1_AWDSGL | ADC_CFGR1_DISCEN |
                               ADC_CFGR1_AUTOFF  | ADC_CFGR1_WAIT   | ADC_CFGR1_CONT   | ADC_CFGR1_OVRMOD |     
                               ADC_CFGR1_EXTEN   | ADC_CFGR1_EXTSEL | ADC_CFGR1_ALIGN  | ADC_CFGR1_RES    |
                               ADC_CFGR1_SCANDIR | ADC_CFGR1_DMACFG | ADC_CFGR1_DMAEN                      );
    
    /* Reset register CFGR2 */
    /* @Note: Update of ADC clock mode is conditioned to ADC state disabled:   */
    /*       already done above.                                              */
    hadc->Instance->CFGR2 &= ~ADC_CFGR2_CKMODE;
    
    /* Reset register SMPR */
    hadc->Instance->SMPR &= ~ADC_SMPR_SMP;
    
    /* Reset register TR1 */
    hadc->Instance->TR &= ~(ADC_TR_HT | ADC_TR_LT);
    
    /* Reset register CHSELR */
    hadc->Instance->CHSELR &= ~(ADC_CHSELR_CHSEL18 | ADC_CHSELR_CHSEL17 | ADC_CHSELR_CHSEL16 |
                                ADC_CHSELR_CHSEL15 | ADC_CHSELR_CHSEL14 | ADC_CHSELR_CHSEL13 | ADC_CHSELR_CHSEL12 |
                                ADC_CHSELR_CHSEL11 | ADC_CHSELR_CHSEL10 | ADC_CHSELR_CHSEL9  | ADC_CHSELR_CHSEL8  |
                                ADC_CHSELR_CHSEL7  | ADC_CHSELR_CHSEL6  | ADC_CHSELR_CHSEL5  | ADC_CHSELR_CHSEL4  |
                                ADC_CHSELR_CHSEL3  | ADC_CHSELR_CHSEL2  | ADC_CHSELR_CHSEL1  | ADC_CHSELR_CHSEL0   );
    
    /* Reset register DR */
    /* bits in access mode read only, no direct reset applicable*/
    
    /* Reset register CCR */
    ADC->CCR &= ~( ADC_CCR_VBATEN |
                   ADC_CCR_TSEN   |
                   ADC_CCR_VREFEN  );

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

  /* Perform ADC enable and conversion start if no conversion is on going */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)
  {
    /* Process locked */
    __HAL_LOCK(hadc);
      
    /* Enable the ADC peripheral */
    /* If low power mode AutoPowerOff is enabled, power-on/off phases are     */
    /* performed automatically by hardware.                                   */
    if (hadc->Init.LowPowerAutoPowerOff != ENABLE)
    {
      tmpHALStatus = ADC_Enable(hadc);
    }
    
    /* Start conversion if ADC is effectively enabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* State machine update: Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;

      /* Set ADC error code to none */
      __HAL_ADC_CLEAR_ERRORCODE(hadc);
      
      /* Clear regular group conversion flag and overrun flag */
      /* (To ensure of no unknown state from potential previous ADC           */
      /* operations)                                                          */
      __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS | ADC_FLAG_OVR));
      
      /* Enable conversion of regular group.                                  */
      /* If software start has been selected, conversion starts immediately.  */
      /* If external trigger has been selected, conversion will start at next */
      /* trigger event.                                                       */
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  else
  {
    tmpHALStatus = HAL_BUSY;
  }
  
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Stop ADC conversion of regular group, disable ADC peripheral.
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
  
  /* 1. Stop potential conversion on going, on regular group */
  tmpHALStatus = ADC_ConversionStop(hadc);
  
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
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_EOC_REG;
  }
  
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Poll for conversion event.
  * @param  hadc: ADC handle
  * @param  EventType: the ADC event type.
  *          This parameter can be one of the following values:
  *            @arg AWD_EVENT: ADC Analog watchdog event
  *            @arg OVR_EVENT: ADC Overrun event
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart=0; 

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
  case AWD_EVENT:
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD;
      
    /* Clear ADC analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD);
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

/**
  * @brief  Enables ADC, starts conversion of regular group with interruption.
  *         Interruptions enabled in this function:
  *          - EOC (end of conversion of regular group) or EOS (end of 
  *            sequence of regular group) depending on ADC initialization 
  *            parameter "EOCSelection"
  *          - overrun (if available)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmpHALStatus = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
    
  /* Perform ADC enable and conversion start if no conversion is on going */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)
  {
    /* Process locked */
    __HAL_LOCK(hadc);
     
    /* Enable the ADC peripheral */
    /* If low power mode AutoPowerOff is enabled, power-on/off phases are     */
    /* performed automatically by hardware.                                   */
    if (hadc->Init.LowPowerAutoPowerOff != ENABLE)
    {
      tmpHALStatus = ADC_Enable(hadc);
    }
    
    /* Start conversion if ADC is effectively enabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* State machine update: Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
      
      /* Set ADC error code to none */
      __HAL_ADC_CLEAR_ERRORCODE(hadc);
      
      /* Clear regular group conversion flag and overrun flag */
      /* (To ensure of no unknown state from potential previous ADC           */
      /* operations)                                                          */
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
      
      /* Enable conversion of regular group.                                  */
      /* If software start has been selected, conversion starts immediately.  */
      /* If external trigger has been selected, conversion will start at next */
      /* trigger event.                                                       */
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  else
  {
    tmpHALStatus = HAL_BUSY;
  }    
    
  /* Return function status */
  return tmpHALStatus;
}


/**
  * @brief  Stop ADC conversion of regular group, disable interruption of 
  *         end-of-conversion, disable ADC peripheral.
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
  
  /* 1. Stop potential conversion on going, on regular group */
  tmpHALStatus = ADC_ConversionStop(hadc);
  
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

/**
  * @brief  Enables ADC, starts conversion of regular group and transfers result
  *         through DMA.
  *         Interruptions enabled in this function:
  *          - DMA transfer complete
  *          - DMA half transfer
  *          - overrun
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

  /* Perform ADC enable and conversion start if no conversion is on going */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)
  {
    /* Process locked */
    __HAL_LOCK(hadc);

    /* Enable the ADC peripheral */
    /* If low power mode AutoPowerOff is enabled, power-on/off phases are       */
    /* performed automatically by hardware.                                     */
    if (hadc->Init.LowPowerAutoPowerOff != ENABLE)
    {
      tmpHALStatus = ADC_Enable(hadc);
    }
    
    /* Start conversion if ADC is effectively enabled */
    if (tmpHALStatus != HAL_ERROR)
    {
      /* State machine update: Change ADC state */
      hadc->State = HAL_ADC_STATE_BUSY_REG;
      
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
      hadc->Instance->CFGR1 |= ADC_CFGR1_DMAEN;
      
      /* Start the DMA channel */
      HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DR, (uint32_t)pData, Length);
           
      /* Enable conversion of regular group.                                  */
      /* If software start has been selected, conversion starts immediately.  */
      /* If external trigger has been selected, conversion will start at next */
      /* trigger event.                                                       */
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  else
  {
    tmpHALStatus = HAL_BUSY;
  }
    
  /* Return function status */
  return tmpHALStatus;
}

/**
  * @brief  Stop ADC conversion of regular group, disable ADC DMA transfer, disable 
  *         ADC peripheral.
  *         Each of these interruptions has its dedicated callback function.
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
  
  /* 1. Stop potential conversion on going, on regular group */
  tmpHALStatus = ADC_ConversionStop(hadc);
  
  /* Disable ADC peripheral if conversions are effectively stopped */
  if (tmpHALStatus != HAL_ERROR)
  {
    /* Disable ADC DMA (ADC DMA configuration ADC_CFGR_DMACFG is kept) */
    hadc->Instance->CFGR1 &= ~ADC_CFGR1_DMAEN;
    
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

/**
  * @brief  Get ADC regular group conversion result.
  * @note   Reading DR register automatically clears EOC (end of conversion of
  *         regular group) flag.
  *         Additionally, this functions clears EOS (end of sequence of
  *         regular group) flag, in case of the end of the sequence is reached.
  * @param  hadc: ADC handle
  * @retval Converted value
  */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* @Note: EOC flag is not cleared here by software because automatically     */
  /*       cleared by hardware when reading register DR.                      */
  
  /* Clear regular group end of sequence flag */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOS);
  
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
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_EOC_REG;
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
      /* Change ADC state */
      hadc->State = HAL_ADC_STATE_EOC_REG;
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
          /* @Note: Overrun interrupt was enabled with EOC interrupt in        */
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
    /* @Note: into callback, to determine if conversion has been triggered     */
    /*       from EOC or EOS, possibility to use:                             */
    /*        " if( __HAL_ADC_GET_FLAG(&hadc, ADC_FLAG_EOS)) "                */
      HAL_ADC_ConvCpltCallback(hadc);

    
    /* Clear regular group conversion flag */
    /* @Note: in case of overrun set to OVR_DATA_PRESERVED, end of conversion  */
    /*       flags clear induces the release of the preserved data.           */
    /*       Therefore, if the preserved data value is needed, it must be     */
    /*       read preliminarily into HAL_ADC_ConvCpltCallback().              */
    __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS) );
  }
   
  /* ========== Check Analog watchdog flags ========== */
  if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD) && __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_AWD))
  {
    /* Change ADC state */
    hadc->State = HAL_ADC_STATE_AWD;

    /* Level out of window callback */ 
    HAL_ADC_LevelOutOfWindowCallback(hadc);
    
    /* Clear ADC Analog watchdog flag */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD);
   
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
    if ((hadc->Init.Overrun == OVR_DATA_PRESERVED)            ||
        HAL_IS_BIT_SET(hadc->Instance->CFGR1, ADC_CFGR1_DMAEN)  )
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
  *         VrefInt/Vbat/TempSensor.
  *         Sampling time constraints must be respected (sampling time can be 
  *         adjusted in function of ADC clock frequency and sampling time 
  *         setting).
  *         Refer to device datasheet for timings values, parameters TS_vrefint,
  *         TS_vbat, TS_temp (values rough order: 5us to 17us).
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
  __IO uint32_t wait_loop_index = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_ADC_CHANNEL(sConfig->Channel));
  assert_param(IS_ADC_RANK(sConfig->Rank));
  assert_param(IS_ADC_SAMPLE_TIME(sConfig->SamplingTime));

  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on regular group:                                    */
  /*  - Channel number                                                        */
  /*  - Channel sampling time                                                 */
  /*  - Management of internal measurement channels: Vbat/VrefInt/TempSensor  */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)
  {
    /* Configure channel: depending on rank setting, add it or remove it from */
    /* ADC conversion sequencer.                                              */
    if (sConfig->Rank != ADC_RANK_NONE)
    {
      /* Regular sequence configuration */
      /* Set the channel selection register from the selected channel */
      hadc->Instance->CHSELR |= __HAL_ADC_CHSELR_CHANNEL(sConfig->Channel);
      
      /* Channel sampling time configuration */
      /* Modify sampling time if needed (not needed in case of reoccurrence   */
      /* for several channels programmed consecutively into the sequencer)    */
      if (sConfig->SamplingTime != __HAL_ADC_GET_SAMPLINGTIME(hadc))
      {
        /* Channel sampling time configuration */
        /* Clear the old sample time */
        hadc->Instance->SMPR &= ~(ADC_SMPR_SMP);
        
        /* Set the new sample time */
        hadc->Instance->SMPR |= (sConfig->SamplingTime);
      }

      /* Management of internal measurement channels: Vbat/VrefInt/TempSensor */
      /* internal measurement paths enable: If internal channel selected,     */
      /* enable dedicated internal buffers and path.                          */
      /* @Note: these internal measurement paths can be disabled using         */
      /* HAL_ADC_DeInit() or removing the channel from sequencer with         */
      /* channel configuration parameter "Rank".                              */

      /* If Channel_16 is selected, enable Temp. sensor measurement path. */
      if (sConfig->Channel == ADC_CHANNEL_TEMPSENSOR)
      {
        ADC->CCR |= ADC_CCR_TSEN;
        
        /* Delay for temperature sensor stabilization time */
        while(wait_loop_index < ADC_TEMPSENSOR_DELAY_CPU_CYCLES)
        {
          wait_loop_index++;
        }
      }
      /* If Channel_17 is selected, enable VBAT measurement path. */
      else if (sConfig->Channel == ADC_CHANNEL_VBAT)
      {
        ADC->CCR |= ADC_CCR_VBATEN;
      }
      /* If Channel_18 is selected, enable VREFINT measurement path. */
      else if (sConfig->Channel == ADC_CHANNEL_VREFINT)
      {
        ADC->CCR |= ADC_CCR_VREFEN;
      }

    }
    else
    {
      /* Regular sequence configuration */
      /* Reset the channel selection register from the selected channel */
      hadc->Instance->CHSELR &= ~__HAL_ADC_CHSELR_CHANNEL(sConfig->Channel);
      
      /* Management of internal measurement channels: Vbat/VrefInt/TempSensor */
      /* internal measurement paths disable: If internal channel selected,    */
      /* disable dedicated internal buffers and path.                         */

      /* If Channel_16 is selected, disable Temp. sensor measurement path. */
      if (sConfig->Channel == ADC_CHANNEL_TEMPSENSOR)
      {
        ADC->CCR &= ~ADC_CCR_TSEN;
      }
      /* If Channel_17 is selected, disable VBAT measurement path. */
      else if (sConfig->Channel == ADC_CHANNEL_VBAT)
      {
        ADC->CCR &= ~ADC_CCR_VBATEN;
      }
      /* If Channel_18 is selected, disable VREFINT measurement path. */
      else if (sConfig->Channel == ADC_CHANNEL_VREFINT)
      {
        ADC->CCR &= ~ADC_CCR_VREFEN;
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
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  assert_param(IS_FUNCTIONAL_STATE(AnalogWDGConfig->ITMode));

  /* Verify if threshold is within the selected ADC resolution */
  assert_param(IS_ADC_RANGE(__HAL_ADC_GET_RESOLUTION(hadc), AnalogWDGConfig->HighThreshold));
  assert_param(IS_ADC_RANGE(__HAL_ADC_GET_RESOLUTION(hadc), AnalogWDGConfig->LowThreshold));

  if(AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REG)
  {
    assert_param(IS_ADC_CHANNEL(AnalogWDGConfig->Channel));
  }
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated when ADC is disabled or enabled without   */
  /* conversion on going on regular group:                                    */
  /*  - Analog watchdog channels                                              */
  /*  - Analog watchdog thresholds                                            */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)
  {
    /* Configuration of analog watchdog:                                      */
    /*  - Set the analog watchdog enable mode: one or overall group of        */
    /*    channels.                                                           */
    /*  - Set the Analog watchdog channel (is not used if watchdog            */
    /*    mode "all channels": ADC_CFGR_AWD1SGL=0).                           */
    hadc->Instance->CFGR1 &= ~( ADC_CFGR1_AWDSGL |
                                ADC_CFGR1_AWDEN  |
                                ADC_CFGR1_AWDCH   );
    
    hadc->Instance->CFGR1 |= ( AnalogWDGConfig->WatchdogMode                 |
                               __HAL_ADC_CFGR_AWDCH(AnalogWDGConfig->Channel) );

    /* Shift the offset in function of the selected ADC resolution: Thresholds*/
    /* have to be left-aligned on bit 11, the LSB (right bits) are set to 0   */
    tmpAWDHighThresholdShifted = __HAL_ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(hadc, AnalogWDGConfig->HighThreshold);
    tmpAWDLowThresholdShifted  = __HAL_ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(hadc, AnalogWDGConfig->LowThreshold);
    
    /* Set the high and low thresholds */
    hadc->Instance->TR &= ~(ADC_TR_HT | ADC_TR_LT);
    hadc->Instance->TR |=  ( __HAL_ADC_TRX_HIGHTHRESHOLD (tmpAWDHighThresholdShifted) |
                             tmpAWDLowThresholdShifted                                 );
    
    /* Clear the ADC Analog watchdog flag (in case of left enabled by         */
    /* previous ADC operations) to be ready to use for HAL_ADC_IRQHandler()   */
    /* or HAL_ADC_PollForEvent().                                             */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_IT_AWD);
    
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
    
  }
  /* If a conversion is on going on regular group, no update could be done    */
  /* on neither of the AWD configuration structure parameters.                */
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
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;
  __IO uint32_t wait_loop_index = 0;
  
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
    
    /* Delay for ADC stabilization time.                                      */
    /* Delay fixed to worst case: maximum CPU frequency                       */
    while(wait_loop_index < ADC_STAB_DELAY_CPU_CYCLES)
    {
      wait_loop_index++;
    }    

    /* Get timeout */
    tickstart = HAL_GetTick();
    
    /* Wait for ADC effectively enabled */
    while(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_RDY) == RESET)
    {
      if((HAL_GetTick() - tickstart) > ADC_ENABLE_TIMEOUT)
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
  /* @Note: forbidden to disable ADC (set bit ADC_CR_ADDIS) if ADC is already  */
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
      if((HAL_GetTick() - tickstart) > ADC_ENABLE_TIMEOUT)
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
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
    
  /* Verification if ADC is not already stopped on regular group to bypass    */
  /* this function if not needed.                                             */
  if (__HAL_ADC_IS_CONVERSION_ONGOING_REGULAR(hadc))
  {
    
    /* Stop potential conversion on going on regular group */
    /* Software is allowed to set ADSTP only when ADSTART=1 and ADDIS=0 */
    if (HAL_IS_BIT_SET(hadc->Instance->CR, ADC_CR_ADSTART) && 
        HAL_IS_BIT_CLR(hadc->Instance->CR, ADC_CR_ADDIS)                  )
    {
      /* Stop conversions on regular group */
      hadc->Instance->CR |= ADC_CR_ADSTP;
    }
    
    /* Wait for conversion effectively stopped */
    tickstart = HAL_GetTick();
      
    while((hadc->Instance->CR & ADC_CR_ADSTART) != RESET)
    {
      if((HAL_GetTick() - tickstart) > ADC_STOP_CONVERSION_TIMEOUT)
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
