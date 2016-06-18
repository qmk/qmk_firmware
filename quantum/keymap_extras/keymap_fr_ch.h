#ifndef KEYMAP_FR_CH
#define KEYMAP_FR_CH

#include "keymap.h"

// Alt gr
#define ALGR(kc) kc | 0x1400
#define FR_CH_ALGR KC_RALT

// normal characters
#define FR_CH_Z KC_Y
#define FR_CH_Y KC_Z

#define FR_CH_A KC_A
#define FR_CH_B KC_B
#define FR_CH_C KC_C
#define FR_CH_D KC_D
#define FR_CH_E KC_E
#define FR_CH_F KC_F
#define FR_CH_G KC_G
#define FR_CH_H KC_H
#define FR_CH_I KC_I
#define FR_CH_J KC_J
#define FR_CH_K KC_K
#define FR_CH_L KC_L
#define FR_CH_M KC_M
#define FR_CH_N KC_N
#define FR_CH_O KC_O
#define FR_CH_P KC_P
#define FR_CH_Q KC_Q
#define FR_CH_R KC_R
#define FR_CH_S KC_S
#define FR_CH_T KC_T
#define FR_CH_U KC_U
#define FR_CH_V KC_V
#define FR_CH_W KC_W
#define FR_CH_X KC_X

#define FR_CH_0 KC_0
#define FR_CH_1 KC_1
#define FR_CH_2 KC_2
#define FR_CH_3 KC_3
#define FR_CH_4 KC_4
#define FR_CH_5 KC_5
#define FR_CH_6 KC_6
#define FR_CH_7 KC_7
#define FR_CH_8 KC_8
#define FR_CH_9 KC_9

#define FR_CH_DOT KC_DOT
#define FR_CH_COMM KC_COMM

#define FR_CH_QUOT KC_MINS
#define FR_CH_AE KC_QUOT
#define FR_CH_UE KC_LBRC
#define FR_CH_OE KC_SCLN

#define FR_CH_CIRC KC_EQL // accent circumflex ^ and grave ` and ~
#define FR_CH_LESS KC_NUBS // < and > and backslash
#define FR_CH_MINS KC_SLSH // - and _
#define FR_CH_DLR KC_BSLS // $, £ and }
#define FR_CH_PARA KC_GRV // § and ring °
#define FR_CH_DIAE KC_RBRC // accent ¨

// shifted characters
#define FR_CH_RING LSFT(KC_GRV) // °
#define FR_CH_EXLM LSFT(KC_RBRC) // !
#define FR_CH_PLUS LSFT(KC_1) // +
#define FR_CH_DQOT LSFT(KC_2) // "
#define FR_CH_ASTR LSFT(KC_3) // *
#define FR_CH_PERC LSFT(KC_5) // %
#define FR_CH_AMPR LSFT(KC_6) // &
#define FR_CH_SLSH LSFT(KC_7) // /
#define FR_CH_LPRN LSFT(KC_8) // (
#define FR_CH_RPRN LSFT(KC_9) // )
#define FR_CH_EQL  LSFT(KC_0) // =
#define FR_CH_QST  LSFT(FR_CH_QUOT) // ?
#define FR_CH_MORE LSFT(FR_CH_LESS) // >
#define FR_CH_COLN LSFT(KC_DOT) // :
#define FR_CH_SCLN LSFT(KC_COMM) // ;
#define FR_CH_UNDS LSFT(FR_CH_MINS) // _
#define FR_CH_CCED LSFT(KC_4) // ç
#define FR_CH_GRV  LSFT(FR_CH_CIRC) // accent grave `

// Alt Gr-ed characters
#define FR_CH_LCBR ALGR(KC_QUOT) // {
#define FR_CH_LBRC ALGR(KC_LBRC) // [
#define FR_CH_RBRC ALGR(KC_9) // ]
#define FR_CH_RCBR ALGR(KC_0) // }
#define FR_CH_BSLS ALGR(FR_CH_LESS) // backslash
#define FR_CH_AT   ALGR(KC_2) // @
#define FR_CH_EURO ALGR(KC_E) // €
#define FR_CH_TILD ALGR(FR_CH_CIRC) // ~
#define FR_CH_PIPE ALGR(KC_1) // |
#define FR_CH_HASH ALGR(KC_3) // #
#define FR_CH_ACUT ALGR(FR_CH_QUOT) // accent acute ´

#endif
