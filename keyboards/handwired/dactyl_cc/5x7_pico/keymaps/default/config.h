/*
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

#define MASTER_LEFT
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2500
#define SPLIT_TRANSPORT_MIRROR
#define SERIAL_USART_FULL_DUPLEX     // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN  GP8  // USART TX pin
#define SERIAL_USART_RX_PIN  GP9  // USART RX pin
#define RGBLIGHT_LED_COUNT 66
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 33, 33 }

// PMW3389 Settings
#define PMW33XX_LIFTOFF_DISTANCE 0x02
#define POINTING_DEVICE_RIGHT
#define SPI_SCK_PIN GP2
#define SPI_MISO_PIN GP4
#define SPI_MOSI_PIN GP3
#define PMW33XX_CS_PIN GP5
#define POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_TASK_THROTTLE_MS 1
#define SPLIT_POINTING_ENABLE
//#define SPI_DRIVER SPI0
//#define MASTER_RIGHT

//#define EE_HANDS

//#define RGBLIGHT_SPLIT
//#define RGBLIGHT_DEFAULT_ON

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_HUE_STEP 6 // number of steps to cycle through the hue by
#    define RGBLIGHT_SAT_STEP 6 // number of steps to increment the saturation by
#    define RGBLIGHT_VAL_STEP 6 // number of steps to increment the brightness by
#    define RGBLIGHT_SLEEP      //  the RGB lighting will be switched off when the host goes to sleep

#endif
