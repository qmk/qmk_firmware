/**
 * Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 * 
 * This file is part of qmk_firmware.
 * 
 * qmk_firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qmk_firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jjerrell.h"

float game_song[][2] = SONG(TO_BOLDLY_GO);
float work_song[][2] = SONG(MARIO_GAMEOVER);
float doom_song[][2] = SONG(E1M1_DOOM);

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

static uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (process_record_keymap(keycode, record)) {
        static uint8_t mods = 0;
        // static uint8_t layer = 0;
        mods = get_mods();
        switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case KC_WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
            }
            return false;
            break;
        case KC_CCCV:
            if (record->event.pressed) {
                key_timer = timer_read();
            } else {
                clear_mods();
                if (timer_elapsed(key_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(G(KC_C));
                } else if (mods & MOD_MASK_SHIFT) {  
                    // Tap w/ shift held, open [Paste App](https://pasteapp.io) (no affiliation)
                    // Shift + Command(GUI) + V                
                    tap_code16(S(G(KC_V)));
                } else { // Regular tap, do paste
                    tap_code16(G(KC_V));
                }
                set_mods(mods);
            }
            return false;
            break;
        case KC_ARROW:
            if (record->event.pressed) {
                clear_mods();
                if (mods & MOD_MASK_SHIFT) {
                    SEND_STRING("=>");
                } else {
                    SEND_STRING("->"); 
                }
                set_mods(mods);
            }
            return false;
            break;
        case KC_MAKE:
            if (!record->event.pressed) {
#ifndef MAKE_BOOTLOADER
                uint8_t temp_mod = mod_config(get_mods());
                uint8_t temp_osm = mod_config(get_oneshot_mods());
                clear_mods();
                clear_oneshot_mods();
#endif
                send_string_with_delay_P(PSTR("qmk"), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#endif
                {
                    send_string_with_delay_P(PSTR(" flash "), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                } else {
                    send_string_with_delay_P(PSTR(" compile "), TAP_CODE_DELAY);
#endif
                }
                send_string_with_delay_P(PSTR("-kb " QMK_KEYBOARD " -km " QMK_KEYMAP), TAP_CODE_DELAY);
                send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
            }
            return false;
            break;
        case KC_VRSN:
            if (!record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " Built at: " QMK_BUILDDATE), TAP_CODE_DELAY);
            }
            return false;
            break;
        case KC_GAME:
            if (record->event.pressed) {
                key_timer = timer_read();
            } else {
                if (IS_LAYER_OFF(_GAME)) {
                    if (timer_elapsed(key_timer) > TAPPING_TERM) {
                        layer_move(_GAME);
#ifdef AUDIO_ENABLE
PLAY_SONG(game_song);
#endif
                    }
                    break;
                    // todo: cycle game layers
                // } else if (mods & MOD_MASK_SHIFT) {
// #ifdef AUDIO_ENABLE
// PLAY_SONG(doom_song);
// #endif
//                     break;
                } else {
                    layer_move(_WORKMAN);
#ifdef AUDIO_ENABLE
PLAY_SONG(work_song);
#endif
                    break;
                }
            }
            return false;
            break;
        }
    }
    return true;
}
