/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#include "glorious_sides.h"


//  Skitzo2000's Custom Colors
#define ORANGE_RGB        120, 26, 0
#define DARKORANGE_RGB    60, 13, 0
#define BLUE_RGB          0, 26, 255
#define DARKBLUE_RGB      0, 60, 120
//  GMMK 2 65 Default Function Layer colors
#define FUNCTION_KEYS     RGB_GREEN
#define ARROW_KEYS        ORANGE_RGB
#define MISC_KEYS         RGB_YELLOW
#define RESET_KEY         RGB_RED
#define RGB_KEYS          RGB_PURPLE
#define MEDIA_KEYS        RGB_GOLD
//  Skitzo2000's custom keys
#define TO_KEYS           BLUE_RGB


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[0] = LAYOUT(
  QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_PGDN,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 MO(2),    MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[1] = LAYOUT(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_INS,
  LCTL(KC_TAB), LCTL(KC_Q), LCTL(KC_W), LCTL(KC_E), LCTL(KC_R), LCTL(KC_T), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_TRNS, KC_TRNS,
  KC_TRNS,  LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  KC_MUTE,  KC_VOLU,  KC_VOLD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_TRNS,  RGB_VAI,  KC_HOME,
  KC_TRNS,  KC_TRNS,  KC_TRNS,                                QK_BOOT,                                KC_TRNS,  KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_MOD),

[2] = LAYOUT(
  KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,
  LCTL(KC_TAB), LCTL(KC_Q), LCTL(KC_W), LCTL(KC_E), LCTL(KC_R), LCTL(KC_T), LCTL(KC_Y), LCTL(KC_U), LCTL(KC_I), LCTL(KC_O), LCTL(KC_P), KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME,
  KC_TRNS,  LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), LCTL(KC_G), LCTL(KC_H), LCTL(KC_J), LCTL(KC_K), LCTL(KC_L), KC_TRNS, KC_TRNS, KC_ENT, KC_TRNS,
  KC_TRNS,  LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B), LCTL(KC_N), LCTL(KC_M), KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT, KC_UP, KC_END,
  KC_TRNS,  KC_TRNS, KC_TRNS,                                 KC_SPC,                                 KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[3] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
  _______,  _______,  _______,                                _______,                                _______,  _______,  _______,   _______,  _______)
};

/* bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(5, 255, 255, 255); // assuming caps lock is at led #5
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(5, 0, 0, 0);
    }
    return false;
} */

/* enum LEDLAYER {
    L0 = 0x1,
    L1 = 0x2,
    L2 = 0x4,
    L3 = 0x8,
};


uint32_t layer_state_set_user(uint32_t state) {
    if ((state & L3) == L3) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE);
    }
    else if ((state & L2) == L2) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    }
    else if ((state & L1) == L1) {
        rgblight_set_speed(150);
        rgblight_sethsv_noeeprom(RGB_PURPLE);
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_MULTISPLASH);
    }
    else if ((state & L0) == L0) {
        rgblight_set_speed(100);
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE);
    }
    else {
        rgblight_set_speed(100);
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE);
    }
    return state;
}

// RGB LED layout for GMMK 2 65%
// By Skitzo2000
// led number, function of the key

//  0,  Esc         1,  1       2,  2       3,  3       4,  4   5,  5   6,  6   7,  7   8,  8       9,  9       10, 0       11, -          12, =      13, Backspace   14, Del
//  15, Tab         16, Q       17, W       18, E       19, R       20, T   21, Y       22, U       23, I       24, O       25, P   26, [          27, ]      28, \|          29, PgUp
//  30 Caps Lock    31, A       32, S       33, D       34, F       35, G   36, H       37, J       38, K       39, L       40, ;   41, '          42, Enter  43, PgDn
//  44, Shift_L     45, Z       46, X       47, C       48, V       49, B   50, N       51, M       52, ,       53, .       54, /   55, Shift_R    56, Up     57, END
//  58, Ctrl_L      59, Win_L   60, Alt_L   61, Space   62, Alt_R   63, FN  64, Left    65, Down    66, Right

//  Side LEDs

//  Right Side          Left Side
//  67, LED 1           77, LED 11
//  68, LED 2           78, LED 12
//  69, LED 3           79, LED 13
//  70, LED 4           80, LED 14
//  71, LED 5           81, LED 15
//  72, LED 6           82, LED 16
//  73, LED 7           83, LED 17
//  74, LED 8           84, LED 18
//  75, LED 9           85, LED 19
//  76, LED 10          86, LED 20


void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(30, 255, 255, 255); //capslock key
    }

    switch(get_highest_layer(layer_state)){  // special handling per layer
        case 0:  //Layer 0
        case 1:  //layer 1
            set_glorious_side('l', DARKORANGE_RGB);
            set_glorious_side('r', DARKBLUE_RGB);
            break;
        case 2:  //layer 2
            break;
        case 3:  //layer 2
            rgb_matrix_set_color(0, DARKBLUE_RGB);  //  `~
            //Function Keys
            rgb_matrix_set_color(1, FUNCTION_KEYS);
            rgb_matrix_set_color(2, FUNCTION_KEYS);
            rgb_matrix_set_color(3, FUNCTION_KEYS);
            rgb_matrix_set_color(4, FUNCTION_KEYS);
            rgb_matrix_set_color(5, FUNCTION_KEYS);
            rgb_matrix_set_color(6, FUNCTION_KEYS);
            rgb_matrix_set_color(7, FUNCTION_KEYS);
            rgb_matrix_set_color(8, FUNCTION_KEYS);
            rgb_matrix_set_color(9, FUNCTION_KEYS);
            rgb_matrix_set_color(10, FUNCTION_KEYS);
            rgb_matrix_set_color(11, FUNCTION_KEYS);
            rgb_matrix_set_color(12, FUNCTION_KEYS);
            //TO(Layers)
            rgb_matrix_set_color(16, TO_KEYS);
            rgb_matrix_set_color(17, TO_KEYS);
            rgb_matrix_set_color(18, TO_KEYS);
            // KC_INS, KC_PSCR,  KC_SCRL,  KC_PAUS, KC_HOME
            rgb_matrix_set_color(14, MISC_KEYS);  //  KC_INS
            rgb_matrix_set_color(25, MISC_KEYS);  //  KC_PSCR
            rgb_matrix_set_color(26, MISC_KEYS);  //  KC_SCRL
            rgb_matrix_set_color(27, MISC_KEYS);  //  KC_PAUS
            rgb_matrix_set_color(57, MISC_KEYS);  //  KC_HOME
            rgb_matrix_set_color(0, MISC_KEYS);  //  `~
            // Reset
            rgb_matrix_set_color(61, RESET_KEY);  //  KC_HOME
            //RGBMatrix
            rgb_matrix_set_color(45, RGB_KEYS);  // RGB_HUI
            rgb_matrix_set_color(46, RGB_KEYS);  // RGB_HUD
            rgb_matrix_set_color(47, RGB_KEYS);  // RGB_SPD
            rgb_matrix_set_color(48, RGB_KEYS);  // RGB_SPI
            //Media
            rgb_matrix_set_color(49, MEDIA_KEYS);  // KC_MUTE
            rgb_matrix_set_color(50, MEDIA_KEYS);  // KC_VOLU
            rgb_matrix_set_color(51, MEDIA_KEYS);  // KC_VOLD
            rgb_matrix_set_color(52, MEDIA_KEYS);  // KC_MPRV
            rgb_matrix_set_color(53, MEDIA_KEYS);  // KC_MPLY
            rgb_matrix_set_color(54, MEDIA_KEYS);  // KC_MNXT
            //  Arrow Keys
            rgb_matrix_set_color(56, ARROW_KEYS);  // RGB_VAI
            rgb_matrix_set_color(64, ARROW_KEYS);  // RGB_RMOD
            rgb_matrix_set_color(65, ARROW_KEYS);  // RGB_VAD
            rgb_matrix_set_color(66, ARROW_KEYS);  // RGB_MOD
            break;
        default:
        break;
        //case #:
            //Sample options
            //rgb_matrix_set_color(1, 238, 65, 23);
            //rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_NEXUS);
            //rgb_matrix_set_color_all(238, 65, 23);
            //RGB_MATRIX_INDICATOR_SET_COLOR(0, 255, 0, 255);   //Set Color per key
    }
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_set_speed(25);
} */
