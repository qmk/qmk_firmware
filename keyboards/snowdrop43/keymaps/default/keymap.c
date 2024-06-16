// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum my_keycode {
    SCROLL = SAFE_RANGE,
    SWITCH,
    CPI_UP,
    CPI_DW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_BSPC, KC_SPC,  MO(2),   KC_LCMD,   KC_RCMD, MO(1),   KC_ENT
    ),
    [1] = LAYOUT(
        _______, KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, _______,   _______, KC_RPRN, KC_RCBR, KC_RBRC, KC_RABK, _______,
        _______, KC_LALT, KC_TILD, KC_GRV,  KC_PIPE, KC_BSLS,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ESC,  _______,
        _______, _______, _______, _______, _______, _______,   _______, CPI_UP,  CPI_DW,  _______, _______, _______,
                          _______, _______, _______, _______,   _______, _______, _______

    ),
    [2] = LAYOUT(
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_PEQL, KC_PPLS, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, SWITCH,  SCROLL,  KC_BTN2, KC_BTN1, _______,   _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______,   _______, _______, _______

    )
};


int8_t cpi_a      = 40;
int8_t cpi_n      = 125;
bool   scrolling = false;
bool   is_normal = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t  addr     = 0x14;
    uint8_t  data_n[] = {0x90, 0x00};
    uint8_t  data_a[] = {0x91, 0x00};
    uint16_t timeout  = 100;
    switch (keycode) {
        case SWITCH:
            if (record->event.pressed) {
                if (is_normal) {
                    i2c_transmit(addr, data_a, 2, timeout);
                    pimoroni_trackball_set_cpi(128 * cpi_a);
                    is_normal = false;
                } else {
                    i2c_transmit(addr, data_n, 2, timeout);
                    pimoroni_trackball_set_cpi(128 * cpi_n);
                    is_normal = true;
                }
            }
            break;
        case CPI_UP:
            if (record->event.pressed) {
                if (is_normal) {
                    cpi_n += 5;
                    pimoroni_trackball_set_cpi(128 * cpi_n);
                } else {
                    cpi_a += 5;
                    pimoroni_trackball_set_cpi(128 * cpi_a);
                }
            }
            break;
        case CPI_DW:
            if (record->event.pressed) {
                if (is_normal) {
                    cpi_n -= 5;
                    pimoroni_trackball_set_cpi(128 * cpi_n);
                } else {
                    cpi_a -= 5;
                    pimoroni_trackball_set_cpi(128 * cpi_a);
                }
            }
            break;
        case SCROLL:
            if (record->event.pressed) {
                i2c_transmit(addr, data_n, 2, timeout);
                pimoroni_trackball_set_cpi(128 * cpi_n);
            } else {
                if (!is_normal) {
                    i2c_transmit(addr, data_a, 2, timeout);
                    pimoroni_trackball_set_cpi(128 * cpi_a);
                }
            }
            scrolling = record->event.pressed;
            break;
        default:
            break;
    }
    return true;
}

void pointing_device_init_kb(void) {
    uint8_t  addr     = 0x14;
    uint8_t  data_a[] = {0x91, 0x00};
    uint16_t timeout  = 100;
    i2c_transmit(addr, data_a, 2, timeout);
    pimoroni_trackball_set_cpi(128 * cpi_a);
}

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H -8.0
#define SCROLL_DIVISOR_V -8.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (scrolling) {
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
