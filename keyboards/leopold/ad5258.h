// Copyright 2024 Wilhelm Schuster
// Copyright 2017 Balz Guenat
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

#define AD5258_RDAC_MAX 63
#define AD5258_RDAC_MIN 0

void ad5258_init(void);

int8_t ad5258_read_rdac(void);

int8_t ad5258_read_eeprom(void);

int8_t ad5258_write_rdac(uint8_t rdac);

void ad5258_restore_from_eeprom(void);
