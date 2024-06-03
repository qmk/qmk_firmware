/* Copyright 2021 Jessica Sullivan and Don Kjer
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


#define WAIT_US_TIMER           GPTD3

// Dynamic EEPROM
// Something sensible or else VIA may crash
// Users may enable more if they wish
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  4095

// Increase VIA layer count
#define DYNAMIC_KEYMAP_LAYER_COUNT 16

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/* LED indicator pins */
#define LED_WIN_LOCK_PIN    C5
#define LED_MR_LOCK_PIN     LED_SCROLL_LOCK_PIN

#define IS31FL3733_I2C_ADDRESS_1 IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2 IS31FL3733_I2C_ADDRESS_GND_VCC

/* I2C Alternate function settings */
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

/* Set I2C speed to 400kHz, 300ns Tr, 14ns Tf */
#define I2C1_TIMINGR_PRESC   0x1U
#define I2C1_TIMINGR_SCLDEL  0x9U
#define I2C1_TIMINGR_SDADEL  0x0U
#define I2C1_TIMINGR_SCLH   0x0cU
#define I2C1_TIMINGR_SCLL   0x22U
