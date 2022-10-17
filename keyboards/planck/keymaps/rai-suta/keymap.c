// This keymap assumes that the keyboard is recognized as JIS keyboard from the OS.

#include QMK_KEYBOARD_H
#include "version.h"

#include "sendstring_japanese.h"

// JIS keyboard
#define JK_CIRC KC_EQL      // ^
#define JK_AT   KC_LBRC     // @
#define JK_LBRC KC_RBRC     // [
#define JK_CLN  KC_QUOT     // :
#define JK_RBRC KC_BSLS     // ]
#define JK_BSLS KC_RO       // Backslash(\)
#define JK_DQT  S(KC_2)     // "
#define JK_AMPR S(KC_6)     // &
#define JK_SQT  S(KC_7)     // '
#define JK_LPRN S(KC_8)     // (
#define JK_RPRN S(KC_9)     // )
#define JK_S0   S(KC_0)     // Tilde(~) at IBM 5576-A01 spec
#define JK_EQ   S(KC_MINS)  // =
#define JK_TLD  S(JK_CIRC)  // ~
#define JK_PIPE S(KC_JYEN)  // |
#define JK_GRV  S(JK_AT)    // `
#define JK_LCBR S(JK_LBRC)  // {
#define JK_PLUS S(KC_SCLN)  // +
#define JK_ASTR S(JK_CLN)   // *
#define JK_RCBR S(JK_RBRC)  // }
#define JK_QUES S(KC_SLSH)  // ?
#define JK_UNDS S(JK_BSLS)  // _

enum user_macro {
  UM_MHEN,
  UM_HENK,
  UM_DEBUG,
};
#define M_MHEN  MACROTAP(UM_MHEN)
#define M_HENK  MACROTAP(UM_HENK)
#define M_DEBUG M(UM_DEBUG)

enum keymap_layer {
  KL_QWERTY,
  KL_LOWER,
  KL_RAISE,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [KL_QWERTY] = LAYOUT_planck_grid(
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  JK_CLN,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    KC_ZKHK, KC_KANA, KC_LGUI, KC_LALT,  M_MHEN,  KC_SPC,  KC_SPC,  M_HENK, KC_RALT, KC_RGUI,  KC_APP,  KC_ENT
  ),

  [KL_LOWER] = LAYOUT_planck_grid(
    KC_GESC, KC_EXLM,  JK_DQT, KC_HASH,  KC_DLR, KC_PERC, JK_AMPR,  JK_SQT, JK_LPRN, JK_RPRN,   JK_S0,  KC_DEL,
    _______, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,   JK_EQ,  JK_TLD,  JK_GRV, JK_LCBR, JK_PIPE,
    _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y), XXXXXXX,  KC_ENT, KC_LABK, KC_RABK, JK_RCBR, JK_UNDS,
      QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [KL_RAISE] = LAYOUT_planck_grid(
    KC_CAPS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_MINS, JK_CIRC,   JK_AT, JK_LBRC, KC_JYEN,
    _______,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12, XXXXXXX, KC_COMM,  KC_DOT, JK_RBRC, JK_BSLS,
    M_DEBUG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  dprintf( "record.\n"
           "  event.pressed = %u\n"
           "  tap.count = %u\n"
           "  tap.interrupted = %u\n"
              , record->event.pressed
              , record->tap.count
              , record->tap.interrupted );
  dprintf( "id = %u\n", id );
  dprintf( "opt = %u\n", opt );

  switch(id) {

    case UM_MHEN: {
      return MACRO_TAP_HOLD_LAYER( record, MACRO(TYPE(KC_MHEN), END), KL_LOWER );
    } break;

    case UM_HENK: {
      return MACRO_TAP_HOLD_LAYER( record, MACRO(TYPE(KC_HENK), END), KL_RAISE );
    } break;

    case UM_DEBUG: {
      if (record->event.pressed) {
        debug_enable = !debug_enable;
        if (debug_enable) {
          dprint("\nDEBUG: enabled.\n");
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
      }
    } break;

  }
  return MACRO_NONE;
};
