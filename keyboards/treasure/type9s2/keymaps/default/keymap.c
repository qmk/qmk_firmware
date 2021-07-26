#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
  [0] = LAYOUT(MO(1), KC_MEDIA_PLAY_PAUSE, BL_STEP,
               KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP,
               KC_KP_1, KC_KP_2, KC_KP_3),

  [1] = LAYOUT(KC_TRNS, KC_TRNS, MO(2),
               KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS),

  [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, MO(3)),

  [3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               RESET, KC_TRNS, KC_TRNS),
};
