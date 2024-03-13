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

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, SW1_CS1,  SW1_CS2,  SW1_CS3   },  // 0
    {0, SW2_CS1,  SW2_CS2,  SW2_CS3   },  // 1
    {0, SW3_CS1,  SW3_CS2,  SW3_CS3   },  // 2
    {0, SW4_CS1,  SW4_CS2,  SW4_CS3   },  // 3
    {0, SW5_CS1,  SW5_CS2,  SW5_CS3   },  // 4
    {0, SW6_CS1,  SW6_CS2,  SW6_CS3   },  // 5
    {0, SW7_CS1,  SW7_CS2,  SW7_CS3   },  // 6
    {0, SW8_CS1,  SW8_CS2,  SW8_CS3   },  // 7
    {0, SW9_CS1,  SW9_CS2,  SW9_CS3   },  // 8
    {0, SW10_CS1, SW10_CS2, SW10_CS3  },  // 9
    {0, SW11_CS1, SW11_CS2, SW11_CS3  },  // 10
    {0, SW12_CS1, SW12_CS2, SW12_CS3  },  // 11
    {1, SW1_CS1,  SW1_CS2,  SW1_CS3   },  // 12
    {1, SW2_CS1,  SW2_CS2,  SW2_CS3   },  // 13

    {0, SW1_CS4,  SW1_CS5,  SW1_CS6   },  // 14
    {0, SW2_CS4,  SW2_CS5,  SW2_CS6   },  // 15
    {0, SW3_CS4,  SW3_CS5,  SW3_CS6   },  // 16
    {0, SW4_CS4,  SW4_CS5,  SW4_CS6   },  // 17
    {0, SW5_CS4,  SW5_CS5,  SW5_CS6   },  // 18
    {0, SW6_CS4,  SW6_CS5,  SW6_CS6   },  // 19
    {0, SW7_CS4,  SW7_CS5,  SW7_CS6   },  // 20
    {0, SW8_CS4,  SW8_CS5,  SW8_CS6   },  // 21
    {0, SW9_CS4,  SW9_CS5,  SW9_CS6   },  // 22
    {0, SW10_CS4, SW10_CS5, SW10_CS6  },  // 23
    {0, SW11_CS4, SW11_CS5, SW11_CS6  },  // 24
    {0, SW12_CS4, SW12_CS5, SW12_CS6  },  // 25
    {1, SW5_CS1,  SW5_CS2,  SW5_CS3   },  // 26
    {1, SW7_CS1,  SW7_CS2,  SW7_CS3   },  // 27
    {1, SW3_CS4,  SW3_CS5,  SW3_CS6   },  // 28

    {0, SW1_CS7,  SW1_CS8,  SW1_CS9   },  // 29
    {0, SW2_CS7,  SW2_CS8,  SW2_CS9   },  // 30
    {0, SW3_CS7,  SW3_CS8,  SW3_CS9   },  // 31
    {0, SW4_CS7,  SW4_CS8,  SW4_CS9   },  // 32
    {0, SW5_CS7,  SW5_CS8,  SW5_CS9   },  // 33
    {0, SW6_CS7,  SW6_CS8,  SW6_CS9   },  // 34
    {0, SW7_CS7,  SW7_CS8,  SW7_CS9   },  // 35
    {0, SW8_CS7,  SW8_CS8,  SW8_CS9   },  // 36
    {0, SW9_CS7,  SW9_CS8,  SW9_CS9   },  // 37
    {0, SW10_CS7, SW10_CS8, SW10_CS9  },  // 38
    {0, SW11_CS7, SW11_CS8, SW11_CS9  },  // 39
    {0, SW12_CS7, SW12_CS8, SW12_CS9  },  // 40
    {1, SW8_CS1,  SW8_CS2,  SW8_CS3   },  // 41
    {1, SW9_CS1,  SW9_CS2,  SW9_CS3   },  // 42
    {1, SW4_CS4,  SW4_CS5,  SW4_CS6   },  // 43


    {0, SW1_CS10, SW1_CS11, SW1_CS12  },  // 44
    {0, SW2_CS10, SW2_CS11, SW2_CS12  },  // 45
    {0, SW3_CS10, SW3_CS11, SW3_CS12  },  // 46
    {0, SW4_CS10, SW4_CS11, SW4_CS12  },  // 47
    {0, SW5_CS10, SW5_CS11, SW5_CS12  },  // 48
    {0, SW6_CS10, SW6_CS11, SW6_CS12  },  // 49
    {0, SW7_CS10, SW7_CS11, SW7_CS12  },  // 50
    {0, SW8_CS10, SW8_CS11, SW8_CS12  },  // 51
    {0, SW9_CS10, SW9_CS11, SW9_CS12  },  // 52
    {0, SW10_CS10,SW10_CS11,SW10_CS12 },  // 53
    {0, SW11_CS10,SW11_CS11,SW11_CS12 },  // 54
    {0, SW12_CS10,SW12_CS11,SW12_CS12 },  // 55
    {1, SW11_CS1, SW11_CS2, SW11_CS3  },  // 56
    {1, SW7_CS4,  SW7_CS5,  SW7_CS6   },  // 57

    {0, SW1_CS13, SW1_CS14, SW1_CS15  },  // 58
    {0, SW2_CS13, SW2_CS14, SW2_CS15  },  // 59
    {0, SW3_CS13, SW3_CS14, SW3_CS15  },  // 60
    {0, SW4_CS13, SW4_CS14, SW4_CS15  },  // 61
    {0, SW5_CS13, SW5_CS14, SW5_CS15  },  // 62
    {0, SW6_CS13, SW6_CS14, SW6_CS15  },  // 63
    {0, SW7_CS13, SW7_CS14, SW7_CS15  },  // 64
    {0, SW8_CS13, SW8_CS14, SW8_CS15  },  // 65
    {0, SW9_CS13, SW9_CS14, SW9_CS15  },  // 66
    {0, SW10_CS13,SW10_CS14,SW10_CS15 },  // 67
    {0, SW11_CS13,SW11_CS14,SW11_CS15 },  // 68
    {1, SW8_CS4,  SW8_CS5,  SW8_CS6   },  // 69
    {1, SW9_CS4,  SW9_CS5,  SW9_CS6   },  // 70

    {0, SW1_CS16, SW1_CS17,  SW1_CS18 },  // 71
    {0, SW2_CS16, SW2_CS17,  SW2_CS18 },  // 72
    {0, SW3_CS16, SW3_CS17,  SW3_CS18 },  // 73
    {0, SW6_CS16, SW6_CS17,  SW6_CS18 },  // 74
    {0, SW9_CS16, SW9_CS17,  SW9_CS18 },  // 75
    {0, SW10_CS16,SW10_CS17, SW10_CS18},  // 76
    {1, SW10_CS4, SW10_CS5,  SW10_CS6 },  // 77
    {1, SW11_CS4, SW11_CS5,  SW11_CS6 },  // 78
    {1, SW5_CS10, SW5_CS11,  SW5_CS12 },  // 79
};