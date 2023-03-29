/* Copyright 2020 smssmssms
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
#include "keymap_uk.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_ortho_6x13(
        KC_ESC,     KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,   KC_BSPC, KC_DEL,
        UK_GRV,     UK_1,      UK_2,      UK_3,      UK_4,      UK_5,      UK_6,      UK_7,      UK_8,      UK_9,     UK_0,     UK_MINS, UK_EQL,
        KC_TAB,     KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,     KC_P,     UK_LBRC, UK_RBRC,
        KC_CAPS,    KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,     UK_SCLN,  UK_QUOT, UK_HASH,
        KC_LSFT,    KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      UK_COMM,   UK_DOT,   UK_SLSH,  UK_BSLS, KC_RSFT,
        KC_LCTL,    KC_LGUI,   KC_LALT,   XXXXXXX,   KC_SPC,    TG(_FN),     KC_MUTE,   KC_ENT,    KC_ALGR,   KC_RGUI,  KC_MENU,  KC_HOME, KC_END
    ),
    
    [_FN] = LAYOUT_ortho_6x13(
        _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______, _______,
        KC_SLEP,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  KC_F11,  KC_F12,
        _______,    XXXXXXX,   KC_WAKE,   KC_MYCM,   XXXXXXX,   XXXXXXX,   KC_AGAIN,  KC_VOLU,   KC_INS,    KC_PWR,   KC_PSCR,  XXXXXXX, KC_PGUP,
        _______,    XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_FIND,   XXXXXXX,   KC_HELP,   KC_VOLD,   KC_CALC,   KC_BRIU,  XXXXXXX,  KC_UP,   KC_PGDN,
        _______,    KC_UNDO,   KC_CUT,    KC_COPY,   KC_PASTE,  QK_BOOT,     XXXXXXX,   KC_MAIL,   UK_COMM,   KC_BRID,  KC_LEFT,  KC_DOWN, KC_RIGHT,
        _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______, _______
    )
};
