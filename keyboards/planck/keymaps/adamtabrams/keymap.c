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
  _COLEMK,
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
#define COLEMK TO(_COLEMK)
#define ARROWS TT(_ARROWS)
#define CURSOR TT(_CURSOR)
#define SYSTEM TT(_SYSTEM)
#define KBOARD MO(_KBOARD)
#define FMWARE MO(_FMWARE)

#define NUMSPAC LT(_NUMBER, KC_SPC)
#define SHFTESC LSFT_T(KC_ESC)

#define CTRLTAB CTL_T(KC_TAB)
#define CTRLMIN CTL_T(KC_MINS)
#define SFTEXLM SFT_T(KC_EXLM)
#define SFTENTR SFT_T(KC_ENT)

#define ALTRGHT A(KC_RGHT)
#define ALTLEFT A(KC_LEFT)
#define CTLRGHT C(KC_RGHT)
#define CTLLEFT C(KC_LEFT)

#define ALT__A  ALT_T(KC_A)
#define ALTSCLN ALT_T(KC_SCLN)
#define ALT__O  ALT_T(KC_O)
#define GUI__S  GUI_T(KC_S)
#define GUI__L  GUI_T(KC_L)
#define GUI__R  GUI_T(KC_R)
#define GUI__I  GUI_T(KC_I)
#define SFT__D  SFT_T(KC_D)
#define SFT__K  SFT_T(KC_K)
#define SFT__S  SFT_T(KC_S)
#define SFT__E  SFT_T(KC_E)
#define CTL__F  CTL_T(KC_F)
#define CTL__J  CTL_T(KC_J)
#define CTL__T  CTL_T(KC_T)
#define CTL__N  CTL_T(KC_N)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ## Normal

|C(Tab)|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | C(-) |
| Bsp/~| A(A) | G(S) | S(D) | C(F) |   G  |   H  | C(J) | S(K) | G(L) | A(;) |  '"  |
| S(!) |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |S(Ent)|
|COLMAK|      |      |System|Cursor|S(Esc)|N(Spc)|Arrows|      |      |      |      |
 */

[_NORMAL] = LAYOUT_planck_grid(
    CTRLTAB, KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    CTRLMIN,
    BACKTLD, ALT__A,  GUI__S,  SFT__D, CTL__F, KC_G,    KC_H,    CTL__J, SFT__K,  GUI__L,  ALTSCLN, KC_QUOT,
    SFTEXLM, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, SFTENTR,
    COLEMK,  _______, _______, SYSTEM, CURSOR, SHFTESC, NUMSPAC, ARROWS, _______, _______, _______, _______
),

/* ## Colemak

|C(Tab)|   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | C(-) |
| Bsp/~| A(A) | G(R) | S(S) | C(T) |   G  |   M  | C(N) | S(E) | G(I) | A(O) |  '"  |
| S(!) |   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  |S(Ent)|
|QWERTY|      |      |System|Cursor|S(Esc)|N(Spc)|Arrows|      |      |      |      |
 */

[_COLEMK] = LAYOUT_planck_grid(
    CTRLTAB, KC_Q,    KC_W,    KC_F,   KC_P,   KC_B,    KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN, CTRLMIN,
    BACKTLD, ALT__A,  GUI__R,  SFT__S, CTL__T, KC_G,    KC_M,    CTL__N, SFT__E,  GUI__I,  ALT__O,  KC_QUOT,
    SFTEXLM, KC_Z,    KC_X,    KC_C,   KC_D,   KC_V,    KC_K,    KC_H,   KC_COMM, KC_DOT,  KC_SLSH, SFTENTR,
    NORMAL,  _______, _______, SYSTEM, CURSOR, SHFTESC, NUMSPAC, ARROWS, _______, _______, _______, _______
),

/* ## Number

|      |  @   |  +   |  =   |  &   |  |   |  #   |  *   |  ^   |  $   |  %   |      |
|      |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  \`  |
|      |  ~   |  [   |  {   |  (   |  !   |  =   |  )   |  }   |  ]   |  \   |      |
|      |      |      |      | \\/  |      |      |      |      |      |      |NORMAL|
 */

[_NUMBER] = LAYOUT_planck_grid(
    _______, KC_AT,   KC_PLUS, KC_EQL,  KC_AMPR, KC_PIPE, KC_HASH, KC_ASTR, KC_CIRC, KC_DLR,  KC_PERC, _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    _______, KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_EXLM, KC_EQL,  KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NORMAL
),


/* ## Arrows

|      |      |A(->) |A(->) |      |      |      | P_Up |C(<-) |C(->) |      |      |
|      |C(->) |      |P_Down|      |      | Left | Down |  Up  |Right |C(<-) |      |
|      |      |      |      |      |A(<-) |      |      |      |      |      |      |
|      |      |      |      |      |      |      | \\/  |      |      |      |NORMAL|
 */

[_ARROWS] = LAYOUT_planck_grid(
    _______, XXXXXXX, ALTRGHT, ALTRGHT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, CTLLEFT, CTLRGHT, XXXXXXX, _______,
    _______, CTLRGHT, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, CTLLEFT, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ALTLEFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NORMAL
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

    switch (keycode) {
        case SHFTESC:
            if (record->event.pressed) {
                shift_is_pressed = true;
            } else {
                shift_is_pressed = false;
            }
            return true;

        case SFTEXLM:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(KC_EXLM);
                }
                return false;
            }
            return true;

        case BACKTLD:
            if (record->event.pressed) {
                if (shift_is_pressed) {
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
        case CTRLTAB:
            return true;
        case CTRLMIN:
            return true;
        case SFTENTR:
            return true;
        case SFTEXLM:
            return true;
        case SHFTESC:
            return true;
        case NUMSPAC:
            return true;
        case ALT__A:
            return true;
        case ALTSCLN:
            return true;
        case ALT__O:
            return true;
        case GUI__S:
            return true;
        case GUI__L:
            return true;
        case GUI__R:
            return true;
        case GUI__I:
            return true;
        case SFT__D:
            return true;
        case SFT__K:
            return true;
        case SFT__S:
            return true;
        case SFT__E:
            return true;
        case CTL__F:
            return true;
        case CTL__J:
            return true;
        case CTL__T:
            return true;
        case CTL__N:
            return true;
        default:
            return false;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT__A:
            return true;
        case ALTSCLN:
            return true;
        case ALT__O:
            return true;
        case GUI__S:
            return true;
        case GUI__L:
            return true;
        case GUI__R:
            return true;
        case GUI__I:
            return true;
        case SFT__D:
            return true;
        case SFT__K:
            return true;
        case SFT__S:
            return true;
        case SFT__E:
            return true;
        case CTL__F:
            return true;
        case CTL__J:
            return true;
        case CTL__T:
            return true;
        case CTL__N:
            return true;
        default:
            return false;
    }
}
