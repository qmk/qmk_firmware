/**************************************************************************/
/*!
    Modified from the original Adafruit_BLE.h which was released under
    the BSD License (below).

    Software License Agreement (BSD License)

    Copyright (c) 2020, Joshua Rubin
    Copyright (c) 2014, Adafruit Industries (adafruit.com)
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

#include "adafruit_ble.h"

#ifdef __cplusplus
#    include "ATParser.h"

#    define BLE_DEFAULT_TIMEOUT 250
#    define VERIFY_(condition) \
        if (!(condition)) return false;

#    ifndef AdafruitBleVerbose
#        define AdafruitBleVerbose true
#    endif

enum BLEDataType_t {
    BLE_DATATYPE_AUTO = 0,
    BLE_DATATYPE_STRING,
    BLE_DATATYPE_BYTEARRAY,
    BLE_DATATYPE_INTEGER,
};

class BLE : public ATParser {
   protected:
    enum {
        BLUEFRUIT_TRANSPORT_INVALID,
        BLUEFRUIT_TRANSPORT_HWUART,
        BLUEFRUIT_TRANSPORT_HWSPI,
    };

    uint8_t  _physical_transport;
    uint32_t _reset_started_timestamp;

   public:
    // Constructor
    BLE(void);

    // Functions implemented in this base class
    bool reset(bool blocking = true);
    bool factoryReset(bool blocking = true);
    bool resetCompleted(void);

    void info(void);
    bool echo(bool enable);

    bool isConnected(void);
    bool isVersionAtLeast(const char *versionString);
    void disconnect(void);

    bool setAdvData(uint8_t advdata[], uint8_t size);

    bool writeNVM(uint16_t offset, uint8_t const data[], uint16_t size);
    bool writeNVM(uint16_t offset, char const *str);
    bool writeNVM(uint16_t offset, int32_t number);

    bool readNVM(uint16_t offset, uint8_t data[], uint16_t size);
    bool readNVM(uint16_t offset, char *str, uint16_t size);
    bool readNVM(uint16_t offset, int32_t *number);

    // helper with bleuart
    int writeBLEUart(uint8_t const *buffer, int size);
    int writeBLEUart(char const *str) { return writeBLEUart((uint8_t const *)str, strlen(str)); }

    int readBLEUart(uint8_t *buffer, int size);

    // No parameters
    bool sendCommandCheckOK(const __FlashStringHelper *cmd) { return this->atcommand(cmd); }
    bool sendCommandCheckOK(const char cmd[]) { return this->atcommand(cmd); }

    bool sendCommandWithIntReply(const __FlashStringHelper *cmd, int32_t *reply) { return this->atcommandIntReply(cmd, reply); }
    bool sendCommandWithIntReply(const char cmd[], int32_t *reply) { return this->atcommandIntReply(cmd, reply); }

    // Physical transportation checking
    bool isTransportHwUart(void) { return _physical_transport == BLUEFRUIT_TRANSPORT_HWUART; }
    bool isTransportUart(void) { return isTransportHwUart(); }

    bool isTransportHwSpi(void) { return _physical_transport == BLUEFRUIT_TRANSPORT_HWSPI; }
    bool isTransportSpi(void) { return isTransportHwSpi(); }

    /////////////////////
    // callback functions
    /////////////////////
    void update(uint32_t period_ms = 200);
    void handleDfuIrq(void) { this->update(0); }

    void setDisconnectCallback(void (*fp)(void));
    void setConnectCallback(void (*fp)(void));
    void setBleUartRxCallback(void (*fp)(char data[], uint16_t len));

   protected:
    // helper
    void install_callback(bool enable, int8_t system_id);

    void (*_disconnect_callback)(void);
    void (*_connect_callback)(void);
    void (*_ble_uart_rx_callback)(char data[], uint16_t len);
};
#endif
