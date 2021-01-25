/**
 * @file tca6424.c
 * @author astro
 * @brief  driver for the tca6424
 *
 * Copyright 2020 astro <yuleiz@gmail.com>
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

#include "tca6424.h"
#include "i2c_master.h"

#define TCA6424_INPUT_PORT0     0x0
#define TCA6424_INPUT_PORT1     0x01
#define TCA6424_INPUT_PORT2     0x02

#define TCA6424_OUTPUT_PORT0    0x04
#define TCA6424_OUTPUT_PORT1    0x05
#define TCA6424_OUTPUT_PORT2    0x06

#define TCA6424_POLARITY_PORT0  0x08
#define TCA6424_POLARITY_PORT1  0x09
#define TCA6424_POLARITY_PORT2  0x0A

#define TCA6424_CONF_PORT0      0x0C
#define TCA6424_CONF_PORT1      0x0D
#define TCA6424_CONF_PORT2      0x0E

#define TIMEOUT         100

void tca6424_init(void)
{
    i2c_init();
}

static void write_port(uint8_t p, uint8_t d)
{
    i2c_writeReg(TCA6424_ADDR, p, &d, 1, TIMEOUT);
}

static uint8_t read_port(uint8_t port)
{
    uint8_t data = 0;
    i2c_readReg(TCA6424_ADDR, port, &data, 1, TIMEOUT);
    return data;
}

void tca6424_write_config(TCA6424_PORT port, uint8_t data)
{
    switch(port) {
        case TCA6424_PORT0:
            write_port(TCA6424_CONF_PORT0, data);
            break;
        case TCA6424_PORT1:
            write_port(TCA6424_CONF_PORT1, data);
            break;
        case TCA6424_PORT2:
            write_port(TCA6424_CONF_PORT2, data);
            break;
    }
}

void tca6424_write_polarity(TCA6424_PORT port, uint8_t data)
{
    switch(port) {
        case TCA6424_PORT0:
            write_port(TCA6424_POLARITY_PORT0, data);
            break;
        case TCA6424_PORT1:
            write_port(TCA6424_POLARITY_PORT1, data);
            break;
        case TCA6424_PORT2:
            write_port(TCA6424_POLARITY_PORT2, data);
            break;
    }
}

void tca6424_write_port(TCA6424_PORT port, uint8_t data)
{
    switch(port) {
        case TCA6424_PORT0:
            write_port(TCA6424_OUTPUT_PORT0, data);
            break;
        case TCA6424_PORT1:
            write_port(TCA6424_OUTPUT_PORT1, data);
            break;
        case TCA6424_PORT2:
            write_port(TCA6424_OUTPUT_PORT2, data);
            break;
    }
}

uint8_t tca6424_read_port(TCA6424_PORT port)
{
    switch(port) {
        case TCA6424_PORT0:
            return read_port(TCA6424_INPUT_PORT0);
        case TCA6424_PORT1:
            return read_port(TCA6424_INPUT_PORT1);
        case TCA6424_PORT2:
            return read_port(TCA6424_INPUT_PORT2);
    }

    return 0;
}
