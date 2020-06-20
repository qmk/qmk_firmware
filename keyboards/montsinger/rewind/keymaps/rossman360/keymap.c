#include QMK_KEYBOARD_H
#include "rossman360.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
  _BASE,
  _DEL,
  _FN1,
  _FN2,
  _NUM,
};

#define PGMOD LT(_NUM, KC_PGDN)
#define SPCMOD LT(_FN1, KC_SPACE)
#define ZSHIFT MT(MOD_LSFT, KC_Z)
#define TABMOD LT(_FN1, KC_TAB)
#define ESCMOD LT(_FN1, KC_1)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_ortho_5x10(
   ESCMOD,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, 
   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, 
   ZSHIFT,  KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, 
   KC_BSPC, ALTDEL,  KC_LCTRL,TABMOD,  PGMOD ,  KC_ENTER,SPCMOD, MO(_DEL), KC_BSPC, KC_DEL
),

[_FN1] = LAYOUT_ortho_5x10(
   XXXXXXX, KC_ESC,  KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,  RESET,
   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, 
   JUMPBACK,KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_LEFT, KC_UP,   KC_RIGHT,KC_END, 
   _______, KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    PMERGE,  KC_DOWN, KC_DOT,  KC_SLSH, 
   XXXXXXX, XXXXXXX, XXXXXXX, LWORD,   RWORD,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_DEL] = LAYOUT_ortho_5x10(
   RESET,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, 
   REMCAPS, KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_LEFT, KC_UP,   KC_RIGHT,KC_END, 
   XXXXXXX, KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_DOWN, KC_DOT,  KC_SLSH, 
   XXXXXXX, XXXXXXX, BLINE  , KC_BSPC, BWORD  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_NUM] = LAYOUT_ortho_5x10(
   RESET,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    NTAB,
   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_7,    KC_8,    KC_9,    KC_MINS,
   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_4,    KC_5,    KC_6,    KC_SCLN,
   XXXXXXX, KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_1,    KC_2,    KC_3,    KC_MINS,
   XXXXXXX, XXXXXXX, BLINE  , KC_BSPC, BWORD  , XXXXXXX, XXXXXXX, KC_0,    XXXXXXX, XXXXXXX
),

};
