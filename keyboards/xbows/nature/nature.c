/* Copyright 2020 Shulin Huang <mumu@x-bows.com>
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
#include "nature.h"
#include "Peripherals.h"

void matrix_init_kb(void) {
    init_fallacy_leds();
    matrix_init_user();
}

void matrix_scan_kb(void) {
    update_fallacy_leds();
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}
void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
__attribute__ ((weak))

void rgb_matrix_indicators_user(void)
{
    if (IS_LED_ON(host_keyboard_leds(), USB_LED_CAPS_LOCK))
    {
        rgb_matrix_set_color(45, 0xFF, 0x00, 0x00);
    }
}
