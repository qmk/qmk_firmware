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
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    M_NUTS,
    M_UMARUBM,
    M_UMARUEAT,
    M_UMARUMAD,
    M_UMARUHAPPY,
    M_UMARUSAD,
    M_UMARUGAME,
    M_UMARUSLEEP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        M_UMARUHAPPY, M_UMARUSAD, M_UMARUMAD, MO(_FN),
        M_UMARUEAT, M_UMARUGAME, M_UMARUBM, M_UMARUSLEEP
    ),
    [_FN] = LAYOUT(
        LALT(KC_F4), KC_F5, RESET, MO(_FN),
        LCTL(KC_W), C(S(KC_T)), LCTL(KC_T), LALT(KC_TAB)
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
                SEND_STRING("hello, mingwahlu!");
                tap_code(KC_ENTER);
            } else {
            }
            break;
        case M_UMARUBM:
            if(record->event.pressed) {
                SEND_STRING("https://imgur.com/NvKoahR" SS_TAP(X_ENTER));
            } else {
            }
            break;
        case M_UMARUEAT:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/ramen-slurp-anime-umaru-cute-gif-16722331" SS_TAP(X_ENTER));
            } else {
            }
            break;
        case M_UMARUMAD:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/anime-umaru-mad-cute-small-girl-gif-5169671" SS_TAP(X_ENTER));
            } else {
            }
            break;
        case M_UMARUHAPPY:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/umaru-gif-4927713" SS_TAP(X_ENTER));
            } else {
            }
            break;
        case M_UMARUSAD:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/umaru-crying-tears-gif-5497252" SS_TAP(X_ENTER));
            } else {
            }
            break;
        case M_UMARUGAME:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/mash-buttons-press-himouto-umaru-chan-anime-gif-17872461" SS_TAP(X_ENTER));
            } else {
            }
            break;
        case M_UMARUSLEEP:
            if(record->event.pressed) {
                SEND_STRING("https://tenor.com/view/umaru-himouto-sleeping-dreaming-gif-4769761" SS_TAP(X_ENTER));
            } else {
            }
            break;
    }
    return true;
}
