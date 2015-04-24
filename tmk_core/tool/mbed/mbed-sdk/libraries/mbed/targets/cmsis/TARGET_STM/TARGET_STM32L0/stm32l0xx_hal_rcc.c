/**
  ******************************************************************************
  * @file    stm32l0xx_hal_rcc.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   RCC HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Reset and Clock Control (RCC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *       
  @verbatim                
  ==============================================================================
                      ##### RCC specific features #####
  ==============================================================================
    [..] After reset the device is running from MSI (2 MHz) with Flash 0 WS, 
         all peripherals are off except internal SRAM, Flash and SW-DP.
         (+) There is no prescaler on High speed (AHB) and Low speed (APB) busses;
             all peripherals mapped on these busses are running at MSI speed.
         (+) The clock for all peripherals is switched off, except the SRAM and 
             FLASH.
         (+) All GPIOs are in input floating state, except the SW-DP pins which
             are assigned to be used for debug purpose.
    [..] Once the device started from reset, the user application has to:
         (+) Configure the clock source to be used to drive the System clock
             (if the application needs higher frequency/performance)
         (+) Configure the System clock frequency and Flash settings
         (+) Configure the AHB and APB busses prescalers
         (+) Enable the clock for the peripheral(s) to be used
         (+) Configure the clock source(s) for peripherals whose clocks are not
             derived from the System clock (ADC, RTC/LCD, RNG and IWDG)

                      ##### RCC Limitations #####
  ==============================================================================
    [..]  
      A delay between an RCC peripheral clock enable and the effective peripheral 
      enabling should be taken into account in order to manage the peripheral read/write 
      from/to registeres.
      (+) This delay depends on the peripheral mapping.
      (+) If peripheral is mapped on AHB: the delay is 2 AHB clock cycle 
          after the clock enable bit is set on the hardware register
      (+) If peripheral is mapped on APB: the delay is 2 APB clock cycle 
          after the clock enable bit is set on the hardware register

    [..]  
      Possible Workarounds:
      (#) Enable the peripheral clock sometimes before the peripheral read/write 
          register is required.
      (#) For AHB peripheral, insert two dummy read to the peripheral register.
      (#) For APB peripheral, insert a dummy read to the peripheral register.
             
  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup RCC 
  * @brief RCC HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/** @defgroup RCC_Private_Constants RCC Private constants
  * @{
  */ 
#define RCC_HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define RCC_HSI_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define RCC_LSI_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define RCC_PLL_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define RCC_HSI48_TIMEOUT_VALUE        ((uint32_t)100)  /* 100 ms */
#define RCC_MSI_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */    
#define RCC_CLOCKSWITCH_TIMEOUT_VALUE  ((uint32_t)5000) /* 5 s    */

#define __MCO1_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO1_GPIO_PORT        GPIOA
#define MCO1_PIN              GPIO_PIN_8
#define MCO2_PIN              GPIO_PIN_9

/**
  * @}
  */ 

/** @defgroup RCC_Private_Vatiables RCC Private Data
  * @{
  */ 
const uint8_t PLLMulTable[9] = {3, 4, 6, 8, 12, 16, 24, 32, 48};
const uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @}
  */ 

/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
           ##### Initialization and de-initialization functions #####
 ===============================================================================
   [..] 
      This section provide functions allowing to configure the internal/external 
         clocks, PLL, CSS and MCO.
   [..] Internal/external clock and PLL configuration
         (#) HSI (high-speed internal), 16 MHz factory-trimmed RC used directly 
             or through the PLL as System clock source.
         (#) MSI (multi-speed internal), multispeed low power RC 
             (65.536 KHz to 4.194 MHz) MHz used as System clock source.
         (#) LSI (low-speed internal), 37 KHz low consumption RC used as IWDG 
             and/or RTC clock source.
         (#) HSE (high-speed external), 1 to 24 MHz crystal oscillator used 
             directly or through the PLL as System clock source. Can be used 
             also as RTC clock source.
         (#) LSE (low-speed external), 32 KHz oscillator used as RTC clock source.
         (#) PLL (clocked by HSI or HSE), for System clock and USB (48 MHz).
         (#) CSS (Clock security system), once enable and if a HSE clock failure 
             occurs (HSE used directly or through PLL as System clock source), 
             the System clock is automatically switched to MSI and an interrupt 
             is generated if enabled. 
             The interrupt is linked to the Cortex-M3 NMI (Non-Maskable Interrupt) 
             exception vector.
         (#) MCO (microcontroller clock output), used to output SYSCLK, HSI, MSI, 
             HSE, PLL, LSI or LSE clock (through a configurable prescaler) on 
             PA8 pin.
 [..] System, AHB and APB busses clocks configuration  
         (#) Several clock sources can be used to drive the System clock (SYSCLK): MSI, HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System clock through configurable 
             prescaler and used to clock the CPU, memory and peripherals mapped 
             on IOPORT, AHB bus (DMA,Flash...). APB1 (PCLK1) and APB2 (PCLK2) clocks are derived 
             from AHB clock through configurable prescalers and used to clock 
             the peripherals mapped on these busses. You can use 
             "HAL_RCC_GetSysClockFreq()" function to retrieve the frequencies of these clocks.  

         -@- All the peripheral clocks are derived from the System clock (SYSCLK) except:
           (+@) I2S: the I2S clock can be derived from an external clock mapped on the I2S_CKIN pin. 
              
           (+@) RTC: the RTC clock can be derived either from the LSI, LSE or HSE clock
                divided by 2 to 16. You have to use __HAL_RCC_RTC_CONFIG() and __HAL_RCC_RTC_ENABLE()
                macros to configure this clock. 
           (+@) USB FS,and RNG  require a frequency equal to 48 MHz to work correctly
                This clock is derived from the main PLL or HSI48 RC oscillator.
           (+@) IWDG clock which is always the LSI clock.
       
         (#) For the STM32L0xx devices, the maximum
             frequency of the SYSCLK ,HCLK, APB1 and APB2 is 32 MHz. 
             Depending on the device voltage range, the maximum frequency should
             be adapted accordingly:
 ----------------------------------------------------------------
 |  Wait states  |                HCLK clock frequency (MHz)      |
 |               |------------------------------------------------|
 |   (Latency)   |            voltage range       | voltage range |
 |               |            1.65 V - 3.6 V      | 2.0 V - 3.6 V |
 |               |----------------|---------------|---------------|
 |               |  VCORE = 1.2 V | VCORE = 1.5 V | VCORE = 1.8 V |
 |-------------- |----------------|---------------|---------------|
 |0WS(1CPU cycle)|0 < HCLK <= 2   |0 < HCLK <= 8  |0 < HCLK <= 16 |
 |---------------|----------------|---------------|---------------|
 |1WS(2CPU cycle)|2 < HCLK <= 4   |8 < HCLK <= 16 |16 < HCLK <= 32|
  ----------------------------------------------------------------
@endverbatim
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *           - MSI ON and used as system clock source (MSI range is not modified
  *           - by this function, it keep the value configured by user application)
  *           - HSI, HSE and PLL OFF
  *           - AHB, APB1 and APB2 prescaler set to 1.
  *           - CSS and MCO OFF
  *           - All interrupts disabled
  * @note   This function does not modify the configuration of the
  * @note      -Peripheral clocks
  * @note      -HSI48, LSI, LSE and RTC clocks                  
  * @param  None
  * @retval None
  */
__weak void HAL_RCC_DeInit(void)
{
  /* This function is now defined in the file stm32L0xx_rcc_ex.c */
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
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));
  /*------------------------------- HSE Configuration ------------------------*/ 
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));
    /* When the HSE is used as system clock or clock source for PLL in these cases HSE will not disabled */
    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HSE) || ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && ((RCC->CFGR & RCC_CFGR_PLLSRC) == RCC_CFGR_PLLSRC_HSE)))
    {
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET) && (RCC_OscInitStruct->HSEState == RCC_HSE_OFF))
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
    
      /* Wait till HSE is disabled */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_HSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }      
      }
      
      /* Set the new HSE configuration ---------------------------------------*/
      __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);
      
      /* Check the HSE State */
      if((RCC_OscInitStruct->HSEState) != RCC_HSE_OFF)
      {
        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till HSE is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
        {
          if((HAL_GetTick() - tickstart ) > RCC_HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }      
        }      
      }
      else
      {
        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till HSE is disabled */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
        {
           if((HAL_GetTick() - tickstart ) > RCC_HSE_TIMEOUT_VALUE)
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
    
    /* When the HSI is used as system clock it will not disabled */
    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HSI) || ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && ((RCC->CFGR & RCC_CFGR_PLLSRC) == RCC_CFGR_PLLSRC_HSI)))
    {
      /* When HSI is used as system clock it will not disabled */
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
      if((RCC_OscInitStruct->HSIState)!= RCC_HSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (HSI or HSIdiv4 */
        __HAL_RCC_HSI_CONFIG(RCC_OscInitStruct->HSIState);
        
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
      
        /* Wait till HSI is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
        {
          if((HAL_GetTick() - tickstart ) > RCC_HSI_TIMEOUT_VALUE)
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
        __HAL_RCC_HSI_CONFIG(RCC_OscInitStruct->HSIState);
       
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
      
        /* Wait till HSI is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET)
        {
          if((HAL_GetTick() - tickstart ) > RCC_HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }      
        } 
      }
    }
  }
   /*----------------------------- MSI Configuration --------------------------*/ 
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_MSI) == RCC_OSCILLATORTYPE_MSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_MSI(RCC_OscInitStruct->MSIState));
    assert_param(IS_RCC_MSICALIBRATION_VALUE(RCC_OscInitStruct->MSICalibrationValue));
    
        
    /* When the MSI is used as system clock it will not disabled */
    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_MSI) )
    {
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_MSIRDY) != RESET) && (RCC_OscInitStruct->MSIState != RCC_MSI_ON))
      {
        return HAL_ERROR;
      }
      
       /* Otherwise, just the calibration and MSI range change are allowed */
      else
      {
       /* Selects the Multiple Speed oscillator (MSI) clock range .*/
        __HAL_RCC_MSI_RANGE_CONFIG (RCC_OscInitStruct->MSIClockRange);   
        /* Adjusts the Multiple Speed oscillator (MSI) calibration value.*/
        __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->MSICalibrationValue);
      }
    }
    else
    {
      /* Check the MSI State */
      if((RCC_OscInitStruct->MSIState)!= RCC_MSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (MSI). */
        __HAL_RCC_MSI_ENABLE();
        
        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till MSI is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_MSIRDY) == RESET)
        {
          if((HAL_GetTick() - tickstart ) > RCC_MSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }      
        } 
         /* Selects the Multiple Speed oscillator (MSI) clock range .*/
        __HAL_RCC_MSI_RANGE_CONFIG (RCC_OscInitStruct->MSIClockRange);   
         /* Adjusts the Multiple Speed oscillator (MSI) calibration value.*/
        __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->MSICalibrationValue);
        
      }
      else
      {
        /* Disable the Internal High Speed oscillator (MSI). */
        __HAL_RCC_MSI_DISABLE();
        
        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till MSI is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_MSIRDY) != RESET)
        {
          if((HAL_GetTick() - tickstart ) > RCC_MSI_TIMEOUT_VALUE)
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
    if((RCC_OscInitStruct->LSIState)!= RCC_LSI_OFF)
    {
      /* Enable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_ENABLE();
      
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till LSI is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_LSI_TIMEOUT_VALUE)
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
        if((HAL_GetTick() - tickstart ) > RCC_LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }      
      } 
    }
  }
  
#if !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx) && !defined(STM32L081xx)  
   /*------------------------------ HSI48 Configuration -------------------------*/ 
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI48) == RCC_OSCILLATORTYPE_HSI48)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI48(RCC_OscInitStruct->HSI48State));
    
    /* Check the HSI48 State */
    if((RCC_OscInitStruct->HSI48State)!= RCC_HSI48_OFF)
    {
      /* Enable the Internal Low Speed oscillator (HSI48). */
      __HAL_RCC_HSI48_ENABLE();
      
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till HSI48 is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSI48RDY) == RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_HSI48_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }      
      } 
    }
    else
    {
      /* Disable the Internal Low Speed oscillator (HSI48). */
      __HAL_RCC_HSI48_DISABLE();
      
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till HSI48 is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSI48RDY) != RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_HSI48_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }      
      } 
    }
  }
#endif /* !(STM32L031xx) && !(STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx) && !defined(STM32L081xx)*/  
  
  /*------------------------------ LSE Configuration -------------------------*/ 
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));

    /* Enable Power Clock*/
    __HAL_RCC_PWR_CLK_ENABLE();

    /* Enable write access to Backup domain */
    PWR->CR |= PWR_CR_DBP;

    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();
 
    while((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if((HAL_GetTick() - tickstart ) > RCC_DBP_TIMEOUT_VALUE)
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
      if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }      
    } 
    
    /* Set the new LSE configuration -----------------------------------------*/
    __HAL_RCC_LSE_CONFIG(RCC_OscInitStruct->LSEState);
    /* Check the LSE State */
    if((RCC_OscInitStruct->LSEState) != RCC_LSE_OFF)
    {     
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
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
        if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
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
        assert_param(IS_RCC_PLL_DIV(RCC_OscInitStruct->PLL.PLLDIV));
        
        
        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();
        
        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till PLL is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
        {
          if((HAL_GetTick() - tickstart ) > RCC_PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }      
        }        

        /* Configure the main PLL clock source, multiplication and division factors. */
        __HAL_RCC_PLL_CONFIG(RCC_OscInitStruct->PLL.PLLSource,
                             RCC_OscInitStruct->PLL.PLLMUL,
                             RCC_OscInitStruct->PLL.PLLDIV);
        /* Enable the main PLL. */
        __HAL_RCC_PLL_ENABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();
      
        /* Wait till PLL is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
        {
          if((HAL_GetTick() - tickstart ) > RCC_PLL_TIMEOUT_VALUE)
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
          if((HAL_GetTick() - tickstart ) > RCC_PLL_TIMEOUT_VALUE)
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
  * @brief  Initializes the CPU, AHB and APB busses clocks according to the specified 
  *         parameters in the RCC_ClkInitStruct.
  * @param  RCC_ClkInitStruct: pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @param  FLatency: FLASH Latency, this parameter depends on System Clock Frequency
  * 
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency 
  *         and updated by HAL_RCC_GetHCLKFreq() function called within this function
  *                 
  * @note   The MSI is used (enabled by hardware) as system clock source after
  *         startup from Reset, wake-up from STOP and STANDBY mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  *           
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked). 
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source will be ready. 
  * @retval None
  */
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t FLatency)
{

  uint32_t tickstart = 0;
 
  /* Check the parameters */
  assert_param(IS_RCC_CLOCKTYPE(RCC_ClkInitStruct->ClockType));
  assert_param(IS_FLASH_LATENCY(FLatency));
 
  /* To correctly read data from FLASH memory, the number of wait states (LATENCY) 
    must be correctly programmed according to the frequency of the CPU clock 
    (HCLK) and the supply voltage of the device. */
  
  /* Increasing the CPU frequency */
  if(FLatency > (FLASH->ACR & FLASH_ACR_LATENCY))
  {    
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);
    
    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if((FLASH->ACR & FLASH_ACR_LATENCY) != FLatency)
    {
      return HAL_ERROR;
    }

    /*-------------------------- HCLK Configuration --------------------------*/
    if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
    {
      assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
      MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }

    /*------------------------- SYSCLK Configuration ---------------------------*/ 
    if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
    {    
      assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));
      
      /* HSE is selected as System Clock Source */
      if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
      {
        /* Check the HSE ready flag */  
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
        {
          return HAL_ERROR;
        }
      }
      
          /* MSI is selected as System Clock Source */
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_MSI)
      {
        /* Check the MSI ready flag */  
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_MSIRDY) == RESET)
        {
          return HAL_ERROR;
        }
      }
      /* PLL is selected as System Clock Source */
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
      {
        /* Check the PLL ready flag */  
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
        {
          return HAL_ERROR;
        }
      }
      /* HSI is selected as System Clock Source */
      else
      {
        /* Check the HSI ready flag */  
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
        {
          return HAL_ERROR;
        }
      }
      MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_ClkInitStruct->SYSCLKSource);
 
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSE)
        {
          if((HAL_GetTick() - tickstart ) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          } 
        }
      }
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
        {
          if((HAL_GetTick() - tickstart ) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          } 
        }
      }
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_MSI)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_MSI)
        {
          if((HAL_GetTick() - tickstart ) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          } 
        }
      }
      else
      {
        while(__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSI)
        {
          if((HAL_GetTick() - tickstart ) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }    
  }
  /* Decreasing the CPU frequency */
  else
  {
    /*-------------------------- HCLK Configuration --------------------------*/
    if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
    {
      assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
      MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }

    /*------------------------- SYSCLK Configuration -------------------------*/
    if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
    {    
      assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));
      
      /* HSE is selected as System Clock Source */
      if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
      {
        /* Check the HSE ready flag */  
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
        {
          return HAL_ERROR;
        }
      }

      /* MSI is selected as System Clock Source */
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_MSI)
      {
        /* Check the MSI ready flag */  
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_MSIRDY) == RESET)
        {
          return HAL_ERROR;
        }
      }
      /* PLL is selected as System Clock Source */
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
      {
        /* Check the PLL ready flag */  
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
        {
          return HAL_ERROR;
        }
      }
      /* HSI is selected as System Clock Source */
      else
      {
        /* Check the HSI ready flag */  
        if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
        {
          return HAL_ERROR;
        }
      }
      MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_ClkInitStruct->SYSCLKSource);
      
      /* Get timeout */
      tickstart = HAL_GetTick();
      
      if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSE)
        {
          if((HAL_GetTick() - tickstart ) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          } 
        }
      }
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
        {
          if((HAL_GetTick() - tickstart ) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          } 
        }
      }
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_MSI)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_MSI)
        {
          if((HAL_GetTick() - tickstart ) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          } 
        }
      }
      else
      {
        while(__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSI)
        {
          if((HAL_GetTick() - tickstart ) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }  
        }
      }
    }
    
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);
    
    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if((FLASH->ACR & FLASH_ACR_LATENCY) != FLatency)
    {
      return HAL_ERROR;
    }
 }

  /*-------------------------- PCLK1 Configuration ---------------------------*/ 
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
  {
    assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APB1CLKDivider));
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_ClkInitStruct->APB1CLKDivider);
  }
  
  /*-------------------------- PCLK2 Configuration ---------------------------*/ 
  if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
  {
    assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APB2CLKDivider));
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, ((RCC_ClkInitStruct->APB2CLKDivider) << 3));
  }

  /* Configure the source of time base considering new system clocks settings*/
  HAL_InitTick (TICK_INT_PRIORITY);
  
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief   RCC clocks control functions 
 *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks 
    frequencies.
      
@endverbatim
  * @{
  */

/**
  * @brief  Selects the clock source to output on MCO pin.
  * @note   MCO pin should be configured in alternate function mode.
  * @param  RCC_MCOx: specifies the output direction for the clock source.
  *           For STM32L0xx family this parameter can have only one value:
  *            @arg RCC_MCO1: Clock source to output on MCO pin(PA8).
  *            @arg RCC_MCO2: Clock source to output on MCO pin(PA9).
  * @param  RCC_MCOSource: specifies the clock source to output.
  *          This parameter can be one of the following values:
  *     @arg RCC_MCO1SOURCE_NOCLOCK: No clock selected
  *     @arg RCC_MCO1SOURCE_SYSCLK: System clock selected
  *     @arg RCC_MCO1SOURCE_HSI: HSI oscillator clock selected
  *     @arg RCC_MCO1SOURCE_MSI: MSI oscillator clock selected  
  *     @arg RCC_MCO1SOURCE_HSE: HSE oscillator clock selected
  *     @arg RCC_MCO1SOURCE_PLLCLK: PLL clock selected
  *     @arg RCC_MCO1SOURCE_LSI: LSI clock selected
  *     @arg RCC_MCO1SOURCE_LSE: LSE clock selected
  *     and in STM32L052xx,STM32L053xx,STM32L062xx, STM32L063xx
  *            STM32L072xx,STM32L073xx,STM32L082xx, STM32L083xx 
  *     @arg RCC_MCO1SOURCE_HSI48: HSI48 clock selected
  * @param  RCC_MCODIV: specifies the MCO DIV.
  *     This parameter can be one of the following values: 
  *     @arg RCC_MCODIV_1: no division applied to MCO clock 
  *     @arg RCC_MCODIV_2: division by 2 applied to MCO clock
  *     @arg RCC_MCODIV_4: division by 4 applied to MCO clock
  *     @arg RCC_MCODIV_8: division by 8 applied to MCO clock
  *     @arg RCC_MCODIV_16: division by 16 applied to MCO clock        
  * @retval None
  */
void HAL_RCC_MCOConfig( uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /* Check the parameters */
  assert_param(IS_RCC_MCO(RCC_MCOx));
  assert_param(IS_RCC_MCODIV(RCC_MCODiv));
  assert_param(IS_RCC_MCO1SOURCE(RCC_MCOSource));
    
    /* MCO Clock Enable */
    __MCO1_CLK_ENABLE();
    
    /* Configure the MCO1 pin in alternate function mode */    
  if(RCC_MCOx == RCC_MCO1)
  {    
    GPIO_InitStruct.Pin = MCO1_PIN;
  }
    else
  {    
    GPIO_InitStruct.Pin = MCO2_PIN;
  }    
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    HAL_GPIO_Init(MCO1_GPIO_PORT, &GPIO_InitStruct);
    
    /* Mask MCO1 and MCO1PRE[2:0] bits then Select MCO1 clock source and prescaler */
    MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCOSEL | RCC_CFGR_MCO_PRE), ((RCC_MCOSource | RCC_MCODiv )));
}

/**
  * @brief  Enables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to 
  *         the Cortex-M0+ NMI (Non-Maskable Interrupt) exception vector.  
  * @param  None
  * @retval None
  */
void HAL_RCC_EnableCSS(void)
{
   SET_BIT(RCC->CR, RCC_CR_CSSHSEON) ;
}


/**
  * @brief  Returns the SYSCLK frequency
  *        
  * @note   The system frequency computed by this function is not the real 
  *         frequency in the chip. It is calculated based on the predefined 
  *         constant and the selected clock source:
  * @note     If SYSCLK source is MSI, function returns values based on MSI
  *             Value as defined by the MSI range.
  * @note     If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
  * @note     If SYSCLK source is HSE, function returns values based on HSE_VALUE(**)
  * @note     If SYSCLK source is PLL, function returns values based on HSE_VALUE(**) 
  *           or HSI_VALUE(*) multiplied/divided by the PLL factors.         
  * @note     (*) HSI_VALUE is a constant defined in stm32l0xx_hal_conf.h file (default value
  *               16 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature.
  * @note     (**) HSE_VALUE is a constant defined in stm32l0xx_hal_conf.h file (default value
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
  *               
  * @param  None
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  uint32_t pllmul = 0, plldiv = 0, pllsource = 0,  msirange = 0;
  uint32_t sysclockfreq = 0;
    
  /* Get SYSCLK source -------------------------------------------------------*/
 
  /*MSI frequency range in HZ*/
  msirange = (RCC->ICSCR & RCC_ICSCR_MSIRANGE) >> 13;
  
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case RCC_CFGR_SWS_MSI: /* MSI used as system clock */ 
    {  
      sysclockfreq = (32768 * (1 << (msirange + 1)));
      break;
    }
    case RCC_SYSCLKSOURCE_STATUS_HSI:  /* HSI used as system clock */
    {
      if ((RCC->CR & RCC_CR_HSIDIVF) != 0)
      {
        sysclockfreq =  (HSI_VALUE >> 2);
      }
      else 
      {
        sysclockfreq =  HSI_VALUE;
      }
      break;
    }
    case RCC_SYSCLKSOURCE_STATUS_HSE:  /* HSE used as system clock */
    {
      sysclockfreq = HSE_VALUE;
      break;
    }
    case RCC_SYSCLKSOURCE_STATUS_PLLCLK:  /* PLL used as system clock */
    {
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmul = RCC->CFGR & RCC_CFGR_PLLMUL;
      plldiv = RCC->CFGR & RCC_CFGR_PLLDIV;
      pllmul = PLLMulTable[(pllmul >> 18)];
      plldiv = (plldiv >> 22) + 1;
      
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;

      if (pllsource == RCC_CFGR_PLLSRC_HSI)
      {
        /* HSI oscillator clock selected as PLL clock source */
        if ((RCC->CR & RCC_CR_HSIDIVF) != 0)
        {
          sysclockfreq = (HSI_VALUE >> 2) * (pllmul / plldiv);
        }
        else 
        {
          sysclockfreq =(((HSI_VALUE) * pllmul) / plldiv);
        }
      }
      else
      {
        /* HSE selected as PLL clock source */
       sysclockfreq = (((HSE_VALUE) * pllmul) / plldiv);
      }
      break;
    }
    default: /* MSI used as system clock */
    {
      sysclockfreq = (32768 * (1 << (msirange + 1)));
      break;
    }
  }
  return sysclockfreq;
}

/**
  * @brief  Returns the HCLK frequency     
  * @note   Each time HCLK changes, this function must be called to update the
  *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  *
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency 
  *         and updated within this function                   
  * @param  None
  * @retval HCLK frequency
  */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
  SystemCoreClock =  HAL_RCC_GetSysClockFreq() >> APBAHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  
  return (SystemCoreClock);

}

/**
  * @brief  Returns the PCLK1 frequency     
  * @note   Each time PCLK1 changes, this function must be called to update the
  *         right PCLK1 value. Otherwise, any configuration based on this function will be incorrect.
  * @param  None
  * @retval PCLK1 frequency
  */
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
  
 return ( HAL_RCC_GetHCLKFreq() >> APBAHBPrescTable[((RCC->CFGR & RCC_CFGR_PPRE1) >> 8)]);
  
}    

/**
  * @brief  Returns the PCLK2 frequency     
  * @note   Each time PCLK2 changes, this function must be called to update the
  *         right PCLK2 value. Otherwise, any configuration based on this function will be incorrect.
  * @param  None
  * @retval PCLK2 frequency
  */
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
  
  return ( HAL_RCC_GetHCLKFreq() >> APBAHBPrescTable[((RCC->CFGR & RCC_CFGR_PPRE2) >> 11)]);
  
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
  /* Set all possible values for the Oscillator type parameter ---------------*/
  RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_MSI | RCC_OSCILLATORTYPE_HSI | \
                                      RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI;
#if !defined (STM32L031xx) && !defined (STM32L041xx) && !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx) && !defined(STM32L081xx) 
  RCC_OscInitStruct->OscillatorType |= RCC_OSCILLATORTYPE_HSI48;
#endif

  /* Get the HSE configuration -----------------------------------------------*/
  if((RCC->CR &RCC_CR_HSEBYP) == RCC_CR_HSEBYP)
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_BYPASS;
  }
  else if((RCC->CR &RCC_CR_HSEON) == RCC_CR_HSEON)
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_ON;
  }
  else
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_OFF;
  }
  
  /* Get the MSI configuration -----------------------------------------------*/
  if((RCC->CR &RCC_CR_MSION) == RCC_CR_MSION)
  {
    RCC_OscInitStruct->MSIState = RCC_MSI_ON;
  }
  else
  {
    RCC_OscInitStruct->MSIState = RCC_MSI_OFF;
  }
  
  RCC_OscInitStruct->MSICalibrationValue = (uint32_t)((RCC->CR &RCC_ICSCR_MSITRIM) >> 24); 
  RCC_OscInitStruct->MSIClockRange = (uint32_t)((RCC->ICSCR &RCC_ICSCR_MSIRANGE) >> 13); 

#if !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx) && !defined(STM32L081xx)  
  /* Get the HSI48 configuration -----------------------------------------------*/
  if((RCC->CRRCR &RCC_CRRCR_HSI48ON) == RCC_CRRCR_HSI48ON)
  {
    RCC_OscInitStruct->HSI48State = RCC_HSI48_ON;
  }
  else
  {
    RCC_OscInitStruct->HSI48State = RCC_HSI48_OFF;
  }
#endif
  
  /* Get the HSI configuration -----------------------------------------------*/
  if((RCC->CR &RCC_CR_HSION) == RCC_CR_HSION)
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_ON;
  }
  else
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_OFF;
  }
  
  RCC_OscInitStruct->HSICalibrationValue = (uint32_t)((RCC->ICSCR &RCC_ICSCR_HSITRIM) >> 8);
  
  /* Get the LSE configuration -----------------------------------------------*/
  if((RCC->CSR &RCC_CSR_LSEBYP) == RCC_CSR_LSEBYP)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_BYPASS;
  }
  else if((RCC->CSR &RCC_CSR_LSEON) == RCC_CSR_LSEON)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_ON;
  }
  else
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_OFF;
  }
  
  /* Get the LSI configuration -----------------------------------------------*/
  if((RCC->CSR &RCC_CSR_LSION) == RCC_CSR_LSION)
  {
    RCC_OscInitStruct->LSIState = RCC_LSI_ON;
  }
  else
  {
    RCC_OscInitStruct->LSIState = RCC_LSI_OFF;
  }
  
  /* Get the PLL configuration -----------------------------------------------*/
  if((RCC->CR &RCC_CR_PLLON) == RCC_CR_PLLON)
  {
    RCC_OscInitStruct->PLL.PLLState = RCC_PLL_ON;
  }
  else
  {
    RCC_OscInitStruct->PLL.PLLState = RCC_PLL_OFF;
  }
  RCC_OscInitStruct->PLL.PLLSource = (uint32_t)(RCC->CFGR & RCC_CFGR_PLLSRC);
  RCC_OscInitStruct->PLL.PLLMUL = (uint32_t)(RCC->CFGR & RCC_CFGR_PLLMUL) >> 18;
  RCC_OscInitStruct->PLL.PLLDIV = (uint32_t)(RCC->CFGR & RCC_CFGR_PLLDIV) >> 22;

}

/**
  * @brief  Configures the RCC_ClkInitStruct according to the internal 
  * RCC configuration registers.
  * @param  RCC_OscInitStruct: pointer to an RCC_ClkInitTypeDef structure that 
  * will be configured.
  * @param  pFLatency: Pointer on the Flash Latency.
  * @retval None
  */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency)
{
  /* Set all possible values for the Clock type parameter --------------------*/
  RCC_ClkInitStruct->ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
   
  /* Get the SYSCLK configuration --------------------------------------------*/ 
  RCC_ClkInitStruct->SYSCLKSource = (uint32_t)(RCC->CFGR & RCC_CFGR_SW);
  
  /* Get the HCLK configuration ----------------------------------------------*/ 
  RCC_ClkInitStruct->AHBCLKDivider = (uint32_t)(RCC->CFGR & RCC_CFGR_HPRE); 
  
  /* Get the APB1 configuration ----------------------------------------------*/ 
  RCC_ClkInitStruct->APB1CLKDivider = (uint32_t)(RCC->CFGR & RCC_CFGR_PPRE1);   
  
  /* Get the APB2 configuration ----------------------------------------------*/ 
  RCC_ClkInitStruct->APB2CLKDivider = (uint32_t)((RCC->CFGR & RCC_CFGR_PPRE2) >> 3);
  
  /* Get the Flash Wait State (Latency) configuration ------------------------*/   
  *pFLatency = (uint32_t)(FLASH->ACR & FLASH_ACR_LATENCY); 
}

/**
  * @brief This function handles the RCC CSS interrupt request.
  * @note This API should be called under the NMI_Handler().
  * @param None
  * @retval None
  */
void HAL_RCC_NMI_IRQHandler(void)
{
  /* Check RCC CSSF flag  */
  if(__HAL_RCC_GET_IT_SOURCE(RCC_IT_CSS))
  {
    /* RCC Clock Security System interrupt user callback */
    HAL_RCC_CSSCallback();

    /* Clear RCC CSS pending bit */
    __HAL_RCC_CLEAR_IT(RCC_IT_CSS);
  }
}

/**
  * @brief  RCC Clock Security System interrupt callback
  * @param  none 
  * @retval none
  */
__weak void HAL_RCC_CSSCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_RCC_CSSCallback could be implemented in the user file
   */ 
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

