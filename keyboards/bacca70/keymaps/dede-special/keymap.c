/*
Copyright 2022 keebnewb

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

// Windows mods
#define GRV_CTL MT(MOD_LCTL, KC_GRV)
#define BLS_CTL MT(MOD_RCTL, KC_BSLS)
#define TAB_ALT MT(MOD_LALT, KC_TAB)

// MacOS mods
#define GRV_GUI MT(MOD_LGUI, KC_GRV)
#define BLS_GUI MT(MOD_RGUI, KC_BSLS)
#define TAB_CTL MT(MOD_LCTL, KC_TAB)

// mod tap bracket shifts
#define LBR_SFT MT(MOD_LSFT, KC_LBRC)
#define RBR_SFT MT(MOD_RSFT, KC_RBRC)

// Arrow/TenKey/Media Keys/Reset hold with Backspace tap
#define BSPC_LR LT(3, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_debaccabean(
        KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_F13,
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_LBRC,KC_GRV, KC_RBRC,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_DEL,
        KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_P7,  KC_P8,  KC_P9,  KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_ENT,
        TAB_ALT,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_P4,  KC_P5,  KC_P6,  KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
        LBR_SFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_P1,  KC_P2,  KC_P3,  KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,RBR_SFT,
        KC_LGUI,        GRV_CTL,                                BSPC_LR,MO(2),  KC_SPC,                 BLS_CTL,        KC_RGUI
    ),

    // MacOS layer
    [1] = LAYOUT_debaccabean(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        TAB_CTL,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_LALT,        GRV_GUI,                                KC_TRNS,KC_TRNS,KC_TRNS,                BLS_GUI,        KC_RALT
    ),

    [2] = LAYOUT_debaccabean(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_UNDS,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_DLR, KC_TRNS,KC_TRNS,KC_TRNS,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_PLUS,
        KC_MINS,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_TRNS,KC_TRNS,KC_TRNS,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQL,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,        KC_TRNS,                                KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,        KC_TRNS
    ),

    [3] = LAYOUT_debaccabean(
        QK_BOOT,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,TG(1),
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_PAUS,KC_TRNS,KC_TRNS,
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_INS, KC_UP,  KC_PGUP,KC_TRNS,KC_TRNS,
        KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_MNXT,KC_TRNS,KC_TRNS,KC_TRNS,KC_LEFT,KC_DOWN,KC_RGHT,KC_TRNS,
        KC_MPLY,KC_MUTE,KC_VOLD,KC_VOLU,KC_MPRV,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_HOME,KC_END, KC_PGDN,KC_TRNS,KC_TRNS,
        KC_TRNS,        KC_TRNS,                                KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,        KC_TRNS
    )
};
