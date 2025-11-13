# Vermillion's Ergo - Armored Edition

![VE.A](https://massdrop-s3.imgix.net/product-images/ve-a/MD-17533_20160504151111_9285b969d2f9c191.jpg)

This is a port of the QMK firmware for the VE.A. 

* Keyboard Maintainer: [Major Koos](https://github.com/MajorKoos)
* Keyboard Manufacturer: OddForge
* Hardware Availability: [Drop.com](https://drop.com/buy/ve-a)

Make example for this keyboard (after setting up your build environment):

    make oddforge/vea:default

Flashing example for this keyboard:

    make oddforge/vea:default:flash

or

    bootloadHID -r oddforge_vea_default.hex

## How to get QMK working on the VE.A

**Reset Key**: Hold down the key located at 3rd left position in the bottom row, commonly programmed as Left Control while plugging in the keyboard.  There is also a jumper on the bottom of the PCB (JP_FW) which you can short to get into the bootloader.

![VE.A](https://massdrop-s3.imgix.net/product-images/ve-a/MD-17533_20160330103302_53ecc4b5015273e5.jpg)


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
