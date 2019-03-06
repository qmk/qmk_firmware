#include QMK_KEYBOARD_H

// Define Layers
#define _FUNCPAD 0
#define _PINPAD  1
#define _RGBPAD  2
#define _RGBCTRL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_FUNCPAD] = LAYOUT( \
    LALT(KC_ESC),  LALT(KC_Z), \
    KC_F21,        KC_F22, \
    KC_F23,        KC_F24, \
    TG(1),         TG(2)),

[_PINPAD] = LAYOUT( \
    KC_3,    KC_5, \
    KC_8,    KC_2, \
    KC_4,    KC_2, \
    KC_TRNS, KC_ENT),

[_RGBPAD] = LAYOUT( \
    RGB_MOD, RGB_TOG, \
    RGB_VAI, RGB_VAD, \
    RGB_SPI, RGB_SPD, \
    TO(3),   KC_TRNS),

[_RGBCTRL] = LAYOUT( \
    RGB_HUI, RGB_HUD, \
    RGB_SAI, RGB_SAD, \
    RGB_VAI, RGB_VAD, \
    KC_TRNS, RGB_TOG)

};

void matrix_init_user(void) {

}
