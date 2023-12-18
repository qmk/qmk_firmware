// Copyright 2023 gkeyboard (@gkeyboard)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define OLED_DISPLAY_128X64
#define I2C1_SCL_PIN        GP21
#define I2C1_SDA_PIN        GP20
#define I2C_DRIVER I2CD0
#define OLED_BRIGHTNESS 128
#define OLED_FONT_H  "lib/glcdfont.c"

#define ENCODER_DIRECTION_FLIP          // If your encoder’s clockwise directions are incorrect, you can swap the A & B pad definitions

#define RGB_MATRIX_LED_COUNT 28

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES           // reacts to keypresses
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
