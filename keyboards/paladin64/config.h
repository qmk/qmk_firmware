#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    inachie
#define PRODUCT         paladin64

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#ifdef PS2_USE_USART
    #define PS2_CLOCK_PORT  PORTD
    #define PS2_CLOCK_PIN   PIND
    #define PS2_CLOCK_DDR   DDRD
    #define PS2_CLOCK_BIT   5
    #define PS2_DATA_PORT   PORTD
    #define PS2_DATA_PIN    PIND
    #define PS2_DATA_DDR    DDRD
    #define PS2_DATA_BIT    2

    /* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling
     * edge */
    /* set DDR of CLOCK as input to be slave */
    #define PS2_USART_INIT() do {   \
                    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
                    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
                    UCSR1C = ((1 << UMSEL10) |  \
                                                  (3 << UPM10)   |  \
                                                  (0 << USBS1)   |  \
                                                  (3 << UCSZ10)  |  \
                                                  (0 << UCPOL1));   \
                    UCSR1A = 0;                 \
                    UBRR1H = 0;                 \
                    UBRR1L = 0;                 \
                } while (0)
    #define PS2_USART_RX_INT_ON() do {  \
                    UCSR1B = ((1 << RXCIE1) |       \
                                                  (1 << RXEN1));        \
                } while (0)
    #define PS2_USART_RX_POLL_ON() do { \
                    UCSR1B = (1 << RXEN1);          \
                } while (0)
    #define PS2_USART_OFF() do {    \
                    UCSR1C = 0;                 \
                    UCSR1B &= ~((1 << RXEN1) |  \
                                                    (1 << TXEN1));  \
                } while (0)
    #define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
    #define PS2_USART_RX_DATA       UDR1
    #define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
    #define PS2_USART_RX_VECT       USART1_RX_vect
#endif

#ifdef PS2_USE_INT
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   2
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    5

    #define PS2_INT_INIT()  do {    \
        EICRA |= ((1<<ISC21) |      \
                  (0<<ISC20));      \
    } while (0)
    #define PS2_INT_ON()  do {      \
        EIMSK |= (1<<INT2);         \
    } while (0)
    #define PS2_INT_OFF() do {      \
        EIMSK &= ~(1<<INT2);        \
    } while (0)
    #define PS2_INT_VECT   INT2_vect

#endif

/* key matrix pins */
#define MATRIX_ROW_PINS { C6, B6, B5, B4, D7, D6, B0, D3 }
#define MATRIX_COL_PINS { C7, F7, F6, F5, F4, F1, F0, D1 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN D0
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 12
#endif

#endif
