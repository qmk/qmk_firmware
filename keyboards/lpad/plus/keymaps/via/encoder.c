/* Copyright 2021 bululau
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


//Setting up what encoder rotation does. If your encoder can be pressed as a button, that function can be set in Via.

// #ifdef ENCODER_ENABLE

// bool encoder_update_user(uint8_t index, bool clockwise) {

//         if (index == 0) {
//             if (clockwise) {
//                 // tap_code(KC_PGDN);
//                 tap_code16(dynamic_keymap_get_keycode(biton32(layer_state), 0, 0));
//             } else {
//                 // tap_code(KC_PGUP);
//                 tap_code16(dynamic_keymap_get_keycode(biton32(layer_state), 0, 1));
//             }
//         } else if (index == 1) {
//             if (clockwise) {
//                 // tap_code(KC_LEFT);
//                 tap_code16(dynamic_keymap_get_keycode(biton32(layer_state), 4, 3));
//             } else {
//                 // tap_code(KC_RIGHT);
//                 tap_code16(dynamic_keymap_get_keycode(biton32(layer_state), 4, 4));
//             }
//         } else if (index == 2) {
//             if (clockwise) {
//                 // tap_code(KC_VOLU);
//                 tap_code16(dynamic_keymap_get_keycode(biton32(layer_state), 3, 4));
//             } else {
//                 // tap_code(KC_VOLD);
//                 tap_code16(dynamic_keymap_get_keycode(biton32(layer_state), 3, 5));
//             }
//         }

//     return true;
// }

// #endif



#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        if (clockwise) {
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 0, 1);
            if (keycode >= MACRO00 && keycode <= MACRO15) {
                dynamic_keymap_macro_send(keycode - MACRO00);
            } else {
                register_code16(keycode);
                wait_ms(10);
                unregister_code16(keycode);
            }
        } else {
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 0, 0);
            if (keycode >= MACRO00 && keycode <= MACRO15) {
                dynamic_keymap_macro_send(keycode - MACRO00);
            } else {
                register_code16(keycode);
                wait_ms(10);
                unregister_code16(keycode);
            }
        }
    }else if (index == 1) {
            if (clockwise) {
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4, 4);
            if (keycode >= MACRO00 && keycode <= MACRO15) {
                dynamic_keymap_macro_send(keycode - MACRO00);
            } else {
                register_code16(keycode);
                wait_ms(10);
                unregister_code16(keycode);
            }
        } else {
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4, 3);
            if (keycode >= MACRO00 && keycode <= MACRO15) {
                dynamic_keymap_macro_send(keycode - MACRO00);
            } else {
                register_code16(keycode);
                wait_ms(10);
                unregister_code16(keycode);
            }
        }
        } else if (index == 2) {
            if (clockwise) {
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 3, 5);
            if (keycode >= MACRO00 && keycode <= MACRO15) {
                dynamic_keymap_macro_send(keycode - MACRO00);
            } else {
                register_code16(keycode);
                wait_ms(10);
                unregister_code16(keycode);
            }
        } else {
            uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 3, 4);
            if (keycode >= MACRO00 && keycode <= MACRO15) {
                dynamic_keymap_macro_send(keycode - MACRO00);
            } else {
                register_code16(keycode);
                wait_ms(10);
                unregister_code16(keycode);
            }
        }
    }
        return false;
    }
    #endif
