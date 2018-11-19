#pragma once

#include "config_common.h"

#define VENDOR_ID       0x1234
#define PRODUCT_ID      0x5678
#define DEVICE_VER      0x0001
#define MANUFACTURER    QMK
#define PRODUCT         108Key-Trackpoint
#define DESCRIPTION     A 108 key ANSI keyboard with a trackpoint and three mouse buttons

#define MATRIX_ROWS 8
#define MATRIX_COLS 23

#ifdef PS2_USE_USART
  #define PS2_CLOCK_PORT  PORTD
  #define PS2_CLOCK_PIN   PIND
  #define PS2_CLOCK_DDR   DDRD
  #define PS2_CLOCK_BIT   5
  #define PS2_DATA_PORT   PORTD
  #define PS2_DATA_PIN    PIND
  #define PS2_DATA_DDR    DDRD
  #define PS2_DATA_BIT    2

  /* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
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

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { C0, C1, C2, C3, C4, C5, C6, C7, D0, D1, F0, D3, D4, F1, D6, D7, E0, E1, E2, E3, E4, E5, E6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCING_DELAY 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

/* key combination for commkand */
#define IS_COMMAND() ( \
  keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

