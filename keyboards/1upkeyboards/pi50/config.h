// Copyright 2023 ziptyze
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define I2C1_SCL_PIN GP11
#define I2C1_SDA_PIN GP10
#define I2C_DRIVER I2CD1
#define OLED_BRIGHTNESS 128
#define OLED_FONT_H "keyboards/1upkeyboards/pi50/lib/glcdfont.c"

#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
