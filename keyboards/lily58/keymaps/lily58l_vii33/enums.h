/*
Global enum and define file for all c files

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 Ben Roesner (keycapsss.com)
Copyright 2022 Vii33 (https://github.com/vii33/mecha-keyboard-lily58l)

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

enum layers {
    _QWERTY,    //0
    _LOWER,     //1
    _UPPER,     //2
    _MOD,       //3
    _GAME       //4
};


enum custom_keycodes {
    CC_AE = SAFE_RANGE,
    CC_OE,
    CC_UE,
    CC_BckDel,
    CC_SLH,
    CC_QUOT,
    CC_APHO,
    CC_SCOLN,
    CC_COLN,
    CC_EXLM,
    CC_SAVRGB,
    CC_ALRM,
};


/* HOME Row Modifiers */
/* Left-hand home row mods */
#define GUI_S LGUI_T(KC_S)
#define ALT_D LALT_T(KC_D)
#define CTL_F LCTL_T(KC_F)
/* Right-hand home row mods */
#define CTL_J RCTL_T(KC_J)
#define ALT_K LALT_T(KC_K)
#define GUI_L RGUI_T(KC_L)

#define SHFT_SP RSFT_T(KC_SPC)