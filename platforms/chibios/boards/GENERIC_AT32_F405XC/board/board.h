/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2023..2024 HorrorTroll
    ChibiOS - Copyright (C) 2023..2024 Zhaqian
    ChibiOS - Copyright (C) 2023..2024 Maxjta

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
 * Setup for a AT-START-F405 board.
 */

/*
 * Board identifier.
 */
#define BOARD_AT_START_F405
#define BOARD_NAME                  "Artery AT-START-F405"

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
#if !defined(AT32F405RCT7)
#define AT32F405RCT7
#endif

/*
 * IO pins assignments.
 */
#define GPIOA_BUTTON                0U
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
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
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
#define GPIOB_PIN11                 11U
#define GPIOB_PIN12                 12U
#define GPIOB_PIN13                 13U
#define GPIOB_PIN14                 14U
#define GPIOB_PIN15                 15U

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


/*
 * IO lines assignments.
 */
#define LINE_BUTTON                 PAL_LINE(GPIOA, 0U)
#define LINE_LED_RED                PAL_LINE(GPIOF, 4U)
#define LINE_LED_YELLOW             PAL_LINE(GPIOF, 5U)
#define LINE_LED_GREEN              PAL_LINE(GPIOF, 6U)

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
#define PIN_OUTPUT_PUSHPULL(n)      (0U << (n))
#define PIN_OUTPUT_OPENDRAIN(n)     (1U << (n))
#define PIN_ODRVR_STRONGER(n)       (1U << ((n) * 2U))
#define PIN_ODRVR_MODERATE(n)       (2U << ((n) * 2U))
#define PIN_PULL_NONE(n)            (0U << ((n) * 2U))
#define PIN_PULL_UP(n)              (1U << ((n) * 2U))
#define PIN_PULL_DOWN(n)            (2U << ((n) * 2U))
#define PIN_MUX(n, v)               ((v) << (((n) % 8U) * 4U))
#define PIN_HDRV_NOTACTIVE(n)       (0U << (n))
#define PIN_HDRV_ACTIVE(n)          (1U << (n))


/*
 * GPIOA setup:
 *
 * PA0  - PIN0                      (output none pull).
 * PA1  - PIN1                      (input none pull).
 * PA2  - PIN2                      (input none pull).
 * PA3  - PIN3                      (input none pull).
 * PA4  - PIN4                      (input none pull).
 * PA5  - PIN5                      (input none pull).
 * PA6  - PIN6                      (input none pull).
 * PA7  - PIN7                      (input none pull).
 * PA8  - PIN8                      (input none pull).
 * PA9  - PIN9                      (mux 7).
 * PA10 - PIN10                     (mux 7).
 * PA11 - PIN11                     (input none pull).
 * PA12 - PIN12                     (input none pull).
 * PA13 - SWDIO                     (mux 0).
 * PA14 - SWCLK                     (mux 0).
 * PA15 - PIN15                     (input none pull).
 */
#define VAL_GPIOA_MODE              (PIN_MODE_INPUT(GPIOA_BUTTON) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |            \
                                     PIN_MODE_INPUT(GPIOA_PIN2) |            \
                                     PIN_MODE_INPUT(GPIOA_PIN3) |            \
                                     PIN_MODE_INPUT(GPIOA_PIN4) |            \
                                     PIN_MODE_INPUT(GPIOA_PIN5) |            \
                                     PIN_MODE_INPUT(GPIOA_PIN6) |            \
                                     PIN_MODE_INPUT(GPIOA_PIN7) |            \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |            \
                                     PIN_MODE_INPUT(GPIOA_PIN9) |              \
                                     PIN_MODE_INPUT(GPIOA_PIN10) |             \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN12) |           \
                                     PIN_MODE_MUX(GPIOA_SWDIO) |             \
                                     PIN_MODE_MUX(GPIOA_SWCLK) |             \
                                     PIN_MODE_INPUT(GPIOA_PIN15))

#define VAL_GPIOA_ODT               (PIN_ODT_HIGH(GPIOA_BUTTON) |            \
                                     PIN_ODT_HIGH(GPIOA_PIN1) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN2) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN3) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN4) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN5) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN6) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN7) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN8) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN9) |              \
                                     PIN_ODT_HIGH(GPIOA_PIN10) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN11) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN12) |             \
                                     PIN_ODT_HIGH(GPIOA_SWDIO) |             \
                                     PIN_ODT_HIGH(GPIOA_SWCLK) |             \
                                     PIN_ODT_HIGH(GPIOA_PIN15))

#define VAL_GPIOA_OUTPUT            (PIN_OUTPUT_PUSHPULL(GPIOA_BUTTON) |     \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN1) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN2) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN3) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN4) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN5) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN6) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN7) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN8) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN9) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN10) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN11) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN12) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOA_PIN15))

#define VAL_GPIOA_ODRVR             (PIN_ODRVR_STRONGER(GPIOA_BUTTON) |      \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN1) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN2) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN3) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN4) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN5) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN6) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN7) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN8) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN9) |        \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN10) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN11) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN12) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_SWDIO) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_SWCLK) |       \
                                     PIN_ODRVR_STRONGER(GPIOA_PIN15))

#define VAL_GPIOA_PULL              (PIN_PULL_NONE(GPIOA_BUTTON) |           \
                                     PIN_PULL_NONE(GPIOA_PIN1) |             \
                                     PIN_PULL_NONE(GPIOA_PIN2) |             \
                                     PIN_PULL_NONE(GPIOA_PIN3) |             \
                                     PIN_PULL_NONE(GPIOA_PIN4) |             \
                                     PIN_PULL_NONE(GPIOA_PIN5) |             \
                                     PIN_PULL_NONE(GPIOA_PIN6) |             \
                                     PIN_PULL_NONE(GPIOA_PIN7) |             \
                                     PIN_PULL_NONE(GPIOA_PIN8) |             \
                                     PIN_PULL_NONE(GPIOA_PIN9) |             \
                                     PIN_PULL_NONE(GPIOA_PIN10) |            \
                                     PIN_PULL_NONE(GPIOA_PIN11) |            \
                                     PIN_PULL_NONE(GPIOA_PIN12) |            \
                                     PIN_PULL_NONE(GPIOA_SWDIO) |            \
                                     PIN_PULL_NONE(GPIOA_SWCLK) |            \
                                     PIN_PULL_NONE(GPIOA_PIN15))

#define VAL_GPIOA_MUXL              (PIN_MUX(GPIOA_BUTTON, 0U) |             \
                                     PIN_MUX(GPIOA_PIN1, 0U) |               \
                                     PIN_MUX(GPIOA_PIN2, 0U) |               \
                                     PIN_MUX(GPIOA_PIN3, 0U) |               \
                                     PIN_MUX(GPIOA_PIN4, 5U) |               \
                                     PIN_MUX(GPIOA_PIN5, 5U) |               \
                                     PIN_MUX(GPIOA_PIN6, 5U) |               \
                                     PIN_MUX(GPIOA_PIN7, 5U))

#define VAL_GPIOA_MUXH              (PIN_MUX(GPIOA_PIN8, 0U) |               \
                                     PIN_MUX(GPIOA_PIN9, 7U) |               \
                                     PIN_MUX(GPIOA_PIN10, 7U) |              \
                                     PIN_MUX(GPIOA_PIN11, 0U) |              \
                                     PIN_MUX(GPIOA_PIN12, 0U) |              \
                                     PIN_MUX(GPIOA_SWDIO, 0U) |              \
                                     PIN_MUX(GPIOA_SWCLK, 0U) |              \
                                     PIN_MUX(GPIOA_PIN15, 0U))

#define VAL_GPIOA_HDRV              (PIN_HDRV_NOTACTIVE(GPIOA_BUTTON) |      \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN1) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN2) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN3) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN4) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN5) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN6) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN7) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN8) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN9) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN10) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN11) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN12) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOA_SWDIO) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOA_SWCLK) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOA_PIN15))
/*
 * GPIOB setup:
 *
 * PB0  - PIN0                      (input none pull).
 * PB1  - PIN1                      (input none pull).
 * PB2  - PIN2                      (input none pull).
 * PB3  - PIN3                      (input none pull).
 * PB4  - PIN4                      (input none pull).
 * PB5  - PIN5                      (input none pull).
 * PB6  - PIN6                      (input none pull).
 * PB7  - PIN7                      (input none pull).
 * PB8  - PIN8                      (input none pull).
 * PB9  - PIN9                      (input none pull).
 * PB10 - PIN10                     (input none pull).
 * PB11 - PIN11                     (input none pull).
 * PB12 - PIN12                     (input none pull).
 * PB13 - PIN13                     (input none pull).
 * PB14 - PIN14                     (input none pull).
 * PB15 - PIN15                     (input none pull).
 */
#define VAL_GPIOB_MODE              (PIN_MODE_INPUT(GPIOB_PIN0) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN3) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN6) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN9) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN10) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN11) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN12) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN13) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN15))

#define VAL_GPIOB_ODT               (PIN_ODT_HIGH(GPIOB_PIN0) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN1) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN2) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN3) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN4) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN5) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN6) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN7) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN8) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN9) |              \
                                     PIN_ODT_HIGH(GPIOB_PIN10) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN11) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN12) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN13) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN14) |             \
                                     PIN_ODT_HIGH(GPIOB_PIN15))

#define VAL_GPIOB_OUTPUT            (PIN_OUTPUT_PUSHPULL(GPIOB_PIN0) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN3) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN4) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN5) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN6) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN7) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN8) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN9) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN10) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN11) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN12) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN13) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN14) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOB_PIN15))

#define VAL_GPIOB_ODRVR             (PIN_ODRVR_STRONGER(GPIOB_PIN0) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN1) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN2) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN3) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN4) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN5) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN6) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN7) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN8) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN9) |        \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN10) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN11) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN12) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN13) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN14) |       \
                                     PIN_ODRVR_STRONGER(GPIOB_PIN15))

#define VAL_GPIOB_PULL              (PIN_PULL_NONE(GPIOB_PIN0) |             \
                                     PIN_PULL_NONE(GPIOB_PIN1) |             \
                                     PIN_PULL_NONE(GPIOB_PIN2) |             \
                                     PIN_PULL_NONE(GPIOB_PIN3) |             \
                                     PIN_PULL_NONE(GPIOB_PIN4) |             \
                                     PIN_PULL_NONE(GPIOB_PIN5) |             \
                                     PIN_PULL_NONE(GPIOB_PIN6) |             \
                                     PIN_PULL_NONE(GPIOB_PIN7) |             \
                                     PIN_PULL_NONE(GPIOB_PIN8) |             \
                                     PIN_PULL_NONE(GPIOB_PIN9) |             \
                                     PIN_PULL_NONE(GPIOB_PIN10) |            \
                                     PIN_PULL_NONE(GPIOB_PIN11) |            \
                                     PIN_PULL_NONE(GPIOB_PIN12) |            \
                                     PIN_PULL_NONE(GPIOB_PIN13) |            \
                                     PIN_PULL_NONE(GPIOB_PIN14) |            \
                                     PIN_PULL_NONE(GPIOB_PIN15))

#define VAL_GPIOB_MUXL              (PIN_MUX(GPIOB_PIN0, 0U) |               \
                                     PIN_MUX(GPIOB_PIN1, 0U) |               \
                                     PIN_MUX(GPIOB_PIN2, 0U) |               \
                                     PIN_MUX(GPIOB_PIN3, 0U) |               \
                                     PIN_MUX(GPIOB_PIN4, 0U) |               \
                                     PIN_MUX(GPIOB_PIN5, 0U) |               \
                                     PIN_MUX(GPIOB_PIN6, 0U) |               \
                                     PIN_MUX(GPIOB_PIN7, 0U))

#define VAL_GPIOB_MUXH              (PIN_MUX(GPIOB_PIN8, 0U) |               \
                                     PIN_MUX(GPIOB_PIN9, 0U) |               \
                                     PIN_MUX(GPIOB_PIN10, 0U) |              \
                                     PIN_MUX(GPIOB_PIN11, 0U) |              \
                                     PIN_MUX(GPIOB_PIN12, 0U) |              \
                                     PIN_MUX(GPIOB_PIN13, 0U) |              \
                                     PIN_MUX(GPIOB_PIN14, 0U) |              \
                                     PIN_MUX(GPIOB_PIN15, 0U))

#define VAL_GPIOB_HDRV              (PIN_HDRV_NOTACTIVE(GPIOB_PIN0) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN1) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN2) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN3) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN4) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN5) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN6) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN7) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN8) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN9) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN10) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN11) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN12) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN13) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN14) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOB_PIN15))

/*
 * GPIOC setup:
 *
 * PC0  - PIN0                      (input none pull).
 * PC1  - PIN1                      (input none pull).
 * PC2  - PIN2                      (input none pull).
 * PC3  - PIN3                      (input none pull).
 * PC4  - PIN4                      (input none pull).
 * PC5  - PIN5                      (input none pull).
 * PC6  - PIN6                      (input none pull).
 * PC7  - PIN7                      (input none pull).
 * PC8  - PIN8                      (input none pull).
 * PC9  - PIN9                      (input none pull).
 * PC10 - PIN10                     (input none pull).
 * PC11 - PIN11                     (input none pull).
 * PC12 - PIN12                     (input none pull).
 * PC13 - PIN13                     (input none pull).
 * PC14 - PIN14                     (input none pull).
 * PC15 - PIN15                     (input none pull).
 */
#define VAL_GPIOC_MODE              (PIN_MODE_INPUT(GPIOC_PIN0) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |            \
                                     PIN_MODE_INPUT(GPIOC_PIN10) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN12) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN15))

#define VAL_GPIOC_ODT               (PIN_ODT_HIGH(GPIOC_PIN0) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN1) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN2) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN3) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN4) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN5) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN6) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN7) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN8) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN9) |              \
                                     PIN_ODT_HIGH(GPIOC_PIN10) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN11) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN12) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN13) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN14) |             \
                                     PIN_ODT_HIGH(GPIOC_PIN15))

#define VAL_GPIOC_OUTPUT            (PIN_OUTPUT_PUSHPULL(GPIOC_PIN0) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN7) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN10) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN12) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN14) |      \
                                     PIN_OUTPUT_PUSHPULL(GPIOC_PIN15))

#define VAL_GPIOC_ODRVR             (PIN_ODRVR_STRONGER(GPIOC_PIN0) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN1) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN2) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN3) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN4) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN5) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN6) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN7) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN8) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN9) |        \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN10) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN11) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN12) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN13) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN14) |       \
                                     PIN_ODRVR_STRONGER(GPIOC_PIN15))

#define VAL_GPIOC_PULL              (PIN_PULL_NONE(GPIOC_PIN0) |             \
                                     PIN_PULL_NONE(GPIOC_PIN1) |             \
                                     PIN_PULL_NONE(GPIOC_PIN2) |             \
                                     PIN_PULL_NONE(GPIOC_PIN3) |             \
                                     PIN_PULL_NONE(GPIOC_PIN4) |             \
                                     PIN_PULL_NONE(GPIOC_PIN5) |             \
                                     PIN_PULL_NONE(GPIOC_PIN6) |             \
                                     PIN_PULL_NONE(GPIOC_PIN7) |             \
                                     PIN_PULL_NONE(GPIOC_PIN8) |             \
                                     PIN_PULL_NONE(GPIOC_PIN9) |             \
                                     PIN_PULL_NONE(GPIOC_PIN10) |            \
                                     PIN_PULL_NONE(GPIOC_PIN11) |            \
                                     PIN_PULL_NONE(GPIOC_PIN12) |            \
                                     PIN_PULL_NONE(GPIOC_PIN13) |            \
                                     PIN_PULL_NONE(GPIOC_PIN14) |            \
                                     PIN_PULL_NONE(GPIOC_PIN15))

#define VAL_GPIOC_MUXL              (PIN_MUX(GPIOC_PIN0, 0U) |               \
                                     PIN_MUX(GPIOC_PIN1, 0U) |               \
                                     PIN_MUX(GPIOC_PIN2, 0U) |               \
                                     PIN_MUX(GPIOC_PIN3, 0U) |               \
                                     PIN_MUX(GPIOC_PIN4, 0U) |               \
                                     PIN_MUX(GPIOC_PIN5, 0U) |               \
                                     PIN_MUX(GPIOC_PIN6, 0U) |               \
                                     PIN_MUX(GPIOC_PIN7, 0U))

#define VAL_GPIOC_MUXH              (PIN_MUX(GPIOC_PIN8, 0U) |               \
                                     PIN_MUX(GPIOC_PIN9, 0U) |               \
                                     PIN_MUX(GPIOC_PIN10, 0U) |              \
                                     PIN_MUX(GPIOC_PIN11, 0U) |              \
                                     PIN_MUX(GPIOC_PIN12, 0U) |              \
                                     PIN_MUX(GPIOC_PIN13, 0U) |              \
                                     PIN_MUX(GPIOC_PIN14, 0U) |              \
                                     PIN_MUX(GPIOC_PIN15, 0U))

#define VAL_GPIOC_HDRV              (PIN_HDRV_NOTACTIVE(GPIOC_PIN0) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN1) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN2) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN3) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN4) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN5) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN6) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN7) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN8) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN9) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN10) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN11) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN12) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN13) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN14) |       \
                                     PIN_HDRV_NOTACTIVE(GPIOC_PIN15))

/*
 * GPIOD setup:
 * PD2  - PIN2                      (input none pull).
 */
#define VAL_GPIOD_MODE              (PIN_MODE_INPUT(GPIOD_PIN2))
#define VAL_GPIOD_ODT               (PIN_ODT_HIGH(GPIOD_PIN2))
#define VAL_GPIOD_OUTPUT            (PIN_OUTPUT_PUSHPULL(GPIOD_PIN2))
#define VAL_GPIOD_ODRVR             (PIN_ODRVR_STRONGER(GPIOD_PIN2))
#define VAL_GPIOD_PULL              (PIN_PULL_NONE(GPIOD_PIN2))
#define VAL_GPIOD_MUXL              (PIN_MUX(GPIOD_PIN2, 0U))
#define VAL_GPIOD_MUXH              0U
#define VAL_GPIOD_HDRV              (PIN_HDRV_NOTACTIVE(GPIOD_PIN2))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (input none pull).
 * PF1  - PIN1                      (input none pull).
 * PF4  - PIN4                      (output none pull).
 * PF5  - PIN5                      (output none pull).
 * PF6  - PIN6                      (output none pull).
 * PF7  - PIN7                      (input none pull).
 * PF11 - PIN11                     (input none pull).
 */
#define VAL_GPIOF_MODE              (PIN_MODE_INPUT(GPIOF_HEXT_IN) |         \
									 PIN_MODE_INPUT(GPIOF_HEXT_OUT) |        \
                                     PIN_MODE_OUTPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_OUTPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_OUTPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7)  |           \
									 PIN_MODE_INPUT(GPIOF_PIN11))

#define VAL_GPIOF_ODT               (PIN_ODT_HIGH(GPIOF_HEXT_IN) |           \
                                     PIN_ODT_HIGH(GPIOF_HEXT_OUT) |          \
									 PIN_ODT_HIGH(GPIOF_PIN4) |              \
                                     PIN_ODT_HIGH(GPIOF_PIN5) |              \
                                     PIN_ODT_HIGH(GPIOF_PIN6) |              \
                                     PIN_ODT_HIGH(GPIOF_PIN7) |              \
                                     PIN_ODT_HIGH(GPIOF_PIN11))


#define VAL_GPIOF_OUTPUT            (PIN_OUTPUT_PUSHPULL(GPIOF_HEXT_IN) |    \
                                     PIN_OUTPUT_PUSHPULL(GPIOF_HEXT_OUT) |   \
									 PIN_OUTPUT_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OUTPUT_PUSHPULL(GPIOF_PIN11))


#define VAL_GPIOF_ODRVR             (PIN_ODRVR_STRONGER(GPIOF_HEXT_IN) |     \
                                     PIN_ODRVR_STRONGER(GPIOF_HEXT_OUT) |    \
									 PIN_ODRVR_STRONGER(GPIOF_PIN4) |        \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN5) |        \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN6) |        \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN7) |        \
                                     PIN_ODRVR_STRONGER(GPIOF_PIN11))

#define VAL_GPIOF_PULL              (PIN_PULL_NONE(GPIOF_HEXT_IN) |          \
                                     PIN_PULL_NONE(GPIOF_HEXT_OUT) |         \
									 PIN_PULL_NONE(GPIOF_PIN4) |             \
                                     PIN_PULL_NONE(GPIOF_PIN5) |             \
                                     PIN_PULL_NONE(GPIOF_PIN6) |             \
                                     PIN_PULL_NONE(GPIOF_PIN7) |             \
                                     PIN_PULL_NONE(GPIOF_PIN11))

#define VAL_GPIOF_MUXL              (PIN_MUX(GPIOF_HEXT_IN, 0U) |            \
                                     PIN_MUX(GPIOF_HEXT_OUT, 0U) |           \
									 PIN_MUX(GPIOF_PIN4, 0U) |               \
                                     PIN_MUX(GPIOF_PIN5, 0U) |               \
                                     PIN_MUX(GPIOF_PIN6, 0U) |               \
                                     PIN_MUX(GPIOF_PIN7, 0U) |               \
                                     PIN_MUX(GPIOF_PIN11, 0U))
#define VAL_GPIOF_MUXH               0U

#define VAL_GPIOF_HDRV              (PIN_HDRV_NOTACTIVE(GPIOF_HEXT_IN) |     \
                                     PIN_HDRV_NOTACTIVE(GPIOF_HEXT_OUT) |    \
									 PIN_HDRV_NOTACTIVE(GPIOF_PIN4) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOF_PIN5) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOF_PIN6) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOF_PIN7) |        \
                                     PIN_HDRV_NOTACTIVE(GPIOF_PIN11))

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
