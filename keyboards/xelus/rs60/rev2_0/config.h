/* Copyright 2022 Harrison Chan (Xelus)
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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { B15, B14, B12, B1, B0 }
#define MATRIX_COL_PINS { B13, A7, A6, A5, A4, A3, A2, B7, B6, B5, B4, B3, A15, A14 }

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE

// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

//Indicator
#define LED_CAPS_LOCK_PIN A1

// I2C config
#define I2C1_SCL_PIN        B8
#define I2C1_SDA_PIN        B9
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_CLOCK_SPEED    400000
#define I2C1_DUTY_CYCLE     FAST_DUTY_CYCLE_2

// EEPROM config
// 24LC32
#define EXTERNAL_EEPROM_BYTE_COUNT 4096
#define EXTERNAL_EEPROM_PAGE_SIZE 32
#define EXTERNAL_EEPROM_ADDRESS_SIZE 2
#define EXTERNAL_EEPROM_WRITE_TIME 5

// More EEPROM for layers
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 4095

// Hardware Defines
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

// HSE CLK
#define STM32_HSECLK 16000000

//Force NKRO
#define FORCE_NKRO
