/* Copyright 2021 Harrison Chan (Xelus)
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

#include "rgb.h"
#include <hal.h>
#include <ch.h>

// tested and working
void matrix_io_delay(void) { __asm__ volatile("nop\nnop\nnop\n"); }

#ifdef RGB_MATRIX_ENABLE
#include <i2c_master.h>
#include "drivers/led/issi/is31fl3741.h"
const is31_led __flash g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |         G location
 *   |  |         |         B location
 *   |  |         |         | */
    {0, CS39_SW1, CS38_SW1, CS37_SW1}, //A1
    {0, CS36_SW1, CS35_SW1, CS34_SW1}, //A2
    {0, CS33_SW1, CS32_SW1, CS31_SW1}, //A3
    {0, CS30_SW1, CS29_SW1, CS28_SW1}, //A4
    {0, CS27_SW1, CS26_SW1, CS25_SW1}, //A5
    {0, CS24_SW1, CS23_SW1, CS22_SW1}, //A6
    {0, CS21_SW1, CS20_SW1, CS19_SW1}, //A7
    {0, CS18_SW1, CS17_SW1, CS16_SW1}, //A8
    {0, CS15_SW1, CS14_SW1, CS13_SW1}, //A9
    {0, CS12_SW1, CS11_SW1, CS10_SW1}, //A10
    {0, CS9_SW1 , CS8_SW1 , CS7_SW1 }, //A11
    {0, CS6_SW1 , CS5_SW1 , CS4_SW1 }, //A12
    {0, CS3_SW1 , CS2_SW1 , CS1_SW1 }, //A13

    {0, CS39_SW2, CS38_SW2, CS37_SW2}, //B1
    {0, CS36_SW2, CS35_SW2, CS34_SW2}, //B2
    {0, CS33_SW2, CS32_SW2, CS31_SW2}, //B3
    {0, CS30_SW2, CS29_SW2, CS28_SW2}, //B4
    {0, CS27_SW2, CS26_SW2, CS25_SW2}, //B5
    {0, CS24_SW2, CS23_SW2, CS22_SW2}, //B6
    {0, CS21_SW2, CS20_SW2, CS19_SW2}, //B7
    {0, CS18_SW2, CS17_SW2, CS16_SW2}, //B8
    {0, CS15_SW2, CS14_SW2, CS13_SW2}, //B9
    {0, CS12_SW2, CS11_SW2, CS10_SW2}, //B10
    {0, CS9_SW2 , CS8_SW2 , CS7_SW2 }, //B11
    {0, CS6_SW2 , CS5_SW2 , CS4_SW2 }, //B12
    {0, CS3_SW2 , CS2_SW2 , CS1_SW2 }, //B13

    {0, CS39_SW3, CS38_SW3, CS37_SW3}, //C1
    {0, CS36_SW3, CS35_SW3, CS34_SW3}, //C2
    {0, CS33_SW3, CS32_SW3, CS31_SW3}, //C3
    {0, CS30_SW3, CS29_SW3, CS28_SW3}, //C4
    {0, CS27_SW3, CS26_SW3, CS25_SW3}, //C5
    {0, CS24_SW3, CS23_SW3, CS22_SW3}, //C6
    {0, CS21_SW3, CS20_SW3, CS19_SW3}, //C7
    {0, CS18_SW3, CS17_SW3, CS16_SW3}, //C8
    {0, CS15_SW3, CS14_SW3, CS13_SW3}, //C9
    {0, CS12_SW3, CS11_SW3, CS10_SW3}, //C10
    {0, CS9_SW3 , CS8_SW3 , CS7_SW3 }, //C11
    {0, CS6_SW3 , CS5_SW3 , CS4_SW3 }, //C12
    {0, CS3_SW3 , CS2_SW3 , CS1_SW3 }, //C13

    {0, CS39_SW4, CS38_SW4, CS37_SW4}, //D1
    {0, CS36_SW4, CS35_SW4, CS34_SW4}, //D2
    {0, CS33_SW4, CS32_SW4, CS31_SW4}, //D3
    {0, CS30_SW4, CS29_SW4, CS28_SW4}, //D4
    {0, CS27_SW4, CS26_SW4, CS25_SW4}, //D5
    {0, CS24_SW4, CS23_SW4, CS22_SW4}, //D6
    {0, CS21_SW4, CS20_SW4, CS19_SW4}, //D7
    {0, CS18_SW4, CS17_SW4, CS16_SW4}, //D8
    {0, CS15_SW4, CS14_SW4, CS13_SW4}, //D9
    {0, CS12_SW4, CS11_SW4, CS10_SW4}, //D10
    {0, CS9_SW4 , CS8_SW4 , CS7_SW4 }, //D11
    {0, CS6_SW4 , CS5_SW4 , CS4_SW4 }, //D12
    {0, CS3_SW4 , CS2_SW4 , CS1_SW4 }, //D13

    {0, CS39_SW5, CS38_SW5, CS37_SW5}, //E1
    {0, CS36_SW5, CS35_SW5, CS34_SW5}, //E2
    {0, CS33_SW5, CS32_SW5, CS31_SW5}, //E3
    {0, CS30_SW5, CS29_SW5, CS28_SW5}, //E4
    {0, CS27_SW5, CS26_SW5, CS25_SW5}, //E5
    {0, CS24_SW5, CS23_SW5, CS22_SW5}, //E6
    {0, CS21_SW5, CS20_SW5, CS19_SW5}, //E7
    {0, CS18_SW5, CS17_SW5, CS16_SW5}, //E8
    {0, CS15_SW5, CS14_SW5, CS13_SW5}, //E9
    {0, CS12_SW5, CS11_SW5, CS10_SW5}, //E10
    {0, CS9_SW5 , CS8_SW5 , CS7_SW5 }, //E11
    {0, CS6_SW5 , CS5_SW5 , CS4_SW5 }, //E12
    {0, CS3_SW5 , CS2_SW5 , CS1_SW5 }, //E13

    {0, CS39_SW6, CS38_SW6, CS37_SW6}, //F1
    {0, CS36_SW6, CS35_SW6, CS34_SW6}, //F2
    {0, CS33_SW6, CS32_SW6, CS31_SW6}, //F3
    {0, CS30_SW6, CS29_SW6, CS28_SW6}, //F4
    {0, CS27_SW6, CS26_SW6, CS25_SW6}, //F5
    {0, CS24_SW6, CS23_SW6, CS22_SW6}, //F6
    {0, CS21_SW6, CS20_SW6, CS19_SW6}, //F7
    {0, CS18_SW6, CS17_SW6, CS16_SW6}, //F8
    {0, CS15_SW6, CS14_SW6, CS13_SW6}, //F9
    {0, CS12_SW6, CS11_SW6, CS10_SW6}, //F10
    {0, CS9_SW6 , CS8_SW6 , CS7_SW6 }, //F11
    {0, CS6_SW6 , CS5_SW6 , CS4_SW6 }, //F12
    {0, CS3_SW6 , CS2_SW6 , CS1_SW6 }, //F13

    {0, CS39_SW7, CS38_SW7, CS37_SW7}, //G1
    {0, CS36_SW7, CS35_SW7, CS34_SW7}, //G2
    {0, CS33_SW7, CS32_SW7, CS31_SW7}, //G3
    {0, CS30_SW7, CS29_SW7, CS28_SW7}, //G4
    {0, CS27_SW7, CS26_SW7, CS25_SW7}, //G5
    {0, CS24_SW7, CS23_SW7, CS22_SW7}, //G6
    {0, CS21_SW7, CS20_SW7, CS19_SW7}, //G7
    {0, CS18_SW7, CS17_SW7, CS16_SW7}, //G8
    {0, CS15_SW7, CS14_SW7, CS13_SW7}, //G9
    {0, CS12_SW7, CS11_SW7, CS10_SW7}, //G10
    {0, CS9_SW7 , CS8_SW7 , CS7_SW7 }, //G11
    {0, CS6_SW7 , CS5_SW7 , CS4_SW7 }, //G12
    {0, CS3_SW7 , CS2_SW7 , CS1_SW7 }, //G13

    {0, CS39_SW8, CS38_SW8, CS37_SW8}, //H1
    {0, CS36_SW8, CS35_SW8, CS34_SW8}, //H2
    {0, CS33_SW8, CS32_SW8, CS31_SW8}, //H3
    {0, CS30_SW8, CS29_SW8, CS28_SW8}, //H4
    {0, CS27_SW8, CS26_SW8, CS25_SW8}, //H5
    {0, CS24_SW8, CS23_SW8, CS22_SW8}, //H6
    {0, CS21_SW8, CS20_SW8, CS19_SW8}, //H7
    {0, CS18_SW8, CS17_SW8, CS16_SW8}, //H8
    {0, CS15_SW8, CS14_SW8, CS13_SW8}, //H9
    {0, CS12_SW8, CS11_SW8, CS10_SW8}, //H10
    {0, CS9_SW8 , CS8_SW8 , CS7_SW8 }, //H11
    {0, CS6_SW8 , CS5_SW8 , CS4_SW8 }, //H12
    {0, CS3_SW8 , CS2_SW8 , CS1_SW8 }, //H13

    {0, CS39_SW9, CS38_SW9, CS37_SW9}, //I1
    {0, CS36_SW9, CS35_SW9, CS34_SW9}, //I2
    {0, CS33_SW9, CS32_SW9, CS31_SW9}, //I3
    {0, CS30_SW9, CS29_SW9, CS28_SW9}, //I4
    {0, CS27_SW9, CS26_SW9, CS25_SW9}, //I5
    {0, CS24_SW9, CS23_SW9, CS22_SW9}, //I6
    {0, CS21_SW9, CS20_SW9, CS19_SW9}, //I7
    {0, CS18_SW9, CS17_SW9, CS16_SW9}, //I8
    {0, CS15_SW9, CS14_SW9, CS13_SW9}, //I9
    {0, CS12_SW9, CS11_SW9, CS10_SW9}, //I10
    {0, CS9_SW9 , CS8_SW9 , CS7_SW9 }, //I11
    {0, CS6_SW9 , CS5_SW9 , CS4_SW9 }, //I12
    {0, CS3_SW9 , CS2_SW9 , CS1_SW9 }  //I13
};

__attribute__ ((weak))
led_config_t g_led_config = { {
    { -1+00+3 , NO_LED,   -1+26+3 , -1+39+3 , -1+52+3 , -1+65+3 , -1+78+3 , -1+91+3 , -1+104+3 , -1+00+1 , -1+13+1 , -1+26+1 , -1+39+1 , -1+52+1 , -1+65+1 , -1+78+1 , -1+91+1 },
    { -1+00+4 , -1+13+4 , -1+26+4 , -1+39+4 , -1+52+4 , -1+65+4 , -1+78+4 , -1+91+4 , -1+104+4 , -1+00+2 , -1+13+2 , -1+26+2 , -1+39+2 , -1+52+2 , -1+65+2 , -1+78+2 , -1+91+2 },
    { -1+00+6 , -1+13+6 , -1+26+6 , -1+39+6 , -1+52+6 , -1+65+6 , -1+78+6 , -1+91+6 , -1+104+6 , -1+00+5 , -1+13+5 , -1+26+5 , -1+39+5 , -1+52+5 , -1+65+5 , -1+78+5 , -1+91+6 },
    { -1+00+8 , -1+13+8 , -1+26+8 , -1+39+8 , -1+52+8 , -1+65+8 , -1+78+8 , -1+91+8 , -1+104+8 , -1+00+7 , -1+13+7 , -1+26+7 , NO_LED  , -1+52+7 , NO_LED  , NO_LED  , NO_LED  },
    { -1+00+11, -1+13+11, -1+26+11, -1+39+11, -1+52+11, -1+65+11, -1+78+11, -1+91+11, -1+104+11, -1+00+10, -1+13+10, NO_LED  , -1+52+10, NO_LED  , NO_LED  , -1+78+10, NO_LED  },
    { -1+00+9 , -1+13+9 , -1+26+9 , NO_LED  , NO_LED  , -1+65+9 , NO_LED  , NO_LED  , NO_LED   , NO_LED  , -1+13+12, NO_LED  , -1+39+12, -1+52+12, -1+65+12, -1+78+12, -1+91+12}
}, {
    {123,  0}, {117, 15}, {0  ,  0}, {0  , 15}, {123, 27}, {3  , 27}, {127, 40}, {5  , 40}, {2  , 64}, {133, 52}, {8  , 52}, {131, 64}, {255,255},
    {143,  0}, {130, 15}, {255,255}, {13 , 15}, {136, 27}, {19 , 27}, {140, 40}, {23 , 40}, {18 , 64}, {146, 52}, {29 , 52}, {148, 64}, {255,255},
    {156,  0}, {143, 15}, {26 ,  0}, {26 , 15}, {149, 27}, {32 , 27}, {153, 40}, {36 , 40}, {34 , 64}, {255,255}, {42 , 52}, {255,255}, {255,255},
    {169,  0}, {156, 15}, {39 ,  0}, {39 , 15}, {162, 27}, {45 , 27}, {255,255}, {49 , 40}, {255,255}, {255,255}, {55 , 52}, {164, 64}, {255,255},
    {182,  0}, {175, 15}, {52 ,  0}, {52 , 15}, {179, 27}, {58 , 27}, {174, 40}, {62 , 40}, {255,255}, {170, 52}, {68 , 52}, {180, 64}, {255,255},
    {198,  0}, {198, 15}, {65 ,  0}, {65 , 15}, {198, 27}, {71 , 27}, {255,255}, {75 , 40}, {83 , 64}, {255,255}, {81 , 52}, {198, 64}, {255,255},
    {211,  0}, {211, 15}, {84 ,  0}, {78 , 15}, {211, 27}, {84 , 27}, {255,255}, {88 , 40}, {255,255}, {211, 52}, {94 , 52}, {211, 64}, {255,255},
    {224,  0}, {224, 15}, {97 ,  0}, {91 , 15}, {224, 27}, {97 , 27}, {255,255}, {101, 40}, {255,255}, {255,255}, {107, 52}, {224, 64}, {255,255},
    {255,255}, {255,255}, {110,  0}, {104, 15}, {255,255}, {110, 27}, {255,255}, {114, 40}, {255,255}, {255,255}, {120, 52}, {255,255}, {255,255}
}, {
    1, 4, 1, 1, 4, 1, 4, 1, 1, 4, 1, 4, 4,  //0-12
    1, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 1, 4,  //13-25
    1, 4, 1, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4,  //26-38
    1, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4,  //39-51
    1, 1, 1, 4, 1, 4, 1, 4, 4, 1, 4, 1, 4,  //52-64
    1, 1, 1, 4, 1, 4, 4, 4, 1, 4, 4, 1, 4,  //65-77
    1, 1, 1, 4, 1, 4, 4, 4, 4, 1, 4, 1, 4,  //78-90
    1, 1, 1, 4, 1, 4, 4, 4, 4, 4, 4, 1, 4,  //91-103
    4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4   //104-116
} };

static void init(void) {
    i2c_init();
    IS31FL3741_init(DRIVER_ADDR_1);
    for (int index = 0; index < ISSI_DRIVER_TOTAL; index++) {
        bool enabled = !(   ( index == -1+0+13) || //A13
                            ( index == -1+13+3) || //B3
                            ( index == -1+13+13) || //B13
                            ( index == -1+26+10) || //C10
                            ( index == -1+26+12) || //C12
                            ( index == -1+26+13) || //C13
                            ( index == -1+39+7) || //D7
                            ( index == -1+39+9) || //D9
                            ( index == -1+39+10) || //D10
                            ( index == -1+39+13) || //D13
                            ( index == -1+52+9) || //E9
                            ( index == -1+52+13) || //E13
                            ( index == -1+65+7) || //F7
                            ( index == -1+65+10) || //F10
                            ( index == -1+65+13) || //F13
                            ( index == -1+78+7) || //G7
                            ( index == -1+78+9) || //G9
                            ( index == -1+78+13) || //G13
                            ( index == -1+91+7) || //H7
                            ( index == -1+91+9) || //H9
                            ( index == -1+91+10) || //H10
                            ( index == -1+91+13) || //H13
                            ( index == -1+104+1) || //I1
                            ( index == -1+104+2) || //I2
                            ( index == -1+104+5) || //I5
                            ( index == -1+104+7) || //I7
                            ( index == -1+104+9) || //I9
                            ( index == -1+104+10) || //I10
                            ( index == -1+104+12) || //I12
                            ( index == -1+104+13) //I13
                        );
        IS31FL3741_set_led_control_register(index, enabled, enabled, enabled);
    }
    IS31FL3741_update_led_control_registers(DRIVER_ADDR_1, 0);
}

static void flush(void) {
    IS31FL3741_update_pwm_buffers(DRIVER_ADDR_1, 0);
    // Just for reference. Only first driver is used? 
    // IS31FL3741_update_pwm_buffers(DRIVER_ADDR_2, 1);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3741_set_color,
    .set_color_all = IS31FL3741_set_color_all
};
#endif
