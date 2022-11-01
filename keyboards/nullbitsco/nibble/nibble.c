/* Copyright 2021 Jay Greco
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
#include QMK_KEYBOARD_H

// Use Bit-C and Big LED to show CAPS LOCK status
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        set_bitc_LED(led_state.caps_lock ? LED_DIM : LED_OFF);
        set_big_LED_r(led_state.caps_lock ? LED_ON : LED_OFF);
    }
    return res;
}

void matrix_init_kb(void) {
    set_bitc_LED(LED_OFF);
    matrix_init_remote_kb();
    matrix_init_user();
}

void keyboard_post_init_kb(void) {
    #ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
    #endif
    keyboard_post_init_user();
}

void matrix_scan_kb(void) {
    matrix_scan_remote_kb();
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
    #ifdef CONSOLE_ENABLE
    dprintf("kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time);
    #endif

    process_record_remote_kb(keycode, record);
    if (!process_record_user(keycode, record)) return false;

    switch (keycode) {
        case RESET:
            if (record->event.pressed) {
                set_big_LED_rgb(LED_OFF, LED_OFF, LED_OFF);
                set_bitc_LED(LED_DIM);
                #ifdef RGBLIGHT_ENABLE
                rgblight_disable_noeeprom();
                #endif
                #ifdef OLED_ENABLE
                oled_off();
                #endif
                bootloader_jump();  // jump to bootloader
            }
            return false;

        default:
            break;
    }

    return true;
}

// Workaround for sleep issues
void suspend_power_down_kb(void) {
    suspend_power_down_user();

    // Turn off Bit-C LED and big LED
    set_bitc_LED(LED_OFF);
    set_big_LED_rgb(LED_OFF, LED_OFF, LED_OFF);

    // Turn off underglow
#    if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    rgblight_suspend();
#    endif
    // Turn off OLED
#    ifdef OLED_ENABLE
    oled_off();
#    endif
}

void suspend_wakeup_init_kb(void) {
    suspend_wakeup_init_user();

    // Wake up underglow
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    rgblight_wakeup();
#endif
}
