/* Copyright 2021 JasonRen(biu)
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
#include "print.h"
#include "biu_ble_common.h"
#include "outputselect.h"


enum keyboard_keycodes {
    BLE_TOG = SAFE_RANGE, // ble
    USB_TOG,              // usb
    BAU_TOG,              // if ble then usb, if usb then ble
    BL_SW_0,              // ble id 0
    BL_SW_1,
    BL_SW_2,
    BL_SW_3,
    BLE_DEL,              // delete current ble bound
    BLE_CLR,              // delete all ble bound
    NEW_SAFE_RANGE  // Important!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
    BLE_TOG,  KC_1,    KC_2,       KC_3,    KC_4,    KC_5,    KC_6,
    USB_TOG,  KC_Q,    KC_W,       KC_E,    KC_R,    KC_T,    KC_Y,
    BL_SW_0, BLE_DEL,    KC_S,       KC_D,    KC_F,    KC_G,    KC_H,
    BL_SW_1, BLE_CLR,    KC_X,       KC_C,    KC_V,    MO(1),    KC_RSFT),
    LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_SPACE,KC_TRNS, KC_TRNS, KC_TRNS),
    LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_SPACE,KC_TRNS, KC_TRNS, KC_TRNS)
};


void keyboard_post_init_user(void) {
    // eeconfig_init();
    // uart_init(115200);
    debug_enable=true;
    //   debug_matrix=true;
    //   debug_keyboard=true;
    //     //debug_mouse=true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    }
    switch(keycode) {
        case BLE_TOG:
            if (record->event.pressed) {
                set_output(OUTPUT_BLUETOOTH);
            }
            return false;
        case USB_TOG:
            if (record->event.pressed) {
                set_output(OUTPUT_USB);
            }
            return false;
        case BAU_TOG:
            if (record->event.pressed) {
                if (where_to_send() == OUTPUT_USB) {
                    set_output(OUTPUT_BLUETOOTH);
                } else {
                    set_output(OUTPUT_USB);
                }
            }
            return false;
        case BL_SW_0:
        case BL_SW_1:
        case BL_SW_2:
        case BL_SW_3:
            if (record->event.pressed) {
                bluetooth_switch_one(keycode - BL_SW_0);
            }
            return false;
        case BLE_DEL:
            if (record->event.pressed) {
                bluetooth_unpair_current();
            }
            return false;
        case BLE_CLR:
            if (record->event.pressed) {
                bluetooth_unpair_all();
            }
            return false;
        default:
            return true;
    }
    return true;
}
