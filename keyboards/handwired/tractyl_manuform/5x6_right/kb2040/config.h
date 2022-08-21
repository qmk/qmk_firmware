/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define PRODUCT Tractyl Manuform(5x6) RP2040

// wiring of each half
#define MATRIX_COL_PINS \
    { GP0, GP1, GP2, GP3, GP4, GP5 }
#define MATRIX_ROW_PINS \
    { GP6, GP7, GP8, GP9, GP27 }

#ifdef DIODE_DIRECTION
#    undef DIODE_DIRECTION
#endif // DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

// #define USB_VBUS_PIN        B10 // doesn't seem to work for me on one of my controllers... */
// #define SPLIT_HAND_PIN C14 // high = left, low = right

// WS2812 RGB LED strip input and number of LEDs
#define RGB_DI_PIN GP26
#define WS2812_PWM_DRIVER vendor

#define RGBLED_NUM 62
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT \
    { 32, 30 }

// #define DEBUG_LED_PIN GP17

/* serial.c configuration for split keyboard */
#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP28
#define SERIAL_USART_RX_PIN GP29
#define SERIAL_USART_DRIVER SD2
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 100   // USART driver timeout. default 100
#define SERIAL_USART_SPEED 921600

/* i2c config for oleds */
/* spi config for eeprom and pmw3360 sensor */

/* eeprom config */

/* pmw3360 config  */
#define PMW33XX_CS_PIN GP10

#ifdef POINTING_DEVICE_INVERT_X
#    undef POINTING_DEVICE_INVERT_X
#endif

#define POINTING_DEVICE_INVERT_Y
