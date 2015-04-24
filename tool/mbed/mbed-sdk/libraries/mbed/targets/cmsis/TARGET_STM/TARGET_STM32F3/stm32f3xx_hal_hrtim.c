/**
  ******************************************************************************
  * @file    stm32f3xx_hal_hrtim.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   TIM HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the High Resolution Timer (HRTIM) peripheral:
  *           + HRTIM Initialization
  *           + DLL Calibration Start
  *           + Timer Time Base Unit Configuration
  *           + Simple Time Base Start/Stop
  *           + Simple Time Base Start/Stop Interrupt
  *           + Simple Time Base Start/Stop DMA Request
  *           + Simple Output Compare/PWM Channel Configuration
  *           + Simple Output Compare/PWM Channel Start/Stop Interrupt
  *           + Simple Output Compare/PWM Channel Start/Stop DMA Request
  *           + Simple Input Capture Channel Configuration
  *           + Simple Input Capture Channel Start/Stop Interrupt
  *           + Simple Input Capture Channel Start/Stop DMA Request
  *           + Simple One Pulse Channel Configuration
  *           + Simple One Pulse Channel Start/Stop Interrupt
  *           + HRTIM External Synchronization Configuration
  *           + HRTIM Burst Mode Controller Configuration
  *           + HRTIM Burst Mode Controller Enabling
  *           + HRTIM External Events Conditioning Configuration
  *           + HRTIM Faults Conditioning Configuration
  *           + HRTIM Faults Enabling
  *           + HRTIM ADC trigger Configuration
  *           + Waveform Timer Configuration
  *           + Waveform Event Filtering Configuration
  *           + Waveform Dead Time Insertion Configuration
  *           + Waveform Chopper Mode Configuration
  *           + Waveform Compare Unit Configuration
  *           + Waveform Capture Unit Configuration
  *           + Waveform Output Configuration
  *           + Waveform Counter Start/Stop
  *           + Waveform Counter Start/Stop Interrupt
  *           + Waveform Counter Start/Stop DMA Request
  *           + Waveform Output Enabling
  *           + Waveform Output Level Set/Get
  *           + Waveform Output State Get
  *           + Waveform Burst DMA Operation Configuration
  *           + Waveform Burst DMA Operation Start
  *           + Waveform Timer Counter Software Reset
  *           + Waveform Capture Software Trigger 
  *           + Waveform Burst Mode Controller Software Trigger
  *           + Waveform Timer Pre-loadable Registers Update Enabling
  *           + Waveform Timer Pre-loadable Registers Software Update
  *           + Waveform Timer Delayed Protection Status Get
  *           + Waveform Timer Burst Status Get
  *           + Waveform Timer Push-Pull Status Get
  *           + Peripheral State Get
  @verbatim
  ==============================================================================
                      ##### Simple mode v.s. waveform mode #####
==============================================================================
  [..] The HRTIM HAL API is split into 2 categories:
    (#)Simple functions: these functions allow for using a HRTIM timer as a  
        general purpose timer with high resolution capabilities.
       Following simple modes are proposed:
         (+)Output compare mode
         (+)PWM output mode
         (+)Input capture mode
         (+)One pulse mode
       HRTIM simple modes are managed through the set of functions named
       HAL_HRTIM_Simple<Function>. These functions are similar in name and usage 
       to the one defined for the TIM peripheral. When a HRTIM timer operates in 
       simple mode, only a very limited set of HRTIM features are used.
    (#)Waveform functions: These functions allow taking advantage of the HRTIM 
       flexibility to produce numerous types of control signal. When a HRTIM timer 
       operates in waveform mode, all the HRTIM features are accessible without 
       any restriction.  HRTIM waveform modes are managed through the set of
       functions named HAL_HRTIM_Waveform<Function>

==============================================================================
                      ##### How to use this driver #####
==============================================================================
    [..]
     (#)Initialize the HRTIM low level resources by implementing the
        HAL_HRTIM_MspInit() function:
        (##)Enable the HRTIM clock source using __HRTIMx_CLK_ENABLE() 
        (##)Connect HRTIM pins to MCU I/Os
            (+++) Enable the clock for the HRTIM GPIOs using the following
                  function: __GPIOx_CLK_ENABLE()   
            (+++) Configure these GPIO pins in Alternate Function mode using
                  HAL_GPIO_Init()
        (##)When using DMA to control data transfer (e.g HAL_HRTIM_SimpleBaseStart_DMA())
            (+++)Enable the DMAx interface clock using __DMAx_CLK_ENABLE()
            (+++)Initialize the DMA handle
            (+++)Associate the initialized DMA handle to the appropriate DMA 
                 handle of the HRTIM handle using  __HAL_LINKDMA()
            (+++)Initialize the DMA channel using HAL_DMA_Init()
            (+++)Configure the priority and enable the NVIC for the transfer
                 complete interrupt on the DMA channel using HAL_NVIC_SetPriority()
                 and HAL_NVIC_EnableIRQ()
        (##)In case of using interrupt mode (e.g HAL_HRTIM_SimpleBaseStart_IT())
            (+++)Configure the priority and enable the NVIC for the concerned
                 HRTIM interrupt using HAL_NVIC_SetPriority() and HAL_NVIC_EnableIRQ()

    (#)Initialize the HRTIM HAL using HAL_HRTIM_Init(). The HRTIM configuration 
       structure (field of the HRTIM handle) specifies which global interrupt of
       whole HRTIM must be enabled (Burst mode period, System fault, Faults).
       It also contains the HRTIM external synchronization configuration. HRTIM
       can act as a master (generating a synchronization signal) or as a slave
       (waiting for a trigger to be synchronized).

    (#)Start the high resolution unit using HAL_HRTIM_DLLCalibrationStart(). DLL
       calibration is executed periodically and compensate for potential voltage
       and temperature drifts. DLL calibration period is specified by the 
       CalibrationRate argument.	

    (#)HRTIM timers cannot be used until the high resolution unit is ready. This 
       can be checked using HAL_HRTIM_PollForDLLCalibration(): this function returns
       HAL_OK if DLL calibration is completed or HAL_TIMEOUT if the DLL calibration
       is still going on when timeout given is argument expires. DLL calibration  
       can also be started in interrupt mode using HAL_HRTIM_DLLCalibrationStart_IT(). 
       In that case an interrupt is generated when the DLL calibration is completed.
       Note that as DLL calibration is executed on a periodic basis an interrupt 
       will be generated at the end of every DLL calibration operation
      (worst case: one interrupt every 14  micro seconds !).

     (#) Configure HRTIM resources shared by all HRTIM timers
        (##)Burst Mode Controller:
                (+++)HAL_HRTIM_BurstModeConfig(): configures the HRTIM burst mode
                     controller: operating mode (continuous or -shot mode), clock
                     (source, prescaler) , trigger(s), period, idle duration.
        (##)External Events Conditionning:
                (+++)HAL_HRTIM_EventConfig(): configures the conditioning of an
                     external event channel: source, polarity, edge-sensitivity.
                     External event can be used as triggers (timer reset, input
                     capture, burst mode, ADC triggers, delayed protection, …)
                     They can also be used to set or reset timer outputs. Up to
                     10 event channels are available.
                (+++)HAL_HRTIM_EventPrescalerConfig(): configures the external
                     event sampling clock (used for digital filtering).
        (##)Fault Conditionning:
                (+++)HAL_HRTIM_FaultConfig(): configures the conditioning of a
                     fault channel: source, polarity, edge-sensitivity.  Fault
                     channels are used to disable the outputs in case of an
                     abnormal operation. Up to 5 fault channels are available.
                (+++)HAL_HRTIM_FaultPrescalerConfig(): configures the fault
                     sampling clock (used for digital filtering).
                (+++)HAL_HRTIM_FaultModeCtl(): Enables or disables fault input(s)
                     circuitry. By default all fault inputs are disabled.
        (##)ADC trigger:
                (+++)HAL_HRTIM_ADCTriggerConfig(): configures the source triggering
                     the update of the ADC trigger register and the ADC trigger.
                     4 independent triggers are available to start both the regular
                     and the injected sequencers of the 2 ADCs

     (#) Configure HRTIM timer time base using HAL_HRTIM_TimeBaseConfig(). This
         function must be called whatever the HRTIM timer operating mode is
         (simple v.s. waveform). It  configures mainly:
        (##)The HRTIM  timer counter operating mode (continuous, one shot)
        (##)The HRTIM  timer clock prescaler
        (##)The HRTIM  timer period 
        (##)The HRTIM  timer repetition counter

     (#) If the HRTIM timer operates in simple mode:
        (##)Simple time base: HAL_HRTIM_SimpleBaseStart(),HAL_HRTIM_SimpleBaseStop(),
                  HAL_HRTIM_SimpleBaseStart_IT(),HAL_HRTIM_SimpleBaseStop_IT(), 
                  HAL_HRTIM_SimpleBaseStart_DMA(),HAL_HRTIM_SimpleBaseStop_DMA(). 
        (##)Simple output compare: HAL_HRTIM_SimpleOCChannelConfig(),
                  HAL_HRTIM_SimpleOCStart(),HAL_HRTIM_SimpleOCStop(),
                  HAL_HRTIM_SimpleOCStart_IT(),HAL_HRTIM_SimpleOCStop_IT(),
                  HAL_HRTIM_SimpleOCStart_DMA(),HAL_HRTIM_SimpleOCStop_DMA(),
        (##)Simple PWM output: HAL_HRTIM_SimplePWMChannelConfig(),
                  HAL_HRTIM_SimplePWMStart(),HAL_HRTIM_SimplePWMStop(),
                  HAL_HRTIM_SimplePWMStart_IT(),HAL_HRTIM_SimplePWMStop_IT(),
                  HAL_HRTIM_SimplePWMStart_DMA(),HAL_HRTIM_SimplePWMStop_DMA(),
        (##)Simple input capture: HAL_HRTIM_SimpleCaptureChannelConfig(),
                  HAL_HRTIM_SimpleCaptureStart(),HAL_HRTIM_SimpleCaptureStop(),
                  HAL_HRTIM_SimpleCaptureStart_IT(),HAL_HRTIM_SimpleCaptureStop_IT(),
                  HAL_HRTIM_SimpleCaptureStart_DMA(),HAL_HRTIM_SimpleCaptureStop_DMA().
        (##)Simple one pulse: HAL_HRTIM_SimpleOnePulseChannelConfig(),
                  HAL_HRTIM_SimpleOnePulseStart(),HAL_HRTIM_SimpleOnePulseStop(),
                  HAL_HRTIM_SimpleOnePulseStart_IT(),HAL_HRTIM_SimpleOnePulseStop_It().

     (#) If the HRTIM timer operates in waveform mode:
        (##)Completes waveform timer configuration
                (+++)HAL_HRTIM_WaveformTimerConfig(): configuration of a HRTIM
                     timer operating in wave form mode mainly consists in:
                        - Enabling the HRTIM timer interrupts and DMA requests,
                        - Enabling the half mode for the HRTIM timer,
                        - Defining how the HRTIM timer reacts to external
                          synchronization input,
                        - Enabling the push-pull mode for the HRTIM timer,
                        - Enabling the fault channels for the HRTIM timer,
                        - Enabling the deadtime insertion for the HRTIM timer,
                        - Setting the delayed protection mode for the HRTIM timer
                          (source and outputs on which the delayed protection are applied),
                        - Specifying the HRTIM timer update and reset triggers,
                        - Specifying the HRTIM timer registers update policy (preload enabling, …).
                (+++)HAL_HRTIM_TimerEventFilteringConfig(): configures external 
                     event blanking and windowingcircuitry of a HRTIM timer:
                        - Blanking:  to mask external events during a defined 
                          time period
                        - Windowing:  to enable external events only during
                          a defined time period
                (+++)HAL_HRTIM_DeadTimeConfig(): configures the deadtime insertion
                     unit for a HRTIM timer. Allows to generate a couple of
                     complementary signals from a single reference waveform, 
                     with programmable delays between active state.
                (+++)HAL_HRTIM_ChopperModeConfig(): configures the parameters of
                     the high-frequency carrier signal added on top of the timing
                     unit output. Chopper mode can be enabled or disabled for each
                     timer output separately (see  HAL_HRTIM_WaveformOutputConfig()).
                (+++)HAL_HRTIM_BurstDMAConfig(): configures the burst DMA burst 
                     controller. Allows having multiple HRTIM registers updated
                     with a single DMA request. The burst DMA operation is started
                     by calling HAL_HRTIM_BurstDMATransfer().
                (+++)HAL_HRTIM_WaveformCompareConfig():configures the compare unit
                     of a HRTIM timer. This operation consists in setting the
                     compare value and possibly specifying the auto delayed mode
                     for compare units 2 and 4 (allows to have compare events
                     generated relatively to capture events). Note that when auto
                     delayed mode is needed, the capture unit associated to the
                     compare unit must be configured separately.
                (+++)HAL_HRTIM_WaveformCaptureConfig(): configures the capture unit
                     of a HRTIM timer. This operation consists in specifying the
                     source(s)  triggering the capture (timer register update event,
                     external event, timer output set/reset event, other HRTIM
                     timer related events). 
                (+++)HAL_HRTIM_WaveformOutputConfig(): configuration HRTIM timer
                     output manly consists in: 
                        - Setting the output polarity (active high or active low),
                        - Defining the set/reset crossbar for the output, 
                        - Specifying the fault level (active or inactive) in IDLE
                          and FAULT states.,
        (##)Set waveform timer output(s) level
                (+++)HAL_HRTIM_WaveformSetOutputLevel(): forces the output to its
                     active or inactive level. For example, when deadtime insertion 
                     is enabled it is necessary to force the output level by software
                     to have the outputs in a complementary state as soon as the RUN mode is entered.
        (##)Enable/Disable waveform timer output(s)
                (+++)HAL_HRTIM_WaveformOutputStart(),HAL_HRTIM_WaveformOutputStop().
        (##)Start/Stop waveform HRTIM timer(s). 
                (+++)HAL_HRTIM_WaveformCounterStart(),HAL_HRTIM_WaveformCounterStop(),
                (+++)HAL_HRTIM_WaveformCounterStart_IT(),HAL_HRTIM_WaveformCounterStop_IT(),
                (+++)HAL_HRTIM_WaveformCounterStart()_DMA,HAL_HRTIM_WaveformCounterStop_DMA(),

        (##)Burst mode controller enabling:
                (+++)HAL_HRTIM_BurstModeCtl(): activates or de-activates the 
                     burst mode controller.

        (##)Some HRTIM operations can be triggered by software:
                (+++)HAL_HRTIM_BurstModeSoftwareTrigger(): calling this function 
                     trigs the burst operation.
                (+++)HAL_HRTIM_SoftwareCapture(): calling this function trigs the 
                     capture of the HRTIM timer counter.
                (+++)HAL_HRTIM_SoftwareUpdate(): calling this function trigs the 
                     update of the pre-loadable registers of the HRTIM timer ()
                (+++)HAL_HRTIM_SoftwareReset():calling this function resets the 
                     HRTIM timer counter.

        (##)Some functions can be used anytime to retrieve HRTIM timer related 
            information
                (+++)HAL_HRTIM_GetCapturedValue(): returns actual value of the
                     capture register of the designated capture unit.
                (+++)HAL_HRTIM_WaveformGetOutputLevel(): returns actual level
                     (ACTIVE/INACTIVE) of the designated timer output.
                (+++)HAL_HRTIM_WaveformGetOutputState():returns actual state
                     (IDLE/RUN/FAULT) of the designated timer output.
                (+++)HAL_HRTIM_GetDelayedProtectionStatus():returns actual level 
                     (ACTIVE/INACTIVE) of the designated output when the delayed
                      protection was triggered.
                (+++)HAL_HRTIM_GetBurstStatus(): returns the actual status
                     (ACTIVE/INACTIVE) of the burst mode controller.
                (+++)HAL_HRTIM_GetCurrentPushPullStatus(): when the push-pull mode
                     is enabled for the HRTIM timer (see HAL_HRTIM_WaveformTimerConfig()),
                     the push-pull indicates on which output the signal is currently 
                     active (e.g signal applied on output 1 and output 2 forced
                     inactive or vice versa). 
                (+++)HAL_HRTIM_GetIdlePushPullStatus(): when the push-pull mode
                     is enabled for the HRTIM timer (see HAL_HRTIM_WaveformTimerConfig()),
                     the idle push-pull  status indicates during which period the
                     delayed protection request occurred (e.g. protection occurred
                     when the output 1 was active and output 2 forced inactive or
                     vice versa).

        (##)Some functions can be used anytime to retrieve actual HRTIM status
                (+++)HAL_HRTIM_GetState(): returns actual HRTIM instance HAL state.
  
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

#ifdef HAL_HRTIM_MODULE_ENABLED

#if defined(STM32F334x8)

/** @defgroup HRTIM HRTIM HAL module driver
  * @brief HRTIM HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup HRTIM_Private_Defines HRTIM Private Define
  * @{
  */
#define HRTIM_FLTR_FLTxEN (HRTIM_FLTR_FLT1EN |\
                           HRTIM_FLTR_FLT2EN |\
                           HRTIM_FLTR_FLT3EN |\
                           HRTIM_FLTR_FLT4EN | \
                           HRTIM_FLTR_FLT5EN)

#define HRTIM_TIMCR_TIMUPDATETRIGGER (HRTIM_TIMUPDATETRIGGER_MASTER  |\
                                      HRTIM_TIMUPDATETRIGGER_TIMER_A |\
                                      HRTIM_TIMUPDATETRIGGER_TIMER_B |\
                                      HRTIM_TIMUPDATETRIGGER_TIMER_C |\
                                      HRTIM_TIMUPDATETRIGGER_TIMER_D |\
                                      HRTIM_TIMUPDATETRIGGER_TIMER_E)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup HRTIM_Private_Variables HRTIM Private Variables
  * @{
  */
static uint32_t TimerIdxToTimerId[] = 
{
  HRTIM_TIMERID_TIMER_A,
  HRTIM_TIMERID_TIMER_B,
  HRTIM_TIMERID_TIMER_C,
  HRTIM_TIMERID_TIMER_D,
  HRTIM_TIMERID_TIMER_E,
  HRTIM_TIMERID_MASTER,
};
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup HRTIM_Private_Functions HRTIM Private Functions
  * @{
  */
static void HRTIM_MasterBase_Config(HRTIM_HandleTypeDef * hhrtim, 
                                    HRTIM_TimeBaseCfgTypeDef * pTimeBaseCfg);

static void HRTIM_TimingUnitBase_Config(HRTIM_HandleTypeDef * hhrtim, 
                                        uint32_t TimerIdx,
                                        HRTIM_TimeBaseCfgTypeDef * pTimeBaseCfg);

static void HRTIM_MasterWaveform_Config(HRTIM_HandleTypeDef * hhrtim, 
                                        HRTIM_TimerCfgTypeDef * pTimerCfg);

static void HRTIM_TimingUnitWaveform_Config(HRTIM_HandleTypeDef * hhrtim, 
                                            uint32_t TimerIdx, 
                                            HRTIM_TimerCfgTypeDef * pTimerCfg);

static void HRTIM_CompareUnitConfig(HRTIM_HandleTypeDef * hhrtim,
                                    uint32_t TimerIdx,
                                    uint32_t CompareUnit,
                                    HRTIM_CompareCfgTypeDef * pCompareCfg);

static void HRTIM_CaptureUnitConfig(HRTIM_HandleTypeDef * hhrtim,
                                    uint32_t TimerIdx,
                                    uint32_t CaptureUnit,
                                    uint32_t Event);

static void HRTIM_OutputConfig(HRTIM_HandleTypeDef * hhrtim,
                                uint32_t TimerIdx,
                                uint32_t Output,
                                HRTIM_OutputCfgTypeDef * pOutputCfg);

static void HRTIM_EventConfig(HRTIM_HandleTypeDef * hhrtim,
                              uint32_t Event,
                              HRTIM_EventCfgTypeDef * pEventCfg);

static void HRTIM_TIM_ResetConfig(HRTIM_HandleTypeDef * hhrtim,
                                  uint32_t TimerIdx,
                                  uint32_t Event);  

static uint32_t HRTIM_GetITFromOCMode(HRTIM_HandleTypeDef * hhrtim,
                                      uint32_t TimerIdx,
                                      uint32_t OCChannel);

static uint32_t HRTIM_GetDMAFromOCMode(HRTIM_HandleTypeDef * hhrtim,
                                       uint32_t TimerIdx,
                                       uint32_t OCChannel);

static DMA_HandleTypeDef * HRTIM_GetDMAHandleFromTimerIdx(HRTIM_HandleTypeDef * hhrtim,
                                                          uint32_t TimerIdx);

static uint32_t GetTimerIdxFromDMAHandle(DMA_HandleTypeDef *hdma);

static void HRTIM_ForceRegistersUpdate(HRTIM_HandleTypeDef * hhrtim,
                                      uint32_t TimerIdx);

static void HRTIM_HRTIM_ISR(HRTIM_HandleTypeDef * hhrtim);

static void HRTIM_Master_ISR(HRTIM_HandleTypeDef * hhrtim);

static void HRTIM_Timer_ISR(HRTIM_HandleTypeDef * hhrtim,
                                       uint32_t TimerIdx);

static void HRTIM_DMAMasterCplt(DMA_HandleTypeDef *hdma);

static void HRTIM_DMATimerxCplt(DMA_HandleTypeDef *hdma);

static void HRTIM_DMAError(DMA_HandleTypeDef *hdma);

static void HRTIM_BurstDMACplt(DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup HRTIM_Exported_Functions HRTIM Exported Functions
  * @{
  */

/** @defgroup HRTIM_Exported_Functions_Group1 Initialization and de-initialization functions  
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and Time Base Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize a HRTIM instance 
      (+) De-initialize a HRTIM instance 
      (+) Initialize the HRTIM MSP 
      (+) De-initialize the HRTIM MSP 
      (+) Start the high-resolution unit (start DLL calibration) 
      (+) Check that the high resolution unit is ready (DLL calibration done) 
      (+) Configure the time base unit of a HRTIM timer 

@endverbatim
  * @{
  */

/**
  * @brief  Initializes a HRTIM instance 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_Init(HRTIM_HandleTypeDef * hhrtim)
{
  uint8_t timer_idx;
  uint32_t hrtim_mcr;
  
  /* Check the HRTIM handle allocation */
  if(hhrtim == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_HRTIM_ALL_INSTANCE(hhrtim->Instance));
  assert_param(IS_HRTIM_IT(hhrtim->Init.HRTIMInterruptResquests)); 
 
  /* Set the HRTIM state */
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* Initialize the DMA handles */
  hhrtim->hdmaMaster = (DMA_HandleTypeDef *)HAL_NULL;    
  hhrtim->hdmaTimerA = (DMA_HandleTypeDef *)HAL_NULL;     
  hhrtim->hdmaTimerB = (DMA_HandleTypeDef *)HAL_NULL;  
  hhrtim->hdmaTimerC = (DMA_HandleTypeDef *)HAL_NULL;  
  hhrtim->hdmaTimerD = (DMA_HandleTypeDef *)HAL_NULL;  
  hhrtim->hdmaTimerE = (DMA_HandleTypeDef *)HAL_NULL;  
  
  /* HRTIM output synchronization configuration (if required) */
  if ((hhrtim->Init.SyncOptions & HRTIM_SYNCOPTION_MASTER) != RESET)
  {
    /* Check parameters */
    assert_param(IS_HRTIM_SYNCOUTPUTSOURCE(hhrtim->Init.SyncOutputSource));
    assert_param(IS_HRTIM_SYNCOUTPUTPOLARITY(hhrtim->Init.SyncOutputPolarity));
    
    /* The synchronization output initialization procedure must be done prior 
       to the configuration of the MCU outputs (done within HAL_HRTIM_MspInit)
    */
    if (hhrtim->Instance == HRTIM1)
    {
      /* Enable the HRTIM peripheral clock */
      __HRTIM1_CLK_ENABLE();
    }
    
    hrtim_mcr = hhrtim->Instance->sMasterRegs.MCR;
    
    /* Set the event to be sent on the synchronization output */
    hrtim_mcr &= ~(HRTIM_MCR_SYNC_SRC);
    hrtim_mcr |= (hhrtim->Init.SyncOutputSource & HRTIM_MCR_SYNC_SRC);
    
    /* Set the polarity of the synchronization output */
    hrtim_mcr &= ~(HRTIM_MCR_SYNC_OUT);
    hrtim_mcr |= (hhrtim->Init.SyncOutputPolarity & HRTIM_MCR_SYNC_OUT);
    
    /* Update the HRTIM registers */  
    hhrtim->Instance->sMasterRegs.MCR = hrtim_mcr;    
  }

  /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
  HAL_HRTIM_MspInit(hhrtim);
  
  /* HRTIM input synchronization configuration (if required) */
  if ((hhrtim->Init.SyncOptions & HRTIM_SYNCOPTION_SLAVE) != RESET)
  {
    /* Check parameters */
    assert_param(IS_HRTIM_SYNCINPUTSOURCE(hhrtim->Init.SyncInputSource));
    
    hrtim_mcr = hhrtim->Instance->sMasterRegs.MCR;

    /* Set the synchronization input source */
    hrtim_mcr &= ~(HRTIM_MCR_SYNC_IN);
    hrtim_mcr |= (hhrtim->Init.SyncInputSource & HRTIM_MCR_SYNC_IN);
    
    /* Update the HRTIM registers */  
    hhrtim->Instance->sMasterRegs.MCR = hrtim_mcr;    
  }
  
  /* Initialize the HRTIM state*/
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Initialize the lock status of the HRTIM HAL API */
  __HAL_UNLOCK(hhrtim);

  /* Tnitialize timer related parameters */ 
  for (timer_idx = HRTIM_TIMERINDEX_TIMER_A ; 
       timer_idx <= HRTIM_TIMERINDEX_MASTER ; 
       timer_idx++)
  {
    hhrtim->TimerParam[timer_idx].CaptureTrigger1 = HRTIM_CAPTURETRIGGER_NONE;
    hhrtim->TimerParam[timer_idx].CaptureTrigger2 = HRTIM_CAPTURETRIGGER_NONE;
    hhrtim->TimerParam[timer_idx].InterruptRequests = HRTIM_IT_NONE;
    hhrtim->TimerParam[timer_idx].DMARequests = HRTIM_IT_NONE;
    hhrtim->TimerParam[timer_idx].DMASrcAddress = 0;
    hhrtim->TimerParam[timer_idx].DMASize = 0;
  }
  
  return HAL_OK;
}

/**
  * @brief  De-initializes a timer operating in waveform mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_DeInit (HRTIM_HandleTypeDef * hhrtim)
{
  /* Check the HRTIM handle allocation */
  if(hhrtim == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_HRTIM_ALL_INSTANCE(hhrtim->Instance));

  /* Set the HRTIM state */
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* DeInit the low level hardware */
  HAL_HRTIM_MspDeInit(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  return HAL_OK;
}

/**
  * @brief  MSP initialization for a HRTIM instance
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval None
  */
__weak void HAL_HRTIM_MspInit(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_HRTIM_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  MSP initialization for a for a HRTIM instance
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval None
  */
__weak void HAL_HRTIM_MspDeInit(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_HRTIM_MspDeInit could be implemented in the user file
   */ 
}

/**
  * @brief  Starts the DLL calibration
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  CalibrationRate: DLL calibration period
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_SINGLE_CALIBRATION: One shot DLL calibration
  *                    @arg HRTIM_CALIBRATIONRATE_7300: Periodic DLL calibration. T=7.3 ms
  *                    @arg HRTIM_CALIBRATIONRATE_910: Periodic DLL calibration. T=910 us
  *                    @arg HRTIM_CALIBRATIONRATE_114: Periodic DLL calibration. T=114 us
  *                    @arg HRTIM_CALIBRATIONRATE_14: Periodic DLL calibration. T=14 us
  * @retval HAL status
  * @note This function locks the HRTIM instance. HRTIM instance is unlocked 
  *       within the HAL_HRTIM_PollForDLLCalibration function, just before 
  *       exiting the function.
  */
HAL_StatusTypeDef HAL_HRTIM_DLLCalibrationStart(HRTIM_HandleTypeDef * hhrtim,
                                                uint32_t CalibrationRate)
{
  uint32_t hrtim_dllcr;
  
   /* Check the parameters */
  assert_param(IS_HRTIM_CALIBRATIONRATE(CalibrationRate));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Configure DLL Calibration */
  hrtim_dllcr = hhrtim->Instance->sCommonRegs.DLLCR;
  
  if (CalibrationRate == HRTIM_SINGLE_CALIBRATION)
  {
    /* One shot DLL calibration */
    hrtim_dllcr &= ~(HRTIM_DLLCR_CALEN);
    hrtim_dllcr |= HRTIM_DLLCR_CAL;    
  }
  else
  {
    /* Periodic DLL calibration */
    hrtim_dllcr &= ~(HRTIM_DLLCR_CALRTE | HRTIM_DLLCR_CAL);
    hrtim_dllcr |= (CalibrationRate | HRTIM_DLLCR_CALEN);
  }

  /* Update HRTIM register */
  hhrtim->Instance->sCommonRegs.DLLCR = hrtim_dllcr;
  
  return HAL_OK;
}

/**
  * @brief  Starts the DLL calibration
  *         DLL ready interrupt is enabled
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  CalibrationRate: DLL calibration period
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_SINGLE_CALIBRATION: One shot DLL calibration
  *                    @arg HRTIM_CALIBRATIONRATE_7300: Periodic DLL calibration. T=7.3 ms
  *                    @arg HRTIM_CALIBRATIONRATE_910: Periodic DLL calibration. T=910 us
  *                    @arg HRTIM_CALIBRATIONRATE_114: Periodic DLL calibration. T=114 us
  *                    @arg HRTIM_CALIBRATIONRATE_14: Periodic DLL calibration. T=14 us
  * @retval HAL status
  * @note This function locks the HRTIM instance. HRTIM instance is unlocked 
  *       within the IRQ processing function when processing the DLL ready 
  *       interrupt.
  * @note If this function is called for periodic calibration, the DLLRDY 
  *       interrupt is generated every time the calibration completes which
  *       will significantly increases the overall interrupt rate.
  */
HAL_StatusTypeDef HAL_HRTIM_DLLCalibrationStart_IT(HRTIM_HandleTypeDef * hhrtim,
                                                   uint32_t CalibrationRate)
{
  uint32_t hrtim_dllcr;
  
   /* Check the parameters */
  assert_param(IS_HRTIM_CALIBRATIONRATE(CalibrationRate));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* Enable DLL Ready interrupt flag */
  __HAL_HRTIM_ENABLE_IT(hhrtim, HRTIM_IT_DLLRDY);
  
  /* Configure DLL Calibration */
  hrtim_dllcr = hhrtim->Instance->sCommonRegs.DLLCR;
  
  if (CalibrationRate == HRTIM_SINGLE_CALIBRATION)
  {
    /* One shot DLL calibration */
    hrtim_dllcr &= ~(HRTIM_DLLCR_CALEN);
    hrtim_dllcr |= HRTIM_DLLCR_CAL;    
  }
  else
  {
    /* Periodic DLL calibration */
    hrtim_dllcr &= ~(HRTIM_DLLCR_CALRTE | HRTIM_DLLCR_CAL);
    hrtim_dllcr |= (CalibrationRate | HRTIM_DLLCR_CALEN);
  }
               
  /* Update HRTIM register */
  hhrtim->Instance->sCommonRegs.DLLCR = hrtim_dllcr;
  
  return HAL_OK;
}

/**
  * @brief  Polls the DLL calibration ready flag and returns when the flag is
  *         set (DLL calibration completed) or upon timeout expiration
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timeout: Timeout duration in millisecond
  * @retval HAL status 
  */
HAL_StatusTypeDef HAL_HRTIM_PollForDLLCalibration(HRTIM_HandleTypeDef * hhrtim,
                                                  uint32_t Timeout)
{
  uint32_t tickstart=0;

  tickstart = HAL_GetTick();  
     
  /* Check End of conversion flag */
  while(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_IT_DLLRDY) == RESET)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
      {
        hhrtim->State = HAL_HRTIM_STATE_ERROR;
        return HAL_TIMEOUT;
      }
    }
  }

  /* Set HRTIM State */  
  hhrtim->State = HAL_HRTIM_STATE_READY;
 
  /* Process unlocked */
  __HAL_UNLOCK(hhrtim); 

  return HAL_OK;
}

/**
  * @brief  Configures the time base unit of a timer 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  pTimeBaseCfg: pointer to the time base configuration structure
  * @note This function must be called prior starting the timer 
  * @note   The time-base unit initialization parameters specify:
  *           The timer counter operating mode (continuous, one shot)
  *           The timer clock prescaler
  *           The timer period 
  *           The timer repetition counter.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_TimeBaseConfig(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx,
                                           HRTIM_TimeBaseCfgTypeDef * pTimeBaseCfg)
{
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  assert_param(IS_HRTIM_PRESCALERRATIO(pTimeBaseCfg->PrescalerRatio)); 
  assert_param(IS_HRTIM_MODE(pTimeBaseCfg->Mode)); 
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }
 
  /* Set the HRTIM state */
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    /* Configure master timer time base unit */
    HRTIM_MasterBase_Config(hhrtim, pTimeBaseCfg);
  }
  else
  {
    /* Configure timing unit time base unit */
    HRTIM_TimingUnitBase_Config(hhrtim, TimerIdx, pTimeBaseCfg);
  }
      
  /* Set HRTIM state */
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  return HAL_OK; 
}

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group2 Simple time base mode functions  
 *  @brief    When à HRTIM timer operates in simple time base mode, the
 *            timer counter counts from 0 to the period value.
 *
@verbatim    
 ===============================================================================
              ##### Simple time base mode functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start simple time base 
      (+) Stop simple time base 
      (+) Start simple time base and enable interrupt 
      (+) Stop simple time base and disable interrupt 
      (+) Start simple time base and enable DMA transfer 
      (+) Stop simple time base and disable DMA transfer 

@endverbatim
  * @{
  */

/**
  * @brief  Starts the counter of a timer operating in basic time base mode
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStart(HRTIM_HandleTypeDef * hhrtim,
                                           uint32_t TimerIdx)
{  
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK;
}

/**
  * @brief  Stops the counter of a timer operating in basic time base mode
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStop(HRTIM_HandleTypeDef * hhrtim,
                                          uint32_t TimerIdx)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK;
}

/**
  * @brief  Starts the counter of a timer operating in basic time base mode
  *         Timer repetition interrupt is enabled.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStart_IT(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* Enable the repetition interrupt */
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    __HAL_HRTIM_MASTER_ENABLE_IT(hhrtim, HRTIM_MASTER_IT_MREP);
  }
  else
  {
    __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_REP);
  }
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK;
}

/**
  * @brief  Starts the counter of a timer operating in basic time base mode
  *         Timer repetition interrupt is disabled.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStop_IT(HRTIM_HandleTypeDef * hhrtim,
                                             uint32_t TimerIdx)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* Disable the repetition interrupt */
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    __HAL_HRTIM_MASTER_DISABLE_IT(hhrtim, HRTIM_MASTER_IT_MREP);
  }
  else
  {
    __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_REP);
  }
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK;
}

/**
  * @brief  Starts the counter of a timer operating in basic time base mode
  *         Timer repetition DMA request is enabled.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                    @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                    @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                    @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                    @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                    @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                    @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  SrcAddr: DMA transfer source address
  * @param  DestAddr: DMA transfer destination address
  * @param  Length: The length of data items (data size) to be transferred
  *                     from source to destination
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStart_DMA(HRTIM_HandleTypeDef * hhrtim,
                                               uint32_t TimerIdx,
                                               uint32_t SrcAddr,
                                               uint32_t DestAddr,
                                               uint32_t Length)
{
  DMA_HandleTypeDef * hdma;
  
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  
  if((hhrtim->State == HAL_HRTIM_STATE_BUSY))
  {
     return HAL_BUSY;
  }
  if((hhrtim->State == HAL_HRTIM_STATE_READY))
  {
    if((SrcAddr == 0 ) || (DestAddr == 0 ) || (Length == 0)) 
    {
      return HAL_ERROR;                                    
    }
    else
    {
      hhrtim->State = HAL_HRTIM_STATE_BUSY;
    }
  }
  
  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  /* Get the timer DMA handler */
  hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);
  
  /* Set the DMA transfer completed callback */
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    hdma->XferCpltCallback = HRTIM_DMAMasterCplt;
  }
  else
  {
    hdma->XferCpltCallback = HRTIM_DMATimerxCplt;
  }
  
  /* Set the DMA error callback */
  hdma->XferErrorCallback = HRTIM_DMAError ;
  
  /* Enable the DMA channel */
  HAL_DMA_Start_IT(hdma, SrcAddr, DestAddr, Length);
  
  /* Enable the timer repetition DMA request */
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    __HAL_HRTIM_MASTER_ENABLE_DMA(hhrtim, HRTIM_MASTER_DMA_MREP);
  }
  else
  {
    __HAL_HRTIM_TIMER_ENABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_REP);
  }
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  
  
  return HAL_OK;
}

/**
  * @brief  Starts the counter of a timer operating in basic time base mode
  *         Timer repetition DMA request is disabled.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStop_DMA(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  DMA_HandleTypeDef * hdma;

  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
    
  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    /* Disable the DMA */
    HAL_DMA_Abort(hhrtim->hdmaMaster);
    
    /* Disable the timer repetition DMA request */
    __HAL_HRTIM_MASTER_DISABLE_DMA(hhrtim, HRTIM_MASTER_DMA_MREP);
  }
  else
  {
    /* Get the timer DMA handler */
    hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);
    
    /* Disable the DMA */
    HAL_DMA_Abort(hdma);
    
    /* Disable the timer repetition DMA request */
    __HAL_HRTIM_TIMER_DISABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_REP);
  }
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group3 Simple output compare mode functions  
 *  @brief    When a HRTIM timer operates in simple output compare mode
 *            the output level is set to a programmable value when a match 
 *            is found between the compare register and the counter.
 *            Compare unit 1 is automatically associated to output 1
 *            Compare unit 2 is automatically associated to output 2
 *
@verbatim    
 ===============================================================================
              ##### Simple output compare functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure simple output channel 
      (+) Start simple output compare 
      (+) Stop simple output compare 
      (+) Start simple output compare and enable interrupt 
      (+) Stop simple output compare and disable interrupt 
      (+) Start simple output compare and enable DMA transfer 
      (+) Stop simple output compare and disable DMA transfer 

@endverbatim
  * @{
  */

/**
  * @brief  Configures an output in basic output compare mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2 
  * @param  pSimpleOCChannelCfg: pointer to the basic output compare output configuration structure
  * @note When the timer operates in basic output compare mode:
  *         Output 1 is implicitely controled by the compare unit 1
  *         Output 2 is implicitely controled by the compare unit 2
  *       Output Set/Reset crossbar is set according to the selected output compare mode:
  *         Toggle: SETxyR = RSTxyR = CMPy
  *         Active: SETxyR = CMPy, RSTxyR = 0
  *         Inactive: SETxy =0, RSTxy = CMPy
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOCChannelConfig(HRTIM_HandleTypeDef * hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t OCChannel,
                                                 HRTIM_SimpleOCChannelCfgTypeDef* pSimpleOCChannelCfg)
{
  uint32_t CompareUnit = 0xFFFFFFFF;
  HRTIM_CompareCfgTypeDef CompareCfg;
  HRTIM_OutputCfgTypeDef OutputCfg;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));
  assert_param(IS_HRTIM_BASICOCMODE(pSimpleOCChannelCfg->Mode));
  assert_param(IS_HRTIM_OUTPUTPOLARITY(pSimpleOCChannelCfg->Polarity));
  assert_param(IS_HRTIM_OUTPUTIDLELEVEL(pSimpleOCChannelCfg->IdleLevel));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Set HRTIM state */
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* Configure timer compare unit */  
  switch (OCChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      CompareUnit = HRTIM_COMPAREUNIT_1;
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      CompareUnit = HRTIM_COMPAREUNIT_2;
    }
    break;
  }
  
  CompareCfg.CompareValue = pSimpleOCChannelCfg->Pulse;
  CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  CompareCfg.AutoDelayedTimeout = 0;
  
  HRTIM_CompareUnitConfig(hhrtim,
                          TimerIdx,
                          CompareUnit,
                          &CompareCfg);
  
  /* Configure timer output */
  OutputCfg.Polarity = pSimpleOCChannelCfg->Polarity;
  OutputCfg.IdleLevel = pSimpleOCChannelCfg->IdleLevel;
  OutputCfg.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_NONE;
  OutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  OutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  OutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
  
  switch (pSimpleOCChannelCfg->Mode)
  {
  case HRTIM_BASICOCMODE_TOGGLE:
    {
      if (CompareUnit == HRTIM_COMPAREUNIT_1)
      {
        OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
      }
      else
      {
        OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP2;
      }
      OutputCfg.ResetSource = OutputCfg.SetSource;
    }
    break;
  case HRTIM_BASICOCMODE_ACTIVE:
    {
      if (CompareUnit == HRTIM_COMPAREUNIT_1)
      {
        OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
      }
      else
      {
        OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP2;
      }
      OutputCfg.ResetSource = HRTIM_OUTPUTRESET_NONE;
    }
    break;
  case HRTIM_BASICOCMODE_INACTIVE:
    {
      if (CompareUnit == HRTIM_COMPAREUNIT_1)
      {
        OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP1;
      }
      else
      {
        OutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP2;
      }
      OutputCfg.SetSource = HRTIM_OUTPUTSET_NONE;
    }
    break;
  }
  
  HRTIM_OutputConfig(hhrtim,
                     TimerIdx,
                     OCChannel,
                     &OutputCfg);  
  
  /* Set HRTIM state */
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  return HAL_OK; 
}

/**
  * @brief  Starts the output compare signal generation on the designed timer output 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOCStart(HRTIM_HandleTypeDef * hhrtim,
                                         uint32_t TimerIdx,
                                         uint32_t OCChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable the timer output */
  hhrtim->Instance->sCommonRegs.OENR |= OCChannel;
    
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Stops the output compare signal generation on the designed timer output 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOCStop(HRTIM_HandleTypeDef * hhrtim,
                                        uint32_t TimerIdx,
                                        uint32_t OCChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Disable the timer output */
  hhrtim->Instance->sCommonRegs.ODISR |= OCChannel;
    
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Starts the output compare signal generation on the designed timer output
  *         Interrupt is enabled (see note below)
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @note Interrupt enabling depends on the chosen output compare mode
  *          Output toggle: compare match interrupt is enabled
  *          Output set active:  output set interrupt is enabled
  *          Output set inactive:  output reset interrupt is enabled
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOCStart_IT(HRTIM_HandleTypeDef * hhrtim,
                                            uint32_t TimerIdx,
                                            uint32_t OCChannel)
{
  uint32_t interrupt;
  
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Get the interrupt to enable (depends on the output compare mode) */
  interrupt = HRTIM_GetITFromOCMode(hhrtim, TimerIdx, OCChannel);
  
  /* Enable the timer output */
  hhrtim->Instance->sCommonRegs.OENR |= OCChannel;
    
  /* Enable the timer interrupt (depends on the output compare mode) */
  __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, TimerIdx, interrupt);
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Stops the output compare signal generation on the designed timer output
  *         Interrupt is disabled
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOCStop_IT(HRTIM_HandleTypeDef * hhrtim,
                                           uint32_t TimerIdx,
                                           uint32_t OCChannel)
{
  uint32_t interrupt;
  
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Disable the timer output */
  hhrtim->Instance->sCommonRegs.ODISR |= OCChannel;
    
  /* Get the interrupt to disable (depends on the output compare mode) */
  interrupt = HRTIM_GetITFromOCMode(hhrtim, TimerIdx, OCChannel);

  /* Disable the timer interrupt */
  __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, TimerIdx, interrupt);
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Starts the output compare signal generation on the designed timer output
  *         DMA request is enabled (see note below)
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @param  SrcAddr: DMA transfer source address
  * @param  DestAddr: DMA transfer destination address
  * @param  Length: The length of data items (data size) to be transferred
  *                     from source to destination
  * @note  DMA request enabling depends on the chosen output compare mode
  *          Output toggle: compare match DMA request is enabled
  *          Output set active:  output set DMA request is enabled
  *          Output set inactive:  output reset DMA request is enabled 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOCStart_DMA(HRTIM_HandleTypeDef * hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t OCChannel,
                                             uint32_t SrcAddr,
                                             uint32_t DestAddr,
                                             uint32_t Length)
{
  DMA_HandleTypeDef * hdma;
  uint32_t dma_request;
  
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));
  
  if((hhrtim->State == HAL_HRTIM_STATE_BUSY))
  {
     return HAL_BUSY;
  }
  if((hhrtim->State == HAL_HRTIM_STATE_READY))
  {
    if((SrcAddr == 0 ) || (DestAddr == 0 ) || (Length == 0)) 
    {
      return HAL_ERROR;                                    
    }
    else
    {
      hhrtim->State = HAL_HRTIM_STATE_BUSY;
    }
  }
  
  /* Process Locked */
  __HAL_LOCK(hhrtim);
 
   /* Enable the timer output */
  hhrtim->Instance->sCommonRegs.OENR |= OCChannel;

  /* Get the DMA request to enable */
  dma_request = HRTIM_GetDMAFromOCMode(hhrtim, TimerIdx, OCChannel);
  
  /* Get the timer DMA handler */
  hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);

  /* Set the DMA error callback */
  hdma->XferErrorCallback = HRTIM_DMAError ;
  
  /* Set the DMA transfer completed callback */
  hdma->XferCpltCallback = HRTIM_DMATimerxCplt;
  
  /* Enable the DMA channel */
  HAL_DMA_Start_IT(hdma, SrcAddr, DestAddr, Length);
  
  /* Enable the timer DMA request */
  __HAL_HRTIM_TIMER_ENABLE_DMA(hhrtim, TimerIdx, dma_request);
    
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  
 
  return HAL_OK;
}

/**
  * @brief  Stops the output compare signal generation on the designed timer output
  *         DMA request is disabled
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOCStop_DMA(HRTIM_HandleTypeDef * hhrtim,
                                            uint32_t TimerIdx,
                                            uint32_t OCChannel)
{
  DMA_HandleTypeDef * hdma;
  uint32_t dma_request;
 
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));
    
  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 

  /* Disable the timer output */
  hhrtim->Instance->sCommonRegs.ODISR |= OCChannel;
    
  /* Get the timer DMA handler */
  hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);
  
  /* Disable the DMA */
  HAL_DMA_Abort(hdma);
  
  /* Get the DMA request to disable */
  dma_request = HRTIM_GetDMAFromOCMode(hhrtim, TimerIdx, OCChannel);

  /* Disable the timer DMA request */
  __HAL_HRTIM_TIMER_DISABLE_DMA(hhrtim, TimerIdx, dma_request);
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group4 Simple PWM output mode functions  
 *  @brief    When a HRTIM timer operates in simple PWM output mode 
 *            the output level is set to a programmable value when a match is
 *            found between the compare register and the counter and reset when
 *            the timer period is reached. Duty cycle is determined by the 
 *            comparison value.
 *            Compare unit 1 is automatically associated to output 1
 *            Compare unit 2 is automatically associated to output 2
 *
@verbatim    
 ===============================================================================
              ##### Simple PWM output functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure simple PWM output channel 
      (+) Start simple PWM output 
      (+) Stop simple PWM output 
      (+) Start simple PWM output and enable interrupt 
      (+) Stop simple PWM output and disable interrupt 
      (+) Start simple PWM output and enable DMA transfer 
      (+) Stop simple PWM output and disable DMA transfer 

@endverbatim
  * @{
  */

/**
  * @brief  Configures an output in basic PWM mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2 
  * @param  pSimplePWMChannelCfg: pointer to the basic PWM output configuration structure
  * @note When the timer operates in basic PWM output mode:
  *         Output 1 is implicitely controled by the compare unit 1
  *         Output 2 is implicitely controled by the compare unit 2
  *       Output Set/Reset crossbar is set as follows:
  *         Ouput 1: SETx1R = CMP1, RSTx1R = PER
  *         Output 2: SETx2R = CMP2, RST2R = PER
  * @note When Simple PWM mode is used the registers preload mechanism is 
  *       enabled (otherwise the behavior is not guaranteed).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimplePWMChannelConfig(HRTIM_HandleTypeDef * hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t PWMChannel,
                                                  HRTIM_SimplePWMChannelCfgTypeDef* pSimplePWMChannelCfg)
{
  uint32_t CompareUnit = 0xFFFFFFFF;
  HRTIM_CompareCfgTypeDef CompareCfg;
  HRTIM_OutputCfgTypeDef OutputCfg;
  uint32_t hrtim_timcr;

  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));
  assert_param(IS_HRTIM_OUTPUTPOLARITY(pSimplePWMChannelCfg->Polarity));
  assert_param(IS_HRTIM_OUTPUTIDLELEVEL(pSimplePWMChannelCfg->IdleLevel));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Configure timer compare unit */  
  switch (PWMChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      CompareUnit = HRTIM_COMPAREUNIT_1;
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      CompareUnit = HRTIM_COMPAREUNIT_2;
    }
    break;
  }
  
  CompareCfg.CompareValue = pSimplePWMChannelCfg->Pulse;
  CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  CompareCfg.AutoDelayedTimeout = 0;
  
  HRTIM_CompareUnitConfig(hhrtim,
                          TimerIdx,
                          CompareUnit,
                          &CompareCfg);
  
  /* Configure timer output */
  OutputCfg.Polarity = pSimplePWMChannelCfg->Polarity;
  OutputCfg.IdleLevel = pSimplePWMChannelCfg->IdleLevel;
  OutputCfg.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_NONE;
  OutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  OutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  OutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
  
  if (CompareUnit == HRTIM_COMPAREUNIT_1)
  {
    OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
  }
  else
  {
    OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP2;
  }
  OutputCfg.ResetSource = HRTIM_OUTPUTSET_TIMPER;
  
  HRTIM_OutputConfig(hhrtim,
                     TimerIdx,
                     PWMChannel,
                     &OutputCfg);
  
  /* Enable the registers preload mechanism */
  hrtim_timcr   = hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR;
  hrtim_timcr |= HRTIM_TIMCR_PREEN;
  hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR  = hrtim_timcr;  
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Starts the PWM output signal generation on the designed timer output
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimplePWMStart(HRTIM_HandleTypeDef * hhrtim,
                                          uint32_t TimerIdx,
                                          uint32_t PWMChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable the timer output */
  hhrtim->Instance->sCommonRegs.OENR |= PWMChannel;
    
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Stops the PWM output signal generation on the designed timer output
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimplePWMStop(HRTIM_HandleTypeDef * hhrtim,
                                         uint32_t TimerIdx,
                                         uint32_t PWMChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Disable the timer output */
  hhrtim->Instance->sCommonRegs.ODISR |= PWMChannel;
    
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Starts the PWM output signal generation on the designed timer output
  *         The compare interrupt is enabled.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimplePWMStart_IT(HRTIM_HandleTypeDef * hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t PWMChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable the timer output */
  hhrtim->Instance->sCommonRegs.OENR |= PWMChannel;

  /* Enable the timer interrupt (depends on the PWM output) */
  switch (PWMChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP1);
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP2);
    }
    break;
  }
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Stops the PWM output signal generation on the designed timer output
  *         The compare interrupt is disabled.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimplePWMStop_IT(HRTIM_HandleTypeDef * hhrtim,
                                            uint32_t TimerIdx,
                                            uint32_t PWMChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Disable the timer output */
  hhrtim->Instance->sCommonRegs.ODISR |= PWMChannel;
    
  /* Disable the timer interrupt (depends on the PWM output) */
  switch (PWMChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP1);
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP2);
    }
    break;
  }
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Starts the PWM output signal generation on the designed timer output
  *         The compare DMA request is enabled.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @param  SrcAddr: DMA transfer source address
  * @param  DestAddr: DMA transfer destination address
  * @param  Length: The length of data items (data size) to be transferred
  *                     from source to destination
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimplePWMStart_DMA(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx,
                                              uint32_t PWMChannel,
                                              uint32_t SrcAddr,
                                              uint32_t DestAddr,
                                              uint32_t Length)
{
  DMA_HandleTypeDef * hdma;

  /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));
  
  if((hhrtim->State == HAL_HRTIM_STATE_BUSY))
  {
     return HAL_BUSY;
  }
  if((hhrtim->State == HAL_HRTIM_STATE_READY))
  {
    if((SrcAddr == 0 ) || (DestAddr == 0 ) || (Length == 0)) 
    {
      return HAL_ERROR;                                    
    }
    else
    {
      hhrtim->State = HAL_HRTIM_STATE_BUSY;
    }
  }
  
  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  /* Enable the timer output */
  hhrtim->Instance->sCommonRegs.OENR |= PWMChannel;
  
  /* Get the timer DMA handler */
  hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);

  /* Set the DMA error callback */
  hdma->XferErrorCallback = HRTIM_DMAError ;
  
  /* Set the DMA transfer completed callback */
  hdma->XferCpltCallback = HRTIM_DMATimerxCplt;
  
  /* Enable the DMA channel */
  HAL_DMA_Start_IT(hdma, SrcAddr, DestAddr, Length);
  
  /* Enable the timer DMA request */
  switch (PWMChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      __HAL_HRTIM_TIMER_ENABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_CMP1);      
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      __HAL_HRTIM_TIMER_ENABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_CMP2);      
    }
    break;
  }
   
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK;
}

/**
  * @brief  Stops the PWM output signal generation on the designed timer output
  *         The compare DMA request is disabled.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimplePWMStop_DMA(HRTIM_HandleTypeDef * hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t PWMChannel)
{
  DMA_HandleTypeDef * hdma;

  /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));
    
  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 

  /* Disable the timer output */
  hhrtim->Instance->sCommonRegs.ODISR |= PWMChannel;
    
  /* Get the timer DMA handler */
  hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);
  
  /* Disable the DMA */
  HAL_DMA_Abort(hdma);
  
  /* Disable the timer DMA request */
  switch (PWMChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      __HAL_HRTIM_TIMER_DISABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_CMP1);
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      __HAL_HRTIM_TIMER_DISABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_CMP2);
    }
    break;
  }
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group5 Simple input capture functions  
 *  @brief    When a HRTIM timer operates in simple input capture mode 
 *            the Capture Register (HRTIM_CPT1/2xR) is used to latch the
 *            value of the timer counter counter after a transition detected 
 *            on a given external event input.
 *
@verbatim    
 ===============================================================================
              ##### Simple input capture functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure simple input capture channel
      (+) Start simple input capture 
      (+) Stop simple input capture 
      (+) Start simple input capture and enable interrupt 
      (+) Stop simple input capture and disable interrupt 
      (+) Start simple input capture and enable DMA transfer 
      (+) Stop simple input capture and disable DMA transfer 

@endverbatim
  * @{
  */

/**
  * @brief  Configures a basic capture 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureChannel: Capture unit
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @param  pSimpleCaptureChannelCfg: pointer to the basic capture configuration structure
  * @note When the timer operates in basic capture mode the capture is trigerred
  *       by the designated external event and GPIO input is implicitely used as event source.
  *       The cature can be triggered by a rising edge, a falling edge or both
  *       edges on event channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureChannelConfig(HRTIM_HandleTypeDef * hhrtim,
                                                      uint32_t TimerIdx,
                                                      uint32_t CaptureChannel,
                                                      HRTIM_SimpleCaptureChannelCfgTypeDef* pSimpleCaptureChannelCfg)
{
  HRTIM_EventCfgTypeDef EventCfg;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));
  assert_param(IS_HRTIM_EVENT(pSimpleCaptureChannelCfg->Event));
  assert_param(IS_HRTIM_EVENTPOLARITY(pSimpleCaptureChannelCfg->EventSensitivity,
                                      pSimpleCaptureChannelCfg->EventPolarity));
  assert_param(IS_HRTIM_EVENTSENSITIVITY(pSimpleCaptureChannelCfg->EventSensitivity));
  assert_param(IS_HRTIM_EVENTFILTER(pSimpleCaptureChannelCfg->Event, 
                                    pSimpleCaptureChannelCfg->EventFilter));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);

  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Configure external event channel */
  EventCfg.FastMode = HRTIM_EVENTFASTMODE_DISABLE;
  EventCfg.Filter = pSimpleCaptureChannelCfg->EventFilter;
  EventCfg.Polarity = pSimpleCaptureChannelCfg->EventPolarity;
  EventCfg.Sensitivity = pSimpleCaptureChannelCfg->EventSensitivity;
  EventCfg.Source = HRTIM_EVENTSRC_1;
    
  HRTIM_EventConfig(hhrtim,
                    pSimpleCaptureChannelCfg->Event,
                    &EventCfg);

  /* Memorize capture trigger (will be configured when the capture is started */  
  HRTIM_CaptureUnitConfig(hhrtim,
                          TimerIdx,
                          CaptureChannel,
                          pSimpleCaptureChannelCfg->Event);
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Enables a basic capture on the designed capture unit
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureChannel: Timer output
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval HAL status
  * @note  The external event triggering the capture is available for all timing 
  *        units. It can be used directly and is active as soon as the timing 
  *        unit counter is enabled.
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStart(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx,
                                              uint32_t CaptureChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
    
  /* Set the capture unit trigger */
  switch (CaptureChannel)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR = hhrtim->TimerParam[TimerIdx].CaptureTrigger1;
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR = hhrtim->TimerParam[TimerIdx].CaptureTrigger2;
    }
    break;
  }
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Disables a basic capture on the designed capture unit 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureChannel: Timer output
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStop(HRTIM_HandleTypeDef * hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t CaptureChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
    
  /* Set the capture unit trigger */
  switch (CaptureChannel)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR = HRTIM_CAPTURETRIGGER_NONE;
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR = HRTIM_CAPTURETRIGGER_NONE;
    }
    break;
  }
  
  /* Disable the timer counter */
  if ((hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR == HRTIM_CAPTURETRIGGER_NONE) &&
      (hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR == HRTIM_CAPTURETRIGGER_NONE))
  {
    __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  }
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Enables a basic capture on the designed capture unit
  *         Capture interrupt is enabled
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureChannel: Timer output
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStart_IT(HRTIM_HandleTypeDef * hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t CaptureChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
    
  /* Set the capture unit trigger */
  switch (CaptureChannel)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR = hhrtim->TimerParam[TimerIdx].CaptureTrigger1;
      
      /* Enable the capture unit 1 interrupt */
      __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CPT1);
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR = hhrtim->TimerParam[TimerIdx].CaptureTrigger2;
      
      /* Enable the capture unit 2 interrupt */
      __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CPT2);
    }
    break;
  }
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Disables a basic capture on the designed capture unit
  *         Capture interrupt is disabled
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureChannel: Timer output
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStop_IT(HRTIM_HandleTypeDef * hhrtim,
                                                uint32_t TimerIdx,
                                                uint32_t CaptureChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
    
  /* Set the capture unit trigger */
  switch (CaptureChannel)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR = HRTIM_CAPTURETRIGGER_NONE;
      
      /* Disable the capture unit 1 interrupt */
      __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CPT1);
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR = HRTIM_CAPTURETRIGGER_NONE;

      /* Disable the capture unit 2 interrupt */
      __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CPT2);
    }
    break;
  }
  
  /* Disable the timer counter */
  if ((hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR == HRTIM_CAPTURETRIGGER_NONE) &&
      (hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR == HRTIM_CAPTURETRIGGER_NONE))
  {
    __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  }
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Enables a basic capture on the designed capture unit
  *         Capture DMA request is enabled
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureChannel: Timer output
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @param  SrcAddr: DMA transfer source address
  * @param  DestAddr: DMA transfer destination address
  * @param  Length: The length of data items (data size) to be transferred
  *                     from source to destination
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStart_DMA(HRTIM_HandleTypeDef * hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t CaptureChannel,
                                                  uint32_t SrcAddr,
                                                  uint32_t DestAddr,
                                                  uint32_t Length)
{
  DMA_HandleTypeDef * hdma;

   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
    
  /* Get the timer DMA handler */
  hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);
  
  /* Set the DMA error callback */
  hdma->XferErrorCallback = HRTIM_DMAError ;
  
  /* Set the DMA transfer completed callback */
  hdma->XferCpltCallback = HRTIM_DMATimerxCplt;
  
  /* Enable the DMA channel */
  HAL_DMA_Start_IT(hdma, SrcAddr, DestAddr, Length);
  
  switch (CaptureChannel)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      /* Set the capture unit trigger */
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR = hhrtim->TimerParam[TimerIdx].CaptureTrigger1;
      
      __HAL_HRTIM_TIMER_ENABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_CPT1);      
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      /* Set the capture unit trigger */
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR = hhrtim->TimerParam[TimerIdx].CaptureTrigger2;
      
      /* Enable the timer DMA request */
      __HAL_HRTIM_TIMER_ENABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_CPT2);      
    }
    break;
  }
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);

  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Disables a basic capture on the designed capture unit
  *         Capture DMA request is disabled
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureChannel: Timer output
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStop_DMA(HRTIM_HandleTypeDef * hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t CaptureChannel)
{
  DMA_HandleTypeDef * hdma;

  /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
    
  /* Get the timer DMA handler */
  hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);
  
  /* Disable the DMA */
  HAL_DMA_Abort(hdma);
  
  switch (CaptureChannel)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      /* Reset the capture unit trigger */
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR = HRTIM_CAPTURETRIGGER_NONE;
      
      /* Disable the capture unit 1 DMA request */
      __HAL_HRTIM_TIMER_DISABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_CPT1);
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      /* Reset the capture unit trigger */
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR = HRTIM_CAPTURETRIGGER_NONE;
      
      /* Disable the capture unit 2 DMA request */
      __HAL_HRTIM_TIMER_DISABLE_DMA(hhrtim, TimerIdx, HRTIM_TIM_DMA_CPT2);
    }
    break;
  }
  
  /* Disable the timer counter */
  if ((hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR == HRTIM_CAPTURETRIGGER_NONE) &&
      (hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR == HRTIM_CAPTURETRIGGER_NONE))
  {
    __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  }
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group6 Simple one pulse functions  
 *  @brief    When a HRTIM timer operates in simple one pulse mode 
 *            the timer counter is started in response to transition detected 
 *            on a given external event input to generate a pulse with a 
 *            programmable length after a programmable delay.
 *
@verbatim    
 ===============================================================================
              ##### Simple one pulse functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure one pulse channel 
      (+) Start one pulse generation 
      (+) Stop one pulse generation 
      (+) Start one pulse generation and enable interrupt 
      (+) Stop one pulse generation and disable interrupt 

@endverbatim
  * @{
  */

/**
  * @brief  Configures an output basic one pulse mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OnePulseChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2 
  * @param  pSimpleOnePulseChannelCfg: pointer to the basic one pulse output configuration structure
  * @note When the timer operates in basic one pulse mode:
  *         the timer counter is implicitely started by the reset event,
  *         the reset of the timer counter is triggered by the designated external event
  *         GPIO input is implicitely used as event source,
  *         Output 1 is implicitely controled by the compare unit 1,
  *         Output 2 is implicitely controled by the compare unit 2.
  *       Output Set/Reset crossbar is set as follows:
  *         Ouput 1: SETx1R = CMP1, RSTx1R = PER
  *         Output 2: SETx2R = CMP2, RST2R = PER
  * @retval HAL status
  * @note If HAL_HRTIM_SimpleOnePulseChannelConfig is called for both timer 
  *       outputs, the reset event related configuration data provided in the 
  *       second call will override the reset event related configuration data 
  *       provided in the first call.
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseChannelConfig(HRTIM_HandleTypeDef * hhrtim,
                                                       uint32_t TimerIdx,
                                                       uint32_t OnePulseChannel,
                                                       HRTIM_SimpleOnePulseChannelCfgTypeDef* pSimpleOnePulseChannelCfg)
{
  uint32_t CompareUnit = 0xFFFFFFFF;
  HRTIM_CompareCfgTypeDef CompareCfg;
  HRTIM_OutputCfgTypeDef OutputCfg;
  HRTIM_EventCfgTypeDef EventCfg;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OnePulseChannel));
  assert_param(IS_HRTIM_OUTPUTPOLARITY(pSimpleOnePulseChannelCfg->OutputPolarity));
  assert_param(IS_HRTIM_OUTPUTIDLELEVEL(pSimpleOnePulseChannelCfg->OutputIdleLevel));
  assert_param(IS_HRTIM_EVENT(pSimpleOnePulseChannelCfg->Event));
  assert_param(IS_HRTIM_EVENTPOLARITY(pSimpleOnePulseChannelCfg->EventSensitivity,
                                      pSimpleOnePulseChannelCfg->EventPolarity));
  assert_param(IS_HRTIM_EVENTSENSITIVITY(pSimpleOnePulseChannelCfg->EventSensitivity));
  assert_param(IS_HRTIM_EVENTFILTER(pSimpleOnePulseChannelCfg->Event,
                                    pSimpleOnePulseChannelCfg->EventFilter));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Configure timer compare unit */  
  switch (OnePulseChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      CompareUnit = HRTIM_COMPAREUNIT_1;
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      CompareUnit = HRTIM_COMPAREUNIT_2;
    }
    break;
  }
  
  CompareCfg.CompareValue = pSimpleOnePulseChannelCfg->Pulse;
  CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  CompareCfg.AutoDelayedTimeout = 0;
  
  HRTIM_CompareUnitConfig(hhrtim,
                          TimerIdx,
                          CompareUnit,
                          &CompareCfg);
  
  /* Configure timer output */
  OutputCfg.Polarity = pSimpleOnePulseChannelCfg->OutputPolarity;
  OutputCfg.IdleLevel = pSimpleOnePulseChannelCfg->OutputIdleLevel;
  OutputCfg.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_NONE;
  OutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  OutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  OutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
  
  if (CompareUnit == HRTIM_COMPAREUNIT_1)
  {
    OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
  }
  else
  {
    OutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP2;
  }
  OutputCfg.ResetSource = HRTIM_OUTPUTSET_TIMPER;
  
  HRTIM_OutputConfig(hhrtim,
                     TimerIdx,
                     OnePulseChannel,
                     &OutputCfg);  
  
  /* Configure external event channel */
  EventCfg.FastMode = HRTIM_EVENTFASTMODE_DISABLE;
  EventCfg.Filter = pSimpleOnePulseChannelCfg->EventFilter;
  EventCfg.Polarity = pSimpleOnePulseChannelCfg->EventPolarity;
  EventCfg.Sensitivity = pSimpleOnePulseChannelCfg->EventSensitivity;
  EventCfg.Source = HRTIM_EVENTSRC_1;
    
  HRTIM_EventConfig(hhrtim,
                    pSimpleOnePulseChannelCfg->Event,
                    &EventCfg);

  /* Configure the timer reset register */
  HRTIM_TIM_ResetConfig(hhrtim,
                        TimerIdx, 
                        pSimpleOnePulseChannelCfg->Event);  
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Enables the basic one pulse signal generation on the designed output 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OnePulseChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseStart(HRTIM_HandleTypeDef * hhrtim,
                                                uint32_t TimerIdx,
                                                uint32_t OnePulseChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OnePulseChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable the timer output */
  hhrtim->Instance->sCommonRegs.OENR |= OnePulseChannel;
    
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Disables the basic one pulse signal generation on the designed output 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OnePulseChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseStop(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx,
                                              uint32_t OnePulseChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OnePulseChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Disable the timer output */
  hhrtim->Instance->sCommonRegs.ODISR |= OnePulseChannel;
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Enables the basic one pulse signal generation on the designed output
  *         The compare interrupt is enabled (pulse start)
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OnePulseChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseStart_IT(HRTIM_HandleTypeDef * hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t OnePulseChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OnePulseChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable the timer output */
  hhrtim->Instance->sCommonRegs.OENR |= OnePulseChannel;

  /* Enable the timer interrupt (depends on the OnePulse output) */
  switch (OnePulseChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP1);
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP2);
    }
    break;
  }
  
  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Disables the basic one pulse signal generation on the designed output
  *         The compare interrupt is disabled
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  OnePulseChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseStop_IT(HRTIM_HandleTypeDef * hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t OnePulseChannel)
{
     /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OnePulseChannel));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Disable the timer output */
  hhrtim->Instance->sCommonRegs.ODISR |= OnePulseChannel;
    
  /* Disable the timer interrupt (depends on the OnePulse output) */
  switch (OnePulseChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP1);
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP2);
    }
    break;
  }
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, TimerIdxToTimerId[TimerIdx]);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group7 Configuration functions  
 *  @brief    Functions configuring the HRTIM resources shared by all the
 *            HRTIM timers operating in waveform mode.
 *
@verbatim    
 ===============================================================================
              ##### HRTIM configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the burst mode controller 
      (+) Configure an external event conditionning 
      (+) Configure the external events sampling clock  
      (+) Configure a fault conditionning 
      (+) Enable or disable fault inputs 
      (+) Configure the faults sampling clock  
      (+) Configure an ADC trigger  

@endverbatim
  * @{
  */

/**
  * @brief  Configures the burst mode feature of the HRTIM 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  pBurstModeCfg: pointer to the burst mode configuration structure
  * @retval HAL status
  * @note This function must be called before starting the burst mode 
  *       controller
  */
HAL_StatusTypeDef HAL_HRTIM_BurstModeConfig(HRTIM_HandleTypeDef * hhrtim,
                                            HRTIM_BurstModeCfgTypeDef* pBurstModeCfg)
{
  uint32_t hrtim_bmcr;

  /* Check parameters */
  assert_param(IS_HRTIM_BURSTMODE(pBurstModeCfg->Mode));
  assert_param(IS_HRTIM_BURSTMODECLOCKSOURCE(pBurstModeCfg->ClockSource));
  assert_param(IS_HRTIM_HRTIM_BURSTMODEPRESCALER(pBurstModeCfg->Prescaler));
  assert_param(IS_HRTIM_BURSTMODEPRELOAD(pBurstModeCfg->PreloadEnable));

  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  hrtim_bmcr = hhrtim->Instance->sCommonRegs.BMCR;

  /* Set the burst mode operating mode */
  hrtim_bmcr &= ~(HRTIM_BMCR_BMOM);
  hrtim_bmcr |= pBurstModeCfg->Mode;
  
  /* Set the burst mode clock source */
  hrtim_bmcr &= ~(HRTIM_BMCR_BMCLK);
  hrtim_bmcr |= pBurstModeCfg->ClockSource;
  
  /* Set the burst mode prescaler */
  hrtim_bmcr &= ~(HRTIM_BMCR_BMPRSC);
  hrtim_bmcr |= pBurstModeCfg->Prescaler;
 
  /* Enable/disable burst mode registers preload */
  hrtim_bmcr &= ~(HRTIM_BMCR_BMPREN);
  hrtim_bmcr |= pBurstModeCfg->PreloadEnable;
 
  /* Set the burst mode trigger */
  hhrtim->Instance->sCommonRegs.BMTRGR = pBurstModeCfg->Trigger;
  
  /* Set the burst mode compare value */
  hhrtim->Instance->sCommonRegs.BMCMPR = pBurstModeCfg->IdleDuration;
  
  /* Set the burst mode period */
  hhrtim->Instance->sCommonRegs.BMPER = pBurstModeCfg->Period;
  
  /* Update the HRTIM registers */  
  hhrtim->Instance->sCommonRegs.BMCR = hrtim_bmcr;

  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the conditioning of an external event
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Event: external event to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_EVENT_1: External event 1
  *                    @arg HRTIM_EVENT_2: External event 2
  *                    @arg HRTIM_EVENT_3: External event 3
  *                    @arg HRTIM_EVENT_4: External event 4
  *                    @arg HRTIM_EVENT_5: External event 5
  *                    @arg HRTIM_EVENT_6: External event 6
  *                    @arg HRTIM_EVENT_7: External event 7
  *                    @arg HRTIM_EVENT_8: External event 8
  *                    @arg HRTIM_EVENT_9: External event 9
  *                    @arg HRTIM_EVENT_10: External event 10
  * @param  pEventCfg: pointer to the event conditioning configuration structure
  * @note This function must be called before starting the timer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_EventConfig(HRTIM_HandleTypeDef * hhrtim,
                                        uint32_t Event,
                                        HRTIM_EventCfgTypeDef* pEventCfg)
{
  /* Check parameters */
  assert_param(IS_HRTIM_EVENTSRC(pEventCfg->Source)); 
  assert_param(IS_HRTIM_EVENTPOLARITY(pEventCfg->Sensitivity, pEventCfg->Polarity)); 
  assert_param(IS_HRTIM_EVENTSENSITIVITY(pEventCfg->Sensitivity)); 
  assert_param(IS_HRTIM_EVENTFASTMODE(Event, pEventCfg->FastMode)); 
  assert_param(IS_HRTIM_EVENTFILTER(Event, pEventCfg->Filter)); 
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Configure the event channel */
  HRTIM_EventConfig(hhrtim, Event, pEventCfg);
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the external event conditioning block prescaler
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Prescaler: Prescaler value
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_EVENTPRESCALER_DIV1: fEEVS=fHRTIM
  *                    @arg HRTIM_EVENTPRESCALER_DIV2: fEEVS=fHRTIM / 2
  *                    @arg HRTIM_EVENTPRESCALER_DIV4: fEEVS=fHRTIM / 4
  *                    @arg HRTIM_EVENTPRESCALER_DIV8: fEEVS=fHRTIM / 8
  * @note This function must be called before starting the timer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_EventPrescalerConfig(HRTIM_HandleTypeDef * hhrtim,
                                                 uint32_t Prescaler)
{
  uint32_t hrtim_eecr3;

  /* Check parameters */
  assert_param(IS_HRTIM_EVENTPRESCALER(Prescaler));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Set the external event prescaler */
  hrtim_eecr3 = hhrtim->Instance->sCommonRegs.EECR3;
  hrtim_eecr3 &= ~(HRTIM_EECR3_EEVSD);
  hrtim_eecr3 |= Prescaler;
  
  /* Update the HRTIM registers */
  hhrtim->Instance->sCommonRegs.EECR3 = hrtim_eecr3;

  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}
 
/**
  * @brief  Configures the conditioning of fault input
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Fault: fault input to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_FAULT_1: Fault input 1
  *                    @arg HRTIM_FAULT_2: Fault input 2
  *                    @arg HRTIM_FAULT_3: Fault input 3
  *                    @arg HRTIM_FAULT_4: Fault input 4
  *                    @arg HRTIM_FAULT_5: Fault input 5
  * @param  pFaultCfg: pointer to the fault conditioning configuration structure
  * @note This function must be called before starting the timer and before
  *       enabling faults inputs
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_FaultConfig(HRTIM_HandleTypeDef * hhrtim,
                                        uint32_t Fault,
                                        HRTIM_FaultCfgTypeDef* pFaultCfg)
{
  uint32_t hrtim_fltinr1;
  uint32_t hrtim_fltinr2;

  /* Check parameters */
  assert_param(IS_HRTIM_FAULT(Fault));
  assert_param(IS_HRTIM_FAULTSOURCE(pFaultCfg->Source));
  assert_param(IS_HRTIM_FAULTPOLARITY(pFaultCfg->Polarity));
  assert_param(IS_HRTIM_FAULTFILTER(pFaultCfg->Filter));
  assert_param(IS_HRTIM_FAULTLOCK(pFaultCfg->Lock));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Configure fault channel */
  hrtim_fltinr1 = hhrtim->Instance->sCommonRegs.FLTINR1;
  hrtim_fltinr2 = hhrtim->Instance->sCommonRegs.FLTINR2;
  
  switch (Fault)
  {
  case HRTIM_FAULT_1:
    {
      hrtim_fltinr1 &= ~(HRTIM_FLTINR1_FLT1P | HRTIM_FLTINR1_FLT1SRC | HRTIM_FLTINR1_FLT1F | HRTIM_FLTINR1_FLT1LCK);
      hrtim_fltinr1 |= pFaultCfg->Polarity;
      hrtim_fltinr1 |= pFaultCfg->Source;
      hrtim_fltinr1 |= pFaultCfg->Filter;
      hrtim_fltinr1 |= pFaultCfg->Lock;
    }
    break;
  case HRTIM_FAULT_2:
    {
      hrtim_fltinr1 &= ~(HRTIM_FLTINR1_FLT2P | HRTIM_FLTINR1_FLT2SRC | HRTIM_FLTINR1_FLT2F | HRTIM_FLTINR1_FLT2LCK);
      hrtim_fltinr1 |= (pFaultCfg->Polarity << 8);
      hrtim_fltinr1 |= (pFaultCfg->Source << 8);
      hrtim_fltinr1 |= (pFaultCfg->Filter << 8);
      hrtim_fltinr1 |= (pFaultCfg->Lock << 8);
    }
    break;
  case HRTIM_FAULT_3:
    {
      hrtim_fltinr1 &= ~(HRTIM_FLTINR1_FLT3P | HRTIM_FLTINR1_FLT3SRC | HRTIM_FLTINR1_FLT3F | HRTIM_FLTINR1_FLT3LCK);
      hrtim_fltinr1 |= (pFaultCfg->Polarity << 16);
      hrtim_fltinr1 |= (pFaultCfg->Source << 16);
      hrtim_fltinr1 |= (pFaultCfg->Filter << 16);
      hrtim_fltinr1 |= (pFaultCfg->Lock << 16);
    }
    break;
  case HRTIM_FAULT_4:
    {
      hrtim_fltinr1 &= ~(HRTIM_FLTINR1_FLT4P | HRTIM_FLTINR1_FLT4SRC | HRTIM_FLTINR1_FLT4F | HRTIM_FLTINR1_FLT4LCK);
      hrtim_fltinr1 |= (pFaultCfg->Polarity << 24);
      hrtim_fltinr1 |= (pFaultCfg->Source << 24);
      hrtim_fltinr1 |= (pFaultCfg->Filter << 24);
      hrtim_fltinr1 |= (pFaultCfg->Lock << 24);
    }
    break;
  case HRTIM_FAULT_5:
    {
      hrtim_fltinr2 &= ~(HRTIM_FLTINR2_FLT5P | HRTIM_FLTINR2_FLT5SRC | HRTIM_FLTINR2_FLT5F | HRTIM_FLTINR2_FLT5LCK);
      hrtim_fltinr2 |= pFaultCfg->Polarity;
      hrtim_fltinr2 |= pFaultCfg->Source;
      hrtim_fltinr2 |= pFaultCfg->Filter;
      hrtim_fltinr2 |= pFaultCfg->Lock;
    }
    break;
  default:
    break;
  }

  /* Update the HRTIM registers */
  hhrtim->Instance->sCommonRegs.FLTINR1 = hrtim_fltinr1;
  hhrtim->Instance->sCommonRegs.FLTINR2 = hrtim_fltinr2;

  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the fault conditioning block prescaler
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Prescaler: Prescaler value
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_FAULTPRESCALER_DIV1: fFLTS=fHRTIM
  *                    @arg HRTIM_FAULTPRESCALER_DIV2: fFLTS=fHRTIM / 2
  *                    @arg HRTIM_FAULTPRESCALER_DIV4: fFLTS=fHRTIM / 4
  *                    @arg HRTIM_FAULTPRESCALER_DIV8: fFLTS=fHRTIM / 8
  * @retval HAL status
  * @note This function must be called before starting the timer and before
  *       enabling faults inputs
  */
HAL_StatusTypeDef HAL_HRTIM_FaultPrescalerConfig(HRTIM_HandleTypeDef * hhrtim,
                                                 uint32_t Prescaler)
{
  uint32_t hrtim_fltinr2;

  /* Check parameters */
  assert_param(IS_HRTIM_FAULTPRESCALER(Prescaler));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Set the external event prescaler */
  hrtim_fltinr2 = hhrtim->Instance->sCommonRegs.FLTINR2;
  hrtim_fltinr2 &= ~(HRTIM_FLTINR2_FLTSD);
  hrtim_fltinr2 |= Prescaler;
  
  /* Update the HRTIM registers */
  hhrtim->Instance->sCommonRegs.FLTINR2 = hrtim_fltinr2;

  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}
 
/**
  * @brief  Enables or disables the HRTIMx Fault mode.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Faults: fault input(s) to enable or disable
  *                   This parameter can be any combination of the following values:
  *                    @arg HRTIM_FAULT_1: Fault input 1
  *                    @arg HRTIM_FAULT_2: Fault input 2
  *                    @arg HRTIM_FAULT_3: Fault input 3
  *                    @arg HRTIM_FAULT_4: Fault input 4
  *                    @arg HRTIM_FAULT_5: Fault input 5
  * @param  Enable: Fault(s) enabling
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_FAULTMODECTL_ENABLED: Fault(s) enabled
  *                    @arg HRTIM_FAULTMODECTL_DISABLED: Fault(s) disabled
  * @retval None
  */
void HAL_HRTIM_FaultModeCtl(HRTIM_HandleTypeDef * hhrtim, 
                        uint32_t Faults, 
                        uint32_t Enable)
{
  uint32_t hrtim_fltinr1;
  uint32_t hrtim_fltinr2;
  
  /* Check parameters */
  assert_param(IS_HRTIM_FAULT(Faults));
  assert_param(IS_HRTIM_FAULTMODECTL(Enable));

  /* Configure fault channel */
  hrtim_fltinr1 = hhrtim->Instance->sCommonRegs.FLTINR1;
  hrtim_fltinr2 = hhrtim->Instance->sCommonRegs.FLTINR2;
  
  if ((Faults & HRTIM_FAULT_1) != RESET)
  {
    hrtim_fltinr1 &= ~HRTIM_FLTINR1_FLT1E;
    hrtim_fltinr1 |= Enable;
  }
  if ((Faults & HRTIM_FAULT_2) != RESET)
  {
    hrtim_fltinr1 &= ~HRTIM_FLTINR1_FLT2E;
    hrtim_fltinr1 |= (Enable << 8);
  }
  if ((Faults & HRTIM_FAULT_3) != RESET)
  {
    hrtim_fltinr1 &= ~HRTIM_FLTINR1_FLT3E;
    hrtim_fltinr1 |= (Enable << 16);
  }
  if ((Faults & HRTIM_FAULT_4) != RESET)
  {
    hrtim_fltinr1 &= ~HRTIM_FLTINR1_FLT4E; 
    hrtim_fltinr1 |= (Enable << 24);
  }
  if ((Faults & HRTIM_FAULT_5) != RESET)
  {
    hrtim_fltinr2 &= ~HRTIM_FLTINR2_FLT5E;
    hrtim_fltinr2 |= Enable;
  }
  
  /* Update the HRTIMx registers */
  hhrtim->Instance->sCommonRegs.FLTINR1 = hrtim_fltinr1;
  hhrtim->Instance->sCommonRegs.FLTINR2 = hrtim_fltinr2;
}      

/**
  * @brief  Configures both the ADC trigger register update source and the ADC
  *         trigger source.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  ADCTrigger: ADC trigger to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_ADCTRIGGER_1: ADC trigger 1
  *                    @arg HRTIM_ADCTRIGGER_2: ADC trigger 2
  *                    @arg HRTIM_ADCTRIGGER_3: ADC trigger 3
  *                    @arg HRTIM_ADCTRIGGER_4: ADC trigger 4
  * @param  pADCTriggerCfg: pointer to the ADC trigger configuration structure
  * @retval HAL status
  * @note This function must be called before starting the timer
  */
HAL_StatusTypeDef HAL_HRTIM_ADCTriggerConfig(HRTIM_HandleTypeDef * hhrtim,
                                             uint32_t ADCTrigger,
                                             HRTIM_ADCTriggerCfgTypeDef* pADCTriggerCfg)
{
  uint32_t hrtim_cr1;
  
  /* Check parameters */
  assert_param(IS_HRTIM_ADCTRIGGER(ADCTrigger));
  assert_param(IS_HRTIM_ADCTRIGGERUPDATE(pADCTriggerCfg->UpdateSource));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Set the ADC trigger update source */
  hrtim_cr1 = hhrtim->Instance->sCommonRegs.CR1;
  
  switch (ADCTrigger)
  {
  case HRTIM_ADCTRIGGER_1:
    {
      hrtim_cr1 &= ~(HRTIM_CR1_ADC1USRC);
      hrtim_cr1 |= (pADCTriggerCfg->UpdateSource & HRTIM_CR1_ADC1USRC);
      
      /* Set the ADC trigger 1 source */
      hhrtim->Instance->sCommonRegs.ADC1R = pADCTriggerCfg->Trigger;
    }
    break;
  case HRTIM_ADCTRIGGER_2:
    {
      hrtim_cr1 &= ~(HRTIM_CR1_ADC2USRC);
      hrtim_cr1 |= ((pADCTriggerCfg->UpdateSource << 3) & HRTIM_CR1_ADC2USRC); 

      /* Set the ADC trigger 2 source */
      hhrtim->Instance->sCommonRegs.ADC2R = pADCTriggerCfg->Trigger;
    }
    break;
  case HRTIM_ADCTRIGGER_3:
    {
      hrtim_cr1 &= ~(HRTIM_CR1_ADC3USRC);
      hrtim_cr1 |= ((pADCTriggerCfg->UpdateSource << 6) & HRTIM_CR1_ADC3USRC); 
      
      /* Set the ADC trigger 3 source */
      hhrtim->Instance->sCommonRegs.ADC3R = pADCTriggerCfg->Trigger;
    }
    break;
  case HRTIM_ADCTRIGGER_4:
    {
      hrtim_cr1 &= ~(HRTIM_CR1_ADC4USRC);
      hrtim_cr1 |= ((pADCTriggerCfg->UpdateSource << 9) & HRTIM_CR1_ADC4USRC); 
      
      /* Set the ADC trigger 4 source */
      hhrtim->Instance->sCommonRegs.ADC4R = pADCTriggerCfg->Trigger;
    }
    break;
  }
  
  /* Update the HRTIM registers */
  hhrtim->Instance->sCommonRegs.CR1 = hrtim_cr1;

  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group8 Timer waveform configuration and functions
 *  @brief    Functions used to configure and control a HRTIM timer 
 *            operating in waveform mode.
 *
@verbatim    
 ===============================================================================
              ##### HRTIM timer configuration and control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure HRTIM timer general behavior
      (+) Configure HRTIM timer event filtering
      (+) Configure HRTIM timer deadtime insertion 
      (+) Configure HRTIM timer chopper mode  
      (+) Configure HRTIM timer burst DMA 
      (+) Configure HRTIM timer compare unit
      (+) Configure HRTIM timer capture unit 
      (+) Configure HRTIM timer output 
      (+) Set HRTIM timer output level
      (+) Enable HRTIM timer output
      (+) Disable HRTIM timer output
      (+) Start HRTIM timer
      (+) Stop HRTIM timer
      (+) Start HRTIM timer and enable interrupt 
      (+) Stop HRTIM timer and disable interrupt
      (+) Start HRTIM timer and enable DMA transfer  
      (+) Stop HRTIM timer and disable DMA transfer  
      (+) Enable or disable the burst mode controller  
      (+) Start the burst mode controller (by software)
      (+) Trigger a Capture (by software)
      (+) Update the HRTIM timer preloadable registers (by software)
      (+) Reset the HRTIM timer counter (by software)
      (+) Start a burst DMA transfer
      (+) Enable timer register update
      (+) Disable timer register update

@endverbatim
  * @{
  */

/**
  * @brief  Configures the general behavior of a timer operating in waveform mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  pTimerCfg: pointer to the timer configuration structure
  * @note When the timer operates in waveform mode, all the features supported by
  *       the HRTIM are available without any limitation.
  * @retval HAL status
  * @note This function must be called before starting the timer
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformTimerConfig(HRTIM_HandleTypeDef * hhrtim,
                                                uint32_t TimerIdx,
                                                HRTIM_TimerCfgTypeDef * pTimerCfg)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  
  /* Relevant for all HRTIM timers, including the master */
  assert_param(IS_HRTIM_HALFMODE(pTimerCfg->HalfModeEnable));
  assert_param(IS_HRTIM_SYNCSTART(pTimerCfg->StartOnSync));
  assert_param(IS_HRTIM_SYNCRESET(pTimerCfg->ResetOnSync));
  assert_param(IS_HHRTIM_DACSYNC(pTimerCfg->DACSynchro));
  assert_param(IS_HRTIM_PRELOAD(pTimerCfg->PreloadEnable));
  assert_param(IS_HRTIM_TIMERBURSTMODE(pTimerCfg->BurstMode));
  assert_param(IS_HRTIM_UPDATEONREPETITION(pTimerCfg->RepetitionUpdate));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    /* Check parameters */
    assert_param(IS_HRTIM_UPDATEGATING_MASTER(pTimerCfg->UpdateGating));
    assert_param(IS_HRTIM_MASTER_IT(pTimerCfg->InterruptRequests));
    assert_param(IS_HRTIM_MASTER_DMA(pTimerCfg->DMARequests));
    
    /* Configure master timer */
    HRTIM_MasterWaveform_Config(hhrtim, pTimerCfg);
  }
  else
  {
    /* Check parameters */
    assert_param(IS_HRTIM_UPDATEGATING_TIM(pTimerCfg->UpdateGating));  
    assert_param(IS_HRTIM_TIM_IT(pTimerCfg->InterruptRequests));
    assert_param(IS_HRTIM_TIM_DMA(pTimerCfg->DMARequests));
    assert_param(IS_HRTIM_TIMPUSHPULLMODE(pTimerCfg->PushPull));
    assert_param(IS_HRTIM_TIMFAULTENABLE(pTimerCfg->FaultEnable));
    assert_param(IS_HRTIM_TIMFAULTLOCK(pTimerCfg->FaultLock));
    assert_param(IS_HRTIM_TIMDEADTIMEINSERTION(pTimerCfg->PushPull,
                                               pTimerCfg->DeadTimeInsertion));
    assert_param(IS_HRTIM_TIMDELAYEDPROTECTION(pTimerCfg->PushPull,
                                               pTimerCfg->DelayedProtectionMode));
    assert_param(IS_HRTIM_TIMUPDATETRIGGER(pTimerCfg->UpdateTrigger)); 
    assert_param(IS_HRTIM_TIMRESETTRIGGER(pTimerCfg->ResetTrigger));
    assert_param(IS_HRTIM_TIMUPDATEONRESET(pTimerCfg->ResetUpdate));
    
    /* Configure timing unit */
    HRTIM_TimingUnitWaveform_Config(hhrtim, TimerIdx, pTimerCfg);
  }
  
  /* Update timer parameters */
  hhrtim->TimerParam[TimerIdx].InterruptRequests = pTimerCfg->InterruptRequests;
  hhrtim->TimerParam[TimerIdx].DMARequests = pTimerCfg->DMARequests;
  hhrtim->TimerParam[TimerIdx].DMASrcAddress = pTimerCfg->DMASrcAddress;
  hhrtim->TimerParam[TimerIdx].DMADstAddress = pTimerCfg->DMADstAddress;
  hhrtim->TimerParam[TimerIdx].DMASize = pTimerCfg->DMASize;

  /* Force a software update */
  HRTIM_ForceRegistersUpdate(hhrtim, TimerIdx);
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the event filtering capabilities of a timer (blanking, windowing) 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  Event: external event for which timer event filtering must be configured
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_EVENT_NONE: Reset timer event filtering configuration
  *                    @arg HRTIM_EVENT_1: External event 1
  *                    @arg HRTIM_EVENT_2: External event 2
  *                    @arg HRTIM_EVENT_3: External event 3
  *                    @arg HRTIM_EVENT_4: External event 4
  *                    @arg HRTIM_EVENT_5: External event 5
  *                    @arg HRTIM_EVENT_6: External event 6
  *                    @arg HRTIM_EVENT_7: External event 7
  *                    @arg HRTIM_EVENT_8: External event 8
  *                    @arg HRTIM_EVENT_9: External event 9
  *                    @arg HRTIM_EVENT_10: External event 10
  * @param  pTimerEventFilteringCfg: pointer to the timer event filtering configuration structure
  * @note This function must be called before starting the timer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_TimerEventFilteringConfig(HRTIM_HandleTypeDef * hhrtim,
                                                      uint32_t TimerIdx,
                                                      uint32_t Event,
                                                      HRTIM_TimerEventFilteringCfgTypeDef* pTimerEventFilteringCfg)
{
  uint32_t hrtim_eefr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_EVENT(Event));
  assert_param(IS_HRTIM_TIMEVENTFILTER(pTimerEventFilteringCfg->Filter));
  assert_param(IS_HRTIM_TIMEVENTLATCH(pTimerEventFilteringCfg->Latch));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Configure timer event filtering capabilities */
  switch (Event)
  {
  case HRTIM_EVENT_NONE:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1 = 0;
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2 = 0;
    }
    break;
  case HRTIM_EVENT_1:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1;
      hrtim_eefr &= ~(HRTIM_EEFR1_EE1FLTR | HRTIM_EEFR1_EE1LTCH);
      hrtim_eefr |= (pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_2:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1;
      hrtim_eefr &= ~(HRTIM_EEFR1_EE2FLTR | HRTIM_EEFR1_EE2LTCH);
      hrtim_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 6);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_3:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1;
      hrtim_eefr &= ~(HRTIM_EEFR1_EE3FLTR | HRTIM_EEFR1_EE3LTCH);
      hrtim_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 12);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_4:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1;
      hrtim_eefr &= ~(HRTIM_EEFR1_EE4FLTR | HRTIM_EEFR1_EE4LTCH);
      hrtim_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 18);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_5:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1;
      hrtim_eefr &= ~(HRTIM_EEFR1_EE5FLTR | HRTIM_EEFR1_EE5LTCH);
      hrtim_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 24);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR1 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_6:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2;
      hrtim_eefr &= ~(HRTIM_EEFR2_EE6FLTR | HRTIM_EEFR2_EE6LTCH);
      hrtim_eefr |= (pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_7:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2;
      hrtim_eefr &= ~(HRTIM_EEFR2_EE7FLTR | HRTIM_EEFR2_EE7LTCH);
      hrtim_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 6);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_8:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2;
      hrtim_eefr &= ~(HRTIM_EEFR2_EE8FLTR | HRTIM_EEFR2_EE8LTCH);
      hrtim_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 12);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_9:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2;
      hrtim_eefr &= ~(HRTIM_EEFR2_EE9FLTR | HRTIM_EEFR2_EE9LTCH);
      hrtim_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 18);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2 = hrtim_eefr;
    }
    break;
  case HRTIM_EVENT_10:
    {
      hrtim_eefr = hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2;
      hrtim_eefr &= ~(HRTIM_EEFR2_EE10FLTR | HRTIM_EEFR2_EE10LTCH);
      hrtim_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 24);
      hhrtim->Instance->sTimerxRegs[TimerIdx].EEFxR2 = hrtim_eefr;
    }
    break;
  }
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the deadtime insertion feature for a timer 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  pDeadTimeCfg: pointer to the deadtime insertion configuration structure
  * @retval HAL status
  * @note This function must be called before starting the timer
  */
HAL_StatusTypeDef HAL_HRTIM_DeadTimeConfig(HRTIM_HandleTypeDef * hhrtim,
                                           uint32_t TimerIdx,
                                           HRTIM_DeadTimeCfgTypeDef* pDeadTimeCfg)
{
  uint32_t hrtim_dtr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_TIMDEADTIME_PRESCALERRATIO(pDeadTimeCfg->Prescaler));
  assert_param(IS_HRTIM_TIMDEADTIME_RISINGSIGN(pDeadTimeCfg->RisingSign));
  assert_param(IS_HRTIM_TIMDEADTIME_RISINGLOCK(pDeadTimeCfg->RisingLock));
  assert_param(IS_HRTIM_TIMDEADTIME_RISINGSIGNLOCK(pDeadTimeCfg->RisingSignLock));
  assert_param(IS_HRTIM_TIMDEADTIME_FALLINGSIGN(pDeadTimeCfg->FallingSign));
  assert_param(IS_HRTIM_TIMDEADTIME_FALLINGLOCK(pDeadTimeCfg->FallingLock));
  assert_param(IS_HRTIM_TIMDEADTIME_FALLINGSIGNLOCK(pDeadTimeCfg->FallingSignLock));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  hrtim_dtr = hhrtim->Instance->sTimerxRegs[TimerIdx].DTxR;
     
  /* Clear timer deadtime configuration */
  hrtim_dtr &= ~(HRTIM_DTR_DTR | HRTIM_DTR_SDTR | HRTIM_DTR_DTPRSC |
                 HRTIM_DTR_DTRSLK | HRTIM_DTR_DTRLK | HRTIM_DTR_DTF |
                 HRTIM_DTR_SDTF | HRTIM_DTR_DTFSLK | HRTIM_DTR_DTFLK);
  
  /* Set timer deadtime configuration */
  hrtim_dtr |= pDeadTimeCfg->Prescaler;
  hrtim_dtr |= pDeadTimeCfg->RisingValue;
  hrtim_dtr |= pDeadTimeCfg->RisingSign;
  hrtim_dtr |= pDeadTimeCfg->RisingSignLock;
  hrtim_dtr |= pDeadTimeCfg->RisingLock;
  hrtim_dtr |= (pDeadTimeCfg->FallingValue << 16);
  hrtim_dtr |= pDeadTimeCfg->FallingSign;
  hrtim_dtr |= pDeadTimeCfg->FallingSignLock;
  hrtim_dtr |= pDeadTimeCfg->FallingLock;
    
  /* Update the HRTIM registers */  
  hhrtim->Instance->sTimerxRegs[TimerIdx].DTxR = hrtim_dtr;
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the chopper mode feature for a timer 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  pChopperModeCfg: pointer to the chopper mode configuration structure
  * @retval HAL status
  * @note This function must be called before configuring the timer output(s)
  */
HAL_StatusTypeDef HAL_HRTIM_ChopperModeConfig(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx,
                                              HRTIM_ChopperModeCfgTypeDef* pChopperModeCfg)
{
  uint32_t hrtim_chpr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CHOPPER_PRESCALERRATIO(pChopperModeCfg->CarrierFreq));
  assert_param(IS_HRTIM_CHOPPER_DUTYCYCLE(pChopperModeCfg->DutyCycle));
  assert_param(IS_HRTIM_CHOPPER_PULSEWIDTH(pChopperModeCfg->StartPulse));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  hrtim_chpr = hhrtim->Instance->sTimerxRegs[TimerIdx].CHPxR;
     
  /* Clear timer chopper mode configuration */
  hrtim_chpr &= ~(HRTIM_CHPR_CARFRQ | HRTIM_CHPR_CARDTY | HRTIM_CHPR_STRPW);
  
  /* Set timer choppe mode configuration */
  hrtim_chpr |= pChopperModeCfg->CarrierFreq;
  hrtim_chpr |= (pChopperModeCfg->DutyCycle);
  hrtim_chpr |= (pChopperModeCfg->StartPulse);
    
  /* Update the HRTIM registers */  
  hhrtim->Instance->sTimerxRegs[TimerIdx].CHPxR = hrtim_chpr;
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the burst DMA controller for a timer 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                  This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  RegistersToUpdate: registers to be written by DMA
  *                    This parameter can be any combination of the following values:
  *                    @arg HRTIM_BURSTDMA_CR: HRTIM_MCR or HRTIM_TIMxCR
  *                    @arg HRTIM_BURSTDMA_ICR: HRTIM_MICR or HRTIM_TIMxICR
  *                    @arg HRTIM_BURSTDMA_DIER: HRTIM_MDIER or HRTIM_TIMxDIER
  *                    @arg HRTIM_BURSTDMA_CNT: HRTIM_MCNT or HRTIM_TIMxCNT
  *                    @arg HRTIM_BURSTDMA_PER: HRTIM_MPER or HRTIM_TIMxPER
  *                    @arg HRTIM_BURSTDMA_REP: HRTIM_MREP or HRTIM_TIMxREP
  *                    @arg HRTIM_BURSTDMA_CMP1: HRTIM_MCMP1 or HRTIM_TIMxCMP1
  *                    @arg HRTIM_BURSTDMA_CMP2: HRTIM_MCMP2 or HRTIM_TIMxCMP2
  *                    @arg HRTIM_BURSTDMA_CMP3: HRTIM_MCMP3 or HRTIM_TIMxCMP3
  *                    @arg HRTIM_BURSTDMA_CMP4: HRTIM_MCMP4 or HRTIM_TIMxCMP4
  *                    @arg HRTIM_BURSTDMA_DTR: HRTIM_TIMxDTR
  *                    @arg HRTIM_BURSTDMA_SET1R: HRTIM_TIMxSET1R
  *                    @arg HRTIM_BURSTDMA_RST1R: HRTIM_TIMxRST1R
  *                    @arg HRTIM_BURSTDMA_SET2R: HRTIM_TIMxSET2R
  *                    @arg HRTIM_BURSTDMA_RST2R: HRTIM_TIMxRST2R
  *                    @arg HRTIM_BURSTDMA_EEFR1: HRTIM_TIMxEEFR1
  *                    @arg HRTIM_BURSTDMA_EEFR2: HRTIM_TIMxEEFR2
  *                    @arg HRTIM_BURSTDMA_RSTR: HRTIM_TIMxRSTR
  *                    @arg HRTIM_BURSTDMA_CHPR: HRTIM_TIMxCHPR
  *                    @arg HRTIM_BURSTDMA_OUTR: HRTIM_TIMxOUTR
  *                    @arg HRTIM_BURSTDMA_FLTR: HRTIM_TIMxFLTR
  * @retval HAL status
  * @note This function must be called before starting the timer
  */
HAL_StatusTypeDef HAL_HRTIM_BurstDMAConfig(HRTIM_HandleTypeDef * hhrtim,
                                           uint32_t TimerIdx,
                                           uint32_t RegistersToUpdate)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_BURSTDMA(TimerIdx, RegistersToUpdate));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Set the burst DMA timer update register */
  switch (TimerIdx) 
  {
  case HRTIM_TIMERINDEX_TIMER_A:
    {
      hhrtim->Instance->sCommonRegs.BDTAUPR = RegistersToUpdate;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_B:
    {
      hhrtim->Instance->sCommonRegs.BDTBUPR = RegistersToUpdate;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_C:
    {
      hhrtim->Instance->sCommonRegs.BDTCUPR = RegistersToUpdate;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_D:
    {
      hhrtim->Instance->sCommonRegs.BDTDUPR = RegistersToUpdate;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_E:
    {
      hhrtim->Instance->sCommonRegs.BDTEUPR = RegistersToUpdate;
    }
    break;
  case HRTIM_TIMERINDEX_MASTER:
    {
      hhrtim->Instance->sCommonRegs.BDMUPR = RegistersToUpdate;
    }
    break;
  }
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the compare unit of a timer operating in waveform mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CompareUnit: Compare unit to configure
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_COMPAREUNIT_1: Compare unit 1
  *                    @arg HRTIM_COMPAREUNIT_2: Compare unit 2
  *                    @arg HRTIM_COMPAREUNIT_3: Compare unit 3
  *                    @arg HRTIM_COMPAREUNIT_4: Compare unit 4
  * @param  pCompareCfg: pointer to the compare unit configuration structure
  * @note When auto delayed mode is required for compare unit 2 or compare unit 4, 
  *       application has to configure separately the capture unit. Capture unit 
  *       to configure in that case depends on the compare unit auto delayed mode
  *       is applied to (see below):
  *         Auto delayed on output compare 2: capture unit 1 must be configured
  *         Auto delayed on output compare 4: capture unit 2 must be configured
  * @retval HAL status
  * @note This function must be called before starting the timer
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformCompareConfig(HRTIM_HandleTypeDef * hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t CompareUnit,
                                                  HRTIM_CompareCfgTypeDef* pCompareCfg)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* Configure the compare unit */
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    switch (CompareUnit)
    {
      case HRTIM_COMPAREUNIT_1:
        {
        hhrtim->Instance->sMasterRegs.MCMP1R = pCompareCfg->CompareValue;
        }
        break;
      case HRTIM_COMPAREUNIT_2:
        {
        hhrtim->Instance->sMasterRegs.MCMP2R = pCompareCfg->CompareValue;
        }
        break;
      case HRTIM_COMPAREUNIT_3:
        {
        hhrtim->Instance->sMasterRegs.MCMP3R = pCompareCfg->CompareValue;
        }
        break;
      case HRTIM_COMPAREUNIT_4:
        {
        hhrtim->Instance->sMasterRegs.MCMP4R = pCompareCfg->CompareValue;
        }
        break;
    }
  }
  else
  {
    switch (CompareUnit)
    {
    case HRTIM_COMPAREUNIT_1:
      {
        /* Set the compare value */
        hhrtim->Instance->sTimerxRegs[TimerIdx].CMP1xR = pCompareCfg->CompareValue;
      }
      break;
    case HRTIM_COMPAREUNIT_2:
      {
        /* Check parameters */
        assert_param(IS_HRTIM_COMPAREUNIT_AUTODELAYEDMODE(CompareUnit, pCompareCfg->AutoDelayedMode));
        
        /* Set the compare value */
        hhrtim->Instance->sTimerxRegs[TimerIdx].CMP2xR = pCompareCfg->CompareValue;
        
        if (pCompareCfg->AutoDelayedMode != HRTIM_AUTODELAYEDMODE_REGULAR)
        {
          /* Configure auto-delayed mode */
          /* DELCMP2 bitfield must be reset when reprogrammed from one value */
          /* to the other to reinitialize properly the auto-delayed mechanism */
          hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR &= ~HRTIM_TIMCR_DELCMP2;
          hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR |= pCompareCfg->AutoDelayedMode;
          
          /* Set the compare value for timeout compare unit (if any) */
          if (pCompareCfg->AutoDelayedMode == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1)
          {
            hhrtim->Instance->sTimerxRegs[TimerIdx].CMP1xR = pCompareCfg->AutoDelayedTimeout;
          }
          else if (pCompareCfg->AutoDelayedMode == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3)
          {
            hhrtim->Instance->sTimerxRegs[TimerIdx].CMP3xR = pCompareCfg->AutoDelayedTimeout;
          }
        }
      }
      break;
    case HRTIM_COMPAREUNIT_3:
      {
        /* Set the compare value */
        hhrtim->Instance->sTimerxRegs[TimerIdx].CMP3xR = pCompareCfg->CompareValue;
      }
      break;
    case HRTIM_COMPAREUNIT_4:
      {
        /* Check parameters */
        assert_param(IS_HRTIM_COMPAREUNIT_AUTODELAYEDMODE(CompareUnit, pCompareCfg->AutoDelayedMode));
        
        /* Set the compare value */
        hhrtim->Instance->sTimerxRegs[TimerIdx].CMP4xR = pCompareCfg->CompareValue;
        
        if (pCompareCfg->AutoDelayedMode != HRTIM_AUTODELAYEDMODE_REGULAR)
        {
          /* Configure auto-delayed mode */
          /* DELCMP4 bitfield must be reset when reprogrammed from one value */
          /* to the other to reinitialize properly the auto-delayed mechanism */
          hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR &= ~HRTIM_TIMCR_DELCMP4;
          hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR |= (pCompareCfg->AutoDelayedMode << 2);
          
          /* Set the compare value for timeout compare unit (if any) */
          if (pCompareCfg->AutoDelayedMode == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1)
          {
            hhrtim->Instance->sTimerxRegs[TimerIdx].CMP1xR = pCompareCfg->AutoDelayedTimeout;
          }
          else if (pCompareCfg->AutoDelayedMode == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3)
          {
            hhrtim->Instance->sTimerxRegs[TimerIdx].CMP3xR = pCompareCfg->AutoDelayedTimeout;
          }
        }
      }
      break;
    }
  }
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the cature unit of a timer operating in waveform mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureUnit: Capture unit to configure
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @param  pCaptureCfg: pointer to the compare unit configuration structure
  * @retval HAL status
  * @note This function must be called before starting the timer
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformCaptureConfig(HRTIM_HandleTypeDef * hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t CaptureUnit,
                                                  HRTIM_CaptureCfgTypeDef* pCaptureCfg)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_CAPTURETRIGGER(TimerIdx, pCaptureCfg->Trigger));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Configure the capture unit */
  switch (CaptureUnit)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR = pCaptureCfg->Trigger;
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR = pCaptureCfg->Trigger;
    }
    break;
  }
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Configures the output of a timer operating in waveform mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2 
  * @param  pOutputCfg: pointer to the timer output configuration structure
  * @retval HAL status
  * @note This function must be called before configuring the timer and after 
  *       configuring the deadtime insertion feature (if required).
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformOutputConfig(HRTIM_HandleTypeDef * hhrtim,
                                                uint32_t TimerIdx,
                                                uint32_t Output,
                                                HRTIM_OutputCfgTypeDef * pOutputCfg)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, Output));
  assert_param(IS_HRTIM_OUTPUTPOLARITY(pOutputCfg->Polarity));
  assert_param(IS_HRTIM_OUTPUTIDLELEVEL(pOutputCfg->IdleLevel));
  assert_param(IS_HRTIM_OUTPUTIDLEMODE(pOutputCfg->IdleMode));
  assert_param(IS_HRTIM_OUTPUTFAULTLEVEL(pOutputCfg->FaultLevel));
  assert_param(IS_HRTIM_OUTPUTCHOPPERMODE(pOutputCfg->ChopperModeEnable));
  assert_param(IS_HRTIM_OUTPUTBURSTMODEENTRY(pOutputCfg->BurstModeEntryDelayed));

  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Configure the timer output */
  HRTIM_OutputConfig(hhrtim,
                     TimerIdx,
                     Output,
                     pOutputCfg);  
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Forces the timer output to its active or inactive state 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @param OutputLevel: indicates whether the output is forced to its active or inactive level
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUTLEVEL_ACTIVE: output is forced to its active level
  *                    @arg HRTIM_OUTPUTLEVEL_INACTIVE: output is forced to its inactive level
  * @retval HAL status
  * @note The 'software set/reset trigger' bit in the output set/reset registers 
  *       is automatically reset by hardware
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformSetOutputLevel(HRTIM_HandleTypeDef * hhrtim,
                                                   uint32_t TimerIdx,
                                                   uint32_t Output,
                                                   uint32_t OutputLevel)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, Output));
  assert_param(IS_HRTIM_OUTPUTLEVEL(OutputLevel));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Force timer output level */
  switch (Output)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      if (OutputLevel == HRTIM_OUTPUTLEVEL_ACTIVE)
      {
        /* Force output to its active state */
        hhrtim->Instance->sTimerxRegs[TimerIdx].SETx1R |= HRTIM_SET1R_SST;
      }
      else
      {
        /* Force output to its inactive state */
        hhrtim->Instance->sTimerxRegs[TimerIdx].RSTx1R |= HRTIM_RST1R_SRT;
      }
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      if (OutputLevel == HRTIM_OUTPUTLEVEL_ACTIVE)
      {
        /* Force output to its active state */
        hhrtim->Instance->sTimerxRegs[TimerIdx].SETx2R |= HRTIM_SET2R_SST;
      }
      else
      {
        /* Force output to its inactive state */
        hhrtim->Instance->sTimerxRegs[TimerIdx].RSTx2R |= HRTIM_RST2R_SRT;
      }
    }
    break;
  }
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Enables the generation of the waveform signal on the designated output(s)
  *         Ouputs can becombined (ORed) to allow for simultaneous output enabling
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  OutputsToStart: Timer output(s) to enable
  *                    This parameter can be any combination of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformOutputStart(HRTIM_HandleTypeDef * hhrtim,
                                                uint32_t OutputsToStart)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_OUTPUT(OutputsToStart));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable the HRTIM outputs */
  hhrtim->Instance->sCommonRegs.OENR |= (OutputsToStart);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Disables the generation of the waveform signal on the designated output(s)
  *         Ouputs can becombined (ORed) to allow for simultaneous output disabling
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  OutputsToStop: Timer output(s) to disable
  *                    This parameter can be any combination of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformOutputStop(HRTIM_HandleTypeDef * hhrtim,
                                               uint32_t OutputsToStop)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_OUTPUT(OutputsToStop));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable the HRTIM outputs */
  hhrtim->Instance->sCommonRegs.ODISR |= (OutputsToStop);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Starts the counter of the designated timer(s) operating in waveform mode
  *         Timers can be combined (ORed) to allow for simultaneous counter start
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: Timer counter(s) to start
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMERID_MASTER 
  *                   @arg HRTIM_TIMERID_TIMER_A 
  *                   @arg HRTIM_TIMERID_TIMER_B 
  *                   @arg HRTIM_TIMERID_TIMER_C 
  *                   @arg HRTIM_TIMERID_TIMER_D 
  *                   @arg HRTIM_TIMERID_TIMER_E 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformCounterStart(HRTIM_HandleTypeDef * hhrtim,
                                                 uint32_t Timers)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERID(Timers));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable timer(s) counter */
  hhrtim->Instance->sMasterRegs.MCR |= (Timers);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Stops the counter of the designated timer(s) operating in waveform mode
  *         Timers can be combined (ORed) to allow for simultaneous counter stop
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: Timer counter(s) to stop
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMER_MASTER 
  *                   @arg HRTIM_TIMER_A 
  *                   @arg HRTIM_TIMER_B 
  *                   @arg HRTIM_TIMER_C 
  *                   @arg HRTIM_TIMER_D 
  *                   @arg HRTIM_TIMER_E 
  * @retval HAL status
  * @note The counter of a timer is stopped only if all timer outputs are disabled   
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformCounterStop(HRTIM_HandleTypeDef * hhrtim,
                                                uint32_t Timers)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERID(Timers));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Disable timer(s) counter */
  hhrtim->Instance->sMasterRegs.MCR &= ~(Timers);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Starts the counter of the designated timer(s) operating in waveform mode
  *         Timers can be combined (ORed) to allow for simultaneous counter start
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: Timer counter(s) to start
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMERID_MASTER 
  *                   @arg HRTIM_TIMERID_A 
  *                   @arg HRTIM_TIMERID_B 
  *                   @arg HRTIM_TIMERID_C 
  *                   @arg HRTIM_TIMERID_D 
  *                   @arg HRTIM_TIMERID_E 
  * @note HRTIM interrupts (e.g. faults interrupts) and interrupts related
  *       to the timers to start are enabled within this function. 
  *       Interrupts to enable are selected through HAL_HRTIM_WaveformTimerConfig
  *       function.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformCounterStart_IT(HRTIM_HandleTypeDef * hhrtim,
                                                    uint32_t Timers)
{
  uint8_t timer_idx;
  
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERID(Timers));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* Enable HRTIM interrupts (if required) */
  __HAL_HRTIM_ENABLE_IT(hhrtim, hhrtim->Init.HRTIMInterruptResquests);
  
  /* Enable master timer related interrupts (if required) */
  if ((Timers & HRTIM_TIMERID_MASTER) != RESET)
  {
    __HAL_HRTIM_MASTER_ENABLE_IT(hhrtim, 
                                 hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].InterruptRequests);
  }
  
  /* Enable timing unit related interrupts (if required) */
  for (timer_idx = HRTIM_TIMERINDEX_TIMER_A ; 
       timer_idx < HRTIM_TIMERINDEX_MASTER ; 
       timer_idx++)
  {
    if ((Timers & TimerIdxToTimerId[timer_idx]) != RESET)
    {
      __HAL_HRTIM_TIMER_ENABLE_IT(hhrtim, 
                                  timer_idx, 
                                  hhrtim->TimerParam[timer_idx].InterruptRequests);
    }
  }
  
  /* Enable timer(s) counter */
  hhrtim->Instance->sMasterRegs.MCR |= (Timers);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;}

/**
  * @brief  Stops the counter of the designated timer(s) operating in waveform mode
  *         Timers can be combined (ORed) to allow for simultaneous counter stop
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: Timer counter(s) to stop
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMER_MASTER 
  *                   @arg HRTIM_TIMER_A 
  *                   @arg HRTIM_TIMER_B 
  *                   @arg HRTIM_TIMER_C 
  *                   @arg HRTIM_TIMER_D 
  *                   @arg HRTIM_TIMER_E 
  * @retval HAL status
  * @note The counter of a timer is stopped only if all timer outputs are disabled
  * @note All enabled timer related interrupts are disabled.
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformCounterStop_IT(HRTIM_HandleTypeDef * hhrtim,
                                                   uint32_t Timers)
{
  /* ++ WA */
  __IO uint32_t delai = (uint32_t)(0x17F);
  /* -- WA */
  
  uint8_t timer_idx;
  
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERID(Timers));
  
  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 

  /* Disable HRTIM interrupts (if required) */
  __HAL_HRTIM_DISABLE_IT(hhrtim, hhrtim->Init.HRTIMInterruptResquests);
  
  /* Disable master timer related interrupts (if required) */
  if ((Timers & HRTIM_TIMERID_MASTER) != RESET)
  {
    /* Interrupts enable flag must be cleared one by one */
    __HAL_HRTIM_MASTER_DISABLE_IT(hhrtim, hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].InterruptRequests); 
  }
  
  /* Disable timing unit related interrupts (if required) */
  for (timer_idx = HRTIM_TIMERINDEX_TIMER_A ; 
       timer_idx < HRTIM_TIMERINDEX_MASTER ; 
       timer_idx++)
  {
    if ((Timers & TimerIdxToTimerId[timer_idx]) != RESET)
    {
      __HAL_HRTIM_TIMER_DISABLE_IT(hhrtim, timer_idx, hhrtim->TimerParam[timer_idx].InterruptRequests);
    }
  }
  
  /* ++ WA */
  do { delai--; } while (delai != 0);
  /* -- WA */
  
  /* Disable timer(s) counter */
  hhrtim->Instance->sMasterRegs.MCR &= ~(Timers);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
}

/**
  * @brief  Starts the counter of the designated timer(s) operating in waveform mode
  *         Timers can be combined (ORed) to allow for simultaneous counter start
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: Timer counter(s) to start
  *                   This parameter can be any combination of the following values:
  *                   HRTIM_TIMER_MASTER 
  *                   @arg HRTIM_TIMER_A 
  *                   @arg HRTIM_TIMER_B 
  *                   @arg HRTIM_TIMER_C 
  *                   @arg HRTIM_TIMER_D 
  *                   @arg HRTIM_TIMER_E 
  * @retval HAL status
  * @note This function enables the dma request(s) mentionned in the timer
  *       configuration data structure for every timers to start.
  * @note The source memory address, the destination memory address and the
  *       size of each DMA transfer are specified at timer configuration time
  *       (see HAL_HRTIM_WaveformTimerConfig)
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformCounterStart_DMA(HRTIM_HandleTypeDef * hhrtim,
                                                     uint32_t Timers)
{
  uint8_t timer_idx;
  DMA_HandleTypeDef * hdma;
  
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERID(Timers));

  if((hhrtim->State == HAL_HRTIM_STATE_BUSY))
  {
     return HAL_BUSY;
  }

  hhrtim->State = HAL_HRTIM_STATE_BUSY;
  
  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  if (((Timers & HRTIM_TIMERID_MASTER) != RESET) &&
      (hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].DMARequests != 0))
  {
      /* Set the DMA error callback */
      hhrtim->hdmaMaster->XferErrorCallback = HRTIM_DMAError ;
      
      /* Set the DMA transfer completed callback */
      hhrtim->hdmaMaster->XferCpltCallback = HRTIM_DMAMasterCplt;
      
      /* Enable the DMA channel */
      HAL_DMA_Start_IT(hhrtim->hdmaMaster,
                       hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].DMASrcAddress,
                       hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].DMADstAddress,
                       hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].DMASize);
      
      /* Enable the timer DMA request */
      __HAL_HRTIM_MASTER_ENABLE_DMA(hhrtim, 
                                   hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].DMARequests);
  }
  
  for (timer_idx = HRTIM_TIMERINDEX_TIMER_A ; 
       timer_idx < HRTIM_TIMERINDEX_MASTER ; 
       timer_idx++)
  {
    if (((Timers & TimerIdxToTimerId[timer_idx]) != RESET) &&
         (hhrtim->TimerParam[timer_idx].DMARequests != 0))
    {
      /* Get the timer DMA handler */
      hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, timer_idx);

      /* Set the DMA error callback */
      hdma->XferErrorCallback = HRTIM_DMAError ;
      
      /* Set the DMA transfer completed callback */
      hdma->XferCpltCallback = HRTIM_DMATimerxCplt;
      
      /* Enable the DMA channel */
      HAL_DMA_Start_IT(hdma,
                       hhrtim->TimerParam[timer_idx].DMASrcAddress,
                       hhrtim->TimerParam[timer_idx].DMADstAddress,
                       hhrtim->TimerParam[timer_idx].DMASize);
      
      /* Enable the timer DMA request */
      __HAL_HRTIM_TIMER_ENABLE_DMA(hhrtim, 
                                   timer_idx,
                                   hhrtim->TimerParam[timer_idx].DMARequests); 
    }
  }

  /* Enable the timer counter */
  __HAL_HRTIM_ENABLE(hhrtim, Timers);

  hhrtim->State = HAL_HRTIM_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  
  
  return HAL_OK;
}

/**
  * @brief  Stops the counter of the designated timer(s) operating in waveform mode
  *         Timers can be combined (ORed) to allow for simultaneous counter stop
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: Timer counter(s) to stop
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMER_MASTER 
  *                   @arg HRTIM_TIMER_A 
  *                   @arg HRTIM_TIMER_B 
  *                   @arg HRTIM_TIMER_C 
  *                   @arg HRTIM_TIMER_D 
  *                   @arg HRTIM_TIMER_E 
  * @retval HAL status
  * @note  The counter of a timer is stopped only if all timer outputs are disabled
  * @note  All enabled timer related DMA requests are disabled.
  */
HAL_StatusTypeDef HAL_HRTIM_WaveformCounterStop_DMA(HRTIM_HandleTypeDef * hhrtim,
                                                    uint32_t Timers)
{
  uint8_t timer_idx;
  DMA_HandleTypeDef * hdma;

  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERID(Timers));

  hhrtim->State = HAL_HRTIM_STATE_BUSY; 

  if (((Timers & HRTIM_TIMERID_MASTER) != RESET) &&
      (hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].DMARequests != 0))
  { 
    /* Disable the DMA */
    HAL_DMA_Abort(hhrtim->hdmaMaster);
    
    /* Disable the DMA request(s) */
    __HAL_HRTIM_MASTER_DISABLE_DMA(hhrtim,
                                   hhrtim->TimerParam[HRTIM_TIMERINDEX_MASTER].DMARequests);
  }
  
  for (timer_idx = HRTIM_TIMERINDEX_TIMER_A ; 
       timer_idx < HRTIM_TIMERINDEX_MASTER ; 
       timer_idx++)
  {
    if (((Timers & TimerIdxToTimerId[timer_idx]) != RESET) &&
        (hhrtim->TimerParam[timer_idx].DMARequests != 0))
    {
      /* Get the timer DMA handler */
      hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, timer_idx);

      /* Disable the DMA */
      HAL_DMA_Abort(hdma);
      
    /* Disable the DMA request(s) */
      __HAL_HRTIM_TIMER_DISABLE_DMA(hhrtim,
                                    timer_idx,
                                    hhrtim->TimerParam[timer_idx].DMARequests);      
    }
  }
  
  /* Disable the timer counter */
  __HAL_HRTIM_DISABLE(hhrtim, Timers);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  return HAL_OK;
}

/**
  * @brief  Enables or disables the HRTIM burst mode controller.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Enable: Burst mode controller enabling
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_BURSTMODECTL_ENABLED: Burst mode enabled
  *                    @arg HRTIM_BURSTMODECTL_DISABLED: Burst mode disabled
  * @retval HAL status
  * @note This function must be called after starting the timer(s)
  */
HAL_StatusTypeDef HAL_HRTIM_BurstModeCtl(HRTIM_HandleTypeDef * hhrtim,
                                         uint32_t Enable)
{
  uint32_t hrtim_bmcr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_BURSTMODECTL(Enable));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Enable/Disable the burst mode controller */
  hrtim_bmcr = hhrtim->Instance->sCommonRegs.BMCR;
  hrtim_bmcr &= ~(HRTIM_BMCR_BME);
  hrtim_bmcr |= Enable;
  
  /* Update the HRTIM registers */
  hhrtim->Instance->sCommonRegs.BMCR = hrtim_bmcr;

  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Triggers the burst mode operation.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_BurstModeSoftwareTrigger(HRTIM_HandleTypeDef *hhrtim)
{
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Software trigger of the burst mode controller */
  hhrtim->Instance->sCommonRegs.BMTRGR |= HRTIM_BMTRGR_SW;

  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Triggers a software capture on the designed capture unit
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureUnit: Capture unit to trig
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval HAL status
  * @note The 'software capture' bit in the capure configuration register is
  *       automatically reset by hardware
  */
HAL_StatusTypeDef HAL_HRTIM_SoftwareCapture(HRTIM_HandleTypeDef * hhrtim,
                                            uint32_t TimerIdx,
                                            uint32_t CaptureUnit)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureUnit));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Force a software capture on concerned capture unit */
  switch (CaptureUnit)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xCR |= HRTIM_CPT1CR_SWCPT;
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xCR |= HRTIM_CPT2CR_SWCPT;
    }
    break;
  }
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Triggers the update of the registers of one or several timers
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: timers concerned with the software register update
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMERUPDATE_MASTER 
  *                   @arg HRTIM_TIMERUPDATE_A 
  *                   @arg HRTIM_TIMERUPDATE_B 
  *                   @arg HRTIM_TIMERUPDATE_C 
  *                   @arg HRTIM_TIMERUPDATE_D 
  *                   @arg HRTIM_TIMERUPDATE_E 
  * @retval HAL status
  * @note The 'software update' bits in the HRTIM conrol register 2 register are
  *       automatically reset by hardware
  */
HAL_StatusTypeDef HAL_HRTIM_SoftwareUpdate(HRTIM_HandleTypeDef * hhrtim,
                                           uint32_t Timers)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMERUPDATE(Timers));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Force timer(s) registers update */
  hhrtim->Instance->sCommonRegs.CR2 |= Timers;
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Triggers the reset of one or several timers
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: timers concerned with the software counter reset
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMERRESET_MASTER 
  *                   @arg HRTIM_TIMERRESET_TIMER_A 
  *                   @arg HRTIM_TIMERRESET_TIMER_B 
  *                   @arg HRTIM_TIMERRESET_TIMER_C 
  *                   @arg HRTIM_TIMERRESET_TIMER_D 
  *                   @arg HRTIM_TIMERRESET_TIMER_E 
  * @retval HAL status
  * @note The 'software reset' bits in the HRTIM conrol register 2  are
  *       automatically reset by hardware
  */
HAL_StatusTypeDef HAL_HRTIM_SoftwareReset(HRTIM_HandleTypeDef * hhrtim,
                                          uint32_t Timers)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMERRESET(Timers));
  
  if(hhrtim->State == HAL_HRTIM_STATE_BUSY)
  {
     return HAL_BUSY;
  }

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY;

  /* Force timer(s) registers reset */
  hhrtim->Instance->sCommonRegs.CR2 = Timers;
  
  hhrtim->State = HAL_HRTIM_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  

  return HAL_OK; 
}

/**
  * @brief  Starts a burst DMA operation to update HRTIM control registers content
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  BurstBufferAddress: address of the buffer the HRTIM control registers
  *                             content will be updated from.
  * @param  BurstBufferLength: size (in WORDS) of the burst buffer.
  * @retval HAL status
  * @note The TimerIdx parameter determines the dma channel to be used by the  
  *       DMA burst controller (see below)
  *       HRTIM_TIMERINDEX_MASTER: DMA channel 2 is used by the DMA burst controller
  *       HRTIM_TIMERINDEX_TIMER_A: DMA channel 3 is used by the DMA burst controller
  *       HRTIM_TIMERINDEX_TIMER_B: DMA channel 4 is used by the DMA burst controller
  *       HRTIM_TIMERINDEX_TIMER_C: DMA channel 5 is used by the DMA burst controller
  *       HRTIM_TIMERINDEX_TIMER_D: DMA channel 6 is used by the DMA burst controller
  *       HRTIM_TIMERINDEX_TIMER_E: DMA channel 7 is used by the DMA burst controller
  */
HAL_StatusTypeDef HAL_HRTIM_BurstDMATransfer(HRTIM_HandleTypeDef *hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t BurstBufferAddress,
                                             uint32_t BurstBufferLength)
{
  DMA_HandleTypeDef * hdma;

  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  
  if((hhrtim->State == HAL_HRTIM_STATE_BUSY))
  {
     return HAL_BUSY;
  }
  if((hhrtim->State == HAL_HRTIM_STATE_READY))
  {
    if((BurstBufferAddress == 0 ) || (BurstBufferLength == 0)) 
    {
      return HAL_ERROR;                                    
    }
    else
    {
      hhrtim->State = HAL_HRTIM_STATE_BUSY;
    }
  }
  
  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  /* Get the timer DMA handler */
  hdma = HRTIM_GetDMAHandleFromTimerIdx(hhrtim, TimerIdx);
  
  /* Set the DMA transfer completed callback */
  hdma->XferCpltCallback = HRTIM_BurstDMACplt;
  
  /* Set the DMA error callback */
  hdma->XferErrorCallback = HRTIM_DMAError ;
  
  /* Enable the DMA channel */
  HAL_DMA_Start_IT(hdma, 
                   BurstBufferAddress, 
                   (uint32_t)&(hhrtim->Instance->sCommonRegs.BDMADR),
                   BurstBufferLength);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 

  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);  
  
  return HAL_OK;
}

/**
  * @brief  Enables the transfer from preload to active registers for one
  *         or several timing units (including master timer)
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: Timer(s) concerned by the register preload enabling command
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMERUPDATE_MASTER 
  *                   @arg HRTIM_TIMERUPDATE_A 
  *                   @arg HRTIM_TIMERUPDATE_B 
  *                   @arg HRTIM_TIMERUPDATE_C 
  *                   @arg HRTIM_TIMERUPDATE_D 
  *                   @arg HRTIM_TIMERUPDATE_E 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_UpdateEnable(HRTIM_HandleTypeDef *hhrtim,
                                          uint32_t Timers)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERUPDATE(Timers));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable timer(s) registers update */
  hhrtim->Instance->sCommonRegs.CR1 &= ~(Timers);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
  }

/**
  * @brief  Disables the transfer from preload to active registers for one
  *         or several timing units (including master timer)
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Timers: Timer(s) concerned by the register preload disabling command
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMERUPDATE_MASTER 
  *                   @arg HRTIM_TIMERUPDATE_A 
  *                   @arg HRTIM_TIMERUPDATE_B 
  *                   @arg HRTIM_TIMERUPDATE_C 
  *                   @arg HRTIM_TIMERUPDATE_D 
  *                   @arg HRTIM_TIMERUPDATE_E 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_HRTIM_UpdateDisable(HRTIM_HandleTypeDef *hhrtim,
                                          uint32_t Timers)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERUPDATE(Timers));

  /* Process Locked */
  __HAL_LOCK(hhrtim);
  
  hhrtim->State = HAL_HRTIM_STATE_BUSY; 
  
  /* Enable timer(s) registers update */
  hhrtim->Instance->sCommonRegs.CR1 |= (Timers);
  
  hhrtim->State = HAL_HRTIM_STATE_READY; 
                  
  /* Process Unlocked */
  __HAL_UNLOCK(hhrtim);      
  
  return HAL_OK;
  }

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group9 Peripheral state functions
 *  @brief    Functions used to get HRTIM or HRTIM timer specific
 *            information.
 *
@verbatim    
 ===============================================================================
              ##### Peripheral State functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Get HRTIM HAL state 
      (+) Get captured value 
      (+) Get HRTIM timer output level 
      (+) Get HRTIM timer output state 
      (+) Get delayed protection status  
      (+) Get burst status 
      (+) Get current push-pull status  
      (+) Get idle push-pull status  

@endverbatim
  * @{
  */

/**
  * @brief  return the HRTIM HAL state
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval HAL state
  */
HAL_HRTIM_StateTypeDef HAL_HRTIM_GetState(HRTIM_HandleTypeDef* hhrtim)
{
  /* Return ADC state */
  return hhrtim->State;
}

/**
  * @brief  Returns actual value of the capture register of the designated capture unit 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  CaptureUnit: Capture unit to trig
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval Captured value
  */
uint32_t HAL_HRTIM_GetCapturedValue(HRTIM_HandleTypeDef * hhrtim,
                                    uint32_t TimerIdx,
                                    uint32_t CaptureUnit)
{
  uint32_t captured_value = 0;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureUnit));

  /* Read captured value */
  switch (CaptureUnit)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      captured_value = hhrtim->Instance->sTimerxRegs[TimerIdx].CPT1xR;
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      captured_value = hhrtim->Instance->sTimerxRegs[TimerIdx].CPT2xR;
    }
    break;
  }
  
  return captured_value; 
}

/**
  * @brief  Returns actual level (active or inactive) of the designated output 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval Output level
  * @note Returned output level is taken before the output stage (chopper, 
  *        polarity).
  */
uint32_t HAL_HRTIM_WaveformGetOutputLevel(HRTIM_HandleTypeDef * hhrtim,
                                          uint32_t TimerIdx,
                                          uint32_t Output)
{
  uint32_t output_level = HRTIM_OUTPUTLEVEL_INACTIVE;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, Output));
  
  /* Read the output level */
  switch (Output)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      if ((hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxISR & HRTIM_TIMISR_O1CPY) != RESET)
      {
        output_level = HRTIM_OUTPUTLEVEL_ACTIVE;
      }
      else
      {
        output_level = HRTIM_OUTPUTLEVEL_INACTIVE;
      }
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      if ((hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxISR & HRTIM_TIMISR_O2CPY) != RESET)
      {
        output_level = HRTIM_OUTPUTLEVEL_ACTIVE;
      }
      else
      {
        output_level = HRTIM_OUTPUTLEVEL_INACTIVE;
      }
    }
    break;
  }
  
  return output_level; 
}

/**
  * @brief  Returns actual state (RUN, IDLE, FAULT) of the designated output 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval Output state
  */
uint32_t HAL_HRTIM_WaveformGetOutputState(HRTIM_HandleTypeDef * hhrtim,
                                          uint32_t TimerIdx,
                                          uint32_t Output)
{
  uint32_t output_bit = 0;
  uint32_t output_state = HRTIM_OUTPUTSTATE_IDLE;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, Output));
  
  /* Set output state according to output control status and output disable status */
  switch (Output)
  {
  case HRTIM_OUTPUT_TA1:
    {
      output_bit = HRTIM_OENR_TA1OEN;
    }
    break;
  case HRTIM_OUTPUT_TA2:
    {
      output_bit = HRTIM_OENR_TA2OEN;
    }
    break;
  case HRTIM_OUTPUT_TB1:
    {
      output_bit = HRTIM_OENR_TB1OEN;
    }
    break;
  case HRTIM_OUTPUT_TB2:
    {
      output_bit = HRTIM_OENR_TB2OEN;
    }
    break;
  case HRTIM_OUTPUT_TC1:
    {
      output_bit = HRTIM_OENR_TC1OEN;
    }
    break;
  case HRTIM_OUTPUT_TC2:
    {
      output_bit = HRTIM_OENR_TC2OEN;
    }
    break;
  case HRTIM_OUTPUT_TD1:
    {
      output_bit = HRTIM_OENR_TD1OEN;
    }
    break;
  case HRTIM_OUTPUT_TD2:
    {
      output_bit = HRTIM_OENR_TD2OEN;
    }
    break;
  case HRTIM_OUTPUT_TE1:
    {
      output_bit = HRTIM_OENR_TE1OEN;
    }
    break;
  case HRTIM_OUTPUT_TE2:
    {
      output_bit = HRTIM_OENR_TE2OEN;
    }
    break;
  }
  
  if ((hhrtim->Instance->sCommonRegs.OENR & output_bit) != RESET)
  {
    /* Output is enabled: output in RUN state (whatever ouput disable status is)*/
    output_state = HRTIM_OUTPUTSTATE_RUN;
  }
  else
  {
    if ((hhrtim->Instance->sCommonRegs.ODSR & output_bit) != RESET)
    {
    /* Output is disabled: output in FAULT state */
      output_state = HRTIM_OUTPUTSTATE_FAULT;
    }
    else
    {
      /* Output is disabled: output in IDLE state */
      output_state = HRTIM_OUTPUTSTATE_IDLE;
    }
  }
  
  return(output_state);  
}

/**
  * @brief  Returns the level (active or inactive) of the designated output 
  *         when the delayed protection was triggered 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer E - Ouput 2
  * @retval Delayed protection status 
  */
uint32_t HAL_HRTIM_GetDelayedProtectionStatus(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx,
                                              uint32_t Output)
{
  uint32_t delayed_protection_status = HRTIM_OUTPUTLEVEL_INACTIVE;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, Output));

  /* Read the delayed protection status */
  switch (Output)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      if ((hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxISR & HRTIM_TIMISR_O1STAT) != RESET)
      {
        /* Output 1 was active when the delayed idle protection was triggered */
        delayed_protection_status = HRTIM_OUTPUTLEVEL_ACTIVE;
      }
      else
      {
        /* Output 1 was inactive when the delayed idle protection was triggered */
        delayed_protection_status = HRTIM_OUTPUTLEVEL_INACTIVE;
      }
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      if ((hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxISR & HRTIM_TIMISR_O2STAT) != RESET)
      {
        /* Output 2 was active when the delayed idle protection was triggered */
        delayed_protection_status = HRTIM_OUTPUTLEVEL_ACTIVE;
      }
      else
      {
        /* Output 2 was inactive when the delayed idle protection was triggered */
        delayed_protection_status = HRTIM_OUTPUTLEVEL_INACTIVE;
      }
    }
    break;
  }
  
  return delayed_protection_status;
}

/**
  * @brief  Returns the actual status (active or inactive) of the burst mode controller 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval Burst mode controller status 
  */
uint32_t HAL_HRTIM_GetBurstStatus(HRTIM_HandleTypeDef * hhrtim)
{
  uint32_t burst_mode_status;

  /* Read burst mode status */
  burst_mode_status = (hhrtim->Instance->sCommonRegs.BMCR & HRTIM_BMCR_BMSTAT);
  
  return burst_mode_status; 
}

/**
  * @brief  Indicates on which output the signal is currently active (when the
  *         push pull mode is enabled)
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval Burst mode controller status 
  */
uint32_t HAL_HRTIM_GetCurrentPushPullStatus(HRTIM_HandleTypeDef * hhrtim,
                                            uint32_t TimerIdx)
{
  uint32_t current_pushpull_status;

   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));

  /* Read current push pull status */
  current_pushpull_status = (hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxISR & HRTIM_TIMISR_CPPSTAT);
  
  return current_pushpull_status; 
}


/**
  * @brief  Indicates on which output the signal was applied, in push-pull mode
            balanced fault mode or delayed idle mode, when the protection was triggered
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval Idle Push Pull Status 
  */
uint32_t HAL_HRTIM_GetIdlePushPullStatus(HRTIM_HandleTypeDef * hhrtim,
                                         uint32_t TimerIdx)
{
  uint32_t idle_pushpull_status;

   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));

  /* Read current push pull status */
  idle_pushpull_status = (hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxISR & HRTIM_TIMISR_IPPSTAT);
  
  return idle_pushpull_status; 
}

/**
  * @}
  */

/** @defgroup HRTIM_Exported_Functions_Group10 Interrupts handling
 *  @brief  Functions called when HRTIM generates an interrupt
 *          7 interrupts can be generated by the master timer:
 *            - Master timer registers update
 *            - Synchronization event received
 *            - Master timer repetition event
 *            - Master Compare 1 to 4 event
 *          14 interrupts can be generated by each timing unit:
 *            - Delayed protection triggered
 *            - Counter reset or roll-over event
 *            - Output 1 and output 2 reset (transition active to inactive)
 *            - Output 1 and output 2 set (transition inactive to active)
 *            - Capture 1 and 2 events
 *            - Timing unit registers update
 *            - Repetition event
 *            - Compare 1 to 4 event
 *          8 global interrupts are generated for the whole HRTIM:
 *            - System fault and Fault 1 to 5 (regardless of the timing unit attribution)
 *            - DLL calibration done
 *            - Burst mode period completed
 *
@verbatim   
 ===============================================================================
                      ##### HRTIM interrupts handling #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the HRTIM  
    interrupts
      (+)  HRTIM interrupt handler
      (+)  Callback function called when Fault1 interrupt occurs
      (+)  Callback function called when Fault2 interrupt occurs
      (+)  Callback function called when Fault3 interrupt occurs
      (+)  Callback function called when Fault4 interrupt occurs
      (+)  Callback function called when Fault5 interrupt occurs
      (+)  Callback function called when system Fault interrupt occurs
      (+)  Callback function called when DLL ready interrupt occurs
      (+)  Callback function called when burst mode period interrupt occurs
      (+)  Callback function called when synchronization input interrupt occurs
      (+)  Callback function called when a timer register update interrupt occurs
      (+)  Callback function called when a timer repetition interrupt occurs
      (+)  Callback function called when a compare 1 match interrupt occurs
      (+)  Callback function called when a compare 2 match interrupt occurs
      (+)  Callback function called when a compare 3 match interrupt occurs
      (+)  Callback function called when a compare 4 match interrupt occurs
      (+)  Callback function called when a capture 1 interrupt occurs
      (+)  Callback function called when a capture 2 interrupt occurs
      (+)  Callback function called when a delayed protection interrupt occurs
      (+)  Callback function called when a timer counter reset interrupt occurs
      (+)  Callback function called when a timer output 1 set interrupt occurs
      (+)  Callback function called when a timer output 1 reset interrupt occurs
      (+)  Callback function called when a timer output 2 set interrupt occurs
      (+)  Callback function called when a timer output 2 reset interrupt occurs
      (+)  Callback function called when a timer output 2 reset interrupt occurs
      (+)  Callback function called upon completion of a burst DMA transfer

@endverbatim
  * @{
  */

/**
  * @brief  This function handles HRTIM interrupt request.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be any value of @ref HRTIM_Timer_Index
  * @retval None
  */
void HAL_HRTIM_IRQHandler(HRTIM_HandleTypeDef * hhrtim,
                          uint32_t TimerIdx)
{
  /* HRTIM interrupts handling */
  if (TimerIdx == HRTIM_TIMERINDEX_COMMON)
  {
    HRTIM_HRTIM_ISR(hhrtim);
  }
  else if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    /* Master related interrupts handling */
      HRTIM_Master_ISR(hhrtim);
  }
  else
  {
    /* Timing unit related interrupts handling */
    HRTIM_Timer_ISR(hhrtim, TimerIdx);
  }
  
}

/**
  * @brief  Callback function invoked when a fault 1 interrupt occured
  * @param  hhrtim: pointer to HAL HRTIM handle  * @retval None
  * @retval None
  */
__weak void HAL_HRTIM_Fault1Callback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Fault1Callback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a fault 2 interrupt occured
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval None
  */
__weak void HAL_HRTIM_Fault2Callback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Fault2Callback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a fault 3 interrupt occured
  * @param  hhrtim: pointer to HAL HRTIM handle 
  * @retval None
  */
__weak void HAL_HRTIM_Fault3Callback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Fault3Callback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a fault 4 interrupt occured
  * @param  hhrtim: pointer to HAL HRTIM handle 
  * @retval None
  */
__weak void HAL_HRTIM_Fault4Callback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Fault4Callback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a fault 5 interrupt occured
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @retval None
  */
__weak void HAL_HRTIM_Fault5Callback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Fault5Callback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a system fault interrupt occured
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @retval None
  */
__weak void HAL_HRTIM_SystemFaultCallback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_SystemFaultCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a the DLL calibration is completed
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @retval None
  */
__weak void HAL_HRTIM_DLLCalbrationReadyCallback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_DLLCalbrationCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the end of the burst mode period is reached
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @retval None
  */
__weak void HAL_HRTIM_BurstModePeriodCallback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_BurstModeCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a synchronization input event is received
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @retval None
  */
__weak void HAL_HRTIM_SynchronizationEventCallback(HRTIM_HandleTypeDef * hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Master_SynchronizationEventCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when timer registers are updated
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_RegistersUpdateCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Master_RegistersUpdateCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when timer repetition period has elapsed
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_RepetitionEventCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Master_RepetitionEventCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer counter matches the value
  *         programmed in the compare 1 register
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_Compare1EventCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Master_Compare1EventCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer counter matches the value
  *         programmed in the compare 2 register
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @retval None
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  */
__weak void HAL_HRTIM_Compare2EventCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Master_Compare2EventCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer counter matches the value
  *         programmed in the compare 3 register
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_Compare3EventCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Master_Compare3EventCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer counter matches the value
  *         programmed in the compare 4 register
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_Compare4EventCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Master_Compare4EventCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer x capture 1 event occurs
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_Capture1EventCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Timer_Capture1EventCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer x capture 2 event occurs
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_Capture2EventCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Timer_Capture2EventCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the delayed idle or balanced idle mode is 
  *         entered
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_DelayedProtectionCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Timer_DelayedProtectionCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer x counter reset/roll-over
  *         event occurs
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_CounterResetCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Timer_CounterResetCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer x output 1 is set
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_Output1SetCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Timer_Output1SetCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer x output 1 is reset
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_Output1ResetCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Timer_Output1ResetCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer x output 2 is set
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_Output2SetCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Timer_Output2SetCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when the timer x output 2 is reset
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
 * @retval None
  */
__weak void HAL_HRTIM_Output2ResetCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Timer_Output2ResetCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a DMA burst transfer is completed
  * @param  hhrtim: pointer to HAL HRTIM handle  
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_MASTER  for master timer
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
  */
__weak void HAL_HRTIM_BurstDMATransferCallback(HRTIM_HandleTypeDef * hhrtim,
                                               uint32_t TimerIdx)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_BurstDMATransferCallback could be implenetd in the user file
   */ 
}

/**
  * @brief  Callback function invoked when a DMA error occurs
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval None
  */
__weak void HAL_HRTIM_ErrorCallback(HRTIM_HandleTypeDef *hhrtim)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_ErrorCallback could be implenetd in the user file
   */ 
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup HRTIM_Private_Functions HRTIM Private Functions
  * @{
  */

/**
  * @brief  Configures the master timer time base
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  pTimeBaseCfg: pointer to the time base configuration structure
  * @retval None
  */
static void  HRTIM_MasterBase_Config(HRTIM_HandleTypeDef * hhrtim, 
                                     HRTIM_TimeBaseCfgTypeDef * pTimeBaseCfg)
{
  uint32_t hrtim_mcr;
  
  /* Configure master timer */
  hrtim_mcr = hhrtim->Instance->sMasterRegs.MCR;
  
  /* Set the prescaler ratio */
  hrtim_mcr &= (uint32_t) ~(HRTIM_MCR_CK_PSC);
  hrtim_mcr |= (uint32_t)pTimeBaseCfg->PrescalerRatio;
  
  /* Set the operating mode */
  hrtim_mcr &= (uint32_t) ~(HRTIM_MCR_CONT | HRTIM_MCR_RETRIG);
  hrtim_mcr |= (uint32_t)pTimeBaseCfg->Mode;
  
  /* Update the HRTIM registers */
  hhrtim->Instance->sMasterRegs.MCR  = hrtim_mcr;
  hhrtim->Instance->sMasterRegs.MPER = pTimeBaseCfg->Period;
  hhrtim->Instance->sMasterRegs.MREP = pTimeBaseCfg->RepetitionCounter;
}

/**
  * @brief  Configures timing unit (timer A to timer E) time base
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @param  pTimeBaseCfg: pointer to the time base configuration structure
  * @retval None
  */
static void  HRTIM_TimingUnitBase_Config(HRTIM_HandleTypeDef * hhrtim,
                                         uint32_t TimerIdx ,
                                         HRTIM_TimeBaseCfgTypeDef * pTimeBaseCfg)
{
  uint32_t hrtim_timcr;
  
  /* Configure master timing unit */
  hrtim_timcr = hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR;
 
  /* Set the prescaler ratio */
  hrtim_timcr &= (uint32_t) ~(HRTIM_TIMCR_CK_PSC);
  hrtim_timcr |= (uint32_t)pTimeBaseCfg->PrescalerRatio;

  /* Set the operating mode */
  hrtim_timcr &= (uint32_t) ~(HRTIM_TIMCR_CONT | HRTIM_TIMCR_RETRIG);
  hrtim_timcr |= (uint32_t)pTimeBaseCfg->Mode;
  
  /* Update the HRTIM registers */
  hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR  = hrtim_timcr;
  hhrtim->Instance->sTimerxRegs[TimerIdx].PERxR = pTimeBaseCfg->Period;
  hhrtim->Instance->sTimerxRegs[TimerIdx].REPxR = pTimeBaseCfg->RepetitionCounter;
}

/**
  * @brief  Configures the master timer in waveform mode
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  pTimerCfg: pointer to the timer configuration data structure
  * @retval None
  */
static void  HRTIM_MasterWaveform_Config(HRTIM_HandleTypeDef * hhrtim, 
                                         HRTIM_TimerCfgTypeDef * pTimerCfg)
{
  uint32_t hrtim_mcr;
  uint32_t hrtim_bmcr;
  
  /* Configure master timer */
  hrtim_mcr = hhrtim->Instance->sMasterRegs.MCR;
  hrtim_bmcr = hhrtim->Instance->sCommonRegs.BMCR;
  
  /* Enable/Disable the half mode */
  hrtim_mcr &= ~(HRTIM_MCR_HALF);
  hrtim_mcr |= pTimerCfg->HalfModeEnable;
  
  /* Enable/Disable the timer start upon synchronization event reception */
  hrtim_mcr &= ~(HRTIM_MCR_SYNCSTRTM);
  hrtim_mcr |= pTimerCfg->StartOnSync;
 
  /* Enable/Disable the timer reset upon synchronization event reception */
  hrtim_mcr &= ~(HRTIM_MCR_SYNCRSTM);
  hrtim_mcr |= pTimerCfg->ResetOnSync;
  
  /* Enable/Disable the DAC synchronization event generation */
  hrtim_mcr &= ~(HRTIM_MCR_DACSYNC);
  hrtim_mcr |= pTimerCfg->DACSynchro;
  
  /* Enable/Disable preload meachanism for timer registers */
  hrtim_mcr &= ~(HRTIM_MCR_PREEN);
  hrtim_mcr |= pTimerCfg->PreloadEnable;
  
  /* Master timer registers update handling */
  hrtim_mcr &= ~(HRTIM_MCR_BRSTDMA);
  hrtim_mcr |= (pTimerCfg->UpdateGating << 2);
  
  /* Enable/Disable registers update on repetition */
  hrtim_mcr &= ~(HRTIM_MCR_MREPU);
  hrtim_mcr |= pTimerCfg->RepetitionUpdate;
  
  /* Set the timer burst mode */
  hrtim_bmcr &= ~(HRTIM_BMCR_MTBM);
  hrtim_bmcr |= pTimerCfg->BurstMode;

  /* Update the HRTIM registers */
  hhrtim->Instance->sMasterRegs.MCR  = hrtim_mcr;
  hhrtim->Instance->sCommonRegs.BMCR = hrtim_bmcr;
}

/**
  * @brief  Configures timing unit (timer A to timer E) in waveform mode 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @param  pTimerCfg: pointer to the timer configuration data structure
  * @retval None
  */
static void  HRTIM_TimingUnitWaveform_Config(HRTIM_HandleTypeDef * hhrtim, 
                                             uint32_t TimerIdx, 
                                             HRTIM_TimerCfgTypeDef * pTimerCfg)
{
  uint32_t hrtim_timcr;
  uint32_t hrtim_timfltr;
  uint32_t hrtim_timoutr;
  uint32_t hrtim_timrstr;
  uint32_t hrtim_bmcr;
  
  /* UPDGAT bitfield must be reset before programming a new value */
  hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR &= ~(HRTIM_TIMCR_UPDGAT);

  /* Configure timing unit (Timer A to Timer E) */
  hrtim_timcr   = hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR;
  hrtim_timfltr = hhrtim->Instance->sTimerxRegs[TimerIdx].FLTxR;
  hrtim_timoutr = hhrtim->Instance->sTimerxRegs[TimerIdx].OUTxR;
  hrtim_timrstr = hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR;
  hrtim_bmcr    = hhrtim->Instance->sCommonRegs.BMCR;
  
  /* Enable/Disable the half mode */
  hrtim_timcr &= ~(HRTIM_TIMCR_HALF);
  hrtim_timcr |= pTimerCfg->HalfModeEnable;
  
  /* Enable/Disable the timer start upon synchronization event reception */
  hrtim_timcr &= ~(HRTIM_TIMCR_SYNCSTRT);
  hrtim_timcr |= pTimerCfg->StartOnSync;
 
  /* Enable/Disable the timer reset upon synchronization event reception */
  hrtim_timcr &= ~(HRTIM_TIMCR_SYNCRST);
  hrtim_timcr |= pTimerCfg->ResetOnSync;
  
  /* Enable/Disable the DAC synchronization event generation */
  hrtim_timcr &= ~(HRTIM_TIMCR_DACSYNC);
  hrtim_timcr |= pTimerCfg->DACSynchro;
  
  /* Enable/Disable preload meachanism for timer registers */
  hrtim_timcr &= ~(HRTIM_TIMCR_PREEN);
  hrtim_timcr |= pTimerCfg->PreloadEnable;
  
  /* Timing unit registers update handling */
  hrtim_timcr &= ~(HRTIM_TIMCR_UPDGAT);
  hrtim_timcr |= pTimerCfg->UpdateGating;
  
  /* Enable/Disable registers update on repetition */
  hrtim_timcr &= ~(HRTIM_TIMCR_TREPU);
  if (pTimerCfg->RepetitionUpdate == HRTIM_UPDATEONREPETITION_ENABLED)
  {
    hrtim_timcr |= HRTIM_TIMCR_TREPU;
  }

  /* Set the push-pull mode */
  hrtim_timcr &= ~(HRTIM_TIMCR_PSHPLL);
  hrtim_timcr |= pTimerCfg->PushPull;
  
  /* Enable/Disable registers update on timer counter reset */
  hrtim_timcr &= ~(HRTIM_TIMCR_TRSTU);
  hrtim_timcr |= pTimerCfg->ResetUpdate;
  
  /* Set the timer update trigger */
  hrtim_timcr &= ~(HRTIM_TIMCR_TIMUPDATETRIGGER);
  hrtim_timcr |= pTimerCfg->UpdateTrigger;
  
  
  /* Enable/Disable the fault channel at timer level */
  hrtim_timfltr &= ~(HRTIM_FLTR_FLTxEN);
  hrtim_timfltr |= (pTimerCfg->FaultEnable & HRTIM_FLTR_FLTxEN);
  
  /* Lock/Unlock fault sources at timer level */
  hrtim_timfltr &= ~(HRTIM_FLTR_FLTLCK);
  hrtim_timfltr |= pTimerCfg->FaultLock;
  
  /* The deadtime cannot be used simultaneously with the push-pull mode */
  if (pTimerCfg->PushPull == HRTIM_TIMPUSHPULLMODE_DISABLED)
  {
    /* Enable/Disable dead time insertion at timer level */
    hrtim_timoutr &= ~(HRTIM_OUTR_DTEN);
    hrtim_timoutr |= pTimerCfg->DeadTimeInsertion;
  }
  
  /* Enable/Disable delayed protection at timer level
     Delayed Idle is available whatever the timer operating mode (regular, push-pull)
     Balanced Idle is only available in push-pull mode
  */
  if (   ((pTimerCfg->DelayedProtectionMode != HRTIM_TIMDELAYEDPROTECTION_BALANCED_EEV68)
      && (pTimerCfg->DelayedProtectionMode != HRTIM_TIMDELAYEDPROTECTION_BALANCED_EEV79))
      || (pTimerCfg->PushPull == HRTIM_TIMPUSHPULLMODE_ENABLED))
  {
    hrtim_timoutr &= ~(HRTIM_OUTR_DLYPRT| HRTIM_OUTR_DLYPRTEN);
    hrtim_timoutr |= pTimerCfg->DelayedProtectionMode;
  }
    
  /* Set the timer counter reset trigger */
  hrtim_timrstr = pTimerCfg->ResetTrigger;

  /* Set the timer burst mode */
  switch (TimerIdx)
  {
  case HRTIM_TIMERINDEX_TIMER_A:
    {
      hrtim_bmcr &= ~(HRTIM_BMCR_TABM);
      hrtim_bmcr |= ( pTimerCfg->BurstMode << 1);
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_B:
    {
      hrtim_bmcr &= ~(HRTIM_BMCR_TBBM);
      hrtim_bmcr |= ( pTimerCfg->BurstMode << 2);
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_C:
    {
      hrtim_bmcr &= ~(HRTIM_BMCR_TCBM);
      hrtim_bmcr |= ( pTimerCfg->BurstMode << 3);
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_D:
    {
      hrtim_bmcr &= ~(HRTIM_BMCR_TDBM);
      hrtim_bmcr |= ( pTimerCfg->BurstMode << 4);
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_E:
    {
      hrtim_bmcr &= ~(HRTIM_BMCR_TEBM);
      hrtim_bmcr |= ( pTimerCfg->BurstMode << 5);
    }
    break;
  }

  /* Update the HRTIM registers */
  hhrtim->Instance->sTimerxRegs[TimerIdx].TIMxCR  = hrtim_timcr;
  hhrtim->Instance->sTimerxRegs[TimerIdx].FLTxR = hrtim_timfltr;
  hhrtim->Instance->sTimerxRegs[TimerIdx].OUTxR = hrtim_timoutr;
  hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = hrtim_timrstr;  
  hhrtim->Instance->sCommonRegs.BMCR = hrtim_bmcr;
}

/**
  * @brief  Configures a compare unit 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @param  CompareUnit: Compare unit identifier
  * @param  pCompareCfg: pointer to the compare unit configuration data structure
  * @retval None
  */
static void  HRTIM_CompareUnitConfig(HRTIM_HandleTypeDef * hhrtim,
                                     uint32_t TimerIdx,
                                     uint32_t CompareUnit,
                                     HRTIM_CompareCfgTypeDef * pCompareCfg)
{
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    /* Configure the compare unit of the master timer */
    switch (CompareUnit)
    {
    case HRTIM_COMPAREUNIT_1:
      {
        hhrtim->Instance->sMasterRegs.MCMP1R = pCompareCfg->CompareValue;
      }
      break;
    case HRTIM_COMPAREUNIT_2:
      {
        hhrtim->Instance->sMasterRegs.MCMP2R = pCompareCfg->CompareValue;
      }
      break;
    case HRTIM_COMPAREUNIT_3:
      {
        hhrtim->Instance->sMasterRegs.MCMP3R = pCompareCfg->CompareValue;
      }
      break;
    case HRTIM_COMPAREUNIT_4:
      {
        hhrtim->Instance->sMasterRegs.MCMP4R = pCompareCfg->CompareValue;
      }
      break;
    }
  }
  else
  {
    /* Configure the compare unit of the timing unit */
    switch (CompareUnit)
    {
    case HRTIM_COMPAREUNIT_1:
      {
        hhrtim->Instance->sTimerxRegs[TimerIdx].CMP1xR = pCompareCfg->CompareValue;
      }
      break;
    case HRTIM_COMPAREUNIT_2:
      {
        hhrtim->Instance->sTimerxRegs[TimerIdx].CMP2xR = pCompareCfg->CompareValue;
      }
      break;
    case HRTIM_COMPAREUNIT_3:
      {
        hhrtim->Instance->sTimerxRegs[TimerIdx].CMP3xR = pCompareCfg->CompareValue;
      }
      break;
    case HRTIM_COMPAREUNIT_4:
      {
        hhrtim->Instance->sTimerxRegs[TimerIdx].CMP4xR = pCompareCfg->CompareValue;
      }
      break;
    }    
  }
}

/**
  * @brief  Configures a capture unit 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @param  CaptureUnit: Capture unit identifier
  * @param  Event: Event reference
  * @retval None
  */
static void HRTIM_CaptureUnitConfig(HRTIM_HandleTypeDef * hhrtim,
                                    uint32_t TimerIdx,
                                    uint32_t CaptureUnit,
                                    uint32_t Event)
{
  uint32_t CaptureTrigger = 0xFFFFFFFF;
  
  switch (Event)
  {
  case HRTIM_EVENT_1:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_1;
    }
    break;
  case HRTIM_EVENT_2:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_2;
    }
    break;
  case HRTIM_EVENT_3:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_3;
    }
    break;
  case HRTIM_EVENT_4:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_4;
    }
    break;
  case HRTIM_EVENT_5:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_5;
    }
    break;
  case HRTIM_EVENT_6:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_6;
    }
    break;
  case HRTIM_EVENT_7:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_7;
    }
    break;
  case HRTIM_EVENT_8:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_8;
    }
    break;
  case HRTIM_EVENT_9:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_9;
    }
    break;
  case HRTIM_EVENT_10:
    {
      CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_10;
    }
    break;
  }
  
  switch (CaptureUnit)
  {
  case HRTIM_CAPTUREUNIT_1:
    {
      hhrtim->TimerParam[TimerIdx].CaptureTrigger1 = CaptureTrigger;
    }
    break;
  case HRTIM_CAPTUREUNIT_2:
    {
      hhrtim->TimerParam[TimerIdx].CaptureTrigger2 = CaptureTrigger;
    }
    break;
  }
}

/**
  * @brief  Configures the output of a timing unit 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @param  Output: timing unit output identifier
  * @param  pOutputCfg: pointer to the output configuration data structure
  * @retval None
  */
static void  HRTIM_OutputConfig(HRTIM_HandleTypeDef * hhrtim,
                                uint32_t TimerIdx,
                                uint32_t Output,
                                HRTIM_OutputCfgTypeDef * pOutputCfg)
{
  uint32_t hrtim_outr;
  uint32_t hrtim_dtr;
  
  uint32_t shift = 0xFFFFFFFF;
  
  hrtim_outr = hhrtim->Instance->sTimerxRegs[TimerIdx].OUTxR;
  hrtim_dtr = hhrtim->Instance->sTimerxRegs[TimerIdx].DTxR;
  
  switch (Output)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      /* Set the output set/reset crossbar */
      hhrtim->Instance->sTimerxRegs[TimerIdx].SETx1R = pOutputCfg->SetSource;
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTx1R = pOutputCfg->ResetSource;
      
      shift = 0;
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      /* Set the output set/reset crossbar */
      hhrtim->Instance->sTimerxRegs[TimerIdx].SETx2R = pOutputCfg->SetSource;
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTx2R = pOutputCfg->ResetSource;

      shift = 16;
    }
    break;
  }
  
  /* Clear output config */
  hrtim_outr &= ~((HRTIM_OUTR_POL1 |
                   HRTIM_OUTR_IDLM1 |
                   HRTIM_OUTR_IDLES1|
                   HRTIM_OUTR_FAULT1|
                   HRTIM_OUTR_CHP1 |
                   HRTIM_OUTR_DIDL1)  << shift);
  
  /* Set the polarity */
  hrtim_outr |= (pOutputCfg->Polarity << shift);
  
  /* Set the IDLE mode */
  hrtim_outr |= (pOutputCfg->IdleMode << shift);
  
  /* Set the IDLE state */
  hrtim_outr |= (pOutputCfg->IdleLevel << shift);
  
  /* Set the FAULT state */
  hrtim_outr |= (pOutputCfg->FaultLevel << shift);
  
  /* Set the chopper mode */
  hrtim_outr |= (pOutputCfg->ChopperModeEnable << shift);

  /* Set the burst mode entry mode : deadtime insertion when entering the idle
     state during a burst mode operation is allowed only under the following
     conditions:
     - the outputs is active during the burst mode (IDLES=1)
     - positive deadtimes (SDTR/SDTF set to 0)
  */
  if ((pOutputCfg->IdleLevel == HRTIM_OUTPUTIDLELEVEL_ACTIVE) && 
      ((hrtim_dtr & HRTIM_DTR_SDTR) == RESET) &&
      ((hrtim_dtr & HRTIM_DTR_SDTF) == RESET))
  {
    hrtim_outr |= (pOutputCfg->BurstModeEntryDelayed << shift);
  }
  
  /* Update HRTIM register */
  hhrtim->Instance->sTimerxRegs[TimerIdx].OUTxR = hrtim_outr;
}

/**
  * @brief  Configures an external event channel 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  Event: Event channel identifier
  * @param  pEventCfg: pointer to the event channel configuration data structure
  * @retval None
  */
static void HRTIM_EventConfig(HRTIM_HandleTypeDef * hhrtim,
                              uint32_t Event,
                              HRTIM_EventCfgTypeDef *pEventCfg)
{
  uint32_t hrtim_eecr1;
  uint32_t hrtim_eecr2;
  uint32_t hrtim_eecr3;

  /* Configure external event channel */
  hrtim_eecr1 = hhrtim->Instance->sCommonRegs.EECR1;
  hrtim_eecr2 = hhrtim->Instance->sCommonRegs.EECR2;
  hrtim_eecr3 = hhrtim->Instance->sCommonRegs.EECR3;
  
  switch (Event)
  {
  case HRTIM_EVENT_1:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE1SRC | HRTIM_EECR1_EE1POL | HRTIM_EECR1_EE1SNS | HRTIM_EECR1_EE1FAST);
      hrtim_eecr1 |= pEventCfg->Source;
      hrtim_eecr1 |= (pEventCfg->Polarity & HRTIM_EECR1_EE1POL);
      hrtim_eecr1 |= pEventCfg->Sensitivity;
      /* Update the HRTIM registers (all bitfields but EE1FAST bit) */
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE1FAST bit) */
      hrtim_eecr1 |= pEventCfg->FastMode;
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
    }
    break;
  case HRTIM_EVENT_2:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE2SRC | HRTIM_EECR1_EE2POL | HRTIM_EECR1_EE2SNS | HRTIM_EECR1_EE2FAST);
      hrtim_eecr1 |= (pEventCfg->Source << 6);
      hrtim_eecr1 |= ((pEventCfg->Polarity << 6) & (HRTIM_EECR1_EE2POL));
      hrtim_eecr1 |= (pEventCfg->Sensitivity << 6);
      /* Update the HRTIM registers (all bitfields but EE2FAST bit) */
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE2FAST bit) */
      hrtim_eecr1 |= (pEventCfg->FastMode << 6);
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
    }
    break;
  case HRTIM_EVENT_3:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE3SRC | HRTIM_EECR1_EE3POL | HRTIM_EECR1_EE3SNS | HRTIM_EECR1_EE3FAST);
      hrtim_eecr1 |= (pEventCfg->Source << 12);
      hrtim_eecr1 |= ((pEventCfg->Polarity << 12) & (HRTIM_EECR1_EE3POL));
      hrtim_eecr1 |= (pEventCfg->Sensitivity << 12);
      /* Update the HRTIM registers (all bitfields but EE3FAST bit) */
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE3FAST bit) */
      hrtim_eecr1 |= (pEventCfg->FastMode << 12);
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
    }
    break;
  case HRTIM_EVENT_4:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE4SRC | HRTIM_EECR1_EE4POL | HRTIM_EECR1_EE4SNS | HRTIM_EECR1_EE4FAST);
      hrtim_eecr1 |= (pEventCfg->Source << 18);
      hrtim_eecr1 |= ((pEventCfg->Polarity << 18) & (HRTIM_EECR1_EE4POL));
      hrtim_eecr1 |= (pEventCfg->Sensitivity << 18);
      /* Update the HRTIM registers (all bitfields but EE4FAST bit) */
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE4FAST bit) */
      hrtim_eecr1 |= (pEventCfg->FastMode << 18);
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
    }
    break;
  case HRTIM_EVENT_5:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE5SRC | HRTIM_EECR1_EE5POL | HRTIM_EECR1_EE5SNS | HRTIM_EECR1_EE5FAST);
      hrtim_eecr1 |= (pEventCfg->Source << 24);
      hrtim_eecr1 |= ((pEventCfg->Polarity << 24) & (HRTIM_EECR1_EE5POL));
      hrtim_eecr1 |= (pEventCfg->Sensitivity << 24);
      /* Update the HRTIM registers (all bitfields but EE5FAST bit) */
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE5FAST bit) */
      hrtim_eecr1 |= (pEventCfg->FastMode << 24);
      hhrtim->Instance->sCommonRegs.EECR1 = hrtim_eecr1;
    }
    break;
  case HRTIM_EVENT_6:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE6SRC | HRTIM_EECR2_EE6POL | HRTIM_EECR2_EE6SNS);
      hrtim_eecr2 |= pEventCfg->Source;
      hrtim_eecr2 |= (pEventCfg->Polarity & HRTIM_EECR2_EE6POL);
      hrtim_eecr2 |= pEventCfg->Sensitivity;
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE6F);
      hrtim_eecr3 |= pEventCfg->Filter;
      /* Update the HRTIM registers */
      hhrtim->Instance->sCommonRegs.EECR2 = hrtim_eecr2;
      hhrtim->Instance->sCommonRegs.EECR3 = hrtim_eecr3;
    }
    break;
  case HRTIM_EVENT_7:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE7SRC | HRTIM_EECR2_EE7POL | HRTIM_EECR2_EE7SNS);
      hrtim_eecr2 |= (pEventCfg->Source << 6);
      hrtim_eecr2 |= ((pEventCfg->Polarity << 6) & (HRTIM_EECR2_EE7POL));
      hrtim_eecr2 |= (pEventCfg->Sensitivity << 6);
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE7F);
      hrtim_eecr3 |= (pEventCfg->Filter << 6);
      /* Update the HRTIM registers */
      hhrtim->Instance->sCommonRegs.EECR2 = hrtim_eecr2;
      hhrtim->Instance->sCommonRegs.EECR3 = hrtim_eecr3;
    }
    break;
  case HRTIM_EVENT_8:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE8SRC | HRTIM_EECR2_EE8POL | HRTIM_EECR2_EE8SNS);
      hrtim_eecr2 |= (pEventCfg->Source << 12);
      hrtim_eecr2 |= ((pEventCfg->Polarity << 12) & (HRTIM_EECR2_EE8POL));
      hrtim_eecr2 |= (pEventCfg->Sensitivity << 12);
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE8F);
      hrtim_eecr3 |= (pEventCfg->Filter << 12);
      /* Update the HRTIM registers */
      hhrtim->Instance->sCommonRegs.EECR2 = hrtim_eecr2;
      hhrtim->Instance->sCommonRegs.EECR3 = hrtim_eecr3;
    }
    break;
  case HRTIM_EVENT_9:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE9SRC | HRTIM_EECR2_EE9POL | HRTIM_EECR2_EE9SNS);
      hrtim_eecr2 |= (pEventCfg->Source << 18);
      hrtim_eecr2 |= ((pEventCfg->Polarity << 18) & (HRTIM_EECR2_EE9POL));
      hrtim_eecr2 |= (pEventCfg->Sensitivity << 18);
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE9F);
      hrtim_eecr3 |= (pEventCfg->Filter << 18);
      /* Update the HRTIM registers */
      hhrtim->Instance->sCommonRegs.EECR2 = hrtim_eecr2;
      hhrtim->Instance->sCommonRegs.EECR3 = hrtim_eecr3;
    }
    break;
  case HRTIM_EVENT_10:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE10SRC | HRTIM_EECR2_EE10POL | HRTIM_EECR2_EE10SNS);
      hrtim_eecr2 |= (pEventCfg->Source << 24);
      hrtim_eecr2 |= ((pEventCfg->Polarity << 24) & (HRTIM_EECR2_EE10POL));
      hrtim_eecr2 |= (pEventCfg->Sensitivity << 24);
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE10F);
      hrtim_eecr3 |= (pEventCfg->Filter << 24);
      /* Update the HRTIM registers */
      hhrtim->Instance->sCommonRegs.EECR2 = hrtim_eecr2;
      hhrtim->Instance->sCommonRegs.EECR3 = hrtim_eecr3;
    }
    break;
  default:
    break;
  }
}

/**
  * @brief  Configures the timer counter reset 
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @param  Event: Event channel identifier
  * @retval None
  */
static void HRTIM_TIM_ResetConfig(HRTIM_HandleTypeDef * hhrtim,
                                  uint32_t TimerIdx,
                                  uint32_t Event)
{
  switch (Event)
  {
  case HRTIM_EVENT_1:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_1;
    }
    break;
  case HRTIM_EVENT_2:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_2;
    }
    break;
  case HRTIM_EVENT_3:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_3;
    }
    break;
  case HRTIM_EVENT_4:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_4;
    }
    break;
  case HRTIM_EVENT_5:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_5;
    }
    break;
  case HRTIM_EVENT_6:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_6;
    }
    break;
  case HRTIM_EVENT_7:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_7;
    }
    break;
  case HRTIM_EVENT_8:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_8;
    }
    break;
  case HRTIM_EVENT_9:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_9;
    }
    break;
  case HRTIM_EVENT_10:
    {
      hhrtim->Instance->sTimerxRegs[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_10;
    }
    break;
  }
}

/**
  * @brief  Returns the interrupt to enable or disable according to the
  *         OC mode.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval Interrupt to enable or disable
  */
static uint32_t HRTIM_GetITFromOCMode(HRTIM_HandleTypeDef * hhrtim,
                                      uint32_t TimerIdx,
                                      uint32_t OCChannel)
{
  uint32_t hrtim_set;
  uint32_t hrtim_reset;
  uint32_t interrupt = 0;
  
  switch (OCChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      /* Retreives actual OC mode and set interrupt accordingly */
      hrtim_set = hhrtim->Instance->sTimerxRegs[TimerIdx].SETx1R;
      hrtim_reset = hhrtim->Instance->sTimerxRegs[TimerIdx].RSTx1R;
      
      if (((hrtim_set & HRTIM_OUTPUTSET_TIMCMP1) == HRTIM_OUTPUTSET_TIMCMP1) &&
          ((hrtim_reset & HRTIM_OUTPUTSET_TIMCMP1) == HRTIM_OUTPUTSET_TIMCMP1))
      {
        /* OC mode: HRTIM_BASICOCMODE_TOGGLE */
        interrupt = HRTIM_TIM_IT_CMP1;
      }
      else if (((hrtim_set & HRTIM_OUTPUTSET_TIMCMP1) == HRTIM_OUTPUTSET_TIMCMP1) &&
               (hrtim_reset  == 0))
      {
         /* OC mode: HRTIM_BASICOCMODE_ACTIVE */
        interrupt = HRTIM_TIM_IT_SET1;
      }
      else if ((hrtim_set == 0) &&
               ((hrtim_reset & HRTIM_OUTPUTSET_TIMCMP1) == HRTIM_OUTPUTSET_TIMCMP1))
      {
         /* OC mode: HRTIM_BASICOCMODE_INACTIVE */
        interrupt = HRTIM_TIM_IT_RST1;
      }
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      /* Retreives actual OC mode and set interrupt accordingly */
      hrtim_set = hhrtim->Instance->sTimerxRegs[TimerIdx].SETx2R;
      hrtim_reset = hhrtim->Instance->sTimerxRegs[TimerIdx].RSTx2R;
      
      if (((hrtim_set & HRTIM_OUTPUTSET_TIMCMP2) == HRTIM_OUTPUTSET_TIMCMP2) &&
          ((hrtim_reset & HRTIM_OUTPUTSET_TIMCMP2) == HRTIM_OUTPUTSET_TIMCMP2))
      {
        /* OC mode: HRTIM_BASICOCMODE_TOGGLE */
        interrupt = HRTIM_TIM_IT_CMP2;
      }
      else if (((hrtim_set & HRTIM_OUTPUTSET_TIMCMP2) == HRTIM_OUTPUTSET_TIMCMP2) &&
               (hrtim_reset  == 0))
      {
         /* OC mode: HRTIM_BASICOCMODE_ACTIVE */
        interrupt = HRTIM_TIM_IT_SET2;
      }
      else if ((hrtim_set == 0) &&
               ((hrtim_reset & HRTIM_OUTPUTSET_TIMCMP2) == HRTIM_OUTPUTSET_TIMCMP2))
      {
         /* OC mode: HRTIM_BASICOCMODE_INACTIVE */
        interrupt = HRTIM_TIM_IT_RST2;
      }
    }
    break;
  }
  
  return interrupt;
}

/**
  * @brief  Returns the DMA request to enable or disable according to the
  *         OC mode.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Ouput 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Ouput 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Ouput 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Ouput 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Ouput 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Ouput 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Ouput 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Ouput 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Ouput 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Ouput 2
  * @retval DMA request to enable or disable
  */
static uint32_t HRTIM_GetDMAFromOCMode(HRTIM_HandleTypeDef * hhrtim,
                                       uint32_t TimerIdx,
                                       uint32_t OCChannel)
{
  uint32_t hrtim_set;
  uint32_t hrtim_reset;
  uint32_t dma_request = 0;
  
  switch (OCChannel)
  {
  case HRTIM_OUTPUT_TA1:
  case HRTIM_OUTPUT_TB1:
  case HRTIM_OUTPUT_TC1:
  case HRTIM_OUTPUT_TD1:
  case HRTIM_OUTPUT_TE1:
    {
      /* Retreives actual OC mode and set dma_request accordingly */
      hrtim_set = hhrtim->Instance->sTimerxRegs[TimerIdx].SETx1R;
      hrtim_reset = hhrtim->Instance->sTimerxRegs[TimerIdx].RSTx1R;
      
      if (((hrtim_set & HRTIM_OUTPUTSET_TIMCMP1) == HRTIM_OUTPUTSET_TIMCMP1) &&
          ((hrtim_reset & HRTIM_OUTPUTSET_TIMCMP1) == HRTIM_OUTPUTSET_TIMCMP1))
      {
        /* OC mode: HRTIM_BASICOCMODE_TOGGLE */
        dma_request = HRTIM_TIM_DMA_CMP1;
      }
      else if (((hrtim_set & HRTIM_OUTPUTSET_TIMCMP1) == HRTIM_OUTPUTSET_TIMCMP1) &&
               (hrtim_reset  == 0))
      {
         /* OC mode: HRTIM_BASICOCMODE_ACTIVE */
        dma_request = HRTIM_TIM_DMA_SET1;
      }
      else if ((hrtim_set == 0) &&
               ((hrtim_reset & HRTIM_OUTPUTSET_TIMCMP1) == HRTIM_OUTPUTSET_TIMCMP1))
      {
         /* OC mode: HRTIM_BASICOCMODE_INACTIVE */
        dma_request = HRTIM_TIM_DMA_RST1;
      }
    }
    break;
  case HRTIM_OUTPUT_TA2:
  case HRTIM_OUTPUT_TB2:
  case HRTIM_OUTPUT_TC2:
  case HRTIM_OUTPUT_TD2:
  case HRTIM_OUTPUT_TE2:
    {
      /* Retreives actual OC mode and set dma_request accordingly */
      hrtim_set = hhrtim->Instance->sTimerxRegs[TimerIdx].SETx2R;
      hrtim_reset = hhrtim->Instance->sTimerxRegs[TimerIdx].RSTx2R;
      
      if (((hrtim_set & HRTIM_OUTPUTSET_TIMCMP2) == HRTIM_OUTPUTSET_TIMCMP2) &&
          ((hrtim_reset & HRTIM_OUTPUTSET_TIMCMP2) == HRTIM_OUTPUTSET_TIMCMP2))
      {
        /* OC mode: HRTIM_BASICOCMODE_TOGGLE */
        dma_request = HRTIM_TIM_DMA_CMP2;
      }
      else if (((hrtim_set & HRTIM_OUTPUTSET_TIMCMP2) == HRTIM_OUTPUTSET_TIMCMP2) &&
               (hrtim_reset  == 0))
      {
         /* OC mode: HRTIM_BASICOCMODE_ACTIVE */
        dma_request = HRTIM_TIM_DMA_SET2;
      }
      else if ((hrtim_set == 0) &&
               ((hrtim_reset & HRTIM_OUTPUTSET_TIMCMP2) == HRTIM_OUTPUTSET_TIMCMP2))
      {
         /* OC mode: HRTIM_BASICOCMODE_INACTIVE */
        dma_request = HRTIM_TIM_DMA_RST2;
      }
    }
    break;
  }
  
  return dma_request;
}

static DMA_HandleTypeDef * HRTIM_GetDMAHandleFromTimerIdx(HRTIM_HandleTypeDef * hhrtim,
                                                          uint32_t TimerIdx)
{
  DMA_HandleTypeDef * hdma = (DMA_HandleTypeDef *)HAL_NULL;
  
  switch (TimerIdx)
  {
  case HRTIM_TIMERINDEX_MASTER:
    {
      hdma = hhrtim->hdmaMaster;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_A:
    {
      hdma = hhrtim->hdmaTimerA;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_B:
    {
      hdma = hhrtim->hdmaTimerB;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_C:
    {
      hdma = hhrtim->hdmaTimerC;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_D:
    {
      hdma = hhrtim->hdmaTimerD;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_E:
    {
      hdma = hhrtim->hdmaTimerE;
    }
    break;
  }
  
  return hdma;
}

static uint32_t GetTimerIdxFromDMAHandle(DMA_HandleTypeDef *hdma)
{
  uint32_t timed_idx = 0xFFFFFFFF;
  
  if (hdma->Instance ==  DMA1_Channel2)
  {
    timed_idx = HRTIM_TIMERINDEX_MASTER;
  }
  else if (hdma->Instance ==  DMA1_Channel3)
  {
    timed_idx = HRTIM_TIMERINDEX_TIMER_A;
  }
  else if (hdma->Instance ==  DMA1_Channel4)
  {
    timed_idx = HRTIM_TIMERINDEX_TIMER_B;
  }
  else if (hdma->Instance ==  DMA1_Channel5)
  {
    timed_idx = HRTIM_TIMERINDEX_TIMER_C;
  }
  else if (hdma->Instance ==  DMA1_Channel6)
  {
    timed_idx = HRTIM_TIMERINDEX_TIMER_D;
  }
  else if (hdma->Instance ==  DMA1_Channel7)
  {
    timed_idx = HRTIM_TIMERINDEX_TIMER_E;
  }
  
  return timed_idx;
}

/**
  * @brief  Forces an immediate transfer from the preload to the active 
  *         registers.
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  * @retval None
  */
static void HRTIM_ForceRegistersUpdate(HRTIM_HandleTypeDef * hhrtim,
                                       uint32_t TimerIdx)
{
  switch (TimerIdx)
  {
  case HRTIM_TIMERINDEX_MASTER:
    {
      hhrtim->Instance->sCommonRegs.CR2 |= HRTIM_CR2_MSWU;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_A:
    {
      hhrtim->Instance->sCommonRegs.CR2 |= HRTIM_CR2_TASWU;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_B:
    {
      hhrtim->Instance->sCommonRegs.CR2 |= HRTIM_CR2_TBSWU;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_C:
    {
      hhrtim->Instance->sCommonRegs.CR2 |= HRTIM_CR2_TCSWU;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_D:
    {
      hhrtim->Instance->sCommonRegs.CR2 |= HRTIM_CR2_TDSWU;
    }
    break;
  case HRTIM_TIMERINDEX_TIMER_E:
    {
      hhrtim->Instance->sCommonRegs.CR2 |= HRTIM_CR2_TESWU;
    }
    break;
  }
}


/**
  * @brief  HRTIM interrupts service routine
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @retval None
  */
static void HRTIM_HRTIM_ISR(HRTIM_HandleTypeDef * hhrtim)
{
  /* Fault 1 event */
  if(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_FLAG_FLT1) != RESET)
  {
    if(__HAL_HRTIM_GET_ITSTATUS(hhrtim, HRTIM_IT_FLT1) != RESET)
    {
      __HAL_HRTIM_CLEAR_IT(hhrtim, HRTIM_IT_FLT1);
      
      /* Invoke Fault 1 event callback */
      HAL_HRTIM_Fault1Callback(hhrtim);  
    }
  }
  
  /* Fault 2 event */
  if(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_FLAG_FLT2) != RESET)
  {
    if(__HAL_HRTIM_GET_ITSTATUS(hhrtim, HRTIM_IT_FLT2) != RESET)
    {
      __HAL_HRTIM_CLEAR_IT(hhrtim, HRTIM_IT_FLT2);
      
      /* Invoke Fault 2 event callback */
      HAL_HRTIM_Fault2Callback(hhrtim);  
    }
  }
  
  /* Fault 3 event */
  if(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_FLAG_FLT3) != RESET)
  {
    if(__HAL_HRTIM_GET_ITSTATUS(hhrtim, HRTIM_IT_FLT3) != RESET)
    {
      __HAL_HRTIM_CLEAR_IT(hhrtim, HRTIM_IT_FLT3);
      
      /* Invoke Fault 3 event callback */
      HAL_HRTIM_Fault3Callback(hhrtim);  
    }
  }
  
  /* Fault 4 event */
  if(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_FLAG_FLT4) != RESET)
  {
    if(__HAL_HRTIM_GET_ITSTATUS(hhrtim, HRTIM_IT_FLT4) != RESET)
    {
      __HAL_HRTIM_CLEAR_IT(hhrtim, HRTIM_IT_FLT4);
      
      /* Invoke Fault 4 event callback */
      HAL_HRTIM_Fault4Callback(hhrtim);  
    }
  }
  
  /* Fault 5 event */
  if(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_FLAG_FLT5) != RESET)
  {
    if(__HAL_HRTIM_GET_ITSTATUS(hhrtim, HRTIM_IT_FLT5) != RESET)
    {
      __HAL_HRTIM_CLEAR_IT(hhrtim, HRTIM_IT_FLT5);
      
      /* Invoke Fault 5 event callback */
      HAL_HRTIM_Fault5Callback(hhrtim);  
    }
  }
  
  /* System fault event */
  if(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_FLAG_SYSFLT) != RESET)
  {
    if(__HAL_HRTIM_GET_ITSTATUS(hhrtim, HRTIM_IT_SYSFLT) != RESET)
    {
      __HAL_HRTIM_CLEAR_IT(hhrtim, HRTIM_IT_SYSFLT);
      
      /* Invoke System fault event callback */
      HAL_HRTIM_SystemFaultCallback(hhrtim);  
    }
  }
}

/**
* @brief  Master timer interrupts service routine
* @param  hhrtim: pointer to HAL HRTIM handle
* @retval None
*/
static void HRTIM_Master_ISR(HRTIM_HandleTypeDef * hhrtim)
{
  /* DLL calibration ready event */
  if(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_FLAG_DLLRDY) != RESET)
  {
    if(__HAL_HRTIM_GET_ITSTATUS(hhrtim, HRTIM_IT_DLLRDY) != RESET)
    {
      __HAL_HRTIM_CLEAR_IT(hhrtim, HRTIM_IT_DLLRDY);
      
      /* Set HRTIM State */  
      hhrtim->State = HAL_HRTIM_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hhrtim); 
      
      /* Invoke System fault event callback */
      HAL_HRTIM_DLLCalbrationReadyCallback(hhrtim);  
    }
  }
  
  /* Burst mode period event */
  if(__HAL_HRTIM_GET_FLAG(hhrtim, HRTIM_FLAG_BMPER) != RESET)
  {
    if(__HAL_HRTIM_GET_ITSTATUS(hhrtim, HRTIM_IT_BMPER) != RESET)
    {
      __HAL_HRTIM_CLEAR_IT(hhrtim, HRTIM_IT_BMPER);
      
      /* Invoke Burst mode period event callback */
      HAL_HRTIM_BurstModePeriodCallback(hhrtim);  
    }
  }  
  
  /* Master timer compare 1 event */
  if(__HAL_HRTIM_MASTER_GET_FLAG(hhrtim, HRTIM_MASTER_FLAG_MCMP1) != RESET)
  {
    if(__HAL_HRTIM_MASTER_GET_ITSTATUS(hhrtim, HRTIM_MASTER_IT_MCMP1) != RESET)
    {
      __HAL_HRTIM_MASTER_CLEAR_IT(hhrtim, HRTIM_MASTER_IT_MCMP1);
      
      /* Invoke compare 1 event callback */
      HAL_HRTIM_Compare1EventCallback(hhrtim, HRTIM_TIMERINDEX_MASTER);  
    }
  }
  
  /* Master timer compare 2 event */
  if(__HAL_HRTIM_MASTER_GET_FLAG(hhrtim, HRTIM_MASTER_FLAG_MCMP2) != RESET)
  {
    if(__HAL_HRTIM_MASTER_GET_ITSTATUS(hhrtim, HRTIM_MASTER_IT_MCMP2) != RESET)
    {
      __HAL_HRTIM_MASTER_CLEAR_IT(hhrtim, HRTIM_MASTER_IT_MCMP2);
      
      /* Invoke compare 2 event callback */
      HAL_HRTIM_Compare2EventCallback(hhrtim, HRTIM_TIMERINDEX_MASTER);  
    }
  }
  
  /* Master timer compare 3 event */
  if(__HAL_HRTIM_MASTER_GET_FLAG(hhrtim, HRTIM_MASTER_FLAG_MCMP3) != RESET)
  {
    if(__HAL_HRTIM_MASTER_GET_ITSTATUS(hhrtim, HRTIM_MASTER_IT_MCMP3) != RESET)
    {
      __HAL_HRTIM_MASTER_CLEAR_IT(hhrtim, HRTIM_MASTER_IT_MCMP3);
      
      /* Invoke compare 3 event callback */
      HAL_HRTIM_Compare3EventCallback(hhrtim, HRTIM_TIMERINDEX_MASTER);  
    }
  }
  
  /* Master timer compare 4 event */
  if(__HAL_HRTIM_MASTER_GET_FLAG(hhrtim, HRTIM_MASTER_FLAG_MCMP4) != RESET)
  {
    if(__HAL_HRTIM_MASTER_GET_ITSTATUS(hhrtim, HRTIM_MASTER_IT_MCMP4) != RESET)
    {
      __HAL_HRTIM_MASTER_CLEAR_IT(hhrtim, HRTIM_MASTER_IT_MCMP4);
      
      /* Invoke compare 4 event callback */
      HAL_HRTIM_Compare4EventCallback(hhrtim, HRTIM_TIMERINDEX_MASTER);  
    }
  }
  
  /* Master timer repetition event */
  if(__HAL_HRTIM_MASTER_GET_FLAG(hhrtim, HRTIM_MASTER_FLAG_MREP) != RESET)
  {
    if(__HAL_HRTIM_MASTER_GET_ITSTATUS(hhrtim, HRTIM_MASTER_IT_MREP) != RESET)
    {
      __HAL_HRTIM_MASTER_CLEAR_IT(hhrtim, HRTIM_MASTER_IT_MREP);
      
      /* Invoke repetition event callback */
      HAL_HRTIM_RepetitionEventCallback(hhrtim, HRTIM_TIMERINDEX_MASTER);  
    }
  }
  
  /* Synchronization input event */
  if(__HAL_HRTIM_MASTER_GET_FLAG(hhrtim, HRTIM_MASTER_FLAG_SYNC) != RESET)
  {
    if(__HAL_HRTIM_MASTER_GET_ITSTATUS(hhrtim, HRTIM_MASTER_IT_SYNC) != RESET)
    {
      __HAL_HRTIM_MASTER_CLEAR_IT(hhrtim, HRTIM_MASTER_IT_SYNC);
      
      /* Invoke synchronization event callback */
      HAL_HRTIM_SynchronizationEventCallback(hhrtim);  
    }
  }
  
  /* Master timer registers update event */
  if(__HAL_HRTIM_MASTER_GET_FLAG(hhrtim, HRTIM_MASTER_FLAG_MUPD) != RESET)
  {
    if(__HAL_HRTIM_MASTER_GET_ITSTATUS(hhrtim, HRTIM_MASTER_IT_MUPD) != RESET)
    {
      __HAL_HRTIM_MASTER_CLEAR_IT(hhrtim, HRTIM_MASTER_IT_MUPD);
      
      /* Invoke registers update event callback */
      HAL_HRTIM_RegistersUpdateCallback(hhrtim, HRTIM_TIMERINDEX_MASTER);  
    }
  }
}

/**
  * @brief  Timer interrupts service routine
  * @param  hhrtim: pointer to HAL HRTIM handle
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_TIMERINDEX_TIMER_A for timer A
  *                   @arg HRTIM_TIMERINDEX_TIMER_B for timer B
  *                   @arg HRTIM_TIMERINDEX_TIMER_C for timer C
  *                   @arg HRTIM_TIMERINDEX_TIMER_D for timer D
  *                   @arg HRTIM_TIMERINDEX_TIMER_E for timer E
  * @retval None
*/
static void HRTIM_Timer_ISR(HRTIM_HandleTypeDef * hhrtim,
                     uint32_t TimerIdx)
{
  /* Timer compare 1 event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_CMP1) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP1) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP1);
      
      /* Invoke compare 1 event callback */
      HAL_HRTIM_Compare1EventCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer compare 2 event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_CMP2) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP2) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP2);
      
      /* Invoke compare 2 event callback */
      HAL_HRTIM_Compare2EventCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer compare 3 event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_CMP3) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP3) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP3);
      
      /* Invoke compare 3 event callback */
      HAL_HRTIM_Compare3EventCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer compare 4 event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_CMP4) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP4) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CMP4);
      
      /* Invoke compare 4 event callback */
      HAL_HRTIM_Compare4EventCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer repetition event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_REP) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_REP) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_REP);
      
      /* Invoke repetition event callback */
      HAL_HRTIM_RepetitionEventCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer registers update event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_UPD) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_UPD) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_UPD);
      
      /* Invoke registers update event callback */
      HAL_HRTIM_RegistersUpdateCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer capture 1 event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_CPT1) != RESET)
  {    
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_CPT1) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CPT1);
      
      /* Invoke capture 1 event callback */
      HAL_HRTIM_Capture1EventCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer capture 2 event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_CPT2) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_CPT2) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_CPT2);
      
      /* Invoke capture 2 event callback */
      HAL_HRTIM_Capture2EventCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer ouput 1 set event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_SET1) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_SET1) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_SET1);
      
      /* Invoke ouput 1 set event callback */
      HAL_HRTIM_Output1SetCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer ouput 1 reset event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_RST1) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_RST1) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_RST1);
      
      /* Invoke ouput 1 reset event callback */
      HAL_HRTIM_Output1ResetCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer ouput 2 set event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_SET2) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_SET2) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_SET2);
      
      /* Invoke ouput 2 set event callback */
      HAL_HRTIM_Output2SetCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer ouput 2 reset event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_RST2) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_RST2) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_RST2);
      
      /* Invoke ouput 2 reset event callback */
      HAL_HRTIM_Output2ResetCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Timer reset event */
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_RST) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_RST) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_RST);
      
      /* Invoke timer reset callback */
      HAL_HRTIM_CounterResetCallback(hhrtim, TimerIdx);  
    }
  }
  
  /* Delayed protection event */  
  if(__HAL_HRTIM_TIMER_GET_FLAG(hhrtim, TimerIdx, HRTIM_TIM_FLAG_DLYPRT) != RESET)
  {
    if(__HAL_HRTIM_TIMER_GET_ITSTATUS(hhrtim, TimerIdx, HRTIM_TIM_IT_DLYPRT) != RESET)
    {
      __HAL_HRTIM_TIMER_CLEAR_IT(hhrtim, TimerIdx, HRTIM_TIM_IT_DLYPRT);
      
      /* Invoke delayed protection callback */
      HAL_HRTIM_DelayedProtectionCallback(hhrtim, TimerIdx);  
    }
  }
}

/**
  * @brief  DMA callback invoked upon master timer related DMA request completion
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void HRTIM_DMAMasterCplt(DMA_HandleTypeDef *hdma)
{
  HRTIM_HandleTypeDef * hrtim = (HRTIM_HandleTypeDef *)((DMA_HandleTypeDef* )hdma)->Parent;
  
  if ((hrtim->Instance->sMasterRegs.MDIER & HRTIM_MASTER_DMA_MCMP1) != RESET)
  {
    HAL_HRTIM_Compare1EventCallback(hrtim, HRTIM_TIMERINDEX_MASTER);
  }
  else if ((hrtim->Instance->sMasterRegs.MDIER & HRTIM_MASTER_DMA_MCMP2) != RESET)
  {
    HAL_HRTIM_Compare2EventCallback(hrtim, HRTIM_TIMERINDEX_MASTER);
  }
  else if ((hrtim->Instance->sMasterRegs.MDIER & HRTIM_MASTER_DMA_MCMP3) != RESET)
  {
    HAL_HRTIM_Compare3EventCallback(hrtim, HRTIM_TIMERINDEX_MASTER);
  }
  else if ((hrtim->Instance->sMasterRegs.MDIER & HRTIM_MASTER_DMA_MCMP4) != RESET)
  {
    HAL_HRTIM_Compare4EventCallback(hrtim, HRTIM_TIMERINDEX_MASTER);
  }
  else if ((hrtim->Instance->sMasterRegs.MDIER & HRTIM_MASTER_DMA_MREP) != RESET)
  {
    HAL_HRTIM_RepetitionEventCallback(hrtim, HRTIM_TIMERINDEX_MASTER);
  }
  else if ((hrtim->Instance->sMasterRegs.MDIER & HRTIM_MASTER_DMA_SYNC) != RESET)
  {
    HAL_HRTIM_SynchronizationEventCallback(hrtim);
  }
  else if ((hrtim->Instance->sMasterRegs.MDIER & HRTIM_MASTER_DMA_MUPD) != RESET)
  {
    HAL_HRTIM_RegistersUpdateCallback(hrtim, HRTIM_TIMERINDEX_MASTER);
  }
}

/**
  * @brief  DMA callback invoked upon timer A..E related DMA request completion
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void HRTIM_DMATimerxCplt(DMA_HandleTypeDef *hdma)
{
  uint8_t timer_idx;
  
  HRTIM_HandleTypeDef * hrtim = (HRTIM_HandleTypeDef *)((DMA_HandleTypeDef* )hdma)->Parent;
  
  timer_idx = GetTimerIdxFromDMAHandle(hdma);
  
  if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_CMP1) != RESET)
  {
    HAL_HRTIM_Compare1EventCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_CMP2) != RESET)
  {
    HAL_HRTIM_Compare2EventCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_CMP3) != RESET)
  {
    HAL_HRTIM_Compare3EventCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_CMP4) != RESET)
  {
    HAL_HRTIM_Compare4EventCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_REP) != RESET)
  {
    HAL_HRTIM_RepetitionEventCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_UPD) != RESET)
  {
    HAL_HRTIM_RegistersUpdateCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_CPT1) != RESET)
  {
    HAL_HRTIM_Capture1EventCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_CPT2) != RESET)
  {
    HAL_HRTIM_Capture2EventCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_SET1) != RESET)
  {
    HAL_HRTIM_Output1SetCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_RST1) != RESET)
  {
    HAL_HRTIM_Output1ResetCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_SET2) != RESET)
  {
    HAL_HRTIM_Output2SetCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_RST2) != RESET)
  {
    HAL_HRTIM_Output2ResetCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_RST) != RESET)
  {
    HAL_HRTIM_CounterResetCallback(hrtim, timer_idx);
  }
  else if ((hrtim->Instance->sTimerxRegs[timer_idx].TIMxDIER & HRTIM_TIM_DMA_DLYPRT) != RESET)
  {
    HAL_HRTIM_DelayedProtectionCallback(hrtim, timer_idx);
  }
}

/**
* @brief  DMA error callback 
* @param  hdma: pointer to DMA handle.
* @retval None
*/
static void HRTIM_DMAError(DMA_HandleTypeDef *hdma)
{
  HRTIM_HandleTypeDef * hrtim = (HRTIM_HandleTypeDef *)((DMA_HandleTypeDef* )hdma)->Parent;
  
  HAL_HRTIM_ErrorCallback(hrtim);
}

/**
  * @brief  DMA callback invoked upon burst DMA transfer completion
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void HRTIM_BurstDMACplt(DMA_HandleTypeDef *hdma)
{
  HRTIM_HandleTypeDef * hrtim = (HRTIM_HandleTypeDef *)((DMA_HandleTypeDef* )hdma)->Parent;
  
  HAL_HRTIM_BurstDMATransferCallback(hrtim, GetTimerIdxFromDMAHandle(hdma));
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* STM32F334x8 */

#endif /* HAL_HRTIM_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



