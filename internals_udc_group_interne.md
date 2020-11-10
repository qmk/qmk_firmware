# group `udc_group_interne` {#group__udc__group__interne}

Internal implementation

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`usb_iface_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__iface__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udc_get_interface_desc`](#group__udc__group__interne_1gadb2a0f5ad1e834d4d7e7777f901d64d2)`(void)`            | Returns a pointer on the current interface descriptor.
`public static `[`usb_conf_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__conf__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udc_get_eof_conf`](#group__udc__group__interne_1ga3442594fd7435c3803460847014c8970)`(void)`            | Returns a value to check the end of USB Configuration descriptor.
`public static `[`usb_conf_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__conf__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udc_next_desc_in_iface`](#group__udc__group__interne_1ga5b377861e784ec69c3e841643169a981)`(`[`usb_conf_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__conf__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * desc,uint8_t desc_id)`            | Search specific descriptor in global interface descriptor.
`public static bool `[`udc_update_iface_desc`](#group__udc__group__interne_1gab6a52be155f35da55d33d3474f06cc47)`(uint8_t iface_num,uint8_t setting_num)`            | Search an interface descriptor This routine updates the internal pointer udc_ptr_iface.
`public static bool `[`udc_iface_disable`](#group__udc__group__interne_1ga4d8c4886411e5f90adaac8bff065c610)`(uint8_t iface_num)`            | Disables an usb device interface (UDI) This routine call the UDI corresponding to interface number.
`public static bool `[`udc_iface_enable`](#group__udc__group__interne_1gab7d44215050fc758b44c86dc88a16264)`(uint8_t iface_num,uint8_t setting_num)`            | Enables an usb device interface (UDI) This routine calls the UDI corresponding to the interface and setting number.
`public void `[`udc_start`](#group__udc__group__interne_1gadf4e193509cd03ab6333d62629ea51e7)`(void)`            | Start the USB Device stack.
`public void `[`udc_stop`](#group__udc__group__interne_1gae2264dd91b24db9d4bb23fb1a2014972)`(void)`            | Stop the USB Device stack.
`public void `[`udc_reset`](#group__udc__group__interne_1ga11a32ff7928ba06d3b59e95e0a2b7a92)`(void)`            | Reset the current configuration of the USB device, This routines can be called by UDD when a RESET on the USB line occurs.
`public void `[`udc_sof_notify`](#group__udc__group__interne_1ga4afae313045f44b5eb4c60957ab8ef4e)`(void)`            | To signal that a SOF is occurred.
`public static bool `[`udc_req_std_dev_get_status`](#group__udc__group__interne_1gad6531ffd8e25d5b7492a7a7f4f89ea3f)`(void)`            | Standard device request to get device status.
`public static bool `[`udc_req_std_ep_get_status`](#group__udc__group__interne_1ga97951f0c157b56a0bdb2c1ee01ef28c7)`(void)`            | Standard endpoint request to get endpoint status.
`public static bool `[`udc_req_std_dev_clear_feature`](#group__udc__group__interne_1gace4de90bb4ef13b7aede71038a5e1dcb)`(void)`            | Standard device request to change device status.
`public static bool `[`udc_req_std_ep_clear_feature`](#group__udc__group__interne_1ga59d4bc22153641a20eb48f8407e9c099)`(void)`            | Standard endpoint request to clear endpoint feature.
`public static bool `[`udc_req_std_dev_set_feature`](#group__udc__group__interne_1gadd42bf8a4178b3e06f78966a6323108d)`(void)`            | Standard device request to set a feature.
`public static bool `[`udc_req_std_ep_set_feature`](#group__udc__group__interne_1ga11f8eef1ab88fe1d029414f039508661)`(void)`            | Standard endpoint request to halt an endpoint.
`public static void `[`udc_valid_address`](#group__udc__group__interne_1ga8b6715772a604a998846a3aa97c042c2)`(void)`            | Change the address of device Callback called at the end of request set address.
`public static bool `[`udc_req_std_dev_set_address`](#group__udc__group__interne_1gaa800b0a860337f155b43b86444f43809)`(void)`            | Standard device request to set device address.
`public static bool `[`udc_req_std_dev_get_str_desc`](#group__udc__group__interne_1gaf13a0b91b1ec15e4aae33a7d5df2be64)`(void)`            | Standard device request to get device string descriptor.
`public static bool `[`udc_req_std_dev_get_descriptor`](#group__udc__group__interne_1gae46c685525dbe2a47ed7acdabda5f094)`(void)`            | Standard device request to get descriptors about USB device.
`public static bool `[`udc_req_std_dev_get_configuration`](#group__udc__group__interne_1gadd826de0797aae1e872f44a6a9ee81da)`(void)`            | Standard device request to get configuration number.
`public static bool `[`udc_req_std_dev_set_configuration`](#group__udc__group__interne_1ga0da31a19fcd81e03a9b0d6ba17a2cdc4)`(void)`            | Standard device request to enable a configuration.
`public static bool `[`udc_req_std_iface_get_setting`](#group__udc__group__interne_1gac9f53c587375a24ac6b63206d650f36c)`(void)`            | Standard interface request to get the alternate setting number of an interface.
`public static bool `[`udc_req_std_iface_set_setting`](#group__udc__group__interne_1gad06f93d41064705e7f6fd992fef1230f)`(void)`            | Standard interface request to set an alternate setting of an interface.
`public static bool `[`udc_reqstd`](#group__udc__group__interne_1gac82ad471b5bfa644309f98815757c867)`(void)`            | Main routine to manage the standard USB SETUP request.
`public static bool `[`udc_req_iface`](#group__udc__group__interne_1ga920a557a9121c44513deceb2f9358fc1)`(void)`            | Send the SETUP interface request to UDI.
`public static bool `[`udc_req_ep`](#group__udc__group__interne_1ga640a2df7bb1c1fbed895286a8513663c)`(void)`            | Send the SETUP interface request to UDI.
`public bool `[`udc_process_setup`](#group__udc__group__interne_1ga58c2916d7984e0e5b2143cadf4af6080)`(void)`            | Main routine to manage the USB SETUP request.
`struct `[`udc_string_desc_t`](#structudc__string__desc__t) | 

## Members

#### `public `[`usb_iface_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__iface__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udc_get_interface_desc`](#group__udc__group__interne_1gadb2a0f5ad1e834d4d7e7777f901d64d2)`(void)` {#group__udc__group__interne_1gadb2a0f5ad1e834d4d7e7777f901d64d2}

Returns a pointer on the current interface descriptor.

#### Returns
pointer on the current interface descriptor.

#### `public static `[`usb_conf_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__conf__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udc_get_eof_conf`](#group__udc__group__interne_1ga3442594fd7435c3803460847014c8970)`(void)` {#group__udc__group__interne_1ga3442594fd7435c3803460847014c8970}

Returns a value to check the end of USB Configuration descriptor.

#### Returns
address after the last byte of USB Configuration descriptor

#### `public static `[`usb_conf_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__conf__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udc_next_desc_in_iface`](#group__udc__group__interne_1ga5b377861e784ec69c3e841643169a981)`(`[`usb_conf_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__conf__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * desc,uint8_t desc_id)` {#group__udc__group__interne_1ga5b377861e784ec69c3e841643169a981}

Search specific descriptor in global interface descriptor.

#### Parameters
* `desc` Address of interface descriptor or previous specific descriptor found 

* `desc_id` Descriptor ID to search

#### Returns
address of specific descriptor found 

#### Returns
NULL if it is the end of global interface descriptor

#### `public static bool `[`udc_update_iface_desc`](#group__udc__group__interne_1gab6a52be155f35da55d33d3474f06cc47)`(uint8_t iface_num,uint8_t setting_num)` {#group__udc__group__interne_1gab6a52be155f35da55d33d3474f06cc47}

Search an interface descriptor This routine updates the internal pointer udc_ptr_iface.

#### Parameters
* `iface_num` Interface number to find in Configuration Descriptor 

* `setting_num` Setting number of interface to find

#### Returns
1 if found or 0 if not found

#### `public static bool `[`udc_iface_disable`](#group__udc__group__interne_1ga4d8c4886411e5f90adaac8bff065c610)`(uint8_t iface_num)` {#group__udc__group__interne_1ga4d8c4886411e5f90adaac8bff065c610}

Disables an usb device interface (UDI) This routine call the UDI corresponding to interface number.

#### Parameters
* `iface_num` Interface number to disable

#### Returns
1 if it is done or 0 if interface is not found

#### `public static bool `[`udc_iface_enable`](#group__udc__group__interne_1gab7d44215050fc758b44c86dc88a16264)`(uint8_t iface_num,uint8_t setting_num)` {#group__udc__group__interne_1gab7d44215050fc758b44c86dc88a16264}

Enables an usb device interface (UDI) This routine calls the UDI corresponding to the interface and setting number.

#### Parameters
* `iface_num` Interface number to enable 

* `setting_num` Setting number to enable

#### Returns
1 if it is done or 0 if interface is not found

#### `public void `[`udc_start`](#group__udc__group__interne_1gadf4e193509cd03ab6333d62629ea51e7)`(void)` {#group__udc__group__interne_1gadf4e193509cd03ab6333d62629ea51e7}

Start the USB Device stack.

#### `public void `[`udc_stop`](#group__udc__group__interne_1gae2264dd91b24db9d4bb23fb1a2014972)`(void)` {#group__udc__group__interne_1gae2264dd91b24db9d4bb23fb1a2014972}

Stop the USB Device stack.

#### `public void `[`udc_reset`](#group__udc__group__interne_1ga11a32ff7928ba06d3b59e95e0a2b7a92)`(void)` {#group__udc__group__interne_1ga11a32ff7928ba06d3b59e95e0a2b7a92}

Reset the current configuration of the USB device, This routines can be called by UDD when a RESET on the USB line occurs.

Reset the UDC.

#### `public void `[`udc_sof_notify`](#group__udc__group__interne_1ga4afae313045f44b5eb4c60957ab8ef4e)`(void)` {#group__udc__group__interne_1ga4afae313045f44b5eb4c60957ab8ef4e}

To signal that a SOF is occurred.

The UDC must send the signal to all UDIs enabled

#### `public static bool `[`udc_req_std_dev_get_status`](#group__udc__group__interne_1gad6531ffd8e25d5b7492a7a7f4f89ea3f)`(void)` {#group__udc__group__interne_1gad6531ffd8e25d5b7492a7a7f4f89ea3f}

Standard device request to get device status.

#### Returns
true if success

#### `public static bool `[`udc_req_std_ep_get_status`](#group__udc__group__interne_1ga97951f0c157b56a0bdb2c1ee01ef28c7)`(void)` {#group__udc__group__interne_1ga97951f0c157b56a0bdb2c1ee01ef28c7}

Standard endpoint request to get endpoint status.

#### Returns
true if success

#### `public static bool `[`udc_req_std_dev_clear_feature`](#group__udc__group__interne_1gace4de90bb4ef13b7aede71038a5e1dcb)`(void)` {#group__udc__group__interne_1gace4de90bb4ef13b7aede71038a5e1dcb}

Standard device request to change device status.

#### Returns
true if success

#### `public static bool `[`udc_req_std_ep_clear_feature`](#group__udc__group__interne_1ga59d4bc22153641a20eb48f8407e9c099)`(void)` {#group__udc__group__interne_1ga59d4bc22153641a20eb48f8407e9c099}

Standard endpoint request to clear endpoint feature.

#### Returns
true if success

#### `public static bool `[`udc_req_std_dev_set_feature`](#group__udc__group__interne_1gadd42bf8a4178b3e06f78966a6323108d)`(void)` {#group__udc__group__interne_1gadd42bf8a4178b3e06f78966a6323108d}

Standard device request to set a feature.

#### Returns
true if success

#### `public static bool `[`udc_req_std_ep_set_feature`](#group__udc__group__interne_1ga11f8eef1ab88fe1d029414f039508661)`(void)` {#group__udc__group__interne_1ga11f8eef1ab88fe1d029414f039508661}

Standard endpoint request to halt an endpoint.

#### Returns
true if success

#### `public static void `[`udc_valid_address`](#group__udc__group__interne_1ga8b6715772a604a998846a3aa97c042c2)`(void)` {#group__udc__group__interne_1ga8b6715772a604a998846a3aa97c042c2}

Change the address of device Callback called at the end of request set address.

#### `public static bool `[`udc_req_std_dev_set_address`](#group__udc__group__interne_1gaa800b0a860337f155b43b86444f43809)`(void)` {#group__udc__group__interne_1gaa800b0a860337f155b43b86444f43809}

Standard device request to set device address.

#### Returns
true if success

#### `public static bool `[`udc_req_std_dev_get_str_desc`](#group__udc__group__interne_1gaf13a0b91b1ec15e4aae33a7d5df2be64)`(void)` {#group__udc__group__interne_1gaf13a0b91b1ec15e4aae33a7d5df2be64}

Standard device request to get device string descriptor.

#### Returns
true if success

#### `public static bool `[`udc_req_std_dev_get_descriptor`](#group__udc__group__interne_1gae46c685525dbe2a47ed7acdabda5f094)`(void)` {#group__udc__group__interne_1gae46c685525dbe2a47ed7acdabda5f094}

Standard device request to get descriptors about USB device.

#### Returns
true if success

#### `public static bool `[`udc_req_std_dev_get_configuration`](#group__udc__group__interne_1gadd826de0797aae1e872f44a6a9ee81da)`(void)` {#group__udc__group__interne_1gadd826de0797aae1e872f44a6a9ee81da}

Standard device request to get configuration number.

#### Returns
true if success

#### `public static bool `[`udc_req_std_dev_set_configuration`](#group__udc__group__interne_1ga0da31a19fcd81e03a9b0d6ba17a2cdc4)`(void)` {#group__udc__group__interne_1ga0da31a19fcd81e03a9b0d6ba17a2cdc4}

Standard device request to enable a configuration.

#### Returns
true if success

#### `public static bool `[`udc_req_std_iface_get_setting`](#group__udc__group__interne_1gac9f53c587375a24ac6b63206d650f36c)`(void)` {#group__udc__group__interne_1gac9f53c587375a24ac6b63206d650f36c}

Standard interface request to get the alternate setting number of an interface.

#### Returns
true if success

#### `public static bool `[`udc_req_std_iface_set_setting`](#group__udc__group__interne_1gad06f93d41064705e7f6fd992fef1230f)`(void)` {#group__udc__group__interne_1gad06f93d41064705e7f6fd992fef1230f}

Standard interface request to set an alternate setting of an interface.

#### Returns
true if success

#### `public static bool `[`udc_reqstd`](#group__udc__group__interne_1gac82ad471b5bfa644309f98815757c867)`(void)` {#group__udc__group__interne_1gac82ad471b5bfa644309f98815757c867}

Main routine to manage the standard USB SETUP request.

#### Returns
true if the request is supported

#### `public static bool `[`udc_req_iface`](#group__udc__group__interne_1ga920a557a9121c44513deceb2f9358fc1)`(void)` {#group__udc__group__interne_1ga920a557a9121c44513deceb2f9358fc1}

Send the SETUP interface request to UDI.

#### Returns
true if the request is supported

#### `public static bool `[`udc_req_ep`](#group__udc__group__interne_1ga640a2df7bb1c1fbed895286a8513663c)`(void)` {#group__udc__group__interne_1ga640a2df7bb1c1fbed895286a8513663c}

Send the SETUP interface request to UDI.

#### Returns
true if the request is supported

#### `public bool `[`udc_process_setup`](#group__udc__group__interne_1ga58c2916d7984e0e5b2143cadf4af6080)`(void)` {#group__udc__group__interne_1ga58c2916d7984e0e5b2143cadf4af6080}

Main routine to manage the USB SETUP request.

Decodes and manages a setup request.

This function parses a USB SETUP request and submits an appropriate response back to the host or, in the case of SETUP OUT requests with data, sets up a buffer for receiving the data payload.

The main standard requests defined by the USB 2.0 standard are handled internally. The interface requests are sent to UDI, and the specific request sent to a specific application callback.

#### Returns
true if the request is supported, else the request is stalled by UDD

# struct `udc_string_desc_t` {#structudc__string__desc__t}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`usb_str_desc_t`](.build/docs/internals_usb_protocol_group.md#structusb__str__desc__t)` `[`header`](#structudc__string__desc__t_1ae96103b577725a05178dac3136d1a859) | 
`public le16_t `[`string`](#structudc__string__desc__t_1a9c4b5919e84bf0e87ea42a502f4dd74c) | 

## Members

#### `public `[`usb_str_desc_t`](.build/docs/internals_usb_protocol_group.md#structusb__str__desc__t)` `[`header`](#structudc__string__desc__t_1ae96103b577725a05178dac3136d1a859) {#structudc__string__desc__t_1ae96103b577725a05178dac3136d1a859}

#### `public le16_t `[`string`](#structudc__string__desc__t_1a9c4b5919e84bf0e87ea42a502f4dd74c) {#structudc__string__desc__t_1a9c4b5919e84bf0e87ea42a502f4dd74c}

