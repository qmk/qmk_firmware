# plaid // Through Hole

![plaid](https://i.imgur.com/tTi9yR9h.jpg)

12x4 ortholinear keyboard with only through hole components.   

Keyboard Maintainer: [hsgw](https://github.com/hsgw)  
Hardware Supported: ATMEGA328p with vusb [PCB](https://github.com/hsgw/plaid)  
Hardware Availability: Group buy in r/mk

Make example for this keyboard (after setting up your build environment):
    make plaid:default

Flash firmware:
    // In bootloader mode
    make plaid:default:program

## Bootloader
use usbasploader in my repository.
https://github.com/hsgw/USBaspLoader/tree/plaid


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
