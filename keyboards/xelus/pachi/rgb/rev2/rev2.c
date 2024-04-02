/* Copyright 2023 Harrison Chan (Xelus)
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

#include "rev2.h"

// tested and working
void matrix_io_delay(void) { __asm__ volatile("nop\nnop\nnop\n"); }

#ifdef RGB_MATRIX_ENABLE
#include "i2c_master.h"
#include "drivers/led/issi/is31fl3741.h"
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |         G location
 *   |  |         |         B location
 *   |  |         |         | */
    {0, SW1_CS39, SW1_CS38, SW1_CS37}, //A1
    {0, SW1_CS36, SW1_CS35, SW1_CS34}, //A2
    {0, SW1_CS33, SW1_CS32, SW1_CS31}, //A3
    {0, SW1_CS30, SW1_CS29, SW1_CS28}, //A4
    {0, SW1_CS27, SW1_CS26, SW1_CS25}, //A5
    {0, SW1_CS24, SW1_CS23, SW1_CS22}, //A6
    {0, SW1_CS21, SW1_CS20, SW1_CS19}, //A7
    {0, SW1_CS18, SW1_CS17, SW1_CS16}, //A8
    {0, SW1_CS15, SW1_CS14, SW1_CS13}, //A9
    {0, SW1_CS12, SW1_CS11, SW1_CS10}, //A10
    {0, SW1_CS9 , SW1_CS8 , SW1_CS7 }, //A11
    {0, SW1_CS6 , SW1_CS5 , SW1_CS4 }, //A12
    {0, SW1_CS3 , SW1_CS2 , SW1_CS1 }, //A13

    {0, SW2_CS39, SW2_CS38, SW2_CS37}, //B1
    {0, SW2_CS36, SW2_CS35, SW2_CS34}, //B2
    {0, SW2_CS33, SW2_CS32, SW2_CS31}, //B3
    {0, SW2_CS30, SW2_CS29, SW2_CS28}, //B4
    {0, SW2_CS27, SW2_CS26, SW2_CS25}, //B5
    {0, SW2_CS24, SW2_CS23, SW2_CS22}, //B6
    {0, SW2_CS21, SW2_CS20, SW2_CS19}, //B7
    {0, SW2_CS18, SW2_CS17, SW2_CS16}, //B8
    {0, SW2_CS15, SW2_CS14, SW2_CS13}, //B9
    {0, SW2_CS12, SW2_CS11, SW2_CS10}, //B10
    {0, SW2_CS9 , SW2_CS8 , SW2_CS7 }, //B11
    {0, SW2_CS6 , SW2_CS5 , SW2_CS4 }, //B12
    {0, SW2_CS3 , SW2_CS2 , SW2_CS1 }, //B13

    {0, SW3_CS39, SW3_CS38, SW3_CS37}, //C1
    {0, SW3_CS36, SW3_CS35, SW3_CS34}, //C2
    {0, SW3_CS33, SW3_CS32, SW3_CS31}, //C3
    {0, SW3_CS30, SW3_CS29, SW3_CS28}, //C4
    {0, SW3_CS27, SW3_CS26, SW3_CS25}, //C5
    {0, SW3_CS24, SW3_CS23, SW3_CS22}, //C6
    {0, SW3_CS21, SW3_CS20, SW3_CS19}, //C7
    {0, SW3_CS18, SW3_CS17, SW3_CS16}, //C8
    {0, SW3_CS15, SW3_CS14, SW3_CS13}, //C9
    {0, SW3_CS12, SW3_CS11, SW3_CS10}, //C10
    {0, SW3_CS9 , SW3_CS8 , SW3_CS7 }, //C11
    {0, SW3_CS6 , SW3_CS5 , SW3_CS4 }, //C12
    {0, SW3_CS3 , SW3_CS2 , SW3_CS1 }, //C13

    {0, SW4_CS39, SW4_CS38, SW4_CS37}, //D1
    {0, SW4_CS36, SW4_CS35, SW4_CS34}, //D2
    {0, SW4_CS33, SW4_CS32, SW4_CS31}, //D3
    {0, SW4_CS30, SW4_CS29, SW4_CS28}, //D4
    {0, SW4_CS27, SW4_CS26, SW4_CS25}, //D5
    {0, SW4_CS24, SW4_CS23, SW4_CS22}, //D6
    {0, SW4_CS21, SW4_CS20, SW4_CS19}, //D7
    {0, SW4_CS18, SW4_CS17, SW4_CS16}, //D8
    {0, SW4_CS15, SW4_CS14, SW4_CS13}, //D9
    {0, SW4_CS12, SW4_CS11, SW4_CS10}, //D10
    {0, SW4_CS9 , SW4_CS8 , SW4_CS7 }, //D11
    {0, SW4_CS6 , SW4_CS5 , SW4_CS4 }, //D12
    {0, SW4_CS3 , SW4_CS2 , SW4_CS1 }, //D13

    {0, SW5_CS39, SW5_CS38, SW5_CS37}, //E1
    {0, SW5_CS36, SW5_CS35, SW5_CS34}, //E2
    {0, SW5_CS33, SW5_CS32, SW5_CS31}, //E3
    {0, SW5_CS30, SW5_CS29, SW5_CS28}, //E4
    {0, SW5_CS27, SW5_CS26, SW5_CS25}, //E5
    {0, SW5_CS24, SW5_CS23, SW5_CS22}, //E6
    {0, SW5_CS21, SW5_CS20, SW5_CS19}, //E7
    {0, SW5_CS18, SW5_CS17, SW5_CS16}, //E8
    {0, SW5_CS15, SW5_CS14, SW5_CS13}, //E9
    {0, SW5_CS12, SW5_CS11, SW5_CS10}, //E10
    {0, SW5_CS9 , SW5_CS8 , SW5_CS7 }, //E11
    {0, SW5_CS6 , SW5_CS5 , SW5_CS4 }, //E12
    {0, SW5_CS3 , SW5_CS2 , SW5_CS1 }, //E13

    {0, SW6_CS39, SW6_CS38, SW6_CS37}, //F1
    {0, SW6_CS36, SW6_CS35, SW6_CS34}, //F2
    {0, SW6_CS33, SW6_CS32, SW6_CS31}, //F3
    {0, SW6_CS30, SW6_CS29, SW6_CS28}, //F4
    {0, SW6_CS27, SW6_CS26, SW6_CS25}, //F5
    {0, SW6_CS24, SW6_CS23, SW6_CS22}, //F6
    {0, SW6_CS21, SW6_CS20, SW6_CS19}, //F7
    {0, SW6_CS18, SW6_CS17, SW6_CS16}, //F8
    {0, SW6_CS15, SW6_CS14, SW6_CS13}, //F9
    {0, SW6_CS12, SW6_CS11, SW6_CS10}, //F10
    {0, SW6_CS9 , SW6_CS8 , SW6_CS7 }, //F11
    {0, SW6_CS6 , SW6_CS5 , SW6_CS4 }, //F12
    {0, SW6_CS3 , SW6_CS2 , SW6_CS1 }, //F13

    {0, SW7_CS39, SW7_CS38, SW7_CS37}, //G1
    {0, SW7_CS36, SW7_CS35, SW7_CS34}, //G2
    {0, SW7_CS33, SW7_CS32, SW7_CS31}, //G3
    {0, SW7_CS30, SW7_CS29, SW7_CS28}, //G4
    {0, SW7_CS27, SW7_CS26, SW7_CS25}, //G5
    {0, SW7_CS24, SW7_CS23, SW7_CS22}, //G6
    {0, SW7_CS21, SW7_CS20, SW7_CS19}, //G7
    {0, SW7_CS18, SW7_CS17, SW7_CS16}, //G8
    {0, SW7_CS15, SW7_CS14, SW7_CS13}, //G9
    {0, SW7_CS12, SW7_CS11, SW7_CS10}, //G10
    {0, SW7_CS9 , SW7_CS8 , SW7_CS7 }, //G11
    {0, SW7_CS6 , SW7_CS5 , SW7_CS4 }, //G12
    {0, SW7_CS3 , SW7_CS2 , SW7_CS1 }, //G13

    {0, SW8_CS39, SW8_CS38, SW8_CS37}, //H1
    {0, SW8_CS36, SW8_CS35, SW8_CS34}, //H2
    {0, SW8_CS33, SW8_CS32, SW8_CS31}, //H3
    {0, SW8_CS30, SW8_CS29, SW8_CS28}, //H4
    {0, SW8_CS27, SW8_CS26, SW8_CS25}, //H5
    {0, SW8_CS24, SW8_CS23, SW8_CS22}, //H6
    {0, SW8_CS21, SW8_CS20, SW8_CS19}, //H7
    {0, SW8_CS18, SW8_CS17, SW8_CS16}, //H8
    {0, SW8_CS15, SW8_CS14, SW8_CS13}, //H9
    {0, SW8_CS12, SW8_CS11, SW8_CS10}, //H10
    {0, SW8_CS9 , SW8_CS8 , SW8_CS7 }, //H11
    {0, SW8_CS6 , SW8_CS5 , SW8_CS4 }, //H12
    {0, SW8_CS3 , SW8_CS2 , SW8_CS1 }, //H13

    {0, SW9_CS39, SW9_CS38, SW9_CS37}, //I1
    {0, SW9_CS36, SW9_CS35, SW9_CS34}, //I2
    {0, SW9_CS33, SW9_CS32, SW9_CS31}, //I3
    {0, SW9_CS30, SW9_CS29, SW9_CS28}, //I4
    {0, SW9_CS27, SW9_CS26, SW9_CS25}, //I5
    {0, SW9_CS24, SW9_CS23, SW9_CS22}, //I6
    {0, SW9_CS21, SW9_CS20, SW9_CS19}, //I7
    {0, SW9_CS18, SW9_CS17, SW9_CS16}, //I8
    {0, SW9_CS15, SW9_CS14, SW9_CS13}, //I9
    {0, SW9_CS12, SW9_CS11, SW9_CS10}, //I10
    {0, SW9_CS9 , SW9_CS8 , SW9_CS7 }, //I11
    {0, SW9_CS6 , SW9_CS5 , SW9_CS4 }, //I12
    {0, SW9_CS3 , SW9_CS2 , SW9_CS1 }  //I13
};

__attribute__ ((weak))
led_config_t g_led_config = { {
    {      2,     28,     54,     80,    106,     13,     39,     65,     91 },
    { NO_LED,     41,     67,     93,      0,     26,     52,     78, NO_LED },
    {      3,     29,     55,     81,    107,     14,     40,     66,     92 },
    {     16,     42,     68,     94,      1,     27,     53,     79, NO_LED },
    {      5,     31,     57,     83,    109,     17,     43,     69,     95 },
    {     18,     44,     70,     96,      4,     31,     56,     82, NO_LED },
    {      7,     33,     59,     85,    111,     19, NO_LED, NO_LED, NO_LED },
    {     20,     46,     72,     98,      6,     32,     58, NO_LED, NO_LED },
    {     10,     36,     62,     88,    114,     22,     61, NO_LED, NO_LED },
    {     23,     49,     75,    101,      9, NO_LED, NO_LED,     87, NO_LED },
    {      8,     34, NO_LED, NO_LED, NO_LED,     24,     50,     76,    102 },
    {     21, NO_LED,     73, NO_LED, NO_LED, NO_LED,     63,     89, NO_LED }
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
    is31fl3741_init(0);
    for (int index = 0; index < IS31FL3741_LED_COUNT; index++) {
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
        is31fl3741_set_led_control_register(index, enabled, enabled, enabled);
    }
    is31fl3741_update_led_control_registers(0);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = is31fl3741_flush,
    .set_color = is31fl3741_set_color,
    .set_color_all = is31fl3741_set_color_all
};

#ifdef VIA_ENABLE
#include "quantum.h"
#include "eeprom.h"

indicator_settings_config g_config = {
    .caps_lock_indicator = {0, 0, 128},
    .num_lock_indicator = {60, 0, 128},
    .scroll_lock_indicator = {120, 0, 128},
    .layer_indicator = {180, 0, 128},
    .caps_lock_key = 7,
    .num_lock_key = 0,
    .scroll_lock_key = 78,
    .layer_indicator_key = 0,
    .enable_caps_lock = true,
    .enable_num_lock = false,
    .enable_scroll_lock = true,
    .enable_layer_indicator = false,
    .caps_override_bl = true,
    .num_override_bl = true,
    .scroll_override_bl = true,
    .layer_override_bl = true
};

void values_load(void)
{
    eeprom_read_block( &g_config, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config) );
}

void values_save(void)
{
    eeprom_update_block( &g_config, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config) );
}

void via_init_kb(void)
{
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        values_load();
    } else	{
        values_save();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                indicator_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                indicator_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                values_save();
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void indicator_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_caps_lock_enable:
            g_config.enable_caps_lock = *value_data;
            break;
        case id_num_lock_enable:
            g_config.enable_num_lock = *value_data;
            break;
        case id_scroll_lock_enable:
            g_config.enable_scroll_lock = *value_data;
            break;
        case id_layer_indicator_enable:
            g_config.enable_layer_indicator = *value_data;
            break;
        case id_caps_lock_brightness:
            g_config.caps_lock_indicator.v = *value_data;
            break;
        case id_num_lock_brightness:
            g_config.num_lock_indicator.v = *value_data;
            break;
        case id_scroll_lock_brightness:
            g_config.scroll_lock_indicator.v = *value_data;
            break;
        case id_layer_indicator_brightness:
            g_config.layer_indicator.v = *value_data;
            break;
        case id_caps_lock_color:
            _set_color( &(g_config.caps_lock_indicator), value_data );
            break;
        case id_num_lock_color:
            _set_color( &(g_config.num_lock_indicator), value_data );
            break;
        case id_scroll_lock_color:
            _set_color( &(g_config.scroll_lock_indicator), value_data );
            break;
        case id_layer_indicator_color:
            _set_color( &(g_config.layer_indicator), value_data );
            break;
        case id_caps_lock_key:
            g_config.caps_lock_key = *value_data;
            break;
        case id_num_lock_key:
            g_config.num_lock_key = *value_data;
            break;
        case id_scroll_lock_key:
            g_config.scroll_lock_key = *value_data;
            break;
        case id_layer_indicator_key:
            g_config.layer_indicator_key = *value_data;
            break;
        case id_caps_lock_override:
            g_config.caps_override_bl = *value_data;
            break;
        case id_num_lock_override:
            g_config.num_override_bl = *value_data;
            break;
        case id_scroll_lock_override:
            g_config.scroll_override_bl = *value_data;
            break;
        case id_layer_indicator_override:
            g_config.layer_override_bl = *value_data;
            break;
    }
}

void indicator_config_get_value( uint8_t *data )
{
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_caps_lock_enable:
            *value_data = g_config.enable_caps_lock;
            break;
        case id_num_lock_enable:
            *value_data = g_config.enable_num_lock;
            break;
        case id_scroll_lock_enable:
            *value_data = g_config.enable_scroll_lock;
            break;
        case id_layer_indicator_enable:
            *value_data = g_config.enable_layer_indicator;
            break;
        case id_caps_lock_brightness:
            *value_data = g_config.caps_lock_indicator.v;
            break;
        case id_num_lock_brightness:
            *value_data = g_config.num_lock_indicator.v;
            break;
        case id_layer_indicator_brightness:
            *value_data = g_config.scroll_lock_indicator.v;
            break;
        case id_scroll_lock_brightness:
            *value_data = g_config.layer_indicator.v;
            break;
        case id_caps_lock_color:
            _get_color( &(g_config.caps_lock_indicator), value_data );
            break;
        case id_num_lock_color:
            _get_color( &(g_config.num_lock_indicator), value_data );
            break;
        case id_scroll_lock_color:
            _get_color( &(g_config.scroll_lock_indicator), value_data );
            break;
        case id_layer_indicator_color:
            _get_color( &(g_config.layer_indicator), value_data );
            break;
        case id_caps_lock_key:
            *value_data = g_config.caps_lock_key;
            break;
        case id_num_lock_key:
            *value_data = g_config.num_lock_key;
            break;
        case id_scroll_lock_key:
            *value_data = g_config.scroll_lock_key;
            break;
        case id_layer_indicator_key:
            *value_data = g_config.layer_indicator_key;
            break;
        case id_caps_lock_override:
            *value_data = g_config.caps_override_bl;
            break;
        case id_num_lock_override:
            *value_data = g_config.num_override_bl;
            break;
        case id_scroll_lock_override:
            *value_data = g_config.scroll_override_bl;
            break;
        case id_layer_indicator_override:
            *value_data = g_config.layer_override_bl;
            break;
    }
}

// Some helpers for setting/getting HSV
void _set_color( HSV *color, uint8_t *data )
{
    color->h = data[0];
    color->s = data[1];
}

void _get_color( HSV *color, uint8_t *data )
{
    data[0] = color->h;
    data[1] = color->s;
}

// Set the indicators with RGB Matrix subsystem
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    // caps lock cyan
    if (g_config.enable_caps_lock) {
        RGB rgb_caps = hsv_to_rgb( (HSV){ .h = g_config.caps_lock_indicator.h,
                                          .s = g_config.caps_lock_indicator.s,
                                          .v = g_config.caps_lock_indicator.v } );
        if (host_keyboard_led_state().caps_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.caps_lock_key, rgb_caps.r, rgb_caps.g, rgb_caps.b);
        } else {
            if (g_config.caps_override_bl) {
                RGB_MATRIX_INDICATOR_SET_COLOR(g_config.caps_lock_key, 0, 0, 0);
            }
        }
    }

    // num lock cyan
    if (g_config.enable_num_lock) {
        RGB rgb_num = hsv_to_rgb( (HSV){ .h = g_config.num_lock_indicator.h,
                                         .s = g_config.num_lock_indicator.s,
                                         .v = g_config.num_lock_indicator.v } );
        if (host_keyboard_led_state().num_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.num_lock_key, rgb_num.r, rgb_num.g, rgb_num.b);
        } else {
            if (g_config.num_override_bl) {
                RGB_MATRIX_INDICATOR_SET_COLOR(g_config.num_lock_key, 0, 0, 0);
            }
        }
    }

    // scroll lock cyan
    if (g_config.enable_scroll_lock) {
        RGB rgb_scroll = hsv_to_rgb( (HSV){ .h = g_config.scroll_lock_indicator.h,
                                            .s = g_config.scroll_lock_indicator.s,
                                            .v = g_config.scroll_lock_indicator.v } );
        if (host_keyboard_led_state().scroll_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.scroll_lock_key, rgb_scroll.r, rgb_scroll.g, rgb_scroll.b);
        } else {
            if (g_config.scroll_override_bl) {
                RGB_MATRIX_INDICATOR_SET_COLOR(g_config.scroll_lock_key, 0, 0, 0);
            }
        }
    }

    // layer state
    if (g_config.enable_layer_indicator) {
        RGB rgb_layer = hsv_to_rgb( (HSV){ .h = g_config.layer_indicator.h,
                                           .s = g_config.layer_indicator.s,
                                           .v = g_config.layer_indicator.v } );
        switch (get_highest_layer(layer_state)) {
            case 0:
                if (g_config.layer_override_bl) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(g_config.layer_indicator_key, 0, 0, 0);
                }
                break;
            case 1:
                RGB_MATRIX_INDICATOR_SET_COLOR(g_config.layer_indicator_key, rgb_layer.r, rgb_layer.g, rgb_layer.b);
                break;
            default:
                // white
                RGB_MATRIX_INDICATOR_SET_COLOR(24, 128, 128, 128);
                break;
        }
    }
    return false;
}

#endif
#endif
