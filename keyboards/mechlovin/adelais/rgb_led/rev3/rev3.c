/* Copyright 2021 Team Mechlovin
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
    {0, SW5_CS3, SW5_CS2, SW5_CS1}, /* D9-K31-00 */
    {0, SW5_CS6, SW5_CS5, SW5_CS4}, /* D46-K00-01 */
    {0, SW9_CS6, SW9_CS5, SW9_CS4}, /* D59-K01-02 */
    {0, SW5_CS9, SW5_CS8, SW5_CS7}, /* D73-K02-03 */
    {0, SW9_CS9, SW9_CS8, SW9_CS7}, /* D75-K03-04 */
    {0, SW5_CS12, SW5_CS11, SW5_CS10}, /* D77-K04-05 */
    {0, SW9_CS12, SW9_CS11, SW9_CS10}, /* D79-K05-06 */
    {0, SW5_CS15, SW5_CS14, SW5_CS13}, /* D81-K06-07 */
    {0, SW9_CS15, SW9_CS14, SW9_CS13}, /* D83-K07-08 */
    {0, SW5_CS18, SW5_CS17, SW5_CS16}, /* D85-K08-09 */
    {0, SW9_CS18, SW9_CS17, SW9_CS16}, /* D87-K09-10 */
    {0, SW5_CS21, SW5_CS20, SW5_CS19}, /* D90-K0A-11 */
    {0, SW9_CS21, SW9_CS20, SW9_CS19}, /* D93-K0B-12 */
    {0, SW5_CS24, SW5_CS23, SW5_CS22}, /* D95-K0C-13 */
    {0, SW9_CS24, SW9_CS23, SW9_CS22}, /* D98-K0D-14 */
    {0, SW3_CS24, SW3_CS23, SW3_CS22}, /* D100-K0E-15 */
    {0, SW4_CS3, SW4_CS2, SW4_CS1}, /* D94-K41-16 */
    {0, SW4_CS6, SW4_CS5, SW4_CS4}, /* D92-K10-17 */
    {0, SW6_CS6, SW6_CS5, SW6_CS4}, /* D89-K11-18 */
    {0, SW4_CS9, SW4_CS8, SW4_CS7}, /* D86-K12-19 */
    {0, SW6_CS9, SW6_CS8, SW6_CS7}, /* D84-K13-20 */
    {0, SW4_CS12, SW4_CS11, SW4_CS10}, /* D82-K14-21 */
    {0, SW6_CS12, SW6_CS11, SW6_CS10}, /* D80-K15-22 */
    {0, SW4_CS15, SW4_CS14, SW4_CS13}, /* D78-K16-23 */
    {0, SW6_CS15, SW6_CS14, SW6_CS13}, /* D76-K17-24 */
    {0, SW4_CS18, SW4_CS17, SW4_CS16}, /* D74-K18-25 */
    {0, SW6_CS18, SW6_CS17, SW6_CS16}, /* D72-K19-26 */
    {0, SW4_CS21, SW4_CS20, SW4_CS19}, /* D51-K1A-27 */
    {0, SW6_CS21, SW6_CS20, SW6_CS19}, /* D10-K1B-28 */
    {0, SW4_CS24, SW4_CS23, SW4_CS22}, /* D101-K1C-29 */
    {0, SW6_CS24, SW6_CS23, SW6_CS22}, /* D104-K1D-30 */
    {0, SW3_CS3, SW3_CS2, SW3_CS1}, /* D108-K43-31 */
    {0, SW3_CS6, SW3_CS5, SW3_CS4}, /* D111-K20-32 */
    {0, SW7_CS6, SW7_CS5, SW7_CS4}, /* D114-K21-33 */
    {0, SW3_CS9, SW3_CS8, SW3_CS7}, /* D117-K22-34 */
    {0, SW7_CS9, SW7_CS8, SW7_CS7}, /* D120-K23-35 */
    {0, SW3_CS12, SW3_CS11, SW3_CS10}, /* D123-K24-36 */
    {0, SW7_CS12, SW7_CS11, SW7_CS10}, /* D126-K25-37 */
    {0, SW3_CS15, SW3_CS14, SW3_CS13}, /* D129-K26-38 */
    {0, SW7_CS15, SW7_CS14, SW7_CS13}, /* D133-K27-39 */
    {0, SW3_CS18, SW3_CS17, SW3_CS16}, /* D142-K28-40 */
    {0, SW7_CS18, SW7_CS17, SW7_CS16}, /* D146-K29-41 */
    {0, SW3_CS21, SW3_CS20, SW3_CS19}, /* D160-K2A-42 */
    {0, SW7_CS21, SW7_CS20, SW7_CS19}, /* D167-K2B-43 */
    {0, SW7_CS24, SW7_CS23, SW7_CS22}, /* D168-K2D-44 */

    {0, SW2_CS6, SW2_CS5, SW2_CS4}, /* D163-K30-45 */
    {0, SW8_CS6, SW8_CS5, SW8_CS4}, /* D147-K31-46 */
    {0, SW2_CS9, SW2_CS8, SW2_CS7}, /* D144-K32-47 */
    {0, SW8_CS9, SW8_CS8, SW8_CS7}, /* D137-K33-48 */
    {0, SW2_CS12, SW2_CS11, SW2_CS10}, /* D130-K34-49 */
    {0, SW8_CS12, SW8_CS11, SW8_CS10}, /* D127-K35-50 */
    {0, SW2_CS15, SW2_CS14, SW2_CS13}, /* D124-K36-51 */
    {0, SW8_CS15, SW8_CS14, SW8_CS13}, /* D121-K37-52 */
    {0, SW2_CS18, SW2_CS17, SW2_CS16}, /* D118-K38-53 */
    {0, SW8_CS18, SW8_CS17, SW8_CS16}, /* D115-K39-54 */
    {0, SW2_CS21, SW2_CS20, SW2_CS19}, /* D112-K3A-55 */
    {0, SW8_CS21, SW8_CS20, SW8_CS19}, /* D109-K3B-56 */
    {0, SW2_CS24, SW2_CS23, SW2_CS22}, /* D105-K3D-57 */
    {0, SW8_CS24, SW8_CS23, SW8_CS22}, /* D103-K3E-58 */

    {0, SW1_CS3, SW1_CS2, SW1_CS1}, /* D163-K40-59 */
    {0, SW1_CS6, SW1_CS5, SW1_CS4}, /* D147-K42-60 */
    {0, SW1_CS9, SW1_CS8, SW1_CS7}, /* D137-K44-61 */
    {0, SW1_CS12, SW1_CS11, SW1_CS10}, /* D127-K46-62 */
    {0, SW1_CS15, SW1_CS14, SW1_CS13}, /* D121-K48-63 */
    {0, SW1_CS18, SW1_CS17, SW1_CS16}, /* D115-K4A-64 */
    {0, SW1_CS24, SW1_CS23, SW1_CS22}, /* D103-K4E-65 */
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(32, 255, 255, 255);
    }
    return true;
}


#endif
