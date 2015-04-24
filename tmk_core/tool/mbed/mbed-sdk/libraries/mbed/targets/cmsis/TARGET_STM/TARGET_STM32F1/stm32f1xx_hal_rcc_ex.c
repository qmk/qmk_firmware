/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rcc_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Extended RCC HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities RCC extension peripheral:
  *           + Extended Peripheral Control functions
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/** @defgroup RCCEx RCCEx
  * @brief RCC Extension HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup RCCEx_Private_Constants RCCEx Private Constants
 * @{
 */
#define PLL2_TIMEOUT_VALUE         ((uint32_t)100)  /* 100 ms */

/* Alias word address of PLL2ON bit */
#define PLL2ON_BITNUMBER           POSITION_VAL(RCC_CR_PLL2ON)
#define CR_PLL2ON_BB               ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32) + (PLL2ON_BITNUMBER * 4)))


/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/** @defgroup RCCEx_Private_Macros RCCEx Private Macros
 * @{
 */
/**
  * @}
  */

/** @defgroup RCCEx_Private_Macros RCCEx Private Macros
 * @{
 */

/**
  * @}
  */


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/** @addtogroup RCC
  * @{
  */

/** @addtogroup RCC_Exported_Functions
  * @{
  */

#if defined(STM32F105xC) || defined(STM32F107xC) || defined (STM32F100xB) || defined (STM32F100xE) 
/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - HSI ON and used as system clock source
  *            - HSE and PLL OFF
  *            - AHB, APB1 and APB2 prescaler set to 1.
  *            - CSS and MCO1 OFF
  *            - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *            - Peripheral clocks  
  *            - LSI, LSE and RTC clocks 
  * @retval None
  */
void HAL_RCC_DeInit(void)
{
  /* Switch SYSCLK to HSI */
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_SW);
  
  /* Reset HSEON, CSSON, & PLLON bits */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON);
  
  /* Reset HSEBYP bit */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
  
  /* Reset CFGR register */
  CLEAR_REG(RCC->CFGR);
  
  /* Set HSITRIM bits to the reset value */
  MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, ((uint32_t)0x10 << POSITION_VAL(RCC_CR_HSITRIM)));

  /* Reset CFGR2 register */
  CLEAR_REG(RCC->CFGR2);
  
  /* Disable all interrupts */
  CLEAR_REG(RCC->CIR);
}
/**
  * @}
  */

#endif /* STM32F105xC || STM32F107xC || STM32F100xB || STM32F100xE */  

#if defined(STM32F105xC) || defined(STM32F107xC)
/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/**
  * @brief  Initializes the RCC Oscillators according to the specified parameters in the
  *         RCC_OscInitTypeDef.
  * @param  RCC_OscInitStruct: pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @note   The PLL is not disabled when used as system clock.
  * @note   The PLL is not disabled when USB OTG FS clock is enabled (specific to devices with USB FS)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
   uint32_t tickstart = 0;
  
  /* Check the parameters */
  assert_param(RCC_OscInitStruct != NULL);
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));
  
  /*------------------------------- HSE Configuration ------------------------*/ 
  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));
        
    /* When the HSE is used as system clock or clock source for PLL in these cases it is not allowed to be disabled */
    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HSE) 
       || ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSE)))
    {
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET) && (RCC_OscInitStruct->HSEState != RCC_HSE_ON) && (RCC_OscInitStruct->HSEState != RCC_HSE_BYPASS))
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Reset HSEON and HSEBYP bits before configuring the HSE --------------*/
      __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF);
      
      /* Get Start Tick*/
      tickstart = HAL_GetTick();
      
      /* Wait till HSE is disabled */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
      {
        if((HAL_GetTick() - tickstart ) > HSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
      
      /* Set the new HSE configuration ---------------------------------------*/
      __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);
      
      /* Check the HSE State */
      if(RCC_OscInitStruct->HSEState != RCC_HSE_OFF)
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till HSE is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
        {
          if((HAL_GetTick() - tickstart ) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till HSE is disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
        {
           if((HAL_GetTick() - tickstart ) > HSE_TIMEOUT_VALUE)
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
    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HSI) 
       || ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSI_DIV2)))
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
        /* Enable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_ENABLE();
        
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till HSI is ready */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
        {
          if((HAL_GetTick() - tickstart ) > HSI_TIMEOUT_VALUE)
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
        
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till HSI is disabled */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET)
        {
          if((HAL_GetTick() - tickstart ) > HSI_TIMEOUT_VALUE)
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
      
      /* Get Start Tick*/
      tickstart = HAL_GetTick();
      
      /* Wait till LSI is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET)
      {
        if((HAL_GetTick() - tickstart ) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
      /*  To have a fully stabilized clock in the specified range, a software temporization of 1ms 
          should be added.*/
      HAL_Delay(1);
    }
    else
    {
      /* Disable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_DISABLE();
      
      /* Get Start Tick*/
      tickstart = HAL_GetTick();
      
      /* Wait till LSI is disabled */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) != RESET)
      {
        if((HAL_GetTick() - tickstart ) > LSI_TIMEOUT_VALUE)
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
    __HAL_RCC_PWR_CLK_ENABLE();
    
    /* Enable write access to Backup domain */
    SET_BIT(PWR->CR, PWR_CR_DBP);

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
    
    /* Get Start Tick*/
    tickstart = HAL_GetTick();
    
    /* Wait till LSE is disabled */  
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
    if((RCC_OscInitStruct->LSEState) == RCC_LSE_ON)
    {
      /* Get Start Tick*/
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
      /* Get Start Tick*/
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is disabled */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /*-------------------------------- PLL2 Configuration -----------------------*/
  /* Check the parameters */
  assert_param(IS_RCC_PLL2(RCC_OscInitStruct->PLL2.PLL2State));
  if ((RCC_OscInitStruct->PLL2.PLL2State) != RCC_PLL2_NONE)
  {
    /* This bit can not be cleared if the PLL2 clock is used indirectly as system 
      clock (i.e. it is used as PLL clock entry that is used as system clock). */
    if((__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSE) && \
        (__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && \
        ((READ_BIT(RCC->CFGR2,RCC_CFGR2_PREDIV1SRC)) == RCC_CFGR2_PREDIV1SRC_PLL2))
    {
      return HAL_ERROR;
    }
    else
    {
      if((RCC_OscInitStruct->PLL2.PLL2State) == RCC_PLL2_ON)
      {
        /* Check the parameters */
        assert_param(IS_RCC_PLL2_MUL(RCC_OscInitStruct->PLL2.PLL2MUL));
        assert_param(IS_RCC_HSE_PREDIV2(RCC_OscInitStruct->PLL2.HSEPrediv2Value));

        /* Prediv2 can be written only when the PLLI2S is disabled. */
        /* Return an error only if new value is different from the programmed value */
        if (HAL_IS_BIT_SET(RCC->CR,RCC_CR_PLL3ON) && \
          (__HAL_RCC_HSE_GET_PREDIV2() != RCC_OscInitStruct->PLL2.HSEPrediv2Value))
        {
          return HAL_ERROR;
        }
        
        /* Disable the main PLL2. */
        __HAL_RCC_PLL2_DISABLE();
        
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till PLL2 is disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLL2RDY) != RESET)
        {
          if((HAL_GetTick() - tickstart ) > PLL2_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
        
        /* Configure the HSE prediv2 factor --------------------------------*/
        __HAL_RCC_HSE_PREDIV2_CONFIG(RCC_OscInitStruct->PLL2.HSEPrediv2Value);

        /* Configure the main PLL2 multiplication factors. */
        __HAL_RCC_PLL2_CONFIG(RCC_OscInitStruct->PLL2.PLL2MUL);
        
        /* Enable the main PLL2. */
        __HAL_RCC_PLL2_ENABLE();
        
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till PLL2 is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLL2RDY)  == RESET)
        {
          if((HAL_GetTick() - tickstart ) > PLL2_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
       /* Set PREDIV1 source to HSE */
        CLEAR_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC);

        /* Disable the main PLL2. */
        __HAL_RCC_PLL2_DISABLE();
 
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till PLL2 is disabled */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLL2RDY)  != RESET)
        {
          if((HAL_GetTick() - tickstart ) > PLL2_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
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

        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();
        
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till PLL is disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY)  != RESET)
        {
          if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
        
        /* Configure the HSE prediv1 factor and source --------------------------------*/
        /* It can be written only when the PLL is disabled. Not used in PLL source is different than HSE */
        if(RCC_OscInitStruct->PLL.PLLSource == RCC_PLLSOURCE_HSE)
        {
          /* Check the parameter */
          assert_param(IS_RCC_PREDIV1_SOURCE(RCC_OscInitStruct->Prediv1Source));
          assert_param(IS_RCC_HSE_PREDIV(RCC_OscInitStruct->HSEPredivValue));
          
          /* Set PREDIV1 source */
          SET_BIT(RCC->CFGR2, RCC_OscInitStruct->Prediv1Source);

          /* Set PREDIV1 Value */
          __HAL_RCC_HSE_PREDIV_CONFIG(RCC_OscInitStruct->HSEPredivValue);
        }

        /* Configure the main PLL clock source and multiplication factors. */
        __HAL_RCC_PLL_CONFIG(RCC_OscInitStruct->PLL.PLLSource,
                             RCC_OscInitStruct->PLL.PLLMUL);
        /* Enable the main PLL. */
        __HAL_RCC_PLL_ENABLE();
        
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till PLL is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY)  == RESET)
        {
          if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();
 
        /* Get Start Tick*/
        tickstart = HAL_GetTick();
        
        /* Wait till PLL is disabled */  
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY)  != RESET)
        {
          if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
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
  * @}
  */

#endif /* STM32F105xC STM32F107xC */

#if defined(STM32F101x6) || defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || defined(STM32F103xB) || \
    defined(STM32F103xE) || defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC)
/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/**
  * @brief  Initializes the CPU, AHB and APB busses clocks according to the specified 
  *         parameters in the RCC_ClkInitStruct.
  * @param  RCC_ClkInitStruct: pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @param  FLatency: FLASH Latency                   
  *          This parameter can be one of the following values:
  *            @arg FLASH_LATENCY_0:  FLASH 0 Latency cycle
  *
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency 
  *         and updated by HAL_RCC_GetHCLKFreq() function called within this function
  *
  * @note   The HSI is used (enabled by hardware) as system clock source after
  *         startup from Reset, wake-up from STOP and STANDBY mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  *           
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked). 
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source will be ready. 
  *         You can use HAL_RCC_GetClockConfig() function to know which clock is
  *         currently used as system clock source.
  * @retval None
  */
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t FLatency)
{
  uint32_t tickstart = 0;
  
  /* Check the parameters */
  assert_param(RCC_ClkInitStruct != NULL);
  assert_param(IS_RCC_CLOCKTYPE(RCC_ClkInitStruct->ClockType));
  assert_param(IS_FLASH_LATENCY(FLatency));
  
  /* To correctly read data from FLASH memory, the number of wait states (LATENCY) 
  must be correctly programmed according to the frequency of the CPU clock 
    (HCLK) of the device. */

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
      
      /* Get Start Tick*/
      tickstart = HAL_GetTick();
      
      if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSE)
        {
          if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
        {
          if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSI)
        {
          if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
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
      
      /* Get Start Tick*/
      tickstart = HAL_GetTick();
      
      if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSE)
        {
          if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
        {
          if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSI)
        {
          if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
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

#endif /* STM32F101x6 || STM32F101xB || STM32F101xE || (...) || STM32F105xC || STM32F107xC */

#if defined(STM32F105xC) || defined(STM32F107xC)
/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/**
  * @brief  Returns the SYSCLK frequency     
  *        
  * @note   The system frequency computed by this function is not the real 
  *         frequency in the chip. It is calculated based on the predefined 
  *         constant and the selected clock source:
  * @note     If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
  * @note     If SYSCLK source is HSE, function returns values based on HSE_VALUE
  *           divided by PREDIV factor(**)
  * @note     If SYSCLK source is PLL, function returns values based on HSE_VALUE
  *           divided by PREDIV factor(**) or HSI_VALUE(*) multiplied by the PLL factor.
  * @note     (*) HSI_VALUE is a constant defined in stm32f1xx_hal_conf.h file (default value
  *               8 MHz).
  * @note     (**) HSE_VALUE is a constant defined in stm32f1xx_hal_conf.h file (default value
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
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  const uint8_t aPLLMULFactorTable[12] = {0, 0, 4,  5,  6,  7,  8,  9, 0, 0, 0, 13};
  const uint8_t aPredivFactorTable[16] = { 1, 2,  3,  4,  5,  6,  7,  8, 9,10, 11, 12, 13, 14, 15, 16};
  
  uint32_t tmp_reg = 0, prediv1 = 0, pllclk = 0, pllmul = 0;
  uint32_t sysclockfreq = 0;
  uint32_t prediv2 = 0, pll2mul = 0;

  tmp_reg = RCC->CFGR;
  
  /* Get SYSCLK source -------------------------------------------------------*/
  switch (tmp_reg & RCC_CFGR_SWS)
  {
  case RCC_CFGR_SWS_HSE:  /* HSE used as system clock */
    {
      sysclockfreq = HSE_VALUE;
      break;
    }
  case RCC_CFGR_SWS_PLL:  /* PLL used as system clock */
    {
      pllmul = aPLLMULFactorTable[(uint32_t)(tmp_reg & RCC_CFGR_PLLMULL) >> POSITION_VAL(RCC_CFGR_PLLMULL)];

      if ((tmp_reg & RCC_CFGR_PLLSRC) != RCC_PLLSOURCE_HSI_DIV2)
      {
        prediv1 = aPredivFactorTable[(uint32_t)(RCC->CFGR2 & RCC_CFGR2_PREDIV1) >> POSITION_VAL(RCC_CFGR2_PREDIV1)];
        if(HAL_IS_BIT_SET(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC))
        {
          /* PLL2 selected as Prediv1 source */
          /* PLLCLK = PLL2CLK / PREDIV1 * PLLMUL with PLL2CLK = HSE/PREDIV2 * PLL2MUL */
          prediv2 = ((RCC->CFGR2 & RCC_CFGR2_PREDIV2) >> POSITION_VAL(RCC_CFGR2_PREDIV2)) + 1;
          pll2mul = ((RCC->CFGR2 & RCC_CFGR2_PLL2MUL) >> POSITION_VAL(RCC_CFGR2_PLL2MUL)) + 2;
          pllclk = (uint32_t)((((HSE_VALUE / prediv2) * pll2mul) / prediv1) * pllmul);
        }
        else
        {
          /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
          pllclk = (uint32_t)((HSE_VALUE / prediv1) * pllmul);
        }
        
        /* If PLLMUL was set to 13 means that it was to cover the case PLLMUL 6.5 (avoid using float) */
        /* In this case need to divide pllclk by 2 */
        if (pllmul == aPLLMULFactorTable[(uint32_t)(RCC_CFGR_PLLMULL6_5) >> POSITION_VAL(RCC_CFGR_PLLMULL)])
        {
            pllclk = pllclk / 2;
        }
      }
      else
      {
        /* HSI used as PLL clock source : PLLCLK = HSI/2 * PLLMUL */
        pllclk = (uint32_t)((HSI_VALUE >> 1) * pllmul);
      }
      sysclockfreq = pllclk;
      break;
    }
  case RCC_CFGR_SWS_HSI:  /* HSI used as system clock source */
  default: /* HSI used as system clock */
    {
      sysclockfreq = HSI_VALUE;
      break;
    }
  }
  return sysclockfreq;
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
  assert_param(RCC_OscInitStruct != NULL);

  /* Set all possible values for the Oscillator type parameter ---------------*/
  RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI  \
                  | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI;
  
  /* Get the Prediv1 source --------------------------------------------------*/
  RCC_OscInitStruct->Prediv1Source = READ_BIT(RCC->CFGR2,RCC_CFGR2_PREDIV1SRC);
  
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
  
  RCC_OscInitStruct->HSEPredivValue = __HAL_RCC_HSE_GET_PREDIV();

  /* Get the HSI configuration -----------------------------------------------*/
  if((RCC->CR &RCC_CR_HSION) == RCC_CR_HSION)
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_ON;
  }
  else
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_OFF;
  }
  
  RCC_OscInitStruct->HSICalibrationValue = (uint32_t)((RCC->CR & RCC_CR_HSITRIM) >> POSITION_VAL(RCC_CR_HSITRIM));
  
  /* Get the LSE configuration -----------------------------------------------*/
  if((RCC->BDCR &RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_BYPASS;
  }
  else if((RCC->BDCR &RCC_BDCR_LSEON) == RCC_BDCR_LSEON)
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
  RCC_OscInitStruct->PLL.PLLMUL = (uint32_t)(RCC->CFGR & RCC_CFGR_PLLMULL);
  
  /* Get the PLL2 configuration -----------------------------------------------*/
  if((RCC->CR &RCC_CR_PLL2ON) == RCC_CR_PLL2ON)
  {
    RCC_OscInitStruct->PLL2.PLL2State = RCC_PLL2_ON;
  }
  else
  {
    RCC_OscInitStruct->PLL2.PLL2State = RCC_PLL2_OFF;
  }
  RCC_OscInitStruct->PLL2.HSEPrediv2Value = __HAL_RCC_HSE_GET_PREDIV2();
  RCC_OscInitStruct->PLL2.PLL2MUL = (uint32_t)(RCC->CFGR2 & RCC_CFGR2_PLL2MUL);
}

/**
  * @}
  */

#endif /* STM32F105xC || STM32F107xC*/    

#if defined (STM32F100xB) || defined (STM32F100xE)
/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/**
  * @brief  Returns the SYSCLK frequency     
  *        
  * @note   The system frequency computed by this function is not the real 
  *         frequency in the chip. It is calculated based on the predefined 
  *         constant and the selected clock source:
  * @note     If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
  * @note     If SYSCLK source is HSE, function returns values based on HSE_VALUE
  *           divided by PREDIV factor(**)
  * @note     If SYSCLK source is PLL, function returns values based on HSE_VALUE
  *           divided by PREDIV factor(**) or HSI_VALUE(*) multiplied by the PLL factor.
  * @note     (*) HSI_VALUE is a constant defined in stm32f1xx.h file (default value
  *               8 MHz).
  * @note     (**) HSE_VALUE is a constant defined in stm32f1xx_hal_conf.h file (default value
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
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  const uint8_t aPLLMULFactorTable[16] = { 2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 16};
  const uint8_t aPredivFactorTable[16] = { 1, 2,  3,  4,  5,  6,  7,  8, 9,10, 11, 12, 13, 14, 15, 16};
  uint32_t tmp_reg = 0, prediv1 = 0, pllclk = 0, pllmul = 0;
  uint32_t sysclockfreq = 0;

  tmp_reg = RCC->CFGR;
  
  /* Get SYSCLK source -------------------------------------------------------*/
  switch (tmp_reg & RCC_CFGR_SWS)
  {
  case RCC_CFGR_SWS_HSE:  /* HSE used as system clock */
    {
      sysclockfreq = HSE_VALUE;
      break;
    }
  case RCC_CFGR_SWS_PLL:  /* PLL used as system clock */
    {
      pllmul = aPLLMULFactorTable[(uint32_t)(tmp_reg & RCC_CFGR_PLLMULL) >> POSITION_VAL(RCC_CFGR_PLLMULL)];
      if ((tmp_reg & RCC_CFGR_PLLSRC) != RCC_PLLSOURCE_HSI_DIV2)
      {
        prediv1 = aPredivFactorTable[(uint32_t)(RCC->CFGR2 & RCC_CFGR2_PREDIV1) >> POSITION_VAL(RCC_CFGR2_PREDIV1)];
        /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
        pllclk = (uint32_t)((HSE_VALUE / prediv1) * pllmul);
      }
      else
      {
        /* HSI used as PLL clock source : PLLCLK = HSI/2 * PLLMUL */
        pllclk = (uint32_t)((HSI_VALUE >> 1) * pllmul);
      }
      sysclockfreq = pllclk;
      break;
    }
  case RCC_CFGR_SWS_HSI:  /* HSI used as system clock source */
  default: /* HSI used as system clock */
    {
      sysclockfreq = HSI_VALUE;
      break;
    }
  }
  return sysclockfreq;
}
/**
  * @}
  */

#endif /* STM32F100xB || STM32F100xE*/    

#if defined(STM32F101x6) || defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || defined(STM32F103xB) || \
    defined(STM32F103xE) || defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC)
/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/**
  * @brief  Configures the RCC_ClkInitStruct according to the internal 
  * RCC configuration registers.
  * @param  RCC_ClkInitStruct: pointer to an RCC_ClkInitTypeDef structure that 
  * will be configured.
  * @param  pFLatency: Pointer on the Flash Latency.
  * @retval None
  */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency)
{
  /* Check the parameters */
  assert_param(RCC_ClkInitStruct != NULL);
  assert_param(pFLatency != NULL);

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
  * @}
  */

#endif /* STM32F101x6 || STM32F101xB || STM32F101xE || (...) || STM32F105xC || STM32F107xC */

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup RCCEx
  * @{
  */

/** @defgroup RCCEx_Exported_Functions RCCEx Exported Functions
  * @{
  */

/** @defgroup RCCEx_Exported_Functions_Group1 Peripheral Control functions 
 *  @brief  Extended Peripheral Control functions  
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
  * @brief  Initializes the RCC extended peripherals clocks according to the specified parameters in the
  *         RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit: pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         contains the configuration information for the Extended Peripherals clocks(RTC clock).
  *
  * @note   Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select 
  *         the RTC clock source; in this case the Backup domain will be reset in  
  *         order to modify the RTC Clock source, as consequence RTC registers (including 
  *         the backup registers) are set to their reset values.
  *
  * @note   In case of STM32F105xC or STM32F107xC devices, PLLI2S will be enabled if requested on 
  *         one of 2 I2S interfaces. When PLLI2S is enabled, you need to call HAL_RCCEx_DisablePLLI2S to
  *         manually disable it.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0, tmp_reg = 0;
#if defined(STM32F105xC) || defined(STM32F107xC)
  uint32_t  pllactive = 0;
#endif /* STM32F105xC || STM32F107xC */

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));
  
  /*------------------------------- RTC/LCD Configuration ------------------------*/ 
  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC))
    {
    /* Enable Power Controller clock */
    __HAL_RCC_PWR_CLK_ENABLE();
    
    /* Enable write access to Backup domain */
    SET_BIT(PWR->CR, PWR_CR_DBP);

    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();
    
    while((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if((HAL_GetTick() - tickstart ) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }      
    }
    
    tmp_reg = (RCC->BDCR & RCC_BDCR_RTCSEL);
    /* Reset the Backup domain only if the RTC Clock source selection is modified */ 
    if((tmp_reg != (PeriphClkInit->RTCClockSelection & RCC_BDCR_RTCSEL)))
    {
      /* Store the content of BDCR register before the reset of Backup Domain */
      tmp_reg = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));
      /* RTC Clock selection can be changed only if the Backup Domain is reset */
      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();
      /* Restore the Content of BDCR register */
      RCC->BDCR = tmp_reg;
    }

    /* If LSE is selected as RTC clock source, wait for LSE reactivation */
    if ((PeriphClkInit->RTCClockSelection == RCC_RTCCLKSOURCE_LSE))
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

    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }

  /*------------------------------ ADC clock Configuration ------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC) == RCC_PERIPHCLK_ADC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADCPLLCLK_DIV(PeriphClkInit->AdcClockSelection));
    
    /* Configure the ADC clock source */
    __HAL_RCC_ADC_CONFIG(PeriphClkInit->AdcClockSelection);
  }

#if defined(STM32F105xC) || defined(STM32F107xC)
  /*------------------------------ I2S2 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S2) == RCC_PERIPHCLK_I2S2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2S2CLKSOURCE(PeriphClkInit->I2s2ClockSelection));

    /* Configure the I2S2 clock source */
    __HAL_RCC_I2S2_CONFIG(PeriphClkInit->I2s2ClockSelection);
  }

  /*------------------------------ I2S3 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S3) == RCC_PERIPHCLK_I2S3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2S3CLKSOURCE(PeriphClkInit->I2s3ClockSelection));
    
    /* Configure the I2S3 clock source */
    __HAL_RCC_I2S3_CONFIG(PeriphClkInit->I2s3ClockSelection);
  }

  /*------------------------------ PLL I2S Configuration ----------------------*/ 
  /* Check that PLLI2S need to be enabled */
  if (HAL_IS_BIT_SET(RCC->CFGR2, RCC_CFGR2_I2S2SRC) || HAL_IS_BIT_SET(RCC->CFGR2, RCC_CFGR2_I2S3SRC))
  {
    /* Update flag to indicate that PLL I2S should be active */
    pllactive = 1;
  }

  /* Check if PLL I2S need to be enabled */
  if (pllactive == 1)
  {
    /* Enable PLL I2S only if not active */
    if (HAL_IS_BIT_CLR(RCC->CR, RCC_CR_PLL3ON))
    {
      /* Check the parameters */
      assert_param(IS_RCC_PLLI2S_MUL(PeriphClkInit->PLLI2S.PLLI2SMUL));
      assert_param(IS_RCC_HSE_PREDIV2(PeriphClkInit->PLLI2S.HSEPrediv2Value));

      /* Prediv2 can be written only when the PLL2 is disabled. */
      /* Return an error only if new value is different from the programmed value */
      if (HAL_IS_BIT_SET(RCC->CR,RCC_CR_PLL2ON) && \
        (__HAL_RCC_HSE_GET_PREDIV2() != PeriphClkInit->PLLI2S.HSEPrediv2Value))
      {
        return HAL_ERROR;
      }

      /* Configure the HSE prediv2 factor --------------------------------*/
      __HAL_RCC_HSE_PREDIV2_CONFIG(PeriphClkInit->PLLI2S.HSEPrediv2Value);

      /* Configure the main PLLI2S multiplication factors. */
      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SMUL);
      
      /* Enable the main PLLI2S. */
      __HAL_RCC_PLLI2S_ENABLE();
      
      /* Get Start Tick*/
      tickstart = HAL_GetTick();
      
      /* Wait till PLLI2S is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  == RESET)
      {
        if((HAL_GetTick() - tickstart ) > PLLI2S_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Return an error only if user wants to change the PLLI2SMUL whereas PLLI2S is active */
      if (READ_BIT(RCC->CFGR2, RCC_CFGR2_PLL3MUL) != PeriphClkInit->PLLI2S.PLLI2SMUL)
      {
          return HAL_ERROR;
      }
    }
  }
#endif /* STM32F105xC || STM32F107xC */

#if defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || \
    defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC)
  /*------------------------------ USB clock Configuration ------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USB) == RCC_PERIPHCLK_USB)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USBPLLCLK_DIV(PeriphClkInit->UsbClockSelection));
    
    /* Configure the USB clock source */
    __HAL_RCC_USB_CONFIG(PeriphClkInit->UsbClockSelection);
  }
#endif /* STM32F102x6 || STM32F102xB || STM32F103x6 || STM32F103xB || STM32F103xE || STM32F103xG || STM32F105xC || STM32F107xC */

  return HAL_OK;
}

/**
  * @brief  Get the PeriphClkInit according to the internal
  * RCC configuration registers.
  * @param  PeriphClkInit: pointer to an RCC_PeriphCLKInitTypeDef structure that 
  *         returns the configuration information for the Extended Peripherals clocks(RTC, I2S, ADC clocks).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t srcclk = 0;
  
  /* Set all possible values for the extended clock type parameter------------*/
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_RTC;

  /* Get the RTC configuration -----------------------------------------------*/
  srcclk = __HAL_RCC_GET_RTC_SOURCE();
  /* Source clock is LSE or LSI*/
  PeriphClkInit->RTCClockSelection = srcclk;

  /* Get the ADC clock configuration -----------------------------------------*/
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_ADC;
  PeriphClkInit->AdcClockSelection = __HAL_RCC_GET_ADC_SOURCE();

#if defined(STM32F105xC) || defined(STM32F107xC)
  /* Get the I2S2 clock configuration -----------------------------------------*/
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_I2S2;
  PeriphClkInit->I2s2ClockSelection = __HAL_RCC_GET_I2S2_SOURCE();

  /* Get the I2S3 clock configuration -----------------------------------------*/
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_I2S3;
  PeriphClkInit->I2s3ClockSelection = __HAL_RCC_GET_I2S3_SOURCE();

#endif /* STM32F105xC || STM32F107xC */

#if defined(STM32F103xE) || defined(STM32F103xG)
  /* Get the I2S2 clock configuration -----------------------------------------*/
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_I2S2;
  PeriphClkInit->I2s2ClockSelection = RCC_I2S2CLKSOURCE_SYSCLK;

  /* Get the I2S3 clock configuration -----------------------------------------*/
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_I2S3;
  PeriphClkInit->I2s3ClockSelection = RCC_I2S3CLKSOURCE_SYSCLK;

#endif /* STM32F103xE || STM32F103xG */

#if defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || \
    defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC)
  /* Get the USB clock configuration -----------------------------------------*/
  PeriphClkInit->PeriphClockSelection |= RCC_PERIPHCLK_USB;
  PeriphClkInit->UsbClockSelection = __HAL_RCC_GET_USB_SOURCE();
#endif /* STM32F102x6 || STM32F102xB || STM32F103x6 || STM32F103xB || STM32F103xE || STM32F103xG || STM32F105xC || STM32F107xC */
}

/**
  * @brief  Returns the peripheral clock frequency
  * @note   Returns 0 if peripheral clock is unknown
  * @param  PeriphClk: Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg RCC_PERIPHCLK_RTC:  RTC peripheral clock
  *            @arg RCC_PERIPHCLK_ADC:  ADC peripheral clock
  *            @arg RCC_PERIPHCLK_I2S2: I2S2 peripheral clock (STM32F103xE, STM32F103xG, STM32F105xC & STM32F107xC)
  *            @arg RCC_PERIPHCLK_I2S3: I2S3 peripheral clock (STM32F103xE, STM32F103xG, STM32F105xC & STM32F107xC)
  *            @arg RCC_PERIPHCLK_USB: USB peripheral clock (STM32F102xx, STM32F103xx, STM32F105xC & STM32F107xC)
  * @retval Frequency in Hz (0: means that no available frequency for the peripheral)
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
#if defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || \
    defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC)
#if defined(STM32F105xC) || defined(STM32F107xC)
  const uint8_t aPLLMULFactorTable[12] = {0, 0, 4,  5,  6,  7,  8,  9, 0, 0, 0, 13};
  const uint8_t aPredivFactorTable[16] = { 1, 2,  3,  4,  5,  6,  7,  8, 9,10, 11, 12, 13, 14, 15, 16};
#else
  const uint8_t aPLLMULFactorTable[16] = { 2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 16};
  const uint8_t aPredivFactorTable[2] = { 1, 2};
#endif
#endif
  uint32_t tmp_reg = 0, frequency = 0;
#if defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || \
    defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC)
  uint32_t prediv1 = 0, pllclk = 0, pllmul = 0;
#endif /* STM32F102x6 || STM32F102xB || STM32F103x6 || STM32F103xB || STM32F103xE || STM32F103xG || STM32F105xC || STM32F107xC */
#if defined(STM32F105xC) || defined(STM32F107xC)
  uint32_t pll2mul = 0, pll3mul = 0, prediv2 = 0;
#endif /* STM32F105xC || STM32F107xC */

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));
  
  switch (PeriphClk)
  {
#if defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || \
    defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC)
  case RCC_PERIPHCLK_USB:  
    {
      /* Get RCC configuration ------------------------------------------------------*/
      tmp_reg = RCC->CFGR;
  
      /* Check if PLL is enabled */
      if (HAL_IS_BIT_SET(RCC->CR,RCC_CR_PLLON))
      {
        pllmul = aPLLMULFactorTable[(uint32_t)(tmp_reg & RCC_CFGR_PLLMULL) >> POSITION_VAL(RCC_CFGR_PLLMULL)];
        if ((tmp_reg & RCC_CFGR_PLLSRC) != RCC_PLLSOURCE_HSI_DIV2)
        {
#if defined(STM32F105xC) || defined(STM32F107xC) || defined (STM32F100xB) || defined (STM32F100xE)
          prediv1 = aPredivFactorTable[(uint32_t)(RCC->CFGR2 & RCC_CFGR2_PREDIV1) >> POSITION_VAL(RCC_CFGR2_PREDIV1)];
#else
          prediv1 = aPredivFactorTable[(uint32_t)(RCC->CFGR & RCC_CFGR_PLLXTPRE) >> POSITION_VAL(RCC_CFGR_PLLXTPRE)];
#endif /* STM32F105xC || STM32F107xC || STM32F100xB || STM32F100xE */

#if defined(STM32F105xC) || defined(STM32F107xC)
          if(HAL_IS_BIT_SET(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC))
          {
            /* PLL2 selected as Prediv1 source */
            /* PLLCLK = PLL2CLK / PREDIV1 * PLLMUL with PLL2CLK = HSE/PREDIV2 * PLL2MUL */
            prediv2 = ((RCC->CFGR2 & RCC_CFGR2_PREDIV2) >> POSITION_VAL(RCC_CFGR2_PREDIV2)) + 1;
            pll2mul = ((RCC->CFGR2 & RCC_CFGR2_PLL2MUL) >> POSITION_VAL(RCC_CFGR2_PLL2MUL)) + 2;
            pllclk = (uint32_t)((((HSE_VALUE / prediv2) * pll2mul) / prediv1) * pllmul);
          }
          else
          {
            /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
            pllclk = (uint32_t)((HSE_VALUE / prediv1) * pllmul);
          }
          
          /* If PLLMUL was set to 13 means that it was to cover the case PLLMUL 6.5 (avoid using float) */
          /* In this case need to divide pllclk by 2 */
          if (pllmul == aPLLMULFactorTable[(uint32_t)(RCC_CFGR_PLLMULL6_5) >> POSITION_VAL(RCC_CFGR_PLLMULL)])
          {
              pllclk = pllclk / 2;
          }
#else
          if ((tmp_reg & RCC_CFGR_PLLSRC) != RCC_PLLSOURCE_HSI_DIV2)
          {
            /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
            pllclk = (uint32_t)((HSE_VALUE / prediv1) * pllmul);
          }
#endif /* STM32F105xC || STM32F107xC */
        }
        else
        {
          /* HSI used as PLL clock source : PLLCLK = HSI/2 * PLLMUL */
          pllclk = (uint32_t)((HSI_VALUE >> 1) * pllmul);
        }

        /* Calcul of the USB frequency*/
#if defined(STM32F105xC) || defined(STM32F107xC)
        /* USBCLK = PLLVCO = (2 x PLLCLK) / USB prescaler */
        if (__HAL_RCC_GET_USB_SOURCE() == RCC_USBPLLCLK_DIV2)
        {
          /* Prescaler of 2 selected for USB */ 
          frequency = pllclk;
        }
        else
        {
          /* Prescaler of 3 selected for USB */ 
          frequency = (2 * pllclk) / 3;
        }
#else
        /* USBCLK = PLLCLK / USB prescaler */
        if (__HAL_RCC_GET_USB_SOURCE() == RCC_USBPLLCLK_DIV1)
        {
          /* No prescaler selected for USB */
          frequency = pllclk;
        }
        else
        {
          /* Prescaler of 1.5 selected for USB */ 
          frequency = (pllclk * 2) / 3;
        }
#endif
      }
      break;
    }
#endif /* STM32F102x6 || STM32F102xB || STM32F103x6 || STM32F103xB || STM32F103xE || STM32F103xG || STM32F105xC || STM32F107xC */
#if defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)
  case RCC_PERIPHCLK_I2S2:  
    {
#if defined (STM32F103xE) || defined (STM32F103xG)
      /* SYSCLK used as source clock for I2S2 */
      frequency = HAL_RCC_GetSysClockFreq();
#else
      if (__HAL_RCC_GET_I2S2_SOURCE() == RCC_I2S2CLKSOURCE_SYSCLK)
      {
        /* SYSCLK used as source clock for I2S2 */
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else
      {
         /* Check if PLLI2S is enabled */
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_PLL3ON))
        {
          /* PLLI2SVCO = 2 * PLLI2SCLK = 2 * (HSE/PREDIV2 * PLL3MUL) */
          prediv2 = ((RCC->CFGR2 & RCC_CFGR2_PREDIV2) >> POSITION_VAL(RCC_CFGR2_PREDIV2)) + 1;
          pll3mul = ((RCC->CFGR2 & RCC_CFGR2_PLL3MUL) >> POSITION_VAL(RCC_CFGR2_PLL3MUL)) + 2;
          frequency = (uint32_t)(2 * ((HSE_VALUE / prediv2) * pll3mul));
        }
      }
#endif /* STM32F103xE || STM32F103xG */
      break;
    }
  case RCC_PERIPHCLK_I2S3:
    {
#if defined (STM32F103xE) || defined (STM32F103xG)
      /* SYSCLK used as source clock for I2S3 */
      frequency = HAL_RCC_GetSysClockFreq();
#else
      if (__HAL_RCC_GET_I2S3_SOURCE() == RCC_I2S3CLKSOURCE_SYSCLK)
      {
        /* SYSCLK used as source clock for I2S3 */
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else
      {
         /* Check if PLLI2S is enabled */
        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_PLL3ON))
        {
          /* PLLI2SVCO = 2 * PLLI2SCLK = 2 * (HSE/PREDIV2 * PLL3MUL) */
          prediv2 = ((RCC->CFGR2 & RCC_CFGR2_PREDIV2) >> POSITION_VAL(RCC_CFGR2_PREDIV2)) + 1;
          pll3mul = ((RCC->CFGR2 & RCC_CFGR2_PLL3MUL) >> POSITION_VAL(RCC_CFGR2_PLL3MUL)) + 2;
          frequency = (uint32_t)(2 * ((HSE_VALUE / prediv2) * pll3mul));
        }
      }
#endif /* STM32F103xE || STM32F103xG */
      break;
    }
#endif /* STM32F103xE || STM32F103xG || STM32F105xC || STM32F107xC */
  case RCC_PERIPHCLK_RTC:  
    {
      /* Get RCC BDCR configuration ------------------------------------------------------*/
      tmp_reg = RCC->BDCR;

      /* Check if LSE is ready if RTC clock selection is LSE */
      if (((tmp_reg & RCC_BDCR_RTCSEL) == RCC_RTCCLKSOURCE_LSE) && (HAL_IS_BIT_SET(tmp_reg, RCC_BDCR_LSERDY)))
      {
        frequency = LSE_VALUE;
      }
      /* Check if LSI is ready if RTC clock selection is LSI */
      else if (((tmp_reg & RCC_BDCR_RTCSEL) == RCC_RTCCLKSOURCE_LSI) && (HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)))
      {
        frequency = LSI_VALUE;
      }
      else if (((tmp_reg & RCC_BDCR_RTCSEL) == RCC_RTCCLKSOURCE_HSE_DIV128) && (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)))
      {
        frequency = HSE_VALUE / 128;
      }
      /* Clock not enabled for RTC*/
      else
      {
        frequency = 0;
      }
      break;
    }
  case RCC_PERIPHCLK_ADC:  
    {
      frequency = HAL_RCC_GetPCLK2Freq() / (((__HAL_RCC_GET_ADC_SOURCE() >> POSITION_VAL(RCC_CFGR_ADCPRE_DIV4)) + 1) * 2);
      break;
    }
  default: 
    {
      break;
    }
  }
  return(frequency);
}

/**
  * @}
  */

#if defined(STM32F105xC) || defined(STM32F107xC)
/** @defgroup RCCEx_Exported_Functions_Group2 PLLI2S Management function
 *  @brief  PLLI2S Management functions
 *
@verbatim   
 ===============================================================================
                ##### Extended PLLI2S Management functions  #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the PLLI2S
    activation or deactivation
@endverbatim
  * @{
  */

/**
  * @brief  Enable PLLI2S
  * @param  PLLI2SInit: pointer to an RCC_PLLI2SInitTypeDef structure that
  *         contains the configuration information for the PLLI2S
  * @note   The PLLI2S configuration not modified if used by I2S2 or I2S3 Interface.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_EnablePLLI2S(RCC_PLLI2SInitTypeDef  *PLLI2SInit)
{
  uint32_t tickstart = 0;

  /* Check that PLL I2S has not been already enabled by I2S2 or I2S3*/
  if (HAL_IS_BIT_CLR(RCC->CFGR2, RCC_CFGR2_I2S2SRC) && HAL_IS_BIT_CLR(RCC->CFGR2, RCC_CFGR2_I2S3SRC))
  {
    /* Check the parameters */
    assert_param(IS_RCC_PLLI2S_MUL(PLLI2SInit->PLLI2SMUL));
    assert_param(IS_RCC_HSE_PREDIV2(PLLI2SInit->HSEPrediv2Value));

    /* Prediv2 can be written only when the PLL2 is disabled. */
    /* Return an error only if new value is different from the programmed value */
    if (HAL_IS_BIT_SET(RCC->CR,RCC_CR_PLL2ON) && \
      (__HAL_RCC_HSE_GET_PREDIV2() != PLLI2SInit->HSEPrediv2Value))
    {
      return HAL_ERROR;
    }

    /* Disable the main PLLI2S. */
    __HAL_RCC_PLLI2S_DISABLE();

    /* Get Start Tick*/
    tickstart = HAL_GetTick();
    
    /* Wait till PLLI2S is ready */  
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET)
    {
      if((HAL_GetTick() - tickstart ) > PLLI2S_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    /* Configure the HSE prediv2 factor --------------------------------*/
    __HAL_RCC_HSE_PREDIV2_CONFIG(PLLI2SInit->HSEPrediv2Value);
    

    /* Configure the main PLLI2S multiplication factors. */
    __HAL_RCC_PLLI2S_CONFIG(PLLI2SInit->PLLI2SMUL);
    
    /* Enable the main PLLI2S. */
    __HAL_RCC_PLLI2S_ENABLE();
    
    /* Get Start Tick*/
    tickstart = HAL_GetTick();
    
    /* Wait till PLLI2S is ready */
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  == RESET)
    {
      if((HAL_GetTick() - tickstart ) > PLLI2S_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }
  else
  {
    /* PLLI2S cannot be modified as already used by I2S2 or I2S3 */
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable PLLI2S
  * @note   PLLI2S is not disabled if used by I2S2 or I2S3 Interface.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_DisablePLLI2S(void)
{
  uint32_t tickstart = 0;

  /* Disable PLL I2S as not requested by I2S2 or I2S3*/
  if (HAL_IS_BIT_CLR(RCC->CFGR2, RCC_CFGR2_I2S2SRC) && HAL_IS_BIT_CLR(RCC->CFGR2, RCC_CFGR2_I2S3SRC))
  {
    /* Disable the main PLLI2S. */
    __HAL_RCC_PLLI2S_DISABLE();

    /* Get Start Tick*/
    tickstart = HAL_GetTick();
    
    /* Wait till PLLI2S is ready */  
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET)
    {
      if((HAL_GetTick() - tickstart ) > PLLI2S_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }
  else
  {
    /* PLLI2S is currently used by I2S2 or I2S3. Cannot be disabled.*/
    return HAL_ERROR;
  }
  
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup RCCEx_Exported_Functions_Group3 PLL2 Management function
 *  @brief  PLL2 Management functions
 *
@verbatim   
 ===============================================================================
                ##### Extended PLL2 Management functions  #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the PLL2
    activation or deactivation
@endverbatim
  * @{
  */

/**
  * @brief  Enable PLL2
  * @param  PLL2Init: pointer to an RCC_PLL2InitTypeDef structure that
  *         contains the configuration information for the PLL2
  * @note   The PLL2 configuration not modified if used indirectly as system clock.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_EnablePLL2(RCC_PLL2InitTypeDef  *PLL2Init)
{
  uint32_t tickstart = 0;

  /* This bit can not be cleared if the PLL2 clock is used indirectly as system 
    clock (i.e. it is used as PLL clock entry that is used as system clock). */
  if((__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSE) && \
        (__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && \
        ((READ_BIT(RCC->CFGR2,RCC_CFGR2_PREDIV1SRC)) == RCC_CFGR2_PREDIV1SRC_PLL2))
  {
    return HAL_ERROR;
  }
  else
  {
    /* Check the parameters */
    assert_param(IS_RCC_PLL2_MUL(PLL2Init->PLL2MUL));
    assert_param(IS_RCC_HSE_PREDIV2(PLL2Init->HSEPrediv2Value));

    /* Prediv2 can be written only when the PLLI2S is disabled. */
    /* Return an error only if new value is different from the programmed value */
    if (HAL_IS_BIT_SET(RCC->CR,RCC_CR_PLL3ON) && \
      (__HAL_RCC_HSE_GET_PREDIV2() != PLL2Init->HSEPrediv2Value))
    {
      return HAL_ERROR;
    }

    /* Disable the main PLL2. */
    __HAL_RCC_PLL2_DISABLE();
    
    /* Get Start Tick*/
    tickstart = HAL_GetTick();
    
    /* Wait till PLL2 is disabled */
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLL2RDY) != RESET)
    {
      if((HAL_GetTick() - tickstart ) > PLL2_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
    
    /* Configure the HSE prediv2 factor --------------------------------*/
    __HAL_RCC_HSE_PREDIV2_CONFIG(PLL2Init->HSEPrediv2Value);

    /* Configure the main PLL2 multiplication factors. */
    __HAL_RCC_PLL2_CONFIG(PLL2Init->PLL2MUL);
    
    /* Enable the main PLL2. */
    __HAL_RCC_PLL2_ENABLE();
    
    /* Get Start Tick*/
    tickstart = HAL_GetTick();
    
    /* Wait till PLL2 is ready */
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLL2RDY)  == RESET)
    {
      if((HAL_GetTick() - tickstart ) > PLL2_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Disable PLL2
  * @note   PLL2 is not disabled if used indirectly as system clock.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_DisablePLL2(void)
{
  uint32_t tickstart = 0;

  /* This bit can not be cleared if the PLL2 clock is used indirectly as system 
    clock (i.e. it is used as PLL clock entry that is used as system clock). */
  if((__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSE) && \
        (__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && \
        ((READ_BIT(RCC->CFGR2,RCC_CFGR2_PREDIV1SRC)) == RCC_CFGR2_PREDIV1SRC_PLL2))
  {
    return HAL_ERROR;
  }
  else
  {
    /* Disable the main PLL2. */
    __HAL_RCC_PLL2_DISABLE();

    /* Get Start Tick*/
    tickstart = HAL_GetTick();
    
    /* Wait till PLL2 is disabled */  
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLL2RDY)  != RESET)
    {
      if((HAL_GetTick() - tickstart ) > PLL2_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @}
  */
#endif /* STM32F105xC || STM32F107xC */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

