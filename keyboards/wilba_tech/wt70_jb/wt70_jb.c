/* Copyright 2020 Jason Williams (Wilba)
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

bool g_first_execution = false;

// This is some magic so that PCBs flashed with VIA firmware at the factory
// will start with an RGB test pattern. Not relevant for non-VIA firmware.
#ifdef VIA_ENABLE

// Called from via_init() if VIA_ENABLE
// Called from matrix_init_kb() if not VIA_ENABLE
void via_init_kb(void)
{
    // This checks both an EEPROM reset (from bootmagic lite, keycodes)
    // and also firmware build date (from via_eeprom_is_valid())
    if (eeconfig_is_enabled()) {
    } else	{
        // Cache "first execution" state so we can do something
        // specific after QMK initialization has done its thing.
        g_first_execution = true;
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void keyboard_post_init_kb(void) {
    // This is a workaround to ensure "EEPROM cleared" PCBs will
    // start with the RGB test mode, essential for testing LEDs.
    if ( g_first_execution ) {
        rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
    }
}

#endif // VIA_ENABLE
