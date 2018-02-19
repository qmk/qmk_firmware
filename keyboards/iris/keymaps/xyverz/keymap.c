#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_____ KC_TRNS
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_QWRT QWERTY
#define KC_CLMK COLEMAK
#define KC_DVRK DVORAK

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,                N  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL,LALT,GRV ,LEFT,RGHT,HOME,END ,     PGDN,PGUP,UP  ,DOWN,BSLS,RGUI,RCTL,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LOWR,BSPC,LGUI,         ENT ,SPC ,RASE
  //                  `----+----+----'        `----+----+----'
  ),

  [_COLEMAK] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     ESC , A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,                K  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL,LALT,GRV ,LEFT,RGHT,HOME,END ,     PGDN,PGUP,UP  ,DOWN,BSLS,RGUI,RCTL,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LOWR,BSPC,LGUI,         ENT ,SPC ,RASE
  //                  `----+----+----'        `----+----+----'
  ),

  [_DVORAK] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TAB ,QUOT,COMM,DOT , P  , Y  ,                F  , G  , C  , R  , L  ,SLSH,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     ESC , A  , O  , E  , U  , I  ,                D  , H  , T  , N  , S  ,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSFT,SCLN, Q  , J  , K  , X  ,                B  , M  , W  , V  , Z  ,RSFT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL,LALT,GRV ,LEFT,RGHT,HOME,END ,     PGDN,PGUP,UP  ,DOWN,BSLS,RGUI,RCTL,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LOWR,BSPC,LGUI,         ENT ,SPC ,RASE
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CAPS,____,MUTE,VOLD,VOLU,____,               ____,UNDS,PLUS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     DEL ,____,MPRV,MPLY,MNXT,____,               ____,____,____,____,____,____,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     BL_S,____,____,HOME,END ,____,____,     ____,____,PGUP,PGDN,____,____,____,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       ____,DEL ,____,         ____,INS ,____
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,____,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CAPS,____,MUTE,VOLD,VOLU,____,               ____,MINS,EQL ,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     DEL ,____,MPRV,MPLY,MNXT,____,               ____,____,____,____,____,____,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     BL_S,____,____,HOME,END ,____,____,     ____,____,PGUP,PGDN,____,____,____,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       ____,DEL ,____,         ____,INS ,____
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F11 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F12 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     ____,RST ,____,____,____,____,               ____,QWRT,CLMK,DVRK,____,____,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     ____,____,____,____,____,____,               ____,____,____,____,____,____,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     ____,____,____,____,____,____,____,     ____,____,____,____,____,____,____,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       ____,____,____,         ____,____,____
  //                  `----+----+----'        `----+----+----'
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
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
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
