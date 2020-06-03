#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT( RGB_MOD )
};

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom_cyan();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}
