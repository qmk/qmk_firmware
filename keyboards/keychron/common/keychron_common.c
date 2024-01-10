/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"
#include "raw_hid.h"
#include "version.h"

#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#    include "keychron_common.h"
#endif

#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#endif

bool     is_siri_active = false;
uint32_t siri_timer     = 0;

static uint8_t mac_keycode[4] = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};

static key_combination_t key_comb_list[4] = {{2, {KC_LWIN, KC_TAB}}, {2, {KC_LWIN, KC_E}}, {3, {KC_LSFT, KC_LCMD, KC_4}}, {2, {KC_LWIN, KC_C}}};

bool process_record_keychron_common(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MCTRL:
            if (record->event.pressed) {
                register_code(KC_MISSION_CONTROL);
            } else {
                unregister_code(KC_MISSION_CONTROL);
            }
            return false; // Skip all further processing of this key
        case KC_LNPAD:
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
        case KC_SIRI:
            if (record->event.pressed) {
                if (!is_siri_active) {
                    is_siri_active = true;
                    register_code(KC_LCMD);
                    register_code(KC_SPACE);
                }
                siri_timer = timer_read32();
            } else {
                // Do something else when release
            }
            return false; // Skip all further processing of this key
        case KC_TASK:
        case KC_FILE:
        case KC_SNAP:
        case KC_CTANA:
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
        default:
            return true; // Process all other keycodes normally
    }
}

void keychron_common_task(void) {
    if (is_siri_active && timer_elapsed32(siri_timer) > 500) {
        unregister_code(KC_LCMD);
        unregister_code(KC_SPACE);
        is_siri_active = false;
        siri_timer     = 0;
    }
}

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

//__attribute__((weak)) bool raw_hid_receive_keychron(uint8_t *data, uint8_t length) { return true; }
#define PROTOCOL_VERSION 0x02

enum { kc_get_protocol_version = 0xA0, kc_get_firmware_version = 0xA1, kc_get_support_feature = 0xA2, kc_get_default_layer = 0xA3 };

enum {
    FEATURE_DEFAULT_LAYER = 0x01 << 0,
    FEATURE_BLUETOOTH     = 0x01 << 1,
    FEATURE_P2P4G         = 0x01 << 2,
    FEATURE_ANALOG_MATRIX = 0x01 << 3,
};

void get_support_feature(uint8_t *data) {
    data[1] = FEATURE_DEFAULT_LAYER
#ifdef KC_BLUETOOTH_ENABLE
              | FEATURE_BLUETOOTH
#endif
#ifdef LK_WIRELESS_ENABLE
              | FEATURE_BLUETOOTH | FEATURE_P2P4G
#endif
#ifdef ANANLOG_MATRIX
              | FEATURE_ANALOG_MATRIX
#endif
        ;
}

bool via_command_kb(uint8_t *data, uint8_t length) {
    // if (!raw_hid_receive_keychron(data, length))
    //     return false;
    switch (data[0]) {
        case kc_get_protocol_version:
            data[1] = PROTOCOL_VERSION;
            raw_hid_send(data, length);
            break;

        case kc_get_firmware_version: {
            uint8_t i = 1;
            data[i++] = 'v';
            if ((DEVICE_VER & 0xF000) != 0) itoa((DEVICE_VER >> 12), (char *)&data[i++], 16);
            itoa((DEVICE_VER >> 8) & 0xF, (char *)&data[i++], 16);
            data[i++] = '.';
            itoa((DEVICE_VER >> 4) & 0xF, (char *)&data[i++], 16);
            data[i++] = '.';
            itoa((DEVICE_VER >> 4) & 0xF, (char *)&data[i++], 16);
            data[i++] = ' ';
            memcpy(&data[i], QMK_BUILDDATE, sizeof(QMK_BUILDDATE));
            i += sizeof(QMK_BUILDDATE);
            raw_hid_send(data, length);
        } break;

        case kc_get_support_feature:
            get_support_feature(&data[1]);
            raw_hid_send(data, length);
            break;

        case kc_get_default_layer:
            data[1] = get_highest_layer(default_layer_state);
            raw_hid_send(data, length);
            break;

#ifdef ANANLOG_MATRIX
        case 0xA9:
            analog_matrix_rx(data, length);
            break;
#endif
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
