/**
  ******************************************************************************
  * @file    stm32f0xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file of RCC HAL Extension module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_HAL_RCC_EX_H
#define __STM32F0xx_HAL_RCC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */

/**
  * @brief  RCC extended clocks structure definition  
  */
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) || \
    defined(STM32F030xC)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCC_USART1_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F030x6 || STM32F030x8 || STM32F031x6 || STM32F038xx ||
          STM32F030xC */

#if defined(STM32F070x6) || defined(STM32F070xB)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCC_USART1_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t UsbClockSelection;    /*!< USB clock source
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */                                      

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F070x6 || STM32F070xB */

#if defined(STM32F042x6) || defined(STM32F048xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCC_USART1_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t CecClockSelection;    /*!< HDMI CEC clock source
                                      This parameter can be a value of @ref RCCEx_CEC_Clock_Source */

  uint32_t UsbClockSelection;    /*!< USB clock source
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F042x6 || STM32F048xx */

#if defined(STM32F051x8) || defined(STM32F058xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCC_USART1_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t CecClockSelection;    /*!< HDMI CEC clock source
                                      This parameter can be a value of @ref RCCEx_CEC_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F051x8 || STM32F058xx */

#if defined(STM32F071xB)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCC_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCCEx_USART2_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t CecClockSelection;    /*!< HDMI CEC clock source
                                      This parameter can be a value of @ref RCCEx_CEC_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F071xB */

#if defined(STM32F072xB) || defined(STM32F078xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCC_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCCEx_USART2_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t CecClockSelection;    /*!< HDMI CEC clock source
                                      This parameter can be a value of @ref RCCEx_CEC_Clock_Source */

  uint32_t UsbClockSelection;    /*!< USB clock source
                                      This parameter can be a value of @ref RCCEx_USB_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F072xB || STM32F078xx */


#if defined(STM32F091xC) || defined(STM32F098xx)
typedef struct
{
  uint32_t PeriphClockSelection; /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;    /*!< Specifies RTC Clock Prescalers Selection 
                                      This parameter can be a value of @ref RCC_RTC_Clock_Source */

  uint32_t Usart1ClockSelection; /*!< USART1 clock source
                                      This parameter can be a value of @ref RCC_USART1_Clock_Source */

  uint32_t Usart2ClockSelection; /*!< USART2 clock source
                                      This parameter can be a value of @ref RCCEx_USART2_Clock_Source */

  uint32_t Usart3ClockSelection; /*!< USART3 clock source
                                      This parameter can be a value of @ref RCCEx_USART3_Clock_Source */

  uint32_t I2c1ClockSelection;   /*!< I2C1 clock source
                                      This parameter can be a value of @ref RCC_I2C1_Clock_Source */

  uint32_t CecClockSelection;    /*!< HDMI CEC clock source
                                      This parameter can be a value of @ref RCCEx_CEC_Clock_Source */

}RCC_PeriphCLKInitTypeDef;
#endif /* STM32F091xC || STM32F098xx */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

/** 
  * @brief RCC_CRS Init structure definition  
  */
typedef struct
{
  uint32_t Prescaler;             /*!< Specifies the division factor of the SYNC signal.
                                     This parameter can be a value of @ref RCCEx_CRS_SynchroDivider */

  uint32_t Source;                /*!< Specifies the SYNC signal source.
                                     This parameter can be a value of @ref RCCEx_CRS_SynchroSource */

  uint32_t Polarity;              /*!< Specifies the input polarity for the SYNC signal source.
                                     This parameter can be a value of @ref RCCEx_CRS_SynchroPolarity */

  uint32_t ReloadValue;           /*!< Specifies the value to be loaded in the frequency error counter with each SYNC event.
                                      It can be calculated in using macro __HAL_RCC_CRS_CALCULATE_RELOADVALUE(_FTARGET_, _FSYNC_)
                                     This parameter must be a number between 0 and 0xFFFF or a value of @ref RCCEx_CRS_ReloadValueDefault .*/

  uint32_t ErrorLimitValue;       /*!< Specifies the value to be used to evaluate the captured frequency error value.
                                     This parameter must be a number between 0 and 0xFF or a value of @ref RCCEx_CRS_ErrorLimitDefault */

  uint32_t HSI48CalibrationValue; /*!< Specifies a user-programmable trimming value to the HSI48 oscillator.
                                     This parameter must be a number between 0 and 0x3F or a value of @ref RCCEx_CRS_HSI48CalibrationDefault */
   
}RCC_CRSInitTypeDef;

/** 
  * @brief RCC_CRS Synchronization structure definition  
  */
typedef struct
{
  uint32_t ReloadValue;           /*!< Specifies the value loaded in the Counter reload value.
                                     This parameter must be a number between 0 and 0xFFFF*/

  uint32_t HSI48CalibrationValue; /*!< Specifies value loaded in HSI48 oscillator smooth trimming.
                                     This parameter must be a number between 0 and 0x3F */
   
  uint32_t FreqErrorCapture;      /*!< Specifies the value loaded in the .FECAP, the frequency error counter 
                                                                    value latched in the time of the last SYNC event.
                                    This parameter must be a number between 0 and 0xFFFF */
                                    
  uint32_t FreqErrorDirection;    /*!< Specifies the value loaded in the .FEDIR, the counting direction of the 
                                                                    frequency error counter latched in the time of the last SYNC event. 
                                                                    It shows whether the actual frequency is below or above the target.
                                    This parameter must be a value of @ref RCCEx_CRS_FreqErrorDirection*/

}RCC_CRSSynchroInfoTypeDef;

#endif /* STM32F042x6 || STM32F048xx */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_CRS_Status RCCEx CRS Status
  * @{
  */
#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define RCC_CRS_NONE      ((uint32_t)0x00000000)
#define RCC_CRS_TIMEOUT   ((uint32_t)0x00000001)
#define RCC_CRS_SYNCOK    ((uint32_t)0x00000002)
#define RCC_CRS_SYNCWARM  ((uint32_t)0x00000004)
#define RCC_CRS_SYNCERR   ((uint32_t)0x00000008)
#define RCC_CRS_SYNCMISS  ((uint32_t)0x00000010)
#define RCC_CRS_TRIMOV    ((uint32_t)0x00000020)

#endif /* STM32F042x6 || STM32F048xx */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection RCCEx Periph Clock Selection
  * @{
  */
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) || \
    defined(STM32F030xC)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1 | \
                                                     RCC_PERIPHCLK_RTC))
#endif /* STM32F030x6 || STM32F030x8 || STM32F031x6 || STM32F038xx || 
          STM32F030xC */

#if defined(STM32F070x6) || defined(STM32F070xB)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1 | \
                                                     RCC_PERIPHCLK_RTC    | RCC_PERIPHCLK_USB))
#endif /* STM32F070x6 || STM32F070xB */

#if defined(STM32F042x6) || defined(STM32F048xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_CEC              ((uint32_t)0x00000400)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1   | \
                                                     RCC_PERIPHCLK_CEC    | RCC_PERIPHCLK_RTC    | \
                                                     RCC_PERIPHCLK_USB))
#endif /* STM32F042x6 || STM32F048xx */

#if defined(STM32F051x8) || defined(STM32F058xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_CEC              ((uint32_t)0x00000400)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1 | \
                                                     RCC_PERIPHCLK_CEC    | RCC_PERIPHCLK_RTC))
#endif /* STM32F051x8 || STM32F058xx */

#if defined(STM32F071xB)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_CEC              ((uint32_t)0x00000400)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_CEC    | \
                                                     RCC_PERIPHCLK_RTC))
#endif /* STM32F071xB */

#if defined(STM32F072xB) || defined(STM32F078xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_CEC              ((uint32_t)0x00000400)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USB              ((uint32_t)0x00020000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_CEC    | \
                                                     RCC_PERIPHCLK_RTC    | RCC_PERIPHCLK_USB))
#endif /* STM32F072xB || STM32F078xx */

#if defined(STM32F091xC) || defined(STM32F098xx)
#define RCC_PERIPHCLK_USART1           ((uint32_t)0x00000001)
#define RCC_PERIPHCLK_USART2           ((uint32_t)0x00000002)
#define RCC_PERIPHCLK_I2C1             ((uint32_t)0x00000020)
#define RCC_PERIPHCLK_CEC              ((uint32_t)0x00000400)
#define RCC_PERIPHCLK_RTC              ((uint32_t)0x00010000)
#define RCC_PERIPHCLK_USART3           ((uint32_t)0x00040000)

#define IS_RCC_PERIPHCLK(SELECTION) ((SELECTION) <= (RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | \
                                                     RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_CEC    | \
                                                     RCC_PERIPHCLK_RTC    | RCC_PERIPHCLK_USART3 ))
#endif /* STM32F091xC || STM32F098xx */

/**
  * @}
  */

/** @defgroup RCCEx_MCO_Clock_Source RCCEx MCO Clock Source
  * @{
  */
  
#if defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx) || defined(STM32F070x6) || defined(STM32F070xB) || defined(STM32F030xC)

#define RCC_MCOSOURCE_PLLCLK_NODIV       (RCC_CFGR_MCO_PLL | RCC_CFGR_PLLNODIV)

#define IS_RCC_MCOSOURCE(SOURCE)  (((SOURCE) == RCC_MCOSOURCE_NONE)         || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSI)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSE)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_SYSCLK)       || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSE)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_PLLCLK_NODIV) || \
                                   ((SOURCE) == RCC_MCOSOURCE_PLLCLK_DIV2)  || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI14))

#endif /* STM32F030x6 || STM32F031x6 || STM32F038xx || STM32F070x6 || STM32F070xB || STM32F030xC */

#if defined(STM32F030x8) || defined(STM32F051x8) || defined(STM32F058xx)

#define IS_RCC_MCOSOURCE(SOURCE)  (((SOURCE) == RCC_MCOSOURCE_NONE)         || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSI)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSE)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_SYSCLK)       || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSE)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_PLLCLK_DIV2)  || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI14))

#endif /* STM32F030x8 || STM32F051x8 || STM32F058xx */

#if defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define RCC_MCOSOURCE_HSI48              RCC_CFGR_MCO_HSI48
#define RCC_MCOSOURCE_PLLCLK_NODIV       (RCC_CFGR_MCO_PLL | RCC_CFGR_PLLNODIV)

#define IS_RCC_MCOSOURCE(SOURCE)  (((SOURCE) == RCC_MCOSOURCE_NONE)         || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSI)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSE)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_SYSCLK)       || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSE)          || \
                                   ((SOURCE) == RCC_MCOSOURCE_PLLCLK_NODIV) || \
                                   ((SOURCE) == RCC_MCOSOURCE_PLLCLK_DIV2)  || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI14)        || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSI48))

#define RCC_IT_HSI48                     ((uint8_t)0x40)

/* Flags in the CR2 register */
#define RCC_CR2_HSI48RDY_BitNumber       16

#define RCC_FLAG_HSI48RDY                ((uint8_t)((CR2_REG_INDEX << 5) | RCC_CR2_HSI48RDY_BitNumber))

#endif /* STM32F042x6 || STM32F048xx ||             */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */
/**
  * @}
  */

#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F072xB) || defined(STM32F078xx)

/** @defgroup RCCEx_USB_Clock_Source RCCEx USB Clock Source
  * @{
  */
#define RCC_USBCLKSOURCE_HSI48           RCC_CFGR3_USBSW_HSI48
#define RCC_USBCLKSOURCE_PLLCLK          RCC_CFGR3_USBSW_PLLCLK

#define IS_RCC_USBCLKSOURCE(SOURCE)  (((SOURCE) == RCC_USBCLKSOURCE_HSI48) || \
                                      ((SOURCE) == RCC_USBCLKSOURCE_PLLCLK))
/**
  * @}
  */

#endif /* STM32F042x6 || STM32F048xx || STM32F072xB || STM32F078xx */

#if defined(STM32F070x6) || defined(STM32F070xB)

/** @defgroup RCCEx_USB_Clock_Source RCCEx USB Clock Source
  * @{
  */
#define RCC_USBCLKSOURCE_PLLCLK          RCC_CFGR3_USBSW_PLLCLK

#define IS_RCC_USBCLKSOURCE(SOURCE)  (((SOURCE) == RCC_USBCLKSOURCE_PLLCLK))
/**
  * @}
  */

#endif /* STM32F070x6 || STM32F070xB */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

/** @defgroup RCCEx_USART2_Clock_Source RCCEx USART2 Clock Source
  * @{
  */
#define RCC_USART2CLKSOURCE_PCLK1        RCC_CFGR3_USART2SW_PCLK
#define RCC_USART2CLKSOURCE_SYSCLK       RCC_CFGR3_USART2SW_SYSCLK
#define RCC_USART2CLKSOURCE_LSE          RCC_CFGR3_USART2SW_LSE
#define RCC_USART2CLKSOURCE_HSI          RCC_CFGR3_USART2SW_HSI

#define IS_RCC_USART2CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART2CLKSOURCE_PCLK1)  || \
                                         ((SOURCE) == RCC_USART2CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART2CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART2CLKSOURCE_HSI))
/**
  * @}
  */

#endif /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F091xC) || defined(STM32F098xx)

/** @defgroup RCCEx_USART3_Clock_Source RCCEx USART3 Clock Source
  * @{
  */
#define RCC_USART3CLKSOURCE_PCLK1        RCC_CFGR3_USART3SW_PCLK
#define RCC_USART3CLKSOURCE_SYSCLK       RCC_CFGR3_USART3SW_SYSCLK
#define RCC_USART3CLKSOURCE_LSE          RCC_CFGR3_USART3SW_LSE
#define RCC_USART3CLKSOURCE_HSI          RCC_CFGR3_USART3SW_HSI

#define IS_RCC_USART3CLKSOURCE(SOURCE)  (((SOURCE) == RCC_USART3CLKSOURCE_PCLK1)  || \
                                         ((SOURCE) == RCC_USART3CLKSOURCE_SYSCLK) || \
                                         ((SOURCE) == RCC_USART3CLKSOURCE_LSE)    || \
                                         ((SOURCE) == RCC_USART3CLKSOURCE_HSI))
/**
  * @}
  */

#endif /* STM32F091xC || STM32F098xx */


#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

/** @defgroup RCCEx_CEC_Clock_Source RCCEx CEC Clock Source
  * @{
  */
#define RCC_CECCLKSOURCE_HSI             RCC_CFGR3_CECSW_HSI_DIV244
#define RCC_CECCLKSOURCE_LSE             RCC_CFGR3_CECSW_LSE

#define IS_RCC_CECCLKSOURCE(SOURCE)  (((SOURCE) == RCC_CECCLKSOURCE_HSI) || \
                                      ((SOURCE) == RCC_CECCLKSOURCE_LSE))
/**
  * @}
  */

#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

/** @defgroup RCCEx_PLL_Clock_Source RCCEx PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI                RCC_CFGR_PLLSRC_HSI_PREDIV
#define RCC_PLLSOURCE_HSI48              RCC_CFGR_PLLSRC_HSI48_PREDIV

#define IS_RCC_PLLSOURCE(SOURCE) (((SOURCE) == RCC_PLLSOURCE_HSI)   || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSI48) || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_System_Clock_Source RCCEx System Clock Source
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI48           RCC_CFGR_SW_HSI48

#define IS_RCC_SYSCLKSOURCE(SOURCE)  (((SOURCE) == RCC_SYSCLKSOURCE_HSI)    || \
                                      ((SOURCE) == RCC_SYSCLKSOURCE_HSE)    || \
                                      ((SOURCE) == RCC_SYSCLKSOURCE_PLLCLK) || \
                                      ((SOURCE) == RCC_SYSCLKSOURCE_HSI48))

#define RCC_SYSCLKSOURCE_STATUS_HSI48    RCC_CFGR_SWS_HSI48

#define IS_RCC_SYSCLKSOURCE_STATUS(SOURCE) (((SOURCE) == RCC_SYSCLKSOURCE_STATUS_HSI)    || \
                                            ((SOURCE) == RCC_SYSCLKSOURCE_STATUS_HSE)    || \
                                            ((SOURCE) == RCC_SYSCLKSOURCE_STATUS_PLLCLK) || \
                                            ((SOURCE) == RCC_SYSCLKSOURCE_STATUS_HSI48))
/**
  * @}
  */

/** @defgroup RCCEx_HSI48_Config RCCEx HSI48 Config
  * @{
  */
#define RCC_HSI48_OFF                    ((uint8_t)0x00)
#define RCC_HSI48_ON                     ((uint8_t)0x01)

#define IS_RCC_HSI48(HSI48) (((HSI48) == RCC_HSI48_OFF) || ((HSI48) == RCC_HSI48_ON))
/**
  * @}
  */
#else
/** @defgroup RCCEx_PLL_Clock_Source RCCEx PLL Clock Source
  * @{
  */

#if defined(STM32F070xB) || defined(STM32F070x6) || defined(STM32F030xC)
#define RCC_PLLSOURCE_HSI                RCC_CFGR_PLLSRC_HSI_PREDIV
#else
#define RCC_PLLSOURCE_HSI                RCC_CFGR_PLLSRC_HSI_DIV2
#endif

#define IS_RCC_PLLSOURCE(SOURCE) (((SOURCE) == RCC_PLLSOURCE_HSI)   || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSE))
/**
  * @}
  */

/** @defgroup RCCEx_System_Clock_Source RCCEx System Clock Source
  * @{
  */
#define IS_RCC_SYSCLKSOURCE(SOURCE)  (((SOURCE) == RCC_SYSCLKSOURCE_HSI)    || \
                                      ((SOURCE) == RCC_SYSCLKSOURCE_HSE)    || \
                                      ((SOURCE) == RCC_SYSCLKSOURCE_PLLCLK))

#define IS_RCC_SYSCLKSOURCE_STATUS(SOURCE) (((SOURCE) == RCC_SYSCLKSOURCE_STATUS_HSI)    || \
                                            ((SOURCE) == RCC_SYSCLKSOURCE_STATUS_HSE)    || \
                                            ((SOURCE) == RCC_SYSCLKSOURCE_STATUS_PLLCLK))
/**
  * @}
  */

/** @defgroup RCCEx_HSI48_Config RCCEx HSI48 Config
  * @{
  */
#define RCC_HSI48_OFF                    ((uint8_t)0x00)

#define IS_RCC_HSI48(HSI48) (((HSI48) == RCC_HSI48_OFF))
/**
  * @}
  */

#endif /* STM32F042x6 || STM32F048xx ||             */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */


/** @defgroup RCCEx_MCOx_Clock_Prescaler RCCEx MCOx Clock Prescaler
  * @{
  */
  
#if defined(STM32F030x8) || defined(STM32F051x8) || defined(STM32F058xx)

#define RCC_MCO_NODIV                    ((uint32_t)0x00000000)

#define IS_RCC_MCODIV(DIV) (((DIV) == RCC_MCO_NODIV))

#endif /* STM32F030x8 || STM32F051x8 || STM32F058xx */

#if defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx) || defined(STM32F070x6) || \
    defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F071xB) || defined(STM32F070xB) || \
    defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define RCC_MCO_DIV1                     ((uint32_t)0x00000000)
#define RCC_MCO_DIV2                     ((uint32_t)0x10000000)
#define RCC_MCO_DIV4                     ((uint32_t)0x20000000)
#define RCC_MCO_DIV8                     ((uint32_t)0x30000000)
#define RCC_MCO_DIV16                    ((uint32_t)0x40000000)
#define RCC_MCO_DIV32                    ((uint32_t)0x50000000)
#define RCC_MCO_DIV64                    ((uint32_t)0x60000000)
#define RCC_MCO_DIV128                   ((uint32_t)0x70000000)

#define IS_RCC_MCODIV(DIV) (((DIV) == RCC_MCO_DIV1)  || ((DIV) == RCC_MCO_DIV2)   || \
                            ((DIV) == RCC_MCO_DIV4)  || ((DIV) == RCC_MCO_DIV8)   || \
                            ((DIV) == RCC_MCO_DIV16) || ((DIV) == RCC_MCO_DIV32)  || \
                            ((DIV) == RCC_MCO_DIV64) || ((DIV) == RCC_MCO_DIV128))

#endif /* STM32F030x6 || STM32F031x6 || STM32F038xx || STM32F042x6 || STM32F048xx || */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070x6 || STM32F070xB */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

/**
  * @}
  */

#if defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

/** @defgroup RCCEx_CRS_SynchroSource RCCEx CRS SynchroSource
  * @{
  */
#define RCC_CRS_SYNC_SOURCE_GPIO       ((uint32_t)0x00)        /*!< Synchro Signal soucre GPIO */
#define RCC_CRS_SYNC_SOURCE_LSE        CRS_CFGR_SYNCSRC_0      /*!< Synchro Signal source LSE */
#define RCC_CRS_SYNC_SOURCE_USB        CRS_CFGR_SYNCSRC_1      /*!< Synchro Signal source USB SOF (default)*/
  
#define IS_RCC_CRS_SYNC_SOURCE(_SOURCE_) (((_SOURCE_) == RCC_CRS_SYNC_SOURCE_GPIO) || \
                                          ((_SOURCE_) == RCC_CRS_SYNC_SOURCE_LSE)  || \
                                          ((_SOURCE_) == RCC_CRS_SYNC_SOURCE_USB))
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroDivider RCCEx CRS SynchroDivider
  * @{
  */
#define RCC_CRS_SYNC_DIV1        ((uint32_t)0x00)                          /*!< Synchro Signal not divided (default) */
#define RCC_CRS_SYNC_DIV2        CRS_CFGR_SYNCDIV_0                        /*!< Synchro Signal divided by 2 */
#define RCC_CRS_SYNC_DIV4        CRS_CFGR_SYNCDIV_1                        /*!< Synchro Signal divided by 4 */
#define RCC_CRS_SYNC_DIV8        (CRS_CFGR_SYNCDIV_1 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 8 */
#define RCC_CRS_SYNC_DIV16       CRS_CFGR_SYNCDIV_2                        /*!< Synchro Signal divided by 16 */
#define RCC_CRS_SYNC_DIV32       (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_0) /*!< Synchro Signal divided by 32 */
#define RCC_CRS_SYNC_DIV64       (CRS_CFGR_SYNCDIV_2 | CRS_CFGR_SYNCDIV_1) /*!< Synchro Signal divided by 64 */
#define RCC_CRS_SYNC_DIV128      CRS_CFGR_SYNCDIV                          /*!< Synchro Signal divided by 128 */
  
#define IS_RCC_CRS_SYNC_DIV(_DIV_) (((_DIV_) == RCC_CRS_SYNC_DIV1)  || ((_DIV_) == RCC_CRS_SYNC_DIV2)  || \
                                    ((_DIV_) == RCC_CRS_SYNC_DIV4)  || ((_DIV_) == RCC_CRS_SYNC_DIV8)  || \
                                    ((_DIV_) == RCC_CRS_SYNC_DIV16) || ((_DIV_) == RCC_CRS_SYNC_DIV32) || \
                                    ((_DIV_) == RCC_CRS_SYNC_DIV64) || ((_DIV_) == RCC_CRS_SYNC_DIV128))
/**
  * @}
  */

/** @defgroup RCCEx_CRS_SynchroPolarity RCCEx CRS SynchroPolarity
  * @{
  */
#define RCC_CRS_SYNC_POLARITY_RISING        ((uint32_t)0x00)      /*!< Synchro Active on rising edge (default) */
#define RCC_CRS_SYNC_POLARITY_FALLING       CRS_CFGR_SYNCPOL      /*!< Synchro Active on falling edge */
  
#define IS_RCC_CRS_SYNC_POLARITY(_POLARITY_) (((_POLARITY_) == RCC_CRS_SYNC_POLARITY_RISING) || \
                                              ((_POLARITY_) == RCC_CRS_SYNC_POLARITY_FALLING))
/**
  * @}
  */
  
/** @defgroup RCCEx_CRS_ReloadValueDefault RCCEx CRS ReloadValueDefault
  * @{
  */
#define RCC_CRS_RELOADVALUE_DEFAULT         ((uint32_t)0xBB7F)      /*!< The reset value of the RELOAD field corresponds 
                                                                         to a target frequency of 48 MHz and a synchronization signal frequency of 1 kHz (SOF signal from USB). */

#define IS_RCC_CRS_RELOADVALUE(_VALUE_) (((_VALUE_) <= 0xFFFF))
/**
  * @}
  */
  
/** @defgroup RCCEx_CRS_ErrorLimitDefault RCCEx CRS ErrorLimitDefault
  * @{
  */
#define RCC_CRS_ERRORLIMIT_DEFAULT          ((uint32_t)0x22)      /*!< Default Frequency error limit */
    
#define IS_RCC_CRS_ERRORLIMIT(_VALUE_) (((_VALUE_) <= 0xFF))
/**
  * @}
  */

/** @defgroup RCCEx_CRS_HSI48CalibrationDefault RCCEx CRS HSI48CalibrationDefault
  * @{
  */
#define RCC_CRS_HSI48CALIBRATION_DEFAULT    ((uint32_t)0x20)   /*!< The default value is 32, which corresponds to the middle of the trimming interval. 
                                                                    The trimming step is around 67 kHz between two consecutive TRIM steps. A higher TRIM value
                                                                    corresponds to a higher output frequency */
    
#define IS_RCC_CRS_HSI48CALIBRATION(_VALUE_) (((_VALUE_) <= 0x3F))
/**
  * @}
  */

/** @defgroup RCCEx_CRS_FreqErrorDirection RCCEx CRS FreqErrorDirection
  * @{
  */
#define RCC_CRS_FREQERRORDIR_UP             ((uint32_t)0x00)          /*!< Upcounting direction, the actual frequency is above the target */
#define RCC_CRS_FREQERRORDIR_DOWN           ((uint32_t)CRS_ISR_FEDIR) /*!< Downcounting direction, the actual frequency is below the target */
    
#define IS_RCC_CRS_FREQERRORDIR(_DIR_) (((_DIR_) == RCC_CRS_FREQERRORDIR_UP) || \
                                        ((_DIR_) == RCC_CRS_FREQERRORDIR_DOWN))
/**
  * @}
  */

/** @defgroup RCCEx_CRS_Interrupt_Sources RCCEx CRS Interrupt Sources
  * @{
  */
#define RCC_CRS_IT_SYNCOK             CRS_ISR_SYNCOKF    /*!< SYNC event OK */
#define RCC_CRS_IT_SYNCWARN           CRS_ISR_SYNCWARNF  /*!< SYNC warning */
#define RCC_CRS_IT_ERR                CRS_ISR_ERRF       /*!< error */
#define RCC_CRS_IT_ESYNC              CRS_ISR_ESYNCF     /*!< Expected SYNC */
#define RCC_CRS_IT_TRIMOVF            CRS_ISR_TRIMOVF    /*!< Trimming overflow or underflow */
#define RCC_CRS_IT_SYNCERR            CRS_ISR_SYNCERR    /*!< SYNC error */
#define RCC_CRS_IT_SYNCMISS           CRS_ISR_SYNCMISS    /*!< SYNC missed*/

/**
  * @}
  */
  
/** @defgroup RCCEx_CRS_Flags RCCEx CRS Flags
  * @{
  */
#define RCC_CRS_FLAG_SYNCOK             CRS_ISR_SYNCOKF     /* SYNC event OK flag     */
#define RCC_CRS_FLAG_SYNCWARN           CRS_ISR_SYNCWARNF   /* SYNC warning flag      */
#define RCC_CRS_FLAG_ERR                CRS_ISR_ERRF        /* Error flag        */
#define RCC_CRS_FLAG_ESYNC              CRS_ISR_ESYNCF      /* Expected SYNC flag     */
#define RCC_CRS_FLAG_TRIMOVF            CRS_ISR_TRIMOVF     /*!< Trimming overflow or underflow */
#define RCC_CRS_FLAG_SYNCERR            CRS_ISR_SYNCERR     /*!< SYNC error */
#define RCC_CRS_FLAG_SYNCMISS           CRS_ISR_SYNCMISS    /*!< SYNC missed*/

/**
  * @}
  */

#endif /* STM32F042x6 || STM32F048xx || */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

/**
  * @}
  */

/* Exported macros ------------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */

/** @defgroup RCCEx_Peripheral_Clock_Enable_Disable RCCEx_Peripheral_Clock_Enable_Disable
  * @brief  Enables or disables the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
#if defined(STM32F030x6) || defined(STM32F030x8) || \
    defined(STM32F051x8) || defined(STM32F058xx) || defined(STM32F070xB) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __GPIOD_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIODEN))

#define __GPIOD_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIODEN))

#endif /* STM32F030x6 || STM32F030x8 ||  */
       /* STM32F051x8 || STM32F058xx || STM32F070xB || */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __GPIOE_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_GPIOEEN))

#define __GPIOE_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_GPIOEEN))

#endif /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
      
#define __TSC_CLK_ENABLE()           (RCC->AHBENR |= (RCC_AHBENR_TSCEN))

#define __TSC_CLK_DISABLE()          (RCC->AHBENR &= ~(RCC_AHBENR_TSCEN))

#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F091xC) || defined(STM32F098xx)

#define __DMA2_CLK_ENABLE()         (RCC->AHBENR |= (RCC_AHBENR_DMA2EN))

#define __DMA2_CLK_DISABLE()        (RCC->AHBENR &= ~(RCC_AHBENR_DMA2EN))

#endif /* STM32F091xC || STM32F098xx */
      
/** @brief  Enable or disable the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  */
#if defined(STM32F030x8) ||                                                 \
    defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __USART2_CLK_ENABLE()  (RCC->APB1ENR |= (RCC_APB1ENR_USART2EN))
#define __SPI2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN))

#define __USART2_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_USART2EN))
#define __SPI2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI2EN))

#endif /* STM32F030x8 || STM32F042x6 || STM32F048xx || */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F031x6) || defined(STM32F038xx) ||                         \
    defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __TIM2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN))

#define __TIM2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))

#endif /* STM32F031x6 || STM32F038xx ||             */
       /* STM32F042x6 || STM32F048xx ||             */
       /* STM32F051x8 || STM32F058xx ||             */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F030x8) ||                                                 \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __TIM6_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM6EN))
#define __I2C2_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_I2C2EN))

#define __TIM6_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN))
#define __I2C2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C2EN))

#endif /* STM32F030x8 ||                               */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __DAC1_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_DACEN))

#define __DAC1_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_DACEN))

#endif /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __CEC_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_CECEN))

#define __CEC_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CECEN))

#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) ||  \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __TIM7_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_TIM7EN))
#define __USART3_CLK_ENABLE()  (RCC->APB1ENR |= (RCC_APB1ENR_USART3EN))
#define __USART4_CLK_ENABLE()  (RCC->APB1ENR |= (RCC_APB1ENR_USART4EN))

#define __TIM7_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7EN))
#define __USART3_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_USART3EN))
#define __USART4_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_USART4EN))

#endif /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F070x6) || \
    defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB)

#define __USB_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_USBEN))

#define __USB_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_USBEN))

#endif /* STM32F042x6 || STM32F048xx || STM32F070x6 || */
       /* STM32F072xB || STM32F078xx || STM32F070xB  */

#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F072xB) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __CAN_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_CANEN))
#define __CAN_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CANEN))

#endif /* STM32F042x6 || STM32F048xx || STM32F072xB  || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __CRS_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_CRSEN))

#define __CRS_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CRSEN))

#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __USART5_CLK_ENABLE()       (RCC->APB1ENR |= (RCC_APB1ENR_USART5EN))

#define __USART5_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_USART5EN))

#endif /* STM32F091xC || STM32F098xx || STM32F030xC */

/** @brief  Enable or disable the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  */
#if defined(STM32F030x8) || defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F070x6) || \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC) 

#define __TIM15_CLK_ENABLE()    (RCC->APB2ENR |= (RCC_APB2ENR_TIM15EN))

#define __TIM15_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM15EN))

#endif /* STM32F030x8 || STM32F042x6 || STM32F048xx || STM32F070x6 || */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __USART6_CLK_ENABLE()       (RCC->APB2ENR |= (RCC_APB2ENR_USART6EN))

#define __USART6_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_USART6EN))

#endif /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F091xC) || defined(STM32F098xx)

#define __USART7_CLK_ENABLE()       (RCC->APB2ENR |= (RCC_APB2ENR_USART7EN))
#define __USART8_CLK_ENABLE()       (RCC->APB2ENR |= (RCC_APB2ENR_USART8EN))

#define __USART7_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_USART7EN))
#define __USART8_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_USART8EN))

#endif /* STM32F091xC || STM32F098xx */

/**
  * @}
  */


/** @defgroup RCCEx_Force_Release_Peripheral_Reset RCCEx Force Release Peripheral Reset
  * @brief  Forces or releases peripheral reset.
  * @{
  */

/** @brief  Force or release AHB peripheral reset.
  */
#if defined(STM32F030x6) || defined(STM32F030x8) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __GPIOD_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIODRST))

#define __GPIOD_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIODRST))

#endif /* STM32F030x6 || STM32F030x8 ||                */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __GPIOE_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOERST))

#define __GPIOE_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOERST))

#endif /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
      
#define __TSC_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_TSCRST))

#define __TSC_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_TSCRST))

#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

/** @brief  Force or release APB1 peripheral reset.
  */
#if defined(STM32F030x8) ||                                                 \
    defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F070x6) || \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __USART2_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART2RST))
#define __SPI2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI2RST))

#define __USART2_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART2RST))
#define __SPI2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI2RST))

#endif /* STM32F030x8 || STM32F042x6 || STM32F048xx || STM32F070x6 || */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F031x6) || defined(STM32F038xx) ||                         \
    defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __TIM2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))

#define __TIM2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))

#endif /* STM32F031x6 || STM32F038xx ||             */
       /* STM32F042x6 || STM32F048xx ||             */
       /* STM32F051x8 || STM32F058xx ||             */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F030x8) ||                                                 \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) ||\
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __TIM6_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM6RST))
#define __I2C2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C2RST))

#define __TIM6_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM6RST))
#define __I2C2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C2RST))

#endif /* STM32F030x8 ||                               */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __DAC1_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_DACRST))

#define __DAC1_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DACRST))

#endif /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __CEC_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_CECRST))

#define __CEC_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CECRST))

#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __TIM7_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM7RST))
#define __USART3_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART3RST))
#define __USART4_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART4RST))

#define __TIM7_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM7RST))
#define __USART3_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART3RST))
#define __USART4_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART4RST))

#endif /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F070x6) ||  \
    defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB)

#define __USB_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_USBRST))

#define __USB_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USBRST))

#endif /* STM32F042x6 || STM32F048xx || STM32F070x6 || */
       /* STM32F072xB || STM32F078xx || STM32F070xB */

#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F072xB) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __CAN_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_CANRST))

#define __CAN_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CANRST))

#endif /* STM32F042x6 || STM32F048xx || STM32F072xB || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __CRS_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_CRSRST))

#define __CRS_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CRSRST))

#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#if defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __USART5_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_USART5RST))

#define __USART5_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART5RST))

#endif /* STM32F091xC || STM32F098xx || STM32F030xC */


/** @brief  Force or release APB2 peripheral reset.
  */
#if defined(STM32F030x8) || defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F070x6) || \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __TIM15_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM15RST))

#define __TIM15_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM15RST))

#endif /* STM32F030x8 || STM32F042x6 || STM32F048xx || STM32F070x6 || */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

#define __USART6_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_USART6RST))

#define __USART6_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART6RST))

#endif /* STM32F091xC || STM32F098xx || STM32F030xC */

#if defined(STM32F091xC) || defined(STM32F098xx)

#define __USART7_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_USART7RST))
#define __USART8_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_USART8RST))

#define __USART7_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART7RST))
#define __USART8_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART8RST))

#endif /* STM32F091xC || STM32F098xx */

/**
  * @}
  */
  
/** @defgroup RCCEx_HSI48_Enable_Disable RCCEx HSI48 Enable Disable    
  * @brief  Macros to enable or disable the Internal 48Mhz High Speed oscillator (HSI48).
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  * @note   HSI48 can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI14.
  * @note   After enabling the HSI48 with __HAL_RCC_HSI48_ENABLE(), the application software
  *         should wait on HSI48RDY flag to be set indicating that HSI48 clock is stable and can be
  *         used as system clock source. This is not necessary if HAL_RCC_OscConfig() is used.
  * @note   When the HSI48 is stopped, HSI48RDY flag goes low after 6 HSI48 oscillator
  *         clock cycles.
  * @{
  */
#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

#define __HAL_RCC_HSI48_ENABLE()  SET_BIT(RCC->CR2, RCC_CR2_HSI48ON)
#define __HAL_RCC_HSI48_DISABLE() CLEAR_BIT(RCC->CR2, RCC_CR2_HSI48ON)

/** @brief  Macro to get the Internal 48Mhz High Speed oscillator (HSI48) state.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_HSI48_ON:  HSI48 enabled
  *            @arg RCC_HSI48_OFF: HSI48 disabled
  */
#define __HAL_RCC_GET_HSI48_STATE() \
                  (((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CR2_HSI48ON)) != RESET) ? RCC_HSI48_ON : RCC_HSI48_OFF)  

#else

/** @brief  Macro to get the Internal 48Mhz High Speed oscillator (HSI48) state.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_HSI_OFF: HSI48 disabled
  */
#define __HAL_RCC_GET_HSI48_STATE()   RCC_HSI_OFF 

#endif /* STM32F042x6 || STM32F048xx ||             */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

/**
  * @}
  */

/** @defgroup RCCEx_Peripheral_Clock_Source_Config RCCEx Peripheral Clock Source Config
  * @{
  */
#if defined(STM32F042x6) || defined(STM32F048xx) ||  \
    defined(STM32F072xB) || defined(STM32F078xx) ||  \
    defined(STM32F070x6) || defined(STM32F070xB)

/** @brief  Macro to configure the USB clock (USBCLK).
  * @param  __USBCLKSource__: specifies the USB clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USBCLKSOURCE_HSI48:  HSI48 selected as USB clock (not available for STM32F070x6 & STM32F070xB)
  *            @arg RCC_USBCLKSOURCE_PLLCLK: PLL Clock selected as USB clock
  */
#define __HAL_RCC_USB_CONFIG(__USBCLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_USBSW, (uint32_t)(__USBCLKSource__))

/** @brief  Macro to get the USB clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USBCLKSOURCE_HSI48:  HSI48 selected as USB clock (not available for STM32F070x6 & STM32F070xB)
  *            @arg RCC_USBCLKSOURCE_PLLCLK: PLL Clock selected as USB clock
  */
#define __HAL_RCC_GET_USB_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_USBSW)))

#endif /* STM32F042x6 || STM32F048xx || */
       /* STM32F072xB || STM32F078xx || */
       /* STM32F070x6 || STM32F070xB    */

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F051x8) || defined(STM32F058xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

/** @brief  Macro to configure the CEC clock.
  * @param  __CECCLKSource__: specifies the CEC clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_CECCLKSOURCE_HSI: HSI selected as CEC clock
  *            @arg RCC_CECCLKSOURCE_LSE: LSE selected as CEC clock
  */
#define __HAL_RCC_CEC_CONFIG(__CECCLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_CECSW, (uint32_t)(__CECCLKSource__))

/** @brief  Macro to get the HDMI CEC clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_CECCLKSOURCE_HSI: HSI selected as CEC clock
  *            @arg RCC_CECCLKSOURCE_LSE: LSE selected as CEC clock
  */
#define __HAL_RCC_GET_CEC_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_CECSW)))

#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F051x8 || STM32F058xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || defined(STM32F098xx) */

#if defined(STM32F030x6) || defined(STM32F031x6) || defined(STM32F038xx) || \
    defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F070x6) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)

/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSource__: specifies the MCO clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_MCOSOURCE_HSI: HSI selected as MCO clock
  *            @arg RCC_MCOSOURCE_HSE: HSE selected as MCO clock
  *            @arg RCC_MCOSOURCE_LSI: LSI selected as MCO clock
  *            @arg RCC_MCOSOURCE_LSE: LSE selected as MCO clock
  *            @arg RCC_MCOSOURCE_PLLCLK_NODIV: PLLCLK selected as MCO clock
  *            @arg RCC_MCOSOURCE_PLLCLK_DIV2: PLLCLK Divided by 2 selected as MCO clock
  *            @arg RCC_MCOSOURCE_SYSCLK: System Clock selected as MCO clock
  *            @arg RCC_MCOSOURCE_HSI14: HSI14 selected as MCO clock
  *            @arg RCC_MCOSOURCE_HSI48: HSI48 selected as MCO clock
  * @param  __MCODiv__: specifies the MCO clock prescaler.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCO_DIV1: MCO clock source is divided by 1
  *            @arg RCC_MCO_DIV2: MCO clock source is divided by 2
  *            @arg RCC_MCO_DIV4: MCO clock source is divided by 4
  *            @arg RCC_MCO_DIV8: MCO clock source is divided by 8
  *            @arg RCC_MCO_DIV16: MCO clock source is divided by 16
  *            @arg RCC_MCO_DIV32: MCO clock source is divided by 32
  *            @arg RCC_MCO_DIV64: MCO clock source is divided by 64
  *            @arg RCC_MCO_DIV128: MCO clock source is divided by 128
  */
#define __HAL_RCC_MCO_CONFIG(__MCOCLKSource__, __MCODiv__) \
                 MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO | RCC_CFGR_MCOPRE), ((__MCOCLKSource__) | (__MCODiv__)))
#else

/** @brief  Macro to configure the MCO clock.
  * @param  __MCOCLKSource__: specifies the MCO clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_MCOSOURCE_HSI: HSI selected as MCO clock
  *            @arg RCC_MCOSOURCE_HSE: HSE selected as MCO clock
  *            @arg RCC_MCOSOURCE_LSI: LSI selected as MCO clock
  *            @arg RCC_MCOSOURCE_LSE: LSE selected as MCO clock
  *            @arg RCC_MCOSOURCE_PLLCLK_DIV2: PLLCLK Divided by 2 selected as MCO clock
  *            @arg RCC_MCOSOURCE_SYSCLK: System Clock selected as MCO clock
  *            @arg RCC_MCOSOURCE_HSI14: HSI14 selected as MCO clock
  *            @arg RCC_MCOSOURCE_HSI48: HSI48 selected as MCO clock
  * @param  __MCODiv__: specifies the MCO clock prescaler.
  *         This parameter can be one of the following values:
  *            @arg RCC_MCO_NODIV: No division applied on MCO clock source
  */
#define __HAL_RCC_MCO_CONFIG(__MCOCLKSource__, __MCODiv__) \
                 MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, __MCOCLKSource__)

#endif /* STM32F030x6 || STM32F031x6 || STM32F038xx || STM32F070x6 || */
       /* STM32F042x6 || STM32F048xx ||                               */
       /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB || */
       /* STM32F091xC || STM32F098xx || STM32F030xC                   */
                   
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
/** @brief  Macro to configure the USART2 clock (USART2CLK).
  * @param  __USART2CLKSource__: specifies the USART2 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USART2CLKSOURCE_PCLK1: PCLK1 selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_HSI: HSI selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_SYSCLK: System Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_LSE: LSE selected as USART2 clock
  */
#define __HAL_RCC_USART2_CONFIG(__USART2CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_USART2SW, (uint32_t)(__USART2CLKSource__))

/** @brief  Macro to get the USART2 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART2CLKSOURCE_PCLK1: PCLK1 selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_HSI: HSI selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_SYSCLK: System Clock selected as USART2 clock
  *            @arg RCC_USART2CLKSOURCE_LSE: LSE selected as USART2 clock
  */
#define __HAL_RCC_GET_USART2_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_USART2SW)))
#endif /* STM32F071xB || STM32F072xB || STM32F078xx || STM32F091xC || STM32F098xx*/

#if defined(STM32F091xC) || defined(STM32F098xx)
/** @brief  Macro to configure the USART3 clock (USART3CLK).
  * @param  __USART3CLKSource__: specifies the USART3 clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_USART3CLKSOURCE_PCLK1: PCLK1 selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_HSI: HSI selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_SYSCLK: System Clock selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_LSE: LSE selected as USART3 clock
  */
#define __HAL_RCC_USART3_CONFIG(__USART3CLKSource__) \
                  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_USART3SW, (uint32_t)(__USART3CLKSource__))

/** @brief  Macro to get the USART3 clock source.
  * @retval The clock source can be one of the following values:
  *            @arg RCC_USART3CLKSOURCE_PCLK1: PCLK1 selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_HSI: HSI selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_SYSCLK: System Clock selected as USART3 clock
  *            @arg RCC_USART3CLKSOURCE_LSE: LSE selected as USART3 clock
  */
#define __HAL_RCC_GET_USART3_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_USART3SW)))

#endif /* STM32F091xC || STM32F098xx */
/**
  * @}
  */
  
#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

/** @defgroup RCCEx_IT_And_Flag RCCEx IT and Flag
  * @{
  */
/* Interrupt & Flag management */

/**
  * @brief  Enables the specified CRS interrupts.
  * @param  __INTERRUPT__: specifies the CRS interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *              @arg RCC_CRS_IT_SYNCOK
  *              @arg RCC_CRS_IT_SYNCWARN
  *              @arg RCC_CRS_IT_ERR
  *              @arg RCC_CRS_IT_ESYNC
  * @retval None
  */
#define __HAL_RCC_CRS_ENABLE_IT(__INTERRUPT__)   (CRS->CR |= (__INTERRUPT__))

/**
  * @brief  Disables the specified CRS interrupts.
  * @param  __INTERRUPT__: specifies the CRS interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *              @arg RCC_CRS_IT_SYNCOK
  *              @arg RCC_CRS_IT_SYNCWARN
  *              @arg RCC_CRS_IT_ERR
  *              @arg RCC_CRS_IT_ESYNC
  * @retval None
  */
#define __HAL_RCC_CRS_DISABLE_IT(__INTERRUPT__)  (CRS->CR &= ~(__INTERRUPT__))

/** @brief  Check the CRS's interrupt has occurred or not.
  * @param  __INTERRUPT__: specifies the CRS interrupt source to check.
  *         This parameter can be one of the following values:
  *              @arg RCC_CRS_IT_SYNCOK
  *              @arg RCC_CRS_IT_SYNCWARN
  *              @arg RCC_CRS_IT_ERR
  *              @arg RCC_CRS_IT_ESYNC
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_RCC_CRS_GET_IT_SOURCE(__INTERRUPT__)     ((CRS->CR & (__INTERRUPT__))? SET : RESET)

/** @brief  Clear the CRS's interrupt pending bits
  *         bits to clear the selected interrupt pending bits.
  * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *              @arg RCC_CRS_IT_SYNCOK
  *              @arg RCC_CRS_IT_SYNCWARN
  *              @arg RCC_CRS_IT_ERR
  *              @arg RCC_CRS_IT_ESYNC
  *              @arg RCC_CRS_IT_TRIMOVF
  *              @arg RCC_CRS_IT_SYNCERR
  *              @arg RCC_CRS_IT_SYNCMISS
  */
/* CRS IT Error Mask */
#define  RCC_CRS_IT_ERROR_MASK                 ((uint32_t)(RCC_CRS_IT_TRIMOVF | RCC_CRS_IT_SYNCERR | RCC_CRS_IT_SYNCMISS))

#define __HAL_RCC_CRS_CLEAR_IT(__INTERRUPT__)  ((((__INTERRUPT__) &  RCC_CRS_IT_ERROR_MASK)!= 0) ? (CRS->ICR |= CRS_ICR_ERRC) : \
                                                (CRS->ICR |= (__INTERRUPT__)))

/**
  * @brief  Checks whether the specified CRS flag is set or not.
  * @param  _FLAG_: specifies the flag to check.
  *          This parameter can be one of the following values:
  *              @arg RCC_CRS_FLAG_SYNCOK
  *              @arg RCC_CRS_FLAG_SYNCWARN
  *              @arg RCC_CRS_FLAG_ERR
  *              @arg RCC_CRS_FLAG_ESYNC
  *              @arg RCC_CRS_FLAG_TRIMOVF
  *              @arg RCC_CRS_FLAG_SYNCERR
  *              @arg RCC_CRS_FLAG_SYNCMISS
  * @retval The new state of _FLAG_ (TRUE or FALSE).
  */
#define __HAL_RCC_CRS_GET_FLAG(_FLAG_)  ((CRS->ISR & (_FLAG_)) == (_FLAG_))

/**
  * @brief  Clears the CRS specified FLAG.
  * @param _FLAG_: specifies the flag to clear.
  *          This parameter can be one of the following values:
  *              @arg RCC_CRS_FLAG_SYNCOK
  *              @arg RCC_CRS_FLAG_SYNCWARN
  *              @arg RCC_CRS_FLAG_ERR
  *              @arg RCC_CRS_FLAG_ESYNC
  *              @arg RCC_CRS_FLAG_TRIMOVF
  *              @arg RCC_CRS_FLAG_SYNCERR
  *              @arg RCC_CRS_FLAG_SYNCMISS
  * @retval None
  */

/* CRS Flag Error Mask */
#define RCC_CRS_FLAG_ERROR_MASK                 ((uint32_t)(RCC_CRS_FLAG_TRIMOVF | RCC_CRS_FLAG_SYNCERR | RCC_CRS_FLAG_SYNCMISS))

#define __HAL_RCC_CRS_CLEAR_FLAG(__FLAG__)   ((((__FLAG__) & RCC_CRS_FLAG_ERROR_MASK)!= 0) ? (CRS->ICR |= CRS_ICR_ERRC) : \
                                              (CRS->ICR |= (__FLAG__)))

/**
  * @}
  */

/** @defgroup RCCEx_CRS_Extended_Features RCCEx CRS Extended Features
  * @{
  */  
/**
  * @brief  Enables the oscillator clock for frequency error counter.
  * @note   when the CEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_ENABLE_FREQ_ERROR_COUNTER() (CRS->CR |= CRS_CR_CEN)

/**
  * @brief  Disables the oscillator clock for frequency error counter.
  * @retval None
  */
#define __HAL_RCC_CRS_DISABLE_FREQ_ERROR_COUNTER()  (CRS->CR &= ~CRS_CR_CEN)

/**
  * @brief  Enables the automatic hardware adjustement of TRIM bits.
  * @note   When the AUTOTRIMEN bit is set the CRS_CFGR register becomes write-protected.
  * @retval None
  */
#define __HAL_RCC_CRS_ENABLE_AUTOMATIC_CALIB()  (CRS->CR |= CRS_CR_AUTOTRIMEN)

/**
  * @brief  Enables or disables the automatic hardware adjustement of TRIM bits.
  * @retval None
  */
#define __HAL_RCC_CRS_DISABLE_AUTOMATIC_CALIB()  (CRS->CR &= ~CRS_CR_AUTOTRIMEN)

/**
  * @brief  Macro to calculate reload value to be set in CRS register according to target and sync frequencies
  * @note   The RELOAD value should be selected according to the ratio between the target frequency and the frequency 
  *             of the synchronization source after prescaling. It is then decreased by one in order to 
  *             reach the expected synchronization on the zero value. The formula is the following:
  *             RELOAD = (fTARGET / fSYNC) -1
  * @param  _FTARGET_ Target frequency (value in Hz)
  * @param  _FSYNC_ Synchronization signal frequency (value in Hz)
  * @retval None
  */
#define __HAL_RCC_CRS_CALCULATE_RELOADVALUE(_FTARGET_, _FSYNC_)  (((_FTARGET_) / (_FSYNC_)) - 1)

/**
  * @}
  */
  
#endif /* STM32F042x6 || STM32F048xx ||                */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */
  
/**
  * @}
  */   

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1 
  * @{
  */
  
HAL_StatusTypeDef     HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void                  HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);

#if defined(STM32F042x6) || defined(STM32F048xx) ||                         \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)
void                  HAL_RCCEx_CRSConfig(RCC_CRSInitTypeDef *pInit);
void                  HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void);
void                  HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo);
uint32_t              HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout);
#endif /* STM32F042x6 || STM32F048xx || */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */


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

#endif /* __STM32F0xx_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
