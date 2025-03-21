/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2019 Drashna Jaelre (Christopher Courtney) <drashna@live.com>
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

#include <string.h> // for memcpy

#include "dip_switch.h"

#ifdef SPLIT_KEYBOARD
#    include "split_common/split_util.h"
#endif

#if !defined(DIP_SWITCH_PINS) && !defined(DIP_SWITCH_MATRIX_GRID)
#    error "Either DIP_SWITCH_PINS or DIP_SWITCH_MATRIX_GRID must be defined."
#endif

#if defined(DIP_SWITCH_PINS) && defined(DIP_SWITCH_MATRIX_GRID)
#    error "Both DIP_SWITCH_PINS and DIP_SWITCH_MATRIX_GRID are defined."
#endif

#ifdef DIP_SWITCH_PINS
static pin_t dip_switch_pad[] = DIP_SWITCH_PINS;
#endif

#ifdef DIP_SWITCH_MATRIX_GRID
static matrix_intersection_t dip_switch_pad[] = DIP_SWITCH_MATRIX_GRID;
extern bool                  peek_matrix(uint8_t row_index, uint8_t col_index, bool read_raw);
static uint16_t              scan_count;
#endif /* DIP_SWITCH_MATRIX_GRID */

static bool dip_switch_state[NUM_DIP_SWITCHES]      = {0};
static bool last_dip_switch_state[NUM_DIP_SWITCHES] = {0};

__attribute__((weak)) bool dip_switch_update_user(uint8_t index, bool active) {
    return true;
}

__attribute__((weak)) bool dip_switch_update_kb(uint8_t index, bool active) {
    return dip_switch_update_user(index, active);
}

__attribute__((weak)) bool dip_switch_update_mask_user(uint32_t state) {
    return true;
}

__attribute__((weak)) bool dip_switch_update_mask_kb(uint32_t state) {
    return dip_switch_update_mask_user(state);
}

#ifdef DIP_SWITCH_MAP_ENABLE
#    include "keymap_introspection.h"
#    include "action.h"
#    include "wait.h"

#    ifndef DIP_SWITCH_MAP_KEY_DELAY
#        define DIP_SWITCH_MAP_KEY_DELAY TAP_CODE_DELAY
#    endif

static void dip_switch_exec_mapping(uint8_t index, bool on) {
    // The delays below cater for Windows and its wonderful requirements.
    action_exec(on ? MAKE_DIPSWITCH_ON_EVENT(index, true) : MAKE_DIPSWITCH_OFF_EVENT(index, true));
#    if DIP_SWITCH_MAP_KEY_DELAY > 0
    wait_ms(DIP_SWITCH_MAP_KEY_DELAY);
#    endif // DIP_SWITCH_MAP_KEY_DELAY > 0

    action_exec(on ? MAKE_DIPSWITCH_ON_EVENT(index, false) : MAKE_DIPSWITCH_OFF_EVENT(index, false));
#    if DIP_SWITCH_MAP_KEY_DELAY > 0
    wait_ms(DIP_SWITCH_MAP_KEY_DELAY);
#    endif // DIP_SWITCH_MAP_KEY_DELAY > 0
}
#endif // DIP_SWITCH_MAP_ENABLE

void dip_switch_init(void) {
#ifdef DIP_SWITCH_PINS
#    if defined(SPLIT_KEYBOARD) && defined(DIP_SWITCH_PINS_RIGHT)
    if (!isLeftHand) {
        const pin_t dip_switch_pad_right[] = DIP_SWITCH_PINS_RIGHT;
        for (uint8_t i = 0; i < NUM_DIP_SWITCHES; i++) {
            dip_switch_pad[i] = dip_switch_pad_right[i];
        }
    }
#    endif
    for (uint8_t i = 0; i < NUM_DIP_SWITCHES; i++) {
        gpio_set_pin_input_high(dip_switch_pad[i]);
    }
    dip_switch_read(true);
#endif
#ifdef DIP_SWITCH_MATRIX_GRID
    scan_count = 0;
#endif
}

void dip_switch_read(bool forced) {
    bool     has_dip_state_changed = false;
    uint32_t dip_switch_mask       = 0;

#ifdef DIP_SWITCH_MATRIX_GRID
    bool read_raw = false;

    if (scan_count < 500) {
        scan_count++;
        if (scan_count == 10) {
            read_raw = true;
            forced   = true; /* First reading of the dip switch */
        } else {
            return;
        }
    }
#endif

    for (uint8_t i = 0; i < NUM_DIP_SWITCHES; i++) {
#ifdef DIP_SWITCH_PINS
        dip_switch_state[i] = !gpio_read_pin(dip_switch_pad[i]);
#endif
#ifdef DIP_SWITCH_MATRIX_GRID
        dip_switch_state[i] = peek_matrix(dip_switch_pad[i].row, dip_switch_pad[i].col, read_raw);
#endif
        dip_switch_mask |= dip_switch_state[i] << i;
        if (last_dip_switch_state[i] != dip_switch_state[i] || forced) {
            has_dip_state_changed = true;
#ifndef DIP_SWITCH_MAP_ENABLE
            dip_switch_update_kb(i, dip_switch_state[i]);
#else
            dip_switch_exec_mapping(i, dip_switch_state[i]);
#endif
        }
    }
    if (has_dip_state_changed) {
#ifndef DIP_SWITCH_MAP_ENABLE
        dip_switch_update_mask_kb(dip_switch_mask);
#endif
        memcpy(last_dip_switch_state, dip_switch_state, sizeof(dip_switch_state));
    }
}

void dip_switch_task(void) {
    dip_switch_read(false);
}
