// Copyright 2022 Ulrich Spörlein (@uqs)
// SPDX-License-Identifier: GPL-2.0-or-later
// vi:et sw=4 cc=5,15,25,35,45,55,65:

#include "uqs.h"

/*
 * My custom layout macro that allows for easy diff(1) operations between
 * various keyboards. It probably doesn't make sense to you.
 */
#define LAYOUT_uqs(               \
    k00, k01, k02, k03, k04, k05, \
    k10, k11, k12, k13, k14, k15, \
    k20, k21, k22, k23, k24, k25, \
    k30, k31, k32, k33, k34, k35, \
         k43, k44,                \
    k40, k41, k42,                \
    k06, k07, k08, k09, k0a, k0b, \
    k16, k17, k18, k19, k1a, k1b, \
    k26, k27, k28, k29, k2a, k2b, \
    k36, k37, k38, k39, k3a, k3b, \
              k46, k48,           \
                   k49, k4a, k4b  \
)                                 \
LAYOUT_preonic_2x2u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
    k40, k41, k42, k43, k44,      k46,      k48, k49, k4a, k4b \
)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_QWER] = LAYOUT_uqs(
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,
     KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,

     /*thumb*/ LT_EXTD_ESC, KC_SPC,
      /*aux*/  KC_NO,    KC_LGUI,  KC_LALT,
     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINUS,
     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
     /*thumb*/ KC_ENT,   LT_NUM_BSPC,
      /*aux*/  MO(L_FUNC), KC_NO,  KC_NO
  ),
  [L_EXTD] = LAYOUT_uqs(
     KC_F11,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
     _______,  KC_BTN1,  KC_SCTAB, KC_PGUP,  KC_CTAB,  QK_LEAD,
     _______,  OSM_GUI,  OSM_ALT,  OSM_SFT,  OSM_CTL,  KC_RALT,
     _______,  ALT_TAB,  MS_WHUP,  MS_WHDN,  KC_PGDN,  INS_HARD,
     /*thumb*/ _______,  _______,
      /*aux*/  _______,  _______,  _______,
               /* ^^^^ can't be used */
     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F12,
     KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_INS,   KC_NO,
     KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_DEL,   KC_NO,
     WIN_LEFT, WIN_DN,   WIN_UP,   WIN_RGHT, KC_PSTE,  KC_NO,
     /*thumb*/ _______,  KC_BSPC,
      /*aux*/  _______,  _______,  KC_ENTER
               /* ^^^^ use these */
  ),

  [L_NUM] = LAYOUT_uqs(
     KC_F11,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
     _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,
     _______,  KC_SCLN,  KC_COLN,  KC_LCBR,  KC_LPRN,  KC_LBRC,
     _______,  KC_CIRC,  KC_AMPR,  KC_RCBR,  KC_RPRN,  KC_RBRC,
     /*thumb*/ KC_ESC,   _______,
      /*aux*/  _______,  _______,  _______,
               /* ^^^^ use these */
     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F12,
     KC_EQUAL, KC_7,     KC_8,     KC_9,     KC_KP_PLUS,_______,
     KC_KP_ASTERISK,KC_4,KC_5,     KC_6,     MINS_UNDSCR,_______,
     KC_COMM,  KC_1,     KC_2,     KC_3,     KC_KP_SLASH,KC_KP_ENTER,  // Enter here, because thumb is occupied
     /*thumb*/ _______,  _______,
      /*aux*/  KC_0,     KC_KP_DOT, _______
               /* ^^^^ can't be used */
  ),

  [L_FUNC] = LAYOUT_uqs(
     _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
     _______,  KC_NO,    KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_NO,
     _______,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_LCTL,  KC_NO,
     _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
     /*thumb*/ _______,  _______,
      /*aux*/  _______,  _______,  _______,
               /* ^^^^ use these */
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
     KC_PSCR,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_NO,
     KC_SCRL,  KC_F4,    KC_F5,    KC_F6,    KC_F11,   KC_NO,
     KC_PAUS,  KC_F1,    KC_F2,    KC_F3,    KC_F12,   KC_NO,
     /*thumb*/ _______,  _______,
      /*aux*/  _______,  _______,  _______
               /* ^^^^ can't be used */
  ),

  [L_MOUSE] = LAYOUT_uqs(
     KC_NO,    _______,  _______,  _______,  _______,  _______,
     KC_NO,    KC_NO,    KC_BTN2,  KC_BTN3,  KC_BTN1,  KC_VOLU,
     KC_NO,    KC_NO,    KC_ACL0,  KC_ACL1,  KC_ACL2,  KC_VOLD,
     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_MUTE,
     /*thumb*/ _______,  _______,
      /*aux*/  _______,  _______,  _______,
               /* ^^^^ can't be used */
     _______,  _______,  _______,  _______,  _______,  _______,
     _______,  _______,  KC_MS_UP, MS_WHUP,  _______,  _______,
     MS_WHLEFT,KC_MS_L,  KC_MS_D,  KC_MS_R,  MS_WHRGHT,_______,
     _______,  MS_WHDN,  KC_BTN3,  KC_BTN4,  KC_BTN5,  _______,
     /*thumb*/ KC_BTN1,  KC_BTN2,
      /*aux*/  KC_NO,    KC_NO,    KC_NO
               /* use these ^^^^ */
  ),
};
