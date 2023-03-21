/* Copyright 2019 Josef Adamcik
 *
 *  This program is free software: you can redistribute it and/or modify
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

enum katana_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _M_COLEMAK,
    _M_QWERTY,
    _W_COLEMAK,
    _W_QWERTY,
    _NUMB,
    _SYMB,
    _M_EXT,
    _W_EXT
};

enum katana_keycodes {
    M_COLEMAK = SAFE_RANGE,
    M_QWERTY,
    W_COLEMAK,
    W_QWERTY
};

#define K_SPCFN LT(_SYMB, KC_SPACE) /* Tap for space, hold for symbols layer */
#define K_BSPFN LT(_SYMB, KC_BSPC)  /* Tap for backspace, hold for symbols layer */
/* Linux/win variants */
#define W_LEFT_MOD MT(MOD_RCTL, KC_LEFT)
#define W_DOWN_MOD MT(MOD_RALT, KC_DOWN)
#define W_UP_MOD MT(MOD_RGUI, KC_UP)
#define W_UNDO    LCTL(KC_Z)
#define W_CUT     LCTL(KC_X)
#define W_COPY    LCTL(KC_C)
#define W_PASTE   LCTL(KC_V)
#define W_PRVWD LCTL(KC_LEFT)
#define W_NXTWD LCTL(KC_RIGHT)
#define W_LSTRT KC_HOME
#define W_LEND KC_END
/* Mac variants */
#define M_LEFT_MOD MT(MOD_RGUI, KC_LEFT)
#define M_DOWN_MOD MT(MOD_RALT, KC_DOWN)
#define M_UP_MOD MT(MOD_RCTL, KC_UP)
#define M_UNDO LGUI(KC_Z)
#define M_CUT LGUI(KC_X)
#define M_COPY LGUI(KC_C)
#define M_PASTE LGUI(KC_V)
#define M_PRVWD LALT(KC_LEFT)
#define M_NXTWD LALT(KC_RIGHT)
#define M_LSTRT LGUI(KC_LEFT)
#define M_LEND LGUI(KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_M_COLEMAK] = LAYOUT(
    KC_ESC,    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   TG(_NUMB),KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
    KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_LBRC,          KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    MO(_M_EXT),KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_MINS,          KC_QUOT, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_EQL,  KC_DEL,  KC_BSLS, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    MO(_SYMB), KC_LCTL, KC_LALT, KC_LGUI,                   K_BSPFN, KC_ENT,  KC_SPACE,         M_LEFT_MOD,M_DOWN_MOD,M_UP_MOD,  KC_RIGHT,MO(_SYMB)
),
[_M_QWERTY] = LAYOUT(
    KC_ESC,    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   TG(_NUMB),KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,          KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    MO(_M_EXT),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MINS,          KC_QUOT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_EQL,  KC_DEL,  KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    MO(_SYMB), KC_LCTL, KC_LALT, KC_LGUI,                   K_BSPFN, KC_ENT,  KC_SPACE,         M_LEFT_MOD,M_DOWN_MOD,M_UP_MOD,   KC_RIGHT,MO(_SYMB)
),
[_W_COLEMAK] = LAYOUT(
    KC_ESC,    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   TG(_NUMB),KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
    KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_LBRC,          KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    MO(_W_EXT),KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_MINS,          KC_QUOT, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_EQL,  KC_DEL,  KC_BSLS, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    MO(_SYMB), KC_LGUI, KC_LALT, KC_LCTL,                   K_BSPFN, KC_ENT,  KC_SPACE,         W_LEFT_MOD,W_DOWN_MOD,W_UP_MOD,  KC_RIGHT,MO(_SYMB)
),
[_W_QWERTY] = LAYOUT(
    KC_ESC,    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   TG(_NUMB),KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,          KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    MO(_W_EXT),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MINS,          KC_QUOT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_EQL,  KC_DEL,  KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    MO(_SYMB), KC_LGUI, KC_LALT, KC_LCTL,                   K_BSPFN, KC_ENT,  KC_SPACE,         W_LEFT_MOD,W_DOWN_MOD,W_UP_MOD,   KC_RIGHT,MO(_SYMB)
),
[_NUMB] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,_______, KC_PSLS, KC_PAST, KC_PMNS, _______, _______,
    _______, _______, _______, KC_MS_U, _______, _______, _______,          _______,_______, KC_7,    KC_8,    KC_9,    KC_PPLS, _______,
    _______, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,          _______,_______, KC_4,    KC_5,    KC_6,    KC_PPLS, _______,
    _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______,_______, KC_1,    KC_2,    KC_3,    KC_PENT, _______,
    _______, _______, _______, _______,                   KC_BTN1, _______, KC_P0,            KC_PDOT, _______, _______, _______, _______
),
[_SYMB] = LAYOUT(
    QK_BOOT, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,          _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_VOLD,          KC_VOLU, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_PLUS, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_MPRV, KC_MPLY, KC_MNXT, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
    _______, _______, _______, _______,                   KC_DEL,  _______, _______,          _______, _______, _______, _______, _______
),
[_M_EXT] = LAYOUT(
    QK_BOOT,M_COLEMAK,M_QWERTY,W_COLEMAK,W_QWERTY,_______,_______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,          _______, KC_PGUP, M_PRVWD, KC_UP,   M_NXTWD, _______, _______,
    _______, KC_LALT, KC_LCTL, KC_LSFT, _______, KC_CAPS, _______,          _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT,KC_DEL,  _______,
    _______, M_UNDO,  M_CUT,   M_COPY,  M_PASTE, _______, _______, _______, _______, _______, M_LSTRT, _______, M_LEND,  _______, _______,
    _______, _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
),
[_W_EXT] = LAYOUT(
    QK_BOOT,M_COLEMAK,M_QWERTY,W_COLEMAK,W_QWERTY,_______,_______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,          _______, KC_PGUP, W_PRVWD, KC_UP,   W_NXTWD, _______, _______,
    _______, KC_LALT, KC_LCTL, KC_LSFT, _______, KC_CAPS, _______,          _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT,KC_DEL,  _______,
    _______, W_UNDO,  W_CUT,   W_COPY,  W_PASTE, _______, _______, _______, _______, _______, W_LSTRT, _______, W_LEND,  _______, _______,
    _______, _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
)
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_M_QWERTY);
            }
            return false;
            break;
        case M_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_M_COLEMAK);
            }
            return false;
            break;
        case W_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_W_QWERTY);
            }
            return false;
            break;
        case W_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_W_COLEMAK);
            }
            return false;
            break;
    }
    return true;
}

void led_set_user(uint8_t usb_led) {

}
