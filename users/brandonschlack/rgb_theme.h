/* Copyright 2020 Brandon Schlack
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
#pragma once

#include "brandonschlack.h"
#include "color.h"

/*TODO Update as RGBLIGHT Mode */
#ifndef RGB_THEME_COLORS_MAX
#define RGB_THEME_COLORS_MAX 5
#endif

enum rgb_themes {
#define RGB_THEME(name) RGB_THEME_##name,
    #include "rgb_theme_user.inc"
#undef RGB_THEME
    RGB_THEME_MAX
};

// RGB Theme Color
typedef const HSV rgb_theme_color_t;
#define RGB_THEME_COLOR(tname, tcolor,...)   rgb_theme_color_t tname ## _ ## tcolor = { __VA_ARGS__ }

// RGB Theme
typedef struct {
    const HSV *colors[RGB_THEME_COLORS_MAX];
} rgb_theme_t;
extern const rgb_theme_t *themes[];

void set_rgb_theme(uint8_t index);
rgb_theme_t get_rgb_theme(void);

void rgb_theme_step(void);
void rgb_theme_step_reverse(void);

rgb_theme_color_t get_rgb_theme_color(uint8_t index);
void rgb_theme_layer(layer_state_t state);
