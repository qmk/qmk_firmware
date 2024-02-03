#include QMK_KEYBOARD_H

enum layer_names { _MAIN, _FN1, _FN2, _FN3 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAIN] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

    [_FN1] = LAYOUT(KC_NO, KC_NO, KC_NO, _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

    [_FN2] = LAYOUT(_______, _______, _______, _______, _______, _______, _______, _______, _______),

    [_FN3] = LAYOUT(_______, _______, _______, _______, _______, _______, _______, _______, _______)

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAIN] = {ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO)},
    [_FN1]  = {ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO)},
    [_FN2]  = {ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(_______, _______)},
    [_FN3]  = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
};
#endif
