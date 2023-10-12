# group `midi_util` {#group__midi__util}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`midi_packet_length_t`](#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e)            | An enumeration of the possible packet length values.
`public bool `[`midi_is_statusbyte`](#group__midi__util_1ga12e3b42ff9cbb4b4f2bc455fc8743ee5)`(uint8_t theByte)`            | Test to see if the byte given is a status byte.
`public bool `[`midi_is_realtime`](#group__midi__util_1gad2f52c363e34a8000d80c983c324e2d7)`(uint8_t theByte)`            | Test to see if the byte given is a realtime message.
`public `[`midi_packet_length_t`](#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e)` `[`midi_packet_length`](#group__midi__util_1gaa168b43af6ae9de0debce1625e4b8175)`(uint8_t status)`            | Find the length of the packet associated with the status byte given.

## Members

#### `enum `[`midi_packet_length_t`](#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e) {#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
UNDEFINED            | 
ONE            | 
TWO            | 
THREE            | 

An enumeration of the possible packet length values.

#### `public bool `[`midi_is_statusbyte`](#group__midi__util_1ga12e3b42ff9cbb4b4f2bc455fc8743ee5)`(uint8_t theByte)` {#group__midi__util_1ga12e3b42ff9cbb4b4f2bc455fc8743ee5}

Test to see if the byte given is a status byte.

#### Parameters
* `theByte` the byte to test 

#### Returns
true if the byte given is a midi status byte

#### `public bool `[`midi_is_realtime`](#group__midi__util_1gad2f52c363e34a8000d80c983c324e2d7)`(uint8_t theByte)` {#group__midi__util_1gad2f52c363e34a8000d80c983c324e2d7}

Test to see if the byte given is a realtime message.

#### Parameters
* `theByte` the byte to test 

#### Returns
true if it is a realtime message, false otherwise

#### `public `[`midi_packet_length_t`](#group__midi__util_1gae29ff56aee2b430ffe53933b97e5e79e)` `[`midi_packet_length`](#group__midi__util_1gaa168b43af6ae9de0debce1625e4b8175)`(uint8_t status)` {#group__midi__util_1gaa168b43af6ae9de0debce1625e4b8175}

Find the length of the packet associated with the status byte given.

#### Parameters
* `status` the status byte 

#### Returns
the length of the packet, will return UNDEFINED if the byte is not a status byte or if it is a sysex status byte

