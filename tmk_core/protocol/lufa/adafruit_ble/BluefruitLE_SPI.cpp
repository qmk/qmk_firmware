/**************************************************************************/
/*!
    Modified from the original Adafruit_BluefruitLE_SPI.cpp which was released
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

#include "BluefruitLE_SPI.h"
#include "quantum.h"
#include "spi_master.h"
#include <stdlib.h>

#ifndef min
#    define min(a, b) ((a) < (b) ? (a) : (b))
#endif

#define SPI_IGNORED_BYTE 0xFEu  /**< SPI default character. Character clocked out in case of an ignored transaction. */
#define SPI_OVERREAD_BYTE 0xFFu /**< SPI over-read character. Character clocked out after an over-read of the transmit buffer. */
#define SPI_DEFAULT_DELAY_US 50

#define memclr(buffer, size) memset(buffer, 0, size)

#ifndef AdafruitBleResetPin
#    define AdafruitBleResetPin D4
#endif

#ifndef AdafruitBleCSPin
#    define AdafruitBleCSPin B4
#endif

#ifndef AdafruitBleIRQPin
#    define AdafruitBleIRQPin E6
#endif

#ifndef AdafruitBleSpiClockSpeed
#    define AdafruitBleSpiClockSpeed 4000000UL  // SCK frequency
#endif

#define SCK_DIVISOR (F_CPU / AdafruitBleSpiClockSpeed)

#define lowByte(w) ((uint8_t)((w)&0xff))
#define highByte(w) ((uint8_t)((w) >> 8))

unsigned int makeWord(unsigned int w) { return w; }
unsigned int makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }
#define word(...) makeWord(__VA_ARGS__)

/******************************************************************************/
/*!
    @brief Instantiates a new instance of the BluefruitLE_SPI class
*/
/******************************************************************************/
BluefruitLE_SPI::BluefruitLE_SPI() : m_rx_fifo(m_rx_buffer, sizeof(m_rx_buffer), 1, true) { m_tx_count = 0; }

/******************************************************************************/
/*!
    @brief Initialize the HW to enable communication with the BLE module

    @return Returns 'true' if everything initialised correctly, otherwise
            'false' if there was a problem during HW initialisation. If
            'irqPin' is not a HW interrupt pin false will be returned.
*/
/******************************************************************************/

static bool spiInitialized = false;

bool BluefruitLE_SPI::begin() {
    _verbose = AdafruitBleVerbose;

    setPinInput(AdafruitBleIRQPin);

    // Set CS pin to output and de-assert by default
    setPinOutput(AdafruitBleCSPin);
    writePinHigh(AdafruitBleCSPin);

    if (!spiInitialized) {
        spi_init();
        spiInitialized = true;
    }

    // use hardware reset
    // pull the RST to GND for 10 ms
    setPinOutput(AdafruitBleResetPin);
    writePinHigh(AdafruitBleResetPin);
    writePinLow(AdafruitBleResetPin);
    wait_ms(10);
    writePinHigh(AdafruitBleResetPin);

    // Bluefruit takes 1 second to reboot
    wait_ms(1000);

    return true;
}

bool BluefruitLE_SPI::setMode(uint8_t new_mode) {
    // invalid mode
    if (!(new_mode == BLUEFRUIT_MODE_COMMAND || new_mode == BLUEFRUIT_MODE_DATA)) return false;

    // Already in the wanted mode
    if (_mode == new_mode) return true;

    // SPI use different SDEP command when in DATA/COMMAND mode.
    // --> does not switch using +++ command
    _mode = new_mode;

    // If we're entering DATA mode, flush any old response, so that it isn't
    // interpreted as incoming UART data
    if (_mode == BLUEFRUIT_MODE_DATA) flush();

    return true;
}

/******************************************************************************/
/*!
    @brief  Send out an packet with data in m_tx_buffer

    @param[in]  more_data
                More Data bitfield, 0 indicates this is not end of transfer yet
*/
/******************************************************************************/
bool BluefruitLE_SPI::sendPacket(uint16_t command, const uint8_t *buf, uint8_t count, uint8_t more_data) {
    // flush old response before sending the new command, but only if we're *not*
    // in DATA mode, as the RX FIFO may containg incoming UART data that hasn't
    // been read yet
    if (more_data == 0 && _mode != BLUEFRUIT_MODE_DATA) flush();

    sdepMsgCommand_t msgCmd;

    msgCmd.header.msg_type    = SDEP_MSGTYPE_COMMAND;
    msgCmd.header.cmd_id_high = highByte(command);
    msgCmd.header.cmd_id_low  = lowByte(command);
    msgCmd.header.length      = count;
    msgCmd.header.more_data   = (count == SDEP_MAX_PACKETSIZE) ? more_data : 0;

    // Copy payload
    if (buf != NULL && count > 0) memcpy(msgCmd.payload, buf, count);

    spi_start(AdafruitBleCSPin, false, 0, SCK_DIVISOR);

    uint32_t tt = timer_read32();

    // Bluefruit may not be ready
    while ((spi_write(msgCmd.header.msg_type) == SPI_IGNORED_BYTE) && (timer_elapsed32(tt) < _timeout)) {
        // Disable & Re-enable CS with a bit of delay for Bluefruit to ready itself
        spi_stop();
        wait_us(SPI_DEFAULT_DELAY_US);
        spi_start(AdafruitBleCSPin, false, 0, SCK_DIVISOR);
    }

    bool result = (timer_elapsed32(tt) < _timeout);
    if (result) {
        // transfer the rest of the data
        spi_transmit((((uint8_t *)&msgCmd) + 1), sizeof(sdepMsgHeader_t) + count - 1);
    }

    spi_stop();

    return result;
}

/******************************************************************************/
/*!
    @brief  Print API. Either buffer the data internally or send it to bus
            if possible. \r and \n are command terminators and will force the
            packet to be sent to the Bluefruit LE module.

    @param[in]  c
                Character to send
*/
/******************************************************************************/
size_t BluefruitLE_SPI::write(uint8_t c) {
    if (_mode == BLUEFRUIT_MODE_DATA) {
        sendPacket(SDEP_CMDTYPE_BLE_UARTTX, &c, 1, 0);
        getResponse();
        return 1;
    }

    // Following code handle BLUEFRUIT_MODE_COMMAND

    // Final packet due to \r or \n terminator
    if (c == '\r' || c == '\n') {
        if (m_tx_count > 0) {
            sendPacket(SDEP_CMDTYPE_AT_WRAPPER, m_tx_buffer, m_tx_count, 0);
            m_tx_count = 0;
        }
    } else if (m_tx_count == SDEP_MAX_PACKETSIZE) {
        // More than max packet buffered --> send with more_data = 1
        sendPacket(SDEP_CMDTYPE_AT_WRAPPER, m_tx_buffer, m_tx_count, 1);

        m_tx_buffer[0] = c;
        m_tx_count     = 1;
    } else {
        // Not enough data, continue to buffer
        m_tx_buffer[m_tx_count++] = c;
    }

    if (_verbose) dprintf("%c", (char)c);

    return 1;
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
size_t BluefruitLE_SPI::write(const uint8_t *buf, size_t size) {
    if (_mode == BLUEFRUIT_MODE_DATA) {
        size_t remain = size;
        while (remain) {
            size_t len = min(remain, SDEP_MAX_PACKETSIZE);
            remain -= len;

            sendPacket(SDEP_CMDTYPE_BLE_UARTTX, buf, (uint8_t)len, remain ? 1 : 0);
            buf += len;
        }

        getResponse();

        return size;
    }

    // Command mode
    size_t n = 0;
    while (size--) {
        n += write(*buf++);
    }
    return n;
}

/******************************************************************************/
/*!
    @brief Check if the response from the previous command is ready

    @return 'true' if a response is ready, otherwise 'false'
*/
/******************************************************************************/
int BluefruitLE_SPI::available(void) {
    if (!m_rx_fifo.empty()) {
        return m_rx_fifo.count();
    }

    if (_mode == BLUEFRUIT_MODE_DATA) {
        // DATA Mode: query for BLE UART data
        sendPacket(SDEP_CMDTYPE_BLE_UARTRX, NULL, 0, 0);

        // Waiting to get response from Bluefruit
        getResponse();

        return m_rx_fifo.count();
    }

    return readPin(AdafruitBleIRQPin);
}

/******************************************************************************/
/*!
    @brief Get a byte from response data, perform SPI transaction if needed

    @return -1 if no data is available
*/
/******************************************************************************/
int BluefruitLE_SPI::read(void) {
    uint8_t ch;

    // try to grab from buffer first...
    if (!m_rx_fifo.empty()) {
        m_rx_fifo.read(&ch);
        return (int)ch;
    }

    if (_mode == BLUEFRUIT_MODE_DATA) {
        // DATA Mode: query for BLE UART data
        sendPacket(SDEP_CMDTYPE_BLE_UARTRX, NULL, 0, 0);

        // Waiting to get response from Bluefruit
        getResponse();
    } else {
        // COMMAND Mode: Only read data from Bluefruit if IRQ is raised
        if (readPin(AdafruitBleIRQPin)) getResponse();
    }

    return m_rx_fifo.read(&ch) ? ((int)ch) : EOF;
}

/******************************************************************************/
/*!
    @brief Get a byte from response without removing it, perform SPI transaction
           if needed

    @return -1 if no data is available
*/
/******************************************************************************/
int BluefruitLE_SPI::peek(void) {
    uint8_t ch;

    // try to grab from buffer first...
    if (m_rx_fifo.peek(&ch)) {
        return (int)ch;
    }

    if (_mode == BLUEFRUIT_MODE_DATA) {
        // DATA Mode: query for BLE UART data
        sendPacket(SDEP_CMDTYPE_BLE_UARTRX, NULL, 0, 0);

        // Waiting to get response from Bluefruit
        getResponse();
    } else {
        // Read data from Bluefruit if possible
        if (readPin(AdafruitBleIRQPin)) getResponse();
    }

    return m_rx_fifo.peek(&ch) ? ch : EOF;
}

/******************************************************************************/
/*!
    @brief Flush current response data in the internal FIFO

    @return -1 if no data is available
*/
/******************************************************************************/
void BluefruitLE_SPI::flush(void) { m_rx_fifo.clear(); }

/******************************************************************************/
/*!
    @brief  Try to perform an full AT response transfer from Bluefruit, or execute
            as many SPI transaction as internal FIFO can hold up.

    @note   If verbose is enabled, all the received data will be print to Serial

    @return
      - true  : if succeeded
      - false : if failed
*/
/******************************************************************************/
bool BluefruitLE_SPI::getResponse(void) {
    // Try to read data from Bluefruit if there is enough room in the fifo
    while (m_rx_fifo.remaining() >= SDEP_MAX_PACKETSIZE) {
        // Get a SDEP packet
        sdepMsgResponse_t msg_response;
        memclr(&msg_response, sizeof(sdepMsgResponse_t));

        if (!getPacket(&msg_response)) return false;

        // Write to fifo
        if (msg_response.header.length > 0) {
            m_rx_fifo.write_n(msg_response.payload, msg_response.header.length);
        }

        // No more packet data
        if (!msg_response.header.more_data) break;
    }

    return true;
}

/******************************************************************************/
/*!
    @brief      Perform a single SPI SDEP transaction and is used by getReponse to
                get a full response composed of multiple packets.

    @param[in]  buf
                Memory location where payload is copied to

    @return number of bytes in SDEP payload
*/
/******************************************************************************/
bool BluefruitLE_SPI::getPacket(sdepMsgResponse_t *p_response) {
    // Wait until IRQ is asserted, double timeout since some commands take long time to start responding
    uint32_t tt = timer_read32();

    while (!readPin(AdafruitBleIRQPin)) {
        if (timer_elapsed32(tt) > 2 * _timeout) return false;
    }

    sdepMsgHeader_t *p_header = &p_response->header;

    spi_start(AdafruitBleCSPin, false, 0, SCK_DIVISOR);

    tt = timer_read32();

    do {
        if (timer_elapsed32(tt) > _timeout) break;

        p_header->msg_type = spi_read();

        switch (p_header->msg_type) {
            case SPI_IGNORED_BYTE:
                // Bluefruit may not be ready
                //
                // Disable & Re-enable CS with a bit of delay for Bluefruit to
                // ready itself
                //
                // intentional fallthrough, no break
            case SPI_OVERREAD_BYTE:
                // IRQ may not be pulled down by Bluefruit when returning all
                // data in previous transfer. This could happen when Arduino MCU
                // is running at fast rate comparing to Bluefruit's MCU, causing
                // an SPI_OVERREAD_BYTE to be returned at stage.
                //
                // Walkaround: Disable & Re-enable CS with a bit of delay and
                // keep waiting
                // TODO IRQ is supposed to be OFF then ON, it is better to use
                // GPIO trigger interrupt.
                spi_stop();
                wait_us(SPI_DEFAULT_DELAY_US);
                spi_start(AdafruitBleCSPin, false, 0, SCK_DIVISOR);
        }
    } while (p_header->msg_type == SPI_IGNORED_BYTE || p_header->msg_type == SPI_OVERREAD_BYTE);

    bool result = false;

    // Not a loop, just a way to avoid goto with error handling
    do {
        // Look for the header
        // note that we should always get the right header at this point, and not doing so will really mess up things.
        while (p_header->msg_type != SDEP_MSGTYPE_RESPONSE && p_header->msg_type != SDEP_MSGTYPE_ERROR && timer_elapsed32(tt) < _timeout) {
            p_header->msg_type = spi_read();
        }

        if (timer_elapsed32(tt) > _timeout) break;

        spi_receive((&p_header->msg_type) + 1, sizeof(sdepMsgHeader_t) - 1);

        // Error Message Response
        if (p_header->msg_type == SDEP_MSGTYPE_ERROR) break;

        // Command is 16-bit at odd address, may have alignment issue with 32-bit chip
        uint16_t cmd_id = word(p_header->cmd_id_high, p_header->cmd_id_low);

        // Invalid command
        if (!(cmd_id == SDEP_CMDTYPE_AT_WRAPPER || cmd_id == SDEP_CMDTYPE_BLE_UARTTX || cmd_id == SDEP_CMDTYPE_BLE_UARTRX)) {
            break;
        }

        // Invalid length
        if (p_header->length > SDEP_MAX_PACKETSIZE) break;

        // read payload
        spi_receive(p_response->payload, p_header->length);

        result = true;
    } while (0);

    spi_stop();

    return result;
}
