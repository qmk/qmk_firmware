# NoodlePad [Micro]

![npv3](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [The Mad Noodle](https://github.com/The-Mad-Noodle)
* Hardware Supported: NoodlePad [Micro]
* Hardware Availability: *Links to where you can find this hardware*

This folder is set as default in the parent rules.mk - it will build firmware compatible with the RP2040 Community Edition. See [here](https://docs.qmk.fm/#/platformdev_rp2040?id=rp2040_ce) for a list.

Compile example for this keyboard (after setting up your build environment):

    qmk compile -kb themadnoodle/noodlepad/micro -km default

Flashing example for this keyboard:

    qmk flash -kb themadnoodle/noodlepad/micro -km defualt

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
