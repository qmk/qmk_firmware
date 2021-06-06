#pragma once

#include "quantum.h"
#include "pointing_device.h"

#if defined(KEYBOARD_handwired_tractyl_manuform_5x6_right)
#    include "5x6_right.h"
#endif

void process_mouse(report_mouse_t* mouse_report);
void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y);

typedef union {
    uint32_t raw;
    struct {
        uint8_t dpi_config;
    };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;

enum ploopy_keycodes {
    DPI_CONFIG = SAFE_RANGE,
    KEYMAP_SAFE_RANGE,
};

void master_mouse_send(int8_t x, int8_t y);
void trackball_set_cpi(uint16_t cpi);
