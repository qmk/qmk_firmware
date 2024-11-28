/* Copyright 2023 ~ 2024 @ Lemokey (https://www.lemokey.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3
#define ENCODER_MAP_KEY_DELAY 2

#if defined(RGB_MATRIX_ENABLE) || defined(LK_WIRELESS_ENABLE)
/* SPI configuration */
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#endif

#if defined(RGB_MATRIX_ENABLE)
#    define DRIVER_COUNT 2
#    define DRIVER_CS_PINS \
        { B8, B9 }
#    define LED_DRIVER_SHUTDOWN_PIN B7
#    define SNLED23751_SPI_DIVISOR 16
#endif

#ifdef LK_WIRELESS_ENABLE
/* Hardware configuration */
#    define P2P4_MODE_SELECT_PIN A10
#    define BT_MODE_SELECT_PIN A9

#    define LKBT51_RESET_PIN C4
#    define LKBT51_INT_INPUT_PIN B1
#    define BLUETOOTH_INT_OUTPUT_PIN A4

#    define USB_POWER_SENSE_PIN B0
#    define USB_POWER_CONNECTED_LEVEL 0

#    define BAT_LOW_LED_PIN B12
#    define BAT_LOW_LED_PIN_ON_STATE 1

#    define BT_HOST_DEVICES_COUNT 3

#    define BT_INDICATION_LED_PIN_LIST \
        { C9, C9, C9 }
#    define BT_INDICATION_LED_ON_STATE 0

#    define P24G_INDICATION_LED_PIN A8

#    if defined(RGB_MATRIX_ENABLE) || defined(LED_MATRIX_ENABLE)

#        define BT_INDICATION_LED_LIST \
            { 17, 18, 19 }

#        define P24G_INDICATION_LED_INDEX 20

#        define BAT_LEVEL_LED_LIST \
            { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 }

/* Backlit disable timeout when keyboard is disconnected(unit: second) */
#        define DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT 40

/* Backlit disable timeout when keyboard is connected(unit: second) */
#        define CONNECTED_BACKLIGHT_DISABLE_TIMEOUT 600

/* Reinit LED driver on tranport changed */
#        define REINIT_LED_DRIVER 1

#    endif

/* Keep USB connection in blueooth mode */
#    define KEEP_USB_CONNECTION_IN_WIRELESS_MODE

/* Enable bluetooth NKRO */
#    define WIRELESS_NKRO_ENABLE
#endif

/* Factory test keys */
#define FN_KEY_1 MO(1)

#define MATRIX_IO_DELAY 10
