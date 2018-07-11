#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _DVORAK 0
#define _QWERTY 1
#define _GAMING 13
#define _LOWER 14
#define _RAISE 15
#define _ADJUST 16


enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  GAME,
  DVPR,
  QRTY,
  QUIT,
  LOWER,
  RAISE,
  ADJUST,
};

//Definitions of Different Keys Go Here
  #define KC_ KC_TRNS
  #define _______ KC_TRNS

  #define KC_LOWR LOWER
  #define KC_RASE RAISE
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
  #define KC_DVPR DF(_DVORAK)
  #define KC_GAME DF(_GAMING)
  #define KC_QRTY DF(_QWERTY)
  #define KC_QUIT LSFT(LALT(KC_Q))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// All custom layers should be placed below LOWER, RAISE, and ADJUST -- in that order.
// LOWER and RAISE have helpful keys on them. ADJUST is to adjust the keyboard's settings.
// I suppose that a pedestrian way of setting it up would be to make it as close to the old
// KB as possible and then slowly adjust things from there.

//DVORAK (Base Layer)
  [_DVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 7  , 5  , 3  , 1  , 9  ,                2  , 4  , 6  , 8  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB ,SCLN,COMM,DOT , P  , Y  ,                F  , G  , C  , R  , L  ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSFT, A  , O  , E  , U  , I  ,                D  , H  , T  , N  , S  ,RSFT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL,QUOT, Q  , J  , K  , X  ,HOME,     END , B  , M  , W  , V  , Z  ,SLSH,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,ENT ,         SPC ,RASE,LGUI
  //                  `----+----+----'        `----+----+----'
  ),

//QWERTY
    [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSFT, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,ENT ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL, Z  , X  , C  , V  , B  ,HOME,     END , N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,SPC ,         SPC ,RASE,LGUI
  //                  `----+----+----'        `----+----+----'
  ),

//GAMING
    [_GAMING] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     QUOT,TAB , Q  , W  , E  , R  ,                T  , Y  , U  , I  , O  , P ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     INS ,LSFT, A  , S  , D  , F  ,                G  , H  , J  , K  , L  ,SCLN,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     DEL ,LCTL, Z  , X  , C  , V  ,SPC,      ENT , B  , N  , M  ,COMM,DOT ,SLSH,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,LCTL,         SPC ,RASE,LGUI
  //                  `----+----+----'        `----+----+----'
  ),

//GAMELOWER -- For one handed gaming

//LOWER - MAYBE TRY AND MAKE IT RIGHT HANDED SINCE LOWER IS ON LT?
  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+---+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,LEFT, UP ,DOWN,RGHT,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

//RAISE - MAYBE TRY AND MAKE IT LEFT HANDED SINCE RAISE IS ON RT?
  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     QUIT,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

//ADJUST
     /*TOP ROW: Different custom defined layers, in order
      * 2ND ROW:
      * 3RD ROW:
      * 4TH ROW:
      * LTHUMBS:
      * RTHUMBS:
      */
  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     DVPR,QRTY,    ,GAME,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     BL_S,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,RST ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  )

};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    //After this point, it's all about switching layers
    case DVORAK:                                     //DVORAK here is the base layer
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case QRTY:
      if (record->event.pressed) {
      persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
   case GAME:                                      //GAME is now a keycode here
      if (record->event.pressed) {
      persistent_default_layer_set(1UL<<_GAMING);   //revert to Qwerty if we're on NSA/Windows
      }                                             //to play  V / I / D / E / O ~ G / A / M / E / S
      return false;
      break;
    case DVPR:
      if (record->event.pressed) {
      persistent_default_layer_set(1UL<<_DVORAK);   //Changes base layer to _DVORAK
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:                                    //Defines what happens when the RAISE key is pressed
      if (record->event.pressed) {                 //if they key is pressed
        layer_on(_RAISE);                          //toggle on the RAISE layer
        update_tri_layer(_LOWER, _RAISE, _ADJUST); //update our layers to check if the LOWER key is pressed
      }
      else {                                       //if the key is not pressed
        layer_off(_RAISE);                         //leave everything alone
        update_tri_layer(_LOWER, _RAISE, _ADJUST); //update the layers???
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {                 //RAISE + LOWER = ADJUST
        layer_on(_ADJUST);
        }
      else {
        layer_off(_ADJUST);                        //Releasing one of them goes to the other one
        }
      return false;
      break;
  }
  return true;
}
