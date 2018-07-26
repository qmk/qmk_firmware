/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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


#define _______ KC_TRNS
#define OOOOOOO KC_TRNS

#define C_LCTL MT(MOD_LCTL, KC_QUOT)
#define C_RCTL MT(MOD_RCTL, KC_GRV)

#define C_LGUI MT(MOD_LGUI, KC_LBRC)
#define C_RGUI MT(MOD_RGUI, KC_RBRC)

#define C_ESC MT(MOD_LCTL, KC_ESC)
#define C_ENT MT(MOD_RCTL, KC_ENT)


/*
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |     SPC     |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_mit(
        KC_TAB,  KC_Q,   KC_W,     KC_E,  KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,     KC_P,    KC_BSPC, \
        C_ESC,   KC_A,   KC_S,     KC_D,  KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,     KC_SCLN, C_ENT,   \
        KC_LSPO, KC_Z,   KC_X,     KC_C,  KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,   KC_SLSH, KC_RSPC, \
        C_LCTL,  C_LGUI, MOD_LALT, MO(3), MO(1),     KC_SPC,     MO(2), MO(4),   MOD_RALT, C_RGUI,  C_RCTL),

    [1] = LAYOUT_planck_mit(
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  RGB_TOG, RGB_MOD, KC_P7, KC_P8,   KC_P9,   KC_PSLS, _______, \
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   RGB_VAD, RGB_VAI, KC_P4, KC_P5,   KC_P6,   KC_PAST, _______, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   BL_TOGG, BL_INC,  KC_P1, KC_P2,   KC_P3,   KC_PMNS, KC_PGUP, \
        _______, _______, _______, _______, OOOOOOO,     _______,      KC_P0, KC_PDOT, KC_PENT, KC_PPLS, KC_PGDN),

    [2] = LAYOUT_planck_mit(
        _______,  _______, _______, _______, _______, _______, _______, KC_QUOT, KC_EQL,  KC_LBRC, KC_RBRC, KC_NUBS, \
        KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______,  _______, _______, _______, _______,     _______,      OOOOOOO, KC_HOME, KC_PGDOWN, KC_PGUP, KC_END),

    [3] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, KC_COPY, KC_PGUP, _______, _______,  KC_PASTE, KC_DEL,  \
        _______, _______, _______, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,  _______, \
        _______, _______, KC_CUT,  _______, _______, _______, _______, _______, _______, _______,  _______,  _______, \
        _______, _______, _______, OOOOOOO, _______,     _______,      _______, _______, _______,  _______,  _______),

    [4] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, \
        KC_PSCR, KC_INS,  KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, \
        KC_CAPS, _______, KC_MPLY, KC_MRWD, KC_MFFD, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, \
        _______, _______, _______, _______, _______,     _______,      _______, OOOOOOO, _______, _______, _______),


};



