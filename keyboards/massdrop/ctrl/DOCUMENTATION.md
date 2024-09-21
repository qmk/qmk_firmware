# Massdrop CTRL Documentation

This is a WIP and will contine to be updated for some time in the future.

This doc will include all currently available information, including low level information, for the CTRL keyboard collected from code committed by Drop, Inc. and freely available sources. It will also include a deprecation list of code committed by Drop, Inc. that is no longer needed and a TODO list for necessary code fixes and changes for existing protocol and a list of suggested improvements. This is the hopes of making MD CTRL fully QMK compatible by improving the existing protocol and/or perhaps working on a ChibiOS port at one point.

**Note**: given that all Drop, Inc. keyboards to date have used the same MCU and the same protocol, the MCU and protocol documentation should apply to all keyboards in Massdrop folder. Most HID-related information however is product-specific and will not apply to other keyboards.

### MCU 

* Microchip Technology SAMD51J18A
* RISC 32-Bit
* 120MHz Cortex®-M4
* [Datasheet](https://www.datasheets360.com/pdf/3214995481162464753)

### HID descriptor

* VENDOR_ID           0x04D8
* PRODUCT_ID          0xEED2
* DEVICE_VER          0x0101
* MANUFACTURER        "Massdrop Inc."
* PRODUCT             "CTRL Keyboard"

### USB Hub descriptor

* VENDOR_ID           0x04D8
* PRODUCT_ID          0xEEC5
* MANUFACTURER        "Massdrop Inc."
* PRODUCT             "Massdrop Hub"
