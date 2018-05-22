#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

#include "edvorakjp.h"

extern edvorakjp_config_t edvorakjp_config;

enum custom_keycodes {
  KC_LOCK = NEW_SAFE_RANGE,
};

#define KC_ KC_TRNS

#define KC_TMB1 LGUI_T(KC_TAB)
#define KC_TMB2 LSFT_T(KC_SPC)
#define KC_TMB3 LOWER // act as LOWER when hold, as KC_LANG2(=English) when tapped
#define KC_TMB4 LCTL_T(KC_ESC)
#define KC_TMB5 RSFT_T(KC_DEL)
#define KC_TMB6 RAISE // act as RAISE when hold, as KC_LANG1(=Japanese) when tapped
#define KC_TMB7 RCTL_T(KC_BSPC)
#define KC_TMB8 RALT_T(KC_ENT)
#define KC_TMB9 LGUI(KC_TAB)

#define KC_RST  RESET
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_EDJP EDVORAK
#define KC_QWER QWERTY

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_EDVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV ,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LBRC,RBRC,COMM,DOT , P  , Y  ,                F  , G  , R  , W  , Q  ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     EQL , A  , O  , E  , I  , U  ,                D  , T  , N  , S  , M  ,MINS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     QUOT,SCLN, X  , C  , V  , Z  ,TMB4,     TMB5, B  , H  , J  , K  , L  ,SLSH,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                       TMB1,TMB2,TMB3,         TMB6,TMB7,TMB8
  //                  `----+----+----'        `----+----+----'
  ),

  [_EDVORAKJ1] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         , AI , OU , EI ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    , Y  ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,ANN ,ONN ,ENN ,INN ,UNN ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_EDVORAKJ2] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         , AI , OU , EI ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   , Y  ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,ANN ,ONN ,ENN ,INN ,UNN ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV ,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     EQL , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LBRC, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     RBRC, Z  , X  , C  , V  , B  ,    ,         , N  , M  ,COMM,DOT ,SLSH,BSLS,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,SLSH,ASTR,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,BTN4,WH_U,BTN5,    ,                   , 7  , 8  , 9  ,MINS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,WH_L,WH_D,WH_R,    ,                   , 4  , 5  , 6  ,PLUS,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,BTN1,BTN3,BTN2,    ,    ,         ,    , 1  , 2  , 3  ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             , 0  ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      F1 , F2 , F3 , F4 , F5 ,LCBR,               RCBR,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      F6 , F7 , F8 , F9 ,F10 ,LPRN,               RPRN,HOME,PGDN,PGUP,END ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     F11 ,F12 ,PSCR,SLCK,PAUS,LBRC,LOCK,         ,RBRC,LEFT,DOWN, UP ,RGHT,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                       TMB9,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,   ,EXTOFF,   ,                   ,EXTON,   ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,RST ,DBUG,RTOG,WIN ,    ,                   ,MAC ,QWER,EDJP,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  )
};

void matrix_init_keymap() {
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_LOCK:
      if (record->event.pressed) {
        if (edvorakjp_config.enable_kc_lang) {
          SEND_STRING( SS_LCTRL(SS_LSFT(SS_TAP(X_POWER))) );
        } else {
          SEND_STRING( SS_LGUI("L") );
        }
      }
      return false;
  }
  return true;
}

uint32_t layer_state_set_keymap(uint32_t state) {
  switch (biton32(state)) {
    case _EDVORAKJ1:
    case _EDVORAKJ2:
      // _EDVORAKJ1 & J2 are same colored
      rgblight_setrgb (0xFF, 0xFF, 0xFF);
      break;
    case _LOWER:
      rgblight_setrgb (0xFF, 0x00, 0x00);
      break;
    case _RAISE:
      rgblight_setrgb (0x00, 0x00, 0xFF);
      break;
    case _ADJUST:
      rgblight_setrgb (0x00, 0xFF, 0x00);
      break;
    default: //  for any other layers, or the default layer
      rgblight_mode(28);
      break;
  }
  return state;
}
