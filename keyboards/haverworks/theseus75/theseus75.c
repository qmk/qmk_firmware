/* Copyright 2023 Moritz Plattner (@ebastler), Alex Havermale (@haversnail)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "transactions.h"
#include <stdio.h>
#include "print.h"

void keyboard_pre_init_kb(void) {
    // Disable the PD peripheral in pre-init because its pins are being used in the matrix:
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_pre_init_user();
    // Customise these values to desired behaviour:
    debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;
}

void keyboard_post_init_kb(void) {
    // If the keyboard is master
    if (is_keyboard_master()) {
        // Turn on power to the split half and to underglow LEDs
        gpio_set_pin_output(PSW_PIN);
        gpio_write_pin_high(PSW_PIN);

        // Enable inputs used for current negotiation
        gpio_set_pin_input_high(USBPD_1_PIN);
        gpio_set_pin_input_high(USBPD_2_PIN);

        // Not needed in this mode (always high-Z with pull-up on PCB if port controller is sink)
        gpio_set_pin_input_high(ID_PIN);
    } else {
        // Prepare output to enable power for USB output after negotiation
        gpio_set_pin_output(PSW_PIN);

        // Switch the USB MUXes between hub and ports
        gpio_set_pin_output(USBSW_PIN);
        gpio_write_pin_high(USBSW_PIN);

        // Enable outputs used for current negotiation
        gpio_set_pin_output(USBPD_1_PIN);
        gpio_set_pin_output(USBPD_2_PIN);

        // Test: 1.5A forced output
        gpio_write_pin_low(USBPD_1_PIN);
        gpio_write_pin_high(USBPD_2_PIN);

        // Use ID pin to check if client is detected (if low: USB source port powered)
        gpio_set_pin_input_high(ID_PIN);

        // Set BUS_B low to indicate a bus-powered hub (Test)
        gpio_set_pin_output(BUS_B_PIN);
        gpio_write_pin_high(BUS_B_PIN);
    }
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_post_init_user();
}

// Todo: Insert timer based delay to avoid spamming pin reads/writes, only set on pin change
void housekeeping_task_kb(void) {
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    housekeeping_task_user();

    static uint32_t usbcpd_timer = 0;
    if (timer_elapsed32(usbcpd_timer) > USBCPD_TIMESPAN) {
        // On master side: check USBPD_1_PIN and USBPD_2_PIN to determine current negotiated with host
        if (is_keyboard_master()) {
            bool    out1         = gpio_read_pin(USBPD_1_PIN);
            bool    out2         = gpio_read_pin(USBPD_2_PIN);
            uint8_t host_current = 0; // 0: 500 mA, 1: 1500 mA, 2:3000 mA

            if (out1 == 1) {
                host_current = 0;
                printf("Host negotiated current: 500 mA\n");
            } else if (out2 == 1) {
                host_current = 1;
                printf("Host negotiated current: 1500 mA\n");
            } else {
                host_current = 2;
                printf("Host negotiated current: 3000 mA\n");
            };
            printf("Host current variable: %d\n", host_current);
        } else {
            printf("Im slave, you shouldn't see this\n");
            // On peripheral side - If ID_PIN is low: USB client negotiated 5V successfully -> enable power routing
            // Check if PSW_PIN is not already high to avoid wasting time
            if (!gpio_read_pin(ID_PIN) && !gpio_read_pin(PSW_PIN)) {
                gpio_write_pin_high(PSW_PIN);
                printf("USB downstream device detected\n");
            } else if (gpio_read_pin(ID_PIN) && gpio_read_pin(PSW_PIN)) {
                gpio_write_pin_low(PSW_PIN);
                printf("USB downstream device disconnected\n");
            }
        };
        usbcpd_timer = timer_read32();
    };
}
