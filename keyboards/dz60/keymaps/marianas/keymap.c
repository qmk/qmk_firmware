#include QMK_KEYBOARD_H
#include "keymap.h"
#include "relativity.h"
#include "keyDefinitions.h"
#include "customLogic.h"

// planned change: store previous table names and abbreviations to allow scrolling for inner joins on table name+id and abbreviation+id.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY]=
    LAYOUT_60_ansi(
      ESCAP,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  MNUS,  EQUL,  BACKSPC,
      KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  LBRC,  RBRC,  BSLASH,
      FN_QT,    KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  COLN,  QUOT,  ENTER_OR_SQL,
      LEFTSHFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  CMMA,  PRRD,  SLSH,  RIGHT_SHIFT__PAREN,
      CTLL,  WINL,  ALTL,  SPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACE,  ALTR,  WINR,  APPR,  CTLR),

  [NAV_CLUSTER]=
    LAYOUT_60_ansi(
      _____,  PSCR,  SCRL,  PAUS,  NSRT,  HOME,  PGUP,  NMLK,  KSSH,  STAR,  KMIN,  ____,  ____,  ______,
      ______,  ____,  ____,  ____,  DEL,   END_,  PGDN,  KP_7,  KP_8,  KP_9,  PLUS,  ____,  ____,  _____,
      _______,  ____,  ____,  ____,  ____,  UPUP,  UPUP,  KP_4,  KP_5,  KP_6,  PLUS,  ____,  ___________,
      ________,  ____,  ____,  ____,  LEFT,  D_WN,  RGHT,  KP_1,  KP_2,  KP_3,  KNTR,  _________________,
      ____,  ____,  ____,  /*-----------------*/KC_KP_0/*-----------------*/,  KDOT,  KNTR,  ____,  ____),

  [GAMING]=
    LAYOUT_60_ansi(
      _____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ______,
      ______,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  _____,
         KCNO,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ___________,
      ________,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  _________________,
      ____,  KCNO,  ____,  /*------------------*/_____/*------------------*/,  ____,  KCNO,  ____,  QWRTY),

  [SQLMACROS]=
    LAYOUT_60_ansi(
      S_ALTER, ____, ____, ____, ____, ____, ____, ____, S_ASTRK, ____, ____, ____, ____,    ___________,
      ______,    ____, S_WHERE, ____, ____, ____, ____, ____, S_INRJN, S_ORDER, ____, ____, ____, ______,
      _______, KC_LBRC, S_SLCT, S_ASTRK ,S_FROM, ____, ____, ____, ____, S_LFTJN, ____, RBRC, ___________,
      ________,  RGB_VAI, RGB_VAD, ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  _________________,
      ____,  ____,  ____,  /*------------------*/_____/*------------------*/,  ____,  ____,  ____,  ____),

  [FN_LAYER]=
    LAYOUT_60_ansi(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
      KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, LWIN(KC_R), ____, KC_CALC, KC_PGUP, KC_UP, KC_PGDN, KC_PSCR, KC_SCRL, KC_BRK, ____,
      ____, KC_VOLD, KC_MUTE, KC_VOLU, ____, ____, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_INS, KC_DEL, ____,
      ____, RGB_HUI, RGB_SAI, RGB_SAD, ____,  ____, KC_END, QWRTY, GAME, NAVS, ____, ____,
      ____, ____, ____, _________________, ____, KC_HYPR, KC_MEH, QK_BOOT)
};
