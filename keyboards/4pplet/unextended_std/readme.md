# ASK

PCB for the Unextended Standard Project. The PCB enables use of M0116, M0118, IIc and NeXT keycaps and is designed to fit in the open sourced Unextended case.

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: [Unextended Standard PCB](https://github.com/4pplet/Unextended-Standard-PCB)

Make example for this keyboard (after setting up your build environment):

    make 4pplet/unextended_std/rev_a:default

Flashing example for this keyboard:

    make 4pplet/unextended_std/rev_a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

How to enter bootloader (DFU):
* Short the reset-header (labled RESET) on tha back of the PCB for keyboard to enter DFU. When in DFU, it's ready to flash the firmware.

Alternative option if the firmware is already pre-flashed:
* Unplug your keyboard, hold down the Spacebar and B at the same time, plug in your keyboard and wait a second before releasing the keys. The keyboard will enter DFU and is ready to flash the firmware.
