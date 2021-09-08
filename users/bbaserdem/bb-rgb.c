/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "bb-rgb.h"
#define SPLIT_POINT 112
/* Code relating to per-key RGB LED stuff
 */

// Allow hooking into the RGB matrix indications using keymap code
__attribute__ ((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return false;
}
// Set RGB state depending on layer
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Load keymap hooks
    if(rgb_matrix_indicators_advanced_keymap(led_min, led_max)) {
        return;
    }
    // Do each layer seperately
    switch (get_highest_layer(layer_state)) {
        case _GAME: // Set left side as turquoise
            for(uint8_t i = led_min; i <= led_max; i++) {
                if(g_led_config.point[i].x < SPLIT_POINT) {
                    rgb_matrix_set_color(i, RGB_PURPLE);
                }
            }
            break;
        case _CHAR: // Set full board as chartreuse
            rgb_matrix_set_color_all(RGB_GOLD);
            break;
        case _MEDI: // Set right side as coral
            for(uint8_t i = led_min; i <= led_max; i++) {
                if(g_led_config.point[i].x > SPLIT_POINT) {
                    rgb_matrix_set_color(i, RGB_PINK);
                }
            }
            break;
        case _NAVI: // Set right side as green
            for(uint8_t i = led_min; i <= led_max; i++) {
                if(g_led_config.point[i].x > SPLIT_POINT) {
                    rgb_matrix_set_color(i, RGB_GREEN);
                }
            }
            break;
        case _SYMB: // Set right side as purple
            for(uint8_t i = led_min; i <= led_max; i++) {
                if(g_led_config.point[i].x > SPLIT_POINT) {
                    rgb_matrix_set_color(i, RGB_YELLOW);
                }
            }
            break;
        case _NUMB: // Set left side as cyan
            for(uint8_t i = led_min; i <= led_max; i++) {
                if(g_led_config.point[i].x < SPLIT_POINT) {
                    rgb_matrix_set_color(i, RGB_CYAN);
                }
            }
            break;
        case _FUNC: // Set left side as red
            for(uint8_t i = led_min; i <= led_max; i++) {
                if(g_led_config.point[i].x < SPLIT_POINT) {
                    rgb_matrix_set_color(i, RGB_RED);
                }
            }
            break;
        case _MOUS: // Set left side as yellow
            for(uint8_t i = led_min; i <= led_max; i++) {
                if(g_led_config.point[i].x < SPLIT_POINT) {
                    rgb_matrix_set_color(i, RGB_SPRINGGREEN);
                }
            }
            break;
        case _MUSI: // Set full board as magenta
            rgb_matrix_set_color_all(RGB_ORANGE);
            break;
    }
}

// Hook into shutdown code to make all perkey LED's red on hitting reset
void shutdown_keylight(void) {
    // Flash all the key LED's red on shutdown
    uint16_t timer_start = timer_read();
    rgb_matrix_set_color_all(RGB_CORAL);
    // Delay until this registers
    while(timer_elapsed(timer_start) < 250) {wait_ms(1);}
}

// Hook into suspend code
void suspend_power_down_keylight(void) {
    rgb_matrix_set_suspend_state(true);
}
void suspend_wakeup_init_keylight(void) {
    rgb_matrix_set_suspend_state(false);
}
