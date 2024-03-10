/* Copyright 2023 Gondolindrim <gondolindrim@acheronproject.com>
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
#include "print.h"

/* RGB indicators: by default, they are numbered (when looking from above) INDICATOR_R, INDICATOR_C, INDICATOR_L
*/

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

// Number of properties of the "indicator" struct
#define INDICATOR_PROPERTY_NUMBER 6
// Declaring a keyboard_indicators type that stores the indicators states
#define INDICATOR_NUMBER 3

/* List of functions:
    0x00 NONE
    0x01 CAPS LOCK
    0x02 NUM LOCK
    0x03 SCROLL LOCK
    0x04 LAYER 0
    0x05 LAYER 1
    0x06 LAYER 2
    0x07 LAYER 3
*/

bool func_switch(uint8_t func) {
    switch (func)
    {
        case 0x00:
        {
           return false;
           break;
        }
        case 0x01: // If indicator is set as caps lock
        {
            if (host_keyboard_led_state().caps_lock) return true;
            break;
        }
        case 0x02: // If indicator is set as num lock
        {
            if (host_keyboard_led_state().num_lock) return true;
            break;
        }
        case 0x03: // If indicator is set as scroll lock
        {
            if (host_keyboard_led_state().scroll_lock) return true;
            break;
        }
        case 0x04: // If indicator is set as layer 0
        case 0x05:
        case 0x06:
        case 0x07:
        {
            if ( IS_LAYER_ON( (int)(func) - 4  ) ) return true;
            break;
        }
        default:
        {
            return false;
        }
    }
    return false;
}

// Here the indicators functions themselves are programmed.
bool set_indicator(indicator_config indicator) {
    if (!indicator.enabled) return false;
    return func_switch(indicator.func & 0x0F) | func_switch( (indicator.func & 0xF0) >> 4);
}

typedef struct _keyboard_indicators_t {
    indicator_config ind1 ;
    indicator_config ind2 ;
    indicator_config ind3 ;
} keyboard_indicators ;

_Static_assert(sizeof(keyboard_indicators) == EECONFIG_KB_DATA_SIZE, "Mismatch in keyboard indicators stored data");

// Declaring a new variable indicators of the type keyboard_indicators
keyboard_indicators indicators;
uint8_t* pIndicators = (uint8_t*)&indicators ; // Gets a pointer to the first indicator

// This function returns the pointer to an indicator given an index. Basically what is done is shifting the pointer of the indicators struct by 6*index.
// Each indicator is INDICATOR_PROPERTY_NUMBER  bytes long, so the shift needs to be that size.
indicator_config* get_indicator_p (int index) {
    return (indicator_config*) (pIndicators + INDICATOR_PROPERTY_NUMBER*index) ;
}

// Initializing persistent memory configuration: default values are declared and stored in PMEM
void eeconfig_init_kb(void) {
    // Default values: indicators start at white, 150 (roughly 60%) brightness value. Indicators 1 and 2 are active by default.
    // INDICATOR 0: RIGHT INDICATOR
    indicators.ind1.h = 0;
    indicators.ind1.s = 255;
    indicators.ind1.v = 150;
    indicators.ind1.func = 0x76;
    indicators.ind1.index = 0;
    indicators.ind1.enabled = true;

    // INDICATOR 1: MIDDLE INDICATOR
    indicators.ind2.h = 86;
    indicators.ind2.s = 255;
    indicators.ind2.v = 150;
    indicators.ind2.func = 0x75;
    indicators.ind2.index = 1;
    indicators.ind2.enabled = true;

    // INDICATOR 2: LEFT INDICATOR
    indicators.ind3.h = 166;
    indicators.ind3.s = 254;
    indicators.ind3.v = 150;
    indicators.ind3.func = 0x01;
    indicators.ind3.index = 2;
    indicators.ind3.enabled = true;

    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&indicators);
}

// INDICATOR CALLBACK ------------------------------------------------------------------------------
bool indicators_callback(void) {

    // Basic functioning: for each indicator, set_indicator is used to decide if the current indicator should be lit or off.
    indicator_config* current_indicator_p ;
    int index ;
    for (index = 0 ; index < INDICATOR_NUMBER ; index++) {
        current_indicator_p = get_indicator_p(index) ;
        if (set_indicator( *(current_indicator_p)) ) sethsv( current_indicator_p -> h, current_indicator_p -> s, current_indicator_p -> v, (LED_TYPE *)&led[current_indicator_p -> index]);
        else sethsv( 0,0,0, (LED_TYPE *)&led[current_indicator_p -> index]);
    }
    return true;
}

// This function gets called when caps, num, scroll change
bool led_update_kb(led_t led_state) {
 	indicators_callback();
        return true;
}

// This function is called when layers change
layer_state_t layer_state_set_user(layer_state_t state) {
    indicators_callback();
    return state;
}

// At the keyboard start, retrieves PMEM stored configs and runs indicator_callback
void keyboard_post_init_kb(void) {
    eeconfig_read_kb_datablock(&indicators);
    rgblight_set_effect_range(3,66);
    indicators_callback();

    debug_enable = true;
    //debug_keyboard = true;
}

// VIA CONFIGURATION -------------------------------------------------------------------------------
enum via_indicator_color {
    id_ind1_enabled = 1,
    id_ind1_brightness = 2,
    id_ind1_color = 3,
    id_ind1_func1 = 4,
    id_ind1_func2 = 5,
//
    id_ind2_enabled = 6,
    id_ind2_brightness = 7,
    id_ind2_color = 8,
    id_ind2_func1 = 9,
    id_ind2_func2 = 10,
//
    id_ind3_enabled = 11,
    id_ind3_brightness = 12,
    id_ind3_color = 13,
    id_ind3_func1 = 14,
    id_ind3_func2 = 15
};

int indi_index;
int data_index;

void indicator_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id;
    value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    /* Suppose that the brightness value of indicator 3 is being changed; then
       index = (12-1)/INDICATOR_PROPERTY_NUMBER = 11/5 = 2 (integer division!), which indeed relates to indicator 3 (ind1 is 0, ind2 is 1 etc)
       data_index = (12 - index*INDICATOR_PROPERTY_NUMBER) = 12 - 2*5 = 2, which indeed relates to a brightness setting (0 is for enabled, 1 for brightness, 2 for color and 3 for func)
       Therefore, the basic idea is that index is about which indicator the set_value is about, and data_index about what indicator property it is
    */
    indi_index = ( (int)(*value_id) - 1) / 5;
    data_index = (int)(*value_id) - indi_index*5;
    indicator_config* current_indicator_p = get_indicator_p(indi_index);
    uprintf("--> value_id: %X\n", (int)(*value_id));
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
                current_indicator_p -> func = (current_indicator_p -> func & 0xF0 ) | (uint8_t) value_data[0];
                break;
        }
        case 5:
        {

                current_indicator_p -> func = (current_indicator_p -> func & 0x0F ) | ((uint8_t) value_data[0] << 4);
                break;
        }
    }
    indicators_callback();
}


void indicator_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    indi_index = ( (int)(*value_id) - 1) / 5; data_index = (int)(*value_id) - indi_index*5;
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

            value_data[0] = current_indicator_p -> func & 0x0F;
            uprintf("--> Current func: %x, current func with bitwise or: %X\n", current_indicator_p -> func, current_indicator_p -> func % 0x0F);
            break;
        }
        case 5:
        {

            value_data[0] = (current_indicator_p -> func & 0xF0) >> 4;
            uprintf("--> Current func: %x, current func with bitwise or: %X\n", current_indicator_p -> func, current_indicator_p -> func % 0xF0);
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
