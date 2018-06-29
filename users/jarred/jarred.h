/* Copyright 2018 Jarred Steenvoorden
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
 
#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Use 7 wide characters for keymaps
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Layers
#define _QW 0
#define _LW 1
#define _NV 2
#define _NP 3
#define _MS 4 // Mouse

#define MS_A LT(_MS,KC_A)

// Shared keymaps
#define KM(...) KEYMAP(__VA_ARGS__) // Required to expand the CSVs

/* Qwerty Layer */
#define QWERTY_1   KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC
#define QWERTY_2   MO(_NV),    MS_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT
#define QWERTY_3   KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT
#define QWERTY_4   KC_LCTL, KC_LGUI, MO(_NP), KC_LALT, MO(_LW),  KC_SPC,  KC_ENT, MO(_LW), KC_RALT, MO(_MS),  KC_APP, KC_RCTL

/* Lower / Upper Layer */
#define LOWER_1    KC_ESC ,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______
#define LOWER_2    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F11,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS
#define LOWER_3    _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F12,  KC_GRV,  _______, _______, _______, _______
#define LOWER_4    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______

/* Navigation Layer */
#define NAV_1      _______, _______, _______, KC_LGUI,  KC_DEL, KC_BSPC, _______, KC_HOME, KC_UP  , KC_END ,  KC_INS, _______
#define NAV_2      _______, _______, _______, KC_LSFT, KC_LCTL,  KC_ENT, _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, _______
#define NAV_3      _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______, _______, _______
#define NAV_4      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______

/* Numpad Layer */
#define NUMPAD_1   RGB_TOG, RGB_MOD, _______, _______, RGB_HUD, RGB_HUI, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______
#define NUMPAD_2   BL_TOGG, BL_STEP, BL_BRTG, _______, RGB_SAD, RGB_SAI, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______
#define NUMPAD_3   _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______, KC_P1,   KC_P2,   KC_P3,   KC_PAST, KC_ENT 
#define NUMPAD_4     RESET, _______, _______, _______, _______, _______, _______, KC_P0,   XXXXXXX, KC_PDOT, KC_PSLS, KC_ENT 

#define MOUSE_1    _______, _______, _______, _______, _______, _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______
#define MOUSE_2    _______, _______, KC_ACL1, KC_ACL0, KC_BTN1, KC_BTN2, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______
#define MOUSE_3    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
#define MOUSE_4    _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______

#define KM_QWERTY KM(QWERTY_1,QWERTY_2,QWERTY_3,QWERTY_4)
#define KM_LOWER KM(LOWER_1,LOWER_2,LOWER_3,LOWER_4)
#define KM_NAV KM(NAV_1,NAV_2,NAV_3,NAV_4)
#define KM_NUMPAD KM(NUMPAD_1,NUMPAD_2,NUMPAD_3,NUMPAD_4)
#define KM_MOUSE KM(MOUSE_1,MOUSE_2,MOUSE_3,MOUSE_4)

#endif
