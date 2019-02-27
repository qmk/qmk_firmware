#pragma once

// Include overwrites for specific keymap
#define HS60_ANSI
#undef  PRODUCT_ID
#define PRODUCT_ID      0x4854

// disable backlight after timeout in minutes, 0 = no timeout
#undef RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT
#define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 10
