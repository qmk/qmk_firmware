#include QMK_KEYBOARD_H
#include "rhruiz.h"

#define KC_ KC_TRNS
#define KC__FN1 MO(_FN1)
#define KC__FN2 MO(_FN2)
#define KC__CFG MO(_CFG)
#define KC_CFG1 LT(_CFG, KC_SPC)
#define KC_CFG2 LT(_CFG, KC_BSPC)

#define KC_RST RESET
#define KC__VUP KC__VOLUP
#define KC__VDN KC__VOLDOWN

#define KC_SPCFN1 SPCFN1
#define KC_BKSFN2 BKSFN2
#define KC_CESC CTRLESC

#define KC__M DF(_MOUSE)
#define KC__BL DF(_BL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* template
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
        ,    ,    ,    ,    ,    ,    ,     ,   ,    ,    ,    ,    ,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,        ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
         ,    ,     , ,           ,        ,     ,     ,     ,
 //`-----+----+-----+-------------+--------+-----+-----+-----+------'
    */
  [_BL] = LAYOUT_kc(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
    TAB , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,LBRC,RBRC,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
    CESC , A  , S  , D  , F  , G  , H  , J  , K  , L  ,SCLN, ENTER  ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
    LSFT   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH, RSFT ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
    _FN2 ,LALT,LGUI , ,  SPCFN1   , BKSFN2 , RGUI, RALT, _FN1, _M
 //`-----+----+-----+-------------+--------+-----+-----+-----+------'
  ),

  [_VIM_EMACS] = LAYOUT_kc(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
        ,    ,    ,    ,    ,    ,    ,     ,   ,    ,    ,    ,    ,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
         ,    ,    ,    ,    ,    ,LEFT,DOWN,UP  ,RGHT,    ,        ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
         ,    ,     , ,           ,        ,     ,     ,     ,
 //`-----+----+-----+-------------+--------+-----+-----+-----+------'
  ),

  [_MOUSE] = LAYOUT_kc(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
        ,BTN1,MS_U,BTN2,WH_D,    ,    ,     ,   ,    ,    ,    ,    ,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
         ,MS_L,MS_D,MS_R,WH_U ,    ,    ,    ,    ,    ,    ,        ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
         ,    ,     , ,           ,        ,     ,     ,     , _BL
 //`-----+----+-----+-------------+--------+-----+-----+-----+------'
  ),

  [_KEY_OVERRIDE] = LAYOUT_kc(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
        ,    ,    ,    ,    ,    ,    ,     ,   ,    ,    ,    ,    ,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,        ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
         ,    ,     , ,           ,        ,     ,     ,     ,
 //`-----+----+-----+-------------+--------+-----+-----+-----+------'
  ),

  [_FN1] = LAYOUT_kc(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
    GRV , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,MINS,EQL ,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,QUOT,   BSLS ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
         ,    ,     , ,           ,  CFG2  ,     ,     ,_CFG ,
 //`-----+----+-----+-------------+--------+-----+-----+-----+------'
  ),

  [_FN2] = LAYOUT_kc(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
    TILD,EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,UNDS,PLUS,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,DQUO,   PIPE ,
 //|-----`----`----`----`----`----`----`----`----`----`----`--------+
           ,    ,    ,    ,    ,    ,    ,    , LT , GT ,QUES,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
    _CFG,     ,     , ,   CFG1    ,        ,     ,     ,     ,
 //`-----+----+-----+-------------+--------+-----+-----+-----+------'
  ),

  [_CFG] = LAYOUT_kc(
 //,----+----+----+----+----+----+----+----+----+----+----+----+----.
        , F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 , F10, F11, F12,
 //|----`----`----`----`----`----`----`----`----`----`----`----`----+
           ,_VUP,_VDN,MUTE,EJCT,    ,HOME,PGDN,PGUP,END ,    ,  RST ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----`----`----`----`----`----`------+
         ,    ,     , ,           ,        ,     ,     ,     ,
 //`-----+----+-----+-------------+--------+-----+-----+-----+------'
  )
};

void matrix_init_user(void) {
  setPinOutput(B0);
  writePinHigh(B0);

  setPinOutput(D5);
  writePinHigh(D5);
}

void rhruiz_update_layer_colors() {
  switch(biton32(layer_state))  {
    case _FN1:
      writePinHigh(B0);
      writePinLow(D5);
      break;

    case _FN2:
      writePinLow(B0);
      writePinHigh(D5);
      break;

    case _CFG:
      writePinLow(D5);
      writePinLow(B0);
      break;

    default:
      writePinHigh(B0);
      writePinHigh(D5);
      break;
  }
}

void matrix_scan_user(void) {
  rhruiz_update_layer_colors();
}

uint32_t layer_state_set_user(uint32_t state) {
  return rhruiz_layer_state_set_user(state);
}
