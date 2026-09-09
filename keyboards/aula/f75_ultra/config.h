/* Copyright (C) 2022 Westberry Technology (ChangZhou) Corp., Ltd
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

#ifdef MULTIMODE_ENABLE
#    define MM_BT_HOST1_NAME "AULA F75 Ultra $"
#    define MM_BT_HOST2_NAME "AULA F75 Ultra $"
#    define MM_BT_HOST3_NAME "AULA F75 Ultra $"

// Indicate index of mm device
#    define MM_BLINK_HOST1_INDEX 14
#    define MM_BLINK_HOST2_INDEX 15
#    define MM_BLINK_HOST3_INDEX 16
#    define MM_BLINK_2G4_INDEX 13
#    define MM_BLINK_USB_INDEX 17

// Multi mode used pins
#    define MM_CABLE_PIN B9
#    define MM_CHARGE_PIN B8
#    define MM_BT_MODE_PIN C0
#    define MM_2G4_MODE_PIN B11

// Indicate color of mm device
#    define MM_BLINK_HOST1_COLOR RGB_BLUE // Host1 color
#    define MM_BLINK_HOST2_COLOR RGB_BLUE // Host2 color
#    define MM_BLINK_HOST3_COLOR RGB_BLUE // Host3 color
#    define MM_BLINK_2G4_COLOR RGB_CYAN   // 2.4G color
#    define MM_BLINK_USB_COLOR RGB_WHITE  // USB color

#    define BAT_LEVEL_DISPLAY_INDEX {14, 15, 16, 17, 18, 19, 20, 21, 22, 23} // Battery level indicator

#    define CHRGE_LOW_LEVEL_INDICATOR_INDEX 84
#    define CHRGE_LOW_LEVEL_INDICATOR_COLOR RGB_RED

// Other config
#    define USB_SUSPEND_CHECK_ENABLE
#    define BT_KEY_NUM 8
#    define USBLINK_Status gpio_read_pin(MM_CABLE_PIN)
#    define CHARGE_Status gpio_read_pin(MM_CHARGE_PIN)
#endif

#define LED_Q_INDEX 29
#define LED_W_INDEX 30
#define LED_E_INDEX 31
#define LED_R_INDEX 32
#define LED_LWIN_INDEX 72
#define LED_CAPS_INDEX 43

/* SPI Config for spi flash*/
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4
#define SPI_MOSI_PAL_MODE 5

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12

/* I2C Config for LED Driver */
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_GND
#define SNLED27351_I2C_ADDRESS_2 SNLED27351_I2C_ADDRESS_VDDIO

#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 1000000

// RGB Matrix Config
#define RGB_MATRIX_SHUTDOWN_PIN A15

// Encoder Config
#define ENCODER_DEFAULT_POS 0x0

/*
 * F75 Ultra VIA Edition
 *
 * Reserve the final 256 bytes of the 2048-byte logical EEPROM
 * for persistent Per-Key RGB configuration.
 *
 * 0x0000-0x06FF : QMK/VIA/dynamic keymap/macros
 * 0x0700-0x07FF : Per-Key RGB persistent storage
 */
#define F75_PER_KEY_EEPROM_ADDR 0x0700
#define F75_PER_KEY_EEPROM_SIZE 0x0100
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 1791
