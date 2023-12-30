/* Copyright 2018 Mike Roberts
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
#include <stdbool.h>
#include "action.h"
#include <LUFA/Drivers/Peripheral/TWI.h>
#include <LUFA/Drivers/Peripheral/AVR8/TWI_AVR8.c>
#include "mcp23017.h"
#include "debug.h"
#include "wait.h"

uint8_t bit_for_pin(uint8_t pin);

uint8_t expander_write(uint8_t reg, uint8_t data);

uint8_t expander_read(uint8_t reg, uint8_t *data);

void expander_config(void);

static const char *twi_err_str(uint8_t res) {
    switch (res) {
        case TWI_ERROR_NoError:
            return "OK";
        case TWI_ERROR_BusFault:
            return "BUSFAULT";
        case TWI_ERROR_BusCaptureTimeout:
            return "BUSTIMEOUT";
        case TWI_ERROR_SlaveResponseTimeout:
            return "SLAVETIMEOUT";
        case TWI_ERROR_SlaveNotReady:
            return "SLAVENOTREADY";
        case TWI_ERROR_SlaveNAK:
            return "SLAVENAK";
        default:
            return "UNKNOWN";
    }
}

void expander_init(void) {
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 400000));
}

// set IN and HI
void expander_unselect_all(void) {
    expander_write(EXPANDER_REG_IODIRA, 0xff);
    expander_write(EXPANDER_REG_IODIRB, 0xff);
    expander_write(EXPANDER_REG_OLATA, 0xff);
    expander_write(EXPANDER_REG_OLATB, 0xff);
    wait_us(EXPANDER_PAUSE);
}

// set OUT and LOW
void expander_select(uint8_t pin) {
    const uint8_t mask = 0xff & ~(1 << bit_for_pin(pin));
    if (pin < 8) {
        expander_write(EXPANDER_REG_IODIRA, mask);
        expander_write(EXPANDER_REG_OLATA, mask);
    } else {
        expander_write(EXPANDER_REG_IODIRB, mask);
        expander_write(EXPANDER_REG_OLATB, mask);
    }
    wait_us(EXPANDER_PAUSE);
}

void expander_config(void) {
    // set everything to input
    expander_write(EXPANDER_REG_IODIRA, 0xff);
    expander_write(EXPANDER_REG_IODIRB, 0xff);

    // turn on pull-ups
    expander_write(EXPANDER_REG_GPPUA, 0xff);
    expander_write(EXPANDER_REG_GPPUB, 0xff);

    // disable interrupts
    expander_write(EXPANDER_REG_GPINTENA, 0x0);
    expander_write(EXPANDER_REG_GPINTENB, 0x0);

    // polarity
    expander_write(EXPANDER_REG_IPOLA, 0x0);
    expander_write(EXPANDER_REG_IPOLB, 0x0);
}

uint8_t bit_for_pin(uint8_t pin) {
    return pin % 8;
}

uint8_t expander_write(uint8_t reg, unsigned char val) {
    uint8_t addr = reg;
    uint8_t result = TWI_WritePacket(EXPANDER_ADDR << 1, I2C_TIMEOUT, &addr, sizeof(addr), &val, sizeof(val));
    if (result) {
        xprintf("mcp: set_register %d = %d failed: %s\n", reg, val, twi_err_str(result));
    }
    return result == 0;
}

