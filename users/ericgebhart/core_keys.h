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
