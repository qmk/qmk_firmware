/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <jcblake@outlook.com>
   
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

#include "caps_word.h"

#ifdef TD_LSFT_CAPSLOCK_ENABLE
// Tap once for shift, twice for Caps Lock but only if Win Key in not disabled
void dance_LSFT_each_tap(qk_tap_dance_state_t * state, void * user_data) {
    if (state -> count == 1 || keymap_config.no_gui) {
        register_code16(KC_LSFT);
    } else {
        register_code(KC_CAPS);
    }
}

void dance_LSFT_reset(qk_tap_dance_state_t * state, void * user_data) {
    if (state -> count == 1 || keymap_config.no_gui) {
        unregister_code16(KC_LSFT);
    } else {
        unregister_code(KC_CAPS);
        unregister_code16(KC_LSFT);
    }
}
// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for shift, twice for Caps Lock
    [TD_LSFT_CAPSLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_LSFT_CAPS_WIN] = ACTION_TAP_DANCE_FN_ADVANCED(dance_LSFT_each_tap, NULL, dance_LSFT_reset),
    // Tap once for Escape, twice to reset to base layer
    [TD_ESC_BASELYR] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ESC, _BASE),
};
#endif // TD_LSFT_CAPSLOCK_ENABLE

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
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    if (!process_caps_word(keycode, record)) {
        return false;
    }

    // Your macros ...
    switch (keycode) {

    // DotCom domain macros
    case DOTCOM:
        if (record -> event.pressed) {
            SEND_STRING(".com");
        } else {
            // when keycode is released
        }
        break;
    case YAHOO:
        if (record -> event.pressed) {
            SEND_STRING("yahoo.com");
        } else {
            // when keycode is released
        }
        break;
    case OUTLOOK:
        if (record -> event.pressed) {
            SEND_STRING("outlook.com");
        } else {
            // when keycode is released
        }
        break;
    case GMAIL:
        if (record -> event.pressed) {
            SEND_STRING("gmail.com");
        } else {
            // when keycode is released
        }
        break;
    case HOTMAIL:
        if (record -> event.pressed) {
            SEND_STRING("hotmail.com");
        } else {
            // when keycode is released
        }
        break;
		
/*
    case YAHOO:
        if (record -> event.pressed) SEND_STRING("yahoo.com");
        else unregister_code16(keycode);
        break;
    case OUTLOOK:
        if (record -> event.pressed) SEND_STRING("outlook.com");
        else unregister_code16(keycode);
        break;
    case GMAIL:
        if (record -> event.pressed) SEND_STRING("gmail.com");
        else unregister_code16(keycode);
        break;
    case HOTMAIL:
        if (record -> event.pressed) {
            SEND_STRING("hotmail.com");
        } else unregister_code16(keycode);
        break;
    case DOTCOM:
        if (record -> event.pressed) SEND_STRING(".com");
        else unregister_code16(keycode);
        break;
*/

    // Windows key lock		
    case KC_WINLCK:
        if (record -> event.pressed) {
            keymap_config.no_gui = !keymap_config.no_gui; //toggle status
        } else unregister_code16(keycode);
        break;

    // Double Zero    
    case KC_00:
        if (record -> event.pressed) {
            // when keycode KC_00 is pressed
            SEND_STRING("00");
        } else unregister_code16(keycode);
        break;

    // Treat Control+Space as if regular Space
    case KC_SPC: {
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

    // Treat Shift+Space as if regular Space
    case KC_SHIFTSPC: {
        // Initialize a boolean variable that keeps track of the space key status: registered or not?
        static bool spc2key_registered;
        if (record -> event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_SPC keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_SPC);
                // Update the boolean variable to reflect the status of KC_SPC
                spc2key_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Space key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_SPC
            // In case KC_SPC is still being sent even after the release of KC_SPC
            if (spc2key_registered) {
                unregister_code(KC_SPC);
                spc2key_registered = false;
                return false;
            }
        }
        }
        break;

    // Add INS as SHIFT-modified BackSpace key
    case KC_BSPC: {
        // Initialize a boolean variable that keeps track of the delete key status: registered or not?
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
                // still work even after having tapped the Delete/Insert key.
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
        break;

    /* Add INS as SHIFT-modified DEL key
    case KC_DEL: {
        // Initialize a boolean variable that keeps track of the delete key status: registered or not?
        static bool inskey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_INS keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_INS);
                // Update the boolean variable to reflect the status of KC_INS
                inskey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Delete/Insert key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_DEL
            // In case KC_INS is still being sent even after the release of KC_DEL
            if (inskey_registered) {
                unregister_code(KC_INS);
                inskey_registered = false;
                return false;
            }
        }
        }
        break;
    */

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
        if (record -> event.pressed) SEND_STRING("`\\_(\"/)_/`");
        else unregister_code16(keycode);
        break;
    case EMO_CONFUSE:
        if (record -> event.pressed) SEND_STRING("(*_*)");
        else unregister_code16(keycode);
        break;
    case EMO_TEARS:
        if (record -> event.pressed) SEND_STRING("(T_T)");
        else unregister_code16(keycode);
        break;
    case EMO_NERVOUS:
        if (record -> event.pressed) SEND_STRING("(~_~;)");
        else unregister_code16(keycode);
        break;
    case EMO_JOY:
        if (record -> event.pressed) SEND_STRING("(^o^)");
        else unregister_code16(keycode);
        break;
    case EMO_SAD:
        if (record -> event.pressed) SEND_STRING(":'-(");
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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t * record) {
    switch (keycode) {
    case KC_SFTUP:
        return 300;
    case KC_RAISESPC:
    case KC_LOWERSPC:
        return 450;
    default:
        return TAPPING_TERM;
    }
}

// Turn on/off NUM LOCK if current state is different
void activate_numlock(bool turn_on) {
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK) != turn_on) {
        tap_code(KC_NUMLOCK);
    }
}

// INITIAL STARTUP

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    keyboard_post_init_keymap();
    #ifdef STARTUP_NUMLOCK_ON
    activate_numlock(true); // turn on Num lock by default so that the numpad layer always has predictable results
    #endif // STARTUP_NUMLOC_ON
    #ifdef IDLE_TIMEOUT_ENABLE
    timeout_timer = timer_read(); // set inital time for ide timeout
    #endif
}