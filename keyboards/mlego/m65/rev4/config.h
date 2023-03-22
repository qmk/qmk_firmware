// Copyright 2021-2022 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X32
#    define I2C1_SCL_PIN B9
#    define I2C1_SDA_PIN B8
#    define OLED_BRIGHTNESS 128
#    define OLED_FONT_H "keyboards/mlego/m65/lib/glcdfont.c"
#endif
