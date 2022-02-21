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

## Members

