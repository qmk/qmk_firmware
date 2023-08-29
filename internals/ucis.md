# group `ucis` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`UCIS_MAX_INPUT_LENGTH`](#group__ucis_1ga73e9023ff14efb3cba312ea1e77135dc)            | 
`define `[`UCIS_MAX_CODE_POINTS`](#group__ucis_1ga0616160474ddd884e704c1e8c2bac310)            | 
`define `[`UCIS_TABLE`](#group__ucis_1ga590d8e3349fc2e3a61b4cbef5ea2ceb2)            | 
`define `[`UCIS_SYM`](#group__ucis_1ga92cb8820d5a2619d51ded3cf3703d822)            | 
`public void `[`ucis_start`](#group__ucis_1ga24f5ad4abb77ce169249fe08b05808d6)`(void)`            | Begin the input sequence.
`public bool `[`ucis_active`](#group__ucis_1gab95904598448c3cee70267e467ff6632)`(void)`            | Whether UCIS is currently active.
`public uint8_t `[`ucis_count`](#group__ucis_1ga16e22f4f2c0548267bf5a402ced55a84)`(void)`            | Get the number of characters in the input sequence buffer.
`public bool `[`ucis_add`](#group__ucis_1ga5c83053fee50b4e2be7ba5216f958c00)`(uint16_t keycode)`            | Add the given keycode to the input sequence buffer.
`public bool `[`ucis_remove_last`](#group__ucis_1ga0ddf9bda327e02ba2a638628a5601767)`(void)`            | Remove the last character from the input sequence.
`public void `[`ucis_finish`](#group__ucis_1ga153d42bfafc6a4f14b3cd00148d88a96)`(void)`            | Mark the input sequence as complete, and attempt to match.
`public void `[`ucis_cancel`](#group__ucis_1ga09967a54ced333cd14d6c6cf02758595)`(void)`            | Cancel the input sequence.
`public void `[`register_ucis`](#group__ucis_1ga7d0e659a28d1aac67930ebec4b240265)`(uint8_t index)`            | Send the code point(s) for the given UCIS index.
`struct `[`ucis_symbol_t`](#structucis__symbol__t) | 

## Members

#### `define `[`UCIS_MAX_INPUT_LENGTH`](#group__ucis_1ga73e9023ff14efb3cba312ea1e77135dc) 

#### `define `[`UCIS_MAX_CODE_POINTS`](#group__ucis_1ga0616160474ddd884e704c1e8c2bac310) 

#### `define `[`UCIS_TABLE`](#group__ucis_1ga590d8e3349fc2e3a61b4cbef5ea2ceb2) 

#### `define `[`UCIS_SYM`](#group__ucis_1ga92cb8820d5a2619d51ded3cf3703d822) 

#### `public void `[`ucis_start`](#group__ucis_1ga24f5ad4abb77ce169249fe08b05808d6)`(void)` 

Begin the input sequence.

#### `public bool `[`ucis_active`](#group__ucis_1gab95904598448c3cee70267e467ff6632)`(void)` 

Whether UCIS is currently active.

#### Returns
`true` if UCIS is active.

#### `public uint8_t `[`ucis_count`](#group__ucis_1ga16e22f4f2c0548267bf5a402ced55a84)`(void)` 

Get the number of characters in the input sequence buffer.

#### Returns
The current input sequence buffer length.

#### `public bool `[`ucis_add`](#group__ucis_1ga5c83053fee50b4e2be7ba5216f958c00)`(uint16_t keycode)` 

Add the given keycode to the input sequence buffer.

#### Parameters
* `keycode` The keycode to add. Must be between `KC_A` and `KC_Z`, or `KC_1` and `KC_0`.

#### Returns
`true` if the keycode was added.

#### `public bool `[`ucis_remove_last`](#group__ucis_1ga0ddf9bda327e02ba2a638628a5601767)`(void)` 

Remove the last character from the input sequence.

#### Returns
`true` if the sequence was not empty.

#### `public void `[`ucis_finish`](#group__ucis_1ga153d42bfafc6a4f14b3cd00148d88a96)`(void)` 

Mark the input sequence as complete, and attempt to match.

#### `public void `[`ucis_cancel`](#group__ucis_1ga09967a54ced333cd14d6c6cf02758595)`(void)` 

Cancel the input sequence.

#### `public void `[`register_ucis`](#group__ucis_1ga7d0e659a28d1aac67930ebec4b240265)`(uint8_t index)` 

Send the code point(s) for the given UCIS index.

#### Parameters
* `index` The index into the UCIS symbol table.

# struct `ucis_symbol_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public char * `[`mnemonic`](#structucis__symbol__t_1ae2f07a7a5599d68570038f803c6951ca) | 
`public uint32_t `[`code_points`](#structucis__symbol__t_1abd2bf47d0342135474193ccb8f3e67f7) | 

## Members

#### `public char * `[`mnemonic`](#structucis__symbol__t_1ae2f07a7a5599d68570038f803c6951ca) 

#### `public uint32_t `[`code_points`](#structucis__symbol__t_1abd2bf47d0342135474193ccb8f3e67f7) 

