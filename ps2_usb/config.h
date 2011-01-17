#ifndef CONFIG_H
#define CONFIG_H

/* controller configuration */
#include "controller_teensy.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6512
#define MANUFACTURER    t.m.k.
#define PRODUCT         PS/2 keyboard converter
#define DESCRIPTION     convert PS/2 keyboard to USB

/* matrix size */
#define MATRIX_ROWS 32  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4
/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* USB NKey Rollover */
#ifdef USB_NKRO_ENABLE
#endif

/* mouse keys */
#ifdef MOUSEKEY_ENABLE
#   define MOUSEKEY_DELAY_TIME 255
#endif

/* PS/2 mouse */
#define PS2_CLOCK_PORT  PORTF
#define PS2_CLOCK_PIN   PINF
#define PS2_CLOCK_DDR   DDRF
#define PS2_CLOCK_BIT   0
#define PS2_DATA_PORT   PORTF
#define PS2_DATA_PIN    PINF
#define PS2_DATA_DDR    DDRF
#define PS2_DATA_BIT    1

#endif
