#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;


//Heavily modified keymap. Some features:
//Multiple layouts, I use dvorak as main.
//Nordic(swedish) signs
//Symbols, numpad, arrows/navigation reachable under the alpas via the layers
//Mirrored ctl, alt and shift to be able to use both hands when doing commands
//Gaming layer, qwerty with space on left half.

#define _QWERTY 2
#define _DVORAK 0
#define _COLEMAK 1
#define _WORKMAN 3
#define _GAMING 4
#define _NUMPAD 5
#define _LOWER 6
#define _RAISE 7

#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  COLEMAK,
  WORKMAN,
  GAMING,
  NUMPAD,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define KC_XXXX KC_NO

#define KC_Sw2 RALT(KC_2) // Nordic @
#define KC_Sw3 RALT(KC_3) // Nordic something
#define KC_Sw4 RALT(KC_4) // Nordic something
#define KC_Sw5 RALT(KC_5) // Nordic something
#define KC_Sw6 RALT(KC_6) // ...
#define KC_Sw7 RALT(KC_7)
#define KC_Sw8 RALT(KC_8)
#define KC_Sw9 RALT(KC_9)
#define KC_Sw0 RALT(KC_0)
#define KC_Tild RALT(KC_RBRC)
#define KC_Bsls RALT(KC_MINS)
#define KC_Bar RALT(KC_NUBS)
#define KC_Less S(KC_NUBS)
#define KC_CATDEL LCTL(LALT(KC_DEL)) // Ctrl alt del
#define KC_TSKMGR LCTL(S(KC_ESC)) // Ctrl shift esc
#define KC_NUMP TG(_NUMPAD)  // Toggle layer NUMPAD for use in LAYOUT_kc
#define KC_Close RALT(KC_F4) // Alt F4
#define KC_Great S(KC_NUBS)
#define KC_MEH1 MEH(KC_1)
#define KC_MEH2 MEH(KC_2)
#define KC_MEH3 MEH(KC_3)
#define KC_MEH4 MEH(KC_4)
#define KC_MEH5 MEH(KC_5)

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     DEL ,APP, VOLD,MUTE,VOLU,LGUI,               RGUI,MPRV,MPLY,MNXT,DOWN,ESC ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,LBRC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,NUMP,     ENT , N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,BSPC,         SPC ,RASE,LALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_GAMING] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,ESC ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,DEL,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,RCTL,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  , Y  ,     ENT , N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,SPC,         BSPC ,RASE,LALT
  //                  `----+----+----'        `----+----+----'
  ),

 [_DVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     DEL ,APP ,VOLD,MUTE,VOLU,LGUI,               RGUI,MPRV,MPLY,MNXT,DOWN,ESC ,
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TAB ,LBRC,QUOT,SCLN, P  , Y  ,                F  , G  , C  , R  , L  ,DEL,
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     LCTL, A  , O  , E  , U  , I  ,                D  , H  , T  , N  , S  ,RCTL,
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     LSFT,DOT , Q  , J  , K  , X  ,NUMP,     ENT , B  , M  , W  , V  , Z  ,RSFT,
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
                       LALT,LOWR,BSPC,         SPC ,RASE,LALT
  //                  `----+----+----'        `----+----+----'
  ),

 [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     DEL ,APP, VOLD,MUTE,VOLU,LGUI,               RGUI,MPRV,MPLY,MNXT,DOWN,ESC ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,LBRC,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,SCLN,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,NUMP,     ENT , K  , M  ,COMM, DOT,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,BSPC,         SPC ,RASE,LALT
  //                  `----+----+----'        `----+----+----'
  ),

[_WORKMAN] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     DEL ,APP, VOLD,MUTE,VOLU,LGUI,               RGUI,MPRV,MPLY,MNXT,DOWN,ESC ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , R  , W  , B  ,                J  , F  , U  , P  ,LBRC,SCLN,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , S  , H  , T  , G  ,                Y  , N  , E  , O  , I  ,RCTL,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , M  , C  , V  ,NUMP,     ENT , K  , L  ,QUOT, DOT,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,BSPC,         SPC ,RASE,LALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F1  , F2 , F3 , F4 , F5 , F6 ,                F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,MEH1,BTN2,MS_U,BTN1,CATDEL,             PIPE, P7 , P8 , P9 ,SLSH,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,MEH4,MS_L,MS_D,MS_R,TSKMGR,             COMM, P4 , P5 , P6 ,MINS,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,MEH5,ACL0,ACL1,ACL2,MEH3,    ,     PENT,DOT , P1 , P2 , P3 , P0 ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,BSPC,             , P0 ,NLCK
  //                  `----+----+----'        `----+----+----'
  ),


  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F1  , F2 , F3 , F4 , F5 , F6 ,                F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,CAPS,PGUP, UP ,PGDN, ESC,               RCBR,EXLM,ASTR,LPRN,UNDS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,HOME,LEFT,DOWN,RGHT, END,               RPRN,QUES,Sw8 ,Sw9 ,LABK,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         , ENT,    ,    ,    , DEL,    ,         ,RABK,NUBS,Sw7 ,Sw0 ,Great,   ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,   ,            ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TILD,EXLM,GRV ,EQL, DLR ,PERC,               Sw3 ,Sw5 ,Sw6 ,Sw0 ,RPRN,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,Bar ,Sw2 ,HASH, AT ,PERC,               PIPE, 7  , 8  , 9  ,PMNS,PSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,Bsls,Tild,SLSH,AMPR,BSLS,               COMM, 4  , 5  , 6  ,PPLS,PAST,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,PIPE,Sw4 ,PLUS,CIRC,TILD,    ,     PENT,DOT , 1  , 2  , 3  , 0  ,PEQL,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,DEL ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      GAMING , DVORAK,  WORKMAN, COLEMAK, QWERTY ,   KC_RST,                           _______, _______, _______, _______, KC_PWR,    RESET,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______,LGUI(KC_UP),_______,LALT(KC_F4),                       _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      _______, _______,LGUI(KC_LEFT),LGUI(KC_DOWN),LGUI(KC_RGHT),_______,             _______,  DEBUG  , RGB_HUD, RGB_SAD, RGB_VAD, BL_STEP,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,                  _______, _______, _______
  //                                `--------+--------+--------'                `--------+--------+--------'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
//          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
//          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_NUMPAD);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
//          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
//          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
//          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_GAMING);
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
