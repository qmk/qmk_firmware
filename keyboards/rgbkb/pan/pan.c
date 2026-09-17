// Copyright 2020 RGBKB
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
#    include "ws2812.h"

static inline void setled(int i, uint8_t r, uint8_t g, uint8_t b) {
    if (i == 0 || i == 1) { // Encoder LEDs require GBR sequence
        ws2812_set_color(i, g, b, r);
    } else {
        ws2812_set_color(i, r, g, b);
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = ws2812_init,
    .flush         = ws2812_flush,
    .set_color     = setled,
    .set_color_all = ws2812_set_color_all,
};
#endif

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_write_P(PSTR("RGBKB Pan\n"), false);
    oled_write_P(PSTR("Layer: "), false);
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    switch (layer) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Colemak\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("Numlock On\n") : PSTR("           \n"), false);
    oled_write_P(led_state.caps_lock ? PSTR("Capslock On \n") : PSTR("           \n"), false);
    return false;
}
#endif
