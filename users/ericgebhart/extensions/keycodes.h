#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
#include "eeconfig.h"
#include "keymap_bepo.h"
//#include "keymap_us_international.h"
#include "keymap_us_international_linux.h"
#include "lang.h"
#include "ericgebhart.h"

//#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */

// #define DEFAULT_LANG EN // US_INT // EN, BEPO, US_INT, EURkey

#define KEY_NAME(NAME, ...) NAME,
#define BLANK(...)

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);

enum userspace_custom_keycodes {
  // Get all the custom keys from the defs if we can.
  ALT_LOCAL_KEYS_START = SAFE_RANGE,
#ifdef ALT_LOCAL_ENABLE
#undef MK_KEY
#define MK_KEY KEY_NAME
#undef MK_SKEY
#define MK_SKEY KEY_NAME
#include "altlocal_keys.def"
#undef MK_KEY
#undef MK_SKEY
#endif
  ALT_LOCAL_KEYS_END,

#ifdef ACCENTED_KEYS_ENABLE
#undef ACCENTED
#define ACCENTED KEY_NAME
#include "accented_keys.def"
#undef ACCENTED
#endif

#ifdef TAP_HOLD_ENABLE
#undef TP_TPL
#define TP_TPL KEY_NAME
#undef TP_SML
#define TP_SML KEY_NAME
#undef OPEN_OCL
#define OPEN_OCL KEY_NAME
#undef OPEN_OCL_ND
#define OPEN_OCL_ND KEY_NAME
#include "tap_hold.def"
#undef OPEN_OCL
#undef OPEN_OCL_ND
#undef TP_TPL
#undef TP_SML
#endif

#ifdef UNICODE_ENABLE
#undef UC_STR
#define UC_STR KEY_NAME
#include "unicode.def"
#undef UC_STR
#endif

#ifdef SEND_STRING_ENABLE
#undef SEND_STR
#define SEND_STR KEY_NAME
#undef SEND_STR_DELAY
#define SEND_STR_DELAY KEY_NAME
#include "send_string.def"
#undef SEND_STR
#undef SEND_STR_DELAY
#endif

#ifdef SMART_LOCK_ENABLE
#undef SMLM
#define SMLM KEY_NAME
#undef SMLL
#define SMLL KEY_NAME
#include "smart_lock.def"
#undef SMLM
#undef SMLL
#endif

#ifdef MOD_LOCK_ENABLE
#undef IGNORE_KC
#define IGNORE_KC BLANK
#undef MODL
#define MODL KEY_NAME
#include "mod_lock.def"
#undef IGNORE_KC
#undef MODL
#endif


#undef IGNORE_KEY
#define IGNORE_KEY BLANK
#undef CANCEL_KEY
#define CANCEL_KEY BLANK
#undef ONESHOT
#undef NSHOT
#define ONESHOT KEY_NAME
#define NSHOT KEY_NAME

#ifdef NSHOT_ENABLE
#include "nshot.def"
#else
  TS_RCTL,
  TS_LCTL,
#endif

#ifdef ONESHOT_MOD_ENABLE
#include "oneshot.def"
#endif

#undef IGNORE_KEY
#undef CANCEL_KEY
#undef ONESHOT
#undef NSHOT

#ifdef SWAPPER_ENABLE
#undef SWAPPER_KEY
#define SWAPPER_KEY KEY_NAME
#include "swapper.def"
#undef SWAPPER_KEY
#endif

#ifdef NOT_DEAD_ENABLE
#undef NOT_DEAD
#define NOT_DEAD KEY_NAME
#include "not_dead.def"
#undef NOT_DEAD
#endif

#include "custom_keys.def"
  NEW_SAFE_RANGE
};

#define FIRST_LAYER (BEGINNING_OF_BASE_LAYERS + 1)

#define TL_DQUO TLKC(_DQUO)
#define TL_QUOT TLKC(_QUOT)
#define TL_COMM TLKC(_COMM)
#define TL_DOT  TLKC(_DOT)
#define TL_SCLN TLKC(_SCLN)
#define TL_SLSH TLKC(_SLSH)
#define TL_EXLM TLKC(_EXLM)
#define TL_MINS TLKC(_MINS)
#define TL_LPRN TLKC(_LPRN)
#define TL_LCBR TLKC(_LCBR)
#ifdef SYMBOL_LAYER_ENABLE
#define TL_DOT_SYMB LT(LN_SYMB, LANG_KC(TL_DOT))
#endif


#define BP_LT BP_LABK
#define BP_GT BP_RABK
#define BP_TAB KC_TAB
#define US_GT US_RABK
#define US_LT US_LABK
#define US_TAB KC_TAB
#define US_DCMM KC_COMM // us doesn't have this dead key.

// this is odd, there is interplay between this and
// the not-dead extension. - and tap-hold not-dead.
#undef US_TILD
#define US_TILD KC_TILD
// redefine us_circ so we actually get a circ.
#undef US_CIRC
#define US_CIRC KC_CIRC
#define US_EQUAL KC_EQUAL
// redefine us_quote so we actually get a quote.
#undef US_QUOT
#define US_QUOT KC_QUOT

#define US_PRINT_SCREEN KC_PRINT_SCREEN
#define US_SCROLL_LOCK KC_SCROLL_LOCK
#define US_PAUSE KC_PAUSE
#define BP_PRINT_SCREEN KC_PRINT_SCREEN
#define BP_SCROLL_LOCK KC_SCROLL_LOCK
#define BP_PAUSE KC_PAUSE

#define BP_F1 KC_F1
#define BP_F2 KC_F2
#define BP_F3 KC_F3
#define BP_F4 KC_F4
#define BP_F5 KC_F5
#define BP_F6 KC_F6
#define BP_F7 KC_F7
#define BP_F8 KC_F8
#define BP_F9 KC_F9
#define BP_F10 KC_F10
#define BP_F11 KC_F11
#define BP_F12 KC_F12
#define BP_TRNS KC_TRNS

#define US_F1 KC_F1
#define US_F2 KC_F2
#define US_F3 KC_F3
#define US_F4 KC_F4
#define US_F5 KC_F5
#define US_F6 KC_F6
#define US_F7 KC_F7
#define US_F8 KC_F8
#define US_F9 KC_F9
#define US_F10 KC_F10
#define US_F11 KC_F11
#define US_F12 KC_F12
#define US_TRNS KC_TRNS

#ifdef KEYPAD_LAYER_ENABLE
#define TT_KEYPAD TT(LANG_N(_KEYPAD))
#define MO_KEYPAD MO(LANG_N(_KEYPAD))
#else
#define TT_KEYPAD ___
#define MO_KEYPAD ___
#endif

#ifdef SYMBOL_LAYER_ENABLE
#define TT_SYMB TT(LANG_N(_SYMB))
#define MO_SYMB MO(LANG_N(_SYMB))
#define OSL_SYMB OSL(LANG_N(_SYMB))
#else
#define TT_SYMB ___
#define MO_SYMB ___
#define OSL_SYMB ___
#endif

#ifdef TOPROWS_LAYER_ENABLE
#define TT_TOPROWS TT(LANG_N(_TOPROWS))
#define MO_TOPROWS MO(LANG_N(_TOPROWS))
#else
#define TT_TOPROWS ___
#define MO_TOPROWS ___
#endif

#ifdef RGB_LAYER_ENABLE
#define MO_RGB MO(_RGB)
#else
#define MO_RGB ___
#endif

#ifdef ADJUST_LAYER_ENABLE
#define MO_ADJUST MO(_ADJUST)
#else
#define MO_ADJUST ___
#endif

#ifdef ACCENTS_MORTE_LAYER_ENABLE
//#define LN_ACCENTS_MORTE LANG_N(_ACCENTS_MORTE)
#define OSL_ACCENTS_MORTE OSL(LANG_N(_ACCENTS_MORTE))
#else
#define OSL_ACCENTS_MORTE ___
#endif

#ifdef ACCENTS_LAYER_ENABLE
#define LN_ACCENTS LANG_N(_ACCENTS)
#define OSL_ACCENTS OSL(LN_ACCENTS)
#else
#define OSL_ACCENTS ___
#endif

#ifdef MORTE_LAYER_ENABLE
#define LN_MORTE LANG_N(_MORTE)
#define OSL_MORTE OSL(LN_MORTE)
#else
#define OSL_MORTE ___
#endif

#define CTLGUI_T(kc) MT(MOD_LGUI | MOD_LCTL, kc)
#define SFTGUI_T(kc) MT(MOD_LGUI | MOD_LSFT, kc)
#define ALTGUI_T(kc) MT(MOD_LGUI | MOD_LALT, kc)

#define ALT_ENT     ALGR_T(KC_ENT)       // Alt oor nter
#define CTL_ENT     CTL_T(KC_ENT)       // ctrl or space
#define CTL_SPC     CTL_T(KC_SPC)       // ctrl or space
#define CTL_BSPC    CTL_T(KC_BSPC)      // ctrl or backspace
#define ALT_DEL     ALT_T(KC_DEL)       // Alt or delete
#define GUI_ESC     GUI_T(KC_ESC)       // Gui or escape
#define ALGR_SYMB   ALGR_T(TG(LANG_N(_SYMB))) // Alt gre or toggle symbol layer

// one shot on tap, or hold like usual
#define OSLCTL_CTL CTL_T(OS_LCTL)
#define OSLSFT_SFT SFT_T(OS_LSFT)
#define OSLALT_ALT ALT_T(OS_LALT)
#define OSLGUI_GUI GUI_T(OS_LGUI)

/* miryoku */
/*   esc_media, space_navnm, tab_navm,  ENT_SYM, BSPC_TOPR, del_fun */
/* hands down */
/* TL_COMM, TL_DOT_SYMB, GUI_ESC, ALT_ENT, SPC_TOPR, BSPC */

// Lots of LT options.  My thumb keys.
#ifdef TOPROWS_LAYER_ENABLE
#define LN_TOPROWS LANG_N(_TOPROWS)
#else
#define LN_TOPROWS KC_NO
#endif

#ifdef SYMBOL_LAYER_ENABLE
#  define LN_SYMB LANG_N(_SYMB)
#  define TH_LTR_SYM LT(LN_SYMB, THUMB_LETTER)
#else
#  define TH_LTR_SYM THUMB_LETTER
#endif

#define TH_LTR_NAV LT(_NAV, THUMB_LETTER)

#define LN_KEYPAD LANG_N(_KEYPAD)

#define ACCENTS_RALT MT(MOD_RALT, OSL_ACCENTS)
#define ACCENTS_CTL MT(MOD_LCTL, OSL_ACCENTS)
#define ENT_SYM LT(LN_SYMB, KC_ENT)
#define ENT_NAV LT(_NAV, KC_ENT)
#define ENT_TOPR LT(LN_TOPROWS, KC_ENT)

#define ESC_TOPR LT(LN_TOPROWS, KC_ESC)
#define ESC_SYMB LT(LN_SYMB, KC_ESC)
#define ESC_NUM LT(LN_KEYPAD, KC_ESC)
#define ESC_MEDIA LT(_MEDIA, KC_ESC)

#define DEL_FUN LT(_FUN, KC_DEL)
#define TAB_NAVM LT(_NAVm, KC_TAB)
#define TAB_NUM LT(LN_KEYPAD, KC_TAB)
#define I_SYMB LT(LN_SYMB, KC_I)

#define SPC_NAVm   LT(_NAVm, KC_SPC)
#define SPC_NAVnm  LT(_NAVnm, KC_SPC)
#define SPC_NAV    LT(_NAV, KC_SPC)
#define SPC_SYMB   LT(LN_SYMB, KC_SPC)
#define SPC_TOPR   LT(LN_TOPROWS, KC_SPC)
#define SPC_LAYR   LT(_LAYERS, KC_SPC)
#define SPC_ADJ    LT(_ADJUST, KC_SPC)
#define SPC_NUM    LT(LN_KEYPAD, KC_SPC)

#define BSPC_NAVm  LT(_NAVm, KC_BSPC)
#define BSPC_NAV   LT(_NAV, KC_BSPC)
#ifdef SYMBOL_LAYER_ENABLE
#define BSPC_SYMB  LT(LN_SYMB, KC_BSPC)
#else
#define BSPC_SYMB  KC_BSPC
#endif
#define BSPC_TOPR  LT(LN_TOPROWS, KC_BSPC)
#define BSPC_NUM   LT(LN_KEYPAD, KC_BSPC)
#define BSPC_ALT   MT(MOD_LALT, KC_BSPC)
#define BSPC_MEDIA LT(_MEDIA, KC_BSPC)

#define KC_BKTAB    LSFT(KC_TAB)

// layer toggles
#define LAYER_OSL   OSL(_LAYERS)
#define SYM_OSL     OSL(LN_SYMB)
#define SYM_TG      TG(LN_SYMB)
#define SYM_MO      MO(LN_SYMB)
#define NAV_TG      TG(_NAV)
#define COMBO_REF_TG_EN TG(_COMBO_REF)
#define NUM_OSL     OSL(LN_KEYPAD)
#define NUM_TO      TO(LN_KEYPAD)
#define FUN_OSL     OSL(LN_FUNC)
#define SYS_OSL     OSL(LN_SYSTEM)
#define SYS_TG      TG(LN_SYSTEM)

// Shortcuts
#define S_CUT       S(KC_DEL)
#define S_COPY      C(KC_INS)
#define S_PASTE     S(KC_INS)
#define S_UNDO      C(KC_Z)
#define S_REDO      C(KC_Y)
#define S_SAVE      C(KC_S)
#define S_ALL       C(KC_A)
#define S_BACK      A(KC_LEFT)
#define S_FWD       A(KC_RIGHT)
#define C_BSPC      C(KC_BSPC)
#define SCREEN      S(C(KC_PSCR))

// One Shot Mods keycodes,
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

#define UC_IRNY UC(0x2E2E)
#define UC_CLUE UC(0x203D)


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
  TD_DVORAK_BEPO = 8,
  TD_UP_HOME = 9,
  TD_DOWN_END = 10,
  TD_RIGHT_TAB = 11,
  TD_LEFT_BACKTAB = 12
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
#define RIGHT_TAB       TD(TD_RIGHT_TAB)   // Bad idea these 4. Maybe with good timing...
#define LEFT_BACKTAB    TD(TD_LEFT_BACKTAB)
#define UP_HOME         TD(TD_UP_HOME)
#define DOWN_END        TD(TD_DOWN_END)  //  No! Down Down Not End....

// HOME ROW LAYER TOGGLE (LT) and Shift.
// both sides of the home row have  "shift, ___, media , symb, ___"  and  "___, symb, media, ___, shift".
// so pinky fingers are shift when held and the index and second fingers are symbol and
// media layers when held.

// The most portable copy/paste keys (windows (mostly), linux, and some terminal emulators).
// The KC_CCCV key takes care of the last two...
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert
#define EOT     LCTL(KC_D)
#define NAK     LCTL(KC_U)
#define XPASTE   LCTL(LSFT(KC_V))
#define UNDO    LCTL(KC_Z)
#define XCOPY   LCTL(LSFT(KC_C))

#undef ___ //kint defines it as KC_NO
#define ___ KC_TRNS
#define XXX KC_NO
#define ____ _TRNS

// Blocking keys
#define _X_ XXX
#define ___X___ XXX
#define ___X2___ XXX, XXX
#define ___X3___ ___X2___, XXX
#define ___X4___ ___X3___, XXX
#define ___X5___ ___X4___, XXX
#define ___X6___ ___X5___, XXX
#define ___X12___ ___X6___, ___X6___
#define ___X15___ ___X5___, ___X5___,  ___X5___

// Transparent keys
#define ___2___ ___, ___
#define ___3___ ___2___, ___
#define ___4___ ___3___, ___
#define ___5___ ___4___, ___
#define ___6___ ___5___, ___
#define ___10___ ___6___, ___4___
#define ___12___ ___6___, ___6___
#define ___14___ ___5___, ___4___,  ___5___
#define ___15___ ___5___, ___5___,  ___5___
#define ___16___ ___15___, ___

#define ____2_ ____, ____
#define ____3_ ____2_, ____
#define ____4_ ____3_, ____
#define ____5_ ____4_, ____
#define ____6_ ____5_, ____
#define ____10_ ____6_, ____4_
#define ____12_ ____6_, ____6_
#define ____14_ ____5_, ____4_,  ____5_
#define ____15_ ____5_, ____5_,  ____5_
#define ____16_ ____15_, ____

int on_qwerty(void);

#ifdef TAP_DANCES_ENABLE
int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);
#endif
