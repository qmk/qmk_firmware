#include QMK_KEYBOARD_H

#include "action_layer.h"



#define _BASE 0
#define _RAISE 1
#define _NAVIGATION 3


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// layer access
#define RSESPC LT( 1, KC_SPC)
#define NAVSPC LT( 3, KC_SPC)

// Key Combos
#define CTRLSFT LCTL(KC_LSFT)
#define CTLALTSFT LALT(LCTL(KC_LSFT))
#define CTLALTDEL LALT(LCTL(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {






[_BASE] = LAYOUT( \
    KC_KP_SLASH,  KC_KP_ASTERISK,   KC_PMNS,  KC_PPLS,    KC_PSCREEN,       KC_CAPS,    KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,       KC_F10,         KC_F11,         KC_F12,   \
    KC_P7,        KC_P8,            KC_P9,    KC_LBRC,    KC_RBRC,          KC_GRV,     KC_1,     KC_2,     KC_3,    KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,        KC_0,           KC_MINS,        KC_EQL,   \
    KC_P4,        KC_P5,            KC_P6,    KC_HOME,    KC_END,           KC_TAB,     KC_Q,     KC_W,     KC_F,    KC_P,     KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,        KC_SCLN,        KC_BSPC,        KC_BSLS,  \
    KC_P1,        KC_P2,            KC_P3,    KC_SLCK,    KC_PGUP,          KC_ESC,     KC_A,     KC_R,     KC_S,    KC_T,     KC_D,    KC_H,    KC_N,    KC_E,    KC_I,        KC_O,           KC_QUOT,        KC_ENT,   \
    KC_P0,        KC_PDOT,          KC_PENT,  KC_UP,      KC_PGDN,          KC_LSFT,    KC_Z,     KC_X,     KC_C,    KC_V,     KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,      KC_SLSH,        SFT_T(KC_ENT),  KC_PGUP,    \
    CTLALTDEL,    KC_LCTL,          KC_LEFT,  KC_DOWN,    KC_RGHT,          KC_LCTL,    CTRLSFT,  KC_LGUI,  KC_LALT,  RSESPC,   NAVSPC,  NAVSPC,  RSESPC,  KC_RGUI, KC_RALT,    KC_APPLICATION, KC_RCTL,        KC_PGDN \
),
[_RAISE] = LAYOUT( \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PAUSE,       KC_NUMLOCK, XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    _______,    _______,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        _______,    KC_EXLM,      KC_AT,      KC_HASH,    KC_DLR,         KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,        KC_RPRN,    _______,    XXXXXXX,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        KC_DEL,     KC_1,         KC_2,       KC_3,       KC_4,           KC_5,       KC_6,       KC_7,       KC_8,       KC_9,           KC_0,       _______,    _______,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        _______,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    _______,        _______,    _______,    XXXXXXX,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    _______,        _______,    _______,      _______,    _______,    _______,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        XXXXXXX,    _______,    XXXXXXX    \
),
[_NAVIGATION] = LAYOUT( \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PAUSE,       KC_NUMLOCK, XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    _______,    _______,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        _______,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    KC_HOME,    KC_PGDN,    KC_PGUP,        KC_END,     _______,    XXXXXXX,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        KC_DEL,     _______,      XXXXXXX,    KC_LSFT,    KC_LCTL,        XXXXXXX,    XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_UP,          KC_RIGHT,   _______,    _______,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        _______,    _______,      XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    _______,        _______,    _______,    XXXXXXX,    \
XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    _______,        _______,    _______,      _______,    _______,    _______,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,        XXXXXXX,    _______,    XXXXXXX    \
)
// ),
/// [_NAVIGATION] = {
//   {XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END, LCTL(KC_BSPC) },
//   {KC_DEL,              LCTL(KC_A), XXXXXXX, KC_LSFT, KC_LCTL, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_DEL},
//   {LCTL(KC_LSFT),       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, KC_RSFT, KC_RSFT, KC_ENT},
//   {LCTL(LALT(KC_LSFT)),LCTL(KC_Z),  LCTL(KC_X), LCTL(KC_C),  LCTL(KC_V), _______, _______, _______, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP),   LCTL(KC_RGHT)}
// }

};
