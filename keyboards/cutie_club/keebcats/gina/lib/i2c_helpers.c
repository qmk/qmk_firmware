#include <stdint.h>
#include "i2c_master.h"

#include "i2c_helpers.h"

void i2c_updateRegBit(uint8_t devaddr, uint8_t register_to_update, uint8_t bit, uint8_t value, uint16_t timeout) {
    uint8_t register_data;
    i2c_readReg(devaddr, register_to_update, &register_data, 1, timeout);

    if(value) {
        register_data |= 1 << bit;
    } else {
        register_data &= ~(1 << bit);
    }

    i2c_writeReg(devaddr, register_to_update, &register_data, 1, timeout);
}