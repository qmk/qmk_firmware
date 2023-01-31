/* Copyright 2021 Daniel Shields
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
#include "dshields.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P   ,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_TAB,  KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        OSMLCTL, MT_ESC,  OSMLALT, OSL_FUN, MT_BSPC, OSL_LWR, OSL_RSE, MT_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [LWR] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_TILD, _______, _______, _______, _______,                   KC_UNDS, KC_PLUS, _______, KC_LCBR, KC_RCBR,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DQUO, KC_PIPE,
        _______, _______, _______, _______, KC_DEL,  _______, _______, KC_ENT,  KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

    [RSE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0   ,
        KC_GRV,  _______, _______, _______, _______,                   KC_MINS, KC_EQL,  _______, KC_LBRC, KC_RBRC,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUOT, KC_BSLS,
        _______, _______, _______, _______, KC_DEL,  _______, _______, KC_ENT,  KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
    [FUN] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10 ,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,                    _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
        _______, _______, _______, _______, _______, QK_BOOT, EEP_RST, _______, _______, KC_BTN1, KC_BTN2, KC_BTN3,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
    )
};
