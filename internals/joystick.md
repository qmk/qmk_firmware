# group `joystick` 

HID Joystick

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`JOYSTICK_BUTTON_COUNT`](#group__joystick_1ga3792c81f5808ad4f30000689ee0f0d07)            | 
`define `[`JOYSTICK_AXIS_COUNT`](#group__joystick_1gab8d61934912a07819f6715ec9e54d32c)            | 
`define `[`JOYSTICK_AXIS_RESOLUTION`](#group__joystick_1gaddb4b3e42ee90269812fd0bd9acf21d8)            | 
`define `[`JOYSTICK_MAX_VALUE`](#group__joystick_1ga7084cc64aa477bb62ef80e4c827ebf93)            | 
`define `[`JS_VIRTUAL_AXIS`](#group__joystick_1gadec5fdc9d76e6bc1360c331276e50e87)            | 
`define `[`JOYSTICK_AXIS_VIRTUAL`](#group__joystick_1ga6ac5611ba2703332430aee9606ac30c8)            | 
`define `[`JOYSTICK_AXIS_IN`](#group__joystick_1ga1e985d1ca9689875587c8148bbcd76d4)            | 
`define `[`JOYSTICK_AXIS_IN_OUT`](#group__joystick_1gaca92c20ad4aba8d78e6d048e9189c745)            | 
`define `[`JOYSTICK_AXIS_IN_OUT_GROUND`](#group__joystick_1gae2e481604075d4b4425d5813a8c0c740)            | 
`public void `[`joystick_task`](#group__joystick_1ga8cfa738eaf345576667029cf64247ec1)`(void)`            | 
`public void `[`joystick_flush`](#group__joystick_1ga74d47db58c2ab483351eb4500f0fdd92)`(void)`            | Send the joystick report to the host, if it has been marked as dirty.
`public void `[`register_joystick_button`](#group__joystick_1ga7045cb2fd5477cd11554275fd4630ef6)`(uint8_t button)`            | Set the state of a button, and flush the report.
`public void `[`unregister_joystick_button`](#group__joystick_1ga7fb173dc8d4b68bf518629517d631576)`(uint8_t button)`            | Reset the state of a button, and flush the report.
`public int16_t `[`joystick_read_axis`](#group__joystick_1ga1d149bcbf0587ef5ad514832cc2014b5)`(uint8_t axis)`            | Sample and process the analog value of the given axis.
`public void `[`joystick_read_axes`](#group__joystick_1ga0b0011c0c3b90ed2ac6581218a081740)`(void)`            | 
`public void `[`joystick_set_axis`](#group__joystick_1ga2d3be63c85914d5de96ad1352fd2ff2b)`(uint8_t axis,int16_t value)`            | Set the value of the given axis.
`public void `[`host_joystick_send`](#group__joystick_1ga3ef94672dc82a59587caa6147304041f)`(`[`joystick_t`](.build/docs/internals/joystick.md#structjoystick__t)` * joystick)`            | 
`struct `[`joystick_config_t`](#structjoystick__config__t) | 
`struct `[`joystick_t`](#structjoystick__t) | 

## Members

#### `define `[`JOYSTICK_BUTTON_COUNT`](#group__joystick_1ga3792c81f5808ad4f30000689ee0f0d07) 

#### `define `[`JOYSTICK_AXIS_COUNT`](#group__joystick_1gab8d61934912a07819f6715ec9e54d32c) 

#### `define `[`JOYSTICK_AXIS_RESOLUTION`](#group__joystick_1gaddb4b3e42ee90269812fd0bd9acf21d8) 

#### `define `[`JOYSTICK_MAX_VALUE`](#group__joystick_1ga7084cc64aa477bb62ef80e4c827ebf93) 

#### `define `[`JS_VIRTUAL_AXIS`](#group__joystick_1gadec5fdc9d76e6bc1360c331276e50e87) 

#### `define `[`JOYSTICK_AXIS_VIRTUAL`](#group__joystick_1ga6ac5611ba2703332430aee9606ac30c8) 

#### `define `[`JOYSTICK_AXIS_IN`](#group__joystick_1ga1e985d1ca9689875587c8148bbcd76d4) 

#### `define `[`JOYSTICK_AXIS_IN_OUT`](#group__joystick_1gaca92c20ad4aba8d78e6d048e9189c745) 

#### `define `[`JOYSTICK_AXIS_IN_OUT_GROUND`](#group__joystick_1gae2e481604075d4b4425d5813a8c0c740) 

#### `public void `[`joystick_task`](#group__joystick_1ga8cfa738eaf345576667029cf64247ec1)`(void)` 

#### `public void `[`joystick_flush`](#group__joystick_1ga74d47db58c2ab483351eb4500f0fdd92)`(void)` 

Send the joystick report to the host, if it has been marked as dirty.

#### `public void `[`register_joystick_button`](#group__joystick_1ga7045cb2fd5477cd11554275fd4630ef6)`(uint8_t button)` 

Set the state of a button, and flush the report.

#### Parameters
* `button` The index of the button to press, from 0 to 31.

#### `public void `[`unregister_joystick_button`](#group__joystick_1ga7fb173dc8d4b68bf518629517d631576)`(uint8_t button)` 

Reset the state of a button, and flush the report.

#### Parameters
* `button` The index of the button to release, from 0 to 31.

#### `public int16_t `[`joystick_read_axis`](#group__joystick_1ga1d149bcbf0587ef5ad514832cc2014b5)`(uint8_t axis)` 

Sample and process the analog value of the given axis.

#### Parameters
* `axis` The axis to read.

#### Returns
A signed 16-bit integer, where 0 is the resting or mid point.

#### `public void `[`joystick_read_axes`](#group__joystick_1ga0b0011c0c3b90ed2ac6581218a081740)`(void)` 

#### `public void `[`joystick_set_axis`](#group__joystick_1ga2d3be63c85914d5de96ad1352fd2ff2b)`(uint8_t axis,int16_t value)` 

Set the value of the given axis.

#### Parameters
* `axis` The axis to set the value of. 

* `value` The value to set.

#### `public void `[`host_joystick_send`](#group__joystick_1ga3ef94672dc82a59587caa6147304041f)`(`[`joystick_t`](.build/docs/internals/joystick.md#structjoystick__t)` * joystick)` 

# struct `joystick_config_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public pin_t `[`output_pin`](#structjoystick__config__t_1a933352102e7001dd3ef32ab30626d5d9) | 
`public pin_t `[`input_pin`](#structjoystick__config__t_1a618b5e95bb730a44349ee0cc0a9ead2b) | 
`public pin_t `[`ground_pin`](#structjoystick__config__t_1a68d0d2868fb6174cd8f5d4e4484e761c) | 
`public uint16_t `[`min_digit`](#structjoystick__config__t_1a58f2a813b3bd682d8e0832901717ae0a) | 
`public uint16_t `[`mid_digit`](#structjoystick__config__t_1aabf753cef243f656f9dcf1f8416cd019) | 
`public uint16_t `[`max_digit`](#structjoystick__config__t_1a5efa9ac6ea984ad8f980cc83dd64215b) | 

## Members

#### `public pin_t `[`output_pin`](#structjoystick__config__t_1a933352102e7001dd3ef32ab30626d5d9) 

#### `public pin_t `[`input_pin`](#structjoystick__config__t_1a618b5e95bb730a44349ee0cc0a9ead2b) 

#### `public pin_t `[`ground_pin`](#structjoystick__config__t_1a68d0d2868fb6174cd8f5d4e4484e761c) 

#### `public uint16_t `[`min_digit`](#structjoystick__config__t_1a58f2a813b3bd682d8e0832901717ae0a) 

#### `public uint16_t `[`mid_digit`](#structjoystick__config__t_1aabf753cef243f656f9dcf1f8416cd019) 

#### `public uint16_t `[`max_digit`](#structjoystick__config__t_1a5efa9ac6ea984ad8f980cc83dd64215b) 

# struct `joystick_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`buttons`](#structjoystick__t_1aac061683d3987491e9f2547b1b1aff3d) | 
`public int16_t `[`axes`](#structjoystick__t_1ad27ebfc17a6488794bafecaf2d71eb46) | 
`public bool `[`dirty`](#structjoystick__t_1ad25edacba00e4d0666a9959053b7cc10) | 

## Members

#### `public uint8_t `[`buttons`](#structjoystick__t_1aac061683d3987491e9f2547b1b1aff3d) 

#### `public int16_t `[`axes`](#structjoystick__t_1ad27ebfc17a6488794bafecaf2d71eb46) 

#### `public bool `[`dirty`](#structjoystick__t_1ad25edacba00e4d0666a9959053b7cc10) 

