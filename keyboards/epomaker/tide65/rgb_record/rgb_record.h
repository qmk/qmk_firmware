/* 
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
#include <stdbool.h>
#include <string.h>

#include <math.h>
#include "color.h"
#include "eeprom.h"
#include "quantum.h"
#include "wireless.h"

#define HS_GET_H(value) ((uint8_t)(value >> 8))
#define HS_GET_S(value) ((uint8_t)(value & 0xFF))

/* HSV Color bit[15:8] H  bit[7:0] S */
#define HS_AZURE        0x8466
#define HS_BLACK        0x0000
#define HS_BLUE         0xAAFF
#define HS_CHARTREUSE   0x40FF
#define HS_CORAL        0x0BB0
#define HS_GOLD         0x24FF
#define HS_GOLDENROD    0x1EDA
#define HS_GREEN        0x55FF
#define HS_MAGENTA      0xD5FF
#define HS_ORANGE       0x15FF
#define HS_PINK         0xEA80
#define HS_PURPLE       0xBFFF
#define HS_RED          0x00FF
#define HS_CYAN         0x6AFF
#define HS_TEAL         0x80FF
#define HS_TURQUOISE    0x7B5A
#define HS_WHITE        0x0101
#define HS_YELLOW       0x2BFF

#define LASET_MOD_NO    0xFF
#define RGB_HSV_MAX     7
#define ________        HS_BLACK

#ifndef RGB_RECORD_HS_LISTS
#    define RGB_RECORD_HS_LISTS \
        {HS_BLACK, HS_RED, HS_GREEN, HS_BLUE, HS_YELLOW, HS_PURPLE, HS_CYAN, HS_WHITE}
#endif

#define RGB_MATRIX_BAT_VAL 150

#define IM_BAT_REQ_LEVEL1_VAL 50
#define IM_BAT_REQ_LEVEL1_COLOR 0x00, RGB_MATRIX_BAT_VAL, 0x00

#define IM_BAT_REQ_LEVEL2_VAL 30
#define IM_BAT_REQ_LEVEL2_COLOR 0x00, RGB_MATRIX_BAT_VAL, 0x00

#define IM_BAT_REQ_LEVEL3_COLOR RGB_MATRIX_BAT_VAL, 0x00, 0x00

void rgbrec_read_current_channel(uint8_t channel);
void rgbrec_set_close_all(uint8_t h, uint8_t s, uint8_t v);
void rgbrec_play(uint8_t led_min, uint8_t led_max);
bool rgbrec_end(uint8_t channel);
bool rgbrec_start(uint8_t channel);
bool rgbrec_show(uint8_t channel);
void rgbrec_init(uint8_t channel);
bool rgbrec_is_started(void);
void eeconfig_init_user_datablock(void);
bool rgbrec_register_record(uint16_t keycode, keyrecord_t *record);
void record_rgbmatrix_increase(uint8_t *last_mode);
void record_color_hsv(bool status);
void query(void);
