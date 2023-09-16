/* Copyright 2022 Murali Suresh
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,------------------------------------------------------------------------------------------.
   * | ` ~  |  1! |  2@ |  3# |  4$ |  5% |  6^ |  7& |  8* |  9( |  0) |  -  |  =  |   Bkspc   |
   * |------------------------------------------------------------------------------------------+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |     \   |
   * |------------------------------------------------------------------------------------------+
   * | Ctl_T(C) |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
   * |------------------------------------------------------------------------------------------+
   * | Shift      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |    RShift       |
   * |------------------------------------------------------------------------------------------+
   * |  MO1  |  Cmd  |  Alt  |              Space                | RAlt | Cmd  |  MO2  |  RCTL  |
   * `------------------------------------------------------------------------------------------'
   */
    [0] = LAYOUT_60_ansi(
        KC_GRAVE,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  LT(1,KC_BSPC),
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CTL_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        MO(1)  ,        KC_LGUI, KC_RALT,                            KC_SPC,                             KC_RALT, KC_RGUI, MO(2),   KC_RCTL
    ),
  /* Layer1
   * ,------------------------------------------------------------------------------------------.
   * | ` ~  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   Del     |
   * |------------------------------------------------------------------------------------------+
   * |        |     |     |     |     |     |  Y  |     |  I  |     | PScr| Slck| Paus|  Reset  |
   * |------------------------------------------------------------------------------------------+
   * |          |     |     |     |     |     | Left| Down| Up  | Rght| Home| Pgup|             |
   * |------------------------------------------------------------------------------------------+
   * | Shift      | V-  | V+  |  C  |     |     |     |     |     | End | PgDn|                 |
   * |------------------------------------------------------------------------------------------+
   * |       |       |       |              TO3                  |      |      |       |        |
   * `------------------------------------------------------------------------------------------'
   */
    [1] = LAYOUT_60_ansi(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, _______, KC_END,  _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, QK_BOOT,
        _______, KC_HOME, _______, _______, KC_PGDN, _______, KC_LEFT, KC_DOWN, KC_UP ,  KC_RGHT, _______, _______,          _______,
        _______,          _______, _______, _______, _______, KC_PGUP, NK_TOGG, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            TO(3)  ,                            _______, _______, _______, _______
    ),
    [2] = LAYOUT_60_ansi(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        _______, RGB_TOG, _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPI, RGB_SPD, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [3] = LAYOUT_60_ansi(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, TO(0),
        _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______,          _______,
        _______,          _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______,          KC_UP,
        _______, _______, _______,                            _______,                            _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
};

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
        rgb_matrix_set_color( i, red, green, blue );
    }
  }
}

void highlight_layer1(void){
    // F9-F12
    rgb_matrix_set_color(4, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(3, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(2, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(1, 0xFF, 0xFF, 0xFF);
    // F1-F4
    rgb_matrix_set_color(9, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(10, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(11, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(12, 0xFF, 0xFF, 0xFF);
    // Reset
    rgb_matrix_set_color(14, 0x99, 0x99, 0xFF);
    // Pause + Slck + PrScr
    rgb_matrix_set_color(15, 0xFF, 0x99, 0x00);
    rgb_matrix_set_color(16, 0xFF, 0x99, 0x00);
    rgb_matrix_set_color(17, 0xFF, 0x99, 0x00);
    // Pgup, Home
    rgb_matrix_set_color(39, 0x00, 0x99, 0x00);
    rgb_matrix_set_color(24, 0x00, 0x99, 0x00);
    // hjkl
    rgb_matrix_set_color(31, 0x00, 0x00, 0xFF);
    rgb_matrix_set_color(32, 0x00, 0x00, 0xFF);
    rgb_matrix_set_color(33, 0x00, 0x00, 0xFF);
    rgb_matrix_set_color(34, 0x00, 0x00, 0xFF);
    // PgDwn, End
    rgb_matrix_set_color(36, 0x00, 0x99, 0x00);
    rgb_matrix_set_color(46, 0x00, 0x99, 0x00);
}

void highlight_layer2(void){
    // Mode
    rgb_matrix_set_color(18, 0xFF, 0xFF, 0xFF);
    // Value
    rgb_matrix_set_color(19, 0x4C, 0x00, 0x99);
    rgb_matrix_set_color(20, 0x4C, 0x00, 0x99);
    // Sat
    rgb_matrix_set_color(21, 0xFF, 0xFF, 0xFF);
    rgb_matrix_set_color(22, 0xFF, 0xFF, 0xFF);
    // Hue
    rgb_matrix_set_color(23, 0x99, 0x99, 0x00);
    rgb_matrix_set_color(24, 0x99, 0x99, 0x00);
    // Toggle
    rgb_matrix_set_color(26, 0xFF, 0xFF, 0xFF);
    // Speed
    rgb_matrix_set_color(31, 0xFF, 0x99, 0x00);
    rgb_matrix_set_color(32, 0xFF, 0x99, 0x00);
}

void highlight_layer3(void) {
    int ins_key_block[9] = {25, 24, 23, 38, 37, 36, 50, 49, 48};
    for(int i  = 0; i < 9; i++) {
      rgb_matrix_set_color(ins_key_block[i], 0x00, 0x99, 0x00);
    }
    int num_key_block[9] = {20, 19, 18, 33, 32, 31, 45, 44, 43};
    for(int i  = 0; i < 9; i++) {
      rgb_matrix_set_color(num_key_block[i], 0x00, 0x09, 0x09);
    }
    int easy_arrow_keys[4] = {41, 55, 54, 53};
    for(int i  = 0; i < 4; i++) {
      rgb_matrix_set_color(easy_arrow_keys[i], 0x09, 0x00, 0x09);
    }
}

bool rgb_matrix_indicators_user(void) {
	  uint8_t this_led = host_keyboard_leds();
      if (!g_suspend_state) {
        switch (get_highest_layer(layer_state)) {
          case 1:
            highlight_layer1(); break;
          case 2:
            highlight_layer2(); break;
          case 3:
            /* rgb_matrix_layer_helper(0x03, 0x03, 0x00); */
            highlight_layer3();
            break;
          default:
            break;
        }
      }
	  if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
	        rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	  }
    return false;
}
