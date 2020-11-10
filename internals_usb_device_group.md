# group `usb_device_group` {#group__usb__device__group}

This module includes USB Stack Device implementation. The stack is divided in three parts:

* USB Device Controller (UDC) provides USB chapter 9 compliance

* USB Device Interface (UDI) provides USB Class compliance

* USB Device Driver (UDD) provides USB Driver for each Atmel MCU

Many USB Device applications can be implemented on Atmel MCU. Atmel provides many application notes for different applications:

* AVR4900, provides general information about Device Stack

* AVR4901, explains how to create a new class

* AVR4902, explains how to create a composite device

* AVR49xx, all device classes provided in ASF have an application note

A basic USB knowledge is required to understand the USB Device Class application notes ([HID](.build/docs/internals_undefined.md#class_h_i_d),MS,CDC,PHDC,...). Then, to create an USB device with only one class provided by ASF, refer directly to the application note corresponding to this USB class. The USB Device application note for New Class and Composite is dedicated to advanced USB users.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

