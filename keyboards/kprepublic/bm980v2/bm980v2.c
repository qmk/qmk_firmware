 /* Copyright 2022 bdtc123
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
#include "bm980v2.h"

#ifdef RGB_MATRIX_ENABLE

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
    {0, CS6_SW1, CS5_SW1, CS4_SW1},
    {0, CS6_SW3, CS5_SW3, CS4_SW3}, 
    {0, CS6_SW4, CS5_SW4, CS4_SW4},    
    {0, CS6_SW5, CS5_SW5, CS4_SW5},
    {0, CS6_SW6, CS5_SW6, CS4_SW6},
    {0, CS6_SW7, CS5_SW7, CS4_SW7}, 
    {0, CS6_SW8, CS5_SW8, CS4_SW8},
    {0, CS6_SW9, CS5_SW9, CS4_SW9},
    {0, CS21_SW1, CS20_SW1, CS19_SW1},
    {0, CS21_SW2, CS20_SW2, CS19_SW2},
    {0, CS21_SW3, CS20_SW3, CS19_SW3},
    {0, CS21_SW4, CS20_SW4, CS19_SW4},
    {0, CS21_SW5, CS20_SW5, CS19_SW5},
    {0, CS21_SW6, CS20_SW6, CS19_SW6},
    {0, CS21_SW7, CS20_SW7, CS19_SW7},
    {0, CS21_SW8, CS20_SW8, CS19_SW8},
    {0, CS21_SW9, CS20_SW9, CS19_SW9},

    
    {0, CS9_SW1, CS8_SW1, CS7_SW1},     
    {0, CS9_SW2, CS8_SW2, CS7_SW2},
    {0, CS9_SW3, CS8_SW3, CS7_SW3},
    {0, CS9_SW4, CS8_SW4, CS7_SW4},
    {0, CS9_SW5, CS8_SW5, CS7_SW5},
    {0, CS9_SW6, CS8_SW6, CS7_SW6},
    {0, CS9_SW7, CS8_SW7, CS7_SW7},
    {0, CS9_SW8, CS8_SW8, CS7_SW8},
    {0, CS9_SW9, CS8_SW9, CS7_SW9},
    {0,CS24_SW1, CS23_SW1, CS22_SW1}, 
    {0,CS24_SW2, CS23_SW2, CS22_SW2},
    {0,CS24_SW3, CS23_SW3, CS22_SW3},
    {0,CS24_SW4, CS23_SW4, CS22_SW4},
    {0,CS24_SW5, CS23_SW5, CS22_SW5},
    {0,CS24_SW6, CS23_SW6, CS22_SW6},
    {0,CS24_SW7, CS23_SW7, CS22_SW7},
    {0,CS24_SW8, CS23_SW8, CS22_SW8},
    {0,CS24_SW9, CS23_SW9, CS22_SW9},
    
    {0, CS12_SW1, CS11_SW1, CS10_SW1},     
    {0, CS12_SW2, CS11_SW2, CS10_SW2},  
    {0, CS12_SW3, CS11_SW3, CS10_SW3},      
    {0, CS12_SW4, CS11_SW4, CS10_SW4},      
    {0, CS12_SW5, CS11_SW5, CS10_SW5},      
    {0, CS12_SW6, CS11_SW6, CS10_SW6},      
    {0, CS12_SW7, CS11_SW7, CS10_SW7},  
    {0, CS12_SW8, CS11_SW8, CS10_SW8},
    {0, CS12_SW9, CS11_SW9, CS10_SW9},
    {0, CS27_SW1, CS26_SW1, CS25_SW1},      
    {0, CS27_SW2, CS26_SW2, CS25_SW2},     
    {0, CS27_SW3, CS26_SW3, CS25_SW3},     
    {0, CS27_SW4, CS26_SW4, CS25_SW4},
    {0, CS27_SW5, CS26_SW5, CS25_SW5},
    {0, CS27_SW6, CS26_SW6, CS25_SW6}, 
    {0, CS27_SW7, CS26_SW7, CS25_SW7},
    {0, CS27_SW8, CS26_SW8, CS25_SW8},
    {0, CS27_SW9, CS26_SW9, CS25_SW9},
    
    {0, CS15_SW1, CS14_SW1, CS13_SW1},
    {0, CS15_SW2, CS14_SW2, CS13_SW2},
    {0, CS15_SW3, CS14_SW3, CS13_SW3}, 
    {0, CS15_SW4, CS14_SW4, CS13_SW4},     
    {0, CS15_SW5, CS14_SW5, CS13_SW5},     
    {0, CS15_SW6, CS14_SW6, CS13_SW6},     
    {0, CS15_SW7, CS14_SW7, CS13_SW7},     
    {0, CS15_SW8, CS14_SW8, CS13_SW8},
    {0, CS15_SW9, CS14_SW9, CS13_SW9},
    {0, CS30_SW1, CS29_SW1, CS28_SW1},
    {0, CS30_SW2, CS29_SW2, CS28_SW2},
    {0, CS30_SW3, CS29_SW3, CS28_SW3},
    {0, CS30_SW4, CS29_SW4, CS28_SW4},
    {0, CS30_SW6, CS29_SW6, CS28_SW6},
    {0, CS30_SW7, CS29_SW7, CS28_SW7},
    {0, CS30_SW8, CS29_SW8, CS28_SW8},

    
    {0, CS18_SW1, CS17_SW1, CS16_SW1},
    {0, CS18_SW3, CS17_SW3, CS16_SW3}, 
    {0, CS18_SW4, CS17_SW4, CS16_SW4},     
    {0, CS18_SW5, CS17_SW5, CS16_SW5},     
    {0, CS18_SW6, CS17_SW6, CS16_SW6},     
    {0, CS18_SW7, CS17_SW7, CS16_SW7},     
    {0, CS18_SW8, CS17_SW8, CS16_SW8},
    {0, CS18_SW9, CS17_SW9, CS16_SW9},
    {0, CS33_SW1, CS32_SW1, CS31_SW1},
    {0, CS33_SW2, CS32_SW2, CS31_SW2},
    {0, CS33_SW3, CS32_SW3, CS31_SW3},
    {0, CS33_SW4, CS32_SW4, CS31_SW4},
    {0, CS33_SW5, CS32_SW5, CS31_SW5},
    {0, CS33_SW6, CS32_SW6, CS31_SW6},
    {0, CS33_SW7, CS32_SW7, CS31_SW7},
    {0, CS33_SW8, CS32_SW8, CS31_SW8},
    {0, CS33_SW9, CS32_SW9, CS31_SW9},

    {0, CS3_SW1, CS2_SW1, CS1_SW1},
    {0, CS3_SW2, CS2_SW2, CS1_SW2},
    {0, CS3_SW3, CS2_SW3, CS1_SW3}, 
    {0, CS3_SW6, CS2_SW6, CS1_SW6}, 
    {0, CS36_SW2, CS35_SW2, CS34_SW2},
    {0, CS36_SW3, CS35_SW3, CS34_SW3},
    {0, CS36_SW4, CS35_SW4, CS34_SW4},
    {0, CS36_SW5, CS35_SW5, CS34_SW5},
    {0, CS36_SW6, CS35_SW6, CS34_SW6},
    {0, CS36_SW7, CS35_SW7, CS34_SW7},
    {0, CS36_SW8, CS35_SW8, CS34_SW8},   
    {0, CS36_SW9, CS35_SW9, CS34_SW9}                                                                                                       
};
led_config_t g_led_config = { {
  {  0,     13,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 },
  { 17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30 },
  { 35,     36,     37,     38,     39,     40,     41,     42,     43,     44,     45,     46,     47,     48 },
  { 53,     54,     55,     56,     57,     58,     59,     60,     61,     62,     64,     64,     65,     66 },
  { 69,     82,     70,     71,     72,     73,     74,     75,     76,     77,     78,     79,     80,     81 },
  { 86,     87,     88,     94,     95,     89,     96,     84,     85,     97,     90,     91,     92,     93 },
  { 31,     49,     32,     83,     67,     50,     51,     68,     52,     34,     14,     15,     16,     33 }
}, {
    {   0,   0 },  {  15,   0 },  {  30,   0 },  {  45,   0 },  {  60,   0 },  {  75,   0 },  {  90,   0 },  { 105,   0 },  { 120,   0 },  { 135,   0 },  { 150,   0 },  { 165,   0 },  { 180,   0 }, { 195,   0 },  { 202,   0 },  { 212,   0 }, { 224,   0 },
    {   0,   20 }, {  15,   20 }, {  30,   20 }, {  45,   20 }, {  60,   20 }, {  75,   20 }, {  90,   20 }, { 105,   20 }, { 120,   20 }, { 135,   20 }, { 150,   20 }, { 165,   20 }, { 180,   20 },{ 195,   20 }, { 202,   20 }, { 212,   20 },{ 220,   20 },{ 224,   20 },
    {   8,   30 }, {  15,   30 }, {  30,   30 }, {  45,   30 }, {  60,   30 }, {  75,   30 }, {  90,   30 }, { 105,   30 }, { 120,   30 }, { 135,   30 }, { 150,   30 }, { 165,   30 }, { 180,   30 },{ 195,   30 }, { 202,   30 }, { 212,   30 },{ 220,   30 },{ 224,   30 },
    {   9,   40 }, {  15,   40 }, {  30,   40 }, {  45,   40 }, {  60,   40 }, {  75,   40 }, {  90,   40 }, { 105,   40 }, { 120,   40 }, { 135,   40 }, { 150,   40 }, { 165,   40 }, { 180,   40 },{ 195,   40 }, { 202,   40 }, { 212,   40 },
    {   12,  50 }, {  15,   50 }, {  30,   50 }, {  45,   50 }, {  60,   50 }, {  75,   50 }, {  90,   50 }, { 105,   50 }, { 120,   50 }, { 135,   50 }, { 150,   50 }, { 165,   50 }, { 180,   50 },{ 195,   50 }, { 202,   50 }, { 212,   50 },{ 224,   50 },
    {   2,   60 }, {  17,   60 }, {  34,   60 },  { 77,   60 }, { 120,   60 }, { 135,   60 }, {  150,  60 }, { 165,   60 }, { 177,   60 }, { 182,   60 }, { 197,   60 }, { 212,   60 }, 
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1,
} };

__attribute__ ((weak))
void rgb_matrix_indicators_user(void)
{
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(53, 0xFF, 0xFF, 0xFF);
    }
}
#endif

