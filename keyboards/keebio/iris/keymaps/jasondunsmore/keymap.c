#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layers
#define _QWERTY 0 // Base layer
#define _NAVI   1 // Navigation layer
#define _NUMP   2 // Numpad layer

// Keys
#define KC_NAVI TT(_NAVI)
#define KC_NUMP TT(_NUMP)
#define KC_AGRV LALT_T(KC_GRAVE)
#define KC_AQUO RALT_T(KC_QUOTE)
#define KC_GUIE LGUI_T(KC_ESC)
#define KC_DSFT RSFT_T(KC_DEL)
#define KC_PSFT LSFT_T(KC_KP_PLUS)
#define KC_MCTL RCTL_T(KC_MINS)
#define KC_ECTL LCTL_T(KC_EQL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   KC_GUIE, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                  KC_6,   KC_7,   KC_8,   KC_9,   KC_0,  KC_BSLS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                  KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,  KC_BSPC,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   KC_AGRV, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                  KC_H,   KC_J,   KC_K,   KC_L,  KC_SCLN,KC_AQUO,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   KC_PSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  KC_NAVI,     KC_NAVI, KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,KC_DSFT,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     KC_NAVI,KC_ECTL, KC_SPC,         KC_ENT, KC_MCTL,KC_NAVI
//                  `----+----+----'        `----+----+----'
     ),

  [_NAVI] = LAYOUT(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   KC_F12,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                 KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   KC_TRNS,KC_TRNS,KC_MUTE,KC_VOLU,KC_TRNS,KC_TRNS,               KC_PGUP,KC_HOME, KC_UP, KC_END, KC_TRNS,KC_TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   KC_TRNS,KC_TRNS,KC_BRID,KC_VOLD,KC_BRIU,KC_TRNS,               KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_TRNS,KC_TRNS,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   KC_TRNS,KC_TRNS,KC_TRNS,KC_NUMP,KC_INS, KC_TRNS,KC_TRNS,     KC_TRNS,KC_TRNS,KC_CAPS,KC_LBRC,KC_RBRC,KC_TRNS,KC_TRNS,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     KC_TRNS,KC_TRNS,KC_TRNS,         KC_TRNS,KC_TRNS,KC_TRNS
//                  `----+----+----'        `----+----+----'
     ),

  [_NUMP] = LAYOUT(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,               KC_TRNS,KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,KC_TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,               KC_TRNS, KC_P7,  KC_P8,  KC_P9, KC_PPLS,KC_TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,               KC_TRNS, KC_P4,  KC_P5,  KC_P6, KC_PCMM,KC_TRNS,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,     KC_TRNS,KC_TRNS, KC_P1,  KC_P2,  KC_P3, KC_PEQL,KC_TRNS,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     KC_TRNS,KC_TRNS,KC_TRNS,         KC_PENT, KC_P0, KC_PDOT
//                  `----+----+----'        `----+----+----'
     )
};
