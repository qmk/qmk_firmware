/******************************************************************************/
/*!
    Modified from the original sdep.h which was released under the BSD License
    (below).

    Software License Agreement (BSD License)

    Copyright (c) 2020, Joshua Rubin
    Copyright (c) 2013, K. Townsend (microBuilder.eu)
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
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/******************************************************************************/
#pragma once

#define ATTR_PACKED __attribute__((packed))
#define SDEP_MAX_PACKETSIZE 16  // Maximum payload per packet

/******************************************************************************/
/*!
    This enumeration is used to make sure that each command has a unique
    ID, and is used to create the command lookup table enum further down
*/
/******************************************************************************/
typedef enum {
    SDEP_CMDTYPE_AT_WRAPPER = 0x0A00,
    SDEP_CMDTYPE_BLE_UARTTX = 0x0A01,
    SDEP_CMDTYPE_BLE_UARTRX = 0x0A02,
} sdepCmdType_t;

/******************************************************************************/
/*!
    The first byte of every transfer defines the message type
*/
/******************************************************************************/
typedef enum {
    SDEP_MSGTYPE_COMMAND  = 0x10,
    SDEP_MSGTYPE_RESPONSE = 0x20,
    SDEP_MSGTYPE_ALERT    = 0x40,
    SDEP_MSGTYPE_ERROR    = 0x80,
} sdepMsgType_t;

/******************************************************************************/
/*!
    4-byte header for SDEP messages
*/
/******************************************************************************/
typedef struct ATTR_PACKED {
    uint8_t msg_type;  // 8-bit message type indicator (sdepMsgType_t)

    union {
        uint16_t cmd_id;  // 16-bit command ID
        struct {
            uint8_t cmd_id_low;
            uint8_t cmd_id_high;
        };
    };

    struct ATTR_PACKED {
        uint8_t length : 7;     // Payload length (for this packet)
        uint8_t more_data : 1;  // 'more' bit for multiple packet transfers
    };
} sdepMsgHeader_t;

/******************************************************************************/
/*!
    SDEP command message
*/
/******************************************************************************/
typedef struct ATTR_PACKED {
    sdepMsgHeader_t header;
    uint8_t         payload[SDEP_MAX_PACKETSIZE];
} sdepMsgCommand_t;

/******************************************************************************/
/*!
    Response message struct (same as sdepMsgCommand_t)
*/
/******************************************************************************/
typedef sdepMsgCommand_t sdepMsgResponse_t;

/******************************************************************************/
/*!
    Alert message struct
*/
/******************************************************************************/
typedef sdepMsgCommand_t sdepMsgAlert_t;
