/* Copyright 2025 Garretonzo
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

#include "keycode_cache_mock.h"
#include "quantum/action.h"
#include "quantum/quantum_keycodes.h"

// Mock keymap storage
static uint16_t mock_keymap[4][4] = {{KC_NO}};

// Mock functions needed for testing
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    if (layer < 4 && key.row < 4 && key.col < 4) {
        return mock_keymap[key.row][key.col];
    }
    return KC_NO;
}

void dynamic_keymap_set_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode) {
    if (layer < 4 && row < 4 && column < 4) {
        mock_keymap[row][column] = keycode;
    }
}

uint16_t dynamic_keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t column) {
    if (layer < 4 && row < 4 && column < 4) {
        return mock_keymap[row][column];
    }
    return KC_NO;
}

action_t action_for_keycode(uint16_t keycode) {
    action_t action;
    action.code = keycode;
    return action;
}

action_t action_for_key(uint8_t layer, keypos_t key) {
    uint16_t keycode = keymap_key_to_keycode(layer, key);
    return action_for_keycode(keycode);
}

// Utilities for debug
uint8_t biton(uint8_t bits) {
    for (uint8_t i = 0; i < 8; i++) {
        if (bits & (1 << i)) return i;
    }
    return 0;
}

uint8_t biton16(uint16_t bits) {
    for (uint8_t i = 0; i < 16; i++) {
        if (bits & (1 << i)) return i;
    }
    return 0;
}

uint8_t biton32(uint32_t bits) {
    for (uint8_t i = 0; i < 32; i++) {
        if (bits & (1UL << i)) return i;
    }
    return 0;
}

// Keyboard functions
void clear_keyboard_but_mods(void) {
    // No-op for tests
}

void clear_keyboard_but_mods_and_keys(void) {
    // No-op for tests
}
