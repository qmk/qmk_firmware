/* Keymap _0: (Base Layer) Default Layer
   * .-----------.
   * |PGUP | PGDN| 
   * |-----------------------.
   * |  7  |  8  |  9  | MO1 |
   * |-----|-----|-----|-----|
   * |  4  |  5  |  6  |  +  |
   * |-----|-----|-----|-----|
   * |  1  |  2  |  3  |  —  |
   * |-----|-----|-----|-----|
   * |  0  |  .  | DEL |Enter|
   * .-----------------------.
   */
     /* Keymap _1: (Second Layer) second Layer
   * .---------------.
   * |NUMLOCK|Calc.  | 
   * |--------------------------------.
   * |RGB_TOG|RGB_MOD|RGB_M_K|RGB_M_X |
   * |-------|-------|-------|--------|
   * |RGB_SAI|RGB_SAD|RGB_HUI|RGB_HUD |
   * |-------|-------|-------|--------|
   * |RGB_VAI|RGB_VAD|RGB_SPI|RGB_SPD |
   * |-------|-------|-------|--------|
   * |RGB_SPI|RGB_SPD|RGB_TOG|KC_TRNS |
   * .--------------------------------.
*/

#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_KP_7, KC_KP_8, KC_KP_9, MO(1),
        KC_P4, KC_P5, KC_P6, KC_KP_PLUS,
        KC_P1, KC_P2, KC_P3, KC_KP_MINUS,
        KC_P0, KC_PDOT,KC_DELETE, KC_KP_ENTER,
        KC_PGUP, KC_PGDOWN),
    [1] = LAYOUT_all(
        RGB_TOG, RGB_MOD, RGB_M_K, RGB_M_X,
        RGB_SAI, RGB_SAD, RGB_HUI, RGB_HUD,
        RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD,
        RGB_SPI, RGB_SPD, RGB_TOG, KC_TRNS,
        KC_NUMLOCK, KC_CALCULATOR),
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_AUDIO_VOL_UP);
    } else {
      tap_code(KC_AUDIO_VOL_DOWN);
    }
  } else if (index == 1) {
    if (clockwise) {
      tap_code(KC_BRIGHTNESS_UP);
    } else {
      tap_code(KC_BRIGHTNESS_DOWN);
    }
  }
}
