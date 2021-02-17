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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE = SAFE_RANGE,
    KC_LSPC,


};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    LAYOUT(
    KC_TAB, KC_PGUP,KC_UP,  KC_PGDN,KC_HOME,KC_INS,
    KC_LCTL,KC_LEFT,KC_DOWN,KC_RGHT,KC_END, KC_DEL,
    KC_LSFT,KC_LGUI,KC_ESC, KC_LALT,KC_SPC, DF(1)
),
    LAYOUT(
    KC_ESC, KC_W,   KC_E,   KC_R,   KC_Y,   KC_BSPC,
    KC_LCTL,KC_A,   KC_D,   KC_F,   KC_H,   LCTL(KC_Z),
    KC_LSFT,KC_X,   KC_V,   KC_B,   KC_LSPC,LCTL(KC_S)
),
    LAYOUT(
    KC_ESC, KC_Q,   KC_BTN3,KC_INS, KC_NO,  KC_NO,
    KC_LCTL,KC_LBRC,KC_RBRC,KC_PGDN,KC_PGUP,LCTL(KC_Y),
    KC_LSFT,DF(3),  KC_NO,  DF(0),  _______,KC_NO
),
    LAYOUT(
    KC_ESC, KC_P0,  KC_P7,  KC_P8,  KC_P9,  KC_NLCK,
    KC_TAB, KC_PDOT,KC_P4,  KC_P5,  KC_P6,  KC_BSPC,
    KC_LSFT,KC_ENT, KC_P1,  KC_P2,  KC_P3,  DF(2)
)
};

static bool layer_shift = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSPC:
            if (record->event.pressed){
                layer_shift = 1;
                layer_on(2);
            }else{
                layer_off(2);
                if(layer_shift){
                    register_code(KC_SPC);
                    unregister_code(KC_SPC);
                }
            }
            return false;
            break;
        default:
            if (record->event.pressed){
                layer_shift = 0;
            }
            break;
    }
    return true;
}

//void encoder_update_user(uint8_t index, bool clockwise) {
//    if (index == 0) {
//        switch (layer_state) {
//            case _BASE:
//                if (clockwise) {
//                    tap_code(KC_WH_U);
//                } else {
//                    tap_code(KC_WH_D);
//                }
//                break;
//            case _PHOTO:
//            case _PHOTO_SHIFT:
//                if (clockwise) {
//                    tap_code(KC_RBRC);
//                } else {
//                    tap_code(KC_LBRC);
//                }
//                break;
//            case _FN:
//                if (clockwise) {
//                    tap_code(KC_VOLU);
//                } else {
//                    tap_code(KC_VOLD);
//                }
//            default:
//                break;
//        }
//    }
//}

//  #ifdef RGBLIGHT_LAYERS
//      const rgblight_segment_t PROGMEM mode_mac[] = RGBLIGHT_LAYER_SEGMENTS(
//          {5, 1, HSV_WHITE}
//      );
//      const rgblight_segment_t PROGMEM mode_win[] = RGBLIGHT_LAYER_SEGMENTS(
//          {5, 1, HSV_TEAL}
//      );
//      const rgblight_segment_t PROGMEM mode_photo[] = RGBLIGHT_LAYER_SEGMENTS(
//          {11, 1, HSV_TEAL}
//      );
//      const rgblight_segment_t PROGMEM mode_photo1[] = RGBLIGHT_LAYER_SEGMENTS(
//          {11, 1, HSV_BLUE}
//      );
//      const rgblight_segment_t PROGMEM mode_fn[] = RGBLIGHT_LAYER_SEGMENTS(
//          {11, 1, HSV_SPRINGGREEN}
//      );
//      const rgblight_segment_t PROGMEM mode_ja[] = RGBLIGHT_LAYER_SEGMENTS(
//          {17, 1, HSV_ORANGE}
//      );
//      const rgblight_segment_t PROGMEM mode_en[] = RGBLIGHT_LAYER_SEGMENTS(
//          {17, 1, HSV_YELLOW}
//      );
//      const rgblight_segment_t* const PROGMEM quick17_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//          mode_photo,
//          mode_photo1,
//          mode_fn,
//          mode_mac,
//          mode_win,
//          mode_ja,
//          mode_en
//      );
//      void keyboard_post_init_user(void){
//          rgblight_layers = quick17_rgb_layers;
//      }
//      layer_state_t layer_state_set_user(layer_state_t state){
//          rgblight_set_layer_state(1, layer_state_cmp(state, _PHOTO_SHIFT));
//          rgblight_set_layer_state(2, layer_state_cmp(state, _FN));
//          return state;
//      }
//      bool led_update_user(led_t led_state){
//          rgblight_set_layer_state(0, layer_state_cmp(layer_state, _PHOTO));
//          rgblight_set_layer_state(3, _mode_mac);
//          rgblight_set_layer_state(4, !_mode_mac);
//          rgblight_set_layer_state(5, _mode_ja);
//          rgblight_set_layer_state(6, !_mode_ja);
//          return true;
//      }
//  #endif
