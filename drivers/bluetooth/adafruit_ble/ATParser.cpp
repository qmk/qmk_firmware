/**************************************************************************/
/*!
    Modified from the original ATParser.cpp which was released under
    the BSD License (below).

    Software License Agreement (BSD License)

    Copyright (c) 2020, Joshua Rubin
    Copyright (c) 2016, Adafruit Industries (adafruit.com)
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
#include "ATParser.h"
#include "wait.h"
#include "debug.h"

#define lowByte(w) ((uint8_t)((w)&0xff))

static inline char digit2ascii(uint8_t digit) { return (digit + ((digit) < 10 ? '0' : ('A' - 10))); }

/******************************************************************************/
/*!
    @brief Constructor
*/
/******************************************************************************/
ATParser::ATParser(void) {
    _mode    = BLUEFRUIT_MODE_COMMAND;
    _verbose = false;
}

/******************************************************************************/
/*!
    @brief  Read the whole response and check if it ended up with OK.
    @return true if response is ended with "OK". Otherwise it could be "ERROR"
*/
/******************************************************************************/
bool ATParser::waitForOK(void) {
    if (_verbose) dprint("\n<- ");

    // Use temp buffer to avoid overwrite returned result if any
    char tempbuf[BLE_BUFSIZE + 1];

    while (readline(tempbuf, BLE_BUFSIZE)) {
        if (strcmp(tempbuf, "OK") == 0) return true;
        if (strcmp(tempbuf, "ERROR") == 0) return false;

        // Copy to internal buffer if not OK or ERROR
        strcpy(this->buffer, tempbuf);
    }
    return false;
}

/******************************************************************************/
/*!
    @brief
    @param
*/
/******************************************************************************/
bool ATParser::send_arg_get_resp(int32_t* reply, uint8_t argcount, uint16_t argtype[], uint32_t args[]) {
    // Command arguments according to its type
    for (uint8_t i = 0; i < argcount; i++) {
        // print '=' for WRITE mode
        if (i == 0) this->pprint('=');

        switch (argtype[i] & 0xFF00) {
            case AT_ARGTYPE_STRING:
                this->pprint((char const*)args[i]);
                break;

            case AT_ARGTYPE_BYTEARRAY: {
                uint8_t count = lowByte(argtype[i]);
                this->printByteArray((uint8_t const*)args[i], count);
            } break;

            case AT_ARGTYPE_UINT32:
                this->pprint((uint32_t)args[i]);
                break;

            case AT_ARGTYPE_INT32:
                this->pprint((int32_t)args[i]);
                break;

            case AT_ARGTYPE_UINT16:
                this->pprint((uint16_t)args[i]);
                break;

            case AT_ARGTYPE_INT16:
                this->pprint((int16_t)args[i]);
                break;

            case AT_ARGTYPE_UINT8:
                this->pprint((uint8_t)((uint32_t)args[i]));
                break;

            case AT_ARGTYPE_INT8:
                this->pprint((int8_t)((int32_t)args[i]));
                break;

            default:
                break;
        }

        if (i != argcount - 1) this->pprint(',');
    }
    this->pprintln();  // execute command

    // parse integer response if required
    if (reply) {
        if (_verbose) dprint("\n<- ");
        (*reply) = readline_parseInt();
    }

    // check OK or ERROR status
    return waitForOK();
}

/******************************************************************************/
/*!
    @brief
    @param
*/
/******************************************************************************/
bool ATParser::atcommand_full(const char cmd[], int32_t* reply, uint8_t argcount, uint16_t argtype[], uint32_t args[]) {
    bool    result;
    uint8_t current_mode = _mode;

    // switch mode if necessary to execute command
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_COMMAND);

    // Execute command with parameter and get response
    this->pprint(cmd);
    result = this->send_arg_get_resp(reply, argcount, argtype, args);

    // switch back if necessary
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_DATA);

    return result;
}

/******************************************************************************/
/*!
    @brief
    @param
*/
/******************************************************************************/
bool ATParser::atcommand_full(const __FlashStringHelper* cmd, int32_t* reply, uint8_t argcount, uint16_t argtype[], uint32_t args[]) {
    bool    result;
    uint8_t current_mode = _mode;

    // switch mode if necessary to execute command
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_COMMAND);

    // Execute command with parameter and get response
    this->pprint(cmd);
    result = this->send_arg_get_resp(reply, argcount, argtype, args);

    // switch back if necessary
    if (current_mode == BLUEFRUIT_MODE_DATA) setMode(BLUEFRUIT_MODE_DATA);

    return result;
}

/******************************************************************************/
/*!
    @brief  Get a line of response data (see \ref readline) and try to interpret
            it to an integer number. If the number is prefix with '0x', it will
            be interpreted as hex number. This function also drop the rest of
            data to the end of the line.
*/
/******************************************************************************/
int32_t ATParser::readline_parseInt(void) {
    uint16_t len = readline();
    if (len == 0) return 0;

    // also parsed hex number e.g 0xADAF
    int32_t val = strtol(buffer, NULL, 0);

    return val;
}

/******************************************************************************/
/*!
    @brief  Get a line of response data into provided buffer.

    @param[in] buf Provided buffer
    @param[in] bufsize buffer size
    @param[in] timeout timeout in milliseconds
    @param[in] multiline Read multiple line if true, otherwise only read 1 line

    @note '\r' and '\n' are not included in returned buffer.
*/
/******************************************************************************/
uint16_t ATParser::readline(char* buf, uint16_t bufsize, uint16_t timeout, bool multiline) {
    uint16_t replyidx = 0;

    while (timeout--) {
        while (available()) {
            char c = read();

            if (c == '\r') continue;

            if (c == '\n') {
                // the first '\n' is ignored
                if (replyidx == 0) continue;

                if (!multiline) {
                    timeout = 0;
                    break;
                }
            }

            buf[replyidx] = c;
            replyidx++;

            // Buffer is full
            if (replyidx >= bufsize) {
                timeout = 0;
                break;
            }
        }

        // delay if needed
        if (timeout) wait_ms(1);
    }

    buf[replyidx] = 0;  // null term

    // Print out if is verbose
    if (_verbose && replyidx > 0) {
        dprintf("%s", buf);
        if (replyidx < bufsize) dprintln();
    }

    return replyidx;
}

/******************************************************************************/
/*!
    @brief  Get raw binary data to internal buffer, only stop when encountering
            either "OK\r\n" or "ERROR\r\n" or timed out. Buffer does not contain
            OK or ERROR

    @param[in] timeout
               Timeout for each read() operation

    @return    The number of bytes read excluding OK, ERROR ending.
               0 usually means error
*/
/******************************************************************************/
uint16_t ATParser::readraw(uint16_t timeout) {
    uint16_t replyidx = 0;

    while (timeout--) {
        while (available()) {
            char c = read();

            if (c == '\n') {
                // done if ends with "OK\r\n"
                if ((replyidx >= 3) && !strncmp(this->buffer + replyidx - 3, "OK\r", 3)) {
                    replyidx -= 3;  // chop OK\r
                    timeout = 0;
                    break;
                } else if ((replyidx >= 6) && !strncmp(this->buffer + replyidx - 6, "ERROR\r", 6)) {
                    // done if ends with "ERROR\r\n"
                    replyidx -= 6;  // chop ERROR\r
                    timeout = 0;
                    break;
                }
            }

            this->buffer[replyidx] = c;
            replyidx++;

            // Buffer is full
            if (replyidx >= BLE_BUFSIZE) {
                timeout = 0;
                break;
            }
        }

        if (timeout == 0) break;
        wait_ms(1);
    }
    this->buffer[replyidx] = 0;  // null term

    return replyidx;
}

/******************************************************************************/
/*!
    @brief Print a buffer to BYTE ARRAY format e.g 11-22-33-44-55
    @param bytearray buffer to print
    @param size number of byte
    @return number of printed characters
*/
/******************************************************************************/
int ATParser::printByteArray(uint8_t const bytearray[], int size) {
    while (size--) {
        uint8_t byte = *bytearray++;
        write(digit2ascii((byte & 0xF0) >> 4));
        write(digit2ascii(byte & 0x0F));
        if (size != 0) write('-');
    }

    return (size * 3) - 1;
}
