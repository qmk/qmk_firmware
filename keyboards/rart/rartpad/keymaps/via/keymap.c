#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_5x4(
    KC_NLCK, KC_PSLS, KC_PAST, KC_INS,
    KC_P7,   KC_P8,   KC_P9,   KC_PEQL,
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
    MO(1),   KC_P0,   KC_PDOT, KC_PENT
    ),

  [1] = LAYOUT_ortho_5x4(
    KC_TRNS, RGB_HUI, RGB_HUD,  QK_BOOT,
    RGB_SAI, RGB_SAD, KC_MNXT,  KC_MPRV,
    RGB_VAI, RGB_VAD, KC_MSTP,  KC_MPLY,
    KC_COPY, KC_PSTE, KC_MYCM,  KC_CALC,
    KC_TRNS, RGB_TOG, KC_TRNS,  KC_TRNS
    ),

  [2] = LAYOUT_ortho_5x4(
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______
    ),

  [3] = LAYOUT_ortho_5x4(
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
