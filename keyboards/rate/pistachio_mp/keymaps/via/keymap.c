/* Copyright 2020 rate
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE = 0,
    _FN,
    _RESERVE_0,
    _RESERVE_1
};

static uint8_t encoder_state = 0;
static const keypos_t ENC_CW = {.row = 3, .col = 3};
static const keypos_t ENC_CCW = {.row = 4, .col = 1};

#define LAYOUT_via( \
         ECW,ECCW, K07, \
    K00, K01, K02, K03, \
    K04, K05, K06,      \
    K08, K09, K10, K11, \
    K12, K13, K14,      \
    K15,      K16, K17 ) { \
    { K00,   K01,   K02,   K03 }, \
    { K04,   K05,   K06,   K07 }, \
    { K08,   K09,   K10,   K11 }, \
    { K12,   K13,   K14,   ECCW }, \
    { K15,   ECW,   K16,   K17 }, \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_via(
                           KC_VOLU,KC_VOLD,KC_MPLY,
    LT(_FN, KC_NUM),   KC_PSLS,  KC_PAST,  KC_PMNS,
    KC_P7,             KC_P8,    KC_P9,
    KC_P4,             KC_P5,    KC_P6,    KC_PPLS,
    KC_P1,             KC_P2,    KC_P3,
    KC_P0,                       KC_PDOT,  KC_PENT
    ),
    /* Fn */
    [_FN] = LAYOUT_via(
                KC_VOLU,KC_VOLD,KC_NO,
    KC_NO,   KC_NO,   KC_NO,    KC_NO,
    RGB_HUI, RGB_SAI, RGB_VAI,
    RGB_HUD, RGB_SAD, RGB_VAD,  RGB_TOG,
    KC_NO,   KC_NO,   KC_NO,
    KC_NO,            KC_NO,    KC_NO
    ),
    /* Reserve */
    [_RESERVE_0] = LAYOUT_via(
                KC_VOLU,KC_VOLD,KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,          KC_TRNS,  KC_TRNS
    ),
    /* Reserve */
    [_RESERVE_1] = LAYOUT_via(
                KC_VOLU,KC_VOLD,KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,          KC_TRNS,  KC_TRNS
    ),
};

#ifdef ENCODER_ENABLE
void encoder_action_unregister(void) {
    if (encoder_state) {
        keyevent_t encoder_event = (keyevent_t) {
            .key = encoder_state >> 1 ? ENC_CW : ENC_CCW,
            .pressed = false,
            .time = timer_read(),
            .type = KEY_EVENT
        };
        encoder_state = 0;
        action_exec(encoder_event);
    }
    return;
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? ENC_CW : ENC_CCW,
        .pressed = true,
        .time = timer_read(),
        .type = KEY_EVENT
    };
    encoder_state = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
    return;
}

void matrix_scan_kb(void) {
    encoder_action_unregister();
    matrix_scan_user();
    return;
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    // don't return user actions, because they are in the keymap
    // encoder_update_user(index, clockwise);
    return true;
};
#endif
