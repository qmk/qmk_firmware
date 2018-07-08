/* Copyright 2018 Jumail Mundekkat / MxBlue
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

// EEPROM management code taken from Wilba6582
// https://github.com/Wilba6582/qmk_firmware/blob/zeal60/keyboards/zeal60/zeal_eeprom.h
 
#ifndef MXSS_FRONTLED_H
#define MXSS_FRONTLED_H

#include "quantum_keycodes.h"

// RGBLED index for front LEDs
#define RGBLIGHT_FLED1 14
#define RGBLIGHT_FLED2 15

// Brightness increase step for front LEDs
#define FLED_VAL_STEP 8

// QMK never uses more then 32bytes of EEPROM, so our region starts there
// Magic value to verify the state of the EEPROM
#define EEPROM_MAGIC 0xC3E7
#define EEPROM_MAGIC_ADDR ((void*)32)

// Front LED settings
#define EEPROM_FRONTLED_ADDR ((void*)34)

// Modes for front LEDs
#define FLED_OFF    0b00
#define FLED_INDI   0b01
#define FLED_RGB    0b10
#define FLED_UNDEF  0b11

// Hard-coded color for capslock indicator in FLED_INDI mode, H:0% S:100% = Red
#define FLED_CAPS_H 0
#define FLED_CAPS_S 255

// Config storage format for EEPROM
typedef union {
  uint8_t raw;
  struct {
    uint8_t  mode    :2;
    uint8_t  val     :6;
  };
} fled_config;

// Structure to store hue and saturation values
typedef struct _hs_set {
    uint16_t hue; 
    uint8_t sat;
} hs_set;

// Custom keycodes for front LED control
enum fled_keycodes {
  FLED_MOD = SAFE_RANGE,
  FLED_VAI,
  FLED_VAD,
  NEW_SAFE_RANGE // define a new safe range
};

bool eeprom_is_valid(void);         // Check if EEPROM has been set up
void eeprom_set_valid(bool valid);  // Change validity state of EEPROM
void eeprom_update_conf(void);      // Store current front LED config to EEPROM

void fled_mode_cycle(void);         // Cycle between the 3 modes for the front LEDs
void fled_val_increase(void);       // Increase the brightness of the front LEDs
void fled_val_decrease(void);       // Decrease the brightness of the front LEDs

#endif //MXSS_FRONTLED_H