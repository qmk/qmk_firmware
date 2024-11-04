# ivworks / umbra / hotswap

Hotswap 60% for Umbra.

* Keyboard Maintainer: [4pplet](https://github.com/josephawilliamsiv)
* Hardware Supported: [waffling60](https://www.iv-works.com)

Make example for this keyboard (after setting up your build environment):

    make ivworks/umbra/solder:default

Flashing example for this keyboard:

    make ivworks/umbra/solder:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

How to enter bootloader (DFU):
* Short the reset-header on the back of the PCB just to the right of the MCU, it is labeled RESET. After 2 seconds it will enter DFU and you can flash the fireware. Replug the USB cable to fresh boot the PCB.

Alternative option if the firmware is already pre-flashed:
* Unplug USB cable. Press B and Spacebar at the same time while replug the USB cable. Continue to hold the keys down for 2 seconds. Release and the PCB will enter DFU to be flash.