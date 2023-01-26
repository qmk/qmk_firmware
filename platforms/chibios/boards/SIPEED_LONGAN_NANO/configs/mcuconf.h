/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2021 Stefan Kerkmann

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

#pragma once

#define GD32VF103_MCUCONF
#define GD32VF103CB

/*
 * GD32VF103 drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 0...15       Lowest...Highest.
 *
 * DMA priorities:
 * 0...3        Lowest...Highest.
 */

/*
 * HAL driver system settings.
*/

#if defined(OVERCLOCK_120MHZ)
/* (8MHz / 2) * 30 = 120MHz Sysclock */
#define GD32_ALLOW_120MHZ_SYSCLK
#define GD32_PLLMF_VALUE                     30
#define GD32_USBFSPSC                        GD32_USBFSPSC_DIV2P5
#else
/* (8MHz / 2) * 24 = 96MHz Sysclock */
#define GD32_PLLMF_VALUE                     24
#define GD32_USBFSPSC                        GD32_USBFSPSC_DIV2
#endif

#define GD32_NO_INIT                         FALSE
#define GD32_IRC8M_ENABLED                   TRUE
#define GD32_IRC40K_ENABLED                  FALSE
#define GD32_HXTAL_ENABLED                   TRUE
#define GD32_LXTAL_ENABLED                   FALSE
#define GD32_SCS                             GD32_SCS_PLL
#define GD32_PLLSEL                          GD32_PLLSEL_PREDV0
#define GD32_PREDV0SEL                       GD32_PREDV0SEL_HXTAL
#define GD32_PREDV0_VALUE                    2
#define GD32_PREDV1_VALUE                    2
#define GD32_PLL1MF_VALUE                    14
#define GD32_PLL2MF_VALUE                    13
#define GD32_AHBPSC                          GD32_AHBPSC_DIV1
#define GD32_APB1PSC                         GD32_APB1PSC_DIV2
#define GD32_APB2PSC                         GD32_APB2PSC_DIV1
#define GD32_ADCPSC                          GD32_ADCPSC_DIV16
#define GD32_USB_CLOCK_REQUIRED              TRUE
#define GD32_I2S_CLOCK_REQUIRED              FALSE
#define GD32_CKOUT0SEL                       GD32_CKOUT0SEL_NOCLOCK
#define GD32_RTCSRC                          GD32_RTCSRC_NOCLOCK
#define GD32_PVD_ENABLE                      FALSE
#define GD32_LVDT                            GD32_LVDT_LEV0

/*
 * ECLIC system settings.
 */
#define ECLIC_TRIGGER_DEFAULT                ECLIC_POSTIVE_EDGE_TRIGGER
#define ECLIC_DMA_TRIGGER                    ECLIC_TRIGGER_DEFAULT

/*
 * IRQ system settings.
 */
#define GD32_IRQ_EXTI0_PRIORITY              6
#define GD32_IRQ_EXTI1_PRIORITY              6
#define GD32_IRQ_EXTI2_PRIORITY              6
#define GD32_IRQ_EXTI3_PRIORITY              6
#define GD32_IRQ_EXTI4_PRIORITY              6
#define GD32_IRQ_EXTI5_9_PRIORITY            6
#define GD32_IRQ_EXTI10_15_PRIORITY          6
#define GD32_IRQ_EXTI0_TRIGGER               ECLIC_TRIGGER_DEFAULT
#define GD32_IRQ_EXTI1_TRIGGER               ECLIC_TRIGGER_DEFAULT
#define GD32_IRQ_EXTI2_TRIGGER               ECLIC_TRIGGER_DEFAULT
#define GD32_IRQ_EXTI3_TRIGGER               ECLIC_TRIGGER_DEFAULT
#define GD32_IRQ_EXTI4_TRIGGER               ECLIC_TRIGGER_DEFAULT
#define GD32_IRQ_EXTI5_9_TRIGGER             ECLIC_TRIGGER_DEFAULT
#define GD32_IRQ_EXTI10_15_TRIGGER           ECLIC_TRIGGER_DEFAULT

/*
 * ADC driver system settings.
 */
#define GD32_ADC_USE_ADC0                    FALSE
#define GD32_ADC_ADC0_DMA_PRIORITY           2
#define GD32_ADC_ADC0_IRQ_PRIORITY           6

/*
 * CAN driver system settings.
 */
#define GD32_CAN_USE_CAN0                    FALSE
#define GD32_CAN_CAN0_IRQ_PRIORITY           11
#define GD32_CAN_USE_CAN1                    FALSE
#define GD32_CAN_CAN1_IRQ_PRIORITY           11
#define GD32_CAN_CAN0_IRQ_TRIGGER            ECLIC_TRIGGER_DEFAULT
#define GD32_CAN_CAN1_IRQ_TRIGGER            ECLIC_TRIGGER_DEFAULT

/*
 * CRC driver system settings.
 */
#define GD32_CRC_USE_CRC0                   FALSE
#define GD32_CRC_CRC0_DMA_IRQ_PRIORITY      14
#define GD32_CRC_CRC0_DMA_PRIORITY          2
#define GD32_CRC_CRC0_DMA_STREAM            GD32_DMA_STREAM_ID(0, 0)
#define CRC_USE_DMA                         FALSE
#define CRCSW_USE_CRC1                      FALSE
#define CRCSW_CRC32_TABLE                   FALSE
#define CRCSW_CRC16_TABLE                   FALSE
#define CRCSW_PROGRAMMABLE                  FALSE

/*
 * DAC driver system settings.
 */
#define GD32_DAC_USE_DAC_CH1                FALSE
#define GD32_DAC_USE_DAC_CH2                FALSE

/*
 * GPT driver system settings.
 */
#define GD32_GPT_USE_TIM0                   FALSE
#define GD32_GPT_USE_TIM1                   FALSE
#define GD32_GPT_USE_TIM2                   FALSE
#define GD32_GPT_USE_TIM3                   FALSE
#define GD32_GPT_USE_TIM4                   FALSE
#define GD32_GPT_TIM0_IRQ_PRIORITY          7
#define GD32_GPT_TIM1_IRQ_PRIORITY          7
#define GD32_GPT_TIM2_IRQ_PRIORITY          7
#define GD32_GPT_TIM3_IRQ_PRIORITY          7
#define GD32_GPT_TIM4_IRQ_PRIORITY          7
#define GD32_GPT_TIM0_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_GPT_TIM1_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_GPT_TIM2_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_GPT_TIM3_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_GPT_TIM4_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_GPT_TIM5_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_GPT_TIM6_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT

/*
 * I2S driver system settings.
 */
#define GD32_I2S_USE_SPI1                   FALSE
#define GD32_I2S_USE_SPI2                   FALSE
#define GD32_I2S_SPI1_IRQ_PRIORITY          10
#define GD32_I2S_SPI2_IRQ_PRIORITY          10
#define GD32_I2S_SPI1_DMA_PRIORITY          1
#define GD32_I2S_SPI2_DMA_PRIORITY          1
#define GD32_I2S_DMA_ERROR_HOOK(i2sp)       osalSysHalt("DMA failure")

/*
 * I2C driver system settings.
 */
#define GD32_I2C_USE_I2C0                   FALSE
#define GD32_I2C_USE_I2C1                   FALSE
#define GD32_I2C_BUSY_TIMEOUT               50
#define GD32_I2C_I2C0_IRQ_PRIORITY          10
#define GD32_I2C_I2C1_IRQ_PRIORITY          5
#define GD32_I2C_I2C0_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_I2C_I2C1_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_I2C_I2C0_DMA_PRIORITY          2
#define GD32_I2C_I2C1_DMA_PRIORITY          2
#define GD32_I2C_DMA_ERROR_HOOK(i2cp)       osalSysHalt("DMA failure")

/*
 * ICU driver system settings.
 */
#define GD32_ICU_USE_TIM0                   FALSE
#define GD32_ICU_USE_TIM1                   FALSE
#define GD32_ICU_USE_TIM2                   FALSE
#define GD32_ICU_USE_TIM3                   FALSE
#define GD32_ICU_USE_TIM4                   FALSE
#define GD32_ICU_TIM0_IRQ_PRIORITY          7
#define GD32_ICU_TIM1_IRQ_PRIORITY          7
#define GD32_ICU_TIM2_IRQ_PRIORITY          7
#define GD32_ICU_TIM3_IRQ_PRIORITY          7
#define GD32_ICU_TIM4_IRQ_PRIORITY          7
#define GD32_ICU_TIM0_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_ICU_TIM1_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_ICU_TIM2_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_ICU_TIM3_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_ICU_TIM4_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT

/*
 * PWM driver system settings.
 */
#define GD32_PWM_USE_ADVANCED               FALSE
#define GD32_PWM_USE_TIM0                   FALSE
#define GD32_PWM_USE_TIM1                   FALSE
#define GD32_PWM_USE_TIM2                   FALSE
#define GD32_PWM_USE_TIM3                   FALSE
#define GD32_PWM_USE_TIM4                   FALSE
#define GD32_PWM_TIM0_IRQ_PRIORITY          10
#define GD32_PWM_TIM1_IRQ_PRIORITY          10
#define GD32_PWM_TIM2_IRQ_PRIORITY          10
#define GD32_PWM_TIM3_IRQ_PRIORITY          10
#define GD32_PWM_TIM4_IRQ_PRIORITY          10
#define GD32_PWM_TIM0_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_PWM_TIM1_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_PWM_TIM2_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_PWM_TIM3_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_PWM_TIM4_IRQ_TRIGGER           ECLIC_TRIGGER_DEFAULT

/*
 * RTC driver system settings.
 */
#define GD32_RTC_IRQ_PRIORITY               15
#define GD32_RTC_IRQ_TRIGGER                ECLIC_TRIGGER_DEFAULT

/*
 * SERIAL driver system settings.
 */
#define GD32_SERIAL_USE_USART0              FALSE
#define GD32_SERIAL_USE_USART1              FALSE
#define GD32_SERIAL_USE_USART2              FALSE
#define GD32_SERIAL_USE_UART3               FALSE
#define GD32_SERIAL_USE_UART4               FALSE
#define GD32_SERIAL_USART0_PRIORITY         10
#define GD32_SERIAL_USART1_PRIORITY         10
#define GD32_SERIAL_USART2_PRIORITY         10
#define GD32_SERIAL_UART3_PRIORITY          10
#define GD32_SERIAL_UART4_PRIORITY          10
#define GD32_SERIAL_USART0_TRIGGER          ECLIC_TRIGGER_DEFAULT
#define GD32_SERIAL_USART1_TRIGGER          ECLIC_TRIGGER_DEFAULT
#define GD32_SERIAL_USART2_TRIGGER          ECLIC_TRIGGER_DEFAULT
#define GD32_SERIAL_UART3_TRIGGER           ECLIC_TRIGGER_DEFAULT
#define GD32_SERIAL_UART4_TRIGGER           ECLIC_TRIGGER_DEFAULT

/*
 * SPI driver system settings.
 */
#define GD32_SPI_USE_SPI0                   FALSE
#define GD32_SPI_USE_SPI1                   FALSE
#define GD32_SPI_USE_SPI2                   FALSE
#define GD32_SPI_SPI0_DMA_PRIORITY          1
#define GD32_SPI_SPI1_DMA_PRIORITY          1
#define GD32_SPI_SPI2_DMA_PRIORITY          1
#define GD32_SPI_SPI0_IRQ_PRIORITY          10
#define GD32_SPI_SPI1_IRQ_PRIORITY          10
#define GD32_SPI_SPI2_IRQ_PRIORITY          10
#define GD32_SPI_DMA_ERROR_HOOK(spip)       osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 */
#define GD32_ST_IRQ_PRIORITY                10
#define GD32_ST_IRQ_TRIGGER                 ECLIC_TRIGGER_DEFAULT
#define GD32_ST_USE_TIMER                   1

/*
 * UART driver system settings.
 */
#define GD32_UART_USE_USART0                FALSE
#define GD32_UART_USE_USART1                FALSE
#define GD32_UART_USE_USART2                FALSE
#define GD32_UART_USE_UART3                 FALSE
#define GD32_UART_USE_UART4                 FALSE
#define GD32_UART_USART0_IRQ_PRIORITY       10
#define GD32_UART_USART1_IRQ_PRIORITY       10
#define GD32_UART_USART2_IRQ_PRIORITY       10
#define GD32_UART_UART3_IRQ_PRIORITY        10
#define GD32_UART_UART4_IRQ_PRIORITY        10
#define GD32_UART_USART0_IRQ_TRIGGER        ECLIC_TRIGGER_DEFAULT
#define GD32_UART_USART1_IRQ_TRIGGER        ECLIC_TRIGGER_DEFAULT
#define GD32_UART_USART2_IRQ_TRIGGER        ECLIC_TRIGGER_DEFAULT
#define GD32_UART_UART3_IRQ_TRIGGER         ECLIC_TRIGGER_DEFAULT
#define GD32_UART_UART4_IRQ_TRIGGER         ECLIC_TRIGGER_DEFAULT
#define GD32_UART_USART0_DMA_PRIORITY       3
#define GD32_UART_USART1_DMA_PRIORITY       3
#define GD32_UART_USART2_DMA_PRIORITY       3
#define GD32_UART_UART3_DMA_PRIORITY        3
#define GD32_UART_UART4_DMA_PRIORITY        3
#define GD32_UART_DMA_ERROR_HOOK(uartp)     osalSysHalt("DMA failure")

/*
 * USB driver system settings.
 */
#define GD32_USB_USE_USBFS                  TRUE
#define GD32_USB_USBFS_IRQ_PRIORITY         10
#define GD32_USB_USBFS_IRQ_TRIGGER          ECLIC_TRIGGER_DEFAULT
#define GD32_USB_USBFS_RX_FIFO_SIZE         256

/*
 * WDG driver system settings.
 */
#define GD32_WDG_USE_FWDGT                  FALSE
