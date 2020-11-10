# group `udc_desc_group` {#group__udc__desc__group}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`UDC_DESC_STORAGE`](#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)            | Defines the memory's location of USB descriptors.
`define `[`UDC_DATA`](#group__udc__desc__group_1ga1659a2f0b429f07a985a8faaa3fb27b1)            | 
`define `[`UDC_BSS`](#group__udc__desc__group_1ga198e5cdf3367aa0b35821417b7ede0b2)            | 
`struct `[`udc_config_speed_t`](#structudc__config__speed__t) | Configuration descriptor and UDI link for one USB speed.
`struct `[`udc_config_t`](#structudc__config__t) | All information about the USB Device.

## Members

#### `define `[`UDC_DESC_STORAGE`](#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f) {#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f}

Defines the memory's location of USB descriptors.

By default the Descriptor is stored in RAM (UDC_DESC_STORAGE is defined empty).

If you have need to free RAM space, it is possible to put descriptor in flash in following case:

* USB driver authorize flash transfer (USBB on UC3 and USB on Mega)

* USB Device is not high speed (UDC no need to change USB descriptors)

For UC3 application used "const".

For Mega application used "code".

#### `define `[`UDC_DATA`](#group__udc__desc__group_1ga1659a2f0b429f07a985a8faaa3fb27b1) {#group__udc__desc__group_1ga1659a2f0b429f07a985a8faaa3fb27b1}

#### `define `[`UDC_BSS`](#group__udc__desc__group_1ga198e5cdf3367aa0b35821417b7ede0b2) {#group__udc__desc__group_1ga198e5cdf3367aa0b35821417b7ede0b2}

# struct `udc_config_speed_t` {#structudc__config__speed__t}

Configuration descriptor and UDI link for one USB speed.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`usb_conf_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__conf__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`desc`](#structudc__config__speed__t_1a6603d52f85ab88bc45af669a01c4b73a) | USB configuration descriptor.
`public `[`udi_api_t](.build/docs/internals_udi_group.md#structudi__api__t)[UDC_DESC_STORAGE](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f) *[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udi_apis`](#structudc__config__speed__t_1a6b3a118ab8cad1b5fd0a3a1e8cf2ba36) | Array of UDI API pointer.

## Members

#### `public `[`usb_conf_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__conf__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`desc`](#structudc__config__speed__t_1a6603d52f85ab88bc45af669a01c4b73a) {#structudc__config__speed__t_1a6603d52f85ab88bc45af669a01c4b73a}

USB configuration descriptor.

#### `public `[`udi_api_t](.build/docs/internals_udi_group.md#structudi__api__t)[UDC_DESC_STORAGE](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f) *[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udi_apis`](#structudc__config__speed__t_1a6b3a118ab8cad1b5fd0a3a1e8cf2ba36) {#structudc__config__speed__t_1a6b3a118ab8cad1b5fd0a3a1e8cf2ba36}

Array of UDI API pointer.

# struct `udc_config_t` {#structudc__config__t}

All information about the USB Device.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`usb_dev_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__dev__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`confdev_lsfs`](#structudc__config__t_1af7a4ce04947ddceb4c621cfd1da6e19f) | USB device descriptor for low or full speed.
`public `[`udc_config_speed_t](.build/docs/internals_udc_desc_group.md#structudc__config__speed__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`conf_lsfs`](#structudc__config__t_1a5f1714368d3c5fc176c1d31705e8ab89) | USB configuration descriptor and UDI API pointers for low or full speed.
`public `[`usb_dev_bos_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__dev__bos__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`conf_bos`](#structudc__config__t_1a1618a7226bcdbef10cf749598ce5d2af) | 

## Members

#### `public `[`usb_dev_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__dev__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`confdev_lsfs`](#structudc__config__t_1af7a4ce04947ddceb4c621cfd1da6e19f) {#structudc__config__t_1af7a4ce04947ddceb4c621cfd1da6e19f}

USB device descriptor for low or full speed.

#### `public `[`udc_config_speed_t](.build/docs/internals_udc_desc_group.md#structudc__config__speed__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`conf_lsfs`](#structudc__config__t_1a5f1714368d3c5fc176c1d31705e8ab89) {#structudc__config__t_1a5f1714368d3c5fc176c1d31705e8ab89}

USB configuration descriptor and UDI API pointers for low or full speed.

#### `public `[`usb_dev_bos_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__dev__bos__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`conf_bos`](#structudc__config__t_1a1618a7226bcdbef10cf749598ce5d2af) {#structudc__config__t_1a1618a7226bcdbef10cf749598ce5d2af}

