#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY = 0,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define OLED_TIMEOUT_DISABLE

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// Guide
// - Press LOWER + HOME to switch to Qwerty
// - Press LOWER + END to switch to Colemak

bool isColemak = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_ESC,          KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,      KC_5,   KC_6,                   KC_7,    KC_8,      KC_9,    KC_0,    KC_MINS,    KC_EQL,     KC_BACKSPACE, 
    KC_HOME,         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,                  KC_Y,    KC_U,    KC_I,      KC_O,    KC_P,    KC_LBRC,    KC_RBRC,    KC_BACKSLASH,
    KC_END,          KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,      KC_G,                           KC_H,    KC_J,      KC_K,    KC_L,    KC_SCLN,    KC_QUOT,    KC_ENT,
    KC_PRINT_SCREEN, KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,                           KC_N,    KC_M,      KC_COMM, KC_DOT,  KC_SLSH,    KC_LSFT,    KC_PAGE_UP,
    KC_F3,           KC_LCTL,   KC_LALT, KC_LGUI, LOWER,   KC_MS_BTN1,                                         KC_SPACE,  RAISE,   KC_RALT, KC_RCTL,    KC_DELETE,  KC_PAGE_DOWN
  ),
  [_COLEMAK] = LAYOUT(
    KC_ESC,          KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,     KC_5,   KC_6,                  KC_7,    KC_8,      KC_9,    KC_0,    KC_MINS,    KC_EQL,     KC_BACKSPACE, 
    KC_HOME,         KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,     KC_G,                 KC_J,    KC_L,    KC_U,      KC_Y,    KC_SCLN, KC_LBRC,    KC_RBRC,    KC_BACKSLASH,
    KC_END,          KC_LCTL,   KC_A,    KC_R,    KC_S,    KC_T,     KC_D,                          KC_H,    KC_N,      KC_E,    KC_I,    KC_O,       KC_QUOT,    KC_ENT,
    KC_PRINT_SCREEN, KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,                          KC_K,    KC_M,      KC_COMM, KC_DOT,  KC_SLSH,    KC_LSFT,    KC_PAGE_UP,
    KC_F3,           KC_LCTL,   KC_LALT, KC_LGUI, LOWER,   KC_MS_BTN1,                                       KC_SPACE,  RAISE,   KC_RALT, KC_RCTL,    KC_DELETE,  KC_PAGE_DOWN
  ),

  [_LOWER] = LAYOUT(
    _______, _______,      KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,                      KC_F7,       KC_F8,      KC_F9,         KC_F10,       KC_F11,     KC_F12,  KC_F3,
    QWERTY,  _______,      _______, _______, _______,  _______, _______,                    _______, KC_MS_WH_UP, KC_MS_UP,   KC_MS_WH_DOWN, _______,      _______,    _______, _______,
    COLEMAK, KC_MS_ACCEL2, _______, _______, _______,  _______, _______,                             KC_MS_BTN1,  KC_MS_LEFT, KC_MS_DOWN,    KC_MS_RIGHT,  KC_MS_BTN2, _______, _______,
    _______, _______,      _______, _______, _______,  _______, _______,                             _______,     KC_PAGE_UP, _______,       KC_PAGE_DOWN, _______,    _______, KC_VOLU, 
    _______, _______,      _______, _______, _______,  _______,                                                   KC_MS_BTN1, _______,       _______,      _______,    _______, KC_VOLD
  ),

  [_RAISE] = LAYOUT(
    _______, _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,                     KC_F7,      KC_F8,   KC_F9,        KC_F10,   KC_F11,       KC_F12,  KC_F3,
    _______, _______, _______, KC_UP,   _______,  _______, _______,                   _______, KC_PAGE_UP, KC_UP,   KC_PAGE_DOWN, _______,  _______,      _______, _______,
    _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,                            KC_HOME,    KC_LEFT, KC_DOWN,      KC_RIGHT, KC_END,       _______, _______,
    _______, _______, _______, _______, _______,  _______, _______,                            _______,    _______, _______,      _______,  _______,      _______, _______,
    _______, _______, _______, _______, _______,  _______,                                                 _______, _______,      _______,  _______,      _______, _______
  ),

  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______,  _______, _______, _______,                    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, _______,                    _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, _______,                             _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______,  _______, _______,                             _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______,  _______,                                               _______, _______, _______, _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        isColemak = false;
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        isColemak = true;
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
  }
  return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("ULTIMATE"), false);
    if (isColemak == true) {
        oled_write_P(PSTR("     COLEMAK"), false);
    } else {
        oled_write_P(PSTR("      QWERTY"), false);
    }
    oled_write_P(PSTR("\nNGOPREK\nKEYBOARD"), false);
    oled_write_P(PSTR("\nv1.2.1"), false);
    return false;
}
#endif
