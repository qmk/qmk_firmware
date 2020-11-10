# group `udd_group` {#group__udd__group}

The UDD driver provides a low-level abstraction of the device controller hardware. Most events coming from the hardware such as interrupts, which may cause the UDD to call into the UDC and UDI.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`Udd_setup_is_in`](#group__udd__group_1gaffd9b7cf165cd149868373fa12595d12)            | Return true if the setup request *udd_g_ctrlreq* indicates IN data transfer.
`define `[`Udd_setup_is_out`](#group__udd__group_1gaf67b7c8de30fdc881b567385f2345926)            | Return true if the setup request *udd_g_ctrlreq* indicates OUT data transfer.
`define `[`Udd_setup_type`](#group__udd__group_1ga85dc2b7b6c270e8dd8323fa4779a7ca2)            | Return the type of the SETUP request *udd_g_ctrlreq*.
`define `[`Udd_setup_recipient`](#group__udd__group_1gac963bb7b8a965c2fec45a71c9faca6f5)            | Return the recipient of the SETUP request *udd_g_ctrlreq*.
`enum `[`udd_ep_status_t`](#group__udd__group_1gac0f77f5a0e085af1242b48fd1054959a)            | Endpoint transfer status Returned in parameters of callback register via udd_ep_run routine.
`public bool `[`udd_include_vbus_monitoring`](#group__udd__group_1gaa4cac8c35ae056e26cf4ab5b426bbe09)`(void)`            | Authorizes the VBUS event.
`public void `[`udd_enable`](#group__udd__group_1ga9792d1899ae058e3984d6a622fe2ad42)`(void)`            | Enables the USB Device mode.
`public void `[`udd_disable`](#group__udd__group_1gab283432057b934e9d73ac9282d9b0f11)`(void)`            | Disables the USB Device mode.
`public void `[`udd_attach`](#group__udd__group_1ga7a7c0d9236c922c2af33c6702565a99f)`(void)`            | Attach device to the bus when possible.
`public void `[`udd_detach`](#group__udd__group_1ga03e59eaa264f1dbe5a52559311d0520e)`(void)`            | Detaches the device from the bus.
`public bool `[`udd_is_high_speed`](#group__udd__group_1ga85f403ddb78776b1ba014dafd3ffec2c)`(void)`            | Test whether the USB Device Controller is running at high speed or not.
`public void `[`udd_set_address`](#group__udd__group_1ga05da762e0faf9d478e532de40afa71f6)`(uint8_t address)`            | Changes the USB address of device.
`public uint8_t `[`udd_getaddress`](#group__udd__group_1gaebd36638d482f6df00a8aff006ef2246)`(void)`            | Returns the USB address of device.
`public uint16_t `[`udd_get_frame_number`](#group__udd__group_1ga96dc248cc05e07ffe2cf21e4d7465320)`(void)`            | Returns the current start of frame number.
`public uint16_t `[`udd_get_micro_frame_number`](#group__udd__group_1ga63047eec59b8e8798ca1d3366472d82b)`(void)`            | Returns the current micro start of frame number.
`public void `[`udd_send_remotewakeup`](#group__udd__group_1gac447212e04789282dabee65a23fe2a08)`(void)`            | The USB driver sends a resume signal called Upstream Resume.
`public void `[`udd_set_setup_payload`](#group__udd__group_1ga017ef5ea7626be258c24d345218976f9)`(uint8_t * payload,uint16_t payload_size)`            | Load setup payload.
`struct `[`udd_ctrl_request_t`](#structudd__ctrl__request__t) | Global variable to give and record information of the setup request management.

## Members

#### `define `[`Udd_setup_is_in`](#group__udd__group_1gaffd9b7cf165cd149868373fa12595d12) {#group__udd__group_1gaffd9b7cf165cd149868373fa12595d12}

Return true if the setup request *udd_g_ctrlreq* indicates IN data transfer.

#### `define `[`Udd_setup_is_out`](#group__udd__group_1gaf67b7c8de30fdc881b567385f2345926) {#group__udd__group_1gaf67b7c8de30fdc881b567385f2345926}

Return true if the setup request *udd_g_ctrlreq* indicates OUT data transfer.

#### `define `[`Udd_setup_type`](#group__udd__group_1ga85dc2b7b6c270e8dd8323fa4779a7ca2) {#group__udd__group_1ga85dc2b7b6c270e8dd8323fa4779a7ca2}

Return the type of the SETUP request *udd_g_ctrlreq*.

**See also**: usb_reqtype.

#### `define `[`Udd_setup_recipient`](#group__udd__group_1gac963bb7b8a965c2fec45a71c9faca6f5) {#group__udd__group_1gac963bb7b8a965c2fec45a71c9faca6f5}

Return the recipient of the SETUP request *udd_g_ctrlreq*.

**See also**: usb_recipient

#### `enum `[`udd_ep_status_t`](#group__udd__group_1gac0f77f5a0e085af1242b48fd1054959a) {#group__udd__group_1gac0f77f5a0e085af1242b48fd1054959a}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
UDD_EP_TRANSFER_OK            | 
UDD_EP_TRANSFER_ABORT            | 

Endpoint transfer status Returned in parameters of callback register via udd_ep_run routine.

#### `public bool `[`udd_include_vbus_monitoring`](#group__udd__group_1gaa4cac8c35ae056e26cf4ab5b426bbe09)`(void)` {#group__udd__group_1gaa4cac8c35ae056e26cf4ab5b426bbe09}

Authorizes the VBUS event.

#### Returns
true, if the VBUS monitoring is possible.

#### `public void `[`udd_enable`](#group__udd__group_1ga9792d1899ae058e3984d6a622fe2ad42)`(void)` {#group__udd__group_1ga9792d1899ae058e3984d6a622fe2ad42}

Enables the USB Device mode.

#### `public void `[`udd_disable`](#group__udd__group_1gab283432057b934e9d73ac9282d9b0f11)`(void)` {#group__udd__group_1gab283432057b934e9d73ac9282d9b0f11}

Disables the USB Device mode.

#### `public void `[`udd_attach`](#group__udd__group_1ga7a7c0d9236c922c2af33c6702565a99f)`(void)` {#group__udd__group_1ga7a7c0d9236c922c2af33c6702565a99f}

Attach device to the bus when possible.

If a VBus control is included in driver, then it will attach device when an acceptable Vbus level from the host is detected.

#### `public void `[`udd_detach`](#group__udd__group_1ga03e59eaa264f1dbe5a52559311d0520e)`(void)` {#group__udd__group_1ga03e59eaa264f1dbe5a52559311d0520e}

Detaches the device from the bus.

The driver must remove pull-up on USB line D- or D+.

#### `public bool `[`udd_is_high_speed`](#group__udd__group_1ga85f403ddb78776b1ba014dafd3ffec2c)`(void)` {#group__udd__group_1ga85f403ddb78776b1ba014dafd3ffec2c}

Test whether the USB Device Controller is running at high speed or not.

#### Returns
`true` if the Device is running at high speed mode, otherwise `false`.

#### `public void `[`udd_set_address`](#group__udd__group_1ga05da762e0faf9d478e532de40afa71f6)`(uint8_t address)` {#group__udd__group_1ga05da762e0faf9d478e532de40afa71f6}

Changes the USB address of device.

#### Parameters
* `address` New USB address

#### `public uint8_t `[`udd_getaddress`](#group__udd__group_1gaebd36638d482f6df00a8aff006ef2246)`(void)` {#group__udd__group_1gaebd36638d482f6df00a8aff006ef2246}

Returns the USB address of device.

#### Returns
USB address

#### `public uint16_t `[`udd_get_frame_number`](#group__udd__group_1ga96dc248cc05e07ffe2cf21e4d7465320)`(void)` {#group__udd__group_1ga96dc248cc05e07ffe2cf21e4d7465320}

Returns the current start of frame number.

#### Returns
current start of frame number.

#### `public uint16_t `[`udd_get_micro_frame_number`](#group__udd__group_1ga63047eec59b8e8798ca1d3366472d82b)`(void)` {#group__udd__group_1ga63047eec59b8e8798ca1d3366472d82b}

Returns the current micro start of frame number.

#### Returns
current micro start of frame number required in high speed mode.

#### `public void `[`udd_send_remotewakeup`](#group__udd__group_1gac447212e04789282dabee65a23fe2a08)`(void)` {#group__udd__group_1gac447212e04789282dabee65a23fe2a08}

The USB driver sends a resume signal called Upstream Resume.

#### `public void `[`udd_set_setup_payload`](#group__udd__group_1ga017ef5ea7626be258c24d345218976f9)`(uint8_t * payload,uint16_t payload_size)` {#group__udd__group_1ga017ef5ea7626be258c24d345218976f9}

Load setup payload.

#### Parameters
* `payload` Pointer on payload 

* `payload_size` Size of payload

# struct `udd_ctrl_request_t` {#structudd__ctrl__request__t}

Global variable to give and record information of the setup request management.

This global variable allows to decode and response a setup request. It can be updated by [udc_process_setup()](.build/docs/internals_undefined.md#group__udc__group__interne_1ga58c2916d7984e0e5b2143cadf4af6080) from UDC or *setup() from UDIs.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`usb_setup_req_t`](.build/docs/internals_usb_protocol_group.md#structusb__setup__req__t)` `[`req`](#structudd__ctrl__request__t_1a8ca591128eb7000ed02f8cc730af6e69) | Data received in USB SETUP packet Note: The swap of "req.wValues" from uin16_t to le16_t is done by UDD.
`public uint8_t * `[`payload`](#structudd__ctrl__request__t_1aa5cbdad2c57e9b3f949e1a4d96382b66) | [Point](.build/docs/internals_undefined.md#struct_point) to buffer to send or fill with data following SETUP packet This buffer must be word align for DATA IN phase (use prefix COMPILER_WORD_ALIGNED for buffer)
`public uint16_t `[`payload_size`](#structudd__ctrl__request__t_1a34d21baa46ca7f4b695307631457c75f) | Size of buffer to send or fill, and content the number of byte transfered.
`public void(* `[`callback`](#structudd__ctrl__request__t_1a11f084a69a85b6e1da79695b6a3d07c3) | Callback called after reception of ZLP from setup request.
`public bool(* `[`over_under_run`](#structudd__ctrl__request__t_1a3d31b0db5458678975632d6b5815ea8c) | Callback called when the buffer given (.payload) is full or empty. This one return false to abort data transfer, or true with a new buffer in .payload.

## Members

#### `public `[`usb_setup_req_t`](.build/docs/internals_usb_protocol_group.md#structusb__setup__req__t)` `[`req`](#structudd__ctrl__request__t_1a8ca591128eb7000ed02f8cc730af6e69) {#structudd__ctrl__request__t_1a8ca591128eb7000ed02f8cc730af6e69}

Data received in USB SETUP packet Note: The swap of "req.wValues" from uin16_t to le16_t is done by UDD.

#### `public uint8_t * `[`payload`](#structudd__ctrl__request__t_1aa5cbdad2c57e9b3f949e1a4d96382b66) {#structudd__ctrl__request__t_1aa5cbdad2c57e9b3f949e1a4d96382b66}

[Point](.build/docs/internals_undefined.md#struct_point) to buffer to send or fill with data following SETUP packet This buffer must be word align for DATA IN phase (use prefix COMPILER_WORD_ALIGNED for buffer)

#### `public uint16_t `[`payload_size`](#structudd__ctrl__request__t_1a34d21baa46ca7f4b695307631457c75f) {#structudd__ctrl__request__t_1a34d21baa46ca7f4b695307631457c75f}

Size of buffer to send or fill, and content the number of byte transfered.

#### `public void(* `[`callback`](#structudd__ctrl__request__t_1a11f084a69a85b6e1da79695b6a3d07c3) {#structudd__ctrl__request__t_1a11f084a69a85b6e1da79695b6a3d07c3}

Callback called after reception of ZLP from setup request.

#### `public bool(* `[`over_under_run`](#structudd__ctrl__request__t_1a3d31b0db5458678975632d6b5815ea8c) {#structudd__ctrl__request__t_1a3d31b0db5458678975632d6b5815ea8c}

Callback called when the buffer given (.payload) is full or empty. This one return false to abort data transfer, or true with a new buffer in .payload.

