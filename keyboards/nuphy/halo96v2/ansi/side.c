/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ansi.h"
#include "rgb_matrix.h"
#include "user_kb.h"
#include "side.h"

#define SIDE_WAVE 0
#define SIDE_MIX 1
#define SIDE_NEW 2
#define SIDE_BREATH 3
#define SIDE_STATIC 4

#define SIDE_MODE_1 0
#define SIDE_MODE_2 1
#define SIDE_MODE_3 2
#define SIDE_MODE_4 3
#define SIDE_MODE_5 4
#define SIDE_MODE_6 5
#define SIDE_MODE_7 6

#define LIGHT_COLOR_MAX 8
#define SIDE_COLOR_MAX 8
#define LIGHT_SPEED_MAX 4

const uint8_t side_speed_table[5][5] = {
    [SIDE_WAVE] = {6, 14, 20, 25, 40}, [SIDE_MIX] = {10, 20, 25, 30, 45}, [SIDE_NEW] = {30, 50, 60, 70, 100}, [SIDE_BREATH] = {10, 20, 25, 30, 45}, [SIDE_STATIC] = {10, 20, 25, 30, 45},
};

#define SIDE_BLINK_LIGHT 128
const uint8_t side_light_table[5] = {
    0, 64, 128, 192, 255,
};

#define SIDE_INDEX 99

const uint8_t side_led_index_tab[45] = {
    SIDE_INDEX + 10, SIDE_INDEX + 11, SIDE_INDEX + 12, SIDE_INDEX + 13, SIDE_INDEX + 14, SIDE_INDEX + 15, SIDE_INDEX + 16, SIDE_INDEX + 17, SIDE_INDEX + 18, SIDE_INDEX + 19, SIDE_INDEX + 20, SIDE_INDEX + 21, SIDE_INDEX + 22, SIDE_INDEX + 23, SIDE_INDEX + 0, SIDE_INDEX + 1, SIDE_INDEX + 2, SIDE_INDEX + 3, SIDE_INDEX + 4, SIDE_INDEX + 24, SIDE_INDEX + 25, SIDE_INDEX + 26, SIDE_INDEX + 27, SIDE_INDEX + 28, SIDE_INDEX + 29, SIDE_INDEX + 30, SIDE_INDEX + 31, SIDE_INDEX + 32, SIDE_INDEX + 33, SIDE_INDEX + 34, SIDE_INDEX + 35, SIDE_INDEX + 36, SIDE_INDEX + 37, SIDE_INDEX + 38, SIDE_INDEX + 39, SIDE_INDEX + 40, SIDE_INDEX + 41, SIDE_INDEX + 42, SIDE_INDEX + 43, SIDE_INDEX + 44, SIDE_INDEX + 9, SIDE_INDEX + 8, SIDE_INDEX + 7, SIDE_INDEX + 6, SIDE_INDEX + 5,
};

const uint8_t side_rgb_parallel[45] = {
    1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

uint8_t side_line = 45;

bool     f_charging      = 1;
uint8_t  side_play_point = 0;
uint32_t bat_show_time   = 0;
bool     bat_show_flag   = true;

uint16_t side_play_cnt   = 0;
uint32_t side_play_timer = 0;

uint8_t r_temp, g_temp, b_temp;

extern DEV_INFO_STRUCT dev_info;
extern bool            f_bat_hold;
extern kb_config_t     g_config;
extern uint16_t        rf_link_show_time;

/**
 * @brief suspend_power_down_kb
 *
 */
void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
}

/**
 * @brief  Adjusting the brightness of side lights.
 * @param  dir: 0 - decrease, 1 - increase.
 * @note  save to eeprom.
 */
void light_level_control(uint8_t brighten) {
    if (brighten) {
        if (g_config.side_brightness == 4) {
            return;
        } else
            g_config.side_brightness++;
    } else {
        if (g_config.side_brightness == 0) {
            return;
        } else
            g_config.side_brightness--;
    }
    save_config_to_eeprom();
}

/**
 * @brief  Adjusting the speed of side lights.
 * @param  dir: 0 - decrease, 1 - increase.
 * @note  save to eeprom.
 */
void light_speed_control(uint8_t fast) {
    if ((g_config.side_speed) > LIGHT_SPEED_MAX) (g_config.side_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if ((g_config.side_speed)) g_config.side_speed--;
    } else {
        if ((g_config.side_speed) < LIGHT_SPEED_MAX) g_config.side_speed++;
    }
    save_config_to_eeprom();
}

/**
 * @brief  Switch to the next color of side lights.
 * @param  dir: 0 - prev, 1 - next.
 * @note  save to eeprom.
 */
uint8_t light_color_max = 8;
void    side_color_control(uint8_t dir) {
    if (g_config.side_mode_a == SIDE_NEW) {
        light_color_max = 3;
    } else
        light_color_max = 8;
    if ((g_config.side_mode_a != SIDE_WAVE) && (g_config.side_mode_a != SIDE_BREATH)) {
        if (g_config.side_rgb) {
            g_config.side_rgb   = 0;
            g_config.side_color = 0;
        }
    }

    if (dir) {
        if (g_config.side_rgb) {
            g_config.side_rgb   = 0;
            g_config.side_color = 0;
        } else {
            g_config.side_color++;
            if (g_config.side_color >= light_color_max) {
                g_config.side_rgb   = 1;
                g_config.side_color = 0;
            }
        }
    } else {
        if (g_config.side_rgb) {
            g_config.side_rgb   = 0;
            g_config.side_color = light_color_max - 1;
        } else {
            g_config.side_color--;
            if (g_config.side_color >= light_color_max) {
                g_config.side_rgb   = 1;
                g_config.side_color = 0;
            }
        }
    }
    save_config_to_eeprom();
}

/**
 * @brief  Change the color mode of side lights.
 * @param  dir: 0 - prev, 1 - next.
 * @note  save to eeprom.
 */
uint8_t side_old_color = 0;
uint8_t side_new_color = 0;
void    side_mode_a_control(uint8_t dir) {
    if (dir) {
        g_config.side_mode_a++;
        if (g_config.side_mode_a > SIDE_STATIC) {
            g_config.side_mode_a = 0;
        }
    } else {
        if (g_config.side_mode_a > 0) {
            g_config.side_mode_a--;
        } else {
            g_config.side_mode_a = 0;
        }
    }
    if (g_config.side_mode_a == SIDE_NEW) {
        side_old_color      = g_config.side_color;
        g_config.side_color = side_new_color;
    } else if (g_config.side_mode_a == SIDE_BREATH) {
        side_new_color      = g_config.side_color;
        g_config.side_color = side_old_color;
    }
    side_play_point = 0;

    save_config_to_eeprom();
}

void side_mode_b_control(uint8_t dir) {
    if (dir) {
        g_config.side_mode_b++;
        if (g_config.side_mode_b > SIDE_MODE_7) {
            g_config.side_mode_b = SIDE_MODE_1;
        }
    } else {
        if (g_config.side_mode_b > 0) {
            g_config.side_mode_b--;
        } else {
            g_config.side_mode_b = SIDE_MODE_1;
        }
    }
    side_play_point = 0;
    save_config_to_eeprom();
}

/**
 * @brief  set left side leds.
 * @param  ...
 */
void set_left_rgb(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < 5; i++)
        rgb_matrix_set_color(SIDE_INDEX + i, r, g, b);
}

void set_all_side_off(void) {
    for (int i = 0; i < 45; i++) {
        rgb_matrix_set_color(SIDE_INDEX + i, 0, 0, 0);
    }
}

/**
 * @brief  mac or win system indicate
 */
void sys_sw_led_show(void) {
    static uint32_t sys_show_timer = 0;
    static bool     sys_show_flag  = false;
    extern bool     f_sys_show;

    if (f_sys_show) {
        f_sys_show     = false;
        sys_show_timer = timer_read32(); // store time of last refresh
        sys_show_flag  = true;
    }

    if (sys_show_flag) {
        if (dev_info.sys_sw_state == SYS_SW_MAC) {
            r_temp = side_color_lib[7][0];
            g_temp = side_color_lib[7][1];
            b_temp = side_color_lib[7][2];
        } else {
            r_temp = side_color_lib[5][0];
            g_temp = side_color_lib[5][1];
            b_temp = side_color_lib[5][2];
        }
        if ((timer_elapsed32(sys_show_timer) / 500) % 2 == 0) {
            set_left_rgb(r_temp, g_temp, b_temp);
        } else {
            set_left_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sys_show_timer) >= (3000 - 50)) {
            sys_show_flag = false;
        }
    }
}

/**
 * @brief  sleep enable or disable indicate
 */
void sleep_sw_led_show(void) {
    static uint32_t sleep_show_timer     = 0;
    static bool     sleep_show_flag      = false;
    static bool     usb_sleep_show_flag  = false;
    static bool     deep_sleep_show_flag = false;

    if (f_sleep_show) {
        f_sleep_show = false;

        sleep_show_timer     = timer_read32();
        sleep_show_flag      = true;
        usb_sleep_show_flag  = false;
        deep_sleep_show_flag = false;
    } else if (f_usb_sleep_show) {
        f_usb_sleep_show     = false;
        sleep_show_timer     = timer_read32();
        usb_sleep_show_flag  = true;
        sleep_show_flag      = false;
        deep_sleep_show_flag = false;
    } else if (f_deep_sleep_show) {
        f_deep_sleep_show    = false;
        sleep_show_timer     = timer_read32();
        usb_sleep_show_flag  = false;
        sleep_show_flag      = false;
        deep_sleep_show_flag = true;
    }

    if (sleep_show_flag) {
        if (g_config.sleep_toggle) {
            r_temp = 0x00;
            g_temp = SIDE_BLINK_LIGHT;
            b_temp = 0x00;
        } else {
            r_temp = 0xff;
            g_temp = 0x00;
            b_temp = 0x00;
        }
        if ((timer_elapsed32(sleep_show_timer) / 500) % 2 == 0) {
            set_left_rgb(r_temp, g_temp, b_temp);
        } else {
            set_left_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sleep_show_timer) >= (3000 - 50)) {
            sleep_show_flag = false;
        }
    } else if (usb_sleep_show_flag) {
        if (g_config.usb_sleep_toggle) {
            r_temp = 0x00;
            g_temp = SIDE_BLINK_LIGHT;
            b_temp = 0x00;
        } else {
            r_temp = 0xff;
            g_temp = 0x00;
            b_temp = 0x00;
        }
        if ((timer_elapsed32(sleep_show_timer) / 500) % 2 == 0) {
            set_left_rgb(r_temp, g_temp, b_temp);
        } else {
            set_left_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sleep_show_timer) >= (3000 - 50)) {
            usb_sleep_show_flag = false;
        }
    } else if (deep_sleep_show_flag) {
        if (g_config.deep_sleep_toggle) {
            r_temp = 0x00;
            g_temp = SIDE_BLINK_LIGHT;
            b_temp = 0x00;
        } else {
            r_temp = 0xff;
            g_temp = 0x00;
            b_temp = 0x00;
        }
        if ((timer_elapsed32(sleep_show_timer) / 500) % 2 == 0) {
            set_left_rgb(r_temp, g_temp, b_temp);
        } else {
            set_left_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sleep_show_timer) >= (3000 - 50)) {
            deep_sleep_show_flag = false;
        }
    }
}

/**
 * @brief  host system led indicate.
 */
void sys_led_show(void) {
    uint8_t caps_key_led_idx = get_led_index(3, 0);
    bool    showCapsLock     = false;
    if (dev_info.link_mode == LINK_USB) {
        showCapsLock = host_keyboard_led_state().caps_lock;
    } else {
        showCapsLock = dev_info.rf_led & 0x02;
    }

    if (showCapsLock) {
        switch (g_config.caps_indicator_type) {
            case CAPS_INDICATOR_SIDE:
                set_left_rgb(side_color_lib[4][0], side_color_lib[4][1], side_color_lib[4][2]);

                break;
            case CAPS_INDICATOR_UNDER_KEY:
                rgb_matrix_set_color(caps_key_led_idx, side_color_lib[4][0], side_color_lib[4][1], side_color_lib[4][2]);

                break;
            case CAPS_INDICATOR_BOTH:
                set_left_rgb(side_color_lib[4][0], side_color_lib[4][1], side_color_lib[4][2]);
                rgb_matrix_set_color(caps_key_led_idx, side_color_lib[4][0], side_color_lib[4][1], side_color_lib[4][2]);

                break;
            case CAPS_INDICATOR_OFF:
            default:
                break;
        }
    }
}

/**
 * @brief  light_point_playing.
 * @param trend:
 * @param step:
 * @param len:
 * @param point:
 */
static void light_point_playing(uint8_t trend, uint8_t step, uint8_t len, uint8_t *point) {
    if (trend) {
        *point += step;
        if (*point >= len) *point -= len;
    } else {
        *point -= step;
        if (*point >= len) *point = len - (255 - *point) - 1;
    }
}

/**
 * @brief  count_rgb_light.
 * @param light_temp:
 */
static void count_rgb_light(uint8_t light_temp) {
    uint16_t temp;

    temp   = (light_temp)*r_temp + r_temp;
    r_temp = temp >> 8;

    temp   = (light_temp)*g_temp + g_temp;
    g_temp = temp >> 8;

    temp   = (light_temp)*b_temp + b_temp;
    b_temp = temp >> 8;
}

/**
 * @brief  auxiliary_rgb_light.
 */
uint8_t key_pwm_tab[45]  = {0x00};
uint8_t power_play_index = 0;
uint8_t f_power_show     = 1;
uint8_t f_side_flag      = 0x1f;
uint8_t is_side_rgb_on(uint8_t index) {
    if ((((index >= 0) && (index <= 7)) || ((index >= 37) && (index <= 39))) && (f_side_flag & 0x01))
        return true;
    else if ((((index >= 8) && (index <= 13)) || ((index >= 19) && (index <= 29)) || ((index >= 31) && (index <= 36))) && (f_side_flag & 0x02))
        return true;
    else if (((index >= 40) && (index <= 44)) && (f_side_flag & 0x04))
        return true;
    else if (((index >= 14) && (index <= 18)) && (f_side_flag & 0x08))
        return true;
    else if (((index >= 30) && (index <= 31)) && (f_side_flag & 0x10))
        return true;
    else
        return false;
}

/**
 * @brief  side_wave_mode_show.
 */
static void side_wave_mode_show(void) {
    uint8_t play_index;
    uint8_t play_index_1;

    if (side_play_cnt <= side_speed_table[g_config.side_mode_a][g_config.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[g_config.side_mode_a][g_config.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (g_config.side_rgb)
        light_point_playing(0, 1, FLOW_COLOR_TAB_LEN, &side_play_point);
    else
        light_point_playing(0, 1, WAVE_TAB_LEN, &side_play_point);

    play_index = side_play_point;
    if (side_line == 0) set_all_side_off();
    for (int i = 0; i <= side_line - 5; i++) {
        if (g_config.side_rgb) {
            r_temp = flow_rainbow_color_tab[play_index][0];
            g_temp = flow_rainbow_color_tab[play_index][1] * 0.3;
            b_temp = flow_rainbow_color_tab[play_index][2] * 0.4;

            light_point_playing(1, 5, FLOW_COLOR_TAB_LEN, &play_index);

        } else {
            r_temp = side_color_lib[g_config.side_color][0];
            g_temp = side_color_lib[g_config.side_color][1];
            b_temp = side_color_lib[g_config.side_color][2];

            light_point_playing(1, 5, WAVE_TAB_LEN, &play_index);
            count_rgb_light(wave_data_tab[play_index]);
        }

        count_rgb_light(side_light_table[g_config.side_brightness]);

        play_index_1 = play_index;

        if (i == 40) {
            if (f_side_flag == 0x1f) {
                for (; i < 45; i++) {
                    if (g_config.side_rgb) {
                        r_temp = flow_rainbow_color_tab[play_index_1][0];
                        g_temp = flow_rainbow_color_tab[play_index_1][1] * 0.3;
                        b_temp = flow_rainbow_color_tab[play_index_1][2] * 0.4;
                        light_point_playing(1, 5, FLOW_COLOR_TAB_LEN, &play_index_1);
                    } else {
                        r_temp = side_color_lib[g_config.side_color][0];
                        g_temp = side_color_lib[g_config.side_color][1];
                        b_temp = side_color_lib[g_config.side_color][2];
                        light_point_playing(1, 5, WAVE_TAB_LEN, &play_index_1);
                        count_rgb_light(wave_data_tab[play_index_1]);
                    }
                    count_rgb_light(side_light_table[g_config.side_brightness]);
                    rgb_matrix_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
                }
                return;
            } else {
                for (; i < 45; i++) {
                    rgb_matrix_set_color(side_led_index_tab[i], 0, 0, 0);
                }
                return;
            }
        }
        if (is_side_rgb_on(i))
            rgb_matrix_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
        else
            rgb_matrix_set_color(side_led_index_tab[i], 0, 0, 0);
    }
}

static void side_new_mode_show(void) {
    uint8_t play_index;

    if (side_play_cnt <= side_speed_table[g_config.side_mode_a][g_config.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[g_config.side_mode_a][g_config.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    light_point_playing(0, 1, (side_line - 5), &side_play_point);
    play_index = side_play_point;
    if (side_line == 0) set_all_side_off();
    for (int i = 0; i <= (side_line - 5); i++) {
        if (play_index < (side_line - 5) / 2) {
            r_temp = dual_side_color_lib[g_config.side_color][0];
            g_temp = dual_side_color_lib[g_config.side_color][1];
            b_temp = dual_side_color_lib[g_config.side_color][2];
        } else {
            r_temp = dual_side_color_lib[g_config.side_color][3];
            g_temp = dual_side_color_lib[g_config.side_color][4];
            b_temp = dual_side_color_lib[g_config.side_color][5];
        }

        light_point_playing(1, 1, (side_line - 5), &play_index);

        count_rgb_light(side_light_table[g_config.side_brightness]);

        if (i == 40) {
            if (f_side_flag == 0x1f) {
                for (; i < 45; i++) {
                    rgb_matrix_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
                }
                return;
            } else {
                for (; i < 45; i++) {
                    rgb_matrix_set_color(side_led_index_tab[i], 0, 0, 0);
                }
                return;
            }
        }
        if (is_side_rgb_on(i))
            rgb_matrix_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
        else
            rgb_matrix_set_color(side_led_index_tab[i], 0, 0, 0);
    }
}

static void side_spectrum_mode_show(void) {
    if (side_play_cnt <= side_speed_table[g_config.side_mode_a][g_config.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[g_config.side_mode_a][g_config.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (side_line == 0) set_all_side_off();

    light_point_playing(1, 1, FLOW_COLOR_TAB_LEN, &side_play_point);

    r_temp = flow_rainbow_color_tab[side_play_point][0];
    g_temp = flow_rainbow_color_tab[side_play_point][1];
    b_temp = flow_rainbow_color_tab[side_play_point][2];

    count_rgb_light(side_light_table[g_config.side_brightness]);

    for (int i = 0; i < side_line; i++) {
        if (is_side_rgb_on(i))
            rgb_matrix_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
        else
            rgb_matrix_set_color(side_led_index_tab[i], 0, 0, 0);
    }
}

static void side_breathe_mode_show(void) {
    static uint8_t play_point = 0;
    static uint8_t color      = 0;

    if (side_play_cnt <= side_speed_table[g_config.side_mode_a][g_config.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[g_config.side_mode_a][g_config.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (side_line == 0) set_all_side_off();

    light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);

    if (g_config.side_rgb) {
        if (play_point == 0) {
            if (++color >= LIGHT_COLOR_MAX) color = 0;
        }
        r_temp = side_color_lib[color][0];
        g_temp = side_color_lib[color][1];
        b_temp = side_color_lib[color][2];

    } else {
        r_temp = side_color_lib[g_config.side_color][0];
        g_temp = side_color_lib[g_config.side_color][1];
        b_temp = side_color_lib[g_config.side_color][2];
    }
    count_rgb_light(breathe_data_tab[play_point]);
    count_rgb_light(side_light_table[g_config.side_brightness]);

    for (int i = 0; i < side_line; i++) {
        if (is_side_rgb_on(i))
            rgb_matrix_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
        else
            rgb_matrix_set_color(side_led_index_tab[i], 0, 0, 0);
    }
}

/**
 * @brief  side_static_mode_show.
 */
static void side_static_mode_show(void) {
    if (side_play_cnt <= side_speed_table[g_config.side_mode_a][g_config.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[g_config.side_mode_a][g_config.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (side_line == 0) set_all_side_off();

    if (side_play_point >= SIDE_COLOR_MAX) side_play_point = 0;

    for (int i = 0; i < side_line; i++) {
        if (((i <= 18) && (i >= 14)) || ((i >= 40) && (i <= 44))) {
            r_temp = side_color_lib_1[g_config.side_color][0];
            g_temp = side_color_lib_1[g_config.side_color][1];
            b_temp = side_color_lib_1[g_config.side_color][2];
        } else {
            r_temp = side_color_lib[g_config.side_color][0];
            g_temp = side_color_lib[g_config.side_color][1];
            b_temp = side_color_lib[g_config.side_color][2];
        }
        if (side_rgb_parallel[i] == 2) {
            r_temp *= 0.8;
        } else {
            ;
        }

        count_rgb_light(side_light_table[g_config.side_brightness]);

        if (is_side_rgb_on(i))
            rgb_matrix_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
        else
            rgb_matrix_set_color(side_led_index_tab[i], 0, 0, 0);
    }
}

/**
 * @brief  bat_charging_breathe.
 */
void bat_charging_breathe(void) {
    static uint32_t interval_timer = 0;
    static uint8_t  play_point     = 0;

    if (timer_elapsed32(interval_timer) > 45) {
        interval_timer = timer_read32();
        light_point_playing(0, 4, BREATHE_TAB_LEN, &play_point);
    }

    r_temp = 0xff;
    g_temp = 0x20;
    b_temp = 0x00;
    count_rgb_light(breathe_data_tab[play_point]);
    set_left_rgb(r_temp, g_temp, b_temp);
}

/**
 * @brief  rf state indicate
 */
#define RF_LED_LINK_PERIOD 500
#define RF_LED_PAIR_PERIOD 250
void rf_led_show(void) {
    static uint32_t rf_blink_timer = 0;
    static bool     flag_power_on  = 1;
    uint16_t        rf_blink_priod = 0;
    extern uint8_t  rf_blink_cnt;

    if (dev_info.link_mode == LINK_RF_24) {
        r_temp = side_color_lib[3][0];
        g_temp = side_color_lib[3][1];
        b_temp = side_color_lib[3][2];
    } else if (dev_info.link_mode == LINK_USB) {
        r_temp = side_color_lib[2][0];
        g_temp = side_color_lib[2][1];
        b_temp = side_color_lib[2][2];
        if (flag_power_on && (rf_link_show_time < RF_LINK_SHOW_TIME)) return;
    } else {
        r_temp = side_color_lib[5][0];
        g_temp = side_color_lib[5][1];
        b_temp = side_color_lib[5][2];
    }

    flag_power_on = 0;

    if (rf_blink_cnt) {
        if (dev_info.rf_state == RF_PAIRING)
            rf_blink_priod = RF_LED_PAIR_PERIOD;
        else
            rf_blink_priod = RF_LED_LINK_PERIOD;

        if (timer_elapsed32(rf_blink_timer) < (rf_blink_priod >> 1)) {
        } else {
            r_temp = 0x00;
            g_temp = 0x00;
            b_temp = 0x00;
        }

        if (timer_elapsed32(rf_blink_timer) >= rf_blink_priod) {
            rf_blink_cnt--;
            rf_blink_timer = timer_read32();
        }
    } else if (rf_link_show_time < RF_LINK_SHOW_TIME) {
    } else {
        rf_blink_timer = timer_read32();
        return;
    }

    set_left_rgb(r_temp, g_temp, b_temp);
}

uint8_t low_bat_blink_cnt = 6;
#define LOW_BAT_BLINK_PRIOD 500
void low_bat_show(void) {
    static uint32_t interval_timer = 0;

    r_temp = 0x80, g_temp = 0, b_temp = 0;

    if (low_bat_blink_cnt) {
        if (timer_elapsed32(interval_timer) > (LOW_BAT_BLINK_PRIOD >> 1)) {
            r_temp = 0x00;
            g_temp = 0x00;
            b_temp = 0x00;
        }

        if (timer_elapsed32(interval_timer) >= LOW_BAT_BLINK_PRIOD) {
            interval_timer = timer_read32();
            low_bat_blink_cnt--;
        }
    }
    set_left_rgb(r_temp, g_temp, b_temp);
}

/**
 * @brief  Battery level indicator
 */
uint8_t bat_pwm_buf[6 * 3] = {0};
uint8_t bat_end_led        = 0;
uint8_t bat_r, bat_g, bat_b;
bool    low_bat_flag = 0;
void    bat_percent_led(uint8_t bat_percent) {
    uint8_t i;
    if (bat_percent <= 20) { // 0-20 red
        bat_end_led = 0;
        bat_r       = side_color_lib[0][0];
        bat_g       = side_color_lib[0][1];
        bat_b       = side_color_lib[0][2];
    } else if (bat_percent <= 40) { // 20-40 orange
        bat_end_led = 1;
        bat_r       = side_color_lib[1][0];
        bat_g       = side_color_lib[1][1];
        bat_b       = side_color_lib[1][2];
    } else if (bat_percent <= 60) { // 40-60 yellow
        bat_end_led = 2;
        bat_r       = side_color_lib[2][0];
        bat_g       = side_color_lib[2][1];
        bat_b       = side_color_lib[2][2];
    } else if (bat_percent <= 80) { // 60-80 light blue
        bat_end_led = 3;
        bat_r       = side_color_lib[4][0];
        bat_g       = side_color_lib[4][1];
        bat_b       = side_color_lib[4][2];
    } else { // 80-100 green
        bat_end_led = 4;
        bat_r       = side_color_lib[3][0];
        bat_g       = side_color_lib[3][1];
        bat_b       = side_color_lib[3][2];
    }

    // NOTE: dim using g_config.battery_indicator_brightness as percentage value
    bat_r = bat_r * g_config.battery_indicator_brightness / 100;
    bat_g = bat_g * g_config.battery_indicator_brightness / 100;
    bat_b = bat_b * g_config.battery_indicator_brightness / 100;

    if (f_charging) {
        low_bat_blink_cnt = 6;
        bat_charging_breathe();
    } else if (bat_percent < 10) {
        low_bat_show();
    } else {
        bat_end_led       = 4;
        low_bat_blink_cnt = 6;
        for (i = 0; i <= bat_end_led; i++)
            rgb_matrix_set_color(SIDE_INDEX + i, bat_r, bat_g, bat_b);
    }
}

/**
 * @brief  battery state indicate
 */
void bat_led_show(void) {
    static bool     bat_show_flag    = true;
    static uint32_t bat_show_time    = 0;
    static uint32_t bat_sts_debounce = 0;
    static uint32_t bat_per_debounce = 0;
    static uint8_t  charge_state     = 0;
    static uint8_t  bat_percent      = 0;
    static bool     f_init           = 1;

    if (dev_info.link_mode != LINK_USB) {
        if (rf_link_show_time < RF_LINK_SHOW_TIME) return;

        if (dev_info.rf_state != RF_CONNECT) return;
    }

    if (f_init) {
        f_init        = 0;
        bat_show_time = timer_read32();
        charge_state  = dev_info.rf_charge;
        bat_percent   = dev_info.rf_battery;
    }

    if (charge_state != dev_info.rf_charge) {
        if (timer_elapsed32(bat_sts_debounce) > 500) {
            if (((charge_state & 0x01) == 0) && ((dev_info.rf_charge & 0x01) != 0)) {
                bat_show_flag = true;
                f_charging    = true;
                bat_show_time = timer_read32();
            }
            charge_state = dev_info.rf_charge;
        }
    } else {
        bat_sts_debounce = timer_read32();
        if (f_charging) {
            if (timer_elapsed32(bat_show_time) > 10000) {
                bat_show_flag = false;
                f_charging    = false;
            }
        } else {
            if (timer_elapsed32(bat_show_time) > 5000) {
                bat_show_flag = false;
            }
        }
        if (charge_state == 0x03) {
            f_charging = true;
        } else if (!(charge_state & 0x01)) {
            f_charging = 0;
        }
    }

    if (bat_percent != dev_info.rf_battery) {
        if (timer_elapsed32(bat_per_debounce) > 1000) {
            bat_percent = dev_info.rf_battery;
        }
    } else {
        bat_per_debounce = timer_read32();

        if ((bat_percent < 10) && (!(charge_state & 0x01))) {
            bat_show_flag = true;
            bat_show_time = timer_read32();
            low_bat_flag  = 1;
            if (rgb_matrix_config.hsv.v > RGB_MATRIX_VAL_STEP) {
                rgb_matrix_config.hsv.v = RGB_MATRIX_VAL_STEP;
            }

            if (g_config.side_brightness > 1) {
                g_config.side_brightness = 1;
            }
        } else
            low_bat_flag = 0;
    }
    if (f_bat_hold || bat_show_flag) {
        bat_percent_led(bat_percent);
    }
}

/**
 * @brief  device_reset_show.
 */
void rgb_matrix_update_pwm_buffers(void);
void device_reset_show(void) {
    writePinHigh(DC_BOOST_PIN);
    writePinHigh(RGB_DRIVER_SDB1);
    writePinHigh(RGB_DRIVER_SDB2);

    for (int blink_cnt = 0; blink_cnt < 3; blink_cnt++) {
        rgb_matrix_set_color_all(0xFF, 0xFF, 0xFF);
        rgb_matrix_update_pwm_buffers();
        rgb_matrix_set_color_all(0xFF, 0xFF, 0xFF);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);

        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        rgb_matrix_update_pwm_buffers();
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);
    }
}

void device_reset_init(void) {
    side_play_point = 0;
    side_play_cnt   = 0;
    side_play_timer = timer_read32();
    f_bat_hold      = false;

    kb_config_reset();
}

/**
 * @brief  rgb test
 */
void rgb_test_show(void) {
    writePinHigh(DC_BOOST_PIN);
    writePinHigh(RGB_DRIVER_SDB1);
    writePinHigh(RGB_DRIVER_SDB2);
    rgb_matrix_set_color_all(0xFF, 0x00, 0x00);
    rgb_matrix_update_pwm_buffers();
    wait_ms(1000);
    rgb_matrix_set_color_all(0x00, 0xFF, 0x00);
    rgb_matrix_update_pwm_buffers();
    wait_ms(1000);
    rgb_matrix_set_color_all(0x00, 0x00, 0xFF);
    rgb_matrix_update_pwm_buffers();
    wait_ms(1000);
}

/*
 * @brief power on animation
 */
static void side_power_mode_show(void) {
    if (side_play_cnt <= side_speed_table[0][g_config.side_speed])

        return;
    else
        side_play_cnt -= side_speed_table[0][g_config.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (power_play_index <= 45) {
        key_pwm_tab[power_play_index] = 0xff;
        power_play_index++;
    }

    uint8_t i;

    for (i = 0; i < 45; i++) {
        r_temp = side_color_lib[g_config.side_color][0];
        g_temp = side_color_lib[g_config.side_color][1];
        b_temp = side_color_lib[g_config.side_color][2];

        count_rgb_light(key_pwm_tab[i]);
        count_rgb_light(side_light_table[2]);
        rgb_matrix_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
    }

    for (i = 0; i < 45; i++)

    {
        if (key_pwm_tab[i] & 0x80)
            key_pwm_tab[i] -= 8;
        else if (key_pwm_tab[i] & 0x40)
            key_pwm_tab[i] -= 6;

        else if (key_pwm_tab[i] & 0x20)
            key_pwm_tab[i] -= 4;
        else if (key_pwm_tab[i] & 0x10)
            key_pwm_tab[i] -= 3;
        else if (key_pwm_tab[i] & 0x08)
            key_pwm_tab[i] -= 2;
        else if (key_pwm_tab[i])
            key_pwm_tab[i]--;
    }

    if (key_pwm_tab[44] == 1) {
        f_power_show = 0;
        save_config_to_eeprom();
        rf_link_show_time = 0;
        bat_show_flag     = true;
        f_charging        = true;
        bat_show_time     = timer_read32();
    }
}

/**
 * @brief  side_led_show.
 */
void side_led_show(void) {
    static bool flag_power_on = 1;
    extern bool f_dial_sw_init_ok;

    side_play_cnt += timer_elapsed32(side_play_timer);
    side_play_timer = timer_read32();

    if (flag_power_on) {
        if (!f_dial_sw_init_ok) return;
        flag_power_on = 0;
    }

    if (!g_config.power_show) {
        f_power_show = 0;
    }

    if (f_power_show) {
        side_power_mode_show();
        return;
    }

    switch (g_config.side_mode_b) {
        case SIDE_MODE_1:
            side_line   = 0;
            f_side_flag = 0;
            break;

        case SIDE_MODE_2:
            side_line   = 45;
            f_side_flag = 0x08;
            break;

        case SIDE_MODE_3:
            side_line   = 45;
            f_side_flag = 0x18;
            break;

        case SIDE_MODE_4:
            side_line   = 45;
            f_side_flag = 0x1f;
            break;

        case SIDE_MODE_5:
            side_line   = 45;
            f_side_flag = 0x01;
            break;

        case SIDE_MODE_6:
            side_line   = 45;
            f_side_flag = 0x09;
            break;

        case SIDE_MODE_7:
            side_line   = 45;
            f_side_flag = 0x19;
            break;
        default:
            break;
    }
    switch (g_config.side_mode_a) {
        case SIDE_WAVE:
            side_wave_mode_show();
            break;
        case SIDE_NEW:
            side_new_mode_show();
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
    }

    bat_led_show();
    sys_led_show();
    sys_sw_led_show();
    sleep_sw_led_show();
    rf_led_show();
}
