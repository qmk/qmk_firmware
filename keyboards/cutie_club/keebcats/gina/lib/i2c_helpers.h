#include <stdint.h>

void i2c_updateRegBit(uint8_t devaddr, uint8_t register_to_update, uint8_t bit, uint8_t value, uint16_t timeout);