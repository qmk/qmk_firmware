/* Copyright 2022 SevenLiang(@skyjun)
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

void matrix_init_kb(void)
{
    setPinOutput(LED_KEY_PRESS_PIN);
    writePinHigh(LED_KEY_PRESS_PIN);

    matrix_init_user();

    // 键盘连接时，获取 CAPS LOCK LED 和 NUM LOCK LED 的状态，并初始化这两个灯的电平状态
    // on powerup, caps lock and num lock light diode init
    led_update_kb(host_keyboard_led_state());
}

bool led_update_kb(led_t led_state)
{
    writePin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
    writePin(LED_NUM_LOCK_PIN, !led_state.num_lock);

    return led_update_user(led_state);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
    writePin(LED_KEY_PRESS_PIN, !record->event.pressed);

    return process_record_user(keycode, record);
}
