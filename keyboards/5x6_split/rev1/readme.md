# 5x6_split revision 1

![5x6_split-rev1](https://git.zacke.dev/wholteza/5x6-split-kb/raw/branch/main/rev1/images/assembled.jpeg)

**This is the first revision of the 5x6_split keyboard.**

The 5x6_split is designed to be easily accessible, with openly and freely available hardware and firmware. It features a split layout to minimize the PCB footprint, reducing manufacturing costs.

In the repository linked below (see the Hardware Availability section), you will find KiCad schematics, PCB designs, and 3D models for a printable chassis.

* Keyboard Maintainer: [wholteza](https://github.com/wholteza)
* Hardware Supported: Raspberry Pi Pico, 5x6_split PCB, 5x6_split Chassis
* Hardware Availability: [PCB, Chassi 3d-models](https://git.zacke.dev/wholteza/5x6-split-kb/src/branch/main/rev1)

Make example for this keyboard (after setting up your build environment):

    make 5x6_split/rev1:default

Flashing example for this keyboard:

    make 5x6_split/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
