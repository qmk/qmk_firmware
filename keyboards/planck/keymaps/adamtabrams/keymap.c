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
  _QWERTY,
  _COLEMAK,
  _SIMPLE,
  _NUMBER,
  _ARROWS,
  _CURSOR,
  _SYSTEM,
  _KBOARD,
  _FMWARE
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  SIMPLE,
  NORMAL
};

#define ARROWS TT(_ARROWS)
#define CURSOR TT(_CURSOR)
#define SYSTEM TT(_SYSTEM)
#define KBOARD MO(_KBOARD)
#define FMWARE MO(_FMWARE)

#define NUMSPAC LT(_NUMBER, KC_SPC)
#define SHFTESC LSFT_T(KC_ESC)
#define SFTENTR SFT_T(KC_ENT)

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

#define ALTRGHT A(KC_RGHT)
#define ALTLEFT A(KC_LEFT)
#define CTLRGHT C(KC_RGHT)
#define CTLLEFT C(KC_LEFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ## Qwerty

| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  -_  |
| Bsp  | A(A) | G(S) | S(D) | C(F) |   G  |   H  | C(J) | S(K) | G(L) | A(;) |  '"  |
|   !  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Enter|
| CTRL |  GUI |  ALT |System|Cursor|S(Esc)|N(Spc)|Arrows| Left | Down |  Up  | Right|
 */

[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_BSPC, ALT__A,  GUI__S,  SFT__D, CTL__F, KC_G,    KC_H,    CTL__J, SFT__K,  GUI__L,  ALTSCLN, KC_QUOT,
    KC_EXLM, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, KC_LGUI, KC_LALT, SYSTEM, CURSOR, SHFTESC, NUMSPAC, ARROWS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* ## Colemak

| Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  |  -_  |
| Bsp  | A(A) | G(R) | S(S) | C(T) |   G  |   M  | C(N) | S(E) | G(I) | A(O) |  '"  |
|   !  |   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  | Enter|
| CTRL |  GUI |  ALT |System|Cursor|S(Esc)|N(Spc)|Arrows| Left | Down |  Up  | Right|
 */

[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,   KC_P,   KC_B,    KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_MINS,
    KC_BSPC, ALT__A,  GUI__R,  SFT__S, CTL__T, KC_G,    KC_M,    CTL__N, SFT__E,  GUI__I,  ALT__O,  KC_QUOT,
    KC_EXLM, KC_Z,    KC_X,    KC_C,   KC_D,   KC_V,    KC_K,    KC_H,   KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, KC_LGUI, KC_LALT, SYSTEM, CURSOR, SHFTESC, NUMSPAC, ARROWS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* ## Simple

| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bsp  |
| Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '"  |
| SHFT |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |S(Ent)|
| CTRL |  GUI |  ALT |System|Cursor|  Spc |N(Spc)|Arrows| Left | Down |  Up  | Right|
 */

[_SIMPLE] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, SFTENTR,
    KC_LCTL, KC_LGUI, KC_LALT, SYSTEM, CURSOR, KC_SPC,  NUMSPAC, ARROWS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* ## Number

|      |  \|  |  &   |  =   |  +   |  @   |  %   |  #   |  *   |  $   |  ^   |      |
|      |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  \`  |
|      |      |  [   |  {   |  (   |  ~   |  !   |  )   |  }   |  ]   |  \   |      |
|      |      |      |      |      |      | \\/  |      |      |      |      |Normal|
 */

[_NUMBER] = LAYOUT_planck_grid(
    _______, KC_PIPE, KC_AMPR, KC_EQL,  KC_PLUS, KC_AT,   KC_PERC, KC_HASH, KC_ASTR, KC_DLR,  KC_CIRC, _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    _______, XXXXXXX, KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, KC_EXLM, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NORMAL
),


/* ## Arrows

|      |      |A(->) |      |      |A(<-) |      | P_Up | P_Up |C(->) |      |      |
|      |      |      |P_Down|      |      | Left | Down |  Up  |Right |C(<-) |      |
|      |      |      |      |P_Down|A(<-) |      |      |      |      |      |      |
|      |      |      |      |      |      |      | \\/  |      |      |      |Normal|
 */

[_ARROWS] = LAYOUT_planck_grid(
    _______, _______, ALTRGHT, _______, _______, ALTLEFT, _______, KC_PGUP, KC_PGUP, CTLRGHT, _______, _______,
    _______, _______, _______, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, CTLLEFT, _______,
    _______, _______, _______, _______, KC_PGDN, ALTLEFT, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NORMAL
),

/* ## Cursor

|      |      |      |Wh_Dn |M_Btn2|      |      |Wh_Dn |Wh_Dn |      |      |      |
|      |M_Acc2|M_Acc1|Wh_Up |M_Btn1|      | M_L  |M_Down| M_Up | M_R  |      |      |
|      |      |      |      |Wh_Up |      |      |      |      |      |      |      |
|      |      |      |      | \\/  |      |      |      |      |      |      |Normal|
 */

[_CURSOR] = LAYOUT_planck_grid(
    _______, _______, _______, KC_WH_D, KC_BTN2, _______, _______, KC_WH_D, KC_WH_D, _______, _______, _______,
    _______, KC_ACL2, KC_ACL1, KC_WH_U, KC_BTN1, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
    _______, _______, _______, _______, KC_WH_U, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NORMAL
),

/* ## System

|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
|      |      |Pr_Scn|Pr_Scn|      |      |Brght-| Vol- | Vol+ |Brght+| Mute |      |
|      |      |      |      |      |      |      | Mute |P_Trac|N_Trac|      | Play |
|KBoard|      |      | \\/  |      |      |      |      |Simple|Qwerty|Colemk|Normal|
 */

[_SYSTEM] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, XXXXXXX, KC_PSCR, KC_PSCR, XXXXXXX, XXXXXXX, KC_BRID, KC_VOLD, KC_VOLU, KC_BRIU, KC_MUTE, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_MPRV, KC_MNXT, XXXXXXX, KC_MPLY,
    KBOARD,  _______, _______, _______, _______, _______, _______, _______, SIMPLE,  QWERTY,  COLEMAK, NORMAL
),

/* ## KBoard

|------|      |      |      |      |      |      |      |      |      |      |      |
|      |      |      |      |      |      | Hue- | Sat- | Sat+ | Hue+ |Mode+ |      |
|      |      |      |      |      |      |      |Mode- |Brght-|Brght+|      |RGB_Tg|
| \\/  |      |      | \\/  |      |      |      |      |      |      |      |FMWare|
 */

[_KBOARD] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD,  RGB_SAI, RGB_HUI, RGB_MOD, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD, RGB_VAD, RGB_VAI, XXXXXXX, RGB_TOG,
    _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, FMWARE
),

/* ## FMWare

|      |      |      |EEPROM|Reset |      |      |      |      |      |      |      |
|      |      |Reset |Debug |      |      |      |      |      |      |      |      |
|------|      |      |      |      |      |      |      |      |      |      |      |
| \\/  |      |      | \\/  |      |      |      |      |      |      |      | \\/  |
 */

[_FMWARE] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, RESET,   DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            set_single_persistent_default_layer(_QWERTY);
            return true;

        case COLEMAK:
            set_single_persistent_default_layer(_COLEMAK);
            return true;

        case SIMPLE:
            set_single_persistent_default_layer(_SIMPLE);
            return true;

        case NORMAL:
            layer_clear();
            return false;
    }
    return true;
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SHFTESC:
        case NUMSPAC:
        case SFTENTR:
        case ALT__A:
        case ALTSCLN:
        case ALT__O:
        case GUI__S:
        case GUI__L:
        case GUI__R:
        case GUI__I:
        case SFT__D:
        case SFT__K:
        case SFT__S:
        case SFT__E:
        case CTL__F:
        case CTL__J:
        case CTL__T:
        case CTL__N:
            return true;
        default:
            return false;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT__A:
        case ALTSCLN:
        case ALT__O:
        case GUI__S:
        case GUI__L:
        case GUI__R:
        case GUI__I:
        case SFT__D:
        case SFT__K:
        case SFT__S:
        case SFT__E:
        case CTL__F:
        case CTL__J:
        case CTL__T:
        case CTL__N:
            return true;
        default:
            return false;
    }
}
