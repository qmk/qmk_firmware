/* Copyright 2023 Brian Low
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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "rgb_matrix_user.h"

char rgb_str[10];

// Get RGB mode name for enabled animations only
const char* get_rgb_mode_name(uint8_t mode) {
    switch(mode) {
        case 1: return "Static";
        case 2: return "AlphaMods";
        case 14: return "CycleUpDn";
        case 15: return "CycleOut";
        case 18: return "Pinwheel";
        case 20: return "DualBeam";
        case 22: return "RainbowPin";
        case 25: return "HueBreathe";
        default: return "Unknown";
    }
}

// Custom 8x8 layer bitmaps (each array is 8 bytes for 8x8 pixels)
static const uint8_t PROGMEM layer_main_bitmap[] = {
    0x3C, 0x42, 0x81, 0x99, 0x99, 0x81, 0x42, 0x3C  // Main layer - circle with dots (home icon)
};

static const uint8_t PROGMEM layer_symbols_bitmap[] = {
    0x00, 0x24, 0x66, 0xFF, 0xFF, 0x66, 0x24, 0x00  // Symbols layer - diamond/star pattern
};

static const uint8_t PROGMEM layer_util_bitmap[] = {
    0x1C, 0x22, 0x49, 0x49, 0x49, 0x49, 0x22, 0x1C  // Util layer - gear/settings icon
};

enum layer_names {
    _MAC_DEFAULT,
    _MAC_SYMBOLS,
    _MAC_UTIL
};



// Function to draw 8x8 bitmap by setting individual pixels
void oled_write_bitmap(const uint8_t *bitmap, uint8_t start_col, uint8_t start_row, bool invert) {
    for (uint8_t row = 0; row < 8; row++) {
        uint8_t byte = pgm_read_byte(&bitmap[row]);
        if (invert) {
            byte = ~byte;
        }
        for (uint8_t col = 0; col < 8; col++) {
            bool pixel_on = (byte & (1 << (7 - col))) != 0;
            oled_write_pixel(start_col + col, start_row + row, pixel_on);
        }
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAC_DEFAULT] =
        LAYOUT(
    KC_GRV,     KC_1,   KC_2, KC_3, KC_4,           KC_5,                   KC_6,   KC_7,           KC_8, KC_9, KC_0,       KC_MINUS,
    KC_TAB,     KC_Q,   KC_W, KC_E, KC_R,           KC_T,                   KC_Y,   KC_U,           KC_I, KC_O, KC_P,       KC_EQUAL,
    KC_RCTL,    KC_A,   KC_S, KC_D, KC_F,   KC_G,                   KC_H,   KC_J,   KC_K, KC_L, KC_SCLN,    KC_QUOT,
    KC_LSFT,    KC_B,   KC_Z, KC_X, KC_C,   KC_V,  KC_MUTE,     KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                RGB_MOD, LSA_T(KC_TAB), LCA_T(KC_ESC), MO(1), LCMD_T(KC_SPC),     KC_SPC, KC_ENT, SCMD_T(KC_TAB), MO(2), MOD_MEH
            ),

    [_MAC_SYMBOLS] =
        LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS,                   KC_TRNS, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_PAGE_DOWN, KC_PAGE_UP, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSLS,
    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
            ),

    [_MAC_UTIL] =
        LAYOUT(
    RGB_TOG,    KC_F1,   KC_F2,     KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  QK_BOOT,
    RGB_MOD,  RGB_HUI, RGB_SAI,   RGB_VAI, RGB_SPI, KC_F11,                       KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR,
    RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG,        KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
            )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PAGE_DOWN, KC_PAGE_UP)},
    {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
};
#endif

// Global key counter for OLED display
static uint16_t key_count = 0;

// Handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Increment key counter for all keys except RGB control keys
    if (record->event.pressed) {
        // Don't count RGB control keys for key counter
        if (!(keycode >= RGB_TOG && keycode <= RGB_MODE_TWINKLE)) {
            key_count++;
        }
    }
    return true;  // Allow QMK to process all keycodes normally
}

// OLED
#ifdef OLED_ENABLE

// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// Draw to OLED
bool oled_task_user() {
    if (is_keyboard_master()) {
        // Master side - WPM and layer info
        oled_set_cursor(0, 0);
        sprintf(rgb_str, "WC:%03d", get_current_wpm());
        oled_write(rgb_str, false);

        oled_set_cursor(0, 1);

        // Draw layer bitmap above layer name
        uint8_t current_layer = get_highest_layer(layer_state);
        switch (current_layer) {
            case _MAC_DEFAULT:
                oled_write_bitmap(layer_main_bitmap, 0, 8, false);  // Row 1 (8 pixels down)
                oled_set_cursor(0, 2);  // Row 2 for text
                oled_write_P(PSTR("Main"), false);
                break;
            case _MAC_SYMBOLS:
                oled_write_bitmap(layer_symbols_bitmap, 0, 8, false);
                oled_set_cursor(0, 2);
                oled_write_P(PSTR("Syms"), false);
                break;
            case _MAC_UTIL:
                oled_write_bitmap(layer_util_bitmap, 0, 8, false);
                oled_set_cursor(0, 2);
                oled_write_P(PSTR("Util"), false);
                break;
        }

        // RGB info with name
        oled_set_cursor(0, 3);
        if (!(rgb_matrix_is_enabled())) {
            oled_write_P(PSTR("RGB:Off"), false);
        } else {
            uint8_t current_mode = rgb_matrix_get_mode();
            oled_write(get_rgb_mode_name(current_mode), false);
        }
    } else {
        // Slave side - uptime and activity
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("UP"), false);

        oled_set_cursor(0, 1);
        // Show timer in seconds (simple uptime counter)
        static uint32_t start_time = 0;
        if (start_time == 0) start_time = timer_read32();
        uint32_t uptime_sec = (timer_read32() - start_time) / 1000;
        sprintf(rgb_str, "%02d:%02d", (int)(uptime_sec / 60), (int)(uptime_sec % 60));
        oled_write(rgb_str, false);

        oled_set_cursor(0, 2);
        oled_write_P(PSTR("KEYS"), false);

        oled_set_cursor(0, 3);
        // Show total key press count
        sprintf(rgb_str, "%04d", key_count);
        oled_write(rgb_str, false);
    }

    return false;
}

#endif
