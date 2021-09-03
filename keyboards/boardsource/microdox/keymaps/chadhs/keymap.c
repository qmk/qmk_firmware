/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h" // enables combos.def support

enum layers {
    _COLEMAK_DH,
    _NUM_NAV,
    _FUNCTION,
    _GAMING,
};

/* thumb mods */
#define NUM_BSPC LT(_NUM_NAV,KC_BSPC)
#define FUN_SPC LT(_FUNCTION,KC_SPC)
#define CMD_TAB CMD_T(KC_TAB)
#define GAMING TG(_GAMING)

/* home row mods */
#define HOME_A SFT_T(KC_A)
#define HOME_R CTL_T(KC_R)
#define HOME_S OPT_T(KC_S)
#define HOME_T CMD_T(KC_T)
#define HOME_Z SFT_T(KC_Z)
#define HOME_BT SFT_T(KC_GRV)
#define HOME_N CMD_T(KC_N)
#define HOME_E OPT_T(KC_E)
#define HOME_I CTL_T(KC_I)
#define HOME_O SFT_T(KC_O)
#define HOME_SL SFT_T(KC_SLSH)
#define HOME_DWN CMD_T(KC_DOWN)
#define HOME_UP OPT_T(KC_UP)
#define HOME_RGT CTL_T(KC_RGHT)
#define HOME_QT SFT_T(KC_QUOT)
#define HOME_BSL SFT_T(KC_BSLS)

/* layer definitions */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK_DH] = LAYOUT_split_3x5_3(
/*
 ,------.------.------.------.------.            ,------.------.------.------.------.
 | Q    | W    | F    | P    | B    |            | J    | L    | U    | Y    | ; :  |
 |      |      |      |      |      |            |      |      |      |      |      |
 |------+------+------+------+------|            |------+------+------+------+------|
 | A    | R    | S    | T    | G    |            | M    | N    | E    | I    | O    |
 | SFT  | CTL  | OPT  | CMD  |      |            |      | CMD  | OPT  | CTL  | SFT  |
 |------+------+------+------+------|            |------+------+------+------+------|
 | Z    | X    | C    | D    | V    |            | K    | H    | , <  | . >  | / ?  |
 | SFT  |      |      |      |      |            |      |      |      |      | SFT  |
 `------'------'------'------'------'            `------'------'------'------'------'
                  .------.------.------.      .------.------.------.
                  | XXX  | TAB  | BSPC |      | SPC  | ENT  | XXX  |
                  |      | CMD  | LNUM |      | LFUN |      |      |
                  '------'------'------'      '------'------'------'
*/
  KC_Q,   KC_W,   KC_F,    KC_P,     KC_B,         KC_J,    KC_L,   KC_U,    KC_Y,   KC_SCLN,
  HOME_A, HOME_R, HOME_S,  HOME_T,   KC_G,         KC_M,    HOME_N, HOME_E,  HOME_I, HOME_O,
  HOME_Z, KC_X,   KC_C,    KC_D,     KC_V,         KC_K,    KC_H,   KC_COMM, KC_DOT, HOME_SL,
                  XXXXXXX, CMD_TAB,  NUM_BSPC,     FUN_SPC, KC_ENT, XXXXXXX
),

[_NUM_NAV] = LAYOUT_split_3x5_3(
/*
 ,------.------.------.------.------.            ,------.------.------.------.------.
 | 1 !  | 2 @  | 3 #  | 4 $  | 5 %  |            | 6 ^  | 7 &  | 8 *  | 9 (  | 0 )  |
 |      |      |      |      |      |            |      |      |      |      |      |
 |------+------+------+------+------|            |------+------+------+------+------|
 | ` ~  |      |      |      |      |            | ←    | ↓    | ↑    | →    | ' "  |
 | SFT  | CTL  | OPT  | CMD  |      |            |      | CMD  | OPT  | CTL  | SFT  |
 |------+------+------+------+------|            |------+------+------+------+------|
 | Z    |      |      |      |      |            | - _  | = +  | [ {  | ] }  | \ |  |
 | SFT  |      |      |      |      |            |      |      |      |      | SFT  |
 `------'------'------'------'------'            `------'------'------'------'------'
                  .------.------.------.      .------.------.------.
                  | XXX  | ESC  | ↓↓↓  |      | ↓↓↓  | ↓↓↓  | XXX  |
                  |      |      |      |      |      |      |      |
                  '------'------'------'      '------'------'------'
*/
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,     KC_8,    KC_9,     KC_0,
  HOME_BT, KC_LCTL, KC_LOPT, KC_LCMD, XXXXXXX,      KC_LEFT, HOME_DWN, HOME_UP, HOME_RGT, HOME_QT,
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_MINS, KC_EQL,   KC_LBRC, KC_RBRC,  HOME_BSL,
                    XXXXXXX, KC_ESC,  KC_TRNS,      KC_TRNS, KC_TRNS,  XXXXXXX
),

[_FUNCTION] = LAYOUT_split_3x5_3(
/*
 ,------.------.------.------.------.            ,------.------.------.------.------.
 | F1   | F2   | F3   | F4   | F5   |            | F6   | F7   | F8   | F9   | F10  |
 |      |      |      |      |      |            |      |      |      |      |      |
 |------+------+------+------+------|            |------+------+------+------+------|
 |      |      |      |      |      |            |      |      |      | F11  | F12  |
 |      |      |      |      |      |            |      |      |      |      |      |
 |------+------+------+------+------|            |------+------+------+------+------|
 | RGB  | RGB  | RGB  | RGB- | RGB+ |            |      |      |      |      |      |
 | TGGL | RMOD | MOD  |      |      |            |      |      |      |      |      |
 `------'------'------'------'------'            `------'------'------'------'------'
                  .------.------.------.      .------.------.------.
                  | XXX  | ESC  | DEL  |      | ↓↓↓  | GAME | XXX  |
                  |      |      |      |      |      |      |      |
                  '------'------'------'      '------'------'------'
*/
  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,
  RGB_TOG, RGB_RMOD, RGB_MOD, RGB_VAD, RGB_VAI,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GAMING,
                     XXXXXXX, KC_ESC,  KC_DEL,       KC_TRNS, GAMING,  XXXXXXX
),

[_GAMING] = LAYOUT_split_3x5_3(
/*
 ,------.------.------.------.------.            ,------.------.------.------.------.
 | TAB  | Q    | W    | E    | R    |            | Y    | U    | I    | O    | P    |
 |      |      |      |      |      |            |      |      |      |      |      |
 |------+------+------+------+------|            |------+------+------+------+------|
 | ESC  | A    | S    | D    | F    |            | H    | J    | K    | L    | ; :  |
 |      |      |      |      |      |            |      |      |      |      |      |
 |------+------+------+------+------|            |------+------+------+------+------|
 |      | Z    | X    | C    | V    |            | N    | M    | , <  | . >  | \ |  |
 | SFT  |      |      |      |      |            |      |      |      |      |      |
 `------'------'------'------'------'            `------'------'------'------'------'
                  .------.------.------.      .------.------.------.
                  | XXX  |      | SPC  |      | ↓↓↓  | GAME | XXX  |
                  |      | CMD  |      |      |      |      |      |
                  '------'------'------'      '------'------'------'
*/
  KC_TAB,  KC_Q, KC_W,    KC_E,    KC_R,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  KC_ESC,  KC_A, KC_S,    KC_D,    KC_F,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
  KC_LSFT, KC_Z, KC_X,    KC_C,    KC_V,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_BSLS,
                 XXXXXXX, KC_LCMD, KC_SPC,      KC_TRNS, GAMING,  XXXXXXX
),
};

/* per key configuration */
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CMD_TAB: /* make CMD SPC faster */
        return false;
    default:
        return true;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    /* adjust home row key timing to prevent letter rolls triggering modifiers */
    case HOME_A:
    case HOME_R:
    case HOME_S:
    case HOME_T:
    case HOME_Z:
    case HOME_N:
    case HOME_E:
    case HOME_I:
    case HOME_O:
        return TAPPING_TERM + 150;
    default:
        return TAPPING_TERM;
    }
}
