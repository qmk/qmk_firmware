/* Copyright 2019 ash0x0 2021 peepeetee
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
#include "keymap.h"
// // Defines names for use in layer keycodes and the keymap
// enum layer_names {
//     _BASE,
//     _FN
// };



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi(
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,  KC_BSPC,   KC_HOME,
         KC_TAB,    KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,  KC_BSLS, KC_PGUP,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,        KC_ENT,    KC_PGDOWN,
        KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,     KC_RSFT,     KC_UP,  KC_END,
        KC_LCTL,   KC_LGUI,LT(1, KC_LALT),                     KC_SPC,                         KC_RALT,   MO(1),KC_RCTRL, KC_LEFT, KC_DOWN,  KC_RGHT
    ),
    [1] = LAYOUT_65_ansi(
        KC_GRAVE,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  _______,   KC_DELETE,
        RGB_MOD,   RGB_HUI, RGB_VAI, RGB_SAI, RGB_SPI, _______, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______, _______, _______,  _______, KC_PGUP,
        RGB_TOG,    RGB_HUD, RGB_VAD, RGB_SAD, RGB_SPD, _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______, _______,       _______,    KC_PGDOWN,
        BL_TOGG,      _______, _______, _______, _______,   QK_BOOT, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,     _______,   KC_AUDIO_VOL_UP,  KC_END,
        _______,   _______,   _______,                    _______,                         _______, _______, _______, KC_BRIGHTNESS_DOWN, KC_AUDIO_VOL_DOWN,  KC_BRIGHTNESS_UP
    ),

};

/*
Templete
    [ ] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______,
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,    _______,
        _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,   _______,  _______,
        _______,   _______,   _______,                    _______,                         _______, _______, _______, _______, _______,  _______
    ),
*/

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = {
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______,
        GREEN,   BLUE, {0, 0, 255}, PURPLE, AZURE, _______, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, _______, _______, _______, _______,  _______, _______,
        RED,    BLUE, {0, 0, 1}, PURPLE, AZURE, _______, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, _______, _______, _______,       _______,    _______,
        _______,      _______, _______, _______, _______, RED, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, _______, _______,     _______,   _______,  _______,
        _______,   _______,   _______,                    _______,                         _______, _______, _______, _______, _______,  _______
    }

};

#undef _______
#define _______ KC_TRNS
#endif



void keyboard_post_init_user(void) {
  // Call the post init code.
    dfa_state = 0; // ENGLISH
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_DELETE:
      if (record->event.pressed) {
                dfa_state = 0;
    } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case KC_SPC:
      if (record->event.pressed) {
          if ((get_mods() & MOD_BIT(KC_LGUI)) == MOD_BIT(KC_LGUI)){
              if(dfa_state == 3){
                  dfa_state = 0;
              } else {
                  dfa_state = dfa_state + 1;
              }
          }
    } else {
        // Do something else when release
      }
      return true; // Continue execution


    case KC_HOME:
      if (record->event.pressed) {
          switch(dfa_state){
            case 0 :{
                return false;
            }
            case 1 :{
                tap_code16(G(KC_SPC));
                wait_ms(100);
                tap_code16(G(KC_SPC));
                wait_ms(100);
                tap_code16(G(KC_SPC));
                dfa_state = 0;
                return false;
            }
            case 2 :{
                tap_code16(G(KC_SPC));
                wait_ms(100);
                tap_code16(G(KC_SPC));
                dfa_state = 0;
                return false;
            }
            case 3 :{
                tap_code16(G(KC_SPC));
                dfa_state = 0;
                return false;
            }
          }

        // Do something when pressed
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    // case KC_PGUP:
    //   if (record->event.pressed) {
    //       switch(dfa_state){
    //         case 0 :{
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 1;
    //             return false;
    //         }
    //         case 1 :{
    //             return false;
    //         }
    //         case 2 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 1;
    //             return false;
    //         }
    //         case 3 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 1;
    //             return false;
    //         }
    //       }
    //     // Do something when pressed
    //   } else {
    //     // Do something else when release
    //   }
    //   return false; // Skip all further processing of this key
    // case KC_PGDOWN:
    //   if (record->event.pressed) {
    //       switch(dfa_state){
    //         case 0 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 2;
    //             return false;
    //         }
    //         case 1 :{
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 2;
    //             return false;
    //         }
    //         case 2 :{
    //             return false;
    //         }
    //         case 3 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 2;
    //             return false;
    //         }
    //       }
    //     // Do something when pressed
    //   } else {
    //     // Do something else when release
    //   }
    //   return false; // Skip all further processing of this key
    // case KC_END:
    //   if (record->event.pressed) {
    //       switch(dfa_state){
    //         case 0 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 3;
    //             return false;
    //         }
    //         case 1 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 3;
    //             return false;
    //         }
    //         case 2 :{
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 3;
    //             return false;
    //         }
    //         case 3 :{
    //             return false;
    //         }
    //       }
    //     // Do something when pressed
    //   } else {
    //     // Do something else when release
    //   }
    //   return false; // Skip all further processing of this key
            case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
    default:
      return true; // Process all other keycodes normally
  }
}

void set_layer_color(int layer) {
    if (layer == 0) { return; }
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        } else if (layer != 1) {
            // Only deactivate non-defined key LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
            // If the values are all false then it's a transparent key and deactivate LED at this layer
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
}

void rgb_matrix_indicators_user(void) {

    led_t host_leds = host_keyboard_led_state();
    if (host_leds.caps_lock) {
        //rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
        rgb_matrix_set_color(30, 0x0, 0x0, 0x0);

    } else {
        //rgb_matrix_set_color(30, 0x0, 0x0, 0x0);
    }
        set_layer_color(get_highest_layer(layer_state));

}
