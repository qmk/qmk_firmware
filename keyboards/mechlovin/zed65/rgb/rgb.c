/* Copyright 2024 Mechlovin'
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

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
}

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           |           LED Number in schematic
 *   |  |           |           |           |    Key Number in schematic
 *   |  |           |           |           |    |   LED Index  
 *   |  |           |           |           |    |   |*/
    {0,   CS37_SW7, CS39_SW7,   CS38_SW7}, //D93-SW2-0
    {0,   CS37_SW8, CS39_SW8,   CS38_SW8}, //D95-SW7-1
    {0,   CS34_SW7, CS36_SW7,   CS35_SW7}, //D97-SW13-2
    {0,   CS34_SW8, CS36_SW8,   CS35_SW8}, //D99-SW19-3
    {0,   CS31_SW7, CS33_SW7,   CS32_SW7}, //D101-SW24-4
    {0,   CS31_SW8, CS33_SW8,   CS32_SW8}, //D103-SW29-5
    {0,   CS28_SW7, CS30_SW7,   CS29_SW7}, //D105-SW33-6
    {0,   CS28_SW8, CS30_SW8,   CS29_SW8}, //D107-SW39-7
    {0,    CS7_SW7, CS9_SW7,    CS8_SW7},  //D109-SW44-8
    {0,    CS7_SW8, CS9_SW8,    CS8_SW8},  //D111-SW49-9
    {0,   CS13_SW7, CS15_SW7,   CS14_SW7}, //D113-SW54-10
    {0,   CS13_SW8, CS15_SW8,   CS14_SW8}, //D115-SW60-11
    {0,   CS16_SW7, CS18_SW7,   CS17_SW7}, //D117-SW66-12
    {0,   CS16_SW8, CS18_SW8,   CS17_SW8}, //D86-SW72-13
    {0,   CS19_SW8, CS21_SW8,   CS20_SW8}, //D180-SW80-14
    
    {0,   CS37_SW5, CS39_SW5,   CS38_SW5}, //D124-SW5-15
    {0,   CS37_SW6, CS39_SW6,   CS38_SW6}, //D127-SW9-16
    {0,   CS34_SW5, CS36_SW5,   CS35_SW5}, //D130-SW14-17
    {0,   CS34_SW6, CS36_SW6,   CS35_SW6}, //D133-SW20-18
    {0,   CS31_SW5, CS33_SW5,   CS32_SW5}, //D135-SW25-19
    {0,   CS31_SW6, CS33_SW6,   CS32_SW6}, //D137-SW30-20
    {0,   CS28_SW5, CS30_SW5,   CS29_SW5}, //D139-SW34-21
    {0,   CS28_SW6, CS30_SW6,   CS29_SW6}, //D142-SW40-22
    {0,    CS7_SW5, CS9_SW5,    CS8_SW5},  //D144-SW45-23
    {0,    CS7_SW6, CS9_SW6,    CS8_SW6},  //D146-SW50-24
    {0,   CS13_SW5, CS15_SW5,   CS14_SW5}, //D148-SW55-25
    {0,   CS13_SW6, CS15_SW6,   CS14_SW6}, //D151-SW61-26
    {0,   CS16_SW5, CS18_SW5,   CS17_SW5}, //D154-SW67-27
    {0,   CS16_SW6, CS18_SW6,   CS17_SW6}, //D179-SW73-28
    {0,   CS19_SW6, CS21_SW6,   CS20_SW6}, //D59-SW81-29
    
    {0,   CS37_SW3, CS39_SW3,   CS38_SW3}, //D165-SW93-30
    {0,   CS37_SW4, CS39_SW4,   CS38_SW4}, //D167-SW11-31
    {0,   CS34_SW3, CS36_SW3,   CS35_SW3}, //D168-SW16-32
    {0,   CS34_SW4, CS36_SW4,   CS35_SW4}, //D169-SW22-33
    {0,   CS31_SW3, CS33_SW3,   CS32_SW3}, //D170-SW27-34
    {0,   CS31_SW4, CS33_SW4,   CS32_SW4}, //D171-SW32-35
    {0,   CS28_SW3, CS30_SW3,   CS29_SW3}, //D172-SW38-36
    {0,   CS28_SW4, CS30_SW4,   CS29_SW4}, //D173-SW43-37
    {0,    CS7_SW3, CS9_SW3,    CS8_SW3},  //D174-SW48-38
    {0,    CS7_SW4, CS9_SW4,    CS8_SW4},  //D175-SW53-39
    {0,   CS13_SW3, CS15_SW3,   CS14_SW3}, //D176-SW58-40
    {0,   CS13_SW4, CS15_SW4,   CS14_SW4}, //D177-SW64-41
    {0,   CS16_SW3, CS18_SW3,   CS17_SW3}, //D87-SW94-42
    {0,   CS19_SW3, CS21_SW3,   CS20_SW3}, //D42-SW23-43
    
    {0,   CS37_SW1, CS39_SW1,   CS38_SW1}, //D125-SW3-44
    {0,   CS34_SW1, CS36_SW1,   CS35_SW1}, //D131-SW15-45
    {0,   CS34_SW2, CS36_SW2,   CS35_SW2}, //D134-SW21-46
    {0,   CS31_SW1, CS33_SW1,   CS32_SW1}, //D136-SW26-47
    {0,   CS31_SW2, CS33_SW2,   CS32_SW2}, //D138-SW31-48
    {0,   CS28_SW1, CS30_SW1,   CS29_SW1}, //D140-SW35-49
    {0,   CS28_SW2, CS30_SW2,   CS29_SW2}, //D143-SW41-50
    {0,    CS7_SW1, CS9_SW1,    CS8_SW1},  //D145-SW46-51
    {0,    CS7_SW2, CS9_SW2,    CS8_SW2},  //D147-SW51-52
    {0,   CS13_SW1, CS15_SW1,   CS14_SW1}, //D149-SW56-53
    {0,   CS13_SW2, CS15_SW2,   CS14_SW2}, //D152-SW62-54
    {0,   CS16_SW1, CS18_SW1,   CS17_SW1}, //D155-SW68-55
    {0,   CS16_SW2, CS18_SW2,   CS17_SW2}, //D160-SW74-56
    {0,   CS19_SW2, CS21_SW2,   CS20_SW2}, //D47-SW28-57
    
    {0,   CS37_SW9, CS39_SW9,   CS38_SW9}, //D124-SW104-58
    {0,   CS37_SW2, CS39_SW2,   CS38_SW2}, //D127-SW106-59
    {0,   CS34_SW9, CS36_SW9,   CS35_SW9}, //D130-SW17-60
    {0,   CS28_SW9, CS30_SW9,   CS29_SW9}, //D142-SW36-61
    {0,   CS13_SW9, CS15_SW9,   CS14_SW9}, //D151-SW63-62
    {0,   CS16_SW9, CS18_SW9,   CS17_SW9}, //D154-SW69-63
    {0,   CS16_SW4, CS18_SW4,   CS17_SW4}, //D179-SW75-64
    {0,   CS19_SW4, CS21_SW4,   CS20_SW4}, //D59-SW82-65
};

led_config_t g_led_config = { {
    // Key Matrix to LED Index
        {0,           1,           2,           3,           4,           5,           6,           7,           8,           9,           10,           11,           12,           13,           14},
        {15,         16,          17,          18,          19,          20,          21,          22,          23,          24,           25,           26,           27,           28,           29},
        {30,         31,          32,          33,          34,          35,          36,          37,          38,          39,           40,           41,       NO_LED,           42,           43},
        {44,     NO_LED,          45,          46,          47,          48,          49,          50,          51,          52,           53,           54,           55,           56,           57},
        {58,         59,          60,      NO_LED,      NO_LED,      NO_LED,          61,      NO_LED,      NO_LED,      NO_LED,       NO_LED,           62,           63,           64,           65},
    }, {
        {0, 0},  {16, 0},    {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},     {192,  0},     {208,  0},     {224,  0},
        {0, 0},  {16, 0},    {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},     {192,  0},     {208,  0},     {224,  0},
        {0, 0},  {16, 0},    {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},                    {208,  0},     {224,  0},
        {0, 0},              {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},     {192,  0},     {208,  0},     {224,  0},
        {0, 0},  {16, 0},    {32, 0},                                           {96,  0},                                                             {176,  0},     {192,  0},     {208,  0},     {224,  0},
    }, {
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,                            1,             1,
       1,                    1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,                                                  1,                                                                     1,             1,             1,             1,
    }
};

#endif
