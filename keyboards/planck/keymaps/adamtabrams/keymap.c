/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"


enum planck_layers {
  _NORMAL,
  _COLEMAK,
  _NUMBER,
  _ARROWS,
  _CURSOR,
  _SYSTEM,
  _KBOARD,
  _FMWARE
};

enum planck_keycodes {
  BACKTLD = SAFE_RANGE
};

#define NORMAL TO(_NORMAL)
#define COLEMAK TO(_COLEMAK)
#define NUMBER TT(_NUMBER)
#define ARROWS TT(_ARROWS)
#define CURSOR TT(_CURSOR)
#define SYSTEM TT(_SYSTEM)
#define KBOARD MO(_KBOARD)
#define FMWARE MO(_FMWARE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ## Normal

|C(Tab)|  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |C(-_) |
|Bsp/~ |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;:  |A('") |
| G(!) |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /?  |G(Ent)|
|COLMAK| GUI  | ALT  |System|Cursor|S(Esc)|Space |Arrows| Left | Down |  Up  |Right |
 */

[_NORMAL] = LAYOUT_planck_grid(
    CTL_T(KC_TAB),  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,          KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    CTL_T(KC_MINS),
    BACKTLD,        KC_A,    KC_S,    KC_D,   KC_F,   KC_G,          KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, ALT_T(KC_QUOT),
    GUI_T(KC_NO),   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,          KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, GUI_T(KC_ENT),
    COLEMAK,        KC_LGUI, KC_LALT, SYSTEM, CURSOR, SFT_T(KC_ESC), KC_SPC, ARROWS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* ## Colemak

|C(Tab)|  Q   |  W   |  F   |  P   |  B   |  J   |  L   |  U   |  Y   |  ;:  |C(-_) |
|Bsp/~ |  A   |  R   |  S   |  T   |  G   |  M   |  N   |  E   |  I   |  O   |A('") |
| G(!) |  Z   |  X   |  C   |  D   |  V   |  K   |  H   |  ,   |  .   |  /?  |G(Ent)|
|NORMAL| GUI  | ALT  |System|Cursor|S(Esc)|Space |Arrows| Left | Down |  Up  |Right |
 */

[_COLEMAK] = LAYOUT_planck_grid(
    CTL_T(KC_TAB),  KC_Q,    KC_W,    KC_F,   KC_P,   KC_B,          KC_J,   KC_L,   KC_U,    KC_Y,    KC_SCLN, CTL_T(KC_MINS),
    BACKTLD,        KC_A,    KC_R,    KC_S,   KC_T,   KC_G,          KC_M,   KC_N,   KC_E,    KC_I,    KC_O,    ALT_T(KC_QUOT),
    GUI_T(KC_NO),   KC_Z,    KC_X,    KC_C,   KC_D,   KC_V,          KC_K,   KC_H,   KC_COMM, KC_DOT,  KC_SLSH, GUI_T(KC_ENT),
    NORMAL,         KC_LGUI, KC_LALT, SYSTEM, CURSOR, SFT_T(KC_ESC), KC_SPC, ARROWS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* ## Number

|      |  @   |  +   |  =   |  &   |  |   |  #   |  *   |  ^   |  $   |  %   |      |
|      |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  \`  |
|      |  ~   |  [   |  {   |  (   |      |      |  )   |  }   |  ]   |  \   |      |
|      |      |      |      | \\/  |      |      |      |      |      |      |NORMAL|
 */

[_NUMBER] = LAYOUT_planck_grid(
    _______, KC_AT,   KC_PLUS, KC_EQL,  KC_AMPR, KC_PIPE, KC_HASH, KC_ASTR, KC_CIRC, KC_DLR,  KC_PERC, _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    _______, KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, XXXXXXX, XXXXXXX, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NORMAL
),


/* ## Arrows

|      |      |A(->) |A(->) |      |      |      | P_Up |C(<-) |C(->) |      |      |
|      |C(->) |      |P_Down|      |      | Left | Down |  Up  |Right |C(<-) |      |
|      |      |      |      |      |A(<-) |      |      |      |      |      |      |
|      |      |      |      |      |      |      | \\/  |      |      |      |NORMAL|
 */

[_ARROWS] = LAYOUT_planck_grid(
    _______, XXXXXXX,    A(KC_RGHT), A(KC_RGHT), XXXXXXX, XXXXXXX,    XXXXXXX, KC_PGUP, C(KC_LEFT), C(KC_RGHT), XXXXXXX,    _______,
    _______, C(KC_RGHT), XXXXXXX,    KC_PGDN,    XXXXXXX, XXXXXXX,    KC_LEFT, KC_DOWN,   KC_UP,    KC_RGHT,    C(KC_LEFT), _______,
    _______, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, A(KC_LEFT), XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,
    _______, _______,    _______,    _______,    _______, _______,    _______, _______, _______,    _______,    _______,    NORMAL
),

/* ## Cursor

|      |      |      |Wh_Dn |M_Btn2|      |      |Wh_Dn |      |      |      |      |
|      |M_Acc2|M_Acc1|Wh_Up |M_Btn1|      | M_L  |M_Down| M_Up | M_R  |      |SHIFT |
|      |      |      |      |M_Btn3|      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      | \\/  |      |      |NORMAL|
 */

[_CURSOR] = LAYOUT_planck_grid(
    _______, XXXXXXX, XXXXXXX, KC_WH_D, KC_BTN2, XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, KC_ACL2, KC_ACL1, KC_WH_U, KC_BTN1, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, KC_LSFT,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NORMAL
),

/* ## System

|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
| Caps |      |Pr_Scn|      | Fwd  |      |Brght-| Vol- | Vol+ |Brght+|      |      |
|      |      |      |      |      | Rwd  |      | Mute |P_Trac|N_Trac|      | Play |
|      |      |      | \\/  |      |      |      |      |KBoard|      |      |NORMAL|
 */

[_SYSTEM] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_CAPS, XXXXXXX, KC_PSCR, XXXXXXX, KC_MFFD, XXXXXXX, KC_BRID, KC_VOLD, KC_VOLU, KC_BRIU, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, XXXXXXX, KC_MUTE, KC_MPRV, KC_MNXT, XXXXXXX, KC_MPLY,
    _______, _______, _______, _______, _______, _______, _______, _______, KBOARD,  _______, _______, NORMAL
),

/* ## KBoard

|      |      |      |      |      |RGB_Tg|      |Brght+|      |      |Mode- |      |
|      |      |      |Brght-|      |      | Hue- | Sat- | Sat+ | Hue+ |      |      |
|      |      |      |      |      |      |Mode+ |      |      |      |      |      |
|      |      |      | \\/  |      |      |      |      | \\/  |      |FMWare|NORMAL|
 */

[_KBOARD] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, RGB_VAI, XXXXXXX, XXXXXXX, RGB_RMOD, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI, XXXXXXX,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, FMWARE,   NORMAL
),

/* ## FMWare

|      |      |      |EEPROM|Reset |      |      |      |      |      |      |      |
|      |      |      |Debug |      |      |      |      |      |      |      |      |
|------|      |      |      |      |      |      |      |      |      |      |      |
|      |      |      | \\/  |      |      |      |      | \\/  |      | \\/  |NORMAL|
 */

[_FMWARE] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,   DEBUG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, NORMAL
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool shift_is_pressed = false;
    static bool number_is_active = false;
    static bool number_was_used = false;
    static bool lgui_is_pressed = false;
    static bool lgui_was_used = false;
    static uint16_t number_timer;

    if (number_is_active && record->event.pressed) {
        number_was_used = true;
    }
    if (lgui_is_pressed && record->event.pressed) {
        lgui_was_used = true;
    }

    switch (keycode) {
        case GUI_T(KC_NO):
            if (record->event.pressed) {
                lgui_is_pressed = true;
            } else {
                if (!lgui_was_used) {
                    register_code(KC_LSFT);
                    tap_code(KC_1);
                    unregister_code(KC_LSFT);
                }
                lgui_is_pressed = false;
                lgui_was_used = false;
            }
            return true;

        case SFT_T(KC_ESC):
            if (record->event.pressed) {
                shift_is_pressed = true;
            } else {
                shift_is_pressed = false;
            }
            return true;

        case BACKTLD:
            if (record->event.pressed) {
                if (shift_is_pressed && !number_is_active) {
                    register_code(KC_GRV);
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_GRV);
                unregister_code(KC_BSPC);
            }
            return false;

        case KC_SPC:
            if (record->event.pressed) {
                if (shift_is_pressed && !number_is_active) {
                    unregister_code(KC_LSFT);
                    layer_on(_NUMBER);
                    number_timer = timer_read();
                    number_is_active = true;
                } else {
                    register_code(KC_SPC);
                }
            } else {
                if (number_is_active) {
                    layer_off(_NUMBER);
                    if (shift_is_pressed) {
                        register_code(KC_LSFT);
                    }
                    if (!number_was_used && timer_elapsed(number_timer) < TAPPING_TERM ) {
                        register_code(KC_SPC);
                    }
                    number_is_active = false;
                    number_was_used = false;
                }
                unregister_code(KC_SPC);
            }
            return false;
    }
    return true;
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_T(KC_TAB):
            return true;
        case CTL_T(KC_MINS):
            return true;
        case GUI_T(KC_NO):
            return true;
        case GUI_T(KC_ENT):
            return true;
        case SFT_T(KC_ESC):
            return true;
        default:
            return false;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_T(KC_QUOT):
            return true;
        default:
            return false;
    }
}
