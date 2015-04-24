/**
  ******************************************************************************
  * @file    stm32f30x_hrtim.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   HRTIMx module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the HRTIMx peripheral:
  *           + Initialization/de-initialization methods
  *           + I/O operation methods
  *           + Peripheral Control methods 
  *         
  @verbatim
================================================================================
                    ##### <HRTIM specific features> #####
================================================================================
           
  [..] < HRTIM introduction: 
       (#) The high-resolution timer can generate up to 10 digital signals with
           highly accurate timings.
           It is primarily intended to drive power conversion systems such as 
           switch mode power supplies or lighting systems, 
           but can be of general purpose usage, whenever a very fine timing 
           resolution is expected.

       (#) Its modular architecture allows to generate either independent or 
           coupled waveforms. 
           The wave-shape is defined by self-contained timings 
           (using counters and compare units) and a broad range of external events,
           such as analog or digital feedbacks and synchronisation signals. 
           This allows to produce a large variety of control signal (PWM, phase-shifted,
           constant Ton,...) and address most of conversion topologies.

       (#) For control and monitoring purposes, the timer has also timing measure 
           capabilities and links to built-in ADC and DAC converters. 
           Last, it features light-load management mode and is able to handle 
           various fault schemes for safe shut-down purposes.
                 
   
            ##### How to use this driver #####
================================================================================
        [..] This driver provides functions to configure and program the HRTIM 
        of all stm32f33x devices.
        These functions are split in 9 groups: 
     
        (#) HRTIM Simple TimeBase management: this group includes all needed functions 
            to configure the HRTIM Timebase unit:
                 (++) Initializes the HRTIMx timer in simple time base mode 
                 (++) Start/Stop the time base generation
                 (++) Deinitialize the HRTIM peripheral  
    
                   
       (#) HRTIM simple Output Compare management: this group includes all needed 
           functions to configure the Compare unit used in Output compare mode: 
                 (++) Initializes the HRTIMx timer time base unit 
                 (++) Configure the compare unit in in simple Output Compare mode
                 (++) Start/Stop the Output compare generation    
                    
       (#) HRTIM simple PWM management: this group includes all needed 
           functions to configure the Compare unit used in PWM mode: 
                 (++) Initializes the HRTIMx timer time base unit 
                 (++) Configure the compare unit in in simple PWM mode
                 (++) Start/Stop the PWM generation      
                     
       (#) HRTIM simple Capture management: this group includes all needed 
           functions to configure the Capture unit used in Capture mode: 
                 (++) Initializes the HRTIMx timer time base unit 
                 (++) Configure the compare unit in in simple Capture mode
                 (++) Start/Stop the Capture mode

       (#) HRTIM simple One Pulse management: this group includes all needed 
           functions to configure the Capture unit and Compare unit used in One Pulse mode: 
                 (++) Initializes the HRTIMx timer time base unit 
                 (++) Configure the compare unit and the capture unit in in simple One Pulse mode
                 (++) Start/Stop the One Pulse mode generation 
                   
       (#) HRTIM Waveform management: this group includes all needed 
           functions to configure the HRTIM possible waveform mode: 
                 (++) Initializes the HRTIMx timer Master time base unit 
                 (++) Initializes the HRTIMx timer Slaves time base unit
                 (++) Configures the HRTIMx timer Compare unit  
                 (++) Configures the HRTIMx Slave timer Capture unit 
                 (++) Configures the HRTIMx timer Output unit 
                 (++) Configures the HRTIMx timer DeadTime / Chopper / Burst features 
                 (++) Configures the HRTIMx timer Fault / External event features 
                 (++) Configures the HRTIMx timer Synchronization features: Internal/External connection, DACs,... 
                 (++) Configures the HRTIMx timer Synchronization features: ADCs Triggers  
                 (++) HRTIMx timer Outputs Start/Stop  
                 (++) Start/Stop the HRTIMx Timer counters            
                               
        (#) HRTIM interrupts, DMA and flags management
                 (++) Enable/Disable interrupt sources
                 (++) Get flags status
                 (++) Clear flags/ Pending bits
                 (++) Enable/Disable DMA requests 
                 (++) Configure DMA burst mode
       
        (#) TIM specific interface management, this group includes all 
            needed functions to use the specific TIM interface:
                 (++) HRTIMx timer DLL calibration      
  
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
#include "stm32f30x_hrtim.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup HRTIM 
  * @brief HRTIM driver module
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
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

#define HRTIM_TIM_OFFSET      (uint32_t)0x00000080
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t TimerIdxToTimerId[] = 
{
  HRTIM_TIMERID_TIMER_A,
  HRTIM_TIMERID_TIMER_B,
  HRTIM_TIMERID_TIMER_C,
  HRTIM_TIMERID_TIMER_D,
  HRTIM_TIMERID_TIMER_E,
  HRTIM_TIMERID_MASTER,
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void HRTIM_MasterBase_Config(HRTIM_TypeDef* HRTIMx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruc);
static void HRTIM_TimingUnitBase_Config(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct);
static void HRTIM_MasterWaveform_Config(HRTIM_TypeDef * HRTIMx, HRTIM_TimerInitTypeDef * TimerInit);
static void HRTIM_TimingUnitWaveform_Config(HRTIM_TypeDef * HRTIMx, 
                                            uint32_t TimerIdx, 
                                            HRTIM_TimerInitTypeDef * TimerInit);
static void HRTIM_CompareUnitConfig(HRTIM_TypeDef * HRTIMx,
                                    uint32_t TimerIdx,
                                    uint32_t CompareUnit,
                                    HRTIM_CompareCfgTypeDef * CompareCfg);
static void HRTIM_CaptureUnitConfig(HRTIM_TypeDef * HRTIMx,
                                    uint32_t TimerIdx,
                                    uint32_t CaptureUnit,
                                    uint32_t Event);
static void HRTIM_OutputConfig(HRTIM_TypeDef * HRTIMx,
                                uint32_t TimerIdx,
                                uint32_t Output,
                                HRTIM_OutputCfgTypeDef * OutputCfg);
static void HRTIM_ExternalEventConfig(HRTIM_TypeDef * HRTIMx,
                                      uint32_t Event,
                                      HRTIM_EventCfgTypeDef * EventCfg);
static void HRTIM_TIM_ResetConfig(HRTIM_TypeDef * HRTIMx,
                                  uint32_t TimerIdx,
                                  uint32_t Event);  
  /** @defgroup HRTIM_Private_Functions
  * @{
  */

/** @defgroup HRTIM_Group1 Initialization/de-initialization methods 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization/de-initialization methods #####
 ===============================================================================
    [..]  This section provides functions allowing to:
          (+)Initializes timer in basic time base mode
          (+)Initializes timer in basic OC mode
          (+)Initializes timer in basic PWM mode
          (+)Initializes timer in basic Capture mode
          (+)Initializes timer in One Pulse mode
          (+)Initializes a timer operating in waveform mode
          (+)De-initializes the HRTIMx timer
 
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the HRTIMx timer in basic time base mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 for master timer
  *                   @arg 0x1 to 0x5 for timers A to E
  * @note   The time-base unit initialization parameters specify:
  *           The timer counter operating mode (continuous, one shot)
  *           The timer clock prescaler
  *           The timer period 
  *           The timer repetition counter.
  * @retval None
  */
void HRTIM_SimpleBase_Init(HRTIM_TypeDef* HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct)
{
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  assert_param(IS_HRTIM_MODE(HRTIM_BaseInitStruct->Mode));
   
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    /* Configure master timer */
    HRTIM_MasterBase_Config(HRTIMx, HRTIM_BaseInitStruct);
  }
  else
  {
    /* Configure timing unit */
    HRTIM_TimingUnitBase_Config(HRTIMx, TimerIdx, HRTIM_BaseInitStruct);
  }
}

/**
  * @brief  De-initializes a timer operating in all mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral 
  * @retval None
  */
void HRTIM_DeInit(HRTIM_TypeDef* HRTIMx)
{
  /* Check the parameters */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_HRTIM1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_HRTIM1, DISABLE);  
 }

/**
  * @brief  Initializes the HRTIMx timer in basic output compare mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x1 to 0x5 for timers A to E
  * @note   Initializes the time-base unit of the timer and prepare it to
  *         operate in output compare mode
  * @retval None
  */
void HRTIM_SimpleOC_Init(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct)
{
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  assert_param(IS_HRTIM_MODE(HRTIM_BaseInitStruct->Mode));
   
  /* Configure timing unit */
  HRTIM_TimingUnitBase_Config(HRTIMx, TimerIdx, HRTIM_BaseInitStruct);
}

/**
  * @brief  Initializes the HRTIMx timer in basic PWM mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x1 to 0x5 for timers A to E
  * @note   Initializes the time-base unit of the timer and prepare it to
  *         operate in capture mode
  * @retval None
  */
void HRTIM_SimplePWM_Init(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct)
{
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  assert_param(IS_HRTIM_MODE(HRTIM_BaseInitStruct->Mode));
  
  /* Configure timing unit */
  HRTIM_TimingUnitBase_Config(HRTIMx, TimerIdx, HRTIM_BaseInitStruct);
}

/**
  * @brief  Initializes a timer operating in basic capture mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x1 to 0x5 for timers A to E 
  * @retval None
  */
void HRTIM_SimpleCapture_Init(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct)
{
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  assert_param(IS_HRTIM_MODE(HRTIM_BaseInitStruct->Mode));
  
  /* Configure timing unit */
  HRTIM_TimingUnitBase_Config(HRTIMx, TimerIdx, HRTIM_BaseInitStruct);
}

/**
  * @brief  Initializes the HRTIMx timer in basic one pulse mode 
  * @param  HRTIMx: pointer to  HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x1 to 0x5 for timers A to E
  * @note   Initializes the time-base unit of the timer and prepare it to
  *         operate in one pulse mode. In this mode the counter operates
  *         in single shot mode (retriggerable or not)
  * @retval None
  */
void HRTIM_SimpleOnePulse_Init(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct)
{
  /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  assert_param(IS_HRTIM_MODE(HRTIM_BaseInitStruct->Mode));
  
  /* Configure timing unit */
  HRTIM_TimingUnitBase_Config(HRTIMx, TimerIdx, HRTIM_BaseInitStruct);
}

/**
  * @brief  Initializes a timer operating in waveform mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 for master timer
  *                   @arg 0x1 to 0x5 for timers A to E 
  * @param  pTimerInit: pointer to the timer initialization data structure
  * @retval None
  */
void HRTIM_Waveform_Init(HRTIM_TypeDef * HRTIMx,
                                         uint32_t TimerIdx,
                                         HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct,
                                         HRTIM_TimerInitTypeDef* HRTIM_TimerInitStruct)
{
  /* Check the parameters */
  assert_param(IS_HRTIM_HALFMODE(HRTIM_TimerInitStruct->HalfModeEnable));
  assert_param(IS_HRTIM_SYNCSTART(HRTIM_TimerInitStruct->StartOnSync));
  assert_param(IS_HRTIM_SYNCRESET(HRTIM_TimerInitStruct->ResetOnSync));
  assert_param(IS_HRTIM_DACSYNC(HRTIM_TimerInitStruct->DACSynchro));
  assert_param(IS_HRTIM_PRELOAD(HRTIM_TimerInitStruct->PreloadEnable));
  assert_param(IS_HRTIM_TIMERBURSTMODE(HRTIM_TimerInitStruct->BurstMode));
  assert_param(IS_HRTIM_UPDATEONREPETITION(HRTIM_TimerInitStruct->RepetitionUpdate));
 
  if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
  {
    /* Check parameters */
    assert_param(IS_HRTIM_UPDATEGATING_MASTER(HRTIM_TimerInitStruct->UpdateGating));  
    
    /* Configure master timer */
    HRTIM_MasterBase_Config(HRTIMx, HRTIM_BaseInitStruct);
    HRTIM_MasterWaveform_Config(HRTIMx, HRTIM_TimerInitStruct);
  }
  else
  {
    /* Check parameters */
    assert_param(IS_HRTIM_UPDATEGATING_TIM(HRTIM_TimerInitStruct->UpdateGating));  
    
    /* Configure timing unit */
    HRTIM_TimingUnitBase_Config(HRTIMx, TimerIdx, HRTIM_BaseInitStruct);
    HRTIM_TimingUnitWaveform_Config(HRTIMx, TimerIdx, HRTIM_TimerInitStruct);
  }
}

/**
  * @}
  */

/** @defgroup HRTIM_Group2 I/O operation methods 
 *  @brief   Data transfers functions 
 *
@verbatim   
 ===============================================================================
                      ##### IO operation methods #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the HRTIMx data 
    transfers.
    (+) Starts the DLL calibration.
    (+) Starts / stops the counter of a timer operating in basic time base mode
    (+) Starts / stops the output compare signal generation on the designed timer output
    (+) Starts / stops the PWM output signal generation on the designed timer output
    (+) Enables / disables a basic capture on the designed capture unit

@endverbatim
  * @{
  */

/**
  * @brief  Starts the DLL calibration
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  CalibrationRate: DLL calibration period
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_CALIBRATIONRATE_7300: 7.3 ms
  *                    @arg HRTIM_CALIBRATIONRATE_910: 910 us
  *                    @arg HRTIM_CALIBRATIONRATE_114: 114 us
  *                    @arg HRTIM_CALIBRATIONRATE_14: 14 us
  * @retval None
  */
void HRTIM_DLLCalibrationStart(HRTIM_TypeDef * HRTIMx, uint32_t CalibrationRate)
{
  uint32_t HRTIM_dllcr;
  
   /* Check the parameters */
  assert_param(IS_HRTIM_CALIBRATIONRATE(CalibrationRate));

  /* Configure DLL Calibration */
  HRTIM_dllcr = (HRTIMx->HRTIM_COMMON).DLLCR;
  
  /* Set the Calibration rate */
  HRTIM_dllcr &= ~(HRTIM_DLLCR_CALRTE);
  HRTIM_dllcr |= CalibrationRate;
    
  /* Start DLL calibration */
   HRTIM_dllcr |= HRTIM_DLLCR_CAL;
               
  /* Update HRTIMx register */
  (HRTIMx->HRTIM_COMMON).DLLCR = HRTIM_dllcr;
  
}
/**
  * @brief  Starts the counter of a timer operating in basic time base mode
  * @param  HRTIMx: pointer to HRTIM peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @retval None
  */
void HRTIM_SimpleBaseStart(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx)
{  
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx));
  
  /* Enable the timer counter */
  __HRTIM_ENABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
}

/**
  * @brief  Stops the counter of a timer operating in basic time base mode
  * @param  HRTIMx: pointer to HRTIM peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @retval None
  */
void HRTIM_SimpleBaseStop(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMERINDEX(TimerIdx)); 
  
  /* Disable the timer counter */
  __HRTIM_DISABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
}

/**
  * @brief  Starts the output compare signal generation on the designed timer output 
  * @param  HRTIMx: pointer to HRTIM peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval None
  */
void HRTIM_SimpleOCStart(HRTIM_TypeDef * HRTIMx,
                                         uint32_t TimerIdx,
                                         uint32_t OCChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));
  
  /* Enable the timer output */
   (HRTIMx->HRTIM_COMMON).OENR |= OCChannel;
       
    /* Enable the timer counter */
  __HRTIM_ENABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
  
}

/**
  * @brief  Stops the output compare signal generation on the designed timer output 
  * @param  HRTIMx: pointer to HRTIM peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval None
  */
void HRTIM_SimpleOCStop(HRTIM_TypeDef * HRTIMx,
                                        uint32_t TimerIdx,
                                        uint32_t OCChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));
  
  /* Disable the timer output */
  HRTIMx->HRTIM_COMMON.DISR |= OCChannel;
    
  /* Disable the timer counter */
   __HRTIM_DISABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
}

/**
  * @brief  Starts the PWM output signal generation on the designed timer output
  * @param  HRTIMx: pointer to HRTIM peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval None
  */
void HRTIM_SimplePWMStart(HRTIM_TypeDef * HRTIMx,
                                          uint32_t TimerIdx,
                                          uint32_t PWMChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));
  
  /* Enable the timer output */
  HRTIMx->HRTIM_COMMON.OENR |= PWMChannel;
    
  /* Enable the timer counter */
  __HRTIM_ENABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
}

/**
  * @brief  Stops the PWM output signal generation on the designed timer output
  * @param  HRTIMx: pointer to HRTIM peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval None
  */
void HRTIM_SimplePWMStop(HRTIM_TypeDef * HRTIMx,
                                         uint32_t TimerIdx,
                                         uint32_t PWMChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));
 
  /* Disable the timer output */
  HRTIMx->HRTIM_COMMON.DISR |= PWMChannel;
    
  /* Disable the timer counter */
   __HRTIM_DISABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
}

/**
  * @brief  Enables a basic capture on the designed capture unit
  * @param  HRTIMx: pointer to HRTIM peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  CaptureChannel: Timer output
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval None
  * @note  The external event triggering the capture is available for all timing 
  *        units. It can be used directly and is active as soon as the timing 
  *        unit counter is enabled.
  */
void HRTIM_SimpleCaptureStart(HRTIM_TypeDef * HRTIMx,
                                              uint32_t TimerIdx,
                                              uint32_t CaptureChannel)
{
  /* Enable the timer counter */
  __HRTIM_ENABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);

}

/**
  * @brief  Disables a basic capture on the designed capture unit 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  CaptureChannel: Timer output
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval None
  */
void HRTIM_SimpleCaptureStop(HRTIM_TypeDef * HRTIMx,
                                             uint32_t TimerIdx,
                                             uint32_t CaptureChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));
    
  /* Set the capture unit trigger */
  switch (CaptureChannel)
  {
    case HRTIM_CAPTUREUNIT_1:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].CPT1xCR = HRTIM_CAPTURETRIGGER_NONE;
    }
    break;
    case HRTIM_CAPTUREUNIT_2:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].CPT2xCR = HRTIM_CAPTURETRIGGER_NONE;
    }
    break;
    default:
    break;  
  }
  
  /* Disable the timer counter */
  if ((HRTIMx->HRTIM_TIMERx[TimerIdx].CPT1xCR == HRTIM_CAPTURETRIGGER_NONE) &&
      (HRTIMx->HRTIM_TIMERx[TimerIdx].CPT2xCR == HRTIM_CAPTURETRIGGER_NONE))
  {
    __HRTIM_DISABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
  }
  
}

/**
  * @brief  Enables the basic one pulse signal generation on the designed output 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  OnePulseChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval None
  */
void HRTIM_SimpleOnePulseStart(HRTIM_TypeDef * HRTIMx,
                                                uint32_t TimerIdx,
                                                uint32_t OnePulseChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OnePulseChannel));
  
  /* Enable the timer output */
  HRTIMx->HRTIM_COMMON.OENR |= OnePulseChannel;
    
  /* Enable the timer counter */
  __HRTIM_ENABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
}

/**
  * @brief  Disables the basic one pulse signal generation on the designed output 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  OnePulseChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval None
  */
void HRTIM_SimpleOnePulseStop(HRTIM_TypeDef * HRTIMx,
                                              uint32_t TimerIdx,
                                              uint32_t OnePulseChannel)
{
   /* Check the parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OnePulseChannel));
   
  /* Disable the timer output */
  HRTIMx->HRTIM_COMMON.DISR |= OnePulseChannel;
  
  /* Disable the timer counter */
  __HRTIM_DISABLE(HRTIMx, TimerIdxToTimerId[TimerIdx]);
}

/**
  * @brief  Starts the counter of the designated timer(s) operating in waveform mode
  *         Timers can be combined (ORed) to allow for simultaneous counter start
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimersToStart: Timer counter(s) to start
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMERID_MASTER 
  *                   @arg HRTIM_TIMERID_TIMER_A 
  *                   @arg HRTIM_TIMERID_TIMER_B 
  *                   @arg HRTIM_TIMERID_TIMER_C 
  *                   @arg HRTIM_TIMERID_TIMER_D 
  *                   @arg HRTIM_TIMERID_TIMER_E 
  * @retval None
  */
void HRTIM_WaveformCounterStart(HRTIM_TypeDef * HRTIMx,
                                                 uint32_t TimersToStart)
{ 
   /* Enable timer(s) counter */
   HRTIMx->HRTIM_MASTER.MCR |= TimersToStart;
}

/**
  * @brief  Stops the counter of the designated timer(s) operating in waveform mode
  *         Timers can be combined (ORed) to allow for simultaneous counter stop
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimersToStop: Timer counter(s) to stop
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMER_MASTER 
  *                   @arg HRTIM_TIMER_A 
  *                   @arg HRTIM_TIMER_B 
  *                   @arg HRTIM_TIMER_C 
  *                   @arg HRTIM_TIMER_D 
  *                   @arg HRTIM_TIMER_E 
  * @retval None
  */
void HRTIM_WaveformCounterStop(HRTIM_TypeDef * HRTIMx,
                                                uint32_t TimersToStop)
{
  /* Disable timer(s) counter */
  HRTIMx->HRTIM_MASTER.MCR &= ~TimersToStop;
}

/**
  * @brief  Enables the generation of the waveform signal on the designated output(s)
  *         Outputs can be combined (ORed) to allow for simultaneous output enabling
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  OutputsToStart: Timer output(s) to enable
  *                    This parameter can be any combination of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval None
  */
void HRTIM_WaveformOutputStart(HRTIM_TypeDef * HRTIMx,
                                                uint32_t OutputsToStart)
{
  /* Enable the HRTIM outputs */
  HRTIMx->HRTIM_COMMON.OENR = OutputsToStart;
}

/**
  * @brief  Disables the generation of the waveform signal on the designated output(s)
  *         Outputs can be combined (ORed) to allow for simultaneous output disabling
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  OutputsToStop: Timer output(s) to disable
  *                    This parameter can be any combination of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval None
  */
void HRTIM_WaveformOutputStop(HRTIM_TypeDef * HRTIMx,
                                               uint32_t OutputsToStop)
{
  /* Disable the HRTIM outputs */
  HRTIMx->HRTIM_COMMON.DISR = OutputsToStop;
}

/**
  * @brief  Enables or disables the Master and slaves interrupt request
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  HRTIM_IT: specifies the HRTIM interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_MASTER_IT_MCMP1: Master compare 1 interrupt source
  *            @arg HRTIM_MASTER_IT_MCMP2: Master compare 2 interrupt source
  *            @arg HRTIM_MASTER_IT_MCMP3: Master compare 3 interrupt Interrupt source
  *            @arg HRTIM_MASTER_IT_MCMP4: Master compare 4 Interrupt source
  *            @arg HRTIM_MASTER_IT_MREP: Master Repetition Interrupt source
  *            @arg HRTIM_MASTER_IT_SYNC: Synchronization input Interrupt source
  *            @arg HRTIM_MASTER_IT_MUPD: Master update Interrupt source
  *            @arg HRTIM_TIM_IT_CMP1: Timer compare 1 Interrupt source
  *            @arg HRTIM_TIM_IT_CMP2: Timer compare 2 Interrupt source
  *            @arg HRTIM_TIM_IT_CMP3: Timer compare 3 Interrupt source
  *            @arg HRTIM_TIM_IT_CMP4: Timer compare 4 Interrupt source
  *            @arg HRTIM_TIM_IT_REP: Timer repetition Interrupt source
  *            @arg HRTIM_TIM_IT_UPD: Timer update Interrupt source
  *            @arg HRTIM_TIM_IT_CPT1: Timer capture 1 Interrupt source
  *            @arg HRTIM_TIM_IT_CPT2: Timer capture 2 Interrupt source
  *            @arg HRTIM_TIM_IT_SET1: Timer output 1 set Interrupt source
  *            @arg HRTIM_TIM_IT_RST1: Timer output 1 reset Interrupt source
  *            @arg HRTIM_TIM_IT_SET2: Timer output 2 set Interrupt source
  *            @arg HRTIM_TIM_IT_RST2: Timer output 2 reset Interrupt source
  *            @arg HRTIM_TIM_IT_RST: Timer reset Interrupt source
  *            @arg HRTIM_TIM_IT_DLYPRT1: Timer delay protection Interrupt source
  * @param  NewState: new state of the TIM interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void HRTIM_ITConfig(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_IT, FunctionalState NewState)
{
  if(TimerIdx != HRTIM_TIMERINDEX_MASTER)
  {  
    if(NewState != DISABLE)
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxDIER |= HRTIM_IT;
    }
    else
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxDIER &= ~HRTIM_IT;
    }
  }
  else  
  {
    if(NewState != DISABLE)
    {
      HRTIMx->HRTIM_MASTER.MDIER |= HRTIM_IT;
    }
    else
    {
      HRTIMx->HRTIM_MASTER.MDIER &= ~HRTIM_IT;
    }  
  }
}

/**
  * @brief  Enables or disables the common interrupt request
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  HRTIM_IT: specifies the HRTIM interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_IT_FLT1: Fault 1 interrupt source
  *            @arg HRTIM_IT_FLT2: Fault 2 interrupt source
  *            @arg HRTIM_IT_FLT3: Fault 3 interrupt Interrupt source
  *            @arg HRTIM_IT_FLT4: Fault 4 Interrupt source
  *            @arg HRTIM_IT_FLT5: Fault 5  Interrupt source
  *            @arg HRTIM_IT_SYSFLT: System Fault Interrupt source
  *            @arg HRTIM_IT_DLLRDY: DLL ready Interrupt source
  *            @arg HRTIM_IT_BMPER: Burst mode period Interrupt source
  * @param  NewState: new state of the TIM interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void HRTIM_ITCommonConfig(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonIT, FunctionalState NewState)
{
   if(NewState != DISABLE)
    {
      HRTIMx->HRTIM_COMMON.IER |= HRTIM_CommonIT;
    }
    else
    {
      HRTIMx->HRTIM_COMMON.IER &= ~HRTIM_CommonIT;
    }
}

/**
  * @brief  Clears the Master and slaves interrupt flags
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  HRTIM_FLAG: specifies the HRTIM flags sources to be cleared.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_MASTER_FLAG_MCMP1: Master compare 1 interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MCMP2: Master compare 2 interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MCMP3: Master compare 3 interrupt Interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MCMP4: Master compare 4 Interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MREP: Master Repetition Interrupt flag
  *            @arg HRTIM_MASTER_FLAG_SYNC: Synchronization input Interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MUPD: Master update Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CMP1: Timer compare 1 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CMP2: Timer compare 2 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CMP3: Timer compare 3 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CMP4: Timer compare 4 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_REP: Timer repetition Interrupt flag
  *            @arg HRTIM_TIM_FLAG_UPD: Timer update Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CPT1: Timer capture 1 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CPT2: Timer capture 2 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_SET1: Timer output 1 set Interrupt flag
  *            @arg HRTIM_TIM_FLAG_RST1: Timer output 1 reset Interrupt flag
  *            @arg HRTIM_TIM_FLAG_SET2: Timer output 2 set Interrupt flag
  *            @arg HRTIM_TIM_FLAG_RST2: Timer output 2 reset Interrupt flag
  *            @arg HRTIM_TIM_FLAG_RST: Timer reset Interrupt flag
  *            @arg HRTIM_TIM_FLAG_DLYPRT1: Timer delay protection Interrupt flag
  * @retval None
  */
void HRTIM_ClearFlag(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_FLAG)
{
  if(TimerIdx != HRTIM_TIMERINDEX_MASTER)
  {
    HRTIMx->HRTIM_MASTER.MICR |= HRTIM_FLAG;
  }
  else
  {
     HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxICR |= HRTIM_FLAG;
  }  
}

/**
  * @brief  Clears the common interrupt flags
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  HRTIM_FLAG: specifies the HRTIM flags to be cleared.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_FLAG_FLT1: Fault 1 interrupt flag
  *            @arg HRTIM_FLAG_FLT2: Fault 2 interrupt flag
  *            @arg HRTIM_FLAG_FLT3: Fault 3 interrupt Interrupt flag
  *            @arg HRTIM_FLAG_FLT4: Fault 4 Interrupt flag
  *            @arg HRTIM_FLAG_FLT5: Fault 5  Interrupt flag
  *            @arg HRTIM_FLAG_SYSFLT: System Fault Interrupt flag
  *            @arg HRTIM_FLAG_DLLRDY: DLL ready Interrupt flag
  *            @arg HRTIM_FLAG_BMPER: Burst mode period Interrupt flag
  * @retval None
  */
void HRTIM_ClearCommonFlag(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonFLAG)
{
  HRTIMx->HRTIM_COMMON.ICR |= HRTIM_CommonFLAG;
}

/**
  * @brief  Clears the Master and slaves interrupt request pending bits
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  HRTIM_IT: specifies the HRTIM interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_MASTER_IT_MCMP1: Master compare 1 interrupt source
  *            @arg HRTIM_MASTER_IT_MCMP2: Master compare 2 interrupt source
  *            @arg HRTIM_MASTER_IT_MCMP3: Master compare 3 interrupt Interrupt source
  *            @arg HRTIM_MASTER_IT_MCMP4: Master compare 4 Interrupt source
  *            @arg HRTIM_MASTER_IT_MREP: Master Repetition Interrupt source
  *            @arg HRTIM_MASTER_IT_SYNC: Synchronization input Interrupt source
  *            @arg HRTIM_MASTER_IT_MUPD: Master update Interrupt source
  *            @arg HRTIM_TIM_IT_CMP1: Timer compare 1 Interrupt source
  *            @arg HRTIM_TIM_IT_CMP2: Timer compare 2 Interrupt source
  *            @arg HRTIM_TIM_IT_CMP3: Timer compare 3 Interrupt source
  *            @arg HRTIM_TIM_IT_CMP4: Timer compare 4 Interrupt source
  *            @arg HRTIM_TIM_IT_REP: Timer repetition Interrupt source
  *            @arg HRTIM_TIM_IT_UPD: Timer update Interrupt source
  *            @arg HRTIM_TIM_IT_CPT1: Timer capture 1 Interrupt source
  *            @arg HRTIM_TIM_IT_CPT2: Timer capture 2 Interrupt source
  *            @arg HRTIM_TIM_IT_SET1: Timer output 1 set Interrupt source
  *            @arg HRTIM_TIM_IT_RST1: Timer output 1 reset Interrupt source
  *            @arg HRTIM_TIM_IT_SET2: Timer output 2 set Interrupt source
  *            @arg HRTIM_TIM_IT_RST2: Timer output 2 reset Interrupt source
  *            @arg HRTIM_TIM_IT_RST: Timer reset Interrupt source
  *            @arg HRTIM_TIM_IT_DLYPRT: Timer delay protection Interrupt source
  * @retval None
  */
void HRTIM_ClearITPendingBit(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_IT)
{
  if(TimerIdx != HRTIM_TIMERINDEX_MASTER)
  {
    HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxICR |= HRTIM_IT;
  }
  else 
  {   
    HRTIMx->HRTIM_MASTER.MICR |= HRTIM_IT;
  }
}

/**
  * @brief  Clears the common interrupt pending bits
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  HRTIM_IT: specifies the HRTIM interrupts sources to be cleared.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_IT_FLT1: Fault 1 interrupt source
  *            @arg HRTIM_IT_FLT2: Fault 2 interrupt source
  *            @arg HRTIM_IT_FLT3: Fault 3 interrupt Interrupt source
  *            @arg HRTIM_IT_FLT4: Fault 4 Interrupt source
  *            @arg HRTIM_IT_FLT5: Fault 5  Interrupt source
  *            @arg HRTIM_IT_SYSFLT: System Fault Interrupt source
  *            @arg HRTIM_IT_DLLRDY: DLL ready Interrupt source
  *            @arg HRTIM_IT_BMPER: Burst mode period Interrupt source
  * @retval None
  */
void HRTIM_ClearCommonITPendingBit(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonIT)
{
  HRTIMx->HRTIM_COMMON.ICR |= HRTIM_CommonIT;
}


/**
  * @brief  Checks whether the specified HRTIM flag is set or not.
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  HRTIM_FLAG: specifies the HRTIM flags to check.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_MASTER_FLAG_MCMP1: Master compare 1 interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MCMP2: Master compare 2 interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MCMP3: Master compare 3 interrupt Interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MCMP4: Master compare 4 Interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MREP: Master Repetition Interrupt flag
  *            @arg HRTIM_MASTER_FLAG_SYNC: Synchronization input Interrupt flag
  *            @arg HRTIM_MASTER_FLAG_MUPD: Master update Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CMP1: Timer compare 1 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CMP2: Timer compare 2 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CMP3: Timer compare 3 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CMP4: Timer compare 4 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_REP: Timer repetition Interrupt flag
  *            @arg HRTIM_TIM_FLAG_UPD: Timer update Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CPT1: Timer capture 1 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_CPT2: Timer capture 2 Interrupt flag
  *            @arg HRTIM_TIM_FLAG_SET1: Timer output 1 set Interrupt flag
  *            @arg HRTIM_TIM_FLAG_RST1: Timer output 1 reset Interrupt flag
  *            @arg HRTIM_TIM_FLAG_SET2: Timer output 2 set Interrupt flag
  *            @arg HRTIM_TIM_FLAG_RST2: Timer output 2 reset Interrupt flag
  *            @arg HRTIM_TIM_FLAG_RST: Timer reset Interrupt flag
  *            @arg HRTIM_TIM_FLAG_DLYPRT: Timer delay protection Interrupt flag
  * @retval The new state of HRTIM_FLAG (SET or RESET).
  */
FlagStatus HRTIM_GetFlagStatus(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_FLAG)
{
  FlagStatus bitstatus = RESET;  

  if(TimerIdx != HRTIM_TIMERINDEX_MASTER)
  {  
    if ((HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxISR & HRTIM_FLAG) != RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if ((HRTIMx->HRTIM_MASTER.MISR & HRTIM_FLAG) != RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }  
  return bitstatus;
}

/**
  * @brief  Checks whether the specified HRTIM common flag is set or not.
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  HRTIM_FLAG: specifies the HRTIM flags to check.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_FLAG_FLT1: Fault 1 interrupt flag
  *            @arg HRTIM_FLAG_FLT2: Fault 2 interrupt flag
  *            @arg HRTIM_FLAG_FLT3: Fault 3 interrupt Interrupt flag
  *            @arg HRTIM_FLAG_FLT4: Fault 4 Interrupt flag
  *            @arg HRTIM_FLAG_FLT5: Fault 5  Interrupt flag
  *            @arg HRTIM_FLAG_SYSFLT: System Fault Interrupt flag
  *            @arg HRTIM_FLAG_DLLRDY: DLL ready Interrupt flag
  *            @arg HRTIM_FLAG_BMPER: Burst mode period Interrupt flag
  * @retval The new state of HRTIM_FLAG (SET or RESET).
  */
FlagStatus HRTIM_GetCommonFlagStatus(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonFLAG)
{
  FlagStatus bitstatus = RESET;  

  if((HRTIMx->HRTIM_COMMON.ISR & HRTIM_CommonFLAG) != RESET)
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
  * @brief  Checks whether the specified HRTIM interrupt has occurred or not.
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  HRTIM_IT: specifies the HRTIM flags sources to be cleared.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_MASTER_IT_MCMP1: Master compare 1 interrupt 
  *            @arg HRTIM_MASTER_IT_MCMP2: Master compare 2 interrupt 
  *            @arg HRTIM_MASTER_IT_MCMP3: Master compare 3 interrupt Interrupt 
  *            @arg HRTIM_MASTER_IT_MCMP4: Master compare 4 Interrupt 
  *            @arg HRTIM_MASTER_IT_MREP: Master Repetition Interrupt 
  *            @arg HRTIM_MASTER_IT_SYNC: Synchronization input Interrupt 
  *            @arg HRTIM_MASTER_IT_MUPD: Master update Interrupt 
  *            @arg HRTIM_TIM_IT_CMP1: Timer compare 1 Interrupt 
  *            @arg HRTIM_TIM_IT_CMP2: Timer compare 2 Interrupt 
  *            @arg HRTIM_TIM_IT_CMP3: Timer compare 3 Interrupt 
  *            @arg HRTIM_TIM_IT_CMP4: Timer compare 4 Interrupt 
  *            @arg HRTIM_TIM_IT_REP: Timer repetition Interrupt 
  *            @arg HRTIM_TIM_IT_UPD: Timer update Interrupt 
  *            @arg HRTIM_TIM_IT_CPT1: Timer capture 1 Interrupt 
  *            @arg HRTIM_TIM_IT_CPT2: Timer capture 2 Interrupt 
  *            @arg HRTIM_TIM_IT_SET1: Timer output 1 set Interrupt 
  *            @arg HRTIM_TIM_IT_RST1: Timer output 1 reset Interrupt 
  *            @arg HRTIM_TIM_IT_SET2: Timer output 2 set Interrupt 
  *            @arg HRTIM_TIM_IT_RST2: Timer output 2 reset Interrupt 
  *            @arg HRTIM_TIM_IT_RST: Timer reset Interrupt 
  *            @arg HRTIM_TIM_IT_DLYPRT: Timer delay protection Interrupt 
  * @retval The new state of the HRTIM_IT(SET or RESET).
  */
ITStatus HRTIM_GetITStatus(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_IT)
{
  ITStatus bitstatus = RESET;  
  uint16_t itstatus = 0x0, itenable = 0x0;

  if(TimerIdx != HRTIM_TIMERINDEX_MASTER)
  {  
    itstatus = HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxISR & HRTIM_IT;
  
    itenable = HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxDIER & HRTIM_IT;
    if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    itstatus = HRTIMx->HRTIM_MASTER.MISR & HRTIM_IT;
  
    itenable = HRTIMx->HRTIM_MASTER.MDIER & HRTIM_IT;
    if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }  
  return bitstatus;
}

/**
  * @brief  Checks whether the specified HRTIM common interrupt has occurred or not.
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  HRTIM_IT: specifies the HRTIM interrupt source to check.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_IT_FLT1: Fault 1 interrupt 
  *            @arg HRTIM_IT_FLT2: Fault 2 interrupt 
  *            @arg HRTIM_IT_FLT3: Fault 3 interrupt Interrupt 
  *            @arg HRTIM_IT_FLT4: Fault 4 Interrupt 
  *            @arg HRTIM_IT_FLT5: Fault 5  Interrupt 
  *            @arg HRTIM_IT_SYSFLT: System Fault Interrupt 
  *            @arg HRTIM_IT_DLLRDY: DLL ready Interrupt flag
  *            @arg HRTIM_IT_BMPER: Burst mode period Interrupt 
  * @retval The new state of HRTIM_FLAG (SET or RESET).
  */
ITStatus HRTIM_GetCommonITStatus(HRTIM_TypeDef * HRTIMx, uint32_t HRTIM_CommonIT)
{
  ITStatus bitstatus = RESET;  
  uint16_t itstatus = 0x0, itenable = 0x0;
 
  itstatus = HRTIMx->HRTIM_COMMON.ISR & HRTIM_CommonIT; 
  itenable = HRTIMx->HRTIM_COMMON.IER & HRTIM_CommonIT;
  
  if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
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
  * @brief  Enables or disables the HRTIMx's DMA Requests.
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  HRTIM_DMA: specifies the DMA Request sources.
  *          This parameter can be any combination of the following values:
  *            @arg HRTIM_MASTER_DMA_MCMP1: Master compare 1 DMA request source
  *            @arg HRTIM_MASTER_DMA_MCMP2: Master compare 2 DMA request source
  *            @arg HRTIM_MASTER_DMA_MCMP3: Master compare 3 DMA request source
  *            @arg HRTIM_MASTER_DMA_MCMP4: Master compare 4 DMA request source
  *            @arg HRTIM_MASTER_DMA_MREP: Master Repetition DMA request source
  *            @arg HRTIM_MASTER_DMA_SYNC: Synchronization input DMA request source
  *            @arg HRTIM_MASTER_DMA_MUPD:Master update DMA request source
  *            @arg HRTIM_TIM_DMA_CMP1: Timer compare 1 DMA request source 
  *            @arg HRTIM_TIM_DMA_CMP2: Timer compare 2 DMA request source 
  *            @arg HRTIM_TIM_DMA_CMP3: Timer compare 3 DMA request source 
  *            @arg HRTIM_TIM_DMA_CMP4: Timer compare 4 DMA request source 
  *            @arg HRTIM_TIM_DMA_REP: Timer repetition DMA request source 
  *            @arg HRTIM_TIM_DMA_UPD: Timer update DMA request source 
  *            @arg HRTIM_TIM_DMA_CPT1: Timer capture 1 DMA request source 
  *            @arg HRTIM_TIM_DMA_CPT2: Timer capture 2 DMA request source 
  *            @arg HRTIM_TIM_DMA_SET1: Timer output 1 set DMA request source 
  *            @arg HRTIM_TIM_DMA_RST1: Timer output 1 reset DMA request source 
  *            @arg HRTIM_TIM_DMA_SET2: Timer output 2 set DMA request source 
  *            @arg HRTIM_TIM_DMA_RST2: Timer output 2 reset DMA request source 
  *            @arg HRTIM_TIM_DMA_RST: Timer reset DMA request source 
  *            @arg HRTIM_TIM_DMA_DLYPRT: Timer delay protection DMA request source 
  * @param  NewState: new state of the DMA Request sources.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void HRTIM_DMACmd(HRTIM_TypeDef* HRTIMx, uint32_t TimerIdx, uint32_t HRTIM_DMA, FunctionalState NewState)
{
  if(TimerIdx != HRTIM_TIMERINDEX_MASTER)
  { 
     if(NewState != DISABLE)
     {
       HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxDIER |= HRTIM_DMA;
     }
     else
     {
       HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxDIER &= ~HRTIM_DMA;
     }
  }
  else
  {
     if(NewState != DISABLE)
     {
       HRTIMx->HRTIM_MASTER.MDIER |= HRTIM_DMA;
     }
     else
     {
       HRTIMx->HRTIM_MASTER.MDIER &= ~HRTIM_DMA;
     }
  }  
}

/**
  * @}
  */

/** @defgroup HRTIM_Group3 Peripheral Control methods 
 *  @brief   management functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control methods #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the HRTIMx data 
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Configures an output in basic output compare mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  OCChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2 
  * @param  pBasicOCChannelCfg: pointer to the basic output compare output configuration structure
  * @note When the timer operates in basic output compare mode:
  *         Output 1 is implicitely controled by the compare unit 1
  *         Output 2 is implicitely controled by the compare unit 2
  *       Output Set/Reset crossbar is set according to the selected output compare mode:
  *         Toggle: SETxyR = RSTxyR = CMPy
  *         Active: SETxyR = CMPy, RSTxyR = 0
  *         Inactive: SETxy =0, RSTxy = CMPy
  * @retval None
  */
void HRTIM_SimpleOCChannelConfig(HRTIM_TypeDef * HRTIM_,
                                                 uint32_t TimerIdx,
                                                 uint32_t OCChannel,
                                                 HRTIM_BasicOCChannelCfgTypeDef* pBasicOCChannelCfg)
{
  uint32_t CompareUnit = HRTIM_COMPAREUNIT_1;
  HRTIM_CompareCfgTypeDef CompareCfg;
  HRTIM_OutputCfgTypeDef OutputCfg;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OCChannel));
  assert_param(IS_HRTIM_BASICOCMODE(pBasicOCChannelCfg->Mode));
  assert_param(IS_HRTIM_OUTPUTPOLARITY(pBasicOCChannelCfg->Polarity));
  assert_param(IS_HRTIM_OUTPUTIDLESTATE(pBasicOCChannelCfg->IdleState));
    
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
    default:
    break;
  }
  
  CompareCfg.CompareValue = pBasicOCChannelCfg->Pulse;
  CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  CompareCfg.AutoDelayedTimeout = 0;
  
  HRTIM_CompareUnitConfig(HRTIM_,
                          TimerIdx,
                          CompareUnit,
                          &CompareCfg);
  
  /* Configure timer output */
  OutputCfg.Polarity = pBasicOCChannelCfg->Polarity;
  OutputCfg.IdleState = pBasicOCChannelCfg->IdleState;
  OutputCfg.FaultState = HRTIM_OUTPUTFAULTSTATE_NONE;
  OutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  OutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  OutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
  
  switch (pBasicOCChannelCfg->Mode)
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
    default:
    break;  
  }
  
  HRTIM_OutputConfig(HRTIM_, TimerIdx, OCChannel, &OutputCfg);   
}

/**
  * @brief  Configures an output in basic PWM mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  PWMChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2 
  * @param  pBasicPWMChannelCfg: pointer to the basic PWM output configuration structure
  * @note When the timer operates in basic PWM output mode:
  *         Output 1 is implicitly controled by the compare unit 1
  *         Output 2 is implicitly controled by the compare unit 2
  *         Output Set/Reset crossbar is set as follows:
  *         Output 1: SETx1R = CMP1, RSTx1R = PER
  *         Output 2: SETx2R = CMP2, RST2R = PER
  * @retval None
  */
void HRTIM_SimplePWMChannelConfig(HRTIM_TypeDef * HRTIM_,
                                                  uint32_t TimerIdx,
                                                  uint32_t PWMChannel,
                                                  HRTIM_BasicPWMChannelCfgTypeDef* pBasicPWMChannelCfg)
{
  uint32_t CompareUnit = HRTIM_COMPAREUNIT_1;
  HRTIM_CompareCfgTypeDef CompareCfg;
  HRTIM_OutputCfgTypeDef OutputCfg;

  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, PWMChannel));
  assert_param(IS_HRTIM_OUTPUTPOLARITY(pBasicPWMChannelCfg->Polarity));
  assert_param(IS_HRTIM_OUTPUTIDLESTATE(pBasicPWMChannelCfg->IdleState));

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
    default:
    break;  
  }
  
  CompareCfg.CompareValue = pBasicPWMChannelCfg->Pulse;
  CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  CompareCfg.AutoDelayedTimeout = 0;
  
  HRTIM_CompareUnitConfig(HRTIM_,
                          TimerIdx,
                          CompareUnit,
                          &CompareCfg);
  
  /* Configure timer output */
  OutputCfg.Polarity = pBasicPWMChannelCfg->Polarity;
  OutputCfg.IdleState = pBasicPWMChannelCfg->IdleState;
  OutputCfg.FaultState = HRTIM_OUTPUTFAULTSTATE_NONE;
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
  
  HRTIM_OutputConfig(HRTIM_, TimerIdx, PWMChannel, &OutputCfg);  
}

/**
  * @brief  Configures a basic capture 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  CaptureChannel: Capture unit
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @param  pBasicCaptureChannelCfg: pointer to the basic capture configuration structure
  * @note When the timer operates in basic capture mode the capture is triggered
  *       by the designated external event and GPIO input is implicitly used as event source.
  *       The cature can be triggered by a rising edge, a falling edge or both
  *       edges on event channel.
  * @retval None
  */
void HRTIM_SimpleCaptureChannelConfig(HRTIM_TypeDef * HRTIMx,
                                                      uint32_t TimerIdx,
                                                      uint32_t CaptureChannel,
                                                      HRTIM_BasicCaptureChannelCfgTypeDef* pBasicCaptureChannelCfg)
{
  HRTIM_EventCfgTypeDef EventCfg;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureChannel));
  assert_param(IS_HRTIM_EVENT(pBasicCaptureChannelCfg->Event));
  assert_param(IS_HRTIM_EVENTPOLARITY(pBasicCaptureChannelCfg->EventPolarity));
  assert_param(IS_HRTIM_EVENTSENSITIVITY(pBasicCaptureChannelCfg->EventSensitivity));
  assert_param(IS_HRTIM_EVENTFILTER(pBasicCaptureChannelCfg->EventFilter));
  
  /* Configure external event channel */
  EventCfg.FastMode = HRTIM_EVENTFASTMODE_DISABLE;
  EventCfg.Filter = pBasicCaptureChannelCfg->EventFilter;
  EventCfg.Polarity = pBasicCaptureChannelCfg->EventPolarity;
  EventCfg.Sensitivity = pBasicCaptureChannelCfg->EventSensitivity;
  EventCfg.Source = HRTIM_EVENTSRC_1;
    
  HRTIM_ExternalEventConfig(HRTIMx,
                    pBasicCaptureChannelCfg->Event,
                    &EventCfg);

  /* Memorize capture trigger (will be configured when the capture is started */  
  HRTIM_CaptureUnitConfig(HRTIMx,
                          TimerIdx,
                          CaptureChannel,
                          pBasicCaptureChannelCfg->Event); 
}

/**
  * @brief  Configures an output basic one pulse mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  OnePulseChannel: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2 
  * @param  pBasicOnePulseChannelCfg: pointer to the basic one pulse output configuration structure
  * @note When the timer operates in basic one pulse mode:
  *         the timer counter is implicitly started by the reset event,
  *         the reset of the timer counter is triggered by the designated external event
  *         GPIO input is implicitly used as event source,
  *         Output 1 is implicitly controled by the compare unit 1,
  *         Output 2 is implicitly controled by the compare unit 2.
  *         Output Set/Reset crossbar is set as follows:
  *         Output 1: SETx1R = CMP1, RSTx1R = PER
  *         Output 2: SETx2R = CMP2, RST2R = PER
  *         The counter mode should be HRTIM_MODE_SINGLESHOT_RETRIGGERABLE
  * @retval None
  */
void HRTIM_SimpleOnePulseChannelConfig(HRTIM_TypeDef * HRTIM_,
                                                       uint32_t TimerIdx,
                                                       uint32_t OnePulseChannel,
                                                       HRTIM_BasicOnePulseChannelCfgTypeDef* pBasicOnePulseChannelCfg)
{
  uint32_t CompareUnit = HRTIM_COMPAREUNIT_1;
  HRTIM_CompareCfgTypeDef CompareCfg;
  HRTIM_OutputCfgTypeDef OutputCfg;
  HRTIM_EventCfgTypeDef EventCfg;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, OnePulseChannel));
  assert_param(IS_HRTIM_OUTPUTPOLARITY(pBasicOnePulseChannelCfg->OutputPolarity));
  assert_param(IS_HRTIM_OUTPUTIDLESTATE(pBasicOnePulseChannelCfg->OutputIdleState));
  assert_param(IS_HRTIM_EVENT(pBasicOnePulseChannelCfg->Event));
  assert_param(IS_HRTIM_EVENTPOLARITY(pBasicOnePulseChannelCfg->EventPolarity));
  assert_param(IS_HRTIM_EVENTSENSITIVITY(pBasicOnePulseChannelCfg->EventSensitivity));
  assert_param(IS_HRTIM_EVENTFILTER(pBasicOnePulseChannelCfg->EventFilter));
  
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
    default:
    break;      
  }
  
  CompareCfg.CompareValue = pBasicOnePulseChannelCfg->Pulse;
  CompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  CompareCfg.AutoDelayedTimeout = 0;
  
  HRTIM_CompareUnitConfig(HRTIM_,
                          TimerIdx,
                          CompareUnit,
                          &CompareCfg);
  
  /* Configure timer output */
  OutputCfg.Polarity = pBasicOnePulseChannelCfg->OutputPolarity;
  OutputCfg.IdleState = pBasicOnePulseChannelCfg->OutputIdleState;
  OutputCfg.FaultState = HRTIM_OUTPUTFAULTSTATE_NONE;
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
  
  HRTIM_OutputConfig(HRTIM_,
                     TimerIdx,
                     OnePulseChannel,
                     &OutputCfg);  
  
  /* Configure external event channel */
  EventCfg.FastMode = HRTIM_EVENTFASTMODE_DISABLE;
  EventCfg.Filter = pBasicOnePulseChannelCfg->EventFilter;
  EventCfg.Polarity = pBasicOnePulseChannelCfg->EventPolarity;
  EventCfg.Sensitivity = pBasicOnePulseChannelCfg->EventSensitivity;
  EventCfg.Source = HRTIM_EVENTSRC_1;
    
  HRTIM_ExternalEventConfig(HRTIM_,
                    pBasicOnePulseChannelCfg->Event,
                    &EventCfg);

  /* Configure the timer reset register */
  HRTIM_TIM_ResetConfig(HRTIM_,
                        TimerIdx, 
                        pBasicOnePulseChannelCfg->Event);  
}

/**
  * @brief  Configures the general behavior of a timer operating in waveform mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  pTimerCfg: pointer to the timer configuration structure
  * @note When the timer operates in waveform mode, all the features supported by
  *       the HRTIMx are available without any limitation.
  * @retval None
  */
void HRTIM_WaveformTimerConfig(HRTIM_TypeDef * HRTIMx,
                                                uint32_t TimerIdx,
                                                HRTIM_TimerCfgTypeDef * pTimerCfg)
{
  uint32_t HRTIM_timcr;
  uint32_t HRTIM_timfltr;
  uint32_t HRTIM_timoutr;
  uint32_t HRTIM_timrstr;

  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_TIMPUSHPULLMODE(pTimerCfg->PushPull));
  assert_param(IS_HRTIM_TIMFAULTENABLE(pTimerCfg->FaultEnable));
  assert_param(IS_HRTIM_TIMFAULTLOCK(pTimerCfg->FaultLock));
  assert_param(IS_HRTIM_TIMDEADTIMEINSERTION(pTimerCfg->DeadTimeInsertion));
  assert_param(IS_HRTIM_TIMDELAYEDPROTECTION(pTimerCfg->DelayedProtectionMode));
  assert_param(IS_HRTIM_TIMUPDATETRIGGER(pTimerCfg->UpdateTrigger)); 
  assert_param(IS_HRTIM_TIMRESETTRIGGER(pTimerCfg->ResetTrigger));
  assert_param(IS_HRTIM_TIMUPDATEONRESET(pTimerCfg->ResetUpdate));

  /* Configure timing unit (Timer A to Timer E) */
  HRTIM_timcr = HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR;
  HRTIM_timfltr  = HRTIMx->HRTIM_TIMERx[TimerIdx].FLTxR;
  HRTIM_timoutr  = HRTIMx->HRTIM_TIMERx[TimerIdx].OUTxR;
  HRTIM_timrstr  = HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR;
  
  /* Set the push-pull mode */
  HRTIM_timcr &= ~(HRTIM_TIMCR_PSHPLL);
  HRTIM_timcr |= pTimerCfg->PushPull;
  
  /* Enable/Disable registers update on timer counter reset */
  HRTIM_timcr &= ~(HRTIM_TIMCR_TRSTU);
  HRTIM_timcr |= pTimerCfg->ResetUpdate;
  
  /* Set the timer update trigger */
  HRTIM_timcr &= ~(HRTIM_TIMCR_TIMUPDATETRIGGER);
  HRTIM_timcr |= pTimerCfg->UpdateTrigger;
  
  /* Enable/Disable the fault channel at timer level */
  HRTIM_timfltr &= ~(HRTIM_FLTR_FLTxEN);
  HRTIM_timfltr |= (pTimerCfg->FaultEnable & HRTIM_FLTR_FLTxEN);
  
  /* Lock/Unlock fault sources at timer level */
  HRTIM_timfltr &= ~(HRTIM_FLTR_FLTCLK);
  HRTIM_timfltr |= pTimerCfg->FaultLock;
  
  /* Enable/Disable dead time insertion at timer level */
  HRTIM_timoutr &= ~(HRTIM_OUTR_DTEN);
  HRTIM_timoutr |= pTimerCfg->DeadTimeInsertion;

  /* Enable/Disable delayed protection at timer level */
  HRTIM_timoutr &= ~(HRTIM_OUTR_DLYPRT| HRTIM_OUTR_DLYPRTEN);
  HRTIM_timoutr |= pTimerCfg->DelayedProtectionMode;
  
  /* Set the timer counter reset trigger */
  HRTIM_timrstr = pTimerCfg->ResetTrigger;

  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR  = HRTIM_timcr;
  HRTIMx->HRTIM_TIMERx[TimerIdx].FLTxR = HRTIM_timfltr;
  HRTIMx->HRTIM_TIMERx[TimerIdx].OUTxR = HRTIM_timoutr;
  HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_timrstr;
 }

/**
  * @brief  Configures the compare unit of a timer operating in waveform mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   0xFF for master timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
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
  * @retval None
  */
 void HRTIM_WaveformCompareConfig(HRTIM_TypeDef * HRTIMx,
                                                  uint32_t TimerIdx,
                                                  uint32_t CompareUnit,
                                                  HRTIM_CompareCfgTypeDef* pCompareCfg)
{
    uint32_t HRTIM_timcr;

  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_COMPAREUNIT_AUTODELAYEDMODE(CompareUnit, pCompareCfg->AutoDelayedMode));
  
  /* Configure the compare unit */
  switch (CompareUnit)
  {
    case HRTIM_COMPAREUNIT_1:
    {
      /* Set the compare value */
      HRTIMx->HRTIM_TIMERx[TimerIdx].CMP1xR = pCompareCfg->CompareValue;
    }
    break;
    case HRTIM_COMPAREUNIT_2:
    {
      /* Set the compare value */
      HRTIMx->HRTIM_TIMERx[TimerIdx].CMP2xR = pCompareCfg->CompareValue;
      
      if (pCompareCfg->AutoDelayedMode != HRTIM_AUTODELAYEDMODE_REGULAR)
      {
        /* Configure auto-delayed mode */
        HRTIM_timcr = HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR;
        HRTIM_timcr &= ~HRTIM_TIMCR_DELCMP2;
        HRTIM_timcr |= pCompareCfg->AutoDelayedMode;
        HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR = HRTIM_timcr;
        
        /* Set the compare value for timeout compare unit (if any) */
        if (pCompareCfg->AutoDelayedMode == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1)
        {
          HRTIMx->HRTIM_TIMERx[TimerIdx].CMP1xR = pCompareCfg->AutoDelayedTimeout;
        }
        else if (pCompareCfg->AutoDelayedMode == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3)
        {
          HRTIMx->HRTIM_TIMERx[TimerIdx].CMP3xR = pCompareCfg->AutoDelayedTimeout;
        }
      }
    }
    break;
    case HRTIM_COMPAREUNIT_3:
    {
      /* Set the compare value */
      HRTIMx->HRTIM_TIMERx[TimerIdx].CMP3xR = pCompareCfg->CompareValue;
    }
    break;
    case HRTIM_COMPAREUNIT_4:
    {
      /* Set the compare value */
      HRTIMx->HRTIM_TIMERx[TimerIdx].CMP4xR = pCompareCfg->CompareValue;
      
      if (pCompareCfg->AutoDelayedMode != HRTIM_AUTODELAYEDMODE_REGULAR)
      {
        /* Configure auto-delayed mode */
        HRTIM_timcr = HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR;
        HRTIM_timcr &= ~HRTIM_TIMCR_DELCMP4;
        HRTIM_timcr |= (pCompareCfg->AutoDelayedMode << 2);
        HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR = HRTIM_timcr;
        
        /* Set the compare value for timeout compare unit (if any) */
        if (pCompareCfg->AutoDelayedMode == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1)
        {
          HRTIMx->HRTIM_TIMERx[TimerIdx].CMP1xR = pCompareCfg->AutoDelayedTimeout;
        }
        else if (pCompareCfg->AutoDelayedMode == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3)
        {
          HRTIMx->HRTIM_TIMERx[TimerIdx].CMP3xR = pCompareCfg->AutoDelayedTimeout;
        }
      }
    }
    break;
    default:
    break;  
  }
}

/**
  * @brief  Sets the HRTIMx Master Comparex Register value 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  CompareUnit: Compare unit to configure
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_COMPAREUNIT_1: Compare unit 1
  *                    @arg HRTIM_COMPAREUNIT_2: Compare unit 2
  *                    @arg HRTIM_COMPAREUNIT_3: Compare unit 3
  *                    @arg HRTIM_COMPAREUNIT_4: Compare unit 4
  * @param  Compare: specifies the Comparex register new value
  * @retval None
  */
void HRTIM_MasterSetCompare(HRTIM_TypeDef * HRTIMx,
                                                  uint32_t CompareUnit,
                                                  uint32_t Compare)
{
  /* Check parameters */
  assert_param(IS_HRTIM_COMPAREUNIT(CompareUnit));
  
  /* Configure the compare unit */
  switch (CompareUnit)
  {
    case HRTIM_COMPAREUNIT_1:
    {
      /* Set the compare value */
      HRTIMx->HRTIM_MASTER.MCMP1R = Compare;
    }
    break;
    case HRTIM_COMPAREUNIT_2:
    {
      /* Set the compare value */
      HRTIMx->HRTIM_MASTER.MCMP2R = Compare;
    }
    break;
    case HRTIM_COMPAREUNIT_3:
    {
      /* Set the compare value */
      HRTIMx->HRTIM_MASTER.MCMP3R = Compare;
    }
    break;
    case HRTIM_COMPAREUNIT_4:
    {
      /* Set the compare value */
      HRTIMx->HRTIM_MASTER.MCMP4R = Compare;
    }
    break;
    default:
    break;
  }  
}
/**
  * @brief  Configures the capture unit of a timer operating in waveform mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  CaptureChannel: Capture unit to configure
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @param  pCaptureCfg: pointer to the compare unit configuration structure
  * @retval None
  */
void HRTIM_WaveformCaptureConfig(HRTIM_TypeDef * HRTIMx,
                                                  uint32_t TimerIdx,
                                                  uint32_t CaptureUnit,
                                                  HRTIM_CaptureCfgTypeDef* pCaptureCfg)
{
  /* Configure the capture unit */
  switch (CaptureUnit)
  {
    case HRTIM_CAPTUREUNIT_1:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].CPT1xCR = pCaptureCfg->Trigger;
    }
    break;
    case HRTIM_CAPTUREUNIT_2:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].CPT2xCR = pCaptureCfg->Trigger;
    }
    break;
    default:
    break;
  }
}

/**
  * @brief  Configures the output of a timer operating in waveform mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2 
  * @param  pOutputCfg: pointer to the timer output configuration structure
  * @retval None
  */
void HRTIM_WaveformOutputConfig(HRTIM_TypeDef * HRTIM_,
                                                uint32_t TimerIdx,
                                                uint32_t Output,
                                                HRTIM_OutputCfgTypeDef * pOutputCfg)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, Output));
  assert_param(IS_HRTIM_OUTPUTPOLARITY(pOutputCfg->Polarity));
  assert_param(IS_HRTIM_OUTPUTIDLESTATE(pOutputCfg->IdleState));
  assert_param(IS_HRTIM_OUTPUTIDLEMODE(pOutputCfg->IdleMode));
  assert_param(IS_HRTIM_OUTPUTFAULTSTATE(pOutputCfg->FaultState));
  assert_param(IS_HRTIM_OUTPUTCHOPPERMODE(pOutputCfg->ChopperModeEnable));
  assert_param(IS_HRTIM_OUTPUTBURSTMODEENTRY(pOutputCfg->BurstModeEntryDelayed));

  /* Configure the timer output */
  HRTIM_OutputConfig(HRTIM_, TimerIdx, Output, pOutputCfg);  
}

/**
  * @brief  Configures the event filtering capabilities of a timer (blanking, windowing) 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  Event: external event for which timer event filtering must be configured
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
  * @param  pTimerEventFilteringCfg: pointer to the timer event filtering configuration structure
  * @retval None
  */
void HRTIM_TimerEventFilteringConfig(HRTIM_TypeDef * HRTIMx,
                                                      uint32_t TimerIdx,
                                                      uint32_t Event,
                                                      HRTIM_TimerEventFilteringCfgTypeDef* pTimerEventFilteringCfg)
{
  uint32_t HRTIM_eefr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_EVENT(Event));
  assert_param(IS_HRTIM_TIMEVENTFILTER(pTimerEventFilteringCfg->Filter));
  assert_param(IS_HRTIM_TIMEVENTLATCH(pTimerEventFilteringCfg->Latch));

  /* Configure timer event filtering capabilities */
  switch (Event)
  {
    case HRTIM_TIMEVENTFILTER_NONE:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1 = 0;
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2 = 0;
    }
    break;
    case HRTIM_EVENT_1:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1;
      HRTIM_eefr &= ~(HRTIM_EEFR1_EE1FLTR | HRTIM_EEFR1_EE1LTCH);
      HRTIM_eefr |= (pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_2:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1;
      HRTIM_eefr &= ~(HRTIM_EEFR1_EE2FLTR | HRTIM_EEFR1_EE2LTCH);
      HRTIM_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 6);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_3:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1;
      HRTIM_eefr &= ~(HRTIM_EEFR1_EE3FLTR | HRTIM_EEFR1_EE3LTCH);
      HRTIM_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 12);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_4:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1;
      HRTIM_eefr &= ~(HRTIM_EEFR1_EE4FLTR | HRTIM_EEFR1_EE4LTCH);
      HRTIM_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 18);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_5:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1;
      HRTIM_eefr &= ~(HRTIM_EEFR1_EE5FLTR | HRTIM_EEFR1_EE5LTCH);
      HRTIM_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 24);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR1 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_6:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2;
      HRTIM_eefr &= ~(HRTIM_EEFR2_EE6FLTR | HRTIM_EEFR2_EE6LTCH);
      HRTIM_eefr |= (pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_7:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2;
      HRTIM_eefr &= ~(HRTIM_EEFR2_EE7FLTR | HRTIM_EEFR2_EE7LTCH);
      HRTIM_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 6);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_8:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2;
      HRTIM_eefr &= ~(HRTIM_EEFR2_EE8FLTR | HRTIM_EEFR2_EE8LTCH);
      HRTIM_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 12);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_9:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2;
      HRTIM_eefr &= ~(HRTIM_EEFR2_EE9FLTR | HRTIM_EEFR2_EE9LTCH);
      HRTIM_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 18);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2 = HRTIM_eefr;
    }
    break;
    case HRTIM_EVENT_10:
    {
      HRTIM_eefr = HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2;
      HRTIM_eefr &= ~(HRTIM_EEFR2_EE10FLTR | HRTIM_EEFR2_EE10LTCH);
      HRTIM_eefr |= ((pTimerEventFilteringCfg->Filter | pTimerEventFilteringCfg->Latch) << 24);
      HRTIMx->HRTIM_TIMERx[TimerIdx].EEFxR2 = HRTIM_eefr;
    }
    break;
    default:
    break;
  }
}

/**
  * @brief  Configures the dead time insertion feature for a timer 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  pDeadTimeCfg: pointer to the dead time insertion configuration structure
  * @retval None
  */
void HRTIM_DeadTimeConfig(HRTIM_TypeDef * HRTIMx,
                                           uint32_t TimerIdx,
                                           HRTIM_DeadTimeCfgTypeDef* pDeadTimeCfg)
{
  uint32_t HRTIM_dtr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_TIMDEADTIME_RISINGSIGN(pDeadTimeCfg->RisingSign));
  assert_param(IS_HRTIM_TIMDEADTIME_RISINGLOCK(pDeadTimeCfg->RisingLock));
  assert_param(IS_HRTIM_TIMDEADTIME_RISINGSIGNLOCK(pDeadTimeCfg->RisingSignLock));
  assert_param(IS_HRTIM_TIMDEADTIME_FALLINGSIGN(pDeadTimeCfg->FallingSign));
  assert_param(IS_HRTIM_TIMDEADTIME_FALLINGLOCK(pDeadTimeCfg->FallingLock));
  assert_param(IS_HRTIM_TIMDEADTIME_FALLINGSIGNLOCK(pDeadTimeCfg->FallingSignLock));

  HRTIM_dtr = HRTIMx->HRTIM_TIMERx[TimerIdx].DTxR;
     
  /* Clear timer dead times configuration */
  HRTIM_dtr &= ~(HRTIM_DTR_DTR | HRTIM_DTR_SDTR | HRTIM_DTR_DTPRSC |
                 HRTIM_DTR_DTRSLK | HRTIM_DTR_DTRLK | HRTIM_DTR_SDTF |
                 HRTIM_DTR_SDTR | HRTIM_DTR_DTFSLK | HRTIM_DTR_DTFLK);
  
  /* Set timer dead times configuration */
  HRTIM_dtr |= (pDeadTimeCfg->Prescaler << 10);
  HRTIM_dtr |= pDeadTimeCfg->RisingValue;
  HRTIM_dtr |= pDeadTimeCfg->RisingSign;
  HRTIM_dtr |= pDeadTimeCfg->RisingSignLock;
  HRTIM_dtr |= pDeadTimeCfg->RisingLock;
  HRTIM_dtr |= (pDeadTimeCfg->FallingValue << 16);
  HRTIM_dtr |= pDeadTimeCfg->FallingSign;
  HRTIM_dtr |= pDeadTimeCfg->FallingSignLock;
  HRTIM_dtr |= pDeadTimeCfg->FallingLock;
    
  /* Update the HRTIMx registers */  
  HRTIMx->HRTIM_TIMERx[TimerIdx].DTxR = HRTIM_dtr;
}

/**
  * @brief  Configures the chopper mode feature for a timer 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  pChopperModeCfg: pointer to the chopper mode configuration structure
  * @retval None
  */
void HRTIM_ChopperModeConfig(HRTIM_TypeDef * HRTIMx,
                                              uint32_t TimerIdx,
                                              HRTIM_ChopperModeCfgTypeDef* pChopperModeCfg)
{
  uint32_t HRTIM_chpr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));

  HRTIM_chpr = HRTIMx->HRTIM_TIMERx[TimerIdx].CHPxR;
     
  /* Clear timer chopper mode configuration */
  HRTIM_chpr &= ~(HRTIM_CHPR_CARFRQ | HRTIM_CHPR_CARDTY | HRTIM_CHPR_STRPW);
  
  /* Set timer chopper mode configuration */
  HRTIM_chpr |= pChopperModeCfg->CarrierFreq;
  HRTIM_chpr |= (pChopperModeCfg->DutyCycle << 4);
  HRTIM_chpr |= (pChopperModeCfg->StartPulse << 7);
    
  /* Update the HRTIMx registers */  
  HRTIMx->HRTIM_TIMERx[TimerIdx].CHPxR = HRTIM_chpr;
}

/**
  * @brief  Configures the burst DMA controller for a timer 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
   *                  This parameter can be one of the following values:
 *                    @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E 
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
  * @retval None
  */
void HRTIM_BurstDMAConfig(HRTIM_TypeDef * HRTIMx,
                                           uint32_t TimerIdx,
                                           uint32_t RegistersToUpdate)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_BURSTDMA(TimerIdx, RegistersToUpdate));
  
  /* Set the burst DMA timer update register */
  switch (TimerIdx) 
  {
    case HRTIM_TIMERINDEX_TIMER_A:
    {
      HRTIMx->HRTIM_COMMON.BDTAUPR = RegistersToUpdate;
    }
    break;
    case HRTIM_TIMERINDEX_TIMER_B:
    {
      HRTIMx->HRTIM_COMMON.BDTBUPR = RegistersToUpdate;
    }
    break;
    case HRTIM_TIMERINDEX_TIMER_C:
    {
      HRTIMx->HRTIM_COMMON.BDTCUPR = RegistersToUpdate;
    }
    break;
    case HRTIM_TIMERINDEX_TIMER_D:
    {
      HRTIMx->HRTIM_COMMON.BDTDUPR = RegistersToUpdate;
    }
    break;
    case HRTIM_TIMERINDEX_TIMER_E:
    {
      HRTIMx->HRTIM_COMMON.BDTEUPR = RegistersToUpdate;
    }
    break;
    case HRTIM_TIMERINDEX_MASTER:
    {
      HRTIMx->HRTIM_COMMON.BDMUPDR = RegistersToUpdate;
    }
    break;
    default:
    break;
  }
}

/**
  * @brief  Configures the external input/output synchronization of the HRTIMx 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  pSynchroCfg: pointer to the input/output synchronization configuration structure
  * @retval None
  */
void HRTIM_SynchronizationConfig(HRTIM_TypeDef *HRTIMx, HRTIM_SynchroCfgTypeDef * pSynchroCfg)
{
  uint32_t HRTIM_mcr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_SYNCINPUTSOURCE(pSynchroCfg->SyncInputSource));
  assert_param(IS_HRTIM_SYNCOUTPUTSOURCE(pSynchroCfg->SyncOutputSource));
  assert_param(IS_HRTIM_SYNCOUTPUTPOLARITY(pSynchroCfg->SyncOutputPolarity));
    
  HRTIM_mcr = HRTIMx->HRTIM_MASTER.MCR;

  /* Set the synchronization input source */
  HRTIM_mcr &= ~(HRTIM_MCR_SYNC_IN);
  HRTIM_mcr |= pSynchroCfg->SyncInputSource;
  
  /* Set the event to be sent on the synchronization output */
  HRTIM_mcr &= ~(HRTIM_MCR_SYNC_SRC);
  HRTIM_mcr |= pSynchroCfg->SyncOutputSource;
  
  /* Set the polarity of the synchronization output */
  HRTIM_mcr &= ~(HRTIM_MCR_SYNC_OUT);
  HRTIM_mcr |= pSynchroCfg->SyncOutputPolarity;
  
  /* Update the HRTIMx registers */  
  HRTIMx->HRTIM_MASTER.MCR = HRTIM_mcr;
}

/**
  * @brief  Configures the burst mode feature of the HRTIMx 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  pBurstModeCfg: pointer to the burst mode configuration structure
  * @retval None
  */
void HRTIM_BurstModeConfig(HRTIM_TypeDef * HRTIMx,
                                            HRTIM_BurstModeCfgTypeDef* pBurstModeCfg)
{
  uint32_t HRTIM_bmcr;

  /* Check parameters */
  assert_param(IS_HRTIM_BURSTMODE(pBurstModeCfg->Mode));
  assert_param(IS_HRTIM_BURSTMODECLOCKSOURCE(pBurstModeCfg->ClockSource));
  assert_param(IS_HRTIM_HRTIM_BURSTMODEPRESCALER(pBurstModeCfg->Prescaler));
  assert_param(IS_HRTIM_BURSTMODEPRELOAD(pBurstModeCfg->PreloadEnable));
  
  HRTIM_bmcr = HRTIMx->HRTIM_COMMON.BMCR;

  /* Set the burst mode operating mode */
  HRTIM_bmcr &= ~(HRTIM_BMCR_BMOM);
  HRTIM_bmcr |= pBurstModeCfg->Mode;
  
  /* Set the burst mode clock source */
  HRTIM_bmcr &= ~(HRTIM_BMCR_BMCLK);
  HRTIM_bmcr |= pBurstModeCfg->ClockSource;
  
  /* Set the burst mode prescaler */
  HRTIM_bmcr &= ~(HRTIM_BMCR_BMPSC);
  HRTIM_bmcr |= pBurstModeCfg->Prescaler;
 
  /* Enable/disable burst mode registers preload */
  HRTIM_bmcr &= ~(HRTIM_BMCR_BMPREN);
  HRTIM_bmcr |= pBurstModeCfg->PreloadEnable;
 
  /* Set the burst mode trigger */
  HRTIMx->HRTIM_COMMON.BMTRGR = pBurstModeCfg->Trigger;
  
  /* Set the burst mode compare value */
  HRTIMx->HRTIM_COMMON.BMCMPR = pBurstModeCfg->IdleDuration;
  
  /* Set the burst mode period */
  HRTIMx->HRTIM_COMMON.BMPER = pBurstModeCfg->Period;
  
  /* Update the HRTIMx registers */  
  HRTIMx->HRTIM_COMMON.BMCR = HRTIM_bmcr;
}

/**
  * @brief  Configures the conditioning of an external event
  * @param  HRTIMx: pointer to HRTIMx peripheral
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
  * @retval None
  */
void HRTIM_EventConfig(HRTIM_TypeDef * HRTIMx,
                                        uint32_t Event,
                                        HRTIM_EventCfgTypeDef* pEventCfg)
{
  /* Check parameters */
  assert_param(IS_HRTIM_EVENTSRC(pEventCfg->Source)); 
  assert_param(IS_HRTIM_EVENTPOLARITY(pEventCfg->Polarity)); 
  assert_param(IS_HRTIM_EVENTSENSITIVITY(pEventCfg->Sensitivity)); 
  assert_param(IS_HRTIM_EVENTFASTMODE(pEventCfg->FastMode)); 
  assert_param(IS_HRTIM_EVENTFILTER(pEventCfg->Filter)); 

  /* Configure the event channel */
  HRTIM_ExternalEventConfig(HRTIMx, Event, pEventCfg);
 
}

/**
  * @brief  Configures the external event conditioning block prescaler
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  Prescaler: Prescaler value
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_EVENTPRESCALER_DIV1: fEEVS=fHRTIMx
  *                    @arg HRTIM_EVENTPRESCALER_DIV2: fEEVS=fHRTIMx / 2
  *                    @arg HRTIM_EVENTPRESCALER_DIV4: fEEVS=fHRTIMx / 4
  *                    @arg HRTIM_EVENTPRESCALER_DIV8: fEEVS=fHRTIMx / 8
  * @retval None
  */
void HRTIM_EventPrescalerConfig(HRTIM_TypeDef * HRTIMx,
                                                 uint32_t Prescaler)
{
  uint32_t HRTIM_eecr3;

  /* Check parameters */
  assert_param(IS_HRTIM_EVENTPRESCALER(Prescaler));

  /* Set the external event prescaler */
  HRTIM_eecr3 = HRTIMx->HRTIM_COMMON.EECR3;
  HRTIM_eecr3 &= ~(HRTIM_EECR3_EEVSD);
  HRTIM_eecr3 |= Prescaler;
  
  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_COMMON.EECR3 = HRTIM_eecr3;
}
 
/**
  * @brief  Configures the conditioning of fault input
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  Fault: fault input to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_FAULT_1: Fault input 1
  *                    @arg HRTIM_FAULT_2: Fault input 2
  *                    @arg HRTIM_FAULT_3: Fault input 3
  *                    @arg HRTIM_FAULT_4: Fault input 4
  *                    @arg HRTIM_FAULT_5: Fault input 5
  * @param  pFaultCfg: pointer to the fault conditioning configuration structure
  * @retval None
  */
void HRTIM_FaultConfig(HRTIM_TypeDef * HRTIMx,
                                        HRTIM_FaultCfgTypeDef* pFaultCfg,
                                        uint32_t Fault)
{
  uint32_t HRTIM_fltinr1;
  uint32_t HRTIM_fltinr2;

  /* Check parameters */
  assert_param(IS_HRTIM_FAULT(Fault));
  assert_param(IS_HRTIM_FAULTSOURCE(pFaultCfg->Source));
  assert_param(IS_HRTIM_FAULTPOLARITY(pFaultCfg->Polarity));
  assert_param(IS_HRTIM_FAULTFILTER(pFaultCfg->Filter));
  assert_param(IS_HRTIM_FAULTLOCK(pFaultCfg->Lock));

  /* Configure fault channel */
  HRTIM_fltinr1 = HRTIMx->HRTIM_COMMON.FLTINxR1;
  HRTIM_fltinr2 = HRTIMx->HRTIM_COMMON.FLTINxR2;
  
  switch (Fault)
  {
    case HRTIM_FAULT_1:
    {
      HRTIM_fltinr1 &= ~(HRTIM_FLTINR1_FLT1P | HRTIM_FLTINR1_FLT1SRC | HRTIM_FLTINR1_FLT1F | HRTIM_FLTINR1_FLT1LCK);
      HRTIM_fltinr1 |= pFaultCfg->Polarity;
      HRTIM_fltinr1 |= pFaultCfg->Source;
      HRTIM_fltinr1 |= pFaultCfg->Filter;
      HRTIM_fltinr1 |= pFaultCfg->Lock;
    }
    break;
    case HRTIM_FAULT_2:
    {
      HRTIM_fltinr1 &= ~(HRTIM_FLTINR1_FLT2P | HRTIM_FLTINR1_FLT2SRC | HRTIM_FLTINR1_FLT2F | HRTIM_FLTINR1_FLT2LCK);
      HRTIM_fltinr1 |= (pFaultCfg->Polarity << 8);
      HRTIM_fltinr1 |= (pFaultCfg->Source << 8);
      HRTIM_fltinr1 |= (pFaultCfg->Filter << 8);
      HRTIM_fltinr1 |= (pFaultCfg->Lock << 8);
    }
    break;
    case HRTIM_FAULT_3:
    {
      HRTIM_fltinr1 &= ~(HRTIM_FLTINR1_FLT3P | HRTIM_FLTINR1_FLT3SRC | HRTIM_FLTINR1_FLT3F | HRTIM_FLTINR1_FLT3LCK);
      HRTIM_fltinr1 |= (pFaultCfg->Polarity << 16);
      HRTIM_fltinr1 |= (pFaultCfg->Source << 16);
      HRTIM_fltinr1 |= (pFaultCfg->Filter << 16);
      HRTIM_fltinr1 |= (pFaultCfg->Lock << 16);
    }
    break;
    case HRTIM_FAULT_4:
    {
      HRTIM_fltinr1 &= ~(HRTIM_FLTINR1_FLT4P | HRTIM_FLTINR1_FLT4SRC | HRTIM_FLTINR1_FLT4F | HRTIM_FLTINR1_FLT4LCK);
      HRTIM_fltinr1 |= (pFaultCfg->Polarity << 24);
      HRTIM_fltinr1 |= (pFaultCfg->Source << 24);
      HRTIM_fltinr1 |= (pFaultCfg->Filter << 24);
      HRTIM_fltinr1 |= (pFaultCfg->Lock << 24);
    }
    break;
    case HRTIM_FAULT_5:
    {
      HRTIM_fltinr2 &= ~(HRTIM_FLTINR2_FLT5P | HRTIM_FLTINR2_FLT5SRC | HRTIM_FLTINR2_FLT5F | HRTIM_FLTINR2_FLT5LCK);
      HRTIM_fltinr2 |= pFaultCfg->Polarity;
      HRTIM_fltinr2 |= pFaultCfg->Source;
      HRTIM_fltinr2 |= pFaultCfg->Filter;
      HRTIM_fltinr2 |= pFaultCfg->Lock;
    }
    break;
    default:
    break;
  }

  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_COMMON.FLTINxR1 = HRTIM_fltinr1;
  HRTIMx->HRTIM_COMMON.FLTINxR2 = HRTIM_fltinr2;
}

/**
  * @brief  Configures the fault conditioning block prescaler
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  Prescaler: Prescaler value
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_FAULTPRESCALER_DIV1: fFLTS=fHRTIMx
  *                    @arg HRTIM_FAULTPRESCALER_DIV2: fFLTS=fHRTIMx / 2
  *                    @arg HRTIM_FAULTPRESCALER_DIV4: fFLTS=fHRTIMx / 4
  *                    @arg HRTIM_FAULTPRESCALER_DIV8: fFLTS=fHRTIMx / 8
  * @retval None
  */
void HRTIM_FaultPrescalerConfig(HRTIM_TypeDef * HRTIMx,
                                                 uint32_t Prescaler)
{
  uint32_t HRTIM_fltinr2;

  /* Check parameters */
  assert_param(IS_HRTIM_FAULTPRESCALER(Prescaler));
  
  /* Set the external event prescaler */
  HRTIM_fltinr2 = HRTIMx->HRTIM_COMMON.FLTINxR2;
  HRTIM_fltinr2 &= ~(HRTIM_FLTINR2_FLTSD);
  HRTIM_fltinr2 |= Prescaler;
  
  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_COMMON.FLTINxR2 = HRTIM_fltinr2;
}

/**
  * @brief  Enables or disables the HRTIMx Fault mode.
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  Fault: fault input to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_FAULT_1: Fault input 1
  *                    @arg HRTIM_FAULT_2: Fault input 2
  *                    @arg HRTIM_FAULT_3: Fault input 3
  *                    @arg HRTIM_FAULT_4: Fault input 4
  *                    @arg HRTIM_FAULT_5: Fault input 5
  * @param  Enable: Fault mode controller enabling
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_FAULT_ENABLED: Fault mode enabled
  *                    @arg HRTIM_FAULT_DISABLED: Fault mode disabled
  * @retval None
  */
void HRTIM_FaultModeCtl(HRTIM_TypeDef * HRTIMx, uint32_t Fault, uint32_t Enable)
{
  uint32_t HRTIM_fltinr1;
  uint32_t HRTIM_fltinr2;
  
  /* Check parameters */
  assert_param(IS_HRTIM_FAULT(Fault));
  assert_param(IS_HRTIM_FAULTCTL(Enable));

  /* Configure fault channel */
  HRTIM_fltinr1 = HRTIMx->HRTIM_COMMON.FLTINxR1;
  HRTIM_fltinr2 = HRTIMx->HRTIM_COMMON.FLTINxR2;
  
  switch (Fault)
  {
    case HRTIM_FAULT_1:
    {
      HRTIM_fltinr1 &= ~HRTIM_FLTINR1_FLT1E;
      HRTIM_fltinr1 |= Enable;
    }
    break;
    case HRTIM_FAULT_2:
    {
      HRTIM_fltinr1 &= ~HRTIM_FLTINR1_FLT2E;
      HRTIM_fltinr1 |= (Enable<< 8);
    }
    break;
    case HRTIM_FAULT_3:
    {
      HRTIM_fltinr1 &= ~HRTIM_FLTINR1_FLT3E;
      HRTIM_fltinr1 |= (Enable << 16);
    }
    break;
    case HRTIM_FAULT_4:
    {
      HRTIM_fltinr1 &= ~HRTIM_FLTINR1_FLT4E; 
      HRTIM_fltinr1 |= (Enable << 24);
    }
    break;
    case HRTIM_FAULT_5:
    {
      HRTIM_fltinr2 &= ~HRTIM_FLTINR2_FLT5E;
      HRTIM_fltinr2 |= Enable;
    }
    break;
    default:
    break;
  }

  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_COMMON.FLTINxR1 = HRTIM_fltinr1;
  HRTIMx->HRTIM_COMMON.FLTINxR2 = HRTIM_fltinr2;
}                              

/**
  * @brief  Configures both the ADC trigger register update source and the ADC
  *         trigger source.
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  ADC trigger: ADC trigger to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_ADCTRIGGER_1: ADC trigger 1
  *                    @arg HRTIM_ADCTRIGGER_2: ADC trigger 2
  *                    @arg HRTIM_ADCTRIGGER_3: ADC trigger 3
  *                    @arg HRTIM_ADCTRIGGER_4: ADC trigger 4
  * @param  pADCTriggerCfg: pointer to the ADC trigger configuration structure
  * @retval None
  */
void HRTIM_ADCTriggerConfig(HRTIM_TypeDef * HRTIMx,
                                             uint32_t ADCTrigger,
                                             HRTIM_ADCTriggerCfgTypeDef* pADCTriggerCfg)
{
  uint32_t HRTIM_cr1;
  
  /* Check parameters */
  assert_param(IS_HRTIM_ADCTRIGGER(ADCTrigger));
  assert_param(IS_HRTIM_ADCTRIGGERUPDATE(pADCTriggerCfg->UpdateSource));

  /* Set the ADC trigger update source */
  HRTIM_cr1 = HRTIMx->HRTIM_COMMON.CR1;
  
  switch (ADCTrigger)
  {
    case HRTIM_ADCTRIGGER_1:
    {
      HRTIM_cr1 &= ~(HRTIM_CR1_ADC1USRC);
      HRTIM_cr1 |= pADCTriggerCfg->UpdateSource;
      
      /* Set the ADC trigger 1 source */
      HRTIMx->HRTIM_COMMON.ADC1R = pADCTriggerCfg->Trigger;
    }
    break;
    case HRTIM_ADCTRIGGER_2:
    {
      HRTIM_cr1 &= ~(HRTIM_CR1_ADC2USRC);
      HRTIM_cr1 |= (pADCTriggerCfg->UpdateSource << 3); 

      /* Set the ADC trigger 2 source */
      HRTIMx->HRTIM_COMMON.ADC2R = pADCTriggerCfg->Trigger;
    }
    break;
    case HRTIM_ADCTRIGGER_3:
    {
      HRTIM_cr1 &= ~(HRTIM_CR1_ADC3USRC);
      HRTIM_cr1 |= (pADCTriggerCfg->UpdateSource << 6); 
      
      /* Set the ADC trigger 3 source */
      HRTIMx->HRTIM_COMMON.ADC3R = pADCTriggerCfg->Trigger;
    }
    case HRTIM_ADCTRIGGER_4:
    {
      HRTIM_cr1 &= ~(HRTIM_CR1_ADC4USRC);
      HRTIM_cr1 |= (pADCTriggerCfg->UpdateSource << 9); 
      
      /* Set the ADC trigger 4 source */
      HRTIMx->HRTIM_COMMON.ADC4R = pADCTriggerCfg->Trigger;
    }
    break;
    default:
    break;
  }
  
  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_COMMON.CR1 = HRTIM_cr1;
}


/**
  * @brief  Enables or disables the HRTIMx burst mode controller.
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  Enable: Burst mode controller enabling
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_BURSTMODECTL_ENABLED: Burst mode enabled
  *                    @arg HRTIM_BURSTMODECTL_DISABLED: Burst mode disabled
  * @retval None
  */
void HRTIM_BurstModeCtl(HRTIM_TypeDef * HRTIMx, uint32_t Enable)
{
  uint32_t HRTIM_bmcr;
  
  /* Check parameters */
  assert_param(IS_HRTIM_BURSTMODECTL(Enable));
  
  /* Enable/Disable the burst mode controller */
  HRTIM_bmcr = HRTIMx->HRTIM_COMMON.BMCR;
  HRTIM_bmcr &= ~(HRTIM_BMCR_BME);
  HRTIM_bmcr |= Enable;
  
  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_COMMON.BMCR = HRTIM_bmcr;
}

/**
  * @brief  Triggers a software capture on the designed capture unit
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  CaptureUnit: Capture unit to trig
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval None
  * @note The 'software capture' bit in the capure configuration register is
  *       automatically reset by hardware
  */
void HRTIM_SoftwareCapture(HRTIM_TypeDef * HRTIMx,
                                            uint32_t TimerIdx,
                                            uint32_t CaptureUnit)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));
  assert_param(IS_HRTIM_CAPTUREUNIT(CaptureUnit));
  
  /* Force a software capture on concerned capture unit */
  switch (CaptureUnit)
  {
    case HRTIM_CAPTUREUNIT_1:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].CPT1xCR |= HRTIM_CPT1CR_SWCPT;
    }
    break;
    case HRTIM_CAPTUREUNIT_2:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].CPT2xCR |= HRTIM_CPT2CR_SWCPT;
    }
    break;
    default:
    break;
  }
}

/**
  * @brief  Triggers the update of the registers of one or several timers
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimersToUpdate: timers concerned with the software register update
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMERUPDATE_MASTER 
  *                   @arg HRTIM_TIMERUPDATE_A 
  *                   @arg HRTIM_TIMERUPDATE_B 
  *                   @arg HRTIM_TIMERUPDATE_C 
  *                   @arg HRTIM_TIMERUPDATE_D 
  *                   @arg HRTIM_TIMERUPDATE_E 
  * @retval None
  * @note The 'software update' bits in the HRTIMx control register 2 register are
  *       automatically reset by hardware
  */
void HRTIM_SoftwareUpdate(HRTIM_TypeDef * HRTIMx,
                                           uint32_t TimersToUpdate)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMERUPDATE(TimersToUpdate));
  
  /* Force timer(s) registers update */
  HRTIMx->HRTIM_COMMON.CR2 |= TimersToUpdate;
  
}

/**
  * @brief  Triggers the reset of one or several timers
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimersToUpdate: timers concerned with the software counter reset
  *                   This parameter can be any combination of the following values:
  *                   @arg HRTIM_TIMER_MASTER 
  *                   @arg HRTIM_TIMER_A 
  *                   @arg HRTIM_TIMER_B 
  *                   @arg HRTIM_TIMER_C 
  *                   @arg HRTIM_TIMER_D 
  *                   @arg HRTIM_TIMER_E 
  * @retval None
  * @note The 'software reset' bits in the HRTIMx control register 2  are
  *       automatically reset by hardware
  */
void HRTIM_SoftwareReset(HRTIM_TypeDef * HRTIMx,
                                          uint32_t TimersToReset)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMERRESET(TimersToReset));
  
  /* Force timer(s) registers update */
  HRTIMx->HRTIM_COMMON.CR2 |= TimersToReset;
 
}

/**
  * @brief  Forces the timer output to its active or inactive state 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @param OutputLevel: indicates whether the output is forced to its active or inactive state
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUTLEVEL_ACTIVE: output is forced to its active state
  *                    @arg HRTIM_OUTPUTLEVEL_INACTIVE: output is forced to its inactive state
  * @retval None
  * @note The 'software set/reset trigger' bit in the output set/reset registers 
  *       is automatically reset by hardware
  */
void HRTIM_WaveformSetOutputLevel(HRTIM_TypeDef * HRTIMx,
                                                   uint32_t TimerIdx,
                                                   uint32_t Output,
                                                   uint32_t OutputLevel)
{
  /* Check parameters */
  assert_param(IS_HRTIM_TIMER_OUTPUT(TimerIdx, Output));
  assert_param(IS_HRTIM_OUTPUTLEVEL(OutputLevel));

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
        HRTIMx->HRTIM_TIMERx[TimerIdx].SETx1R |= HRTIM_SET1R_SST;
      }
      else
      {
        /* Force output to its inactive state */
        HRTIMx->HRTIM_TIMERx[TimerIdx].RSTx1R |= HRTIM_RST1R_SRT;
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
        HRTIMx->HRTIM_TIMERx[TimerIdx].SETx2R |= HRTIM_SET2R_SST;
      }
      else
      {
        /* Force output to its inactive state */
        HRTIMx->HRTIM_TIMERx[TimerIdx].RSTx2R |= HRTIM_RST2R_SRT;
      }
    }
    break;
    default:
    break;
  } 
}


/**
  * @}
  */

/** @defgroup HRTIM_Group4 Peripheral State methods 
 *  @brief   Peripheral State functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral State methods #####
 ===============================================================================  
    [..]
    This subsection permit to get in run-time the status of the peripheral 
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Returns actual value of the capture register of the designated capture unit 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  CaptureUnit: Capture unit to trig
  *                    This parameter can be one of the following values: 
  *                    @arg HRTIM_CAPTUREUNIT_1: Capture unit 1
  *                    @arg HRTIM_CAPTUREUNIT_2: Capture unit 2
  * @retval Captured value
  */
uint32_t HRTIM_GetCapturedValue(HRTIM_TypeDef * HRTIMx,
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
      captured_value = HRTIMx->HRTIM_TIMERx[TimerIdx].CPT1xR;
    }
    break;
    case HRTIM_CAPTUREUNIT_2:
    {
      captured_value = HRTIMx->HRTIM_TIMERx[TimerIdx].CPT2xR;
    }
    break;
    default:
    break;
  }
  
  return captured_value; 
}

/**
  * @brief  Returns actual level (active or inactive) of the designated output 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval Output level
  * @note Returned output level is taken before the output stage (chopper, 
  *        polarity).
  */
uint32_t HRTIM_WaveformGetOutputLevel(HRTIM_TypeDef * HRTIMx,
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
      if ((HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxISR & HRTIM_TIMISR_O1CPY) != RESET)
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
      if ((HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxISR & HRTIM_TIMISR_O2CPY) != RESET)
      {
        output_level = HRTIM_OUTPUTLEVEL_ACTIVE;
      }
      else
      {
        output_level = HRTIM_OUTPUTLEVEL_INACTIVE;
      }
    }
    break;
    default:
    break;
  }
  
  return output_level; 
}

/**
  * @brief  Returns actual state (RUN, IDLE, FAULT) of the designated output 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TE1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TE2: Timer E - Output 2
  * @retval Output state
  */
uint32_t HRTIM_WaveformGetOutputState(HRTIM_TypeDef * HRTIMx,
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
    default:
    break;
  }
  
  if ((HRTIMx->HRTIM_COMMON.OENR & output_bit) != RESET)
  {
    /* Output is enabled: output in RUN state (whatever ouput disable status is)*/
    output_state = HRTIM_OUTPUTSTATE_RUN;
  }
  else
  {
    if ((HRTIMx->HRTIM_COMMON.ODSR & output_bit) != RESET)
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
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @param  Output: Timer output
  *                    This parameter can be one of the following values:
  *                    @arg HRTIM_OUTPUT_TA1: Timer A - Output 1
  *                    @arg HRTIM_OUTPUT_TA2: Timer A - Output 2
  *                    @arg HRTIM_OUTPUT_TB1: Timer B - Output 1
  *                    @arg HRTIM_OUTPUT_TB2: Timer B - Output 2
  *                    @arg HRTIM_OUTPUT_TC1: Timer C - Output 1
  *                    @arg HRTIM_OUTPUT_TC2: Timer C - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer D - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer D - Output 2
  *                    @arg HRTIM_OUTPUT_TD1: Timer E - Output 1
  *                    @arg HRTIM_OUTPUT_TD2: Timer E - Output 2
  * @retval Delayed protection status 
  */
uint32_t HRTIM_GetDelayedProtectionStatus(HRTIM_TypeDef * HRTIMx,
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
      if ((HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxISR & HRTIM_TIMISR_O1STAT) != RESET)
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
      if ((HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxISR & HRTIM_TIMISR_O2STAT) != RESET)
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
    default:
    break;
  }
  
  return delayed_protection_status;
}

/**
  * @brief  Returns the actual status (active or inactive) of the burst mode controller 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @retval Burst mode controller status 
  */
uint32_t HRTIM_GetBurstStatus(HRTIM_TypeDef * HRTIMx)
{
  uint32_t burst_mode_status;

  /* Read burst mode status */
  burst_mode_status = (HRTIMx->HRTIM_COMMON.BMCR & HRTIM_BMCR_BMSTAT);
  
  return burst_mode_status; 
}

/**
  * @brief  Indicates on which output the signal is currently active (when the
  *         push pull mode is enabled)
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @retval Burst mode controller status 
  */
uint32_t HRTIM_GetCurrentPushPullStatus(HRTIM_TypeDef * HRTIMx,
                                            uint32_t TimerIdx)
{
  uint32_t current_pushpull_status;

   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));

  /* Read current push pull status */
  current_pushpull_status = (HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxISR & HRTIM_TIMISR_CPPSTAT);
  
  return current_pushpull_status; 
}


/**
  * @brief  Indicates on which output the signal was applied, in push-pull mode
            balanced fault mode or delayed idle mode, when the protection was triggered
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E 
  * @retval Idle Push Pull Status 
  */
uint32_t HRTIM_GetIdlePushPullStatus(HRTIM_TypeDef * HRTIMx,
                                         uint32_t TimerIdx)
{
  uint32_t idle_pushpull_status;

   /* Check the parameters */
  assert_param(IS_HRTIM_TIMING_UNIT(TimerIdx));

  /* Read current push pull status */
  idle_pushpull_status = (HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxISR & HRTIM_TIMISR_IPPSTAT);
  
  return idle_pushpull_status; 
}

/**
  * @brief  Configures the master timer time base
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @retval None
  */
void  HRTIM_MasterBase_Config(HRTIM_TypeDef * HRTIMx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct)
{  
  /* Set the prescaler ratio */
  HRTIMx->HRTIM_MASTER.MCR &= (uint32_t) ~(HRTIM_MCR_CK_PSC);
  HRTIMx->HRTIM_MASTER.MCR  |= (uint32_t)HRTIM_BaseInitStruct->PrescalerRatio;
  
  /* Set the operating mode */
  HRTIMx->HRTIM_MASTER.MCR  &= (uint32_t) ~(HRTIM_MCR_CONT | HRTIM_MCR_RETRIG);
  HRTIMx->HRTIM_MASTER.MCR  |= (uint32_t)HRTIM_BaseInitStruct->Mode;
  
  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_MASTER.MPER = HRTIM_BaseInitStruct->Period;
  HRTIMx->HRTIM_MASTER.MREP = HRTIM_BaseInitStruct->RepetitionCounter;
}

/**
  * @brief  Configures timing unit (timer A to timer E) time base
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  * @retval None
  */
void HRTIM_TimingUnitBase_Config(HRTIM_TypeDef * HRTIMx, uint32_t TimerIdx, HRTIM_BaseInitTypeDef* HRTIM_BaseInitStruct)
{   
  /* Set the prescaler ratio */
  HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR &= (uint32_t) ~(HRTIM_TIMCR_CK_PSC);
  HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR |= (uint32_t)HRTIM_BaseInitStruct->PrescalerRatio;

  /* Set the operating mode */
  HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR &= (uint32_t) ~(HRTIM_TIMCR_CONT | HRTIM_TIMCR_RETRIG);
  HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR |= (uint32_t)HRTIM_BaseInitStruct->Mode;
  
  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_TIMERx[TimerIdx].PERxR = HRTIM_BaseInitStruct->Period;
  HRTIMx->HRTIM_TIMERx[TimerIdx].REPxR = HRTIM_BaseInitStruct->RepetitionCounter;
}

/**
  * @brief  Configures the master timer in waveform mode
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  * @param  pTimerInit: pointer to the timer initialization data structure
  * @retval None
  */
void  HRTIM_MasterWaveform_Config(HRTIM_TypeDef * HRTIMx, 
                                HRTIM_TimerInitTypeDef * pTimerInit)
{
  uint32_t HRTIM_mcr;
  uint32_t HRTIM_bmcr;
  
  /* Configure master timer */
  HRTIM_mcr = HRTIMx->HRTIM_MASTER.MCR;
  HRTIM_bmcr = HRTIMx->HRTIM_COMMON.BMCR;
  
  /* Enable/Disable the half mode */
  HRTIM_mcr &= ~(HRTIM_MCR_HALF);
  HRTIM_mcr |= pTimerInit->HalfModeEnable;
  
  /* Enable/Disable the timer start upon synchronization event reception */
  HRTIM_mcr &= ~(HRTIM_MCR_SYNCSTRTM);
  HRTIM_mcr |= pTimerInit->StartOnSync;
 
  /* Enable/Disable the timer reset upon synchronization event reception */
  HRTIM_mcr &= ~(HRTIM_MCR_SYNCRSTM);
  HRTIM_mcr |= pTimerInit->ResetOnSync;
  
  /* Enable/Disable the DAC synchronization event generation */
  HRTIM_mcr &= ~(HRTIM_MCR_DACSYNC);
  HRTIM_mcr |= pTimerInit->DACSynchro;
  
  /* Enable/Disable preload mechanism for timer registers */
  HRTIM_mcr &= ~(HRTIM_MCR_PREEN);
  HRTIM_mcr |= pTimerInit->PreloadEnable;
  
  /* Master timer registers update handling */
  HRTIM_mcr &= ~(HRTIM_MCR_BRSTDMA);
  HRTIM_mcr |= (pTimerInit->UpdateGating << 2);
  
  /* Enable/Disable registers update on repetition */
  HRTIM_mcr &= ~(HRTIM_MCR_MREPU);
  HRTIM_mcr |= pTimerInit->RepetitionUpdate;
  
  /* Set the timer burst mode */
  HRTIM_bmcr &= ~(HRTIM_BMCR_MTBM);
  HRTIM_bmcr |= pTimerInit->BurstMode;

  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_MASTER.MCR  = HRTIM_mcr;
  HRTIMx->HRTIM_COMMON.BMCR = HRTIM_bmcr;
  
}

/**
  * @brief  Configures timing unit (timer A to timer E) in waveform mode 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  * @param  pTimerInit: pointer to the timer initialization data structure
  * @retval None
  */
void HRTIM_TimingUnitWaveform_Config(HRTIM_TypeDef * HRTIMx, 
                                    uint32_t TimerIdx, 
                                    HRTIM_TimerInitTypeDef * pTimerInit)
{
  uint32_t HRTIM_timcr;
  uint32_t HRTIM_bmcr;
  
  /* Configure timing unit */
  HRTIM_timcr = HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR;
  HRTIM_bmcr = HRTIMx->HRTIM_COMMON.BMCR;
  
  /* Enable/Disable the half mode */
  HRTIM_timcr &= ~(HRTIM_TIMCR_HALF);
  HRTIM_timcr |= pTimerInit->HalfModeEnable;
  
  /* Enable/Disable the timer start upon synchronization event reception */
  HRTIM_timcr &= ~(HRTIM_TIMCR_SYNCSTRT);
  HRTIM_timcr |= pTimerInit->StartOnSync;
 
  /* Enable/Disable the timer reset upon synchronization event reception */
  HRTIM_timcr &= ~(HRTIM_TIMCR_SYNCRST);
  HRTIM_timcr |= pTimerInit->ResetOnSync;
  
  /* Enable/Disable the DAC synchronization event generation */
  HRTIM_timcr &= ~(HRTIM_TIMCR_DACSYNC);
  HRTIM_timcr |= pTimerInit->DACSynchro;
  
  /* Enable/Disable preload mechanism for timer registers */
  HRTIM_timcr &= ~(HRTIM_TIMCR_PREEN);
  HRTIM_timcr |= pTimerInit->PreloadEnable;
  
  /* Timing unit registers update handling */
  HRTIM_timcr &= ~(HRTIM_TIMCR_UPDGAT);
  HRTIM_timcr |= pTimerInit->UpdateGating;
  
  /* Enable/Disable registers update on repetition */
  HRTIM_timcr &= ~(HRTIM_TIMCR_TREPU);
  if (pTimerInit->RepetitionUpdate == HRTIM_UPDATEONREPETITION_ENABLED)
  {
    HRTIM_timcr |= HRTIM_TIMCR_TREPU;
  }

  /* Set the timer burst mode */
  switch (TimerIdx)
  {
    case HRTIM_TIMERINDEX_TIMER_A:
    {
      HRTIM_bmcr &= ~(HRTIM_BMCR_TABM);
      HRTIM_bmcr |= ( pTimerInit->BurstMode << 1);
    }
    break;
    case HRTIM_TIMERINDEX_TIMER_B:
    {
      HRTIM_bmcr &= ~(HRTIM_BMCR_TBBM);
      HRTIM_bmcr |= ( pTimerInit->BurstMode << 2);
    }
    break;
    case HRTIM_TIMERINDEX_TIMER_C:
    {
      HRTIM_bmcr &= ~(HRTIM_BMCR_TCBM);
      HRTIM_bmcr |= ( pTimerInit->BurstMode << 3);
    }
    break;
    case HRTIM_TIMERINDEX_TIMER_D:
    {
      HRTIM_bmcr &= ~(HRTIM_BMCR_TDBM);
      HRTIM_bmcr |= ( pTimerInit->BurstMode << 4);
    }
    break;
    case HRTIM_TIMERINDEX_TIMER_E:
    {
      HRTIM_bmcr &= ~(HRTIM_BMCR_TEBM);
      HRTIM_bmcr |= ( pTimerInit->BurstMode << 5);
    }
    break;
    default:
    break;
  }
  
  /* Update the HRTIMx registers */
  HRTIMx->HRTIM_TIMERx[TimerIdx].TIMxCR = HRTIM_timcr;
  HRTIMx->HRTIM_COMMON.BMCR = HRTIM_bmcr;
}

/**
  * @brief  Configures a compare unit 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  * @param  CompareUnit: Compare unit identifier
  * @param  pCompareCfg: pointer to the compare unit configuration data structure
  * @retval None
  */
void  HRTIM_CompareUnitConfig(HRTIM_TypeDef * HRTIMx,
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
        HRTIMx->HRTIM_MASTER.MCMP1R = pCompareCfg->CompareValue;
      }
      break;
      case HRTIM_COMPAREUNIT_2:
      {
        HRTIMx->HRTIM_MASTER.MCMP2R = pCompareCfg->CompareValue;
      }
      break;
      case HRTIM_COMPAREUNIT_3:
      {
        HRTIMx->HRTIM_MASTER.MCMP3R = pCompareCfg->CompareValue;
      }
      break;
      case HRTIM_COMPAREUNIT_4:
      {
        HRTIMx->HRTIM_MASTER.MCMP4R = pCompareCfg->CompareValue;
      }
      break;
      default:
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
        HRTIMx->HRTIM_TIMERx[TimerIdx].CMP1xR = pCompareCfg->CompareValue;
      }
      break;
      case HRTIM_COMPAREUNIT_2:
      {
        HRTIMx->HRTIM_TIMERx[TimerIdx].CMP2xR = pCompareCfg->CompareValue;
      }
      break;
      case HRTIM_COMPAREUNIT_3:
      {
        HRTIMx->HRTIM_TIMERx[TimerIdx].CMP3xR = pCompareCfg->CompareValue;
      }
      break;
      case HRTIM_COMPAREUNIT_4:
      {
        HRTIMx->HRTIM_TIMERx[TimerIdx].CMP4xR = pCompareCfg->CompareValue;
      }
      break;
      default:
      break;
    }
  }
}

/**
  * @brief  Configures a capture unit 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  * @param  CaptureUnit: Capture unit identifier
  * @param  pCaptureCfg: pointer to the compare unit configuration data structure
  * @retval None
  */
void HRTIM_CaptureUnitConfig(HRTIM_TypeDef * HRTIMx,
                             uint32_t TimerIdx,
                             uint32_t CaptureUnit,
                             uint32_t Event)
{
  uint32_t CaptureTrigger = HRTIM_CAPTURETRIGGER_EEV_1;
  
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
    default:
    break;  
    
  }  
  switch (CaptureUnit)
  {
    case HRTIM_CAPTUREUNIT_1:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].CPT1xCR = CaptureTrigger;
    }
    break;
    case HRTIM_CAPTUREUNIT_2:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].CPT2xCR = CaptureTrigger;
    }
    break;
    default:
    break;  
  }
}

/**
  * @brief  Configures the output of a timing unit 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  * @param  Output: timing unit output identifier
  * @param  pOutputCfg: pointer to the output configuration data structure
  * @retval None
  */
void  HRTIM_OutputConfig(HRTIM_TypeDef * HRTIMx,
                         uint32_t TimerIdx,
                         uint32_t Output,
                         HRTIM_OutputCfgTypeDef * pOutputCfg)
{
  uint32_t HRTIM_outr;
  uint32_t shift = 0;
  
  HRTIM_outr = HRTIMx->HRTIM_TIMERx[TimerIdx].OUTxR;
  
  switch (Output)
  {
    case HRTIM_OUTPUT_TA1:
    case HRTIM_OUTPUT_TB1:
    case HRTIM_OUTPUT_TC1:
    case HRTIM_OUTPUT_TD1:
    case HRTIM_OUTPUT_TE1:
    {
      /* Set the output set/reset crossbar */
      HRTIMx->HRTIM_TIMERx[TimerIdx].SETx1R = pOutputCfg->SetSource;
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTx1R = pOutputCfg->ResetSource;
      
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
      HRTIMx->HRTIM_TIMERx[TimerIdx].SETx2R = pOutputCfg->SetSource;
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTx2R = pOutputCfg->ResetSource;

      shift = 16;
    }
    break;
    default:
    break;
  }
  
  /* Clear output config */
  HRTIM_outr &= ~((HRTIM_OUTR_POL1 |
                   HRTIM_OUTR_IDLM1 |
                   HRTIM_OUTR_IDLES1|
                   HRTIM_OUTR_FAULT1|
                   HRTIM_OUTR_CHP1 |
                   HRTIM_OUTR_DIDL1)  << shift);
  
  /* Set the polarity */
  HRTIM_outr |= (pOutputCfg->Polarity << shift);
  
  /* Set the IDLE mode */
  HRTIM_outr |= (pOutputCfg->IdleMode << shift);
  
  /* Set the IDLE state */
  HRTIM_outr |= (pOutputCfg->IdleState << shift);
  
  /* Set the FAULT state */
  HRTIM_outr |= (pOutputCfg->FaultState << shift);
  
  /* Set the chopper mode */
  HRTIM_outr |= (pOutputCfg->ChopperModeEnable << shift);

  /* Set the burst mode entry mode */
  HRTIM_outr |= (pOutputCfg->BurstModeEntryDelayed << shift);
  
  /* Update HRTIMx register */
  HRTIMx->HRTIM_TIMERx[TimerIdx].OUTxR = HRTIM_outr;
}

/**
  * @brief  Configures an external event channel 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  Event: Event channel identifier
  * @param  pEventCfg: pointer to the event channel configuration data structure
  * @retval None
  */
static void HRTIM_ExternalEventConfig(HRTIM_TypeDef * HRTIMx,
                              uint32_t Event,
                              HRTIM_EventCfgTypeDef *pEventCfg)
{
  uint32_t hrtim_eecr1;
  uint32_t hrtim_eecr2;
  uint32_t hrtim_eecr3;

  /* Configure external event channel */
  hrtim_eecr1 = HRTIMx->HRTIM_COMMON.EECR1;
  hrtim_eecr2 = HRTIMx->HRTIM_COMMON.EECR2;
  hrtim_eecr3 = HRTIMx->HRTIM_COMMON.EECR3;
  
  switch (Event)
  {
    case HRTIM_EVENT_1:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE1SRC | HRTIM_EECR1_EE1POL | HRTIM_EECR1_EE1SNS | HRTIM_EECR1_EE1FAST);
      hrtim_eecr1 |= pEventCfg->Source;
      hrtim_eecr1 |= pEventCfg->Polarity;
      hrtim_eecr1 |= pEventCfg->Sensitivity;
      /* Update the HRTIM registers (all bit fields but EE1FAST bit) */
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE1FAST bit) */
      hrtim_eecr1 |= pEventCfg->FastMode;
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
    }
    break;
    case HRTIM_EVENT_2:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE2SRC | HRTIM_EECR1_EE2POL | HRTIM_EECR1_EE2SNS | HRTIM_EECR1_EE2FAST);
      hrtim_eecr1 |= (pEventCfg->Source << 6);
      hrtim_eecr1 |= (pEventCfg->Polarity << 6);
      hrtim_eecr1 |= (pEventCfg->Sensitivity << 6);
      /* Update the HRTIM registers (all bit fields but EE2FAST bit) */
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE2FAST bit) */
      hrtim_eecr1 |= (pEventCfg->FastMode << 6);
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
    }
    break;
    case HRTIM_EVENT_3:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE3SRC | HRTIM_EECR1_EE3POL | HRTIM_EECR1_EE3SNS | HRTIM_EECR1_EE3FAST);
      hrtim_eecr1 |= (pEventCfg->Source << 12);
      hrtim_eecr1 |= (pEventCfg->Polarity << 12);
      hrtim_eecr1 |= (pEventCfg->Sensitivity << 12);
      /* Update the HRTIM registers (all bit fields but EE3FAST bit) */
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE3FAST bit) */
      hrtim_eecr1 |= (pEventCfg->FastMode << 12);
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
    }
    break;
    case HRTIM_EVENT_4:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE4SRC | HRTIM_EECR1_EE4POL | HRTIM_EECR1_EE4SNS | HRTIM_EECR1_EE4FAST);
      hrtim_eecr1 |= (pEventCfg->Source << 18);
      hrtim_eecr1 |= (pEventCfg->Polarity << 18);
      hrtim_eecr1 |= (pEventCfg->Sensitivity << 18);
      /* Update the HRTIM registers (all bit fields but EE4FAST bit) */
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE4FAST bit) */
      hrtim_eecr1 |= (pEventCfg->FastMode << 18);
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
    }
    break;
    case HRTIM_EVENT_5:
    {
      hrtim_eecr1 &= ~(HRTIM_EECR1_EE5SRC | HRTIM_EECR1_EE5POL | HRTIM_EECR1_EE5SNS | HRTIM_EECR1_EE5FAST);
      hrtim_eecr1 |= (pEventCfg->Source << 24);
      hrtim_eecr1 |= (pEventCfg->Polarity << 24);
      hrtim_eecr1 |= (pEventCfg->Sensitivity << 24);
      /* Update the HRTIM registers (all bit fields but EE5FAST bit) */
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
      /* Update the HRTIM registers (EE5FAST bit) */
      hrtim_eecr1 |= (pEventCfg->FastMode << 24);
      HRTIMx->HRTIM_COMMON.EECR1 = hrtim_eecr1;
    }
    break;
    case HRTIM_EVENT_6:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE6SRC | HRTIM_EECR2_EE6POL | HRTIM_EECR2_EE6SNS);
      hrtim_eecr2 |= pEventCfg->Source;
      hrtim_eecr2 |= pEventCfg->Polarity;
      hrtim_eecr2 |= pEventCfg->Sensitivity;
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE6F);
      hrtim_eecr3 |= pEventCfg->Filter;
      /* Update the HRTIM registers */
      HRTIMx->HRTIM_COMMON.EECR2 = hrtim_eecr2;
      HRTIMx->HRTIM_COMMON.EECR3 = hrtim_eecr3;
    }
    break;
    case HRTIM_EVENT_7:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE7SRC | HRTIM_EECR2_EE7POL | HRTIM_EECR2_EE7SNS);
      hrtim_eecr2 |= (pEventCfg->Source << 6);
      hrtim_eecr2 |= (pEventCfg->Polarity << 6);
      hrtim_eecr2 |= (pEventCfg->Sensitivity << 6);
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE7F);
      hrtim_eecr3 |= (pEventCfg->Filter << 6);
      /* Update the HRTIM registers */
      HRTIMx->HRTIM_COMMON.EECR2 = hrtim_eecr2;
      HRTIMx->HRTIM_COMMON.EECR3 = hrtim_eecr3;
    }
    break;
    case HRTIM_EVENT_8:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE8SRC | HRTIM_EECR2_EE8POL | HRTIM_EECR2_EE8SNS);
      hrtim_eecr2 |= (pEventCfg->Source << 12);
      hrtim_eecr2 |= (pEventCfg->Polarity << 12);
      hrtim_eecr2 |= (pEventCfg->Sensitivity << 12);
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE8F);
      hrtim_eecr3 |= (pEventCfg->Filter << 12);
      /* Update the HRTIM registers */
      HRTIMx->HRTIM_COMMON.EECR2 = hrtim_eecr2;
      HRTIMx->HRTIM_COMMON.EECR3 = hrtim_eecr3;
    }
    break;
    case HRTIM_EVENT_9:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE9SRC | HRTIM_EECR2_EE9POL | HRTIM_EECR2_EE9SNS);
      hrtim_eecr2 |= (pEventCfg->Source << 18);
      hrtim_eecr2 |= (pEventCfg->Polarity << 18);
      hrtim_eecr2 |= (pEventCfg->Sensitivity << 18);
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE9F);
      hrtim_eecr3 |= (pEventCfg->Filter << 18);
      /* Update the HRTIM registers */
      HRTIMx->HRTIM_COMMON.EECR2 = hrtim_eecr2;
      HRTIMx->HRTIM_COMMON.EECR3 = hrtim_eecr3;
    }
    break;
    case HRTIM_EVENT_10:
    {
      hrtim_eecr2 &= ~(HRTIM_EECR2_EE10SRC | HRTIM_EECR2_EE10POL | HRTIM_EECR2_EE10SNS);
      hrtim_eecr2 |= (pEventCfg->Source << 24);
      hrtim_eecr2 |= (pEventCfg->Polarity << 24);
      hrtim_eecr2 |= (pEventCfg->Sensitivity << 24);
      hrtim_eecr3 &= ~(HRTIM_EECR3_EE10F);
      hrtim_eecr3 |= (pEventCfg->Filter << 24);
      /* Update the HRTIM registers */
      HRTIMx->HRTIM_COMMON.EECR2 = hrtim_eecr2;
      HRTIMx->HRTIM_COMMON.EECR3 = hrtim_eecr3;
    }
    break;
    default:
    break;
  }
}

/**
  * @brief  Configures the timer counter reset 
  * @param  HRTIMx: pointer to HRTIMx peripheral
  * @param  TimerIdx: Timer index
  * @param  Event: Event channel identifier
  * @retval None
  */
void HRTIM_TIM_ResetConfig(HRTIM_TypeDef * HRTIMx,
                           uint32_t TimerIdx,
                           uint32_t Event)
{
  switch (Event)
  {
    case HRTIM_EVENT_1:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_1;
    }
    break;
    case HRTIM_EVENT_2:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_2;
    }
    break;
    case HRTIM_EVENT_3:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_3;
    }
    break;
    case HRTIM_EVENT_4:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_4;
    }
    break;
    case HRTIM_EVENT_5:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_5;
    }
    break;
    case HRTIM_EVENT_6:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_6;
    }
    break;
    case HRTIM_EVENT_7:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_7;
    }
    break;
    case HRTIM_EVENT_8:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_8;
    }
    break;
    case HRTIM_EVENT_9:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_9;
    }
    break;
    case HRTIM_EVENT_10:
    {
      HRTIMx->HRTIM_TIMERx[TimerIdx].RSTxR = HRTIM_TIMRESETTRIGGER_EEV_10;
    }
    break;
    default:
    break;
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



