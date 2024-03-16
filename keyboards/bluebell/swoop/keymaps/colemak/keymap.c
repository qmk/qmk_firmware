/* Copyright 2022 James White <jamesmnw@gmail.com>
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

enum ferris_tap_dances {
  TD_1,
  TD_2,
  TD_3,
  TD_4,
  TD_5,
  TD_6,
  TD_7,
  TD_8,
  TD_9,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_1] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENT),
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_ESC),
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_C, LGUI(KC_C)),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_V, LGUI(KC_V)),
    [TD_5] = ACTION_TAP_DANCE_DOUBLE(KC_X, LGUI(KC_X)),
    [TD_6] = ACTION_TAP_DANCE_DOUBLE(KC_1, LCTL(KC_1)),
    [TD_7] = ACTION_TAP_DANCE_DOUBLE(KC_2, LCTL(KC_2)),
    [TD_8] = ACTION_TAP_DANCE_DOUBLE(KC_3, LCTL(KC_3)),
    [TD_9] = ACTION_TAP_DANCE_DOUBLE(KC_4, LCTL(KC_4)),
};

enum layers {
    _QWERTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,---------------------------------.     ,----------------------------------.
 * |  Q  |   W  |   E  |   R  |   T  |     |   Y  |   U  |   I  |   O  |   P  |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * |  A  |   S  |   D  |   F  |   G  |     |   H  |   J  |   K  |   L  |   ;  |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |  Z  |   X  |   C  |   V  |   B  |     |   N  |   M  |   ,  |   .  |   /  |
 * `------------+------+------+------|     |------+------+------+-------------'
 *              | LCTL | BSpc | Esc  |     | Ent  | Spc  | LAlt |
 *              `--------------------'     `--------------------'
 */

[_QWERTY] = LAYOUT_split_3x5_3(
  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                   KC_LCTL, KC_BSPC, KC_ESC,      KC_ENT,  KC_SPC,  KC_LALT
)
};