/* Copyright 2022 Chris Tanaka <https://github.com/christanaka>
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

#include QMK_KEYBOARD_H

// clang-format off
#define _OLED_WIDTH         (OLED_DISPLAY_WIDTH - 1)
#define _OLED_HEIGHT        (OLED_DISPLAY_HEIGHT - 1)

#ifdef SPLIT_KEYBOARD
#define _PHYSICAL_PARTS 2
#else
#define _PHYSICAL_PARTS 1
#endif

#ifdef TYPEHUD_MATRIX_ROWS
#define _NML_MATRIX_ROWS TYPEHUD_MATRIX_ROWS
#else
#    ifdef SPLIT_KEYBOARD
#define _NML_MATRIX_ROWS (MATRIX_ROWS / 2)
#    else
#define _NML_MATRIX_ROWS MATRIX_ROWS
#    endif
#endif

#ifdef TYPEHUD_MATRIX_COLS
#define _NML_MATRIX_COLS TYPEHUD_MATRIX_COLS
#else
#define _NML_MATRIX_COLS (MATRIX_COLS * _PHYSICAL_PARTS)
#endif

#define _MATRIX_SIZE        2
#if defined(TYPEHUD_MATRIX_ROTATE_90) || defined(TYPEHUD_MATRIX_ROTATE_270)
#define _MATRIX_WIDTH       (_NML_MATRIX_ROWS * _MATRIX_SIZE + 2)
#define _MATRIX_HEIGHT      (_NML_MATRIX_COLS * _MATRIX_SIZE + 2)
#else
#define _MATRIX_WIDTH       (_NML_MATRIX_COLS * _MATRIX_SIZE + 2)
#define _MATRIX_HEIGHT      (_NML_MATRIX_ROWS * _MATRIX_SIZE + 2)
#endif
#define _MATRIX_X           0
#define _MATRIX_Y           (_OLED_HEIGHT - _MATRIX_HEIGHT + 1)
#define _MATRIX_RPAD        2
#define _MATRIX_PAD_WIDTH   (_MATRIX_WIDTH + _MATRIX_RPAD)

#define _BAR_WIDTH          3
#define _BAR_HEIGHT         _OLED_HEIGHT
#define _BAR_X              (_OLED_WIDTH - _BAR_WIDTH)

#define _AXIS_WIDTH         5
#define _AXIS_HEIGHT        _OLED_HEIGHT
#define _AXIS_TICK_WIDTH    3
#define _AXIS_SUBTICK_WIDTH 2
#define _AXIS_INTERVAL      3
#define _AXIS_TICK_INTERVAL 15
#define _AXIS_RPAD          2
#define _AXIS_PAD_WIDTH     (_AXIS_WIDTH + _AXIS_RPAD)
#define _AXIS_X             (_OLED_WIDTH - _BAR_WIDTH - _AXIS_PAD_WIDTH)

#define _CARET_WIDTH        3
#define _CARET_HEIGHT       5

#define _GRAPH_RPAD         2
#define _GRAPH_MAX_WIDTH    (_OLED_WIDTH - _BAR_WIDTH - _AXIS_PAD_WIDTH - _CARET_WIDTH - _GRAPH_RPAD - _MATRIX_PAD_WIDTH)
#define _GRAPH_WIDTH        (_GRAPH_MAX_WIDTH - 4)
#define _GRAPH_HEIGHT       31
#define _GRAPH_REFRESH      300
#define _GRAPH_X            (_MATRIX_WIDTH + _MATRIX_RPAD)
#define _GRAPH_Y            0
// clang-format on

void 
    typehud_init(void),
    typehud_render(void),
    typehud_process_record(keyrecord_t *record);
