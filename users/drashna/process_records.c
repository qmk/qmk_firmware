/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "drashna.h"
#include "version.h"

uint16_t copy_paste_timer;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %b, time: %5u, int: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif  // KEYLOGGER_ENABLE
#ifdef OLED_DRIVER_ENABLE
    process_record_user_oled(keycode, record);
#endif  // OLED

    if (!(process_record_keymap(keycode, record) && process_record_secrets(keycode, record)
#ifdef RGB_MATRIX_ENABLE
          && process_record_user_rgb_matrix(keycode, record)
#endif
#ifdef RGBLIGHT_ENABLE
          && process_record_user_rgb_light(keycode, record)
#endif
          && true)) {
        return false;
    }

    switch (keycode) {
        case KC_QWERTY ... KC_WORKMAN:
            if (record->event.pressed) {
                uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
                if (!mods) {
                    set_single_persistent_default_layer(keycode - KC_QWERTY);
                } else if (mods & MOD_MASK_SHIFT) {
                    set_single_persistent_default_layer(keycode - KC_QWERTY + 4);
                } else if (mods & MOD_MASK_CTRL) {
                    set_single_persistent_default_layer(keycode - KC_QWERTY + 8);
                }
            }
            break;

        case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
#ifndef MAKE_BOOTLOADER
                uint8_t temp_mod = mod_config(get_mods());
                uint8_t temp_osm = mod_config(get_oneshot_mods());
                clear_mods();
                clear_oneshot_mods();
#endif
                send_string_with_delay_P(PSTR("qmk"), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#endif
                {
                    send_string_with_delay_P(PSTR(" flash "), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                } else {
                    send_string_with_delay_P(PSTR(" compile "), TAP_CODE_DELAY);
#endif
                }
                send_string_with_delay_P(PSTR("-kb " QMK_KEYBOARD " -km " QMK_KEYMAP), TAP_CODE_DELAY);
#ifdef RGB_MATRIX_SPLIT_RIGHT
                send_string_with_delay_P(PSTR(" RGB_MATRIX_SPLIT_RIGHT=yes"), TAP_CODE_DELAY);
#    ifndef OLED_DRIVER_ENABLE
                send_string_with_delay_P(PSTR(" OLED_DRIVER_ENABLE=no"), TAP_CODE_DELAY);
#    endif
#endif
                send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
            }

            break;

        case VRSN:  // Prints firmware version
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
            }
            break;

        case KC_DIABLO_CLEAR:  // reset all Diablo timers, disabling them
#ifdef TAP_DANCE_ENABLE
            if (record->event.pressed) {
                for (uint8_t index = 0; index < 4; index++) {
                    diablo_timer[index].key_interval = 0;
                }
            }
#endif  // TAP_DANCE_ENABLE
            break;

        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else {  // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
#ifdef UNICODE_ENABLE
        case UC_FLIP:  // (ノಠ痊ಠ)ノ彡┻━┻
            if (record->event.pressed) {
                send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
            }
            break;
        case UC_TABL:  // ┬─┬ノ( º _ ºノ)
            if (record->event.pressed) {
                send_unicode_string("┬─┬ノ( º _ ºノ)");
            }
            break;
        case UC_SHRG:  // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            break;
        case UC_DISA:  // ಠ_ಠ
            if (record->event.pressed) {
                send_unicode_string("ಠ_ಠ");
            }
            break;
#endif
        case KC_RGB_T:  // This allows me to use underglow as layer indication, or as normal
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                userspace_config.rgb_layer_change ^= 1;
                dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                eeconfig_update_user(userspace_config.raw);
                if (userspace_config.rgb_layer_change) {
#    if defined(RGBLIGHT_ENABLE) && defined(RGB_MATRIX_ENABLE)
                    rgblight_enable_noeeprom();
#    endif
                    layer_state_set(layer_state);  // This is needed to immediately set the layer color (looks better)
#    if defined(RGBLIGHT_ENABLE) && defined(RGB_MATRIX_ENABLE)
                } else {
                    rgblight_disable_noeeprom();
#    endif
                }
            }
#endif  // RGBLIGHT_ENABLE
            break;

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        case RGB_TOG:
            // Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
#    if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                rgblight_toggle();
#    endif
#    if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                rgb_matrix_toggle();
#    endif
            }
            return false;
            break;
        case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT:  // quantum_keycodes.h L400 for definitions
            if (record->event.pressed) {
                bool is_eeprom_updated;
#    if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                // This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
                if (userspace_config.rgb_layer_change) {
                    userspace_config.rgb_layer_change = false;
                    dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                    is_eeprom_updated = true;
                }
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
                if (userspace_config.rgb_matrix_idle_anim) {
                    userspace_config.rgb_matrix_idle_anim = false;
                    dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                    is_eeprom_updated = true;
                }
#    endif
                if (is_eeprom_updated) {
                    eeconfig_update_user(userspace_config.raw);
                }
            }
#endif
    }
    return true;
}
