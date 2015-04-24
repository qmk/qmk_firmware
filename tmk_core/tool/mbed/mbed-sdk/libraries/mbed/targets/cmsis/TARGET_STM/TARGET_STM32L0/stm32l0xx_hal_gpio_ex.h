/**
  ******************************************************************************
  * @file    stm32l0xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of GPIO HAL Extension module.
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
#ifndef __STM32L0xx_HAL_GPIO_EX_H
#define __STM32L0xx_HAL_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */ 
  

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L083xx/STM32L073xx---------------------------*/
/*----------------------------------------------------------------------------*/

#if defined (STM32L083xx) || defined (STM32L073xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */

/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |TSC     |USART2  |TIM2_TR |USART4  |COMP1   |
 * PA1 |EVENTOUT|LCD     |TIM2_C2 |TSC     |USART2  |TIM21_TR|USART4  |        |
 * PA2 |TIM21_C1|LCD     |TIM2_C3 |TSC     |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|LCD     |TIM2_C4 |TSC     |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |        |        |TSC     |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |TSC     |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |LCD     |TIM3_C1 |TSC     |LPUART1 |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |LCD     |TIM3_C2 |TSC     |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |LCD     |USB     |EVENTOUT|USART1  |        |        |I2C3    |
 * PA9 |MCO     |LCD     |        |TSC     |USART1  |        |I2C1    |I2C3    |
 * PA10|        |LCD     |        |TSC     |USART1  |        |I2C1    |        |
 * PA11|SPI1    |        |EVENTOUT|TSC     |USART1  |        |I2C2    |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|TSC     |USART1  |        |I2C2    |COMP2   |
 * PA13|SWDIO   |        |USB     |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |LCD     |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |USART4  |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|LCD     |TIM3_C3 |TSC     |        |        |        |        |
 * PB1 |        |LCD     |TIM3_C4 |TSC     |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|TSC     |        |        |        |I2C3    |
 * PB3 |SPI1    |LCD     |TIM2_C2 |TSC     |EVENTOUT|USART1  |USART5  |        |
 * PB4 |SPI1    |LCD     |TIM3_C1 |TSC     |TIM22_C1|USART1  |USART5  |I2C3    |
 * PB5 |SPI1    |LCD     |LPTIM1_I|I2C1    |TIM3_C2 |USART1  |USART5  |        |
 *     |        |        |        |        |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|TSC     |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|TSC     |        |        |USART4  |        |
 * PB8 |        |LCD     |        |TSC     |I2C1    |        |        |        |
 * PB9 |        |LCD     |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |LCD     |TIM2_C3 |TSC     |LPUART1 |SPI2    |I2C2    |LPUART1 |
 * PB11|EVENTOUT|LCD     |TIM2_C4 |TSC     |LPUART1 |        |I2C2    |LPUART1 |
 * PB12|SPI2    |LCD     |LPUART1 |TSC     |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |LCD     |MCO     |TSC     |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |LCD     |RTC     |TSC     |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |LCD     |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|LCD     |EVENTOUT|TSC     |        |        |LPUART1 |I2C3    |
 * PC1 |LPTIM1_O|LCD     |EVENTOUT|TSC     |        |        |LPUART1 |I2C3    |
 * PC2 |LPTIM1_I|LCD     |SPI2    |TSC     |        |        |        |        |
 * PC3 |LPTIM1_T|LCD     |SPI2    |TSC     |        |        |        |        |
 * PC4 |EVENTOUT|LCD     |LPUART1 |        |        |        |        |        |
 * PC5 |        |LCD     |LPUART1 |TSC     |        |        |        |        |
 * PC6 |TIM22_C1|LCD     |TIM3_C1 |TSC     |        |        |        |        |
 * PC7 |TIM22_C2|LCD     |TIM3_C2 |TSC     |        |        |        |        |
 * PC8 |TIM22_TR|LCD     |TIM3_C3 |TSC     |        |        |        |        |
 * PC9 |TIM21_TR|LCD     |USB     |TSC     |        |        |        |I2C3    |
 *     |        |        |TIM3_C4 |        |        |        |        |        |
 * PC10|LPUART1 |LCD     |        |        |        |        |USART4  |        |
 * PC11|LPUART1 |LCD     |        |        |        |        |USART4  |        |
 * PC12|        |LCD     |USART5  |        |        |        |USART4  |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD0 |TIM21_C1|SPI2    |        |        |        |        |        |        |
 * PD1 |        |SPI2    |        |        |        |        |        |        |
 * PD2 |LPUART1 |LCD     |TIM3_TR |        |        |        |USART5  |        |
 * PD3 |USART2  |LCD     |SPI2    |        |        |        |        |        |
 * PD4 |USART2  |SPI2    |        |        |        |        |        |        |
 * PD5 |USART2  |        |        |        |        |        |        |        |
 * PD6 |USART2  |        |        |        |        |        |        |        |
 * PD7 |USART2  |TIM21_C2|        |        |        |        |        |        |
 * PD8 |LPUART1 |LCD     |        |        |        |        |        |        |
 * PD9 |LPUART1 |LCD     |        |        |        |        |        |        |
 * PD10|        |LCD     |        |        |        |        |        |        |
 * PD11|LPUART1 |LCD     |        |        |        |        |        |        |
 * PD12|LPUART1 |LCD     |        |        |        |        |        |        |
 * PD13|        |LCD     |        |        |        |        |        |        |
 * PD14|        |LCD     |        |        |        |        |        |        |
 * PD15|USB     |LCD     |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PE0 |        |LCD     |EVENTOUT|        |        |        |        |        |
 * PE1 |        |LCD     |EVENTOUT|        |        |        |        |        |
 * PE2 |        |LCD     |TIM3_TR |        |        |        |        |        |
 * PE3 |TIM22_C1|LCD     |TIM3_C1 |        |        |        |        |        |
 * PE4 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PE5 |TIM21_C1|        |TIM3_C3 |        |        |        |        |        |
 * PE6 |TIM21_C2|        |TIM3_C4 |        |        |        |        |        |
 * PE7 |        |LCD     |        |        |        |        |USART5  |        |
 * PE8 |        |LCD     |        |        |        |        |USART4  |        |
 * PE9 |TIM2_C1 |LCD     |TIM2_TR |        |        |        |USART4  |        |
 * PE10|TIM2_C2 |LCD     |        |        |        |        |USART5  |        |
 * PE11|TIM2_C3 |        |        |        |        |        |USART5  |        |
 * PE12|TIM2_C4 |        |SPI1    |        |        |        |        |        |
 * PE13|        |LCD     |SPI1    |        |        |        |        |        |
 * PE14|        |LCD     |SPI1    |        |        |        |        |        |
 * PE15|        |LCD     |SPI1    |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |USB     |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 * PH9 |        |        |        |        |        |        |        |        |
 * PH10|        |        |        |        |        |        |        |        |
 *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/** @defgroup GPIOEx_Alternate_function_AF0  Alternate function AF0
 * @{
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_SPI2          ((uint8_t)0x00)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM22         ((uint8_t)0x00)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_TIM2          ((uint8_t)0x00)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_USB           ((uint8_t)0x00)  /* USB Alternate Function mapping      */
/**
 * @}
 */

/** @defgroup GPIOEx_Alternate_function_AF1  Alternate function AF1
 * @{
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF1_TIM21         ((uint8_t)0x01)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF1_LCD           ((uint8_t)0x01)  /* LCD Alternate Function mapping      */
/**
 * @}
 */

/** @defgroup GPIOEx_Alternate_function_AF2  Alternate function AF2
 * @{
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping     */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF2_MCO           ((uint8_t)0x02)  /* MCO Alternate Function mapping      */
#define GPIO_AF2_RTC           ((uint8_t)0x02)  /* RTC_OUT Alternate Function mapping  */
#define GPIO_AF2_SPI2          ((uint8_t)0x02)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF2_USART5        ((uint8_t)0x02)  /* USART5 Alternate Function mapping   */
#define GPIO_AF2_SPI1          ((uint8_t)0x02)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF2_USB           ((uint8_t)0x00)  /* USB Alternate Function mapping      */
/**
 * @}
 */

/** @defgroup GPIOEx_Alternate_function_AF3  Alternate function AF3
 * @{
 */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF3_I2C1          ((uint8_t)0x03)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC  Alternate Function mapping     */
/**
 * @}
 */

/** @defgroup GPIOEx_Alternate_function_AF4  Alternate function AF4
 * @{
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04)  /* USART2 Alternate Function mapping  */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04)  /* LPUART1 Alternate Function mapping */
#define GPIO_AF4_USART1          ((uint8_t)0x04)  /* USART1 Alternate Function mapping  */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04)  /* EVENTOUT Alternate Function mapping*/
#define GPIO_AF4_TIM22           ((uint8_t)0x04)  /* TIM22 Alternate Function mapping   */
#define GPIO_AF4_TIM3            ((uint8_t)0x04)  /* TIM3 Alternate Function mapping    */
#define GPIO_AF4_I2C1            ((uint8_t)0x04)  /* I2C1 Alternate Function mapping    */
/**
 * @}
 */

/** @defgroup GPIOEx_Alternate_function_AF5  Alternate function AF5
 * @{
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF5_USART1        ((uint8_t)0x05)  /* USART1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C2          ((uint8_t)0x05)  /* I2C2 Alternate Function mapping     */
/**
 * @}
 */

/** @defgroup GPIOEx_Alternate_function_AF6  Alternate function AF6
 * @{
 */

#define GPIO_AF6_USART4        ((uint8_t)0x06)  /* USART4 Alternate Function mapping   */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF6_I2C1          ((uint8_t)0x06)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF6_USART5        ((uint8_t)0x06)  /* USART5 Alternate Function mapping   */
#define GPIO_AF6_TIM21         ((uint8_t)0x06)  /* TIM21 Alternate Function mapping    */
/**
 * @}
 */

/** @defgroup GPIOEx_Alternate_function_AF7  Alternate function AF7
 * @{
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07)  /* COMP2 Alternate Function mapping     */
#define GPIO_AF7_I2C3         ((uint8_t)0x07)  /* I2C3 Alternate Function mapping      */
#define GPIO_AF7_LPUART1      ((uint8_t)0x07)  /* LPUART1 Alternate Function mapping   */
/**
  * @}
  */

/**
  * @}
  */

/**
 * @brief  IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(__AF__) (((__AF__) == GPIO_AF0_EVENTOUT) || ((__AF__) == GPIO_AF1_LCD)      || \
                            ((__AF__) == GPIO_AF0_SPI1)     || ((__AF__) == GPIO_AF1_I2C1)     || \
                            ((__AF__) == GPIO_AF0_TIM21)    || ((__AF__) == GPIO_AF1_SPI2)     || \
                            ((__AF__) == GPIO_AF0_MCO)      || ((__AF__) == GPIO_AF1_TIM21)    || \
                            ((__AF__) == GPIO_AF0_SWDIO)    || ((__AF__) == GPIO_AF2_TIM2)     || \
                            ((__AF__) == GPIO_AF0_SWCLK)    || ((__AF__) == GPIO_AF2_TIM3)     || \
                            ((__AF__) == GPIO_AF0_USART1)   || ((__AF__) == GPIO_AF2_USB)      || \
                            ((__AF__) == GPIO_AF0_SPI2)     || ((__AF__) == GPIO_AF2_EVENTOUT) || \
                            ((__AF__) == GPIO_AF0_LPTIM1)   || ((__AF__) == GPIO_AF2_LPTIM1)   || \
                            ((__AF__) == GPIO_AF0_TIM2)     || ((__AF__) == GPIO_AF2_LPUART1)  || \
                            ((__AF__) == GPIO_AF0_LPUART1)  || ((__AF__) == GPIO_AF2_MCO)      || \
                            ((__AF__) == GPIO_AF0_USART2)   || ((__AF__) == GPIO_AF2_RTC)      || \
                            ((__AF__) == GPIO_AF0_USB)      || ((__AF__) == GPIO_AF2_SPI2)     || \
                            ((__AF__) == GPIO_AF0_TIM2)     || ((__AF__) == GPIO_AF2_USART5)   || \
                            ((__AF__) == GPIO_AF3_TSC)      || ((__AF__) == GPIO_AF2_SPI1)     || \
                            ((__AF__) == GPIO_AF3_EVENTOUT) || ((__AF__) == GPIO_AF4_USART2)   || \
                            ((__AF__) == GPIO_AF3_I2C1)     || ((__AF__) == GPIO_AF4_LPUART1)  || \
                            ((__AF__) == GPIO_AF5_TIM21)    || ((__AF__) == GPIO_AF4_EVENTOUT) || \
                            ((__AF__) == GPIO_AF5_TIM2)     || ((__AF__) == GPIO_AF4_USART1)   || \
                            ((__AF__) == GPIO_AF5_USART1)   || ((__AF__) == GPIO_AF4_TIM22)    || \
                            ((__AF__) == GPIO_AF5_TIM22)    || ((__AF__) == GPIO_AF4_TIM3)     || \
                            ((__AF__) == GPIO_AF5_SPI2)     || ((__AF__) == GPIO_AF4_I2C1)     || \
                            ((__AF__) == GPIO_AF5_I2C2)     || ((__AF__) == GPIO_AF6_USART4)   || \
                            ((__AF__) == GPIO_AF7_COMP2)    || ((__AF__) == GPIO_AF6_LPUART1)  || \
                            ((__AF__) == GPIO_AF7_COMP1)    || ((__AF__) == GPIO_AF6_I2C1)     || \
                            ((__AF__) == GPIO_AF7_I2C3)     || ((__AF__) == GPIO_AF6_EVENTOUT) || \
                            ((__AF__) == GPIO_AF7_LPUART1)  || ((__AF__) == GPIO_AF6_I2C2)     || \
                            ((__AF__) == GPIO_AF6_USART5)   || ((__AF__) == GPIO_AF6_TIM21))


#define IS_GPIO_AF_AVAILABLE(__INSTANCE__,__AF__)  \
        ((((__INSTANCE__) == GPIOA) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)       ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)       ||   \
                                        ((__AF__) ==  GPIO_AF4_USART2)    ||   \
                                        ((__AF__) ==  GPIO_AF5_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)    ||   \
                                        ((__AF__) ==  GPIO_AF7_I2C3)))    ||   \
         (((__INSTANCE__) == GPIOB) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)       ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)       ||   \
                                        ((__AF__) ==  GPIO_AF4_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF5_I2C2)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)    ||   \
                                        ((__AF__) ==  GPIO_AF7_LPUART1))) ||   \
         (((__INSTANCE__) == GPIOC) && (((__AF__) ==  GPIO_AF0_LPTIM1)    ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)       ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)       ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)    ||   \
                                        ((__AF__) ==  GPIO_AF7_I2C3)))    ||   \
         (((__INSTANCE__) == GPIOD) && (((__AF__) ==  GPIO_AF0_LPUART1)   ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)       ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART5)))  ||   \
         (((__INSTANCE__) == GPIOE) && (((__AF__) ==  GPIO_AF0_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)       ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)))  ||   \
         (((__INSTANCE__) == GPIOH) && (((__AF__) ==  GPIO_AF0_USB))))

#endif /* (STM32L083xx) || (STM32L073xx) */

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L082xx and STM32L072xx-----------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L082xx) || defined (STM32L072xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 */


/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |TSC     |USART2  |TIM2_TR |USART4  |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |TSC     |USART2  |TIM21_TR|USART4  |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |TSC     |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |TSC     |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |        |        |TSC     |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |TSC     |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |TIM3_C1 |TSC     |LPUART1 |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |TIM3_C2 |TSC     |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |USB     |EVENTOUT|USART1  |        |        |I2C3    |
 * PA9 |MCO     |        |        |TSC     |USART1  |        |I2C1    |I2C3    |
 * PA10|        |        |        |TSC     |USART1  |        |I2C1    |        |
 * PA11|SPI1    |        |EVENTOUT|TSC     |USART1  |        |I2C2    |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|TSC     |USART1  |        |I2C2    |COMP2   |
 * PA13|SWDIO   |        |USB     |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |USART4  |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |TIM3_C3 |TSC     |        |        |        |        |
 * PB1 |        |        |TIM3_C4 |TSC     |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|TSC     |        |        |        |I2C3    |
 * PB3 |SPI1    |        |TIM2_C2 |TSC     |EVENTOUT|USART1  |USART5  |        |
 * PB4 |SPI1    |        |TIM3_C1 |TSC     |TIM22_C1|USART1  |USART5  |I2C3    |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM3_C2 |USART1  |USART5  |        |
 *     |        |        |        |        |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|TSC     |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|TSC     |        |        |USART4  |        |
 * PB8 |        |        |        |TSC     |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |TSC     |LPUART1 |SPI2    |I2C2    |LPUART1 |
 * PB11|EVENTOUT|        |TIM2_C4 |TSC     |LPUART1 |        |I2C2    |LPUART1 |
 * PB12|SPI2    |        |LPUART1 |TSC     |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |MCO     |TSC     |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |TSC     |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|TSC     |        |        |LPUART1 |I2C3    |
 * PC1 |LPTIM1_O|        |EVENTOUT|TSC     |        |        |LPUART1 |I2C3    |
 * PC2 |LPTIM1_I|        |SPI2    |TSC     |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |TSC     |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART1 |        |        |        |        |        |
 * PC5 |        |        |LPUART1 |TSC     |        |        |        |        |
 * PC6 |TIM22_C1|        |TIM3_C1 |TSC     |        |        |        |        |
 * PC7 |TIM22_C2|        |TIM3_C2 |TSC     |        |        |        |        |
 * PC8 |TIM22_TR|        |TIM3_C3 |TSC     |        |        |        |        |
 * PC9 |TIM21_TR|        |USB     |TSC     |        |        |        |I2C3    |
 *     |        |        |TIM3_C4 |        |        |        |        |        |
 * PC10|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC11|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC12|        |        |USART5  |        |        |        |USART4  |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD0 |TIM21_C1|SPI2    |        |        |        |        |        |        |
 * PD1 |        |SPI2    |        |        |        |        |        |        |
 * PD2 |LPUART1 |        |TIM3_TR |        |        |        |USART5  |        |
 * PD3 |USART2  |        |SPI2    |        |        |        |        |        |
 * PD4 |USART2  |SPI2    |        |        |        |        |        |        |
 * PD5 |USART2  |        |        |        |        |        |        |        |
 * PD6 |USART2  |        |        |        |        |        |        |        |
 * PD7 |USART2  |TIM21_C2|        |        |        |        |        |        |
 * PD8 |LPUART1 |        |        |        |        |        |        |        |
 * PD9 |LPUART1 |        |        |        |        |        |        |        |
 * PD10|        |        |        |        |        |        |        |        |
 * PD11|LPUART1 |        |        |        |        |        |        |        |
 * PD12|LPUART1 |        |        |        |        |        |        |        |
 * PD13|        |        |        |        |        |        |        |        |
 * PD14|        |        |        |        |        |        |        |        |
 * PD15|USB     |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PE0 |        |        |EVENTOUT|        |        |        |        |        |
 * PE1 |        |        |EVENTOUT|        |        |        |        |        |
 * PE2 |        |        |TIM3_TR |        |        |        |        |        |
 * PE3 |TIM22_C1|        |TIM3_C1 |        |        |        |        |        |
 * PE4 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PE5 |TIM21_C1|        |TIM3_C3 |        |        |        |        |        |
 * PE6 |TIM21_C2|        |TIM3_C4 |        |        |        |        |        |
 * PE7 |        |        |        |        |        |        |USART5  |        |
 * PE8 |        |        |        |        |        |        |USART4  |        |
 * PE9 |TIM2_C1 |        |TIM2_TR |        |        |        |USART4  |        |
 * PE10|TIM2_C2 |        |        |        |        |        |USART5  |        |
 * PE11|TIM2_C3 |        |        |        |        |        |USART5  |        |
 * PE12|TIM2_C4 |        |SPI1    |        |        |        |        |        |
 * PE13|        |        |SPI1    |        |        |        |        |        |
 * PE14|        |        |SPI1    |        |        |        |        |        |
 * PE15|        |        |SPI1    |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |USB     |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 * PH9 |        |        |        |        |        |        |        |        |
 * PH10|        |        |        |        |        |        |        |        |
 *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/** @defgroup GPIOEx_Alternate_function_AF1  Alternate function AF1
 * @{
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_SPI2          ((uint8_t)0x00)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM22         ((uint8_t)0x00)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_TIM2          ((uint8_t)0x00)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_USB           ((uint8_t)0x00)  /* USB Alternate Function mapping      */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF0  Alternate function AF0
 * @{
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_TIM21         ((uint8_t)0x01)  /* TIM21 Alternate Function mapping */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF2  Alternate function AF2
 * @{
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_MCO           ((uint8_t)0x02)  /* MCO Alternate Function mapping        */
#define GPIO_AF2_RTC           ((uint8_t)0x02)  /* RTC_OUT Alternate Function mapping    */
#define GPIO_AF2_SPI2          ((uint8_t)0x02)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_USART5        ((uint8_t)0x02)  /* USART5 Alternate Function mapping     */
#define GPIO_AF2_SPI1          ((uint8_t)0x02)  /* SPI1 Alternate Function mapping       */
#define GPIO_AF2_USB           ((uint8_t)0x00)  /* USB Alternate Function mapping        */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF3  Alternate function AF3
 * @{
 */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF3_I2C1          ((uint8_t)0x03)  /* I2C1 Alternate Function mapping       */
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC  Alternate Function mapping       */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF4  Alternate function AF4
 * @{
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_USART1          ((uint8_t)0x04)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF4_TIM22           ((uint8_t)0x04)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_TIM3            ((uint8_t)0x04)  /* TIM3 Alternate Function mapping     */
#define GPIO_AF4_I2C1            ((uint8_t)0x04)  /* I2C1 Alternate Function mapping     */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF5  Alternate function AF5
 * @{
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF5_USART1        ((uint8_t)0x05)  /* USART1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping      */
#define GPIO_AF5_I2C2          ((uint8_t)0x05)  /* I2C2 Alternate Function mapping      */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF6  Alternate function AF6
 * @{
 */
#define GPIO_AF6_USART4        ((uint8_t)0x06)  /* USART4 Alternate Function mapping    */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06)  /* LPUART1 Alternate Function mapping   */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06)  /* EVENTOUT Alternate Function mapping  */
#define GPIO_AF6_I2C1          ((uint8_t)0x06)  /* I2C1 Alternate Function mapping      */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping      */
#define GPIO_AF6_USART5        ((uint8_t)0x06)  /* USART5 Alternate Function mapping    */
#define GPIO_AF6_TIM21         ((uint8_t)0x06)  /* TIM21 Alternate Function mapping     */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF7  Alternate function AF7
 * @{
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07)  /* COMP2 Alternate Function mapping     */
#define GPIO_AF7_I2C3         ((uint8_t)0x07)  /* I2C3 Alternate Function mapping      */
#define GPIO_AF7_LPUART1      ((uint8_t)0x07)  /* LPUART1 Alternate Function mapping   */
/**
  * @}
  */

/**
  * @}
  */

/**
 * IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(__AF__) (((__AF__) == GPIO_AF0_EVENTOUT)  || ((__AF__) == GPIO_AF6_TIM21)    || \
                            ((__AF__) == GPIO_AF0_SPI1)      || ((__AF__) == GPIO_AF1_I2C1)     || \
                            ((__AF__) == GPIO_AF0_TIM21)     || ((__AF__) == GPIO_AF1_SPI2)     || \
                            ((__AF__) == GPIO_AF0_MCO)       || ((__AF__) == GPIO_AF1_TIM21)    || \
                            ((__AF__) == GPIO_AF0_SWDIO)     || ((__AF__) == GPIO_AF2_TIM2)     || \
                            ((__AF__) == GPIO_AF0_SWCLK)     || ((__AF__) == GPIO_AF2_TIM3)     || \
                            ((__AF__) == GPIO_AF0_USART1)    || ((__AF__) == GPIO_AF2_USB)      || \
                            ((__AF__) == GPIO_AF0_SPI2)      || ((__AF__) == GPIO_AF2_EVENTOUT) || \
                            ((__AF__) == GPIO_AF0_LPTIM1)    || ((__AF__) == GPIO_AF2_LPTIM1)   || \
                            ((__AF__) == GPIO_AF0_TIM2)      || ((__AF__) == GPIO_AF2_LPUART1)  || \
                            ((__AF__) == GPIO_AF0_LPUART1)   || ((__AF__) == GPIO_AF2_MCO)      || \
                            ((__AF__) == GPIO_AF0_USART2)    || ((__AF__) == GPIO_AF2_RTC)      || \
                            ((__AF__) == GPIO_AF0_USB)       || ((__AF__) == GPIO_AF2_SPI2)     || \
                            ((__AF__) == GPIO_AF0_TIM2)      || ((__AF__) == GPIO_AF2_USART5)   || \
                            ((__AF__) == GPIO_AF3_TSC)       || ((__AF__) == GPIO_AF2_SPI1)     || \
                            ((__AF__) == GPIO_AF3_EVENTOUT)  || ((__AF__) == GPIO_AF4_USART2)   || \
                            ((__AF__) == GPIO_AF3_I2C1)      || ((__AF__) == GPIO_AF4_LPUART1)  || \
                            ((__AF__) == GPIO_AF5_TIM21)     || ((__AF__) == GPIO_AF4_EVENTOUT) || \
                            ((__AF__) == GPIO_AF5_TIM2)      || ((__AF__) == GPIO_AF4_USART1)   || \
                            ((__AF__) == GPIO_AF5_USART1)    || ((__AF__) == GPIO_AF4_TIM22)    || \
                            ((__AF__) == GPIO_AF5_TIM22)     || ((__AF__) == GPIO_AF4_TIM3)     || \
                            ((__AF__) == GPIO_AF5_SPI2)      || ((__AF__) == GPIO_AF4_I2C1)     || \
                            ((__AF__) == GPIO_AF5_I2C2)      || ((__AF__) == GPIO_AF6_USART4)   || \
                            ((__AF__) == GPIO_AF7_COMP2)     || ((__AF__) == GPIO_AF6_LPUART1)  || \
                            ((__AF__) == GPIO_AF7_COMP1)     || ((__AF__) == GPIO_AF6_I2C1)     || \
                            ((__AF__) == GPIO_AF7_I2C3)      || ((__AF__) == GPIO_AF6_EVENTOUT) || \
                            ((__AF__) == GPIO_AF7_LPUART1)   || ((__AF__) == GPIO_AF6_I2C2)     || \
                            ((__AF__) == GPIO_AF6_USART5))

#define IS_GPIO_AF_AVAILABLE(__INSTANCE__,__AF__)  \
        ((((__INSTANCE__) == GPIOA) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)       ||   \
                                        ((__AF__) ==  GPIO_AF4_USART2)    ||   \
                                        ((__AF__) ==  GPIO_AF5_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF6_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF7_COMP1)))   ||   \
         (((__INSTANCE__) == GPIOB) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF1_I2C1)      ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)       ||   \
                                        ((__AF__) ==  GPIO_AF4_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF5_I2C2)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)    ||   \
                                        ((__AF__) ==  GPIO_AF7_LPUART1))) ||   \
         (((__INSTANCE__) == GPIOC) && (((__AF__) ==  GPIO_AF0_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)       ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)    ||   \
                                        ((__AF__) ==  GPIO_AF7_I2C3)))    ||   \
         (((__INSTANCE__) == GPIOD) && (((__AF__) ==  GPIO_AF0_TIM21)     ||   \
                                        ((__AF__) ==  GPIO_AF1_TIM21)     ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART5)))  ||   \
         (((__INSTANCE__) == GPIOE) && (((__AF__) ==  GPIO_AF0_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)))  ||   \
         (((__INSTANCE__) == GPIOH) && (((__AF__) ==  GPIO_AF0_USB))))


#endif /* (STM32L082xx) || (STM32L072xx) */


/*----------------------------------------------------------------------------*/
/*------------------------- STM32L081xx and STM32L071xx-----------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L081xx) || defined (STM32L071xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */


/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |        |USART2  |TIM2_TR |USART4  |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |        |USART2  |TIM21_TR|USART4  |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |        |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |        |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |        |        |        |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |        |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |TIM3_C1 |        |LPUART1 |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |TIM3_C2 |        |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |        |EVENTOUT|USART1  |        |        |I2C3    |
 * PA9 |MCO     |        |        |        |USART1  |        |I2C1    |I2C3    |
 * PA10|        |        |        |        |USART1  |        |I2C1    |        |
 * PA11|SPI1    |        |EVENTOUT|        |USART1  |        |I2C2    |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|        |USART1  |        |I2C2    |COMP2   |
 * PA13|SWDIO   |        |        |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |USART4  |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |TIM3_C3 |        |        |        |        |        |
 * PB1 |        |        |TIM3_C4 |        |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|        |        |        |        |I2C3    |
 * PB3 |SPI1    |        |TIM2_C2 |        |EVENTOUT|USART1  |USART5  |        |
 * PB4 |SPI1    |        |TIM3_C1 |        |TIM22_C1|USART1  |USART5  |I2C3    |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM3_C2 |USART1  |USART5  |        |
 *     |        |        |        |        |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|        |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|        |        |        |USART4  |        |
 * PB8 |        |        |        |        |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |        |LPUART1 |SPI2    |I2C2    |LPUART1 |
 * PB11|EVENTOUT|        |TIM2_C4 |        |LPUART1 |        |I2C2    |LPUART1 |
 * PB12|SPI2    |        |LPUART1 |        |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |MCO     |        |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |        |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|        |        |        |LPUART1 |I2C3    |
 * PC1 |LPTIM1_O|        |EVENTOUT|        |        |        |LPUART1 |I2C3    |
 * PC2 |LPTIM1_I|        |SPI2    |        |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |        |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART1 |        |        |        |        |        |
 * PC5 |        |        |LPUART1 |        |        |        |        |        |
 * PC6 |TIM22_C1|        |TIM3_C1 |        |        |        |        |        |
 * PC7 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PC8 |TIM22_TR|        |TIM3_C3 |        |        |        |        |        |
 * PC9 |TIM21_TR|        |        |        |        |        |        |I2C3    |
 *     |        |        |TIM3_C4 |        |        |        |        |        |
 * PC10|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC11|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC12|        |        |USART5  |        |        |        |USART4  |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD0 |TIM21_C1|SPI2    |        |        |        |        |        |        |
 * PD1 |        |SPI2    |        |        |        |        |        |        |
 * PD2 |LPUART1 |        |TIM3_TR |        |        |        |USART5  |        |
 * PD3 |USART2  |        |SPI2    |        |        |        |        |        |
 * PD4 |USART2  |SPI2    |        |        |        |        |        |        |
 * PD5 |USART2  |        |        |        |        |        |        |        |
 * PD6 |USART2  |        |        |        |        |        |        |        |
 * PD7 |USART2  |TIM21_C2|        |        |        |        |        |        |
 * PD8 |LPUART1 |        |        |        |        |        |        |        |
 * PD9 |LPUART1 |        |        |        |        |        |        |        |
 * PD10|        |        |        |        |        |        |        |        |
 * PD11|LPUART1 |        |        |        |        |        |        |        |
 * PD12|LPUART1 |        |        |        |        |        |        |        |
 * PD13|        |        |        |        |        |        |        |        |
 * PD14|        |        |        |        |        |        |        |        |
 * PD15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PE0 |        |        |EVENTOUT|        |        |        |        |        |
 * PE1 |        |        |EVENTOUT|        |        |        |        |        |
 * PE2 |        |        |TIM3_TR |        |        |        |        |        |
 * PE3 |TIM22_C1|        |TIM3_C1 |        |        |        |        |        |
 * PE4 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PE5 |TIM21_C1|        |TIM3_C3 |        |        |        |        |        |
 * PE6 |TIM21_C2|        |TIM3_C4 |        |        |        |        |        |
 * PE7 |        |        |        |        |        |        |USART5  |        |
 * PE8 |        |        |        |        |        |        |USART4  |        |
 * PE9 |TIM2_C1 |        |TIM2_TR |        |        |        |USART4  |        |
 * PE10|TIM2_C2 |        |        |        |        |        |USART5  |        |
 * PE11|TIM2_C3 |        |        |        |        |        |USART5  |        |
 * PE12|TIM2_C4 |        |SPI1    |        |        |        |        |        |
 * PE13|        |        |SPI1    |        |        |        |        |        |
 * PE14|        |        |SPI1    |        |        |        |        |        |
 * PE15|        |        |SPI1    |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |        |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 * PH9 |        |        |        |        |        |        |        |        |
 * PH10|        |        |        |        |        |        |        |        |
 *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/** @defgroup GPIOEx_Alternate_function_AF0  Alternate function AF0
 * @{
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_SPI2          ((uint8_t)0x00)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM22         ((uint8_t)0x00)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_TIM2          ((uint8_t)0x00)  /* TIM2 Alternate Function mapping     */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF1  Alternate function AF1
 * @{
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_TIM21         ((uint8_t)0x01)  /* TIM21 Alternate Function mapping */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF2  Alternate function AF2
 * @{
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_MCO           ((uint8_t)0x02)  /* MCO Alternate Function mapping      */
#define GPIO_AF2_RTC           ((uint8_t)0x02)  /* RTC_OUT Alternate Function mapping    */
#define GPIO_AF2_SPI2          ((uint8_t)0x02)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_USART5        ((uint8_t)0x02)  /* USART5 Alternate Function mapping   */
#define GPIO_AF2_SPI1          ((uint8_t)0x02)  /* SPI1 Alternate Function mapping       */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF3  Alternate function AF3
 * @{
 */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF3_I2C1          ((uint8_t)0x03)  /* I2C1 Alternate Function mapping */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF4  Alternate function AF4
 * @{
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_USART1          ((uint8_t)0x04)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF4_TIM22           ((uint8_t)0x04)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_TIM3            ((uint8_t)0x04)  /* TIM3 Alternate Function mapping    */
#define GPIO_AF4_I2C1            ((uint8_t)0x04)  /* I2C1 Alternate Function mapping    */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF5  Alternate function AF5
 * @{
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF5_USART1        ((uint8_t)0x05)  /* USART1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF5_I2C2          ((uint8_t)0x05)  /* I2C2 Alternate Function mapping       */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF6  Alternate function AF6
 * @{
 */
#define GPIO_AF6_USART4        ((uint8_t)0x06)  /* USART4 Alternate Function mapping   */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06)  /* EVENTOUT Alternate Function mapping  */
#define GPIO_AF6_I2C1          ((uint8_t)0x06)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping  */
#define GPIO_AF6_USART5        ((uint8_t)0x06)  /* USART5 Alternate Function mapping   */
#define GPIO_AF6_TIM21         ((uint8_t)0x06)  /* TIM21 Alternate Function mapping    */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF7  Alternate function AF7
 * @{
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07)  /* COMP2 Alternate Function mapping     */
#define GPIO_AF7_I2C3         ((uint8_t)0x07)  /* I2C3 Alternate Function mapping     */
#define GPIO_AF7_LPUART1      ((uint8_t)0x07)  /* LPUART1 Alternate Function mapping     */
/**
  * @}
  */

/**
  * @}
  */

   /**
 * IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(__AF__) (((__AF__) == GPIO_AF0_EVENTOUT) || ((__AF__) == GPIO_AF7_LPUART1)  || \
                            ((__AF__) == GPIO_AF0_SPI1)     || ((__AF__) == GPIO_AF1_I2C1)     || \
                            ((__AF__) == GPIO_AF0_TIM21)    || ((__AF__) == GPIO_AF1_SPI2)     || \
                            ((__AF__) == GPIO_AF0_MCO)      || ((__AF__) == GPIO_AF1_TIM21)    || \
                            ((__AF__) == GPIO_AF0_SWDIO)    || ((__AF__) == GPIO_AF2_TIM2)     || \
                            ((__AF__) == GPIO_AF0_SWCLK)    || ((__AF__) == GPIO_AF2_TIM3)     || \
                            ((__AF__) == GPIO_AF0_USART1)   || ((__AF__) == GPIO_AF6_TIM21)    || \
                            ((__AF__) == GPIO_AF0_SPI2)     || ((__AF__) == GPIO_AF2_EVENTOUT) || \
                            ((__AF__) == GPIO_AF0_LPTIM1)   || ((__AF__) == GPIO_AF2_LPTIM1)   || \
                            ((__AF__) == GPIO_AF0_TIM2)     || ((__AF__) == GPIO_AF2_LPUART1)  || \
                            ((__AF__) == GPIO_AF0_LPUART1)  || ((__AF__) == GPIO_AF2_MCO)      || \
                            ((__AF__) == GPIO_AF0_USART2)   || ((__AF__) == GPIO_AF2_RTC)      || \
                            ((__AF__) == GPIO_AF2_SPI2)     || ((__AF__) == GPIO_AF6_USART5)   || \
                            ((__AF__) == GPIO_AF0_TIM2)     || ((__AF__) == GPIO_AF2_USART5)   || \
                            ((__AF__) == GPIO_AF2_SPI1)     || ((__AF__) == GPIO_AF6_I2C2)     || \
                            ((__AF__) == GPIO_AF3_EVENTOUT) || ((__AF__) == GPIO_AF4_USART2)   || \
                            ((__AF__) == GPIO_AF3_I2C1)     || ((__AF__) == GPIO_AF4_LPUART1)  || \
                            ((__AF__) == GPIO_AF5_TIM21)    || ((__AF__) == GPIO_AF4_EVENTOUT) || \
                            ((__AF__) == GPIO_AF5_TIM2)     || ((__AF__) == GPIO_AF4_USART1)   || \
                            ((__AF__) == GPIO_AF5_USART1)   || ((__AF__) == GPIO_AF4_TIM22)    || \
                            ((__AF__) == GPIO_AF5_TIM22)    || ((__AF__) == GPIO_AF4_TIM3)     || \
                            ((__AF__) == GPIO_AF5_SPI2)     || ((__AF__) == GPIO_AF4_I2C1)     || \
                            ((__AF__) == GPIO_AF5_I2C2)     || ((__AF__) == GPIO_AF6_USART4)   || \
                            ((__AF__) == GPIO_AF7_COMP2)    || ((__AF__) == GPIO_AF6_LPUART1)  || \
                            ((__AF__) == GPIO_AF7_COMP1)    || ((__AF__) == GPIO_AF6_I2C1)     || \
                            ((__AF__) == GPIO_AF7_I2C3)     || ((__AF__) == GPIO_AF6_EVENTOUT))


#define IS_GPIO_AF_AVAILABLE(__INSTANCE__,__AF__)  \
        ((((__INSTANCE__) == GPIOA) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF4_USART2)    ||   \
                                        ((__AF__) ==  GPIO_AF5_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)    ||   \
                                        ((__AF__) ==  GPIO_AF7_COMP1)))   ||   \
         (((__INSTANCE__) == GPIOB) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF1_I2C1)      ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_I2C1)      ||   \
                                        ((__AF__) ==  GPIO_AF4_I2C1)      ||   \
                                        ((__AF__) ==  GPIO_AF5_I2C2)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4)    ||   \
                                        ((__AF__) ==  GPIO_AF7_LPUART1))) ||   \
         (((__INSTANCE__) == GPIOC) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF6_LPUART1)   ||   \
                                        ((__AF__) ==  GPIO_AF7_I2C3)))    ||   \
         (((__INSTANCE__) == GPIOD) && (((__AF__) ==  GPIO_AF0_LPUART1)   ||   \
                                        ((__AF__) ==  GPIO_AF1_SPI2)      ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART5)))  ||   \
         (((__INSTANCE__) == GPIOE) && (((__AF__) ==  GPIO_AF0_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM3)      ||   \
                                        ((__AF__) ==  GPIO_AF6_USART4))))


#endif /* (STM32L081xx) || (STM32L071xx) */

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L053xx/STM32L063xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L053xx) || defined (STM32L063xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |TSC     |USART2  |TIM2_TR |        |COMP1   |
 * PA1 |EVENTOUT|LCD     |TIM2_C2 |TSC     |USART2  |TIM21_TR|        |        |
 * PA2 |TIM21_C1|LCD     |TIM2_C3 |TSC     |USART2  |        |        |COMP2   |
 * PA3 |TIM21_C2|LCD     |TIM2_C4 |TSC     |USART2  |        |        |        |
 * PA4 |SPI1    |        |        |TSC     |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |TSC     |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |LCD     |        |TSC     |LPUART  |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |LCD     |        |TSC     |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |LCD     |USB     |EVENTOUT|USART1  |        |        |        |
 * PA9 |MCO     |LCD     |        |TSC     |USART1  |        |        |        |
 * PA10|        |LCD     |        |TSC     |USART1  |        |        |        |
 * PA11|SPI1    |        |EVENTOUT|TSC     |USART1  |        |        |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|TSC     |USART1  |        |        |COMP2   |
 * PA13|SWDIO   |        |USB     |        |        |        |        |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |        |        |
 * PA15|SPI1    |LCD     |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |        |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|LCD     |        |TSC     |        |        |        |        |
 * PB1 |        |LCD     |        |TSC     |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|TSC     |        |        |        |        |
 * PB3 |SPI1    |LCD     |TIM2_C2 |TSC     |EVENTOUT|        |        |        |
 * PB4 |SPI1    |LCD     |EVENTOUT|TSC     |TIM22_C1|        |        |        |
 * PB5 |SPI1    |LCD     |LPTIM1_I|I2C1    |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|TSC     |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|TSC     |        |        |        |        |
 * PB8 |        |LCD     |        |TSC     |I2C1    |        |        |        |
 * PB9 |        |LCD     |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |LCD     |TIM2_C3 |TSC     |LPUART1 |SPI2    |I2C2    |        |
 * PB11|EVENTOUT|LCD     |TIM2_C4 |TSC     |LPUART1 |        |I2C2    |        |
 * PB12|SPI2    |LCD     |LPUART1 |TSC     |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |LCD     |        |TSC     |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |LCD     |RTC     |TSC     |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |LCD     |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|LCD     |EVENTOUT|TSC     |        |        |        |        |
 * PC1 |LPTIM1_O|LCD     |EVENTOUT|TSC     |        |        |        |        |
 * PC2 |LPTIM1_I|LCD     |SPI2    |TSC     |        |        |        |        |
 * PC3 |LPTIM1_T|LCD     |SPI2    |TSC     |        |        |        |        |
 * PC4 |EVENTOUT|LCD     |LPUART  |        |        |        |        |        |
 * PC5 |        |LCD     |LPUART  |TSC     |        |        |        |        |
 * PC6 |TIM22_C1|LCD     |        |TSC     |        |        |        |        |
 * PC7 |TIM22_C2|LCD     |        |TSC     |        |        |        |        |
 * PC8 |TIM22_TR|LCD     |        |TSC     |        |        |        |        |
 * PC9 |TIM21_TR|LCD     |USB     |TSC     |        |        |        |        |
 * PC10|LPUART  |LCD     |        |        |        |        |        |        |
 * PC11|LPUART  |LCD     |        |        |        |        |        |        |
 * PC12|        |LCD     |        |        |        |        |        |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD2 |LPUART  |LCD     |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |USB     |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 *  *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/** @defgroup GPIOEx_Alternate_function_AF0  Alternate function AF0
 * @{
 */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_SPI2          ((uint8_t)0x00)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USB           ((uint8_t)0x00)  /* USB Alternate Function mapping      */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TSC           ((uint8_t)0x00)  /* TSC Alternate Function mapping      */
#define GPIO_AF0_TIM2          ((uint8_t)0x00)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_TIM21         ((uint8_t)0x00)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_TIM22         ((uint8_t)0x00)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /* SWCLK Alternate Function mapping    */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF1  Alternate function AF1
 * @{
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01)  /* SPI1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_I2C1          ((uint8_t)0x01)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF1_LCD           ((uint8_t)0x01)  /* LCD Alternate Function mapping   */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF2  Alternate function AF2
 * @{
 */
#define GPIO_AF2_SPI2          ((uint8_t)0x02)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_USB           ((uint8_t)0x02)  /* USB Alternate Function mapping        */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC           ((uint8_t)0x02)  /* RTC_OUT Alternate Function mapping    */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF3  Alternate function AF3
 * @{
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC  Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03)  /* EVENTOUT Alternate Function mapping */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF4  Alternate function AF4
 * @{
 */
#define GPIO_AF4_I2C1            ((uint8_t)0x04)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART1          ((uint8_t)0x04)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_USART2          ((uint8_t)0x04)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_TIM22           ((uint8_t)0x04)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04)  /* EVENTOUT Alternate Function mapping */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF5  Alternate function AF5
 * @{
 */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C2          ((uint8_t)0x05)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF5_TIM2          ((uint8_t)0x05)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05)  /* TIM22 Alternate Function mapping    */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF6  Alternate function AF6
 * @{
 */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping      */
#define GPIO_AF6_TIM21         ((uint8_t)0x06)  /* TIM21 Alternate Function mapping     */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06)  /* EVENTOUT Alternate Function mapping  */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF7  Alternate function AF7
 * @{
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07)  /* COMP2 Alternate Function mapping     */
/**
  * @}
  */

/**
  * @}
  */



#define IS_GPIO_AF(__AF__) (((__AF__) == GPIO_AF0_SPI1)     || ((__AF__) == GPIO_AF2_SPI2)     || \
                            ((__AF__) == GPIO_AF0_SPI2)     || ((__AF__) == GPIO_AF2_LPUART1)  || \
                            ((__AF__) == GPIO_AF0_USART1)   || ((__AF__) == GPIO_AF2_USB)      || \
                            ((__AF__) == GPIO_AF0_USART2)   || ((__AF__) == GPIO_AF2_LPTIM1)   || \
                            ((__AF__) == GPIO_AF0_LPUART1)  || ((__AF__) == GPIO_AF2_TIM2)     || \
                            ((__AF__) == GPIO_AF0_USB)      || ((__AF__) == GPIO_AF3_TSC)      || \
                            ((__AF__) == GPIO_AF0_LPTIM1)   || ((__AF__) == GPIO_AF2_EVENTOUT) || \
                            ((__AF__) == GPIO_AF0_TSC)      || ((__AF__) == GPIO_AF2_RTC) || \
                            ((__AF__) == GPIO_AF3_I2C1)     || ((__AF__) == GPIO_AF7_COMP2)    || \
                            ((__AF__) == GPIO_AF0_TIM22)    || ((__AF__) == GPIO_AF3_EVENTOUT) || \
                            ((__AF__) == GPIO_AF0_EVENTOUT) || ((__AF__) == GPIO_AF4_I2C1)     || \
                            ((__AF__) == GPIO_AF0_MCO)      || ((__AF__) == GPIO_AF4_USART1)   || \
                            ((__AF__) == GPIO_AF0_SWDIO)    || ((__AF__) == GPIO_AF0_SWCLK)    || \
                            ((__AF__) == GPIO_AF1_SPI1)     || ((__AF__) == GPIO_AF4_USART2)   || \
                            ((__AF__) == GPIO_AF1_SPI2)     || ((__AF__) == GPIO_AF4_LPUART1)  || \
                            ((__AF__) == GPIO_AF7_COMP2)    || ((__AF__) == GPIO_AF4_TIM22)    || \
                            ((__AF__) == GPIO_AF1_I2C1)     || ((__AF__) == GPIO_AF4_EVENTOUT) || \
                            ((__AF__) == GPIO_AF1_LCD)      || ((__AF__) == GPIO_AF5_SPI2)     || \
                            ((__AF__) == GPIO_AF5_I2C2)     || ((__AF__) == GPIO_AF5_TIM2)     || \
                            ((__AF__) == GPIO_AF5_TIM21)    || ((__AF__) == GPIO_AF5_TIM22)    || \
                            ((__AF__) == GPIO_AF6_I2C2)     || ((__AF__) == GPIO_AF6_TIM21)    || \
                            ((__AF__) == GPIO_AF6_EVENTOUT) || ((__AF__) == GPIO_AF7_COMP1))



#define IS_GPIO_AF_AVAILABLE(__INSTANCE__,__AF__)  \
        ((((__INSTANCE__) == GPIOA) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)       ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)       ||   \
                                        ((__AF__) ==  GPIO_AF4_USART2)    ||   \
                                        ((__AF__) ==  GPIO_AF5_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF6_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF7_COMP1)))   ||   \
         (((__INSTANCE__) == GPIOB) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)       ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)       ||   \
                                        ((__AF__) ==  GPIO_AF4_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF5_I2C2)      ||   \
                                        ((__AF__) ==  GPIO_AF6_TIM21)))   ||   \
         (((__INSTANCE__) == GPIOC) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)       ||   \
                                        ((__AF__) ==  GPIO_AF2_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)))     ||   \
         (((__INSTANCE__) == GPIOD) && (((__AF__) ==  GPIO_AF0_LPUART1)   ||   \
                                        ((__AF__) ==  GPIO_AF1_LCD)))     ||   \
         (((__INSTANCE__) == GPIOH) && (((__AF__) ==  GPIO_AF0_USB))))


#endif /* STM32L053xx || STM32L063xx */
/*------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L052xx/STM32L062xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L052xx) || defined (STM32L062xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |TSC     |USART2  |TIM2_TR |        |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |TSC     |USART2  |TIM21_TR|        |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |TSC     |USART2  |        |        |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |TSC     |USART2  |        |        |        |
 * PA4 |SPI1    |        |        |TSC     |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |TSC     |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |        |TSC     |LPUART  |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |        |TSC     |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |USB     |EVENTOUT|USART1  |        |        |        |
 * PA9 |MCO     |        |        |TSC     |USART1  |        |        |        |
 * PA10|        |        |        |TSC     |USART1  |        |        |        |
 * PA11|SPI1    |        |EVENTOUT|TSC     |USART1  |        |        |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|TSC     |USART1  |        |        |COMP2   |
 * PA13|SWDIO   |        |USB     |        |        |        |        |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |        |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |        |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |        |TSC     |        |        |        |        |
 * PB1 |        |        |        |TSC     |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|TSC     |        |        |        |        |
 * PB3 |SPI1    |        |TIM2_C2 |TSC     |EVENTOUT|        |        |        |
 * PB4 |SPI1    |        |EVENTOUT|TSC     |TIM22_C1|        |        |        |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|TSC     |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|TSC     |        |        |        |        |
 * PB8 |        |        |        |TSC     |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |TSC     |LPUART1 |SPI2    |I2C2    |        |
 * PB11|EVENTOUT|        |TIM2_C4 |TSC     |LPUART1 |        |I2C2    |        |
 * PB12|SPI2    |        |LPUART1 |TSC     |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |        |TSC     |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |TSC     |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|TSC     |        |        |        |        |
 * PC1 |LPTIM1_O|        |EVENTOUT|TSC     |        |        |        |        |
 * PC2 |LPTIM1_I|        |SPI2    |TSC     |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |TSC     |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART  |        |        |        |        |        |
 * PC5 |        |        |LPUART  |TSC     |        |        |        |        |
 * PC6 |TIM22_C1|        |        |TSC     |        |        |        |        |
 * PC7 |TIM22_C2|        |        |TSC     |        |        |        |        |
 * PC8 |TIM22_TR|        |        |TSC     |        |        |        |        |
 * PC9 |TIM21_TR|        |USB     |TSC     |        |        |        |        |
 * PC10|LPUART  |        |        |        |        |        |        |        |
 * PC11|LPUART  |        |        |        |        |        |        |        |
 * PC12|        |        |        |        |        |        |        |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD2 |LPUART  |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |USB     |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 *  *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/** @defgroup GPIOEx_Alternate_function_AF0  Alternate function AF0
 * @{
 */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_SPI2          ((uint8_t)0x00)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USB           ((uint8_t)0x00)  /* USB Alternate Function mapping      */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TSC           ((uint8_t)0x00)  /* TSC Alternate Function mapping      */
#define GPIO_AF0_TIM2          ((uint8_t)0x00)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_TIM21         ((uint8_t)0x00)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_TIM22         ((uint8_t)0x00)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /* SWCLK Alternate Function mapping    */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF1  Alternate function AF1
 * @{
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01)  /* SPI1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_I2C1          ((uint8_t)0x01)  /* I2C1 Alternate Function mapping  */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF2  Alternate function AF2
 * @{
 */
#define GPIO_AF2_SPI2          ((uint8_t)0x02)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_USB           ((uint8_t)0x02)  /* USB Alternate Function mapping        */
#define GPIO_AF2_LPTIM1         ((uint8_t)0x02) /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC      ((uint8_t)0x02)  /* RTC_OUT Alternate Function mapping    */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF3  Alternate function AF3
 * @{
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_TSC           ((uint8_t)0x03)  /* TSC  Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03)  /* EVENTOUT Alternate Function mapping */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF4  Alternate function AF4
 * @{
 */
#define GPIO_AF4_I2C1            ((uint8_t)0x04)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART1          ((uint8_t)0x04)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_USART2          ((uint8_t)0x04)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_TIM22           ((uint8_t)0x04)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04)  /* EVENTOUT Alternate Function mapping */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF5  Alternate function AF5
 * @{
 */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C2          ((uint8_t)0x05)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF5_TIM2          ((uint8_t)0x05)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05)  /* TIM22 Alternate Function mapping    */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF6  Alternate function AF6
 * @{
 */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping      */
#define GPIO_AF6_TIM21         ((uint8_t)0x06)  /* TIM21 Alternate Function mapping     */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06)  /* EVENTOUT Alternate Function mapping  */
/**
  * @}
  */

   /** @defgroup GPIOEx_Alternate_function_AF7  Alternate function AF7
 * @{
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07)  /* COMP2 Alternate Function mapping     */
/**
  * @}
  */

/**
  * @}
  */


#define IS_GPIO_AF(__AF__) (((__AF__) == GPIO_AF0_SPI1)     || ((__AF__) == GPIO_AF2_SPI2)        || \
                            ((__AF__) == GPIO_AF0_SPI2)     || ((__AF__) == GPIO_AF2_LPUART1)     || \
                            ((__AF__) == GPIO_AF0_USART1)   || ((__AF__) == GPIO_AF2_USB)         || \
                            ((__AF__) == GPIO_AF0_USART2)   || ((__AF__) == GPIO_AF2_LPTIM1)      || \
                            ((__AF__) == GPIO_AF0_LPUART1)  || ((__AF__) == GPIO_AF2_TIM2)        || \
                            ((__AF__) == GPIO_AF0_USB)      || ((__AF__) == GPIO_AF4_TIM22)       || \
                            ((__AF__) == GPIO_AF0_LPTIM1)   || ((__AF__) == GPIO_AF2_EVENTOUT)    || \
                            ((__AF__) == GPIO_AF0_TSC)      || ((__AF__) == GPIO_AF2_RTC)    || \
                            ((__AF__) == GPIO_AF0_TIM2)     || ((__AF__) == GPIO_AF3_I2C1)        || \
                            ((__AF__) == GPIO_AF0_TIM21)    || ((__AF__) == GPIO_AF3_TSC)         || \
                            ((__AF__) == GPIO_AF0_TIM22)    || ((__AF__) == GPIO_AF3_EVENTOUT)    || \
                            ((__AF__) == GPIO_AF0_EVENTOUT) || ((__AF__) == GPIO_AF4_I2C1)        || \
                            ((__AF__) == GPIO_AF0_MCO)      || ((__AF__) == GPIO_AF4_USART1)      || \
                            ((__AF__) == GPIO_AF0_SWDIO)    || ((__AF__) == GPIO_AF0_SWCLK)       || \
                            ((__AF__) == GPIO_AF1_SPI1)     || ((__AF__) == GPIO_AF4_USART2)      || \
                            ((__AF__) == GPIO_AF1_SPI2)     || ((__AF__) == GPIO_AF4_LPUART1)     || \
                            ((__AF__) == GPIO_AF1_I2C1)     || ((__AF__) == GPIO_AF4_EVENTOUT)    || \
                            ((__AF__) == GPIO_AF6_EVENTOUT) || ((__AF__) == GPIO_AF5_SPI2)        || \
                            ((__AF__) == GPIO_AF5_I2C2)     || ((__AF__) == GPIO_AF5_TIM2)        || \
                            ((__AF__) == GPIO_AF5_TIM21)    || ((__AF__) == GPIO_AF5_TIM22)       || \
                            ((__AF__) == GPIO_AF6_I2C2)     || ((__AF__) == GPIO_AF6_TIM21)       || \
                            ((__AF__) == GPIO_AF7_COMP2)    || ((__AF__) == GPIO_AF7_COMP1))


#define IS_GPIO_AF_AVAILABLE(__INSTANCE__,__AF__)  \
        ((((__INSTANCE__) == GPIOA) && (((__AF__) ==  GPIO_AF0_EVENTOUT)   ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)       ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)        ||   \
                                        ((__AF__) ==  GPIO_AF4_USART2)     ||   \
                                        ((__AF__) ==  GPIO_AF5_TIM22)      ||   \
                                        ((__AF__) ==  GPIO_AF6_EVENTOUT)   ||   \
                                        ((__AF__) ==  GPIO_AF7_COMP1)))    ||   \
         (((__INSTANCE__) == GPIOB) && (((__AF__) ==  GPIO_AF0_EVENTOUT)   ||   \
                                        ((__AF__) ==  GPIO_AF1_I2C1)       ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)       ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)        ||   \
                                        ((__AF__) ==  GPIO_AF4_LPUART1)    ||   \
                                        ((__AF__) ==  GPIO_AF5_I2C2)       ||   \
                                        ((__AF__) ==  GPIO_AF6_EVENTOUT))) ||   \
         (((__INSTANCE__) == GPIOC) && (((__AF__) ==  GPIO_AF0_EVENTOUT)   ||   \
                                        ((__AF__) ==  GPIO_AF2_EVENTOUT)   ||   \
                                        ((__AF__) ==  GPIO_AF3_TSC)))      ||   \
         (((__INSTANCE__) == GPIOD) && (((__AF__) ==  GPIO_AF0_LPUART1)))  ||   \
         (((__INSTANCE__) == GPIOH) && (((__AF__) ==  GPIO_AF0_USB))))


#endif /* STM32L052xx || STM32L062xx */
/*------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L051xx/STM32L061xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L051xx)|| defined (STM32L061xx)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |        |USART2  |TIM2_TR |        |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |        |USART2  |TIM21_TR|        |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |        |USART2  |        |        |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |        |USART2  |        |        |        |
 * PA4 |SPI1    |        |        |        |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |        |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |        |        |LPUART  |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |        |        |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |        |EVENTOUT|USART1  |        |        |        |
 * PA9 |MCO     |        |        |        |USART1  |        |        |        |
 * PA10|        |        |        |        |USART1  |        |        |        |
 * PA11|SPI1    |        |EVENTOUT|        |USART1  |        |        |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|        |USART1  |        |        |COMP2   |
 * PA13|SWDIO   |        |        |        |        |        |        |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |        |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |        |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |        |        |        |        |        |        |
 * PB1 |        |        |        |        |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|        |        |        |        |        |
 * PB3 |SPI1    |        |TIM2_C2 |        |EVENTOUT|        |        |        |
 * PB4 |SPI1    |        |EVENTOUT|        |TIM22_C1|        |        |        |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|        |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|        |        |        |        |        |
 * PB8 |        |        |        |        |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |        |LPUART1 |SPI2    |I2C2    |        |
 * PB11|EVENTOUT|        |TIM2_C4 |        |LPUART1 |        |I2C2    |        |
 * PB12|SPI2    |        |LPUART1 |        |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |        |        |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |        |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|        |        |        |        |        |
 * PC1 |LPTIM1_O|        |EVENTOUT|        |        |        |        |        |
 * PC2 |LPTIM1_I|        |SPI2    |        |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |        |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART  |        |        |        |        |        |
 * PC5 |        |        |LPUART  |        |        |        |        |        |
 * PC6 |TIM22_C1|        |        |        |        |        |        |        |
 * PC7 |TIM22_C2|        |        |        |        |        |        |        |
 * PC8 |TIM22_TR|        |        |        |        |        |        |        |
 * PC9 |TIM21_TR|        |        |        |        |        |        |        |
 * PC10|LPUART  |        |        |        |        |        |        |        |
 * PC11|LPUART  |        |        |        |        |        |        |        |
 * PC12|        |        |        |        |        |        |        |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD2 |LPUART  |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |        |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 *  *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/** @defgroup GPIOEx_Alternate_function_AF0  Alternate function AF0
 * @{
 */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_SPI2          ((uint8_t)0x00)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_LPTIM1         ((uint8_t)0x00) /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM2          ((uint8_t)0x00)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_TIM21         ((uint8_t)0x00)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_TIM22         ((uint8_t)0x00)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /* SWCLK Alternate Function mapping    */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF1  Alternate function AF1
 * @{
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01)  /* SPI1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_I2C1          ((uint8_t)0x01)  /* I2C1 Alternate Function mapping  */
/**
  * @}
  */

 /** @defgroup GPIOEx_Alternate_function_AF2  Alternate function AF2
 * @{
 */
#define GPIO_AF2_SPI2          ((uint8_t)0x02)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_USB           ((uint8_t)0x02)  /* USB Alternate Function mapping        */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /* LPTIM1 Alternate Function mapping      */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC      ((uint8_t)0x02)  /* RTC_OUT Alternate Function mapping    */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF3  Alternate function AF3
 * @{
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03)  /* EVENTOUT Alternate Function mapping */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF4  Alternate function AF4
 * @{
 */
#define GPIO_AF4_I2C1            ((uint8_t)0x04)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART1          ((uint8_t)0x04)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_USART2          ((uint8_t)0x04)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_TIM22           ((uint8_t)0x04)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04)  /* EVENTOUT Alternate Function mapping */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF5  Alternate function AF5
 * @{
 */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C2          ((uint8_t)0x05)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF5_TIM2          ((uint8_t)0x05)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05)  /* TIM22 Alternate Function mapping    */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF6  Alternate function AF6
 * @{
 */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /* I2C2 Alternate Function mapping      */
#define GPIO_AF6_TIM21         ((uint8_t)0x06)  /* TIM21 Alternate Function mapping     */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06)  /* EVENTOUT Alternate Function mapping  */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF7  Alternate function AF7
 * @{
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07)  /* COMP2 Alternate Function mapping     */
/**
  * @}
  */

/**
  * @}
  */


#define IS_GPIO_AF(__AF__) (((__AF__) == GPIO_AF0_SPI1)     || ((__AF__) == GPIO_AF2_SPI2)     || \
                            ((__AF__) == GPIO_AF0_SPI2)     || ((__AF__) == GPIO_AF2_LPUART1)  || \
                            ((__AF__) == GPIO_AF0_USART1)   || ((__AF__) == GPIO_AF7_COMP1)    || \
                            ((__AF__) == GPIO_AF0_USART2)   || ((__AF__) == GPIO_AF2_LPTIM1)   || \
                            ((__AF__) == GPIO_AF0_LPUART1)  || ((__AF__) == GPIO_AF2_TIM2)     || \
                            ((__AF__) == GPIO_AF0_LPTIM1)   || ((__AF__) == GPIO_AF2_EVENTOUT) || \
                            ((__AF__) == GPIO_AF2_RTC) || ((__AF__) == GPIO_AF4_TIM22)    || \
                            ((__AF__) == GPIO_AF0_TIM2)     || ((__AF__) == GPIO_AF3_I2C1)     || \
                            ((__AF__) == GPIO_AF0_TIM21)    || ((__AF__) == GPIO_AF7_COMP2)    || \
                            ((__AF__) == GPIO_AF0_TIM22)    || ((__AF__) == GPIO_AF3_EVENTOUT) || \
                            ((__AF__) == GPIO_AF0_EVENTOUT) || ((__AF__) == GPIO_AF4_I2C1)     || \
                            ((__AF__) == GPIO_AF0_MCO)      || ((__AF__) == GPIO_AF4_USART1)   || \
                            ((__AF__) == GPIO_AF0_SWDIO)    || ((__AF__) == GPIO_AF0_SWCLK)    || \
                            ((__AF__) == GPIO_AF1_SPI1)     || ((__AF__) == GPIO_AF4_USART2)   || \
                            ((__AF__) == GPIO_AF1_SPI2)     || ((__AF__) == GPIO_AF4_LPUART1)  || \
                            ((__AF__) == GPIO_AF1_I2C1)     || ((__AF__) == GPIO_AF4_EVENTOUT) || \
                            ((__AF__) == GPIO_AF6_EVENTOUT) || ((__AF__) == GPIO_AF5_SPI2)     || \
                            ((__AF__) == GPIO_AF5_I2C2)     || ((__AF__) == GPIO_AF5_TIM2)     || \
                            ((__AF__) == GPIO_AF5_TIM21)    || ((__AF__) == GPIO_AF5_TIM22)    || \
                            ((__AF__) == GPIO_AF6_I2C2)     || ((__AF__) == GPIO_AF6_TIM21))

                         

   #define IS_GPIO_AF_AVAILABLE(__INSTANCE__,__AF__)  \
        ((((__INSTANCE__) == GPIOA) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF4_USART2)    ||   \
                                        ((__AF__) ==  GPIO_AF5_TIM22)     ||   \
                                        ((__AF__) ==  GPIO_AF6_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF7_COMP2)))   ||   \
         (((__INSTANCE__) == GPIOB) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF1_I2C1)      ||   \
                                        ((__AF__) ==  GPIO_AF2_TIM2)      ||   \
                                        ((__AF__) ==  GPIO_AF3_I2C1)      ||   \
                                        ((__AF__) ==  GPIO_AF4_LPUART1)   ||   \
                                        ((__AF__) ==  GPIO_AF5_I2C2)      ||   \
                                        ((__AF__) ==  GPIO_AF6_TIM21)))   ||   \
         (((__INSTANCE__) == GPIOC) && (((__AF__) ==  GPIO_AF0_EVENTOUT)  ||   \
                                        ((__AF__) ==  GPIO_AF2_LPUART1))) ||   \
         (((__INSTANCE__) == GPIOD) && (((__AF__) ==  GPIO_AF0_LPUART1))))


#endif /* STM32L051xx/STM32L061xx*/
/*------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L031xx/STM32L041xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L031xx)|| defined (STM32L041xx)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |LPTIM1  |TIM2_C1 |        |USART2  |TIM2_TR |        |COMP1   |
 * PA1 |EVENTOUT|LPTIM1  |TIM2_C2 |I2C1    |USART2  |TIM21_TR|        |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |        |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |        |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |LPTIM1  |        |        |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |LPTIM1  |TIM2_TR |        |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |LPTIM1  |        |        |LPUART  |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |LPTIM1  |        |        |USART2  |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |LPTIM1  |EVENTOUT|USART2  |        |        |        |
 * PA9 |MCO     |I2C1    |        |        |USART2  |TIM22_C1|        |        |
 * PA10|        |I2C1    |        |        |USART2  |TIM22_C2|        |        |
 * PA11|SPI1    |        |EVENTOUT|        |USART2  |        |        |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|        |USART2  |        |        |COMP2   |
 * PA13|SWDIO   |LPTIM1  |        |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |LPTIM1  |        |I2C1    |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |        |        |
 *_____________________________________________________________________________|
 * PB0 |EVENTOUT|SPI1    |        |        |USART2  |TIM2_C3 |        |        |
 * PB1 |USART2  |SPI1    |        |        |LPUART1 |TIM2_C4 |        |        |
 * PB2 |        |        |LPTIM1_O|        |        |        |        |        |
 * PB3 |SPI1    |        |TIM2_C2 |        |EVENTOUT|        |        |        |
 * PB4 |SPI1    |        |EVENTOUT|        |TIM22_C1|        |        |        |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM22_C2|        |        |        |
 * PB6 |USART2  |I2C1    |LPTIM1_T|        |        |        |        |        |
 * PB7 |USART2  |I2C1    |LPTIM1_I|        |        |        |        |        |
 * PB8 |        |        |        |        |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |        |        |        |
 * PB10|        |        |TIM2_C3 |        |        |        |LPUART1 |        |
 * PB11|EVENTOUT|        |TIM2_C4 |        |        |        |LPUART1 |        |
 * PB12|SPI2    |        |        |        |        |        |EVENTOUT|        |
 * PB13|SPI2    |        |MCO     |        |        |TIM21_C1|LPUART1 |        |
 * PB14|SPI2    |        |RTC     |        |        |TIM21_C2|LPUART1 |        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *_____________________________________________________________________________|
 * PC0 |LPTIM1_I|        |EVENTOUT|        |        |        |LPUART1 |        |
 * PC1 |        |        |        |        |        |        |        |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *_____________________________________________________________________________|
 * PH0 |        |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 *_____________________________________________________________________________|
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/** @defgroup GPIOEx_Alternate_function_AF0  Alternate function AF0
 * @{
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00)  /* SWCLK Alternate Function mapping    */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF1  Alternate function AF1
 * @{
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01)  /* SPI1 Alternate Function mapping   */
#define GPIO_AF1_I2C1          ((uint8_t)0x01)  /* I2C1 Alternate Function mapping   */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)  /* LPTIM1 Alternate Function mapping */
/**
  * @}
  */

 /** @defgroup GPIOEx_Alternate_function_AF2  Alternate function AF2
 * @{
 */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC      ((uint8_t)0x02)  /* RTC_OUT Alternate Function mapping    */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF3  Alternate function AF3
 * @{
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03)  /* EVENTOUT Alternate Function mapping  */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF4  Alternate function AF4
 * @{
 */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART2        ((uint8_t)0x04)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1       ((uint8_t)0x04)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_TIM22         ((uint8_t)0x04)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_EVENTOUT      ((uint8_t)0x04)  /* EVENTOUT Alternate Function mapping  */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF5  Alternate function AF5
 * @{
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05)  /* TIM22 Alternate Function mapping    */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF6  Alternate function AF6
 * @{
 */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06)  /* EVENTOUT Alternate Function mapping  */
/**
  * @}
  */

/** @defgroup GPIOEx_Alternate_function_AF7  Alternate function AF7
 * @{
 */
#define GPIO_AF7_COMP1         ((uint8_t)0x07)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2         ((uint8_t)0x07)  /* COMP2 Alternate Function mapping     */
/**
  * @}
  */

/**
  * @}
  */

#define IS_GPIO_AF(__AF__)   (((__AF__) == GPIO_AF0_EVENTOUT  ) || \
                              ((__AF__) == GPIO_AF0_TIM21     ) || \
                              ((__AF__) == GPIO_AF0_SPI1      ) || \
                              ((__AF__) == GPIO_AF0_USART2    ) || \
                              ((__AF__) == GPIO_AF0_LPTIM1    ) || \
                              ((__AF__) == GPIO_AF0_MCO       ) || \
                              ((__AF__) == GPIO_AF0_SWDIO     ) || \
                              ((__AF__) == GPIO_AF0_SWCLK     ) || \
                              ((__AF__) == GPIO_AF1_SPI1      ) || \
                              ((__AF__) == GPIO_AF1_I2C1      ) || \
                              ((__AF__) == GPIO_AF1_LPTIM1    ) || \
                              ((__AF__) == GPIO_AF2_LPTIM1    ) || \
                              ((__AF__) == GPIO_AF2_TIM2      ) || \
                              ((__AF__) == GPIO_AF2_EVENTOUT  ) || \
                              ((__AF__) == GPIO_AF2_RTC       ) || \
                              ((__AF__) == GPIO_AF3_I2C1      ) || \
                              ((__AF__) == GPIO_AF3_EVENTOUT  ) || \
                              ((__AF__) == GPIO_AF4_I2C1      ) || \
                              ((__AF__) == GPIO_AF4_USART2    ) || \
                              ((__AF__) == GPIO_AF4_LPUART1   ) || \
                              ((__AF__) == GPIO_AF4_TIM22     ) || \
                              ((__AF__) == GPIO_AF4_EVENTOUT  ) || \
                              ((__AF__) == GPIO_AF5_TIM2      ) || \
                              ((__AF__) == GPIO_AF5_TIM21     ) || \
                              ((__AF__) == GPIO_AF5_TIM22     ) || \
                              ((__AF__) == GPIO_AF6_LPUART1   ) || \
                              ((__AF__) == GPIO_AF6_EVENTOUT  ) || \
                              ((__AF__) == GPIO_AF7_COMP1     ) || \
                              ((__AF__) == GPIO_AF7_COMP2     ))
                                      
                         

#define IS_GPIO_AF_AVAILABLE(__INSTANCE__,__AF__)  \
        (1)


#endif /* STM32L031xx/STM32L041xx*/
/*------------------------------------------------------------------------------------------*/



#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx)

#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U :\
                                      ((__GPIOx__) == (GPIOD))? 3U :\
                                      ((__GPIOx__) == (GPIOE))? 4U :\
                                      ((__GPIOx__) == (GPIOH))? 5U : 6U)

/** @defgroup GPIOEx_Pin_Available Pin available
 * @{
 */
#define GPIOA_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOB_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOC_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOD_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOE_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOH_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_9 | GPIO_PIN_10)
/**
  * @}
  */

#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
           ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOD) && (((__PIN__) & (GPIOD_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOD_PIN_AVAILABLE)) == (GPIOD_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOE) && (((__PIN__) & (GPIOE_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOE_PIN_AVAILABLE)) == (GPIOE_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOH) && (((__PIN__) & (GPIOH_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOH_PIN_AVAILABLE)) == (GPIOH_PIN_AVAILABLE))))

#elif defined (STM32L031xx) || defined (STM32L041xx)

#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U :\
                                      ((__GPIOx__) == (GPIOH))? 5U : 6U)

/** @defgroup GPIOEx_Pin_Available Pin available
 * @{
 */
#define GPIOA_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOB_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOC_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15)
#define GPIOH_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_1)
/**
  * @}
  */

#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
           ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOH) && (((__PIN__) & (GPIOH_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOH_PIN_AVAILABLE)) == (GPIOH_PIN_AVAILABLE))))

#elif defined (STM32L063xx) || defined (STM32L062xx) || defined (STM32L061xx) || \
      defined (STM32L053xx) || defined (STM32L052xx) || defined (STM32L051xx)

#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U :\
                                      ((__GPIOx__) == (GPIOD))? 3U :\
                                      ((__GPIOx__) == (GPIOH))? 5U : 6U)

/** @defgroup GPIOEx_Pin_Available Pin available
 * @{
 */
#define GPIOA_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOB_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOC_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOD_PIN_AVAILABLE  GPIO_PIN_2
#define GPIOH_PIN_AVAILABLE  GPIO_PIN_0 | GPIO_PIN_1
/**
  * @}
  */

#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
                ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
                 (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
                 (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))) || \
                 (((__INSTANCE__) == GPIOD) && (((__PIN__) & (GPIOD_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOD_PIN_AVAILABLE)) == (GPIOD_PIN_AVAILABLE))) || \
                 (((__INSTANCE__) == GPIOH) && (((__PIN__) & (GPIOH_PIN_AVAILABLE)) != 0) && (((__PIN__) | (GPIOH_PIN_AVAILABLE)) == (GPIOH_PIN_AVAILABLE))))


#endif /* STM32L083xx || STM32L082xx || STM32L081xx || STM32L073xx || STM32L072xx || STM32L071xx*/


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

#endif /* __STM32L0xx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

