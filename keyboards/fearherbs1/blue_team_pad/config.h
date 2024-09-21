// Copyright 2022-2023 Thomas Autiello Jr (@fearherbs1)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef OLED_ENABLE
#define I2C1_SCL_PIN        GP27
#define I2C1_SDA_PIN        GP26
#define I2C_DRIVER I2CD1
#define OLED_DISPLAY_128X32
#define OLED_BRIGHTNESS 128
#endif
