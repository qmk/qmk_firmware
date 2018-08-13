#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define KC_     KC_TRNS
#define XXXXXXX KC_NO

#define ESC_CMD MT(MOD_LGUI, KC_ESC)
#define RSE_ENT LT(_RAISE, KC_ENT)
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_ADJ  ADJUST

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12( \
  // .--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
       KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I,    KC_O   , KC_P   , KC_BSPC, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K,    KC_L   , KC_SCLN, KC_QUOT, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSPC, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER  , KC_SPC , KC_LSFT, RSE_ENT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT \
  // '--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
),

[_COLEMAK] = LAYOUT_ortho_4x12( \
  // .--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
       KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       ESC_CMD, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSPC, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER  , KC_SPC , KC_LSFT, RSE_ENT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT \
  // '--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
),

[_DVORAK] = LAYOUT_ortho_4x12( \
  // .--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
       KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT , \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER  , KC_SPC , KC_LSFT, RSE_ENT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT \
  // '--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
),

[_LOWER] = LAYOUT_ortho_4x12( \
  // .--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
       KC_TILD, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_MINS, KC_DEL, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_PIPE, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       _______, KC_CIRC, KC_ASTR, KC_UNDS, KC_EQL,  KC_AMPR, _______, KC_1,    KC_2,    KC_3,    KC_SLSH, _______, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       _______, _______, _______, _______, _______, _______, _______, KC_0,    _______, _______, _______, _______ \
  // '--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
),

[_RAISE] = LAYOUT_ortho_4x12( \
  // .--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
       KC_GRV,  _______, _______, KC_LPRN, KC_RPRN, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, KC_DEL, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       _______, _______, _______, KC_LCBR, KC_RCBR, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, KC_BSLS, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       _______, _______, _______, KC_LBRC, KC_RBRC, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, \
  // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  // '--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
),

[_ADJUST] =  LAYOUT_ortho_4x12( \
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
  _______, _______, RESET,   AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}