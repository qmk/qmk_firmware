// Copyright 2023 Ryodeushii (@ryodeushii)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdint.h>
#include "color.h"
#include "host.h"
#include "rgb_matrix.h"
#include "timer.h"
#include "side.h"
#include "common/side_table.h"
#include "common/rf_driver.h"
#include "common/config.h"

// clang-format off
const uint8_t side_speed_table[5][5] = {
    [SIDE_WAVE] = {24, 30, 36, 42, 50},
    [SIDE_MIX] = {14, 20, 28, 36, 50},
    [SIDE_STATIC] = {50, 50, 50, 50, 50},
    [SIDE_BREATH] = {14, 20, 28, 36, 50},
    [SIDE_OFF] = {50, 50, 50, 50, 50},
};

const uint8_t side_light_table[6] = {
    0, 22, 34, 55, 79, 106,
};

const uint8_t side_led_index_tab[SIDE_LINE] = {
    0, 1, 2, 3, 4,
};

// clang-format on

bool f_charging = 1;

uint8_t side_play_point = 0;

uint8_t low_bat_blink_cnt = 6;
uint8_t side_play_cnt     = 0;

uint32_t side_play_timer = 0;

uint8_t                r_temp, g_temp, b_temp;
extern DEV_INFO_STRUCT dev_info;
extern bool            f_bat_hold;

extern void kb_config_reset(void);

extern bool     f_dial_sw_init_ok;
extern uint8_t  logo_play_point;
extern uint8_t  rf_blink_cnt;
extern uint16_t rf_link_show_time;
extern uint8_t  logo_play_cnt;
extern uint32_t logo_play_timer;

RGB  side_leds[SIDE_LED_NUM] = {0};
void side_ws2812_setleds(RGB *ledarray, uint16_t leds);
void rgb_matrix_update_pwm_buffers(void);
void logo_led_loop(void);

/**
 * @brief  side leds set color vaule.
 * @param  index: index of side_leds[].
 * @param  ...
 */
void side_rgb_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    side_leds[index].r = red;
    side_leds[index].g = green;
    side_leds[index].b = blue;
}

/**
 * @brief  refresh side leds.

 */
void side_rgb_refresh(void) {
    side_ws2812_setleds(side_leds, SIDE_LED_NUM);
}

/**
 * @brief  Adjusting the brightness of side lights.
 * @param  dir: 0 - decrease, 1 - increase.

 * @note  save to eeprom.
 */
void side_brightness_control(uint8_t brighten) {
    if (brighten) {
        if (keyboard_config.lights.side_brightness == 5) {
            return;
        } else
            keyboard_config.lights.side_brightness++;

    } else {
        if (keyboard_config.lights.side_brightness == 0) {
            return;
        } else
            keyboard_config.lights.side_brightness--;
    }
    save_config_to_eeprom();
}

/**

 * @brief  Adjusting the speed of side lights.
 * @param  dir: 0 - decrease, 1 - increase.
 * @note  save to eeprom.
 */
void side_speed_control(uint8_t fast) {
    if ((keyboard_config.lights.side_speed) > LIGHT_SPEED_MAX) (keyboard_config.lights.side_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if (keyboard_config.lights.side_speed) keyboard_config.lights.side_speed--;
    } else {
        if (keyboard_config.lights.side_speed < LIGHT_SPEED_MAX) keyboard_config.lights.side_speed++;
    }
    save_config_to_eeprom();
}

/**
 * @brief  Switch to the next color of side lights.
 * @param  dir: 0 - prev, 1 - next.
 * @note  save to eeprom.
 */

void side_color_control(uint8_t dir) {
    if (keyboard_config.lights.side_mode != SIDE_WAVE) {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb   = 0;
            keyboard_config.lights.side_color = 0;
        }
    }

    if (dir) {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb = 0;

            keyboard_config.lights.side_color = 0;

        } else {
            keyboard_config.lights.side_color++;
            if (keyboard_config.lights.side_color >= LIGHT_COLOR_MAX) {
                keyboard_config.lights.side_rgb   = 1;
                keyboard_config.lights.side_color = 0;
            }
        }
    } else {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb   = 0;
            keyboard_config.lights.side_color = LIGHT_COLOR_MAX - 1;

        } else {
            keyboard_config.lights.side_color--;
            if (keyboard_config.lights.side_color >= LIGHT_COLOR_MAX) {
                keyboard_config.lights.side_rgb   = 1;
                keyboard_config.lights.side_color = 0;
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
void side_mode_control(uint8_t dir) {
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

    side_play_point = 0;
    save_config_to_eeprom();
}

/**
 * @brief  set left side leds.
 * @param  ...

 */
void set_side_rgb(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < SIDE_LINE; i++)
        side_rgb_set_color(i, r >> 2, g >> 2, b >> 2);
}

void set_indicator_on_side(uint8_t r, uint8_t g, uint8_t b) {
    set_side_rgb(r, g, b);
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
 * @brief  side_wave_mode_show.
 */
static void side_wave_mode_show(void) {
    uint8_t play_index;

    //------------------------------
    if (side_play_cnt <= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[keyboard_config.lights.side_mode][keyboard_config.lights.side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    //------------------------------
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

/**

 * @brief  side_spectrum_mode_show.
 */
static void side_spectrum_mode_show(void) {
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

/**
 * @brief  side_breathe_mode_show.
 */
static void side_breathe_mode_show(void) {
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

/**
 * @brief  side_static_mode_show.

 */
static void side_static_mode_show(void) {
    if (side_play_point >= SIDE_COLOR_MAX) side_play_point = 0;

    r_temp = side_color_lib[keyboard_config.lights.side_color][0] >> 2;
    g_temp = side_color_lib[keyboard_config.lights.side_color][1] >> 2;
    b_temp = side_color_lib[keyboard_config.lights.side_color][2] >> 2;

    count_rgb_light(side_light_table[keyboard_config.lights.side_brightness]);

    for (int i = 0; i < SIDE_LINE; i++) {
        side_rgb_set_color(side_led_index_tab[i], r_temp, g_temp, b_temp);
    }
}

/**
 * @brief  side_off_mode_show.
 */
static void side_off_mode_show(void)

{
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

void bat_charging_design(uint8_t init, uint8_t r, uint8_t g, uint8_t b) {
    static uint32_t interval_timer = 0;
    static uint16_t show_mask      = 0x00;
    static bool     f_move_trend   = 0;
    uint16_t        bit_mask       = 1;
    uint8_t         i;

    if (timer_elapsed32(interval_timer) > 100) {
        interval_timer = timer_read32();

        if (f_move_trend) {
            show_mask >>= 1;
            if (show_mask == 0x1f >> (SIDE_LINE - init)) f_move_trend = 0;
        } else {
            show_mask <<= 1;
            show_mask |= 1;
            if (show_mask == 0x7f) f_move_trend = 1;
        }
    }

    for (i = 0; i < SIDE_LINE; i++) {
        if (show_mask & bit_mask) {
            side_rgb_set_color(i, r, g, b);
        } else {
            side_rgb_set_color(i, 0x00, 0x00, 0x00);
        }
        bit_mask <<= 1;
    }
}

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

    set_side_rgb(r_temp, g_temp, b_temp);
}

/**
 * @brief  bat_percent_led.
 */
void bat_percent_led(uint8_t bat_percent) {
    uint8_t i;
    uint8_t bat_end_led = 0;
    uint8_t bat_r, bat_g, bat_b;

    if (bat_percent <= 20) { // 0-20
        bat_end_led = 0;
        bat_r = 0x80, bat_g = 0, bat_b = 0; // red
    } else if (bat_percent <= 40) {         // 20-40
        bat_end_led = 1;
        bat_r = 0x80, bat_g = 0x40, bat_b = 0; // orange
    } else if (bat_percent <= 60) {            // 40-60
        bat_end_led = 2;
        bat_r = 0x80, bat_g = 0x80, bat_b = 0; // yellow
    } else if (bat_percent <= 80) {            // 60-80
        bat_end_led = 3;
        bat_r = 0x20, bat_g = 0, bat_b = 0x80; // blue-purpleish
    } else {                                   // 80-100
        bat_end_led = 4;
        bat_r = 0, bat_g = 0x80, bat_b = 0; // green
    }

    // NOTE: dim using g_config.battery_indicator_brightness as percentage value
    bat_r = bat_r * keyboard_config.custom.battery_indicator_brightness / 100;
    bat_g = bat_g * keyboard_config.custom.battery_indicator_brightness / 100;
    bat_b = bat_b * keyboard_config.custom.battery_indicator_brightness / 100;

    if (f_charging) {
        low_bat_blink_cnt = 6;
#if (CHARGING_SHIFT)
        bat_charging_design(bat_end_led, bat_r >> 2, bat_g >> 2, bat_b >> 2);
#else
        bat_charging_breathe();
#endif
    }

    else if (bat_percent < 10) {
        low_bat_show();
    } else {
        bat_end_led       = 4;
        low_bat_blink_cnt = 6;
        for (i = 0; i <= bat_end_led; i++)
            side_rgb_set_color(i, bat_r >> 2, bat_g >> 2, bat_b >> 2);

        for (; i < SIDE_LINE; i++)
            side_rgb_set_color(i, 0, 0, 0);
    }
}

/**
 * @brief  bat_led_show.
 */

void bat_led_show(void) {
    static bool bat_show_flag = true;

    static uint32_t bat_show_time    = 0;
    static uint32_t bat_sts_debounce = 0;
    static uint32_t bat_per_debounce = 0;
    static uint8_t  charge_state     = 0;
    static uint8_t  bat_percent      = 0;
    static bool     f_init           = 1;

    if (dev_info.link_mode != LINK_USB) {
        extern uint16_t rf_link_show_time;
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
        if (timer_elapsed32(bat_sts_debounce) > 1000) {
            if (((charge_state & 0x01) == 0) && ((dev_info.rf_charge & 0x01) != 0)) {
                bat_show_flag = true;
                f_charging    = true;
                bat_show_time = timer_read32();
            }
            charge_state = dev_info.rf_charge;
        }

    } else {
        bat_sts_debounce = timer_read32();
        if (timer_elapsed32(bat_show_time) > 5000) {
            bat_show_flag = false;

            f_charging = false;
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

            if (rgb_matrix_config.hsv.v > RGB_MATRIX_VAL_STEP) {
                rgb_matrix_config.hsv.v = RGB_MATRIX_VAL_STEP;
            }

            if (keyboard_config.lights.side_brightness > 1) {
                keyboard_config.lights.side_brightness = 1;
            }

            if (keyboard_config.lights.ambient_brightness > 1) {
                keyboard_config.lights.ambient_brightness = 1;
            }
        }
    }

    if (f_bat_hold || bat_show_flag) {
        bat_percent_led(bat_percent);
    }
}

/**

 * @brief  device_reset_show.
 */
void device_reset_show(void) {
    writePinHigh(DC_BOOST_PIN);
    setPinOutput(DRIVER_SIDE_CS_PIN);
    setPinOutput(DRIVER_MATRIX_CS_PIN);

    writePinLow(DRIVER_SIDE_CS_PIN);
    writePinLow(DRIVER_MATRIX_CS_PIN);

    for (int blink_cnt = 0; blink_cnt < 3; blink_cnt++) {
        rgb_matrix_set_color_all(0x10, 0x10, 0x10);
        for (int i = 0; i < SIDE_LED_NUM; i++) {
            side_rgb_set_color(i, 0x10, 0x10, 0x10);
        }
        rgb_matrix_update_pwm_buffers();

        side_rgb_refresh();
        wait_ms(200);

        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        for (int i = 0; i < SIDE_LED_NUM; i++) {
            side_rgb_set_color(i, 0x00, 0x00, 0x00);
        }
        rgb_matrix_update_pwm_buffers();
        side_rgb_refresh();
        wait_ms(200);
    }
}

/**
 * @brief  device_reset_init.
 */
void device_reset_init(void) {
    side_play_point = 0;
    side_play_cnt   = 0;
    side_play_timer = timer_read32();

    logo_play_point = 0;
    logo_play_cnt   = 0;
    logo_play_timer = timer_read32();

    f_bat_hold = false;

    kb_config_reset();
}

void rgb_test_show(void) {
    writePinHigh(DC_BOOST_PIN);
    setPinOutput(DRIVER_MATRIX_CS_PIN);
    writePinLow(DRIVER_MATRIX_CS_PIN);

    rgb_matrix_set_color_all(0xFF, 0x00, 0x00);
    for (int i = 0; i < SIDE_LED_NUM; i++)
        side_rgb_set_color(i, 0xFF, 0x00, 0x00);
    rgb_matrix_update_pwm_buffers();
    side_rgb_refresh();
    wait_ms(1000);
    rgb_matrix_set_color_all(0x00, 0xFF, 0x00);
    for (int i = 0; i < SIDE_LED_NUM; i++)
        side_rgb_set_color(i, 0x00, 0xFF, 0x00);

    rgb_matrix_update_pwm_buffers();
    side_rgb_refresh();
    wait_ms(1000);
    rgb_matrix_set_color_all(0x00, 0x00, 0xFF);
    for (int i = 0; i < SIDE_LED_NUM; i++)
        side_rgb_set_color(i, 0x00, 0x00, 0xFF);
    rgb_matrix_update_pwm_buffers();
    side_rgb_refresh();
    wait_ms(1000);
}

/**
 * @brief  side_led_show.
 */
void side_led_show(void) {
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

#if (WORK_MODE == THREE_MODE)
    bat_led_show();
#endif

    logo_led_loop();
}
