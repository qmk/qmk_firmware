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
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
    {0, SW1_CS3,  SW1_CS2,  SW1_CS1},  /* RGB0-ESC ROW0*/
    {0, SW1_CS6,  SW1_CS5,  SW1_CS4},  /* RGB1-1 */
    {0, SW1_CS9,  SW1_CS8,  SW1_CS7},  /* RGB2-2 */
    {0, SW1_CS12,  SW1_CS11,  SW1_CS10},  /* RGB3-3 */
    {0, SW1_CS15,  SW1_CS14,  SW1_CS13},  /* RGB4-4 */
    {0, SW1_CS18,  SW1_CS17,  SW1_CS16},  /* RGB5-5 */
    {0, SW1_CS21,  SW1_CS20,  SW1_CS19},  /* RGB6-6 */
    {0, SW1_CS24,  SW1_CS23,  SW1_CS22},  /* RGB7-7 */
    {0, SW1_CS27,  SW1_CS26,  SW1_CS25},  /* RGB8-8 */
    {0, SW1_CS30,  SW1_CS29,  SW1_CS28},  /* RGB9-9 */
    {0, SW1_CS33,  SW1_CS32,  SW1_CS31},  /* RGB10-0 */
    {0, SW1_CS36,  SW1_CS35,  SW1_CS34},  /* RGB11--- */
    {0, SW1_CS39,  SW1_CS38,  SW1_CS37},  /* RGB12-+= */
    {0, SW6_CS36,  SW6_CS35,  SW6_CS34},  /* RGB13-BS */
    {0, SW7_CS27,  SW7_CS26,  SW7_CS25},  /* RGB14-DEL */
    {0, SW2_CS3,  SW2_CS2,  SW2_CS1},  /* RGB15-TAB ----ROW1*/
    {0, SW2_CS6,  SW2_CS5,  SW2_CS4}, /* RGB16-Q */
    {0, SW2_CS9,  SW2_CS8,  SW2_CS7}, /* RGB17-W */
    {0, SW2_CS12,  SW2_CS11,  SW2_CS10}, /* RGB18-E */
    {0, SW2_CS15,  SW2_CS14,  SW2_CS13}, /* RGB19-R */
    {0, SW2_CS18,  SW2_CS17,  SW2_CS16}, /* RGB20-T */
    {0, SW2_CS21,  SW2_CS20,  SW2_CS19}, /* RGB21-Y */
    {0, SW2_CS24,  SW2_CS23,  SW2_CS22}, /* RGB22-U */
    {0, SW2_CS27,  SW2_CS26,  SW2_CS25}, /* RGB23-I */
    {0, SW2_CS30,  SW2_CS29,  SW2_CS28}, /* RGB24-O */
    {0, SW2_CS33,  SW2_CS32,  SW2_CS31}, /* RGB25-P */
    {0, SW2_CS36,  SW2_CS35,  SW2_CS34}, /* RGB26-[ */
    {0, SW2_CS39,  SW2_CS38,  SW2_CS37}, /* RGB27-] */
    {0, SW6_CS39,  SW6_CS38,  SW6_CS37}, /* RGB28-\ */
    {0, SW7_CS30,  SW7_CS29,  SW7_CS28},  /* RGB29-PGUP */
    {0, SW3_CS3,  SW3_CS2,  SW3_CS1},  /* RGB30-CAPS---ROW2*/
    {0, SW3_CS6,  SW3_CS5,  SW3_CS4},  /* RGB31-A-- */
    {0, SW3_CS9,  SW3_CS8,  SW3_CS7},  /* RGB32-S-- */
    {0, SW3_CS12,  SW3_CS11,  SW3_CS10},  /* RGB33-D-- */
    {0, SW3_CS15,  SW3_CS14,  SW3_CS13},  /* RGB34-F-- */
    {0, SW3_CS18,  SW3_CS17,  SW3_CS16},  /* RGB35-G-- */
    {0, SW3_CS21,  SW3_CS20,  SW3_CS19},  /* RGB36-H-- */
    {0, SW3_CS24,  SW3_CS23,  SW3_CS22},  /* RGB37-J-- */
    {0, SW3_CS27,  SW3_CS26,  SW3_CS25},  /* RGB38-K-- */
    {0, SW3_CS30,  SW3_CS29,  SW3_CS28},  /* RGB39-L-- */
    {0, SW3_CS33,  SW3_CS32,  SW3_CS31},  /* RGB40-;:- */
    {0, SW3_CS36,  SW3_CS35,  SW3_CS34},  /* RGB41-''- */
    {0, SW3_CS39,  SW3_CS38,  SW3_CS37},  /* RGB42-ENTER- */
    {0, SW7_CS33,  SW7_CS32,  SW7_CS31},  /* RGB43-PGDN */
    {0, SW4_CS3,  SW4_CS2,  SW4_CS1},  /* RGB44-LSF --ROW3*/
    {0, SW4_CS6,  SW4_CS5,  SW4_CS4},  /* RGB45-Z -*/
    {0, SW4_CS9,  SW4_CS8,  SW4_CS7},  /* RGB46-X -*/
    {0, SW4_CS12,  SW4_CS11,  SW4_CS10},  /* RGB47-C -*/
    {0, SW4_CS15,  SW4_CS14,  SW4_CS13},  /* RGB48-V -*/
    {0, SW4_CS18,  SW4_CS17,  SW4_CS16},  /* RGB49-B -*/
    {0, SW4_CS21,  SW4_CS20,  SW4_CS19},  /* RGB50-N -*/
    {0, SW4_CS24,  SW4_CS23,  SW4_CS22},  /* RGB51-M -*/
    {0, SW4_CS27,  SW4_CS26,  SW4_CS25},  /* RGB52-,< -*/
    {0, SW4_CS30,  SW4_CS29,  SW4_CS28},  /* RGB53->. -*/
    {0, SW4_CS33,  SW4_CS32,  SW4_CS31},  /* RGB54-? -*/
    {0, SW4_CS36,  SW4_CS35,  SW4_CS34},  /* RGB55-RSF -*/
    {0, SW4_CS39,  SW4_CS38,  SW4_CS37},  /* RGB56-UP -*/
    {0, SW7_CS36, SW7_CS35, SW7_CS34}, /* RGB57--MO-- */
    {0, SW5_CS3, SW5_CS2, SW5_CS1}, /* RGB58-lct-- row4*/
    {0, SW5_CS6, SW5_CS5, SW5_CS4}, /* RGB59-lwin- */
    {0, SW5_CS9, SW5_CS8, SW5_CS7}, /* RGB60-lalt- */
    {0, SW5_CS18, SW5_CS17, SW5_CS16}, /* RGB61-sp- */
    {0, SW5_CS30, SW5_CS29, SW5_CS28}, /* RGB62-ralt- */
    {0, SW5_CS33, SW5_CS32, SW5_CS31}, /* RGB63-rct- */
    {0, SW5_CS36, SW5_CS35, SW5_CS34}, /* RGB64-left- */
    {0, SW5_CS39, SW5_CS38, SW5_CS37}, /* RGB65-dn- */
    {0, SW7_CS39, SW7_CS38, SW7_CS37}, /* RGB66-right- */
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
