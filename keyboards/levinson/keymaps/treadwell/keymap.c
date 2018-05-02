#include "levinson.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _NUMB 3
#define _CODE 4
#define _SYS 5
#define _FN4 6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  NUMB,
  CODE,
  SYS,
  FN4,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_X1 CODE
#define KC_X2 NUMB
#define KC_X3 SYS
#define KC_X4 MT(MOD_LSFT, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     BSPC, A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH, X4 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI, X1 ,LALT,     SPC , X2 ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , F  , P  , G  ,      J  , L  , U  , Y  ,SCLN,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     BSPC, A  , R  , S  , T  , D  ,      H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      K  , M  ,COMM,DOT ,SLSH, X4 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI, X1 ,LALT,     SPC , X2 ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_DVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB ,QUOT,COMM,DOT , P  , Y  ,      F  , G  , C  , R  , L  ,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     BSPC, A  , O  , E  , U  , I  ,      D  , H  , T  , N  , S  ,SLSH,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,SCLN, Q  , J  , K  , X  ,      B  , M  , W  , V  , Z  , X4 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI, X1 ,LALT,     SPC , X2 ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_NUMB] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,PMNS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,UNDS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,MPRV,MPLY,MNXT,    ,         ,VOLD,VOLU,MUTE,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,LALT,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_CODE] = LAYOUT_kc(
  //,----+------+----+----+----+----.    ,----+----+----+----+----+----.
     ESC ,      ,    , UP ,    ,    ,     PGUP,HOME,LPRN,RPRN,BSLS,PIPE,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
     CAPS,SELECT,LEFT,DOWN,RGHT,DEL ,     PGDN, END,LBRC,RBRC,MINS,UNDS,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
         , UNDO ,CUT ,COPY,PASTE,   ,     LEFT,RGHT,LCBR,RCBR,PLUS,PEQL,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
         ,      ,    ,    ,    ,LALT,         ,    ,    ,    ,    ,
  //`----+------+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYS] = LAYOUT_kc(
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
  [_ADJUST] = LAYOUT( \
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
    case NUMB:
      if (record->event.pressed) {
        layer_on(_NUMB);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      } else {
        layer_off(_NUMB);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      }
      return false;
      break;
    case CODE:
      if (record->event.pressed) {
        layer_on(_CODE);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      } else {
        layer_off(_CODE);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
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
