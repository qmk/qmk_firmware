#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _COLEMAK 0
#define _QWERTY 1
#define _NUMPAD 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  NUMPAD,
  LOWER,
  RAISE,
  ADJUST,
};

/* Fn keys */

enum {

  F_SFT = 0,
  F_ALT,
  F_CTRL,
  F_NUMPAD
// F_LOWER,
//  F_RAISE,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define KC_XXXX KC_NO

#define KC_CMK COLEMAK
#define KC_QWE QWERTY
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_QRAS QRAISE
#define KC_ADJT ADJUST
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
//#define KC_CATDEL LCTL(LALT(KC_DEL)) // Ctrl alt del
#define KC_CPY LCTL(KC_C)
#define KC_PST LCTL(KC_V)
#define KC_SELA LCTL(KC_A)
#define KC_UDO LCTL(KC_Z)
#define KC_CUT LCTL(KC_X)
#define KC_SVE LCTL(KC_S)
#define KC_OSH F(F_SFT)
#define KC_OCTL F(F_CTRL)
#define KC_NUMP F(F_NUMPAD)
#define KC_SHESC MT(MOD_LSFT,KC_ESC)
#define KC_SHENT MT(MOD_RSFT,KC_ENT)
//#define KC_NUMP TG(_NUMPAD)  // Toggle layer NUMPAD for use in KC_keymaps
//#define KC_RST RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Colemak Mod-DH is used. https://colemakmods.github.io/mod-dh/
  [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
     TAB , Q  , W  , F  , P  , B  ,LPRN,      RPRN, J  , L  , U  , Y  ,SCLN,BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     BSPC, A  , R  , S  , T  , G  ,EQL ,      MINS, K  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
    SHESC, Z  , X  , C  , D  , V  ,NUMP,       ENT, M  , H  ,COMM,DOT ,SLSH,SHENT,
  //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
     OCTL,LALT,LGUI,DEL ,LOWR, SPC,                OSH, RASE,LEFT,RIGHT,RALT,RCTL
  //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,LBRC,      RBRC, Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     TAB , A  , S  , D  , F  , G  ,LPRN,      RPRN, H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,    ,          , N  , M  ,COMM,DOT ,SLSH,ENT ,
  //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
     LCTL,LGUI,LALT,DEL ,    , SPC,                SPC ,    ,LEFT,DOWN, UP ,RIGHT
  //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
           ,    ,    ,    ,    ,    ,    ,          ,ASTR, P7 , P8 , P9 ,SLSH,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,    ,          ,PIPE, P4 , P5 , P6 ,MINS,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,    ,          ,COMM, P1 , P2 , P3 ,PLUS,    ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,                    , P0 ,NLCK,    ,    ,    
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
         ,XXXX,XXXX,XXXX,XXXX,CAPS,    ,          ,PGUP,HOME, UP ,END ,DEL ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,SELA,LALT,LSFT,LCTL,SVE ,    ,          ,PGDN,LEFT,DOWN,RGHT,BSPC,INS ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,UDO ,CUT ,CPY ,PST ,XXXX,    ,          ,XXXX,XXXX,COMM,DOT ,SLSH,    ,
  //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,    
  //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
           ,AMPR,PERC,HASH,EXLM,LPRN,    ,          ,ASTR,RPRN, AT ,DLR ,CIRC,BSPC,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           , 7  , 5  , 3  , 1  , 9  ,LBRC,      RBRC,  8 , 0  , 2  , 4  , 6  ,BSLS,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           , GRV,TILD,XXXX,EQL ,PLUS,    ,          ,UNDS,MINS,COMM,DOT ,SLSH,ENT ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,    
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),


  [_ADJUST] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
           , F1 , F2 , F3 , F4 , F5 , F6,         F7,  F8, F9 ,F10 , F11, F12,BSPC,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,    ,          ,    , CMK,QWE ,    ,    ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,                    ,    ,    ,VOLD,VOLU,MUTE
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ) 

};

const uint16_t PROGMEM fn_actions[] = {
  [F_SFT]  = ACTION_MODS_ONESHOT (MOD_LSFT)
  ,[F_ALT]  = ACTION_MODS_ONESHOT (MOD_LALT)
  ,[F_CTRL] = ACTION_MODS_ONESHOT (MOD_LCTL)
  ,[F_NUMPAD] = ACTION_LAYER_TAP_TOGGLE(_NUMPAD)
// ,[F_LOWER] = ACTION_LAYER_TAP_TOGGLE(LOWER)                // FN1 - Momentary Layer 1 (Lower)    
// ,[F_RAISE] = ACTION_LAYER_TAP_TOGGLE(RAISE)                // FN2 - Momentary Layer 2 (Raise)
};   



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);

      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
