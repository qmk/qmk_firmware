/* Copyright (C) 2023 Westberry Technology Corp., Ltd
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
    {0, CS18_SW2,  CS17_SW2,  CS16_SW2   },  // 0  Esc
    {0, CS18_SW3,  CS17_SW3,  CS16_SW3   },  // 1  F1
    {0, CS18_SW4,  CS17_SW4,  CS16_SW4   },  // 2  F2
    {0, CS18_SW5,  CS17_SW5,  CS16_SW5   },  // 3  F3
    {0, CS18_SW6,  CS17_SW6,  CS16_SW6   },  // 4  F4
    {0, CS18_SW7,  CS17_SW7,  CS16_SW7   },  // 5  F5
    {0, CS18_SW8,  CS17_SW8,  CS16_SW8   },  // 6  F6
    {0, CS18_SW9,  CS17_SW9,  CS16_SW9   },  // 7  F7
    {0, CS18_SW10, CS17_SW10, CS16_SW10  },  // 8  F8
    {0, CS18_SW11, CS17_SW11, CS16_SW11  },  // 9  F9
    {0, CS18_SW12, CS17_SW12, CS16_SW12  },  // 10 F10
    {1, CS18_SW1,  CS17_SW1,  CS16_SW1   },  // 11 F11
    {1, CS18_SW2,  CS17_SW2,  CS16_SW2   },  // 12 F12
    {1, CS18_SW3,  CS17_SW3,  CS16_SW3   },  // 13 MUTE
    {1, CS18_SW4,  CS17_SW4,  CS16_SW4   },  // 14 PSCR
    {1, CS18_SW5,  CS17_SW5,  CS16_SW5   },  // 15 SCRL
    {1, CS18_SW6,  CS17_SW6,  CS16_SW6   },  // 16 PAUSE

    {0, CS15_SW2,  CS14_SW2,  CS13_SW2   },  // 17 `~
    {0, CS15_SW3,  CS14_SW3,  CS13_SW3   },  // 18 1
    {0, CS15_SW4,  CS14_SW4,  CS13_SW4   },  // 19 2
    {0, CS15_SW5,  CS14_SW5,  CS13_SW5   },  // 20 3
    {0, CS15_SW6,  CS14_SW6,  CS13_SW6   },  // 21 4
    {0, CS15_SW7,  CS14_SW7,  CS13_SW7   },  // 22 5
    {0, CS15_SW8,  CS14_SW8,  CS13_SW8   },  // 23 6
    {0, CS15_SW9,  CS14_SW9,  CS13_SW9   },  // 24 7
    {0, CS15_SW10, CS14_SW10, CS13_SW10  },  // 25 8
    {0, CS15_SW11, CS14_SW11, CS13_SW11  },  // 26 9
    {0, CS15_SW12, CS14_SW12, CS13_SW12  },  // 27 0
    {1, CS15_SW1,  CS14_SW1,  CS13_SW1   },  // 28 -_
    {1, CS15_SW2,  CS14_SW2,  CS13_SW2   },  // 29 =+
    {1, CS15_SW3,  CS14_SW3,  CS13_SW3   },  // 30 BSPC
    {1, CS15_SW4,  CS14_SW4,  CS13_SW4   },  // 31 INS
    {1, CS15_SW5,  CS14_SW5,  CS13_SW5   },  // 32 HOME
    {1, CS15_SW6,  CS14_SW6,  CS13_SW6   },  // 33 PGUP

    {0, CS12_SW2,  CS11_SW2,  CS10_SW2   },  // 34 Tab
    {0, CS12_SW3,  CS11_SW3,  CS10_SW3   },  // 35 Q
    {0, CS12_SW4,  CS11_SW4,  CS10_SW4   },  // 36 W
    {0, CS12_SW5,  CS11_SW5,  CS10_SW5   },  // 37 E
    {0, CS12_SW6,  CS11_SW6,  CS10_SW6   },  // 38 R
    {0, CS12_SW7,  CS11_SW7,  CS10_SW7   },  // 39 T
    {0, CS12_SW8,  CS11_SW8,  CS10_SW8   },  // 40 Y
    {0, CS12_SW9,  CS11_SW9,  CS10_SW9   },  // 41 U
    {0, CS12_SW10, CS11_SW10, CS10_SW10  },  // 42 I
    {0, CS12_SW11, CS11_SW11, CS10_SW11  },  // 43 O
    {0, CS12_SW12, CS11_SW12, CS10_SW12  },  // 44 P
    {1, CS12_SW1,  CS11_SW1,  CS10_SW1   },  // 45 [{
    {1, CS12_SW2,  CS11_SW2,  CS10_SW2   },  // 48 ]}
    {1, CS12_SW3,  CS11_SW3,  CS10_SW3   },  // 47 \|
    {1, CS12_SW4,  CS11_SW4,  CS10_SW4   },  // 48 Del
    {1, CS12_SW5,  CS11_SW5,  CS10_SW5   },  // 49 End
    {1, CS12_SW6,  CS11_SW6,  CS10_SW6   },  // 50 PGDN

    {0, CS1_SW2,   CS2_SW2,   CS3_SW2    },  // 51 Caps
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3    },  // 52 A
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4    },  // 33 S
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5    },  // 54 D
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6    },  // 55 F
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7    },  // 56 G
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8    },  // 57 H
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9    },  // 58 J
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10   },  // 59 K
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11   },  // 60 L
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12   },  // 61 ;:
    {1, CS1_SW1,   CS2_SW1,   CS3_SW1    },  // 62 '
    {1, CS1_SW3,   CS2_SW3,   CS3_SW3    },  // 63 Enter

    {0, CS4_SW2,   CS5_SW2,   CS6_SW2    },  // 64 Shift
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4    },  // 65 Z
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5    },  // 66 X
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6    },  // 67 C
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7    },  // 68 V
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8    },  // 69 B
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9    },  // 70 N
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10   },  // 71 M
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11   },  // 72 ,<
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12   },  // 73 .>
    {1, CS4_SW1,   CS5_SW1,   CS6_SW1    },  // 74 ?
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3    },  // 75 Shift
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5    },  // 76 Up

    {0, CS7_SW2,   CS8_SW2,   CS9_SW2    },  // 77 Ctrl_L
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3    },  // 78 Win_L
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4    },  // 79 ALT_L
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8    },  // 80 SPACE
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12   },  // 81 ALT_L
    {1, CS7_SW1,   CS8_SW1,   CS9_SW1    },  // 82 Win_L
    {1, CS7_SW2,   CS8_SW2,   CS9_SW2    },  // 83 Fn
    {1, CS7_SW3,   CS8_SW3,   CS9_SW3    },  // 84 Ctrl_L
    {1, CS7_SW4,   CS8_SW4,   CS9_SW4    },  // 85 Left
    {1, CS7_SW5,   CS8_SW5,   CS9_SW5    },  // 86 Down
    {1, CS7_SW6,   CS8_SW6,   CS9_SW6    },  // 87 Right
};
