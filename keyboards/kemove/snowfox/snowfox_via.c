// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

// The keyboard's own page in VIA: power, Bluetooth and reset.

#include <string.h>
#include "snowfox.h"
#include "snowfox_ble.h"
#include "snowfox_power.h"
#include "via.h"

#ifdef VIA_ENABLE

// Value ids on VIA's custom channel. They must match the VIA definition.
enum snowfox_via_value {
    VIA_SLEEP = 1,
    VIA_BATTERY,
    VIA_BLE_STATUS,
    VIA_BLE_CONNECT,
    VIA_BLE_PAIR,
    VIA_BLE_DISCONNECT,
    VIA_FACTORY_RESET,
    VIA_BOOTLOADER,
    VIA_PROFILE,
    VIA_SWITCH_MODE,
    VIA_PROFILE_RESET,
};

static const char *const ble_state_names[] = {"off", "ready", "pairing", "connecting", "connected"};

// Appends text to out, keeping room for the terminator. Returns the new end.
static char *append(char *out, const char *end, const char *text) {
    while (*text && out < end - 1) {
        *out++ = *text++;
    }
    *out = '\0';
    return out;
}

static char *append_number(char *out, const char *end, uint8_t value) {
    char digits[4] = {0};
    char *d        = &digits[3];
    do {
        *--d = '0' + value % 10;
        value /= 10;
    } while (value);
    return append(out, end, d);
}

static void get_value(uint8_t *data, uint8_t length) {
    char       *text = (char *)&data[1];
    const char *end  = text + (length - 3);

    switch (data[0]) {
        case VIA_SLEEP:
            data[1] = snowfox_sleep_setting();
            break;
        case VIA_PROFILE:
            data[1] = snowfox_profile();
            break;
        case VIA_SWITCH_MODE:
            data[1] = snowfox_switch_mode();
            break;
        case VIA_BATTERY:
            append(append_number(text, end, snowfox_battery_percent()), end, "%");
            break;
        case VIA_BLE_STATUS: {
            const ble_handle_t *ble   = snowfox_ble_handle();
            uint8_t             state = ble->state < ARRAY_SIZE(ble_state_names) ? ble->state : 0;
            char *out = append(text, end, "Host ");
            out       = append_number(out, end, ble->keyboard + 1);
            out       = append(out, end, ", ");
            append(out, end, ble_state_names[state]);
            break;
        }
    }
}

static void set_value(uint8_t *data) {
    switch (data[0]) {
        case VIA_SLEEP:
            snowfox_set_sleep_setting(data[1]);
            break;
        case VIA_PROFILE:
            snowfox_profile_select(data[1]);
            break;
        case VIA_SWITCH_MODE:
            snowfox_set_switch_mode(data[1]);
            break;
        case VIA_PROFILE_RESET:
            snowfox_profile_reset();
            break;
        case VIA_BLE_CONNECT:
        case VIA_BLE_PAIR:
            if (data[1] >= 1 && data[1] <= 3) {
                snowfox_ble_select(data[1] - 1, data[0] == VIA_BLE_PAIR);
            }
            break;
        case VIA_BLE_DISCONNECT:
            ble_cmdq->put(DROP_CONN);
            break;
        case VIA_FACTORY_RESET:
            snowfox_factory_reset();
            break;
        case VIA_BOOTLOADER:
            reset_keyboard();
            break;
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [command_id, channel_id, value_id, value_data...]
    if (data[1] != id_custom_channel) {
        data[0] = id_unhandled;
        return;
    }
    switch (data[0]) {
        case id_custom_get_value:
            get_value(&data[2], length);
            break;
        case id_custom_set_value:
            set_value(&data[2]);
            break;
        case id_custom_save:
            // Settings are saved when they are set.
            break;
        default:
            data[0] = id_unhandled;
            break;
    }
}

#endif // VIA_ENABLE
