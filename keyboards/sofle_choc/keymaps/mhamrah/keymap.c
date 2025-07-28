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
#include "rgb_matrix_user.h"

char rgb_str[10];

enum layer_names {
    _MAC_DEFAULT,
    _MAC_SYMBOLS,
    _MAC_UTIL
};

enum custom_keycodes {
    RGB_CYCLE = SAFE_RANGE,
    RGB_CYCLE_REV
};

// Custom RGB modes array
const uint8_t custom_rgb_modes[] = {
    0,   // Off
    2,   // ALPHAS_MODS
    14,  // CYCLE_UP_DOWN
    15,  // CYCLE_OUT_IN
    18,  // CYCLE_PINWHEEL
    20,  // DUAL_BEACON
    22,  // RAINBOW_PINWHEELS
    25   // HUE_BREATHING
};

#define CUSTOM_RGB_MODES_COUNT (sizeof(custom_rgb_modes) / sizeof(custom_rgb_modes[0]))

uint8_t current_custom_mode_index = 6; // Start with RAINBOW_PINWHEELS (index 6)

// Custom RGB mode cycling function
void cycle_custom_rgb_mode(bool forward) {
    if (forward) {
        current_custom_mode_index = (current_custom_mode_index + 1) % CUSTOM_RGB_MODES_COUNT;
    } else {
        current_custom_mode_index = (current_custom_mode_index + CUSTOM_RGB_MODES_COUNT - 1) % CUSTOM_RGB_MODES_COUNT;
    }
    
    if (custom_rgb_modes[current_custom_mode_index] == 0) {
        rgb_matrix_disable();
    } else {
        rgb_matrix_enable();
        rgb_matrix_mode(custom_rgb_modes[current_custom_mode_index]);
    }
}

// Get RGB mode name
const char* get_rgb_mode_name(uint8_t mode) {
    switch(mode) {
        case 0: return "Off";
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAC_DEFAULT] = 
        LAYOUT( 
    KC_GRV,     KC_1,   KC_2, KC_3, KC_4,           KC_5,                   KC_6,   KC_7,           KC_8, KC_9, KC_0,       KC_MINUS, 
    KC_TAB,     KC_Q,   KC_W, KC_E, KC_R,           KC_T,                   KC_Y,   KC_U,           KC_I, KC_O, KC_P,       KC_EQUAL, 
    KC_RCTL,    KC_A,   KC_S, KC_D, KC_F,   KC_G,                   KC_H,   KC_J,   KC_K, KC_L, KC_SCLN,    KC_QUOT, 
    LSFT_T(KC_LBRC),    KC_B,   KC_Z, KC_X, KC_C,   KC_V,  KC_MUTE,     KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_RBRC), 
                RGB_CYCLE, LSA_T(KC_TAB), LCA_T(KC_ESC), MO(1), LCMD_T(KC_SPC),     KC_SPC, KC_ENT, SCMD_T(KC_TAB), MO(2), MOD_MEH  
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
    RGB_CYCLE,  RGB_HUI, RGB_SAI,   RGB_VAI, RGB_SPI, KC_F11,                       KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR, 
    RGB_CYCLE_REV, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG,        KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
            )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PAGE_DOWN, KC_PAGE_UP)},
    {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    {ENCODER_CCW_CW(RGB_CYCLE_REV, RGB_CYCLE), ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
};
#endif

// Handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_CYCLE:
            if (record->event.pressed) {
                cycle_custom_rgb_mode(true);
            }
            return false;
        case RGB_CYCLE_REV:
            if (record->event.pressed) {
                cycle_custom_rgb_mode(false);
            }
            return false;
        default:
            return true;
    }
}

// OLED
#ifdef OLED_ENABLE
 
// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270; 
}

// Layer icons (8x8 bitmaps)
static const char PROGMEM main_icon[] = {
    0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C
};

static const char PROGMEM symbols_icon[] = {
    0x18, 0x24, 0x42, 0x99, 0x99, 0x42, 0x24, 0x18
};

static const char PROGMEM util_icon[] = {
    0xFF, 0x81, 0xBD, 0xA5, 0xA5, 0xBD, 0x81, 0xFF
};

// Draw to OLED
bool oled_task_user() {
    if (is_keyboard_master()) {
        // Master side - WPM and layer info
        oled_set_cursor(0, 0);
        sprintf(rgb_str, "WPM:%03d", get_current_wpm());
        oled_write(rgb_str, false);

        // Layer with icon
        oled_set_cursor(0, 1);
        switch (get_highest_layer(layer_state)) {
            case _MAC_DEFAULT:
                oled_write_raw_P(main_icon, sizeof(main_icon));
                oled_write(" Main  ", false);
                break;
            case _MAC_SYMBOLS:
                oled_write_raw_P(symbols_icon, sizeof(symbols_icon));
                oled_write(" Syms  ", false);
                break;
            case _MAC_UTIL:
                oled_write_raw_P(util_icon, sizeof(util_icon));
                oled_write(" Util  ", false);
                break;
        }

        // RGB info with name
        oled_set_cursor(0, 2);
        if (!(rgb_matrix_is_enabled())) {
            oled_write_P(PSTR("RGB:Off"), false);
        } else {
            uint8_t current_mode = rgb_matrix_get_mode();
            oled_write(get_rgb_mode_name(current_mode), false);
        }
    } else {
        // Slave side - system stats and time
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("SYSTEM"), false);
        
        oled_set_cursor(0, 1);
        // Simple time display (you'll need to implement time sync)
        oled_write_P(PSTR("--:--"), false);
        
        oled_set_cursor(0, 2);
        oled_write_P(PSTR("STATS"), false);
        
        oled_set_cursor(0, 3);
        // Placeholder for CPU usage (requires external script)
        oled_write_P(PSTR("CPU:--"), false);
    }

    return false;
}

#endif
