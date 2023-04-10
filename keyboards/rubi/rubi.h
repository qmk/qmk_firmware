/* Copyright 2021 gregorio
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

#include "quantum.h"

#define CALC_DIGITS 12

enum rubi_keycodes {
    ENC_PRESS = QK_KB_0,
    CL_PLUS,
    CL_STAR,
    CL_TYPE
};

enum oled_modes {
    OLED_MODE_DEFAULT,
    OLED_MODE_CALC,
    OLED_MODE_OFF,
    _NUM_OLED_MODES
};

enum encoder_modes {
    ENC_MODE_VOLUME,
    ENC_MODE_MEDIA,
    ENC_MODE_BRIGHTNESS,
    _NUM_ENCODER_MODES
};

extern uint8_t current_layer;
extern uint8_t oled_mode;
extern uint8_t encoder_mode;

extern char calc_result_display[CALC_DIGITS+1];
extern char calc_operator_display;
extern char calc_status_display[CALC_DIGITS+1];
extern uint8_t calc_display_lines;

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
void change_oled_mode(void);

void change_encoder_mode(bool reverse);
uint16_t handle_encoder_cw(void);
uint16_t handle_encoder_ccw(void);
uint16_t handle_encoder_press(void);

void calcUpdate(void);
void calcInput(char input);
void calcOperands(void);
