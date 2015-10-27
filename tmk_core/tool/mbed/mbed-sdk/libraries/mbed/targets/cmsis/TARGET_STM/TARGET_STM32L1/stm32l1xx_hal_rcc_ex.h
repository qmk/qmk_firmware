/**
  ******************************************************************************
  * @file    stm32l1xx_hal_rcc_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
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
#ifndef __STM32L1xx_HAL_RCC_EX_H
#define __STM32L1xx_HAL_RCC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
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
typedef struct
{
  uint32_t PeriphClockSelection;                /*!< The Extended Clock to be configured.
                                      This parameter can be a value of @ref RCCEx_Periph_Clock_Selection */

  uint32_t RTCClockSelection;         /*!< specifies the RTC clock source.
                                       This parameter can be a value of @ref RCC_RTC_LCD_Clock_Source */

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)

  uint32_t LCDClockSelection;         /*!< specifies the LCD clock source.
                                       This parameter can be a value of @ref RCC_RTC_LCD_Clock_Source */

#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */
} RCC_PeriphCLKInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_Periph_Clock_Selection RCCEx Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_RTC           ((uint32_t)0x00000001)

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)

#define RCC_PERIPHCLK_LCD           ((uint32_t)0x00000002)

#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)

#define IS_RCC_PERIPHCLOCK(__CLK__) ((RCC_PERIPHCLK_RTC <= (__CLK__)) && ((__CLK__) <= RCC_PERIPHCLK_LCD))

#else /* Not LCD LINE */

#define IS_RCC_PERIPHCLOCK(__CLK__) ((__CLK__) == RCC_PERIPHCLK_RTC)

#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */
/**
  * @}
  */

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

/* Alias word address of LSECSSON bit */
#define LSECSSON_BITNUMBER      POSITION_VAL(RCC_CSR_LSECSSON)
#define CSR_LSECSSON_BB         ((uint32_t)(PERIPH_BB_BASE + (RCC_CSR_OFFSET_BB * 32) + (LSECSSON_BITNUMBER * 4)))

#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE*/

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
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
#if defined (STM32L151xB) || defined (STM32L152xB) || \
    defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
#define __GPIOE_CLK_ENABLE()    (RCC->AHBENR |= (RCC_AHBENR_GPIOEEN))
#define __GPIOE_CLK_DISABLE()   (RCC->AHBENR &= ~(RCC_AHBENR_GPIOEEN))

#endif /* STM32L151xB || STM32L152xB || ... || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __GPIOF_CLK_ENABLE()    (RCC->AHBENR |= (RCC_AHBENR_GPIOFEN))
#define __GPIOG_CLK_ENABLE()    (RCC->AHBENR |= (RCC_AHBENR_GPIOGEN))

#define __GPIOF_CLK_DISABLE()   (RCC->AHBENR &= ~(RCC_AHBENR_GPIOFEN))
#define __GPIOG_CLK_DISABLE()   (RCC->AHBENR &= ~(RCC_AHBENR_GPIOGEN))

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
#define __DMA2_CLK_ENABLE()     (RCC->AHBENR |= (RCC_AHBENR_DMA2EN))
#define __DMA2_CLK_DISABLE()    (RCC->AHBENR &= ~(RCC_AHBENR_DMA2EN))

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L162xC) || defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L162xE)

#define __CRYP_CLK_ENABLE()     (RCC->AHBENR |= (RCC_AHBENR_AESEN))
#define __CRYP_CLK_DISABLE()    (RCC->AHBENR &= ~(RCC_AHBENR_AESEN))

#endif /* STM32L162xC || STM32L162xCA || STM32L162xD || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
  
#define __FSMC_CLK_ENABLE()     (RCC->AHBENR |= (RCC_AHBENR_FSMCEN))
#define __FSMC_CLK_DISABLE()    (RCC->AHBENR &= ~(RCC_AHBENR_FSMCEN))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)
    
#define __LCD_CLK_ENABLE()        (RCC->APB1ENR |= (RCC_APB1ENR_LCDEN))
#define __LCD_CLK_DISABLE()       (RCC->APB1ENR &= ~(RCC_APB1ENR_LCDEN))

#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */

/** @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it. 
  */
#if defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __TIM5_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_TIM5EN))
#define __TIM5_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM5EN))

#endif /* STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __SPI3_CLK_ENABLE()     (RCC->APB1ENR |= (RCC_APB1ENR_SPI3EN))
#define __SPI3_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __UART4_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_UART4EN))
#define __UART5_CLK_ENABLE()    (RCC->APB1ENR |= (RCC_APB1ENR_UART5EN))

#define __UART4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_UART4EN))
#define __UART5_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_UART5EN))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)

#define __OPAMP_CLK_ENABLE()      __COMP_CLK_ENABLE()   /* Peripherals COMP and OPAMP share the same clock domain */
#define __OPAMP_CLK_DISABLE()     __COMP_CLK_DISABLE()  /* Peripherals COMP and OPAMP share the same clock domain */
      
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE || STM32L162xC || STM32L152xC || STM32L151xC */
      
/** @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)

#define __SDIO_CLK_ENABLE()     (RCC->APB2ENR |= (RCC_APB2ENR_SDIOEN))
#define __SDIO_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_SDIOEN))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

/**
    * @}
    */
  

/** @defgroup RCCEx_Force_Release_Peripheral_Reset RCCEx Force Release Peripheral Reset
  * @brief  Forces or releases AHB peripheral reset.
  * @{
  */  
#if defined (STM32L151xB) || defined (STM32L152xB) || \
    defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
#define __GPIOE_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOERST))
#define __GPIOE_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOERST))

#endif /* STM32L151xB || STM32L152xB || ... || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __GPIOF_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOFRST))
#define __GPIOG_FORCE_RESET()   (RCC->AHBRSTR |= (RCC_AHBRSTR_GPIOGRST))

#define __GPIOF_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOFRST))
#define __GPIOG_RELEASE_RESET() (RCC->AHBRSTR &= ~(RCC_AHBRSTR_GPIOGRST))

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
#define __DMA2_FORCE_RESET()    (RCC->AHBRSTR |= (RCC_AHBRSTR_DMA2RST))
#define __DMA2_RELEASE_RESET()  (RCC->AHBRSTR &= ~(RCC_AHBRSTR_DMA2RST))

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L162xC) || defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L162xE)

#define __CRYP_FORCE_RESET()     (RCC->AHBRSTR |= (RCC_AHBRSTR_AESRST))
#define __CRYP_RELEASE_RESET()   (RCC->AHBRSTR &= ~(RCC_AHBRSTR_AESRST))

#endif /* STM32L162xC || STM32L162xCA || STM32L162xD || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
  
#define __FSMC_FORCE_RESET()    (RCC->AHBRSTR |= (RCC_AHBRSTR_FSMCRST))
#define __FSMC_RELEASE_RESET()  (RCC->AHBRSTR &= ~(RCC_AHBRSTR_FSMCRST))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)
    
#define __LCD_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_LCDRST))
#define __LCD_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_LCDRST))

#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */

/** @brief  Forces or releases APB1 peripheral reset.
  */
#if defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
      defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
      defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __TIM5_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM5RST))
#define __TIM5_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM5RST))

#endif /* STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __SPI3_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __SPI3_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __UART4_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_UART4RST))
#define __UART5_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_UART5RST))

#define __UART4_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART4RST))
#define __UART5_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART5RST))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)

#define __OPAMP_FORCE_RESET()     __COMP_FORCE_RESET()   /* Peripherals COMP and OPAMP share the same clock domain */
#define __OPAMP_RELEASE_RESET()   __COMP_RELEASE_RESET() /* Peripherals COMP and OPAMP share the same clock domain */
      
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE || STM32L162xC || STM32L152xC || STM32L151xC */
      
/** @brief  Forces or releases APB2 peripheral reset.
  */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)

#define __SDIO_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_SDIORST))
#define __SDIO_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDIORST))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

/**
  * @}
  */

/** @defgroup RCCEx_Peripheral_Clock_Sleep_Enable_Disable RCCEx Peripheral Clock Sleep Enable Disable
  * @brief  Enables or disables the AHB1 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  * @{
  */
#if defined (STM32L151xB) || defined (STM32L152xB) || \
    defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
#define __GPIOE_CLK_SLEEP_ENABLE()  (RCC->AHBLPENR |= (RCC_AHBLPENR_GPIOELPEN))
#define __GPIOE_CLK_SLEEP_DISABLE() (RCC->AHBLPENR &= ~(RCC_AHBLPENR_GPIOELPEN))

#endif /* STM32L151xB || STM32L152xB || ... || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __GPIOF_CLK_SLEEP_ENABLE()  (RCC->AHBLPENR |= (RCC_AHBLPENR_GPIOFLPEN))
#define __GPIOG_CLK_SLEEP_ENABLE()  (RCC->AHBLPENR |= (RCC_AHBLPENR_GPIOGLPEN))

#define __GPIOF_CLK_SLEEP_DISABLE() (RCC->AHBLPENR &= ~(RCC_AHBLPENR_GPIOFLPEN))
#define __GPIOG_CLK_SLEEP_DISABLE() (RCC->AHBLPENR &= ~(RCC_AHBLPENR_GPIOGLPEN))

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
#define __DMA2_CLK_SLEEP_ENABLE()   (RCC->AHBLPENR |= (RCC_AHBLPENR_DMA2LPEN))
#define __DMA2_CLK_SLEEP_DISABLE()  (RCC->AHBLPENR &= ~(RCC_AHBLPENR_DMA2LPEN))

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L162xC) || defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L162xE)

#define __CRYP_CLK_SLEEP_ENABLE()    (RCC->AHBLPENR |= (RCC_AHBLPENR_AESLPEN))
#define __CRYP_CLK_SLEEP_DISABLE()   (RCC->AHBLPENR &= ~(RCC_AHBLPENR_AESLPEN))

#endif /* STM32L162xC || STM32L162xCA || STM32L162xD || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
  
#define __FSMC_CLK_SLEEP_ENABLE()   (RCC->AHBLPENR |= (RCC_AHBLPENR_FSMCLPEN))
#define __FSMC_CLK_SLEEP_DISABLE()  (RCC->AHBLPENR &= ~(RCC_AHBLPENR_FSMCLPEN))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)
    
#define __LCD_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_LCDLPEN))
#define __LCD_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_LCDLPEN))

#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */

/** @brief  Enables or disables the APB1 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *           power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  */
#if defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __TIM5_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM5LPEN))
#define __TIM5_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM5LPEN))

#endif /* STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __SPI3_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI3LPEN))
#define __SPI3_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI3LPEN))

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

#define __UART4_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_UART4LPEN))
#define __UART5_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_UART5LPEN))

#define __UART4_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART4LPEN))
#define __UART5_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART5LPEN))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/** @brief  Enables or disables the APB2 peripheral clock during Low Power (Sleep) mode.
  * @note   Peripheral clock gating in SLEEP mode can be used to further reduce
  *           power consumption.
  * @note   After wakeup from SLEEP mode, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode.
  */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)

#define __SDIO_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_SDIOLPEN))
#define __SDIO_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SDIOLPEN))

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

/**
  * @}
  */

#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)
    

/** @brief Macro to configures LCD clock (LCDCLK).
  *  @note   LCD and RTC use the same configuration
  *  @note   LCD can however be used in the Stop low power mode if the LSE or LSI is used as the
  *   LCD clock source.
  *    
  *  @param  __LCD_CLKSOURCE__: specifies the LCD clock source.
  *          This parameter can be one of the following values:
  *             @arg RCC_RTCCLKSOURCE_LSE: LSE selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_LSI: LSI selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_HSE_DIV2: HSE divided by 2 selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_HSE_DIV4: HSE divided by 4 selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_HSE_DIV8: HSE divided by 8 selected as RTC clock
  *             @arg RCC_RTCCLKSOURCE_HSE_DIV16: HSE divided by 16 selected as RTC clock
  */
#define __HAL_RCC_LCD_CONFIG(__LCD_CLKSOURCE__) __HAL_RCC_RTC_CONFIG(__LCD_CLKSOURCE__)

/** @brief macros to get the LCD clock source.
  */
#define __HAL_RCC_GET_LCD_SOURCE()              __HAL_RCC_GET_RTC_SOURCE()

#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);

#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

void              HAL_RCCEx_EnableLSECSS(void);
void              HAL_RCCEx_DisableLSECSS(void);

#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE*/

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

#endif /* __STM32L1xx_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
