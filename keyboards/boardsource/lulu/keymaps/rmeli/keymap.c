/*
Copyright 2022 Cole Smith <cole@boadsource.xyz>
Copyright 2022 Rocco Meli <@RMeli>

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

#include "rmeli.h"

enum layers { _QWERTY, _COLEMAK_DH, _RAISE, _LOWER, _ADJUST };

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define QWY_DF DF(_QWERTY)
#define CMK_DF DF(_COLEMAK_DH)

#define __________THUMB_LEFT_x4___________ KC_LALT, KC_LGUI, LOWER, KC_SPC
#define __________THUMB_RIGHT_x4__________ KC_ENT, RAISE, KC_BSPC, KC_RGUI

/* LAYOUT
 *
 * ,-----------------------------.                ,-----------------------------.
 * |    |    |    |    |    |    |                |    |    |    |    |    |    |
 * |----+----+----+----+----+----|                |----+----+----+----+----+----|
 * |    |    |    |    |    |    |                |    |    |    |    |    |    |
 * |----+----+----+----+----+----|                |----+----+----+----+----+----|
 * |    |    |    |    |    |    |-----.    ,-----|    |    |    |    |    |    |
 * |----+----+----+----+----+----|     |    |     |----+----+----+----+----+----|
 * |    |    |    |    |    |    |-----|    |-----|    |    |    |    |    |    |
 * `----------------------------/     /      \     \----------------------------'
 *            |    |    |    | /     /        \     \  |    |    |    |
 *            |    |    |    |/     /          \     \ |    |    |    |
 *            `--------------''-----'          '------''--------------'
 */

// Define wrapper for standard LULU layout
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_wrapper(
  ___________________NUMBER_LEFT_x6___________________,                   ___________________NUMBER_RIGHT_x6__________________,
  ___________________QWERTY_L1_x6_____________________,                   ___________________QWERTY_R1_x6_____________________,
  ___________________QWERTY_L2_x6_____________________,                   ___________________QWERTY_R2_x6_____________________,
  ___________________QWERTY_L3_x6_____________________, KC_LBRC, KC_RBRC, ___________________QWERTY_R3_x6_____________________,
                             __________THUMB_LEFT_x4___________,  __________THUMB_RIGHT_x4__________
  ),

  [_COLEMAK_DH] = LAYOUT_wrapper(
  ___________________NUMBER_LEFT_x6___________________,                   ___________________NUMBER_RIGHT_x6__________________,
  ________________COLEMAK_MOD_DH_L1_x6________________,                   ________________COLEMAK_MOD_DH_R1_x6________________,
  ________________COLEMAK_MOD_DH_L2_x6________________,                   ________________COLEMAK_MOD_DH_R2_x6________________,
  ________________COLEMAK_MOD_DH_L3_x6________________, KC_LBRC, KC_RBRC, ________________COLEMAK_MOD_DH_R3_x6________________,
                             __________THUMB_LEFT_x4___________,  __________THUMB_RIGHT_x4__________
  ),

  [_LOWER] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  ____________________FUNC_LEFT_x6____________________,                   ____________________FUNC_RIGHT_x6___________________,
  ___________________SYMBOL_LEFT_x6___________________,                   ___________________SYMBOL_RIGHT_x6__________________,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),

  [_RAISE] = LAYOUT(
  RGB_MOD, RGB_RMOD,RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   RGB_TOG, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
  ),

  [_ADJUST] = LAYOUT(
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    UC_MOD,  KC_ASUP,   NK_ON, XXXXXXX, XXXXXXX,  QWY_DF,
  RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                    XXXXXXX, KC_ASTG, NK_TOGG, CG_TOGG, XXXXXXX, XXXXXXX,
  XXXXXXX,RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______,  UC_RMOD, KC_ASDN,  NK_OFF, CG_NORM, XXXXXXX,  CMK_DF,
                             _______, _______, _______, _______, _______,  _______, _______, _______
 )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
