// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_quantum.h"
#include "quantum.h"

#ifdef ENABLE_COMPILE_KEYCODE
/** \brief Compiles the firmware, and adds the flash command based on keyboard bootloader
 */
static void send_make_command(void) {
#    ifdef NO_ACTION_ONESHOT
    const uint8_t temp_mod = mod_config(get_mods());
#    else
    const uint8_t temp_mod = mod_config(get_mods() | get_oneshot_mods());
    clear_oneshot_mods();
#    endif
    clear_mods();

    SEND_STRING_DELAY("qmk", TAP_CODE_DELAY);
    if (temp_mod & MOD_MASK_SHIFT) { // if shift is held, flash rather than compile
        SEND_STRING_DELAY(" flash ", TAP_CODE_DELAY);
    } else {
        SEND_STRING_DELAY(" compile ", TAP_CODE_DELAY);
    }
#    if defined(CONVERTER_ENABLED)
    SEND_STRING_DELAY("-kb " QMK_KEYBOARD " -km " QMK_KEYMAP " -e CONVERT_TO=" CONVERTER_TARGET SS_TAP(X_ENTER), TAP_CODE_DELAY);
#    else
    SEND_STRING_DELAY("-kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER), TAP_CODE_DELAY);
#    endif
    if (temp_mod & MOD_MASK_SHIFT && temp_mod & MOD_MASK_CTRL) {
        reset_keyboard();
    }
}
#endif

bool process_quantum(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
#ifndef NO_RESET
            case QK_BOOTLOADER:
                reset_keyboard();
                return false;
            case QK_REBOOT:
                soft_reset_keyboard();
                return false;
#endif
#ifndef NO_DEBUG
            case QK_DEBUG_TOGGLE:
                debug_enable ^= 1;
                if (debug_enable) {
                    print("DEBUG: enabled.\n");
                } else {
                    print("DEBUG: disabled.\n");
                }
                return false;
#endif
            case QK_CLEAR_EEPROM:
#ifdef NO_RESET
                eeconfig_init();
#else
                eeconfig_disable();
                soft_reset_keyboard();
#endif
                return false;
#ifdef ENABLE_COMPILE_KEYCODE
            case QK_MAKE:
                send_make_command();
                return false;
#endif
            default:
                break;
        }
    }

    return true;
}
