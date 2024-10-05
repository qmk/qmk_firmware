#pragma once


#ifdef PS2_DRIVER_USART
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

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
