/**
  ******************************************************************************
  * @file    stm32f30x_rcc.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Reset and clock control (RCC) peripheral:           
  *           + Internal/external clocks, PLL, CSS and MCO configuration
  *           + System, AHB and APB busses clocks configuration
  *           + Peripheral clocks configuration
  *           + Interrupts and flags management
  *
  @verbatim
               
 ===============================================================================
                      ##### RCC specific features #####
 ===============================================================================
    [..] After reset the device is running from HSI (8 MHz) with Flash 0 WS, 
         all peripherals are off except internal SRAM, Flash and SWD.
         (+) There is no prescaler on High speed (AHB) and Low speed (APB) busses;
             all peripherals mapped on these busses are running at HSI speed.
       	 (+) The clock for all peripherals is switched off, except the SRAM and FLASH.
         (+) All GPIOs are in input floating state, except the SWD pins which
             are assigned to be used for debug purpose.
    [..] Once the device starts from reset, the user application has to:        
         (+) Configure the clock source to be used to drive the System clock
             (if the application needs higher frequency/performance).
         (+) Configure the System clock frequency and Flash settings.  
         (+) Configure the AHB and APB busses prescalers.
         (+) Enable the clock for the peripheral(s) to be used.
         (+) Configure the clock source(s) for peripherals which clocks are not
             derived from the System clock (ADC, TIM, I2C, USART, RTC and IWDG).      
                        
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
#include "stm32f30x_rcc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC 
  * @brief RCC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ------------ RCC registers bit address in the alias region ----------- */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)

/* --- CR Register ---*/

/* Alias word address of HSION bit */
#define CR_OFFSET                 (RCC_OFFSET + 0x00)
#define HSION_BitNumber           0x00
#define CR_HSION_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (HSION_BitNumber * 4))

/* Alias word address of PLLON bit */
#define PLLON_BitNumber           0x18
#define CR_PLLON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLLON_BitNumber * 4))

/* Alias word address of CSSON bit */
#define CSSON_BitNumber           0x13
#define CR_CSSON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (CSSON_BitNumber * 4))

/* --- CFGR Register ---*/
/* Alias word address of USBPRE bit */
#define CFGR_OFFSET               (RCC_OFFSET + 0x04)
#define USBPRE_BitNumber          0x16
#define CFGR_USBPRE_BB            (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (USBPRE_BitNumber * 4))
/* Alias word address of I2SSRC bit */
#define I2SSRC_BitNumber          0x17
#define CFGR_I2SSRC_BB            (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (I2SSRC_BitNumber * 4))

/* --- BDCR Register ---*/

/* Alias word address of RTCEN bit */
#define BDCR_OFFSET               (RCC_OFFSET + 0x20)
#define RTCEN_BitNumber           0x0F
#define BDCR_RTCEN_BB             (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (RTCEN_BitNumber * 4))

/* Alias word address of BDRST bit */
#define BDRST_BitNumber           0x10
#define BDCR_BDRST_BB             (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (BDRST_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of LSION bit */
#define CSR_OFFSET                (RCC_OFFSET + 0x24)
#define LSION_BitNumber           0x00
#define CSR_LSION_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (LSION_BitNumber * 4))

/* ---------------------- RCC registers bit mask ------------------------ */
/* RCC Flag Mask */
#define FLAG_MASK                 ((uint8_t)0x1F)

/* CFGR register byte 3 (Bits[31:23]) base address */
#define CFGR_BYTE3_ADDRESS        ((uint32_t)0x40021007)

/* CIR register byte 2 (Bits[15:8]) base address */
#define CIR_BYTE2_ADDRESS         ((uint32_t)0x40021009)

/* CIR register byte 3 (Bits[23:16]) base address */
#define CIR_BYTE3_ADDRESS         ((uint32_t)0x4002100A)

/* CR register byte 2 (Bits[23:16]) base address */
#define CR_BYTE2_ADDRESS          ((uint32_t)0x40021002)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
const uint16_t ADCPrescTable[16] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256, 0, 0, 0, 0 };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RCC_Private_Functions
  * @{
  */

/** @defgroup RCC_Group1 Internal and external clocks, PLL, CSS and MCO configuration functions
 *  @brief   Internal and external clocks, PLL, CSS and MCO configuration functions 
 *
@verbatim   
 ===============================================================================
 ##### Internal-external clocks, PLL, CSS and MCO configuration functions #####
 ===============================================================================  
    [..] This section provides functions allowing to configure the internal/external 
         clocks, PLL, CSS and MCO.
         (#) HSI (high-speed internal), 8 MHz factory-trimmed RC used directly 
             or through the PLL as System clock source.
             The HSI clock can be used also to clock the USART and I2C peripherals.
         (#) LSI (low-speed internal), 40 KHz low consumption RC used as IWDG and/or RTC
             clock source.
         (#) HSE (high-speed external), 4 to 32 MHz crystal oscillator used directly or
             through the PLL as System clock source. Can be used also as RTC clock source.
         (#) LSE (low-speed external), 32 KHz oscillator used as RTC clock source.
             LSE can be used also to clock the USART peripherals.
         (#) PLL (clocked by HSI or HSE), for System clock.
         (#) CSS (Clock security system), once enabled and if a HSE clock failure occurs 
             (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled. 
             The interrupt is linked to the Cortex-M4 NMI (Non-Maskable Interrupt) 
             exception vector.   
         (#) MCO (microcontroller clock output), used to output SYSCLK, HSI, HSE, LSI, LSE,
             PLL clock on PA8 pin.

@endverbatim
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  * @note     HSI ON and used as system clock source 
  * @note     HSE and PLL OFF
  * @note     AHB, APB1 and APB2 prescalers set to 1.
  * @note     CSS and MCO OFF
  * @note     All interrupts disabled
  * @note   However, this function doesn't modify the configuration of the
  * @note     Peripheral clocks
  * @note     LSI, LSE and RTC clocks                  
  * @param  None
  * @retval None
  */
void RCC_DeInit(void)
{
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0] and MCOSEL[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FFC000;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

  /* Reset PREDIV1[3:0] and ADCPRE[13:4] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFC000;

  /* Reset USARTSW[1:0], I2CSW and TIMSW bits */
  RCC->CFGR3 &= (uint32_t)0xF00ECCC;
  
  /* Disable all interrupts */
  RCC->CIR = 0x00000000;
}

/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.         
  * @note   This function resets the CSSON bit, so if the Clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  RCC_HSE: specifies the new state of the HSE.
  *   This parameter can be one of the following values:
  *     @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                       6 HSE oscillator clock cycles.
  *     @arg RCC_HSE_ON: turn ON the HSE oscillator
  *     @arg RCC_HSE_Bypass: HSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_HSEConfig(uint8_t RCC_HSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSE(RCC_HSE));

  /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
  *(__IO uint8_t *) CR_BYTE2_ADDRESS = RCC_HSE_OFF;

  /* Set the new HSE configuration -------------------------------------------*/
  *(__IO uint8_t *) CR_BYTE2_ADDRESS = RCC_HSE;

}

/**
  * @brief  Waits for HSE start-up.
  * @note   This function waits on HSERDY flag to be set and return SUCCESS if 
  *         this flag is set, otherwise returns ERROR if the timeout is reached 
  *         and this flag is not set. The timeout value is defined by the constant
  *         HSE_STARTUP_TIMEOUT in stm32f30x.h file. You can tailor it depending
  *         on the HSE crystal used in your application. 
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: HSE oscillator is stable and ready to use
  *          - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;
  
  /* Wait till HSE is ready and if timeout is reached exit */
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;  
  } while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));
  
  if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
  return (status);
}

/**
  * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  *         Refer to the Application Note AN3300 for more details on how to  
  *         calibrate the HSI.
  * @param  HSICalibrationValue: specifies the HSI calibration trimming value.
  *         This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HSI_CALIBRATION_VALUE(HSICalibrationValue));
  
  tmpreg = RCC->CR;
  
  /* Clear HSITRIM[4:0] bits */
  tmpreg &= ~RCC_CR_HSITRIM;
  
  /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
  tmpreg |= (uint32_t)HSICalibrationValue << 3;
  
  /* Store the new value */
  RCC->CR = tmpreg;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note   After enabling the HSI, the application software should wait on 
  *         HSIRDY flag to be set indicating that HSI clock is stable and can
  *         be used to clock the PLL and/or system clock.
  * @note   HSI can not be stopped if it is used directly or through the PLL
  *         as system clock. In this case, you have to select another source 
  *         of the system clock then stop the HSI.
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes. 
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.    
  * @param  NewState: new state of the HSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(__IO uint32_t *) CR_HSION_BB = (uint32_t)NewState;
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @note     As the LSE is in the Backup domain and write access is denied to this
  *           domain after reset, you have to enable write access using 
  *           PWR_BackupAccessCmd(ENABLE) function before to configure the LSE
  *           (to be done once after reset).
  * @note     After enabling the LSE (RCC_LSE_ON or RCC_LSE_Bypass), the application
  *           software should wait on LSERDY flag to be set indicating that LSE clock
  *           is stable and can be used to clock the RTC.
  * @param  RCC_LSE: specifies the new state of the LSE.
  *   This parameter can be one of the following values:
  *     @arg RCC_LSE_OFF: turn OFF the LSE oscillator, LSERDY flag goes low after
  *                       6 LSE oscillator clock cycles.
  *     @arg RCC_LSE_ON: turn ON the LSE oscillator
  *     @arg RCC_LSE_Bypass: LSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_LSEConfig(uint32_t RCC_LSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE(RCC_LSE));

  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* Reset LSEON bit */
  RCC->BDCR &= ~(RCC_BDCR_LSEON);

  /* Reset LSEBYP bit */
  RCC->BDCR &= ~(RCC_BDCR_LSEBYP);

  /* Configure LSE */
  RCC->BDCR |= RCC_LSE;
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE) drive capability.
  * @param  RCC_LSEDrive: specifies the new state of the LSE drive capability.
  *   This parameter can be one of the following values:
  *     @arg RCC_LSEDrive_Low: LSE oscillator low drive capability.
  *     @arg RCC_LSEDrive_MediumLow: LSE oscillator medium low drive capability.
  *     @arg RCC_LSEDrive_MediumHigh: LSE oscillator medium high drive capability.
  *     @arg RCC_LSEDrive_High: LSE oscillator high drive capability.
  * @retval None
  */
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE_DRIVE(RCC_LSEDrive));
  
  /* Clear LSEDRV[1:0] bits */
  RCC->BDCR &= ~(RCC_BDCR_LSEDRV);

  /* Set the LSE Drive */
  RCC->BDCR |= RCC_LSEDrive;
}

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).  
  * @note   After enabling the LSI, the application software should wait on 
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.  
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @param  NewState: new state of the LSI.
  *         This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void RCC_LSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(__IO uint32_t *) CSR_LSION_BB = (uint32_t)NewState;
}

/**
  * @brief  Configures the PLL clock source and multiplication factor.
  * @note   This function must be used only when the PLL is disabled.
  * @note   The minimum input clock frequency for PLL is 2 MHz (when using HSE as
  *         PLL source).   
  * @param  RCC_PLLSource: specifies the PLL entry clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_PLLSource_HSI_Div2: HSI oscillator clock divided by 2 selected as
  *         PLL clock entry
  *     @arg RCC_PLLSource_PREDIV1: PREDIV1 clock selected as PLL clock source              
  * @param  RCC_PLLMul: specifies the PLL multiplication factor, which drive the PLLVCO clock
  *   This parameter can be RCC_PLLMul_x where x:[2,16] 
  *                                               
  * @retval None
  */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  /* Check the parameters */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));
  
  /* Clear PLL Source [16] and Multiplier [21:18] bits */
  RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC);

  /* Set the PLL Source and Multiplier */
  RCC->CFGR |= (uint32_t)(RCC_PLLSource | RCC_PLLMul);
}

/**
  * @brief  Enables or disables the PLL.
  * @note   After enabling the PLL, the application software should wait on 
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The PLL can not be disabled if it is used as system clock source
  * @note   The PLL is disabled by hardware when entering STOP and STANDBY modes.    
  * @param  NewState: new state of the PLL.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLLCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CR_PLLON_BB = (uint32_t)NewState;
}

/**
  * @brief  Configures the PREDIV1 division factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PREDIV1_Div: specifies the PREDIV1 clock division factor.
  *         This parameter can be RCC_PREDIV1_Divx where x:[1,16]
  * @retval None
  */
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Div)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_PREDIV1(RCC_PREDIV1_Div));

  tmpreg = RCC->CFGR2;
  /* Clear PREDIV1[3:0] bits */
  tmpreg &= ~(RCC_CFGR2_PREDIV1);

  /* Set the PREDIV1 division factor */
  tmpreg |= RCC_PREDIV1_Div;

  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}

/**
  * @brief  Enables or disables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to 
  *         the Cortex-M4 NMI (Non-Maskable Interrupt) exception vector.  
  * @param  NewState: new state of the Clock Security System.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(__IO uint32_t *) CR_CSSON_BB = (uint32_t)NewState;
}

#ifdef STM32F303xC
/**
  * @brief  Selects the clock source to output on MCO pin (PA8).
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOSource: specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOSource_NoClock: No clock selected.
  *            @arg RCC_MCOSource_HSI14: HSI14 oscillator clock selected.
  *            @arg RCC_MCOSource_LSI: LSI oscillator clock selected.
  *            @arg RCC_MCOSource_LSE: LSE oscillator clock selected.
  *            @arg RCC_MCOSource_SYSCLK: System clock selected.
  *            @arg RCC_MCOSource_HSI: HSI oscillator clock selected.
  *            @arg RCC_MCOSource_HSE: HSE oscillator clock selected.
  *            @arg RCC_MCOSource_PLLCLK_Div2: PLL clock divided by 2 selected.
  *            @arg RCC_MCOSource_PLLCLK: PLL clock selected.
  *            @arg RCC_MCOSource_HSI48: HSI48 clock selected.  
  * @retval None
  */
void RCC_MCOConfig(uint8_t RCC_MCOSource)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));

  /* Get CFGR value */  
  tmpreg = RCC->CFGR;
  /* Clear MCO[3:0] bits */
  tmpreg &= ~(RCC_CFGR_MCO | RCC_CFGR_PLLNODIV);
  /* Set the RCC_MCOSource */
  tmpreg |= RCC_MCOSource<<24;
  /* Store the new value */
  RCC->CFGR = tmpreg;
}
#else

/**
  * @brief  Selects the clock source to output on MCO pin (PA8) and the corresponding
  *         prescsaler.
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOSource: specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOSource_NoClock: No clock selected.
  *            @arg RCC_MCOSource_HSI14: HSI14 oscillator clock selected.
  *            @arg RCC_MCOSource_LSI: LSI oscillator clock selected.
  *            @arg RCC_MCOSource_LSE: LSE oscillator clock selected.
  *            @arg RCC_MCOSource_SYSCLK: System clock selected.
  *            @arg RCC_MCOSource_HSI: HSI oscillator clock selected.
  *            @arg RCC_MCOSource_HSE: HSE oscillator clock selected.
  *            @arg RCC_MCOSource_PLLCLK_Div2: PLL clock divided by 2 selected.
  *            @arg RCC_MCOSource_PLLCLK: PLL clock selected.
  *            @arg RCC_MCOSource_HSI48: HSI48 clock selected.
  * @param  RCC_MCOPrescaler: specifies the prescaler on MCO pin.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOPrescaler_1: MCO clock is divided by 1.
  *            @arg RCC_MCOPrescaler_2: MCO clock is divided by 2.
  *            @arg RCC_MCOPrescaler_4: MCO clock is divided by 4.
  *            @arg RCC_MCOPrescaler_8: MCO clock is divided by 8.
  *            @arg RCC_MCOPrescaler_16: MCO clock is divided by 16.
  *            @arg RCC_MCOPrescaler_32: MCO clock is divided by 32.
  *            @arg RCC_MCOPrescaler_64: MCO clock is divided by 64.
  *            @arg RCC_MCOPrescaler_128: MCO clock is divided by 128.    
  * @retval None
  */
void RCC_MCOConfig(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));
  assert_param(IS_RCC_MCO_PRESCALER(RCC_MCOPrescaler));
    
  /* Get CFGR value */  
  tmpreg = RCC->CFGR;
  /* Clear MCOPRE[2:0] bits */
  tmpreg &= ~(RCC_CFGR_MCO_PRE | RCC_CFGR_MCO | RCC_CFGR_PLLNODIV);
  /* Set the RCC_MCOSource and RCC_MCOPrescaler */
  tmpreg |= (RCC_MCOPrescaler | RCC_MCOSource<<24);
  /* Store the new value */
  RCC->CFGR = tmpreg;
}
#endif /* STM32F303xC */

/**
  * @}
  */

/** @defgroup RCC_Group2 System AHB, APB1 and APB2 busses clocks configuration functions
 *  @brief   System, AHB and APB busses clocks configuration functions
 *
@verbatim   
 ===============================================================================
  ##### System, AHB, APB1 and APB2 busses clocks configuration functions #####
 ===============================================================================  
    [..] This section provide functions allowing to configure the System, AHB, APB1 and 
         APB2 busses clocks.
         (#) Several clock sources can be used to drive the System clock (SYSCLK): HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System clock through configurable prescaler
             and used to clock the CPU, memory and peripherals mapped on AHB bus (DMA and GPIO).
             APB1 (PCLK1) and APB2 (PCLK2) clocks are derived from AHB clock through 
             configurable prescalers and used to clock the peripherals mapped on these busses.
             You can use "RCC_GetClocksFreq()" function to retrieve the frequencies of these clocks.

         (#) The maximum frequency of the SYSCLK, HCLK, PCLK1 and PCLK2 is 72 MHz.
             Depending on the maximum frequency, the FLASH wait states (WS) should be 
             adapted accordingly:
        +---------------------------------+
        |  Wait states  |   HCLK clock    |
        |   (Latency)   | frequency (MHz) |
        |-------------- |-----------------|             
        |0WS(1CPU cycle)| 0 < HCLK <= 24  |
        |---------------|-----------------| 
        |1WS(2CPU cycle)|24 < HCLK <=48   |
        |---------------|-----------------| 
        |2WS(3CPU cycle)|48 < HCLK <= 72  |
        +---------------------------------+

         (#) After reset, the System clock source is the HSI (8 MHz) with 0 WS and 
             prefetch is disabled.
        [..]
         (@) All the peripheral clocks are derived from the System clock (SYSCLK) 
             except:
             (+@) The FLASH program/erase clock  which is always HSI 8MHz clock.
             (+@) The USB 48 MHz clock which is derived from the PLL VCO clock.
             (+@) The USART clock which can be derived as well from HSI 8MHz, LSI or LSE.
             (+@) The I2C clock which can be derived as well from HSI 8MHz clock.
             (+@) The ADC clock which is derived from PLL output.
             (+@) The RTC clock which is derived from the LSE, LSI or 1 MHz HSE_RTC 
                  (HSE divided by a programmable prescaler). The System clock (SYSCLK) 
                  frequency must be higher or equal to the RTC clock frequency.
             (+@) IWDG clock which is always the LSI clock.
    [..] It is recommended to use the following software sequences to tune the number
         of wait states needed to access the Flash memory with the CPU frequency (HCLK).
         (+) Increasing the CPU frequency
            (++) Program the Flash Prefetch buffer, using "FLASH_PrefetchBufferCmd(ENABLE)" 
                 function
            (++) Check that Flash Prefetch buffer activation is taken into account by 
                 reading FLASH_ACR using the FLASH_GetPrefetchBufferStatus() function
            (++) Program Flash WS to 1 or 2, using "FLASH_SetLatency()" function
            (++) Check that the new number of WS is taken into account by reading FLASH_ACR
            (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
            (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
            (++) Check that the new CPU clock source is taken into account by reading 
                 the clock source status, using "RCC_GetSYSCLKSource()" function 
         (+) Decreasing the CPU frequency
            (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
            (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
            (++) Check that the new CPU clock source is taken into account by reading 
                 the clock source status, using "RCC_GetSYSCLKSource()" function
            (++) Program the new number of WS, using "FLASH_SetLatency()" function
            (++) Check that the new number of WS is taken into account by reading FLASH_ACR
            (++) Disable the Flash Prefetch buffer using "FLASH_PrefetchBufferCmd(DISABLE)" 
                 function
            (++) Check that Flash Prefetch buffer deactivation is taken into account by reading FLASH_ACR
                 using the FLASH_GetPrefetchBufferStatus() function.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the system clock (SYSCLK).
  * @note     The HSI is used (enabled by hardware) as system clock source after
  *           startup from Reset, wake-up from STOP and STANDBY mode, or in case
  *           of failure of the HSE used directly or indirectly as system clock
  *           (if the Clock Security System CSS is enabled).
  * @note     A switch from one clock source to another occurs only if the target
  *           clock source is ready (clock stable after startup delay or PLL locked). 
  *           If a clock source which is not yet ready is selected, the switch will
  *           occur when the clock source will be ready. 
  *           You can use RCC_GetSYSCLKSource() function to know which clock is
  *           currently used as system clock source.  
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock source 
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLKSource_HSI:    HSI selected as system clock source
  *     @arg RCC_SYSCLKSource_HSE:    HSE selected as system clock source
  *     @arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
  * @retval None
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
  
  tmpreg = RCC->CFGR;
  
  /* Clear SW[1:0] bits */
  tmpreg &= ~RCC_CFGR_SW;
  
  /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
  tmpreg |= RCC_SYSCLKSource;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval The clock source used as system clock. The returned value can be one 
  *         of the following values:
  *              - 0x00: HSI used as system clock
  *              - 0x04: HSE used as system clock  
  *              - 0x08: PLL used as system clock
  */
uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR & RCC_CFGR_SWS));
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @note   Depending on the device voltage range, the software has to set correctly
  *         these bits to ensure that the system frequency does not exceed the
  *         maximum allowed frequency (for more details refer to section above
  *         "CPU, AHB and APB busses clocks configuration functions").
  * @param  RCC_SYSCLK: defines the AHB clock divider. This clock is derived from 
  *                     the system clock (SYSCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLK_Div1:   AHB clock = SYSCLK
  *     @arg RCC_SYSCLK_Div2:   AHB clock = SYSCLK/2
  *     @arg RCC_SYSCLK_Div4:   AHB clock = SYSCLK/4
  *     @arg RCC_SYSCLK_Div8:   AHB clock = SYSCLK/8
  *     @arg RCC_SYSCLK_Div16:  AHB clock = SYSCLK/16
  *     @arg RCC_SYSCLK_Div64:  AHB clock = SYSCLK/64
  *     @arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *     @arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *     @arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @retval None
  */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HCLK(RCC_SYSCLK));
  
  tmpreg = RCC->CFGR;
  
  /* Clear HPRE[3:0] bits */
  tmpreg &= ~RCC_CFGR_HPRE;
  
  /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
  tmpreg |= RCC_SYSCLK;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the Low Speed APB clock (PCLK1).
  * @param  RCC_HCLK: defines the APB1 clock divider. This clock is derived from 
  *         the AHB clock (HCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_HCLK_Div1: APB1 clock = HCLK
  *     @arg RCC_HCLK_Div2: APB1 clock = HCLK/2
  *     @arg RCC_HCLK_Div4: APB1 clock = HCLK/4
  *     @arg RCC_HCLK_Div8: APB1 clock = HCLK/8
  *     @arg RCC_HCLK_Div16: APB1 clock = HCLK/16
  * @retval None
  */
void RCC_PCLK1Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  
  tmpreg = RCC->CFGR;
  /* Clear PPRE1[2:0] bits */
  tmpreg &= ~RCC_CFGR_PPRE1;
  
  /* Set PPRE1[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK;
  
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the High Speed APB clock (PCLK2).
  * @param  RCC_HCLK: defines the APB2 clock divider. This clock is derived from 
  *         the AHB clock (HCLK).
  *         This parameter can be one of the following values:
  *             @arg RCC_HCLK_Div1: APB2 clock = HCLK
  *             @arg RCC_HCLK_Div2: APB2 clock = HCLK/2
  *             @arg RCC_HCLK_Div4: APB2 clock = HCLK/4
  *             @arg RCC_HCLK_Div8: APB2 clock = HCLK/8
  *             @arg RCC_HCLK_Div16: APB2 clock = HCLK/16
  * @retval None
  */
void RCC_PCLK2Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  
  tmpreg = RCC->CFGR;
  /* Clear PPRE2[2:0] bits */
  tmpreg &= ~RCC_CFGR_PPRE2;
  /* Set PPRE2[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK << 3;
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
  * @brief  Returns the frequencies of the System, AHB, APB2 and APB1 busses clocks.
  * 
  *  @note    This function returns the frequencies of :
  *           System, AHB, APB2 and APB1 busses clocks, ADC1/2/3/4 clocks, 
  *           USART1/2/3/4/5 clocks, I2C1/2 clocks and TIM1/8 Clocks.
  *                         
  * @note     The frequency returned by this function is not the real frequency
  *           in the chip. It is calculated based on the predefined constant and
  *           the source selected by RCC_SYSCLKConfig().
  *                                              
  * @note      If SYSCLK source is HSI, function returns constant HSI_VALUE(*)
  *                                              
  * @note      If SYSCLK source is HSE, function returns constant HSE_VALUE(**)
  *                          
  * @note      If SYSCLK source is PLL, function returns constant HSE_VALUE(**) 
  *             or HSI_VALUE(*) multiplied by the PLL factors.
  *         
  * @note     (*) HSI_VALUE is a constant defined in stm32f30x.h file (default value
  *               8 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature, refer to RCC_AdjustHSICalibrationValue().   
  *    
  * @note     (**) HSE_VALUE is a constant defined in stm32f30x.h file (default value
  *                8 MHz), user has to ensure that HSE_VALUE is same as the real
  *                frequency of the crystal used. Otherwise, this function may
  *                return wrong result.
  *                
  * @note     The result of this function could be not correct when using fractional
  *           value for HSE crystal.   
  *             
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold 
  *         the clocks frequencies. 
  *     
  * @note     This function can be used by the user application to compute the 
  *           baudrate for the communication peripherals or configure other parameters.
  * @note     Each time SYSCLK, HCLK, PCLK1 and/or PCLK2 clock changes, this function
  *           must be called to update the structure's field. Otherwise, any
  *           configuration based on this function will be incorrect.
  *    
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0, presc = 0, pllclk = 0;
  uint32_t apb2presc = 0, ahbpresc = 0;
  
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        pllclk = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
        /* HSE oscillator clock selected as PREDIV1 clock entry */
        pllclk = (HSE_VALUE / prediv1factor) * pllmull; 
      }
      RCC_Clocks->SYSCLK_Frequency = pllclk;      
      break;
    default: /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
  }
    /* Compute HCLK, PCLK clocks frequencies -----------------------------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & RCC_CFGR_HPRE;
  tmp = tmp >> 4;
  ahbpresc = APBAHBPrescTable[tmp]; 
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> ahbpresc;

  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & RCC_CFGR_PPRE1;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  
  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & RCC_CFGR_PPRE2;
  tmp = tmp >> 11;
  apb2presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> apb2presc;
  
  /* Get ADC12CLK prescaler */
  tmp = RCC->CFGR2 & RCC_CFGR2_ADCPRE12;
  tmp = tmp >> 4;
  presc = ADCPrescTable[tmp & 0x0F];
  if (((tmp & 0x10) != 0) && (presc != 0))
  {
     /* ADC12CLK clock frequency is derived from PLL clock */
     RCC_Clocks->ADC12CLK_Frequency = pllclk / presc;
  }
  else
  {
   /* ADC12CLK clock frequency is AHB clock */
     RCC_Clocks->ADC12CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  
  /* Get ADC34CLK prescaler */
  tmp = RCC->CFGR2 & RCC_CFGR2_ADCPRE34;
  tmp = tmp >> 9;
  presc = ADCPrescTable[tmp & 0x0F];
  if (((tmp & 0x10) != 0) && (presc != 0))
  {
     /* ADC34CLK clock frequency is derived from PLL clock */
     RCC_Clocks->ADC34CLK_Frequency = pllclk / presc;
  }
  else
  {
   /* ADC34CLK clock frequency is AHB clock */
     RCC_Clocks->ADC34CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }

  /* I2C1CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_I2C1SW) != RCC_CFGR3_I2C1SW)
  {
    /* I2C1 Clock is HSI Osc. */
    RCC_Clocks->I2C1CLK_Frequency = HSI_VALUE;
  }
  else
  {
    /* I2C1 Clock is System Clock */
    RCC_Clocks->I2C1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }

  /* I2C2CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_I2C2SW) != RCC_CFGR3_I2C2SW)
  {
    /* I2C2 Clock is HSI Osc. */
    RCC_Clocks->I2C2CLK_Frequency = HSI_VALUE;
  }
  else
  {
    /* I2C2 Clock is System Clock */
    RCC_Clocks->I2C2CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }

  /* I2C3CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_I2C3SW) != RCC_CFGR3_I2C3SW)
  {
    /* I2C3 Clock is HSI Osc. */
    RCC_Clocks->I2C3CLK_Frequency = HSI_VALUE;
  }
  else
  {
    /* I2C3 Clock is System Clock */
    RCC_Clocks->I2C3CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
    
    /* TIM1CLK clock frequency */
  if(((RCC->CFGR3 & RCC_CFGR3_TIM1SW) == RCC_CFGR3_TIM1SW)&& (RCC_Clocks->SYSCLK_Frequency == pllclk) \
  && (apb2presc == ahbpresc)) 
  {
    /* TIM1 Clock is 2 * pllclk */
    RCC_Clocks->TIM1CLK_Frequency = pllclk * 2;
  }
  else
  {
    /* TIM1 Clock is APB2 clock. */
    RCC_Clocks->TIM1CLK_Frequency = RCC_Clocks->PCLK2_Frequency;
  }

    /* TIM1CLK clock frequency */
  if(((RCC->CFGR3 & RCC_CFGR3_HRTIM1SW) == RCC_CFGR3_HRTIM1SW)&& (RCC_Clocks->SYSCLK_Frequency == pllclk) \
  && (apb2presc == ahbpresc)) 
  {
    /* HRTIM1 Clock is 2 * pllclk */
    RCC_Clocks->HRTIM1CLK_Frequency = pllclk * 2;
  }
  else
  {
    /* HRTIM1 Clock is APB2 clock. */
    RCC_Clocks->HRTIM1CLK_Frequency = RCC_Clocks->PCLK2_Frequency;
  }
  
    /* TIM8CLK clock frequency */
  if(((RCC->CFGR3 & RCC_CFGR3_TIM8SW) == RCC_CFGR3_TIM8SW)&& (RCC_Clocks->SYSCLK_Frequency == pllclk) \
  && (apb2presc == ahbpresc))
  {
    /* TIM8 Clock is 2 * pllclk */
    RCC_Clocks->TIM8CLK_Frequency = pllclk * 2;
  }
  else
  {
    /* TIM8 Clock is APB2 clock. */
    RCC_Clocks->TIM8CLK_Frequency = RCC_Clocks->PCLK2_Frequency;
  }

    /* TIM15CLK clock frequency */
  if(((RCC->CFGR3 & RCC_CFGR3_TIM15SW) == RCC_CFGR3_TIM15SW)&& (RCC_Clocks->SYSCLK_Frequency == pllclk) \
  && (apb2presc == ahbpresc))
  {
    /* TIM15 Clock is 2 * pllclk */
    RCC_Clocks->TIM15CLK_Frequency = pllclk * 2;
  }
  else
  {
    /* TIM15 Clock is APB2 clock. */
    RCC_Clocks->TIM15CLK_Frequency = RCC_Clocks->PCLK2_Frequency;
  }
    
    /* TIM16CLK clock frequency */
  if(((RCC->CFGR3 & RCC_CFGR3_TIM16SW) == RCC_CFGR3_TIM16SW)&& (RCC_Clocks->SYSCLK_Frequency == pllclk) \
  && (apb2presc == ahbpresc))
  {
    /* TIM16 Clock is 2 * pllclk */
    RCC_Clocks->TIM16CLK_Frequency = pllclk * 2;
  }
  else
  {
    /* TIM16 Clock is APB2 clock. */
    RCC_Clocks->TIM16CLK_Frequency = RCC_Clocks->PCLK2_Frequency;
  }

    /* TIM17CLK clock frequency */
  if(((RCC->CFGR3 & RCC_CFGR3_TIM17SW) == RCC_CFGR3_TIM17SW)&& (RCC_Clocks->SYSCLK_Frequency == pllclk) \
  && (apb2presc == ahbpresc))
  {
    /* TIM17 Clock is 2 * pllclk */
    RCC_Clocks->TIM17CLK_Frequency = pllclk * 2;
  }
  else
  {
    /* TIM17 Clock is APB2 clock. */
    RCC_Clocks->TIM16CLK_Frequency = RCC_Clocks->PCLK2_Frequency;
  }
    
  /* USART1CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == 0x0)
  {
#if defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F301x8) || defined(STM32F302x8)
    /* USART1 Clock is PCLK1 instead of PCLK2 (limitation described in the 
       STM32F302/01/34 x4/x6/x8 respective erratasheets) */
    RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->PCLK1_Frequency;
#else
    /* USART Clock is PCLK2 */
    RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->PCLK2_Frequency;
#endif  
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW_0)
  {
    /* USART Clock is System Clock */
    RCC_Clocks->USART1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW_1)
  {
    /* USART Clock is LSE Osc. */
    RCC_Clocks->USART1CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == RCC_CFGR3_USART1SW)
  {
    /* USART Clock is HSI Osc. */
    RCC_Clocks->USART1CLK_Frequency = HSI_VALUE;
  }

  /* USART2CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_USART2SW) == 0x0)
  {
    /* USART Clock is PCLK */
    RCC_Clocks->USART2CLK_Frequency = RCC_Clocks->PCLK1_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART2SW) == RCC_CFGR3_USART2SW_0)
  {
    /* USART Clock is System Clock */
    RCC_Clocks->USART2CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART2SW) == RCC_CFGR3_USART2SW_1)
  {
    /* USART Clock is LSE Osc. */
    RCC_Clocks->USART2CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART2SW) == RCC_CFGR3_USART2SW)
  {
    /* USART Clock is HSI Osc. */
    RCC_Clocks->USART2CLK_Frequency = HSI_VALUE;
  }    

  /* USART3CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_USART3SW) == 0x0)
  {
    /* USART Clock is PCLK */
    RCC_Clocks->USART3CLK_Frequency = RCC_Clocks->PCLK1_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART3SW) == RCC_CFGR3_USART3SW_0)
  {
    /* USART Clock is System Clock */
    RCC_Clocks->USART3CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART3SW) == RCC_CFGR3_USART3SW_1)
  {
    /* USART Clock is LSE Osc. */
    RCC_Clocks->USART3CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_USART3SW) == RCC_CFGR3_USART3SW)
  {
    /* USART Clock is HSI Osc. */
    RCC_Clocks->USART3CLK_Frequency = HSI_VALUE;
  }
  
    /* UART4CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_UART4SW) == 0x0)
  {
    /* USART Clock is PCLK */
    RCC_Clocks->UART4CLK_Frequency = RCC_Clocks->PCLK1_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_UART4SW) == RCC_CFGR3_UART4SW_0)
  {
    /* USART Clock is System Clock */
    RCC_Clocks->UART4CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_UART4SW) == RCC_CFGR3_UART4SW_1)
  {
    /* USART Clock is LSE Osc. */
    RCC_Clocks->UART4CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_UART4SW) == RCC_CFGR3_UART4SW)
  {
    /* USART Clock is HSI Osc. */
    RCC_Clocks->UART4CLK_Frequency = HSI_VALUE;
  }   
  
  /* UART5CLK clock frequency */
  if((RCC->CFGR3 & RCC_CFGR3_UART5SW) == 0x0)
  {
    /* USART Clock is PCLK */
    RCC_Clocks->UART5CLK_Frequency = RCC_Clocks->PCLK1_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_UART5SW) == RCC_CFGR3_UART5SW_0)
  {
    /* USART Clock is System Clock */
    RCC_Clocks->UART5CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_UART5SW) == RCC_CFGR3_UART5SW_1)
  {
    /* USART Clock is LSE Osc. */
    RCC_Clocks->UART5CLK_Frequency = LSE_VALUE;
  }
  else if((RCC->CFGR3 & RCC_CFGR3_UART5SW) == RCC_CFGR3_UART5SW)
  {
    /* USART Clock is HSI Osc. */
    RCC_Clocks->UART5CLK_Frequency = HSI_VALUE;
  } 
}

/**
  * @}
  */

/** @defgroup RCC_Group3 Peripheral clocks configuration functions
 *  @brief   Peripheral clocks configuration functions 
 *
@verbatim   
 ===============================================================================
            ##### Peripheral clocks configuration functions #####
 ===============================================================================  
    [..] This section provide functions allowing to configure the Peripheral clocks. 
         (#) The RTC clock which is derived from the LSE, LSI or  HSE_Div32 
             (HSE divided by 32).
         (#) After restart from Reset or wakeup from STANDBY, all peripherals are 
             off except internal SRAM, Flash and SWD. Before to start using 
             a peripheral you have to enable its interface clock. You can do this 
             using RCC_AHBPeriphClockCmd(), RCC_APB2PeriphClockCmd() 
             and RCC_APB1PeriphClockCmd() functions.
         (#) To reset the peripherals configuration (to the default state after 
             device reset) you can use RCC_AHBPeriphResetCmd(), RCC_APB2PeriphResetCmd() 
             and RCC_APB1PeriphResetCmd() functions.
@endverbatim
  * @{
  */

/**
  * @brief  Configures the ADC clock (ADCCLK).
  * @param  RCC_PLLCLK: defines the ADC clock divider. This clock is derived from 
  *         the PLL Clock.
  *   This parameter can be one of the following values:
  *     @arg RCC_ADC12PLLCLK_OFF: ADC12 clock disabled
  *     @arg RCC_ADC12PLLCLK_Div1: ADC12 clock = PLLCLK/1
  *     @arg RCC_ADC12PLLCLK_Div2: ADC12 clock = PLLCLK/2
  *     @arg RCC_ADC12PLLCLK_Div4: ADC12 clock = PLLCLK/4
  *     @arg RCC_ADC12PLLCLK_Div6: ADC12 clock = PLLCLK/6
  *     @arg RCC_ADC12PLLCLK_Div8: ADC12 clock = PLLCLK/8
  *     @arg RCC_ADC12PLLCLK_Div10: ADC12 clock = PLLCLK/10
  *     @arg RCC_ADC12PLLCLK_Div12: ADC12 clock = PLLCLK/12
  *     @arg RCC_ADC12PLLCLK_Div16: ADC12 clock = PLLCLK/16
  *     @arg RCC_ADC12PLLCLK_Div32: ADC12 clock = PLLCLK/32
  *     @arg RCC_ADC12PLLCLK_Div64: ADC12 clock = PLLCLK/64
  *     @arg RCC_ADC12PLLCLK_Div128: ADC12 clock = PLLCLK/128
  *     @arg RCC_ADC12PLLCLK_Div256: ADC12 clock = PLLCLK/256
  *     @arg RCC_ADC34PLLCLK_OFF: ADC34 clock disabled
  *     @arg RCC_ADC34PLLCLK_Div1: ADC34 clock = PLLCLK/1
  *     @arg RCC_ADC34PLLCLK_Div2: ADC34 clock = PLLCLK/2
  *     @arg RCC_ADC34PLLCLK_Div4: ADC34 clock = PLLCLK/4
  *     @arg RCC_ADC34PLLCLK_Div6: ADC34 clock = PLLCLK/6
  *     @arg RCC_ADC34PLLCLK_Div8: ADC34 clock = PLLCLK/8
  *     @arg RCC_ADC34PLLCLK_Div10: ADC34 clock = PLLCLK/10
  *     @arg RCC_ADC34PLLCLK_Div12: ADC34 clock = PLLCLK/12
  *     @arg RCC_ADC34PLLCLK_Div16: ADC34 clock = PLLCLK/16
  *     @arg RCC_ADC34PLLCLK_Div32: ADC34 clock = PLLCLK/32
  *     @arg RCC_ADC34PLLCLK_Div64: ADC34 clock = PLLCLK/64       
  *     @arg RCC_ADC34PLLCLK_Div128: ADC34 clock = PLLCLK/128                                  
  *     @arg RCC_ADC34PLLCLK_Div256: ADC34 clock = PLLCLK/256
  * @retval None
  */
void RCC_ADCCLKConfig(uint32_t RCC_PLLCLK)
{
  uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_ADCCLK(RCC_PLLCLK));

  tmp = (RCC_PLLCLK >> 28);
  
  /* Clears ADCPRE34 bits */
  if (tmp != 0)
  {
    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE34;
  }
   /* Clears ADCPRE12 bits */
  else
  {
    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12;
  }
  /* Set ADCPRE bits according to RCC_PLLCLK value */
  RCC->CFGR2 |= RCC_PLLCLK;
}

/**
  * @brief  Configures the I2C clock (I2CCLK).
  * @param  RCC_I2CCLK: defines the I2C clock source. This clock is derived 
  *         from the HSI or System clock.
  *   This parameter can be one of the following values:
  *     @arg RCC_I2CxCLK_HSI: I2Cx clock = HSI
  *     @arg RCC_I2CxCLK_SYSCLK: I2Cx clock = System Clock
  *          (x can be 1 or 2 or 3).  
  * @retval None
  */
void RCC_I2CCLKConfig(uint32_t RCC_I2CCLK)
{ 
  uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_I2CCLK(RCC_I2CCLK));

  tmp = (RCC_I2CCLK >> 28);
  
  /* Clear I2CSW bit */
    switch (tmp)
  {
    case 0x00: 
      RCC->CFGR3 &= ~RCC_CFGR3_I2C1SW;
      break;
    case 0x01:
      RCC->CFGR3 &= ~RCC_CFGR3_I2C2SW;
      break;
    case 0x02:
      RCC->CFGR3 &= ~RCC_CFGR3_I2C3SW;
      break;
    default:
      break;
  }
  
  /* Set I2CSW bits according to RCC_I2CCLK value */
  RCC->CFGR3 |= RCC_I2CCLK;
}

/**
  * @brief  Configures the TIMx clock sources(TIMCLK).
  * @note     The configuration of the TIMx clock source is only possible when the 
  *           SYSCLK = PLL and HCLK and PCLK2 clocks are not divided in respect to SYSCLK
  * @note     If one of the previous conditions is missed, the TIM clock source 
  *           configuration is lost and calling again this function becomes mandatory.  
  * @param  RCC_TIMCLK: defines the TIMx clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_TIMxCLK_HCLK: TIMx clock = APB high speed clock (doubled frequency
  *          when prescaled)
  *     @arg RCC_TIMxCLK_PLLCLK: TIMx clock = PLL output (running up to 144 MHz)
  *          (x can be 1, 8, 15, 16, 17).
  * @retval None
  */
void RCC_TIMCLKConfig(uint32_t RCC_TIMCLK)
{ 
  uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_TIMCLK(RCC_TIMCLK));

  tmp = (RCC_TIMCLK >> 28);
  
  /* Clear TIMSW bit */
  
  switch (tmp)
  {
    case 0x00: 
      RCC->CFGR3 &= ~RCC_CFGR3_TIM1SW;
      break;
    case 0x01:
      RCC->CFGR3 &= ~RCC_CFGR3_TIM8SW;
      break;
    case 0x02:
      RCC->CFGR3 &= ~RCC_CFGR3_TIM15SW;
      break;
    case 0x03:
      RCC->CFGR3 &= ~RCC_CFGR3_TIM16SW;
      break;
    case 0x04:
      RCC->CFGR3 &= ~RCC_CFGR3_TIM17SW;
      break;
    default:
      break;
  }
  
  /* Set I2CSW bits according to RCC_TIMCLK value */
  RCC->CFGR3 |= RCC_TIMCLK;
}

/**
  * @brief  Configures the HRTIM1 clock sources(HRTIM1CLK).
  * @note     The configuration of the HRTIM1 clock source is only possible when the 
  *           SYSCLK = PLL and HCLK and PCLK2 clocks are not divided in respect to SYSCLK
  * @note     If one of the previous conditions is missed, the TIM clock source 
  *           configuration is lost and calling again this function becomes mandatory.  
  * @param  RCC_HRTIMCLK: defines the TIMx clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_HRTIM1CLK_HCLK: TIMx clock = APB high speed clock (doubled frequency
  *          when prescaled)
  *     @arg RCC_HRTIM1CLK_PLLCLK: TIMx clock = PLL output (running up to 144 MHz)
  *          (x can be 1 or 8).
  * @retval None
  */
void RCC_HRTIM1CLKConfig(uint32_t RCC_HRTIMCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_HRTIMCLK(RCC_HRTIMCLK));
  
  /* Clear HRTIMSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_HRTIM1SW;

  /* Set HRTIMSW bits according to RCC_HRTIMCLK value */
  RCC->CFGR3 |= RCC_HRTIMCLK;
}

/**
  * @brief  Configures the USART clock (USARTCLK).
  * @param  RCC_USARTCLK: defines the USART clock source. This clock is derived 
  *         from the HSI or System clock.
  *   This parameter can be one of the following values:
  *     @arg RCC_USARTxCLK_PCLK: USART clock = APB Clock (PCLK)
  *     @arg RCC_USARTxCLK_SYSCLK: USART clock = System Clock
  *     @arg RCC_USARTxCLK_LSE: USART clock = LSE Clock
  *     @arg RCC_USARTxCLK_HSI: USART clock = HSI Clock
  *          (x can be 1, 2, 3, 4 or 5).  
  * @retval None
  */
void RCC_USARTCLKConfig(uint32_t RCC_USARTCLK)
{ 
  uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_USARTCLK(RCC_USARTCLK));

  tmp = (RCC_USARTCLK >> 28);

  /* Clear USARTSW[1:0] bit */
  switch (tmp)
  {
    case 0x01:  /* clear USART1SW */
      RCC->CFGR3 &= ~RCC_CFGR3_USART1SW;
      break;
    case 0x02:  /* clear USART2SW */
      RCC->CFGR3 &= ~RCC_CFGR3_USART2SW;
      break;
    case 0x03:  /* clear USART3SW */
      RCC->CFGR3 &= ~RCC_CFGR3_USART3SW;
      break;
    case 0x04:  /* clear UART4SW */
      RCC->CFGR3 &= ~RCC_CFGR3_UART4SW;
      break;
    case 0x05:  /* clear UART5SW */
      RCC->CFGR3 &= ~RCC_CFGR3_UART5SW;
      break;
    default:
      break;
  }

  /* Set USARTSW bits according to RCC_USARTCLK value */
  RCC->CFGR3 |= RCC_USARTCLK;
}

/**
  * @brief  Configures the USB clock (USBCLK).
  * @param  RCC_USBCLKSource: specifies the USB clock source. This clock is 
  *   derived from the PLL output.
  *   This parameter can be one of the following values:
  *     @arg RCC_USBCLKSource_PLLCLK_1Div5: PLL clock divided by 1,5 selected as USB 
  *                                     clock source
  *     @arg RCC_USBCLKSource_PLLCLK_Div1: PLL clock selected as USB clock source
  * @retval None
  */
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_USBCLK_SOURCE(RCC_USBCLKSource));

  *(__IO uint32_t *) CFGR_USBPRE_BB = RCC_USBCLKSource;
}

/**
  * @brief  Configures the RTC clock (RTCCLK).
  * @note     As the RTC clock configuration bits are in the Backup domain and write
  *           access is denied to this domain after reset, you have to enable write
  *           access using PWR_BackupAccessCmd(ENABLE) function before to configure
  *           the RTC clock source (to be done once after reset).    
  * @note     Once the RTC clock is configured it can't be changed unless the RTC
  *           is reset using RCC_BackupResetCmd function, or by a Power On Reset (POR)
  *             
  * @param  RCC_RTCCLKSource: specifies the RTC clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_RTCCLKSource_LSE: LSE selected as RTC clock
  *     @arg RCC_RTCCLKSource_LSI: LSI selected as RTC clock
  *     @arg RCC_RTCCLKSource_HSE_Div32: HSE divided by 32 selected as RTC clock
  *       
  * @note     If the LSE or LSI is used as RTC clock source, the RTC continues to
  *           work in STOP and STANDBY modes, and can be used as wakeup source.
  *           However, when the HSE clock is used as RTC clock source, the RTC
  *           cannot be used in STOP and STANDBY modes.             
  * @note     The maximum input clock frequency for RTC is 2MHz (when using HSE as
  *           RTC clock source).             
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));
  
  /* Select the RTC clock source */
  RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @brief  Configures the I2S clock source (I2SCLK).
  * @note   This function must be called before enabling the SPI2 and SPI3 clocks.
  * @param  RCC_I2SCLKSource: specifies the I2S clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_I2S2CLKSource_SYSCLK: SYSCLK clock used as I2S clock source
  *            @arg RCC_I2S2CLKSource_Ext: External clock mapped on the I2S_CKIN pin
  *                                        used as I2S clock source
  * @retval None
  */
void RCC_I2SCLKConfig(uint32_t RCC_I2SCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_I2SCLK_SOURCE(RCC_I2SCLKSource));

  *(__IO uint32_t *) CFGR_I2SSRC_BB = RCC_I2SCLKSource;
}

/**
  * @brief  Enables or disables the RTC clock.
  * @note   This function must be used only after the RTC clock source was selected
  *         using the RCC_RTCCLKConfig function.
  * @param  NewState: new state of the RTC clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(__IO uint32_t *) BDCR_RTCEN_BB = (uint32_t)NewState;
}

/**
  * @brief  Forces or releases the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_BDCR register.
  * @param  NewState: new state of the Backup domain reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(__IO uint32_t *) BDCR_BDRST_BB = (uint32_t)NewState;
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.    
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_AHBPeriph_GPIOA
  *     @arg RCC_AHBPeriph_GPIOB
  *     @arg RCC_AHBPeriph_GPIOC  
  *     @arg RCC_AHBPeriph_GPIOD
  *     @arg RCC_AHBPeriph_GPIOE  
  *     @arg RCC_AHBPeriph_GPIOF
  *     @arg RCC_AHBPeriph_TS
  *     @arg RCC_AHBPeriph_CRC
  *     @arg RCC_AHBPeriph_FLITF (has effect only when the Flash memory is in power down mode)  
  *     @arg RCC_AHBPeriph_SRAM
  *     @arg RCC_AHBPeriph_DMA2
  *     @arg RCC_AHBPeriph_DMA1
  *     @arg RCC_AHBPeriph_ADC34
  *     @arg RCC_AHBPeriph_ADC12      
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB2Periph_SYSCFG
  *     @arg RCC_APB2Periph_SPI1
  *     @arg RCC_APB2Periph_USART1
  *     @arg RCC_APB2Periph_TIM15
  *     @arg RCC_APB2Periph_TIM16
  *     @arg RCC_APB2Periph_TIM17
  *     @arg RCC_APB2Periph_TIM1       
  *     @arg RCC_APB2Periph_TIM8
  *     @arg RCC_APB2Periph_HRTIM1  
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB1Periph_TIM2
  *     @arg RCC_APB1Periph_TIM3
  *     @arg RCC_APB1Periph_TIM4
  *     @arg RCC_APB1Periph_TIM6
  *     @arg RCC_APB1Periph_TIM7
  *     @arg RCC_APB1Periph_WWDG
  *     @arg RCC_APB1Periph_SPI2
  *     @arg RCC_APB1Periph_SPI3  
  *     @arg RCC_APB1Periph_USART2
  *     @arg RCC_APB1Periph_USART3
  *     @arg RCC_APB1Periph_UART4 
  *     @arg RCC_APB1Periph_UART5     
  *     @arg RCC_APB1Periph_I2C1
  *     @arg RCC_APB1Periph_I2C2
  *     @arg RCC_APB1Periph_USB
  *     @arg RCC_APB1Periph_CAN1
  *     @arg RCC_APB1Periph_PWR
  *     @arg RCC_APB1Periph_DAC1
  *     @arg RCC_APB1Periph_DAC2  
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

/**
  * @brief  Forces or releases AHB peripheral reset.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_AHBPeriph_GPIOA
  *     @arg RCC_AHBPeriph_GPIOB
  *     @arg RCC_AHBPeriph_GPIOC  
  *     @arg RCC_AHBPeriph_GPIOD
  *     @arg RCC_AHBPeriph_GPIOE  
  *     @arg RCC_AHBPeriph_GPIOF
  *     @arg RCC_AHBPeriph_TS
  *     @arg RCC_AHBPeriph_ADC34
  *     @arg RCC_AHBPeriph_ADC12    
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_RST_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBRSTR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBRSTR &= ~RCC_AHBPeriph;
  }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB2Periph_SYSCFG
  *     @arg RCC_APB2Periph_SPI1
  *     @arg RCC_APB2Periph_USART1
  *     @arg RCC_APB2Periph_TIM15
  *     @arg RCC_APB2Periph_TIM16
  *     @arg RCC_APB2Periph_TIM17
  *     @arg RCC_APB2Periph_TIM1       
  *     @arg RCC_APB2Periph_TIM8 
  *     @arg RCC_APB2Periph_HRTIM1       
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB1Periph_TIM2
  *     @arg RCC_APB1Periph_TIM3
  *     @arg RCC_APB1Periph_TIM4
  *     @arg RCC_APB1Periph_TIM6
  *     @arg RCC_APB1Periph_TIM7
  *     @arg RCC_APB1Periph_WWDG
  *     @arg RCC_APB1Periph_SPI2
  *     @arg RCC_APB1Periph_SPI3  
  *     @arg RCC_APB1Periph_USART2
  *     @arg RCC_APB1Periph_USART3
  *     @arg RCC_APB1Periph_UART4
  *     @arg RCC_APB1Periph_UART5      
  *     @arg RCC_APB1Periph_I2C1
  *     @arg RCC_APB1Periph_I2C2
  *     @arg RCC_APB1Periph_I2C3
  *     @arg RCC_APB1Periph_USB
  *     @arg RCC_APB1Periph_CAN1
  *     @arg RCC_APB1Periph_PWR
  *     @arg RCC_APB1Periph_DAC
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
  * @}
  */

/** @defgroup RCC_Group4 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified RCC interrupts.
  * @note   The CSS interrupt doesn't have an enable bit; once the CSS is enabled
  *         and if the HSE clock fails, the CSS interrupt occurs and an NMI is
  *         automatically generated. The NMI will be executed indefinitely, and 
  *         since NMI has higher priority than any other IRQ (and main program)
  *         the application will be stacked in the NMI ISR unless the CSS interrupt
  *         pending bit is cleared.
  * @param  RCC_IT: specifies the RCC interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_IT_LSIRDY: LSI ready interrupt
  *     @arg RCC_IT_LSERDY: LSE ready interrupt
  *     @arg RCC_IT_HSIRDY: HSI ready interrupt
  *     @arg RCC_IT_HSERDY: HSE ready interrupt
  *     @arg RCC_IT_PLLRDY: PLL ready interrupt
  * @param  NewState: new state of the specified RCC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_IT(RCC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Perform Byte access to RCC_CIR[13:8] bits to enable the selected interrupts */
    *(__IO uint8_t *) CIR_BYTE2_ADDRESS |= RCC_IT;
  }
  else
  {
    /* Perform Byte access to RCC_CIR[13:8] bits to disable the selected interrupts */
    *(__IO uint8_t *) CIR_BYTE2_ADDRESS &= (uint8_t)~RCC_IT;
  }
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg RCC_FLAG_HSIRDY: HSI oscillator clock ready  
  *     @arg RCC_FLAG_HSERDY: HSE oscillator clock ready
  *     @arg RCC_FLAG_PLLRDY: PLL clock ready
  *     @arg RCC_FLAG_MCOF: MCO Flag  
  *     @arg RCC_FLAG_LSERDY: LSE oscillator clock ready
  *     @arg RCC_FLAG_LSIRDY: LSI oscillator clock ready
  *     @arg RCC_FLAG_OBLRST: Option Byte Loader (OBL) reset 
  *     @arg RCC_FLAG_PINRST: Pin reset
  *     @arg RCC_FLAG_PORRST: POR/PDR reset
  *     @arg RCC_FLAG_SFTRST: Software reset
  *     @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
  *     @arg RCC_FLAG_WWDGRST: Window Watchdog reset
  *     @arg RCC_FLAG_LPWRRST: Low Power reset
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_FLAG(RCC_FLAG));

  /* Get the RCC register index */
  tmp = RCC_FLAG >> 5;

   if (tmp == 0)               /* The flag to check is in CR register */
  {
    statusreg = RCC->CR;
  }
  else if (tmp == 1)          /* The flag to check is in BDCR register */
  {
    statusreg = RCC->BDCR;
  }
  else if (tmp == 4)          /* The flag to check is in CFGR register */
  {
    statusreg = RCC->CFGR;
  }
  else                       /* The flag to check is in CSR register */
  {
    statusreg = RCC->CSR;
  }

  /* Get the flag position */
  tmp = RCC_FLAG & FLAG_MASK;

  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clears the RCC reset flags.
  *         The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_PORRST, 
  *         RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST.
  * @param  None
  * @retval None
  */
void RCC_ClearFlag(void)
{
  /* Set RMVF bit to clear the reset flags */
  RCC->CSR |= RCC_CSR_RMVF;
}

/**
  * @brief  Checks whether the specified RCC interrupt has occurred or not.
  * @param  RCC_IT: specifies the RCC interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg RCC_IT_LSIRDY: LSI ready interrupt
  *     @arg RCC_IT_LSERDY: LSE ready interrupt
  *     @arg RCC_IT_HSIRDY: HSI ready interrupt
  *     @arg RCC_IT_HSERDY: HSE ready interrupt
  *     @arg RCC_IT_PLLRDY: PLL ready interrupt
  *     @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval The new state of RCC_IT (SET or RESET).
  */
ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_RCC_GET_IT(RCC_IT));
  
  /* Check the status of the specified RCC interrupt */
  if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the RCC_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the RCC's interrupt pending bits.
  * @param  RCC_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_IT_LSIRDY: LSI ready interrupt
  *     @arg RCC_IT_LSERDY: LSE ready interrupt
  *     @arg RCC_IT_HSIRDY: HSI ready interrupt
  *     @arg RCC_IT_HSERDY: HSE ready interrupt
  *     @arg RCC_IT_PLLRDY: PLL ready interrupt
  *     @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval None
  */
void RCC_ClearITPendingBit(uint8_t RCC_IT)
{
  /* Check the parameters */
  assert_param(IS_RCC_CLEAR_IT(RCC_IT));
  
  /* Perform Byte access to RCC_CIR[23:16] bits to clear the selected interrupt
     pending bits */
  *(__IO uint8_t *) CIR_BYTE3_ADDRESS = RCC_IT;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
