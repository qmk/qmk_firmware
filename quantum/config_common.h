#ifndef CONFIG_DEFINITIONS_H
#define CONFIG_DEFINITIONS_H

#define B0 0x30
#define B1 0x31
#define B2 0x32
#define B3 0x33
#define B4 0x34
#define B5 0x35
#define B6 0x36
#define B7 0x37
#define C0 0x60
#define C1 0x61
#define C2 0x62
#define C3 0x63
#define C4 0x64
#define C5 0x65
#define C6 0x66
#define C7 0x67
#define D0 0x90
#define D1 0x91
#define D2 0x92
#define D3 0x93
#define D4 0x94
#define D5 0x95
#define D6 0x96
#define D7 0x97
#define E0 0xC0
#define E1 0xC1
#define E2 0xC2
#define E3 0xC3
#define E4 0xC4
#define E5 0xC5
#define E6 0xC6
#define E7 0xC7
#define F0 0xF0
#define F1 0xF1
#define F2 0xF2
#define F3 0xF3
#define F4 0xF4
#define F5 0xF5
#define F6 0xF6
#define F7 0xF7

#define COL2ROW 0x0
#define ROW2COL 0x1

#ifdef BLUETOOTH_ENABLE
#ifdef __AVR_ATmega32U4__
    #define SERIAL_UART_BAUD       9600
    #define SERIAL_UART_DATA       UDR1
    #define SERIAL_UART_UBRR       ((F_CPU/(16UL*SERIAL_UART_BAUD))-1)
    #define SERIAL_UART_RXD_VECT   USART1_RX_vect
    #define SERIAL_UART_TXD_READY  (UCSR1A&(1<<UDRE1))
    #define SERIAL_UART_INIT()     do { \
        UBRR1L = (uint8_t) SERIAL_UART_UBRR;       /* baud rate */ \
        UBRR1H = (uint8_t) (SERIAL_UART_UBRR>>8);  /* baud rate */ \
        UCSR1B = (1<<TXEN1);                /* TX: enable */ \
        UCSR1C = (0<<UPM11) | (0<<UPM10) | /* parity: none(00), even(01), odd(11) */ \
                 (0<<UCSZ12) | (1<<UCSZ11) | (1<<UCSZ10); /* data-8bit(011) */ \
		sei(); \
    } while(0)
#else
#   error "USART configuration is needed."
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
