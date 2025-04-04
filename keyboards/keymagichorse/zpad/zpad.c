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
#endif

#if defined(KB_LPM_ENABLED)
#   include "lpm.h"
#endif

#if defined(KM_DEBUG)
#   include "km_printf.h"
#endif

#if defined(KB_CHECK_BATTERY_ENABLED)
    extern void battery_percent_read_task(void);
#   endif

void board_init(void) 
{
#if defined(BLUETOOTH_BHQ)
#   if defined(KB_LPM_ENABLED)
    lpm_init();
#   endif
#endif


}


void keyboard_post_init_kb(void) {
#   if defined(KM_DEBUG)
    km_printf_init();
    km_printf("hello rtt log1111111\r\n");
#   endif
}
void housekeeping_task_kb(void) {
#if defined(BLUETOOTH_BHQ)

    #if defined(KB_CHECK_BATTERY_ENABLED)
        battery_percent_read_task();
    #   endif

    #   if defined(KB_LPM_ENABLED)
        lpm_task();
    #   endif
#endif

}
