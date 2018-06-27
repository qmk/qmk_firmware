#ifndef STM70_CONFIG_H_
#define STM70_CONFIG_H_

#include "../config.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001
/* in python2: list(u"whatever".encode('utf-16-le')) */
/*   at most 32 characters or the ugly hack in usb_main.c borks */
//  Modified by Xydane
#define MANUFACTURER "QMK"
#define USBSTR_MANUFACTURER    'T', '\x00', 'M', '\x00', 'K', '\x00', ' ', '\x00', '\xc6', '\x00'
#define PRODUCT "Stm32 70"
#define USBSTR_PRODUCT         'C', '\x00', 'h', '\x00', 'i', '\x00', 'b', '\x00', 'i', '\x00', 'O', '\x00', 'S', '\x00', ' ', '\x00', 'Q', '\x00', 'M', '\x00', 'K', '\x00', ' ', '\x00', 't', '\x00', 'e', '\x00', 's', '\x00', 't', '\x00'
#define DESCRIPTION "QMK keyboard firmware test for ChibiOS"

/* key matrix size */
//  Modified by Xydane
#define MATRIX_ROWS 6
#define MATRIX_COLS 15
#define DIODE_DIRECTION COL2ROW


#endif /* STM70_CONFIG_H_ */
