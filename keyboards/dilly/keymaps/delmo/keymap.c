#include QMK_KEYBOARD_H

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
//#define KC_ASFT MT(MOD_LSFT, KC_A)
#define KC_F_L3 LT(_FN3, KC_F)
#define KC_ZCTL MT(MOD_LCTL, KC_Z)
#define KC_XALT MT(MOD_LALT, KC_X)
//#define KC_CGUI MT(MOD_LGUI, KC_C)
#define KC_V_L4 LT(_FN4, KC_V)
#define KC_SPL2 LT(_FN2, KC_SPC)
#define KC_B_L1 LT(_FN1, KC_B)
#define KC_N_L5 LT(_FN5, KC_N)
//#define KC_MALT MT(MOD_RALT, KC_M)
//#define KC_BSCT MT(MOD_RCTL, KC_BSPC)
#define KC_ENTS MT(MOD_RSFT, KC_ENT)
#define KC_BSCS MT(MOD_RSFT, KC_BSPC)

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

  [_BASE] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----.
      Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,
  //|----+----+----+----+----+----+----+----+----+----|
      A  , S  , D  ,F_L3, G  , H  , J  , K  , L  ,BSCS,
  //|----+----+----+----+----+----+----+----+----+----|
     ZCTL,XALT,C   ,V_L4,B_L1,SPL2,N_L5,M   ,DOT ,ENTS
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN1] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----.
      1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,
  //|----+----+----+----+----+----+----+----+----+----|
      F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 ,F10 ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,BSPC,    ,    ,    ,CAPS
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN2] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----.
     EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,
  //|----+----+----+----+----+----+----+----+----+----|
     F11 ,F12 ,    ,    ,    ,    ,    ,    ,    ,GRV ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,DEL ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN3] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----.
     ESC ,    ,    ,    ,    ,MINS,EQL ,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----+----+----+----+----|
     TAB ,    ,    ,    ,    ,COMM,DOT ,SLSH,SCLN,QUOT,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,BSPC,    ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN4] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,UNDS,PLUS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----+----+----+----+----|
     TAB ,    ,    ,    ,    , LT , GT ,QUES,COLN,DQUO,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,GUIC,    ,BSPC,    ,HOME,PGDN,PGUP,END
  //`----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN5] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----.
     RTOG,RMOD,    ,RST ,RHUI,RSAI,RVAI,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----|
         ,    ,DBUG,    ,RHUD,RSAD,RVAD,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----|
     BL_S,    ,GUIC,    ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----+----+----+----'
  )

};