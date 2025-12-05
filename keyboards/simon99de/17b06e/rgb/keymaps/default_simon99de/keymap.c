// Copyright 2025 FabiClawZ
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
[0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(KC_WBAK, KC_WFWD), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLL, MS_WHLR)},
    [1] = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_SPDD, RM_SPDU), ENCODER_CCW_CW(RM_SATD, RM_SATU), ENCODER_CCW_CW(RM_HUED, RM_HUEU), ENCODER_CCW_CW(RM_PREV, RM_NEXT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [3] = { ENCODER_CCW_CW(MI_OCTD, MI_OCTU), ENCODER_CCW_CW(MI_TRSD, MI_TRSU), ENCODER_CCW_CW(MI_VELD, MI_VELU), ENCODER_CCW_CW(MI_CHND, MI_CHNU), ENCODER_CCW_CW(MI_MODD, MI_MODU), ENCODER_CCW_CW(MI_BNDD, MI_BNDU)}
};
#endif

enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

#define LAYER_CYCLE_START   0
#define LAYER_CYCLE_END     3

void keyboard_post_init_user(void) {
    debug_enable = true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_CYCLE_LAYERS:
            if(!record->event.pressed) {
                return false;
            }

            layer_state_t current_layer = get_highest_layer(layer_state);

            if(current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
                return false;
            }

            layer_state_t next_layer = current_layer + 1;
            if(next_layer > LAYER_CYCLE_END) {
                next_layer = LAYER_CYCLE_START;
            }
            layer_move(next_layer);
            return false;
        default:
            return true;
    }
}

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
        KC_MUTE,                              KC_CYCLE_LAYERS,    KC_MPLY,
                KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_CALC,   KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_NUM,
                KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_MSEL,   KC_P0,   KC_PDOT, KC_PENT, KC_PPLS, KC_CAPS
    ),
    [1] = LAYOUT_ortho_6x4(
        RM_TOGG,                            KC_CYCLE_LAYERS,    KC_F13,
                    MS_BTN1,   MS_UP,   MS_BTN2,   MS_WHLU,
        KC_F14,    MS_LEFT,   MS_DOWN,   MS_RGHT,   MS_WHLD, KC_F15,
                    KC_F17,   KC_F18,   KC_F19,   KC_F20,
        KC_F16,    KC_F21,   KC_F22, KC_F23, KC_F24, QK_BOOT
    ),
    [2] = LAYOUT_ortho_6x4(
        QK_LOCK,                              KC_CYCLE_LAYERS,    KC_TRNS,
                 MS_BTN1,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,
                 KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_ortho_6x4(
        MI_TOGG,                            KC_CYCLE_LAYERS,    MI_AOFF,
                    MI_C,   MI_Cs,      MI_D,   MI_Ds,
        MI_SUST,    MI_E,   MI_F,       MI_Fs,  MI_G,               MI_PORT,
                    MI_Gs,  MI_A,       MI_As,  MI_B,
        MI_SOST,    MI_VL0, MI_VL3,     MI_VL7,   MI_VL10,        MI_LEG
    ),
};
