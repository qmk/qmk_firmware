// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "ansi_tkl.h"

#include "print.h"
#include "sidetable.h"

#define LAYER_MAC_MODE (1)
#define LAYER_WIN_MODE (2)

typedef struct {
    uint8_t ee_init_flag;
    uint8_t ee_layer_mode;
    uint8_t ee_side_mode;
    uint8_t ee_side_light;
    uint8_t ee_side_speed;
    uint8_t ee_side_rgb;
    uint8_t ee_side_colour;
    uint8_t retain1;
} user_config_t;

user_config_t user_config;

#define SIDE_WAVE    0
#define SIDE_MIX     1
#define SIDE_STATIC  2
#define SIDE_BREATH  3
#define SIDE_OFF     4

#define SIDE_LED_NUM 4
const uint8_t side_led_index_tab[SIDE_LED_NUM][2] = {
    {84, 85},
    {83, 86},
    {82, 87},
    {81, 88},
};

uint8_t side_mode       = 0;
uint8_t side_light      = 40;
uint8_t side_speed      = 3;
uint8_t side_rgb        = 1;
uint8_t side_colour     = 0;
uint8_t side_play_point = 0;

uint32_t side_play_cnt   = 0;
uint32_t side_play_timer = 0;

uint8_t r_temp, g_temp, b_temp;

bool f_layer_win_press = 0;
bool f_layer_mac_press = 0;
bool f_reset_press     = 0;

#define SIDE_COLOUR_MAX 8
#define LIGHT_SPEED_MAX 4

uint8_t side_speed_table[5][5] = {
    [SIDE_WAVE]   = {10, 14, 20, 28, 38},
    [SIDE_MIX]    = {10, 14, 20, 28, 38},
    [SIDE_STATIC] = {50, 50, 50, 50, 50},
    [SIDE_BREATH] = {10, 14, 20, 28, 38},
    [SIDE_OFF]    = {50, 50, 50, 50, 50},
};

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

void light_level_control(uint8_t brighten)
{
    if (brighten) {
        if (side_light == 100) {
            return;
        } else if (side_light >= 80)
            side_light = 100;
        else if (side_light >= 60)
            side_light = 80;
        else if (side_light >= 40)
            side_light = 60;
        else if (side_light >= 20)
            side_light = 40;
        else
            side_light = 20;
    } else {
        if (side_light == 0) {
            return;
        } else if (side_light > 80)
            side_light = 80;
        else if (side_light > 60)
            side_light = 60;
        else if (side_light > 40)
            side_light = 40;
        else if (side_light > 20)
            side_light = 20;
        else
            side_light = 0;
    }
    user_config.ee_side_light = side_light;
    eeconfig_update_user_datablock(&user_config);
}

void light_speed_contol(uint8_t fast)
{
    if ((side_speed) > LIGHT_SPEED_MAX)
        (side_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if ((side_speed)) side_speed--;
    } else {
        if ((side_speed) < LIGHT_SPEED_MAX) side_speed++;
    }
    user_config.ee_side_speed = side_speed;
    eeconfig_update_user_datablock(&user_config);
}

void side_colour_control(uint8_t dir)
{
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
                side_rgb = 1;
            }
        }
    }
    user_config.ee_side_rgb    = side_rgb;
    user_config.ee_side_colour = side_colour;
    eeconfig_update_user_datablock(&user_config);
}

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
    eeconfig_update_user_datablock(&user_config);
}

void set_left_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < 4; i++) {
        rgb_matrix_set_color(81 + i, r >> 2, g >> 2, b >> 2);
    }
}

void set_right_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < 4; i++) {
        rgb_matrix_set_color(85 + i, r >> 2, g >> 2, b >> 2);
    }
}

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
    for (int i = 0; i < SIDE_LED_NUM; i++) {
        if (side_rgb) {
            r_temp = flow_rainbow_colour_tab[play_index][0];
            g_temp = flow_rainbow_colour_tab[play_index][1];
            b_temp = flow_rainbow_colour_tab[play_index][2];

            light_point_playing(1, 16, FLOW_COLOUR_TAB_LEN, &play_index);
        } else {
            r_temp = colour_lib[side_colour][0];
            g_temp = colour_lib[side_colour][1];
            b_temp = colour_lib[side_colour][2];

            light_point_playing(1, 12, WAVE_TAB_LEN, &play_index);
            count_rgb_light(wave_data_tab[play_index]);
        }
        count_rgb_light(light_value_tab[side_light]);
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

static void side_spectrum_mode_show(void)
{
    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    light_point_playing(1, 1, FLOW_COLOUR_TAB_LEN, &side_play_point);

    r_temp = flow_rainbow_colour_tab[side_play_point][0];
    g_temp = flow_rainbow_colour_tab[side_play_point][1];
    b_temp = flow_rainbow_colour_tab[side_play_point][2];

    count_rgb_light(light_value_tab[side_light]);

    for (int i = 0; i < SIDE_LED_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

static void side_breathe_mode_show(void)
{
    static uint8_t play_point = 0;

    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);

    if (side_rgb) {
        if (play_point == 0) {
            if (++side_play_point >= LIGHT_COLOUR_MAX) side_play_point = 0;
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
    count_rgb_light(light_value_tab[side_light]);

    for (int i = 0; i < SIDE_LED_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

static void side_static_mode_show(void)
{
    uint8_t play_index;

    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (side_play_point >= SIDE_COLOUR_MAX) side_play_point = 0;

    for (int i = 0; i < SIDE_LED_NUM; i++) {
        if (side_rgb) {
            r_temp = flow_rainbow_colour_tab[16 * i][0];
            g_temp = flow_rainbow_colour_tab[16 * i][1];
            b_temp = flow_rainbow_colour_tab[16 * i][2];
            light_point_playing(0, 24, FLOW_COLOUR_TAB_LEN, &play_index);
        } else {
            r_temp = colour_lib[side_colour][0];
            g_temp = colour_lib[side_colour][1];
            b_temp = colour_lib[side_colour][2];
        }
        count_rgb_light(light_value_tab[side_light]);
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

void set_side_colour(uint8_t r_temp, uint8_t g_temp, uint8_t b_temp)
{
    for (int i = 0; i < SIDE_LED_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

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

    for (int i = 0; i < SIDE_LED_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

void m_side_led_show(void)
{
    side_play_cnt += timer_elapsed32(side_play_timer);
    side_play_timer = timer_read32();

    switch (side_mode) {
        case SIDE_WAVE:
            side_wave_mode_show();
            break;
        case SIDE_MIX:
            side_spectrum_mode_show();
            break;
        case SIDE_STATIC:
            side_static_mode_show();
            break;
        case SIDE_BREATH:
            side_breathe_mode_show();
            break;
        case SIDE_OFF:
            side_off_mode_show();
            break;
    }

    if (host_keyboard_led_state().caps_lock) {
        set_left_rgb(0x00, 0xff, 0xff);
    }
}

void rgb_matrix_update_pwm_buffers(void);
void device_reset_show(void)
{
    for (int blink_cnt = 0; blink_cnt < 3; blink_cnt++) {
        rgb_matrix_set_color_all(0x40, 0x40, 0x40);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);

        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);
    }
}

void device_sys_show(void)
{
    if (user_config.ee_layer_mode == LAYER_MAC_MODE) {
        r_temp = 0xff;
        g_temp = 0xff;
        b_temp = 0xff;
    } else {
        r_temp = 0x00;
        g_temp = 0x00;
        b_temp = 0xff;
    }

    for (int blink_cnt = 0; blink_cnt < 3; blink_cnt++) {
        set_right_rgb(r_temp, g_temp, b_temp);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);

        set_right_rgb(0, 0, 0);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);
    }
}

void device_reset_init(void)
{
    side_mode       = 0;
    side_light      = 40;
    side_speed      = 3;
    side_rgb        = 1;
    side_colour     = 0;
    side_play_cnt   = 0;
    side_play_point = 0;
    side_play_timer = timer_read32();

    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
    rgb_matrix_set_speed(255 - RGB_MATRIX_SPD_STEP * 2);
    rgb_matrix_sethsv(255, 255, RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP * 2);

    default_layer_set(1 << 0);
    keymap_config.nkro        = 0;
    user_config.ee_layer_mode = LAYER_MAC_MODE;

    user_config.ee_init_flag   = 0xA5;
    user_config.ee_side_mode   = side_mode;
    user_config.ee_side_light  = side_light;
    user_config.ee_side_speed  = side_speed;
    user_config.ee_side_rgb    = side_rgb;
    user_config.ee_side_colour = side_colour;
    eeconfig_update_user_datablock(&user_config);
}

void long_press_key(void)
{
    static uint32_t long_press_timer = 0;
    static uint16_t reset_press_time = 0;
    static uint16_t layer_sw_press_time;

    if (timer_elapsed32(long_press_timer) < 100) return;
    long_press_timer = timer_read32();

    if (f_layer_mac_press || f_layer_win_press) {
        layer_sw_press_time++;
        if (layer_sw_press_time >= 30) {
            layer_sw_press_time = 0;

            if (f_layer_mac_press) {
                default_layer_set(1 << 0);
                keymap_config.nkro        = 0;
                user_config.ee_layer_mode = LAYER_MAC_MODE;
            } else if (f_layer_win_press) {
                default_layer_set(1 << 2);
                keymap_config.nkro        = 1;
                user_config.ee_layer_mode = LAYER_WIN_MODE;
            }
            f_layer_win_press = 0;
            f_layer_mac_press = 0;

            eeconfig_update_user_datablock(&user_config);

            device_sys_show();
        }
    } else {
        layer_sw_press_time = 0;
    }

    if (f_reset_press) {
        reset_press_time++;
        if (reset_press_time >= 30) {
            reset_press_time = 0;

            f_reset_press = 0;
            eeconfig_init();

            device_reset_show();

            device_reset_init();
        }
    } else {
        reset_press_time = 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case MAC_TASK: {
            if (record->event.pressed) {
                host_consumer_send(0x029F);
            } else {
                host_consumer_send(0);
            }
            return false;
        }
        case MAC_SEARCH: {
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code_delay(KC_SPACE, 50);
                unregister_code(KC_LGUI);
            }
            return false;
        }
        case MAC_VOICE: {
            if (record->event.pressed) {
                host_consumer_send(0xcf);
            } else {
                host_consumer_send(0);
            }
            return false;
        }
        case MAC_DNT: {
            if (record->event.pressed) {
                host_consumer_send(0x02A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        }
        case SIDE_VAI: {
            if (record->event.pressed) {
                light_level_control(1);
            }
            return false;
        }
        case SIDE_VAD: {
            if (record->event.pressed) {
                light_level_control(0);
            }
            return false;
        }
        case SIDE_MOD: {
            if (record->event.pressed) {
                side_mode_control(1);
            }
            return false;
        }
        case SIDE_HUI: {
            if (record->event.pressed) {
                side_colour_control(1);
            }
            return false;
        }
        case SIDE_SPI: {
            if (record->event.pressed) {
                light_speed_contol(1);
            }
            return false;
        }
        case SIDE_SPD: {
            if (record->event.pressed) {
                light_speed_contol(0);
            }
            return false;
        }
        case SYS_WIN: {
            if (record->event.pressed) {
                f_layer_win_press = 1;
            } else {
                f_layer_win_press = 0;
            }
            return false;
        }
        case SYS_MAC: {
            if (record->event.pressed) {
                f_layer_mac_press = 1;
            } else {
                f_layer_mac_press = 0;
            }
            return false;
        }
        case DEV_RESET: {
            if (record->event.pressed) {
                f_reset_press = 1;
            } else {
                f_reset_press = 0;
            }
            return false;
        }
        default:
            return true;
    }
    return true;
};

void sys_layer_init(void)
{
    eeconfig_read_user_datablock(&user_config);

    if (user_config.ee_init_flag != 0xA5) {
        rgb_matrix_sethsv(255, 255, RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP * 2);
        user_config.ee_init_flag   = 0xA5;
        user_config.ee_layer_mode  = LAYER_MAC_MODE;
        user_config.ee_side_mode   = side_mode;
        user_config.ee_side_light  = side_light;
        user_config.ee_side_speed  = side_speed;
        user_config.ee_side_rgb    = side_rgb;
        user_config.ee_side_colour = side_colour;
        eeconfig_update_user_datablock(&user_config);
    } else {
        side_mode   = user_config.ee_side_mode;
        side_light  = user_config.ee_side_light;
        side_speed  = user_config.ee_side_speed;
        side_rgb    = user_config.ee_side_rgb;
        side_colour = user_config.ee_side_colour;
    }

    if (user_config.ee_layer_mode == LAYER_MAC_MODE) {
        default_layer_set(1 << 0);
        keymap_config.nkro = 0;
    } else if (user_config.ee_layer_mode == LAYER_WIN_MODE) {
        default_layer_set(1 << 2);
        keymap_config.nkro = 1;
    } else {
        user_config.ee_layer_mode = LAYER_MAC_MODE;
        default_layer_set(1 << 0);
        keymap_config.nkro = 0;
        eeconfig_update_user_datablock(&user_config);
    }
}

void keyboard_post_init_user(void)
{
    // debug_enable = true;

    sys_layer_init();

    rgb_matrix_set_color_all(0x00, 0x00, 0x00);
    rgb_matrix_update_pwm_buffers();
}

bool rgb_matrix_indicators_user(void)
{
    m_side_led_show();

    return true;
}

void housekeeping_task_user(void)
{
    long_press_key();
}
