#include QMK_KEYBOARD_H
#include "apa102.h" // Only needed if you want to use the global brightness function

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(UG_NEXT)
};

void keyboard_post_init_user(void) {
    apa102_set_brightness(5);

    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_CYAN);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}
