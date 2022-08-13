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

#include "rgb_handler.h"

uint8_t indicator_state = DEFAULT_INDI;

const HexColor PROGMEM indicators[][MATRIX_ROWS-1][MATRIX_COLS] = { TRANS_INDICATORS };

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    /* If we are IDLING set matrix to black */
    if(rgb_matrix_idling){
        for (uint8_t i = led_min; i <= led_max; i++) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0,0,0);
        }
        return;
    }

    /* If we are showing the animations, we dont have to run any of this */
    if(indicator_state == SHOW_ANIM){
        return;
    }

    int layer_idx = get_highest_layer(layer_state|default_layer_state);

    /* Calculate Brightness */
    uint8_t val = rgb_matrix_config.hsv.v;
    val = val >> 1;
    double n_val = ((double)val * (double)RGB_MATRIX_MAXIMUM_BRIGHTNESS) / (double)255;

    for (uint8_t i = led_min; i <= led_max; i++) {

        /* Get Matrix position */
        uint8_t col_idx = i % MATRIX_COLS;
        uint8_t row_idx = i / MATRIX_COLS;

        /* Get Indicator Color */
        HexColor color = indicators[layer_idx][row_idx][col_idx];

        /* Apply Brightness */
        double r, g, b;

        r = (double)color.r*(n_val/(double)255);
        g = (double)color.g*(n_val/(double)255);
        b = (double)color.b*(n_val/(double)255);

        /* If We are masking the animation */
        if(indicator_state == MASK_ANIM){
            /* Set black the keys that dont have indicators defined */
            if(color.hex == 0)
                RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
            continue;
        }

        /* Apply Indicatore */
        RGB_MATRIX_INDICATOR_SET_COLOR(i, (int)r, (int)g, (int)b);
    }
}