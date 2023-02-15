#include <stdint.h>
#include "i2c_master.h"

#define RETURN_IF_I2C_FAIL(i2c_status, return_value) if(i2c_status != I2C_STATUS_SUCCESS) { return return_value; }
#define RETURN_STATUS_IF_I2C_FAIL(i2c_status) if(i2c_status != I2C_STATUS_SUCCESS) { return i2c_status; }

i2c_status_t i2c_updateRegBit(uint8_t devaddr, uint8_t register_to_update, uint8_t bit, uint8_t value, uint16_t timeout);
