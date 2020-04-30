/*
  Modified from the original HardwareSerial.h which was released under the GPLv2
  License.

  Copyright (c) 2020 Joshua Rubin
  Copyright (c) 2013 by Matthijs Kooijman
  Copyright (c) 2012 by Alarus
  Copyright (c) 2010 by Mark Sproul
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

#pragma once

#include <inttypes.h>

#include "Stream.h"

/*
// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.
// NOTE: a "power of 2" buffer size is reccomended to dramatically
//       optimize all the modulo operations for ring buffers.
// WARNING: When buffer sizes are increased to > 256, the buffer index
// variables are automatically increased in size, but the extra
// atomicity guards needed for that are not implemented. This will
// often work, but occasionally a race condition can occur that makes
// Serial behave erratically. See https://github.com/arduino/Arduino/issues/2405
*/
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64
typedef uint8_t tx_buffer_index_t;
typedef uint8_t rx_buffer_index_t;

// Define config for Serial.begin(baud, config);
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

class HardwareSerial : public Stream {
   protected:
    // Has any byte been written to the UART since begin()
    bool _written;

    volatile rx_buffer_index_t _rx_buffer_head;
    volatile rx_buffer_index_t _rx_buffer_tail;
    volatile tx_buffer_index_t _tx_buffer_head;
    volatile tx_buffer_index_t _tx_buffer_tail;

    // Don't put any members after these buffers, since only the first
    // 32 bytes of this struct can be accessed quickly using the ldd
    // instruction.
    unsigned char _rx_buffer[64];
    unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

   public:
    inline HardwareSerial();
    void           begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
    void           begin(unsigned long, uint8_t);
    void           end();
    virtual int    available(void);
    virtual int    peek(void);
    virtual int    read(void);
    virtual int    availableForWrite(void);
    virtual void   flush(void);
    virtual size_t write(uint8_t);
    inline size_t  write(unsigned long n) { return write((uint8_t)n); }
    inline size_t  write(long n) { return write((uint8_t)n); }
    inline size_t  write(unsigned int n) { return write((uint8_t)n); }
    inline size_t  write(int n) { return write((uint8_t)n); }
    using Print::write;  // pull in write(str) and write(buf, size) from Print

    // Interrupt handlers - Not intended to be called externally
    inline void _rx_complete_irq(void);
    void        _tx_udr_empty_irq(void);
};

extern HardwareSerial Serial;
