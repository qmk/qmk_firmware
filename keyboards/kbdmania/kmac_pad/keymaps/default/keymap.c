/*
Copyright 2021 talsu <talsu84@gmail.com>

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

#include QMK_KEYBOARD_H

enum kmac_pad_keycodes {
    MD_BOOT = SAFE_RANGE,
    MCR1,
    MCR2,
    MCR3,
    MCR4,
    MCR5,
    MCR6,
    MCR7,
    MCR8,
    MCR9,
    MCR10,
    MCR11,
    MCR12
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
                               TG(1),
    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_P4,   KC_P5,   KC_P6,
    KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_P0,            KC_PDOT          ),
    [1] = LAYOUT( /* FN  */
                               KC_TRNS,
    MCR1,    MCR2,    MCR3,    KC_TRNS,
    MCR4,    MCR5,    MCR6,    KC_TRNS,
    MCR7,    MCR8,    MCR9,
    MCR10,   MCR11,   MCR12,   KC_TRNS,
    KC_TRNS,          MD_BOOT          )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case MD_BOOT:
        {
            static uint32_t key_timer;
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 2000) {
                    reset_keyboard();
                }
            }
            return false;
        }
        case MCR1:
            if (record->event.pressed) {
                SEND_STRING("Macro 1");
            }
            return false;
        case MCR2:
            if (record->event.pressed) {
                SEND_STRING("Macro 2");
            }
            return false;
        case MCR3:
            if (record->event.pressed) {
                SEND_STRING("Macro 3");
            }
            return false;
        case MCR4:
            if (record->event.pressed) {
                SEND_STRING("Macro 4");
            }
            return false;
        case MCR5:
            if (record->event.pressed) {
                SEND_STRING("Macro 5");
            }
            return false;
        case MCR6:
            if (record->event.pressed) {
                SEND_STRING("Macro 6");
            }
            return false;
        case MCR7:
            if (record->event.pressed) {
                SEND_STRING("Macro 7");
            }
            return false;
        case MCR8:
            if (record->event.pressed) {
                SEND_STRING("Macro 8");
            }
            return false;
        case MCR9:
            if (record->event.pressed) {
                SEND_STRING("Macro 9");
            }
            return false;
        case MCR10:
            if (record->event.pressed) {
                SEND_STRING("Macro 10");
            }
            return false;
        case MCR11:
            if (record->event.pressed) {
                SEND_STRING("Macro 12");
            }
            return false;
        case MCR12:
            if (record->event.pressed) {
                SEND_STRING("Macro 12");
            }
            return false;
        default:
            return true;
    }

}

bool led_update_user(led_t led_state) {
    gpio_write_pin(B1, led_state.num_lock);
    return false;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(B3, !IS_LAYER_ON_STATE(state, 0));
    return state;
}
