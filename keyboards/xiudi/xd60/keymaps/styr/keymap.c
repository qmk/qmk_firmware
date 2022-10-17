#include QMK_KEYBOARD_H

#define _BL 0
#define _FL 1
#define _LL 2

enum custom_keycodes {
  MACRO_STRING
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  [_BL] = LAYOUT_all(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_GRV,  KC_BSPC,    \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,          KC_BSLS,   \
      MO(_LL), KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NO,            KC_ENT,    \
      KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,   KC_DEL, \
      KC_LCTL, KC_LALT, KC_LGUI,                          KC_SPC,                          MO(_FL), KC_RALT, KC_LEFT,  KC_DOWN, KC_RIGHT),

  // 1: Function Layer
  [_FL] = LAYOUT_all(
      XXXXXXX,   KC_F1,     KC_F2,     KC_F3,     KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F13,   KC_F14,    \
      XXXXXXX,   RGB_TOG,   RGB_MOD,   RGB_RMOD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  RGB_HUI,  RGB_HUD,  XXXXXXX,  RGB_VAI,  RGB_VAD,  XXXXXXX,    \
      XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  \
      XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, \
      XXXXXXX,   XXXXXXX,   XXXXXXX,                    MACRO_STRING,                                            XXXXXXX,    F(0),    KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT),

  [_LL] = LAYOUT_all(
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_F13,   KC_F14,    \
      XXXXXXX,   RGB_TOG, XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,   XXXXXXX,    \
      XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,    KC_MUTE,   \
      XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,   XXXXXXX, KC_VOLU, KC_MPLY, \
      XXXXXXX,   XXXXXXX,   XXXXXXX,                    XXXXXXX,                                            XXXXXXX,    F(0),    KC_MRWD, KC_VOLD, KC_MFFD),


};

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACRO_STRING:
      if(record->event.pressed){
        SEND_STRING("My Custom String");
      }
      return false;
      break;
    default:
      return true;
  }
}

// Loop
void matrix_scan_user(void) {
  // Empty
};
