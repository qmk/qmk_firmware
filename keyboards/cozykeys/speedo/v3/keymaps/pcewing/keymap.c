/*
 * Copyright 2022 Paul Ewing
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

#include "key_repeater.h"

#include <stdlib.h>

enum {
    LAYER_DEFAULT,
    LAYER_FN,
    LAYER_MACRO,

    __LAYER_COUNT,
};

#define TO_MACRO TO(LAYER_MACRO)
#define TO_DFLT TO(LAYER_DEFAULT)
#define MO_FN   MO(LAYER_FN)

#define RGB_N RGB_MOD  // Rotate to next RGB mode
#define RGB_P RGB_RMOD // Rotate to next RGB mode

#define KC_YANK LCTL(KC_INS) // Copy shortcut in most terminal emulators
#define KC_PUT  LSFT(KC_INS) // Paste shortcut in most terminal emulators

// Custom keycodes
enum {
    SH_TOG = SAFE_RANGE,  // Toggle shift
    SH_BTN1,              // Shift left click
    RP_BTN1,              // Click repeatedly while key is held
};

const uint16_t PROGMEM keymaps[__LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {

[LAYER_DEFAULT] = LAYOUT(
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_UP,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT,           KC_RGHT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_DOWN,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_GRV,  MO_FN,   KC_BSPC, KC_DEL,            KC_ENT,  KC_SPC,  KC_LBRC, KC_RBRC, KC_RALT, KC_RGUI, KC_RCTL
),

[LAYER_FN] = LAYOUT(
    RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,                            _______, _______, _______, _______, _______, RESET,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          RGB_TOG,          KC_YANK, KC_GRV,  KC_LBRC, KC_RBRC, KC_PUT,  _______,
    KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_INS,  RGB_N,            RGB_P,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS,          RGB_M_P,          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______,          TO_MACRO, _______, _______, _______, _______, _______, _______
),

[LAYER_MACRO] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, RP_BTN1, SH_TOG,           _______,          _______, _______, _______, _______, _______, _______,
    TO_DFLT, _______, _______, KC_BTN1, SH_BTN1, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_1,    KC_6,    _______,          _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_BTN1, _______,          _______, _______, _______, _______, _______, _______, _______
),

};

static bool shift_enabled = false;

static struct key_repeater_t* click_repeater = NULL;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SH_TOG:
        if (record->event.pressed) {
            if (shift_enabled) {
                unregister_code(KC_LSFT);
            } else {
                register_code(KC_LSFT);
            }
            shift_enabled = !shift_enabled;
        }
        return false; // Skip all further processing of this key
    case SH_BTN1:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_BTN1);
        } else {
            unregister_code(KC_BTN1);
            unregister_code(KC_LSFT);
        }
        return false;
    case RP_BTN1:
        if (record->event.pressed) {
            kr_enable(click_repeater);
        } else {
            kr_disable(click_repeater);
        }
        return false;
    default:
        return true; // Process all other keycodes normally
    }
}

void keyboard_post_init_user(void) {
    // Seed the random number generator which is used by the key repeater
    srand(timer_read32());

    // Configure and instantiate a key repeater for mouse button 1 "rapid fire"
    struct key_repeater_config_t cfg = {
        .key = KC_BTN1,
        .key_duration_min = 20,
        .key_duration_max = 50,
        .wait_duration_min = 90,
        .wait_duration_max = 140,
    };

    click_repeater = kr_new(&cfg);
}

void matrix_scan_user(void) {
    kr_poll(click_repeater);
}
