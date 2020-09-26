// based on drashna's but I think at this point it's a new axe

#include QMK_KEYBOARD_H
#include "milestogo.h"
#include <print.h>

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool move_is_on = false;  // track if we are in _MOV layer
bool sym_is_on  = false;  // track if we are in _SYM layer

// Defines actions for global custom keycodes
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // static uint16_t spcmov_timer; // timer for spcmov key

#ifdef USE_BABBLEPASTE
    if (keycode > BABBLE_START && keycode < BABBLE_END_RANGE) {
        if (record->event.pressed) {  // is there a case where this isn't desired?
            babblePaste(keycode);
        } else {
            return true;
        }
    }
#endif

    switch (keycode) {
        case _QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;

        case _CDH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_CDH);
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

void babble_led_user(void) {
#ifdef USE_BABLPASTE
    extern uint8_t babble_mode;

#    ifdef BABL_WINDOWS
    if (babble_mode == BABL_WINDOWS_MODE) {
        if (BABL_LED_INDEX > 0) {
            rgblight_setrgb_at(RGBLIGHT_COLOR_MS, BABL_LED_INDEX);
        } else {
            rgblight_setrgb(RGBLIGHT_COLOR_MS);
        }
    }
#    endif
#    ifdef BABL_READMUX
    if (babble_mode == BABL_READMUX_MODE) {
        if (BABL_LED_INDEX > 0) {
            rgblight_setrgb_at(RGBLIGHT_COLOR_READMUX, BABL_LED_INDEX);
        } else {
            rgblight_setrgb(RGBLIGHT_COLOR_READMUX);
        }
    }
#    endif
#    ifdef BABL_MAC
    if (babble_mode == BABL_MAC_MODE) {
        if (BABL_LED_INDEX > 0) {
            rgblight_setrgb_at(RGBLIGHT_COLOR_MAC, BABL_LED_INDEX);
        } else {
            rgblight_setrgb(RGBLIGHT_COLOR_MAC);
        }
    }
#    endif
#    ifdef BABL_VI
    if (babble_mode == BABL_VI_MODE) {
        if (BABL_LED_INDEX > 0) {
            rgblight_setrgb_at(RGBLIGHT_COLOR_VI, BABL_LED_INDEX);
        } else {
            rgblight_setrgb(RGBLIGHT_COLOR_VI);
        }
    }
#    endif
#    ifdef BABL_EMACS
    if (babble_mode == BABL_EMACS_MODE) {
        if (BABL_LED_INDEX > 0) {
            rgblight_setrgb_at(RGBLIGHT_COLOR_EMACS, BABL_LED_INDEX);
        } else {
            rgblight_setrgb(RGBLIGHT_COLOR_EMACS);
        }
    }
#    endif
#    ifdef BABL_CHROMEOS
    if (babble_mode == BABL_CHROMEOS_MODE) {
        if (BABL_LED_INDEX > 0) {
            rgblight_setrgb_at(RGBLIGHT_COLOR_CHROMEOS, BABL_LED_INDEX);
        } else {
            rgblight_setrgb(RGBLIGHT_COLOR_CHROMEOS);
        }
    }
#    endif
#    ifdef BABL_LINUX
    if (babble_mode == BABL_LINUX_MODE) {
        if (BABL_LED_INDEX > 0) {
            rgblight_setrgb_at(RGBLIGHT_COLOR_LINUX, BABL_LED_INDEX);
        } else {
            rgblight_setrgb(RGBLIGHT_COLOR_LINUX);
        }
    }
#    endif
#endif  // bablepaste
}
