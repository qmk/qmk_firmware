#include QMK_KEYBOARD_H
#include <sendstring_dvorak.h>
//#include <sendstring_colemak.h>
#include <print.h>


/**********************
** LAYER DEFINITIONS **
**********************/
enum layers_keymap {
  // BASE LAYERS
  _QWERTY = 0,
  _DVORAK,
  _COLEMAK,
  _WIN,
  _MAC,
  _QUAKE2,
  _QUAKE2_DVORAK,
  _QUAKE2_CONSOLE,

  // FUNCTION LAYERS
  _FUNCWIN,
  _FUNCMAC,
  _FUNCQ2,

  // OTHER LAYERS
  _NUMPAD,
  _MACROS,
  _SYSTEM
};

// LAYER SHORT CODES
#define _QW _QWERTY
#define _DV _DVORAK
#define _CM _COLEMAK
#define _MC _MAC
#define _Q2 _QUAKE2
#define _QD _QUAKE2_DVORAK
#define _QC _QUAKE2_CONSOLE
#define _FW _FUNCWIN
#define _FM _FUNCMAC
#define _FQ _FUNCQ2
#define _NP _NUMPAD
#define _MA _MACROS
#define _SY _SYSTEM


// default base layer
#define BASE _DVORAK
//layer_on(_WIN);

// include userspace
// ../../../../users/noroadsleft/
#include "noroadsleft.h"

// KEYMAPS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /****************
  ** BASE LAYERS **
  ****************/

  /* QWERTY */
  [_QWERTY] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    FW_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FW), KC_RCTL  \
  ),

  /* Dvorak */
  [_DVORAK] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, \
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, \
    FW_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,           \
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,                   \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FW), KC_RCTL  \
  ),

  /* Colemak */
  [_COLEMAK] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, \
    FW_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,           \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FW), KC_RCTL  \
  ),

  /****************
  ** OS OVERLAYS **
  ****************/

  /* Mac */
  [_MAC] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    FM_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, MO(_FM), _______  \
  ),

  /*********************
  ** QUAKE 2 OVERLAYS **
  *********************/

  /* Quake 2 */
  [_QUAKE2] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    Q2_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, Q2_ON,            \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, MO(_FQ), _______  \
  ),

  [_QUAKE2_DVORAK] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    Q2_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    Q2_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, Q2_OFF,           \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, MO(_FQ), _______  \
  ),

  [_QUAKE2_CONSOLE] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    Q2_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    Q2_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT,           \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, MO(_FQ), _______  \
  ),

  /********************
  ** FUNCTION LAYERS **
  ********************/

  /* Windows Fn layer */
  [_FUNCWIN] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    _______, KC_CALC, KC_APP,  _______, _______, _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS, \
    NO_CHNG, WN_SALL, _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_PENT,          \
    _______, WN_UNDO, WN_CUT,  WN_COPY, WN_PSTE, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, TG(_SY), _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, TG(_MA), NO_CHNG, _______  \
  ),

  /* MacOS Fn layer */
  [_FUNCMAC] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    _______, _______, _______, _______, _______, _______, KC_INS,  MC_HOME, KC_UP,   MC_END,  KC_PGUP, MC_PSCR, _______, _______, \
    NO_CHNG, MC_SALL, _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______,          \
    _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PSTE, _______, _______, _______, _______, _______, TG(_SY), _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, _______, NO_CHNG, _______  \
  ),

  /* Quake 2 Fn layer */
  [_FUNCQ2] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    Q2_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS, \
    NO_CHNG, _______, _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_ENT,           \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TG(_SY), _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, NO_CHNG, _______  \
  ),

  /*****************
  ** OTHER LAYERS **
  *****************/

  /* Numpad layer */
  [_NUMPAD] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______, \
    _______, _______, _______, _______, KC_E,    KC_F,    _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_PSLS, KC_PEQL, _______, \
    _______, _______, _______, _______, KC_C,    KC_D,    _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_PMNS, KC_PENT,          \
    _______, _______, _______, _______, KC_A,    KC_B,    _______, KC_P0,   _______, KC_PDOT, _______, _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, _______, NO_CHNG, _______  \
  ),

  /* Macro layer */
  [_MACROS] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    TG(_MA), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, G_PUSH,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, G_RST,   G_FTCH,  G_COMM,  _______, _______, _______, _______, T_L3DED, _______, _______, _______,          \
    _______, _______, _______, G_C10R,  _______, G_BRCH,  SIGNA,   _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, NO_CHNG, _______  \
  ),

  /* System layer */
  [_SYSTEM] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    TG(_SY), TO(_QW), TO(_DV), TO(_CM), GO_Q2,   XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, TG(_MC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          \
    XXXXXXX, XXXXXXX, XXXXXXX, BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   \
    XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,                                     XXXXXXX, XXXXXXX, NO_CHNG, XXXXXXX  \
  ),

};
