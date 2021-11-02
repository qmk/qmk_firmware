#include QMK_KEYBOARD_H

enum layer {
    LYR0,
    LYR1,
};

/* Toggle between layers */
#define LYRTOG TG(LYR1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYR0] = LAYOUT(
        KC_AUDIO_MUTE, LYRTOG,  G(KC_TAB),
        KC_HOME,       KC_UP,   KC_END,
        KC_LEFT,       KC_DOWN, KC_RGHT
    ),
    [LYR1] = LAYOUT(
        RGB_TOG, KC_TRNS, RGB_MOD,
        RGB_HUI, RGB_SAI, RGB_VAI,
        RGB_HUD, RGB_SAD, RGB_VAD
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_AUDIO_VOL_UP);
    } else {
      tap_code(KC_AUDIO_VOL_DOWN);
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      tap_code16(G(C(KC_RGHT)));
    } else {
      tap_code16(G(C(KC_LEFT)));
    }
  }
}
