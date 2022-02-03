// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "template.h"

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__((weak)) void matrix_init_keymap(void) {}

// Call user matrix init, then call the keymap's init function
void matrix_init_user(void) { matrix_init_keymap(); }

__attribute__((weak)) void matrix_scan_keymap(void) {}

// No global matrix scan code, so just run keymap's matix
// scan function
void matrix_scan_user(void) { matrix_scan_keymap(); }

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's recod handier if not processed here,
// And use "NEWPLACEHOLDER" for new safe range
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MAKE:
            if (!record->event.pressed) {
                SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP
#if (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
                            ":dfu"
#elif defined(BOOTLOADER_HALFKAY)
                            ":teensy"
#elif defined(BOOTLOADER_CATERINA)
                            ":avrdude"
#endif
                            SS_TAP(X_ENTER));
            }
            return false;
            break;

        case VRSN:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            return false;
            break;
    }
    return process_record_keymap(keycode, record);
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state) { return layer_state_set_keymap(state); }

__attribute__((weak)) void led_set_keymap(uint8_t usb_led) {}

void led_set_user(uint8_t usb_led) { led_set_keymap(usb_led); }

__attribute__((weak)) void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) { suspend_power_down_keymap(); }

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
    suspend_wakeup_init_keymap();
#ifdef KEYBOARD_ergodox_ez
    wait_ms(10);
#endif
}

__attribute__((weak)) void startup_keymap(void) {}

void startup_user(void) {
#ifdef RGBLIGHT_ENABLE
    matrix_init_rgb();
#endif  // RGBLIGHT_ENABLE
    startup_keymap();
}

__attribute__((weak)) void shutdown_keymap(void) {}

void shutdown_user(void) { shutdown_keymap(); }
