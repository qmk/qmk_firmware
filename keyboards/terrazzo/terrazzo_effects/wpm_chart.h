/* Copyright 2020 ademey "MsMustard"
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

#ifndef DISABLE_TERRAZZO_EFFECT_WPM_CHART
TERRAZZO_EFFECT(WPM_CHART)
#   ifdef TERRAZZO_EFFECT_IMPLS

static uint8_t number_3_4[10][12] = {
{ // 0
    9, 9, 9,
    9, 0, 9,
    9, 0, 9,
    9, 9, 9
}, 
{ // 1
    0, 9, 0,
    9, 9, 0,
    0, 9, 0,
    9, 9, 9
},
{ // 2
    9, 9, 0,
    0, 0, 9,
    0, 9, 0,
    9, 9, 9
},
{ // 3
    9, 9, 9,
    0, 9, 0,
    0, 0, 9,
    9, 9, 0
},
{ // 4
    9, 0, 9,
    9, 0, 9,
    9, 9, 9,
    0, 0, 9
},
{ // 5
    9, 9, 9,
    9, 9, 0,
    0, 0, 9,
    9, 9, 9
},
{ // 6
    0, 0, 9,
    0, 9, 0,
    9, 0, 9,
    0, 9, 0
},
{ // 7
    9, 9, 9,
    0, 0, 9,
    0, 9, 0,
    9, 0, 0
},
{ // 8
    9, 9, 9,
    9, 0, 9,
    9, 4, 9,
    9, 9, 9
},
{ // 9
    9, 9, 9,
    9, 0, 9,
    9, 9, 9,
    0, 0, 9
}
};

/* Reference to create a gradient effect */
uint8_t wpm_levels[10] = {20, 9, 8, 7, 6, 5, 4, 3, 2, 1};

void WPM_CHART(uint8_t i, bool dir) {
    led_matrix_set_index_value_all(0);
    uint8_t c_wpm = get_current_wpm();
    uint8_t half_wpm = floor(c_wpm / 2);
    uint8_t max_rows = 10;
    /* Turn on LED for current WPM. Each pixel is 2 wpm. */
    for (int k = 0; k < half_wpm && k < 70; k++) {
        uint8_t current_row = (int)floor(k / 7);
        led_matrix_set_index_value(k, wpm_levels[max_rows - current_row]);
    };
    uint8_t d1 = (int)floor(c_wpm / 10);
    /* There is only room to print 2 digits. If the WPM is greater than
       99 then the last 2 digits will show, ie 120 = 20. */
    if (c_wpm > 99) {
        uint8_t tens_place = d1 % 10;
        terrazzo_draw_at(0, 11, 3, 4, number_3_4[tens_place]);
    } else {
        terrazzo_draw_at(0, 11, 3, 4, number_3_4[d1]);
    }
    
    terrazzo_draw_at(4, 11, 3, 4, number_3_4[c_wpm % 10]);
}

#   endif
#endif