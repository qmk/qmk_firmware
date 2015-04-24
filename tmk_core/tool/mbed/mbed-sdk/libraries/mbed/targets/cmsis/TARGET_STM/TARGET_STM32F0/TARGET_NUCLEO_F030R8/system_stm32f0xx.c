/**
  ******************************************************************************
  * @file    system_stm32f0xx.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    05-December-2014
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Source File.
  *
  * 1. This file provides two functions and one global variable to be called from
  *    user application:
  *      - SystemInit(): This function is called at startup just after reset and 
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32f0xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  * 2. After each device reset the HSI (8 MHz) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_stm32f0xx.s" file, to
  *    configure the system clock before to branch to main program.
  *
  * 3. This file configures the system clock as follows:
  *=============================================================================
  * System clock source                | 1- PLL_HSE_EXTC        | 3- PLL_HSI
  *                                    | (external 8 MHz clock) | (internal 48 MHz)
  *                                    | 2- PLL_HSE_XTAL        |
  *                                    | (external 8 MHz xtal)  |
  *-----------------------------------------------------------------------------
  * SYSCLK(MHz)                        | 48                     | 48
  *-----------------------------------------------------------------------------
  * AHBCLK (MHz)                       | 48                     | 48
  *-----------------------------------------------------------------------------
  * APB1CLK (MHz)                      | 48                     | 48
  *-----------------------------------------------------------------------------
  * USB capable (48 MHz precise clock) | YES                    | YES
  *=============================================================================
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f0xx_system
  * @{
  */

/** @addtogroup STM32F0xx_System_Private_Includes
  * @{
  */

#include "stm32f0xx.h"

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_Defines
  * @{
  */
#if !defined  (HSE_VALUE) 
  #define HSE_VALUE    ((uint32_t)8000000) /*!< Default value of the External oscillator in Hz.
                                                This value can be provided and adapted by the user application. */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)8000000) /*!< Default value of the Internal oscillator in Hz.
                                                This value can be provided and adapted by the user application. */
#endif /* HSI_VALUE */
/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_Macros
  * @{
  */

/* Select the clock sources (other than HSI) to start with (0=OFF, 1=ON) */
#define USE_PLL_HSE_EXTC (1) /* Use external clock */
#define USE_PLL_HSE_XTAL (1) /* Use external xtal */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_Variables
  * @{
  */
  /* This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetHCLKFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock there is no need to
               call the 2 first functions listed above, since SystemCoreClock variable is 
               updated automatically.
  */
uint32_t SystemCoreClock = 48000000;

const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_FunctionPrototypes
  * @{
  */

#if (USE_PLL_HSE_XTAL != 0) || (USE_PLL_HSE_EXTC != 0)
uint8_t SetSysClock_PLL_HSE(uint8_t bypass);
#endif

uint8_t SetSysClock_PLL_HSI(void);

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  *         Initialize the default HSI clock source, vector table location and the PLL configuration is reset.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

#if defined (STM32F051x8) || defined (STM32F058x8)
  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FFB80C;
#else
  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits */
  RCC->CFGR &= (uint32_t)0x08FFB80C;
#endif /* STM32F051x8 or STM32F058x8 */
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  RCC->CFGR &= (uint32_t)0xFFC0FFFF;

  /* Reset PREDIV[3:0] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;

#if defined (STM32F072xB) || defined (STM32F078xB)
  /* Reset USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW, USBSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFCFE2C;
#elif defined (STM32F071xB)
  /* Reset USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFCEAC;
#elif defined (STM32F091xC) || defined (STM32F098xx)
  /* Reset USART3SW[1:0], USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFF0FEAC;
#elif defined (STM32F030x6) || defined (STM32F030x8) || defined (STM32F031x6) || defined (STM32F038xx) || defined (STM32F030xC)
  /* Reset USART1SW[1:0], I2C1SW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFEEC;
#elif defined (STM32F051x8) || defined (STM32F058xx)
  /* Reset USART1SW[1:0], I2C1SW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFEAC;
#elif defined (STM32F042x6) || defined (STM32F048xx)
  /* Reset USART1SW[1:0], I2C1SW, CECSW, USBSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFE2C;
#elif defined (STM32F070x6) || defined (STM32F070xB)
  /* Reset USART1SW[1:0], I2C1SW, USBSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFE6C;
  /* Set default USB clock to PLLCLK, since there is no HSI48 */
  RCC->CFGR3 |= (uint32_t)0x00000080;  
#else
 #warning "No target selected"
#endif

  /* Reset HSI14 bit */
  RCC->CR2 &= (uint32_t)0xFFFFFFFE;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;

  /* Configure the Cube driver */
  SystemCoreClock = 8000000; // At this stage the HSI is used as system clock
  HAL_Init();

  /* Configure the System clock source, PLL Multiplier and Divider factors,
     AHB/APBx prescalers and Flash settings */
  SetSysClock();
}

/**
   * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**)
  *             or HSI_VALUE(*) multiplied/divided by the PLL factors.
  *
  *         (*) HSI_VALUE is a constant defined in stm32f0xx_hal.h file (default value
  *             8 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSE_VALUE is a constant defined in stm32f0xx_hal.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  *
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, predivfactor = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;

  switch (tmp)
  {
    case RCC_CFGR_SWS_HSI:  /* HSI used as system clock */
      SystemCoreClock = HSI_VALUE;
      break;
    case RCC_CFGR_SWS_HSE:  /* HSE used as system clock */
      SystemCoreClock = HSE_VALUE;
      break;
    case RCC_CFGR_SWS_PLL:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMUL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      pllmull = ( pllmull >> 18) + 2;
      predivfactor = (RCC->CFGR2 & RCC_CFGR2_PREDIV) + 1;

      if (pllsource == RCC_CFGR_PLLSRC_HSE_PREDIV)
      {
        /* HSE used as PLL clock source : SystemCoreClock = HSE/PREDIV * PLLMUL */
        SystemCoreClock = (HSE_VALUE/predivfactor) * pllmull;
      }
#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx)
      else if (pllsource == RCC_CFGR_PLLSRC_HSI48_PREDIV)
      {
        /* HSI48 used as PLL clock source : SystemCoreClock = HSI48/PREDIV * PLLMUL */
        SystemCoreClock = (HSI48_VALUE/predivfactor) * pllmull;
      }
#endif /* STM32F042x6 || STM32F048xx || STM32F072xB || STM32F078xx || STM32F091xC || STM32F098xx */
      else
      {
#if defined(STM32F042x6) || defined(STM32F048xx)  || defined(STM32F070x6) || \
    defined(STM32F078xx) || defined(STM32F071xB)  || defined(STM32F072xB) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx)  || defined(STM32F030xC)
        /* HSI used as PLL clock source : SystemCoreClock = HSI/PREDIV * PLLMUL */
        SystemCoreClock = (HSI_VALUE/predivfactor) * pllmull;
#else
        /* HSI used as PLL clock source : SystemCoreClock = HSI/2 * PLLMUL */
        SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
#endif /* STM32F042x6 || STM32F048xx || STM32F070x6 || 
          STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB ||
          STM32F091xC || STM32F098xx || STM32F030xC */
      }
      break;
    default: /* HSI used as system clock */
      SystemCoreClock = HSI_VALUE;
      break;
  }
  /* Compute HCLK clock frequency ----------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}

/**
  * @brief  Configures the System clock source, PLL Multiplier and Divider factors,
  *               AHB/APBx prescalers and Flash settings
  * @note   This function should be called only once the RCC clock configuration  
  *         is reset to the default reset state (done in SystemInit() function).             
  * @param  None
  * @retval None
  */
void SetSysClock(void)
{
  /* 1- Try to start with HSE and external clock */
#if USE_PLL_HSE_EXTC != 0
  if (SetSysClock_PLL_HSE(1) == 0)
#endif
  {
    /* 2- If fail try to start with HSE and external xtal */
    #if USE_PLL_HSE_XTAL != 0
    if (SetSysClock_PLL_HSE(0) == 0)
    #endif
    {
      /* 3- If fail start with HSI clock */
      if (SetSysClock_PLL_HSI() == 0)
      {
        while(1)
        {
          // [TODO] Put something here to tell the user that a problem occured...
        }
      }
    }
  }
  
  // Output clock on MCO pin(PA8) for debugging purpose
  //HAL_RCC_MCOConfig(RCC_MCO, RCC_MCOSOURCE_SYSCLK, RCC_MCO_NODIV); // 48 MHz
}

#if (USE_PLL_HSE_XTAL != 0) || (USE_PLL_HSE_EXTC != 0)
/******************************************************************************/
/*            PLL (clocked by HSE) used as System clock source                */
/******************************************************************************/
uint8_t SetSysClock_PLL_HSE(uint8_t bypass)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  // Select HSE oscillator as PLL source
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI48;
  if (bypass == 0) {
      RCC_OscInitStruct.HSEState   = RCC_HSE_ON; // External 8 MHz xtal on OSC_IN/OSC_OUT
  } else {
      RCC_OscInitStruct.HSEState   = RCC_HSE_BYPASS; // External 8 MHz clock on OSC_IN only
  }
  RCC_OscInitStruct.HSI48State     = 0; // not used 
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PREDIV     = RCC_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      return 0; // FAIL
  }
 
  // Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers
  RCC_ClkInitStruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK; // 48 MHz
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;         // 48 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;           // 48 MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
      return 0; // FAIL
  }
  
  return 1; // OK
}
#endif

/******************************************************************************/
/*            PLL (clocked by HSI) used as System clock source                */
/******************************************************************************/
uint8_t SetSysClock_PLL_HSI(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
 
  // Select PLLCLK = 48 MHz ((HSI 8 MHz / 2) * 12)
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSI; // HSI div 2
  RCC_OscInitStruct.PLL.PREDIV     = RCC_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      return 0; // FAIL
  }
 
  // Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers
  RCC_ClkInitStruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK; // 48 MHz
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;         // 48 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;           // 48 MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
      return 0; // FAIL
  }

  return 1; // OK
}

/* Used for the different timeouts in the HAL */
void SysTick_Handler(void)
{
  HAL_IncTick();
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

