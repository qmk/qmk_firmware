#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MACRO_TERMINAL,
  MACRO_QUIT,
  MACRO_DESKUP,
  MACRO_DESKDOWN,
  MACRO_MOVEUP,
  MACRO_MOVEDOWN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    
    case MACRO_TERMINAL:
        if (record->event.pressed) {
            // when keycode MACRO_TERMINAL is pressed
            SEND_STRING(SS_LGUI("t"));
            } else {
            //when keycode MACRO_TERMINAL is released
            }
        break;
    
    
    case MACRO_QUIT:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI("q"));
            } else {
            }
        break;


    case MACRO_DESKUP:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LGUI)SS_TAP(X_UP)SS_UP(X_LCTRL)SS_UP(X_LGUI));
            } else {
            }
        break;


    case MACRO_DESKDOWN:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LGUI)SS_TAP(X_DOWN)SS_UP(X_LCTRL)SS_UP(X_LGUI));
            } else {
            }
        break;


    case MACRO_MOVEUP:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LGUI)SS_TAP(X_UP)SS_UP(X_LSFT)SS_UP(X_LGUI));
            } else {
            }
        break;


    case MACRO_MOVEDOWN:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LGUI)SS_TAP(X_DOWN)SS_UP(X_LSFT)SS_UP(X_LGUI));
            } else {
            }
        break;
    
    }
    return true;

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_65_with_macro(
    KC_MPLY,         KC_ESC,       KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX,  KC_BSPC, KC_HOME, \
    KC_MPRV,         KC_MNXT,      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, \
    MACRO_TERMINAL,  MACRO_QUIT,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN, \
    MACRO_DESKUP,    KC_F5,        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,  \
    MACRO_DESKDOWN,  KC_DEL,       KC_LCTL, KC_LGUI, KC_LALT, KC_SPC  ,MO(_FN1),         XXXXXXX,  KC_SPC,  KC_RALT, KC_RCTL, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN1] = LAYOUT_65_with_macro(
    _______,        _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  _______, _______, \
    _______,        _______, _______, RGB_MOD, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______,        _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    MACRO_MOVEUP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    MACRO_MOVEDOWN, _______, KC_TILD, _______, _______, RGB_TOG, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  )
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    tap_code(KC_VOLU);
  } else {
    tap_code(KC_VOLD);
  }
}
