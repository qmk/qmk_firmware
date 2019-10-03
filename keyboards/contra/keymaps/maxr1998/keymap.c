/* Copyright 2015-2017 Jack Humbert
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

#include "contra.h"
#include "keymap_german.h"

enum contra_layers {
  _QWERTZ,
  _FN,
  _NR,
  _NR_L3,
  _FX,
  _GAMING
};

#define KC_I3 LM(_NR, MOD_LALT)
#define KC_NR SAFE_RANGE
#define KC_N3 (SAFE_RANGE + 1)
#define KC_FN MO(_FN)
#define G_1 TO(_GAMING)
#define G_0 TG(_GAMING)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwertz
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | +* ~ | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Sup  | Alt  |  i3  | NumR |    Space    | Spec | Fun  | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTZ] = {
  {KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    DE_PLUS, KC_ENT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT},
  {KC_LCTL, KC_LGUI, KC_LALT, KC_I3,   KC_NR,   KC_SPC,  KC_SPC,  KC_N3,   KC_FN,   KC_LEFT, KC_DOWN, KC_RGHT}
},

/* Function layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   Ü  |      |   Ö  |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Lock |   Ä  |   ß  |      |      | GAME |      | RGBS | RGBB | RGBS |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | RGBH-| RGBT | RGBH+| PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ---- | ---- |             | ---- | ---- | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = {
  {_______, _______, _______, _______, _______, _______, _______, DE_UE,   _______, DE_OE,   _______, KC_DEL },
  {KC_LOCK, DE_AE,   DE_SS,   _______, _______, G_1,     _______, RGB_M_P, RGB_M_B, RGB_M_SW,_______, _______},
  {_______, _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_TOG, RGB_HUI, KC_PGUP, _______},
  {_______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END }
},

/* Numrow layer (special characters with Shift and ISO_L3_Shift)
 * ,-----------------------------------------------------------------------------------.
 * |      |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |  #'  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | <> | |      |      |      |      |      |      |      |      |  -_  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ---- | ---- |             | ---- | ---- |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NR] = {
  {_______, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DE_HASH, _______},
  {_______, DE_LESS, _______, _______, _______, _______, _______, _______, _______, _______, DE_MINS, _______},
  {_______, _______, _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______}
},
[_NR_L3] = {
  {_______, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_SS  },
  {_______, DE_Q,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, DE_LESS, _______, _______, _______, _______, _______, _______, _______, _______, DE_MINS, _______},
  {_______, _______, _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______}
},

/* Function keys
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FX] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, _______, _______}
},

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Space|      |      |      |      |             |      | Leave|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {KC_SPC,  XXXXXXX, _______, _______, _______, KC_LCTL, KC_LCTL, _______, G_0,     _______, _______, _______}
}
};

void update_tri_layer_user(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_BSPC:
      if (record->event.pressed) {
        if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
          register_code(DE_SS);
          return false;
        }
      } else {
        unregister_code(DE_SS);
      }
      return true;
    case KC_NR:
      if (record->event.pressed) {
        layer_on(_NR);
      } else {
        layer_off(_NR);
      }
      update_tri_layer_user();
      return false;
    case KC_N3:
      if (record->event.pressed) {
        layer_on(_NR_L3);
      } else {
        layer_off(_NR_L3);
      }
      update_tri_layer_user();
      return false;
    default:
      return true;
  }
}

void update_tri_layer_user(void) {
    update_tri_layer(_NR, _NR_L3, _FX);
    if (layer_state_is(_NR_L3) && !layer_state_is(_FX)) {
        register_code(KC_ALGR);
    } else {
        unregister_code(KC_ALGR);
    }
}

void led_set_user(uint8_t usb_led) {
  // Force-enable Numlock
  if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
    register_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}
