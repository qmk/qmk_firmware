/*
Copyright 2023 Gondolindrim <gondolindrim@acheronproject.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |         G location
 *   |  |         |         B location
 *   |  |         |         | */
// First row
    {0, CS7_SW9 , CS9_SW9 , CS8_SW9  }, //ESC    0
    {0, CS7_SW8 , CS9_SW8 , CS8_SW8  }, //F1     1
    {0, CS7_SW7 , CS9_SW7 , CS8_SW7  }, //F2     2
    {0, CS7_SW6 , CS9_SW6 , CS8_SW6  }, //F3     3
    {0, CS7_SW5 , CS9_SW5 , CS8_SW5  }, //F4     4
    {0, CS7_SW4 , CS9_SW4 , CS8_SW4  }, //F5     5
    {0, CS7_SW3 , CS9_SW3 , CS8_SW3  }, //F6     6
    {0, CS7_SW2 , CS9_SW2 , CS8_SW2  }, //F7     7
    {0, CS7_SW1 , CS9_SW1 , CS8_SW1  }, //F8     8
    {0, CS18_SW2, CS16_SW2, CS17_SW2 }, //F9     9
    {0, CS18_SW3, CS16_SW3, CS17_SW3 }, //F10    10
    {0, CS18_SW4, CS16_SW4, CS17_SW4 }, //F11    11
    {0, CS18_SW6, CS16_SW6, CS17_SW6 }, //F12    12
    {0, CS18_SW7, CS16_SW7, CS17_SW7 }, //PRI    13
    {0, CS18_SW8, CS16_SW8, CS17_SW8 }, //SCR    14
    {0, CS18_SW9, CS16_SW9, CS17_SW9 }, //PAUS   15
//Second row
    {0, CS12_SW9, CS11_SW9, CS10_SW9 }, //GRAVE  16
    {0, CS12_SW8, CS11_SW8, CS10_SW8 }, //1      17
    {0, CS12_SW7, CS11_SW7, CS10_SW7 }, //2      18
    {0, CS12_SW6, CS11_SW6, CS10_SW6 }, //3      19
    {0, CS12_SW5, CS11_SW5, CS10_SW5 }, //4      20
    {0, CS12_SW4, CS11_SW4, CS10_SW4 }, //5      21
    {0, CS12_SW3, CS11_SW3, CS10_SW3 }, //6      22
    {0, CS12_SW2, CS11_SW2, CS10_SW2 }, //7      23
    {0, CS12_SW1, CS11_SW1, CS10_SW1 }, //8      24
    {0, CS15_SW1, CS13_SW1, CS14_SW1 }, //9      25
    {0, CS15_SW2, CS13_SW2, CS14_SW2 }, //0      26
    {0, CS15_SW3, CS13_SW3, CS14_SW3 }, //MINUS  27
    {0, CS15_SW4, CS13_SW4, CS14_SW4 }, //PLUS   28
    {0, CS15_SW5, CS13_SW5, CS14_SW5 }, //BKSP   29
    {0, CS15_SW7, CS13_SW7, CS14_SW7 }, //INS    30
    {0, CS15_SW8, CS13_SW8, CS14_SW8 }, //HOME   31
    {0, CS15_SW9, CS13_SW9, CS14_SW9 }, //PGUP   32
//Third row
    {0, CS4_SW9 , CS6_SW9 , CS5_SW9  }, //TAB    33
    {0, CS4_SW8 , CS6_SW8 , CS5_SW8  }, //Q      34
    {0, CS4_SW7 , CS6_SW7 , CS5_SW7  }, //W      35
    {0, CS4_SW6 , CS6_SW6 , CS5_SW6  }, //E      36
    {0, CS4_SW5 , CS6_SW5 , CS5_SW5  }, //R      37
    {0, CS4_SW4 , CS6_SW4 , CS5_SW4  }, //T      38
    {0, CS4_SW3 , CS6_SW3 , CS5_SW3  }, //Y      39
    {0, CS4_SW2 , CS6_SW2 , CS5_SW2  }, //U      40
    {0, CS4_SW1 , CS6_SW1 , CS5_SW1  }, //I      41
    {0, CS3_SW2 , CS1_SW2 , CS2_SW2  }, //O      42
    {0, CS3_SW3 , CS1_SW3 , CS2_SW3  }, //P      43
    {0, CS3_SW4 , CS1_SW4 , CS2_SW4  }, //LBRKT  44
    {0, CS3_SW5 , CS1_SW5 , CS2_SW5  }, //RBRKT  45
    {0, CS3_SW6 , CS1_SW6 , CS2_SW6  }, //BSLS   46
    {0, CS3_SW7 , CS1_SW7 , CS2_SW7  }, //DEL    47
    {0, CS3_SW8 , CS1_SW8 , CS2_SW8  }, //END    48
    {0, CS3_SW9 , CS1_SW9 , CS2_SW9  }, //PGDN   49
//Fourth row
    {0, CS33_SW9, CS32_SW9, CS31_SW9  }, //CAPS  50
    {0, CS33_SW8, CS32_SW8, CS31_SW8  }, //A     51
    {0, CS33_SW7, CS32_SW7, CS31_SW7  }, //S     52
    {0, CS33_SW6, CS32_SW6, CS31_SW6  }, //D     53
    {0, CS33_SW5, CS32_SW5, CS31_SW5  }, //F     54
    {0, CS33_SW4, CS32_SW4, CS31_SW4  }, //G     55
    {0, CS33_SW3, CS32_SW3, CS31_SW3  }, //H     56
    {0, CS33_SW2, CS32_SW2, CS31_SW2  }, //J     57
    {0, CS33_SW1, CS32_SW1, CS31_SW1  }, //K     58
    {0, CS39_SW2, CS38_SW2, CS37_SW2  }, //L     59
    {0, CS39_SW3, CS38_SW3, CS37_SW3  }, //COLON 60
    {0, CS39_SW4, CS38_SW4, CS37_SW4  }, //QUOTE 61
    {0, CS39_SW6, CS38_SW6, CS37_SW6  }, //ENTER 62
//Fifth row
    {0, CS30_SW9, CS28_SW9, CS29_SW9  }, //LSFT  63
    {0, CS30_SW7, CS28_SW7, CS29_SW7  }, //Z     64
    {0, CS30_SW6, CS28_SW6, CS29_SW6  }, //X     65
    {0, CS30_SW5, CS28_SW5, CS29_SW5  }, //C     66
    {0, CS30_SW4, CS28_SW4, CS29_SW4  }, //V     67
    {0, CS30_SW3, CS28_SW3, CS29_SW3  }, //B     68
    {0, CS30_SW2, CS28_SW2, CS29_SW2  }, //N     69
    {0, CS30_SW1, CS28_SW1, CS29_SW1  }, //M     70
    {0, CS36_SW1, CS35_SW1, CS34_SW1  }, //COMMA 71
    {0, CS36_SW3, CS35_SW3, CS34_SW3  }, //DOT   72
    {0, CS36_SW4, CS35_SW4, CS34_SW4  }, //SLASH 73
    {0, CS36_SW6, CS35_SW6, CS34_SW6  }, //RSFT  74
    {0, CS36_SW7, CS35_SW7, CS34_SW7  }, //UP    75
//Sixth row
    {0, CS27_SW9, CS25_SW9, CS26_SW9  }, //LCTRL 76
    {0, CS27_SW7, CS25_SW7, CS26_SW7  }, //LWIN  77
    {0, CS27_SW6, CS25_SW6, CS26_SW6  }, //LALT  78
    {0, CS27_SW5, CS25_SW5, CS26_SW5  }, //SPACE 79
    {0, CS27_SW3, CS25_SW3, CS26_SW3  }, //RALT  80
    {0, CS24_SW4, CS23_SW4, CS22_SW4  }, //RGUI  81
    {0, CS24_SW5, CS23_SW5, CS22_SW5  }, //MENU  82
    {0, CS24_SW6, CS23_SW6, CS22_SW6  }, //RCTRL 83
    {0, CS24_SW1, CS23_SW1, CS22_SW1  }, //LEFT  84
    {0, CS24_SW2, CS23_SW2, CS22_SW2  }, //DOWN  85
    {0, CS24_SW3, CS23_SW3, CS22_SW3  }, //RIGHT 86

};
#endif

#ifdef VIA_ENABLE
// Declaring a type indicator_config that stores color and enabled state
typedef struct _indicator_config_t {
// H, S, V store the color values; func stores the function (caps lock, scroll, num, layer indication); index stores the RGB LED index; and enabled stores the enabled state
        uint8_t h;
        uint8_t s;
        uint8_t v;
        uint8_t func ;
        uint8_t index ;
        bool enabled;    
} indicator_config ;

/* List of functions:
    0x0000 CAPS LOCK
    0x0001 NUM LOCK
    0x0002 SCROLL LOCK
    0x0003 LAYER 0
    0x0004 LAYER 1
    0x0005 LAYER 2
    0x0006 LAYER 3
*/

// Declaring a keyboard_indicators type that stores the indicators states

typedef struct _keyboard_indicators_t {
    indicator_config ind1 ;
    indicator_config ind2 ;
    indicator_config ind3 ;
    indicator_config ind4 ;
} keyboard_indicators ;

int indicator_number = (int)sizeof(keyboard_indicators)/(int)sizeof(indicator_config) ;

// Checks if the available EECONFIG DATA SIZE is exactly the size as keyboard_indicators
_Static_assert(sizeof(keyboard_indicators) == EECONFIG_KB_DATA_SIZE, "Mismatch in keyboard indicators stored data");

// Declaring a new variable indicators of the type keyboard_indicators
keyboard_indicators indicators;
uint8_t* pIndicators = (uint8_t*)&indicators ; // Gets a pointer to the first indicator

// This function returns the pointer to an indicator given an index
indicator_config* get_indicator_p (int index) {
    return (indicator_config*) (pIndicators + sizeof(indicator_config)*index) ;
}

// Initializing persistent memory configuration: default values are declared and stored in PMEM
void eeconfig_init_kb(void) {
    // Default values: all indicators start at white, 150 (roughly 60%) brightness value. Indicators 1 and 2 are active by default. Indicators 3 and 4 are disabled.
    // INDICATOR 1: CAPS LOCK
    indicators.ind1.h = 0;
    indicators.ind1.s = 0;
    indicators.ind1.v = 150;
    indicators.ind1.func = 0;
    indicators.ind1.index = 50;
    indicators.ind1.enabled = true;

    // INDICATOR 2: SCROLL LOCK
    indicators.ind2.h = 0;
    indicators.ind2.s = 0;
    indicators.ind2.v = 150;
    indicators.ind2.func = 2;

    indicators.ind2.index = 14;
    indicators.ind2.enabled = true;

    // INDICATOR 3: LAYER 1
    indicators.ind3.h = 0;
    indicators.ind3.s = 0;
    indicators.ind3.v = 150;
    indicators.ind3.func = 4;
    indicators.ind3.index = 82;
    indicators.ind3.enabled = false;

    // INDICATOR 4: LAYER 2
    indicators.ind4.h = 0;
    indicators.ind4.s = 0;
    indicators.ind4.v = 150;
    indicators.ind4.func = 5;
    indicators.ind4.index = 0;
    indicators.ind4.enabled = false;

    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&indicators);
}

void rgb_matrix_startup(void) {
    rgb_matrix_disable_noeeprom();
    wait_ms(20);
    rgb_matrix_reload_from_eeprom();
}

// At the keyboard start, retrieves PMEM stored configs
void keyboard_post_init_kb(void) {
    rgb_matrix_startup();
    eeconfig_read_kb_datablock(&indicators);
    rgb_matrix_indicators_kb();
}

bool set_indicator(indicator_config indicator) {
    switch (indicator.func)
    {
        case 0: // If indicator is set as caps lock
        {
            if (host_keyboard_led_state().caps_lock) return true;
        }
        case 1: // If indicator is set as num lock
        {
            if (host_keyboard_led_state().num_lock) return true;
        }
        case 2: // If indicator is set as scroll lock
        {
            if (host_keyboard_led_state().scroll_lock) return true;
        }
        case 3: // If indicator is set as layer 0
        case 4:
        case 5:
        case 6:
        {
            if ( IS_LAYER_ON( (int)(indicator.func) - 3  ) ) return true;
        }
        default:
        {
            return false;
        }
    }
    return false;
}

HSV return_indicator_hsv (indicator_config indicator){
    return (HSV){indicator.h, indicator.s, indicator.v};
}

// INDICATOR CALLBACK ------------------------------------------------------------------------------
bool rgb_matrix_indicators_kb(void) {
    // First decides if action is needed. If a user code is defined, or the indicator is disabled, then does not act.
    if (!rgb_matrix_indicators_user()) return false;

    RGB rgb_current_indicator ;
    indicator_config* current_indicator_p ;
    int index ;

    for (index = 0 ; index < indicator_number ; index++) {
        current_indicator_p = get_indicator_p(index) ;
        if (current_indicator_p -> enabled) {
            rgb_current_indicator = hsv_to_rgb(return_indicator_hsv( *(current_indicator_p) ));
            if (set_indicator( *(current_indicator_p)) ) rgb_matrix_set_color( current_indicator_p -> index, rgb_current_indicator.r, rgb_current_indicator.g, rgb_current_indicator.b);
            else rgb_matrix_set_color(current_indicator_p -> index, 0, 0, 0);
       }
    }
    return true;
}

// VIA CONFIGURATION -------------------------------------------------------------------------------
enum via_indicator_color {
    id_ind1_enabled = 1,
    id_ind1_brightness = 2,
    id_ind1_color = 3,
    id_ind1_func = 4,
    id_ind1_index = 5,
//
    id_ind2_enabled = 6,
    id_ind2_brightness = 7,
    id_ind2_color = 8,
    id_ind2_func = 9,
    id_ind2_index = 10,
//
    id_ind3_enabled = 11,
    id_ind3_brightness = 12,
    id_ind3_color = 13,
    id_ind3_func = 14,
    id_ind3_index = 15,
//
    id_ind4_enabled = 16,
    id_ind4_brightness = 17,
    id_ind4_color = 18,
    id_ind4_func = 19,
    id_ind4_index = 20
};

#define INDICATOR_PROPERTY_NUMBER 5

int indi_index;
int data_index;
void indicator_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id;
    value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    /* Suppose that the brightness value of indicator 3 is being changed; then

       index = (12-1)/INDICATOR_PROPERTY_NUMBER = (12-1)/5 = 2 (integer division!), which indeed relates to indicator 3 (ind1 is 0, ind2 is 1 etc)
       data_index = (12 - index*INDICATOR_PROPERTY_NUMBER) = 12 - 2*5 = 2, which indeed relates to a brightness setting (0 is for enabled, 1 for brightness, 2 for color and 3 for func)

       Therefore, the basic idea is that index is about which indicator the set_value is about, and data_index about what indicator property it is
    */
    indi_index = ( (int)(*value_id) - 1) / (int)INDICATOR_PROPERTY_NUMBER;
    data_index = (int)(*value_id) - indi_index*(int)INDICATOR_PROPERTY_NUMBER;
    indicator_config* current_indicator_p = get_indicator_p(indi_index);
    switch ( data_index )
    {
        case 1 :
        {
                current_indicator_p -> enabled = value_data[0];
                break;
        }
        case 2 :
        {
                current_indicator_p -> v = value_data[0];
                break;
        }
        case 3:
        {
                current_indicator_p -> h = value_data[0];
                current_indicator_p -> s = value_data[1];
                break;
        }
        case 4:
        {
                current_indicator_p -> func = value_data[0];
                break;
        }
        case 5:
        {
                current_indicator_p -> index = value_data[0];
                break;
        }
    }
    // Run callback after update
    rgb_matrix_indicators_kb();
}


void indicator_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    indi_index = ( (int)(*value_id) - 1) / (int)INDICATOR_PROPERTY_NUMBER;
    data_index = (int)(*value_id) - indi_index*(int)INDICATOR_PROPERTY_NUMBER;
    indicator_config* current_indicator_p = get_indicator_p(indi_index);
    switch ( data_index )
    {
        case 1:
        {
            value_data[0] =  current_indicator_p -> enabled;
            break;
        }
        case 2:
        {

            value_data[0] = current_indicator_p -> v;
            break;
        }
        case 3:
        {

            value_data[0] = current_indicator_p -> h;
            value_data[1] = current_indicator_p -> s;
            break;
        }
        case 4:
        {

            value_data[0] = current_indicator_p -> func;
            break;
        }
        case 5:
        {

            value_data[0] = current_indicator_p -> index;
            break;
        }
    }
}

void indicator_config_save(void)
{
    eeconfig_update_kb_datablock(&indicators);
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
                indicator_config_save();
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

    *command_id = id_unhandled;
}
#endif // VIA_ENABLE
