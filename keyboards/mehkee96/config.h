#ifndef CONFIG_H
#define CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
#define MANUFACTURER    mehkee
#define PRODUCT         96kee

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 15

#define RGBLED_NUM 16
#define RGBLIGHT_ANIMATIONS

#define NO_UART 1
#define BOOTLOADHID_BOOTLOADER 1

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

#endif
