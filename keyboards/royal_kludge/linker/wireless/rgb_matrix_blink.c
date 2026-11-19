// Copyright 2024 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stddef.h>
#include "rgb_matrix.h"
#include "rgb_matrix_blink.h"
#include "timer.h"

#define NUM_BLINK_RGBS (sizeof(blink_rgbs) / sizeof(blink_rgbs[0]))

// /* Example */
// blink_rgb_t blink_rgbs[RGB_MATRIX_BLINK_COUNT] = {
//     {.index = 1, .interval = 250, .times = 5, .color = {.r = 0xFF, .g = 0xFF, .b = 0xFF}, .blink_cb = NULL},
//     {.index = 0xFF, .interval = 250, .times = 5, .color = {.r = 0xFF, .g = 0x00, .b = 0x00}, .blink_cb = NULL},
// };

bool rgb_matrix_blink_set(uint8_t index) {

    for (uint8_t i = 0; i < NUM_BLINK_RGBS; i++) {
        if (blink_rgbs[i].index == index) {
            if (blink_rgbs[i].times < 1) {
                return false;
            }
            blink_rgbs[i].remain_time = blink_rgbs[i].interval * blink_rgbs[i].times * 2 + 1;
            if (blink_rgbs[i].times == 0xFF) {
                blink_rgbs[i].remain_time = blink_rgbs[i].interval + 1;
            }
            return true;
        }
    }

    return false;
}

bool rgb_matrix_blink_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {

    for (uint8_t i = 0; i < NUM_BLINK_RGBS; i++) {
        if (blink_rgbs[i].index == index) {
            blink_rgbs[i].color.r = r;
            blink_rgbs[i].color.g = g;
            blink_rgbs[i].color.b = b;
            return true;
        }
    }

    return false;
}

bool rgb_matrix_blink_set_cb(uint8_t index, void *blink_cb) {

    for (uint8_t i = 0; i < NUM_BLINK_RGBS; i++) {
        if (blink_rgbs[i].index == index) {
            blink_rgbs[i].blink_cb = blink_cb;
            return true;
        }
    }

    return false;
}

bool rgb_matrix_blink_set_interval(uint8_t index, uint32_t interval) {

    for (uint8_t i = 0; i < NUM_BLINK_RGBS; i++) {
        if (blink_rgbs[i].index == index) {
            blink_rgbs[i].interval = interval;
            return true;
        }
    }

    return false;
}

bool rgb_matrix_blink_set_times(uint8_t index, uint32_t times) {

    for (uint8_t i = 0; i < NUM_BLINK_RGBS; i++) {
        if (blink_rgbs[i].index == index) {
            blink_rgbs[i].times = times;
            return true;
        }
    }

    return false;
}

bool rgb_matrix_blink_set_remain_time(uint8_t index, uint32_t time) {

    for (uint8_t i = 0; i < NUM_BLINK_RGBS; i++) {
        if (blink_rgbs[i].index == index) {
            blink_rgbs[i].remain_time = time;
            return true;
        }
    }

    return false;
}

bool rgb_matrix_blink_set_interval_times(uint8_t index, uint32_t interval, uint32_t times) {

    for (uint8_t i = 0; i < NUM_BLINK_RGBS; i++) {
        if (blink_rgbs[i].index == index) {
            blink_rgbs[i].interval = interval;
            blink_rgbs[i].times    = times;
            blink_rgbs[i].time     = 0x00;
            blink_rgbs[i].flip     = false;
            return true;
        }
    }

    return false;
}

__attribute__((weak)) bool rgb_matrix_blink_user(blink_rgb_t *blink_rgb) {
    return true;
}

bool rgb_matrix_blink_task(uint8_t led_min, uint8_t led_max) {

    for (uint8_t rgb_index = 0; rgb_index < NUM_BLINK_RGBS; rgb_index++) {
        if (blink_rgbs[rgb_index].remain_time != 0) {
            if ((blink_rgbs[rgb_index].time == 0) || (timer_elapsed32(blink_rgbs[rgb_index].time) >= blink_rgbs[rgb_index].interval)) {
                blink_rgbs[rgb_index].flip = !blink_rgbs[rgb_index].flip;
                blink_rgbs[rgb_index].time = timer_read32();

                if (blink_rgbs[rgb_index].remain_time >= blink_rgbs[rgb_index].interval) {
                    blink_rgbs[rgb_index].remain_time -= blink_rgbs[rgb_index].interval;
                } else {
                    blink_rgbs[rgb_index].remain_time = 0;
                    blink_rgbs[rgb_index].flip        = false;
                    blink_rgbs[rgb_index].time        = 0;
                }
            }

            if (blink_rgbs[rgb_index].remain_time == 0) {
                if (blink_rgbs[rgb_index].blink_cb != NULL) {
                    blink_rgbs[rgb_index].blink_cb(blink_rgbs[rgb_index].index);
                }
                if (blink_rgbs[rgb_index].index == 0xFF) {
                    rgb_matrix_set_color_all(0x00, 0x00, 0x00);
                } else if (blink_rgbs[rgb_index].index < RGB_MATRIX_LED_COUNT) {
                    rgb_matrix_set_color(blink_rgbs[rgb_index].index, 0x00, 0x00, 0x00);
                }
                continue;
            }

            if (rgb_matrix_blink_user(&blink_rgbs[rgb_index]) != true) {
                continue;
            }

            if (blink_rgbs[rgb_index].flip) {
                if (blink_rgbs[rgb_index].index == 0xFF) {
                    rgb_matrix_set_color_all(blink_rgbs[rgb_index].color.r,
                                             blink_rgbs[rgb_index].color.g,
                                             blink_rgbs[rgb_index].color.b);
                } else if (blink_rgbs[rgb_index].index < RGB_MATRIX_LED_COUNT) {
                    rgb_matrix_set_color(blink_rgbs[rgb_index].index,
                                         blink_rgbs[rgb_index].color.r,
                                         blink_rgbs[rgb_index].color.g,
                                         blink_rgbs[rgb_index].color.b);
                }
            } else {
                if (blink_rgbs[rgb_index].index == 0xFF) {
                    rgb_matrix_set_color_all(0x00, 0x00, 0x00);
                } else if (blink_rgbs[rgb_index].index < RGB_MATRIX_LED_COUNT) {
                    rgb_matrix_set_color(blink_rgbs[rgb_index].index, 0x00, 0x00, 0x00);
                }
            }
        } else {
            blink_rgbs[rgb_index].flip = false;
            blink_rgbs[rgb_index].time = 0;
        }
    }

    return true;
}
