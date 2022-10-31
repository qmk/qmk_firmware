// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later 
#include QMK_KEYBOARD_H
#ifdef FADER_ENABLE
#    include "fader.h"
#endif
#ifdef RGB_INDICATOR_ENABLE
#    include "rgb_indicator.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#    include <lib/lib8tion/lib8tion.h>
#    include "rgb_matrix_effects_custom.h"
#endif

#ifdef FADER_ENABLE
extern MidiDevice midi_device;
#endif
#ifdef RGB_MATRIX_ENABLE
extern bool fade_completed;
#endif

void eeconfig_init_kb(void) {
#ifdef RGB_INDICATOR_ENABLE
    eeconfig_init_rgb_indicator();
#endif
#ifdef FADER_ENABLE
    eeconfig_init_fader();
#endif
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;
#ifdef RGB_INDICATOR_ENABLE
    rgb_indicator_init();
#endif
#ifdef FADER_ENABLE
    fader_init();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_target_val();
#endif
    wait_ms(100);
    keyboard_post_init_user();
}

void matrix_scan_kb(void) {
#ifdef RGB_INDICATOR_ENABLE
    rgb_indicator_factory_test_runner();
#endif
#ifdef FADER_ENABLE
    fader_run(&midi_device);
#endif
#ifdef RGB_MATRIX_ENABLE
    if (!fade_completed) {
        if (rgb_matrix_fade_in()) {
            fade_completed = true;
        }
    }
#endif
    matrix_scan_user();
}

bool led_update_kb(led_t led_state) {
#ifdef RGB_INDICATOR_ENABLE
    bool res = led_update_user(led_state);
    if (res) {
        rgb_indicator_toggle(led_state.caps_lock);
    }
    return res;
#else
    return false;
#endif
}

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {{0, J_12, K_12, L_12}, {0, J_10, K_10, L_10}, {0, J_11, K_11, L_11}, {0, J_14, K_14, L_14}, {0, J_15, K_15, L_15}, {0, J_13, K_13, L_13}, {0, J_8, K_8, L_8},    {0, J_7, K_7, L_7},    {0, J_6, K_6, L_6},   {0, J_5, K_5, L_5}, {0, J_4, K_4, L_4}, {0, J_3, K_3, L_3}, {0, J_2, K_2, L_2}, {0, J_1, K_1, L_1},

                                                        {0, G_12, H_12, I_12}, {0, G_10, H_10, I_10}, {0, G_11, H_11, I_11}, {0, G_14, H_14, I_14}, {0, G_15, H_15, I_15}, {0, G_13, H_13, I_13}, {0, G_8, H_8, I_8},    {0, G_7, H_7, I_7},    {0, G_6, H_6, I_6},   {0, G_5, H_5, I_5}, {0, G_4, H_4, I_4}, {0, G_3, H_3, I_3}, {0, G_2, H_2, I_2}, {0, G_1, H_1, I_1},

                                                        {0, D_12, E_12, F_12}, {0, D_10, E_10, F_10}, {0, D_11, E_11, F_11}, {0, D_14, E_14, F_14}, {0, D_15, E_15, F_15}, {0, D_13, E_13, F_13}, {0, D_8, E_8, F_8},    {0, D_7, E_7, F_7},    {0, D_6, E_6, F_6},   {0, D_5, E_5, F_5}, {0, D_4, E_4, F_4}, {0, D_3, E_3, F_3}, {0, D_2, E_2, F_2},

                                                        {0, A_12, B_12, C_12}, {0, A_10, B_10, C_10}, {0, A_11, B_11, C_11}, {0, A_14, B_14, C_14}, {0, A_15, B_15, C_15}, {0, A_13, B_13, C_13}, {0, A_8, B_8, C_8},    {0, A_7, B_7, C_7},    {0, A_6, B_6, C_6},   {0, A_5, B_5, C_5}, {0, A_4, B_4, C_4}, {0, A_3, B_3, C_3}, {0, A_2, B_2, C_2},

                                                        {1, B_15, A_15, C_15}, {1, B_14, A_14, C_14}, {1, B_13, A_13, C_13}, {1, B_7, A_7, C_7},    {1, B_9, A_9, C_9},    {1, B_8, A_8, C_8},    {1, B_10, A_10, C_10}, {1, B_11, A_11, C_11}, {1, B_12, A_12, C_12}};

void rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        HSV hsv = rgb_matrix_get_hsv();
        RGB rgb;
        hsv.h = qadd8(hsv.h, 64);
        rgb   = hsv_to_rgb(hsv);
        RGB_MATRIX_INDICATOR_SET_COLOR(28, rgb.r, rgb.g, rgb.b);
    }
}
#endif