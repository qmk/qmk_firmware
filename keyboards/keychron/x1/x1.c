/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

static uint8_t win_lock_state = 0;
static uint8_t win_lock_state_datablock_offset = 0;
static uint8_t win_lock_state_datablock_size = 1;

#define SET_LED_WIN_LOCK_ON gpio_write_pin(LED_WIN_LOCK_PIN, LED_WIN_LOCK_PIN_ON_STATE)
#define SET_LED_WIN_LOCK_OFF gpio_write_pin(LED_WIN_LOCK_PIN, !LED_WIN_LOCK_PIN_ON_STATE)

static void set_led_win_lock_state(void) {
    if (win_lock_state) {
        SET_LED_WIN_LOCK_ON;
    } else {
        SET_LED_WIN_LOCK_OFF;
    }
}

void eeconfig_init_kb(void) {
    //if (!eeconfig_is_enabled()) {
    //    eeconfig_init();
    //}
#if (EECONFIG_KB_DATA_SIZE) == 0
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);
#endif
    eeconfig_read_keymap(&keymap_config);
    keymap_config.nkro = 1;
    eeconfig_update_keymap(&keymap_config);

    win_lock_state = 0;
    eeconfig_update_user_datablock(&win_lock_state, win_lock_state_datablock_offset, win_lock_state_datablock_size);

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    gpio_set_pin_output_push_pull(LED_WIN_LOCK_PIN);
    eeconfig_read_user_datablock(&win_lock_state, win_lock_state_datablock_offset, win_lock_state_datablock_size);

    keyboard_post_init_user();
}

void housekeeping_task_kb() {
    set_led_win_lock_state();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case GU_TOGG:
            if (record->event.pressed) {
                win_lock_state = !win_lock_state;
                eeconfig_update_user_datablock(&win_lock_state, win_lock_state_datablock_offset, win_lock_state_datablock_size);
            }
            return true;
        default:
            return true;
    }
}

void suspend_power_down_kb(void) {
    SET_LED_WIN_LOCK_OFF;

    suspend_power_down_user();
}
