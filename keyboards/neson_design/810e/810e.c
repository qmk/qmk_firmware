/**
 * Copyright 2024 astro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "810e.h"
#include "i2c_master.h"
#include "is31fl3729.h"

#define IS31FL3236_ADDR     /*0x3C*/ 0x78
#define IS31FL3729_ADDR_1   /*0x34*/ 0x68
#define IS31FL3729_ADDR_2   /*0x37*/ 0x6E

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
#define ST_LEFT_SIZE        3

#define ST_LEFT_END         (ST_LEFT_BEGIN+ST_LEFT_SIZE-1)

#define ST_RIGHT_BEGIN      87
#define ST_RIGHT_SIZE       3
#define ST_RIGHT_END        (ST_RIGHT_BEGIN+ST_RIGHT_SIZE-1)

#ifdef RGBLIGHT_ENABLE

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
    HSV hsv = rgblight_get_hsv();

    RGB led = hsv_to_rgb(hsv);
    switch(rgb_state.testing) {
        case ST_STAGE_1:
            if (rgb_state.index !=0 ) {
                IS31FL3729_set_color_all(0, 0, 0);
            }

            if (rgb_state.index >= ST_LEFT_END) {
                for (int i = rgb_state.index - 1; i < IS31FL3729_LED_TOTAL - rgb_state.index + 1; i++) {
                    IS31FL3729_set_color(i, led.r, led.g, led.b);
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
            IS31FL3729_set_color_all(0, 0, 0);
            int i = 0;
            // light left and right
            for (i = 0; i < ST_LEFT_SIZE; i++) {
                IS31FL3729_set_color(ST_LEFT_BEGIN+i, led.r, led.g, led.b);
            }
            for (i = 0; i < ST_RIGHT_SIZE; i++) {
                IS31FL3729_set_color(ST_RIGHT_BEGIN+i, led.r, led.g, led.b);
            }
            if (rgb_state.dir) {
                // left to right
                for (int i = rgb_state.index; i < rgb_state.index+ST_LEFT_SIZE+ST_RIGHT_SIZE; i++) {
                    IS31FL3729_set_color(i, led.r, led.g, led.b);
                }
                rgb_state.index += ST_LEFT_SIZE+ST_RIGHT_SIZE;
                if (rgb_state.index >= ST_RIGHT_BEGIN) {
                    rgb_state.dir = !rgb_state.dir;
                    rgb_state.count--;
                }
            } else {
                // right to left
                for (int i = rgb_state.index - ST_LEFT_SIZE - ST_RIGHT_SIZE; i < rgb_state.index; i++) {
                    IS31FL3729_set_color(i, led.r, led.g, led.b);
                }
                rgb_state.index = rgb_state.index - ST_LEFT_SIZE - ST_RIGHT_SIZE;
                if (rgb_state.index <= ST_LEFT_BEGIN+ST_LEFT_SIZE) {
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
            if (rgb_state.index != IS31FL3729_LED_TOTAL/2) {
                IS31FL3729_set_color_all(0, 0, 0);
            }

            // light left and right

            if (rgb_state.index == IS31FL3729_LED_TOTAL/2) {
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
                    IS31FL3729_set_color(i, led.r, led.g, led.b);
                }
                // right
                for (int i = ST_RIGHT_END; i > ST_RIGHT_END - rgb_state.index - 1; i--) {
                    IS31FL3729_set_color(i, led.r, led.g, led.b);
                }
                rgb_state.index ++;
            }
        break;
    }

    update_ticks();
}

const is31_led PROGMEM g_is31_leds[RGB_LED_TOTAL] = {
    /* Refer to IS31 manual for these locations
     *   driver
     *   |  R location
     *   |  |       G location
     *   |  |       |       B location
     *   |  |       |       | */
    // left
    {0,  CS2_SW1_29,  CS1_SW1_29,  CS3_SW1_29},
    {0,  CS2_SW2_29,  CS1_SW2_29,  CS3_SW2_29},
    {0,  CS2_SW3_29,  CS1_SW3_29,  CS3_SW3_29},
    {0,  CS2_SW4_29,  CS1_SW4_29,  CS3_SW4_29},
    {0,  CS2_SW5_29,  CS1_SW5_29,  CS3_SW5_29},
    {0,  CS2_SW6_29,  CS1_SW6_29,  CS3_SW6_29},
    {0,  CS2_SW7_29,  CS1_SW7_29,  CS3_SW7_29},
    {0,  CS2_SW8_29,  CS1_SW8_29,  CS3_SW8_29},
    {0,  CS2_SW9_29,  CS1_SW9_29,  CS3_SW9_29},

    {0,  CS5_SW1_29,  CS4_SW1_29,  CS6_SW1_29},
    {0,  CS5_SW2_29,  CS4_SW2_29,  CS6_SW2_29},
    {0,  CS5_SW3_29,  CS4_SW3_29,  CS6_SW3_29},
    {0,  CS5_SW4_29,  CS4_SW4_29,  CS6_SW4_29},
    {0,  CS5_SW5_29,  CS4_SW5_29,  CS6_SW5_29},
    {0,  CS5_SW6_29,  CS4_SW6_29,  CS6_SW6_29},
    {0,  CS5_SW7_29,  CS4_SW7_29,  CS6_SW7_29},
    {0,  CS5_SW8_29,  CS4_SW8_29,  CS6_SW8_29},
    {0,  CS5_SW9_29,  CS4_SW9_29,  CS6_SW9_29},

    {0, CS8_SW1_29, CS7_SW1_29, CS9_SW1_29},
    {0, CS8_SW2_29, CS7_SW2_29, CS9_SW2_29},
    {0, CS8_SW3_29, CS7_SW3_29, CS9_SW3_29},
    {0, CS8_SW4_29, CS7_SW4_29, CS9_SW4_29},
    {0, CS8_SW5_29, CS7_SW5_29, CS9_SW5_29},
    {0, CS8_SW6_29, CS7_SW6_29, CS9_SW6_29},
    {0, CS8_SW7_29, CS7_SW7_29, CS9_SW7_29},
    {0, CS8_SW8_29, CS7_SW8_29, CS9_SW8_29},
    {0, CS8_SW9_29, CS7_SW9_29, CS9_SW9_29},

    {0, CS11_SW1_29, CS10_SW1_29, CS12_SW1_29},
    {0, CS11_SW2_29, CS10_SW2_29, CS12_SW2_29},
    {0, CS11_SW3_29, CS10_SW3_29, CS12_SW3_29},
    {0, CS11_SW4_29, CS10_SW4_29, CS12_SW4_29},
    {0, CS11_SW5_29, CS10_SW5_29, CS12_SW5_29},
    {0, CS11_SW6_29, CS10_SW6_29, CS12_SW6_29},
    {0, CS11_SW7_29, CS10_SW7_29, CS12_SW7_29},
    {0, CS11_SW8_29, CS10_SW8_29, CS12_SW8_29},
    {0, CS11_SW9_29, CS10_SW9_29, CS12_SW9_29},

    {0, CS14_SW1_29, CS13_SW1_29, CS15_SW1_29},
    {0, CS14_SW2_29, CS13_SW2_29, CS15_SW2_29},
    {0, CS14_SW3_29, CS13_SW3_29, CS15_SW3_29},
    {0, CS14_SW4_29, CS13_SW4_29, CS15_SW4_29},
    {0, CS14_SW5_29, CS13_SW5_29, CS15_SW5_29},
    {0, CS14_SW6_29, CS13_SW6_29, CS15_SW6_29},
    {0, CS14_SW7_29, CS13_SW7_29, CS15_SW7_29},
    {0, CS14_SW8_29, CS13_SW8_29, CS15_SW8_29},
    {0, CS14_SW9_29, CS13_SW9_29, CS15_SW9_29},

    // right
    {1,  CS2_SW1_29,  CS1_SW1_29,  CS3_SW1_29},
    {1,  CS2_SW2_29,  CS1_SW2_29,  CS3_SW2_29},
    {1,  CS2_SW3_29,  CS1_SW3_29,  CS3_SW3_29},
    {1,  CS2_SW4_29,  CS1_SW4_29,  CS3_SW4_29},
    {1,  CS2_SW5_29,  CS1_SW5_29,  CS3_SW5_29},
    {1,  CS2_SW6_29,  CS1_SW6_29,  CS3_SW6_29},
    {1,  CS2_SW7_29,  CS1_SW7_29,  CS3_SW7_29},
    {1,  CS2_SW8_29,  CS1_SW8_29,  CS3_SW8_29},
    {1,  CS2_SW9_29,  CS1_SW9_29,  CS3_SW9_29},

    {1,  CS5_SW1_29,  CS4_SW1_29,  CS6_SW1_29},
    {1,  CS5_SW2_29,  CS4_SW2_29,  CS6_SW2_29},
    {1,  CS5_SW3_29,  CS4_SW3_29,  CS6_SW3_29},
    {1,  CS5_SW4_29,  CS4_SW4_29,  CS6_SW4_29},
    {1,  CS5_SW5_29,  CS4_SW5_29,  CS6_SW5_29},
    {1,  CS5_SW6_29,  CS4_SW6_29,  CS6_SW6_29},
    {1,  CS5_SW7_29,  CS4_SW7_29,  CS6_SW7_29},
    {1,  CS5_SW8_29,  CS4_SW8_29,  CS6_SW8_29},
    {1,  CS5_SW9_29,  CS4_SW9_29,  CS6_SW9_29},

    {1, CS8_SW1_29, CS7_SW1_29, CS9_SW1_29},
    {1, CS8_SW2_29, CS7_SW2_29, CS9_SW2_29},
    {1, CS8_SW3_29, CS7_SW3_29, CS9_SW3_29},
    {1, CS8_SW4_29, CS7_SW4_29, CS9_SW4_29},
    {1, CS8_SW5_29, CS7_SW5_29, CS9_SW5_29},
    {1, CS8_SW6_29, CS7_SW6_29, CS9_SW6_29},
    {1, CS8_SW7_29, CS7_SW7_29, CS9_SW7_29},
    {1, CS8_SW8_29, CS7_SW8_29, CS9_SW8_29},
    {1, CS8_SW9_29, CS7_SW9_29, CS9_SW9_29},

    {1, CS11_SW1_29, CS10_SW1_29, CS12_SW1_29},
    {1, CS11_SW2_29, CS10_SW2_29, CS12_SW2_29},
    {1, CS11_SW3_29, CS10_SW3_29, CS12_SW3_29},
    {1, CS11_SW4_29, CS10_SW4_29, CS12_SW4_29},
    {1, CS11_SW5_29, CS10_SW5_29, CS12_SW5_29},
    {1, CS11_SW6_29, CS10_SW6_29, CS12_SW6_29},
    {1, CS11_SW7_29, CS10_SW7_29, CS12_SW7_29},
    {1, CS11_SW8_29, CS10_SW8_29, CS12_SW8_29},
    {1, CS11_SW9_29, CS10_SW9_29, CS12_SW9_29},

    {1, CS14_SW1_29, CS13_SW1_29, CS15_SW1_29},
    {1, CS14_SW2_29, CS13_SW2_29, CS15_SW2_29},
    {1, CS14_SW3_29, CS13_SW3_29, CS15_SW3_29},
    {1, CS14_SW4_29, CS13_SW4_29, CS15_SW4_29},
    {1, CS14_SW5_29, CS13_SW5_29, CS15_SW5_29},
    {1, CS14_SW6_29, CS13_SW6_29, CS15_SW6_29},
    {1, CS14_SW7_29, CS13_SW7_29, CS15_SW7_29},
    {1, CS14_SW8_29, CS13_SW8_29, CS15_SW8_29},
    {1, CS14_SW9_29, CS13_SW9_29, CS15_SW9_29},

    // front
    {0, OUT_25, OUT_26, OUT_27},
    {0, OUT_22, OUT_23, OUT_24},
    {0, OUT_19, OUT_20, OUT_21},
    {0, OUT_16, OUT_17, OUT_18},
    {0, OUT_13, OUT_14, OUT_15},
    {0, OUT_10, OUT_11, OUT_12},
};

void matrix_init_kb(void)
{
    setPinOutput(LED_CAPS_LOCK_PIN);
    writePinLow(LED_CAPS_LOCK_PIN);
    setPinOutput(LED_NUM_LOCK_PIN);
    writePinLow(LED_NUM_LOCK_PIN);

    i2c_init();
    IS31FL3729_init(IS31FL3729_ADDR_1, 0);
    IS31FL3729_init(IS31FL3729_ADDR_2, 1);
    IS31FL3236_init(IS31FL3236_ADDR, 0);

    update_ticks();
    matrix_init_user();
}

#define ALERM_LED_R     0xFF
#define ALERM_LED_G     0xA5
#define ALERM_LED_B     0x00
//golden 0xFF, 0xD9, 0x00

void housekeeping_task_kb(void)
{
    if (rgb_state.state == SELF_TESTING) {
        self_testing();
    } else if (rgb_state.state == CAPS_ALERT) {
        if (rgb_state.alert) {
            IS31FL3729_set_color_all(ALERM_LED_R, ALERM_LED_G, ALERM_LED_B);
            IS31FL3236_set_color_all(ALERM_LED_R, ALERM_LED_G, ALERM_LED_B);
        } else {
            IS31FL3729_set_color_all(0, 0, 0);
            IS31FL3236_set_color_all(0, 0, 0);
        }

        if (timer_elapsed(rgb_state.ticks) > ALERT_INTERVAL) {
            rgb_state.alert = !rgb_state.alert;
            update_ticks();
        }
    }

    IS31FL3729_update_pwm_buffers(IS31FL3729_ADDR_1, 0);
    IS31FL3729_update_pwm_buffers(IS31FL3729_ADDR_2, 1);

    IS31FL3236_update_pwm_buffers(IS31FL3236_ADDR, 0);

    housekeeping_task_user();
}

void rgblight_call_driver(rgb_led_t *start_led, uint8_t num_leds)
{
    for (uint8_t i = IS31FL3729_LED_BEGIN; i < IS31FL3729_LED_BEGIN+IS31FL3729_LED_TOTAL; i++) {
        IS31FL3729_set_color(i, start_led[i].r, start_led[i].g, start_led[i].b);
    }

    for (uint8_t i = IS31FL3236_LED_BEGIN; i < IS31FL3236_LED_BEGIN+IS31FL3236_LED_TOTAL; i++) {
        IS31FL3236_set_color(i, start_led[i].r, start_led[i].g, start_led[i].b);
    } 
}

bool led_update_kb(led_t led_state)
{
    bool res = led_update_user(led_state);

    if (res) {
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
        writePin(LED_NUM_LOCK_PIN, led_state.num_lock);

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