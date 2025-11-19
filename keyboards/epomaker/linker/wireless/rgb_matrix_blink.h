// Copyright 2024 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

typedef struct {
    uint32_t interval;
    uint32_t remain_time;
    uint32_t times;
    uint32_t time;
    uint8_t index;
    uint8_t flip;
    void (*blink_cb)(uint8_t);
    RGB color;
} blink_rgb_t;

#ifndef RGB_MATRIX_BLINK_COUNT
#    define RGB_MATRIX_BLINK_COUNT 0
#endif

extern blink_rgb_t blink_rgbs[RGB_MATRIX_BLINK_COUNT];

bool rgb_matrix_blink_set(uint8_t index);
bool rgb_matrix_blink_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
bool rgb_matrix_blink_set_cb(uint8_t index, void *blink_cb);
bool rgb_matrix_blink_set_interval(uint8_t index, uint32_t interval);
bool rgb_matrix_blink_set_times(uint8_t index, uint32_t times);
bool rgb_matrix_blink_set_remain_time(uint8_t index, uint32_t time);
bool rgb_matrix_blink_set_interval_times(uint8_t index, uint32_t interval, uint32_t times);
bool rgb_matrix_blink_task(uint8_t led_min, uint8_t led_max);
bool rgb_matrix_blink_user(blink_rgb_t *blink_rgb);
