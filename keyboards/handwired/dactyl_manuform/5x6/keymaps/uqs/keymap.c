// Copyright 2022 Ulrich Spörlein (@uqs)
// SPDX-License-Identifier: GPL-2.0-or-later
// vi:et sw=4 cc=5,15,25,35,45,55,65:

#include "uqs.h"

/*
 * My custom layout macro that allows for easy diff(1) operations between
 * various keyboards. It probably doesn't make sense to you.
 */
#define LAYOUT_uqs(               \
    L00, L01, L02, L03, L04, L05, \
    L10, L11, L12, L13, L14, L15, \
    L20, L21, L22, L23, L24, L25, \
    L30, L31, L32, L33, L34, L35, \
              L42, L43,           \
         L44, L45, L54,           \
         L55, L52, L53,           \
    R00, R01, R02, R03, R04, R05, \
    R10, R11, R12, R13, R14, R15, \
    R20, R21, R22, R23, R24, R25, \
    R30, R31, R32, R33, R34, R35, \
              R42, R43,           \
         R51, R40, R41,           \
         R50, R52, R53            \
)                                 \
LAYOUT_5x6(                       \
  L00, L01, L02, L03, L04, L05,                          R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15,                          R10, R11, R12, R13, R14, R15, \
  L20, L21, L22, L23, L24, L25,                          R20, R21, R22, R23, R24, R25, \
  L30, L31, L32, L33, L34, L35,                          R30, R31, R32, R33, R34, R35, \
            L42, L43,                                              R42, R43,           \
                      L44, L45,                          R40, R41,                     \
                                L54, L55,      R50, R51,                               \
                                L52, L53,      R52, R53                                \
)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_QWER] = LAYOUT_uqs(
     QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,
     KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,
                         KC_LBRC,  KC_RBRC,
     /*thumb*/ LT_EXTD_ESC, KC_SPC, LT_MOUSE_ALT_SHIFT_INS,
      /*aux*/  QK_LEAD,  OSM_GUI,  KC_LALT,
     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINUS,
     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_GRV),
                         KC_MINS,  KC_EQL,
     /*thumb*/ LT_FUNC_SHIFT_INS, KC_ENT, LT_NUM_BSPC,
      /*aux*/  KC_RALT,  KC_APP,   QK_LEAD
  ),

  [L_WASD] = LAYOUT_uqs(
     KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,
     KC_T,     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,
     KC_G,     KC_LSFT,  KC_A,     KC_S,     KC_D,     KC_F,
     KC_B,     KC_GRV,   KC_Z,     KC_X,     KC_C,     KC_V,
                         KC_LBRC,  KC_RBRC,
     /*thumb*/ KC_LCTL,  KC_SPC,   KC_R,
      /*aux*/  A(KC_M),  KC_LGUI,  KC_LALT,
     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_GRV),
                         KC_MINS,  KC_EQL,
     /*thumb*/ DF(L_COLM), KC_ENT, KC_BSPC,
      /*aux*/  KC_F5,    KC_RALT,  KC_APP
  ),

  [L_COLM] = LAYOUT_uqs(
     KC_NO,    KC_NO,    KC_BTN2,  KC_BTN3,  KC_BTN1,  KC_NO,
     KC_BTN2,  KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,
     KC_BTN1,  KC_G_A,   KC_A_R,   KC_S_S,   KC_C_T,   KC_G,
     KC_BTN3,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,
                         MS_WHUP,  MS_WHDN,
     /*thumb*/ LT_EXTD_ESC, SFT_T(KC_SPC), LT(L_MOUSE, KC_TAB),
      /*aux*/  QK_LEAD,  OSM_GUI,  KC_LALT,
     KC_NO,    KC_BTN1,  KC_BTN2,  KC_BTN3,  KC_NO,    KC_NO,
     KC_J,     KC_L,     KC_U,     KC_Y,     KC_QUOT,  KC_NO,
     KC_M,     KC_C_N,   KC_S_E,   KC_A_I,   KC_G_O,   KC_NO,
     KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,
                         KC_NO,    KC_NO,
     /*thumb*/ LT_FUNC_SHIFT_INS, KC_ENT, LT_NUM_BSPC,
      /*aux*/  QK_LEAD,  KC_RALT,  KC_APP
  ),

  // Updated with inspiration from https://forum.colemak.com/topic/2014-extend-extra-extreme/
  // I like the AltGr trick from https://stevep99.github.io/seniply/ and should probably incorporate some stuff from it.
  [L_EXTD] = LAYOUT_uqs(
     _______,  _______,  _______,  _______,  _______,  _______,
     _______,  KC_BTN1,  KC_SCTAB, KC_PGUP,  KC_CTAB,  QK_LEAD,
     _______,  OSM_GUI,  OSM_ALT,  OSM_SFT,  OSM_CTL,  KC_RALT,
     _______,  ALT_TAB,  MS_WHUP,  MS_WHDN,  KC_PGDN,  INS_HARD,
                         _______,  _______,
     /*thumb*/ _______,  _______,  _______,
      /*aux*/  _______,  _______,  _______,
               /* ^^^^ can't be used */
     _______,  _______,  _______,  _______,  _______,  _______,
     KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_INS,   KC_NO,
     KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_DEL,   KC_NO,
     WIN_LEFT, WIN_DN,   WIN_UP,   WIN_RGHT, KC_PSTE,  KC_NO,  // KC_PSTE works in XTerm to emulate middle-click
                         _______,  _______,
     /*thumb*/ _______,  _______,  KC_BSPC,
      /*aux*/  _______,  _______,  _______
               /* ^^^^ use these */
  ),

  // TODO: maybe swap # with ;, that way I can roll :w or :wq which I need
  // often ... probably better to add a combo?
  [L_NUM] = LAYOUT_uqs(
     _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
     _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,
     _______,  KC_SCLN,  KC_COLN,  KC_LCBR,  KC_LPRN,  KC_LBRC,
     _______,  KC_CIRC,  KC_AMPR,  KC_RCBR,  KC_RPRN,  KC_RBRC,
                         KC_GRV,   KC_TILDE,
     /*thumb*/ KC_ESC,   KC_SPC,   KC_0,
      /*aux*/  _______,  _______,  _______,
               /* ^^^^ use these */
     KC_NUM,   KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,
     KC_EQUAL, KC_7,     KC_8,     KC_9,     KC_KP_PLUS,_______,
     KC_KP_ASTERISK,KC_4,KC_5,     KC_6,     MINS_UNDSCR,_______,
     KC_COMM,  KC_1,     KC_2,     KC_3,     KC_KP_SLASH,KC_KP_ENTER,  // Enter here, because thumb is occupied
                         KC_0,     KC_KP_DOT,
     /*thumb*/ _______,  _______,  _______,
      /*aux*/  _______,  _______,  _______
               /* ^^^^ can't be used */
  ),

  [L_FUNC] = LAYOUT_uqs(
     _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
     _______,  KC_NO,    KC_MUTE,  KC_VOLD,  KC_VOLU,  DF(L_WASD),
     _______,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_LCTL,  DF(L_QWER),
     _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    DF(L_COLM),
                         KC_NO,    KC_NO,
     /*thumb*/ _______,  _______,  _______,
      /*aux*/  _______,  _______,  _______,
               /* ^^^^ use these */
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
     KC_PSCR,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_NO,
     KC_SCRL,  KC_F4,    KC_F5,    KC_F6,    KC_F11,   KC_NO,
     KC_PAUS,  KC_F1,    KC_F2,    KC_F3,    KC_F12,   KC_NO,
                         KC_NO,    KC_NO,
     /*thumb*/ _______,  _______,  _______,
      /*aux*/  _______,  _______,  _______
               /* ^^^^ can't be used */
  ),

  [L_MOUSE] = LAYOUT_uqs(
     _______,  _______,  _______,  _______,  _______,  _______,
     _______,  KC_NO,    KC_BTN2,  KC_BTN3,  KC_BTN1,  KC_VOLU,
     _______,  KC_NO,    KC_ACL0,  KC_ACL1,  KC_ACL2,  KC_VOLD,
     _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_MUTE,
                         KC_NO,    KC_NO,
     /*thumb*/ _______,  _______,  _______,
      /*aux*/  _______,  _______,  _______,
               /* ^^^^ can't be used */
     _______,  _______,  _______,  _______,  _______,  _______,
     _______,  _______,  KC_MS_UP, MS_WHUP,  _______,  _______,
     MS_WHLEFT,KC_MS_L,  KC_MS_D,  KC_MS_R,  MS_WHRGHT,_______,
     _______,  MS_WHDN,  KC_BTN3,  KC_BTN4,  KC_BTN5,  _______,
                         KC_NO,    KC_NO,
     /*thumb*/ KC_NO,    KC_BTN1,  KC_BTN2,
      /*aux*/  _______,  _______,  _______
               /* use these ^^^^ */
  ),
};
