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

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// I2C setup
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 7U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH   45U
#define I2C1_TIMINGR_SCLL   149U

// I2C EEPROM
#define EEPROM_I2C_24LC64

// More EEPROM for layers
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191

// RGBLIGHT
#define RGBLIGHT_LAYERS
#define WS2812_EXTERNAL_PULLUP
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

// Bitbang WS2812
#define NOP_FUDGE 0.4
