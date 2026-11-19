/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio.

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
 * SK32F0xx drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * The SK32F0xx family is register-compatible with STM32F072 except for the
 * USB IP (musbfsfc) and the peripheral set: the SK32F077 variant does not
 * have the TIM1, TIM2, SPI2 and I2C2 units (see the SK32_HAS_* macros in
 * sk32_registry.h).  The SK32 port provides NATIVE low level drivers for the
 * whole peripheral set (clocks, SysTick ST, ISR aggregation, GPIO/PAL, USB,
 * USART serial, SPI, I2C, EFL, SLED, KBCU, GPT, ADC, RTC, WDG and the
 * Cortex-M0 STOP low-power), and does NOT pull in any shared STM32 LLD (the
 * SK32F0xx port/platform.mk no longer references the STM32 TIMv1/ADCv1/USARTv2
 * LLDs).  The SK32_* settings below are consumed by these native drivers.
 * The STM32F0xx_MCUCONF define and the STM32_* names are retained only for
 * CMSIS/driver compatibility headers; they do not gate any shared LLD.
 *
 * IRQ priorities:
 * 3...0       Lowest...Highest.
 *
 * DMA priorities:
 * 0...3        Lowest...Highest.
 */

#define STM32F0xx_MCUCONF
#define SK32F0xx_MCUCONF

/*
 * SK32 HAL system clock settings.
 * SK32_* defaults (72MHz system clock from the 8MHz HSI through the main
 * PLL, HSI/PREDIV1(=1) * PLLMUL(=9)) are applied by hal_lld.h when not
 * defined here; they are repeated below for clarity.
 */
#define SK32_SW                            SK32_SW_PLL
#define SK32_PREDIV_VALUE                  1
#define SK32_PLLMUL_VALUE                  9
#define SK32_HPRE                          SK32_HPRE_DIV1
#define SK32_PPRE                          SK32_PPRE_DIV1

/*
 * STM32 HAL driver system settings (shared LLD requirements).
 */
#define STM32_NO_INIT                       FALSE
#define STM32_PVD_ENABLE                    FALSE
#define STM32_PLS                           STM32_PLS_LEV0
#define STM32_HSI_ENABLED                   TRUE
#define STM32_HSI14_ENABLED                 TRUE
#define STM32_HSI48_ENABLED                 FALSE
#define STM32_LSI_ENABLED                   TRUE
#define STM32_HSE_ENABLED                   FALSE
#define STM32_LSE_ENABLED                   FALSE
#define STM32_SW                            STM32_SW_PLL
#define STM32_PLLSRC                        STM32_PLLSRC_HSI_DIV2
#define STM32_PREDIV_VALUE                  1
#define STM32_PLLMUL_VALUE                  12
#define STM32_HPRE                          STM32_HPRE_DIV1
#define STM32_PPRE                          STM32_PPRE_DIV1
#define STM32_MCOSEL                        STM32_MCOSEL_NOCLOCK
#define STM32_MCOPRE                        STM32_MCOPRE_DIV1
#define STM32_PLLNODIV                      STM32_PLLNODIV_DIV2
#define STM32_USBSW                         STM32_USBSW_HSI48
#define STM32_CECSW                         STM32_CECSW_HSI
/* No STM32_I2C1SW setting: the SK32 CFGR3 has no I2C1 clock selection bits,
   the I2C1 input clock is fixed (analyzed as the 8MHz HSI, see the SK32 I2C
   driver settings below).*/
#define STM32_USART1SW                      STM32_USART1SW_PCLK
#define STM32_RTCSEL                        STM32_RTCSEL_LSI

/*
 * IRQ system settings.
 * The EXTI line IRQ priorities are configured through the native
 * SK32_IRQ_EXTI*_PRIORITY defaults in sk32_isr.h (priority 3), the shared
 * STM32 EXTIv1/GPIOv2 layers are not used by this port.
 */
#define STM32_IRQ_USART1_PRIORITY           3
#define STM32_IRQ_USART2_PRIORITY           3
#define STM32_IRQ_USART3_8_PRIORITY         3

/*
 * ADC driver system settings.
 */
#define STM32_ADC_USE_ADC1                  FALSE
#define STM32_ADC_ADC1_CFGR2                ADC_CFGR2_CKMODE_ADCCLK
#define STM32_ADC_ADC1_DMA_PRIORITY         2
#define STM32_ADC_ADC1_DMA_IRQ_PRIORITY     2
#define STM32_ADC_ADC1_DMA_STREAM           STM32_DMA_STREAM_ID(1, 1)

/*
 * CAN driver system settings.
 */
#define STM32_CAN_USE_CAN1                  FALSE
#define STM32_CAN_CAN1_IRQ_PRIORITY         3

/*
 * DAC driver system settings.
 */
#define STM32_DAC_DUAL_MODE                 FALSE
#define STM32_DAC_USE_DAC1_CH1              FALSE
#define STM32_DAC_USE_DAC1_CH2              FALSE
#define STM32_DAC_DAC1_CH1_IRQ_PRIORITY     2
#define STM32_DAC_DAC1_CH2_IRQ_PRIORITY     2
#define STM32_DAC_DAC1_CH1_DMA_PRIORITY     2
#define STM32_DAC_DAC1_CH2_DMA_PRIORITY     2
#define STM32_DAC_DAC1_CH1_DMA_STREAM       STM32_DMA_STREAM_ID(1, 3)
#define STM32_DAC_DAC1_CH2_DMA_STREAM       STM32_DMA_STREAM_ID(1, 4)

/*
 * GPT driver system settings.
 * The SK32F077 variant has the TIM3, TIM6, TIM16 and TIM17 timers only,
 * the TIM1/TIM2 units are not present (see SK32_HAS_TIM* in the registry)
 * so they are not configured here.
 */
#define STM32_GPT_USE_TIM3                  FALSE
#define STM32_GPT_USE_TIM6                  FALSE
#define STM32_GPT_USE_TIM16                 FALSE
#define STM32_GPT_USE_TIM17                 FALSE
#define STM32_GPT_TIM3_IRQ_PRIORITY         2
#define STM32_GPT_TIM6_IRQ_PRIORITY         2
#define STM32_GPT_TIM16_IRQ_PRIORITY        2
#define STM32_GPT_TIM17_IRQ_PRIORITY        2

/*
 * I2C driver system settings.
 * The SK32 I2C is a legacy CR1/CR2/SR1/SR2/DR/CCR unit (no TRISE register)
 * served by the native interrupt-driven SK32 driver; the shared STM32
 * I2Cv1/I2Cv2 LLDs are not usable on this platform (TRISE access, DMA
 * streams and the EV/ER IRQ split do not apply).  The I2C1 input clock is
 * fixed: the CFGR3 register has no I2C1SW bits and the clock is analyzed as
 * the 8MHz HSI for the CCR/FREQ computation (to be validated on hardware).
 * I2C1 is wired to PB6 (SCL) and PB7 (SDA), alternate function 13 (open
 * drain, external pull-ups) as validated by the SK32 IIC testhal.
 * SK32_I2C_USE_I2C1 defaults to FALSE: the native driver (hal_i2c_lld.c)
 * is only pulled into the build when HAL_USE_I2C is TRUE in halconf.h, in
 * which case this switch must also be set to TRUE.
 */
#define SK32_I2C_USE_I2C1                   TRUE
#define SK32_I2C_I2C1_PRIORITY              3
#define SK32_I2C_BUSY_TIMEOUT               50

/*
 * I2S driver system settings.
 * I2S is implemented on the SPI2 peripheral which is not present on the
 * SK32F077 variant, only the (dummy) SPI1 based settings are kept.
 */
#define STM32_I2S_USE_SPI1                  FALSE
#define STM32_I2S_SPI1_MODE                 (STM32_I2S_MODE_MASTER |        \
                                             STM32_I2S_MODE_RX)
#define STM32_I2S_SPI1_IRQ_PRIORITY         2
#define STM32_I2S_SPI1_DMA_PRIORITY         1
#define STM32_I2S_SPI1_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 2)
#define STM32_I2S_SPI1_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 3)
#define STM32_I2S_DMA_ERROR_HOOK(i2sp)      osalSysHalt("DMA failure")

/*
 * ICU driver system settings.
 * Only the TIM3 unit is kept, TIM1/TIM2 are not present on the SK32F077
 * variant and the shared ICU LLD does not support the TIM16/TIM17 units.
 */
#define STM32_ICU_USE_TIM3                  FALSE
#define STM32_ICU_TIM3_IRQ_PRIORITY         3

/*
 * PWM driver system settings.
 * The SK32F077 variant has the TIM3, TIM16 and TIM17 timers only, TIM1/TIM2
 * are not present so they are not configured here.
 */
#define STM32_PWM_USE_ADVANCED              FALSE
#define STM32_PWM_USE_TIM3                  FALSE
#define STM32_PWM_USE_TIM16                 FALSE
#define STM32_PWM_USE_TIM17                 FALSE
#define STM32_PWM_TIM3_IRQ_PRIORITY         3
#define STM32_PWM_TIM16_IRQ_PRIORITY        3
#define STM32_PWM_TIM17_IRQ_PRIORITY        3

/*
 * SERIAL driver system settings.
 * The SK32 native serial driver (SR/DR USART) is selected through the
 * SK32_SERIAL_USE_USARTx switches.  No SK32 keyboard enables HAL_USE_SERIAL
 * (QMK console goes over the USB console endpoint, not USART), so all USART
 * channels stay disabled to keep this file consistent with halconf.h.  If a
 * future board wants a real UART console, set HAL_USE_SERIAL TRUE in its
 * halconf.h and flip the matching switch to TRUE.
 */
#define SK32_SERIAL_USE_USART1              FALSE
#define SK32_SERIAL_USE_USART2              FALSE
#define SK32_SERIAL_USART1_PRIORITY         3
#define SK32_SERIAL_USART2_PRIORITY         3

/*
 * SPI driver system settings.
 * The SK32 SPI is a legacy CR1/CR2/SR/DR unit (SPIv1 class) served by the
 * native SK32 driver selected through the SK32_SPI_USE_SPIx switches; the
 * shared STM32 SPIv2 LLD is not part of this platform.  The driver is
 * interrupt-driven by default, SPI1 can optionally be switched to its DMA1
 * based transfer engine with SK32_SPI_USE_DMA (SPI2 has no DMA request
 * lines).  The SPI2 unit is not present on the SK32F077 variant and is not
 * configured.
 */
#define SK32_SPI_USE_SPI1                   FALSE
#define SK32_SPI_USE_SPI2                   FALSE
#define SK32_SPI_SPI1_PRIORITY              3
#define SK32_SPI_SPI2_PRIORITY              3
#define STM32_SPI_USE_SPI1                  FALSE
#define STM32_SPI_SPI1_DMA_PRIORITY         1
#define STM32_SPI_SPI1_IRQ_PRIORITY         2
#define STM32_SPI_SPI1_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 2)
#define STM32_SPI_SPI1_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 3)
#define STM32_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 * The shared STM32 ST driver is not used by this port (native SysTick based
 * ST) but its TIM2 reference would name a timer that is not present on the
 * SK32F077 variant, it is aligned to the available TIM3 unit.
 */
#define STM32_ST_IRQ_PRIORITY               2
#define STM32_ST_USE_TIMER                  3

/*
 * SK32 ST driver system settings.
 * The SK32 port uses its native SysTick-based ST driver which requires
 * periodic mode (CH_CFG_ST_TIMEDELTA is forced to zero for this series in
 * platforms/chibios/mcu_selection.mk), the STM32_ST_* settings above are
 * only kept for the shared STM32 low level drivers.
 */
#define SK32_ST_IRQ_PRIORITY                2

/*
 * UART driver system settings.
 */
#define STM32_UART_USE_USART1               FALSE
#define STM32_UART_USE_USART2               FALSE
#define STM32_UART_USE_USART3               FALSE
#define STM32_UART_USE_UART4                FALSE
#define STM32_UART_USART1_DMA_PRIORITY      0
#define STM32_UART_USART2_DMA_PRIORITY      0
#define STM32_UART_USART3_DMA_PRIORITY      0
#define STM32_UART_UART4_DMA_PRIORITY       0
#define STM32_UART_USART1_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 3)
#define STM32_UART_USART1_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 2)
#define STM32_UART_USART2_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 5)
#define STM32_UART_USART2_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 4)
#define STM32_UART_USART3_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 3)
#define STM32_UART_USART3_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 2)
#define STM32_UART_UART4_RX_DMA_STREAM      STM32_DMA_STREAM_ID(1, 6)
#define STM32_UART_UART4_TX_DMA_STREAM      STM32_DMA_STREAM_ID(1, 7)
#define STM32_UART_DMA_ERROR_HOOK(uartp)    osalSysHalt("DMA failure")

/*
 * USB driver system settings.
 * The SK32 musbfsfc USB LLD (not the STM32 USBv1 LLD) is used by this port.
 */
#define STM32_USB_USE_USB1                  TRUE
#define STM32_USB_LOW_POWER_ON_SUSPEND      FALSE
#define STM32_USB_USB1_LP_IRQ_PRIORITY      3

/*
 * RTC driver system settings.
 * The SK32 RTC is part of the backup domain and is served by the native
 * SK32 driver; the shared STM32 RTCv2 LLD is not used (it requires the
 * STM32 registry macros and the EXTI driver for its interrupt routing).
 * SK32_RTC_USE_LSE selects the 32768Hz LSE crystal as clock source, when
 * FALSE the internal LSI oscillator is used; the matching PRER prescalers
 * are derived in hal_rtc_lld.h.  The STM32_RTCSEL setting above belongs to
 * the (unused) shared STM32 driver.
 */
#define SK32_RTC_USE_LSE                    FALSE
#define SK32_RTC_IRQ_PRIORITY               3

/*
 * WDG driver system settings.
 * The SK32 port provides a native driver for both watchdog controllers:
 * the IWDG (WDGD1, clocked by the LSI oscillator, no interrupt) and the
 * WWDG (WDGD2, clocked by PCLK1).  The shared STM32 xWDGv1 LLD is not used
 * (IWDG only, STM32 registry based).  Both switches default to FALSE, set
 * them to TRUE (together with HAL_USE_WDG in halconf.h) to enable the
 * corresponding driver.
 */
#define SK32_WDG_USE_IWDG                   FALSE
#define SK32_WDG_USE_WWDG                   FALSE
#define STM32_WDG_USE_IWDG                  FALSE

#endif /* MCUCONF_H */
