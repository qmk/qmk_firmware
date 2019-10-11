#include QMK_KEYBOARD_H
#include "bootloader.h"
#include "tominabox1.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_wrapper( \
___________________CRKBD1__________________,
___________________CRKBD2__________________,
___________________CRKBD3__________________,
___________________CRKBD4__________________
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,  MINS,   EQL,  LBRC,  RBRC,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    SFT_CPS, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,    DOT,    DOT,BEPIS,\
  //|------+--- ---+------+------+------+------+------| |------+------+------+------+------+------+------|
                                   LGUI, LALT,ENT_LOW,  SPC_RSE, ARROW, FKEY\
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  EXLM,   EML,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,  UNDS,  PLUS,  LCBR,  RCBR,   PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    CAPS, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,  PLUS, XXXXX,   DOT,    QUES,  SLSH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LALT,ENT_LOW,  SPC_RSE, ARROW, FKEY\
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                 XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LALT,ENT_LOW,  SPC_RSE, ARROW, FKEY\
                              //`--------------------'  `--------------------'
  ),

  [_ARROW] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX,    UP, XXXXX, XXXXX, XXXXX,                  XXXXX,  PGDN,    UP,  PGUP, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,  LEFT,  DOWN, RIGHT, XXXXX, XXXXX,                  XXXXX,  LEFT,  DOWN,  RGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LALT,ENT_LOW,  SPC_RSE, ARROW, FKEY\
                              //`--------------------'  `--------------------'
   ),
   [_FKEY] = LAYOUT_kc( \
   //,-----------------------------------------.                ,-----------------------------------------.
       XXXXX,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10, XXXXX,\
   //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX,   F11,   F12, XXXXX,\
   //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
   //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    LGUI, LALT,ENT_LOW,  SPC_RSE, ARROW, FKEY\
                               //`--------------------'  `--------------------'
   )

};
