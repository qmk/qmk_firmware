/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2019 /u/KeepItUnder

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

#ifndef _MCUCONF_H_
#define _MCUCONF_H_

/*
 * NUC123SD4AN0 drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 3...0       Lowest...Highest.
 *
 * DMA priorities:
 * 5...0        Lowest...Highest.
 */

#define NUC123SD4AN0_MCUCONF

/*
 * HAL driver system settings.
 */
#define NUC123_NO_INIT                       FALSE
#define NUC123_PVD_ENABLE                    FALSE
#define NUC123_PLS                           NUC123_PLS_LEV0
#define NUC123_HSI_ENABLED                   TRUE
#define NUC123_LSI_ENABLED                   TRUE
#define NUC123_HSE_ENABLED                   TRUE
#define NUC123_LSE_ENABLED                   FALSE
#define NUC123_SW                            NUC123_SW_HCLK_2
#define NUC123_PLLSRC                        NUC123_PLLSRC_HSI_DIV2

#define NUC123_I2C1SW                        NUC123_I2C1SW_HSI
#define NUC123_USART1SW                      NUC123_USART1SW_PCLK

/*
 * ADC driver system settings.
 */
#define NUC123_ADC_USE_ADC1                  FALSE
#define NUC123_ADC_ADC1_DMA_PRIORITY         2
#define NUC123_ADC_IRQ_PRIORITY              2
#define NUC123_ADC_ADC1_DMA_IRQ_PRIORITY     2

/*
 * GPT driver system settings.
 */
#define NUC123_GPT_USE_TIM1                  FALSE
#define NUC123_GPT_USE_TIM2                  FALSE
#define NUC123_GPT_USE_TIM3                  FALSE
#define NUC123_GPT_TIM1_IRQ_PRIORITY         2
#define NUC123_GPT_TIM2_IRQ_PRIORITY         2
#define NUC123_GPT_TIM3_IRQ_PRIORITY         2

/*
 * I2C driver system settings.
 */
#define NUC123_I2C_USE_I2C1                  FALSE
#define NUC123_I2C_USE_I2C2                  FALSE
#define NUC123_I2C_BUSY_TIMEOUT              50
#define NUC123_I2C_I2C1_IRQ_PRIORITY         3
#define NUC123_I2C_I2C2_IRQ_PRIORITY         3
#define NUC123_I2C_USE_DMA                   TRUE
#define NUC123_I2C_I2C1_DMA_PRIORITY         1
#define NUC123_I2C_I2C2_DMA_PRIORITY         1
#define NUC123_I2C_I2C1_RX_DMA_STREAM        NUC123_DMA_STREAM_ID(1, 7)
#define NUC123_I2C_I2C1_TX_DMA_STREAM        NUC123_DMA_STREAM_ID(1, 6)
#define NUC123_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")
/*
 * PWM driver system settings.
 */
#define NUC123_PWM_USE_ADVANCED              FALSE
#define NUC123_PWM_USE_TIM1                  FALSE
#define NUC123_PWM_USE_TIM2                  FALSE
#define NUC123_PWM_USE_TIM3                  TRUE
#define NUC123_PWM_TIM1_IRQ_PRIORITY         3
#define NUC123_PWM_TIM2_IRQ_PRIORITY         3
#define NUC123_PWM_TIM3_IRQ_PRIORITY         3

/*
 * SERIAL driver system settings.
 */
#define NUC123_SERIAL_USE_UART1             FALSE
#define NUC123_SERIAL_USE_UART2             FALSE
#define NUC123_SERIAL_USART1_PRIORITY        3
#define NUC123_SERIAL_USART2_PRIORITY        3

/*
 * SPI driver system settings.
 */
#define NUC123_SPI_USE_SPI1                  FALSE
#define NUC123_SPI_USE_SPI2                  FALSE
#define NUC123_SPI_SPI1_DMA_PRIORITY         1
#define NUC123_SPI_SPI2_DMA_PRIORITY         1
#define NUC123_SPI_SPI1_IRQ_PRIORITY         2
#define NUC123_SPI_SPI2_IRQ_PRIORITY         2
#define NUC123_SPI_SPI2_RX_DMA_STREAM        NUC123_DMA_STREAM_ID(1, 4)
#define NUC123_SPI_SPI2_TX_DMA_STREAM        NUC123_DMA_STREAM_ID(1, 5)
#define NUC123_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 */
#define NUC123_ST_IRQ_PRIORITY               2
#define NUC123_ST_USE_TIMER                  2

/*
 * UART driver system settings.
 */
#define NUC123_UART_USE_USART1               FALSE
#define NUC123_UART_USE_USART2               FALSE
#define NUC123_UART_USART1_IRQ_PRIORITY      3
#define NUC123_UART_USART2_IRQ_PRIORITY      3
#define NUC123_UART_USART1_DMA_PRIORITY      0
#define NUC123_UART_USART2_DMA_PRIORITY      0
#define NUC123_UART_DMA_ERROR_HOOK(uartp)    osalSysHalt("DMA failure")

/*
 * USB driver system settings.
 */
#define NUC123_USB_USE_USB1                  TRUE
#define NUC123_USB_LOW_POWER_ON_SUSPEND      FALSE

#endif /* _MCUCONF_H_ */
