#pragma once
#include QMK_KEYBOARD_H

#define CTL_ALT(kc) (CTL_ALT_START + ((kc) & 0xff))

extern bool is_win;

enum layer_names {
  QWERTY,
  WORKMAN,  
  BASE, //only specific for split75
#if defined(KEYBOARD_wheatfield_split75)
  QWERTY_MOD,
  LAYOUT_CHG,
#elif defined(KEYBOARD_ergodone)
  FKEYS,
  CTRL_NAV,
  SHIFT_NAV,
#endif

  MEDIA,
  COMBOS,
  STRINGS,
  CONFIG,
  NAV,
  NUMPAD,
  GIT,
  GIT_C,
  GIT_S
};

enum custom_keycodes_art {
  CTRL_CTV = SAFE_RANGE,
  CTRL_LCTV,
  CTRL_CAV,
  SARCASM,

  TOG_OS,
  CTR_ALT,
  OS_CTRL,
  OS_WIN,

  TILD_BLOCK,
  ADMINS,
  PRESCRIPTION,
  FOURS,
  
  G_ADD,
  G_BRCH,
  G_C,
  G_CHEC,	
  G_COMM,
  G_DEV,
  G_DIFF,
  G_FTCH,
  G_LOG,
  G_MERG,
  G_P,
  G_RST,
  G_S,
  G_STAT,
  G_STSH,
  G_SHOW,

  CTL_ALT_START,
  CTL_ALT_END = CTL_ALT_START + 0xff,

  NEW_SAFE_RANGE  //for keymap specific codes
};
