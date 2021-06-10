/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#include "pro.h"

#ifdef RGB_MATRIX_ENABLE

const aw_led g_aw_leds[DRIVER_LED_TOTAL] = {
/* Refer to AW20216S manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          |                               Key       Flag    Row y-cm x-cm
 */                                                                                 
    {0, CS13_SW1,  CS14_SW1,  CS15_SW1  },  // 0 : R0-S0    //KC_LSFT   1       4   8.2  2.5
    //                                      //     R1-S0    //KC_MUTE                        
    //                                      //     R2-S0    //                           
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10  },  // 1 : R3-S0    //KC_LEFT   1       5   10   26
    {0, CS16_SW12, CS17_SW12, CS18_SW12 },  // 2 : R4-S0    //KC_RCTL   1       5   10   23.7
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5  },  // 3 : R5-S0    //KC_RGHT   1       5   10   29.9
    {0, CS16_SW1,  CS17_SW1,  CS18_SW1  },  // 4 : R6-S0    //KC_LCTL   1       5   10   1.2
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6   },  // 5 : R7-S0    //KC_F5     4       0   0    11.2
                                                            //                           
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2  },   // 6 : R0-S1    //KC_Q      4       2   4.3  3.7
    {0, CS7_SW1,   CS8_SW1,   CS9_SW1  },   // 7 : R1-S1    //KC_TAB    1       2   4.3  1.5
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2 },   // 8 : R2-S1    //KC_A      4       3   6.2  4.3
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1  },   // 9 : R3-S1    //KC_ESC    1       0   0    0.9
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2 },   //10 : R4-S1    //KC_Z      4       4   8.2  5.3
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4  },   //11 : R5-S1    //KC_PGUP   4       2   4.3  30.2
    {0, CS4_SW1,   CS5_SW1,   CS6_SW1  },   //12 : R6-S1    //KC_GRV    1       1   2.9  0.9
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2  },   //13 : R7-S1    //KC_1      4       1   2.9  2.6
                                                            //                           
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3  },   //14 : R0-S2    //KC_W      4       2   4.3  5.8
    {0, CS10_SW1,  CS11_SW1,  CS12_SW1 },   //15 : R1-S2    //KC_CAPS   1       3   6.2  1.8
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3 },   //16 : R2-S2    //KC_S      4       3   6.2  6.2
    //                                      //     R3-S2    //                           
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3 },   //17 : R4-S2    //KC_X      4       4   8.2  7.1
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7  },   //18 : R5-S2    //KC_PGDN   4       3   6.2  30.2
    {0, CS1_SW2,   CS2_SW2,   CS3_SW2  },   //19 : R6-S2    //KC_F1     4       0   0    3.3
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3  },   //20 : R7-S2    //KC_2      4       1   2.9  4.6
                                                            //                           
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4  },   //21 : R0-S3    //KC_E      4       2   4.3  7.6
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4  },   //22 : R1-S3    //KC_F3     4       0   0    7
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4 },   //23 : R2-S3    //KC_D      4       3   6.2  8
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5  },   //24 : R3-S3    //KC_F4     4       0   0    9   
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4 },   //25 : R4-S3    //KC_C      4       4   8.2  9
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9  },   //26 : R5-S3    //KC_UP     1       4   8.2  28
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3  },   //27 : R6-S3    //KC_F2     4       0   0    5.2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4  },   //28 : R7-S3    //KC_3      4       1   2.9  6.6
                                                            //                           
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5  },   //29 : R0-S4    //KC_R      4       2   4.3  9.5
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6  },   //30 : R1-S4    //KC_T      4       2   4.3  11.4
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5 },   //31 : R2-S4    //KC_F      4       3   6.2  10
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6 },   //32 : R3-S4    //KC_G      4       3   6.2  11.9
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5 },   //33 : R4-S4    //KC_V      4       4   8.2  11
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6 },   //34 : R5-S4    //KC_B      4       4   8.2  12.9
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6  },   //35 : R6-S4    //KC_5      4       1   2.9  10.4
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5  },   //36 : R7-S4    //KC_4      4       1   2.9  8.5
                                                            //                           
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8  },   //37 : R0-S5    //KC_U      4       2   4.3  15.3
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7  },   //38 : R1-S5    //KC_Y      4       2   4.3  13.4
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8 },   //39 : R2-S5    //KC_J      4       3   6.2  15.7
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7 },   //40 : R3-S5    //KC_H      4       3   6.2  13.8
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8 },   //41 : R4-S5    //KC_M      4       4   8.2  16.5
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7 },   //42 : R5-S5    //KC_N      4       4   8.2  14.7
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7  },   //43 : R6-S5    //KC_6      4       1   2.9  12.3
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8  },   //44 : R7-S5    //KC_7      4       1   2.9  14.2
                                                            //                           
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9  },   //45 : R0-S6    //KC_I      4       2   4.3  17.2
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8  },   //46 : R1-S6    //KC_RBRC   4       2   4.3  24.5
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9 },   //47 : R2-S6    //KC_K      4       3   6.2  17.5
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7  },   //48 : R3-S6    //KC_F6     4       0   0    13.2
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9 },   //49 : R4-S6    //KC_COMM   4       4   8.2  18.5
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3  },   //50 : R5-S6    //KC_DEL    4       1   2.9  30.2
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5  },   //51 : R6-S6    //KC_EQL    4       1   2.9  23.7
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9  },   //52 : R7-S6    //KC_8      4       1   2.9  16.1
                                                            //                           
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10 },   //53 : R0-S7    //KC_O      4       2   4.3  19
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8  },   //54 : R1-S7    //KC_F7     4       0   0    15.1
    {0, CS10_SW10, CS11_SW10, CS12_SW10},   //55 : R2-S7    //KC_L      4       3   6.2  19.5
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11 },   //56 : R3-S7    //KC_DOWN   1       5   10   28
    {0, CS13_SW10, CS14_SW10, CS15_SW10},   //57 : R4-S7    //KC_DOT    4       4   8.2  20.5
    {1, CS4_SW6,   CS5_SW6,   CS6_SW6  },   //58 : R5-S7    //KC_END    4       4   8.2  30.2
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9  },   //59 : R6-S7    //KC_F8     4       0   0    17
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10 },   //60 : R7-S7    //KC_9      4       1   2.9  18
                                                            //                           
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11 },   //61 : R0-S8    //KC_P      4       2   4.3  21
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12 },   //62 : R1-S8    //KC_LBRC   4       2   4.3  22.7
    {0, CS10_SW11, CS11_SW11, CS12_SW11},   //63 : R2-S8    //KC_SCLN   4       3   6.2  21.5
    {0, CS10_SW12, CS11_SW12, CS12_SW12},   //64 : R3-S8    //KC_QUOT   4       3   6.2  23.2
    //                                      //     R4-S8    //                           
    {0, CS13_SW11, CS14_SW11, CS15_SW11},   //65 : R5-S8    //KC_SLSH   4       4   8.2  22.3
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12 },   //66 : R6-S8    //KC_MINS   4       1   2.9  21.7
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11 },   //67 : R7-S8    //KC_0      4       1   2.9  19.8
                                                            //                           
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2 },   //68 : R0-S9    //KC_LGUI   1       5   10   3.7
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8  },   //69 : R1-S9    //KC_RSFT   1       4   8.2  25
    {0, CS16_SW10, CS17_SW10, CS18_SW10},   //70 : R2-S9    //MO(1)     1       5   10   21.9
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3 },   //71 : R3-S9    //KC_LALT   1       5   10   6
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6 },   //72 : R4-S9    //KC_SPC    4       5   10   13.2
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9 },   //73 : R5-S9    //KC_RALT   1       5   10   20
    //                                      //     R6-S9    //                           
    {1, CS4_SW2,   CS5_SW2,   CS6_SW2  },   //74 : R7-S9    //KC_PSCR   4       0   0    27.5
                                                            //                           
    //                                      //     R0-S10   //                           
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7  },   //75 : R1-S10   //KC_BSPC   1       1   2.9  26.5
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9  },   //76 : R2-S10   //KC_BSLS   1       2   4.3  27
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12 },   //77 : R3-S10   //KC_F11    4       0   0    23.2    
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11 },   //78 : R4-S10   //KC_ENT    1       3   6.2  26.5
    {1, CS1_SW1,   CS2_SW1,   CS3_SW1  },   //79 : R5-S10   //KC_F12    4       0   0    25.1
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10 },   //80 : R6-S10   //KC_F9     4       0   0    19.5
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11 },   //81 : R7-S10   //KC_F10    4       0   0    21.3
                                                                                         
    //Underglow                                                                         
    {1, CS13_SW1,  CS14_SW1,  CS15_SW1 },   //82 :          //LED1      2           0.8  0
    {1, CS13_SW2,  CS14_SW2,  CS15_SW2 },   //83 :          //LED2      2           1.9  0
    {1, CS13_SW3,  CS14_SW3,  CS15_SW3 },   //84 :          //LED3      2           3.0  0
    {1, CS13_SW4,  CS14_SW4,  CS15_SW4 },   //85 :          //LED4      2           4.1  0
    {1, CS13_SW5,  CS14_SW5,  CS15_SW5 },   //86 :          //LED5      2           5.2  0
    {1, CS13_SW6,  CS14_SW6,  CS15_SW6 },   //87 :          //LED6      2           6.3  0
    {1, CS13_SW7,  CS14_SW7,  CS15_SW7 },   //88 :          //LED7      2           7.4  0
    {1, CS13_SW8,  CS14_SW8,  CS15_SW8 },   //89 :          //LED8      2           8.5  0

    {1, CS16_SW1,  CS17_SW1,  CS18_SW1 },   //90 :          //LED11     2           0.8  32
    {1, CS16_SW2,  CS17_SW2,  CS18_SW2 },   //91 :          //LED12     2           1.9  32
    {1, CS16_SW3,  CS17_SW3,  CS18_SW3 },   //92 :          //LED13     2           3.0  32
    {1, CS16_SW4,  CS17_SW4,  CS18_SW4 },   //93 :          //LED14     2           4.1  32
    {1, CS16_SW5,  CS17_SW5,  CS18_SW5 },   //94 :          //LED15     2           5.2  32
    {1, CS16_SW6,  CS17_SW6,  CS18_SW6 },   //95 :          //LED16     2           6.3  32
    {1, CS16_SW7,  CS17_SW7,  CS18_SW7 },   //96 :          //LED17     2           7.4  32
    {1, CS16_SW8,  CS17_SW8,  CS18_SW8 },   //97 :          //LED18     2           8.5  32
};

//See definition in 'rgb_matrix_types.h'
led_config_t g_led_config = { {
    //R0      R1      R2      R3      R4      R5  R6      R7 
    { 0,      NO_LED, NO_LED, 1,      2,      3,  4,      5 }, /*S0 */  \
    { 6,      7,      8,      9,      10,     11, 12,     13}, /*S1 */  \
    { 14,     15,     16,     NO_LED, 17,     18, 19,     20}, /*S2 */  \
    { 21,     22,     23,     24,     25,     26, 27,     28}, /*S3 */  \
    { 29,     30,     31,     32,     33,     34, 35,     36}, /*S4 */  \
    { 37,     38,     39,     40,     41,     42, 43,     44}, /*S5 */  \
    { 45,     46,     47,     48,     49,     50, 51,     52}, /*S6 */  \
    { 53,     54,     55,     56,     57,     58, 59,     60}, /*S7 */  \
    { 61,     62,     63,     64,     NO_LED, 65, 66,     67}, /*S8 */  \
    { 68,     69,     70,     71,     72,     73, NO_LED, 74}, /*S9 */  \
    { NO_LED, 75,     76,     77,     78,     79, 80,     81}  /*S10*/  \
}, {
    {17,52},{182,64},{165,64},{209,64},{8,64},{78,0},{25,27},{10,27},
    {30,39},{6,0},{37,52},{211,27},{6,18},{18,18},{40,27},{12,39},
    {43,39},{49,52},{211,39},{23,0},{32,18},{53,27},{49,0},{56,39},
    {63,0},{63,52},{196,52},{36,0},{46,18},{66,27},{79,27},{70,39},
    {83,39},{77,52},{90,52},{72,18},{59,18},{107,27},{93,27},{109,39},
    {96,39},{115,52},{102,52},{86,18},{99,18},{120,27},{171,27},{122,39},
    {92,0},{129,52},{211,18},{165,18},{112,18},{133,27},{105,0},{136,39},
    {196,64},{143,52},{211,52},{119,0},{126,18},{147,27},{158,27},{150,39},
    {162,39},{156,52},{151,18},{138,18},{25,64},{175,52},{153,64},{42,64},
    {92,64},{140,64},{192,0},{185,18},{189,27},{162,0},{185,39},{175,0},
    {136,0},{149,0},{0,5},{0,12},{0,19},{0,26},{0,33},{0,40},
    {0,47},{0,54},{224,5},{224,12},{224,19},{224,26},{224,33},{224,40},
    {224,47},{224,54},
}, {
    1,1,1,1,1,4,4,1,
    4,1,4,4,1,4,4,1,
    4,4,4,4,4,4,4,4,
    4,4,1,4,4,4,4,4,
    4,4,4,4,4,4,4,4,
    4,4,4,4,4,4,4,4,
    4,4,4,4,4,4,4,4,
    1,4,4,4,4,4,4,4,
    4,4,4,4,1,1,1,1,
    4,1,4,1,1,4,1,4,
    4,4,2,2,2,2,2,2,
    2,2,2,2,2,2,2,2,
    2,2
} };
#endif
