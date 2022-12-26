/* Copyright 2020 Brandon Schlack
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
#include "brandonschlack.h"

// Super CMD↯TAB
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

// Consolidated Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QM_MAKE: // Sends 'qmk compile' or 'qmk flash'
            if (record->event.pressed) {
                bool flash = false;
        // If is a keyboard and auto-flash is not set in rules.mk,
        // then Shift will trigger the flash command
        #if !defined(FLASH_BOOTLOADER) && !defined(IS_MACROPAD)
                uint8_t temp_mod = get_mods();
                uint8_t temp_osm = get_oneshot_mods();
                clear_mods();
                clear_oneshot_mods();
                if ( (temp_mod | temp_osm) & MOD_MASK_SHIFT )
        #endif
                {
                    flash = true;
                }
                send_make_command(flash);
            }
            break;
        case QM_FLSH: // Sends flash command instead of compile
            if (record->event.pressed) {
                clear_mods();
                clear_oneshot_mods();
                send_make_command(true);
            }
            break;
        case QM_VRSN:  // Prints firmware version
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
            }
            break;
        case QM_KYBD:  // Prints keyboard path
            if (record->event.pressed) {
                SEND_STRING("keyboards/" QMK_KEYBOARD "/");
            }
            break;
        case QM_KYMP:  // Prints keymap path
            if (record->event.pressed) {
                SEND_STRING("keyboards/" QMK_KEYBOARD "/keymaps/" QMK_KEYMAP "/keymap.c");
            }
            break;
        case CMD_TAB: // Super CMD↯TAB
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        #if defined(RGB_THEME_ENABLE)
        case RGB_LYR:
            if (record->event.pressed) {
                user_config.rgb_layer_change ^= 1;
                dprintf("rgb layer change [EEPROM]: %u\n", user_config.rgb_layer_change);
                eeconfig_update_user(user_config.raw);
                if (user_config.rgb_layer_change) {
                    layer_state_set(layer_state);
                }
            }
            break;
        case RGB_HUI ... RGB_SAD:
            if (record->event.pressed) {
                if (user_config.rgb_layer_change) {
                    user_config.rgb_layer_change = false;
                    dprintf("rgb layer change [EEPROM]: %u\n", user_config.rgb_layer_change);
                    eeconfig_update_user(user_config.raw);
                }
            }
            break;
        case RGB_THEME_FORWARD:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT));
                if(shifted) {
                    rgb_theme_step_reverse();
                } else {
                    rgb_theme_step();
                }
                layer_state_set(layer_state);
            }
            break;
        case RGB_THEME_REVERSE:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT));
                if(shifted) {
                    rgb_theme_step();
                } else {
                    rgb_theme_step_reverse();
                }
                layer_state_set(layer_state);
            }
            break;
        #endif
    }
    return process_record_keymap(keycode, record);
}

// Super CMD↯TAB
void matrix_scan_cmd_tab(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 500) {
            unregister_code(KC_LGUI);
            is_cmd_tab_active = false;
        }
    }
}

/**
 * Send Make Command
 *
 * Sends 'qmk compile -kb keyboard -km keymap' command to compile firmware
 * Uses 'qmk flash' and resets keyboard, if flash_bootloader set to true
 * Sends CTPC and/or FORCE_LAYOUT parameters if built with those options
 */
void send_make_command(bool flash_bootloader) {
#ifdef FORCE_LAYOUT // Add layout string if built with FORCE_LAYOUT
    SEND_STRING("FORCE_LAYOUT=" FORCE_LAYOUT " ");
#endif
#ifdef CONVERT_TO_PROTON_C // Add CTPC if built with CONVERT_TO_PROTON_C
    SEND_STRING("CTPC=yes ");
#endif
    SEND_STRING("qmk ");
    if (flash_bootloader) {
#ifndef KEYBOARD_massdrop // Don't run flash for Massdrop boards
        SEND_STRING("flash ");
    } else {
#endif
        SEND_STRING("compile ");
    }
    SEND_STRING("-kb " QMK_KEYBOARD " ");
    SEND_STRING("-km " QMK_KEYMAP);
    if (flash_bootloader) {
#if defined(KEYBOARD_massdrop) // only run for Massdrop boards
        SEND_STRING(" && mdlflash " QMK_KEYBOARD " " QMK_KEYMAP);
#endif
    }
    SEND_STRING(SS_TAP(X_ENTER));
    if (flash_bootloader) {
        reset_keyboard();
    }
}
