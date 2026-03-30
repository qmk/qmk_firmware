// Copyright 2023 NuPhy
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "color.h"
#include "common/rf_driver.h"

// Effect mode indices - must match keyboard side.h definitions
#ifndef SIDE_WAVE
#    define SIDE_WAVE 0
#endif
#ifndef SIDE_MIX
#    define SIDE_MIX 1
#endif
#ifndef SIDE_STATIC
#    define SIDE_STATIC 2
#endif
#ifndef SIDE_BREATH
#    define SIDE_BREATH 3
#endif
#ifndef SIDE_OFF
#    define SIDE_OFF 4
#endif

// Default values - keyboards can override via their side.h
#ifndef LIGHT_SPEED_MAX
#    define LIGHT_SPEED_MAX 4
#endif
#ifndef LIGHT_COLOR_MAX
#    define LIGHT_COLOR_MAX 8
#endif
#ifndef SIDE_COLOR_MAX
#    define SIDE_COLOR_MAX 8
#endif
#ifndef SIDE_LINE
#    define SIDE_LINE 5
#endif
#ifndef SIDE_LED_NUM
#    define SIDE_LED_NUM SIDE_LINE
#endif

// Table lengths - keyboards must define these in their side.h
#ifndef BREATHE_TAB_LEN
#    define BREATHE_TAB_LEN 128
#endif
#ifndef WAVE_TAB_LEN
#    define WAVE_TAB_LEN 112
#endif
#ifndef FLOW_COLOR_TAB_LEN
#    define FLOW_COLOR_TAB_LEN 224
#endif
#ifndef SIDE_MIX
#    define SIDE_MIX 1
#endif
#ifndef SIDE_STATIC
#    define SIDE_STATIC 2
#endif
#ifndef SIDE_BREATH
#    define SIDE_BREATH 3
#endif
#ifndef SIDE_OFF
#    define SIDE_OFF 4
#endif

// External tables - defined in keyboard-specific side.c
extern const uint8_t side_speed_table[5][5];
extern const uint8_t side_light_table[6];
extern const uint8_t side_led_index_tab[];
extern uint8_t       side_play_point;
extern uint8_t       side_play_cnt;
extern uint32_t      side_play_timer;
extern uint8_t       r_temp, g_temp, b_temp;

// LED array - defined in keyboard-specific side.c
extern RGB side_leds[];

// External state from other modules
extern bool            f_bat_hold;
extern DEV_INFO_STRUCT dev_info;

// Control functions (weak - can be overridden by keyboard)
__attribute__((weak)) void side_brightness_control(uint8_t brighten);
__attribute__((weak)) void side_speed_control(uint8_t dir);
__attribute__((weak)) void side_color_control(uint8_t dir);
__attribute__((weak)) void side_mode_control(uint8_t dir);

// Effect mode functions
void side_wave_mode_show(void);
void side_spectrum_mode_show(void);
void side_breathe_mode_show(void);
void side_static_mode_show(void);
void side_off_mode_show(void);

// Battery indicator functions
void bat_percent_led(uint8_t bat_percent);
void bat_charging_breathe(void);
void low_bat_show(void);

// Main side LED show function
void side_led_show(void);

// Helper functions
void side_rgb_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void side_rgb_refresh(void);
void set_side_rgb(uint8_t r, uint8_t g, uint8_t b);

// Initialization
void device_reset_init(void);
void device_reset_show(void);
void rgb_test_show(void);

// Keyboard-specific hooks (must be implemented by keyboard)
void side_led_show_kb(void);
void logo_led_loop(void);
void bat_led_show(void);
void kb_config_reset(void);

// External driver function
void side_ws2812_setleds(RGB *ledarray, uint16_t leds);
void rgb_matrix_update_pwm_buffers(void);
