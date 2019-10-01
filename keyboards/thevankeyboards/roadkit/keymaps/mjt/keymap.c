#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

void backlight_toggle(void){
};

enum roadkit_layers {
  _NUMPAD,
  _NAVIGATION,
  _EXCEL,
  _ADJUST,
  _DYN
};

enum minivan_keycodes {
  NUMPAD = SAFE_RANGE,
  NAVIGATION,
  EXCEL,
  NUMPAD_LOCK,
  NAVIGATION_LOCK,
  EXCEL_LOCK,
  PARENS,
  BRACKETS,
  BRACES,
  BACKLIT,
  MACSLEEP,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

// Fillers to make keymaps cleaner looking
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUMPAD] = LAYOUT_numpad_4x4( /* Numpad */
    KC_KP_7, KC_KP_8, KC_KP_9,   KC_KP_PLUS, \
    KC_KP_4, KC_KP_5, KC_KP_6,   \
    KC_KP_1, KC_KP_2, KC_KP_3,   NAVIGATION, \
    EXCEL,            KC_KP_DOT
  ),
  [_EXCEL] = LAYOUT_numpad_4x4( /* Excel related */
    KC_KP_SLASH, KC_KP_ASTERISK, KC_MINS,  KC_TAB, \
    KC_QUOT,     KC_KP_EQUAL,    PARENS,   \
    KC_DQT,      BRACKETS,       BRACES,   _______, \
    _______,                     MO(_DYN)
  ),
  [_NAVIGATION] = LAYOUT_numpad_4x4( /* Navigation */
    KC_HOME, _______, KC_PGUP,  KC_TAB, \
    KC_END,  KC_UP,   KC_PGDN,  \
    KC_LEFT, KC_DOWN, KC_RIGHT, _______, \
    _______,          MO(_DYN)
  ),
  [_ADJUST] = LAYOUT_numpad_4x4( /* Adjustments */
    KC_NUMLOCK, MACSLEEP,    BACKLIT,         _______, \
    KC_BSPC,     _______,    KC_DEL,          \
    EXCEL_LOCK, NUMPAD_LOCK, NAVIGATION_LOCK, _______, \
    _______,                 _______
  ),
  [_DYN] = LAYOUT_numpad_4x4( /* DYNAMIC MACRO */
    DYN_REC_START1,  DYN_REC_START2,  _______, _______, \
    _______,         _______,         _______, \
    DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, _______, _______, \
    _______,                          _______
  ),
};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_numpad[][2]     = SONG(QWERTY_SOUND);
float tone_excel[][2]     = SONG(DVORAK_SOUND);
float tone_navigation[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool fn_tap_used = false; // sets to false when space is pressed,
                          // sets to true when any other key is pressed,
                          //when space is lifted, if another key was prssed, don't send space.
uint16_t fn_keycode = 0; // stores which spacebar was used, either raise or lower...

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  switch (keycode) {
      case NAVIGATION: // This key is enter if tapped, navigation if held
        if (record->event.pressed) {
          fn_keycode = NAVIGATION; // these two lines figure out if the next action is
          fn_tap_used = false;
          layer_on(_NAVIGATION);
          update_tri_layer(_EXCEL, _NAVIGATION, _ADJUST);
        } else {
          layer_off(_NAVIGATION);
          update_tri_layer(_EXCEL, _NAVIGATION, _ADJUST);
          if(!fn_tap_used && fn_keycode == NAVIGATION ){
              register_code(KC_KP_ENTER);
              unregister_code(KC_KP_ENTER);
              fn_keycode = 0;
              fn_tap_used = false;
          }
        }
        return false;
        break;
      case EXCEL:
        if (record->event.pressed) {
          fn_keycode = EXCEL;
          fn_tap_used = false;
          layer_on(_EXCEL);
          update_tri_layer(_EXCEL, _NAVIGATION, _ADJUST);
        } else {
          layer_off(_EXCEL);
          update_tri_layer(_EXCEL, _NAVIGATION, _ADJUST);
          if(!fn_tap_used && fn_keycode == EXCEL ){
              register_code(KC_KP_0);
              unregister_code(KC_KP_0);
              fn_keycode = 0;
              fn_tap_used = false;
          }
        }
        return false;
        break;
    default:
        fn_tap_used = true;
        break; // don't return because this just handles the spacebars.
    }
    // this is the normal keycode processing switch from Planck default layout.
    switch (keycode) {
    case NUMPAD_LOCK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_numpad, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_NUMPAD);
      }
      return false;
      break;
    case NAVIGATION_LOCK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_navigation, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_NAVIGATION);
      }
      return false;
      break;
    case EXCEL_LOCK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_excel, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_EXCEL);
      }
      return false;
      break;
    case PARENS:
      if (record->event.pressed) {
          register_code(KC_RSFT);
          register_code(KC_9);
          unregister_code(KC_9);
          register_code(KC_0);
          unregister_code(KC_0);
          register_code(KC_RSFT);
          register_code(KC_LEFT);
          unregister_code(KC_LEFT);
      }
      return false;
      break;
    case BRACKETS:
      if (record->event.pressed) {
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          register_code(KC_LEFT);
          unregister_code(KC_LEFT);
        }
        return false;
        break;
    case BRACES:
      if (record->event.pressed) {
          register_code(KC_RSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          unregister_code(KC_RSFT);
          register_code(KC_LEFT);
          unregister_code(KC_LEFT);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      }
      return false;
      break;
    case MACSLEEP:
      if (record->event.pressed) {
          register_code(KC_RSFT);
          register_code(KC_RCTL);
          register_code(KC_POWER);
          unregister_code(KC_POWER);
          unregister_code(KC_RCTL);
          unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}
