// Copyright 2023 Moritz Plattner (@ebastler), Alex Havermale (@haversnail)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "transactions.h"
#include <stdio.h>
#include "print.h"
#include "split_util.h"
#include "usbpd.h"

typedef struct _kb_state_t {
    usbpd_allowance_t allowance;
} kb_state_t;

kb_state_t kb_state;

const char* usbpd_str(usbpd_allowance_t allowance) {
    switch (allowance) {
        case USBPD_500MA:
            return "500mA";
        case USBPD_1500MA:
            return "1500mA";
        case USBPD_3000MA:
            return "3000mA";
        default:
            dprintf("Encountered unknown allowance enum value: %d\n", allowance);
            return "UNKNOWN";
    }
}

void kb_state_slave_handler(uint8_t m2s_size, const void* m2s_buffer, uint8_t s2m_size, void* s2m_buffer) {
    if (m2s_size == sizeof(kb_state_t)) {
        memcpy(&kb_state, m2s_buffer, sizeof(kb_state_t));
    } else {
        dprintf("Unexpected response in slave handler\n"); // TODO: add split debug logging
    }
}

void keyboard_pre_init_kb(void) {
    // Disable the PD peripheral in pre-init because its pins are being used in the matrix:
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // Register keyboard state transaction:
    transaction_register_rpc(RPC_ID_KB_STATE, kb_state_slave_handler);

    // Set default state values:
    kb_state.allowance = USBPD_500MA;

    // If the keyboard is master,
    if (is_keyboard_master()) {
        // Turn on power to the split half and to underglow LEDs:
        gpio_set_pin_output(PSW_PIN);
        gpio_write_pin_high(PSW_PIN);

        // Enable inputs used for current negotiation:
        gpio_set_pin_input_high(USBPD_1_PIN);
        gpio_set_pin_input_high(USBPD_2_PIN);

        // Not needed in this mode (always high-Z with pull-up on PCB if port controller is sink)
        gpio_set_pin_input_high(ID_PIN);
    } else {
        // Prepare output to enable power for USB output after negotiation:
        gpio_set_pin_output(PSW_PIN);

        // Switch the USB MUXes between hub and ports:
        gpio_set_pin_output(USBSW_PIN);
        gpio_write_pin_high(USBSW_PIN);

        // Enable outputs used for current negotiation and default to 500mA:
        gpio_set_pin_output(USBPD_1_PIN);
        gpio_write_pin_high(USBPD_1_PIN);
        gpio_set_pin_output(USBPD_2_PIN);
        gpio_write_pin_high(USBPD_2_PIN);

        // Use ID pin to check if client is detected (if low: USB source port powered):
        gpio_set_pin_input_high(ID_PIN);

        // Indicate that the hub is either self-powered or bus-powered based on whether the bus-power mode flag is enabled
        // (configurable for users who would rather always have their device connect, regardless of whether they meet the specs):
        gpio_set_pin_output(BUS_B_PIN);
        if (DISABLE_BUS_POWER_MODE == TRUE) {
            gpio_write_pin_high(BUS_B_PIN);
        } else {
            gpio_write_pin_low(BUS_B_PIN);
        }
    }
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    // Update any shared kb state to send to slave:
    static uint32_t last_usbpd_allowance_check_time = 0;
    if (timer_elapsed32(last_usbpd_allowance_check_time) > USBPD_ALLOWANCE_CHECK_INTERVAL) {
        // On master side: check USBPD_1_PIN and USBPD_2_PIN to determine current negotiated with host
        // (Can't use the usbpd_get_allowance() function, as this uses this uses the native CC PD interface
        // of the G series MCU, while we're using dedicated port controllers instead):
        if (is_keyboard_master()) {
            usbpd_allowance_t allowance;

            if (gpio_read_pin(USBPD_1_PIN)) {
                allowance = USBPD_500MA;
            } else if (gpio_read_pin(USBPD_2_PIN)) {
                allowance = USBPD_1500MA;
            } else {
                allowance = USBPD_3000MA;
            }

            if (kb_state.allowance != allowance) {
                printf("Host negotiated current: %s -> %s\n", usbpd_str(kb_state.allowance), usbpd_str(allowance));
                kb_state.allowance = allowance;
            }
        } else {
            // On peripheral side - If ID_PIN is low: USB client negotiated 5V successfully -> enable power routing
            // Check if PSW_PIN is not already high to avoid wasting time
            if (!gpio_read_pin(ID_PIN) && !gpio_read_pin(PSW_PIN)) {
                gpio_write_pin_high(PSW_PIN);
                dprintf("USB downstream device connected\n"); // TODO: add split debug logging
            } else if (gpio_read_pin(ID_PIN) && gpio_read_pin(PSW_PIN)) {
                gpio_write_pin_low(PSW_PIN);
                dprintf("USB downstream device disconnected\n"); // TODO: add split debug logging
            }
        };
        last_usbpd_allowance_check_time = timer_read32();
    };

    // Sync state from master to slave:
    if (is_keyboard_master() && is_transport_connected()) {
        bool              needs_sync = false;
        static uint32_t   last_kb_state_sync_time;
        static kb_state_t last_kb_state;

        // Check if the state values are different:
        if (memcmp(&kb_state, &last_kb_state, sizeof(kb_state_t))) {
            needs_sync = true;
            memcpy(&last_kb_state, &kb_state, sizeof(kb_state_t));
        }

        // Sync state every so often regardless:
        if (timer_elapsed32(last_kb_state_sync_time) > KB_STATE_SYNC_INTERVAL) {
            needs_sync = true;
        }

        if (needs_sync) {
            bool did_sync = transaction_rpc_send(RPC_ID_KB_STATE, sizeof(kb_state_t), &kb_state);
            if (did_sync) {
                dprintf("Synced to slave\n");
                last_kb_state_sync_time = timer_read32();
            } else {
                dprintf("Failed to sync state\n");
            }
        }
    }

    // Update the USBPD output pins on slave half whenever allowance has changed:
    if (!is_keyboard_master()) {
        static usbpd_allowance_t last_allowance;

        if (last_allowance != kb_state.allowance) {
            last_allowance = kb_state.allowance;

            printf("Setting USB-PD output to %s (%s-powered)\n", usbpd_str(kb_state.allowance), kb_state.allowance == USBPD_500MA ? "bus" : "self"); // TODO: add split debug logging

            switch (kb_state.allowance) {
                default:
                case USBPD_500MA:
                    // Set USBPD output to 500 mA:
                    gpio_write_pin_high(USBPD_1_PIN);
                    gpio_write_pin_high(USBPD_2_PIN);
                    if (DISABLE_BUS_POWER_MODE == TRUE) {
                        // Indicate hub is self-powered and devices can try to connect or fast charge:
                        gpio_write_pin_high(BUS_B_PIN);
                    } else {
                        // Indicate hub is bus-powered and devices should not try to connect or fast charge:
                        gpio_write_pin_low(BUS_B_PIN);
                    }
                    break;
                case USBPD_1500MA:
                    // Set USBPD output to 500 mA:
                    gpio_write_pin_high(USBPD_1_PIN);
                    gpio_write_pin_high(USBPD_2_PIN);
                    // Indicate hub is self-powered and devices can try to connect or fast charge:
                    gpio_write_pin_high(BUS_B_PIN);
                    break;
                case USBPD_3000MA:
                    // Set USBPD output to 1500 mA:
                    gpio_write_pin_low(USBPD_1_PIN);
                    gpio_write_pin_high(USBPD_2_PIN);
                    // Indicate hub is self-powered and devices can try to connect or fast charge:
                    gpio_write_pin_high(BUS_B_PIN);
                    break;
            }
        }
    }
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, INDICATOR_MAX_BRIGHTNESS, INDICATOR_MAX_BRIGHTNESS, INDICATOR_MAX_BRIGHTNESS);
    } else {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 0, 0, 0);
    }
    return true;
}
#endif
