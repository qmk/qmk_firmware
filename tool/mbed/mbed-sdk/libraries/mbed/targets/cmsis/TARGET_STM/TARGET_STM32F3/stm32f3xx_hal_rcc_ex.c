/**
  ******************************************************************************
  * @file    stm32f3xx_hal_rcc_ex.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Extended RCC HAL module driver
  *          This file provides firmware functions to manage the following 
  *          functionalities RCC Extended peripheral:
  *           + Extended Clock Source configuration functions
  *  
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

/** @defgroup RCCEx RCC Extended HAL module driver
  * @brief RCC Extended HAL module driver.
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup RCCEx_Private_Define RCC Extended Private Define
  * @{
  */
#define HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define LSI_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define PLL_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define CLOCKSWITCH_TIMEOUT_VALUE  ((uint32_t)5000) /* 5 s    */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup RCCEx_Private_Variables RCC Extented Private Variables
  * @{
  */
const uint8_t PLLMULFactorTable[16] = { 2,  3,  4,  5,  6,  7,  8,  9,
                                       10, 11, 12, 13, 14, 15, 16, 16};
const uint8_t PredivFactorTable[16] = { 1, 2,  3,  4,  5,  6,  7,  8,
                                         9,10, 11, 12, 13, 14, 15, 16};
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Functions RCC Extended Exported Functions
  * @{
  */

/** @defgroup RCCEx_Exported_Functions_Group1 Extended Peripheral Control functions 
  * @brief    Extended Peripheral Control functions
  *
@verbatim   
 ===============================================================================
                ##### Extended Peripheral Control functions  #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks 
    frequencies.
    [..] 
    (@) Important note: Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to
        select the RTC clock source; in this case the Backup domain will be reset in  
        order to modify the RTC Clock source, as consequence RTC registers (including 
        the backup registers) and RCC_BDCR register are set to their reset values.
      
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the RCC extended peripherals clocks according to the specified
  *         parameters in the RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit: pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         contains the configuration information for the Extended Peripherals clocks
  *         (ADC, CEC, I2C, I2S, SDADC, HRTIM, TIM, USART, RTC and USB).
  *
  * @note   Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select 
  *         the RTC clock source; in this case the Backup domain will be reset in  
  *         order to modify the RTC Clock source, as consequence RTC registers (including 
  *         the backup registers) and RCC_BDCR register are set to their reset values.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0;
  uint32_t tmpreg = 0;
    
  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLK(PeriphClkInit->PeriphClockSelection));
  
   
  /*---------------------------- RTC configuration -------------------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == (RCC_PERIPHCLK_RTC))
  {
    /* Enable Power Clock*/
    __PWR_CLK_ENABLE();
    
    /* Enable write access to Backup domain */
    SET_BIT(PWR->CR, PWR_CR_DBP);
    
    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();
    
    while((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if((HAL_GetTick()-tickstart) > DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }      
    }
    
    /* Reset the Backup domain only if the RTC Clock source selction is modified */ 
    if((RCC->BDCR & RCC_BDCR_RTCSEL) != (PeriphClkInit->RTCClockSelection & RCC_BDCR_RTCSEL))
    {
      /* Store the content of BDCR register before the reset of Backup Domain */
      tmpreg = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));
      /* RTC Clock selection can be changed only if the Backup Domain is reset */
      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();
      /* Restore the Content of BDCR register */
      RCC->BDCR = tmpreg;
    }
    
    /* If LSE is selected as RTC clock source, wait for LSE reactivation */
    if(PeriphClkInit->RTCClockSelection == RCC_RTCCLKSOURCE_LSE)
    {
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
      if((HAL_GetTick()-tickstart) > LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }      
      }  
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection); 
  }
  
  /*------------------------------- USART1 Configuration ------------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART1) == RCC_PERIPHCLK_USART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART1CLKSOURCE(PeriphClkInit->Usart1ClockSelection));
    
    /* Configure the USART1 clock source */
    __HAL_RCC_USART1_CONFIG(PeriphClkInit->Usart1ClockSelection);
  }
  
  /*----------------------------- USART2 Configuration --------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART2CLKSOURCE(PeriphClkInit->Usart2ClockSelection));
    
    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(PeriphClkInit->Usart2ClockSelection);
  }
  
  /*------------------------------ USART3 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART3) == RCC_PERIPHCLK_USART3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART3CLKSOURCE(PeriphClkInit->Usart3ClockSelection));
    
    /* Configure the USART3 clock source */
    __HAL_RCC_USART3_CONFIG(PeriphClkInit->Usart3ClockSelection);
  }

  /*------------------------------ I2C1 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(PeriphClkInit->I2c1ClockSelection));
    
    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(PeriphClkInit->I2c1ClockSelection);
  }

#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F302x8)                         || \
    defined(STM32F373xC)
  /*------------------------------ USB Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USB) == RCC_PERIPHCLK_USB)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USBCLKSOURCE(PeriphClkInit->USBClockSelection));
    
    /* Configure the USB clock source */
    __HAL_RCC_USB_CONFIG(PeriphClkInit->USBClockSelection);
  }

#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302xC || STM32F303xC || */
       /* STM32F302x8                || */
       /* STM32F373xC                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)

  /*------------------------------ I2C2 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C2) == RCC_PERIPHCLK_I2C2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C2CLKSOURCE(PeriphClkInit->I2c2ClockSelection));
    
    /* Configure the I2C2 clock source */
    __HAL_RCC_I2C2_CONFIG(PeriphClkInit->I2c2ClockSelection);
  }

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F373xC || STM32F378xx                   */
  
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

  /*------------------------------ I2C3 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C3) == RCC_PERIPHCLK_I2C3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLKSOURCE(PeriphClkInit->I2c3ClockSelection));
    
    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(PeriphClkInit->I2c3ClockSelection);
  }
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
  
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)

  /*------------------------------ UART4 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_UART4) == RCC_PERIPHCLK_UART4)
  {
    /* Check the parameters */
    assert_param(IS_RCC_UART4CLKSOURCE(PeriphClkInit->Uart4ClockSelection));
    
    /* Configure the UART4 clock source */
    __HAL_RCC_UART4_CONFIG(PeriphClkInit->Uart4ClockSelection);
  }

  /*------------------------------ UART5 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_UART5) == RCC_PERIPHCLK_UART5)
  {
    /* Check the parameters */
    assert_param(IS_RCC_UART5CLKSOURCE(PeriphClkInit->Uart5ClockSelection));
    
    /* Configure the UART5 clock source */
    __HAL_RCC_UART5_CONFIG(PeriphClkInit->Uart5ClockSelection);
  }

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
  /*------------------------------ I2S Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S) == RCC_PERIPHCLK_I2S)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2SCLKSOURCE(PeriphClkInit->I2sClockSelection));
    
    /* Configure the I2S clock source */
    __HAL_RCC_I2S_CONFIG(PeriphClkInit->I2sClockSelection);
  }

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
  
#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
      
  /*------------------------------ ADC1 clock Configuration ------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC1) == RCC_PERIPHCLK_ADC1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADC1PLLCLK_DIV(PeriphClkInit->Adc1ClockSelection));
    
    /* Configure the ADC1 clock source */
    __HAL_RCC_ADC1_CONFIG(PeriphClkInit->Adc1ClockSelection);
  }

#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */
  
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
      
  /*------------------------------ ADC1 & ADC2 clock Configuration -------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC12) == RCC_PERIPHCLK_ADC12)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADC12PLLCLK_DIV(PeriphClkInit->Adc12ClockSelection));
    
    /* Configure the ADC12 clock source */
    __HAL_RCC_ADC12_CONFIG(PeriphClkInit->Adc12ClockSelection);
  }

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx    */    
  
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)

  /*------------------------------ ADC3 & ADC4 clock Configuration -------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC34) == RCC_PERIPHCLK_ADC34)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADC34PLLCLK_DIV(PeriphClkInit->Adc34ClockSelection));
    
    /* Configure the ADC34 clock source */
    __HAL_RCC_ADC34_CONFIG(PeriphClkInit->Adc34ClockSelection);
  }

#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F373xC) || defined(STM32F378xx)
      
  /*------------------------------ ADC1 clock Configuration ------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC1) == RCC_PERIPHCLK_ADC1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADC1PCLK2_DIV(PeriphClkInit->Adc1ClockSelection));
    
    /* Configure the ADC1 clock source */
    __HAL_RCC_ADC1_CONFIG(PeriphClkInit->Adc1ClockSelection);
  }

#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

  /*------------------------------ TIM1 clock Configuration ----------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM1) == RCC_PERIPHCLK_TIM1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM1CLKSOURCE(PeriphClkInit->Tim1ClockSelection));
    
    /* Configure the TIM1 clock source */
    __HAL_RCC_TIM1_CONFIG(PeriphClkInit->Tim1ClockSelection);
  }

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
  
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)

  /*------------------------------ TIM8 clock Configuration ----------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM8) == RCC_PERIPHCLK_TIM8)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM8CLKSOURCE(PeriphClkInit->Tim8ClockSelection));
    
    /* Configure the TIM8 clock source */
    __HAL_RCC_TIM8_CONFIG(PeriphClkInit->Tim8ClockSelection);
  }

#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

  /*------------------------------ TIM15 clock Configuration ----------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM15) == RCC_PERIPHCLK_TIM15)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM15CLKSOURCE(PeriphClkInit->Tim15ClockSelection));
    
    /* Configure the TIM15 clock source */
    __HAL_RCC_TIM15_CONFIG(PeriphClkInit->Tim15ClockSelection);
  }

  /*------------------------------ TIM16 clock Configuration ----------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM16) == RCC_PERIPHCLK_TIM16)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM16CLKSOURCE(PeriphClkInit->Tim16ClockSelection));
    
    /* Configure the TIM16 clock source */
    __HAL_RCC_TIM16_CONFIG(PeriphClkInit->Tim16ClockSelection);
  }

  /*------------------------------ TIM17 clock Configuration ----------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM17) == RCC_PERIPHCLK_TIM17)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM17CLKSOURCE(PeriphClkInit->Tim17ClockSelection));
    
    /* Configure the TIM17 clock source */
    __HAL_RCC_TIM17_CONFIG(PeriphClkInit->Tim17ClockSelection);
  }

#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F334x8)

  /*------------------------------ HRTIM1 clock Configuration ----------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_HRTIM1) == RCC_PERIPHCLK_HRTIM1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HRTIM1CLKSOURCE(PeriphClkInit->Hrtim1ClockSelection));
    
    /* Configure the HRTIM1 clock source */
    __HAL_RCC_HRTIM1_CONFIG(PeriphClkInit->Hrtim1ClockSelection);
  }

#endif /* STM32F334x8 */

#if defined(STM32F373xC) || defined(STM32F378xx)
  
  /*------------------------------ SDADC clock Configuration -------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SDADC) == RCC_PERIPHCLK_SDADC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SDADCSYSCLK_DIV(PeriphClkInit->SdadcClockSelection));
    
    /* Configure the SDADC clock prescaler */
    __HAL_RCC_SDADC_CONFIG(PeriphClkInit->SdadcClockSelection);
  }

  /*------------------------------ CEC clock Configuration -------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CEC) == RCC_PERIPHCLK_CEC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_CECCLKSOURCE(PeriphClkInit->CecClockSelection));
    
    /* Configure the CEC clock source */
    __HAL_RCC_CEC_CONFIG(PeriphClkInit->CecClockSelection);
  }

#endif /* STM32F373xC || STM32F378xx */
  
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
  
  /*------------------------------ TIM2 clock Configuration -------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM2) == RCC_PERIPHCLK_TIM2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM2CLKSOURCE(PeriphClkInit->Tim2ClockSelection));
    
    /* Configure the CEC clock source */
    __HAL_RCC_TIM2_CONFIG(PeriphClkInit->Tim2ClockSelection);
  }

  /*------------------------------ TIM3 clock Configuration -------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM34) == RCC_PERIPHCLK_TIM34)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM3CLKSOURCE(PeriphClkInit->Tim34ClockSelection));
    
    /* Configure the CEC clock source */
    __HAL_RCC_TIM34_CONFIG(PeriphClkInit->Tim34ClockSelection);
  }

  /*------------------------------ TIM15 clock Configuration ------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM15) == RCC_PERIPHCLK_TIM15)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM15CLKSOURCE(PeriphClkInit->Tim15ClockSelection));
    
    /* Configure the CEC clock source */
    __HAL_RCC_TIM15_CONFIG(PeriphClkInit->Tim15ClockSelection);
  }

  /*------------------------------ TIM16 clock Configuration ------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM16) == RCC_PERIPHCLK_TIM16)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM16CLKSOURCE(PeriphClkInit->Tim16ClockSelection));
    
    /* Configure the CEC clock source */
    __HAL_RCC_TIM16_CONFIG(PeriphClkInit->Tim16ClockSelection);
  }

  /*------------------------------ TIM17 clock Configuration ------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM17) == RCC_PERIPHCLK_TIM17)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM17CLKSOURCE(PeriphClkInit->Tim17ClockSelection));
    
    /* Configure the CEC clock source */
    __HAL_RCC_TIM17_CONFIG(PeriphClkInit->Tim17ClockSelection);
  }

#endif /* STM32F302xE || STM32F303xE || STM32F398xx */  

#if defined(STM32F303xE) || defined(STM32F398xx)
  /*------------------------------ TIM20 clock Configuration ------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM20) == RCC_PERIPHCLK_TIM20)
  {
    /* Check the parameters */
    assert_param(IS_RCC_TIM20CLKSOURCE(PeriphClkInit->Tim20ClockSelection));
    
    /* Configure the CEC clock source */
    __HAL_RCC_TIM20_CONFIG(PeriphClkInit->Tim20ClockSelection);
  }
#endif /* STM32F303xE || STM32F398xx */  

  
  return HAL_OK;
}

/**
  * @brief  Get the RCC_ClkInitStruct according to the internal
  * RCC configuration registers.
  * @param  PeriphClkInit: pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals clocks
  *         (ADC, CEC, I2C, I2S, SDADC, HRTIM, TIM, USART, RTC and USB clocks).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/
  /* Common part first */
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                        RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_RTC;
  
  /* Get the RTC configuration --------------------------------------------*/
  PeriphClkInit->RTCClockSelection = __HAL_RCC_GET_RTC_SOURCE();
  /* Get the USART1 clock configuration --------------------------------------------*/
  PeriphClkInit->Usart1ClockSelection = __HAL_RCC_GET_USART1_SOURCE();
  /* Get the USART2 clock configuration -----------------------------------------*/
  PeriphClkInit->Usart2ClockSelection = __HAL_RCC_GET_USART2_SOURCE();
   /* Get the USART3 clock configuration -----------------------------------------*/
  PeriphClkInit->Usart3ClockSelection = __HAL_RCC_GET_USART3_SOURCE();
  /* Get the I2C1 clock configuration -----------------------------------------*/
  PeriphClkInit->I2c1ClockSelection = __HAL_RCC_GET_I2C1_SOURCE();

#if defined(STM32F302xE) || defined(STM32F303xE) || \
    defined(STM32F302xC) || defined(STM32F303xC) || \
    defined(STM32F302x8)                         || \
    defined(STM32F373xC)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_USB;
  /* Get the USB clock configuration -----------------------------------------*/
  PeriphClkInit->USBClockSelection = __HAL_RCC_GET_USB_SOURCE();

#endif /* STM32F302xE || STM32F303xE || */
       /* STM32F302xC || STM32F303xC || */
       /* STM32F302x8                || */
       /* STM32F373xC                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_I2C2;
  /* Get the I2C2 clock configuration -----------------------------------------*/
  PeriphClkInit->I2c2ClockSelection = __HAL_RCC_GET_I2C2_SOURCE();

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F373xC || STM32F378xx                   */
  
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_I2C3;
  /* Get the I2C3 clock configuration -----------------------------------------*/
  PeriphClkInit->I2c3ClockSelection = __HAL_RCC_GET_I2C3_SOURCE();

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
  
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) ||defined(STM32F358xx)

  PeriphClkInit->PeriphClockSelection |= (RCC_PERIPHCLK_UART4  | RCC_PERIPHCLK_UART5);
  /* Get the UART4 clock configuration -----------------------------------------*/
  PeriphClkInit->Uart4ClockSelection = __HAL_RCC_GET_UART4_SOURCE();
  /* Get the UART5 clock configuration -----------------------------------------*/
  PeriphClkInit->Uart5ClockSelection = __HAL_RCC_GET_UART5_SOURCE();

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_I2S;
  /* Get the I2S clock configuration -----------------------------------------*/
  PeriphClkInit->I2sClockSelection = __HAL_RCC_GET_I2S_SOURCE();

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
  
#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
      
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_ADC1;
  /* Get the ADC1 clock configuration -----------------------------------------*/
  PeriphClkInit->Adc1ClockSelection = __HAL_RCC_GET_ADC1_SOURCE();

#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_ADC12;
  /* Get the ADC1 & ADC2 clock configuration -----------------------------------------*/
  PeriphClkInit->Adc12ClockSelection = __HAL_RCC_GET_ADC12_SOURCE();

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx    */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_ADC34;
   /* Get the ADC3 & ADC4 clock configuration -----------------------------------------*/
  PeriphClkInit->Adc34ClockSelection = __HAL_RCC_GET_ADC34_SOURCE();

#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM1;
  /* Get the TIM1 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim1ClockSelection = __HAL_RCC_GET_TIM1_SOURCE();

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
  
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM8;
  /* Get the TIM8 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim8ClockSelection = __HAL_RCC_GET_TIM8_SOURCE();

#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)

  PeriphClkInit->PeriphClockSelection |= (RCC_PERIPHCLK_TIM15 | RCC_PERIPHCLK_TIM16 | RCC_PERIPHCLK_TIM17);
  /* Get the TIM15 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim15ClockSelection = __HAL_RCC_GET_TIM15_SOURCE();
  /* Get the TIM16 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim16ClockSelection = __HAL_RCC_GET_TIM16_SOURCE();
  /* Get the TIM17 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim17ClockSelection = __HAL_RCC_GET_TIM17_SOURCE();

#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx */

#if defined(STM32F334x8)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_HRTIM1;
  /* Get the HRTIM1 clock configuration -----------------------------------------*/
  PeriphClkInit->Hrtim1ClockSelection = __HAL_RCC_GET_HRTIM1_SOURCE();

#endif /* STM32F334x8 */

#if defined(STM32F373xC) || defined(STM32F378xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_SDADC;
  /* Get the SDADC clock configuration -----------------------------------------*/
  PeriphClkInit->SdadcClockSelection = __HAL_RCC_GET_SDADC_SOURCE();

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_CEC;
  /* Get the CEC clock configuration -----------------------------------------*/
  PeriphClkInit->CecClockSelection = __HAL_RCC_GET_CEC_SOURCE();

#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM2;
  /* Get the TIM2 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim2ClockSelection = __HAL_RCC_GET_TIM2_SOURCE();

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM34;
  /* Get the TIM3 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim34ClockSelection = __HAL_RCC_GET_TIM34_SOURCE();

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM15;
  /* Get the TIM15 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim15ClockSelection = __HAL_RCC_GET_TIM15_SOURCE();

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM16;
  /* Get the TIM16 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim16ClockSelection = __HAL_RCC_GET_TIM16_SOURCE();

  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM17;
  /* Get the TIM17 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim17ClockSelection = __HAL_RCC_GET_TIM17_SOURCE();

#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
  
#if defined (STM32F303xE) || defined(STM32F398xx)
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_TIM20;
  /* Get the TIM20 clock configuration -----------------------------------------*/
  PeriphClkInit->Tim20ClockSelection = __HAL_RCC_GET_TIM20_SOURCE();
#endif /* STM32F303xE || STM32F398xx */
}

/**
  * @brief  Initializes the RCC Oscillators according to the specified parameters in the
  *         RCC_OscInitTypeDef.
  * @param  RCC_OscInitStruct: pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @note   The PLL is not disabled when used as system clock.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  uint32_t tickstart = 0;

  /* Check the parameters */
  assert_param(RCC_OscInitStruct != HAL_NULL);
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));
  /*------------------------------- HSE Configuration ------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));
    /* When the HSE is used as system clock or clock source for PLL in these cases HSE will not disabled */
    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HSE) ||
       ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSE)))
    {
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET) && (RCC_OscInitStruct->HSEState != RCC_HSE_ON))
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Reset HSEON and HSEBYP bits before configuring the HSE --------------*/
      __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF);
      
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till HSE is bypassed or disabled */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
      {
        if((HAL_GetTick()-tickstart) > HSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

      /* Set the new HSE configuration ---------------------------------------*/
      __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
      /* Configure the HSE predivision factor --------------------------------*/
      __HAL_RCC_HSE_PREDIV_CONFIG(RCC_OscInitStruct->HSEPredivValue);
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
       /* STM32F373xC || STM32F378xx                   */

      /* Check the HSE State */
      if(RCC_OscInitStruct->HSEState == RCC_HSE_ON)
      {
        /* Get timeout */
        tickstart = HAL_GetTick();
        
        /* Wait till HSE is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
        {
          if((HAL_GetTick()-tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Get timeout */
        tickstart = HAL_GetTick();

        /* Wait till HSE is bypassed or disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
        {
          if((HAL_GetTick()-tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }
  /*----------------------------- HSI Configuration --------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI(RCC_OscInitStruct->HSIState));
    assert_param(IS_RCC_CALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

    /* Check if HSI is used as system clock or as PLL source when PLL is selected as system clock */    
    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HSI) ||
       ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSI)))
    {
      /* When the HSI is used as system clock it is not allowed to be disabled */
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET) && (RCC_OscInitStruct->HSIState != RCC_HSI_ON))
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
      else
      {
        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
    }
    else
    {
      /* Check the HSI State */
      if(RCC_OscInitStruct->HSIState != RCC_HSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_ENABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();

        /* Wait till HSI is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
        {
          if((HAL_GetTick()-tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }      
        } 

        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
      else
      {
        /* Disable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_DISABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till HSI is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET)
        {
          if((HAL_GetTick()-tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }
  /*------------------------------ LSI Configuration -------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSI(RCC_OscInitStruct->LSIState));

    /* Check the LSI State */
    if(RCC_OscInitStruct->LSIState != RCC_LSI_OFF)
    {
      /* Enable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_ENABLE();
      
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till LSI is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET)
      {
        if((HAL_GetTick()-tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Disable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_DISABLE();
      
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till LSI is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) != RESET)
      {
        if((HAL_GetTick()-tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }
  /*------------------------------ LSE Configuration -------------------------*/
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));
    
    /* Enable Power Clock*/
    __PWR_CLK_ENABLE();
    
    /* Enable write access to Backup domain */
    SET_BIT(PWR->CR, PWR_CR_DBP);
    
    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();
    
    while((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if((HAL_GetTick()-tickstart) > DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }      
    }

    /* Reset LSEON and LSEBYP bits before configuring the LSE ----------------*/
    __HAL_RCC_LSE_CONFIG(RCC_LSE_OFF);
    
    /* Get timeout */
    tickstart = HAL_GetTick();
      
    /* Wait till LSE is ready */  
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != RESET)
    {
      if((HAL_GetTick()-tickstart) > LSE_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    /* Set the new LSE configuration -----------------------------------------*/
    __HAL_RCC_LSE_CONFIG(RCC_OscInitStruct->LSEState);
    /* Check the LSE State */
    if(RCC_OscInitStruct->LSEState == RCC_LSE_ON)
    {
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
        if((HAL_GetTick()-tickstart) > LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != RESET)
      {
        if((HAL_GetTick()-tickstart) > LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }
  /*-------------------------------- PLL Configuration -----------------------*/
  /* Check the parameters */
  assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL.PLLState));
  if ((RCC_OscInitStruct->PLL.PLLState) != RCC_PLL_NONE)
  {
    /* Check if the PLL is used as system clock or not */
    if(__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
    {
      if((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_ON)
      {
        /* Check the parameters */
        assert_param(IS_RCC_PLLSOURCE(RCC_OscInitStruct->PLL.PLLSource));
        assert_param(IS_RCC_PLL_MUL(RCC_OscInitStruct->PLL.PLLMUL));
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
        assert_param(IS_RCC_PREDIV(RCC_OscInitStruct->PLL.PREDIV));
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();
        
        /* Wait till PLL is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
        {
          if((HAL_GetTick()-tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
      /* Configure the main PLL clock source and multiplication factor. */
      __HAL_RCC_PLL_CONFIG(RCC_OscInitStruct->PLL.PLLSource,
                           RCC_OscInitStruct->PLL.PLLMUL);
#else
        /* Configure the main PLL clock source, predivider and multiplication factor. */
        __HAL_RCC_PLL_CONFIG(RCC_OscInitStruct->PLL.PLLSource,
                             RCC_OscInitStruct->PLL.PREDIV,
                             RCC_OscInitStruct->PLL.PLLMUL);
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
       /* STM32F373xC || STM32F378xx                   */
        
        /* Enable the main PLL. */
        __HAL_RCC_PLL_ENABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till PLL is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
        {
          if((HAL_GetTick()-tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();
        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till PLL is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
        {
          if((HAL_GetTick()-tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    else
    {
      return HAL_ERROR;
    }
  }
  return HAL_OK;
}

/**
  * @brief  Configures the RCC_OscInitStruct according to the internal
  * RCC configuration registers.
  * @param  RCC_OscInitStruct: pointer to an RCC_OscInitTypeDef structure that
  * will be configured.
  * @retval None
  */
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  /* Check the parameters */
  assert_param(RCC_OscInitStruct != HAL_NULL);

  /* Set all possible values for the Oscillator type parameter ---------------*/
  RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI;

  /* Get the HSE configuration -----------------------------------------------*/
  if((RCC->CR & RCC_CR_HSEBYP) == RCC_CR_HSEBYP)
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_BYPASS;
  }
  else if((RCC->CR & RCC_CR_HSEON) == RCC_CR_HSEON)
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_ON;
  }
  else
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_OFF;
  }
  
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
  RCC_OscInitStruct->HSEPredivValue = (uint32_t)(RCC->CFGR2 & RCC_CFGR2_PREDIV);
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
       /* STM32F373xC || STM32F378xx                   */

  /* Get the HSI configuration -----------------------------------------------*/
  if((RCC->CR & RCC_CR_HSION) == RCC_CR_HSION)
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_ON;
  }
  else
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_OFF;
  }

  RCC_OscInitStruct->HSICalibrationValue = (uint32_t)((RCC->CR &RCC_CR_HSITRIM) >> POSITION_VAL(RCC_CR_HSITRIM));

  /* Get the LSE configuration -----------------------------------------------*/
  if((RCC->BDCR & RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_BYPASS;
  }
  else if((RCC->BDCR & RCC_BDCR_LSEON) == RCC_BDCR_LSEON)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_ON;
  }
  else
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_OFF;
  }

  /* Get the LSI configuration -----------------------------------------------*/
  if((RCC->CSR & RCC_CSR_LSION) == RCC_CSR_LSION)
  {
    RCC_OscInitStruct->LSIState = RCC_LSI_ON;
  }
  else
  {
    RCC_OscInitStruct->LSIState = RCC_LSI_OFF;
  }

  /* Get the PLL configuration -----------------------------------------------*/
  if((RCC->CR & RCC_CR_PLLON) == RCC_CR_PLLON)
  {
    RCC_OscInitStruct->PLL.PLLState = RCC_PLL_ON;
  }
  else
  {
    RCC_OscInitStruct->PLL.PLLState = RCC_PLL_OFF;
  }
  
  RCC_OscInitStruct->PLL.PLLSource = (uint32_t)(RCC->CFGR & RCC_CFGR_PLLSRC);
  RCC_OscInitStruct->PLL.PLLMUL = (uint32_t)(RCC->CFGR & RCC_CFGR_PLLMUL);
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
  RCC_OscInitStruct->PLL.PREDIV = (uint32_t)(RCC->CFGR2 & RCC_CFGR2_PREDIV);
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */
}

/**
  * @brief  Returns the SYSCLK frequency
  * @note   The system frequency computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  * @note     If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
  * @note     If SYSCLK source is HSE, function returns values based on HSE_VALUE
  *           divided by PREDIV factor(**)
  * @note     If SYSCLK source is PLL, function returns values based on HSE_VALUE
  *           divided by PREDIV factor(**) or HSI_VALUE(*) multiplied by the PLL factor.
  * @note     (*) HSI_VALUE is a constant defined in stm32f3xx.h file (default value
  *               8 MHz).
  * @note     (**) HSE_VALUE is a constant defined in stm32f3xx.h file (default value
  *                8 MHz), user has to ensure that HSE_VALUE is same as the real
  *                frequency of the crystal used. Otherwise, this function may
  *                have wrong result.
  *
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.
  *
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  *
  * @note   Each time SYSCLK changes, this function must be called to update the
  *         right SYSCLK value. Otherwise, any configuration based on this function will be incorrect.
  *
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  uint32_t tmpreg = 0, prediv = 0, pllmul = 0, pllclk = 0;
  uint32_t sysclockfreq = 0;
  
  tmpreg = RCC->CFGR;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (tmpreg & RCC_CFGR_SWS)
  {
  case RCC_SYSCLKSOURCE_STATUS_HSE:    /* HSE used as system clock  source */
    sysclockfreq = HSE_VALUE;
    break;

  case RCC_SYSCLKSOURCE_STATUS_PLLCLK: /* PLL used as system clock  source */
    pllmul = PLLMULFactorTable[(uint32_t)(tmpreg & RCC_CFGR_PLLMUL) >> POSITION_VAL(RCC_CFGR_PLLMUL)];
    prediv = PredivFactorTable[(uint32_t)(RCC->CFGR2 & RCC_CFGR2_PREDIV) >> POSITION_VAL(RCC_CFGR2_PREDIV)];
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
    if ((tmpreg & RCC_CFGR_PLLSRC) != RCC_PLLSOURCE_HSI)
    {
      /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV * PLLMUL */
      pllclk = (HSE_VALUE/prediv) * pllmul;
    }
    else
    {
      /* HSI used as PLL clock source : PLLCLK = HSI/2 * PLLMUL */
      pllclk = (HSI_VALUE >> 1) * pllmul;
    }
#else
    if ((tmpreg & RCC_CFGR_PLLSRC_HSE_PREDIV) == RCC_CFGR_PLLSRC_HSE_PREDIV)
    {
      /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV * PLLMUL */
      pllclk = (HSE_VALUE/prediv) * pllmul;
    }
    else
    {
      /* HSI used as PLL clock source : PLLCLK = HSI/PREDIV * PLLMUL */
      pllclk = (HSI_VALUE/prediv) * pllmul;
    }
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */
       /* STM32F373xC || STM32F378xx                   */
    sysclockfreq = pllclk;
    break;

  case RCC_SYSCLKSOURCE_STATUS_HSI:    /* HSI used as system clock source */
  default:
    sysclockfreq = HSI_VALUE;
    break;
  }
  return sysclockfreq;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_RCC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
