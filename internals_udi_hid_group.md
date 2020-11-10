# group `udi_hid_group` {#group__udi__hid__group}

Common library for all Human Interface Device ([HID](.build/docs/internals_undefined.md#class_h_i_d)) implementation.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`udi_hid_setup`](#group__udi__hid__group_1ga9594c21fbb713dabebed1c970664680b)`(uint8_t * rate,uint8_t * protocol,uint8_t * report_desc,bool(*)(void) setup_report)`            | Decode [HID](.build/docs/internals_undefined.md#class_h_i_d) setup request.

## Members

#### `public bool `[`udi_hid_setup`](#group__udi__hid__group_1ga9594c21fbb713dabebed1c970664680b)`(uint8_t * rate,uint8_t * protocol,uint8_t * report_desc,bool(*)(void) setup_report)` {#group__udi__hid__group_1ga9594c21fbb713dabebed1c970664680b}

Decode [HID](.build/docs/internals_undefined.md#class_h_i_d) setup request.

#### Parameters
* `rate` Pointer on rate of current [HID](.build/docs/internals_undefined.md#class_h_i_d) interface 

* `protocol` Pointer on protocol of current [HID](.build/docs/internals_undefined.md#class_h_i_d) interface 

* `report_desc` Pointer on report descriptor of current [HID](.build/docs/internals_undefined.md#class_h_i_d) interface 

* `set_report` Pointer on set_report callback of current [HID](.build/docs/internals_undefined.md#class_h_i_d) interface

#### Returns
`1` if function was successfully done, otherwise `0`.

