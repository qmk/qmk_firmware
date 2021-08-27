#include QMK_KEYBOARD_H
#include "milestogo.h"
//#include <print.h>

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool move_is_on = false;  // track if we are in _MOV layer
bool sym_is_on  = false;  // track if we are in _SYM layer



// Defines actions for global custom keycodes
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // static uint16_t spcmov_timer; // timer for spcmov key

#ifdef USE_BABBLEPASTE
    if (keycode > BABBLE_START && keycode < BABBLE_END_RANGE) {
        if (record->event.pressed) {
            babblePaste(keycode, 1);
        } else {
            babblePaste(keycode, 0);
        }
    }
#endif

    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                layer_off(_CDH);
                default_layer_set(_QWERTY);
            }
            break;

        case KC_CDH:
            if (record->event.pressed) {
                layer_on(_CDH);
                default_layer_set(_CDH);
            }
            break;

        case TMUX:  // ctl-B
            if (record->event.pressed) {
                tap_code16(C(KC_B));
            }
            break;

            /* Colemak mod-dh moves the D key to the qwerty V position
                        This hack makes apple-V_position do what I mean */
        case DHPASTE:
            if (get_mods() & MOD_BIT(KC_LGUI)) {
                if (record->event.pressed) {
                    clear_keyboard_but_mods();
                    register_code(KC_V);
                } else {
                    unregister_code(KC_V);
                }
            } else {
                if (record->event.pressed) {
                    register_code(KC_D);
                } else {
                    unregister_code(KC_D);
                }
            }
            return false;
            break;

        default:
            return true;
    }

    // normal keycode
    return process_record_keymap(keycode, record);
}

void babble_modeswitch_user(uint8_t bmode) { 
#ifdef USE_BABBLEPASTE
#   ifdef RGBLIGHT_ENABLE
#       ifdef BABL_WINDOWS
    if (BABL_WINDOWS_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_MS, LED_BABL_OS);
    }
#       endif
#       ifdef BABL_READMUX
    if (BABL_READMUX_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_READMUX, LED_BABL_OS);
    }
#       endif
#       ifdef BABL_MAC
    if (BABL_MAC_MODE== bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_MAC, LED_BABL_OS); 
    }
#       endif
#       ifdef BABL_VI
    if (BABL_VI_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_VI, LED_BABL_OS);
    }
#       endif
#       ifdef BABL_EMACS
    if (BABL_EMACS_MODE  == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_EMACS, LED_BABL_OS);
    }
#       endif
#       ifdef BABL_CHROMEOS
    if (BABL_CHROMEOS_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_CHROMEOS, LED_BABL_OS);
    }
#       endif
#       ifdef BABL_KITTY
   if (BABL_KITTY_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_KITTY, LED_BABL_OS);
    }
#       endif
#       ifdef BABL_LINUX
   if (BABL_LINUX_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_LINUX, LED_BABL_OS);
    }
#       endif
#   endif
#endif  // bablepaste
}
