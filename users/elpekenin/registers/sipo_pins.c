// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "sipo_pins.h"
#include "custom_spi_master.h"

uint8_t sipo_pin_state[_SIPO_BYTES] = {0};
bool sipo_state_changed = true;

void set_sipo_pin(uint8_t  position, bool state) {
    // this change makes position 0 to be the closest to the MCU, instead of being the 1st bit of the last byte
    uint8_t byte_offset = _SIPO_BYTES - 1 - (position / 8);
    uint8_t bit_offset  = position % 8;

    // Check if pin already had that state
    uint8_t curr_value = (sipo_pin_state[byte_offset] >> bit_offset) & 1;
    if (curr_value == state) {
        sipo_dprintf("set_sipo_pin: no changes on the desired bit, quitting\n");
        return;
    }

    sipo_state_changed = true;

    if (state)
        // add data starting on the least significant bit
        sipo_pin_state[byte_offset] |=  (1 << bit_offset);
    else
        sipo_pin_state[byte_offset] &= ~(1 << bit_offset);
}

void send_sipo_state() {
    if (!sipo_state_changed) {
        sipo_dprintf("send_sipo_state: no changes on the desired output, quitting\n");
        return;
    }

    sipo_state_changed = false;

    custom_spi_init(REGISTERS_SPI_DRIVER_ID);

    if(!custom_spi_start(SIPO_CS_PIN, false, REGISTERS_SPI_MODE, REGISTERS_SPI_DIV, REGISTERS_SPI_DRIVER_ID)) {
        sipo_dprintf("send_sipo_state: couldn't start SPI\n");
        return;
    }

    writePinLow(SIPO_CS_PIN);
    custom_spi_transmit(sipo_pin_state, _SIPO_BYTES, REGISTERS_SPI_DRIVER_ID);
    writePinHigh(SIPO_CS_PIN);

    custom_spi_stop(REGISTERS_SPI_DRIVER_ID);

    sipo_print_status();
}
