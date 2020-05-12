/**************************************************************************/
/*!
    Modified from the original Adafruit_BLE.cpp which was released under
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

#include <stdlib.h>
#include "BLE.h"
#include "wait.h"
#include "timer.h"
#include "print.h"

#define bit(b) (1UL << (b))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

#ifndef min
#    define min(a, b) ((a) < (b) ? (a) : (b))
#endif

enum {
    EVENT_SYSTEM_CONNECT    = 0,
    EVENT_SYSTEM_DISCONNECT = 1,

    EVENT_SYSTEM_BLE_UART_RX = 8,
    //  9 reserved
    // 10 reserved
    // 11 reserved
};

enum { NVM_USERDATA_SIZE = 256 };

/******************************************************************************/
/*!
    @brief  Constructor
*/
/******************************************************************************/
BLE::BLE(void) {
    _timeout = BLE_DEFAULT_TIMEOUT;

    _reset_started_timestamp = 0;
    _using_events            = false;

    _disconnect_callback  = NULL;
    _connect_callback     = NULL;
    _ble_uart_rx_callback = NULL;
}

/******************************************************************************/
/*!
    @brief Helper to install callback
    @param
*/
/******************************************************************************/
void BLE::install_callback(bool enable, int8_t system_id) {
    uint8_t current_mode = _mode;

    // switch mode if necessary to execute command
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_COMMAND);

    this->pprint(enable ? F("AT+EVENTENABLE=0x") : F("AT+EVENTDISABLE=0x"));
    this->pprint((system_id < 0) ? 0 : bit(system_id), HEX);

    this->pprintln();

    if (waitForOK()) {
        _using_events = true;
    }

    // switch back if necessary
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_DATA);
}

/******************************************************************************/
/*!
    @brief  Performs a system reset using AT command
    @param blocking blocking until bluefruit is ready, will take 1 second mostly
*/
/******************************************************************************/
bool BLE::reset(bool blocking) {
    bool isOK;
    for (uint8_t t = 0; t < 5; t++) {
        isOK = atcommand(F("ATZ"));

        if (isOK) break;
    }

    if (!isOK) {
        // ok we're going to get desperate
        wait_ms(50);
        setMode(BLUEFRUIT_MODE_COMMAND);
        wait_ms(50);

        for (uint8_t t = 0; t < 5; t++) {
            isOK = atcommand(F("ATZ"));

            if (isOK) break;
        }

        if (!isOK) return false;
    }

    _reset_started_timestamp = timer_read32();

    // Bluefruit need 1 second to reboot
    if (blocking) {
        wait_ms(1000);
    }

    // flush all left over
    flush();

    return isOK;
}

/******************************************************************************/
/*!
    @brief  Performs a factory reset
*/
/******************************************************************************/
bool BLE::factoryReset(bool blocking) {
    this->pprintln(F("AT+FACTORYRESET"));
    bool isOK = waitForOK();

    _reset_started_timestamp = timer_read32();

    // Bluefruit need 1 second to reboot
    if (blocking) {
        wait_ms(1000);
    }

    // flush all left over
    flush();

    return isOK;
}

/******************************************************************************/
/*!
    @brief  Check if the reset process is completed, should be used if user
    reset Bluefruit with non-blocking aka reset(false)
*/
/******************************************************************************/
bool BLE::resetCompleted(void) { return timer_elapsed32(_reset_started_timestamp) > 1000; }

/******************************************************************************/
/*!
    @brief  Enable or disable AT Command echo from Bluefruit

    @parma[in] enable
               true to enable (default), false to disable
*/
/******************************************************************************/
bool BLE::echo(bool enable) { return atcommand(F("ATE"), (int32_t)enable); }

/******************************************************************************/
/*!
    @brief  Check connection state, returns true is connected!
*/
/******************************************************************************/
bool BLE::isConnected(void) {
    int32_t connected = 0;
    atcommandIntReply(F("AT+GAPGETCONN"), &connected);
    return connected;
}

/******************************************************************************/
/*!
    @brief  Disconnect if currently connected
*/
/******************************************************************************/
void BLE::disconnect(void) { atcommand(F("AT+GAPDISCONNECT")); }

/******************************************************************************/
/*!
    @brief  Print Bluefruit's information retrieved by ATI command
*/
/******************************************************************************/
void BLE::info(void) {
    uint8_t current_mode = _mode;

    bool v   = _verbose;
    _verbose = false;

    println("----------------");

    // switch mode if necessary to execute command
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_COMMAND);

    pprintln(F("ATI"));

    while (readline()) {
        if (!strcmp(buffer, "OK") || !strcmp(buffer, "ERROR")) break;
        xprintf("%s\n", buffer);
    }

    // switch back if necessary
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_DATA);

    println("----------------");

    _verbose = v;
}

/**************************************************************************/
/*!
    @brief  Checks if firmware is equal or later than specified version
*/
/**************************************************************************/
bool BLE::isVersionAtLeast(const char* versionString) {
    uint8_t current_mode = _mode;

    // switch mode if necessary to execute command
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_COMMAND);

    // requesting version number
    this->pprintln(F("ATI=4"));

    readline();
    bool result = (strcmp(buffer, versionString) >= 0);
    waitForOK();

    // switch back if necessary
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_DATA);

    return result;
}

/******************************************************************************/
/*!
    @brief  Get (multiple) lines of response data into internal buffer.

    @param[in] period_ms
               period in milliseconds between each event scanning
    @return    None
*/
/******************************************************************************/
void BLE::update(uint32_t period_ms) {
    if (!_using_events) return;

    static uint32_t tt = 0;

    if (timer_elapsed32(tt) > period_ms) {
        tt = timer_read32();

        bool v   = _verbose;
        _verbose = false;

        uint8_t current_mode = _mode;

        // switch mode if necessary to execute command
        if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_COMMAND);

        this->pprintln(F("AT+EVENTSTATUS"));
        readline();
        waitForOK();

        // parse event status system_event
        uint8_t  tempbuf[BLE_BUFSIZE + 1];
        uint32_t system_event;
        char*    p_comma = NULL;

        system_event = strtoul(this->buffer, &p_comma, 16);

        //--------------------------------------------------------------------+
        // System Event
        //--------------------------------------------------------------------+
        if (this->_connect_callback && bitRead(system_event, EVENT_SYSTEM_CONNECT)) this->_connect_callback();
        if (this->_disconnect_callback && bitRead(system_event, EVENT_SYSTEM_DISCONNECT)) this->_disconnect_callback();

        if (this->_ble_uart_rx_callback && bitRead(system_event, EVENT_SYSTEM_BLE_UART_RX)) {
            this->pprintln(F("AT+BLEUARTRX"));
            uint16_t len = readline(tempbuf, BLE_BUFSIZE);
            waitForOK();

            this->_ble_uart_rx_callback((char*)tempbuf, len);
        }

        // switch back if necessary
        if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_DATA);

        _verbose = v;
    }
}

/******************************************************************************/
/*!
    @brief Set custom ADV data packet
    @param
*/
/******************************************************************************/
bool BLE::setAdvData(uint8_t advdata[], uint8_t size) { return this->atcommand(F("AT+GAPSETADVDATA"), advdata, size); }

/******************************************************************************/
/*!
    @brief Save user information to NVM section, current size limit is 256 bytes
    @param data buffer holding data
    @param size number of bytes
    @param offset relative offset in the NVM section
*/
/******************************************************************************/
bool BLE::writeNVM(uint16_t offset, uint8_t const data[], uint16_t size) {
    VERIFY_(offset + size <= NVM_USERDATA_SIZE);

    uint16_t type[] = {AT_ARGTYPE_UINT16, AT_ARGTYPE_UINT8, (uint16_t)(AT_ARGTYPE_BYTEARRAY + size)};
    uint32_t args[] = {offset, BLE_DATATYPE_BYTEARRAY, (uint32_t)data};

    return this->atcommand_full(F("AT+NVMWRITE"), NULL, 3, type, args);
}

/******************************************************************************/
/*!
    @brief Save String to NVM section, current size limit is 256 bytes
    @param data buffer holding data
    @param size number of bytes
    @param offset relative offset in the NVM section
*/
/******************************************************************************/
bool BLE::writeNVM(uint16_t offset, char const* str) {
    VERIFY_(offset + strlen(str) <= NVM_USERDATA_SIZE);

    uint16_t type[] = {AT_ARGTYPE_UINT16, AT_ARGTYPE_UINT8, AT_ARGTYPE_STRING};
    uint32_t args[] = {offset, BLE_DATATYPE_STRING, (uint32_t)str};

    return this->atcommand_full(F("AT+NVMWRITE"), NULL, 3, type, args);
}

/******************************************************************************/
/*!
    @brief Save an 32-bit number to NVM
    @param number Number to be saved
    @param offset relative offset in the NVM section
*/
/******************************************************************************/
bool BLE::writeNVM(uint16_t offset, int32_t number) {
    VERIFY_(offset + 4 <= NVM_USERDATA_SIZE);

    uint16_t type[] = {AT_ARGTYPE_UINT16, AT_ARGTYPE_UINT8, AT_ARGTYPE_INT32};
    uint32_t args[] = {offset, BLE_DATATYPE_INTEGER, (uint32_t)number};

    return this->atcommand_full(F("AT+NVMWRITE"), NULL, 3, type, args);
}

/******************************************************************************/
/*!
    @brief Read an number of bytes from NVM at offset to buffer
    @param
*/
/******************************************************************************/
bool BLE::readNVM(uint16_t offset, uint8_t data[], uint16_t size) {
    VERIFY_(offset < NVM_USERDATA_SIZE);

    uint8_t current_mode = _mode;

    // switch mode if necessary to execute command
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_COMMAND);

    // use RAW command version
    this->pprint(F("AT+NVMREADRAW="));
    this->pprint(offset);

    this->pprint(',');
    this->pprintln(size);

    uint16_t len = readraw();  // readraw swallow OK/ERROR already

    // Check for an error reading
    if (len != size) return false;

    // skip if NULL is entered
    if (data) memcpy(data, this->buffer, min(size, BLE_BUFSIZE));

    // switch back if necessary
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_DATA);

    return true;
}

/******************************************************************************/
/*!
    @brief Read a string from NVM at offset to buffer
    @param
*/
/******************************************************************************/
bool BLE::readNVM(uint16_t offset, char* str, uint16_t size) {
    VERIFY_(offset < NVM_USERDATA_SIZE);

    uint16_t type[] = {AT_ARGTYPE_UINT16, AT_ARGTYPE_UINT16, AT_ARGTYPE_UINT8};
    uint32_t args[] = {offset, size, BLE_DATATYPE_STRING};

    bool isOK = this->atcommand_full(F("AT+NVMREAD"), NULL, 3, type, args);

    // skip if NULL is entered
    if (isOK && str) strncpy(str, this->buffer, min(size, BLE_BUFSIZE));

    return isOK;
}

/******************************************************************************/
/*!
    @brief Read an 32-bit number from NVM
    @param
*/
/******************************************************************************/
bool BLE::readNVM(uint16_t offset, int32_t* number) { return this->readNVM(offset, (uint8_t*)number, 4); }

/**
 *
 * @param buffer
 * @param size
 * @return
 */
int BLE::writeBLEUart(uint8_t const* buffer, int size) {
    uint8_t current_mode = _mode;

    // switch mode if necessary to execute command
    if (current_mode == BLUEFRUIT_MODE_COMMAND) setMode(BLUEFRUIT_MODE_DATA);

    size_t n = write(buffer, size);

    // switch back if necessary
    if (current_mode == BLUEFRUIT_MODE_COMMAND) setMode(BLUEFRUIT_MODE_COMMAND);

    return n;
}

/**
 *
 * @param buffer
 * @param size
 * @return
 */
int BLE::readBLEUart(uint8_t* buffer, int size) {
    uint8_t current_mode = _mode;

    // switch mode if necessary to execute command
    if (current_mode == BLUEFRUIT_MODE_COMMAND) setMode(BLUEFRUIT_MODE_DATA);

    size_t n = readBytes(buffer, size);

    // switch back if necessary
    if (current_mode == BLUEFRUIT_MODE_COMMAND) setMode(BLUEFRUIT_MODE_COMMAND);

    return n;
}

/******************************************************************************/
/*!
    @brief  Set handle for connect callback

    @param[in] fp function pointer, NULL will discard callback
*/
/******************************************************************************/
void BLE::setConnectCallback(void (*fp)(void)) {
    this->_connect_callback = fp;
    install_callback(fp != NULL, EVENT_SYSTEM_CONNECT);
}

/******************************************************************************/
/*!
    @brief  Set handle for disconnection callback

    @param[in] fp function pointer, NULL will discard callback
*/
/******************************************************************************/
void BLE::setDisconnectCallback(void (*fp)(void)) {
    this->_disconnect_callback = fp;
    install_callback(fp != NULL, EVENT_SYSTEM_DISCONNECT);
}

/******************************************************************************/
/*!
    @brief  Set handle for BLE Uart Rx callback

    @param[in] fp function pointer, NULL will discard callback
*/
/******************************************************************************/
void BLE::setBleUartRxCallback(void (*fp)(char data[], uint16_t len)) {
    this->_ble_uart_rx_callback = fp;
    install_callback(fp != NULL, EVENT_SYSTEM_BLE_UART_RX);
}

bool BLE::usingEvents() { return _using_events; }
