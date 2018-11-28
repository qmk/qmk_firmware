#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#include "levinson.h"
#include "neo2-keys-on-quertz-de-latin1.h"
#include "neo2-basic-layout.h"

enum my_keycodes
{
  N2_LETTERS = 1,

  N2_SYM = 3,
  N2_CON = 4,
  N2_GREEK = 5,
  N2_MATH = 6,
  N2_FUN = 7,

  QWERTY = 8,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* L01 -> default: BASE LAYER
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |                                  |                                  | ENTER|
 * |------+                                  |                                  +------|
 * | L03  |             L01_LEFT             |             L01_RIGHT            | L03  |
 * |------+                                  |                                  +------|
 * | SHIFT|                                  |                                  | SHIFT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTLR | GUI  | ALT  | L05  | L04  | SPACE| SPACE| L04  | L05  | ALTGR| LFN  | CTLR |
 * `-----------------------------------------------------------------------------------'
 */
[N2_LETTERS] = {
  {KC_ESC,                 L01_LEFT_01,                                 L01_RIGHT_01,                 KC_ENTER},
  {MO(N2_SYM),             L01_LEFT_02,                                 L01_RIGHT_02,                 MO(N2_SYM)},
  {KC_LSHIFT,              L01_LEFT_03,                                 L01_RIGHT_03,                 KC_RSFT},
  {KC_LCTRL,KC_LGUI, KC_LALT, MO(N2_FUN), MO(N2_CON), KC_SPC,  KC_SPC,  MO(N2_CON), MO(N2_FUN), KC_RALT, GUI, KC_RCTRL}
},


[N2_SYM] = {
  { _______,               L03_LEFT_01,                                 L03_RIGHT_01,                           _______},
  { _______,               L03_LEFT_02,                                 L03_RIGHT_02,                           _______},
  { _______,               L03_LEFT_03,                                 L03_RIGHT_03,                           _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},


[N2_CON] = {
  { _______,               L04_LEFT_01,                                 L04_RIGHT_01,                           _______},
  { _______,               L04_LEFT_01,                                 L04_RIGHT_02,                           _______},
  { _______,               L04_LEFT_03,                                 L04_RIGHT_03,                           _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}

},

[N2_FUN] = {
  { _______,               L07_LEFT_01,                                 L07_RIGHT_01,                           _______},
  { _______,               L07_LEFT_01,                                 L07_RIGHT_02,                           _______},
  { _______,               L07_LEFT_03,                                 L07_RIGHT_03,                           _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}

},

[QWERTY] = {
  { _______,               L08_LEFT_01,                                 L08_RIGHT_01,                           _______},
  { _______,               L08_LEFT_01,                                 L08_RIGHT_02,                           _______},
  { _______,               L08_LEFT_03,                                 L08_RIGHT_03,                           _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}

}
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
