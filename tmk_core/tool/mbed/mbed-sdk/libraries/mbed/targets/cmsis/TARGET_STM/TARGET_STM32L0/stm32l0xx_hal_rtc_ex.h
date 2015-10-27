/**
  ******************************************************************************
  * @file    stm32l0xx_hal_rtc_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of RTC HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_HAL_RTC_EX_H
#define __STM32L0xx_HAL_RTC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup RTCEx RTCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** @defgroup RTCEx_Exported_Types RTC Extended Exported Types
  * @{
  */

/**
  * @brief  RTC Tamper structure definition
  */
typedef struct
{
  uint32_t Tamper;                      /*!< Specifies the Tamper Pin.
                                             This parameter can be a value of @ref  RTCEx_Tamper_Pins_Definitions */

  uint32_t Interrupt;                   /*!< Specifies the Tamper Interrupt.
                                             This parameter can be a value of @ref  RTCEx_Tamper_Interrupt_Definitions */

  uint32_t Trigger;                     /*!< Specifies the Tamper Trigger.
                                             This parameter can be a value of @ref  RTCEx_Tamper_Trigger_Definitions */

  uint32_t NoErase;                     /*!< Specifies the Tamper no erase mode.
                                             This parameter can be a value of @ref  RTCEx_Tamper_EraseBackUp_Definitions */

  uint32_t MaskFlag;                     /*!< Specifies the Tamper Flag masking.
                                             This parameter can be a value of @ref RTCEx_Tamper_MaskFlag_Definitions   */

  uint32_t Filter;                      /*!< Specifies the RTC Filter Tamper.
                                             This parameter can be a value of @ref RTCEx_Tamper_Filter_Definitions */

  uint32_t SamplingFrequency;           /*!< Specifies the sampling frequency.
                                             This parameter can be a value of @ref RTCEx_Tamper_Sampling_Frequencies_Definitions */

  uint32_t PrechargeDuration;           /*!< Specifies the Precharge Duration .
                                             This parameter can be a value of @ref RTCEx_Tamper_Pin_Precharge_Duration_Definitions */

  uint32_t TamperPullUp;                /*!< Specifies the Tamper PullUp .
                                             This parameter can be a value of @ref RTCEx_Tamper_Pull_UP_Definitions */

  uint32_t TimeStampOnTamperDetection;  /*!< Specifies the TimeStampOnTamperDetection.
                                             This parameter can be a value of @ref RTCEx_Tamper_TimeStampOnTamperDetection_Definitions */
}RTC_TamperTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RTCEx_Exported_Constants RTC Extended Exported Constants
  * @{
  */


/** @defgroup RTCEx_Interrupts_Definitions RTC Extended Interrupts Definitions
  * @{
  */
#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
  defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx)
    
#define RTC_IT_TAMP3                      RTC_TAMPCR_TAMP3IE
    
#endif /* (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
    * (STM32L073xx) || (STM32L072xx) || (STM32L071xx)
    */
/**
  * @}
  */

    
/** @defgroup RTCEx_Flags_Definitions RTC Extended Flags Definitions
  * @{
  */
#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx)
      
#define RTC_FLAG_TAMP3F                    RTC_ISR_TAMP3F
      
#endif /* (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
        * (STM32L073xx) || (STM32L072xx) || (STM32L071xx)
      */
      
/**
  * @}
  */    
      
/** @defgroup RTCEx_Backup_Registers_Definitions RTC Extended Backup Registers Definition
  * @{
  */
#define RTC_BKP_DR0                       ((uint32_t)0x00000000)
#define RTC_BKP_DR1                       ((uint32_t)0x00000001)
#define RTC_BKP_DR2                       ((uint32_t)0x00000002)
#define RTC_BKP_DR3                       ((uint32_t)0x00000003)
#define RTC_BKP_DR4                       ((uint32_t)0x00000004)

#define IS_RTC_BKP(__BKP__)               (((__BKP__) == RTC_BKP_DR0) || \
                                           ((__BKP__) == RTC_BKP_DR1) || \
                                           ((__BKP__) == RTC_BKP_DR2) || \
                                           ((__BKP__) == RTC_BKP_DR3) || \
                                           ((__BKP__) == RTC_BKP_DR4))
/**
  * @}
  */
  
/** @defgroup RTC_Mask_Definition RTC Mask Definition
  * @{
  */
  
/* Masks Definition */

#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx)

#define RTC_FLAGS_MASK          ((uint32_t) (RTC_FLAG_RECALPF | RTC_FLAG_TAMP3F | RTC_FLAG_TAMP2F | \
                                             RTC_FLAG_TAMP1F| RTC_FLAG_TSOVF | RTC_FLAG_TSF       | \
                                             RTC_FLAG_WUTF | RTC_FLAG_ALRBF | RTC_FLAG_ALRAF      | \
                                             RTC_FLAG_INIT | RTC_FLAG_INITF | RTC_FLAG_RSF        | \
                                             RTC_FLAG_INITS | RTC_FLAG_SHPF | RTC_FLAG_WUTWF      | \
                                             RTC_FLAG_ALRBWF | RTC_FLAG_ALRAWF))

#define RTC_TAMPCR_TAMPXE     ((uint32_t) (RTC_TAMPCR_TAMP3E | RTC_TAMPCR_TAMP2E | RTC_TAMPCR_TAMP1E))

#else

#define RTC_FLAGS_MASK          ((uint32_t) (RTC_FLAG_RECALPF | RTC_FLAG_TAMP2F | RTC_FLAG_TAMP1F| \
                                             RTC_FLAG_TSOVF | RTC_FLAG_TSF | RTC_FLAG_WUTF       | \
                                             RTC_FLAG_ALRBF | RTC_FLAG_ALRAF | RTC_FLAG_INIT     | \
                                             RTC_FLAG_INITF | RTC_FLAG_RSF | RTC_FLAG_INITS      | \
                                             RTC_FLAG_SHPF | RTC_FLAG_WUTWF |RTC_FLAG_ALRBWF     | \
                                             RTC_FLAG_ALRAWF))

#define RTC_TAMPCR_TAMPXE     ((uint32_t) (RTC_TAMPCR_TAMP2E | RTC_TAMPCR_TAMP1E))

#endif /* (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
        * (STM32L073xx) || (STM32L072xx) || (STM32L071xx)
        */
/**
  * @}
  */
  
/** @defgroup RTCEx_Time_Stamp_Edges_definitions RTC Extended Time Stamp Edges definition
  * @{
  */ 
#define RTC_TIMESTAMPEDGE_RISING        ((uint32_t)0x00000000)
#define RTC_TIMESTAMPEDGE_FALLING       RTC_CR_TSEDGE

#define IS_TIMESTAMP_EDGE(__EDGE__)     (((__EDGE__) == RTC_TIMESTAMPEDGE_RISING) || \
                                         ((__EDGE__) == RTC_TIMESTAMPEDGE_FALLING))
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pins_Definitions RTC Extended Tamper Pins Definition
  * @{
  */

#define RTC_TAMPER_1                    RTC_TAMPCR_TAMP1E
#define RTC_TAMPER_2                    RTC_TAMPCR_TAMP2E

#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx)

#define RTC_TAMPER_3                    RTC_TAMPCR_TAMP3E

#endif /* (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
        * (STM32L073xx) || (STM32L072xx) || (STM32L071xx)
        */

#define  IS_RTC_TAMPER(__TAMPER__) ((((__TAMPER__) & ((uint32_t)(0xFFFFFFFF ^ RTC_TAMPCR_TAMPXE))) == 0x00) && ((__TAMPER__) != (uint32_t)RESET))

/**
  * @}
  */


/** @defgroup RTCEx_Tamper_Interrupt_Definitions RTC Extended Tamper Interrupt Definitions
  * @{
  */

#define RTC_TAMPER1_INTERRUPT                RTC_TAMPCR_TAMP1IE
#define RTC_TAMPER2_INTERRUPT                RTC_TAMPCR_TAMP2IE
#define RTC_ALL_TAMPER_INTERRUPT             RTC_TAMPCR_TAMPIE

#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx)

#define RTC_TAMPER3_INTERRUPT                RTC_TAMPCR_TAMP3IE
#define IS_RTC_TAMPER_INTERRUPT(__INTERRUPT__)  (((__INTERRUPT__) == RTC_TAMPER1_INTERRUPT)    || \
                                                 ((__INTERRUPT__) == RTC_TAMPER2_INTERRUPT)    || \
                                                 ((__INTERRUPT__) == RTC_TAMPER3_INTERRUPT)    || \
                                                 ((__INTERRUPT__) == RTC_ALL_TAMPER_INTERRUPT ))

#else

#define IS_RTC_TAMPER_INTERRUPT(__INTERRUPT__) (((__INTERRUPT__) == RTC_TAMPER1_INTERRUPT)  || \
                                                ((__INTERRUPT__) == RTC_TAMPER2_INTERRUPT)  || \
                                                ((__INTERRUPT__) == RTC_ALL_TAMPER_INTERRUPT ))

#endif /* (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
        * (STM32L073xx) || (STM32L072xx) || (STM32L071xx)
        */

/**
  * @}
  */

/** @defgroup RTCEx_TimeStamp_Pin_Selections RTC Extended TimeStamp Pin Selection
  * @{
  */
#define RTC_TIMESTAMPPIN_PC13              ((uint32_t)0x00000000)

#define IS_RTC_TIMESTAMP_PIN(__PIN__) (((__PIN__) == RTC_TIMESTAMPPIN_PC13))
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Trigger_Definitions RTC Extended Tamper Trigger Definition
  * @{
  */
#define RTC_TAMPERTRIGGER_RISINGEDGE       ((uint32_t)0x00000000)
#define RTC_TAMPERTRIGGER_FALLINGEDGE      RTC_TAMPCR_TAMP1TRG
#define RTC_TAMPERTRIGGER_LOWLEVEL         RTC_TAMPERTRIGGER_RISINGEDGE
#define RTC_TAMPERTRIGGER_HIGHLEVEL        RTC_TAMPERTRIGGER_FALLINGEDGE

#define  IS_RTC_TAMPER_TRIGGER(__TRIGGER__) (((__TRIGGER__) == RTC_TAMPERTRIGGER_RISINGEDGE)  || \
                                        ((__TRIGGER__) == RTC_TAMPERTRIGGER_FALLINGEDGE) || \
                                        ((__TRIGGER__) == RTC_TAMPERTRIGGER_LOWLEVEL)    || \
                                        ((__TRIGGER__) == RTC_TAMPERTRIGGER_HIGHLEVEL))

/**
  * @}
  */

/** @defgroup RTCEx_Tamper_EraseBackUp_Definitions RTC Extended Tamper EraseBackUp Definitions
* @{
*/
#define RTC_TAMPER_ERASE_BACKUP_ENABLE               ((uint32_t)0x00000000)
#define RTC_TAMPER_ERASE_BACKUP_DISABLE              RTC_TAMPCR_TAMP1NOERASE

#define IS_RTC_TAMPER_ERASE_MODE(__MODE__)              (((__MODE__) == RTC_TAMPER_ERASE_BACKUP_ENABLE) || \
                                                     ((__MODE__) == RTC_TAMPER_ERASE_BACKUP_DISABLE))
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_MaskFlag_Definitions RTC Extended Tamper MaskFlag Definitions
* @{
*/
#define RTC_TAMPERMASK_FLAG_DISABLE               ((uint32_t)0x00000000)
#define RTC_TAMPERMASK_FLAG_ENABLE                  RTC_TAMPCR_TAMP1MF

#define IS_RTC_TAMPER_MASKFLAG_STATE(__STATE__)        (((__STATE__) == RTC_TAMPERMASK_FLAG_ENABLE ) || \
                                                    ((__STATE__) == RTC_TAMPERMASK_FLAG_DISABLE))
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Filter_Definitions RTC Extended Tamper Filter Definitions
  * @{
  */
#define RTC_TAMPERFILTER_DISABLE   ((uint32_t)0x00000000)  /*!< Tamper filter is disabled */

#define RTC_TAMPERFILTER_2SAMPLE   RTC_TAMPCR_TAMPFLT_0    /*!< Tamper is activated after 2
                                                                consecutive samples at the active level */
#define RTC_TAMPERFILTER_4SAMPLE   RTC_TAMPCR_TAMPFLT_1    /*!< Tamper is activated after 4
                                                                consecutive samples at the active level */
#define RTC_TAMPERFILTER_8SAMPLE   RTC_TAMPCR_TAMPFLT      /*!< Tamper is activated after 8
                                                                consecutive samples at the active leve. */

#define IS_RTC_TAMPER_FILTER(__FILTER__)  (((__FILTER__) == RTC_TAMPERFILTER_DISABLE) || \
                                       ((__FILTER__) == RTC_TAMPERFILTER_2SAMPLE) || \
                                       ((__FILTER__) == RTC_TAMPERFILTER_4SAMPLE) || \
                                       ((__FILTER__) == RTC_TAMPERFILTER_8SAMPLE))
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Sampling_Frequencies_Definitions RTC Extended Tamper Sampling Frequencies Definitions
  * @{
  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768  ((uint32_t)0x00000000)                                         /*!< Each of the tamper inputs are sampled
                                                                                                                    with a frequency =  RTCCLK / 32768 */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV16384  RTC_TAMPCR_TAMPFREQ_0                                          /*!< Each of the tamper inputs are sampled
                                                                                                                    with a frequency =  RTCCLK / 16384 */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV8192   RTC_TAMPCR_TAMPFREQ_1                                          /*!< Each of the tamper inputs are sampled
                                                                                                                    with a frequency =  RTCCLK / 8192  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV4096   ((uint32_t) (RTC_TAMPCR_TAMPFREQ_0 | RTC_TAMPCR_TAMPFREQ_1))   /*!< Each of the tamper inputs are sampled
                                                                                                                    with a frequency =  RTCCLK / 4096  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV2048   RTC_TAMPCR_TAMPFREQ_2                                          /*!< Each of the tamper inputs are sampled
                                                                                                                    with a frequency =  RTCCLK / 2048  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV1024   ((uint32_t) (RTC_TAMPCR_TAMPFREQ_0 | RTC_TAMPCR_TAMPFREQ_2))   /*!< Each of the tamper inputs are sampled
                                                                                                                    with a frequency =  RTCCLK / 1024  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV512    ((uint32_t) (RTC_TAMPCR_TAMPFREQ_1 | RTC_TAMPCR_TAMPFREQ_2))   /*!< Each of the tamper inputs are sampled
                                                                                                                    with a frequency =  RTCCLK / 512   */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV256    ((uint32_t) (RTC_TAMPCR_TAMPFREQ_0 | RTC_TAMPCR_TAMPFREQ_1 | \
                                                 RTC_TAMPCR_TAMPFREQ_2))                                       /*!< Each of the tamper inputs are sampled
                                                                                                                    with a frequency =  RTCCLK / 256   */

#define IS_RTC_TAMPER_SAMPLING_FREQ(__FREQ__) (((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768)|| \
                                           ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV16384)|| \
                                           ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV8192) || \
                                           ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV4096) || \
                                           ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV2048) || \
                                           ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV1024) || \
                                           ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV512)  || \
                                           ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV256))
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pin_Precharge_Duration_Definitions RTC Extended Tamper Pin Precharge Duration Definitions
  * @{
  */
#define RTC_TAMPERPRECHARGEDURATION_1RTCCLK  ((uint32_t)0x00000000)                                     /*!< Tamper pins are pre-charged before
                                                                                                            sampling during 1 RTCCLK cycle  */
#define RTC_TAMPERPRECHARGEDURATION_2RTCCLK  RTC_TAMPCR_TAMPPRCH_0                                      /*!< Tamper pins are pre-charged before
                                                                                                             sampling during 2 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_4RTCCLK  RTC_TAMPCR_TAMPPRCH_1                                      /*!< Tamper pins are pre-charged before
                                                                                                             sampling during 4 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_8RTCCLK ((uint32_t)(RTC_TAMPCR_TAMPPRCH_0 | RTC_TAMPCR_TAMPPRCH_1)) /*!< Tamper pins are pre-charged before
                                                                                                             sampling during 8 RTCCLK cycles */

#define IS_RTC_TAMPER_PRECHARGE_DURATION(__DURATION_) (((__DURATION_) == RTC_TAMPERPRECHARGEDURATION_1RTCCLK) || \
                                                   ((__DURATION_) == RTC_TAMPERPRECHARGEDURATION_2RTCCLK) || \
                                                   ((__DURATION_) == RTC_TAMPERPRECHARGEDURATION_4RTCCLK) || \
                                                   ((__DURATION_) == RTC_TAMPERPRECHARGEDURATION_8RTCCLK))
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_TimeStampOnTamperDetection_Definitions RTC Extended Tamper TimeStampOnTamperDetection Definitions
  * @{
  */
#define RTC_TIMESTAMPONTAMPERDETECTION_ENABLE  RTC_TAMPCR_TAMPTS       /*!< TimeStamp on Tamper Detection event saved        */
#define RTC_TIMESTAMPONTAMPERDETECTION_DISABLE ((uint32_t)0x00000000)  /*!< TimeStamp on Tamper Detection event is not saved */

#define IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(__DETECTION__) (((__DETECTION__) == RTC_TIMESTAMPONTAMPERDETECTION_ENABLE) || \
                                                              ((__DETECTION__) == RTC_TIMESTAMPONTAMPERDETECTION_DISABLE))
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pull_UP_Definitions RTC Extended Tamper Pull UP Definitions
  * @{
  */
#define RTC_TAMPER_PULLUP_ENABLE  ((uint32_t)0x00000000)  /*!< Tamper pins are pre-charged before sampling */
#define RTC_TAMPER_PULLUP_DISABLE  RTC_TAMPCR_TAMPPUDIS   /*!< Tamper pins pre-charge is disabled          */

#define IS_RTC_TAMPER_PULLUP_STATE(__STATE__) (((__STATE__) == RTC_TAMPER_PULLUP_ENABLE) || \
                                           ((__STATE__) == RTC_TAMPER_PULLUP_DISABLE))
/**
  * @}
  */

/** @defgroup RTCEx_Wakeup_Timer_Definitions RTC Extended Wakeup Timer Definitions
  * @{
  */
#define RTC_WAKEUPCLOCK_RTCCLK_DIV16        ((uint32_t)0x00000000)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV8         RTC_CR_WUCKSEL_0
#define RTC_WAKEUPCLOCK_RTCCLK_DIV4         RTC_CR_WUCKSEL_1
#define RTC_WAKEUPCLOCK_RTCCLK_DIV2         ((uint32_t) (RTC_CR_WUCKSEL_0 | RTC_CR_WUCKSEL_1))
#define RTC_WAKEUPCLOCK_CK_SPRE_16BITS      RTC_CR_WUCKSEL_2
#define RTC_WAKEUPCLOCK_CK_SPRE_17BITS      ((uint32_t) (RTC_CR_WUCKSEL_1 | RTC_CR_WUCKSEL_2))

#define IS_RTC_WAKEUP_CLOCK(__CLOCK__) (((__CLOCK__) == RTC_WAKEUPCLOCK_RTCCLK_DIV16)   || \
                                    ((__CLOCK__) == RTC_WAKEUPCLOCK_RTCCLK_DIV8)    || \
                                    ((__CLOCK__) == RTC_WAKEUPCLOCK_RTCCLK_DIV4)    || \
                                    ((__CLOCK__) == RTC_WAKEUPCLOCK_RTCCLK_DIV2)    || \
                                    ((__CLOCK__) == RTC_WAKEUPCLOCK_CK_SPRE_16BITS) || \
                                    ((__CLOCK__) == RTC_WAKEUPCLOCK_CK_SPRE_17BITS))

#define IS_RTC_WAKEUP_COUNTER(__COUNTER__)  ((__COUNTER__) <= RTC_WUTR_WUT)
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_period_Definitions RTC Extended Smooth calib period Definitions
  * @{
  */
#define RTC_SMOOTHCALIB_PERIOD_32SEC   ((uint32_t)0x00000000)  /*!< If RTCCLK = 32768 Hz, Smooth calibation
                                                                    period is 32s,  else 2exp20 RTCCLK pulses */
#define RTC_SMOOTHCALIB_PERIOD_16SEC   RTC_CAL_CALW16          /*!< If RTCCLK = 32768 Hz, Smooth calibation
                                                                    period is 16s, else 2exp19 RTCCLK pulses */
#define RTC_SMOOTHCALIB_PERIOD_8SEC    RTC_CAL_CALW8           /*!< If RTCCLK = 32768 Hz, Smooth calibation
                                                                    period is 8s, else 2exp18 RTCCLK pulses */

#define IS_RTC_SMOOTH_CALIB_PERIOD(__PERIOD__) (((__PERIOD__) == RTC_SMOOTHCALIB_PERIOD_32SEC) || \
                                                ((__PERIOD__) == RTC_SMOOTHCALIB_PERIOD_16SEC) || \
                                                ((__PERIOD__) == RTC_SMOOTHCALIB_PERIOD_8SEC))
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_Plus_pulses_Definitions RTC Extended Smooth calib Plus pulses Definitions
  * @{
  */
#define RTC_SMOOTHCALIB_PLUSPULSES_SET    RTC_CAL_CALP            /*!< The number of RTCCLK pulses added
                                                                       during a X -second window = Y - CALM[8:0]
                                                                       with Y = 512, 256, 128 when X = 32, 16, 8 */
#define RTC_SMOOTHCALIB_PLUSPULSES_RESET  ((uint32_t)0x00000000)  /*!< The number of RTCCLK pulses subbstited
                                                                       during a 32-second window = CALM[8:0] */

#define IS_RTC_SMOOTH_CALIB_PLUS(__PLUS__) (((__PLUS__) == RTC_SMOOTHCALIB_PLUSPULSES_SET) || \
                                            ((__PLUS__) == RTC_SMOOTHCALIB_PLUSPULSES_RESET))
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_Minus_pulses_Definitions RTC Extended Smooth calib Minus pulses Definitions
  * @{
  */
#define  IS_RTC_SMOOTH_CALIB_MINUS(__VALUE__) ((__VALUE__) <= RTC_CAL_CALM)
/**
  * @}
  */

/** @defgroup RTCEx_Add_1_Second_Parameter_Definition RTC Extended Add 1 Second Parameter Definitions
  * @{
  */
#define RTC_SHIFTADD1S_RESET      ((uint32_t)0x00000000)
#define RTC_SHIFTADD1S_SET        RTC_SHIFTR_ADD1S

#define IS_RTC_SHIFT_ADD1S(__SEL__) (((__SEL__) == RTC_SHIFTADD1S_RESET) || \
                                     ((__SEL__) == RTC_SHIFTADD1S_SET))
/**
  * @}
  */

/** @defgroup RTCEx_Substract_Fraction_Of_Second_Value RTC Extended Substract Fraction Of Second Value
  * @{
  */
#define IS_RTC_SHIFT_SUBFS(__FS__) ((__FS__) <= RTC_SHIFTR_SUBFS)
/**
  * @}
  */

 /** @defgroup RTCEx_Calib_Output_selection_Definitions RTC Extended Calib Output selection Definitions
  * @{
  */
#define RTC_CALIBOUTPUT_512HZ            ((uint32_t)0x00000000)
#define RTC_CALIBOUTPUT_1HZ              RTC_CR_COSEL

#define IS_RTC_CALIB_OUTPUT(__OUTPUT__)  (((__OUTPUT__) == RTC_CALIBOUTPUT_512HZ) || \
                                          ((__OUTPUT__) == RTC_CALIBOUTPUT_1HZ))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RTCEx_Exported_Macros RTC Extended Exported Macros
  * @{
  */

/**
  * @brief  Enable the RTC WakeUp Timer peripheral.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_ENABLE(__HANDLE__)                      ((__HANDLE__)->Instance->CR |= (RTC_CR_WUTE))

/**
  * @brief  Enable the RTC TimeStamp peripheral.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_ENABLE(__HANDLE__)                        ((__HANDLE__)->Instance->CR |= (RTC_CR_TSE))

/**
  * @brief  Disable the RTC WakeUp Timer peripheral.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_DISABLE(__HANDLE__)                     ((__HANDLE__)->Instance->CR &= ~(RTC_CR_WUTE))

/**
  * @brief  Disable the RTC TimeStamp peripheral.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_DISABLE(__HANDLE__)                       ((__HANDLE__)->Instance->CR &= ~(RTC_CR_TSE))

/**
  * @brief  Enable the RTC calibration output.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CALIBRATION_OUTPUT_ENABLE(__HANDLE__)               ((__HANDLE__)->Instance->CR |= (RTC_CR_COE))

/**
  * @brief  Disable the calibration output.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CALIBRATION_OUTPUT_DISABLE(__HANDLE__)              ((__HANDLE__)->Instance->CR &= ~(RTC_CR_COE))

/**
  * @brief  Enable the clock reference detection.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CLOCKREF_DETECTION_ENABLE(__HANDLE__)               ((__HANDLE__)->Instance->CR |= (RTC_CR_REFCKON))

/**
  * @brief  Disable the clock reference detection.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CLOCKREF_DETECTION_DISABLE(__HANDLE__)              ((__HANDLE__)->Instance->CR &= ~(RTC_CR_REFCKON))

/**
  * @brief  Enable the RTC TimeStamp interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC TimeStamp interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_TS: TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_ENABLE_IT(__HANDLE__, __INTERRUPT__)      ((__HANDLE__)->Instance->CR |= (__INTERRUPT__))

/**
  * @brief  Enable the RTC WakeUpTimer interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC WakeUpTimer interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_WUT: WakeUpTimer A interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_ENABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the RTC TimeStamp interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC TimeStamp interrupt sources to be enabled or disabled. 
  *         This parameter can be:
  *            @arg RTC_IT_TS: TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_DISABLE_IT(__HANDLE__, __INTERRUPT__)     ((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__))

/**
  * @brief  Disable the RTC WakeUpTimer interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC WakeUpTimer interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_WUT: WakeUpTimer A interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_DISABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Tamper interrupt has occurred or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Tamper interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg  RTC_IT_TAMP1
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT(__HANDLE__, __FLAG__)                 (((((__HANDLE__)->Instance->ISR) & ((__FLAG__)>> 4)) != RESET)? SET : RESET)

/**
  * @brief  Check whether the specified RTC WakeUpTimer interrupt has occurred or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC WakeUpTimer interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_WUT:  WakeUpTimer A interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_IT(__HANDLE__, __FLAG__)            (((((__HANDLE__)->Instance->ISR) & ((__FLAG__)>> 4)) != RESET)? SET : RESET)

/**
  * @brief  Check whether the specified RTC TimeStamp interrupt has occurred or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC TimeStamp interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_TS: TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_IT(__HANDLE__, __FLAG__)              (((((__HANDLE__)->Instance->ISR) & ((__FLAG__)>> 4)) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC TimeStamp's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC TimeStamp Flag sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_FLAG_TSF
  *            @arg RTC_FLAG_TSOVF
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_FLAG(__HANDLE__, __FLAG__)            (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC WakeUpTimer's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC WakeUpTimer Flag sources to be enabled or disabled.
  *          This parameter can be:
  *             @arg RTC_FLAG_WUTF
  *             @arg RTC_FLAG_WUTWF
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_FLAG(__HANDLE__, __FLAG__)          (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC Tamper's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Tamper Flag sources to be enabled or disabled.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP1F
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_FLAG(__HANDLE__, __FLAG__)               (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Get the selected RTC shift operation's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC shift operation Flag is pending or not.
  *          This parameter can be:
  *             @arg RTC_FLAG_SHPF
  * @retval None
  */
#define __HAL_RTC_SHIFT_GET_FLAG(__HANDLE__, __FLAG__)                (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Clear the RTC Time Stamp's pending flags.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Alarm Flag sources to be enabled or disabled.
  *          This parameter can be:
  *             @arg RTC_FLAG_TSF
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_CLEAR_FLAG(__HANDLE__, __FLAG__)          ((__HANDLE__)->Instance->ISR) = (~(((__FLAG__) | RTC_ISR_INIT)& RTC_FLAGS_MASK)|((__HANDLE__)->Instance->ISR & RTC_ISR_INIT))

/**
  * @brief  Clear the RTC Tamper's pending flags.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Tamper Flag sources to be enabled or disabled.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP1F
  * @retval None
  */
#define __HAL_RTC_TAMPER_CLEAR_FLAG(__HANDLE__, __FLAG__)             ((__HANDLE__)->Instance->ISR) = (~(((__FLAG__) | RTC_ISR_INIT)& RTC_FLAGS_MASK)|((__HANDLE__)->Instance->ISR & RTC_ISR_INIT))

/**
  * @brief  Clear the RTC Wake Up timer's pending flags.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Tamper Flag sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_FLAG_WUTF
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(__HANDLE__, __FLAG__)        ((__HANDLE__)->Instance->ISR) = (~(((__FLAG__) | RTC_ISR_INIT)& RTC_FLAGS_MASK)|((__HANDLE__)->Instance->ISR & RTC_ISR_INIT))

/* WAKE-UP TIMER EXTI */
/* ------------------ */
/**
  * @brief  Enable interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT()       (EXTI->IMR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_IT()      (EXTI->IMR &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  Enable event on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_EVENT()    (EXTI->EMR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable event on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_EVENT()   (EXTI->EMR &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  Enable falling edge trigger on the RTC WakeUp Timer associated Exti line. 
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_FALLING_EDGE()   (EXTI->FTSR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable falling edge trigger on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_FALLING_EDGE()  (EXTI->FTSR &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  Enable rising edge trigger on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE()    (EXTI->RTSR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable rising edge trigger on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_RISING_EDGE()   (EXTI->RTSR &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  Enable rising & falling edge trigger on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_FALLING_EDGE() __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE();__HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_FALLING_EDGE();

/**
  * @brief  Disable rising & falling edge trigger on the RTC WakeUp Timer associated Exti line.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_RISING_FALLING_EDGE() __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_RISING_EDGE();__HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_FALLING_EDGE();

/**
  * @brief Check whether the RTC WakeUp Timer associated Exti line interrupt flag is set or not.
  * @retval Line Status.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_GET_FLAG()              (EXTI->PR & RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief Clear the RTC WakeUp Timer associated Exti line flag.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG()            (EXTI->PR = RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief Generate a Software interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_GENERATE_SWIT()         (EXTI->SWIER |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)


/* TAMPER TIMESTAMP EXTI */
/* --------------------- */
/**
  * @brief  Enable interrupt on the RTC Tamper and Timestamp associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_IT()        (EXTI->IMR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Disable interrupt on the RTC Tamper and Timestamp associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_IT()       (EXTI->IMR &= ~(RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT))

/**
  * @brief  Enable event on the RTC Tamper and Timestamp associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_EVENT()    (EXTI->EMR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Disable event on the RTC Tamper and Timestamp associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_EVENT()   (EXTI->EMR &= ~(RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT))

/**
  * @brief  Enable falling edge trigger on the RTC Tamper and Timestamp associated Exti line. 
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_FALLING_EDGE()   (EXTI->FTSR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Disable falling edge trigger on the RTC Tamper and Timestamp associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_FALLING_EDGE()  (EXTI->FTSR &= ~(RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT))

/**
  * @brief  Enable rising edge trigger on the RTC Tamper and Timestamp associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_RISING_EDGE()    (EXTI->RTSR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Disable rising edge trigger on the RTC Tamper and Timestamp associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_RISING_EDGE()   (EXTI->RTSR &= ~(RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT))

/**
  * @brief  Enable rising & falling edge trigger on the RTC Tamper and Timestamp associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_RISING_FALLING_EDGE() __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_RISING_EDGE();__HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_FALLING_EDGE();

/**
  * @brief  Disable rising & falling edge trigger on the RTC Tamper and Timestamp associated Exti line.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_RISING_FALLING_EDGE() __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_RISING_EDGE();__HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_FALLING_EDGE();

/**
  * @brief Check whether the RTC Tamper and Timestamp associated Exti line interrupt flag is set or not.
  * @retval Line Status.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_GET_FLAG()         (EXTI->PR & RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief Clear the RTC Tamper and Timestamp associated Exti line flag.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_CLEAR_FLAG()       (EXTI->PR = RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief Generate a Software interrupt on the RTC Tamper and Timestamp associated Exti line
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_GENERATE_SWIT()    (EXTI->SWIER |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RTCEx_Exported_Functions RTC Extended Exported Functions
  * @{
  */

/** @defgroup RTCEx_Exported_Functions_Group1 Extended RTC TimeStamp and Tamper functions
 * @{
 */ 

/* RTC TimeStamp and Tamper functions *****************************************/
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp_IT(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_GetTimeStamp(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTimeStamp, RTC_DateTypeDef *sTimeStampDate, uint32_t Format);

HAL_StatusTypeDef HAL_RTCEx_SetTamper(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef* sTamper);
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef* sTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(RTC_HandleTypeDef *hrtc, uint32_t Tamper);
void              HAL_RTCEx_TamperTimeStampIRQHandler(RTC_HandleTypeDef *hrtc);

void              HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc);

#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx)

void              HAL_RTCEx_Tamper3EventCallback(RTC_HandleTypeDef *hrtc);

#endif /* (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
        * (STM32L073xx) || (STM32L072xx) || (STM32L071xx)
        */

void              HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTimeStampEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_PollForTamper1Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_PollForTamper2Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout);

#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx)

HAL_StatusTypeDef HAL_RTCEx_PollForTamper3Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout);

#endif /* (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
    * (STM32L073xx) || (STM32L072xx) || (STM32L071xx)
    */

/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group2 Extended RTC Wake-up functions
 * @{
 */ 

/* RTC Wake-up functions ******************************************************/
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock);
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock);
uint32_t HAL_RTCEx_DeactivateWakeUpTimer(RTC_HandleTypeDef *hrtc);
uint32_t HAL_RTCEx_GetWakeUpTimer(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_WakeUpTimerIRQHandler(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForWakeUpTimerEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group3 Extended Peripheral Control functions
 * @{
 */ 

/* Extended Control functions ************************************************/
void HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data);
uint32_t HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister);

HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef *hrtc, uint32_t SmoothCalibPeriod, uint32_t SmoothCalibPlusPulses, uint32_t SmouthCalibMinusPulsesValue);
HAL_StatusTypeDef HAL_RTCEx_SetSynchroShift(RTC_HandleTypeDef *hrtc, uint32_t ShiftAdd1S, uint32_t ShiftSubFS);
HAL_StatusTypeDef HAL_RTCEx_SetCalibrationOutPut(RTC_HandleTypeDef *hrtc, uint32_t CalibOutput);
HAL_StatusTypeDef HAL_RTCEx_DeactivateCalibrationOutPut(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_SetRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_EnableBypassShadow(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DisableBypassShadow(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */

/* Extended RTC features functions *******************************************/
/** @defgroup RTCEx_Exported_Functions_Group4 Extended features functions
 * @{
 */ 
void              HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc); 
HAL_StatusTypeDef HAL_RTCEx_PollForAlarmBEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);

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

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_RTC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

