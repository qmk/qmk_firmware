// Copyright 2022 Kevin Goldberg @kevkevco <hello@kevkev.co>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_records.h"

// Super cmd↯TAB initializations
bool     is_cmd_tab_active = false;
uint16_t cmd_tab_timer     = 0;

// This function holds the main switch statement for keycode definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Caps word
    if (!process_caps_word(keycode, record)) {
        return false;
    }

    // Num word
    if (!process_record_num_word(keycode, record)) {
        return false;
    }

    // Select word macro from https://getreuer.info/posts/keyboards/select-word/index.html
    if (!process_select_word(keycode, record, SELWORD)) {
        return false;
    }

    // Store the current modifier state in a variable for later reference
    mod_state = get_mods();

    switch (keycode) {
        case LT(0, KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_X)); // Intercept hold function to send CMD+X
                return false;
            }
            return true; // Return true for normal processing of tap key code

        case LT(0, KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_C)); // Intercept hold function to send CMD+C
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_V):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_V)); // Intercept hold function to send CMD+V
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_Z):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_Z)); // Intercept hold function to send CMD+Z
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_Y):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(SGUI(KC_Z)); // Intercept hold function to send CMD+SHIFT+Z for MacOS standard redo
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_Q):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_Q)); // Intercept hold function to send CMD+Q
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_W):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_W)); // Intercept hold function to send CMD+W
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_T):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_T)); // Intercept hold function to send CMD+T
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_B):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_B)); // Intercept hold function to send CMD+T
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_N):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_N)); // Intercept hold function to send CMD+T
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LT(0, KC_R):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_R)); // Intercept hold function to send CMD+T
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        // Shortcut for QMK compiling in terminal
        // Add CMD for QMK compiling in terminal AND application switch Teensy and activate program (flashing) mode
        // Add SHIFT for only the latter
        case QMK:
            if (record->event.pressed && !(mod_state & MOD_MASK_SHIFT)) {
                clear_mods();
                tap_code16(MEH(KC_E));
                SEND_STRING(SS_DELAY(500) "cd ~/code/github/qmk_firmware");
                tap_code(KC_ENT);
                SEND_STRING("qmk compile");
                tap_code(KC_ENT);
                SEND_STRING(SS_DELAY(2000));
            }
            if (record->event.pressed && ((mod_state & MOD_MASK_GUI) || (mod_state & MOD_MASK_SHIFT))) {
                clear_mods();
                SEND_STRING(SS_DELAY(300));
                tap_code16(MEH(KC_1));
                SEND_STRING(SS_DELAY(300));
                set_mods(MOD_MASK_CTRL);
                add_oneshot_mods(MOD_MASK_CTRL);
                tap_code(KC_B);
                return false;
            }
            return false; // Return true for normal processing of tap keycode

        case CLEAR: // Clears all keycodes currently pressed, including modifiers
            if (record->event.pressed) {
                clear_keyboard();
                return false;
            }
            return true; // Return true for normal processing of tap keycode

        case LGUI_T(KC_BSPC):
        case HYPR_T(KC_BSPC): {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT || get_oneshot_mods() & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_LNUM); // Dummy keypress to get rid of lingering one shot modifier shift that seems to be a bug
                    register_code(KC_DEL);
                    set_mods(mod_state);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    del_mods(MOD_MASK_SHIFT);
                    unregister_code(KC_DEL);
                    set_mods(mod_state);
                    delkey_registered = false;
                    return false;
                }
            }
            return true;
        }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;

        case APP_NAV:
            // Super cmd↯TAB modified for MacOS to CMD_TAB
            // This macro will register KC_LGUI and tap KC_TAB, then wait for 1000ms.
            // If the key is tapped again, it will send another KC_TAB and restart timer.
            // If there is no tap within 800ms, KC_LGUI will be unregistered, thus allowing you to cycle through windows.
            // Press shift key with APP_NAV key to send Shift+Cmd+Tab which iterates through the application switcher window backwards.
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
            return true;

        case KPSWAP:
            if (record->event.pressed) {
                layer_invert(_KEYPAD);
                layer_invert(_LKEYPAD);
                return false;
            }
            return true;

        case (ESC_STS):
            if (mod_state & MOD_MASK_GUI) {
                tap_code(KC_ESC);
                // if (mod_state & MOD_MASK_ALT);
                // tap_code(KC_ESC);
                return false;
            }
            // return true;
            else if (mod_state & MOD_MASK_SHIFT || get_oneshot_mods() & MOD_MASK_SHIFT) {
                // Detect the activation of either shift keys
                if (record->event.pressed) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the following code
                    del_mods(MOD_MASK_SHIFT);

                    SEND_STRING("Firmware> QMK " QMK_VERSION ", " QMK_BUILDDATE "\n");
                    SEND_STRING("Keyboard> " QMK_KEYBOARD "\n");
                    SEND_STRING("Keymap> " QMK_KEYMAP "\n");

                    if (keymap_config.nkro)
                        SEND_STRING("NKRO> Enabled\n");
                    else
                        SEND_STRING("NKRO> Disabled\n");

                    if (debug_enable)
                        SEND_STRING("Debug> Enabled\n");
                    else
                        SEND_STRING("Debug> Disabled\n");

                    // Reapplying modifier state so that the held shift key(s) still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else if (record->event.pressed) {
                // Esc key activated without either shift key
                register_code(KC_ESC);
                return false;
            } else {
                // On release of Esc key if Status was not executed
                unregister_code(KC_ESC);
                return false;
            }
            break;
        default:
            break;
    }
    return true; // Return true for normal processing of tap keycode
}