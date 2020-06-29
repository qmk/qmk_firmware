/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
          2020 Pierre Chevalier <pierrechevalier83@gmail.com>

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
#include QMK_KEYBOARD_H

bool         i2c_initialized = 0;
i2c_status_t mcp23017_status = I2C_ADDR;

void matrix_init_kb(void) {
    // set unused pins on mcu as input with internal pull-up enabled
    pin_t unused_pins_mcu[UNUSED_MCU] = UNUSED_PINS_MCU;
    for (int pin_index = 0; pin_index < UNUSED_MCU; pin_index++) {
        pin_t pin = unused_pins_mcu[pin_index];
        setPinInputHigh(pin);
    }

    matrix_init_user();
}

uint8_t init_mcp23017(void) {
    print("starting init");
    mcp23017_status = I2C_ADDR;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(I2C_TIMEOUT);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23017_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);
    if (mcp23017_status) goto out;
    mcp23017_status = i2c_write(IODIRA, I2C_TIMEOUT);
    if (mcp23017_status) goto out;
    // This means: we will read all the bits on GPIOA
    mcp23017_status = i2c_write(0b11111111, I2C_TIMEOUT);
    if (mcp23017_status) goto out;
    // This means: we will write to the pins 0-4 on GPIOB (in select_rows)
    mcp23017_status = i2c_write(0b11110000, I2C_TIMEOUT);
    if (mcp23017_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23017_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);
    if (mcp23017_status) goto out;
    mcp23017_status = i2c_write(GPPUA, I2C_TIMEOUT);
    if (mcp23017_status) goto out;
    // This means: we will read all the bits on GPIOA
    mcp23017_status = i2c_write(0b11111111, I2C_TIMEOUT);
    if (mcp23017_status) goto out;
    // This means: we will write to the pins 0-4 on GPIOB (in select_rows)
    mcp23017_status = i2c_write(0b11110000, I2C_TIMEOUT);
    if (mcp23017_status) goto out;

out:
    i2c_stop();
    return mcp23017_status;
}
