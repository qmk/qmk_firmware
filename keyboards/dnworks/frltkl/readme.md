# FRLTKL

PCB that supports FRLTKLs designed by dnworks, such as DNDD and HITC.

* Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
* Hardware Supported: DNDD Solder PCB rev1 & HITC Solder PCB rev1
* Hardware Availability: [dnworks.co](https://dnworks.co/)

Make example for this keyboard (after setting up your build environment):

    make dnworks/frltkl:default

Flashing example for this keyboard:

    make dnworks/frltkl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the `RESET` button twice or short the `USB_BOOT` and `GND` pads and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available