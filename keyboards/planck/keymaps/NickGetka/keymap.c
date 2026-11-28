/* Copyright 2015-2021 Jack Humbert
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
 * You should have received a copy of the GNU General Public Licensequ
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
* qmk compile -kb planck/ez/base -km NickGetka
* qmk flash -kb planck/ez/base -km NickGetka
*/

#include QMK_KEYBOARD_H
#include "NickGetka.h"

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

// enum planck_keycodes {
// };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Blank
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
// [_BLANK] = LAYOUT_planck_grid(
    // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// ),

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | / ?  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |Ctrl+A| Alt  | GUI  |Lower |    Space    |Raise | Left |  UP  | DOWN |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,       KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,       KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_ESC,  LCS_T(KC_NO), KC_LALT, KC_LGUI, LOWER, KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |  `   |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  _   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  |   |  \   |  +   |  ;   |  =   |  <   |  >   |  (   |  )   |  {   |  }   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |  -   |  /   |  ?   |  :   |  '   |  "   |  ,   |  .   |  [   |  ]   | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |Ctrl+A| Alt  | GUI  |Lower |    Space    |Raise | Left |  Up  | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, _______,
    _______, KC_PIPE, KC_BSLS, KC_PLUS, KC_SCLN, KC_EQL,  KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR,
    _______, KC_MINS, KC_SLSH, KC_QUES, KC_COLN, KC_QUOT, KC_DQUO, KC_COMM, KC_DOT,  KC_LBRC, KC_RBRC, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  %   |  -   |  1   |  2   |  3   |  =   | Home | PgDn | PgUp | End  | Del  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  0   |  4   |  5   |  6   |  *   | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |  +   |  7   |  8   |  9   |  .   |      |      |      |      |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  /   |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_PERC, KC_MINS, KC_1, KC_2, KC_3, KC_EQL,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL, _______,
    _______, KC_0,    KC_4, KC_5, KC_6, KC_PAST, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, KC_PLUS, KC_7, KC_8, KC_9, KC_DOT,  _______, _______, _______, _______, _______, _______,
    KC_SLSH, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      | PrtSc| RGB  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Mute | Vol- | Vol+ |C+A+Lt|      | Prev |C+A+Rt| Play | Next |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Bri- | Bri+ |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | BOOT |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, UG_TOGG,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, LCA(KC_LEFT), _______, KC_MPRV, LCA(KC_RGHT), KC_MPLY, KC_MNXT, _______, _______,
    _______, KC_BRID, KC_BRIU, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


};

#if defined(KEYBOARD_planck_rev6_drop) && defined(RGBLIGHT_ENABLE)
const rgblight_segment_t PROGMEM lower_indicator[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_WHITE}
);
const rgblight_segment_t PROGMEM raise_indicator[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_WHITE}
);
const rgblight_segment_t *const PROGMEM indicator_layers[] = RGBLIGHT_LAYERS_LIST(
    lower_indicator,
    raise_indicator
);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
#if defined(KEYBOARD_planck_rev6_drop) && defined(RGBLIGHT_ENABLE)
  rgblight_set_layer_state(0, layer_state_cmp(state, _LOWER));
  rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
#endif
  return state;
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
#    ifdef KEYBOARD_planck_rev6_drop
  rgblight_layers = indicator_layers;
#    endif
  rgblight_disable();
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  }
  return true;
}
