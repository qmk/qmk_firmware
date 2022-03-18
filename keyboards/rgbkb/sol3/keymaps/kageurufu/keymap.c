/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/kageurufu> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. Frank Tackitt
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H
#include "kageurufu.h"

extern keymap_config_t keymap_config;

/* Base Layout
  * ,------------------------------------------------.  ,------------------------------------------------.
  * |   `  |      |      |      |      |      |      |  |      |      |      |      |      |      | BkSp |
  * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
  * | Tab  |      |      |      |      |      |      |  |      |      |      |      |      |      |   \  |
  * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
  * | Esc  |      |      |      |      |      |      |  |      |      |      |      |      |      |   '  |
  * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
  * | Sft( |      |      |      |      |      |      |  |      |      |      |      |      |      | Sft) |
  * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
  * | Ctrl |  Win |  Win |  Alt |  FN  | Space|  RGB |  |  FN  |  FN  |   -  |   =  | Down | PgUp | PgDn |
  * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
  *                                    | Space| Bksp |  | Enter| Space|
  *                                    `-------------'  `--------=----'
  */
#define EXPAND_LAYOUT(...) LAYOUT(__VA_ARGS__, \
      KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU,                                     KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU, \
      KC_MNXT, KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU,                                                       KC_MNXT, KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = EXPAND_LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    RGB_MOD,                   KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_TAB,  _________________QWERTY_L1_________________, KC_LBRC,                   KC_RBRC, _________________QWERTY_R1_________________, KC_BSLS,
      FN_ESC,  _________________QWERTY_L2_________________, RGB_SAI,                   RGB_VAI, _________________QWERTY_R2_________________, KC_QUOT,
      KC_LSPO, _________________QWERTY_L3_________________, RGB_SAD,                   RGB_VAD, _________________QWERTY_R3_________________, KC_RSPC,
      KC_LCTL, KC_LGUI, KC_LGUI, KC_LALT, FN,      KC_SPC,  KC_MUTE, KC_BSPC, KC_ENT,  FN,      KC_SPC,  KC_MINS, KC_EQL,  KC_DOWN, KC_PGUP, KC_PGDN
  ),

  [_FN] = EXPAND_LAYOUT(
      ________________FUNCTION_L1________________, _______,                   KC_PSCR, ________________FUNCTION_R1________________,
      ________________FUNCTION_L2________________, _______,                   _______, ________________FUNCTION_R2________________,
      ________________FUNCTION_L3________________, _______,                   _______, ________________FUNCTION_R3________________,
      ________________FUNCTION_L4________________, _______,                   _______, ________________FUNCTION_R4________________,
      ________________FUNCTION_L5________________, ADJ,     KC_DEL,  _______, ADJ,     ________________FUNCTION_R5________________
      ),

  [_ADJ] = EXPAND_LAYOUT(
      _________________ADJUST_L1_________________, _______,                   _______, _________________ADJUST_R1_________________,
      _________________ADJUST_L2_________________, _______,                   _______, _________________ADJUST_R2_________________,
      _________________ADJUST_L3_________________, _______,                   _______, _________________ADJUST_R3_________________,
      _________________ADJUST_L4_________________, _______,                   _______, _________________ADJUST_R4_________________,
      _________________ADJUST_L5_________________, _______, _______, _______, _______, _________________ADJUST_R5_________________

      )

};
