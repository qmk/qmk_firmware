/* Copyright 2019 Markus Weimar
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
#include "keymap_german.h"

#define ________ KC_TRNS
#define ___xx___ KC_NO

enum my_layers {
    _QWZ,
    _QWY,
    _GAM,
    _FN1,
    _FN2,
    _FN3,
};

enum my_keycodes {
    QWERTZ = SAFE_RANGE,
    QWERTY,
    GAMING,
    FN1,
    FN2,
    FN3
};

enum my_ucis {
    UNI_LNX,
    UNI_MAC,
    UNI_WIN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTZ
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | 1 !    | 2 "    | 3 §    | 4 $    | 5 %    | 6 &    | Mute   | Vol-   | Vol+   | 7 /    | 8 (    | 9 )    | 0 =    | ẞ ?    | Ü      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Esc    | Q      | W      | E      | R      | T      | Home   | Play   | End    | Z      | U      | I      | O      | P      | Ä      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LShift | A      | S      | D      | F      | G      | Pg Up  | Up     | Pg Dn  | H      | J      | K      | L      | Ö      | RShift |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCtrl  | Y      | X      | C      | V      | B      | Left   | Down   | Right  | N      | M      | , ;    | . :    | - _    | RCtrl  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Caps   | Fn3    | LGUI   | LAlt   | Fn2    | Fn1    | Tab    | Del    | Enter  | Space  | Bksp   | LAlt   | LGUI   | Fn3    | Ins    |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_QWZ] = LAYOUT_ortho_5x15(
DE_1,     DE_2,     DE_3,     DE_4,     DE_5,     DE_6,     KC_MUTE,  KC_VOLD,  KC_VOLU,  DE_7,     DE_8,     DE_9,     DE_0,     DE_SS,    DE_UDIA,
KC_ESC,   DE_Q,     DE_W,     DE_E,     DE_R,     DE_T,     KC_HOME,  KC_MPLY,  KC_END,   DE_Z,     DE_U,     DE_I,     DE_O,     DE_P,     DE_ADIA,
KC_LSFT,  DE_A,     DE_S,     DE_D,     DE_F,     DE_G,     KC_PGUP,  KC_UP,    KC_PGDN,  DE_H,     DE_J,     DE_K,     DE_L,     DE_ODIA,  KC_RSFT,
KC_LCTL,  DE_Y,     DE_X,     DE_C,     DE_V,     DE_B,     KC_LEFT,  KC_DOWN,  KC_RIGHT, DE_N,     DE_M,     DE_COMM,  DE_DOT,   DE_MINS,  KC_RCTL,
KC_CAPS,  MO(_FN3), KC_LGUI,  KC_LALT,  MO(_FN2), MO(_FN1), KC_TAB,   KC_DEL,   KC_ENT,   KC_SPC,   KC_BSPC,  KC_LALT,  KC_LGUI,  MO(_FN3), KC_INS
),

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | Y      |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | Z      |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_QWY] = LAYOUT_ortho_5x15(
DE_1,     DE_2,     DE_3,     DE_4,     DE_5,     DE_6,     KC_MUTE,  KC_VOLD,  KC_VOLU,  DE_7,     DE_8,     DE_9,     DE_0,     DE_SS,    DE_UDIA,
KC_ESC,   DE_Q,     DE_W,     DE_E,     DE_R,     DE_T,     KC_HOME,  KC_MPLY,  KC_END,   DE_Y,     DE_U,     DE_I,     DE_O,     DE_P,     DE_ADIA,
KC_LSFT,  DE_A,     DE_S,     DE_D,     DE_F,     DE_G,     KC_PGUP,  KC_UP,    KC_PGDN,  DE_H,     DE_J,     DE_K,     DE_L,     DE_ODIA,  KC_RSFT,
KC_LCTL,  DE_Z,     DE_X,     DE_C,     DE_V,     DE_B,     KC_LEFT,  KC_DOWN,  KC_RIGHT, DE_N,     DE_M,     DE_COMM,  DE_DOT,   DE_MINS,  KC_RCTL,
KC_CAPS,  MO(_FN3), KC_LGUI,  KC_LALT,  MO(_FN2), MO(_FN1), KC_TAB,   KC_DEL,   KC_ENT,   KC_SPC,   KC_BSPC,  KC_LALT,  KC_LGUI,  MO(_FN3), KC_INS
),

/* GAMING
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | Y      |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | Z      |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Fn2    |        |        |        | Space  |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_GAM] = LAYOUT_ortho_5x15(
DE_1,     DE_2,     DE_3,     DE_4,     DE_5,     DE_6,     KC_MUTE,  KC_VOLD,  KC_VOLU,  DE_7,     DE_8,     DE_9,     DE_0,     DE_SS,    DE_UDIA,
KC_ESC,   DE_Q,     DE_W,     DE_E,     DE_R,     DE_T,     KC_HOME,  KC_MPLY,  KC_END,   DE_Y,     DE_U,     DE_I,     DE_O,     DE_P,     DE_ADIA,
KC_LSFT,  DE_A,     DE_S,     DE_D,     DE_F,     DE_G,     KC_PGUP,  KC_UP,    KC_PGDN,  DE_H,     DE_J,     DE_K,     DE_L,     DE_ODIA,  KC_RSFT,
KC_LCTL,  DE_Z,     DE_X,     DE_C,     DE_V,     DE_B,     KC_LEFT,  KC_DOWN,  KC_RIGHT, DE_N,     DE_M,     DE_COMM,  DE_DOT,   DE_MINS,  KC_RCTL,
MO(_FN2), MO(_FN3), KC_LGUI,  KC_LALT,  KC_SPC,   MO(_FN1), KC_TAB,   KC_DEL,   KC_ENT,   KC_SPC,   KC_BSPC,  KC_LALT,  KC_LGUI,  MO(_FN3), KC_INS
),

/* FN1
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | Prev   | Play   | Next   | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | @      | ~      | €      | ´      | `      |        |        |        | \      | {      | }      | +      | *      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | "      | '      | ‚      | ‘      | ’      |        |        |        | |      | [      | ]      | !      | ?      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | °      | ^      | „      | “      | ”      |        |        |        | #      | <      | >      | …      | – EN   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_FN1] = LAYOUT_ortho_5x15(
KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
________, DE_AT,    DE_TILD,  DE_EURO,  DE_ACUT,  DE_GRV,   ________, ___xx___, ________, DE_BSLS,  DE_LCBR,  DE_RCBR,  DE_PLUS,  DE_ASTR,  ___xx___,
________, DE_DQUO,  DE_QUOT,  UC(L'‚'), UC(L'‘'), UC(L'’'), ________, ________, ________, DE_PIPE,  DE_LBRC,  DE_RBRC,  DE_EXLM,  DE_QUES,  ________,
________, DE_DEG,   DE_CIRC,  UC(L'„'), UC(L'“'), UC(L'”'), ________, ________, ________, DE_HASH,  DE_LABK,  DE_RABK,  UC(L'…'), UC(L'–'), ________,
___xx___, ________, ________, ________, ________, ________, ________, ________, ________, ________, ________, ________, ________, ________, ________
),

/* FN2
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        | %      | (      | )      | P/     | P*     | P-     | Print  | Scroll | Pause  | ẞ      | − MNS  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | Mute   | Vol-   | Vol+   | Bspc   | P7     | P8     | P9     | P+     | WH_U   | MS_U   | WH_D   | ×      | ÷      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | App    | ACL2   | ACL1   | ACL0   | Space  | P4     | P5     | P6     | WH_L   | MS_L   | MS_D   | MS_R   | WH_R   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | Prev   | Play   | Next   | Tab    | P1     | P2     | P3     | PEnter | BTN1   | BTN2   | BTN3   | — EM   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Fn2    |        |        |        |        | PEnter | P0     | . :    | P,     | BTN1   | BTN2   | BTN3   |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_FN2] = LAYOUT_ortho_5x15(
___xx___, ___xx___, ___xx___, ___xx___, DE_PERC,  DE_LPRN,  DE_RPRN,  KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PSCR,  KC_LSCR,  KC_PAUS,  UC(L'ẞ'), UC(L'−'),
________, ___xx___, KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_BSPC,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  KC_WH_U,  KC_MS_U,  KC_WH_D,  UC(L'×'), UC(L'÷'),
________, KC_APP,   KC_ACL2,  KC_ACL1,  KC_ACL0,  KC_SPC,   KC_P4,    KC_P5,    KC_P6,    KC_WH_L,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_R,  ________,
________, ___xx___, KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_TAB,   KC_P1,    KC_P2,    KC_P3,    KC_PENT,  KC_BTN1,  KC_BTN2,  KC_BTN3,  UC(L'—'), ________,
MO(_FN2), ________, ________, ________, ________, KC_PENT,  KC_P0,    DE_DOT,   KC_PDOT,  KC_BTN1,  KC_BTN2,  KC_BTN3,  ________, ________, ________
),

/* FN3
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F13    | F14    | F15    | F16    | F17    | F18    | U LNX  | U WIN  | U MAC  | F19    | F20    | F21    | F22    | F23    | F24    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | QWERTZ | QWERTY | GAMING |        |        | L TOG  | L MP   | L MOD  |        | Pg Up  | Up     | Pg Dn  |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | ›      | ‹      |        | L HUI  | L SAI  | L VAI  | Home   | Left   | Down   | Right  | End    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | »      | «      |        | L HUD  | L SAD  | L VAD  | NumSp  | ThinSp | NaNbSp | NbSp   | NbHyph |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        | Reset  |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
[_FN3] = LAYOUT_ortho_5x15(
KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   UNI_LNX,  UNI_WIN,  UNI_MAC,  KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,
________, QWERTZ,   QWERTY,   GAMING,   ___xx___, ___xx___, RGB_TOG,  RGB_M_P,  RGB_MOD,  ___xx___, KC_PGUP,  KC_UP,    KC_PGDN,  ___xx___, ___xx___,
________, ___xx___, ___xx___, UC(L'›'), UC(L'‹'), ___xx___, RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_END,   ________,
________, ___xx___, ___xx___, UC(L'»'), UC(L'«'), ___xx___, RGB_HUD,  RGB_SAD,  RGB_VAD,  UC(L' '), UC(L' '), UC(L' '), UC(L' '), UC(L'‑'), ________,
___xx___, ________, ________, ________, ________, ________, ________, RESET,    ________, ________, ________, ________, ________, ________, ________
)

};

void matrix_init_user(){
    set_unicode_input_mode(UC_LNX);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case QWERTZ:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWZ);
            }
            return false;
            break;
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWY);
            }
            return false;
            break;
        case GAMING:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAM);
            }
            return false;
            break;
        case UNI_LNX:
            set_unicode_input_mode(UC_LNX);
            return false;
            break;
        case UNI_WIN:
            set_unicode_input_mode(UC_WINC);
            return false;
            break;
        case UNI_MAC:
            set_unicode_input_mode(UC_OSX);
            return false;
            break;
    }
    return true;
}
