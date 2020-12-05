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

// small function that we might also want to call from a keymap.

// GLOBAL variable to determine mode.  Sets startup default if no eeppom
uint8_t babble_mode = 0;

// function to tell the user that the mode has changed
__attribute__((weak)) void babble_led_user(void) {}

void set_babble_mode(uint8_t id) { babble_mode = id; }

void babble_mode_increment() {
    babble_mode += 1;
    if (babble_mode >= BABL_MODEMAX) {
        babble_mode = 0;
    }
}

void babble_mode_decrement() {
    if (babble_mode >= 1) {
        babble_mode -= 1;
    } else {
        babble_mode = BABL_MODEMAX - 1;
    }
}

/* this function runs the appropriate babblepaste macro, given
the global babble_mode and a keycode defined in the babble_keycodes enum.

This could be made faster by splitting into two functions sorted by keycode range
But that makes for a *lot* of ifdefs.
*/
bool babblePaste(uint16_t keycode) {
    // handle the OS/mode  switching first

#    ifdef BABL_MAC
    if (keycode == BABL_DO_MAC) {
        set_babble_mode(BABL_MAC_MODE);
        babble_led_user();
        return true;
    }

    if (babble_mode == BABL_MAC_MODE) {
        babblePaste_mac(keycode);
    }
#    endif

#    ifdef BABL_VI
    if (keycode == BABL_DO_VI) {
        set_babble_mode(BABL_VI_MODE);
        babble_led_user();
        return true;
    }
    if (babble_mode == BABL_VI_MODE) {
        babblePaste_vi(keycode);
    }
#    endif
#    ifdef BABL_WINDOWS
    if (keycode == BABL_DO_WINDOWS) {
        set_babble_mode(BABL_WINDOWS_MODE);
        babble_led_user();
        return true;
    }
    if (babble_mode == BABL_WINDOWS_MODE) {
        babblePaste_win(keycode);
    }
#    endif
#    ifdef BABL_LINUX
    if (keycode == BABL_DO_LINUX) {
        set_babble_mode(BABL_LINUX_MODE);
        babble_led_user();
        return true;
    }
    if (babble_mode == BABL_LINUX_MODE) {
        babblePaste_linux(keycode);
    }
#    endif
#    ifdef BABL_EMACS
    if (keycode == BABL_DO_EMACS) {
        set_babble_mode(BABL_EMACS_MODE);
        babble_led_user();
        return true;
    }
    if (babble_mode == BABL_EMACS_MODE) {
        babblePaste_emacs(keycode);
    }
#    endif
#    ifdef BABL_CHROME
    if (keycode == BABL_DO_CHROMEOS) {
        set_babble_mode(BABL_CHROMEOS_MODE);
        babble_led_user();
        return true;
    }
    if (babble_mode == BABL_CHROMEOS_MODE) {
        babblePaste_readmux(keycode);
    }
#    endif
#    ifdef BABL_READMUX
    if (keycode == BABL_DO_READMUX) {
        set_babble_mode(BABL_READMUX_MODE);
        babble_led_user();
        return true;
    }
    if (babble_mode == BABL_READMUX_MODE) {
        babblePaste_readmux(keycode);
    }
#    endif

    return false;
}

#endif  // USE_BABBLEPASTE
