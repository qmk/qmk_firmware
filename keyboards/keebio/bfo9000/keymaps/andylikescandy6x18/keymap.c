#include QMK_KEYBOARD_H

#include "action_layer.h"



#define _BASE 0
#define _QWERTY 1
#define _RAISE 2
#define _NAVIGATION 3

//Switch Layouts
#define SWBASE M(_BASE)
#define SWQWERTY M(_QWERTY)

// layer access
#define RSESPC LT( 2, KC_SPC)
#define NAVSPC LT( 3, KC_SPC)

// Key Combos
#define CTRLSFT LCTL(KC_LSFT)
#define CTLALTSFT LALT(LCTL(KC_LSFT))
#define CTLALTDEL LALT(LCTL(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT( \
    CTLALTSFT,  KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,         KC_F6,          KC_F7,            KC_F8,        KC_F9,          KC_F10,     KC_F11,             KC_F12,  KC_PSCREEN,  KC_PAUSE,   KC_CAPS,    KC_INSERT,      KC_EQL,     \
    KC_GRV,     KC_1,     KC_2,     KC_3,    KC_4,     KC_5,          KC_HOME,        KC_NUMLOCK,       KC_KP_SLASH,  KC_KP_ASTERISK, KC_LBRC,    KC_RBRC,              KC_6,    KC_7,        KC_8,       KC_9,       KC_0,           KC_MINS,   \
    KC_TAB,     KC_Q,     KC_W,     KC_F,    KC_P,     KC_G,          KC_END,         KC_P7,            KC_P8,        KC_P9,          KC_PMNS,    KC_PGUP,              KC_J,    KC_L,        KC_U,       KC_Y,       KC_SCLN,        KC_BSPC,         \
    KC_ESC,     KC_A,     KC_R,     KC_S,    KC_T,     KC_D,          KC_DEL,         KC_P4,            KC_P5,        KC_P6,          KC_PPLS,    KC_PGDN,              KC_H,    KC_N,        KC_E,       KC_I,       KC_O,           KC_QUOT,          \
    KC_LSFT,    KC_Z,     KC_X,     KC_C,    KC_V,     KC_B,          SFT_T(KC_ENT),  KC_P1,            KC_P2,        KC_P3,          KC_UP,      KC_BSLASH,            KC_K,    KC_M,        KC_COMM,    KC_DOT,     KC_SLSH,        SFT_T(KC_ENT),      \
    KC_LCTL,    CTRLSFT,  KC_LGUI,  KC_LALT, RSESPC,   NAVSPC,        KC_LCTL,        KC_P0,            KC_PDOT,      KC_LEFT,        KC_DOWN,    KC_RGHT,              NAVSPC,  RSESPC,      KC_RALT,    KC_RGUI,    KC_APPLICATION, KC_RCTL       \
),
[_QWERTY] = LAYOUT( \
    CTLALTSFT,  KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,         KC_F6,          KC_F7,            KC_F8,        KC_F9,          KC_F10,     KC_F11,               KC_F12,  KC_PSCREEN,  KC_PAUSE,   KC_CAPS,    KC_INSERT,      KC_EQL,     \
    KC_GRV,     KC_1,     KC_2,     KC_3,    KC_4,     KC_5,          KC_HOME,        KC_NUMLOCK,       KC_KP_SLASH,  KC_KP_ASTERISK, KC_LBRC,    KC_RBRC,              KC_6,    KC_7,        KC_8,       KC_9,       KC_0,           KC_MINS,   \
    KC_TAB,     KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,          KC_END,         KC_P7,            KC_P8,        KC_P9,          KC_PMNS,    KC_PGUP,              KC_Y,    KC_U,        KC_I,       KC_O,       KC_P,        KC_BSPC,         \
    KC_ESC,     KC_A,     KC_S,     KC_D,    KC_F,     KC_G,          KC_DEL,         KC_P4,            KC_P5,        KC_P6,          KC_PPLS,    KC_PGDN,              KC_H,    KC_J,        KC_K,       KC_L,       KC_SCLN,           KC_QUOT,          \
    KC_LSFT,    KC_Z,     KC_X,     KC_C,    KC_V,     KC_B,          SFT_T(KC_ENT),  KC_P1,            KC_P2,        KC_P3,          KC_UP,      KC_BSLASH,            KC_N,    KC_M,        KC_COMM,    KC_DOT,     KC_SLSH,        SFT_T(KC_ENT),      \
    KC_LCTL,    CTRLSFT,  KC_LGUI,  KC_LALT, RSESPC,   NAVSPC,        KC_LCTL,        KC_P0,            KC_PDOT,      KC_LEFT,        KC_DOWN,    KC_RGHT,              NAVSPC,  RSESPC,      KC_RALT,    KC_RGUI,    KC_APPLICATION, KC_RCTL       \
),
[_RAISE] = LAYOUT( \
    CTLALTDEL,  SWBASE,     SWQWERTY,   XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,                   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    \
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,                   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    _______,    \
    _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,         KC_PERC,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,   _______,    LCTL(KC_PGUP),             KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    _______,        \
    KC_DEL,     KC_1,       KC_2,       KC_3,       KC_4,           KC_5,       XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,   _______,    LCTL(KC_PGDN),             KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,      \
    _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    _______,      XXXXXXX,    XXXXXXX,    XXXXXXX,   _______,    LSFT(KC_BSLASH),           XXXXXXX,    _______,    _______,    _______,    _______,    _______,    \
    _______,    _______,    _______,    _______,    _______,        _______,    _______,      _______,    _______,    _______,   _______,    _______,                   _______,    _______,    _______,    _______,    _______,    _______    \
),
[_NAVIGATION] = LAYOUT( \
    CTLALTDEL,  SWBASE,     SWQWERTY,   XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX,                   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        \
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,   XXXXXXX,                   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        \
    _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,   LCTL(KC_PGUP),             XXXXXXX,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     _______,       \
    KC_DEL,     _______,    XXXXXXX,    KC_LSFT,    KC_LCTL,        XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,   LCTL(KC_PGDN),             XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______,        \
    _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    _______,      XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,   LSFT(KC_BSLASH),           XXXXXXX,    XXXXXXX,    _______,    _______,    _______,    _______,        \
    _______,    _______,    _______,    _______,    _______,        _______,    _______,      _______,    _______,    _______,    _______,   _______,                   _______,    _______,    _______,    _______,    _______,    _______      \
)


};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _BASE:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_BASE);
          }
          break;
        case _QWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          break;
      }
    return MACRO_NONE;
};
