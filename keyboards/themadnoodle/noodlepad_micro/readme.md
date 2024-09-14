# NoodlePad [Micro]

![NoodlePad [Micro]](https://i.imgur.com/uRmVt3ah.jpg)

The NoodlePad [Micro] is a 6 key 2 encoder macro keypad designed using RP2040 chipset.

* Keyboard Maintainer: [The Mad Noodle](https://github.com/The-Mad-Noodle)
* Hardware Supported: NoodlePad [Micro]
* Hardware Availability: https://www.madnoodleprototypes.com/shop

Compile example for this keyboard (after setting up your build environment):

    qmk compile -kb themadnoodle/noodlepad_micro -km default

Flashing example for this keyboard:

    qmk flash -kb themadnoodle/noodlepad_micro -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader & Flashing


**Physical reset button**: 

* Double press the button on the back, center, left of the PCB labeled "R" to enter the bootloader drive mode.

* If you have a pre-compiled .uf2 file, copy it into bootloader drive (RPI-RP2), board will reset automatically once file is copied sucessfully