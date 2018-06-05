#include "ergodash.h"
#include "action_layer.h"
#include "eeconfig.h"

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

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_AJST ADJUST
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_JPN LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 */
  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.         ,----+----+----+----+----+----+----.
      ESC, 1,   2,   3,   4,   5,   LBRC,         RBRC,  6,   7,   8,   9,   0, CAPS,
  //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
      GRV , Q  , W  , E  , R  , T , MINS,          EQL,  Y  , U  , I  , O  , P ,BSLS,
  //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
      TAB , A  , S  , D  , F  , G  ,DEL ,         BSPC,  H  , J  , K ,  L ,SCLN,QUOT,
  //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
      LSFT, Z  , X  , C  , V  , B  ,JPN,           ENT,  N ,  M ,COMM, DOT,SLSH,RSFT,
  //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
     LCTL,LGUI,LALT, AJST,     LOWR,SPC,           ENT,RASE,     LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----'         `----+----+----+----+----+----+----'
  ),

/* Lower
 */
 [_LOWER] = KC_KEYMAP(
 //,----+----+----+----+----+----+----.         ,----+----+----+----+----+----+----.
     F11, F1,  F2,  F3,  F4,  F5, LCBR,          RCBR, F6,  F7,  F8,  F9,  F10, F12,
 //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
     TILD,EXLM, AT ,HASH, DLR,PERC,UNDS,         PLUS,CIRC,AMPR,ASTR,LPRN,RPRN,PIPE,
 //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
     TAB , 1  , 2  , 3  , 4  , 5  ,DEL ,         BSPC,  H  , J ,  K ,  L ,COLN, DQT,
 //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
     LSFT, 6  , 7  , 8  , 9  , 0  ,JPN,           ENT,  N  , M , LT , GT ,QUES,RSFT,
 //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
    LCTL,LGUI,LALT, AJST,     LOWR,SPC,           ENT,RASE,     HOME,PGDN,PGUP, END
 //`----+----+----+----+----+----+----'         `----+----+----+----+----+----+----'
 ),

/* Raise
 */
  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.         ,----+----+----+----+----+----+----.
      F11, F1,  F2,  F3,  F4,  F5, LCBR,          RCBR, F6,  F7,  F8,  F9,  F10, F12,
  //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
      TILD,EXLM, AT ,HASH, DLR,PERC,UNDS,         PLUS,CIRC,AMPR,ASTR,LPRN,RPRN,PIPE,
  //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
      TAB , 1  , 2  , 3  , 4  , 5  ,DEL ,         BSPC,  H  , J ,  K ,  L ,COLN, DQT,
  //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
      LSFT, 6  , 7  , 8  , 9  , 0  ,JPN,           ENT,  N  , M , LT , GT ,QUES,RSFT,
  //|----+----+----+----+----+----+----|         |----+----+----+----+----+----+----|
     LCTL,LGUI,LALT, AJST,     LOWR,SPC,           ENT,RASE,     HOME,PGDN,PGUP, END
  //`----+----+----+----+----+----+----'         `----+----+----+----+----+----+----'
  ),

  [_ADJUST] = KEYMAP(
    _______, _______, _______, _______, _______, _______,_______,       _______, _______, _______, _______, _______, _______, _______, \
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,       _______, _______,          _______, _______, _______, _______ \
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
