 /* Keymap _1: (Base Layer) Default Layer
   * .-----------.
   * |PGUP | PGDN| 
   * |-----|-----|-----|-----|
   * |  7  |  8  |  9  | MO1 |
   * |-----|-----|-----|-----|
   * |  4  |  5  |  6  |  +  |
   * |-----|-----|-----|-----|
   * |  1  |  2  |  3  |  —  |
   * |-----|-----|-----|-----|
   * |  0  |  .  | DEL |Enter|
   * .-----------------------.
   */
     /* Keymap _1: (Base Layer) Default Layer
   * .------------------.
   * |NUMLOCK|Caculator | 
   * |-------|-------|-----|-----|
   * |RGB_TOG|RGB_MOD|  9  | MO1 |
   * |-------|-------|-----|-----|
   * |RGB_M_K|RGB_SAI|  6  |  +  |
   * |-------|-------|-----|-----|
   * |RGB_HUI|RGB_VAI|  3  |  —  |
   * |-------|-------|-----|-----|
   * |   0   |   .   | DEL |Enter|
   * .-----------------------.
   
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(RGB_MOD, RESET)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_hasu_5x4(
	KC_KP_7, KC_KP_8, KC_KP_9, MO(1),
	KC_KP_PLUS,KC_P6,KC_P5,KC_P4, 
	KC_P1, KC_P2, KC_P3, KC_KP_MINUS, KC_KP_ENTER,KC_DELETE, KC_PDOT,KC_P0, KC_PGUP, KC_PGDOWN, _______, _______),
    [1] = LAYOUT_hasu_5x4(RGB_TOG, RGB_MOD, RGB_M_K, RGB_M_X, RGB_SAI, RGB_SAD, RGB_HUI, RGB_HUD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, RGB_SPI, RGB_SPD, RGB_TOG, KC_TRNS, KC_NUMLOCK, KC_CALCULATOR, _______, _______),
};
*/

#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_hasu_5x4(
        KC_KP_7, KC_KP_8, KC_KP_9, MO(1),
        KC_KP_PLUS, KC_P6, KC_P5, KC_P4,
        KC_P1, KC_P2, KC_P3, KC_KP_MINUS,
        KC_KP_ENTER, KC_DELETE, KC_PDOT, KC_P0,
        KC_PGUP, KC_PGDOWN, _______, _______),
    [1] = LAYOUT_hasu_5x4(
        RGB_TOG, RGB_MOD, RGB_M_K, RGB_M_X,
        RGB_SAI, RGB_SAD, RGB_HUI, RGB_HUD,
        RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD,
        RGB_SPI, RGB_SPD, RGB_TOG, KC_TRNS,
        KC_NUMLOCK, KC_CALCULATOR, _______, _______),
};

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,  0};
    oled_write_P(qmk_logo, false);
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) { render_logo(); }
#endif

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
void matrix_init_user(void) { render_logo(); }
