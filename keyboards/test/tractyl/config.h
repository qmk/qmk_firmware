 /* Copyright 2020 Imam Rafii 
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
#include "config_common.h"

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define MATRIX_COL_PINS \
	{ A15, B3, B4, A2, A3, B8 }
#define MATRIX_ROW_PINS \
    { B12, B13, B14, B15, A8, A10 }
#define UNUSED_PINS \
    { }

#define DIODE_DIRECTION     COL2ROW

//#define USB_SUSPEND_WAKEUP_DELAY 5000

#define SPI_DRIVER                           SPID1
#define SPI_SCK_PIN                          A5
#define SPI_SCK_PAL_MODE                     5
#define SPI_MOSI_PIN                         A7
#define SPI_MOSI_PAL_MODE                    5
#define SPI_MISO_PIN                         A6
#define SPI_MISO_PAL_MODE                    5

/* Trackball */
#define PMW3360_CS_PIN                       A4
#define PMW3360_SPI_MODE                     3
#define PMW3360_SPI_DIVISOR                  64
#define PMW3360_FIRMWARE_UPLOAD_FAST
#define PMW3360_LIFTOFF_DISTANCE 0x02
//#define PMW3360_CLOCK_SPEED 2000000
//#define POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y
//#define ROTATIONAL_TRANSFORM_ANGLE  90

/* Encoder */
#define ENCODERS_PAD_A {A13}
#define ENCODERS_PAD_B {A14}
#define ENCODER_RESOLUTION 4

/* Split configuration */
#define SPLIT_HAND_PIN C14 //high = left, low = right
#define SPLIT_USB_DETECT
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10
#define POINTING_DEVICE_TASK_THROTTLE_MS 1
#define SPLIT_TRANSACTION_IDS_KB RPC_ID_KB_CONFIG_SYNC

/* serial.c configuration for split keyboard */
#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN      B6 //Left Tx goes to Right Rx
#define SERIAL_USART_RX_PIN      B7
#define SERIAL_USART_DRIVER      SD1 
#define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT     100  // USART driver timeout. default 100
#define SERIAL_USART_SPEED       921600
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* RGBLight configuration */
#define RGB_DI_PIN A1
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM          18
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT \
    { 9, 9 }
#define DEBUG_LED_PIN      C13

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x3536
#define DEVICE_VER 0x0001

#define MANUFACTURER "Me"
#define PRODUCT Tractyl Manuform

#define MATRIX_ROWS 12
#define MATRIX_COLS 6
#define DIODE_DIRECTION COL2ROW

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

/* #define AUTO_SHIFT_TIMEOUT 200
#define PERMISSIVE_HOLD */


