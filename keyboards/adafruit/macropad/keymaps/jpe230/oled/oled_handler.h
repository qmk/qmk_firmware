/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "keymap.h"
#include <stdio.h>

/* -----------------------
 * Custom OLED Region
 * -----------------------
 */
enum OLED_STATES{
    DEFAULT_OLED = 0,
    BONGO_CAT,
    LOGO
};

/* -----------------------
 * OLED Function Prototypes
 * -----------------------
 */
void center_text(const char *text, char *output, int width);
uint8_t get_current_wpm(void);
void fake_wpm_increment(void);
void fake_wpm_decay(void);
void render_short_array_pos(const uint16_t* frame, uint8_t x, uint8_t y, uint8_t width);
void render_short_array(const uint16_t* frame);
void render_anim(void);
void render_wpm(void);
void render_logo(void);
void render_bongo_cat(void);
void render_authenticator(int layer);
void render_lockscreen(void);

extern uint8_t oled_state;
extern bool indicator_oled_state[MATRIX_ROWS][MATRIX_COLS];
extern const char PROGMEM *key_strings[][MATRIX_ROWS][MATRIX_COLS];
extern const char* PROGMEM layer_strings[];

/* -----------------------
 * OLED Defines
 * -----------------------
 */
#define CHARS_PER_LINE 21
#define CHARS_PER_KEY 7
#define decay_every_x 250
#define increment_amount 15