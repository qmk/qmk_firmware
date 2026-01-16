/*
Copyright 2022 Terry Mathews

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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
    {0, SW1_CS18, SW1_CS17, SW1_CS16}, /* RGB1 */
    {0, SW2_CS18, SW2_CS17, SW2_CS16}, /* RGB2 */
    {0, SW3_CS18, SW3_CS17, SW3_CS16}, /* RGB3 */
    {0, SW4_CS18, SW4_CS17, SW4_CS16}, /* RGB4 */
    {0, SW5_CS18, SW5_CS17, SW5_CS16}, /* RGB5 */
    {0, SW6_CS18, SW6_CS17, SW6_CS16}, /* RGB6 */
    {0, SW7_CS18, SW7_CS17, SW7_CS16}, /* RGB7 */
    {0, SW8_CS18, SW8_CS17, SW8_CS16}, /* RGB8 */
    {0, SW9_CS18, SW9_CS17, SW9_CS16}, /* RGB9 */
    {0, SW1_CS21, SW1_CS20, SW1_CS19}, /* RGB10 */
    {0, SW2_CS21, SW2_CS20, SW2_CS19}, /* RGB11 */
    {0, SW3_CS21, SW3_CS20, SW3_CS19}, /* RGB12 */
    {0, SW4_CS21, SW4_CS20, SW4_CS19}, /* RGB13 */
    {0, SW5_CS21, SW5_CS20, SW5_CS19}, /* RGB14 */
    {0, SW6_CS21, SW6_CS20, SW6_CS19}, /* RGB15 */
    {0, SW1_CS15, SW1_CS14, SW1_CS13}, /* RGB16 */
    {0, SW2_CS15, SW2_CS14, SW2_CS13}, /* RGB17 */
    {0, SW3_CS15, SW3_CS14, SW3_CS13}, /* RGB18 */
    {0, SW4_CS15, SW4_CS14, SW4_CS13}, /* RGB19 */
    {0, SW5_CS15, SW5_CS14, SW5_CS13}, /* RGB20 */
    {0, SW6_CS15, SW6_CS14, SW6_CS13}, /* RGB21 */
    {0, SW7_CS15, SW7_CS14, SW7_CS13}, /* RGB22 */
    {0, SW8_CS15, SW8_CS14, SW8_CS13}, /* RGB23 */
    {0, SW9_CS15, SW9_CS14, SW9_CS13}, /* RGB24 */
    {0, SW1_CS24, SW1_CS23, SW1_CS22}, /* RGB25 */
    {0, SW2_CS24, SW2_CS23, SW2_CS22}, /* RGB26 */
    {0, SW3_CS24, SW3_CS23, SW3_CS22}, /* RGB27 */
    {0, SW4_CS24, SW4_CS23, SW4_CS22}, /* RGB28 */
    {0, SW5_CS24, SW5_CS23, SW5_CS22}, /* RGB29 */
    {0, SW6_CS24, SW6_CS23, SW6_CS22}, /* RGB30 */
    {0, SW1_CS12, SW1_CS11, SW1_CS10}, /* RGB31 */
    {0, SW2_CS12, SW2_CS11, SW2_CS10}, /* RGB32 */
    {0, SW3_CS12, SW3_CS11, SW3_CS10}, /* RGB33 */
    {0, SW4_CS12, SW4_CS11, SW4_CS10}, /* RGB34 */
    {0, SW5_CS12, SW5_CS11, SW5_CS10}, /* RGB35 */
    {0, SW6_CS12, SW6_CS11, SW6_CS10}, /* RGB36 */
    {0, SW7_CS12, SW7_CS11, SW7_CS10}, /* RGB37 */
    {0, SW8_CS12, SW8_CS11, SW8_CS10}, /* RGB38 */
    {0, SW9_CS12, SW9_CS11, SW9_CS10}, /* RGB39 */
    {0, SW1_CS27, SW1_CS26, SW1_CS25}, /* RGB40 */
    {0, SW2_CS27, SW2_CS26, SW2_CS25}, /* RGB41 */
    {0, SW3_CS27, SW3_CS26, SW3_CS25}, /* RGB42 */
    {0, SW4_CS27, SW4_CS26, SW4_CS25}, /* RGB43 */
    {0, SW6_CS27, SW6_CS26, SW6_CS25}, /* RGB44 */
    {0, SW1_CS9, SW1_CS8, SW1_CS7}, /* RGB45 */
    {0, SW3_CS9, SW3_CS8, SW3_CS7}, /* RGB46 */
    {0, SW4_CS9, SW4_CS8, SW4_CS7}, /* RGB47 */
    {0, SW5_CS9, SW5_CS8, SW5_CS7}, /* RGB48 */
    {0, SW6_CS9, SW6_CS8, SW6_CS7}, /* RGB49 */
    {0, SW7_CS9, SW7_CS8, SW7_CS7}, /* RGB50 */
    {0, SW8_CS9, SW8_CS8, SW8_CS7}, /* RGB51 */
    {0, SW9_CS9, SW9_CS8, SW9_CS7}, /* RGB52 */
    {0, SW1_CS30, SW1_CS29, SW1_CS28}, /* RGB53 */
    {0, SW2_CS30, SW2_CS29, SW2_CS28}, /* RGB54 */
    {0, SW3_CS30, SW3_CS29, SW3_CS28}, /* RGB55 */
    {0, SW4_CS30, SW4_CS29, SW4_CS28}, /* RGB56 */
    {0, SW5_CS30, SW5_CS29, SW5_CS28}, /* RGB57 */
    {0, SW6_CS30, SW6_CS29, SW6_CS28}, /* RGB58 */
    {0, SW1_CS6, SW1_CS5, SW1_CS4}, /* RGB59 */
    {0, SW2_CS6, SW2_CS5, SW2_CS4}, /* RGB60 */
    {0, SW3_CS6, SW3_CS5, SW3_CS4}, /* RGB61 */
    {0, SW7_CS6, SW7_CS5, SW7_CS4}, /* RGB62 */
    {0, SW2_CS33, SW2_CS32, SW2_CS31}, /* RGB63 */
    {0, SW3_CS33, SW3_CS32, SW3_CS31}, /* RGB64 */
    {0, SW4_CS33, SW4_CS32, SW4_CS31}, /* RGB65 */
    {0, SW5_CS33, SW5_CS32, SW5_CS31}, /* RGB66 */
    {0, SW6_CS33, SW6_CS32, SW6_CS31}, /* RGB67 */

    {0,SW1_CS36,SW1_CS35,SW1_CS34}, /* RGB68 */
    {0,SW2_CS36,SW2_CS35,SW2_CS34}, /* RGB69 */
    {0,SW3_CS36,SW3_CS35,SW3_CS34}, /* RGB70 */
    {0,SW4_CS36,SW4_CS35,SW4_CS34}, /* RGB71 */
    {0,SW5_CS36,SW5_CS35,SW5_CS34}, /* RGB72 */
    {0,SW6_CS36,SW6_CS35,SW6_CS34}, /* RGB73 */
    {0,SW7_CS36,SW7_CS35,SW7_CS34}, /* RGB74 */
    {0,SW8_CS36,SW8_CS35,SW8_CS34}, /* RGB75 */
    {0,SW9_CS36,SW9_CS35,SW9_CS34}, /* RGB76 */
    {0,SW1_CS39,SW1_CS38,SW1_CS37}, /* RGB77 */
    {0,SW2_CS39,SW2_CS38,SW2_CS37}, /* RGB78 */
    {0,SW3_CS39,SW3_CS38,SW3_CS37}, /* RGB79 */
    {0,SW4_CS39,SW4_CS38,SW4_CS37}, /* RGB80 */
    {0,SW5_CS39,SW5_CS38,SW5_CS37}, /* RGB81 */
    {0,SW6_CS39,SW6_CS38,SW6_CS37}, /* RGB82 */
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
        }
    }
    else {
         if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    }
    return true;
}
#endif
