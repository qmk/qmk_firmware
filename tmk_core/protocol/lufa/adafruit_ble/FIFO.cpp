/**************************************************************************/
/*!
    Modified from the original Adafruit_FIFO.cpp which was released under
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

#include "FIFO.h"
#include <string.h>

/******************************************************************************/
/*!
    @brief  Constructor

    @param[in] buffer
               Memory location to store data
    @param[in] depth
               Maximum number of items can be hold in buffer
    @param[in] item_size
               Number of bytes of each item
    @param[in] overwrite
               Should the buffer is overwitten to the first item when it is full
*/
/******************************************************************************/
FIFO::FIFO(void* buffer, uint16_t depth, uint8_t item_size, bool overwrite) {
    m_buffer       = (uint8_t*)buffer;
    m_depth        = depth;
    m_item_size    = item_size;
    m_overwritable = overwrite;

    m_count = m_wr_idx = m_rd_idx = 0;
}

/******************************************************************************/
/*!
    @brief  Clear the FIFO
*/
/******************************************************************************/
void FIFO::clear(void) { m_rd_idx = m_wr_idx = m_count = 0; }

/******************************************************************************/
/*!
    @brief  Write an item to the FIFO

    @param[in] item
               Memory address of the item
*/
/******************************************************************************/
bool FIFO::write(void const* item) {
    if (full() && !m_overwritable) return false;

    memcpy(m_buffer + (m_wr_idx * m_item_size), item, m_item_size);

    m_wr_idx = (m_wr_idx + 1) % m_depth;

    if (full()) {
        m_rd_idx = m_wr_idx;  // keep the full state (rd == wr && len = size)
    } else {
        m_count++;
    }

    return true;
}

/******************************************************************************/
/*!
    @brief  Write array of items to the FIFO

    @param[in] data
               Memory address of the item's array
    @param[in] n
               Number of items to write

    @return    Number of written items
*/
/******************************************************************************/
uint16_t FIFO::write_n(void const* data, uint16_t n) {
    if (n == 0) return 0;

    uint8_t* buf = (uint8_t*)data;

    uint16_t len = 0;
    while ((len < n) && write(buf)) {
        len++;
        buf += m_item_size;
    }

    return len;
}

/******************************************************************************/
/*!
    @brief  Read an item from FIFO

    @param[in] buffer
               Memory address to store item
*/
/******************************************************************************/
bool FIFO::read(void* buffer) {
    if (empty()) return false;

    memcpy(buffer, m_buffer + (m_rd_idx * m_item_size), m_item_size);
    m_rd_idx = (m_rd_idx + 1) % m_depth;
    m_count--;

    return true;
}

/******************************************************************************/
/*!
    @brief  Read multiple items to an array

    @param[in] buffer
               Memory address of the item's array
    @param[in] n
               Number of items to read

    @return    Number of read items
*/
/******************************************************************************/

uint16_t FIFO::read_n(void* buffer, uint16_t n) {
    if (n == 0) return 0;

    uint8_t* buf = (uint8_t*)buffer;

    uint16_t len = 0;
    while ((len < n) && read(buf)) {
        len++;
        buf += m_item_size;
    }

    return len;
}

/******************************************************************************/
/*!
    @brief  Read an item without removing it from the FIFO

    @param[in] buffer
               Memory address to store item
*/
/******************************************************************************/
bool FIFO::peek(void* buffer) {
    if (empty()) return false;

    memcpy(buffer, m_buffer + (m_rd_idx * m_item_size), m_item_size);

    return true;
}

/******************************************************************************/
/*!
    @brief  Read an item without removing it from the FIFO at the specific index

    @param[in] position
               Position to read from in the FIFO buffer

    @param[in] buffer
               Memory address to store item
*/
/******************************************************************************/
bool FIFO::peekAt(uint16_t position, void* p_buffer) {
    if (empty() || (position >= m_count)) return false;

    uint16_t index = (m_rd_idx + position) % m_depth;  // rd_idx is position=0
    memcpy(p_buffer, m_buffer + (index * m_item_size), m_item_size);

    return true;
}
