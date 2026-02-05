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
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |         G location
 *   |  |         |         B location
 *   |  |         |         | */
// First row
    {0, SW9_CS7 , SW9_CS9 , SW9_CS8  }, //ESC    0
    {0, SW8_CS7 , SW8_CS9 , SW8_CS8  }, //F1     1
    {0, SW7_CS7 , SW7_CS9 , SW7_CS8  }, //F2     2
    {0, SW6_CS7 , SW6_CS9 , SW6_CS8  }, //F3     3
    {0, SW5_CS7 , SW5_CS9 , SW5_CS8  }, //F4     4
    {0, SW4_CS7 , SW4_CS9 , SW4_CS8  }, //F5     5
    {0, SW3_CS7 , SW3_CS9 , SW3_CS8  }, //F6     6
    {0, SW2_CS7 , SW2_CS9 , SW2_CS8  }, //F7     7
    {0, SW1_CS7 , SW1_CS9 , SW1_CS8  }, //F8     8
    {0, SW2_CS18, SW2_CS16, SW2_CS17 }, //F9     9
    {0, SW3_CS18, SW3_CS16, SW3_CS17 }, //F10    10
    {0, SW4_CS18, SW4_CS16, SW4_CS17 }, //F11    11
    {0, SW6_CS18, SW6_CS16, SW6_CS17 }, //F12    12
    {0, SW7_CS18, SW7_CS16, SW7_CS17 }, //PRI    13
    {0, SW8_CS18, SW8_CS16, SW8_CS17 }, //SCR    14
    {0, SW9_CS18, SW9_CS16, SW9_CS17 }, //PAUS   15
//Second row
    {0, SW9_CS12, SW9_CS11, SW9_CS10 }, //GRAVE  16
    {0, SW8_CS12, SW8_CS11, SW8_CS10 }, //1      17
    {0, SW7_CS12, SW7_CS11, SW7_CS10 }, //2      18
    {0, SW6_CS12, SW6_CS11, SW6_CS10 }, //3      19
    {0, SW5_CS12, SW5_CS11, SW5_CS10 }, //4      20
    {0, SW4_CS12, SW4_CS11, SW4_CS10 }, //5      21
    {0, SW3_CS12, SW3_CS11, SW3_CS10 }, //6      22
    {0, SW2_CS12, SW2_CS11, SW2_CS10 }, //7      23
    {0, SW1_CS12, SW1_CS11, SW1_CS10 }, //8      24
    {0, SW1_CS15, SW1_CS13, SW1_CS14 }, //9      25
    {0, SW2_CS15, SW2_CS13, SW2_CS14 }, //0      26
    {0, SW3_CS15, SW3_CS13, SW3_CS14 }, //MINUS  27
    {0, SW4_CS15, SW4_CS13, SW4_CS14 }, //PLUS   28
    {0, SW5_CS15, SW5_CS13, SW5_CS14 }, //BKSP   29
    {0, SW7_CS15, SW7_CS13, SW7_CS14 }, //INS    30
    {0, SW8_CS15, SW8_CS13, SW8_CS14 }, //HOME   31
    {0, SW9_CS15, SW9_CS13, SW9_CS14 }, //PGUP   32
//Third row
    {0, SW9_CS4 , SW9_CS6 , SW9_CS5  }, //TAB    33
    {0, SW8_CS4 , SW8_CS6 , SW8_CS5  }, //Q      34
    {0, SW7_CS4 , SW7_CS6 , SW7_CS5  }, //W      35
    {0, SW6_CS4 , SW6_CS6 , SW6_CS5  }, //E      36
    {0, SW5_CS4 , SW5_CS6 , SW5_CS5  }, //R      37
    {0, SW4_CS4 , SW4_CS6 , SW4_CS5  }, //T      38
    {0, SW3_CS4 , SW3_CS6 , SW3_CS5  }, //Y      39
    {0, SW2_CS4 , SW2_CS6 , SW2_CS5  }, //U      40
    {0, SW1_CS4 , SW1_CS6 , SW1_CS5  }, //I      41
    {0, SW2_CS3 , SW2_CS1 , SW2_CS2  }, //O      42
    {0, SW3_CS3 , SW3_CS1 , SW3_CS2  }, //P      43
    {0, SW4_CS3 , SW4_CS1 , SW4_CS2  }, //LBRKT  44
    {0, SW5_CS3 , SW5_CS1 , SW5_CS2  }, //RBRKT  45
    {0, SW6_CS3 , SW6_CS1 , SW6_CS2  }, //BSLS   46
    {0, SW7_CS3 , SW7_CS1 , SW7_CS2  }, //DEL    47
    {0, SW8_CS3 , SW8_CS1 , SW8_CS2  }, //END    48
    {0, SW9_CS3 , SW9_CS1 , SW9_CS2  }, //PGDN   49
//Fourth row
    {0, SW9_CS33, SW9_CS32, SW9_CS31  }, //CAPS  50
    {0, SW8_CS33, SW8_CS32, SW8_CS31  }, //A     51
    {0, SW7_CS33, SW7_CS32, SW7_CS31  }, //S     52
    {0, SW6_CS33, SW6_CS32, SW6_CS31  }, //D     53
    {0, SW5_CS33, SW5_CS32, SW5_CS31  }, //F     54
    {0, SW4_CS33, SW4_CS32, SW4_CS31  }, //G     55
    {0, SW3_CS33, SW3_CS32, SW3_CS31  }, //H     56
    {0, SW2_CS33, SW2_CS32, SW2_CS31  }, //J     57
    {0, SW1_CS33, SW1_CS32, SW1_CS31  }, //K     58
    {0, SW2_CS39, SW2_CS38, SW2_CS37  }, //L     59
    {0, SW3_CS39, SW3_CS38, SW3_CS37  }, //COLON 60
    {0, SW4_CS39, SW4_CS38, SW4_CS37  }, //QUOTE 61
    {0, SW6_CS39, SW6_CS38, SW6_CS37  }, //ENTER 62
//Fifth row
    {0, SW9_CS30, SW9_CS28, SW9_CS29  }, //LSFT  63
    {0, SW7_CS30, SW7_CS28, SW7_CS29  }, //Z     64
    {0, SW6_CS30, SW6_CS28, SW6_CS29  }, //X     65
    {0, SW5_CS30, SW5_CS28, SW5_CS29  }, //C     66
    {0, SW4_CS30, SW4_CS28, SW4_CS29  }, //V     67
    {0, SW3_CS30, SW3_CS28, SW3_CS29  }, //B     68
    {0, SW2_CS30, SW2_CS28, SW2_CS29  }, //N     69
    {0, SW1_CS30, SW1_CS28, SW1_CS29  }, //M     70
    {0, SW1_CS36, SW1_CS35, SW1_CS34  }, //COMMA 71
    {0, SW3_CS36, SW3_CS35, SW3_CS34  }, //DOT   72
    {0, SW4_CS36, SW4_CS35, SW4_CS34  }, //SLASH 73
    {0, SW6_CS36, SW6_CS35, SW6_CS34  }, //RSFT  74
    {0, SW7_CS36, SW7_CS35, SW7_CS34  }, //UP    75
//Sixth row
    {0, SW9_CS27, SW9_CS25, SW9_CS26  }, //LCTRL 76
    {0, SW7_CS27, SW7_CS25, SW7_CS26  }, //LWIN  77
    {0, SW6_CS27, SW6_CS25, SW6_CS26  }, //LALT  78
    {0, SW5_CS27, SW5_CS25, SW5_CS26  }, //SPACE 79
    {0, SW3_CS27, SW3_CS25, SW3_CS26  }, //RALT  80
    {0, SW4_CS24, SW4_CS23, SW4_CS22  }, //RGUI  81
    {0, SW5_CS24, SW5_CS23, SW5_CS22  }, //MENU  82
    {0, SW6_CS24, SW6_CS23, SW6_CS22  }, //RCTRL 83
    {0, SW1_CS24, SW1_CS23, SW1_CS22  }, //LEFT  84
    {0, SW2_CS24, SW2_CS23, SW2_CS22  }, //DOWN  85
    {0, SW3_CS24, SW3_CS23, SW3_CS22  }, //RIGHT 86

};
#endif
