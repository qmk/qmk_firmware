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

#include "dip_switch.h"
#include "gpio.h"
#include "util.h"
#ifdef SPLIT_KEYBOARD
#    include "split_common/split_util.h"
#endif

#include <string.h> // for memcpy


#if !defined(DIP_SWITCH_PINS) && !defined(DIP_SWITCH_MATRIX_GRID)
#    error "Either DIP_SWITCH_PINS or DIP_SWITCH_MATRIX_GRID must be defined."
#endif

#if defined(DIP_SWITCH_PINS) && defined(DIP_SWITCH_MATRIX_GRID)
#    error "Both DIP_SWITCH_PINS and DIP_SWITCH_MATRIX_GRID are defined."
#endif

#ifdef DIP_SWITCH_PINS
static pin_t dip_switch_pad[NUM_DIP_SWITCHES_MAX_PER_SIDE] = DIP_SWITCH_PINS;
#endif

extern volatile bool isLeftHand;

#ifdef DIP_SWITCH_MATRIX_GRID
static matrix_index_t dip_switch_pad[NUM_DIP_SWITCHES_MAX_PER_SIDE] = DIP_SWITCH_MATRIX_GRID;
extern bool           peek_matrix(uint8_t row_index, uint8_t col_index, bool read_raw);
static uint16_t       scan_count;
#endif /* DIP_SWITCH_MATRIX_GRID */

static uint8_t thisCount;
#ifdef SPLIT_KEYBOARD
static uint8_t thisHand, thatHand;
static uint8_t thatCount;
#endif
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


__attribute__((weak)) void dip_switch_wait_pullup_charge(void) {
    wait_us(100);
}

void dip_switch_init(void) {
#ifdef SPLIT_KEYBOARD
    thisHand  = isLeftHand ? 0 : NUM_DIP_SWITCHES_LEFT;
    thatHand  = NUM_DIP_SWITCHES_LEFT - thisHand;
    thisCount = isLeftHand ? NUM_DIP_SWITCHES_LEFT : NUM_DIP_SWITCHES_RIGHT;
    thatCount = isLeftHand ? NUM_DIP_SWITCHES_RIGHT : NUM_DIP_SWITCHES_LEFT;
#else // SPLIT_KEYBOARD
    thisCount = NUM_DIP_SWITCHES;
#endif

#ifdef DIP_SWITCH_PINS
#    if defined(SPLIT_KEYBOARD) && defined(DIP_SWITCH_PINS_RIGHT)
    if (!isLeftHand) {
        const pin_t dip_switch_pad_right[] = DIP_SWITCH_PINS_RIGHT;
        for (uint8_t i = 0; i < thisCount; i++) {
            dip_switch_pad[i] = dip_switch_pad_right[i];
        }
    }
#    endif
    for (uint8_t i = 0; i < thisCount; i++) {
        setPinInputHigh(dip_switch_pad[i]);
    }
    dip_switch_wait_pullup_charge();
    dip_switch_read(true);
#endif
#ifdef DIP_SWITCH_MATRIX_GRID
    scan_count = 0;
#endif
}

void dip_switch_read(bool forced) {
    bool     has_dip_state_changed = false;
    uint32_t dip_switch_mask       = 0;
    uint8_t  index                 = 0;

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

    for (uint8_t i = 0; i < thisCount; i++) {
        index = i;

#ifdef SPLIT_KEYBOARD
        index += thisHand;
#endif
#ifdef DIP_SWITCH_PINS
        dip_switch_state[index] = !readPin(dip_switch_pad[i]);
#endif
#ifdef DIP_SWITCH_MATRIX_GRID
        dip_switch_state[index] = peek_matrix(dip_switch_pad[i].row, dip_switch_pad[i].col, read_raw);
#endif
        dip_switch_mask |= dip_switch_state[i] << index;
        if (last_dip_switch_state[index] != dip_switch_state[index] || forced) {
            has_dip_state_changed = true;
            dip_switch_update_kb(index, dip_switch_state[index]);
        }
    }
    if (has_dip_state_changed) {
        dip_switch_update_mask_kb(dip_switch_mask);
        memcpy(last_dip_switch_state, dip_switch_state, sizeof(dip_switch_state));
    }
}

#ifdef SPLIT_KEYBOARD
void dip_switch_state_raw(bool *slave_state) {
    memcpy(slave_state, &dip_switch_state[thisHand], sizeof(bool) * thisCount);
}

void dip_switch_update_raw(bool *slave_state) {
    uint8_t  index_that_hand       = 0;
    uint8_t  index_this_hand       = 0;
    uint32_t dip_switch_mask       = 0;
    bool     has_dip_state_changed = false;

    for (int i = 0; i < thatCount; ++i) {
        index_that_hand = i + thatHand;
        index_this_hand = i + thisHand;

        // copy slave state to master state
        dip_switch_state[index_that_hand] = slave_state[i];

        // update mask for both sides
        dip_switch_mask |= dip_switch_state[index_that_hand] << index_that_hand;
        dip_switch_mask |= dip_switch_state[index_this_hand] << index_this_hand;

        // if there is a change do update
        if (last_dip_switch_state[index_that_hand] != dip_switch_state[index_that_hand]) {
            has_dip_state_changed = true;
            dip_switch_update_kb(index_that_hand, dip_switch_state[index_that_hand]);
        }
    }

    // if mask has changed do update
    if (has_dip_state_changed) {
        dip_switch_update_mask_kb(dip_switch_mask);
        memcpy(last_dip_switch_state, dip_switch_state, sizeof(dip_switch_state));
    }
}

#endif
