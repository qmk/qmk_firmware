#include QMK_KEYBOARD_H
#include "mtdjr.h"

extern keymap_config_t keymap_config;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc (
// ,-----------------------------.  .-----------------------------.
    GESC,  1 ,  2 ,  3 ,  4 ,  5 ,     6 ,  7 ,  8 ,  9 ,  0 ,BSPC,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
     TAB,  Q ,  W ,  E ,  R ,  T ,     Y ,  U ,  I ,  O ,  P ,QUOT,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    RASE,  A ,  S ,  D ,  F ,  G ,     H ,  J ,  K ,  L ,SCLN, ENT,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    LSFT,  Z ,  X ,  C ,  V ,  B ,     N ,  M ,COMM, DOT,SLSH,xxxx,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    LOWR,LCTL,LALT,LGUI, SPC, SPC,    SPC, SPC,LEFT,DOWN, UP ,RGHT
// '-----------------------------'  '-----------------------------'
),

  [_LOWER] = LAYOUT_kc(
// ,-----------------------------.  .-----------------------------.
    TILD,xxxx,xxxx,xxxx,xxxx,xxxx,   xxxx,xxxx,xxxx,UNDS,PLUS, DEL,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,   xxxx,xxxx,xxxx,LBRC,RBRC,BSLS,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
        ,xxxx,xxxx,xxxx,xxxx,xxxx,   xxxx,xxxx,xxxx,xxxx,xxxx,    ,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    xxxx,UNDO, CUT,XCPY,XINS,xxxx,   xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
        ,    ,    ,    ,    ,    ,       ,    ,MNXT,VOLD,VOLU,MPLY
// '-----------------------------'  '-----------------------------'
),

  [_RAISE] = LAYOUT_kc(
// ,-----------------------------.  .-----------------------------.
    xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,   xxxx,xxxx,xxxx,MINS, EQL,    ,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,   xxxx,xxxx,xxxx,LCBR,RCBR,PIPE,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
        ,xxxx,xxxx,xxxx,xxxx,xxxx,   xxxx,xxxx,xxxx,xxxx,xxxx,    ,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,   xxxx,xxxx,xxxx,xxxx,xxxx,xxxx,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
        ,    ,    ,    ,    ,    ,       ,    ,MNXT,VOLD,VOLU,MPLY
// '-----------------------------'  '-----------------------------'
),

  [_ADJUST] =  LAYOUT_kc(
// ,-----------------------------.  .-----------------------------.
    xxxx,ROOT,PPLY,PSEF,xxxx,xxxx,    F1 , F2 , F3 , F4 , F5 , F6 ,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    xxxx,xxxx,xxxx,xxxx, RST,xxxx,    F7 , F8 , F9 , F10, F11, F12,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
        , RGB,RHUI,RSAI,RVAI, MOD,   xxxx,xxxx,xxxx,xxxx,xxxx,    ,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
    xxxx,RBTH,RHUD,RSAD,RVAD,RMOD,   xxxx,xxxx,xxxx,xxxx,xxxx, BLB,
// |----+----+----+----+----+----|  |----+----+----+----+----+----|
        ,xxxx,xxxx,xxxx,    ,    ,       ,    ,BLOF, BLD, BLI,BLON
// '-----------------------------'  '-----------------------------'
)

};
