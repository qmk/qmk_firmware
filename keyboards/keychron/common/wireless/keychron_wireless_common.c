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
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#    include "wireless.h"
#    include "indicator.h"
#    include "transport.h"
#    include "battery.h"
#    include "bat_level_animation.h"
#    include "lpm.h"
#    include "keychron_wireless_common.h"
#    include "keychron_task.h"
#endif
#include "keychron_common.h"

bool firstDisconnect = true;

static uint32_t pairing_key_timer;
static uint8_t  host_idx = 0;

bool process_record_keychron_wireless(uint16_t keycode, keyrecord_t *record) {
    static uint8_t host_idx;

    switch (keycode) {
        case BT_HST1 ... BT_HST3:
            if (get_transport() == TRANSPORT_BLUETOOTH) {
                if (record->event.pressed) {
                    host_idx = keycode - BT_HST1 + 1;

                    pairing_key_timer = timer_read32();
                    wireless_connect_ex(host_idx, 0);
                } else {
                    host_idx          = 0;
                    pairing_key_timer = 0;
                }
            }
            break;
        case P2P4G:
            if (get_transport() == TRANSPORT_P2P4) {
                if (record->event.pressed) {
                    host_idx = P24G_INDEX;

                    pairing_key_timer = timer_read32();
                } else {
                    host_idx          = 0;
                    pairing_key_timer = 0;
                }
            }
            break;
#if (defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)) && defined(BAT_LEVEL_LED_LIST)
        case BAT_LVL:
            if ((get_transport() & TRANSPORT_WIRELESS) && !usb_power_connected()) {
                bat_level_animiation_start(battery_get_percentage());
            }
            break;
#endif

        default:
            break;
    }

    return true;
}

void lkbt51_param_init(void) {
    /* Set bluetooth device name */
    lkbt51_set_local_name(PRODUCT);
    wait_ms(3);
    // clang-format off
    /* Set bluetooth parameters */
    module_param_t param = {.event_mode             = 0x02,
                            .connected_idle_timeout = 7200,
                            .pairing_timeout        = 180,
                            .pairing_mode           = 0,
                            .reconnect_timeout      = 5,
                            .report_rate            = 90,
                            .vendor_id_source       = 1,
                            .verndor_id             = 0x3434, // Must be 0x3434
                            .product_id             = PRODUCT_ID};
    // clang-format on
    lkbt51_set_param(&param);
}

void wireless_enter_reset_kb(uint8_t reason) {
    lkbt51_param_init();
}

void wireless_enter_disconnected_kb(uint8_t host_idx, uint8_t reason) {
    /* CKBT51 bluetooth module boot time is slower, it enters disconnected after boot,
       so we place initialization here. */
    if (firstDisconnect && timer_read32() < 1000) {
        lkbt51_param_init();
        if (get_transport() == TRANSPORT_BLUETOOTH) wireless_connect();
        firstDisconnect = false;
    }
}

void keychron_wireless_common_task(void) {
    if (pairing_key_timer) {
        if (timer_elapsed32(pairing_key_timer) > 2000) {
            pairing_key_timer = 0;
            wireless_pairing_ex(host_idx, NULL);
        }
    }
}

void wireless_pre_task(void) {
    static uint8_t  mode = 0;
    static uint32_t time = 0;

    if (time == 0) {
        if ((readPin(BT_MODE_SELECT_PIN) << 1 | readPin(P2P4_MODE_SELECT_PIN)) != mode) {
            mode = readPin(BT_MODE_SELECT_PIN) << 1 | readPin(P2P4_MODE_SELECT_PIN);
            time = timer_read32();
        }
    }

    if ((time && timer_elapsed32(time) > 100) || get_transport() == TRANSPORT_NONE) {
        if ((readPin(BT_MODE_SELECT_PIN) << 1 | readPin(P2P4_MODE_SELECT_PIN)) == mode) {
            time = 0;

            switch (mode) {
                case 0x01:
                    set_transport(TRANSPORT_BLUETOOTH);
                    break;
                case 0x02:
                    set_transport(TRANSPORT_P2P4);
                    break;
                case 0x03:
                    set_transport(TRANSPORT_USB);
                    break;
                default:
                    break;
            }
        } else {
            mode = readPin(BT_MODE_SELECT_PIN) << 1 | readPin(P2P4_MODE_SELECT_PIN);
            time = timer_read32();
        }
    }
}
