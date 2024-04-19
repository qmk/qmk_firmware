/* Protokeeb Copyright 2024 A-Tech Officials 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. 
 * If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */

#include "rev1.h"

#if defined(DIP_SWITCH_ENABLE)
bool dip_switch_update_kb(uint8_t index, bool active) { 
    if(!dip_switch_update_user(index, active))
		{
			return false;
		}
		switch (index) {
        case 0:
						// Encode Push Button Pressed
            if(active) {
							// Toggle Host Mute
							tap_code(KC_MUTE);
						}
						// Encoder Push Button Released
						else {
							// Do Nothing
						}
            break;
		}
		return true;
}
#endif