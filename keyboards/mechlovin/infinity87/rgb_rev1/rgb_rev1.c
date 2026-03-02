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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
    {0, SW1_CS34,   SW1_CS35,   SW1_CS36}, //D92-K00-0
    {0, SW1_CS37,   SW1_CS38,   SW1_CS39}, //D94-K01-1
    {0, SW1_CS31,   SW1_CS32,   SW1_CS33}, //D96-K02-2
    {0, SW1_CS28,   SW1_CS29,   SW1_CS30}, //D98-K03-3
    {0, SW1_CS25,   SW1_CS26,   SW1_CS27}, //D100-K04-4
    {0, SW1_CS22,   SW1_CS23,   SW1_CS24}, //D102-K05-5
    {0, SW1_CS19,   SW1_CS20,   SW1_CS21}, //D104-K06-6
    {0, SW1_CS18,   SW1_CS17,   SW1_CS16}, //D106-K07-7
    {0, SW1_CS15,   SW1_CS14,   SW1_CS13}, //D108-K08-8
    {0, SW1_CS12,   SW1_CS11,   SW1_CS10}, //D110-K09-9
    {0, SW1_CS9,    SW1_CS8,    SW1_CS7},  //D112-K0A-10
    {0, SW1_CS6,    SW1_CS5,    SW1_CS4},  //D114-K0B-11
    {0, SW1_CS3,    SW1_CS2,    SW1_CS1},  //D116-K0C-12
    {0, SW7_CS15,   SW7_CS14,   SW7_CS13}, //D157-K0D-13
    {0, SW7_CS18,   SW7_CS17,   SW7_CS16}, //D118-K0E-14
    {0, SW7_CS19,   SW7_CS20,   SW7_CS21}, //D120-K0F-15
    {0, SW7_CS12,   SW7_CS11,   SW7_CS10}, //D122-K0G-16
    {0, SW2_CS34,   SW2_CS35,   SW2_CS36}, //D93-K10-17
    {0, SW2_CS37,   SW2_CS38,   SW2_CS39}, //D95-K11-18
    {0, SW2_CS31,   SW2_CS32,   SW2_CS33}, //D97-K12-19
    {0, SW2_CS28,   SW2_CS29,   SW2_CS30}, //D99-K13-20
    {0, SW2_CS25,   SW2_CS26,   SW2_CS27}, //D101-K14-21
    {0, SW2_CS22,   SW2_CS23,   SW2_CS24}, //D103-K15-22
    {0, SW2_CS19,   SW2_CS20,   SW2_CS21}, //D105-K16-23
    {0, SW2_CS18,   SW2_CS17,   SW2_CS16}, //D107-K17-24
    {0, SW2_CS15,   SW2_CS14,   SW2_CS13}, //D109-K18-25
    {0, SW2_CS12,   SW2_CS11,   SW2_CS10}, //D111-K19-26
    {0, SW2_CS9,    SW2_CS8,    SW2_CS7},  //D113-K1A-27
    {0, SW2_CS6,    SW2_CS5,    SW2_CS4},  //D115-K1B-28
    {0, SW2_CS3,    SW2_CS2,    SW2_CS1},  //D117-K1C-29
    {0, SW8_CS3,    SW8_CS2,    SW8_CS1},  //D158-K1D-30
    {0, SW7_CS3,    SW7_CS2,    SW7_CS1},  //D119-K1E-31
    {0, SW8_CS18,   SW8_CS17,   SW8_CS16}, //D121-K1F-32
    {0, SW9_CS9,    SW9_CS8,    SW9_CS7}, //D123-K1G-33
    {0, SW3_CS34,   SW3_CS35,   SW3_CS36}, //D124-K20-34
    {0, SW3_CS37,   SW3_CS38,   SW3_CS39}, //D127-K21-35
    {0, SW3_CS31,   SW3_CS32,   SW3_CS33}, //D130-K22-36
    {0, SW3_CS28,   SW3_CS29,   SW3_CS30}, //D133-K23-37
    {0, SW3_CS25,   SW3_CS26,   SW3_CS27}, //D135-K24-38
    {0, SW3_CS22,   SW3_CS23,   SW3_CS24}, //D137-K25-39
    {0, SW3_CS19,   SW3_CS20,   SW3_CS21}, //D139-K26-40
    {0, SW3_CS18,   SW3_CS17,   SW3_CS16}, //D142-K27-41
    {0, SW3_CS15,   SW3_CS14,   SW3_CS13}, //D144-K28-42
    {0, SW3_CS12,   SW3_CS11,   SW3_CS10}, //D146-K29-43
    {0, SW3_CS9,    SW3_CS8,    SW3_CS7},  //D148-K2A-44
    {0, SW3_CS6,    SW3_CS5,    SW3_CS4},  //D151-K2B-45
    {0, SW3_CS3,    SW3_CS2,    SW3_CS1},  //D154-K2C-46
    {0, SW8_CS6,    SW8_CS5,    SW8_CS4},  //D159-K2D-47
    {0, SW7_CS6,    SW7_CS5,    SW7_CS4},  //D180-K2E-48
    {0, SW8_CS19,   SW8_CS20,   SW8_CS21}, //D181-K2F-49
    {0, SW7_CS9,    SW7_CS8,    SW7_CS7},  //D182-K2G-50
    {0, SW4_CS34,   SW4_CS35,   SW4_CS36}, //D166-K30-51
    {0, SW4_CS37,   SW4_CS38,   SW4_CS39}, //D167-K31-52
    {0, SW4_CS31,   SW4_CS32,   SW4_CS33}, //D168-K32-53
    {0, SW4_CS28,   SW4_CS29,   SW4_CS30}, //D169-K33-54
    {0, SW4_CS25,   SW4_CS26,   SW4_CS27}, //D170-K34-55
    {0, SW4_CS22,   SW4_CS23,   SW4_CS24}, //D171-K35-56
    {0, SW4_CS19,   SW4_CS20,   SW4_CS21}, //D172-K36-57
    {0, SW4_CS18,   SW4_CS17,   SW4_CS16}, //D173-K37-58
    {0, SW4_CS15,   SW4_CS14,   SW4_CS13}, //D174-K38-59
    {0, SW4_CS12,   SW4_CS11,   SW4_CS10}, //D175-K39-60
    {0, SW4_CS9,    SW4_CS8,    SW4_CS7},  //D176-K3A-61
    {0, SW4_CS6,    SW4_CS5,    SW4_CS4},  //D177-K3B-62
    {0, SW4_CS3,    SW4_CS2,    SW4_CS1},  //D178-K3C-63
    {0, SW8_CS9,    SW8_CS8,    SW8_CS7},  //D179-K3D-64
    {0, SW5_CS34,   SW5_CS35,   SW5_CS36}, //D125-K40-65
    {0, SW5_CS37,   SW5_CS38,   SW5_CS39}, //D128-K41-66
    {0, SW5_CS31,   SW5_CS32,   SW5_CS33}, //D131-K42-67
    {0, SW5_CS28,   SW5_CS29,   SW5_CS30}, //D134-K43-68
    {0, SW5_CS25,   SW5_CS26,   SW5_CS27}, //D136-K44-69
    {0, SW5_CS22,   SW5_CS23,   SW5_CS24}, //D138-K45-70
    {0, SW5_CS19,   SW5_CS20,   SW5_CS21}, //D140-K46-71
    {0, SW5_CS18,   SW5_CS17,   SW5_CS16}, //D143-K47-72
    {0, SW5_CS15,   SW5_CS14,   SW5_CS13}, //D145-K48-73
    {0, SW5_CS12,   SW5_CS11,   SW5_CS10}, //D147-K49-74
    {0, SW5_CS9,    SW5_CS8,    SW5_CS7},  //D149-K4A-75
    {0, SW5_CS6,    SW5_CS5,    SW5_CS4},  //D152-K4B-76
    {0, SW5_CS3,    SW5_CS2,    SW5_CS1},  //D155-K4C-77
    {0, SW8_CS12,   SW8_CS11,   SW8_CS10}, //D160-K4D-78
    {0, SW9_CS12,   SW9_CS11,   SW9_CS10}, //D163-K4E-79
    {0, SW6_CS34,   SW6_CS35,   SW6_CS36}, //D126-K20-80
    {0, SW6_CS37,   SW6_CS38,   SW6_CS39}, //D129-K21-81
    {0, SW6_CS31,   SW6_CS32,   SW6_CS33}, //D132-K22-82
    {0, SW6_CS19,   SW6_CS20,   SW6_CS21}, //D141-K26-83
    {0, SW6_CS9,    SW6_CS8,    SW6_CS7},  //D150-K2A-84
    {0, SW6_CS6,    SW6_CS5,    SW6_CS4},  //D153-K2B-85
    {0, SW6_CS3,    SW6_CS2,    SW6_CS1},  //D156-K2C-86
    {0, SW8_CS15,   SW8_CS14,   SW8_CS13}, //D161-K2D-87
    {0, SW9_CS15,   SW9_CS14,   SW9_CS13}, //D162-K2E-88
    {0, SW9_CS18,   SW9_CS17,   SW9_CS16}, //D164-K2F-89
    {0, SW9_CS19,   SW9_CS20,   SW9_CS21}, //D165-K2G-90
};

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
