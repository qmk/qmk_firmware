/* Copyright 2020 Jumail Mundekkat / MxBlue
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

#include "quantum.h"
#include "quantum_keycodes.h"
#include "via.h"

// RGBLED index for front LEDs
#define RGBLIGHT_FLED1 14
#define RGBLIGHT_FLED2 15

// Brightness increase step for front LEDs
#define FLED_VAL_STEP 8

// Front LED settings
#define EEPROM_FRONTLED_ADDR ((uint8_t*) VIA_EEPROM_CUSTOM_CONFIG_ADDR)

// Modes for front LEDs
#define FLED_OFF    0b00
#define FLED_INDI   0b01
#define FLED_RGB    0b10
#define FLED_UNDEF  0b11

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
    uint8_t hue;
    uint8_t sat;
} hs_set;

// Custom keycodes for front LED control
enum fled_keycodes {
    FLED_MOD = USER00, // USER00 = VIA custom keycode start
    FLED_VAI,
    FLED_VAD,
    NEW_SAFE_RANGE // define a new safe range
};

void fled_init(void);                // Run init functions for front LEDs
void process_record_fled(uint16_t, keyrecord_t*); // Process keycodes for front LEDs
void fled_update_conf(void);        // Store current front LED config to EEPROM

void fled_mode_cycle(void);         // Cycle between the 3 modes for the front LEDs
void fled_val_increase(void);       // Increase the brightness of the front LEDs
void fled_val_decrease(void);       // Decrease the brightness of the front LEDs

void fled_layer_update(uint32_t);   // Process layer update for front LEDs
void fled_lock_update(uint8_t);     // Process lock update for front LEDs

void set_fled_layer_color(uint8_t, hs_set); // Set color for a given layer
void set_fled_caps_color(hs_set hs);        // Set color for the capslock indicator
hs_set get_fled_caps_color(void);           // Get color for the capslock indicator
hs_set get_fled_layer_color(uint8_t);       // Get color for a given layer

#endif //MXSS_FRONTLED_H
