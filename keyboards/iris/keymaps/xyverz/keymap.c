#include QMK_KEYBOARD_H
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
#define KC_BSLT ALT_T(KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc (
     EQL , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,MINS,
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSLS,
     ESC , A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
     LSFT, Z  , X  , C  , V  , B  ,LOWR,     RASE, N  , M  ,COMM,DOT ,SLSH,RSFT,
                       LCTL,BSPC,LGUI,         ENT ,SPC ,LALT
  ),

  [_COLEMAK] = LAYOUT_kc (
     EQL , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,MINS,
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,BSPC,
     ESC , A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
     LSFT, Z  , X  , C  , V  , B  ,LOWR,     RASE, K  , M  ,COMM,DOT ,SLSH,RSFT,
                       LCTL,BSPC,LGUI,         ENT ,SPC ,LALT
  ),

  [_DVORAK] = LAYOUT_kc (
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSLS,
     TAB ,QUOT,COMM,DOT , P  , Y  ,                F  , G  , C  , R  , L  ,SLSH,
     ESC , A  , O  , E  , U  , I  ,                D  , H  , T  , N  , S  ,MINS,
     LSFT,SCLN, Q  , J  , K  , X  ,LOWR,     RASE, B  , M  , W  , V  , Z  ,RSFT,
                       LCTL,BSLT,LGUI,         ENT ,SPC ,LALT
  ),

  [_LOWER] = LAYOUT_kc (
     F11 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F12 ,
     TILD,____,____, UP ,____,____,               ____,____,____,____,____,____,
     CAPS,____,LEFT,DOWN,RGHT,HOME,               PGUP,UNDS,PLUS,LCBR,RCBR,PIPE,
     BL_S,____,MUTE,VOLD,VOLU,END ,____,     ____,PGDN,MPRV,MPLY,MNXT,____,____,
                       ____,DEL ,____,         ____,INS ,____
  ),

  [_RAISE] = LAYOUT_kc (
     F11 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F12 ,
     GRV ,____,____, UP ,____,____,               ____,____,____,____,____,____,
     CAPS,____,LEFT,DOWN,RGHT,HOME,               PGUP,MINS,EQL ,LBRC,RBRC,BSLS,
     BL_S,____,MUTE,VOLD,VOLU,END ,____,     ____,PGDN,MPRV,MPLY,MNXT,____,____,
                       ____,DEL ,____,         ____,INS ,____
  ),

  [_ADJUST] = LAYOUT_kc (
     F11 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F12 ,
     ____,RST ,____,____,____,____,               ____,____,____,____,____,____,
     ____,____,____,____,____,____,               ____,QWRT,CLMK,DVRK,____,____,
     ____,____,____,____,____,____,____,     ____,____,____,____,____,____,____,
                       ____,____,____,         ____,____,____
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
};

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
