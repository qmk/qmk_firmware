// Copyright 2022 catmunch (@catmunch)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "macrocat.h"

static bool encoder_pressed = 0;
static bool encoder_switched_layer = 0;
static uint32_t encoder_last_release_time = 0;
static uint32_t encoder_press_combo = 0;
static uint8_t current_layer = 0;
void encoder_single_click(void) {
    tap_code(KC_MPLY);
}
void encoder_double_click(void) {
    tap_code(KC_MNXT);
}
void encoder_triple_click(void) {
    tap_code(KC_MPRV);
}
void matrix_init_kb() {
    setPinInputHigh(ENCODER_SWITCH);
}
void matrix_scan_kb() {
    matrix_scan_user();
    if (readPin(ENCODER_SWITCH)) {
        if (encoder_pressed) { // release switch
            encoder_pressed = 0;
            encoder_press_combo += 1;
            encoder_last_release_time = timer_read32();
        }
        if (encoder_press_combo && timer_elapsed(encoder_last_release_time) > 300) {
            // combo timeout
            if (encoder_switched_layer) { // switch layer
                encoder_switched_layer = 0;
            } else { // click
                switch (encoder_press_combo) {
                    case 1:
                        encoder_single_click();
                        break;
                    case 2:
                        encoder_double_click();
                        break;
                    default:
                        encoder_triple_click();
                }
            }
            encoder_press_combo = 0;
            encoder_last_release_time = 0;
        }
    } else {
        if (!encoder_pressed) { // press switch
            encoder_pressed = 1;
        }
    }
}
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false; 
    }
    if (clockwise) {
        if (encoder_pressed) {
            if (current_layer < 3) {
                current_layer += 1;
                layer_move(current_layer);
            }
            encoder_switched_layer = 1;
        } else {
            tap_code(KC_VOLU);
        }
    } else {
        if (encoder_pressed) {
            if (current_layer > 0) {
                current_layer -= 1;
                layer_move(current_layer);
            }
            encoder_switched_layer = 1;
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}
