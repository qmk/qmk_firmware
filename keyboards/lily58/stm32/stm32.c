/* Copyright 2020 zvecr <git@zvecr.com>
 * Copyright 2020 nho-nyc
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
#include "lily58.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config =
{
    // Key Matrix to LED Index
    {
        // Left
        { 11,     10,      9,      8,      7,      6 },
        { 12,     13,     14,     15,     16,     17 },
        { 23,     22,     21,     20,     19,     18 },
        { 24,     25,     26,     27,     28,     29 },
        { NO_LED, 34,     33,     32,     31,     30 },
        // Right
        { 40,     41,     42,     43,     44,     45 },
        { 51,     50,     49,     48,     47,     46 },
        { 52,     53,     54,     55,     56,     57 },
        { 63,     62,     61,     60,     59,     58 },
        { NO_LED, 64,     65,     67,     68,     69 },
    },
    // LED Index to Physical Position
    {
        // Left
        { 80, 56 }, { 48, 56 }, { 16, 40 }, { 16, 8 }, { 48, 8 }, { 80, 8 },
        { 80, 0 }, { 64, 0 }, { 48, 0 }, { 32, 0 }, { 16, 0 }, { 0, 0 },
        { 0, 16 }, { 16, 16 }, { 32, 16 }, { 48, 16 }, { 64, 16 }, { 80, 16 },
        { 80, 32 }, { 64, 32 }, { 48, 32 }, { 32, 32 }, { 16, 32 }, { 0, 32 },
        { 0, 48 }, { 16, 48 }, { 32, 48 }, { 48, 48 }, { 64, 48 }, { 80, 48 },
        { 96, 40 }, { 96, 64 }, { 72, 64 }, { 56, 64 }, { 40, 64 },
        // Right
        { 144, 56 }, { 176, 56 }, { 208, 40 }, { 208, 8 }, { 176, 8 }, { 144, 8 },
        { 144, 0 }, { 160, 0 }, { 176, 0 }, { 192, 0 }, { 208, 0 }, { 224, 0 },
        { 224, 16 }, { 208, 16 }, { 192, 16 }, { 176, 16 }, { 160, 16 }, { 144, 16 },
        { 144, 32 }, { 160, 32 }, { 176, 32 }, { 192, 32 }, { 208, 32 }, { 224, 32 },
        { 224, 48 }, { 208, 48 }, { 192, 48 }, { 176, 48 }, { 160, 48 }, { 144, 48 },
        { 128, 40 }, { 128, 64 }, { 152, 64 }, { 168, 64 }, { 184, 64 },

    },
    // LED Index to Flag
    {
        // Underglow
        2, 2, 2, 2, 2, 2,
        // Key backlight
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        // Underglow
        2, 2, 2, 2, 2, 2,
        // Key backlight
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

void swap_matrix_hands(led_config_t* led_config)
{
    uint8_t uint8;
    point_t point;
    int i, j;

    int half_matrix_rows = MATRIX_ROWS / 2;
    int half_driver_led_total = DRIVER_LED_TOTAL / 2;

    for (i = 0; i < half_matrix_rows; i++)
    {
        for (j = 0; j < MATRIX_COLS; j++)
        {
            uint8 = led_config->matrix_co[i][j];
            led_config->matrix_co[i][j] = led_config->matrix_co[i + half_matrix_rows][j];
            led_config->matrix_co[i + half_matrix_rows][j] = uint8;
        }
    }

    for (i = 0; i < half_driver_led_total; i++)
    {
        point = led_config->point[i];
        led_config->point[i] = led_config->point[i + half_driver_led_total];
        led_config->point[i + half_driver_led_total] = point;
    }
}
#endif

void matrix_init_kb(void) {
    #ifdef RGB_MATRIX_ENABLE
    if (!is_keyboard_master())
    {
      swap_matrix_hands(&g_led_config);
    }
    #endif
}


