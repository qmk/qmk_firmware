<!--- Copyright 2024 QMK --->
<!--- SPDX-License-Identifier: GPL-2.0-or-later --->

<!---
*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************
--->
# QMK Firmware XAP Specs

This document describes the requirements of the QMK XAP ("extensible application protocol") API.

## Types

**All integral types are little-endian.**

| Name | Definition |
| -- | -- |
| _type[n]_ | An array of `type`, with array extent of `N` -- e.g. `u8[2]` signifies two consecutive octets. |
| _u16_ | An unsigned 16-bit integral, commonly seen as `uint16_t` from _stdint.h_. |
| _u32_ | An unsigned 32-bit integral, commonly seen as `uint32_t` from _stdint.h_. |
| _u8_ | An unsigned 8-bit integral (octet, or byte), commonly seen as `uint8_t` from _stdint.h_. |

## Definitions

This list defines the terms used across the entire set of XAP protocol documentation.

| Name | Definition |
| -- | -- |
| _Handler_ | A piece of code that is executed when a specific _route_ is received. |
| _Payload_ | Any received data appended to the _route_, which gets delivered to the _handler_ when received. |
| _Response_ | The data sent back to the host during execution of a _handler_. |
| _Route_ | A sequence of _IDs_ describing the route to invoke a _handler_. |
| _Subsystem_ | A high-level area of functionality within XAP. |
| _ID_ | A single octet / 8-bit byte, representing Subsystem or Route index. |
| _Request Header_ | Packet format for inbound data. Takes the format:<br>`token` - token<br>`u8` - length |
| _Response Flags_ | An `u8` containing the status of the request. |
| _Response Header_ | Packet format for outbound data. Takes the format:<br>`token` - token<br>`response_flags` - flags<br>`u8` - length |
| _Token_ | A `u16` associated with a specific request as well as its corresponding response. Valid token values are within the range `0x0100`-`0xFFFF`. |

## Requests and Responses

Communication generally follows a request/response pattern.

Each request needs to include a _token_ -- this `u16` value prefixes each outbound request from the host application and its corresponding response.
This allows response messages to be correlated with their request, even if multiple host applications are communicating with the firmware simultaneously.
Host applications should randomly generate a token ID for **every** outbound request, unless using a reserved token defined below.
To ensure host interoperability, valid token values are within the range `0x0100`-`0xFFFF`.

This token is followed by a `u8` signifying the length of data in the request.



Response messages will always be prefixed by the originating request _token_, directly followed by that request's _response flags_, then the response payload length:

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| -- | -- | -- | -- | -- | -- | -- | -- |
| `-` | `-` | `-` | `-` | `-` | `-` | `-` | `SUCCESS` |

* Bit 0 (`SUCCESS`): When this bit is set, the request was successfully handled. If not set, all payload data should be disregarded, and the request retried if appropriate (with a new token).

### Example "conversation":

**Request** -- version query:

| Byte | 0 | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- | --- |
| **Purpose** | Token | Token | Payload Length | Route | Route |
| **Value** | `0x43` | `0x2B` | `0x02` | `0x00` | `0x00` |

**Response** -- matching token, successful flag, payload of `0x03170192` = 3.17.192:

| Byte | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| **Purpose** | Token | Token | Response Flags | Payload Length | Payload | Payload | Payload | Payload |
| **Value** | `0x43` | `0x2B` | `0x01` | `0x04` | `0x92` | `0x01` | `0x17` | `0x03` |

## Routes

Subsystem validity should be queried through the “Enabled-in-firmware subsystem query” under the QMK subsystem (route=0x00,0x01).
This is the primary method for determining if a subsystem has been enabled in the running firmware.

### XAP - `0x00`
This subsystem is always present, and provides the ability to query information about the XAP protocol of the connected device.

| Name | Route | Tags | Payloads | Description |
| -- | -- | -- | -- | -- |
| Version Query | `0x00 0x00` |  | __Response:__ `u32` | XAP protocol version query.<br><br>* Returns the BCD-encoded version in the format of XX.YY.ZZZZ => `0xXXYYZZZZ`<br>    * e.g. 3.2.115 will match `0x03020115`, or bytes {0x15,0x01,0x02,0x03}.|


