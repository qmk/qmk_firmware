#include "clueboard.h"

// Helpful defines
#define _______ KC_TRNS

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _BL 0
#define _FL 1
#define _CL 2

// Custom keycodes
enum custom_keycodes {
  RGB_MODE_PLAIN = SAFE_RANGE,
  RGB_MODE_BREATHE,
  RGB_MODE_RAINBOW,
  RGB_MODE_SWIRL,
  RGB_MODE_SNAKE,
  RGB_MODE_KNIGHT,
  RGB_MODE_XMAS
};

#define RGB_M_P RGB_MODE_PLAIN
#define RGB_M_B RGB_MODE_BREATHE
#define RGB_M_R RGB_MODE_RAINBOW
#define RGB_M_SW RGB_MODE_SWIRL
#define RGB_M_SN RGB_MODE_SNAKE
#define RGB_M_K RGB_MODE_KNIGHT
#define RGB_M_X RGB_MODE_XMAS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = KEYMAP(
  KC_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_GRV, KC_BSPC,        KC_PGUP, \
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,                KC_PGDN, \
  KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,                          \
  KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RO,  KC_RSFT,        KC_UP,           \
  KC_LCTL,KC_LGUI,KC_LALT,KC_MHEN,        KC_SPC, KC_SPC,                         KC_HENK,KC_RALT,MO(_FL),KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = KEYMAP(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_DEL,         KC_VOLU, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_MUTE,                KC_VOLD, \
  _______,_______,MO(_CL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                         \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,         \
  _______,_______,_______,_______,        _______,_______,                        _______,_______,MO(_FL),_______,KC_HOME,KC_PGDN,KC_END),

  /* Keymap _CL: Control layer
   */
[_CL] = KEYMAP(
  BL_STEP,RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,RGB_M_X,_______,_______,_______,_______,_______,_______,RGB_TOG,        RGB_VAI, \
  _______,_______,_______,_______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,                RGB_VAD, \
  _______,_______,MO(_CL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                         \
  MO(_FL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        RGB_SAI,         \
  _______,_______,_______,_______,        RGB_MOD,   RGB_MOD,                     _______,_______,MO(_FL),_______,RGB_HUD,RGB_SAD,RGB_HUI),
};

#define RGB_M_PL RGB_MODE_PLAIN
#define RGB_M_BR RGB_MODE_BREATHE
#define RGB_M_RA RGB_MODE_RAINBOW
#define RGB_M_SW RGB_MODE_SWIRL
#define RGB_M_SN RGB_MODE_SNAKE
#define RGB_M_KR RGB_MODE_KNIGHT

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      #ifdef RGBLIGHT_ENABLE
      case RGB_MODE_PLAIN:
        rgblight_mode(1);
        return true;
      case RGB_MODE_BREATHE:
        rgblight_mode(2);
        return true;
      case RGB_MODE_RAINBOW:
        rgblight_mode(6);
        return true;
      case RGB_MODE_SWIRL:
        rgblight_mode(9);
        return true;
      case RGB_MODE_SNAKE:
        rgblight_mode(15);
        return true;
      case RGB_MODE_KNIGHT:
        rgblight_mode(21);
        return true;
      case RGB_MODE_XMAS:
        rgblight_mode(24);
        return true;
      #endif
    }
  }
  return true;
}
