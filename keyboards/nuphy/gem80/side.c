// Copyright 2023 Ryodeushii (@ryodeushii)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdint.h>
#include "color.h"
#include "host.h"
#include "rgb_matrix.h"
#include "timer.h"
#include "side.h"
#include "common/side_table.h"
#include "common/side_effects.h"
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

uint8_t  side_play_point   = 0;
uint8_t  low_bat_blink_cnt = 6;
uint8_t  side_play_cnt     = 0;
uint32_t side_play_timer   = 0;
uint8_t  r_temp, g_temp, b_temp;

extern DEV_INFO_STRUCT dev_info;
extern bool            f_bat_hold;
extern bool            f_dial_sw_init_ok;
extern uint8_t         logo_play_point;
extern uint8_t         rf_blink_cnt;
extern uint16_t        rf_link_show_time;
extern uint8_t         logo_play_cnt;
extern uint32_t        logo_play_timer;

RGB side_leds[SIDE_LED_NUM] = {0};

void side_ws2812_setleds(RGB *ledarray, uint16_t leds);
void rgb_matrix_update_pwm_buffers(void);
void logo_led_loop(void);

// Keyboard-specific implementations

void side_rgb_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    side_leds[index].r = red;
    side_leds[index].g = green;
    side_leds[index].b = blue;
}

void side_rgb_refresh(void) {
    side_ws2812_setleds(side_leds, SIDE_LED_NUM);
}

void set_side_rgb(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < SIDE_LINE; i++)
        side_rgb_set_color(i, r >> 2, g >> 2, b >> 2);
}

void set_indicator_on_side(uint8_t r, uint8_t g, uint8_t b) {
    set_side_rgb(r, g, b);
}

// Control functions - keyboard-specific implementations that use common config

void side_brightness_control(uint8_t brighten) {
    if (brighten) {
        if (keyboard_config.lights.side_brightness == 5) return;
        keyboard_config.lights.side_brightness++;
    } else {
        if (keyboard_config.lights.side_brightness == 0) return;
        keyboard_config.lights.side_brightness--;
    }
    save_config_to_eeprom();
}

void side_speed_control(uint8_t fast) {
    if ((keyboard_config.lights.side_speed) > LIGHT_SPEED_MAX) (keyboard_config.lights.side_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if (keyboard_config.lights.side_speed) keyboard_config.lights.side_speed--;
    } else {
        if (keyboard_config.lights.side_speed < LIGHT_SPEED_MAX) keyboard_config.lights.side_speed++;
    }
    save_config_to_eeprom();
}

void side_color_control(uint8_t dir) {
    if (keyboard_config.lights.side_mode != SIDE_WAVE) {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb   = 0;
            keyboard_config.lights.side_color = 0;
        }
    }

    if (dir) {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb   = 0;
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

// Battery LED show - keyboard-specific
void bat_led_show(void) {
    uint8_t bat_percent   = dev_info.rf_battery;
    uint8_t bat_show_flag = 0;

    if (dev_info.rf_charge) {
        if (f_charging) {
            bat_charging_breathe();
            return;
        }
    } else {
        if (f_charging) {
            f_charging      = 0;
            side_play_point = 0;
        }
    }

    if (f_bat_hold) {
        if (bat_percent < 10) {
            bat_show_flag = 1;
        } else {
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

// Keyboard-specific hook for side_led_show
void side_led_show_kb(void) {
    logo_led_loop();
}

// Device reset show - keyboard-specific
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
