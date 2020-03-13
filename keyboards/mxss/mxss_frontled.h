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

#pragma once

#include "quantum.h"
#include "quantum_keycodes.h"
#include "via.h"

// RGBLED index for front LEDs
#define RGBLIGHT_FLED1 14
#define RGBLIGHT_FLED2 15

// Brightness increase step for front LEDs
#define FLED_VAL_STEP 8

// Front LED settings
#define FRONTLED_CONF_ADDR ((uint8_t*) VIA_EEPROM_CUSTOM_CONFIG_ADDR)
#define FRONTLED_COLOR_CNT_ADDR (FRONTLED_CONF_ADDR + 1)
#define FRONTLED_COLOR_ADDR ((uint16_t*)(FRONTLED_COLOR_CNT_ADDR + 1))

// No point persisting more 4, VIA only allows editing of 3 + 1 for caps
#define FRONTLED_COLOR_MAXCNT 4

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
typedef union {
    uint16_t raw;
    struct {
        uint8_t hue;
        uint8_t sat;
    };
} hs_set;

// Custom keycodes for front LED control
enum fled_keycodes {
    FLED_MOD = USER00, // USER00 = VIA custom keycode start
    FLED_VAI,
    FLED_VAD,
    NEW_SAFE_RANGE // define a new safe range
};

void fled_init(void);                // Run init functions for front LEDs
void process_record_fled(uint16_t keycode, keyrecord_t* record); // Process keycodes for front LEDs
void fled_load_conf(void);          // Load front LED config from EEPROM
void fled_update_conf(void);        // Store current front LED config to EEPROM

void fled_mode_cycle(void);         // Cycle between the 3 modes for the front LEDs
void fled_val_increase(void);       // Increase the brightness of the front LEDs
void fled_val_decrease(void);       // Decrease the brightness of the front LEDs

void fled_layer_update(layer_state_t state);   // Process layer update for front LEDs
void fled_lock_update(led_t led_state);     // Process lock update for front LEDs

void set_fled_layer_color(uint8_t layer, hs_set hs); // Set color for a given layer
void set_fled_caps_color(hs_set hs);        // Set color for the capslock indicator
hs_set get_fled_caps_color(void);           // Get color for the capslock indicator
hs_set get_fled_layer_color(uint8_t layer);       // Get color for a given layer
