# Gingham

![plaid](https://i.imgur.com/tTi9yR9h.jpg)

A 60% keyboard with only through hole components.   

Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [github](https://github.com/yiancar)  
Hardware Supported: ATMEGA328p with vusb [PCB](https://github.com/hsgw/plaid)  
Hardware Availability: https://yiancar-designs.com/, https://novelkeys.xyz, https://mechboards.co.uk/  

Make example for this keyboard (after setting up your build environment):
    make gingham:default

Flash firmware:
    // In bootloader mode
    make gingham:default:program

Bootloader:
use usbasploader HSGW's my repository.
https://github.com/hsgw/USBaspLoader/tree/plaid

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
