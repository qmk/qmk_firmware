// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifndef ADS1100_ADDRESS
#    define ADS1100_ADDRESS (0b1001000 << 1)
#endif
#define ADS1100_TIMEOUT 100
#ifndef ADS1100_CONFIG
#    define ADS1100_CONFIG 0x8C
#endif
#ifndef ADS1100_MAX_VAL
#    define ADS1100_MAX_VAL 0x7FFF
#endif

void    ads1100_init(void);
int16_t ads1100_read(void);