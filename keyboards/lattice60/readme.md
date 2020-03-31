# lattice60

![lattice60](https://i.imgur.com/1TdrWii.jpg)

A HHKB layout keyboard using only through-hole components.

* Keyboard Maintainer: [emdarcher](https://github.com/emdarcher)  
* Hardware Supported: LATTICE60 PCB  
* Hardware Availability: [KeyHive](https://keyhive.xyz/)

Make example for this keyboard (after setting up your build environment):

    make lattice60:default

To activate the USBasploader bootloader, hold the BOOT button down during power on or reset. LED2 should light up to indicate that the bootloader is active.

Flash the firmware using the `make` command with the `flash` parameter, example below:

    make lattice60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
