/* Copyright 2020 Ilya Zhuravlev
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

#include <inttypes.h>
#include <stdbool.h>

#include "dynamic_keymap_eeprom.h"
#include "action.h"

#define VIAL_PROTOCOL_VERSION ((uint32_t)0x00000004)
#define VIAL_RAW_EPSIZE 32

void vial_init(void);
void vial_handle_cmd(uint8_t *data, uint8_t length);
bool process_record_vial(uint16_t keycode, keyrecord_t *record);

#ifdef VIAL_ENCODERS_ENABLE
bool vial_encoder_update(uint8_t index, bool clockwise);
#endif

extern int vial_unlocked;
extern int vial_unlock_in_progress;

enum {
    vial_get_keyboard_id = 0x00,
    vial_get_size = 0x01,
    vial_get_def = 0x02,
    vial_get_encoder = 0x03,
    vial_set_encoder = 0x04,
    vial_get_unlock_status = 0x05,
    vial_unlock_start = 0x06,
    vial_unlock_poll = 0x07,
    vial_lock = 0x08,
    vial_qmk_settings_query = 0x09,
    vial_qmk_settings_get = 0x0A,
    vial_qmk_settings_set = 0x0B,
    vial_qmk_settings_reset = 0x0C,
    vial_dynamic_entry_op = 0x0D,  /* operate on tapdance, combos, etc */
};

enum {
    dynamic_vial_get_number_of_entries = 0x00,
    dynamic_vial_tap_dance_get = 0x01,
    dynamic_vial_tap_dance_set = 0x02,
    dynamic_vial_combo_get = 0x03,
    dynamic_vial_combo_set = 0x04,
};

/* Fake position in keyboard matrix, can't use 255 as that is immediately rejected by IS_NOEVENT
   used to send arbitrary keycodes thru process_record_quantum_helper */
#define VIAL_MATRIX_MAGIC 254

#ifdef TAP_DANCE_ENABLE

#define VIAL_TAP_DANCE_ENABLE

#ifndef VIAL_TAP_DANCE_ENTRIES
    #if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 4000
        #define VIAL_TAP_DANCE_ENTRIES 32
    #elif DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 2000
        #define VIAL_TAP_DANCE_ENTRIES 16
    #elif DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 1000
        #define VIAL_TAP_DANCE_ENTRIES 8
    #else
        #define VIAL_TAP_DANCE_ENTRIES 4
    #endif
#endif

typedef struct {
    uint16_t on_tap;
    uint16_t on_hold;
    uint16_t on_double_tap;
    uint16_t on_tap_hold;
    uint16_t custom_tapping_term;
} vial_tap_dance_entry_t;
_Static_assert(sizeof(vial_tap_dance_entry_t) == 10, "Unexpected size of the vial_tap_dance_entry_t structure");

#else
#undef VIAL_TAP_DANCE_ENTRIES
#define VIAL_TAP_DANCE_ENTRIES 0
#endif

#ifdef COMBO_ENABLE
#define VIAL_COMBO_ENABLE

#ifndef VIAL_COMBO_ENTRIES
    #if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 4000
        #define VIAL_COMBO_ENTRIES 32
    #elif DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 2000
        #define VIAL_COMBO_ENTRIES 16
    #elif DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 1000
        #define VIAL_COMBO_ENTRIES 8
    #else
        #define VIAL_COMBO_ENTRIES 4
    #endif
#endif

typedef struct {
    uint16_t input[4];
    uint16_t output;
} vial_combo_entry_t;
_Static_assert(sizeof(vial_combo_entry_t) == 10, "Unexpected size of the vial_combo_entry_t structure");

/* also to catch wrong include order in e.g. process_combo.h */
#ifdef COMBO_COUNT
#error COMBO_COUNT redefined - define VIAL_COMBO_ENTRIES instead
#endif

#define COMBO_COUNT VIAL_COMBO_ENTRIES

#else
#undef VIAL_COMBO_ENTRIES
#define VIAL_COMBO_ENTRIES 0
#endif
