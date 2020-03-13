#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,LBRC,      RBRC, Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     TAB , A  , S  , D  , F  , G  , A,          A,  H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  , A,        SPC,  N  , M  ,COMM,DOT ,SLSH,ENT ,
  //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
     LCTL,LGUI,LALT,ADJT,LOWR,SPC,                 SPC, RASE,LEFT, UP ,DOWN,RIGHT
  //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
      GRAVE, 1  , 2  , 3  , 4  , 5  , A,           B,  6  , 7  , 8  , 9  , 0  ,DEL,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
       TAB , F1 , F2 , F3 , F4 , F5 , F6 ,         D,  Y  ,MINS, EQL,LBRC,RBRC,BSLS,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
       LSFT, F7 , F8 , F9 , F10, F11, F12,       SPC,  N  , M ,COMM,DOT ,SLSH,ENT ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
       LCTL,LGUI,LALT,ADJT,LOWR,SPC,                 SPC, RASE,LEFT, UP ,DOWN,RIGHT
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
       ESC , 1  , 2  , 3  , 4  , 5  , A,          B,  6  , 7  , 8  , 9  , 0  ,BSPC,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
       TAB , Q  , W  , E  , R  , T  , C ,         D,  Y  , U  , I  , O  , P  ,DEL ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
       LSFT, Z  , X  , C  , V  , B  , A,        SPC,  N  , M  ,COMM,DOT ,SLSH,ENT ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
       LCTL,LGUI,LALT,ADJT,LOWR,SPC,                 SPC, RASE,LEFT, UP ,DOWN,RIGHT
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
       ESC , F1 , F2 , F3 , F4 , F5 , F6,         F7,  F8, F9 ,F10 , F11, F12,BSPC,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
       TAB , Q  , W  , E  , R  , T  , C ,         D,  Y  , U  , I  , O  , P  ,DEL ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
       LSFT, Z  , X  , C  , V  , B  , A,        SPC,  N  , M  ,COMM,DOT ,SLSH,ENT ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
       LCTL,LGUI,LALT,ADJT,LOWR,SPC,                 SPC, RASE,LEFT, UP ,DOWN,RIGHT
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  )

};

   



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
