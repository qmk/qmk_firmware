// Copyright 2025 FabiClawZ
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
[0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(KC_WBAK, KC_WFWD), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLL, MS_WHLR)},
    [1] = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_SPDD, RM_SPDU), ENCODER_CCW_CW(RM_SATD, RM_SATU), ENCODER_CCW_CW(RM_HUED, RM_HUEU), ENCODER_CCW_CW(RM_PREV, RM_NEXT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_6x4(
        KC_MUTE,                              TO(1),    KC_MPLY,
                KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_CALC,   KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_NUM,
                KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_MSEL,   KC_P0,   KC_PDOT, KC_PENT, KC_PPLS, KC_CAPS
    ),
    [1] = LAYOUT_ortho_6x4(
        RM_TOGG,                            TO(0),    KC_F13,
                    MS_BTN1,   MS_UP,   MS_BTN2,   MS_WHLU,
        KC_F14,    MS_LEFT,   MS_DOWN,   MS_RGHT,   MS_WHLD, KC_F15,
                    KC_F17,   KC_F18,   KC_F19,   KC_F20,
        KC_F16,    KC_F21,   KC_F22, KC_F23, KC_F24, QK_BOOT
    )
};
