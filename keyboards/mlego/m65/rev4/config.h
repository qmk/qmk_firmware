// Copyright 2021-2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LED_RSE_PIN B13
#define LED_LWR_PIN B12

#ifdef OLED_ENABLE
#    define I2C1_SCL_PIN B9
#    define I2C1_SDA_PIN B8
#    define OLED_BRIGHTNESS 128
#    define OLED_FONT_H "keyboards/mlego/m65/lib/glcdfont.c"
#endif
