/**
 * @file rgb_ring.c
 * @author astro
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

#include "rgb_ring.h"

#include <string.h>
#include "quantum.h"
#include "rgblight.h"
#include "drivers/led/issi/is31fl3731.h"
#include "i2c_master.h"


#ifndef RGBLIGHT_ENABLE
#error "MUST enable rgblight"
#endif
// rgb ring leds setting

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, C1_1,   C3_2,   C4_2},
    {0, C1_2,   C2_2,   C4_3},
    {0, C1_3,   C2_3,   C3_3},
    {0, C1_4,   C2_4,   C3_4},
    {0, C1_5,   C2_5,   C3_5},
    {0, C1_6,   C2_6,   C3_6},
    {0, C1_7,   C2_7,   C3_7},
    {0, C1_8,   C2_8,   C3_8},

    {0, C9_1,   C8_1,   C7_1},
    {0, C9_2,   C8_2,   C7_2},
    {0, C9_3,   C8_3,   C7_3},
    {0, C9_4,   C8_4,   C7_4},
    {0, C9_5,   C8_5,   C7_5},
    {0, C9_6,   C8_6,   C7_6},
    {0, C9_7,   C8_7,   C6_6},
    {0, C9_8,   C7_7,   C6_7},

    {0, C1_9,   C3_10,  C4_10},
    {0, C1_10,  C2_10,  C4_11},
    {0, C1_11,  C2_11,  C3_11},
    {0, C1_12,  C2_12,  C3_12},
};

#define RING_OUTER_BEGIN    0
#define RING_OUTER_END      15
#define RING_OUTER_SIZE     (RING_OUTER_END + 1 - RING_OUTER_BEGIN)

#define RING_INNER_BEGIN    16
#define RING_INNER_END      19
#define RING_INNER_SIZE     (RING_INNER_END + 1 - RING_INNER_BEGIN)

#define SPEED_MAX           100
#define SPEED_STEP          10

typedef enum {
    RING_STATE_INIT,
    RING_STATE_QMK,
    RING_STATE_CUSTOM,
} RING_STATE;

typedef enum {
    RING_EFFECT_1,
    RING_EFFECT_2,
    RING_EFFECT_3,
    RING_EFFECT_4,
    RING_EFFECT_5,
    RING_EFFECT_6,
    RING_EFFECT_MAX
} RING_EFFECT;

typedef struct {
    uint8_t state;
    uint8_t effect;
    uint8_t speed;
    uint8_t outer_index;
    uint8_t inner_index;
    uint8_t effect_count;
    uint8_t led_begin;
    uint8_t led_end;
    bool    led_forward;
    bool    led_clear;
} rgb_ring_t;

static rgb_ring_t rgb_ring = {
    .state          = RING_STATE_INIT,
    .effect         = RING_EFFECT_1,
    .speed          = 10,
    .outer_index    = 0,
    .inner_index    = 0,
    .effect_count   = 0,
    .led_begin      = RING_OUTER_BEGIN,
    .led_end        = RING_OUTER_END,
    .led_forward    = true,
    .led_clear      = false,
};

static void rgb_ring_reset(void)
{
    rgb_ring.effect_count   = 0;
    rgb_ring.led_begin      = RING_OUTER_BEGIN;
    rgb_ring.led_end        = RING_OUTER_END;
    rgb_ring.led_forward    = true;
    rgb_ring.led_clear      = false;
}

extern animation_status_t animation_status;
extern rgblight_config_t rgblight_config;

#define EFFECT_TEST_INTERVAL    50
#define EFFECT_TEST_COUNT       5
#define EFFECT_TEST_HUE_STEP    85
#define EFFECT_TEST_VAL_STEP    17
static void testing_mode(void)
{
    if (timer_elapsed(animation_status.last_timer) > EFFECT_TEST_INTERVAL) {
        HSV h = {rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
        RGB c = hsv_to_rgb(h);
        //is31fl3731_set_color_all(c.r, c.g, c.b);
        is31fl3731_set_color_all(0, 0, 0);
        is31fl3731_set_color(rgb_ring.outer_index+RING_OUTER_BEGIN, c.r, c.g, c.b);
        h.v = EFFECT_TEST_VAL_STEP*rgb_ring.outer_index;
        c = hsv_to_rgb(h);
        for (uint8_t i = RING_INNER_BEGIN; i <= RING_INNER_END; i++) {
            is31fl3731_set_color(i, c.r, c.g, c.b);
        }
        rgb_ring.outer_index = (rgb_ring.outer_index + 1) % RING_OUTER_SIZE;
        //rgb_ring.inner_index = (rgb_ring.inner_index + 1) % RING_INNER_SIZE;

        if (rgb_ring.outer_index == RING_OUTER_BEGIN) {
            rgblight_config.hue += EFFECT_TEST_HUE_STEP;
            rgb_ring.effect_count++;
        }
        animation_status.last_timer = timer_read();
    }
    if (rgb_ring.effect_count > EFFECT_TEST_COUNT) {
        rgb_ring_reset();
        rgb_ring.state = RING_STATE_QMK;
        rgblight_set();
    }
}

static bool need_update(uint32_t max_interval)
{
    uint32_t interval = timer_elapsed(animation_status.last_timer);
    return (interval*rgb_ring.speed) > max_interval;
}

static void update_effect(uint32_t max_count)
{
    if (rgb_ring.effect_count > max_count) {
        rgb_ring_reset();
        rgb_ring.effect = (rgb_ring.effect + 1) % RING_EFFECT_MAX;
    }
}

#define EFFECT_1_INTERVAL  1000
#define EFFECT_1_COUNT     64
#define EFFECT_1_HUE_STEP  15

static void ring_effect_no_1(void)
{
    if (need_update(EFFECT_1_INTERVAL)) {
        HSV h = {rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
        for (uint8_t i = RING_OUTER_BEGIN; i <= RING_OUTER_END; i++) {
            RGB c = hsv_to_rgb(h);
            is31fl3731_set_color(i, c.r, c.g, c.b);
        }
        rgblight_config.hue += EFFECT_1_HUE_STEP;
        rgb_ring.effect_count++;
        animation_status.last_timer = timer_read();
    }

    update_effect(EFFECT_1_COUNT);
}

#define EFFECT_2_INTERVAL  1000
#define EFFECT_2_COUNT     64
#define EFFECT_2_HUE_STEP  15

static void ring_effect_no_2(void)
{
    if (need_update(EFFECT_2_INTERVAL)) {
        is31fl3731_set_color_all(0, 0, 0);
        HSV h = {rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
        RGB c = hsv_to_rgb(h);

        is31fl3731_set_color(rgb_ring.led_begin, c.r, c.g, c.b);
        is31fl3731_set_color(rgb_ring.led_end, c.r, c.g, c.b);

        rgb_ring.led_begin = (rgb_ring.led_begin + 1) % RING_OUTER_SIZE;
        rgb_ring.led_end = (rgb_ring.led_end + RING_OUTER_SIZE - 1) % RING_OUTER_SIZE;

        rgblight_config.hue += EFFECT_2_HUE_STEP;
        rgb_ring.effect_count++;
        animation_status.last_timer = timer_read();
    }

    update_effect(EFFECT_2_COUNT);
}

#define EFFECT_3_INTERVAL  1000
#define EFFECT_3_COUNT     64
#define EFFECT_3_HUE_STEP  15

static void ring_effect_no_3(void)
{
    if (rgb_ring.effect_count == 0) {
        is31fl3731_set_color_all(0, 0, 0);
    }

    if (need_update(EFFECT_3_INTERVAL)) {
        HSV h = {rgblight_config.hue, rgblight_config.sat, rgblight_config.val};

        if (rgb_ring.led_clear) {
            is31fl3731_set_color(rgb_ring.led_begin, 0, 0, 0);
            is31fl3731_set_color(rgb_ring.led_end, 0, 0, 0);
        } else {
            RGB c = hsv_to_rgb(h);
            is31fl3731_set_color(rgb_ring.led_begin, c.r, c.g, c.b);
            is31fl3731_set_color(rgb_ring.led_end, c.r, c.g, c.b);
        }

        rgb_ring.led_begin = (rgb_ring.led_begin + 1) % RING_OUTER_SIZE;
        if (rgb_ring.led_begin == rgb_ring.led_end) {
            if (rgb_ring.led_forward) {
                rgb_ring.led_begin = RING_OUTER_BEGIN;
                rgb_ring.led_end = RING_OUTER_END+1;
            } else {
                rgb_ring.led_begin = RING_OUTER_BEGIN + RING_OUTER_SIZE/2;
                rgb_ring.led_end = RING_OUTER_END+1 - RING_OUTER_SIZE/2;
            }

            if (!rgb_ring.led_clear) {
                rgb_ring.led_forward = !rgb_ring.led_forward;
            }

            rgb_ring.led_clear = !rgb_ring.led_clear;
        }

        rgb_ring.led_end = (rgb_ring.led_end + RING_OUTER_SIZE - 1) % RING_OUTER_SIZE;

        rgblight_config.hue += EFFECT_3_HUE_STEP;
        rgb_ring.effect_count++;
        animation_status.last_timer = timer_read();
    }

    update_effect(EFFECT_3_COUNT);
}

#define EFFECT_4_INTERVAL  1000
#define EFFECT_4_COUNT     64
#define EFFECT_4_STEP      3
static void ring_effect_no_4(void)
{
    if (need_update(EFFECT_4_INTERVAL)) {
        is31fl3731_set_color_all(0, 0, 0);
        HSV h = {rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
        RGB c = hsv_to_rgb(h);

        is31fl3731_set_color(rgb_ring.led_begin, c.r, c.g, c.b);
        is31fl3731_set_color(rgb_ring.led_end, c.r, c.g, c.b);

        rgb_ring.led_begin = (rgb_ring.led_begin + EFFECT_4_STEP) % RING_OUTER_SIZE;
        rgb_ring.led_end = (rgb_ring.led_end + RING_OUTER_SIZE - EFFECT_4_STEP) % RING_OUTER_SIZE;

        rgblight_config.hue += EFFECT_1_HUE_STEP;
        rgb_ring.effect_count++;
        animation_status.last_timer = timer_read();
    }

    update_effect(EFFECT_4_COUNT);
}

#define EFFECT_5_INTERVAL  1000
#define EFFECT_5_COUNT     64
#define EFFECT_5_HUE_STEP  16
static void ring_effect_no_5(void)
{
    if (need_update(EFFECT_5_INTERVAL)) {
        is31fl3731_set_color_all(0, 0, 0);
        for (uint8_t i = RING_INNER_BEGIN; i <= RING_INNER_END; i++) {
            HSV h = {rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
            RGB c = hsv_to_rgb(h);
            is31fl3731_set_color(i, c.r, c.g, c.b);
        }
        for (uint8_t i = RING_OUTER_BEGIN; i <= RING_OUTER_END; i++) {
            HSV h = {rgblight_config.hue+EFFECT_5_HUE_STEP, rgblight_config.sat, rgblight_config.val};
            RGB c = hsv_to_rgb(h);
            is31fl3731_set_color(i, c.r, c.g, c.b);
        }
        rgblight_config.hue += EFFECT_5_HUE_STEP;
        rgb_ring.effect_count++;
        animation_status.last_timer = timer_read();
    }

    update_effect(EFFECT_5_COUNT);
}

#define EFFECT_6_INTERVAL  1000
#define EFFECT_6_COUNT     64
#define EFFECT_I_HUE_STEP  10
#define EFFECT_O_HUE_STEP  10
static void ring_effect_no_6(void)
{
    if (need_update(EFFECT_6_INTERVAL)) {
        is31fl3731_set_color_all(0, 0, 0);
        for (uint8_t i = RING_INNER_BEGIN; i <= RING_INNER_END; i++) {
            HSV h = {rgblight_config.hue+i*EFFECT_I_HUE_STEP, rgblight_config.sat, rgblight_config.val};
            RGB c = hsv_to_rgb(h);
            is31fl3731_set_color(i, c.r, c.g, c.b);
        }
        for (uint8_t i = RING_OUTER_BEGIN; i <= RING_OUTER_END; i++) {
            HSV h = {rgblight_config.hue+i*EFFECT_O_HUE_STEP, rgblight_config.sat, rgblight_config.val};
            RGB c = hsv_to_rgb(h);
            is31fl3731_set_color(i, c.r, c.g, c.b);
        }
        rgblight_config.hue += EFFECT_I_HUE_STEP;
        rgb_ring.effect_count++;
        animation_status.last_timer = timer_read();
    }

    update_effect(EFFECT_6_COUNT);
}

typedef void(*effect_fun)(void);
static effect_fun effect_funcs[RING_EFFECT_MAX] = {
    ring_effect_no_1,
    ring_effect_no_2,
    ring_effect_no_3,
    ring_effect_no_4,
    ring_effect_no_5,
    ring_effect_no_6,
};

static void custom_effects(void)
{
    effect_funcs[rgb_ring.effect]();
}

void rgblight_call_driver(rgb_led_t *start_led, uint8_t num_leds)
{
    if (rgb_ring.state != RING_STATE_QMK) {
        return;
    }

    for (uint8_t i = 0; i < num_leds; i++) {
        is31fl3731_set_color(i, start_led[i].r, start_led[i].g, start_led[i].b);
    }
}


void rgb_ring_init(void)
{
    i2c_init();
    is31fl3731_init(DRIVER_ADDR_1);
    for (int index = 0; index < RGB_MATRIX_LED_COUNT; index++) {
        bool enabled = true;
        is31fl3731_set_led_control_register(index, enabled, enabled, enabled);
    }
    is31fl3731_update_led_control_registers(DRIVER_ADDR_1, 0);
}

void rgb_ring_task(void)
{
    switch (rgb_ring.state) {
        case RING_STATE_INIT: // testing mode
            testing_mode();
            break;
        case RING_STATE_QMK: // qmk effects
            //rgblight_task();
            break;
        case RING_STATE_CUSTOM: // custom effects
            custom_effects();
            break;
        default:
            break;
    };

    is31fl3731_update_pwm_buffers(DRIVER_ADDR_1, 0);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed) {
        switch(keycode) {
            case RGB_MODE_FORWARD:
                if (rgb_ring.state == RING_STATE_INIT) {
                    // in testing mode, do nothing
                    return false;
                } else if (rgb_ring.state == RING_STATE_CUSTOM) {
                    // switch to qmk mode
                    rgblight_config.mode = 1;
                    rgb_ring.state = RING_STATE_QMK;
                    rgblight_mode(rgblight_config.mode);
                    return false;
                } else {
                    // in qmk mode, switch to custom mode?
                    if (rgblight_config.mode >= RGBLIGHT_MODES) {
                        rgb_ring.state = RING_STATE_CUSTOM;
                        return false;
                    }
                }
                break;
            case RGB_MODE_REVERSE:
                if (rgb_ring.state == RING_STATE_INIT) {
                    // in testing mode, do nothing
                    return false;
                } else if (rgb_ring.state == RING_STATE_CUSTOM) {
                    // switch to qmk mode
                    rgblight_config.mode = RGBLIGHT_MODES;
                    rgb_ring.state = RING_STATE_QMK;
                    rgblight_mode(rgblight_config.mode);
                    return false;
                } else {
                    // in qmk mode, switch to custom mode?
                    if (rgblight_config.mode <= 1) {
                        rgb_ring.state = RING_STATE_CUSTOM;
                        return false;
                    }
                }
                break;
            case KC_F24:
                if (rgb_ring.state == RING_STATE_QMK) {
                    rgb_ring.state = RING_STATE_CUSTOM;
                    rgb_ring_reset();
                    return false;
                } else if (rgb_ring.state == RING_STATE_CUSTOM) {
                    rgb_ring.state = RING_STATE_QMK;
                    return false;
                }
                break;
            default:
                break;
        }
    }
    return process_record_user(keycode, record);
}
