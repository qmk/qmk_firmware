#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _FKEYS 5
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_GRVF LT(_FKEYS, KC_GRV)
#define KC_ENTS MT(MOD_LSFT, KC_ENT)
#define KC_BL_S BL_STEP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = KC_LAYOUT_ortho_4x12(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESCC, A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,ENTS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     GRVF,LCTL,LALT,LGUI,LOWR,SPC ,     BSPC,RASE,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_COLEMAK] = KC_LAYOUT_ortho_4x12(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , F  , P  , G  ,      J  , L  , U  , Y  ,SCLN,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESCC, A  , R  , S  , T  , D  ,      H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      K  , M  ,COMM,DOT ,SLSH,ENTS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     GRVF,LCTL,LALT,LGUI,LOWR,SPC ,     BSPC,RASE,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_DVORAK] = KC_LAYOUT_ortho_4x12(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB ,QUOT,COMM,DOT , P  , Y  ,      F  , G  , C  , R  , L  ,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESCC, A  , O  , E  , U  , I  ,      D  , H  , T  , N  , S  ,SLSH,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,SCLN, Q  , J  , K  , X  ,      B  , M  , W  , V  , Z  ,ENTS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     GRVF,LCTL,LALT,LGUI,LOWR,SPC ,     BSPC,RASE,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_LOWER] = KC_LAYOUT_ortho_4x12(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     DEL ,CAPP,LEFT,RGHT, UP ,LBRC,     RBRC, P4 , P5 , P6 ,PLUS,PIPE,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,CPYP,    ,    ,DOWN,LCBR,     RCBR, P1 , P2 , P3 ,MINS,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     BL_S,    ,    ,    ,    ,DEL ,     DEL ,    , P0 ,PDOT,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_RAISE] = KC_LAYOUT_ortho_4x12(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     DEL ,MPRV,MNXT,VOLU,PGUP,UNDS,     EQL ,HOME,    ,    ,    ,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     MUTE,MSTP,MPLY,VOLD,PGDN,MINS,     PLUS,END ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_FKEYS] = KC_LAYOUT_ortho_4x12(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_ortho_4x12( \
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
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
