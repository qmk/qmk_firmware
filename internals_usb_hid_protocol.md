# group `usb_hid_protocol` {#group__usb__hid__protocol}

USB Human Interface Device ([HID](.build/docs/internals_undefined.md#class_h_i_d)) protocol definitions.

protocol definitions

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`usb_reqid_hid`](#group__usb__hid__protocol_1gaa7c41bb1274630413fb8f1e9a8acb3e5)            | Hid USB requests (bRequest)
`enum `[`usb_descriptor_type_hid`](#group__usb__hid__protocol_1ga75d07fddd98e94eee499e34ce80eebc7)            | [HID](.build/docs/internals_undefined.md#class_h_i_d) USB descriptor types.
`enum `[`usb_hid_item_report_type`](#group__usb__hid__protocol_1gab8c213eaa38f71a4aae0c2bb7341f170)            | [HID](.build/docs/internals_undefined.md#class_h_i_d) Type for report descriptor.
`enum `[`usb_hid_report_type`](#group__usb__hid__protocol_1ga5832b449d0ccdae41b51ee5436e8df28)            | [HID](.build/docs/internals_undefined.md#class_h_i_d) report type.
`enum `[`usb_hid_protocol`](#group__usb__hid__protocol_1gaf68d2167c72cb42e4788cbeba994c255)            | [HID](.build/docs/internals_undefined.md#class_h_i_d) protocol.
`struct `[`usb_hid_descriptor_t`](#structusb__hid__descriptor__t) | [HID](.build/docs/internals_undefined.md#class_h_i_d) Descriptor.

## Members

#### `enum `[`usb_reqid_hid`](#group__usb__hid__protocol_1gaa7c41bb1274630413fb8f1e9a8acb3e5) {#group__usb__hid__protocol_1gaa7c41bb1274630413fb8f1e9a8acb3e5}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_REQ_HID_GET_REPORT            | 
USB_REQ_HID_GET_IDLE            | 
USB_REQ_HID_GET_PROTOCOL            | 
USB_REQ_HID_SET_REPORT            | 
USB_REQ_HID_SET_IDLE            | 
USB_REQ_HID_SET_PROTOCOL            | 

Hid USB requests (bRequest)

#### `enum `[`usb_descriptor_type_hid`](#group__usb__hid__protocol_1ga75d07fddd98e94eee499e34ce80eebc7) {#group__usb__hid__protocol_1ga75d07fddd98e94eee499e34ce80eebc7}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_DT_HID            | 
USB_DT_HID_REPORT            | 
USB_DT_HID_PHYSICAL            | 

[HID](.build/docs/internals_undefined.md#class_h_i_d) USB descriptor types.

#### `enum `[`usb_hid_item_report_type`](#group__usb__hid__protocol_1gab8c213eaa38f71a4aae0c2bb7341f170) {#group__usb__hid__protocol_1gab8c213eaa38f71a4aae0c2bb7341f170}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_HID_ITEM_REPORT_TYPE_MAIN            | 
USB_HID_ITEM_REPORT_TYPE_GLOBAL            | 
USB_HID_ITEM_REPORT_TYPE_LOCAL            | 
USB_HID_ITEM_REPORT_TYPE_LONG            | 

[HID](.build/docs/internals_undefined.md#class_h_i_d) Type for report descriptor.

#### `enum `[`usb_hid_report_type`](#group__usb__hid__protocol_1ga5832b449d0ccdae41b51ee5436e8df28) {#group__usb__hid__protocol_1ga5832b449d0ccdae41b51ee5436e8df28}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_HID_REPORT_TYPE_INPUT            | 
USB_HID_REPORT_TYPE_OUTPUT            | 
USB_HID_REPORT_TYPE_FEATURE            | 

[HID](.build/docs/internals_undefined.md#class_h_i_d) report type.

#### `enum `[`usb_hid_protocol`](#group__usb__hid__protocol_1gaf68d2167c72cb42e4788cbeba994c255) {#group__usb__hid__protocol_1gaf68d2167c72cb42e4788cbeba994c255}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
USB_HID_PROCOTOL_BOOT            | 
USB_HID_PROCOTOL_REPORT            | 

[HID](.build/docs/internals_undefined.md#class_h_i_d) protocol.

# struct `usb_hid_descriptor_t` {#structusb__hid__descriptor__t}

[HID](.build/docs/internals_undefined.md#class_h_i_d) Descriptor.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__hid__descriptor__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | Size of this descriptor in bytes.
`public uint8_t `[`bDescriptorType`](#structusb__hid__descriptor__t_1a67d7027b9eb9ed268d28e84fbc675707) | [HID](.build/docs/internals_undefined.md#class_h_i_d) descriptor type.
`public le16_t `[`bcdHID`](#structusb__hid__descriptor__t_1ab86c23448d45c6d68efec9f9af5d10de) | Binary Coded Decimal Spec. release.
`public uint8_t `[`bCountryCode`](#structusb__hid__descriptor__t_1a969a604033b72573d59a740badf6920e) | Hardware target country.
`public uint8_t `[`bNumDescriptors`](#structusb__hid__descriptor__t_1a86ff434026085d9c0c751185eb3700c5) | Number of [HID](.build/docs/internals_undefined.md#class_h_i_d) class descriptors to follow.
`public uint8_t `[`bRDescriptorType`](#structusb__hid__descriptor__t_1a6da89ed91bee6e0a4f2c8cf3b40a7ede) | Report descriptor type.
`public le16_t `[`wDescriptorLength`](#structusb__hid__descriptor__t_1ab3d5c878a0abf618eecc7f860e9aeb62) | Total length of Report descriptor.

## Members

#### `public uint8_t `[`bLength`](#structusb__hid__descriptor__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__hid__descriptor__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

Size of this descriptor in bytes.

#### `public uint8_t `[`bDescriptorType`](#structusb__hid__descriptor__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__hid__descriptor__t_1a67d7027b9eb9ed268d28e84fbc675707}

[HID](.build/docs/internals_undefined.md#class_h_i_d) descriptor type.

#### `public le16_t `[`bcdHID`](#structusb__hid__descriptor__t_1ab86c23448d45c6d68efec9f9af5d10de) {#structusb__hid__descriptor__t_1ab86c23448d45c6d68efec9f9af5d10de}

Binary Coded Decimal Spec. release.

#### `public uint8_t `[`bCountryCode`](#structusb__hid__descriptor__t_1a969a604033b72573d59a740badf6920e) {#structusb__hid__descriptor__t_1a969a604033b72573d59a740badf6920e}

Hardware target country.

#### `public uint8_t `[`bNumDescriptors`](#structusb__hid__descriptor__t_1a86ff434026085d9c0c751185eb3700c5) {#structusb__hid__descriptor__t_1a86ff434026085d9c0c751185eb3700c5}

Number of [HID](.build/docs/internals_undefined.md#class_h_i_d) class descriptors to follow.

#### `public uint8_t `[`bRDescriptorType`](#structusb__hid__descriptor__t_1a6da89ed91bee6e0a4f2c8cf3b40a7ede) {#structusb__hid__descriptor__t_1a6da89ed91bee6e0a4f2c8cf3b40a7ede}

Report descriptor type.

#### `public le16_t `[`wDescriptorLength`](#structusb__hid__descriptor__t_1ab3d5c878a0abf618eecc7f860e9aeb62) {#structusb__hid__descriptor__t_1ab3d5c878a0abf618eecc7f860e9aeb62}

Total length of Report descriptor.

