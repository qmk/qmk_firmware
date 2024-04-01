/*
    Copyright (C) 2021 essemi

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef MCUCONF_H
#define MCUCONF_H

/**
 * @name    Internal clock sources
 * @{
 */
#define ES32_PLLCLK                        72000000
#define ES32_HRCCLK                        48000000
#define ES32_LSECLK                        32768

/*
 * HAL driver system settings.
 */
#define ES32_NO_INIT                       FALSE
#define ES32_MHSI_ENABLED                  TRUE
#define ES32_FHSI_ENABLED                  FALSE
#define ES32_LSI_ENABLED                   FALSE
#define ES32_HSE_ENABLED                   TRUE
#define ES32_LSE_ENABLED                   FALSE
#define ES32_PLL_ENABLED                   TRUE
#define ES32_MAINCLKSRC                    ES32_MAINCLKSRC_PLL
#define ES32_HSE_STATE                     ANCTL_HSECR0_HSEON
#define ES32_PLLSRC                        ES32_PLLSRC_HSE
#define ES32_PLLDIV_VALUE                  2
#define ES32_PLLMUL_VALUE                  12     // The allowed range is 12,16,20,24.
#define ES32_HPRE                          1
#define ES32_PPRE1                         1
#define ES32_PPRE2                         1
#define ES32_USBPRE                        ES32_USBPRE_DIV1P5

/*
 * EXTI driver system settings.
 */
#define ES32_IRQ_EXTI0_PRIORITY            6
#define ES32_IRQ_EXTI1_PRIORITY            6
#define ES32_IRQ_EXTI2_PRIORITY            6
#define ES32_IRQ_EXTI3_PRIORITY            6
#define ES32_IRQ_EXTI4_PRIORITY            6
#define ES32_IRQ_EXTI5_9_PRIORITY          6
#define ES32_IRQ_EXTI10_15_PRIORITY        6
#define ES32_IRQ_EXTI16_PRIORITY           6
#define ES32_IRQ_EXTI17_PRIORITY           6
#define ES32_IRQ_EXTI18_PRIORITY           6
#define ES32_IRQ_EXTI19_PRIORITY           6

/*
 * GPT driver system settings.
 */
#define ES32_TIM_MAX_CHANNELS              4
#define ES32_GPT_USE_TIM1                  FALSE
#define ES32_GPT_USE_TIM2                  FALSE
#define ES32_GPT_USE_TIM3                  FALSE
#define ES32_GPT_USE_TIM4                  FALSE
#define ES32_GPT_TIM1_IRQ_PRIORITY         7
#define ES32_GPT_TIM2_IRQ_PRIORITY         7
#define ES32_GPT_TIM3_IRQ_PRIORITY         7
#define ES32_GPT_TIM4_IRQ_PRIORITY         7

/*
 * ICU driver system settings.
 */
#define ES32_ICU_USE_TIM1                  FALSE
#define ES32_ICU_USE_TIM2                  FALSE
#define ES32_ICU_USE_TIM3                  FALSE
#define ES32_ICU_USE_TIM4                  FALSE
#define ES32_ICU_TIM1_IRQ_PRIORITY         7
#define ES32_ICU_TIM2_IRQ_PRIORITY         7
#define ES32_ICU_TIM3_IRQ_PRIORITY         7
#define ES32_ICU_TIM4_IRQ_PRIORITY         7

/*
 * PWM driver system settings.
 */
#define ES32_PWM_USE_ADVANCED              FALSE
#define ES32_PWM_USE_TIM1                  FALSE
#define ES32_PWM_USE_TIM2                  FALSE
#define ES32_PWM_USE_TIM3                  FALSE
#define ES32_PWM_USE_TIM4                  FALSE
#define ES32_PWM_TIM1_IRQ_PRIORITY         7
#define ES32_PWM_TIM2_IRQ_PRIORITY         7
#define ES32_PWM_TIM3_IRQ_PRIORITY         7
#define ES32_PWM_TIM4_IRQ_PRIORITY         7

/*
 * I2C driver system settings.
 */
#define ES32_I2C_USE_I2C1                  FALSE
#define ES32_I2C_USE_I2C2                  FALSE
#define ES32_I2C_BUSY_TIMEOUT              50
#define ES32_I2C_I2C1_IRQ_PRIORITY         5
#define ES32_I2C_I2C2_IRQ_PRIORITY         5

/*
 * SERIAL driver system settings.
 */
#define ES32_SERIAL_USE_UART1             FALSE
#define ES32_SERIAL_USE_UART2             FALSE
#define ES32_SERIAL_USE_UART3             FALSE
#define ES32_SERIAL_USART1_PRIORITY        12
#define ES32_SERIAL_USART2_PRIORITY        12
#define ES32_SERIAL_USART3_PRIORITY        12

/*
 * SPI driver system settings.
 */
#define ES32_SPI_USE_QSPI                   FALSE
#define ES32_SPI_USE_SPIM2                  FALSE
#define ES32_SPI_USE_SPIS1                  FALSE
#define ES32_SPI_USE_SPIS2                  FALSE
#define ES32_SPI_QSPI_IRQ_PRIORITY          10
#define ES32_SPI_SPIM2_IRQ_PRIORITY         10
#define ES32_SPI_SPIS1_IRQ_PRIORITY         10
#define ES32_SPI_SPIS2_IRQ_PRIORITY         10

/*
 * ST driver system settings.
 */
#define ES32_ST_IRQ_PRIORITY                8
#define ES32_ST_USE_TIMER                   2

/*
 * UART driver system settings.
 */
#define ES32_UART_USE_UART1                 FALSE
#define ES32_UART_USE_UART2                 FALSE
#define ES32_UART_USE_UART3                 FALSE
#define ES32_UART_UART1_IRQ_PRIORITY        12
#define ES32_UART_UART2_IRQ_PRIORITY        12
#define ES32_UART_UART3_IRQ_PRIORITY        12

/*
 * USB driver system settings.
 */
#define ES32_USB_USE_USB1                   TRUE
#define ES32_USB_USB1_IRQ_PRIORITY          13
#define ES32_USB_HOST_WAKEUP_DURATION       10

/*
 * ADC driver system settings.
 */
#define ES32_ADC_USE_ADC1                   FALSE
#define ES32_ADC_ADC1_DMA_PRIORITY          2
#define ES32_ADC_ADC1_IRQ_PRIORITY          6

#endif /* MCUCONF_H */
