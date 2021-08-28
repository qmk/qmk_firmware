# group `udi_hid_group` {#group__udi__hid__group}

Common library for all Human Interface Device (HID) implementation.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`udi_hid_setup`](#group__udi__hid__group_1ga9594c21fbb713dabebed1c970664680b)`(uint8_t * rate,uint8_t * protocol,uint8_t * report_desc,bool(*)(void) setup_report)`            | Decode HID setup request.

## Members

#### `public bool `[`udi_hid_setup`](#group__udi__hid__group_1ga9594c21fbb713dabebed1c970664680b)`(uint8_t * rate,uint8_t * protocol,uint8_t * report_desc,bool(*)(void) setup_report)` {#group__udi__hid__group_1ga9594c21fbb713dabebed1c970664680b}

Decode HID setup request.

#### Parameters
* `rate` Pointer on rate of current HID interface 

* `protocol` Pointer on protocol of current HID interface 

* `report_desc` Pointer on report descriptor of current HID interface 

* `set_report` Pointer on set_report callback of current HID interface

#### Returns
`1` if function was successfully done, otherwise `0`.

