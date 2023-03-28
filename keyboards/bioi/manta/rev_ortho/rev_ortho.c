/* Copyright 2022 Basic I/O Instruments (Scott Wei)
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

#include "rev_ortho.h"
#include "quantum.h"


void keyboard_pre_init_kb(void) {
#ifdef LED_CAPS_LOCK_PIN
    setPinOutput(LED_CAPS_LOCK_PIN);
    writePinLow(LED_CAPS_LOCK_PIN);
#endif
#ifdef BLE_CONTROL_PIN
    setPinOutput(BLE_CONTROL_PIN);
    writePinLow(BLE_CONTROL_PIN);
#endif
#ifdef RGB_UG_CONTROL_PIN
    setPinOutput(RGB_UG_CONTROL_PIN);
    writePinLow(RGB_UG_CONTROL_PIN);
#endif
    keyboard_pre_init_user();
}