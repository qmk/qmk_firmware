/* Copyright 2016 Jack Humbert
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

#include "action.h"
#include "progmem.h"
#include <stdint.h>

#ifndef COMBO_TERM
#    define COMBO_TERM 50
#endif

// Maximum number of combo keys
#ifndef COMBO_KEY_COUNT
#    define COMBO_KEY_COUNT 32
#endif

#define COMBO_KEY_BLOCKS_COUNT (COMBO_KEY_COUNT + 15) / 16

// Maximum number of keys pressed at the same time, for which combos work
#ifndef COMBO_BUFFER_SIZE
#    define COMBO_BUFFER_SIZE 8
#endif

typedef void (*combo_callback)(bool pressed);

typedef enum {
    COMBO_ACTION_KEYCODE,
    COMBO_ACTION_FUNCTION,
    COMBO_ACTION_STRING,
} combo_action_type;

typedef union {
    uint16_t packed;
    struct combo_metadata_unpacked {
        uint16_t          combo_term : 10;
        bool              urgent : 1;
        combo_action_type action_type : 2;
        uint8_t           reserved : 3;
    } unpacked;
} combo_metadata;

typedef union {
    uint16_t       keycode;
    combo_callback function;
    const char *   string;  // PSTR
} combo_action;

typedef struct {
    uint16_t       key_mask[COMBO_KEY_BLOCKS_COUNT];
    combo_action   action;
    combo_metadata metadata;
} combo_data;

typedef struct {
    uint16_t combo_count;
    uint16_t combo_offset;
} combo_layer_data;

typedef struct {
    uint8_t                 keys[MATRIX_ROWS][MATRIX_COLS];
    uint8_t                 layer_count;
    const combo_layer_data *layers;
    const combo_data *      combos;
} combo_storage;

void process_combo(const keyrecord_t *record);
void matrix_scan_combo(void);

void combo_enable(void);
void combo_disable(void);
void combo_toggle(void);
bool is_combo_enabled(void);
