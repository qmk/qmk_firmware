/*
Copyright 2020 Atsushi Morimoto @74th

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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _FN,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOCK,
    ESC_MHEN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
    // /-------+-------+-------+-------+-------+-------\                 /-------+-------+-------+-------+-------+-------.
    // |  `    |   1   |   2   |   3   |   4   |   5   |                 |   7   |   8   |   9   |   0   |   -   |   =   |
        KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                     KC_7,   KC_8,   KC_9,   KC_0,  KC_MINS,KC_EQL,
    // |-------+-------+-------+-------+-------+-------+-------\ /-------+-------+-------+-------+-------+-------+-------|
    // |  `    |   Q   |   W   |   E   |   R   |   T   |   6   | |   6   |   Y   |   U   |   I   |   O   |   P   |   =   |
        KC_GRV,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_6,     KC_6,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,  KC_EQL,
    // |-------+-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------+-------|
    // |Ctr(TAB|   A   |   S   |   D   |   F   |   G   |   [   | |   ]   |   H   |   J   |   K   |   L   |  ; :  |  ' "  |
    CTL_T(KC_TAB),KC_A,  KC_S,   KC_D,   KC_F,   KC_G,  KC_LBRC,  KC_RBRC, KC_H,   KC_J,   KC_K,   KC_L,  KC_SCLN,KC_QUOT,
    // |-------+-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------+-------|
    // |Sft(ESC|   Z   |   X   |   C   |   V   |   B   |   [   | |   ]   |   N   |   M   |  , <  |  . >  |  / ?  |  \ |  |
    SFT_T(KC_ESC),KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,  KC_LBRC,  KC_RBRC, KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,KC_BSLS,
    // |-------+-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------+-------|
    //                       |  ESC  |Alt(TAB|Sf(Eisu|Ctl(SPC|     |Ctl(ENT|  FN   |GU(Kana|  BS   |
    ESC_MHEN, ALT_T(KC_TAB), SFT_T(KC_INT5), CTL_T(KC_SPC), CTL_T(KC_ENT), MO(_FN), GUI_T(KC_INT4), KC_BSPC
    //                       \-------+-------+-------+-------/     \-------+-------+-------+-------/
    ),

    [_FN] = LAYOUT(
    // /-------+-------+-------+-------+-------+-------\                 /-------+-------+-------+-------+-------+-------.
    // | Lock  |CMD+F1 |Sft+F2 |CMD+F3 |CMD+F4 |CMD+F5 |                 |CMD+F6 |CMD+F7 |CMD+F8 |CMD+F9 |       |       |
    C(G(KC_Q)),LCMD(KC_F1),SCMD(KC_F2),LCMD(KC_F3),LCMD(KC_F4),LCMD(KC_F5),LCMD(KC_F6),LCMD(KC_F7),LCMD(KC_F8),LCMD(KC_F9),_______,_______,
    // |-------+-------+-------+-------+-------+-------+-------\ /-------+-------+-------+-------+-------+-------+-------|
    // | ESC   |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   | |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |
        KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,    KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,
    // |-------+-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------+-------|
    // |   ~   |   !   |   @   |   #   |   $   |   %   |   ^   | |   ^   |   &   |   *   |       | PrSC  | PrSC2 | PrSC3 |
        KC_GRV, KC_EXLM, KC_AT, KC_HASH,KC_DLR, KC_PERC,KC_CIRC,  KC_CIRC,KC_AMPR,KC_ASTR,_______,KC_PSCR,LALT(KC_PSCR),LSFT(KC_PSCR),
    // |-------+-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------+-------|
    // |       |       |       |       |       |       |       | |       |   ←   |   ↓   |   ↑   |   →   | HOME  |  END  |
        _______,_______,_______,_______,_______,_______,_______,  _______,KC_LEFT,KC_DOWN, KC_UP,KC_RIGHT,KC_HOME,KC_END,
    // |-------+-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------+-------|
    //                       |  ESC  |Alt(TAB|Sf(Eisu|Ctl(SPC|     |       |  FN   | RAlt  |  DEL  |
                              _______,_______,_______,_______,      _______,_______,_______,KC_DEL
    //                       \-------+-------+-------+-------/     \-------+-------+-------+-------/
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case ESC_MHEN:
                tap_code(KC_INT5);
                tap_code(KC_ESC);
                return false;
        }
    }
    return true;
}
