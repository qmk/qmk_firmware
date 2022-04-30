#pragma once
#include "mutecivilian.h"

enum combo_events {
  COMBO_ALFRED,
  COMBO_AMPERSAND,
  COMBO_CLICK_L,
  COMBO_CLICK_R,
  COMBO_DASH,
  COMBO_DBL_QUOT,
  COMBO_ESC,
  COMBO_L_CURLY_BRACE,
  COMBO_L_PAREN,
  COMBO_L_SQR_BRACK,
  COMBO_QUOT,
  COMBO_R_CURLY_BRACE,
  COMBO_R_PAREN,
  COMBO_R_SQR_BRACK,
  COMBO_TAB,
  COMBO_TERMINAL,
  COMBO_UNDERSCORE,
  COMBO_WORD_CAPS,
  /* COMBO_BSPC, */
  /* COMBO_BSPC_NUM, */
  /* COMBO_DEL, */
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_alfred[]      = {  NAV_SPACE,  SYM_ENT,     COMBO_END};
const uint16_t PROGMEM combo_ampersand[]   = {  KC_I,       KC_U,        COMBO_END};
const uint16_t PROGMEM combo_click_left[]  = {  SYM_ENT,    WORDS_BACK,  COMBO_END};
const uint16_t PROGMEM combo_click_right[] = {  MISC_DEL,   NAV_SPACE,   COMBO_END};
const uint16_t PROGMEM combo_dash[]        = {  KC_DOT,     SYM_SLSH,    COMBO_END};
const uint16_t PROGMEM combo_dub_quot[]    = {  KC_AL,      KC_GK,       COMBO_END};
const uint16_t PROGMEM combo_esc[]         = {  KC_CA,      KC_AS,       COMBO_END};
const uint16_t PROGMEM combo_l_curly[]     = {  KC_X,       KC_C,        COMBO_END};
const uint16_t PROGMEM combo_l_paren[]     = {  KC_AS,      KC_GD,       COMBO_END};
const uint16_t PROGMEM combo_l_sqr_brack[] = {  KC_W,       KC_E,        COMBO_END};
const uint16_t PROGMEM combo_quot[]        = {  KC_AL,      KC_CSCLN,    COMBO_END};
const uint16_t PROGMEM combo_r_curly[]     = {  KC_X,       KC_V,        COMBO_END};
const uint16_t PROGMEM combo_r_paren[]     = {  KC_AS,      KC_SF,       COMBO_END};
const uint16_t PROGMEM combo_r_sqr_brack[] = {  KC_W,       KC_R,        COMBO_END};
const uint16_t PROGMEM combo_tab[]         = {  NAV_Z,      KC_X,        COMBO_END};
const uint16_t PROGMEM combo_terminal[]    = {  KC_SF,      KC_GD,       COMBO_END};
const uint16_t PROGMEM combo_unds[]        = {  KC_DOT,     KC_COMM,     COMBO_END};
const uint16_t PROGMEM combo_wcaps[]       = {  KC_SF,      KC_SJ,       COMBO_END};
/* const uint16_t PROGMEM combo_bspc[]         = {  KC_O,       KC_P,        COMBO_END}; */
/* const uint16_t PROGMEM combo_bspc_num[]    = {  KC_EQL,     KC_9,        COMBO_END}; */
/* const uint16_t PROGMEM combo_del[]        = {  KC_I,       KC_O,        COMBO_END}; */

combo_t key_combos[] = {
  [COMBO_ALFRED]         = COMBO(  combo_alfred,       LGUI(KC_SPC)),
  [COMBO_AMPERSAND]      = COMBO(  combo_ampersand,    KC_AMPERSAND),
  [COMBO_CLICK_L]        = COMBO(  combo_click_left,   L_CLICK),
  [COMBO_CLICK_R]        = COMBO(  combo_click_right,  R_CLICK),
  [COMBO_DASH]           = COMBO(  combo_dash,         KC_MINUS),
  [COMBO_DBL_QUOT]       = COMBO(  combo_dub_quot,     KC_DOUBLE_QUOTE),
  [COMBO_ESC]            = COMBO(  combo_esc,          KC_ESC),
  [COMBO_L_CURLY_BRACE]  = COMBO(  combo_l_curly,      KC_LCBR),
  [COMBO_L_PAREN]        = COMBO(  combo_l_paren,      KC_LEFT_PAREN),
  [COMBO_L_SQR_BRACK]    = COMBO(  combo_l_sqr_brack,  KC_LBRC),
  [COMBO_QUOT]           = COMBO(  combo_quot,         KC_QUOT),
  [COMBO_R_CURLY_BRACE]  = COMBO(  combo_r_curly,      KC_RCBR),
  [COMBO_R_PAREN]        = COMBO(  combo_r_paren,      KC_RIGHT_PAREN),
  [COMBO_R_SQR_BRACK]    = COMBO(  combo_r_sqr_brack,  KC_RBRC),
  [COMBO_TAB]            = COMBO(  combo_tab,          KC_TAB),
  [COMBO_TERMINAL]       = COMBO(  combo_terminal,     KC_NUMLOCK),
  [COMBO_UNDERSCORE]     = COMBO(  combo_unds,         KC_UNDS),
  [COMBO_WORD_CAPS]      = COMBO(  combo_wcaps,        CAPS_WORD)
  /* [COMBO_BSPC]           = COMBO(  combo_bspc,         KC_BSPC), */
  /* [COMBO_BSPC_NUM        = COMBO(  combo_bspc_num,     KC_BSPC), */
  /* [COMBO_DEL]            = COMBO(  combo_del,          KC_DEL), */
};
