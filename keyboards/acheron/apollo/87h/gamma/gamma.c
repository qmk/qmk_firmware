/*
 Copyright 2022 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |         G location
 *   |  |         |         B location
 *   |  |         |         | */
// First row
    {0, CS7_SW9 , CS9_SW9 , CS8_SW9  }, //ESC    0
    {0, CS7_SW8 , CS9_SW8 , CS8_SW8  }, //F1     1
    {0, CS7_SW7 , CS9_SW7 , CS8_SW7  }, //F2     2
    {0, CS7_SW6 , CS9_SW6 , CS8_SW6  }, //F3     3
    {0, CS7_SW5 , CS9_SW5 , CS8_SW5  }, //F4     4
    {0, CS7_SW4 , CS9_SW4 , CS8_SW4  }, //F5     5
    {0, CS7_SW3 , CS9_SW3 , CS8_SW3  }, //F6     6
    {0, CS7_SW2 , CS9_SW2 , CS8_SW2  }, //F7     7
    {0, CS7_SW1 , CS9_SW1 , CS8_SW1  }, //F8     8
    {0, CS18_SW2, CS16_SW2, CS17_SW2 }, //F9     9
    {0, CS18_SW3, CS16_SW3, CS17_SW3 }, //F10    10
    {0, CS18_SW4, CS16_SW4, CS17_SW4 }, //F11    11
    {0, CS18_SW6, CS16_SW6, CS17_SW6 }, //F12    12
    {0, CS18_SW7, CS16_SW7, CS17_SW7 }, //PRI    13
    {0, CS18_SW8, CS16_SW8, CS17_SW8 }, //SCR    14
    {0, CS18_SW9, CS16_SW9, CS17_SW9 }, //PAUS   15
//Second row
    {0, CS12_SW9, CS11_SW9, CS10_SW9 }, //GRAVE  16
    {0, CS12_SW8, CS11_SW8, CS10_SW8 }, //1      17
    {0, CS12_SW7, CS11_SW7, CS10_SW7 }, //2      18
    {0, CS12_SW6, CS11_SW6, CS10_SW6 }, //3      19
    {0, CS12_SW5, CS11_SW5, CS10_SW5 }, //4      20
    {0, CS12_SW4, CS11_SW4, CS10_SW4 }, //5      21
    {0, CS12_SW3, CS11_SW3, CS10_SW3 }, //6      22
    {0, CS12_SW2, CS11_SW2, CS10_SW2 }, //7      23
    {0, CS12_SW1, CS11_SW1, CS10_SW1 }, //8      24
    {0, CS15_SW1, CS13_SW1, CS14_SW1 }, //9      25
    {0, CS15_SW2, CS13_SW2, CS14_SW2 }, //0      26
    {0, CS15_SW3, CS13_SW3, CS14_SW3 }, //MINUS  27
    {0, CS15_SW4, CS13_SW4, CS14_SW4 }, //PLUS   28
    {0, CS15_SW5, CS13_SW5, CS14_SW5 }, //BKSP   29
    {0, CS15_SW7, CS13_SW7, CS14_SW7 }, //INS    30
    {0, CS15_SW8, CS13_SW8, CS14_SW8 }, //HOME   31
    {0, CS15_SW9, CS13_SW9, CS14_SW9 }, //PGUP   32
//Third row
    {0, CS4_SW9 , CS6_SW9 , CS5_SW9  }, //TAB    33
    {0, CS4_SW8 , CS6_SW8 , CS5_SW8  }, //Q      34
    {0, CS4_SW7 , CS6_SW7 , CS5_SW7  }, //W      35
    {0, CS4_SW6 , CS6_SW6 , CS5_SW6  }, //E      36
    {0, CS4_SW5 , CS6_SW5 , CS5_SW5  }, //R      37
    {0, CS4_SW4 , CS6_SW4 , CS5_SW4  }, //T      38
    {0, CS4_SW3 , CS6_SW3 , CS5_SW3  }, //Y      39
    {0, CS4_SW2 , CS6_SW2 , CS5_SW2  }, //U      40
    {0, CS4_SW1 , CS6_SW1 , CS5_SW1  }, //I      41
    {0, CS3_SW2 , CS1_SW2 , CS2_SW2  }, //O      42
    {0, CS3_SW3 , CS1_SW3 , CS2_SW3  }, //P      43
    {0, CS3_SW4 , CS1_SW4 , CS2_SW4  }, //LBRKT  44
    {0, CS3_SW5 , CS1_SW5 , CS2_SW5  }, //RBRKT  45
    {0, CS3_SW6 , CS1_SW6 , CS2_SW6  }, //BSLS   46
    {0, CS3_SW7 , CS1_SW7 , CS2_SW7  }, //DEL    47
    {0, CS3_SW8 , CS1_SW8 , CS2_SW8  }, //END    48
    {0, CS3_SW9 , CS1_SW9 , CS2_SW9  }, //PGDN   49
//Fourth row
    {0, CS33_SW9, CS32_SW9, CS31_SW9  }, //CAPS  50
    {0, CS33_SW8, CS32_SW8, CS31_SW8  }, //A     51
    {0, CS33_SW7, CS32_SW7, CS31_SW7  }, //S     52
    {0, CS33_SW6, CS32_SW6, CS31_SW6  }, //D     53
    {0, CS33_SW5, CS32_SW5, CS31_SW5  }, //F     54
    {0, CS33_SW4, CS32_SW4, CS31_SW4  }, //G     55
    {0, CS33_SW3, CS32_SW3, CS31_SW3  }, //H     56
    {0, CS33_SW2, CS32_SW2, CS31_SW2  }, //J     57
    {0, CS33_SW1, CS32_SW1, CS31_SW1  }, //K     58
    {0, CS39_SW2, CS38_SW2, CS37_SW2  }, //L     59
    {0, CS39_SW3, CS38_SW3, CS37_SW3  }, //COLON 60
    {0, CS39_SW4, CS38_SW4, CS37_SW4  }, //QUOTE 61
    {0, CS39_SW6, CS38_SW6, CS37_SW6  }, //ENTER 62
//Fifth row
    {0, CS30_SW9, CS28_SW9, CS29_SW9  }, //LSFT  63
    {0, CS30_SW7, CS28_SW7, CS29_SW7  }, //Z     64
    {0, CS30_SW6, CS28_SW6, CS29_SW6  }, //X     65
    {0, CS30_SW5, CS28_SW5, CS29_SW5  }, //C     66
    {0, CS30_SW4, CS28_SW4, CS29_SW4  }, //V     67
    {0, CS30_SW3, CS28_SW3, CS29_SW3  }, //B     68
    {0, CS30_SW2, CS28_SW2, CS29_SW2  }, //N     69
    {0, CS30_SW1, CS28_SW1, CS29_SW1  }, //M     70
    {0, CS36_SW1, CS35_SW1, CS34_SW1  }, //COMMA 71
    {0, CS36_SW3, CS35_SW3, CS34_SW3  }, //DOT   72
    {0, CS36_SW4, CS35_SW4, CS34_SW4  }, //SLASH 73
    {0, CS36_SW6, CS35_SW6, CS34_SW6  }, //RSFT  74
    {0, CS36_SW7, CS35_SW7, CS34_SW7  }, //UP    75
//Sixth row
    {0, CS27_SW9, CS25_SW9, CS26_SW9  }, //LCTRL 76
    {0, CS27_SW7, CS25_SW7, CS26_SW7  }, //LWIN  77
    {0, CS27_SW6, CS25_SW6, CS26_SW6  }, //LALT  78
    {0, CS27_SW5, CS25_SW5, CS26_SW5  }, //SPACE 79
    {0, CS27_SW3, CS25_SW3, CS26_SW3  }, //RALT  80
    {0, CS24_SW4, CS23_SW4, CS22_SW4  }, //RGUI  81
    {0, CS24_SW5, CS23_SW5, CS22_SW5  }, //MENU  82
    {0, CS24_SW6, CS23_SW6, CS22_SW6  }, //RCTRL 83
    {0, CS24_SW1, CS23_SW1, CS22_SW1  }, //LEFT  84
    {0, CS24_SW2, CS23_SW2, CS22_SW2  }, //DOWN  85
    {0, CS24_SW3, CS23_SW3, CS22_SW3  }, //RIGHT 86

};

led_config_t g_led_config = { {
    { 0        , 1          , 2          , 3          , 4          , 5          , 6          , 7          , 8          , 9          , 10         , 11         , 12         , 13         , 14         , 15        },
    { 16       , 17         , 18         , 19         , 20         , 21         , 22         , 23         , 24         , 25         , 26         , 27         , 28         , 29         , 30         , 31        },
    { 33       , 34         , 35         , 36         , 37         , 38         , 39         , 40         , 41         , 41         , 43         , 44         , 45         , 46         , 47         , 48        },
    { 50       , 51         , 52         , 53         , 54         , 55         , 56         , 57         , 58         , 59         , 60         , 61         , 62         , NO_LED     , NO_LED     , NO_LED    },
    { 63       , NO_LED     , 64         , 65         , 66         , 67         , 68         , 69         , 70         , 71         , 72         , 73         , 74         , 75         , 49         , 32        },
    { 76       , 77         , 78         , NO_LED     , NO_LED     , NO_LED     , 79         , NO_LED     , NO_LED     , 80         , 81         , 82         , 83         , 84         , 85         , 86        }
},{
    {   0,   0}, {  15,   0}, {  30,   0}, {  45,   0}, {  60,   0}, {  75,   0}, {  90,   0}, { 105,   0}, { 120,   0}, { 135,   0}, { 150,   0}, { 165,   0}, { 180,   0}, { 210,   0}, { 210,   0}, { 225,   0},
    {   0,  45}, {  15,  45}, {  30,  45}, {  45,  45}, {  60,  45}, {  75,  45}, {  90,  45}, { 105,  45}, { 120,  45}, { 135,  45}, { 150,  45}, { 165,  45}, { 180,  45}, { 210,  45}, { 210,  45}, { 215,  45},
    {   0,  90}, {  15,  90}, {  30,  90}, {  45,  90}, {  60,  90}, {  75,  90}, {  90,  90}, { 105,  90}, { 120,  90}, { 135,  90}, { 150,  90}, { 165,  90}, { 180,  90}, { 195,  90}, { 210,  90}, { 215,  90},
    {   0, 135}, {  15, 135}, {  30, 135}, {  45, 135}, {  60, 135}, {  75, 135}, {  90, 135}, { 105, 135}, { 120, 135}, { 135, 135}, { 150, 135}, { 165, 135}, { 180, 135},
    {   0, 180},              {  30, 180}, {  45, 180}, {  60, 180}, {  75, 180}, {  90, 180}, { 105, 180}, { 120, 180}, { 135, 180}, { 150, 180}, { 165, 180}, { 180, 180}, { 210, 180}, { 225,  45}, { 225,   0},
    {   0, 225}, {  15, 225}, {  30, 225},                                        {  90, 225},                           { 135, 225}, { 150, 225}, { 165, 225}, { 180, 225}, { 195, 225}, { 210, 225}, { 225, 225}
}, {
    1          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          ,
    4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          ,
    4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          ,
    4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 1          ,
    1                       , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 1          , 1          , 1          , 1          ,
    1          , 1          , 1          ,                                        4          ,                           1          , 1          , 1          , 1          , 1          , 1          , 1
} };
#endif
