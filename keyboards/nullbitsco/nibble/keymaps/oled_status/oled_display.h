/* Copyright 2021 Jose Luis Adelantado Torres
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

#include <stdint.h>

typedef enum {
    OLED_MODE_IDLE = 0,
    OLED_MODE_VOLUME_UP = 1,
    OLED_MODE_VOLUME_DOWN = 2,
    OLED_MODE_RGB_ON = 3,
    OLED_MODE_RGB_OFF = 4,
} oled_mode_t;

uint16_t oled_timer;
oled_mode_t oled_mode;

void set_oled_mode(oled_mode_t mode);

void process_record_encoder_oled(uint16_t keycode);

void process_record_keymap_oled(uint16_t keycode);

void render_wpm(void);

void render_idle(void);

void render_status_mode_message(void);

void render_frame(void);
