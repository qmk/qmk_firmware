/**************************************************************************/
/*!
    Modified from the original Adafruit_BluefruitLE_SPI.h which was released
    under the BSD License (below).

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

#include "BLE.h"
#include "FIFO.h"

class BluefruitLE_SPI : public BLE {
   private:
    // TX
    uint8_t m_tx_buffer[SDEP_MAX_PACKETSIZE];
    uint8_t m_tx_count;

    // RX
    uint8_t m_rx_buffer[BLE_BUFSIZE];
    FIFO    m_rx_fifo;

    // Low level transportation I/O functions
    bool sendPacket(uint16_t command, const uint8_t* buffer, uint8_t count, uint8_t more_data);
    bool getPacket(sdepMsgResponse_t* p_response);

    bool getResponse(void);

   public:
    // Constructor
    BluefruitLE_SPI();

    // HW initialisation
    bool begin();

    bool setMode(uint8_t new_mode);

    // Class Print virtual function Interface
    virtual size_t write(uint8_t c);
    virtual size_t write(const uint8_t* buffer, size_t size);

    // pull in write(str) and write(buf, size) from Print
    using Print::write;

    // Class Stream interface
    virtual int  available(void);
    virtual int  read(void);
    virtual void flush(void);
    virtual int  peek(void);
};
