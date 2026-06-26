/* Copyright 2023 Gondolindrim
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

/* ---------------------------------------------- DEALING WITH THE JOYSTICK
 * The Evolv revision Beta supports two rotary devices: an encoder and a joystick. The encoder is a simple EC11E and it is listed as encoder 0; its push is the matrix 0,15.
 * 
 * The joystick, however, is a little problematic. It has a construction particularity in that not only it has rotation and clicking, like the EC11E, but also directional joystic capabilities in the four cardinal directions, as in, it can also register four directions. The way that it works is, there are A,B and a common pin for the encoder rotation , with a PUSH and a COM pin. The encoder pins work pretty much like common encoders, as does the switch click: once you click it, PUSH and COM short-circuit, so the pushing mechanic can be easily integrated into a switch matrix and treated like a switch would. Such is the case: the joystick rotary is programmed as encoder 1, and its click is the matrix position 3,15.
 * 
 * The problem, however, lies in the directionals. For each directional, say N,S,W,E, there is a corresponding pin on the encoder; once one directional is hit its pin is shorted with PUSH and COM. But because the PUSH and COM already trigger a key; if this behavior is left unchecked, hitting a directional activates both the directional key and the PUSH key, which is not intended. This means that the directionals can be treated as four short-circuit keys and integrated into the matrix, but with the added hassle that every time one of them is registered, the encoder push is also registered.
 * 
 * The way this problem is dealt with is threefold.
 * - First, in hardware. The PUSH key is in 5,15, while NSWE are in 1,15 ; 2,15 ; 3,15 ; 4,15 . This means that the record event for the directionals happen before the event for the push;
 * - With this in mind, once a directional is hit, the flag is_joystick_push_blocked is set, flagging that the push of the joystick should be blocked;
 * - Finally, if the push is activated while the flag is true, this means that a directional was also hit. Therefore the processing of the push is halted — only the directional action goes through. The flag is set false only when the push is released. Note that this flag is inocuous when the PUSH is simply pressed, because when this is the case, a directional was not hit. So the PUSH is processed normally.
 */

#include "quantum.h"

bool is_joystick_push_blocked = false; // Keeps track of joystick push block

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    if (record->event.key.col == 15) {
        switch (record->event.key.row) {
            case 1:
            case 2:
            case 3:
            case 4:
                if (record->event.pressed) is_joystick_push_blocked = true;
                break;
            case 5:  // If joystick was pressed/unpressd, sets/unsets boolean
                if (!record->event.pressed) is_joystick_push_blocked = false;
                if (is_joystick_push_blocked) return false;
                break;
            default:
                return true;
                break;
        }
    }
    return true;
}

backlight_config_t backlight_config;

bool led_update_kb(led_t led_state) {
    eeconfig_read_backlight(&backlight_config);
    led_state.caps_lock ? backlight_set(backlight_config.level) : backlight_set(0);
    return true;
}
