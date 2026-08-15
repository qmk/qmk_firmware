// Copyright 2024-2026 DailyDesk, gregandcin <gregandcinbusiness@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef I2C_DRIVER
#define I2C_DRIVER I2CD0
#undef I2C1_SCL_PIN
#define I2C1_SCL_PIN GP1
#undef I2C1_SDA_PIN
#define I2C1_SDA_PIN GP0
