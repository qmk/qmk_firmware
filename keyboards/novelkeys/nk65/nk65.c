/* Copyright 2019 Yiancar
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
#ifndef RGB_BACKLIGHT_NK65
#error RGB_BACKLIGHT_NK65 not defined, recheck config.h
#endif

#include "nk65.h"
#include "drivers/led/issi/is31fl3733.h"

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_BACKLIGHT_NK65)
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, SW2_CS1,   SW1_CS1,   SW3_CS1}, //LA1
    {0, SW5_CS1,   SW4_CS1,   SW6_CS1}, //LA2
    {0, SW8_CS1,   SW7_CS1,   SW9_CS1}, //LA3
    {0, SW11_CS1,   SW10_CS1,   SW12_CS1}, //LA4
    {0, SW2_CS2,   SW1_CS2,   SW3_CS2}, //LA5
    {0, SW5_CS2,   SW4_CS2,   SW6_CS2}, //LA6
    {0, SW8_CS2,   SW7_CS2,   SW9_CS2}, //LA7
    {0, SW11_CS2,   SW10_CS2,   SW12_CS2}, //LA8
    {0, SW2_CS3,   SW1_CS3,   SW3_CS3}, //LA9
    {0, SW5_CS3,   SW4_CS3,   SW6_CS3}, //LA10
    {0, SW8_CS3,   SW7_CS3,   SW9_CS3}, //LA11
    {0, SW11_CS3,   SW10_CS3,   SW12_CS3}, //LA12
    {0, SW2_CS4,   SW1_CS4,   SW3_CS4}, //LA13
    {0, SW5_CS4,   SW4_CS4,   SW6_CS4}, //LA14
    {0, SW8_CS4,   SW7_CS4,   SW9_CS4}, //LA15
    {0, SW11_CS4,   SW10_CS4,   SW12_CS4}, //LA16
    {0, SW2_CS5,   SW1_CS5,   SW3_CS5}, //LA17
    {0, SW5_CS5,   SW4_CS5,   SW6_CS5}, //LA18
    {0, SW8_CS5,   SW7_CS5,   SW9_CS5}, //LA19
    {0, SW11_CS5,   SW10_CS5,   SW12_CS5}, //LA20
    {0, SW2_CS6,   SW1_CS6,   SW3_CS6}, //LA21
    {0, SW5_CS6,   SW4_CS6,   SW6_CS6}, //LA22
    {0, SW8_CS6,   SW7_CS6,   SW9_CS6}, //LA23
    {0, SW11_CS6,   SW10_CS6,   SW12_CS6}, //LA24
    {0, SW2_CS7,   SW1_CS7,   SW3_CS7}, //LA25
    {0, SW5_CS7,   SW4_CS7,   SW6_CS7}, //LA26
    {0, SW8_CS7,   SW7_CS7,   SW9_CS7}, //LA27
    {0, SW11_CS7,   SW10_CS7,   SW12_CS7}, //LA28
    {0, SW2_CS8,   SW1_CS8,   SW3_CS8}, //LA29
    {0, SW5_CS8,   SW4_CS8,   SW6_CS8}, //LA30
    {0, SW8_CS8,   SW7_CS8,   SW9_CS8}, //LA31
    {0, SW11_CS8,   SW10_CS8,   SW12_CS8}, //LA32
    {0, SW2_CS9,   SW1_CS9,   SW3_CS9}, //LA33
    {0, SW5_CS9,   SW4_CS9,   SW6_CS9}, //LA34
    {0, SW8_CS9,   SW7_CS9,   SW9_CS9}, //LA35
    {0, SW11_CS9,   SW10_CS9,   SW12_CS9}, //LA36
    {0, SW2_CS10,  SW1_CS10,  SW3_CS10}, //LA37
    {0, SW5_CS10,  SW4_CS10,  SW6_CS10}, //LA38
    {0, SW8_CS10,  SW7_CS10,  SW9_CS10}, //LA39
    {0, SW11_CS10,  SW10_CS10,  SW12_CS10}, //LA40
    {0, SW2_CS11,  SW1_CS11,  SW3_CS11}, //LA41
    {0, SW5_CS11,  SW4_CS11,  SW6_CS11}, //LA42
    {0, SW8_CS11,  SW7_CS11,  SW9_CS11}, //LA43
    {0, SW11_CS11,  SW10_CS11,  SW12_CS11}, //LA44
    {0, SW2_CS12,  SW1_CS12,  SW3_CS12}, //LA45
    {0, SW5_CS12,  SW4_CS12,  SW6_CS12}, //LA46
    {0, SW8_CS12,  SW7_CS12,  SW9_CS12}, //LA47
    {0, SW11_CS12,  SW10_CS12,  SW12_CS12}, //LA48
    {0, SW2_CS13,  SW1_CS13,  SW3_CS13}, //LA49
    {0, SW5_CS13,  SW4_CS13,  SW6_CS13}, //LA50
    {0, SW8_CS13,  SW7_CS13,  SW9_CS13}, //LA51
    {0, SW11_CS13,  SW10_CS13,  SW12_CS13}, //LA52
    {0, SW2_CS14,  SW1_CS14,  SW3_CS14}, //LA53
    {0, SW5_CS14,  SW4_CS14,  SW6_CS14}, //LA54
    {0, SW8_CS14,  SW7_CS14,  SW9_CS14}, //LA55
    {0, SW11_CS14,  SW10_CS14,  SW12_CS14}, //LA56
    {0, SW2_CS15,  SW1_CS15,  SW3_CS15}, //LA57
    {0, SW5_CS15,  SW4_CS15,  SW6_CS15}, //LA58
    {0, SW8_CS15,  SW7_CS15,  SW9_CS15}, //LA59
    {0, SW11_CS15,  SW10_CS15,  SW12_CS15}, //LA60
    {0, SW2_CS16,  SW1_CS16,  SW3_CS16}, //LA61
    {0, SW5_CS16,  SW4_CS16,  SW6_CS16}, //LA62
    {0, SW8_CS16,  SW7_CS16,  SW9_CS16}, //LA63
    {0, SW11_CS16,  SW10_CS16,  SW12_CS16}, //LA64

    {1, SW2_CS1,   SW1_CS1,   SW3_CS1}, //LB1
    {1, SW5_CS1,   SW4_CS1,   SW6_CS1}, //LB2
    {1, SW8_CS1,   SW7_CS1,   SW9_CS1}, //LB3
    {1, SW11_CS1,   SW10_CS1,   SW12_CS1}, //LB4
    {1, SW2_CS2,   SW1_CS2,   SW3_CS2}, //LB5
    {1, SW5_CS2,   SW4_CS2,   SW6_CS2}, //LB6
    {1, SW8_CS2,   SW7_CS2,   SW9_CS2}, //LB7
    {1, SW11_CS2,   SW10_CS2,   SW12_CS2}, //LB8
    {1, SW2_CS3,   SW1_CS3,   SW3_CS3}, //LB9
    {1, SW5_CS3,   SW4_CS3,   SW6_CS3}, //LB10
    {1, SW8_CS3,   SW7_CS3,   SW9_CS3}, //LB11
    {1, SW11_CS3,   SW10_CS3,   SW12_CS3}, //LB12
    {1, SW2_CS4,   SW1_CS4,   SW3_CS4}, //LB13
    {1, SW5_CS4,   SW4_CS4,   SW6_CS4}, //LB14
    {1, SW8_CS4,   SW7_CS4,   SW9_CS4}, //LB15
    {1, SW11_CS4,   SW10_CS4,   SW12_CS4}, //LB16
    {1, SW2_CS5,   SW1_CS5,   SW3_CS5}, //LB17
    {1, SW5_CS5,   SW4_CS5,   SW6_CS5}, //LB18
    {1, SW8_CS5,   SW7_CS5,   SW9_CS5}, //LB19
    {1, SW11_CS5,   SW10_CS5,   SW12_CS5}, //LB20
    {1, SW2_CS6,   SW1_CS6,   SW3_CS6}, //LB21
    {1, SW5_CS6,   SW4_CS6,   SW6_CS6}, //LB22
    {1, SW8_CS6,   SW7_CS6,   SW9_CS6}, //LB23
    {1, SW11_CS6,   SW10_CS6,   SW12_CS6}, //LB24
    {1, SW2_CS7,   SW1_CS7,   SW3_CS7}, //LB25
    {1, SW5_CS7,   SW4_CS7,   SW6_CS7}, //LB26
    {1, SW8_CS7,   SW7_CS7,   SW9_CS7}, //LB27
    {1, SW11_CS7,   SW10_CS7,   SW12_CS7}, //LB28
    {1, SW2_CS8,   SW1_CS8,   SW3_CS8}, //LB29
    {1, SW5_CS8,   SW4_CS8,   SW6_CS8}, //LB30
    {1, SW8_CS8,   SW7_CS8,   SW9_CS8}, //LB31
    {1, SW11_CS8,   SW10_CS8,   SW12_CS8}, //LB32
    {1, SW2_CS9,   SW1_CS9,   SW3_CS9}, //LB33
    {1, SW5_CS9,   SW4_CS9,   SW6_CS9}, //LB34
    {1, SW8_CS9,   SW7_CS9,   SW9_CS9}, //LB35
    {1, SW11_CS9,   SW10_CS9,   SW12_CS9}, //LB36
    {1, SW2_CS10,  SW1_CS10,  SW3_CS10}, //LB37
    {1, SW5_CS10,  SW4_CS10,  SW6_CS10}, //LB38
    {1, SW8_CS10,  SW7_CS10,  SW9_CS10}, //LB39
    {1, SW11_CS10,  SW10_CS10,  SW12_CS10}, //LB40
    {1, SW2_CS11,  SW1_CS11,  SW3_CS11}, //LB41
    {1, SW5_CS11,  SW4_CS11,  SW6_CS11}, //LB42
    {1, SW8_CS11,  SW7_CS11,  SW9_CS11}, //LB43
    {1, SW11_CS11,  SW10_CS11,  SW12_CS11}, //LB44
    {1, SW2_CS12,  SW1_CS12,  SW3_CS12}, //LB45
    {1, SW5_CS12,  SW4_CS12,  SW6_CS12}, //LB46
    {1, SW8_CS12,  SW7_CS12,  SW9_CS12}, //LB47
    {1, SW11_CS12,  SW10_CS12,  SW12_CS12}, //LB48
    {1, SW2_CS13,  SW1_CS13,  SW3_CS13}, //LB49
    {1, SW5_CS13,  SW4_CS13,  SW6_CS13}, //LB50
    {1, SW8_CS13,  SW7_CS13,  SW9_CS13}, //LB51
    {1, SW11_CS13,  SW10_CS13,  SW12_CS13}, //LB52
    {1, SW2_CS14,  SW1_CS14,  SW3_CS14}, //LB53
    {1, SW5_CS14,  SW4_CS14,  SW6_CS14}, //LB54
    {1, SW8_CS14,  SW7_CS14,  SW9_CS14}, //LB55
    {1, SW11_CS14,  SW10_CS14,  SW12_CS14}, //LB56
    {1, SW2_CS15,  SW1_CS15,  SW3_CS15}, //LB57
    {1, SW5_CS15,  SW4_CS15,  SW6_CS15}, //LB58
    {1, SW8_CS15,  SW7_CS15,  SW9_CS15}, //LB59
    {1, SW11_CS15,  SW10_CS15,  SW12_CS15}, //LB60
    {1, SW2_CS16,  SW1_CS16,  SW3_CS16}, //LB61
    {1, SW5_CS16,  SW4_CS16,  SW6_CS16}, //LB62
    {1, SW8_CS16,  SW7_CS16,  SW9_CS16}, //LB63
    {1, SW11_CS16,  SW10_CS16,  SW12_CS16}, //LB64
};
#endif

/* Indicator LEDS are part of the LED driver
 * Top LED is blue only. LED driver 2 RGB 7 Green channel
 * Middle LED is blue and red. LED driver 2 RGB 6 Red and Blue channel
 * Bottom LED is red only LED driver 2 RGB 6 Green channel.
 */
void led_update_ports(led_t led_state) {
    if (led_state.caps_lock) {
        is31fl3733_set_color( 7+64-1, 0, 255, 0 );
    } else {
        is31fl3733_set_color( 7+64-1, 0, 0, 0 );
    }
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;
    if (state & (1UL << 1)) {
        R = 255;
        B = 255;
    }
    if (state & (1UL << 2)) {
        G = 255;
    }

    is31fl3733_set_color( 6+64-1, R, G, B );
  return state;
}
