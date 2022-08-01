/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <gourdo1@outlook.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "gourdo1.h"

#include "custom_double_taps.h"

// Tap once for shift, twice for Caps Lock but only if Win Key is not disabled (also disabled by user.config variable)
void dance_LSFT_each_tap(qk_tap_dance_state_t * state, void * user_data) {
    if (user_config.double_tap_shift_for_capslock) {
        if (state -> count == 1 || keymap_config.no_gui) {
            register_code(KC_LSFT);
        } else {
            register_code(KC_CAPS);
        }
    } else {
        register_code(KC_LSFT);
    }
}

void dance_LSFT_reset(qk_tap_dance_state_t * state, void * user_data) {
    if (state -> count == 1 || keymap_config.no_gui) {
        unregister_code(KC_LSFT);
    } else {
        unregister_code(KC_CAPS);
        unregister_code(KC_LSFT);
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for shift, twice for Caps Lock
    [TD_LSFT_CAPS_WIN] = ACTION_TAP_DANCE_FN_ADVANCED(dance_LSFT_each_tap, NULL, dance_LSFT_reset)
};

// RGB NIGHT MODE
#ifdef RGB_MATRIX_ENABLE
static bool rgb_nightmode = false;

// Turn on/off NUM LOCK if current state is different
void activate_rgb_nightmode(bool turn_on) {
    if (rgb_nightmode != turn_on) {
        rgb_nightmode = !rgb_nightmode;
    }
}

bool get_rgb_nightmode(void) {
    return rgb_nightmode;
}
#endif // RGB_MATRIX_ENABLE

// TIMEOUTS
#ifdef IDLE_TIMEOUT_ENABLE
static uint16_t timeout_timer = 0;
static uint16_t timeout_counter = 0; //in minute intervals
static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

uint16_t get_timeout_threshold(void) {
    return timeout_threshold;
}

void timeout_reset_timer(void) {
    timeout_timer = timer_read();
    timeout_counter = 0;
};

void timeout_update_threshold(bool increase) {
    if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
    if (!increase && timeout_threshold > 0) timeout_threshold--;
};

void timeout_tick_timer(void) {
    if (timeout_threshold > 0) {
        if (timer_elapsed(timeout_timer) >= 60000) { // 1 minute tick
            timeout_counter++;
            timeout_timer = timer_read();
        }
        #ifdef RGB_MATRIX_ENABLE
        if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
            rgb_matrix_disable_noeeprom();
        }
        #endif
    } // timeout_threshold = 0 will disable timeout
}

#endif // IDLE_TIMEOUT_ENABLE

#if defined(ALTTAB_SCROLL_ENABLE) || defined(IDLE_TIMEOUT_ENABLE) // timer features
__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    #ifdef ALTTAB_SCROLL_ENABLE
    encoder_tick_alttabscroll();
    #endif
    #ifdef IDLE_TIMEOUT_ENABLE
    timeout_tick_timer();
    #endif
    matrix_scan_keymap();
}
#endif // ALTTAB_SCROLL_ENABLE or IDLE_TIMEOUT_ENABLE

// Initialize variable holding the binary representation of active modifiers.
uint8_t mod_state;

// ============================================= PROCESS KEY CODES =============================================

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t * record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t * record) {
    mod_state = get_mods();
    if (!process_record_keymap(keycode, record)) { return false; }
    if (!process_capsnum(keycode, record)) { return false; }
    if (!process_esc_to_base(keycode, record)) { return false; }

    // Key macros ...
    switch (keycode) {

        // User configuration toggles
    case PRNCONF:  // Print verbose status of all user_config toggles (open a text editor before engaging!!)
        if (record->event.pressed) {
            //send_string("Left bracket with alt numcodes "SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_0) SS_TAP(X_KP_9) SS_TAP(X_KP_1))"\n");
            send_string("\n\x2D\x2D\x2D\x2D\x2D\x2D\x2D\x2D\x2D\x3C\x3C\x3C\x3C\x3C\x3C\x3C\x3C\x3C");
            send_string(" gourdo1\x27s GMMK Pro User Settings ");
            send_string("\x3E\x3E\x3E\x3E\x3E\x3E\x3E\x3E\x3E\x2D\x2D\x2D\x2D\x2D\x2D\x2D\x2D\x2D\n");
            send_string("Hold \x5B \bFn\x5D and the number corresponding to a setting below to toggle.\n");
            send_string("Re-print this screen with \x5B \bFn\x5D \x5B`\x5D to see your changes reflected.\n");
            send_string("Config also visible as RGB under number keys by holding \x5B \bFn\x5D.\n");
            send_string("\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d");
            send_string("\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d");
            send_string("\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d");
            send_string("\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\n");
            send_string("1. CapsLock RGB highlight alpha keys................ ");
            if (user_config.rgb_hilite_caps) {
                send_string("\x5BON\x5D\n");
            } else {
                send_string("\x5BOFF\x5D\n");
            }
            send_string("2. Numpad RGB highlight layer keys.................. ");
            if (user_config.rgb_hilite_numpad) {
                send_string("\x5BON\x5D\n");
            } else {
                send_string("\x5BOFF\x5D\n");
            }
            send_string("3. Double tap ESC to revert to BASE layer........... ");
            if (user_config.esc_double_tap_to_baselyr) {
                send_string("\x5BON\x5D\n");
            } else {
                send_string("\x5BOFF\x5D\n");
            }
            send_string("4. DEL \x26 HOME key locations......................... ");
            if (user_config.del_right_home_top) {
                send_string("\x5BHOME on F13\x3B DEL right of BKSPC\x5D\n");
            } else {
                send_string("\x5B \bDEL on F13\x3B HOME right of BKSPC\x5D\n");
            }
            send_string("5. Numpad on CapsLock\x3B double tap LSHIFT for Caps... ");
            if (user_config.double_tap_shift_for_capslock) {
                send_string("\x5BON\x5D\n");
            } else {
                send_string("\x5BOFF\x5D\n");
            }
            send_string("6. Encoder button function.......................... ");
            if (user_config.encoder_press_mute_or_media) {
                send_string("\x5BMUTE\x5D\n");
            } else {
                send_string("\x5BMEDIA PLAY\x2FPAUSE\x5D\n");
            }
            send_string("7. Insert function accessed with.................... ");
            if (user_config.ins_on_shft_bkspc_or_del) {
                send_string("\x5BSHIFT\x2D \bBKSPC\x5D\n");
            } else {
                send_string("\x5BSHIFT\x2D \bDEL\x5D\n");
            }
            send_string("8. Force SHIFT \x26 CTRL\x2DSPACE to function like SPACE.. ");
            if (user_config.disable_space_mods) {
                send_string("\x5BON\x5D\n");
            } else {
                send_string("\x5BOFF\x5D\n");
            }
            send_string("\nThe latest firmware updates are always here\x3a https\x3a\x2F\x2Fgithub.com\x2Fgourdo1\x2Fgmmkpro\x2Dmedia\n");
        }
        break;

    case TG_CAPS:  // Toggle RGB highlighting of Capslock state
        if (record->event.pressed) {
            user_config.rgb_hilite_caps ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        }
        break;
    case TG_PAD:  // Toggle RGB highlighting of Numpad state
        if (record->event.pressed) {
            user_config.rgb_hilite_numpad ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        }
        break;
    case TG_ESC:  // Toggle alternate ESC functionality
        if (record->event.pressed) {
            user_config.esc_double_tap_to_baselyr ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        }
        break;
    case TG_DEL:  // Toggle alternate placement of DEL and HOME keys
        if (record->event.pressed) {
            user_config.del_right_home_top ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        }
        break;
    case TG_TDCAP:  // Toggle alternate Capslock/Numpad functionality
        if (record->event.pressed) {
            user_config.double_tap_shift_for_capslock ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        }
        break;
    case TG_ENC:  // Toggle Encoder function
        if (record->event.pressed) {
            user_config.encoder_press_mute_or_media ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        }
        break;
    case TG_INS:  // Toggle Encoder function
        if (record->event.pressed) {
            user_config.ins_on_shft_bkspc_or_del ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        }
        break;
    case TG_SPCMOD:  // Toggle forcing SHIFT&CTRL-SPACE to function like SPACE
        if (record->event.pressed) {
            user_config.disable_space_mods ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        }
        break;
        //return false;

        // Key to the left of encoder function (default HOME)
    case LEFTOFENC:
        if (!(user_config.del_right_home_top)) {
            if (!(user_config.ins_on_shft_bkspc_or_del)) {
                static bool inskey_registered;
                if (record -> event.pressed) {
                    // Detect the activation of either shift keys
                    if (mod_state & MOD_MASK_SHIFT) {
                        // First temporarily canceling both shifts so that
                        // shift isn't applied to the KC_INS keycode
                        del_mods(MOD_MASK_SHIFT);
                        register_code(KC_INS);
                        // Update the boolean variable to reflect the status of KC_INS
                        inskey_registered = true;
                        // Reapplying modifier state so that the held shift key(s)
                        // still work even after having tapped the key.
                        set_mods(mod_state);
                        return false;
                    } else {
                        register_code(KC_DEL);
                        return false;
                    }
                } else { // on release of KC_DEL
                    // In case KC_INS is still being sent even after the release of KC_DEL
                    if (inskey_registered) {
                        unregister_code(KC_INS);
                        inskey_registered = false;
                        return false;
                    } else {
                        unregister_code(KC_DEL);
                        return false;
                    }
                }
            } else {
                if (record -> event.pressed) {
                    register_code(KC_DEL);
                    return false;
                } else {
                    unregister_code(KC_DEL);
                    return false;
                }
            }
        } else {
            if (record -> event.pressed) {
                register_code(KC_HOME);
                return false;
            } else {
                unregister_code(KC_HOME);
                return false;
            }
        }
        break;

        // Key below encoder function (default DEL)
    case BELOWENC:
        if (user_config.del_right_home_top) {
            if (!(user_config.ins_on_shft_bkspc_or_del)) {
                static bool inskey_registered;
                if (record -> event.pressed) {
                    // Detect the activation of either shift keys
                    if (mod_state & MOD_MASK_SHIFT) {
                        // First temporarily canceling both shifts so that
                        // shift isn't applied to the KC_INS keycode
                        del_mods(MOD_MASK_SHIFT);
                        register_code(KC_INS);
                        // Update the boolean variable to reflect the status of KC_INS
                        inskey_registered = true;
                        // Reapplying modifier state so that the held shift key(s)
                        // still work even after having tapped the key.
                        set_mods(mod_state);
                        return false;
                    } else {
                        register_code(KC_DEL);
                        return false;
                    }
                } else { // on release of KC_DEL
                    // In case KC_INS is still being sent even after the release of KC_DEL
                    if (inskey_registered) {
                        unregister_code(KC_INS);
                        inskey_registered = false;
                        return false;
                    } else {
                        unregister_code(KC_DEL);
                        return false;
                    }
                }
            } else {
                if (record -> event.pressed) {
                    register_code(KC_DEL);
                    return false;
                } else {
                    unregister_code(KC_DEL);
                    return false;
                }
            }
        } else {
            if (record -> event.pressed) {
                register_code(KC_HOME);
                return false;
            } else {
                unregister_code(KC_HOME);
                return false;
            }
        }
        break;

        // Encoder button function
    case ENCFUNC:
        if (user_config.encoder_press_mute_or_media) {
            if (record -> event.pressed) {
                register_code(KC_MUTE);
            } else unregister_code16(keycode);
        }
        else {
            if (record -> event.pressed) {
                register_code(KC_MPLY);
            } else unregister_code16(keycode);
        }
        break;

        // DotCom domain macros
    case DOTCOM:
        if (record -> event.pressed) {
            send_string(".com");
        } else {
            // when keycode is released
        }
        break;
    case YAHOO:
        if (record -> event.pressed) {
            send_string("yahoo.com");
        } else {
            // when keycode is released
        }
        break;
    case OUTLOOK:
        if (record -> event.pressed) {
            send_string("outlook.com");
        } else {
            // when keycode is released
        }
        break;
    case GMAIL:
        if (record -> event.pressed) {
            send_string("gmail.com");
        } else {
            // when keycode is released
        }
        break;
    case HOTMAIL:
        if (record -> event.pressed) {
            send_string("hotmail.com");
        } else {
            // when keycode is released
        }
        break;

        // Windows Key lockout
    case WINLOCK:
        if (record -> event.pressed) {
            keymap_config.no_gui = !keymap_config.no_gui; //toggle status
        } else unregister_code16(keycode);
        break;

        // Double Zero
    case KC_00:
        if (record -> event.pressed) {
            // when keycode KC_00 is pressed
            send_string("00");
        } else unregister_code16(keycode);
        break;

        // Treat Control & Shift-Space as if regular Space
    case KC_SPC:
        if (user_config.disable_space_mods) {
            // Initialize a boolean variable that keeps track of the space key status: registered or not?
            static bool spckey_registered;
            if (record -> event.pressed) {
                // Detect the activation of either ctrl keys
                if (mod_state & MOD_MASK_CTRL) {
                    // First temporarily canceling both ctrls so that
                    // ctrl isn't applied to the KC_SPC keycode
                    del_mods(MOD_MASK_CTRL);
                    register_code(KC_SPC);
                    // Update the boolean variable to reflect the status of KC_SPC
                    spckey_registered = true;
                    // Reapplying modifier state so that the held ctrl key(s)
                    // still work even after having tapped the Space key.
                    set_mods(mod_state);
                    return false;
                }
                else if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_SPC keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_SPC);
                    // Update the boolean variable to reflect the status of KC_SPC
                    spckey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Space key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_SPC
                // In case KC_SPC is still being sent even after the release of KC_SPC
                if (spckey_registered) {
                    unregister_code(KC_SPC);
                    spckey_registered = false;
                    return false;
                }
            }
        }
        break;

    // INS as SHIFT-modified BackSpace key
    case KC_BSPC: {
        if (user_config.ins_on_shft_bkspc_or_del) {
            // Initialize a boolean variable that keeps track of the ins key status: registered or not?
            static bool inskey_registered;
            if (record -> event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_INS keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_INS);
                    // Update the boolean variable to reflect the status of KC_INS
                    inskey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_INS is still being sent even after the release of KC_BSPC
                if (inskey_registered) {
                    unregister_code(KC_INS);
                    inskey_registered = false;
                    return false;
                }
            }
        }
    }
    break;

    #ifdef IDLE_TIMEOUT_ENABLE
    case RGB_TOI:
        if (record -> event.pressed) {
            timeout_update_threshold(true);
        } else unregister_code16(keycode);
        break;
    case RGB_TOD:
        if (record -> event.pressed) {
            timeout_update_threshold(false); //decrease timeout
        } else unregister_code16(keycode);
        break;
        #endif // IDLE_TIMEOUT_ENABLE
        #ifdef RGB_MATRIX_ENABLE
    case RGB_NITE:
        if (record -> event.pressed) {
            rgb_nightmode = !rgb_nightmode;
        } else unregister_code16(keycode);
        break;
        #endif // RGB_MATRIX_ENABLE

        #ifdef EMOTICON_ENABLE
    case EMO_SHRUG:
        if (record -> event.pressed) send_string("`\\_(\"/)_/`");
        else unregister_code16(keycode);
        break;
    case EMO_CONFUSE:
        if (record -> event.pressed) send_string("(*_*)");
        else unregister_code16(keycode);
        break;
    case EMO_TEARS:
        if (record -> event.pressed) send_string("(T_T)");
        else unregister_code16(keycode);
        break;
    case EMO_NERVOUS:
        if (record -> event.pressed) send_string("(~_~;)");
        else unregister_code16(keycode);
        break;
    case EMO_JOY:
        if (record -> event.pressed) send_string("(^o^)");
        else unregister_code16(keycode);
        break;
    case EMO_SAD:
        if (record -> event.pressed) send_string(":'-(");
        else unregister_code16(keycode);
        break;
        #endif // EMOTICON_ENABLE

        #ifdef ALTTAB_SCROLL_ENABLE
    case KC_TSTOG:
        if (record -> event.pressed) encoder_toggle_alttabscroll();
        else unregister_code16(keycode);
        break;
        #endif // ALTTAB_SCROLL_ENABLE

    default:
        if (record -> event.pressed) {
            #ifdef RGB_MATRIX_ENABLE
            rgb_matrix_enable();
            #endif
            #ifdef IDLE_TIMEOUT_ENABLE
            timeout_reset_timer(); //reset activity timer
            #endif
        }
        break;
    }
    return true;
};

// Define custom Caps Word continuity characters
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_TILD:
        case KC_UNDS:
        case KC_DQT:
        case KC_COLN:
        case KC_RSFT:
        case LSFTCAPSWIN:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_GRV:
        case KC_MINS:
        case KC_QUOT:
        case KC_SCLN:
        case KC_BSPC:
        case KC_DEL:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// Turn on/off NUM LOCK if current state is different
void activate_numlock(bool turn_on) {
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK) != turn_on) {
        tap_code(KC_NUMLOCK);
    }
}

// INITIAL STARTUP
__attribute__((weak)) void keyboard_post_init_keymap(void) {
}

void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    keyboard_post_init_keymap();
    #ifdef STARTUP_NUMLOCK_ON
    activate_numlock(true); // turn on Num lock by default so that the numpad layer always has predictable results
    #endif // STARTUP_NUMLOCK_ON
    #ifdef IDLE_TIMEOUT_ENABLE
    timeout_timer = timer_read(); // set initial time for idle timeout
    #endif
}

/* Set defaults for EEPROM user configuration variables */
void eeconfig_init_user(void) {
    user_config.raw                           = 0;
    user_config.rgb_hilite_caps               = true;
    user_config.rgb_hilite_numpad             = true;
    user_config.double_tap_shift_for_capslock = true;
    user_config.del_right_home_top            = true;
    user_config.encoder_press_mute_or_media   = true;
    user_config.esc_double_tap_to_baselyr     = true;
    user_config.ins_on_shft_bkspc_or_del      = true;
    user_config.disable_space_mods            = true;

    eeconfig_update_user(user_config.raw);
}
