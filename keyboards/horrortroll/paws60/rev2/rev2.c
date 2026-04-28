// Copyright 2026 HorrorTroll <https://github.com/HorrorTroll>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rev2.h"
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    rgb_matrix_set_color(1, 0, 0, 0);

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(1, RGB_CYAN);
    } else if (!(rgb_matrix_get_flags() & LED_FLAG_INDICATOR)) {
        rgb_matrix_set_color(1, 0, 0, 0);
    }
    return true;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case CLR_CYC:
            if (record->event.pressed) {
                static uint8_t color_index;

                static const uint8_t colors[][3] = {
                    {HSV_ORANGE},
                    {HSV_YELLOW},
                    {HSV_GREEN},
                    {HSV_CYAN},
                    {HSV_BLUE},
                    {HSV_MAGENTA},
                    {242, 171, 217},
                    {HSV_RED},
                };

                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv(colors[color_index][0], colors[color_index][1], colors[color_index][2]);

                color_index = (color_index + 1) % (sizeof(colors) / sizeof(colors[0]));
            }

            return false;
        case RGB_ESC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
                rgb_matrix_sethsv(HSV_RED);
            }
            return false;
    }

    return true;
}
