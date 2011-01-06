#ifndef CONFIG_H
#define CONFIG_H

/* controller configuration */
#include "controller_teensy.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xCAFE
#define MANUFACTURER    t.m.k.
#define PRODUCT         HHKB mod
#define DESCRIPTION     t.m.k. keyboard firmware for HHKB mod

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8
/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* USB NKey Rollover */
#ifdef USB_NKRO_ENABLE
#endif

/* mouse keys */
#ifdef MOUSEKEY_ENABLE
#   define MOUSEKEY_DELAY_TIME 192
#endif

/* PS/2 mouse */
#ifdef PS2_MOUSE_ENABLE
/*
#   define PS2_CLOCK_PORT  PORTF
#   define PS2_CLOCK_PIN   PINF
#   define PS2_CLOCK_DDR   DDRF
#   define PS2_CLOCK_BIT   0
#   define PS2_DATA_PORT   PORTF
#   define PS2_DATA_PIN    PINF
#   define PS2_DATA_DDR    DDRF
#   define PS2_DATA_BIT    1
*/
#endif

#endif
