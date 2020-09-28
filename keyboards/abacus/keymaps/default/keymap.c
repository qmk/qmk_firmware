/* Copyright 2020 nickolaij
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

// wait DELAY ms before unregistering media keys
#define MEDIA_KEY_DELAY 10

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _UPPER,
    _LOWER
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    NICKURL = SAFE_RANGE,
    ALTTAB
};

enum unicode_names {
    LOVEEYES,
    THINK,
    UPSIDEDOWN,
    NOMOUTH,
    PARTY,
    HEART,
    EGGPLANT,
    PEACH,
    EMOJI100,
    EMOJIB
};

const uint32_t PROGMEM unicode_map[] = {
    [LOVEEYES]  = 0x1f60d,
    [THINK] = 0x1f914,
    [UPSIDEDOWN] = 0x1f643,
    [NOMOUTH] = 0x1f636,
    [PARTY]  = 0x1f973,
    [HEART] = 0x1f495,
    [EMOJI100] = 0x1f4af,
    [PEACH] = 0x1f351,
    [EGGPLANT] = 0x1f346,
    [EMOJIB] = 0x1f171
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESCAPE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPACE,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_BSLASH,
        KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_UP, KC_DELETE,
        KC_LCTRL, KC_LGUI, MO(_UPPER), KC_SPACE, KC_ENTER, MO(_LOWER), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_UPPER] = LAYOUT(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______,
        ALTTAB, _______, _______, _______, _______, _______, _______, _______, KC_LBRACKET, KC_RBRACKET, KC_QUOTE, KC_SLASH,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MINUS, KC_EQUAL, _______, _______,
        KC_LALT, _______, _______, _______, _______, _______, KC_HOME, _______, KC_END
    ),
    [_LOWER] = LAYOUT(
        NICKURL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______,
        _______, KC_F11, KC_F12, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW, RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_MODE_KNIGHT, RGB_MODE_GRADIENT, XXXXXXX, RGB_TOG, 
        _______, X(LOVEEYES), X(THINK), X(UPSIDEDOWN), X(NOMOUTH), X(PARTY), X(PEACH), X(HEART), X(EGGPLANT), X(EMOJI100), X(EMOJIB), RGB_HUI,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______
    )
 
 
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NICKURL:
            if (record->event.pressed) {
                SEND_STRING("https://www.github.com/nickolaij");
            } else {
                tap_code(KC_ENTER);
            }
            return true;
            break;
        
        case ALTTAB:
            if (record->event.pressed) {
                tap_code16(A(KC_TAB));
            }
            return true;
            break;

        default:
            return true;

    }
}


void dip_switch_update_user(uint8_t index, bool active) { 
    switch (index) {
        case 0:
            if(active) {
                switch(get_highest_layer(layer_state)) {
                case _BASE:
                    tap_code16(LCTL(KC_F));
                    break;
                case _UPPER:
                    tap_code(KC_MUTE);
                    break;
                case _LOWER:
                    tap_code(KC_MEDIA_PLAY_PAUSE);
                    break;
                }
        }
    }
}


void matrix_init_user(void) {
    set_unicode_input_mode(UC_WINC);
}

void encoder_update_user(uint8_t index, bool clockwise) {

    switch(get_highest_layer(layer_state)) {
        case _BASE:
            clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
            break;
        case _UPPER:
            clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            break;
        case _LOWER:
            clockwise ? tap_code(KC_MEDIA_NEXT_TRACK) : tap_code(KC_MEDIA_PREV_TRACK);
            break;
        }
}
