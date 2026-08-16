/* Copyright 2026 Jubakuba
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

#include "quantum.h"

static uint16_t space_timer = 0;
static uint16_t caps_timer = 0;
static bool     space_active = false;
static bool     caps_active = false;

static uint8_t  space_heat = 0;
static uint8_t  caps_heat = 0;
static uint16_t heatmap_timer = 0;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (record->event.key.row == 5 && record->event.key.col == 3) {
            space_timer  = timer_read();
            space_active = true;
            space_heat   = (space_heat + 30 > 255) ? 255 : space_heat + 30;
        }
        if (record->event.key.row == 3 && record->event.key.col == 0) {
            caps_timer  = timer_read();
            caps_active = true;
            caps_heat   = (caps_heat + 30 > 255) ? 255 : caps_heat + 30;
        }
    }
    return process_record_user(keycode, record);
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    uint8_t mode = rgb_matrix_get_mode();

    if (mode == RGB_MATRIX_SOLID_REACTIVE_SIMPLE || mode == RGB_MATRIX_SOLID_REACTIVE) {
        uint16_t max_fade_time = 1200 - (rgb_matrix_config.speed * 4);

        if (space_active) {
            uint16_t elapsed = timer_elapsed(space_timer);
            if (elapsed > max_fade_time) {
                space_active = false;
            } else {
                HSV current_hsv = rgb_matrix_config.hsv;
                uint8_t fade = 255 - (255 * elapsed / max_fade_time);

                if (mode == RGB_MATRIX_SOLID_REACTIVE_SIMPLE) {
                    current_hsv.v = fade;
                } else {
                    current_hsv.h += (130U * fade) / 255;
                }

                RGB current_rgb = hsv_to_rgb(current_hsv);
                rgb_matrix_set_color(68, current_rgb.r, current_rgb.g, current_rgb.b);
                rgb_matrix_set_color(88, current_rgb.r, current_rgb.g, current_rgb.b);
            }
        }

        if (caps_active) {
            uint16_t elapsed = timer_elapsed(caps_timer);
            if (elapsed > max_fade_time) {
                caps_active = false;
            } else {
                HSV     current_hsv = rgb_matrix_config.hsv;
                uint8_t fade        = 255 - (255 * elapsed / max_fade_time);

                if (mode == RGB_MATRIX_SOLID_REACTIVE_SIMPLE) {
                    current_hsv.v = fade;
                } else {
                    current_hsv.h += (130 * fade) / 255;
                }

                RGB current_rgb = hsv_to_rgb(current_hsv);
                rgb_matrix_set_color(63, current_rgb.r, current_rgb.g, current_rgb.b);
            }
        }
    } else if (mode == RGB_MATRIX_TYPING_HEATMAP) {
        if (timer_elapsed(heatmap_timer) > 25) {
            uint8_t cool_rate = (rgb_matrix_config.speed / 150) + 1;
            if (space_heat > cool_rate)
                space_heat -= cool_rate;
            else
                space_heat = 0;
            if (caps_heat > cool_rate)
                caps_heat -= cool_rate;
            else
                caps_heat = 0;
            heatmap_timer = timer_read();
        }

        HSV space_hsv = {170 - (170 * space_heat / 255), rgb_matrix_config.hsv.s, (rgb_matrix_config.hsv.v * space_heat) / 255};
        RGB space_rgb = hsv_to_rgb(space_hsv);
        rgb_matrix_set_color(68, space_rgb.r, space_rgb.g, space_rgb.b);
        rgb_matrix_set_color(88, space_rgb.r, space_rgb.g, space_rgb.b);

        HSV caps_hsv = {170 - (170 * caps_heat / 255), rgb_matrix_config.hsv.s, (rgb_matrix_config.hsv.v * caps_heat) / 255};
        RGB caps_rgb = hsv_to_rgb(caps_hsv);
        rgb_matrix_set_color(63, caps_rgb.r, caps_rgb.g, caps_rgb.b);
    }

    return true;
}