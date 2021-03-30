# Tartan # Through Hole

![tartan](https://i.imgur.com/1qSrVcs.jpg)

A 60% keyboard with only through hole components.   

* Keyboard Maintainer: [hsgw](https://github.com/hsgw)
* Hardware Supported: ATMEGA328p with vusb [PCB](https://github.com/hsgw/tartan)
* Hardware Availability: https://5z6p.com/products/tartan/

Make example for this keyboard (after setting up your build environment):

    make dm9records/tartan:default

Flash firmware:

    // In bootloader mode
    make dm9records/tartan:default:flash

## Bootloader
use usbasploader in my repository.
https://github.com/hsgw/USBaspLoader/tree/plaid


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
