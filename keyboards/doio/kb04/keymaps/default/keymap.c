#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
       ┌───┬───┬───┬───┐   ┌───┐
       │ 1 │ 2 │ 3 │ 4 │   │Mut│
       └───┴───┴───┴───┘   └───┘
*/
    [0] = LAYOUT(
        KC_1,     KC_2,    KC_3,    KC_4,     KC_MUTE
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif
