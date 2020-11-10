# group `udc_group` {#group__udc__group}

The UDC provides a high-level abstraction of the usb device. You can use these functions to control the main device state (start/attach/wakeup).

USB Device Custom configurationThe following USB Device configuration must be included in the [conf_usb.h](.build/docs/internals_undefined.md#conf__usb_8h) file of the application.

USB_DEVICE_VENDOR_ID (Word)
 Vendor ID provided by USB org (ATMEL 0x03EB).

USB_DEVICE_PRODUCT_ID (Word)
 Product ID (Referenced in [usb_atmel.h](.build/docs/internals_undefined.md#usb__atmel_8h)).

USB_DEVICE_MAJOR_VERSION (Byte)
 Major version of the device

USB_DEVICE_MINOR_VERSION (Byte)
 Minor version of the device

USB_DEVICE_MANUFACTURE_NAME (string)
 ASCII name for the manufacture

USB_DEVICE_PRODUCT_NAME (string)
 ASCII name for the product

USB_DEVICE_SERIAL_NAME (string)
 ASCII name to enable and set a serial number

USB_DEVICE_POWER (Numeric)
 (unit mA) Maximum device power

USB_DEVICE_ATTR (Byte)
 USB attributes available:

* USB_CONFIG_ATTR_SELF_POWERED

* USB_CONFIG_ATTR_REMOTE_WAKEUP Note: if remote wake enabled then defines remotewakeup callbacks, see Table 5-2. External API from UDC - Callback

USB_DEVICE_LOW_SPEED (Only defined)
 Force the USB Device to run in low speed

USB_DEVICE_HS_SUPPORT (Only defined)
 Authorize the USB Device to run in high speed

USB_DEVICE_MAX_EP (Byte)
 Define the maximum endpoint number used by the USB Device.
 This one is already defined in UDI default configuration. Ex:

* When endpoint control 0x00, endpoint 0x01 and endpoint 0x82 is used then USB_DEVICE_MAX_EP=2

* When only endpoint control 0x00 is used then USB_DEVICE_MAX_EP=0

* When endpoint 0x01 and endpoint 0x81 is used then USB_DEVICE_MAX_EP=1
 (configuration not possible on USBB interface)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline static bool `[`udc_include_vbus_monitoring`](#group__udc__group_1ga70d88509bac27ef9c25f693dd21d91ca)`(void)`            | Authorizes the VBUS event.
`public void `[`udc_start`](#group__udc__group_1gadf4e193509cd03ab6333d62629ea51e7)`(void)`            | Start the USB Device stack.
`public void `[`udc_stop`](#group__udc__group_1gae2264dd91b24db9d4bb23fb1a2014972)`(void)`            | Stop the USB Device stack.
`public inline static void `[`udc_attach`](#group__udc__group_1ga2e71c4c6090543bc3bab06e710e2ee6b)`(void)`            | Attach device to the bus when possible.
`public inline static void `[`udc_detach`](#group__udc__group_1ga702d387f5ebfc2e0ab41667eb7644dda)`(void)`            | Detaches the device from the bus.
`public inline void `[`udc_remotewakeup`](#group__udc__group_1ga52c0439e5f6e471a9570471f00476260)`(void)`            | The USB driver sends a resume signal called *"Upstream Resume"* This is authorized only when the remote wakeup feature is enabled by host.
`public `[`usb_iface_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__iface__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udc_get_interface_desc`](#group__udc__group_1gadb2a0f5ad1e834d4d7e7777f901d64d2)`(void)`            | Returns a pointer on the current interface descriptor.

## Members

#### `public inline static bool `[`udc_include_vbus_monitoring`](#group__udc__group_1ga70d88509bac27ef9c25f693dd21d91ca)`(void)` {#group__udc__group_1ga70d88509bac27ef9c25f693dd21d91ca}

Authorizes the VBUS event.

#### Returns
true, if the VBUS monitoring is possible.

VBus monitoring used casesThe VBus monitoring is used only for USB SELF Power application.

* By default the USB device is automatically attached when Vbus is high or when USB is start for devices without internal Vbus monitoring. [conf_usb.h](.build/docs/internals_undefined.md#conf__usb_8h) file does not contains define USB_DEVICE_ATTACH_AUTO_DISABLE. 
```cpp
//#define USB_DEVICE_ATTACH_AUTO_DISABLE 
```

* Add custom VBUS monitoring. [conf_usb.h](.build/docs/internals_undefined.md#conf__usb_8h) file contains define USB_DEVICE_ATTACH_AUTO_DISABLE: 
```cpp
#define USB_DEVICE_ATTACH_AUTO_DISABLE 
```
 User C file contains: 
```cpp
// Authorize VBUS monitoring
if (!udc_include_vbus_monitoring()) {
  // Implement custom VBUS monitoring via GPIO or other
}
Event_VBUS_present() // VBUS interrupt or GPIO interrupt or other
{
  // Attach USB Device
  udc_attach();
}
```

* Case of battery charging. [conf_usb.h](.build/docs/internals_undefined.md#conf__usb_8h) file contains define USB_DEVICE_ATTACH_AUTO_DISABLE: 
```cpp
#define USB_DEVICE_ATTACH_AUTO_DISABLE 
```
 User C file contains: 
```cpp
Event VBUS present() // VBUS interrupt or GPIO interrupt or ..
{
  // Authorize battery charging, but wait key press to start USB.
}
Event Key press()
{
  // Stop batteries charging
  // Start USB
  udc_attach();
}
```

#### `public void `[`udc_start`](#group__udc__group_1gadf4e193509cd03ab6333d62629ea51e7)`(void)` {#group__udc__group_1gadf4e193509cd03ab6333d62629ea51e7}

Start the USB Device stack.

#### `public void `[`udc_stop`](#group__udc__group_1gae2264dd91b24db9d4bb23fb1a2014972)`(void)` {#group__udc__group_1gae2264dd91b24db9d4bb23fb1a2014972}

Stop the USB Device stack.

#### `public inline static void `[`udc_attach`](#group__udc__group_1ga2e71c4c6090543bc3bab06e710e2ee6b)`(void)` {#group__udc__group_1ga2e71c4c6090543bc3bab06e710e2ee6b}

Attach device to the bus when possible.

If a VBus control is included in driver, then it will attach device when an acceptable Vbus level from the host is detected.

#### `public inline static void `[`udc_detach`](#group__udc__group_1ga702d387f5ebfc2e0ab41667eb7644dda)`(void)` {#group__udc__group_1ga702d387f5ebfc2e0ab41667eb7644dda}

Detaches the device from the bus.

The driver must remove pull-up on USB line D- or D+.

#### `public inline void `[`udc_remotewakeup`](#group__udc__group_1ga52c0439e5f6e471a9570471f00476260)`(void)` {#group__udc__group_1ga52c0439e5f6e471a9570471f00476260}

The USB driver sends a resume signal called *"Upstream Resume"* This is authorized only when the remote wakeup feature is enabled by host.

#### `public `[`usb_iface_desc_t](.build/docs/internals_usb_protocol_group.md#structusb__iface__desc__t)[UDC_DESC_STORAGE`](.build/docs/internals_undefined.md#group__udc__desc__group_1gae086959cec07a2e71ab069e25a51764f)` * `[`udc_get_interface_desc`](#group__udc__group_1gadb2a0f5ad1e834d4d7e7777f901d64d2)`(void)` {#group__udc__group_1gadb2a0f5ad1e834d4d7e7777f901d64d2}

Returns a pointer on the current interface descriptor.

#### Returns
pointer on the current interface descriptor.

