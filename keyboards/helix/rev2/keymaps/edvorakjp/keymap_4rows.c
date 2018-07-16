#include "helix.h"
#include "keymap_xrows.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_EDVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     LBRC,RBRC,COMM,DOT , P  , Y  ,                F  , G  , R  , W  , Q  ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     EQL , A  , O  , E  , I  , U  ,                D  , T  , N  , S  , M  ,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     QUOT,SCLN, X  , C  , V  , Z  ,                B  , H  , J  , K  , L  ,SLSH,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LEFT,DOWN, UP ,RGHT,TMB1,TMB2,TMB3,     TMB6,TMB7,TMB8,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
  ),

  [_EDVORAKJ1] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , AI , OU , EI ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    , Y  ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,ANN ,ONN ,ENN ,INN ,UNN ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
  ),

  [_EDVORAKJ2] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , AI , OU , EI ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   , Y  ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,ANN ,ONN ,ENN ,INN ,UNN ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
  ),

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     EQL , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LBRC, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RBRC, Z  , X  , C  , V  , B  ,                N  , M  ,COMM,DOT ,SLSH,BSLS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
      F1 , F2 , F3 , F4 , F5 ,LCBR,               RCBR, 7  , 8  , 9  ,MINS,SLSH,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      F6 , F7 , F8 , F9 ,F10 ,LPRN,               RPRN, 4  , 5  , 6  ,PLUS,ASTR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     F11 ,F12 ,PSCR,SLCK,PAUS,LBRC,               RBRC, 1  , 2  , 3  , NO , NO ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     HOME,PGDN,PGUP,END ,    ,    ,    ,         ,ESC , 0  ,HOME,PGDN,PGUP,END
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
      F1 , F2 , F3 , F4 , F5 , F6 ,                F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN, NO ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  , NO ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     HOME,PGDN,PGUP,END ,TMB9,ESC ,    ,         ,    ,    ,HOME,PGDN,PGUP,END
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,   ,EXTOFF,   ,                   ,EXTON,   ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,RST ,DBUG,RTOG,WIN ,    ,                   ,MAC ,QWER,EDJP,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
  )
};
