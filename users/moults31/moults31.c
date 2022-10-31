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
#include "moults31.h"

bool moults31_tap_custom_code(uint16_t keycode) {
    keyrecord_t record = {
        .event = {
            .pressed = 1,
        },
    };
    return process_record_user(keycode, &record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool rv = true;
    switch (keycode) {
        case M_MST_CODEBLOCK:
            if (record->event.pressed) {
                SEND_STRING("```");
            }
            break;

        case M_VSC_TERMFOCUS:
        case M_VSC_SIDEBARFOCUS:
        case M_VSC_SIDEBARCLOSE:
        case M_VSC_FILECLOSE:
        case M_VSC_FILENXT:
        case M_VSC_FILEPRV:
        case M_VSC_DBGCNSLFOCUS:
        case M_VSC_MVEDTRNXTGRP:
        case M_VSC_MVEDTRPRVGRP:
        case M_VSC_EDGRPNXT:
        case M_VSC_EDGRPPRV:
        case M_VSC_VIEWSIZEINC:
        case M_VSC_VIEWSIZEDEC:
            rv = process_record_vsc(keycode, record);
            break;

        case M_GDB_PLAY:
        case M_GDB_PAUSE:
        case M_GDB_STEPOVER:
        case M_GDB_STEPIN:
        case M_GDB_STEPOUT:
        case M_GDB_RESTART:
        case M_GDB_STOP:
            rv = process_record_gdb(keycode, record);
            break;

        case M_OBS_BRB:
        case M_OBS_GAME:
        case M_OBS_JSTCHT:
        case M_OBS_DSKT_MUTE:
        case M_OBS_DSKT_UNMUTE:
        case M_OBS_VOICE_MUTE:
        case M_OBS_VOICE_UNMUTE:
        case M_OBS_MOOSIC_MUTE:
        case M_OBS_MOOSIC_UNMUTE:
            rv = process_record_obs(keycode, record);
            break;
    }
    return rv;
};

#ifdef ENCODER_ENABLE
__attribute__((weak)) bool encoder_update_user(uint8_t index, bool clockwise) {
    const layer_state_t curr_layer = get_highest_layer(layer_state);
    if (index == 1) { /* Bottom encoder */
        if(curr_layer == 2 || curr_layer == 3) {
            if (clockwise) {
                moults31_tap_custom_code(M_VSC_FILENXT);
            } else {
                moults31_tap_custom_code(M_VSC_FILEPRV);
            }
        }
        else {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }
    if (index == 0) { /* Top encoder */
        if(curr_layer == 2 || curr_layer == 3) {
            if (clockwise) {
                moults31_tap_custom_code(M_VSC_VIEWSIZEINC);
            } else {
                moults31_tap_custom_code(M_VSC_VIEWSIZEDEC);
            }
        }
        else {
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        }
    }
    return false;
}
#endif
