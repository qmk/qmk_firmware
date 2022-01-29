/* Copyright 2022 Se1enLiang(@skyjun)
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

#include "v1.h"

#include "tp_encoder.h"

void matrix_init_kb(void)
{
    setPinOutput(LED_KEY_PRESS_PIN);
    writePinHigh(LED_KEY_PRESS_PIN);

    matrix_init_user();

    encoder_init();
}

static uint8_t key_tracker  = 0;
bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed)
    {
        key_tracker++;
    }
    else
    {
        key_tracker--;
    }

    writePin(LED_KEY_PRESS_PIN, !key_tracker);

    return process_record_user(keycode, record);
}

void matrix_scan_kb(void)
{
   encoder_scan(); 
}

bool encoder_update_kb(bool clockwise)
{
    if (!encoder_update_user(clockwise)) return false;

    return true;
}