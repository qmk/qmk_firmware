/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

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

#include "ergodox_extended.h"

keyboard_config_t keyboard_config;

bool         i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
    // (tied to Vcc for hardware convenience)
    DDRB &= ~(1 << 4);   // set B(4) as input
    PORTB &= ~(1 << 4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, E6
    // set as input with internal pull-up enabled
    DDRC &= ~(1 << 7);
    DDRD &= ~(1 << 5 | 1 << 4);
    DDRE &= ~(1 << 6);
    PORTC |= (1 << 7);
    PORTD |= (1 << 5 | 1 << 4);
    PORTE |= (1 << 6);

    keyboard_config.raw = eeconfig_read_kb();
    matrix_init_user();
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }
    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    uint8_t data[] = {0b00000000, 0b00111111};
    mcp23018_status = i2c_writeReg(I2C_ADDR, IODIRA, data, 2, ERGODOX_EXTENDED_I2C_TIMEOUT);

    if (!mcp23018_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        mcp23018_status = i2c_writeReg(I2C_ADDR, GPPUA, data, 2, ERGODOX_EXTENDED_I2C_TIMEOUT);
    }

    // SREG=sreg_prev;

    return mcp23018_status;
}

// clang-format on

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    keyboard_config.raw = 0;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void matrix_scan_kb(void) {
    matrix_scan_user();
}
