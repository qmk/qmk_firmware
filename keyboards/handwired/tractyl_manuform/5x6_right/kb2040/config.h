/*
        j* Copyright 2012 Jun Wako<wakojun @gmail.com> Copyright 2015 Jack Humbert

            This program is free                                                                     software : you can redistribute it and /
    or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,
    either version 2 of the License, or (at your option) any later version.

                                         This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "pins.h"

#define PRODUCT Tractyl Manuform(5x6) RP2040

// wiring of each half
#define MATRIX_COL_PINS \
    { PIN_D10, PIN_D6, PIN_D5, PIN_D4, PIN_D3, PIN_D2 }

#define MATRIX_ROW_PINS \
    { PIN_D7, PIN_D8, PIN_A1, PIN_A2, PIN_A3, PIN_D9 }

#define MATRIX_COL_PINS_RIGHT \
    { PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7 }

#define MATRIX_ROW_PINS_RIGHT \
    { PIN_D8, PIN_D9, PIN_A2, PIN_A3, PIN_A1, NO_PIN }

#ifdef DIODE_DIRECTION
#    undef DIODE_DIRECTION
#endif // DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

// #define USB_VBUS_PIN        B10 // doesn't seem to work for me on one of my controllers... */
// #define SPLIT_HAND_PIN C14 // high = left, low = right

#define EE_HANDS

// WS2812 RGB LED strip input and number of LEDs
#define RGB_DI_PIN PIN_A0
#define WS2812_PWM_DRIVER vendor

#define RGBLED_NUM 62
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT \
    { 32, 30 }

/* serial.c configuration for split keyboard */
#define SERIAL_DEBUG
#define SERIAL_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the Serial implementation uses the PIO0 peripheral
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN PIN_TX
#define SERIAL_USART_RX_PIN PIN_RX
#define SERIAL_USART_TIMEOUT 100 // USART driver timeout. default 100
#define SERIAL_USART_SPEED 230400

#define SPLIT_USB_DETECT
#define EE_HANDS

// #define MASTER_RIGHT

/* pmw3360 config  */
#define PMW33XX_CS_PIN PIN_D10

#ifdef POINTING_DEVICE_INVERT_X
#    undef POINTING_DEVICE_INVERT_X
#endif

#define POINTING_DEVICE_ROTATION_90
