/* Copyright 2023 Tom Sennewald (@beelzebubi)
  * Copyright 2021 HellSingCoder
 * SPDX-License-Identifier: GPL-2.0-or-later
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
#include "nazu.h"


extern uint8_t is_master;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |  ;   |  '   |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * |LShift|   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Enter /        \Space \ |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \|      |      |      |
 *                   `--------------------'------´            `------'--------------------´
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,  KC_1,   KC_2,   KC_3,    KC_4,    KC_5,                    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                    KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_LCTL, KC_A,   KC_S,   KC_D,    KC_F,    KC_G,                    KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  TD_CAPS, KC_Z,   KC_X,   KC_C,    KC_V,    KC_B,  KC_LBRC, KC_RBRC, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_MINS, KC_RSFT,
                           KC_LALT, KC_LGUI, LOWER, KC_SPC,  KC_ENT,  RAISE,  KC_BSPC, KC_RALT
),
/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCTRL|   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space /        \ Enter\ |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \|      |      |      |
 *                   `--------------------'------´            `------'--------------------´
 */

[_COLEMAK_DH] = LAYOUT(
  KC_ESC,  KC_1,   KC_2,   KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,  KC_Q,   KC_W,   KC_F,    KC_P,    KC_B,                    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  KC_LCTL, KC_A,   KC_R,   KC_S,    KC_T,    KC_G,                    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  TD_CAPS, KC_Z,   KC_X,   KC_C,    KC_D,    KC_V,  KC_LBRC, KC_RBRC, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                           KC_LALT, KC_LGUI, LOWER, KC_SPC,  KC_ENT,  RAISE,   KC_BSPC, KC_RALT
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   @  |   $  |   %  |   ?  | PgUp |                    | HOME |   {  |   }  |   <  |   >  | PrnSc|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   ^  |   _  |   =  |   ~  | PgDn |-------.    ,-------|  END |   (  |   )  |   [  |   ]  |      |
 * |------+------+------+------+------+------|       |    |   |   |------+------+------+------+------+------|
 * |LShift|      |      |   ;  |   :  |      |-------|    |-------|   ´  |   '  |   "  |      |      |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space /        \ Enter\ |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \|      |      |      |
 *                   `--------------------'------´            `------'--------------------´
 */
[_LOWER] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,      KC_F4,   KC_F5,      KC_F6,                        KC_F7,   KC_F8,      KC_F9,      KC_F10,     KC_F11,    KC_F12,
  _______, S(KC_2), S(KC_4),    S(KC_5), S(KC_SLSH), KC_PGUP,                      KC_HOME, S(KC_LBRC), S(KC_RBRC), S(KC_COMM), S(KC_DOT), KC_PSCR,
  _______, S(KC_6), S(KC_MINS), KC_EQL,  S(KC_GRV),  KC_PGDN,                      KC_END,  S(KC_9),    S(KC_0),    KC_LBRC,    KC_RBRC,   XXXXXXX,
  _______, XXXXXXX, XXXXXXX,    KC_SCLN, S(KC_SCLN), XXXXXXX, XXXXXXX, S(KC_BSLS), KC_GRV,  KC_QUOT,    S(KC_QUOT), XXXXXXX,    XXXXXXX,   _______,
                                _______, _______,    _______, _______, _______,    _______, KC_DEL,     _______
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |                    |   .  |   7  |   8  |   9  |   /  |   *  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL | Left | Down |Right |      |      |-------.    ,-------|   ,  |   4  |   5  |   6  |   +  |   -  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|      |      |      |      |      |-------|    |-------|   0  |   1  |   2  |   3  |      |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space /        \ Enter\ |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \|      |      |      |
 *                   `--------------------'------´            `------'--------------------´
 */

[_RAISE] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,                     KC_DOT,  KC_P7,   KC_P8,   KC_P9,   KC_PSLS, KC_PAST,
  _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,                     KC_COMM, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_PMNS,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  KC_P0,   KC_P1,   KC_P2,   KC_P3,   XXXXXXX, _______,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |RESET |      |      |      |      |      |                    |RGB TG| HUE+ | SAT+ | VAL+ |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |QWERTY|      |COLEMK|      |                    | MODE | HUE- | SAT- | VAL- |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | MUTE |VOLDO | VOLUP|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV |PLAY  | NEXT |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space /        \ Enter\ |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \|      |      |      |
 *                   `--------------------'------´            `------'--------------------´
 */
  [_ADJUST] = LAYOUT(
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, QWERTY,  XXXXXXX, CLMKDH,  XXXXXXX,                    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_SWAP, KC_NORM, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                               _______, _______,    _______,  _______, _______, _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

bool oled_task_user(void) {
    /* KEYBOARD PET VARIABLES START */

    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    /* KEYBOARD PET VARIABLES END */

    if (is_keyboard_master()) {
        // print_luna_status_narrow();
        print_status_narrow();
    } else {
        // print_logo_narrow();
        render_space(); // Call this to render the space stuff on the one screen
    }
    return false;
}

#endif // OLED_ENABLE


/* RGB Matrix related code */
#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { { // underlight fehlt noch...
    // Key Matrix to LED Index
//   {     11,     10,      9,      8,      7,      6, NO_LED, NO_LED,      5,      4,      3,      2,      1,      0},
//   {     23,     22,     21,     20,     19,     18, NO_LED, NO_LED,     17,     16,     15,     14,     13,     12},
//   {     35,     34,     33,     32,     31,     30, NO_LED, NO_LED,     29,     28,     27,     26,     25,     24},
//   {     49,     48,     47,     46,     45,     44,     43,     42,     41,     40,     39,     38,     37,     36},
//   { NO_LED, NO_LED, NO_LED,     57,     56,     55,     54,     53,     52,     51,     50, NO_LED, NO_LED, NO_LED},

//   {     11,     10,      9,      8,      7,      6,                      5,      4,      3,      2,      1,      0},
//   {     23,     22,     21,     20,     19,     18,                     17,     16,     15,     14,     13,     12},
//   {     35,     34,     33,     32,     31,     30,                     29,     28,     27,     26,     25,     24},
//   {     49,     48,     47,     46,     45,     44,     43,     42,     41,     40,     39,     38,     37,     36},
//   {                             57,     56,     55,     54,     53,     52,     51,     50                        },

    {  0,  1,  2,  3,  4,  5 },
    {  6,  7,  8,  9, 10, 11 },
    { 12, 13, 14, 15, 16, 17 },
    { 18, 19, 20, 21, 22, 23 },
    { NO_LED, 24, 25, 26, 27, 28 },
    { 29, 30, 31, 32, 33, 34 },
    { 35, 36, 37, 38, 39, 40 },
    { 41, 42, 43, 44, 45, 46 },
    { 47, 48, 49, 50, 51, 52 },
    { NO_LED, 53, 54, 55, 56, 57 },
}, {
    // LED Index to Physical Position
    {   0,   0 }, {  16,   0 }, {  32,   0 }, {  48,   0 }, {  64,   0 }, {  80,   0 },
    {   0,  16 }, {  16,  16 }, {  32,  16 }, {  48,  16 }, {  64,  16 }, {  80,  16 },
    {   0,  32 }, {  16,  32 }, {  32,  32 }, {  48,  32 }, {  64,  32 }, {  80,  32 },
    {   0,  48 }, {  16,  48 }, {  32,  48 }, {  48,  48 }, {  64,  48 }, {  80,  48 },
                  {  48,  64 }, {  64,  64 }, {  80,  64 }, {  96,  64 }, {  96,  48 },
    { 128,   0 }, { 144,   0 }, { 160,   0 }, { 176,   0 }, { 192,   0 }, { 224,   0 },
    { 128,  16 }, { 144,  16 }, { 160,  16 }, { 176,  16 }, { 192,  16 }, { 224,  16 },
    { 128,  32 }, { 144,  32 }, { 160,  32 }, { 176,  32 }, { 192,  32 }, { 224,  32 },
    { 128,  48 }, { 144,  48 }, { 160,  48 }, { 176,  48 }, { 192,  48 }, { 224,  48 },
                  { 128,  64 }, { 144,  64 }, { 160,  64 }, { 112,  64 }, { 112,  48 },
}, {
    // LED Index to Flag (1 - modifier, 2 - underglow, 4 - key backlight)
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
       1, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
       1, 1, 1, 1, 1,
} };

#endif

/* Rotary encoder related code */
#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // Encoder on master side
    if(IS_LAYER_ON(_RAISE)) { // on Raise layer
      // Cursor control
      if (clockwise) {
          tap_code(KC_MNXT);
      } else {
          tap_code(KC_MPRV);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_VOLU);
      } else {
          tap_code(KC_VOLD);
      }
    }
  }
  else if (index == 1) { // Encoder on slave side
    if(IS_LAYER_ON(_LOWER)) { // on Lower layer
      //
      if (clockwise) {
          tap_code(KC_RIGHT);
      } else {
          tap_code(KC_LEFT);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_DOWN);
      } else {
          tap_code(KC_UP);
      }
    }
  }
    return true;
}
#endif // ENCODER_ENABLE
