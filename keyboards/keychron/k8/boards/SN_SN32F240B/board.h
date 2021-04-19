/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

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

/*
 * Setup for Generic STM32_F303 Board
 */

/*
 * Board identifier.
 */
#define BOARD_GENERIC_SN32_F240B
#define BOARD_NAME "SN32F240B"

/*
 * MCU type as defined in the ST header.
 */
#define system_SN32F240B

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0 0U
#define GPIOA_PIN1 1U
#define GPIOA_PIN2 2U
#define GPIOA_PIN3 3U
#define GPIOA_PIN4 4U
#define GPIOA_PIN5 5U
#define GPIOA_PIN6 6U
#define GPIOA_PIN7 7U
#define GPIOA_PIN8 8U
#define GPIOA_PIN9 9U
#define GPIOA_PIN10 10U
#define GPIOA_PIN11 11U
#define GPIOA_PIN12 12U
#define GPIOA_PIN13 13U
#define GPIOA_PIN14 14U
#define GPIOA_PIN15 15U

#define GPIOB_PIN0 0U
#define GPIOB_PIN1 1U
#define GPIOB_PIN2 2U
#define GPIOB_PIN3 3U
#define GPIOB_PIN4 4U
#define GPIOB_PIN5 5U
#define GPIOB_PIN6 6U
#define GPIOB_PIN7 7U
#define GPIOB_PIN8 8U
#define GPIOB_PIN9 9U
#define GPIOB_PIN10 10U
#define GPIOB_PIN11 11U
#define GPIOB_PIN12 12U
#define GPIOB_PIN13 13U
#define GPIOB_PIN14 14U
#define GPIOB_PIN15 15U

#define GPIOC_PIN0 0U
#define GPIOC_PIN1 1U
#define GPIOC_PIN2 2U
#define GPIOC_PIN3 3U
#define GPIOC_PIN4 4U
#define GPIOC_PIN5 5U
#define GPIOC_PIN6 6U
#define GPIOC_PIN7 7U
#define GPIOC_PIN8 8U
#define GPIOC_PIN9 9U
#define GPIOC_PIN10 10U
#define GPIOC_PIN11 11U
#define GPIOC_PIN12 12U
#define GPIOC_PIN13 13U
#define GPIOC_PIN14 14U
#define GPIOC_PIN15 15U

// #define GPIOD_PIN0 0U
// #define GPIOD_PIN1 1U
// #define GPIOD_PIN2 2U
#define GPIOD_PIN3 3U
#define GPIOD_PIN4 4U
#define GPIOD_PIN5 5U
#define GPIOD_PIN6 6U
#define GPIOD_PIN7 7U
#define GPIOD_PIN8 8U
#define GPIOD_PIN9 9U
#define GPIOD_PIN10 10U
#define GPIOD_PIN11 11U
// #define GPIOD_PIN12 12U
// #define GPIOD_PIN13 13U
// #define GPIOD_PIN14 14U
// #define GPIOD_PIN15 15U


/*
 * IO lines assignments.
 */
// #define LINE_L3GD20_SDI PAL_LINE(GPIOA, 7U)
// #define LINE_USB_DM PAL_LINE(GPIOA, 11U)
// #define LINE_USB_DP PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO PAL_LINE(GPIOD, 5U)
#define LINE_SWCLK PAL_LINE(GPIOD, 6U)

// #define LINE_PINB8 PAL_LINE(GPIOB, 8U)
// #define LINE_PINB9 PAL_LINE(GPIOB, 9U)

//#define LINE_CAPS_LOCK PAL_LINE(GPIOC, 8U)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the SN32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n) (0U << ((n)))
#define PIN_MODE_OUTPUT(n) (1U << ((n)))
#define PIN_MODE_PULLUP(n) (0U << ((n*2)))
#define PIN_MODE_SCHMITT_EN(n) (10U << ((n*2)))
#define PIN_MODE_SCHMITT_DIS(n) (11U << ((n*2)))

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
 * PA11 - PIN10                     (input pullup).
 * PA11 - PIN11                     (input pullup).
 * PA12 - PIN12                     (input pullup).
 * PA13 - PIN13                     (input pullup).
 * PA14 - PIN14                     (input pullup).
 * PA15 - PIN15                     (input pullup).
 */
#define VAL_GPIOA_MODE (PIN_MODE_INPUT(GPIOA_PIN0) | PIN_MODE_INPUT(GPIOA_PIN1) | PIN_MODE_INPUT(GPIOA_PIN2) | PIN_MODE_INPUT(GPIOA_PIN3) | PIN_MODE_INPUT(GPIOA_PIN4) | PIN_MODE_INPUT(GPIOA_PIN5) | PIN_MODE_INPUT(GPIOA_PIN6) | PIN_MODE_INPUT(GPIOA_PIN7) | PIN_MODE_INPUT(GPIOA_PIN8) | PIN_MODE_INPUT(GPIOA_PIN9) | PIN_MODE_INPUT(GPIOA_PIN10) | PIN_MODE_INPUT(GPIOA_PIN11) | PIN_MODE_INPUT(GPIOA_PIN12) | PIN_MODE_INPUT(GPIOA_PIN13) | PIN_MODE_INPUT(GPIOA_PIN14) | PIN_MODE_INPUT(GPIOA_PIN15))

/*
 * GPIOB setup:
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
 * PB11 - PIN11                     (input pullup).
 * PB12 - PIN12                     (input pullup).
 * PB13 - PIN13                     (input pullup).
 * PB14 - PIN14                     (input pullup).
 * PB15 - PIN15                     (input pullup).
 */
#define VAL_GPIOB_MODE (PIN_MODE_INPUT(GPIOB_PIN0) | PIN_MODE_INPUT(GPIOB_PIN1) | PIN_MODE_INPUT(GPIOB_PIN2) | PIN_MODE_INPUT(GPIOB_PIN3) | PIN_MODE_INPUT(GPIOB_PIN4) | PIN_MODE_INPUT(GPIOB_PIN5) | PIN_MODE_INPUT(GPIOB_PIN6) | PIN_MODE_OUTPUT(GPIOB_PIN7) | PIN_MODE_INPUT(GPIOB_PIN8) | PIN_MODE_INPUT(GPIOB_PIN9) | PIN_MODE_INPUT(GPIOB_PIN10) | PIN_MODE_INPUT(GPIOB_PIN11) | PIN_MODE_INPUT(GPIOB_PIN12) | PIN_MODE_INPUT(GPIOB_PIN13) | PIN_MODE_INPUT(GPIOB_PIN14) | PIN_MODE_INPUT(GPIOB_PIN15))
/*
 * GPIOC setup:
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
#define VAL_GPIOC_MODE (PIN_MODE_INPUT(GPIOC_PIN0) | PIN_MODE_INPUT(GPIOC_PIN1) | PIN_MODE_INPUT(GPIOC_PIN2) | PIN_MODE_INPUT(GPIOC_PIN3) | PIN_MODE_INPUT(GPIOC_PIN4) | PIN_MODE_INPUT(GPIOC_PIN5) | PIN_MODE_INPUT(GPIOC_PIN6) | PIN_MODE_INPUT(GPIOC_PIN7) | PIN_MODE_INPUT(GPIOC_PIN8) | PIN_MODE_INPUT(GPIOC_PIN9) | PIN_MODE_INPUT(GPIOC_PIN10) | PIN_MODE_INPUT(GPIOC_PIN11) | PIN_MODE_INPUT(GPIOC_PIN12) | PIN_MODE_INPUT(GPIOC_PIN13) | PIN_MODE_INPUT(GPIOC_PIN14) | PIN_MODE_INPUT(GPIOC_PIN15))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (input pullup).
 * PD1  - PIN1                      (input pullup).
 * PD2  - PIN2                      (input pullup).
 * PD3  - PIN3                      (input pullup).
 * PD4  - PIN4                      (input pullup).
 * PD5  - PIN5                      (input pullup).
 * PD6  - PIN6                      (input pullup).
 * PD7  - PIN7                      (input pullup).
 * PD8  - PIN8                      (input pullup).
 * PD9  - PIN9                      (input pullup).
 * PD11 - PIN10                     (input pullup).
 * PD11 - PIN11                     (input pullup).
 * PD12 - PIN12                     (input pullup).
 * PD13 - PIN13                     (input pullup).
 * PD14 - PIN14                     (input pullup).
 * PD15 - PIN15                     (input pullup).
 */
#define VAL_GPIOD_MODE (PIN_MODE_INPUT(GPIOD_PIN3) | PIN_MODE_INPUT(GPIOD_PIN4) | PIN_MODE_INPUT(GPIOD_PIN5) | PIN_MODE_INPUT(GPIOD_PIN6) | PIN_MODE_INPUT(GPIOD_PIN7) | PIN_MODE_INPUT(GPIOD_PIN8) | PIN_MODE_INPUT(GPIOD_PIN9) | PIN_MODE_INPUT(GPIOD_PIN10) | PIN_MODE_INPUT(GPIOD_PIN11))

#if !defined(_FROM_ASM_)
#    ifdef __cplusplus
extern "C" {
#    endif
void boardInit(void);
#    ifdef __cplusplus
}
#    endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
