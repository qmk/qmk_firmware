#include "sx60.h"
#include "i2c_master.h"


bool i2c_initialized = 0;
uint8_t mcp23018_status = 0x20;

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    /* I2C subsystem */

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }

    /* B Pins are Row, A pins are Columns 
       Set them to output */
    static uint8_t direction[2] = {
        0b11111111,
        0b00000000,
    };
    static uint8_t pullup[2] = {
        0b11111111,
        0b00000000,
    };

    mcp23018_status = i2c_writeReg(I2C_ADDR, IODIRA, direction, 2, I2C_TIMEOUT);
    if (mcp23018_status) return mcp23018_status;

    mcp23018_status = i2c_writeReg(I2C_ADDR, GPPUA, pullup, 2, I2C_TIMEOUT);
    return mcp23018_status;
}
