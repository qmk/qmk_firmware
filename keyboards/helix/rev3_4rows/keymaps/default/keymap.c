/* Copyright 2020 yushakobo
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


// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  EISU = SAFE_RANGE,
  KANA,
  ADJUST,
  RGBRST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      ADJUST,  KC_ESC,  KC_LALT, KC_LGUI, EISU,    LOWER,   KC_SPC,  KC_SPC,  RAISE,   KANA,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CAPS |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      | Home | End  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  _______, _______, KC_HOME, KC_END,  _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CAPS |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      |PageDn|PageUp|      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
      KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  _______, _______, KC_PGDN, KC_PGUP, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|EEPRST|      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      | Mac  |             | Win  |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      _______, RESET,   RGBRST,  EEP_RST, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL, \
      _______, _______, _______, _______, _______, AG_NORM,                   AG_SWAP, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )

};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left side encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Right side encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EISU:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_LANG2);
        }else{
          tap_code16(LALT(KC_GRAVE));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_LANG1);
        }else{
          tap_code16(LALT(KC_GRAVE));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_LOWER);
        layer_on(_RAISE);
      } else {
        layer_off(_LOWER);
        layer_off(_RAISE);
      }
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
