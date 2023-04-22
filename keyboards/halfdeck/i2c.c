// Copyright 2018 Wez Furlong (@wez)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "i2c.h"
#include "lib/lufa/LUFA/Drivers/Peripheral/AVR8/TWI_AVR8.c"
#include "debug.h"

const char *twi_err_str(uint8_t res) {
  switch (res) {
    case TWI_ERROR_NoError: return "OK";
    case TWI_ERROR_BusFault: return "BUSFAULT";
    case TWI_ERROR_BusCaptureTimeout: return "BUSTIMEOUT";
    case TWI_ERROR_SlaveResponseTimeout: return "SLAVETIMEOUT";
    case TWI_ERROR_SlaveNotReady: return "SLAVENOTREADY";
    case TWI_ERROR_SlaveNAK: return "SLAVENAK";
    default: return "UNKNOWN";
  }
}

void twi_init(unsigned long freq) {
  TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, freq));
}

bool twi_write_register(uint8_t i2cAddress, uint8_t reg, uint8_t val) {
  uint8_t addr = reg;
  uint8_t result = TWI_WritePacket(i2cAddress << 1, i2cTimeout, &addr, sizeof(addr),
                                   &val, sizeof(val));
  if (result) {
    xprintf("sx1509: set_register %d = %d failed: %s\n", reg, val, twi_err_str(result));
  }
  return result == 0;
}

bool twi_read_register(uint8_t i2cAddress, uint8_t reg, uint8_t *val) {
  uint8_t addr = reg;
  uint8_t result;

  for (int i = 0; i < 1; i++) {
    result = TWI_ReadPacket(i2cAddress << 1, i2cTimeout, &addr,
                                  sizeof(addr), val, 1);
    if (result == TWI_ERROR_SlaveNotReady) {
      _delay_ms(1);
      continue;
    }
    break;
  }
  if (result) {
    xprintf("i2c: device %d: read reg %d: %s\n", i2cAddress, reg, twi_err_str(result));
    return false;
  }
  return true;
}
