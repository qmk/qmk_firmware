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

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
extern rgblight_config_t rgblight_config;
#endif

enum layer_number {
    _QWERTY = 0,
    _NUM,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUM,
  LOWER,
  // SP_LOW,
  RAISE,
  ADJUST
};

#define TG_NUM  TT(_NUM)
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_GUI  MT(MOD_LGUI, KC_SPC)
#define SP_SFT  MT(MOD_LSFT, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
      KC_ESC, KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,               KC_PSLS,KC_PAST,TG_NUM,                  KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC, \
              KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,       KC_P7,  KC_P8,  KC_P9,  KC_PMNS,                 KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS, \
              KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,       KC_MPRV,KC_MPLY,KC_MNXT,KC_PPLS,                 KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT, \
              KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   RAISE,      KC_MUTE,KC_VOLD,KC_VOLU,KC_PENT,                 KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,KC_UP, \
              RAISE,                  KC_LALT,KC_LGUI,SP_SFT,             KC_P0,          KC_PDOT,                         LOWER,  SP_GUI, KC_LALT,        KC_LCTL,KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    [_NUM] = LAYOUT(
      _______, KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,               KC_PSLS,KC_PAST,TG_NUM,              KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC, \
              KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,       KC_P7,  KC_P8,  KC_P9,  KC_PMNS,                 KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS, \
              KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,       KC_P4,  KC_P5,  KC_P6,  KC_PPLS,                 KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT, \
              KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   LOWER,      KC_P1,  KC_P2,  KC_P3,  KC_PENT,                 KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,KC_UP, \
              RAISE,                  KC_LALT,KC_LGUI,_______,             KC_P0,          KC_PDOT,                         _______,_______,_______,        _______,KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    [_LOWER] = LAYOUT(
    _______,_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                 _______,_______,_______,            KC_F7,  KC_F8,  KC_F9,KC_F10,   KC_F11, KC_F12, KC_DEL, \
              _______,_______,_______,LCTL(KC_E),_______,_______,_______,    _______,_______,_______,_______,            _______,_______,_______,_______,KC_UP,  _______,_______,_______, \
              _______,LCTL(KC_A),_______,KC_DEL, KC_RGHT,KC_ESC, KC_BSPC,    _______,_______,_______,_______,            KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,_______,_______,_______, \
              _______,_______,_______,_______,_______,KC_LEFT,_______,       _______,_______,_______,_______,            KC_DOWN,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______, \
              _______,                _______,_______,_______,               _______,        _______,                    _______,_______,_______,        _______,_______,_______,_______ \
    ),
    [_RAISE] = LAYOUT(
      _______, KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,               KC_PSLS,KC_PAST,KC_PMNS,              KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC, \
              KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,          KC_P7,  KC_P8,  KC_P9,  KC_PMNS,                 KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS, \
              KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,          KC_P4,  KC_P5,  KC_P6,  KC_PPLS,                 KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT, \
              KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   _______,       KC_P1,  KC_P2,  KC_P3,  KC_PENT,                 KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_UP,  KC_RSFT, \
              _______,                  KC_LALT,KC_LGUI,_______,              KC_P0,          KC_PDOT,                         _______,_______,_______,        _______,KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    [_ADJUST] = LAYOUT(
      _______, KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,              KC_PSLS,KC_PAST,KC_PMNS,             KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC, \
              _______, KC_Q,   KC_W,   KC_E,   RESET,   KC_T,   KC_Y,        RGB_TOG,RGB_MOD,RGB_RMOD,  KC_PMNS,                KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS, \
              KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,          RGB_HUI,RGB_SAI,RGB_VAI,  KC_PPLS,                 KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT, \
              KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   _______,       RGB_HUD,RGB_SAD,RGB_VAD,  KC_PENT,                 KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_UP,  KC_RSFT, \
              _______,                  KC_LALT,KC_LGUI,_______,              KC_P0,          KC_PDOT,                           _______,_______,_______,        _______,KC_LEFT,KC_DOWN,KC_RGHT \
    )
};

// レイヤーキーを変換・無変換キーと共用する際に動作を改善する。
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TG_NUM:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_NUM)) {
        } else {
        }
      }
      return true;
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

// レイヤー切り替えにともなって、インジケータLEDを発光
layer_state_t layer_state_set_user(layer_state_t state) {
  #ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _NUM:
          rgblight_sethsv_at (HSV_GOLD, 0);
          rgblight_sethsv_at(0,0,0,1);
          break;
    case _LOWER:
          rgblight_sethsv_at(HSV_CYAN,1);
          break;
    case _RAISE:
          rgblight_sethsv_at(HSV_RED,1);
        break;
    case _ADJUST:
          rgblight_sethsv_at(HSV_GREEN,1);
        break;
    default: //  for any other layers, or the default layer
          rgblight_sethsv(0,0,0);
        break;
    }
  #endif
  return state;
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
