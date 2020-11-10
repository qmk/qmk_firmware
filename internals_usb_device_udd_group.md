# group `usb_device_udd_group` {#group__usb__device__udd__group}

USB low-level driver for USB device mode

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`UDC_REMOTEWAKEUP_LPM_ENABLE`](#group__usb__device__udd__group_1gaad02b98c5c4188ff50fd72c81e6bfa20)            | 
`define `[`UDC_REMOTEWAKEUP_LPM_DISABLE`](#group__usb__device__udd__group_1gabd679a48d3828303b04b4e56b5e92481)            | 
`define `[`UDC_SUSPEND_LPM_EVENT`](#group__usb__device__udd__group_1gaad464bdb9c5a422a2f337b6367114db6)            | 
`define `[`dbg_print`](#group__usb__device__udd__group_1gac0876bf5bac7dfffd0ee0b003cdc76ef)            | 
`define `[`UDD_ENDPOINT_MAX_TRANS`](#group__usb__device__udd__group_1ga9b73a2cd4488b39038d49d865e03fe0e)            | Maximum size of a transfer in multi-packet mode
`public static udd_ep_job_t * `[`udd_ep_get_job`](#group__usb__device__udd__group_1ga44d7180f54df872da50d8d04918fc5c7)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)`            | Get the detailed job by endpoint number.
`public static void `[`udd_ep_trans_in_next`](#group__usb__device__udd__group_1ga7cd1ac3f0e6071afa036e27c5bd4d33c)`(void * pointer)`            | Endpoint IN process, continue to send packets or zero length packet.
`public static void `[`udd_ep_trans_out_next`](#group__usb__device__udd__group_1ga2c2140346e2f4ef3b07e36d2abf2de5e)`(void * pointer)`            | Endpoint OUT process, continue to receive packets or zero length packet.
`public static void `[`udd_ep_transfer_process`](#group__usb__device__udd__group_1gaa3607835799fb01db3d38bcbc87463fb)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)`            | Endpoint Transfer Complete callback function, to do the next transfer depends on the direction(IN or OUT)
`public void `[`udd_ep_abort`](#group__usb__device__udd__group_1gaacd4ece19accac669506b615916efe2f)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)`            | Aborts transfer on going on endpoint.
`public bool `[`udd_is_high_speed`](#group__usb__device__udd__group_1ga85f403ddb78776b1ba014dafd3ffec2c)`(void)`            | Test whether the USB Device Controller is running at high speed or not.
`public uint16_t `[`udd_get_frame_number`](#group__usb__device__udd__group_1ga96dc248cc05e07ffe2cf21e4d7465320)`(void)`            | Returns the current start of frame number.
`public uint16_t `[`udd_get_micro_frame_number`](#group__usb__device__udd__group_1ga63047eec59b8e8798ca1d3366472d82b)`(void)`            | Returns the current micro start of frame number.
`public void `[`udd_ep_free`](#group__usb__device__udd__group_1ga12c064720e08b9151e2a47f79d986c29)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)`            | Disables an endpoint.
`public bool `[`udd_ep_alloc`](#group__usb__device__udd__group_1gaf87db391732b278915079b43ce20a4c1)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep,uint8_t bmAttributes,uint16_t MaxEndpointSize)`            | Configures and enables an endpoint.
`public bool `[`udd_ep_is_halted`](#group__usb__device__udd__group_1ga2d531ac8c1e142185c6ed6eaeb2737c0)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)`            | Check if the endpoint *ep* is halted.
`public bool `[`udd_ep_set_halt`](#group__usb__device__udd__group_1ga55dd14b9b00781223e39c2549ffdb61c)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)`            | Set the halted state of the endpoint *ep*.
`public bool `[`udd_ep_clear_halt`](#group__usb__device__udd__group_1ga2b89e75674bd590432e9928326d5ef73)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)`            | Clear the halted state of the endpoint *ep*.
`public bool `[`udd_ep_wait_stall_clear`](#group__usb__device__udd__group_1ga9dde9a9ac41ffc519cc2e2f93308db1c)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep,`[`udd_callback_halt_cleared_t`](.build/docs/internals_undefined.md#group__udd__group_1ga70b1655bda30b7d03df637a1bb23bdd5)` callback)`            | Registers a callback to call when endpoint halt is cleared.
`public static void `[`udd_ctrl_stall_data`](#group__usb__device__udd__group_1gabf919b71cee71a11e1ea4e64fb9891d1)`(void)`            | Control Endpoint stall sending data.
`public bool `[`udd_ep_run`](#group__usb__device__udd__group_1ga3023b640115dd86dc922fcd79f5b8757)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep,bool b_shortpacket,uint8_t * buf,iram_size_t buf_size,`[`udd_callback_trans_t`](.build/docs/internals_undefined.md#group__udd__group_1ga4e79edfc4d62b203dbc271e80a624917)` callback)`            | Allows to receive or send data on an endpoint.
`public void `[`udd_set_address`](#group__usb__device__udd__group_1ga05da762e0faf9d478e532de40afa71f6)`(uint8_t address)`            | Changes the USB address of device.
`public uint8_t `[`udd_getaddress`](#group__usb__device__udd__group_1gaebd36638d482f6df00a8aff006ef2246)`(void)`            | Returns the USB address of device.
`public void `[`udd_send_remotewakeup`](#group__usb__device__udd__group_1gac447212e04789282dabee65a23fe2a08)`(void)`            | The USB driver sends a resume signal called Upstream Resume.
`public void `[`udd_set_setup_payload`](#group__usb__device__udd__group_1ga017ef5ea7626be258c24d345218976f9)`(uint8_t * payload,uint16_t payload_size)`            | Load setup payload.
`public static void `[`udd_ctrl_fetch_ram`](#group__usb__device__udd__group_1gaf6ffb95ec28493ddaf038642ee995ce6)`(void)`            | Control Endpoint translate the data in buffer into Device Request Struct.
`public static void `[`udd_ctrl_send_zlp_in`](#group__usb__device__udd__group_1gab6a8abd5db8a94d6becc73b2b70dc748)`(void)`            | Control Endpoint send out zero length packet.
`public static void `[`udd_ctrl_in_sent`](#group__usb__device__udd__group_1ga181ffd0cddf5130f55df6df8ca3f916c)`(void)`            | Process control endpoint IN transaction.
`public static void `[`udd_ctrl_out_received`](#group__usb__device__udd__group_1gaa137563d9a7717c634279ad596fbc5fb)`(void * pointer)`            | Process control endpoint OUT transaction.
`public static void `[`_usb_ep0_on_setup`](#group__usb__device__udd__group_1ga2f36d2d5628b8edfaf619bcb2c7de44f)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)`            | 
`public static void `[`udd_ctrl_underflow`](#group__usb__device__udd__group_1gae49bae7d7d68329b1c050f39c902d08e)`(void * pointer)`            | Control Endpoint Process when underflow condition has occurred.
`public static void `[`udd_ctrl_overflow`](#group__usb__device__udd__group_1ga58ec0c5b490824774f753cc9ff6c1250)`(void * pointer)`            | Control Endpoint Process when overflow condition has occurred.
`public static void `[`_usb_ep0_on_tansfer_fail`](#group__usb__device__udd__group_1ga67ec9c51a13358e3e241b2d10b3b4a05)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)`            | 
`public static void `[`_usb_ep0_on_tansfer_ok`](#group__usb__device__udd__group_1gabe51608c4f3fb3cb905463758645127c)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)`            | 
`public static void `[`udd_ctrl_ep_enable`](#group__usb__device__udd__group_1ga16a526f9870d3b670345b98bcfbe166c)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst)`            | Enable Control Endpoint.
`public static void `[`_usb_on_suspend`](#group__usb__device__udd__group_1gaf4c2f4bf0f76bcf873d165f1e960c8e1)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)`            | 
`public static void `[`_usb_on_sof_notify`](#group__usb__device__udd__group_1gae65a2792570d8aec7e758b3526721086)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)`            | 
`public static void `[`_usb_on_bus_reset`](#group__usb__device__udd__group_1gaf286144a1b50b68ed2edd38d67e1f4b0)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)`            | 
`public static void `[`_usb_on_wakeup`](#group__usb__device__udd__group_1ga563d04cd60d478a430261aaa9da5e07a)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)`            | 
`public void `[`udd_detach`](#group__usb__device__udd__group_1ga03e59eaa264f1dbe5a52559311d0520e)`(void)`            | Detaches the device from the bus.
`public void `[`udd_attach`](#group__usb__device__udd__group_1ga7a7c0d9236c922c2af33c6702565a99f)`(void)`            | Attach device to the bus when possible.
`public void `[`udd_enable`](#group__usb__device__udd__group_1ga9792d1899ae058e3984d6a622fe2ad42)`(void)`            | Enables the USB Device mode.
`public void `[`udd_disable`](#group__usb__device__udd__group_1gab283432057b934e9d73ac9282d9b0f11)`(void)`            | Disables the USB Device mode.

## Members

#### `define `[`UDC_REMOTEWAKEUP_LPM_ENABLE`](#group__usb__device__udd__group_1gaad02b98c5c4188ff50fd72c81e6bfa20) {#group__usb__device__udd__group_1gaad02b98c5c4188ff50fd72c81e6bfa20}

#### `define `[`UDC_REMOTEWAKEUP_LPM_DISABLE`](#group__usb__device__udd__group_1gabd679a48d3828303b04b4e56b5e92481) {#group__usb__device__udd__group_1gabd679a48d3828303b04b4e56b5e92481}

#### `define `[`UDC_SUSPEND_LPM_EVENT`](#group__usb__device__udd__group_1gaad464bdb9c5a422a2f337b6367114db6) {#group__usb__device__udd__group_1gaad464bdb9c5a422a2f337b6367114db6}

#### `define `[`dbg_print`](#group__usb__device__udd__group_1gac0876bf5bac7dfffd0ee0b003cdc76ef) {#group__usb__device__udd__group_1gac0876bf5bac7dfffd0ee0b003cdc76ef}

#### `define `[`UDD_ENDPOINT_MAX_TRANS`](#group__usb__device__udd__group_1ga9b73a2cd4488b39038d49d865e03fe0e) {#group__usb__device__udd__group_1ga9b73a2cd4488b39038d49d865e03fe0e}

Maximum size of a transfer in multi-packet mode

#### `public static udd_ep_job_t * `[`udd_ep_get_job`](#group__usb__device__udd__group_1ga44d7180f54df872da50d8d04918fc5c7)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)` {#group__usb__device__udd__group_1ga44d7180f54df872da50d8d04918fc5c7}

Get the detailed job by endpoint number.

#### Parameters
* `ep` Endpoint Address 

#### Parameters
* `pointer` to an udd_ep_job_t structure instance

#### `public static void `[`udd_ep_trans_in_next`](#group__usb__device__udd__group_1ga7cd1ac3f0e6071afa036e27c5bd4d33c)`(void * pointer)` {#group__usb__device__udd__group_1ga7cd1ac3f0e6071afa036e27c5bd4d33c}

Endpoint IN process, continue to send packets or zero length packet.

#### Parameters
* `pointer` Pointer to the endpoint transfer status parameter struct from driver layer.

#### `public static void `[`udd_ep_trans_out_next`](#group__usb__device__udd__group_1ga2c2140346e2f4ef3b07e36d2abf2de5e)`(void * pointer)` {#group__usb__device__udd__group_1ga2c2140346e2f4ef3b07e36d2abf2de5e}

Endpoint OUT process, continue to receive packets or zero length packet.

#### Parameters
* `pointer` Pointer to the endpoint transfer status parameter struct from driver layer.

#### `public static void `[`udd_ep_transfer_process`](#group__usb__device__udd__group_1gaa3607835799fb01db3d38bcbc87463fb)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)` {#group__usb__device__udd__group_1gaa3607835799fb01db3d38bcbc87463fb}

Endpoint Transfer Complete callback function, to do the next transfer depends on the direction(IN or OUT)

#### Parameters
* `module_inst` Pointer to USB module instance 

* `pointer` Pointer to the endpoint transfer status parameter struct from driver layer.

#### `public void `[`udd_ep_abort`](#group__usb__device__udd__group_1gaacd4ece19accac669506b615916efe2f)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)` {#group__usb__device__udd__group_1gaacd4ece19accac669506b615916efe2f}

Aborts transfer on going on endpoint.

If a transfer is on going, then it is stopped and the callback registered is called to signal the end of transfer. Note: The control endpoint is not authorized.

#### Parameters
* `ep` Endpoint to abort

#### `public bool `[`udd_is_high_speed`](#group__usb__device__udd__group_1ga85f403ddb78776b1ba014dafd3ffec2c)`(void)` {#group__usb__device__udd__group_1ga85f403ddb78776b1ba014dafd3ffec2c}

Test whether the USB Device Controller is running at high speed or not.

#### Returns
`true` if the Device is running at high speed mode, otherwise `false`.

#### `public uint16_t `[`udd_get_frame_number`](#group__usb__device__udd__group_1ga96dc248cc05e07ffe2cf21e4d7465320)`(void)` {#group__usb__device__udd__group_1ga96dc248cc05e07ffe2cf21e4d7465320}

Returns the current start of frame number.

#### Returns
current start of frame number.

#### `public uint16_t `[`udd_get_micro_frame_number`](#group__usb__device__udd__group_1ga63047eec59b8e8798ca1d3366472d82b)`(void)` {#group__usb__device__udd__group_1ga63047eec59b8e8798ca1d3366472d82b}

Returns the current micro start of frame number.

#### Returns
current micro start of frame number required in high speed mode.

#### `public void `[`udd_ep_free`](#group__usb__device__udd__group_1ga12c064720e08b9151e2a47f79d986c29)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)` {#group__usb__device__udd__group_1ga12c064720e08b9151e2a47f79d986c29}

Disables an endpoint.

#### Parameters
* `ep` Endpoint number including direction (USB_EP_DIR_IN/USB_EP_DIR_OUT).

#### `public bool `[`udd_ep_alloc`](#group__usb__device__udd__group_1gaf87db391732b278915079b43ce20a4c1)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep,uint8_t bmAttributes,uint16_t MaxEndpointSize)` {#group__usb__device__udd__group_1gaf87db391732b278915079b43ce20a4c1}

Configures and enables an endpoint.

#### Parameters
* `ep` Endpoint number including direction (USB_EP_DIR_IN/USB_EP_DIR_OUT). 

* `bmAttributes` Attributes of endpoint declared in the descriptor. 

* `MaxEndpointSize` Endpoint maximum size

#### Returns
`1` if the endpoint is enabled, otherwise `0`.

#### `public bool `[`udd_ep_is_halted`](#group__usb__device__udd__group_1ga2d531ac8c1e142185c6ed6eaeb2737c0)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)` {#group__usb__device__udd__group_1ga2d531ac8c1e142185c6ed6eaeb2737c0}

Check if the endpoint *ep* is halted.

#### Parameters
* `ep` The ID of the endpoint to check.

#### Returns
`1` if *ep* is halted, otherwise `0`.

#### `public bool `[`udd_ep_set_halt`](#group__usb__device__udd__group_1ga55dd14b9b00781223e39c2549ffdb61c)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)` {#group__usb__device__udd__group_1ga55dd14b9b00781223e39c2549ffdb61c}

Set the halted state of the endpoint *ep*.

After calling this function, any transaction on *ep* will result in a STALL handshake being sent. Any pending transactions will be performed first, however.

#### Parameters
* `ep` The ID of the endpoint to be halted

#### Returns
`1` if *ep* is halted, otherwise `0`.

#### `public bool `[`udd_ep_clear_halt`](#group__usb__device__udd__group_1ga2b89e75674bd590432e9928326d5ef73)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep)` {#group__usb__device__udd__group_1ga2b89e75674bd590432e9928326d5ef73}

Clear the halted state of the endpoint *ep*.

After calling this function, any transaction on *ep* will be handled normally, i.e. a STALL handshake will not be sent, and the data toggle sequence will start at DATA0.

#### Parameters
* `ep` The ID of the endpoint to be un-halted

#### Returns
`1` if function was successfully done, otherwise `0`.

#### `public bool `[`udd_ep_wait_stall_clear`](#group__usb__device__udd__group_1ga9dde9a9ac41ffc519cc2e2f93308db1c)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep,`[`udd_callback_halt_cleared_t`](.build/docs/internals_undefined.md#group__udd__group_1ga70b1655bda30b7d03df637a1bb23bdd5)` callback)` {#group__usb__device__udd__group_1ga9dde9a9ac41ffc519cc2e2f93308db1c}

Registers a callback to call when endpoint halt is cleared.

#### Parameters
* `ep` The ID of the endpoint to use 

* `callback` NULL or function to call when endpoint halt is cleared

if the endpoint is not halted then the *callback* is called immediately.

#### Returns
`1` if the register is accepted, otherwise `0`.

#### `public static void `[`udd_ctrl_stall_data`](#group__usb__device__udd__group_1gabf919b71cee71a11e1ea4e64fb9891d1)`(void)` {#group__usb__device__udd__group_1gabf919b71cee71a11e1ea4e64fb9891d1}

Control Endpoint stall sending data.

#### `public bool `[`udd_ep_run`](#group__usb__device__udd__group_1ga3023b640115dd86dc922fcd79f5b8757)`(`[`udd_ep_id_t`](.build/docs/internals_undefined.md#group__udd__group_1ga6f25ea016c07bd48c3074f51d8ef8b01)` ep,bool b_shortpacket,uint8_t * buf,iram_size_t buf_size,`[`udd_callback_trans_t`](.build/docs/internals_undefined.md#group__udd__group_1ga4e79edfc4d62b203dbc271e80a624917)` callback)` {#group__usb__device__udd__group_1ga3023b640115dd86dc922fcd79f5b8757}

Allows to receive or send data on an endpoint.

The driver uses a specific DMA USB to transfer data from internal RAM to endpoint, if this one is available. When the transfer is finished or aborted (stall, reset, ...), the *callback* is called. The *callback* returns the transfer status and eventually the number of byte transfered. Note: The control endpoint is not authorized.

#### Parameters
* `ep` The ID of the endpoint to use 

* `b_shortpacket` Enabled automatic short packet 

* `buf` Buffer on Internal RAM to send or fill. It must be align, then use COMPILER_WORD_ALIGNED. 

* `buf_size` Buffer size to send or fill 

* `callback` NULL or function to call at the end of transfer

About *b_shortpacket*, for IN endpoint it means that a short packet (or a Zero Length Packet) will be sent to the USB line to properly close the usb transfer at the end of the data transfer. For Bulk and Interrupt OUT endpoint, it will automatically stop the transfer at the end of the data transfer (received short packet).

#### Returns
`1` if function was successfully done, otherwise `0`.

#### `public void `[`udd_set_address`](#group__usb__device__udd__group_1ga05da762e0faf9d478e532de40afa71f6)`(uint8_t address)` {#group__usb__device__udd__group_1ga05da762e0faf9d478e532de40afa71f6}

Changes the USB address of device.

#### Parameters
* `address` New USB address

#### `public uint8_t `[`udd_getaddress`](#group__usb__device__udd__group_1gaebd36638d482f6df00a8aff006ef2246)`(void)` {#group__usb__device__udd__group_1gaebd36638d482f6df00a8aff006ef2246}

Returns the USB address of device.

#### Returns
USB address

#### `public void `[`udd_send_remotewakeup`](#group__usb__device__udd__group_1gac447212e04789282dabee65a23fe2a08)`(void)` {#group__usb__device__udd__group_1gac447212e04789282dabee65a23fe2a08}

The USB driver sends a resume signal called Upstream Resume.

#### `public void `[`udd_set_setup_payload`](#group__usb__device__udd__group_1ga017ef5ea7626be258c24d345218976f9)`(uint8_t * payload,uint16_t payload_size)` {#group__usb__device__udd__group_1ga017ef5ea7626be258c24d345218976f9}

Load setup payload.

#### Parameters
* `payload` Pointer on payload 

* `payload_size` Size of payload

#### `public static void `[`udd_ctrl_fetch_ram`](#group__usb__device__udd__group_1gaf6ffb95ec28493ddaf038642ee995ce6)`(void)` {#group__usb__device__udd__group_1gaf6ffb95ec28493ddaf038642ee995ce6}

Control Endpoint translate the data in buffer into Device Request Struct.

#### `public static void `[`udd_ctrl_send_zlp_in`](#group__usb__device__udd__group_1gab6a8abd5db8a94d6becc73b2b70dc748)`(void)` {#group__usb__device__udd__group_1gab6a8abd5db8a94d6becc73b2b70dc748}

Control Endpoint send out zero length packet.

#### `public static void `[`udd_ctrl_in_sent`](#group__usb__device__udd__group_1ga181ffd0cddf5130f55df6df8ca3f916c)`(void)` {#group__usb__device__udd__group_1ga181ffd0cddf5130f55df6df8ca3f916c}

Process control endpoint IN transaction.

#### `public static void `[`udd_ctrl_out_received`](#group__usb__device__udd__group_1gaa137563d9a7717c634279ad596fbc5fb)`(void * pointer)` {#group__usb__device__udd__group_1gaa137563d9a7717c634279ad596fbc5fb}

Process control endpoint OUT transaction.

#### Parameters
* `pointer` Pointer to the endpoint transfer status parameter struct from driver layer.

#### `public static void `[`_usb_ep0_on_setup`](#group__usb__device__udd__group_1ga2f36d2d5628b8edfaf619bcb2c7de44f)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)` {#group__usb__device__udd__group_1ga2f36d2d5628b8edfaf619bcb2c7de44f}

#### `public static void `[`udd_ctrl_underflow`](#group__usb__device__udd__group_1gae49bae7d7d68329b1c050f39c902d08e)`(void * pointer)` {#group__usb__device__udd__group_1gae49bae7d7d68329b1c050f39c902d08e}

Control Endpoint Process when underflow condition has occurred.

#### Parameters
* `pointer` Pointer to the endpoint transfer status parameter struct from driver layer.

#### `public static void `[`udd_ctrl_overflow`](#group__usb__device__udd__group_1ga58ec0c5b490824774f753cc9ff6c1250)`(void * pointer)` {#group__usb__device__udd__group_1ga58ec0c5b490824774f753cc9ff6c1250}

Control Endpoint Process when overflow condition has occurred.

#### Parameters
* `pointer` Pointer to the endpoint transfer status parameter struct from driver layer.

#### `public static void `[`_usb_ep0_on_tansfer_fail`](#group__usb__device__udd__group_1ga67ec9c51a13358e3e241b2d10b3b4a05)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)` {#group__usb__device__udd__group_1ga67ec9c51a13358e3e241b2d10b3b4a05}

#### `public static void `[`_usb_ep0_on_tansfer_ok`](#group__usb__device__udd__group_1gabe51608c4f3fb3cb905463758645127c)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)` {#group__usb__device__udd__group_1gabe51608c4f3fb3cb905463758645127c}

#### `public static void `[`udd_ctrl_ep_enable`](#group__usb__device__udd__group_1ga16a526f9870d3b670345b98bcfbe166c)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst)` {#group__usb__device__udd__group_1ga16a526f9870d3b670345b98bcfbe166c}

Enable Control Endpoint.

#### Parameters
* `module_inst` Pointer to USB module instance

#### `public static void `[`_usb_on_suspend`](#group__usb__device__udd__group_1gaf4c2f4bf0f76bcf873d165f1e960c8e1)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)` {#group__usb__device__udd__group_1gaf4c2f4bf0f76bcf873d165f1e960c8e1}

#### `public static void `[`_usb_on_sof_notify`](#group__usb__device__udd__group_1gae65a2792570d8aec7e758b3526721086)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)` {#group__usb__device__udd__group_1gae65a2792570d8aec7e758b3526721086}

#### `public static void `[`_usb_on_bus_reset`](#group__usb__device__udd__group_1gaf286144a1b50b68ed2edd38d67e1f4b0)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)` {#group__usb__device__udd__group_1gaf286144a1b50b68ed2edd38d67e1f4b0}

#### `public static void `[`_usb_on_wakeup`](#group__usb__device__udd__group_1ga563d04cd60d478a430261aaa9da5e07a)`(struct `[`usb_module`](.build/docs/internals_undefined.md#structusb__module)` * module_inst,void * pointer)` {#group__usb__device__udd__group_1ga563d04cd60d478a430261aaa9da5e07a}

#### `public void `[`udd_detach`](#group__usb__device__udd__group_1ga03e59eaa264f1dbe5a52559311d0520e)`(void)` {#group__usb__device__udd__group_1ga03e59eaa264f1dbe5a52559311d0520e}

Detaches the device from the bus.

The driver must remove pull-up on USB line D- or D+.

#### `public void `[`udd_attach`](#group__usb__device__udd__group_1ga7a7c0d9236c922c2af33c6702565a99f)`(void)` {#group__usb__device__udd__group_1ga7a7c0d9236c922c2af33c6702565a99f}

Attach device to the bus when possible.

If a VBus control is included in driver, then it will attach device when an acceptable Vbus level from the host is detected.

#### `public void `[`udd_enable`](#group__usb__device__udd__group_1ga9792d1899ae058e3984d6a622fe2ad42)`(void)` {#group__usb__device__udd__group_1ga9792d1899ae058e3984d6a622fe2ad42}

Enables the USB Device mode.

#### `public void `[`udd_disable`](#group__usb__device__udd__group_1gab283432057b934e9d73ac9282d9b0f11)`(void)` {#group__usb__device__udd__group_1gab283432057b934e9d73ac9282d9b0f11}

Disables the USB Device mode.

