# mini_mighty_kbd

![mini_mighty_kbd](https://i.imgur.com/D3JGure.jpeg)

![pcb](https://i.imgur.com/x1oOogB.jpeg)

A low profile, small form factor, wired mechanical keyboard with hot-swappable switches, featuring a fully 3D printable enclosure and keycaps with an open source design, offering endless possibilities for customization and creativity.
Measuring just 256x115x17 mm (10×4.5×0.675 inches), mini·mighty·kbd is one of the thinnest and smallest keyboards on the market. It has the functionality of a 75% keyboard, packed in the size of a 60% keyboard.

* Keyboard Maintainer: [dimitrix-llc](https://github.com/dimitrix-llc)
* Hardware Supported: mini·mighty·kbd v2.2 or later PCB
* Hardware Availability: https://dimitrix.llc/keyboards

Make example for this keyboard (after setting up your build environment):

    make mini_mighty/kbd:default

Flashing example for this keyboard:

    make mini_mighty/kbd:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Bootmagic reset**: Hold down the ESC key and plug in the keyboard
* **Physical reset pad**: Briefly short the "RESET" pad on the back of the PCB
