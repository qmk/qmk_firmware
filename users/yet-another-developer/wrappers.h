#pragma once
#include "yet-another-developer.h"

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off

#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_5x14_wrapper(...)       LAYOUT_ortho_5x14(__VA_ARGS__)

/*  ---------- LEFT HAND -----------                ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodash_pretty( \
    L00, L01, L02, L03, L04, L05, L06,              R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16,              R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26,              R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35,                        R31, R32, R33, R34, R35, R36, \
    L40, L41, L42, L43,                                            R43, R44, R45, R46, \
                                  L36,              R30,                               \
                             L44, L45, L46,    R40, R41, R42                           \
    ) \
	{ \
        { L00, L01, L02, L03, L04, L05, L06 }, \
        { L10, L11, L12, L13, L14, L15, L16 }, \
        { L20, L21, L22, L23, L24, L25, L26 }, \
        { L30, L31, L32, L33, L34, L35, L36 }, \
        { L40, L41, L42, L43, L44, L45, L46 }, \
        { R06, R05, R04, R03, R02, R01, R00 }, \
        { R16, R15, R14, R13, R12, R11, R10 }, \
        { R26, R25, R24, R23, R22, R21, R20 }, \
        { R36, R35, R34, R33, R32, R31, R30 }, \
        { R46, R45, R44, R43, R42, R41, R40 }  \
    }

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts

NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
*/

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#ifdef TAP_DANCE_ENABLE
  #define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
  #define _________________COLEMAK_L2________________       KC_BOL,    KC_R,    KC_S,    KC_T,    KC_D
  #define _________________COLEMAK_L3________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

  #define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
  #define _________________COLEMAK_R2________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O
  #define _________________COLEMAK_R3________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH
#else
  #define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
  #define _________________COLEMAK_L2________________       KC_A,    KC_R,    KC_S,    KC_T,    KC_D
  #define _________________COLEMAK_L3________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

  #define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
  #define _________________COLEMAK_R2________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O
  #define _________________COLEMAK_R3________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH
#endif




#define _________________DVORAK_L1_________________        KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________        KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________        KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________        KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________        KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________        KC_B,    KC_M,    KC_W,    KC_V,    KC_Z


#define _________________WORKMAN_L1________________       KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________       KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________       KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________       KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________       KC_Y,    KC_N,    KC_E,    KC_O,    KC_I
#define _________________WORKMAN_R3________________       KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH

// #define _________________WHITE_R1__________________       KC_V,    KC_Y,    KC_D,    KC_COMM, KC_QUOT
// #define _________________WHITE_R2__________________       KC_A,    KC_T,    KC_H,    KC_E,    KC_B
// #define _________________WHITE_R3__________________       KC_P,    KC_K,    KC_G,    KC_W,    KC_Q

// #define _________________WHITE_L1__________________       KC_INT1, KC_J,    KC_M,    KC_L,    KC_U
// #define _________________WHITE_L2__________________       KC_MINS, KC_C,    KC_S,    KC_N,    KC_O  // KC_I
// #define _________________WHITE_L3__________________       KC_X,    KC_R,    KC_F,    KC_DOT,  KC_Z


#ifdef UNICODE_ENABLE
#define _______________UNICODE_L1__________________        UC_DISA,UC_DISA, UC_DISA, UC_DISA, UC_DISA
#define _______________UNICODE_L2__________________        UC_DISA,UC_DISA, UC_DISA, UC_DISA, UC_DISA
#define _______________UNICODE_L3__________________        UC_DISA,UC_DISA, UC_DISA, UC_DISA, UC_DISA

#define _______________UNICODE_R1__________________        UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG
#define _______________UNICODE_R2__________________        UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG
#define _______________UNICODE_R3__________________        UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG, UC_SHRG
#endif

#ifdef UNICODEMAP_ENABLE
#define _______________UNICODE_L1__________________        X(SMRK),  X(THINK),  X(CLOWN), X(HUNDR), X(BANG)
#define _______________UNICODE_L2__________________        X(GRIN),  X(MONKEY), X(OKOK), X(EGGPL), X(LIT)
#define _______________UNICODE_L3__________________        X(WEARY), X(UNAMU),  X(EFFU), X(MONOCL), X(IRONY)

#define _______________UNICODE_R1__________________        X(DRUG0), X(THUP), X(INUP), X(DIZZY), X(COOL)
#define _______________UNICODE_R2__________________        X(FIST0), X(FIST2),X(FIST3),X(FIST1), X(OKOK)
#define _______________UNICODE_R3__________________        X(MNDBLWN), X(THDN), X(SPOCK),X(HOLE),  X(DASH)
#endif

#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ___________________BLANK___________________        _______, _______, _______, _______, _______


#define _________________LOWER_L1__________________        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________LOWER_L2__________________        _________________FUNC_LEFT_________________
#define _________________LOWER_L3__________________        _________________FUNC_RIGHT________________

#define _________________LOWER_R1__________________        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define _________________LOWER_R2__________________        OS_UNI,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR
#define _________________LOWER_R3__________________        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT



#define _________________RAISE_L1__________________        ________________NUMBER_LEFT________________
#define _________________RAISE_L2__________________        ___________________BLANK___________________
#define _________________RAISE_L3__________________        ___________________BLANK___________________

#define _________________RAISE_R1__________________        ________________NUMBER_RIGHT_______________
#define _________________RAISE_R2__________________        _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC
#define _________________RAISE_R3__________________        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END



#define _________________ADJUST_L1_________________        ___________________BLANK___________________
#define _________________ADJUST_L2_________________        _________________FUNC_LEFT_________________
#define _________________ADJUST_L3_________________        _______, QWERTY,  COLEMAK, DVORAK,  WORKMAN

#define _________________ADJUST_R1_________________        KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5
#define _________________ADJUST_R2_________________        _________________FUNC_RIGHT________________
#define _________________ADJUST_R3_________________        KC_MUTE, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT

// clang-format on
