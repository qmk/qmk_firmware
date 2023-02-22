#include QMK_KEYBOARD_H

enum layers
{
    _LAYER0,
    _LAYER1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT(
        KC_NO,   KC_UP,   TO(_LAYER1),
        KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_LAYER1] = LAYOUT(
        KC_NUBS,    KC_NUHS,    TO(_LAYER0),
        LCAG(KC_Z), LCAG(KC_X), LCAG(KC_C)
    )
};
