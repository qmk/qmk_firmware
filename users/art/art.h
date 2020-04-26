#pragma once
#include QMK_KEYBOARD_H

extern bool is_win;
  
enum layer_names {
  QWERTY,
  WORKMAN,
  
#if defined(KEYBOARD_wheatfield_split75)
  BASE,

  QWERTY_MOD,
  LAYOUT_CHG,
  MEDIA,
  COMBOS,
  STRINGS,
  CONFIG,
#elif defined(KEYBOARD_ergodone)
  FKEYS,
  CTRL_NAV,
  SHIFT_NAV,
#endif
  NAV,
  GIT,
  GIT_C,
  GIT_P,
  GIT_S
};

enum custom_keycodes_art {
  CTRL_CTV = SAFE_RANGE,
  CTRL_LCTV,
  SARCASM,
  N_BSPACE,

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
  G_BS_C,
  G_CHEC,	
  G_COMM,
  G_DIFF,
  G_FTCH,
  G_LOG,
  G_MERG,
  G_P,
  G_RST,
  G_S,
  G_BS_S,
  G_STAT,
  G_STSH,
  G_SHOW,

  NEW_SAFE_RANGE  //for keymap specific codes
};