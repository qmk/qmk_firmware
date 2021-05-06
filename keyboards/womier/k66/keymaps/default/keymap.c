/*
Copyright 2019 Stephen Peery

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
enum layer_names {
    _BASE,
    _FN1,
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_GESC , KC_1    , KC_2     , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_MINS , KC_EQL  , KC_BSPC , KC_INS  ,
    KC_TAB  , KC_Q    , KC_W     , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC , KC_RBRC , KC_BSLS , KC_DEL  ,
    MO(1)   , KC_A    , KC_S     , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_ENT  ,
    KC_LSFT , KC_Z    , KC_X     , KC_C    , KC_V    , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT , KC_UP   ,
    KC_LCTL , KC_LGUI , KC_LALT  ,                     KC_SPC  ,                     KC_RALT , MO(1)   , KC_RCTL , KC_LEFT , KC_DOWN , KC_RGHT
    )       ,
  [1] = LAYOUT(
    KC_GRV  , KC_F1   , KC_F2    , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_MUTE , KC_VOLU ,
    _______ , _______ , _______  , _______ , _______ , _______ , _______ , _______ , KC_PSCR , KC_SLCK , KC_PAUS , _______ , _______ , _______ , KC_VOLD ,
    MO(1)   , _______  , MO(2)   , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______  , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_PGUP ,
    _______ , _______ , _______  ,                     _______ ,                     _______ , MO(1)   , _______ , KC_HOME , KC_PGDN , KC_END
    ),
  [2] = LAYOUT(
    RGB_MOD , RGB_RMOD, RGB_M_P  , RGB_M_B , RGB_M_R , RGB_M_SW, RGB_M_SN, RGB_M_K , RGB_M_X , RGB_M_G , RGB_M_T , KC_F11  , KC_F12  , RGB_TOG , RGB_VAI ,
    _______ , _______ , _______  , _______ , RESET   , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , RGB_VAD ,
    MO(1)   , _______ , MO(2)    , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______  , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , RGB_SAI ,
    _______ , _______ , _______  ,                     _______ ,                     _______ , MO(1)   , _______ , RGB_HUD , RGB_SAD , RGB_HUI
    )
};
/* clang-format on */
