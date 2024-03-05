/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
#include "features/achordion.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_achordion(keycode, record)) { return false; }
  return true;
}

void matrix_scan_user(void) {
  achordion_task();
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
        // Mods
        case KC_LEFT_CTRL:
        case KC_LEFT_ALT:
        case KC_LEFT_GUI:
        case KC_LEFT_SHIFT:
        case KC_RIGHT_CTRL:
        case KC_RIGHT_ALT:
        case KC_RIGHT_GUI:
        case KC_RIGHT_SHIFT:
        // Arrows
        case KC_LEFT:
        case KC_RIGHT:
        case KC_UP:
        case KC_DOWN:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

const key_override_t **key_overrides = (const key_override_t *[]){
	&ko_make_basic(MOD_MASK_SHIFT, MEH_T(KC_COMM), KC_COLON),
	&ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_SEMICOLON),
	NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_split_3x5_3(
      KC_Q,         KC_W,         HYPR_T(KC_F), KC_P,          KC_B,                                    KC_J,           KC_L,         HYPR_T(KC_U),   KC_Y,         KC_QUOT,
      LCTL_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T),  KC_G,                                    KC_M,           RSFT_T(KC_N), RGUI_T(KC_E),   RALT_T(KC_I), RCTL_T(KC_O),
      KC_Z,         KC_X,         MEH_T(KC_C),  KC_D,          KC_V,                                    KC_K,           KC_H,         MEH_T(KC_COMM), KC_DOT,       KC_MINS,
                                                LT(1, KC_ESC), LT(2, KC_SPC), KC_TAB,       KC_ENT,     LT(3, KC_BSPC), KC_SLASH

  ),

  [1] = LAYOUT_split_3x5_3(
      XXXXXXX,      XXXXXXX,     XXXXXXX,       XXXXXXX,       XXXXXXX,                                 XXXXXXX,        KC_7,         KC_8,           KC_9,         KC_KB_VOLUME_UP,
      KC_LEFT_CTRL, KC_LEFT_ALT, KC_LEFT_GUI,   KC_LEFT_SHIFT, XXXXXXX,                                 XXXXXXX,        KC_4,         KC_5,           KC_6,         KC_KB_VOLUME_DOWN,
      XXXXXXX,      XXXXXXX,     XXXXXXX,       XXXXXXX,       XXXXXXX,                                 KC_0,           KC_1,         KC_2,           KC_3,         KC_KB_MUTE,
                                                KC_ESC,        KC_SPC,        KC_TAB,       XXXXXXX,    XXXXXXX,        XXXXXXX
  ),

  [2] = LAYOUT_split_3x5_3(
      XXXXXXX,      XXXXXXX,     XXXXXXX,       XXXXXXX,       XXXXXXX,                                 KC_CAPS,        KC_LCBR,      KC_RCBR,        KC_LPRN,      KC_RPRN,
      KC_LEFT_CTRL, KC_LEFT_ALT, KC_LEFT_GUI,   KC_LEFT_SHIFT, XXXXXXX,                                 CW_TOGG,        KC_LEFT,      KC_DOWN,        KC_UP,        KC_RIGHT,
      XXXXXXX,      XXXXXXX,     XXXXXXX,       XXXXXXX,       XXXXXXX,                                 XXXXXXX,        KC_LBRC,      KC_RBRC,        KC_LT,        KC_GT,
                                                XXXXXXX,       XXXXXXX,       XXXXXXX,      KC_ENT,     KC_BSPC,        KC_SLASH
  ),

  [3] = LAYOUT_split_3x5_3(
      KC_TILD,      KC_EXLM,     KC_AT,         KC_HASH,       KC_DLR,                                  XXXXXXX,    XXXXXXX,            XXXXXXX,      XXXXXXX,      XXXXXXX,
      KC_PIPE,      KC_BSLS,     KC_PLUS,       KC_EQL,        KC_QUES,                                 XXXXXXX,    KC_RIGHT_SHIFT,     KC_RIGHT_GUI, KC_RIGHT_ALT, KC_RIGHT_CTRL,
      KC_GRAVE,     KC_PERC,     KC_CIRC,       KC_AMPR,       KC_ASTR,                                 XXXXXXX,    XXXXXXX,            XXXXXXX,      XXXXXXX,      XXXXXXX,
                                                KC_ESC,        KC_SPC,        KC_TAB,       XXXXXXX,    XXXXXXX,    XXXXXXX
  )
};
