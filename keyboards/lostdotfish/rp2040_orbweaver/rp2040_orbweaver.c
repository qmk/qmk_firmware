/* Copyright 2024 lostdotfish
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#include "rgb_matrix.h"
#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Initialize Reset pins
 
    gpio_set_pin_output(GP23);
    gpio_set_pin_output(GP24);
    gpio_set_pin_output(GP25);

    gpio_write_pin_high(GP23);
    gpio_write_pin_high(GP24);
    gpio_write_pin_high(GP25);

    keyboard_pre_init_user();
}



const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C9_1,  C8_1,  C7_1}, //top left key.
    {0, C9_2,  C8_2,  C7_2},	
    {0, C9_3,  C8_3,  C7_3},
    {0, C9_4,  C8_4,  C7_4},
    {0, C9_5,  C8_5,  C7_5}, //top right key. 
    {0, C9_6,  C8_6,  C7_6},
    {0, C9_7,  C8_7,  C6_6},      
    {0, C9_8,  C7_7,  C6_7},
    {0, C1_8,  C2_8,  C3_8},  
    {0, C1_7,  C2_7,  C3_7},
    {0, C1_6,  C2_6,  C3_6},
    {0, C1_5,  C2_5,  C3_5},  
    {0, C1_4,  C2_4,  C3_4},  
    {0, C1_3,  C2_3,  C3_3},  
    {0, C1_2,  C2_2,  C4_3},
    {0, C1_1,  C3_2,  C4_2}, //lower left key
    {0, C9_9,  C8_9,  C7_9},  
    {0, C9_10,  C8_10,  C7_10},
    {0, C9_11,  C8_11,  C7_11},
    {0, C9_12,  C8_12,  C7_12} //lower right key

};
