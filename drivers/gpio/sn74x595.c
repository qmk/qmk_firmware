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

#include "sn74x595.h"
#include "spi_master.h"
#include "print.h"

#ifdef CONSOLE_ENABLE
#    include "debug.h"
#    include "timer.h"
uint32_t timer_now;
#endif

spi_status_t res;
uint8_t      pinStates[SN74X595_LENGTH];
typedef enum { Low = 0, High = 1 } pinState;

/* get length */
uint8_t sn74x595_length(void) {
    return SN74X595_LENGTH;
}
/*
    init first
*/
void sn74x595_init(void) {
    spi_init();
}

bool sn74x595_spi_transmit(void) {
    if (!spi_start(SN74X595_SPI_SLAVE_SELECT_PIN, SN74X595_SPI_LSBFIRST, SN74X595_SPI_MODE, SN74X595_SPI_CLOCK_DIVISOR)) {
        uprint("sn74x595 spi can't start \n");
        spi_stop();
        return false;
    }

    res = spi_transmit(pinStates, SN74X595_LENGTH);
    if (res != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    spi_stop();
    return true;
}

/*
    set pin number on sn74x595
*/
bool sn74x595_setPin(uint8_t pin, bool set) {
#ifdef CONSOLE_ENABLE
    uint8_t current_pin = pin;
#endif
    // set pin state like binary 1000010
    for (int current = (SN74X595_LENGTH - 1); current >= 0; current--) {
        if (pin < 8) {
            int mask           = 1 << pin;
            pinStates[current] = ((pinStates[current] & ~mask) | set << pin);
        }
        pin -= 8;
    }

// pinstates debug
#ifdef CONSOLE_ENABLE
    if (timer_elapsed32(timer_now) >= 1000 && debug_sn74x595) {
        dprintf("pos: %d | ", current_pin);
        dprint("sn74x595 Pin States in HEX: ");
        for (int current = (SN74X595_LENGTH - 1); current >= 0; current--) {
            dprintf("PS %i:[0x%02x]", current, pinStates[current]);
            if (current > 0) {
                dprint(",");
            }
        }
        dprint(" | BIN: ");
        for (int current = (SN74X595_LENGTH - 1); current >= 0; current--) {
            debug_bin_reverse8(pinStates[current]);
            if (current > 0) {
                dprint("|");
            }
        }
        dprint("\n");
        timer_now = timer_read32();
    }
#endif

    // then send it using spi
    if (!sn74x595_spi_transmit()) {
        uprintf("sn74x595 can't set pin number %d to %s \n", current_pin, set ? "High" : "Low");
        return false;
    }
    return true;
}

/*
    for easy use
*/
bool sn74x595_setPinHigh(uint8_t pin) {
    return sn74x595_setPin(pin, High);
}

bool sn74x595_setPinLow(uint8_t pin) {
    return sn74x595_setPin(pin, Low);
}

/*
    make a shortcut, slightly faster then set pin one by one
*/

bool sn74x595_set_raw(uint8_t* raw_value) {
    if (!spi_start(SN74X595_SPI_SLAVE_SELECT_PIN, SN74X595_SPI_LSBFIRST, SN74X595_SPI_MODE, SN74X595_SPI_CLOCK_DIVISOR)) {
        uprint("sn74x595 spi can't start \n");
        spi_stop();
        return false;
    }

    res = spi_transmit(raw_value, SN74X595_LENGTH);
    if (res != SPI_STATUS_SUCCESS) {
        uprintf("sn74x595 spi can't set value[0x%02x] to peripheral \n", raw_value);
        spi_stop();
        return false;
    }

    spi_stop();
    return true;
}

bool sn74x595_AllPin_High(void) {
    for (uint8_t current = 0; current < SN74X595_LENGTH; current++) {
        pinStates[current] = 0xFF;
    }

    if (!sn74x595_spi_transmit()) {
        uprint("sn74x595 can't set all pin to High \n");
        return false;
    }
    return true;
}

bool sn74x595_AllPin_Low(void) {
    for (uint8_t current = 0; current < SN74X595_LENGTH; current++) {
        pinStates[current] = 0x0;
    }
    if (!sn74x595_spi_transmit()) {
        uprint("sn74x595 can't set all pin to Low \n");
        return false;
    }
    return true;
}
