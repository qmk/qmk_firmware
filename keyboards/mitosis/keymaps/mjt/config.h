#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */

#define VENDOR_ID       0xFEEB
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    MJT
#define PRODUCT         Mitosis
#define DESCRIPTION     q.m.k. keyboard firmware for Mitosis

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 10

// fix iPhone power adapter issue
#define USB_MAX_POWER_CONSUMPTION 50
// #define CATERINA_BOOTLOADER

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
//#define BACKLIGHT_LEVELS 3

#define ONESHOT_TIMEOUT 500


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

#define PREVENT_STUCK_MODIFIERS

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

//UART settings for communication with the RF microcontroller
#define SERIAL_UART_BAUD 1000000
#define SERIAL_UART_DATA UDR1
#define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#define SERIAL_UART_RXD_PRESENT (UCSR1A & _BV(RXC1))
#define SERIAL_UART_INIT() do { \
    	/* baud rate */ \
    	UBRR1L = SERIAL_UART_UBRR; \
    	/* baud rate */ \
    	UBRR1H = SERIAL_UART_UBRR >> 8; \
    	/* enable TX and RX */ \
    	UCSR1B = _BV(TXEN1) | _BV(RXEN1); \
    	/* 8-bit data */ \
    	UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
  	} while(0)

#endif
