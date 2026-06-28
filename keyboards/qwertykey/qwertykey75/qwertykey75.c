/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
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

#ifdef RGB_MATRIX_ENABLE
#define LED_CAP_INDEX       (43)

led_config_t g_led_config = { {
	{ 0  , 1      , 2  , 3      , 4      , 5  , 6      , 7      , 8      , 9  , 10 , 11     , 12     , NO_LED , NO_LED , NO_LED },
	{ 13 , 14     , 15 , 16     , 17     , 18 , 19     , 20     , 21     , 22 , 23 , 24     , 25     , 26     , NO_LED , NO_LED },
	{ 28 , 29     , 30 , 31     , 32     , 33 , 34     , 35     , 36     , 37 , 38 , 39     , 40     , 41     , NO_LED , 27     },
	{ 43 , 44     , 45 , 46     , 47     , 48 , 49     , 50     , 51     , 52 , 53 , 54     , NO_LED , 55     , 42     , 56     },
	{ 57 , NO_LED , 58 , 59     , 60     , 61 , 62     , 63     , 64     , 65 , 66 , 67     , NO_LED , 68     , 69     , NO_LED },
	{ 70 , 71     , 72 , NO_LED , NO_LED , 73 , NO_LED , NO_LED , NO_LED , 74 , 75 , NO_LED , 76     , 77     , 78     , 79     }
},{
    // "Fine-tuned" complex configuration
    {7, 10},           {37, 10}, {52, 10}, {67, 10}, {82, 10}, {97, 10}, {112, 10}, {127, 10}, {142, 10}, {157, 10}, {156, 10}, {172, 10}, {187, 10},
    {7, 20}, {22, 20}, {37, 20}, {52, 20}, {67, 20}, {82, 20}, {97, 20}, {112, 20}, {127, 20}, {142, 20}, {157, 20}, {156, 20}, {172, 20}, {187, 20}, {202, 20},
    {7, 30}, {22, 30}, {37, 30}, {52, 30}, {67, 30}, {82, 30}, {97, 30}, {112, 30}, {127, 30}, {142, 30}, {157, 30}, {156, 30}, {172, 30}, {187, 30}, {202, 30},
    {7, 40}, {22, 40}, {37, 40}, {52, 40}, {67, 40}, {82, 40}, {97, 40}, {112, 40}, {127, 40}, {142, 40}, {157, 40}, {156, 40},            {187, 40}, {202, 40},
    {7, 50},           {37, 50}, {52, 50}, {67, 50}, {82, 50}, {97, 50}, {112, 50}, {127, 50}, {142, 50}, {157, 50}, {156, 50}, {172, 50}, {187, 50},
    {7, 60}, {22, 60}, {37, 60},                     {82, 60},                                 {142, 60}, {157, 60}, {156, 60}, {172, 60}, {187, 60}, {202, 60}
}, {
    1,      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,  1,
    1,      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,          1,              1,  1,  1,  1,  1,  1
} };

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(LED_CAP_INDEX, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    }
    return false;
}
#endif

void keyboard_post_init_user(void) {
  // Call the post init code.
    gpio_set_pin_output(A3);
    gpio_write_pin_high(A3);

    gpio_set_pin_output(D0);
    gpio_write_pin_high(D0);
}

void matrix_io_delay(void) {
}

void matrix_output_select_delay(void) {
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
}
