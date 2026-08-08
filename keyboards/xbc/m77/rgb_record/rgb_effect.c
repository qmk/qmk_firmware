// Copyright 2025 lucky(@lucky-zang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_effect.h"

static uint8_t adjust_value(uint8_t val, uint8_t max, uint8_t *dir) {
    if (*dir == 0) {
        if (val < max - 1)
            val += 2;
        else
            val++;
        if (val >= max)
            *dir = 1;
    } else {
        if (val > 1)
            val -= 2;
        else
            val--;
        if (val == 0)
            *dir = 0;
    }
    return val;
}

void rgblight_effect_breathing(animation_status_t *anim) {
    static uint8_t i = 0, r = 0, g = 0, b = 0, dir = 0;

    switch (i) {
        case 0:
            r = adjust_value(r, BREATHING_VAL, &dir);
            if (r == 0 && dir == 0) i++;
            break;
        case 1:
            g = adjust_value(g, BREATHING_VAL, &dir);
            if (g == 0 && dir == 0) i++;
            break;
        case 2:
            b = adjust_value(b, BREATHING_VAL, &dir);
            if (b == 0 && dir == 0) i++;
            break;
        case 3:
            r = adjust_value(r, BREATHING_VAL, &dir);
            b = r;
            if (r == 0 && dir == 0) i++;
            break;
        case 4:
            r = adjust_value(r, BREATHING_VAL, &dir);
            g = r;
            if (r == 0 && dir == 0) i++;
            break;
        case 5:
            g = adjust_value(g, BREATHING_VAL, &dir);
            b = g;
            if (g == 0 && dir == 0) i++;
            break;
        case 6:
            g = adjust_value(g, BREATHING_VAL, &dir);
            b = g;
            r = g;
            if (g == 0 && dir == 0) i = 0;
            break;
    }

    for (uint8_t j = 0; j < RGBLED_NUM; j++)
        rgblight_setrgb_at(r, g, b, j);
}

void rgblight_effect_rainbow_mood(animation_status_t *anim) {
    static uint8_t i = 0, r = RAINBOW_MOOD, g = 0, b = 0;

    if (!rgblight_config.enable) return;



    switch (i) {
        case 0: 
            r = (r > 1) ? r - 2 : r - 1;
            g = (g < RAINBOW_MOOD - 1) ? g + 2 : g + 1;
            if (g >= RAINBOW_MOOD) i++;
            break;
        case 1: 
            g = (g > 1) ? g - 2 : g - 1;
            b = (b < RAINBOW_MOOD - 1) ? b + 2 : b + 1;
            if (b >= RAINBOW_MOOD) i++;
            break;
        case 2: 
            b = (b > 1) ? b - 2 : b - 1;
            r = (r < RAINBOW_MOOD - 1) ? r + 2 : r + 1;
            if (r >= RAINBOW_MOOD) i = 0;
            break;
    }

    for (uint8_t j = 0; j < RGBLED_NUM; j++)
        rgblight_setrgb_at(r, g, b, j);
}

bool rgblight_effect_custom_rainbow_swirl(animation_status_t *anim) {
    uint8_t hue;
    uint8_t i;

    for (i = 0; i < 5; i++) {
        hue = (RGBLIGHT_RAINBOW_SWIRL_RANGE / rgblight_ranges.effect_num_leds * i + anim->current_hue);
        sethsv(hue, rgblight_config.sat, rgblight_config.val, (LED_TYPE *)&led[i + rgblight_ranges.effect_start_pos]);
        sethsv(hue, rgblight_config.sat, rgblight_config.val, (LED_TYPE *)&led[(i+5) + rgblight_ranges.effect_start_pos]);
    }

    rgblight_set();

    if (anim->delta % 2) {
        anim->current_hue++;
        anim->current_hue++;
    } else {
        anim->current_hue--;
        anim->current_hue--;
    }

    return false;
}