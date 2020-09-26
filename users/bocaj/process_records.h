#pragma once
#include "bocaj.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
  KC_EPRM = PLACEHOLDER_SAFE_RANGE, // can always be here
  KC_MWRK,
  KC_WWRK,
  KC_MQWR,
  KC_VRSN,
  LM_GRAVE,            // Shift if held, layer change if tapped
  JJ_COPY,
  JJ_PSTE,
  JJ_ARRW,
  KC_CCCV,
  MC_LOCK,
  KC_DCLR,
  KC_MAKE,
  UC_FLIP,           // (ಠ痊ಠ)┻━┻
  UC_TABL,           // ┬─┬ノ( º _ ºノ)
  UC_SHRG,           // ¯\_(ツ)_/¯
  UC_DISA,           // ಠ_ಠ
  NEW_SAFE_RANGE  //use "NEWPLACEHOLDER for keymap specific codes
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

// One Shot
#define OS_LSFT OSM(MOD_LSFT)

// Space Cadet Hyper/Meh and [/]
#define HYP_LBK ALL_T(KC_LBRACKET)
#define MEH_RBK MEH_T(KC_RBRACKET)

#define GUI_CTR(os, kc) MT( (os == 0) ? (MOD_LGUI) : (MOD_LCTL), kc )

// Layout beauti-/simpli-fication
#define KC_LWEN LT(_LOWER, KC_ENTER)
#define KC_ADJS TT(_ADJUST)
#define KC_NUMS TT(_LOWER)
#define KC_GAME TT(_DIABLO)

// Other Keycodes
#define KC_RST RESET
#define KC_BS  KC_BSLASH
