# group `unicodemap` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`unicodemap_index`](#group__unicodemap_1gaf2e331f270db9f276cf7cb3977384712)`(uint16_t keycode)`            | Get the index into the `unicode_map` array for the given keycode, respecting shift state for pair keycodes.
`public uint32_t `[`unicodemap_get_code_point`](#group__unicodemap_1gae3d21f90ee76bce7c12336d6e727b73a)`(uint8_t index)`            | Get the code point for the given index in the `unicode_map` array.
`public void `[`register_unicodemap`](#group__unicodemap_1gaf76d22d6821316d4e25782ace183e58d)`(uint8_t index)`            | Send the code point for the given index in the `unicode_map` array.

## Members

#### `public uint8_t `[`unicodemap_index`](#group__unicodemap_1gaf2e331f270db9f276cf7cb3977384712)`(uint16_t keycode)` 

Get the index into the `unicode_map` array for the given keycode, respecting shift state for pair keycodes.

#### Parameters
* `keycode` The Unicode Map keycode to get the index of.

#### Returns
An index into the `unicode_map` array.

#### `public uint32_t `[`unicodemap_get_code_point`](#group__unicodemap_1gae3d21f90ee76bce7c12336d6e727b73a)`(uint8_t index)` 

Get the code point for the given index in the `unicode_map` array.

#### Parameters
* `index` The index into the `unicode_map` array.

#### Returns
A Unicode code point value.

#### `public void `[`register_unicodemap`](#group__unicodemap_1gaf76d22d6821316d4e25782ace183e58d)`(uint8_t index)` 

Send the code point for the given index in the `unicode_map` array.

#### Parameters
* `index` The index into the `unicode_map` array.

