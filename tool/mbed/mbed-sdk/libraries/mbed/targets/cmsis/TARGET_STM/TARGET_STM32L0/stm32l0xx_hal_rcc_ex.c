/**
  ******************************************************************************
  * @file    stm32l0xx_hal_rcc_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Extended RCC HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities RCC extension peripheral:
  *           + Extended Peripheral Control functions
  *  
  @verbatim                
  ==============================================================================
                      ##### RCC specific features #####
  ==============================================================================
    For CRS, RCC Extension HAL driver can be used as follows:

      (#) In System clock configuration, HSI48 need to be enabled

      (#] Enable CRS clock in IP MSP init which will use CRS functions

      (#) Call CRS functions like this
          (##) Prepare synchronization configuration necessary for HSI48 calibration
              (+++) Default values can be set for frequency Error Measurement (reload and error limit)
                        and also HSI48 oscillator smooth trimming.
              (+++) Macro __HAL_RCC_CRS_CALCULATE_RELOADVALUE can be also used to calculate 
                        directly reload value with target and synchronization frequencies values
          (##) Call function HAL_RCCEx_CRSConfig which
              (+++) Reset CRS registers to their default values.
              (+++) Configure CRS registers with synchronization configuration 
              (+++) Enable automatic calibration and frequency error counter feature

          (##) A polling function is provided to wait for complete Synchronization
              (+++) Call function 'HAL_RCCEx_CRSWaitSynchronization()'
              (+++) According to CRS status, user can decide to adjust again the calibration or continue
                        application if synchronization is OK
              
      (#) User can retrieve information related to synchronization in calling function
            HAL_RCCEx_CRSGetSynchronizationInfo()

      (#) Regarding synchronization status and synchronization information, user can try a new calibration
           in changing synchronization configuration and call again HAL_RCCEx_CRSConfig.
           Note: When the SYNC event is detected during the downcounting phase (before reaching the zero value), 
           it means that the actual frequency is lower than the target (and so, that the TRIM value should be 
           incremented), while when it is detected during the upcounting phase it means that the actual frequency 
           is higher (and that the TRIM value should be decremented).

      (#) To use IT mode, user needs to handle it in calling different macros available to do it
            (__HAL_RCC_CRS_XXX_IT). Interruptions will go through RCC Handler (RCC_IRQn/RCC_CRS_IRQHandler)
              (+++) Call function HAL_RCCEx_CRSConfig()
              (+++) Enable RCC_IRQn (thnaks to NVIC functions)
              (+++) Enable CRS IT (__HAL_RCC_CRS_ENABLE_IT)
              [+++) Implement CRS status management in RCC_CRS_IRQHandler

      (#) To force a SYNC EVENT, user can use function 'HAL_RCCEx_CRSSoftwareSynchronizationGenerate()'. Function can be 
            called before calling HAL_RCCEx_CRSConfig (for instance in Systick handler)
       
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

/** @addtogroup RCCEx 
  * @brief RCC Extension HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/** @defgroup RCCEx_Private_Constants
  * @{
  */
/* Bit position in register */
#define CRS_CFGR_FELIM_BITNUMBER    16
#define CRS_CR_TRIM_BITNUMBER       8
#define CRS_ISR_FECAP_BITNUMBER     16

/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
 *  @brief  Extended Peripheral Initialization and Control functions  
 *
@verbatim   
 ===============================================================================
                      ##### Extended Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks 
    frequencies.
      
@endverbatim
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *           - MSI ON and used as system clock source (MSI range is not modified
  *           - by this function, it keep the value configured by user application)
  *           - HSI, HSI_OUT, HSE and PLL OFF
  *           - AHB, APB1 and APB2 prescaler set to 1.
  *           - CSS and MCO OFF
  *           - All interrupts disabled
  * @note   This function does not modify the configuration of the
  * @note      -Peripheral clocks
  * @note      -HSI48, LSI, LSE and RTC clocks                  
  * @param  None
  * @retval None
  */
void HAL_RCC_DeInit(void)
{
  /* Set MSION bit */
  SET_BIT(RCC->CR, RCC_CR_MSION); 
  
#if defined(STM32L073xx) || defined(STM32L083xx) || \
    defined(STM32L072xx) || defined(STM32L082xx) || \
    defined(STM32L071xx) || defined(STM32L081xx)
  /* Reset HSE, HSI, CSS, PLL */
  CLEAR_BIT(RCC->CR, RCC_CR_HSION| RCC_CR_HSIKERON| RCC_CR_HSIDIVEN | RCC_CR_HSIOUTEN | \
                     RCC_CR_HSEON | RCC_CR_CSSHSEON | RCC_CR_PLLON); 
#else
  CLEAR_BIT(RCC->CR, RCC_CR_HSION| RCC_CR_HSIKERON| RCC_CR_HSIDIVEN | \
                     RCC_CR_HSEON | RCC_CR_CSSHSEON | RCC_CR_PLLON); 
#endif

  /* Reset HSEBYP bit */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
  
  /* Reset CFGR register */
  CLEAR_REG(RCC->CFGR);
  
  /* Disable all interrupts */
  CLEAR_REG(RCC->CIER); 
}

/**
  * @brief  Initializes the RCC extended peripherals clocks 
  * @note   Initializes the RCC extended peripherals clocks according to the specified parameters in the
  *         RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit: pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         contains the configuration information for the Extended Peripherals clocks(USART1,USART2, LPUART1, 
  *         I2C1, I2C3, RTC, USB/RNG  and LPTIM1 clocks).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0;   
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLK(PeriphClkInit->PeriphClockSelection));

#if !defined (STM32L031xx) && !defined (STM32L041xx)
  /*------------------------------- USART1 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART1) == RCC_PERIPHCLK_USART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART1CLKSOURCE(PeriphClkInit->Usart1ClockSelection));
    
    /* Configure the USART1 clock source */
    __HAL_RCC_USART1_CONFIG(PeriphClkInit->Usart1ClockSelection);
  }
#endif
  
  /*----------------------------- USART2 Configuration --------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART2CLKSOURCE(PeriphClkInit->Usart2ClockSelection));
    
    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(PeriphClkInit->Usart2ClockSelection);
  }
  
  /*------------------------------ LPUART1 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1CLKSOURCE(PeriphClkInit->Lpuart1ClockSelection));
    
    /* Configure the LPUAR1 clock source */
    __HAL_RCC_LPUART1_CONFIG(PeriphClkInit->Lpuart1ClockSelection);
  }

  /*------------------------------ I2C1 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(PeriphClkInit->I2c1ClockSelection));
    
    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(PeriphClkInit->I2c1ClockSelection);
  }

#if defined (STM32L071xx) || (STM32L072xx) || defined(STM32L073xx) || \
    defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)
    /*------------------------------ I2C3 Configuration ------------------------*/ 
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C3) == RCC_PERIPHCLK_I2C3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLKSOURCE(PeriphClkInit->I2c3ClockSelection));
    
    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(PeriphClkInit->I2c3ClockSelection);
  }  
#endif /* defined (STM32L071xx) (STM32L072xx)|| (STM32L073xx)|| (STM32L081xx)|| (STM32L082xx) || (STM32L083xx) */

  /*---------------------------- RTC/LCD configuration -------------------------------*/
  if((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC)
#if defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx)
    || (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LCD) == RCC_PERIPHCLK_LCD)
#endif /* defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx) */
  )
  {
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
    
    /* Reset the Backup domain only if the RTC Clock source selection is modified */ 
    if(((RCC->CSR & RCC_CSR_RTCSEL) != (PeriphClkInit->RTCClockSelection & RCC_CSR_RTCSEL))
#if defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx)
    || (tmpreg != (PeriphClkInit->LCDClockSelection & RCC_CSR_RTCSEL))
#endif /* defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx) */
    )
    {
      /* Store the content of CSR register before the reset of Backup Domain */
      tmpreg = (RCC->CSR & ~(RCC_CSR_RTCSEL));
      /* RTC Clock selection can be changed only if the Backup Domain is reset */
      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();
      /* Restore the Content of CSR register */
      RCC->CSR = tmpreg;
    }
    
    /* If LSE is selected as RTC clock source, wait for LSE reactivation */
    if((PeriphClkInit->RTCClockSelection == RCC_RTCCLKSOURCE_LSE)
#if defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx)
    || (PeriphClkInit->LCDClockSelection == RCC_RTCCLKSOURCE_LSE)
#endif /* defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx) */
    )
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
#if !defined (STM32L031xx) && !defined (STM32L041xx) && !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx) && !defined(STM32L081xx)  
 /*---------------------------- USB and RNG configuration --------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USB) == (RCC_PERIPHCLK_USB))
  {
    assert_param(IS_RCC_USBCLKSOURCE(PeriphClkInit->UsbClockSelection));
    __HAL_RCC_USB_CONFIG(PeriphClkInit->UsbClockSelection);
  }
#endif
  
  /*---------------------------- LPTIM1 configuration ------------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == (RCC_PERIPHCLK_LPTIM1))
  {
    assert_param(IS_RCC_LPTIMCLK(PeriphClkInit->LptimClockSelection));
    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->LptimClockSelection);
  }
  return HAL_OK;
}



/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  PeriphClkInit: pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals clocks(USART1,USART2, LPUART1, 
  *         I2C1, I2C3, RTC, USB/RNG  and LPTIM1 clocks).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
   /* Set all possible values for the extended clock type parameter -----------*/
  /* Common part first */
#if defined(STM32L031xx) || defined(STM32L041xx)   
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_I2C1   | \
                                        RCC_PERIPHCLK_RTC    | RCC_PERIPHCLK_LPTIM1;
#endif
#if defined(STM32L052xx) || defined(STM32L062xx)
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_LPUART1 | \
                                        RCC_PERIPHCLK_I2C1   |  RCC_PERIPHCLK_RTC   | RCC_PERIPHCLK_USB     | \
                                        RCC_PERIPHCLK_LPTIM1 ;
#endif
#if  defined(STM32L053xx) || defined(STM32L063xx)
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_LPUART1 | \
                                        RCC_PERIPHCLK_I2C1   |  RCC_PERIPHCLK_RTC   | RCC_PERIPHCLK_USB     | \
                                        RCC_PERIPHCLK_LPTIM1 |  RCC_PERIPHCLK_LCD;
#endif
#if defined(STM32L072xx) || defined(STM32L082xx)
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_LPUART1 | \
                                        RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C3   | RCC_PERIPHCLK_RTC     | \
                                        RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_LPTIM1 ;
#endif
#if defined(STM32L073xx) || defined(STM32L083xx)
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_LPUART1 | \
                                        RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C3   | RCC_PERIPHCLK_RTC     | \
                                        RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_LPTIM1 |  RCC_PERIPHCLK_LCD;
  
#endif
#if defined(STM32L051xx) || defined(STM32L061xx)   
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_LPUART1 | \
                                        RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_RTC    | RCC_PERIPHCLK_LPTIM1;
#endif
#if defined(STM32L071xx) || defined(STM32L081xx) 
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_LPUART1 | \
                                        RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C3   | RCC_PERIPHCLK_RTC     | \
                                        RCC_PERIPHCLK_LPTIM1;
#endif 

#if !defined (STM32L031xx) && !defined (STM32L041xx)
  /* Get the USART1 configuration --------------------------------------------*/
  PeriphClkInit->Usart1ClockSelection  = __HAL_RCC_GET_USART1_SOURCE();
#endif
  /* Get the USART2 clock source ---------------------------------------------*/
  PeriphClkInit->Usart2ClockSelection  = __HAL_RCC_GET_USART2_SOURCE();
  /* Get the LPUART1 clock source ---------------------------------------------*/
  PeriphClkInit->Lpuart1ClockSelection = __HAL_RCC_GET_LPUART1_SOURCE();
  /* Get the I2C1 clock source -----------------------------------------------*/
  PeriphClkInit->I2c1ClockSelection    = __HAL_RCC_GET_I2C1_SOURCE();
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || \
    defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)
/* Get the I2C3 clock source -----------------------------------------------*/
  PeriphClkInit->I2c3ClockSelection    = __HAL_RCC_GET_I2C3_SOURCE();
#endif /* defined (STM32L071xx) || (STM32L073xx) || (STM32L082xx) || (STM32L082xx) || (STM32L083xx)  */
  /* Get the LPTIM1 clock source -----------------------------------------------*/
  PeriphClkInit->LptimClockSelection   = __HAL_RCC_GET_LPTIM1_SOURCE();
  /* Get the RTC clock source -----------------------------------------------*/
  PeriphClkInit->RTCClockSelection     = __HAL_RCC_GET_RTC_SOURCE();
#if defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx)
  PeriphClkInit->LCDClockSelection = PeriphClkInit->RTCClockSelection;
#endif /* defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx) */

#if !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx) && !defined(STM32L081xx)  
  /* Get the USB/RNG clock source -----------------------------------------------*/
  PeriphClkInit->UsbClockSelection  = __HAL_RCC_GET_USB_SOURCE();
#endif
}

/**
  * @brief  Enables the LSE Clock Security System.
  * @param  None
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS(void)
{
   SET_BIT(RCC->CSR, RCC_CSR_LSECSSON) ;
}

/**
  * @brief  Disables the LSE Clock Security System.
  * @param  None
  * @retval None
  */
void HAL_RCCEx_DisableLSECSS(void)
{
   CLEAR_BIT(RCC->CSR, RCC_CSR_LSECSSON) ;
}

#if !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx) && !defined(STM32L081xx)
    
/**
  * @brief  Start automatic synchronization using polling mode
  * @param  pInit Pointer on RCC_CRSInitTypeDef structure
  * @retval None
  */
void HAL_RCCEx_CRSConfig(RCC_CRSInitTypeDef *pInit)
{
  /* Check the parameters */
  assert_param(IS_RCC_CRS_SYNC_DIV(pInit->Prescaler));
  assert_param(IS_RCC_CRS_SYNC_SOURCE(pInit->Source));
  assert_param(IS_RCC_CRS_SYNC_POLARITY(pInit->Polarity));
  assert_param(IS_RCC_CRS_RELOADVALUE(pInit->ReloadValue));
  assert_param(IS_RCC_CRS_ERRORLIMIT(pInit->ErrorLimitValue));
  assert_param(IS_RCC_CRS_HSI48CALIBRATION(pInit->HSI48CalibrationValue));


  /* CONFIGURATION */

  /* Before configuration, reset CRS registers to their default values*/
  __HAL_RCC_CRS_FORCE_RESET();
  __HAL_RCC_CRS_RELEASE_RESET();

  /* Configure Synchronization input */
  /* Clear SYNCDIV[2:0], SYNCSRC[1:0] & SYNCSPOL bits */
  CRS->CFGR &= ~(CRS_CFGR_SYNCDIV | CRS_CFGR_SYNCSRC | CRS_CFGR_SYNCPOL);

  /* Set the CRS_CFGR_SYNCDIV[2:0] bits according to Prescaler value */
  CRS->CFGR |= pInit->Prescaler;

  /* Set the SYNCSRC[1:0] bits according to Source value */
  CRS->CFGR |= pInit->Source;

  /* Set the SYNCSPOL bits according to Polarity value */
  CRS->CFGR |= pInit->Polarity;

  /* Configure Frequency Error Measurement */
  /* Clear RELOAD[15:0] & FELIM[7:0] bits*/
  CRS->CFGR &= ~(CRS_CFGR_RELOAD | CRS_CFGR_FELIM);

  /* Set the RELOAD[15:0] bits according to ReloadValue value */
  CRS->CFGR |= pInit->ReloadValue;

  /* Set the FELIM[7:0] bits according to ErrorLimitValue value */
  CRS->CFGR |= (pInit->ErrorLimitValue << CRS_CFGR_FELIM_BITNUMBER);

  /* Adjust HSI48 oscillator smooth trimming */
  /* Clear TRIM[5:0] bits */
  CRS->CR &= ~CRS_CR_TRIM;

  /* Set the TRIM[5:0] bits according to RCC_CRS_HSI48CalibrationValue value */
  CRS->CR |= (pInit->HSI48CalibrationValue << CRS_CR_TRIM_BITNUMBER);


  /* START AUTOMATIC SYNCHRONIZATION*/
  
  /* Enable Automatic trimming */
  __HAL_RCC_CRS_ENABLE_AUTOMATIC_CALIB();

  /* Enable Frequency error counter */
  __HAL_RCC_CRS_ENABLE_FREQ_ERROR_COUNTER();

}

/**
  * @brief  Generate the software synchronization event
  * @param  None
  * @retval None
  */
void HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void)
{
  CRS->CR |= CRS_CR_SWSYNC;
}


/**
  * @brief  Function to return synchronization info 
  * @param  pSynchroInfo Pointer on RCC_CRSSynchroInfoTypeDef structure
  * @retval None
  */
void HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo)
{
  /* Check the parameter */
  assert_param(pSynchroInfo != NULL);
  
  /* Get the reload value */
  pSynchroInfo->ReloadValue = (uint32_t)(CRS->CFGR & CRS_CFGR_RELOAD);
  
  /* Get HSI48 oscillator smooth trimming */
  pSynchroInfo->HSI48CalibrationValue = (uint32_t)((CRS->CR & CRS_CR_TRIM) >> CRS_CR_TRIM_BITNUMBER);

  /* Get Frequency error capture */
  pSynchroInfo->FreqErrorCapture = (uint32_t)((CRS->ISR & CRS_ISR_FECAP) >> CRS_ISR_FECAP_BITNUMBER);

  /* Get Frequency error direction */
  pSynchroInfo->FreqErrorDirection = (uint32_t)(CRS->ISR & CRS_ISR_FEDIR);
  
  
}

/**
* @brief This function handles CRS Synchronization Timeout.
* @param Timeout: Duration of the timeout
* @note  Timeout is based on the maximum time to receive a SYNC event based on synchronization
*        frequency.
* @note    If Timeout set to HAL_MAX_DELAY, HAL_TIMEOUT will be never returned.
* @retval Combination of Synchronization status
*          This parameter can be a combination of the following values:
*            @arg RCC_CRS_TIMEOUT
*            @arg RCC_CRS_SYNCOK
*            @arg RCC_CRS_SYNCWARM
*            @arg RCC_CRS_SYNCERR
*            @arg RCC_CRS_SYNCMISS
*            @arg RCC_CRS_TRIMOV
*/
uint32_t HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout)
{
  uint32_t crsstatus = RCC_CRS_NONE;
  uint32_t tickstart = 0;
  
  /* Get timeout */
  tickstart = HAL_GetTick();
  
  /* Check that if one of CRS flags have been set */
  while(RCC_CRS_NONE == crsstatus)
  {
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        crsstatus = RCC_CRS_TIMEOUT;
      }
    }
    /* Check CRS SYNCOK flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCOK))
    {
      /* CRS SYNC event OK */
      crsstatus |= RCC_CRS_SYNCOK;
    
      /* Clear CRS SYNC event OK bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCOK);
    }
    
    /* Check CRS SYNCWARN flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCWARN))
    {
      /* CRS SYNC warning */
      crsstatus |= RCC_CRS_SYNCWARM;
    
      /* Clear CRS SYNCWARN bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCWARN);
    }
    
    /* Check CRS TRIM overflow flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_TRIMOVF))
    {
      /* CRS SYNC Error */
      crsstatus |= RCC_CRS_TRIMOV;
    
      /* Clear CRS Error bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_TRIMOVF);
    }
    
    /* Check CRS Error flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCERR))
    {
      /* CRS SYNC Error */
      crsstatus |= RCC_CRS_SYNCERR;
    
      /* Clear CRS Error bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCERR);
    }
    
    /* Check CRS SYNC Missed flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCMISS))
    {
      /* CRS SYNC Missed */
      crsstatus |= RCC_CRS_SYNCMISS;
    
      /* Clear CRS SYNC Missed bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCMISS);
    }
    
    /* Check CRS Expected SYNC flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_ESYNC))
    {
      /* frequency error counter reached a zero value */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_ESYNC);
    }
  }

  return crsstatus;
}         
/**
  * @brief Enables Vrefint for the HSI48.
  * @param None
  * @note  This is functional only if the LOCK is not set  
  * @retval None
  */
void HAL_RCCEx_EnableHSI48_VREFINT(void)
{
    /* Enable the Buffer for the ADC by setting EN_VREFINT bit  */
    /* and the SYSCFG_CFGR3_ENREF_HSI48 in the CFGR3 register   */
    SET_BIT (SYSCFG->CFGR3, (SYSCFG_CFGR3_ENREF_HSI48 | SYSCFG_CFGR3_EN_VREFINT)); 
}

/**
  * @brief Disables the Vrefint for the HSI48.
  * @param None.
  * @note  This is functional only if the LOCK is not set  
  * @retval None
  */
void HAL_RCCEx_DisableHSI48_VREFINT(void)
{
    /* Disable the Vrefint by resetting SYSCFG_CFGR3_ENREF_HSI48 bit */ 
    /*  and the EN_VREFINT bit in the CFGR3 register */
    CLEAR_BIT(SYSCFG->CFGR3, (SYSCFG_CFGR3_ENREF_HSI48 | SYSCFG_CFGR3_EN_VREFINT));
}
#endif /* !defined (STM32L031xx) && !defined (STM32L041xx) && !defined(STM32L051xx) && !defined(STM32L061xx) && !defined(STM32L071xx) && !defined(STM32L081xx) */


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

