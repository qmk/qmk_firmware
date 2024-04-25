# wilba.tech WT65-H(1,2,3,4)

* Keyboard Maintainer: [Wilba6582](https://github.com/Wilba6582)
* Hardware Supported: WT65-H PCBs w/ atmega32u4
* Hardware Availability: [wilba.tech](https://wilba.tech/)

Make example for this keyboard (after setting up your build environment):

    make wilba_tech/wt65_h:default

Flashing example for this keyboard:

    make wilba_tech/wt65_h:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
