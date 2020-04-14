#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = LAYOUT( \
             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC,         KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_B,           KC_B,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, \
    RGB_MOD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_MOD, \
             KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO,         KC_NO,  KC_NO, KC_NO,        KC_NO, KC_NO, \
                                   KC_NO, KC_NO, KC_NO,         KC_NO,  KC_NO, KC_NO \
  ),

[_LOWER] = LAYOUT( \
             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC,         KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_B,           KC_B,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, \
    RGB_MOD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_MOD, \
             KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO,         KC_NO,  KC_NO, KC_NO,        KC_NO, KC_NO, \
                                   KC_NO, KC_NO, KC_NO,         KC_NO,  KC_NO, KC_NO \
  )


};

void persistant_default_layer_set(uint16_t default_layer) {
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
        persistant_default_layer_set(1UL<<_QWERTY);
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
