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
#include "side.h"

#define SIDE_WAVE           0
#define SIDE_MIX            1
#define SIDE_STATIC         2
#define SIDE_BREATH         3
#define SIDE_OFF            4

#define LIGHT_COLOUR_MAX    8
#define SIDE_COLOUR_MAX     8
#define LIGHT_SPEED_MAX     4
#define SIDE_BLINK_LIGHT    128
#define SIDE_LINE           5
#define SIDE_INDEX          64


const uint8_t side_speed_table[5][5] = {
    [SIDE_WAVE]   = {14, 19, 25, 32, 40},
    [SIDE_MIX]    = {14, 19, 25, 32, 40},
    [SIDE_STATIC] = {50, 50, 50, 50, 50},
    [SIDE_BREATH] = {14, 19, 25, 32, 40},
    [SIDE_OFF]    = {50, 50, 50, 50, 50},
};

const uint8_t side_light_table[6] = {
    0,
    48,
    96,
    144,
    192,
    255,
};

const uint8_t side_led_index_tab[SIDE_LINE][2] =
    {
        {SIDE_INDEX + 4, SIDE_INDEX + 5},
        {SIDE_INDEX + 3, SIDE_INDEX + 6},
        {SIDE_INDEX + 2, SIDE_INDEX + 7},
        {SIDE_INDEX + 1, SIDE_INDEX + 8},
        {SIDE_INDEX + 0, SIDE_INDEX + 9},
};


uint8_t side_mode           = 0;
uint8_t side_light          = 3;
uint8_t side_speed          = 2;
uint8_t side_rgb            = 1;
uint8_t side_colour         = 0;
uint8_t side_play_point     = 0;
uint8_t side_play_cnt       = 0;
uint32_t side_play_timer    = 0;
uint8_t r_temp, g_temp, b_temp;

extern bool f_bat_hold;
extern DEV_INFO_STRUCT dev_info;
extern user_config_t user_config;
extern uint8_t rf_blink_cnt;
extern uint16_t rf_link_show_time;

/**
 * @brief suspend_power_down_kb
 *
 */
void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

/**
 * @brief suspend_wakeup_init_kb
 *
 */
void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}

/**
 * @brief  Adjusting the brightness of side lights.
 * @param  dir: 0 - decrease, 1 - increase.
 * @note  save to eeprom.
 */
void light_level_control(uint8_t brighten)
{
    if (brighten)
    {
        if (side_light == 5) {
            return;
        } else
            side_light++;
    } else
    {
        if (side_light == 0) {
            return;
        } else
            side_light--;
    }
    user_config.ee_side_light = side_light;
    nuphy_eeconfig_update_user(&user_config);
}

/**
 * @brief  Adjusting the speed of side lights.
 * @param  dir: 0 - decrease, 1 - increase.
 * @note  save to eeprom.
 */
void light_speed_control(uint8_t fast)
{
    if ((side_speed) > LIGHT_SPEED_MAX)
        (side_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if ((side_speed)) side_speed--;
    } else {
        if ((side_speed) < LIGHT_SPEED_MAX) side_speed++;
    }
    user_config.ee_side_speed = side_speed;
    nuphy_eeconfig_update_user(&user_config);
}

/**
 * @brief  Switch to the next color of side lights.
 * @param  dir: 0 - prev, 1 - next.
 * @note  save to eeprom.
 */
void side_colour_control(uint8_t dir)
{
    if (side_mode != SIDE_WAVE) {
        if (side_rgb) {
            side_rgb    = 0;
            side_colour = 0;
        }
    }

    if (dir) {
        if (side_rgb) {
            side_rgb    = 0;
            side_colour = 0;
        } else {
            side_colour++;
            if (side_colour >= LIGHT_COLOUR_MAX) {
                side_rgb    = 1;
                side_colour = 0;
            }
        }
    } else {
        if (side_rgb) {
            side_rgb    = 0;
            side_colour = LIGHT_COLOUR_MAX - 1;
        } else {
            side_colour--;
            if (side_colour >= LIGHT_COLOUR_MAX) {
                side_rgb    = 1;
                side_colour = 0;
            }
        }
    }
    user_config.ee_side_rgb    = side_rgb;
    user_config.ee_side_colour = side_colour;
    nuphy_eeconfig_update_user(&user_config);
}

/**
 * @brief  Change the color mode of side lights.
 * @param  dir: 0 - prev, 1 - next.
 * @note  save to eeprom.
 */
void side_mode_control(uint8_t dir)
{
    if (dir) {
        side_mode++;
        if (side_mode > SIDE_OFF) {
            side_mode = 0;
        }
    } else {
        if (side_mode > 0) {
            side_mode--;
        } else {
            side_mode = SIDE_OFF;
        }
    }
    side_play_point          = 0;
    user_config.ee_side_mode = side_mode;
    nuphy_eeconfig_update_user(&user_config);
}

/**
 * @brief  set left side leds.
 * @param  ...
 */
void set_left_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < SIDE_LINE; i++)
        rgb_matrix_set_color(SIDE_INDEX + i, r, g, b);
}

/**
 * @brief  set right side leds.
 * @param  ...
 */
void set_right_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < SIDE_LINE; i++)
        rgb_matrix_set_color(SIDE_INDEX + SIDE_LINE + i, r, g, b);
}

/**
 * @brief  mac or win system indicate
 */
void sys_sw_led_show(void)
{
    static uint32_t sys_show_timer = 0;
    static bool sys_show_flag      = false;
    extern bool f_sys_show;

    if (f_sys_show) {
        f_sys_show     = false;
        sys_show_timer = timer_read32();
        sys_show_flag  = true;
    }

    if (sys_show_flag) {
        if (dev_info.sys_sw_state == SYS_SW_MAC) {
            r_temp = colour_lib[7][0];
            g_temp = colour_lib[7][1];
            b_temp = colour_lib[7][2];
        } else {
            r_temp = colour_lib[5][0];
            g_temp = colour_lib[5][1];
            b_temp = colour_lib[5][2];
        }
        if ((timer_elapsed32(sys_show_timer) / 500) % 2 == 0) {
            set_right_rgb(r_temp, g_temp, b_temp);
        } else {
            set_right_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sys_show_timer) >= 3000) {
            sys_show_flag = false;
        }
    }
}

/**
 * @brief  sleep enable or disable indicate
 */
void sleep_sw_led_show(void)
{
    static uint32_t sleep_show_timer = 0;
    static bool sleep_show_flag      = false;
    extern bool f_sleep_show;

    if (f_sleep_show) {
        f_sleep_show     = false;
        sleep_show_timer = timer_read32();
        sleep_show_flag  = true;
    }

    if (sleep_show_flag) {
        if (user_config.sleep_enable) {
            r_temp = 0x00;
            g_temp = SIDE_BLINK_LIGHT;
            b_temp = 0x00;
        } else {
            r_temp = 0xff;
            g_temp = 0x00;
            b_temp = 0x00;
        }
        if ((timer_elapsed32(sleep_show_timer) / 500) % 2 == 0) {
            set_right_rgb(r_temp, g_temp, b_temp);
        } else {
            set_right_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sleep_show_timer) >= 3000) {
            sleep_show_flag = false;
        }
    }
}

/**
 * @brief  host system led indicate.
 */
void sys_led_show(void)
{
    if (dev_info.link_mode == LINK_USB) {
        if (host_keyboard_led_state().caps_lock) {
            set_left_rgb(colour_lib[4][0], colour_lib[4][1], colour_lib[4][2]);
        }
    }
    else {
        if (dev_info.rf_led & 0x02) {
            set_left_rgb(colour_lib[4][0], colour_lib[4][1], colour_lib[4][2]);
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
static void light_point_playing(uint8_t trend, uint8_t step, uint8_t len, uint8_t *point)
{
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
static void count_rgb_light(uint8_t light_temp)
{
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
static void side_wave_mode_show(void)
{
    uint8_t play_index;

    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (side_rgb)
        light_point_playing(0, 3, FLOW_COLOUR_TAB_LEN, &side_play_point);
    else
        light_point_playing(0, 2, WAVE_TAB_LEN, &side_play_point);

    play_index = side_play_point;
    for (int i = 0; i < SIDE_LINE; i++) {
        if (side_rgb) {
            r_temp = flow_rainbow_colour_tab[play_index][0];
            g_temp = flow_rainbow_colour_tab[play_index][1] * 0.3;
            b_temp = flow_rainbow_colour_tab[play_index][2] * 0.4;

            light_point_playing(1, 24, FLOW_COLOUR_TAB_LEN, &play_index);

        } else {
            r_temp = colour_lib[side_colour][0];
            g_temp = colour_lib[side_colour][1];
            b_temp = colour_lib[side_colour][2];

            light_point_playing(1, 12, WAVE_TAB_LEN, &play_index);
            count_rgb_light(wave_data_tab[play_index]);
        }

        count_rgb_light(side_light_table[side_light]);

        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp, g_temp, b_temp);
        }
    }
}

/**
 * @brief  side_spectrum_mode_show.
 */
static void side_spectrum_mode_show(void)
{
    //------------------------------
    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    light_point_playing(1, 1, FLOW_COLOUR_TAB_LEN, &side_play_point);

    r_temp = flow_rainbow_colour_tab[side_play_point][0];
    g_temp = flow_rainbow_colour_tab[side_play_point][1];
    b_temp = flow_rainbow_colour_tab[side_play_point][2];

    count_rgb_light(side_light_table[side_light]);

    for (int i = 0; i < SIDE_LINE; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp, g_temp, b_temp);
        }
    }
}

/**
 * @brief  side_breathe_mode_show.
 */
static void side_breathe_mode_show(void)
{
    static uint8_t play_point = 0;

    //------------------------------
    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    //------------------------------
    light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);

    if (0) {
        if (play_point == 0) {
            if (++side_play_point >= LIGHT_COLOUR_MAX)
                side_play_point = 0;
        }

        r_temp = colour_lib[side_play_point][0];
        g_temp = colour_lib[side_play_point][1];
        b_temp = colour_lib[side_play_point][2];
    } else {
        r_temp = colour_lib[side_colour][0];
        g_temp = colour_lib[side_colour][1];
        b_temp = colour_lib[side_colour][2];
    }

    count_rgb_light(breathe_data_tab[play_point]);
    count_rgb_light(side_light_table[side_light]);

    for (int i = 0; i < SIDE_LINE; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp, g_temp, b_temp);
        }
    }
}

/**
 * @brief  side_static_mode_show.
 */
static void side_static_mode_show(void)
{
    uint8_t play_index;

    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (side_play_point >= SIDE_COLOUR_MAX) side_play_point = 0;

    for (int i = 0; i < SIDE_LINE; i++) {
        if (0) {
            r_temp = flow_rainbow_colour_tab[16 * i][0];
            g_temp = flow_rainbow_colour_tab[16 * i][1];
            b_temp = flow_rainbow_colour_tab[16 * i][2];
            light_point_playing(0, 24, FLOW_COLOUR_TAB_LEN, &play_index);
        } else
        {
            r_temp = colour_lib[side_colour][0];
            g_temp = colour_lib[side_colour][1];
            b_temp = colour_lib[side_colour][2];
        }

        count_rgb_light(side_light_table[side_light]);

        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp, g_temp, b_temp);
        }
    }
}

/**
 * @brief  side_off_mode_show.
 */
static void side_off_mode_show(void)
{
    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    r_temp = 0x00;
    g_temp = 0x00;
    b_temp = 0x00;

    for (int i = 0; i < SIDE_LINE; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp, g_temp, b_temp);
        }
    }
}

/**
 * @brief  rf state indicate
 */
#define RF_LED_LINK_PERIOD 500
#define RF_LED_PAIR_PERIOD 250

void rf_led_show(void)
{
    static uint32_t rf_blink_timer = 0;
    uint16_t rf_blink_priod        = 0;

    if (dev_info.link_mode == LINK_RF_24)
    {
        r_temp = colour_lib[3][0];
        g_temp = colour_lib[3][1];
        b_temp = colour_lib[3][2];
    } else if (dev_info.link_mode == LINK_USB) {
        r_temp = colour_lib[2][0];
        g_temp = colour_lib[2][1];
        b_temp = colour_lib[2][2];
    } else
    {
        r_temp = colour_lib[5][0];
        g_temp = colour_lib[5][1];
        b_temp = colour_lib[5][2];
    }

    if (rf_blink_cnt)
    {
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


/**
 * @brief  bat_num_led.
 */
void bat_num_led(uint8_t bat_percent)
{
    uint8_t r, g, b;

    // set color
    if (bat_percent <= 15) {
        r = 0xff; g = 0x00; b = 0x00;
    }
    else if (bat_percent <= 50) {
        r = 0xff; g = 0x40; b = 0x00;
    }
    else if (bat_percent <= 80) {
        r = 0xff; g = 0xff; b = 0x00;
    }
    else {
        r = 0x00; g = 0xff; b = 0x00;
    }

    // set percent
    if (bat_percent >= 1) rgb_matrix_set_color(29, r, g, b);
    if (bat_percent > 10) rgb_matrix_set_color(28, r, g, b);
    if (bat_percent > 20) rgb_matrix_set_color(27, r, g, b);
    if (bat_percent > 30) rgb_matrix_set_color(26, r, g, b);
    if (bat_percent > 40) rgb_matrix_set_color(25, r, g, b);
    if (bat_percent > 50) rgb_matrix_set_color(24, r, g, b);
    if (bat_percent > 60) rgb_matrix_set_color(23, r, g, b);
    if (bat_percent > 70) rgb_matrix_set_color(22, r, g, b);
    if (bat_percent > 80) rgb_matrix_set_color(21, r, g, b);
    if (bat_percent > 90) rgb_matrix_set_color(20, r, g, b);
}

void num_led_show(void)
{
    static uint8_t num_bat_temp         = 0;
    num_bat_temp         = dev_info.rf_baterry;
    bat_num_led(num_bat_temp);
}

void bat_led_close(void)
{
    for(int i=20; i<=29; i++) {
        rgb_matrix_set_color(i,0,0,0);
    }

}

/**
 * @brief  Battery level indicator
 */
uint8_t bat_pwm_buf[6 * 3] = {0};
uint8_t bat_end_led        = 0;
uint8_t bat_r, bat_g, bat_b;

void bat_percent_led(uint8_t bat_percent)
{
    if (bat_percent <= 20) {
        bat_end_led = 0;
        bat_r = colour_lib[0][0]; bat_g = colour_lib[0][1]; bat_b = colour_lib[0][2];
    } else if (bat_percent <= 30) {
        bat_end_led = 1;
        bat_r = colour_lib[1][0]; bat_g = colour_lib[1][1]; bat_b = colour_lib[1][2];
    } else if (bat_percent <= 50) {
        bat_end_led = 2;
        bat_r = colour_lib[1][0]; bat_g = colour_lib[1][1]; bat_b = colour_lib[1][2];
    } else if (bat_percent <= 70) {
        bat_end_led = 3;
        bat_r = colour_lib[1][0]; bat_g = colour_lib[1][1]; bat_b = colour_lib[1][2];
    } else if (bat_percent <= 95) {
        bat_end_led = 4;
        bat_r = colour_lib[1][0]; bat_g = colour_lib[1][1]; bat_b = colour_lib[1][2];
    } else {
        bat_end_led = 4;
        bat_r = colour_lib[3][0]; bat_g = colour_lib[3][1]; bat_b = colour_lib[3][2];
    }

    uint8_t i;
    for (i = 0; i <= bat_end_led; i++)
        rgb_matrix_set_color(SIDE_INDEX + 9 - i, bat_r, bat_g, bat_b);

    for (; i < SIDE_LINE; i++)
        rgb_matrix_set_color(SIDE_INDEX + 9 - i, 0, 0, 0);
}

/**
 * @brief  battery state indicate
 */
void bat_led_show(void)
{
    static uint8_t play_point      = 0;
    static uint32_t bat_play_timer = 0;

    static uint32_t bat_show_time = 0;
    static bool bat_show_flag     = true;
    static bool bat_show_breath   = false;
    static uint32_t bat_sts_debounce = 0;
    static uint32_t bat_per_debounce = 0;
    static uint8_t charge_state      = 0;
    static uint8_t bat_percent       = 0;
    static bool f_init               = 1;

    if (f_init) {
        f_init        = 0;
        bat_show_time = timer_read32();
        charge_state  = dev_info.rf_charge;
        bat_percent   = dev_info.rf_baterry;
    }

    if (charge_state != dev_info.rf_charge) {
        if (timer_elapsed32(bat_sts_debounce) > 1000) {
            if (((charge_state & 0x01) == 0) && ((dev_info.rf_charge & 0x01) != 0)) {
                bat_show_flag   = true;
                bat_show_breath = true;
                bat_show_time   = timer_read32();
            }
            charge_state = dev_info.rf_charge;
        }
    }
    else {
        bat_sts_debounce = timer_read32();

        if (timer_elapsed32(bat_show_time) > 5000) {
            bat_show_flag   = false;
            bat_show_breath = false;
        }
        if (charge_state == 0x03) {
            bat_show_breath = true;
        }
        else if (charge_state & 0x01) {
            dev_info.rf_baterry = 100;
        }
    }

    if (bat_percent != dev_info.rf_baterry) {
        if (timer_elapsed32(bat_per_debounce) > 1000) {
            bat_percent = dev_info.rf_baterry;
        }
    }
    else {
        bat_per_debounce = timer_read32();
        if (bat_percent < 15) {
            bat_show_flag = true;
            bat_show_time = timer_read32();
        }
    }

    if (f_bat_hold || bat_show_flag) {
        if (bat_show_breath) {
            if (timer_elapsed32(bat_play_timer) > 10) {
                bat_play_timer = timer_read32();
                light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);
            }
            r_temp = colour_lib[1][0];
            g_temp = colour_lib[1][1];
            b_temp = colour_lib[1][2];
            count_rgb_light(breathe_data_tab[play_point]);
            set_right_rgb(r_temp, g_temp, b_temp);
        }
        else {
            bat_percent_led(bat_percent);
        }
    }
}


/**
 * @brief  device_reset_show.
 */
void rgb_matrix_update_pwm_buffers(void);
void device_reset_show(void)
{
    writePinHigh(DC_BOOST_PIN);
    writePinHigh(RGB_DRIVER_SDB1);
    writePinHigh(RGB_DRIVER_SDB2);
    for (int blink_cnt = 0; blink_cnt < 3; blink_cnt++) {
        rgb_matrix_set_color_all(0xFF, 0xFF, 0xFF);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);

        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);
    }
}

/**
 * @brief  device_reset_init.
 */
void device_reset_init(void)
{
    side_mode       = 0;
    side_light      = 3;
    side_speed      = 2;
    side_rgb        = 1;
    side_colour     = 0;
    side_play_point = 0;

    side_play_cnt   = 0;
    side_play_timer = timer_read32();

    f_bat_hold = false;

    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
    rgb_matrix_set_speed(255 - RGB_MATRIX_SPD_STEP * 2);
    rgb_matrix_sethsv(255, 255, RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP * 2);

    user_config.default_brightness_flag = 0xA5;
    user_config.ee_side_mode            = side_mode;
    user_config.ee_side_light           = side_light;
    user_config.ee_side_speed           = side_speed;
    user_config.ee_side_rgb             = side_rgb;
    user_config.ee_side_colour          = side_colour;
    user_config.sleep_enable            = true;
    nuphy_eeconfig_update_user(&user_config);
}

/**
 * @brief  rgb test
 */
void rgb_test_show(void)
{
    writePinHigh(DC_BOOST_PIN);
    writePinHigh(RGB_DRIVER_SDB1);
    writePinHigh(RGB_DRIVER_SDB2);

    // set test color
    rgb_matrix_set_color_all(0xFF, 0x00, 0x00);
    rgb_matrix_update_pwm_buffers();
    wait_ms(500);

    rgb_matrix_set_color_all(0x00, 0xFF, 0x00);
    rgb_matrix_update_pwm_buffers();
    wait_ms(500);

    rgb_matrix_set_color_all(0x00, 0x00, 0xFF);
    rgb_matrix_update_pwm_buffers();
    wait_ms(500);

    rgb_matrix_set_color_all(0x80, 0x80, 0x80);
    rgb_matrix_update_pwm_buffers();
    wait_ms(500);

    rgb_matrix_set_color_all(0x80, 0x80, 0x00);
    rgb_matrix_update_pwm_buffers();
    wait_ms(500);

    rgb_matrix_set_color_all(0x80, 0x00, 0x80);
    rgb_matrix_update_pwm_buffers();
    wait_ms(500);

    rgb_matrix_set_color_all(0x00, 0x80, 0x80);
    rgb_matrix_update_pwm_buffers();
    wait_ms(500);
}

/**
 * @brief  side_led_show.
 */
void m_side_led_show(void)
{
    side_play_cnt += timer_elapsed32(side_play_timer);
    side_play_timer = timer_read32();  // store time of last refresh

    switch (side_mode) {
        case SIDE_WAVE:     side_wave_mode_show();      break;
        case SIDE_MIX:      side_spectrum_mode_show();  break;
        case SIDE_BREATH:   side_breathe_mode_show();   break;
        case SIDE_STATIC:   side_static_mode_show();    break;
        case SIDE_OFF:      side_off_mode_show();       break;
    }

    bat_led_show();
    sleep_sw_led_show();
    sys_sw_led_show();

    sys_led_show();
    rf_led_show();
}
