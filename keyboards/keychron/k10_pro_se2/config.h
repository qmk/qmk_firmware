/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#define MAC_LOCK_SCREEN_ENABLE
#define WIN_LOCK_SCREEN_ENABLE

#ifdef LK_WIRELESS_ENABLE
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#    define SPI_DRIVER SPID1

/* Hardware configuration */
#    define P2P4_MODE_SELECT_PIN A9
// #    define USB_MODE_SELECT_PIN A9
#    define BT_MODE_SELECT_PIN A10

#    define LKBT51_RESET_PIN C4
#    define LKBT51_INT_INPUT_PIN B1
#    define BLUETOOTH_INT_OUTPUT_PIN A4

#    define USB_POWER_SENSE_PIN B0
#    define USB_POWER_CONNECTED_LEVEL 0

#    define BAT_CHARGING_PIN B13
#    define BAT_CHARGING_LEVEL 0

#    define BAT_LOW_LED_PIN C5
#    define BAT_LOW_LED_PIN_ON_STATE 1

#    define COMMON_BT_LED_PIN B15
#    define COMMON_P24G_LED_PIN B14
#    define COMMON_BT_LED_PIN_ON_STATE 0

/* Keep USB connection in blueooth mode */
#    define KEEP_USB_CONNECTION_IN_WIRELESS_MODE

/* Enable bluetooth NKRO */
#    define WIRELESS_NKRO_ENABLE
#endif

#define MATRIX_IO_DELAY 10
