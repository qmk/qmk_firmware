#pragma once

#include "brandonschlack.h"
#include "color.h"
#include "rgblight_list.h"

#ifndef RGB_THEME_COLORS_MAX
#define RGB_THEME_COLORS_MAX 5
#endif

typedef struct {
    const HSV *colors[RGB_THEME_COLORS_MAX];
} rgb_theme_t;

extern const rgb_theme_t *themes[];

void set_rgb_theme(uint8_t index);
rgb_theme_t get_rgb_theme(void);

void rgb_theme_step(void);
void rgb_theme_step_reverse(void);

HSV get_rgb_theme_color(uint8_t index);
void rgb_theme_layer(layer_state_t state);
