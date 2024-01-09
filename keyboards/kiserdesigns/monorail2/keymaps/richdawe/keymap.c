// Copyright 2023 Noah Kiser
// Copyright 2023 Richard Dawe
// SPDX-License-Identifier: GPL-2.0-or-later

// Based on the default layout for the Vial for Monorail.

// Convert this into a printable keymap on Linux using:
/*
grep -A13 '[=] LAYOUT(' keymap.c > monorail2-keymap-richdawe.txt
enscript -v -r -f Courier7 --media=A4 monorail2-keymap-richdawe.txt -o monorail2-keymap-richdawe.ps
ps2pdf monorail2-keymap-richdawe.ps monorail2-keymap-richdawe.pdf
*/

#include QMK_KEYBOARD_H

#define LT1_SPC LT(1, KC_SPC)
#define LT2_CAPS LT(2, KC_CAPS)
#define LT3_ESC LT(3, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT( \
  /* Base layer
   *    ,-----+-----+-----+-----+-----+-----.
   *    |Es/L3|  `  |  [  |  ]  |  -  |  =  |
   * ,--+-----+-----+-----+-----+-----+-----------------------------------------.
   * | Tab |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bspace  |
   * |--------------------------------------------------------------------------+
   * |Cps/L2|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |   '   |
   * |--------------------------------------------------------------------------+
   * | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | Up  |Sh/En|
   * |--------------------------------------------------------------------------+
   * | Ctrl | Gui | Alt  |   Space / L1  |  Space / L1 |  /   |Left |Down |Right|
   * `--------------------------------------------------------------------------'
   */
  LT3_ESC, KC_GRV,  KC_LBRC,    KC_RBRC,    KC_MINS, KC_EQL, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  LT2_CAPS,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_SENT, \
  KC_LCTL, KC_LGUI, KC_LALT, KC_LALT,     LT1_SPC,          LT1_SPC,      KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),
[1] = LAYOUT( \
/* Numbers and symbols layer
   *    ,-----+-----+-----+-----+-----+-----.
   *    |     |     |     |     |     |     |
   * ,--+-----+-----+-----+-----+-----+-----------------------------------------.
   * |  :  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |Bspace  |
   * |--------------------------------------------------------------------------+
   * |  .   |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |   \   |
   * |--------------------------------------------------------------------------+
   * |        |     |     |  ~  |  |  |  +  |  -  |     |     |     |PgUp |     |
   * |--------------------------------------------------------------------------+
   * |      |     |      |               |             |      |Home |PgDn | End |
   * `--------------------------------------------------------------------------'
   */
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_COLN, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_DOT,  S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), KC_BSLS, \
  _______, XXXXXXX, XXXXXXX, KC_TILD, KC_PIPE, KC_PLUS, KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, _______, \
  _______, _______, _______, _______,      _______,          _______,     XXXXXXX, KC_HOME, KC_PGDN, KC_END
),
[2] = LAYOUT( \
/* F-keys and media
   *    ,-----+-----+-----+-----+-----+-----.
   *    |     |     |     |     |     |     |
   * ,--+-----+-----+-----+-----+-----+-----------------------------------------.
   * | F12 |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 |  F11   |
   * |--------------------------------------------------------------------------+
   * |      |     |     |     |     |     |Left |Down | Up  |Right|     |       |
   * |--------------------------------------------------------------------------+
   * |        |     |     |     |     |     |     |     |     |Mute |VolUp|     |
   * |--------------------------------------------------------------------------+
   * |      |     |      |               |     -       |P/Paus|Prev |VolDn|Next |
   * `--------------------------------------------------------------------------'
   */
  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_F12,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLU, _______, \
  _______, _______, _______,  _______,      _______,          KC_MINS,     KC_MPLY, KC_MPRV, KC_VOLD, KC_MNXT
),
[3] = LAYOUT( \
/* RGB and boot
   *    ,-----+-----+-----+-----+-----+-----.
   *    |     |     |     |     |     |     |
   * ,--+-----+-----+-----+-----+-----+-----------------------------------------.
   * |     |     |     |     |     |     |     |     |     |     |     |        |
   * |--------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |     |     |     |     |       |
   * |--------------------------------------------------------------------------+
   * | RGBTog |RMod |RRMod| Hui | Hud | Sai | Sad | Vai | Vad | Spi | Spd |     |
   * |--------------------------------------------------------------------------+
   * | Boot |     |      |               |             |      |     |     |     |
   * `--------------------------------------------------------------------------'
   */
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, XXXXXXX, \
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,          XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
};

void keyboard_post_init_user(void) {
  setPinOutput(LED0_PIN);
  setPinOutput(LED1_PIN);
  setPinOutput(LED2_PIN);

  writePin(LED0_PIN, 1);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 1:
        writePin(LED2_PIN, 1);
        writePin(LED1_PIN, 0);
        break;
    case 2:
        writePin(LED2_PIN, 0);
        writePin(LED1_PIN, 1);
        break;
    case 3:
        writePin(LED2_PIN, 1);
        writePin(LED1_PIN, 1);
        break;
    default: //  for any other layers, or the default layer
        writePin(LED2_PIN, 0);
        writePin(LED1_PIN, 0);
        break;
    }
  return state;
}
