// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "report.h"
#include "test_pointing_device_driver.h"
#include <string.h>

typedef struct {
    bool pressed;
    bool dirty;
} pd_button_state_t;

typedef struct {
    int16_t           x;
    int16_t           y;
    int16_t           h;
    int16_t           v;
    pd_button_state_t button_state[8];
    uint16_t          cpi;
    bool              initiated;
} pd_config_t;

static pd_config_t pd_config = {0};

void pointing_device_driver_init(void) {
    pd_set_init(true);
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    for (uint8_t i = 0; i < 8; i++) {
        if (pd_config.button_state[i].dirty) {
            pd_config.button_state[i].dirty = false;
            if (pd_config.button_state[i].pressed) {
                mouse_report.buttons |= 1 << (i);
            } else {
                mouse_report.buttons &= ~(1 << (i));
            }
        }
    }
    mouse_report.x = pd_config.x;
    mouse_report.y = pd_config.y;
    mouse_report.h = pd_config.h;
    mouse_report.v = pd_config.v;
    return mouse_report;
}

__attribute__((weak)) uint16_t pointing_device_driver_get_cpi(void) {
    return pd_config.cpi;
}

__attribute__((weak)) void pointing_device_driver_set_cpi(uint16_t cpi) {
    pd_config.cpi = cpi;
}

void pd_press_button(uint8_t btn) {
    pd_config.button_state[btn].dirty   = true;
    pd_config.button_state[btn].pressed = true;
}
void pd_release_button(uint8_t btn) {
    pd_config.button_state[btn].dirty   = true;
    pd_config.button_state[btn].pressed = false;
}

void pd_clear_all_buttons(void) {
    for (uint8_t i = 0; i < 8; i++) {
        pd_config.button_state[i].dirty   = true;
        pd_config.button_state[i].pressed = false;
    }
}

void pd_set_x(int16_t x) {
    pd_config.x = x;
}

void pd_clear_x(void) {
    pd_set_x(0);
}

void pd_set_y(int16_t y) {
    pd_config.y = y;
}
void pd_clear_y(void) {
    pd_set_y(0);
}

void pd_set_h(int16_t h) {
    pd_config.h = h;
}
void pd_clear_h(void) {
    pd_set_h(0);
}

void pd_set_v(int16_t v) {
    pd_config.v = v;
}
void pd_clear_v(void) {
    pd_set_v(0);
}

void pd_clear_movement(void) {
    pd_set_x(0);
    pd_set_y(0);
    pd_set_h(0);
    pd_set_v(0);
}

void pd_set_init(bool success) {
    pd_config.initiated = success;
}
