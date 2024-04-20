/* Copyright 2019 Jack Humbert
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

#include "process_space_cadet.h"
#include "keycodes.h"
#include "timer.h"
#include "action.h"
#include "action_tapping.h"
#include "action_util.h"

// ********** OBSOLETE DEFINES, STOP USING! (pls?) **********
// Shift / paren setup
#ifndef LSPO_KEY
#    define LSPO_KEY KC_9
#endif
#ifndef RSPC_KEY
#    define RSPC_KEY KC_0
#endif

// Shift / Enter setup
#ifndef SFTENT_KEY
#    define SFTENT_KEY KC_ENTER
#endif

#ifdef DISABLE_SPACE_CADET_MODIFIER
#    ifndef LSPO_MOD
#        define LSPO_MOD KC_TRANSPARENT
#    endif
#    ifndef RSPC_MOD
#        define RSPC_MOD KC_TRANSPARENT
#    endif
#else
#    ifndef LSPO_MOD
#        define LSPO_MOD KC_LEFT_SHIFT
#    endif
#    ifndef RSPC_MOD
#        define RSPC_MOD KC_RIGHT_SHIFT
#    endif
#endif
// **********************************************************

// Shift / paren setup
#ifndef LSPO_KEYS
#    define LSPO_KEYS KC_LEFT_SHIFT, LSPO_MOD, LSPO_KEY
#endif
#ifndef RSPC_KEYS
#    define RSPC_KEYS KC_RIGHT_SHIFT, RSPC_MOD, RSPC_KEY
#endif

// Control / paren setup
#ifndef LCPO_KEYS
#    define LCPO_KEYS KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_9
#endif
#ifndef RCPC_KEYS
#    define RCPC_KEYS KC_RIGHT_CTRL, KC_RIGHT_SHIFT, KC_0
#endif

// Alt / paren setup
#ifndef LAPO_KEYS
#    define LAPO_KEYS KC_LEFT_ALT, KC_LEFT_SHIFT, KC_9
#endif
#ifndef RAPC_KEYS
#    define RAPC_KEYS KC_RIGHT_ALT, KC_RIGHT_SHIFT, KC_0
#endif

// Shift / Enter setup
#ifndef SFTENT_KEYS
#    define SFTENT_KEYS KC_RIGHT_SHIFT, KC_TRANSPARENT, SFTENT_KEY
#endif

static uint8_t  sc_last  = 0;
static uint16_t sc_timer = 0;
#ifdef SPACE_CADET_MODIFIER_CARRYOVER
static uint8_t sc_mods = 0;
#endif

void perform_space_cadet(keyrecord_t *record, uint16_t sc_keycode, uint8_t holdMod, uint8_t tapMod, uint8_t keycode) {
    if (record->event.pressed) {
        sc_last  = holdMod;
        sc_timer = timer_read();
#ifdef SPACE_CADET_MODIFIER_CARRYOVER
        sc_mods = get_mods();
#endif
        if (IS_MODIFIER_KEYCODE(holdMod)) {
            register_mods(MOD_BIT(holdMod));
        }
    } else {
        if (sc_last == holdMod && timer_elapsed(sc_timer) < GET_TAPPING_TERM(sc_keycode, record)) {
            if (holdMod != tapMod) {
                if (IS_MODIFIER_KEYCODE(holdMod)) {
                    unregister_mods(MOD_BIT(holdMod));
                }
                if (IS_MODIFIER_KEYCODE(tapMod)) {
                    register_mods(MOD_BIT(tapMod));
                }
            }
#ifdef SPACE_CADET_MODIFIER_CARRYOVER
            set_weak_mods(sc_mods);
#endif
            tap_code(keycode);
#ifdef SPACE_CADET_MODIFIER_CARRYOVER
            clear_weak_mods();
#endif
            if (IS_MODIFIER_KEYCODE(tapMod)) {
                unregister_mods(MOD_BIT(tapMod));
            }
        } else {
            if (IS_MODIFIER_KEYCODE(holdMod)) {
                unregister_mods(MOD_BIT(holdMod));
            }
        }
    }
}

bool process_space_cadet(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN: {
            perform_space_cadet(record, keycode, LSPO_KEYS);
            return false;
        }
        case QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE: {
            perform_space_cadet(record, keycode, RSPC_KEYS);
            return false;
        }
        case QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN: {
            perform_space_cadet(record, keycode, LCPO_KEYS);
            return false;
        }
        case QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE: {
            perform_space_cadet(record, keycode, RCPC_KEYS);
            return false;
        }
        case QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN: {
            perform_space_cadet(record, keycode, LAPO_KEYS);
            return false;
        }
        case QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE: {
            perform_space_cadet(record, keycode, RAPC_KEYS);
            return false;
        }
        case QK_SPACE_CADET_RIGHT_SHIFT_ENTER: {
            perform_space_cadet(record, keycode, SFTENT_KEYS);
            return false;
        }
        default: {
            if (record->event.pressed) {
                reset_space_cadet();
            }
            break;
        }
    }
    return true;
}

void reset_space_cadet() {
    sc_last = 0;
}
