#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LT(1, KC_MPRV), KC_MNXT, KC_MPLY,
        KC_VOLD,        KC_UP,   KC_VOLU,
        KC_LEFT,        KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        KC_ESC,  KC_MPLY, RESET,
        KC_P7,   KC_P1,   M(0),
        KC_F1,   KC_F2,   M(1)
    )
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LCTL), T(C), U(LCTL), END);
            case 1:
                return MACRO(D(LCTL), T(V), U(LCTL), END);
        }
    }
    return MACRO_NONE;
};
