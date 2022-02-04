/* Copyright 2022
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

#include "sn74x237.h"
#include "gpio.h"

#define ADDRESS_PIN_COUNT 3

#ifndef SN74X237_ADDRESS_PINS
#    error sn74x237: no address pins defined!
#endif

static const pin_t address_pins[ADDRESS_PIN_COUNT] = SN74X237_ADDRESS_PINS;

void sn74x237_init(void) {
    for (int i = 0; i < ADDRESS_PIN_COUNT; i++) {
        setPinOutput(address_pins[i]);
        writePinLow(address_pins[i]);
    }

#if defined(SN74X237_LE_PIN)
    setPinOutput(SN74X237_LE_PIN);
    writePinHigh(SN74X237_LE_PIN);
#endif

#if defined(SN74X237_E1_PIN)
    setPinOutput(SN74X237_E1_PIN);
    writePinHigh(SN74X237_E1_PIN);
#endif
#if defined(SN74X237_E2_PIN)
    setPinOutput(SN74X237_E2_PIN);
    writePinLow(SN74X237_E2_PIN);
#endif
}

void sn74x237_set_enabled(bool enabled) {
#if defined(SN74X237_E1_PIN)
    writePin(SN74X237_E1_PIN, !enabled);
#endif
#if defined(SN74X237_E2_PIN)
    writePin(SN74X237_E2_PIN, enabled);
#endif
}

void sn74x237_latch(void) {
#if defined(SN74X237_LE_PIN)
    writePinLow(SN74X237_LE_PIN);
    writePinHigh(SN74X237_LE_PIN);
#endif
}

void sn74x237_unlatch(void) {
#if defined(SN74X237_LE_PIN)
    writePinLow(SN74X237_LE_PIN);
#endif
}

void sn74x237_set_addr(uint8_t address) {
    for (int i = 0; i < ADDRESS_PIN_COUNT; i++) {
        writePin(address_pins[i], address & (1 << i));
    }
}
