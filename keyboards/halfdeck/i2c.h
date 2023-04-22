// Copyright 2018 Wez Furlong (@wez)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "lib/lufa/LUFA/Drivers/Peripheral/TWI.h"
#ifndef i2cTimeout
#define i2cTimeout 200 // milliseconds
#endif

#ifdef __cplusplus
extern "C" {
#endif
const char *twi_err_str(uint8_t res);

void twi_init(unsigned long freq);
bool twi_write_register(uint8_t i2cAddress, uint8_t reg, uint8_t val);
bool twi_read_register(uint8_t i2cAddress, uint8_t reg, uint8_t *val);
#ifdef __cplusplus
}
#endif
