/* Copyright 2021 @waffle#0007
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

#include "waffle.h"
#ifdef RANDICT //from ridingqwerty's random word generator
#include "dict.h"
uint16_t rand_key;
bool randword_seed = false;
bool random_word(void) {
  bool rbool = rand() & 1;
  return rbool;
}
#endif
uint16_t alt_tab_timer = 0;
bool is_alt_tab_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    process_record_user_oled(keycode, record);
#endif
    switch (keycode) {
        case CP_PSTE: //copy/paste on hold/release
            if (record->event.pressed) { tap_code16(C(KC_C)); } else {
                tap_code16(C(KC_V));
                tap_code(KC_ENT); }
            return false;

        case ROFL:
            if (record->event.pressed) {
                SEND_STRING("```Incoming ROFLCOPTER!\n"
                            "\n   ROFL:ROFL:ROFL:ROFL\n"
                            "         ___^___ _\n"
                            " L    __/      []  \\ \n"
                            "LOL===__            \\ \n"
                            " L      \\___ ___ ___ ]\n"
                            "           I   I\n"
                            "         ----------/```"SS_TAP(X_ENT));
            }
            break;

        case MT(MOD_LSFT, KC_F23): //allows for shift mod-tap on already shifted keycode
            if (record->tap.count > 0) {
            if (record->event.pressed) { register_code16(KC_EXLM); } else { unregister_code16(KC_EXLM); }
            return false;
            }
            break;

        case MT(MOD_RSFT, KC_F24): //allows for shift mod-tap on already shifted keycode
            if (record->tap.count > 0) {
            if (record->event.pressed) { register_code16(KC_RPRN); } else { unregister_code16(KC_RPRN); }
            return false;
            }
            break;
#ifdef UNICODEMAP_ENABLE
        case UNIT:
            if (record->event.pressed) { send_unicode_string("(＾▽＾)"); } break;
        case UNIT2:
            if (record->event.pressed) { send_unicode_string("≧ω≦"); } break;
        case TABLE1:
            if (record->event.pressed) { send_unicode_hex_string("┬──┬ ノ( ゜-゜ノ)"); } break;
        case TABLE2:
            if (record->event.pressed) { send_unicode_hex_string("(╯°□°)╯︵┻━┻"); } break;
            case DANCE:
            if (record->event.pressed) { send_unicode_hex_string("༼ つ ◕_◕ ༽つ"); } break;
        case SHRUG:
            if (record->event.pressed) { send_unicode_hex_string("¯\\_(ツ)_/¯"); } break;
#endif
#ifdef RANDICT
        case RWORD:
            if (randword_seed == false) {
                randword_seed = true;
                srand(timer_read32());
            }
            rand_key = rand() % NUMBER_OF_WORDS;
            if (record->event.pressed) {
                send_string(dict[rand_key]);
                tap_code(KC_SPC);
            }
            break;
#endif
#ifdef PIMORONI_TRACKBALL
        case BALL_HUI:
            if (record->event.pressed) { ball_increase_hue(); }
            break;
        case BALL_WHT:
            if (record->event.pressed) { cycle_white(); }
            break;
        case BALL_DEC:
            if (record->event.pressed) { decrease_color(); }
            break;
        case BALL_SCR:
            if (record->event.pressed) {
                trackball_set_scrolling(true);
            } else {
                trackball_set_scrolling(false);
            }
            break;
#endif
        case ALT_TAB:
            if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;

        case MAKE:
            if (!record->event.pressed) {
                SEND_STRING("qmk flash -kb " QMK_KEYBOARD " -km " QMK_KEYMAP
#if  (defined(BOOTLOADER_DFU))
                        "-bl dfu"
#elif defined(BOOLOADER_CATERINA)
                        "-bl avrdude"
#elif defined(BOOTLOADER_STM32DUINO)
                        "-bl dfu-util"
#endif
                        SS_TAP(X_ENTER));
            }
            return false;
            break;
    }
    return true;
};

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
