// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "report.h"
#include "test_pointing_device_driver.h"
#include <string.h>

typedef struct {
    bool state;
    bool set;
} test_buttons_t;

static report_mouse_t test_report           = {0};
static uint16_t       test_cpi              = {0};
static test_buttons_t test_button_events[8] = {0};

void pointing_device_driver_init(void) {}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    test_report.buttons = 0;
    test_report.buttons = mouse_report.buttons; // buttons must currently be preserved by pointing device driver
    for (uint8_t i = 0; i < 8; i++) {
        if (test_button_events[i].set) {
            test_button_events[i].set = false;
            if (test_button_events[i].state) {
                test_report.buttons |= 1 << (i);
            } else {
                test_report.buttons &= ~(1 << (i));
            }
        }
    }
    return test_report;
}

__attribute__((weak)) uint16_t pointing_device_driver_get_cpi(void) {
    return test_cpi;
}

__attribute__((weak)) void pointing_device_driver_set_cpi(uint16_t cpi) {
    test_cpi = cpi;
}

void press_button(uint8_t btn) {
    test_button_events[btn].set   = true;
    test_button_events[btn].state = true;
}
void release_button(uint8_t btn) {
    test_button_events[btn].set   = true;
    test_button_events[btn].state = false;
}

void clear_all_buttons(void) {
    for (uint8_t i = 0; i < 8; i++) {
        test_button_events[i].set   = true;
        test_button_events[i].state = false;
    }
}

void set_x(int16_t x) {
    test_report.x = x;
}

void clear_x(void) {
    set_x(0);
}

void set_y(int16_t y) {
    test_report.y = y;
}
void clear_y(void) {
    set_y(0);
}

void set_h(int8_t h) {
    test_report.h = h;
}
void clear_h(void) {
    set_h(0);
}

void set_v(int8_t v) {
    test_report.v = v;
}
void clear_v(void) {
    set_v(0);
}

void clear_movement(void) {
    set_x(0);
    set_y(0);
    set_h(0);
    set_v(0);
}
