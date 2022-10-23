#ifndef KUATSURE
#define KUATSURE

#include "quantum.h"

enum kuatsure_keycodes {
  KB_MAKE = SAFE_RANGE,
  KB_FLSH,
  KB_VRSN,

  USER_SAFE_RANGE,
};

#define ONESHOT_TAP_TOGGLE 2
#define KT_LSFT OSM(MOD_LSFT)

enum {
  TD_LBRC = 0,
  TD_RBRC,
  TD_SLSH
};

#define KT_LBRC TD(TD_LBRC)
#define KT_RBRC TD(TD_RBRC)
#define KT_SLSH TD(TD_SLSH)

#define TAPPING_TERM 200

#define LEADER_TIMEOUT 250
#define LEADER_PER_KEY_TIMING

void tmux_prefix(void);
void tmux_pane_zoom(void);

#define KT_CESC CTL_T(KC_ESC)
#define KT_MTAB MEH_T(KC_TAB)

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 300

#define _________________NUMBER_L1_________________        KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________NUMBER_R1_________________        KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________SYMBOL_L1_________________        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________SYMBOL_R1_________________        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KT_SLSH
#define _________________QWERTY_R3_M_______________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP

#define ____________FUNCTION_1____________                 KC_F1,   KC_F2,   KC_F3,   KC_F4
#define ____________FUNCTION_2____________                 KC_F5,   KC_F6,   KC_F7,   KC_F8
#define ____________FUNCTION_3____________                 KC_F9,   KC_F10,  KC_F11,  KC_F12

#define ___SQBRACKETS___                                   KT_LBRC, KT_RBRC
#define _____PARENS_____                                   KC_LPRN, KC_RPRN
#define ____CRBRACES____                                   KC_LCBR, KC_RCBR
#define ___ANBRACKETS___                                   KC_LT,   KC_GT

#endif
