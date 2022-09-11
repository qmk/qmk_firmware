/*  A library to output the right key shortcut in any common app.
Given a global variable babble_mode to show the environment and a
key that calls the paste macro, do the right type of paste.
Setting the context is done by another macro, or TBD interaction with the host.

Huge thanks to https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
and https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/jeebak/keymap.c
*/

#include QMK_KEYBOARD_H

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

// GLOBAL variable to determine mode.  Sets startup default if no eeppom
uint8_t babble_mode = 0;

// functions to tell the user that the mode has changed
__attribute__((weak)) void babble_modeswitch_user(uint8_t mode) {}
__attribute__((weak)) void babble_modeswitch_kb(uint8_t mode) { babble_modeswitch_user( mode); }



void set_babble_mode(uint8_t id) { babble_mode = id; }

void babble_mode_increment() {
    babble_mode += 1;
    if (babble_mode >= BABL_MODEMAX) {
        babble_mode = 0;
    }
    babble_modeswitch_kb(babble_mode);
}

void babble_mode_decrement() {
    if (babble_mode >= 1) {
        babble_mode -= 1;
    } else {
        babble_mode = BABL_MODEMAX - 1;
    }
    babble_modeswitch_kb(babble_mode);
}

/* this function runs the appropriate babblepaste macro, given
the global babble_mode and a keycode defined in the babble_keycodes enum.

This could be made faster by splitting into functions sorted by keycode range
But that makes for a *lot* of ifdefs.
*/
bool babblePaste(uint16_t keycode, bool is_pressed )  {
    // handle keys that have up & down behavior first, then OS/mode switching, then macros

// This is the key used for cut & paste (Propeller on Mac, Control elsewhere)
#   ifdef BABL_MODSWAP
    // WARNING, this assumes you have BABL_MAC_MODE defined. 
    if (keycode == BABL_PRIMARY_OS_MOD ) {
        if (babble_mode == BABL_MAC_MODE) {
            if (is_pressed) {
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LGUI);
            }
        } else { // everybody else 

            if (is_pressed) {
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
            }
        }
    }

// This is the os key not used in cut & paste. (CTRL on mac, GUI elsewhere)
    if (keycode == BABL_SECONDARY_OS_MOD ) {
        if (babble_mode == BABL_MAC_MODE) {
                if (is_pressed) {
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
            }

        } else { // everybody else 
            if (is_pressed) {
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LGUI);
            }
        }
    }

// This is the alt key in most OSes. Mostly useful if you want to do hyper on one OS, Meh on another.  
    if (keycode == BABL_TERTIARY_OS_MOD ) {
        if (babble_mode == BABL_MAC_MODE) {
            if (is_pressed) {
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
            }
        } else { // everybody else 

            if (is_pressed) {
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
            }
        }
    }

#   endif 

// below here we are only running macros - don't serve any key up events. 
    if (is_pressed == 0 ) {
           return true;
    }

// handle increment functions. 

if (keycode == BABL_MODE_INCREMENT) {
        babble_mode_increment();
        return true;
}

if (keycode == BABL_MODE_DECREMENT) {
        babble_mode_decrement();
        return true;
}

#    ifdef BABL_MAC
    if (keycode == BABL_DO_MAC) {
        set_babble_mode(BABL_MAC_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }

    if (babble_mode == BABL_MAC_MODE) {
        babblePaste_mac(keycode);
    }
#    endif

#    ifdef BABL_VI
    if (keycode == BABL_DO_VI) {
        set_babble_mode(BABL_VI_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }
    if (babble_mode == BABL_VI_MODE) {
        babblePaste_vi(keycode);
    }
#    endif
#    ifdef BABL_WINDOWS
    if (keycode == BABL_DO_WINDOWS) {
        set_babble_mode(BABL_WINDOWS_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }
    if (babble_mode == BABL_WINDOWS_MODE) {
        babblePaste_win(keycode);
    }
#    endif
#    ifdef BABL_LINUX
    if (keycode == BABL_DO_LINUX) {
        set_babble_mode(BABL_LINUX_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }
    if (babble_mode == BABL_LINUX_MODE) {
        babblePaste_linux(keycode);
    }
#    endif
#    ifdef BABL_EMACS
    if (keycode == BABL_DO_EMACS) {
        set_babble_mode(BABL_EMACS_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }
    if (babble_mode == BABL_EMACS_MODE) {
        babblePaste_emacs(keycode);
    }
#    endif
#    ifdef BABL_NANO
    if (keycode == BABL_DO_NANO) {
        set_babble_mode(BABL_NANO_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }
    if (babble_mode == BABL_NANO_MODE) {
        babblePaste_nano(keycode);
    }
#    endif
#    ifdef BABL_KITTY
    if (keycode == BABL_DO_KITTY) {
        set_babble_mode(BABL_KITTY_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }
    if (babble_mode == BABL_KITTY_MODE) {
        babblePaste_kitty(keycode);
    }
#    endif
#    ifdef BABL_CHROMEOS
    if (keycode == BABL_DO_CHROMEOS) {
        set_babble_mode(BABL_CHROMEOS_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }
    if (babble_mode == BABL_CHROMEOS_MODE) {
        babblePaste_chromeos(keycode);
    }
#    endif
#    ifdef BABL_READMUX
    if (keycode == BABL_DO_READMUX) {
        set_babble_mode(BABL_READMUX_MODE);
        babble_modeswitch_kb(babble_mode);
        return true;
    }
    if (babble_mode == BABL_READMUX_MODE) {
        babblePaste_readmux(keycode);
    }
#    endif

    return false;
}

#endif  // USE_BABBLEPASTE
