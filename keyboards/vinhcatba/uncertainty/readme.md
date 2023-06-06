# uncertainty

![uncertainty](https://i.imgur.com/IKrn37B.jpeg)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Vinh Le](https://github.com/vinhcatba)
* Hardware Supported: The PCB is [here](https://github.com/vinhcatba/uncertainty), controller supported: STM32F401 Blackpill
* Hardware Availability: [Open-source hardware](https://github.com/vinhcatba/uncertainty)

Make example for this keyboard (after setting up your build environment):

    make uncertainty:default

Flashing example for this keyboard:

    make uncertainty:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: On Blackpill board: Hold `NRST` and `BOOT0` -> Release `NRST` first and **quickly** release `BOOT0` right after.
* **Keycode in layout**: Press `FN` + `ESC`
