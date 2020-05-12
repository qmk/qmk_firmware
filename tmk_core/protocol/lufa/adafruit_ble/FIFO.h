/**************************************************************************/
/*!
    Modified from the original Adafruit_FIFO.h which was released under
    the BSD License (below).

    Software License Agreement (BSD License)

    Copyright (c) 2020, Joshua Rubin
    Copyright (c) 2015, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#pragma once

#include <stdint.h>
#include <stdbool.h>

class FIFO {
   private:
    uint8_t*          m_buffer;     ///< buffer pointer
    uint16_t          m_depth;      ///< max items
    uint8_t           m_item_size;  ///< size of each item
    bool              m_overwritable;
    volatile uint16_t m_count;   ///< number of items in queue
    volatile uint16_t m_wr_idx;  ///< write pointer
    volatile uint16_t m_rd_idx;  ///< read pointer

   public:
    // Constructor
    FIFO(void* buffer, uint16_t depth, uint8_t item_size, bool overwrite);

    void clear(void);
    bool peek(void* buffer);
    bool peekAt(uint16_t position, void* p_buffer);

    bool     write(void const* item);
    uint16_t write_n(void const* data, uint16_t n);

    bool     read(void* buffer);
    uint16_t read_n(void* buffer, uint16_t n);

    inline bool     empty(void) { return m_count == 0; }
    inline bool     full(void) { return m_count == m_depth; }
    inline uint16_t count(void) { return m_count; }
    inline uint16_t remaining(void) { return m_depth - m_count; }
};
