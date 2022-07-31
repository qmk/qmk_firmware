/* Copyright 2021 Team Mechlovin
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

#include "rev3.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
    {0, CS3_SW5, CS2_SW5, CS1_SW5}, /* D9-K31-00 */
    {0, CS6_SW5, CS5_SW5, CS4_SW5}, /* D46-K00-01 */
    {0, CS6_SW9, CS5_SW9, CS4_SW9}, /* D59-K01-02 */
    {0, CS9_SW5, CS8_SW5, CS7_SW5}, /* D73-K02-03 */
    {0, CS9_SW9, CS8_SW9, CS7_SW9}, /* D75-K03-04 */
    {0, CS12_SW5, CS11_SW5, CS10_SW5}, /* D77-K04-05 */
    {0, CS12_SW9, CS11_SW9, CS10_SW9}, /* D79-K05-06 */
    {0, CS15_SW5, CS14_SW5, CS13_SW5}, /* D81-K06-07 */
    {0, CS15_SW9, CS14_SW9, CS13_SW9}, /* D83-K07-08 */
    {0, CS18_SW5, CS17_SW5, CS16_SW5}, /* D85-K08-09 */
    {0, CS18_SW9, CS17_SW9, CS16_SW9}, /* D87-K09-10 */
    {0, CS21_SW5, CS20_SW5, CS19_SW5}, /* D90-K0A-11 */
    {0, CS21_SW9, CS20_SW9, CS19_SW9}, /* D93-K0B-12 */
    {0, CS24_SW5, CS23_SW5, CS22_SW5}, /* D95-K0C-13 */
    {0, CS24_SW9, CS23_SW9, CS22_SW9}, /* D98-K0D-14 */
    {0, CS24_SW3, CS23_SW3, CS22_SW3}, /* D100-K0E-15 */
    {0, CS3_SW4, CS2_SW4, CS1_SW4}, /* D94-K41-16 */
    {0, CS6_SW4, CS5_SW4, CS4_SW4}, /* D92-K10-17 */
    {0, CS6_SW6, CS5_SW6, CS4_SW6}, /* D89-K11-18 */
    {0, CS9_SW4, CS8_SW4, CS7_SW4}, /* D86-K12-19 */
    {0, CS9_SW6, CS8_SW6, CS7_SW6}, /* D84-K13-20 */
    {0, CS12_SW4, CS11_SW4, CS10_SW4}, /* D82-K14-21 */
    {0, CS12_SW6, CS11_SW6, CS10_SW6}, /* D80-K15-22 */
    {0, CS15_SW4, CS14_SW4, CS13_SW4}, /* D78-K16-23 */
    {0, CS15_SW6, CS14_SW6, CS13_SW6}, /* D76-K17-24 */
    {0, CS18_SW4, CS17_SW4, CS16_SW4}, /* D74-K18-25 */
    {0, CS18_SW6, CS17_SW6, CS16_SW6}, /* D72-K19-26 */
    {0, CS21_SW4, CS20_SW4, CS19_SW4}, /* D51-K1A-27 */
    {0, CS21_SW6, CS20_SW6, CS19_SW6}, /* D10-K1B-28 */
    {0, CS24_SW4, CS23_SW4, CS22_SW4}, /* D101-K1C-29 */
    {0, CS24_SW6, CS23_SW6, CS22_SW6}, /* D104-K1D-30 */
    {0, CS3_SW3, CS2_SW3, CS1_SW3}, /* D108-K43-31 */
    {0, CS6_SW3, CS5_SW3, CS4_SW3}, /* D111-K20-32 */
    {0, CS6_SW7, CS5_SW7, CS4_SW7}, /* D114-K21-33 */
    {0, CS9_SW3, CS8_SW3, CS7_SW3}, /* D117-K22-34 */
    {0, CS9_SW7, CS8_SW7, CS7_SW7}, /* D120-K23-35 */
    {0, CS12_SW3, CS11_SW3, CS10_SW3}, /* D123-K24-36 */
    {0, CS12_SW7, CS11_SW7, CS10_SW7}, /* D126-K25-37 */
    {0, CS15_SW3, CS14_SW3, CS13_SW3}, /* D129-K26-38 */
    {0, CS15_SW7, CS14_SW7, CS13_SW7}, /* D133-K27-39 */
    {0, CS18_SW3, CS17_SW3, CS16_SW3}, /* D142-K28-40 */
    {0, CS18_SW7, CS17_SW7, CS16_SW7}, /* D146-K29-41 */
    {0, CS21_SW3, CS20_SW3, CS19_SW3}, /* D160-K2A-42 */
    {0, CS21_SW7, CS20_SW7, CS19_SW7}, /* D167-K2B-43 */
    {0, CS24_SW7, CS23_SW7, CS22_SW7}, /* D168-K2D-44 */

    {0, CS6_SW2, CS5_SW2, CS4_SW2}, /* D163-K30-45 */
    {0, CS6_SW8, CS5_SW8, CS4_SW8}, /* D147-K31-46 */
    {0, CS9_SW2, CS8_SW2, CS7_SW2}, /* D144-K32-47 */
    {0, CS9_SW8, CS8_SW8, CS7_SW8}, /* D137-K33-48 */
    {0, CS12_SW2, CS11_SW2, CS10_SW2}, /* D130-K34-49 */
    {0, CS12_SW8, CS11_SW8, CS10_SW8}, /* D127-K35-50 */
    {0, CS15_SW2, CS14_SW2, CS13_SW2}, /* D124-K36-51 */
    {0, CS15_SW8, CS14_SW8, CS13_SW8}, /* D121-K37-52 */
    {0, CS18_SW2, CS17_SW2, CS16_SW2}, /* D118-K38-53 */
    {0, CS18_SW8, CS17_SW8, CS16_SW8}, /* D115-K39-54 */
    {0, CS21_SW2, CS20_SW2, CS19_SW2}, /* D112-K3A-55 */
    {0, CS21_SW8, CS20_SW8, CS19_SW8}, /* D109-K3B-56 */
    {0, CS24_SW2, CS23_SW2, CS22_SW2}, /* D105-K3D-57 */
    {0, CS24_SW8, CS23_SW8, CS22_SW8}, /* D103-K3E-58 */
    
    {0, CS3_SW1, CS2_SW1, CS1_SW1}, /* D163-K40-59 */
    {0, CS6_SW1, CS5_SW1, CS4_SW1}, /* D147-K42-60 */
    {0, CS9_SW1, CS8_SW1, CS7_SW1}, /* D137-K44-61 */
    {0, CS12_SW1, CS11_SW1, CS10_SW1}, /* D127-K46-62 */
    {0, CS15_SW1, CS14_SW1, CS13_SW1}, /* D121-K48-63 */
    {0, CS18_SW1, CS17_SW1, CS16_SW1}, /* D115-K4A-64 */
    {0, CS24_SW1, CS23_SW1, CS22_SW1}, /* D103-K4E-65 */
};

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 1,           2,         3,          4,           5,           6,         7,          8,          9,          10,        11,           12,           13,          14,         15},
        {17,          18,        19,         20,          21,          22,        23,         24,         25,          26,        27,           28,           29,          30,      NO_LED},
        {32,          33,        34,         35,          36,          37,        38,         39,         40,          41,        42,           43,       NO_LED,          44,      NO_LED},
        {45,        NO_LED,      46,         47,          48,          49,        50,         51,         52,          53,        54,           55,           56,          57,          58},
        {59,        NO_LED,      60,     NO_LED,          61,      NO_LED,        62,     NO_LED,         63,      NO_LED,        64,       NO_LED,       NO_LED,      NO_LED,          65},
    }, {
        //LED Index to Physical Positon
        {0,0},      { 17,  0},  { 34, 0 },  { 51, 0 },  { 69, 0},   { 86, 0},   {100, 0},   {103, 0},   { 120, 0},  { 138, 0},  { 155, 0},  { 172, 0},  { 189, 0},    {207,  0},   {215,  0},   {224, 0},
        {0,16},     { 17, 16},  { 34,16 },  { 51,16 },  { 69,16},   { 86,16},   {103,16},               { 120,16},  { 138,16},  { 155,16},  { 172,16},  { 189,16},    {207, 16},   {215, 16},   {224,16},
        {0,32},     { 17, 32},  { 34,32 },  { 51,32 },  { 69,32},   { 86,32},   {103,32},   { 120,32},  { 138,32},  { 155,32},  { 172,32},  { 189,32},  {207, 32},    {224,32},
                    { 17, 48},  { 34,48 },  { 51,48 },  { 69,48},   { 86,48},   {103,48},   { 120,48},  { 138,48},  { 155,48},  { 172,48},  { 189,48},  {207, 48},    {215, 48},   {224,48},   
                    { 17, 64},              { 51,64 },              { 86,64},   { 103,64},              { 138,64},              { 172,64},              {224, 64},      
    }, {
        1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
        1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
        1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,                         1,           1,  
        1,                      1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
        1,                      1,                      1,                      1,                      1,                      1,          1,            1, 
    } 
};

__attribute__((weak)) void rgb_matrix_indicators_user(void) {
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(32, 255, 255, 255);
        }
}


#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
    #ifdef RGBLIGHT_ENABLE
        #ifdef RGB_MATRIX_ENABLE
        case KC_F13: // toggle rgb matrix
            rgb_matrix_toggle();
            return false;
        case KC_F14:
            rgb_matrix_step();
            return false;
        case KC_F15:
            rgb_matrix_increase_speed();
            return false;
        case KC_F16:
            rgb_matrix_decrease_speed();
            return false;
        case KC_F17:
            rgb_matrix_increase_hue();
            return false;
        case KC_F18:
            rgb_matrix_decrease_hue();
            return false;
        case KC_F19:
            rgb_matrix_increase_sat();
            return false;
        case KC_F20:
            rgb_matrix_decrease_sat();
            return false;
        case KC_F21:
            rgb_matrix_increase_val();
            return false;
        case KC_F22:
            rgb_matrix_decrease_val();
            return false;
        #endif
    #endif
        default:
        break;
    }
  }
  return true;
}