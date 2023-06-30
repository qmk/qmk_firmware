/* Copyright 2020 Gondolindrim
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

void board_init(void) {
    setPinInput(B6);
    setPinInput(B7);
#if defined (LINE_RGBS)
    rgblight_set_effect_range(0,16);
#elif defined (RUNE_RGBS)
    rgblight_set_effect_range(0,5);
#elif defined (LUKE_RGBS)
    rgblight_set_effect_range(0,2);
#endif
}

#define LED_PIN_ON_STATE 1

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
    return res;
}
