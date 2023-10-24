#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _UPPER 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  UPPER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
               KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
     KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
      KC_BSPC, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,  KC_ENT,
     SC_LSPO,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  SC_RSPC,
                             LALT(KC_A), KC_LCTL,KC_LGUI,  MO(1),   KC_SPC,   MO(2),   KC_PGDN,     KC_NO),

[_LOWER] = LAYOUT(
               KC_ESC,LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),                  KC_SCLN,LSFT(KC_BSLS),   KC_NO,LCTL(KC_9),LCTL(KC_0),    KC_F12,
LCTL(KC_TAB),LGUI(KC_Q),LGUI(KC_W),  KC_ESC,LGUI(KC_R),LGUI(KC_T),               LCTL(KC_Y),LGUI(KC_LEFT),   KC_UP,LGUI(KC_RGHT),LSFT(KC_GRV),     KC_F11,
LGUI(KC_BSPC),MO(2),LGUI(KC_S),LGUI(KC_C),LGUI(KC_V),LGUI(KC_X),                   KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT,     KC_GRV,LSFT(KC_SCLN),
      KC_F15,LGUI(KC_A),LGUI(KC_D),  KC_F13,LGUI(KC_Z),LGUI(KC_Y),LSFT(KC_LBRC),LSFT(KC_RBRC),KC_BSPC,LGUI(KC_F), SGUI(KC_G),LGUI(KC_G),  KC_BSLS,   KC_F23,
                                  KC_NO,   KC_NO,KC_NO,KC_TRNS,    KC_NO, KC_RGUI,   KC_PGUP,     KC_NO),

[_UPPER] = LAYOUT(
            KC_VOLU,LGUI(LALT(KC_1)),LGUI(LALT(KC_2)),   KC_F3,   KC_F4,   KC_F5,                    KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,LSFT(KC_EQL),
    KC_VOLD,  KC_NO,  KC_NO,   KC_NO,SGUI(KC_R),  KC_F14,               SGUI(KC_K),SGUI(KC_LEFT),LSFT(KC_UP),SGUI(KC_RGHT),  KC_F18,LSFT(KC_MINS),
      KC_MUTE,KC_TRNS,  KC_NO, KC_LGUI,  KC_TAB,  KC_F21,                    KC_NO,LSFT(KC_LEFT),LSFT(KC_DOWN),LSFT(KC_RGHT),     KC_F20,  KC_F16,
     AS_TOGG, KC_NO,  KC_NO,   KC_NO,  KC_F22,LCTL(KC_U),LGUI(KC_LBRC),LGUI(KC_RBRC),LGUI(KC_N),   KC_NO,LALT(LSFT(KC_LEFT)),LALT(LSFT(KC_RIGHT)),   KC_F17,   KC_F19,
                                  KC_NO,   KC_NO,KC_NO,  KC_NO,    KC_NO, KC_TRNS,     KC_NO,     KC_NO)

};
