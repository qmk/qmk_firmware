// Copyright 2022 ziptyze (@ziptyze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define OLED_DISPLAY_128X32
#define I2C1_SCL_PIN        GP17
#define I2C1_SDA_PIN        GP16
#define I2C_DRIVER I2CD0
#define OLED_BRIGHTNESS 128
#define OLED_FONT_H "keyboards/1upkeyboards/pi40/lib/glcdfont.c"

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
