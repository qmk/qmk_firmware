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

#if defined(__AVR_AT90USB162__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#    define UDRn UDR1
#    define UBRRnL UBRR1L
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
#    define USARTn_UDRE_vect USART1_UDRE_vect
#    define USARTn_RX_vect USART1_RX_vect
#elif defined(__AVR_ATmega32A__)
#    define UDRn UDR
#    define UBRRnL UBRRL
#    define UCSRnA UCSRA
#    define UCSRnB UCSRB
#    define UCSRnC UCSRC
#    define U2Xn U2X
#    define RXENn RXEN
#    define TXENn TXEN
#    define RXCIEn RXCIE
#    define UCSZn1 UCSZ1
#    define UCSZn0 UCSZ0
#    define UDRIEn UDRIE
#    define USARTn_UDRE_vect USART_UDRE_vect
#    define USARTn_RX_vect USART_RX_vect
#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#    define UDRn UDR0
#    define UBRRnL UBRR0L
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
#    define USARTn_UDRE_vect USART_UDRE_vect
#    define USARTn_RX_vect USART_RX_vect
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
    UBRRnL         = (F_CPU / 4 / baud - 1) / 2;
    UCSRnA         = (1 << U2Xn);
    UCSRnB         = (1 << RXENn) | (1 << TXENn) | (1 << RXCIEn);
    UCSRnC         = (1 << UCSZn1) | (1 << UCSZn0);
    tx_buffer_head = tx_buffer_tail = 0;
    rx_buffer_head = rx_buffer_tail = 0;
    sei();
}

// Transmit a byte
void uart_write(uint8_t data) {
    uint8_t i;

    i = tx_buffer_head + 1;
    if (i >= TX_BUFFER_SIZE) i = 0;
    // return immediately to avoid deadlock when interrupt is disabled(called from ISR)
    if (tx_buffer_tail == i && (SREG & (1 << SREG_I)) == 0) return;
    while (tx_buffer_tail == i)
        ;  // wait until space in buffer
    // cli();
    tx_buffer[i]   = data;
    tx_buffer_head = i;
    UCSRnB         = (1 << RXENn) | (1 << TXENn) | (1 << RXCIEn) | (1 << UDRIEn);
    // sei();
}

// Receive a byte
uint8_t uart_read(void) {
    uint8_t data, i;

    while (rx_buffer_head == rx_buffer_tail)
        ;  // wait for character
    i = rx_buffer_tail + 1;
    if (i >= RX_BUFFER_SIZE) i = 0;
    data           = rx_buffer[i];
    rx_buffer_tail = i;
    return data;
}

void uart_transmit(const uint8_t *data, uint16_t length) {
    for (uint16_t i = 0; i < length; i++) {
        uart_write(data[i]);
    }
}

void uart_receive(uint8_t *data, uint16_t length) {
    for (uint16_t i = 0; i < length; i++) {
        data[i] = uart_read();
    }
}

// Return whether the number of bytes waiting in the receive buffer is nonzero.
// Call this before uart_read() to check if it will need
// to wait for a byte to arrive.
bool uart_available(void) {
    uint8_t head, tail;

    head = rx_buffer_head;
    tail = rx_buffer_tail;
    if (head >= tail) return (head - tail) > 0;
    return (RX_BUFFER_SIZE + head - tail) > 0;
}

// Transmit Interrupt
ISR(USARTn_UDRE_vect) {
    uint8_t i;

    if (tx_buffer_head == tx_buffer_tail) {
        // buffer is empty, disable transmit interrupt
        UCSRnB = (1 << RXENn) | (1 << TXENn) | (1 << RXCIEn);
    } else {
        i = tx_buffer_tail + 1;
        if (i >= TX_BUFFER_SIZE) i = 0;
        UDRn           = tx_buffer[i];
        tx_buffer_tail = i;
    }
}

// Receive Interrupt
ISR(USARTn_RX_vect) {
    uint8_t c, i;

    c = UDRn;
    i = rx_buffer_head + 1;
    if (i >= RX_BUFFER_SIZE) i = 0;
    if (i != rx_buffer_tail) {
        rx_buffer[i]   = c;
        rx_buffer_head = i;
    }
}
