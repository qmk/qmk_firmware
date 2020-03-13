#include QMK_KEYBOARD_H

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
#define KC_FN1 LT(_FN1, KC_NO)
#define KC_FN2 LT(_FN2, KC_NO)
#define KC_SPFN LT(_FN1, KC_SPACE)
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
  [_BASE] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    TAB , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  , DEL,BSPC,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
    ESC  , A  , S  , D  , F  , G  , H  , J  , K  , L  ,QUOT,  SCLN  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
    LSFT   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH, PGUP ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
    LCTL ,LALT,  FN1,   ,ENTER    ,  SPACE , FN2 , HOME, END , PGDN
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
  ),

  [_FN1] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    GRV , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,    ,    ,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
     DEL , F1  ,F2 , F3 , F4 , F5 , F6 ,MINS, EQL,LBRC,RBRC,  BSLS  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           , F7 , F8 , F9 , F10, F11, F12,    ,    ,    , UP ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,    ,         ,        ,RGUI,LEFT ,DOWN ,RIGHT
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
  ),

  [_FN2] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    TILD,EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,    ,    ,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
     DEL ,RHUI,RSAI,RVAI,    ,    ,    ,UNDS,PLUS,LCBR,RCBR,  PIPE  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           ,RHUD,RSAD,RVAD,    ,    ,VOLU,VOLD,    ,    , UP ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,RTOG,RMOD ,    ,        ,        ,     , LEFT, DOWN, RIGHT
 //`-----+----+-----+-------------|--------+-----+-----+-----+------'
  )

};
