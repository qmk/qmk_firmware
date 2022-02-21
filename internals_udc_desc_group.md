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

## Members

# struct `udc_config_t` {#structudc__config__t}

All information about the USB Device.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

