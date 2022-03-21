/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#define LW_BSPC LT(2, KC_BSPC)
#define RS_SPC  LT(1, KC_SPC)

#define ALT_ENT ALT_T(KC_ENT)
#define SFT_ESC SFT_T(KC_ESC)

// home row mods.
#define CT_S    RCTL_T(KC_S)
#define CT_L    RCTL_T(KC_L)
#define SH_A    RSFT_T(KC_A)
#define SH_SCLN RSFT_T(KC_SCLN)
#define AL_D    RALT_T(KC_D)
#define AL_K    RALT_T(KC_K)
#define GU_G    RGUI_T(KC_G)
#define GU_H    RGUI_T(KC_H)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,            KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_DEL, KC_BSPC,
        KC_LCTL,SH_A,   CT_S,   AL_D,   KC_F,   KC_G,            KC_H,   KC_J,   KC_K,   KC_L,   KC_QUOT,     KC_SCLN,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,MO(1),
        KC_LGUI,KC_LALT,        KC_LGUI,LW_BSPC,SFT_ESC,         ALT_ENT,RS_SPC, KC_LALT,                KC_RGUI,KC_RCTL
    ),
    [1] = LAYOUT_all(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,            KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_DEL, KC_BSPC,
        KC_LCTL,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,         KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,   KC_SCLN,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,MO(2),
        KC_LGUI,KC_LALT,        KC_LGUI,LW_BSPC,SFT_ESC,         ALT_ENT,RS_SPC, KC_LALT,                KC_RGUI,KC_RCTL
    ),
    [2] = LAYOUT_all(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,           KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_F13,
        KC_LCTL,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,         KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,   KC_SCLN,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   RESET,           KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,MO(1),
        KC_LGUI,KC_LALT,        KC_LGUI,LW_BSPC,SFT_ESC,         ALT_ENT,RS_SPC, KC_LALT,                KC_RGUI,KC_RCTL
    ),
};
