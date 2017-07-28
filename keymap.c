/* Check on proper usage of MT and LT.
   What should happen is if you tap the Fn key you get an exclamation point
   If you tap the Num key you should get an equals sign
   If either one is held they take you to a new layer
   
   Set up macros over shift keys for custom keys 
  
   Make sure that switching between layers is working correctly
*/

#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _DVORAK 0
#define _SYMBOLS 2
#define _FN 3
#define _NUMPAD 1

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  SYMBOLS,
  NUMPAD,
  FN
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_NMPD TG(_NUMPAD)
#define KC_SYMB TG(_SYMBOLS)
#define KC_SPFN LT(_FN,KC_PERC)
#define KC_SPCT MT(MOD_LCTL, KC_EXLM)
#define KC_SPLT MT(MOD_LALT, KC_AMPR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     ESC ,QUOT,COMM,DOT , P  , Y  ,      F  , G  , C  , R  , L  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     TAB , A  , O  , E  , U  , I  ,      D  , H  , R  , N  , S  , ENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSPO,SCLN, Q  , J  , K  , X  ,      B  , M  , W  , V  , Z  ,RSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     SPCT,SPFN,SPLT,MINS,NMPD,SLSH,     SPC ,SYMB,ASTR,EQL ,LBRC,RBRC
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_NUMPAD] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,         ,  7 ,  8 ,  9 ,MINS,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,  4 ,  5 ,  6 ,PLUS, EQL,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,  1 ,  2 ,  3 ,ASTR, ENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,  0 ,  0 , DOT,SLSH, ENT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYMBOLS] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      F1 , F2 , F3 , F4 , F5 , F6 ,     TILD,EQL ,UNDS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      F7 , F8 , F9 , F10, F11, F12,     GRV ,PLUS,MINS,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_FN] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,    ,    ,    , DEL,BSPC,         ,HOME, UP , END, INS,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,LSFT,LCTL, ENT,         ,LEFT,DOWN,RGHT, DEL,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,PGUP,PGDN,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,   
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case SYMBOLS:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_SYMBOLS);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_NUMPAD);
      }
      return false;
      break;
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_FN);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
 }
  return true;
}
