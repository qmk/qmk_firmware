/* Copyright 2020 mingwahlu
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LAYER
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    M_NUTS,
    M_RESET,
    M_CLOSETAB,
    M_REOPENTAB,
    M_NEWTAB,
    M_SWITCHTABS,
    M_ALTTAB,
    M_ALTF4,
    M_MACROMACRO,
    M_UMARUEAT,
    M_UMARUMAD,
    M_UMARUHAPPY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Base */
    [_BASE] = LAYOUT(
        M_ALTF4, KC_F5, KC_A, MO(_LAYER), \
        M_CLOSETAB, M_NEWTAB, M_REOPENTAB, M_SWITCHTABS  \
    ),

    [_LAYER] = LAYOUT(
        M_RESET, KC_NO, KC_NO, KC_NO \
        M_UMARUEAT, M_UMARUMAD, M_UMARUHAPPY, KC_NO\
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
        case M_NUTS:
            if (record->event.pressed) {
                SEND_STRING("deeznuts");
                tap_code(KC_ENTER);
            } else {
            }
            break;
        case M_RESET:
            if (record->event.pressed) {
                reset_keyboard();
            } else {
            }
            break;
        case M_CLOSETAB:
            if(record->event.pressed) {
                SEND_STRING(SS_LCTL("w"));
            } else {

            }
            break;
        case M_REOPENTAB:
            if(record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT("t")));
            } else {

            }
            break;
        case M_NEWTAB:
            if(record->event.pressed) {
                SEND_STRING(SS_LCTL("t"));
            } else {

            }
            break;
        case M_SWITCHTABS:
            if(record->event.pressed) {
                register_code(KC_LCTL);  
                tap_code(KC_TAB);
            } else {
               unregister_code(KC_LCTL); 
            }
            break;
        case M_ALTTAB:
            if(record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_TAB);
            } else {
                unregister_code(KC_LALT);
            }
            break;
        case M_ALTF4:
            if(record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_F4);
            } else {
               unregister_code(KC_LALT); 
            }
            break;
        case M_MACROMACRO:
            if(record->event.pressed) {
                SEND_STRING("https://imgur.com/NvKoahR");
                tap_code(KC_ENTER);
            } else {
            }
            break;
        case M_UMARUEAT:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/ramen-slurp-anime-umaru-cute-gif-16722331");
                tap_code(KC_ENTER);
            } else {
            }
            break;
        case M_UMARUMAD:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/anime-umaru-mad-cute-small-girl-gif-5169671");
                tap_code(KC_ENTER);
            } else {
            }
            break;   
        case M_UMARUHAPPY:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/umaru-gif-4927713");
                tap_code(KC_ENTER);
            } else {
            }
            break;               
    }
    return true;
}
