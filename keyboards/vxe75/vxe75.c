/* Copyright (C) 2024 Westberry Technology Corp., Ltd
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

#include QMK_KEYBOARD_H

const aw_led g_aw_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, CS1_SW1,  CS2_SW1,  CS3_SW1   },  // 0
    {0, CS1_SW2,  CS2_SW2,  CS3_SW2   },  // 1
    {0, CS1_SW3,  CS2_SW3,  CS3_SW3   },  // 2
    {0, CS1_SW4,  CS2_SW4,  CS3_SW4   },  // 3
    {0, CS1_SW5,  CS2_SW5,  CS3_SW5   },  // 4
    {0, CS1_SW6,  CS2_SW6,  CS3_SW6   },  // 5
    {0, CS1_SW7,  CS2_SW7,  CS3_SW7   },  // 6
    {0, CS1_SW8,  CS2_SW8,  CS3_SW8   },  // 7
    {0, CS1_SW9,  CS2_SW9,  CS3_SW9   },  // 8
    {0, CS1_SW10, CS2_SW10, CS3_SW10  },  // 9
    {0, CS1_SW11, CS2_SW11, CS3_SW11  },  // 10
    {0, CS1_SW12, CS2_SW12, CS3_SW12  },  // 11
    {1, CS1_SW1,  CS2_SW1,  CS3_SW1   },  // 12
    {1, CS1_SW2,  CS2_SW2,  CS3_SW2   },  // 13

    {0, CS4_SW1,  CS5_SW1,  CS6_SW1   },  // 14
    {0, CS4_SW2,  CS5_SW2,  CS6_SW2   },  // 15
    {0, CS4_SW3,  CS5_SW3,  CS6_SW3   },  // 16
    {0, CS4_SW4,  CS5_SW4,  CS6_SW4   },  // 17
    {0, CS4_SW5,  CS5_SW5,  CS6_SW5   },  // 18
    {0, CS4_SW6,  CS5_SW6,  CS6_SW6   },  // 19
    {0, CS4_SW7,  CS5_SW7,  CS6_SW7   },  // 20
    {0, CS4_SW8,  CS5_SW8,  CS6_SW8   },  // 21
    {0, CS4_SW9,  CS5_SW9,  CS6_SW9   },  // 22
    {0, CS4_SW10, CS5_SW10, CS6_SW10  },  // 23
    {0, CS4_SW11, CS5_SW11, CS6_SW11  },  // 24
    {0, CS4_SW12, CS5_SW12, CS6_SW12  },  // 25
    {1, CS1_SW5,  CS2_SW5,  CS3_SW5   },  // 26
    {1, CS1_SW7,  CS2_SW7,  CS3_SW7   },  // 27
    {1, CS4_SW3,  CS5_SW3,  CS6_SW3   },  // 28

    {0, CS7_SW1,  CS8_SW1,  CS9_SW1   },  // 29
    {0, CS7_SW2,  CS8_SW2,  CS9_SW2   },  // 30
    {0, CS7_SW3,  CS8_SW3,  CS9_SW3   },  // 31
    {0, CS7_SW4,  CS8_SW4,  CS9_SW4   },  // 32
    {0, CS7_SW5,  CS8_SW5,  CS9_SW5   },  // 33
    {0, CS7_SW6,  CS8_SW6,  CS9_SW6   },  // 34
    {0, CS7_SW7,  CS8_SW7,  CS9_SW7   },  // 35
    {0, CS7_SW8,  CS8_SW8,  CS9_SW8   },  // 36
    {0, CS7_SW9,  CS8_SW9,  CS9_SW9   },  // 37
    {0, CS7_SW10, CS8_SW10, CS9_SW10  },  // 38
    {0, CS7_SW11, CS8_SW11, CS9_SW11  },  // 39
    {0, CS7_SW12, CS8_SW12, CS9_SW12  },  // 40
    {1, CS1_SW8,  CS2_SW8,  CS3_SW8   },  // 41
    {1, CS1_SW9,  CS2_SW9,  CS3_SW9   },  // 42
    {1, CS4_SW4,  CS5_SW4,  CS6_SW4   },  // 43


    {0, CS10_SW1, CS11_SW1, CS12_SW1  },  // 44
    {0, CS10_SW2, CS11_SW2, CS12_SW2  },  // 45
    {0, CS10_SW3, CS11_SW3, CS12_SW3  },  // 46
    {0, CS10_SW4, CS11_SW4, CS12_SW4  },  // 47
    {0, CS10_SW5, CS11_SW5, CS12_SW5  },  // 48
    {0, CS10_SW6, CS11_SW6, CS12_SW6  },  // 49
    {0, CS10_SW7, CS11_SW7, CS12_SW7  },  // 50
    {0, CS10_SW8, CS11_SW8, CS12_SW8  },  // 51
    {0, CS10_SW9, CS11_SW9, CS12_SW9  },  // 52
    {0, CS10_SW10,CS11_SW10,CS12_SW10 },  // 53
    {0, CS10_SW11,CS11_SW11,CS12_SW11 },  // 54
    {0, CS10_SW12,CS11_SW12,CS12_SW12 },  // 55
    {1, CS1_SW11, CS2_SW11, CS3_SW11  },  // 56
    {1, CS4_SW7,  CS5_SW7,  CS6_SW7   },  // 57

    {0, CS13_SW1, CS14_SW1, CS15_SW1  },  // 58
    {0, CS13_SW2, CS14_SW2, CS15_SW2  },  // 59
    {0, CS13_SW3, CS14_SW3, CS15_SW3  },  // 60
    {0, CS13_SW4, CS14_SW4, CS15_SW4  },  // 61
    {0, CS13_SW5, CS14_SW5, CS15_SW5  },  // 62
    {0, CS13_SW6, CS14_SW6, CS15_SW6  },  // 63
    {0, CS13_SW7, CS14_SW7, CS15_SW7  },  // 64
    {0, CS13_SW8, CS14_SW8, CS15_SW8  },  // 65
    {0, CS13_SW9, CS14_SW9, CS15_SW9  },  // 66
    {0, CS13_SW10,CS14_SW10,CS15_SW10 },  // 67
    {0, CS13_SW11,CS14_SW11,CS15_SW11 },  // 68
    {1, CS4_SW8,  CS5_SW8,  CS6_SW8   },  // 69
    {1, CS4_SW9,  CS5_SW9,  CS6_SW9   },  // 70

    {0, CS16_SW1, CS17_SW1,  CS18_SW1 },  // 71
    {0, CS16_SW2, CS17_SW2,  CS18_SW2 },  // 72
    {0, CS16_SW3, CS17_SW3,  CS18_SW3 },  // 73
    {0, CS16_SW6, CS17_SW6,  CS18_SW6 },  // 74
    {0, CS16_SW9, CS17_SW9,  CS18_SW9 },  // 75
    {0, CS16_SW10,CS17_SW10, CS18_SW10},  // 76
    {1, CS4_SW10 ,CS5_SW10,  CS6_SW10 },  // 77
    {1, CS4_SW11, CS5_SW11,  CS6_SW11 },  // 78
    {1, CS10_SW5, CS11_SW5,  CS12_SW5 },  // 79
};