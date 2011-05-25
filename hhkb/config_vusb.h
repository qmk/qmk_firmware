#ifndef CONFIG_H
#define CONFIG_H


#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xC0FE
// TODO: share these strings with usbconfig.h
// Edit usbconfig.h to change these.
#define MANUFACTURER    t.m.k.
#define PRODUCT         HHKB mod
#define DESCRIPTION     t.m.k. keyboard firmware for HHKB mod


/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (BIT_LSHIFT | BIT_RSHIFT) || \
    keyboard_report->mods == (BIT_LCTRL | BIT_RSHIFT) \
)


/* mouse keys */
#ifdef MOUSEKEY_ENABLE
#   define MOUSEKEY_DELAY_TIME 255
#endif


#endif
