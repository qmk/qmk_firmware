/* A standard layout for the Dactyl Manuform 5x6 Keyboard */

#include QMK_KEYBOARD_H
#include "quantum.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define __________ KC_TRNS

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

enum CUSTOM_KEYCODES {
    KC_LLEFT = SAFE_RANGE,
    KC_RRIGHT,
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode)
    {
    case KC_LLEFT:
        if (record->event.pressed) {
            register_code16(C(KC_LEFT));
        } else {
            unregister_code16(C(KC_LEFT));
        }
        return false;
        break;
    case KC_RRIGHT:
        if (record->event.pressed) {
            register_code16(C(KC_RIGHT));
        } else {
            unregister_code16(C(KC_RIGHT));
        }
        return false;
        break;
    default:
        return true;
        break;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_5x6_alt(
      KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,                                       KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,
      KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                                       KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_EQL,
      KC_BSLASH, KC_A,      KC_S,      KC_D,      KC_F,      KC_G,                                       KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,
      KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,                                       KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,
                            KC_LBRC,   KC_LPRN,                                                                     KC_RPRN,   KC_RBRC,
                                                  RAISE,     KC_SPACE,  KC_DEL,               KC_BSPACE, KC_ENTER, LOWER,
                                                             KC_LCTRL,  KC_LALT,              KC_RALT,   KC_RGUI
  ),

  [_RAISE] = LAYOUT_5x6_alt(
      KC_GRAVE,  KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,                                      KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,
      KC_CAPS,   __________,KC_UP,     __________,__________,__________,                                 __________,__________,__________,__________,__________,KC_F12,
      __________,KC_LEFT,   KC_DOWN,   KC_RIGHT,  __________,__________,                                 __________,KC_LLEFT,  KC_DOWN,   KC_UP,     KC_RRIGHT, __________,
      __________,__________,__________,__________,__________,__________,                                 __________,__________,__________,__________,__________,__________,
                            __________,__________,                                                                             __________,__________,
                                                  __________,__________,__________,           __________,__________,__________,
                                                             __________,__________,           __________,__________
  ),

  [_LOWER] = LAYOUT_5x6_alt(
      KC_GRAVE,  KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,                                      KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,
      KC_CAPS,   __________,KC_PGUP,   __________,__________,__________,                                 __________,__________,__________,__________,__________,KC_F12,
      __________,KC_HOME,   KC_PGDN,   KC_END,    __________,__________,                                 __________,KC_LLEFT,  KC_DOWN,   KC_UP,     KC_RRIGHT, __________,
      __________,__________,__________,__________,__________,__________,                                 __________,__________,__________,__________,__________,__________,
                            __________,__________,                                                                             __________,__________,
                                                  __________,__________,__________,           __________,__________,__________,
                                                             __________,__________,           __________,__________
  )
};


