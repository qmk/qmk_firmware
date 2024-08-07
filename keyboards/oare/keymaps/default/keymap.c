// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keycode_lookup.h"
#include "matrix.h"

extern matrix_row_t matrix[MATRIX_ROWS];

uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b) {
    uint8_t colIndex = index % 10;
    uint8_t rowIndex = (index / 10) * 3 + (pad_b ? 1 : 2);
    uint8_t returnVal = (uint8_t)!!(matrix[rowIndex] & (0x1 << colIndex));
    return returnVal;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_3x10(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SPC
    ),
    [1] = LAYOUT_ortho_3x10(
        KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  
        KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_TRNS,  
        KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_ENC,  KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// We store an array of key offset to shift the alpha keys depending on how many times the encoder has been turned
uint8_t key_offsets[KEY_OFFSET_COUNT];

// Note: we start on layer 1, which is basically just a fancy mask so we can modify layer 0 for alpha keys
void keyboard_post_init_user(void) {
    layer_on(1);
    for (uint8_t i=0; i<KEY_OFFSET_COUNT; i++) {
        key_offsets[i] = 0; // initialize - might not need to, but doesn't hurt
    }
    debug_enable=true;
    debug_matrix=true; // note that I ran into strange issues where the matrix didn't seem to get populated properly if I wasn't
    // using the values, such as in this debug - not sure if it's something to do with the compiler optimizing something out?
}

// We'll need a way to go from row/col to the index in that above array - fortunately we have a pretty convenient macro.
// This is clever, give me some credit.
uint8_t key_positions[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_ortho_3x10(
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29
);

// Whenever an encoder is turned, we need to update the key_offset array so we know how much to modify the alphas
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t newVal = key_offsets[index];
    newVal += (clockwise ? 1 : -1);
    newVal += KEY_OFFSET_SIZE;
    newVal %= KEY_OFFSET_SIZE;
    key_offsets[index] = newVal;
    if (index < 29) {
        return false;
    }
    return true;
}