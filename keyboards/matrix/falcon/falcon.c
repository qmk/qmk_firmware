/**
 * falcon.c
 *   Copyright 2021 astro 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "falcon.h"
#include "wait.h"

void matrix_init_kb(void)
{
    // enable charge
    setPinOutput(CHG_EN_PIN);
    writePinHigh(CHG_EN_PIN);

    // enable led power
    setPinOutput(LED_POWER_PIN);
    writePinHigh(LED_POWER_PIN);

    // clear caps led
    setPinOutput(CAPS_PIN);
    writePinLow(CAPS_PIN);
}

bool led_update_kb(led_t led_state)
{
    bool res = led_update_user(led_state);
    if (res) {
        writePin(CAPS_PIN, led_state.caps_lock);
    }
    return res;
}

void keyboard_post_init_user(void)
{
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}