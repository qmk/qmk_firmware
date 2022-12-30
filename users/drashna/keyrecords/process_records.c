// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "drashna.h"
#include "version.h"

uint16_t copy_paste_timer;
bool     host_driver_disabled = false;
// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here

/**
 * @brief Keycode handler for keymaps
 *
 * This handles the keycodes at the keymap level, useful for keyboard specific customization
 */
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}
__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

/**
 * @brief Main user keycode handler
 *
 * This handles all of the keycodes for the user, including calling feature handlers.
 *
 * @param keycode Keycode from matrix
 * @param record keyrecord_t data structure
 * @return true Continue processing keycode and send to host
 * @return false Stop process keycode and do not send to host
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ENCODER_ENABLE // some debouncing for weird issues
    if (IS_ENCODEREVENT(record->event)) {
        static bool ignore_first = true;
        if (ignore_first) {
            ignore_first = false;
            return false;
        }
    }
#endif
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %1d, time: %5u, int: %1d, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif // KEYLOGGER_ENABLE
#if defined(OLED_ENABLE) && defined(CUSTOM_OLED_DRIVER)
    process_record_user_oled(keycode, record);
#endif // OLED

    if (!(process_record_keymap(keycode, record) && process_record_secrets(keycode, record)
#ifdef CUSTOM_RGB_MATRIX
          && process_record_user_rgb_matrix(keycode, record)
#endif
#ifdef CUSTOM_RGBLIGHT
          && process_record_user_rgb_light(keycode, record)
#endif
#ifdef CUSTOM_UNICODE_ENABLE
          && process_record_unicode(keycode, record)
#endif
#if defined(CUSTOM_POINTING_DEVICE)
          && process_record_pointing(keycode, record)
#endif
          && true)) {
        return false;
    }

    switch (keycode) {
        case FIRST_DEFAULT_LAYER_KEYCODE ... LAST_DEFAULT_LAYER_KEYCODE:
            if (record->event.pressed) {
                uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
                if (!mods) {
                    set_single_persistent_default_layer(keycode - FIRST_DEFAULT_LAYER_KEYCODE);
#if LAST_DEFAULT_LAYER_KEYCODE > (FIRST_DEFAULT_LAYER_KEYCODE + 3)
                } else if (mods & MOD_MASK_SHIFT) {
                    set_single_persistent_default_layer(keycode - FIRST_DEFAULT_LAYER_KEYCODE + 4);
#    if LAST_DEFAULT_LAYER_KEYCODE > (FIRST_DEFAULT_LAYER_KEYCODE + 7)

                } else if (mods & MOD_MASK_CTRL) {
                    set_single_persistent_default_layer(keycode - FIRST_DEFAULT_LAYER_KEYCODE + 8);
#    endif
#endif
                }
            }
            break;

        case VRSN: // Prints firmware version
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
            }
            break;

        case KC_DIABLO_CLEAR: // reset all Diablo timers, disabling them
#ifdef TAP_DANCE_ENABLE
            if (record->event.pressed) {
                for (uint8_t index = 0; index < 4; index++) {
                    diablo_timer[index].key_interval = 0;
                }
            }
#endif // TAP_DANCE_ENABLE
            break;

        case KC_CCCV: // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) { // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
        case KC_RGB_T: // This allows me to use underglow as layer indication, or as normal
#if defined(CUSTOM_RGBLIGHT) || defined(CUSTOM_RGB_MATRIX)
            if (record->event.pressed) {
                userspace_config.rgb_layer_change ^= 1;
                dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                eeconfig_update_user(userspace_config.raw);
                if (userspace_config.rgb_layer_change) {
#    if defined(CUSTOM_RGB_MATRIX)
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR);
#        if defined(CUSTOM_RGBLIGHT)
                    rgblight_enable_noeeprom();
#        endif
#    endif
                    layer_state_set(layer_state); // This is needed to immediately set the layer color (looks better)
#    if defined(CUSTOM_RGB_MATRIX)
                } else {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
#        if defined(CUSTOM_RGBLIGHT)
                    rgblight_disable_noeeprom();
#        endif
#    endif
                }
            }
#endif // CUSTOM_RGBLIGHT
            break;

#if defined(CUSTOM_RGBLIGHT) || defined(CUSTOM_RGB_MATRIX)
        case RGB_TOG:
            // Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
#    if defined(CUSTOM_RGBLIGHT) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                rgblight_toggle();
#    endif
#    if defined(CUSTOM_RGB_MATRIX) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                rgb_matrix_toggle();
#    endif
            }
            return false;
            break;
        case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // quantum_keycodes.h L400 for definitions
            if (record->event.pressed) {
                bool is_eeprom_updated;
#    if defined(CUSTOM_RGBLIGHT) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                // This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
                if (userspace_config.rgb_layer_change) {
                    userspace_config.rgb_layer_change = false;
                    dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                    is_eeprom_updated = true;
                }
#    endif
#    if defined(CUSTOM_RGB_MATRIX) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
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
            break;
#endif
        case KEYLOCK: {
            static host_driver_t *host_driver = 0;

            if (record->event.pressed) {
                if (host_get_driver()) {
                    host_driver = host_get_driver();
                    clear_keyboard();
                    host_set_driver(0);
                    host_driver_disabled = true;
                } else {
                    host_set_driver(host_driver);
                    host_driver_disabled = false;
                }
            }
            break;
        }
    }
    return true;
}

__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    post_process_record_keymap(keycode, record);
}
