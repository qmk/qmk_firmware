# waffling60 Rev. E ISO

A 60% PCB for MX switches, one hot swap and one solder-pcb version with decent layout support. Revision E adds underglow and rotary encoder support.

More info: https://github.com/4pplet/waffling60

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: [waffling60](https://github.com/4pplet/waffling60)

Make example for this keyboard (after setting up your build environment):

    make 4pplet/waffling60/rev_e_iso:default

Flashing example for this keyboard:

    make 4pplet/waffling60/rev_e_iso:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

How to enter bootloader (DFU):
* Short the reset-header (labled BL/RESET) on the back of the PCB for about 2 seconds for the keyboard to enter DFU. When in DFU, it's ready to flash the firmware. If using a APM MCU it will not automatically reset after flash. Simply short the reset-header for a very short time to just reset the PCB, alternatively unplug and repluck the USB-cable to the keyboard.

Alternative option if the firmware is already pre-flashed:
* Unplug your keyboard, hold down the Spacebar and B at the same time, plug in your keyboard and wait a second before releasing the keys. The keyboard will enter DFU and is ready to flash the firmware.
