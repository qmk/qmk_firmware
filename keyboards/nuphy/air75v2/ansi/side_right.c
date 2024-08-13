// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "ansi.h"
#include "rgb_matrix.h"
#include "side.h"
#include "timer.h"

extern const uint8_t side_speed_table[6][5];
extern const uint8_t side_light_table[6];
extern const uint8_t light_value_tab[101];
extern const uint8_t breathe_data_tab[BREATHE_TAB_LEN];
extern const uint8_t wave_data_tab[WAVE_TAB_LEN];
extern const uint8_t flow_rainbow_color_tab[FLOW_COLOR_TAB_LEN][3];
extern const uint8_t side_color_lib[9][3];
extern uint8_t       r_temp, g_temp, b_temp;
extern void          side_rgb_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);

const uint8_t right_side_led_index_tab[RIGHT_SIDE_LINE] = {
    6, 7, 8, 9, 10, 11,
};

uint8_t  right_side_play_point = 0;
uint8_t  right_side_play_cnt   = 0;
uint32_t right_side_play_timer = 0;

void right_side_light_level_control(uint8_t brighten) {
    if (brighten) {
        if (g_config.right_side_brightness == 5) {
            return;
        } else
            g_config.right_side_brightness++;
    } else {
        if (g_config.right_side_brightness == 0) {
            return;
        } else
            g_config.right_side_brightness--;
    }
    save_config_to_eeprom();
}

void right_side_light_speed_contol(uint8_t fast) {
    if ((g_config.right_side_speed) > LIGHT_SPEED_MAX) (g_config.right_side_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if ((g_config.right_side_speed)) g_config.right_side_speed--;
    } else {
        if ((g_config.right_side_speed) < LIGHT_SPEED_MAX) g_config.right_side_speed++;
    }
    save_config_to_eeprom();
}

void right_side_side_color_control(uint8_t dir) {
    if (g_config.right_side_mode != SIDE_WAVE) {
        if (g_config.right_side_rgb) {
            g_config.right_side_rgb   = 0;
            g_config.right_side_color = 0;
        }
    }

    if (dir) {
        if (g_config.right_side_rgb) {
            g_config.right_side_rgb   = 0;
            g_config.right_side_color = 0;
        } else {
            g_config.right_side_color++;
            if (g_config.right_side_color >= LIGHT_COLOR_MAX) {
                g_config.right_side_rgb   = 1;
                g_config.right_side_color = 0;
            }
        }
    } else {
        if (g_config.right_side_rgb) {
            g_config.right_side_rgb   = 0;
            g_config.right_side_color = LIGHT_COLOR_MAX - 1;
        } else {
            g_config.right_side_color--;
            if (g_config.right_side_color >= LIGHT_COLOR_MAX) {
                g_config.right_side_rgb   = 1;
                g_config.right_side_color = 0;
            }
        }
    }
    save_config_to_eeprom();
}

void right_side_side_mode_control(uint8_t dir) {
    if (dir) {
        g_config.right_side_mode++;
        if (g_config.right_side_mode > SIDE_OFF) {
            g_config.right_side_mode = 0;
        }
    } else {
        if (g_config.right_side_mode > 0) {
            g_config.right_side_mode--;
        } else {
            g_config.right_side_mode = SIDE_OFF;
        }
    }
    right_side_play_point = 0;
    save_config_to_eeprom();
}

void set_right_side_rgb(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = SIDE_LINE; i < SIDE_LED_NUM; i++)
        side_rgb_set_color(i, r >> 2, g >> 2, b >> 2);
}

static void right_side_light_point_playing(uint8_t trend, uint8_t step, uint8_t len, uint8_t *point) {
    if (trend) {
        *point += step;
        if (*point >= len) *point -= len;
    } else {
        *point -= step;
        if (*point >= len) *point = len - (255 - *point) - 1;
    }
}

static void right_side_count_rgb_light(uint8_t light_temp) {
    uint16_t temp;

    temp   = (light_temp)*r_temp + r_temp;
    r_temp = temp >> 8;

    temp   = (light_temp)*g_temp + g_temp;
    g_temp = temp >> 8;

    temp   = (light_temp)*b_temp + b_temp;
    b_temp = temp >> 8;
}

static void right_side_wave_mode_show(void) {
    uint8_t play_index;

    //------------------------------
    if (right_side_play_cnt <= side_speed_table[g_config.right_side_mode][g_config.right_side_speed])
        return;
    else
        right_side_play_cnt -= side_speed_table[g_config.right_side_mode][g_config.right_side_speed];
    if (right_side_play_cnt > 20) right_side_play_cnt = 0;

    //------------------------------
    if (g_config.right_side_rgb)
        right_side_light_point_playing(0, 1, FLOW_COLOR_TAB_LEN, &right_side_play_point);
    else
        right_side_light_point_playing(0, 1, WAVE_TAB_LEN, &right_side_play_point);

    play_index = right_side_play_point;

    for (int i = 0; i < RIGHT_SIDE_LINE; i++) {
        if (g_config.right_side_rgb) {
            r_temp = flow_rainbow_color_tab[play_index][0];
            g_temp = flow_rainbow_color_tab[play_index][1];
            b_temp = flow_rainbow_color_tab[play_index][2];

            right_side_light_point_playing(1, 5, FLOW_COLOR_TAB_LEN, &play_index);
        } else {
            r_temp = side_color_lib[g_config.right_side_color][0];
            g_temp = side_color_lib[g_config.right_side_color][1];
            b_temp = side_color_lib[g_config.right_side_color][2];

            right_side_light_point_playing(1, 12, WAVE_TAB_LEN, &play_index);
            right_side_count_rgb_light(wave_data_tab[play_index]);
        }

        right_side_count_rgb_light(side_light_table[g_config.right_side_brightness]);

        side_rgb_set_color(right_side_led_index_tab[i], r_temp >> 1, g_temp >> 1, b_temp >> 1);
    }
}

static void right_side_spectrum_mode_show(void) {
    if (right_side_play_cnt <= side_speed_table[g_config.right_side_mode][g_config.right_side_speed])
        return;
    else
        right_side_play_cnt -= side_speed_table[g_config.right_side_mode][g_config.right_side_speed];
    if (right_side_play_cnt > 20) right_side_play_cnt = 0;

    right_side_light_point_playing(1, 1, FLOW_COLOR_TAB_LEN, &right_side_play_point);

    r_temp = flow_rainbow_color_tab[right_side_play_point][0];
    g_temp = flow_rainbow_color_tab[right_side_play_point][1];
    b_temp = flow_rainbow_color_tab[right_side_play_point][2];

    right_side_count_rgb_light(side_light_table[g_config.right_side_brightness]);

    for (int i = 0; i < RIGHT_SIDE_LINE; i++) {
        side_rgb_set_color(right_side_led_index_tab[i], r_temp >> 2, g_temp >> 2, b_temp >> 2);
    }
}

static void right_side_breathe_mode_show(void) {
    static uint8_t play_point = 0;

    if (right_side_play_cnt <= side_speed_table[g_config.right_side_mode][g_config.right_side_speed])
        return;
    else
        right_side_play_cnt -= side_speed_table[g_config.right_side_mode][g_config.right_side_speed];
    if (right_side_play_cnt > 20) right_side_play_cnt = 0;

    right_side_light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);

    r_temp = side_color_lib[g_config.right_side_color][0] >> 2;
    g_temp = side_color_lib[g_config.right_side_color][1] >> 2;
    b_temp = side_color_lib[g_config.right_side_color][2] >> 2;

    right_side_count_rgb_light(breathe_data_tab[play_point]);
    right_side_count_rgb_light(side_light_table[g_config.right_side_brightness]);

    set_right_side_rgb(r_temp, g_temp, b_temp);
}

static void right_side_static_mode_show(void) {
    if (right_side_play_point >= SIDE_COLOR_MAX) right_side_play_point = 0;

    if (g_config.right_side_use_custom_color) {
        HSV hsv = g_config.right_side_custom_color;
        hsv.v   = rgb_matrix_config.hsv.v;
        RGB rgb = hsv_to_rgb(hsv);
        r_temp  = rgb.r;
        g_temp  = rgb.g;
        b_temp  = rgb.b;
    } else {
        r_temp = side_color_lib[g_config.right_side_color][0] >> 2;
        g_temp = side_color_lib[g_config.right_side_color][1] >> 2;
        b_temp = side_color_lib[g_config.right_side_color][2] >> 2;
    }

    right_side_count_rgb_light(side_light_table[g_config.right_side_brightness]);

    set_right_side_rgb(r_temp, g_temp, b_temp);
}

static void right_side_off_mode_show(void) {
    if (right_side_play_cnt <= side_speed_table[g_config.right_side_mode][g_config.right_side_speed])
        return;
    else
        right_side_play_cnt -= side_speed_table[g_config.right_side_mode][g_config.right_side_speed];
    if (right_side_play_cnt > 20) right_side_play_cnt = 0;

    r_temp = 0x00;
    g_temp = 0x00;
    b_temp = 0x00;

    for (int i = 0; i < RIGHT_SIDE_LINE; i++) {
        side_rgb_set_color(right_side_led_index_tab[i], r_temp >> 2, g_temp >> 2, b_temp >> 2);
    }
}

void right_side_led_loop(void) {
    right_side_play_cnt += timer_elapsed32(right_side_play_timer);
    right_side_play_timer = timer_read32();

    switch (g_config.right_side_mode) {
        case SIDE_WAVE:
            right_side_wave_mode_show();
            break;
        case SIDE_MIX:
            right_side_spectrum_mode_show();
            break;
        case SIDE_BREATH:
            right_side_breathe_mode_show();
            break;
        case SIDE_STATIC:
            right_side_static_mode_show();
            break;
        case SIDE_OFF:
            right_side_off_mode_show();
            break;
    }
}
