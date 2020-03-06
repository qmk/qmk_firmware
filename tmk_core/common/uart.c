// TODO: Teensy support(ATMega32u4/AT90USB128)
// Fixed for Arduino Duemilanove ATmega168p by Jun Wako
/* UART Example for Teensy USB Development Board
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2009 PJRC.COM, LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Version 1.0: Initial Release
// Version 1.1: Add support for Teensy 2.0, minor optimizations

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
#    define UDRn UDR0
#    define UBRRn UBRR0
#    define UCSRnA UCSR0A
#    define UCSRnB UCSR0B
#    define UCSRnC UCSR0C
#    define U2Xn U2X0
#    define RXENn RXEN0
#    define TXENn TXEN0
#    define RXCIEn RXCIE0
#    define UCSZn1 UCSZ01
#    define UCSZn0 UCSZ00
#    define UDRIEn UDRIE0
#    define UDRE_vect USART_UDRE_vect
#    define RX_vect USART_RX_vect
#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega32U2__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#    define UDRn UDR1
#    define UBRRn UBRR1
#    define UCSRnA UCSR1A
#    define UCSRnB UCSR1B
#    define UCSRnC UCSR1C
#    define U2Xn U2X1
#    define RXENn RXEN1
#    define TXENn TXEN1
#    define RXCIEn RXCIE1
#    define UCSZn1 UCSZ11
#    define UCSZn0 UCSZ10
#    define UDRIEn UDRIE1
#    define UDRE_vect USART1_UDRE_vect
#    define RX_vect USART1_RX_vect
#endif

// These buffers may be any size from 2 to 256 bytes.
#define RX_BUFFER_SIZE 64
#define TX_BUFFER_SIZE 256

static volatile uint8_t tx_buffer[TX_BUFFER_SIZE];
static volatile uint8_t tx_buffer_head;
static volatile uint8_t tx_buffer_tail;
static volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t rx_buffer_head;
static volatile uint8_t rx_buffer_tail;

// Initialize the UART
void uart_init(uint32_t baud) {
    cli();
    UBRRn          = (F_CPU / 4 / baud - 1) / 2;
    UCSRnA         = (1 << U2Xn);
    UCSRnB         = (1 << RXENn) | (1 << TXENn) | (1 << RXCIEn);
    UCSRnC         = (1 << UCSZn1) | (1 << UCSZn0);
    tx_buffer_head = tx_buffer_tail = 0;
    rx_buffer_head = rx_buffer_tail = 0;
    sei();
}

// Transmit a byte
void uart_putchar(uint8_t c) {
    uint8_t i;

    i = tx_buffer_head + 1;
    if (i >= TX_BUFFER_SIZE) i = 0;
    // return immediately to avoid deadlock when interrupt is disabled(called from ISR)
    if (tx_buffer_tail == i && (SREG & (1 << SREG_I)) == 0) return;
    while (tx_buffer_tail == i)
        ;  // wait until space in buffer
    // cli();
    tx_buffer[i]   = c;
    tx_buffer_head = i;
    UCSRB          = (1 << RXENn) | (1 << TXENn) | (1 << RXCIEn) | (1 << UDRIEn);
    // sei();
}

// Receive a byte
uint8_t uart_getchar(void) {
    uint8_t c, i;

    while (rx_buffer_head == rx_buffer_tail)
        ;  // wait for character
    i = rx_buffer_tail + 1;
    if (i >= RX_BUFFER_SIZE) i = 0;
    c              = rx_buffer[i];
    rx_buffer_tail = i;
    return c;
}

// Return the number of bytes waiting in the receive buffer.
// Call this before uart_getchar() to check if it will need
// to wait for a byte to arrive.
uint8_t uart_available(void) {
    uint8_t head, tail;

    head = rx_buffer_head;
    tail = rx_buffer_tail;
    if (head >= tail) return head - tail;
    return RX_BUFFER_SIZE + head - tail;
}

// Transmit Interrupt
ISR(UDRE_vect) {
    uint8_t i;

    if (tx_buffer_head == tx_buffer_tail) {
        // buffer is empty, disable transmit interrupt
        UCSRnB = (1 << RXENn) | (1 << TXENn) | (1 << RXCIEn);
    } else {
        i = tx_buffer_tail + 1;
        if (i >= TX_BUFFER_SIZE) i = 0;
        UDR0           = tx_buffer[i];
        tx_buffer_tail = i;
    }
}

// Receive Interrupt
ISR(RX_vect) {
    uint8_t c, i;

    c = UDRn;
    i = rx_buffer_head + 1;
    if (i >= RX_BUFFER_SIZE) i = 0;
    if (i != rx_buffer_tail) {
        rx_buffer[i]   = c;
        rx_buffer_head = i;
    }
}
