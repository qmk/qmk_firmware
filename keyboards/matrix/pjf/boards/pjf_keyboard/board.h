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
 * Board identifier.
 */
#define BOARD_PJF_STM32_F103XB
#define BOARD_NAME              "stm32 based pjf"

/*
 * Board frequencies.
 */
//#define STM32_LSECLK            32768
#define STM32_HSECLK            8000000
//#define STM32_HSE_BYPASS

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F103xB

/*
 * IO pins assignments.
 */

/*
 * MCU voltage
 */
//#define STM32_VDD 300
/*
 * IO pins assignments.
 */
#define GPIOA_PIN0        0U
#define GPIOA_PIN1        1U
#define GPIOA_PIN2        2U
#define GPIOA_PIN3        3U
#define GPIOA_PIN4        4U
#define GPIOA_PIN5        5U
#define GPIOA_PIN6        6U
#define GPIOA_PIN7        7U
#define GPIOA_PIN8        8U
#define GPIOA_USART1_TX   9U
#define GPIOA_USART1_RX   10U
#define GPIOA_USB_DM      11U
#define GPIOA_USB_DP      12U
#define GPIOA_TMS         13U
#define GPIOA_TCK         14U
#define GPIOA_TDI         15U

#define GPIOB_PIN0        0U
#define GPIOB_PIN1        1U
#define GPIOB_PIN2        2U
#define GPIOB_TDO         3U
#define GPIOB_NTRST       4U
#define GPIOB_PIN5        5U
#define GPIOB_PIN6        6U
#define GPIOB_PIN7        7U
#define GPIOB_PIN8        8U
#define GPIOB_PIN9        9U
#define GPIOB_PIN10       10U
#define GPIOB_PIN11       11U
#define GPIOB_PIN12       12U
#define GPIOB_PIN13       13U
#define GPIOB_PIN14       14U
#define GPIOB_PIN15       15U

#define GPIOC_PIN0        0U
#define GPIOC_PIN1        1U
#define GPIOC_PIN2        2U
#define GPIOC_PIN3        3U
#define GPIOC_PIN4        4U
#define GPIOC_PIN5        5U
#define GPIOC_PIN6        6U
#define GPIOC_PIN7        7U
#define GPIOC_PIN8        8U
#define GPIOC_PIN9        9U
#define GPIOC_PIN10       10U
#define GPIOC_PIN11       11U
#define GPIOC_PIN12       12U
#define GPIOC_PIN13       13U
#define GPIOC_PIN14       14U
#define GPIOC_PIN15       15U

#define GPIOD_PIN0       0U
#define GPIOD_PIN1       1U
#define GPIOD_PIN2       2U
#define GPIOD_PIN3       3U
#define GPIOD_PIN4       4U
#define GPIOD_PIN5       5U
#define GPIOD_PIN6       6U
#define GPIOD_PIN7       7U
#define GPIOD_PIN8       8U
#define GPIOD_PIN9       9U
#define GPIOD_PIN10      10U
#define GPIOD_PIN11      11U
#define GPIOD_PIN12      12U
#define GPIOD_PIN13      13U
#define GPIOD_PIN14      14U
#define GPIOD_PIN15      15U

#define GPIOE_PIN0       0U
#define GPIOE_PIN1       1U
#define GPIOE_PIN2       2U
#define GPIOE_PIN3       3U
#define GPIOE_PIN4       4U
#define GPIOE_PIN5       5U
#define GPIOE_PIN6       6U
#define GPIOE_PIN7       7U
#define GPIOE_PIN8       8U
#define GPIOE_PIN9       9U
#define GPIOE_PIN10      10U
#define GPIOE_PIN11      11U
#define GPIOE_PIN12      12U
#define GPIOE_PIN13      13U
#define GPIOE_PIN14      14U
#define GPIOE_PIN15      15U

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */
/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define CRL_INPUT(n)             (0U << ((n) * 4U))
#define CRL_OUTPUT_LOW(n)        (2U << ((n) * 4U))
#define CRL_OUTPUT_MEDIUM(n)     (1U << ((n) * 4U))
#define CRL_OUTPUT_HIGH(n)       (3U << ((n) * 4U))
#define CRL_INPUT_ANOLOG(n)      (0U << (((n) * 4U + 2)))
#define CRL_INPUT_FLOATING(n)    (1U << (((n) * 4U + 2)))
#define CRL_INPUT_PULLUPDOWN(n)  (2U << (((n) * 4U + 2)))
#define CRL_OUTPUT_PUSHPULL(n)   (0U << (((n) * 4U + 2)))
#define CRL_OUTPUT_OPENDRAIN(n)  (1U << (((n) * 4U + 2)))
#define CRL_AF_PUSHPULL(n)       (2U << (((n) * 4U + 2)))
#define CRL_AF_OPENDRAIN(n)      (3U << (((n) * 4U + 2)))

#define CRH_INPUT(n)             CRL_INPUT((n-8))
#define CRH_OUTPUT_LOW(n)        CRL_OUTPUT_LOW((n-8))
#define CRH_OUTPUT_MEDIUM(n)     CRL_OUTPUT_MEDIUM((n-8))
#define CRH_OUTPUT_HIGH(n)       CRL_OUTPUT_HIGH((n-8))
#define CRH_INPUT_ANOLOG(n)      CRL_INPUT_ANOLOG((n-8))
#define CRH_INPUT_FLOATING(n)    CRL_INPUT_FLOATING((n-8))
#define CRH_INPUT_PULLUPDOWN(n)  CRL_INPUT_PULLUPDOWN((n-8))
#define CRH_OUTPUT_PUSHPULL(n)   CRL_OUTPUT_PUSHPULL((n-8))
#define CRH_OUTPUT_OPENDRAIN(n)  CRL_OUTPUT_OPENDRAIN((n-8))
#define CRH_AF_PUSHPULL(n)       CRL_AF_PUSHPULL((n-8))
#define CRH_AF_OPENDRAIN(n)      CRL_AF_OPENDRAIN((n-8))

#define ODR_INPUT_PULLDOWN(n)     (0U << (n))
#define ODR_INPUT_PULLUP(n)       (1U << (n))

/*
 * Port A setup.
 * Everything input with pull-up except:
 * PA9 - Alternate output           (USART1 TX)
 * PA10 - Alternate output          (USART1 RX)
 * PA11 - Alternate output          (USB DM)
 * PA12 - Alternate output          (USB DP)
 * PA13 - Pull-up input             (TMS)
 * PA14 - Pull-down input           (TCK)
 * PA15 - Pull-up input             (TDI)
 */
/* PA7...PA0 */
#define VAL_GPIOA_CRL           0x88887888
                                /*(CRL_INPUT(GPIOA_PIN0)|CRL_INPUT_PULLUPDOWN(GPIOA_PIN0) \
                                |CRL_INPUT(GPIOA_PIN1)|CRL_INPUT_PULLUPDOWN(GPIOA_PIN1) \
                                |CRL_OUTPUT_HIGH(GPIOA_LED_PWM)|CRL_ALT_PUSHPULL(GPIOA_LED_PWM) \
                                |CRL_OUTPUT_HIGH(GPIOA_RGB_PWM)|CRL_ALT_PUSHPULL(GPIOA_RGB_PWM) \
                                |CRL_INPUT(GPIOA_PIN4)|CRL_INPUT_PULLUPDOWN(GPIOA_PIN4) \
                                |CRL_INPUT(GPIOA_PIN5)|CRL_INPUT_PULLUPDOWN(GPIOA_PIN5) \
                                |CRL_INPUT(GPIOA_PIN6)|CRL_INPUT_PULLUPDOWN(GPIOA_PIN6) \
                                |CRL_INPUT(GPIOA_PIN7)|CRL_INPUT_PULLUPDOWN(GPIOA_PIN7))
                                */
/* PA15...PA8 */
#define VAL_GPIOA_CRH           0x88888888
                                /*(CRH_INPUT(GPIOA_PIN8)|CRH_INPUT_PULLUPDOWN(GPIOA_PIN8) \
                                |CRH_OUTPUT_HIGH(GPIOA_USART1_TX)|CRH_ALT_PUSHPULL(GPIOA_USART1_TX) \
                                |CRH_INPUT(GPIOA_USART1_RX)|CRH_INPUT_FLOATING(GPIOA_USART1_RX) \
                                |CRH_OUTPUT_HIGH(GPIOA_USB_DM)|CRH_ALT_OPENDRAIN(GPIOA_USB_DM) \
                                |CRH_OUTPUT_HIGH(GPIOA_USB_DP)|CRH_ALT_OPENDRAIN(GPIOA_USB_DP) \
                                |CRH_INPUT(GPIOA_TMS)|CRH_INPUT_PULLUPDOWN(GPIOA_TMS) \
                                |CRH_INPUT(GPIOA_TCK)|CRH_INPUT_PULLUPDOWN(GPIOA_TCK) \
                                |CRH_INPUT(GPIOA_TDI)|CRH_INPUT_PULLUPDOWN(GPIOA_TDI))
                                */

#define VAL_GPIOA_ODR           0xFFFFFFFF//(ODR_INPUT_PULLUP(GPIOA_TMS)|ODR_INPUT_PULLDOWN(GPIOA_TCK)|ODR_INPUT_PULLUP(GPIOA_TDI))

/*
 * Port B setup.
 * Everything input with pull-up except:
 * PB3 - Pull-up input             (TDO)
 * PB4 - Pull-up input             (nTRST)
 * PB8 - Pushpull output           (LOGO RGB)
 * PB9 - Pull-up input             (SET0)
 * PB13 - Pushpull output          (INDICATE LED 1)
 * PB14 - Pushpull output          (INDICATE LED 1)
 * PB15 - Pushpull output          (INDICATE LED 1)
 */

/* PB7...PB0 */
#define VAL_GPIOB_CRL           0x88888888
                                /*(CRL_INPUT(GPIOB_PIN0)|CRL_INPUT_PULLUPDOWN(GPIOB_PIN0) \
                                |CRL_INPUT(GPIOB_PIN1)|CRL_INPUT_PULLUPDOWN(GPIOB_PIN1) \
                                |CRL_INPUT(GPIOB_PIN2)|CRL_INPUT_PULLUPDOWN(GPIOB_PIN2) \
                                |CRL_INPUT(GPIOB_TDO)|CRL_INPUT_PULLUPDOWN(GPIOB_TDO) \
                                |CRL_INPUT(GPIOB_NTRST)|CRL_INPUT_PULLUPDOWN(GPIOB_NTRST) \
                                |CRL_INPUT(GPIOB_PIN5)|CRL_INPUT_PULLUPDOWN(GPIOB_PIN5) \
                                |CRL_INPUT(GPIOB_PIN6)|CRL_INPUT_PULLUPDOWN(GPIOB_PIN6) \
                                |CRL_INPUT(GPIOB_PIN7)|CRL_INPUT_PULLUPDOWN(GPIOB_PIN7))
                                */
/* PB15...PB8 */
#define VAL_GPIOB_CRH           0x88888887
                                /*(CRH_OUTPUT_HIGH(GPIOB_LOGO_RGB)|CRH_OUTPUT_PUSHPULL(GPIOB_LOGO_RGB) \
                                |CRH_INPUT(GPIOB_SET0)|CRH_INPUT_PULLUPDOWN(GPIOB_SET0) \
                                |CRH_INPUT(GPIOB_PIN10)|CRH_INPUT_PULLUPDOWN(GPIOB_PIN10) \
                                |CRH_INPUT(GPIOB_PIN11)|CRH_INPUT_PULLUPDOWN(GPIOB_PIN11) \
                                |CRH_INPUT(GPIOB_PIN12)|CRH_INPUT_PULLUPDOWN(GPIOB_PIN12) \
                                |CRH_OUTPUT_LOW(GPIOB_ILED_1)|CRH_OUTPUT_PUSHPULL(GPIOB_ILED_1) \
                                |CRH_OUTPUT_LOW(GPIOB_ILED_2)|CRH_OUTPUT_PUSHPULL(GPIOB_ILED_2) \
                                |CRH_OUTPUT_LOW(GPIOB_ILED_3)|CRH_OUTPUT_PUSHPULL(GPIOB_ILED_3))
                                */

#define VAL_GPIOB_ODR           0xFFFFFFFF//(ODR_INPUT_PULLUP(GPIOB_TDO)|ODR_INPUT_PULLUP(GPIOB_NTRST)|ODR_INPUT_PULLUP(GPIOB_SET0))
/*
 * Port C setup.
 * Everything input with pull-up except:
 * PC0 - ADC input                  (JOYSTICK VR1)
 * PC1 - ADC input                  (JOYSTICK VR2)
 * PC5 - Pull-up input              (JOYSTICK SWITCH)
 */

/* PC7...PC0 */
#define VAL_GPIOC_CRL           0x88888888
                                /*(CRL_INPUT(GPIOC_JS_VR1)|CRL_INPUT_ANOLOG(GPIOC_JS_VR1) \
                                |CRL_INPUT(GPIOC_JS_VR2)|CRL_INPUT_ANOLOG(GPIOC_JS_VR2) \
                                |CRL_INPUT(GPIOC_PIN3)|CRL_INPUT_PULLUPDOWN(GPIOC_PIN3) \
                                |CRL_INPUT(GPIOC_PIN4)|CRL_INPUT_PULLUPDOWN(GPIOC_PIN4) \
                                |CRL_INPUT(GPIOC_JS_SW)|CRL_INPUT_PULLUPDOWN(GPIOC_JS_SW) \
                                |CRL_INPUT(GPIOC_PIN6)|CRL_INPUT_PULLUPDOWN(GPIOC_PIN6) \
                                |CRL_INPUT(GPIOC_PIN7)|CRL_INPUT_PULLUPDOWN(GPIOC_PIN7))
                                */
/* PC15...PC8 */
#define VAL_GPIOC_CRH           0x88888888

#define VAL_GPIOC_ODR           0xFFFFFFFF//(ODR_INPUT_PULLUP(GPIOC_JS_SW))

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0 - Floating input             (HSE OSC in)
 * PD1 - Floating input             (HSE OSC out)
 */
/*  PD7...PD0 */
#define VAL_GPIOD_CRL            0x88888844
/* PD15...PD8 */
#define VAL_GPIOD_CRH            0x88888888

#define VAL_GPIOD_ODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 */
/*  PE7...PE0 */
#define VAL_GPIOE_CRL            0x88888888
/* PE15...PE8 */
#define VAL_GPIOE_CRH            0x88888888

#define VAL_GPIOE_ODR            0xFFFFFFFF
/*
 *
 * USB bus activation macro, required by the USB driver.
 */
// #define usb_lld_connect_bus(usbp)
#define usb_lld_connect_bus(usbp) palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL); palClearPad(GPIOA, 8)
/*
 * USB bus de-activation macro, required by the USB driver.
 */
// #define usb_lld_disconnect_bus(usbp)
#define usb_lld_disconnect_bus(usbp) palSetPad(GPIOA, 8)

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
