// Copyright 2023 NuPhy
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdint.h>
#include "color.h"
#include "timer.h"
#include "common/side_effects.h"
#include "common/side_table.h"
#include "common/config.h"

// External state from keyboard-specific code
extern bool f_dial_sw_init_ok;

// Default weak implementations for control functions
__attribute__((weak)) void side_brightness_control(uint8_t brighten) {
    if (brighten) {
        if (keyboard_config.lights.side_brightness == 5) return;
        keyboard_config.lights.side_brightness++;
    } else {
        if (keyboard_config.lights.side_brightness == 0) return;
        keyboard_config.lights.side_brightness--;
    }
    save_config_to_eeprom();
}

__attribute__((weak)) void side_speed_control(uint8_t dir) {
    if (dir) {
        if ((keyboard_config.lights.side_speed) > LIGHT_SPEED_MAX) keyboard_config.lights.side_speed = LIGHT_SPEED_MAX / 2;
        if (keyboard_config.lights.side_speed) keyboard_config.lights.side_speed--;
    } else {
        if (keyboard_config.lights.side_speed < LIGHT_SPEED_MAX) keyboard_config.lights.side_speed++;
    }
    save_config_to_eeprom();
}

__attribute__((weak)) void side_color_control(uint8_t dir) {
    if (keyboard_config.lights.side_mode != SIDE_WAVE) {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb   = 0;
            keyboard_config.lights.side_color = 0;
        }
        if (dir) {
            if (keyboard_config.lights.side_rgb) {
                keyboard_config.lights.side_rgb = 0;
            }
            keyboard_config.lights.side_color++;
            if (keyboard_config.lights.side_color >= LIGHT_COLOR_MAX) {
                keyboard_config.lights.side_rgb   = 1;
                keyboard_config.lights.side_color = 0;
            }
        } else {
            if (keyboard_config.lights.side_rgb) {
                keyboard_config.lights.side_rgb   = 0;
                keyboard_config.lights.side_color = LIGHT_COLOR_MAX - 1;
            } else {
                keyboard_config.lights.side_color--;
            }
            if (keyboard_config.lights.side_color >= LIGHT_COLOR_MAX) {
                keyboard_config.lights.side_rgb   = 1;
                keyboard_config.lights.side_color = 0;
            }
        }
        save_config_to_eeprom();
    }
}

__attribute__((weak)) void side_mode_control(uint8_t dir) {
    if (dir) {
        keyboard_config.lights.side_mode++;
        if (keyboard_config.lights.side_mode > SIDE_OFF) {
            keyboard_config.lights.side_mode = 0;
        }
    } else {
        if (keyboard_config.lights.side_mode > 0) {
            keyboard_config.lights.side_mode--;
        } else {
            keyboard_config.lights.side_mode = SIDE_OFF;
        }
    }
    save_config_to_eeprom();
}

// Helper functions - weak implementations
__attribute__((weak)) void side_rgb_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    side_leds[index].r = red;
    side_leds[index].g = green;
    side_leds[index].b = blue;
}

__attribute__((weak)) void set_side_rgb(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < SIDE_LINE; i++) {
        side_rgb_set_color(side_led_index_tab[i], r, g, b);
    }
}

static void count_rgb_light(uint8_t light_temp) {
    uint16_t temp;
    temp   = (light_temp)*r_temp + r_temp;
    r_temp = temp >> 8;
    temp   = (light_temp)*g_temp + g_temp;
    g_temp = temp >> 8;
    temp   = (light_temp)*b_temp + b_temp;
    b_temp = temp >> 8;
}

static void light_point_playing(uint8_t trend, uint8_t step, uint8_t len, uint8_t *point) {
    if (trend) {
        *point += step;
        if (*point >= len) *point -= len;
    } else {
        *point -= step;
        if (*point >= len) *point = len - (255 - *point) - 1;
    }
}

// Effect mode implementations
void side_wave_mode_show(void) {
    uint8_t play_index;

    if (side_play_cnt <= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (keyboard_config.lights.side_rgb)
        light_point_playing(0, 1, FLOW_COLOR_TAB_LEN, &side_play_point);
    else
        light_point_playing(0, 2, WAVE_TAB_LEN, &side_play_point);

    play_index = side_play_point;

    count_rgb_light(side_light_table[keyboard_config.lights.side_brightness]);

    for (int i = 0; i < SIDE_LINE; i++) {
        if (keyboard_config.lights.side_rgb) {
            r_temp = flow_rainbow_color_tab[play_index][0];
            g_temp = flow_rainbow_color_tab[play_index][1];
            b_temp = flow_rainbow_color_tab[play_index][2];
            light_point_playing(1, 8, FLOW_COLOR_TAB_LEN, &play_index);
        } else {
            r_temp = side_color_lib[keyboard_config.lights.side_color][0];
            g_temp = side_color_lib[keyboard_config.lights.side_color][1];
            b_temp = side_color_lib[keyboard_config.lights.side_color][2];
            light_point_playing(1, 12, WAVE_TAB_LEN, &play_index);
            count_rgb_light(wave_data_tab[play_index]);
        }
        count_rgb_light(side_light_table[keyboard_config.lights.side_brightness]);
        side_rgb_set_color(side_led_index_tab[i], r_temp >> 2, g_temp >> 2, b_temp >> 2);
    }
}

void side_spectrum_mode_show(void) {
    if (side_play_cnt <= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    light_point_playing(1, 1, FLOW_COLOR_TAB_LEN, &side_play_point);

    r_temp = flow_rainbow_color_tab[side_play_point][0];
    g_temp = flow_rainbow_color_tab[side_play_point][1];
    b_temp = flow_rainbow_color_tab[side_play_point][2];

    count_rgb_light(side_light_table[keyboard_config.lights.side_brightness]);

    for (int i = 0; i < SIDE_LINE; i++) {
        side_rgb_set_color(side_led_index_tab[i], r_temp >> 2, g_temp >> 2, b_temp >> 2);
    }
}

void side_breathe_mode_show(void) {
    static uint8_t play_point = 0;

    if (side_play_cnt <= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);

    r_temp = side_color_lib[keyboard_config.lights.side_color][0] >> 2;
    g_temp = side_color_lib[keyboard_config.lights.side_color][1] >> 2;
    b_temp = side_color_lib[keyboard_config.lights.side_color][2] >> 2;

    count_rgb_light(breathe_data_tab[play_point]);
    count_rgb_light(side_light_table[keyboard_config.lights.side_brightness]);

    set_side_rgb(r_temp, g_temp, b_temp);
}

void side_static_mode_show(void) {
    if (side_play_point >= SIDE_COLOR_MAX) side_play_point = 0;

    r_temp = side_color_lib[keyboard_config.lights.side_color][0] >> 2;
    g_temp = side_color_lib[keyboard_config.lights.side_color][1] >> 2;
    b_temp = side_color_lib[keyboard_config.lights.side_color][2] >> 2;

    count_rgb_light(side_light_table[keyboard_config.lights.side_brightness]);

    for (int i = 0; i < SIDE_LINE; i++) {
        side_rgb_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
    }
}

void side_off_mode_show(void) {
    if (side_play_cnt <= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    r_temp = 0x00;
    g_temp = 0x00;
    b_temp = 0x00;

    set_side_rgb(r_temp >> 2, g_temp >> 2, b_temp >> 2);
}

// Battery indicator functions
__attribute__((weak)) void bat_percent_led(uint8_t bat_percent) {
    uint8_t i;
    uint8_t bat_end_led = 0;
    uint8_t bat_r, bat_g, bat_b;

    if (bat_percent <= 20) {
        bat_end_led = 0;
        bat_r = 0x80, bat_g = 0, bat_b = 0;
    } else if (bat_percent <= 40) {
        bat_end_led = 1;
        bat_r = 0x80, bat_g = 0x40, bat_b = 0;
    } else if (bat_percent <= 60) {
        bat_end_led = 2;
        bat_r = 0x80, bat_g = 0x80, bat_b = 0;
    } else if (bat_percent <= 80) {
        bat_end_led = 3;
        bat_r = 0x40, bat_g = 0x80, bat_b = 0;
    } else {
        bat_end_led = SIDE_LINE - 1;
        bat_r = 0, bat_g = 0x80, bat_b = 0;
    }

    for (i = 0; i < SIDE_LINE; i++) {
        if (i <= bat_end_led) {
            side_rgb_set_color(side_led_index_tab[i], bat_r >> 2, bat_g >> 2, bat_b >> 2);
        } else {
            side_rgb_set_color(side_led_index_tab[i], 0x00, 0x00, 0x00);
        }
    }
}

void bat_charging_breathe(void) {
    static uint32_t interval_timer = 0;
    static uint8_t  play_point     = 0;

    if (timer_elapsed32(interval_timer) > 10) {
        interval_timer = timer_read32();
        light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);
    }

    r_temp = 0x80;
    g_temp = 0x40;
    b_temp = 0x00;
    count_rgb_light(breathe_data_tab[play_point]);
    set_side_rgb(r_temp, g_temp, b_temp);
}

// Main side LED show function
__attribute__((weak)) void side_led_show(void) {
    static bool flag_power_on = 1;

    if (flag_power_on) {
        if (!f_dial_sw_init_ok) return;
        flag_power_on = 0;
    }

    side_play_cnt += timer_elapsed32(side_play_timer);
    side_play_timer = timer_read32();

    switch (keyboard_config.lights.side_mode) {
        case SIDE_WAVE:
            side_wave_mode_show();
            break;
        case SIDE_MIX:
            side_spectrum_mode_show();
            break;
        case SIDE_BREATH:
            side_breathe_mode_show();
            break;
        case SIDE_STATIC:
            side_static_mode_show();
            break;
        case SIDE_OFF:
            side_off_mode_show();
            break;
    }

    // Keyboard-specific hooks
    bat_led_show();
    side_led_show_kb();
}

// Weak keyboard-specific hooks
__attribute__((weak)) void side_led_show_kb(void) {}
__attribute__((weak)) void bat_led_show(void) {}
__attribute__((weak)) void logo_led_loop(void) {}
__attribute__((weak)) void side_rgb_refresh(void) {}
__attribute__((weak)) void device_reset_init(void) {}
__attribute__((weak)) void device_reset_show(void) {}
__attribute__((weak)) void rgb_test_show(void) {}
__attribute__((weak)) void kb_config_reset(void) {}
__attribute__((weak)) void low_bat_show(void) {}
