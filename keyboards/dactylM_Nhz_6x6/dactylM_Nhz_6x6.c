/* Copyright 2020 NeohertzParts
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

#include "dactylM_Nhz_6x6.h"
#include "print.h"

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
		    print("init i2c");
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }
	  print("init mcp23018\n");
    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // ROWS are port A
    // COLS are port B

    // COLS get set pull-high and INPUT.
    // ROWS get set as open-drain and OUTPUT

    // CONFIGURE DEVICE
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, DACTYL_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0x05, DACTYL_I2C_TIMEOUT);              if (mcp23018_status) goto out;  // IOCON
    mcp23018_status = i2c_write(0b00000000, DACTYL_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();
    _delay_ms(10);

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, DACTYL_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, DACTYL_I2C_TIMEOUT);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000, DACTYL_I2C_TIMEOUT);        if (mcp23018_status) goto out;  // A
    mcp23018_status = i2c_write(0b11111111, DACTYL_I2C_TIMEOUT);        if (mcp23018_status) goto out;  // B
    i2c_stop();
    _delay_ms(10);

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, DACTYL_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, DACTYL_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000, DACTYL_I2C_TIMEOUT);        if (mcp23018_status) goto out; // A
    mcp23018_status = i2c_write(0b11111111, DACTYL_I2C_TIMEOUT);        if (mcp23018_status) goto out; // B
    i2c_stop();
    _delay_ms(10);

	// LED, write pin LOW, bcuz open drain outputs :(
	// also set rows to OPEN drain
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, DACTYL_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(OLATA, DACTYL_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111, DACTYL_I2C_TIMEOUT);        if (mcp23018_status) goto out; // A
    mcp23018_status = i2c_write(0b00000000, DACTYL_I2C_TIMEOUT);        if (mcp23018_status) goto out; // B
    i2c_stop();

    // Read the column pin states (should be all 1s)
    _delay_ms(10);
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, DACTYL_I2C_TIMEOUT);
    mcp23018_status = i2c_write(GPIOB, DACTYL_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    i2c_start(I2C_ADDR_READ, DACTYL_I2C_TIMEOUT);
    mcp23018_status = i2c_read_nack(DACTYL_I2C_TIMEOUT);
    i2c_status_t stat2 = ~mcp23018_status;
    i2c_stop();

    mcp23018_status = i2c_start(I2C_ADDR_WRITE, DACTYL_I2C_TIMEOUT);
    mcp23018_status = i2c_write(0x05, DACTYL_I2C_TIMEOUT);             if (mcp23018_status) goto out; // read config reg
    i2c_start(I2C_ADDR_READ, DACTYL_I2C_TIMEOUT);
    mcp23018_status = i2c_read_nack(DACTYL_I2C_TIMEOUT);
    mcp23018_status = mcp23018_status | stat2; // Should be 0s all around
    i2c_stop();

out:
    i2c_stop();

    // SREG=sreg_prev;

    return mcp23018_status;
}
