#include "chocopad.h"

#define _BASE 0
#define _FN1 1
#define _FN2 2

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_X1 MO(_FN1)
#define KC_X2 MO(_FN2)
#define KC_RST RESET
#define KC_BSTP BL_STEP
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = KC_KEYMAP(
  //,----+----+----+----.
     PGUP,HOME, UP ,END ,
  //|----+----+----+----|
     PGDN,LEFT,DOWN,RGHT,
  //|----+----+----+----|
      X2 ,VOLU,MPLY,MPRV,
  //|----+----+----+----|
      X1 ,VOLD,MUTE,MNXT
  //`----+----+----+----'
  ),

  [_FN1] = KC_KEYMAP(
  //,----+----+----+----.
     ESC , P7 , P8 , P9 ,
  //|----+----+----+----|
     TAB , P4 , P5 , P6 ,
  //|----+----+----+----|
     ENT , P1 , P2 , P3 ,
  //|----+----+----+----|
         , P0 , P0 ,DOT 
  //`----+----+----+----'
  ),

  [_FN2] = KC_KEYMAP(
  //,----+----+----+----.
     RTOG,RHUI,RSAI,RVAI,
  //|----+----+----+----|
     RMOD,RHUD,RSAD,RVAD,
  //|----+----+----+----|
         ,    ,    ,RST ,
  //|----+----+----+----|
     BSTP,    ,    ,    
  //`----+----+----+----'
  )

};
