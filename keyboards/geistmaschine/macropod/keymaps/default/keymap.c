#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_fourkey (
        KC_MPLY, KC_A,    KC_B,    KC_C
    ),

    [1] = LAYOUT_fourkey (
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT_fourkey (
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [3] = LAYOUT_fourkey (
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
};
#endif
