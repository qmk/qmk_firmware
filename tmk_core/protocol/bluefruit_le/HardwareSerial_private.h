/*
  HardwareSerial_private.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
*/

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
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

#ifndef cbi
#    define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#    define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Constructors ////////////////////////////////////////////////////////////////

HardwareSerial::HardwareSerial() : _rx_buffer_head(0), _rx_buffer_tail(0), _tx_buffer_head(0), _tx_buffer_tail(0) {}

// Actual interrupt handlers //////////////////////////////////////////////////////////////

void HardwareSerial::_rx_complete_irq(void) {
    if (bit_is_clear(UCSRnA, UPEn)) {
        // No Parity error, read byte and store it in the buffer if there is
        // room
        unsigned char     c = UDRn;
        rx_buffer_index_t i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;

        // if we should be storing the received character into the location
        // just before the tail (meaning that the head would advance to the
        // current location of the tail), we're about to overflow the buffer
        // and so we don't write the character or advance the head.
        if (i != _rx_buffer_tail) {
            _rx_buffer[_rx_buffer_head] = c;
            _rx_buffer_head             = i;
        }
    } else {
        // Parity error, read byte but discard it
        UDRn;
    };
}

// #endif // whole file
