/*
  Modified from the original HardwareSerial.h which was released under the GPLv2
  License.

  Copyright (c) 2020 Joshua Rubin
  Copyright (c) 2013 Matthijs Kooijman
  Copyright (c) 2012 Alarus
  Copyright (c) 2010 Mark Sproul
  Copyright (c) 2006 David A. Mellis
  Copyright (c) 2006 Nicholas Zambetti
  All right reserved.

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
*/

#include <util/atomic.h>
#include <avr/interrupt.h>

#include "HardwareSerial.h"
#include "HardwareSerial_private.h"

// Actual interrupt handlers //////////////////////////////////////////////////////////////

void HardwareSerial::_tx_udr_empty_irq(void) {
    // If interrupts are enabled, there must be more data in the output
    // buffer. Send the next byte
    unsigned char c = _tx_buffer[_tx_buffer_tail];
    _tx_buffer_tail = (_tx_buffer_tail + 1) % SERIAL_TX_BUFFER_SIZE;

    UDRn = c;

    // clear the TXCn bit -- "can be cleared by writing a one to its bit
    // location". This makes sure flush() won't return until the bytes
    // actually got written. Other r/w bits are preserved, and zeroes
    // written to the rest.

    UCSRnA = ((UCSRnA) & ((1 << U2Xn) | (1 << TXCn)));

    if (_tx_buffer_head == _tx_buffer_tail) {
        // Buffer empty, so disable interrupts
        cbi(UCSRnB, UDRIEn);
    }
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long baud, uint8_t config) {
    uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
    UCSRnA                = 1 << U2Xn;

    // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
    UBRRnH = baud_setting >> 8;
    UBRRnL = baud_setting;

    _written = false;

    // set the data bits, parity, and stop bits
    UCSRnC = config;

    sbi(UCSRnB, RXENn);
    sbi(UCSRnB, TXENn);
    sbi(UCSRnB, RXCIEn);
    cbi(UCSRnB, UDRIEn);
}

void HardwareSerial::end() {
    // wait for transmission of outgoing data
    flush();

    cbi(UCSRnB, RXENn);
    cbi(UCSRnB, TXENn);
    cbi(UCSRnB, RXCIEn);
    cbi(UCSRnB, UDRIEn);

    // clear any received data
    _rx_buffer_head = _rx_buffer_tail;
}

int HardwareSerial::available(void) { return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE; }

int HardwareSerial::peek(void) {
    if (_rx_buffer_head == _rx_buffer_tail) {
        return -1;
    }

    return _rx_buffer[_rx_buffer_tail];
}

int HardwareSerial::read(void) {
    // if the head isn't ahead of the tail, we don't have any characters
    if (_rx_buffer_head == _rx_buffer_tail) {
        return -1;
    }

    unsigned char c = _rx_buffer[_rx_buffer_tail];
    _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
    return c;
}

int HardwareSerial::availableForWrite(void) {
    tx_buffer_index_t head = _tx_buffer_head;
    tx_buffer_index_t tail = _tx_buffer_tail;

    if (head >= tail) return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
    return tail - head - 1;
}

void HardwareSerial::flush() {
    // If we have never written a byte, no need to flush. This special
    // case is needed since there is no way to force the TXCn (transmit
    // complete) bit to 1 during initialization
    if (!_written) return;

    while (bit_is_set(UCSRnB, UDRIEn) || bit_is_clear(UCSRnA, TXCn)) {
        if (bit_is_clear(SREG, SREG_I) && bit_is_set(UCSRnB, UDRIEn))
            // Interrupts are globally disabled, but the DR empty
            // interrupt should be enabled, so poll the DR empty flag to
            // prevent deadlock
            if (bit_is_set(UCSRnA, UDREn)) _tx_udr_empty_irq();
    }
    // If we get here, nothing is queued anymore (DRIE is disabled) and
    // the hardware finished tranmission (TXCn is set).
}

size_t HardwareSerial::write(uint8_t c) {
    _written = true;

    // If the buffer and the data register is empty, just write the byte
    // to the data register and be done. This shortcut helps
    // significantly improve the effective datarate at high (>
    // 500kbit/s) bitrates, where interrupt overhead becomes a slowdown.
    if (_tx_buffer_head == _tx_buffer_tail && bit_is_set(UCSRnA, UDREn)) {
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
        return 1;
    }
    tx_buffer_index_t i = (_tx_buffer_head + 1) % SERIAL_TX_BUFFER_SIZE;

    // If the output buffer is full, there's nothing for it other than to
    // wait for the interrupt handler to empty it a bit
    while (i == _tx_buffer_tail) {
        if (bit_is_clear(SREG, SREG_I)) {
            // Interrupts are disabled, so we'll have to poll the data
            // register empty flag ourselves. If it is set, pretend an
            // interrupt has happened and call the handler to free up
            // space for us.
            if (bit_is_set(UCSRnA, UDREn)) _tx_udr_empty_irq();
        } else {
            // nop, the interrupt handler will free up space for us
        }
    }

    _tx_buffer[_tx_buffer_head] = c;

    // make atomic to prevent execution of ISR between setting the
    // head pointer and setting the interrupt flag resulting in buffer
    // retransmission
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        _tx_buffer_head = i;
        sbi(UCSRnB, UDRIEn);
    }

    return 1;
}

HardwareSerial Serial;

bool Serial_available() { return Serial.available(); }

ISR(USARTn_RX_vect) { Serial._rx_complete_irq(); }

ISR(USARTn_UDRE_vect) { Serial._tx_udr_empty_irq(); }
