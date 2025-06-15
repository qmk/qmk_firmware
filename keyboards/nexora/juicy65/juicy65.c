/* Copyright 2024 keymagichorse
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

#if defined(BLUETOOTH_BHQ)
#   include "bhq.h"
#   include "bhq_common.h"
#endif

#if defined(KB_LPM_ENABLED)
#   include "lpm.h"
#endif

#if defined(KM_DEBUG)
#   include "km_printf.h"
#endif

#if defined(KB_CHECK_BATTERY_ENABLED)
#include "battery.h"
#   endif



void board_init(void) 
{
#if defined(BLUETOOTH_BHQ)
#   if defined(KB_LPM_ENABLED)
    lpm_init();
#   endif
#endif

}
void housekeeping_task_kb(void) {
#if defined(BLUETOOTH_BHQ)
    bhq_switch_host_task();
    #if defined(KB_CHECK_BATTERY_ENABLED)
        battery_percent_read_task();
    #   endif

    #   if defined(KB_LPM_ENABLED)
        lpm_task();
    #   endif
#endif
}



#ifdef RGB_MATRIX_ENABLE 

led_config_t g_led_config = { 
    {
    {  0,  1,  2,  3,  4,      5,  6,      7,       8,      9,  10,  11, 12,    13,  14 },
    {  29, 28, 27, 26, 25,     24, 23,     22,      21,     20, 19,  18, 17,    16,  15 },
    {  30, 31, 32, 33, 34,     35, 36,     37,      38,     39, 40,  41, 42,NO_LED,  43 },
    {  57, 56, 55, 54, 53,     52, 51,     50,      49,     48, 47,  46, 45,NO_LED,  44 },
    {  58, 59, 60, NO_LED, NO_LED, NO_LED, 61, NO_LED,  NO_LED, 62, 63,  64, 65,66,  67,}
    }, {
        {7, 6}, {21, 6}, {35, 6}, {49, 6}, {63, 6}, {77, 6}, {91, 6}, {105, 6}, {119, 6}, {133, 6}, {147, 6}, {161, 6}, {175, 6}, {196, 6}, {217, 6}, {10, 19}, {28, 19}, {42, 19}, {56, 19}, {70, 19}, {84, 19}, {98, 19}, {112, 19}, {126, 19}, {140, 19}, {154, 19}, {168, 19}, {182, 19}, {200, 19}, {217, 19}, {12, 32}, {9, 32}, {32, 32}, {46, 32}, {60, 32}, {74, 32}, {88, 32}, {102, 32}, {116, 32}, {130, 32}, {144, 32}, {158, 32}, {172, 32}, {194, 32}, {217, 32}, {16, 45}, {38, 45}, {52, 45}, {66, 45}, {80, 45}, {94, 45}, {108, 45}, {122, 45}, {136, 45}, {150, 45}, {164, 45}, {184, 45}, {203, 45}, {217, 45}, {9, 58}, {26, 58}, {44, 58}, {96, 58}, {149, 58}, {166, 58}, {189, 58}, {203, 58}, {217, 58}, 
    }, {
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    }
};

#endif

