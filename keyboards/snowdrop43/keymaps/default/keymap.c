// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,     KC_T,
        KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,     KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,     KC_B,
                          KC_BSPC, KC_SPC, MO(2),    KC_LCMD,

        KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     KC_MINS,
        KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,  KC_QUOTE,
        KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLASH, KC_RSFT,
        KC_RCMD, MO(1),   KC_ENT
    ),
    [1] = LAYOUT(
        _______, KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, _______,
        _______, KC_LALT, KC_TILD, KC_GRV , KC_PIPE, KC_BSLS,
        _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______,

        _______, KC_RPRN, KC_RCBR, KC_RBRC, KC_RABK, _______,
        KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_ESC , _______,
        _______, _______, _______, _______, _______, _______,
                 _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,
        _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,
        _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, _______,
                          _______, _______, _______, _______,


        KC_CIRC, KC_AMPR, KC_ASTR, KC_PEQL, KC_PPLS, _______,
        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
        _______, _______, _______, _______, _______, _______,
                 _______, _______, _______
    )
};

enum custom_keycodes {
    DRAG_SCROLL = KC_BTN3,
};

bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H -8.0
#define SCROLL_DIVISOR_V -8.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Function to handle key events and enable/disable drag scrolling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRAG_SCROLL:
            // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
            set_scrolling = record->event.pressed;
            break;
        default:
            break;
    }
    return true;
}

