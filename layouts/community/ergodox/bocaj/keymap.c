/*
Copyright 2020 Jacob Jerrell <jacob.jerrell@gmail.com> @JacobJerrell

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "bocaj.h"

/*
 * The `LAYOUT_ergodox_pretty_base` macro is a template to allow the use of
 * identical modifiers for the default layouts (eg QWERTY, Colemak, Dvorak,
 * etc), so that there is no need to set them up for each layout, and modify
 * all of them if I want to change them.  This helps to keep consistency and
 * ease of use. K## is a placeholder to pass through the individual keycodes
 */
#define LAYOUT_ergodox_bocaj(...)       WRAPPER_ergodox_bocaj(__VA_ARGS__)
#define LAYOUT_ergodox_bocaj_WIN(...)   WRAPPER_ergodox_bocaj_WIN(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WORKMAN] = LAYOUT_ergodox_bocaj(
        KC_ESC, ________________NUMBER_LEFT________________, KC_ARRW,     KC_MINS, ________________NUMBER_RIGHT_______________, KC_EQUAL,
        KC_DEL, _________________WORKMAN_L1________________, KC_LPRN,     KC_RPRN, _________________WORKMAN_R1________________, KC_BSLS,
       _______, _________________WORKMAN_L2________________,                       _________________WORKMAN_R2________________, KC_QUOT,
       KC_LSFT, _________________WORKMAN_L3________________, KC_LBRC,     KC_RBRC, _________________WORKMAN_R3________________, _______,
        MO_MOD, KC_PGUP, KC_HOME, KC_UP, KC_LEFT,                                          KC_RIGHT, KC_DOWN, KC_END, KC_PGDN, WORKMAN,
                                              KC_APP,KC_HOME, /* <- LHS/RHS -> */ KC_END,KC_ESC,
                                                     KC_PGUP, /* <- LHS/RHS -> */ KC_PGDN,
                                  KC_SPACE,KC_BSPACE,KC_LEAD, /* <- LHS/RHS -> */ KC_LOCK,KC_TAB,KC_ENTER
    ),

    [_WWORKMAN] = LAYOUT_ergodox_bocaj_WIN(
        KC_ESC, ________________NUMBER_LEFT________________, KC_ARRW,     KC_MINS, ________________NUMBER_RIGHT_______________, KC_EQUAL,
        KC_DEL, _________________WORKMAN_L1________________, KC_LPRN,     KC_RPRN, _________________WORKMAN_R1________________, KC_BSLS,
       _______, _________________WORKMAN_L2________________,                       _________________WORKMAN_R2________________, KC_QUOT,
       KC_LSFT, _________________WORKMAN_L3________________, KC_LBRC,     KC_RBRC, _________________WORKMAN_R3________________, _______,
        MO_MOD, KC_PGUP, KC_HOME, KC_UP, KC_LEFT,                                          KC_RIGHT, KC_DOWN, KC_END, KC_PGDN, WORKMAN,
                                              KC_APP,KC_HOME, /* <- LHS/RHS -> */ KC_END,KC_ESC,
                                                     KC_PGUP, /* <- LHS/RHS -> */ KC_PGDN,
                                  KC_SPACE,KC_BSPACE,KC_LEAD, /* <- LHS/RHS -> */ KC_LOCK,KC_TAB,KC_ENTER
    ),

    [_LOWER] = LAYOUT_ergodox_bocaj(
        KC_GRV, _______, _______, _______, _______,  _______, _______,     _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_UP,   _______,  _______, _______,     _______, _______, KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
       _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,                       _______, KC_4,    KC_5,    KC_6,    KC_ASTR, _______,
       _______, _______, _______, _______, _______,  _______, _______,     _______, _______, KC_1,    KC_2,    KC_3,    KC_PLUS, _______,
       _______, _______, _______, _______,  _______,                                         KC_0,    KC_DOT,  KC_COMM, KC_MINS, _______,
                                               KC_APP,KC_HOME, /* <- LHS/RHS -> */ KC_END,KC_ESC,
                                                      KC_PGUP, /* <- LHS/RHS -> */ KC_PGDN,
                                   KC_SPACE,KC_BSPACE,KC_LEAD, /* <- LHS/RHS -> */ KC_LOCK,KC_TAB,KC_ENTER
    ),

    [_RAISE] = LAYOUT_ergodox_bocaj(
        KC_TILD, _________________RAISE_L1__________________, _______,         _______, _________________RAISE_R1__________________, _______,
         KC_F11, _________________RAISE_L2__________________, _______,         _______, _________________RAISE_R2__________________, KC_F12,
        _______, _________________RAISE_L3__________________,                           _________________RAISE_R3__________________, _______,
        _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______,         _______, ___________________BLANK___________________, _______,
        ___________________BLANK___________________,                                             ___________________BLANK___________________,
                                                 KC_APP,KC_HOME, /* <- LHS/RHS -> */ KC_END,KC_ESC,
                                                        KC_PGUP, /* <- LHS/RHS -> */ KC_PGDN,
                                     KC_SPACE,KC_BSPACE,KC_LEAD, /* <- LHS/RHS -> */ KC_LOCK,KC_TAB,KC_ENTER
    ),

    [_ADJUST] = LAYOUT_ergodox_pretty(
        KC_MAKE, _______,  _______,     _______,   _______, _______, _______,       _______, _______, _______, _______, _______, _______, KC_RST,
        VRSN,    _______,  _______,     _______,   _______, _______, _______,       _______, _______, _______, _______, _______, _______, EEP_RST,
        _______, KC__MUTE, KC__VOLDOWN, KC__VOLUP, _______, KC_MNXT,                         _______, _______, _______, _______, _______, _______,
        _______, _______,  _______,     _______,   _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______,     _______,   _______,                                           _______, _______, _______, _______, _______,
                                              KC_APP,KC_HOME, /* <- LHS/RHS -> */ KC_END,KC_ESC,
                                                     KC_PGUP, /* <- LHS/RHS -> */ KC_PGDN,
                                  KC_SPACE,KC_BSPACE,KC_LEAD, /* <- LHS/RHS -> */ KC_LOCK,KC_TAB,KC_ENTER
    ),

    // Wrapping Mouse-Wheel Keys with `X_T()` style functions seems
    // to break the mouse button. So we can't use the wrapper here.
    [_MOD] = LAYOUT_ergodox_pretty(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_WH_D, _______, _______, _______,           _______, _______, _______, KC_MS_U, _______, _______, _______,
        _______, _______, KC_WH_L, KC_WH_U, KC_WH_R, _______,                             _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_ACL0,                                               KC_ACL1, KC_ACL2, _______, _______, _______,
                                                 _______,_______, /* <- LHS/RHS -> */ _______,_______,
                                                         _______, /* <- LHS/RHS -> */ _______,
                                         KC_BTN1,KC_BTN2,_______, /* <- LHS/RHS -> */ _______,KC_BTN3,KC_BTN4
    )

};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void matrix_init_keymap(void) {};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_keymap(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case _LOWER:
            ergodox_right_led_3_on();
            break;
        case _MOD:
            ergodox_right_led_2_on();
            break;
        case _RAISE:
            ergodox_right_led_1_on();
            break;
        case _ADJUST:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        default:
            break;
    }

    ergodox_right_led_1_set(25);
    ergodox_right_led_2_set(25);
    ergodox_right_led_3_set(25);

    return state;
};

void matrix_scan_keymap(void) {
    uint8_t modifiers = get_mods();
    uint8_t led_usb_state = host_keyboard_leds();
    uint8_t one_shot = get_oneshot_mods();
    uint8_t layer_is_workman = layer_state_is(_WORKMAN);

    if ((modifiers) && (layer_is_workman)) {
        if (modifiers & MODS_SHIFT_MASK || led_usb_state & (1<<USB_LED_CAPS_LOCK) || one_shot & MODS_SHIFT_MASK) {
            ergodox_right_led_1_on();
            ergodox_right_led_1_set( 25 );
        } else {
            ergodox_right_led_1_off();
        }
        if ((modifiers & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK) && (modifiers & MODS_GUI_MASK || one_shot & MODS_GUI_MASK)) {
            ergodox_right_led_2_on();
            ergodox_right_led_2_set( 50 );
        } else if ((modifiers & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK) || (modifiers & MODS_GUI_MASK || one_shot & MODS_GUI_MASK)) {
            ergodox_right_led_2_on();
            ergodox_right_led_2_set( 10 );
        } else {
            ergodox_right_led_2_off();
        }
        if (modifiers & MODS_ALT_MASK || one_shot & MODS_ALT_MASK) {
            ergodox_right_led_3_on();
            ergodox_right_led_3_set( 10 );
        } else {
            ergodox_right_led_3_off();
        }
    } else if (!(modifiers) && (layer_is_workman)) {
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();
    }
};
