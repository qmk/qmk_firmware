/* This is the Zen keyboard layout by Xyverz aka u/Zrevyx on r/mk.
   This is pretty much a direct port of my Atreus62 keymap.

   The bottom row is fairly Kinesis-ish since the Contour and Advantage
   keyboards have been my daily drivers for the last 17 years. I hope
   You can get some enjoyment out of this layout should you chose it!

CHANGELOG:

 0.1 - Initial commit. Based off of Profet's default keymap.

TODO:

 * Figure out how to make the bottom row work best for me.
 * Add legends in comments for each layer. Maybe.

*/

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _COLEMAK 2
#define _WOW 3
#define _LOWER 4
#define _RAISE 5
#define _ADJUST 16

enum atreus52_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  WOW,
  LOWER,
  RAISE
};

// Aliases to make the keymap clearer.
#define CTLBSPC CTL_T(KC_BSPC) // CTRL when held, BSPC when tapped.
#define RGB_SWR RGB_M_SW // Swirl Animation alias
#define RGB_SNK RGB_M_SN // Snake Animation alias
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT( \
    KC_RBRC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, \
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
    LOWER,   KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  KC_UP,   KC_DOWN, KC_SLSH, KC_EQL,  RAISE   \
  ),

  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL , \
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    LOWER,   KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, RAISE   \
  ),

  [_COLEMAK] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL , \
    KC_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    LOWER,   KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, RAISE   \
  ),

  [_WOW] = LAYOUT( \
    KC_RBRC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, \
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
    LOWER,   KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, CTLBSPC, KC_LALT, KC_ENT,  KC_SPC,  KC_UP,   KC_DOWN, KC_SLSH, KC_EQL,  RAISE   \
  ),

  [_LOWER] = LAYOUT( \
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
    KC_TILD, KC_GRV,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_PIPE, \
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, _______, KC_PLUS, KC_LCBR, KC_RCBR, _______, \
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, \
    _______, _______, _______, KC_HOME, KC_END,  KC_DEL,  _______, _______, KC_INS,  KC_PGUP, KC_PGDN, _______, _______, _______ \
  ),

  [_RAISE] = LAYOUT( \
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
    KC_TILD, KC_GRV,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_PIPE, \
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, _______, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, \
    _______, _______, _______, KC_HOME, KC_END,  KC_DEL,  _______, _______, KC_INS,  KC_PGUP, KC_PGDN, _______, _______, _______ \
  ),

  [_ADJUST] = LAYOUT( \
    QK_BOOT, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_SNK,                   _______, QWERTY,  COLEMAK, DVORAK,  WOW,     _______, \
    RGB_TOG, RGB_MOD, RGB_SWR, RGB_M_K, RGB_M_G, RGB_HUI,                   RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  ),

};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case DVORAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DVORAK);
          }
          return false;
          break;
        case QWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_COLEMAK);
          }
          return false;
          break;
        case WOW:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_WOW);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};
