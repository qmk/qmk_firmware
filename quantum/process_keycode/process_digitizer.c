/* Copyright 2022
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


#include "digitizer.h"
#include "process_digitizer.h"


bool process_digitizer(uint16_t keycode, keyrecord_t *record) {
    if (IS_DIGITIZER(keycode)) {
        digitizer_t digitizer = digitizer_get_report();
        if (IS_DIGITIZER_BUTTON(keycode)) {
            // OSX ignores some not inrange buttons
            if (record->event.pressed) {
                digitizer.buttons |= DIG_BIT(keycode);
                digitizer.inrange = true;
                digitizer_set_report(digitizer);
            } else {
                digitizer.buttons &= ~DIG_BIT(keycode);
                digitizer.inrange = true;
                digitizer_set_report(digitizer);
            }
        } else if (IS_DIGITIZER_POINTER(keycode)) {
            if (record->event.pressed) {
                uint16_t x, y;
                switch (keycode) {
                    case DZ_POINTER_CENTER:
                        x = DIG_REL2ABS_X(0.5);
                        y = DIG_REL2ABS_Y(0.5);
                        break;
                    case DZ_POINTER_TOP_LEFT:
                        // OSX gets glitchy with (0, 0)
                        x = 1;
                        y = 1;
                        break;
                    case DZ_POINTER_TOP_RIGHT:
                        x = DIGITIZER_MAX_X;
                        y = 1;
                        break;
                    case DZ_POINTER_BOTTOM_LEFT:
                        x = 1;
                        y = DIGITIZER_MAX_Y;
                        break;
                    case DZ_POINTER_BOTTOM_RIGHT:
                        x = DIGITIZER_MAX_X;
                        y = DIGITIZER_MAX_Y;
                        break;
                    case DZ_POINTER_USER0:
                        x = DIGITIZER_USER0_X;
                        y = DIGITIZER_USER0_Y;
                        break;
                    case DZ_POINTER_USER1:
                        x = DIGITIZER_USER1_X;
                        y = DIGITIZER_USER1_Y;
                        break;
                    case DZ_POINTER_USER2:
                        x = DIGITIZER_USER2_X;
                        y = DIGITIZER_USER2_Y;
                        break;
                    case DZ_POINTER_USER3:
                        x = DIGITIZER_USER3_X;
                        y = DIGITIZER_USER3_Y;
                        break;
                    default:
                        x = 0;
                        y = 0;
                        break;
                }
                // Immediately send a "fuzzy" touch sequence near x/y
                digitizer_fuzz_inrange(x, y);
            } else {
                // Immediately end InRange so we can jitter the mouse
                digitizer_unregister_inrange();
#ifdef DIGITIZER_FUZZ_MOUSE
                // Immediately jitter the mouse to encourage OS to render
                digitizer_fuzz_mouse();
#endif
            }
        }
    }
    return true;
}
