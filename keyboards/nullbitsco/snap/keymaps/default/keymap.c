/* Copyright 2021 Jay Greco
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
#include "common/remote_kb.h"

// clang-format off
enum layers {
    _BASE = 0,
    _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ansi(
             KC_ESC,   KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,    KC_F7,  KC_F8,  KC_F9,   KC_F10,    KC_F11,   KC_F12,   KC_PSCR,  KC_PAUS,
    KC_F13,  KC_GRV,   KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,     KC_7,   KC_8,   KC_9,    KC_0,      KC_MINS,  KC_EQL,        KC_BSPC,       KC_HOME,
    KC_F14,  KC_TAB,   KC_Q,    KC_W,   KC_E,   KC_R,           KC_T,     KC_Y,   KC_U,   KC_I,    KC_O,      KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_END,
    KC_F15,  KC_CAPS,  KC_A,    KC_S,   KC_D,   KC_F,           KC_G,     KC_H,   KC_J,   KC_K,    KC_L,      KC_SCLN,  KC_QUOT,  KC_ENT,             KC_PGUP,
    KC_F16,       KC_LSFT,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,     KC_N,   KC_M,   KC_COMM, KC_DOT,    KC_SLSH,  KC_RSFT,            KC_UP,    KC_PGDN,
    KC_F17,  KC_LCTL,  KC_LGUI, KC_LALT,        MO(_FUNC),     KC_SPC,   KC_BSPC,                  MO(_FUNC), KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
    [_FUNC] = LAYOUT_ansi(
             QK_BOOT,  _____,   _____,  _____,  _____,  _____,  _____,    _____,  _____,  _____,   _____,     _____,    _____,    _____,    _____,
    RGB_TOG, _____,    _____,   _____,  _____,  _____,  _____,  _____,    _____,  _____,  _____,   _____,     _____,    _____,         _____,         _____,
    _____,   _____,    _____,   _____,  _____,  _____,          _____,    _____,  _____,  _____,   _____,     _____,    _____,    _____,    _____,    _____,
    _____,   _____,    _____,   _____,  _____,  _____,          _____,    _____,  _____,  _____,   _____,     _____,    _____,    _____,              _____,
    _____,        _____,        _____,  _____,  _____,  _____,  _____,    _____,  _____,  _____,   _____,     _____,    _____,              _____,    _____,
    _____,   _____,    _____,   _____,          _____,          _____,    _____,                   _____,     _____,    _____,    KC_MPRV,  KC_MPLY,  KC_MNXT
  ),
};
// clang-format on

// RGB config, for changing RGB settings on non-VIA firmware
#ifdef RGBLIGHT_ENABLE
void change_RGB(bool clockwise) {
    bool shift = get_mods() & MOD_MASK_SHIFT;
    bool alt   = get_mods() & MOD_MASK_ALT;
    bool ctrl  = get_mods() & MOD_MASK_CTRL;

#ifdef CONSOLE_ENABLE
    dprintf("Mods: %u\n", get_mods());
#endif

    if (clockwise) {
        if (alt) {
            rgblight_increase_hue();
        } else if (ctrl) {
            rgblight_increase_val();
        } else if (shift) {
            rgblight_increase_sat();
        } else {
            rgblight_step();
        }

    } else {
        if (alt) {
            rgblight_decrease_hue();
        } else if (ctrl) {
            rgblight_decrease_val();
        } else if (shift) {
            rgblight_decrease_sat();
        } else {
            rgblight_step_reverse();
        }
    }
}
#endif

bool encoder_update_user(uint8_t index, bool clockwise) {
    // change RGB settings and don't do anything else
    if (!layer_state_is(_BASE)) {
        #ifdef RGBLIGHT_ENABLE
        change_RGB(clockwise);
        #endif
        return false;
    }
    /* Left encoder */
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    /* Right encoder */
    } else if (index == 1) {
        if (clockwise) {
            tap_code_delay(KC_MNXT, 10);
        } else {
            tap_code_delay(KC_MPRV, 10);
        }
    }
    return true;
}
