/*
    ChibiOS - Copyright (C) 2006..2020 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2023..2025 HorrorTroll
    ChibiOS - Copyright (C) 2023..2025 Zhaqian

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

/*
 * AT32F402 drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 15...0       Lowest...Highest.
 *
 * DMA priorities:
 * 0...3        Lowest...Highest.
 */

#define AT32F402_MCUCONF

/*
 * General settings.
 */
#define AT32_NO_INIT                        FALSE

/*
 * HAL driver system settings.
 */
#define AT32_HICK_ENABLED                   TRUE
#define AT32_LICK_ENABLED                   FALSE
#define AT32_HEXT_ENABLED                   TRUE
#define AT32_LEXT_ENABLED                   FALSE
#define AT32_PLLU_ENABLED                   TRUE
#define AT32_SCLKSEL                        AT32_SCLKSEL_PLL
#define AT32_PLLRCS                         AT32_PLLRCS_HEXT
#define AT32_PLL_MS_VALUE                   1
#define AT32_PLL_NS_VALUE                   108
#define AT32_PLL_FP_VALUE                   4
#define AT32_PLL_FU_VALUE                   18
#define AT32_AHBDIV                         AT32_AHBDIV_DIV1
#define AT32_APB1DIV                        AT32_APB1DIV_DIV2
#define AT32_APB2DIV                        AT32_APB2DIV_DIV1
#define AT32_HICK_TO_SCLK                   AT32_HICK_TO_SCLK_48M
#define AT32_HICKDIV                        AT32_HICKDIV_DIV1
#define AT32_HICK_TO_SCLK_DIV               AT32_HICK_TO_SCLK_DIV_DIV1
#define AT32_HEXT_TO_SCLK_DIV               AT32_HEXT_TO_SCLK_DIV_DIV1
#define AT32_USB_CLOCK48_REQUIRED           TRUE
#define AT32_PLLU_USB48_SEL                 AT32_PLLU_USB48_SEL_PLLU
#define AT32_CLKOUT_SEL                     AT32_CLKOUT_SEL_HICK
#define AT32_CLKOUTDIV1                     AT32_CLKOUTDIV1_DIV1
#define AT32_CLKOUTDIV2                     AT32_CLKOUTDIV2_DIV1
#define AT32_ERTCSEL                        AT32_ERTCSEL_NOCLOCK
#define AT32_ERTCDIV_VALUE                  12
#define AT32_I2SF5CLKSEL                    AT32_I2SF5CLKSEL_SCLK
#define AT32_PVM_ENABLE                     FALSE
#define AT32_PVMSEL                         AT32_PVMSEL_LEV1
#define AT32_LDOOVSEL                       AT32_LDOOVSEL_LEV3

/*
 * IRQ system settings.
 */
#define AT32_IRQ_EXINT0_PRIORITY            6
#define AT32_IRQ_EXINT1_PRIORITY            6
#define AT32_IRQ_EXINT2_PRIORITY            6
#define AT32_IRQ_EXINT3_PRIORITY            6
#define AT32_IRQ_EXINT4_PRIORITY            6
#define AT32_IRQ_EXINT5_9_PRIORITY          6
#define AT32_IRQ_EXINT10_15_PRIORITY        6
#define AT32_IRQ_EXINT16_PRIORITY           6
#define AT32_IRQ_EXINT17_PRIORITY           15
#define AT32_IRQ_EXINT18_PRIORITY           6
#define AT32_IRQ_EXINT20_PRIORITY           6
#define AT32_IRQ_EXINT21_PRIORITY           15
#define AT32_IRQ_EXINT22_PRIORITY           15

#define AT32_IRQ_TMR1_BRK_TMR9_PRIORITY     7
#define AT32_IRQ_TMR1_OVF_TMR10_PRIORITY    7
#define AT32_IRQ_TMR1_HALL_TMR11_PRIORITY   7
#define AT32_IRQ_TMR1_CH_PRIORITY           7
#define AT32_IRQ_TMR2_PRIORITY              7
#define AT32_IRQ_TMR3_PRIORITY              7
#define AT32_IRQ_TMR4_PRIORITY              7
#define AT32_IRQ_TMR6_PRIORITY              7
#define AT32_IRQ_TMR7_PRIORITY              7
#define AT32_IRQ_TMR13_PRIORITY             7
#define AT32_IRQ_TMR14_PRIORITY             7

#define AT32_IRQ_USART1_PRIORITY            12
#define AT32_IRQ_USART2_PRIORITY            12
#define AT32_IRQ_USART3_PRIORITY            12
#define AT32_IRQ_UART4_PRIORITY             12
#define AT32_IRQ_UART5_PRIORITY             12
#define AT32_IRQ_USART6_PRIORITY            12
#define AT32_IRQ_UART7_PRIORITY             12
#define AT32_IRQ_UART8_PRIORITY             12

/*
 * ADC driver system settings.
 */
#define AT32_ADC_USE_ADC1                   FALSE
#define AT32_ADC_ADC1_DMA_PRIORITY          2
#define AT32_ADC_IRQ_PRIORITY               6
#define AT32_ADC_ADC1_DMA_IRQ_PRIORITY      6
#define AT32_ADC_ADCDIV                     8

/*
 * CAN driver system settings.
 */
#define AT32_CAN_USE_CAN1                   FALSE
#define AT32_CAN_CAN1_IRQ_PRIORITY          11

/*
 * GPT driver system settings.
 */
#define AT32_GPT_USE_TMR1                   FALSE
#define AT32_GPT_USE_TMR2                   FALSE
#define AT32_GPT_USE_TMR3                   FALSE
#define AT32_GPT_USE_TMR4                   FALSE
#define AT32_GPT_USE_TMR6                   FALSE
#define AT32_GPT_USE_TMR7                   FALSE
#define AT32_GPT_USE_TMR9                   FALSE
#define AT32_GPT_USE_TMR10                  FALSE
#define AT32_GPT_USE_TMR11                  FALSE
#define AT32_GPT_USE_TMR13                  FALSE
#define AT32_GPT_USE_TMR14                  FALSE

/*
 * I2C driver system settings.
 */
#define AT32_I2C_USE_I2C1                   FALSE
#define AT32_I2C_USE_I2C2                   FALSE
#define AT32_I2C_USE_I2C3                   FALSE
#define AT32_I2C_BUSY_TIMEOUT               50
#define AT32_I2C_I2C1_DMA_PRIORITY          3
#define AT32_I2C_I2C2_DMA_PRIORITY          3
#define AT32_I2C_I2C3_DMA_PRIORITY          3
#define AT32_I2C_I2C1_IRQ_PRIORITY          5
#define AT32_I2C_I2C2_IRQ_PRIORITY          5
#define AT32_I2C_I2C3_IRQ_PRIORITY          5
#define AT32_I2C_DMA_ERROR_HOOK(i2cp)       osalSysHalt("DMA failure")

/*
 * ICU driver system settings.
 */
#define AT32_ICU_USE_TMR1                   FALSE
#define AT32_ICU_USE_TMR2                   FALSE
#define AT32_ICU_USE_TMR3                   FALSE
#define AT32_ICU_USE_TMR4                   FALSE
#define AT32_ICU_USE_TMR9                   FALSE

/*
 * PWM driver system settings.
 */
#define AT32_PWM_USE_TMR1                   FALSE
#define AT32_PWM_USE_TMR2                   FALSE
#define AT32_PWM_USE_TMR3                   FALSE
#define AT32_PWM_USE_TMR4                   FALSE
#define AT32_PWM_USE_TMR9                   FALSE
#define AT32_PWM_USE_TMR10                  FALSE
#define AT32_PWM_USE_TMR11                  FALSE
#define AT32_PWM_USE_TMR13                  FALSE
#define AT32_PWM_USE_TMR14                  FALSE

/*
 * RTC driver system settings.
 */
#define AT32_ERTC_DIVA_VALUE                32
#define AT32_ERTC_DIVB_VALUE                1024
#define AT32_ERTC_CTRL_INIT                 0
#define AT32_ERTC_TAMP_INIT                 0

/*
 * SERIAL driver system settings.
 */
#define AT32_SERIAL_USE_USART1              FALSE
#define AT32_SERIAL_USE_USART2              FALSE
#define AT32_SERIAL_USE_USART3              FALSE
#define AT32_SERIAL_USE_UART4               FALSE
#define AT32_SERIAL_USE_UART5               FALSE
#define AT32_SERIAL_USE_USART6              FALSE
#define AT32_SERIAL_USE_UART7               FALSE
#define AT32_SERIAL_USE_UART8               FALSE

/*
 * SIO driver system settings.
 */
#define AT32_SIO_USE_USART1                 FALSE
#define AT32_SIO_USE_USART2                 FALSE
#define AT32_SIO_USE_USART3                 FALSE
#define AT32_SIO_USE_UART4                  FALSE
#define AT32_SIO_USE_UART5                  FALSE
#define AT32_SIO_USE_USART6                 FALSE
#define AT32_SIO_USE_UART7                  FALSE
#define AT32_SIO_USE_UART8                  FALSE

/*
 * SPI driver system settings.
 */
#define AT32_SPI_USE_SPI1                   FALSE
#define AT32_SPI_USE_SPI2                   FALSE
#define AT32_SPI_USE_SPI3                   FALSE
#define AT32_SPI_SPI1_DMA_PRIORITY          1
#define AT32_SPI_SPI2_DMA_PRIORITY          1
#define AT32_SPI_SPI3_DMA_PRIORITY          1
#define AT32_SPI_SPI1_IRQ_PRIORITY          10
#define AT32_SPI_SPI2_IRQ_PRIORITY          10
#define AT32_SPI_SPI3_IRQ_PRIORITY          10
#define AT32_SPI_DMA_ERROR_HOOK(spip)       osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 */
#define AT32_ST_IRQ_PRIORITY                8
#define AT32_ST_USE_TIMER                   2

/*
 * UART driver system settings.
 */
#define AT32_UART_USE_USART1                FALSE
#define AT32_UART_USE_USART2                FALSE
#define AT32_UART_USE_USART3                FALSE
#define AT32_UART_USE_UART4                 FALSE
#define AT32_UART_USE_UART5                 FALSE
#define AT32_UART_USE_USART6                FALSE
#define AT32_UART_USE_UART7                 FALSE
#define AT32_UART_USE_UART8                 FALSE
#define AT32_UART_USART1_DMA_PRIORITY       0
#define AT32_UART_USART2_DMA_PRIORITY       0
#define AT32_UART_USART3_DMA_PRIORITY       0
#define AT32_UART_UART4_DMA_PRIORITY        0
#define AT32_UART_UART5_DMA_PRIORITY        0
#define AT32_UART_USART6_DMA_PRIORITY       0
#define AT32_UART_UART7_DMA_PRIORITY        0
#define AT32_UART_UART8_DMA_PRIORITY        0
#define AT32_UART_DMA_ERROR_HOOK(uartp)     osalSysHalt("DMA failure")

/*
 * USB driver system settings.
 */
#define AT32_USB_USE_OTG1                   TRUE
#define AT32_USB_OTG1_IRQ_PRIORITY          14
#define AT32_USB_OTG1_RX_FIFO_SIZE          512

/*
 * WDG driver system settings.
 */
#define AT32_WDG_USE_WDT                    FALSE

#endif /* MCUCONF_H */
