# Blacktip

![Blacktip](https://i.imgur.com/w8sGP4R)

A 60-key split ortholinear keyboard

* Keyboard Maintainer: [iH0118](https://github.com/iH0118)
* Hardware Supported: 0118 Blacktip
* Hardware Availability: [design files](https://github.com/iH0118/blacktip)

Make example for this keyboard (after setting up your build environment):

    make 0118/blacktip:default

Flashing example for this keyboard:

    make 0118/blacktip:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key and plug in the keyboard.
* **Physical reset button**: Flip the bootloader switch and briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
