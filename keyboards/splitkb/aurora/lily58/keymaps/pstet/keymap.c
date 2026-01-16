/* Copyright 2022 splitkb.com <support@splitkb.com>
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

enum layers {
    _COLEMAK = 0,
    _QWERTY,
    _DVORAK,
    _RAISE,
    _LOWER,
    _ADJUST,
};

#define COLEMAK DF(_COLEMAK)
#define QWERTY DF(_QWERTY)
#define DVORAK DF(_DVORAK)


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT(
        _______, _______, _______, KC_VOLD, KC_VOLU, _______,                       _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_RCTL,
        KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                       KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_ESC ,
        KC_LCTL, KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                       KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   , ADJUST ,     _______, KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_LALT,
                                   KC_LALT, RAISE  , KC_LSFT, KC_SPC ,     KC_ENT , LOWER  , KC_BSPC, KC_LGUI
    ),
    [_QWERTY] = LAYOUT(
        KC_TAB , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                       KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
        KC_CAPS, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                       KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_ESC ,
        KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                       KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , ADJUST ,     _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_LALT,
                                   KC_LALT, RAISE  , KC_SPC , KC_LSFT,     LOWER  , KC_ENT , KC_BSPC, KC_LGUI
    ),
    [_DVORAK] = LAYOUT(
        _______, _______, _______, KC_VOLD, KC_VOLU, _______,                       _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
        KC_TAB , KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   ,                       KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_ESC ,
        KC_LCTL, KC_A   , KC_O   , KC_E   , KC_U   , KC_I   ,                       KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_QUOT,
        KC_LSFT, KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , ADJUST ,     _______, KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , KC_LALT,
                                   KC_LALT, RAISE  , KC_SPC , KC_LSFT,     LOWER  , KC_ENT , KC_BSPC, KC_LGUI
    ),
    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
        KC_TAB , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                       KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_TILD,
        KC_LCTL, KC_LPRN, KC_RPRN, KC_EQL , KC_MINS, KC_PLUS,                       KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_GRV ,
        KC_LSFT, KC_LCBR, KC_RCBR, KC_ASTR, KC_UNDS, KC_PERC, ADJUST ,     _______, KC_BSLS, KC_LBRC, KC_RBRC, KC_DLR , KC_PIPE, KC_LALT,
                                   KC_LALT, RAISE  , KC_SPC , KC_LSFT,     LOWER  , KC_ENT , KC_BSPC, KC_LGUI
    ),
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
        KC_TAB , KC_MPRV, KC_MPLY, KC_MNXT, KC_CIRC, _______,                       KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,
        KC_LCTL, KC_EXLM, KC_AT  , KC_HASH, KC_AMPR, KC_CIRC,                       KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        KC_LSFT, _______, _______, KC_PSCR, KC_DEL , _______, ADJUST ,     _______, KC_INS , KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_LALT,
                                   KC_LALT, RAISE  , KC_SPC , KC_LSFT,     LOWER,   KC_ENT , KC_BSPC, KC_LGUI
    ),
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                       _______, KC_VOLD, KC_VOLU, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                       _______, COLEMAK, QWERTY , DVORAK , _______, _______,
        _______, _______, _______, _______, _______, _______, ADJUST ,     _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
                                   KC_LALT, RAISE  , KC_SPC , KC_LSFT,     LOWER,   KC_ENT , KC_BSPC, KC_LGUI
    )
};

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_RED); // sets the color to red without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // 0 is left-half encoder
    // 1 is right-half encoder
    if (index == 0) {
        tap_code(KC_0);
    } else if (index == 1) {
        tap_code(KC_1);
    }

    if (clockwise) {
        tap_code16(KC_PLUS);
    } else {
        tap_code(KC_MINUS);
    }

    return false;
}
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // A 128x32 OLED rotated 90 degrees is 5 characters wide and 16 characters tall
    // This example string should fill that neatly
    const char *text = PSTR("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%^&*()[]{}-=_+?");

    if (is_keyboard_master()) {
        oled_write_P(text, false);
    } else {
        oled_write_P(text, false);
    }
    return false;
}
#endif
