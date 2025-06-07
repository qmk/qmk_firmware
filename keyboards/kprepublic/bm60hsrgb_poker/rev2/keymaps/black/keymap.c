/* Copyright 2021 bdtc123
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

#include "eeprom.h"

#define LT_SPC LT(LY_NAV, KC_SPC)
#define MO_CTRL MO(LY_CTRL)

#define LCTL_SPC C(KC_SPC)

enum {
    QU_RAND = SAFE_RANGE
};

enum {
    LY_BASE = 0,
    LY_NAV,
    LY_CTRL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LY_BASE] = LAYOUT_60_ansi(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT ,
        SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   SC_RSPC,
        KC_LCTL, KC_LALT, KC_LGUI,                            LT_SPC,                             KC_RGUI, MO_CTRL, KC_RALT, KC_RCTL
    ),
    [LY_NAV] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [LY_CTRL] = LAYOUT_60_ansi(
        QK_BOOT, EE_CLR , QK_RBT , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QU_RAND,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
};


void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#endif /* RGB_MATRIX_ENABLE */
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QU_RAND:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < 16; i++) {
                    tap_random_base64();
                }
            }

            return false;
        default:
            return true;
    }
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case LY_NAV:
            for (uint8_t i = 34; i <= 37; i++) {
                rgb_matrix_set_color(i, RGB_GREEN);
            }
            break;
        case LY_CTRL:
            rgb_matrix_set_color_all(RGB_MAGENTA);
            break;
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(28, RGB_WHITE);
    } else {
        rgb_matrix_set_color(28, RGB_OFF);
    }

    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case LY_BASE:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
            break;
    }

    return state;
}
#endif /* RGB_MATRIX_ENABLE */
