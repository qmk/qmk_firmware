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
    {0, SW2_CS18,  SW2_CS17,  SW2_CS16   },  // 0  Esc
    {0, SW3_CS18,  SW3_CS17,  SW3_CS16   },  // 1  F1
    {0, SW4_CS18,  SW4_CS17,  SW4_CS16   },  // 2  F2
    {0, SW5_CS18,  SW5_CS17,  SW5_CS16   },  // 3  F3
    {0, SW6_CS18,  SW6_CS17,  SW6_CS16   },  // 4  F4
    {0, SW7_CS18,  SW7_CS17,  SW7_CS16   },  // 5  F5
    {0, SW8_CS18,  SW8_CS17,  SW8_CS16   },  // 6  F6
    {0, SW9_CS18,  SW9_CS17,  SW9_CS16   },  // 7  F7
    {0, SW10_CS18, SW10_CS17, SW10_CS16  },  // 8  F8
    {0, SW11_CS18, SW11_CS17, SW11_CS16  },  // 9  F9
    {0, SW12_CS18, SW12_CS17, SW12_CS16  },  // 10 F10
    {1, SW1_CS18,  SW1_CS17,  SW1_CS16   },  // 11 F11
    {1, SW2_CS18,  SW2_CS17,  SW2_CS16   },  // 12 F12
    {1, SW3_CS18,  SW3_CS17,  SW3_CS16   },  // 13 MUTE
    {1, SW4_CS18,  SW4_CS17,  SW4_CS16   },  // 14 PSCR
    {1, SW5_CS18,  SW5_CS17,  SW5_CS16   },  // 15 SCRL
    {1, SW6_CS18,  SW6_CS17,  SW6_CS16   },  // 16 PAUSE

    {0, SW2_CS15,  SW2_CS14,  SW2_CS13   },  // 17 `~
    {0, SW3_CS15,  SW3_CS14,  SW3_CS13   },  // 18 1
    {0, SW4_CS15,  SW4_CS14,  SW4_CS13   },  // 19 2
    {0, SW5_CS15,  SW5_CS14,  SW5_CS13   },  // 20 3
    {0, SW6_CS15,  SW6_CS14,  SW6_CS13   },  // 21 4
    {0, SW7_CS15,  SW7_CS14,  SW7_CS13   },  // 22 5
    {0, SW8_CS15,  SW8_CS14,  SW8_CS13   },  // 23 6
    {0, SW9_CS15,  SW9_CS14,  SW9_CS13   },  // 24 7
    {0, SW10_CS15, SW10_CS14, SW10_CS13  },  // 25 8
    {0, SW11_CS15, SW11_CS14, SW11_CS13  },  // 26 9
    {0, SW12_CS15, SW12_CS14, SW12_CS13  },  // 27 0
    {1, SW1_CS15,  SW1_CS14,  SW1_CS13   },  // 28 -_
    {1, SW2_CS15,  SW2_CS14,  SW2_CS13   },  // 29 =+
    {1, SW3_CS15,  SW3_CS14,  SW3_CS13   },  // 30 BSPC
    {1, SW4_CS15,  SW4_CS14,  SW4_CS13   },  // 31 INS
    {1, SW5_CS15,  SW5_CS14,  SW5_CS13   },  // 32 HOME
    {1, SW6_CS15,  SW6_CS14,  SW6_CS13   },  // 33 PGUP

    {0, SW2_CS12,  SW2_CS11,  SW2_CS10   },  // 34 Tab
    {0, SW3_CS12,  SW3_CS11,  SW3_CS10   },  // 35 Q
    {0, SW4_CS12,  SW4_CS11,  SW4_CS10   },  // 36 W
    {0, SW5_CS12,  SW5_CS11,  SW5_CS10   },  // 37 E
    {0, SW6_CS12,  SW6_CS11,  SW6_CS10   },  // 38 R
    {0, SW7_CS12,  SW7_CS11,  SW7_CS10   },  // 39 T
    {0, SW8_CS12,  SW8_CS11,  SW8_CS10   },  // 40 Y
    {0, SW9_CS12,  SW9_CS11,  SW9_CS10   },  // 41 U
    {0, SW10_CS12, SW10_CS11, SW10_CS10  },  // 42 I
    {0, SW11_CS12, SW11_CS11, SW11_CS10  },  // 43 O
    {0, SW12_CS12, SW12_CS11, SW12_CS10  },  // 44 P
    {1, SW1_CS12,  SW1_CS11,  SW1_CS10   },  // 45 [{
    {1, SW2_CS12,  SW2_CS11,  SW2_CS10   },  // 48 ]}
    {1, SW3_CS12,  SW3_CS11,  SW3_CS10   },  // 47 \|
    {1, SW4_CS12,  SW4_CS11,  SW4_CS10   },  // 48 Del
    {1, SW5_CS12,  SW5_CS11,  SW5_CS10   },  // 49 End
    {1, SW6_CS12,  SW6_CS11,  SW6_CS10   },  // 50 PGDN

    {0, SW2_CS1,   SW2_CS2,   SW2_CS3    },  // 51 Caps
    {0, SW3_CS1,   SW3_CS2,   SW3_CS3    },  // 52 A
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3    },  // 33 S
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3    },  // 54 D
    {0, SW6_CS1,   SW6_CS2,   SW6_CS3    },  // 55 F
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3    },  // 56 G
    {0, SW8_CS1,   SW8_CS2,   SW8_CS3    },  // 57 H
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3    },  // 58 J
    {0, SW10_CS1,  SW10_CS2,  SW10_CS3   },  // 59 K
    {0, SW11_CS1,  SW11_CS2,  SW11_CS3   },  // 60 L
    {0, SW12_CS1,  SW12_CS2,  SW12_CS3   },  // 61 ;:
    {1, SW1_CS1,   SW1_CS2,   SW1_CS3    },  // 62 '
    {1, SW3_CS1,   SW3_CS2,   SW3_CS3    },  // 63 Enter

    {0, SW2_CS4,   SW2_CS5,   SW2_CS6    },  // 64 Shift
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6    },  // 65 Z
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6    },  // 66 X
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6    },  // 67 C
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6    },  // 68 V
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6    },  // 69 B
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6    },  // 70 N
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6   },  // 71 M
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6   },  // 72 ,<
    {0, SW12_CS4,  SW12_CS5,  SW12_CS6   },  // 73 .>
    {1, SW1_CS4,   SW1_CS5,   SW1_CS6    },  // 74 ?
    {1, SW3_CS4,   SW3_CS5,   SW3_CS6    },  // 75 Shift
    {1, SW5_CS4,   SW5_CS5,   SW5_CS6    },  // 76 Up

    {0, SW2_CS7,   SW2_CS8,   SW2_CS9    },  // 77 Ctrl_L
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9    },  // 78 Win_L
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9    },  // 79 ALT_L
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9    },  // 80 SPACE
    {0, SW12_CS7,  SW12_CS8,  SW12_CS9   },  // 81 ALT_L
    {1, SW1_CS7,   SW1_CS8,   SW1_CS9    },  // 82 Win_L
    {1, SW2_CS7,   SW2_CS8,   SW2_CS9    },  // 83 Fn
    {1, SW3_CS7,   SW3_CS8,   SW3_CS9    },  // 84 Ctrl_L
    {1, SW4_CS7,   SW4_CS8,   SW4_CS9    },  // 85 Left
    {1, SW5_CS7,   SW5_CS8,   SW5_CS9    },  // 86 Down
    {1, SW6_CS7,   SW6_CS8,   SW6_CS9    },  // 87 Right
};
