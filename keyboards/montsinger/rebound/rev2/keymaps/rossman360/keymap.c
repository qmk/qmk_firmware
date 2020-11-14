#include QMK_KEYBOARD_H
#include "rossman360.h"

#define PGMOD LT(_NUM, KC_PGDN)
#define TABMOD LT(_FN1, KC_TAB)
#define SPCMOD LT(_FN1, KC_SPACE)
#define ENTMOD LT(_FN2, KC_ENTER)
#define ESCMOD LT(_NUM, KC_ESC)
#define RSMOD LT(_FN1, KC_RSHIFT)

enum layer_names {
  _BASE,
  _DEL,
  _FN1,
  _FN2,
  _NUM,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_all(
    KC_ESC  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , NTAB  ,
    JUMPBACK, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,          KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,          KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_MINS,
    CMDBSP  , ALTDEL , KC_NO  , CTRLSP , TABMOD , PGMOD  , KC_Y   , ENTMOD , SPCMOD , MO(_DEL),KC_NO  , KC_BSPC, KC_DEL
  ),

[_FN1] = LAYOUT_all(
    _______, TAB1   , TAB2   , TAB3   , TAB4   , _______,          _______, UNDO   , _______, _______, _______, CTAB   ,
    KC_CAPS, _______, _______, _______, _______, _______,          KC_HOME, KC_LEFT, KC_UP  , KC_RIGHT,KC_END , KC_NO  ,
    _______, _______, XPANDR , _______, _______, _______,          _______, PMERGE , KC_DOWN, _______, _______, _______,
    WREFRESH,_______, _______, _______, LWORD  , RWORD  , KC_Y   , RVOLD  , RVOLU  , _______, _______, _______, _______
  ),

[_FN2] = LAYOUT_all(
    _______, SPEAK1 , SPEAK2 , SPEAK3 , SPEAK4 , _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, PARADOWN, CSPEAK, KC_Y   , _______, _______, _______, _______, _______, _______
  ),

[_DEL] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______,          _______, UNDO   , _______, _______, _______, CTAB   ,
    REMCAPS, _______, _______, _______, _______, _______,          _______, KC_LEFT, KC_UP  ,KC_RIGHT, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, KC_DOWN, _______, _______, _______,
    _______, _______, _______, KC_DEL , KC_BSPC, BWORD  , KC_Y   , _______, _______, _______, _______, _______, _______
  ),

[_NUM] = LAYOUT_all(
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_6   , KC_7   , KC_8   , KC_9   , KC_MINS, KC_EQL, 
    KC_CAPS, _______, _______, _______, _______, _______,          KC_MINS, KC_4   , KC_5   , KC_6   , KC_COLN, _______,
    _______, _______, _______, _______, _______, KC_LBRC,          KC_RBRC, KC_1   , KC_2   , KC_3   , KC_BSLS, _______, 
    _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_Y   , _______, _______, KC_0   , _______, _______, _______
  )
};
