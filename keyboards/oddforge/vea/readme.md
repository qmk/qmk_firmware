# Vermillion's Ergo - Armored Edition

![VE.A](https://massdrop-s3.imgix.net/product-images/ve-a/MD-17533_20160504151111_9285b969d2f9c191.jpg)

This is a port of the QMK firmware for the VE.A. 

* Keyboard Maintainer: [Major Koos](https://github.com/MajorKoos)
* Keyboard Manufacturer: OddForge
* Hardware Availability: [Drop.com](https://drop.com/buy/ve-a)

Make example for this keyboard (after setting up your build environment):

    make oddforge/vea:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make oddforge/vea:default:flash

or

    bootloadHID -r oddforge_vea_default.hex

## How to get QMK working on the VE.A

**Reset Key**: Hold down the key located at 3rd left position in the bottom row, commonly programmed as Left Control while plugging in the keyboard.  There is also a jumper on the bottom of the PCB (JP_FW) which you can short to get into the bootloader.

 **You will need an [ISP programmer](https://www.sparkfun.com/products/9825) to get QMK working on the VE.A. first time round because the firmware for the attiny85 which controls the bling on each half [needs an upgrade](https://github.com/MajorKoos/KBDParts/blob/master/Firmware/ps2avrGB_rgb_controller_20200412.zip)**
 
- Upgrade the attiny85 on each half **before** upgrading to QMK
   - Trying to flash the atmega32 or the attiny85 with both halves connected is flaky
   - Setting JP_FW seems necessary even when using an ISP?
- Once the bling is upgraded you can upload QMK over USB using QMK Toolbox
   


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
