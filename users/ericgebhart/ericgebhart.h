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

//#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */

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
#define KEYPAD 14 // number and Fkey pads
#define KEYPAD_ON_BEPO 15 // number and Fkey pads.
#define _RGB 16 // RGB stuff.


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
#define MDIA_SYMB_KP_LAYERS TD(TD_MDIA_SYMB)  // MDIA, symb, keypad, layouts layer tapdance toggle.
#define DEF_LAYER_SW    TD(TD_DEF_LAYER_SW)  // dvorak, dvorak_on_bepo, bepo default layer
#define DEF_OS_LAYER_SW TD(TD_DEF_OS_LAYER_SW)  // dvorak, dvorak_on_bepo, bepo default layer
#define HOME_END        TD(TD_HOME_END)  // home or end tapdance.
#define XMONAD_ESC      TD(TD_XMONAD_ESC)  // Escape, dvorak, media or symb. - tap and hold tap dance. 1-4
#define DVORAK_ET_BEPO  TD(TD_DVORAK_BEPO)  // Escape, dvorak, media or symb. - tap and hold tap dance. 1-4
#define TDMOUSE_BTNS    TD(TD_MOUSE_BTNS)  // hmmm. 1-5

// HOME ROW LAYER TOGGLE (LT) and Shift.
// both sides of the home row have  "shift, ___, media , symb, ___"  and  "___, symb, media, ___, shift".
// so pinky fingers are shift when held and the index and second fingers are symbol and
// media layers when held.

// Dvorak
// shift and layer switch on hold on the home row.
#define KC_SFT_T_A   SFT_T(KC_A)
#define KC_SFT_T_S   SFT_T(KC_S)

#define KC_LT_SYMB_U LT(SYMB, KC_U)
#define KC_LT_SYMB_H LT(SYMB, KC_H)

#define KC_LT_MDIA_E LT(MDIA, KC_E)
#define KC_LT_MDIA_T LT(MDIA, KC_T)

// Need to add this to the others.
#define KC_LT_KP_N LT(KEYPAD, KC_N)
#define KC_LT_KP_O LT(KEYPAD, KC_O)

// for dvorak on bepo
#define BP_SFT_T_A   SFT_T(BP_A)
#define BP_SFT_T_S   SFT_T(BP_S)

#define BP_LT_SYMB_U LT(SYMB, BP_U)
#define BP_LT_SYMB_H LT(MDIA, BP_H)

#define BP_LT_MDIA_E LT(MDIA, BP_E)
#define BP_LT_MDIA_T LT(MDIA, BP_T)

// Need to add this to the others.
#define BP_LT_KP_N LT(KEYPAD, BP_N)
#define BP_LT_KP_O LT(KEYPAD, BP_O)

// for bepo on bepo
#define BP_SFT_T_T    SFT_T(BP_T)
#define BP_SFT_T_W    SFT_T(BP_W)

#define BP_LT_SYMB_I  LT(SYMB_ON_BEPO, BP_I)
#define BP_LT_MDIA_E  LT(MDIA, BP_E)
#define BP_LT_KP_U    LT(KEYPAD, BP_U)

#define BP_LT_SYMB_S  LT(SYMB_ON_BEPO, BP_S)
#define BP_LT_MDIA_R  LT(MDIA, BP_R)
#define BP_LT_KP_N    LT(KEYPAD, BP_N)

#define BP_SFT_T_A SFT_T(BP_A)
#define BP_SFT_T_S SFT_T(BP_S)
#define BP_SFT_T_E SFT_T(BP_E)
#define BP_SFT_T_M SFT_T(BP_M)

#define BP_SFT_T_ECRC SFT_T(BP_ECRC)
#define BP_SFT_T_CCED SFT_T(BP_CCED)
#define BP_LT_SYMB_COMM LT(SYMB,BP_COMM)

//QWERTY
#define KC_SFT_T_SCLN   SFT_T(KC_SCLN)

#define KC_LT_MDIA_D LT(MDIA, KC_D)
#define KC_LT_MDIA_K LT(MDIA, KC_K)
#define KC_LT_SYMB_F LT(SYMB, KC_F)
#define KC_LT_SYMB_J LT(SYMB, KC_J)

//COLEMAK
#define KC_SFT_T_O   SFT_T(KC_O)
#define KC_LT_MDIA_S LT(MDIA, KC_S)
#define KC_LT_SYMB_T LT(SYMB, KC_T)

#define KC_LT_MDIA_E LT(MDIA, KC_E)
#define KC_LT_SYMB_N LT(SYMB, KC_N)

//WORKMAN
#define KC_SFT_T_I   SFT_T(KC_I)
#define KC_LT_MDIA_H LT(MDIA, KC_H)

//NORMAN
// For keys on the homerow.  Hold for shift, keypad,mouse,and smbol layers
#define KC_SFT_T_U   SFT_T(KC_U)
#define KC_LT_MDIA_I LT(MDIA, KC_I)

// The most portable copy/paste keys (windows (mostly), linux, and some terminal emulators).
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert

#define ___ KC_TRNS
#define XXX KC_NO

// Blocking keys
#define ___X___ XXX
#define ___X2___ XXX, XXX
#define ___X3___ ___X2___, XXX
#define ___X5___ ___X3___, XXX, XXX
#define ___X15___ ___X5___, ___X5___,  ___X5___

// Transparent keys
#define ___2___ ___, ___
#define ___3___ ___2___, ___
#define ___4___ ___3___, ___
#define ___5___ ___4___, ___
#define ___6___ ___5___, ___
#define ___14___ ___5___, ___4___,  ___5___
#define ___15___ ___5___, ___5___,  ___5___

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

#define LAYOUT_ortho_5x15_wrapper(...)       LAYOUT_ortho_5x15(__VA_ARGS__)
#define LAYOUT_ortho_5x14_wrapper(...)       LAYOUT_ortho_5x14(__VA_ARGS__)

/********************************************************************/
/**  The Core rows of each given layout.                           **/
/********************************************************************/
//Dvorak on a qwerty software layer in the OS
#define ___DVORAK_L1___ KC_QUOT,    KC_COMM, KC_DOT, KC_P,   KC_Y
#define ___DVORAK_L2___ KC_SFT_T_A, KC_LT_KP_O,  KC_LT_MDIA_E,  KC_LT_SYMB_U, KC_I
#define ___DVORAK_L3___ KC_SCLN,    KC_Q,    KC_J,   KC_K,   KC_X

#define ___DVORAK_R1___ KC_F, KC_G,          KC_C, KC_R,   KC_L
#define ___DVORAK_R2___ KC_D, KC_LT_SYMB_H,  KC_LT_MDIA_T, KC_LT_KP_N, KC_SFT_T_S
#define ___DVORAK_R3___ KC_B, KC_M,          KC_W, KC_V,   KC_Z

// Qwerty based layers that I don't really use.
#define ___QWERTY_L1___ KC_Q,        KC_W,    KC_E,          KC_R,         KC_T
#define ___QWERTY_L2___ KC_SFT_T_A,  KC_S,    KC_LT_MDIA_D,  KC_LT_SYMB_F, KC_G
#define ___QWERTY_L3___ KC_Z,        KC_X,    KC_C,          KC_V,         KC_B

#define ___QWERTY_R1___ KC_Y,    KC_U,            KC_I,          KC_O,    KC_P
#define ___QWERTY_R2___ KC_H,    KC_LT_SYMB_J,    KC_LT_MDIA_K,  KC_L,    KC_SFT_T_SCLN
#define ___QWERTY_R3___ KC_N,    KC_M,            KC_COMM,       KC_DOT,  KC_SLASH

// COLEMAK
#define ___COLEMAK_L1___ KC_Q,       KC_W,    KC_F,          KC_P,          KC_G
#define ___COLEMAK_L2___ KC_SFT_T_A, KC_R,    KC_LT_MDIA_S,  KC_LT_SYMB_T,  KC_D
#define ___COLEMAK_L3___ KC_Z,       KC_X,    KC_C,          KC_V,          KC_B

#define ___COLEMAK_R1___ KC_J,    KC_L,          KC_U,          KC_Y,    KC_SCLN
#define ___COLEMAK_R2___ KC_H,    KC_LT_SYMB_N,  KC_LT_MDIA_E,  KC_I,    KC_SFT_T_O
#define ___COLEMAK_R3___ KC_K,    KC_M,          KC_COMM,       KC_DOT,  KC_SLASH

// COLEMAK-DH
#define ___COLEMAK_MOD_DH_L1___ KC_Q,        KC_W,    KC_F,          KC_P,          KC_B
#define ___COLEMAK_MOD_DH_L2___ KC_SFT_T_A,  KC_R,    KC_LT_MDIA_S,  KC_LT_SYMB_T,  KC_G
#define ___COLEMAK_MOD_DH_L3___ KC_Z,        KC_X,    KC_C,          KC_D,          KC_V

#define ___COLEMAK_MOD_DH_R1___ KC_J,  KC_L,          KC_U,          KC_Y,    KC_SCLN
#define ___COLEMAK_MOD_DH_R2___ KC_M,  KC_LT_SYMB_N,  KC_LT_MDIA_E,  KC_I,    KC_SFT_T_O
#define ___COLEMAK_MOD_DH_R3___ KC_K,  KC_H,          KC_COMM,       KC_DOT,  KC_SLASH

// WORKMAN
#define ___WORKMAN_L1___ KC_Q,        KC_D,    KC_R,          KC_W,          KC_B
#define ___WORKMAN_L2___ KC_SFT_T_A,  KC_S,    KC_LT_MDIA_H,  KC_LT_SYMB_T,  KC_G
#define ___WORKMAN_L3___ KC_Z,        KC_X,    KC_M,          KC_C,          KC_V

#define ___WORKMAN_R1___ KC_J,  KC_F,          KC_U,          KC_P,    KC_SCLN
#define ___WORKMAN_R2___ KC_Y,  KC_LT_SYMB_N,  KC_LT_MDIA_E,  KC_O,    KC_SFT_T_I
#define ___WORKMAN_R3___ KC_K,  KC_L,          KC_COMM,       KC_DOT,  KC_SLASH

// NORMAN
#define ___NORMAN_L1___ KC_Q,        KC_W,    KC_D,          KC_F,          KC_K
#define ___NORMAN_L2___ KC_SFT_T_A,  KC_S,    KC_LT_MDIA_E,  KC_LT_SYMB_T,  KC_G
#define ___NORMAN_L3___ KC_Z,        KC_X,    KC_C,          KC_V,          KC_B

#define ___NORMAN_R1___ KC_J,   KC_U,          KC_R,          KC_L,    KC_SCLN
#define ___NORMAN_R2___ KC_Y,   KC_LT_SYMB_N,  KC_LT_MDIA_I,  KC_O,    KC_SFT_T_U
#define ___NORMAN_R3___ KC_P,   KC_M,          KC_COMM,       KC_DOT,  KC_SLASH

// BEPO MAPS
// Dvorak on fr-bepo software layer in the OS.
// for dvorak and all the other qwerty like keyboards on bepo
#define ___DVORAK_FR_L1___ DB_QUOT,    DB_COMM,  DB_DOT,  BP_P,        BP_Y
#define ___DVORAK_FR_L2___ BP_SFT_T_A, BP_LT_KP_O,     BP_LT_MDIA_E,    BP_LT_SYMB_U,  BP_I
#define ___DVORAK_FR_L3___ DB_SCOLON,  BP_Q,     BP_J,    BP_K,        BP_X

#define ___DVORAK_FR_R1___ BP_F,    BP_G,        BP_C,  BP_R,  BP_L
#define ___DVORAK_FR_R2___ BP_D,    BP_LT_SYMB_H,        BP_LT_MDIA_T,  BP_LT_KP_N,  BP_SFT_T_S
#define ___DVORAK_FR_R3___ BP_B,    BP_M,        BP_W,  BP_V,  BP_Z


// Bepo on fr-bepo software layer
// for bepo on bepo
/* BP_DLR,   BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN, KC_DEL, */
#define ___SYMBOL_BEPO_L___ /* BP_DLR */ BP_DQOT,  BP_LGIL,   BP_RGIL,   BP_LPRN,   BP_RPRN
/*   KC_DEL,  BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL, */
#define ___SYMBOL_BEPO_R___    BP_AT,    BP_PLUS,  BP_MINS,   BP_SLASH,  BP_ASTR /* BP_EQL,  BP_PERC */

#define ___BEPO_FR_L1___             BP_B,        BP_ECUT, BP_P,           BP_O,          BP_EGRV
#define ___BEPO_FR_L2___             BP_SFT_T_A,  BP_LT_KP_U,    BP_LT_SYMB_I,   BP_LT_MDIA_E,  BP_COMM
#define ___BEPO_FR_L3___ /*BP_ECRC*/ BP_AGRV,     BP_Y,    BP_X,           BP_DOT,        BP_K

#define ___BEPO_FR_R1___  /* BP_DCRC,*/  BP_V, BP_D,  BP_L,    BP_J,  BP_Z
#define ___BEPO_FR_R2___  /* BP_C,   */  BP_T, BP_LT_SYMB_S,    BP_LT_MDIA_R,  BP_LT_KP_N, BP_SFT_T_M  //BP_CCED
#define ___BEPO_FR_R3___                 BP_APOS,    BP_Q,    BP_G,  BP_H, BP_F //BP_SFT_T_W

/* BP_DLR,   BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN, KC_DEL, */
/*   KC_TAB,   BP_B,    BP_ECUT, BP_P,    BP_O,    BP_EGRV, KC_BSPC, */
/*   KC_LSFT,  BP_A,    BP_U,    BP_I,    BP_E,    BP_COMM, */
/*   KC_LCTRL, BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,    KC_ENT, */
/*   ESC_FN,   BP_ECRC, KC_LGUI, KC_LALT, SPC_RALT, */
/*   TT(SWAP), KC_MNXT, */
/*   KC_MPLY, */
/*   TT(FN), TT(NUMS), KC_MPRV, */

/* /\* right hand *\/ */
/*   KC_DEL,  BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL, */
/*   KC_BSPC, BP_DCRC, BP_V,     BP_D,    BP_L,        BP_J,    BP_Z, */
/*   BP_C,    BP_T,     BP_S,    BP_R,        BP_N,    M_RSFT, */
/*   KC_ENT,  BP_APOS, BP_Q,     BP_G,    BP_H,        BP_F,    W_RCTL, */


/******************************************************************/
/* Middle Keysets for the XD75                                    */
/******************************************************************/
// For the middle keys of an xd75. It's got one more column in the middle than
// the ergodox, or the viterbi. And the Ergodox is missing a key in column 7
// counting from either end.  Which is the first and 3rd columns of these sets.

// it's all an experient.  I'm not sure what make sense here.
// stealing what I can from the ergodox layout.
/* The XD75 has 3 keys inbetween the usual left and right hand */
#define ___MIDDLE_T___ OSL(LAYERS), LCTL(KC_A),  MDIA_SYMB_KP_LAYERS
#define ___MIDDLE_1___ LCTL(KC_C),  LCTL(KC_X),  LCTL(KC_V)
#define ___MIDDLE_2___ TO(SYMB),    TO(_RGB),    TO(KEYPAD)
#define ___MIDDLE_3___ OSL(SYMB),   TO(MDIA),    OSL(KEYPAD)
#define ___MIDDLE_4___ CTL_BSPC,    ALT_DEL,     XMONAD_ESC,  ALT_ENT,   CTL_SPC

// The same, for BEPO
#define ___MIDDLE_T_BP___ OSL(LAYERS),       LCTL(BP_A),    MDIA_SYMB_KP_LAYERS
#define ___MIDDLE_1_BP___ LCTL(BP_C),        LCTL(BP_X),    LCTL(BP_V)
#define ___MIDDLE_2_BP___ TO(SYMB_ON_BEPO),  TO(_RGB),      TO(KEYPAD_ON_BEPO)
#define ___MIDDLE_3_BP___ OSL(SYMB_ON_BEPO), TO(MDIA),      OSL(KEYPAD_ON_BEPO)

// The Viterbi only has 2 keys in the middle.
#define ___MIDDLE2_T___ OSL(LAYERS),  MDIA_SYMB_KP_LAYERS
#define ___MIDDLE2_1___ LCTL(KC_C),   LCTL(KC_V)
#define ___MIDDLE2_2___ TO(SYMB),     TO(KEYPAD)
#define ___MIDDLE2_3___ OSL(SYMB),    OSL(KEYPAD)

// becomes the upper thumbs, the real 4th row if we throw away
// the number row at the top
#define ___MIDDLE2_4___ XXX,    HOME_END,    KC_PGDN, XXX
// basically the thumb keys like on the ergodox.
#define ___MIDDLE_THUMBS___ CTL_BSPC, ALT_DEL, XMONAD_ESC,   KC_PGDN, ALT_ENT, CTL_SPC

// The same, for BEPO
#define ___MIDDLE2_T_BP___ OSL(LAYERS),       MDIA_SYMB_KP_LAYERS
#define ___MIDDLE2_1_BP___ LCTL(BP_C),        LCTL(BP_V)
#define ___MIDDLE2_2_BP___ TO(SYMB_ON_BEPO),  TO(KEYPAD_ON_BEPO)
#define ___MIDDLE2_3_BP___ OSL(SYMB_ON_BEPO), OSL(KEYPAD_ON_BEPO)

#define ___MIDDLE2_4_BP___ XXX,    HOME_END,  KC_PGUP,  XXX


/********************************************************************/
/**  The bottom row and thumbs as needed.                          **/
/********************************************************************/
// the bottom rows  for keyboards on bepo.
// bepo on bepo - not enough space to go around....
#define ___ERGODOX_BOTTOM_LEFT_BP___  LCTL(BP_C),  BP_ECRC,  LCTL(BP_V),  KC_LEFT, KC_RIGHT
#define ___ERGODOX_BOTTOM_RIGHT_BP___ KC_UP,  KC_DOWN,  DB_BACKSLASH,  BP_CCED,  BP_PERC

// for dvorak on bepo
#define ___ERGODOX_BOTTOM_LEFT_FR___  LCTL(BP_C),  LCTL(BP_C),  LCTL(BP_V),  KC_LEFT, KC_RIGHT
#define ___ERGODOX_BOTTOM_RIGHT_FR___ KC_UP,  KC_DOWN,  DB_BACKSLASH,  BP_CCED,  BP_PERC

// Since we have 7 default layouts (QWERTY, DVORAK, COLEMAK and WORKMAN, NORMAN,
// 2 of them based on a Bepo software keyboard, ---  DVORAK_ON_BEPO and BEPO),
// this allows us to quickly modify the bottom row for all of the layouts
// so we don't have to alter it 4 times and hope that we haven't missed
// anything
#define ___ERGODOX_BOTTOM_LEFT___  LCTL(KC_C),  LCTL(KC_V),  KC_INS,  KC_LEFT, KC_RIGHT
#define ___ERGODOX_BOTTOM_RIGHT___ KC_UP,  KC_DOWN,  KC_BSLASH,  LCTL(KC_V),  LCTL(KC_C)

#define ___XD75_BOTTOM___     ___ERGODOX_BOTTOM_LEFT___,    ___MIDDLE_4___, ___ERGODOX_BOTTOM_RIGHT___
#define ___XD75_BOTTOM_FR___  ___ERGODOX_BOTTOM_LEFT_FR___, ___MIDDLE_4___, ___ERGODOX_BOTTOM_RIGHT_FR___

#define ___VITERBI_BOTTOM___    ___ERGODOX_BOTTOM_LEFT___,    ___MIDDLE2_4___, ___ERGODOX_BOTTOM_RIGHT___
#define ___VITERBI_BOTTOM_FR___ ___ERGODOX_BOTTOM_LEFT_FR___, ___MIDDLE2_4___, ___ERGODOX_BOTTOM_RIGHT_FR___
#define ___VITERBI_BOTTOM_BP___ ___ERGODOX_BOTTOM_LEFT_BP___, ___MIDDLE2_4___, ___ERGODOX_BOTTOM_RIGHT_BP___
#define ___VITERBI_THUMBS_BOTTOM___   ___4___, ___MIDDLE_THUMBS___, ___4___


#define ___ERGODOX_THUMB_LEFT___                \
  OS_RALT, TG(MDIA),                            \
    HOME_END,                                   \
    CTL_BSPC, ALT_DEL, XMONAD_ESC

#define ___ERGODOX_THUMB_RIGHT___               \
  TG(SYMB), OS_RALT,                            \
    KC_PGUP,                                    \
    KC_PGDN, ALT_ENT, CTL_SPC

#define ___ERGODOX_THUMB_RIGHT_BP___            \
  TG(SYMB_ON_BEPO), OS_RALT,                    \
    KC_PGUP,                                    \
    KC_PGDN, ALT_ENT, CTL_SPC

#define ___ERGODOX_TRANS_THUMBS___ ___6___
#define ___ERGODOX_TRANS_BOTTOM___  ___5___
#define ___ERGODOX_TRANS_6_ROW___  ___6___
#define ___TRANS_6_COL___ ___6___

/*******************************************************************/
/** For the top rows.  Numbers for most things, symbols for Bepo. **/
/*******************************************************************/

// for everything on qwerty.
#define ___NUMBER_L___ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ___NUMBER_R___ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

// function key rows, works for everyone.
#define ___FUNC_L___   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ___FUNC_R___   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ___FUNC_1_6___   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6
#define ___FUNC_7_12___  KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, KC_F12

// a top symbol row if someone wants it.
#define ___SYMB_L___   KC_EXLM,   KC_AT,    KC_HASH,  KC_DLR,   KC_PERC
#define ___SYMB_R___   KC_CIRC,   KC_AMPR,  KC_AST,   KC_LPRN,  KC_RPRN

// For numbers on bepo. Bepo has numbers on shifted keys, the
// reverse of most keyboard layouts.
#define ___NUMBER_BEPO_L___ DB_1,   DB_2,   DB_3,   DB_4,   DB_5
#define ___NUMBER_BEPO_R___ DB_6,   DB_7,   DB_8,   DB_9,   DB_0


/*******************************************************************/
/* Rows for the auxillary layers.                                  */
/* the KC_P?  codes don't work for me. I don't use those shifted   */
/* values anyway.                                                  */
/*******************************************************************/

// Keypads
#define ___KEYPAD_1___ KC_7,  KC_8,    KC_9,     KC_PSLS
#define ___KEYPAD_2___ KC_4,  KC_5,    KC_6,     KC_PAST
#define ___KEYPAD_3___ KC_1,  KC_2,    KC_3,     KC_PMNS
#define ___KEYPAD_4___ KC_0,  KC_DOT,  KC_PEQL,  KC_PPLS

// Keypad from the default keymap.c of the xd75
#define ___KEYPAD_1_ALT___ KC_P7, KC_P8,  KC_P9,   KC_MINS
#define ___KEYPAD_2_ALT___ KC_P4, KC_P5,  KC_P6,   KC_PLUS
#define ___KEYPAD_3_ALT___ KC_P1, KC_P2,  KC_P3,   KC_PENT
#define ___KEYPAD_4_ALT___ KC_P0, KC_DOT, KC_PENT, KC_PENT

// For Bepo
#define ___KEYPAD_1_BP___ DB_7,  DB_8,    DB_9,     BP_SLASH
#define ___KEYPAD_2_BP___ DB_4,  DB_5,    DB_6,     BP_ASTR
#define ___KEYPAD_3_BP___ DB_1,  DB_2,    DB_3,     DB_MINUS
#define ___KEYPAD_4_BP___ DB_0,  DB_DOT,  DB_EQL,   BP_PLUS



// SYMBOLS

// An arrangement for the left hand with a focus on the ()[]{}s.
#define ___SYMBOLS_1___  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE
#define ___SYMBOLS_2___  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV
#define ___SYMBOLS_3___  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD

// A larger 6 column arrangement for the left hand, A merge of dvorak and the above.
#define ___SYMBOLS6_1___  KC_GRV,  KC_LT,    KC_GT,    KC_LCBR,  KC_RCBR,  KC_HASH
#define ___SYMBOLS6_2___  KC_AMPR, KC_AT,    KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PERC
#define ___SYMBOLS6_3___  KC_DLR,  KC_DQT,   KC_QUOT,  KC_LBRC,  KC_RBRC,  KC_COLON
#define ___SYMBOLS6_4___  ___2___, KC_TILD,  KC_DOT,   KC_EXLM,  KC_SCLN

// A symbol pad.  Basically the same layout as a number pad with the symbols
// instead of the numbers with some extras around it, in familiar places for the
// right hand.
#define ___SYMPAD_1___  KC_GRV,  KC_AMPR, KC_ASTR, KC_LCBR,  KC_PLUS,  KC_PIPE
#define ___SYMPAD_2___  KC_TILD, KC_DLR,  KC_PERC, KC_CIRC,  KC_ASTR,  KC_GRV
#define ___SYMPAD_3___  ___,     KC_EXLM, KC_AT,   KC_HASH,  KC_MINUS, KC_SLASH
#define ___SYMPAD_4___  ___,     KC_RCBR, KC_DOT,  KC_EQUAL, KC_UNDS,  KC_BSLASH

// Function pad.  Same idea as above, but for function keys.
#define ___FUNCPAD_T___   KC_F10,  KC_F11,  KC_F12
#define ___FUNCPAD_1___   KC_F7,   KC_F8,   KC_F9
#define ___FUNCPAD_2___   KC_F4,   KC_F5,   KC_F6
#define ___FUNCPAD_3___   KC_F1,   KC_F2,   KC_F3


//---  all over again for BEPO

// SYMBOLS FOR BEPO
// The top row.  Bepo has symbols not numbers. Numbers are the shifted values.
#define ___SYMBOL_BEPO_L___ /* BP_DLR */ BP_DQOT,  BP_LGIL,   BP_RGIL,   BP_LPRN,   BP_RPRN
/*   KC_DEL,  BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL, */
#define ___SYMBOL_BEPO_R___    BP_AT,    BP_PLUS,  BP_MINS,   BP_SLASH,  BP_ASTR /* BP_EQL,  BP_PERC */

// An arrangement for the left hand with a focus on the ()[]{}s.
#define ___SYMBOLS_1_BP___ KC_EXLM,  BP_AT,    DB_LCBR,  DB_RCBR,  DB_PIPE
#define ___SYMBOLS_2_BP___ DB_HASH,  BP_DLR,   DB_LPRN,  DB_RPRN,  DB_GRV
#define ___SYMBOLS_3_BP___ BP_PERC,  DB_CIRC,  DB_LBRC,  DB_RBRC,  DB_TILD

// A larger 6 column arrangement for the left hand, A merge of dvorak and the above.
#define ___SYMBOLS6_1_BP___  DB_GRV,  DB_LESS, DB_GRTR, DB_LCBR,  DB_RCBR,  DB_HASH
#define ___SYMBOLS6_2_BP___  KC_AMPR, BP_AT,   BP_ASTR, DB_LPRN,  DB_RPRN,  BP_PERC
#define ___SYMBOLS6_3_BP___  BP_DLR,  BP_DQOT, DB_QUOT, DB_LBRC,  DB_RBRC,  KC_COLON

#define ___SYMBOLS6_4_BP___  ___2___, DB_TILD, DB_DOT,  KC_EXLM, DB_SCOLON

// A symbol pad.  Basically the same layout as a number pad with the symbols
// instead of the numbers with some extras around it, in familiar places for the
// right hand.
#define ___SYMPAD_1_BP___  DB_GRV,  BP_AMPR, BP_ASTR, DB_LCBR,  BP_PLUS,  DB_PIPE
#define ___SYMPAD_2_BP___  DB_TILD, BP_DLR,  BP_PERC, DB_CIRC,  BP_ASTR,  DB_GRV
#define ___SYMPAD_3_BP___  ___,     BP_EXLM, BP_AT,   DB_HASH,  BP_MINS,  BP_SLSH
#define ___SYMPAD_4_BP___  ___,     DB_RCBR, DB_DOT,  BP_EQL,   BP_MINUS, DB_BACKSLASH



// MOUSE, ARROW and MEDIA KEY SETS

#define ___MOUSE_LDUR___      KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R
#define ___MWHEEL_LDUR___     KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R
#define ___MOUSE_BTNS_R___    KC_BTN1,  KC_BTN2,  KC_BTN3,  KC_BTN4,  KC_BTN5
#define ___MOUSE_BTNS_L___    KC_BTN5,  KC_BTN4,  KC_BTN3,  KC_BTN2,  KC_BTN1
#define ___MOUSE_ACCL_012___  KC_ACL0,  KC_ACL1,  KC_ACL2
#define ___MACCL___ ___MOUSE_ACCL_012___

#define ___PRV_PLAY_NXT_STOP KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define ___VDN_MUTE_VUP___ KC_VOLD, KC_MUTE, KC_VOLU

#define ___MUTE_PRV_PLAY_NXT_STOP___  KC_MUTE,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define ___MUTE_PLAY_STOP___  KC_MUTE,  KC_MPLY,  KC_MSTP
#define ___VI_ARROWS___       KC_LEFT,  KC_DOWN,  KC_UP, KC_RIGHT

// RGB FUNCTION Keysets
// RGB row for the _FN layer from the redo of the default keymap.c
#define ___RGB_HUE_SAT_INT_UP___ RGB_HUI, RGB_SAI, RGB_VAI, RGB_RMOD
#define ___RGB_HUE_SAT_INT_DN___ RGB_HUD, RGB_SAD, RGB_VAD, RGB_MOD
#define ___RGB_MODE_PRV_NXT___ RGB_RMOD, RGB_MOD
#define ___RGB_TOGGLE___ RGB_TOG
#define ___RGB_P_B_R_SW_SN___ RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN
#define ___RGB_KXGT___ RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T

// Print screen, screen lock, pause
#define ___PSCR_SLCK_PAUS___ KC_PSCR, KC_SLCK, KC_PAUS


// LAYER Keysets. Changing the Default base layer or the transient layers.
#define ___LAYERS_B1_2___ DF(BEPO), DF(DVORAK_ON_BEPO)
#define ___LAYERS_B2_2___ DF(COLEMAK), DF(DVORAK)
#define ___LAYERS_B3_3___ DF(QWERTY), DF(NORMAN), DF(WORKMAN)
#define ___LAYERS_B4_3___ ___X3___

// transient layers.
#define ___LAYERS_T_BP_3___ TO(MDIA), TO(SYMB_ON_BEPO), TO(KEYPAD_ON_BEPO)
#define ___LAYERS_T_3___    TO(MDIA), TO(SYMB), TO(KEYPAD)
#define ___LAYERS_T_DEF___  TO(_RGB), ___X2___


#endif
