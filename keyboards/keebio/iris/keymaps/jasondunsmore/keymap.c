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

  [_QWERTY] = LAYOUT_kc(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   GUIE, 1,   2,   3,   4,   5,                  6,   7,   8,   9,   0,  BSLS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   TAB,  Q,   W,   E,   R,   T,                  Y,   U,   I,   O,   P,  BSPC,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   AGRV, A,   S,   D,   F,   G,                  H,   J,   K,   L,  SCLN,AQUO,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   PSFT, Z,   X,   C,   V,   B,  NAVI,     NAVI, N,   M,  COMM,DOT, SLSH,DSFT,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     NAVI,ECTL, SPC,         ENT, MCTL,NAVI
//                  `----+----+----'        `----+----+----'
     ),

  [_NAVI] = LAYOUT_kc(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   F12,  F1,  F2,  F3,  F4,  F5,                 F6,  F7,  F8,  F9, F10, F11,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   TRNS,TRNS,MUTE,VOLU,TRNS,TRNS,               PGUP,HOME, UP, END, TRNS,TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   TRNS,TRNS,BRID,VOLD,BRIU,TRNS,               PGDN,LEFT,DOWN,RGHT,TRNS,TRNS,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   TRNS,TRNS,TRNS,NUMP,INS, TRNS,TRNS,     TRNS,TRNS,CAPS,LBRC,RBRC,TRNS,TRNS,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     TRNS,TRNS,TRNS,         TRNS,TRNS,TRNS
//                  `----+----+----'        `----+----+----'
     ),

  [_NUMP] = LAYOUT_kc(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,               TRNS,NLCK,PSLS,PAST,PMNS,TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,               TRNS, P7,  P8,  P9, PPLS,TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,               TRNS, P4,  P5,  P6, PCMM,TRNS,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS, P1,  P2,  P3, PEQL,TRNS,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     TRNS,TRNS,TRNS,         PENT, P0, PDOT
//                  `----+----+----'        `----+----+----'
     )
};
