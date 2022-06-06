/*
    ChibiOS - Copyright (C) 2006..2020 Giovanni Di Sirio

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

/*
 * STM32G4xx drivers configuration.
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

#ifndef MCUCONF_H
#define MCUCONF_H

#define STM32G4xx_MCUCONF
#define STM32G473_MCUCONF
#define STM32G483_MCUCONF
#define STM32G474_MCUCONF
#define STM32G484_MCUCONF

/*
 * HAL driver system settings.
 */
#define STM32_NO_INIT                       FALSE
#define STM32_CLOCK_DYNAMIC                 FALSE
#define STM32_VOS                           STM32_VOS_RANGE1
#define STM32_PWR_BOOST                     TRUE
#define STM32_PWR_CR2                       (PWR_CR2_PLS_LEV0)
#define STM32_PWR_CR3                       (PWR_CR3_EIWF)
#define STM32_PWR_CR4                       (0U)
#define STM32_PWR_PUCRA                     (0U)
#define STM32_PWR_PDCRA                     (0U)
#define STM32_PWR_PUCRB                     (0U)
#define STM32_PWR_PDCRB                     (0U)
#define STM32_PWR_PUCRC                     (0U)
#define STM32_PWR_PDCRC                     (0U)
#define STM32_PWR_PUCRD                     (0U)
#define STM32_PWR_PDCRD                     (0U)
#define STM32_PWR_PUCRE                     (0U)
#define STM32_PWR_PDCRE                     (0U)
#define STM32_PWR_PUCRF                     (0U)
#define STM32_PWR_PDCRF                     (0U)
#define STM32_PWR_PUCRG                     (0U)
#define STM32_PWR_PDCRG                     (0U)
#define STM32_HSI16_ENABLED                 TRUE
#define STM32_HSI48_ENABLED                 TRUE
#define STM32_HSE_ENABLED                   FALSE
#define STM32_LSI_ENABLED                   FALSE
#define STM32_LSE_ENABLED                   FALSE
#define STM32_SW                            STM32_SW_PLLRCLK
#define STM32_PLLSRC                        STM32_PLLSRC_HSI16
#define STM32_PLLM_VALUE                    2
#define STM32_PLLN_VALUE                    40
#define STM32_PLLPDIV_VALUE                 0
#define STM32_PLLP_VALUE                    7
#define STM32_PLLQ_VALUE                    2
#define STM32_PLLR_VALUE                    2
#define STM32_HPRE                          STM32_HPRE_DIV1
#define STM32_PPRE1                         STM32_PPRE1_DIV1
#define STM32_PPRE2                         STM32_PPRE2_DIV1
#define STM32_MCOSEL                        STM32_MCOSEL_NOCLOCK
#define STM32_MCOPRE                        STM32_MCOPRE_DIV1
#define STM32_LSCOSEL                       STM32_LSCOSEL_NOCLOCK

/*
 * Peripherals clock sources.
 */
#define STM32_USART1SEL                     STM32_USART1SEL_SYSCLK
#define STM32_USART2SEL                     STM32_USART2SEL_SYSCLK
#define STM32_USART3SEL                     STM32_USART3SEL_SYSCLK
#define STM32_UART4SEL                      STM32_UART4SEL_SYSCLK
#define STM32_UART5SEL                      STM32_UART5SEL_SYSCLK
#define STM32_LPUART1SEL                    STM32_LPUART1SEL_PCLK1
#define STM32_I2C1SEL                       STM32_I2C1SEL_PCLK1
#define STM32_I2C2SEL                       STM32_I2C2SEL_PCLK1
#define STM32_I2C3SEL                       STM32_I2C3SEL_PCLK1
#define STM32_I2C4SEL                       STM32_I2C4SEL_PCLK1
#define STM32_LPTIM1SEL                     STM32_LPTIM1SEL_PCLK1
#define STM32_SAI1SEL                       STM32_SAI1SEL_SYSCLK
#define STM32_I2S23SEL                      STM32_I2S23SEL_SYSCLK
#define STM32_FDCANSEL                      STM32_FDCANSEL_HSE
#define STM32_CLK48SEL                      STM32_CLK48SEL_HSI48
#define STM32_ADC12SEL                      STM32_ADC12SEL_PLLPCLK
#define STM32_ADC345SEL                     STM32_ADC345SEL_PLLPCLK
#define STM32_QSPISEL                       STM32_QSPISEL_SYSCLK
#define STM32_RTCSEL                        STM32_RTCSEL_NOCLOCK

/*
 * IRQ system settings.
 */
#define STM32_IRQ_EXTI0_PRIORITY            6
#define STM32_IRQ_EXTI1_PRIORITY            6
#define STM32_IRQ_EXTI2_PRIORITY            6
#define STM32_IRQ_EXTI3_PRIORITY            6
#define STM32_IRQ_EXTI4_PRIORITY            6
#define STM32_IRQ_EXTI5_9_PRIORITY          6
#define STM32_IRQ_EXTI10_15_PRIORITY        6
#define STM32_IRQ_EXTI164041_PRIORITY       6
#define STM32_IRQ_EXTI17_PRIORITY           6
#define STM32_IRQ_EXTI18_PRIORITY           6
#define STM32_IRQ_EXTI19_PRIORITY           6
#define STM32_IRQ_EXTI20_PRIORITY           6
#define STM32_IRQ_EXTI212229_PRIORITY       6
#define STM32_IRQ_EXTI30_32_PRIORITY        6
#define STM32_IRQ_EXTI33_PRIORITY           6

#define STM32_IRQ_FDCAN1_PRIORITY           10
#define STM32_IRQ_FDCAN2_PRIORITY           10
#define STM32_IRQ_FDCAN3_PRIORITY           10

#define STM32_IRQ_TIM1_BRK_TIM15_PRIORITY   7
#define STM32_IRQ_TIM1_UP_TIM16_PRIORITY    7
#define STM32_IRQ_TIM1_TRGCO_TIM17_PRIORITY 7
#define STM32_IRQ_TIM1_CC_PRIORITY          7
#define STM32_IRQ_TIM2_PRIORITY             7
#define STM32_IRQ_TIM3_PRIORITY             7
#define STM32_IRQ_TIM4_PRIORITY             7
#define STM32_IRQ_TIM5_PRIORITY             7
#define STM32_IRQ_TIM6_PRIORITY             7
#define STM32_IRQ_TIM7_PRIORITY             7
#define STM32_IRQ_TIM8_UP_PRIORITY          7
#define STM32_IRQ_TIM8_CC_PRIORITY          7
#define STM32_IRQ_TIM20_UP_PRIORITY         7
#define STM32_IRQ_TIM20_CC_PRIORITY         7

#define STM32_IRQ_USART1_PRIORITY           12
#define STM32_IRQ_USART2_PRIORITY           12
#define STM32_IRQ_USART3_PRIORITY           12
#define STM32_IRQ_UART4_PRIORITY            12
#define STM32_IRQ_UART5_PRIORITY            12
#define STM32_IRQ_LPUART1_PRIORITY          12

/*
 * ADC driver system settings.
 */
#define STM32_ADC_DUAL_MODE                 FALSE
#define STM32_ADC_COMPACT_SAMPLES           FALSE
#define STM32_ADC_USE_ADC1                  FALSE
#define STM32_ADC_USE_ADC2                  FALSE
#define STM32_ADC_USE_ADC3                  FALSE
#define STM32_ADC_USE_ADC4                  FALSE
#define STM32_ADC_ADC1_DMA_STREAM           STM32_DMA_STREAM_ID_ANY
#define STM32_ADC_ADC2_DMA_STREAM           STM32_DMA_STREAM_ID_ANY
#define STM32_ADC_ADC3_DMA_STREAM           STM32_DMA_STREAM_ID_ANY
#define STM32_ADC_ADC4_DMA_STREAM           STM32_DMA_STREAM_ID_ANY
#define STM32_ADC_ADC1_DMA_PRIORITY         2
#define STM32_ADC_ADC2_DMA_PRIORITY         2
#define STM32_ADC_ADC3_DMA_PRIORITY         2
#define STM32_ADC_ADC4_DMA_PRIORITY         2
#define STM32_ADC_ADC12_IRQ_PRIORITY        5
#define STM32_ADC_ADC3_IRQ_PRIORITY         5
#define STM32_ADC_ADC4_IRQ_PRIORITY         5
#define STM32_ADC_ADC1_DMA_IRQ_PRIORITY     5
#define STM32_ADC_ADC2_DMA_IRQ_PRIORITY     5
#define STM32_ADC_ADC3_DMA_IRQ_PRIORITY     5
#define STM32_ADC_ADC4_DMA_IRQ_PRIORITY     5
#define STM32_ADC_ADC12_CLOCK_MODE          ADC_CCR_CKMODE_AHB_DIV4
#define STM32_ADC_ADC345_CLOCK_MODE         ADC_CCR_CKMODE_AHB_DIV4
#define STM32_ADC_ADC12_PRESC               ADC_CCR_PRESC_DIV2
#define STM32_ADC_ADC345_PRESC              ADC_CCR_PRESC_DIV2

/*
 * CAN driver system settings.
 */
#define STM32_CAN_USE_FDCAN1                FALSE
#define STM32_CAN_USE_FDCAN2                FALSE
#define STM32_CAN_USE_FDCAN3                FALSE

/*
 * DAC driver system settings.
 */
#define STM32_DAC_DUAL_MODE                 FALSE
#define STM32_DAC_USE_DAC1_CH1              FALSE
#define STM32_DAC_USE_DAC1_CH2              FALSE
#define STM32_DAC_USE_DAC2_CH1              FALSE
#define STM32_DAC_USE_DAC3_CH1              FALSE
#define STM32_DAC_USE_DAC3_CH2              FALSE
#define STM32_DAC_USE_DAC4_CH1              FALSE
#define STM32_DAC_USE_DAC4_CH2              FALSE
#define STM32_DAC_DAC1_CH1_IRQ_PRIORITY     10
#define STM32_DAC_DAC1_CH2_IRQ_PRIORITY     10
#define STM32_DAC_DAC2_CH1_IRQ_PRIORITY     10
#define STM32_DAC_DAC3_CH1_IRQ_PRIORITY     10
#define STM32_DAC_DAC3_CH2_IRQ_PRIORITY     10
#define STM32_DAC_DAC4_CH1_IRQ_PRIORITY     10
#define STM32_DAC_DAC4_CH2_IRQ_PRIORITY     10
#define STM32_DAC_DAC1_CH1_DMA_PRIORITY     2
#define STM32_DAC_DAC1_CH2_DMA_PRIORITY     2
#define STM32_DAC_DAC2_CH1_DMA_PRIORITY     2
#define STM32_DAC_DAC3_CH1_DMA_PRIORITY     2
#define STM32_DAC_DAC3_CH2_DMA_PRIORITY     2
#define STM32_DAC_DAC4_CH1_DMA_PRIORITY     2
#define STM32_DAC_DAC4_CH2_DMA_PRIORITY     2
#define STM32_DAC_DAC1_CH1_DMA_STREAM       STM32_DMA_STREAM_ID_ANY
#define STM32_DAC_DAC1_CH2_DMA_STREAM       STM32_DMA_STREAM_ID_ANY
#define STM32_DAC_DAC2_CH1_DMA_STREAM       STM32_DMA_STREAM_ID_ANY
#define STM32_DAC_DAC3_CH1_DMA_STREAM       STM32_DMA_STREAM_ID_ANY
#define STM32_DAC_DAC3_CH2_DMA_STREAM       STM32_DMA_STREAM_ID_ANY
#define STM32_DAC_DAC4_CH1_DMA_STREAM       STM32_DMA_STREAM_ID_ANY
#define STM32_DAC_DAC4_CH2_DMA_STREAM       STM32_DMA_STREAM_ID_ANY

/*
 * GPT driver system settings.
 */
#define STM32_GPT_USE_TIM1                  FALSE
#define STM32_GPT_USE_TIM2                  FALSE
#define STM32_GPT_USE_TIM3                  FALSE
#define STM32_GPT_USE_TIM4                  FALSE
#define STM32_GPT_USE_TIM5                  FALSE
#define STM32_GPT_USE_TIM6                  FALSE
#define STM32_GPT_USE_TIM7                  FALSE
#define STM32_GPT_USE_TIM8                  FALSE
#define STM32_GPT_USE_TIM15                 FALSE
#define STM32_GPT_USE_TIM16                 FALSE
#define STM32_GPT_USE_TIM17                 FALSE

/*
 * I2C driver system settings.
 */
#define STM32_I2C_USE_I2C1                  FALSE
#define STM32_I2C_USE_I2C2                  FALSE
#define STM32_I2C_USE_I2C3                  FALSE
#define STM32_I2C_USE_I2C4                  FALSE
#define STM32_I2C_BUSY_TIMEOUT              50
#define STM32_I2C_I2C1_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C1_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C2_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C2_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C3_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C3_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C4_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C4_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_I2C_I2C1_IRQ_PRIORITY         5
#define STM32_I2C_I2C2_IRQ_PRIORITY         5
#define STM32_I2C_I2C3_IRQ_PRIORITY         5
#define STM32_I2C_I2C4_IRQ_PRIORITY         5
#define STM32_I2C_I2C1_DMA_PRIORITY         3
#define STM32_I2C_I2C2_DMA_PRIORITY         3
#define STM32_I2C_I2C3_DMA_PRIORITY         3
#define STM32_I2C_I2C4_DMA_PRIORITY         3
#define STM32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")

/*
 * ICU driver system settings.
 */
#define STM32_ICU_USE_TIM1                  FALSE
#define STM32_ICU_USE_TIM2                  FALSE
#define STM32_ICU_USE_TIM3                  FALSE
#define STM32_ICU_USE_TIM4                  FALSE
#define STM32_ICU_USE_TIM5                  FALSE
#define STM32_ICU_USE_TIM8                  FALSE
#define STM32_ICU_USE_TIM15                 FALSE
#define STM32_ICU_USE_TIM16                 FALSE
#define STM32_ICU_USE_TIM17                 FALSE

/*
 * PWM driver system settings.
 */
#define STM32_PWM_USE_TIM1                  FALSE
#define STM32_PWM_USE_TIM2                  FALSE
#define STM32_PWM_USE_TIM3                  FALSE
#define STM32_PWM_USE_TIM4                  FALSE
#define STM32_PWM_USE_TIM5                  FALSE
#define STM32_PWM_USE_TIM8                  FALSE
#define STM32_PWM_USE_TIM15                 FALSE
#define STM32_PWM_USE_TIM16                 FALSE
#define STM32_PWM_USE_TIM17                 FALSE
#define STM32_PWM_USE_TIM20                 FALSE

/*
 * RTC driver system settings.
 */
#define STM32_RTC_PRESA_VALUE               32
#define STM32_RTC_PRESS_VALUE               1024
#define STM32_RTC_CR_INIT                   0
#define STM32_TAMP_CR1_INIT                 0
#define STM32_TAMP_CR2_INIT                 0
#define STM32_TAMP_FLTCR_INIT               0
#define STM32_TAMP_IER_INIT                 0

/*
 * SDC driver system settings.
 */

/*
 * SERIAL driver system settings.
 */
#define STM32_SERIAL_USE_USART1             FALSE
#define STM32_SERIAL_USE_USART2             FALSE
#define STM32_SERIAL_USE_USART3             FALSE
#define STM32_SERIAL_USE_UART4              FALSE
#define STM32_SERIAL_USE_UART5              FALSE
#define STM32_SERIAL_USE_LPUART1            FALSE

/*
 * SIO driver system settings.
 */
#define STM32_SIO_USE_USART1                FALSE
#define STM32_SIO_USE_USART2                FALSE
#define STM32_SIO_USE_USART3                FALSE
#define STM32_SIO_USE_UART4                 FALSE
#define STM32_SIO_USE_UART5                 FALSE
#define STM32_SIO_USE_LPUART1               FALSE

/*
 * SPI driver system settings.
 */
#define STM32_SPI_USE_SPI1                  FALSE
#define STM32_SPI_USE_SPI2                  FALSE
#define STM32_SPI_USE_SPI3                  FALSE
#define STM32_SPI_USE_SPI4                  FALSE
#define STM32_SPI_SPI1_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI1_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI2_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI2_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI3_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI3_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI4_RX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI4_TX_DMA_STREAM        STM32_DMA_STREAM_ID_ANY
#define STM32_SPI_SPI1_DMA_PRIORITY         1
#define STM32_SPI_SPI2_DMA_PRIORITY         1
#define STM32_SPI_SPI3_DMA_PRIORITY         1
#define STM32_SPI_SPI4_DMA_PRIORITY         1
#define STM32_SPI_SPI1_IRQ_PRIORITY         10
#define STM32_SPI_SPI2_IRQ_PRIORITY         10
#define STM32_SPI_SPI3_IRQ_PRIORITY         10
#define STM32_SPI_SPI4_IRQ_PRIORITY         10
#define STM32_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 */
#define STM32_ST_IRQ_PRIORITY               8
#define STM32_ST_USE_TIMER                  2

/*
 * TRNG driver system settings.
 */
#define STM32_TRNG_USE_RNG1                 FALSE

/*
 * UART driver system settings.
 */
#define STM32_UART_USE_USART1               FALSE
#define STM32_UART_USE_USART2               FALSE
#define STM32_UART_USE_USART3               FALSE
#define STM32_UART_USE_UART4                FALSE
#define STM32_UART_USE_UART5                FALSE
#define STM32_UART_USART1_RX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART1_TX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART2_RX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART2_TX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART3_RX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART3_TX_DMA_STREAM     STM32_DMA_STREAM_ID_ANY
#define STM32_UART_UART4_RX_DMA_STREAM      STM32_DMA_STREAM_ID_ANY
#define STM32_UART_UART4_TX_DMA_STREAM      STM32_DMA_STREAM_ID_ANY
#define STM32_UART_UART5_RX_DMA_STREAM      STM32_DMA_STREAM_ID_ANY
#define STM32_UART_UART5_TX_DMA_STREAM      STM32_DMA_STREAM_ID_ANY
#define STM32_UART_USART1_DMA_PRIORITY      0
#define STM32_UART_USART2_DMA_PRIORITY      0
#define STM32_UART_USART3_DMA_PRIORITY      0
#define STM32_UART_UART4_DMA_PRIORITY       0
#define STM32_UART_UART5_DMA_PRIORITY       0
#define STM32_UART_DMA_ERROR_HOOK(uartp)    osalSysHalt("DMA failure")

/*
 * USB driver system settings.
 */
#define STM32_USB_USE_USB1                  TRUE
#define STM32_USB_LOW_POWER_ON_SUSPEND      FALSE
#define STM32_USB_USB1_HP_IRQ_PRIORITY      5
#define STM32_USB_USB1_LP_IRQ_PRIORITY      5

/*
 * WDG driver system settings.
 */
#define STM32_WDG_USE_IWDG                  FALSE

/*
 * WSPI driver system settings.
 */
#define STM32_WSPI_USE_QUADSPI1             FALSE
#define STM32_WSPI_QUADSPI1_DMA_STREAM      STM32_DMA_STREAM_ID(2, 7)
#define STM32_WSPI_QUADSPI1_PRESCALER_VALUE 1

#endif /* MCUCONF_H */
