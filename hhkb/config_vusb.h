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


/* PS/2 lines */
#ifdef PS2_MOUSE_ENABLE

#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   4
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    0


// Synchronous USART is used to receive data from keyboard.
// Use RXD pin for PS/2 DATA line and XCK for PS/2 CLOCK.
// NOTE: This is recomended strongly if you use V-USB library.
#define PS2_USE_USART

// External or Pin Change Interrupt is used to receive data from keyboard.
// Use INT1 or PCINTxx for PS/2 CLOCK line. see below.
//#define PS2_USE_INT


#ifdef PS2_USE_USART
// synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge
// set DDR of CLOCK as input to be slave
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR0C = ((1 << UMSEL00) |  \
              (3 << UPM00)   |  \
              (0 << USBS0)   |  \
              (3 << UCSZ00)  |  \
              (0 << UCPOL0));   \
    UCSR0A = 0;                 \
    UBRR0H = 0;                 \
    UBRR0L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR0B = ((1 << RXCIE0) |       \
              (1 << RXEN0));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR0B = (1 << RXEN0);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR0C = 0;                 \
    UCSR0B &= ~((1 << RXEN0) |  \
                (1 << TXEN0));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR0A & (1<<RXC0))
#define PS2_USART_RX_DATA       UDR0
#define PS2_USART_ERROR         (UCSR0A & ((1<<FE0) | (1<<DOR0) | (1<<UPE0)))
#define PS2_USART_RX_VECT       USART_RX_vect
#endif


#ifdef PS2_USE_INT
/* INT1
#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC11) |      \
              (0<<ISC10));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT1);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT1);        \
} while (0)
#define PS2_INT_VECT    INT1_vect
*/

/* PCINT20 */
#define PS2_INT_INIT()  do {    \
    PCICR  |= (1<<PCIE2);       \
} while (0)
#define PS2_INT_ON()  do {      \
    PCMSK2 |= (1<<PCINT20);     \
} while (0)
#define PS2_INT_OFF() do {      \
    PCMSK2 &= ~(1<<PCINT20);    \
    PCICR  &= ~(1<<PCIE2);      \
} while (0)
#define PS2_INT_VECT    PCINT2_vect
#endif

#endif

#endif
