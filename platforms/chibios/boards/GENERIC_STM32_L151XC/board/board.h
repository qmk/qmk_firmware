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

/*
 * Generic STM32L151xC board file. Based on the ST_NUCLEO64_L152RE config,
 * modified to use a more compatible pin setup.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for a generic STM32L151xC board.
 */

/*
 * Board identifier.
 */
#define BOARD_GENERIC_STM32_L151XC
#define BOARD_NAME                  "STM32L151xC generic"

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

/*
 * MCU type as defined in the ST header.
 */
#undef STM32L151xC
#define STM32L151xC

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
#define GPIOA_PIN10                  10U
#define GPIOA_PIN11                11U
#define GPIOA_PIN12                12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                  15U

#define GPIOB_PIN0                  0U
#define GPIOB_PIN1                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_PIN3                 3U
#define GPIOB_PIN4                 4U
#define GPIOB_PIN5                 5U
#define GPIOB_PIN6              6U
#define GPIOB_PIN7              7U
#define GPIOB_PIN8                 8U
#define GPIOB_PIN9                  9U
#define GPIOB_PIN10                  10U
#define GPIOB_PIN11                  11U
#define GPIOB_PIN12                  12U
#define GPIOB_PIN13                  13U
#define GPIOB_PIN14                  14U
#define GPIOB_PIN15                  15U

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
#define GPIOC_PIN10                  10U
#define GPIOC_PIN11                  11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13               13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                 2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
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

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)

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
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - PIN0                      (analog).
 * PA1  - PIN1                      (analog).
 * PA2  - PIN2                      (analog).
 * PA3  - PIN3                      (analog).
 * PA4  - PIN4                      (analog).
 * PA5  - PIN5                      (analog).
 * PA6  - PIN6                      (analog).
 * PA7  - PIN7                      (analog).
 * PA8  - PIN8                      (analog).
 * PA9  - PIN9                      (analog).
 * PA10 - PIN10                     (analog).
 * PA11 - PIN11                     (input floating, USB DM).
 * PA12 - PIN12                     (input floating, USB DP).
 * PA13 - SWDIO                     (alternate 0, pullup).
 * PA14 - SWCLK                     (alternate 0, pulldown).
 * PA15 - PIN15                     (analog).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ANALOG(GPIOA_PIN0) |         \
                                     PIN_MODE_ANALOG(GPIOA_PIN1) |         \
                                     PIN_MODE_ANALOG(GPIOA_PIN2) |         \
                                     PIN_MODE_ANALOG(GPIOA_PIN3) |         \
                                     PIN_MODE_ANALOG(GPIOA_PIN4) |         \
                                     PIN_MODE_ANALOG(GPIOA_PIN5) |         \
                                     PIN_MODE_ANALOG(GPIOA_PIN6) |        \
                                     PIN_MODE_ANALOG(GPIOA_PIN7) |        \
                                     PIN_MODE_ANALOG(GPIOA_PIN8) |         \
                                     PIN_MODE_ANALOG(GPIOA_PIN9) |         \
                                     PIN_MODE_ANALOG(GPIOA_PIN10) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN12) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ANALOG(GPIOA_PIN15))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN5) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN6) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN7) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN9) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN10) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_PIN0) |        \
                                     PIN_OSPEED_HIGH(GPIOA_PIN1) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_PIN2) |      \
                                     PIN_OSPEED_MEDIUM(GPIOA_PIN3) |      \
                                     PIN_OSPEED_HIGH(GPIOA_PIN4) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_PIN5) |   \
                                     PIN_OSPEED_HIGH(GPIOA_PIN6) |       \
                                     PIN_OSPEED_HIGH(GPIOA_PIN7) |       \
                                     PIN_OSPEED_HIGH(GPIOA_PIN8) |        \
                                     PIN_OSPEED_HIGH(GPIOA_PIN9) |        \
                                     PIN_OSPEED_HIGH(GPIOA_PIN10) |        \
                                     PIN_OSPEED_HIGH(GPIOA_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN2) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN3) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN5) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN6) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN7) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN10) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN15))
#define VAL_GPIOA_ODR               (PIN_ODR_LOW(GPIOA_PIN0) |           \
                                     PIN_ODR_LOW(GPIOA_PIN1) |           \
                                     PIN_ODR_LOW(GPIOA_PIN2) |           \
                                     PIN_ODR_LOW(GPIOA_PIN3) |           \
                                     PIN_ODR_LOW(GPIOA_PIN4) |           \
                                     PIN_ODR_LOW(GPIOA_PIN5) |         \
                                     PIN_ODR_LOW(GPIOA_PIN6) |          \
                                     PIN_ODR_LOW(GPIOA_PIN7) |          \
                                     PIN_ODR_LOW(GPIOA_PIN8) |           \
                                     PIN_ODR_LOW(GPIOA_PIN9) |           \
                                     PIN_ODR_LOW(GPIOA_PIN10) |           \
                                     PIN_ODR_LOW(GPIOA_PIN11) |            \
                                     PIN_ODR_LOW(GPIOA_PIN12) |            \
                                     PIN_ODR_LOW(GPIOA_SWDIO) |            \
                                     PIN_ODR_LOW(GPIOA_SWCLK) |            \
                                     PIN_ODR_LOW(GPIOA_PIN15))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PIN0, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN1, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN2, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN3, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN4, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN5, 0U) |     \
                                     PIN_AFIO_AF(GPIOA_PIN6, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_PIN7, 0U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN9, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN10, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_PIN15, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - PIN0                      (analog).
 * PB1  - PIN1                      (analog).
 * PB2  - PIN2                      (analog).
 * PB3  - PIN3                      (analog).
 * PB4  - PIN4                      (analog).
 * PB5  - PIN5                      (analog).
 * PB6  - PIN6                      (analog).
 * PB7  - PIN7                      (analog).
 * PB8  - PIN8                      (analog).
 * PB9  - PIN9                      (analog).
 * PB10 - PIN10                     (analog).
 * PB11 - PIN11                     (analog).
 * PB12 - PIN12                     (analog).
 * PB13 - PIN13                     (analog).
 * PB14 - PIN14                     (analog).
 * PB15 - PIN15                     (analog).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ANALOG(GPIOB_PIN0) |         \
                                     PIN_MODE_ANALOG(GPIOB_PIN1) |           \
                                     PIN_MODE_ANALOG(GPIOB_PIN2) |           \
                                     PIN_MODE_ANALOG(GPIOB_PIN3) |        \
                                     PIN_MODE_ANALOG(GPIOB_PIN4) |         \
                                     PIN_MODE_ANALOG(GPIOB_PIN5) |         \
                                     PIN_MODE_ANALOG(GPIOB_PIN6) |        \
                                     PIN_MODE_ANALOG(GPIOB_PIN7) |           \
                                     PIN_MODE_ANALOG(GPIOB_PIN8) |        \
                                     PIN_MODE_ANALOG(GPIOB_PIN9) |        \
                                     PIN_MODE_ANALOG(GPIOB_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOB_PIN11) |          \
                                     PIN_MODE_ANALOG(GPIOB_PIN12) |          \
                                     PIN_MODE_ANALOG(GPIOB_PIN13) |          \
                                     PIN_MODE_ANALOG(GPIOB_PIN14) |          \
                                     PIN_MODE_ANALOG(GPIOB_PIN15))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN3) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN6) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN9) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN10) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN15))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_PIN0) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN3) |           \
                                     PIN_OSPEED_HIGH(GPIOB_PIN4) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN5) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN6) |       \
                                     PIN_OSPEED_HIGH(GPIOB_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN8) |       \
                                     PIN_OSPEED_HIGH(GPIOB_PIN9) |       \
                                     PIN_OSPEED_HIGH(GPIOB_PIN10) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN15))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN1) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN3) |          \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN6) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN8) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN9) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN10) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN13) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN14) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN15))
#define VAL_GPIOB_ODR               (PIN_ODR_LOW(GPIOB_PIN0) |           \
                                     PIN_ODR_LOW(GPIOB_PIN1) |             \
                                     PIN_ODR_LOW(GPIOB_PIN2) |             \
                                     PIN_ODR_LOW(GPIOB_PIN3) |              \
                                     PIN_ODR_LOW(GPIOB_PIN4) |           \
                                     PIN_ODR_LOW(GPIOB_PIN5) |           \
                                     PIN_ODR_LOW(GPIOB_PIN6) |          \
                                     PIN_ODR_LOW(GPIOB_PIN7) |             \
                                     PIN_ODR_LOW(GPIOB_PIN8) |          \
                                     PIN_ODR_LOW(GPIOB_PIN9) |          \
                                     PIN_ODR_LOW(GPIOB_PIN10) |           \
                                     PIN_ODR_LOW(GPIOB_PIN11) |            \
                                     PIN_ODR_LOW(GPIOB_PIN12) |            \
                                     PIN_ODR_LOW(GPIOB_PIN13) |            \
                                     PIN_ODR_LOW(GPIOB_PIN14) |            \
                                     PIN_ODR_LOW(GPIOB_PIN15))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PIN0, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN3, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN5, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN6, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN9, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN10, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN15, 0U))

/*
 * GPIOC setup:
 *
 * PC0  - PIN0                      (analog).
 * PC1  - PIN1                      (analog).
 * PC2  - PIN2                      (analog).
 * PC3  - PIN3                      (analog).
 * PC4  - PIN4                      (analog).
 * PC5  - PIN5                      (analog).
 * PC6  - PIN6                      (analog).
 * PC7  - PIN7                      (analog).
 * PC8  - PIN8                      (analog).
 * PC9  - PIN9                      (analog).
 * PC10 - PIN10                     (analog).
 * PC11 - PIN11                     (analog).
 * PC12 - PIN12                     (analog).
 * PC13 - PIN13                     (analog).
 * PC14 - PIN14                     (analog).
 * PC15 - PIN15                     (analog).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ANALOG(GPIOC_PIN0) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN1) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN2) |           \
                                     PIN_MODE_ANALOG(GPIOC_PIN3) |           \
                                     PIN_MODE_ANALOG(GPIOC_PIN4) |           \
                                     PIN_MODE_ANALOG(GPIOC_PIN5) |           \
                                     PIN_MODE_ANALOG(GPIOC_PIN6) |           \
                                     PIN_MODE_ANALOG(GPIOC_PIN7) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN8) |           \
                                     PIN_MODE_ANALOG(GPIOC_PIN9) |           \
                                     PIN_MODE_ANALOG(GPIOC_PIN10) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN11) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN12) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN14) |       \
                                     PIN_MODE_ANALOG(GPIOC_PIN15))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN14) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_PIN0) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN1) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN7) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN13) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN14) |      \
                                     PIN_OSPEED_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN4) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN5) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN6) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN10) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN13) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN14) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN15))
#define VAL_GPIOC_ODR               (PIN_ODR_LOW(GPIOC_PIN0) |           \
                                     PIN_ODR_LOW(GPIOC_PIN1) |           \
                                     PIN_ODR_LOW(GPIOC_PIN2) |             \
                                     PIN_ODR_LOW(GPIOC_PIN3) |             \
                                     PIN_ODR_LOW(GPIOC_PIN4) |             \
                                     PIN_ODR_LOW(GPIOC_PIN5) |             \
                                     PIN_ODR_LOW(GPIOC_PIN6) |             \
                                     PIN_ODR_LOW(GPIOC_PIN7) |           \
                                     PIN_ODR_LOW(GPIOC_PIN8) |             \
                                     PIN_ODR_LOW(GPIOC_PIN9) |             \
                                     PIN_ODR_LOW(GPIOC_PIN10) |            \
                                     PIN_ODR_LOW(GPIOC_PIN11) |            \
                                     PIN_ODR_LOW(GPIOC_PIN12) |            \
                                     PIN_ODR_LOW(GPIOC_PIN13) |           \
                                     PIN_ODR_LOW(GPIOC_PIN14) |         \
                                     PIN_ODR_LOW(GPIOC_PIN15))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN14, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (analog).
 * PD1  - PIN1                      (analog).
 * PD2  - PIN2                      (analog).
 * PD3  - PIN3                      (analog).
 * PD4  - PIN4                      (analog).
 * PD5  - PIN5                      (analog).
 * PD6  - PIN6                      (analog).
 * PD7  - PIN7                      (analog).
 * PD8  - PIN8                      (analog).
 * PD9  - PIN9                      (analog).
 * PD10 - PIN10                     (analog).
 * PD11 - PIN11                     (analog).
 * PD12 - PIN12                     (analog).
 * PD13 - PIN13                     (analog).
 * PD14 - PIN14                     (analog).
 * PD15 - PIN15                     (analog).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ANALOG(GPIOD_PIN0) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN1) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN2) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN3) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN4) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN5) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN6) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN7) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN8) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN9) |           \
                                     PIN_MODE_ANALOG(GPIOD_PIN10) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN11) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN12) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN13) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN14) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOD_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_PIN0) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN1) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN4) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN5) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN6) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN10) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN13) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN14) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_LOW(GPIOD_PIN0) |             \
                                     PIN_ODR_LOW(GPIOD_PIN1) |             \
                                     PIN_ODR_LOW(GPIOD_PIN2) |             \
                                     PIN_ODR_LOW(GPIOD_PIN3) |             \
                                     PIN_ODR_LOW(GPIOD_PIN4) |             \
                                     PIN_ODR_LOW(GPIOD_PIN5) |             \
                                     PIN_ODR_LOW(GPIOD_PIN6) |             \
                                     PIN_ODR_LOW(GPIOD_PIN7) |             \
                                     PIN_ODR_LOW(GPIOD_PIN8) |             \
                                     PIN_ODR_LOW(GPIOD_PIN9) |             \
                                     PIN_ODR_LOW(GPIOD_PIN10) |            \
                                     PIN_ODR_LOW(GPIOD_PIN11) |            \
                                     PIN_ODR_LOW(GPIOD_PIN12) |            \
                                     PIN_ODR_LOW(GPIOD_PIN13) |            \
                                     PIN_ODR_LOW(GPIOD_PIN14) |            \
                                     PIN_ODR_LOW(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                      (analog).
 * PE1  - PIN1                      (analog).
 * PE2  - PIN2                      (analog).
 * PE3  - PIN3                      (analog).
 * PE4  - PIN4                      (analog).
 * PE5  - PIN5                      (analog).
 * PE6  - PIN6                      (analog).
 * PE7  - PIN7                      (analog).
 * PE8  - PIN8                      (analog).
 * PE9  - PIN9                      (analog).
 * PE10 - PIN10                     (analog).
 * PE11 - PIN11                     (analog).
 * PE12 - PIN12                     (analog).
 * PE13 - PIN13                     (analog).
 * PE14 - PIN14                     (analog).
 * PE15 - PIN15                     (analog).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ANALOG(GPIOE_PIN0) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN1) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN2) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN3) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN4) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN5) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN6) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN7) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN8) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN9) |           \
                                     PIN_MODE_ANALOG(GPIOE_PIN10) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN11) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN12) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN13) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN14) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOE_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_PIN0) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN1) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN4) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN5) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN6) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN10) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN13) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN14) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_LOW(GPIOE_PIN0) |             \
                                     PIN_ODR_LOW(GPIOE_PIN1) |             \
                                     PIN_ODR_LOW(GPIOE_PIN2) |             \
                                     PIN_ODR_LOW(GPIOE_PIN3) |             \
                                     PIN_ODR_LOW(GPIOE_PIN4) |             \
                                     PIN_ODR_LOW(GPIOE_PIN5) |             \
                                     PIN_ODR_LOW(GPIOE_PIN6) |             \
                                     PIN_ODR_LOW(GPIOE_PIN7) |             \
                                     PIN_ODR_LOW(GPIOE_PIN8) |             \
                                     PIN_ODR_LOW(GPIOE_PIN9) |             \
                                     PIN_ODR_LOW(GPIOE_PIN10) |            \
                                     PIN_ODR_LOW(GPIOE_PIN11) |            \
                                     PIN_ODR_LOW(GPIOE_PIN12) |            \
                                     PIN_ODR_LOW(GPIOE_PIN13) |            \
                                     PIN_ODR_LOW(GPIOE_PIN14) |            \
                                     PIN_ODR_LOW(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (analog).
 * PH3  - PIN3                      (analog).
 * PH4  - PIN4                      (analog).
 * PH5  - PIN5                      (analog).
 * PH6  - PIN6                      (analog).
 * PH7  - PIN7                      (analog).
 * PH8  - PIN8                      (analog).
 * PH9  - PIN9                      (analog).
 * PH10 - PIN10                     (analog).
 * PH11 - PIN11                     (analog).
 * PH12 - PIN12                     (analog).
 * PH13 - PIN13                     (analog).
 * PH14 - PIN14                     (analog).
 * PH15 - PIN15                     (analog).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_ANALOG(GPIOH_PIN2) |           \
                                     PIN_MODE_ANALOG(GPIOH_PIN3) |           \
                                     PIN_MODE_ANALOG(GPIOH_PIN4) |           \
                                     PIN_MODE_ANALOG(GPIOH_PIN5) |           \
                                     PIN_MODE_ANALOG(GPIOH_PIN6) |           \
                                     PIN_MODE_ANALOG(GPIOH_PIN7) |           \
                                     PIN_MODE_ANALOG(GPIOH_PIN8) |           \
                                     PIN_MODE_ANALOG(GPIOH_PIN9) |           \
                                     PIN_MODE_ANALOG(GPIOH_PIN10) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN11) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN12) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN13) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN14) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN4) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN5) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN6) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN10) |        \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN13) |        \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN14) |        \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_LOW(GPIOH_OSC_IN) |           \
                                     PIN_ODR_LOW(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_LOW(GPIOH_PIN2) |             \
                                     PIN_ODR_LOW(GPIOH_PIN3) |             \
                                     PIN_ODR_LOW(GPIOH_PIN4) |             \
                                     PIN_ODR_LOW(GPIOH_PIN5) |             \
                                     PIN_ODR_LOW(GPIOH_PIN6) |             \
                                     PIN_ODR_LOW(GPIOH_PIN7) |             \
                                     PIN_ODR_LOW(GPIOH_PIN8) |             \
                                     PIN_ODR_LOW(GPIOH_PIN9) |             \
                                     PIN_ODR_LOW(GPIOH_PIN10) |            \
                                     PIN_ODR_LOW(GPIOH_PIN11) |            \
                                     PIN_ODR_LOW(GPIOH_PIN12) |            \
                                     PIN_ODR_LOW(GPIOH_PIN13) |            \
                                     PIN_ODR_LOW(GPIOH_PIN14) |            \
                                     PIN_ODR_LOW(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * USB bus control. The STM32L1 DP pull-up is internal, controlled through
 * SYSCFG_PMC.USB_PU (the USBv1 LLD's BCDR-based default does not exist on
 * this family).
 */
#define usb_lld_connect_bus(usbp)    (SYSCFG->PMC |= SYSCFG_PMC_USB_PU)
#define usb_lld_disconnect_bus(usbp) (SYSCFG->PMC &= ~SYSCFG_PMC_USB_PU)

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

#endif /* BOARD_H */
