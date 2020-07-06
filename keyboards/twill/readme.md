# Twill

A 60% keyboard with only through hole components and RGB underglow.   

Based off the Gingham designed by [Yiancar](https://yiancar-designs.com/portfolio/gingham/)

![Twill image](https://imgur.com/gallery/gNAEsL6)

* Keyboard Maintainer: [UWA Makers](https://wiki.uwamakers.com//)  
* Hardware Supported: Twill PCB rev1 with ATMEGA328p 

Make example for this keyboard (after setting up your build environment):
    qmk compile -kb twill

Flash firmware:
    // In bootloader mode
    qmk flash -kb twill

Bootloader:
use usbasploader HSGW's my repository.
https://github.com/hsgw/USBaspLoader/tree/plaid

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
