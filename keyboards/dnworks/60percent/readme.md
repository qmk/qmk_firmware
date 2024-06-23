# DN60

![Layout Compatibility](https://i.imgur.com/HN4Eexg.png)

Supports dnworks 60% rev1 PCBs.

* Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
* Hardware Supported: SBL Solder PCB rev1, DN Solder PCB rev1
* Hardware Availability: https://dnworks.co/products

Make example for this keyboard (after setting up your build environment):

    make dnworks/60percent:default

Flashing example for this keyboard:

    make dnworks/60percent:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down escape and plug in the keyboard
* **Physical reset button**: Short the 'USB_BOOT' button and plug in keyboard or press the 'RESET' button twice with the keyboard plugged in.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available