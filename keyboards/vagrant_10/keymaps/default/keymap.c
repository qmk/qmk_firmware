/**
MIT License

Copyright (c) 2020 Shanduur & QMK Firmware

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    HOME,
    MODS,
    MODS2,
    OTHER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[HOME] = LAYOUT(
                          KC_P0,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        LT(1, KC_P1), LT(2, KC_P2), LT(3, KC_P3)),

	[MODS] = LAYOUT(
                          KC_MUTE,
        KC_MPLY, KC_NO,   KC_VOLU,
        KC_MPRV, KC_MNXT, KC_VOLD,
        KC_TRNS, KC_NO,   KC_NO),

	[MODS2] = LAYOUT(
                          KC_F13,
        KC_F14,  KC_F15,  KC_F16,
        KC_F19,  KC_F18,  KC_F17,
        KC_NO,   KC_TRNS, KC_NO),

	[OTHER] = LAYOUT(
                          QK_BOOT,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_TRNS),
};
