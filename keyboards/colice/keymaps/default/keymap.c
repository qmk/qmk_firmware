/* Copyright 2020 Takeshi Nishio
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


enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  STR_LOWER,
  STR_RAISE
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    /* 動作確認済み
    [_QWERTY] = LAYOUT(
            KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,           KC_PSLS,KC_PAST,KC_PMNS, \
                    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_P7,  KC_P8,  KC_P9,  KC_PMNS, \
                    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS, \
                    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_GRV, KC_P1,  KC_P2,  KC_P3,  KC_PENT, \
      KC_ESC, KC_TAB, KC_LCTL,KC_LSFT,LOWER,  KC_LALT,KC_LGUI,KC_SPC, KC_P0,          KC_PDOT \
    ),
    [_LOWER] = LAYOUT(
            KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,           KC_PSLS,KC_PAST,KC_PMNS, \
                    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_P7,  KC_P8,  KC_P9,  KC_PMNS, \
                    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS, \
                    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_GRV, KC_P1,  KC_P2,  KC_P3,  KC_PENT, \
      KC_ESC, KC_TAB, KC_LCTL,KC_LSFT,_______,  KC_LALT,KC_LGUI,KC_SPC, KC_P0,          KC_PDOT \
    )*/
    [_QWERTY] = LAYOUT(
      KC_ESC, KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,           KC_PSLS,KC_PAST,KC_PMNS, \
              KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_P7,  KC_P8,  KC_P9,  KC_PMNS, \
              KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS, \
              KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   RAISE,  KC_P1,  KC_P2,  KC_P3,  KC_PENT, \
              LOWER,                  KC_LALT,KC_LGUI,KC_SPC, KC_P0,          KC_PDOT \
    ),
    [_LOWER] = LAYOUT(
      STR_LOWER,  KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,           KC_PSLS,KC_PAST,KC_PMNS, \
              KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_P7,  KC_P8,  KC_P9,  KC_PMNS, \
              KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS, \
              KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   RAISE,  KC_P1,  KC_P2,  KC_P3,  KC_PENT, \
              _______,                KC_LALT,KC_LGUI,KC_SPC, KC_P0,          KC_PDOT \
    ),
    [_RAISE] = LAYOUT(
      STR_RAISE,  KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,           KC_PSLS,KC_PAST,KC_PMNS, \
              KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_P7,  KC_P8,  KC_P9,  KC_PMNS, \
              KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS, \
              KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   RAISE,  KC_P1,  KC_P2,  KC_P3,  KC_PENT, \
              _______,                KC_LALT,KC_LGUI,KC_SPC, KC_P0,          KC_PDOT \
    )
};

// レイヤーキーを変換・無変換キーと共用する際に動作を改善する。
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case STR_LOWER:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("Lower");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case STR_RAISE:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("Raise");
      } else {
        // when keycode QMKBEST is released
      }
      break;
      case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        lower_pressed_time = record->event.time;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        /*
        長押し時に入力キャンセルする場合はこれ
        if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
        */
        if (lower_pressed) {
          register_code(KC_LANG2); // for macOS
          register_code(KC_MHEN);
          unregister_code(KC_MHEN);
          unregister_code(KC_LANG2);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        raise_pressed_time = record->event.time;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        /*
        長押し時に入力キャンセルする場合はこれ
        if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
        */
        if (raise_pressed) {
          register_code(KC_LANG1); // for macOS
          register_code(KC_HENK);
          unregister_code(KC_HENK);
          unregister_code(KC_LANG1);
        }
        raise_pressed = false;
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    default:
      if (record->event.pressed) {
        // reset the flags
        lower_pressed = false;
        raise_pressed = false;
      }
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
