#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _COLEMAK 2
#define _LOWER 5
#define _RAISE 6
#define _ADJUST 16

enum ergotravel_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  LOWER,
  RAISE
};

// Fillers to make layering more clear
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT ( /* dvorak */
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_PGUP, KC_HOME, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_PGDN, KC_END,  KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_LGUI, KC_ENT,  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT,          LOWER,   KC_BSPC, KC_SPC,  RAISE,            KC_UP,   KC_DOWN, KC_RGUI, KC_ENT
  ),

  [_QWERTY] = LAYOUT ( /* qwerty */
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_PGUP, KC_HOME, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PGDN, KC_END,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI, KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT,          LOWER,   KC_BSPC, KC_SPC,  RAISE,            KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_COLEMAK] = LAYOUT ( /* colemak */
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_PGUP, KC_HOME, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_PGDN, KC_END,  KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI, KC_ENT,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT,          LOWER,   KC_BSPC, KC_SPC,  RAISE,            KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_LOWER] = LAYOUT ( /* lower */
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
    _______, _______, KC_HOME, KC_END,           _______, KC_DEL,  KC_INS,  _______,          KC_PGUP, KC_PGDN, _______, _______
  ),

  [_RAISE] = LAYOUT ( /* raise */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
    _______, _______, KC_HOME, KC_END,           _______, KC_DEL,  KC_INS,  _______,          KC_PGUP, KC_PGDN, _______, _______
  ),

  [_ADJUST] = LAYOUT (
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    _______, RESET,   _______, _______, _______, _______, _______, _______, _______, QWERTY,  COLEMAK, DVORAK,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______, _______, _______, _______,          _______, _______, _______, _______
  ),

};

void matrix_init_user(void) {
#ifdef BOOTLOADER_CATERINA
   // This will disable the red LEDs on the ProMicros
   setPinInput(D5);
   writePinLow(D5);
   setPinInput(B0);
   writePinLow(B0);
#endif
};

const uint16_t PROGMEM fn_actions[] = {
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      }
    return true;
};