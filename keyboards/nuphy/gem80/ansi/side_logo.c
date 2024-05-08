// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "ansi.h"
#include "side.h"
#include "timer.h"

extern const uint8_t side_speed_table[6][5];
extern const uint8_t side_light_table[6];
extern const uint8_t light_value_tab[101];
extern const uint8_t breathe_data_tab[BREATHE_TAB_LEN];
extern const uint8_t wave_data_tab[WAVE_TAB_LEN];
extern const uint8_t flow_rainbow_colour_tab[FLOW_COLOUR_TAB_LEN][3];
extern const uint8_t colour_lib[9][3];
extern uint8_t       r_temp, g_temp, b_temp;
extern void          side_rgb_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);

const uint8_t logo_led_index_tab[LOGO_LINE] = {
    5, 6, 7, 8, 9, 10, 11,
};

uint8_t  logo_play_point = 0;
uint8_t  logo_play_cnt   = 0;
uint32_t logo_play_timer = 0;

void logo_light_level_control(uint8_t brighten) {
    if (brighten) {
        if (g_config.logo_brightness == 5) {
            return;
        } else
            g_config.logo_brightness++;
    } else {
        if (g_config.logo_brightness == 0) {
            return;
        } else
            g_config.logo_brightness--;
    }
    save_config_to_eeprom();
}

void logo_light_speed_contol(uint8_t fast) {
    if ((g_config.logo_speed) > LIGHT_SPEED_MAX) (g_config.logo_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if ((g_config.logo_speed)) g_config.logo_speed--;
    } else {
        if ((g_config.logo_speed) < LIGHT_SPEED_MAX) g_config.logo_speed++;
    }
    save_config_to_eeprom();
}

void logo_side_colour_control(uint8_t dir) {
    if (g_config.logo_mode != SIDE_WAVE) {
        if (g_config.logo_rgb) {
            g_config.logo_rgb   = 0;
            g_config.logo_color = 0;
        }
    }

    if (dir) {
        if (g_config.logo_rgb) {
            g_config.logo_rgb   = 0;
            g_config.logo_color = 0;
        } else {
            g_config.logo_color++;
            if (g_config.logo_color >= LIGHT_COLOUR_MAX) {
                g_config.logo_rgb   = 1;
                g_config.logo_color = 0;
            }
        }
    } else {
        if (g_config.logo_rgb) {
            g_config.logo_rgb   = 0;
            g_config.logo_color = LIGHT_COLOUR_MAX - 1;
        } else {
            g_config.logo_color--;
            if (g_config.logo_color >= LIGHT_COLOUR_MAX) {
                g_config.logo_rgb   = 1;
                g_config.logo_color = 0;
            }
        }
    }
    save_config_to_eeprom();
}

void logo_side_mode_control(uint8_t dir) {
    if (dir) {
        g_config.logo_mode++;
        if (g_config.logo_mode > SIDE_OFF) {
            g_config.logo_mode = 0;
        }
    } else {
        if (g_config.logo_mode > 0) {
            g_config.logo_mode--;
        } else {
            g_config.logo_mode = SIDE_OFF;
        }
    }
    logo_play_point = 0;
    save_config_to_eeprom();
}

void set_logo_rgb(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 5; i < 12; i++)
        side_rgb_set_color(i, r >> 2, g >> 2, b >> 2);
}

static void logo_light_point_playing(uint8_t trend, uint8_t step, uint8_t len, uint8_t *point) {
    if (trend) {
        *point += step;
        if (*point >= len) *point -= len;
    } else {
        *point -= step;
        if (*point >= len) *point = len - (255 - *point) - 1;
    }
}

static void logo_count_rgb_light(uint8_t light_temp) {
    uint16_t temp;

    temp   = (light_temp)*r_temp + r_temp;
    r_temp = temp >> 8;

    temp   = (light_temp)*g_temp + g_temp;
    g_temp = temp >> 8;

    temp   = (light_temp)*b_temp + b_temp;
    b_temp = temp >> 8;
}

static void logo_wave_mode_show(void) {
    uint8_t play_index;

    //------------------------------
    if (logo_play_cnt <= side_speed_table[g_config.logo_mode][g_config.logo_speed])
        return;
    else
        logo_play_cnt -= side_speed_table[g_config.logo_mode][g_config.logo_speed];
    if (logo_play_cnt > 20) logo_play_cnt = 0;

    //------------------------------
    if (g_config.logo_rgb)
        logo_light_point_playing(0, 1, FLOW_COLOUR_TAB_LEN, &logo_play_point);
    else
        logo_light_point_playing(0, 1, WAVE_TAB_LEN, &logo_play_point);

    play_index = logo_play_point;
    for (int i = 0; i < LOGO_LINE; i++) {
        if (g_config.logo_rgb) {
            r_temp = flow_rainbow_colour_tab[play_index][0];
            g_temp = flow_rainbow_colour_tab[play_index][1];
            b_temp = flow_rainbow_colour_tab[play_index][2];

            logo_light_point_playing(1, 5, FLOW_COLOUR_TAB_LEN, &play_index);
        } else {
            r_temp = colour_lib[g_config.logo_color][0];
            g_temp = colour_lib[g_config.logo_color][1];
            b_temp = colour_lib[g_config.logo_color][2];

            logo_light_point_playing(1, 12, WAVE_TAB_LEN, &play_index);
            logo_count_rgb_light(wave_data_tab[play_index]);
        }

        logo_count_rgb_light(side_light_table[g_config.logo_brightness]);
        side_rgb_set_color(logo_led_index_tab[i], r_temp >> 1, g_temp >> 1, b_temp >> 1);
    }
}

static void logo_spectrum_mode_show(void) {
    if (logo_play_cnt <= side_speed_table[g_config.logo_mode][g_config.logo_speed])
        return;
    else
        logo_play_cnt -= side_speed_table[g_config.logo_mode][g_config.logo_speed];
    if (logo_play_cnt > 20) logo_play_cnt = 0;

    logo_light_point_playing(1, 1, FLOW_COLOUR_TAB_LEN, &logo_play_point);

    r_temp = flow_rainbow_colour_tab[logo_play_point][0];
    g_temp = flow_rainbow_colour_tab[logo_play_point][1];
    b_temp = flow_rainbow_colour_tab[logo_play_point][2];

    logo_count_rgb_light(side_light_table[g_config.logo_brightness]);

    for (int i = 0; i < LOGO_LINE; i++) {
        side_rgb_set_color(logo_led_index_tab[i], r_temp >> 2, g_temp >> 2, b_temp >> 2);
    }
}

static void logo_breathe_mode_show(void) {
    static uint8_t play_point = 0;

    if (logo_play_cnt <= side_speed_table[g_config.logo_mode][g_config.logo_speed])
        return;
    else
        logo_play_cnt -= side_speed_table[g_config.logo_mode][g_config.logo_speed];
    if (logo_play_cnt > 20) logo_play_cnt = 0;

    logo_light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);

    if (0) {
        if (play_point == 0) {
            if (++logo_play_point >= LIGHT_COLOUR_MAX) logo_play_point = 0;
        }

        r_temp = colour_lib[logo_play_point][0];
        g_temp = colour_lib[logo_play_point][1];
        b_temp = colour_lib[logo_play_point][2];
    } else {
        r_temp = colour_lib[g_config.logo_color][0];
        g_temp = colour_lib[g_config.logo_color][1];
        b_temp = colour_lib[g_config.logo_color][2];
    }

    logo_count_rgb_light(breathe_data_tab[play_point]);
    logo_count_rgb_light(side_light_table[g_config.logo_brightness]);

    for (int i = 0; i < LOGO_LINE; i++) {
        side_rgb_set_color(logo_led_index_tab[i], r_temp >> 2, g_temp >> 2, b_temp >> 2);
    }
}

static void logo_static_mode_show(void) {
    uint8_t play_index;

    if (logo_play_cnt <= side_speed_table[g_config.logo_mode][g_config.logo_speed])
        return;
    else
        logo_play_cnt -= side_speed_table[g_config.logo_mode][g_config.logo_speed];
    if (logo_play_cnt > 20) logo_play_cnt = 0;

    if (logo_play_point >= SIDE_COLOUR_MAX) logo_play_point = 0;

    for (int i = 0; i < LOGO_LINE; i++) {
        if (0) {
            r_temp = flow_rainbow_colour_tab[16 * i][0];
            g_temp = flow_rainbow_colour_tab[16 * i][1];
            b_temp = flow_rainbow_colour_tab[16 * i][2];
            logo_light_point_playing(0, 24, FLOW_COLOUR_TAB_LEN, &play_index);
        } else {
            r_temp = colour_lib[g_config.logo_color][0];
            g_temp = colour_lib[g_config.logo_color][1];
            b_temp = colour_lib[g_config.logo_color][2];
        }

        logo_count_rgb_light(side_light_table[g_config.logo_brightness]);

        side_rgb_set_color(logo_led_index_tab[i], r_temp >> 2, g_temp >> 2, b_temp >> 2);
    }
}

static void logo_off_mode_show(void) {
    if (logo_play_cnt <= side_speed_table[g_config.logo_mode][g_config.logo_speed])
        return;
    else
        logo_play_cnt -= side_speed_table[g_config.logo_mode][g_config.logo_speed];
    if (logo_play_cnt > 20) logo_play_cnt = 0;

    r_temp = 0x00;
    g_temp = 0x00;
    b_temp = 0x00;

    for (int i = 0; i < LOGO_LINE; i++) {
        side_rgb_set_color(logo_led_index_tab[i], r_temp >> 2, g_temp >> 2, b_temp >> 2);
    }
}

void logo_led_loop(void) {
    logo_play_cnt += timer_elapsed32(logo_play_timer);
    logo_play_timer = timer_read32();

    switch (g_config.logo_mode) {
        case SIDE_WAVE:
            logo_wave_mode_show();
            break;
        case SIDE_MIX:
            logo_spectrum_mode_show();
            break;
        case SIDE_BREATH:
            logo_breathe_mode_show();
            break;
        case SIDE_STATIC:
            logo_static_mode_show();
            break;
        case SIDE_OFF:
            logo_off_mode_show();
            break;
    }
}
