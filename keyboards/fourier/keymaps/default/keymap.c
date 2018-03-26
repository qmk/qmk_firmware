#include "fourier.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1
#define _FN2 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
<<<<<<< HEAD
#define KC_FN1 LT(_FN2, KC_SPACE)
#define KC_FN2 MO(_FN2)
#define KC_SPFN LT(_FN1, KC_SPACE)
=======
#define KC_FN1 MO(_FN1)
#define KC_FN2 MO(_FN2)
#define KC_SPFN1 LT(_FN1, KC_SPACE)
#define KC_SPFN2 LT(_FN2, KC_SPACE)
#define KC_BSFN1 LT(_FN1, KC_BSPC)
#define KC_BSFN2 LT(_FN2, KC_BSPC)
>>>>>>> 19a1fbaca2137a9d4cd529e363039a612a4f941d
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
<<<<<<< HEAD
    TAB , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,DEL ,BSPC,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
    ESC  , A  , S  , D  , F  , G  , H  , J  , K  , L  ,SCLN, ENTER  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
    LSFT   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH, RSFT ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
    LCTL ,LGUI,LALT ,    SPFN     ,  FN1  ,RALT ,MENU , FN2 , RCTL 
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
=======
    ESC , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,DEL ,BSPC,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
    TAB  , A  , S  , D  , F  , G  , H  , J  , K  , L  ,QUOT, ENTER  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
    LSFT   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH, RSFT ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
    LCTL ,LALT,LGUI ,FN1 , SPFN1  ,  BSFN2 ,RGUI ,RALT , FN2 , RCTL 
 //`-----+----+-----+----+--------|--------+-----+-----+-----+------'
>>>>>>> 19a1fbaca2137a9d4cd529e363039a612a4f941d
  ),

  [_FN1] = KC_KEYMAP(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    GRV , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,MINS,EQL ,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
<<<<<<< HEAD
         , A  , S  , D  , F  , G  , H  , 4  , 5  , 6  ,SCLN, ENTER  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           , Z  , X  , C  , V  , B  , N  , 1  , 2  , 3  ,SLSH, RSFT ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,             ,   0    ,     ,     ,     ,      
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
=======
    RST  ,RHUI,RSAI,RVAI,VOLU,LBRC,RBRC, 4  , 5  , 6  ,SCLN,        ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
    RMOD   ,RHUD,RSAD,RVAD,VOLD,LCBR,RCBR, 1  , 2  , 3  , UP ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
    RTOG ,    ,     ,    ,        ,  DEL   ,  0  ,LEFT ,DOWN , RGHT 
 //`-----+----+-----+----+--------|--------+-----+-----+-----+------'
>>>>>>> 19a1fbaca2137a9d4cd529e363039a612a4f941d
  ),

  [_FN2] = KC_KEYMAP(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    TILD,EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,UNDS,PLUS,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
<<<<<<< HEAD
    RST  ,RHUI,RSAI,RVAI,    ,    ,    ,    ,    ,    ,    ,        ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           ,RHUD,RSAD,RVAD,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,RTOG,RMOD ,             ,        ,     ,     ,     ,      
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
=======
         ,    ,    ,INS ,PGUP,HOME,    ,    ,    ,    ,COLN,        ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           ,    ,    ,DEL ,PGDN,END ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,    ,  DEL   ,        ,     ,     ,     ,      
 //`-----+----+-----+----+--------|--------+-----+-----+-----+------'
>>>>>>> 19a1fbaca2137a9d4cd529e363039a612a4f941d
  )

};
