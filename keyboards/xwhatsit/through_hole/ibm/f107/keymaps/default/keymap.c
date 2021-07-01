/* Copyright 2020 Purdea Andrei
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3,
    _FN4
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_102key_ansi(
        KC_ESC,              KC_AUDIO_MUTE,   KC_GRV,   KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,        KC_BSPC, KC_INS,  KC_HOME,  KC_PGUP,      KC_NLCK, KC_PSLS, KC_PAST,  KC_PMNS, \
        KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP, KC_TAB,      KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,   KC_PGDN,      KC_P7,   KC_P8,   KC_P9,    KC_PPLS, \
        KC_MEDIA_PLAY_PAUSE, KC_MEDIA_STOP,   KC_CAPS,        KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,       KC_ENT,  KC_PSCR, KC_SLCK,  KC_PAUS,      KC_P4,   KC_P5,   KC_P6, \
        TO(_BASE),           TO(_FN1),        KC_LSFT,           KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,   KC_F5,   KC_UP,    KC_INT1,      KC_P1,   KC_P2,   KC_P3,    KC_PENT, \
        TO(_FN2),            TO(_FN3),        KC_LCTRL,    MO(_FN1),  KC_LALT,                   KC_SPC,            KC_RALT, MO(_FN2), KC_RGUI,      KC_LEFT, KC_DOWN,  KC_RIGHT,              KC_P0,   KC_KP_DOT \
    ),
    [_FN1] = LAYOUT_102key_ansi(
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______,  _______, _______, _______,      _______, _______, _______, \
        _______, _______,   _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,   _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,     _______,  _______,                               MO(_FN4),                               _______, _______, _______,     _______, _______, _______,               _______, _______ \
    ),
    [_FN2] = LAYOUT_102key_ansi(
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______,  _______, _______, _______,      _______, _______, _______, \
        _______, _______,   _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,   _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,     _______,  _______,                               _______,                                _______, _______, _______,     _______, _______, _______,               _______, _______ \
    ),
    [_FN3] = LAYOUT_102key_ansi(
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______,  _______, _______, _______,      _______, _______, _______, \
        _______, _______,   _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,   _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,     _______,  _______,                               _______,                                _______, _______, _______,     _______, _______, _______,               _______, _______ \
    ),
    [_FN4] = LAYOUT_102key_ansi(
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,    _______, _______, EEPROM_RESET, RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,      _______, _______, DEBUG  , _______, _______, _______, _______, _______, _______, _______, _______,           _______,  _______, _______, _______,      _______, _______, _______, \
        _______, _______,   _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,   _______, _______, _______,      _______, _______, _______, _______, \
        _______, _______,   _______,     _______,  _______,                               _______,                                _______, _______, _______,     _______, _______, _______,               _______, _______ \
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
