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

// Tap-Hold keys
#define KC_ASFT MT(MOD_LSFT, KC_A)
#define KC_F_L3 LT(_FN3, KC_F)
#define KC_ZCTL MT(MOD_LCTL, KC_Z)
#define KC_XALT MT(MOD_LALT, KC_X)
#define KC_CGUI MT(MOD_LGUI, KC_C)
#define KC_V_L4 LT(_FN4, KC_V)
#define KC_SPL2 LT(_FN2, KC_SPC)
#define KC_B_L1 LT(_FN1, KC_B)
#define KC_N_L5 LT(_FN5, KC_N)
#define KC_MALT MT(MOD_RALT, KC_M)
#define KC_BSCT MT(MOD_RCTL, KC_BSPC)
#define KC_ENTS MT(MOD_RSFT, KC_ENT)
#define KC_ESCS MT(MOD_RSFT, KC_ESC)

#define KC_GUIC LGUI(KC_C)

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
     ASFT, S  , D  ,F_L3, G  , H  , J  , K  , L  ,ESCS,
  //|----+----+----+----+----+----+----+----+----+----|
     ZCTL,XALT,CGUI,V_L4,SPL2,B_L1,N_L5,MALT,BSCT,ENTS
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN1] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
      1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,
  //|----+----+----+----+----+----+----+----+----+----|
      F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 ,F10 ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,BSPC,    ,    ,    ,    ,    
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN2] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
     EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,
  //|----+----+----+----+----+----+----+----+----+----|
     F11 ,F12 ,    ,    ,    ,    ,    ,    ,    ,GRV ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,DEL ,    ,    ,    ,    
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN3] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,MINS,EQL ,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----+----+----+----+----|
     TAB ,    ,    ,    ,    ,COMM,DOT ,SLSH,SCLN,QUOT,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,BSPC,    ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN4] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,UNDS,PLUS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----+----+----+----+----|
     TAB ,    ,    ,    ,    , LT , GT ,QUES,COLN,DQUO,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,GUIC,    ,BSPC,    ,HOME,PGDN,PGUP,END 
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN5] = KC_KEYMAP(
  //,----+----+----+----+----+----+----+----+----+----.
     RTOG,RMOD,    ,RST ,RHUI,RSAI,RVAI,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,DBUG,    ,RHUD,RSAD,RVAD,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----|
     BL_S,    ,GUIC,    ,    ,    ,    ,    ,    ,    
  //`----+----+----+----+----+----+----+----+----+----'
  )

};
