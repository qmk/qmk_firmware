// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// settings for the oled keyboard demo with Adafruit 0.91" OLED display on the Stemma QT port
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP1

#define OLED_TIMEOUT 3000000 // 5 minutes before oled turns off
