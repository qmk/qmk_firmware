#include QMK_KEYBOARD_H
#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"
// #include "pvinis.h"

extern keymap_config_t keymap_config;

#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

#ifdef AUDIO_ENABLE
  //#define STARTUP_SONG SONG(SONIC_RING)
#endif

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16
// #define _TESSS 8

enum custom_keycaodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  TESSS,
  SSP,
  SSP1,
  SSP2,
  SSP3,
  SSP4,
};

#define KC_  KC_TRNS // empty keys are transparent
#define ____ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST  RESET
#define KC_SSP  SSP
#define KC_SSP1  SSP1
#define KC_SSP2  SSP2
#define KC_SSP3  SSP3
#define KC_SSP4  SSP4

#ifdef AUDIO_ENABLE
float tone_sonic[][2] = SONG(IN_LIKE_FLINT);
float tone_1[][2] = SONG(QWERTY_SOUND);
float tone_2[][2] = SONG(OLD_SPICE);
float tone_3[][2] = SONG(OVERWATCH_THEME);
float tone_4[][2] = SONG(QWERTY_SOUND);
#endif

#define KC_ESCC MT(MOD_LCTL, KC_ESC) // esc on tap, control on hold
#define KC_LBRK LSFT(KC_LBRC)
#define KC_RBRK LSFT(KC_RBRC)

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


// ,-----------------------------.              ,-----------------------------.
// |    |    |    |    |    |    |              |    |    |    |    |    |    |
// |----+----+----+----+----+----|              |----+----+----+----+----+----|
// |    |    |    |    |    |    |              |    |    |    |    |    |    |
// |----+----+----+----x----x----|              |----x----x----+----+----+----|
// |    |    |    |    |    |    |              |    |    |    |    |    |    |
// |----+----+----+----x----x----+----.    ,----|----x----x----+----+----+----|
// |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
// `-------------------+----+----+----/    \----+----+----+-------------------'
//                    |    |    |    |      |    |    |    |
//                    `----+---------'      `--------------'
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QUERTY] = LAYOUT_wrapper(
     KC_GRV  , _________NUMBERS_L__________ ,                       _________NUMBERS_R_______ , KC_QUOT ,
     KC_TAB  , _________QWERTY_L1__________ ,                       _________QWERTY_R1_______ , KC_DEL  ,
     KC_ESCC , _________QWERTY_L2__________ ,                       _________QWERTY_R2_______ , KC_ENT  ,
     KC_LSFT , _________QWERTY_L3__________ , KC_HOME ,    KC_END , _________QWERTY_R3_______ , KC_RSFT ,
                          KC_LGUI , KC_LOWR , KC_BSPC ,    KC_SPC , KC_RASE , KC_LALT ,
  ),


  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----x----x----|              |----x----x----+----+----+----|
     ESCC,   4,   4,   9, F  , G  ,                H  , J  , K  , L  ,SCLN,ENT ,
  //|----+----+----+----x----x----+----.    ,----|----x----x----+----+----+----|
       A ,SSP,SSP1,SSP2,SSP3,SSP4,HOME,     END , N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+---+----/    \----+----+----+----+----+----+----'
                       LGUI,LOWR,BSPC,         SPC ,RASE,LALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RST ,SSP , 7  ,    ,LBRK,RBRK,               SLSH, 7  , 8  , 9  ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,PLUS,LPRN,RPRN,               EQL , 4  , 5  , 6  ,    ,PIPE,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     BL_S,    ,    ,MINS,LBRC,RBRC,    ,         ,ASTR, 1  , 2  , 3  ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    , 0
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     AMPR,EXLM, AT ,HASH,DLR ,PERC,               MUTE,HOME, UP ,END ,RPRN,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LPRN,MPRV,MNXT,CIRC,PGUP,UNDS,               VOLU,LEFT,DOWN,RGHT,ASTR,BSLS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     PLUS,MSTP,MPLY,EQL ,PGDN,MINS,    ,         ,VOLD,MRWD,MPLY,MFFD,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RTOG,RMOD,RHUI,RSAI,RVAI,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,DBUG,RHUD,RSAD,RVAD,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     BL_S,RST ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  // [_TESSS] = LAYOUT(
  // //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
  //        ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  // //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //    ,,,,,    ,                   ,    ,    ,    ,    ,    ,
  // //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //        ,,,,,    ,                   ,    ,    ,    ,    ,    ,
  // //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  //    MUV_DE,MUV_IN,MU_ON,MU_OFF,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  // //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
  //                          ,    ,    ,             ,    ,
  // //                  `----+----+----'        `----+----+----'
  // )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
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
    case SSP:
      #ifdef AUDIO_ENABLE
      if (record->event.pressed) {
        PLAY_SONG(tone_sonic);
      }
      #endif
      return false;
    case SSP1:
      #ifdef AUDIO_ENABLE
      if (record->event.pressed) {
        PLAY_SONG(tone_1);
      }
      #endif
      return false;
    case SSP2:
      #ifdef AUDIO_ENABLE
      if (record->event.pressed) {
        PLAY_SONG(tone_2);
      }
      #endif
      return false;
    case SSP3:
      #ifdef AUDIO_ENABLE
      if (record->event.pressed) {
        PLAY_SONG(tone_3);
      }
      #endif
      return false;
    case SSP4:
      #ifdef AUDIO_ENABLE
      if (record->event.pressed) {
        PLAY_SONG(tone_4);
      }
      #endif
      return false;
  }
  return true;
}
