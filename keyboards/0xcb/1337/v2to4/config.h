// Copyright 2022 Conor Burns (@Conor-Burns)
/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define DRIVER_LED_TOTAL 12
#define LED_FLAG_UNDERGLOW 0x02
#define LED_FLAG_KEYLIGHT 0x04
#define RGB_DISABLE_WHEN_USB_SUSPENDED false
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_BREATHING
#define RGB_MATRIX_STARTUP_HUE 152
#define RGB_MATRIX_STARTUP_SAT 232
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_STARTUP_SPD 50

#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
/* Oled Size */
#define OLED_DISPLAY_128X64
#define OLED_FONT_END 223
#define OLED_FONT_H "gfxfont.c"
