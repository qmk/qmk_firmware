# M6-C

![M6-C](https://i.imgur.com/gkRotHh.jpeg)

The following is the QMK Firmware for the M6-C PCB.

* Keyboard Maintainer: [Wolf](https://github.com/ToastyStoemp)
* Hardware Supported: M6-C PCB
* Hardware Availability: https://ramaworks.store/products/m6-c

Make example for this keyboard (after setting up your build environment):

	make wolf/m6_c:default

Flashing example for this keyboard:

    make wolf/m6_c:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways: 
* **Bootmagic reset**: Hold down the key ESC key and plug in the keyboard (Top Left most switch)
* **Physical reset button**: Double press the button through the pinhole in the case
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
