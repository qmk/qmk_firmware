#include QMK_KEYBOARD_H
#include "keymap_german.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTZ 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// macro keys
#define CALTDEL LCTL(LALT(KC_DEL)) // ctrl-alt-del
#define CALTESC LCTL(LSFT(KC_ESC)) // ctrl-alt-esc
#define CALT LCTL(KC_LALT) // ctrl-alt

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTZ] = LAYOUT( \
  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                       DE_Z,    DE_U,    DE_I,    DE_O,    DE_P, \
  DE_A,    DE_S,    DE_D,    DE_F,    DE_G,                       DE_H,    DE_J,    DE_K,    DE_L,    KC_SPC,  \
  DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,                       DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS,  \
                     KC_LCTL, MO(_LOWER), MO(_RAISE),		      KC_LGUI, KC_LSFT, KC_LALT \
),

[_RAISE] = LAYOUT( \
  DE_EXLM,  DE_QUES,  DE_SECT, DE_DLR,  DE_HASH,                  DE_PLUS,  DE_7,  DE_8,   DE_9, DE_0,  \
  DE_CIRC,  DE_QUOT, DE_DQUO, DE_GRV, DE_AMPR,              	    DE_ASTR,  DE_4,  DE_5,   DE_6, DE_EQL, \
  DE_SLSH,  DE_PIPE,  DE_BSLS, DE_AT,   DE_EURO,                  DE_PERC,  DE_1,  DE_2,   DE_3, KC_TAB,  \
                    _______, _______, _______,        _______,  _______,  _______ \
),

[_LOWER] = LAYOUT( \
  KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,  DE_LBRC,  DE_RBRC,  KC_AUDIO_VOL_UP,  KC_HOME,      KC_PGDN,    KC_PGUP,  KC_END,   DE_TILD,  \
  KC_ESC,   DE_LABK,  DE_LPRN,  DE_RPRN,  DE_RABK,                          KC_LEFT,      KC_DOWN,    KC_UP,    KC_RIGHT, KC_ENT,  \
  KC_BSPC,  KC_DEL,   DE_LCBR,  DE_RCBR,  KC_PSCR,                        	_______,  DE_ADIA,  DE_ODIA,  DE_UDIA,  DE_SS,  \
                        _______, _______, _______,                    _______,  MO(_ADJUST), _______  \
),

[_ADJUST] = LAYOUT( \
  _______,  _______,  _______,  _______,  _______,             _______,   KC_F7,    KC_F8,    KC_F9,   KC_F10,  \
  CALTESC,  CALTDEL,  _______,  CALT,     _______,             _______,   KC_F4,    KC_F5,    KC_F6,   KC_F11,  \
  QK_BOOT,  _______,  _______,  _______,  _______,             _______,   KC_F1,     KC_F2,    KC_F3,   KC_F12,  \
                          _______,  _______,  _______,      _______,  _______,  _______  \
)};

void matrix_init_user(void) {
  set_single_persistent_default_layer(_QWERTZ);
};
