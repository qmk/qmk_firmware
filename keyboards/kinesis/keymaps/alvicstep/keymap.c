// Copyright 2023 Alex Stepanov (@alvicstep)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,   // default layer
    _KEYPAD, // arrow keys, shifted symbols, HOME, END, PGUP, PGDN, FKeys, CTRL(TAB)
    _NUMPAD  // numpad keys
};

/* ,------------------------------------------------------------------------------------------------------------------------.
* | Esc | F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 |                           | F9 | F10 | F11 | F12 |PSCR|SLCK|PAUS|KPAD|BOOT|
* |--------+------+------+------+-------+------+--------------------------------+------+------+------+------+------+--------|
* |   -_   |  1!  |  2@  |  3#  |  4$   |  5%  |                                |  6^  |  7&  |  8*  |  9(  |  0)  |  =+    |
* |--------+------+------+------+-------+------|                                +------+------+------+------+------+--------|
* | Tab    |   Q  |   W  |   E  |   R   |   T  |                                |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+-------+------|                                |------+------+------+------+------+--------|
* | Del    |   A  |   S  |   D  |   F   |   G  |                                |   H  |   J  |   K  |   L  |  ;:  | '"     |
* |--------+------+------+------+-------+------|                                |------+------+------+------+------+--------|
* | Shift  |   Z  |   X  |   C  |   V   |   B  |                                |   N  |   M  |  ,.  |  .>  |  /?  |Sht/Ent |
* `--------+------+------+------+-------+-------                                `------+------+------+------+------+--------'
*          | `~   | Gui  | Esc  |MO(Num)|                                              | [{   |  ]}  |      |      |
*          `----------------------------'                                              `---------------------------'
*                                        ,---------------.         ,---------------.
*                                        |Alt+Tab|  Alt  |         |  Alt  |TO(Num)|
*                                 ,------|------ |-------|         |-------+-------+------.
*                                 |      |       | Shift |         | Shift |       |      |
*                                 | BkSp | KPAD  |-------|         |------ | KPAD  | Space|
*                                 |      |       | Ctrl  |         | Ctrl  |       |      |
*                                 `----------------------'         `----------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT(
KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,                 KC_F9,KC_F10,KC_F11,KC_F12,KC_PSCR,KC_SCRL,KC_PAUS,TO(_KEYPAD),QK_BOOT,
KC_MINS,KC_1,KC_2,KC_3,KC_4,KC_5,                                       KC_6,KC_7,KC_8,KC_9,KC_0,KC_EQL,
KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,                                        KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLS,
KC_DEL,KC_A,KC_S,KC_D,KC_F,KC_G,                                        KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,
KC_LSFT,KC_Z,KC_X,KC_C,KC_V,KC_B,                                       KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,SC_SENT,
KC_GRV,KC_LGUI,KC_ESC,MO(_NUMPAD),                                      KC_LBRC,KC_RBRC,KC_NO,KC_NO,
                          LALT(KC_TAB),KC_LALT,                   KC_RALT,TO(_NUMPAD),
                          KC_LSFT,                                KC_RSFT,
                          KC_BSPC,MO(_KEYPAD),KC_LCTL,            KC_RCTL,MO(_KEYPAD),KC_SPC
),
/* ,------------------------------------------------------------------------------------------------------------------------.
* |   |   |   |   |   |   |   |   |                                              |   |   |   |   |   |   |   | TO(BASE) |   |
* |--------+------+------+------+------+------+---------------------------------+------+------+------+------+------+--------|
* |   _    |   !  |  @   |  #   |  $   |  %   |                                 |  ^   |  &   |  *   |  (   |  )   |   +    |
* |--------+------+------+------+------+------|                                 |------+------+------+------+------+--------|
* |        |  F1  |  F2  |  F3  | F4   |  F5  |                                 |      | Home |  Up  | End  |      |   |    |
* |--------+------+------+------+------+------|                                 |------+------+------+------+------+--------|
* |        |  F6  |  F7  |  F8  | F9   |  F10 |                                 | Pgup | Lft  | Dwn  | Rgt  |  :   |   "    |
* |--------+------+------+------+------+------|                                 |------+------+------+------+------+--------|
* | CapsLk |      |      |      | F11  |  F12 |                                 | Pgdn |      |  <   |  >   |  ?   |        |
* `--------+------+------+------+------+------'                                 `------+------+------+------+------+--------'
*          |   ~  | INS  |      |      |                                               |  {   |  }   |      |      |
*          `---------------------------'                                               `---------------------------'
*                                        ,--------------.         ,--------------------.
*                                        |Ctl+Tab|      |         |      |      |      |
*                                 ,------|------ |------|         |------+------+------.
*                                 |      |       |Shift |         |Shift |      |      |
*                                 |      |       |------|         |------|      |      |
*                                 |      |       | Ctrl |         | Ctrl |      |      |
*                                 `-------------- ------'         `--------------------'
*/
[_KEYPAD] = LAYOUT(
 KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                 KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,TO(_BASE),KC_NO,
 KC_UNDS,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,                          KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_PLUS,
 KC_NO,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,                                   KC_NO,KC_HOME,KC_UP,KC_END,KC_NO,KC_PIPE,
 KC_CAPS,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,                                KC_PGUP,KC_LEFT,KC_DOWN,KC_RGHT,KC_COLN,KC_DQUO,
 KC_NO,KC_NO,KC_NO,KC_NO,KC_F11,KC_F12,                                 KC_PGDN,KC_NO,KC_LT,KC_GT,KC_QUES,KC_NO,
 KC_TILD,KC_INS,KC_NO,KC_NO,                                            KC_LCBR,KC_RCBR,KC_NO,KC_NO,
                                LCTL(KC_TAB),KC_NO,             KC_NO,KC_NO,
                                KC_LSFT,                        KC_RSFT,
                                KC_NO,KC_NO,KC_LCTL,            KC_RCTL,KC_NO,KC_NO
),
/*,--------+------+------+------+------+------+                           +------+------+------+------+------+--------.
* |        |      |      |      |      |      |                           |      | Base |  =   |  /   |  *   |        |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |        |      |      |      |      |      |                           |      |  7   |  8   |  9   |  -   |        |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |  Del   |      |      |      |      |      |                           |      |  4   |  5   |  6   |  +   |        |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |  BkSp  |      |      |      |      |      |                           |      |  1   |  2   |  3   |Enter | Enter  |
* `--------+------+------+------+------+------'                           `------+------+------+------+------+--------'
*          |      |      |      |      |                                         |  .   |Enter |      |      |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        |      |      |         |      | Base |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      |      |         |      |      |      |
*                                 | BkSp |      |------|         |------|      |  0   |
*                                 |      |      |      |         |      |      |      |
*                                 `--------------------'         `--------------------'
*/

[_NUMPAD] = LAYOUT(
 KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                 KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
 KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                   KC_NO,TO(_BASE),KC_EQL,KC_SLSH,KC_ASTR,KC_NO,
 KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                   KC_NO,KC_7,KC_8,KC_9,KC_MINS,KC_NO,
 KC_DEL,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                  KC_NO,KC_4,KC_5,KC_6,KC_PLUS,KC_NO,
 KC_BSPC,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                                 KC_NO,KC_1,KC_2,KC_3,KC_ENT,KC_ENT,
 KC_NO,KC_NO,KC_NO,KC_NO,                                               KC_DOT,KC_ENT,KC_NO,KC_NO,
                                KC_NO,KC_NO,                  KC_NO,TO(_BASE),
                                KC_NO,                        KC_NO,
                                KC_BSPC,KC_NO,KC_NO,          KC_NO,KC_NO,KC_0
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  //set LEDs which are triggered by a layer change
  #ifdef LED_COMPOSE_PIN
    writePin(LED_COMPOSE_PIN, !layer_state_cmp(state, _KEYPAD));
  #endif

  #ifdef LED_NUM_LOCK_PIN
    writePin(LED_NUM_LOCK_PIN, !layer_state_cmp(state, _NUMPAD));
  #endif

  return state;
};

bool led_update_user(led_t led_state) {
  #ifdef LED_CAPS_LOCK_PIN
    writePin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
  #endif

  #ifdef LED_SCROLL_LOCK_PIN
    writePin(LED_SCROLL_LOCK_PIN, !led_state.scroll_lock);
  #endif
  
  //disable default processing of LEDs
  return false;
}