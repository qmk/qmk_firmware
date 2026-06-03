// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// Enable I2C0 for AS5600 Magnetic Encoder
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

// Enable I2C1 for OLED Display
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE

