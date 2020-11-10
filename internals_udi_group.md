# group `udi_group` {#group__udi__group}

The UDI provides a common API for all classes, and this is used by UDC for the main control of USB Device interface.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[`udi_api_t`](#structudi__api__t) | UDI API.

# struct `udi_api_t` {#structudi__api__t}

UDI API.

The callbacks within this structure are called only by USB Device Controller (UDC)

The [udc_get_interface_desc()](.build/docs/internals_undefined.md#group__udc__group__interne_1gadb2a0f5ad1e834d4d7e7777f901d64d2) can be use by UDI to know the interface descriptor selected by UDC.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool(* `[`enable`](#structudi__api__t_1ab2247f6571bf21eb4139a40a23c78eea) | Enable the interface.
`public void(* `[`disable`](#structudi__api__t_1ace1449d367bdcce8d6ca549dceac7a7f) | Disable the interface.
`public bool(* `[`setup`](#structudi__api__t_1a11fce471b0558711a238238dac0d5e7c) | Handle a control request directed at an interface.
`public uint8_t(* `[`getsetting`](#structudi__api__t_1a095cfc23d86008d478b6d002afbdd66a) | Returns the current setting of the selected interface.
`public void(* `[`sof_notify`](#structudi__api__t_1a9d8887d1cfbe10252f51a733cb66b9a5) | To signal that a SOF is occurred.

## Members

#### `public bool(* `[`enable`](#structudi__api__t_1ab2247f6571bf21eb4139a40a23c78eea) {#structudi__api__t_1ab2247f6571bf21eb4139a40a23c78eea}

Enable the interface.

This function is called when the host selects a configuration to which this interface belongs through a Set Configuration request, and when the host selects an alternate setting of this interface through a Set Interface request.

#### Returns
`1` if function was successfully done, otherwise `0`.

#### `public void(* `[`disable`](#structudi__api__t_1ace1449d367bdcce8d6ca549dceac7a7f) {#structudi__api__t_1ace1449d367bdcce8d6ca549dceac7a7f}

Disable the interface.

This function is called when this interface is currently active, and

* the host selects any configuration through a Set Configuration request, or

* the host issues a USB reset, or

* the device is detached from the host (i.e. Vbus is no longer present)

#### `public bool(* `[`setup`](#structudi__api__t_1a11fce471b0558711a238238dac0d5e7c) {#structudi__api__t_1a11fce471b0558711a238238dac0d5e7c}

Handle a control request directed at an interface.

This function is called when this interface is currently active and the host sends a SETUP request with this interface as the recipient.

Use udd_g_ctrlreq to decode and response to SETUP request.

#### Returns
`1` if this interface supports the SETUP request, otherwise `0`.

#### `public uint8_t(* `[`getsetting`](#structudi__api__t_1a095cfc23d86008d478b6d002afbdd66a) {#structudi__api__t_1a095cfc23d86008d478b6d002afbdd66a}

Returns the current setting of the selected interface.

This function is called when UDC when know alternate setting of selected interface.

#### Returns
alternate setting of selected interface

#### `public void(* `[`sof_notify`](#structudi__api__t_1a9d8887d1cfbe10252f51a733cb66b9a5) {#structudi__api__t_1a9d8887d1cfbe10252f51a733cb66b9a5}

To signal that a SOF is occurred.

