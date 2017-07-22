/* Copyright 2017 Fred Sundvik
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

#include "lcd_backlight_keyframes.h"

bool lcd_backlight_keyframe_animate_color(keyframe_animation_t* animation, visualizer_state_t* state) {
    int frame_length = animation->frame_lengths[animation->current_frame];
    int current_pos = frame_length - animation->time_left_in_frame;
    uint8_t t_h = LCD_HUE(state->target_lcd_color);
    uint8_t t_s = LCD_SAT(state->target_lcd_color);
    uint8_t t_i = LCD_INT(state->target_lcd_color);
    uint8_t p_h = LCD_HUE(state->prev_lcd_color);
    uint8_t p_s = LCD_SAT(state->prev_lcd_color);
    uint8_t p_i = LCD_INT(state->prev_lcd_color);

    uint8_t d_h1 = t_h - p_h; //Modulo arithmetic since we want to wrap around
    int d_h2 = t_h - p_h;
    // Chose the shortest way around
    int d_h = abs(d_h2) < d_h1 ? d_h2 : d_h1;
    int d_s = t_s - p_s;
    int d_i = t_i - p_i;

    int hue = (d_h * current_pos) / frame_length;
    int sat = (d_s * current_pos) / frame_length;
    int intensity = (d_i * current_pos) / frame_length;
    //dprintf("%X -> %X = %X\n", p_h, t_h, hue);
    hue += p_h;
    sat += p_s;
    intensity += p_i;
    state->current_lcd_color = LCD_COLOR(hue, sat, intensity);
    lcd_backlight_color(
            LCD_HUE(state->current_lcd_color),
            LCD_SAT(state->current_lcd_color),
            LCD_INT(state->current_lcd_color));

    return true;
}

bool lcd_backlight_keyframe_set_color(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)animation;
    state->prev_lcd_color = state->target_lcd_color;
    state->current_lcd_color = state->target_lcd_color;
    lcd_backlight_color(
            LCD_HUE(state->current_lcd_color),
            LCD_SAT(state->current_lcd_color),
            LCD_INT(state->current_lcd_color));
    return false;
}

bool lcd_backlight_keyframe_disable(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)animation;
    (void)state;
    lcd_backlight_hal_color(0, 0, 0);
    return false;
}

bool lcd_backlight_keyframe_enable(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)animation;
    (void)state;
    lcd_backlight_color(LCD_HUE(state->current_lcd_color),
        LCD_SAT(state->current_lcd_color),
        LCD_INT(state->current_lcd_color));
    return false;
}
