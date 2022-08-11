/* A Swedish XMonad layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

enum dactyl_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

#define RAISE  MO(_RAISE)
#define LOWER  MO(_LOWER)
#define TERM   LGUI(LSFT(KC_ENT))
#define ALTTAB LGUI(KC_TAB)
#define KILL   LGUI(LSFT(KC_C))
#define OPEN   LGUI(KC_P)
#define KC_QSM LSFT(SE_PLUS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
     KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , SE_QUOT,
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,
     KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , SE_ODIA, SE_ADIA,
     KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , SE_SLSH, SE_MINS,
                       KC_EXLM, KC_QSM ,                                                            SE_PLUS, SE_EQL ,
                                                  RAISE  , KC_SPC ,      KC_ENT , LOWER  ,
                                                  ALTTAB , KC_LGUI,      KC_BSPC, KC_DEL ,
                                                  OPEN   , TERM   ,      KILL   , KC_LALT
  ),

  [_LOWER] = LAYOUT_5x6(
     SE_TILD, KC_EXLM,  SE_AT , KC_HASH, SE_DLR , KC_PERC,                        SE_CIRC, SE_AMPR, SE_ASTR, SE_SLSH, SE_LPRN, SE_RPRN,
     SE_ACUT, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, SE_LCBR, SE_RCBR,
     _______, _______, _______, _______, _______, _______,                        KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, SE_LBRC, SE_RBRC,
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, SE_LABK, SE_RABK,
                       _______, _______,                                                            _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______

  ),

  [_RAISE] = LAYOUT_5x6(
     KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
     _______, _______, _______, _______, _______, _______,                        RESET  , _______, _______, _______, KC_MUTE, SE_PIPE,
     _______, _______, _______, _______, _______, _______,                        KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_VOLU, SE_BSLS,
     _______, _______, _______, _______, _______, _______,                        _______, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, _______,
                       _______, _______,                                                            _______, _______, 
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______
  ),
};
