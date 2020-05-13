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
#include <util/atomic.h>

#include "uart.h"

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#    define UDRn UDR0
#    define UBRRnL UBRR0L
#    define UBRRnH UBRR0H
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
#    define UPEn UPE0
#    define TXCn TXC0
#    define UDREn UDRE0
#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega32U2__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#    define UDRn UDR1
#    define UBRRnL UBRR1L
#    define UBRRnH UBRR1H
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
#    define UPEn UPE1
#    define TXCn TXC1
#    define UDREn UDRE1
#elif defined(__AVR_ATmega32A__)
#    define UDRn UDR
#    define UBRRnL UBRRL
#    define UBRRnH UBRRH
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
#    define UPEn UPE
#    define TXCn TXC
#    define UDREn UDRE
#endif

// These buffers may be any size from 2 to 256 bytes.
#define RX_BUFFER_SIZE 64
#define TX_BUFFER_SIZE 256

#ifndef cbi
#    define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#    define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

static volatile uint8_t tx_buffer[TX_BUFFER_SIZE];
static volatile uint8_t tx_buffer_head = 0;
static volatile uint8_t tx_buffer_tail = 0;
static volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t rx_buffer_head = 0;
static volatile uint8_t rx_buffer_tail = 0;

static uint8_t written = 0;

// Initialize the UART
void uart_init(uint32_t baud) {
    uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
    UCSRnA                = 1 << U2Xn;

    // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
    UBRRnH = baud_setting >> 8;
    UBRRnL = baud_setting;

    // set the data bits, parity, and stop bits
    UCSRnC = (1 << UCSZn1) | (1 << UCSZn0);

    sbi(UCSRnB, RXENn);
    sbi(UCSRnB, TXENn);
    sbi(UCSRnB, RXCIEn);
    cbi(UCSRnB, UDRIEn);
}

inline static void tx_udr_empty_irq(void) {
    // If interrupts are enabled, there must be more data in the output
    // buffer. Send the next byte
    unsigned char c = tx_buffer[tx_buffer_tail];
    tx_buffer_tail  = (tx_buffer_tail + 1) % TX_BUFFER_SIZE;

    UDRn = c;

    // clear the TXCn bit -- "can be cleared by writing a one to its bit
    // location". This makes sure flush() won't return until the bytes
    // actually got written. Other r/w bits are preserved, and zeroes
    // written to the rest.

    UCSRnA = ((UCSRnA) & ((1 << U2Xn) | (1 << TXCn)));

    if (tx_buffer_head == tx_buffer_tail) {
        // Buffer empty, so disable interrupts
        cbi(UCSRnB, UDRIEn);
    }
}

// Transmit a byte
void uart_putchar(uint8_t c) {
    written = 1;

    // If the buffer and the data register is empty, just write the byte
    // to the data register and be done. This shortcut helps
    // significantly improve the effective datarate at high (>
    // 500kbit/s) bitrates, where interrupt overhead becomes a slowdown.
    if (tx_buffer_head == tx_buffer_tail && bit_is_set(UCSRnA, UDREn)) {
        // If TXCn is cleared before writing UDR and the previous byte
        // completes before writing to UDR, TXCn will be set but a byte
        // is still being transmitted causing flush() to return too soon.
        // So writing UDR must happen first.
        // Writing UDR and clearing TC must be done atomically, otherwise
        // interrupts might delay the TXCn clear so the byte written to UDR
        // is transmitted (setting TXCn) before clearing TXCn. Then TXCn will
        // be cleared when no bytes are left, causing flush() to hang
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            UDRn   = c;
            UCSRnA = ((UCSRnA) & ((1 << U2Xn) | (1 << TXCn)));
        }
        return;
    }
    uint8_t i = (tx_buffer_head + 1) % TX_BUFFER_SIZE;

    // If the output buffer is full, there's nothing for it other than to
    // wait for the interrupt handler to empty it a bit
    while (i == tx_buffer_tail) {
        if (bit_is_clear(SREG, SREG_I)) {
            // Interrupts are disabled, so we'll have to poll the data
            // register empty flag ourselves. If it is set, pretend an
            // interrupt has happened and call the handler to free up
            // space for us.
            if (bit_is_set(UCSRnA, UDREn)) tx_udr_empty_irq();
        } else {
            // nop, the interrupt handler will free up space for us
        }
    }

    tx_buffer[tx_buffer_head] = c;

    // make atomic to prevent execution of ISR between setting the
    // head pointer and setting the interrupt flag resulting in buffer
    // retransmission
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        tx_buffer_head = i;
        sbi(UCSRnB, UDRIEn);
    }
}

// Receive a byte
uint8_t uart_getchar(void) {
    while (rx_buffer_head == rx_buffer_tail)
        ;  // wait for character

    unsigned char c = rx_buffer[rx_buffer_tail];
    rx_buffer_tail  = (rx_buffer_tail + 1) % RX_BUFFER_SIZE;
    return c;
}

void uart_flush(void) {
    // If we have never written a byte, no need to flush. This special
    // case is needed since there is no way to force the TXCn (transmit
    // complete) bit to 1 during initialization
    if (!written) return;

    while (bit_is_set(UCSRnB, UDRIEn) || bit_is_clear(UCSRnA, TXCn)) {
        if (bit_is_clear(SREG, SREG_I) && bit_is_set(UCSRnB, UDRIEn))
            // Interrupts are globally disabled, but the DR empty
            // interrupt should be enabled, so poll the DR empty flag to
            // prevent deadlock
            if (bit_is_set(UCSRnA, UDREn)) tx_udr_empty_irq();
    }
    // If we get here, nothing is queued anymore (DRIE is disabled) and
    // the hardware finished tranmission (TXCn is set).
}

uint8_t uart_peek(void) {
    if (rx_buffer_head == rx_buffer_tail) return -1;
    return rx_buffer[rx_buffer_tail];
}

// Return the number of bytes waiting in the receive buffer.
// Call this before uart_getchar() to check if it will need
// to wait for a byte to arrive.
uint8_t uart_available(void) { return (RX_BUFFER_SIZE + rx_buffer_head - rx_buffer_tail) % RX_BUFFER_SIZE; }

// Transmit Interrupt
ISR(USARTn_UDRE_vect) { tx_udr_empty_irq(); }

// Receive Interrupt
ISR(USARTn_RX_vect) {
    if (bit_is_clear(UCSRnA, UPEn)) {
        // No Parity error, read byte and store it in the buffer if there is
        // room
        unsigned char c = UDRn;
        uint8_t       i = (rx_buffer_head + 1) % RX_BUFFER_SIZE;

        // if we should be storing the received character into the location
        // just before the tail (meaning that the head would advance to the
        // current location of the tail), we're about to overflow the buffer
        // and so we don't write the character or advance the head.
        if (i != rx_buffer_tail) {
            rx_buffer[rx_buffer_head] = c;
            rx_buffer_head            = i;
        }
    } else {
        // Parity error, read byte but discard it
        UDRn;
    };
}
