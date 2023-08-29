# group `unicode` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`unicode_input_modes`](#group__unicode_1ga87526b135d1ea56f53fe933d6bc66a6c)            | 
`public  `[`_Static_assert`](#group__unicode_1ga228e8f68206b6c1ee202d512b34cf2cd)`(sizeof(`[`unicode_config_t`](.build/docs/internals/unicode.md#unionunicode__config__t))`,"Unicode EECONFIG out of spec.")`            | 
`public void `[`unicode_input_mode_init`](#group__unicode_1ga8592ac0ef108389ad732680a269b2a3a)`(void)`            | 
`public uint8_t `[`get_unicode_input_mode`](#group__unicode_1ga03d833381368ad20462bffa3b716b1f5)`(void)`            | Get the current Unicode input mode.
`public void `[`set_unicode_input_mode`](#group__unicode_1gac4985dee9f40737398b9486217cdb51d)`(uint8_t mode)`            | Set the Unicode input mode.
`public void `[`unicode_input_mode_step`](#group__unicode_1gaebd6917bb13f4334bc278ec8b528a736)`(void)`            | Change to the next Unicode input mode.
`public void `[`unicode_input_mode_step_reverse`](#group__unicode_1ga1939521bfa03504e4d49f4d96d2f91c3)`(void)`            | Change to the previous Unicode input mode.
`public void `[`unicode_input_mode_set_user`](#group__unicode_1ga39925b42094bbfddc2caffb641e54c94)`(uint8_t input_mode)`            | User-level callback, invoked when the input mode is changed.
`public void `[`unicode_input_mode_set_kb`](#group__unicode_1ga4cbea45151384f73acfcbf443c81b7f2)`(uint8_t input_mode)`            | Keyboard-level callback, invoked when the input mode is changed.
`public void `[`unicode_input_start`](#group__unicode_1ga6d60352abfa290cc3585bbcf6541a900)`(void)`            | Begin the Unicode input sequence. The exact behavior depends on the currently selected input mode.
`public void `[`unicode_input_finish`](#group__unicode_1gae14a43125d8d6dcbd7bc5b9e90b0bfe5)`(void)`            | Complete the Unicode input sequence. The exact behavior depends on the currently selected input mode.
`public void `[`unicode_input_cancel`](#group__unicode_1ga437fcef7d812226afd59dc1f792b4b23)`(void)`            | Cancel the Unicode input sequence. The exact behavior depends on the currently selected input mode.
`public void `[`register_hex`](#group__unicode_1ga8d77f2e7de42368d12863b77df11d3a5)`(uint16_t hex)`            | Send a 16-bit hex number.
`public void `[`register_hex32`](#group__unicode_1ga631488849fd1bc67a84604e825b7d48e)`(uint32_t hex)`            | Send a 32-bit hex number.
`public void `[`register_unicode`](#group__unicode_1ga0a0deec32fa289a5e4cecf2fa27aa0c0)`(uint32_t code_point)`            | Input a single Unicode character. A surrogate pair will be sent if required by the input mode.
`public void `[`send_unicode_string`](#group__unicode_1ga5a8c63163afccad70b74fac3171f7607)`(const char * str)`            | Send a string containing Unicode characters.
`union `[`unicode_config_t`](#unionunicode__config__t) | 

## Members

#### `enum `[`unicode_input_modes`](#group__unicode_1ga87526b135d1ea56f53fe933d6bc66a6c) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
UNICODE_MODE_MACOS            | 
UNICODE_MODE_LINUX            | 
UNICODE_MODE_WINDOWS            | 
UNICODE_MODE_BSD            | 
UNICODE_MODE_WINCOMPOSE            | 
UNICODE_MODE_EMACS            | 
UNICODE_MODE_COUNT            | 

#### `public  `[`_Static_assert`](#group__unicode_1ga228e8f68206b6c1ee202d512b34cf2cd)`(sizeof(`[`unicode_config_t`](.build/docs/internals/unicode.md#unionunicode__config__t))`,"Unicode EECONFIG out of spec.")` 

#### `public void `[`unicode_input_mode_init`](#group__unicode_1ga8592ac0ef108389ad732680a269b2a3a)`(void)` 

#### `public uint8_t `[`get_unicode_input_mode`](#group__unicode_1ga03d833381368ad20462bffa3b716b1f5)`(void)` 

Get the current Unicode input mode.

#### Returns
The currently active Unicode input mode.

#### `public void `[`set_unicode_input_mode`](#group__unicode_1gac4985dee9f40737398b9486217cdb51d)`(uint8_t mode)` 

Set the Unicode input mode.

#### Parameters
* `mode` The input mode to set.

#### `public void `[`unicode_input_mode_step`](#group__unicode_1gaebd6917bb13f4334bc278ec8b528a736)`(void)` 

Change to the next Unicode input mode.

#### `public void `[`unicode_input_mode_step_reverse`](#group__unicode_1ga1939521bfa03504e4d49f4d96d2f91c3)`(void)` 

Change to the previous Unicode input mode.

#### `public void `[`unicode_input_mode_set_user`](#group__unicode_1ga39925b42094bbfddc2caffb641e54c94)`(uint8_t input_mode)` 

User-level callback, invoked when the input mode is changed.

#### Parameters
* `input_mode` The new input mode.

#### `public void `[`unicode_input_mode_set_kb`](#group__unicode_1ga4cbea45151384f73acfcbf443c81b7f2)`(uint8_t input_mode)` 

Keyboard-level callback, invoked when the input mode is changed.

#### Parameters
* `input_mode` The new input mode.

#### `public void `[`unicode_input_start`](#group__unicode_1ga6d60352abfa290cc3585bbcf6541a900)`(void)` 

Begin the Unicode input sequence. The exact behavior depends on the currently selected input mode.

#### `public void `[`unicode_input_finish`](#group__unicode_1gae14a43125d8d6dcbd7bc5b9e90b0bfe5)`(void)` 

Complete the Unicode input sequence. The exact behavior depends on the currently selected input mode.

#### `public void `[`unicode_input_cancel`](#group__unicode_1ga437fcef7d812226afd59dc1f792b4b23)`(void)` 

Cancel the Unicode input sequence. The exact behavior depends on the currently selected input mode.

#### `public void `[`register_hex`](#group__unicode_1ga8d77f2e7de42368d12863b77df11d3a5)`(uint16_t hex)` 

Send a 16-bit hex number.

#### Parameters
* `hex` The number to send.

#### `public void `[`register_hex32`](#group__unicode_1ga631488849fd1bc67a84604e825b7d48e)`(uint32_t hex)` 

Send a 32-bit hex number.

#### Parameters
* `hex` The number to send.

#### `public void `[`register_unicode`](#group__unicode_1ga0a0deec32fa289a5e4cecf2fa27aa0c0)`(uint32_t code_point)` 

Input a single Unicode character. A surrogate pair will be sent if required by the input mode.

#### Parameters
* `code_point` The code point of the character to send.

#### `public void `[`send_unicode_string`](#group__unicode_1ga5a8c63163afccad70b74fac3171f7607)`(const char * str)` 

Send a string containing Unicode characters.

#### Parameters
* `str` The string to send.

