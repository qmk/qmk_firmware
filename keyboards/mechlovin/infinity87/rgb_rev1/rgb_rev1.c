/* Copyright 2020 Team Mechlovin'
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

#include "rgb_rev1.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS34_SW1,   CS35_SW1,   CS36_SW1}, //D92-K00-0
    {0, CS37_SW1,   CS38_SW1,   CS39_SW1}, //D94-K01-1
    {0, CS31_SW1,   CS32_SW1,   CS33_SW1}, //D96-K02-2
    {0, CS28_SW1,   CS29_SW1,   CS30_SW1}, //D98-K03-3
    {0, CS25_SW1,   CS26_SW1,   CS27_SW1}, //D100-K04-4
    {0, CS22_SW1,   CS23_SW1,   CS24_SW1}, //D102-K05-5
    {0, CS19_SW1,   CS20_SW1,   CS21_SW1}, //D104-K06-6
    {0, CS18_SW1,   CS17_SW1,   CS16_SW1}, //D106-K07-7
    {0, CS15_SW1,   CS14_SW1,   CS13_SW1}, //D108-K08-8
    {0, CS12_SW1,   CS11_SW1,   CS10_SW1}, //D110-K09-9
    {0, CS9_SW1,    CS8_SW1,    CS7_SW1},  //D112-K0A-10
    {0, CS6_SW1,    CS5_SW1,    CS4_SW1},  //D114-K0B-11
    {0, CS3_SW1,    CS2_SW1,    CS1_SW1},  //D116-K0C-12
    {0, CS15_SW7,   CS14_SW7,   CS13_SW7}, //D157-K0D-13
    {0, CS18_SW7,   CS17_SW7,   CS16_SW7}, //D118-K0E-14
    {0, CS19_SW7,   CS20_SW7,   CS21_SW7}, //D120-K0F-15
    {0, CS12_SW7,   CS11_SW7,   CS10_SW7}, //D122-K0G-16
    {0, CS34_SW2,   CS35_SW2,   CS36_SW2}, //D93-K10-17
    {0, CS37_SW2,   CS38_SW2,   CS39_SW2}, //D95-K11-18
    {0, CS31_SW2,   CS32_SW2,   CS33_SW2}, //D97-K12-19
    {0, CS28_SW2,   CS29_SW2,   CS30_SW2}, //D99-K13-20
    {0, CS25_SW2,   CS26_SW2,   CS27_SW2}, //D101-K14-21
    {0, CS22_SW2,   CS23_SW2,   CS24_SW2}, //D103-K15-22
    {0, CS19_SW2,   CS20_SW2,   CS21_SW2}, //D105-K16-23
    {0, CS18_SW2,   CS17_SW2,   CS16_SW2}, //D107-K17-24
    {0, CS15_SW2,   CS14_SW2,   CS13_SW2}, //D109-K18-25
    {0, CS12_SW2,   CS11_SW2,   CS10_SW2}, //D111-K19-26
    {0, CS9_SW2,    CS8_SW2,    CS7_SW2},  //D113-K1A-27
    {0, CS6_SW2,    CS5_SW2,    CS4_SW2},  //D115-K1B-28
    {0, CS3_SW2,    CS2_SW2,    CS1_SW2},  //D117-K1C-29
    {0, CS3_SW8,    CS2_SW8,    CS1_SW8},  //D158-K1D-30
    {0, CS3_SW7,    CS2_SW7,    CS1_SW7},  //D119-K1E-31
    {0, CS18_SW8,   CS17_SW8,   CS16_SW8}, //D121-K1F-32
    {0, CS9_SW9,    CS8_SW9,    CS7_SW9}, //D123-K1G-33
    {0, CS34_SW3,   CS35_SW3,   CS36_SW3}, //D124-K20-34
    {0, CS37_SW3,   CS38_SW3,   CS39_SW3}, //D127-K21-35
    {0, CS31_SW3,   CS32_SW3,   CS33_SW3}, //D130-K22-36
    {0, CS28_SW3,   CS29_SW3,   CS30_SW3}, //D133-K23-37
    {0, CS25_SW3,   CS26_SW3,   CS27_SW3}, //D135-K24-38
    {0, CS22_SW3,   CS23_SW3,   CS24_SW3}, //D137-K25-39
    {0, CS19_SW3,   CS20_SW3,   CS21_SW3}, //D139-K26-40
    {0, CS18_SW3,   CS17_SW3,   CS16_SW3}, //D142-K27-41
    {0, CS15_SW3,   CS14_SW3,   CS13_SW3}, //D144-K28-42
    {0, CS12_SW3,   CS11_SW3,   CS10_SW3}, //D146-K29-43
    {0, CS9_SW3,    CS8_SW3,    CS7_SW3},  //D148-K2A-44
    {0, CS6_SW3,    CS5_SW3,    CS4_SW3},  //D151-K2B-45
    {0, CS3_SW3,    CS2_SW3,    CS1_SW3},  //D154-K2C-46
    {0, CS6_SW8,    CS5_SW8,    CS4_SW8},  //D159-K2D-47
    {0, CS6_SW7,    CS5_SW7,    CS4_SW7},  //D180-K2E-48
    {0, CS19_SW8,   CS20_SW8,   CS21_SW8}, //D181-K2F-49
    {0, CS9_SW7,    CS8_SW7,    CS7_SW7},  //D182-K2G-50
    {0, CS34_SW4,   CS35_SW4,   CS36_SW4}, //D166-K30-51
    {0, CS37_SW4,   CS38_SW4,   CS39_SW4}, //D167-K31-52
    {0, CS31_SW4,   CS32_SW4,   CS33_SW4}, //D168-K32-53
    {0, CS28_SW4,   CS29_SW4,   CS30_SW4}, //D169-K33-54
    {0, CS25_SW4,   CS26_SW4,   CS27_SW4}, //D170-K34-55
    {0, CS22_SW4,   CS23_SW4,   CS24_SW4}, //D171-K35-56
    {0, CS19_SW4,   CS20_SW4,   CS21_SW4}, //D172-K36-57
    {0, CS18_SW4,   CS17_SW4,   CS16_SW4}, //D173-K37-58
    {0, CS15_SW4,   CS14_SW4,   CS13_SW4}, //D174-K38-59
    {0, CS12_SW4,   CS11_SW4,   CS10_SW4}, //D175-K39-60
    {0, CS9_SW4,    CS8_SW4,    CS7_SW4},  //D176-K3A-61
    {0, CS6_SW4,    CS5_SW4,    CS4_SW4},  //D177-K3B-62
    {0, CS3_SW4,    CS2_SW4,    CS1_SW4},  //D178-K3C-63
    {0, CS9_SW8,    CS8_SW8,    CS7_SW8},  //D179-K3D-64
    {0, CS34_SW5,   CS35_SW5,   CS36_SW5}, //D125-K40-65
    {0, CS37_SW5,   CS38_SW5,   CS39_SW5}, //D128-K41-66
    {0, CS31_SW5,   CS32_SW5,   CS33_SW5}, //D131-K42-67
    {0, CS28_SW5,   CS29_SW5,   CS30_SW5}, //D134-K43-68
    {0, CS25_SW5,   CS26_SW5,   CS27_SW5}, //D136-K44-69
    {0, CS22_SW5,   CS23_SW5,   CS24_SW5}, //D138-K45-70
    {0, CS19_SW5,   CS20_SW5,   CS21_SW5}, //D140-K46-71
    {0, CS18_SW5,   CS17_SW5,   CS16_SW5}, //D143-K47-72
    {0, CS15_SW5,   CS14_SW5,   CS13_SW5}, //D145-K48-73
    {0, CS12_SW5,   CS11_SW5,   CS10_SW5}, //D147-K49-74
    {0, CS9_SW5,    CS8_SW5,    CS7_SW5},  //D149-K4A-75
    {0, CS6_SW5,    CS5_SW5,    CS4_SW5},  //D152-K4B-76
    {0, CS3_SW5,    CS2_SW5,    CS1_SW5},  //D155-K4C-77
    {0, CS12_SW8,   CS11_SW8,   CS10_SW8}, //D160-K4D-78
    {0, CS12_SW9,   CS11_SW9,   CS10_SW9}, //D163-K4E-79
    {0, CS34_SW6,   CS35_SW6,   CS36_SW6}, //D126-K20-80
    {0, CS37_SW6,   CS38_SW6,   CS39_SW6}, //D129-K21-81
    {0, CS31_SW6,   CS32_SW6,   CS33_SW6}, //D132-K22-82
    {0, CS19_SW6,   CS20_SW6,   CS21_SW6}, //D141-K26-83
    {0, CS9_SW6,    CS8_SW6,    CS7_SW6},  //D150-K2A-84
    {0, CS6_SW6,    CS5_SW6,    CS4_SW6},  //D153-K2B-85
    {0, CS3_SW6,    CS2_SW6,    CS1_SW6},  //D156-K2C-86
    {0, CS15_SW8,   CS14_SW8,   CS13_SW8}, //D161-K2D-87
    {0, CS15_SW9,   CS14_SW9,   CS13_SW9}, //D162-K2E-88
    {0, CS18_SW9,   CS17_SW9,   CS16_SW9}, //D164-K2F-89
    {0, CS19_SW9,   CS20_SW9,   CS21_SW9}, //D165-K2G-90
};

led_config_t g_led_config = { {
    // Key Matrix to LED Index
        {0,           1,           2,           3,           4,           5,           6,           7,           8,           9,           10,           11,           12,           13,           14,           15,           16},
        {17,         18,          19,          20,          21,          22,          23,          24,          25,          26,           27,           28,           29,           30,           31,           32,           33},
        {34,         35,          36,          37,          38,          39,          40,          41,          42,          43,           44,           45,           46,           47,           48,           49,           50},
        {51,         52,          53,          54,          55,          56,          57,          58,          59,          60,           61,           62,           63,           64,       NO_LED,       NO_LED,       NO_LED},
        {65,         66,          67,          68,          69,          70,          71,          72,          73,          74,           75,           76,           77,           78,       NO_LED,           79,       NO_LED},
        {80,         81,          82,      NO_LED,      NO_LED,      NO_LED,          83,      NO_LED,      NO_LED,      NO_LED,           84,           85,           86,           87,           88,           89,           90}
    }, {
        {0, 0},  {14, 0},    {28, 0},    {42,  0},    {56,  0},    {70,  0},    {84,  0},    {98,  0},    {112,  0},    {126,  0},     {140,  0},     {154,  0},     {168,  0},     {182,  0},     {196,  0},     {210,  0},      {224,  0},
        {0,16},  {14,16},    {28,16},    {42, 16},    {56, 16},    {70, 16},    {84, 16},    {98, 16},    {112, 16},    {126, 16},     {140, 16},     {154, 16},     {168, 16},     {182, 16},     {196, 16},     {210, 16},      {224, 16},
        {0,32},  {14,32},    {28,32},    {42, 32},    {56, 32},    {70, 32},    {84, 32},    {98, 32},    {112, 32},    {126, 32},     {140, 32},     {154, 32},     {168, 32},     {182, 32},     {196, 32},     {210, 32},      {224, 32},
        {0,48},  {14,48},    {28,48},    {42, 48},    {56, 48},    {70, 48},    {84, 48},    {98, 48},    {112, 48},    {126, 48},     {140, 48},     {154, 48},     {168, 48},     {182, 48},
        {0,64},  {14,64},    {28,64},    {42, 64},    {56, 64},    {70, 64},    {84, 64},    {98, 64},    {112, 64},    {126, 64},     {140, 64},     {154, 64},     {168, 64},     {182, 64},     {210, 64},
        {0,80},  {14,80},    {28,80},                                           {84, 80},                                              {140, 80},     {154, 80},     {168, 80},     {182, 80},     {196, 80},     {210, 80},      {224, 80}
    }, {
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,                                                  1,                                                      1,             1,             1,             1,             1,             1,             1
    } };


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(51, 255, 255, 255);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(15, 255, 255, 255);
    }
    return true;
}
#endif
