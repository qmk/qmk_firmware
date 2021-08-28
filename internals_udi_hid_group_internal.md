# group `udi_hid_group_internal` {#group__udi__hid__group__internal}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public static bool `[`udi_hid_reqstdifaceget_descriptor`](#group__udi__hid__group__internal_1ga0ecbd5a80812ac07a1ee3f890a959640)`(uint8_t * report_desc)`            | Send the specific descriptors requested by SETUP request.
`public bool `[`udi_hid_setup`](#group__udi__hid__group__internal_1ga9594c21fbb713dabebed1c970664680b)`(uint8_t * rate,uint8_t * protocol,uint8_t * report_desc,bool(*)(void) setup_report)`            | Decode HID setup request.

## Members

#### `public static bool `[`udi_hid_reqstdifaceget_descriptor`](#group__udi__hid__group__internal_1ga0ecbd5a80812ac07a1ee3f890a959640)`(uint8_t * report_desc)` {#group__udi__hid__group__internal_1ga0ecbd5a80812ac07a1ee3f890a959640}

Send the specific descriptors requested by SETUP request.

#### Parameters
* `true` if the descriptor is supported

#### `public bool `[`udi_hid_setup`](#group__udi__hid__group__internal_1ga9594c21fbb713dabebed1c970664680b)`(uint8_t * rate,uint8_t * protocol,uint8_t * report_desc,bool(*)(void) setup_report)` {#group__udi__hid__group__internal_1ga9594c21fbb713dabebed1c970664680b}

Decode HID setup request.

#### Parameters
* `rate` Pointer on rate of current HID interface 

* `protocol` Pointer on protocol of current HID interface 

* `report_desc` Pointer on report descriptor of current HID interface 

* `set_report` Pointer on set_report callback of current HID interface

#### Returns
`1` if function was successfully done, otherwise `0`.

