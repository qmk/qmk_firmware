#include "laplace.h"

#define _BASE 0
#define _FN1 1
#define _FN2 2

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_FN1 MO(_FN1)
#define KC_FN2 MO(_FN2)
#define KC_SPFN1 LT(_FN1, KC_SPACE)
#define KC_SPFN2 LT(_FN2, KC_SPACE)
#define KC_BSFN1 LT(_FN1, KC_BSPC)
#define KC_BSFN2 LT(_FN2, KC_BSPC)
#define KC_RST RESET
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
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    ESC , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,DEL ,BSPC,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
    TAB  , A  , S  , D  , F  , G  , H  , J  , K  , L  ,QUOT, ENTER  ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------|
    LSFT   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH, RSFT ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------|
    LCTL ,LALT,LGUI ,FN1 , SPFN1  ,  BSFN2 ,RGUI ,RALT , FN2 , RCTL 
 //`-----+----+-----+----+--------`--------+-----+-----+-----+------'
  ),

  [_FN1] = KC_KEYMAP(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
    GRV , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,MINS,EQL ,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
    RST  ,RHUI,RSAI,RVAI,VOLU,LBRC,RBRC, 4  , 5  , 6  ,SCLN,        ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
    RMOD   ,RHUD,RSAD,RVAD,VOLD,LCBR,RCBR, 1  , 2  , 3  , UP ,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
    RTOG ,    ,     ,    ,        ,  DEL   ,  0  ,LEFT ,DOWN , RGHT 
 //`-----+----+-----+----+--------+--------+-----+-----+-----+------'
  ),

  [_FN2] = KC_KEYMAP(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
    TILD,EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,UNDS,PLUS,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
         ,    ,    ,INS ,PGUP,HOME,    ,    ,    ,    ,COLN,        ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
           ,    ,    ,DEL ,PGDN,END ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
         ,    ,     ,    ,  DEL   ,        ,     ,     ,     ,      
 //`-----+----+-----+----+--------+--------+-----+-----+-----+------'
  )
};
