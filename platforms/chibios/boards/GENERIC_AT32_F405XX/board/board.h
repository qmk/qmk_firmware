/*
    ChibiOS - Copyright (C) 2006..2020 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2023..2025 HorrorTroll
    ChibiOS - Copyright (C) 2023..2025 Zhaqian
    ChibiOS - Copyright (C) 2024..2025 Maxjta

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

#ifndef _BOARD_H_
#define _BOARD_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for a Generic AT32F405 board.
 */

/*
 * Board identifier.
 */
#define BOARD_GENERIC_AT32_F405XX
#define BOARD_NAME                  "GENERIC AT32F405 board"

/*
 * The board has an ULPI USB PHY.
 */
#define BOARD_OTG2_USES_ULPI

/*
 * Board oscillators-related settings.
 */
#if !defined(AT32_LEXTCLK)
#define AT32_LEXTCLK                32768
#endif

#if !defined(AT32_HEXTCLK)
#define AT32_HEXTCLK                12000000
#endif

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define AT32F405KB

/*
 * GPIO settings, allow unused GPIO for smaller chip packages.
 */
#if defined(AT32F405KB) || defined(AT32F405KC)
#define AT32_HAS_GPIOC              TRUE
#define AT32_HAS_GPIOD              TRUE
#elif defined(AT32F405CB) || defined(AT32F405CC)
#define AT32_HAS_GPIOD              TRUE
#endif

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
#define GPIOA_PIN10                 10U
#define GPIOA_PIN11                 11U
#define GPIOA_PIN12                 12U
#define GPIOA_PIN13                 13U
#define GPIOA_PIN14                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_PIN0                  0U
#define GPIOB_PIN1                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_PIN3                  3U
#define GPIOB_PIN4                  4U
#define GPIOB_PIN5                  5U
#define GPIOB_PIN6                  6U
#define GPIOB_PIN7                  7U
#define GPIOB_PIN8                  8U
#define GPIOB_PIN9                  9U
#define GPIOB_PIN10                 10U
#define GPIOB_PIN12                 12U
#define GPIOB_PIN13                 13U

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

#define GPIOD_PIN2                  2U

#define GPIOF_HEXT_IN               0U
#define GPIOF_HEXT_OUT              1U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN11                 11U

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the AT32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_MUX(n)             (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODT_LOW(n)              (0U << (n))
#define PIN_ODT_HIGH(n)             (1U << (n))
#define PIN_OMODE_PUSHPULL(n)       (0U << (n))
#define PIN_OMODE_OPENDRAIN(n)      (1U << (n))
#define PIN_ODRVR_STRONGER(n)       (1U << ((n) * 2U))
#define PIN_ODRVR_MODERATE(n)       (3U << ((n) * 2U))
#define PIN_PULL_FLOATING(n)        (0U << ((n) * 2U))
#define PIN_PULL_PULLUP(n)          (1U << ((n) * 2U))
#define PIN_PULL_PULLDOWN(n)        (2U << ((n) * 2U))
#define PIN_IOMUX_MUX(n, v)         ((v) << (((n) % 8U) * 4U))
#define PIN_WPR_DISABLED(n)         (0U << (n))
#define PIN_WPR_ENABLED(n)          (1U << (n))
#define PIN_HDRV_DISABLED(n)        (0U << (n))
#define PIN_HDRV_ENABLED(n)         (1U << (n))

/*
 * Port A setup.
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
 * PA10 - PIN10                     (input pullup).
 * PA11 - PIN11                     (input floating).
 * PA12 - PIN12                     (input floating).
 * PA13 - PIN13                     (input pullup).
 * PA14 - PIN14                     (input pullup).
 * PA15 - PIN15                     (input pullup).
 */
#define VAL_GPIOA_CFGR              (PIN_MODE_INPUT(GPIOA_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN15))
#define VAL_GPIOA_OMODE             (PIN_OMODE_PUSHPULL(GPIOA_PIN0) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN1) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN2) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN3) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN4) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN5) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN6) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN7) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN8) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN9) |       \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN10) |      \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN11) |      \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN12) |      \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN13) |      \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN14) |      \
                                     PIN_OMODE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_ODRVR             (PIN_ODRVR_STRONGER(GPIOA_PIN0) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN1) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN2) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN3) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN4) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN5) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN6) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN7) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN8) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN9) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN10) |      \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN11) |      \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN12) |      \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN13) |      \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN14) |      \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN15))
#define VAL_GPIOA_PULL              (PIN_PULL_PULLUP(GPIOA_PIN0) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN1) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN2) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN3) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN4) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN5) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN6) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN7) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN8) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN9) |          \
                                     PIN_PULL_PULLUP(GPIOA_PIN10) |         \
                                     PIN_PULL_FLOATING(GPIOA_PIN11) |       \
                                     PIN_PULL_FLOATING(GPIOA_PIN12) |       \
                                     PIN_PULL_PULLUP(GPIOA_PIN13) |         \
                                     PIN_PULL_PULLUP(GPIOA_PIN14) |         \
                                     PIN_PULL_PULLUP(GPIOA_PIN15))
#define VAL_GPIOA_ODT               (PIN_ODT_HIGH(GPIOA_PIN0) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN1) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN2) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN3) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN4) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN5) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN6) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN7) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN8) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN9) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN10) |            \
                                     PIN_ODT_HIGH(GPIOA_PIN11) |            \
                                     PIN_ODT_HIGH(GPIOA_PIN12) |            \
                                     PIN_ODT_HIGH(GPIOA_PIN13) |            \
                                     PIN_ODT_HIGH(GPIOA_PIN14) |            \
                                     PIN_ODT_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_MUXL              (PIN_IOMUX_MUX(GPIOA_PIN0, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN1, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN2, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN3, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN4, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN5, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN6, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN7, 0U))
#define VAL_GPIOA_MUXH              (PIN_IOMUX_MUX(GPIOA_PIN8, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN9, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOA_PIN10, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOA_PIN11, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOA_PIN12, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOA_PIN13, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOA_PIN14, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOA_PIN15, 0U))
#define VAL_GPIOA_HDRV              (PIN_HDRV_DISABLED(GPIOA_PIN0) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN1) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN2) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN3) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN4) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN5) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN6) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN7) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN8) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN9) |        \
                                     PIN_HDRV_DISABLED(GPIOA_PIN10) |       \
                                     PIN_HDRV_DISABLED(GPIOA_PIN11) |       \
                                     PIN_HDRV_DISABLED(GPIOA_PIN12) |       \
                                     PIN_HDRV_DISABLED(GPIOA_PIN13) |       \
                                     PIN_HDRV_DISABLED(GPIOA_PIN14) |       \
                                     PIN_HDRV_DISABLED(GPIOA_PIN15))

/*
 * Port B setup.
 *
 * PB0  - PIN0                      (input pullup).
 * PB1  - PIN1                      (input pullup).
 * PB2  - PIN2                      (input pullup).
 * PB3  - PIN3                      (input pullup).
 * PB4  - PIN4                      (input pullup).
 * PB5  - PIN5                      (input pullup).
 * PB6  - PIN6                      (input pullup).
 * PB7  - PIN7                      (input pullup).
 * PB8  - PIN8                      (input pullup).
 * PB9  - PIN9                      (input pullup).
 * PB10 - PIN10                     (input pullup).
 * PB12 - PIN12                     (input pullup).
 * PB13 - PIN13                     (input pullup).
 */
#define VAL_GPIOB_CFGR              (PIN_MODE_INPUT(GPIOB_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN13))
#define VAL_GPIOB_OMODE             (PIN_OMODE_PUSHPULL(GPIOB_PIN0) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN3) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN4) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN5) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN6) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN7) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN8) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN9) |       \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN10) |      \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN12) |      \
                                     PIN_OMODE_PUSHPULL(GPIOB_PIN13))
#define VAL_GPIOB_ODRVR             (PIN_ODRVR_STRONGER(GPIOB_PIN0) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN1) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN2) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN3) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN4) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN5) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN6) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN7) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN8) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN9) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN10) |      \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN12) |      \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN13))
#define VAL_GPIOB_PULL              (PIN_PULL_PULLUP(GPIOB_PIN0) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN1) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN2) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN3) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN4) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN5) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN6) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN7) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN8) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN9) |          \
                                     PIN_PULL_PULLUP(GPIOB_PIN10) |         \
                                     PIN_PULL_PULLUP(GPIOB_PIN12) |         \
                                     PIN_PULL_PULLUP(GPIOB_PIN13))
#define VAL_GPIOB_ODT               (PIN_ODT_HIGH(GPIOB_PIN0) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN1) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN2) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN3) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN4) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN5) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN6) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN7) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN8) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN9) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN10) |            \
                                     PIN_ODT_HIGH(GPIOB_PIN12) |            \
                                     PIN_ODT_HIGH(GPIOB_PIN13))
#define VAL_GPIOB_MUXL              (PIN_IOMUX_MUX(GPIOB_PIN0, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN1, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN2, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN3, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN4, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN5, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN6, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN7, 0U))
#define VAL_GPIOB_MUXH              (PIN_IOMUX_MUX(GPIOB_PIN8, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN9, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOB_PIN10, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOB_PIN12, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOB_PIN13, 0U))
#define VAL_GPIOB_HDRV              (PIN_HDRV_DISABLED(GPIOB_PIN0) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN1) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN2) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN3) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN4) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN5) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN6) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN7) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN8) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN9) |        \
                                     PIN_HDRV_DISABLED(GPIOB_PIN10) |       \
                                     PIN_HDRV_DISABLED(GPIOB_PIN12) |       \
                                     PIN_HDRV_DISABLED(GPIOB_PIN13))

/*
 * Port C setup.
 *
 * PC0  - PIN0                      (input pullup).
 * PC1  - PIN1                      (input pullup).
 * PC2  - PIN2                      (input pullup).
 * PC3  - PIN3                      (input pullup).
 * PC4  - PIN4                      (input pullup).
 * PC5  - PIN5                      (input pullup).
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
#define VAL_GPIOC_CFGR              (PIN_MODE_INPUT(GPIOC_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#define VAL_GPIOC_OMODE             (PIN_OMODE_PUSHPULL(GPIOC_PIN0) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN7) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN10) |      \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN12) |      \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN14) |      \
                                     PIN_OMODE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_ODRVR             (PIN_ODRVR_STRONGER(GPIOC_PIN0) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN1) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN2) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN3) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN4) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN5) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN6) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN7) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN8) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN9) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN10) |      \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN11) |      \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN12) |      \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN13) |      \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN14) |      \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN15))
#define VAL_GPIOC_PULL              (PIN_PULL_PULLUP(GPIOC_PIN0) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN1) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN2) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN3) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN4) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN5) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN6) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN7) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN8) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN9) |          \
                                     PIN_PULL_PULLUP(GPIOC_PIN10) |         \
                                     PIN_PULL_PULLUP(GPIOC_PIN11) |         \
                                     PIN_PULL_PULLUP(GPIOC_PIN12) |         \
                                     PIN_PULL_PULLUP(GPIOC_PIN13) |         \
                                     PIN_PULL_PULLUP(GPIOC_PIN14) |         \
                                     PIN_PULL_PULLUP(GPIOC_PIN15))
#define VAL_GPIOC_ODT               (PIN_ODT_HIGH(GPIOC_PIN0) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN1) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN2) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN3) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN4) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN5) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN6) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN7) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN8) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN9) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN10) |            \
                                     PIN_ODT_HIGH(GPIOC_PIN11) |            \
                                     PIN_ODT_HIGH(GPIOC_PIN12) |            \
                                     PIN_ODT_HIGH(GPIOC_PIN13) |            \
                                     PIN_ODT_HIGH(GPIOC_PIN14) |            \
                                     PIN_ODT_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_MUXL              (PIN_IOMUX_MUX(GPIOC_PIN0, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN1, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN2, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN3, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN4, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN5, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN6, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN7, 0U))
#define VAL_GPIOC_MUXH              (PIN_IOMUX_MUX(GPIOC_PIN8, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN9, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOC_PIN10, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOC_PIN11, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOC_PIN12, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOC_PIN13, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOC_PIN14, 0U) |       \
                                     PIN_IOMUX_MUX(GPIOC_PIN15, 0U))
#define VAL_GPIOC_HDRV              (PIN_HDRV_DISABLED(GPIOC_PIN0) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN1) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN2) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN3) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN4) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN5) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN6) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN7) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN8) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN9) |        \
                                     PIN_HDRV_DISABLED(GPIOC_PIN10) |       \
                                     PIN_HDRV_DISABLED(GPIOC_PIN11) |       \
                                     PIN_HDRV_DISABLED(GPIOC_PIN12) |       \
                                     PIN_HDRV_DISABLED(GPIOC_PIN13) |       \
                                     PIN_HDRV_DISABLED(GPIOC_PIN14) |       \
                                     PIN_HDRV_DISABLED(GPIOC_PIN15))

/*
 * Port D setup.
 *
 * PD2  - PIN2                      (input pullup).
 */
#define VAL_GPIOD_CFGR              (PIN_MODE_INPUT(GPIOD_PIN2))
#define VAL_GPIOD_OMODE             (PIN_OMODE_PUSHPULL(GPIOD_PIN2))
#define VAL_GPIOD_ODRVR             (PIN_ODRVR_STRONGER(GPIOD_PIN2))
#define VAL_GPIOD_PULL              (PIN_PULL_PULLUP(GPIOD_PIN2))
#define VAL_GPIOD_ODT               (PIN_ODT_HIGH(GPIOD_PIN2))
#define VAL_GPIOD_MUXL              (PIN_IOMUX_MUX(GPIOD_PIN2, 0U))
#define VAL_GPIOD_MUXH              0U
#define VAL_GPIOD_HDRV              (PIN_HDRV_DISABLED(GPIOD_PIN2))

/*
 * Port F setup.
 *
 * PF0  - HEXT_IN                   (input floating).
 * PF1  - HEXT_OUT                  (input floating).
 * PF4  - PIN4                      (input pullup).
 * PF5  - PIN5                      (input pullup).
 * PF6  - PIN6                      (input pullup).
 * PF7  - PIN7                      (input pullup).
 * PF11 - PIN11                     (input pullup).
 */
#define VAL_GPIOF_CFGR              (PIN_MODE_INPUT(GPIOF_HEXT_IN) |        \
                                     PIN_MODE_INPUT(GPIOF_HEXT_OUT) |       \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN11))
#define VAL_GPIOF_OMODE             (PIN_OMODE_PUSHPULL(GPIOF_HEXT_IN) |    \
                                     PIN_OMODE_PUSHPULL(GPIOF_HEXT_OUT) |   \
                                     PIN_OMODE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OMODE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OMODE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OMODE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OMODE_PUSHPULL(GPIOF_PIN11))
#define VAL_GPIOF_ODRVR             (PIN_ODRVR_STRONGER(GPIOF_HEXT_IN) |    \
                                     PIN_ODRVR_STRONGER(GPIOF_HEXT_OUT) |   \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN4) |       \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN5) |       \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN6) |       \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN7) |       \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN11))
#define VAL_GPIOF_PULL              (PIN_PULL_FLOATING(GPIOF_HEXT_IN) |     \
                                     PIN_PULL_FLOATING(GPIOF_HEXT_OUT) |    \
                                     PIN_PULL_PULLUP(GPIOF_PIN4) |          \
                                     PIN_PULL_PULLUP(GPIOF_PIN5) |          \
                                     PIN_PULL_PULLUP(GPIOF_PIN6) |          \
                                     PIN_PULL_PULLUP(GPIOF_PIN7) |          \
                                     PIN_PULL_PULLUP(GPIOF_PIN11))
#define VAL_GPIOF_ODT               (PIN_ODT_HIGH(GPIOF_HEXT_IN) |          \
                                     PIN_ODT_HIGH(GPIOF_HEXT_OUT) |         \
                                     PIN_ODT_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODT_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODT_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODT_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODT_HIGH(GPIOF_PIN11))
#define VAL_GPIOF_MUXL              (PIN_IOMUX_MUX(GPIOF_HEXT_IN, 0U) |     \
                                     PIN_IOMUX_MUX(GPIOF_HEXT_OUT, 0U) |    \
                                     PIN_IOMUX_MUX(GPIOF_PIN4, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOF_PIN5, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOF_PIN6, 0U) |        \
                                     PIN_IOMUX_MUX(GPIOF_PIN7, 0U))
#define VAL_GPIOF_MUXH              (PIN_IOMUX_MUX(GPIOF_PIN11, 0U))
#define VAL_GPIOF_HDRV              (PIN_HDRV_DISABLED(GPIOF_HEXT_IN) |     \
                                     PIN_HDRV_DISABLED(GPIOF_HEXT_OUT) |    \
                                     PIN_HDRV_DISABLED(GPIOF_PIN4) |        \
                                     PIN_HDRV_DISABLED(GPIOF_PIN5) |        \
                                     PIN_HDRV_DISABLED(GPIOF_PIN6) |        \
                                     PIN_HDRV_DISABLED(GPIOF_PIN7) |        \
                                     PIN_HDRV_DISABLED(GPIOF_PIN11))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
