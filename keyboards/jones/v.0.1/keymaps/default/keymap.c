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

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _MAC = 0,
    _WIN,
    _LOWER,
    _RAISE,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  MAC = SAFE_RANGE,
  WIN,
  LOWER,
  RAISE,
  ADJUST,
  ALT_US,
  ALT_JP
};

//#define TG_NUM  TT(_NUM)
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)
#define SP_GUI  MT(MOD_LGUI, KC_SPC)
#define SP_SFT  MT(MOD_LSFT, KC_SPC)
// #define RAI_OP  LALT_T(IME_US)
#define C_E     LCTL(KC_E)
#define C_A     LCTL(KC_A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT(
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,  \
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,KC_LBRC,KC_RBRC, \
    KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_ENT,         KC_QUOT, \
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,        LOWER,   \
    RAISE,  ALT_US, KC_LGUI,SP_SFT,                                 SP_RAI, KC_LGUI,KC_LALT,LOWER,          KC_MUTE  \
    ),
    [_WIN] = LAYOUT(
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,  \
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,KC_LBRC,KC_RBRC, \
    KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_ENT,         KC_QUOT, \
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,        LOWER,   \
    RAISE,  KC_LGUI,KC_LALT,SP_SFT,                                 SP_RAI, KC_LALT,KC_APP, LOWER,          KC_MUTE  \
    ),
        [_LOWER] = LAYOUT(
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_UP,  KC_END, KC_VOLU, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PGUP,KC_LEFT,KC_RGHT,        KC_VOLD, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PGDN,KC_DOWN,_______,        _______, \
    ADJUST, _______,_______,_______,                                ADJUST, _______,_______,_______,        _______  \
    ),
    [_RAISE] = LAYOUT(
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL, \
    _______,_______,_______,C_E,    _______,_______,_______,_______,_______,_______,KC_PGUP,KC_DEL, _______,KC_VOLU, \
    _______,C_A,    _______,KC_DEL, KC_RGHT,KC_ESC, KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,_______,_______,        KC_VOLD, \
    _______,_______,_______,_______,_______,KC_LEFT,KC_PGDN,KC_ENT, _______,_______,_______,_______,        ADJUST,   \
    _______,_______,_______,_______,                                _______,_______,_______,ADJUST,         _______  \
    ),
    [_ADJUST] = LAYOUT(
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
    _______,_______,DF(_WIN),_______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______, \
    _______,_______,_______,_______,_______,_______,_______,_______,RGB_M_P,RGB_TOG,RGB_MOD,_______,        _______, \
    _______,_______,_______,_______,_______,_______,_______,DF(_MAC),_______,_______,_______,_______,        _______, \
    _______,_______,_______,_______,                                _______,_______,_______,_______,        _______  \
    )
};

// レイヤーキーを変換・無変換キーと共用する際に動作を改善する。
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
static bool alt_us_pressed = false;
static uint16_t alt_us_pressed_time = 0;
static bool alt_jp_pressed = false;
static uint16_t alt_jp_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

switch (keycode) {
    // case TG_NUM:
    //   if (record->event.pressed) {
    //     if (IS_LAYER_ON(_NUM)) {
    //     } else {
    //     }
    //   }
    //   return true;
    //   break;
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
            長押し時に入力キャンセルする場合
            if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {

            長押しキャンセルなしの場合
            if (lower_pressed) {
            */
            if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
                register_code(KC_LANG1); // for macOS
                register_code(KC_HENK);
                unregister_code(KC_HENK);
                unregister_code(KC_LANG1);
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
                register_code(KC_LANG2); // for macOS
                register_code(KC_MHEN);
                unregister_code(KC_MHEN);
                unregister_code(KC_LANG2);
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
    case ALT_US:
        if (record->event.pressed) {
            alt_us_pressed = true;
            alt_us_pressed_time = record->event.time;
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LALT);
            /*
            長押し時に入力キャンセルする場合はこれ
            if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
            */
            if (alt_us_pressed) {
                register_code(KC_LANG2); // for macOS
                register_code(KC_MHEN);
                unregister_code(KC_MHEN);
                unregister_code(KC_LANG2);
            }
            alt_us_pressed = false;
        }
        return false;
        break;
    case ALT_JP:
        if (record->event.pressed) {
            alt_jp_pressed = true;
            alt_jp_pressed_time = record->event.time;
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LALT);
            /*
            長押し時に入力キャンセルする場合はこれ
            if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
            */
            if (alt_jp_pressed) {
                register_code(KC_LANG1); // for macOS
                register_code(KC_HENK);
                unregister_code(KC_HENK);
                unregister_code(KC_LANG1);
            }
            alt_jp_pressed = false;
        }
        return false;
        break;
    default:
        if (record->event.pressed) {
            // reset the flags
            lower_pressed = false;
            raise_pressed = false;
            alt_us_pressed = false;
            alt_jp_pressed = false;
        }
        break;
    }
    return true;
}

// レイヤー切り替えにともなって、インジケータLEDを発光
// layer_state_t layer_state_set_user(layer_state_t state) {
//   #ifdef RGBLIGHT_ENABLE
//     // rgblight_sethsv_at (200,200,200, 0);
//
//     switch (get_highest_layer(state)) {
//     case _LOWER:
//           rgblight_sethsv_range(HSV_CYAN,0,2);
//           break;
//     case _RAISE:
//           rgblight_sethsv_range(HSV_RED,0,1);
//           break;
//     case _ADJUST:
//           rgblight_sethsv_range(HSV_GREEN,0,1);
//           break;
//     default: //  for any other layers, or the default layer
//           rgblight_sethsv_range(200,200,200,0,2);
//         break;
//     }
//     rgblight_set_effect_range(0,1);
//   #endif
//   return state;
// }

#ifdef RGBLIGHT_LAYERS
// Light LEDs 1 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_CYAN}
);
// Light LEDs 1 in red when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_RED}
);
// Light LEDs 1 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_GREEN}
);
// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer     // Overrides other layers
);
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));

    return state;
}
#endif

// ロータリーエンコーダ
// void encoder_update_user(uint8_t index, bool clockwise) {
//     if (index == 0) { /* First encoder */
//         if (clockwise) {
//             tap_code(KC_VOLD);
//         } else {
//             tap_code(KC_VOLU);
//         }
//     }
// }

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
