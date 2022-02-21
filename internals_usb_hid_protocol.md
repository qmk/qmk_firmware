# group `usb_hid_protocol` {#group__usb__hid__protocol}

USB Human Interface Device (HID) protocol definitions.

protocol definitions

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[`usb_hid_descriptor_t`](#structusb__hid__descriptor__t) | HID Descriptor.

# struct `usb_hid_descriptor_t` {#structusb__hid__descriptor__t}

HID Descriptor.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t `[`bLength`](#structusb__hid__descriptor__t_1a1deca1f1d6e5815b290e6e1015bce5b8) | Size of this descriptor in bytes.
`public uint8_t `[`bDescriptorType`](#structusb__hid__descriptor__t_1a67d7027b9eb9ed268d28e84fbc675707) | HID descriptor type.
`public le16_t `[`bcdHID`](#structusb__hid__descriptor__t_1ab86c23448d45c6d68efec9f9af5d10de) | Binary Coded Decimal Spec. release.
`public uint8_t `[`bCountryCode`](#structusb__hid__descriptor__t_1a969a604033b72573d59a740badf6920e) | Hardware target country.
`public uint8_t `[`bNumDescriptors`](#structusb__hid__descriptor__t_1a86ff434026085d9c0c751185eb3700c5) | Number of HID class descriptors to follow.
`public uint8_t `[`bRDescriptorType`](#structusb__hid__descriptor__t_1a6da89ed91bee6e0a4f2c8cf3b40a7ede) | Report descriptor type.
`public le16_t `[`wDescriptorLength`](#structusb__hid__descriptor__t_1ab3d5c878a0abf618eecc7f860e9aeb62) | Total length of Report descriptor.

## Members

#### `public uint8_t `[`bLength`](#structusb__hid__descriptor__t_1a1deca1f1d6e5815b290e6e1015bce5b8) {#structusb__hid__descriptor__t_1a1deca1f1d6e5815b290e6e1015bce5b8}

Size of this descriptor in bytes.

#### `public uint8_t `[`bDescriptorType`](#structusb__hid__descriptor__t_1a67d7027b9eb9ed268d28e84fbc675707) {#structusb__hid__descriptor__t_1a67d7027b9eb9ed268d28e84fbc675707}

HID descriptor type.

#### `public le16_t `[`bcdHID`](#structusb__hid__descriptor__t_1ab86c23448d45c6d68efec9f9af5d10de) {#structusb__hid__descriptor__t_1ab86c23448d45c6d68efec9f9af5d10de}

Binary Coded Decimal Spec. release.

#### `public uint8_t `[`bCountryCode`](#structusb__hid__descriptor__t_1a969a604033b72573d59a740badf6920e) {#structusb__hid__descriptor__t_1a969a604033b72573d59a740badf6920e}

Hardware target country.

#### `public uint8_t `[`bNumDescriptors`](#structusb__hid__descriptor__t_1a86ff434026085d9c0c751185eb3700c5) {#structusb__hid__descriptor__t_1a86ff434026085d9c0c751185eb3700c5}

Number of HID class descriptors to follow.

#### `public uint8_t `[`bRDescriptorType`](#structusb__hid__descriptor__t_1a6da89ed91bee6e0a4f2c8cf3b40a7ede) {#structusb__hid__descriptor__t_1a6da89ed91bee6e0a4f2c8cf3b40a7ede}

Report descriptor type.

#### `public le16_t `[`wDescriptorLength`](#structusb__hid__descriptor__t_1ab3d5c878a0abf618eecc7f860e9aeb62) {#structusb__hid__descriptor__t_1ab3d5c878a0abf618eecc7f860e9aeb62}

Total length of Report descriptor.

