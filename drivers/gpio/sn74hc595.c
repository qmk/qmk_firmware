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

#include "sn74hc595.h"
#include "spi_master.h"
#include "debug.h"
#include "timer.h"

uint32_t timer_now;

spi_status_t res;
uint8_t      pinStates[SN74HC595_LENGTH];
typedef enum { Low = 0, High = 1 } pinState;

/* get length */
uint8_t sn74hc595_length(void) {
    return SN74HC595_LENGTH;
}
/*
    init first
*/
void sn74hc595_init(void) {
    spi_init();
}

spi_status_t sn74hc595_spi_transmit(void) {
    res = spi_start(SN74HC595_SPI_SLAVE_SELECT_PIN, SN74HC595_SPI_LSBFIRST, SN74HC595_SPI_MODE, SN74HC595_SPI_CLOCK_DIVISOR);
    if (res < SPI_STATUS_SUCCESS) {
        dprintf("sn74hc595 spi failed to start, msg: %x\n", res);
        return res;
    }

    res = spi_transmit(pinStates, SN74HC595_LENGTH);
    if (res != SPI_STATUS_SUCCESS) {
        dprintf("sn7chc595 spi cant transmit, msg: %x \n", res);
        return res;
    }

    spi_stop();
    return res;
}

/*
    set pin number on sn74hc595
*/
spi_status_t sn74hc595_setPin(uint8_t pin, bool set) {
    // set pin state like binary 1000010
    for (int current = (SN74HC595_LENGTH - 1); current >= 0; current--) {
        if (pin < 8) {
            int mask           = 1 << pin;
            pinStates[current] = ((pinStates[current] & ~mask) | set << pin);
        }
        pin -= 8;
    }

    // pinstates debug
    if (timer_elapsed32(timer_now) >= 1000) {
        dprintf("PinStates HEX: ");
        for (uint8_t x = 0; x < SN74HC595_LENGTH; x++) {
            dprintf("PS %i:[0x%02x]|", x, pinStates[x]);
        }
        dprintf("PinStates BIN: ");
        for (uint8_t x = 0; x < SN74HC595_LENGTH; x++) {
            dprintf("|");
            debug_bin_reverse8(pinStates[x]);
        }
        dprintf("\n");
        timer_now = timer_read32();
    }
    // then send it using spi
    return sn74hc595_spi_transmit();
}

/*
    for easy use
*/
spi_status_t sn74hc595_setPinHigh(uint8_t pin) {
    return sn74hc595_setPin(pin, High);
}

spi_status_t sn74hc595_setPinLow(uint8_t pin) {
    return sn74hc595_setPin(pin, Low);
}

/*
    make a shortcut, slightly faster then set pin one by one
*/

spi_status_t sn74hc595_set_raw(uint8_t* raw_value) {
    res = spi_start(SN74HC595_SPI_SLAVE_SELECT_PIN, SN74HC595_SPI_LSBFIRST, SN74HC595_SPI_MODE, SN74HC595_SPI_CLOCK_DIVISOR);
    if (res < SPI_STATUS_SUCCESS) {
        dprintf("sn74hc595 spi raw failed to start, msg: %x\n", res);
        return res;
    }

    res = spi_transmit(raw_value, SN74HC595_LENGTH);
    if (res != SPI_STATUS_SUCCESS) {
        dprintf("sn7chc595 spi raw cant transmit, msg: %x\n", res);
        return res;
    }

    spi_stop();
    return SPI_STATUS_SUCCESS;
}

spi_status_t sn74hc595_AllPin_High(void) {
    for (uint8_t current = 0; current < SN74HC595_LENGTH; current++) {
        pinStates[current] = 0xFF;
    }

    return sn74hc595_spi_transmit();
}

spi_status_t sn74hc595_AllPin_Low(void) {
    for (uint8_t current = 0; current < SN74HC595_LENGTH; current++) {
        pinStates[current] = 0x0;
    }
    return sn74hc595_spi_transmit();
}
