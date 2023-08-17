/* Copyright 2023 Jay Greco
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

#include "typehud.h"

static bool     is_initialized;
static uint16_t timer;
static int8_t   bar_height;
static uint8_t  wpm_arr[_GRAPH_WIDTH];
static uint8_t  point_arr[_GRAPH_WIDTH];


static void 
    render_graph(uint8_t wpm),
    render_caret(void),
    render_axis(void),
    render_bar(void),
    render_init(void);

/*
 * Renders the wpm counter.
 */
static void render_wpm(uint8_t wpm) {
    oled_set_cursor(0, 0);
    oled_write("WPM", false);
    oled_set_cursor(0, 1);
    oled_write(get_u8_str(wpm, '0'), false);
}

/*
 * Renders the keyboard matrix.
 */
static void render_matrix(keyrecord_t *record) {
    uint8_t x      = _MATRIX_X;
    uint8_t y      = _MATRIX_Y;
    uint8_t width  = _MATRIX_WIDTH;
    uint8_t height = _MATRIX_HEIGHT;
#ifdef SPLIT_KEYBOARD
    uint8_t rows = _NML_MATRIX_ROWS;
    uint8_t cols = _NML_MATRIX_COLS;
#endif

    // On initial render draw the matrix outline
    if (!is_initialized) {
        for (uint8_t i = 1; i <= width - 2; i++) {
            oled_write_pixel(x + i, y, true);
            oled_write_pixel(x + i, y + height - 1, true);
        }
        for (uint8_t j = 1; j <= height - 2; j++) {
            oled_write_pixel(x, y + j, true);
            oled_write_pixel(x + width - 1, y + j, true);
        }
        return;
    }

    // Determine position based on matrix rotation
    // For split keyboards the keys on the right half get appended as additional rows and
    // have their columns reset at 0
#ifdef SPLIT_KEYBOARD
    uint8_t row = (record->event.key.row % rows);
    uint8_t col = record->event.key.col;
    if (record->event.key.row >= rows) {
        col += (cols / 2);
    }
#else
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
#endif

#ifdef TYPEHUD_MATRIX_ROW_SHIFT
    row += TYPEHUD_MATRIX_ROW_SHIFT;
#endif
#ifdef TYPEHUD_MATRIX_COL_SHIFT
    col += TYPEHUD_MATRIX_COL_SHIFT;
#endif

    // Scale position to key size
    uint8_t size = _MATRIX_SIZE;
    row *= size;
    col *= size;

    // Render key in matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
#if defined(TYPEHUD_MATRIX_ROTATE_90)
            uint8_t key_x = x + width - 1 - size - row;
            uint8_t key_y = y + 1 + col;
#elif defined(TYPEHUD_MATRIX_ROTATE_180)
            uint8_t key_x = x + width - 1 - size - col;
            uint8_t key_y = y + height - 1 - size - row;
#elif defined(TYPEHUD_MATRIX_ROTATE_270)
            uint8_t key_x = x + 1 + row;
            uint8_t key_y = y + height - 1 - size - col;
#else
            uint8_t key_x = x + 1 + col;
            uint8_t key_y = y + 1 + row;
#endif
            oled_write_pixel(key_x + i, key_y + j, record->event.pressed);
        }
    }
}

/*
 * Renders the graph.
 */
static void render_graph(uint8_t wpm) {
    uint8_t x      = _GRAPH_X;
    uint8_t y      = _GRAPH_Y + _GRAPH_HEIGHT;
    uint8_t width  = _GRAPH_WIDTH;
    uint8_t height = _GRAPH_HEIGHT;

    // Handle intial graph render
    if (!is_initialized) {
        for (uint8_t i = 0; i < width; i++) {
            oled_write_pixel(x + i, y, true);
        }
        return;
    }

    uint8_t i = 0;

    // Shift all graph points except last to the left and re-render
    for (; i < width - 1; i++) {
        int8_t point_delta = point_arr[i + 1] - point_arr[i];

#ifdef TYPEHUD_FILLGRAPH
        if (point_delta < 0) {
#else
        if (point_delta != 0) {
#endif
            oled_write_pixel(x + i, y - point_arr[i], false);
        }

        wpm_arr[i]   = wpm_arr[i + 1];
        point_arr[i] = point_arr[i + 1];

        if (point_delta != 0) {
            oled_write_pixel(x + i, y - point_arr[i], true);
        }
    }

    // Clear last graph point
    if (wpm > wpm_arr[i] && point_arr[i] + 1 <= height) {
#ifndef TYPEHUD_FILLGRAPH
        oled_write_pixel(x + i, y - point_arr[i], false);
#endif
        point_arr[i] = point_arr[i] + 1;
    } else if ((wpm < wpm_arr[i] && point_arr[i] - 1 >= 0) || (wpm <= 0 && point_arr[i] > 0)) {
        oled_write_pixel(x + i, y - point_arr[i], false);
        point_arr[i] = point_arr[i] - 1;
    }

    // Render last graph point
    wpm_arr[i] = wpm;

    if (point_arr[i] != point_arr[i - 1]) {
        oled_write_pixel(x + i, y - point_arr[i], true);
    }
}

/*
 * Renders the caret.
 */
static void render_caret(void) {
    uint8_t x        = _GRAPH_X + _GRAPH_WIDTH + _GRAPH_RPAD + _CARET_WIDTH;
    uint8_t y        = 0;
    uint8_t width    = _CARET_WIDTH;
    uint8_t height   = _CARET_HEIGHT;
    uint8_t g_width  = _GRAPH_WIDTH;
    uint8_t g_height = _GRAPH_HEIGHT;

    // Handle initial caret render
    if (!is_initialized) {
        y = g_height - point_arr[g_width - 1];

        for (uint8_t i = 0; i < width; i++) {
            for (uint8_t j = i; j < height - i; j++) {
                oled_write_pixel(x - i, y - j, true);
            }
        }
        return;
    }

    // Handle caret updates and re-render
    int8_t point_delta = point_arr[g_width - 1] - point_arr[g_width - 2];
    if (point_delta > 0) {
        y = g_height - point_arr[g_width - 2];
        if (y - height + 1 > 0) {
            for (uint8_t i = 0; i < width; i++) {
                oled_write_pixel(x - i, y - i, false);
                oled_write_pixel(x - i, y - height + i, true);
            }
        }
    } else if (point_delta < 0) {
        y = g_height - point_arr[g_width - 1];
        if (y - height + 1 > 0) {
            for (uint8_t i = 0; i < width; i++) {
                oled_write_pixel(x - i, y - height + i, false);
                oled_write_pixel(x - i, y - i, true);
            }
        }
    }
}

/*
 * Renders the axis.
 */
static void render_axis(void) {
    uint8_t x             = _AXIS_X;
    uint8_t y             = _AXIS_HEIGHT;
    uint8_t width         = _AXIS_WIDTH;
    uint8_t height        = _AXIS_HEIGHT;
    uint8_t tick_width    = _AXIS_TICK_WIDTH;
    uint8_t subtick_width = _AXIS_SUBTICK_WIDTH;
    uint8_t interval      = _AXIS_INTERVAL;
    uint8_t tick_interval = _AXIS_TICK_INTERVAL;

    for (uint8_t j = 0; j <= height; j += interval) {
        uint8_t curr_tick_width = 0;

        // Determine tick width and draw extra point if at interval
        if (j % tick_interval == 0) {
            curr_tick_width = tick_width;
            oled_write_pixel(x, y - j, true);
        } else {
            curr_tick_width = subtick_width;
        }

        // Draw tick
        for (uint8_t i = 0; i < curr_tick_width; i++) {
            oled_write_pixel(x + width - i, y - j, true);
        }
    }
}

/*
 * Renders the input bar.
 */
static void render_bar(void) {
    uint8_t x      = _BAR_X;
    uint8_t width  = _BAR_WIDTH;
    uint8_t height = _BAR_HEIGHT;

    // Increment bar height
    bar_height = (bar_height + 1) % height;

    // When bar resets back to 0, clear bar pixels
    if (bar_height % height == 0) {
        for (uint8_t i = 0; i < width; i++) {
            for (uint8_t j = 0; j < height; j++) {
                oled_write_pixel(x + i, j, false);
            }
        }
    }

    // Draw new bar pixels
    for (uint8_t i = 0; i < width; i++) {
        oled_write_pixel(x + i, height - bar_height, true);
    }
}

/*
 * Renders the initial frame for all components.
 */
static void render_init(void) {
    render_graph(0);
    render_caret();
    render_matrix(NULL);
    render_axis();
}

/*
 * Initializes and resets the typehud.
 */
void typehud_init(void) {
    // Reset variables
    is_initialized = false;
    timer          = 0;
    bar_height     = -1;

    for (uint8_t i = 0; i < _GRAPH_WIDTH; i++) {
        wpm_arr[i]   = 0;
        point_arr[i] = 0;
    }

    // Draw the initial graph
    for (uint8_t i = 0; i < _GRAPH_WIDTH; i++) {
        oled_write_pixel(_GRAPH_X + i, _GRAPH_HEIGHT, true);
    }
}

/*
 * Renders the typehud.
 */
void typehud_render(void) {
    uint8_t wpm = get_current_wpm();

    // Run initial rendering once
    if (!is_initialized) {
        render_init();
        is_initialized = true;
    }

    // Render wpm
    render_wpm(wpm);

    // Render next graph and caret frame when timer reaches refresh rate
    if (timer_elapsed(timer) > _GRAPH_REFRESH) {
        render_graph(wpm);
        render_caret();
        timer = timer_read();
    }
}

/*
 * Handles keypresses for the typehud.
 */
void typehud_process_record(keyrecord_t *record) {
    // For split keyboards, only draw on correct side
#ifdef SPLIT_KEYBOARD
#    ifdef TYPEHUD_MASTER
    if (!is_keyboard_master()) {
#    else
    if (is_keyboard_master()) {
#    endif
        return;
    }
#endif
    // Render/update matrix
    render_matrix(record);

    // Render/update input bar on keypress
    if (record->event.pressed) {
        render_bar();
    }
}
