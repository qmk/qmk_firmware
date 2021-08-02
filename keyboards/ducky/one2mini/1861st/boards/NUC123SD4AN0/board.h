/*
    ChibiOS Driver element - Copyright (C) 2019 /u/KeepItUnder

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

#ifndef BOARD_H
#define BOARD_H

/*
 * Setup for Generic NUC123 board.
 */

/*
 * Board identifier.
 */
#define BOARD_NUC123SD4AN0
#define BOARD_NAME                  "Nuvoton NUC123SD4AN0 MCU"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 * NOTE: HSE is fitted.
 */
#if !defined(NUC123_LSECLK)
#define NUC123_LSECLK                0U
#endif

#define NUC123_LSEDRV                (3U << 3U)

#if !defined(NUC123_HSECLK)
#define NUC123_HSECLK                12000000U
#endif

//#define NUC123_HSE_BYPASS

/*
 * MCU type as defined in the NUC123 header.
 */
#define NUC123SD4AN0

/*
 * GPIO Multi Function Pin USB Setup
 * Requires Some GPIO pins to be disabled/set to USB
 */

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0                  0U
#define GPIOA_PIN1                  1U
#define GPIOA_PIN2                  2U
#define GPIOA_PIN3                  3U
#define GPIOA_PIN4                  4U
#define GPIOA_PIN5                  5U
#define GPIOA_PIN6                  6U
#define GPIOA_PIN7                  7U
#define GPIOA_PIN8                  8U
#define GPIOA_PIN9                  9U
#define GPIOA_SPI1_MISO0            10U
#define GPIOA_SPI1_CLK              11U
#define GPIOA_PWM0                  12U
#define GPIOA_PWM1                  13U
#define GPIOA_PWM2                  14U
#define GPIOA_PWM3                  15U

#define GPIOB_UART0_RXD             0U
#define GPIOB_UART0_TXD             1U
#define GPIOB_UART0_RTS             2U
#define GPIOB_UART0_CTS             3U
#define GPIOB_UART1_RXD             4U
#define GPIOB_UART1_TXD             5U
#define GPIOB_UART1_RTS             6U
#define GPIOB_UART1_CTS             7U
#define GPIOB_TM0                   8U
#define GPIOB_TM1                   9U
#define GPIOB_TM2                   10U
#define GPIOB_PIN11                 11U
#define GPIOB_CLK0                  12U
#define GPIOB_PIN13                 13U
#define GPIOB_INT0                  14U
#define GPIOB_INT1                  15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_ADC0                  0U
#define GPIOD_ADC1                  1U
#define GPIOD_ADC2                  2U
#define GPIOD_ADC3                  3U
#define GPIOD_ADC4                  4U
#define GPIOD_ADC5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_OSC_OUT               0U
#define GPIOF_OSC_IN                1U
#define GPIOF_I2C0_SDA              2U
#define GPIOF_I2C0_SCL              3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_USB_DM                 PAL_LINE(GPIOA, 11U)
#define LINE_USB_DP                 PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)

// #define LINE_SPI2_SCK               PAL_LINE(GPIOB, 13U)
// #define LINE_SPI2_MISO              PAL_LINE(GPIOB, 14U)
// #define LINE_SPI2_MOSI              PAL_LINE(GPIOB, 15U)

#define LINE_OSC_IN                 PAL_LINE(GPIOF, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOF, 1U)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the NUC123 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)             (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)            (1U << ((n) * 2U))
#define PIN_MODE_OPENDRAIN(n)         (2U << ((n) * 2U))
#define PIN_MODE_QUASI(n)             (3U << ((n) * 2U))
#define PIN_DIGITAL_EN(n)             (0U << (n))
#define PIN_DIGITAL_DIS(n)            (1U << (n))
#define PIN_DMASK_DIS(n)              (0U << (n))
#define PIN_DMASK_EN(n)               (1U << (n))
#define PIN_DBNCE_DIS(n)              (0U << (n))
#define PIN_DBNCE_EN(n)               (1U << (n))
#define PIN_IMD_EDGE(n)               (0U << (n))
#define PIN_IMD_LVL(n)                (1U << (n))
#define PIN_IEN_FELL_DIS(n)           (0U << (n))
#define PIN_IEN_FELL_EN(n)            (1U << (n))
#define PIN_IEN_REHL_DIS(n)           ((0U << (n)) << 16)
#define PIN_IEN_REHL_EN(n)            ((1U << (n)) << 16)
#define PIN_ISRC_EN(n)                (1U << (n))
#define PIN_ISRC_DIS(n)               (0U << (n))
#define PIN_ISRC_CLR(n)               (1U << (n))
#define PIN_DATA_LOW(n)               (0U << (n))
#define PIN_DATA_HIGH(n)              (1U << (n))

/*
 * GPIOA setup:
 *
 * PA0  - PIN0                      (input pullup).
 * PA1  - PIN1                      (input pullup).
 * PA2  - PIN2                      (input pullup).
 * PA3  - PIN3                      (input pullup).
 * PA4  - PIN4                      (input pullup).
 * PA5  - PIN5                      (input pullup).
 * PA6  - PIN6                      (input pullup).
 * PA7  - PIN7                      (input pullup).
 * PA8  - PIN8                      (input pullup).
 * PA9  - PIN9                      (input pullup).
 * PA10 - SPI1_MISO0                (input pullup).
 * PA11 - SPI1_CLK                  (input floating).
 * PA12 - PWM0                      (input floating).
 * PA13 - PWM1                      (input pullup).
 * PA14 - PWM2                      (input pullup).
 * PA15 - PWM3                      (input pullup).
 */

#define VAL_GPIOA_PMD               (PIN_MODE_INPUT(GPIOA_PIN0) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOA_SPI1_MISO0) |          \
                                     PIN_MODE_INPUT(GPIOA_SPI1_CLK) |         \
                                     PIN_MODE_INPUT(GPIOA_PWM0) |         \
                                     PIN_MODE_INPUT(GPIOA_PWM1) |      \
                                     PIN_MODE_INPUT(GPIOA_PWM2) |      \
                                     PIN_MODE_INPUT(GPIOA_PWM3))
#define VAL_GPIOA_OFFD              (PIN_DIGITAL_EN(GPIOA_PIN0) |     \
                                     PIN_DIGITAL_EN(GPIOA_PIN1) |       \
                                     PIN_DIGITAL_EN(GPIOA_PIN2) |       \
                                     PIN_DIGITAL_EN(GPIOA_PIN3) |       \
                                     PIN_DIGITAL_EN(GPIOA_PIN4) |       \
                                     PIN_DIGITAL_EN(GPIOA_PIN5) |       \
                                     PIN_DIGITAL_EN(GPIOA_PIN6) |       \
                                     PIN_DIGITAL_EN(GPIOA_PIN7) |       \
                                     PIN_DIGITAL_EN(GPIOA_PIN8) |       \
                                     PIN_DIGITAL_EN(GPIOA_PIN9) |       \
                                     PIN_DIGITAL_EN(GPIOA_SPI1_MISO0) |      \
                                     PIN_DIGITAL_EN(GPIOA_SPI1_CLK) |     \
                                     PIN_DIGITAL_EN(GPIOA_PWM0) |     \
                                     PIN_DIGITAL_EN(GPIOA_PWM1) |      \
                                     PIN_DIGITAL_EN(GPIOA_PWM2) |      \
                                     PIN_DIGITAL_EN(GPIOA_PWM3))
#define VAL_GPIOA_DMASK             (PIN_DMASK_EN(GPIOA_PIN0) |     \
                                     PIN_DMASK_EN(GPIOA_PIN1) |       \
                                     PIN_DMASK_EN(GPIOA_PIN2) |       \
                                     PIN_DMASK_EN(GPIOA_PIN3) |       \
                                     PIN_DMASK_EN(GPIOA_PIN4) |       \
                                     PIN_DMASK_EN(GPIOA_PIN5) |       \
                                     PIN_DMASK_EN(GPIOA_PIN6) |       \
                                     PIN_DMASK_EN(GPIOA_PIN7) |       \
                                     PIN_DMASK_EN(GPIOA_PIN8) |       \
                                     PIN_DMASK_EN(GPIOA_PIN9) |       \
                                     PIN_DMASK_EN(GPIOA_SPI1_MISO0) |      \
                                     PIN_DMASK_EN(GPIOA_SPI1_CLK) |     \
                                     PIN_DMASK_EN(GPIOA_PWM0) |     \
                                     PIN_DMASK_EN(GPIOA_PWM1) |         \
                                     PIN_DMASK_EN(GPIOA_PWM2) |         \
                                     PIN_DMASK_EN(GPIOA_PWM3))
#define VAL_GPIOA_DBEN              (PIN_DBNCE_EN(GPIOA_PIN0) |     \
                                     PIN_DBNCE_EN(GPIOA_PIN1) |         \
                                     PIN_DBNCE_EN(GPIOA_PIN2) |         \
                                     PIN_DBNCE_EN(GPIOA_PIN3) |         \
                                     PIN_DBNCE_EN(GPIOA_PIN4) |         \
                                     PIN_DBNCE_EN(GPIOA_PIN5) |         \
                                     PIN_DBNCE_EN(GPIOA_PIN6) |         \
                                     PIN_DBNCE_EN(GPIOA_PIN7) |         \
                                     PIN_DBNCE_EN(GPIOA_PIN8) |         \
                                     PIN_DBNCE_EN(GPIOA_PIN9) |         \
                                     PIN_DBNCE_EN(GPIOA_SPI1_MISO0) |        \
                                     PIN_DBNCE_EN(GPIOA_SPI1_CLK) |     \
                                     PIN_DBNCE_EN(GPIOA_PWM0) |     \
                                     PIN_DBNCE_EN(GPIOA_PWM1) |        \
                                     PIN_DBNCE_EN(GPIOA_PWM2) |      \
                                     PIN_DBNCE_EN(GPIOA_PWM3))
#define VAL_GPIOA_IMD               (PIN_IMD_EDGE(GPIOA_PIN0) |           \
                                     PIN_IMD_EDGE(GPIOA_PIN1) |             \
                                     PIN_IMD_EDGE(GPIOA_PIN2) |             \
                                     PIN_IMD_EDGE(GPIOA_PIN3) |             \
                                     PIN_IMD_EDGE(GPIOA_PIN4) |             \
                                     PIN_IMD_EDGE(GPIOA_PIN5) |             \
                                     PIN_IMD_EDGE(GPIOA_PIN6) |             \
                                     PIN_IMD_EDGE(GPIOA_PIN7) |             \
                                     PIN_IMD_EDGE(GPIOA_PIN8) |             \
                                     PIN_IMD_EDGE(GPIOA_PIN9) |             \
                                     PIN_IMD_EDGE(GPIOA_SPI1_MISO0) |            \
                                     PIN_IMD_EDGE(GPIOA_SPI1_CLK) |           \
                                     PIN_IMD_EDGE(GPIOA_PWM0) |           \
                                     PIN_IMD_EDGE(GPIOA_PWM1) |            \
                                     PIN_IMD_EDGE(GPIOA_PWM2) |            \
                                     PIN_IMD_EDGE(GPIOA_PWM3))
#define VAL_GPIOA_IEN               (PIN_IEN_FELL_DIS(GPIOA_PIN0) |        \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN1) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN2) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN3) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN4) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN5) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN6) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN7) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN8) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_PIN9) |          \
                                     PIN_IEN_FELL_DIS(GPIOA_SPI1_MISO0) |         \
                                     PIN_IEN_FELL_DIS(GPIOA_SPI1_CLK) |        \
                                     PIN_IEN_FELL_DIS(GPIOA_PWM0) |        \
                                     PIN_IEN_FELL_DIS(GPIOA_PWM1) |         \
                                     PIN_IEN_FELL_DIS(GPIOA_PWM2) |         \
                                     PIN_IEN_FELL_DIS(GPIOA_PWM3))
#define VAL_GPIOA_ISRC              (PIN_ISRC_DIS(GPIOA_PIN0) |        \
                                     PIN_ISRC_DIS(GPIOA_PIN1) |          \
                                     PIN_ISRC_DIS(GPIOA_PIN2) |          \
                                     PIN_ISRC_DIS(GPIOA_PIN3) |          \
                                     PIN_ISRC_DIS(GPIOA_PIN4) |          \
                                     PIN_ISRC_DIS(GPIOA_PIN5) |          \
                                     PIN_ISRC_DIS(GPIOA_PIN6) |          \
                                     PIN_ISRC_DIS(GPIOA_PIN7) |          \
                                     PIN_ISRC_DIS(GPIOA_PIN8) |          \
                                     PIN_ISRC_DIS(GPIOA_PIN9) |          \
                                     PIN_ISRC_DIS(GPIOA_SPI1_MISO0) |         \
                                     PIN_ISRC_DIS(GPIOA_SPI1_CLK) |        \
                                     PIN_ISRC_DIS(GPIOA_PWM0) |        \
                                     PIN_ISRC_DIS(GPIOA_PWM1) |         \
                                     PIN_ISRC_DIS(GPIOA_PWM2) |         \
                                     PIN_ISRC_DIS(GPIOA_PWM3))
#define VAL_GPIOA_DOUT              (PIN_DATA_LOW(GPIOA_PIN0) |        \
                                     PIN_DATA_LOW(GPIOA_PIN1) |          \
                                     PIN_DATA_LOW(GPIOA_PIN2) |          \
                                     PIN_DATA_LOW(GPIOA_PIN3) |          \
                                     PIN_DATA_LOW(GPIOA_PIN4) |          \
                                     PIN_DATA_LOW(GPIOA_PIN5) |          \
                                     PIN_DATA_LOW(GPIOA_PIN6) |          \
                                     PIN_DATA_LOW(GPIOA_PIN7) |          \
                                     PIN_DATA_LOW(GPIOA_PIN8) |          \
                                     PIN_DATA_LOW(GPIOA_PIN9) |          \
                                     PIN_DATA_LOW(GPIOA_SPI1_MISO0) |         \
                                     PIN_DATA_LOW(GPIOA_SPI1_CLK) |        \
                                     PIN_DATA_LOW(GPIOA_PWM0) |        \
                                     PIN_DATA_LOW(GPIOA_PWM1) |         \
                                     PIN_DATA_LOW(GPIOA_PWM2) |         \
                                     PIN_DATA_LOW(GPIOA_PWM3))

/*
 * GPIOB setup:
 *
 * PB0  - UART0_RXD                 (input pullup).
 * PB1  - UART0_TXD                 (output).
 * PB2  - UART0_RTS                 (output).
 * PB3  - UART0_CTS                 (output).
 * PB4  - UART1_RXD                 (output).
 * PB5  - UART1_TXD                 (output).
 * PB6  - UART1_RTS                 (output).
 * PB7  - UART1_CTS                 (output).
 * PB8  - TM0                       (input pullup).
 * PB9  - TM1                       (input pullup).
 * PB10 - TM2                       (input pullup).
 * PB11 - PIN11                     (input pullup).
 * PB12 - CLK0                      (output).
 * PB13 - PIN13                     (output).
 * PB14 - INT0                      (debug output).
 * PB15 - INT1                      (input pullup).
 */
#define VAL_GPIOB_PMD               (PIN_MODE_INPUT(GPIOB_UART0_RXD) |           \
                                     PIN_MODE_OUTPUT(GPIOB_UART0_TXD) |           \
                                     PIN_MODE_OUTPUT(GPIOB_UART0_RTS) |           \
                                     PIN_MODE_OUTPUT(GPIOB_UART0_CTS) |           \
                                     PIN_MODE_OUTPUT(GPIOB_UART1_RXD) |           \
                                     PIN_MODE_OUTPUT(GPIOB_UART1_TXD) |           \
                                     PIN_MODE_OUTPUT(GPIOB_UART1_RTS) |           \
                                     PIN_MODE_OUTPUT(GPIOB_UART1_CTS) |           \
                                     PIN_MODE_INPUT(GPIOB_TM0) |           \
                                     PIN_MODE_INPUT(GPIOB_TM1) |           \
                                     PIN_MODE_INPUT(GPIOB_TM2) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN11) |          \
                                     PIN_MODE_OUTPUT(GPIOB_CLK0) |          \
                                     PIN_MODE_OUTPUT(GPIOB_PIN13) |   \
                                     PIN_MODE_OUTPUT(GPIOB_INT0) |  \
                                     PIN_MODE_INPUT(GPIOB_INT1))
#define VAL_GPIOB_OFFD              (PIN_DIGITAL_EN(GPIOB_UART0_RXD) |       \
                                     PIN_DIGITAL_DIS(GPIOB_UART0_TXD) |       \
                                     PIN_DIGITAL_DIS(GPIOB_UART0_RTS) |       \
                                     PIN_DIGITAL_DIS(GPIOB_UART0_CTS) |       \
                                     PIN_DIGITAL_DIS(GPIOB_UART1_RXD) |       \
                                     PIN_DIGITAL_DIS(GPIOB_UART1_TXD) |       \
                                     PIN_DIGITAL_DIS(GPIOB_UART1_RTS) |       \
                                     PIN_DIGITAL_DIS(GPIOB_UART1_CTS) |       \
                                     PIN_DIGITAL_DIS(GPIOB_TM0) |       \
                                     PIN_DIGITAL_EN(GPIOB_TM1) |       \
                                     PIN_DIGITAL_EN(GPIOB_TM2) |      \
                                     PIN_DIGITAL_EN(GPIOB_PIN11) |      \
                                     PIN_DIGITAL_DIS(GPIOB_CLK0) |      \
                                     PIN_DIGITAL_DIS(GPIOB_PIN13) |   \
                                     PIN_DIGITAL_DIS(GPIOB_INT0) |  \
                                     PIN_DIGITAL_EN(GPIOB_INT1))
#define VAL_GPIOB_DMASK             (PIN_DMASK_EN(GPIOB_UART0_RXD) |       \
                                     PIN_DMASK_DIS(GPIOB_UART0_TXD) |       \
                                     PIN_DMASK_DIS(GPIOB_UART0_RTS) |          \
                                     PIN_DMASK_DIS(GPIOB_UART0_CTS) |          \
                                     PIN_DMASK_DIS(GPIOB_UART1_RXD) |          \
                                     PIN_DMASK_DIS(GPIOB_UART1_TXD) |       \
                                     PIN_DMASK_DIS(GPIOB_UART1_RTS) |       \
                                     PIN_DMASK_DIS(GPIOB_UART1_CTS) |       \
                                     PIN_DMASK_EN(GPIOB_TM0) |       \
                                     PIN_DMASK_EN(GPIOB_TM1) |       \
                                     PIN_DMASK_EN(GPIOB_TM2) |      \
                                     PIN_DMASK_EN(GPIOB_PIN11) |      \
                                     PIN_DMASK_DIS(GPIOB_CLK0) |      \
                                     PIN_DMASK_DIS(GPIOB_PIN13) |   \
                                     PIN_DMASK_DIS(GPIOB_INT0) |  \
                                     PIN_DMASK_EN(GPIOB_INT1))
#define VAL_GPIOB_DBEN              (PIN_DBNCE_EN(GPIOB_UART0_RXD) |         \
                                     PIN_DBNCE_DIS(GPIOB_UART0_TXD) |         \
                                     PIN_DBNCE_DIS(GPIOB_UART0_RTS) |         \
                                     PIN_DBNCE_DIS(GPIOB_UART0_CTS) |         \
                                     PIN_DBNCE_DIS(GPIOB_UART1_RXD) |         \
                                     PIN_DBNCE_DIS(GPIOB_UART1_TXD) |         \
                                     PIN_DBNCE_DIS(GPIOB_UART1_RTS) |         \
                                     PIN_DBNCE_DIS(GPIOB_UART1_CTS) |         \
                                     PIN_DBNCE_EN(GPIOB_TM0) |         \
                                     PIN_DBNCE_EN(GPIOB_TM1) |         \
                                     PIN_DBNCE_EN(GPIOB_TM2) |        \
                                     PIN_DBNCE_EN(GPIOB_PIN11) |        \
                                     PIN_DBNCE_DIS(GPIOB_CLK0) |        \
                                     PIN_DBNCE_DIS(GPIOB_PIN13) |   \
                                     PIN_DBNCE_DIS(GPIOB_INT0) |  \
                                     PIN_DBNCE_EN(GPIOB_INT1))
#define VAL_GPIOB_IMD               (PIN_IMD_EDGE(GPIOB_UART0_RXD) |             \
                                     PIN_IMD_EDGE(GPIOB_UART0_TXD) |             \
                                     PIN_IMD_EDGE(GPIOB_UART0_RTS) |             \
                                     PIN_IMD_EDGE(GPIOB_UART0_CTS) |             \
                                     PIN_IMD_EDGE(GPIOB_UART1_RXD) |             \
                                     PIN_IMD_EDGE(GPIOB_UART1_TXD) |             \
                                     PIN_IMD_EDGE(GPIOB_UART1_RTS) |             \
                                     PIN_IMD_EDGE(GPIOB_UART1_CTS) |             \
                                     PIN_IMD_EDGE(GPIOB_TM0) |             \
                                     PIN_IMD_EDGE(GPIOB_TM1) |             \
                                     PIN_IMD_EDGE(GPIOB_TM2) |            \
                                     PIN_IMD_EDGE(GPIOB_PIN11) |            \
                                     PIN_IMD_EDGE(GPIOB_CLK0) |            \
                                     PIN_IMD_EDGE(GPIOB_PIN13) |         \
                                     PIN_IMD_EDGE(GPIOB_INT0) |        \
                                     PIN_IMD_EDGE(GPIOB_INT1))
#define VAL_GPIOB_IEN               (PIN_IEN_FELL_DIS(GPIOB_UART0_RXD) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_UART0_TXD) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_UART0_RTS) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_UART0_CTS) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_UART1_RXD) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_UART1_TXD) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_UART1_RTS) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_UART1_CTS) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_TM0) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_TM1) |          \
                                     PIN_IEN_FELL_DIS(GPIOB_TM2) |         \
                                     PIN_IEN_FELL_DIS(GPIOB_PIN11) |         \
                                     PIN_IEN_FELL_DIS(GPIOB_CLK0) |         \
                                     PIN_IEN_FELL_DIS(GPIOB_PIN13) |      \
                                     PIN_IEN_FELL_DIS(GPIOB_INT0) |     \
                                     PIN_IEN_FELL_DIS(GPIOB_INT1))
#define VAL_GPIOB_ISRC              (PIN_ISRC_DIS(GPIOB_UART0_RXD) |          \
                                     PIN_ISRC_DIS(GPIOB_UART0_TXD) |          \
                                     PIN_ISRC_DIS(GPIOB_UART0_RTS) |          \
                                     PIN_ISRC_DIS(GPIOB_UART0_CTS) |          \
                                     PIN_ISRC_DIS(GPIOB_UART1_RXD) |          \
                                     PIN_ISRC_DIS(GPIOB_UART1_TXD) |          \
                                     PIN_ISRC_DIS(GPIOB_UART1_RTS) |          \
                                     PIN_ISRC_DIS(GPIOB_UART1_CTS) |          \
                                     PIN_ISRC_DIS(GPIOB_TM0) |          \
                                     PIN_ISRC_DIS(GPIOB_TM1) |          \
                                     PIN_ISRC_DIS(GPIOB_TM2) |         \
                                     PIN_ISRC_DIS(GPIOB_PIN11) |         \
                                     PIN_ISRC_DIS(GPIOB_CLK0) |         \
                                     PIN_ISRC_DIS(GPIOB_PIN13) |      \
                                     PIN_ISRC_DIS(GPIOB_INT0) |     \
                                     PIN_ISRC_DIS(GPIOB_INT1))
#define VAL_GPIOB_DOUT              (PIN_DATA_LOW(GPIOB_UART0_RXD) |          \
                                     PIN_DATA_LOW(GPIOB_UART0_TXD) |          \
                                     PIN_DATA_LOW(GPIOB_UART0_RTS) |          \
                                     PIN_DATA_LOW(GPIOB_UART0_CTS) |          \
                                     PIN_DATA_LOW(GPIOB_UART1_RXD) |          \
                                     PIN_DATA_LOW(GPIOB_UART1_TXD) |          \
                                     PIN_DATA_LOW(GPIOB_UART1_RTS) |          \
                                     PIN_DATA_LOW(GPIOB_UART1_CTS) |          \
                                     PIN_DATA_LOW(GPIOB_TM0) |          \
                                     PIN_DATA_LOW(GPIOB_TM1) |          \
                                     PIN_DATA_LOW(GPIOB_TM2) |         \
                                     PIN_DATA_LOW(GPIOB_PIN11) |         \
                                     PIN_DATA_LOW(GPIOB_CLK0) |         \
                                     PIN_DATA_LOW(GPIOB_PIN13) |      \
                                     PIN_DATA_LOW(GPIOB_INT0) |     \
                                     PIN_DATA_LOW(GPIOB_INT1))

/*
 * GPIOC setup:
 *
 * PC0  - PIN0                      (input pullup).
 * PC1  - PIN1                      (input pullup).
 * PC2  - PIN2                      (input pullup).
 * PC3  - PIN3                      (input pullup).
 * PC4  - PIN4                      (output).
 * PC5  - PIN5                      (output).
 * PC6  - PIN6                      (input pullup).
 * PC7  - PIN7                      (input pullup).
 * PC8  - PIN8                      (input pullup).
 * PC9  - PIN9                      (input pullup).
 * PC10 - PIN10                     (input pullup).
 * PC11 - PIN11                     (input pullup).
 * PC12 - PIN12                     (input pullup).
 * PC13 - PIN13                     (input pullup).
 * PC14 - PIN14                     (input pullup).
 * PC15 - PIN15                     (input pullup).
 */
#define VAL_GPIOC_PMD               (PIN_MODE_INPUT(GPIOC_PIN0) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |           \
                                     PIN_MODE_OUTPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_OUTPUT(GPIOC_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |      \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |    \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |     \
                                     PIN_MODE_INPUT(GPIOC_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#define VAL_GPIOC_OFFD              (PIN_DIGITAL_EN(GPIOC_PIN0) |    \
                                     PIN_DIGITAL_EN(GPIOC_PIN1) |       \
                                     PIN_DIGITAL_EN(GPIOC_PIN2) |       \
                                     PIN_DIGITAL_EN(GPIOC_PIN3) |       \
                                     PIN_DIGITAL_DIS(GPIOC_PIN4) |       \
                                     PIN_DIGITAL_DIS(GPIOC_PIN5) |       \
                                     PIN_DIGITAL_EN(GPIOC_PIN6) |    \
                                     PIN_DIGITAL_EN(GPIOC_PIN7) |   \
                                     PIN_DIGITAL_EN(GPIOC_PIN8) | \
                                     PIN_DIGITAL_EN(GPIOC_PIN9) |  \
                                     PIN_DIGITAL_EN(GPIOC_PIN10) |      \
                                     PIN_DIGITAL_EN(GPIOC_PIN11) |      \
                                     PIN_DIGITAL_EN(GPIOC_PIN12) |      \
                                     PIN_DIGITAL_EN(GPIOC_PIN13) |      \
                                     PIN_DIGITAL_EN(GPIOC_PIN14) |   \
                                     PIN_DIGITAL_EN(GPIOC_PIN15))
#define VAL_GPIOC_DMASK             (PIN_DMASK_EN(GPIOC_PIN0) |       \
                                     PIN_DMASK_EN(GPIOC_PIN1) |       \
                                     PIN_DMASK_EN(GPIOC_PIN2) |       \
                                     PIN_DMASK_EN(GPIOC_PIN3) |       \
                                     PIN_DMASK_DIS(GPIOC_PIN4) |       \
                                     PIN_DMASK_DIS(GPIOC_PIN5) |       \
                                     PIN_DMASK_EN(GPIOC_PIN6) |       \
                                     PIN_DMASK_EN(GPIOC_PIN7) |      \
                                     PIN_DMASK_EN(GPIOC_PIN8) |    \
                                     PIN_DMASK_EN(GPIOC_PIN9) |     \
                                     PIN_DMASK_EN(GPIOC_PIN10) |      \
                                     PIN_DMASK_EN(GPIOC_PIN11) |      \
                                     PIN_DMASK_EN(GPIOC_PIN12) |      \
                                     PIN_DMASK_EN(GPIOC_PIN13) |      \
                                     PIN_DMASK_EN(GPIOC_PIN14) |      \
                                     PIN_DMASK_EN(GPIOC_PIN15))
#define VAL_GPIOC_DBEN              (PIN_DBNCE_EN(GPIOC_PIN0) |    \
                                     PIN_DBNCE_EN(GPIOC_PIN1) |         \
                                     PIN_DBNCE_EN(GPIOC_PIN2) |         \
                                     PIN_DBNCE_EN(GPIOC_PIN3) |         \
                                     PIN_DBNCE_DIS(GPIOC_PIN4) |         \
                                     PIN_DBNCE_DIS(GPIOC_PIN5) |         \
                                     PIN_DBNCE_EN(GPIOC_PIN6) |    \
                                     PIN_DBNCE_EN(GPIOC_PIN7) |   \
                                     PIN_DBNCE_EN(GPIOC_PIN8) | \
                                     PIN_DBNCE_EN(GPIOC_PIN9) |  \
                                     PIN_DBNCE_EN(GPIOC_PIN10) |        \
                                     PIN_DBNCE_EN(GPIOC_PIN11) |        \
                                     PIN_DBNCE_EN(GPIOC_PIN12) |        \
                                     PIN_DBNCE_EN(GPIOC_PIN13) |        \
                                     PIN_DBNCE_EN(GPIOC_PIN14) |   \
                                     PIN_DBNCE_EN(GPIOC_PIN15))
#define VAL_GPIOC_IMD               (PIN_IMD_EDGE(GPIOC_PIN0) |          \
                                     PIN_IMD_EDGE(GPIOC_PIN1) |             \
                                     PIN_IMD_EDGE(GPIOC_PIN2) |             \
                                     PIN_IMD_EDGE(GPIOC_PIN3) |             \
                                     PIN_IMD_EDGE(GPIOC_PIN4) |             \
                                     PIN_IMD_EDGE(GPIOC_PIN5) |             \
                                     PIN_IMD_EDGE(GPIOC_PIN6) |           \
                                     PIN_IMD_EDGE(GPIOC_PIN7) |          \
                                     PIN_IMD_EDGE(GPIOC_PIN8) |        \
                                     PIN_IMD_EDGE(GPIOC_PIN9) |         \
                                     PIN_IMD_EDGE(GPIOC_PIN10) |            \
                                     PIN_IMD_EDGE(GPIOC_PIN11) |            \
                                     PIN_IMD_EDGE(GPIOC_PIN12) |            \
                                     PIN_IMD_EDGE(GPIOC_PIN13) |            \
                                     PIN_IMD_EDGE(GPIOC_PIN14) |         \
                                     PIN_IMD_EDGE(GPIOC_PIN15))
#define VAL_GPIOC_IEN               (PIN_IEN_FELL_DIS(GPIOC_PIN0) |       \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN1) |          \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN2) |          \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN3) |          \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN4) |          \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN5) |          \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN6) |       \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN7) |       \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN8) |    \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN9) |     \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN10) |         \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN11) |         \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN12) |         \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN13) |         \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN14) |      \
                                     PIN_IEN_FELL_DIS(GPIOC_PIN15))
#define VAL_GPIOC_ISRC              (PIN_ISRC_DIS(GPIOC_PIN0) |       \
                                     PIN_ISRC_DIS(GPIOC_PIN1) |          \
                                     PIN_ISRC_DIS(GPIOC_PIN2) |          \
                                     PIN_ISRC_DIS(GPIOC_PIN3) |          \
                                     PIN_ISRC_DIS(GPIOC_PIN4) |          \
                                     PIN_ISRC_DIS(GPIOC_PIN5) |          \
                                     PIN_ISRC_DIS(GPIOC_PIN6) |       \
                                     PIN_ISRC_DIS(GPIOC_PIN7) |       \
                                     PIN_ISRC_DIS(GPIOC_PIN8) |    \
                                     PIN_ISRC_DIS(GPIOC_PIN9) |     \
                                     PIN_ISRC_DIS(GPIOC_PIN10) |         \
                                     PIN_ISRC_DIS(GPIOC_PIN11) |         \
                                     PIN_ISRC_DIS(GPIOC_PIN12) |         \
                                     PIN_ISRC_DIS(GPIOC_PIN13) |         \
                                     PIN_ISRC_DIS(GPIOC_PIN14) |      \
                                     PIN_ISRC_DIS(GPIOC_PIN15))
#define VAL_GPIOC_DOUT              (PIN_DATA_LOW(GPIOC_PIN0) |       \
                                     PIN_DATA_LOW(GPIOC_PIN1) |          \
                                     PIN_DATA_LOW(GPIOC_PIN2) |          \
                                     PIN_DATA_LOW(GPIOC_PIN3) |          \
                                     PIN_DATA_LOW(GPIOC_PIN4) |          \
                                     PIN_DATA_LOW(GPIOC_PIN5) |          \
                                     PIN_DATA_LOW(GPIOC_PIN6) |       \
                                     PIN_DATA_LOW(GPIOC_PIN7) |       \
                                     PIN_DATA_LOW(GPIOC_PIN8) |    \
                                     PIN_DATA_LOW(GPIOC_PIN9) |     \
                                     PIN_DATA_LOW(GPIOC_PIN10) |         \
                                     PIN_DATA_LOW(GPIOC_PIN11) |         \
                                     PIN_DATA_LOW(GPIOC_PIN12) |         \
                                     PIN_DATA_LOW(GPIOC_PIN13) |         \
                                     PIN_DATA_LOW(GPIOC_PIN14) |      \
                                     PIN_DATA_LOW(GPIOC_PIN15))

/*
 * GPIOD setup:
 *
 * PD0  - ADC0                      (input pullup).
 * PD1  - ADC1                      (input pullup).
 * PD2  - ADC2                      (input pullup).
 * PD3  - ADC3                      (output).
 * PD4  - ADC4                      (output).
 * PD5  - ADC5                      (output).
 * PD6  - PIN6                      (input pullup).
 * PD7  - PIN7                      (input pullup).
 * PD8  - PIN8                      (input pullup).
 * PD9  - PIN9                      (output).
 * PD10 - PIN10                     (debug output).
 * PD11 - PIN11                     (output).
 * PD12 - PIN12                     (input pullup).
 * PD13 - PIN13                     (input pullup).
 * PD14 - PIN14                     (input pullup).
 * PD15 - PIN15                     (input pullup).
 */
#define VAL_GPIOD_PMD               (PIN_MODE_INPUT(GPIOD_ADC0) |           \
                                     PIN_MODE_INPUT(GPIOD_ADC1) |           \
                                     PIN_MODE_INPUT(GPIOD_ADC2) |           \
                                     PIN_MODE_OUTPUT(GPIOD_ADC3) |           \
                                     PIN_MODE_OUTPUT(GPIOD_ADC4) |           \
                                     PIN_MODE_OUTPUT(GPIOD_ADC5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_OUTPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_OUTPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_OUTPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OFFD              (PIN_DIGITAL_EN(GPIOD_ADC0) |       \
                                     PIN_DIGITAL_EN(GPIOD_ADC1) |       \
                                     PIN_DIGITAL_EN(GPIOD_ADC2) |       \
                                     PIN_DIGITAL_DIS(GPIOD_ADC3) |       \
                                     PIN_DIGITAL_DIS(GPIOD_ADC4) |       \
                                     PIN_DIGITAL_DIS(GPIOD_ADC5) |       \
                                     PIN_DIGITAL_EN(GPIOD_PIN6) |       \
                                     PIN_DIGITAL_EN(GPIOD_PIN7) |       \
                                     PIN_DIGITAL_EN(GPIOD_PIN8) |       \
                                     PIN_DIGITAL_DIS(GPIOD_PIN9) |       \
                                     PIN_DIGITAL_DIS(GPIOD_PIN10) |      \
                                     PIN_DIGITAL_DIS(GPIOD_PIN11) |      \
                                     PIN_DIGITAL_EN(GPIOD_PIN12) |      \
                                     PIN_DIGITAL_EN(GPIOD_PIN13) |      \
                                     PIN_DIGITAL_EN(GPIOD_PIN14) |      \
                                     PIN_DIGITAL_EN(GPIOD_PIN15))
#define VAL_GPIOD_DMASK             (PIN_DMASK_EN(GPIOD_ADC0) |       \
                                     PIN_DMASK_EN(GPIOD_ADC1) |       \
                                     PIN_DMASK_EN(GPIOD_ADC2) |       \
                                     PIN_DMASK_DIS(GPIOD_ADC3) |       \
                                     PIN_DMASK_DIS(GPIOD_ADC4) |       \
                                     PIN_DMASK_DIS(GPIOD_ADC5) |       \
                                     PIN_DMASK_EN(GPIOD_PIN6) |       \
                                     PIN_DMASK_EN(GPIOD_PIN7) |       \
                                     PIN_DMASK_EN(GPIOD_PIN8) |       \
                                     PIN_DMASK_DIS(GPIOD_PIN9) |       \
                                     PIN_DMASK_DIS(GPIOD_PIN10) |      \
                                     PIN_DMASK_DIS(GPIOD_PIN11) |      \
                                     PIN_DMASK_EN(GPIOD_PIN12) |      \
                                     PIN_DMASK_EN(GPIOD_PIN13) |      \
                                     PIN_DMASK_EN(GPIOD_PIN14) |      \
                                     PIN_DMASK_EN(GPIOD_PIN15))
#define VAL_GPIOD_DBEN              (PIN_DBNCE_EN(GPIOD_ADC0) |         \
                                     PIN_DBNCE_EN(GPIOD_ADC1) |         \
                                     PIN_DBNCE_EN(GPIOD_ADC2) |         \
                                     PIN_DBNCE_DIS(GPIOD_ADC3) |         \
                                     PIN_DBNCE_DIS(GPIOD_ADC4) |         \
                                     PIN_DBNCE_DIS(GPIOD_ADC5) |         \
                                     PIN_DBNCE_EN(GPIOD_PIN6) |         \
                                     PIN_DBNCE_EN(GPIOD_PIN7) |         \
                                     PIN_DBNCE_EN(GPIOD_PIN8) |         \
                                     PIN_DBNCE_DIS(GPIOD_PIN9) |         \
                                     PIN_DBNCE_DIS(GPIOD_PIN10) |        \
                                     PIN_DBNCE_DIS(GPIOD_PIN11) |        \
                                     PIN_DBNCE_EN(GPIOD_PIN12) |        \
                                     PIN_DBNCE_EN(GPIOD_PIN13) |        \
                                     PIN_DBNCE_EN(GPIOD_PIN14) |        \
                                     PIN_DBNCE_EN(GPIOD_PIN15))
#define VAL_GPIOD_IMD               (PIN_IMD_EDGE(GPIOD_ADC0) |             \
                                     PIN_IMD_EDGE(GPIOD_ADC1) |             \
                                     PIN_IMD_EDGE(GPIOD_ADC2) |             \
                                     PIN_IMD_EDGE(GPIOD_ADC3) |             \
                                     PIN_IMD_EDGE(GPIOD_ADC4) |             \
                                     PIN_IMD_EDGE(GPIOD_ADC5) |             \
                                     PIN_IMD_EDGE(GPIOD_PIN6) |             \
                                     PIN_IMD_EDGE(GPIOD_PIN7) |             \
                                     PIN_IMD_EDGE(GPIOD_PIN8) |             \
                                     PIN_IMD_EDGE(GPIOD_PIN9) |             \
                                     PIN_IMD_EDGE(GPIOD_PIN10) |            \
                                     PIN_IMD_EDGE(GPIOD_PIN11) |            \
                                     PIN_IMD_EDGE(GPIOD_PIN12) |            \
                                     PIN_IMD_EDGE(GPIOD_PIN13) |            \
                                     PIN_IMD_EDGE(GPIOD_PIN14) |            \
                                     PIN_IMD_EDGE(GPIOD_PIN15))
#define VAL_GPIOD_IEN               (PIN_IEN_FELL_DIS(GPIOD_ADC0) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_ADC1) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_ADC2) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_ADC3) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_ADC4) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_ADC5) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN6) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN7) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN8) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN9) |          \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN10) |         \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN11) |         \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN12) |         \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN13) |         \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN14) |         \
                                     PIN_IEN_FELL_DIS(GPIOD_PIN15))
#define VAL_GPIOD_ISRC              (PIN_ISRC_DIS(GPIOD_ADC0) |          \
                                     PIN_ISRC_DIS(GPIOD_ADC1) |          \
                                     PIN_ISRC_DIS(GPIOD_ADC2) |          \
                                     PIN_ISRC_DIS(GPIOD_ADC3) |          \
                                     PIN_ISRC_DIS(GPIOD_ADC4) |          \
                                     PIN_ISRC_DIS(GPIOD_ADC5) |          \
                                     PIN_ISRC_DIS(GPIOD_PIN6) |          \
                                     PIN_ISRC_DIS(GPIOD_PIN7) |          \
                                     PIN_ISRC_DIS(GPIOD_PIN8) |          \
                                     PIN_ISRC_DIS(GPIOD_PIN9) |          \
                                     PIN_ISRC_DIS(GPIOD_PIN10) |         \
                                     PIN_ISRC_DIS(GPIOD_PIN11) |         \
                                     PIN_ISRC_DIS(GPIOD_PIN12) |         \
                                     PIN_ISRC_DIS(GPIOD_PIN13) |         \
                                     PIN_ISRC_DIS(GPIOD_PIN14) |         \
                                     PIN_ISRC_DIS(GPIOD_PIN15))
#define VAL_GPIOD_DOUT              (PIN_DATA_LOW(GPIOD_ADC0) |          \
                                     PIN_DATA_LOW(GPIOD_ADC1) |          \
                                     PIN_DATA_LOW(GPIOD_ADC2) |          \
                                     PIN_DATA_LOW(GPIOD_ADC3) |          \
                                     PIN_DATA_LOW(GPIOD_ADC4) |          \
                                     PIN_DATA_LOW(GPIOD_ADC5) |          \
                                     PIN_DATA_LOW(GPIOD_PIN6) |          \
                                     PIN_DATA_LOW(GPIOD_PIN7) |          \
                                     PIN_DATA_LOW(GPIOD_PIN8) |          \
                                     PIN_DATA_LOW(GPIOD_PIN9) |          \
                                     PIN_DATA_LOW(GPIOD_PIN10) |         \
                                     PIN_DATA_LOW(GPIOD_PIN11) |         \
                                     PIN_DATA_LOW(GPIOD_PIN12) |         \
                                     PIN_DATA_LOW(GPIOD_PIN13) |         \
                                     PIN_DATA_LOW(GPIOD_PIN14) |         \
                                     PIN_DATA_LOW(GPIOD_PIN15))

/*
 * GPIOF setup:
 *
 * PF0  - OSC_IN                    (input floating).
 * PF1  - OSC_OUT                   (input floating).
 * PF2  - I2C0_SDA                  (input pullup).
 * PF3  - I2C0_SCL                  (input pullup).
 * PF4  - PIN4                      (input pullup).
 * PF5  - PIN5                      (input pullup).
 * PF6  - PIN6                      (input pullup).
 * PF7  - PIN7                      (input pullup).
 * PF8  - PIN8                      (input pullup).
 * PF9  - PIN9                      (input pullup).
 * PF10 - PIN10                     (input pullup).
 * PF11 - PIN11                     (input pullup).
 * PF12 - PIN12                     (input pullup).
 * PF13 - PIN13                     (input pullup).
 * PF14 - PIN14                     (input pullup).
 * PF15 - PIN15                     (input pullup).
 */
#define VAL_GPIOF_PMD               (PIN_MODE_QUASI(GPIOF_OSC_IN) |        \
                                     PIN_MODE_QUASI(GPIOF_OSC_OUT) |         \
                                     PIN_MODE_INPUT(GPIOF_I2C0_SDA) |           \
                                     PIN_MODE_INPUT(GPIOF_I2C0_SCL) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OFFD              (PIN_DIGITAL_DIS(GPIOF_OSC_IN) |    \
                                     PIN_DIGITAL_DIS(GPIOF_OSC_OUT) |     \
                                     PIN_DIGITAL_EN(GPIOF_I2C0_SDA) |       \
                                     PIN_DIGITAL_EN(GPIOF_I2C0_SCL) |       \
                                     PIN_DIGITAL_EN(GPIOF_PIN4) |       \
                                     PIN_DIGITAL_EN(GPIOF_PIN5) |       \
                                     PIN_DIGITAL_EN(GPIOF_PIN6) |       \
                                     PIN_DIGITAL_EN(GPIOF_PIN7) |       \
                                     PIN_DIGITAL_EN(GPIOF_PIN8) |       \
                                     PIN_DIGITAL_EN(GPIOF_PIN9) |       \
                                     PIN_DIGITAL_EN(GPIOF_PIN10) |      \
                                     PIN_DIGITAL_EN(GPIOF_PIN11) |      \
                                     PIN_DIGITAL_EN(GPIOF_PIN12) |      \
                                     PIN_DIGITAL_EN(GPIOF_PIN13) |      \
                                     PIN_DIGITAL_EN(GPIOF_PIN14) |      \
                                     PIN_DIGITAL_EN(GPIOF_PIN15))
#define VAL_GPIOF_DMASK             (PIN_DMASK_DIS(GPIOF_OSC_IN) |    \
                                     PIN_DMASK_DIS(GPIOF_OSC_OUT) |     \
                                     PIN_DMASK_EN(GPIOF_I2C0_SDA) |       \
                                     PIN_DMASK_EN(GPIOF_I2C0_SCL) |       \
                                     PIN_DMASK_EN(GPIOF_PIN4) |       \
                                     PIN_DMASK_EN(GPIOF_PIN5) |       \
                                     PIN_DMASK_EN(GPIOF_PIN6) |       \
                                     PIN_DMASK_EN(GPIOF_PIN7) |       \
                                     PIN_DMASK_EN(GPIOF_PIN8) |       \
                                     PIN_DMASK_EN(GPIOF_PIN9) |       \
                                     PIN_DMASK_EN(GPIOF_PIN10) |      \
                                     PIN_DMASK_EN(GPIOF_PIN11) |      \
                                     PIN_DMASK_EN(GPIOF_PIN12) |      \
                                     PIN_DMASK_EN(GPIOF_PIN13) |      \
                                     PIN_DMASK_EN(GPIOF_PIN14) |      \
                                     PIN_DMASK_EN(GPIOF_PIN15))
#define VAL_GPIOF_DBEN              (PIN_DBNCE_DIS(GPIOF_OSC_IN) |    \
                                     PIN_DBNCE_DIS(GPIOF_OSC_OUT) |     \
                                     PIN_DBNCE_EN(GPIOF_I2C0_SDA) |         \
                                     PIN_DBNCE_EN(GPIOF_I2C0_SCL) |         \
                                     PIN_DBNCE_EN(GPIOF_PIN4) |         \
                                     PIN_DBNCE_EN(GPIOF_PIN5) |         \
                                     PIN_DBNCE_EN(GPIOF_PIN6) |         \
                                     PIN_DBNCE_EN(GPIOF_PIN7) |         \
                                     PIN_DBNCE_EN(GPIOF_PIN8) |         \
                                     PIN_DBNCE_EN(GPIOF_PIN9) |         \
                                     PIN_DBNCE_EN(GPIOF_PIN10) |        \
                                     PIN_DBNCE_EN(GPIOF_PIN11) |        \
                                     PIN_DBNCE_EN(GPIOF_PIN12) |        \
                                     PIN_DBNCE_EN(GPIOF_PIN13) |        \
                                     PIN_DBNCE_EN(GPIOF_PIN14) |        \
                                     PIN_DBNCE_EN(GPIOF_PIN15))
#define VAL_GPIOF_IMD               (PIN_IMD_LVL(GPIOF_OSC_IN) |          \
                                     PIN_IMD_LVL(GPIOF_OSC_OUT) |           \
                                     PIN_IMD_EDGE(GPIOF_I2C0_SDA) |             \
                                     PIN_IMD_EDGE(GPIOF_I2C0_SCL) |             \
                                     PIN_IMD_EDGE(GPIOF_PIN4) |             \
                                     PIN_IMD_EDGE(GPIOF_PIN5) |             \
                                     PIN_IMD_EDGE(GPIOF_PIN6) |             \
                                     PIN_IMD_EDGE(GPIOF_PIN7) |             \
                                     PIN_IMD_EDGE(GPIOF_PIN8) |             \
                                     PIN_IMD_EDGE(GPIOF_PIN9) |             \
                                     PIN_IMD_EDGE(GPIOF_PIN10) |            \
                                     PIN_IMD_EDGE(GPIOF_PIN11) |            \
                                     PIN_IMD_EDGE(GPIOF_PIN12) |            \
                                     PIN_IMD_EDGE(GPIOF_PIN13) |            \
                                     PIN_IMD_EDGE(GPIOF_PIN14) |            \
                                     PIN_IMD_EDGE(GPIOF_PIN15))
#define VAL_GPIOF_IEN               (PIN_IEN_FELL_DIS(GPIOF_OSC_IN) |       \
                                     PIN_IEN_FELL_DIS(GPIOF_OSC_OUT) |        \
                                     PIN_IEN_FELL_DIS(GPIOF_I2C0_SDA) |          \
                                     PIN_IEN_FELL_DIS(GPIOF_I2C0_SCL) |          \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN4) |          \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN5) |          \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN6) |          \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN7) |          \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN8) |          \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN9) |          \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN10) |         \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN11) |         \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN12) |         \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN13) |         \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN14) |         \
                                     PIN_IEN_FELL_DIS(GPIOF_PIN15))
#define VAL_GPIOF_ISRC              (PIN_ISRC_DIS(GPIOF_OSC_IN) |       \
                                     PIN_ISRC_DIS(GPIOF_OSC_OUT) |        \
                                     PIN_ISRC_DIS(GPIOF_I2C0_SDA) |          \
                                     PIN_ISRC_DIS(GPIOF_I2C0_SCL) |          \
                                     PIN_ISRC_DIS(GPIOF_PIN4) |          \
                                     PIN_ISRC_DIS(GPIOF_PIN5) |          \
                                     PIN_ISRC_DIS(GPIOF_PIN6) |          \
                                     PIN_ISRC_DIS(GPIOF_PIN7) |          \
                                     PIN_ISRC_DIS(GPIOF_PIN8) |          \
                                     PIN_ISRC_DIS(GPIOF_PIN9) |          \
                                     PIN_ISRC_DIS(GPIOF_PIN10) |         \
                                     PIN_ISRC_DIS(GPIOF_PIN11) |         \
                                     PIN_ISRC_DIS(GPIOF_PIN12) |         \
                                     PIN_ISRC_DIS(GPIOF_PIN13) |         \
                                     PIN_ISRC_DIS(GPIOF_PIN14) |         \
                                     PIN_ISRC_DIS(GPIOF_PIN15))
#define VAL_GPIOF_DOUT              (PIN_DATA_LOW(GPIOF_OSC_IN) |       \
                                     PIN_DATA_LOW(GPIOF_OSC_OUT) |        \
                                     PIN_DATA_LOW(GPIOF_I2C0_SDA) |          \
                                     PIN_DATA_LOW(GPIOF_I2C0_SCL) |          \
                                     PIN_DATA_LOW(GPIOF_PIN4) |          \
                                     PIN_DATA_LOW(GPIOF_PIN5) |          \
                                     PIN_DATA_LOW(GPIOF_PIN6) |          \
                                     PIN_DATA_LOW(GPIOF_PIN7) |          \
                                     PIN_DATA_LOW(GPIOF_PIN8) |          \
                                     PIN_DATA_LOW(GPIOF_PIN9) |          \
                                     PIN_DATA_LOW(GPIOF_PIN10) |         \
                                     PIN_DATA_LOW(GPIOF_PIN11) |         \
                                     PIN_DATA_LOW(GPIOF_PIN12) |         \
                                     PIN_DATA_LOW(GPIOF_PIN13) |         \
                                     PIN_DATA_LOW(GPIOF_PIN14) |         \
                                     PIN_DATA_LOW(GPIOF_PIN15))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
