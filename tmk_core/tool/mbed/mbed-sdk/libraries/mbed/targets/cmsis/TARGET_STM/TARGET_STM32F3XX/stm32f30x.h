/**
  ******************************************************************************
  * @file    stm32f30x.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral registers definitions, bits 
  *          definitions and memory mapping for STM32F30x devices.
  *            
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE 
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral registers declarations and bits definition
  *           - Macros to access peripheral registers hardware
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f30x
  * @{
  */
    
#ifndef __STM32F30x_H
#define __STM32F30x_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
  
/** @addtogroup Library_configuration_section
  * @{
  */
  
/* Uncomment the line below according to the target STM32 device used in your
   application 
  */

#if !defined (STM32F303xC) && !defined (STM32F334x8) && !defined (STM32F303x8) && !defined (STM32F301x8) && !defined (STM32F302x8)
#define STM32F303xC   /*!< STM32F303CB, STM32F303CC, STM32F303RB, STM32F303RC, STM32F303VB and STM32F303VC Devices */
 /* #define STM32F334x8 */   /*!< STM32F334C4, STM32F334C6, STM32F334C8, STM32F334R4, STM32F334R6 and STM32F334R8 Devices */
 /* #define STM32F302x8 */         /*!< STM32F302K4, STM32F302K6, STM32F302K8, STM32F302C4, STM32F302C6, STM32F302C8, 
                                   STM32F302R4, STM32F302R6 and STM32F302R8 Devices */
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */

/* Old STM32F30X definition, maintained for legacy purpose */
#if defined(STM32F30X) 
  #define STM32F303xC
#endif /* STM32F30X */

#if !defined (STM32F303xC) && !defined (STM32F334x8) && !defined (STM32F302x8)
 #error "Please select first the target STM32F30X device used in your application (in stm32f30x.h file)"
#endif

#if !defined  (USE_STDPERIPH_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will 
   be based on direct access to peripherals registers 
   */
#define USE_STDPERIPH_DRIVER
#endif /* USE_STDPERIPH_DRIVER */

/**
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application 
   
   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */           
#if !defined  (HSE_VALUE) 
 #define HSE_VALUE  ((uint32_t)8000000) /*!< Value of the External xtal in Hz */
#endif /* HSE_VALUE */

/**
 * @brief In the following line adjust the External High Speed oscillator (HSE) Startup 
   Timeout value 
   */
#if !defined  (HSE_STARTUP_TIMEOUT) 
 #define HSE_STARTUP_TIMEOUT  ((uint16_t)0x5000)   /*!< Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup 
   Timeout value 
   */
#if !defined  (HSI_STARTUP_TIMEOUT) 
 #define HSI_STARTUP_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HSI start up */
#endif /* HSI_STARTUP_TIMEOUT */  

#if !defined  (HSI_VALUE) 
 #define HSI_VALUE  ((uint32_t)8000000)
#endif /* HSI_VALUE */                      /*!< Value of the Internal High Speed oscillator in Hz.
                                            The real value may vary depending on the variations
                                             in voltage and temperature.  */
#if !defined  (LSI_VALUE) 
 #define LSI_VALUE  ((uint32_t)40000)    
#endif /* LSI_VALUE */                      /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#if !defined  (LSE_VALUE)
 #define LSE_VALUE  ((uint32_t)32768)    /*!< Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */     


/**
 * @brief STM32F30x Standard Peripherals Library version number V1.1.0
   */
#define __STM32F30X_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */                                  
#define __STM32F30X_STDPERIPH_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __STM32F30X_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32F30X_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F30X_STDPERIPH_VERSION       ( (__STM32F30X_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__STM32F30X_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__STM32F30X_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__STM32F30X_STDPERIPH_VERSION_RC))
                                             
/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
 * @brief Configuration of the Cortex-M4 Processor and Core Peripherals 
 */
#define __CM4_REV                 0x0001  /*!< Core revision r0p1                            */
#define __MPU_PRESENT             1         /*!< STM32F30X provide an MPU */
#define __NVIC_PRIO_BITS          4         /*!< STM32F30X uses 4 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1         /*!< STM32F30X provide an FPU */


/**
 * @brief STM32F30X Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */
typedef enum IRQn
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
#ifdef STM32F303xC 
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMPER_STAMP_IRQn           = 2,      /*!< Tamper and TimeStamp interrupts                                   */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI lines 17, 19 & 20           */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_TS_IRQn               = 8,      /*!< EXTI Line2 Interrupt and Touch Sense Interrupt                    */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 Interrupt                                          */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 Interrupt                                          */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 Interrupt                                          */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 Interrupt                                          */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 Interrupt                                          */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 Interrupt                                          */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 Interrupt                                          */
  ADC1_2_IRQn                 = 18,     /*!< ADC1 & ADC2 Interrupts                                            */
  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts                    */
  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts                    */  
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM15_IRQn         = 24,     /*!< TIM1 Break and TIM15 Interrupts                                   */
  TIM1_UP_TIM16_IRQn          = 25,     /*!< TIM1 Update and TIM16 Interrupts                                  */
  TIM1_TRG_COM_TIM17_IRQn     = 26,     /*!< TIM1 Trigger and Commutation and TIM17 Interrupt                  */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */ 
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */  
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */  
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  USBWakeUp_IRQn              = 42,     /*!< USB Wakeup Interrupt                                              */
  TIM8_BRK_IRQn               = 43,     /*!< TIM8 Break Interrupt                                              */
  TIM8_UP_IRQn                = 44,     /*!< TIM8 Update Interrupt                                             */
  TIM8_TRG_COM_IRQn           = 45,     /*!< TIM8 Trigger and Commutation Interrupt                            */
  TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare Interrupt                                    */
  ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                             */
  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
  UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
  TIM6_DAC_IRQn               = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
  TIM7_IRQn                   = 55,     /*!< TIM7 global Interrupt                                             */
  DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                                   */
  DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                                   */
  DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                                   */
  DMA2_Channel4_IRQn          = 59,     /*!< DMA2 Channel 4 global Interrupt                                   */
  DMA2_Channel5_IRQn          = 60,     /*!< DMA2 Channel 5 global Interrupt                                   */
  ADC4_IRQn                   = 61,     /*!< ADC4  global Interrupt                                            */
  COMP1_2_3_IRQn              = 64,     /*!< COMP1, COMP2 and COMP3 global Interrupt                           */
  COMP4_5_6_IRQn              = 65,     /*!< COMP5, COMP6 and COMP4 global Interrupt                           */
  COMP7_IRQn                  = 66,     /*!< COMP7 global Interrupt                                            */
  USB_HP_IRQn                 = 74,     /*!< USB High Priority global Interrupt remap                          */
  USB_LP_IRQn                 = 75,     /*!< USB Low Priority global Interrupt  remap                          */
  USBWakeUp_RMP_IRQn          = 76,     /*!< USB Wakeup Interrupt remap                                        */
  FPU_IRQn                    = 81      /*!< Floating point Interrupt                                          */
#endif /* STM32F303xC */
#ifdef STM32F334x8 
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMPER_STAMP_IRQn           = 2,      /*!< Tamper and TimeStamp interrupts                                   */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI lines 17, 19 & 20           */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_TS_IRQn               = 8,      /*!< EXTI Line2 Interrupt and Touch Sense Interrupt                    */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 Interrupt                                          */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 Interrupt                                          */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 Interrupt                                          */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 Interrupt                                          */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 Interrupt                                          */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 Interrupt                                          */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 Interrupt                                          */
  ADC1_2_IRQn                 = 18,     /*!< ADC1 & ADC2 Interrupts                                            */
  CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupts                                                */
  CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupts                                               */
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM15_IRQn         = 24,     /*!< TIM1 Break and TIM15 Interrupts                                   */
  TIM1_UP_TIM16_IRQn          = 25,     /*!< TIM1 Update and TIM16 Interrupts                                  */
  TIM1_TRG_COM_TIM17_IRQn     = 26,     /*!< TIM1 Trigger and Commutation and TIM17 Interrupt                  */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */ 
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */  
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  TIM6_DAC1_IRQn              = 54,     /*!< TIM6 global and DAC1 underrun error  interrupts                   */
  TIM7_DAC2_IRQn              = 55,     /*!< TIM7 global and DAC2 underrun error Interrupt                      */
  COMP2_IRQn                  = 64,     /*!< COMP2 global Interrupt                                            */
  COMP4_6_IRQn                = 65,     /*!< COMP6 and COMP4 global Interrupt                                  */  
  HRTIM1_Master_IRQn          = 67,     /*!< HRTIM Master Timer global Interrupts                              */
  HRTIM1_TIMA_IRQn            = 68,     /*!< HRTIM Timer A global Interrupt                                    */
  HRTIM1_TIMB_IRQn            = 69,     /*!< HRTIM Timer B global Interrupt                                    */
  HRTIM1_TIMC_IRQn            = 70,     /*!< HRTIM Timer C global Interrupt                                    */
  HRTIM1_TIMD_IRQn            = 71,     /*!< HRTIM Timer D global Interrupt                                    */
  HRTIM1_TIME_IRQn            = 72,     /*!< HRTIM Timer E global Interrupt                                    */
  HRTIM1_FLT_IRQn             = 73,     /*!< HRTIM Fault global Interrupt                                      */
  FPU_IRQn                    = 81      /*!< Floating point Interrupt                                          */
#endif /* STM32F334x8 */
#ifdef STM32F302x8 
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMPER_STAMP_IRQn           = 2,      /*!< Tamper and TimeStamp interrupts                                   */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI lines 20           */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_TS_IRQn               = 8,      /*!< EXTI Line2 Interrupt and Touch Sense Interrupt                    */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 Interrupt                                          */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 Interrupt                                          */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 Interrupt                                          */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 Interrupt                                          */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 Interrupt                                          */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 Interrupt                                          */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 Interrupt                                          */
  ADC1_IRQn                   = 18,     /*!< ADC1 Interrupts                                            */
  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts                    */
  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts                    */  
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM15_IRQn         = 24,     /*!< TIM1 Break and TIM15 Interrupts                                   */
  TIM1_UP_TIM16_IRQn          = 25,     /*!< TIM1 Update and TIM16 Interrupts                                  */
  TIM1_TRG_COM_TIM17_IRQn     = 26,     /*!< TIM1 Trigger and Commutation and TIM17 Interrupt                  */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */ 
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */  
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */  
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  USBWakeUp_IRQn              = 42,     /*!< USB Wakeup Interrupt                                              */
  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  TIM6_DAC_IRQn               = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
  COMP2_IRQn                  = 64,     /*!< COMP2 global Interrupt                           */
  COMP4_6_IRQn                = 65,     /*!< COMP5, COMP6 and COMP4 global Interrupt                           */
  COMP7_IRQn                  = 66,     /*!< COMP7 global Interrupt                                            */
  I2C3_EV_IRQn                = 72,     /*!< I2C3 Event Interrupt                                              */
  I2C3_ER_IRQn                = 73,     /*!< I2C3 Error Interrupt                                              */ 
  USB_HP_IRQn                 = 74,     /*!< USB High Priority global Interrupt remap                          */
  USB_LP_IRQn                 = 75,     /*!< USB Low Priority global Interrupt  remap                          */
  USBWakeUp_RMP_IRQn          = 76,     /*!< USB Wakeup Interrupt remap                                        */
  FPU_IRQn                    = 81      /*!< Floating point Interrupt                                          */
#endif /* STM32F302x8 */
} IRQn_Type;

/**
  * @}
  */

#include "core_cm4.h"            /* Cortex-M4 processor and core peripherals */
#include "system_stm32f30x.h"    /* STM32F30x System Header */
#include <stdint.h>

/** @addtogroup Exported_types
  * @{
  */  
/*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/**
  * @}
  */

/** @addtogroup Peripheral_registers_structures
  * @{
  */   

/** 
  * @brief Analog to Digital Converter  
  */

typedef struct
{
  __IO uint32_t ISR;              /*!< ADC Interrupt and Status Register,                 Address offset: 0x00 */
  __IO uint32_t IER;              /*!< ADC Interrupt Enable Register,                     Address offset: 0x04 */      
  __IO uint32_t CR;               /*!< ADC control register,                              Address offset: 0x08 */
  __IO uint32_t CFGR;             /*!< ADC Configuration register,                        Address offset: 0x0C */
  uint32_t      RESERVED0;        /*!< Reserved, 0x010                                                         */
  __IO uint32_t SMPR1;            /*!< ADC sample time register 1,                        Address offset: 0x14 */
  __IO uint32_t SMPR2;            /*!< ADC sample time register 2,                        Address offset: 0x18 */
  uint32_t      RESERVED1;        /*!< Reserved, 0x01C                                                         */
  __IO uint32_t TR1;              /*!< ADC watchdog threshold register 1,                 Address offset: 0x20 */
  __IO uint32_t TR2;              /*!< ADC watchdog threshold register 2,                 Address offset: 0x24 */
  __IO uint32_t TR3;              /*!< ADC watchdog threshold register 3,                 Address offset: 0x28 */
  uint32_t      RESERVED2;        /*!< Reserved, 0x02C                                                         */
  __IO uint32_t SQR1;             /*!< ADC regular sequence register 1,                   Address offset: 0x30 */
  __IO uint32_t SQR2;             /*!< ADC regular sequence register 2,                   Address offset: 0x34 */
  __IO uint32_t SQR3;             /*!< ADC regular sequence register 3,                   Address offset: 0x38 */
  __IO uint32_t SQR4;             /*!< ADC regular sequence register 4,                   Address offset: 0x3C */
  __IO uint32_t DR;               /*!< ADC regular data register,                         Address offset: 0x40 */
  uint32_t      RESERVED3;        /*!< Reserved, 0x044                                                         */
  uint32_t      RESERVED4;        /*!< Reserved, 0x048                                                         */
  __IO uint32_t JSQR;             /*!< ADC injected sequence register,                    Address offset: 0x4C */
  uint32_t      RESERVED5[4];     /*!< Reserved, 0x050 - 0x05C                                                 */
  __IO uint32_t OFR1;             /*!< ADC offset register 1,                             Address offset: 0x60 */
  __IO uint32_t OFR2;             /*!< ADC offset register 2,                             Address offset: 0x64 */
  __IO uint32_t OFR3;             /*!< ADC offset register 3,                             Address offset: 0x68 */
  __IO uint32_t OFR4;             /*!< ADC offset register 4,                             Address offset: 0x6C */
  uint32_t      RESERVED6[4];     /*!< Reserved, 0x070 - 0x07C                                                 */
  __IO uint32_t JDR1;             /*!< ADC injected data register 1,                      Address offset: 0x80 */
  __IO uint32_t JDR2;             /*!< ADC injected data register 2,                      Address offset: 0x84 */
  __IO uint32_t JDR3;             /*!< ADC injected data register 3,                      Address offset: 0x88 */
  __IO uint32_t JDR4;             /*!< ADC injected data register 4,                      Address offset: 0x8C */
  uint32_t      RESERVED7[4];     /*!< Reserved, 0x090 - 0x09C                                                 */  
  __IO uint32_t AWD2CR;           /*!< ADC  Analog Watchdog 2 Configuration Register,     Address offset: 0xA0 */
  __IO uint32_t AWD3CR;           /*!< ADC  Analog Watchdog 3 Configuration Register,     Address offset: 0xA4 */
  uint32_t      RESERVED8;        /*!< Reserved, 0x0A8                                                         */
  uint32_t      RESERVED9;        /*!< Reserved, 0x0AC                                                         */  
  __IO uint32_t DIFSEL;           /*!< ADC  Differential Mode Selection Register,         Address offset: 0xB0 */
  __IO uint32_t CALFACT;          /*!< ADC  Calibration Factors,                          Address offset: 0xB4 */
  
} ADC_TypeDef;

typedef struct
{
  __IO uint32_t CSR;            /*!< ADC Common status register,                  Address offset: ADC1/3 base address + 0x300 */
  uint32_t      RESERVED;       /*!< Reserved, ADC1/3 base address + 0x304                                                    */
  __IO uint32_t CCR;            /*!< ADC common control register,                 Address offset: ADC1/3 base address + 0x308 */
  __IO uint32_t CDR;            /*!< ADC common regular data register for dual
                                     modes,                                       Address offset: ADC1/3 base address + 0x30A */
} ADC_Common_TypeDef;
  

/** 
  * @brief Controller Area Network TxMailBox 
  */
typedef struct
{
  __IO uint32_t TIR;  /*!< CAN TX mailbox identifier register */
  __IO uint32_t TDTR; /*!< CAN mailbox data length control and time stamp register */
  __IO uint32_t TDLR; /*!< CAN mailbox data low register */
  __IO uint32_t TDHR; /*!< CAN mailbox data high register */
} CAN_TxMailBox_TypeDef;

/** 
  * @brief Controller Area Network FIFOMailBox 
  */
typedef struct
{
  __IO uint32_t RIR;  /*!< CAN receive FIFO mailbox identifier register */
  __IO uint32_t RDTR; /*!< CAN receive FIFO mailbox data length control and time stamp register */
  __IO uint32_t RDLR; /*!< CAN receive FIFO mailbox data low register */
  __IO uint32_t RDHR; /*!< CAN receive FIFO mailbox data high register */
} CAN_FIFOMailBox_TypeDef;
  
/** 
  * @brief Controller Area Network FilterRegister 
  */
typedef struct
{
  __IO uint32_t FR1; /*!< CAN Filter bank register 1 */
  __IO uint32_t FR2; /*!< CAN Filter bank register 1 */
} CAN_FilterRegister_TypeDef;

/** 
  * @brief Controller Area Network 
  */
typedef struct
{
  __IO uint32_t              MCR;                 /*!< CAN master control register,         Address offset: 0x00          */
  __IO uint32_t              MSR;                 /*!< CAN master status register,          Address offset: 0x04          */
  __IO uint32_t              TSR;                 /*!< CAN transmit status register,        Address offset: 0x08          */
  __IO uint32_t              RF0R;                /*!< CAN receive FIFO 0 register,         Address offset: 0x0C          */
  __IO uint32_t              RF1R;                /*!< CAN receive FIFO 1 register,         Address offset: 0x10          */
  __IO uint32_t              IER;                 /*!< CAN interrupt enable register,       Address offset: 0x14          */
  __IO uint32_t              ESR;                 /*!< CAN error status register,           Address offset: 0x18          */
  __IO uint32_t              BTR;                 /*!< CAN bit timing register,             Address offset: 0x1C          */
  uint32_t                   RESERVED0[88];       /*!< Reserved, 0x020 - 0x17F                                            */
  CAN_TxMailBox_TypeDef      sTxMailBox[3];       /*!< CAN Tx MailBox,                      Address offset: 0x180 - 0x1AC */
  CAN_FIFOMailBox_TypeDef    sFIFOMailBox[2];     /*!< CAN FIFO MailBox,                    Address offset: 0x1B0 - 0x1CC */
  uint32_t                   RESERVED1[12];       /*!< Reserved, 0x1D0 - 0x1FF                                            */
  __IO uint32_t              FMR;                 /*!< CAN filter master register,          Address offset: 0x200         */
  __IO uint32_t              FM1R;                /*!< CAN filter mode register,            Address offset: 0x204         */
  uint32_t                   RESERVED2;           /*!< Reserved, 0x208                                                    */
  __IO uint32_t              FS1R;                /*!< CAN filter scale register,           Address offset: 0x20C         */
  uint32_t                   RESERVED3;           /*!< Reserved, 0x210                                                    */
  __IO uint32_t              FFA1R;               /*!< CAN filter FIFO assignment register, Address offset: 0x214         */
  uint32_t                   RESERVED4;           /*!< Reserved, 0x218                                                    */
  __IO uint32_t              FA1R;                /*!< CAN filter activation register,      Address offset: 0x21C         */
  uint32_t                   RESERVED5[8];        /*!< Reserved, 0x220-0x23F                                              */
  CAN_FilterRegister_TypeDef sFilterRegister[28]; /*!< CAN Filter Register,                 Address offset: 0x240-0x31C   */
} CAN_TypeDef;


/** 
  * @brief Analog Comparators 
  */

typedef struct
{
  __IO uint32_t CSR;    /*!< Comparator control Status register, Address offset: 0x00 */
} COMP_TypeDef;

/** 
  * @brief CRC calculation unit 
  */

typedef struct
{
  __IO uint32_t DR;          /*!< CRC Data register,                           Address offset: 0x00 */
  __IO uint8_t  IDR;         /*!< CRC Independent data register,               Address offset: 0x04 */
  uint8_t       RESERVED0;   /*!< Reserved,                                                    0x05 */
  uint16_t      RESERVED1;   /*!< Reserved,                                                    0x06 */
  __IO uint32_t CR;          /*!< CRC Control register,                        Address offset: 0x08 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                    0x0C */
  __IO uint32_t INIT;        /*!< Initial CRC value register,                  Address offset: 0x10 */
  __IO uint32_t POL;         /*!< CRC polynomial register,                     Address offset: 0x14 */
} CRC_TypeDef;

/** 
  * @brief Digital to Analog Converter
  */

typedef struct
{
  __IO uint32_t CR;       /*!< DAC control register,                                    Address offset: 0x00 */
  __IO uint32_t SWTRIGR;  /*!< DAC software trigger register,                           Address offset: 0x04 */
  __IO uint32_t DHR12R1;  /*!< DAC channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
  __IO uint32_t DHR12L1;  /*!< DAC channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
  __IO uint32_t DHR8R1;   /*!< DAC channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
  __IO uint32_t DHR12R2;  /*!< DAC channel2 12-bit right aligned data holding register, Address offset: 0x14 */
  __IO uint32_t DHR12L2;  /*!< DAC channel2 12-bit left aligned data holding register,  Address offset: 0x18 */
  __IO uint32_t DHR8R2;   /*!< DAC channel2 8-bit right-aligned data holding register,  Address offset: 0x1C */
  __IO uint32_t DHR12RD;  /*!< Dual DAC 12-bit right-aligned data holding register,     Address offset: 0x20 */
  __IO uint32_t DHR12LD;  /*!< DUAL DAC 12-bit left aligned data holding register,      Address offset: 0x24 */
  __IO uint32_t DHR8RD;   /*!< DUAL DAC 8-bit right aligned data holding register,      Address offset: 0x28 */
  __IO uint32_t DOR1;     /*!< DAC channel1 data output register,                       Address offset: 0x2C */
  __IO uint32_t DOR2;     /*!< DAC channel2 data output register,                       Address offset: 0x30 */
  __IO uint32_t SR;       /*!< DAC status register,                                     Address offset: 0x34 */
} DAC_TypeDef;

/** 
  * @brief Debug MCU
  */

typedef struct
{
  __IO uint32_t IDCODE;  /*!< MCU device ID code,               Address offset: 0x00 */
  __IO uint32_t CR;      /*!< Debug MCU configuration register, Address offset: 0x04 */
  __IO uint32_t APB1FZ;  /*!< Debug MCU APB1 freeze register,   Address offset: 0x08 */
  __IO uint32_t APB2FZ;  /*!< Debug MCU APB2 freeze register,   Address offset: 0x0C */
}DBGMCU_TypeDef;

/** 
  * @brief DMA Controller
  */

typedef struct
{
  __IO uint32_t CCR;          /*!< DMA channel x configuration register                                           */
  __IO uint32_t CNDTR;        /*!< DMA channel x number of data register                                          */
  __IO uint32_t CPAR;         /*!< DMA channel x peripheral address register                                      */
  __IO uint32_t CMAR;         /*!< DMA channel x memory address register                                          */
} DMA_Channel_TypeDef;

typedef struct
{
  __IO uint32_t ISR;    /*!< DMA interrupt status register,      Address offset: 0x00 */
  __IO uint32_t IFCR;   /*!< DMA interrupt clear flag register,  Address offset: 0x04 */
} DMA_TypeDef;

/** 
  * @brief External Interrupt/Event Controller
  */

typedef struct
{
  __IO uint32_t IMR;        /*!< EXTI Interrupt mask register,                Address offset: 0x00 */
  __IO uint32_t EMR;        /*!< EXTI Event mask register,                    Address offset: 0x04 */
  __IO uint32_t RTSR;       /*!< EXTI Rising trigger selection register,      Address offset: 0x08 */
  __IO uint32_t FTSR;       /*!< EXTI Falling trigger selection register,     Address offset: 0x0C */
  __IO uint32_t SWIER;      /*!< EXTI Software interrupt event register,      Address offset: 0x10 */
  __IO uint32_t PR;         /*!< EXTI Pending register,                       Address offset: 0x14 */
  uint32_t      RESERVED1;  /*!< Reserved, 0x18                                                    */
  uint32_t      RESERVED2;  /*!< Reserved, 0x1C                                                    */
  __IO uint32_t IMR2;       /*!< EXTI Interrupt mask register,                Address offset: 0x20 */
  __IO uint32_t EMR2;       /*!< EXTI Event mask register,                    Address offset: 0x24 */
  __IO uint32_t RTSR2;      /*!< EXTI Rising trigger selection register,      Address offset: 0x28 */
  __IO uint32_t FTSR2;      /*!< EXTI Falling trigger selection register,     Address offset: 0x2C */
  __IO uint32_t SWIER2;     /*!< EXTI Software interrupt event register,      Address offset: 0x30 */
  __IO uint32_t PR2;        /*!< EXTI Pending register,                       Address offset: 0x34 */
}EXTI_TypeDef;

/** 
  * @brief FLASH Registers
  */

typedef struct
{
  __IO uint32_t ACR;          /*!< FLASH access control register,              Address offset: 0x00 */
  __IO uint32_t KEYR;         /*!< FLASH key register,                         Address offset: 0x04 */
  __IO uint32_t OPTKEYR;      /*!< FLASH option key register,                  Address offset: 0x08 */
  __IO uint32_t SR;           /*!< FLASH status register,                      Address offset: 0x0C */
  __IO uint32_t CR;           /*!< FLASH control register,                     Address offset: 0x10 */
  __IO uint32_t AR;           /*!< FLASH address register,                     Address offset: 0x14 */
  uint32_t      RESERVED;     /*!< Reserved, 0x18                                                   */
  __IO uint32_t OBR;          /*!< FLASH Option byte register,                 Address offset: 0x1C */
  __IO uint32_t WRPR;         /*!< FLASH Write register,                       Address offset: 0x20 */
  
} FLASH_TypeDef;

/** 
  * @brief Option Bytes Registers
  */
typedef struct
{
  __IO uint16_t RDP;          /*!<FLASH option byte Read protection,             Address offset: 0x00 */
  __IO uint16_t USER;         /*!<FLASH option byte user options,                Address offset: 0x02 */
  uint16_t RESERVED0;         /*!< Reserved,                                                     0x04 */
  uint16_t RESERVED1;         /*!< Reserved,                                                     0x06 */
  __IO uint16_t WRP0;         /*!<FLASH option byte write protection 0,          Address offset: 0x08 */
  __IO uint16_t WRP1;         /*!<FLASH option byte write protection 1,          Address offset: 0x0C */
  __IO uint16_t WRP2;         /*!<FLASH option byte write protection 2,          Address offset: 0x10 */
  __IO uint16_t WRP3;         /*!<FLASH option byte write protection 3,          Address offset: 0x12 */
} OB_TypeDef;

/** 
  * @brief General Purpose I/O
  */

typedef struct
{
  __IO uint32_t MODER;        /*!< GPIO port mode register,                                  Address offset: 0x00 */
  __IO uint16_t OTYPER;       /*!< GPIO port output type register,                           Address offset: 0x04 */
  uint16_t RESERVED0;         /*!< Reserved,                                                                 0x06 */
  __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,                          Address offset: 0x08 */
  __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,                     Address offset: 0x0C */
  __IO uint16_t IDR;          /*!< GPIO port input data register,                            Address offset: 0x10 */
  uint16_t RESERVED1;         /*!< Reserved,                                                                 0x12 */
  __IO uint16_t ODR;          /*!< GPIO port output data register,                           Address offset: 0x14 */
  uint16_t RESERVED2;         /*!< Reserved,                                                                 0x16 */
  __IO uint32_t BSRR;         /*!< GPIO port bit set/reset registerBSRR,                     Address offset: 0x18 */
  __IO uint32_t LCKR;         /*!< GPIO port configuration lock register,                    Address offset: 0x1C */
  __IO uint32_t AFR[2];       /*!< GPIO alternate function low register,                Address offset: 0x20-0x24 */
  __IO uint16_t BRR;          /*!< GPIO bit reset register,                                  Address offset: 0x28 */
  uint16_t RESERVED3;         /*!< Reserved,                                                                 0x2A */
}GPIO_TypeDef;

/** 
  * @brief High resolution Timer (HRTIM)
  */
/* HRTIM master definition */
typedef struct
{
  __IO uint32_t MCR;            /*!< HRTIM Master Timer control register,                     Address offset: 0x00 */
  __IO uint32_t MISR;           /*!< HRTIM Master Timer interrupt status register,            Address offset: 0x04 */
  __IO uint32_t MICR;           /*!< HRTIM Master Timer interupt clear register,              Address offset: 0x08 */
  __IO uint32_t MDIER;          /*!< HRTIM Master Timer DMA/interrupt enable register         Address offset: 0x0C */
  __IO uint32_t MCNTR;          /*!< HRTIM Master Timer counter register,                     Address offset: 0x10 */
  __IO uint32_t MPER;           /*!< HRTIM Master Timer period register,                      Address offset: 0x14 */
  __IO uint32_t MREP;           /*!< HRTIM Master Timer repetition register,                  Address offset: 0x18 */
  __IO uint32_t MCMP1R;         /*!< HRTIM Master Timer compare 1 register,                   Address offset: 0x1C */
  uint32_t      RESERVED0;     /*!< Reserved,                                                                0x20 */
  __IO uint32_t MCMP2R;         /*!< HRTIM Master Timer compare 2 register,                   Address offset: 0x24 */
  __IO uint32_t MCMP3R;         /*!< HRTIM Master Timer compare 3 register,                   Address offset: 0x28 */
  __IO uint32_t MCMP4R;         /*!< HRTIM Master Timer compare 4 register,                   Address offset: 0x2C */
}HRTIM_Master_TypeDef; 
 
/* HRTIM slave definition */
typedef struct
{
  __IO uint32_t TIMxCR;     /*!< HRTIM Timerx control register,                              Address offset: 0x00  */
  __IO uint32_t TIMxISR;    /*!< HRTIM Timerx interrupt status register,                     Address offset: 0x04  */
  __IO uint32_t TIMxICR;    /*!< HRTIM Timerx interrupt clear register,                      Address offset: 0x08  */
  __IO uint32_t TIMxDIER;   /*!< HRTIM Timerx DMA/interrupt enable register,                 Address offset: 0x0C  */
  __IO uint32_t CNTxR;      /*!< HRTIM Timerx counter register,                              Address offset: 0x10  */
  __IO uint32_t PERxR;      /*!< HRTIM Timerx period register,                               Address offset: 0x14  */
  __IO uint32_t REPxR;      /*!< HRTIM Timerx repetition register,                           Address offset: 0x18  */
  __IO uint32_t CMP1xR;     /*!< HRTIM Timerx compare 1 register,                            Address offset: 0x1C  */
  __IO uint32_t CMP1CxR;    /*!< HRTIM Timerx compare 1 compound register,                   Address offset: 0x20  */
  __IO uint32_t CMP2xR;     /*!< HRTIM Timerx compare 2 register,                            Address offset: 0x24  */
  __IO uint32_t CMP3xR;     /*!< HRTIM Timerx compare 3 register,                            Address offset: 0x28  */
  __IO uint32_t CMP4xR;     /*!< HRTIM Timerx compare 4 register,                            Address offset: 0x2C  */
  __IO uint32_t CPT1xR;     /*!< HRTIM Timerx capture 1 register,                            Address offset: 0x30  */
  __IO uint32_t CPT2xR;     /*!< HRTIM Timerx capture 2 register,                            Address offset: 0x34 */
  __IO uint32_t DTxR;       /*!< HRTIM Timerx dead time register,                            Address offset: 0x38 */
  __IO uint32_t SETx1R;     /*!< HRTIM Timerx output 1 set register,                         Address offset: 0x3C */
  __IO uint32_t RSTx1R;     /*!< HRTIM Timerx output 1 reset register,                       Address offset: 0x40 */
  __IO uint32_t SETx2R;     /*!< HRTIM Timerx output 2 set register,                         Address offset: 0x44 */
  __IO uint32_t RSTx2R;     /*!< HRTIM Timerx output 2 reset register,                       Address offset: 0x48 */
  __IO uint32_t EEFxR1;     /*!< HRTIM Timerx external event filtering 1 register,           Address offset: 0x4C */
  __IO uint32_t EEFxR2;     /*!< HRTIM Timerx external event filtering 2 register,           Address offset: 0x50 */
  __IO uint32_t RSTxR;      /*!< HRTIM Timerx Reset register,                                Address offset: 0x54 */
  __IO uint32_t CHPxR;      /*!< HRTIM Timerx Chopper register,                              Address offset: 0x58 */
  __IO uint32_t CPT1xCR;    /*!< HRTIM Timerx Capture 1 register,                            Address offset: 0x5C */
  __IO uint32_t CPT2xCR;    /*!< HRTIM Timerx Capture 2 register,                            Address offset: 0x60 */
  __IO uint32_t OUTxR;      /*!< HRTIM Timerx Output register,                               Address offset: 0x64 */
  __IO uint32_t FLTxR;      /*!< HRTIM Timerx Fault register,                                Address offset: 0x68 */
  uint32_t      RESERVED0[5];/*!< Reserved,                                                                       */
}HRTIM_Timerx_TypeDef;

/* HRTIM common register definition */
typedef struct
{
  __IO uint32_t CR1;        /*!< HRTIM control register1,                                    Address offset: 0x00 */
  __IO uint32_t CR2;        /*!< HRTIM control register2,                                    Address offset: 0x04 */
  __IO uint32_t ISR;        /*!< HRTIM interrupt status register,                            Address offset: 0x08 */
  __IO uint32_t ICR;        /*!< HRTIM interrupt clear register,                             Address offset: 0x0C */
  __IO uint32_t IER;        /*!< HRTIM interrupt enable register,                            Address offset: 0x10 */
  __IO uint32_t OENR;       /*!< HRTIM Output enable register,                               Address offset: 0x14 */
  __IO uint32_t DISR;       /*!< HRTIM Output disable register,                              Address offset: 0x18 */
  __IO uint32_t ODSR;       /*!< HRTIM Output disable status register,                       Address offset: 0x1C */
  __IO uint32_t BMCR;       /*!< HRTIM Burst mode control register,                          Address offset: 0x20 */
  __IO uint32_t BMTRGR;     /*!< HRTIM Busrt mode trigger register,                          Address offset: 0x24 */
  __IO uint32_t BMCMPR;     /*!< HRTIM Burst mode compare register,                          Address offset: 0x28 */
  __IO uint32_t BMPER;      /*!< HRTIM Burst mode period register,                           Address offset: 0x2C */
  __IO uint32_t EECR1;      /*!< HRTIM Timer external event control register1,               Address offset: 0x30 */
  __IO uint32_t EECR2;      /*!< HRTIM Timer external event control register2,               Address offset: 0x34 */
  __IO uint32_t EECR3;      /*!< HRTIM Timer external event control register3,               Address offset: 0x38 */
  __IO uint32_t ADC1R;      /*!< HRTIM ADC Trigger 1 register,                               Address offset: 0x3C */
  __IO uint32_t ADC2R;      /*!< HRTIM ADC Trigger 2 register,                               Address offset: 0x40 */
  __IO uint32_t ADC3R;      /*!< HRTIM ADC Trigger 3 register,                               Address offset: 0x44 */
  __IO uint32_t ADC4R;      /*!< HRTIM ADC Trigger 4 register,                               Address offset: 0x48 */
  __IO uint32_t DLLCR;      /*!< HRTIM DLL control register,                                 Address offset: 0x4C */
  __IO uint32_t FLTINxR1;   /*!< HRTIM Fault input register1,                                Address offset: 0x50 */
  __IO uint32_t FLTINxR2;   /*!< HRTIM Fault input register2,                                Address offset: 0x54 */
  __IO uint32_t BDMUPDR;    /*!< HRTIM Burst DMA Master Timer update register,               Address offset: 0x58 */
  __IO uint32_t BDTAUPR;    /*!< HRTIM Burst DMA Timerx update register,                     Address offset: 0x5C */
  __IO uint32_t BDTBUPR;    /*!< HRTIM Burst DMA Timerx update register,                     Address offset: 0x60 */
  __IO uint32_t BDTCUPR;    /*!< HRTIM Burst DMA Timerx update register,                     Address offset: 0x64 */
  __IO uint32_t BDTDUPR;    /*!< HRTIM Burst DMA Timerx update register,                     Address offset: 0x68 */  
  __IO uint32_t BDTEUPR;    /*!< HRTIM Burst DMA Timerx update register,                     Address offset: 0x6C */  
  __IO uint32_t BDMADR;     /*!< HRTIM Burst DMA Master Data register,                       Address offset: 0x70 */
}HRTIM_Common_TypeDef;

/* HRTIM  register definition */
typedef struct {
  HRTIM_Master_TypeDef HRTIM_MASTER;
  uint32_t             RESERVED0[20];
  HRTIM_Timerx_TypeDef HRTIM_TIMERx[5];
  uint32_t             RESERVED1[32];
  HRTIM_Common_TypeDef HRTIM_COMMON;
}HRTIM_TypeDef;

/** 
  * @brief Operational Amplifier (OPAMP)
  */
  
typedef struct
{
  __IO uint32_t CSR;        /*!< OPAMP control and status register,            Address offset: 0x00 */
} OPAMP_TypeDef;


/** 
  * @brief System configuration controller
  */

typedef struct
{
  __IO uint32_t CFGR1;      /*!< SYSCFG configuration register 1,                   Address offset: 0x00 */
  __IO uint32_t RCR;        /*!< SYSCFG CCM SRAM protection register,               Address offset: 0x04 */
  __IO uint32_t EXTICR[4];  /*!< SYSCFG external interrupt configuration registers, Address offset: 0x14-0x08 */
  __IO uint32_t CFGR2;      /*!< SYSCFG configuration register 2,                    Address offset: 0x18 */
  __IO uint32_t RESERVED0;  /*!< Reserved,                                                           0x1C */
  __IO uint32_t RESERVED1;  /*!< Reserved,                                                          0x20 */
  __IO uint32_t RESERVED2;  /*!< Reserved,                                                          0x24 */
  __IO uint32_t RESERVED4;  /*!< Reserved,                                                          0x28 */
  __IO uint32_t RESERVED5;  /*!< Reserved,                                                          0x2C */
  __IO uint32_t RESERVED6;  /*!< Reserved,                                                          0x30 */
  __IO uint32_t RESERVED7;  /*!< Reserved,                                                          0x34 */
  __IO uint32_t RESERVED8;  /*!< Reserved,                                                          0x38 */
  __IO uint32_t RESERVED9;  /*!< Reserved,                                                          0x3C */
  __IO uint32_t RESERVED10; /*!< Reserved,                                                          0x40 */
  __IO uint32_t RESERVED11; /*!< Reserved,                                                          0x44 */
  __IO uint32_t RESERVED12; /*!< Reserved,                                                          0x48 */
  __IO uint32_t RESERVED13; /*!< Reserved,                                                          0x4C */
  __IO uint32_t CFGR3;      /*!< SYSCFG configuration register 3,                    Address offset: 0x50 */
} SYSCFG_TypeDef;

/**
  * @brief Inter-integrated Circuit Interface
  */

typedef struct
{
  __IO uint32_t CR1;      /*!< I2C Control register 1,            Address offset: 0x00 */
  __IO uint32_t CR2;      /*!< I2C Control register 2,            Address offset: 0x04 */
  __IO uint32_t OAR1;     /*!< I2C Own address 1 register,        Address offset: 0x08 */
  __IO uint32_t OAR2;     /*!< I2C Own address 2 register,        Address offset: 0x0C */
  __IO uint32_t TIMINGR;  /*!< I2C Timing register,               Address offset: 0x10 */
  __IO uint32_t TIMEOUTR; /*!< I2C Timeout register,              Address offset: 0x14 */
  __IO uint32_t ISR;      /*!< I2C Interrupt and status register, Address offset: 0x18 */
  __IO uint32_t ICR;      /*!< I2C Interrupt clear register,      Address offset: 0x1C */
  __IO uint32_t PECR;     /*!< I2C PEC register,                  Address offset: 0x20 */
  __IO uint32_t RXDR;     /*!< I2C Receive data register,         Address offset: 0x24 */
  __IO uint32_t TXDR;     /*!< I2C Transmit data register,        Address offset: 0x28 */
}I2C_TypeDef;

/**
  * @brief Independent WATCHDOG
  */

typedef struct
{
  __IO uint32_t KR;   /*!< IWDG Key register,       Address offset: 0x00 */
  __IO uint32_t PR;   /*!< IWDG Prescaler register, Address offset: 0x04 */
  __IO uint32_t RLR;  /*!< IWDG Reload register,    Address offset: 0x08 */
  __IO uint32_t SR;   /*!< IWDG Status register,    Address offset: 0x0C */
  __IO uint32_t WINR; /*!< IWDG Window register,    Address offset: 0x10 */
} IWDG_TypeDef;

/**
  * @brief Power Control
  */

typedef struct
{
  __IO uint32_t CR;   /*!< PWR power control register,        Address offset: 0x00 */
  __IO uint32_t CSR;  /*!< PWR power control/status register, Address offset: 0x04 */
} PWR_TypeDef;

/**
  * @brief Reset and Clock Control
  */
typedef struct
{
  __IO uint32_t CR;         /*!< RCC clock control register,                                  Address offset: 0x00 */
  __IO uint32_t CFGR;       /*!< RCC clock configuration register,                            Address offset: 0x04 */
  __IO uint32_t CIR;        /*!< RCC clock interrupt register,                                Address offset: 0x08 */
  __IO uint32_t APB2RSTR;   /*!< RCC APB2 peripheral reset register,                          Address offset: 0x0C */
  __IO uint32_t APB1RSTR;   /*!< RCC APB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t AHBENR;     /*!< RCC AHB peripheral clock register,                           Address offset: 0x14 */
  __IO uint32_t APB2ENR;    /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x18 */
  __IO uint32_t APB1ENR;    /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x1C */
  __IO uint32_t BDCR;       /*!< RCC Backup domain control register,                          Address offset: 0x20 */
  __IO uint32_t CSR;        /*!< RCC clock control & status register,                         Address offset: 0x24 */
  __IO uint32_t AHBRSTR;    /*!< RCC AHB peripheral reset register,                           Address offset: 0x28 */
  __IO uint32_t CFGR2;      /*!< RCC clock configuration register 2,                          Address offset: 0x2C */
  __IO uint32_t CFGR3;      /*!< RCC clock configuration register 3,                          Address offset: 0x30 */
} RCC_TypeDef;

/**
  * @brief Real-Time Clock
  */

typedef struct
{
  __IO uint32_t TR;         /*!< RTC time register,                                        Address offset: 0x00 */
  __IO uint32_t DR;         /*!< RTC date register,                                        Address offset: 0x04 */
  __IO uint32_t CR;         /*!< RTC control register,                                     Address offset: 0x08 */
  __IO uint32_t ISR;        /*!< RTC initialization and status register,                   Address offset: 0x0C */
  __IO uint32_t PRER;       /*!< RTC prescaler register,                                   Address offset: 0x10 */
  __IO uint32_t WUTR;       /*!< RTC wakeup timer register,                                Address offset: 0x14 */
  uint32_t RESERVED0;       /*!< Reserved, 0x18                                                                 */
  __IO uint32_t ALRMAR;     /*!< RTC alarm A register,                                     Address offset: 0x1C */
  __IO uint32_t ALRMBR;     /*!< RTC alarm B register,                                     Address offset: 0x20 */
  __IO uint32_t WPR;        /*!< RTC write protection register,                            Address offset: 0x24 */
  __IO uint32_t SSR;        /*!< RTC sub second register,                                  Address offset: 0x28 */
  __IO uint32_t SHIFTR;     /*!< RTC shift control register,                               Address offset: 0x2C */
  __IO uint32_t TSTR;       /*!< RTC time stamp time register,                             Address offset: 0x30 */
  __IO uint32_t TSDR;       /*!< RTC time stamp date register,                             Address offset: 0x34 */
  __IO uint32_t TSSSR;      /*!< RTC time-stamp sub second register,                       Address offset: 0x38 */
  __IO uint32_t CALR;       /*!< RTC calibration register,                                 Address offset: 0x3C */
  __IO uint32_t TAFCR;      /*!< RTC tamper and alternate function configuration register, Address offset: 0x40 */
  __IO uint32_t ALRMASSR;   /*!< RTC alarm A sub second register,                          Address offset: 0x44 */
  __IO uint32_t ALRMBSSR;   /*!< RTC alarm B sub second register,                          Address offset: 0x48 */
  uint32_t RESERVED7;       /*!< Reserved, 0x4C                                                                 */
  __IO uint32_t BKP0R;      /*!< RTC backup register 0,                                    Address offset: 0x50 */
  __IO uint32_t BKP1R;      /*!< RTC backup register 1,                                    Address offset: 0x54 */
  __IO uint32_t BKP2R;      /*!< RTC backup register 2,                                    Address offset: 0x58 */
  __IO uint32_t BKP3R;      /*!< RTC backup register 3,                                    Address offset: 0x5C */
  __IO uint32_t BKP4R;      /*!< RTC backup register 4,                                    Address offset: 0x60 */
  __IO uint32_t BKP5R;      /*!< RTC backup register 5,                                    Address offset: 0x64 */
  __IO uint32_t BKP6R;      /*!< RTC backup register 6,                                    Address offset: 0x68 */
  __IO uint32_t BKP7R;      /*!< RTC backup register 7,                                    Address offset: 0x6C */
  __IO uint32_t BKP8R;      /*!< RTC backup register 8,                                    Address offset: 0x70 */
  __IO uint32_t BKP9R;      /*!< RTC backup register 9,                                    Address offset: 0x74 */
  __IO uint32_t BKP10R;     /*!< RTC backup register 10,                                   Address offset: 0x78 */
  __IO uint32_t BKP11R;     /*!< RTC backup register 11,                                   Address offset: 0x7C */
  __IO uint32_t BKP12R;     /*!< RTC backup register 12,                                   Address offset: 0x80 */
  __IO uint32_t BKP13R;     /*!< RTC backup register 13,                                   Address offset: 0x84 */
  __IO uint32_t BKP14R;     /*!< RTC backup register 14,                                   Address offset: 0x88 */
  __IO uint32_t BKP15R;     /*!< RTC backup register 15,                                   Address offset: 0x8C */
} RTC_TypeDef;


/**
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  __IO uint16_t CR1;      /*!< SPI Control register 1 (not used in I2S mode),       Address offset: 0x00 */
  uint16_t  RESERVED0;    /*!< Reserved, 0x02                                                            */
  __IO uint16_t CR2;      /*!< SPI Control register 2,                              Address offset: 0x04 */
  uint16_t  RESERVED1;    /*!< Reserved, 0x06                                                            */
  __IO uint16_t SR;       /*!< SPI Status register,                                 Address offset: 0x08 */
  uint16_t  RESERVED2;    /*!< Reserved, 0x0A                                                            */
  __IO uint16_t DR;       /*!< SPI data register,                                   Address offset: 0x0C */
  uint16_t  RESERVED3;    /*!< Reserved, 0x0E                                                            */
  __IO uint16_t CRCPR;    /*!< SPI CRC polynomial register (not used in I2S mode),  Address offset: 0x10 */
  uint16_t  RESERVED4;    /*!< Reserved, 0x12                                                            */
  __IO uint16_t RXCRCR;   /*!< SPI Rx CRC register (not used in I2S mode),          Address offset: 0x14 */
  uint16_t  RESERVED5;    /*!< Reserved, 0x16                                                            */
  __IO uint16_t TXCRCR;   /*!< SPI Tx CRC register (not used in I2S mode),          Address offset: 0x18 */
  uint16_t  RESERVED6;    /*!< Reserved, 0x1A                                                            */ 
  __IO uint16_t I2SCFGR;  /*!< SPI_I2S configuration register,                      Address offset: 0x1C */
  uint16_t  RESERVED7;    /*!< Reserved, 0x1E                                                            */
  __IO uint16_t I2SPR;    /*!< SPI_I2S prescaler register,                          Address offset: 0x20 */
  uint16_t  RESERVED8;    /*!< Reserved, 0x22                                                            */    
} SPI_TypeDef;

/**
  * @brief TIM
  */
typedef struct
{
  __IO uint16_t CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
  uint16_t      RESERVED0;   /*!< Reserved, 0x02                                            */
 __IO uint32_t CR2;          /*!< TIM control register 2,              Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                 Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                Address offset: 0x24 */
  __IO uint16_t PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
  uint16_t      RESERVED9;   /*!< Reserved, 0x2A                                            */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
  __IO uint16_t RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
  uint16_t      RESERVED10;  /*!< Reserved, 0x32                                            */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
  __IO uint16_t DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
  uint16_t      RESERVED12;  /*!< Reserved, 0x4A                                            */
  __IO uint16_t DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
  uint16_t      RESERVED13;  /*!< Reserved, 0x4E                                            */
  __IO uint16_t OR;          /*!< TIM option register,                 Address offset: 0x50 */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3, Address offset: 0x54 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare register5,      Address offset: 0x58 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare register 4,      Address offset: 0x5C */
} TIM_TypeDef;


/**
  * @brief Touch Sensing Controller (TSC)
  */
typedef struct
{
  __IO uint32_t CR;            /*!< TSC control register,                                     Address offset: 0x00 */
  __IO uint32_t IER;           /*!< TSC interrupt enable register,                            Address offset: 0x04 */
  __IO uint32_t ICR;           /*!< TSC interrupt clear register,                             Address offset: 0x08 */
  __IO uint32_t ISR;           /*!< TSC interrupt status register,                            Address offset: 0x0C */
  __IO uint32_t IOHCR;         /*!< TSC I/O hysteresis control register,                      Address offset: 0x10 */
  uint32_t      RESERVED1;     /*!< Reserved,                                                 Address offset: 0x14 */
  __IO uint32_t IOASCR;        /*!< TSC I/O analog switch control register,                   Address offset: 0x18 */
  uint32_t      RESERVED2;     /*!< Reserved,                                                 Address offset: 0x1C */
  __IO uint32_t IOSCR;         /*!< TSC I/O sampling control register,                        Address offset: 0x20 */
  uint32_t      RESERVED3;     /*!< Reserved,                                                 Address offset: 0x24 */
  __IO uint32_t IOCCR;         /*!< TSC I/O channel control register,                         Address offset: 0x28 */
  uint32_t      RESERVED4;     /*!< Reserved,                                                 Address offset: 0x2C */
  __IO uint32_t IOGCSR;        /*!< TSC I/O group control status register,                    Address offset: 0x30 */
  __IO uint32_t IOGXCR[8];     /*!< TSC I/O group x counter register,                         Address offset: 0x34-50 */
} TSC_TypeDef;

/**
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */

typedef struct
{
  __IO uint32_t CR1;    /*!< USART Control register 1,                 Address offset: 0x00 */
  __IO uint32_t CR2;    /*!< USART Control register 2,                 Address offset: 0x04 */
  __IO uint32_t CR3;    /*!< USART Control register 3,                 Address offset: 0x08 */
  __IO uint16_t BRR;    /*!< USART Baud rate register,                 Address offset: 0x0C */
  uint16_t  RESERVED1;  /*!< Reserved, 0x0E                                                 */
  __IO uint16_t GTPR;   /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
  uint16_t  RESERVED2;  /*!< Reserved, 0x12                                                 */
  __IO uint32_t RTOR;   /*!< USART Receiver Time Out register,         Address offset: 0x14 */
  __IO uint16_t RQR;    /*!< USART Request register,                   Address offset: 0x18 */
  uint16_t  RESERVED3;  /*!< Reserved, 0x1A                                                 */
  __IO uint32_t ISR;    /*!< USART Interrupt and status register,      Address offset: 0x1C */
  __IO uint32_t ICR;    /*!< USART Interrupt flag Clear register,      Address offset: 0x20 */
  __IO uint16_t RDR;    /*!< USART Receive Data register,              Address offset: 0x24 */
  uint16_t  RESERVED4;  /*!< Reserved, 0x26                                                 */
  __IO uint16_t TDR;    /*!< USART Transmit Data register,             Address offset: 0x28 */
  uint16_t  RESERVED5;  /*!< Reserved, 0x2A                                                 */
} USART_TypeDef;

/**
  * @brief Window WATCHDOG
  */
typedef struct
{
  __IO uint32_t CR;   /*!< WWDG Control register,       Address offset: 0x00 */
  __IO uint32_t CFR;  /*!< WWDG Configuration register, Address offset: 0x04 */
  __IO uint32_t SR;   /*!< WWDG Status register,        Address offset: 0x08 */
} WWDG_TypeDef;

  
/** @addtogroup Peripheral_memory_map
  * @{
  */

#define FLASH_BASE            ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE             ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE          ((uint32_t)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */


/*!< Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000)
#define AHB3PERIPH_BASE       (PERIPH_BASE + 0x10000000)

/*!< APB1 peripherals */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x00000000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x00000400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x00000800)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x00001000)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x00001400)
#define RTC_BASE              (APB1PERIPH_BASE + 0x00002800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x00002C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x00003000)
#define I2S2ext_BASE          (APB1PERIPH_BASE + 0x00003400)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x00003800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x00003C00)
#define I2S3ext_BASE          (APB1PERIPH_BASE + 0x00004000)
#define USART2_BASE           (APB1PERIPH_BASE + 0x00004400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x00004800)
#define UART4_BASE            (APB1PERIPH_BASE + 0x00004C00)
#define UART5_BASE            (APB1PERIPH_BASE + 0x00005000)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x00005400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x00005800)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x00006400)
#define PWR_BASE              (APB1PERIPH_BASE + 0x00007000)
#define DAC1_BASE             (APB1PERIPH_BASE + 0x00007400)
#define I2C3_BASE             (APB1PERIPH_BASE + 0x00007800)
#define DAC2_BASE             (APB1PERIPH_BASE + 0x00009800)
#define DAC_BASE               DAC1_BASE

/*!< APB2 peripherals */
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x00000000)
#define COMP_BASE             (APB2PERIPH_BASE + 0x0000001C)
#define COMP1_BASE            (APB2PERIPH_BASE + 0x0000001C)
#define COMP2_BASE            (APB2PERIPH_BASE + 0x00000020)
#define COMP3_BASE            (APB2PERIPH_BASE + 0x00000024)
#define COMP4_BASE            (APB2PERIPH_BASE + 0x00000028)
#define COMP5_BASE            (APB2PERIPH_BASE + 0x0000002C)
#define COMP6_BASE            (APB2PERIPH_BASE + 0x00000030)
#define COMP7_BASE            (APB2PERIPH_BASE + 0x00000034)
#define OPAMP_BASE            (APB2PERIPH_BASE + 0x00000038)
#define OPAMP1_BASE           (APB2PERIPH_BASE + 0x00000038)
#define OPAMP2_BASE           (APB2PERIPH_BASE + 0x0000003C)
#define OPAMP3_BASE           (APB2PERIPH_BASE + 0x00000040)
#define OPAMP4_BASE           (APB2PERIPH_BASE + 0x00000044)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x00000400)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x00002C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x00003000)
#define TIM8_BASE             (APB2PERIPH_BASE + 0x00003400)
#define USART1_BASE           (APB2PERIPH_BASE + 0x00003800)
#define TIM15_BASE            (APB2PERIPH_BASE + 0x00004000)
#define TIM16_BASE            (APB2PERIPH_BASE + 0x00004400)
#define TIM17_BASE            (APB2PERIPH_BASE + 0x00004800)
#define HRTIM1_BASE           (APB2PERIPH_BASE + 0x00007400)
#define HRTIM1_TIMA_BASE      (HRTIM1_BASE + 0x00000080)
#define HRTIM1_TIMB_BASE      (HRTIM1_BASE + 0x00000100)
#define HRTIM1_TIMC_BASE      (HRTIM1_BASE + 0x00000180)
#define HRTIM1_TIMD_BASE      (HRTIM1_BASE + 0x00000200)
#define HRTIM1_TIME_BASE      (HRTIM1_BASE + 0x00000280)
#define HRTIM1_COMMON_BASE    (HRTIM1_BASE + 0x00000380)

/*!< AHB1 peripherals */
#define DMA1_BASE             (AHB1PERIPH_BASE + 0x00000000)
#define DMA1_Channel1_BASE    (AHB1PERIPH_BASE + 0x00000008)
#define DMA1_Channel2_BASE    (AHB1PERIPH_BASE + 0x0000001C)
#define DMA1_Channel3_BASE    (AHB1PERIPH_BASE + 0x00000030)
#define DMA1_Channel4_BASE    (AHB1PERIPH_BASE + 0x00000044)
#define DMA1_Channel5_BASE    (AHB1PERIPH_BASE + 0x00000058)
#define DMA1_Channel6_BASE    (AHB1PERIPH_BASE + 0x0000006C)
#define DMA1_Channel7_BASE    (AHB1PERIPH_BASE + 0x00000080)
#define DMA2_BASE             (AHB1PERIPH_BASE + 0x00000400)
#define DMA2_Channel1_BASE    (AHB1PERIPH_BASE + 0x00000408)
#define DMA2_Channel2_BASE    (AHB1PERIPH_BASE + 0x0000041C)
#define DMA2_Channel3_BASE    (AHB1PERIPH_BASE + 0x00000430)
#define DMA2_Channel4_BASE    (AHB1PERIPH_BASE + 0x00000444)
#define DMA2_Channel5_BASE    (AHB1PERIPH_BASE + 0x00000458)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x00001000)
#define FLASH_R_BASE          (AHB1PERIPH_BASE + 0x00002000) /*!< Flash registers base address */
#define OB_BASE               ((uint32_t)0x1FFFF800)     /*!< Flash Option Bytes base address */
#define CRC_BASE              (AHB1PERIPH_BASE + 0x00003000)
#define TSC_BASE              (AHB1PERIPH_BASE + 0x00004000)

/*!< AHB2 peripherals */
#define GPIOA_BASE            (AHB2PERIPH_BASE + 0x0000)
#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400)
#define GPIOC_BASE            (AHB2PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (AHB2PERIPH_BASE + 0x0C00)
#define GPIOE_BASE            (AHB2PERIPH_BASE + 0x1000)
#define GPIOF_BASE            (AHB2PERIPH_BASE + 0x1400)

/*!< AHB3 peripherals */
#define ADC1_BASE             (AHB3PERIPH_BASE + 0x0000)
#define ADC2_BASE             (AHB3PERIPH_BASE + 0x0100)
#define ADC1_2_BASE           (AHB3PERIPH_BASE + 0x0300)
#define ADC3_BASE             (AHB3PERIPH_BASE + 0x0400)
#define ADC4_BASE             (AHB3PERIPH_BASE + 0x0500)
#define ADC3_4_BASE           (AHB3PERIPH_BASE + 0x0700)

#define DBGMCU_BASE          ((uint32_t)0xE0042000) /*!< Debug MCU registers base address */
/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */  
#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define WWDG                ((WWDG_TypeDef *) WWDG_BASE)
#define IWDG                ((IWDG_TypeDef *) IWDG_BASE)
#define I2S2ext             ((SPI_TypeDef *) I2S2ext_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)
#define I2S3ext             ((SPI_TypeDef *) I2S3ext_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)
#define UART4               ((USART_TypeDef *) UART4_BASE)
#define UART5               ((USART_TypeDef *) UART5_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                ((I2C_TypeDef *) I2C2_BASE)
#define I2C3                ((I2C_TypeDef *) I2C3_BASE)
#define CAN1                ((CAN_TypeDef *) CAN1_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define DAC1                ((DAC_TypeDef *) DAC1_BASE)
#define DAC2                ((DAC_TypeDef *) DAC2_BASE)
#define DAC                  DAC1
#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define COMP                ((COMP_TypeDef *) COMP_BASE)
#define COMP1               ((COMP_TypeDef *) COMP1_BASE)
#define COMP2               ((COMP_TypeDef *) COMP2_BASE)
#define COMP3               ((COMP_TypeDef *) COMP3_BASE)
#define COMP4               ((COMP_TypeDef *) COMP4_BASE)
#define COMP5               ((COMP_TypeDef *) COMP5_BASE)
#define COMP6               ((COMP_TypeDef *) COMP6_BASE)
#define COMP7               ((COMP_TypeDef *) COMP7_BASE)
#define OPAMP               ((OPAMP_TypeDef *) OPAMP_BASE)
#define OPAMP1              ((OPAMP_TypeDef *) OPAMP1_BASE)
#define OPAMP2              ((OPAMP_TypeDef *) OPAMP2_BASE)
#define OPAMP3              ((OPAMP_TypeDef *) OPAMP3_BASE)
#define OPAMP4              ((OPAMP_TypeDef *) OPAMP4_BASE)
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
#define TIM1                ((TIM_TypeDef *) TIM1_BASE)
#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define TIM8                ((TIM_TypeDef *) TIM8_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define TIM15               ((TIM_TypeDef *) TIM15_BASE)
#define TIM16               ((TIM_TypeDef *) TIM16_BASE)
#define TIM17               ((TIM_TypeDef *) TIM17_BASE)
#define HRTIM1              ((HRTIM_TypeDef *) HRTIM1_BASE)
#define HRTIM1_TIMA         ((HRTIM_TIM_TypeDef *) HRTIM1_TIMA_BASE)
#define HRTIM1_TIMB         ((HRTIM_TIM_TypeDef *) HRTIM1_TIMB_BASE)
#define HRTIM1_TIMC         ((HRTIM_TIM_TypeDef *) HRTIM1_TIMC_BASE)
#define HRTIM1_TIMD         ((HRTIM_TIM_TypeDef *) HRTIM1_TIMD_BASE)
#define HRTIM1_TIME         ((HRTIM_TIM_TypeDef *) HRTIM1_TIME_BASE)
#define HRTIM1_COMMON       ((HRTIM_Common_TypeDef *) HRTIM1_COMMON_BASE)
#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)
#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA1_Channel1       ((DMA_Channel_TypeDef *) DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_TypeDef *) DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_TypeDef *) DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_TypeDef *) DMA1_Channel6_BASE)
#define DMA1_Channel7       ((DMA_Channel_TypeDef *) DMA1_Channel7_BASE)
#define DMA2                ((DMA_TypeDef *) DMA2_BASE)
#define DMA2_Channel1       ((DMA_Channel_TypeDef *) DMA2_Channel1_BASE)
#define DMA2_Channel2       ((DMA_Channel_TypeDef *) DMA2_Channel2_BASE)
#define DMA2_Channel3       ((DMA_Channel_TypeDef *) DMA2_Channel3_BASE)
#define DMA2_Channel4       ((DMA_Channel_TypeDef *) DMA2_Channel4_BASE)
#define DMA2_Channel5       ((DMA_Channel_TypeDef *) DMA2_Channel5_BASE)
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define OB                  ((OB_TypeDef *) OB_BASE)
#define CRC                 ((CRC_TypeDef *) CRC_BASE)
#define TSC                 ((TSC_TypeDef *) TSC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC2                ((ADC_TypeDef *) ADC2_BASE)
#define ADC3                ((ADC_TypeDef *) ADC3_BASE)
#define ADC4                ((ADC_TypeDef *) ADC4_BASE)
#define ADC1_2              ((ADC_Common_TypeDef *) ADC1_2_BASE)
#define ADC3_4              ((ADC_Common_TypeDef *) ADC3_4_BASE)
/**
  * @}
  */

/** @addtogroup Exported_constants
  * @{
  */
  
  /** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */
    
/******************************************************************************/
/*                         Peripheral Registers_Bits_Definition               */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                        High Resolution Timer (HRTIM)                       */
/*                                                                            */
/******************************************************************************/
/******************** Master Timer control register ***************************/
#define HRTIM_MCR_CK_PSC     ((uint32_t)0x00000007)   /*!< Prescaler mask */
#define HRTIM_MCR_CK_PSC_0   ((uint32_t)0x00000001)   /*!< Prescaler bit 0 */ 
#define HRTIM_MCR_CK_PSC_1   ((uint32_t)0x00000002)   /*!< Prescaler bit 1 */ 
#define HRTIM_MCR_CK_PSC_2   ((uint32_t)0x00000004)   /*!< Prescaler bit 2 */ 

#define HRTIM_MCR_CONT       ((uint32_t)0x00000008)   /*!< Continuous mode */
#define HRTIM_MCR_RETRIG     ((uint32_t)0x00000010)   /*!< Rettrigreable mode */
#define HRTIM_MCR_HALF       ((uint32_t)0x00000020)   /*!< Half mode */

#define HRTIM_MCR_SYNC_IN    ((uint32_t)0x00000300)   /*!< Synchronization input master */
#define HRTIM_MCR_SYNC_IN_0  ((uint32_t)0x00000100)   /*!< Synchronization input bit 0 */
#define HRTIM_MCR_SYNC_IN_1  ((uint32_t)0x00000200)   /*!< Synchronization input bit 1 */
#define HRTIM_MCR_SYNCRSTM   ((uint32_t)0x00000400)   /*!< Synchronization reset master */
#define HRTIM_MCR_SYNCSTRTM  ((uint32_t)0x00000800)   /*!< Synchronization start master */
#define HRTIM_MCR_SYNC_OUT   ((uint32_t)0x00003000)   /*!< Synchronization output master */
#define HRTIM_MCR_SYNC_OUT_0 ((uint32_t)0x00001000)   /*!< Synchronization output bit 0 */
#define HRTIM_MCR_SYNC_OUT_1 ((uint32_t)0x00002000)   /*!< Synchronization output bit 1 */
#define HRTIM_MCR_SYNC_SRC   ((uint32_t)0x0000C000)   /*!< Synchronization source */
#define HRTIM_MCR_SYNC_SRC_0 ((uint32_t)0x00004000)   /*!< Synchronization source bit 0 */
#define HRTIM_MCR_SYNC_SRC_1 ((uint32_t)0x00008000)   /*!< Synchronization source bit 1 */

#define HRTIM_MCR_MCEN       ((uint32_t)0x00010000)   /*!< Master counter enable */
#define HRTIM_MCR_TACEN      ((uint32_t)0x00020000)   /*!< Timer A counter enable */
#define HRTIM_MCR_TBCEN      ((uint32_t)0x00040000)   /*!< Timer B counter enable */
#define HRTIM_MCR_TCCEN      ((uint32_t)0x00080000)   /*!< Timer C counter enable */
#define HRTIM_MCR_TDCEN      ((uint32_t)0x00100000)   /*!< Timer D counter enable */
#define HRTIM_MCR_TECEN      ((uint32_t)0x00200000)   /*!< Timer E counter enable */

#define HRTIM_MCR_DACSYNC    ((uint32_t)0x06000000)   /*!< DAC synchronization mask */
#define HRTIM_MCR_DACSYNC_0  ((uint32_t)0x02000000)   /*!< DAC synchronization bit 0 */
#define HRTIM_MCR_DACSYNC_1  ((uint32_t)0x04000000)   /*!< DAC synchronization bit 1 */

#define HRTIM_MCR_PREEN      ((uint32_t)0x08000000)   /*!< Master preload enable */
#define HRTIM_MCR_MREPU      ((uint32_t)0x20000000)   /*!< Master repetition update */

#define HRTIM_MCR_BRSTDMA    ((uint32_t)0xC0000000)   /*!< Burst DMA update */
#define HRTIM_MCR_BRSTDMA_0  ((uint32_t)0x40000000)   /*!< Burst DMA update bit 0*/
#define HRTIM_MCR_BRSTDMA_1  ((uint32_t)0x80000000)   /*!< Burst DMA update bit 1 */

/******************** Master Timer Interrupt status register ******************/
#define HRTIM_MISR_MCMP1    ((uint32_t)0x00000001)  /*!< Master compare 1 interrupt flag */
#define HRTIM_MISR_MCMP2    ((uint32_t)0x00000002)  /*!< Master compare 2 interrupt flag */
#define HRTIM_MISR_MCMP3    ((uint32_t)0x00000004)  /*!< Master compare 3 interrupt flag */
#define HRTIM_MISR_MCMP4    ((uint32_t)0x00000008)  /*!< Master compare 4 interrupt flag */
#define HRTIM_MISR_MREP     ((uint32_t)0x00000010)  /*!< Master Repetition interrupt flag */
#define HRTIM_MISR_SYNC     ((uint32_t)0x00000020)  /*!< Synchronization input interrupt flag */
#define HRTIM_MISR_MUPD     ((uint32_t)0x00000040)  /*!< Master update interrupt flag */

/******************** Master Timer Interrupt clear register *******************/
#define HRTIM_MICR_MCMP1    ((uint32_t)0x00000001)  /*!< Master compare 1 interrupt flag clear */
#define HRTIM_MICR_MCMP2    ((uint32_t)0x00000002)  /*!< Master compare 2 interrupt flag clear */
#define HRTIM_MICR_MCMP3    ((uint32_t)0x00000004)  /*!< Master compare 3 interrupt flag clear */
#define HRTIM_MICR_MCMP4    ((uint32_t)0x00000008)  /*!< Master compare 4 interrupt flag clear */
#define HRTIM_MICR_MREP     ((uint32_t)0x00000010)  /*!< Master Repetition interrupt flag clear */
#define HRTIM_MICR_SYNC     ((uint32_t)0x00000020)  /*!< Synchronization input interrupt flag clear */
#define HRTIM_MICR_MUPD     ((uint32_t)0x00000040)  /*!< Master update interrupt flag clear */

/******************** Master Timer DMA/Interrupt enable register **************/
#define HRTIM_MDIER_MCMP1IE    ((uint32_t)0x00000001)  /*!< Master compare 1 interrupt enable */
#define HRTIM_MDIER_MCMP2IE    ((uint32_t)0x00000002)  /*!< Master compare 2 interrupt enable */
#define HRTIM_MDIER_MCMP3IE    ((uint32_t)0x00000004)  /*!< Master compare 3 interrupt enable */
#define HRTIM_MDIER_MCMP4IE    ((uint32_t)0x00000008)  /*!< Master compare 4 interrupt enable */
#define HRTIM_MDIER_MREPIE     ((uint32_t)0x00000010)  /*!< Master Repetition interrupt enable */
#define HRTIM_MDIER_SYNCIE     ((uint32_t)0x00000020)  /*!< Synchronization input interrupt enable */
#define HRTIM_MDIER_MUPDIE     ((uint32_t)0x00000040)  /*!< Master update interrupt enable */

#define HRTIM_MDIER_MCMP1DE    ((uint32_t)0x00010000)  /*!< Master compare 1 DMA enable */
#define HRTIM_MDIER_MCMP2DE    ((uint32_t)0x00020000)  /*!< Master compare 2 DMA enable */
#define HRTIM_MDIER_MCMP3DE    ((uint32_t)0x00040000)  /*!< Master compare 3 DMA enable */
#define HRTIM_MDIER_MCMP4DE    ((uint32_t)0x00080000)  /*!< Master compare 4 DMA enable */
#define HRTIM_MDIER_MREPDE     ((uint32_t)0x00100000)  /*!< Master Repetition DMA enable */
#define HRTIM_MDIER_SYNCDE     ((uint32_t)0x00200000)  /*!< Synchronization input DMA enable */
#define HRTIM_MDIER_MUPDDE     ((uint32_t)0x00400000)  /*!< Master update DMA enable */

/*******************  Bit definition for HRTIM_MCNTR register  ****************/
#define  HRTIM_MCNTR_MCNTR     ((uint32_t)0xFFFFFFFF)       /*!<Counter Value */

/*******************  Bit definition for HRTIM_MPER register  *****************/
#define  HRTIM_MPER_MPER      ((uint32_t)0xFFFFFFFF)        /*!< Period Value */

/*******************  Bit definition for HRTIM_MREP register  *****************/
#define  HRTIM_MREP_MREP     ((uint32_t)0xFFFFFFFF)        /*!<Repetition Value */

/*******************  Bit definition for HRTIM_MCMP1R register  *****************/
#define  HRTIM_MCMP1R_MCMP1R     ((uint32_t)0xFFFFFFFF)     /*!<Compare Value */

/*******************  Bit definition for HRTIM_MCMP2R register  *****************/
#define  HRTIM_MCMP1R_MCMP2R     ((uint32_t)0xFFFFFFFF)     /*!<Compare Value */

/*******************  Bit definition for HRTIM_MCMP3R register  *****************/
#define  HRTIM_MCMP1R_MCMP3R     ((uint32_t)0xFFFFFFFF)     /*!<Compare Value */

/*******************  Bit definition for HRTIM_MCMP4R register  *****************/
#define  HRTIM_MCMP1R_MCMP4R     ((uint32_t)0xFFFFFFFF)     /*!<Compare Value */

/******************** Slave control register **********************************/
#define HRTIM_TIMCR_CK_PSC      ((uint32_t)0x00000007) /*!< Slave prescaler mask*/
#define HRTIM_TIMCR_CK_PSC_0    ((uint32_t)0x00000001) /*!< prescaler bit 0 */
#define HRTIM_TIMCR_CK_PSC_1    ((uint32_t)0x00000002) /*!< prescaler bit 1 */
#define HRTIM_TIMCR_CK_PSC_2    ((uint32_t)0x00000004) /*!< prescaler bit 2 */

#define HRTIM_TIMCR_CONT        ((uint32_t)0x00000008) /*!< Slave continuous mode */
#define HRTIM_TIMCR_RETRIG      ((uint32_t)0x00000010) /*!< Slave Retrigreable mode */
#define HRTIM_TIMCR_HALF        ((uint32_t)0x00000020) /*!< Slave Half mode */
#define HRTIM_TIMCR_PSHPLL      ((uint32_t)0x00000040) /*!< Slave push-pull mode */

#define HRTIM_TIMCR_SYNCRST     ((uint32_t)0x00000400) /*!< Slave synchronization resets */
#define HRTIM_TIMCR_SYNCSTRT    ((uint32_t)0x00000800) /*!< Slave synchronization starts */

#define HRTIM_TIMCR_DELCMP2     ((uint32_t)0x00003000) /*!< Slave delayed comparator 2 mode mask */
#define HRTIM_TIMCR_DELCMP2_0   ((uint32_t)0x00001000) /*!< Slave delayed comparator 2 bit 0 */
#define HRTIM_TIMCR_DELCMP2_1   ((uint32_t)0x00002000) /*!< Slave delayed comparator 2 bit 1 */
#define HRTIM_TIMCR_DELCMP4     ((uint32_t)0x0000C000) /*!< Slave delayed comparator 4 mode mask */
#define HRTIM_TIMCR_DELCMP4_0   ((uint32_t)0x00004000) /*!< Slave delayed comparator 4 bit 0 */
#define HRTIM_TIMCR_DELCMP4_1   ((uint32_t)0x00008000) /*!< Slave delayed comparator 4 bit 1 */

#define HRTIM_TIMCR_TREPU       ((uint32_t)0x00020000) /*!< Slave repetition update */
#define HRTIM_TIMCR_TRSTU       ((uint32_t)0x00040000) /*!< Slave reset update */
#define HRTIM_TIMCR_TAU         ((uint32_t)0x00080000) /*!< Slave Timer A update reserved for TIM A */
#define HRTIM_TIMCR_TBU         ((uint32_t)0x00100000) /*!< Slave Timer B update reserved for TIM B */
#define HRTIM_TIMCR_TCU         ((uint32_t)0x00200000) /*!< Slave Timer C update reserved for TIM C */
#define HRTIM_TIMCR_TDU         ((uint32_t)0x00400000) /*!< Slave Timer D update reserved for TIM D */
#define HRTIM_TIMCR_TEU         ((uint32_t)0x00800000) /*!< Slave Timer E update reserved for TIM E */
#define HRTIM_TIMCR_MSTU        ((uint32_t)0x01000000) /*!< Master Update */

#define HRTIM_TIMCR_DACSYNC    ((uint32_t)0x06000000)   /*!< DAC synchronization mask */
#define HRTIM_TIMCR_DACSYNC_0  ((uint32_t)0x02000000)   /*!< DAC synchronization bit 0 */
#define HRTIM_TIMCR_DACSYNC_1  ((uint32_t)0x04000000)   /*!< DAC synchronization bit 1 */
#define HRTIM_TIMCR_PREEN      ((uint32_t)0x08000000)   /*!< Slave preload enable */

#define HRTIM_TIMCR_UPDGAT     ((uint32_t)0xF0000000)   /*!< Slave update gating mask */
#define HRTIM_TIMCR_UPDGAT_0   ((uint32_t)0x10000000)   /*!< Update gating bit 0 */
#define HRTIM_TIMCR_UPDGAT_1   ((uint32_t)0x20000000)   /*!< Update gating bit 1 */
#define HRTIM_TIMCR_UPDGAT_2   ((uint32_t)0x40000000)   /*!< Update gating bit 2 */
#define HRTIM_TIMCR_UPDGAT_3   ((uint32_t)0x80000000)   /*!< Update gating bit 3 */

/******************** Slave Interrupt status register **************************/
#define HRTIM_TIMISR_CMP1       ((uint32_t)0x00000001)   /*!< Slave compare 1 interrupt flag */
#define HRTIM_TIMISR_CMP2       ((uint32_t)0x00000002)   /*!< Slave compare 2 interrupt flag */
#define HRTIM_TIMISR_CMP3       ((uint32_t)0x00000004)   /*!< Slave compare 3 interrupt flag */
#define HRTIM_TIMISR_CMP4       ((uint32_t)0x00000008)   /*!< Slave compare 4 interrupt flag */
#define HRTIM_TIMISR_REP        ((uint32_t)0x00000010)   /*!< Slave repetition interrupt flag */
#define HRTIM_TIMISR_UPD        ((uint32_t)0x00000040)   /*!< Slave update interrupt flag */
#define HRTIM_TIMISR_CPT1       ((uint32_t)0x00000080)   /*!< Slave capture 1 interrupt flag */
#define HRTIM_TIMISR_CPT2       ((uint32_t)0x00000100)   /*!< Slave capture 2 interrupt flag */
#define HRTIM_TIMISR_SET1       ((uint32_t)0x00000200)   /*!< Slave output 1 set interrupt flag */
#define HRTIM_TIMISR_RST1       ((uint32_t)0x00000400)   /*!< Slave output 1 reset interrupt flag */
#define HRTIM_TIMISR_SET2       ((uint32_t)0x00000800)   /*!< Slave output 2 set interrupt flag */
#define HRTIM_TIMISR_RST2       ((uint32_t)0x00001000)   /*!< Slave output 2 reset interrupt flag */
#define HRTIM_TIMISR_RST        ((uint32_t)0x00002000)   /*!< Slave reset interrupt flag */
#define HRTIM_TIMISR_DLYPRT     ((uint32_t)0x00004000)   /*!< Slave output 1 delay protection interrupt flag */
#define HRTIM_TIMISR_CPPSTAT    ((uint32_t)0x00010000)   /*!< Slave current push-pull flag */
#define HRTIM_TIMISR_IPPSTAT    ((uint32_t)0x00020000)   /*!< Slave idle push-pull flag */
#define HRTIM_TIMISR_O1STAT     ((uint32_t)0x00040000)   /*!< Slave output 1 state flag */
#define HRTIM_TIMISR_O2STAT     ((uint32_t)0x00080000)   /*!< Slave output 2 state flag */
#define HRTIM_TIMISR_O1CPY      ((uint32_t)0x00100000)   /*!< Slave output 1 copy flag */
#define HRTIM_TIMISR_O2CPY      ((uint32_t)0x00200000)   /*!< Slave output 2 copy flag */

/******************** Slave Interrupt clear register **************************/
#define HRTIM_TIMICR_CMP1C       ((uint32_t)0x00000001)   /*!< Slave compare 1 clear flag */
#define HRTIM_TIMICR_CMP2C       ((uint32_t)0x00000002)   /*!< Slave compare 2 clear flag */
#define HRTIM_TIMICR_CMP3C       ((uint32_t)0x00000004)   /*!< Slave compare 3 clear flag */
#define HRTIM_TIMICR_CMP4C       ((uint32_t)0x00000008)   /*!< Slave compare 4 clear flag */
#define HRTIM_TIMICR_REPC        ((uint32_t)0x00000010)   /*!< Slave repetition clear flag */
#define HRTIM_TIMICR_UPDC        ((uint32_t)0x00000040)   /*!< Slave update clear flag */
#define HRTIM_TIMICR_CPT1C       ((uint32_t)0x00000080)   /*!< Slave capture 1 clear flag */
#define HRTIM_TIMICR_CPT2C       ((uint32_t)0x00000100)   /*!< Slave capture 2 clear flag */
#define HRTIM_TIMICR_SET1C       ((uint32_t)0x00000200)   /*!< Slave output 1 set clear flag */
#define HRTIM_TIMICR_RST1C       ((uint32_t)0x00000400)   /*!< Slave output 1 reset clear flag */
#define HRTIM_TIMICR_SET2C       ((uint32_t)0x00000800)   /*!< Slave output 2 set clear flag */
#define HRTIM_TIMICR_RST2C       ((uint32_t)0x00001000)   /*!< Slave output 2 reset clear flag */
#define HRTIM_TIMICR_RSTC        ((uint32_t)0x00002000)   /*!< Slave reset clear flag */
#define HRTIM_TIMICR_DLYPRT1C    ((uint32_t)0x00004000)   /*!< Slave output 1 delay protection clear flag */
#define HRTIM_TIMICR_DLYPRT2C    ((uint32_t)0x00008000)   /*!< Slave output 2 delay protection clear flag */

/******************** Slave DMA/Interrupt enable register *********************/
#define HRTIM_TIMDIER_CMP1IE       ((uint32_t)0x00000001)   /*!< Slave compare 1 interrupt enable */
#define HRTIM_TIMDIER_CMP2IE       ((uint32_t)0x00000002)   /*!< Slave compare 2 interrupt enable */
#define HRTIM_TIMDIER_CMP3IE       ((uint32_t)0x00000004)   /*!< Slave compare 3 interrupt enable */
#define HRTIM_TIMDIER_CMP4IE       ((uint32_t)0x00000008)   /*!< Slave compare 4 interrupt enable */
#define HRTIM_TIMDIER_REPIE        ((uint32_t)0x00000010)   /*!< Slave repetition interrupt enable */
#define HRTIM_TIMDIER_UPDIE        ((uint32_t)0x00000040)   /*!< Slave update interrupt enable */
#define HRTIM_TIMDIER_CPT1IE       ((uint32_t)0x00000080)   /*!< Slave capture 1 interrupt enable */
#define HRTIM_TIMDIER_CPT2IE       ((uint32_t)0x00000100)   /*!< Slave capture 2 interrupt enable */
#define HRTIM_TIMDIER_SET1IE       ((uint32_t)0x00000200)   /*!< Slave output 1 set interrupt enable */
#define HRTIM_TIMDIER_RST1IE       ((uint32_t)0x00000400)   /*!< Slave output 1 reset interrupt enable */
#define HRTIM_TIMDIER_SET2IE       ((uint32_t)0x00000800)   /*!< Slave output 2 set interrupt enable */
#define HRTIM_TIMDIER_RST2IE       ((uint32_t)0x00001000)   /*!< Slave output 2 reset interrupt enable */
#define HRTIM_TIMDIER_RSTIE        ((uint32_t)0x00002000)   /*!< Slave reset interrupt enable */
#define HRTIM_TIMDIER_DLYPRTIE     ((uint32_t)0x00004000)   /*!< Slave delay protection interrupt enable */

#define HRTIM_TIMDIER_CMP1DE       ((uint32_t)0x00010000)   /*!< Slave compare 1 request enable */
#define HRTIM_TIMDIER_CMP2DE       ((uint32_t)0x00020000)   /*!< Slave compare 2 request enable */
#define HRTIM_TIMDIER_CMP3DE       ((uint32_t)0x00040000)   /*!< Slave compare 3 request enable */
#define HRTIM_TIMDIER_CMP4DE       ((uint32_t)0x00080000)   /*!< Slave compare 4 request enable */
#define HRTIM_TIMDIER_REPDE        ((uint32_t)0x00100000)   /*!< Slave repetition request enable */
#define HRTIM_TIMDIER_UPDDE        ((uint32_t)0x00400000)   /*!< Slave update request enable */
#define HRTIM_TIMDIER_CPT1DE       ((uint32_t)0x00800000)   /*!< Slave capture 1 request enable */
#define HRTIM_TIMDIER_CPT2DE       ((uint32_t)0x01000000)   /*!< Slave capture 2 request enable */
#define HRTIM_TIMDIER_SET1DE       ((uint32_t)0x02000000)   /*!< Slave output 1 set request enable */
#define HRTIM_TIMDIER_RST1DE       ((uint32_t)0x04000000)   /*!< Slave output 1 reset request enable */
#define HRTIM_TIMDIER_SET2DE       ((uint32_t)0x08000000)   /*!< Slave output 2 set request enable */
#define HRTIM_TIMDIER_RST2DE       ((uint32_t)0x10000000)   /*!< Slave output 2 reset request enable */
#define HRTIM_TIMDIER_RSTDE        ((uint32_t)0x20000000)   /*!< Slave reset request enable */
#define HRTIM_TIMDIER_DLYPRTDE     ((uint32_t)0x40000000)   /*!< Slave delay protection request enable */

/******************  Bit definition for HRTIM_CNTR register  ****************/
#define  HRTIM_CNTR_CNTR      ((uint32_t)0xFFFFFFFF)       /*!< Counter Value */

/*******************  Bit definition for HRTIM_PER register  *****************/
#define  HRTIM_PER_PER       ((uint32_t)0xFFFFFFFF)        /*!< Period Value */

/*******************  Bit definition for HRTIM_REP register  *****************/
#define  HRTIM_REP_REP      ((uint32_t)0xFFFFFFFF)        /*!< Repetition Value */

/*******************  Bit definition for HRTIM_CMP1R register  *****************/
#define  HRTIM_CMP1R_CMP1R     ((uint32_t)0xFFFFFFFF)     /*!< Compare Value */

/*******************  Bit definition for HRTIM_CMP1CR register  *****************/
#define  HRTIM_CMP1CR_CMP1CR     ((uint32_t)0xFFFFFFFF)     /*!< Compare Value */

/*******************  Bit definition for HRTIM_CMP2R register  *****************/
#define  HRTIM_CMP2R_CMP2R     ((uint32_t)0xFFFFFFFF)     /*!< Compare Value */

/*******************  Bit definition for HRTIM_CMP3R register  *****************/
#define  HRTIM_CMP3R_CMP3R     ((uint32_t)0xFFFFFFFF)     /*!< Compare Value */

/*******************  Bit definition for HRTIM_CMP4R register  *****************/
#define  HRTIM_CMP4R_CMP4R     ((uint32_t)0xFFFFFFFF)     /*!< Compare Value */

/*******************  Bit definition for HRTIM_CPT1R register  ****************/
#define  HRTIM_CPT1R_CPT1R     ((uint32_t)0xFFFFFFFF)     /*!< Capture Value */

/*******************  Bit definition for HRTIM_CPT2R register  ****************/
#define  HRTIM_CPT2R_CPT2R     ((uint32_t)0xFFFFFFFF)     /*!< Capture Value */

/******************** Bit definition for Slave Deadtime register **************/
#define HRTIM_DTR_DTR           ((uint32_t)0x000001FF)    /*!< Dead time rising value */
#define HRTIM_DTR_DTR_0         ((uint32_t)0x00000001)    /*!< Dead time rising bit 0 */
#define HRTIM_DTR_DTR_1         ((uint32_t)0x00000002)    /*!< Dead time rising bit 1 */
#define HRTIM_DTR_DTR_2         ((uint32_t)0x00000004)    /*!< Dead time rising bit 2 */
#define HRTIM_DTR_DTR_3         ((uint32_t)0x00000008)    /*!< Dead time rising bit 3 */
#define HRTIM_DTR_DTR_4         ((uint32_t)0x00000010)    /*!< Dead time rising bit 4 */
#define HRTIM_DTR_DTR_5         ((uint32_t)0x00000020)    /*!< Dead time rising bit 5 */
#define HRTIM_DTR_DTR_6         ((uint32_t)0x00000040)    /*!< Dead time rising bit 6 */
#define HRTIM_DTR_DTR_7         ((uint32_t)0x00000080)    /*!< Dead time rising bit 7 */
#define HRTIM_DTR_DTR_8         ((uint32_t)0x00000100)    /*!< Dead time rising bit 8 */
#define HRTIM_DTR_SDTR          ((uint32_t)0x00000200)    /*!< Sign dead time rising value */
#define HRTIM_DTR_DTPRSC        ((uint32_t)0x00001C00)    /*!< Dead time prescaler */
#define HRTIM_DTR_DTPRSC_0      ((uint32_t)0x00000400)    /*!< Dead time prescaler bit 0 */
#define HRTIM_DTR_DTPRSC_1      ((uint32_t)0x00000800)    /*!< Dead time prescaler bit 1 */
#define HRTIM_DTR_DTPRSC_2      ((uint32_t)0x00001000)    /*!< Dead time prescaler bit 2 */
#define HRTIM_DTR_DTRSLK        ((uint32_t)0x00004000)    /*!< Dead time rising sign lock */
#define HRTIM_DTR_DTRLK         ((uint32_t)0x00008000)    /*!< Dead time rising lock */
#define HRTIM_DTR_DTF           ((uint32_t)0x01FF0000)    /*!< Dead time falling value */
#define HRTIM_DTR_DTF_0         ((uint32_t)0x00010000)    /*!< Dead time falling bit 0 */
#define HRTIM_DTR_DTF_1         ((uint32_t)0x00020000)    /*!< Dead time falling bit 1 */
#define HRTIM_DTR_DTF_2         ((uint32_t)0x00040000)    /*!< Dead time falling bit 2 */
#define HRTIM_DTR_DTF_3         ((uint32_t)0x00080000)    /*!< Dead time falling bit 3 */
#define HRTIM_DTR_DTF_4         ((uint32_t)0x00100000)    /*!< Dead time falling bit 4 */
#define HRTIM_DTR_DTF_5         ((uint32_t)0x00200000)    /*!< Dead time falling bit 5 */
#define HRTIM_DTR_DTF_6         ((uint32_t)0x00400000)    /*!< Dead time falling bit 6 */
#define HRTIM_DTR_DTF_7         ((uint32_t)0x00800000)    /*!< Dead time falling bit 7 */
#define HRTIM_DTR_DTF_8         ((uint32_t)0x01000000)    /*!< Dead time falling bit 8 */
#define HRTIM_DTR_SDTF          ((uint32_t)0x02000000)    /*!< Sign dead time falling value */
#define HRTIM_DTR_DTFSLK        ((uint32_t)0x40000000)    /*!< Dead time falling sign lock */
#define HRTIM_DTR_DTFLK         ((uint32_t)0x80000000)    /*!< Dead time falling lock */

/**** Bit definition for Slave Output 1 set register **************************/
#define HRTIM_SET1R_SST         ((uint32_t)0x00000001)    /*!< software set trigger */
#define HRTIM_SET1R_RESYNC      ((uint32_t)0x00000002)    /*!< Timer A resynchronization */
#define HRTIM_SET1R_PER         ((uint32_t)0x00000004)    /*!< Timer A period */
#define HRTIM_SET1R_CMP1        ((uint32_t)0x00000008)    /*!< Timer A compare 1 */
#define HRTIM_SET1R_CMP2        ((uint32_t)0x00000010)    /*!< Timer A compare 2 */
#define HRTIM_SET1R_CMP3        ((uint32_t)0x00000020)    /*!< Timer A compare 3 */
#define HRTIM_SET1R_CMP4        ((uint32_t)0x00000040)    /*!< Timer A compare 4 */

#define HRTIM_SET1R_MSTPER      ((uint32_t)0x00000080)    /*!< Master period */
#define HRTIM_SET1R_MSTCMP1     ((uint32_t)0x00000100)    /*!< Master compare 1 */
#define HRTIM_SET1R_MSTCMP2     ((uint32_t)0x00000200)    /*!< Master compare 2 */
#define HRTIM_SET1R_MSTCMP3     ((uint32_t)0x00000400)    /*!< Master compare 3 */
#define HRTIM_SET1R_MSTCMP4     ((uint32_t)0x00000800)    /*!< Master compare 4 */

#define HRTIM_SET1R_TIMEVNT1   ((uint32_t)0x00001000)    /*!< Timer event 1 */
#define HRTIM_SET1R_TIMEVNT2   ((uint32_t)0x00002000)    /*!< Timer event 2 */
#define HRTIM_SET1R_TIMEVNT3   ((uint32_t)0x00004000)    /*!< Timer event 3 */
#define HRTIM_SET1R_TIMEVNT4   ((uint32_t)0x00008000)    /*!< Timer event 4 */
#define HRTIM_SET1R_TIMEVNT5   ((uint32_t)0x00010000)    /*!< Timer event 5 */
#define HRTIM_SET1R_TIMEVNT6   ((uint32_t)0x00020000)    /*!< Timer event 6 */
#define HRTIM_SET1R_TIMEVNT7   ((uint32_t)0x00040000)    /*!< Timer event 7 */
#define HRTIM_SET1R_TIMEVNT8   ((uint32_t)0x00080000)    /*!< Timer event 8 */
#define HRTIM_SET1R_TIMEVNT9   ((uint32_t)0x00100000)    /*!< Timer event 9 */

#define HRTIM_SET1R_EXTVNT1   ((uint32_t)0x00200000)    /*!< External event 1 */
#define HRTIM_SET1R_EXTVNT2   ((uint32_t)0x00400000)    /*!< External event 2 */
#define HRTIM_SET1R_EXTVNT3   ((uint32_t)0x00800000)    /*!< External event 3 */
#define HRTIM_SET1R_EXTVNT4   ((uint32_t)0x01000000)    /*!< External event 4 */
#define HRTIM_SET1R_EXTVNT5   ((uint32_t)0x02000000)    /*!< External event 5 */
#define HRTIM_SET1R_EXTVNT6   ((uint32_t)0x04000000)    /*!< External event 6 */
#define HRTIM_SET1R_EXTVNT7   ((uint32_t)0x08000000)    /*!< External event 7 */
#define HRTIM_SET1R_EXTVNT8   ((uint32_t)0x10000000)    /*!< External event 8 */
#define HRTIM_SET1R_EXTVNT9   ((uint32_t)0x20000000)    /*!< External event 9 */
#define HRTIM_SET1R_EXTVNT10  ((uint32_t)0x40000000)    /*!< External event 10 */

#define HRTIM_SET1R_UPDATE    ((uint32_t)0x80000000)    /*!< Register update (transfer preload to active) */

/**** Bit definition for Slave Output 1 reset register ************************/
#define HRTIM_RST1R_SRT         ((uint32_t)0x00000001)    /*!< software reset trigger */
#define HRTIM_RST1R_RESYNC      ((uint32_t)0x00000002)    /*!< Timer A resynchronization */
#define HRTIM_RST1R_PER         ((uint32_t)0x00000004)    /*!< Timer A period */
#define HRTIM_RST1R_CMP1        ((uint32_t)0x00000008)    /*!< Timer A compare 1 */
#define HRTIM_RST1R_CMP2        ((uint32_t)0x00000010)    /*!< Timer A compare 2 */
#define HRTIM_RST1R_CMP3        ((uint32_t)0x00000020)    /*!< Timer A compare 3 */
#define HRTIM_RST1R_CMP4        ((uint32_t)0x00000040)    /*!< Timer A compare 4 */

#define HRTIM_RST1R_MSTPER      ((uint32_t)0x00000080)    /*!< Master period */
#define HRTIM_RST1R_MSTCMP1     ((uint32_t)0x00000100)    /*!< Master compare 1 */
#define HRTIM_RST1R_MSTCMP2     ((uint32_t)0x00000200)    /*!< Master compare 2 */
#define HRTIM_RST1R_MSTCMP3     ((uint32_t)0x00000400)    /*!< Master compare 3 */
#define HRTIM_RST1R_MSTCMP4     ((uint32_t)0x00000800)    /*!< Master compare 4 */

#define HRTIM_RST1R_TIMEVNT1   ((uint32_t)0x00001000)    /*!< Timer event 1 */
#define HRTIM_RST1R_TIMEVNT2   ((uint32_t)0x00002000)    /*!< Timer event 2 */
#define HRTIM_RST1R_TIMEVNT3   ((uint32_t)0x00004000)    /*!< Timer event 3 */
#define HRTIM_RST1R_TIMEVNT4   ((uint32_t)0x00008000)    /*!< Timer event 4 */
#define HRTIM_RST1R_TIMEVNT5   ((uint32_t)0x00010000)    /*!< Timer event 5 */
#define HRTIM_RST1R_TIMEVNT6   ((uint32_t)0x00020000)    /*!< Timer event 6 */
#define HRTIM_RST1R_TIMEVNT7   ((uint32_t)0x00040000)    /*!< Timer event 7 */
#define HRTIM_RST1R_TIMEVNT8   ((uint32_t)0x00080000)    /*!< Timer event 8 */
#define HRTIM_RST1R_TIMEVNT9   ((uint32_t)0x00100000)    /*!< Timer event 9 */

#define HRTIM_RST1R_EXTVNT1   ((uint32_t)0x00200000)    /*!< External event 1 */
#define HRTIM_RST1R_EXTVNT2   ((uint32_t)0x00400000)    /*!< External event 2 */
#define HRTIM_RST1R_EXTVNT3   ((uint32_t)0x00800000)    /*!< External event 3 */
#define HRTIM_RST1R_EXTVNT4   ((uint32_t)0x01000000)    /*!< External event 4 */
#define HRTIM_RST1R_EXTVNT5   ((uint32_t)0x02000000)    /*!< External event 5 */
#define HRTIM_RST1R_EXTVNT6   ((uint32_t)0x04000000)    /*!< External event 6 */
#define HRTIM_RST1R_EXTVNT7   ((uint32_t)0x08000000)    /*!< External event 7 */
#define HRTIM_RST1R_EXTVNT8   ((uint32_t)0x10000000)    /*!< External event 8 */
#define HRTIM_RST1R_EXTVNT9   ((uint32_t)0x20000000)    /*!< External event 9 */
#define HRTIM_RST1R_EXTVNT10  ((uint32_t)0x40000000)    /*!< External event 10 */

#define HRTIM_RST1R_UPDATE    ((uint32_t)0x80000000)    /*!< Register update (transfer preload to active) */


/**** Bit definition for Slave Output 2 set register **************************/
#define HRTIM_SET2R_SST         ((uint32_t)0x00000001)    /*!< software set trigger */
#define HRTIM_SET2R_RESYNC      ((uint32_t)0x00000002)    /*!< Timer A resynchronization */
#define HRTIM_SET2R_PER         ((uint32_t)0x00000004)    /*!< Timer A period */
#define HRTIM_SET2R_CMP1        ((uint32_t)0x00000008)    /*!< Timer A compare 1 */
#define HRTIM_SET2R_CMP2        ((uint32_t)0x00000010)    /*!< Timer A compare 2 */
#define HRTIM_SET2R_CMP3        ((uint32_t)0x00000020)    /*!< Timer A compare 3 */
#define HRTIM_SET2R_CMP4        ((uint32_t)0x00000040)    /*!< Timer A compare 4 */

#define HRTIM_SET2R_MSTPER      ((uint32_t)0x00000080)    /*!< Master period */
#define HRTIM_SET2R_MSTCMP1     ((uint32_t)0x00000100)    /*!< Master compare 1 */
#define HRTIM_SET2R_MSTCMP2     ((uint32_t)0x00000200)    /*!< Master compare 2 */
#define HRTIM_SET2R_MSTCMP3     ((uint32_t)0x00000400)    /*!< Master compare 3 */
#define HRTIM_SET2R_MSTCMP4     ((uint32_t)0x00000800)    /*!< Master compare 4 */

#define HRTIM_SET2R_TIMEVNT1   ((uint32_t)0x00001000)    /*!< Timer event 1 */
#define HRTIM_SET2R_TIMEVNT2   ((uint32_t)0x00002000)    /*!< Timer event 2 */
#define HRTIM_SET2R_TIMEVNT3   ((uint32_t)0x00004000)    /*!< Timer event 3 */
#define HRTIM_SET2R_TIMEVNT4   ((uint32_t)0x00008000)    /*!< Timer event 4 */
#define HRTIM_SET2R_TIMEVNT5   ((uint32_t)0x00010000)    /*!< Timer event 5 */
#define HRTIM_SET2R_TIMEVNT6   ((uint32_t)0x00020000)    /*!< Timer event 6 */
#define HRTIM_SET2R_TIMEVNT7   ((uint32_t)0x00040000)    /*!< Timer event 7 */
#define HRTIM_SET2R_TIMEVNT8   ((uint32_t)0x00080000)    /*!< Timer event 8 */
#define HRTIM_SET2R_TIMEVNT9   ((uint32_t)0x00100000)    /*!< Timer event 9 */

#define HRTIM_SET2R_EXTVNT1   ((uint32_t)0x00200000)    /*!< External event 1 */
#define HRTIM_SET2R_EXTVNT2   ((uint32_t)0x00400000)    /*!< External event 2 */
#define HRTIM_SET2R_EXTVNT3   ((uint32_t)0x00800000)    /*!< External event 3 */
#define HRTIM_SET2R_EXTVNT4   ((uint32_t)0x01000000)    /*!< External event 4 */
#define HRTIM_SET2R_EXTVNT5   ((uint32_t)0x02000000)    /*!< External event 5 */
#define HRTIM_SET2R_EXTVNT6   ((uint32_t)0x04000000)    /*!< External event 6 */
#define HRTIM_SET2R_EXTVNT7   ((uint32_t)0x08000000)    /*!< External event 7 */
#define HRTIM_SET2R_EXTVNT8   ((uint32_t)0x10000000)    /*!< External event 8 */
#define HRTIM_SET2R_EXTVNT9   ((uint32_t)0x20000000)    /*!< External event 9 */
#define HRTIM_SET2R_EXTVNT10  ((uint32_t)0x40000000)    /*!< External event 10 */

#define HRTIM_SET2R_UPDATE    ((uint32_t)0x80000000)    /*!< Register update (transfer preload to active) */

/**** Bit definition for Slave Output 2 reset register ************************/
#define HRTIM_RST2R_SRT         ((uint32_t)0x00000001)    /*!< software reset trigger */
#define HRTIM_RST2R_RESYNC      ((uint32_t)0x00000002)    /*!< Timer A resynchronization */
#define HRTIM_RST2R_PER         ((uint32_t)0x00000004)    /*!< Timer A period */
#define HRTIM_RST2R_CMP1        ((uint32_t)0x00000008)    /*!< Timer A compare 1 */
#define HRTIM_RST2R_CMP2        ((uint32_t)0x00000010)    /*!< Timer A compare 2 */
#define HRTIM_RST2R_CMP3        ((uint32_t)0x00000020)    /*!< Timer A compare 3 */
#define HRTIM_RST2R_CMP4        ((uint32_t)0x00000040)    /*!< Timer A compare 4 */

#define HRTIM_RST2R_MSTPER      ((uint32_t)0x00000080)    /*!< Master period */
#define HRTIM_RST2R_MSTCMP1     ((uint32_t)0x00000100)    /*!< Master compare 1 */
#define HRTIM_RST2R_MSTCMP2     ((uint32_t)0x00000200)    /*!< Master compare 2 */
#define HRTIM_RST2R_MSTCMP3     ((uint32_t)0x00000400)    /*!< Master compare 3 */
#define HRTIM_RST2R_MSTCMP4     ((uint32_t)0x00000800)    /*!< Master compare 4 */

#define HRTIM_RST2R_TIMEVNT1   ((uint32_t)0x00001000)    /*!< Timer event 1 */
#define HRTIM_RST2R_TIMEVNT2   ((uint32_t)0x00002000)    /*!< Timer event 2 */
#define HRTIM_RST2R_TIMEVNT3   ((uint32_t)0x00004000)    /*!< Timer event 3 */
#define HRTIM_RST2R_TIMEVNT4   ((uint32_t)0x00008000)    /*!< Timer event 4 */
#define HRTIM_RST2R_TIMEVNT5   ((uint32_t)0x00010000)    /*!< Timer event 5 */
#define HRTIM_RST2R_TIMEVNT6   ((uint32_t)0x00020000)    /*!< Timer event 6 */
#define HRTIM_RST2R_TIMEVNT7   ((uint32_t)0x00040000)    /*!< Timer event 7 */
#define HRTIM_RST2R_TIMEVNT8   ((uint32_t)0x00080000)    /*!< Timer event 8 */
#define HRTIM_RST2R_TIMEVNT9   ((uint32_t)0x00100000)    /*!< Timer event 9 */

#define HRTIM_RST2R_EXTVNT1   ((uint32_t)0x00200000)    /*!< External event 1 */
#define HRTIM_RST2R_EXTVNT2   ((uint32_t)0x00400000)    /*!< External event 2 */
#define HRTIM_RST2R_EXTVNT3   ((uint32_t)0x00800000)    /*!< External event 3 */
#define HRTIM_RST2R_EXTVNT4   ((uint32_t)0x01000000)    /*!< External event 4 */
#define HRTIM_RST2R_EXTVNT5   ((uint32_t)0x02000000)    /*!< External event 5 */
#define HRTIM_RST2R_EXTVNT6   ((uint32_t)0x04000000)    /*!< External event 6 */
#define HRTIM_RST2R_EXTVNT7   ((uint32_t)0x08000000)    /*!< External event 7 */
#define HRTIM_RST2R_EXTVNT8   ((uint32_t)0x10000000)    /*!< External event 8 */
#define HRTIM_RST2R_EXTVNT9   ((uint32_t)0x20000000)    /*!< External event 9 */
#define HRTIM_RST2R_EXTVNT10  ((uint32_t)0x40000000)    /*!< External event 10 */

#define HRTIM_RST2R_UPDATE    ((uint32_t)0x80000000)    /*!< Register update (transfer preload to active) */

/**** Bit definition for Slave external event filtering  register 1 ***********/
#define HRTIM_EEFR1_EE1LTCH    ((uint32_t)0x00000001)    /*!< External Event 1 latch */
#define HRTIM_EEFR1_EE1FLTR    ((uint32_t)0x0000001E)    /*!< External Event 1 filter mask */
#define HRTIM_EEFR1_EE1FLTR_0  ((uint32_t)0x00000002)    /*!< External Event 1 bit 0  */
#define HRTIM_EEFR1_EE1FLTR_1  ((uint32_t)0x00000004)    /*!< External Event 1 bit 1*/
#define HRTIM_EEFR1_EE1FLTR_2  ((uint32_t)0x00000008)    /*!< External Event 1 bit 2 */
#define HRTIM_EEFR1_EE1FLTR_3  ((uint32_t)0x00000010)    /*!< External Event 1 bit 3 */

#define HRTIM_EEFR1_EE2LTCH    ((uint32_t)0x00000040)    /*!< External Event 2 latch */
#define HRTIM_EEFR1_EE2FLTR    ((uint32_t)0x00000780)    /*!< External Event 2 filter mask */
#define HRTIM_EEFR1_EE2FLTR_0  ((uint32_t)0x00000080)    /*!< External Event 2 bit 0  */
#define HRTIM_EEFR1_EE2FLTR_1  ((uint32_t)0x00000100)    /*!< External Event 2 bit 1*/
#define HRTIM_EEFR1_EE2FLTR_2  ((uint32_t)0x00000200)    /*!< External Event 2 bit 2 */
#define HRTIM_EEFR1_EE2FLTR_3  ((uint32_t)0x00000400)    /*!< External Event 2 bit 3 */

#define HRTIM_EEFR1_EE3LTCH    ((uint32_t)0x00001000)    /*!< External Event 3 latch */
#define HRTIM_EEFR1_EE3FLTR    ((uint32_t)0x0001E000)    /*!< External Event 3 filter mask */
#define HRTIM_EEFR1_EE3FLTR_0  ((uint32_t)0x00002000)    /*!< External Event 3 bit 0  */
#define HRTIM_EEFR1_EE3FLTR_1  ((uint32_t)0x00004000)    /*!< External Event 3 bit 1*/
#define HRTIM_EEFR1_EE3FLTR_2  ((uint32_t)0x00008000)    /*!< External Event 3 bit 2 */
#define HRTIM_EEFR1_EE3FLTR_3  ((uint32_t)0x00010000)    /*!< External Event 3 bit 3 */

#define HRTIM_EEFR1_EE4LTCH    ((uint32_t)0x00040000)    /*!< External Event 4 latch */
#define HRTIM_EEFR1_EE4FLTR    ((uint32_t)0x00780000)    /*!< External Event 4 filter mask */
#define HRTIM_EEFR1_EE4FLTR_0  ((uint32_t)0x00080000)    /*!< External Event 4 bit 0  */
#define HRTIM_EEFR1_EE4FLTR_1  ((uint32_t)0x00100000)    /*!< External Event 4 bit 1*/
#define HRTIM_EEFR1_EE4FLTR_2  ((uint32_t)0x00200000)    /*!< External Event 4 bit 2 */
#define HRTIM_EEFR1_EE4FLTR_3  ((uint32_t)0x00400000)    /*!< External Event 4 bit 3 */

#define HRTIM_EEFR1_EE5LTCH    ((uint32_t)0x01000000)   /*!< External Event 5 latch */
#define HRTIM_EEFR1_EE5FLTR    ((uint32_t)0x1E000000)    /*!< External Event 5 filter mask */
#define HRTIM_EEFR1_EE5FLTR_0  ((uint32_t)0x02000000)    /*!< External Event 5 bit 0  */
#define HRTIM_EEFR1_EE5FLTR_1  ((uint32_t)0x04000000)    /*!< External Event 5 bit 1*/
#define HRTIM_EEFR1_EE5FLTR_2  ((uint32_t)0x08000000)    /*!< External Event 5 bit 2 */
#define HRTIM_EEFR1_EE5FLTR_3  ((uint32_t)0x10000000)    /*!< External Event 5 bit 3 */

/**** Bit definition for Slave external event filtering  register 2 ***********/
#define HRTIM_EEFR2_EE6LTCH    ((uint32_t)0x00000001)    /*!< External Event 6 latch */
#define HRTIM_EEFR2_EE6FLTR    ((uint32_t)0x0000001E)    /*!< External Event 6 filter mask */
#define HRTIM_EEFR2_EE6FLTR_0  ((uint32_t)0x00000002)    /*!< External Event 6 bit 0  */
#define HRTIM_EEFR2_EE6FLTR_1  ((uint32_t)0x00000004)    /*!< External Event 6 bit 1*/
#define HRTIM_EEFR2_EE6FLTR_2  ((uint32_t)0x00000008)    /*!< External Event 6 bit 2 */
#define HRTIM_EEFR2_EE6FLTR_3  ((uint32_t)0x00000010)    /*!< External Event 6 bit 3 */

#define HRTIM_EEFR2_EE7LTCH    ((uint32_t)0x00000040)    /*!< External Event 7 latch */
#define HRTIM_EEFR2_EE7FLTR    ((uint32_t)0x00000780)    /*!< External Event 7 filter mask */
#define HRTIM_EEFR2_EE7FLTR_0  ((uint32_t)0x00000080)    /*!< External Event 7 bit 0  */
#define HRTIM_EEFR2_EE7FLTR_1  ((uint32_t)0x00000100)    /*!< External Event 7 bit 1*/
#define HRTIM_EEFR2_EE7FLTR_2  ((uint32_t)0x00000200)    /*!< External Event 7 bit 2 */
#define HRTIM_EEFR2_EE7FLTR_3  ((uint32_t)0x00000400)    /*!< External Event 7 bit 3 */

#define HRTIM_EEFR2_EE8LTCH    ((uint32_t)0x00001000)    /*!< External Event 8 latch */
#define HRTIM_EEFR2_EE8FLTR    ((uint32_t)0x0001E000)    /*!< External Event 8 filter mask */
#define HRTIM_EEFR2_EE8FLTR_0  ((uint32_t)0x00002000)    /*!< External Event 8 bit 0  */
#define HRTIM_EEFR2_EE8FLTR_1  ((uint32_t)0x00004000)    /*!< External Event 8 bit 1*/
#define HRTIM_EEFR2_EE8FLTR_2  ((uint32_t)0x00008000)    /*!< External Event 8 bit 2 */
#define HRTIM_EEFR2_EE8FLTR_3  ((uint32_t)0x00010000)    /*!< External Event 8 bit 3 */

#define HRTIM_EEFR2_EE9LTCH    ((uint32_t)0x00040000)    /*!< External Event 9 latch */
#define HRTIM_EEFR2_EE9FLTR    ((uint32_t)0x00780000)    /*!< External Event 9 filter mask */
#define HRTIM_EEFR2_EE9FLTR_0  ((uint32_t)0x00080000)    /*!< External Event 9 bit 0  */
#define HRTIM_EEFR2_EE9FLTR_1  ((uint32_t)0x00100000)    /*!< External Event 9 bit 1*/
#define HRTIM_EEFR2_EE9FLTR_2  ((uint32_t)0x00200000)    /*!< External Event 9 bit 2 */
#define HRTIM_EEFR2_EE9FLTR_3  ((uint32_t)0x00400000)    /*!< External Event 9 bit 3 */

#define HRTIM_EEFR2_EE10LTCH    ((uint32_t)0x01000000)   /*!< External Event 10 latch */
#define HRTIM_EEFR2_EE10FLTR    ((uint32_t)0x1E000000)    /*!< External Event 10 filter mask */
#define HRTIM_EEFR2_EE10FLTR_0  ((uint32_t)0x02000000)    /*!< External Event 10 bit 0  */
#define HRTIM_EEFR2_EE10FLTR_1  ((uint32_t)0x04000000)    /*!< External Event 10 bit 1*/
#define HRTIM_EEFR2_EE10FLTR_2  ((uint32_t)0x08000000)    /*!< External Event 10 bit 2 */
#define HRTIM_EEFR2_EE10FLTR_3  ((uint32_t)0x10000000)    /*!< External Event 10 bit 3 */

/**** Bit definition for Slave Timer reset register ***************************/
#define HRTIM_RSTR_UPDATE     ((uint32_t)0x00000002)   /*!< Timer update */
#define HRTIM_RSTR_CMP2       ((uint32_t)0x00000004)   /*!< Timer compare2 */
#define HRTIM_RSTR_CMP4       ((uint32_t)0x00000008)   /*!< Timer compare4 */

#define HRTIM_RSTR_MSTPER     ((uint32_t)0x00000010)   /*!< Master period */
#define HRTIM_RSTR_MSTCMP1    ((uint32_t)0x00000020)   /*!< Master compare1 */
#define HRTIM_RSTR_MSTCMP2    ((uint32_t)0x00000040)   /*!< Master compare2 */
#define HRTIM_RSTR_MSTCMP3    ((uint32_t)0x00000080)   /*!< Master compare3 */
#define HRTIM_RSTR_MSTCMP4    ((uint32_t)0x00000100)   /*!< Master compare4 */

#define HRTIM_RSTR_EXTEVNT1   ((uint32_t)0x00000200)   /*!< External event 1 */
#define HRTIM_RSTR_EXTEVNT2   ((uint32_t)0x00000400)   /*!< External event 2 */
#define HRTIM_RSTR_EXTEVNT3   ((uint32_t)0x00000800)   /*!< External event 3 */
#define HRTIM_RSTR_EXTEVNT4   ((uint32_t)0x00001000)   /*!< External event 4 */
#define HRTIM_RSTR_EXTEVNT5   ((uint32_t)0x00002000)   /*!< External event 5 */
#define HRTIM_RSTR_EXTEVNT6   ((uint32_t)0x00004000)   /*!< External event 6 */
#define HRTIM_RSTR_EXTEVNT7   ((uint32_t)0x00008000)   /*!< External event 7 */
#define HRTIM_RSTR_EXTEVNT8   ((uint32_t)0x00010000)   /*!< External event 8 */
#define HRTIM_RSTR_EXTEVNT9   ((uint32_t)0x00020000)   /*!< External event 9 */
#define HRTIM_RSTR_EXTEVNT10  ((uint32_t)0x00040000)   /*!< External event 10 */

#define HRTIM_RSTR_TIMBCMP1   ((uint32_t)0x00080000)   /*!< Timer B compare 1 */
#define HRTIM_RSTR_TIMBCMP2   ((uint32_t)0x00100000)   /*!< Timer B compare 2 */
#define HRTIM_RSTR_TIMBCMP4   ((uint32_t)0x00200000)   /*!< Timer B compare 4 */

#define HRTIM_RSTR_TIMCCMP1   ((uint32_t)0x00400000)   /*!< Timer C compare 1 */
#define HRTIM_RSTR_TIMCCMP2   ((uint32_t)0x00800000)   /*!< Timer C compare 2 */
#define HRTIM_RSTR_TIMCCMP4   ((uint32_t)0x01000000)   /*!< Timer C compare 4 */

#define HRTIM_RSTR_TIMDCMP1   ((uint32_t)0x02000000)   /*!< Timer D compare 1 */
#define HRTIM_RSTR_TIMDCMP2   ((uint32_t)0x04000000)   /*!< Timer D compare 2 */
#define HRTIM_RSTR_TIMDCMP4   ((uint32_t)0x08000000)   /*!< Timer D compare 4 */

#define HRTIM_RSTR_TIMECMP1   ((uint32_t)0x10000000)   /*!< Timer E compare 1 */
#define HRTIM_RSTR_TIMECMP2   ((uint32_t)0x20000000)   /*!< Timer E compare 2 */
#define HRTIM_RSTR_TIMECMP4   ((uint32_t)0x40000000)   /*!< Timer E compare 4 */

/**** Bit definition for Slave Timer Chopper register *************************/
#define HRTIM_CHPR_CARFRQ    ((uint32_t)0x0000000F)   /*!< Timer carrier frequency value */
#define HRTIM_CHPR_CARFRQ_0  ((uint32_t)0x00000001)   /*!< Timer carrier frequency value bit 0 */
#define HRTIM_CHPR_CARFRQ_1  ((uint32_t)0x00000002)   /*!< Timer carrier frequency value bit 1 */
#define HRTIM_CHPR_CARFRQ_2  ((uint32_t)0x00000004)   /*!< Timer carrier frequency value bit 2 */
#define HRTIM_CHPR_CARFRQ_3  ((uint32_t)0x00000008)   /*!< Timer carrier frequency value bit 3 */

#define HRTIM_CHPR_CARDTY    ((uint32_t)0x00000070)   /*!< Timer chopper duty cycle value */
#define HRTIM_CHPR_CARDTY_0  ((uint32_t)0x00000010)   /*!< Timer chopper duty cycle value bit 0 */
#define HRTIM_CHPR_CARDTY_1  ((uint32_t)0x00000020)   /*!< Timer chopper duty cycle value bit 1 */
#define HRTIM_CHPR_CARDTY_2  ((uint32_t)0x00000040)   /*!< Timer chopper duty cycle value bit 2 */

#define HRTIM_CHPR_STRPW     ((uint32_t)0x00000780)   /*!< Timer start pulse width value */
#define HRTIM_CHPR_STRPW_0   ((uint32_t)0x00000080)   /*!< Timer start pulse width value bit 0 */
#define HRTIM_CHPR_STRPW_1   ((uint32_t)0x00000100)   /*!< Timer start pulse width value bit 1 */
#define HRTIM_CHPR_STRPW_2   ((uint32_t)0x00000200)   /*!< Timer start pulse width value bit 2 */
#define HRTIM_CHPR_STRPW_3   ((uint32_t)0x00000400)   /*!< Timer start pulse width value bit 3 */

/**** Bit definition for Slave Timer Capture 1 control register ***************/
#define HRTIM_CPT1CR_SWCPT       ((uint32_t)0x00000001)   /*!< Software capture */
#define HRTIM_CPT1CR_UPDCPT      ((uint32_t)0x00000002)   /*!< Update capture */
#define HRTIM_CPT1CR_EXEV1CPT    ((uint32_t)0x00000004)   /*!< External event 1 capture */
#define HRTIM_CPT1CR_EXEV2CPT    ((uint32_t)0x00000008)   /*!< External event 2 capture */
#define HRTIM_CPT1CR_EXEV3CPT    ((uint32_t)0x00000010)   /*!< External event 3 capture */
#define HRTIM_CPT1CR_EXEV4CPT    ((uint32_t)0x00000020)   /*!< External event 4 capture */
#define HRTIM_CPT1CR_EXEV5CPT    ((uint32_t)0x00000040)   /*!< External event 5 capture */
#define HRTIM_CPT1CR_EXEV6CPT    ((uint32_t)0x00000080)   /*!< External event 6 capture */
#define HRTIM_CPT1CR_EXEV7CPT    ((uint32_t)0x00000100)   /*!< External event 7 capture */
#define HRTIM_CPT1CR_EXEV8CPT    ((uint32_t)0x00000200)   /*!< External event 8 capture */
#define HRTIM_CPT1CR_EXEV9CPT    ((uint32_t)0x00000400)   /*!< External event 9 capture */
#define HRTIM_CPT1CR_EXEV10CPT   ((uint32_t)0x00000800)   /*!< External event 10 capture */

#define HRTIM_CPT1CR_TA1SET      ((uint32_t)0x00001000)   /*!< Timer A output 1 set */
#define HRTIM_CPT1CR_TA1RST      ((uint32_t)0x00002000)   /*!< Timer A output 1 reset */
#define HRTIM_CPT1CR_TA1CMP1     ((uint32_t)0x00004000)   /*!< Timer A compare 1 */
#define HRTIM_CPT1CR_TA1CMP2     ((uint32_t)0x00008000)   /*!< Timer A compare 2 */

#define HRTIM_CPT1CR_TB1SET      ((uint32_t)0x00010000)   /*!< Timer B output 1 set */
#define HRTIM_CPT1CR_TB1RST      ((uint32_t)0x00020000)   /*!< Timer B output 1 reset */
#define HRTIM_CPT1CR_TB1CMP1     ((uint32_t)0x00040000)   /*!< Timer B compare 1 */
#define HRTIM_CPT1CR_TB1CMP2     ((uint32_t)0x00080000)   /*!< Timer B compare 2 */

#define HRTIM_CPT1CR_TC1SET      ((uint32_t)0x00100000)   /*!< Timer C output 1 set */
#define HRTIM_CPT1CR_TC1RST      ((uint32_t)0x00200000)   /*!< Timer C output 1 reset */
#define HRTIM_CPT1CR_TC1CMP1     ((uint32_t)0x00400000)   /*!< Timer C compare 1 */
#define HRTIM_CPT1CR_TC1CMP2     ((uint32_t)0x00800000)   /*!< Timer C compare 2 */

#define HRTIM_CPT1CR_TD1SET      ((uint32_t)0x01000000)   /*!< Timer D output 1 set */
#define HRTIM_CPT1CR_TD1RST      ((uint32_t)0x02000000)   /*!< Timer D output 1 reset */
#define HRTIM_CPT1CR_TD1CMP1     ((uint32_t)0x04000000)   /*!< Timer D compare 1 */
#define HRTIM_CPT1CR_TD1CMP2     ((uint32_t)0x08000000)   /*!< Timer D compare 2 */

#define HRTIM_CPT1CR_TE1SET      ((uint32_t)0x10000000)   /*!< Timer E output 1 set */
#define HRTIM_CPT1CR_TE1RST      ((uint32_t)0x20000000)   /*!< Timer E output 1 reset */
#define HRTIM_CPT1CR_TE1CMP1     ((uint32_t)0x40000000)   /*!< Timer E compare 1 */
#define HRTIM_CPT1CR_TE1CMP2     ((uint32_t)0x80000000)   /*!< Timer E compare 2 */

/**** Bit definition for Slave Timer Capture 2 control register ***************/
#define HRTIM_CPT2CR_SWCPT       ((uint32_t)0x00000001)   /*!< Software capture */
#define HRTIM_CPT2CR_UPDCPT      ((uint32_t)0x00000002)   /*!< Update capture */
#define HRTIM_CPT2CR_EXEV1CPT    ((uint32_t)0x00000004)   /*!< External event 1 capture */
#define HRTIM_CPT2CR_EXEV2CPT    ((uint32_t)0x00000008)   /*!< External event 2 capture */
#define HRTIM_CPT2CR_EXEV3CPT    ((uint32_t)0x00000010)   /*!< External event 3 capture */
#define HRTIM_CPT2CR_EXEV4CPT    ((uint32_t)0x00000020)   /*!< External event 4 capture */
#define HRTIM_CPT2CR_EXEV5CPT    ((uint32_t)0x00000040)   /*!< External event 5 capture */
#define HRTIM_CPT2CR_EXEV6CPT    ((uint32_t)0x00000080)   /*!< External event 6 capture */
#define HRTIM_CPT2CR_EXEV7CPT    ((uint32_t)0x00000100)   /*!< External event 7 capture */
#define HRTIM_CPT2CR_EXEV8CPT    ((uint32_t)0x00000200)   /*!< External event 8 capture */
#define HRTIM_CPT2CR_EXEV9CPT    ((uint32_t)0x00000400)   /*!< External event 9 capture */
#define HRTIM_CPT2CR_EXEV10CPT   ((uint32_t)0x00000800)   /*!< External event 10 capture */

#define HRTIM_CPT2CR_TA1SET      ((uint32_t)0x00001000)   /*!< Timer A output 1 set */
#define HRTIM_CPT2CR_TA1RST      ((uint32_t)0x00002000)   /*!< Timer A output 1 reset */
#define HRTIM_CPT2CR_TA1CMP1     ((uint32_t)0x00004000)   /*!< Timer A compare 1 */
#define HRTIM_CPT2CR_TA1CMP2     ((uint32_t)0x00008000)   /*!< Timer A compare 2 */

#define HRTIM_CPT2CR_TB1SET      ((uint32_t)0x00010000)   /*!< Timer B output 1 set */
#define HRTIM_CPT2CR_TB1RST      ((uint32_t)0x00020000)   /*!< Timer B output 1 reset */
#define HRTIM_CPT2CR_TB1CMP1     ((uint32_t)0x00040000)   /*!< Timer B compare 1 */
#define HRTIM_CPT2CR_TB1CMP2     ((uint32_t)0x00080000)   /*!< Timer B compare 2 */

#define HRTIM_CPT2CR_TC1SET      ((uint32_t)0x00100000)   /*!< Timer C output 1 set */
#define HRTIM_CPT2CR_TC1RST      ((uint32_t)0x00200000)   /*!< Timer C output 1 reset */
#define HRTIM_CPT2CR_TC1CMP1     ((uint32_t)0x00400000)   /*!< Timer C compare 1 */
#define HRTIM_CPT2CR_TC1CMP2     ((uint32_t)0x00800000)   /*!< Timer C compare 2 */

#define HRTIM_CPT2CR_TD1SET      ((uint32_t)0x01000000)   /*!< Timer D output 1 set */
#define HRTIM_CPT2CR_TD1RST      ((uint32_t)0x02000000)   /*!< Timer D output 1 reset */
#define HRTIM_CPT2CR_TD1CMP1     ((uint32_t)0x04000000)   /*!< Timer D compare 1 */
#define HRTIM_CPT2CR_TD1CMP2     ((uint32_t)0x08000000)   /*!< Timer D compare 2 */

#define HRTIM_CPT2CR_TE1SET      ((uint32_t)0x10000000)   /*!< Timer E output 1 set */
#define HRTIM_CPT2CR_TE1RST      ((uint32_t)0x20000000)   /*!< Timer E output 1 reset */
#define HRTIM_CPT2CR_TE1CMP1     ((uint32_t)0x40000000)   /*!< Timer E compare 1 */
#define HRTIM_CPT2CR_TE1CMP2     ((uint32_t)0x80000000)   /*!< Timer E compare 2 */

/**** Bit definition for Slave Timer Output register **************************/
#define HRTIM_OUTR_POL1       ((uint32_t)0x00000002)    /*!< Slave output 1 polarity */
#define HRTIM_OUTR_IDLM1      ((uint32_t)0x00000004)   /*!< Slave output 1 idle mode */
#define HRTIM_OUTR_IDLES1     ((uint32_t)0x00000008)   /*!< Slave output 1 idle state */
#define HRTIM_OUTR_FAULT1     ((uint32_t)0x00000030)   /*!< Slave output 1 fault state */
#define HRTIM_OUTR_FAULT1_0   ((uint32_t)0x00000010)   /*!< Slave output 1 fault state bit 0 */
#define HRTIM_OUTR_FAULT1_1   ((uint32_t)0x00000020)   /*!< Slave output 1 fault state bit 1 */
#define HRTIM_OUTR_CHP1       ((uint32_t)0x00000040)   /*!< Slave output 1 chopper enable */
#define HRTIM_OUTR_DIDL1      ((uint32_t)0x00000080)   /*!< Slave output 1 dead time idle */

#define HRTIM_OUTR_DTEN      ((uint32_t)0x00000100)   /*!< Slave output deadtime enable */
#define HRTIM_OUTR_DLYPRTEN  ((uint32_t)0x00000200)   /*!< Slave output delay protection enable */
#define HRTIM_OUTR_DLYPRT    ((uint32_t)0x00001C00)   /*!< Slave output delay protection */
#define HRTIM_OUTR_DLYPRT_0  ((uint32_t)0x00000400)   /*!< Slave output delay protection bit 0 */
#define HRTIM_OUTR_DLYPRT_1  ((uint32_t)0x00000800)   /*!< Slave output delay protection bit 1 */
#define HRTIM_OUTR_DLYPRT_2  ((uint32_t)0x00001000)   /*!< Slave output delay protection bit 2 */

#define HRTIM_OUTR_POL2      ((uint32_t)0x00020000)   /*!< Slave output 2 polarity */
#define HRTIM_OUTR_IDLM2     ((uint32_t)0x00040000)   /*!< Slave output 2 idle mode */
#define HRTIM_OUTR_IDLES2    ((uint32_t)0x00080000)   /*!< Slave output 2 idle state */
#define HRTIM_OUTR_FAULT2    ((uint32_t)0x00300000)   /*!< Slave output 2 fault state */
#define HRTIM_OUTR_FAULT2_0  ((uint32_t)0x00100000)   /*!< Slave output 2 fault state bit 0 */
#define HRTIM_OUTR_FAULT2_1  ((uint32_t)0x00200000)   /*!< Slave output 2 fault state bit 1 */
#define HRTIM_OUTR_CHP2      ((uint32_t)0x00400000)   /*!< Slave output 2 chopper enable */
#define HRTIM_OUTR_DIDL2     ((uint32_t)0x00800000)   /*!< Slave output 2 dead time idle */

/**** Bit definition for Slave Timer Fault register ***************************/
#define HRTIM_FLTR_FLT1EN     ((uint32_t)0x00000001)   /*!< Fault 1 enable */
#define HRTIM_FLTR_FLT2EN     ((uint32_t)0x00000002)   /*!< Fault 2 enable */
#define HRTIM_FLTR_FLT3EN     ((uint32_t)0x00000004)   /*!< Fault 3 enable */
#define HRTIM_FLTR_FLT4EN     ((uint32_t)0x00000008)   /*!< Fault 4 enable */
#define HRTIM_FLTR_FLT5EN     ((uint32_t)0x00000010)   /*!< Fault 5 enable */
#define HRTIM_FLTR_FLTCLK     ((uint32_t)0x80000000)   /*!< Fault sources lock */

/**** Bit definition for Common HRTIM Timer control register 1 ****************/
#define HRTIM_CR1_MUDIS       ((uint32_t)0x00000001)   /*!< Master update disable*/
#define HRTIM_CR1_TAUDIS      ((uint32_t)0x00000002)   /*!< Timer A update disable*/
#define HRTIM_CR1_TBUDIS      ((uint32_t)0x00000004)   /*!< Timer B update disable*/
#define HRTIM_CR1_TCUDIS      ((uint32_t)0x00000008)   /*!< Timer C update disable*/
#define HRTIM_CR1_TDUDIS      ((uint32_t)0x00000010)   /*!< Timer D update disable*/
#define HRTIM_CR1_TEUDIS      ((uint32_t)0x00000020)   /*!< Timer E update disable*/
#define HRTIM_CR1_ADC1USRC    ((uint32_t)0x00070000)   /*!< ADC Trigger 1 update source */
#define HRTIM_CR1_ADC1USRC_0  ((uint32_t)0x00010000)   /*!< ADC Trigger 1 update source bit 0 */
#define HRTIM_CR1_ADC1USRC_1  ((uint32_t)0x00020000)   /*!< ADC Trigger 1 update source bit 1 */
#define HRTIM_CR1_ADC1USRC_2  ((uint32_t)0x00040000)   /*!< ADC Trigger 1 update source bit 2 */
#define HRTIM_CR1_ADC2USRC    ((uint32_t)0x00380000)   /*!< ADC Trigger 2 update source */
#define HRTIM_CR1_ADC2USRC_0  ((uint32_t)0x00080000)   /*!< ADC Trigger 2 update source bit 0 */
#define HRTIM_CR1_ADC2USRC_1  ((uint32_t)0x00100000)   /*!< ADC Trigger 2 update source bit 1 */
#define HRTIM_CR1_ADC2USRC_2  ((uint32_t)0x00200000)   /*!< ADC Trigger 2 update source bit 2 */
#define HRTIM_CR1_ADC3USRC    ((uint32_t)0x01C00000)   /*!< ADC Trigger 3 update source */
#define HRTIM_CR1_ADC3USRC_0  ((uint32_t)0x00400000)   /*!< ADC Trigger 3 update source bit 0 */
#define HRTIM_CR1_ADC3USRC_1  ((uint32_t)0x00800000)   /*!< ADC Trigger 3 update source bit 1 */
#define HRTIM_CR1_ADC3USRC_2  ((uint32_t)0x01000000)   /*!< ADC Trigger 3 update source bit 2 */
#define HRTIM_CR1_ADC4USRC    ((uint32_t)0x0E000000)   /*!< ADC Trigger 4 update source */
#define HRTIM_CR1_ADC4USRC_0  ((uint32_t)0x02000000)   /*!< ADC Trigger 4 update source bit 0 */
#define HRTIM_CR1_ADC4USRC_1  ((uint32_t)0x04000000)   /*!< ADC Trigger 4 update source bit 1 */
#define HRTIM_CR1_ADC4USRC_2  ((uint32_t)0x0800000)   /*!< ADC Trigger 4 update source bit 2 */

/**** Bit definition for Common HRTIM Timer control register 2 ****************/
#define HRTIM_CR2_MSWU   ((uint32_t)0x00000001)        /*!< Master software update */
#define HRTIM_CR2_TASWU  ((uint32_t)0x00000002)        /*!< Timer A software update */
#define HRTIM_CR2_TBSWU  ((uint32_t)0x00000004)        /*!< Timer B software update */
#define HRTIM_CR2_TCSWU  ((uint32_t)0x00000008)        /*!< Timer C software update */
#define HRTIM_CR2_TDSWU  ((uint32_t)0x00000010)        /*!< Timer D software update */
#define HRTIM_CR2_TESWU  ((uint32_t)0x00000020)        /*!< Timer E software update */
#define HRTIM_CR2_MRST   ((uint32_t)0x00000100)        /*!< Master count software reset */
#define HRTIM_CR2_TARST  ((uint32_t)0x00000200)        /*!< Timer A count software reset */
#define HRTIM_CR2_TBRST  ((uint32_t)0x00000400)        /*!< Timer B count software reset */
#define HRTIM_CR2_TCRST  ((uint32_t)0x00000800)        /*!< Timer C count software reset */
#define HRTIM_CR2_TDRST  ((uint32_t)0x00001000)        /*!< Timer D count software reset */
#define HRTIM_CR2_TERST  ((uint32_t)0x00002000)        /*!< Timer E count software reset */

/**** Bit definition for Common HRTIM Timer interrupt status register *********/
#define HRTIM_ISR_FLT1    ((uint32_t)0x00000001)   /*!< Fault 1 interrupt flag */
#define HRTIM_ISR_FLT2    ((uint32_t)0x00000002)   /*!< Fault 2 interrupt flag */
#define HRTIM_ISR_FLT3    ((uint32_t)0x00000004)   /*!< Fault 3 interrupt flag */
#define HRTIM_ISR_FLT4    ((uint32_t)0x00000008)   /*!< Fault 4 interrupt flag */
#define HRTIM_ISR_FLT5    ((uint32_t)0x00000010)   /*!< Fault 5 interrupt flag */
#define HRTIM_ISR_SYSFLT  ((uint32_t)0x00000020)   /*!< System Fault interrupt flag */
#define HRTIM_ISR_DLLRDY  ((uint32_t)0x00010000)   /*!< DLL ready interrupt flag */
#define HRTIM_ISR_BMPER   ((uint32_t)0x00020000)   /*!<  Burst mode period interrupt flag */

/**** Bit definition for Common HRTIM Timer interrupt clear register **********/
#define HRTIM_ICR_FLT1C    ((uint32_t)0x00000001)   /*!< Fault 1 interrupt flag clear */
#define HRTIM_ICR_FLT2C    ((uint32_t)0x00000002)   /*!< Fault 2 interrupt flag clear */
#define HRTIM_ICR_FLT3C    ((uint32_t)0x00000004)   /*!< Fault 3 interrupt flag clear */
#define HRTIM_ICR_FLT4C    ((uint32_t)0x00000008)   /*!< Fault 4 interrupt flag clear */
#define HRTIM_ICR_FLT5C    ((uint32_t)0x00000010)   /*!< Fault 5 interrupt flag clear */
#define HRTIM_ICR_SYSFLTC  ((uint32_t)0x00000020)   /*!< System Fault interrupt flag clear */
#define HRTIM_ICR_DLLRDYC  ((uint32_t)0x00010000)   /*!< DLL ready interrupt flag clear */
#define HRTIM_ICR_BMPERC   ((uint32_t)0x00020000)   /*!<  Burst mode period interrupt flag clear */

/**** Bit definition for Common HRTIM Timer interrupt enable register *********/
#define HRTIM_IER_FLT1    ((uint32_t)0x00000001)   /*!< Fault 1 interrupt enable */
#define HRTIM_IER_FLT2    ((uint32_t)0x00000002)   /*!< Fault 2 interrupt enable */
#define HRTIM_IER_FLT3    ((uint32_t)0x00000004)   /*!< Fault 3 interrupt enable */
#define HRTIM_IER_FLT4    ((uint32_t)0x00000008)   /*!< Fault 4 interrupt enable */
#define HRTIM_IER_FLT5    ((uint32_t)0x00000010)   /*!< Fault 5 interrupt enable */
#define HRTIM_IER_SYSFLT  ((uint32_t)0x00000020)   /*!< System Fault interrupt enable */
#define HRTIM_IER_DLLRDY  ((uint32_t)0x00010000)   /*!< DLL ready interrupt enable */
#define HRTIM_IER_BMPER   ((uint32_t)0x00020000)   /*!<  Burst mode period interrupt enable */

/**** Bit definition for Common HRTIM Timer output enable register ************/
#define HRTIM_OENR_TA1OEN    ((uint32_t)0x00000001)   /*!< Timer A Output 1 enable */
#define HRTIM_OENR_TA2OEN    ((uint32_t)0x00000002)   /*!< Timer A Output 2 enable */
#define HRTIM_OENR_TB1OEN    ((uint32_t)0x00000004)   /*!< Timer B Output 1 enable */
#define HRTIM_OENR_TB2OEN    ((uint32_t)0x00000008)   /*!< Timer B Output 2 enable */
#define HRTIM_OENR_TC1OEN    ((uint32_t)0x00000010)   /*!< Timer C Output 1 enable */
#define HRTIM_OENR_TC2OEN    ((uint32_t)0x00000020)   /*!< Timer C Output 2 enable */
#define HRTIM_OENR_TD1OEN    ((uint32_t)0x00000040)   /*!< Timer D Output 1 enable */
#define HRTIM_OENR_TD2OEN    ((uint32_t)0x00000080)   /*!< Timer D Output 2 enable */
#define HRTIM_OENR_TE1OEN    ((uint32_t)0x00000100)   /*!< Timer E Output 1 enable */
#define HRTIM_OENR_TE2OEN    ((uint32_t)0x00000200)   /*!< Timer E Output 2 enable */

/**** Bit definition for Common HRTIM Timer output disable register ***********/
#define HRTIM_ODISR_TA1ODIS    ((uint32_t)0x00000001)   /*!< Timer A Output 1 disable */
#define HRTIM_ODISR_TA2ODIS    ((uint32_t)0x00000002)   /*!< Timer A Output 2 disable */
#define HRTIM_ODISR_TB1ODIS    ((uint32_t)0x00000004)   /*!< Timer B Output 1 disable */
#define HRTIM_ODISR_TB2ODIS    ((uint32_t)0x00000008)   /*!< Timer B Output 2 disable */
#define HRTIM_ODISR_TC1ODIS    ((uint32_t)0x00000010)   /*!< Timer C Output 1 disable */
#define HRTIM_ODISR_TC2ODIS    ((uint32_t)0x00000020)   /*!< Timer C Output 2 disable */
#define HRTIM_ODISR_TD1ODIS    ((uint32_t)0x00000040)   /*!< Timer D Output 1 disable */
#define HRTIM_ODISR_TD2ODIS    ((uint32_t)0x00000080)   /*!< Timer D Output 2 disable */
#define HRTIM_ODISR_TE1ODIS    ((uint32_t)0x00000100)   /*!< Timer E Output 1 disable */
#define HRTIM_ODISR_TE2ODIS    ((uint32_t)0x00000200)   /*!< Timer E Output 2 disable */

/**** Bit definition for Common HRTIM Timer output disable status register *****/
#define HRTIM_ODSR_TA1ODS    ((uint32_t)0x00000001)   /*!< Timer A Output 1 disable status */
#define HRTIM_ODSR_TA2ODS    ((uint32_t)0x00000002)   /*!< Timer A Output 2 disable status */
#define HRTIM_ODSR_TB1ODS    ((uint32_t)0x00000004)   /*!< Timer B Output 1 disable status */
#define HRTIM_ODSR_TB2ODS    ((uint32_t)0x00000008)   /*!< Timer B Output 2 disable status */
#define HRTIM_ODSR_TC1ODS    ((uint32_t)0x00000010)   /*!< Timer C Output 1 disable status */
#define HRTIM_ODSR_TC2ODS    ((uint32_t)0x00000020)   /*!< Timer C Output 2 disable status */
#define HRTIM_ODSR_TD1ODS    ((uint32_t)0x00000040)   /*!< Timer D Output 1 disable status */
#define HRTIM_ODSR_TD2ODS    ((uint32_t)0x00000080)   /*!< Timer D Output 2 disable status */
#define HRTIM_ODSR_TE1ODS    ((uint32_t)0x00000100)   /*!< Timer E Output 1 disable status */
#define HRTIM_ODSR_TE2ODS    ((uint32_t)0x00000200)   /*!< Timer E Output 2 disable status */

/**** Bit definition for Common HRTIM Timer Burst mode control register ********/
#define HRTIM_BMCR_BME       ((uint32_t)0x00000001)    /*!< Burst mode enable */
#define HRTIM_BMCR_BMOM      ((uint32_t)0x00000002)    /*!< Burst mode operating mode */
#define HRTIM_BMCR_BMCLK     ((uint32_t)0x0000003C)    /*!< Burst mode clock source */
#define HRTIM_BMCR_BMCLK_0   ((uint32_t)0x00000004)    /*!< Burst mode clock source bit 0 */
#define HRTIM_BMCR_BMCLK_1   ((uint32_t)0x00000008)    /*!< Burst mode clock source bit 1 */
#define HRTIM_BMCR_BMCLK_2   ((uint32_t)0x00000010)    /*!< Burst mode clock source bit 2 */
#define HRTIM_BMCR_BMCLK_3   ((uint32_t)0x00000020)    /*!< Burst mode clock source bit 3 */
#define HRTIM_BMCR_BMPSC     ((uint32_t)0x000003C0)    /*!< Burst mode prescaler */
#define HRTIM_BMCR_BMPSC_0   ((uint32_t)0x00000040)    /*!< Burst mode prescaler bit 0 */
#define HRTIM_BMCR_BMPSC_1   ((uint32_t)0x00000080)    /*!< Burst mode prescaler bit 1 */
#define HRTIM_BMCR_BMPSC_2   ((uint32_t)0x00000100)    /*!< Burst mode prescaler bit 2 */
#define HRTIM_BMCR_BMPSC_3   ((uint32_t)0x00000200)    /*!< Burst mode prescaler bit 3 */
#define HRTIM_BMCR_BMPREN    ((uint32_t)0x00000400)    /*!< Burst mode Preload bit */
#define HRTIM_BMCR_MTBM      ((uint32_t)0x00010000)    /*!< Master Timer Burst mode */
#define HRTIM_BMCR_TABM      ((uint32_t)0x00020000)    /*!< Timer A Burst mode */
#define HRTIM_BMCR_TBBM      ((uint32_t)0x00040000)    /*!< Timer B Burst mode */
#define HRTIM_BMCR_TCBM      ((uint32_t)0x00080000)    /*!< Timer C Burst mode */
#define HRTIM_BMCR_TDBM      ((uint32_t)0x00100000)    /*!< Timer D Burst mode */
#define HRTIM_BMCR_TEBM      ((uint32_t)0x00200000)    /*!< Timer E Burst mode */
#define HRTIM_BMCR_BMSTAT    ((uint32_t)0x80000000)    /*!< Burst mode status */

/**** Bit definition for Common HRTIM Timer Burst mode Trigger register *******/
#define HRTIM_BMTRGR_SW       ((uint32_t)0x00000001)    /*!< Software start */
#define HRTIM_BMTRGR_MSTRST   ((uint32_t)0x00000002)    /*!<  Master reset */
#define HRTIM_BMTRGR_MSTREP   ((uint32_t)0x00000004)    /*!<  Master repetition */
#define HRTIM_BMTRGR_MSTCMP1  ((uint32_t)0x00000008)    /*!<  Master compare 1 */
#define HRTIM_BMTRGR_MSTCMP2  ((uint32_t)0x00000010)    /*!< Master compare 2  */
#define HRTIM_BMTRGR_MSTCMP3  ((uint32_t)0x00000020)    /*!< Master compare 3 */
#define HRTIM_BMTRGR_MSTCMP4  ((uint32_t)0x00000040)    /*!< Master compare 4 */
#define HRTIM_BMTRGR_TARST    ((uint32_t)0x00000080)    /*!< Timer A reset  */
#define HRTIM_BMTRGR_TAREP    ((uint32_t)0x00000100)    /*!< Timer A repetition  */
#define HRTIM_BMTRGR_TACMP1   ((uint32_t)0x00000200)    /*!< Timer A compare 1  */
#define HRTIM_BMTRGR_TACMP2   ((uint32_t)0x00000400)    /*!< Timer A compare 2  */
#define HRTIM_BMTRGR_TBRST    ((uint32_t)0x00000800)    /*!< Timer B reset  */
#define HRTIM_BMTRGR_TBREP    ((uint32_t)0x00001000)    /*!< Timer B repetition  */
#define HRTIM_BMTRGR_TBCMP1   ((uint32_t)0x00002000)    /*!< Timer B compare 1 */
#define HRTIM_BMTRGR_TBCMP2   ((uint32_t)0x00004000)    /*!< Timer B compare 2 */
#define HRTIM_BMTRGR_TCRST    ((uint32_t)0x00008000)    /*!< Timer C reset  */
#define HRTIM_BMTRGR_TCREP    ((uint32_t)0x00010000)    /*!< Timer C repetition */
#define HRTIM_BMTRGR_TCCMP1   ((uint32_t)0x00020000)    /*!< Timer C compare 1 */
#define HRTIM_BMTRGR_TCCMP2   ((uint32_t)0x00040000)    /*!< Timer C compare 2 */
#define HRTIM_BMTRGR_TDRST    ((uint32_t)0x00080000)    /*!< Timer D reset  */
#define HRTIM_BMTRGR_TDREP    ((uint32_t)0x00100000)    /*!< Timer D repetition  */
#define HRTIM_BMTRGR_TDCMP1   ((uint32_t)0x00200000)    /*!< Timer D compare 1 */
#define HRTIM_BMTRGR_TDCMP2   ((uint32_t)0x00400000)    /*!< Timer D compare 2 */
#define HRTIM_BMTRGR_TERST    ((uint32_t)0x00800000)    /*!< Timer E reset  */
#define HRTIM_BMTRGR_TEREP    ((uint32_t)0x01000000)    /*!< Timer E repetition  */
#define HRTIM_BMTRGR_TECMP1   ((uint32_t)0x02000000)    /*!< Timer E compare 1 */
#define HRTIM_BMTRGR_TECMP2   ((uint32_t)0x04000000)    /*!< Timer E compare 2 */
#define HRTIM_BMTRGR_TAEEV7   ((uint32_t)0x08000000)    /*!< Timer A period following External Event7  */
#define HRTIM_BMTRGR_TDEEV8   ((uint32_t)0x10000000)    /*!< Timer D period following External Event8  */
#define HRTIM_BMTRGR_EEV7     ((uint32_t)0x20000000)    /*!< External Event 7 */
#define HRTIM_BMTRGR_EEV8     ((uint32_t)0x40000000)    /*!< External Event 8 */
#define HRTIM_BMTRGR_OCHPEV   ((uint32_t)0x80000000)    /*!< on-chip Event */

/*******************  Bit definition for HRTIM_BMCMPR register  ***************/
#define  HRTIM_BMCMPR_BMCMPR     ((uint32_t)0x0000FFFF)     /*!<!<Burst Compare Value */

/*******************  Bit definition for HRTIM_BMPER register  ****************/
#define  HRTIM_BMPER_BMPER     ((uint32_t)0x0000FFFF)     /*!<!<Burst period Value */

/*******************  Bit definition for HRTIM_EECR1 register  ****************/
#define HRTIM_EECR1_EE1SRC    ((uint32_t)0x00000003)    /*!< External event 1 source */
#define HRTIM_EECR1_EE1SRC_0  ((uint32_t)0x00000001)    /*!< External event 1 source bit 0 */
#define HRTIM_EECR1_EE1SRC_1  ((uint32_t)0x00000002)    /*!< External event 1 source bit 1 */
#define HRTIM_EECR1_EE1POL    ((uint32_t)0x00000004)    /*!< External event 1 Polarity */
#define HRTIM_EECR1_EE1SNS    ((uint32_t)0x00000018)    /*!< External event 1 sensitivity */
#define HRTIM_EECR1_EE1SNS_0  ((uint32_t)0x00000008)    /*!< External event 1 sensitivity bit 0 */
#define HRTIM_EECR1_EE1SNS_1  ((uint32_t)0x00000010)    /*!< External event 1 sensitivity bit 1 */
#define HRTIM_EECR1_EE1FAST   ((uint32_t)0x00000020)    /*!< External event 1 Fast mode */

#define HRTIM_EECR1_EE2SRC    ((uint32_t)0x000000C0)    /*!< External event 2 source */
#define HRTIM_EECR1_EE2SRC_0  ((uint32_t)0x00000040)    /*!< External event 2 source bit 0 */
#define HRTIM_EECR1_EE2SRC_1  ((uint32_t)0x00000080)    /*!< External event 2 source bit 1 */
#define HRTIM_EECR1_EE2POL    ((uint32_t)0x00000100)    /*!< External event 2 Polarity */
#define HRTIM_EECR1_EE2SNS    ((uint32_t)0x00000600)    /*!< External event 2 sensitivity */
#define HRTIM_EECR1_EE2SNS_0  ((uint32_t)0x00000200)    /*!< External event 2 sensitivity bit 0 */
#define HRTIM_EECR1_EE2SNS_1  ((uint32_t)0x00000400)    /*!< External event 2 sensitivity bit 1 */
#define HRTIM_EECR1_EE2FAST   ((uint32_t)0x00000800)    /*!< External event 2 Fast mode */

#define HRTIM_EECR1_EE3SRC    ((uint32_t)0x00003000)    /*!< External event 3 source */
#define HRTIM_EECR1_EE3SRC_0  ((uint32_t)0x00001000)    /*!< External event 3 source bit 0 */
#define HRTIM_EECR1_EE3SRC_1  ((uint32_t)0x00002000)    /*!< External event 3 source bit 1 */
#define HRTIM_EECR1_EE3POL    ((uint32_t)0x00004000)    /*!< External event 3 Polarity */
#define HRTIM_EECR1_EE3SNS    ((uint32_t)0x00018000)    /*!< External event 3 sensitivity */
#define HRTIM_EECR1_EE3SNS_0  ((uint32_t)0x00008000)    /*!< External event 3 sensitivity bit 0 */
#define HRTIM_EECR1_EE3SNS_1  ((uint32_t)0x00010000)    /*!< External event 3 sensitivity bit 1 */
#define HRTIM_EECR1_EE3FAST   ((uint32_t)0x00020000)    /*!< External event 3 Fast mode */

#define HRTIM_EECR1_EE4SRC    ((uint32_t)0x000C0000)    /*!< External event 4 source */
#define HRTIM_EECR1_EE4SRC_0  ((uint32_t)0x00040000)    /*!< External event 4 source bit 0 */
#define HRTIM_EECR1_EE4SRC_1  ((uint32_t)0x00080000)    /*!< External event 4 source bit 1 */
#define HRTIM_EECR1_EE4POL    ((uint32_t)0x00100000)    /*!< External event 4 Polarity */
#define HRTIM_EECR1_EE4SNS    ((uint32_t)0x00600000)    /*!< External event 4 sensitivity */
#define HRTIM_EECR1_EE4SNS_0  ((uint32_t)0x00200000)    /*!< External event 4 sensitivity bit 0 */
#define HRTIM_EECR1_EE4SNS_1  ((uint32_t)0x00400000)    /*!< External event 4 sensitivity bit 1 */
#define HRTIM_EECR1_EE4FAST   ((uint32_t)0x00800000)    /*!< External event 4 Fast mode */

#define HRTIM_EECR1_EE5SRC    ((uint32_t)0x03000000)    /*!< External event 5 source */
#define HRTIM_EECR1_EE5SRC_0  ((uint32_t)0x01000000)    /*!< External event 5 source bit 0 */
#define HRTIM_EECR1_EE5SRC_1  ((uint32_t)0x02000000)    /*!< External event 5 source bit 1 */
#define HRTIM_EECR1_EE5POL    ((uint32_t)0x04000000)    /*!< External event 5 Polarity */
#define HRTIM_EECR1_EE5SNS    ((uint32_t)0x18000000)    /*!< External event 5 sensitivity */
#define HRTIM_EECR1_EE5SNS_0  ((uint32_t)0x08000000)    /*!< External event 5 sensitivity bit 0 */
#define HRTIM_EECR1_EE5SNS_1  ((uint32_t)0x10000000)    /*!< External event 5 sensitivity bit 1 */
#define HRTIM_EECR1_EE5FAST   ((uint32_t)0x20000000)    /*!< External event 5 Fast mode */

/*******************  Bit definition for HRTIM_EECR2 register  ****************/
#define HRTIM_EECR2_EE6SRC    ((uint32_t)0x00000003)    /*!< External event 6 source */
#define HRTIM_EECR2_EE6SRC_0  ((uint32_t)0x00000001)    /*!< External event 6 source bit 0 */
#define HRTIM_EECR2_EE6SRC_1  ((uint32_t)0x00000002)    /*!< External event 6 source bit 1 */
#define HRTIM_EECR2_EE6POL    ((uint32_t)0x00000004)    /*!< External event 6 Polarity */
#define HRTIM_EECR2_EE6SNS    ((uint32_t)0x00000018)    /*!< External event 6 sensitivity */
#define HRTIM_EECR2_EE6SNS_0  ((uint32_t)0x00000008)    /*!< External event 6 sensitivity bit 0 */
#define HRTIM_EECR2_EE6SNS_1  ((uint32_t)0x00000010)    /*!< External event 6 sensitivity bit 1 */

#define HRTIM_EECR2_EE7SRC    ((uint32_t)0x000000C0)    /*!< External event 7 source */
#define HRTIM_EECR2_EE7SRC_0  ((uint32_t)0x00000040)    /*!< External event 7 source bit 0 */
#define HRTIM_EECR2_EE7SRC_1  ((uint32_t)0x00000080)    /*!< External event 7 source bit 1 */
#define HRTIM_EECR2_EE7POL    ((uint32_t)0x00000100)    /*!< External event 7 Polarity */
#define HRTIM_EECR2_EE7SNS    ((uint32_t)0x00000600)    /*!< External event 7 sensitivity */
#define HRTIM_EECR2_EE7SNS_0  ((uint32_t)0x00000200)    /*!< External event 7 sensitivity bit 0 */
#define HRTIM_EECR2_EE7SNS_1  ((uint32_t)0x00000400)    /*!< External event 7 sensitivity bit 1 */

#define HRTIM_EECR2_EE8SRC    ((uint32_t)0x00003000)    /*!< External event 8 source */
#define HRTIM_EECR2_EE8SRC_0  ((uint32_t)0x00001000)    /*!< External event 8 source bit 0 */
#define HRTIM_EECR2_EE8SRC_1  ((uint32_t)0x00002000)    /*!< External event 8 source bit 1 */
#define HRTIM_EECR2_EE8POL    ((uint32_t)0x00004000)    /*!< External event 8 Polarity */
#define HRTIM_EECR2_EE8SNS    ((uint32_t)0x00018000)    /*!< External event 8 sensitivity */
#define HRTIM_EECR2_EE8SNS_0  ((uint32_t)0x00008000)    /*!< External event 8 sensitivity bit 0 */
#define HRTIM_EECR2_EE8SNS_1  ((uint32_t)0x00010000)    /*!< External event 8 sensitivity bit 1 */

#define HRTIM_EECR2_EE9SRC    ((uint32_t)0x000C0000)    /*!< External event 9 source */
#define HRTIM_EECR2_EE9SRC_0  ((uint32_t)0x00040000)    /*!< External event 9 source bit 0 */
#define HRTIM_EECR2_EE9SRC_1  ((uint32_t)0x00080000)    /*!< External event 9 source bit 1 */
#define HRTIM_EECR2_EE9POL    ((uint32_t)0x00100000)    /*!< External event 9 Polarity */
#define HRTIM_EECR2_EE9SNS    ((uint32_t)0x00600000)    /*!< External event 9 sensitivity */
#define HRTIM_EECR2_EE9SNS_0  ((uint32_t)0x00200000)    /*!< External event 9 sensitivity bit 0 */
#define HRTIM_EECR2_EE9SNS_1  ((uint32_t)0x00400000)    /*!< External event 9 sensitivity bit 1 */

#define HRTIM_EECR2_EE10SRC    ((uint32_t)0x03000000)    /*!< External event 10 source */
#define HRTIM_EECR2_EE10SRC_0  ((uint32_t)0x01000000)    /*!< External event 10 source bit 0 */
#define HRTIM_EECR2_EE10SRC_1  ((uint32_t)0x02000000)    /*!< External event 10 source bit 1 */
#define HRTIM_EECR2_EE10POL    ((uint32_t)0x04000000)    /*!< External event 10 Polarity */
#define HRTIM_EECR2_EE10SNS    ((uint32_t)0x18000000)    /*!< External event 10 sensitivity */
#define HRTIM_EECR2_EE10SNS_0  ((uint32_t)0x08000000)    /*!< External event 10 sensitivity bit 0 */
#define HRTIM_EECR2_EE10SNS_1  ((uint32_t)0x10000000)    /*!< External event 10 sensitivity bit 1 */

/*******************  Bit definition for HRTIM_EECR3 register  ****************/
#define HRTIM_EECR3_EE6F    ((uint32_t)0x0000000F)    /*!< External event 6 filter */
#define HRTIM_EECR3_EE6F_0  ((uint32_t)0x00000001)    /*!< External event 6 filter bit 0 */
#define HRTIM_EECR3_EE6F_1  ((uint32_t)0x00000002)    /*!< External event 6 filter bit 1  */
#define HRTIM_EECR3_EE6F_2  ((uint32_t)0x00000004)    /*!< External event 6 filter bit 2   */
#define HRTIM_EECR3_EE6F_3  ((uint32_t)0x00000008)    /*!< External event 6 filter bit 3   */
#define HRTIM_EECR3_EE7F    ((uint32_t)0x000003C0)    /*!< External event 7 filter */
#define HRTIM_EECR3_EE7F_0  ((uint32_t)0x00000040)    /*!< External event 7 filter bit 0  */
#define HRTIM_EECR3_EE7F_1  ((uint32_t)0x00000080)    /*!< External event 7 filter bit 1  */
#define HRTIM_EECR3_EE7F_2  ((uint32_t)0x00000100)    /*!< External event 7 filter bit 2  */
#define HRTIM_EECR3_EE7F_3  ((uint32_t)0x00000200)    /*!< External event 7 filter bit 3  */
#define HRTIM_EECR3_EE8F    ((uint32_t)0x0000F000)    /*!< External event 8 filter */
#define HRTIM_EECR3_EE8F_0  ((uint32_t)0x00001000)    /*!< External event 8 filter bit 0 */
#define HRTIM_EECR3_EE8F_1  ((uint32_t)0x00002000)    /*!< External event 8 filter bit 1 */
#define HRTIM_EECR3_EE8F_2  ((uint32_t)0x00004000)    /*!< External event 8 filter bit 2 */
#define HRTIM_EECR3_EE8F_3  ((uint32_t)0x00008000)    /*!< External event 8 filter bit 3 */
#define HRTIM_EECR3_EE9F    ((uint32_t)0x003C0000)    /*!< External event 9 filter */
#define HRTIM_EECR3_EE9F_0  ((uint32_t)0x00040000)    /*!< External event 9 filter bit 0 */
#define HRTIM_EECR3_EE9F_1  ((uint32_t)0x00080000)    /*!< External event 9 filter bit 1 */
#define HRTIM_EECR3_EE9F_2  ((uint32_t)0x00100000)    /*!< External event 9 filter bit 2 */
#define HRTIM_EECR3_EE9F_3  ((uint32_t)0x00200000)    /*!< External event 9 filter bit 3 */
#define HRTIM_EECR3_EE10F   ((uint32_t)0x0F000000)    /*!< External event 10 filter */
#define HRTIM_EECR3_EE10F_0 ((uint32_t)0x01000000)    /*!< External event 10 filter bit 0 */
#define HRTIM_EECR3_EE10F_1 ((uint32_t)0x02000000)    /*!< External event 10 filter bit 1 */
#define HRTIM_EECR3_EE10F_2 ((uint32_t)0x04000000)    /*!< External event 10 filter bit 2 */
#define HRTIM_EECR3_EE10F_3 ((uint32_t)0x08000000)    /*!< External event 10 filter bit 3 */
#define HRTIM_EECR3_EEVSD   ((uint32_t)0xC0000000)    /*!< External event sampling clock division */
#define HRTIM_EECR3_EEVSD_0 ((uint32_t)0x40000000)    /*!< External event sampling clock division bit 0 */
#define HRTIM_EECR3_EEVSD_1 ((uint32_t)0x80000000)    /*!< External event sampling clock division bit 1 */

/*******************  Bit definition for HRTIM_ADC1R register  ****************/
#define HRTIM_ADC1R_AD1MC1     ((uint32_t)0x00000001)    /*!< ADC Trigger 1 on master compare 1 */
#define HRTIM_ADC1R_AD1MC2     ((uint32_t)0x00000002)    /*!< ADC Trigger 1 on master compare 2 */
#define HRTIM_ADC1R_AD1MC3     ((uint32_t)0x00000004)    /*!< ADC Trigger 1 on master compare 3 */
#define HRTIM_ADC1R_AD1MC4     ((uint32_t)0x00000008)    /*!< ADC Trigger 1 on master compare 4 */
#define HRTIM_ADC1R_AD1MPER    ((uint32_t)0x00000010)    /*!< ADC Trigger 1 on master period */
#define HRTIM_ADC1R_AD1EEV1    ((uint32_t)0x00000020)    /*!< ADC Trigger 1 on external event 1 */
#define HRTIM_ADC1R_AD1EEV2    ((uint32_t)0x00000040)    /*!< ADC Trigger 1 on external event 2 */
#define HRTIM_ADC1R_AD1EEV3    ((uint32_t)0x00000080)    /*!< ADC Trigger 1 on external event 3 */
#define HRTIM_ADC1R_AD1EEV4    ((uint32_t)0x00000100)    /*!< ADC Trigger 1 on external event 4 */
#define HRTIM_ADC1R_AD1EEV5    ((uint32_t)0x00000200)    /*!< ADC Trigger 1 on external event 5 */
#define HRTIM_ADC1R_AD1TAC2    ((uint32_t)0x00000400)    /*!< ADC Trigger 1 on Timer A compare 2 */
#define HRTIM_ADC1R_AD1TAC3    ((uint32_t)0x00000800)    /*!< ADC Trigger 1 on Timer A compare 3 */
#define HRTIM_ADC1R_AD1TAC4    ((uint32_t)0x00001000)    /*!< ADC Trigger 1 on Timer A compare 4 */
#define HRTIM_ADC1R_AD1TAPER   ((uint32_t)0x00002000)    /*!< ADC Trigger 1 on Timer A period */
#define HRTIM_ADC1R_AD1TARST   ((uint32_t)0x00004000)    /*!< ADC Trigger 1 on Timer A reset */
#define HRTIM_ADC1R_AD1TBC2    ((uint32_t)0x00008000)    /*!< ADC Trigger 1 on Timer B compare 2 */
#define HRTIM_ADC1R_AD1TBC3    ((uint32_t)0x00010000)    /*!< ADC Trigger 1 on Timer B compare 3 */
#define HRTIM_ADC1R_AD1TBC4    ((uint32_t)0x00020000)    /*!< ADC Trigger 1 on Timer B compare 4 */
#define HRTIM_ADC1R_AD1TBPER   ((uint32_t)0x00040000)    /*!< ADC Trigger 1 on Timer B period */
#define HRTIM_ADC1R_AD1TBRST   ((uint32_t)0x00080000)    /*!< ADC Trigger 1 on Timer B reset */
#define HRTIM_ADC1R_AD1TCC2    ((uint32_t)0x00100000)    /*!< ADC Trigger 1 on Timer C compare 2 */
#define HRTIM_ADC1R_AD1TCC3    ((uint32_t)0x00200000)    /*!< ADC Trigger 1 on Timer C compare 3 */
#define HRTIM_ADC1R_AD1TCC4    ((uint32_t)0x00400000)    /*!< ADC Trigger 1 on Timer C compare 4 */
#define HRTIM_ADC1R_AD1TCPER   ((uint32_t)0x00800000)    /*!< ADC Trigger 1 on Timer C period */
#define HRTIM_ADC1R_AD1TDC2    ((uint32_t)0x01000000)    /*!< ADC Trigger 1 on Timer D compare 2 */
#define HRTIM_ADC1R_AD1TDC3    ((uint32_t)0x02000000)    /*!< ADC Trigger 1 on Timer D compare 3 */
#define HRTIM_ADC1R_AD1TDC4    ((uint32_t)0x04000000)    /*!< ADC Trigger 1 on Timer D compare 4 */
#define HRTIM_ADC1R_AD1TDPER   ((uint32_t)0x08000000)    /*!< ADC Trigger 1 on Timer D period */
#define HRTIM_ADC1R_AD1TEC2    ((uint32_t)0x10000000)    /*!< ADC Trigger 1 on Timer E compare 2 */
#define HRTIM_ADC1R_AD1TEC3    ((uint32_t)0x20000000)    /*!< ADC Trigger 1 on Timer E compare 3 */
#define HRTIM_ADC1R_AD1TEC4    ((uint32_t)0x40000000)    /*!< ADC Trigger 1 on Timer E compare 4 */
#define HRTIM_ADC1R_AD1TEPER   ((uint32_t)0x80000000)    /*!< ADC Trigger 1 on Timer E period */

/*******************  Bit definition for HRTIM_ADC2R register  ****************/
#define HRTIM_ADC2R_AD2MC1      ((uint32_t)0x00000001)    /*!< ADC Trigger 2 on master compare 1 */
#define HRTIM_ADC2R_AD2MC2      ((uint32_t)0x00000002)    /*!< ADC Trigger 2 on master compare 2 */
#define HRTIM_ADC2R_AD2MC3      ((uint32_t)0x00000004)    /*!< ADC Trigger 2 on master compare 3 */
#define HRTIM_ADC2R_AD2MC4      ((uint32_t)0x00000008)    /*!< ADC Trigger 2 on master compare 4 */
#define HRTIM_ADC2R_AD2MPER     ((uint32_t)0x00000010)    /*!< ADC Trigger 2 on master period */
#define HRTIM_ADC2R_AD2EEV6     ((uint32_t)0x00000020)    /*!< ADC Trigger 2 on external event 6 */
#define HRTIM_ADC2R_AD2EEV7     ((uint32_t)0x00000040)    /*!< ADC Trigger 2 on external event 7 */
#define HRTIM_ADC2R_AD2EEV8     ((uint32_t)0x00000080)    /*!< ADC Trigger 2 on external event 8 */
#define HRTIM_ADC2R_AD2EEV9     ((uint32_t)0x00000100)    /*!< ADC Trigger 2 on external event 9 */
#define HRTIM_ADC2R_AD2EEV10    ((uint32_t)0x00000200)    /*!< ADC Trigger 2 on external event 10 */
#define HRTIM_ADC2R_AD2TAC2     ((uint32_t)0x00000400)    /*!< ADC Trigger 2 on Timer A compare 2 */
#define HRTIM_ADC2R_AD2TAC3     ((uint32_t)0x00000800)    /*!< ADC Trigger 2 on Timer A compare 3 */
#define HRTIM_ADC2R_AD2TAC4     ((uint32_t)0x00001000)    /*!< ADC Trigger 2 on Timer A compare 4*/
#define HRTIM_ADC2R_AD2TAPER    ((uint32_t)0x00002000)    /*!< ADC Trigger 2 on Timer A period */
#define HRTIM_ADC2R_AD2TBC2     ((uint32_t)0x00004000)    /*!< ADC Trigger 2 on Timer B compare 2 */
#define HRTIM_ADC2R_AD2TBC3     ((uint32_t)0x00008000)    /*!< ADC Trigger 2 on Timer B compare 3 */
#define HRTIM_ADC2R_AD2TBC4     ((uint32_t)0x00010000)    /*!< ADC Trigger 2 on Timer B compare 4 */
#define HRTIM_ADC2R_AD2TBPER    ((uint32_t)0x00020000)    /*!< ADC Trigger 2 on Timer B period */
#define HRTIM_ADC2R_AD2TCC2     ((uint32_t)0x00040000)    /*!< ADC Trigger 2 on Timer C compare 2 */
#define HRTIM_ADC2R_AD2TCC3     ((uint32_t)0x00080000)    /*!< ADC Trigger 2 on Timer C compare 3 */
#define HRTIM_ADC2R_AD2TCC4     ((uint32_t)0x00100000)    /*!< ADC Trigger 2 on Timer C compare 4 */
#define HRTIM_ADC2R_AD2TCPER    ((uint32_t)0x00200000)    /*!< ADC Trigger 2 on Timer C period */
#define HRTIM_ADC2R_AD2TCRST    ((uint32_t)0x00400000)    /*!< ADC Trigger 2 on Timer C reset */
#define HRTIM_ADC2R_AD2TDC2     ((uint32_t)0x00800000)    /*!< ADC Trigger 2 on Timer D compare 2 */
#define HRTIM_ADC2R_AD2TDC3     ((uint32_t)0x01000000)    /*!< ADC Trigger 2 on Timer D compare 3 */
#define HRTIM_ADC2R_AD2TDC4     ((uint32_t)0x02000000)    /*!< ADC Trigger 2 on Timer D compare 4*/
#define HRTIM_ADC2R_AD2TDPER    ((uint32_t)0x04000000)    /*!< ADC Trigger 2 on Timer D period */
#define HRTIM_ADC2R_AD2TDRST    ((uint32_t)0x08000000)    /*!< ADC Trigger 2 on Timer D reset */
#define HRTIM_ADC2R_AD2TEC2     ((uint32_t)0x10000000)    /*!< ADC Trigger 2 on Timer E compare 2 */
#define HRTIM_ADC2R_AD2TEC3     ((uint32_t)0x20000000)    /*!< ADC Trigger 2 on Timer E compare 3 */
#define HRTIM_ADC2R_AD2TEC4     ((uint32_t)0x40000000)    /*!< ADC Trigger 2 on Timer E compare 4 */
#define HRTIM_ADC2R_AD2TERST    ((uint32_t)0x80000000)    /*!< ADC Trigger 2 on Timer E reset */

/*******************  Bit definition for HRTIM_ADC3R register  ****************/
#define HRTIM_ADC3R_AD3MC1     ((uint32_t)0x00000001)    /*!< ADC Trigger 3 on master compare 1 */
#define HRTIM_ADC3R_AD3MC2     ((uint32_t)0x00000002)    /*!< ADC Trigger 3 on master compare 2 */
#define HRTIM_ADC3R_AD3MC3     ((uint32_t)0x00000004)    /*!< ADC Trigger 3 on master compare 3 */
#define HRTIM_ADC3R_AD3MC4     ((uint32_t)0x00000008)    /*!< ADC Trigger 3 on master compare 4 */
#define HRTIM_ADC3R_AD3MPER    ((uint32_t)0x00000010)    /*!< ADC Trigger 3 on master period */
#define HRTIM_ADC3R_AD3EEV1    ((uint32_t)0x00000020)    /*!< ADC Trigger 3 on external event 1 */
#define HRTIM_ADC3R_AD3EEV2    ((uint32_t)0x00000040)    /*!< ADC Trigger 3 on external event 2 */
#define HRTIM_ADC3R_AD3EEV3    ((uint32_t)0x00000080)    /*!< ADC Trigger 3 on external event 3 */
#define HRTIM_ADC3R_AD3EEV4    ((uint32_t)0x00000100)    /*!< ADC Trigger 3 on external event 4 */
#define HRTIM_ADC3R_AD3EEV5    ((uint32_t)0x00000200)    /*!< ADC Trigger 3 on external event 5 */
#define HRTIM_ADC3R_AD3TAC2    ((uint32_t)0x00000400)    /*!< ADC Trigger 3 on Timer A compare 2 */
#define HRTIM_ADC3R_AD3TAC3    ((uint32_t)0x00000800)    /*!< ADC Trigger 3 on Timer A compare 3 */
#define HRTIM_ADC3R_AD3TAC4    ((uint32_t)0x00001000)    /*!< ADC Trigger 3 on Timer A compare 4 */
#define HRTIM_ADC3R_AD3TAPER   ((uint32_t)0x00002000)    /*!< ADC Trigger 3 on Timer A period */
#define HRTIM_ADC3R_AD3TARST   ((uint32_t)0x00004000)    /*!< ADC Trigger 3 on Timer A reset */
#define HRTIM_ADC3R_AD3TBC2    ((uint32_t)0x00008000)    /*!< ADC Trigger 3 on Timer B compare 2 */
#define HRTIM_ADC3R_AD3TBC3    ((uint32_t)0x00010000)    /*!< ADC Trigger 3 on Timer B compare 3 */
#define HRTIM_ADC3R_AD3TBC4    ((uint32_t)0x00020000)    /*!< ADC Trigger 3 on Timer B compare 4 */
#define HRTIM_ADC3R_AD3TBPER   ((uint32_t)0x00040000)    /*!< ADC Trigger 3 on Timer B period */
#define HRTIM_ADC3R_AD3TBRST   ((uint32_t)0x00080000)    /*!< ADC Trigger 3 on Timer B reset */
#define HRTIM_ADC3R_AD3TCC2    ((uint32_t)0x00100000)    /*!< ADC Trigger 3 on Timer C compare 2 */
#define HRTIM_ADC3R_AD3TCC3    ((uint32_t)0x00200000)    /*!< ADC Trigger 3 on Timer C compare 3 */
#define HRTIM_ADC3R_AD3TCC4    ((uint32_t)0x00400000)    /*!< ADC Trigger 3 on Timer C compare 4 */
#define HRTIM_ADC3R_AD3TCPER   ((uint32_t)0x00800000)    /*!< ADC Trigger 3 on Timer C period */
#define HRTIM_ADC3R_AD3TDC2    ((uint32_t)0x01000000)    /*!< ADC Trigger 3 on Timer D compare 2 */
#define HRTIM_ADC3R_AD3TDC3    ((uint32_t)0x02000000)    /*!< ADC Trigger 3 on Timer D compare 3 */
#define HRTIM_ADC3R_AD3TDC4    ((uint32_t)0x04000000)    /*!< ADC Trigger 3 on Timer D compare 4 */
#define HRTIM_ADC3R_AD3TDPER   ((uint32_t)0x08000000)    /*!< ADC Trigger 3 on Timer D period */
#define HRTIM_ADC3R_AD3TEC2    ((uint32_t)0x10000000)    /*!< ADC Trigger 3 on Timer E compare 2 */
#define HRTIM_ADC3R_AD3TEC3    ((uint32_t)0x20000000)    /*!< ADC Trigger 3 on Timer E compare 3 */
#define HRTIM_ADC3R_AD3TEC4    ((uint32_t)0x40000000)    /*!< ADC Trigger 3 on Timer E compare 4 */
#define HRTIM_ADC3R_AD3TEPER   ((uint32_t)0x80000000)    /*!< ADC Trigger 3 on Timer E period */

/*******************  Bit definition for HRTIM_ADC4R register  ****************/
#define HRTIM_ADC4R_AD4MC1      ((uint32_t)0x00000001)    /*!< ADC Trigger 4 on master compare 1 */
#define HRTIM_ADC4R_AD4MC2      ((uint32_t)0x00000002)    /*!< ADC Trigger 4 on master compare 2 */
#define HRTIM_ADC4R_AD4MC3      ((uint32_t)0x00000004)    /*!< ADC Trigger 4 on master compare 3 */
#define HRTIM_ADC4R_AD4MC4      ((uint32_t)0x00000008)    /*!< ADC Trigger 4 on master compare 4 */
#define HRTIM_ADC4R_AD4MPER     ((uint32_t)0x00000010)    /*!< ADC Trigger 4 on master period */
#define HRTIM_ADC4R_AD4EEV6     ((uint32_t)0x00000020)    /*!< ADC Trigger 4 on external event 6 */
#define HRTIM_ADC4R_AD4EEV7     ((uint32_t)0x00000040)    /*!< ADC Trigger 4 on external event 7 */
#define HRTIM_ADC4R_AD4EEV8     ((uint32_t)0x00000080)    /*!< ADC Trigger 4 on external event 8 */
#define HRTIM_ADC4R_AD4EEV9     ((uint32_t)0x00000100)    /*!< ADC Trigger 4 on external event 9 */
#define HRTIM_ADC4R_AD4EEV10    ((uint32_t)0x00000200)    /*!< ADC Trigger 4 on external event 10 */
#define HRTIM_ADC4R_AD4TAC2     ((uint32_t)0x00000400)    /*!< ADC Trigger 4 on Timer A compare 2 */
#define HRTIM_ADC4R_AD4TAC3     ((uint32_t)0x00000800)    /*!< ADC Trigger 4 on Timer A compare 3 */
#define HRTIM_ADC4R_AD4TAC4     ((uint32_t)0x00001000)    /*!< ADC Trigger 4 on Timer A compare 4*/
#define HRTIM_ADC4R_AD4TAPER    ((uint32_t)0x00002000)    /*!< ADC Trigger 4 on Timer A period */
#define HRTIM_ADC4R_AD4TBC2     ((uint32_t)0x00004000)    /*!< ADC Trigger 4 on Timer B compare 2 */
#define HRTIM_ADC4R_AD4TBC3     ((uint32_t)0x00008000)    /*!< ADC Trigger 4 on Timer B compare 3 */
#define HRTIM_ADC4R_AD4TBC4     ((uint32_t)0x00010000)    /*!< ADC Trigger 4 on Timer B compare 4 */
#define HRTIM_ADC4R_AD4TBPER    ((uint32_t)0x00020000)    /*!< ADC Trigger 4 on Timer B period */
#define HRTIM_ADC4R_AD4TCC2     ((uint32_t)0x00040000)    /*!< ADC Trigger 4 on Timer C compare 2 */
#define HRTIM_ADC4R_AD4TCC3     ((uint32_t)0x00080000)    /*!< ADC Trigger 4 on Timer C compare 3 */
#define HRTIM_ADC4R_AD4TCC4     ((uint32_t)0x00100000)    /*!< ADC Trigger 4 on Timer C compare 4 */
#define HRTIM_ADC4R_AD4TCPER    ((uint32_t)0x00200000)    /*!< ADC Trigger 4 on Timer C period */
#define HRTIM_ADC4R_AD4TCRST    ((uint32_t)0x00400000)    /*!< ADC Trigger 4 on Timer C reset */
#define HRTIM_ADC4R_AD4TDC2     ((uint32_t)0x00800000)    /*!< ADC Trigger 4 on Timer D compare 2 */
#define HRTIM_ADC4R_AD4TDC3     ((uint32_t)0x01000000)    /*!< ADC Trigger 4 on Timer D compare 3 */
#define HRTIM_ADC4R_AD4TDC4     ((uint32_t)0x02000000)    /*!< ADC Trigger 4 on Timer D compare 4*/
#define HRTIM_ADC4R_AD4TDPER    ((uint32_t)0x04000000)    /*!< ADC Trigger 4 on Timer D period */
#define HRTIM_ADC4R_AD4TDRST    ((uint32_t)0x08000000)    /*!< ADC Trigger 4 on Timer D reset */
#define HRTIM_ADC4R_AD4TEC2     ((uint32_t)0x10000000)    /*!< ADC Trigger 4 on Timer E compare 2 */
#define HRTIM_ADC4R_AD4TEC3     ((uint32_t)0x20000000)    /*!< ADC Trigger 4 on Timer E compare 3 */
#define HRTIM_ADC4R_AD4TEC4     ((uint32_t)0x40000000)    /*!< ADC Trigger 4 on Timer E compare 4 */
#define HRTIM_ADC4R_AD4TERST    ((uint32_t)0x80000000)    /*!< ADC Trigger 4 on Timer E reset */

/*******************  Bit definition for HRTIM_DLLCR register  ****************/
#define HRTIM_DLLCR_CAL         ((uint32_t)0x00000001)    /*!< DLL calibration start */ 
#define HRTIM_DLLCR_CALEN       ((uint32_t)0x00000002)    /*!< DLL calibration enable */  
#define HRTIM_DLLCR_CALRTE      ((uint32_t)0x0000000C)    /*!< DLL calibration rate */
#define HRTIM_DLLCR_CALRTE_0    ((uint32_t)0x00000004)    /*!< DLL calibration rate bit 0 */
#define HRTIM_DLLCR_CALRTE_1    ((uint32_t)0x00000008)    /*!< DLL calibration rate bit 1 */  

/*******************  Bit definition for HRTIM_FLTINR1 register  ***************/  
#define HRTIM_FLTINR1_FLT1E      ((uint32_t)0x00000001)    /*!< Fault 1 enable */ 
#define HRTIM_FLTINR1_FLT1P      ((uint32_t)0x00000002)    /*!< Fault 1 polarity */
#define HRTIM_FLTINR1_FLT1SRC    ((uint32_t)0x00000004)    /*!< Fault 1 source */
#define HRTIM_FLTINR1_FLT1F      ((uint32_t)0x00000078)    /*!< Fault 1 filter */
#define HRTIM_FLTINR1_FLT1F_0    ((uint32_t)0x00000008)    /*!< Fault 1 filter bit 0 */
#define HRTIM_FLTINR1_FLT1F_1    ((uint32_t)0x00000010)    /*!< Fault 1 filter bit 1 */
#define HRTIM_FLTINR1_FLT1F_2    ((uint32_t)0x00000020)    /*!< Fault 1 filter bit 2 */
#define HRTIM_FLTINR1_FLT1F_3    ((uint32_t)0x00000040)    /*!< Fault 1 filter bit 3 */
#define HRTIM_FLTINR1_FLT1LCK    ((uint32_t)0x00000080)    /*!< Fault 1 lock */ 

#define HRTIM_FLTINR1_FLT2E      ((uint32_t)0x00000100)    /*!< Fault 2 enable */ 
#define HRTIM_FLTINR1_FLT2P      ((uint32_t)0x00000200)    /*!< Fault 2 polarity */
#define HRTIM_FLTINR1_FLT2SRC    ((uint32_t)0x00000400)    /*!< Fault 2 source */
#define HRTIM_FLTINR1_FLT2F      ((uint32_t)0x00007800)    /*!< Fault 2 filter */
#define HRTIM_FLTINR1_FLT2F_0    ((uint32_t)0x00000800)    /*!< Fault 2 filter bit 0 */
#define HRTIM_FLTINR1_FLT2F_1    ((uint32_t)0x00001000)    /*!< Fault 2 filter bit 1 */
#define HRTIM_FLTINR1_FLT2F_2    ((uint32_t)0x00002000)    /*!< Fault 2 filter bit 2 */
#define HRTIM_FLTINR1_FLT2F_3    ((uint32_t)0x00004000)    /*!< Fault 2 filter bit 3 */
#define HRTIM_FLTINR1_FLT2LCK    ((uint32_t)0x00008000)    /*!< Fault 2 lock */ 

#define HRTIM_FLTINR1_FLT3E      ((uint32_t)0x00010000)    /*!< Fault 3 enable */ 
#define HRTIM_FLTINR1_FLT3P      ((uint32_t)0x00020000)    /*!< Fault 3 polarity */
#define HRTIM_FLTINR1_FLT3SRC    ((uint32_t)0x00040000)    /*!< Fault 3 source */
#define HRTIM_FLTINR1_FLT3F      ((uint32_t)0x00780000)    /*!< Fault 3 filter */
#define HRTIM_FLTINR1_FLT3F_0    ((uint32_t)0x00080000)    /*!< Fault 3 filter bit 0 */
#define HRTIM_FLTINR1_FLT3F_1    ((uint32_t)0x00100000)    /*!< Fault 3 filter bit 1 */
#define HRTIM_FLTINR1_FLT3F_2    ((uint32_t)0x00200000)    /*!< Fault 3 filter bit 2 */
#define HRTIM_FLTINR1_FLT3F_3    ((uint32_t)0x00400000)    /*!< Fault 3 filter bit 3 */
#define HRTIM_FLTINR1_FLT3LCK    ((uint32_t)0x00800000)    /*!< Fault 3 lock */ 

#define HRTIM_FLTINR1_FLT4E      ((uint32_t)0x01000000)    /*!< Fault 4 enable */ 
#define HRTIM_FLTINR1_FLT4P      ((uint32_t)0x02000000)    /*!< Fault 4 polarity */
#define HRTIM_FLTINR1_FLT4SRC    ((uint32_t)0x04000000)    /*!< Fault 4 source */
#define HRTIM_FLTINR1_FLT4F      ((uint32_t)0x78000000)    /*!< Fault 4 filter */
#define HRTIM_FLTINR1_FLT4F_0    ((uint32_t)0x08000000)    /*!< Fault 4 filter bit 0 */
#define HRTIM_FLTINR1_FLT4F_1    ((uint32_t)0x10000000)    /*!< Fault 4 filter bit 1 */
#define HRTIM_FLTINR1_FLT4F_2    ((uint32_t)0x20000000)    /*!< Fault 4 filter bit 2 */
#define HRTIM_FLTINR1_FLT4F_3    ((uint32_t)0x40000000)    /*!< Fault 4 filter bit 3 */
#define HRTIM_FLTINR1_FLT4LCK    ((uint32_t)0x80000000)    /*!< Fault 4 lock */

/*******************  Bit definition for HRTIM_FLTINR2 register  ***************/  
#define HRTIM_FLTINR2_FLT5E      ((uint32_t)0x00000001)    /*!< Fault 5 enable */ 
#define HRTIM_FLTINR2_FLT5P      ((uint32_t)0x00000002)    /*!< Fault 5 polarity */
#define HRTIM_FLTINR2_FLT5SRC    ((uint32_t)0x00000004)    /*!< Fault 5 source */
#define HRTIM_FLTINR2_FLT5F      ((uint32_t)0x00000078)    /*!< Fault 5 filter */
#define HRTIM_FLTINR2_FLT5F_0    ((uint32_t)0x00000008)    /*!< Fault 5 filter bit 0 */
#define HRTIM_FLTINR2_FLT5F_1    ((uint32_t)0x00000010)    /*!< Fault 5 filter bit 1 */
#define HRTIM_FLTINR2_FLT5F_2    ((uint32_t)0x00000020)    /*!< Fault 5 filter bit 2 */
#define HRTIM_FLTINR2_FLT5F_3    ((uint32_t)0x00000040)    /*!< Fault 5 filter bit 3 */
#define HRTIM_FLTINR2_FLT5LCK    ((uint32_t)0x00000080)    /*!< Fault 5 lock */
#define HRTIM_FLTINR2_FLTSD      ((uint32_t)0x03000000)    /*!< Fault sampling clock division */
#define HRTIM_FLTINR2_FLTSD_0    ((uint32_t)0x01000000)    /*!< Fault sampling clock division bit 0 */
#define HRTIM_FLTINR2_FLTSD_1    ((uint32_t)0x02000000)    /*!< Fault sampling clock division bit 1 */

/*******************  Bit definition for HRTIM_BDMUPR register  ***************/  
#define HRTIM_BDMUPR_MCR      ((uint32_t)0x00000001)    /*!< MCR register update enable */ 
#define HRTIM_BDMUPR_MICR     ((uint32_t)0x00000002)    /*!< MICR register update enable */ 
#define HRTIM_BDMUPR_MDIER    ((uint32_t)0x00000004)    /*!< MDIER register update enable */ 
#define HRTIM_BDMUPR_MCNT     ((uint32_t)0x00000008)    /*!< MCNT register update enable */ 
#define HRTIM_BDMUPR_MPER     ((uint32_t)0x00000010)    /*!< MPER register update enable */ 
#define HRTIM_BDMUPR_MREP     ((uint32_t)0x00000020)    /*!< MREP register update enable */ 
#define HRTIM_BDMUPR_MCMP1    ((uint32_t)0x00000040)    /*!< MCMP1 register update enable */ 
#define HRTIM_BDMUPR_MCMP2    ((uint32_t)0x00000080)    /*!< MCMP2 register update enable */ 
#define HRTIM_BDMUPR_MCMP3    ((uint32_t)0x00000100)    /*!< MCMP3 register update enable */ 
#define HRTIM_BDMUPR_MCMP4    ((uint32_t)0x00000200)    /*!< MPCMP4 register update enable */ 

/*******************  Bit definition for HRTIM_BDTUPR register  ***************/  
#define HRTIM_BDTUPR_TIMCR      ((uint32_t)0x00000001)    /*!<  TIMCR register update enable */ 
#define HRTIM_BDTUPR_TIMICR     ((uint32_t)0x00000002)    /*!<  TIMICR register update enable */ 
#define HRTIM_BDTUPR_TIMDIER    ((uint32_t)0x00000004)    /*!<  TIMDIER register update enable */ 
#define HRTIM_BDTUPR_TIMCNT     ((uint32_t)0x00000008)    /*!<  TIMCNT register update enable */ 
#define HRTIM_BDTUPR_TIMPER     ((uint32_t)0x00000010)    /*!<  TIMPER register update enable */ 
#define HRTIM_BDTUPR_TIMREP     ((uint32_t)0x00000020)    /*!<  TIMREP register update enable */ 
#define HRTIM_BDTUPR_TIMCMP1    ((uint32_t)0x00000040)    /*!<  TIMCMP1 register update enable */ 
#define HRTIM_BDTUPR_TIMCMP2    ((uint32_t)0x00000080)    /*!<  TIMCMP2 register update enable */ 
#define HRTIM_BDTUPR_TIMCMP3    ((uint32_t)0x00000100)    /*!<  TIMCMP3 register update enable */ 
#define HRTIM_BDTUPR_TIMCMP4    ((uint32_t)0x00000200)    /*!<  TIMCMP4 register update enable */ 
#define HRTIM_BDTUPR_TIMDTR     ((uint32_t)0x00000400)    /*!<  TIMDTR register update enable */ 
#define HRTIM_BDTUPR_TIMSET1R   ((uint32_t)0x00000800)    /*!<  TIMSET1R register update enable */ 
#define HRTIM_BDTUPR_TIMRST1R   ((uint32_t)0x00001000)    /*!<  TIMRST1R register update enable */ 
#define HRTIM_BDTUPR_TIMSET2R   ((uint32_t)0x00002000)    /*!<  TIMSET2R register update enable */ 
#define HRTIM_BDTUPR_TIMRST2R   ((uint32_t)0x00004000)    /*!<  TIMRST2R register update enable */ 
#define HRTIM_BDTUPR_TIMEEFR1   ((uint32_t)0x00008000)    /*!<  TIMEEFR1 register update enable */ 
#define HRTIM_BDTUPR_TIMEEFR2   ((uint32_t)0x00010000)    /*!<  TIMEEFR2 register update enable */ 
#define HRTIM_BDTUPR_TIMRSTR    ((uint32_t)0x00020000)    /*!<  TIMRSTR register update enable */ 
#define HRTIM_BDTUPR_TIMCHPR    ((uint32_t)0x00040000)    /*!<  TIMCHPR register update enable */ 
#define HRTIM_BDTUPR_TIMOUTR    ((uint32_t)0x00080000)    /*!<  TIMOUTR register update enable */ 
#define HRTIM_BDTUPR_TIMFLTR    ((uint32_t)0x00100000)    /*!<  TIMFLTR register update enable */ 

/*******************  Bit definition for HRTIM_BDMADR register  ***************/  
#define HRTIM_BDMADR_BDMADR      ((uint32_t)0xFFFFFFFF)    /*!<  Burst DMA Data register */ 

/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter SAR (ADC)               */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for ADC_ISR register  ********************/
#define ADC_ISR_ADRD          ((uint32_t)0x00000001) /*!< ADC Ready (ADRDY) flag  */
#define ADC_ISR_EOSMP         ((uint32_t)0x00000002) /*!< ADC End of Sampling flag */
#define ADC_ISR_EOC           ((uint32_t)0x00000004) /*!< ADC End of Regular Conversion flag */
#define ADC_ISR_EOS           ((uint32_t)0x00000008) /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_ISR_OVR           ((uint32_t)0x00000010) /*!< ADC overrun flag */
#define ADC_ISR_JEOC          ((uint32_t)0x00000020) /*!< ADC End of Injected Conversion flag */
#define ADC_ISR_JEOS          ((uint32_t)0x00000040) /*!< ADC End of Injected sequence of Conversions flag */
#define ADC_ISR_AWD1          ((uint32_t)0x00000080) /*!< ADC Analog watchdog 1 flag */
#define ADC_ISR_AWD2          ((uint32_t)0x00000100) /*!< ADC Analog watchdog 2 flag */
#define ADC_ISR_AWD3          ((uint32_t)0x00000200) /*!< ADC Analog watchdog 3 flag */
#define ADC_ISR_JQOVF         ((uint32_t)0x00000400) /*!< ADC Injected Context Queue Overflow flag */

/********************  Bit definition for ADC_IER register  ********************/
#define ADC_IER_RDY           ((uint32_t)0x00000001) /*!< ADC Ready (ADRDY) interrupt source */
#define ADC_IER_EOSMP         ((uint32_t)0x00000002) /*!< ADC End of Sampling interrupt source */
#define ADC_IER_EOC           ((uint32_t)0x00000004) /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IER_EOS           ((uint32_t)0x00000008) /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IER_OVR           ((uint32_t)0x00000010) /*!< ADC overrun interrupt source */
#define ADC_IER_JEOC          ((uint32_t)0x00000020) /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IER_JEOS          ((uint32_t)0x00000040) /*!< ADC End of Injected sequence of Conversions interrupt source */
#define ADC_IER_AWD1          ((uint32_t)0x00000080) /*!< ADC Analog watchdog 1 interrupt source */
#define ADC_IER_AWD2          ((uint32_t)0x00000100) /*!< ADC Analog watchdog 2 interrupt source */
#define ADC_IER_AWD3          ((uint32_t)0x00000200) /*!< ADC Analog watchdog 3 interrupt source */
#define ADC_IER_JQOVF         ((uint32_t)0x00000400) /*!< ADC Injected Context Queue Overflow interrupt source */

/********************  Bit definition for ADC_CR register  ********************/
#define ADC_CR_ADEN          ((uint32_t)0x00000001) /*!< ADC Enable control */
#define ADC_CR_ADDIS         ((uint32_t)0x00000002) /*!< ADC Disable command */
#define ADC_CR_ADSTART       ((uint32_t)0x00000004) /*!< ADC Start of Regular conversion */
#define ADC_CR_JADSTART      ((uint32_t)0x00000008) /*!< ADC Start of injected conversion */
#define ADC_CR_ADSTP         ((uint32_t)0x00000010) /*!< ADC Stop of Regular conversion */
#define ADC_CR_JADSTP        ((uint32_t)0x00000020) /*!< ADC Stop of injected conversion */
#define ADC_CR_ADVREGEN      ((uint32_t)0x30000000) /*!< ADC Voltage regulator Enable */
#define ADC_CR_ADVREGEN_0    ((uint32_t)0x10000000) /*!< ADC ADVREGEN bit 0 */
#define ADC_CR_ADVREGEN_1    ((uint32_t)0x20000000) /*!< ADC ADVREGEN bit 1 */
#define ADC_CR_ADCALDIF      ((uint32_t)0x40000000) /*!< ADC Differential Mode for calibration */
#define ADC_CR_ADCAL         ((uint32_t)0x80000000) /*!< ADC Calibration */

/********************  Bit definition for ADC_CFGR register  ********************/
#define ADC_CFGR_DMAEN     ((uint32_t)0x00000001) /*!< ADC DMA Enable */
#define ADC_CFGR_DMACFG    ((uint32_t)0x00000002) /*!< ADC DMA configuration */

#define ADC_CFGR_RES       ((uint32_t)0x00000018) /*!< ADC Data resolution */
#define ADC_CFGR_RES_0     ((uint32_t)0x00000008) /*!< ADC RES bit 0 */
#define ADC_CFGR_RES_1     ((uint32_t)0x00000010) /*!< ADC RES bit 1 */

#define ADC_CFGR_ALIGN     ((uint32_t)0x00000020) /*!< ADC Data Alignment */

#define ADC_CFGR_EXTSEL   ((uint32_t)0x000003C0) /*!< ADC External trigger selection for regular group */
#define ADC_CFGR_EXTSEL_0 ((uint32_t)0x00000040) /*!< ADC EXTSEL bit 0 */
#define ADC_CFGR_EXTSEL_1 ((uint32_t)0x00000080) /*!< ADC EXTSEL bit 1 */
#define ADC_CFGR_EXTSEL_2 ((uint32_t)0x00000100) /*!< ADC EXTSEL bit 2 */
#define ADC_CFGR_EXTSEL_3 ((uint32_t)0x00000200) /*!< ADC EXTSEL bit 3 */

#define ADC_CFGR_EXTEN     ((uint32_t)0x00000C00) /*!< ADC External trigger enable and polarity selection for regular channels */
#define ADC_CFGR_EXTEN_0   ((uint32_t)0x00000400) /*!< ADC EXTEN bit 0 */
#define ADC_CFGR_EXTEN_1   ((uint32_t)0x00000800) /*!< ADC EXTEN bit 1 */

#define ADC_CFGR_OVRMOD    ((uint32_t)0x00001000) /*!< ADC overrun mode */
#define ADC_CFGR_CONT      ((uint32_t)0x00002000) /*!< ADC Single/continuous conversion mode for regular conversion */
#define ADC_CFGR_AUTDLY    ((uint32_t)0x00004000) /*!< ADC Delayed conversion mode */
#define ADC_CFGR_DISCEN    ((uint32_t)0x00010000) /*!< ADC Discontinuous mode for regular channels */

#define ADC_CFGR_DISCNUM   ((uint32_t)0x000E0000) /*!< ADC Discontinuous mode channel count */
#define ADC_CFGR_DISCNUM_0 ((uint32_t)0x00020000) /*!< ADC DISCNUM bit 0 */
#define ADC_CFGR_DISCNUM_1 ((uint32_t)0x00040000) /*!< ADC DISCNUM bit 1 */
#define ADC_CFGR_DISCNUM_2 ((uint32_t)0x00080000) /*!< ADC DISCNUM bit 2 */

#define ADC_CFGR_JDISCEN   ((uint32_t)0x00100000) /*!< ADC Discontinuous mode on injected channels */
#define ADC_CFGR_JQM       ((uint32_t)0x00200000) /*!< ADC JSQR Queue mode */
#define ADC_CFGR_AWD1SGL   ((uint32_t)0x00400000) /*!< Enable the watchdog 1 on a single channel or on all channels */
#define ADC_CFGR_AWD1EN    ((uint32_t)0x00800000) /*!< ADC Analog watchdog 1 enable on regular Channels */
#define ADC_CFGR_JAWD1EN   ((uint32_t)0x01000000) /*!< ADC Analog watchdog 1 enable on injected Channels */
#define ADC_CFGR_JAUTO     ((uint32_t)0x02000000) /*!< ADC Automatic injected group conversion */

#define ADC_CFGR_AWD1CH    ((uint32_t)0x7C000000) /*!< ADC Analog watchdog 1 Channel selection */
#define ADC_CFGR_AWD1CH_0  ((uint32_t)0x04000000) /*!< ADC AWD1CH bit 0 */
#define ADC_CFGR_AWD1CH_1  ((uint32_t)0x08000000) /*!< ADC AWD1CH bit 1  */
#define ADC_CFGR_AWD1CH_2  ((uint32_t)0x10000000) /*!< ADC AWD1CH bit 2  */
#define ADC_CFGR_AWD1CH_3  ((uint32_t)0x20000000) /*!< ADC AWD1CH bit 3  */
#define ADC_CFGR_AWD1CH_4  ((uint32_t)0x40000000) /*!< ADC AWD1CH bit 4  */

/********************  Bit definition for ADC_SMPR1 register  ********************/
#define ADC_SMPR1_SMP0     ((uint32_t)0x00000007) /*!< ADC Channel 0 Sampling time selection  */
#define ADC_SMPR1_SMP0_0   ((uint32_t)0x00000001) /*!< ADC SMP0 bit 0 */
#define ADC_SMPR1_SMP0_1   ((uint32_t)0x00000002) /*!< ADC SMP0 bit 1 */
#define ADC_SMPR1_SMP0_2   ((uint32_t)0x00000004) /*!< ADC SMP0 bit 2 */

#define ADC_SMPR1_SMP1     ((uint32_t)0x00000038) /*!< ADC Channel 1 Sampling time selection  */
#define ADC_SMPR1_SMP1_0   ((uint32_t)0x00000008) /*!< ADC SMP1 bit 0 */
#define ADC_SMPR1_SMP1_1   ((uint32_t)0x00000010) /*!< ADC SMP1 bit 1 */
#define ADC_SMPR1_SMP1_2   ((uint32_t)0x00000020) /*!< ADC SMP1 bit 2 */

#define ADC_SMPR1_SMP2     ((uint32_t)0x000001C0) /*!< ADC Channel 2 Sampling time selection  */
#define ADC_SMPR1_SMP2_0   ((uint32_t)0x00000040) /*!< ADC SMP2 bit 0 */
#define ADC_SMPR1_SMP2_1   ((uint32_t)0x00000080) /*!< ADC SMP2 bit 1 */
#define ADC_SMPR1_SMP2_2   ((uint32_t)0x00000100) /*!< ADC SMP2 bit 2 */

#define ADC_SMPR1_SMP3     ((uint32_t)0x00000E00) /*!< ADC Channel 3 Sampling time selection  */
#define ADC_SMPR1_SMP3_0   ((uint32_t)0x00000200) /*!< ADC SMP3 bit 0 */
#define ADC_SMPR1_SMP3_1   ((uint32_t)0x00000400) /*!< ADC SMP3 bit 1 */
#define ADC_SMPR1_SMP3_2   ((uint32_t)0x00000800) /*!< ADC SMP3 bit 2 */

#define ADC_SMPR1_SMP4     ((uint32_t)0x00007000) /*!< ADC Channel 4 Sampling time selection  */
#define ADC_SMPR1_SMP4_0   ((uint32_t)0x00001000) /*!< ADC SMP4 bit 0 */
#define ADC_SMPR1_SMP4_1   ((uint32_t)0x00002000) /*!< ADC SMP4 bit 1 */
#define ADC_SMPR1_SMP4_2   ((uint32_t)0x00004000) /*!< ADC SMP4 bit 2 */

#define ADC_SMPR1_SMP5     ((uint32_t)0x00038000) /*!< ADC Channel 5 Sampling time selection  */
#define ADC_SMPR1_SMP5_0   ((uint32_t)0x00008000) /*!< ADC SMP5 bit 0 */
#define ADC_SMPR1_SMP5_1   ((uint32_t)0x00010000) /*!< ADC SMP5 bit 1 */
#define ADC_SMPR1_SMP5_2   ((uint32_t)0x00020000) /*!< ADC SMP5 bit 2 */

#define ADC_SMPR1_SMP6     ((uint32_t)0x001C0000) /*!< ADC Channel 6 Sampling time selection  */
#define ADC_SMPR1_SMP6_0   ((uint32_t)0x00040000) /*!< ADC SMP6 bit 0 */
#define ADC_SMPR1_SMP6_1   ((uint32_t)0x00080000) /*!< ADC SMP6 bit 1 */
#define ADC_SMPR1_SMP6_2   ((uint32_t)0x00100000) /*!< ADC SMP6 bit 2 */

#define ADC_SMPR1_SMP7     ((uint32_t)0x00E00000) /*!< ADC Channel 7 Sampling time selection  */
#define ADC_SMPR1_SMP7_0   ((uint32_t)0x00200000) /*!< ADC SMP7 bit 0 */
#define ADC_SMPR1_SMP7_1   ((uint32_t)0x00400000) /*!< ADC SMP7 bit 1 */
#define ADC_SMPR1_SMP7_2   ((uint32_t)0x00800000) /*!< ADC SMP7 bit 2 */

#define ADC_SMPR1_SMP8     ((uint32_t)0x07000000) /*!< ADC Channel 8 Sampling time selection  */
#define ADC_SMPR1_SMP8_0   ((uint32_t)0x01000000) /*!< ADC SMP8 bit 0 */
#define ADC_SMPR1_SMP8_1   ((uint32_t)0x02000000) /*!< ADC SMP8 bit 1 */
#define ADC_SMPR1_SMP8_2   ((uint32_t)0x04000000) /*!< ADC SMP8 bit 2 */

#define ADC_SMPR1_SMP9     ((uint32_t)0x38000000) /*!< ADC Channel 9 Sampling time selection  */
#define ADC_SMPR1_SMP9_0   ((uint32_t)0x08000000) /*!< ADC SMP9 bit 0 */
#define ADC_SMPR1_SMP9_1   ((uint32_t)0x10000000) /*!< ADC SMP9 bit 1 */
#define ADC_SMPR1_SMP9_2   ((uint32_t)0x20000000) /*!< ADC SMP9 bit 2 */

/********************  Bit definition for ADC_SMPR2 register  ********************/
#define ADC_SMPR2_SMP10     ((uint32_t)0x00000007) /*!< ADC Channel 10 Sampling time selection  */
#define ADC_SMPR2_SMP10_0   ((uint32_t)0x00000001) /*!< ADC SMP10 bit 0 */
#define ADC_SMPR2_SMP10_1   ((uint32_t)0x00000002) /*!< ADC SMP10 bit 1 */
#define ADC_SMPR2_SMP10_2   ((uint32_t)0x00000004) /*!< ADC SMP10 bit 2 */

#define ADC_SMPR2_SMP11     ((uint32_t)0x00000038) /*!< ADC Channel 11 Sampling time selection  */
#define ADC_SMPR2_SMP11_0   ((uint32_t)0x00000008) /*!< ADC SMP11 bit 0 */
#define ADC_SMPR2_SMP11_1   ((uint32_t)0x00000010) /*!< ADC SMP11 bit 1 */
#define ADC_SMPR2_SMP11_2   ((uint32_t)0x00000020) /*!< ADC SMP11 bit 2 */

#define ADC_SMPR2_SMP12     ((uint32_t)0x000001C0) /*!< ADC Channel 12 Sampling time selection  */
#define ADC_SMPR2_SMP12_0   ((uint32_t)0x00000040) /*!< ADC SMP12 bit 0 */
#define ADC_SMPR2_SMP12_1   ((uint32_t)0x00000080) /*!< ADC SMP12 bit 1 */
#define ADC_SMPR2_SMP12_2   ((uint32_t)0x00000100) /*!< ADC SMP12 bit 2 */

#define ADC_SMPR2_SMP13     ((uint32_t)0x00000E00) /*!< ADC Channel 13 Sampling time selection  */
#define ADC_SMPR2_SMP13_0   ((uint32_t)0x00000200) /*!< ADC SMP13 bit 0 */
#define ADC_SMPR2_SMP13_1   ((uint32_t)0x00000400) /*!< ADC SMP13 bit 1 */
#define ADC_SMPR2_SMP13_2   ((uint32_t)0x00000800) /*!< ADC SMP13 bit 2 */

#define ADC_SMPR2_SMP14     ((uint32_t)0x00007000) /*!< ADC Channel 14 Sampling time selection  */
#define ADC_SMPR2_SMP14_0   ((uint32_t)0x00001000) /*!< ADC SMP14 bit 0 */
#define ADC_SMPR2_SMP14_1   ((uint32_t)0x00002000) /*!< ADC SMP14 bit 1 */
#define ADC_SMPR2_SMP14_2   ((uint32_t)0x00004000) /*!< ADC SMP14 bit 2 */

#define ADC_SMPR2_SMP15     ((uint32_t)0x00038000) /*!< ADC Channel 15 Sampling time selection  */
#define ADC_SMPR2_SMP15_0   ((uint32_t)0x00008000) /*!< ADC SMP15 bit 0 */
#define ADC_SMPR2_SMP15_1   ((uint32_t)0x00010000) /*!< ADC SMP15 bit 1 */
#define ADC_SMPR2_SMP15_2   ((uint32_t)0x00020000) /*!< ADC SMP15 bit 2 */

#define ADC_SMPR2_SMP16     ((uint32_t)0x001C0000) /*!< ADC Channel 16 Sampling time selection  */
#define ADC_SMPR2_SMP16_0   ((uint32_t)0x00040000) /*!< ADC SMP16 bit 0 */
#define ADC_SMPR2_SMP16_1   ((uint32_t)0x00080000) /*!< ADC SMP16 bit 1 */
#define ADC_SMPR2_SMP16_2   ((uint32_t)0x00100000) /*!< ADC SMP16 bit 2 */

#define ADC_SMPR2_SMP17     ((uint32_t)0x00E00000) /*!< ADC Channel 17 Sampling time selection  */
#define ADC_SMPR2_SMP17_0   ((uint32_t)0x00200000) /*!< ADC SMP17 bit 0 */
#define ADC_SMPR2_SMP17_1   ((uint32_t)0x00400000) /*!< ADC SMP17 bit 1 */
#define ADC_SMPR2_SMP17_2   ((uint32_t)0x00800000) /*!< ADC SMP17 bit 2 */

#define ADC_SMPR2_SMP18     ((uint32_t)0x07000000) /*!< ADC Channel 18 Sampling time selection  */
#define ADC_SMPR2_SMP18_0   ((uint32_t)0x01000000) /*!< ADC SMP18 bit 0 */
#define ADC_SMPR2_SMP18_1   ((uint32_t)0x02000000) /*!< ADC SMP18 bit 1 */
#define ADC_SMPR2_SMP18_2   ((uint32_t)0x04000000) /*!< ADC SMP18 bit 2 */

/********************  Bit definition for ADC_TR1 register  ********************/
#define ADC_TR1_LT1         ((uint32_t)0x00000FFF) /*!< ADC Analog watchdog 1 lower threshold */
#define ADC_TR1_LT1_0       ((uint32_t)0x00000001) /*!< ADC LT1 bit 0 */
#define ADC_TR1_LT1_1       ((uint32_t)0x00000002) /*!< ADC LT1 bit 1 */
#define ADC_TR1_LT1_2       ((uint32_t)0x00000004) /*!< ADC LT1 bit 2 */
#define ADC_TR1_LT1_3       ((uint32_t)0x00000008) /*!< ADC LT1 bit 3 */
#define ADC_TR1_LT1_4       ((uint32_t)0x00000010) /*!< ADC LT1 bit 4 */
#define ADC_TR1_LT1_5       ((uint32_t)0x00000020) /*!< ADC LT1 bit 5 */
#define ADC_TR1_LT1_6       ((uint32_t)0x00000040) /*!< ADC LT1 bit 6 */
#define ADC_TR1_LT1_7       ((uint32_t)0x00000080) /*!< ADC LT1 bit 7 */
#define ADC_TR1_LT1_8       ((uint32_t)0x00000100) /*!< ADC LT1 bit 8 */
#define ADC_TR1_LT1_9       ((uint32_t)0x00000200) /*!< ADC LT1 bit 9 */
#define ADC_TR1_LT1_10      ((uint32_t)0x00000400) /*!< ADC LT1 bit 10 */
#define ADC_TR1_LT1_11      ((uint32_t)0x00000800) /*!< ADC LT1 bit 11 */

#define ADC_TR1_HT1         ((uint32_t)0x0FFF0000) /*!< ADC Analog watchdog 1 higher threshold */
#define ADC_TR1_HT1_0       ((uint32_t)0x00010000) /*!< ADC HT1 bit 0 */
#define ADC_TR1_HT1_1       ((uint32_t)0x00020000) /*!< ADC HT1 bit 1 */
#define ADC_TR1_HT1_2       ((uint32_t)0x00040000) /*!< ADC HT1 bit 2 */
#define ADC_TR1_HT1_3       ((uint32_t)0x00080000) /*!< ADC HT1 bit 3 */
#define ADC_TR1_HT1_4       ((uint32_t)0x00100000) /*!< ADC HT1 bit 4 */
#define ADC_TR1_HT1_5       ((uint32_t)0x00200000) /*!< ADC HT1 bit 5 */
#define ADC_TR1_HT1_6       ((uint32_t)0x00400000) /*!< ADC HT1 bit 6 */
#define ADC_TR1_HT1_7       ((uint32_t)0x00800000) /*!< ADC HT1 bit 7 */
#define ADC_TR1_HT1_8       ((uint32_t)0x01000000) /*!< ADC HT1 bit 8 */
#define ADC_TR1_HT1_9       ((uint32_t)0x02000000) /*!< ADC HT1 bit 9 */
#define ADC_TR1_HT1_10      ((uint32_t)0x04000000) /*!< ADC HT1 bit 10 */
#define ADC_TR1_HT1_11      ((uint32_t)0x08000000) /*!< ADC HT1 bit 11 */

/********************  Bit definition for ADC_TR2 register  ********************/
#define ADC_TR2_LT2         ((uint32_t)0x000000FF) /*!< ADC Analog watchdog 2 lower threshold */
#define ADC_TR2_LT2_0       ((uint32_t)0x00000001) /*!< ADC LT2 bit 0 */
#define ADC_TR2_LT2_1       ((uint32_t)0x00000002) /*!< ADC LT2 bit 1 */
#define ADC_TR2_LT2_2       ((uint32_t)0x00000004) /*!< ADC LT2 bit 2 */
#define ADC_TR2_LT2_3       ((uint32_t)0x00000008) /*!< ADC LT2 bit 3 */
#define ADC_TR2_LT2_4       ((uint32_t)0x00000010) /*!< ADC LT2 bit 4 */
#define ADC_TR2_LT2_5       ((uint32_t)0x00000020) /*!< ADC LT2 bit 5 */
#define ADC_TR2_LT2_6       ((uint32_t)0x00000040) /*!< ADC LT2 bit 6 */
#define ADC_TR2_LT2_7       ((uint32_t)0x00000080) /*!< ADC LT2 bit 7 */

#define ADC_TR2_HT2         ((uint32_t)0x00FF0000) /*!< ADC Analog watchdog 2 higher threshold */
#define ADC_TR2_HT2_0       ((uint32_t)0x00010000) /*!< ADC HT2 bit 0 */
#define ADC_TR2_HT2_1       ((uint32_t)0x00020000) /*!< ADC HT2 bit 1 */
#define ADC_TR2_HT2_2       ((uint32_t)0x00040000) /*!< ADC HT2 bit 2 */
#define ADC_TR2_HT2_3       ((uint32_t)0x00080000) /*!< ADC HT2 bit 3 */
#define ADC_TR2_HT2_4       ((uint32_t)0x00100000) /*!< ADC HT2 bit 4 */
#define ADC_TR2_HT2_5       ((uint32_t)0x00200000) /*!< ADC HT2 bit 5 */
#define ADC_TR2_HT2_6       ((uint32_t)0x00400000) /*!< ADC HT2 bit 6 */
#define ADC_TR2_HT2_7       ((uint32_t)0x00800000) /*!< ADC HT2 bit 7 */

/********************  Bit definition for ADC_TR3 register  ********************/
#define ADC_TR3_LT3         ((uint32_t)0x000000FF) /*!< ADC Analog watchdog 3 lower threshold */
#define ADC_TR3_LT3_0       ((uint32_t)0x00000001) /*!< ADC LT3 bit 0 */
#define ADC_TR3_LT3_1       ((uint32_t)0x00000002) /*!< ADC LT3 bit 1 */
#define ADC_TR3_LT3_2       ((uint32_t)0x00000004) /*!< ADC LT3 bit 2 */
#define ADC_TR3_LT3_3       ((uint32_t)0x00000008) /*!< ADC LT3 bit 3 */
#define ADC_TR3_LT3_4       ((uint32_t)0x00000010) /*!< ADC LT3 bit 4 */
#define ADC_TR3_LT3_5       ((uint32_t)0x00000020) /*!< ADC LT3 bit 5 */
#define ADC_TR3_LT3_6       ((uint32_t)0x00000040) /*!< ADC LT3 bit 6 */
#define ADC_TR3_LT3_7       ((uint32_t)0x00000080) /*!< ADC LT3 bit 7 */

#define ADC_TR3_HT3         ((uint32_t)0x00FF0000) /*!< ADC Analog watchdog 3 higher threshold */
#define ADC_TR3_HT3_0       ((uint32_t)0x00010000) /*!< ADC HT3 bit 0 */
#define ADC_TR3_HT3_1       ((uint32_t)0x00020000) /*!< ADC HT3 bit 1 */
#define ADC_TR3_HT3_2       ((uint32_t)0x00040000) /*!< ADC HT3 bit 2 */
#define ADC_TR3_HT3_3       ((uint32_t)0x00080000) /*!< ADC HT3 bit 3 */
#define ADC_TR3_HT3_4       ((uint32_t)0x00100000) /*!< ADC HT3 bit 4 */
#define ADC_TR3_HT3_5       ((uint32_t)0x00200000) /*!< ADC HT3 bit 5 */
#define ADC_TR3_HT3_6       ((uint32_t)0x00400000) /*!< ADC HT3 bit 6 */
#define ADC_TR3_HT3_7       ((uint32_t)0x00800000) /*!< ADC HT3 bit 7 */

/********************  Bit definition for ADC_SQR1 register  ********************/
#define ADC_SQR1_L          ((uint32_t)0x0000000F) /*!< ADC regular channel sequence length */
#define ADC_SQR1_L_0        ((uint32_t)0x00000001) /*!< ADC L bit 0 */
#define ADC_SQR1_L_1        ((uint32_t)0x00000002) /*!< ADC L bit 1 */
#define ADC_SQR1_L_2        ((uint32_t)0x00000004) /*!< ADC L bit 2 */
#define ADC_SQR1_L_3        ((uint32_t)0x00000008) /*!< ADC L bit 3 */

#define ADC_SQR1_SQ1        ((uint32_t)0x000007C0) /*!< ADC 1st conversion in regular sequence */
#define ADC_SQR1_SQ1_0      ((uint32_t)0x00000040) /*!< ADC SQ1 bit 0 */
#define ADC_SQR1_SQ1_1      ((uint32_t)0x00000080) /*!< ADC SQ1 bit 1 */
#define ADC_SQR1_SQ1_2      ((uint32_t)0x00000100) /*!< ADC SQ1 bit 2 */
#define ADC_SQR1_SQ1_3      ((uint32_t)0x00000200) /*!< ADC SQ1 bit 3 */
#define ADC_SQR1_SQ1_4      ((uint32_t)0x00000400) /*!< ADC SQ1 bit 4 */

#define ADC_SQR1_SQ2        ((uint32_t)0x0001F000) /*!< ADC 2nd conversion in regular sequence */
#define ADC_SQR1_SQ2_0      ((uint32_t)0x00001000) /*!< ADC SQ2 bit 0 */
#define ADC_SQR1_SQ2_1      ((uint32_t)0x00002000) /*!< ADC SQ2 bit 1 */
#define ADC_SQR1_SQ2_2      ((uint32_t)0x00004000) /*!< ADC SQ2 bit 2 */
#define ADC_SQR1_SQ2_3      ((uint32_t)0x00008000) /*!< ADC SQ2 bit 3 */
#define ADC_SQR1_SQ2_4      ((uint32_t)0x00010000) /*!< ADC SQ2 bit 4 */

#define ADC_SQR1_SQ3        ((uint32_t)0x007C0000) /*!< ADC 3rd conversion in regular sequence */
#define ADC_SQR1_SQ3_0      ((uint32_t)0x00040000) /*!< ADC SQ3 bit 0 */
#define ADC_SQR1_SQ3_1      ((uint32_t)0x00080000) /*!< ADC SQ3 bit 1 */
#define ADC_SQR1_SQ3_2      ((uint32_t)0x00100000) /*!< ADC SQ3 bit 2 */
#define ADC_SQR1_SQ3_3      ((uint32_t)0x00200000) /*!< ADC SQ3 bit 3 */
#define ADC_SQR1_SQ3_4      ((uint32_t)0x00400000) /*!< ADC SQ3 bit 4 */

#define ADC_SQR1_SQ4        ((uint32_t)0x1F000000) /*!< ADC 4th conversion in regular sequence */
#define ADC_SQR1_SQ4_0      ((uint32_t)0x01000000) /*!< ADC SQ4 bit 0 */
#define ADC_SQR1_SQ4_1      ((uint32_t)0x02000000) /*!< ADC SQ4 bit 1 */
#define ADC_SQR1_SQ4_2      ((uint32_t)0x04000000) /*!< ADC SQ4 bit 2 */
#define ADC_SQR1_SQ4_3      ((uint32_t)0x08000000) /*!< ADC SQ4 bit 3 */
#define ADC_SQR1_SQ4_4      ((uint32_t)0x10000000) /*!< ADC SQ4 bit 4 */

/********************  Bit definition for ADC_SQR2 register  ********************/
#define ADC_SQR2_SQ5        ((uint32_t)0x0000001F) /*!< ADC 5th conversion in regular sequence */
#define ADC_SQR2_SQ5_0      ((uint32_t)0x00000001) /*!< ADC SQ5 bit 0 */
#define ADC_SQR2_SQ5_1      ((uint32_t)0x00000002) /*!< ADC SQ5 bit 1 */
#define ADC_SQR2_SQ5_2      ((uint32_t)0x00000004) /*!< ADC SQ5 bit 2 */
#define ADC_SQR2_SQ5_3      ((uint32_t)0x00000008) /*!< ADC SQ5 bit 3 */
#define ADC_SQR2_SQ5_4      ((uint32_t)0x00000010) /*!< ADC SQ5 bit 4 */

#define ADC_SQR2_SQ6        ((uint32_t)0x000007C0) /*!< ADC 6th conversion in regular sequence */
#define ADC_SQR2_SQ6_0      ((uint32_t)0x00000040) /*!< ADC SQ6 bit 0 */
#define ADC_SQR2_SQ6_1      ((uint32_t)0x00000080) /*!< ADC SQ6 bit 1 */
#define ADC_SQR2_SQ6_2      ((uint32_t)0x00000100) /*!< ADC SQ6 bit 2 */
#define ADC_SQR2_SQ6_3      ((uint32_t)0x00000200) /*!< ADC SQ6 bit 3 */
#define ADC_SQR2_SQ6_4      ((uint32_t)0x00000400) /*!< ADC SQ6 bit 4 */

#define ADC_SQR2_SQ7        ((uint32_t)0x0001F000) /*!< ADC 7th conversion in regular sequence */
#define ADC_SQR2_SQ7_0      ((uint32_t)0x00001000) /*!< ADC SQ7 bit 0 */
#define ADC_SQR2_SQ7_1      ((uint32_t)0x00002000) /*!< ADC SQ7 bit 1 */
#define ADC_SQR2_SQ7_2      ((uint32_t)0x00004000) /*!< ADC SQ7 bit 2 */
#define ADC_SQR2_SQ7_3      ((uint32_t)0x00008000) /*!< ADC SQ7 bit 3 */
#define ADC_SQR2_SQ7_4      ((uint32_t)0x00010000) /*!< ADC SQ7 bit 4 */

#define ADC_SQR2_SQ8        ((uint32_t)0x007C0000) /*!< ADC 8th conversion in regular sequence */
#define ADC_SQR2_SQ8_0      ((uint32_t)0x00040000) /*!< ADC SQ8 bit 0 */
#define ADC_SQR2_SQ8_1      ((uint32_t)0x00080000) /*!< ADC SQ8 bit 1 */
#define ADC_SQR2_SQ8_2      ((uint32_t)0x00100000) /*!< ADC SQ8 bit 2 */
#define ADC_SQR2_SQ8_3      ((uint32_t)0x00200000) /*!< ADC SQ8 bit 3 */
#define ADC_SQR2_SQ8_4      ((uint32_t)0x00400000) /*!< ADC SQ8 bit 4 */

#define ADC_SQR2_SQ9        ((uint32_t)0x1F000000) /*!< ADC 9th conversion in regular sequence */
#define ADC_SQR2_SQ9_0      ((uint32_t)0x01000000) /*!< ADC SQ9 bit 0 */
#define ADC_SQR2_SQ9_1      ((uint32_t)0x02000000) /*!< ADC SQ9 bit 1 */
#define ADC_SQR2_SQ9_2      ((uint32_t)0x04000000) /*!< ADC SQ9 bit 2 */
#define ADC_SQR2_SQ9_3      ((uint32_t)0x08000000) /*!< ADC SQ9 bit 3 */
#define ADC_SQR2_SQ9_4      ((uint32_t)0x10000000) /*!< ADC SQ9 bit 4 */

/********************  Bit definition for ADC_SQR3 register  ********************/
#define ADC_SQR3_SQ10       ((uint32_t)0x0000001F) /*!< ADC 10th conversion in regular sequence */
#define ADC_SQR3_SQ10_0     ((uint32_t)0x00000001) /*!< ADC SQ10 bit 0 */
#define ADC_SQR3_SQ10_1     ((uint32_t)0x00000002) /*!< ADC SQ10 bit 1 */
#define ADC_SQR3_SQ10_2     ((uint32_t)0x00000004) /*!< ADC SQ10 bit 2 */
#define ADC_SQR3_SQ10_3     ((uint32_t)0x00000008) /*!< ADC SQ10 bit 3 */
#define ADC_SQR3_SQ10_4     ((uint32_t)0x00000010) /*!< ADC SQ10 bit 4 */

#define ADC_SQR3_SQ11       ((uint32_t)0x000007C0) /*!< ADC 11th conversion in regular sequence */
#define ADC_SQR3_SQ11_0     ((uint32_t)0x00000040) /*!< ADC SQ11 bit 0 */
#define ADC_SQR3_SQ11_1     ((uint32_t)0x00000080) /*!< ADC SQ11 bit 1 */
#define ADC_SQR3_SQ11_2     ((uint32_t)0x00000100) /*!< ADC SQ11 bit 2 */
#define ADC_SQR3_SQ11_3     ((uint32_t)0x00000200) /*!< ADC SQ11 bit 3 */
#define ADC_SQR3_SQ11_4     ((uint32_t)0x00000400) /*!< ADC SQ11 bit 4 */

#define ADC_SQR3_SQ12       ((uint32_t)0x0001F000) /*!< ADC 12th conversion in regular sequence */
#define ADC_SQR3_SQ12_0     ((uint32_t)0x00001000) /*!< ADC SQ12 bit 0 */
#define ADC_SQR3_SQ12_1     ((uint32_t)0x00002000) /*!< ADC SQ12 bit 1 */
#define ADC_SQR3_SQ12_2     ((uint32_t)0x00004000) /*!< ADC SQ12 bit 2 */
#define ADC_SQR3_SQ12_3     ((uint32_t)0x00008000) /*!< ADC SQ12 bit 3 */
#define ADC_SQR3_SQ12_4     ((uint32_t)0x00010000) /*!< ADC SQ12 bit 4 */

#define ADC_SQR3_SQ13       ((uint32_t)0x007C0000) /*!< ADC 13th conversion in regular sequence */
#define ADC_SQR3_SQ13_0     ((uint32_t)0x00040000) /*!< ADC SQ13 bit 0 */
#define ADC_SQR3_SQ13_1     ((uint32_t)0x00080000) /*!< ADC SQ13 bit 1 */
#define ADC_SQR3_SQ13_2     ((uint32_t)0x00100000) /*!< ADC SQ13 bit 2 */
#define ADC_SQR3_SQ13_3     ((uint32_t)0x00200000) /*!< ADC SQ13 bit 3 */
#define ADC_SQR3_SQ13_4     ((uint32_t)0x00400000) /*!< ADC SQ13 bit 4 */

#define ADC_SQR3_SQ14       ((uint32_t)0x1F000000) /*!< ADC 14th conversion in regular sequence */
#define ADC_SQR3_SQ14_0     ((uint32_t)0x01000000) /*!< ADC SQ14 bit 0 */
#define ADC_SQR3_SQ14_1     ((uint32_t)0x02000000) /*!< ADC SQ14 bit 1 */
#define ADC_SQR3_SQ14_2     ((uint32_t)0x04000000) /*!< ADC SQ14 bit 2 */
#define ADC_SQR3_SQ14_3     ((uint32_t)0x08000000) /*!< ADC SQ14 bit 3 */
#define ADC_SQR3_SQ14_4     ((uint32_t)0x10000000) /*!< ADC SQ14 bit 4 */

/********************  Bit definition for ADC_SQR4 register  ********************/
#define ADC_SQR4_SQ15       ((uint32_t)0x0000001F) /*!< ADC 15th conversion in regular sequence */
#define ADC_SQR4_SQ15_0     ((uint32_t)0x00000001) /*!< ADC SQ15 bit 0 */
#define ADC_SQR4_SQ15_1     ((uint32_t)0x00000002) /*!< ADC SQ15 bit 1 */
#define ADC_SQR4_SQ15_2     ((uint32_t)0x00000004) /*!< ADC SQ15 bit 2 */
#define ADC_SQR4_SQ15_3     ((uint32_t)0x00000008) /*!< ADC SQ15 bit 3 */
#define ADC_SQR4_SQ15_4     ((uint32_t)0x00000010) /*!< ADC SQ105 bit 4 */

#define ADC_SQR4_SQ16       ((uint32_t)0x000007C0) /*!< ADC 16th conversion in regular sequence */
#define ADC_SQR4_SQ16_0     ((uint32_t)0x00000040) /*!< ADC SQ16 bit 0 */
#define ADC_SQR4_SQ16_1     ((uint32_t)0x00000080) /*!< ADC SQ16 bit 1 */
#define ADC_SQR4_SQ16_2     ((uint32_t)0x00000100) /*!< ADC SQ16 bit 2 */
#define ADC_SQR4_SQ16_3     ((uint32_t)0x00000200) /*!< ADC SQ16 bit 3 */
#define ADC_SQR4_SQ16_4     ((uint32_t)0x00000400) /*!< ADC SQ16 bit 4 */

/* these defines are maintained for legacy purpose */
#define ADC_SQR3_SQ15       ADC_SQR4_SQ15 /*!< ADC 15th conversion in regular sequence */
#define ADC_SQR3_SQ15_0     ADC_SQR4_SQ15_0 /*!< ADC SQ15 bit 0 */
#define ADC_SQR3_SQ15_1     ADC_SQR4_SQ15_1 /*!< ADC SQ15 bit 1 */
#define ADC_SQR3_SQ15_2     ADC_SQR4_SQ15_2 /*!< ADC SQ15 bit 2 */
#define ADC_SQR3_SQ15_3     ADC_SQR4_SQ15_3 /*!< ADC SQ15 bit 3 */
#define ADC_SQR3_SQ15_4     ADC_SQR4_SQ15_4 /*!< ADC SQ105 bit 4 */

#define ADC_SQR3_SQ16       ADC_SQR4_SQ16 /*!< ADC 16th conversion in regular sequence */
#define ADC_SQR3_SQ16_0     ADC_SQR4_SQ16_0 /*!< ADC SQ16 bit 0 */
#define ADC_SQR3_SQ16_1     ADC_SQR4_SQ16_1 /*!< ADC SQ16 bit 1 */
#define ADC_SQR3_SQ16_2     ADC_SQR4_SQ16_2 /*!< ADC SQ16 bit 2 */
#define ADC_SQR3_SQ16_3     ADC_SQR4_SQ16_3 /*!< ADC SQ16 bit 3 */
#define ADC_SQR3_SQ16_4     ADC_SQR4_SQ16_4 /*!< ADC SQ16 bit 4 */
/********************  Bit definition for ADC_DR register  ********************/
#define ADC_DR_RDATA        ((uint32_t)0x0000FFFF) /*!< ADC regular Data converted */
#define ADC_DR_RDATA_0      ((uint32_t)0x00000001) /*!< ADC RDATA bit 0 */
#define ADC_DR_RDATA_1      ((uint32_t)0x00000002) /*!< ADC RDATA bit 1 */
#define ADC_DR_RDATA_2      ((uint32_t)0x00000004) /*!< ADC RDATA bit 2 */
#define ADC_DR_RDATA_3      ((uint32_t)0x00000008) /*!< ADC RDATA bit 3 */
#define ADC_DR_RDATA_4      ((uint32_t)0x00000010) /*!< ADC RDATA bit 4 */
#define ADC_DR_RDATA_5      ((uint32_t)0x00000020) /*!< ADC RDATA bit 5 */
#define ADC_DR_RDATA_6      ((uint32_t)0x00000040) /*!< ADC RDATA bit 6 */
#define ADC_DR_RDATA_7      ((uint32_t)0x00000080) /*!< ADC RDATA bit 7 */
#define ADC_DR_RDATA_8      ((uint32_t)0x00000100) /*!< ADC RDATA bit 8 */
#define ADC_DR_RDATA_9      ((uint32_t)0x00000200) /*!< ADC RDATA bit 9 */
#define ADC_DR_RDATA_10     ((uint32_t)0x00000400) /*!< ADC RDATA bit 10 */
#define ADC_DR_RDATA_11     ((uint32_t)0x00000800) /*!< ADC RDATA bit 11 */
#define ADC_DR_RDATA_12     ((uint32_t)0x00001000) /*!< ADC RDATA bit 12 */
#define ADC_DR_RDATA_13     ((uint32_t)0x00002000) /*!< ADC RDATA bit 13 */
#define ADC_DR_RDATA_14     ((uint32_t)0x00004000) /*!< ADC RDATA bit 14 */
#define ADC_DR_RDATA_15     ((uint32_t)0x00008000) /*!< ADC RDATA bit 15 */

/********************  Bit definition for ADC_JSQR register  ********************/
#define ADC_JSQR_JL         ((uint32_t)0x00000003) /*!< ADC injected channel sequence length */
#define ADC_JSQR_JL_0       ((uint32_t)0x00000001) /*!< ADC JL bit 0 */
#define ADC_JSQR_JL_1       ((uint32_t)0x00000002) /*!< ADC JL bit 1 */

#define ADC_JSQR_JEXTSEL    ((uint32_t)0x0000003C) /*!< ADC external trigger selection for injected group */
#define ADC_JSQR_JEXTSEL_0  ((uint32_t)0x00000004) /*!< ADC JEXTSEL bit 0 */
#define ADC_JSQR_JEXTSEL_1  ((uint32_t)0x00000008) /*!< ADC JEXTSEL bit 1 */
#define ADC_JSQR_JEXTSEL_2  ((uint32_t)0x00000010) /*!< ADC JEXTSEL bit 2 */
#define ADC_JSQR_JEXTSEL_3  ((uint32_t)0x00000020) /*!< ADC JEXTSEL bit 3 */

#define ADC_JSQR_JEXTEN     ((uint32_t)0x000000C0) /*!< ADC external trigger enable and polarity selection for injected channels */
#define ADC_JSQR_JEXTEN_0   ((uint32_t)0x00000040) /*!< ADC JEXTEN bit 0 */
#define ADC_JSQR_JEXTEN_1   ((uint32_t)0x00000080) /*!< ADC JEXTEN bit 1 */

#define ADC_JSQR_JSQ1       ((uint32_t)0x00001F00) /*!< ADC 1st conversion in injected sequence */
#define ADC_JSQR_JSQ1_0     ((uint32_t)0x00000100) /*!< ADC JSQ1 bit 0 */
#define ADC_JSQR_JSQ1_1     ((uint32_t)0x00000200) /*!< ADC JSQ1 bit 1 */
#define ADC_JSQR_JSQ1_2     ((uint32_t)0x00000400) /*!< ADC JSQ1 bit 2 */
#define ADC_JSQR_JSQ1_3     ((uint32_t)0x00000800) /*!< ADC JSQ1 bit 3 */
#define ADC_JSQR_JSQ1_4     ((uint32_t)0x00001000) /*!< ADC JSQ1 bit 4 */

#define ADC_JSQR_JSQ2       ((uint32_t)0x0007C000) /*!< ADC 2nd conversion in injected sequence */
#define ADC_JSQR_JSQ2_0     ((uint32_t)0x00004000) /*!< ADC JSQ2 bit 0 */
#define ADC_JSQR_JSQ2_1     ((uint32_t)0x00008000) /*!< ADC JSQ2 bit 1 */
#define ADC_JSQR_JSQ2_2     ((uint32_t)0x00010000) /*!< ADC JSQ2 bit 2 */
#define ADC_JSQR_JSQ2_3     ((uint32_t)0x00020000) /*!< ADC JSQ2 bit 3 */
#define ADC_JSQR_JSQ2_4     ((uint32_t)0x00040000) /*!< ADC JSQ2 bit 4 */

#define ADC_JSQR_JSQ3       ((uint32_t)0x01F00000) /*!< ADC 3rd conversion in injected sequence */
#define ADC_JSQR_JSQ3_0     ((uint32_t)0x00100000) /*!< ADC JSQ3 bit 0 */
#define ADC_JSQR_JSQ3_1     ((uint32_t)0x00200000) /*!< ADC JSQ3 bit 1 */
#define ADC_JSQR_JSQ3_2     ((uint32_t)0x00400000) /*!< ADC JSQ3 bit 2 */
#define ADC_JSQR_JSQ3_3     ((uint32_t)0x00800000) /*!< ADC JSQ3 bit 3 */
#define ADC_JSQR_JSQ3_4     ((uint32_t)0x01000000) /*!< ADC JSQ3 bit 4 */

#define ADC_JSQR_JSQ4       ((uint32_t)0x7C000000) /*!< ADC 4th conversion in injected sequence */
#define ADC_JSQR_JSQ4_0     ((uint32_t)0x04000000) /*!< ADC JSQ4 bit 0 */
#define ADC_JSQR_JSQ4_1     ((uint32_t)0x08000000) /*!< ADC JSQ4 bit 1 */
#define ADC_JSQR_JSQ4_2     ((uint32_t)0x10000000) /*!< ADC JSQ4 bit 2 */
#define ADC_JSQR_JSQ4_3     ((uint32_t)0x20000000) /*!< ADC JSQ4 bit 3 */
#define ADC_JSQR_JSQ4_4     ((uint32_t)0x40000000) /*!< ADC JSQ4 bit 4 */

/********************  Bit definition for ADC_OFR1 register  ********************/
#define ADC_OFR1_OFFSET1    ((uint32_t)0x00000FFF) /*!< ADC data offset 1 for channel programmed into bits OFFSET1_CH[4:0] */
#define ADC_OFR1_OFFSET1_0  ((uint32_t)0x00000001) /*!< ADC OFFSET1 bit 0 */
#define ADC_OFR1_OFFSET1_1  ((uint32_t)0x00000002) /*!< ADC OFFSET1 bit 1 */
#define ADC_OFR1_OFFSET1_2  ((uint32_t)0x00000004) /*!< ADC OFFSET1 bit 2 */
#define ADC_OFR1_OFFSET1_3  ((uint32_t)0x00000008) /*!< ADC OFFSET1 bit 3 */
#define ADC_OFR1_OFFSET1_4  ((uint32_t)0x00000010) /*!< ADC OFFSET1 bit 4 */
#define ADC_OFR1_OFFSET1_5  ((uint32_t)0x00000020) /*!< ADC OFFSET1 bit 5 */
#define ADC_OFR1_OFFSET1_6  ((uint32_t)0x00000040) /*!< ADC OFFSET1 bit 6 */
#define ADC_OFR1_OFFSET1_7  ((uint32_t)0x00000080) /*!< ADC OFFSET1 bit 7 */
#define ADC_OFR1_OFFSET1_8  ((uint32_t)0x00000100) /*!< ADC OFFSET1 bit 8 */
#define ADC_OFR1_OFFSET1_9  ((uint32_t)0x00000200) /*!< ADC OFFSET1 bit 9 */
#define ADC_OFR1_OFFSET1_10 ((uint32_t)0x00000400) /*!< ADC OFFSET1 bit 10 */
#define ADC_OFR1_OFFSET1_11 ((uint32_t)0x00000800) /*!< ADC OFFSET1 bit 11 */

#define ADC_OFR1_OFFSET1_CH     ((uint32_t)0x7C000000) /*!< ADC Channel selection for the data offset 1 */
#define ADC_OFR1_OFFSET1_CH_0  ((uint32_t)0x04000000) /*!< ADC OFFSET1_CH bit 0 */
#define ADC_OFR1_OFFSET1_CH_1  ((uint32_t)0x08000000) /*!< ADC OFFSET1_CH bit 1 */
#define ADC_OFR1_OFFSET1_CH_2  ((uint32_t)0x10000000) /*!< ADC OFFSET1_CH bit 2 */
#define ADC_OFR1_OFFSET1_CH_3  ((uint32_t)0x20000000) /*!< ADC OFFSET1_CH bit 3 */
#define ADC_OFR1_OFFSET1_CH_4  ((uint32_t)0x40000000) /*!< ADC OFFSET1_CH bit 4 */

#define ADC_OFR1_OFFSET1_EN ((uint32_t)0x80000000) /*!< ADC offset 1 enable */

/********************  Bit definition for ADC_OFR2 register  ********************/
#define ADC_OFR2_OFFSET2    ((uint32_t)0x00000FFF) /*!< ADC data offset 2 for channel programmed into bits OFFSET2_CH[4:0] */
#define ADC_OFR2_OFFSET2_0  ((uint32_t)0x00000001) /*!< ADC OFFSET2 bit 0 */
#define ADC_OFR2_OFFSET2_1  ((uint32_t)0x00000002) /*!< ADC OFFSET2 bit 1 */
#define ADC_OFR2_OFFSET2_2  ((uint32_t)0x00000004) /*!< ADC OFFSET2 bit 2 */
#define ADC_OFR2_OFFSET2_3  ((uint32_t)0x00000008) /*!< ADC OFFSET2 bit 3 */
#define ADC_OFR2_OFFSET2_4  ((uint32_t)0x00000010) /*!< ADC OFFSET2 bit 4 */
#define ADC_OFR2_OFFSET2_5  ((uint32_t)0x00000020) /*!< ADC OFFSET2 bit 5 */
#define ADC_OFR2_OFFSET2_6  ((uint32_t)0x00000040) /*!< ADC OFFSET2 bit 6 */
#define ADC_OFR2_OFFSET2_7  ((uint32_t)0x00000080) /*!< ADC OFFSET2 bit 7 */
#define ADC_OFR2_OFFSET2_8  ((uint32_t)0x00000100) /*!< ADC OFFSET2 bit 8 */
#define ADC_OFR2_OFFSET2_9  ((uint32_t)0x00000200) /*!< ADC OFFSET2 bit 9 */
#define ADC_OFR2_OFFSET2_10 ((uint32_t)0x00000400) /*!< ADC OFFSET2 bit 10 */
#define ADC_OFR2_OFFSET2_11 ((uint32_t)0x00000800) /*!< ADC OFFSET2 bit 11 */

#define ADC_OFR2_OFFSET2_CH     ((uint32_t)0x7C000000) /*!< ADC Channel selection for the data offset 2 */
#define ADC_OFR2_OFFSET2_CH_0  ((uint32_t)0x04000000) /*!< ADC OFFSET2_CH bit 0 */
#define ADC_OFR2_OFFSET2_CH_1  ((uint32_t)0x08000000) /*!< ADC OFFSET2_CH bit 1 */
#define ADC_OFR2_OFFSET2_CH_2  ((uint32_t)0x10000000) /*!< ADC OFFSET2_CH bit 2 */
#define ADC_OFR2_OFFSET2_CH_3  ((uint32_t)0x20000000) /*!< ADC OFFSET2_CH bit 3 */
#define ADC_OFR2_OFFSET2_CH_4  ((uint32_t)0x40000000) /*!< ADC OFFSET2_CH bit 4 */

#define ADC_OFR2_OFFSET2_EN ((uint32_t)0x80000000) /*!< ADC offset 2 enable */

/********************  Bit definition for ADC_OFR3 register  ********************/
#define ADC_OFR3_OFFSET3    ((uint32_t)0x00000FFF) /*!< ADC data offset 3 for channel programmed into bits OFFSET3_CH[4:0] */
#define ADC_OFR3_OFFSET3_0  ((uint32_t)0x00000001) /*!< ADC OFFSET3 bit 0 */
#define ADC_OFR3_OFFSET3_1  ((uint32_t)0x00000002) /*!< ADC OFFSET3 bit 1 */
#define ADC_OFR3_OFFSET3_2  ((uint32_t)0x00000004) /*!< ADC OFFSET3 bit 2 */
#define ADC_OFR3_OFFSET3_3  ((uint32_t)0x00000008) /*!< ADC OFFSET3 bit 3 */
#define ADC_OFR3_OFFSET3_4  ((uint32_t)0x00000010) /*!< ADC OFFSET3 bit 4 */
#define ADC_OFR3_OFFSET3_5  ((uint32_t)0x00000020) /*!< ADC OFFSET3 bit 5 */
#define ADC_OFR3_OFFSET3_6  ((uint32_t)0x00000040) /*!< ADC OFFSET3 bit 6 */
#define ADC_OFR3_OFFSET3_7  ((uint32_t)0x00000080) /*!< ADC OFFSET3 bit 7 */
#define ADC_OFR3_OFFSET3_8  ((uint32_t)0x00000100) /*!< ADC OFFSET3 bit 8 */
#define ADC_OFR3_OFFSET3_9  ((uint32_t)0x00000200) /*!< ADC OFFSET3 bit 9 */
#define ADC_OFR3_OFFSET3_10 ((uint32_t)0x00000400) /*!< ADC OFFSET3 bit 10 */
#define ADC_OFR3_OFFSET3_11 ((uint32_t)0x00000800) /*!< ADC OFFSET3 bit 11 */

#define ADC_OFR3_OFFSET3_CH     ((uint32_t)0x7C000000) /*!< ADC Channel selection for the data offset 3 */
#define ADC_OFR3_OFFSET3_CH_0  ((uint32_t)0x04000000) /*!< ADC OFFSET3_CH bit 0 */
#define ADC_OFR3_OFFSET3_CH_1  ((uint32_t)0x08000000) /*!< ADC OFFSET3_CH bit 1 */
#define ADC_OFR3_OFFSET3_CH_2  ((uint32_t)0x10000000) /*!< ADC OFFSET3_CH bit 2 */
#define ADC_OFR3_OFFSET3_CH_3  ((uint32_t)0x20000000) /*!< ADC OFFSET3_CH bit 3 */
#define ADC_OFR3_OFFSET3_CH_4  ((uint32_t)0x40000000) /*!< ADC OFFSET3_CH bit 4 */

#define ADC_OFR3_OFFSET3_EN ((uint32_t)0x80000000) /*!< ADC offset 3 enable */

/********************  Bit definition for ADC_OFR4 register  ********************/
#define ADC_OFR4_OFFSET4    ((uint32_t)0x00000FFF) /*!< ADC data offset 4 for channel programmed into bits OFFSET4_CH[4:0] */
#define ADC_OFR4_OFFSET4_0  ((uint32_t)0x00000001) /*!< ADC OFFSET4 bit 0 */
#define ADC_OFR4_OFFSET4_1  ((uint32_t)0x00000002) /*!< ADC OFFSET4 bit 1 */
#define ADC_OFR4_OFFSET4_2  ((uint32_t)0x00000004) /*!< ADC OFFSET4 bit 2 */
#define ADC_OFR4_OFFSET4_3  ((uint32_t)0x00000008) /*!< ADC OFFSET4 bit 3 */
#define ADC_OFR4_OFFSET4_4  ((uint32_t)0x00000010) /*!< ADC OFFSET4 bit 4 */
#define ADC_OFR4_OFFSET4_5  ((uint32_t)0x00000020) /*!< ADC OFFSET4 bit 5 */
#define ADC_OFR4_OFFSET4_6  ((uint32_t)0x00000040) /*!< ADC OFFSET4 bit 6 */
#define ADC_OFR4_OFFSET4_7  ((uint32_t)0x00000080) /*!< ADC OFFSET4 bit 7 */
#define ADC_OFR4_OFFSET4_8  ((uint32_t)0x00000100) /*!< ADC OFFSET4 bit 8 */
#define ADC_OFR4_OFFSET4_9  ((uint32_t)0x00000200) /*!< ADC OFFSET4 bit 9 */
#define ADC_OFR4_OFFSET4_10 ((uint32_t)0x00000400) /*!< ADC OFFSET4 bit 10 */
#define ADC_OFR4_OFFSET4_11 ((uint32_t)0x00000800) /*!< ADC OFFSET4 bit 11 */

#define ADC_OFR4_OFFSET4_CH     ((uint32_t)0x7C000000) /*!< ADC Channel selection for the data offset 4 */
#define ADC_OFR4_OFFSET4_CH_0  ((uint32_t)0x04000000) /*!< ADC OFFSET4_CH bit 0 */
#define ADC_OFR4_OFFSET4_CH_1  ((uint32_t)0x08000000) /*!< ADC OFFSET4_CH bit 1 */
#define ADC_OFR4_OFFSET4_CH_2  ((uint32_t)0x10000000) /*!< ADC OFFSET4_CH bit 2 */
#define ADC_OFR4_OFFSET4_CH_3  ((uint32_t)0x20000000) /*!< ADC OFFSET4_CH bit 3 */
#define ADC_OFR4_OFFSET4_CH_4  ((uint32_t)0x40000000) /*!< ADC OFFSET4_CH bit 4 */

#define ADC_OFR4_OFFSET4_EN ((uint32_t)0x80000000) /*!< ADC offset 4 enable */

/********************  Bit definition for ADC_JDR1 register  ********************/
#define ADC_JDR1_JDATA      ((uint32_t)0x0000FFFF) /*!< ADC Injected DATA */
#define ADC_JDR1_JDATA_0    ((uint32_t)0x00000001) /*!< ADC JDATA bit 0 */
#define ADC_JDR1_JDATA_1    ((uint32_t)0x00000002) /*!< ADC JDATA bit 1 */
#define ADC_JDR1_JDATA_2    ((uint32_t)0x00000004) /*!< ADC JDATA bit 2 */
#define ADC_JDR1_JDATA_3    ((uint32_t)0x00000008) /*!< ADC JDATA bit 3 */
#define ADC_JDR1_JDATA_4    ((uint32_t)0x00000010) /*!< ADC JDATA bit 4 */
#define ADC_JDR1_JDATA_5    ((uint32_t)0x00000020) /*!< ADC JDATA bit 5 */
#define ADC_JDR1_JDATA_6    ((uint32_t)0x00000040) /*!< ADC JDATA bit 6 */
#define ADC_JDR1_JDATA_7    ((uint32_t)0x00000080) /*!< ADC JDATA bit 7 */
#define ADC_JDR1_JDATA_8    ((uint32_t)0x00000100) /*!< ADC JDATA bit 8 */
#define ADC_JDR1_JDATA_9    ((uint32_t)0x00000200) /*!< ADC JDATA bit 9 */
#define ADC_JDR1_JDATA_10   ((uint32_t)0x00000400) /*!< ADC JDATA bit 10 */
#define ADC_JDR1_JDATA_11   ((uint32_t)0x00000800) /*!< ADC JDATA bit 11 */
#define ADC_JDR1_JDATA_12   ((uint32_t)0x00001000) /*!< ADC JDATA bit 12 */
#define ADC_JDR1_JDATA_13   ((uint32_t)0x00002000) /*!< ADC JDATA bit 13 */
#define ADC_JDR1_JDATA_14   ((uint32_t)0x00004000) /*!< ADC JDATA bit 14 */
#define ADC_JDR1_JDATA_15   ((uint32_t)0x00008000) /*!< ADC JDATA bit 15 */

/********************  Bit definition for ADC_JDR2 register  ********************/
#define ADC_JDR2_JDATA      ((uint32_t)0x0000FFFF) /*!< ADC Injected DATA */
#define ADC_JDR2_JDATA_0    ((uint32_t)0x00000001) /*!< ADC JDATA bit 0 */
#define ADC_JDR2_JDATA_1    ((uint32_t)0x00000002) /*!< ADC JDATA bit 1 */
#define ADC_JDR2_JDATA_2    ((uint32_t)0x00000004) /*!< ADC JDATA bit 2 */
#define ADC_JDR2_JDATA_3    ((uint32_t)0x00000008) /*!< ADC JDATA bit 3 */
#define ADC_JDR2_JDATA_4    ((uint32_t)0x00000010) /*!< ADC JDATA bit 4 */
#define ADC_JDR2_JDATA_5    ((uint32_t)0x00000020) /*!< ADC JDATA bit 5 */
#define ADC_JDR2_JDATA_6    ((uint32_t)0x00000040) /*!< ADC JDATA bit 6 */
#define ADC_JDR2_JDATA_7    ((uint32_t)0x00000080) /*!< ADC JDATA bit 7 */
#define ADC_JDR2_JDATA_8    ((uint32_t)0x00000100) /*!< ADC JDATA bit 8 */
#define ADC_JDR2_JDATA_9    ((uint32_t)0x00000200) /*!< ADC JDATA bit 9 */
#define ADC_JDR2_JDATA_10   ((uint32_t)0x00000400) /*!< ADC JDATA bit 10 */
#define ADC_JDR2_JDATA_11   ((uint32_t)0x00000800) /*!< ADC JDATA bit 11 */
#define ADC_JDR2_JDATA_12   ((uint32_t)0x00001000) /*!< ADC JDATA bit 12 */
#define ADC_JDR2_JDATA_13   ((uint32_t)0x00002000) /*!< ADC JDATA bit 13 */
#define ADC_JDR2_JDATA_14   ((uint32_t)0x00004000) /*!< ADC JDATA bit 14 */
#define ADC_JDR2_JDATA_15   ((uint32_t)0x00008000) /*!< ADC JDATA bit 15 */

/********************  Bit definition for ADC_JDR3 register  ********************/
#define ADC_JDR3_JDATA      ((uint32_t)0x0000FFFF) /*!< ADC Injected DATA */
#define ADC_JDR3_JDATA_0    ((uint32_t)0x00000001) /*!< ADC JDATA bit 0 */
#define ADC_JDR3_JDATA_1    ((uint32_t)0x00000002) /*!< ADC JDATA bit 1 */
#define ADC_JDR3_JDATA_2    ((uint32_t)0x00000004) /*!< ADC JDATA bit 2 */
#define ADC_JDR3_JDATA_3    ((uint32_t)0x00000008) /*!< ADC JDATA bit 3 */
#define ADC_JDR3_JDATA_4    ((uint32_t)0x00000010) /*!< ADC JDATA bit 4 */
#define ADC_JDR3_JDATA_5    ((uint32_t)0x00000020) /*!< ADC JDATA bit 5 */
#define ADC_JDR3_JDATA_6    ((uint32_t)0x00000040) /*!< ADC JDATA bit 6 */
#define ADC_JDR3_JDATA_7    ((uint32_t)0x00000080) /*!< ADC JDATA bit 7 */
#define ADC_JDR3_JDATA_8    ((uint32_t)0x00000100) /*!< ADC JDATA bit 8 */
#define ADC_JDR3_JDATA_9    ((uint32_t)0x00000200) /*!< ADC JDATA bit 9 */
#define ADC_JDR3_JDATA_10   ((uint32_t)0x00000400) /*!< ADC JDATA bit 10 */
#define ADC_JDR3_JDATA_11   ((uint32_t)0x00000800) /*!< ADC JDATA bit 11 */
#define ADC_JDR3_JDATA_12   ((uint32_t)0x00001000) /*!< ADC JDATA bit 12 */
#define ADC_JDR3_JDATA_13   ((uint32_t)0x00002000) /*!< ADC JDATA bit 13 */
#define ADC_JDR3_JDATA_14   ((uint32_t)0x00004000) /*!< ADC JDATA bit 14 */
#define ADC_JDR3_JDATA_15   ((uint32_t)0x00008000) /*!< ADC JDATA bit 15 */

/********************  Bit definition for ADC_JDR4 register  ********************/
#define ADC_JDR4_JDATA      ((uint32_t)0x0000FFFF) /*!< ADC Injected DATA */
#define ADC_JDR4_JDATA_0    ((uint32_t)0x00000001) /*!< ADC JDATA bit 0 */
#define ADC_JDR4_JDATA_1    ((uint32_t)0x00000002) /*!< ADC JDATA bit 1 */
#define ADC_JDR4_JDATA_2    ((uint32_t)0x00000004) /*!< ADC JDATA bit 2 */
#define ADC_JDR4_JDATA_3    ((uint32_t)0x00000008) /*!< ADC JDATA bit 3 */
#define ADC_JDR4_JDATA_4    ((uint32_t)0x00000010) /*!< ADC JDATA bit 4 */
#define ADC_JDR4_JDATA_5    ((uint32_t)0x00000020) /*!< ADC JDATA bit 5 */
#define ADC_JDR4_JDATA_6    ((uint32_t)0x00000040) /*!< ADC JDATA bit 6 */
#define ADC_JDR4_JDATA_7    ((uint32_t)0x00000080) /*!< ADC JDATA bit 7 */
#define ADC_JDR4_JDATA_8    ((uint32_t)0x00000100) /*!< ADC JDATA bit 8 */
#define ADC_JDR4_JDATA_9    ((uint32_t)0x00000200) /*!< ADC JDATA bit 9 */
#define ADC_JDR4_JDATA_10   ((uint32_t)0x00000400) /*!< ADC JDATA bit 10 */
#define ADC_JDR4_JDATA_11   ((uint32_t)0x00000800) /*!< ADC JDATA bit 11 */
#define ADC_JDR4_JDATA_12   ((uint32_t)0x00001000) /*!< ADC JDATA bit 12 */
#define ADC_JDR4_JDATA_13   ((uint32_t)0x00002000) /*!< ADC JDATA bit 13 */
#define ADC_JDR4_JDATA_14   ((uint32_t)0x00004000) /*!< ADC JDATA bit 14 */
#define ADC_JDR4_JDATA_15   ((uint32_t)0x00008000) /*!< ADC JDATA bit 15 */

/********************  Bit definition for ADC_AWD2CR register  ********************/
#define ADC_AWD2CR_AWD2CH    ((uint32_t)0x0007FFFE) /*!< ADC Analog watchdog 2 channel selection */
#define ADC_AWD2CR_AWD2CH_0  ((uint32_t)0x00000002) /*!< ADC AWD2CH bit 0 */
#define ADC_AWD2CR_AWD2CH_1  ((uint32_t)0x00000004) /*!< ADC AWD2CH bit 1 */
#define ADC_AWD2CR_AWD2CH_2  ((uint32_t)0x00000008) /*!< ADC AWD2CH bit 2 */
#define ADC_AWD2CR_AWD2CH_3  ((uint32_t)0x00000010) /*!< ADC AWD2CH bit 3 */
#define ADC_AWD2CR_AWD2CH_4  ((uint32_t)0x00000020) /*!< ADC AWD2CH bit 4 */
#define ADC_AWD2CR_AWD2CH_5  ((uint32_t)0x00000040) /*!< ADC AWD2CH bit 5 */
#define ADC_AWD2CR_AWD2CH_6  ((uint32_t)0x00000080) /*!< ADC AWD2CH bit 6 */
#define ADC_AWD2CR_AWD2CH_7  ((uint32_t)0x00000100) /*!< ADC AWD2CH bit 7 */
#define ADC_AWD2CR_AWD2CH_8  ((uint32_t)0x00000200) /*!< ADC AWD2CH bit 8 */
#define ADC_AWD2CR_AWD2CH_9  ((uint32_t)0x00000400) /*!< ADC AWD2CH bit 9 */
#define ADC_AWD2CR_AWD2CH_10 ((uint32_t)0x00000800) /*!< ADC AWD2CH bit 10 */
#define ADC_AWD2CR_AWD2CH_11 ((uint32_t)0x00001000) /*!< ADC AWD2CH bit 11 */
#define ADC_AWD2CR_AWD2CH_12 ((uint32_t)0x00002000) /*!< ADC AWD2CH bit 12 */
#define ADC_AWD2CR_AWD2CH_13 ((uint32_t)0x00004000) /*!< ADC AWD2CH bit 13 */
#define ADC_AWD2CR_AWD2CH_14 ((uint32_t)0x00008000) /*!< ADC AWD2CH bit 14 */
#define ADC_AWD2CR_AWD2CH_15 ((uint32_t)0x00010000) /*!< ADC AWD2CH bit 15 */
#define ADC_AWD2CR_AWD2CH_16 ((uint32_t)0x00020000) /*!< ADC AWD2CH bit 16 */
#define ADC_AWD2CR_AWD2CH_17 ((uint32_t)0x00030000) /*!< ADC AWD2CH bit 17 */

/********************  Bit definition for ADC_AWD3CR register  ********************/
#define ADC_AWD3CR_AWD3CH    ((uint32_t)0x0007FFFE) /*!< ADC Analog watchdog 2 channel selection */
#define ADC_AWD3CR_AWD3CH_0  ((uint32_t)0x00000002) /*!< ADC AWD3CH bit 0 */
#define ADC_AWD3CR_AWD3CH_1  ((uint32_t)0x00000004) /*!< ADC AWD3CH bit 1 */
#define ADC_AWD3CR_AWD3CH_2  ((uint32_t)0x00000008) /*!< ADC AWD3CH bit 2 */
#define ADC_AWD3CR_AWD3CH_3  ((uint32_t)0x00000010) /*!< ADC AWD3CH bit 3 */
#define ADC_AWD3CR_AWD3CH_4  ((uint32_t)0x00000020) /*!< ADC AWD3CH bit 4 */
#define ADC_AWD3CR_AWD3CH_5  ((uint32_t)0x00000040) /*!< ADC AWD3CH bit 5 */
#define ADC_AWD3CR_AWD3CH_6  ((uint32_t)0x00000080) /*!< ADC AWD3CH bit 6 */
#define ADC_AWD3CR_AWD3CH_7  ((uint32_t)0x00000100) /*!< ADC AWD3CH bit 7 */
#define ADC_AWD3CR_AWD3CH_8  ((uint32_t)0x00000200) /*!< ADC AWD3CH bit 8 */
#define ADC_AWD3CR_AWD3CH_9  ((uint32_t)0x00000400) /*!< ADC AWD3CH bit 9 */
#define ADC_AWD3CR_AWD3CH_10 ((uint32_t)0x00000800) /*!< ADC AWD3CH bit 10 */
#define ADC_AWD3CR_AWD3CH_11 ((uint32_t)0x00001000) /*!< ADC AWD3CH bit 11 */
#define ADC_AWD3CR_AWD3CH_12 ((uint32_t)0x00002000) /*!< ADC AWD3CH bit 12 */
#define ADC_AWD3CR_AWD3CH_13 ((uint32_t)0x00004000) /*!< ADC AWD3CH bit 13 */
#define ADC_AWD3CR_AWD3CH_14 ((uint32_t)0x00008000) /*!< ADC AWD3CH bit 14 */
#define ADC_AWD3CR_AWD3CH_15 ((uint32_t)0x00010000) /*!< ADC AWD3CH bit 15 */
#define ADC_AWD3CR_AWD3CH_16 ((uint32_t)0x00020000) /*!< ADC AWD3CH bit 16 */
#define ADC_AWD3CR_AWD3CH_17 ((uint32_t)0x00030000) /*!< ADC AWD3CH bit 17 */

/********************  Bit definition for ADC_DIFSEL register  ********************/
#define ADC_DIFSEL_DIFSEL    ((uint32_t)0x0007FFFE) /*!< ADC differential modes for channels 1 to 18 */
#define ADC_DIFSEL_DIFSEL_0  ((uint32_t)0x00000002) /*!< ADC DIFSEL bit 0 */
#define ADC_DIFSEL_DIFSEL_1  ((uint32_t)0x00000004) /*!< ADC DIFSEL bit 1 */
#define ADC_DIFSEL_DIFSEL_2  ((uint32_t)0x00000008) /*!< ADC DIFSEL bit 2 */
#define ADC_DIFSEL_DIFSEL_3  ((uint32_t)0x00000010) /*!< ADC DIFSEL bit 3 */
#define ADC_DIFSEL_DIFSEL_4  ((uint32_t)0x00000020) /*!< ADC DIFSEL bit 4 */
#define ADC_DIFSEL_DIFSEL_5  ((uint32_t)0x00000040) /*!< ADC DIFSEL bit 5 */
#define ADC_DIFSEL_DIFSEL_6  ((uint32_t)0x00000080) /*!< ADC DIFSEL bit 6 */
#define ADC_DIFSEL_DIFSEL_7  ((uint32_t)0x00000100) /*!< ADC DIFSEL bit 7 */
#define ADC_DIFSEL_DIFSEL_8  ((uint32_t)0x00000200) /*!< ADC DIFSEL bit 8 */
#define ADC_DIFSEL_DIFSEL_9  ((uint32_t)0x00000400) /*!< ADC DIFSEL bit 9 */
#define ADC_DIFSEL_DIFSEL_10 ((uint32_t)0x00000800) /*!< ADC DIFSEL bit 10 */
#define ADC_DIFSEL_DIFSEL_11 ((uint32_t)0x00001000) /*!< ADC DIFSEL bit 11 */
#define ADC_DIFSEL_DIFSEL_12 ((uint32_t)0x00002000) /*!< ADC DIFSEL bit 12 */
#define ADC_DIFSEL_DIFSEL_13 ((uint32_t)0x00004000) /*!< ADC DIFSEL bit 13 */
#define ADC_DIFSEL_DIFSEL_14 ((uint32_t)0x00008000) /*!< ADC DIFSEL bit 14 */
#define ADC_DIFSEL_DIFSEL_15 ((uint32_t)0x00010000) /*!< ADC DIFSEL bit 15 */
#define ADC_DIFSEL_DIFSEL_16 ((uint32_t)0x00020000) /*!< ADC DIFSEL bit 16 */
#define ADC_DIFSEL_DIFSEL_17 ((uint32_t)0x00030000) /*!< ADC DIFSEL bit 17 */

/********************  Bit definition for ADC_CALFACT register  ********************/
#define ADC_CALFACT_CALFACT_S   ((uint32_t)0x0000007F) /*!< ADC calibration factors in single-ended mode */
#define ADC_CALFACT_CALFACT_S_0 ((uint32_t)0x00000001) /*!< ADC CALFACT_S bit 0 */
#define ADC_CALFACT_CALFACT_S_1 ((uint32_t)0x00000002) /*!< ADC CALFACT_S bit 1 */
#define ADC_CALFACT_CALFACT_S_2 ((uint32_t)0x00000004) /*!< ADC CALFACT_S bit 2 */
#define ADC_CALFACT_CALFACT_S_3 ((uint32_t)0x00000008) /*!< ADC CALFACT_S bit 3 */
#define ADC_CALFACT_CALFACT_S_4 ((uint32_t)0x00000010) /*!< ADC CALFACT_S bit 4 */
#define ADC_CALFACT_CALFACT_S_5 ((uint32_t)0x00000020) /*!< ADC CALFACT_S bit 5 */
#define ADC_CALFACT_CALFACT_S_6 ((uint32_t)0x00000040) /*!< ADC CALFACT_S bit 6 */
#define ADC_CALFACT_CALFACT_D   ((uint32_t)0x007F0000) /*!< ADC calibration factors in differential mode */
#define ADC_CALFACT_CALFACT_D_0 ((uint32_t)0x00010000) /*!< ADC CALFACT_D bit 0 */
#define ADC_CALFACT_CALFACT_D_1 ((uint32_t)0x00020000) /*!< ADC CALFACT_D bit 1 */
#define ADC_CALFACT_CALFACT_D_2 ((uint32_t)0x00040000) /*!< ADC CALFACT_D bit 2 */
#define ADC_CALFACT_CALFACT_D_3 ((uint32_t)0x00080000) /*!< ADC CALFACT_D bit 3 */
#define ADC_CALFACT_CALFACT_D_4 ((uint32_t)0x00100000) /*!< ADC CALFACT_D bit 4 */
#define ADC_CALFACT_CALFACT_D_5 ((uint32_t)0x00200000) /*!< ADC CALFACT_D bit 5 */
#define ADC_CALFACT_CALFACT_D_6 ((uint32_t)0x00400000) /*!< ADC CALFACT_D bit 6 */

/*************************  ADC Common registers  *****************************/
/********************  Bit definition for ADC12_CSR register  ********************/
#define ADC12_CSR_ADRDY_MST         ((uint32_t)0x00000001) /*!< Master ADC ready */
#define ADC12_CSR_ADRDY_EOSMP_MST   ((uint32_t)0x00000002) /*!< End of sampling phase flag of the master ADC */
#define ADC12_CSR_ADRDY_EOC_MST     ((uint32_t)0x00000004) /*!< End of regular conversion of the master ADC */
#define ADC12_CSR_ADRDY_EOS_MST     ((uint32_t)0x00000008) /*!< End of regular sequence flag of the master ADC */
#define ADC12_CSR_ADRDY_OVR_MST     ((uint32_t)0x00000010) /*!< Overrun flag of the master ADC */
#define ADC12_CSR_ADRDY_JEOC_MST    ((uint32_t)0x00000020) /*!< End of injected conversion of the master ADC */
#define ADC12_CSR_ADRDY_JEOS_MST    ((uint32_t)0x00000040) /*!< End of injected sequence flag of the master ADC */
#define ADC12_CSR_AWD1_MST          ((uint32_t)0x00000080) /*!< Analog watchdog 1 flag of the master ADC */
#define ADC12_CSR_AWD2_MST          ((uint32_t)0x00000100) /*!< Analog watchdog 2 flag of the master ADC */
#define ADC12_CSR_AWD3_MST          ((uint32_t)0x00000200) /*!< Analog watchdog 3 flag of the master ADC */
#define ADC12_CSR_JQOVF_MST         ((uint32_t)0x00000400) /*!< Injected context queue overflow flag of the master ADC */
#define ADC12_CSR_ADRDY_SLV         ((uint32_t)0x00010000) /*!< Slave ADC ready */
#define ADC12_CSR_ADRDY_EOSMP_SLV   ((uint32_t)0x00020000) /*!< End of sampling phase flag of the slave ADC */
#define ADC12_CSR_ADRDY_EOC_SLV     ((uint32_t)0x00040000) /*!< End of regular conversion of the slave ADC */
#define ADC12_CSR_ADRDY_EOS_SLV     ((uint32_t)0x00080000) /*!< End of regular sequence flag of the slave ADC */
#define ADC12_CSR_ADRDY_OVR_SLV     ((uint32_t)0x00100000) /*!< Overrun flag of the slave ADC */
#define ADC12_CSR_ADRDY_JEOC_SLV    ((uint32_t)0x00200000) /*!< End of injected conversion of the slave ADC */
#define ADC12_CSR_ADRDY_JEOS_SLV    ((uint32_t)0x00400000) /*!< End of injected sequence flag of the slave ADC */
#define ADC12_CSR_AWD1_SLV          ((uint32_t)0x00800000) /*!< Analog watchdog 1 flag of the slave ADC */
#define ADC12_CSR_AWD2_SLV          ((uint32_t)0x01000000) /*!< Analog watchdog 2 flag of the slave ADC */
#define ADC12_CSR_AWD3_SLV          ((uint32_t)0x02000000) /*!< Analog watchdog 3 flag of the slave ADC */
#define ADC12_CSR_JQOVF_SLV         ((uint32_t)0x04000000) /*!< Injected context queue overflow flag of the slave ADC */

/********************  Bit definition for ADC34_CSR register  ********************/
#define ADC34_CSR_ADRDY_MST         ((uint32_t)0x00000001) /*!< Master ADC ready */
#define ADC34_CSR_ADRDY_EOSMP_MST   ((uint32_t)0x00000002) /*!< End of sampling phase flag of the master ADC */
#define ADC34_CSR_ADRDY_EOC_MST     ((uint32_t)0x00000004) /*!< End of regular conversion of the master ADC */
#define ADC34_CSR_ADRDY_EOS_MST     ((uint32_t)0x00000008) /*!< End of regular sequence flag of the master ADC */
#define ADC34_CSR_ADRDY_OVR_MST     ((uint32_t)0x00000010) /*!< Overrun flag of the master ADC */
#define ADC34_CSR_ADRDY_JEOC_MST    ((uint32_t)0x00000020) /*!< End of injected conversion of the master ADC */
#define ADC34_CSR_ADRDY_JEOS_MST    ((uint32_t)0x00000040) /*!< End of injected sequence flag of the master ADC */
#define ADC34_CSR_AWD1_MST          ((uint32_t)0x00000080) /*!< Analog watchdog 1 flag of the master ADC */
#define ADC34_CSR_AWD2_MST          ((uint32_t)0x00000100) /*!< Analog watchdog 2 flag of the master ADC */
#define ADC34_CSR_AWD3_MST          ((uint32_t)0x00000200) /*!< Analog watchdog 3 flag of the master ADC */
#define ADC34_CSR_JQOVF_MST         ((uint32_t)0x00000400) /*!< Injected context queue overflow flag of the master ADC */
#define ADC34_CSR_ADRDY_SLV         ((uint32_t)0x00010000) /*!< Slave ADC ready */
#define ADC34_CSR_ADRDY_EOSMP_SLV   ((uint32_t)0x00020000) /*!< End of sampling phase flag of the slave ADC */
#define ADC34_CSR_ADRDY_EOC_SLV     ((uint32_t)0x00040000) /*!< End of regular conversion of the slave ADC */
#define ADC34_CSR_ADRDY_EOS_SLV     ((uint32_t)0x00080000) /*!< End of regular sequence flag of the slave ADC */
#define ADC12_CSR_ADRDY_OVR_SLV     ((uint32_t)0x00100000) /*!< Overrun flag of the slave ADC */
#define ADC34_CSR_ADRDY_JEOC_SLV    ((uint32_t)0x00200000) /*!< End of injected conversion of the slave ADC */
#define ADC34_CSR_ADRDY_JEOS_SLV    ((uint32_t)0x00400000) /*!< End of injected sequence flag of the slave ADC */
#define ADC34_CSR_AWD1_SLV          ((uint32_t)0x00800000) /*!< Analog watchdog 1 flag of the slave ADC */
#define ADC34_CSR_AWD2_SLV          ((uint32_t)0x01000000) /*!< Analog watchdog 2 flag of the slave ADC */
#define ADC34_CSR_AWD3_SLV          ((uint32_t)0x02000000) /*!< Analog watchdog 3 flag of the slave ADC */
#define ADC34_CSR_JQOVF_SLV         ((uint32_t)0x04000000) /*!< Injected context queue overflow flag of the slave ADC */

/********************  Bit definition for ADC_CCR register  ********************/
#define ADC12_CCR_MULTI             ((uint32_t)0x0000001F) /*!< Multi ADC mode selection */
#define ADC12_CCR_MULTI_0           ((uint32_t)0x00000001) /*!< MULTI bit 0 */
#define ADC12_CCR_MULTI_1           ((uint32_t)0x00000002) /*!< MULTI bit 1 */
#define ADC12_CCR_MULTI_2           ((uint32_t)0x00000004) /*!< MULTI bit 2 */
#define ADC12_CCR_MULTI_3           ((uint32_t)0x00000008) /*!< MULTI bit 3 */
#define ADC12_CCR_MULTI_4           ((uint32_t)0x00000010) /*!< MULTI bit 4 */
#define ADC12_CCR_DELAY             ((uint32_t)0x00000F00) /*!< Delay between 2 sampling phases */
#define ADC12_CCR_DELAY_0           ((uint32_t)0x00000100) /*!< DELAY bit 0 */
#define ADC12_CCR_DELAY_1           ((uint32_t)0x00000200) /*!< DELAY bit 1 */
#define ADC12_CCR_DELAY_2           ((uint32_t)0x00000400) /*!< DELAY bit 2 */
#define ADC12_CCR_DELAY_3           ((uint32_t)0x00000800) /*!< DELAY bit 3 */
#define ADC12_CCR_DMACFG            ((uint32_t)0x00002000) /*!< DMA configuration for multi-ADC mode */
#define ADC12_CCR_MDMA              ((uint32_t)0x0000C000) /*!< DMA mode for multi-ADC mode */
#define ADC12_CCR_MDMA_0            ((uint32_t)0x00004000) /*!< MDMA bit 0 */
#define ADC12_CCR_MDMA_1            ((uint32_t)0x00008000) /*!< MDMA bit 1 */
#define ADC12_CCR_CKMODE            ((uint32_t)0x00030000) /*!< ADC clock mode */
#define ADC12_CCR_CKMODE_0          ((uint32_t)0x00010000) /*!< CKMODE bit 0 */
#define ADC12_CCR_CKMODE_1          ((uint32_t)0x00020000) /*!< CKMODE bit 1 */
#define ADC12_CCR_VREFEN            ((uint32_t)0x00400000) /*!< VREFINT enable */
#define ADC12_CCR_TSEN              ((uint32_t)0x00800000) /*!< Temperature sensor enable */
#define ADC12_CCR_VBATEN            ((uint32_t)0x01000000) /*!< VBAT enable */

/********************  Bit definition for ADC_CCR register  ********************/
#define ADC34_CCR_MULTI             ((uint32_t)0x0000001F) /*!< Multi ADC mode selection */
#define ADC34_CCR_MULTI_0           ((uint32_t)0x00000001) /*!< MULTI bit 0 */
#define ADC34_CCR_MULTI_1           ((uint32_t)0x00000002) /*!< MULTI bit 1 */
#define ADC34_CCR_MULTI_2           ((uint32_t)0x00000004) /*!< MULTI bit 2 */
#define ADC34_CCR_MULTI_3           ((uint32_t)0x00000008) /*!< MULTI bit 3 */
#define ADC34_CCR_MULTI_4           ((uint32_t)0x00000010) /*!< MULTI bit 4 */

#define ADC34_CCR_DELAY             ((uint32_t)0x00000F00) /*!< Delay between 2 sampling phases */
#define ADC34_CCR_DELAY_0           ((uint32_t)0x00000100) /*!< DELAY bit 0 */
#define ADC34_CCR_DELAY_1           ((uint32_t)0x00000200) /*!< DELAY bit 1 */
#define ADC34_CCR_DELAY_2           ((uint32_t)0x00000400) /*!< DELAY bit 2 */
#define ADC34_CCR_DELAY_3           ((uint32_t)0x00000800) /*!< DELAY bit 3 */

#define ADC34_CCR_DMACFG            ((uint32_t)0x00002000) /*!< DMA configuration for multi-ADC mode */
#define ADC34_CCR_MDMA              ((uint32_t)0x0000C000) /*!< DMA mode for multi-ADC mode */
#define ADC34_CCR_MDMA_0            ((uint32_t)0x00004000) /*!< MDMA bit 0 */
#define ADC34_CCR_MDMA_1            ((uint32_t)0x00008000) /*!< MDMA bit 1 */

#define ADC34_CCR_CKMODE            ((uint32_t)0x00030000) /*!< ADC clock mode */
#define ADC34_CCR_CKMODE_0          ((uint32_t)0x00010000) /*!< CKMODE bit 0 */
#define ADC34_CCR_CKMODE_1          ((uint32_t)0x00020000) /*!< CKMODE bit 1 */

#define ADC34_CCR_VREFEN            ((uint32_t)0x00400000) /*!< VREFINT enable */

/********************  Bit definition for ADC_CDR register  ********************/
#define ADC12_CDR_RDATA_MST         ((uint32_t)0x0000FFFF) /*!< Regular Data of the master ADC */
#define ADC12_CDR_RDATA_MST_0       ((uint32_t)0x00000001) /*!< RDATA_MST bit 0 */
#define ADC12_CDR_RDATA_MST_1       ((uint32_t)0x00000002) /*!< RDATA_MST bit 1 */
#define ADC12_CDR_RDATA_MST_2       ((uint32_t)0x00000004) /*!< RDATA_MST bit 2 */
#define ADC12_CDR_RDATA_MST_3       ((uint32_t)0x00000008) /*!< RDATA_MST bit 3 */
#define ADC12_CDR_RDATA_MST_4       ((uint32_t)0x00000010) /*!< RDATA_MST bit 4 */
#define ADC12_CDR_RDATA_MST_5       ((uint32_t)0x00000020) /*!< RDATA_MST bit 5 */
#define ADC12_CDR_RDATA_MST_6       ((uint32_t)0x00000040) /*!< RDATA_MST bit 6 */
#define ADC12_CDR_RDATA_MST_7       ((uint32_t)0x00000080) /*!< RDATA_MST bit 7 */
#define ADC12_CDR_RDATA_MST_8       ((uint32_t)0x00000100) /*!< RDATA_MST bit 8 */
#define ADC12_CDR_RDATA_MST_9       ((uint32_t)0x00000200) /*!< RDATA_MST bit 9 */
#define ADC12_CDR_RDATA_MST_10      ((uint32_t)0x00000400) /*!< RDATA_MST bit 10 */
#define ADC12_CDR_RDATA_MST_11      ((uint32_t)0x00000800) /*!< RDATA_MST bit 11 */
#define ADC12_CDR_RDATA_MST_12      ((uint32_t)0x00001000) /*!< RDATA_MST bit 12 */
#define ADC12_CDR_RDATA_MST_13      ((uint32_t)0x00002000) /*!< RDATA_MST bit 13 */
#define ADC12_CDR_RDATA_MST_14      ((uint32_t)0x00004000) /*!< RDATA_MST bit 14 */
#define ADC12_CDR_RDATA_MST_15      ((uint32_t)0x00008000) /*!< RDATA_MST bit 15 */

#define ADC12_CDR_RDATA_SLV         ((uint32_t)0xFFFF0000) /*!< Regular Data of the master ADC */
#define ADC12_CDR_RDATA_SLV_0       ((uint32_t)0x00010000) /*!< RDATA_SLV bit 0 */
#define ADC12_CDR_RDATA_SLV_1       ((uint32_t)0x00020000) /*!< RDATA_SLV bit 1 */
#define ADC12_CDR_RDATA_SLV_2       ((uint32_t)0x00040000) /*!< RDATA_SLV bit 2 */
#define ADC12_CDR_RDATA_SLV_3       ((uint32_t)0x00080000) /*!< RDATA_SLV bit 3 */
#define ADC12_CDR_RDATA_SLV_4       ((uint32_t)0x00100000) /*!< RDATA_SLV bit 4 */
#define ADC12_CDR_RDATA_SLV_5       ((uint32_t)0x00200000) /*!< RDATA_SLV bit 5 */
#define ADC12_CDR_RDATA_SLV_6       ((uint32_t)0x00400000) /*!< RDATA_SLV bit 6 */
#define ADC12_CDR_RDATA_SLV_7       ((uint32_t)0x00800000) /*!< RDATA_SLV bit 7 */
#define ADC12_CDR_RDATA_SLV_8       ((uint32_t)0x01000000) /*!< RDATA_SLV bit 8 */
#define ADC12_CDR_RDATA_SLV_9       ((uint32_t)0x02000000) /*!< RDATA_SLV bit 9 */
#define ADC12_CDR_RDATA_SLV_10      ((uint32_t)0x04000000) /*!< RDATA_SLV bit 10 */
#define ADC12_CDR_RDATA_SLV_11      ((uint32_t)0x08000000) /*!< RDATA_SLV bit 11 */
#define ADC12_CDR_RDATA_SLV_12      ((uint32_t)0x10000000) /*!< RDATA_SLV bit 12 */
#define ADC12_CDR_RDATA_SLV_13      ((uint32_t)0x20000000) /*!< RDATA_SLV bit 13 */
#define ADC12_CDR_RDATA_SLV_14      ((uint32_t)0x40000000) /*!< RDATA_SLV bit 14 */
#define ADC12_CDR_RDATA_SLV_15      ((uint32_t)0x80000000) /*!< RDATA_SLV bit 15 */

/********************  Bit definition for ADC_CDR register  ********************/
#define ADC34_CDR_RDATA_MST         ((uint32_t)0x0000FFFF) /*!< Regular Data of the master ADC */
#define ADC34_CDR_RDATA_MST_0       ((uint32_t)0x00000001) /*!< RDATA_MST bit 0 */
#define ADC34_CDR_RDATA_MST_1       ((uint32_t)0x00000002) /*!< RDATA_MST bit 1 */
#define ADC34_CDR_RDATA_MST_2       ((uint32_t)0x00000004) /*!< RDATA_MST bit 2 */
#define ADC34_CDR_RDATA_MST_3       ((uint32_t)0x00000008) /*!< RDATA_MST bit 3 */
#define ADC34_CDR_RDATA_MST_4       ((uint32_t)0x00000010) /*!< RDATA_MST bit 4 */
#define ADC34_CDR_RDATA_MST_5       ((uint32_t)0x00000020) /*!< RDATA_MST bit 5 */
#define ADC34_CDR_RDATA_MST_6       ((uint32_t)0x00000040) /*!< RDATA_MST bit 6 */
#define ADC34_CDR_RDATA_MST_7       ((uint32_t)0x00000080) /*!< RDATA_MST bit 7 */
#define ADC34_CDR_RDATA_MST_8       ((uint32_t)0x00000100) /*!< RDATA_MST bit 8 */
#define ADC34_CDR_RDATA_MST_9       ((uint32_t)0x00000200) /*!< RDATA_MST bit 9 */
#define ADC34_CDR_RDATA_MST_10      ((uint32_t)0x00000400) /*!< RDATA_MST bit 10 */
#define ADC34_CDR_RDATA_MST_11      ((uint32_t)0x00000800) /*!< RDATA_MST bit 11 */
#define ADC34_CDR_RDATA_MST_12      ((uint32_t)0x00001000) /*!< RDATA_MST bit 12 */
#define ADC34_CDR_RDATA_MST_13      ((uint32_t)0x00002000) /*!< RDATA_MST bit 13 */
#define ADC34_CDR_RDATA_MST_14      ((uint32_t)0x00004000) /*!< RDATA_MST bit 14 */
#define ADC34_CDR_RDATA_MST_15      ((uint32_t)0x00008000) /*!< RDATA_MST bit 15 */

#define ADC34_CDR_RDATA_SLV         ((uint32_t)0xFFFF0000) /*!< Regular Data of the master ADC */
#define ADC34_CDR_RDATA_SLV_0       ((uint32_t)0x00010000) /*!< RDATA_SLV bit 0 */
#define ADC34_CDR_RDATA_SLV_1       ((uint32_t)0x00020000) /*!< RDATA_SLV bit 1 */
#define ADC34_CDR_RDATA_SLV_2       ((uint32_t)0x00040000) /*!< RDATA_SLV bit 2 */
#define ADC34_CDR_RDATA_SLV_3       ((uint32_t)0x00080000) /*!< RDATA_SLV bit 3 */
#define ADC34_CDR_RDATA_SLV_4       ((uint32_t)0x00100000) /*!< RDATA_SLV bit 4 */
#define ADC34_CDR_RDATA_SLV_5       ((uint32_t)0x00200000) /*!< RDATA_SLV bit 5 */
#define ADC34_CDR_RDATA_SLV_6       ((uint32_t)0x00400000) /*!< RDATA_SLV bit 6 */
#define ADC34_CDR_RDATA_SLV_7       ((uint32_t)0x00800000) /*!< RDATA_SLV bit 7 */
#define ADC34_CDR_RDATA_SLV_8       ((uint32_t)0x01000000) /*!< RDATA_SLV bit 8 */
#define ADC34_CDR_RDATA_SLV_9       ((uint32_t)0x02000000) /*!< RDATA_SLV bit 9 */
#define ADC34_CDR_RDATA_SLV_10      ((uint32_t)0x04000000) /*!< RDATA_SLV bit 10 */
#define ADC34_CDR_RDATA_SLV_11      ((uint32_t)0x08000000) /*!< RDATA_SLV bit 11 */
#define ADC34_CDR_RDATA_SLV_12      ((uint32_t)0x10000000) /*!< RDATA_SLV bit 12 */
#define ADC34_CDR_RDATA_SLV_13      ((uint32_t)0x20000000) /*!< RDATA_SLV bit 13 */
#define ADC34_CDR_RDATA_SLV_14      ((uint32_t)0x40000000) /*!< RDATA_SLV bit 14 */
#define ADC34_CDR_RDATA_SLV_15      ((uint32_t)0x80000000) /*!< RDATA_SLV bit 15 */

/******************************************************************************/
/*                                                                            */
/*                      Analog Comparators (COMP)                             */
/*                                                                            */
/******************************************************************************/
/**********************  Bit definition for COMP1_CSR register  ***************/
#define COMP1_CSR_COMP1EN               ((uint32_t)0x00000001) /*!< COMP1 enable */
#define COMP1_CSR_COMP1SW1              ((uint32_t)0x00000002) /*!< COMP1 SW1 switch control */
#define COMP1_CSR_COMP1MODE             ((uint32_t)0x0000000C) /*!< COMP1 power mode */
#define COMP1_CSR_COMP1MODE_0           ((uint32_t)0x00000004) /*!< COMP1 power mode bit 0 */
#define COMP1_CSR_COMP1MODE_1           ((uint32_t)0x00000008) /*!< COMP1 power mode bit 1 */
#define COMP1_CSR_COMP1INSEL            ((uint32_t)0x00000070) /*!< COMP1 inverting input select */
#define COMP1_CSR_COMP1INSEL_0          ((uint32_t)0x00000010) /*!< COMP1 inverting input select bit 0 */
#define COMP1_CSR_COMP1INSEL_1          ((uint32_t)0x00000020) /*!< COMP1 inverting input select bit 1 */
#define COMP1_CSR_COMP1INSEL_2          ((uint32_t)0x00000040) /*!< COMP1 inverting input select bit 2 */
#define COMP1_CSR_COMP1NONINSEL         ((uint32_t)0x00000080) /*!< COMP1 non inverting input select */
#define COMP1_CSR_COMP1OUTSEL           ((uint32_t)0x00003C00) /*!< COMP1 output select */
#define COMP1_CSR_COMP1OUTSEL_0         ((uint32_t)0x00000400) /*!< COMP1 output select bit 0 */
#define COMP1_CSR_COMP1OUTSEL_1         ((uint32_t)0x00000800) /*!< COMP1 output select bit 1 */
#define COMP1_CSR_COMP1OUTSEL_2         ((uint32_t)0x00001000) /*!< COMP1 output select bit 2 */
#define COMP1_CSR_COMP1OUTSEL_3         ((uint32_t)0x00002000) /*!< COMP1 output select bit 3 */
#define COMP1_CSR_COMP1POL              ((uint32_t)0x00008000) /*!< COMP1 output polarity */
#define COMP1_CSR_COMP1HYST             ((uint32_t)0x00030000) /*!< COMP1 hysteresis */
#define COMP1_CSR_COMP1HYST_0           ((uint32_t)0x00010000) /*!< COMP1 hysteresis bit 0 */
#define COMP1_CSR_COMP1HYST_1           ((uint32_t)0x00020000) /*!< COMP1 hysteresis bit 1 */
#define COMP1_CSR_COMP1BLANKING         ((uint32_t)0x000C0000) /*!< COMP1 blanking */
#define COMP1_CSR_COMP1BLANKING_0       ((uint32_t)0x00040000) /*!< COMP1 blanking bit 0 */
#define COMP1_CSR_COMP1BLANKING_1       ((uint32_t)0x00080000) /*!< COMP1 blanking bit 1 */
#define COMP1_CSR_COMP1BLANKING_2       ((uint32_t)0x00100000) /*!< COMP1 blanking bit 2 */
#define COMP1_CSR_COMP1OUT              ((uint32_t)0x40000000) /*!< COMP1 output level */
#define COMP1_CSR_COMP1LOCK             ((uint32_t)0x80000000) /*!< COMP1 lock */

/**********************  Bit definition for COMP2_CSR register  ***************/
#define COMP2_CSR_COMP2EN               ((uint32_t)0x00000001) /*!< COMP2 enable */
#define COMP2_CSR_COMP2MODE             ((uint32_t)0x0000000C) /*!< COMP2 power mode */
#define COMP2_CSR_COMP2MODE_0           ((uint32_t)0x00000004) /*!< COMP2 power mode bit 0 */
#define COMP2_CSR_COMP2MODE_1           ((uint32_t)0x00000008) /*!< COMP2 power mode bit 1 */
#define COMP2_CSR_COMP2INSEL            ((uint32_t)0x00000070) /*!< COMP2 inverting input select */
#define COMP2_CSR_COMP2INSEL_0          ((uint32_t)0x00000010) /*!< COMP2 inverting input select bit 0 */
#define COMP2_CSR_COMP2INSEL_1          ((uint32_t)0x00000020) /*!< COMP2 inverting input select bit 1 */
#define COMP2_CSR_COMP2INSEL_2          ((uint32_t)0x00000040) /*!< COMP2 inverting input select bit 2 */
#define COMP2_CSR_COMP2NONINSEL         ((uint32_t)0x00000080) /*!< COMP2 non inverting input select */
#define COMP2_CSR_COMP2WNDWEN           ((uint32_t)0x00000200) /*!< COMP2 window mode enable */
#define COMP2_CSR_COMP2OUTSEL           ((uint32_t)0x00003C00) /*!< COMP2 output select */
#define COMP2_CSR_COMP2OUTSEL_0         ((uint32_t)0x00000400) /*!< COMP2 output select bit 0 */
#define COMP2_CSR_COMP2OUTSEL_1         ((uint32_t)0x00000800) /*!< COMP2 output select bit 1 */
#define COMP2_CSR_COMP2OUTSEL_2         ((uint32_t)0x00001000) /*!< COMP2 output select bit 2 */
#define COMP2_CSR_COMP2OUTSEL_3         ((uint32_t)0x00002000) /*!< COMP2 output select bit 3 */
#define COMP2_CSR_COMP2POL              ((uint32_t)0x00008000) /*!< COMP2 output polarity */
#define COMP2_CSR_COMP2HYST             ((uint32_t)0x00030000) /*!< COMP2 hysteresis */
#define COMP2_CSR_COMP2HYST_0           ((uint32_t)0x00010000) /*!< COMP2 hysteresis bit 0 */
#define COMP2_CSR_COMP2HYST_1           ((uint32_t)0x00020000) /*!< COMP2 hysteresis bit 1 */
#define COMP2_CSR_COMP2BLANKING         ((uint32_t)0x000C0000) /*!< COMP2 blanking */
#define COMP2_CSR_COMP2BLANKING_0       ((uint32_t)0x00040000) /*!< COMP2 blanking bit 0 */
#define COMP2_CSR_COMP2BLANKING_1       ((uint32_t)0x00080000) /*!< COMP2 blanking bit 1 */
#define COMP2_CSR_COMP2BLANKING_2       ((uint32_t)0x00100000) /*!< COMP2 blanking bit 2 */
#define COMP2_CSR_COMP2OUT              ((uint32_t)0x40000000) /*!< COMP2 output level */
#define COMP2_CSR_COMP2LOCK             ((uint32_t)0x80000000) /*!< COMP2 lock */

/**********************  Bit definition for COMP3_CSR register  ***************/
#define COMP3_CSR_COMP3EN               ((uint32_t)0x00000001) /*!< COMP3 enable */
#define COMP3_CSR_COMP3MODE             ((uint32_t)0x0000000C) /*!< COMP3 power mode */
#define COMP3_CSR_COMP3MODE_0           ((uint32_t)0x00000004) /*!< COMP3 power mode bit 0 */
#define COMP3_CSR_COMP3MODE_1           ((uint32_t)0x00000008) /*!< COMP3 power mode bit 1 */
#define COMP3_CSR_COMP3INSEL            ((uint32_t)0x00000070) /*!< COMP3 inverting input select */
#define COMP3_CSR_COMP3INSEL_0          ((uint32_t)0x00000010) /*!< COMP3 inverting input select bit 0 */
#define COMP3_CSR_COMP3INSEL_1          ((uint32_t)0x00000020) /*!< COMP3 inverting input select bit 1 */
#define COMP3_CSR_COMP3INSEL_2          ((uint32_t)0x00000040) /*!< COMP3 inverting input select bit 2 */
#define COMP3_CSR_COMP3NONINSEL         ((uint32_t)0x00000080) /*!< COMP3 non inverting input select */
#define COMP3_CSR_COMP3OUTSEL           ((uint32_t)0x00003C00) /*!< COMP3 output select */
#define COMP3_CSR_COMP3OUTSEL_0         ((uint32_t)0x00000400) /*!< COMP3 output select bit 0 */
#define COMP3_CSR_COMP3OUTSEL_1         ((uint32_t)0x00000800) /*!< COMP3 output select bit 1 */
#define COMP3_CSR_COMP3OUTSEL_2         ((uint32_t)0x00001000) /*!< COMP3 output select bit 2 */
#define COMP3_CSR_COMP3OUTSEL_3         ((uint32_t)0x00002000) /*!< COMP3 output select bit 3 */
#define COMP3_CSR_COMP3POL              ((uint32_t)0x00008000) /*!< COMP3 output polarity */
#define COMP3_CSR_COMP3HYST             ((uint32_t)0x00030000) /*!< COMP3 hysteresis */
#define COMP3_CSR_COMP3HYST_0           ((uint32_t)0x00010000) /*!< COMP3 hysteresis bit 0 */
#define COMP3_CSR_COMP3HYST_1           ((uint32_t)0x00020000) /*!< COMP3 hysteresis bit 1 */
#define COMP3_CSR_COMP3BLANKING         ((uint32_t)0x000C0000) /*!< COMP3 blanking */
#define COMP3_CSR_COMP3BLANKING_0       ((uint32_t)0x00040000) /*!< COMP3 blanking bit 0 */
#define COMP3_CSR_COMP3BLANKING_1       ((uint32_t)0x00080000) /*!< COMP3 blanking bit 1 */
#define COMP3_CSR_COMP3BLANKING_2       ((uint32_t)0x00100000) /*!< COMP3 blanking bit 2 */
#define COMP3_CSR_COMP3OUT              ((uint32_t)0x40000000) /*!< COMP3 output level */
#define COMP3_CSR_COMP3LOCK             ((uint32_t)0x80000000) /*!< COMP3 lock */

/**********************  Bit definition for COMP4_CSR register  ***************/
#define COMP4_CSR_COMP4EN               ((uint32_t)0x00000001) /*!< COMP4 enable */
#define COMP4_CSR_COMP4MODE             ((uint32_t)0x0000000C) /*!< COMP4 power mode */
#define COMP4_CSR_COMP4MODE_0           ((uint32_t)0x00000004) /*!< COMP4 power mode bit 0 */
#define COMP4_CSR_COMP4MODE_1           ((uint32_t)0x00000008) /*!< COMP4 power mode bit 1 */
#define COMP4_CSR_COMP4INSEL            ((uint32_t)0x00000070) /*!< COMP4 inverting input select */
#define COMP4_CSR_COMP4INSEL_0          ((uint32_t)0x00000010) /*!< COMP4 inverting input select bit 0 */
#define COMP4_CSR_COMP4INSEL_1          ((uint32_t)0x00000020) /*!< COMP4 inverting input select bit 1 */
#define COMP4_CSR_COMP4INSEL_2          ((uint32_t)0x00000040) /*!< COMP4 inverting input select bit 2 */
#define COMP4_CSR_COMP4NONINSEL         ((uint32_t)0x00000080) /*!< COMP4 non inverting input select */
#define COMP4_CSR_COMP4WNDWEN           ((uint32_t)0x00000200) /*!< COMP4 window mode enable */
#define COMP4_CSR_COMP4OUTSEL           ((uint32_t)0x00003C00) /*!< COMP4 output select */
#define COMP4_CSR_COMP4OUTSEL_0         ((uint32_t)0x00000400) /*!< COMP4 output select bit 0 */
#define COMP4_CSR_COMP4OUTSEL_1         ((uint32_t)0x00000800) /*!< COMP4 output select bit 1 */
#define COMP4_CSR_COMP4OUTSEL_2         ((uint32_t)0x00001000) /*!< COMP4 output select bit 2 */
#define COMP4_CSR_COMP4OUTSEL_3         ((uint32_t)0x00002000) /*!< COMP4 output select bit 3 */
#define COMP4_CSR_COMP4POL              ((uint32_t)0x00008000) /*!< COMP4 output polarity */
#define COMP4_CSR_COMP4HYST             ((uint32_t)0x00030000) /*!< COMP4 hysteresis */
#define COMP4_CSR_COMP4HYST_0           ((uint32_t)0x00010000) /*!< COMP4 hysteresis bit 0 */
#define COMP4_CSR_COMP4HYST_1           ((uint32_t)0x00020000) /*!< COMP4 hysteresis bit 1 */
#define COMP4_CSR_COMP4BLANKING         ((uint32_t)0x000C0000) /*!< COMP4 blanking */
#define COMP4_CSR_COMP4BLANKING_0       ((uint32_t)0x00040000) /*!< COMP4 blanking bit 0 */
#define COMP4_CSR_COMP4BLANKING_1       ((uint32_t)0x00080000) /*!< COMP4 blanking bit 1 */
#define COMP4_CSR_COMP4BLANKING_2       ((uint32_t)0x00100000) /*!< COMP4 blanking bit 2 */
#define COMP4_CSR_COMP4OUT              ((uint32_t)0x40000000) /*!< COMP4 output level */
#define COMP4_CSR_COMP4LOCK             ((uint32_t)0x80000000) /*!< COMP4 lock */

/**********************  Bit definition for COMP5_CSR register  ***************/
#define COMP5_CSR_COMP5EN               ((uint32_t)0x00000001) /*!< COMP5 enable */
#define COMP5_CSR_COMP5MODE             ((uint32_t)0x0000000C) /*!< COMP5 power mode */
#define COMP5_CSR_COMP5MODE_0           ((uint32_t)0x00000004) /*!< COMP5 power mode bit 0 */
#define COMP5_CSR_COMP5MODE_1           ((uint32_t)0x00000008) /*!< COMP5 power mode bit 1 */
#define COMP5_CSR_COMP5INSEL            ((uint32_t)0x00000070) /*!< COMP5 inverting input select */
#define COMP5_CSR_COMP5INSEL_0          ((uint32_t)0x00000010) /*!< COMP5 inverting input select bit 0 */
#define COMP5_CSR_COMP5INSEL_1          ((uint32_t)0x00000020) /*!< COMP5 inverting input select bit 1 */
#define COMP5_CSR_COMP5INSEL_2          ((uint32_t)0x00000040) /*!< COMP5 inverting input select bit 2 */
#define COMP5_CSR_COMP5NONINSEL         ((uint32_t)0x00000080) /*!< COMP5 non inverting input select */
#define COMP5_CSR_COMP5OUTSEL           ((uint32_t)0x00003C00) /*!< COMP5 output select */
#define COMP5_CSR_COMP5OUTSEL_0         ((uint32_t)0x00000400) /*!< COMP5 output select bit 0 */
#define COMP5_CSR_COMP5OUTSEL_1         ((uint32_t)0x00000800) /*!< COMP5 output select bit 1 */
#define COMP5_CSR_COMP5OUTSEL_2         ((uint32_t)0x00001000) /*!< COMP5 output select bit 2 */
#define COMP5_CSR_COMP5OUTSEL_3         ((uint32_t)0x00002000) /*!< COMP5 output select bit 3 */
#define COMP5_CSR_COMP5POL              ((uint32_t)0x00008000) /*!< COMP5 output polarity */
#define COMP5_CSR_COMP5HYST             ((uint32_t)0x00030000) /*!< COMP5 hysteresis */
#define COMP5_CSR_COMP5HYST_0           ((uint32_t)0x00010000) /*!< COMP5 hysteresis bit 0 */
#define COMP5_CSR_COMP5HYST_1           ((uint32_t)0x00020000) /*!< COMP5 hysteresis bit 1 */
#define COMP5_CSR_COMP5BLANKING         ((uint32_t)0x000C0000) /*!< COMP5 blanking */
#define COMP5_CSR_COMP5BLANKING_0       ((uint32_t)0x00040000) /*!< COMP5 blanking bit 0 */
#define COMP5_CSR_COMP5BLANKING_1       ((uint32_t)0x00080000) /*!< COMP5 blanking bit 1 */
#define COMP5_CSR_COMP5BLANKING_2       ((uint32_t)0x00100000) /*!< COMP5 blanking bit 2 */
#define COMP5_CSR_COMP5OUT              ((uint32_t)0x40000000) /*!< COMP5 output level */
#define COMP5_CSR_COMP5LOCK             ((uint32_t)0x80000000) /*!< COMP5 lock */

/**********************  Bit definition for COMP6_CSR register  ***************/
#define COMP6_CSR_COMP6EN               ((uint32_t)0x00000001) /*!< COMP6 enable */
#define COMP6_CSR_COMP6MODE             ((uint32_t)0x0000000C) /*!< COMP6 power mode */
#define COMP6_CSR_COMP6MODE_0           ((uint32_t)0x00000004) /*!< COMP6 power mode bit 0 */
#define COMP6_CSR_COMP6MODE_1           ((uint32_t)0x00000008) /*!< COMP6 power mode bit 1 */
#define COMP6_CSR_COMP6INSEL            ((uint32_t)0x00000070) /*!< COMP6 inverting input select */
#define COMP6_CSR_COMP6INSEL_0          ((uint32_t)0x00000010) /*!< COMP6 inverting input select bit 0 */
#define COMP6_CSR_COMP6INSEL_1          ((uint32_t)0x00000020) /*!< COMP6 inverting input select bit 1 */
#define COMP6_CSR_COMP6INSEL_2          ((uint32_t)0x00000040) /*!< COMP6 inverting input select bit 2 */
#define COMP6_CSR_COMP6NONINSEL         ((uint32_t)0x00000080) /*!< COMP6 non inverting input select */
#define COMP6_CSR_COMP6WNDWEN           ((uint32_t)0x00000200) /*!< COMP6 window mode enable */
#define COMP6_CSR_COMP6OUTSEL           ((uint32_t)0x00003C00) /*!< COMP6 output select */
#define COMP6_CSR_COMP6OUTSEL_0         ((uint32_t)0x00000400) /*!< COMP6 output select bit 0 */
#define COMP6_CSR_COMP6OUTSEL_1         ((uint32_t)0x00000800) /*!< COMP6 output select bit 1 */
#define COMP6_CSR_COMP6OUTSEL_2         ((uint32_t)0x00001000) /*!< COMP6 output select bit 2 */
#define COMP6_CSR_COMP6OUTSEL_3         ((uint32_t)0x00002000) /*!< COMP6 output select bit 3 */
#define COMP6_CSR_COMP6POL              ((uint32_t)0x00008000) /*!< COMP6 output polarity */
#define COMP6_CSR_COMP6HYST             ((uint32_t)0x00030000) /*!< COMP6 hysteresis */
#define COMP6_CSR_COMP6HYST_0           ((uint32_t)0x00010000) /*!< COMP6 hysteresis bit 0 */
#define COMP6_CSR_COMP6HYST_1           ((uint32_t)0x00020000) /*!< COMP6 hysteresis bit 1 */
#define COMP6_CSR_COMP6BLANKING         ((uint32_t)0x000C0000) /*!< COMP6 blanking */
#define COMP6_CSR_COMP6BLANKING_0       ((uint32_t)0x00040000) /*!< COMP6 blanking bit 0 */
#define COMP6_CSR_COMP6BLANKING_1       ((uint32_t)0x00080000) /*!< COMP6 blanking bit 1 */
#define COMP6_CSR_COMP6BLANKING_2       ((uint32_t)0x00100000) /*!< COMP6 blanking bit 2 */
#define COMP6_CSR_COMP6OUT              ((uint32_t)0x40000000) /*!< COMP6 output level */
#define COMP6_CSR_COMP6LOCK             ((uint32_t)0x80000000) /*!< COMP6 lock */

/**********************  Bit definition for COMP7_CSR register  ***************/
#define COMP7_CSR_COMP7EN               ((uint32_t)0x00000001) /*!< COMP7 enable */
#define COMP7_CSR_COMP7MODE             ((uint32_t)0x0000000C) /*!< COMP7 power mode */
#define COMP7_CSR_COMP7MODE_0           ((uint32_t)0x00000004) /*!< COMP7 power mode bit 0 */
#define COMP7_CSR_COMP7MODE_1           ((uint32_t)0x00000008) /*!< COMP7 power mode bit 1 */
#define COMP7_CSR_COMP7INSEL            ((uint32_t)0x00000070) /*!< COMP7 inverting input select */
#define COMP7_CSR_COMP7INSEL_0          ((uint32_t)0x00000010) /*!< COMP7 inverting input select bit 0 */
#define COMP7_CSR_COMP7INSEL_1          ((uint32_t)0x00000020) /*!< COMP7 inverting input select bit 1 */
#define COMP7_CSR_COMP7INSEL_2          ((uint32_t)0x00000040) /*!< COMP7 inverting input select bit 2 */
#define COMP7_CSR_COMP7NONINSEL         ((uint32_t)0x00000080) /*!< COMP7 non inverting input select */
#define COMP7_CSR_COMP7OUTSEL           ((uint32_t)0x00003C00) /*!< COMP7 output select */
#define COMP7_CSR_COMP7OUTSEL_0         ((uint32_t)0x00000400) /*!< COMP7 output select bit 0 */
#define COMP7_CSR_COMP7OUTSEL_1         ((uint32_t)0x00000800) /*!< COMP7 output select bit 1 */
#define COMP7_CSR_COMP7OUTSEL_2         ((uint32_t)0x00001000) /*!< COMP7 output select bit 2 */
#define COMP7_CSR_COMP7OUTSEL_3         ((uint32_t)0x00002000) /*!< COMP7 output select bit 3 */
#define COMP7_CSR_COMP7POL              ((uint32_t)0x00008000) /*!< COMP7 output polarity */
#define COMP7_CSR_COMP7HYST             ((uint32_t)0x00030000) /*!< COMP7 hysteresis */
#define COMP7_CSR_COMP7HYST_0           ((uint32_t)0x00010000) /*!< COMP7 hysteresis bit 0 */
#define COMP7_CSR_COMP7HYST_1           ((uint32_t)0x00020000) /*!< COMP7 hysteresis bit 1 */
#define COMP7_CSR_COMP7BLANKING         ((uint32_t)0x000C0000) /*!< COMP7 blanking */
#define COMP7_CSR_COMP7BLANKING_0       ((uint32_t)0x00040000) /*!< COMP7 blanking bit 0 */
#define COMP7_CSR_COMP7BLANKING_1       ((uint32_t)0x00080000) /*!< COMP7 blanking bit 1 */
#define COMP7_CSR_COMP7BLANKING_2       ((uint32_t)0x00100000) /*!< COMP7 blanking bit 2 */
#define COMP7_CSR_COMP7OUT              ((uint32_t)0x40000000) /*!< COMP7 output level */
#define COMP7_CSR_COMP7LOCK             ((uint32_t)0x80000000) /*!< COMP7 lock */

/**********************  Bit definition for COMP_CSR register  ****************/
#define COMP_CSR_COMPxEN               ((uint32_t)0x00000001) /*!< COMPx enable */
#define COMP_CSR_COMP1SW1              ((uint32_t)0x00000002) /*!< COMP1 SW1 switch control */
#define COMP_CSR_COMPxMODE             ((uint32_t)0x0000000C) /*!< COMPx power mode */
#define COMP_CSR_COMPxMODE_0           ((uint32_t)0x00000004) /*!< COMPx power mode bit 0 */
#define COMP_CSR_COMPxMODE_1           ((uint32_t)0x00000008) /*!< COMPx power mode bit 1 */
#define COMP_CSR_COMPxINSEL            ((uint32_t)0x00000070) /*!< COMPx inverting input select */
#define COMP_CSR_COMPxINSEL_0          ((uint32_t)0x00000010) /*!< COMPx inverting input select bit 0 */
#define COMP_CSR_COMPxINSEL_1          ((uint32_t)0x00000020) /*!< COMPx inverting input select bit 1 */
#define COMP_CSR_COMPxINSEL_2          ((uint32_t)0x00000040) /*!< COMPx inverting input select bit 2 */
#define COMP_CSR_COMPxNONINSEL         ((uint32_t)0x00000080) /*!< COMPx non inverting input select */
#define COMP_CSR_COMPxWNDWEN           ((uint32_t)0x00000200) /*!< COMPx window mode enable */
#define COMP_CSR_COMPxOUTSEL           ((uint32_t)0x00003C00) /*!< COMPx output select */
#define COMP_CSR_COMPxOUTSEL_0         ((uint32_t)0x00000400) /*!< COMPx output select bit 0 */
#define COMP_CSR_COMPxOUTSEL_1         ((uint32_t)0x00000800) /*!< COMPx output select bit 1 */
#define COMP_CSR_COMPxOUTSEL_2         ((uint32_t)0x00001000) /*!< COMPx output select bit 2 */
#define COMP_CSR_COMPxOUTSEL_3         ((uint32_t)0x00002000) /*!< COMPx output select bit 3 */
#define COMP_CSR_COMPxPOL              ((uint32_t)0x00008000) /*!< COMPx output polarity */
#define COMP_CSR_COMPxHYST             ((uint32_t)0x00030000) /*!< COMPx hysteresis */
#define COMP_CSR_COMPxHYST_0           ((uint32_t)0x00010000) /*!< COMPx hysteresis bit 0 */
#define COMP_CSR_COMPxHYST_1           ((uint32_t)0x00020000) /*!< COMPx hysteresis bit 1 */
#define COMP_CSR_COMPxBLANKING         ((uint32_t)0x000C0000) /*!< COMPx blanking */
#define COMP_CSR_COMPxBLANKING_0       ((uint32_t)0x00040000) /*!< COMPx blanking bit 0 */
#define COMP_CSR_COMPxBLANKING_1       ((uint32_t)0x00080000) /*!< COMPx blanking bit 1 */
#define COMP_CSR_COMPxBLANKING_2       ((uint32_t)0x00100000) /*!< COMPx blanking bit 2 */
#define COMP_CSR_COMPxINSEL_3          ((uint32_t)0x00400000) /*!< COMPx inverting input select bit 3 */
#define COMP_CSR_COMPxOUT              ((uint32_t)0x40000000) /*!< COMPx output level */
#define COMP_CSR_COMPxLOCK             ((uint32_t)0x80000000) /*!< COMPx lock */

/******************************************************************************/
/*                                                                            */
/*                     Operational Amplifier (OPAMP)                          */
/*                                                                            */
/******************************************************************************/
/*********************  Bit definition for OPAMP1_CSR register  ***************/
#define OPAMP1_CSR_OPAMP1EN               ((uint32_t)0x00000001) /*!< OPAMP1 enable */
#define OPAMP1_CSR_FORCEVP                ((uint32_t)0x00000002) /*!< Connect the internal references to the plus input of the OPAMPX */
#define OPAMP1_CSR_VPSEL                  ((uint32_t)0x0000000C) /*!< Non inverting input selection */
#define OPAMP1_CSR_VPSEL_0                ((uint32_t)0x00000004) /*!< Bit 0 */
#define OPAMP1_CSR_VPSEL_1                ((uint32_t)0x00000008) /*!< Bit 1 */
#define OPAMP1_CSR_VMSEL                  ((uint32_t)0x00000060) /*!< Inverting input selection */
#define OPAMP1_CSR_VMSEL_0                ((uint32_t)0x00000020) /*!< Bit 0 */
#define OPAMP1_CSR_VMSEL_1                ((uint32_t)0x00000040) /*!< Bit 1 */
#define OPAMP1_CSR_TCMEN                  ((uint32_t)0x00000080) /*!< Timer-Controlled Mux mode enable */
#define OPAMP1_CSR_VMSSEL                 ((uint32_t)0x00000100) /*!< Inverting input secondary selection */
#define OPAMP1_CSR_VPSSEL                 ((uint32_t)0x00000600) /*!< Non inverting input secondary selection */
#define OPAMP1_CSR_VPSSEL_0               ((uint32_t)0x00000200) /*!< Bit 0 */
#define OPAMP1_CSR_VPSSEL_1               ((uint32_t)0x00000400) /*!< Bit 1 */
#define OPAMP1_CSR_CALON                  ((uint32_t)0x00000800) /*!< Calibration mode enable */
#define OPAMP1_CSR_CALSEL                 ((uint32_t)0x00003000) /*!< Calibration selection */
#define OPAMP1_CSR_CALSEL_0               ((uint32_t)0x00001000) /*!< Bit 0 */
#define OPAMP1_CSR_CALSEL_1               ((uint32_t)0x00002000) /*!< Bit 1 */
#define OPAMP1_CSR_PGGAIN                 ((uint32_t)0x0003C000) /*!< Gain in PGA mode */
#define OPAMP1_CSR_PGGAIN_0               ((uint32_t)0x00004000) /*!< Bit 0 */
#define OPAMP1_CSR_PGGAIN_1               ((uint32_t)0x00008000) /*!< Bit 1 */
#define OPAMP1_CSR_PGGAIN_2               ((uint32_t)0x00010000) /*!< Bit 2 */
#define OPAMP1_CSR_PGGAIN_3               ((uint32_t)0x00020000) /*!< Bit 3 */
#define OPAMP1_CSR_USERTRIM               ((uint32_t)0x00040000) /*!< User trimming enable */
#define OPAMP1_CSR_TRIMOFFSETP            ((uint32_t)0x00F80000) /*!< Offset trimming value (PMOS) */
#define OPAMP1_CSR_TRIMOFFSETN            ((uint32_t)0x1F000000) /*!< Offset trimming value (NMOS) */
#define OPAMP1_CSR_TSTREF                 ((uint32_t)0x20000000) /*!< It enables the switch to put out the internal reference */
#define OPAMP1_CSR_OUTCAL                 ((uint32_t)0x40000000) /*!< OPAMP output status flag */
#define OPAMP1_CSR_LOCK                   ((uint32_t)0x80000000) /*!< OPAMP lock */

/*********************  Bit definition for OPAMP2_CSR register  ***************/
#define OPAMP2_CSR_OPAMP2EN               ((uint32_t)0x00000001) /*!< OPAMP2 enable */
#define OPAMP2_CSR_FORCEVP                ((uint32_t)0x00000002) /*!< Connect the internal references to the plus input of the OPAMPX */
#define OPAMP2_CSR_VPSEL                  ((uint32_t)0x0000000C) /*!< Non inverting input selection */
#define OPAMP2_CSR_VPSEL_0                ((uint32_t)0x00000004) /*!< Bit 0 */
#define OPAMP2_CSR_VPSEL_1                ((uint32_t)0x00000008) /*!< Bit 1 */
#define OPAMP2_CSR_VMSEL                  ((uint32_t)0x00000060) /*!< Inverting input selection */
#define OPAMP2_CSR_VMSEL_0                ((uint32_t)0x00000020) /*!< Bit 0 */
#define OPAMP2_CSR_VMSEL_1                ((uint32_t)0x00000040) /*!< Bit 1 */
#define OPAMP2_CSR_TCMEN                  ((uint32_t)0x00000080) /*!< Timer-Controlled Mux mode enable */
#define OPAMP2_CSR_VMSSEL                 ((uint32_t)0x00000100) /*!< Inverting input secondary selection */
#define OPAMP2_CSR_VPSSEL                 ((uint32_t)0x00000600) /*!< Non inverting input secondary selection */
#define OPAMP2_CSR_VPSSEL_0               ((uint32_t)0x00000200) /*!< Bit 0 */
#define OPAMP2_CSR_VPSSEL_1               ((uint32_t)0x00000400) /*!< Bit 1 */
#define OPAMP2_CSR_CALON                  ((uint32_t)0x00000800) /*!< Calibration mode enable */
#define OPAMP2_CSR_CALSEL                 ((uint32_t)0x00003000) /*!< Calibration selection */
#define OPAMP2_CSR_CALSEL_0               ((uint32_t)0x00001000) /*!< Bit 0 */
#define OPAMP2_CSR_CALSEL_1               ((uint32_t)0x00002000) /*!< Bit 1 */
#define OPAMP2_CSR_PGGAIN                 ((uint32_t)0x0003C000) /*!< Gain in PGA mode */
#define OPAMP2_CSR_PGGAIN_0               ((uint32_t)0x00004000) /*!< Bit 0 */
#define OPAMP2_CSR_PGGAIN_1               ((uint32_t)0x00008000) /*!< Bit 1 */
#define OPAMP2_CSR_PGGAIN_2               ((uint32_t)0x00010000) /*!< Bit 2 */
#define OPAMP2_CSR_PGGAIN_3               ((uint32_t)0x00020000) /*!< Bit 3 */
#define OPAMP2_CSR_USERTRIM               ((uint32_t)0x00040000) /*!< User trimming enable */
#define OPAMP2_CSR_TRIMOFFSETP            ((uint32_t)0x00F80000) /*!< Offset trimming value (PMOS) */
#define OPAMP2_CSR_TRIMOFFSETN            ((uint32_t)0x1F000000) /*!< Offset trimming value (NMOS) */
#define OPAMP2_CSR_TSTREF                 ((uint32_t)0x20000000) /*!< It enables the switch to put out the internal reference */
#define OPAMP2_CSR_OUTCAL                 ((uint32_t)0x40000000) /*!< OPAMP output status flag */
#define OPAMP2_CSR_LOCK                   ((uint32_t)0x80000000) /*!< OPAMP lock */

/*********************  Bit definition for OPAMP3_CSR register  ***************/
#define OPAMP3_CSR_OPAMP3EN               ((uint32_t)0x00000001) /*!< OPAMP3 enable */
#define OPAMP3_CSR_FORCEVP                ((uint32_t)0x00000002) /*!< Connect the internal references to the plus input of the OPAMPX */
#define OPAMP3_CSR_VPSEL                  ((uint32_t)0x0000000C) /*!< Non inverting input selection */
#define OPAMP3_CSR_VPSEL_0                ((uint32_t)0x00000004) /*!< Bit 0 */
#define OPAMP3_CSR_VPSEL_1                ((uint32_t)0x00000008) /*!< Bit 1 */
#define OPAMP3_CSR_VMSEL                  ((uint32_t)0x00000060) /*!< Inverting input selection */
#define OPAMP3_CSR_VMSEL_0                ((uint32_t)0x00000020) /*!< Bit 0 */
#define OPAMP3_CSR_VMSEL_1                ((uint32_t)0x00000040) /*!< Bit 1 */
#define OPAMP3_CSR_TCMEN                  ((uint32_t)0x00000080) /*!< Timer-Controlled Mux mode enable */
#define OPAMP3_CSR_VMSSEL                 ((uint32_t)0x00000100) /*!< Inverting input secondary selection */
#define OPAMP3_CSR_VPSSEL                 ((uint32_t)0x00000600) /*!< Non inverting input secondary selection */
#define OPAMP3_CSR_VPSSEL_0               ((uint32_t)0x00000200) /*!< Bit 0 */
#define OPAMP3_CSR_VPSSEL_1               ((uint32_t)0x00000400) /*!< Bit 1 */
#define OPAMP3_CSR_CALON                  ((uint32_t)0x00000800) /*!< Calibration mode enable */
#define OPAMP3_CSR_CALSEL                 ((uint32_t)0x00003000) /*!< Calibration selection */
#define OPAMP3_CSR_CALSEL_0               ((uint32_t)0x00001000) /*!< Bit 0 */
#define OPAMP3_CSR_CALSEL_1               ((uint32_t)0x00002000) /*!< Bit 1 */
#define OPAMP3_CSR_PGGAIN                 ((uint32_t)0x0003C000) /*!< Gain in PGA mode */
#define OPAMP3_CSR_PGGAIN_0               ((uint32_t)0x00004000) /*!< Bit 0 */
#define OPAMP3_CSR_PGGAIN_1               ((uint32_t)0x00008000) /*!< Bit 1 */
#define OPAMP3_CSR_PGGAIN_2               ((uint32_t)0x00010000) /*!< Bit 2 */
#define OPAMP3_CSR_PGGAIN_3               ((uint32_t)0x00020000) /*!< Bit 3 */
#define OPAMP3_CSR_USERTRIM               ((uint32_t)0x00040000) /*!< User trimming enable */
#define OPAMP3_CSR_TRIMOFFSETP            ((uint32_t)0x00F80000) /*!< Offset trimming value (PMOS) */
#define OPAMP3_CSR_TRIMOFFSETN            ((uint32_t)0x1F000000) /*!< Offset trimming value (NMOS) */
#define OPAMP3_CSR_TSTREF                 ((uint32_t)0x20000000) /*!< It enables the switch to put out the internal reference */
#define OPAMP3_CSR_OUTCAL                 ((uint32_t)0x40000000) /*!< OPAMP output status flag */
#define OPAMP3_CSR_LOCK                   ((uint32_t)0x80000000) /*!< OPAMP lock */

/*********************  Bit definition for OPAMP4_CSR register  ***************/
#define OPAMP4_CSR_OPAMP4EN               ((uint32_t)0x00000001) /*!< OPAMP4 enable */
#define OPAMP4_CSR_FORCEVP                ((uint32_t)0x00000002) /*!< Connect the internal references to the plus input of the OPAMPX */
#define OPAMP4_CSR_VPSEL                  ((uint32_t)0x0000000C) /*!< Non inverting input selection */
#define OPAMP4_CSR_VPSEL_0                ((uint32_t)0x00000004) /*!< Bit 0 */
#define OPAMP4_CSR_VPSEL_1                ((uint32_t)0x00000008) /*!< Bit 1 */
#define OPAMP4_CSR_VMSEL                  ((uint32_t)0x00000060) /*!< Inverting input selection */
#define OPAMP4_CSR_VMSEL_0                ((uint32_t)0x00000020) /*!< Bit 0 */
#define OPAMP4_CSR_VMSEL_1                ((uint32_t)0x00000040) /*!< Bit 1 */
#define OPAMP4_CSR_TCMEN                  ((uint32_t)0x00000080) /*!< Timer-Controlled Mux mode enable */
#define OPAMP4_CSR_VMSSEL                 ((uint32_t)0x00000100) /*!< Inverting input secondary selection */
#define OPAMP4_CSR_VPSSEL                 ((uint32_t)0x00000600) /*!< Non inverting input secondary selection */
#define OPAMP4_CSR_VPSSEL_0               ((uint32_t)0x00000200) /*!< Bit 0 */
#define OPAMP4_CSR_VPSSEL_1               ((uint32_t)0x00000400) /*!< Bit 1 */
#define OPAMP4_CSR_CALON                  ((uint32_t)0x00000800) /*!< Calibration mode enable */
#define OPAMP4_CSR_CALSEL                 ((uint32_t)0x00003000) /*!< Calibration selection */
#define OPAMP4_CSR_CALSEL_0               ((uint32_t)0x00001000) /*!< Bit 0 */
#define OPAMP4_CSR_CALSEL_1               ((uint32_t)0x00002000) /*!< Bit 1 */
#define OPAMP4_CSR_PGGAIN                 ((uint32_t)0x0003C000) /*!< Gain in PGA mode */
#define OPAMP4_CSR_PGGAIN_0               ((uint32_t)0x00004000) /*!< Bit 0 */
#define OPAMP4_CSR_PGGAIN_1               ((uint32_t)0x00008000) /*!< Bit 1 */
#define OPAMP4_CSR_PGGAIN_2               ((uint32_t)0x00010000) /*!< Bit 2 */
#define OPAMP4_CSR_PGGAIN_3               ((uint32_t)0x00020000) /*!< Bit 3 */
#define OPAMP4_CSR_USERTRIM               ((uint32_t)0x00040000) /*!< User trimming enable */
#define OPAMP4_CSR_TRIMOFFSETP            ((uint32_t)0x00F80000) /*!< Offset trimming value (PMOS) */
#define OPAMP4_CSR_TRIMOFFSETN            ((uint32_t)0x1F000000) /*!< Offset trimming value (NMOS) */
#define OPAMP4_CSR_TSTREF                 ((uint32_t)0x20000000) /*!< It enables the switch to put out the internal reference */
#define OPAMP4_CSR_OUTCAL                 ((uint32_t)0x40000000) /*!< OPAMP output status flag */
#define OPAMP4_CSR_LOCK                   ((uint32_t)0x80000000) /*!< OPAMP lock */

/*********************  Bit definition for OPAMPx_CSR register  ***************/
#define OPAMP_CSR_OPAMPxEN               ((uint32_t)0x00000001) /*!< OPAMP enable */
#define OPAMP_CSR_FORCEVP                ((uint32_t)0x00000002) /*!< Connect the internal references to the plus input of the OPAMPX */
#define OPAMP_CSR_VPSEL                  ((uint32_t)0x0000000C) /*!< Non inverting input selection */
#define OPAMP_CSR_VPSEL_0                ((uint32_t)0x00000004) /*!< Bit 0 */
#define OPAMP_CSR_VPSEL_1                ((uint32_t)0x00000008) /*!< Bit 1 */
#define OPAMP_CSR_VMSEL                  ((uint32_t)0x00000060) /*!< Inverting input selection */
#define OPAMP_CSR_VMSEL_0                ((uint32_t)0x00000020) /*!< Bit 0 */
#define OPAMP_CSR_VMSEL_1                ((uint32_t)0x00000040) /*!< Bit 1 */
#define OPAMP_CSR_TCMEN                  ((uint32_t)0x00000080) /*!< Timer-Controlled Mux mode enable */
#define OPAMP_CSR_VMSSEL                 ((uint32_t)0x00000100) /*!< Inverting input secondary selection */
#define OPAMP_CSR_VPSSEL                 ((uint32_t)0x00000600) /*!< Non inverting input secondary selection */
#define OPAMP_CSR_VPSSEL_0               ((uint32_t)0x00000200) /*!< Bit 0 */
#define OPAMP_CSR_VPSSEL_1               ((uint32_t)0x00000400) /*!< Bit 1 */
#define OPAMP_CSR_CALON                  ((uint32_t)0x00000800) /*!< Calibration mode enable */
#define OPAMP_CSR_CALSEL                 ((uint32_t)0x00003000) /*!< Calibration selection */
#define OPAMP_CSR_CALSEL_0               ((uint32_t)0x00001000) /*!< Bit 0 */
#define OPAMP_CSR_CALSEL_1               ((uint32_t)0x00002000) /*!< Bit 1 */
#define OPAMP_CSR_PGGAIN                 ((uint32_t)0x0003C000) /*!< Gain in PGA mode */
#define OPAMP_CSR_PGGAIN_0               ((uint32_t)0x00004000) /*!< Bit 0 */
#define OPAMP_CSR_PGGAIN_1               ((uint32_t)0x00008000) /*!< Bit 1 */
#define OPAMP_CSR_PGGAIN_2               ((uint32_t)0x00010000) /*!< Bit 2 */
#define OPAMP_CSR_PGGAIN_3               ((uint32_t)0x00020000) /*!< Bit 3 */
#define OPAMP_CSR_USERTRIM               ((uint32_t)0x00040000) /*!< User trimming enable */
#define OPAMP_CSR_TRIMOFFSETP            ((uint32_t)0x00F80000) /*!< Offset trimming value (PMOS) */
#define OPAMP_CSR_TRIMOFFSETN            ((uint32_t)0x1F000000) /*!< Offset trimming value (NMOS) */
#define OPAMP_CSR_TSTREF                 ((uint32_t)0x20000000) /*!< It enables the switch to put out the internal reference */
#define OPAMP_CSR_OUTCAL                 ((uint32_t)0x40000000) /*!< OPAMP output status flag */
#define OPAMP_CSR_LOCK                   ((uint32_t)0x80000000) /*!< OPAMP lock */


/******************************************************************************/
/*                                                                            */
/*                   Controller Area Network (CAN )                           */
/*                                                                            */
/******************************************************************************/
/*!<CAN control and status registers */
/*******************  Bit definition for CAN_MCR register  ********************/
#define  CAN_MCR_INRQ                        ((uint16_t)0x0001)            /*!<Initialization Request */
#define  CAN_MCR_SLEEP                       ((uint16_t)0x0002)            /*!<Sleep Mode Request */
#define  CAN_MCR_TXFP                        ((uint16_t)0x0004)            /*!<Transmit FIFO Priority */
#define  CAN_MCR_RFLM                        ((uint16_t)0x0008)            /*!<Receive FIFO Locked Mode */
#define  CAN_MCR_NART                        ((uint16_t)0x0010)            /*!<No Automatic Retransmission */
#define  CAN_MCR_AWUM                        ((uint16_t)0x0020)            /*!<Automatic Wakeup Mode */
#define  CAN_MCR_ABOM                        ((uint16_t)0x0040)            /*!<Automatic Bus-Off Management */
#define  CAN_MCR_TTCM                        ((uint16_t)0x0080)            /*!<Time Triggered Communication Mode */
#define  CAN_MCR_RESET                       ((uint16_t)0x8000)            /*!<bxCAN software master reset */

/*******************  Bit definition for CAN_MSR register  ********************/
#define  CAN_MSR_INAK                        ((uint16_t)0x0001)            /*!<Initialization Acknowledge */
#define  CAN_MSR_SLAK                        ((uint16_t)0x0002)            /*!<Sleep Acknowledge */
#define  CAN_MSR_ERRI                        ((uint16_t)0x0004)            /*!<Error Interrupt */
#define  CAN_MSR_WKUI                        ((uint16_t)0x0008)            /*!<Wakeup Interrupt */
#define  CAN_MSR_SLAKI                       ((uint16_t)0x0010)            /*!<Sleep Acknowledge Interrupt */
#define  CAN_MSR_TXM                         ((uint16_t)0x0100)            /*!<Transmit Mode */
#define  CAN_MSR_RXM                         ((uint16_t)0x0200)            /*!<Receive Mode */
#define  CAN_MSR_SAMP                        ((uint16_t)0x0400)            /*!<Last Sample Point */
#define  CAN_MSR_RX                          ((uint16_t)0x0800)            /*!<CAN Rx Signal */

/*******************  Bit definition for CAN_TSR register  ********************/
#define  CAN_TSR_RQCP0                       ((uint32_t)0x00000001)        /*!<Request Completed Mailbox0 */
#define  CAN_TSR_TXOK0                       ((uint32_t)0x00000002)        /*!<Transmission OK of Mailbox0 */
#define  CAN_TSR_ALST0                       ((uint32_t)0x00000004)        /*!<Arbitration Lost for Mailbox0 */
#define  CAN_TSR_TERR0                       ((uint32_t)0x00000008)        /*!<Transmission Error of Mailbox0 */
#define  CAN_TSR_ABRQ0                       ((uint32_t)0x00000080)        /*!<Abort Request for Mailbox0 */
#define  CAN_TSR_RQCP1                       ((uint32_t)0x00000100)        /*!<Request Completed Mailbox1 */
#define  CAN_TSR_TXOK1                       ((uint32_t)0x00000200)        /*!<Transmission OK of Mailbox1 */
#define  CAN_TSR_ALST1                       ((uint32_t)0x00000400)        /*!<Arbitration Lost for Mailbox1 */
#define  CAN_TSR_TERR1                       ((uint32_t)0x00000800)        /*!<Transmission Error of Mailbox1 */
#define  CAN_TSR_ABRQ1                       ((uint32_t)0x00008000)        /*!<Abort Request for Mailbox 1 */
#define  CAN_TSR_RQCP2                       ((uint32_t)0x00010000)        /*!<Request Completed Mailbox2 */
#define  CAN_TSR_TXOK2                       ((uint32_t)0x00020000)        /*!<Transmission OK of Mailbox 2 */
#define  CAN_TSR_ALST2                       ((uint32_t)0x00040000)        /*!<Arbitration Lost for mailbox 2 */
#define  CAN_TSR_TERR2                       ((uint32_t)0x00080000)        /*!<Transmission Error of Mailbox 2 */
#define  CAN_TSR_ABRQ2                       ((uint32_t)0x00800000)        /*!<Abort Request for Mailbox 2 */
#define  CAN_TSR_CODE                        ((uint32_t)0x03000000)        /*!<Mailbox Code */

#define  CAN_TSR_TME                         ((uint32_t)0x1C000000)        /*!<TME[2:0] bits */
#define  CAN_TSR_TME0                        ((uint32_t)0x04000000)        /*!<Transmit Mailbox 0 Empty */
#define  CAN_TSR_TME1                        ((uint32_t)0x08000000)        /*!<Transmit Mailbox 1 Empty */
#define  CAN_TSR_TME2                        ((uint32_t)0x10000000)        /*!<Transmit Mailbox 2 Empty */

#define  CAN_TSR_LOW                         ((uint32_t)0xE0000000)        /*!<LOW[2:0] bits */
#define  CAN_TSR_LOW0                        ((uint32_t)0x20000000)        /*!<Lowest Priority Flag for Mailbox 0 */
#define  CAN_TSR_LOW1                        ((uint32_t)0x40000000)        /*!<Lowest Priority Flag for Mailbox 1 */
#define  CAN_TSR_LOW2                        ((uint32_t)0x80000000)        /*!<Lowest Priority Flag for Mailbox 2 */

/*******************  Bit definition for CAN_RF0R register  *******************/
#define  CAN_RF0R_FMP0                       ((uint8_t)0x03)               /*!<FIFO 0 Message Pending */
#define  CAN_RF0R_FULL0                      ((uint8_t)0x08)               /*!<FIFO 0 Full */
#define  CAN_RF0R_FOVR0                      ((uint8_t)0x10)               /*!<FIFO 0 Overrun */
#define  CAN_RF0R_RFOM0                      ((uint8_t)0x20)               /*!<Release FIFO 0 Output Mailbox */

/*******************  Bit definition for CAN_RF1R register  *******************/
#define  CAN_RF1R_FMP1                       ((uint8_t)0x03)               /*!<FIFO 1 Message Pending */
#define  CAN_RF1R_FULL1                      ((uint8_t)0x08)               /*!<FIFO 1 Full */
#define  CAN_RF1R_FOVR1                      ((uint8_t)0x10)               /*!<FIFO 1 Overrun */
#define  CAN_RF1R_RFOM1                      ((uint8_t)0x20)               /*!<Release FIFO 1 Output Mailbox */

/********************  Bit definition for CAN_IER register  *******************/
#define  CAN_IER_TMEIE                       ((uint32_t)0x00000001)        /*!<Transmit Mailbox Empty Interrupt Enable */
#define  CAN_IER_FMPIE0                      ((uint32_t)0x00000002)        /*!<FIFO Message Pending Interrupt Enable */
#define  CAN_IER_FFIE0                       ((uint32_t)0x00000004)        /*!<FIFO Full Interrupt Enable */
#define  CAN_IER_FOVIE0                      ((uint32_t)0x00000008)        /*!<FIFO Overrun Interrupt Enable */
#define  CAN_IER_FMPIE1                      ((uint32_t)0x00000010)        /*!<FIFO Message Pending Interrupt Enable */
#define  CAN_IER_FFIE1                       ((uint32_t)0x00000020)        /*!<FIFO Full Interrupt Enable */
#define  CAN_IER_FOVIE1                      ((uint32_t)0x00000040)        /*!<FIFO Overrun Interrupt Enable */
#define  CAN_IER_EWGIE                       ((uint32_t)0x00000100)        /*!<Error Warning Interrupt Enable */
#define  CAN_IER_EPVIE                       ((uint32_t)0x00000200)        /*!<Error Passive Interrupt Enable */
#define  CAN_IER_BOFIE                       ((uint32_t)0x00000400)        /*!<Bus-Off Interrupt Enable */
#define  CAN_IER_LECIE                       ((uint32_t)0x00000800)        /*!<Last Error Code Interrupt Enable */
#define  CAN_IER_ERRIE                       ((uint32_t)0x00008000)        /*!<Error Interrupt Enable */
#define  CAN_IER_WKUIE                       ((uint32_t)0x00010000)        /*!<Wakeup Interrupt Enable */
#define  CAN_IER_SLKIE                       ((uint32_t)0x00020000)        /*!<Sleep Interrupt Enable */

/********************  Bit definition for CAN_ESR register  *******************/
#define  CAN_ESR_EWGF                        ((uint32_t)0x00000001)        /*!<Error Warning Flag */
#define  CAN_ESR_EPVF                        ((uint32_t)0x00000002)        /*!<Error Passive Flag */
#define  CAN_ESR_BOFF                        ((uint32_t)0x00000004)        /*!<Bus-Off Flag */

#define  CAN_ESR_LEC                         ((uint32_t)0x00000070)        /*!<LEC[2:0] bits (Last Error Code) */
#define  CAN_ESR_LEC_0                       ((uint32_t)0x00000010)        /*!<Bit 0 */
#define  CAN_ESR_LEC_1                       ((uint32_t)0x00000020)        /*!<Bit 1 */
#define  CAN_ESR_LEC_2                       ((uint32_t)0x00000040)        /*!<Bit 2 */

#define  CAN_ESR_TEC                         ((uint32_t)0x00FF0000)        /*!<Least significant byte of the 9-bit Transmit Error Counter */
#define  CAN_ESR_REC                         ((uint32_t)0xFF000000)        /*!<Receive Error Counter */

/*******************  Bit definition for CAN_BTR register  ********************/
#define  CAN_BTR_BRP                         ((uint32_t)0x000003FF)        /*!<Baud Rate Prescaler */
#define  CAN_BTR_TS1                         ((uint32_t)0x000F0000)        /*!<Time Segment 1 */
#define  CAN_BTR_TS2                         ((uint32_t)0x00700000)        /*!<Time Segment 2 */
#define  CAN_BTR_SJW                         ((uint32_t)0x03000000)        /*!<Resynchronization Jump Width */
#define  CAN_BTR_LBKM                        ((uint32_t)0x40000000)        /*!<Loop Back Mode (Debug) */
#define  CAN_BTR_SILM                        ((uint32_t)0x80000000)        /*!<Silent Mode */

/*!<Mailbox registers */
/******************  Bit definition for CAN_TI0R register  ********************/
#define  CAN_TI0R_TXRQ                       ((uint32_t)0x00000001)        /*!<Transmit Mailbox Request */
#define  CAN_TI0R_RTR                        ((uint32_t)0x00000002)        /*!<Remote Transmission Request */
#define  CAN_TI0R_IDE                        ((uint32_t)0x00000004)        /*!<Identifier Extension */
#define  CAN_TI0R_EXID                       ((uint32_t)0x001FFFF8)        /*!<Extended Identifier */
#define  CAN_TI0R_STID                       ((uint32_t)0xFFE00000)        /*!<Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TDT0R register  *******************/
#define  CAN_TDT0R_DLC                       ((uint32_t)0x0000000F)        /*!<Data Length Code */
#define  CAN_TDT0R_TGT                       ((uint32_t)0x00000100)        /*!<Transmit Global Time */
#define  CAN_TDT0R_TIME                      ((uint32_t)0xFFFF0000)        /*!<Message Time Stamp */

/******************  Bit definition for CAN_TDL0R register  *******************/
#define  CAN_TDL0R_DATA0                     ((uint32_t)0x000000FF)        /*!<Data byte 0 */
#define  CAN_TDL0R_DATA1                     ((uint32_t)0x0000FF00)        /*!<Data byte 1 */
#define  CAN_TDL0R_DATA2                     ((uint32_t)0x00FF0000)        /*!<Data byte 2 */
#define  CAN_TDL0R_DATA3                     ((uint32_t)0xFF000000)        /*!<Data byte 3 */

/******************  Bit definition for CAN_TDH0R register  *******************/
#define  CAN_TDH0R_DATA4                     ((uint32_t)0x000000FF)        /*!<Data byte 4 */
#define  CAN_TDH0R_DATA5                     ((uint32_t)0x0000FF00)        /*!<Data byte 5 */
#define  CAN_TDH0R_DATA6                     ((uint32_t)0x00FF0000)        /*!<Data byte 6 */
#define  CAN_TDH0R_DATA7                     ((uint32_t)0xFF000000)        /*!<Data byte 7 */

/*******************  Bit definition for CAN_TI1R register  *******************/
#define  CAN_TI1R_TXRQ                       ((uint32_t)0x00000001)        /*!<Transmit Mailbox Request */
#define  CAN_TI1R_RTR                        ((uint32_t)0x00000002)        /*!<Remote Transmission Request */
#define  CAN_TI1R_IDE                        ((uint32_t)0x00000004)        /*!<Identifier Extension */
#define  CAN_TI1R_EXID                       ((uint32_t)0x001FFFF8)        /*!<Extended Identifier */
#define  CAN_TI1R_STID                       ((uint32_t)0xFFE00000)        /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT1R register  ******************/
#define  CAN_TDT1R_DLC                       ((uint32_t)0x0000000F)        /*!<Data Length Code */
#define  CAN_TDT1R_TGT                       ((uint32_t)0x00000100)        /*!<Transmit Global Time */
#define  CAN_TDT1R_TIME                      ((uint32_t)0xFFFF0000)        /*!<Message Time Stamp */

/*******************  Bit definition for CAN_TDL1R register  ******************/
#define  CAN_TDL1R_DATA0                     ((uint32_t)0x000000FF)        /*!<Data byte 0 */
#define  CAN_TDL1R_DATA1                     ((uint32_t)0x0000FF00)        /*!<Data byte 1 */
#define  CAN_TDL1R_DATA2                     ((uint32_t)0x00FF0000)        /*!<Data byte 2 */
#define  CAN_TDL1R_DATA3                     ((uint32_t)0xFF000000)        /*!<Data byte 3 */

/*******************  Bit definition for CAN_TDH1R register  ******************/
#define  CAN_TDH1R_DATA4                     ((uint32_t)0x000000FF)        /*!<Data byte 4 */
#define  CAN_TDH1R_DATA5                     ((uint32_t)0x0000FF00)        /*!<Data byte 5 */
#define  CAN_TDH1R_DATA6                     ((uint32_t)0x00FF0000)        /*!<Data byte 6 */
#define  CAN_TDH1R_DATA7                     ((uint32_t)0xFF000000)        /*!<Data byte 7 */

/*******************  Bit definition for CAN_TI2R register  *******************/
#define  CAN_TI2R_TXRQ                       ((uint32_t)0x00000001)        /*!<Transmit Mailbox Request */
#define  CAN_TI2R_RTR                        ((uint32_t)0x00000002)        /*!<Remote Transmission Request */
#define  CAN_TI2R_IDE                        ((uint32_t)0x00000004)        /*!<Identifier Extension */
#define  CAN_TI2R_EXID                       ((uint32_t)0x001FFFF8)        /*!<Extended identifier */
#define  CAN_TI2R_STID                       ((uint32_t)0xFFE00000)        /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT2R register  ******************/  
#define  CAN_TDT2R_DLC                       ((uint32_t)0x0000000F)        /*!<Data Length Code */
#define  CAN_TDT2R_TGT                       ((uint32_t)0x00000100)        /*!<Transmit Global Time */
#define  CAN_TDT2R_TIME                      ((uint32_t)0xFFFF0000)        /*!<Message Time Stamp */

/*******************  Bit definition for CAN_TDL2R register  ******************/
#define  CAN_TDL2R_DATA0                     ((uint32_t)0x000000FF)        /*!<Data byte 0 */
#define  CAN_TDL2R_DATA1                     ((uint32_t)0x0000FF00)        /*!<Data byte 1 */
#define  CAN_TDL2R_DATA2                     ((uint32_t)0x00FF0000)        /*!<Data byte 2 */
#define  CAN_TDL2R_DATA3                     ((uint32_t)0xFF000000)        /*!<Data byte 3 */

/*******************  Bit definition for CAN_TDH2R register  ******************/
#define  CAN_TDH2R_DATA4                     ((uint32_t)0x000000FF)        /*!<Data byte 4 */
#define  CAN_TDH2R_DATA5                     ((uint32_t)0x0000FF00)        /*!<Data byte 5 */
#define  CAN_TDH2R_DATA6                     ((uint32_t)0x00FF0000)        /*!<Data byte 6 */
#define  CAN_TDH2R_DATA7                     ((uint32_t)0xFF000000)        /*!<Data byte 7 */

/*******************  Bit definition for CAN_RI0R register  *******************/
#define  CAN_RI0R_RTR                        ((uint32_t)0x00000002)        /*!<Remote Transmission Request */
#define  CAN_RI0R_IDE                        ((uint32_t)0x00000004)        /*!<Identifier Extension */
#define  CAN_RI0R_EXID                       ((uint32_t)0x001FFFF8)        /*!<Extended Identifier */
#define  CAN_RI0R_STID                       ((uint32_t)0xFFE00000)        /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT0R register  ******************/
#define  CAN_RDT0R_DLC                       ((uint32_t)0x0000000F)        /*!<Data Length Code */
#define  CAN_RDT0R_FMI                       ((uint32_t)0x0000FF00)        /*!<Filter Match Index */
#define  CAN_RDT0R_TIME                      ((uint32_t)0xFFFF0000)        /*!<Message Time Stamp */

/*******************  Bit definition for CAN_RDL0R register  ******************/
#define  CAN_RDL0R_DATA0                     ((uint32_t)0x000000FF)        /*!<Data byte 0 */
#define  CAN_RDL0R_DATA1                     ((uint32_t)0x0000FF00)        /*!<Data byte 1 */
#define  CAN_RDL0R_DATA2                     ((uint32_t)0x00FF0000)        /*!<Data byte 2 */
#define  CAN_RDL0R_DATA3                     ((uint32_t)0xFF000000)        /*!<Data byte 3 */

/*******************  Bit definition for CAN_RDH0R register  ******************/
#define  CAN_RDH0R_DATA4                     ((uint32_t)0x000000FF)        /*!<Data byte 4 */
#define  CAN_RDH0R_DATA5                     ((uint32_t)0x0000FF00)        /*!<Data byte 5 */
#define  CAN_RDH0R_DATA6                     ((uint32_t)0x00FF0000)        /*!<Data byte 6 */
#define  CAN_RDH0R_DATA7                     ((uint32_t)0xFF000000)        /*!<Data byte 7 */

/*******************  Bit definition for CAN_RI1R register  *******************/
#define  CAN_RI1R_RTR                        ((uint32_t)0x00000002)        /*!<Remote Transmission Request */
#define  CAN_RI1R_IDE                        ((uint32_t)0x00000004)        /*!<Identifier Extension */
#define  CAN_RI1R_EXID                       ((uint32_t)0x001FFFF8)        /*!<Extended identifier */
#define  CAN_RI1R_STID                       ((uint32_t)0xFFE00000)        /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT1R register  ******************/
#define  CAN_RDT1R_DLC                       ((uint32_t)0x0000000F)        /*!<Data Length Code */
#define  CAN_RDT1R_FMI                       ((uint32_t)0x0000FF00)        /*!<Filter Match Index */
#define  CAN_RDT1R_TIME                      ((uint32_t)0xFFFF0000)        /*!<Message Time Stamp */

/*******************  Bit definition for CAN_RDL1R register  ******************/
#define  CAN_RDL1R_DATA0                     ((uint32_t)0x000000FF)        /*!<Data byte 0 */
#define  CAN_RDL1R_DATA1                     ((uint32_t)0x0000FF00)        /*!<Data byte 1 */
#define  CAN_RDL1R_DATA2                     ((uint32_t)0x00FF0000)        /*!<Data byte 2 */
#define  CAN_RDL1R_DATA3                     ((uint32_t)0xFF000000)        /*!<Data byte 3 */

/*******************  Bit definition for CAN_RDH1R register  ******************/
#define  CAN_RDH1R_DATA4                     ((uint32_t)0x000000FF)        /*!<Data byte 4 */
#define  CAN_RDH1R_DATA5                     ((uint32_t)0x0000FF00)        /*!<Data byte 5 */
#define  CAN_RDH1R_DATA6                     ((uint32_t)0x00FF0000)        /*!<Data byte 6 */
#define  CAN_RDH1R_DATA7                     ((uint32_t)0xFF000000)        /*!<Data byte 7 */

/*!<CAN filter registers */
/*******************  Bit definition for CAN_FMR register  ********************/
#define  CAN_FMR_FINIT                       ((uint8_t)0x01)               /*!<Filter Init Mode */

/*******************  Bit definition for CAN_FM1R register  *******************/
#define  CAN_FM1R_FBM                        ((uint16_t)0x3FFF)            /*!<Filter Mode */
#define  CAN_FM1R_FBM0                       ((uint16_t)0x0001)            /*!<Filter Init Mode bit 0 */
#define  CAN_FM1R_FBM1                       ((uint16_t)0x0002)            /*!<Filter Init Mode bit 1 */
#define  CAN_FM1R_FBM2                       ((uint16_t)0x0004)            /*!<Filter Init Mode bit 2 */
#define  CAN_FM1R_FBM3                       ((uint16_t)0x0008)            /*!<Filter Init Mode bit 3 */
#define  CAN_FM1R_FBM4                       ((uint16_t)0x0010)            /*!<Filter Init Mode bit 4 */
#define  CAN_FM1R_FBM5                       ((uint16_t)0x0020)            /*!<Filter Init Mode bit 5 */
#define  CAN_FM1R_FBM6                       ((uint16_t)0x0040)            /*!<Filter Init Mode bit 6 */
#define  CAN_FM1R_FBM7                       ((uint16_t)0x0080)            /*!<Filter Init Mode bit 7 */
#define  CAN_FM1R_FBM8                       ((uint16_t)0x0100)            /*!<Filter Init Mode bit 8 */
#define  CAN_FM1R_FBM9                       ((uint16_t)0x0200)            /*!<Filter Init Mode bit 9 */
#define  CAN_FM1R_FBM10                      ((uint16_t)0x0400)            /*!<Filter Init Mode bit 10 */
#define  CAN_FM1R_FBM11                      ((uint16_t)0x0800)            /*!<Filter Init Mode bit 11 */
#define  CAN_FM1R_FBM12                      ((uint16_t)0x1000)            /*!<Filter Init Mode bit 12 */
#define  CAN_FM1R_FBM13                      ((uint16_t)0x2000)            /*!<Filter Init Mode bit 13 */

/*******************  Bit definition for CAN_FS1R register  *******************/
#define  CAN_FS1R_FSC                        ((uint16_t)0x3FFF)            /*!<Filter Scale Configuration */
#define  CAN_FS1R_FSC0                       ((uint16_t)0x0001)            /*!<Filter Scale Configuration bit 0 */
#define  CAN_FS1R_FSC1                       ((uint16_t)0x0002)            /*!<Filter Scale Configuration bit 1 */
#define  CAN_FS1R_FSC2                       ((uint16_t)0x0004)            /*!<Filter Scale Configuration bit 2 */
#define  CAN_FS1R_FSC3                       ((uint16_t)0x0008)            /*!<Filter Scale Configuration bit 3 */
#define  CAN_FS1R_FSC4                       ((uint16_t)0x0010)            /*!<Filter Scale Configuration bit 4 */
#define  CAN_FS1R_FSC5                       ((uint16_t)0x0020)            /*!<Filter Scale Configuration bit 5 */
#define  CAN_FS1R_FSC6                       ((uint16_t)0x0040)            /*!<Filter Scale Configuration bit 6 */
#define  CAN_FS1R_FSC7                       ((uint16_t)0x0080)            /*!<Filter Scale Configuration bit 7 */
#define  CAN_FS1R_FSC8                       ((uint16_t)0x0100)            /*!<Filter Scale Configuration bit 8 */
#define  CAN_FS1R_FSC9                       ((uint16_t)0x0200)            /*!<Filter Scale Configuration bit 9 */
#define  CAN_FS1R_FSC10                      ((uint16_t)0x0400)            /*!<Filter Scale Configuration bit 10 */
#define  CAN_FS1R_FSC11                      ((uint16_t)0x0800)            /*!<Filter Scale Configuration bit 11 */
#define  CAN_FS1R_FSC12                      ((uint16_t)0x1000)            /*!<Filter Scale Configuration bit 12 */
#define  CAN_FS1R_FSC13                      ((uint16_t)0x2000)            /*!<Filter Scale Configuration bit 13 */

/******************  Bit definition for CAN_FFA1R register  *******************/
#define  CAN_FFA1R_FFA                       ((uint16_t)0x3FFF)            /*!<Filter FIFO Assignment */
#define  CAN_FFA1R_FFA0                      ((uint16_t)0x0001)            /*!<Filter FIFO Assignment for Filter 0 */
#define  CAN_FFA1R_FFA1                      ((uint16_t)0x0002)            /*!<Filter FIFO Assignment for Filter 1 */
#define  CAN_FFA1R_FFA2                      ((uint16_t)0x0004)            /*!<Filter FIFO Assignment for Filter 2 */
#define  CAN_FFA1R_FFA3                      ((uint16_t)0x0008)            /*!<Filter FIFO Assignment for Filter 3 */
#define  CAN_FFA1R_FFA4                      ((uint16_t)0x0010)            /*!<Filter FIFO Assignment for Filter 4 */
#define  CAN_FFA1R_FFA5                      ((uint16_t)0x0020)            /*!<Filter FIFO Assignment for Filter 5 */
#define  CAN_FFA1R_FFA6                      ((uint16_t)0x0040)            /*!<Filter FIFO Assignment for Filter 6 */
#define  CAN_FFA1R_FFA7                      ((uint16_t)0x0080)            /*!<Filter FIFO Assignment for Filter 7 */
#define  CAN_FFA1R_FFA8                      ((uint16_t)0x0100)            /*!<Filter FIFO Assignment for Filter 8 */
#define  CAN_FFA1R_FFA9                      ((uint16_t)0x0200)            /*!<Filter FIFO Assignment for Filter 9 */
#define  CAN_FFA1R_FFA10                     ((uint16_t)0x0400)            /*!<Filter FIFO Assignment for Filter 10 */
#define  CAN_FFA1R_FFA11                     ((uint16_t)0x0800)            /*!<Filter FIFO Assignment for Filter 11 */
#define  CAN_FFA1R_FFA12                     ((uint16_t)0x1000)            /*!<Filter FIFO Assignment for Filter 12 */
#define  CAN_FFA1R_FFA13                     ((uint16_t)0x2000)            /*!<Filter FIFO Assignment for Filter 13 */

/*******************  Bit definition for CAN_FA1R register  *******************/
#define  CAN_FA1R_FACT                       ((uint16_t)0x3FFF)            /*!<Filter Active */
#define  CAN_FA1R_FACT0                      ((uint16_t)0x0001)            /*!<Filter 0 Active */
#define  CAN_FA1R_FACT1                      ((uint16_t)0x0002)            /*!<Filter 1 Active */
#define  CAN_FA1R_FACT2                      ((uint16_t)0x0004)            /*!<Filter 2 Active */
#define  CAN_FA1R_FACT3                      ((uint16_t)0x0008)            /*!<Filter 3 Active */
#define  CAN_FA1R_FACT4                      ((uint16_t)0x0010)            /*!<Filter 4 Active */
#define  CAN_FA1R_FACT5                      ((uint16_t)0x0020)            /*!<Filter 5 Active */
#define  CAN_FA1R_FACT6                      ((uint16_t)0x0040)            /*!<Filter 6 Active */
#define  CAN_FA1R_FACT7                      ((uint16_t)0x0080)            /*!<Filter 7 Active */
#define  CAN_FA1R_FACT8                      ((uint16_t)0x0100)            /*!<Filter 8 Active */
#define  CAN_FA1R_FACT9                      ((uint16_t)0x0200)            /*!<Filter 9 Active */
#define  CAN_FA1R_FACT10                     ((uint16_t)0x0400)            /*!<Filter 10 Active */
#define  CAN_FA1R_FACT11                     ((uint16_t)0x0800)            /*!<Filter 11 Active */
#define  CAN_FA1R_FACT12                     ((uint16_t)0x1000)            /*!<Filter 12 Active */
#define  CAN_FA1R_FACT13                     ((uint16_t)0x2000)            /*!<Filter 13 Active */

/*******************  Bit definition for CAN_F0R1 register  *******************/
#define  CAN_F0R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F0R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F0R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F0R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F0R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F0R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F0R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F0R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F0R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F0R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F0R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F0R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F0R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F0R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F0R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F0R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F0R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F0R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F0R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F0R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F0R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F0R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F0R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F0R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F0R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F0R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F0R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F0R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F0R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F0R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F0R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F0R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F1R1 register  *******************/
#define  CAN_F1R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F1R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F1R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F1R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F1R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F1R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F1R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F1R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F1R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F1R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F1R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F1R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F1R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F1R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F1R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F1R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F1R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F1R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F1R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F1R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F1R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F1R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F1R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F1R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F1R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F1R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F1R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F1R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F1R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F1R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F1R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F1R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F2R1 register  *******************/
#define  CAN_F2R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F2R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F2R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F2R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F2R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F2R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F2R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F2R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F2R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F2R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F2R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F2R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F2R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F2R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F2R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F2R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F2R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F2R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F2R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F2R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F2R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F2R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F2R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F2R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F2R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F2R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F2R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F2R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F2R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F2R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F2R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F2R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F3R1 register  *******************/
#define  CAN_F3R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F3R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F3R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F3R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F3R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F3R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F3R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F3R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F3R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F3R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F3R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F3R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F3R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F3R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F3R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F3R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F3R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F3R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F3R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F3R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F3R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F3R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F3R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F3R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F3R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F3R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F3R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F3R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F3R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F3R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F3R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F3R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F4R1 register  *******************/
#define  CAN_F4R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F4R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F4R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F4R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F4R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F4R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F4R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F4R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F4R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F4R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F4R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F4R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F4R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F4R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F4R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F4R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F4R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F4R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F4R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F4R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F4R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F4R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F4R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F4R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F4R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F4R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F4R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F4R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F4R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F4R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F4R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F4R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F5R1 register  *******************/
#define  CAN_F5R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F5R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F5R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F5R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F5R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F5R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F5R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F5R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F5R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F5R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F5R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F5R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F5R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F5R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F5R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F5R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F5R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F5R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F5R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F5R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F5R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F5R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F5R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F5R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F5R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F5R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F5R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F5R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F5R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F5R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F5R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F5R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F6R1 register  *******************/
#define  CAN_F6R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F6R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F6R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F6R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F6R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F6R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F6R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F6R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F6R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F6R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F6R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F6R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F6R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F6R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F6R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F6R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F6R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F6R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F6R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F6R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F6R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F6R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F6R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F6R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F6R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F6R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F6R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F6R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F6R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F6R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F6R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F6R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F7R1 register  *******************/
#define  CAN_F7R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F7R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F7R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F7R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F7R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F7R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F7R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F7R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F7R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F7R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F7R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F7R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F7R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F7R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F7R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F7R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F7R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F7R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F7R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F7R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F7R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F7R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F7R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F7R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F7R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F7R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F7R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F7R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F7R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F7R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F7R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F7R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F8R1 register  *******************/
#define  CAN_F8R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F8R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F8R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F8R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F8R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F8R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F8R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F8R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F8R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F8R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F8R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F8R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F8R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F8R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F8R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F8R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F8R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F8R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F8R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F8R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F8R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F8R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F8R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F8R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F8R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F8R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F8R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F8R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F8R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F8R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F8R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F8R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F9R1 register  *******************/
#define  CAN_F9R1_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F9R1_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F9R1_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F9R1_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F9R1_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F9R1_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F9R1_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F9R1_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F9R1_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F9R1_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F9R1_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F9R1_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F9R1_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F9R1_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F9R1_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F9R1_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F9R1_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F9R1_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F9R1_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F9R1_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F9R1_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F9R1_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F9R1_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F9R1_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F9R1_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F9R1_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F9R1_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F9R1_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F9R1_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F9R1_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F9R1_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F9R1_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F10R1 register  ******************/
#define  CAN_F10R1_FB0                       ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F10R1_FB1                       ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F10R1_FB2                       ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F10R1_FB3                       ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F10R1_FB4                       ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F10R1_FB5                       ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F10R1_FB6                       ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F10R1_FB7                       ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F10R1_FB8                       ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F10R1_FB9                       ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F10R1_FB10                      ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F10R1_FB11                      ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F10R1_FB12                      ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F10R1_FB13                      ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F10R1_FB14                      ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F10R1_FB15                      ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F10R1_FB16                      ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F10R1_FB17                      ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F10R1_FB18                      ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F10R1_FB19                      ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F10R1_FB20                      ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F10R1_FB21                      ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F10R1_FB22                      ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F10R1_FB23                      ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F10R1_FB24                      ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F10R1_FB25                      ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F10R1_FB26                      ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F10R1_FB27                      ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F10R1_FB28                      ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F10R1_FB29                      ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F10R1_FB30                      ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F10R1_FB31                      ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F11R1 register  ******************/
#define  CAN_F11R1_FB0                       ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F11R1_FB1                       ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F11R1_FB2                       ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F11R1_FB3                       ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F11R1_FB4                       ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F11R1_FB5                       ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F11R1_FB6                       ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F11R1_FB7                       ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F11R1_FB8                       ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F11R1_FB9                       ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F11R1_FB10                      ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F11R1_FB11                      ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F11R1_FB12                      ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F11R1_FB13                      ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F11R1_FB14                      ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F11R1_FB15                      ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F11R1_FB16                      ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F11R1_FB17                      ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F11R1_FB18                      ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F11R1_FB19                      ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F11R1_FB20                      ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F11R1_FB21                      ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F11R1_FB22                      ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F11R1_FB23                      ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F11R1_FB24                      ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F11R1_FB25                      ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F11R1_FB26                      ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F11R1_FB27                      ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F11R1_FB28                      ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F11R1_FB29                      ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F11R1_FB30                      ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F11R1_FB31                      ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F12R1 register  ******************/
#define  CAN_F12R1_FB0                       ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F12R1_FB1                       ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F12R1_FB2                       ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F12R1_FB3                       ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F12R1_FB4                       ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F12R1_FB5                       ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F12R1_FB6                       ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F12R1_FB7                       ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F12R1_FB8                       ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F12R1_FB9                       ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F12R1_FB10                      ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F12R1_FB11                      ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F12R1_FB12                      ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F12R1_FB13                      ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F12R1_FB14                      ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F12R1_FB15                      ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F12R1_FB16                      ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F12R1_FB17                      ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F12R1_FB18                      ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F12R1_FB19                      ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F12R1_FB20                      ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F12R1_FB21                      ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F12R1_FB22                      ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F12R1_FB23                      ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F12R1_FB24                      ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F12R1_FB25                      ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F12R1_FB26                      ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F12R1_FB27                      ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F12R1_FB28                      ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F12R1_FB29                      ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F12R1_FB30                      ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F12R1_FB31                      ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F13R1 register  ******************/
#define  CAN_F13R1_FB0                       ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F13R1_FB1                       ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F13R1_FB2                       ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F13R1_FB3                       ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F13R1_FB4                       ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F13R1_FB5                       ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F13R1_FB6                       ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F13R1_FB7                       ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F13R1_FB8                       ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F13R1_FB9                       ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F13R1_FB10                      ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F13R1_FB11                      ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F13R1_FB12                      ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F13R1_FB13                      ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F13R1_FB14                      ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F13R1_FB15                      ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F13R1_FB16                      ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F13R1_FB17                      ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F13R1_FB18                      ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F13R1_FB19                      ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F13R1_FB20                      ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F13R1_FB21                      ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F13R1_FB22                      ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F13R1_FB23                      ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F13R1_FB24                      ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F13R1_FB25                      ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F13R1_FB26                      ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F13R1_FB27                      ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F13R1_FB28                      ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F13R1_FB29                      ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F13R1_FB30                      ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F13R1_FB31                      ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F0R2 register  *******************/
#define  CAN_F0R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F0R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F0R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F0R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F0R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F0R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F0R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F0R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F0R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F0R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F0R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F0R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F0R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F0R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F0R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F0R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F0R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F0R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F0R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F0R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F0R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F0R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F0R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F0R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F0R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F0R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F0R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F0R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F0R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F0R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F0R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F0R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F1R2 register  *******************/
#define  CAN_F1R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F1R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F1R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F1R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F1R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F1R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F1R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F1R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F1R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F1R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F1R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F1R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F1R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F1R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F1R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F1R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F1R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F1R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F1R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F1R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F1R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F1R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F1R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F1R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F1R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F1R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F1R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F1R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F1R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F1R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F1R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F1R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F2R2 register  *******************/
#define  CAN_F2R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F2R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F2R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F2R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F2R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F2R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F2R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F2R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F2R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F2R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F2R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F2R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F2R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F2R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F2R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F2R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F2R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F2R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F2R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F2R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F2R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F2R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F2R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F2R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F2R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F2R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F2R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F2R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F2R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F2R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F2R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F2R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F3R2 register  *******************/
#define  CAN_F3R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F3R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F3R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F3R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F3R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F3R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F3R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F3R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F3R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F3R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F3R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F3R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F3R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F3R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F3R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F3R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F3R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F3R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F3R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F3R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F3R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F3R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F3R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F3R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F3R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F3R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F3R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F3R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F3R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F3R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F3R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F3R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F4R2 register  *******************/
#define  CAN_F4R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F4R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F4R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F4R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F4R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F4R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F4R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F4R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F4R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F4R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F4R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F4R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F4R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F4R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F4R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F4R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F4R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F4R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F4R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F4R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F4R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F4R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F4R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F4R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F4R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F4R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F4R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F4R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F4R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F4R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F4R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F4R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F5R2 register  *******************/
#define  CAN_F5R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F5R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F5R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F5R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F5R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F5R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F5R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F5R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F5R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F5R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F5R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F5R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F5R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F5R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F5R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F5R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F5R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F5R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F5R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F5R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F5R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F5R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F5R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F5R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F5R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F5R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F5R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F5R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F5R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F5R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F5R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F5R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F6R2 register  *******************/
#define  CAN_F6R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F6R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F6R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F6R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F6R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F6R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F6R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F6R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F6R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F6R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F6R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F6R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F6R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F6R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F6R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F6R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F6R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F6R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F6R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F6R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F6R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F6R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F6R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F6R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F6R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F6R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F6R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F6R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F6R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F6R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F6R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F6R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F7R2 register  *******************/
#define  CAN_F7R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F7R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F7R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F7R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F7R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F7R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F7R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F7R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F7R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F7R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F7R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F7R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F7R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F7R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F7R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F7R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F7R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F7R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F7R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F7R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F7R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F7R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F7R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F7R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F7R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F7R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F7R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F7R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F7R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F7R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F7R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F7R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F8R2 register  *******************/
#define  CAN_F8R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F8R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F8R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F8R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F8R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F8R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F8R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F8R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F8R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F8R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F8R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F8R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F8R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F8R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F8R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F8R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F8R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F8R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F8R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F8R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F8R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F8R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F8R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F8R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F8R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F8R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F8R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F8R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F8R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F8R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F8R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F8R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F9R2 register  *******************/
#define  CAN_F9R2_FB0                        ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F9R2_FB1                        ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F9R2_FB2                        ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F9R2_FB3                        ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F9R2_FB4                        ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F9R2_FB5                        ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F9R2_FB6                        ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F9R2_FB7                        ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F9R2_FB8                        ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F9R2_FB9                        ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F9R2_FB10                       ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F9R2_FB11                       ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F9R2_FB12                       ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F9R2_FB13                       ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F9R2_FB14                       ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F9R2_FB15                       ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F9R2_FB16                       ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F9R2_FB17                       ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F9R2_FB18                       ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F9R2_FB19                       ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F9R2_FB20                       ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F9R2_FB21                       ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F9R2_FB22                       ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F9R2_FB23                       ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F9R2_FB24                       ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F9R2_FB25                       ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F9R2_FB26                       ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F9R2_FB27                       ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F9R2_FB28                       ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F9R2_FB29                       ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F9R2_FB30                       ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F9R2_FB31                       ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F10R2 register  ******************/
#define  CAN_F10R2_FB0                       ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F10R2_FB1                       ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F10R2_FB2                       ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F10R2_FB3                       ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F10R2_FB4                       ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F10R2_FB5                       ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F10R2_FB6                       ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F10R2_FB7                       ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F10R2_FB8                       ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F10R2_FB9                       ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F10R2_FB10                      ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F10R2_FB11                      ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F10R2_FB12                      ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F10R2_FB13                      ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F10R2_FB14                      ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F10R2_FB15                      ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F10R2_FB16                      ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F10R2_FB17                      ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F10R2_FB18                      ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F10R2_FB19                      ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F10R2_FB20                      ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F10R2_FB21                      ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F10R2_FB22                      ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F10R2_FB23                      ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F10R2_FB24                      ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F10R2_FB25                      ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F10R2_FB26                      ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F10R2_FB27                      ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F10R2_FB28                      ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F10R2_FB29                      ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F10R2_FB30                      ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F10R2_FB31                      ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F11R2 register  ******************/
#define  CAN_F11R2_FB0                       ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F11R2_FB1                       ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F11R2_FB2                       ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F11R2_FB3                       ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F11R2_FB4                       ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F11R2_FB5                       ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F11R2_FB6                       ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F11R2_FB7                       ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F11R2_FB8                       ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F11R2_FB9                       ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F11R2_FB10                      ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F11R2_FB11                      ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F11R2_FB12                      ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F11R2_FB13                      ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F11R2_FB14                      ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F11R2_FB15                      ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F11R2_FB16                      ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F11R2_FB17                      ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F11R2_FB18                      ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F11R2_FB19                      ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F11R2_FB20                      ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F11R2_FB21                      ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F11R2_FB22                      ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F11R2_FB23                      ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F11R2_FB24                      ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F11R2_FB25                      ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F11R2_FB26                      ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F11R2_FB27                      ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F11R2_FB28                      ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F11R2_FB29                      ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F11R2_FB30                      ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F11R2_FB31                      ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F12R2 register  ******************/
#define  CAN_F12R2_FB0                       ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F12R2_FB1                       ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F12R2_FB2                       ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F12R2_FB3                       ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F12R2_FB4                       ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F12R2_FB5                       ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F12R2_FB6                       ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F12R2_FB7                       ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F12R2_FB8                       ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F12R2_FB9                       ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F12R2_FB10                      ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F12R2_FB11                      ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F12R2_FB12                      ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F12R2_FB13                      ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F12R2_FB14                      ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F12R2_FB15                      ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F12R2_FB16                      ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F12R2_FB17                      ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F12R2_FB18                      ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F12R2_FB19                      ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F12R2_FB20                      ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F12R2_FB21                      ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F12R2_FB22                      ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F12R2_FB23                      ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F12R2_FB24                      ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F12R2_FB25                      ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F12R2_FB26                      ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F12R2_FB27                      ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F12R2_FB28                      ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F12R2_FB29                      ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F12R2_FB30                      ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F12R2_FB31                      ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F13R2 register  ******************/
#define  CAN_F13R2_FB0                       ((uint32_t)0x00000001)        /*!<Filter bit 0 */
#define  CAN_F13R2_FB1                       ((uint32_t)0x00000002)        /*!<Filter bit 1 */
#define  CAN_F13R2_FB2                       ((uint32_t)0x00000004)        /*!<Filter bit 2 */
#define  CAN_F13R2_FB3                       ((uint32_t)0x00000008)        /*!<Filter bit 3 */
#define  CAN_F13R2_FB4                       ((uint32_t)0x00000010)        /*!<Filter bit 4 */
#define  CAN_F13R2_FB5                       ((uint32_t)0x00000020)        /*!<Filter bit 5 */
#define  CAN_F13R2_FB6                       ((uint32_t)0x00000040)        /*!<Filter bit 6 */
#define  CAN_F13R2_FB7                       ((uint32_t)0x00000080)        /*!<Filter bit 7 */
#define  CAN_F13R2_FB8                       ((uint32_t)0x00000100)        /*!<Filter bit 8 */
#define  CAN_F13R2_FB9                       ((uint32_t)0x00000200)        /*!<Filter bit 9 */
#define  CAN_F13R2_FB10                      ((uint32_t)0x00000400)        /*!<Filter bit 10 */
#define  CAN_F13R2_FB11                      ((uint32_t)0x00000800)        /*!<Filter bit 11 */
#define  CAN_F13R2_FB12                      ((uint32_t)0x00001000)        /*!<Filter bit 12 */
#define  CAN_F13R2_FB13                      ((uint32_t)0x00002000)        /*!<Filter bit 13 */
#define  CAN_F13R2_FB14                      ((uint32_t)0x00004000)        /*!<Filter bit 14 */
#define  CAN_F13R2_FB15                      ((uint32_t)0x00008000)        /*!<Filter bit 15 */
#define  CAN_F13R2_FB16                      ((uint32_t)0x00010000)        /*!<Filter bit 16 */
#define  CAN_F13R2_FB17                      ((uint32_t)0x00020000)        /*!<Filter bit 17 */
#define  CAN_F13R2_FB18                      ((uint32_t)0x00040000)        /*!<Filter bit 18 */
#define  CAN_F13R2_FB19                      ((uint32_t)0x00080000)        /*!<Filter bit 19 */
#define  CAN_F13R2_FB20                      ((uint32_t)0x00100000)        /*!<Filter bit 20 */
#define  CAN_F13R2_FB21                      ((uint32_t)0x00200000)        /*!<Filter bit 21 */
#define  CAN_F13R2_FB22                      ((uint32_t)0x00400000)        /*!<Filter bit 22 */
#define  CAN_F13R2_FB23                      ((uint32_t)0x00800000)        /*!<Filter bit 23 */
#define  CAN_F13R2_FB24                      ((uint32_t)0x01000000)        /*!<Filter bit 24 */
#define  CAN_F13R2_FB25                      ((uint32_t)0x02000000)        /*!<Filter bit 25 */
#define  CAN_F13R2_FB26                      ((uint32_t)0x04000000)        /*!<Filter bit 26 */
#define  CAN_F13R2_FB27                      ((uint32_t)0x08000000)        /*!<Filter bit 27 */
#define  CAN_F13R2_FB28                      ((uint32_t)0x10000000)        /*!<Filter bit 28 */
#define  CAN_F13R2_FB29                      ((uint32_t)0x20000000)        /*!<Filter bit 29 */
#define  CAN_F13R2_FB30                      ((uint32_t)0x40000000)        /*!<Filter bit 30 */
#define  CAN_F13R2_FB31                      ((uint32_t)0x80000000)        /*!<Filter bit 31 */

/******************************************************************************/
/*                                                                            */
/*                     CRC calculation unit (CRC)                             */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CRC_DR register  *********************/
#define  CRC_DR_DR                           ((uint32_t)0xFFFFFFFF) /*!< Data register bits */

/*******************  Bit definition for CRC_IDR register  ********************/
#define  CRC_IDR_IDR                         ((uint8_t)0xFF)        /*!< General-purpose 8-bit data register bits */

/********************  Bit definition for CRC_CR register  ********************/
#define  CRC_CR_RESET                        ((uint32_t)0x00000001) /*!< RESET the CRC computation unit bit */
#define  CRC_CR_POLSIZE                      ((uint32_t)0x00000018) /*!< Polynomial size bits */
#define  CRC_CR_POLSIZE_0                    ((uint32_t)0x00000008) /*!< Polynomial size bit 0 */
#define  CRC_CR_POLSIZE_1                    ((uint32_t)0x00000010) /*!< Polynomial size bit 1 */
#define  CRC_CR_REV_IN                       ((uint32_t)0x00000060) /*!< REV_IN Reverse Input Data bits */
#define  CRC_CR_REV_IN_0                     ((uint32_t)0x00000020) /*!< Bit 0 */
#define  CRC_CR_REV_IN_1                     ((uint32_t)0x00000040) /*!< Bit 1 */
#define  CRC_CR_REV_OUT                      ((uint32_t)0x00000080) /*!< REV_OUT Reverse Output Data bits */

/*******************  Bit definition for CRC_INIT register  *******************/
#define  CRC_INIT_INIT                       ((uint32_t)0xFFFFFFFF) /*!< Initial CRC value bits */

/*******************  Bit definition for CRC_POL register  ********************/
#define  CRC_POL_POL                         ((uint32_t)0xFFFFFFFF) /*!< Coefficients of the polynomial */
/******************************************************************************/
/*                                                                            */
/*                 Digital to Analog Converter (DAC)                          */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for DAC_CR register  ********************/
#define  DAC_CR_EN1                          ((uint32_t)0x00000001)        /*!< DAC channel1 enable */
#define  DAC_CR_BOFF1                        ((uint32_t)0x00000002)        /*!< DAC channel1 output buffer disable */
#define  DAC_CR_TEN1                         ((uint32_t)0x00000004)        /*!< DAC channel1 Trigger enable */

#define  DAC_CR_TSEL1                        ((uint32_t)0x00000038)        /*!< TSEL1[2:0] (DAC channel1 Trigger selection) */
#define  DAC_CR_TSEL1_0                      ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  DAC_CR_TSEL1_1                      ((uint32_t)0x00000010)        /*!< Bit 1 */
#define  DAC_CR_TSEL1_2                      ((uint32_t)0x00000020)        /*!< Bit 2 */

#define  DAC_CR_WAVE1                        ((uint32_t)0x000000C0)        /*!< WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable) */
#define  DAC_CR_WAVE1_0                      ((uint32_t)0x00000040)        /*!< Bit 0 */
#define  DAC_CR_WAVE1_1                      ((uint32_t)0x00000080)        /*!< Bit 1 */

#define  DAC_CR_MAMP1                        ((uint32_t)0x00000F00)        /*!< MAMP1[3:0] (DAC channel1 Mask/Amplitude selector) */
#define  DAC_CR_MAMP1_0                      ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  DAC_CR_MAMP1_1                      ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  DAC_CR_MAMP1_2                      ((uint32_t)0x00000400)        /*!< Bit 2 */
#define  DAC_CR_MAMP1_3                      ((uint32_t)0x00000800)        /*!< Bit 3 */

#define  DAC_CR_DMAEN1                       ((uint32_t)0x00001000)        /*!< DAC channel1 DMA enable */
#define  DAC_CR_EN2                          ((uint32_t)0x00010000)        /*!< DAC channel2 enable */
#define  DAC_CR_BOFF2                        ((uint32_t)0x00020000)        /*!< DAC channel2 output buffer disable */
#define  DAC_CR_TEN2                         ((uint32_t)0x00040000)        /*!< DAC channel2 Trigger enable */

#define  DAC_CR_TSEL2                        ((uint32_t)0x00380000)        /*!< TSEL2[2:0] (DAC channel2 Trigger selection) */
#define  DAC_CR_TSEL2_0                      ((uint32_t)0x00080000)        /*!< Bit 0 */
#define  DAC_CR_TSEL2_1                      ((uint32_t)0x00100000)        /*!< Bit 1 */
#define  DAC_CR_TSEL2_2                      ((uint32_t)0x00200000)        /*!< Bit 2 */

#define  DAC_CR_WAVE2                        ((uint32_t)0x00C00000)        /*!< WAVE2[1:0] (DAC channel2 noise/triangle wave generation enable) */
#define  DAC_CR_WAVE2_0                      ((uint32_t)0x00400000)        /*!< Bit 0 */
#define  DAC_CR_WAVE2_1                      ((uint32_t)0x00800000)        /*!< Bit 1 */

#define  DAC_CR_MAMP2                        ((uint32_t)0x0F000000)        /*!< MAMP2[3:0] (DAC channel2 Mask/Amplitude selector) */
#define  DAC_CR_MAMP2_0                      ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  DAC_CR_MAMP2_1                      ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  DAC_CR_MAMP2_2                      ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  DAC_CR_MAMP2_3                      ((uint32_t)0x08000000)        /*!< Bit 3 */

#define  DAC_CR_DMAEN2                       ((uint32_t)0x10000000)        /*!< DAC channel2 DMA enabled */

/*****************  Bit definition for DAC_SWTRIGR register  ******************/
#define  DAC_SWTRIGR_SWTRIG1                 ((uint8_t)0x01)               /*!< DAC channel1 software trigger */
#define  DAC_SWTRIGR_SWTRIG2                 ((uint8_t)0x02)               /*!< DAC channel2 software trigger */

/*****************  Bit definition for DAC_DHR12R1 register  ******************/
#define  DAC_DHR12R1_DACC1DHR                ((uint16_t)0x0FFF)            /*!< DAC channel1 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L1 register  ******************/
#define  DAC_DHR12L1_DACC1DHR                ((uint16_t)0xFFF0)            /*!< DAC channel1 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R1 register  ******************/
#define  DAC_DHR8R1_DACC1DHR                 ((uint8_t)0xFF)               /*!< DAC channel1 8-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12R2 register  ******************/
#define  DAC_DHR12R2_DACC2DHR                ((uint16_t)0x0FFF)            /*!< DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L2 register  ******************/
#define  DAC_DHR12L2_DACC2DHR                ((uint16_t)0xFFF0)            /*!< DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R2 register  ******************/
#define  DAC_DHR8R2_DACC2DHR                 ((uint8_t)0xFF)               /*!< DAC channel2 8-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12RD register  ******************/
#define  DAC_DHR12RD_DACC1DHR                ((uint32_t)0x00000FFF)        /*!< DAC channel1 12-bit Right aligned data */
#define  DAC_DHR12RD_DACC2DHR                ((uint32_t)0x0FFF0000)        /*!< DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12LD register  ******************/
#define  DAC_DHR12LD_DACC1DHR                ((uint32_t)0x0000FFF0)        /*!< DAC channel1 12-bit Left aligned data */
#define  DAC_DHR12LD_DACC2DHR                ((uint32_t)0xFFF00000)        /*!< DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8RD register  ******************/
#define  DAC_DHR8RD_DACC1DHR                 ((uint16_t)0x00FF)            /*!< DAC channel1 8-bit Right aligned data */
#define  DAC_DHR8RD_DACC2DHR                 ((uint16_t)0xFF00)            /*!< DAC channel2 8-bit Right aligned data */

/*******************  Bit definition for DAC_DOR1 register  *******************/
#define  DAC_DOR1_DACC1DOR                   ((uint16_t)0x0FFF)            /*!< DAC channel1 data output */

/*******************  Bit definition for DAC_DOR2 register  *******************/
#define  DAC_DOR2_DACC2DOR                   ((uint16_t)0x0FFF)            /*!< DAC channel2 data output */

/********************  Bit definition for DAC_SR register  ********************/
#define  DAC_SR_DMAUDR1                      ((uint32_t)0x00002000)        /*!< DAC channel1 DMA underrun flag */
#define  DAC_SR_DMAUDR2                      ((uint32_t)0x20000000)        /*!< DAC channel2 DMA underrun flag */

/******************************************************************************/
/*                                                                            */
/*                                 Debug MCU (DBGMCU)                         */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for DBGMCU_IDCODE register  *************/
#define  DBGMCU_IDCODE_DEV_ID                ((uint32_t)0x00000FFF)
#define  DBGMCU_IDCODE_REV_ID                ((uint32_t)0xFFFF0000)

/********************  Bit definition for DBGMCU_CR register  *****************/
#define  DBGMCU_CR_DBG_SLEEP                 ((uint32_t)0x00000001)
#define  DBGMCU_CR_DBG_STOP                  ((uint32_t)0x00000002)
#define  DBGMCU_CR_DBG_STANDBY               ((uint32_t)0x00000004)
#define  DBGMCU_CR_TRACE_IOEN                ((uint32_t)0x00000020)

#define  DBGMCU_CR_TRACE_MODE                ((uint32_t)0x000000C0)
#define  DBGMCU_CR_TRACE_MODE_0              ((uint32_t)0x00000040)/*!<Bit 0 */
#define  DBGMCU_CR_TRACE_MODE_1              ((uint32_t)0x00000080)/*!<Bit 1 */

/********************  Bit definition for DBGMCU_APB1_FZ register  ************/
#define  DBGMCU_APB1_FZ_DBG_TIM2_STOP        ((uint32_t)0x00000001)
#define  DBGMCU_APB1_FZ_DBG_TIM3_STOP        ((uint32_t)0x00000002)
#define  DBGMCU_APB1_FZ_DBG_TIM4_STOP        ((uint32_t)0x00000004)
#define  DBGMCU_APB1_FZ_DBG_TIM6_STOP        ((uint32_t)0x00000010)
#define  DBGMCU_APB1_FZ_DBG_TIM7_STOP        ((uint32_t)0x00000020)
#define  DBGMCU_APB1_FZ_DBG_RTC_STOP         ((uint32_t)0x00000400)
#define  DBGMCU_APB1_FZ_DBG_WWDG_STOP        ((uint32_t)0x00000800)
#define  DBGMCU_APB1_FZ_DBG_IWDG_STOP        ((uint32_t)0x00001000)
#define  DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT   ((uint32_t)0x00200000)
#define  DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT   ((uint32_t)0x00400000)
#define  DBGMCU_APB1_FZ_DBG_CAN1_STOP            ((uint32_t)0x02000000)

/********************  Bit definition for DBGMCU_APB2_FZ register  ************/
#define  DBGMCU_APB2_FZ_DBG_TIM1_STOP        ((uint32_t)0x00000001)
#define  DBGMCU_APB2_FZ_DBG_TIM8_STOP        ((uint32_t)0x00000002)
#define  DBGMCU_APB2_FZ_DBG_TIM15_STOP       ((uint32_t)0x00000004)
#define  DBGMCU_APB2_FZ_DBG_TIM16_STOP       ((uint32_t)0x00000008)
#define  DBGMCU_APB2_FZ_DBG_TIM17_STOP       ((uint32_t)0x00000010)

/******************************************************************************/
/*                                                                            */
/*                             DMA Controller (DMA)                           */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for DMA_ISR register  ********************/
#define  DMA_ISR_GIF1                        ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt flag */
#define  DMA_ISR_TCIF1                       ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete flag */
#define  DMA_ISR_HTIF1                       ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer flag */
#define  DMA_ISR_TEIF1                       ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error flag */
#define  DMA_ISR_GIF2                        ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt flag */
#define  DMA_ISR_TCIF2                       ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete flag */
#define  DMA_ISR_HTIF2                       ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer flag */
#define  DMA_ISR_TEIF2                       ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error flag */
#define  DMA_ISR_GIF3                        ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt flag */
#define  DMA_ISR_TCIF3                       ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete flag */
#define  DMA_ISR_HTIF3                       ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer flag */
#define  DMA_ISR_TEIF3                       ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error flag */
#define  DMA_ISR_GIF4                        ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt flag */
#define  DMA_ISR_TCIF4                       ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete flag */
#define  DMA_ISR_HTIF4                       ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer flag */
#define  DMA_ISR_TEIF4                       ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error flag */
#define  DMA_ISR_GIF5                        ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt flag */
#define  DMA_ISR_TCIF5                       ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete flag */
#define  DMA_ISR_HTIF5                       ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer flag */
#define  DMA_ISR_TEIF5                       ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error flag */
#define  DMA_ISR_GIF6                        ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt flag */
#define  DMA_ISR_TCIF6                       ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete flag */
#define  DMA_ISR_HTIF6                       ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer flag */
#define  DMA_ISR_TEIF6                       ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error flag */
#define  DMA_ISR_GIF7                        ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt flag */
#define  DMA_ISR_TCIF7                       ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete flag */
#define  DMA_ISR_HTIF7                       ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer flag */
#define  DMA_ISR_TEIF7                       ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error flag */

/*******************  Bit definition for DMA_IFCR register  *******************/
#define  DMA_IFCR_CGIF1                      ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt clear */
#define  DMA_IFCR_CTCIF1                     ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete clear */
#define  DMA_IFCR_CHTIF1                     ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer clear */
#define  DMA_IFCR_CTEIF1                     ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error clear */
#define  DMA_IFCR_CGIF2                      ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt clear */
#define  DMA_IFCR_CTCIF2                     ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete clear */
#define  DMA_IFCR_CHTIF2                     ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer clear */
#define  DMA_IFCR_CTEIF2                     ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error clear */
#define  DMA_IFCR_CGIF3                      ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt clear */
#define  DMA_IFCR_CTCIF3                     ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete clear */
#define  DMA_IFCR_CHTIF3                     ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer clear */
#define  DMA_IFCR_CTEIF3                     ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error clear */
#define  DMA_IFCR_CGIF4                      ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt clear */
#define  DMA_IFCR_CTCIF4                     ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete clear */
#define  DMA_IFCR_CHTIF4                     ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer clear */
#define  DMA_IFCR_CTEIF4                     ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error clear */
#define  DMA_IFCR_CGIF5                      ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt clear */
#define  DMA_IFCR_CTCIF5                     ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete clear */
#define  DMA_IFCR_CHTIF5                     ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer clear */
#define  DMA_IFCR_CTEIF5                     ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error clear */
#define  DMA_IFCR_CGIF6                      ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt clear */
#define  DMA_IFCR_CTCIF6                     ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete clear */
#define  DMA_IFCR_CHTIF6                     ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer clear */
#define  DMA_IFCR_CTEIF6                     ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error clear */
#define  DMA_IFCR_CGIF7                      ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt clear */
#define  DMA_IFCR_CTCIF7                     ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete clear */
#define  DMA_IFCR_CHTIF7                     ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer clear */
#define  DMA_IFCR_CTEIF7                     ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error clear */

/*******************  Bit definition for DMA_CCR register  ********************/
#define  DMA_CCR_EN                          ((uint32_t)0x00000001)        /*!< Channel enable                      */
#define  DMA_CCR_TCIE                        ((uint32_t)0x00000002)        /*!< Transfer complete interrupt enable  */
#define  DMA_CCR_HTIE                        ((uint32_t)0x00000004)        /*!< Half Transfer interrupt enable      */
#define  DMA_CCR_TEIE                        ((uint32_t)0x00000008)        /*!< Transfer error interrupt enable     */
#define  DMA_CCR_DIR                         ((uint32_t)0x00000010)        /*!< Data transfer direction             */
#define  DMA_CCR_CIRC                        ((uint32_t)0x00000020)        /*!< Circular mode                       */
#define  DMA_CCR_PINC                        ((uint32_t)0x00000040)        /*!< Peripheral increment mode           */
#define  DMA_CCR_MINC                        ((uint32_t)0x00000080)        /*!< Memory increment mode               */

#define  DMA_CCR_PSIZE                       ((uint32_t)0x00000300)        /*!< PSIZE[1:0] bits (Peripheral size)   */
#define  DMA_CCR_PSIZE_0                     ((uint32_t)0x00000100)        /*!< Bit 0                               */
#define  DMA_CCR_PSIZE_1                     ((uint32_t)0x00000200)        /*!< Bit 1                               */

#define  DMA_CCR_MSIZE                       ((uint32_t)0x00000C00)        /*!< MSIZE[1:0] bits (Memory size)       */
#define  DMA_CCR_MSIZE_0                     ((uint32_t)0x00000400)        /*!< Bit 0                               */
#define  DMA_CCR_MSIZE_1                     ((uint32_t)0x00000800)        /*!< Bit 1                               */

#define  DMA_CCR_PL                          ((uint32_t)0x00003000)        /*!< PL[1:0] bits(Channel Priority level)*/
#define  DMA_CCR_PL_0                        ((uint32_t)0x00001000)        /*!< Bit 0                               */
#define  DMA_CCR_PL_1                        ((uint32_t)0x00002000)        /*!< Bit 1                               */

#define  DMA_CCR_MEM2MEM                     ((uint32_t)0x00004000)        /*!< Memory to memory mode               */

/******************  Bit definition for DMA_CNDTR register  *******************/
#define  DMA_CNDTR_NDT                       ((uint32_t)0x0000FFFF)        /*!< Number of data to Transfer          */

/******************  Bit definition for DMA_CPAR register  ********************/
#define  DMA_CPAR_PA                         ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address                  */

/******************  Bit definition for DMA_CMAR register  ********************/
#define  DMA_CMAR_MA                         ((uint32_t)0xFFFFFFFF)        /*!< Memory Address                      */

/******************************************************************************/
/*                                                                            */
/*                    External Interrupt/Event Controller (EXTI)              */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for EXTI_IMR register  *******************/
#define  EXTI_IMR_MR0                        ((uint32_t)0x00000001)        /*!< Interrupt Mask on line 0 */
#define  EXTI_IMR_MR1                        ((uint32_t)0x00000002)        /*!< Interrupt Mask on line 1 */
#define  EXTI_IMR_MR2                        ((uint32_t)0x00000004)        /*!< Interrupt Mask on line 2 */
#define  EXTI_IMR_MR3                        ((uint32_t)0x00000008)        /*!< Interrupt Mask on line 3 */
#define  EXTI_IMR_MR4                        ((uint32_t)0x00000010)        /*!< Interrupt Mask on line 4 */
#define  EXTI_IMR_MR5                        ((uint32_t)0x00000020)        /*!< Interrupt Mask on line 5 */
#define  EXTI_IMR_MR6                        ((uint32_t)0x00000040)        /*!< Interrupt Mask on line 6 */
#define  EXTI_IMR_MR7                        ((uint32_t)0x00000080)        /*!< Interrupt Mask on line 7 */
#define  EXTI_IMR_MR8                        ((uint32_t)0x00000100)        /*!< Interrupt Mask on line 8 */
#define  EXTI_IMR_MR9                        ((uint32_t)0x00000200)        /*!< Interrupt Mask on line 9 */
#define  EXTI_IMR_MR10                       ((uint32_t)0x00000400)        /*!< Interrupt Mask on line 10 */
#define  EXTI_IMR_MR11                       ((uint32_t)0x00000800)        /*!< Interrupt Mask on line 11 */
#define  EXTI_IMR_MR12                       ((uint32_t)0x00001000)        /*!< Interrupt Mask on line 12 */
#define  EXTI_IMR_MR13                       ((uint32_t)0x00002000)        /*!< Interrupt Mask on line 13 */
#define  EXTI_IMR_MR14                       ((uint32_t)0x00004000)        /*!< Interrupt Mask on line 14 */
#define  EXTI_IMR_MR15                       ((uint32_t)0x00008000)        /*!< Interrupt Mask on line 15 */
#define  EXTI_IMR_MR16                       ((uint32_t)0x00010000)        /*!< Interrupt Mask on line 16 */
#define  EXTI_IMR_MR17                       ((uint32_t)0x00020000)        /*!< Interrupt Mask on line 17 */
#define  EXTI_IMR_MR18                       ((uint32_t)0x00040000)        /*!< Interrupt Mask on line 18 */
#define  EXTI_IMR_MR19                       ((uint32_t)0x00080000)        /*!< Interrupt Mask on line 19 */
#define  EXTI_IMR_MR20                       ((uint32_t)0x00100000)        /*!< Interrupt Mask on line 20 */
#define  EXTI_IMR_MR21                       ((uint32_t)0x00200000)        /*!< Interrupt Mask on line 21 */
#define  EXTI_IMR_MR22                       ((uint32_t)0x00400000)        /*!< Interrupt Mask on line 22 */
#define  EXTI_IMR_MR23                       ((uint32_t)0x00800000)        /*!< Interrupt Mask on line 23 */
#define  EXTI_IMR_MR24                       ((uint32_t)0x01000000)        /*!< Interrupt Mask on line 24 */
#define  EXTI_IMR_MR25                       ((uint32_t)0x02000000)        /*!< Interrupt Mask on line 25 */
#define  EXTI_IMR_MR26                       ((uint32_t)0x04000000)        /*!< Interrupt Mask on line 26 */
#define  EXTI_IMR_MR27                       ((uint32_t)0x08000000)        /*!< Interrupt Mask on line 27 */
#define  EXTI_IMR_MR28                       ((uint32_t)0x10000000)        /*!< Interrupt Mask on line 28 */

/*******************  Bit definition for EXTI_EMR register  *******************/
#define  EXTI_EMR_MR0                        ((uint32_t)0x00000001)        /*!< Event Mask on line 0 */
#define  EXTI_EMR_MR1                        ((uint32_t)0x00000002)        /*!< Event Mask on line 1 */
#define  EXTI_EMR_MR2                        ((uint32_t)0x00000004)        /*!< Event Mask on line 2 */
#define  EXTI_EMR_MR3                        ((uint32_t)0x00000008)        /*!< Event Mask on line 3 */
#define  EXTI_EMR_MR4                        ((uint32_t)0x00000010)        /*!< Event Mask on line 4 */
#define  EXTI_EMR_MR5                        ((uint32_t)0x00000020)        /*!< Event Mask on line 5 */
#define  EXTI_EMR_MR6                        ((uint32_t)0x00000040)        /*!< Event Mask on line 6 */
#define  EXTI_EMR_MR7                        ((uint32_t)0x00000080)        /*!< Event Mask on line 7 */
#define  EXTI_EMR_MR8                        ((uint32_t)0x00000100)        /*!< Event Mask on line 8 */
#define  EXTI_EMR_MR9                        ((uint32_t)0x00000200)        /*!< Event Mask on line 9 */
#define  EXTI_EMR_MR10                       ((uint32_t)0x00000400)        /*!< Event Mask on line 10 */
#define  EXTI_EMR_MR11                       ((uint32_t)0x00000800)        /*!< Event Mask on line 11 */
#define  EXTI_EMR_MR12                       ((uint32_t)0x00001000)        /*!< Event Mask on line 12 */
#define  EXTI_EMR_MR13                       ((uint32_t)0x00002000)        /*!< Event Mask on line 13 */
#define  EXTI_EMR_MR14                       ((uint32_t)0x00004000)        /*!< Event Mask on line 14 */
#define  EXTI_EMR_MR15                       ((uint32_t)0x00008000)        /*!< Event Mask on line 15 */
#define  EXTI_EMR_MR16                       ((uint32_t)0x00010000)        /*!< Event Mask on line 16 */
#define  EXTI_EMR_MR17                       ((uint32_t)0x00020000)        /*!< Event Mask on line 17 */
#define  EXTI_EMR_MR18                       ((uint32_t)0x00040000)        /*!< Event Mask on line 18 */
#define  EXTI_EMR_MR19                       ((uint32_t)0x00080000)        /*!< Event Mask on line 19 */
#define  EXTI_EMR_MR20                       ((uint32_t)0x00100000)        /*!< Event Mask on line 20 */
#define  EXTI_EMR_MR21                       ((uint32_t)0x00200000)        /*!< Event Mask on line 21 */
#define  EXTI_EMR_MR22                       ((uint32_t)0x00400000)        /*!< Event Mask on line 22 */
#define  EXTI_EMR_MR23                       ((uint32_t)0x00800000)        /*!< Event Mask on line 23 */
#define  EXTI_EMR_MR24                       ((uint32_t)0x01000000)        /*!< Event Mask on line 24 */
#define  EXTI_EMR_MR25                       ((uint32_t)0x02000000)        /*!< Event Mask on line 25 */
#define  EXTI_EMR_MR26                       ((uint32_t)0x04000000)        /*!< Event Mask on line 26 */
#define  EXTI_EMR_MR27                       ((uint32_t)0x08000000)        /*!< Event Mask on line 27 */
#define  EXTI_EMR_MR28                       ((uint32_t)0x10000000)        /*!< Event Mask on line 28 */

/******************  Bit definition for EXTI_RTSR register  *******************/
#define  EXTI_RTSR_TR0                       ((uint32_t)0x00000001)        /*!< Rising trigger event configuration bit of line 0 */
#define  EXTI_RTSR_TR1                       ((uint32_t)0x00000002)        /*!< Rising trigger event configuration bit of line 1 */
#define  EXTI_RTSR_TR2                       ((uint32_t)0x00000004)        /*!< Rising trigger event configuration bit of line 2 */
#define  EXTI_RTSR_TR3                       ((uint32_t)0x00000008)        /*!< Rising trigger event configuration bit of line 3 */
#define  EXTI_RTSR_TR4                       ((uint32_t)0x00000010)        /*!< Rising trigger event configuration bit of line 4 */
#define  EXTI_RTSR_TR5                       ((uint32_t)0x00000020)        /*!< Rising trigger event configuration bit of line 5 */
#define  EXTI_RTSR_TR6                       ((uint32_t)0x00000040)        /*!< Rising trigger event configuration bit of line 6 */
#define  EXTI_RTSR_TR7                       ((uint32_t)0x00000080)        /*!< Rising trigger event configuration bit of line 7 */
#define  EXTI_RTSR_TR8                       ((uint32_t)0x00000100)        /*!< Rising trigger event configuration bit of line 8 */
#define  EXTI_RTSR_TR9                       ((uint32_t)0x00000200)        /*!< Rising trigger event configuration bit of line 9 */
#define  EXTI_RTSR_TR10                      ((uint32_t)0x00000400)        /*!< Rising trigger event configuration bit of line 10 */
#define  EXTI_RTSR_TR11                      ((uint32_t)0x00000800)        /*!< Rising trigger event configuration bit of line 11 */
#define  EXTI_RTSR_TR12                      ((uint32_t)0x00001000)        /*!< Rising trigger event configuration bit of line 12 */
#define  EXTI_RTSR_TR13                      ((uint32_t)0x00002000)        /*!< Rising trigger event configuration bit of line 13 */
#define  EXTI_RTSR_TR14                      ((uint32_t)0x00004000)        /*!< Rising trigger event configuration bit of line 14 */
#define  EXTI_RTSR_TR15                      ((uint32_t)0x00008000)        /*!< Rising trigger event configuration bit of line 15 */
#define  EXTI_RTSR_TR16                      ((uint32_t)0x00010000)        /*!< Rising trigger event configuration bit of line 16 */
#define  EXTI_RTSR_TR17                      ((uint32_t)0x00020000)        /*!< Rising trigger event configuration bit of line 17 */
#define  EXTI_RTSR_TR18                      ((uint32_t)0x00040000)        /*!< Rising trigger event configuration bit of line 18 */
#define  EXTI_RTSR_TR19                      ((uint32_t)0x00080000)        /*!< Rising trigger event configuration bit of line 19 */
#define  EXTI_RTSR_TR20                      ((uint32_t)0x00100000)        /*!< Rising trigger event configuration bit of line 20 */
#define  EXTI_RTSR_TR21                      ((uint32_t)0x00200000)        /*!< Rising trigger event configuration bit of line 21 */
#define  EXTI_RTSR_TR22                      ((uint32_t)0x00400000)        /*!< Rising trigger event configuration bit of line 22 */
#define  EXTI_RTSR_TR23                      ((uint32_t)0x00800000)        /*!< Rising trigger event configuration bit of line 23 */
#define  EXTI_RTSR_TR24                      ((uint32_t)0x01000000)        /*!< Rising trigger event configuration bit of line 24 */
#define  EXTI_RTSR_TR25                      ((uint32_t)0x02000000)        /*!< Rising trigger event configuration bit of line 25 */
#define  EXTI_RTSR_TR26                      ((uint32_t)0x04000000)        /*!< Rising trigger event configuration bit of line 26 */
#define  EXTI_RTSR_TR27                      ((uint32_t)0x08000000)        /*!< Rising trigger event configuration bit of line 27 */
#define  EXTI_RTSR_TR28                      ((uint32_t)0x10000000)        /*!< Rising trigger event configuration bit of line 28 */

/******************  Bit definition for EXTI_FTSR register  *******************/
#define  EXTI_FTSR_TR0                       ((uint32_t)0x00000001)        /*!< Falling trigger event configuration bit of line 0 */
#define  EXTI_FTSR_TR1                       ((uint32_t)0x00000002)        /*!< Falling trigger event configuration bit of line 1 */
#define  EXTI_FTSR_TR2                       ((uint32_t)0x00000004)        /*!< Falling trigger event configuration bit of line 2 */
#define  EXTI_FTSR_TR3                       ((uint32_t)0x00000008)        /*!< Falling trigger event configuration bit of line 3 */
#define  EXTI_FTSR_TR4                       ((uint32_t)0x00000010)        /*!< Falling trigger event configuration bit of line 4 */
#define  EXTI_FTSR_TR5                       ((uint32_t)0x00000020)        /*!< Falling trigger event configuration bit of line 5 */
#define  EXTI_FTSR_TR6                       ((uint32_t)0x00000040)        /*!< Falling trigger event configuration bit of line 6 */
#define  EXTI_FTSR_TR7                       ((uint32_t)0x00000080)        /*!< Falling trigger event configuration bit of line 7 */
#define  EXTI_FTSR_TR8                       ((uint32_t)0x00000100)        /*!< Falling trigger event configuration bit of line 8 */
#define  EXTI_FTSR_TR9                       ((uint32_t)0x00000200)        /*!< Falling trigger event configuration bit of line 9 */
#define  EXTI_FTSR_TR10                      ((uint32_t)0x00000400)        /*!< Falling trigger event configuration bit of line 10 */
#define  EXTI_FTSR_TR11                      ((uint32_t)0x00000800)        /*!< Falling trigger event configuration bit of line 11 */
#define  EXTI_FTSR_TR12                      ((uint32_t)0x00001000)        /*!< Falling trigger event configuration bit of line 12 */
#define  EXTI_FTSR_TR13                      ((uint32_t)0x00002000)        /*!< Falling trigger event configuration bit of line 13 */
#define  EXTI_FTSR_TR14                      ((uint32_t)0x00004000)        /*!< Falling trigger event configuration bit of line 14 */
#define  EXTI_FTSR_TR15                      ((uint32_t)0x00008000)        /*!< Falling trigger event configuration bit of line 15 */
#define  EXTI_FTSR_TR16                      ((uint32_t)0x00010000)        /*!< Falling trigger event configuration bit of line 16 */
#define  EXTI_FTSR_TR17                      ((uint32_t)0x00020000)        /*!< Falling trigger event configuration bit of line 17 */
#define  EXTI_FTSR_TR18                      ((uint32_t)0x00040000)        /*!< Falling trigger event configuration bit of line 18 */
#define  EXTI_FTSR_TR19                      ((uint32_t)0x00080000)        /*!< Falling trigger event configuration bit of line 19 */
#define  EXTI_FTSR_TR20                      ((uint32_t)0x00100000)        /*!< Falling trigger event configuration bit of line 20 */
#define  EXTI_FTSR_TR21                      ((uint32_t)0x00200000)        /*!< Falling trigger event configuration bit of line 21 */
#define  EXTI_FTSR_TR22                      ((uint32_t)0x00400000)        /*!< Falling trigger event configuration bit of line 22 */
#define  EXTI_FTSR_TR23                      ((uint32_t)0x00800000)        /*!< Falling trigger event configuration bit of line 23 */
#define  EXTI_FTSR_TR24                      ((uint32_t)0x01000000)        /*!< Falling trigger event configuration bit of line 24 */
#define  EXTI_FTSR_TR25                      ((uint32_t)0x02000000)        /*!< Falling trigger event configuration bit of line 25 */
#define  EXTI_FTSR_TR26                      ((uint32_t)0x04000000)        /*!< Falling trigger event configuration bit of line 26 */
#define  EXTI_FTSR_TR27                      ((uint32_t)0x08000000)        /*!< Falling trigger event configuration bit of line 27 */
#define  EXTI_FTSR_TR28                      ((uint32_t)0x10000000)        /*!< Falling trigger event configuration bit of line 28 */

/******************  Bit definition for EXTI_SWIER register  ******************/
#define  EXTI_SWIER_SWIER0                   ((uint32_t)0x00000001)        /*!< Software Interrupt on line 0 */
#define  EXTI_SWIER_SWIER1                   ((uint32_t)0x00000002)        /*!< Software Interrupt on line 1 */
#define  EXTI_SWIER_SWIER2                   ((uint32_t)0x00000004)        /*!< Software Interrupt on line 2 */
#define  EXTI_SWIER_SWIER3                   ((uint32_t)0x00000008)        /*!< Software Interrupt on line 3 */
#define  EXTI_SWIER_SWIER4                   ((uint32_t)0x00000010)        /*!< Software Interrupt on line 4 */
#define  EXTI_SWIER_SWIER5                   ((uint32_t)0x00000020)        /*!< Software Interrupt on line 5 */
#define  EXTI_SWIER_SWIER6                   ((uint32_t)0x00000040)        /*!< Software Interrupt on line 6 */
#define  EXTI_SWIER_SWIER7                   ((uint32_t)0x00000080)        /*!< Software Interrupt on line 7 */
#define  EXTI_SWIER_SWIER8                   ((uint32_t)0x00000100)        /*!< Software Interrupt on line 8 */
#define  EXTI_SWIER_SWIER9                   ((uint32_t)0x00000200)        /*!< Software Interrupt on line 9 */
#define  EXTI_SWIER_SWIER10                  ((uint32_t)0x00000400)        /*!< Software Interrupt on line 10 */
#define  EXTI_SWIER_SWIER11                  ((uint32_t)0x00000800)        /*!< Software Interrupt on line 11 */
#define  EXTI_SWIER_SWIER12                  ((uint32_t)0x00001000)        /*!< Software Interrupt on line 12 */
#define  EXTI_SWIER_SWIER13                  ((uint32_t)0x00002000)        /*!< Software Interrupt on line 13 */
#define  EXTI_SWIER_SWIER14                  ((uint32_t)0x00004000)        /*!< Software Interrupt on line 14 */
#define  EXTI_SWIER_SWIER15                  ((uint32_t)0x00008000)        /*!< Software Interrupt on line 15 */
#define  EXTI_SWIER_SWIER16                  ((uint32_t)0x00010000)        /*!< Software Interrupt on line 16 */
#define  EXTI_SWIER_SWIER17                  ((uint32_t)0x00020000)        /*!< Software Interrupt on line 17 */
#define  EXTI_SWIER_SWIER18                  ((uint32_t)0x00040000)        /*!< Software Interrupt on line 18 */
#define  EXTI_SWIER_SWIER19                  ((uint32_t)0x00080000)        /*!< Software Interrupt on line 19 */
#define  EXTI_SWIER_SWIER20                  ((uint32_t)0x00100000)        /*!< Software Interrupt on line 20 */
#define  EXTI_SWIER_SWIER21                  ((uint32_t)0x00200000)        /*!< Software Interrupt on line 21 */
#define  EXTI_SWIER_SWIER22                  ((uint32_t)0x00400000)        /*!< Software Interrupt on line 22 */
#define  EXTI_SWIER_SWIER23                  ((uint32_t)0x00800000)        /*!< Software Interrupt on line 23 */
#define  EXTI_SWIER_SWIER24                  ((uint32_t)0x01000000)        /*!< Software Interrupt on line 24 */
#define  EXTI_SWIER_SWIER25                  ((uint32_t)0x02000000)        /*!< Software Interrupt on line 25 */
#define  EXTI_SWIER_SWIER26                  ((uint32_t)0x04000000)        /*!< Software Interrupt on line 26 */
#define  EXTI_SWIER_SWIER27                  ((uint32_t)0x08000000)        /*!< Software Interrupt on line 27 */
#define  EXTI_SWIER_SWIER28                  ((uint32_t)0x10000000)        /*!< Software Interrupt on line 28 */

/*******************  Bit definition for EXTI_PR register  ********************/
#define  EXTI_PR_PR0                         ((uint32_t)0x00000001)        /*!< Pending bit for line 0 */
#define  EXTI_PR_PR1                         ((uint32_t)0x00000002)        /*!< Pending bit for line 1 */
#define  EXTI_PR_PR2                         ((uint32_t)0x00000004)        /*!< Pending bit for line 2 */
#define  EXTI_PR_PR3                         ((uint32_t)0x00000008)        /*!< Pending bit for line 3 */
#define  EXTI_PR_PR4                         ((uint32_t)0x00000010)        /*!< Pending bit for line 4 */
#define  EXTI_PR_PR5                         ((uint32_t)0x00000020)        /*!< Pending bit for line 5 */
#define  EXTI_PR_PR6                         ((uint32_t)0x00000040)        /*!< Pending bit for line 6 */
#define  EXTI_PR_PR7                         ((uint32_t)0x00000080)        /*!< Pending bit for line 7 */
#define  EXTI_PR_PR8                         ((uint32_t)0x00000100)        /*!< Pending bit for line 8 */
#define  EXTI_PR_PR9                         ((uint32_t)0x00000200)        /*!< Pending bit for line 9 */
#define  EXTI_PR_PR10                        ((uint32_t)0x00000400)        /*!< Pending bit for line 10 */
#define  EXTI_PR_PR11                        ((uint32_t)0x00000800)        /*!< Pending bit for line 11 */
#define  EXTI_PR_PR12                        ((uint32_t)0x00001000)        /*!< Pending bit for line 12 */
#define  EXTI_PR_PR13                        ((uint32_t)0x00002000)        /*!< Pending bit for line 13 */
#define  EXTI_PR_PR14                        ((uint32_t)0x00004000)        /*!< Pending bit for line 14 */
#define  EXTI_PR_PR15                        ((uint32_t)0x00008000)        /*!< Pending bit for line 15 */
#define  EXTI_PR_PR16                        ((uint32_t)0x00010000)        /*!< Pending bit for line 16 */
#define  EXTI_PR_PR17                        ((uint32_t)0x00020000)        /*!< Pending bit for line 17 */
#define  EXTI_PR_PR18                        ((uint32_t)0x00040000)        /*!< Pending bit for line 18 */
#define  EXTI_PR_PR19                        ((uint32_t)0x00080000)        /*!< Pending bit for line 19 */
#define  EXTI_PR_PR20                        ((uint32_t)0x00100000)        /*!< Pending bit for line 20 */
#define  EXTI_PR_PR21                        ((uint32_t)0x00200000)        /*!< Pending bit for line 21 */
#define  EXTI_PR_PR22                        ((uint32_t)0x00400000)        /*!< Pending bit for line 22 */
#define  EXTI_PR_PR23                        ((uint32_t)0x00800000)        /*!< Pending bit for line 23 */
#define  EXTI_PR_PR24                        ((uint32_t)0x01000000)        /*!< Pending bit for line 24 */
#define  EXTI_PR_PR25                        ((uint32_t)0x02000000)        /*!< Pending bit for line 25 */
#define  EXTI_PR_PR26                        ((uint32_t)0x04000000)        /*!< Pending bit for line 26 */
#define  EXTI_PR_PR27                        ((uint32_t)0x08000000)        /*!< Pending bit for line 27 */
#define  EXTI_PR_PR28                        ((uint32_t)0x10000000)        /*!< Pending bit for line 28 */

/******************************************************************************/
/*                                                                            */
/*                                    FLASH                                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for FLASH_ACR register  ******************/
#define  FLASH_ACR_LATENCY                   ((uint8_t)0x03)               /*!< LATENCY[2:0] bits (Latency) */
#define  FLASH_ACR_LATENCY_0                 ((uint8_t)0x01)               /*!< Bit 0 */
#define  FLASH_ACR_LATENCY_1                 ((uint8_t)0x02)               /*!< Bit 1 */

#define  FLASH_ACR_HLFCYA                    ((uint8_t)0x08)               /*!< Flash Half Cycle Access Enable */
#define  FLASH_ACR_PRFTBE                    ((uint8_t)0x10)               /*!< Prefetch Buffer Enable */
#define  FLASH_ACR_PRFTBS                    ((uint8_t)0x20)  

/******************  Bit definition for FLASH_KEYR register  ******************/
#define  FLASH_KEYR_FKEYR                    ((uint32_t)0xFFFFFFFF)        /*!< FPEC Key */

#define  RDP_KEY                             ((uint16_t)0x00A5)            /*!< RDP Key */
#define  FLASH_KEY1                          ((uint32_t)0x45670123)        /*!< FPEC Key1 */
#define  FLASH_KEY2                          ((uint32_t)0xCDEF89AB)        /*!< FPEC Key2 */

/*****************  Bit definition for FLASH_OPTKEYR register  ****************/
#define  FLASH_OPTKEYR_OPTKEYR               ((uint32_t)0xFFFFFFFF)        /*!< Option Byte Key */

#define  FLASH_OPTKEY1                       FLASH_KEY1                    /*!< Option Byte Key1 */
#define  FLASH_OPTKEY2                       FLASH_KEY2                    /*!< Option Byte Key2 */

/******************  Bit definition for FLASH_SR register  *******************/
#define  FLASH_SR_BSY                        ((uint32_t)0x00000001)        /*!< Busy */
#define  FLASH_SR_PGERR                      ((uint32_t)0x00000004)        /*!< Programming Error */
#define  FLASH_SR_WRPERR                     ((uint32_t)0x00000010)        /*!< Write Protection Error */
#define  FLASH_SR_EOP                        ((uint32_t)0x00000020)        /*!< End of operation */

/*******************  Bit definition for FLASH_CR register  *******************/
#define  FLASH_CR_PG                         ((uint32_t)0x00000001)        /*!< Programming */
#define  FLASH_CR_PER                        ((uint32_t)0x00000002)        /*!< Page Erase */
#define  FLASH_CR_MER                        ((uint32_t)0x00000004)        /*!< Mass Erase */
#define  FLASH_CR_OPTPG                      ((uint32_t)0x00000010)        /*!< Option Byte Programming */
#define  FLASH_CR_OPTER                      ((uint32_t)0x00000020)        /*!< Option Byte Erase */
#define  FLASH_CR_STRT                       ((uint32_t)0x00000040)        /*!< Start */
#define  FLASH_CR_LOCK                       ((uint32_t)0x00000080)        /*!< Lock */
#define  FLASH_CR_OPTWRE                     ((uint32_t)0x00000200)        /*!< Option Bytes Write Enable */
#define  FLASH_CR_ERRIE                      ((uint32_t)0x00000400)        /*!< Error Interrupt Enable */
#define  FLASH_CR_EOPIE                      ((uint32_t)0x00001000)        /*!< End of operation interrupt enable */
#define  FLASH_CR_OBL_LAUNCH                 ((uint32_t)0x00002000)        /*!< OptionBytes Loader Launch */

/*******************  Bit definition for FLASH_AR register  *******************/
#define  FLASH_AR_FAR                        ((uint32_t)0xFFFFFFFF)        /*!< Flash Address */

/******************  Bit definition for FLASH_OBR register  *******************/
#define  FLASH_OBR_OPTERR                    ((uint32_t)0x00000001)        /*!< Option Byte Error */
#define  FLASH_OBR_RDPRT1                    ((uint32_t)0x00000002)        /*!< Read protection Level 1 */
#define  FLASH_OBR_RDPRT2                    ((uint32_t)0x00000004)        /*!< Read protection Level 2 */

#define  FLASH_OBR_USER                      ((uint32_t)0x00003700)        /*!< User Option Bytes */
#define  FLASH_OBR_IWDG_SW                   ((uint32_t)0x00000100)        /*!< IWDG SW */
#define  FLASH_OBR_nRST_STOP                 ((uint32_t)0x00000200)        /*!< nRST_STOP */
#define  FLASH_OBR_nRST_STDBY                ((uint32_t)0x00000400)        /*!< nRST_STDBY */

/******************  Bit definition for FLASH_WRPR register  ******************/
#define  FLASH_WRPR_WRP                        ((uint32_t)0xFFFFFFFF)      /*!< Write Protect */

/*----------------------------------------------------------------------------*/

/******************  Bit definition for OB_RDP register  **********************/
#define  OB_RDP_RDP                          ((uint32_t)0x000000FF)        /*!< Read protection option byte */
#define  OB_RDP_nRDP                         ((uint32_t)0x0000FF00)        /*!< Read protection complemented option byte */

/******************  Bit definition for OB_USER register  *********************/
#define  OB_USER_USER                        ((uint32_t)0x00FF0000)        /*!< User option byte */
#define  OB_USER_nUSER                       ((uint32_t)0xFF000000)        /*!< User complemented option byte */

/******************  Bit definition for FLASH_WRP0 register  ******************/
#define  OB_WRP0_WRP0                        ((uint32_t)0x000000FF)        /*!< Flash memory write protection option bytes */
#define  OB_WRP0_nWRP0                       ((uint32_t)0x0000FF00)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP1 register  ******************/
#define  OB_WRP1_WRP1                        ((uint32_t)0x00FF0000)        /*!< Flash memory write protection option bytes */
#define  OB_WRP1_nWRP1                       ((uint32_t)0xFF000000)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP2 register  ******************/
#define  OB_WRP2_WRP2                        ((uint32_t)0x000000FF)        /*!< Flash memory write protection option bytes */
#define  OB_WRP2_nWRP2                       ((uint32_t)0x0000FF00)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP3 register  ******************/
#define  OB_WRP3_WRP3                        ((uint32_t)0x00FF0000)        /*!< Flash memory write protection option bytes */
#define  OB_WRP3_nWRP3                       ((uint32_t)0xFF000000)        /*!< Flash memory write protection complemented option bytes */
/******************************************************************************/
/*                                                                            */
/*                            General Purpose I/O (GPIO)                      */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for GPIO_MODER register  *****************/
#define GPIO_MODER_MODER0          ((uint32_t)0x00000003)
#define GPIO_MODER_MODER0_0        ((uint32_t)0x00000001)
#define GPIO_MODER_MODER0_1        ((uint32_t)0x00000002)
#define GPIO_MODER_MODER1          ((uint32_t)0x0000000C)
#define GPIO_MODER_MODER1_0        ((uint32_t)0x00000004)
#define GPIO_MODER_MODER1_1        ((uint32_t)0x00000008)
#define GPIO_MODER_MODER2          ((uint32_t)0x00000030)
#define GPIO_MODER_MODER2_0        ((uint32_t)0x00000010)
#define GPIO_MODER_MODER2_1        ((uint32_t)0x00000020)
#define GPIO_MODER_MODER3          ((uint32_t)0x000000C0)
#define GPIO_MODER_MODER3_0        ((uint32_t)0x00000040)
#define GPIO_MODER_MODER3_1        ((uint32_t)0x00000080)
#define GPIO_MODER_MODER4          ((uint32_t)0x00000300)
#define GPIO_MODER_MODER4_0        ((uint32_t)0x00000100)
#define GPIO_MODER_MODER4_1        ((uint32_t)0x00000200)
#define GPIO_MODER_MODER5          ((uint32_t)0x00000C00)
#define GPIO_MODER_MODER5_0        ((uint32_t)0x00000400)
#define GPIO_MODER_MODER5_1        ((uint32_t)0x00000800)
#define GPIO_MODER_MODER6          ((uint32_t)0x00003000)
#define GPIO_MODER_MODER6_0        ((uint32_t)0x00001000)
#define GPIO_MODER_MODER6_1        ((uint32_t)0x00002000)
#define GPIO_MODER_MODER7          ((uint32_t)0x0000C000)
#define GPIO_MODER_MODER7_0        ((uint32_t)0x00004000)
#define GPIO_MODER_MODER7_1        ((uint32_t)0x00008000)
#define GPIO_MODER_MODER8          ((uint32_t)0x00030000)
#define GPIO_MODER_MODER8_0        ((uint32_t)0x00010000)
#define GPIO_MODER_MODER8_1        ((uint32_t)0x00020000)
#define GPIO_MODER_MODER9          ((uint32_t)0x000C0000)
#define GPIO_MODER_MODER9_0        ((uint32_t)0x00040000)
#define GPIO_MODER_MODER9_1        ((uint32_t)0x00080000)
#define GPIO_MODER_MODER10         ((uint32_t)0x00300000)
#define GPIO_MODER_MODER10_0       ((uint32_t)0x00100000)
#define GPIO_MODER_MODER10_1       ((uint32_t)0x00200000)
#define GPIO_MODER_MODER11         ((uint32_t)0x00C00000)
#define GPIO_MODER_MODER11_0       ((uint32_t)0x00400000)
#define GPIO_MODER_MODER11_1       ((uint32_t)0x00800000)
#define GPIO_MODER_MODER12         ((uint32_t)0x03000000)
#define GPIO_MODER_MODER12_0       ((uint32_t)0x01000000)
#define GPIO_MODER_MODER12_1       ((uint32_t)0x02000000)
#define GPIO_MODER_MODER13         ((uint32_t)0x0C000000)
#define GPIO_MODER_MODER13_0       ((uint32_t)0x04000000)
#define GPIO_MODER_MODER13_1       ((uint32_t)0x08000000)
#define GPIO_MODER_MODER14         ((uint32_t)0x30000000)
#define GPIO_MODER_MODER14_0       ((uint32_t)0x10000000)
#define GPIO_MODER_MODER14_1       ((uint32_t)0x20000000)
#define GPIO_MODER_MODER15         ((uint32_t)0xC0000000)
#define GPIO_MODER_MODER15_0       ((uint32_t)0x40000000)
#define GPIO_MODER_MODER15_1       ((uint32_t)0x80000000)


/******************  Bit definition for GPIO_OTYPER register  *****************/
#define GPIO_OTYPER_OT_0           ((uint32_t)0x00000001)
#define GPIO_OTYPER_OT_1           ((uint32_t)0x00000002)
#define GPIO_OTYPER_OT_2           ((uint32_t)0x00000004)
#define GPIO_OTYPER_OT_3           ((uint32_t)0x00000008)
#define GPIO_OTYPER_OT_4           ((uint32_t)0x00000010)
#define GPIO_OTYPER_OT_5           ((uint32_t)0x00000020)
#define GPIO_OTYPER_OT_6           ((uint32_t)0x00000040)
#define GPIO_OTYPER_OT_7           ((uint32_t)0x00000080)
#define GPIO_OTYPER_OT_8           ((uint32_t)0x00000100)
#define GPIO_OTYPER_OT_9           ((uint32_t)0x00000200)
#define GPIO_OTYPER_OT_10          ((uint32_t)0x00000400)
#define GPIO_OTYPER_OT_11          ((uint32_t)0x00000800)
#define GPIO_OTYPER_OT_12          ((uint32_t)0x00001000)
#define GPIO_OTYPER_OT_13          ((uint32_t)0x00002000)
#define GPIO_OTYPER_OT_14          ((uint32_t)0x00004000)
#define GPIO_OTYPER_OT_15          ((uint32_t)0x00008000)


/****************  Bit definition for GPIO_OSPEEDR register  ******************/
#define GPIO_OSPEEDER_OSPEEDR0     ((uint32_t)0x00000003)
#define GPIO_OSPEEDER_OSPEEDR0_0   ((uint32_t)0x00000001)
#define GPIO_OSPEEDER_OSPEEDR0_1   ((uint32_t)0x00000002)
#define GPIO_OSPEEDER_OSPEEDR1     ((uint32_t)0x0000000C)
#define GPIO_OSPEEDER_OSPEEDR1_0   ((uint32_t)0x00000004)
#define GPIO_OSPEEDER_OSPEEDR1_1   ((uint32_t)0x00000008)
#define GPIO_OSPEEDER_OSPEEDR2     ((uint32_t)0x00000030)
#define GPIO_OSPEEDER_OSPEEDR2_0   ((uint32_t)0x00000010)
#define GPIO_OSPEEDER_OSPEEDR2_1   ((uint32_t)0x00000020)
#define GPIO_OSPEEDER_OSPEEDR3     ((uint32_t)0x000000C0)
#define GPIO_OSPEEDER_OSPEEDR3_0   ((uint32_t)0x00000040)
#define GPIO_OSPEEDER_OSPEEDR3_1   ((uint32_t)0x00000080)
#define GPIO_OSPEEDER_OSPEEDR4     ((uint32_t)0x00000300)
#define GPIO_OSPEEDER_OSPEEDR4_0   ((uint32_t)0x00000100)
#define GPIO_OSPEEDER_OSPEEDR4_1   ((uint32_t)0x00000200)
#define GPIO_OSPEEDER_OSPEEDR5     ((uint32_t)0x00000C00)
#define GPIO_OSPEEDER_OSPEEDR5_0   ((uint32_t)0x00000400)
#define GPIO_OSPEEDER_OSPEEDR5_1   ((uint32_t)0x00000800)
#define GPIO_OSPEEDER_OSPEEDR6     ((uint32_t)0x00003000)
#define GPIO_OSPEEDER_OSPEEDR6_0   ((uint32_t)0x00001000)
#define GPIO_OSPEEDER_OSPEEDR6_1   ((uint32_t)0x00002000)
#define GPIO_OSPEEDER_OSPEEDR7     ((uint32_t)0x0000C000)
#define GPIO_OSPEEDER_OSPEEDR7_0   ((uint32_t)0x00004000)
#define GPIO_OSPEEDER_OSPEEDR7_1   ((uint32_t)0x00008000)
#define GPIO_OSPEEDER_OSPEEDR8     ((uint32_t)0x00030000)
#define GPIO_OSPEEDER_OSPEEDR8_0   ((uint32_t)0x00010000)
#define GPIO_OSPEEDER_OSPEEDR8_1   ((uint32_t)0x00020000)
#define GPIO_OSPEEDER_OSPEEDR9     ((uint32_t)0x000C0000)
#define GPIO_OSPEEDER_OSPEEDR9_0   ((uint32_t)0x00040000)
#define GPIO_OSPEEDER_OSPEEDR9_1   ((uint32_t)0x00080000)
#define GPIO_OSPEEDER_OSPEEDR10    ((uint32_t)0x00300000)
#define GPIO_OSPEEDER_OSPEEDR10_0  ((uint32_t)0x00100000)
#define GPIO_OSPEEDER_OSPEEDR10_1  ((uint32_t)0x00200000)
#define GPIO_OSPEEDER_OSPEEDR11    ((uint32_t)0x00C00000)
#define GPIO_OSPEEDER_OSPEEDR11_0  ((uint32_t)0x00400000)
#define GPIO_OSPEEDER_OSPEEDR11_1  ((uint32_t)0x00800000)
#define GPIO_OSPEEDER_OSPEEDR12    ((uint32_t)0x03000000)
#define GPIO_OSPEEDER_OSPEEDR12_0  ((uint32_t)0x01000000)
#define GPIO_OSPEEDER_OSPEEDR12_1  ((uint32_t)0x02000000)
#define GPIO_OSPEEDER_OSPEEDR13    ((uint32_t)0x0C000000)
#define GPIO_OSPEEDER_OSPEEDR13_0  ((uint32_t)0x04000000)
#define GPIO_OSPEEDER_OSPEEDR13_1  ((uint32_t)0x08000000)
#define GPIO_OSPEEDER_OSPEEDR14    ((uint32_t)0x30000000)
#define GPIO_OSPEEDER_OSPEEDR14_0  ((uint32_t)0x10000000)
#define GPIO_OSPEEDER_OSPEEDR14_1  ((uint32_t)0x20000000)
#define GPIO_OSPEEDER_OSPEEDR15    ((uint32_t)0xC0000000)
#define GPIO_OSPEEDER_OSPEEDR15_0  ((uint32_t)0x40000000)
#define GPIO_OSPEEDER_OSPEEDR15_1  ((uint32_t)0x80000000)                       

/*******************  Bit definition for GPIO_PUPDR register ******************/
#define GPIO_PUPDR_PUPDR0          ((uint32_t)0x00000003)
#define GPIO_PUPDR_PUPDR0_0        ((uint32_t)0x00000001)
#define GPIO_PUPDR_PUPDR0_1        ((uint32_t)0x00000002)
#define GPIO_PUPDR_PUPDR1          ((uint32_t)0x0000000C)
#define GPIO_PUPDR_PUPDR1_0        ((uint32_t)0x00000004)
#define GPIO_PUPDR_PUPDR1_1        ((uint32_t)0x00000008)
#define GPIO_PUPDR_PUPDR2          ((uint32_t)0x00000030)
#define GPIO_PUPDR_PUPDR2_0        ((uint32_t)0x00000010)
#define GPIO_PUPDR_PUPDR2_1        ((uint32_t)0x00000020)
#define GPIO_PUPDR_PUPDR3          ((uint32_t)0x000000C0)
#define GPIO_PUPDR_PUPDR3_0        ((uint32_t)0x00000040)
#define GPIO_PUPDR_PUPDR3_1        ((uint32_t)0x00000080)
#define GPIO_PUPDR_PUPDR4          ((uint32_t)0x00000300)
#define GPIO_PUPDR_PUPDR4_0        ((uint32_t)0x00000100)
#define GPIO_PUPDR_PUPDR4_1        ((uint32_t)0x00000200)
#define GPIO_PUPDR_PUPDR5          ((uint32_t)0x00000C00)
#define GPIO_PUPDR_PUPDR5_0        ((uint32_t)0x00000400)
#define GPIO_PUPDR_PUPDR5_1        ((uint32_t)0x00000800)
#define GPIO_PUPDR_PUPDR6          ((uint32_t)0x00003000)
#define GPIO_PUPDR_PUPDR6_0        ((uint32_t)0x00001000)
#define GPIO_PUPDR_PUPDR6_1        ((uint32_t)0x00002000)
#define GPIO_PUPDR_PUPDR7          ((uint32_t)0x0000C000)
#define GPIO_PUPDR_PUPDR7_0        ((uint32_t)0x00004000)
#define GPIO_PUPDR_PUPDR7_1        ((uint32_t)0x00008000)
#define GPIO_PUPDR_PUPDR8          ((uint32_t)0x00030000)
#define GPIO_PUPDR_PUPDR8_0        ((uint32_t)0x00010000)
#define GPIO_PUPDR_PUPDR8_1        ((uint32_t)0x00020000)
#define GPIO_PUPDR_PUPDR9          ((uint32_t)0x000C0000)
#define GPIO_PUPDR_PUPDR9_0        ((uint32_t)0x00040000)
#define GPIO_PUPDR_PUPDR9_1        ((uint32_t)0x00080000)
#define GPIO_PUPDR_PUPDR10         ((uint32_t)0x00300000)
#define GPIO_PUPDR_PUPDR10_0       ((uint32_t)0x00100000)
#define GPIO_PUPDR_PUPDR10_1       ((uint32_t)0x00200000)
#define GPIO_PUPDR_PUPDR11         ((uint32_t)0x00C00000)
#define GPIO_PUPDR_PUPDR11_0       ((uint32_t)0x00400000)
#define GPIO_PUPDR_PUPDR11_1       ((uint32_t)0x00800000)
#define GPIO_PUPDR_PUPDR12         ((uint32_t)0x03000000)
#define GPIO_PUPDR_PUPDR12_0       ((uint32_t)0x01000000)
#define GPIO_PUPDR_PUPDR12_1       ((uint32_t)0x02000000)
#define GPIO_PUPDR_PUPDR13         ((uint32_t)0x0C000000)
#define GPIO_PUPDR_PUPDR13_0       ((uint32_t)0x04000000)
#define GPIO_PUPDR_PUPDR13_1       ((uint32_t)0x08000000)
#define GPIO_PUPDR_PUPDR14         ((uint32_t)0x30000000)
#define GPIO_PUPDR_PUPDR14_0       ((uint32_t)0x10000000)
#define GPIO_PUPDR_PUPDR14_1       ((uint32_t)0x20000000)
#define GPIO_PUPDR_PUPDR15         ((uint32_t)0xC0000000)
#define GPIO_PUPDR_PUPDR15_0       ((uint32_t)0x40000000)
#define GPIO_PUPDR_PUPDR15_1       ((uint32_t)0x80000000)

/*******************  Bit definition for GPIO_IDR register  *******************/
#define GPIO_IDR_0                 ((uint32_t)0x00000001)
#define GPIO_IDR_1                 ((uint32_t)0x00000002)
#define GPIO_IDR_2                 ((uint32_t)0x00000004)
#define GPIO_IDR_3                 ((uint32_t)0x00000008)
#define GPIO_IDR_4                 ((uint32_t)0x00000010)
#define GPIO_IDR_5                 ((uint32_t)0x00000020)
#define GPIO_IDR_6                 ((uint32_t)0x00000040)
#define GPIO_IDR_7                 ((uint32_t)0x00000080)
#define GPIO_IDR_8                 ((uint32_t)0x00000100)
#define GPIO_IDR_9                 ((uint32_t)0x00000200)
#define GPIO_IDR_10                ((uint32_t)0x00000400)
#define GPIO_IDR_11                ((uint32_t)0x00000800)
#define GPIO_IDR_12                ((uint32_t)0x00001000)
#define GPIO_IDR_13                ((uint32_t)0x00002000)
#define GPIO_IDR_14                ((uint32_t)0x00004000)
#define GPIO_IDR_15                ((uint32_t)0x00008000)

/******************  Bit definition for GPIO_ODR register  ********************/
#define GPIO_ODR_0                 ((uint32_t)0x00000001)
#define GPIO_ODR_1                 ((uint32_t)0x00000002)
#define GPIO_ODR_2                 ((uint32_t)0x00000004)
#define GPIO_ODR_3                 ((uint32_t)0x00000008)
#define GPIO_ODR_4                 ((uint32_t)0x00000010)
#define GPIO_ODR_5                 ((uint32_t)0x00000020)
#define GPIO_ODR_6                 ((uint32_t)0x00000040)
#define GPIO_ODR_7                 ((uint32_t)0x00000080)
#define GPIO_ODR_8                 ((uint32_t)0x00000100)
#define GPIO_ODR_9                 ((uint32_t)0x00000200)
#define GPIO_ODR_10                ((uint32_t)0x00000400)
#define GPIO_ODR_11                ((uint32_t)0x00000800)
#define GPIO_ODR_12                ((uint32_t)0x00001000)
#define GPIO_ODR_13                ((uint32_t)0x00002000)
#define GPIO_ODR_14                ((uint32_t)0x00004000)
#define GPIO_ODR_15                ((uint32_t)0x00008000)

/****************** Bit definition for GPIO_BSRR register  ********************/
#define GPIO_BSRR_BS_0             ((uint32_t)0x00000001)
#define GPIO_BSRR_BS_1             ((uint32_t)0x00000002)
#define GPIO_BSRR_BS_2             ((uint32_t)0x00000004)
#define GPIO_BSRR_BS_3             ((uint32_t)0x00000008)
#define GPIO_BSRR_BS_4             ((uint32_t)0x00000010)
#define GPIO_BSRR_BS_5             ((uint32_t)0x00000020)
#define GPIO_BSRR_BS_6             ((uint32_t)0x00000040)
#define GPIO_BSRR_BS_7             ((uint32_t)0x00000080)
#define GPIO_BSRR_BS_8             ((uint32_t)0x00000100)
#define GPIO_BSRR_BS_9             ((uint32_t)0x00000200)
#define GPIO_BSRR_BS_10            ((uint32_t)0x00000400)
#define GPIO_BSRR_BS_11            ((uint32_t)0x00000800)
#define GPIO_BSRR_BS_12            ((uint32_t)0x00001000)
#define GPIO_BSRR_BS_13            ((uint32_t)0x00002000)
#define GPIO_BSRR_BS_14            ((uint32_t)0x00004000)
#define GPIO_BSRR_BS_15            ((uint32_t)0x00008000)
#define GPIO_BSRR_BR_0             ((uint32_t)0x00010000)
#define GPIO_BSRR_BR_1             ((uint32_t)0x00020000)
#define GPIO_BSRR_BR_2             ((uint32_t)0x00040000)
#define GPIO_BSRR_BR_3             ((uint32_t)0x00080000)
#define GPIO_BSRR_BR_4             ((uint32_t)0x00100000)
#define GPIO_BSRR_BR_5             ((uint32_t)0x00200000)
#define GPIO_BSRR_BR_6             ((uint32_t)0x00400000)
#define GPIO_BSRR_BR_7             ((uint32_t)0x00800000)
#define GPIO_BSRR_BR_8             ((uint32_t)0x01000000)
#define GPIO_BSRR_BR_9             ((uint32_t)0x02000000)
#define GPIO_BSRR_BR_10            ((uint32_t)0x04000000)
#define GPIO_BSRR_BR_11            ((uint32_t)0x08000000)
#define GPIO_BSRR_BR_12            ((uint32_t)0x10000000)
#define GPIO_BSRR_BR_13            ((uint32_t)0x20000000)
#define GPIO_BSRR_BR_14            ((uint32_t)0x40000000)
#define GPIO_BSRR_BR_15            ((uint32_t)0x80000000)

/****************** Bit definition for GPIO_LCKR register  ********************/
#define GPIO_LCKR_LCK0             ((uint32_t)0x00000001)
#define GPIO_LCKR_LCK1             ((uint32_t)0x00000002)
#define GPIO_LCKR_LCK2             ((uint32_t)0x00000004)
#define GPIO_LCKR_LCK3             ((uint32_t)0x00000008)
#define GPIO_LCKR_LCK4             ((uint32_t)0x00000010)
#define GPIO_LCKR_LCK5             ((uint32_t)0x00000020)
#define GPIO_LCKR_LCK6             ((uint32_t)0x00000040)
#define GPIO_LCKR_LCK7             ((uint32_t)0x00000080)
#define GPIO_LCKR_LCK8             ((uint32_t)0x00000100)
#define GPIO_LCKR_LCK9             ((uint32_t)0x00000200)
#define GPIO_LCKR_LCK10            ((uint32_t)0x00000400)
#define GPIO_LCKR_LCK11            ((uint32_t)0x00000800)
#define GPIO_LCKR_LCK12            ((uint32_t)0x00001000)
#define GPIO_LCKR_LCK13            ((uint32_t)0x00002000)
#define GPIO_LCKR_LCK14            ((uint32_t)0x00004000)
#define GPIO_LCKR_LCK15            ((uint32_t)0x00008000)
#define GPIO_LCKR_LCKK             ((uint32_t)0x00010000)

/****************** Bit definition for GPIO_AFRL register  ********************/
#define GPIO_AFRL_AFRL0            ((uint32_t)0x0000000F)
#define GPIO_AFRL_AFRL1            ((uint32_t)0x000000F0)
#define GPIO_AFRL_AFRL2            ((uint32_t)0x00000F00)
#define GPIO_AFRL_AFRL3            ((uint32_t)0x0000F000)
#define GPIO_AFRL_AFRL4            ((uint32_t)0x000F0000)
#define GPIO_AFRL_AFRL5            ((uint32_t)0x00F00000)
#define GPIO_AFRL_AFRL6            ((uint32_t)0x0F000000)
#define GPIO_AFRL_AFRL7            ((uint32_t)0xF0000000)

/****************** Bit definition for GPIO_AFRH register  ********************/
#define GPIO_AFRH_AFRH0            ((uint32_t)0x0000000F)
#define GPIO_AFRH_AFRH1            ((uint32_t)0x000000F0)
#define GPIO_AFRH_AFRH2            ((uint32_t)0x00000F00)
#define GPIO_AFRH_AFRH3            ((uint32_t)0x0000F000)
#define GPIO_AFRH_AFRH4            ((uint32_t)0x000F0000)
#define GPIO_AFRH_AFRH5            ((uint32_t)0x00F00000)
#define GPIO_AFRH_AFRH6            ((uint32_t)0x0F000000)
#define GPIO_AFRH_AFRH7            ((uint32_t)0xF0000000)

/****************** Bit definition for GPIO_BRR register  *********************/
#define GPIO_BRR_BR_0              ((uint32_t)0x00000001)
#define GPIO_BRR_BR_1              ((uint32_t)0x00000002)
#define GPIO_BRR_BR_2              ((uint32_t)0x00000004)
#define GPIO_BRR_BR_3              ((uint32_t)0x00000008)
#define GPIO_BRR_BR_4              ((uint32_t)0x00000010)
#define GPIO_BRR_BR_5              ((uint32_t)0x00000020)
#define GPIO_BRR_BR_6              ((uint32_t)0x00000040)
#define GPIO_BRR_BR_7              ((uint32_t)0x00000080)
#define GPIO_BRR_BR_8              ((uint32_t)0x00000100)
#define GPIO_BRR_BR_9              ((uint32_t)0x00000200)
#define GPIO_BRR_BR_10             ((uint32_t)0x00000400)
#define GPIO_BRR_BR_11             ((uint32_t)0x00000800)
#define GPIO_BRR_BR_12             ((uint32_t)0x00001000)
#define GPIO_BRR_BR_13             ((uint32_t)0x00002000)
#define GPIO_BRR_BR_14             ((uint32_t)0x00004000)
#define GPIO_BRR_BR_15             ((uint32_t)0x00008000)

/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface (I2C)              */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for I2C_CR1 register  *******************/
#define  I2C_CR1_PE                          ((uint32_t)0x00000001)        /*!< Peripheral enable */
#define  I2C_CR1_TXIE                        ((uint32_t)0x00000002)        /*!< TX interrupt enable */
#define  I2C_CR1_RXIE                        ((uint32_t)0x00000004)        /*!< RX interrupt enable */
#define  I2C_CR1_ADDRIE                      ((uint32_t)0x00000008)        /*!< Address match interrupt enable */
#define  I2C_CR1_NACKIE                      ((uint32_t)0x00000010)        /*!< NACK received interrupt enable */
#define  I2C_CR1_STOPIE                      ((uint32_t)0x00000020)        /*!< STOP detection interrupt enable */
#define  I2C_CR1_TCIE                        ((uint32_t)0x00000040)        /*!< Transfer complete interrupt enable */
#define  I2C_CR1_ERRIE                       ((uint32_t)0x00000080)        /*!< Errors interrupt enable */
#define  I2C_CR1_DFN                         ((uint32_t)0x00000F00)        /*!< Digital noise filter */
#define  I2C_CR1_ANFOFF                      ((uint32_t)0x00001000)        /*!< Analog noise filter OFF */
#define  I2C_CR1_SWRST                       ((uint32_t)0x00002000)        /*!< Software reset */
#define  I2C_CR1_TXDMAEN                     ((uint32_t)0x00004000)        /*!< DMA transmission requests enable */
#define  I2C_CR1_RXDMAEN                     ((uint32_t)0x00008000)        /*!< DMA reception requests enable */
#define  I2C_CR1_SBC                         ((uint32_t)0x00010000)        /*!< Slave byte control */
#define  I2C_CR1_NOSTRETCH                   ((uint32_t)0x00020000)        /*!< Clock stretching disable */
#define  I2C_CR1_WUPEN                       ((uint32_t)0x00040000)        /*!< Wakeup from STOP enable */
#define  I2C_CR1_GCEN                        ((uint32_t)0x00080000)        /*!< General call enable */
#define  I2C_CR1_SMBHEN                      ((uint32_t)0x00100000)        /*!< SMBus host address enable */
#define  I2C_CR1_SMBDEN                      ((uint32_t)0x00200000)        /*!< SMBus device default address enable */
#define  I2C_CR1_ALERTEN                     ((uint32_t)0x00400000)        /*!< SMBus alert enable */
#define  I2C_CR1_PECEN                       ((uint32_t)0x00800000)        /*!< PEC enable */

/******************  Bit definition for I2C_CR2 register  ********************/
#define  I2C_CR2_SADD                        ((uint32_t)0x000003FF)        /*!< Slave address (master mode) */
#define  I2C_CR2_RD_WRN                      ((uint32_t)0x00000400)        /*!< Transfer direction (master mode) */
#define  I2C_CR2_ADD10                       ((uint32_t)0x00000800)        /*!< 10-bit addressing mode (master mode) */
#define  I2C_CR2_HEAD10R                     ((uint32_t)0x00001000)        /*!< 10-bit address header only read direction (master mode) */
#define  I2C_CR2_START                       ((uint32_t)0x00002000)        /*!< START generation */
#define  I2C_CR2_STOP                        ((uint32_t)0x00004000)        /*!< STOP generation (master mode) */
#define  I2C_CR2_NACK                        ((uint32_t)0x00008000)        /*!< NACK generation (slave mode) */
#define  I2C_CR2_NBYTES                      ((uint32_t)0x00FF0000)        /*!< Number of bytes */
#define  I2C_CR2_RELOAD                      ((uint32_t)0x01000000)        /*!< NBYTES reload mode */
#define  I2C_CR2_AUTOEND                     ((uint32_t)0x02000000)        /*!< Automatic end mode (master mode) */
#define  I2C_CR2_PECBYTE                     ((uint32_t)0x04000000)        /*!< Packet error checking byte */

/*******************  Bit definition for I2C_OAR1 register  ******************/
#define  I2C_OAR1_OA1                        ((uint32_t)0x000003FF)        /*!< Interface own address 1 */
#define  I2C_OAR1_OA1MODE                    ((uint32_t)0x00000400)        /*!< Own address 1 10-bit mode */
#define  I2C_OAR1_OA1EN                      ((uint32_t)0x00008000)        /*!< Own address 1 enable */

/*******************  Bit definition for I2C_OAR2 register  *******************/
#define  I2C_OAR2_OA2                        ((uint32_t)0x000000FE)        /*!< Interface own address 2 */
#define  I2C_OAR2_OA2MSK                     ((uint32_t)0x00000700)        /*!< Own address 2 masks */
#define  I2C_OAR2_OA2EN                      ((uint32_t)0x00008000)        /*!< Own address 2 enable */

/*******************  Bit definition for I2C_TIMINGR register *****************/
#define  I2C_TIMINGR_SCLL                    ((uint32_t)0x000000FF)        /*!< SCL low period (master mode) */
#define  I2C_TIMINGR_SCLH                    ((uint32_t)0x0000FF00)        /*!< SCL high period (master mode) */
#define  I2C_TIMINGR_SDADEL                  ((uint32_t)0x000F0000)        /*!< Data hold time */
#define  I2C_TIMINGR_SCLDEL                  ((uint32_t)0x00F00000)        /*!< Data setup time */
#define  I2C_TIMINGR_PRESC                   ((uint32_t)0xF0000000)        /*!< Timings prescaler */

/******************* Bit definition for I2C_TIMEOUTR register *****************/
#define  I2C_TIMEOUTR_TIMEOUTA               ((uint32_t)0x00000FFF)        /*!< Bus timeout A */
#define  I2C_TIMEOUTR_TIDLE                  ((uint32_t)0x00001000)        /*!< Idle clock timeout detection */
#define  I2C_TIMEOUTR_TIMOUTEN               ((uint32_t)0x00008000)        /*!< Clock timeout enable */
#define  I2C_TIMEOUTR_TIMEOUTB               ((uint32_t)0x0FFF0000)        /*!< Bus timeout B*/
#define  I2C_TIMEOUTR_TEXTEN                 ((uint32_t)0x80000000)        /*!< Extended clock timeout enable */

/******************  Bit definition for I2C_ISR register  *********************/
#define  I2C_ISR_TXE                         ((uint32_t)0x00000001)        /*!< Transmit data register empty */
#define  I2C_ISR_TXIS                        ((uint32_t)0x00000002)        /*!< Transmit interrupt status */
#define  I2C_ISR_RXNE                        ((uint32_t)0x00000004)        /*!< Receive data register not empty */
#define  I2C_ISR_ADDR                        ((uint32_t)0x00000008)        /*!< Address matched (slave mode)*/
#define  I2C_ISR_NACKF                       ((uint32_t)0x00000010)        /*!< NACK received flag */
#define  I2C_ISR_STOPF                       ((uint32_t)0x00000020)        /*!< STOP detection flag */
#define  I2C_ISR_TC                          ((uint32_t)0x00000040)        /*!< Transfer complete (master mode) */
#define  I2C_ISR_TCR                         ((uint32_t)0x00000080)        /*!< Transfer complete reload */
#define  I2C_ISR_BERR                        ((uint32_t)0x00000100)        /*!< Bus error */
#define  I2C_ISR_ARLO                        ((uint32_t)0x00000200)        /*!< Arbitration lost */
#define  I2C_ISR_OVR                         ((uint32_t)0x00000400)        /*!< Overrun/Underrun */
#define  I2C_ISR_PECERR                      ((uint32_t)0x00000800)        /*!< PEC error in reception */
#define  I2C_ISR_TIMEOUT                     ((uint32_t)0x00001000)        /*!< Timeout or Tlow detection flag */
#define  I2C_ISR_ALERT                       ((uint32_t)0x00002000)        /*!< SMBus alert */
#define  I2C_ISR_BUSY                        ((uint32_t)0x00008000)        /*!< Bus busy */
#define  I2C_ISR_DIR                         ((uint32_t)0x00010000)        /*!< Transfer direction (slave mode) */
#define  I2C_ISR_ADDCODE                     ((uint32_t)0x00FE0000)        /*!< Address match code (slave mode) */

/******************  Bit definition for I2C_ICR register  *********************/
#define  I2C_ICR_ADDRCF                      ((uint32_t)0x00000008)        /*!< Address matched clear flag */
#define  I2C_ICR_NACKCF                      ((uint32_t)0x00000010)        /*!< NACK clear flag */
#define  I2C_ICR_STOPCF                      ((uint32_t)0x00000020)        /*!< STOP detection clear flag */
#define  I2C_ICR_BERRCF                      ((uint32_t)0x00000100)        /*!< Bus error clear flag */
#define  I2C_ICR_ARLOCF                      ((uint32_t)0x00000200)        /*!< Arbitration lost clear flag */
#define  I2C_ICR_OVRCF                       ((uint32_t)0x00000400)        /*!< Overrun/Underrun clear flag */
#define  I2C_ICR_PECCF                       ((uint32_t)0x00000800)        /*!< PAC error clear flag */
#define  I2C_ICR_TIMOUTCF                    ((uint32_t)0x00001000)        /*!< Timeout clear flag */
#define  I2C_ICR_ALERTCF                     ((uint32_t)0x00002000)        /*!< Alert clear flag */

/******************  Bit definition for I2C_PECR register  ********************/
#define  I2C_PECR_PEC                        ((uint32_t)0x000000FF)        /*!< PEC register */

/******************  Bit definition for I2C_RXDR register  *********************/
#define  I2C_RXDR_RXDATA                     ((uint32_t)0x000000FF)        /*!< 8-bit receive data */

/******************  Bit definition for I2C_TXDR register  *********************/
#define  I2C_TXDR_TXDATA                     ((uint32_t)0x000000FF)        /*!< 8-bit transmit data */


/******************************************************************************/
/*                                                                            */
/*                           Independent WATCHDOG (IWDG)                      */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for IWDG_KR register  ********************/
#define  IWDG_KR_KEY                         ((uint16_t)0xFFFF)            /*!< Key value (write only, read 0000h) */

/*******************  Bit definition for IWDG_PR register  ********************/
#define  IWDG_PR_PR                          ((uint8_t)0x07)               /*!< PR[2:0] (Prescaler divider) */
#define  IWDG_PR_PR_0                        ((uint8_t)0x01)               /*!< Bit 0 */
#define  IWDG_PR_PR_1                        ((uint8_t)0x02)               /*!< Bit 1 */
#define  IWDG_PR_PR_2                        ((uint8_t)0x04)               /*!< Bit 2 */

/*******************  Bit definition for IWDG_RLR register  *******************/
#define  IWDG_RLR_RL                         ((uint16_t)0x0FFF)            /*!< Watchdog counter reload value */

/*******************  Bit definition for IWDG_SR register  ********************/
#define  IWDG_SR_PVU                         ((uint8_t)0x01)               /*!< Watchdog prescaler value update */
#define  IWDG_SR_RVU                         ((uint8_t)0x02)               /*!< Watchdog counter reload value update */
#define  IWDG_SR_WVU                         ((uint8_t)0x04)               /*!< Watchdog counter window value update */

/*******************  Bit definition for IWDG_KR register  ********************/
#define  IWDG_WINR_WIN                       ((uint16_t)0x0FFF)            /*!< Watchdog counter window value */

/******************************************************************************/
/*                                                                            */
/*                             Power Control                                  */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for PWR_CR register  ********************/
#define  PWR_CR_LPSDSR                       ((uint16_t)0x0001)     /*!< Low-power deepsleep/sleep/low power run */
#define  PWR_CR_PDDS                         ((uint16_t)0x0002)     /*!< Power Down Deepsleep */
#define  PWR_CR_CWUF                         ((uint16_t)0x0004)     /*!< Clear Wakeup Flag */
#define  PWR_CR_CSBF                         ((uint16_t)0x0008)     /*!< Clear Standby Flag */
#define  PWR_CR_PVDE                         ((uint16_t)0x0010)     /*!< Power Voltage Detector Enable */

#define  PWR_CR_PLS                          ((uint16_t)0x00E0)     /*!< PLS[2:0] bits (PVD Level Selection) */
#define  PWR_CR_PLS_0                        ((uint16_t)0x0020)     /*!< Bit 0 */
#define  PWR_CR_PLS_1                        ((uint16_t)0x0040)     /*!< Bit 1 */
#define  PWR_CR_PLS_2                        ((uint16_t)0x0080)     /*!< Bit 2 */

/*!< PVD level configuration */
#define  PWR_CR_PLS_LEV0                     ((uint16_t)0x0000)     /*!< PVD level 0 */
#define  PWR_CR_PLS_LEV1                     ((uint16_t)0x0020)     /*!< PVD level 1 */
#define  PWR_CR_PLS_LEV2                     ((uint16_t)0x0040)     /*!< PVD level 2 */
#define  PWR_CR_PLS_LEV3                     ((uint16_t)0x0060)     /*!< PVD level 3 */
#define  PWR_CR_PLS_LEV4                     ((uint16_t)0x0080)     /*!< PVD level 4 */
#define  PWR_CR_PLS_LEV5                     ((uint16_t)0x00A0)     /*!< PVD level 5 */
#define  PWR_CR_PLS_LEV6                     ((uint16_t)0x00C0)     /*!< PVD level 6 */
#define  PWR_CR_PLS_LEV7                     ((uint16_t)0x00E0)     /*!< PVD level 7 */

#define  PWR_CR_DBP                          ((uint16_t)0x0100)     /*!< Disable Backup Domain write protection */

/*******************  Bit definition for PWR_CSR register  ********************/
#define  PWR_CSR_WUF                         ((uint16_t)0x0001)     /*!< Wakeup Flag */
#define  PWR_CSR_SBF                         ((uint16_t)0x0002)     /*!< Standby Flag */
#define  PWR_CSR_PVDO                        ((uint16_t)0x0004)     /*!< PVD Output */
#define  PWR_CSR_VREFINTRDYF                 ((uint16_t)0x0008)     /*!< Internal voltage reference (VREFINT) ready flag */

#define  PWR_CSR_EWUP1                       ((uint16_t)0x0100)     /*!< Enable WKUP pin 1 */
#define  PWR_CSR_EWUP2                       ((uint16_t)0x0200)     /*!< Enable WKUP pin 2 */
#define  PWR_CSR_EWUP3                       ((uint16_t)0x0400)     /*!< Enable WKUP pin 3 */

/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for RCC_CR register  ********************/
#define  RCC_CR_HSION                        ((uint32_t)0x00000001)
#define  RCC_CR_HSIRDY                       ((uint32_t)0x00000002)

#define  RCC_CR_HSITRIM                      ((uint32_t)0x000000F8)
#define  RCC_CR_HSITRIM_0                    ((uint32_t)0x00000008)/*!<Bit 0 */
#define  RCC_CR_HSITRIM_1                    ((uint32_t)0x00000010)/*!<Bit 1 */
#define  RCC_CR_HSITRIM_2                    ((uint32_t)0x00000020)/*!<Bit 2 */
#define  RCC_CR_HSITRIM_3                    ((uint32_t)0x00000040)/*!<Bit 3 */
#define  RCC_CR_HSITRIM_4                    ((uint32_t)0x00000080)/*!<Bit 4 */

#define  RCC_CR_HSICAL                       ((uint32_t)0x0000FF00)
#define  RCC_CR_HSICAL_0                     ((uint32_t)0x00000100)/*!<Bit 0 */
#define  RCC_CR_HSICAL_1                     ((uint32_t)0x00000200)/*!<Bit 1 */
#define  RCC_CR_HSICAL_2                     ((uint32_t)0x00000400)/*!<Bit 2 */
#define  RCC_CR_HSICAL_3                     ((uint32_t)0x00000800)/*!<Bit 3 */
#define  RCC_CR_HSICAL_4                     ((uint32_t)0x00001000)/*!<Bit 4 */
#define  RCC_CR_HSICAL_5                     ((uint32_t)0x00002000)/*!<Bit 5 */
#define  RCC_CR_HSICAL_6                     ((uint32_t)0x00004000)/*!<Bit 6 */
#define  RCC_CR_HSICAL_7                     ((uint32_t)0x00008000)/*!<Bit 7 */

#define  RCC_CR_HSEON                        ((uint32_t)0x00010000)
#define  RCC_CR_HSERDY                       ((uint32_t)0x00020000)
#define  RCC_CR_HSEBYP                       ((uint32_t)0x00040000)
#define  RCC_CR_CSSON                        ((uint32_t)0x00080000)

#define  RCC_CR_PLLON                        ((uint32_t)0x01000000)
#define  RCC_CR_PLLRDY                       ((uint32_t)0x02000000)

/********************  Bit definition for RCC_CFGR register  ******************/
/*!< SW configuration */
#define  RCC_CFGR_SW                         ((uint32_t)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR_SW_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  RCC_CFGR_SW_HSI                     ((uint32_t)0x00000000)        /*!< HSI selected as system clock */
#define  RCC_CFGR_SW_HSE                     ((uint32_t)0x00000001)        /*!< HSE selected as system clock */
#define  RCC_CFGR_SW_PLL                     ((uint32_t)0x00000002)        /*!< PLL selected as system clock */

/*!< SWS configuration */
#define  RCC_CFGR_SWS                        ((uint32_t)0x0000000C)        /*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_SWS_0                      ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  RCC_CFGR_SWS_1                      ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  RCC_CFGR_SWS_HSI                    ((uint32_t)0x00000000)        /*!< HSI oscillator used as system clock */
#define  RCC_CFGR_SWS_HSE                    ((uint32_t)0x00000004)        /*!< HSE oscillator used as system clock */
#define  RCC_CFGR_SWS_PLL                    ((uint32_t)0x00000008)        /*!< PLL used as system clock */

/*!< HPRE configuration */
#define  RCC_CFGR_HPRE                       ((uint32_t)0x000000F0)        /*!< HPRE[3:0] bits (AHB prescaler) */
#define  RCC_CFGR_HPRE_0                     ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  RCC_CFGR_HPRE_1                     ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  RCC_CFGR_HPRE_2                     ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  RCC_CFGR_HPRE_3                     ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  RCC_CFGR_HPRE_DIV1                  ((uint32_t)0x00000000)        /*!< SYSCLK not divided */
#define  RCC_CFGR_HPRE_DIV2                  ((uint32_t)0x00000080)        /*!< SYSCLK divided by 2 */
#define  RCC_CFGR_HPRE_DIV4                  ((uint32_t)0x00000090)        /*!< SYSCLK divided by 4 */
#define  RCC_CFGR_HPRE_DIV8                  ((uint32_t)0x000000A0)        /*!< SYSCLK divided by 8 */
#define  RCC_CFGR_HPRE_DIV16                 ((uint32_t)0x000000B0)        /*!< SYSCLK divided by 16 */
#define  RCC_CFGR_HPRE_DIV64                 ((uint32_t)0x000000C0)        /*!< SYSCLK divided by 64 */
#define  RCC_CFGR_HPRE_DIV128                ((uint32_t)0x000000D0)        /*!< SYSCLK divided by 128 */
#define  RCC_CFGR_HPRE_DIV256                ((uint32_t)0x000000E0)        /*!< SYSCLK divided by 256 */
#define  RCC_CFGR_HPRE_DIV512                ((uint32_t)0x000000F0)        /*!< SYSCLK divided by 512 */

/*!< PPRE1 configuration */
#define  RCC_CFGR_PPRE1                      ((uint32_t)0x00000700)        /*!< PRE1[2:0] bits (APB1 prescaler) */
#define  RCC_CFGR_PPRE1_0                    ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  RCC_CFGR_PPRE1_1                    ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  RCC_CFGR_PPRE1_2                    ((uint32_t)0x00000400)        /*!< Bit 2 */

#define  RCC_CFGR_PPRE1_DIV1                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE1_DIV2                 ((uint32_t)0x00000400)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE1_DIV4                 ((uint32_t)0x00000500)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE1_DIV8                 ((uint32_t)0x00000600)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE1_DIV16                ((uint32_t)0x00000700)        /*!< HCLK divided by 16 */

/*!< PPRE2 configuration */
#define  RCC_CFGR_PPRE2                      ((uint32_t)0x00003800)        /*!< PRE2[2:0] bits (APB2 prescaler) */
#define  RCC_CFGR_PPRE2_0                    ((uint32_t)0x00000800)        /*!< Bit 0 */
#define  RCC_CFGR_PPRE2_1                    ((uint32_t)0x00001000)        /*!< Bit 1 */
#define  RCC_CFGR_PPRE2_2                    ((uint32_t)0x00002000)        /*!< Bit 2 */

#define  RCC_CFGR_PPRE2_DIV1                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE2_DIV2                 ((uint32_t)0x00002000)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE2_DIV4                 ((uint32_t)0x00002800)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE2_DIV8                 ((uint32_t)0x00003000)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE2_DIV16                ((uint32_t)0x00003800)        /*!< HCLK divided by 16 */

#define  RCC_CFGR_PLLSRC                     ((uint32_t)0x00010000)        /*!< PLL entry clock source */

#define  RCC_CFGR_PLLXTPRE                   ((uint32_t)0x00020000)        /*!< HSE divider for PLL entry */

/*!< PLLMUL configuration */
#define  RCC_CFGR_PLLMULL                    ((uint32_t)0x003C0000)        /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define  RCC_CFGR_PLLMULL_0                  ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  RCC_CFGR_PLLMULL_1                  ((uint32_t)0x00080000)        /*!< Bit 1 */
#define  RCC_CFGR_PLLMULL_2                  ((uint32_t)0x00100000)        /*!< Bit 2 */
#define  RCC_CFGR_PLLMULL_3                  ((uint32_t)0x00200000)        /*!< Bit 3 */

#define  RCC_CFGR_PLLSRC_HSI_Div2            ((uint32_t)0x00000000)        /*!< HSI clock divided by 2 selected as PLL entry clock source */
#define  RCC_CFGR_PLLSRC_PREDIV1             ((uint32_t)0x00010000)        /*!< PREDIV1 clock selected as PLL entry clock source */

#define  RCC_CFGR_PLLXTPRE_PREDIV1           ((uint32_t)0x00000000)        /*!< PREDIV1 clock not divided for PLL entry */
#define  RCC_CFGR_PLLXTPRE_PREDIV1_Div2      ((uint32_t)0x00020000)        /*!< PREDIV1 clock divided by 2 for PLL entry */

#define  RCC_CFGR_PLLMULL2                   ((uint32_t)0x00000000)        /*!< PLL input clock*2 */
#define  RCC_CFGR_PLLMULL3                   ((uint32_t)0x00040000)        /*!< PLL input clock*3 */
#define  RCC_CFGR_PLLMULL4                   ((uint32_t)0x00080000)        /*!< PLL input clock*4 */
#define  RCC_CFGR_PLLMULL5                   ((uint32_t)0x000C0000)        /*!< PLL input clock*5 */
#define  RCC_CFGR_PLLMULL6                   ((uint32_t)0x00100000)        /*!< PLL input clock*6 */
#define  RCC_CFGR_PLLMULL7                   ((uint32_t)0x00140000)        /*!< PLL input clock*7 */
#define  RCC_CFGR_PLLMULL8                   ((uint32_t)0x00180000)        /*!< PLL input clock*8 */
#define  RCC_CFGR_PLLMULL9                   ((uint32_t)0x001C0000)        /*!< PLL input clock*9 */
#define  RCC_CFGR_PLLMULL10                  ((uint32_t)0x00200000)        /*!< PLL input clock10 */
#define  RCC_CFGR_PLLMULL11                  ((uint32_t)0x00240000)        /*!< PLL input clock*11 */
#define  RCC_CFGR_PLLMULL12                  ((uint32_t)0x00280000)        /*!< PLL input clock*12 */
#define  RCC_CFGR_PLLMULL13                  ((uint32_t)0x002C0000)        /*!< PLL input clock*13 */
#define  RCC_CFGR_PLLMULL14                  ((uint32_t)0x00300000)        /*!< PLL input clock*14 */
#define  RCC_CFGR_PLLMULL15                  ((uint32_t)0x00340000)        /*!< PLL input clock*15 */
#define  RCC_CFGR_PLLMULL16                  ((uint32_t)0x00380000)        /*!< PLL input clock*16 */

/*!< USB configuration */
#define  RCC_CFGR_USBPRE                     ((uint32_t)0x00400000)        /*!< USB prescaler */

/*!< I2S configuration */
#define  RCC_CFGR_I2SSRC                     ((uint32_t)0x00800000)        /*!< I2S external clock source selection */

/*!< MCO configuration */
#define  RCC_CFGR_MCO                        ((uint32_t)0x07000000)        /*!< MCO[2:0] bits (Microcontroller Clock Output) */
#define  RCC_CFGR_MCO_0                      ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  RCC_CFGR_MCO_1                      ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  RCC_CFGR_MCO_2                      ((uint32_t)0x04000000)        /*!< Bit 2 */

#define  RCC_CFGR_MCO_NOCLOCK                ((uint32_t)0x00000000)        /*!< No clock */
#define  RCC_CFGR_MCO_LSI                    ((uint32_t)0x02000000)        /*!< LSI clock selected as MCO source */
#define  RCC_CFGR_MCO_LSE                    ((uint32_t)0x03000000)        /*!< LSE clock selected as MCO source */
#define  RCC_CFGR_MCO_SYSCLK                 ((uint32_t)0x04000000)        /*!< System clock selected as MCO source */
#define  RCC_CFGR_MCO_HSI                    ((uint32_t)0x05000000)        /*!< HSI clock selected as MCO source */
#define  RCC_CFGR_MCO_HSE                    ((uint32_t)0x06000000)        /*!< HSE clock selected as MCO source  */
#define  RCC_CFGR_MCO_PLL                    ((uint32_t)0x07000000)        /*!< PLL clock divided by 2 selected as MCO source */

#define  RCC_CFGR_MCOF                       ((uint32_t)0x10000000)        /*!< Microcontroller Clock Output Flag */

#define  RCC_CFGR_MCO_PRE                    ((uint32_t)0x70000000)        /*!< MCO prescaler */
#define  RCC_CFGR_MCO_PRE_1                  ((uint32_t)0x00000000)        /*!< MCO is divided by 1 */
#define  RCC_CFGR_MCO_PRE_2                  ((uint32_t)0x10000000)        /*!< MCO is divided by 2 */
#define  RCC_CFGR_MCO_PRE_4                  ((uint32_t)0x20000000)        /*!< MCO is divided by 4 */
#define  RCC_CFGR_MCO_PRE_8                  ((uint32_t)0x30000000)        /*!< MCO is divided by 8 */
#define  RCC_CFGR_MCO_PRE_16                 ((uint32_t)0x40000000)        /*!< MCO is divided by 16 */
#define  RCC_CFGR_MCO_PRE_32                 ((uint32_t)0x50000000)        /*!< MCO is divided by 32 */
#define  RCC_CFGR_MCO_PRE_64                 ((uint32_t)0x60000000)        /*!< MCO is divided by 64 */
#define  RCC_CFGR_MCO_PRE_128                ((uint32_t)0x70000000)        /*!< MCO is divided by 128 */

#define  RCC_CFGR_PLLNODIV                   ((uint32_t)0x80000000)        /*!< PLL is not divided to MCO */

/*********************  Bit definition for RCC_CIR register  ********************/
#define  RCC_CIR_LSIRDYF                     ((uint32_t)0x00000001)        /*!< LSI Ready Interrupt flag */
#define  RCC_CIR_LSERDYF                     ((uint32_t)0x00000002)        /*!< LSE Ready Interrupt flag */
#define  RCC_CIR_HSIRDYF                     ((uint32_t)0x00000004)        /*!< HSI Ready Interrupt flag */
#define  RCC_CIR_HSERDYF                     ((uint32_t)0x00000008)        /*!< HSE Ready Interrupt flag */
#define  RCC_CIR_PLLRDYF                     ((uint32_t)0x00000010)        /*!< PLL Ready Interrupt flag */
#define  RCC_CIR_CSSF                        ((uint32_t)0x00000080)        /*!< Clock Security System Interrupt flag */
#define  RCC_CIR_LSIRDYIE                    ((uint32_t)0x00000100)        /*!< LSI Ready Interrupt Enable */
#define  RCC_CIR_LSERDYIE                    ((uint32_t)0x00000200)        /*!< LSE Ready Interrupt Enable */
#define  RCC_CIR_HSIRDYIE                    ((uint32_t)0x00000400)        /*!< HSI Ready Interrupt Enable */
#define  RCC_CIR_HSERDYIE                    ((uint32_t)0x00000800)        /*!< HSE Ready Interrupt Enable */
#define  RCC_CIR_PLLRDYIE                    ((uint32_t)0x00001000)        /*!< PLL Ready Interrupt Enable */
#define  RCC_CIR_LSIRDYC                     ((uint32_t)0x00010000)        /*!< LSI Ready Interrupt Clear */
#define  RCC_CIR_LSERDYC                     ((uint32_t)0x00020000)        /*!< LSE Ready Interrupt Clear */
#define  RCC_CIR_HSIRDYC                     ((uint32_t)0x00040000)        /*!< HSI Ready Interrupt Clear */
#define  RCC_CIR_HSERDYC                     ((uint32_t)0x00080000)        /*!< HSE Ready Interrupt Clear */
#define  RCC_CIR_PLLRDYC                     ((uint32_t)0x00100000)        /*!< PLL Ready Interrupt Clear */
#define  RCC_CIR_CSSC                        ((uint32_t)0x00800000)        /*!< Clock Security System Interrupt Clear */

/******************  Bit definition for RCC_APB2RSTR register  *****************/
#define  RCC_APB2RSTR_SYSCFGRST              ((uint32_t)0x00000001)        /*!< SYSCFG reset */
#define  RCC_APB2RSTR_TIM1RST                ((uint32_t)0x00000200)        /*!< TIM1 reset */
#define  RCC_APB2RSTR_SPI1RST                ((uint32_t)0x00001000)        /*!< SPI1 reset */
#define  RCC_APB2RSTR_TIM8RST                ((uint32_t)0x00000200)        /*!< TIM8 reset */
#define  RCC_APB2RSTR_USART1RST              ((uint32_t)0x00004000)        /*!< USART1 reset */
#define  RCC_APB2RSTR_TIM15RST               ((uint32_t)0x00010000)        /*!< TIM15 reset */
#define  RCC_APB2RSTR_TIM16RST               ((uint32_t)0x00020000)        /*!< TIM16 reset */
#define  RCC_APB2RSTR_TIM17RST               ((uint32_t)0x00040000)        /*!< TIM17 reset */
#define  RCC_APB2RSTR_HRTIM1RST              ((uint32_t)0x20000000)        /*!< HRTIM1 reset */

/******************  Bit definition for RCC_APB1RSTR register  ******************/
#define  RCC_APB1RSTR_TIM2RST                ((uint32_t)0x00000001)        /*!< Timer 2 reset */
#define  RCC_APB1RSTR_TIM3RST                ((uint32_t)0x00000002)        /*!< Timer 3 reset */
#define  RCC_APB1RSTR_TIM4RST                ((uint32_t)0x00000004)        /*!< Timer 4 reset */
#define  RCC_APB1RSTR_TIM6RST                ((uint32_t)0x00000010)        /*!< Timer 6 reset */
#define  RCC_APB1RSTR_TIM7RST                ((uint32_t)0x00000020)        /*!< Timer 7 reset */
#define  RCC_APB1RSTR_WWDGRST                ((uint32_t)0x00000800)        /*!< Window Watchdog reset */
#define  RCC_APB1RSTR_SPI2RST                ((uint32_t)0x00004000)        /*!< SPI2 reset */
#define  RCC_APB1RSTR_SPI3RST                ((uint32_t)0x00008000)        /*!< SPI3 reset */
#define  RCC_APB1RSTR_USART2RST              ((uint32_t)0x00020000)        /*!< USART 2 reset */
#define  RCC_APB1RSTR_USART3RST              ((uint32_t)0x00040000)        /*!< USART 3 reset */
#define  RCC_APB1RSTR_UART4RST               ((uint32_t)0x00080000)        /*!< UART 4 reset */
#define  RCC_APB1RSTR_UART5RST               ((uint32_t)0x00100000)        /*!< UART 5 reset */
#define  RCC_APB1RSTR_I2C1RST                ((uint32_t)0x00200000)        /*!< I2C 1 reset */
#define  RCC_APB1RSTR_I2C2RST                ((uint32_t)0x00400000)        /*!< I2C 2 reset */
#define  RCC_APB1RSTR_USBRST                 ((uint32_t)0x00800000)        /*!< USB reset */
#define  RCC_APB1RSTR_CAN1RST                ((uint32_t)0x02000000)        /*!< CAN reset */
#define  RCC_APB1RSTR_PWRRST                 ((uint32_t)0x10000000)        /*!< PWR reset */
#define  RCC_APB1RSTR_DAC1RST                ((uint32_t)0x20000000)        /*!< DAC 1 reset */
#define  RCC_APB1RSTR_I2C3RST                ((uint32_t)0x40000000)        /*!< I2C 3 reset */
#define  RCC_APB1RSTR_DAC2RST                ((uint32_t)0x04000000)        /*!< DAC 2 reset */
#define  RCC_APB1RSTR_DACRST                 RCC_APB1RSTR_DAC1RST          /*!< DAC reset */

/******************  Bit definition for RCC_AHBENR register  ******************/
#define  RCC_AHBENR_DMA1EN                   ((uint32_t)0x00000001)        /*!< DMA1 clock enable */
#define  RCC_AHBENR_DMA2EN                   ((uint32_t)0x00000002)        /*!< DMA2 clock enable */
#define  RCC_AHBENR_SRAMEN                   ((uint32_t)0x00000004)        /*!< SRAM interface clock enable */
#define  RCC_AHBENR_FLITFEN                  ((uint32_t)0x00000010)        /*!< FLITF clock enable */
#define  RCC_AHBENR_CRCEN                    ((uint32_t)0x00000040)        /*!< CRC clock enable */
#define  RCC_AHBENR_GPIOAEN                  ((uint32_t)0x00020000)        /*!< GPIOA clock enable */
#define  RCC_AHBENR_GPIOBEN                  ((uint32_t)0x00040000)        /*!< GPIOB clock enable */
#define  RCC_AHBENR_GPIOCEN                  ((uint32_t)0x00080000)        /*!< GPIOC clock enable */
#define  RCC_AHBENR_GPIODEN                  ((uint32_t)0x00100000)        /*!< GPIOD clock enable */
#define  RCC_AHBENR_GPIOEEN                  ((uint32_t)0x00200000)        /*!< GPIOE clock enable */
#define  RCC_AHBENR_GPIOFEN                  ((uint32_t)0x00400000)        /*!< GPIOF clock enable */
#define  RCC_AHBENR_TSEN                     ((uint32_t)0x01000000)        /*!< TS clock enable */
#define  RCC_AHBENR_ADC12EN                  ((uint32_t)0x10000000)        /*!< ADC1/ ADC2 clock enable */
#define  RCC_AHBENR_ADC34EN                  ((uint32_t)0x20000000)        /*!< ADC1/ ADC2 clock enable */

/*****************  Bit definition for RCC_APB2ENR register  ******************/
#define  RCC_APB2ENR_SYSCFGEN                ((uint32_t)0x00000001)        /*!< SYSCFG clock enable */
#define  RCC_APB2ENR_TIM1EN                  ((uint32_t)0x00000800)        /*!< TIM1 clock enable */
#define  RCC_APB2ENR_SPI1EN                  ((uint32_t)0x00001000)        /*!< SPI1 clock enable */
#define  RCC_APB2ENR_TIM8EN                  ((uint32_t)0x00002000)        /*!< TIM8 clock enable */
#define  RCC_APB2ENR_USART1EN                ((uint32_t)0x00004000)        /*!< USART1 clock enable */
#define  RCC_APB2ENR_TIM15EN                 ((uint32_t)0x00010000)        /*!< TIM15 clock enable */
#define  RCC_APB2ENR_TIM16EN                 ((uint32_t)0x00020000)        /*!< TIM16 clock enable */
#define  RCC_APB2ENR_TIM17EN                 ((uint32_t)0x00040000)        /*!< TIM17 clock enable */
#define  RCC_APB2ENR_HRTIM1                  ((uint32_t)0x20000000)        /*!< HRTIM1 clock enable */

/******************  Bit definition for RCC_APB1ENR register  ******************/
#define  RCC_APB1ENR_TIM2EN                  ((uint32_t)0x00000001)        /*!< Timer 2 clock enable */
#define  RCC_APB1ENR_TIM3EN                  ((uint32_t)0x00000002)        /*!< Timer 3 clock enable */
#define  RCC_APB1ENR_TIM4EN                  ((uint32_t)0x00000004)        /*!< Timer 4 clock enable */
#define  RCC_APB1ENR_TIM6EN                  ((uint32_t)0x00000010)        /*!< Timer 6 clock enable */
#define  RCC_APB1ENR_TIM7EN                  ((uint32_t)0x00000020)        /*!< Timer 7 clock enable */
#define  RCC_APB1ENR_WWDGEN                  ((uint32_t)0x00000800)        /*!< Window Watchdog clock enable */
#define  RCC_APB1ENR_SPI2EN                  ((uint32_t)0x00004000)        /*!< SPI2 clock enable */
#define  RCC_APB1ENR_SPI3EN                  ((uint32_t)0x00008000)        /*!< SPI3 clock enable */
#define  RCC_APB1ENR_USART2EN                ((uint32_t)0x00020000)        /*!< USART 2 clock enable */
#define  RCC_APB1ENR_USART3EN                ((uint32_t)0x00040000)        /*!< USART 3 clock enable */
#define  RCC_APB1ENR_UART4EN                 ((uint32_t)0x00080000)        /*!< UART 4 clock enable */
#define  RCC_APB1ENR_UART5EN                 ((uint32_t)0x00100000)        /*!< UART 5 clock enable */
#define  RCC_APB1ENR_I2C1EN                  ((uint32_t)0x00200000)        /*!< I2C 1 clock enable */
#define  RCC_APB1ENR_I2C2EN                  ((uint32_t)0x00400000)        /*!< I2C 2 clock enable */
#define  RCC_APB1ENR_USBEN                   ((uint32_t)0x00800000)        /*!< USB clock enable */
#define  RCC_APB1ENR_CAN1EN                  ((uint32_t)0x02000000)        /*!< CAN clock enable */
#define  RCC_APB1ENR_DAC2EN                  ((uint32_t)0x04000000)        /*!< DAC 2 clock enable */
#define  RCC_APB1ENR_PWREN                   ((uint32_t)0x10000000)        /*!< PWR clock enable */
#define  RCC_APB1ENR_DAC1EN                  ((uint32_t)0x20000000)        /*!< DAC clock enable */
#define  RCC_APB1ENR_I2C3EN                  ((uint32_t)0x40000000)        /*!< I2C 3 clock enable */
#define  RCC_APB1ENR_DACEN                   RCC_APB1ENR_DAC1EN

/********************  Bit definition for RCC_BDCR register  ******************/
#define  RCC_BDCR_LSEON                      ((uint32_t)0x00000001)        /*!< External Low Speed oscillator enable */
#define  RCC_BDCR_LSERDY                     ((uint32_t)0x00000002)        /*!< External Low Speed oscillator Ready */
#define  RCC_BDCR_LSEBYP                     ((uint32_t)0x00000004)        /*!< External Low Speed oscillator Bypass */

#define  RCC_BDCR_LSEDRV                     ((uint32_t)0x00000018)        /*!< LSEDRV[1:0] bits (LSE Osc. drive capability) */
#define  RCC_BDCR_LSEDRV_0                   ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  RCC_BDCR_LSEDRV_1                   ((uint32_t)0x00000010)        /*!< Bit 1 */


#define  RCC_BDCR_RTCSEL                     ((uint32_t)0x00000300)        /*!< RTCSEL[1:0] bits (RTC clock source selection) */
#define  RCC_BDCR_RTCSEL_0                   ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  RCC_BDCR_RTCSEL_1                   ((uint32_t)0x00000200)        /*!< Bit 1 */

/*!< RTC configuration */
#define  RCC_BDCR_RTCSEL_NOCLOCK             ((uint32_t)0x00000000)        /*!< No clock */
#define  RCC_BDCR_RTCSEL_LSE                 ((uint32_t)0x00000100)        /*!< LSE oscillator clock used as RTC clock */
#define  RCC_BDCR_RTCSEL_LSI                 ((uint32_t)0x00000200)        /*!< LSI oscillator clock used as RTC clock */
#define  RCC_BDCR_RTCSEL_HSE                 ((uint32_t)0x00000300)        /*!< HSE oscillator clock divided by 32 used as RTC clock */

#define  RCC_BDCR_RTCEN                      ((uint32_t)0x00008000)        /*!< RTC clock enable */
#define  RCC_BDCR_BDRST                      ((uint32_t)0x00010000)        /*!< Backup domain software reset  */

/********************  Bit definition for RCC_CSR register  *******************/
#define  RCC_CSR_LSION                       ((uint32_t)0x00000001)        /*!< Internal Low Speed oscillator enable */
#define  RCC_CSR_LSIRDY                      ((uint32_t)0x00000002)        /*!< Internal Low Speed oscillator Ready */
#define  RCC_CSR_RMVF                        ((uint32_t)0x01000000)        /*!< Remove reset flag */
#define  RCC_CSR_OBLRSTF                     ((uint32_t)0x02000000)        /*!< OBL reset flag */
#define  RCC_CSR_PINRSTF                     ((uint32_t)0x04000000)        /*!< PIN reset flag */
#define  RCC_CSR_PORRSTF                     ((uint32_t)0x08000000)        /*!< POR/PDR reset flag */
#define  RCC_CSR_SFTRSTF                     ((uint32_t)0x10000000)        /*!< Software Reset flag */
#define  RCC_CSR_IWDGRSTF                    ((uint32_t)0x20000000)        /*!< Independent Watchdog reset flag */
#define  RCC_CSR_WWDGRSTF                    ((uint32_t)0x40000000)        /*!< Window watchdog reset flag */
#define  RCC_CSR_LPWRRSTF                    ((uint32_t)0x80000000)        /*!< Low-Power reset flag */

/*******************  Bit definition for RCC_AHBRSTR register  ****************/
#define  RCC_AHBRSTR_GPIOARST                ((uint32_t)0x00020000)         /*!< GPIOA reset */
#define  RCC_AHBRSTR_GPIOBRST                ((uint32_t)0x00040000)         /*!< GPIOB reset */
#define  RCC_AHBRSTR_GPIOCRST                ((uint32_t)0x00080000)         /*!< GPIOC reset */
#define  RCC_AHBRSTR_GPIODRST                ((uint32_t)0x00010000)         /*!< GPIOD reset */
#define  RCC_AHBRSTR_GPIOFRST                ((uint32_t)0x00040000)         /*!< GPIOF reset */
#define  RCC_AHBRSTR_TSRST                   ((uint32_t)0x00100000)         /*!< TS reset */
#define  RCC_AHBRSTR_ADC12RST                ((uint32_t)0x01000000)         /*!< ADC1 & ADC2 reset */
#define  RCC_AHBRSTR_ADC34RST                ((uint32_t)0x02000000)         /*!< ADC3 & ADC4 reset */

/*******************  Bit definition for RCC_CFGR2 register  ******************/
/*!< PREDIV1 configuration */
#define  RCC_CFGR2_PREDIV1                   ((uint32_t)0x0000000F)        /*!< PREDIV1[3:0] bits */
#define  RCC_CFGR2_PREDIV1_0                 ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR2_PREDIV1_1                 ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  RCC_CFGR2_PREDIV1_2                 ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  RCC_CFGR2_PREDIV1_3                 ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  RCC_CFGR2_PREDIV1_DIV1              ((uint32_t)0x00000000)        /*!< PREDIV1 input clock not divided */
#define  RCC_CFGR2_PREDIV1_DIV2              ((uint32_t)0x00000001)        /*!< PREDIV1 input clock divided by 2 */
#define  RCC_CFGR2_PREDIV1_DIV3              ((uint32_t)0x00000002)        /*!< PREDIV1 input clock divided by 3 */
#define  RCC_CFGR2_PREDIV1_DIV4              ((uint32_t)0x00000003)        /*!< PREDIV1 input clock divided by 4 */
#define  RCC_CFGR2_PREDIV1_DIV5              ((uint32_t)0x00000004)        /*!< PREDIV1 input clock divided by 5 */
#define  RCC_CFGR2_PREDIV1_DIV6              ((uint32_t)0x00000005)        /*!< PREDIV1 input clock divided by 6 */
#define  RCC_CFGR2_PREDIV1_DIV7              ((uint32_t)0x00000006)        /*!< PREDIV1 input clock divided by 7 */
#define  RCC_CFGR2_PREDIV1_DIV8              ((uint32_t)0x00000007)        /*!< PREDIV1 input clock divided by 8 */
#define  RCC_CFGR2_PREDIV1_DIV9              ((uint32_t)0x00000008)        /*!< PREDIV1 input clock divided by 9 */
#define  RCC_CFGR2_PREDIV1_DIV10             ((uint32_t)0x00000009)        /*!< PREDIV1 input clock divided by 10 */
#define  RCC_CFGR2_PREDIV1_DIV11             ((uint32_t)0x0000000A)        /*!< PREDIV1 input clock divided by 11 */
#define  RCC_CFGR2_PREDIV1_DIV12             ((uint32_t)0x0000000B)        /*!< PREDIV1 input clock divided by 12 */
#define  RCC_CFGR2_PREDIV1_DIV13             ((uint32_t)0x0000000C)        /*!< PREDIV1 input clock divided by 13 */
#define  RCC_CFGR2_PREDIV1_DIV14             ((uint32_t)0x0000000D)        /*!< PREDIV1 input clock divided by 14 */
#define  RCC_CFGR2_PREDIV1_DIV15             ((uint32_t)0x0000000E)        /*!< PREDIV1 input clock divided by 15 */
#define  RCC_CFGR2_PREDIV1_DIV16             ((uint32_t)0x0000000F)        /*!< PREDIV1 input clock divided by 16 */

/*!< ADCPRE12 configuration */
#define  RCC_CFGR2_ADCPRE12                  ((uint32_t)0x000001F0)        /*!< ADCPRE12[8:4] bits */
#define  RCC_CFGR2_ADCPRE12_0                ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  RCC_CFGR2_ADCPRE12_1                ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  RCC_CFGR2_ADCPRE12_2                ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  RCC_CFGR2_ADCPRE12_3                ((uint32_t)0x00000080)        /*!< Bit 3 */
#define  RCC_CFGR2_ADCPRE12_4                ((uint32_t)0x00000100)        /*!< Bit 4 */

#define  RCC_CFGR2_ADCPRE12_NO               ((uint32_t)0x00000000)        /*!< ADC12 clock disabled, ADC12 can use AHB clock */
#define  RCC_CFGR2_ADCPRE12_DIV1             ((uint32_t)0x00000100)        /*!< ADC12 PLL clock divided by 1 */
#define  RCC_CFGR2_ADCPRE12_DIV2             ((uint32_t)0x00000110)        /*!< ADC12 PLL clock divided by 2 */
#define  RCC_CFGR2_ADCPRE12_DIV4             ((uint32_t)0x00000120)        /*!< ADC12 PLL clock divided by 4 */
#define  RCC_CFGR2_ADCPRE12_DIV6             ((uint32_t)0x00000130)        /*!< ADC12 PLL clock divided by 6 */
#define  RCC_CFGR2_ADCPRE12_DIV8             ((uint32_t)0x00000140)        /*!< ADC12 PLL clock divided by 8 */
#define  RCC_CFGR2_ADCPRE12_DIV10            ((uint32_t)0x00000150)        /*!< ADC12 PLL clock divided by 10 */
#define  RCC_CFGR2_ADCPRE12_DIV12            ((uint32_t)0x00000160)        /*!< ADC12 PLL clock divided by 12 */
#define  RCC_CFGR2_ADCPRE12_DIV16            ((uint32_t)0x00000170)        /*!< ADC12 PLL clock divided by 16 */
#define  RCC_CFGR2_ADCPRE12_DIV32            ((uint32_t)0x00000180)        /*!< ADC12 PLL clock divided by 32 */
#define  RCC_CFGR2_ADCPRE12_DIV64            ((uint32_t)0x00000190)        /*!< ADC12 PLL clock divided by 64 */
#define  RCC_CFGR2_ADCPRE12_DIV128           ((uint32_t)0x000001A0)        /*!< ADC12 PLL clock divided by 128 */
#define  RCC_CFGR2_ADCPRE12_DIV256           ((uint32_t)0x000001B0)        /*!< ADC12 PLL clock divided by 256 */

/*!< ADCPRE34 configuration */
#define  RCC_CFGR2_ADCPRE34                  ((uint32_t)0x00003E00)        /*!< ADCPRE34[13:5] bits */
#define  RCC_CFGR2_ADCPRE34_0                ((uint32_t)0x00000200)        /*!< Bit 0 */
#define  RCC_CFGR2_ADCPRE34_1                ((uint32_t)0x00000400)        /*!< Bit 1 */
#define  RCC_CFGR2_ADCPRE34_2                ((uint32_t)0x00000800)        /*!< Bit 2 */
#define  RCC_CFGR2_ADCPRE34_3                ((uint32_t)0x00001000)        /*!< Bit 3 */
#define  RCC_CFGR2_ADCPRE34_4                ((uint32_t)0x00002000)        /*!< Bit 4 */

#define  RCC_CFGR2_ADCPRE34_NO               ((uint32_t)0x00000000)        /*!< ADC34 clock disabled, ADC34 can use AHB clock */
#define  RCC_CFGR2_ADCPRE34_DIV1             ((uint32_t)0x00002000)        /*!< ADC34 PLL clock divided by 1 */
#define  RCC_CFGR2_ADCPRE34_DIV2             ((uint32_t)0x00002200)        /*!< ADC34 PLL clock divided by 2 */
#define  RCC_CFGR2_ADCPRE34_DIV4             ((uint32_t)0x00002400)        /*!< ADC34 PLL clock divided by 4 */
#define  RCC_CFGR2_ADCPRE34_DIV6             ((uint32_t)0x00002600)        /*!< ADC34 PLL clock divided by 6 */
#define  RCC_CFGR2_ADCPRE34_DIV8             ((uint32_t)0x00002800)        /*!< ADC34 PLL clock divided by 8 */
#define  RCC_CFGR2_ADCPRE34_DIV10            ((uint32_t)0x00002A00)        /*!< ADC34 PLL clock divided by 10 */
#define  RCC_CFGR2_ADCPRE34_DIV12            ((uint32_t)0x00002C00)        /*!< ADC34 PLL clock divided by 12 */
#define  RCC_CFGR2_ADCPRE34_DIV16            ((uint32_t)0x00002E00)        /*!< ADC34 PLL clock divided by 16 */
#define  RCC_CFGR2_ADCPRE34_DIV32            ((uint32_t)0x00003000)        /*!< ADC34 PLL clock divided by 32 */
#define  RCC_CFGR2_ADCPRE34_DIV64            ((uint32_t)0x00003200)        /*!< ADC34 PLL clock divided by 64 */
#define  RCC_CFGR2_ADCPRE34_DIV128           ((uint32_t)0x00003400)        /*!< ADC34 PLL clock divided by 128 */
#define  RCC_CFGR2_ADCPRE34_DIV256           ((uint32_t)0x00003600)        /*!< ADC34 PLL clock divided by 256 */

/*******************  Bit definition for RCC_CFGR3 register  ******************/
#define  RCC_CFGR3_USART1SW                  ((uint32_t)0x00000003)        /*!< USART1SW[1:0] bits */
#define  RCC_CFGR3_USART1SW_0                ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR3_USART1SW_1                ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  RCC_CFGR3_I2CSW                     ((uint32_t)0x00000070)        /*!< I2CSW bits */
#define  RCC_CFGR3_I2C1SW                    ((uint32_t)0x00000010)        /*!< I2C1SW bits */ 
#define  RCC_CFGR3_I2C2SW                    ((uint32_t)0x00000020)        /*!< I2C2SW bits */
#define  RCC_CFGR3_I2C3SW                    ((uint32_t)0x00000040)        /*!< I2C3SW bits */

#define  RCC_CFGR3_TIMSW                     ((uint32_t)0x00002F00)        /*!< TIMSW bits */
#define  RCC_CFGR3_TIM1SW                    ((uint32_t)0x00000100)        /*!< TIM1SW bits */ 
#define  RCC_CFGR3_TIM8SW                    ((uint32_t)0x00000200)        /*!< TIM8SW bits */
#define  RCC_CFGR3_TIM15SW                   ((uint32_t)0x00000400)        /*!< TIM15SW bits */
#define  RCC_CFGR3_TIM16SW                   ((uint32_t)0x00000800)        /*!< TIM16SW bits */
#define  RCC_CFGR3_TIM17SW                   ((uint32_t)0x00002000)        /*!< TIM17SW bits */

#define  RCC_CFGR3_HRTIM1SW                  ((uint32_t)0x00001000)        /*!< HRTIM1SW bits */

#define  RCC_CFGR3_USART2SW                  ((uint32_t)0x00030000)        /*!< USART2SW[1:0] bits */
#define  RCC_CFGR3_USART2SW_0                ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  RCC_CFGR3_USART2SW_1                ((uint32_t)0x00020000)        /*!< Bit 1 */

#define  RCC_CFGR3_USART3SW                  ((uint32_t)0x000C0000)        /*!< USART3SW[1:0] bits */
#define  RCC_CFGR3_USART3SW_0                ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  RCC_CFGR3_USART3SW_1                ((uint32_t)0x00080000)        /*!< Bit 1 */

#define  RCC_CFGR3_UART4SW                   ((uint32_t)0x00300000)        /*!< UART4SW[1:0] bits */
#define  RCC_CFGR3_UART4SW_0                 ((uint32_t)0x00100000)        /*!< Bit 0 */
#define  RCC_CFGR3_UART4SW_1                 ((uint32_t)0x00200000)        /*!< Bit 1 */

#define  RCC_CFGR3_UART5SW                   ((uint32_t)0x00C00000)        /*!< UART5SW[1:0] bits */
#define  RCC_CFGR3_UART5SW_0                 ((uint32_t)0x00400000)        /*!< Bit 0 */
#define  RCC_CFGR3_UART5SW_1                 ((uint32_t)0x00800000)        /*!< Bit 1 */

/******************************************************************************/
/*                                                                            */
/*                           Real-Time Clock (RTC)                            */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RTC_TR register  *******************/
#define RTC_TR_PM                            ((uint32_t)0x00400000)
#define RTC_TR_HT                            ((uint32_t)0x00300000)
#define RTC_TR_HT_0                          ((uint32_t)0x00100000)
#define RTC_TR_HT_1                          ((uint32_t)0x00200000)
#define RTC_TR_HU                            ((uint32_t)0x000F0000)
#define RTC_TR_HU_0                          ((uint32_t)0x00010000)
#define RTC_TR_HU_1                          ((uint32_t)0x00020000)
#define RTC_TR_HU_2                          ((uint32_t)0x00040000)
#define RTC_TR_HU_3                          ((uint32_t)0x00080000)
#define RTC_TR_MNT                           ((uint32_t)0x00007000)
#define RTC_TR_MNT_0                         ((uint32_t)0x00001000)
#define RTC_TR_MNT_1                         ((uint32_t)0x00002000)
#define RTC_TR_MNT_2                         ((uint32_t)0x00004000)
#define RTC_TR_MNU                           ((uint32_t)0x00000F00)
#define RTC_TR_MNU_0                         ((uint32_t)0x00000100)
#define RTC_TR_MNU_1                         ((uint32_t)0x00000200)
#define RTC_TR_MNU_2                         ((uint32_t)0x00000400)
#define RTC_TR_MNU_3                         ((uint32_t)0x00000800)
#define RTC_TR_ST                            ((uint32_t)0x00000070)
#define RTC_TR_ST_0                          ((uint32_t)0x00000010)
#define RTC_TR_ST_1                          ((uint32_t)0x00000020)
#define RTC_TR_ST_2                          ((uint32_t)0x00000040)
#define RTC_TR_SU                            ((uint32_t)0x0000000F)
#define RTC_TR_SU_0                          ((uint32_t)0x00000001)
#define RTC_TR_SU_1                          ((uint32_t)0x00000002)
#define RTC_TR_SU_2                          ((uint32_t)0x00000004)
#define RTC_TR_SU_3                          ((uint32_t)0x00000008)

/********************  Bits definition for RTC_DR register  *******************/
#define RTC_DR_YT                            ((uint32_t)0x00F00000)
#define RTC_DR_YT_0                          ((uint32_t)0x00100000)
#define RTC_DR_YT_1                          ((uint32_t)0x00200000)
#define RTC_DR_YT_2                          ((uint32_t)0x00400000)
#define RTC_DR_YT_3                          ((uint32_t)0x00800000)
#define RTC_DR_YU                            ((uint32_t)0x000F0000)
#define RTC_DR_YU_0                          ((uint32_t)0x00010000)
#define RTC_DR_YU_1                          ((uint32_t)0x00020000)
#define RTC_DR_YU_2                          ((uint32_t)0x00040000)
#define RTC_DR_YU_3                          ((uint32_t)0x00080000)
#define RTC_DR_WDU                           ((uint32_t)0x0000E000)
#define RTC_DR_WDU_0                         ((uint32_t)0x00002000)
#define RTC_DR_WDU_1                         ((uint32_t)0x00004000)
#define RTC_DR_WDU_2                         ((uint32_t)0x00008000)
#define RTC_DR_MT                            ((uint32_t)0x00001000)
#define RTC_DR_MU                            ((uint32_t)0x00000F00)
#define RTC_DR_MU_0                          ((uint32_t)0x00000100)
#define RTC_DR_MU_1                          ((uint32_t)0x00000200)
#define RTC_DR_MU_2                          ((uint32_t)0x00000400)
#define RTC_DR_MU_3                          ((uint32_t)0x00000800)
#define RTC_DR_DT                            ((uint32_t)0x00000030)
#define RTC_DR_DT_0                          ((uint32_t)0x00000010)
#define RTC_DR_DT_1                          ((uint32_t)0x00000020)
#define RTC_DR_DU                            ((uint32_t)0x0000000F)
#define RTC_DR_DU_0                          ((uint32_t)0x00000001)
#define RTC_DR_DU_1                          ((uint32_t)0x00000002)
#define RTC_DR_DU_2                          ((uint32_t)0x00000004)
#define RTC_DR_DU_3                          ((uint32_t)0x00000008)

/********************  Bits definition for RTC_CR register  *******************/
#define RTC_CR_COE                           ((uint32_t)0x00800000)
#define RTC_CR_OSEL                          ((uint32_t)0x00600000)
#define RTC_CR_OSEL_0                        ((uint32_t)0x00200000)
#define RTC_CR_OSEL_1                        ((uint32_t)0x00400000)
#define RTC_CR_POL                           ((uint32_t)0x00100000)
#define RTC_CR_COSEL                         ((uint32_t)0x00080000)
#define RTC_CR_BCK                           ((uint32_t)0x00040000)
#define RTC_CR_SUB1H                         ((uint32_t)0x00020000)
#define RTC_CR_ADD1H                         ((uint32_t)0x00010000)
#define RTC_CR_TSIE                          ((uint32_t)0x00008000)
#define RTC_CR_WUTIE                         ((uint32_t)0x00004000)
#define RTC_CR_ALRBIE                        ((uint32_t)0x00002000)
#define RTC_CR_ALRAIE                        ((uint32_t)0x00001000)
#define RTC_CR_TSE                           ((uint32_t)0x00000800)
#define RTC_CR_WUTE                          ((uint32_t)0x00000400)
#define RTC_CR_ALRBE                         ((uint32_t)0x00000200)
#define RTC_CR_ALRAE                         ((uint32_t)0x00000100)
#define RTC_CR_FMT                           ((uint32_t)0x00000040)
#define RTC_CR_BYPSHAD                       ((uint32_t)0x00000020)
#define RTC_CR_REFCKON                       ((uint32_t)0x00000010)
#define RTC_CR_TSEDGE                        ((uint32_t)0x00000008)
#define RTC_CR_WUCKSEL                       ((uint32_t)0x00000007)
#define RTC_CR_WUCKSEL_0                     ((uint32_t)0x00000001)
#define RTC_CR_WUCKSEL_1                     ((uint32_t)0x00000002)
#define RTC_CR_WUCKSEL_2                     ((uint32_t)0x00000004)

/********************  Bits definition for RTC_ISR register  ******************/
#define RTC_ISR_RECALPF                      ((uint32_t)0x00010000)
#define RTC_ISR_TAMP3F                       ((uint32_t)0x00008000)
#define RTC_ISR_TAMP2F                       ((uint32_t)0x00004000)
#define RTC_ISR_TAMP1F                       ((uint32_t)0x00002000)
#define RTC_ISR_TSOVF                        ((uint32_t)0x00001000)
#define RTC_ISR_TSF                          ((uint32_t)0x00000800)
#define RTC_ISR_WUTF                         ((uint32_t)0x00000400)
#define RTC_ISR_ALRBF                        ((uint32_t)0x00000200)
#define RTC_ISR_ALRAF                        ((uint32_t)0x00000100)
#define RTC_ISR_INIT                         ((uint32_t)0x00000080)
#define RTC_ISR_INITF                        ((uint32_t)0x00000040)
#define RTC_ISR_RSF                          ((uint32_t)0x00000020)
#define RTC_ISR_INITS                        ((uint32_t)0x00000010)
#define RTC_ISR_SHPF                         ((uint32_t)0x00000008)
#define RTC_ISR_WUTWF                        ((uint32_t)0x00000004)
#define RTC_ISR_ALRBWF                       ((uint32_t)0x00000002)
#define RTC_ISR_ALRAWF                       ((uint32_t)0x00000001)

/********************  Bits definition for RTC_PRER register  *****************/
#define RTC_PRER_PREDIV_A                    ((uint32_t)0x007F0000)
#define RTC_PRER_PREDIV_S                    ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_WUTR register  *****************/
#define RTC_WUTR_WUT                         ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_ALRMAR register  ***************/
#define RTC_ALRMAR_MSK4                      ((uint32_t)0x80000000)
#define RTC_ALRMAR_WDSEL                     ((uint32_t)0x40000000)
#define RTC_ALRMAR_DT                        ((uint32_t)0x30000000)
#define RTC_ALRMAR_DT_0                      ((uint32_t)0x10000000)
#define RTC_ALRMAR_DT_1                      ((uint32_t)0x20000000)
#define RTC_ALRMAR_DU                        ((uint32_t)0x0F000000)
#define RTC_ALRMAR_DU_0                      ((uint32_t)0x01000000)
#define RTC_ALRMAR_DU_1                      ((uint32_t)0x02000000)
#define RTC_ALRMAR_DU_2                      ((uint32_t)0x04000000)
#define RTC_ALRMAR_DU_3                      ((uint32_t)0x08000000)
#define RTC_ALRMAR_MSK3                      ((uint32_t)0x00800000)
#define RTC_ALRMAR_PM                        ((uint32_t)0x00400000)
#define RTC_ALRMAR_HT                        ((uint32_t)0x00300000)
#define RTC_ALRMAR_HT_0                      ((uint32_t)0x00100000)
#define RTC_ALRMAR_HT_1                      ((uint32_t)0x00200000)
#define RTC_ALRMAR_HU                        ((uint32_t)0x000F0000)
#define RTC_ALRMAR_HU_0                      ((uint32_t)0x00010000)
#define RTC_ALRMAR_HU_1                      ((uint32_t)0x00020000)
#define RTC_ALRMAR_HU_2                      ((uint32_t)0x00040000)
#define RTC_ALRMAR_HU_3                      ((uint32_t)0x00080000)
#define RTC_ALRMAR_MSK2                      ((uint32_t)0x00008000)
#define RTC_ALRMAR_MNT                       ((uint32_t)0x00007000)
#define RTC_ALRMAR_MNT_0                     ((uint32_t)0x00001000)
#define RTC_ALRMAR_MNT_1                     ((uint32_t)0x00002000)
#define RTC_ALRMAR_MNT_2                     ((uint32_t)0x00004000)
#define RTC_ALRMAR_MNU                       ((uint32_t)0x00000F00)
#define RTC_ALRMAR_MNU_0                     ((uint32_t)0x00000100)
#define RTC_ALRMAR_MNU_1                     ((uint32_t)0x00000200)
#define RTC_ALRMAR_MNU_2                     ((uint32_t)0x00000400)
#define RTC_ALRMAR_MNU_3                     ((uint32_t)0x00000800)
#define RTC_ALRMAR_MSK1                      ((uint32_t)0x00000080)
#define RTC_ALRMAR_ST                        ((uint32_t)0x00000070)
#define RTC_ALRMAR_ST_0                      ((uint32_t)0x00000010)
#define RTC_ALRMAR_ST_1                      ((uint32_t)0x00000020)
#define RTC_ALRMAR_ST_2                      ((uint32_t)0x00000040)
#define RTC_ALRMAR_SU                        ((uint32_t)0x0000000F)
#define RTC_ALRMAR_SU_0                      ((uint32_t)0x00000001)
#define RTC_ALRMAR_SU_1                      ((uint32_t)0x00000002)
#define RTC_ALRMAR_SU_2                      ((uint32_t)0x00000004)
#define RTC_ALRMAR_SU_3                      ((uint32_t)0x00000008)

/********************  Bits definition for RTC_ALRMBR register  ***************/
#define RTC_ALRMBR_MSK4                      ((uint32_t)0x80000000)
#define RTC_ALRMBR_WDSEL                     ((uint32_t)0x40000000)
#define RTC_ALRMBR_DT                        ((uint32_t)0x30000000)
#define RTC_ALRMBR_DT_0                      ((uint32_t)0x10000000)
#define RTC_ALRMBR_DT_1                      ((uint32_t)0x20000000)
#define RTC_ALRMBR_DU                        ((uint32_t)0x0F000000)
#define RTC_ALRMBR_DU_0                      ((uint32_t)0x01000000)
#define RTC_ALRMBR_DU_1                      ((uint32_t)0x02000000)
#define RTC_ALRMBR_DU_2                      ((uint32_t)0x04000000)
#define RTC_ALRMBR_DU_3                      ((uint32_t)0x08000000)
#define RTC_ALRMBR_MSK3                      ((uint32_t)0x00800000)
#define RTC_ALRMBR_PM                        ((uint32_t)0x00400000)
#define RTC_ALRMBR_HT                        ((uint32_t)0x00300000)
#define RTC_ALRMBR_HT_0                      ((uint32_t)0x00100000)
#define RTC_ALRMBR_HT_1                      ((uint32_t)0x00200000)
#define RTC_ALRMBR_HU                        ((uint32_t)0x000F0000)
#define RTC_ALRMBR_HU_0                      ((uint32_t)0x00010000)
#define RTC_ALRMBR_HU_1                      ((uint32_t)0x00020000)
#define RTC_ALRMBR_HU_2                      ((uint32_t)0x00040000)
#define RTC_ALRMBR_HU_3                      ((uint32_t)0x00080000)
#define RTC_ALRMBR_MSK2                      ((uint32_t)0x00008000)
#define RTC_ALRMBR_MNT                       ((uint32_t)0x00007000)
#define RTC_ALRMBR_MNT_0                     ((uint32_t)0x00001000)
#define RTC_ALRMBR_MNT_1                     ((uint32_t)0x00002000)
#define RTC_ALRMBR_MNT_2                     ((uint32_t)0x00004000)
#define RTC_ALRMBR_MNU                       ((uint32_t)0x00000F00)
#define RTC_ALRMBR_MNU_0                     ((uint32_t)0x00000100)
#define RTC_ALRMBR_MNU_1                     ((uint32_t)0x00000200)
#define RTC_ALRMBR_MNU_2                     ((uint32_t)0x00000400)
#define RTC_ALRMBR_MNU_3                     ((uint32_t)0x00000800)
#define RTC_ALRMBR_MSK1                      ((uint32_t)0x00000080)
#define RTC_ALRMBR_ST                        ((uint32_t)0x00000070)
#define RTC_ALRMBR_ST_0                      ((uint32_t)0x00000010)
#define RTC_ALRMBR_ST_1                      ((uint32_t)0x00000020)
#define RTC_ALRMBR_ST_2                      ((uint32_t)0x00000040)
#define RTC_ALRMBR_SU                        ((uint32_t)0x0000000F)
#define RTC_ALRMBR_SU_0                      ((uint32_t)0x00000001)
#define RTC_ALRMBR_SU_1                      ((uint32_t)0x00000002)
#define RTC_ALRMBR_SU_2                      ((uint32_t)0x00000004)
#define RTC_ALRMBR_SU_3                      ((uint32_t)0x00000008)

/********************  Bits definition for RTC_WPR register  ******************/
#define RTC_WPR_KEY                          ((uint32_t)0x000000FF)

/********************  Bits definition for RTC_SSR register  ******************/
#define RTC_SSR_SS                           ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_SHIFTR register  ***************/
#define RTC_SHIFTR_SUBFS                     ((uint32_t)0x00007FFF)
#define RTC_SHIFTR_ADD1S                     ((uint32_t)0x80000000)

/********************  Bits definition for RTC_TSTR register  *****************/
#define RTC_TSTR_PM                          ((uint32_t)0x00400000)
#define RTC_TSTR_HT                          ((uint32_t)0x00300000)
#define RTC_TSTR_HT_0                        ((uint32_t)0x00100000)
#define RTC_TSTR_HT_1                        ((uint32_t)0x00200000)
#define RTC_TSTR_HU                          ((uint32_t)0x000F0000)
#define RTC_TSTR_HU_0                        ((uint32_t)0x00010000)
#define RTC_TSTR_HU_1                        ((uint32_t)0x00020000)
#define RTC_TSTR_HU_2                        ((uint32_t)0x00040000)
#define RTC_TSTR_HU_3                        ((uint32_t)0x00080000)
#define RTC_TSTR_MNT                         ((uint32_t)0x00007000)
#define RTC_TSTR_MNT_0                       ((uint32_t)0x00001000)
#define RTC_TSTR_MNT_1                       ((uint32_t)0x00002000)
#define RTC_TSTR_MNT_2                       ((uint32_t)0x00004000)
#define RTC_TSTR_MNU                         ((uint32_t)0x00000F00)
#define RTC_TSTR_MNU_0                       ((uint32_t)0x00000100)
#define RTC_TSTR_MNU_1                       ((uint32_t)0x00000200)
#define RTC_TSTR_MNU_2                       ((uint32_t)0x00000400)
#define RTC_TSTR_MNU_3                       ((uint32_t)0x00000800)
#define RTC_TSTR_ST                          ((uint32_t)0x00000070)
#define RTC_TSTR_ST_0                        ((uint32_t)0x00000010)
#define RTC_TSTR_ST_1                        ((uint32_t)0x00000020)
#define RTC_TSTR_ST_2                        ((uint32_t)0x00000040)
#define RTC_TSTR_SU                          ((uint32_t)0x0000000F)
#define RTC_TSTR_SU_0                        ((uint32_t)0x00000001)
#define RTC_TSTR_SU_1                        ((uint32_t)0x00000002)
#define RTC_TSTR_SU_2                        ((uint32_t)0x00000004)
#define RTC_TSTR_SU_3                        ((uint32_t)0x00000008)

/********************  Bits definition for RTC_TSDR register  *****************/
#define RTC_TSDR_WDU                         ((uint32_t)0x0000E000)
#define RTC_TSDR_WDU_0                       ((uint32_t)0x00002000)
#define RTC_TSDR_WDU_1                       ((uint32_t)0x00004000)
#define RTC_TSDR_WDU_2                       ((uint32_t)0x00008000)
#define RTC_TSDR_MT                          ((uint32_t)0x00001000)
#define RTC_TSDR_MU                          ((uint32_t)0x00000F00)
#define RTC_TSDR_MU_0                        ((uint32_t)0x00000100)
#define RTC_TSDR_MU_1                        ((uint32_t)0x00000200)
#define RTC_TSDR_MU_2                        ((uint32_t)0x00000400)
#define RTC_TSDR_MU_3                        ((uint32_t)0x00000800)
#define RTC_TSDR_DT                          ((uint32_t)0x00000030)
#define RTC_TSDR_DT_0                        ((uint32_t)0x00000010)
#define RTC_TSDR_DT_1                        ((uint32_t)0x00000020)
#define RTC_TSDR_DU                          ((uint32_t)0x0000000F)
#define RTC_TSDR_DU_0                        ((uint32_t)0x00000001)
#define RTC_TSDR_DU_1                        ((uint32_t)0x00000002)
#define RTC_TSDR_DU_2                        ((uint32_t)0x00000004)
#define RTC_TSDR_DU_3                        ((uint32_t)0x00000008)

/********************  Bits definition for RTC_TSSSR register  ****************/
#define RTC_TSSSR_SS                         ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_CAL register  *****************/
#define RTC_CALR_CALP                        ((uint32_t)0x00008000)
#define RTC_CALR_CALW8                       ((uint32_t)0x00004000)
#define RTC_CALR_CALW16                      ((uint32_t)0x00002000)
#define RTC_CALR_CALM                        ((uint32_t)0x000001FF)
#define RTC_CALR_CALM_0                      ((uint32_t)0x00000001)
#define RTC_CALR_CALM_1                      ((uint32_t)0x00000002)
#define RTC_CALR_CALM_2                      ((uint32_t)0x00000004)
#define RTC_CALR_CALM_3                      ((uint32_t)0x00000008)
#define RTC_CALR_CALM_4                      ((uint32_t)0x00000010)
#define RTC_CALR_CALM_5                      ((uint32_t)0x00000020)
#define RTC_CALR_CALM_6                      ((uint32_t)0x00000040)
#define RTC_CALR_CALM_7                      ((uint32_t)0x00000080)
#define RTC_CALR_CALM_8                      ((uint32_t)0x00000100)

/********************  Bits definition for RTC_TAFCR register  ****************/
#define RTC_TAFCR_ALARMOUTTYPE               ((uint32_t)0x00040000)
#define RTC_TAFCR_TAMPPUDIS                  ((uint32_t)0x00008000)
#define RTC_TAFCR_TAMPPRCH                   ((uint32_t)0x00006000)
#define RTC_TAFCR_TAMPPRCH_0                 ((uint32_t)0x00002000)
#define RTC_TAFCR_TAMPPRCH_1                 ((uint32_t)0x00004000)
#define RTC_TAFCR_TAMPFLT                    ((uint32_t)0x00001800)
#define RTC_TAFCR_TAMPFLT_0                  ((uint32_t)0x00000800)
#define RTC_TAFCR_TAMPFLT_1                  ((uint32_t)0x00001000)
#define RTC_TAFCR_TAMPFREQ                   ((uint32_t)0x00000700)
#define RTC_TAFCR_TAMPFREQ_0                 ((uint32_t)0x00000100)
#define RTC_TAFCR_TAMPFREQ_1                 ((uint32_t)0x00000200)
#define RTC_TAFCR_TAMPFREQ_2                 ((uint32_t)0x00000400)
#define RTC_TAFCR_TAMPTS                     ((uint32_t)0x00000080)
#define RTC_TAFCR_TAMP3TRG                   ((uint32_t)0x00000040)
#define RTC_TAFCR_TAMP3E                     ((uint32_t)0x00000020)
#define RTC_TAFCR_TAMP2TRG                   ((uint32_t)0x00000010)
#define RTC_TAFCR_TAMP2E                     ((uint32_t)0x00000008)
#define RTC_TAFCR_TAMPIE                     ((uint32_t)0x00000004)
#define RTC_TAFCR_TAMP1TRG                   ((uint32_t)0x00000002)
#define RTC_TAFCR_TAMP1E                     ((uint32_t)0x00000001)

/********************  Bits definition for RTC_ALRMASSR register  *************/
#define RTC_ALRMASSR_MASKSS                  ((uint32_t)0x0F000000)
#define RTC_ALRMASSR_MASKSS_0                ((uint32_t)0x01000000)
#define RTC_ALRMASSR_MASKSS_1                ((uint32_t)0x02000000)
#define RTC_ALRMASSR_MASKSS_2                ((uint32_t)0x04000000)
#define RTC_ALRMASSR_MASKSS_3                ((uint32_t)0x08000000)
#define RTC_ALRMASSR_SS                      ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_ALRMBSSR register  *************/
#define RTC_ALRMBSSR_MASKSS                  ((uint32_t)0x0F000000)
#define RTC_ALRMBSSR_MASKSS_0                ((uint32_t)0x01000000)
#define RTC_ALRMBSSR_MASKSS_1                ((uint32_t)0x02000000)
#define RTC_ALRMBSSR_MASKSS_2                ((uint32_t)0x04000000)
#define RTC_ALRMBSSR_MASKSS_3                ((uint32_t)0x08000000)
#define RTC_ALRMBSSR_SS                      ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_BKP0R register  ****************/
#define RTC_BKP0R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP1R register  ****************/
#define RTC_BKP1R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP2R register  ****************/
#define RTC_BKP2R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP3R register  ****************/
#define RTC_BKP3R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP4R register  ****************/
#define RTC_BKP4R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP5R register  ****************/
#define RTC_BKP5R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP6R register  ****************/
#define RTC_BKP6R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP7R register  ****************/
#define RTC_BKP7R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP8R register  ****************/
#define RTC_BKP8R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP9R register  ****************/
#define RTC_BKP9R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP10R register  ***************/
#define RTC_BKP10R                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP11R register  ***************/
#define RTC_BKP11R                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP12R register  ***************/
#define RTC_BKP12R                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP13R register  ***************/
#define RTC_BKP13R                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP14R register  ***************/
#define RTC_BKP14R                           ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP15R register  ***************/
#define RTC_BKP15R                           ((uint32_t)0xFFFFFFFF)

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface (SPI)                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SPI_CR1 register  ********************/
#define  SPI_CR1_CPHA                        ((uint16_t)0x0001)            /*!< Clock Phase */
#define  SPI_CR1_CPOL                        ((uint16_t)0x0002)            /*!< Clock Polarity */
#define  SPI_CR1_MSTR                        ((uint16_t)0x0004)            /*!< Master Selection */

#define  SPI_CR1_BR                          ((uint16_t)0x0038)            /*!< BR[2:0] bits (Baud Rate Control) */
#define  SPI_CR1_BR_0                        ((uint16_t)0x0008)            /*!< Bit 0 */
#define  SPI_CR1_BR_1                        ((uint16_t)0x0010)            /*!< Bit 1 */
#define  SPI_CR1_BR_2                        ((uint16_t)0x0020)            /*!< Bit 2 */

#define  SPI_CR1_SPE                         ((uint16_t)0x0040)            /*!< SPI Enable */
#define  SPI_CR1_LSBFIRST                    ((uint16_t)0x0080)            /*!< Frame Format */
#define  SPI_CR1_SSI                         ((uint16_t)0x0100)            /*!< Internal slave select */
#define  SPI_CR1_SSM                         ((uint16_t)0x0200)            /*!< Software slave management */
#define  SPI_CR1_RXONLY                      ((uint16_t)0x0400)            /*!< Receive only */
#define  SPI_CR1_CRCL                        ((uint16_t)0x0800)            /*!< CRC Length */
#define  SPI_CR1_CRCNEXT                     ((uint16_t)0x1000)            /*!< Transmit CRC next */
#define  SPI_CR1_CRCEN                       ((uint16_t)0x2000)            /*!< Hardware CRC calculation enable */
#define  SPI_CR1_BIDIOE                      ((uint16_t)0x4000)            /*!< Output enable in bidirectional mode */
#define  SPI_CR1_BIDIMODE                    ((uint16_t)0x8000)            /*!< Bidirectional data mode enable */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define  SPI_CR2_RXDMAEN                     ((uint16_t)0x0001)            /*!< Rx Buffer DMA Enable */
#define  SPI_CR2_TXDMAEN                     ((uint16_t)0x0002)            /*!< Tx Buffer DMA Enable */
#define  SPI_CR2_SSOE                        ((uint16_t)0x0004)            /*!< SS Output Enable */
#define  SPI_CR2_NSSP                        ((uint16_t)0x0008)            /*!< NSS pulse management Enable */
#define  SPI_CR2_FRF                         ((uint16_t)0x0010)            /*!< Frame Format Enable */
#define  SPI_CR2_ERRIE                       ((uint16_t)0x0020)            /*!< Error Interrupt Enable */
#define  SPI_CR2_RXNEIE                      ((uint16_t)0x0040)            /*!< RX buffer Not Empty Interrupt Enable */
#define  SPI_CR2_TXEIE                       ((uint16_t)0x0080)            /*!< Tx buffer Empty Interrupt Enable */

#define  SPI_CR2_DS                          ((uint16_t)0x0F00)            /*!< DS[3:0] Data Size */
#define  SPI_CR2_DS_0                        ((uint16_t)0x0100)            /*!< Bit 0 */
#define  SPI_CR2_DS_1                        ((uint16_t)0x0200)            /*!< Bit 1 */
#define  SPI_CR2_DS_2                        ((uint16_t)0x0400)            /*!< Bit 2 */
#define  SPI_CR2_DS_3                        ((uint16_t)0x0800)            /*!< Bit 3 */

#define  SPI_CR2_FRXTH                       ((uint16_t)0x1000)            /*!< FIFO reception Threshold */
#define  SPI_CR2_LDMARX                      ((uint16_t)0x2000)            /*!< Last DMA transfer for reception */
#define  SPI_CR2_LDMATX                      ((uint16_t)0x4000)            /*!< Last DMA transfer for transmission */

/********************  Bit definition for SPI_SR register  ********************/
#define  SPI_SR_RXNE                         ((uint16_t)0x0001)            /*!< Receive buffer Not Empty */
#define  SPI_SR_TXE                          ((uint16_t)0x0002)            /*!< Transmit buffer Empty */
#define  SPI_SR_CRCERR                       ((uint16_t)0x0010)            /*!< CRC Error flag */
#define  SPI_SR_MODF                         ((uint16_t)0x0020)            /*!< Mode fault */
#define  SPI_SR_OVR                          ((uint16_t)0x0040)            /*!< Overrun flag */
#define  SPI_SR_BSY                          ((uint16_t)0x0080)            /*!< Busy flag */
#define  SPI_SR_FRE                          ((uint16_t)0x0100)            /*!< TI frame format error */
#define  SPI_SR_FRLVL                        ((uint16_t)0x0600)            /*!< FIFO Reception Level */
#define  SPI_SR_FRLVL_0                      ((uint16_t)0x0200)            /*!< Bit 0 */
#define  SPI_SR_FRLVL_1                      ((uint16_t)0x0400)            /*!< Bit 1 */
#define  SPI_SR_FTLVL                        ((uint16_t)0x1800)            /*!< FIFO Transmission Level */
#define  SPI_SR_FTLVL_0                      ((uint16_t)0x0800)            /*!< Bit 0 */
#define  SPI_SR_FTLVL_1                      ((uint16_t)0x1000)            /*!< Bit 1 */  

/********************  Bit definition for SPI_DR register  ********************/
#define  SPI_DR_DR                           ((uint16_t)0xFFFF)            /*!< Data Register */

/*******************  Bit definition for SPI_CRCPR register  ******************/
#define  SPI_CRCPR_CRCPOLY                   ((uint16_t)0xFFFF)            /*!< CRC polynomial register */

/******************  Bit definition for SPI_RXCRCR register  ******************/
#define  SPI_RXCRCR_RXCRC                    ((uint16_t)0xFFFF)            /*!< Rx CRC Register */

/******************  Bit definition for SPI_TXCRCR register  ******************/
#define  SPI_TXCRCR_TXCRC                    ((uint16_t)0xFFFF)            /*!< Tx CRC Register */

/******************  Bit definition for SPI_I2SCFGR register  *****************/
#define  SPI_I2SCFGR_CHLEN                   ((uint16_t)0x0001)            /*!<Channel length (number of bits per audio channel) */

#define  SPI_I2SCFGR_DATLEN                  ((uint16_t)0x0006)            /*!<DATLEN[1:0] bits (Data length to be transferred) */
#define  SPI_I2SCFGR_DATLEN_0                ((uint16_t)0x0002)            /*!<Bit 0 */
#define  SPI_I2SCFGR_DATLEN_1                ((uint16_t)0x0004)            /*!<Bit 1 */

#define  SPI_I2SCFGR_CKPOL                   ((uint16_t)0x0008)            /*!<steady state clock polarity */

#define  SPI_I2SCFGR_I2SSTD                  ((uint16_t)0x0030)            /*!<I2SSTD[1:0] bits (I2S standard selection) */
#define  SPI_I2SCFGR_I2SSTD_0                ((uint16_t)0x0010)            /*!<Bit 0 */
#define  SPI_I2SCFGR_I2SSTD_1                ((uint16_t)0x0020)            /*!<Bit 1 */

#define  SPI_I2SCFGR_PCMSYNC                 ((uint16_t)0x0080)            /*!<PCM frame synchronization */

#define  SPI_I2SCFGR_I2SCFG                  ((uint16_t)0x0300)            /*!<I2SCFG[1:0] bits (I2S configuration mode) */
#define  SPI_I2SCFGR_I2SCFG_0                ((uint16_t)0x0100)            /*!<Bit 0 */
#define  SPI_I2SCFGR_I2SCFG_1                ((uint16_t)0x0200)            /*!<Bit 1 */

#define  SPI_I2SCFGR_I2SE                    ((uint16_t)0x0400)            /*!<I2S Enable */
#define  SPI_I2SCFGR_I2SMOD                  ((uint16_t)0x0800)            /*!<I2S mode selection */

/******************  Bit definition for SPI_I2SPR register  *******************/
#define  SPI_I2SPR_I2SDIV                    ((uint16_t)0x00FF)            /*!<I2S Linear prescaler */
#define  SPI_I2SPR_ODD                       ((uint16_t)0x0100)            /*!<Odd factor for the prescaler */
#define  SPI_I2SPR_MCKOE                     ((uint16_t)0x0200)            /*!<Master Clock Output Enable */

/******************************************************************************/
/*                                                                            */
/*                        System Configuration(SYSCFG)                        */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for SYSCFG_CFGR1 register  *****************/
#define SYSCFG_CFGR1_MEM_MODE               ((uint32_t)0x00000003) /*!< SYSCFG_Memory Remap Config */
#define SYSCFG_CFGR1_MEM_MODE_0             ((uint32_t)0x00000001) /*!< Bit 0 */
#define SYSCFG_CFGR1_MEM_MODE_1             ((uint32_t)0x00000002) /*!< Bit 1 */
#define SYSCFG_CFGR1_USB_IT_RMP             ((uint32_t)0x00000020) /*!< USB interrupt remap */
#define SYSCFG_CFGR1_TIM1_ITR3_RMP          ((uint32_t)0x00000040) /*!< Timer 1 ITR3 selection */
#define SYSCFG_CFGR1_DAC1_TRIG1_RMP         ((uint32_t)0x00000080) /*!< DAC1 Trigger1 remap */
#define SYSCFG_CFGR1_ADC24_DMA_RMP          ((uint32_t)0x00000100) /*!< ADC2 and ADC4 DMA remap */
#define SYSCFG_CFGR1_TIM16_DMA_RMP          ((uint32_t)0x00000800) /*!< Timer 16 DMA remap */
#define SYSCFG_CFGR1_TIM17_DMA_RMP          ((uint32_t)0x00001000) /*!< Timer 17 DMA remap */
#define SYSCFG_CFGR1_TIM6DAC1Ch1_DMA_RMP    ((uint32_t)0x00002000) /*!< Timer 6 / DAC1 CH1 DMA remap */
#define SYSCFG_CFGR1_TIM7DAC1Ch2_DMA_RMP    ((uint32_t)0x00004000) /*!< Timer 7 / DAC1 CH2 DMA remap */
#define SYSCFG_CFGR1_DAC2Ch1_DMA_RMP        ((uint32_t)0x00008000) /*!< DAC2 CH1 DMA remap */
#define SYSCFG_CFGR1_I2C_PB6_FMP            ((uint32_t)0x00010000) /*!< I2C PB6 Fast mode plus */
#define SYSCFG_CFGR1_I2C_PB7_FMP            ((uint32_t)0x00020000) /*!< I2C PB7 Fast mode plus */
#define SYSCFG_CFGR1_I2C_PB8_FMP            ((uint32_t)0x00040000) /*!< I2C PB8 Fast mode plus */
#define SYSCFG_CFGR1_I2C_PB9_FMP            ((uint32_t)0x00080000) /*!< I2C PB9 Fast mode plus */
#define SYSCFG_CFGR1_I2C1_FMP               ((uint32_t)0x00100000) /*!< I2C1 Fast mode plus */
#define SYSCFG_CFGR1_I2C2_FMP               ((uint32_t)0x00200000) /*!< I2C2 Fast mode plus */
#define SYSCFG_CFGR1_ENCODER_MODE           ((uint32_t)0x00C00000) /*!< Encoder Mode */
#define SYSCFG_CFGR1_ENCODER_MODE_0         ((uint32_t)0x00400000) /*!< Encoder Mode 0 */
#define SYSCFG_CFGR1_ENCODER_MODE_1         ((uint32_t)0x00800000) /*!< Encoder Mode 1 */
#define SYSCFG_CFGR1_FPU_IE                 ((uint32_t)0xFC000000) /*!< Floating Point Unit Interrupt Enable */
#define SYSCFG_CFGR1_FPU_IE_0               ((uint32_t)0x04000000) /*!< Floating Point Unit Interrupt Enable 0 */
#define SYSCFG_CFGR1_FPU_IE_1               ((uint32_t)0x08000000) /*!< Floating Point Unit Interrupt Enable 1 */
#define SYSCFG_CFGR1_FPU_IE_2               ((uint32_t)0x10000000) /*!< Floating Point Unit Interrupt Enable 2 */
#define SYSCFG_CFGR1_FPU_IE_3               ((uint32_t)0x20000000) /*!< Floating Point Unit Interrupt Enable 3 */
#define SYSCFG_CFGR1_FPU_IE_4               ((uint32_t)0x40000000) /*!< Floating Point Unit Interrupt Enable 4 */
#define SYSCFG_CFGR1_FPU_IE_5               ((uint32_t)0x80000000) /*!< Floating Point Unit Interrupt Enable 5 */
#define SYSCFG_CFGR1_DAC_TRIG_RMP           SYSCFG_CFGR1_DAC1_TRIG1_RMP  /*!< Old define maintained for legacy purpose */
#define SYSCFG_CFGR1_TIM6DAC1               SYSCFG_CFGR1_TIM6DAC1Ch1_DMA_RMP /*!< Old define maintained for legacy purpose */
#define SYSCFG_CFGR1_TIM7DAC2               SYSCFG_CFGR1_TIM7DAC1Ch2_DMA_RMP /*!< Old define maintained for legacy purpose */
/*****************  Bit definition for SYSCFG_RCR register  *******************/
#define SYSCFG_RCR_PAGE0          ((uint32_t)0x00000001) /*!< ICODE SRAM Write protection page 0 */
#define SYSCFG_RCR_PAGE1          ((uint32_t)0x00000002) /*!< ICODE SRAM Write protection page 1 */
#define SYSCFG_RCR_PAGE2          ((uint32_t)0x00000004) /*!< ICODE SRAM Write protection page 2 */
#define SYSCFG_RCR_PAGE3          ((uint32_t)0x00000008) /*!< ICODE SRAM Write protection page 3 */
#define SYSCFG_RCR_PAGE4          ((uint32_t)0x00000010) /*!< ICODE SRAM Write protection page 4 */
#define SYSCFG_RCR_PAGE5          ((uint32_t)0x00000020) /*!< ICODE SRAM Write protection page 5 */
#define SYSCFG_RCR_PAGE6          ((uint32_t)0x00000040) /*!< ICODE SRAM Write protection page 6 */
#define SYSCFG_RCR_PAGE7          ((uint32_t)0x00000080) /*!< ICODE SRAM Write protection page 7 */

/*****************  Bit definition for SYSCFG_EXTICR1 register  ***************/
#define SYSCFG_EXTICR1_EXTI0            ((uint16_t)0x000F) /*!< EXTI 0 configuration */
#define SYSCFG_EXTICR1_EXTI1            ((uint16_t)0x00F0) /*!< EXTI 1 configuration */
#define SYSCFG_EXTICR1_EXTI2            ((uint16_t)0x0F00) /*!< EXTI 2 configuration */
#define SYSCFG_EXTICR1_EXTI3            ((uint16_t)0xF000) /*!< EXTI 3 configuration */

/** 
  * @brief  EXTI0 configuration  
  */ 
#define SYSCFG_EXTICR1_EXTI0_PA         ((uint16_t)0x0000) /*!< PA[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PB         ((uint16_t)0x0001) /*!< PB[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PC         ((uint16_t)0x0002) /*!< PC[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PD         ((uint16_t)0x0003) /*!< PD[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PE         ((uint16_t)0x0004) /*!< PE[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PF         ((uint16_t)0x0005) /*!< PF[0] pin */

/** 
  * @brief  EXTI1 configuration  
  */ 
#define SYSCFG_EXTICR1_EXTI1_PA         ((uint16_t)0x0000) /*!< PA[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PB         ((uint16_t)0x0010) /*!< PB[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PC         ((uint16_t)0x0020) /*!< PC[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PD         ((uint16_t)0x0030) /*!< PD[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PE         ((uint16_t)0x0040) /*!< PE[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PF         ((uint16_t)0x0050) /*!< PF[1] pin */

/** 
  * @brief  EXTI2 configuration  
  */ 
#define SYSCFG_EXTICR1_EXTI2_PA         ((uint16_t)0x0000) /*!< PA[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PB         ((uint16_t)0x0100) /*!< PB[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PC         ((uint16_t)0x0200) /*!< PC[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PD         ((uint16_t)0x0300) /*!< PD[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PE         ((uint16_t)0x0400) /*!< PE[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PF         ((uint16_t)0x0500) /*!< PF[2] pin */

/** 
  * @brief  EXTI3 configuration  
  */ 
#define SYSCFG_EXTICR1_EXTI3_PA         ((uint16_t)0x0000) /*!< PA[3] pin */
#define SYSCFG_EXTICR1_EXTI3_PB         ((uint16_t)0x1000) /*!< PB[3] pin */
#define SYSCFG_EXTICR1_EXTI3_PC         ((uint16_t)0x2000) /*!< PC[3] pin */
#define SYSCFG_EXTICR1_EXTI3_PD         ((uint16_t)0x3000) /*!< PD[3] pin */
#define SYSCFG_EXTICR1_EXTI3_PE         ((uint16_t)0x4000) /*!< PE[3] pin */

/*****************  Bit definition for SYSCFG_EXTICR2 register  ***************/
#define SYSCFG_EXTIRCR_EXTI4            ((uint16_t)0x000F) /*!< EXTI 4 configuration */
#define SYSCFG_EXTIRCR_EXTI5            ((uint16_t)0x00F0) /*!< EXTI 5 configuration */
#define SYSCFG_EXTIRCR_EXTI6            ((uint16_t)0x0F00) /*!< EXTI 6 configuration */
#define SYSCFG_EXTIRCR_EXTI7            ((uint16_t)0xF000) /*!< EXTI 7 configuration */

/** 
  * @brief  EXTI4 configuration  
  */ 
#define SYSCFG_EXTIRCR_EXTI4_PA         ((uint16_t)0x0000) /*!< PA[4] pin */
#define SYSCFG_EXTIRCR_EXTI4_PB         ((uint16_t)0x0001) /*!< PB[4] pin */
#define SYSCFG_EXTIRCR_EXTI4_PC         ((uint16_t)0x0002) /*!< PC[4] pin */
#define SYSCFG_EXTIRCR_EXTI4_PD         ((uint16_t)0x0003) /*!< PD[4] pin */
#define SYSCFG_EXTIRCR_EXTI4_PE         ((uint16_t)0x0004) /*!< PE[4] pin */
#define SYSCFG_EXTIRCR_EXTI4_PF         ((uint16_t)0x0005) /*!< PF[4] pin */

/** 
  * @brief  EXTI5 configuration  
  */ 
#define SYSCFG_EXTIRCR_EXTI5_PA         ((uint16_t)0x0000) /*!< PA[5] pin */
#define SYSCFG_EXTIRCR_EXTI5_PB         ((uint16_t)0x0010) /*!< PB[5] pin */
#define SYSCFG_EXTIRCR_EXTI5_PC         ((uint16_t)0x0020) /*!< PC[5] pin */
#define SYSCFG_EXTIRCR_EXTI5_PD         ((uint16_t)0x0030) /*!< PD[5] pin */
#define SYSCFG_EXTIRCR_EXTI5_PE         ((uint16_t)0x0040) /*!< PE[5] pin */
#define SYSCFG_EXTIRCR_EXTI5_PF         ((uint16_t)0x0050) /*!< PF[5] pin */

/** 
  * @brief  EXTI6 configuration  
  */ 
#define SYSCFG_EXTIRCR_EXTI6_PA         ((uint16_t)0x0000) /*!< PA[6] pin */
#define SYSCFG_EXTIRCR_EXTI6_PB         ((uint16_t)0x0100) /*!< PB[6] pin */
#define SYSCFG_EXTIRCR_EXTI6_PC         ((uint16_t)0x0200) /*!< PC[6] pin */
#define SYSCFG_EXTIRCR_EXTI6_PD         ((uint16_t)0x0300) /*!< PD[6] pin */
#define SYSCFG_EXTIRCR_EXTI6_PE         ((uint16_t)0x0400) /*!< PE[6] pin */
#define SYSCFG_EXTIRCR_EXTI6_PF         ((uint16_t)0x0500) /*!< PF[6] pin */

/** 
  * @brief  EXTI7 configuration  
  */ 
#define SYSCFG_EXTIRCR_EXTI7_PA         ((uint16_t)0x0000) /*!< PA[7] pin */
#define SYSCFG_EXTIRCR_EXTI7_PB         ((uint16_t)0x1000) /*!< PB[7] pin */
#define SYSCFG_EXTIRCR_EXTI7_PC         ((uint16_t)0x2000) /*!< PC[7] pin */
#define SYSCFG_EXTIRCR_EXTI7_PD         ((uint16_t)0x3000) /*!< PD[7] pin */
#define SYSCFG_EXTIRCR_EXTI7_PE         ((uint16_t)0x4000) /*!< PE[7] pin */

/*****************  Bit definition for SYSCFG_EXTICR3 register  ***************/
#define SYSCFG_EXTICR3_EXTI8            ((uint16_t)0x000F) /*!< EXTI 8 configuration */
#define SYSCFG_EXTICR3_EXTI9            ((uint16_t)0x00F0) /*!< EXTI 9 configuration */
#define SYSCFG_EXTICR3_EXTI10           ((uint16_t)0x0F00) /*!< EXTI 10 configuration */
#define SYSCFG_EXTICR3_EXTI11           ((uint16_t)0xF000) /*!< EXTI 11 configuration */

/** 
  * @brief  EXTI8 configuration  
  */ 
#define SYSCFG_EXTICR3_EXTI8_PA         ((uint16_t)0x0000) /*!< PA[8] pin */
#define SYSCFG_EXTICR3_EXTI8_PB         ((uint16_t)0x0001) /*!< PB[8] pin */
#define SYSCFG_EXTICR3_EXTI8_PC         ((uint16_t)0x0002) /*!< PC[8] pin */
#define SYSCFG_EXTICR3_EXTI8_PD         ((uint16_t)0x0003) /*!< PD[8] pin */
#define SYSCFG_EXTICR3_EXTI8_PE         ((uint16_t)0x0004) /*!< PE[8] pin */

/** 
  * @brief  EXTI9 configuration  
  */ 
#define SYSCFG_EXTICR3_EXTI9_PA         ((uint16_t)0x0000) /*!< PA[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PB         ((uint16_t)0x0010) /*!< PB[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PC         ((uint16_t)0x0020) /*!< PC[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PD         ((uint16_t)0x0030) /*!< PD[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PE         ((uint16_t)0x0040) /*!< PE[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PF         ((uint16_t)0x0050) /*!< PF[9] pin */

/** 
  * @brief  EXTI10 configuration  
  */ 
#define SYSCFG_EXTICR3_EXTI10_PA        ((uint16_t)0x0000) /*!< PA[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PB        ((uint16_t)0x0100) /*!< PB[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PC        ((uint16_t)0x0200) /*!< PC[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PD        ((uint16_t)0x0300) /*!< PD[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PE        ((uint16_t)0x0400) /*!< PE[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PF        ((uint16_t)0x0500) /*!< PF[10] pin */

/** 
  * @brief  EXTI11 configuration  
  */ 
#define SYSCFG_EXTICR3_EXTI11_PA        ((uint16_t)0x0000) /*!< PA[11] pin */
#define SYSCFG_EXTICR3_EXTI11_PB        ((uint16_t)0x1000) /*!< PB[11] pin */
#define SYSCFG_EXTICR3_EXTI11_PC        ((uint16_t)0x2000) /*!< PC[11] pin */
#define SYSCFG_EXTICR3_EXTI11_PD        ((uint16_t)0x3000) /*!< PD[11] pin */
#define SYSCFG_EXTICR3_EXTI11_PE        ((uint16_t)0x4000) /*!< PE[11] pin */

/*****************  Bit definition for SYSCFG_EXTICR4 register  *****************/
#define SYSCFG_EXTICR4_EXTI12           ((uint16_t)0x000F) /*!< EXTI 12 configuration */
#define SYSCFG_EXTICR4_EXTI13           ((uint16_t)0x00F0) /*!< EXTI 13 configuration */
#define SYSCFG_EXTICR4_EXTI14           ((uint16_t)0x0F00) /*!< EXTI 14 configuration */
#define SYSCFG_EXTICR4_EXTI15           ((uint16_t)0xF000) /*!< EXTI 15 configuration */

/** 
  * @brief  EXTI12 configuration  
  */ 
#define SYSCFG_EXTICR4_EXTI12_PA        ((uint16_t)0x0000) /*!< PA[12] pin */
#define SYSCFG_EXTICR4_EXTI12_PB        ((uint16_t)0x0001) /*!< PB[12] pin */
#define SYSCFG_EXTICR4_EXTI12_PC        ((uint16_t)0x0002) /*!< PC[12] pin */
#define SYSCFG_EXTICR4_EXTI12_PD        ((uint16_t)0x0003) /*!< PD[12] pin */
#define SYSCFG_EXTICR4_EXTI12_PE        ((uint16_t)0x0004) /*!< PE[12] pin */

/** 
  * @brief  EXTI13 configuration  
  */ 
#define SYSCFG_EXTICR4_EXTI13_PA        ((uint16_t)0x0000) /*!< PA[13] pin */
#define SYSCFG_EXTICR4_EXTI13_PB        ((uint16_t)0x0010) /*!< PB[13] pin */
#define SYSCFG_EXTICR4_EXTI13_PC        ((uint16_t)0x0020) /*!< PC[13] pin */
#define SYSCFG_EXTICR4_EXTI13_PD        ((uint16_t)0x0030) /*!< PD[13] pin */
#define SYSCFG_EXTICR4_EXTI13_PE        ((uint16_t)0x0040) /*!< PE[13] pin */

/** 
  * @brief  EXTI14 configuration  
  */ 
#define SYSCFG_EXTICR4_EXTI14_PA        ((uint16_t)0x0000) /*!< PA[14] pin */
#define SYSCFG_EXTICR4_EXTI14_PB        ((uint16_t)0x0100) /*!< PB[14] pin */
#define SYSCFG_EXTICR4_EXTI14_PC        ((uint16_t)0x0200) /*!< PC[14] pin */
#define SYSCFG_EXTICR4_EXTI14_PD        ((uint16_t)0x0300) /*!< PD[14] pin */
#define SYSCFG_EXTICR4_EXTI14_PE        ((uint16_t)0x0400) /*!< PE[14] pin */

/** 
  * @brief  EXTI15 configuration  
  */ 
#define SYSCFG_EXTICR4_EXTI15_PA        ((uint16_t)0x0000) /*!< PA[15] pin */
#define SYSCFG_EXTICR4_EXTI15_PB        ((uint16_t)0x1000) /*!< PB[15] pin */
#define SYSCFG_EXTICR4_EXTI15_PC        ((uint16_t)0x2000) /*!< PC[15] pin */
#define SYSCFG_EXTICR4_EXTI15_PD        ((uint16_t)0x3000) /*!< PD[15] pin */
#define SYSCFG_EXTICR4_EXTI15_PE        ((uint16_t)0x4000) /*!< PE[15] pin */

/*****************  Bit definition for SYSCFG_CFGR2 register  *****************/
#define SYSCFG_CFGR2_LOCKUP_LOCK               ((uint32_t)0x00000001) /*!< Enables and locks the PVD connection with Timer1/8/15/16/17 Break Input and also the PVD_EN and PVDSEL[2:0] bits of the Power Control Interface */
#define SYSCFG_CFGR2_SRAM_PARITY_LOCK          ((uint32_t)0x00000002) /*!< Enables and locks the SRAM_PARITY error signal with Break Input of TIMER1/8/15/16/17 */
#define SYSCFG_CFGR2_PVD_LOCK                  ((uint32_t)0x00000004) /*!< Enables and locks the LOCKUP (Hardfault) output of CortexM4 with Break Input of TIMER1/8/15/16/17 */
#define SYSCFG_CFGR2_BYP_ADDR_PAR              ((uint32_t)0x00000010) /*!< Disables the address parity check on RAM */
#define SYSCFG_CFGR2_SRAM_PE                   ((uint32_t)0x00000100) /*!< SRAM Parity error flag */

/*****************  Bit definition for SYSCFG_CFGR3 register  *****************/
#define SYSCFG_CFGR3_SPI1_RX_DMA_RMP           ((uint32_t)0x00000003) /*!< SPI1 RX DMA remap */
#define SYSCFG_CFGR3_SPI1_RX_DMA_RMP_0         ((uint32_t)0x00000001) /*!< SPI1 RX DMA remap bit 0 */
#define SYSCFG_CFGR3_SPI1_RX_DMA_RMP_1         ((uint32_t)0x00000002) /*!< SPI1 RX DMA remap bit 1 */
#define SYSCFG_CFGR3_SPI1_TX_DMA_RMP           ((uint32_t)0x0000000C) /*!< SPI1 TX DMA remap */
#define SYSCFG_CFGR3_SPI1_TX_DMA_RMP_0         ((uint32_t)0x00000004) /*!< SPI1 TX DMA remap bit 0 */
#define SYSCFG_CFGR3_SPI1_TX_DMA_RMP_1         ((uint32_t)0x00000008) /*!< SPI1 TX DMA remap bit 1 */
#define SYSCFG_CFGR3_I2C1_RX_DMA_RMP           ((uint32_t)0x00000030) /*!< I2C1 RX DMA remap */
#define SYSCFG_CFGR3_I2C1_RX_DMA_RMP_0         ((uint32_t)0x00000010) /*!< I2C1 RX DMA remap bit 0 */
#define SYSCFG_CFGR3_I2C1_RX_DMA_RMP_1         ((uint32_t)0x00000020) /*!< I2C1 RX DMA remap bit 1 */
#define SYSCFG_CFGR3_I2C1_TX_DMA_RMP           ((uint32_t)0x000000C0) /*!< I2C1 RX DMA remap */
#define SYSCFG_CFGR3_I2C1_TX_DMA_RMP_0         ((uint32_t)0x00000040) /*!< I2C1 TX DMA remap bit 0 */
#define SYSCFG_CFGR3_I2C1_TX_DMA_RMP_1         ((uint32_t)0x00000080) /*!< I2C1 TX DMA remap bit 1 */
#define SYSCFG_CFGR3_ADC2_DMA_RMP              ((uint32_t)0x00000300) /*!< ADC2 DMA remap */
#define SYSCFG_CFGR3_ADC2_DMA_RMP_0            ((uint32_t)0x00000100) /*!< ADC2 DMA remap bit 0 */
#define SYSCFG_CFGR3_ADC2_DMA_RMP_1            ((uint32_t)0x00000200) /*!< ADC2 DMA remap bit 1 */
#define SYSCFG_CFGR3_DAC1_TRG3_RMP             ((uint32_t)0x00010000) /*!< DAC1 TRG3 remap */
#define SYSCFG_CFGR3_DAC1_TRG5_RMP             ((uint32_t)0x00020000) /*!< DAC1 TRG5 remap */

/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN                         ((uint16_t)0x0001)            /*!<Counter enable */
#define  TIM_CR1_UDIS                        ((uint16_t)0x0002)            /*!<Update disable */
#define  TIM_CR1_URS                         ((uint16_t)0x0004)            /*!<Update request source */
#define  TIM_CR1_OPM                         ((uint16_t)0x0008)            /*!<One pulse mode */
#define  TIM_CR1_DIR                         ((uint16_t)0x0010)            /*!<Direction */

#define  TIM_CR1_CMS                         ((uint16_t)0x0060)            /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0                       ((uint16_t)0x0020)            /*!<Bit 0 */
#define  TIM_CR1_CMS_1                       ((uint16_t)0x0040)            /*!<Bit 1 */

#define  TIM_CR1_ARPE                        ((uint16_t)0x0080)            /*!<Auto-reload preload enable */

#define  TIM_CR1_CKD                         ((uint16_t)0x0300)            /*!<CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CR1_CKD_1                       ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_CR1_UIFREMAP                    ((uint16_t)0x0800)            /*!<Update interrupt flag remap */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define  TIM_CR2_CCPC                        ((uint32_t)0x00000001)            /*!<Capture/Compare Preloaded Control */
#define  TIM_CR2_CCUS                        ((uint32_t)0x00000004)            /*!<Capture/Compare Control Update Selection */
#define  TIM_CR2_CCDS                        ((uint32_t)0x00000008)            /*!<Capture/Compare DMA Selection */

#define  TIM_CR2_MMS                         ((uint32_t)0x00000070)            /*!<MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS_0                       ((uint32_t)0x00000010)            /*!<Bit 0 */
#define  TIM_CR2_MMS_1                       ((uint32_t)0x00000020)            /*!<Bit 1 */
#define  TIM_CR2_MMS_2                       ((uint32_t)0x00000040)            /*!<Bit 2 */

#define  TIM_CR2_TI1S                        ((uint32_t)0x00000080)            /*!<TI1 Selection */
#define  TIM_CR2_OIS1                        ((uint32_t)0x00000100)            /*!<Output Idle state 1 (OC1 output) */
#define  TIM_CR2_OIS1N                       ((uint32_t)0x00000200)            /*!<Output Idle state 1 (OC1N output) */
#define  TIM_CR2_OIS2                        ((uint32_t)0x00000400)            /*!<Output Idle state 2 (OC2 output) */
#define  TIM_CR2_OIS2N                       ((uint32_t)0x00000800)            /*!<Output Idle state 2 (OC2N output) */
#define  TIM_CR2_OIS3                        ((uint32_t)0x00001000)            /*!<Output Idle state 3 (OC3 output) */
#define  TIM_CR2_OIS3N                       ((uint32_t)0x00002000)            /*!<Output Idle state 3 (OC3N output) */
#define  TIM_CR2_OIS4                        ((uint32_t)0x00004000)            /*!<Output Idle state 4 (OC4 output) */
#define  TIM_CR2_OIS5                        ((uint32_t)0x00010000)            /*!<Output Idle state 4 (OC4 output) */
#define  TIM_CR2_OIS6                        ((uint32_t)0x00020000)            /*!<Output Idle state 4 (OC4 output) */

#define  TIM_CR2_MMS2                        ((uint32_t)0x00F00000)            /*!<MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS2_0                      ((uint32_t)0x00100000)            /*!<Bit 0 */
#define  TIM_CR2_MMS2_1                      ((uint32_t)0x00200000)            /*!<Bit 1 */
#define  TIM_CR2_MMS2_2                      ((uint32_t)0x00400000)            /*!<Bit 2 */
#define  TIM_CR2_MMS2_3                      ((uint32_t)0x00800000)            /*!<Bit 2 */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define  TIM_SMCR_SMS                        ((uint32_t)0x00010007)            /*!<SMS[2:0] bits (Slave mode selection) */
#define  TIM_SMCR_SMS_0                      ((uint32_t)0x00000001)            /*!<Bit 0 */
#define  TIM_SMCR_SMS_1                      ((uint32_t)0x00000002)            /*!<Bit 1 */
#define  TIM_SMCR_SMS_2                      ((uint32_t)0x00000004)            /*!<Bit 2 */
#define  TIM_SMCR_SMS_3                      ((uint32_t)0x00010000)            /*!<Bit 3 */

#define  TIM_SMCR_OCCS                       ((uint32_t)0x00000008)            /*!< OCREF clear selection */

#define  TIM_SMCR_TS                         ((uint32_t)0x00000070)            /*!<TS[2:0] bits (Trigger selection) */
#define  TIM_SMCR_TS_0                       ((uint32_t)0x00000010)            /*!<Bit 0 */
#define  TIM_SMCR_TS_1                       ((uint32_t)0x00000020)            /*!<Bit 1 */
#define  TIM_SMCR_TS_2                       ((uint32_t)0x00000040)            /*!<Bit 2 */

#define  TIM_SMCR_MSM                        ((uint32_t)0x00000080)            /*!<Master/slave mode */

#define  TIM_SMCR_ETF                        ((uint32_t)0x00000F00)            /*!<ETF[3:0] bits (External trigger filter) */
#define  TIM_SMCR_ETF_0                      ((uint32_t)0x00000100)            /*!<Bit 0 */
#define  TIM_SMCR_ETF_1                      ((uint32_t)0x00000200)            /*!<Bit 1 */
#define  TIM_SMCR_ETF_2                      ((uint32_t)0x00000400)            /*!<Bit 2 */
#define  TIM_SMCR_ETF_3                      ((uint32_t)0x00000800)            /*!<Bit 3 */

#define  TIM_SMCR_ETPS                       ((uint32_t)0x00003000)            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define  TIM_SMCR_ETPS_0                     ((uint32_t)0x00001000)            /*!<Bit 0 */
#define  TIM_SMCR_ETPS_1                     ((uint32_t)0x00002000)            /*!<Bit 1 */

#define  TIM_SMCR_ECE                        ((uint32_t)0x00004000)            /*!<External clock enable */
#define  TIM_SMCR_ETP                        ((uint32_t)0x00008000)            /*!<External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define  TIM_DIER_UIE                        ((uint16_t)0x0001)            /*!<Update interrupt enable */
#define  TIM_DIER_CC1IE                      ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt enable */
#define  TIM_DIER_CC2IE                      ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt enable */
#define  TIM_DIER_CC3IE                      ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt enable */
#define  TIM_DIER_CC4IE                      ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt enable */
#define  TIM_DIER_COMIE                      ((uint16_t)0x0020)            /*!<COM interrupt enable */
#define  TIM_DIER_TIE                        ((uint16_t)0x0040)            /*!<Trigger interrupt enable */
#define  TIM_DIER_BIE                        ((uint16_t)0x0080)            /*!<Break interrupt enable */
#define  TIM_DIER_UDE                        ((uint16_t)0x0100)            /*!<Update DMA request enable */
#define  TIM_DIER_CC1DE                      ((uint16_t)0x0200)            /*!<Capture/Compare 1 DMA request enable */
#define  TIM_DIER_CC2DE                      ((uint16_t)0x0400)            /*!<Capture/Compare 2 DMA request enable */
#define  TIM_DIER_CC3DE                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 DMA request enable */
#define  TIM_DIER_CC4DE                      ((uint16_t)0x1000)            /*!<Capture/Compare 4 DMA request enable */
#define  TIM_DIER_COMDE                      ((uint16_t)0x2000)            /*!<COM DMA request enable */
#define  TIM_DIER_TDE                        ((uint16_t)0x4000)            /*!<Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define  TIM_SR_UIF                          ((uint32_t)0x00000001)            /*!<Update interrupt Flag */
#define  TIM_SR_CC1IF                        ((uint32_t)0x00000002)            /*!<Capture/Compare 1 interrupt Flag */
#define  TIM_SR_CC2IF                        ((uint32_t)0x00000004)            /*!<Capture/Compare 2 interrupt Flag */
#define  TIM_SR_CC3IF                        ((uint32_t)0x00000008)            /*!<Capture/Compare 3 interrupt Flag */
#define  TIM_SR_CC4IF                        ((uint32_t)0x00000010)            /*!<Capture/Compare 4 interrupt Flag */
#define  TIM_SR_COMIF                        ((uint32_t)0x00000020)            /*!<COM interrupt Flag */
#define  TIM_SR_TIF                          ((uint32_t)0x00000040)            /*!<Trigger interrupt Flag */
#define  TIM_SR_BIF                          ((uint32_t)0x00000080)            /*!<Break interrupt Flag */
#define  TIM_SR_B2IF                         ((uint32_t)0x00000100)            /*!<Break2 interrupt Flag */
#define  TIM_SR_CC1OF                        ((uint32_t)0x00000200)            /*!<Capture/Compare 1 Over capture Flag */
#define  TIM_SR_CC2OF                        ((uint32_t)0x00000400)            /*!<Capture/Compare 2 Over capture Flag */
#define  TIM_SR_CC3OF                        ((uint32_t)0x00000800)            /*!<Capture/Compare 3 Over capture Flag */
#define  TIM_SR_CC4OF                        ((uint32_t)0x00001000)            /*!<Capture/Compare 4 Over capture Flag */
#define  TIM_SR_CC5IF                        ((uint32_t)0x00010000)            /*!<Capture/Compare 5 interrupt Flag */
#define  TIM_SR_CC6IF                        ((uint32_t)0x00020000)            /*!<Capture/Compare 6 interrupt Flag */


/*******************  Bit definition for TIM_EGR register  ********************/
#define  TIM_EGR_UG                          ((uint16_t)0x0001)               /*!<Update Generation */
#define  TIM_EGR_CC1G                        ((uint16_t)0x0002)               /*!<Capture/Compare 1 Generation */
#define  TIM_EGR_CC2G                        ((uint16_t)0x0004)               /*!<Capture/Compare 2 Generation */
#define  TIM_EGR_CC3G                        ((uint16_t)0x0008)               /*!<Capture/Compare 3 Generation */
#define  TIM_EGR_CC4G                        ((uint16_t)0x0010)               /*!<Capture/Compare 4 Generation */
#define  TIM_EGR_COMG                        ((uint16_t)0x0020)               /*!<Capture/Compare Control Update Generation */
#define  TIM_EGR_TG                          ((uint16_t)0x0040)               /*!<Trigger Generation */
#define  TIM_EGR_BG                          ((uint16_t)0x0080)               /*!<Break Generation */
#define  TIM_EGR_B2G                         ((uint16_t)0x0100)               /*!<Break Generation */


/******************  Bit definition for TIM_CCMR1 register  *******************/
#define  TIM_CCMR1_CC1S                      ((uint32_t)0x00000003)            /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TIM_CCMR1_CC1S_0                    ((uint32_t)0x00000001)            /*!<Bit 0 */
#define  TIM_CCMR1_CC1S_1                    ((uint32_t)0x00000002)            /*!<Bit 1 */

#define  TIM_CCMR1_OC1FE                     ((uint32_t)0x00000004)            /*!<Output Compare 1 Fast enable */
#define  TIM_CCMR1_OC1PE                     ((uint32_t)0x00000008)            /*!<Output Compare 1 Preload enable */

#define  TIM_CCMR1_OC1M                      ((uint32_t)0x00010070)            /*!<OC1M[2:0] bits (Output Compare 1 Mode) */
#define  TIM_CCMR1_OC1M_0                    ((uint32_t)0x00000010)            /*!<Bit 0 */
#define  TIM_CCMR1_OC1M_1                    ((uint32_t)0x00000020)            /*!<Bit 1 */
#define  TIM_CCMR1_OC1M_2                    ((uint32_t)0x00000040)            /*!<Bit 2 */
#define  TIM_CCMR1_OC1M_3                    ((uint32_t)0x00010000)            /*!<Bit 3 */

#define  TIM_CCMR1_OC1CE                     ((uint32_t)0x00000080)            /*!<Output Compare 1Clear Enable */

#define  TIM_CCMR1_CC2S                      ((uint32_t)0x00000300)            /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TIM_CCMR1_CC2S_0                    ((uint32_t)0x00000100)            /*!<Bit 0 */
#define  TIM_CCMR1_CC2S_1                    ((uint32_t)0x00000200)            /*!<Bit 1 */

#define  TIM_CCMR1_OC2FE                     ((uint32_t)0x00000400)            /*!<Output Compare 2 Fast enable */
#define  TIM_CCMR1_OC2PE                     ((uint32_t)0x00000800)            /*!<Output Compare 2 Preload enable */

#define  TIM_CCMR1_OC2M                      ((uint32_t)0x01007000)            /*!<OC2M[2:0] bits (Output Compare 2 Mode) */
#define  TIM_CCMR1_OC2M_0                    ((uint32_t)0x00001000)            /*!<Bit 0 */
#define  TIM_CCMR1_OC2M_1                    ((uint32_t)0x00002000)            /*!<Bit 1 */
#define  TIM_CCMR1_OC2M_2                    ((uint32_t)0x00004000)            /*!<Bit 2 */
#define  TIM_CCMR1_OC2M_3                    ((uint32_t)0x01000000)            /*!<Bit 3 */

#define  TIM_CCMR1_OC2CE                     ((uint32_t)0x00008000)            /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR1_IC1PSC                    ((uint32_t)0x0000000C)            /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TIM_CCMR1_IC1PSC_0                  ((uint32_t)0x00000004)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1PSC_1                  ((uint32_t)0x00000008)            /*!<Bit 1 */

#define  TIM_CCMR1_IC1F                      ((uint32_t)0x000000F0)            /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define  TIM_CCMR1_IC1F_0                    ((uint32_t)0x00000010)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1F_1                    ((uint32_t)0x00000020)            /*!<Bit 1 */
#define  TIM_CCMR1_IC1F_2                    ((uint32_t)0x00000040)            /*!<Bit 2 */
#define  TIM_CCMR1_IC1F_3                    ((uint32_t)0x00000080)            /*!<Bit 3 */

#define  TIM_CCMR1_IC2PSC                    ((uint32_t)0x00000C00)            /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  TIM_CCMR1_IC2PSC_0                  ((uint32_t)0x00000400)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2PSC_1                  ((uint32_t)0x00000800)            /*!<Bit 1 */

#define  TIM_CCMR1_IC2F                      ((uint32_t)0x0000F000)            /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define  TIM_CCMR1_IC2F_0                    ((uint32_t)0x00001000)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2F_1                    ((uint32_t)0x00002000)            /*!<Bit 1 */
#define  TIM_CCMR1_IC2F_2                    ((uint32_t)0x00004000)            /*!<Bit 2 */
#define  TIM_CCMR1_IC2F_3                    ((uint32_t)0x00008000)            /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define  TIM_CCMR2_CC3S                      ((uint32_t)0x00000003)            /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  TIM_CCMR2_CC3S_0                    ((uint32_t)0x00000001)            /*!<Bit 0 */
#define  TIM_CCMR2_CC3S_1                    ((uint32_t)0x00000002)            /*!<Bit 1 */

#define  TIM_CCMR2_OC3FE                     ((uint32_t)0x00000004)            /*!<Output Compare 3 Fast enable */
#define  TIM_CCMR2_OC3PE                     ((uint32_t)0x00000008)            /*!<Output Compare 3 Preload enable */

#define  TIM_CCMR2_OC3M                      ((uint32_t)0x00000070)            /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TIM_CCMR2_OC3M_0                    ((uint32_t)0x00000010)            /*!<Bit 0 */
#define  TIM_CCMR2_OC3M_1                    ((uint32_t)0x00000020)            /*!<Bit 1 */
#define  TIM_CCMR2_OC3M_2                    ((uint32_t)0x00000040)            /*!<Bit 2 */
#define  TIM_CCMR2_OC3M_3                    ((uint32_t)0x00010000)            /*!<Bit 3 */

#define  TIM_CCMR2_OC3CE                     ((uint32_t)0x00000080)            /*!<Output Compare 3 Clear Enable */

#define  TIM_CCMR2_CC4S                      ((uint32_t)0x00000300)            /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TIM_CCMR2_CC4S_0                    ((uint32_t)0x00000100)            /*!<Bit 0 */
#define  TIM_CCMR2_CC4S_1                    ((uint32_t)0x00000200)            /*!<Bit 1 */

#define  TIM_CCMR2_OC4FE                     ((uint32_t)0x00000400)            /*!<Output Compare 4 Fast enable */
#define  TIM_CCMR2_OC4PE                     ((uint32_t)0x00000800)            /*!<Output Compare 4 Preload enable */

#define  TIM_CCMR2_OC4M                      ((uint32_t)0x00007000)            /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR2_OC4M_0                    ((uint32_t)0x00001000)            /*!<Bit 0 */
#define  TIM_CCMR2_OC4M_1                    ((uint32_t)0x00002000)            /*!<Bit 1 */
#define  TIM_CCMR2_OC4M_2                    ((uint32_t)0x00004000)            /*!<Bit 2 */
#define  TIM_CCMR2_OC4M_3                    ((uint32_t)0x00100000)            /*!<Bit 3 */

#define  TIM_CCMR2_OC4CE                     ((uint32_t)0x00008000)            /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR2_IC3PSC                    ((uint16_t)0x0000000C)            /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TIM_CCMR2_IC3PSC_0                  ((uint16_t)0x00000004)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3PSC_1                  ((uint16_t)0x00000008)            /*!<Bit 1 */

#define  TIM_CCMR2_IC3F                      ((uint16_t)0x000000F0)            /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TIM_CCMR2_IC3F_0                    ((uint16_t)0x00000010)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3F_1                    ((uint16_t)0x00000020)            /*!<Bit 1 */
#define  TIM_CCMR2_IC3F_2                    ((uint16_t)0x00000040)            /*!<Bit 2 */
#define  TIM_CCMR2_IC3F_3                    ((uint16_t)0x00000080)            /*!<Bit 3 */

#define  TIM_CCMR2_IC4PSC                    ((uint16_t)0x00000C00)            /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TIM_CCMR2_IC4PSC_0                  ((uint16_t)0x00000400)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4PSC_1                  ((uint16_t)0x00000800)            /*!<Bit 1 */

#define  TIM_CCMR2_IC4F                      ((uint16_t)0x0000F000)            /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TIM_CCMR2_IC4F_0                    ((uint16_t)0x00001000)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4F_1                    ((uint16_t)0x00002000)            /*!<Bit 1 */
#define  TIM_CCMR2_IC4F_2                    ((uint16_t)0x00004000)            /*!<Bit 2 */
#define  TIM_CCMR2_IC4F_3                    ((uint16_t)0x00008000)            /*!<Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E                       ((uint32_t)0x00000001)            /*!<Capture/Compare 1 output enable */
#define  TIM_CCER_CC1P                       ((uint32_t)0x00000002)            /*!<Capture/Compare 1 output Polarity */
#define  TIM_CCER_CC1NE                      ((uint32_t)0x00000004)            /*!<Capture/Compare 1 Complementary output enable */
#define  TIM_CCER_CC1NP                      ((uint32_t)0x00000008)            /*!<Capture/Compare 1 Complementary output Polarity */
#define  TIM_CCER_CC2E                       ((uint32_t)0x00000010)            /*!<Capture/Compare 2 output enable */
#define  TIM_CCER_CC2P                       ((uint32_t)0x00000020)            /*!<Capture/Compare 2 output Polarity */
#define  TIM_CCER_CC2NE                      ((uint32_t)0x00000040)            /*!<Capture/Compare 2 Complementary output enable */
#define  TIM_CCER_CC2NP                      ((uint32_t)0x00000080)            /*!<Capture/Compare 2 Complementary output Polarity */
#define  TIM_CCER_CC3E                       ((uint32_t)0x00000100)            /*!<Capture/Compare 3 output enable */
#define  TIM_CCER_CC3P                       ((uint32_t)0x00000200)            /*!<Capture/Compare 3 output Polarity */
#define  TIM_CCER_CC3NE                      ((uint32_t)0x00000400)            /*!<Capture/Compare 3 Complementary output enable */
#define  TIM_CCER_CC3NP                      ((uint32_t)0x00000800)            /*!<Capture/Compare 3 Complementary output Polarity */
#define  TIM_CCER_CC4E                       ((uint32_t)0x00001000)            /*!<Capture/Compare 4 output enable */
#define  TIM_CCER_CC4P                       ((uint32_t)0x00002000)            /*!<Capture/Compare 4 output Polarity */
#define  TIM_CCER_CC4NP                      ((uint32_t)0x00008000)            /*!<Capture/Compare 4 Complementary output Polarity */
#define  TIM_CCER_CC5E                       ((uint32_t)0x00010000)            /*!<Capture/Compare 5 output enable */
#define  TIM_CCER_CC5P                       ((uint32_t)0x00020000)            /*!<Capture/Compare 5 output Polarity */
#define  TIM_CCER_CC6E                       ((uint32_t)0x00100000)            /*!<Capture/Compare 6 output enable */
#define  TIM_CCER_CC6P                       ((uint32_t)0x00200000)            /*!<Capture/Compare 6 output Polarity */
/*******************  Bit definition for TIM_CNT register  ********************/
#define  TIM_CNT_CNT                         ((uint32_t)0xFFFFFFFF)            /*!<Counter Value */
#define  TIM_CNT_UIFCPY                      ((uint32_t)0x80000000)            /*!<Update interrupt flag copy */
/*******************  Bit definition for TIM_PSC register  ********************/
#define  TIM_PSC_PSC                         ((uint16_t)0xFFFF)            /*!<Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define  TIM_ARR_ARR                         ((uint32_t)0xFFFFFFFF)            /*!<actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define  TIM_RCR_REP                         ((uint8_t)0xFF)               /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define  TIM_CCR1_CCR1                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define  TIM_CCR2_CCR2                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define  TIM_CCR3_CCR3                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define  TIM_CCR4_CCR4                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 4 Value */

/*******************  Bit definition for TIM_CCR5 register  *******************/
#define  TIM_CCR5_CCR5                       ((uint32_t)0xFFFFFFFF)        /*!<Capture/Compare 5 Value */
#define  TIM_CCR5_GC5C1                      ((uint32_t)0x20000000)        /*!<Group Channel 5 and Channel 1 */
#define  TIM_CCR5_GC5C2                      ((uint32_t)0x40000000)        /*!<Group Channel 5 and Channel 2 */
#define  TIM_CCR5_GC5C3                      ((uint32_t)0x80000000)        /*!<Group Channel 5 and Channel 3 */

/*******************  Bit definition for TIM_CCR6 register  *******************/
#define  TIM_CCR6_CCR6                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 6 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define  TIM_BDTR_DTG                        ((uint32_t)0x000000FF)            /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TIM_BDTR_DTG_0                      ((uint32_t)0x00000001)            /*!<Bit 0 */
#define  TIM_BDTR_DTG_1                      ((uint32_t)0x00000002)            /*!<Bit 1 */
#define  TIM_BDTR_DTG_2                      ((uint32_t)0x00000004)            /*!<Bit 2 */
#define  TIM_BDTR_DTG_3                      ((uint32_t)0x00000008)            /*!<Bit 3 */
#define  TIM_BDTR_DTG_4                      ((uint32_t)0x00000010)            /*!<Bit 4 */
#define  TIM_BDTR_DTG_5                      ((uint32_t)0x00000020)            /*!<Bit 5 */
#define  TIM_BDTR_DTG_6                      ((uint32_t)0x00000040)            /*!<Bit 6 */
#define  TIM_BDTR_DTG_7                      ((uint32_t)0x00000080)            /*!<Bit 7 */

#define  TIM_BDTR_LOCK                       ((uint32_t)0x00000300)            /*!<LOCK[1:0] bits (Lock Configuration) */
#define  TIM_BDTR_LOCK_0                     ((uint32_t)0x00000100)            /*!<Bit 0 */
#define  TIM_BDTR_LOCK_1                     ((uint32_t)0x00000200)            /*!<Bit 1 */

#define  TIM_BDTR_OSSI                       ((uint32_t)0x00000400)            /*!<Off-State Selection for Idle mode */
#define  TIM_BDTR_OSSR                       ((uint32_t)0x00000800)            /*!<Off-State Selection for Run mode */
#define  TIM_BDTR_BKE                        ((uint32_t)0x00001000)            /*!<Break enable for Break1 */
#define  TIM_BDTR_BKP                        ((uint32_t)0x00002000)            /*!<Break Polarity for Break1 */
#define  TIM_BDTR_AOE                        ((uint32_t)0x00004000)            /*!<Automatic Output enable */
#define  TIM_BDTR_MOE                        ((uint32_t)0x00008000)            /*!<Main Output enable */

#define  TIM_BDTR_BKF                        ((uint32_t)0x000F0000)            /*!<Break Filter for Break1 */
#define  TIM_BDTR_BK2F                       ((uint32_t)0x00F00000)            /*!<Break Filter for Break2 */

#define  TIM_BDTR_BK2E                       ((uint32_t)0x01000000)            /*!<Break enable for Break2 */
#define  TIM_BDTR_BK2P                       ((uint32_t)0x02000000)            /*!<Break Polarity for Break2 */

/*******************  Bit definition for TIM_DCR register  ********************/
#define  TIM_DCR_DBA                         ((uint16_t)0x001F)            /*!<DBA[4:0] bits (DMA Base Address) */
#define  TIM_DCR_DBA_0                       ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_DCR_DBA_1                       ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_DCR_DBA_2                       ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TIM_DCR_DBA_3                       ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TIM_DCR_DBA_4                       ((uint16_t)0x0010)            /*!<Bit 4 */

#define  TIM_DCR_DBL                         ((uint16_t)0x1F00)            /*!<DBL[4:0] bits (DMA Burst Length) */
#define  TIM_DCR_DBL_0                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_DCR_DBL_1                       ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TIM_DCR_DBL_2                       ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TIM_DCR_DBL_3                       ((uint16_t)0x0800)            /*!<Bit 3 */
#define  TIM_DCR_DBL_4                       ((uint16_t)0x1000)            /*!<Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define  TIM_DMAR_DMAB                       ((uint16_t)0xFFFF)            /*!<DMA register for burst accesses */

/*******************  Bit definition for TIM16_OR register  *********************/
#define TIM16_OR_TI1_RMP                     ((uint16_t)0x00C0)            /*!<TI1_RMP[1:0] bits (TIM16 Input 1 remap) */
#define TIM16_OR_TI1_RMP_0                   ((uint16_t)0x0040)            /*!<Bit 0 */
#define TIM16_OR_TI1_RMP_1                   ((uint16_t)0x0080)            /*!<Bit 1 */

/*******************  Bit definition for TIM1_OR register  *********************/
#define TIM1_OR_ETR_RMP                      ((uint16_t)0x000F)            /*!<ETR_RMP[3:0] bits (TIM1 ETR remap) */
#define TIM1_OR_ETR_RMP_0                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define TIM1_OR_ETR_RMP_1                    ((uint16_t)0x0002)            /*!<Bit 1 */
#define TIM1_OR_ETR_RMP_2                    ((uint16_t)0x0004)            /*!<Bit 2 */
#define TIM1_OR_ETR_RMP_3                    ((uint16_t)0x0008)            /*!<Bit 3 */

/*******************  Bit definition for TIM8_OR register  *********************/
#define TIM8_OR_ETR_RMP                      ((uint16_t)0x000F)            /*!<ETR_RMP[3:0] bits (TIM8 ETR remap) */
#define TIM8_OR_ETR_RMP_0                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define TIM8_OR_ETR_RMP_1                    ((uint16_t)0x0002)            /*!<Bit 1 */
#define TIM8_OR_ETR_RMP_2                    ((uint16_t)0x0004)            /*!<Bit 2 */
#define TIM8_OR_ETR_RMP_3                    ((uint16_t)0x0008)            /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR3 register  *******************/
#define  TIM_CCMR3_OC5FE                     ((uint32_t)0x00000004)            /*!<Output Compare 5 Fast enable */
#define  TIM_CCMR3_OC5PE                     ((uint32_t)0x00000008)            /*!<Output Compare 5 Preload enable */

#define  TIM_CCMR3_OC5M                      ((uint32_t)0x00000070)            /*!<OC5M[2:0] bits (Output Compare 5 Mode) */
#define  TIM_CCMR3_OC5M_0                    ((uint32_t)0x00000010)            /*!<Bit 0 */
#define  TIM_CCMR3_OC5M_1                    ((uint32_t)0x00000020)            /*!<Bit 1 */
#define  TIM_CCMR3_OC5M_2                    ((uint32_t)0x00000040)            /*!<Bit 2 */
#define  TIM_CCMR3_OC5M_3                    ((uint32_t)0x00010000)            /*!<Bit 3 */

#define  TIM_CCMR3_OC5CE                     ((uint32_t)0x00000080)            /*!<Output Compare 5 Clear Enable */

#define  TIM_CCMR3_OC6FE                     ((uint32_t)0x00000400)            /*!<Output Compare 4 Fast enable */
#define  TIM_CCMR3_OC6PE                     ((uint32_t)0x00000800)            /*!<Output Compare 4 Preload enable */

#define  TIM_CCMR3_OC6M                      ((uint32_t)0x00007000)            /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR3_OC6M_0                    ((uint32_t)0x00001000)            /*!<Bit 0 */
#define  TIM_CCMR3_OC6M_1                    ((uint32_t)0x00002000)            /*!<Bit 1 */
#define  TIM_CCMR3_OC6M_2                    ((uint32_t)0x00004000)            /*!<Bit 2 */
#define  TIM_CCMR3_OC6M_3                    ((uint32_t)0x00100000)            /*!<Bit 3 */

#define  TIM_CCMR3_OC6CE                     ((uint32_t)0x00008000)            /*!<Output Compare 4 Clear Enable */

/******************************************************************************/
/*                                                                            */
/*      Universal Synchronous Asynchronous Receiver Transmitter (USART)       */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for USART_CR1 register  *******************/
#define  USART_CR1_UE                        ((uint32_t)0x00000001)            /*!< USART Enable */
#define  USART_CR1_UESM                      ((uint32_t)0x00000002)            /*!< USART Enable in STOP Mode */
#define  USART_CR1_RE                        ((uint32_t)0x00000004)            /*!< Receiver Enable */
#define  USART_CR1_TE                        ((uint32_t)0x00000008)            /*!< Transmitter Enable */
#define  USART_CR1_IDLEIE                    ((uint32_t)0x00000010)            /*!< IDLE Interrupt Enable */
#define  USART_CR1_RXNEIE                    ((uint32_t)0x00000020)            /*!< RXNE Interrupt Enable */
#define  USART_CR1_TCIE                      ((uint32_t)0x00000040)            /*!< Transmission Complete Interrupt Enable */
#define  USART_CR1_TXEIE                     ((uint32_t)0x00000080)            /*!< TXE Interrupt Enable */
#define  USART_CR1_PEIE                      ((uint32_t)0x00000100)            /*!< PE Interrupt Enable */
#define  USART_CR1_PS                        ((uint32_t)0x00000200)            /*!< Parity Selection */
#define  USART_CR1_PCE                       ((uint32_t)0x00000400)            /*!< Parity Control Enable */
#define  USART_CR1_WAKE                      ((uint32_t)0x00000800)            /*!< Receiver Wakeup method */
#define  USART_CR1_M                         ((uint32_t)0x00001000)            /*!< Word length */
#define  USART_CR1_MME                       ((uint32_t)0x00002000)            /*!< Mute Mode Enable */
#define  USART_CR1_CMIE                      ((uint32_t)0x00004000)            /*!< Character match interrupt enable */
#define  USART_CR1_OVER8                     ((uint32_t)0x00008000)            /*!< Oversampling by 8-bit or 16-bit mode */
#define  USART_CR1_DEDT                      ((uint32_t)0x001F0000)            /*!< DEDT[4:0] bits (Driver Enable Deassertion Time) */
#define  USART_CR1_DEDT_0                    ((uint32_t)0x00010000)            /*!< Bit 0 */
#define  USART_CR1_DEDT_1                    ((uint32_t)0x00020000)            /*!< Bit 1 */
#define  USART_CR1_DEDT_2                    ((uint32_t)0x00040000)            /*!< Bit 2 */
#define  USART_CR1_DEDT_3                    ((uint32_t)0x00080000)            /*!< Bit 3 */
#define  USART_CR1_DEDT_4                    ((uint32_t)0x00100000)            /*!< Bit 4 */
#define  USART_CR1_DEAT                      ((uint32_t)0x03E00000)            /*!< DEAT[4:0] bits (Driver Enable Assertion Time) */
#define  USART_CR1_DEAT_0                    ((uint32_t)0x00200000)            /*!< Bit 0 */
#define  USART_CR1_DEAT_1                    ((uint32_t)0x00400000)            /*!< Bit 1 */
#define  USART_CR1_DEAT_2                    ((uint32_t)0x00800000)            /*!< Bit 2 */
#define  USART_CR1_DEAT_3                    ((uint32_t)0x01000000)            /*!< Bit 3 */
#define  USART_CR1_DEAT_4                    ((uint32_t)0x02000000)            /*!< Bit 4 */
#define  USART_CR1_RTOIE                     ((uint32_t)0x04000000)            /*!< Receive Time Out interrupt enable */
#define  USART_CR1_EOBIE                     ((uint32_t)0x08000000)            /*!< End of Block interrupt enable */

/******************  Bit definition for USART_CR2 register  *******************/
#define  USART_CR2_ADDM7                     ((uint32_t)0x00000010)            /*!< 7-bit or 4-bit Address Detection */
#define  USART_CR2_LBDL                      ((uint32_t)0x00000020)            /*!< LIN Break Detection Length */
#define  USART_CR2_LBDIE                     ((uint32_t)0x00000040)            /*!< LIN Break Detection Interrupt Enable */
#define  USART_CR2_LBCL                      ((uint32_t)0x00000100)            /*!< Last Bit Clock pulse */
#define  USART_CR2_CPHA                      ((uint32_t)0x00000200)            /*!< Clock Phase */
#define  USART_CR2_CPOL                      ((uint32_t)0x00000400)            /*!< Clock Polarity */
#define  USART_CR2_CLKEN                     ((uint32_t)0x00000800)            /*!< Clock Enable */
#define  USART_CR2_STOP                      ((uint32_t)0x00003000)            /*!< STOP[1:0] bits (STOP bits) */
#define  USART_CR2_STOP_0                    ((uint32_t)0x00001000)            /*!< Bit 0 */
#define  USART_CR2_STOP_1                    ((uint32_t)0x00002000)            /*!< Bit 1 */
#define  USART_CR2_LINEN                     ((uint32_t)0x00004000)            /*!< LIN mode enable */
#define  USART_CR2_SWAP                      ((uint32_t)0x00008000)            /*!< SWAP TX/RX pins */
#define  USART_CR2_RXINV                     ((uint32_t)0x00010000)            /*!< RX pin active level inversion */
#define  USART_CR2_TXINV                     ((uint32_t)0x00020000)            /*!< TX pin active level inversion */
#define  USART_CR2_DATAINV                   ((uint32_t)0x00040000)            /*!< Binary data inversion */
#define  USART_CR2_MSBFIRST                  ((uint32_t)0x00080000)            /*!< Most Significant Bit First */
#define  USART_CR2_ABREN                     ((uint32_t)0x00100000)            /*!< Auto Baud-Rate Enable*/
#define  USART_CR2_ABRMODE                   ((uint32_t)0x00600000)            /*!< ABRMOD[1:0] bits (Auto Baud-Rate Mode) */
#define  USART_CR2_ABRMODE_0                 ((uint32_t)0x00200000)            /*!< Bit 0 */
#define  USART_CR2_ABRMODE_1                 ((uint32_t)0x00400000)            /*!< Bit 1 */
#define  USART_CR2_RTOEN                     ((uint32_t)0x00800000)            /*!< Receiver Time-Out enable */
#define  USART_CR2_ADD                       ((uint32_t)0xFF000000)            /*!< Address of the USART node */

/******************  Bit definition for USART_CR3 register  *******************/
#define  USART_CR3_EIE                       ((uint32_t)0x00000001)            /*!< Error Interrupt Enable */
#define  USART_CR3_IREN                      ((uint32_t)0x00000002)            /*!< IrDA mode Enable */
#define  USART_CR3_IRLP                      ((uint32_t)0x00000004)            /*!< IrDA Low-Power */
#define  USART_CR3_HDSEL                     ((uint32_t)0x00000008)            /*!< Half-Duplex Selection */
#define  USART_CR3_NACK                      ((uint32_t)0x00000010)            /*!< SmartCard NACK enable */
#define  USART_CR3_SCEN                      ((uint32_t)0x00000020)            /*!< SmartCard mode enable */
#define  USART_CR3_DMAR                      ((uint32_t)0x00000040)            /*!< DMA Enable Receiver */
#define  USART_CR3_DMAT                      ((uint32_t)0x00000080)            /*!< DMA Enable Transmitter */
#define  USART_CR3_RTSE                      ((uint32_t)0x00000100)            /*!< RTS Enable */
#define  USART_CR3_CTSE                      ((uint32_t)0x00000200)            /*!< CTS Enable */
#define  USART_CR3_CTSIE                     ((uint32_t)0x00000400)            /*!< CTS Interrupt Enable */
#define  USART_CR3_ONEBIT                    ((uint32_t)0x00000800)            /*!< One sample bit method enable */
#define  USART_CR3_OVRDIS                    ((uint32_t)0x00001000)            /*!< Overrun Disable */
#define  USART_CR3_DDRE                      ((uint32_t)0x00002000)            /*!< DMA Disable on Reception Error */
#define  USART_CR3_DEM                       ((uint32_t)0x00004000)            /*!< Driver Enable Mode */
#define  USART_CR3_DEP                       ((uint32_t)0x00008000)            /*!< Driver Enable Polarity Selection */
#define  USART_CR3_SCARCNT                   ((uint32_t)0x000E0000)            /*!< SCARCNT[2:0] bits (SmartCard Auto-Retry Count) */
#define  USART_CR3_SCARCNT_0                 ((uint32_t)0x00020000)            /*!< Bit 0 */
#define  USART_CR3_SCARCNT_1                 ((uint32_t)0x00040000)            /*!< Bit 1 */
#define  USART_CR3_SCARCNT_2                 ((uint32_t)0x00080000)            /*!< Bit 2 */
#define  USART_CR3_WUS                       ((uint32_t)0x00300000)            /*!< WUS[1:0] bits (Wake UP Interrupt Flag Selection) */
#define  USART_CR3_WUS_0                     ((uint32_t)0x00100000)            /*!< Bit 0 */
#define  USART_CR3_WUS_1                     ((uint32_t)0x00200000)            /*!< Bit 1 */
#define  USART_CR3_WUFIE                     ((uint32_t)0x00400000)            /*!< Wake Up Interrupt Enable */

/******************  Bit definition for USART_BRR register  *******************/
#define  USART_BRR_DIV_FRACTION              ((uint16_t)0x000F)                /*!< Fraction of USARTDIV */
#define  USART_BRR_DIV_MANTISSA              ((uint16_t)0xFFF0)                /*!< Mantissa of USARTDIV */

/******************  Bit definition for USART_GTPR register  ******************/
#define  USART_GTPR_PSC                      ((uint16_t)0x00FF)                /*!< PSC[7:0] bits (Prescaler value) */
#define  USART_GTPR_GT                       ((uint16_t)0xFF00)                /*!< GT[7:0] bits (Guard time value) */


/*******************  Bit definition for USART_RTOR register  *****************/
#define  USART_RTOR_RTO                      ((uint32_t)0x00FFFFFF)            /*!< Receiver Time Out Value */
#define  USART_RTOR_BLEN                     ((uint32_t)0xFF000000)            /*!< Block Length */

/*******************  Bit definition for USART_RQR register  ******************/
#define  USART_RQR_ABRRQ                     ((uint16_t)0x0001)                /*!< Auto-Baud Rate Request */
#define  USART_RQR_SBKRQ                     ((uint16_t)0x0002)                /*!< Send Break Request */
#define  USART_RQR_MMRQ                      ((uint16_t)0x0004)                /*!< Mute Mode Request */
#define  USART_RQR_RXFRQ                     ((uint16_t)0x0008)                /*!< Receive Data flush Request */
#define  USART_RQR_TXFRQ                     ((uint16_t)0x0010)                /*!< Transmit data flush Request */

/*******************  Bit definition for USART_ISR register  ******************/
#define  USART_ISR_PE                        ((uint32_t)0x00000001)            /*!< Parity Error */
#define  USART_ISR_FE                        ((uint32_t)0x00000002)            /*!< Framing Error */
#define  USART_ISR_NE                        ((uint32_t)0x00000004)            /*!< Noise detected Flag */
#define  USART_ISR_ORE                       ((uint32_t)0x00000008)            /*!< OverRun Error */
#define  USART_ISR_IDLE                      ((uint32_t)0x00000010)            /*!< IDLE line detected */
#define  USART_ISR_RXNE                      ((uint32_t)0x00000020)            /*!< Read Data Register Not Empty */
#define  USART_ISR_TC                        ((uint32_t)0x00000040)            /*!< Transmission Complete */
#define  USART_ISR_TXE                       ((uint32_t)0x00000080)            /*!< Transmit Data Register Empty */
#define  USART_ISR_LBD                       ((uint32_t)0x00000100)            /*!< LIN Break Detection Flag */
#define  USART_ISR_CTSIF                     ((uint32_t)0x00000200)            /*!< CTS interrupt flag */
#define  USART_ISR_CTS                       ((uint32_t)0x00000400)            /*!< CTS flag */
#define  USART_ISR_RTOF                      ((uint32_t)0x00000800)            /*!< Receiver Time Out */
#define  USART_ISR_EOBF                      ((uint32_t)0x00001000)            /*!< End Of Block Flag */
#define  USART_ISR_ABRE                      ((uint32_t)0x00004000)            /*!< Auto-Baud Rate Error */
#define  USART_ISR_ABRF                      ((uint32_t)0x00008000)            /*!< Auto-Baud Rate Flag */
#define  USART_ISR_BUSY                      ((uint32_t)0x00010000)            /*!< Busy Flag */
#define  USART_ISR_CMF                       ((uint32_t)0x00020000)            /*!< Character Match Flag */
#define  USART_ISR_SBKF                      ((uint32_t)0x00040000)            /*!< Send Break Flag */
#define  USART_ISR_RWU                       ((uint32_t)0x00080000)            /*!< Receive Wake Up from mute mode Flag */
#define  USART_ISR_WUF                       ((uint32_t)0x00100000)            /*!< Wake Up from stop mode Flag */
#define  USART_ISR_TEACK                     ((uint32_t)0x00200000)            /*!< Transmit Enable Acknowledge Flag */
#define  USART_ISR_REACK                     ((uint32_t)0x00400000)            /*!< Receive Enable Acknowledge Flag */

/*******************  Bit definition for USART_ICR register  ******************/
#define  USART_ICR_PECF                      ((uint32_t)0x00000001)            /*!< Parity Error Clear Flag */
#define  USART_ICR_FECF                      ((uint32_t)0x00000002)            /*!< Framing Error Clear Flag */
#define  USART_ICR_NCF                       ((uint32_t)0x00000004)            /*!< Noise detected Clear Flag */
#define  USART_ICR_ORECF                     ((uint32_t)0x00000008)            /*!< OverRun Error Clear Flag */
#define  USART_ICR_IDLECF                    ((uint32_t)0x00000010)            /*!< IDLE line detected Clear Flag */
#define  USART_ICR_TCCF                      ((uint32_t)0x00000040)            /*!< Transmission Complete Clear Flag */
#define  USART_ICR_LBDCF                     ((uint32_t)0x00000100)            /*!< LIN Break Detection Clear Flag */
#define  USART_ICR_CTSCF                     ((uint32_t)0x00000200)            /*!< CTS Interrupt Clear Flag */
#define  USART_ICR_RTOCF                     ((uint32_t)0x00000800)            /*!< Receiver Time Out Clear Flag */
#define  USART_ICR_EOBCF                     ((uint32_t)0x00001000)            /*!< End Of Block Clear Flag */
#define  USART_ICR_CMCF                      ((uint32_t)0x00020000)            /*!< Character Match Clear Flag */
#define  USART_ICR_WUCF                      ((uint32_t)0x00100000)            /*!< Wake Up from stop mode Clear Flag */

/*******************  Bit definition for USART_RDR register  ******************/
#define  USART_RDR_RDR                       ((uint16_t)0x01FF)                /*!< RDR[8:0] bits (Receive Data value) */

/*******************  Bit definition for USART_TDR register  ******************/
#define  USART_TDR_TDR                       ((uint16_t)0x01FF)                /*!< TDR[8:0] bits (Transmit Data value) */

/******************************************************************************/
/*                                                                            */
/*                            Window WATCHDOG                                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for WWDG_CR register  ********************/
#define  WWDG_CR_T                           ((uint8_t)0x7F)               /*!<T[6:0] bits (7-Bit counter (MSB to LSB)) */
#define  WWDG_CR_T0                          ((uint8_t)0x01)               /*!<Bit 0 */
#define  WWDG_CR_T1                          ((uint8_t)0x02)               /*!<Bit 1 */
#define  WWDG_CR_T2                          ((uint8_t)0x04)               /*!<Bit 2 */
#define  WWDG_CR_T3                          ((uint8_t)0x08)               /*!<Bit 3 */
#define  WWDG_CR_T4                          ((uint8_t)0x10)               /*!<Bit 4 */
#define  WWDG_CR_T5                          ((uint8_t)0x20)               /*!<Bit 5 */
#define  WWDG_CR_T6                          ((uint8_t)0x40)               /*!<Bit 6 */

#define  WWDG_CR_WDGA                        ((uint8_t)0x80)               /*!<Activation bit */

/*******************  Bit definition for WWDG_CFR register  *******************/
#define  WWDG_CFR_W                          ((uint16_t)0x007F)            /*!<W[6:0] bits (7-bit window value) */
#define  WWDG_CFR_W0                         ((uint16_t)0x0001)            /*!<Bit 0 */
#define  WWDG_CFR_W1                         ((uint16_t)0x0002)            /*!<Bit 1 */
#define  WWDG_CFR_W2                         ((uint16_t)0x0004)            /*!<Bit 2 */
#define  WWDG_CFR_W3                         ((uint16_t)0x0008)            /*!<Bit 3 */
#define  WWDG_CFR_W4                         ((uint16_t)0x0010)            /*!<Bit 4 */
#define  WWDG_CFR_W5                         ((uint16_t)0x0020)            /*!<Bit 5 */
#define  WWDG_CFR_W6                         ((uint16_t)0x0040)            /*!<Bit 6 */

#define  WWDG_CFR_WDGTB                      ((uint16_t)0x0180)            /*!<WDGTB[1:0] bits (Timer Base) */
#define  WWDG_CFR_WDGTB0                     ((uint16_t)0x0080)            /*!<Bit 0 */
#define  WWDG_CFR_WDGTB1                     ((uint16_t)0x0100)            /*!<Bit 1 */

#define  WWDG_CFR_EWI                        ((uint16_t)0x0200)            /*!<Early Wakeup Interrupt */

/*******************  Bit definition for WWDG_SR register  ********************/
#define  WWDG_SR_EWIF                        ((uint8_t)0x01)               /*!<Early Wakeup Interrupt Flag */

/**
  * @}
  */

 /**
  * @}
  */ 

#ifdef USE_STDPERIPH_DRIVER
  #include "stm32f30x_conf.h"
#endif /*!< USE_STDPERIPH_DRIVER */

/** @addtogroup Exported_macro
  * @{
  */

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32F30x_H */

/**
  * @}
  */

  /**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
