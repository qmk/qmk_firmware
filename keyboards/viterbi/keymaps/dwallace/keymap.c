#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _FN 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FN,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_SWIN LGUI(KC_TILD)   // Switch between windows
#define KC_SAPP LGUI(KC_TAB)    // Switch between applications
#define KC_FN1 MO(_FN)
#define KC_LCAG LCAG(KC_NO)
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RVAD RGB_VAD
#define KC_RVAI RGB_VAI
#define KC_CLRM KC_NO           // TODO: Clear sticky modifiers
#define KC_RST RESET

// TODO: Make modifiers sticky

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  , 6  ,      7  , 8  , 9  , 0  ,MINS,EQL ,BSPC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,LBRC,      Y  , U  , I  , O  , P  ,BSLS,PGUP,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,RBRC,      H  , J  , K  , L  ,SCLN,QUOT,ENT ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,SWIN,      N  , M  ,COMM,DOT , UP ,SLSH,RSFT,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LCTL,LCAG,LALT,LGUI,SPC ,CLRM,SAPP,     FN1 ,SPC ,RGUI,LEFT,DOWN,RGHT,PGDN
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_FN] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 , F6 ,      F7 , F8 , F9 ,F10 ,F11 ,F12 ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,RST ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,     RTOG,RMOD,RVAD,RVAI,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,MUTE,VOLD,VOLU,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
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
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
  }
  return true;
}
