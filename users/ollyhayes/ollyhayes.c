/* Copyright 2022 Olly Hayes (@ollyhayes)
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

#include "ollyhayes.h"

#ifdef VIRTSER_ENABLE
#   include "virtser.h"
#endif

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    if (layer_state_cmp(state, BASE)) {
        rgb_matrix_mode(3);
    } else if (layer_state_cmp(state, GAMES)) {
        rgb_matrix_mode(1);
    }
    return state;
}

uint16_t key_presses = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // for tab/number layer switch
    static bool key_pressed_since_switch = false;
    static uint16_t switch_down_time = 0;

    // for alt-tab on punc layer
    static bool alt_tab_used = false;

    // for capital umlauts
    static bool shift_held = false;

#ifdef VIRTSER_ENABLE
    if (record->event.pressed) {
        uint8_t key_index = 40 + record->event.key.col + record->event.key.row * 6;
        virtser_send(key_index);
    } else {
        uint8_t key_index = 90 + record->event.key.col + record->event.key.row * 6;
        virtser_send(key_index);
    }
#endif

    if (record->event.pressed) {
        key_pressed_since_switch = true;
        key_presses++;
    }

    switch (keycode) {
        case UP4:
            if (record->event.pressed) {
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                tap_code(KC_UP);
                return false;
            }
            break;

        case DOWN4:
            if (record->event.pressed) {
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                return false;
            }
            break;

        case NUM_SWITCH:
            if (record->event.pressed) {
                layer_on(NUM);
                key_pressed_since_switch = false;
                switch_down_time = timer_read();
            } else {
                layer_off(NUM);

                if (!key_pressed_since_switch && timer_elapsed(switch_down_time) < 200) {
                    tap_code(KC_TAB);
                }
            }
            return false;

        case MO(PUNC):
            if (!record->event.pressed) {
                if (alt_tab_used) {
                    unregister_code(KC_LALT);
                    alt_tab_used = false;
                }
            }
            return true;

        case MO(FUNCTIONS):
            if (!record->event.pressed) {
                // if NUM_SWITCH has been lifted first, toggle to that layer
                // (4 = 2^NUM)
                if ((layer_state & 4) != 0) {
                    layer_on(FUNCTIONS);
                    return false;
                }
            }
            return true;

        case ALTTAB:
            if (record->event.pressed) {
                alt_tab_used = true;
                register_code(KC_LALT);
                tap_code(KC_TAB);
            }
            return false;

        case KC_LSFT:
        case KC_RSFT:
            shift_held = record->event.pressed;
            break;

        case A_UMLAUT:
            if (record->event.pressed) {
                if (shift_held)
                    register_unicode(0x00c4);
                else
                    register_unicode(0x00e4);
            }
            break;
        case O_UMLAUT:
            if (record->event.pressed) {
                if (shift_held)
                    register_unicode(0x00d6);
                else
                    register_unicode(0x00f6);
            }
            break;
        case U_UMLAUT:
            if (record->event.pressed) {
                if (shift_held)
                    register_unicode(0x00dc);
                else
                    register_unicode(0x00fc);
            }
            break;
    }
    return true;
}
