/* Copyright 2022 ANWC Limited d.b.a. ChonkerKeys
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
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "wait.h"
#include "progmem.h"
#include "timer.h"
#include "rgb_strands.h"
#include "color.h"
#include "debug.h"
#include <lib/lib8tion/lib8tion.h>


static bool is_rgb_strands_initialized = false;

typedef struct _rgb_strand_anim_status_t {
    rgb_strands_anim_t       effect;
    rgb_strand_anim_config_t config;
    uint16_t                 nexttime;
    struct {
        uint8_t state; // current state as defined by animation
        HSV color;
        uint8_t led_i;
        uint8_t count;
    } current;
} rgb_strand_anim_status_t;

static rgb_strand_anim_config_t default_configs[] = {
    {}, // RGB_STRAND_EFFECT_NONE
    // RGB_STRAND_EFFECT_STATIC,
    {
        .color = {HSV_OFF}
    },
    // RGB_STRAND_EFFECT_DRAINSWIRL,
    {
        .color = {HSV_RED},
        .time_step = 60,
        .val_step = 4
    },
    // RGB_STRAND_EFFECT_MOMENTARY,
    {
        .color = {HSV_WHITE},
        .time_step = 50,
        .val_step = 50
    },
    // RGB_STRAND_EFFECT_LIKE,
    {
        .color = {HSV_YELLOW},
        .time_step = 120,
        .num_times = 3
    },
    // RGB_STRAND_EFFECT_BLINKY,
    {
        .color = {HSV_YELLOW},
        .period = 800,
        .num_times = 10
    },
    // RGB_STRAND_EFFECT_RAINBOW,
    {
        .color = {HSV_RED},
        .time_step = 10,
        .num_times = 10
    },
    // RGB_STRAND_EFFECT_BREATHING,
    {
        .color = {HSV_PINK},
        .period = 5000,
        .num_times = 10
    },
    {} // RGB_STRAND_EFFECT_INVALID
};

const rgb_strand_anim_config_t * get_default_rgb_strand_anim_config(rgb_strands_anim_t anim) {
    if (anim <= RGB_STRAND_EFFECT_NONE || anim >= RGB_STRAND_EFFECT_INVALID) {
        return NULL;
    }
    return &default_configs[anim];
}

uint8_t rgb_strand_get_num_leds(uint8_t strand);
void rgb_strand_set_same_color(uint8_t strand, uint8_t h, uint8_t s, uint8_t v);

/** Low(er) level color setting.
 * @param strand Strand ID, 0 to 11
 * @param leds pointer to LEDs
 * @param num_leds number of LEDs in leds array */
void rgb_strand_set(uint8_t strand, LED_TYPE *leds, uint8_t num_leds);

typedef void (*strand_effect_func_t)(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
typedef void (*strand_set_state_func_t)(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_effect_dummy(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_set_state_dummy(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_effect_static(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_set_state_static(uint8_t strand,rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_effect_drainswirl(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_set_state_drainswirl(uint8_t strand,rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_effect_momentary(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_set_state_momentary(uint8_t strand,rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_effect_like(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_set_state_like(uint8_t strand,rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_effect_blinky(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_set_state_blinky(uint8_t strand,rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_effect_rainbow(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_set_state_rainbow(uint8_t strand,rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_effect_breathing(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now);
void rgb_strand_set_state_breathing(uint8_t strand,rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now);

void sethsv_rs(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led) {
    val = val > RGB_STRAND_LIMIT_VAL ? RGB_STRAND_LIMIT_VAL : val;
    HSV hsv = {hue, sat, val};
    RGB rgb = hsv_to_rgb(hsv);
    led->r = rgb.r;
    led->g = rgb.g;
    led->b = rgb.b;
}

bool is_valid_strand(uint8_t strand) {
    if (strand < 0 || strand >= RGB_STRANDS_NUM) return false;

    switch(strand) {
#ifdef RGB_STRAND_0_DI_PIN
        case 0:
            return true;
#endif
#ifdef RGB_STRAND_1_DI_PIN
        case 1:
            return true;
#endif
#ifdef RGB_STRAND_2_DI_PIN
        case 2:
            return true;
#endif
#ifdef RGB_STRAND_3_DI_PIN
        case 3:
            return true;
#endif
#ifdef RGB_STRAND_4_DI_PIN
        case 4:
            return true;
#endif
#ifdef RGB_STRAND_5_DI_PIN
        case 5:
            return true;
#endif
#ifdef RGB_STRAND_6_DI_PIN
        case 6:
            return true;
#endif
#ifdef RGB_STRAND_7_DI_PIN
        case 7:
            return true;
#endif
#ifdef RGB_STRAND_8_DI_PIN
        case 8:
            return true;
#endif
#ifdef RGB_STRAND_9_DI_PIN
        case 9:
            return true;
#endif
#ifdef RGB_STRAND_A_DI_PIN
        case 10:
            return true;
#endif
#ifdef RGB_STRAND_B_DI_PIN
        case 11:
            return true;
#endif
        default:
            break;
    }
    return false;
}

static rgb_strand_anim_status_t rgb_strand_anim_status[RGB_STRANDS_NUM] = {};

void rgb_strands_init(void) {
    if (is_rgb_strands_initialized) {
        return;
    }

    for (uint8_t i = 0; i < RGB_STRANDS_NUM; i++) {
        rgb_strand_anim_status_t * status = &rgb_strand_anim_status[i];
        status->effect = RGB_STRAND_EFFECT_STATIC;
        status->config.color.h = 0;
        status->config.color.s = 0;
        status->config.color.v = 0;
    }

    timer_init();

    is_rgb_strands_initialized = true;
}

void rgb_strands_task(void) {
    strand_effect_func_t effect_func = rgb_strand_effect_dummy;
    for (uint8_t strand = 0; strand < RGB_STRANDS_NUM; strand++) {
        rgb_strand_anim_status_t * status = &rgb_strand_anim_status[strand];
        switch (status->current.state) {
            case RGB_STRAND_ANIM_STATE_OFF:
                rgb_strand_set_same_color(strand, HSV_OFF);
                break;
            case RGB_STRAND_ANIM_STATE_STEADY:
                rgb_strand_set_same_color(strand, status->current.color.h, status->current.color.s,
                        status->current.color.v);
                break;
            default:
                switch (status->effect) {
                    case RGB_STRAND_EFFECT_STATIC:
                        effect_func = rgb_strand_effect_static;
                        break;
                    case RGB_STRAND_EFFECT_DRAINSWIRL:
                        effect_func = rgb_strand_effect_drainswirl;
                        break;
                    case RGB_STRAND_EFFECT_MOMENTARY:
                        effect_func = rgb_strand_effect_momentary;
                        break;
                    case RGB_STRAND_EFFECT_LIKE:
                        effect_func = rgb_strand_effect_like;
                        break;
                    case RGB_STRAND_EFFECT_BLINKY:
                        effect_func = rgb_strand_effect_blinky;
                        break;
                    case RGB_STRAND_EFFECT_RAINBOW:
                        effect_func = rgb_strand_effect_rainbow;
                        break;
                    case RGB_STRAND_EFFECT_BREATHING:
                        effect_func = rgb_strand_effect_breathing;
                        break;
                    default:
                        break;
                }
                effect_func(strand, status, timer_read());
                break;
        }   // switch state
    }  // for strands
}

void rgb_strands_suspend(void) {
    // TODO
}

void rgb_strands_wakeup(void) {
    // TODO
}

void rgb_strand_set_color(uint8_t strand, uint8_t h, uint8_t s, uint8_t v) {
    if (!is_valid_strand(strand)) return;
    rgb_strand_anim_status_t * status = &rgb_strand_anim_status[strand];
    status->effect = RGB_STRAND_EFFECT_STATIC;
    status->config.color.h = h;
    status->config.color.s = s;
    status->config.color.v = v;
}

void rgb_strand_animation_start(
        uint8_t strand,
        rgb_strands_anim_t effect,
        const rgb_strand_anim_config_t *config,
        rgb_strand_anim_state_t initial_state) {
    if (!is_valid_strand(strand)) return;
    if (effect <= RGB_STRAND_EFFECT_NONE || effect >= RGB_STRAND_EFFECT_INVALID) return;

    rgb_strand_anim_status_t * status = &rgb_strand_anim_status[strand];
    status->effect = effect;
    memcpy(&status->config, config, sizeof(rgb_strand_anim_config_t));

    // dummy defaults, overwritten in set_state
    status->nexttime = 0;
    status->current.state = RGB_STRAND_ANIM_STATE_OFF;
    status->current.color.h = config->color.h;
    status->current.color.s = config->color.s;
    status->current.color.v = config->color.v;

    rgb_strand_animation_set_state(strand, initial_state);
}

void rgb_strand_animation_set_state(uint8_t strand, rgb_strand_anim_state_t state) {
    if (!is_valid_strand(strand)) return;
    rgb_strand_anim_status_t * status = &rgb_strand_anim_status[strand];

    if (RGB_STRAND_ANIM_STATE_START == state) {
    }

    strand_set_state_func_t set_state_func = rgb_strand_set_state_dummy;
    switch (status->effect) {
        case RGB_STRAND_EFFECT_DRAINSWIRL:
            set_state_func = rgb_strand_set_state_drainswirl;
            break;
        case RGB_STRAND_EFFECT_MOMENTARY:
            set_state_func = rgb_strand_set_state_momentary;
            break;
        case RGB_STRAND_EFFECT_LIKE:
            set_state_func = rgb_strand_set_state_like;
            break;
        case RGB_STRAND_EFFECT_BLINKY:
            set_state_func = rgb_strand_set_state_blinky;
            break;
        case RGB_STRAND_EFFECT_RAINBOW:
            set_state_func = rgb_strand_set_state_rainbow;
            break;
        case RGB_STRAND_EFFECT_BREATHING:
            set_state_func = rgb_strand_set_state_breathing;
            break;
        default:
            break;
    }
    set_state_func(strand, state, status, timer_read());
    status->current.state = state;
}

void rgb_strand_effect_dummy(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now) { }
void rgb_strand_set_state_dummy(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now) { }

void rgb_strand_effect_static(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now) {
    rgb_strand_set_same_color(strand, status->config.color.h, status->config.color.s, status->config.color.v);
}

void rgb_strand_effect_drainswirl(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now) {
    uint8_t num_leds = rgb_strand_get_num_leds(strand);
    LED_TYPE leds[RGB_STRAND_MAX_NUM_LEDS];
    uint8_t min_v = status->config.color.v/4;

    switch(status->current.state) {
        case RGB_STRAND_ANIM_STATE_DRAINSWIRL_SWIRL:
            if (timer_expired(now, status->nexttime)) {
                status->current.led_i = (status->current.led_i + 1) % num_leds;
                if (0 == status->current.led_i) {
                    status->current.led_i = 1;
                }
                status->current.color.v -= status->config.val_step;
                status->nexttime = now + status->config.time_step;
            }
            sethsv_rs(HSV_OFF, (LED_TYPE *)&leds[0]);
            sethsv_rs(status->current.color.h, status->current.color.s, status->current.color.v,
                    &leds[status->current.led_i]);
            for (uint8_t i = 1; i < num_leds; i++) {
                uint8_t li = status->current.led_i + i;
                uint8_t v = status->current.color.v/2/i;
                if (li >= num_leds) {
                    li %= num_leds;
                    li++;
                }
                v = v > min_v ? v : min_v;
                sethsv_rs(status->current.color.h, status->current.color.s, v,
                        (LED_TYPE *)&leds[li]);
            }
            rgb_strand_set(strand, leds, num_leds);
            if (status->current.color.v < min_v) {
                rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_DRAINSWIRL_FINAL);
            }
            break;
        case RGB_STRAND_ANIM_STATE_DRAINSWIRL_FINAL:
            sethsv_rs(status->config.color.h, status->config.color.s, status->config.color.v,
                    (LED_TYPE *)&leds[0]);
            for (uint8_t i = 1; i < num_leds; i++) {
                sethsv_rs(status->config.color.h, status->config.color.s, min_v, (LED_TYPE *)&leds[i]);
            }
            rgb_strand_set(strand, leds, num_leds);
            if (timer_expired(now, status->nexttime)) {
                rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_OFF);
            }
            break;
        default:
            break;
     }
}

void rgb_strand_set_state_drainswirl(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now) {
    switch(state) {
        case RGB_STRAND_ANIM_STATE_DRAINSWIRL_SWIRL:
            status->nexttime = now + status->config.time_step;
            status->current.led_i = 1;
            break;
        case RGB_STRAND_ANIM_STATE_DRAINSWIRL_FINAL:
            status->nexttime = now + 1000;
            break;
        default:
            break;
    }
}

void rgb_strand_effect_momentary(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now) {
    if (RGB_STRAND_ANIM_STATE_MOMENTARY_DECAY != status->current.state) {
        return;
    }

    rgb_strand_set_same_color(strand, status->current.color.h, status->current.color.s, status->current.color.v);

    if (timer_expired(now, status->nexttime)) {
        status->current.color.v -= status->config.hue_step;
        if (status->current.color.v <= status->config.hue_step) {
            rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_OFF);
        }
        else {
            status->nexttime = now + status->config.time_step;
        }
    }
}

void rgb_strand_set_state_momentary(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now) {
    switch(state) {
        case RGB_STRAND_ANIM_STATE_MOMENTARY_DECAY:
            status->nexttime = now + status->config.time_step;
            break;
        default:
            break;
    }
}

#ifndef RGB_STRAND_ANIM_LIKE_NUM_BLINKS
#    define RGB_STRAND_ANIM_LIKE_NUM_BLINKS 2
#endif

#ifndef RGB_STRAND_ANIM_LIKE_BLINKS_DURATION
#    define RGB_STRAND_ANIM_LIKE_BLINKS_DURATION 1000
#endif

#define _ANIM_LIKE_BLINK_HALF_PERIOD (RGB_STRAND_ANIM_LIKE_BLINKS_DURATION / RGB_STRAND_ANIM_LIKE_NUM_BLINKS / 2)

void rgb_strand_effect_like(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now) {
    uint8_t num_leds = rgb_strand_get_num_leds(strand);
    LED_TYPE leds[RGB_STRAND_MAX_NUM_LEDS];

    switch(status->current.state) {
        case RGB_STRAND_ANIM_STATE_LIKE_SWIRL:
            for (uint8_t i = 0; i < num_leds; i++) {
                if (i != status->current.led_i) {
                    sethsv_rs(HSV_OFF, (LED_TYPE *)&leds[i]);
                }
            }
            sethsv_rs(HSV_WHITE, &leds[status->current.led_i]);
            rgb_strand_set(strand, leds, num_leds);
            if (timer_expired(now, status->nexttime)) {
                status->current.led_i++;
                status->current.led_i %= num_leds;
                if (status->current.led_i == 0) {
                    status->current.count++;
                    status->current.led_i = 1;
                }
                status->nexttime = now + status->config.time_step;
            }
            if (status->current.count >= status->config.num_times) {
                rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_LIKE_BLINKS); }
            break;
        case RGB_STRAND_ANIM_STATE_LIKE_BLINKS:
            if (timer_expired(now, status->nexttime)) {
                rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_OFF);
            }
            else {
                uint16_t time_left = TIMER_DIFF_16(status->nexttime, now);
                uint8_t off = (time_left / _ANIM_LIKE_BLINK_HALF_PERIOD) % 2;

                if (off) {
                    rgb_strand_set_same_color(strand, HSV_OFF);
                }
                else {
                    sethsv_rs(status->config.color.h, status->config.color.s, status->config.color.v, leds);
                    for (uint8_t i = 1; i < num_leds; i++) {
                        sethsv_rs(HSV_WHITE, (LED_TYPE *)&leds[i]);
                    }
                    rgb_strand_set(strand, leds, num_leds);
                }
            }
            break;
        default:
            break;
    }
}

void rgb_strand_set_state_like(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now) {
    switch(state) {
        case RGB_STRAND_ANIM_STATE_LIKE_SWIRL:
            status->nexttime = now + status->config.time_step;
            status->current.count = 0;
            status->current.led_i = 1;
            break;
        case RGB_STRAND_ANIM_STATE_LIKE_BLINKS:
            status->nexttime = now + RGB_STRAND_ANIM_LIKE_BLINKS_DURATION;
        default:
            break;
    }
}

void rgb_strand_effect_blinky(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now) {
    if (status->config.num_times > 0 && status->current.count >= status->config.num_times) {
        rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_OFF);
        return;
    }
    switch(status->current.state) {
        case RGB_STRAND_ANIM_STATE_BLINKY_BLINKON:
            rgb_strand_set_same_color(strand, status->config.color.h, status->config.color.s, status->config.color.v);
            if (timer_expired(now, status->nexttime)) {
                rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_BLINKY_BLINKOFF);
            }
            break;
        case RGB_STRAND_ANIM_STATE_BLINKY_BLINKOFF:
            rgb_strand_set_same_color(strand, HSV_OFF);
            if (timer_expired(now, status->nexttime)) {
                status->current.count++;
                rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_BLINKY_BLINKON);
            }
            break;
    }
}

void rgb_strand_set_state_blinky(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now) {
    switch(state) {
        case RGB_STRAND_ANIM_STATE_BLINKY_BLINKON:
        case RGB_STRAND_ANIM_STATE_BLINKY_BLINKOFF:
            status->nexttime = now + status->config.period/2;
            break;
        default:
            status->current.count = 0;
            break;
    }
}

void rgb_strand_effect_rainbow(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now) {
    if (RGB_STRAND_ANIM_STATE_RAINBOW != status->current.state) {
        return;
    }
    if (status->config.num_times > 0 && status->current.count >= status->config.num_times) {
        rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_OFF);
        return;
    }
    status->current.color.h++;
    rgb_strand_set_same_color(strand, status->current.color.h, status->current.color.s, status->current.color.v);
    if (status->current.color.h == status->config.color.h) {
        status->current.count++;
    }
}

void rgb_strand_set_state_rainbow(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now) {
    switch(state) {
        case RGB_STRAND_ANIM_STATE_RAINBOW:
            status->current.count = 0;
            status->nexttime = now + status->config.period;
            break;
        default:
            break;
    }
}

#ifndef RGB_STRAND_ANIM_BREATHE_CENTER
#    define RGB_STRAND_ANIM_BREATHE_CENTER 2.6
#endif

void rgb_strand_effect_breathing(uint8_t strand, rgb_strand_anim_status_t *status, uint16_t now) {
    if (RGB_STRAND_ANIM_STATE_BREATHING != status->current.state) {
        return;
    }
    if (timer_expired(now, status->nexttime)) {
        status->current.count++;
        status->nexttime = now + status->config.period;
    }
    if (status->config.num_times > 0 && status->current.count >= status->config.num_times) {
        rgb_strand_animation_set_state(strand, RGB_STRAND_ANIM_STATE_OFF);
        return;
    }

    double period = status->config.period;
    double timeleft = TIMER_DIFF_16(status->nexttime, now);
    uint8_t val = (exp(sin((timeleft / period) * M_PI)) - RGB_STRAND_ANIM_BREATHE_CENTER / M_E) * (status->current.color.v / (M_E - 1 / M_E));
    rgb_strand_set_same_color(strand, status->current.color.h, status->current.color.s, val);
}

void rgb_strand_set_state_breathing(uint8_t strand, rgb_strand_anim_state_t state, rgb_strand_anim_status_t *status, uint16_t now) {
    switch(state) {
        case RGB_STRAND_ANIM_STATE_BREATHING:
            status->current.count = 0;
            status->nexttime = now + status->config.period;
            break;
        default:
            break;
    }
}

uint8_t rgb_strand_get_num_leds(uint8_t strand) {
    switch (strand) {
#ifdef RGB_STRAND_0_NUM
        case 0:
            return RGB_STRAND_0_NUM;
#endif
#ifdef RGB_STRAND_1_NUM
        case 1:
            return RGB_STRAND_1_NUM;
#endif
#ifdef RGB_STRAND_2_NUM
        case 2:
            return RGB_STRAND_2_NUM;
#endif
#ifdef RGB_STRAND_3_NUM
        case 3:
            return RGB_STRAND_3_NUM;
#endif
#ifdef RGB_STRAND_4_NUM
        case 4:
            return RGB_STRAND_4_NUM;
#endif
#ifdef RGB_STRAND_5_NUM
        case 5:
            return RGB_STRAND_5_NUM;
#endif
#ifdef RGB_STRAND_6_NUM
        case 6:
            return RGB_STRAND_6_NUM;
#endif
#ifdef RGB_STRAND_7_NUM
        case 7:
            return RGB_STRAND_7_NUM;
#endif
#ifdef RGB_STRAND_8_NUM
        case 8:
            return RGB_STRAND_8_NUM;
#endif
#ifdef RGB_STRAND_9_NUM
        case 9:
            return RGB_STRAND_9_NUM;
#endif
#ifdef RGB_STRAND_A_NUM
        case 10:
            return RGB_STRAND_A_NUM;
#endif
#ifdef RGB_STRAND_B_NUM
        case 11:
            return RGB_STRAND_B_NUM;
#endif
        default:
            break;
    }
    return 0;
}

void rgb_strand_set_same_color(uint8_t strand, uint8_t h, uint8_t s, uint8_t v) {
    uint8_t i;
    LED_TYPE leds[RGB_STRAND_MAX_NUM_LEDS];
#define _SET_ONE_COLOR(stn, strandnum) \
    for (i = 0; i < RGB_STRAND_##stn##_NUM; i++) { sethsv_rs(h, s, v, (LED_TYPE *)&leds[i]); } \
    rgb_strand_set(strandnum, leds, RGB_STRAND_##stn##_NUM)

    switch (strand) {
#ifdef RGB_STRAND_0_DI_PIN
        case 0:
            _SET_ONE_COLOR(0, 0);
            break;
#endif
#ifdef RGB_STRAND_1_DI_PIN
        case 1:
            _SET_ONE_COLOR(1, 1);
            break;
#endif
#ifdef RGB_STRAND_2_DI_PIN
        case 2:
            _SET_ONE_COLOR(2, 2);
            break;
#endif
#ifdef RGB_STRAND_3_DI_PIN
        case 3:
            _SET_ONE_COLOR(3, 3);
            break;
#endif
#ifdef RGB_STRAND_4_DI_PIN
        case 4:
            _SET_ONE_COLOR(4, 4);
            break;
#endif
#ifdef RGB_STRAND_5_DI_PIN
        case 5:
            _SET_ONE_COLOR(5, 5);
            break;
#endif
#ifdef RGB_STRAND_6_DI_PIN
        case 6:
            _SET_ONE_COLOR(6, 6);
            break;
#endif
#ifdef RGB_STRAND_7_DI_PIN
        case 7:
            _SET_ONE_COLOR(7, 7);
            break;
#endif
#ifdef RGB_STRAND_8_DI_PIN
        case 8:
            _SET_ONE_COLOR(8, 8);
            break;
#endif
#ifdef RGB_STRAND_9_DI_PIN
        case 9:
            _SET_ONE_COLOR(9, 9);
            break;
#endif
#ifdef RGB_STRAND_A_DI_PIN
        case 10:
            _SET_ONE_COLOR(A, 10);
            break;
#endif
#ifdef RGB_STRAND_B_DI_PIN
        case 11:
            _SET_ONE_COLOR(B, 11);
            break;
#endif
        default:
            break;
    }
}

__attribute__((weak)) void rgb_strand_call_driver(uint8_t strand, LED_TYPE *start_led, uint8_t num_leds) {
    ws2812_strand_setleds(strand, start_led, num_leds);
}

void rgb_strand_set(uint8_t strand, LED_TYPE *leds, uint8_t num_leds) {
    rgb_strand_call_driver(strand, leds, num_leds);
}

