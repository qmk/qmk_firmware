/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

#ifndef ericgebhart
#define ericgebhart

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"


void tap(uint16_t keycode);
bool process_record_secrets(uint16_t keycode, keyrecord_t *record);


#define EECONFIG_USERSPACE (uint8_t *)19

typedef union {
  uint8_t raw;
  struct {
    bool     clicky_enable    :1;
    bool     rgb_layer_change :1;
    bool     is_overwatch     :1;
    bool     nuke_switch      :1;
  };
} userspace_config_t;

#define ___ KC_TRNS
#define XXX KC_NO

// The most portable copy/paste keys (windows (mostly), linux, and some terminal emulators).
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert


#define DVORAK 0 // dvorak layout (default)
#define QWERTY 1
#define COLEMAK 2
#define WORKMAN 3
#define NORMAN 4
// bepo layers
#define DVORAK_ON_BEPO 6 // dvorak layout (default)
#define BEPO 7 // Bepo
// non-default layers
#define SYMB 8 // symbols and numbers
#define SYMB_ON_BEPO 9 // symbols and numbers
#define MDIA 10 // mouse knd media eys
#define LAYERS 11 // layers and right mousekeys.
#define XMONAD 12 // xmonad ie. dvorak.
#define XMONAD_FR 13 // xmonad ie. dvorak.


// for the creation of dvorak keys on an Bepo keyboard at the OS layer.

// so we can create an array of reasonable size
// for our translation keys. We have to create a
// good range of numbers
#define GR(x) (x-SAFE_RANGE)

uint8_t gr(uint8_t);
void send_keycode(uint8_t);

#define MOD_NONE 0x00

// indexs for the keycode translation table.
#define UNSHIFTED_KEY(key)  key_translations[gr(key)][0][0]
#define UNSHIFTED_MODS(key) key_translations[gr(key)][0][1]
#define SHIFTED_KEY(key)    key_translations[gr(key)][1][0]
#define SHIFTED_MODS(key)   key_translations[gr(key)][1][1]


enum userspace_custom_keycodes {
  // keep the keycodes using the send_key function close to SAFE_RANGE
  // so the array of keycodes remains a reasonbale size.
  DB_1 = SAFE_RANGE,  // can always be here
  DB_2,
  DB_3,
  DB_4,
  DB_5,
  DB_6,
  DB_7,
  DB_8,
  DB_9,
  DB_0,
  DB_GRV,
  DB_SCOLON,
  DB_SLASH,
  DB_BACKSLASH,
  DB_EQL,
  DB_DOT,
  DB_COMM,
  DB_QUOT,
  DB_MINUS,
  DB_RPRN,
  DB_LPRN,
  DB_RBRC,
  DB_LBRC,
  // for symbols layer
  DB_HASH,
  DB_LCBR,
  DB_RCBR,
  DB_PIPE,
  DB_TILD,
  DB_CIRC,
  DB_LESS,
  DB_GRTR,
  // End of dvorak on bepo translation keys.

  EPRM,
  VRSN,
  KC_DVORAK_ON_BEPO,
  KC_BEPO,
  KC_NORMAN,
  KC_QWERTY,
  KC_COLEMAK,
  KC_DVORAK,
  KC_WORKMAN,
  KC_MAKE,
  KC_RESET,
  KC_RGB_T,
  KC_SECRET_1,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
  KC_CCCV
};

#define SFTGUI_T(kc) { MT(MOD_LGUI | MOD_LSFT, kc) }
#define SFT_GUI_ESC MT(MOD_LSFT | MOD_LGUI, KC_PGDN)  // shift LGUI or Escape.
#define ALT_ENT     ALT_T(KC_ENT)  // Alt or enter
#define CTL_SPC     CTL_T(KC_SPC) // ctrl or space
#define CTL_BSPC    CTL_T(KC_BSPC) // ctrl or backspace
#define ALT_DEL     ALT_T(KC_DEL)  // Alt or delete
#define GUI_ESC     GUI_T(KC_ESC)  // Gui or escape
#define ALGR_SYMB   ALGR_T(TG(SYMB))  // Alt gre or toggle symbol layer

#define KC_SFT_T_U   SFT_T(KC_U)
#define KC_SFT_T_H   SFT_T(KC_H)
#define KC_LT_SYMB_I LT(SYMB, KC_I)
#define KC_LT_SYMB_D LT(SYMB, KC_D)

// for dvorak on bepo
#define BP_SFT_T_U   SFT_T(BP_U)
#define BP_SFT_T_H   SFT_T(BP_H)
#define BP_LT_SYMB_D LT(SYMB, BP_D)


// for bepo on bepo
#define BP_SFT_T_T    SFT_T(BP_T)
#define BP_LT_SYMB_C  LT(SYMB_ON_BEPO, BP_C)
#define BP_LT_SYMB_I  LT(SYMB_ON_BEPO, BP_I)
#define BP_SFT_T_E SFT_T(BP_E)
#define BP_SFT_T_ECRC SFT_T(BP_ECRC)
#define BP_SFT_T_CCED SFT_T(BP_CCED)
#define BP_LT_SYMB_COMM LT(SYMB,BP_COMM)

// OSM keycodes, to keep things clean and easy to change
#define KC_MLSF OSM(MOD_LSFT)
#define KC_MRSF OSM(MOD_RSFT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define ALT_APP ALT_T(KC_APP)

#define MG_NKRO MAGIC_TOGGLE_NKRO


////  TAP DANCE

typedef struct {
  bool is_press_action;
    int state;
} tdtap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
  };

  //Tap Dance Declarations
  enum {
    TD_ESC_CAPS = 0,
    TD_TAB_BKTAB = 1,
    TD_MDIA_SYMB = 2,
    TD_HOME_END = 3,
    TD_XMONAD_ESC = 4,
    TD_DEF_LAYER_SW = 5,
    TD_DEF_OS_LAYER_SW = 6,
    TD_MOUSE_BTNS = 7,
    TD_DVORAK_BEPO = 8
  };


// Tap dance
#define TAB_BKTAB       TD(TD_TAB_BKTAB)  // Tab or backtab tapdance.
#define MDIA_SYMB       TD(TD_MDIA_SYMB)  // MDIA or Symb layer tapdance toggle.
#define DEF_LAYER_SW    TD(TD_DEF_LAYER_SW)  // dvorak, dvorak_on_bepo, bepo default layer
#define DEF_OS_LAYER_SW TD(TD_DEF_OS_LAYER_SW)  // dvorak, dvorak_on_bepo, bepo default layer
#define HOME_END        TD(TD_HOME_END)  // home or end tapdance.
#define XMONAD_ESC      TD(TD_XMONAD_ESC)  // Escape, dvorak, media or symb. - tap and hold tap dance. 1-4
#define DVORAK_ET_BEPO  TD(TD_DVORAK_BEPO)  // Escape, dvorak, media or symb. - tap and hold tap dance. 1-4
#define TDMOUSE_BTNS    TD(TD_MOUSE_BTNS)  // hmmm. 1-5


int on_qwerty(void);
int get_xmonad_layer(void);
int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);


// Blocks for each of the four major keyboard layouts
// Organized so we can quickly adapt and modify all of them
// at once, rather than for each keyboard, one at a time.
// And this allows for much cleaner blocks in the keymaps.
// For instance Tap/Hold for Control on all of the layouts

// NOTE: These are all the same length.  If you do a search/replace
//       then you need to add/remove underscores to keep the
//       lengths consistent.

// Since our quirky block definitions are basically a list of comma separated
// arguments, we need a wrapper in order for these definitions to be
// expanded before being used as arguments to the LAYOUT_xxx macro.
#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)

//Dvorak on a qwerty software layer in the OS
#define ___DVORAK_L1___ KC_QUOT, KC_COMM, KC_DOT, KC_P,       KC_Y
#define ___DVORAK_L2___ KC_A,    KC_O,    KC_E,   KC_SFT_T_U, KC_LT_SYMB_I
#define ___DVORAK_L3___ KC_SCLN, KC_Q,    KC_J,   KC_K,       KC_X

#define ___DVORAK_R1___ KC_F,         KC_G,       KC_C, KC_R, KC_L
#define ___DVORAK_R2___ KC_LT_SYMB_D, KC_SFT_T_H, KC_T, KC_N, KC_S
#define ___DVORAK_R3___ KC_B,         KC_M,       KC_W, KC_V, KC_Z


// Dvorak on fr-bepo software layer in the OS.
// for dvorak and all the other qwerty like keyboards on bepo
#define ___NUMBER_BEPO_L___ DB_1,   DB_2,   DB_3,   DB_4,   DB_5
#define ___NUMBER_BEPO_R___ DB_6,   DB_7,   DB_8,   DB_9,   DB_0

#define ___DVORAK_FR_L1___ DB_QUOT,    DB_COMM,  DB_DOT,  BP_P,        BP_Y
#define ___DVORAK_FR_L2___ BP_A,       BP_O,     BP_E,    BP_SFT_T_U,  BP_LT_SYMB_I
#define ___DVORAK_FR_L3___ DB_SCOLON,  BP_Q,     BP_J,    BP_K,        BP_X

#define ___DVORAK_FR_R1___ BP_F,          BP_G,        BP_C,  BP_R,  BP_L
#define ___DVORAK_FR_R2___ BP_LT_SYMB_D,  BP_SFT_T_H,  BP_T,  BP_N,  BP_S
#define ___DVORAK_FR_R3___ BP_B,          BP_M,        BP_W,  BP_V,  BP_Z


// Bepo on fr-bepo software layer
// for bepo on bepo
#define ___SYMBOL_BEPO_L___ /* BP_DLR */ BP_DQOT,  BP_LGIL,   BP_RGIL,   BP_LPRN,   BP_RPRN
#define ___SYMBOL_BEPO_R___    BP_AT,    BP_PLUS,  BP_MINS,   BP_SLASH,  BP_ASTR /* BP_EQL,  BP_PERC */

#define ___BEPO_FR_L1___             BP_B,    BP_ECUT, BP_P,   BP_O,        BP_EGRV
#define ___BEPO_FR_L2___             BP_A,    BP_U,    BP_I,   BP_SFT_T_E,  BP_LT_SYMB_COMM
#define ___BEPO_FR_L3___ /*BP_ECRC*/ BP_AGRV, BP_Y,    BP_X,   BP_DOT,      BP_K

#define ___BEPO_FR_R1___ /* BP_DCRC*/  BP_V,       BP_D,  BP_L,    BP_J,  BP_Z //,  BP_W
#define ___BEPO_FR_R2___ /* BP_C  */   BP_SFT_T_T, BP_S,    BP_R,  BP_N,    BP_M  //BP_CCED
#define ___BEPO_FR_R3___               BP_APOS,    BP_Q,    BP_G,  BP_H,    BP_F

// the bottom rows  for keyboards on bepo.
#define ___ERGODOX_BOTTOM_RIGHT_FR___ KC_UP,  KC_DOWN,  DB_BACKSLASH,  LCTL(BP_V),  LCTL(BP_C)
#define ___ERGODOX_BOTTOM_LEFT_FR___  LCTL(BP_C),  LCTL(BP_V),  KC_INS,  KC_LEFT, KC_RIGHT

// Since we have 7 default layouts (QWERTY, DVORAK, COLEMAK and WORKMAN, NORMAN,
// 2 of them based on a Bepo software keyboard, ---  DVORAK_ON_BEPO and BEPO),
// this allows us to quickly modify the bottom row for all of the layouts
// so we don't have to alter it 4 times and hope that we haven't missed
// anything
#define ___ERGODOX_BOTTOM_LEFT___  LCTL(KC_C),  LCTL(KC_V),  KC_INS,  KC_LEFT, KC_RIGHT
#define ___ERGODOX_BOTTOM_RIGHT___ KC_UP,  KC_DOWN,  KC_BSLASH,  LCTL(KC_V),  LCTL(KC_C)

#define ___ERGODOX_THUMB_LEFT___                \
  KC_RALT, ALGR_SYMB,                           \
    HOME_END,                                   \
    CTL_BSPC, ALT_DEL, XMONAD_ESC

#define ___ERGODOX_THUMB_RIGHT___               \
  ALGR_SYMB,  TD_MOUSE_BTNS,                    \
    KC_PGUP,                                    \
    KC_PGDN, ALT_ENT, CTL_SPC

#define ___ERGODOX_TRANS_THUMBS___              \
  ___, ___,                                     \
    ___,                                        \
    ___, ___, ___                               \

#define ___ERGODOX_TRANS_BOTTOM___              \
  ___,___,___,___,___

#define ___ERGODOX_TRANS_6_ROW___               \
  ___,___,___,___,___,___



// Qwerty based layers that I don't really use.
#define ___QWERTY_L1___ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define ___QWERTY_L2___ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define ___QWERTY_L3___ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define ___QWERTY_R1___ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define ___QWERTY_R2___ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define ___QWERTY_R3___ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define ___COLEMAK_L1___ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define ___COLEMAK_L2___ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define ___COLEMAK_L3___ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define ___COLEMAK_R1___ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ___COLEMAK_R2___ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define ___COLEMAK_R3___ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define ___COLEMAK_MOD_DH_L1___ KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ___COLEMAK_MOD_DH_L2___ KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ___COLEMAK_MOD_DH_L3___ CTL_T(KC_Z),   KC_X,    KC_C,    KC_D,    KC_V

#define ___COLEMAK_MOD_DH_R1___ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ___COLEMAK_MOD_DH_R2___ KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ___COLEMAK_MOD_DH_R3___ KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH


#define ___WORKMAN_L1___ KC_Q,  KC_D,    KC_R,   KC_W,     KC_B
#define ___WORKMAN_L2___ KC_A,  KC_S,    KC_H,   KC_T,     KC_G
#define ___WORKMAN_L3___ KC_Z,  KC_X,    KC_M,   KC_C,     KC_V

#define ___WORKMAN_R1___ KC_J,  KC_F,    KC_U,    KC_P,    KC_SCLN
#define ___WORKMAN_R2___ KC_Y,  KC_N,    KC_E,    KC_O,    KC_I
#define ___WORKMAN_R3___ KC_K,  KC_L,    KC_COMM, KC_DOT,  KC_SLASH


#define ___NORMAN_L1___ KC_Q,   KC_W,    KC_D,    KC_F,    KC_K
#define ___NORMAN_L2___ KC_A,   KC_S,    KC_E,    KC_T,    KC_G
#define ___NORMAN_L3___ KC_Z,   KC_X,    KC_C,    KC_V,    KC_B

#define ___NORMAN_R1___ KC_J,   KC_U,    KC_R,    KC_L,    KC_SCLN
#define ___NORMAN_R2___ KC_Y,   KC_N,    KC_I,    KC_O,    KC_U
#define ___NORMAN_R3___ KC_P,   KC_M,    KC_COMM, KC_DOT,  KC_SLASH


//  For the top rows.  Numbers for most things, symbols for Bepo.

// for everything on qwerty.
#define ___NUMBER_L___ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ___NUMBER_R___ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

// function key rows, works for everyone.
#define ___FUNC_L___   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ___FUNC_R___   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10


// Rows for the auxillary layers.

// The symbol layer is for qwerty.  I need another one for Bepo...

// the KC_P?  codes don't work for me. I don't use those shifted values anyway.
#define ___KEYPAD_1___ KC_7,  KC_8,    KC_9,     KC_PSLS
#define ___KEYPAD_2___ KC_4,  KC_5,    KC_6,     KC_PAST
#define ___KEYPAD_3___ KC_1,  KC_2,    KC_3,     KC_PMNS
#define ___KEYPAD_4___ KC_0,  KC_DOT,  KC_PEQL,  KC_PPLS

#define ___KEYPAD_1_BP___ DB_7,  DB_8,    DB_9,     BP_SLASH
#define ___KEYPAD_2_BP___ DB_4,  DB_5,    DB_6,     BP_ASTR
#define ___KEYPAD_3_BP___ DB_1,  DB_2,    DB_3,     DB_MINUS
#define ___KEYPAD_4_BP___ DB_0,  DB_DOT,  DB_EQL,   BP_PLUS

#define ___SYMBOLS_1___  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE
#define ___SYMBOLS_2___  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV
#define ___SYMBOLS_3___  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD

#define ___SYMBOLS_1_BP___ KC_EXLM,  BP_AT,    DB_LCBR,  DB_RCBR,  DB_PIPE
#define ___SYMBOLS_2_BP___ DB_HASH,  BP_DLR,   DB_LPRN,  DB_RPRN,  DB_GRV
#define ___SYMBOLS_3_BP___ BP_PERC,  DB_CIRC,  DB_LBRC,  DB_RBRC,  DB_TILD

#define ___MOUSE_LDUR___      KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R
#define ___MWHEEL_LDUR___     KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R
#define ___MOUSE_BTNS_R___    KC_BTN1,  KC_BTN2,  KC_BTN3,  KC_BTN4,  KC_BTN5
#define ___MOUSE_BTNS_L___    KC_BTN5,  KC_BTN4,  KC_BTN3,  KC_BTN2,  KC_BTN1
#define ___MOUSE_ACCL_012___  KC_ACL0,  KC_ACL1,  KC_ACL2

#define ___MUTE_PLAY_STOP___  KC_MUTE,  KC_MPLY,  KC_MSTP
#define ___VI_ARROWS___       KC_LEFT,  KC_DOWN,  KC_UP, KC_RIGHT

#define ___LAYERS_L1___ DF(BEPO), DF(DVORAK_ON_BEPO)
#define ___LAYERS_L2___ DF(COLEMAK), DF(DVORAK)
#define ___LAYERS_L3___ DF(QWERTY), DF(NORMAN), DF(WORKMAN)
#define ___LAYERS_L4___ TO(MDIA), TO(SYMB_ON_BEPO), TO(SYMB)


#endif
