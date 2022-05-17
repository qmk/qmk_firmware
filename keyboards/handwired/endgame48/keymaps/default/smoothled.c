// Copyright 2022 Andrew Dunai (@and3rson)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "endgame48.h"
#include "smoothled.h"
#include "math.h"
#include "string.h"

static LED_TYPE   source[RGBLED_NUM]  = {};
static LED_TYPE   current[RGBLED_NUM] = {};
static LED_TYPE   target[RGBLED_NUM]  = {};
static uint32_t   duration            = 1500;
static int32_t    smoothledTimer      = -1;
static animFunc_t animFunc;

const float RGBLED_STEP = 1.0f / ((float)RGBLED_NUM);

void smoothled_set(uint32_t color, uint32_t newDuration, animFunc_t newAnimFunc) {
    smoothledTimer = timer_read32();
    LED_TYPE next  = {.r = (color >> 16) & 0xFF, .g = (color >> 8) & 0xFF, .b = color & 0xFF};
    for (uint8_t p = 0; p < RGBLED_NUM; p++) {
        source[p] = current[p];
        target[p] = next;
    }
    duration = newDuration;
    animFunc = newAnimFunc;
}

LED_TYPE swimOut(LED_TYPE a, LED_TYPE b, float k, uint8_t x) {
    k = pow(k, 2);
    /* Center */
    x = fabs(5.5 - ((float)x));
    /* Time range for current LED */
    float start = RGBLED_STEP * x;
    float end   = RGBLED_STEP * (x + 1);
    if (k <= start) {
        k = 0;
    } else if (k >= end) {
        k = 1;
    } else {
        k = (k - start) / RGBLED_STEP;
    }
    float rk = 1.0f - k;
    return (LED_TYPE){
        .r = rk * a.r + k * b.r,
        .g = rk * a.g + k * b.g,
        .b = rk * a.b + k * b.b,
    };
}

LED_TYPE swimIn(LED_TYPE a, LED_TYPE b, float k, uint8_t x) {
    if (x < RGBLED_NUM / 2) {
        x = RGBLED_NUM / 2 - x - 1;
    } else {
        x = RGBLED_NUM - (x - RGBLED_NUM / 2 - 1);
    }
    return swimOut(a, b, k, x);
}

void smoothled_process(void) {
    if (smoothledTimer == -1) {
        return;
    }
    smoothled_render();
}

void smoothled_render(void) {
    uint32_t passed = timer_elapsed32(smoothledTimer);
    if (passed > duration) {
        passed         = duration;
        smoothledTimer = -1;
    }
    float k = ((float)passed) / duration;
    for (uint8_t p = 0; p < RGBLED_NUM; p++) {
        current[p] = animFunc(source[p], target[p], k, p);
        /* This is much faster than calling rgblight_setrgb_at every iteration */
        led[p] = current[p];
    }
    rgblight_set();
}
