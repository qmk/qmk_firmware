# Perk60 ISO Rev A

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: Perk60 ISO Rev A

Make example for this keyboard (after setting up your build environment):

    make 4pplet/perk60_iso/rev_a:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

How to enter bootloader (DFU):
* Press and hold the button on the keyboard (the small one on the same side as the MCU) for more than 1 second. The keyboard will then enter bootloader (DFU) mode and it's ready to flash the firmware.
* Note: If holding the button a shorter time, the keyboard will just reset. If you want to exit bootloader mode without flashing a firmware, dissconnect the keyboard from your PC and reconnect it.

Alternative option if the firmware is already pre-flashed:
* Unplug your keyboard, hold down the Spacebar and B at the same time, plug in your keyboard and wait a second before releasing the keys. Bootmagic lite is enabled by default.
