/*  Copyright 2020
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

#include "spi_master.h"

#include "timer.h"

#if defined(__AVR_AT90USB162__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#    define SPI_SCK_PIN B1
#    define SPI_MOSI_PIN B2
#    define SPI_MISO_PIN B3
#elif defined(__AVR_ATmega32A__)
#    define SPI_SCK_PIN B7
#    define SPI_MOSI_PIN B5
#    define SPI_MISO_PIN B6
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#    define SPI_SCK_PIN B5
#    define SPI_MOSI_PIN B3
#    define SPI_MISO_PIN B4
#endif

#ifndef SPI_TIMEOUT
#    define SPI_TIMEOUT 100
#endif

static pin_t   current_slave_pin     = NO_PIN;
static bool    current_cs_active_low = true;
static uint8_t current_slave_config  = 0;
static bool    current_slave_2x      = false;

static inline void spi_select(void) {
    gpio_write_pin(current_slave_pin, current_cs_active_low ? 0 : 1);
}

static inline void spi_unselect(void) {
    gpio_write_pin(current_slave_pin, current_cs_active_low ? 1 : 0);
}

void spi_init(void) {
    gpio_write_pin_high(SPI_SS_PIN);
    gpio_set_pin_output(SPI_SCK_PIN);
    gpio_set_pin_output(SPI_MOSI_PIN);
    gpio_set_pin_input(SPI_MISO_PIN);

    SPCR = (_BV(SPE) | _BV(MSTR));
}

bool spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor) {
    spi_start_config_t start_config = {0};
    start_config.slave_pin          = slavePin;
    start_config.lsb_first          = lsbFirst;
    start_config.mode               = mode;
    start_config.divisor            = divisor;
    start_config.cs_active_low      = true;
    return spi_start_extended(&start_config);
}

bool spi_start_extended(spi_start_config_t *start_config) {
    if (current_slave_pin != NO_PIN || start_config->slave_pin == NO_PIN) {
        return false;
    }

    current_slave_config = 0;

    if (start_config->lsb_first) {
        current_slave_config |= _BV(DORD);
    }

    switch (start_config->mode) {
        case 1:
            current_slave_config |= _BV(CPHA);
            break;
        case 2:
            current_slave_config |= _BV(CPOL);
            break;
        case 3:
            current_slave_config |= (_BV(CPOL) | _BV(CPHA));
            break;
    }

    uint16_t roundedDivisor = 1;
    while (roundedDivisor < start_config->divisor) {
        roundedDivisor <<= 1;
    }

    switch (roundedDivisor) {
        case 16:
            current_slave_config |= _BV(SPR0);
            break;
        case 64:
            current_slave_config |= _BV(SPR1);
            break;
        case 128:
            current_slave_config |= (_BV(SPR1) | _BV(SPR0));
            break;
        case 2:
            current_slave_2x = true;
            break;
        case 8:
            current_slave_2x = true;
            current_slave_config |= _BV(SPR0);
            break;
        case 32:
            current_slave_2x = true;
            current_slave_config |= _BV(SPR1);
            break;
    }

    SPCR |= current_slave_config;
    if (current_slave_2x) {
        SPSR |= _BV(SPI2X);
    }
    current_slave_pin     = start_config->slave_pin;
    current_cs_active_low = start_config->cs_active_low;
    gpio_set_pin_output(current_slave_pin);
    spi_select();

    return true;
}

spi_status_t spi_write(uint8_t data) {
    SPDR = data;

    uint16_t timeout_timer = timer_read();
    while (!(SPSR & _BV(SPIF))) {
        if ((timer_read() - timeout_timer) >= SPI_TIMEOUT) {
            return SPI_STATUS_TIMEOUT;
        }
    }

    return SPDR;
}

spi_status_t spi_read() {
    SPDR = 0x00; // Dummy

    uint16_t timeout_timer = timer_read();
    while (!(SPSR & _BV(SPIF))) {
        if ((timer_read() - timeout_timer) >= SPI_TIMEOUT) {
            return SPI_STATUS_TIMEOUT;
        }
    }

    return SPDR;
}

spi_status_t spi_transmit(const uint8_t *data, uint16_t length) {
    spi_status_t status;

    for (uint16_t i = 0; i < length; i++) {
        status = spi_write(data[i]);

        if (status < 0) {
            return status;
        }
    }

    return SPI_STATUS_SUCCESS;
}

spi_status_t spi_receive(uint8_t *data, uint16_t length) {
    spi_status_t status;

    for (uint16_t i = 0; i < length; i++) {
        status = spi_read();

        if (status >= 0) {
            data[i] = status;
        } else {
            return status;
        }
    }

    return SPI_STATUS_SUCCESS;
}

void spi_stop(void) {
    if (current_slave_pin != NO_PIN) {
        gpio_set_pin_output(current_slave_pin);
        spi_unselect();
        current_slave_pin = NO_PIN;
        SPSR &= ~(_BV(SPI2X));
        SPCR &= ~(current_slave_config);
        current_slave_config = 0;
        current_slave_2x     = false;
    }
}
