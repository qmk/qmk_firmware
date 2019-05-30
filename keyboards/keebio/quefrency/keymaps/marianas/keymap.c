#include QMK_KEYBOARD_H
#include "keymap.h"
#include "relativity.h"
#include "keyDefinitions.h"
#include "customLogic.h"

// planned change: store previous table names and abbreviations to allow scrolling for inner joins on table name+id and abbreviation+id.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY]=
    LAYOUT(
      ESCAP,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  MNUS,  EQUL, KC_DEL, BACKSPC,
      KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  LBRC,  RBRC,  BSLASH,
      FN_QT,    KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  COLN,  QUOT,  ENTER_OR_SQL,
      LEFTSHFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  CMMA,  PRRD,  SLSH,  RIGHT_SHIFT__PAREN, RIGHT_SHIFT__PAREN,
      CTLL,  WINL,  ALTL, KC_SPC,  KC_SPC,KC_SPC,LWIN(ESCAP),ALTR,  WINR, KC_MEH, APPR,  CTLR),

  [SQLMACROS]=
    LAYOUT(
      S_ALTER, R_D1,  R_D2,  R_D3,  R_D4,  R_D5,  R_D6,  R_D7,  R_D8, R_D9,  R_D10, R_D12, R_D20, ____,  ______,
      ______,    ____, S_WHERE, ____, ____, ____, ____, ____, S_INRJN, S_ORDER, ____, ____, ____, ______,
      _______, KC_LBRC, S_SLCT, S_ASTRK ,S_FROM, S_GROUP, ____, ____, ____, S_LFTJN, ____, RBRC, ___________,
      ________,  RGB_VAI, RGB_VAD, S_COUNT,  ____,  ____,  S_NOT,  ____,  ____,  ____,  ____,  _________________, ____,
      ____,  ____,  ____, ____, LSFT(KC_LBRC), RSFT(KC_RBRC), ____, ____,  ____,  ____,  ____,  RESET),

  [FN_LAYER]=
    LAYOUT(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_DEL,
      KC_CAPSLOCK, KC_MPRV, KC_MPLY, KC_MNXT, LWIN(KC_R), ____, KC_CALC, KC_PGUP, KC_UP, KC_PGDN, KC_PSCR, KC_SLCK, KC_BRK, ____,
      ____, KC_VOLD, KC_MUTE, KC_VOLU, ____, ____, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_INS, KC_DEL, ____,
      ____, RGB_HUI, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_END, QWRTY, ____, ____, ____, ____, ____,
      ____, ____, ____, ____, KC_LBRC, KC_RBRC, ____, ____, ____, ____, ____, RESET)

};
