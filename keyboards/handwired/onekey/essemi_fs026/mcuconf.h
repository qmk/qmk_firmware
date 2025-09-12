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

#define ES32_FS026_MCUCONF
#define ES32_ES32F0283_MCUCONF

/*
 * HAL driver system settings.
 */
#define ES32_NO_INIT   FALSE

/*system_clk select

MD_RCU_SW_SYSCLK_HRC   = HRC selected as system clock
MD_RCU_SW_SYSCLK_HOSC  = HOSC selected as system clock
MD_RCU_SW_SYSCLK_PLL0  = PLL0 selected as system clock
MD_RCU_SW_SYSCLK_HRC48 = HRC48 selected as system clock
*/
#define ES32_SYSCLK_SOURSE_SELECT   MD_RCU_SW_SYSCLK_PLL0

/*external clk config*/
#define ES32_HOSC_CLK_EN            FALSE
#define ES32_HOSC_CLK_FREQ          8

/*pll clk config

MD_RCU_PLLSRC_HRC     = HRC selected as PLL reference clock
MD_RCU_PLLSRC_HOSC    = HOSC selected as PLL reference clock
MD_RCU_PLLSRC_HRC48   = HRC48 selected as PLL reference clock

MD_RCU_PLLCLK_PASS    = 0
MD_RCU_PLLCLK_4M      = 4000000
MD_RCU_PLLCLK_8M      = 8000000
MD_RCU_PLLCLK_12M     = 12000000
MD_RCU_PLLCLK_16M     = 16000000
MD_RCU_PLLCLK_24M     = 24000000
MD_RCU_PLLCLK_32M     = 32000000
MD_RCU_PLLCLK_36M     = 36000000
MD_RCU_PLLCLK_40M     = 40000000
MD_RCU_PLLCLK_48M     = 48000000
MD_RCU_PLLCLK_64M     = 64000000
MD_RCU_PLLCLK_72M     = 72000000
*/
#define ES32_PLL_CLK_EN             TRUE
#define ES32_PLL_SOURSE_SELECT      MD_RCU_PLLSRC_HRC48
#define ES32_PLL_CLK_FREQ           MD_RCU_PLLCLK_72M

/*bus clk config

MD_RCU_HPRE_SYSCLK_DIV_1     = SYSCLK not divided
MD_RCU_HPRE_SYSCLK_DIV_2     = SYSCLK divided by 2
MD_RCU_HPRE_SYSCLK_DIV_4     = SYSCLK divided by 4
MD_RCU_HPRE_SYSCLK_DIV_8     = SYSCLK divided by 8
MD_RCU_HPRE_SYSCLK_DIV_16    = SYSCLK divided by 16
MD_RCU_HPRE_SYSCLK_DIV_64    = SYSCLK divided by 64
MD_RCU_HPRE_SYSCLK_DIV_128   = SYSCLK divided by 128
MD_RCU_HPRE_SYSCLK_DIV_256   = SYSCLK divided by 256
MD_RCU_HPRE_SYSCLK_DIV_512   = @brief SYSCLK divided by 512

MD_RCU_PPRE_HCLK_DIV_1       = HCLK not divided
MD_RCU_PPRE_HCLK_DIV_2       = HCLK divided by 2
MD_RCU_PPRE_HCLK_DIV_4       = HCLK divided by 4
MD_RCU_PPRE_HCLK_DIV_8       = HCLK divided by 8
MD_RCU_PPRE_HCLK_DIV_16      = HCLK divided by 16
*/
#define ES32_BUS_DIV_HPRE    MD_RCU_HPRE_SYSCLK_DIV_1
#define ES32_BUS_DIV_PPRE    MD_RCU_PPRE_HCLK_DIV_1

/*
 * GPIO driver system settings.
 */
#define ES32_USB_USE_GPIO                   TRUE

/*
 * EXTI driver system settings.
 */
#define ES32_IRQ_EXTI0_1_PRIORITY            6
#define ES32_IRQ_EXTI2_3_PRIORITY            6
#define ES32_IRQ_EXTI4_15_PRIORITY           6

/*
 * ADC driver system settings.
 */
#define ADC_COUNT 1
#define USE_ADCV2

#define ADC_SQR3_SQ1_N(n)       ((n) << 0)  /**< @brief 1st channel in seq. */
#define ADC_SQR3_SQ2_N(n)       ((n) << 5)  /**< @brief 2nd channel in seq. */
#define ADC_SQR3_SQ3_N(n)       ((n) << 10) /**< @brief 3rd channel in seq. */
#define ADC_SQR3_SQ4_N(n)       ((n) << 15) /**< @brief 4th channel in seq. */
#define ADC_SQR3_SQ5_N(n)       ((n) << 20) /**< @brief 5th channel in seq. */
#define ADC_SQR3_SQ6_N(n)       ((n) << 25) /**< @brief 6th channel in seq. */

#define ADC_SQR2_SQ7_N(n)       ((n) << 0)  /**< @brief 7th channel in seq. */
#define ADC_SQR2_SQ8_N(n)       ((n) << 5)  /**< @brief 8th channel in seq. */
#define ADC_SQR2_SQ9_N(n)       ((n) << 10) /**< @brief 9th channel in seq. */
#define ADC_SQR2_SQ10_N(n)      ((n) << 15) /**< @brief 10th channel in seq.*/
#define ADC_SQR2_SQ11_N(n)      ((n) << 20) /**< @brief 11th channel in seq.*/
#define ADC_SQR2_SQ12_N(n)      ((n) << 25) /**< @brief 12th channel in seq.*/

#define ADC_SQR1_SQ13_N(n)      ((n) << 0)  /**< @brief 13th channel in seq.*/
#define ADC_SQR1_SQ14_N(n)      ((n) << 5)  /**< @brief 14th channel in seq.*/
#define ADC_SQR1_SQ15_N(n)      ((n) << 10) /**< @brief 15th channel in seq.*/
#define ADC_SQR1_SQ16_N(n)      ((n) << 15) /**< @brief 16th channel in seq.*/

#define ADC_SMPR2_SMP_AN0(n)    ((n) << 0)  /**< @brief AN0 sampling time.  */
#define ADC_SMPR2_SMP_AN1(n)    ((n) << 3)  /**< @brief AN1 sampling time.  */
#define ADC_SMPR2_SMP_AN2(n)    ((n) << 6)  /**< @brief AN2 sampling time.  */
#define ADC_SMPR2_SMP_AN3(n)    ((n) << 9)  /**< @brief AN3 sampling time.  */
#define ADC_SMPR2_SMP_AN4(n)    ((n) << 12) /**< @brief AN4 sampling time.  */
#define ADC_SMPR2_SMP_AN5(n)    ((n) << 15) /**< @brief AN5 sampling time.  */
#define ADC_SMPR2_SMP_AN6(n)    ((n) << 18) /**< @brief AN6 sampling time.  */
#define ADC_SMPR2_SMP_AN7(n)    ((n) << 21) /**< @brief AN7 sampling time.  */
#define ADC_SMPR2_SMP_AN8(n)    ((n) << 24) /**< @brief AN8 sampling time.  */
#define ADC_SMPR2_SMP_AN9(n)    ((n) << 27) /**< @brief AN9 sampling time.  */

#define ADC_SMPR1_SMP_AN10(n)   ((n) << 0)  /**< @brief AN10 sampling time. */
#define ADC_SMPR1_SMP_AN11(n)   ((n) << 3)  /**< @brief AN11 sampling time. */
#define ADC_SMPR1_SMP_AN12(n)   ((n) << 6)  /**< @brief AN12 sampling time. */
#define ADC_SMPR1_SMP_AN13(n)   ((n) << 9)  /**< @brief AN13 sampling time. */
#define ADC_SMPR1_SMP_AN14(n)   ((n) << 12) /**< @brief AN14 sampling time. */
#define ADC_SMPR1_SMP_AN15(n)   ((n) << 15) /**< @brief AN15 sampling time. */

#define ADC_SAMPLING_RATE ADC_SMPR_SMP_1P5
#define ES32_ADC_USE_ADC1 TRUE
#define ES32_ADC1_HANDLER Vector70

/*
 * GPT driver system settings.
 */
#define ES32_GPT_USE_AD16C4T1 FALSE
#define ES32_GPT_USE_GP32C4T1 FALSE
#define ES32_GPT_USE_GP16C4T1 FALSE
#define ES32_GPT_USE_GP16C4T2 TRUE
#define ES32_GPT_USE_GP16C4T3 FALSE
#define ES32_GPT_USE_GP16C2T1 FALSE
#define ES32_GPT_USE_GP16C2T2 FALSE
#define ES32_GPT_USE_GP16C2T3 FALSE
#define ES32_GPT_USE_GP16C2T4 FALSE
#define ES32_GPT_USE_BS16T1   FALSE
#define ES32_GPT_AD16C4T1_IRQ_PRIORITY         7
#define ES32_GPT_GP32C4T1_IRQ_PRIORITY         7
#define ES32_GPT_GP16C4T1_IRQ_PRIORITY         7
#define ES32_GPT_GP16C4T2_IRQ_PRIORITY         7
#define ES32_GPT_GP16C4T3_IRQ_PRIORITY         7
#define ES32_GPT_GP16C2T1_IRQ_PRIORITY         7
#define ES32_GPT_GP16C2T2_IRQ_PRIORITY         7
#define ES32_GPT_GP16C2T3_IRQ_PRIORITY         7
#define ES32_GPT_GP16C2T4_IRQ_PRIORITY         7
#define ES32_GPT_BS16T1_IRQ_PRIORITY           7

/*
 * ICU driver system settings.
 */
#define ES32_ICU_USE_AD16C4T1 FALSE
#define ES32_ICU_USE_GP32C4T1 FALSE
#define ES32_ICU_USE_GP16C4T1 FALSE
#define ES32_ICU_USE_GP16C4T2 FALSE
#define ES32_ICU_USE_GP16C4T3 FALSE
#define ES32_ICU_USE_GP16C2T1 FALSE
#define ES32_ICU_USE_GP16C2T2 FALSE
#define ES32_ICU_USE_GP16C2T3 FALSE
#define ES32_ICU_USE_GP16C2T4 FALSE
#define ES32_ICU_AD16C4T1_IRQ_PRIORITY 7
#define ES32_ICU_GP32C4T1_IRQ_PRIORITY 7
#define ES32_ICU_GP16C4T1_IRQ_PRIORITY 7
#define ES32_ICU_GP16C4T2_IRQ_PRIORITY 7
#define ES32_ICU_GP16C4T3_IRQ_PRIORITY 7
#define ES32_ICU_GP16C2T1_IRQ_PRIORITY 7
#define ES32_ICU_GP16C2T2_IRQ_PRIORITY 7
#define ES32_ICU_GP16C2T3_IRQ_PRIORITY 7
#define ES32_ICU_GP16C2T4_IRQ_PRIORITY 7

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
#define ES32_SERIAL_USE_UART1              FALSE
#define ES32_SERIAL_USE_UART2              FALSE
#define ES32_SERIAL_USE_UART3              FALSE
#define ES32_SERIAL_USE_UART4              FALSE
#define ES32_SERIAL_UART1_PRIORITY        7
#define ES32_SERIAL_UART2_PRIORITY        7
#define ES32_SERIAL_UART3_PRIORITY        7
#define ES32_SERIAL_UART4_PRIORITY        7

/*
 * SPI driver system settings.
 */
#define ES32_SPI_USE_SPI1                  FALSE
#define ES32_SPI_USE_SPI2                  FALSE
#define ES32_SPI_USE_SPI3                  FALSE
#define ES32_SPI_SPI1_IRQ_PRIORITY         10
#define ES32_SPI_SPI2_IRQ_PRIORITY         10
#define ES32_SPI_SPI3_IRQ_PRIORITY         10

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
#define ES32_UART_USE_UART4                 FALSE
#define ES32_UART_UART1_IRQ_PRIORITY        12
#define ES32_UART_UART2_IRQ_PRIORITY        12
#define ES32_UART_UART3_IRQ_PRIORITY        12
#define ES32_UART_UART4_IRQ_PRIORITY        12

/*
 * PWM driver system settings.
 */
#define ES32_PWM_USE_AD16C4T1 FALSE
#define ES32_PWM_USE_GP32C4T1 FALSE
#define ES32_PWM_USE_GP16C4T1 FALSE
#define ES32_PWM_USE_GP16C4T2 TRUE
#define ES32_PWM_USE_GP16C4T3 FALSE
#define ES32_PWM_USE_GP16C2T1 FALSE
#define ES32_PWM_USE_GP16C2T2 FALSE
#define ES32_PWM_USE_GP16C2T3 FALSE
#define ES32_PWM_USE_GP16C2T4 FALSE
#define ES32_PWM_AD16C4T1_IRQ_PRIORITY 7
#define ES32_PWM_GP32C4T1_IRQ_PRIORITY 7
#define ES32_PWM_GP16C4T1_IRQ_PRIORITY 7
#define ES32_PWM_GP16C4T2_IRQ_PRIORITY 7
#define ES32_PWM_GP16C4T3_IRQ_PRIORITY 7
#define ES32_PWM_GP16C2T1_IRQ_PRIORITY 7
#define ES32_PWM_GP16C2T2_IRQ_PRIORITY 7
#define ES32_PWM_GP16C2T3_IRQ_PRIORITY 7
#define ES32_PWM_GP16C2T4_IRQ_PRIORITY 7

/*
 * USB driver system settings.
 */
#define ES32_USB_USE_USB1                   TRUE
#define ES32_USB_USB1_IRQ_PRIORITY          13
#define ES32_USE_USB_SOF_TRIM_HRC48         TRUE

#endif /* MCUCONF_H */
