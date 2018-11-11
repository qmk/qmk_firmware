#include "satan.h"

// Used for GRAVE_ON_ESC
#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0 // Base Layer
#define _NA 1 // Navigation Layer
#define _FN 2 // Function Layer
#define _MA 3 // Macro layer

// Define name of macro
#define CHROME M(1)
#define SLACK M(2)
#define MAIL M(3)
#define PMAN M(4)
#define ITERM M(5)

// Alias for KC_NO
#define __n__ KC_NO

//Tap Dance Declarations
enum {
  TD_SPC_ENT = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \    |
   * |-----------------------------------------------------------|
   * |Tab~ |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backsp|
   * |-----------------------------------------------------------|
   * |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |_NA |Alt |Gui |      Space            |Cap |Alt |_FN |Macro|
   * `-----------------------------------------------------------'
   */
[_BL] = LAYOUT_60_ansi(
  F(0),    KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL, KC_BSLS, \
  F(1),  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, \
  MT(MOD_LCTL, KC_ESC), KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,  \
  KC_LSPO, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,     KC_COMM, KC_DOT, KC_SLSH,                   KC_RSPC, \
  MO(_NA), KC_LALT, KC_LGUI,                           KC_SPC,                             KC_CAPS, KC_RALT, MO(_FN), MO(_MA)),

/* Keymap _NA: Navigation Layer
   * ,-----------------------------------------------------------.
   * | ` |   |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * | `   |   |   |   |   |   |Hom|PDo|PUp|End|   |   |   |     |
   * |-----------------------------------------------------------|
   * |Ctrl   |   |   |   |   |   |Lef|Dow|Up |Rig|   |   |       |
   * |-----------------------------------------------------------|
   * |Shift   |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |_NA |Alt |Gui |                       |Cap |Alt |_FN |Macro|
   * `-----------------------------------------------------------'
   */
[_NA] = LAYOUT_60_ansi(
  KC_GRV,   __n__,    __n__,  __n__,  __n__,  __n__,  __n__,    __n__,    __n__,    __n__,    __n__,    __n__,  __n__,  __n__, \
  KC_GRV,    __n__,    __n__,  __n__,  __n__,  ITERM,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   PMAN,     __n__,  __n__,  __n__,  \
  _______,  __n__,    SLACK,  __n__,  __n__,  __n__,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, __n__,    __n__,          _______,\
  _______,  __n__,    __n__,  CHROME, __n__,  __n__,  __n__,    MAIL,     __n__,    __n__,    __n__,                    _______,\
  _______,  _______,  _______,                     _______,                         _______,  _______,_______,          _______),

/* Keymap _FN: Function Layer
   * ,-----------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  DEL  |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |Ctrl   |   |   |   |   |   |   |   |   |   |Vol-|Vol+|     |
   * |-----------------------------------------------------------|
   * |Shift   |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |_NA |Alt |Gui |                       |Cap |Alt |_FN |Macro|
   * `-----------------------------------------------------------'
   */
[_FN] = LAYOUT_60_ansi(
  LALT(LGUI(KC_ESC)),   KC_F1,    KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12, KC_DEL, \
  __n__,    __n__,    __n__,  __n__,  __n__,  __n__,  __n__,    __n__,    __n__,    __n__,   __n__,    __n__,    __n__,  __n__,  \
  _______,  __n__,    __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__, KC_VOLD,  KC_VOLU,          _______,\
  _______,  __n__,    __n__,  __n__,  __n__,  __n__,  __n__,  __n__,    __n__,    __n__,    __n__,                      _______,\
  _______,  _______,  _______,                     _______,                         _______,  _______,_______,            _______),

  /* Keymap _MA: Macro Layer
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |   |Macro|
   * `-----------------------------------------------------------'
   */
[_MA] = LAYOUT_60_ansi(
  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__, \
  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__, \
  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,          __n__,  \
  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,  __n__,                  __n__, \
  __n__,  __n__,  __n__,                           __n__,                         __n__,  __n__,  __n__,  _______),
};

enum function_id {
    GRAVE_ON_ESC,
    GRAVE_ON_TAB,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(GRAVE_ON_ESC),
  [1]  = ACTION_FUNCTION(GRAVE_ON_TAB)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case GRAVE_ON_ESC:
      shift_esc_shift_mask = get_mods()&MODS_SHIFT_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
    case GRAVE_ON_TAB:
      shift_esc_shift_mask = get_mods()&MODS_SHIFT_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_TAB);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_TAB);
          send_keyboard_report();
        }
      }
      break;
  }
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_SPC_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT)
};

// Macro
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(10), D(LGUI), T(SPC), U(LGUI), W(30), T(A), T(T), T(O), T(M), T(ENT), END  ); // type atom into spotlight
      }
      break;
    case 1:
      if (record->event.pressed) {
        return MACRO( I(10), D(LGUI), T(SPC), U(LGUI), W(30), T(C), T(H), T(R), T(O), T(M), T(E), T(ENT), END ); // type chrome into spotlight
      }
      break;
    case 2:
      if (record->event.pressed) {
        return MACRO( I(10), D(LGUI), T(SPC), U(LGUI), W(30), T(S), T(L), T(A), T(C), T(K), T(ENT), END); // type slack into spotlight
      }
      break;
    case 3:
      if (record->event.pressed) {
        return MACRO( I(10), D(LGUI), T(SPC), U(LGUI), W(30), T(M), T(A), T(I), T(L), T(ENT), END); // type mail into spotlight
      }
      break;
    case 4:
      if (record->event.pressed) {
        return MACRO( I(10), D(LGUI), T(SPC), U(LGUI), W(30), T(P), T(O), T(S), T(T), T(M), T(A), T(N), T(ENT), END); // type postman into spotlight
      }
      break;
    case 5:
      if (record->event.pressed) {
        return MACRO( I(10), D(LGUI), T(SPC), U(LGUI), W(30), T(I), T(T), T(E), T(R), T(M), T(ENT), END); // type iterm into spotlight
      }
      break;
  }
  return MACRO_NONE;
};
