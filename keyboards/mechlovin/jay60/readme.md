# jay60

![jay60](https://i.imgur.com/FVg59LUl.png)

Jay60 PCB, Unikorn PCB compatible
* Keyboard Maintainer: [Mechlovin'](https://mechlovin.studio)
* Hardware Supported: Jay60, Atmega32A
* Hardware Availability: [Mechlovin'](https://mechlovin.studio)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/jay60:default

Flashing example for this keyboard:

    make mechlovin/jay60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Bootloader reset**: Hold down the key at (0,13) in the matrix (Backspace) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
