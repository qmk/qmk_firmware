/* Copyright 2021 kb-elmo<mail@elmo.space>
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
const is31fl3741_led_t g_is31fl3741_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS3_SW1,  CS2_SW1,  CS1_SW1},  /* RGB0-ESC ROW0*/
    {0, CS6_SW1,  CS5_SW1,  CS4_SW1},  /* RGB1-1 */
    {0, CS9_SW1,  CS8_SW1,  CS7_SW1},  /* RGB2-2 */
    {0, CS12_SW1,  CS11_SW1,  CS10_SW1},  /* RGB3-3 */
    {0, CS15_SW1,  CS14_SW1,  CS13_SW1},  /* RGB4-4 */
    {0, CS18_SW1,  CS17_SW1,  CS16_SW1},  /* RGB5-5 */
    {0, CS21_SW1,  CS20_SW1,  CS19_SW1},  /* RGB6-6 */
    {0, CS24_SW1,  CS23_SW1,  CS22_SW1},  /* RGB7-7 */
    {0, CS27_SW1,  CS26_SW1,  CS25_SW1},  /* RGB8-8 */
    {0, CS30_SW1,  CS29_SW1,  CS28_SW1},  /* RGB9-9 */
    {0, CS33_SW1,  CS32_SW1,  CS31_SW1},  /* RGB10-0 */
    {0, CS36_SW1,  CS35_SW1,  CS34_SW1},  /* RGB11--- */
    {0, CS39_SW1,  CS38_SW1,  CS37_SW1},  /* RGB12-+= */
    {0, CS36_SW6,  CS35_SW6,  CS34_SW6},  /* RGB13-BS */
    {0, CS27_SW7,  CS26_SW7,  CS25_SW7},  /* RGB14-DEL */
    {0, CS3_SW2,  CS2_SW2,  CS1_SW2},  /* RGB15-TAB ----ROW1*/
    {0, CS6_SW2,  CS5_SW2,  CS4_SW2}, /* RGB16-Q */
    {0, CS9_SW2,  CS8_SW2,  CS7_SW2}, /* RGB17-W */
    {0, CS12_SW2,  CS11_SW2,  CS10_SW2}, /* RGB18-E */
    {0, CS15_SW2,  CS14_SW2,  CS13_SW2}, /* RGB19-R */
    {0, CS18_SW2,  CS17_SW2,  CS16_SW2}, /* RGB20-T */
    {0, CS21_SW2,  CS20_SW2,  CS19_SW2}, /* RGB21-Y */
    {0, CS24_SW2,  CS23_SW2,  CS22_SW2}, /* RGB22-U */
    {0, CS27_SW2,  CS26_SW2,  CS25_SW2}, /* RGB23-I */
    {0, CS30_SW2,  CS29_SW2,  CS28_SW2}, /* RGB24-O */
    {0, CS33_SW2,  CS32_SW2,  CS31_SW2}, /* RGB25-P */
    {0, CS36_SW2,  CS35_SW2,  CS34_SW2}, /* RGB26-[ */
    {0, CS39_SW2,  CS38_SW2,  CS37_SW2}, /* RGB27-] */
    {0, CS39_SW6,  CS38_SW6,  CS37_SW6}, /* RGB28-\ */
    {0, CS30_SW7,  CS29_SW7,  CS28_SW7},  /* RGB29-PGUP */
    {0, CS3_SW3,  CS2_SW3,  CS1_SW3},  /* RGB30-CAPS---ROW2*/
    {0, CS6_SW3,  CS5_SW3,  CS4_SW3},  /* RGB31-A-- */
    {0, CS9_SW3,  CS8_SW3,  CS7_SW3},  /* RGB32-S-- */
    {0, CS12_SW3,  CS11_SW3,  CS10_SW3},  /* RGB33-D-- */
    {0, CS15_SW3,  CS14_SW3,  CS13_SW3},  /* RGB34-F-- */
    {0, CS18_SW3,  CS17_SW3,  CS16_SW3},  /* RGB35-G-- */
    {0, CS21_SW3,  CS20_SW3,  CS19_SW3},  /* RGB36-H-- */
    {0, CS24_SW3,  CS23_SW3,  CS22_SW3},  /* RGB37-J-- */
    {0, CS27_SW3,  CS26_SW3,  CS25_SW3},  /* RGB38-K-- */
    {0, CS30_SW3,  CS29_SW3,  CS28_SW3},  /* RGB39-L-- */
    {0, CS33_SW3,  CS32_SW3,  CS31_SW3},  /* RGB40-;:- */
    {0, CS36_SW3,  CS35_SW3,  CS34_SW3},  /* RGB41-''- */
    {0, CS39_SW3,  CS38_SW3,  CS37_SW3},  /* RGB42-ENTER- */
    {0, CS33_SW7,  CS32_SW7,  CS31_SW7},  /* RGB43-PGDN */
    {0, CS3_SW4,  CS2_SW4,  CS1_SW4},  /* RGB44-LSF --ROW3*/
    {0, CS6_SW4,  CS5_SW4,  CS4_SW4},  /* RGB45-Z -*/
    {0, CS9_SW4,  CS8_SW4,  CS7_SW4},  /* RGB46-X -*/
    {0, CS12_SW4,  CS11_SW4,  CS10_SW4},  /* RGB47-C -*/
    {0, CS15_SW4,  CS14_SW4,  CS13_SW4},  /* RGB48-V -*/
    {0, CS18_SW4,  CS17_SW4,  CS16_SW4},  /* RGB49-B -*/
    {0, CS21_SW4,  CS20_SW4,  CS19_SW4},  /* RGB50-N -*/
    {0, CS24_SW4,  CS23_SW4,  CS22_SW4},  /* RGB51-M -*/
    {0, CS27_SW4,  CS26_SW4,  CS25_SW4},  /* RGB52-,< -*/
    {0, CS30_SW4,  CS29_SW4,  CS28_SW4},  /* RGB53->. -*/
    {0, CS33_SW4,  CS32_SW4,  CS31_SW4},  /* RGB54-? -*/
    {0, CS36_SW4,  CS35_SW4,  CS34_SW4},  /* RGB55-RSF -*/
    {0, CS39_SW4,  CS38_SW4,  CS37_SW4},  /* RGB56-UP -*/
    {0, CS36_SW7, CS35_SW7, CS34_SW7}, /* RGB57--MO-- */
    {0, CS3_SW5, CS2_SW5, CS1_SW5}, /* RGB58-lct-- row4*/
    {0, CS6_SW5, CS5_SW5, CS4_SW5}, /* RGB59-lwin- */
    {0, CS9_SW5, CS8_SW5, CS7_SW5}, /* RGB60-lalt- */
    {0, CS18_SW5, CS17_SW5, CS16_SW5}, /* RGB61-sp- */
    {0, CS30_SW5, CS29_SW5, CS28_SW5}, /* RGB62-ralt- */
    {0, CS33_SW5, CS32_SW5, CS31_SW5}, /* RGB63-rct- */
    {0, CS36_SW5, CS35_SW5, CS34_SW5}, /* RGB64-left- */
    {0, CS39_SW5, CS38_SW5, CS37_SW5}, /* RGB65-dn- */
    {0, CS39_SW7, CS38_SW7, CS37_SW7}, /* RGB66-right- */
};

led_config_t g_led_config = { {
    { 0,  1,  2,  3,      4,      5,  6,      7,      8,      9,  10, 11, 12,     13,     14 },
    { 15, 16, 17, 18,     19,     20, 21,     22,     23,     24, 25, 26, 27,     28,     29 },
    { 30, 31, 32, 33,     34,     35, 36,     37,     38,     39, 40, 41, 42,     NO_LED, 43 },
    { 44, 45, 46, 47,     48,     49, 50,     51,     52,     53, 54, 55, NO_LED, 56,     57 },
    { 58, 59, 60, NO_LED, NO_LED, 61, NO_LED, NO_LED, NO_LED, 62, 63, 64, NO_LED, 65,     66 }
}, {
    { 0, 0 },  { 16, 0 },  { 32, 0 },  { 48, 0 },  { 64, 0 },  { 80, 0 },  { 96,  0 },  { 112, 0 },  { 128, 0 },  { 144, 0 },  { 160, 0 },  { 176, 0 },  { 192, 0 },  { 208, 0 },  { 224, 0 },
    { 2, 16 }, { 18, 16 }, { 34, 16 }, { 50, 16 }, { 66, 16 }, { 82, 16 }, { 98,  16 }, { 114, 16 }, { 130, 16 }, { 146, 16 }, { 162, 16 }, { 178, 16 }, { 194, 16 }, { 210, 16 }, { 224, 16 },
    { 4, 32 }, { 20, 32 }, { 36, 32 }, { 52, 32 }, { 68, 32 }, { 84, 32 }, { 100, 32 }, { 116, 32 }, { 132, 32 }, { 148, 32 }, { 164, 32 }, { 180, 32 }, { 196, 32 }, { 224, 32 },
    { 8, 48 }, { 24, 48 }, { 40, 48 }, { 56, 48 }, { 72, 48 }, { 88, 48 }, { 104, 48 }, { 120, 48 }, { 136, 48 }, { 152, 48 }, { 168, 48 }, { 184, 48 },              { 208, 48 }, { 224, 48 },
    { 2, 64 }, { 18, 64 }, { 34, 64 },                         { 82, 64 },                                        { 146, 64 }, { 162, 64 }, { 178, 64 },              { 210, 64 }, { 224, 64 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1, 1,
    1, 1, 1,       1,          1, 1, 1,    1, 1,
    }
};


#endif

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(31, 255, 255, 255);
    } else {
        rgb_matrix_set_color(31, 0, 0, 0);
    }
    return true;
}
