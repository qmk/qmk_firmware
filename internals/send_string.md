# group `send_string` 

These functions allow you to create macros by typing out sequences of keystrokes.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`KCLUT_ENTRY`](#group__send__string_1ga6995d9923416063c9b99f5acd0e91ed7)            | 
`define `[`SEND_STRING`](#group__send__string_1gae83e787cdd7e9cf4587a0e685ffd98f5)            | Shortcut macro for send_string_with_delay_P(PSTR(string), 0).
`define `[`SEND_STRING_DELAY`](#group__send__string_1ga6cac47ec59654132634c70986202dc42)            | Shortcut macro for send_string_with_delay_P(PSTR(string), interval).
`public void `[`send_string`](#group__send__string_1gac5e380e2be08c7a8bee8532cc72d8b30)`(const char * string)`            | Type out a string of ASCII characters.
`public void `[`send_string_with_delay`](#group__send__string_1gaa1d72394f1e4d90a4d789935f947fde6)`(const char * string,uint8_t interval)`            | Type out a string of ASCII characters, with a delay between each character.
`public void `[`send_char`](#group__send__string_1gaac462f52e01a0434a3d0d427156f7ba1)`(char ascii_code)`            | Type out an ASCII character.
`public void `[`send_dword`](#group__send__string_1gacf74558e7014b43355e61fa7104ffa8c)`(uint32_t number)`            | Type out an eight digit (unsigned 32-bit) hexadecimal value.
`public void `[`send_word`](#group__send__string_1ga9ec68473d4b590a48b9d52e35f8aecf3)`(uint16_t number)`            | Type out a four digit (unsigned 16-bit) hexadecimal value.
`public void `[`send_byte`](#group__send__string_1ga015a1b20ba56c7debe2b4edfed5cb815)`(uint8_t number)`            | Type out a two digit (8-bit) hexadecimal value.
`public void `[`send_nibble`](#group__send__string_1ga34ef35dbde792a44bdb299d10c826675)`(uint8_t number)`            | Type out a single hexadecimal digit.
`public void `[`tap_random_base64`](#group__send__string_1ga7cb02fdb6dd1d7babd67df4312a2dab9)`(void)`            | Type a pseudorandom character from the set `A-Z`, `a-z`, `0-9`, `+` and `/`.
`public void `[`send_string_P`](#group__send__string_1ga9e99e584dce970f6fe04a63b71cddf4d)`(const char * string)`            | Type out a PROGMEM string of ASCII characters.
`public void `[`send_string_with_delay_P`](#group__send__string_1ga305251111b4454c681027c5bf1c8b60c)`(const char * string,uint8_t interval)`            | Type out a PROGMEM string of ASCII characters, with a delay between each character.

## Members

#### `define `[`KCLUT_ENTRY`](#group__send__string_1ga6995d9923416063c9b99f5acd0e91ed7) 

#### `define `[`SEND_STRING`](#group__send__string_1gae83e787cdd7e9cf4587a0e685ffd98f5) 

Shortcut macro for send_string_with_delay_P(PSTR(string), 0).

On ARM devices, this define evaluates to send_string_with_delay(string, 0).

#### `define `[`SEND_STRING_DELAY`](#group__send__string_1ga6cac47ec59654132634c70986202dc42) 

Shortcut macro for send_string_with_delay_P(PSTR(string), interval).

On ARM devices, this define evaluates to send_string_with_delay(string, interval).

#### `public void `[`send_string`](#group__send__string_1gac5e380e2be08c7a8bee8532cc72d8b30)`(const char * string)` 

Type out a string of ASCII characters.

This function simply calls `send_string_with_delay(string, 0)`.

Most keycodes from the basic keycode range are also supported by way of a special sequence - see `[send_string_keycodes.h](#send__string__keycodes_8h_source)`.

#### Parameters
* `string` The string to type out.

#### `public void `[`send_string_with_delay`](#group__send__string_1gaa1d72394f1e4d90a4d789935f947fde6)`(const char * string,uint8_t interval)` 

Type out a string of ASCII characters, with a delay between each character.

#### Parameters
* `string` The string to type out. 

* `interval` The amount of time, in milliseconds, to wait before typing the next character.

#### `public void `[`send_char`](#group__send__string_1gaac462f52e01a0434a3d0d427156f7ba1)`(char ascii_code)` 

Type out an ASCII character.

#### Parameters
* `ascii_code` The character to type.

#### `public void `[`send_dword`](#group__send__string_1gacf74558e7014b43355e61fa7104ffa8c)`(uint32_t number)` 

Type out an eight digit (unsigned 32-bit) hexadecimal value.

The format is `[0-9a-f]{8}`, eg. `00000000` through `ffffffff`.

#### Parameters
* `number` The value to type, from 0 to 4,294,967,295.

#### `public void `[`send_word`](#group__send__string_1ga9ec68473d4b590a48b9d52e35f8aecf3)`(uint16_t number)` 

Type out a four digit (unsigned 16-bit) hexadecimal value.

The format is `[0-9a-f]{4}`, eg. `0000` through `ffff`.

#### Parameters
* `number` The value to type, from 0 to 65,535.

#### `public void `[`send_byte`](#group__send__string_1ga015a1b20ba56c7debe2b4edfed5cb815)`(uint8_t number)` 

Type out a two digit (8-bit) hexadecimal value.

The format is `[0-9a-f]{2}`, eg. `00` through `ff`.

#### Parameters
* `number` The value to type, from 0 to 255.

#### `public void `[`send_nibble`](#group__send__string_1ga34ef35dbde792a44bdb299d10c826675)`(uint8_t number)` 

Type out a single hexadecimal digit.

The format is `[0-9a-f]{1}`, eg. `0` through `f`.

#### Parameters
* `number` The value to type, from 0 to 15.

#### `public void `[`tap_random_base64`](#group__send__string_1ga7cb02fdb6dd1d7babd67df4312a2dab9)`(void)` 

Type a pseudorandom character from the set `A-Z`, `a-z`, `0-9`, `+` and `/`.

#### `public void `[`send_string_P`](#group__send__string_1ga9e99e584dce970f6fe04a63b71cddf4d)`(const char * string)` 

Type out a PROGMEM string of ASCII characters.

On ARM devices, this function is simply an alias for send_string_with_delay(string, 0).

#### Parameters
* `string` The string to type out.

#### `public void `[`send_string_with_delay_P`](#group__send__string_1ga305251111b4454c681027c5bf1c8b60c)`(const char * string,uint8_t interval)` 

Type out a PROGMEM string of ASCII characters, with a delay between each character.

On ARM devices, this function is simply an alias for send_string_with_delay(string, interval).

#### Parameters
* `string` The string to type out. 

* `interval` The amount of time, in milliseconds, to wait before typing the next character.

