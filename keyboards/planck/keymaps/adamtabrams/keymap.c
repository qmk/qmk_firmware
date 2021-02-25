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
#define NUMBER TT(_NUMBER)
#define ARROWS TT(_ARROWS)
#define CURSOR TT(_CURSOR)
#define SYSTEM TT(_SYSTEM)
#define KBOARD MO(_KBOARD)
#define FMWARE MO(_FMWARE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ## Normal

| C(Tab) |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |C(-_) |
|Backsp/~|  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;:  |A('") |
| G(=+)  |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /?  |G(Ent)|
|  CTRL  | GUI  | ALT  |System|Number|S(Esc)|Space |Arrows|Cursor| GUI  |      |Normal|
 */

[_NORMAL] = LAYOUT_planck_grid(
    CTL_T(KC_TAB), KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,          KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    CTL_T(KC_MINS),
    BACKTLD,       KC_A,    KC_S,    KC_D,   KC_F,   KC_G,          KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, ALT_T(KC_QUOT),
    GUI_T(KC_EQL), KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,          KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, GUI_T(KC_ENT),
    KC_LCTRL,      KC_LGUI, KC_LALT, SYSTEM, NUMBER, SFT_T(KC_ESC), KC_SPC, ARROWS, CURSOR,  KC_RGUI, XXXXXXX, NORMAL
),

/* ## Number

|      |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |  )   |      |
|      |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  \`  |
|      |  ~   |  [   |  ]   |  =   |  +   |  -   |  |   |  {   |  }   |  \   |      |
|      |      |      |      | \\/  |      |      |      |      |      |      |      |
 */

[_NUMBER] = LAYOUT_planck_grid(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    _______, KC_TILD, KC_LBRC, KC_RBRC, KC_EQL,  KC_PLUS, KC_MINS, KC_PIPE, KC_LCBR, KC_RCBR, KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


/* ## Arrows

|      |      |A(->) |A(->) |      |      |      | P_Up |      |      |      |      |
|      |      |      |P_Down|      |      | Left | Down |  Up  |Right |      |      |
|      |      |      |      |      |A(<-) |      |      |      |      |      |      |
|      |      |      |      |      |      |      | \\/  |      |      |      |      |
 */

[_ARROWS] = LAYOUT_planck_grid(
    _______, XXXXXXX, A(KC_RGHT), A(KC_RGHT), XXXXXXX, XXXXXXX,    XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX,    KC_PGDN,    XXXXXXX, XXXXXXX,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX, A(KC_LEFT), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______,    _______,    _______, _______,    _______, _______, _______, _______, _______, _______
),

/* ## Cursor

|      |      |      |Wh_Dn |M_Btn2|      |      |Wh_Dn |      |      |      |      |
|      |M_Acc2|M_Acc1|Wh_Up |M_Btn1|      | M_L  |M_Down| M_Up | M_R  |      |      |
|      |      |      |      |M_Btn3|      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      | \\/  |      |      |      |
 */

[_CURSOR] = LAYOUT_planck_grid(
    _______, XXXXXXX, XXXXXXX, KC_WH_D, KC_BTN2, XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, KC_ACL2, KC_ACL1, KC_WH_U, KC_BTN1, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* ## System

|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
| Caps |      |Pr_Scn|      | Fwd  |      |Brght-| Vol- | Vol+ |Brght+|      |      |
|      |      |      |      |      | Rwd  |      | Mute |P_Trac|N_Trac|      | Play |
|      |      |      | \\/  |      |      |      |      |KBoard|      |      |      |
 */

[_SYSTEM] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_CAPS, XXXXXXX, KC_PSCR, XXXXXXX, KC_MFFD, XXXXXXX, KC_BRID, KC_VOLD, KC_VOLU, KC_BRIU, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, XXXXXXX, KC_MUTE, KC_MPRV, KC_MNXT, XXXXXXX, KC_MPLY,
    _______, _______, _______, _______, _______, _______, _______, _______, KBOARD,  _______, _______, _______
),

/* ## KBoard

|      |      |      |      |      |RGB_Tg|      |Brght+|      |      |Mode- |      |
|      |      |      |Brght-|      |      | Hue- | Sat- | Sat+ | Hue+ |      |      |
|      |      |      |      |      |      |Mode+ |      |      |      |      |      |
|      |      |      | \\/  |      |      |      |      | \\/  |      |FMWare|      |
 */

[_KBOARD] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, RGB_VAI, XXXXXXX, XXXXXXX, RGB_RMOD, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI, XXXXXXX,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, FMWARE,   _______
),

/* ## FMWare

|      |      |      |EEPROM|Reset |      |      |      |      |      |      |      |
|      |      |      |Debug |      |      |      |      |      |      |      |      |
|------|      |      |      |      |      |      |      |      |      |      |      |
|      |      |      | \\/  |      |      |      |      | \\/  |      | \\/  |      |
 */

[_FMWARE] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,   DEBUG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool shift_is_pressed = false;

    switch (keycode) {
        case SFT_T(KC_ESC):
            if(record->event.pressed){
                shift_is_pressed = true;
            } else {
                shift_is_pressed = false;
            }
            return true;
        case BACKTLD:
            if(record->event.pressed){
                if(shift_is_pressed) {
                    register_code(KC_GRV);
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_GRV);
                unregister_code(KC_BSPC);
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
        case ALT_T(KC_QUOT):
            return true;
        case GUI_T(KC_EQL):
            return true;
        case GUI_T(KC_ENT):
            return true;
        case SFT_T(KC_ESC):
            return true;
        default:
            return false;
    }
}
