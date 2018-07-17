/*
Copyright 2016 Luiz Ribeiro <luizribeiro@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Please do not modify this file 

#include <avr/io.h>
#include <util/twi.h>

#include "i2c.h"

void i2c_set_bitrate(uint16_t bitrate_khz) {
    uint8_t bitrate_div = ((F_CPU / 1000l) / bitrate_khz);
    if (bitrate_div >= 16) {
        bitrate_div = (bitrate_div - 16) / 2;
    }
    TWBR = bitrate_div;
}

void i2c_init(void) {
    // set pull-up resistors on I2C bus pins
    PORTC |= 0b11;

    i2c_set_bitrate(400);

    // enable TWI (two-wire interface)
    TWCR |= (1 << TWEN);

    // enable TWI interrupt and slave address ACK
    TWCR |= (1 << TWIE);
    TWCR |= (1 << TWEA);
}

uint8_t i2c_start(uint8_t address) {
    // reset TWI control register
    TWCR = 0;

    // begin transmission and wait for it to end
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    // check if the start condition was successfully transmitted
    if ((TWSR & 0xF8) != TW_START) {
        return 1;
    }

    // transmit address and wait
    TWDR = address;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    // check if the device has acknowledged the READ / WRITE mode
    uint8_t twst = TW_STATUS & 0xF8;
    if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK)) {
        return 1;
    }

    return 0;
}

void i2c_stop(void) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

uint8_t i2c_write(uint8_t data) {
    TWDR = data;

    // transmit data and wait
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xF8) != TW_MT_DATA_ACK) {
        return 1;
    }

    return 0;
}

uint8_t i2c_send(uint8_t address, uint8_t *data, uint16_t length) {
    if (i2c_start(address)) {
        return 1;
    }

    for (uint16_t i = 0; i < length; i++) {
        if (i2c_write(data[i])) {
            return 1;
        }
    }

    i2c_stop();

    return 0;
}
