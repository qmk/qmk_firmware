/* Copyright 2022 @ Keychron (https://www.keychron.com)
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
#include "lemokey_common.h"

#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#    include "lemokey_common.h"
#endif

#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#endif

static uint8_t mac_keycode[4] = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};

static key_combination_t key_comb_list[3] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}},
    {2, {KC_LWIN, KC_L}},
};

bool process_record_lemokey_common(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TASK_VIEW:
        case KC_FILE_EXPLORER:
        case KC_LOCK_SCREEN:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false; // Skip all further processing of this key
        case KC_MCTRL:
            if (record->event.pressed) {
                register_code(KC_MISSION_CONTROL);
            } else {
                unregister_code(KC_MISSION_CONTROL);
            }
            return false; // Skip all further processing of this key
        case KC_LANCH:
            if (record->event.pressed) {
                register_code(KC_LAUNCHPAD);
            } else {
                unregister_code(KC_LAUNCHPAD);
            }
            return false; // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}

void lemokey_common_task(void) {}

#ifdef ENCODER_ENABLE
static void encoder0_pad_cb(void *param) {
    (void)param;
    encoder_inerrupt_read(0);
}

void encoder_cb_init(void) {
    pin_t encoders_pad_a[] = ENCODERS_PAD_A;
    pin_t encoders_pad_b[] = ENCODERS_PAD_B;
    palEnableLineEvent(encoders_pad_a[0], PAL_EVENT_MODE_BOTH_EDGES);
    palEnableLineEvent(encoders_pad_b[0], PAL_EVENT_MODE_BOTH_EDGES);
    palSetLineCallback(encoders_pad_a[0], encoder0_pad_cb, NULL);
    palSetLineCallback(encoders_pad_b[0], encoder0_pad_cb, NULL);
}
#endif

//__attribute__((weak)) bool raw_hid_receive_lemokey(uint8_t *data, uint8_t length) { return true; }

bool via_command_kb(uint8_t *data, uint8_t length) {
    // if (!raw_hid_receive_lemokey(data, length))
    //     return false;

    switch (data[0]) {
#ifdef LK_WIRELESS_ENABLE
        case 0xAA:
            lkbt51_dfu_rx(data, length);
            break;
#endif
#ifdef FACTORY_TEST_ENABLE
        case 0xAB:
            factory_test_rx(data, length);
            break;
#endif
        default:
            return false;
    }

    return true;
}

#if !defined(VIA_ENABLE)
void raw_hid_receive(uint8_t *data, uint8_t length) {
    switch (data[0]) {
        case RAW_HID_CMD:
            via_command_kb(data, length);
            break;
    }
}
#endif
