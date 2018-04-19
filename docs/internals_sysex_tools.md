# group `sysex_tools` {#group__sysex__tools}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint16_t `[`sysex_encoded_length`](#group__sysex__tools_1ga061e5607030412d6e62e2390d8013f0a)`(uint16_t decoded_length)`            | Compute the length of a message after it is encoded.
`public uint16_t `[`sysex_decoded_length`](#group__sysex__tools_1ga121fc227d3acc1c0ea08c9a5c26fa3b0)`(uint16_t encoded_length)`            | Compute the length of a message after it is decoded.
`public uint16_t `[`sysex_encode`](#group__sysex__tools_1ga54d77f8d32f92a6f329daefa2b314742)`(uint8_t * encoded,const uint8_t * source,uint16_t length)`            | Encode data so that it can be transmitted safely in a sysex message.
`public uint16_t `[`sysex_decode`](#group__sysex__tools_1gaaad1d9ba2d5eca709a0ab4ba40662229)`(uint8_t * decoded,const uint8_t * source,uint16_t length)`            | Decode encoded data.

## Members

#### `public uint16_t `[`sysex_encoded_length`](#group__sysex__tools_1ga061e5607030412d6e62e2390d8013f0a)`(uint16_t decoded_length)` {#group__sysex__tools_1ga061e5607030412d6e62e2390d8013f0a}

Compute the length of a message after it is encoded.

#### Parameters
* `decoded_length` The length, in bytes, of the message to encode.

#### Returns
The length, in bytes, of the message after encodeing.

#### `public uint16_t `[`sysex_decoded_length`](#group__sysex__tools_1ga121fc227d3acc1c0ea08c9a5c26fa3b0)`(uint16_t encoded_length)` {#group__sysex__tools_1ga121fc227d3acc1c0ea08c9a5c26fa3b0}

Compute the length of a message after it is decoded.

#### Parameters
* `encoded_length` The length, in bytes, of the encoded message.

#### Returns
The length, in bytes, of the message after it is decoded.

#### `public uint16_t `[`sysex_encode`](#group__sysex__tools_1ga54d77f8d32f92a6f329daefa2b314742)`(uint8_t * encoded,const uint8_t * source,uint16_t length)` {#group__sysex__tools_1ga54d77f8d32f92a6f329daefa2b314742}

Encode data so that it can be transmitted safely in a sysex message.

#### Parameters
* `encoded` The output data buffer, must be at least sysex_encoded_length(length) bytes long. 

* `source` The input buffer of data to be encoded. 

* `length` The number of bytes from the input buffer to encode.

#### Returns
number of bytes encoded.

#### `public uint16_t `[`sysex_decode`](#group__sysex__tools_1gaaad1d9ba2d5eca709a0ab4ba40662229)`(uint8_t * decoded,const uint8_t * source,uint16_t length)` {#group__sysex__tools_1gaaad1d9ba2d5eca709a0ab4ba40662229}

Decode encoded data.

#### Parameters
* `decoded` The output data buffer, must be at least sysex_decoded_length(length) bytes long. 

* `source` The input buffer of data to be decoded. 

* `length` The number of bytes from the input buffer to decode.

#### Returns
number of bytes decoded.

