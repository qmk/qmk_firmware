# BM16A V2

![bm16v2](https://i.imgur.com/3nr7bSoh.png)

A 16 key macropad, with USB-C and per-key RGB.

* Keyboard Maintainer: QMK Community
* Hardware Supported: BM16A PCB (`BM16V2-ARM`)
* Hardware Availability: [KPrepublic](https://kprepublic.com/collections/bm16/products/bm16a-16-keys-custom-mechanical-keyboard-pcb-plate-programmed-numpad-layouts-qmk-firmware-with-rgb-bottom-underglow-alps-mx)

Make example for this keyboard (after setting up your build environment):

    make kprepublic/bm16v2:default

Flashing example for this keyboard:

    make kprepublic/bm16a/v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
