/* Copyright 2021 moults31
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
#include "obs.h"

bool process_record_obs(uint16_t keycode, keyrecord_t *record) {
    // Apply all 4 mods for custom OBS macros
    register_code(KC_LSFT);
    register_code(KC_LCTL);
    register_code(KC_LALT);
    register_code(KC_LGUI);

    switch (keycode) {
        case M_OBS_BRB:
            if (record->event.pressed) {
                SEND_STRING("1");
            }
            break;
        case M_OBS_GAME:
            if (record->event.pressed) {
                SEND_STRING("2");
            }
            break;
        case M_OBS_JSTCHT:
            if (record->event.pressed) {
                SEND_STRING("3");
            }
            break;
        case M_OBS_DSKT_MUTE:
            if (record->event.pressed) {
                SEND_STRING("4");
            }
            break;
        case M_OBS_DSKT_UNMUTE:
            if (record->event.pressed) {
                SEND_STRING("5");
            }
            break;
        case M_OBS_VOICE_MUTE:
            if (record->event.pressed) {
                SEND_STRING("6");
            }
            break;
        case M_OBS_VOICE_UNMUTE:
            if (record->event.pressed) {
                SEND_STRING("7");
            }
            break;
        case M_OBS_MOOSIC_MUTE:
            if (record->event.pressed) {
                SEND_STRING("8");
            }
            break;
        case M_OBS_MOOSIC_UNMUTE:
            if (record->event.pressed) {
                SEND_STRING("9");
            }
            break;
    }

    // Unpress all 4 mods for custom OBS macros
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);

    return true;
}
