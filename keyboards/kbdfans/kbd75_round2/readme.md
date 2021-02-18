# KBD75 round 2

QMK Firmware is not the official firmware for the KBD75 round 2. 

* Keyboard Maintainer: Anh Nguyen
* Hardware Supported: KBD75 round 2 PCB
* Hardware Availability: Not available on KBDFans anymore. PCB should look exactly like any white v1 PCB but without the RST button and uses an ATMega32A instead of an ATMega32U4. If your KBD75 PCB is white and can be remapped with Bootmapper Client, you should probably use this keymap.
Pictures can be found on KBDFans website at the bottom: https://kbdfans.com/products/kbd75-keyboard-set

Make example for this keyboard (after setting up your build environment):

    make kbdfans/kbd75_round2:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make kbdfans/kbd75_round2:default:flash

**Reset Key**: Hold down the bottom left most key located at `K00`, commonly programmed as Left Control while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
