/* -*- Mode:C; c-basic-offset:2; tab-width:2; indent-tabs-mode:nil; evil-indent-convert-tabs:t; -*- */

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/**
 * See `readme.md` for notes on each define.
 */

/**
 * Optionally support 80 key layout.
 *
 * No default keys defined: use 'CFQ_USER_K80_L0K0' .. etc.
 */
/* #define CFQ_USE_80_KEYS */

/** Personal preference (enable by passing 'EXTRAFLAGS=...' to make). */
/* #define CFQ_USE_MOMENTARY_LAYER_KEYS */

/** Holding right/left or left/right shift for single or double quote pair */
/* #define CFQ_USE_SHIFT_QUOTES */

#define CFQ_USE_DYNAMIC_MACRO

#if !defined(CFQ_USER_KEY0)
#  define CFQ_USER_KEY0 KC_APP
#endif
#if !defined(CFQ_USER_KEY1)
#  define CFQ_USER_KEY1 KC_MENU
#endif
#if !defined(CFQ_USER_KEY2)
#  define CFQ_USER_KEY2 KC_BSPC
#endif
#if !defined(CFQ_USER_KEY3)
#  define CFQ_USER_KEY3 KC_DEL
#endif
#if !defined(CFQ_USER_KEY4)
#  define CFQ_USER_KEY4 KC_SPC
#endif
#if !defined(CFQ_USER_KEY5)
#  define CFQ_USER_KEY5 CFQ_KC_FN1
#endif
#if !defined(CFQ_USER_KEY6)
#  define CFQ_USER_KEY6 KC_CAPS
#endif
#if !defined(CFQ_USER_KEY7)
#  define CFQ_USER_KEY7 KC_INS
#endif
#if !defined(CFQ_USER_KEY8)
#  define CFQ_USER_KEY8 KC_DEL
#endif
#if !defined(CFQ_USER_KEY9)
#  define CFQ_USER_KEY9 KC_BSPC
#endif


#ifdef CFQ_USE_80_KEYS
#  define LAYOUT_ergodox_76_or_80 LAYOUT_ergodox_80
#  define K80(a) CFQ_USER_K80_##a
#else
#  define LAYOUT_ergodox_76_or_80( \
        k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
        k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
        k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
        k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, \
         \
        k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, \
        k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, \
        k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, \
        k70, k71, k72, k73, k74, k75, k76, k77, k78, k79) \
  LAYOUT_ergodox( \
          k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
          k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
          k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
          k30, k31, k32, k33,           k36, k37, k38, k39, \
           \
          k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, \
          k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, \
          k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, \
          k70, k71, k72, k73, k74,           k77, k78, k79)
#  define K80(a) _______
#endif

/**
 * Used to generate lines below:
 * \code{.py}
 * text = '#  ifndef CFQ_USER_K80_L0K0\n#    define CFQ_USER_K80_L0K0 _______\n#  endif'
 * print('\n'.join([text.replace('L0', f'L{l}').replace('K0', f'K{k}') for l in range(3) for k in range(4)]))
 * \endcode
 */
#ifdef CFQ_USE_80_KEYS
#  ifndef CFQ_USER_K80_L0K0
#    define CFQ_USER_K80_L0K0 _______
#  endif
#  ifndef CFQ_USER_K80_L0K1
#    define CFQ_USER_K80_L0K1 _______
#  endif
#  ifndef CFQ_USER_K80_L0K2
#    define CFQ_USER_K80_L0K2 _______
#  endif
#  ifndef CFQ_USER_K80_L0K3
#    define CFQ_USER_K80_L0K3 _______
#  endif
#  ifndef CFQ_USER_K80_L1K0
#    define CFQ_USER_K80_L1K0 _______
#  endif
#  ifndef CFQ_USER_K80_L1K1
#    define CFQ_USER_K80_L1K1 _______
#  endif
#  ifndef CFQ_USER_K80_L1K2
#    define CFQ_USER_K80_L1K2 _______
#  endif
#  ifndef CFQ_USER_K80_L1K3
#    define CFQ_USER_K80_L1K3 _______
#  endif
#  ifndef CFQ_USER_K80_L2K0
#    define CFQ_USER_K80_L2K0 _______
#  endif
#  ifndef CFQ_USER_K80_L2K1
#    define CFQ_USER_K80_L2K1 _______
#  endif
#  ifndef CFQ_USER_K80_L2K2
#    define CFQ_USER_K80_L2K2 _______
#  endif
#  ifndef CFQ_USER_K80_L2K3
#    define CFQ_USER_K80_L2K3 _______
#  endif
#  ifndef CFQ_USER_K80_L3K0
#    define CFQ_USER_K80_L3K0 _______
#  endif
#  ifndef CFQ_USER_K80_L3K1
#    define CFQ_USER_K80_L3K1 _______
#  endif
#  ifndef CFQ_USER_K80_L3K2
#    define CFQ_USER_K80_L3K2 _______
#  endif
#  ifndef CFQ_USER_K80_L3K3
#    define CFQ_USER_K80_L3K3 _______
#  endif
#endif

#ifndef CFQ_WORD_A
#define CFQ_WORD_A ""
#endif
#ifndef CFQ_WORD_B
#define CFQ_WORD_B ""
#endif
#ifndef CFQ_WORD_C
#define CFQ_WORD_C ""
#endif
#ifndef CFQ_WORD_D
#define CFQ_WORD_D ""
#endif
#ifndef CFQ_WORD_E
#define CFQ_WORD_E ""
#endif
#ifndef CFQ_WORD_F
#define CFQ_WORD_F ""
#endif
#ifndef CFQ_WORD_G
#define CFQ_WORD_G ""
#endif
#ifndef CFQ_WORD_H
#define CFQ_WORD_H ""
#endif
#ifndef CFQ_WORD_I
#define CFQ_WORD_I ""
#endif
#ifndef CFQ_WORD_J
#define CFQ_WORD_J ""
#endif
#ifndef CFQ_WORD_K
#define CFQ_WORD_K ""
#endif
#ifndef CFQ_WORD_L
#define CFQ_WORD_L ""
#endif
#ifndef CFQ_WORD_M
#define CFQ_WORD_M ""
#endif
#ifndef CFQ_WORD_N
#define CFQ_WORD_N ""
#endif
#ifndef CFQ_WORD_O
#define CFQ_WORD_O ""
#endif
#ifndef CFQ_WORD_P
#define CFQ_WORD_P ""
#endif
#ifndef CFQ_WORD_Q
#define CFQ_WORD_Q ""
#endif
#ifndef CFQ_WORD_R
#define CFQ_WORD_R ""
#endif
#ifndef CFQ_WORD_S
#define CFQ_WORD_S ""
#endif
#ifndef CFQ_WORD_T
#define CFQ_WORD_T ""
#endif
#ifndef CFQ_WORD_U
#define CFQ_WORD_U ""
#endif
#ifndef CFQ_WORD_V
#define CFQ_WORD_V ""
#endif
#ifndef CFQ_WORD_W
#define CFQ_WORD_W ""
#endif
#ifndef CFQ_WORD_X
#define CFQ_WORD_X ""
#endif
#ifndef CFQ_WORD_Y
#define CFQ_WORD_Y ""
#endif
#ifndef CFQ_WORD_Z
#define CFQ_WORD_Z ""
#endif

/* lower and title capitals versions (setup at start). */
static char *cfq_word_lut[2][26] = {
  {
    CFQ_WORD_A, CFQ_WORD_B, CFQ_WORD_C, CFQ_WORD_D, CFQ_WORD_E, CFQ_WORD_F,
    CFQ_WORD_G, CFQ_WORD_H, CFQ_WORD_I, CFQ_WORD_J, CFQ_WORD_K, CFQ_WORD_L,
    CFQ_WORD_M, CFQ_WORD_N, CFQ_WORD_O, CFQ_WORD_P, CFQ_WORD_Q, CFQ_WORD_R,
    CFQ_WORD_S, CFQ_WORD_T, CFQ_WORD_U, CFQ_WORD_V, CFQ_WORD_W, CFQ_WORD_X,
    CFQ_WORD_Y, CFQ_WORD_Z,
  },
  {NULL}
};

/* Storage for title-caps strings. */
static char cfq_word_lut_title_caps[
    sizeof(CFQ_WORD_A) + sizeof(CFQ_WORD_B) + sizeof(CFQ_WORD_C) + sizeof(CFQ_WORD_D) +
    sizeof(CFQ_WORD_E) + sizeof(CFQ_WORD_F) + sizeof(CFQ_WORD_G) + sizeof(CFQ_WORD_H) +
    sizeof(CFQ_WORD_I) + sizeof(CFQ_WORD_J) + sizeof(CFQ_WORD_K) + sizeof(CFQ_WORD_L) +
    sizeof(CFQ_WORD_M) + sizeof(CFQ_WORD_N) + sizeof(CFQ_WORD_O) + sizeof(CFQ_WORD_P) +
    sizeof(CFQ_WORD_Q) + sizeof(CFQ_WORD_R) + sizeof(CFQ_WORD_S) + sizeof(CFQ_WORD_T) +
    sizeof(CFQ_WORD_U) + sizeof(CFQ_WORD_V) + sizeof(CFQ_WORD_W) + sizeof(CFQ_WORD_X) +
    sizeof(CFQ_WORD_Y) + sizeof(CFQ_WORD_Z)
];

#define LAYER_BASE 0 /* Default Layer. */
#define LAYER_KPAD 1 /* Keypad, Bracket Pairs & Macro Record. */
#define LAYER_FKEY 2 /* Function Keys, Media & Mouse Keys. */
#define LAYER_WORD 3 /* Entire Words (one for each key) & Numbers. */

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, /* can always be here */
  RGB_SLD,

  M_BRACKET_IN_CBR,
  M_BRACKET_IN_PRN,
  M_BRACKET_IN_BRC,
  M_BRACKET_IN_ANG,
  M_BRACKET_OUT_CBR,
  M_BRACKET_OUT_PRN,
  M_BRACKET_OUT_BRC,
  M_BRACKET_OUT_ANG,
  M_ARROW_RMINUS,
  M_ARROW_LMINUS,
  M_ARROW_REQL,
  M_ARROW_LEQL,

  /* allow user defined words for each character:
   * use CFQ_WORD_[A-Z] defines. */
  M_WORD_A, M_WORD_B, M_WORD_C, M_WORD_D, M_WORD_E, M_WORD_F,
  M_WORD_G, M_WORD_H, M_WORD_I, M_WORD_J, M_WORD_K, M_WORD_L,
  M_WORD_M, M_WORD_N, M_WORD_O, M_WORD_P, M_WORD_Q, M_WORD_R,
  M_WORD_S, M_WORD_T, M_WORD_U, M_WORD_V, M_WORD_W, M_WORD_X,
  M_WORD_Y, M_WORD_Z,

#ifdef CFQ_USE_DYNAMIC_MACRO
  DYNAMIC_MACRO_RANGE,
#endif
};

#ifdef CFQ_USE_DYNAMIC_MACRO
#  include "dynamic_macro.h"
#else
   /* avoid ifdef's in keymap */
#  define DM_REC1 _______
#  define DM_REC2 _______
#  define DM_PLY1 _______
#  define DM_PLY2 _______
#  define DM_RSTP _______
#endif

#ifdef CFQ_USE_MOMENTARY_LAYER_KEYS
#define CFQ_KC_FN1 MO(1)
#define CFQ_KC_FN2 MO(2)
#define CFQ_KC_FN3 MO(3)
#else
#define CFQ_KC_FN1 TT(1)
#define CFQ_KC_FN2 TT(2)
#define CFQ_KC_FN3 TT(3)
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * .--------------------------------------------------.  .--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |      |  |      |   6  |   7  |   8  |   9  |   0  | BSpace |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |  |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   S  |   D  |   F  |   G  |------|  |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|   [  |  |  ]   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |  |      |   N  |   M  |   ,  |   .  |   /  |  Del   |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   |      |      |LCtl |Super  | Alt  |                              | Lower|   -  |  =   |      |      |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      |      |      |  |      |      |
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |Space |      |------|  |------|      |Enter |
 *                               |      |      |      |  |      |      |      |
 *                               '--------------------'  '--------------------'
 */

/* If it accepts an argument (i.e, is a function), it doesn't need KC_.
 * Otherwise, it needs KC_* */
[LAYER_BASE] = LAYOUT_ergodox_76_or_80(  /* layer 0 : default */
  /* left hand */
  KC_GRV,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,
  KC_TAB,  KC_Q,    KC_W,    KC_E,          KC_R,   KC_T,    XXXXXXX,
  KC_ESC,  KC_A,    KC_S,    KC_D,      KC_F,   KC_G,
  KC_LSFT, KC_Z,    KC_X,    KC_C,          KC_V,   KC_B,    KC_LBRC,
  XXXXXXX, XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT,
                                                    XXXXXXX, XXXXXXX,
                                     XXXXXXX,       XXXXXXX, XXXXXXX,
                                     CFQ_USER_KEY4, XXXXXXX, XXXXXXX,
  /* right hand */
  XXXXXXX, KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    CFQ_USER_KEY9,
  XXXXXXX,     KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,      KC_BSLS,
               KC_H,    KC_J,    KC_K,   KC_L,    KC_SCLN,   KC_QUOT,
  KC_RBRC,     KC_N,    KC_M,    KC_COMM,KC_DOT,  KC_SLSH,   CFQ_USER_KEY8,
                        CFQ_USER_KEY5, KC_MINS, KC_EQL, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,  XXXXXXX,
  XXXXXXX, XXXXXXX, KC_ENT
),
/* Keymap 1: Keypad, Bracket Pairs & Macro Record
 *
 * .--------------------------------------------------.  .--------------------------------------------------.
 * |        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * |  F1    |  F2  | F3   |  F4  | F5   |  F6  |      |  |      | F7   |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|  |------| Left | Down | Up   |Right |      |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |  | Play | MvPrv|VolDwn|VolUp |MvNex |      |        |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                              |      |      |      |      |      |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      |      |      |  |      |      |
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |      |  |      |      |      |
 *                               '--------------------'  '--------------------'
 */
[LAYER_KPAD] = LAYOUT_ergodox_76_or_80(
  /* left hand */
  _______, _______, _______, _______, _______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______,
  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,
                              _______, _______,
                              _______, _______, _______,
                              _______, _______, _______,
  /* right hand */
  _______, _______, _______, _______, _______, _______, _______,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,
  KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, _______, _______,
  KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,
                    _______, _______, _______, _______, _______,
  _______, _______,
  _______, _______, _______,
  _______, _______, _______
),
/* Keymap 2: Function Keys, Media & Mouse Keys
 *
 * .--------------------------------------------------.  .--------------------------------------------------.
 * |        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|  |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                              |      |      |      |      |      |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      |      |      |  |      |      |
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |      |  |      |      |      |
 *                               '--------------------'  '--------------------'
 */
[LAYER_FKEY] = LAYOUT_ergodox_76_or_80(
  /* left hand */
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,
                                      _______,   _______,
                           _______, _______, _______,
                           _______,   _______,   _______,
  /* right hand */
  _______,  _______, _______,  _______,  _______,  _______, _______,
  _______,  _______, _______,   _______,   _______,   _______, _______,
            _______, _______,   _______,   _______,   _______, _______,
  _______,  _______, _______,   _______,   _______,   _______, _______,
                     _______, _______, _______, _______, _______,
  _______, _______,
  _______, _______,_______,
  _______, _______, _______
),
/* Keymap 3: Entire Words (one for each key) & Numbers
 *
 * Activate by holding L1 & L2.
 *
 * .--------------------------------------------------.  .--------------------------------------------------.
 * |        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|  |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |  |      |      |      |      |      |      |        |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                              |      |      |      |      |      |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      |      |      |  |      |      |
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |      |  |      |      |      |
 *                               '--------------------'  '--------------------'
 */
[LAYER_WORD] = LAYOUT_ergodox_76_or_80(
  /* left hand */
   _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,
                                      _______,   _______,
                           _______, _______, _______,
                           _______,   _______,   _______,
  /* right hand */
  _______,  _______, _______,  _______,  _______,  _______, _______,
  _______,  _______, _______,   _______,   _______,   _______, _______,
            _______, _______,   _______,   _______,   _______, _______,
  _______,  _______, _______,   _______,   _______,   _______, _______,
                     _______, _______, _______, _______, _______,
  _______, _______,
  _______, _______,_______,
  _______, _______, _______
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  /* Use layer 3 when 1 & 2 are pressed. */
  state = update_tri_layer_state(state, LAYER_KPAD, LAYER_FKEY, LAYER_WORD);
  return state;
}

#define WITHOUT_MODS(...) \
  do { \
    uint8_t _real_mods = get_mods(); \
    clear_mods(); \
    { __VA_ARGS__ } \
    set_mods(_real_mods); \
  } while (0)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CFQ_USE_DYNAMIC_MACRO
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
#endif
  switch (keycode) {
    /* dynamically generate these. */
    case RGB_SLD:
      if (record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
        rgblight_mode(1);
#endif
      }
      return false;
      break;
    case M_BRACKET_IN_CBR:  /* {} */
      if (record->event.pressed) {
        SEND_STRING("{}" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_IN_PRN:  /* () */
      if (record->event.pressed) {
        SEND_STRING("()" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_IN_BRC:  /* [] */
      if (record->event.pressed) {
        SEND_STRING("[]" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_IN_ANG:  /* <> */
      if (record->event.pressed) {
        SEND_STRING("<>" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_OUT_CBR:  /* }{ */
      if (record->event.pressed) {
        SEND_STRING("}{" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_OUT_PRN:  /* )( */
      if (record->event.pressed) {
        SEND_STRING(")(" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_OUT_BRC:  /* ][ */
      if (record->event.pressed) {
        SEND_STRING("][" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_OUT_ANG:  /* >< */
      if (record->event.pressed) {
        SEND_STRING("><" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_ARROW_LMINUS:  /* <- */
      if (record->event.pressed) {
        SEND_STRING("<-");
        return false;
      }
      break;
    case M_ARROW_RMINUS:  /* -> */
      if (record->event.pressed) {
        SEND_STRING("->");
        return false;
      }
      break;
    case M_ARROW_LEQL:  /* <= */
      if (record->event.pressed) {
        SEND_STRING("<=");
        return false;
      }
      break;
    case M_ARROW_REQL:  /* => */
      if (record->event.pressed) {
        SEND_STRING("=>");
        return false;
      }
      break;
#ifdef CFQ_USE_SHIFT_QUOTES
    case KC_LEFT_SHIFT:  /* '' */
      if (record->event.pressed && (keyboard_report->mods & (MOD_BIT(KC_RSFT)))) {
        WITHOUT_MODS({
            SEND_STRING("''" SS_TAP(X_LEFT) SS_DOWN(X_RSFT) SS_DOWN(X_LSFT));
          });
        return false;
      }
      break;
    case KC_RIGHT_SHIFT:  /* "" */
      if (record->event.pressed && (keyboard_report->mods & (MOD_BIT(KC_LSFT)))) {
        WITHOUT_MODS({
            SEND_STRING("\x22\x22" SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_DOWN(X_RSFT));
          });
        return false;
      }
      break;
#endif  /* CFQ_USE_SHIFT_QUOTES */
    case M_WORD_A...M_WORD_Z:
    {
      uint8_t shift_index = (keyboard_report->mods & (MOD_BIT(KC_RSFT) | MOD_BIT(KC_LSFT))) ? 1 : 0;
      const char *word = cfq_word_lut[shift_index][keycode - M_WORD_A];
      if (record->event.pressed) {
        if (*word) {
          WITHOUT_MODS({
              send_string(word);
            });
        }
        return false;
      }
      break;
    }
  }

  return true;
}

/* Runs just one time when the keyboard initializes. */
void matrix_init_user(void) {

  /* Duplicate 'cfq_word_lut[0][...]' into 'cfq_word_lut[1][...]' */
  {
    char *d = cfq_word_lut_title_caps;
    for (uint16_t i = 0; i < 26; i++) {
      char *s = cfq_word_lut[0][i];
      cfq_word_lut[1][i] = d;
      while ((*d++ = *s++)) {}
    }
  }
  /* Title caps. */
  for (uint16_t i = 0; i < 26; i++) {
    char *w = cfq_word_lut[1][i];
    bool prev_is_alpha = false;
    if (*w) {
      while (*w) {
        bool is_lower = (*w >= 'a' && *w <= 'z');
        bool is_upper = (*w >= 'A' && *w <= 'Z');
        if (prev_is_alpha == false && is_lower) {
          *w -= ('a' - 'A');
        }
        prev_is_alpha = is_lower || is_upper;
        w++;
      }
    }
  }
};

/* Runs constantly in the background, in a loop. */
void matrix_scan_user(void) {

  uint8_t layer = get_highest_layer(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    default:
      /* none */
      break;
  }

};
