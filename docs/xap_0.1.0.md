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
| _bool_ | Data type that contains values 0 and 1. Implemented as an alias of `u8`. |
| _struct{}_ | A structure of data, packing different objects together. Data is "compacted" -- there are no padding bytes between fields. Equivalent to a packed C-style `struct`. The order in which they're defined matches the order of the data in the response packet. |
| _type[n]_ | An array of `type`, with array extent of `N` -- e.g. `u8[2]` signifies two consecutive octets. |
| _u16_ | An unsigned 16-bit integral, commonly seen as `uint16_t` from _stdint.h_. |
| _u32_ | An unsigned 32-bit integral, commonly seen as `uint32_t` from _stdint.h_. |
| _u64_ | An unsigned 64-bit integral, commonly seen as `uint64_t` from _stdint.h_. |
| _u8_ | An unsigned 8-bit integral (octet, or byte), commonly seen as `uint8_t` from _stdint.h_. |

## Definitions

This list defines the terms used across the entire set of XAP protocol documentation.

| Name | Definition |
| -- | -- |
| _Capability_ | A way to determine if certain functionality is enabled in the firmware. Any _subsystem_ that provides build-time restriction of functionality must provide a _route_ for a _capabilities query_. |
| _Handler_ | A piece of code that is executed when a specific _route_ is received. |
| _Payload_ | Any received data appended to the _route_, which gets delivered to the _handler_ when received. |
| _Response_ | The data sent back to the host during execution of a _handler_. |
| _Route_ | A sequence of _IDs_ describing the route to invoke a _handler_. |
| _Secure Route_ | A _route_ which has potentially destructive consequences, necessitating prior approval by the user before executing. |
| _Subsystem_ | A high-level area of functionality within XAP. |
| _Unlock sequence_ | A physical sequence initiated by the user to enable execution of  _secure routes_. |
| _Broadcast Header_ | Packet format for broadcast messages. Takes the format:<br>`token` - token<br>`u8` - type<br>`u8` - length |
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

Two token values are reserved: `0xFFFE` and `0xFFFF`:
* `0xFFFE`: A message sent by a host application may use this token if no response is to be sent -- a "fire and forget" message.
* `0xFFFF`: Signifies a "broadcast" message sent by the firmware without prompting from the host application. Broadcast messages are defined later in this document.

Any request will generate at least one corresponding response, with the exception of messages using reserved tokens. Maximum total message length is 128 bytes due to RAM constraints.

Response messages will always be prefixed by the originating request _token_, directly followed by that request's _response flags_, then the response payload length:

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| -- | -- | -- | -- | -- | -- | -- | -- |
| `-` | `-` | `-` | `-` | `-` | `-` | `SECURE_FAILURE` | `SUCCESS` |

* Bit 1 (`SECURE_FAILURE`): When this bit is set, the requested _route_ was marked _secure_ but an _unlock sequence_ has not completed.
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
| Capabilities Query | `0x00 0x01` |  | __Response:__ `u32` | XAP subsystem capabilities query. Each bit should be considered as a "usable" route within this subsystem.|
| Enabled subsystem query | `0x00 0x02` |  | __Response:__ `u32` | XAP protocol subsystem query. Each bit should be considered as a "usable" subsystem. For example, checking `(value & (1 << XAP_ROUTE_QMK) != 0)` means the QMK subsystem is enabled and available for querying.|
| Secure Status | `0x00 0x03` |  | __Response:__ `u8` | Query secure route status<br><br>* 0 means secure routes are disabled<br>* 1 means unlock sequence initiated but incomplete<br>* 2 means secure routes are allowed<br>* any other value should be interpreted as disabled|
| Secure Unlock | `0x00 0x04` |  |  | Initiate secure route unlock sequence|
| Secure Lock | `0x00 0x05` |  |  | Disable secure routes|

### QMK - `0x01`
This subsystem is always present, and provides the ability to address QMK-specific functionality.

| Name | Route | Tags | Payloads | Description |
| -- | -- | -- | -- | -- |
| Version Query | `0x01 0x00` |  | __Response:__ `u32` | QMK protocol version query.<br><br>* Returns the BCD-encoded version in the format of XX.YY.ZZZZ => `0xXXYYZZZZ`<br>    * e.g. 3.2.115 will match `0x03020115`, or bytes {0x15,0x01,0x02,0x03}.|
| Capabilities Query | `0x01 0x01` |  | __Response:__ `u32` | QMK subsystem capabilities query. Each bit should be considered as a "usable" route within this subsystem.|
| Board identifiers | `0x01 0x02` |  | __Response:__<br>&nbsp;&nbsp;&nbsp;&nbsp;* Vendor ID: `u16`<br>&nbsp;&nbsp;&nbsp;&nbsp;* Product ID: `u16`<br>&nbsp;&nbsp;&nbsp;&nbsp;* Product Version: `u16`<br>&nbsp;&nbsp;&nbsp;&nbsp;* QMK Unique Identifier: `u32` | Retrieves the set of identifying information for the board.|
| Board Manufacturer | `0x01 0x03` |  | __Response:__ `string` | Retrieves the name of the manufacturer|
| Product Name | `0x01 0x04` |  | __Response:__ `string` | Retrieves the product name|
| Config Blob Length | `0x01 0x05` |  | __Response:__ `u16` | Retrieves the length of the configuration data bundled within the firmware|
| Config Blob Chunk | `0x01 0x06` |  | __Request:__ `u16`<br><br>__Response:__ `u8[32]` | Retrieves a chunk of the configuration data bundled within the firmware|
| Jump to bootloader | `0x01 0x07` | __Secure__ | __Response:__ `u8` | Jump to bootloader<br><br>May not be present - if QMK capabilities query returns “true”, then jump to bootloader is supported<br><br>* 0 means secure routes are disabled, and should be considered as a failure<br>* 1 means successful, board will jump to bootloader|
| Hardware Identifier | `0x01 0x08` |  | __Response:__ `u32[4]` | Retrieves a unique identifier for the board.|
| Reinitialize EEPROM | `0x01 0x09` | __Secure__ | __Response:__ `u8` | Reinitializes the keyboard's EEPROM (persistent memory)<br><br>May not be present - if QMK capabilities query returns “true”, then reinitialize is supported<br><br>* 0 means secure routes are disabled, and should be considered as a failure<br>* 1 means successful, board will reinitialize and then reboot|

### Keyboard - `0x02`
This subsystem is always present, and reserved for vendor-specific functionality. No routes are defined by XAP.

### User - `0x03`
This subsystem is always present, and reserved for user-specific functionality. No routes are defined by XAP.


## Broadcast messages

Broadcast messages may be sent by the firmware to the host, without a corresponding inbound request. Each broadcast message uses the token `0xFFFF`, and does not expect a response from the host. Tokens are followed by an _ID_ signifying the type of broadcast, then the response _payload_ length, and finally the corresponding _payload_.

### Log message - `0x00`
Replicates and replaces the same functionality as if using the standard QMK `CONSOLE_ENABLE = yes` in `rules.mk`. Normal prints within the firmware will manifest as log messages broadcast to the host. `hid_listen` will not be functional with XAP enabled.

Log message payloads include `u8[Length]` containing the text, where the length of the text is the _broadcast_header.length_ field.

**Example Log Broadcast** -- log message "Hello QMK!"

| Byte | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| **Purpose** | Token | Token | Broadcast Type | Length | Payload | Payload | Payload | Payload | Payload | Payload | Payload | Payload | Payload | Payload |
| **Value** | `0xFF` | `0xFF` | `0x00` | `0x0A`(10) | `0x48`(H) | `0x65`(e) | `0x6C`(l) | `0x6C`(l) | `0x6F`(o) | `0x20`(&nbsp;) | `0x51`(Q) | `0x4D`(M) | `0x4B`(K) | `0x21`(!) |
### Secure Status - `0x01`
Secure status has changed. Payloads include a `u8` matching a 'Secure Status' request.

**Example Secure Status Broadcast** -- secure "Unlocking"

| Byte | 0 | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- | --- |
| **Purpose** | Token | Token | Broadcast Type | Length | Secure Status |
| **Value** | `0xFF` | `0xFF` | `0x01` | `0x01` | `0x01` |
### Keyboard - `0x02`
Reserved for vendor-specific functionality. No messages are defined by XAP.
### User - `0x03`
Reserved for user-specific functionality. No messages are defined by XAP.

