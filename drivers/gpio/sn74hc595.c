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

#ifdef CONSOLE_ENABLE
uint32_t timer_now;
#endif

// uint8_t *data_buffer;
uint8_t pinStates[SN74HC595_LENGTH];
typedef enum { Low = 0, High = 1 } state;

/* get length */
uint8_t sn74hc595_length(void) {
    return SN74HC595_LENGTH;
}
/*
    init first
*/
void sn74hc595_init(void) {
    setPinOutputPushPull(SN74HC595_SPI_SLAVE_SELECT_PIN);
    return spi_init();
}

/*
    set pin number on sn74hc595
*/
void sn74hc595_setPin(pin_t pin, bool set) {
    // set pin state like binary 1000010
    for (int current = (SN74HC595_LENGTH - 1); current >= 0; current--) {
        if (pin < 8) {
            int mask           = 1 << pin;
            pinStates[current] = ((pinStates[current] & ~mask) | set << pin);
        }
        pin -= 8;
    }
    // then send it using spi
    spi_start(SN74HC595_SPI_SLAVE_SELECT_PIN, SN74HC595_SPI_LSBFIRST, SN74HC595_SPI_MODE, SN74HC595_SPI_CLOCK_DIVISOR);
    writePinLow(SN74HC595_SPI_SLAVE_SELECT_PIN);
    spi_transmit(pinStates, SN74HC595_LENGTH);
    writePinHigh(SN74HC595_SPI_SLAVE_SELECT_PIN);
    spi_stop();

// pinstates debug
#if defined(CONSOLE_ENABLE) && defined(SN74HC595_DEBUG)
    if (timer_elapsed32(timer_now) >= 1000) {
        uprintf("PinStates HEX: ");
        for (uint8_t x = 0; x < SN74HC595_LENGTH; x++) {
            uprintf("PS %i:[0x%02x]|", x, pinStates[x]);
        }
        uprintf("PinStates BIN: ");
        for (uint8_t x = 0; x < SN74HC595_LENGTH; x++) {
            uprintf("|");
            print_bin_reverse8(pinStates[x]);
        }
        uprintf("\n");
        timer_now = timer_read32();
    }
#endif
}

/*
    for easy use
*/
void sn74hc595_setPinHigh(pin_t pin) {
    sn74hc595_setPin(pin, 1);
}

void sn74hc595_setPinLow(pin_t pin) {
    sn74hc595_setPin(pin, 0);
}

/*
    make a shortcut, slightly faster then set pin one by one
*/
/*
void sn74hc595_setHex(uint8_t * hexValue) {
    spi_start(SN74HC595_SPI_SLAVE_SELECT_PIN, SN74HC595_SPI_LSBFIRST, SN74HC595_SPI_MODE, SN74HC595_SPI_CLOCK_DIVISOR);
    writePinLow(SN74HC595_SPI_SLAVE_SELECT_PIN);
    spi_transmit(&hexValue, SN74HC595_LENGTH);
    writePinHigh(SN74HC595_SPI_SLAVE_SELECT_PIN);
    spi_stop();
}*/

void sn74hc595_AllPin_High(void) {
    for (uint8_t current = 0; current < SN74HC595_LENGTH; current++) {
        pinStates[current] = 0xFF;
    }

    spi_start(SN74HC595_SPI_SLAVE_SELECT_PIN, SN74HC595_SPI_LSBFIRST, SN74HC595_SPI_MODE, SN74HC595_SPI_CLOCK_DIVISOR);
    writePinLow(SN74HC595_SPI_SLAVE_SELECT_PIN);
    spi_transmit(pinStates, SN74HC595_LENGTH);
    writePinHigh(SN74HC595_SPI_SLAVE_SELECT_PIN);
    spi_stop();
}

void sn74hc595_AllPin_Low(void) {
    for (uint8_t current = 0; current < SN74HC595_LENGTH; current++) {
        pinStates[current] = 0x0;
    }
    spi_start(SN74HC595_SPI_SLAVE_SELECT_PIN, SN74HC595_SPI_LSBFIRST, SN74HC595_SPI_MODE, SN74HC595_SPI_CLOCK_DIVISOR);
    writePinLow(SN74HC595_SPI_SLAVE_SELECT_PIN);
    spi_transmit(pinStates, SN74HC595_LENGTH);
    writePinHigh(SN74HC595_SPI_SLAVE_SELECT_PIN);
    spi_stop();
}
