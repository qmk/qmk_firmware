#ifndef KEYMAP_GERMAN_OSX
#define KEYMAP_GERMAN_OSX

#ifdef KEYMAP_GERMAN
	#warning redefining german keys
#endif
#include "keymap_common.h"

// Alt gr

// normal characters
#define DE_Z KC_Y
#define DE_Y KC_Z

#define DE_A KC_A
#define DE_B KC_B
#define DE_C KC_C
#define DE_D KC_D
#define DE_E KC_E
#define DE_F KC_F
#define DE_G KC_G
#define DE_H KC_H
#define DE_I KC_I
#define DE_J KC_J
#define DE_K KC_K
#define DE_L KC_L
#define DE_M KC_M
#define DE_N KC_N
#define DE_O KC_O
#define DE_P KC_P
#define DE_Q KC_Q
#define DE_R KC_R
#define DE_S KC_S
#define DE_T KC_T
#define DE_U KC_U
#define DE_V KC_V
#define DE_W KC_W
#define DE_X KC_X

#define DE_0 KC_0
#define DE_1 KC_1
#define DE_2 KC_2
#define DE_3 KC_3
#define DE_4 KC_4
#define DE_5 KC_5
#define DE_6 KC_6
#define DE_7 KC_7
#define DE_8 KC_8
#define DE_9 KC_9

#define DE_DOT KC_DOT
#define DE_COMM KC_COMM

#define DE_SS KC_MINS
#define DE_AE KC_QUOT
#define DE_UE KC_LBRC
#define DE_OE KC_SCLN

#define DE_CIRC KC_NUBS // accent circumflex ^ and ring °
#define DE_ACUT KC_EQL // accent acute ´ and grave `
#define DE_PLUS KC_RBRC // + and * and ~
#define DE_HASH KC_BSLS // # and '
#define DE_LESS KC_GRV // < and > and |
#define DE_MINS KC_SLSH // - and _

// shifted characters
#define DE_RING LSFT(DE_CIRC) // °
#define DE_EXLM LSFT(KC_1) // !
#define DE_DQOT LSFT(KC_2) // "
#define DE_PARA LSFT(KC_3) // §
#define DE_DLR  LSFT(KC_4) // $
#define DE_PERC LSFT(KC_5) // %
#define DE_AMPR LSFT(KC_6) // &
#define DE_SLSH LSFT(KC_7) // /
#define DE_LPRN LSFT(KC_8) // (
#define DE_RPRN LSFT(KC_9) // )
#define DE_EQL  LSFT(KC_0) // =
#define DE_QST  LSFT(DE_SS) // ?
#define DE_GRV  LSFT(DE_ACUT) // `
#define DE_ASTR LSFT(DE_PLUS) // *
#define DE_QUOT LSFT(DE_HASH) // '
#define DE_MORE LSFT(DE_LESS) // >
#define DE_COLN LSFT(KC_DOT) // :
#define DE_SCLN LSFT(KC_COMM) // ;
#define DE_UNDS LSFT(DE_MINS) // _

// Alt-ed characters
#define DE_SQ2 LALT(KC_2) // ²
#define DE_SQ3 LALT(KC_3) // ³
#define DE_LCBR LALT(KC_8) // {
#define DE_LBRC LALT(KC_5) // [
#define DE_RBRC LALT(KC_6) // ]
#define DE_RCBR LALT(KC_9) // }
#define DE_BSLS LALT(LSFT(KC_7)) // backslash
#define DE_AT  LALT(DE_L) // @
#define DE_EURO LALT(KC_E) // €
#define DE_TILD LALT(DE_N) // ~
#define DE_PIPE LALT(DE_7) // |

#endif
