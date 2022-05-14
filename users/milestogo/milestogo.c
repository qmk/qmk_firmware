/*
 * Copyright 2022 milestogo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "milestogo.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef USE_BABBLEPASTE
    if (!process_babblepaste(keycode, record)) {
        return false;
    }
#endif

    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                layer_off(_CDH);
                // default_layer_set(_QWERTY);
            }
            return false;
            break;

        case KC_CDH:
            if (record->event.pressed) {
                layer_on(_CDH);
            }
            break;

        case VRSN: // Prints firmware version
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
            }
            return false;
            break;
    }
    return process_record_keymap(keycode, record);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_Z):
            return TAPPING_TERM + 275;
        case SFT_T(KC_SLASH):
            return TAPPING_TERM + 175;
        case SMOVE:
            return TAPPING_TERM + 150;
        default:
            return TAPPING_TERM;
    }
}

/// This only affects modifier keys, not layers.

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_Z):
            // Do not force the mod-tap key press to be handled as a modifier
            // if any other key was pressed while the mod-tap key is held down.
            return true;
        case SFT_T(KC_SLASH):
            return true;
        default:
            // Force the mod-tap key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return false;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SMOVE:
            return false; // less irritating to type space twice than to delete extra space after a move action
        default:
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ESCSYM:
            // Immediately select the hold action when another key is pressed.
            return true;
        case SMOVE:
            return false; // minimize fast typing probs
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

void babble_modeswitch_user(uint8_t bmode) {
#ifdef USE_BABBLEPASTE
#    ifdef RGBLIGHT_ENABLE
#        ifdef BABL_WINDOWS
    if (BABL_WINDOWS_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_MS, LED_BABL_OS);
    }
#        endif
#        ifdef BABL_READMUX
    if (BABL_READMUX_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_READMUX, LED_BABL_OS);
    }
#        endif
#        ifdef BABL_MAC
    if (BABL_MAC_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_MAC, LED_BABL_OS);
    }
#        endif
#        ifdef BABL_VI
    if (BABL_VI_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_VI, LED_BABL_OS);
    }
#        endif
#        ifdef BABL_EMACS
    if (BABL_EMACS_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_EMACS, LED_BABL_OS);
    }
#        endif
#        ifdef BABL_CHROMEOS
    if (BABL_CHROMEOS_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_CHROMEOS, LED_BABL_OS);
    }
#        endif
#        ifdef BABL_KITTY
    if (BABL_KITTY_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_KITTY, LED_BABL_OS);
    }
#        endif
#        ifdef BABL_LINUX
    if (BABL_LINUX_MODE == bmode) {
        rgblight_setrgb_at(RGBLIGHT_COLOR_LINUX, LED_BABL_OS);
    }
#        endif
#    endif
#endif // bablepaste
}
