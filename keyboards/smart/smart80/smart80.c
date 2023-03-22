/* Copyright 2021 Gigahawk
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
#include "smart80.h"
#include "uart.h"
//#include "bootloader.h"
extern uint8_t keyboard_led_state;


void board_init(void) {
    uart_init(115200);
    uart_write('s');
}

__attribute__((weak)) void bootloader_jump(void) {
    BKP->DR1 = 0x4F42;
    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {}

__attribute__((weak)) void enter_bootloader_mode_if_requested(void) {}


void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 2);
    matrix_scan();

    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
      // Jump to bootloader.
      
        bootloader_jump();
        while (1) ;
     
    }
}


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        
        rgb_matrix_set_color(3, 99, 99, 22);
    } else {
        rgb_matrix_set_color(3, 0,0,0);
    }

    return true;
}

uint8_t button_flag = 0; //按下标志位  0未按下 1按下
uint8_t keymap_num11[3] = {0x55, 0x00, 0x01};
uint8_t keymap_num22[3] = {0x55, 0x00, 0x00};
uint8_t msg[3] ={0x55,0x55,0x55};


/*
bool process_record_kb(uint16_t keycode, keyrecord_t* record) {


    if IS_ANY (keycode) // #define IS_ANY(code) (KC_A <= (code) && (code) <= 0xFF)
        {
            if (readPin(B14)) {
            
            uart_write(0x55);
            uart_write(keycode);
            uart_write(record->event.pressed);
            

            return false;
            }

        }

    return process_record_user(keycode, record);
        
}
*/

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = {{
// LED 对应到键盘矩阵，index从0开始，没有灯的地方写 NO_LED


    /*
    #define LAYOUT( \
    K00,      K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,   K0D, K0E, K3D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,   K5B, K5C, K3E, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,   K2E, K5D, K5E, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3C,                  \
    K40,      K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,      K4B,        K4C,      \
    K50, K51, K52,                K53,                K54, K55, K56, K57,   K58, K59, K5A  \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   KC_NO }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E   }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48,   K49,   K4A,   K4B,   K4C,   KC_NO, KC_NO }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58,   K59,   K5A,   K5B,   K5C,   K5D,   K5E   }, \
}

    */
    /*  0      1      2      3      4      5      6      7      8      9     10     11     12     13     14  */
     {  0,     6,    12,    18,    23,    28,    34,    39,    44,    50,    56,    62,    68,    74,    78}, 
     {  1,     7,    13,    19,    24,    29,    35,    40,    45,    51,    57,    63,    69,    72,NO_LED},
     {  2,     8,    14,    20,    25,    30,    36,    41,    46,    52,    58,    64,    70,    73,    76},
     {  3,     9,    15,    21,    26,    31,    37,    42,    47,    53,    59,    65,    71,    83,    84},
     {  4,    10,    16,    22,    27,    32,    38,    43,    48,    54,    60,    66,    81,NO_LED,NO_LED},
     {  5,    11,    17,    33,    49,    55,    61,    67,    77,    82,    86,    75,    79,    80,    85}


}, {
    {0, 0},     // 0, ESC, k00
    {0, 17},    // 1, ~, k10
    {3, 29},    // 2, Tab, k20
    {5, 41},    // 3, Caps, k30
    {8, 52},    // 4, Sh_L, k40
    {2, 64},    // 5, Ct_L, k50

    {26, 0},    // 6, F1, k01
    {13, 17},   // 7, 1, k11
    {19, 29},   // 8, Q, k21
    {23, 41},   // 9, A, k31
    {29, 52},   // 10, Z, k41
    {18, 64},   // 11, Win_L, k51

    {39, 0},    // 12, F2, k02
    {26, 17},   // 13, 2, k12
    {32, 29},   // 14, W, k22
    {36, 41},   // 15, S, k32
    {42, 52},   // 16, X, k42
    {34, 64},   // 17, Alt_L, k52

    {52, 0},    // 18, F3, k03
    {39, 17},   // 19, 3, k13
    {45, 29},   // 20, E, k23
    {49, 41},   // 21, D, k33
    {55, 52},   // 22, C, k43

    {65, 0},    // 23, F4, k04
    {52, 17},   // 24, 4, k14
    {58, 29},   // 25, R, k24
    {62, 41},   // 26, F, k34
    {68, 52},   // 27, V, k44

    {84, 0},    // 28, F5, k05
    {65, 17},   // 29, 5, k15
    {71, 29},   // 30, T, k25
    {75, 41},   // 31, G, k35
    {81, 52},   // 32, B, k45
    {83, 64},   // 33, SPACE, k53

    {97, 0},    // 34, F6, k06
    {78, 17},   // 35, 6, k16
    {84, 29},   // 36, Y, k26
    {88, 41},   // 37, H, k36
    {94, 52},  // 38, N, k46

    {110, 0},   // 39, F7, k07
    {91, 17},  // 40, 7, k17
    {97, 29},  // 41, U, k27
    {101, 41},  // 42, J, k37
    {107, 52},  // 43, M, k47

    {123, 0},   // 44, F8, k08
    {104, 17},  // 45, 8, k18
    {110, 29},  // 46, I, k28
    {114, 41},  // 47, K, k38
    {120, 52},  // 48, ,, k48
    {131, 64},  // 49, Alt_R, k51

    {143, 0},   // 50, F9, k09
    {117, 17},  // 51, 9, k19
    {123, 29},  // 52, O, k29
    {127, 41},  // 53, L, k39
    {133, 52},  // 54, ., k49
    {148, 64},  // 55, FN, k55

    {156, 0},   // 56, F10, k0A
    {130, 17},  // 57, 0, k1A
    {136, 29},  // 58, P, k2A
    {140, 41},  // 59, ;, k3A
    {146, 52},  // 60, ?, k4A
    {164, 64},  // 61, Menu, k56


    {169, 0},   // 62, F11, k0B
    {143, 17},  // 63, -, k1B
    {149, 29},  // 64, [, k2B
    {152, 41},  // 65, ", k3B

    {170, 52},  // 66, Sh_R, k4B
    {180, 64},  // 67, Ct_R, k57


    {182, 0},   // 68, F12, k0C
    {156, 17},     // 69, +, k1C
    {162, 29},   // 70, ], k2C
    {177, 41},   // 71, Enter, k3C
    {175, 17},    // 72, BSpc, k1E
    {178, 29},  // 73, \\,  k2D

    {198, 0},  // 74, PrtSc, k0D
    {198, 17},    // 75, Ins, k5B
    {198, 29},  // 76, Del, k2E
    {198, 64},  // 77, ←, k58
    {211, 0},    // 78, Scr, k0E
    {211, 17},  // 79, Home, k5C
    {211, 29},  // 80, End, k5D
    {211, 52},  // 81, ↑, k4C
    {211, 64},    // 82, ↓, k59

    {224, 0},  // 83, Pau,k3D 
    {224, 17},  // 84, PgUp, k3E
    {224, 29},    // 85, PgDn, k5E
    {224, 64},  // 86, →, k5A

    {200, 40},   //87 CHARGE
    {200, 40},    //88 CAPS
  
},
// 分组，如果没有自己做灯光的需求用处其实不大 
 {
    4, 4, 4, 3, 1, 1, 4, 4, 4, 4,//0-9
    4, 1, 4, 4, 4, 4, 4, 1, 4, 4,//10-19
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,//20-29
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,//30-39
    4, 4, 4, 4, 4, 4, 4, 4, 4, 1,//40-49
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,//50-59
    4, 4, 4, 4, 4, 4, 1, 1, 4, 4,//60-69
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,//70-79
    4, 4, 4, 4, 4, 4, 4, 8, 8    //80-88

}};

const aw_led g_aw_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS1_SW1, CS2_SW1, CS3_SW1},        //  0, ESC, k00
    {0, CS4_SW1, CS5_SW1, CS6_SW1},        //  1, ~, k10
    {0, CS7_SW1, CS8_SW1, CS9_SW1},        //  2, Tab, k20
    {0, CS10_SW1, CS11_SW1, CS12_SW1},     //  3, Caps, k30
    {0, CS13_SW1, CS14_SW1, CS15_SW1},     //  4, Sh_L, k40
    {0, CS16_SW1, CS17_SW1, CS18_SW1},     //  5, Ct_L, k50
    {0, CS1_SW2, CS2_SW2, CS3_SW2},        //  6, F1, k01
    {0, CS4_SW2, CS5_SW2, CS6_SW2},        //  7, 1, k11
    {0, CS7_SW2, CS8_SW2, CS9_SW2},        //  8, Q, k21
    {0, CS10_SW2, CS11_SW2, CS12_SW2},     //  9, A, k31
    {0, CS13_SW2, CS14_SW2, CS15_SW2},     //  10, Z, k41
    {0, CS16_SW2, CS17_SW2, CS18_SW2},     //  11, Win_L, k51
    {0, CS1_SW3, CS2_SW3, CS3_SW3},        //  12, F2, k02
    {0, CS4_SW3, CS5_SW3, CS6_SW3},        //  13, 2, k12
    {0, CS7_SW3, CS8_SW3, CS9_SW3},        //  14, W, k22
    {0, CS10_SW3, CS11_SW3, CS12_SW3},     //  15, S, k32
    {0, CS13_SW3, CS14_SW3, CS15_SW3},     //  16, X, k42
    {0, CS16_SW3, CS17_SW3, CS18_SW3},     //  17, Alt_L, k52
    {0, CS1_SW4, CS2_SW4, CS3_SW4},        //  18, F3, k03
    {0, CS4_SW4, CS5_SW4, CS6_SW4},        //  19, 3, k13
    {0, CS7_SW4, CS8_SW4, CS9_SW4},        //  20, E, k23
    {0, CS10_SW4, CS11_SW4, CS12_SW4},     //  21, D, k33
    {0, CS13_SW4, CS14_SW4, CS15_SW4},     //  22, C, k43
    {0, CS1_SW5, CS2_SW5, CS3_SW5},        //  23, F4, k04
    {0, CS4_SW5, CS5_SW5, CS6_SW5},        //  24, 4, k14
    {0, CS7_SW5, CS8_SW5, CS9_SW5},        //  25, R, k24
    {0, CS10_SW5, CS11_SW5, CS12_SW5},     //  26, F, k34
    {0, CS13_SW5, CS14_SW5, CS15_SW5},     //  27, V, k44
    {0, CS1_SW6, CS2_SW6, CS3_SW6},        //  28, F5, k05
    {0, CS4_SW6, CS5_SW6, CS6_SW6},        //  29, 5, k15
    {0, CS7_SW6, CS8_SW6, CS9_SW6},        //  30, T, k25
    {0, CS10_SW6, CS11_SW6, CS12_SW6},     //  31, G, k35
    {0, CS13_SW6, CS14_SW6, CS15_SW6},     //  32, B, k45
    {0, CS16_SW6, CS17_SW6, CS18_SW6},     //  33, SPACE, k53
    {0, CS1_SW7, CS2_SW7, CS3_SW7},        //  34, F6, k06
    {0, CS4_SW7, CS5_SW7, CS6_SW7},        //  35, 6, k16
    {0, CS7_SW7, CS8_SW7, CS9_SW7},        //  36, Y, k26
    {0, CS10_SW7, CS11_SW7, CS12_SW7},     //  37, H, k36
    {0, CS13_SW7, CS14_SW7, CS15_SW7},     //  38, N, k46
    {0, CS1_SW8, CS2_SW8, CS3_SW8},        //  39, F7, k07
    {0, CS4_SW8, CS5_SW8, CS6_SW8},        //  40, 7, k17
    {0, CS7_SW8, CS8_SW8, CS9_SW8},        //  41, U, k27
    {0, CS10_SW8, CS11_SW8, CS12_SW8},     //  42, J, k37
    {0, CS13_SW8, CS14_SW8, CS15_SW8},     //  43, M, k47
    {0, CS1_SW9, CS2_SW9, CS3_SW9},        //  44, F8, k08
    {0, CS4_SW9, CS5_SW9, CS6_SW9},        //  45, 8, k18
    {0, CS7_SW9, CS8_SW9, CS9_SW9},        //  46, I, k28
    {0, CS10_SW9, CS11_SW9, CS12_SW9},     //  47, K, k38
    {0, CS13_SW9, CS14_SW9, CS15_SW9},     //  48, ,M, k48
    {0, CS16_SW9, CS17_SW9, CS18_SW9},     //  49, Alt_R, k54
    {0, CS1_SW10, CS2_SW10, CS3_SW10},     //  50, F9, k09
    {0, CS4_SW10, CS5_SW10, CS6_SW10},     //  51, 9, k19
    {0, CS7_SW10, CS8_SW10, CS9_SW10},     //  52, O, k29
    {0, CS10_SW10, CS11_SW10, CS12_SW10},  //  53, L, k39
    {0, CS13_SW10, CS14_SW10, CS15_SW10},  //  54, ., k49
    {0, CS16_SW10, CS17_SW10, CS18_SW10},  //  55, FN, k55
    {0, CS1_SW11, CS2_SW11, CS3_SW11},     //  56, F10, k0A
    {0, CS4_SW11, CS5_SW11, CS6_SW11},     //  57, 0, k1A
    {0, CS7_SW11, CS8_SW11, CS9_SW11},     //  58, P, k2A
    {0, CS10_SW11, CS11_SW11, CS12_SW11},  //  59, ;, k3A
    {0, CS13_SW11, CS14_SW11, CS15_SW11},  //  60, /, k4A
    {0, CS1_SW12, CS2_SW12, CS3_SW12},     //  61, Menu, k56

    {0, CS4_SW12, CS5_SW12, CS6_SW12},     //  62, F11, k0B
    {0, CS7_SW12, CS8_SW12, CS9_SW12},     //  63, -, k1B
    {0, CS10_SW12, CS11_SW12, CS12_SW12},     //  64, [, k2B
    {1, CS16_SW12, CS17_SW12, CS18_SW12},  //  65, ;, k3B

    {1, CS1_SW1, CS2_SW1, CS3_SW1},  //  66, Sh_R, k4B
    {1, CS13_SW1, CS14_SW1, CS15_SW1},        //  67, Ct_R, k57
    {1, CS16_SW1, CS17_SW1, CS18_SW1},     //  68, F12, k0C
    {1, CS4_SW2, CS5_SW2, CS6_SW2},  //  69,   +, k1C
    {1, CS13_SW2, CS14_SW2, CS15_SW2},  //  70,   ], k2C
    {1, CS16_SW2, CS17_SW2, CS18_SW2},     //  71, Enter, k3C
    {1, CS4_SW3, CS5_SW3, CS6_SW3},  //  72, BSpc, k1E
    {1, CS13_SW3, CS14_SW3, CS15_SW3},  //  73,   \\, k2D

    {1, CS16_SW3, CS17_SW3, CS18_SW3},     //  74, PrtSc, k0D
    {1, CS4_SW4, CS5_SW4, CS6_SW4},  //  75, Ins, k5B
    {1, CS13_SW4, CS14_SW4, CS15_SW4},  //  76, Del, k2E
    {1, CS16_SW4, CS17_SW4, CS18_SW4},     //  77, ←, k58
    {1, CS1_SW5, CS2_SW5, CS3_SW5},  //  78, Scr, k0E
    {1, CS10_SW5, CS11_SW5, CS12_SW5},  //  79, Home, k5C
    {1, CS13_SW5, CS14_SW5, CS15_SW5},     //  80, End, k5D
    {1, CS16_SW5, CS17_SW5, CS18_SW5},  //  81, ↑, k4C
    {1, CS4_SW6, CS5_SW6, CS6_SW6},  //  82, ↓, k59
    {1, CS13_SW6, CS14_SW6, CS15_SW6},  //  83, Pau,k3D 
    {1, CS16_SW6, CS17_SW6, CS18_SW6},     //  84, PgUp, k3E
    {1, CS1_SW7, CS2_SW7, CS3_SW7},  //  85, PgDn, k5E
    {1, CS4_SW7, CS5_SW7, CS6_SW7},  //  86, →, k5A

    {1, CS1_SW2, CS2_SW2, CS3_SW2},  //   87, charge
    {1, CS1_SW3, CS2_SW3, CS3_SW3},   //  88, CPAS
};
// clang-format on
#endif
