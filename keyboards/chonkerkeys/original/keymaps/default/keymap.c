/* Copyright 2021 Chonkerkeys
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
#include QMK_KEYBOARD_H
#include "virtser.h"
#include "../protocol.c"
#include "../../../keyconfig.h"

// Defines names for use in layer keycodes and the keymap
enum layer_type {
    CH_ZOOM_WINDOWS,
    CH_ZOOM_MACOS
};

enum key_size {
    key_1,
    key_1_5,
    key_3
};

enum key_ordinal {
    empty,
    left,
    top,
    right,
    bottom
};

// Code-generated section
const uint32_t firmware_version = 1;

#define LAYER_COUNT 2

const uint8_t layers[LAYER_COUNT] = {
    CH_ZOOM_WINDOWS,
    CH_ZOOM_MACOS
};

const uint8_t key_size_and_ordinals[LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
    {
        {0x01, 0x81, 0x00, 0x00},
        {0x41, 0x43, 0x00, 0x01}
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [CH_ZOOM_WINDOWS] = LAYOUT(
        CH_ZOOM_REACT_TOGGLE, CH_ZOOM_LEAVE_MEETING, KC_NO, KC_NO,
        CH_ZOOM_MUTE_TOGGLE, CH_ZOOM_VIDEO_TOGGLE, KC_NO, CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE
    ),
    [CH_ZOOM_MACOS] = LAYOUT(
        CH_ZOOM_REACT_TOGGLE, CH_ZOOM_LEAVE_MEETING, KC_NO, KC_NO,
        CH_ZOOM_MUTE_TOGGLE, CH_ZOOM_VIDEO_TOGGLE, KC_NO, CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE
    )
};

// End of code-generated section

uint8_t layer_count() {
    return LAYER_COUNT;
}

uint8_t layer_type(uint8_t index) {
    return layers[index];
}

uint8_t key_size_and_ordinal(uint8_t layer, uint8_t x, uint8_t y) {
    return key_size_and_ordinals[layer][y][x];
}

uint8_t key_action_type(uint8_t layer, uint8_t x, uint8_t y) {
    return keymaps[layer][y][x];
}

uint32_t key_icon(uint8_t layer, uint8_t x, uint8_t y) {
    // TODO: Confirm with client.
    return 0;
}

bool isWindows(uint8_t layer) {
    return layer % 2 == 0;
}

void switch_layer(void) {
    uint16_t current_layer = CH_ZOOM_WINDOWS;
    for (uint16_t i = CH_ZOOM_WINDOWS; i < LAYER_COUNT; ++i) {
        if (IS_LAYER_ON(i)) {
            current_layer = i;
            break;
        }
    }
    layer_clear();
    uint16_t next_layer = current_layer + 1;
    if (next_layer >= LAYER_COUNT) {
        next_layer = 0;
    }
    layer_on(next_layer);
}

void virtser_recv(uint8_t c) {
    process_protocol(c);
}

void send_protocol(uint8_t c) {
    virtser_send(c);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_either_pressed = false;
    if (record->event.key.row == 0 && record->event.key.col <= 1) {
        if (is_either_pressed) {
            switch_layer();
        }
        is_either_pressed = record->event.pressed;
    }
    if (record->event.pressed) {
        uint16_t keyConfigIndex = keycode - CH_CUSTOM;
        uint16_t const* keyMacros = windowsConfigs[keyConfigIndex];
        for (uint32_t i = 0; i < KEY_MACROS_MAX_COUNT; ++i) {
            uint16_t code = keyMacros[i];
            if (code == KC_NO) continue;
            register_code(code);
        }
        for (int32_t i = KEY_MACROS_MAX_COUNT - 1; i >= 0; --i) {
            uint16_t code = keyMacros[i];
            if (code == KC_NO) continue;
            unregister_code(code);
        }
    }
    return false;
}
