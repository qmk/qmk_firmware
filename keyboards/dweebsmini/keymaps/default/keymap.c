#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define CTLESC CTL_T(KC_ESC)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_LPRN,           KC_RPRN,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
   CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_PGUP,           KC_PGDN,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                              ADJUST,  KC_LGUI, RAISE, KC_SPACE,          KC_ENTER, LOWER,   KC_RALT,  KC_RCTL  \
),





[_LOWER] = LAYOUT( \
   KC_TILD, KC_EXLM,  KC_AT,    KC_HASH,    KC_DLR,    KC_PERC,    KC_LCBR,           KC_RCBR,  KC_CIRC,  KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_BSPC, \
   KC_DEL,  KC_F1,    KC_F2,    KC_F3,      KC_F4,     KC_F5,      KC_PGUP,           KC_PGDN,  KC_F6,    KC_UNDS,    KC_PLUS,    KC_LCBR,    KC_RCBR,    KC_PIPE, \
   KC_TRNS, KC_F7,    KC_F8,    KC_F9,      KC_F10,    KC_F11,                                  KC_F12,   KC_M,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT, \
                                ADJUST,     KC_LGUI,   RAISE,      KC_SPACE,          KC_ENTER, LOWER,    KC_RALT,     KC_RCTL  \
),


[_RAISE] = LAYOUT( \
   KC_GRAVE, KC_1,    KC_2,     KC_3,       KC_4,      KC_5,       KC_LBRC,           KC_RBRC,  KC_6,     KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC, \
   KC_DEL,  KC_F1,    KC_F2,    KC_F3,      KC_F4,     KC_F5,      KC_PGUP,           KC_PGDN,  KC_F6,    KC_UNDS,    KC_PLUS,    KC_LCBR,    KC_RCBR,    KC_PIPE, \
   KC_TRNS, KC_F7,    KC_F8,    KC_F9,      KC_F10,    KC_F11,                                  KC_F12,   KC_M,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT, \
                                ADJUST,     KC_LGUI,   RAISE,      KC_SPACE,          KC_ENTER, LOWER,    KC_RALT,     KC_RCTL  \
),


[_ADJUST] =  LAYOUT( \
   KC_TRNS,  RESET,    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, \
   KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, \
   KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                               KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, \
                                   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS  \
)


};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
  }
  return true;
}
