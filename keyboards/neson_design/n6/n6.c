/**
 * @file n6.c
 *
    Copyright 2021 astro

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

#include "quantum.h"
#include "i2c_master.h"
#include "drivers/led/issi/is31fl3731.h"
#include "ws2812.h"

enum {
    SELF_TESTING,
    CAPS_ALERT,
    NORMAL,
};

enum {
    ST_STAGE_1,
    ST_STAGE_2,
    ST_STAGE_3,
};

// alert state update interval
#define ALERT_INTERVAL      500
// self testing state update interval
#define ST_INTERVAL         100
// self testing start index
#define ST_DEFAULT_INDEX    15
// self testing stage delay
#define ST_STAGE_DELAY      10
// self testing stage cycle count
#define ST_STAGE_COUNT      4
// self testing stage end duration
#define ST_END_DURATION     10

// led index
#define ST_LEFT_BEGIN       0
#ifdef IS31FL3731_I2C_ADDRESS_2
#define ST_LEFT_SIZE        4
#else
#define ST_LEFT_SIZE        2
#endif
#define ST_LEFT_END         (ST_LEFT_BEGIN+ST_LEFT_SIZE-1)
#ifdef IS31FL3731_I2C_ADDRESS_2
#define ST_RIGHT_BEGIN      60
#else
#define ST_RIGHT_BEGIN      30
#endif
#ifdef IS31FL3731_I2C_ADDRESS_2
#define ST_RIGHT_SIZE       4
#else
#define ST_RIGHT_SIZE       2
#endif
#define ST_RIGHT_END        (ST_RIGHT_BEGIN+ST_RIGHT_SIZE-1)

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;

typedef struct {
    uint8_t state;
    uint8_t testing;
    bool    alert;
    uint8_t index;
    uint8_t delay;
    uint8_t count;
    bool    dir;
    uint8_t duration;
    uint16_t ticks;
} rgb_state_t;

static rgb_state_t rgb_state = {
    .state = //NORMAL,
    SELF_TESTING,
    .testing = ST_STAGE_1,
    .ticks = 0,
    .alert = false,
    .index = ST_DEFAULT_INDEX,
    .delay = ST_STAGE_DELAY,
    .count = ST_STAGE_COUNT,
    .dir = true,
    .duration = ST_END_DURATION,
};

static void update_ticks(void)
{
    rgb_state.ticks = timer_read();
}

static void self_testing(void)
{
    if (timer_elapsed(rgb_state.ticks) < ST_INTERVAL) return;
    HSV hsv;
    hsv.h = rgblight_config.hue;
    hsv.s = rgblight_config.sat;
    hsv.v = rgblight_config.val;

    RGB led = hsv_to_rgb(hsv);
    switch(rgb_state.testing) {
        case ST_STAGE_1:
            if (rgb_state.index !=0 ) {
                is31fl3731_set_color_all(0, 0, 0);
            }

            if (rgb_state.index >= ST_LEFT_END) {
                for (int i = rgb_state.index - 1; i < IS31FL3731_LED_COUNT - rgb_state.index + 1; i++) {
                    is31fl3731_set_color(i, led.r, led.g, led.b);
                }
                if (rgb_state.index == ST_LEFT_END) {
                    rgb_state.index = ST_LEFT_BEGIN;
                } else {
                    rgb_state.index -= ST_LEFT_SIZE;
                }
            } else{
                if (rgb_state.delay > 0) {
                    rgb_state.delay--;
                } else {
                    // move to stage 2
                    rgb_state.index = ST_LEFT_BEGIN+ST_LEFT_SIZE;
                    rgb_state.testing = ST_STAGE_2;
                }
            }
        break;
        case ST_STAGE_2: {
            // clear all
            is31fl3731_set_color_all(0, 0, 0);
            int i = 0;
            // light left and right
            for (i = 0; i < ST_LEFT_SIZE; i++) {
                is31fl3731_set_color(ST_LEFT_BEGIN+i, led.r, led.g, led.b);
            }
            for (i = 0; i < ST_RIGHT_SIZE; i++) {
                is31fl3731_set_color(ST_RIGHT_BEGIN+i, led.r, led.g, led.b);

            }
            if (rgb_state.dir) {
                // left to right
                for (int i = rgb_state.index; i < rgb_state.index+ST_LEFT_SIZE+ST_RIGHT_SIZE; i++) {
                    is31fl3731_set_color(i, led.r, led.g, led.b);
                }
                rgb_state.index += ST_LEFT_SIZE+ST_RIGHT_SIZE;
                if (rgb_state.index == ST_RIGHT_BEGIN) {
                    rgb_state.dir = !rgb_state.dir;
                    rgb_state.count--;
                }
            } else {
                // right to left
                for (int i = rgb_state.index - ST_RIGHT_SIZE; i < rgb_state.index; i++) {
                    is31fl3731_set_color(i, led.r, led.g, led.b);
                }
                rgb_state.index -= ST_LEFT_SIZE + ST_RIGHT_SIZE;
                if (rgb_state.index == ST_LEFT_BEGIN+ST_LEFT_SIZE) {
                    rgb_state.dir = !rgb_state.dir;
                    rgb_state.count--;
                }
            }

            if (rgb_state.count == 0) {
                // move to stage 3
                rgb_state.testing = ST_STAGE_3;
                rgb_state.index = 0;
                rgb_state.delay = ST_STAGE_DELAY;
                rgb_state.duration = ST_END_DURATION;
            }
        }
        break;
        case ST_STAGE_3:
            if (rgb_state.index != IS31FL3731_LED_COUNT/2) {
                is31fl3731_set_color_all(0, 0, 0);
            }

            // light left and right

            if (rgb_state.index == IS31FL3731_LED_COUNT/2) {
                if (rgb_state.duration) {
                    rgb_state.duration--;
                } else {
                    if (host_keyboard_led_state().caps_lock) {
                        rgb_state.state = CAPS_ALERT;
                    } else {
                        rgb_state.state = NORMAL;
                        rgblight_set();
                    }
                }
            } else {
                // left
                for (int i = 0; i < rgb_state.index+1; i++) {
                    is31fl3731_set_color(i, led.r, led.g, led.b);
                }
                // right
                for (int i = ST_RIGHT_END; i > ST_RIGHT_END - rgb_state.index - 1; i--) {
                    is31fl3731_set_color(i, led.r, led.g, led.b);
                }
                rgb_state.index ++;
            }
        break;
    }

    update_ticks();
}

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
    /* Refer to IS31 manual for these locations
     *   driver
     *   |  R location
     *   |  |       G location
     *   |  |       |       B location
     *   |  |       |       | */
    // left CA
    {0, C1_1, C3_2, C4_2},
    {0, C1_2, C2_2, C4_3},
    {0, C1_3, C2_3, C3_3},
    {0, C1_4, C2_4, C3_4},
    {0, C1_5, C2_5, C3_5},
    {0, C1_6, C2_6, C3_6},
    {0, C1_7, C2_7, C3_7},
    {0, C1_8, C2_8, C3_8},

    {0, C9_1, C8_1, C7_1},
    {0, C9_2, C8_2, C7_2},
    {0, C9_3, C8_3, C7_3},
    {0, C9_4, C8_4, C7_4},
    {0, C9_5, C8_5, C7_5},
    {0, C9_6, C8_6, C7_6},
    {0, C9_7, C8_7, C6_6},
    {0, C9_8, C7_7, C6_7},
    // left CB
    {0, C1_9, C3_10, C4_10},
    {0, C1_10, C2_10, C4_11},
    {0, C1_11, C2_11, C3_11},
    {0, C1_12, C2_12, C3_12},
    {0, C1_13, C2_13, C3_13},
    {0, C1_14, C2_14, C3_14},
    {0, C1_15, C2_15, C3_15},
    {0, C1_16, C2_16, C3_16},

    {0, C9_9, C8_9, C7_9},
    {0, C9_10, C8_10, C7_10},
    {0, C9_11, C8_11, C7_11},
    {0, C9_12, C8_12, C7_12},
    {0, C9_13, C8_13, C7_13},
    {0, C9_14, C8_14, C7_14},
    {0, C9_15, C8_15, C6_14},
    {0, C9_16, C7_15, C6_15},

    // right CA
    {1, C1_1, C3_2, C4_2},
    {1, C1_2, C2_2, C4_3},
    {1, C1_3, C2_3, C3_3},
    {1, C1_4, C2_4, C3_4},
    {1, C1_5, C2_5, C3_5},
    {1, C1_6, C2_6, C3_6},
    {1, C1_7, C2_7, C3_7},
    {1, C1_8, C2_8, C3_8},

    {1, C9_1, C8_1, C7_1},
    {1, C9_2, C8_2, C7_2},
    {1, C9_3, C8_3, C7_3},
    {1, C9_4, C8_4, C7_4},
    {1, C9_5, C8_5, C7_5},
    {1, C9_6, C8_6, C7_6},
    {1, C9_7, C8_7, C6_6},
    {1, C9_8, C7_7, C6_7},
    // right CB
    {1, C1_9, C3_10, C4_10},
    {1, C1_10, C2_10, C4_11},
    {1, C1_11, C2_11, C3_11},
    {1, C1_12, C2_12, C3_12},
    {1, C1_13, C2_13, C3_13},
    {1, C1_14, C2_14, C3_14},
    {1, C1_15, C2_15, C3_15},
    {1, C1_16, C2_16, C3_16},

    {1, C9_9, C8_9, C7_9},
    {1, C9_10, C8_10, C7_10},
    {1, C9_11, C8_11, C7_11},
    {1, C9_12, C8_12, C7_12},
    {1, C9_13, C8_13, C7_13},
    {1, C9_14, C8_14, C7_14},
    {1, C9_15, C8_15, C6_14},
    {1, C9_16, C7_15, C6_15},
};

void matrix_init_kb(void)
{
    gpio_set_pin_output(LED_CAPS_LOCK_PIN);
    gpio_write_pin_low(LED_CAPS_LOCK_PIN);

    is31fl3731_init_drivers();

    update_ticks();
    matrix_init_user();
}

void housekeeping_task_kb(void)
{
    if (rgb_state.state == SELF_TESTING) {
        self_testing();
    } else if (rgb_state.state == CAPS_ALERT) {
        //gold 0xFF, 0xD9, 0x00
        rgb_led_t led = {
            .r = 0xFF,
            //.g = 0xD9,
            .g = 0xA5,
            .b = 0x00,
        };
        if (rgb_state.alert) {
            is31fl3731_set_color_all(led.r, led.g, led.b);
            ws2812_setleds(&led, 1);
        } else {
            led.r = 0;
            led.g = 0;
            led.b = 0;
            is31fl3731_set_color_all(0, 0, 0);
            ws2812_setleds(&led, 1);
        }

        if (timer_elapsed(rgb_state.ticks) > ALERT_INTERVAL) {
            rgb_state.alert = !rgb_state.alert;
            update_ticks();
        }
    }

    is31fl3731_flush();

    housekeeping_task_user();
}

void setleds_custom(rgb_led_t *start_led, uint16_t num_leds)
{
    if (rgb_state.state != NORMAL) return;

    for (uint8_t i = 0; i < IS31FL3731_LED_COUNT; i++) {
        is31fl3731_set_color(i, start_led[i].r, start_led[i].g, start_led[i].b);
    }
    ws2812_setleds(start_led+IS31FL3731_LED_COUNT, 1);
}

const rgblight_driver_t rgblight_driver = {
    .init    = ws2812_init,
    .setleds = setleds_custom,
};

bool led_update_kb(led_t led_state)
{
    bool res = led_update_user(led_state);
    if (res) {
        gpio_write_pin(LED_CAPS_LOCK_PIN, led_state.caps_lock);

        if (rgb_state.state != SELF_TESTING) {
            if (led_state.caps_lock) {
                rgb_state.state = CAPS_ALERT;
                update_ticks();
            } else {
                rgb_state.state = NORMAL;
                rgblight_set();
            }
        }
    }
    return res;
}

#endif