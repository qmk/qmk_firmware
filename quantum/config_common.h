#ifndef CONFIG_DEFINITIONS_H
#define CONFIG_DEFINITIONS_H

/* diode directions */
#define COL2ROW 0
#define ROW2COL 1
/* I/O pins */
#define B0 { .input_addr = 3, .bit = 0 }
#define B1 { .input_addr = 3, .bit = 1 }
#define B2 { .input_addr = 3, .bit = 2 }
#define B3 { .input_addr = 3, .bit = 3 }
#define B4 { .input_addr = 3, .bit = 4 }
#define B5 { .input_addr = 3, .bit = 5 }
#define B6 { .input_addr = 3, .bit = 6 }
#define B7 { .input_addr = 3, .bit = 7 }
#define C0 { .input_addr = 6, .bit = 0 }
#define C1 { .input_addr = 6, .bit = 1 }
#define C2 { .input_addr = 6, .bit = 2 }
#define C3 { .input_addr = 6, .bit = 3 }
#define C4 { .input_addr = 6, .bit = 4 }
#define C5 { .input_addr = 6, .bit = 5 }
#define C6 { .input_addr = 6, .bit = 6 }
#define C7 { .input_addr = 6, .bit = 7 }
#define D0 { .input_addr = 9, .bit = 0 }
#define D1 { .input_addr = 9, .bit = 1 }
#define D2 { .input_addr = 9, .bit = 2 }
#define D3 { .input_addr = 9, .bit = 3 }
#define D4 { .input_addr = 9, .bit = 4 }
#define D5 { .input_addr = 9, .bit = 5 }
#define D6 { .input_addr = 9, .bit = 6 }
#define D7 { .input_addr = 9, .bit = 7 }
#define E0 { .input_addr = 0xC, .bit = 0 }
#define E1 { .input_addr = 0xC, .bit = 1 }
#define E2 { .input_addr = 0xC, .bit = 2 }
#define E3 { .input_addr = 0xC, .bit = 3 }
#define E4 { .input_addr = 0xC, .bit = 4 }
#define E5 { .input_addr = 0xC, .bit = 5 }
#define E6 { .input_addr = 0xC, .bit = 6 }
#define E7 { .input_addr = 0xC, .bit = 7 }
#define F0 { .input_addr = 0xF, .bit = 0 }
#define F1 { .input_addr = 0xF, .bit = 1 }
#define F2 { .input_addr = 0xF, .bit = 2 }
#define F3 { .input_addr = 0xF, .bit = 3 }
#define F4 { .input_addr = 0xF, .bit = 4 }
#define F5 { .input_addr = 0xF, .bit = 5 }
#define F6 { .input_addr = 0xF, .bit = 6 }
#define F7 { .input_addr = 0xF, .bit = 7 }

/* USART configuration */
#ifdef BLUETOOTH_ENABLE
#   ifdef __AVR_ATmega32U4__
#      define SERIAL_UART_BAUD 9600
#      define SERIAL_UART_DATA UDR1
#      define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#      define SERIAL_UART_RXD_VECT USART1_RX_vect
#      define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#      define SERIAL_UART_INIT() do { \
            /* baud rate */ \
            UBRR1L = SERIAL_UART_UBRR; \
            /* baud rate */ \
            UBRR1H = SERIAL_UART_UBRR >> 8; \
            /* enable TX */ \
            UCSR1B = _BV(TXEN1); \
            /* 8-bit data */ \
            UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
            sei(); \
        } while(0)
#   else
#       error "USART configuration is needed."
#endif

// I'm fairly sure these aren't needed, but oh well - Jack

/*
 * PS/2 Interrupt configuration
 */
#ifdef PS2_USE_INT
/* uses INT1 for clock line(ATMega32U4) */
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   1

#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    0

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
#endif

/*
 * PS/2 Busywait configuration
 */
#ifdef PS2_USE_BUSYWAIT
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   1

#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    0
#endif

#endif

#endif
