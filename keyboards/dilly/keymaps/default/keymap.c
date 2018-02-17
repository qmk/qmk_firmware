#include "dilly.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define _BASE 0
#define _FN1 1
#define _FN2 2
#define _FN3 3
#define _FN4 4
#define _FN5 5

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_ZCTL MT(MOD_LCTL, KC_Z)
#define KC_XALT MT(MOD_LALT, KC_X)
#define KC_C_L3 LT(_FN3, KC_C)
#define KC_V_L4 LT(_FN4, KC_V)
#define KC_SPL2 LT(_FN2, KC_SPC)
#define KC_BSL1 LT(_FN1, KC_BSPC)
#define KC_B_L5 LT(_FN5, KC_B)
#define KC_NALT MT(MOD_RALT, KC_N)
#define KC_MCTL MT(MOD_RCTL, KC_M)
#define KC_ENTS MT(MOD_RSFT, KC_ENT)

#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
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
  //,----+----+----+----+----+----+----+----+----+----.
      Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,
  //|----+----+----+----+----+----+----+----+----+----|
      A  , S  , D  , F  , G  , H  , J  , K  , L  ,ESC ,
  //|----+----+----+----+----+----+----+----+----+----|
     ZCTL,XALT,C_L3,V_L4,SPL2,BSL1,B_L5,NALT,MCTL,ENTS
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN1] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
      1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,
  //|----+----+----+----+----+----+----+----+----+----|
      F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 ,F10 ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,DEL ,    ,    ,    ,    
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN2] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
     EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,
  //|----+----+----+----+----+----+----+----+----+----|
     F11 ,F12 ,    ,    ,    ,    ,    ,    ,    ,GRV ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,    ,    ,    
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN3] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,MINS,EQL ,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----+----+----+----+----|
     TAB ,    ,    ,    ,    ,COMM,DOT ,SLSH,SCLN,QUOT,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN4] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,UNDS,PLUS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----+----+----+----+----|
     TAB ,    ,    ,    ,    , LT , GT ,QUES,COLN,DQUO,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,HOME,PGDN,PGUP,END 
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN5] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
     RTOG,RMOD,    ,RST ,RHUI,RSAI,RVAI,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,DBUG,    ,RHUD,RSAD,RVAD,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----|
     BL_S,    ,    ,    ,    ,    ,    ,    ,    ,    
  //`----+----+----+----+----+----+----+----+----+----'
  )

};
