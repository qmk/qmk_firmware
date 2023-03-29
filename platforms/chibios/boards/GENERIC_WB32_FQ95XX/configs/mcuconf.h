/*
    Copyright (C) 2022 Westberry Technology (ChangZhou) Corp., Ltd

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

#define WB32FQ95xx_MCUCONF  TRUE

/*
 * WB32FQ95 drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 15...0       Lowest...Highest.
 *
 */

/**
 * @name    Internal clock sources
 * @{
 */
#define WB32_HSECLK                        12000000
#define WB32_LSECLK                        32768

/*
 * HAL driver system settings.
 */
#define WB32_NO_INIT                       FALSE
#define WB32_MHSI_ENABLED                  TRUE
#define WB32_FHSI_ENABLED                  FALSE
#define WB32_LSI_ENABLED                   FALSE
#define WB32_HSE_ENABLED                   TRUE
#define WB32_LSE_ENABLED                   FALSE
#define WB32_PLL_ENABLED                   TRUE
#define WB32_MAINCLKSRC                    WB32_MAINCLKSRC_PLL
#define WB32_PLLSRC                        WB32_PLLSRC_HSE
#define WB32_PLLDIV_VALUE                  2
#define WB32_PLLMUL_VALUE                  12     //The allowed range is 12,16,20,24.
#define WB32_HPRE                          1
#define WB32_PPRE1                         1
#define WB32_PPRE2                         1
#define WB32_USBPRE                        WB32_USBPRE_DIV1P5

/*
 * EXTI driver system settings.
 */
#define WB32_IRQ_EXTI0_PRIORITY            6
#define WB32_IRQ_EXTI1_PRIORITY            6
#define WB32_IRQ_EXTI2_PRIORITY            6
#define WB32_IRQ_EXTI3_PRIORITY            6
#define WB32_IRQ_EXTI4_PRIORITY            6
#define WB32_IRQ_EXTI5_9_PRIORITY          6
#define WB32_IRQ_EXTI10_15_PRIORITY        6
#define WB32_IRQ_EXTI16_PRIORITY           6
#define WB32_IRQ_EXTI17_PRIORITY           6
#define WB32_IRQ_EXTI18_PRIORITY           6
#define WB32_IRQ_EXTI19_PRIORITY           6

/*
 * GPT driver system settings.
 */
#define WB32_TIM_MAX_CHANNELS              4
#define WB32_GPT_USE_TIM1                  FALSE
#define WB32_GPT_USE_TIM2                  FALSE
#define WB32_GPT_USE_TIM3                  FALSE
#define WB32_GPT_USE_TIM4                  FALSE
#define WB32_GPT_TIM1_IRQ_PRIORITY         7
#define WB32_GPT_TIM2_IRQ_PRIORITY         7
#define WB32_GPT_TIM3_IRQ_PRIORITY         7
#define WB32_GPT_TIM4_IRQ_PRIORITY         7

/*
 * ICU driver system settings.
 */
#define WB32_ICU_USE_TIM1                  FALSE
#define WB32_ICU_USE_TIM2                  FALSE
#define WB32_ICU_USE_TIM3                  FALSE
#define WB32_ICU_USE_TIM4                  FALSE
#define WB32_ICU_TIM1_IRQ_PRIORITY         7
#define WB32_ICU_TIM2_IRQ_PRIORITY         7
#define WB32_ICU_TIM3_IRQ_PRIORITY         7
#define WB32_ICU_TIM4_IRQ_PRIORITY         7

/*
 * PWM driver system settings.
 */
#define WB32_PWM_USE_ADVANCED              FALSE
#define WB32_PWM_USE_TIM1                  FALSE
#define WB32_PWM_USE_TIM2                  FALSE
#define WB32_PWM_USE_TIM3                  FALSE
#define WB32_PWM_USE_TIM4                  FALSE
#define WB32_PWM_TIM1_IRQ_PRIORITY         7
#define WB32_PWM_TIM2_IRQ_PRIORITY         7
#define WB32_PWM_TIM3_IRQ_PRIORITY         7
#define WB32_PWM_TIM4_IRQ_PRIORITY         7

/*
 * I2C driver system settings.
 */
#define WB32_I2C_USE_I2C1                  FALSE
#define WB32_I2C_USE_I2C2                  FALSE
#define WB32_I2C_BUSY_TIMEOUT              50
#define WB32_I2C_I2C1_IRQ_PRIORITY         5
#define WB32_I2C_I2C2_IRQ_PRIORITY         5

/*
 * SERIAL driver system settings.
 */
#define WB32_SERIAL_USE_UART1             FALSE
#define WB32_SERIAL_USE_UART2             FALSE
#define WB32_SERIAL_USE_UART3             FALSE
#define WB32_SERIAL_USART1_PRIORITY        12
#define WB32_SERIAL_USART2_PRIORITY        12
#define WB32_SERIAL_USART3_PRIORITY        12

/*
 * SPI driver system settings.
 */
#define WB32_SPI_USE_QSPI                   FALSE
#define WB32_SPI_USE_SPIM2                  FALSE
#define WB32_SPI_USE_SPIS1                  FALSE
#define WB32_SPI_USE_SPIS2                  FALSE
#define WB32_SPI_QSPI_IRQ_PRIORITY          10
#define WB32_SPI_SPIM2_IRQ_PRIORITY         10
#define WB32_SPI_SPIS1_IRQ_PRIORITY         10
#define WB32_SPI_SPIS2_IRQ_PRIORITY         10

/*
 * ST driver system settings.
 */
#define WB32_ST_IRQ_PRIORITY                8
#define WB32_ST_USE_TIMER                   2

/*
 * UART driver system settings.
 */
#define WB32_UART_USE_UART1                 FALSE
#define WB32_UART_USE_UART2                 FALSE
#define WB32_UART_USE_UART3                 FALSE
#define WB32_UART_UART1_IRQ_PRIORITY        12
#define WB32_UART_UART2_IRQ_PRIORITY        12
#define WB32_UART_UART3_IRQ_PRIORITY        12

/*
 * USB driver system settings.
 */
#define WB32_USB_USE_USB1                   TRUE
#define WB32_USB_USB1_IRQ_PRIORITY          13
#define WB32_USB_HOST_WAKEUP_DURATION       10


#endif /* MCUCONF_H */
